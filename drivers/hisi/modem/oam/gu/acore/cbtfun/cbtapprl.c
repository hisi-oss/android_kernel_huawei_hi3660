/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */



/*****************************************************************************
  1 ??????????
**************************************************************************** */

#include "OmHdlcInterface.h"
#include "cbtapprl.h"
#include "omprivate.h"
#include "CbtPpm.h"
#include "diag_api.h"




#define    THIS_FILE_ID        PS_FILE_ID_APP_CBT_RL_C
/*****************************************************************************
  2 ????????????
*****************************************************************************/

VOS_UINT32                              g_ulCbtAcpuDbgFlag = VOS_FALSE;


#define COMPONENT_MODE_COMBINE(CompMode, MsgId)  (((CompMode)<<16) | (MsgId))

/* CBT???????????????????? */
CBT_RCV_CHAN_CTRL_INFO_STRU             g_stAcpuCbtCtrlInfo;
CBT_HDLC_ENCODE_MEM_CTRL                g_stCbtHdlcEncodeBuf;

VOS_SEM                                 g_ulTxCbtSem;
VOS_UINT32                              g_ulExpRcvTransId;
VOS_UINT32                              g_ulCbtMsgSN;


/*****************************************************************************
  3 ????????
*****************************************************************************/


VOS_UINT32 CBT_AcpuUsbFrameInit(VOS_VOID)
{
    VOS_UINT_PTR                        ulRealAddr;

    /* ????CBT????HDLC??????????uncached memory */
    PAM_MEM_SET_S(&g_stCbtHdlcEncodeBuf, sizeof(g_stCbtHdlcEncodeBuf), 0, sizeof(g_stCbtHdlcEncodeBuf));

    g_stCbtHdlcEncodeBuf.pucBuf = (VOS_UINT8 *)VOS_UnCacheMemAlloc(2 * CBT_HDLC_BUF_MAX_LEN, &ulRealAddr);

    if (VOS_NULL_PTR == g_stCbtHdlcEncodeBuf.pucBuf)
    {
        LogPrint("CBT_AcpuUsbFrameInit: VOS_UnCacheMemAlloc failed \n");
        return VOS_ERR;
    }

    /* ????buf?????? */
    g_stCbtHdlcEncodeBuf.pucRealBuf = (VOS_UINT8 *)ulRealAddr;
    g_stCbtHdlcEncodeBuf.ulBufSize  = 2 * CBT_HDLC_BUF_MAX_LEN;

    return VOS_OK;
}


VOS_UINT32 CBT_AcpuInit(VOS_VOID)
{
    g_ulCbtMsgSN       = 0;

    PAM_MEM_SET_S(&g_stAcpuCbtCtrlInfo, sizeof(CBT_RCV_CHAN_CTRL_INFO_STRU), 0, sizeof(CBT_RCV_CHAN_CTRL_INFO_STRU));

    /* ??????????0 */
    g_stAcpuCbtCtrlInfo.stMsgCombineInfo.ucExpectedSegSn = 0;
    g_stAcpuCbtCtrlInfo.stMsgCombineInfo.usTimeStampH    = 0;
    g_stAcpuCbtCtrlInfo.ulCbtSwitchOnOff = CBT_STATE_IDLE;

    if (VOS_OK != CBT_AcpuUsbFrameInit())
    {
        LogPrint("CBT_AcpuInit:CBT_AcpuUsbFrameInit Fail.\n");
        return VOS_ERR;
    }

    /* ?????????????? */
    if (VOS_OK != VOS_SmMCreate("TXCBT", VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE, &g_ulTxCbtSem))
    {
        LogPrint("OM_AcpuInit: Error, VOS_SmMCreate Fail\n");
        return VOS_ERR;
    }

    return VOS_OK;
}

VOS_UINT32 CBT_AcpuSsIdToPid(VOS_UINT8 ucSsId, VOS_UINT32 *pulPid)
{
      switch(ucSsId)
      {
        case CBT_SSID_MODEM_CPU:
        case CBT_SSID_LTE_DSP:
        case CBT_SSID_GU_DSP:
        case CBT_SSID_TDS_DSP:
        case CBT_SSID_X_DSP:
            *pulPid = CCPU_PID_CBT;/* ccpu cbt pid */
            break;
        case CBT_SSID_APP_CPU:
            *pulPid = ACPU_PID_CBT; /* acpu cbt pid */
            break;
        default:
            return VOS_ERR;
      }

      return VOS_OK;
}


VOS_UINT32 CBT_AcpuMsgDispatch(CBT_RCV_CHAN_CTRL_INFO_STRU * pstCtrlInfo)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulTransId;
    CBT_MSG_COMBINE_INFO_STRU          *pstCombineInfo;
    CBT_UNIFORM_MSG_STRU               *pstCbtMsg;

    pstCombineInfo = &(pstCtrlInfo->stMsgCombineInfo);
    pstCbtMsg      = (CBT_UNIFORM_MSG_STRU *)pstCombineInfo->pstWholeMsg->aucValue;
    ulTransId      = pstCbtMsg->stMsgHeader.ulTransId;

    if ((CBT_STATE_IDLE == g_stAcpuCbtCtrlInfo.ulCbtSwitchOnOff)
     && (APP_OM_ESTABLISH_REQ != pstCbtMsg->usMsgId))
    {
        return VOS_ERR;
    }

    /*??????????????*/
    if (APP_OM_ESTABLISH_REQ == pstCbtMsg->usMsgId)
    {
        g_ulExpRcvTransId  = ulTransId;
    }

    if (g_ulExpRcvTransId != ulTransId)
    {
        /*????TransId??????????????*/
        pstCtrlInfo->stPcToUeErrRecord.usTransIdErr++;
    }

    g_ulExpRcvTransId = ulTransId + 1;

    /*lint -e40*/
    CBT_ACPU_DEBUG_TRACE((pstCombineInfo->pstWholeMsg)->aucValue, (pstCombineInfo->pstWholeMsg)->ulLength, CBT_ACPU_DISPATCH_MSG);
    /*lint +e40*/

    /* ????OSA ??????????CBT */
    if (CCPU_PID_CBT == (pstCombineInfo->pstWholeMsg)->ulReceiverPid)/* ??????C?? */
    {
        pstCtrlInfo->stPcToUeSucRecord.stCcpuData.ulDataLen += (pstCombineInfo->pstWholeMsg)->ulLength;
        pstCtrlInfo->stPcToUeSucRecord.stCcpuData.ulNum++;
    }
    else /* ??????A?? */
    {
        pstCtrlInfo->stPcToUeSucRecord.stAcpuData.ulDataLen += (pstCombineInfo->pstWholeMsg)->ulLength;
        pstCtrlInfo->stPcToUeSucRecord.stAcpuData.ulNum++;
    }

    ulRslt = VOS_SendMsg(PC_PID_TOOL, (pstCombineInfo->pstWholeMsg));
    pstCombineInfo->pstWholeMsg = VOS_NULL_PTR;

    if (VOS_OK != ulRslt )
    {
        return VOS_ERR;
    }
    return VOS_OK;

}

VOS_UINT32 CBT_AcpuMsgCombine(CBT_RCV_CHAN_CTRL_INFO_STRU *pstCtrlInfo, VOS_UINT8 *pucData, VOS_UINT32 usLen)
{
    VOS_UINT32                          ulRslt = VOS_OK;
    VOS_UINT32                          ulTransId;
    VOS_UINT32                          ulTimeStampL;
    VOS_UINT16                          usTimeStampH;

    VOS_UINT8                           ucCurrentSegSn;
    VOS_UINT8                           ucFragFlag;
    VOS_UINT8                           ucEof;

    CBT_MSG_HEAD_STRU                  *pstMsgHeader;
    CBT_UNIFORM_MSG_STRU               *pstAppCbtMsg;
    CBT_MSG_COMBINE_INFO_STRU          *pstCombineInfo;

    pstCombineInfo = &(pstCtrlInfo->stMsgCombineInfo);

    /*Check the input parameter's validity.Make sure empty segment can't pass*/
    if ((VOS_NULL_PTR == pucData)
     || (usLen <= CBT_MSG_HEADER_LENGTH))
    {
        LogPrint("CBT_AcpuMsgCombine: The input is wrong.");

        pstCtrlInfo->stPcToUeErrRecord.usLenTooShortErr++;

        return VOS_ERR;
    }

    pstMsgHeader = (CBT_MSG_HEAD_STRU *)pucData;
    /*????????????????0x07(??CBT????????????????????). ??????????????5555aaaa??????????????*/
    if (CBT_MSG_FIRST_BYTE != pstMsgHeader->ucSid)
    {
        pstCtrlInfo->stPcToUeErrRecord.usDatatypeErr++;

        return VOS_ERR;
    }

    ucFragFlag     = pstMsgHeader->stMsgSegment.ucFragFlag;
    ucCurrentSegSn = pstMsgHeader->stMsgSegment.ucFragIndex;
    ucEof          = pstMsgHeader->stMsgSegment.ucEof;

    ulTransId      = pstMsgHeader->ulTransId;
    ulTimeStampL   = pstMsgHeader->stTimeStamp.ulTimestampL;
    usTimeStampH   = pstMsgHeader->stTimeStamp.usTimestampH;

    /*??????*/
    if (0 == ucFragFlag)
    {
        ucCurrentSegSn = 0;
        ucEof          = CBT_END_FRAME;
    }

    /*When the MSG packet is new, we need initialize the static variable.*/
    if (0 == ucCurrentSegSn)
    {
        if (VOS_NULL_PTR != pstCombineInfo->pstWholeMsg)
        {
            if (VOS_OK != VOS_FreeMsg(PC_PID_TOOL, pstCombineInfo->pstWholeMsg))
            {
            }
            pstCombineInfo->pstWholeMsg = VOS_NULL_PTR;

            pstCtrlInfo->stPcToUeErrRecord.usPacketLostErr++;
        }

        /*The new MSG packet is coming.*/
        pstCombineInfo->ucExpectedSegSn = 0;
        pstCombineInfo->ulMoveLen       = 0;

        pstCombineInfo->ulTransId    = ulTransId;
        pstCombineInfo->ulTimeStampL = ulTimeStampL;
        pstCombineInfo->usTimeStampH = usTimeStampH;

        if (usLen < (CBT_MSG_HEADER_LENGTH + CBT_MSG_IDLEN_LENGTH))
        {
            LogPrint("CBT_AcpuMsgCombine: The input parameter is wrong.");

            pstCtrlInfo->stPcToUeErrRecord.usMsgLenErr++;

            return VOS_ERR;
        }
        pstAppCbtMsg = (CBT_UNIFORM_MSG_STRU *)pucData;
        pstCombineInfo->ulTotalMsgLen = pstAppCbtMsg->ulMsgLength + CBT_MSG_HEADER_LENGTH + CBT_MSG_IDLEN_LENGTH;

        /* ??????????????????????????*/
        if (CBT_TOTAL_MSG_MAX_LEN < pstCombineInfo->ulTotalMsgLen)
        {
            pstCtrlInfo->stPcToUeErrRecord.usMsgTooLongErr++;

            LogPrint1("CBT_AcpuMsgUCombine: receive first msg pack is too long %d;\r\n",
                        (VOS_INT32)pstCombineInfo->ulTotalMsgLen);

            /* ????????????????1024???????????????????????????????????????????? */
            VOS_ProtectionReboot(OAM_PC_LENGTH_TOO_BIG, (VOS_INT)pstCombineInfo->ulTotalMsgLen, 0, (VOS_CHAR *)pucData, 1024);

            return VOS_ERR;
        }

        /*Allocate the memory space.*/
        pstCombineInfo->pstWholeMsg = VOS_AllocMsg(PC_PID_TOOL, pstCombineInfo->ulTotalMsgLen);
        if (VOS_NULL_PTR == pstCombineInfo->pstWholeMsg)
        {
            LogPrint("CBT_AcpuMsgCombine: VOS_AllocMsg fail.");

            pstCtrlInfo->stPcToUeErrRecord.usAllocMsg++;

            return VOS_ERR;
        }

        /* ????SSID????????????PID */
        ulRslt = CBT_AcpuSsIdToPid(pstAppCbtMsg->stMsgHeader.stModemSsid.ucSsid, &(pstCombineInfo->pstWholeMsg)->ulReceiverPid);
        if (VOS_OK != ulRslt)
        {
            /* ???????????? */
            if (VOS_OK != VOS_FreeMsg(PC_PID_TOOL, pstCombineInfo->pstWholeMsg))
            {
            }

            pstCombineInfo->pstWholeMsg = VOS_NULL_PTR;

            pstCtrlInfo->stPcToUeErrRecord.usCpuIdErr++;

            return VOS_ERR;
        }

        PAM_MEM_CPY_S((VOS_UINT8*)((pstCombineInfo->pstWholeMsg)->aucValue) + pstCombineInfo->ulMoveLen,
                      CBT_MSG_HEADER_LENGTH,
                      pucData,
                      CBT_MSG_HEADER_LENGTH);

        pstCombineInfo->ulMoveLen += CBT_MSG_HEADER_LENGTH;
    }

    /*The expected TransId and Time Stamp is match*/
    if (pstCombineInfo->ulTransId != ulTransId)
    {
        /*Print the error info.*/
        LogPrint2("CBT_AcpuMsgCombine: expected TransId is %d, current SN is %d.", (VOS_INT)pstCombineInfo->ulTransId, (VOS_INT)ulTransId);

        /* ???????????? */
        if (VOS_OK != VOS_FreeMsg(PC_PID_TOOL, pstCombineInfo->pstWholeMsg))
        {
        }

        pstCombineInfo->pstWholeMsg     = VOS_NULL_PTR;
        pstCombineInfo->ucExpectedSegSn = 0;

        pstCtrlInfo->stPcToUeErrRecord.usMsgSnErr++;

        return VOS_ERR;
    }

    if ( (pstCombineInfo->ulTimeStampL != ulTimeStampL) || (pstCombineInfo->usTimeStampH != usTimeStampH) )
    {
        /*Print the error info.*/
        LogPrint("CBT_AcpuMsgCombine: expected TimeStamp is inCorrect.");

        /* ???????????? */
        if (VOS_OK != VOS_FreeMsg(PC_PID_TOOL, pstCombineInfo->pstWholeMsg))
        {
        }

        pstCombineInfo->pstWholeMsg     = VOS_NULL_PTR;
        pstCombineInfo->ucExpectedSegSn = 0;

        pstCtrlInfo->stPcToUeErrRecord.usTimeStampErr++;

        return VOS_ERR;
    }
    /*The expected MSG pakcet is lost.*/
    if (pstCombineInfo->ucExpectedSegSn != ucCurrentSegSn)
    {
        /*Print the error info.*/
        LogPrint2("CBT_AcpuMsgCombine: expected SN is %d, current SN is %d.", (VOS_INT)pstCombineInfo->ucExpectedSegSn, (VOS_INT)ucCurrentSegSn);

        /* ???????????? */
        if (VOS_OK != VOS_FreeMsg(PC_PID_TOOL, pstCombineInfo->pstWholeMsg))
        {
        }

        pstCombineInfo->pstWholeMsg     = VOS_NULL_PTR;
        pstCombineInfo->ucExpectedSegSn = 0;

        pstCtrlInfo->stPcToUeErrRecord.usMsgSnErr++;

        return VOS_ERR;
    }

    /*We make sure that the memory can't be violated.*/
    if (pstCombineInfo->ulTotalMsgLen < (pstCombineInfo->ulMoveLen + (usLen - CBT_MSG_HEADER_LENGTH)))
    {
        LogPrint("CBT_AcpuMsgCombine: The length of the packet is biger than the size of allocated memory.\n");

        /* ???????????? */
        if (VOS_OK != VOS_FreeMsg(PC_PID_TOOL, pstCombineInfo->pstWholeMsg))
        {
        }

        pstCombineInfo->pstWholeMsg     = VOS_NULL_PTR;
        pstCombineInfo->ucExpectedSegSn = 0;

        pstCtrlInfo->stPcToUeErrRecord.usNoMemErr++;

        return VOS_ERR;
    }

    PAM_MEM_CPY_S((VOS_UINT8*)((pstCombineInfo->pstWholeMsg)->aucValue) + pstCombineInfo->ulMoveLen,
                   (usLen - CBT_MSG_HEADER_LENGTH),
                   pucData + CBT_MSG_HEADER_LENGTH,
                   (usLen - CBT_MSG_HEADER_LENGTH));

    pstCombineInfo->ulMoveLen += usLen - CBT_MSG_HEADER_LENGTH;
    pstCombineInfo->ucExpectedSegSn ++;

    /*If the current MSG packet is an complete packet.*/
    if (CBT_END_FRAME == ucEof)
    {
        /*It will send the MSG to CBT module.*/
        ulRslt = CBT_AcpuMsgDispatch(pstCtrlInfo);

        pstCombineInfo->ucExpectedSegSn = 0;

        return ulRslt;
    }

    return VOS_OK;
}

VOS_UINT32 CBT_AcpuRcvData(VOS_UINT8 *pucData, VOS_UINT32 ulSize)
{
    return CBT_AcpuMsgCombine(&g_stAcpuCbtCtrlInfo, pucData, ulSize);
}


VOS_UINT32 CBT_AcpuSendSegData(VOS_UINT8 * pucSrc, VOS_UINT16 usSrcLen)
{
    VOS_UINT16                         usHdlcEncLen;
    VOS_UINT32                         ulResult;

    /*????????????*/
    if ( VOS_OK != VOS_SmP(g_ulTxCbtSem, OM_PV_TIMEOUT) )
    {
        LogPrint("CBT_AcpuSendSegData, Error, TxBuffSem VOS_SmP Failed.\n");

        return VOS_ERR;
    }

    /* ??HDLC???? */
    if ( VOS_OK != Om_HdlcEncap(pucSrc,
                                usSrcLen,
                                g_stCbtHdlcEncodeBuf.pucBuf,
                                (VOS_UINT16)g_stCbtHdlcEncodeBuf.ulBufSize,
                                &usHdlcEncLen) )
    {
        if (VOS_OK != VOS_SmV(g_ulTxCbtSem))
        {
        }

        return VOS_ERR;
    }

    ulResult = CBTPPM_OamCbtPortDataSnd(g_stCbtHdlcEncodeBuf.pucBuf, g_stCbtHdlcEncodeBuf.pucRealBuf, usHdlcEncLen);

    if (VOS_OK != VOS_SmV(g_ulTxCbtSem))
    {
    }

    return ulResult;
}


VOS_UINT32 CBT_AcpuSendData(CBT_UNIFORM_MSG_STRU * pstMsg, VOS_UINT16 usMsgLen)
{
    VOS_UINT8                           ucCurSegNum = 0; /*??????????*/
    VOS_UINT_PTR                        ulTempAddress;
    VOS_UINT8                           ucMsgCnt    = 1; /*??????????*/

    VOS_UINT8                          *pucBuf = VOS_NULL_PTR;
    VOS_UINT8                          *pucTmpBuf;

    /*???????????? ???????? ??????????CNF ??????????*/
    if ((CBT_STATE_IDLE == g_stAcpuCbtCtrlInfo.ulCbtSwitchOnOff)
     && (OM_APP_ESTABLISH_CNF != pstMsg->usMsgId))
    {
        return VOS_OK;
    }

    /************************ ????????hdlc?????????? ***********************/
    /* ???????????? */
    ucMsgCnt = (VOS_UINT8)((usMsgLen - CBT_MSG_HEADER_LENGTH + (CBT_MSG_CONTEXT_MAX_LENGTH - 1))/(CBT_MSG_CONTEXT_MAX_LENGTH));

    /*??????????????????????*/
    pucTmpBuf = (VOS_UINT8*)VOS_MemAlloc(PC_PID_TOOL,
                DYNAMIC_MEM_PT, CBT_MSG_SEGMENT_LEN + CBT_RL_DATATYPE_LEN);

    if (VOS_NULL_PTR == pucTmpBuf)
    {
        LogPrint("OM_UsbFrameInit:VOS_MemAlloc g_pstSegMsgEx Failed!\n");
        return VOS_ERR;
    }

    /*TransId ?? ??????*/
    pstMsg->stMsgHeader.ulTransId                = g_ulCbtMsgSN++;
    pstMsg->stMsgHeader.stTimeStamp.ulTimestampL = VOS_GetSlice();
    pstMsg->stMsgHeader.stTimeStamp.usTimestampH = 0;
    pstMsg->stMsgHeader.stMsgSegment.ucFragFlag  = 0;

    /* ??????????????????datatype*/
    pucTmpBuf[0] = 0x01;
    pucBuf = pucTmpBuf + CBT_RL_DATATYPE_LEN;

    ulTempAddress = (VOS_UINT_PTR)pstMsg + CBT_MSG_HEADER_LENGTH;
    usMsgLen -= CBT_MSG_HEADER_LENGTH;

    /* ?????????????????????????????????????????????????????????? */
    for (ucCurSegNum = 0; ucCurSegNum < ucMsgCnt-1; ucCurSegNum++)
    {
        pstMsg->stMsgHeader.stMsgSegment.ucFragIndex = ucCurSegNum;
        pstMsg->stMsgHeader.stMsgSegment.ucEof = 0;
        pstMsg->stMsgHeader.stMsgSegment.ucFragFlag = 1;

        PAM_MEM_CPY_S(pucBuf,
                      CBT_MSG_HEADER_LENGTH,
                      (VOS_UINT8*)pstMsg,
                      CBT_MSG_HEADER_LENGTH);

        PAM_MEM_CPY_S(pucBuf + CBT_MSG_HEADER_LENGTH,
                      (CBT_MSG_SEGMENT_LEN - CBT_MSG_HEADER_LENGTH),
                      (VOS_UINT8*)ulTempAddress,
                      (CBT_MSG_SEGMENT_LEN - CBT_MSG_HEADER_LENGTH));

        ulTempAddress += CBT_MSG_SEGMENT_LEN - CBT_MSG_HEADER_LENGTH;

        /* ??????????????????????USB???????????? */
        if (VOS_OK != CBT_AcpuSendSegData(pucTmpBuf, CBT_RL_DATATYPE_LEN + CBT_MSG_SEGMENT_LEN))
        {
            (VOS_VOID)VOS_MemFree(PC_PID_TOOL, pucTmpBuf);

            return VOS_ERR;
        }

        pucBuf = pucTmpBuf + CBT_RL_DATATYPE_LEN;

        /* ?????????????????? */
        usMsgLen -= (CBT_MSG_SEGMENT_LEN - CBT_MSG_HEADER_LENGTH);
    }

    pstMsg->stMsgHeader.stMsgSegment.ucFragIndex = ucMsgCnt - 1;
    pstMsg->stMsgHeader.stMsgSegment.ucEof = CBT_END_FRAME;

    PAM_MEM_CPY_S(pucBuf,
                  CBT_MSG_HEADER_LENGTH,
                  (VOS_UINT8*)pstMsg,
                  CBT_MSG_HEADER_LENGTH);

    PAM_MEM_CPY_S(pucBuf + CBT_MSG_HEADER_LENGTH,
                  usMsgLen,
                  (VOS_UINT8*)ulTempAddress,
                  usMsgLen);

    /* ??????????????????????USB???????????? */
    if ( VOS_OK != CBT_AcpuSendSegData(pucTmpBuf, CBT_RL_DATATYPE_LEN + usMsgLen + CBT_MSG_HEADER_LENGTH))
    {
        (VOS_VOID)VOS_MemFree(PC_PID_TOOL, pucTmpBuf);
        return VOS_ERR;
    }

    (VOS_VOID)VOS_MemFree(PC_PID_TOOL, pucTmpBuf);
    return VOS_OK;
}


VOS_VOID CBT_AcpuResetMsgHead(CBT_UNIFORM_MSG_STRU * pstCbtMsg)
{
    pstCbtMsg->stMsgHeader.ucSid = 0x07;
    pstCbtMsg->stMsgHeader.ucSessionID = 0x01;

    /*????????*/
    pstCbtMsg->stMsgHeader.stMsgSegment.ucMsgType = CBT_MT_CNF;
    pstCbtMsg->stMsgHeader.stMsgSegment.ucFragIndex = 0;
    pstCbtMsg->stMsgHeader.stMsgSegment.ucEof = 1;
    pstCbtMsg->stMsgHeader.stMsgSegment.ucFragFlag = 0;
}

VOS_VOID CBT_AcpuSendResultChannel(CBT_MODEM_SSID_STRU stModemSsid, CBT_COMPONENT_MODE_STRU stCompMode,
                            VOS_UINT16 usReturnPrimId, VOS_UINT32 ulResult)
{
    CBT_UNIFORM_MSG_STRU                stCbtToPcMsg;

    PAM_MEM_SET_S(&stCbtToPcMsg, sizeof(CBT_UNIFORM_MSG_STRU), 0, sizeof(CBT_UNIFORM_MSG_STRU));

    CBT_AcpuResetMsgHead(&stCbtToPcMsg);

    stCbtToPcMsg.stMsgHeader.stModemSsid = stModemSsid;
    stCbtToPcMsg.usMsgId     = usReturnPrimId;
    stCbtToPcMsg.stCompMode  = stCompMode;
    stCbtToPcMsg.ulMsgLength = 4;

    *((VOS_UINT32*)(stCbtToPcMsg.aucPara)) = ulResult;

    (VOS_VOID)CBT_AcpuSendData(&stCbtToPcMsg, (VOS_UINT16)sizeof(CBT_UNIFORM_MSG_STRU));

    return;
}


VOS_VOID CBT_AcpuSendContentChannel(CBT_MODEM_SSID_STRU stModemSsid, CBT_COMPONENT_MODE_STRU stCompMode,
                             VOS_UINT16 usReturnPrimId, CBT_UNIFORM_MSG_STRU * pstCbtToPcMsg)
{
    CBT_UNIFORM_MSG_STRU               *pstTmpMsg;

    pstTmpMsg = (CBT_UNIFORM_MSG_STRU *)pstCbtToPcMsg;

    CBT_AcpuResetMsgHead(pstTmpMsg);
    pstTmpMsg->stMsgHeader.stModemSsid = stModemSsid;
    pstTmpMsg->usMsgId     = usReturnPrimId;
    pstTmpMsg->stCompMode  = stCompMode;

    (VOS_VOID)CBT_AcpuSendData(pstCbtToPcMsg, (VOS_UINT16)(pstCbtToPcMsg->ulMsgLength + CBT_MSG_HEAD_EX_LENGTH));
    return;
}



VOS_VOID CBT_AcpuRcvSucShow(VOS_VOID)
{
    CBT_ACPU_PC_UE_SUC_STRU              *pstPcToUeSucRecord = &(g_stAcpuCbtCtrlInfo.stPcToUeSucRecord);

    (VOS_VOID)vos_printf("\r\n *****CBT receive channel success info show *******\r\n");

    (VOS_VOID)vos_printf("Total Data Recv From PC: num:%6u, len:%6u\n",
                pstPcToUeSucRecord->stTotalData.ulNum, pstPcToUeSucRecord->stTotalData.ulDataLen);

    (VOS_VOID)vos_printf("Data after Hdlc decap:   num:%6u, len:%6u\n",
                pstPcToUeSucRecord->stHdlcDecapData.ulNum, pstPcToUeSucRecord->stHdlcDecapData.ulDataLen);

    (VOS_VOID)vos_printf("Link Data Recv From PC: num:%6u, len:%6u\n",
                pstPcToUeSucRecord->stLinkData.ulNum, pstPcToUeSucRecord->stLinkData.ulDataLen);

    (VOS_VOID)vos_printf("CCPU Data Recv From PC: num:%6u, len:%6u\n",
                pstPcToUeSucRecord->stCcpuData.ulNum, pstPcToUeSucRecord->stCcpuData.ulDataLen);

    (VOS_VOID)vos_printf("ACPU Data Recv From PC: num:%6u, len:%6u\n",
                pstPcToUeSucRecord->stAcpuData.ulNum, pstPcToUeSucRecord->stAcpuData.ulDataLen);

    (VOS_VOID)vos_printf("Data Send by ICC: num:%6u, len:%6u, slice:%6u\n",
                pstPcToUeSucRecord->stICCSendSUCInfo.ulICCOmSendMsgNum,
                pstPcToUeSucRecord->stICCSendSUCInfo.ulICCOmSendLen,
                pstPcToUeSucRecord->stICCSendSUCInfo.ulICCOmSendSlice);

    (VOS_VOID)vos_printf("Rls Data Recv From PC: num:%6u, slice:%6u\n",
                pstPcToUeSucRecord->stRlsData.ulNum, pstPcToUeSucRecord->stRlsData.ulDataLen);

    return;
}


VOS_VOID CBT_AcpuRcvErrShow(VOS_VOID)
{
    CBT_ACPU_PC_UE_FAIL_STRU             *pstPcToUeErrRecord = &(g_stAcpuCbtCtrlInfo.stPcToUeErrRecord);

    (VOS_VOID)vos_printf("\r\n *****CBT receive channel error info show *******\r\n");

    (VOS_VOID)vos_printf("Total Lost Data Recv From PC: num:%6u, len:%6u\n",
            pstPcToUeErrRecord->stLostData.ulNum, pstPcToUeErrRecord->stLostData.ulDataLen);

    (VOS_VOID)vos_printf("Number of Frame Decap Err: num:%6u\n", pstPcToUeErrRecord->ulFrameDecapErr);

    (VOS_VOID)vos_printf("Number of Packet Len Err: num:%6u\n", pstPcToUeErrRecord->usPacketLenErr);

    (VOS_VOID)vos_printf("Number of Too Short Err: num:%6u\n", pstPcToUeErrRecord->usLenTooShortErr);

    (VOS_VOID)vos_printf("Number of Seg Len Err: num:%6u\n", pstPcToUeErrRecord->usSegLenErr);

    (VOS_VOID)vos_printf("Number of Seg Num Err: num:%6u\n", pstPcToUeErrRecord->usSegNumErr);

    (VOS_VOID)vos_printf("Number of DataType Err: num:%6u\n", pstPcToUeErrRecord->usDatatypeErr);

    (VOS_VOID)vos_printf("Number of Too Long Err: num:%6u\n", pstPcToUeErrRecord->usMsgTooLongErr);

    (VOS_VOID)vos_printf("Number of Cpu Id Err: num:%6u\n", pstPcToUeErrRecord->usCpuIdErr);

    (VOS_VOID)vos_printf("Number of No Mem Err: num:%6u\n", pstPcToUeErrRecord->usNoMemErr);

    (VOS_VOID)vos_printf("Number of Data Head Err: num:%6u\n", pstPcToUeErrRecord->usDataHeadErr);

    (VOS_VOID)vos_printf("Number of Msg Len Err: num:%6u\n", pstPcToUeErrRecord->usMsgLenErr);

    (VOS_VOID)vos_printf("Number of Msg Sn Err: num:%6u\n", pstPcToUeErrRecord->usMsgSnErr);

    (VOS_VOID)vos_printf("Number of Msg TransId Err: num:%6u\n", pstPcToUeErrRecord->usTransIdErr);

    (VOS_VOID)vos_printf("Number of Packet Lost Err: num:%6u\n", pstPcToUeErrRecord->usPacketLostErr);

    (VOS_VOID)vos_printf("Number of TimeStamp Err: num:%6u\n", pstPcToUeErrRecord->usTimeStampErr);

    (VOS_VOID)vos_printf("Number of Link Data Len Err: num:%6u\n", pstPcToUeErrRecord->usLinkDataLenErr);

    (VOS_VOID)vos_printf("Number of Alloc msg Mem: num: %6u\n",pstPcToUeErrRecord->usAllocMsg);

    (VOS_VOID)vos_printf("Number of Lost Msg Because Switch Is IDLE: num: %6u\n",pstPcToUeErrRecord->usLinkStatusErr);

    (VOS_VOID)vos_printf("Data Send err by ICC: num:%6u, len:%6u, slice:%6u\n",
            pstPcToUeErrRecord->stICCSendFailInfo.ulICCOmSendErrNum,
            pstPcToUeErrRecord->stICCSendFailInfo.ulICCOmSendErrLen,
            pstPcToUeErrRecord->stICCSendFailInfo.ulICCOmSendErrSlice);

    return;
}


VOS_VOID CBT_AcpuOpenLog(VOS_UINT32 ulFlag)
{
    g_ulCbtAcpuDbgFlag = ulFlag;

    return;
}

