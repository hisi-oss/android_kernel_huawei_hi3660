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
#include "product_config.h"
#include <linux/version.h>
#include <linux/gfp.h>
#include <linux/mm.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/interrupt.h>
#include <linux/spinlock.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/vmalloc.h>
#include "socp_balong.h"
#include <linux/clk.h>
#include "bsp_version.h"
#include "bsp_dump.h"
#include "bsp_nvim.h"
#include "drv_nv_id.h"
/* log2.0 2014-03-19 Begin:*/
#include "drv_nv_def.h"
#include "bsp_trace.h"
#include "bsp_slice.h"
#include "bsp_softtimer.h"
#include "socp_ind_delay.h"
/* log2.0 2014-03-19 End*/


SOCP_GBL_STATE g_strSocpStat = {0};
EXPORT_SYMBOL(g_strSocpStat);
SOCP_DEBUG_INFO_S g_stSocpDebugInfo;
EXPORT_SYMBOL(g_stSocpDebugInfo);

 struct socp_enc_dst_log_cfg *SocpLogConfig =NULL ;
/* ?????????????? */
#define SOCP_ENCSRC_TASK_PRO    79
#define SOCP_ENCDST_TASK_PRO    81
#define SOCP_DECSRC_TASK_PRO    79
#define SOCP_DECDST_TASK_PRO    81
/* SOCP?????? */
u32 g_SocpRegBaseAddr = 0;
/* ???????????? */
u32 socp_app_int_handler(void);

spinlock_t lock;

u32 g_ulThrowout = 0;

u32 socp_version = 0;
u32 g_ulSocpDebugTraceCfg = 0;

#define SOCP_MAX_ENC_DST_COUNT      100
struct socp_enc_dst_stat_s
{
    u32 ulIntStartSlice;
    u32 ulIntEndSlice;
    u32 ulTaskStartSlice;
    u32 ulTaskEndSlice;
    u32 ulReadDoneStartSlice;
    u32 ulReadDoneEndSlice;
};
u32 g_ulEncDstStatCount;

struct socp_enc_dst_stat_s g_stEncDstStat[SOCP_MAX_ENC_DST_COUNT];

void socp_global_reset(void)
{
    SOCP_REG_SETBITS(SOCP_REG_GBLRST, 1, 1, 0x1);
}

void socp_encsrc_init(void)
{
    //enable encode head error of all channels.
    SOCP_REG_WRITE(SOCP_REG_APP_MASK1, 0);
}

void socp_global_ctrl_init(void)
{
    unsigned int i;

    /* ???????????????????? */
    /* ????ID?????? */
    g_strSocpStat.u32EncSrcTskID     = 0;
    g_strSocpStat.u32DecDstTskID     = 0;
    g_strSocpStat.u32EncDstTskID     = 0;
    g_strSocpStat.u32DecSrcTskID     = 0;
    /* ?????????????????? */
    g_strSocpStat.u32IntEncSrcHeader = 0;
    g_strSocpStat.u32IntEncSrcRD     = 0;
    g_strSocpStat.u32IntDecDstTfr    = 0;
    g_strSocpStat.u32IntDecDstOvf    = 0;
    g_strSocpStat.u32IntEncDstTfr    = 0;
    g_strSocpStat.u32IntEncDstOvf    = 0;
    g_strSocpStat.u32IntDecSrcErr    = 0;
    g_strSocpStat.compress_isr       = NULL;

    for(i=0; i<SOCP_MAX_ENCSRC_CHN; i++)
    {
        g_strSocpStat.sEncSrcChan[i].u32ChanID      = i;
        g_strSocpStat.sEncSrcChan[i].u32ChanEn      = SOCP_CHN_DISABLE;
        g_strSocpStat.sEncSrcChan[i].u32AllocStat   = SOCP_CHN_UNALLOCATED;
        g_strSocpStat.sEncSrcChan[i].u32LastRdSize  = 0;
        g_strSocpStat.sEncSrcChan[i].u32DestChanID  = 0xff;
        g_strSocpStat.sEncSrcChan[i].u32BypassEn    = 0;
        g_strSocpStat.sEncSrcChan[i].ePriority      = SOCP_CHAN_PRIORITY_3;
        g_strSocpStat.sEncSrcChan[i].eDataType      = SOCP_DATA_TYPE_BUTT;
        g_strSocpStat.sEncSrcChan[i].eDataTypeEn    = SOCP_DATA_TYPE_EN_BUTT;
        g_strSocpStat.sEncSrcChan[i].eDebugEn       = SOCP_ENC_DEBUG_EN_BUTT;
        g_strSocpStat.sEncSrcChan[i].event_cb       = BSP_NULL;
        g_strSocpStat.sEncSrcChan[i].rd_cb          = BSP_NULL;
    }

    for(i=0; i<SOCP_MAX_ENCDST_CHN; i++)
    {
        g_strSocpStat.sEncDstChan[i].u32ChanID      = i;
        g_strSocpStat.sEncDstChan[i].u32Thrh        = 0;
        g_strSocpStat.sEncDstChan[i].u32SetStat     = SOCP_CHN_UNSET;
        g_strSocpStat.sEncDstChan[i].event_cb       = BSP_NULL;
        g_strSocpStat.sEncDstChan[i].read_cb        = BSP_NULL;
        g_strSocpStat.sEncDstChan[i].eChnEvent      = (SOCP_EVENT_ENUM_UIN32)0;
        g_strSocpStat.sEncDstChan[i].struCompress.bcompress = SOCP_NO_COMPRESS;
        /* coverity[secure_coding] */
        Socp_Memset(&g_strSocpStat.sEncDstChan[i].struCompress.ops,
              0x0,sizeof(socp_compress_ops_stru));
    }

    for(i=0; i<SOCP_MAX_DECSRC_CHN; i++)
    {
        g_strSocpStat.sDecSrcChan[i].u32ChanID      = i;
        g_strSocpStat.sDecSrcChan[i].u32ChanEn      = SOCP_CHN_DISABLE;
        g_strSocpStat.sDecSrcChan[i].eDataTypeEn    = SOCP_DATA_TYPE_EN_BUTT;
        g_strSocpStat.sDecSrcChan[i].u32SetStat     = SOCP_CHN_UNSET;
        g_strSocpStat.sDecSrcChan[i].event_cb       = BSP_NULL;
        g_strSocpStat.sDecSrcChan[i].rd_cb          = BSP_NULL;
    }

    for(i=0; i<SOCP_MAX_DECDST_CHN; i++)
    {
        g_strSocpStat.sDecDstChan[i].u32ChanID      = i;
        g_strSocpStat.sDecDstChan[i].u32AllocStat   = SOCP_CHN_UNALLOCATED;
        g_strSocpStat.sDecDstChan[i].eDataType      = SOCP_DATA_TYPE_BUTT;
        g_strSocpStat.sDecDstChan[i].event_cb       = BSP_NULL;
        g_strSocpStat.sDecDstChan[i].read_cb        = BSP_NULL;
    }

    return;
}

s32 socp_clk_enable(void)
{

    return BSP_OK;
}


/*****************************************************************************
* ?? ?? ??  : socp_get_idle_buffer
*
* ????????  : ??????????????
*
* ????????  :  pRingBuffer       ????????????buffer
                    pRWBuffer         ??????????buffer
*
* ????????  : ??
*
* ?? ?? ??  :  ??
*****************************************************************************/
void socp_get_idle_buffer(SOCP_RING_BUF_S *pRingBuffer, SOCP_BUFFER_RW_STRU *pRWBuffer)
{
    	if(pRingBuffer->u32Write < pRingBuffer->u32Read)
    	{
        	/* ?????????????????????????? */
        	pRWBuffer->pBuffer = (char *)((unsigned long)pRingBuffer->u32Write);
        	pRWBuffer->u32Size = (u32)(pRingBuffer->u32Read - pRingBuffer->u32Write - 1);
        	pRWBuffer->pRbBuffer = (char *)BSP_NULL;
        	pRWBuffer->u32RbSize = 0;
    	}
    	else
    	{
        	/* ?????????????????????????????? */
        	if(pRingBuffer->u32Read != (u32)pRingBuffer->Start)
        	{
            		pRWBuffer->pBuffer = (char *)((unsigned long)pRingBuffer->u32Write);
            		pRWBuffer->u32Size = (u32)(pRingBuffer->End - pRingBuffer->u32Write + 1);
            		pRWBuffer->pRbBuffer =(char *)pRingBuffer->Start;
            		pRWBuffer->u32RbSize = (u32)(pRingBuffer->u32Read - pRingBuffer->Start - 1);
        	}
        	else
        	{
            		pRWBuffer->pBuffer = (char *)((unsigned long)pRingBuffer->u32Write);
            		pRWBuffer->u32Size = (u32)(pRingBuffer->End - pRingBuffer->u32Write);
            		pRWBuffer->pRbBuffer = (char *)BSP_NULL;
            		pRWBuffer->u32RbSize = 0;
        	}
    	}

    return;
}

/*****************************************************************************
* ?? ?? ??  : socp_get_data_buffer
*
* ????????  : ????????????????????
*
* ????????  :  pRingBuffer       ????????????buffer
                    pRWBuffer         ??????????buffer
*
* ????????  : ??
*
* ?? ?? ??  :  ??
*****************************************************************************/
void socp_get_data_buffer(SOCP_RING_BUF_S *pRingBuffer, SOCP_BUFFER_RW_STRU *pRWBuffer)
{
    if(pRingBuffer->u32Read <= pRingBuffer->u32Write)
    {
        /* ?????????????????????????? */
        pRWBuffer->pBuffer = (char *)((unsigned long)pRingBuffer->u32Read);
        pRWBuffer->u32Size = (u32)(pRingBuffer->u32Write - pRingBuffer->u32Read);
        pRWBuffer->pRbBuffer = (char *)BSP_NULL;
        pRWBuffer->u32RbSize = 0;
    }
    else
    {
        /* ?????????????????????????????? */
        pRWBuffer->pBuffer = (char *)((unsigned long)pRingBuffer->u32Read);
        pRWBuffer->u32Size = (u32)(pRingBuffer->End - pRingBuffer->u32Read + 1);
        pRWBuffer->pRbBuffer = (char *)pRingBuffer->Start;
        pRWBuffer->u32RbSize = (u32)(pRingBuffer->u32Write - pRingBuffer->Start);
    }
    return;
}

/*****************************************************************************
* ?? ?? ??  : socp_write_done
*
* ????????  : ??????????????????
*
* ????????  :  pRingBuffer       ????????????buffer
                    u32Size          ??????????????
*
* ????????  : ??
*
* ?? ?? ??  :  ??
*****************************************************************************/
void socp_write_done(SOCP_RING_BUF_S *pRingBuffer, u32 u32Size)
{
    u32 tmp_size;

    tmp_size = (u32)(pRingBuffer->End - pRingBuffer->u32Write + 1);
    if(tmp_size > u32Size)
    {
    	pRingBuffer->u32Write += u32Size;
    }
    else
    {
        u32 rb_size = u32Size - tmp_size;
        pRingBuffer->u32Write = (u32)(pRingBuffer->Start + rb_size);
    }
    return;
}
/*****************************************************************************
* ?? ?? ??  : socp_read_done
*
* ????????  : ??????????????????
*
* ????????  :  pRingBuffer       ????????????buffer
                    u32Size          ??????????????
*
* ????????  : ??
*
* ?? ?? ??  :  ??
*****************************************************************************/
void socp_read_done(SOCP_RING_BUF_S *pRingBuffer, u32 u32Size)
{
	pRingBuffer->u32Read += u32Size;
    	if(pRingBuffer->u32Read > pRingBuffer->End)
    	{
        	pRingBuffer->u32Read -= pRingBuffer->u32Length;
    	}
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_clean_encsrc_chan
*
* ????????  : ????????????????????V9 SOCP????
*
* ????????  : enSrcChanID       ??????????
*
* ????????  : ??
*
* ?? ?? ??  : BSP_OK
*****************************************************************************/
u32 bsp_socp_clean_encsrc_chan(SOCP_CODER_SRC_ENUM_U32 enSrcChanID)
{
    u32 ulResetFlag;
    u32 i;
    u32 ulChanID;
    u32 ulChanType;

    ulChanID    = SOCP_REAL_CHAN_ID(enSrcChanID);
    ulChanType  = SOCP_REAL_CHAN_TYPE(enSrcChanID);

    SOCP_CHECK_CHAN_TYPE(ulChanType, SOCP_CODER_SRC_CHAN);
    SOCP_CHECK_ENCSRC_CHAN_ID(ulChanID);

    /* ???????? */
    SOCP_REG_SETBITS(SOCP_REG_ENCRST, ulChanID, 1, 1);

    /* ???????????? */
    for(i=0; i< SOCP_RESET_TIME; i++)
    {
        ulResetFlag = SOCP_REG_GETBITS(SOCP_REG_ENCRST, ulChanID, 1);

        if(0 == ulResetFlag)
        {
            break;
        }
    }

    if(SOCP_RESET_TIME == i)
    {
        socp_printf("SocpCleanEncChan failed!\n");
    }

    return BSP_OK;
}



/***************************************************************************************
* ?? ?? ??  : socp_reset_chan_reg_wr_addr
*
* ????????  : socp??????????????????????????????????????socp32????64??????
*
* ????????  : ChanId: ??????????????????????????ID
              type: ????????????????????????????????
              Enc_pChan: ??????????????????
              Dec_pChan: ??????????????????
*
* ????????  : ??
*
* ?? ?? ??  : ??
****************************************************************************************/
void socp_reset_chan_reg_wr_addr(u32 ChanId, u32 Type, SOCP_ENCSRC_CHAN_S *Enc_pChan, SOCP_DECSRC_CHAN_S *Dec_pChan)
{    

    if(Type == SOCP_CODER_SRC_CHAN)   // ????????
    {
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFADDR(ChanId), (u32)Enc_pChan->sEncSrcBuf.Start);
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR(ChanId), (u32)Enc_pChan->sEncSrcBuf.Start);
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFRPTR(ChanId),  (u32)Enc_pChan->sEncSrcBuf.Start);
        /* ????????????*/
        g_strSocpStat.sEncSrcChan[ChanId].sEncSrcBuf.u32Read  = (u32)(Enc_pChan->sEncSrcBuf.Start);
        g_strSocpStat.sEncSrcChan[ChanId].sEncSrcBuf.u32Write = (u32)(Enc_pChan->sEncSrcBuf.Start);

        /* ??????????????????????????RDbuffer???????????????? */
        if(SOCP_ENCSRC_CHNMODE_LIST == Enc_pChan->eChnMode)
        {
            SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQADDR(ChanId), (u32)Enc_pChan->sRdBuf.Start);
            SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQRPTR(ChanId), (u32)Enc_pChan->sRdBuf.Start);
            SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQWPTR(ChanId), (u32)Enc_pChan->sRdBuf.Start);
            socp_printf("\r\nsocp_reset_enc_chan: ID is %d, addr is 0x%X.\r\n", ChanId, Enc_pChan->sRdBuf.Start);
			/*lint -save -e647*/
			SOCP_REG_SETBITS(SOCP_REG_ENCSRC_RDQCFG(ChanId), 0, 16, Enc_pChan->sRdBuf.u32Length);
            SOCP_REG_SETBITS(SOCP_REG_ENCSRC_RDQCFG(ChanId), 16, 16, 0);
			/*lint -restore +e647*/
			g_strSocpStat.sEncSrcChan[ChanId].sRdBuf.u32Read  = (u32)(Enc_pChan->sRdBuf.Start);
            g_strSocpStat.sEncSrcChan[ChanId].sRdBuf.u32Write = (u32)(Enc_pChan->sRdBuf.Start);
        }
    }
    
    else if(Type == SOCP_DECODER_SRC_CHAN)   // ????????
    {
    	/* ???????????????????? */
    	SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFADDR(ChanId), (u32)Dec_pChan->sDecSrcBuf.Start);
    	SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFWPTR(ChanId), (u32)Dec_pChan->sDecSrcBuf.Start);
    	SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFRPTR(ChanId), (u32)Dec_pChan->sDecSrcBuf.Start);
    	/* ??????????????????????*/
    	g_strSocpStat.sDecSrcChan[ChanId].sDecSrcBuf.u32Read  = (u32)(Dec_pChan->sDecSrcBuf.Start);
    	g_strSocpStat.sDecSrcChan[ChanId].sDecSrcBuf.u32Write = (u32)(Dec_pChan->sDecSrcBuf.Start);
    }
}


/*****************************************************************************
* ?? ?? ??  : socp_reset_enc_chan
*
* ????????  : ????????????
*
* ????????  : u32ChanID       ??????????
*
* ????????  : ??
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 socp_reset_enc_chan(u32 u32ChanID)
{
    u32  ResetFlag;
    u32  i;
    SOCP_ENCSRC_CHAN_S *pChan;

    pChan = &g_strSocpStat.sEncSrcChan[u32ChanID];

    /* ???????? */
    SOCP_REG_SETBITS(SOCP_REG_ENCRST, u32ChanID, 1, 1);

    /* ???????????? */
    for(i=0; i<SOCP_RESET_TIME; i++)
    {
        ResetFlag = SOCP_REG_GETBITS(SOCP_REG_ENCRST, u32ChanID, 1);
        if(0 == ResetFlag)
        {
            break;
        }

        if((SOCP_RESET_TIME -1) == i)
        {
            socp_printf("socp_reset_enc_chan 0x%x failed!\n", u32ChanID);
        }
    }

    socp_reset_chan_reg_wr_addr(u32ChanID, SOCP_CODER_SRC_CHAN, pChan, NULL);

    /*????????????*/
	/*lint -save -e647*/
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 1, 2, pChan->eChnMode);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 4, 4, pChan->u32DestChanID);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 8, 2, pChan->ePriority);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 10, 1, pChan->u32BypassEn);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 16, 8, pChan->eDataType);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 11, 1, pChan->eDataTypeEn);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 31, 1, pChan->eDebugEn);
	
    /*????????????????????????????*/
    if(pChan->u32ChanEn)
    {
        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 0, 1, 1);
    }
	/*lint -restore +e647*/
    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : socp_reset_dec_chan
*
* ????????  : ????????????
*
* ????????  : u32ChanID       ??????????
*
* ????????  : ??
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 socp_reset_dec_chan(u32 u32ChanID)
{
    u32  u32ResetFlag;
    u32  i;
    SOCP_DECSRC_CHAN_S *pChan;

    if(u32ChanID >= SOCP_MAX_DECSRC_CHN)
    {
        return BSP_ERROR;
    }

    pChan = &g_strSocpStat.sDecSrcChan[u32ChanID];

    /* ???????? */
    SOCP_REG_SETBITS(SOCP_REG_DECRST, u32ChanID, 1, 1);

    /* ???????????? */
    for(i=0; i<SOCP_RESET_TIME; i++)
    {
        u32ResetFlag = SOCP_REG_GETBITS(SOCP_REG_DECRST, u32ChanID, 1);
        if(0 == u32ResetFlag)
        {
            break;
        }
        if((SOCP_RESET_TIME -1) == i)
        {
            socp_printf("socp_reset_dec_chan 0x%x failed!\n", u32ChanID);
        }
    }

    socp_reset_chan_reg_wr_addr(u32ChanID, SOCP_DECODER_SRC_CHAN, NULL, pChan);
	/*lint -save -e647*/
    SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32ChanID), 0, 16, pChan->sDecSrcBuf.u32Length);
    SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32ChanID), 31, 1, pChan->eDataTypeEn);
    //SOCP_REG_SETBITS(SOCP_REG_DECSRC_RDQCFG(u32ChanID), 29, 1, 0);
	/*lint -restore +e647*/
    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : socp_soft_free_encdst_chan
*
* ????????  : ??????????????????
*
* ????????  : u32EncDstChanId       ??????????
*
* ????????  : ??
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 socp_soft_free_encdst_chan(u32 u32EncDstChanId)
{
    u32 u32ChanID;
    u32 u32ChanType;
    SOCP_ENCDST_CHAN_S *pChan;

    u32ChanID   = SOCP_REAL_CHAN_ID(u32EncDstChanId);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32EncDstChanId);

    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_CODER_DEST_CHAN);
    SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_ENCDST_CHN);

    pChan = &g_strSocpStat.sEncDstChan[u32ChanID];

    /* ??????????????????buffer??????????????*/
    SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFADDR(u32ChanID), (u32)pChan->sEncDstBuf.Start);
    SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFRPTR(u32ChanID), (u32)pChan->sEncDstBuf.Start);
    SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFWPTR(u32ChanID), (u32)pChan->sEncDstBuf.Start);

    g_strSocpStat.sEncDstChan[u32ChanID].sEncDstBuf.u32Write = (u32)pChan->sEncDstBuf.Start;
    g_strSocpStat.sEncDstChan[u32ChanID].sEncDstBuf.u32Read = (u32)pChan->sEncDstBuf.Start;
	
    g_strSocpStat.sEncDstChan[u32ChanID].u32SetStat = SOCP_CHN_UNSET;


    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : socp_soft_free_decsrc_chan
*
* ????????  : ????????????????
*
* ????????  : u32DecSrcChanId       ??????????
*
* ????????  : ??
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 socp_soft_free_decsrc_chan(u32 u32DecSrcChanId)
{
    u32 u32ChanID;
    u32 u32ChanType;
    SOCP_DECSRC_CHAN_S *pDecSrcChan;

    u32ChanID   = SOCP_REAL_CHAN_ID(u32DecSrcChanId);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32DecSrcChanId);

    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_SRC_CHAN);
    SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECSRC_CHN);

    pDecSrcChan = &g_strSocpStat.sDecSrcChan[u32ChanID];

    	/* ??????????????????buffer??????????????*/
   	SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFWPTR(u32ChanID), (u32)pDecSrcChan->sDecSrcBuf.Start);
    SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFADDR(u32ChanID), (u32)pDecSrcChan->sDecSrcBuf.Start);
    SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFRPTR(u32ChanID), (u32)pDecSrcChan->sDecSrcBuf.Start);

    g_strSocpStat.sDecSrcChan[u32ChanID].sDecSrcBuf.u32Write = (u32)pDecSrcChan->sDecSrcBuf.Start;
    g_strSocpStat.sDecSrcChan[u32ChanID].sDecSrcBuf.u32Read = (u32)pDecSrcChan->sDecSrcBuf.Start;
	
    g_strSocpStat.sDecSrcChan[u32ChanID].u32SetStat = SOCP_CHN_UNSET;

    return BSP_OK;
}


/*****************************************************************************
* ?? ?? ??  : socp_get_enc_rd_size
*
* ????????  :  ??????????????RDbuffer
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
u32 socp_get_enc_rd_size(u32 u32ChanID)
{
    SOCP_BUFFER_RW_STRU Buff;
    u32          PAddr;

    SOCP_REG_READ(SOCP_REG_ENCSRC_RDQRPTR(u32ChanID), PAddr);
    g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf.u32Read = PAddr;
    SOCP_REG_READ(SOCP_REG_ENCSRC_RDQWPTR(u32ChanID), PAddr);
    g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf.u32Write= PAddr;

    socp_get_data_buffer(&g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf, &Buff);
    return (Buff.u32Size + Buff.u32RbSize);
}

/*****************************************************************************
* ?? ?? ??   : socp_encsrc_rd_handler
*
* ????????  :  ??????????RDbuffer????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void socp_encsrc_rd_handler(u32 RdSize, u32 i)
{
    u32 u32ChanId;

    if (RdSize == g_strSocpStat.sEncSrcChan[i].u32LastRdSize)
    {
        if (g_strSocpStat.sEncSrcChan[i].rd_cb)
        {
            u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN, i);
            (void)g_strSocpStat.sEncSrcChan[i].rd_cb(u32ChanId);

            g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpEncSrcTskRdCbCnt[i]++;
        }

        g_strSocpStat.sEncSrcChan[i].u32LastRdSize = 0;
    }
    else
    {
        g_strSocpStat.sEncSrcChan[i].u32LastRdSize = RdSize;
    }

    return;
}

/*****************************************************************************
* ?? ?? ??  : socp_encsrc_task
*
* ????????  : ????????????:????????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
int socp_encsrc_task(void * data)
{
    u32 i;
    u32 IntHeadState = 0;
    u32 u32ChanId;
    unsigned long lock_flag;
    u32 head_err = 0;
    /* coverity[no_escape] */
    do{
        /* ?????????????????????????? */
        if(0 != down_interruptible(&g_strSocpStat.u32EncSrcSemID))
        {
            continue;
        }

        spin_lock_irqsave(&lock, lock_flag);
        IntHeadState = g_strSocpStat.u32IntEncSrcHeader;
        g_strSocpStat.u32IntEncSrcHeader = 0;
        g_strSocpStat.u32IntEncSrcRD = 0;
        spin_unlock_irqrestore(&lock, lock_flag);

        /* ????????????'HISI'????????*/
        if (IntHeadState)
        {
            for (i = 0; i < SOCP_MAX_ENCSRC_CHN; i++)
            {
                /* ????????????????*/
                if (SOCP_CHN_ALLOCATED == g_strSocpStat.sEncSrcChan[i].u32AllocStat)
                {
                    if (IntHeadState & ((u32)1 << i))
                    {
                        if (g_strSocpStat.sEncSrcChan[i].event_cb)
                        {
                            g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpEncSrcTskHeadCbOriCnt[i]++;
                            u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN, i);
                            socp_printf("\r\nsocp_encsrc_task: packet header Error Channel is %d\r\n", u32ChanId);
                            (void)g_strSocpStat.sEncSrcChan[i].event_cb(u32ChanId, SOCP_EVENT_PKT_HEADER_ERROR, 0);
                            g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpEncSrcTskHeadCbCnt[i]++;
                            socp_printf("head err: %d\n", head_err);
                            head_err++;
                        }
                    }
                }
            }
        }
    } while (1);

    //return BSP_OK;
}

#define TIMEOUT_30S       (32764*30)
/*****************************************************************************
* ?? ?? ??  : socp_encdst_task
*
* ????????  : ????????????:??????????App??
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
int socp_encdst_task(void * data)
{
    u32 i;
    u32 IntTfrState = 0;
    u32 IntOvfState = 0;
    u32 IntThresholdOvfState = 0;
    u32 u32ChanId =0 ;
    unsigned long lock_flag;
    u32 read;
    u32 write;
    u64 SliceOld = 0;
    u64 SliceNow;
    u32 DbgReg;

    /* coverity[no_escape] */
    do{
        /* ?????????????????????????? */
        if(0 != down_interruptible(&g_strSocpStat.u32EncDstSemID))
        {
            continue;
        }

        spin_lock_irqsave(&lock, lock_flag);
        IntTfrState = g_strSocpStat.u32IntEncDstTfr;
        g_strSocpStat.u32IntEncDstTfr = 0;
        IntOvfState = g_strSocpStat.u32IntEncDstOvf;
        g_strSocpStat.u32IntEncDstOvf = 0;
        IntThresholdOvfState = g_strSocpStat.u32IntEncDstThresholdOvf;
        g_strSocpStat.u32IntEncDstThresholdOvf = 0;
        spin_unlock_irqrestore(&lock, lock_flag);

        /* ????????????????????*/
        if (IntTfrState)
        {
            for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
            {
                /* ????????????????*/
                if (SOCP_CHN_SET == g_strSocpStat.sEncDstChan[i].u32SetStat)
                {
                    if (IntTfrState & ((u32)1 << i))
                    {
                        if (g_strSocpStat.sEncDstChan[i].read_cb)
                        {
                            /*lint -save -e732*/
                            SOCP_REG_READ(SOCP_REG_ENCDEST_BUFRPTR(i), read);
                            SOCP_REG_READ(SOCP_REG_ENCDEST_BUFWPTR(i), write);
                            /*lint -restore +e732*/
                            SOCP_DEBUG_TRACE(SOCP_DEBUG_READ_DONE, read, write, 0, 0);
                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskTrfCbOriCnt[i]++;
                            u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, i);
                            if(i == 1){
                                g_stEncDstStat[g_ulEncDstStatCount].ulTaskStartSlice = bsp_get_slice_value();
                            }
                            (void)g_strSocpStat.sEncDstChan[i].read_cb(u32ChanId);
                            if(i == 1){
                                g_stEncDstStat[g_ulEncDstStatCount].ulTaskEndSlice = bsp_get_slice_value();
                                (void)bsp_slice_getcurtime(&SliceNow);
                                if((SliceNow - SliceOld) > TIMEOUT_30S)
                                {
                                    SOCP_REG_READ(HI_SOCP_ENC_IBUF_DBG1_OFFSET, DbgReg);
                                    socp_printf("DBG REG: 0x%x\n", DbgReg);
                                    SliceOld = SliceNow;
                                }
                            }

                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskTrfCbCnt[i]++;
                        }
                    }
                }
            }
        }

        /* ???????????? buffer ????????*/
        if (IntOvfState)
        {
            for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
            {
                /* ????????????????*/
                if (SOCP_CHN_SET == g_strSocpStat.sEncDstChan[i].u32SetStat)
                {
                    if (IntOvfState & ((u32)1 << i))
                    {
                        if (g_strSocpStat.sEncDstChan[i].event_cb)
                        {
                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskOvfCbOriCnt[i]++;
                            u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, i);
                            (void)g_strSocpStat.sEncDstChan[i].event_cb(u32ChanId, SOCP_EVENT_OUTBUFFER_OVERFLOW, 0);

                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskOvfCbCnt[i]++;
                        }
                        if (g_strSocpStat.sEncDstChan[i].read_cb)
                        {
                            /*lint -save -e732*/
                            SOCP_REG_READ(SOCP_REG_ENCDEST_BUFRPTR(i), read);
                            SOCP_REG_READ(SOCP_REG_ENCDEST_BUFWPTR(i), write);
                            /*lint -restore +e732*/
                            SOCP_DEBUG_TRACE(SOCP_DEBUG_READ_DONE, read, write, 0, 0);
                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskTrfCbOriCnt[i]++;
                            u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, i);
                            (void)g_strSocpStat.sEncDstChan[i].read_cb(u32ChanId);

                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskTrfCbCnt[i]++;
                            SOCP_REG_READ(HI_SOCP_ENC_IBUF_DBG1_OFFSET, DbgReg);
                            socp_printf("Dst buffer Ovf, DBG REG: 0x%x\n", DbgReg);
                        }
                    }
                }
            }
        }

        /* ???????????? buffer ????????????*/
        if (IntThresholdOvfState)
        {
            for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
            {
                /* ????????????????*/
                if (SOCP_CHN_SET == g_strSocpStat.sEncDstChan[i].u32SetStat)
                {
                    if (IntThresholdOvfState & ((u32)1 << (i + SOCP_ENC_DST_BUFF_THRESHOLD_OVF_BEGIN)))
                    {
                        if (g_strSocpStat.sEncDstChan[i].event_cb)
                        {
                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskOvfCbOriCnt[i]++;
                            u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, i);
                            (void)g_strSocpStat.sEncDstChan[i].event_cb(u32ChanId, SOCP_EVENT_OUTBUFFER_OVERFLOW, 0);

                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskOvfCbCnt[i]++;
                        }
                        if (g_strSocpStat.sEncDstChan[i].read_cb)
                        {
                            /*lint -save -e732*/
                            SOCP_REG_READ(SOCP_REG_ENCDEST_BUFRPTR(i), read);
                            SOCP_REG_READ(SOCP_REG_ENCDEST_BUFWPTR(i), write);
                            /*lint -restore +e732*/
                            SOCP_DEBUG_TRACE(SOCP_DEBUG_READ_DONE, read, write, 0, 0);
                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskTrfCbOriCnt[i]++;
                            u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, i);
                            (void)g_strSocpStat.sEncDstChan[i].read_cb(u32ChanId);

                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskTrfCbCnt[i]++;
                            SOCP_REG_READ(HI_SOCP_ENC_IBUF_DBG1_OFFSET, DbgReg);
                            socp_printf("Threashold Ovf, DBG REG: 0x%x\n", DbgReg);
                        }
                    }
                }
            }
        }

    } while (1);

    //return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : socp_decsrc_event_handler
*
* ????????  : ??????????????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void  socp_decsrc_event_handler(u32 id, u32 secIntState)
{
    u32 u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN, id);

    if (g_strSocpStat.sDecSrcChan[id].event_cb)
    {
        if (secIntState & 0x10)
        {
            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbOriCnt[id]++;

            (void)g_strSocpStat.sDecSrcChan[id].event_cb(u32ChanId, SOCP_EVENT_DECODER_UNDERFLOW, 0);

            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbCnt[id]++;
        }

        if (secIntState & 0x100)
        {
            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbOriCnt[id]++;

            (void)g_strSocpStat.sDecSrcChan[id].event_cb(u32ChanId, SOCP_EVENT_HDLC_HEADER_ERROR, 0);

            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbCnt[id]++;
        }

        if (secIntState & 0x1000)
        {
            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbOriCnt[id]++;

            (void)g_strSocpStat.sDecSrcChan[id].event_cb(u32ChanId, SOCP_EVENT_DATA_TYPE_ERROR, 0);

            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbCnt[id]++;
        }

        if (secIntState & 0x10000)
        {
            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbOriCnt[id]++;

            (void)g_strSocpStat.sDecSrcChan[id].event_cb(u32ChanId, SOCP_EVENT_CRC_ERROR, 0);

            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbCnt[id]++;
        }

        if (secIntState & 0x100000)
        {
            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbOriCnt[id]++;

            (void)g_strSocpStat.sDecSrcChan[id].event_cb(u32ChanId, SOCP_EVENT_PKT_LENGTH_ERROR, 0);

            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbCnt[id]++;
        }
    }
}

/*****************************************************************************
* ?? ?? ??  : socp_decsrc_handler
*
* ????????  : ??????????????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void  socp_decsrc_handler(void)
{
    u32 IntState, secIntState;
    u32 u32ChanId;
    u32 i;

    if(g_strSocpStat.u32IntDecSrcErr)
    {
        IntState = g_strSocpStat.u32IntDecSrcErr;
        g_strSocpStat.u32IntDecSrcErr = 0;

        for(i=0;i<SOCP_MAX_DECSRC_CHN;i++)
        {
            /* ????????????????*/

            if(SOCP_CHN_SET == g_strSocpStat.sDecSrcChan[i].u32SetStat)
            {
                secIntState = IntState>>i;
                u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN, i);

                if(g_strSocpStat.sDecSrcChan[i].rd_cb)
                {
                    if(secIntState & 0x1)
                    {
                        (void)g_strSocpStat.sDecSrcChan[i].rd_cb(u32ChanId);
                    }
                }

                socp_decsrc_event_handler(i, secIntState);
            }
        }
    }
}

/*****************************************************************************
* ?? ?? ??  : socp_decsrc_task
*
* ????????  : ????????????:????????A??
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
int socp_decsrc_task(void * data)
{
    unsigned long lock_flag;
    /* coverity[no_escape] */
    do{
        /* ?????????????????????????? */
        if(0 != down_interruptible(&g_strSocpStat.u32DecSrcSemID))
        {
            continue;
        }
        spin_lock_irqsave(&lock, lock_flag);
        /* ??????????????*/
        socp_decsrc_handler();
        spin_unlock_irqrestore(&lock, lock_flag);
    }while(1);

    //return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : socp_decdst_task
*
* ????????  : ????????????:??????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
int socp_decdst_task(void * data)
{
    u32 i;
    u32 IntTfrState = 0;
    u32 IntOvfState = 0;
    u32 u32ChanId;
    unsigned long lock_flag;
    /* coverity[no_escape] */
    do{
        /* ?????????????????????????? */
        if(0 != down_interruptible(&g_strSocpStat.u32DecDstSemID))
        {
            continue;
        }

        spin_lock_irqsave(&lock, lock_flag);
        IntTfrState = g_strSocpStat.u32IntDecDstTfr;
        g_strSocpStat.u32IntDecDstTfr = 0;
        IntOvfState = g_strSocpStat.u32IntDecDstOvf;
        g_strSocpStat.u32IntDecDstOvf = 0;
        spin_unlock_irqrestore(&lock, lock_flag);

        /* ????????????????????*/
        if (IntTfrState)
        {
            for (i = 0; i < SOCP_MAX_DECDST_CHN; i++)
            {
                /* ????????????????*/
                if (SOCP_CHN_ALLOCATED == g_strSocpStat.sDecDstChan[i].u32AllocStat)
                {
                    if (IntTfrState & ((u32)1 << i))
                    {
                        if (g_strSocpStat.sDecDstChan[i].read_cb)
                        {
                            g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpDecDstTskTrfCbOriCnt[i]++;

                            u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, i);
                            (void)g_strSocpStat.sDecDstChan[i].read_cb(u32ChanId);

                            g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpDecDstTskTrfCbCnt[i]++;
                        }
                    }
                }
            }
        }

        /* ???????????? buffer ????????*/
        if (IntOvfState)
        {
            for (i = 0; i < SOCP_MAX_DECDST_CHN; i++)
            {
                /* ????????????????*/
                if (SOCP_CHN_ALLOCATED == g_strSocpStat.sDecDstChan[i].u32AllocStat)
                {
                    if (IntOvfState & ((u32)1 << i))
                    {
                        if (g_strSocpStat.sDecDstChan[i].event_cb)
                        {
                            g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpDecDstTskOvfCbOriCnt[i]++;

                            u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, i);
                            socp_printf("\r\nsocp_decdst_task: Call Event Cb, Channel is %d",u32ChanId);
                            (void)g_strSocpStat.sDecDstChan[i].event_cb(u32ChanId, SOCP_EVENT_OUTBUFFER_OVERFLOW, 0);

                            g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpDecDstTskOvfCbCnt[i]++;
                        }
                    }
                }
            }
        }
    } while (1);

    //return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : socp_create_task
*
* ????????  : socp????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 socp_create_task( s8 * puchName,
                        unsigned long * pu32TaskID,
                        socp_task_entry pfnFunc,
                        u32 u32Priority,
                        u32 u32StackSize,
                        void * pParam)
{
    struct task_struct  *tsk;
    struct sched_param  param;

    tsk = kthread_run(pfnFunc, pParam, puchName);
    if (IS_ERR(tsk))
    {
        socp_printf("socp_create_task: create kthread failed!\n");
        return BSP_ERROR;
    }

    param.sched_priority = u32Priority;
    if (BSP_OK != sched_setscheduler(tsk, SCHED_FIFO, &param))
    {
        socp_printf("\nsocp_create_task: Creat Task %s ID %p sched_setscheduler Error", puchName, pu32TaskID);
        return BSP_ERROR;
    }

    *pu32TaskID = (unsigned long)tsk;

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : socp_init_task
*
* ????????  : ??????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 socp_init_task(void)
{
    u32 aulArguments[4] = {0,0,0,0};

    /* ??????????????*/
    sema_init(&g_strSocpStat.u32EncSrcSemID, 0);
    if(!g_strSocpStat.u32EncSrcTskID)
    {
        if ( BSP_OK != socp_create_task( "EncSrc", (unsigned long *)&g_strSocpStat.u32EncSrcTskID, (socp_task_entry)socp_encsrc_task,
                            SOCP_ENCSRC_TASK_PRO, 0x1000, aulArguments) )
        {
            socp_printf("socp_init_task: create socp_encsrc_task failed.\n");
            return BSP_ERR_SOCP_TSK_CREATE;
        }
    }

    /* ????????????????*/
    sema_init(&g_strSocpStat.u32EncDstSemID, 0);
    if(!g_strSocpStat.u32EncDstTskID)
    {
        if ( BSP_OK != socp_create_task( "EncDst", (unsigned long *)&g_strSocpStat.u32EncDstTskID, (socp_task_entry)socp_encdst_task,
                            SOCP_ENCDST_TASK_PRO, 0x1000, aulArguments) )
        {
            socp_printf("socp_init_task: create socp_encdst_task failed.\n");
            return BSP_ERR_SOCP_TSK_CREATE;
        }
    }

    /* ??????????????*/
    sema_init(&g_strSocpStat.u32DecSrcSemID, 0);
    if(!g_strSocpStat.u32DecSrcTskID)
    {
        if ( BSP_OK != socp_create_task( "DecSrc", (unsigned long *)&g_strSocpStat.u32DecSrcTskID, (socp_task_entry)socp_decsrc_task,
                            SOCP_DECSRC_TASK_PRO, 0x1000, aulArguments) )
        {
            socp_printf("socp_init_task: create u32DecSrcTskID failed.\n");
            return BSP_ERR_SOCP_TSK_CREATE;
        }
    }

    /* ????????????????*/
    sema_init(&g_strSocpStat.u32DecDstSemID, 0);
    if(!g_strSocpStat.u32DecDstTskID)
    {
        if ( BSP_OK != socp_create_task( "DecDst", (unsigned long *)&g_strSocpStat.u32DecDstTskID, (socp_task_entry)socp_decdst_task,
                            SOCP_DECDST_TASK_PRO, 0x1000, aulArguments) )
        {
            socp_printf("socp_init_task: create u32DecDstTskID failed.\n");
            return BSP_ERR_SOCP_TSK_CREATE;
        }
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??   : socp_handler_encsrc
*
* ????????  : ????????????????????RD????????????????????RD????????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void  socp_handler_encsrc(void)
{
    u32 IntFlag   = 0;
    u32 IntState  = 0;
    int bHandle  = BSP_FALSE;
    u32 i = 0;

    /*read and clear the interrupt flags*/
    SOCP_REG_READ(SOCP_REG_GBL_INTSTAT, IntFlag);
    /* ???????????? */
    if (IntFlag & SOCP_APP_ENC_FLAGINT_MASK)
    {
        socp_printf("IntFlag = 0x%x\n", IntFlag);
        SOCP_REG_READ(SOCP_REG_APP_INTSTAT1, IntState);
        SOCP_REG_WRITE(SOCP_REG_ENC_RAWINT1, IntState);

        g_strSocpStat.u32IntEncSrcHeader |= IntState;
        bHandle = BSP_TRUE;

        for (i = 0; i < SOCP_MAX_ENCSRC_CHN; i++)
        {
            if (IntState & ((u32)1 << i))
            {
                /* debug???????????????????? */
                if(SOCP_REG_GETBITS(SOCP_REG_ENCSRC_BUFCFG1(i), 31, 1))/*lint !e647*/
                {
                    SOCP_REG_SETBITS(SOCP_REG_APP_MASK1, i, 1,1);
                }
                g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpEncSrcIsrHeadIntCnt[i]++;
                socp_printf("EncSrcHeaderError ChanId = %d",i);
            }
        }
    }

    /*????????RD?????????????????????????? */

    if(bHandle)
    {
        up(&g_strSocpStat.u32EncSrcSemID);
    }

    return ;
}


/*****************************************************************************
* ?? ?? ??   : socp_handler_encdst
*
* ????????  : ????????????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
/*lint -save -e550*/
void socp_handler_encdst(void)
{
    u32  IntFlag = 0;
    u32  IntState = 0;
    int  bHandle = BSP_FALSE;
    u32  i;
    u32  mask;
    u32  mask2;
    u32  write;

    unsigned long lock_flag;
    int countFlag = BSP_FALSE;
    u32  ModeState = 0;

    /*????????????????*/
    SOCP_REG_READ(SOCP_REG_GBL_INTSTAT, IntFlag);
    if (IntFlag & SOCP_APP_ENC_TFRINT_MASK)
    {
        spin_lock_irqsave(&lock, lock_flag);
        SOCP_REG_READ(SOCP_REG_ENC_INTSTAT0, IntState);
        SOCP_REG_READ(SOCP_REG_ENC_MASK0, mask);
        SOCP_REG_WRITE(SOCP_REG_ENC_MASK0, (IntState | mask));   // mask int 2011.7.27 by yangzhi
        /* ???????????? */
        SOCP_REG_READ(SOCP_REG_ENC_MASK2, mask2);
        SOCP_REG_WRITE(SOCP_REG_ENC_MASK2, ((IntState << 16) | mask2));
        SOCP_REG_WRITE(SOCP_REG_ENC_RAWINT0, IntState);

        g_strSocpStat.u32IntEncDstTfr |= IntState;
        spin_unlock_irqrestore(&lock, lock_flag);
        bHandle = BSP_TRUE;

        for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
        {
            if (IntState & ((u32)1 << i))
            {
                if(g_ulThrowout == 0x5a5a5a5a)
                {
                    spin_lock_irqsave(&lock, lock_flag);
                    SOCP_REG_READ(SOCP_REG_ENCDEST_BUFWPTR(i), write);
                    SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFRPTR(i), write);
                    SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT0, i, 1, 1);
                    SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, i, 1, 0);
                    /* overflow int */
                    SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT2, i + 16, 1, 1);
                    SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, i + 16, 1, 0);
                    spin_unlock_irqrestore(&lock, lock_flag);

                    bHandle = BSP_FALSE;
                }
                if(i == 1)
                {
                    g_stEncDstStat[g_ulEncDstStatCount].ulIntStartSlice = bsp_get_slice_value();
                    countFlag = BSP_TRUE;
                }
                g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstIsrTrfIntCnt[i]++;
            }
        }
    }
    // ????????????????????????????????
    else if (IntFlag & SOCP_APP_ENC_OUTOVFINT_MASK)
    {
        SOCP_REG_READ(SOCP_REG_ENC_INTSTAT2, IntState);
        // ????????buffer????????????
        if(0 != (IntState & SOCP_ENC_DST_BUFF_THRESHOLD_OVF_MASK))
        {
            spin_lock_irqsave(&lock, lock_flag);
            SOCP_REG_READ(SOCP_REG_ENC_MASK2, mask);
            SOCP_REG_WRITE(SOCP_REG_ENC_MASK2, (IntState | mask));
            SOCP_REG_WRITE(SOCP_REG_ENC_RAWINT2, IntState);
            g_strSocpStat.u32IntEncDstThresholdOvf |= IntState;
            spin_unlock_irqrestore(&lock, lock_flag);

            bHandle = BSP_TRUE;

            for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
            {
                if (IntState & ((u32)1 << (i + SOCP_ENC_DST_BUFF_THRESHOLD_OVF_BEGIN)))
                {
                    g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstIsrThresholdOvfIntCnt[i]++;
                }
            }

        }
        // ????????buffer????????
        if (0 != (IntState & SOCP_ENC_DST_BUFF_OVF_MASK))
        {
            spin_lock_irqsave(&lock, lock_flag);
            SOCP_REG_READ(SOCP_REG_ENC_MASK2, mask);
            SOCP_REG_WRITE(SOCP_REG_ENC_MASK2, (IntState | mask));
            SOCP_REG_WRITE(SOCP_REG_ENC_RAWINT2, IntState);
            g_strSocpStat.u32IntEncDstOvf |= IntState;
            spin_unlock_irqrestore(&lock, lock_flag);

            bHandle = BSP_TRUE;

            for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
            {
                if (IntState & ((u32)1 << i))
                {
                    g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstIsrOvfIntCnt[i]++;
                }
            }
        }
    }
    else if(g_strSocpStat.compress_isr)
    {
        g_strSocpStat.compress_isr();
        return ;
    }

    /* ????????buffer???????????? */
    else if (IntFlag & SOCP_CORE0_ENC_MODESWT_MASK)
    {
        spin_lock_irqsave(&lock, lock_flag);

        SOCP_REG_READ(SOCP_REG_ENC_INTSTAT0, IntState);
        SOCP_REG_READ(SOCP_REG_ENC_MASK0, mask);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, 16, 7, (((IntState | mask)>>16)&0x7f));

        /* ?????????????? */
        SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT0, 16, 7, ((IntState>>16)&0x7f));

        mask = 0;
        for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
        {
            	SOCP_REG_READ(SOCP_REG_ENCDEST_SBCFG(i), ModeState);
            	if(ModeState & 0x02)
            	{
               	 	mask |= (1<<i);
            	}
        }

        /* ???????????????????????????????????????????? */
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, 0, 7, mask);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, 0, 7, mask);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, 16, 7, mask);

        spin_unlock_irqrestore(&lock, lock_flag);
    }
    else
    {
        bHandle = BSP_FALSE;
    }

    if(bHandle)
    {
        if(countFlag == BSP_TRUE){
            g_stEncDstStat[g_ulEncDstStatCount].ulIntEndSlice= bsp_get_slice_value();
        }
        up(&g_strSocpStat.u32EncDstSemID);
    }

    return ;
}
/*lint -restore +e550*/

/*****************************************************************************
* ?? ?? ??   : socp_handler_decsrc
*
* ????????  : ??????????????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void socp_handler_decsrc(void)
{
    u32 IntFlag  = 0;
    u32 IntState = 0;
    int bHandle = BSP_FALSE;
    u32 i = 0;

    /*????????????*/
    SOCP_REG_READ(SOCP_REG_GBL_INTSTAT, IntFlag);
    if (IntFlag & SOCP_DEC_INERRINT_MASK)
    {
        SOCP_REG_READ(SOCP_REG_DEC_INTSTAT1, IntState);
        SOCP_REG_WRITE(SOCP_REG_DEC_RAWINT1, IntState);

        g_strSocpStat.u32IntDecSrcErr |= IntState;
        bHandle = BSP_TRUE;

        for (i = 0; i < SOCP_MAX_DECSRC_CHN; i++)
        {
            if (IntState & 0x1)
            {
                g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcIsrErrIntCnt[i]++;
            }
        }
    }

    if(bHandle)
    {
        up(&g_strSocpStat.u32DecSrcSemID);
    }

    return;
}


/*****************************************************************************
* ?? ?? ??   : socp_handler_decdst
*
* ????????  : ????????????????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/

void socp_handler_decdst(void)
{
    u32 IntFlag  = 0;
    u32 IntState = 0;
    int bHandle = BSP_FALSE;
    u32 TfMask  ;
    u32 TfState ;
    u32 OvMask   ;
    u32 OvState   ;
    u32 TfMaskReg ;
    u32 i = 0;

    TfMask    = SOCP_CORE0_DEC_TFRINT_MASK;
    TfState   = SOCP_REG_DEC_CORE0ISTAT0;
    TfMaskReg = SOCP_REG_DEC_CORE0MASK0;
    OvMask  = SOCP_CORE0_DEC_OUTOVFINT_MASK;
    OvState = SOCP_REG_DEC_CORE0ISTAT2;

    /*????????????*/
    SOCP_REG_READ(SOCP_REG_GBL_INTSTAT, IntFlag);
    if (IntFlag & TfMask)
    {
        u32 mask;
        SOCP_REG_READ(TfState, IntState);
        IntState = IntState & 0xffff;
        SOCP_REG_READ(TfMaskReg, mask);
        SOCP_REG_WRITE(TfMaskReg, (IntState | mask));  //added by yangzhi 2011.7.27
        SOCP_REG_WRITE(SOCP_REG_DEC_RAWINT0, IntState);

        g_strSocpStat.u32IntDecDstTfr |= IntState;
        bHandle = BSP_TRUE;

        for (i = 0; i < SOCP_MAX_DECDST_CHN; i++)
        {
            if (IntState & ((u32)1 << i))
            {
                g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpDecDstIsrTrfIntCnt[i]++;
            }
        }
    }

    /*????????buffer ????*/
    SOCP_REG_READ(SOCP_REG_GBL_INTSTAT, IntFlag);
    if (IntFlag & OvMask)
    {
        SOCP_REG_READ(OvState, IntState);
        IntState = IntState & 0xffff;
        SOCP_REG_WRITE(SOCP_REG_DEC_RAWINT2, IntState);

        g_strSocpStat.u32IntDecDstOvf |= IntState;
        bHandle = BSP_TRUE;

        for (i = 0; i < SOCP_MAX_DECDST_CHN; i++)
        {
            if (IntState & ((u32)1 << i))
            {
                g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpDecDstIsrOvfIntCnt[i]++;
            }
        }
    }

    if(bHandle)
    {
        up(&g_strSocpStat.u32DecDstSemID);
    }

    return;
}


/*****************************************************************************
* ?? ?? ??   : socp_app_int_handler
*
* ????????  : APP ??????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
u32 socp_app_int_handler(void)
{
    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpAppEtrIntCnt++;

    socp_handler_encsrc();

    socp_handler_encdst();
    socp_handler_decsrc();
    socp_handler_decdst();

    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpAppSucIntCnt++;

    return 1;
}

/*****************************************************************************
* ?? ?? ??  : socp_init
*
* ????????  : ??????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : ??????????????????
*****************************************************************************/
s32 socp_init(void)
{
    s32 ret;
    u32 irq;

    struct device_node* dev = NULL;

    if(BSP_TRUE == g_strSocpStat.bInitFlag)
    {
        return BSP_OK;
    }

    spin_lock_init(&lock);

    /*Add dts begin*/
    dev = of_find_compatible_node(NULL,NULL,"hisilicon,socp_balong_app");
    if(NULL == dev)
    {
        socp_printf("socp_init: Socp dev find failed\n");
        return BSP_ERROR;
    }
    /*Add dts end*/

    g_strSocpStat.baseAddr = (unsigned long)of_iomap(dev,0);
    if(0 == g_strSocpStat.baseAddr)
    {
        socp_printf("socp_init:base addr is error!\n");
        return BSP_ERROR; /* [false alarm]:????Fortify???? */
    }

    /* bsp_memmap.h????????????BBP???????????????? */
    g_strSocpStat.armBaseAddr = (unsigned long)BBP_REG_ARM_BASEADDR;
    /* coverity[secure_coding] */
    Socp_Memset(&g_stSocpDebugInfo, 0x0 ,sizeof(SOCP_DEBUG_INFO_S));

    SOCP_REG_READ(SOCP_REG_SOCP_VERSION, socp_version);

    socp_global_ctrl_init();

    ret = socp_clk_enable();
    if(ret)
    {
        return ret;
    }

    socp_global_reset();

    bsp_socp_ind_delay_init();

    /* ?????????????? */
    ret = socp_init_task();
    if (BSP_OK != ret)
    {
        socp_printf("socp_init: create task failed(0x%x).\n", ret);
        return (s32)ret;
    }

    /* ?????? */
    irq = irq_of_parse_and_map(dev,0);
    ret = request_irq(irq, (irq_handler_t)socp_app_int_handler, 0, "SOCP_APP_IRQ",  BSP_NULL);
    if (BSP_OK != ret)
    {
        socp_printf("socp_init: connect app core int failed.\n");
        return BSP_ERROR;
    }


    /* ?????????????? */
    g_strSocpStat.bInitFlag = BSP_TRUE;

    (void)bsp_socp_dst_init();

    socp_encsrc_init();

    socp_printf("[socp_init]: succeed, base addr=0x%p, irq num:%d !\n",(void*)(g_strSocpStat.baseAddr),irq);

    return BSP_OK;
}


/***************************************************************************************
* ?? ?? ??  : socp_set_reg_wr_addr
*
* ????????  : ????????????????????????????????????????????????SOCP32????64??????????
*
* ????????  : ChanId: ??????????????????????????ID
*             pAttr: ????????????
              start: ????buffer????????
              end: ????buffer????????
*
* ????????  : ??
*
* ?? ?? ??  : ??
****************************************************************************************/
void socp_set_reg_wr_addr(u32 ChanId, void *pAttr, unsigned long start, unsigned long end)
{
    u32 RealChanId = 0;
    u32 ChanType = 0;
    unsigned long rdstart = 0;
    unsigned long rdend = 0;
    SOCP_ENCSRC_CHAN_S *pEncSrcChan = NULL;
    SOCP_ENCDST_CHAN_S *pEncDstChan = NULL;
    SOCP_DECSRC_CHAN_S *pDecSrcChan = NULL;
    SOCP_DECDST_CHAN_S *pDecDstChan = NULL;

    RealChanId = SOCP_REAL_CHAN_ID(ChanId);
    ChanType  = SOCP_REAL_CHAN_TYPE(ChanId);
    

    if(ChanType == SOCP_CODER_SRC_CHAN)   // ??????????
    {
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFADDR(RealChanId),(u32)start);
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR(RealChanId),(u32)start);
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFRPTR(RealChanId), (u32)start);
        if(SOCP_ENCSRC_CHNMODE_LIST == ((SOCP_CODER_SRC_CHAN_S *)pAttr)->eMode)
        {
            rdstart = (unsigned long)((SOCP_CODER_SRC_CHAN_S *)pAttr)->sCoderSetSrcBuf.pucRDStart;
            rdend   = (unsigned long)((SOCP_CODER_SRC_CHAN_S *)pAttr)->sCoderSetSrcBuf.pucRDEnd;
    		SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQADDR(RealChanId), (u32)rdstart);
            SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQRPTR(RealChanId), (u32)rdstart);
            SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQWPTR(RealChanId), (u32)rdstart);       
        }
        pEncSrcChan = &g_strSocpStat.sEncSrcChan[RealChanId];
        pEncSrcChan->eChnMode               = ((SOCP_CODER_SRC_CHAN_S *)pAttr)->eMode;
        pEncSrcChan->ePriority              = ((SOCP_CODER_SRC_CHAN_S *)pAttr)->ePriority;
        pEncSrcChan->eDataType              = ((SOCP_CODER_SRC_CHAN_S *)pAttr)->eDataType;
        pEncSrcChan->eDataTypeEn            = ((SOCP_CODER_SRC_CHAN_S *)pAttr)->eDataTypeEn;
        pEncSrcChan->eDebugEn               = ((SOCP_CODER_SRC_CHAN_S *)pAttr)->eDebugEn;
        pEncSrcChan->u32DestChanID          = ((SOCP_CODER_SRC_CHAN_S *)pAttr)->u32DestChanID;
        pEncSrcChan->u32BypassEn            = ((SOCP_CODER_SRC_CHAN_S *)pAttr)->u32BypassEn;
        pEncSrcChan->sEncSrcBuf.Start    = start;
        pEncSrcChan->sEncSrcBuf.End      = end;
        pEncSrcChan->sEncSrcBuf.u32Write    = start;
        pEncSrcChan->sEncSrcBuf.u32Read     = start;
        pEncSrcChan->sEncSrcBuf.u32Length   = end - start + 1;//lint !e834
        pEncSrcChan->sEncSrcBuf.u32IdleSize = 0;

        if(SOCP_ENCSRC_CHNMODE_LIST == ((SOCP_CODER_SRC_CHAN_S *)pAttr)->eMode)
        {
            pEncSrcChan->sRdBuf.Start    = rdstart;
            pEncSrcChan->sRdBuf.End      = rdend;
            pEncSrcChan->sRdBuf.u32Write    = rdstart;
            pEncSrcChan->sRdBuf.u32Read     = rdstart;
    	    pEncSrcChan->sRdBuf.u32Length   = rdend - rdstart + 1;//lint !e834
            pEncSrcChan->u32RdThreshold     = ((SOCP_CODER_SRC_CHAN_S *)pAttr)->sCoderSetSrcBuf.u32RDThreshold;
        }
    }
    
    else if(ChanType == SOCP_CODER_DEST_CHAN)   // ????????????
    {
        SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFADDR(RealChanId), (u32)start);
        SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFRPTR(RealChanId), (u32)start);
        SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFWPTR(RealChanId), (u32)start);

        pEncDstChan = &g_strSocpStat.sEncDstChan[RealChanId];
        pEncDstChan->sEncDstBuf.Start    = start;
        pEncDstChan->sEncDstBuf.End      = end;
        pEncDstChan->sEncDstBuf.u32Read     = (u32)start;
        pEncDstChan->sEncDstBuf.u32Write    = (u32)start;
        pEncDstChan->sEncDstBuf.u32Length   = end - start + 1;//lint !e834
        /* ?????????????????? */
        pEncDstChan->u32SetStat = SOCP_CHN_SET;
    }
    
    else if(ChanType == SOCP_DECODER_SRC_CHAN)   // ??????????
    {
        SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFWPTR(RealChanId), (u32)start);
        SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFADDR(RealChanId), (u32)start);
        SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFRPTR(RealChanId), (u32)start);

        pDecSrcChan = &g_strSocpStat.sDecSrcChan[RealChanId];
        pDecSrcChan->u32ChanID = RealChanId;
        pDecSrcChan->eDataTypeEn= ((SOCP_DECODER_SRC_CHAN_STRU *)pAttr)->eDataTypeEn;
        pDecSrcChan->sDecSrcBuf.Start = start;
        pDecSrcChan->sDecSrcBuf.End = end;
        pDecSrcChan->sDecSrcBuf.u32Length = end - start + 1;//lint !e834
        pDecSrcChan->sDecSrcBuf.u32Read = (u32)start;
        pDecSrcChan->sDecSrcBuf.u32Write = (u32)start;
        pDecSrcChan->u32SetStat = SOCP_CHN_SET;
    }
    
    else if(ChanType == SOCP_DECODER_DEST_CHAN)   // ????????????
    {
        SOCP_REG_WRITE(SOCP_REG_DECDEST_BUFRPTR(RealChanId), (u32)start);
        SOCP_REG_WRITE(SOCP_REG_DECDEST_BUFADDR(RealChanId), (u32)start);
        SOCP_REG_WRITE(SOCP_REG_DECDEST_BUFWPTR(RealChanId), (u32)start);

        pDecDstChan = &g_strSocpStat.sDecDstChan[RealChanId];
        pDecDstChan->eDataType = ((SOCP_DECODER_DEST_CHAN_STRU *)pAttr)->eDataType;
        pDecDstChan->sDecDstBuf.Start    = start;
        pDecDstChan->sDecDstBuf.End      = end;
        pDecDstChan->sDecDstBuf.u32Length   = end - start + 1;//lint !e834
        pDecDstChan->sDecDstBuf.u32Read     = (u32)start;
        pDecDstChan->sDecDstBuf.u32Write    = (u32)start;
    }
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_coder_set_src_chan
*
* ????????  : ??????????????????
*
* ????????  : pSrcAttr     ??????????????????
*             ulSrcChanID  ??????????ID
*
* ????????  : ??
*
* ?? ?? ??  : ??????????????????????????
*****************************************************************************/
s32 bsp_socp_coder_set_src_chan(SOCP_CODER_SRC_ENUM_U32 enSrcChanID, SOCP_CODER_SRC_CHAN_S *pSrcAttr)
{
    unsigned long start = 0;
    unsigned long end = 0;
    unsigned long base_addr_rdstart = 0;
    unsigned long base_addr_rdend = 0;
    u32 buflength   = 0;
    u32 Rdbuflength = 0;
    u32 i;
    u32 srcChanId;
    u32 u32SrcChanType;
    u32 u32DstChanID;
    u32 u32DstChanType;
    u32 ResetFlag;
    // SOCP_ENCSRC_CHAN_S *pChan;

    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpAllocEncSrcCnt++;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(pSrcAttr);
    SOCP_CHECK_CHAN_PRIORITY(pSrcAttr->ePriority);
    SOCP_CHECK_DATA_TYPE(pSrcAttr->eDataType);
    SOCP_CHECK_DATA_TYPE_EN(pSrcAttr->eDataTypeEn);
    SOCP_CHECK_ENC_DEBUG_EN(pSrcAttr->eDebugEn);

    srcChanId       = SOCP_REAL_CHAN_ID(enSrcChanID);
    u32SrcChanType  = SOCP_REAL_CHAN_TYPE(enSrcChanID);

    SOCP_CHECK_CHAN_TYPE(u32SrcChanType, SOCP_CODER_SRC_CHAN);
    SOCP_CHECK_ENCSRC_CHAN_ID(srcChanId);

    u32DstChanID   = SOCP_REAL_CHAN_ID(pSrcAttr->u32DestChanID);
    u32DstChanType = SOCP_REAL_CHAN_TYPE(pSrcAttr->u32DestChanID);
    SOCP_CHECK_CHAN_TYPE(u32DstChanType, SOCP_CODER_DEST_CHAN);
    SOCP_CHECK_CHAN_ID(u32DstChanID, SOCP_MAX_ENCDST_CHN);

    if ((SOCP_ENCSRC_CHNMODE_CTSPACKET != pSrcAttr->eMode)
        && (SOCP_ENCSRC_CHNMODE_LIST != pSrcAttr->eMode))
    {
        socp_printf("bsp_socp_coder_set_src_chan: chnnel mode is invalid %d!\n", pSrcAttr->eMode);
        return BSP_ERR_SOCP_INVALID_PARA;
    }

    /* ???????????????????? */
    /* ????????????????8???????? */
    start   = (unsigned long)pSrcAttr->sCoderSetSrcBuf.pucInputStart;
    end     = (unsigned long)pSrcAttr->sCoderSetSrcBuf.pucInputEnd;
	
    SOCP_CHECK_PARA(start);
    SOCP_CHECK_8BYTESALIGN(start);
    SOCP_CHECK_PARA(end);
    SOCP_CHECK_BUF_ADDR(start, end);
    buflength = (u32)(end - start + 1);

    SOCP_CHECK_8BYTESALIGN(buflength);

    if(socp_version < SOCP_201_VERSION)
    {
        if(buflength > SOCP_ENC_SRC_BUFLGTH_MAX)
        {
            socp_printf("bsp_socp_coder_set_src_chan: buffer length is too large!\n");
            return BSP_ERR_SOCP_INVALID_PARA;
        }
    }

    /* ??????????????????????????RDbuffer???????????????? */
    if(SOCP_ENCSRC_CHNMODE_LIST == pSrcAttr->eMode)
    {
        /* ????RDBuffer??????????????8???????? */
        base_addr_rdstart = (unsigned long)pSrcAttr->sCoderSetSrcBuf.pucRDStart;
        base_addr_rdend   = (unsigned long)pSrcAttr->sCoderSetSrcBuf.pucRDEnd;

        SOCP_CHECK_PARA(base_addr_rdstart);
        SOCP_CHECK_8BYTESALIGN(base_addr_rdstart);
        SOCP_CHECK_PARA(base_addr_rdend);
        SOCP_CHECK_BUF_ADDR(base_addr_rdstart, base_addr_rdend);
        /* RD???????????? */
        //SOCP_CHECK_PARA(pSrcAttr->sCoderSetSrcBuf.u32RDThreshold);
        Rdbuflength = (u32)(base_addr_rdend - base_addr_rdstart + 1);

        SOCP_CHECK_8BYTESALIGN(Rdbuflength);
        if(Rdbuflength > SOCP_ENC_SRC_RDLGTH_MAX)
        {
            socp_printf("bsp_socp_coder_set_src_chan: RD buffer length is too large!\n");
            return BSP_ERR_SOCP_INVALID_PARA;
        }
    }

    /* ???????? */
    SOCP_REG_SETBITS(SOCP_REG_ENCRST, srcChanId, 1, 1);

    /* ???????????? */
    for (i = 0; i < SOCP_RESET_TIME; i++)
    {
        ResetFlag = SOCP_REG_GETBITS(SOCP_REG_ENCRST, srcChanId, 1);
        if(0 == ResetFlag)
        {
            break;
        }

        if ((SOCP_RESET_TIME - 1) == i)
        {
            socp_printf("bsp_socp_coder_set_src_chan: reset channel 0x%x failed!\n", srcChanId);
        }
    }

    /* ?????????????????? */
	/*lint -save -e647*/
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 1, 2, pSrcAttr->eMode);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 4, 4, pSrcAttr->u32DestChanID);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 8, 2, pSrcAttr->ePriority);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 10, 1, pSrcAttr->u32BypassEn);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 11, 1, pSrcAttr->eDataTypeEn);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 31, 1, pSrcAttr->eDebugEn);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 16, 8, pSrcAttr->eDataType);
	/*lint -restore +e647*/

    /*lint -save -e845*/
    /*lint -save -e647*/
    if(socp_version >= SOCP_201_VERSION)
    {
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFCFG0(srcChanId),buflength);
    }
    else
    {
        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(srcChanId), 0, 27, buflength);
        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(srcChanId), 27, 5, 0);
    }
    if(SOCP_ENCSRC_CHNMODE_LIST == pSrcAttr->eMode)
    {
        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_RDQCFG(srcChanId), 0, 16, Rdbuflength);
        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_RDQCFG(srcChanId), 16, 16, 0);
    }
    /*lint -restore +e647*/
    /*lint -restore +e845*/
    
    socp_set_reg_wr_addr(enSrcChanID, (void*)pSrcAttr, start, end);
    
    /* ???????????? */
    g_strSocpStat.sEncSrcChan[srcChanId].u32AllocStat = SOCP_CHN_ALLOCATED;
    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpAllocEncSrcSucCnt++;
    return BSP_OK;

}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_decoder_set_dest_chan
*
* ????????  : ??????????????????????????
*
* ????????  : pAttr           ????????????????????
*             pDestChanID     ??????????????????ID??????????????????ID??????????
                              SrcID = DestChanID%4
*
* ????????  :
*
* ?? ?? ??  : ??????????????????????????
*****************************************************************************/
s32 bsp_socp_decoder_set_dest_chan(SOCP_DECODER_DST_ENUM_U32 enDestChanID,
                                                SOCP_DECODER_DEST_CHAN_STRU *pAttr)
{
    unsigned long start;
    unsigned long end;
    u32 bufThreshold;
    u32 buflength;
    u32 u32ChanID;
    u32 u32SrcChanID;
    u32 u32ChanType;
    // SOCP_DECDST_CHAN_S *pChan;

    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpAllocDecDstCnt++;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(pAttr);
    SOCP_CHECK_DATA_TYPE(pAttr->eDataType);

    u32ChanID    = SOCP_REAL_CHAN_ID(enDestChanID);
    u32ChanType  = SOCP_REAL_CHAN_TYPE(enDestChanID);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_DEST_CHAN);
    SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECDST_CHN);

    u32SrcChanID = SOCP_REAL_CHAN_ID(pAttr->u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(pAttr->u32SrcChanID);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_SRC_CHAN);
    SOCP_CHECK_CHAN_ID(u32SrcChanID, SOCP_MAX_DECSRC_CHN);

    /* ????????ID???????? */
    if(u32SrcChanID != u32ChanID%4)
    {
        socp_printf("bsp_socp_decoder_set_dest_chan: dest ID(%d) is not matching src ID(%d)!\n", u32ChanID, u32SrcChanID);
        return BSP_ERR_SOCP_INVALID_PARA;
    }

    /* ????????????????????????????????????*/
    start           = (unsigned long)pAttr->sDecoderDstSetBuf.pucOutputStart;
    end             = (unsigned long)pAttr->sDecoderDstSetBuf.pucOutputEnd;
    bufThreshold    = pAttr->sDecoderDstSetBuf.u32Threshold;

    SOCP_CHECK_PARA(start);
    SOCP_CHECK_8BYTESALIGN(start);
    SOCP_CHECK_PARA(end);
    SOCP_CHECK_BUF_ADDR(start, end);
    buflength = (u32)(end - start + 1);


    SOCP_CHECK_PARA(bufThreshold);
    if (bufThreshold > SOCP_DEC_DST_TH_MAX)
    {
        socp_printf("bsp_socp_decoder_set_dest_chan: buffer threshold is too large!\n");
        return BSP_ERR_SOCP_INVALID_PARA;
    }

    SOCP_CHECK_8BYTESALIGN(buflength);
    if (buflength > SOCP_DEC_DST_BUFLGTH_MAX)
    {
        socp_printf("bsp_socp_decoder_set_dest_chan: buffer length is too large!\n");
        return BSP_ERR_SOCP_INVALID_PARA;
    }
	/*lint -save -e647*/
    SOCP_REG_SETBITS(SOCP_REG_DECDEST_BUFCFG(u32ChanID), 24, 8, pAttr->eDataType);
    SOCP_REG_SETBITS(SOCP_REG_DECDEST_BUFCFG(u32ChanID), 0, 16, buflength);
    SOCP_REG_SETBITS(SOCP_REG_DECDEST_BUFCFG(u32ChanID), 16, 8, bufThreshold);
	
    socp_set_reg_wr_addr(enDestChanID, (void*)pAttr, start, end);

    /* ????????????????????*/
    SOCP_REG_SETBITS(SOCP_REG_DEC_RAWINT0, u32ChanID, 1, 1);
    SOCP_REG_SETBITS(SOCP_REG_DEC_CORE0MASK0, u32ChanID, 1, 0);
    SOCP_REG_SETBITS(SOCP_REG_DEC_RAWINT2, u32ChanID, 1, 1);
    SOCP_REG_SETBITS(SOCP_REG_DEC_CORE0MASK2, u32ChanID, 1, 0);
	/*lint -restore +e647*/
	
    /* ???????????????? */
    g_strSocpStat.sDecDstChan[u32ChanID].u32AllocStat = SOCP_CHN_ALLOCATED;
    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpAllocDecDstSucCnt++;

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_coder_set_dest_chan_attr
*
* ????????  : ????????????????????
*
* ????????  : u32DestChanID      ????????????ID
              pDestAttr          ????????????????????
*
* ????????  : ??
* ?? ?? ??  : ????????????????????
*****************************************************************************/

s32 bsp_socp_coder_set_dest_chan_attr(u32 u32DestChanID, SOCP_CODER_DEST_CHAN_S *pDestAttr)
{
    unsigned long start;
    unsigned long end;
    u32 bufThreshold;
    u32 buflength;
    u32 u32ChanID;
    u32 u32ChanType;
    u32 u32Thrh;
    //SOCP_ENCDST_CHAN_S *pChan;

    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpSetEncDstCnt++;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(pDestAttr);
    u32ChanID   = SOCP_REAL_CHAN_ID(u32DestChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32DestChanID);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_CODER_DEST_CHAN);
    SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_ENCDST_CHN);

    start = (unsigned long)pDestAttr->sCoderSetDstBuf.pucOutputStart;
    end   = (unsigned long)pDestAttr->sCoderSetDstBuf.pucOutputEnd;
    bufThreshold = pDestAttr->sCoderSetDstBuf.u32Threshold;
    u32Thrh = pDestAttr->u32EncDstThrh;

    SOCP_CHECK_PARA(start);
    SOCP_CHECK_8BYTESALIGN(start);
    SOCP_CHECK_PARA(end);
    SOCP_CHECK_BUF_ADDR(start, end);
    buflength = (u32)(end - start + 1);

    SOCP_CHECK_PARA(bufThreshold);
    SOCP_CHECK_8BYTESALIGN(buflength);
    if(socp_version < SOCP_201_VERSION)
    {
        if (buflength > SOCP_ENC_DST_BUFLGTH_MAX)
        {
            socp_printf("CoderSetDestChanAttr: buffer length is too large!\n");
            return BSP_ERR_SOCP_INVALID_PARA;
        }

        if (bufThreshold > SOCP_ENC_DST_TH_MAX)
        {
            socp_printf("CoderSetDestChanAttr: buffer threshold is too large!\n");
            return BSP_ERR_SOCP_INVALID_PARA;
        }
    }
    /* ??????????????????????????,?????????????????????? */
    /* ???????????????????? */
	/*lint -save -e647*/
    if (SOCP_CHN_SET == g_strSocpStat.sEncDstChan[u32ChanID].u32SetStat)
    {
        socp_printf("CoderSetDestChanAttr: channel 0x%x can't be set twice!\n", u32ChanID);
        return BSP_ERR_SOCP_SET_FAIL;
    }

    if(socp_version >= SOCP_201_VERSION)
    {
        SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFCFG(u32ChanID),buflength);
        SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFTHRESHOLD(u32ChanID),(bufThreshold*1024));
    }
    else
    {
        SOCP_REG_SETBITS(SOCP_REG_ENCDEST_BUFCFG(u32ChanID), 0, 21, buflength);
        SOCP_REG_SETBITS(SOCP_REG_ENCDEST_BUFCFG(u32ChanID), 21, 11, bufThreshold);
    }

    SOCP_REG_SETBITS(SOCP_REG_ENCDEST_BUFTHRH(u32ChanID), 0, 31, u32Thrh);

    socp_set_reg_wr_addr(u32DestChanID, (void*)pDestAttr, start, end);        

    /* ???????????????????? */
    SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT0, u32ChanID, 1, 1);
    SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, u32ChanID, 1, 0);
    SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT2, u32ChanID, 1, 1);
    SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, u32ChanID, 1, 0);
    // ????????buffer????????
    SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT2, u32ChanID+16, 1, 1);
    SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, u32ChanID+16, 1, 0);
	/*lint -restore +e647*/
	
    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpSetEncDstSucCnt++;

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_decoder_set_src_chan_attr
*
* ????????  : ??????????????????
*
* ????????  : u32SrcChanID    ??????????ID
*             pInputAttr      ??????????????????
*
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_decoder_set_src_chan_attr(u32 u32SrcChanID, SOCP_DECODER_SRC_CHAN_STRU *pInputAttr)
{
    unsigned long start;
    unsigned long end;
    u32 buflength = 0;
    u32 u32ChanID;
    u32 u32ChanType;
    u32 i;
    u32 u32ResetFlag;
    // SOCP_DECSRC_CHAN_S *pDecSrcChan;

    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpSetDecSrcCnt++;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(pInputAttr);
    u32ChanID   = SOCP_REAL_CHAN_ID(u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_SRC_CHAN);
    SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECSRC_CHN);
    SOCP_CHECK_DATA_TYPE_EN(pInputAttr->eDataTypeEn);

    start = (unsigned long)pInputAttr->sDecoderSetSrcBuf.pucInputStart;
    end = (unsigned long)pInputAttr->sDecoderSetSrcBuf.pucInputEnd;

    SOCP_CHECK_PARA(start);
    SOCP_CHECK_8BYTESALIGN(start);
    SOCP_CHECK_PARA(end);
    SOCP_CHECK_BUF_ADDR(start, end);
    buflength = (u32)(end - start + 1);
    SOCP_CHECK_8BYTESALIGN(buflength);
    if (buflength > SOCP_DEC_SRC_BUFLGTH_MAX)
    {
        socp_printf("DecoderSetSrcChanAttr: buffer length is too large!\n");
        return BSP_ERR_SOCP_INVALID_PARA;
    }

    if (SOCP_CHN_SET == g_strSocpStat.sDecSrcChan[u32ChanID].u32SetStat)
    {
        socp_printf("DecoderSetSrcChanAttr: channel 0x%x has been configed!\n", u32ChanID);
        return BSP_ERR_SOCP_DECSRC_SET;
    }

    /* ???????????? */
    SOCP_REG_SETBITS(SOCP_REG_DECRST, u32ChanID, 1, 1);

    /* ???????????????????? */
    for (i = 0; i < SOCP_RESET_TIME; i++)
    {
        u32ResetFlag = SOCP_REG_GETBITS(SOCP_REG_DECRST, u32ChanID, 1);
        if (0 == u32ResetFlag)
        {
            break;
        }

        if ((SOCP_RESET_TIME - 1) == i)
        {
            socp_printf("DecoderSetSrcChanAttr: reset channel 0x%x failed!\n", u32ChanID);
        }
    }
	/*lint -save -e647*/
    SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32ChanID), 0, 16, buflength);
    SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32ChanID), 31, 1, pInputAttr->eDataTypeEn);
    //SOCP_REG_SETBITS(SOCP_REG_DECSRC_RDQCFG(u32ChanID), 29, 1, 0);
	/*lint -restore +e647*/
	
    socp_set_reg_wr_addr(u32SrcChanID, (void*)pInputAttr, start, end);
    
    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpSetDeSrcSucCnt++;

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_decoder_get_err_cnt
*
* ????????  : ??????????????????????????
*
* ????????  : u32ChanID       ????????ID

* ????????  : pErrCnt         ??????????????????????????
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_decoder_get_err_cnt(u32 u32DstChanID, SOCP_DECODER_ERROR_CNT_STRU *pErrCnt)
{
    u32 u32ChanID;
    u32 u32ChanType;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ????????ID???????? */
    u32ChanID   = SOCP_REAL_CHAN_ID(u32DstChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32DstChanID);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_SRC_CHAN);
    SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECSRC_CHN);
    SOCP_CHECK_DECSRC_SET(u32ChanID);

    /* ?????????????? */
    SOCP_CHECK_PARA(pErrCnt);

    /* ??????????????????????????debug????*/
    if (g_strSocpStat.sDecSrcChan[u32ChanID].u32ChanEn)
    {	
    	/*lint -save -e647*/
        pErrCnt->u32PktlengthCnt = SOCP_REG_GETBITS(SOCP_REG_DEC_BUFSTAT0(u32ChanID), 16, 16);
        pErrCnt->u32CrcCnt = SOCP_REG_GETBITS(SOCP_REG_DEC_BUFSTAT0(u32ChanID), 0, 16);
        pErrCnt->u32DataTypeCnt   = SOCP_REG_GETBITS(SOCP_REG_DEC_BUFSTAT1(u32ChanID), 16, 16);
        pErrCnt->u32HdlcHeaderCnt = SOCP_REG_GETBITS(SOCP_REG_DEC_BUFSTAT1(u32ChanID), 0, 16);
		/*lint -restore +e647*/
    }
    else
    {
        socp_printf("DecoderGetErrCnt: debug mode is closed!\n");
        return BSP_ERR_SOCP_SET_FAIL;
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_set_timeout
*
* ????????  : ????????????????
*
* ????????  :   eTmOutEn          ??????????????????
                u32Timeout        ????????
*
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_set_timeout (SOCP_TIMEOUT_EN_ENUM_UIN32 eTmOutEn, u32 u32Timeout)
{
    u32 u32newtime;

    DECODE_TIMEOUT_MODULE decode_timeout_module = DECODE_TIMEOUT_INT_TIMEOUT;
    /* ?????????????????? */
    SOCP_CHECK_INIT();

    u32newtime = (socp_version >= SOCP_3_4MS_VERSION) ? SOCP_CLK_RATIO(u32Timeout) : u32Timeout;

    switch (eTmOutEn)
    {
        case SOCP_TIMEOUT_BUFOVF_DISABLE:
        {
            SOCP_REG_SETBITS(SOCP_REG_BUFTIMEOUT, 31, 1, 0);
            break;
        }
        case SOCP_TIMEOUT_BUFOVF_ENABLE:
        {
            SOCP_REG_SETBITS(SOCP_REG_BUFTIMEOUT, 31, 1, 1);
            /* ?????????????? */
            SOCP_REG_SETBITS(SOCP_REG_BUFTIMEOUT, 0, 16, u32newtime);
            break;
        }
        case SOCP_TIMEOUT_TRF:
        {
            printk(KERN_ERR"bsp_socp_set_timeout 0x%x.\n", u32newtime);

            /* ??????????????????????????????ID*/
            /*
                            ??GLOBAL_CTRL[1]=0, bit[7:0]????
                            ??GLOBAL_CTRL[1]=1, bit[31:0]????
                    */
            /*SOCP_REG_WRITE(SOCP_REG_INTTIMEOUT, u32newtime);*/
            decode_timeout_module = (DECODE_TIMEOUT_MODULE)SOCP_REG_GETBITS(SOCP_REG_GBLRST, 1, 1);
            if(decode_timeout_module == DECODE_TIMEOUT_INT_TIMEOUT)
            {
                if (u32newtime > 0xFF)
                {
                   socp_printf("SetTimeout: the value is too large!\n");
                   return BSP_ERR_SOCP_INVALID_PARA;
                }

                SOCP_REG_WRITE(SOCP_REG_INTTIMEOUT, u32newtime);
            }
            else
            {
                /*SOCP_REG_SETBITS(SOCP_REG_INTTIMEOUT, 0, 31, u32newtime);*/
                SOCP_REG_WRITE(SOCP_REG_INTTIMEOUT, u32newtime);
            }
            break;
        }
        case SOCP_TIMEOUT_DECODE_TRF:
        {
            decode_timeout_module = (DECODE_TIMEOUT_MODULE)SOCP_REG_GETBITS(SOCP_REG_GBLRST, 1, 1);
            if(decode_timeout_module == DECODE_TIMEOUT_INT_TIMEOUT)
            {
                return BSP_ERR_SOCP_INVALID_PARA;
            }

            SOCP_REG_WRITE(SOCP_REG_DEC_INT_TIMEOUT, u32newtime);
			break;
        }
        default:
        {
            socp_printf("SetTimeout: invalid timeout choice type!\n");
            return BSP_ERR_SOCP_SET_FAIL;
        }
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_set_dec_pkt_lgth
*
* ????????  : ????????????????
*
* ????????  :   pPktlgth          ????????????????????????
*
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_set_dec_pkt_lgth(SOCP_DEC_PKTLGTH_STRU *pPktlgth)
{
    u32 u32PktMaxLgth;
    u32 u32PktMinLgth;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(pPktlgth);
    u32PktMaxLgth = pPktlgth->u32PktMax;
    u32PktMinLgth = pPktlgth->u32PktMin;

    SOCP_CHECK_PARA(u32PktMaxLgth);
    if (u32PktMaxLgth*1024 > SOCP_DEC_MAXPKT_MAX)
    {
        socp_printf("SetDecPktLgth: u32PktMaxLgth 0x%x is too large!\n", u32PktMaxLgth);
        return BSP_ERR_SOCP_INVALID_PARA;
    }

    if (u32PktMinLgth > SOCP_DEC_MINPKT_MAX)
    {
        socp_printf("SetDecPktLgth: u32PktMinLgth 0x%x is too large!\n", u32PktMinLgth);
        return BSP_ERR_SOCP_INVALID_PARA;
    }

    /* ????????????????????????????*/
    SOCP_REG_SETBITS(SOCP_REG_DEC_PKTLEN, 0, 12, u32PktMaxLgth);
    SOCP_REG_SETBITS(SOCP_REG_DEC_PKTLEN, 12, 5, u32PktMinLgth);

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_set_debug
*
* ????????  : ??????????????debug????????
*
* ????????  : u32DecChanID  ??????????ID
              u32DebugEn    debug????????????
*
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_set_debug(u32 u32DecChanID, u32 u32DebugEn)
{
    u32 u32ChanID;
    u32 u32ChanType;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ????????ID???????? */
    u32ChanID = SOCP_REAL_CHAN_ID(u32DecChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32DecChanID);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_SRC_CHAN);
    SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECSRC_CHN);
    SOCP_CHECK_DECSRC_SET(u32ChanID);

    /* ?????????????????????????????????????????? */
    if(g_strSocpStat.sDecSrcChan[u32ChanID].u32ChanEn)
    {
        socp_printf("SetDebug: decoder channel is open, can't set debug bit\n");
        return BSP_ERR_SOCP_SET_FAIL;
    }
    else
    {
		/*lint -save -e647*/
		SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32ChanID), 29, 1, u32DebugEn);
		/*lint -restore +e647*/
    }

    return BSP_OK;
}


/*****************************************************************************
* ?? ?? ??  : bsp_socp_free_channel
*
* ????????  : ????????????
*
* ????????  : u32ChanID       ??????????????
*
* ????????  : ??
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_free_channel(u32 u32ChanID)
{
    u32 u32RealChanID;
    u32 u32ChanType;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ????????ID???????? */
    u32RealChanID = SOCP_REAL_CHAN_ID(u32ChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32ChanID);

    if (SOCP_CODER_SRC_CHAN == u32ChanType)
    {
        SOCP_ENCSRC_CHAN_S *pChan;

        SOCP_CHECK_ENCSRC_CHAN_ID(u32RealChanID);
        SOCP_CHECK_ENCSRC_ALLOC(u32RealChanID);

        pChan = &g_strSocpStat.sEncSrcChan[u32RealChanID];
        if (SOCP_CHN_ENABLE == pChan->u32ChanEn)
        {
            socp_printf("FreeChannel: chan 0x%x is running!\n", u32ChanID);
            return BSP_ERR_SOCP_CHAN_RUNNING;
        }

        (void)socp_reset_enc_chan(u32RealChanID);

        pChan->u32AllocStat = SOCP_CHN_UNALLOCATED;

        g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpFreeEncSrcCnt[u32RealChanID]++;
    }
    else if (SOCP_DECODER_DEST_CHAN == u32ChanType)
    {
        SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECDST_CHN);
        SOCP_CHECK_DECDST_ALLOC(u32RealChanID);

        /* ???????????????? */
		/*lint -save -e647*/
        SOCP_REG_SETBITS(SOCP_REG_DECDEST_BUFCFG(u32RealChanID), 24, 8, 0xff);
		/*lint -restore +e647*/
		
        g_strSocpStat.sDecDstChan[u32RealChanID].u32AllocStat = SOCP_CHN_UNALLOCATED;

        g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpFreeDecDstCnt[u32RealChanID]++;
    }
    else
    {
        socp_printf("FreeChannel: invalid chan type 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_chan_soft_reset
*
* ????????  : ??????????????
*
* ????????  : u32ChanID       ??????????ID
*
* ????????  : ??
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_chan_soft_reset(u32 u32ChanID)
{
    u32 u32RealChanID;
    u32 u32ChanType;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ????????ID???????? */
    u32RealChanID = SOCP_REAL_CHAN_ID(u32ChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32ChanID);
    /* ????????????????????????????????LTE DSP/BBP???? */
    /* ???????????????????????????????????????????????????? */
    if (SOCP_CODER_SRC_CHAN == u32ChanType)
    {
        SOCP_CHECK_ENCSRC_CHAN_ID(u32RealChanID);
        SOCP_CHECK_ENCSRC_ALLOC(u32RealChanID);
        (void)socp_reset_enc_chan(u32ChanID);
        g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpSoftResetEncSrcCnt[u32RealChanID]++;
    }
    else if (SOCP_DECODER_SRC_CHAN == u32ChanType)
    {
        SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECSRC_CHN);
        SOCP_CHECK_DECSRC_SET(u32RealChanID);

        (void)socp_reset_dec_chan(u32RealChanID);

        g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpSoftResetDecSrcCnt[u32RealChanID]++;
    }
    else
    {
        socp_printf("ChnSoftReset: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_start
*
* ????????  : ????????????????????
*
* ????????  : u32SrcChanID      ????ID
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_start(u32 u32SrcChanID)
{
    u32 u32RealChanID;
    u32 u32ChanType;
    u32 u32Logic = (u32)1;
    u32 u32DstId;
    u32 i;
    u32 IntIDMask = 0;


    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ????????ID???????? */
    u32RealChanID = SOCP_REAL_CHAN_ID(u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

    /* ???????? */
    if (SOCP_CODER_SRC_CHAN == u32ChanType)
    {
        if (u32RealChanID < SOCP_MAX_ENCSRC_CHN)
        {
            SOCP_CHECK_ENCSRC_CHAN_ID(u32RealChanID);
            SOCP_CHECK_ENCSRC_ALLOC(u32RealChanID);
        }
        else
        {
            socp_printf("Start: enc src 0x%x is valid!\n", u32SrcChanID);
            return BSP_ERR_SOCP_INVALID_CHAN;
        }
	/*lint -save -e647*/
        u32DstId = SOCP_REG_GETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32RealChanID), 4, 4);
		
        if (SOCP_CHN_SET != g_strSocpStat.sEncDstChan[u32DstId].u32SetStat)
        {
            socp_printf("AppStart: enc dst chan is valid!\n");
            return BSP_ERR_SOCP_DEST_CHAN;
        }

        /* ????????????????????*/
        SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT1, u32RealChanID, 1, 1);
        SOCP_REG_SETBITS(SOCP_REG_APP_MASK1, u32RealChanID, 1, 0);

        if (SOCP_ENCSRC_CHNMODE_LIST == g_strSocpStat.sEncSrcChan[u32RealChanID].eChnMode)
        {
            SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT3, u32RealChanID, 1, 1);
            /* ????RD???????? */
            //SOCP_REG_SETBITS(SOCP_REG_APP_MASK3, u32RealChanID, 1, 0);
        }

        /* ????????????*/
        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32RealChanID), 0, 1, 1);
        if(u32RealChanID < SOCP_MAX_ENCSRC_CHN)
        {
            g_strSocpStat.sEncSrcChan[u32RealChanID].u32ChanEn = SOCP_CHN_ENABLE;
            g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpStartEncSrcCnt[u32RealChanID]++;
        }
    }
    else if (SOCP_DECODER_SRC_CHAN == u32ChanType)
    {
        SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECSRC_CHN);
        SOCP_CHECK_DECSRC_SET(u32RealChanID);

        /* ????rd????????*/
        if (SOCP_DECSRC_CHNMODE_LIST == g_strSocpStat.sDecSrcChan[u32RealChanID].eChnMode)
        {
            SOCP_REG_SETBITS(SOCP_REG_DEC_RAWINT1, u32RealChanID, 1, 1);
            SOCP_REG_SETBITS(SOCP_REG_DEC_MASK1, u32RealChanID, 1, 0);
        }

        for (i = 1; i < SOCP_DEC_SRCINT_NUM; i++)
        {
            IntIDMask  = SOCP_REG_GETBITS(SOCP_REG_DEC_RAWINT1, i * 4, 4);
            IntIDMask |= 1 << u32RealChanID;
            SOCP_REG_SETBITS(SOCP_REG_DEC_RAWINT1, i * 4, 4, IntIDMask);

            IntIDMask  = SOCP_REG_GETBITS(SOCP_REG_DEC_MASK1, i * 4, 4);
            IntIDMask &= ~(u32Logic << u32RealChanID);
            SOCP_REG_SETBITS(SOCP_REG_DEC_MASK1, i * 4, 4, IntIDMask);
        }

        /* ????????????*/
        SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32RealChanID), 30, 1, 1);
        g_strSocpStat.sDecSrcChan[u32RealChanID].u32ChanEn = SOCP_CHN_ENABLE;

        g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpStartDecSrcCnt[u32RealChanID]++;
    }
    else
    {
        socp_printf("Start: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }
	/*lint -restore +e647*/
    return BSP_OK;
}



/*****************************************************************************
* ?? ?? ??  : bsp_socp_stop
*
* ????????  : ????????????????????
*
* ????????  : u32SrcChanID      ????ID
*
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/

s32 bsp_socp_stop(u32 u32SrcChanID)
{
    u32 u32RealChanID;
    u32 u32ChanType;
    u32 IntIDMask = 0;
    u32 i;


    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ????????ID???????? */
    u32RealChanID = SOCP_REAL_CHAN_ID(u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

    /* ???????? */
    if (SOCP_CODER_SRC_CHAN == u32ChanType)
    {
        if (u32RealChanID < SOCP_MAX_ENCSRC_CHN)
        {
            SOCP_CHECK_ENCSRC_CHAN_ID(u32RealChanID);
            SOCP_CHECK_ENCSRC_ALLOC(u32RealChanID);
        }
        else
        {
            socp_printf("Stop: enc src 0x%x is valid!\n", u32SrcChanID);
            return BSP_ERR_SOCP_INVALID_CHAN;
        }
	/*lint -save -e647*/
        SOCP_REG_SETBITS(SOCP_REG_APP_MASK1, u32RealChanID, 1, 1);
        if (SOCP_ENCSRC_CHNMODE_LIST == g_strSocpStat.sEncSrcChan[u32RealChanID].eChnMode)
        {
            SOCP_REG_SETBITS(SOCP_REG_APP_MASK3, u32RealChanID, 1, 1);
        }

        /* ????????????????*/
        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32RealChanID), 0, 1, 0);
        if (u32RealChanID < SOCP_MAX_ENCSRC_CHN)
        {
            g_strSocpStat.sEncSrcChan[u32RealChanID].u32ChanEn = SOCP_CHN_DISABLE;
            g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpStopEncSrcCnt[u32RealChanID]++;
        }
    }
    else if (SOCP_DECODER_SRC_CHAN == u32ChanType)
    {
        SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECSRC_CHN);
        SOCP_CHECK_DECSRC_SET(u32RealChanID);

        /* ????????*/
        if (SOCP_DECSRC_CHNMODE_LIST == g_strSocpStat.sDecSrcChan[u32RealChanID].eChnMode)
        {
            SOCP_REG_SETBITS(SOCP_REG_DEC_CORE0MASK0, u32RealChanID, 1, 1);
        }

        for (i = 1; i < SOCP_DEC_SRCINT_NUM; i++)
        {
            IntIDMask  = SOCP_REG_GETBITS(SOCP_REG_DEC_MASK1, i * 4, 4);
            IntIDMask |= 1 << u32RealChanID;
            SOCP_REG_SETBITS(SOCP_REG_DEC_CORE0MASK0, i * 4, 4, IntIDMask);
        }

        /* ????????????????*/
        SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32RealChanID), 30, 1,0);
        g_strSocpStat.sDecSrcChan[u32RealChanID].u32ChanEn = SOCP_CHN_DISABLE;

        g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpStopDecSrcCnt[u32RealChanID]++;
    }
    else
    {
        socp_printf("Stop: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }
	/*lint -restore +e647*/
    return BSP_OK;
}


/*****************************************************************************
* ?? ?? ??  : bsp_socp_register_event_cb
*
* ????????  : ????????????????????????
*
* ????????  : u32ChanID      ????ID
*             EventCB        ??????????????????
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_register_event_cb(u32 u32ChanID, socp_event_cb EventCB)
{
    u32  u32RealChanID;
    u32  u32ChanType;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ????????????????????????ID */
    u32RealChanID = SOCP_REAL_CHAN_ID(u32ChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32ChanID);

    switch (u32ChanType)
    {
        case SOCP_CODER_SRC_CHAN:      /* ?????????? */
        {
            if (u32RealChanID < SOCP_MAX_ENCSRC_CHN)
            {
                SOCP_CHECK_ENCSRC_CHAN_ID(u32RealChanID);
                SOCP_CHECK_ENCSRC_ALLOC(u32RealChanID);
                g_strSocpStat.sEncSrcChan[u32RealChanID].event_cb = EventCB;

                g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpRegEventEncSrcCnt[u32RealChanID]++;
            }
            break;
        }
        case SOCP_CODER_DEST_CHAN:       /* ????????????*/
        {
            SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_ENCDST_CHN);
            SOCP_CHECK_ENCDST_SET(u32RealChanID);

            g_strSocpStat.sEncDstChan[u32RealChanID].event_cb = EventCB;

            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpRegEventEncDstCnt[u32RealChanID]++;
            break;
        }
        case SOCP_DECODER_SRC_CHAN:       /* ??????????*/
        {
            SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECSRC_CHN);
            SOCP_CHECK_DECSRC_SET(u32RealChanID);

            g_strSocpStat.sDecSrcChan[u32RealChanID].event_cb = EventCB;

            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpRegEventDecSrcCnt[u32RealChanID]++;
            break;
        }
        case SOCP_DECODER_DEST_CHAN:       /* ????????????*/
        {
            SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECDST_CHN);
            SOCP_CHECK_DECDST_ALLOC(u32RealChanID);

            g_strSocpStat.sDecDstChan[u32RealChanID].event_cb = EventCB;

            g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpRegEventDecDstCnt[u32RealChanID]++;
            break;
        }
        default:
        {
            socp_printf("RegisterEventCB: invalid chan type: 0x%x!\n", u32ChanType);
            return BSP_ERR_SOCP_INVALID_CHAN;
        }
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_get_write_buff
*
* ????????  : ??????????????buffer????
*
* ????????  : u32SrcChanID    ??????ID
* ????????  : pBuff           ??????buffer
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_get_write_buff(u32 u32SrcChanID, SOCP_BUFFER_RW_STRU *pBuff)
{
    u32 u32ChanID;
    u32 u32ChanType;
    u32 uPAddr;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(pBuff);

    /* ????????????id */
    u32ChanID   = SOCP_REAL_CHAN_ID(u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

    /* ???????? */
    if (SOCP_CODER_SRC_CHAN == u32ChanType)
    {
        g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpGetWBufEncSrcEtrCnt[u32ChanID]++;

        /* ????????id */
        SOCP_CHECK_ENCSRC_CHAN_ID(u32ChanID);
        SOCP_CHECK_ENCSRC_ALLOC(u32ChanID);

        /* ????????????????buffer */
        SOCP_REG_READ(SOCP_REG_ENCSRC_BUFRPTR(u32ChanID), uPAddr);
        g_strSocpStat.sEncSrcChan[u32ChanID].sEncSrcBuf.u32Read = uPAddr;
        SOCP_REG_READ(SOCP_REG_ENCSRC_BUFWPTR(u32ChanID), uPAddr);
        g_strSocpStat.sEncSrcChan[u32ChanID].sEncSrcBuf.u32Write= uPAddr;
        socp_get_idle_buffer(&g_strSocpStat.sEncSrcChan[u32ChanID].sEncSrcBuf, pBuff);
        g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpGetWBufEncSrcSucCnt[u32ChanID]++;
    }
    else if (SOCP_DECODER_SRC_CHAN == u32ChanType) /* ???????? */
    {
        g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpGetWBufDecSrcEtrCnt[u32ChanID]++;

        /* ????????id */
        SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECSRC_CHN);
        SOCP_CHECK_DECSRC_SET(u32ChanID);
        SOCP_REG_READ(SOCP_REG_DECSRC_BUFRPTR(u32ChanID), uPAddr);
        g_strSocpStat.sDecSrcChan[u32ChanID].sDecSrcBuf.u32Read = uPAddr;
        SOCP_REG_READ(SOCP_REG_DECSRC_BUFWPTR(u32ChanID), uPAddr);
        g_strSocpStat.sDecSrcChan[u32ChanID].sDecSrcBuf.u32Write= uPAddr;
        socp_get_idle_buffer(&g_strSocpStat.sDecSrcChan[u32ChanID].sDecSrcBuf, pBuff);
        g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpGetWBufDecSrcSucCnt[u32ChanID]++;
    }
    else
    {
        socp_printf("GetWriteBuff: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_write_done
*
* ????????  : ??????????????
*
* ????????  : u32SrcChanID    ??????ID
              u32WrtSize      ??????????????
*
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_write_done(u32 u32SrcChanID, u32 u32WrtSize)
{
    u32 u32ChanID;
    u32 u32ChanType;
    u32 u32WrtPad;
    SOCP_BUFFER_RW_STRU RwBuff;
    u32  uPAddr;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(u32WrtSize);

    /* ????????????id */
    u32ChanID   = SOCP_REAL_CHAN_ID(u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

    /* ???????? */
    if (SOCP_CODER_SRC_CHAN == u32ChanType)
    {
        SOCP_ENCSRC_CHAN_S *pChan;

        g_stSocpDebugInfo.sSocpDebugEncSrc.u32socp_write_doneEncSrcEtrCnt[u32ChanID]++;

        /* ????????id */
        SOCP_CHECK_ENCSRC_CHAN_ID(u32ChanID);
        SOCP_CHECK_ENCSRC_ALLOC(u32ChanID);

        pChan = &g_strSocpStat.sEncSrcChan[u32ChanID];
        u32WrtPad = u32WrtSize % 8;
        if (0 != u32WrtPad)
        {
            u32WrtSize += (8 - u32WrtPad);
        }

        SOCP_REG_READ(SOCP_REG_ENCSRC_BUFWPTR(u32ChanID), uPAddr);
        pChan->sEncSrcBuf.u32Write= uPAddr;
        SOCP_REG_READ(SOCP_REG_ENCSRC_BUFRPTR(u32ChanID), uPAddr);
        pChan->sEncSrcBuf.u32Read =uPAddr;

        socp_get_idle_buffer(&pChan->sEncSrcBuf, &RwBuff);

        if (RwBuff.u32Size + RwBuff.u32RbSize < u32WrtSize)
        {
            socp_printf("WriteDone: enc src, too large write size!\n");
            socp_printf("WriteDone: enc src, write ptr is 0x%x, read ptr is 0x%x\n", pChan->sEncSrcBuf.u32Write, pChan->sEncSrcBuf.u32Read);
            socp_printf("WriteDone: enc src, u32Size is 0x%x, u32RbSize is 0x%x\n", RwBuff.u32Size, RwBuff.u32RbSize);
            socp_printf("WriteDone: enc src, u32WrtSize is 0x%x, u32SrcChanID is 0x%x\n", u32WrtSize, u32SrcChanID);
            g_stSocpDebugInfo.sSocpDebugEncSrc.u32socp_write_doneEncSrcFailCnt[u32ChanID]++;
            return BSP_ERR_SOCP_INVALID_PARA;
        }

        /* ???????????? */
        socp_write_done(&pChan->sEncSrcBuf, u32WrtSize);

        /* ????????????????????????*/
        uPAddr = pChan->sEncSrcBuf.u32Write; /* [false alarm]:????Fortify???? */
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR(u32ChanID), uPAddr);
        g_stSocpDebugInfo.sSocpDebugEncSrc.u32socp_write_doneEncSrcSucCnt[u32ChanID]++;
    }
    else  if(SOCP_DECODER_SRC_CHAN == u32ChanType) /* ???????? */
    {
        SOCP_DECSRC_CHAN_S  *pChan;

        g_stSocpDebugInfo.sSocpDebugDecSrc.u32socp_write_doneDecSrcEtrCnt[u32ChanID]++;

        /* ????????id */
        SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECSRC_CHN);
        SOCP_CHECK_DECSRC_SET(u32ChanID);
        pChan = &g_strSocpStat.sDecSrcChan[u32ChanID];
        SOCP_REG_READ(SOCP_REG_DECSRC_BUFWPTR(u32ChanID), uPAddr);
        pChan->sDecSrcBuf.u32Write= uPAddr;
        SOCP_REG_READ(SOCP_REG_DECSRC_BUFRPTR(u32ChanID), uPAddr);
        pChan->sDecSrcBuf.u32Read =uPAddr;
        socp_get_idle_buffer(&pChan->sDecSrcBuf, &RwBuff);

        if (RwBuff.u32Size + RwBuff.u32RbSize < u32WrtSize)
        {
            socp_printf("WriteDone: dec src, too large write size!\n");
            socp_printf("WriteDone: dec src, write ptr is 0x%x, read ptr is 0x%x\n", pChan->sDecSrcBuf.u32Write, pChan->sDecSrcBuf.u32Read);
            socp_printf("WriteDone: dec src, u32Size is 0x%x, u32RbSize is 0x%x\n", RwBuff.u32Size, RwBuff.u32RbSize);
            socp_printf("WriteDone: dec src, u32WrtSize is 0x%x, u32SrcChanID is 0x%x\n", u32WrtSize, u32SrcChanID);
            g_stSocpDebugInfo.sSocpDebugDecSrc.u32socp_write_doneDecSrcFailCnt[u32ChanID]++;

            return BSP_ERR_SOCP_INVALID_PARA;
        }

        /* ???????????? */
        socp_write_done(&pChan->sDecSrcBuf, u32WrtSize);

        /* ????????????????????????*/
        uPAddr = pChan->sDecSrcBuf.u32Write; /* [false alarm]:????Fortify???? */
        SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFWPTR(u32ChanID), uPAddr);
        g_stSocpDebugInfo.sSocpDebugDecSrc.u32socp_write_doneDecSrcSucCnt[u32ChanID]++;
    }
    else
    {
        socp_printf("WriteDone: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_register_rd_cb
*
* ????????  : RDbuffer????????????????
*
* ????????  : u32SrcChanID    ??????ID
              RdCB            RDbuffer????????????
*
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_register_rd_cb(u32 u32SrcChanID, socp_rd_cb RdCB)
{
    u32 u32RealChanID;
    u32 u32ChanType;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ????????????????????????ID */
    u32RealChanID = SOCP_REAL_CHAN_ID(u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

    /* ???????? */
    if (SOCP_CODER_SRC_CHAN == u32ChanType)
    {
        SOCP_CHECK_ENCSRC_CHAN_ID(u32RealChanID);
        SOCP_CHECK_ENCSRC_ALLOC(u32RealChanID);

        if (SOCP_ENCSRC_CHNMODE_LIST == g_strSocpStat.sEncSrcChan[u32RealChanID].eChnMode)
        {
            /* ??????????????????????*/
            g_strSocpStat.sEncSrcChan[u32RealChanID].rd_cb = RdCB;
        }
        else
        {
            socp_printf("RegisterRdCB: invalid chan mode!\n");
            return BSP_ERR_SOCP_CHAN_MODE;
        }

        g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpRegRdCBEncSrcCnt[u32RealChanID]++;
    }
    else
    {
        socp_printf("RegisterRdCB: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_get_rd_buffer
*
* ????????  : ????RDbuffer????
*
* ????????  : u32SrcChanID    ??????ID
*
* ????????  : pBuff           ??????RDbuffer
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_get_rd_buffer(u32 u32SrcChanID, SOCP_BUFFER_RW_STRU *pBuff)
{
    u32 u32ChanID;
    u32 u32ChanType;
    u32 uPAddr;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(pBuff);

    /* ????????????id */
    u32ChanID   = SOCP_REAL_CHAN_ID(u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

    /* ???????? */
    if (SOCP_CODER_SRC_CHAN == u32ChanType)
    {
        g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpGetRdBufEncSrcEtrCnt[u32ChanID]++;

        /* ????????id */
        SOCP_CHECK_ENCSRC_CHAN_ID(u32ChanID);
        SOCP_CHECK_ENCSRC_ALLOC(u32ChanID);

        /* ????????????????buffer */
        SOCP_REG_READ(SOCP_REG_ENCSRC_RDQRPTR(u32ChanID), uPAddr);
        g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf.u32Read = uPAddr;
        SOCP_REG_READ(SOCP_REG_ENCSRC_RDQWPTR(u32ChanID), uPAddr);
        g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf.u32Write= uPAddr;
        socp_get_data_buffer(&g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf, pBuff);
        g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpGetRdBufEncSrcSucCnt[u32ChanID]++;
    }
    else
    {
        socp_printf("GetRDBuffer: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}


/*****************************************************************************
* ?? ?? ??  : bsp_socp_read_rd_done
*
* ????????  : ????RDbuffer????????????
*
* ????????  : u32SrcChanID   ??????ID
              u32RDSize      ??????RDbuffer????????
*
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_read_rd_done(u32 u32SrcChanID, u32 u32RDSize)
{
    u32 u32ChanID;
    u32 u32ChanType;
    SOCP_BUFFER_RW_STRU RwBuff;
    u32  uPAddr;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(u32RDSize);

    /* ????????????id */
    u32ChanID   = SOCP_REAL_CHAN_ID(u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

    /* ???????? */
    if (SOCP_CODER_SRC_CHAN == u32ChanType)
    {
        SOCP_ENCSRC_CHAN_S *pChan;

        g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpReadRdDoneEncSrcEtrCnt[u32ChanID]++;

        /* ????????id */
        SOCP_CHECK_ENCSRC_CHAN_ID(u32ChanID);
        SOCP_CHECK_ENCSRC_ALLOC(u32ChanID);

        pChan = &g_strSocpStat.sEncSrcChan[u32ChanID];
        g_strSocpStat.sEncSrcChan[u32ChanID].u32LastRdSize = 0;

        /* ???????????? */
        SOCP_REG_READ(SOCP_REG_ENCSRC_RDQWPTR(u32ChanID), uPAddr);
        pChan->sRdBuf.u32Write = uPAddr;
        SOCP_REG_READ(SOCP_REG_ENCSRC_RDQRPTR(u32ChanID), uPAddr);
        pChan->sRdBuf.u32Read  = uPAddr;
        socp_get_data_buffer(&pChan->sRdBuf, &RwBuff);

        if (RwBuff.u32Size + RwBuff.u32RbSize < u32RDSize)
        {
            socp_printf("ReadRDDone: enc src, too large rd size!\n");
            socp_printf("ReadRDDone: enc src, write ptr is 0x%x, read ptr is 0x%x\n", pChan->sRdBuf.u32Write, pChan->sRdBuf.u32Read);
            socp_printf("ReadRDDone: enc src, u32Size is 0x%x, u32RbSize is 0x%x\n", RwBuff.u32Size, RwBuff.u32RbSize);
            socp_printf("ReadRDDone: enc src, u32RDSize is 0x%x, u32SrcChanID is 0x%x\n", u32RDSize, u32SrcChanID);
            g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpReadRdDoneEncSrcFailCnt[u32ChanID]++;

            return BSP_ERR_SOCP_INVALID_PARA;
        }

        socp_read_done(&pChan->sRdBuf, u32RDSize);

        /* ????????????????????????*/
        uPAddr= pChan->sRdBuf.u32Read; /* [false alarm]:????Fortify???? */
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQRPTR(u32ChanID), uPAddr);
        g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpReadRdDoneEncSrcSucCnt[u32ChanID]++;
    }
    else
    {
        socp_printf("ReadRDDone: invalid chan type: 0x%x!", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

//????????????????

/*****************************************************************************
* ?? ?? ??  : bsp_socp_register_read_cb
*
* ????????  : ??????????????????????
*
* ????????  : u32DestChanID  ??????????ID
              ReadCB         ??????????????
*
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_register_read_cb(u32 u32DestChanID, socp_read_cb ReadCB)
{
    u32 u32RealChanID;
    u32 u32ChanType;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ????????????????????????ID */
    u32RealChanID = SOCP_REAL_CHAN_ID(u32DestChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32DestChanID);

    if (SOCP_DECODER_DEST_CHAN == u32ChanType) /* ???????? */
    {
        SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECDST_CHN);
        SOCP_CHECK_DECDST_ALLOC(u32RealChanID);

        g_strSocpStat.sDecDstChan[u32RealChanID].read_cb = ReadCB;

        g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpRegReadCBDecDstCnt[u32RealChanID]++;
    }
    else if (SOCP_CODER_DEST_CHAN == u32ChanType)/* ???????? */
    {
        SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_ENCDST_CHN);
        SOCP_CHECK_ENCDST_SET(u32RealChanID);

        /* ??????????????????????*/
        g_strSocpStat.sEncDstChan[u32RealChanID].read_cb = ReadCB;

        g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpRegReadCBEncDstCnt[u32RealChanID]++;
    }
    else
    {
        socp_printf("RegisterReadCB: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_get_read_buff
*
* ????????  : ??????????buffer????
*
* ????????  : u32DestChanID  ????????buffer

* ????????  : pBuffer        ????????????buffer
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_get_read_buff(u32 u32DestChanID, SOCP_BUFFER_RW_STRU *pBuffer)
{
    u32 u32ChanID;
    u32 u32ChanType;
    u32  uPAddr;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(pBuffer);

    /* ????????????id */
    u32ChanID   = SOCP_REAL_CHAN_ID(u32DestChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32DestChanID);
    pBuffer->u32Size   = 0;
    pBuffer->u32RbSize = 0;

    if (SOCP_DECODER_DEST_CHAN == u32ChanType) /* ???????? */
    {
        g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpGetReadBufDecDstEtrCnt[u32ChanID]++;

        /* ????????id */
        SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECDST_CHN);
        SOCP_CHECK_DECDST_ALLOC(u32ChanID);

        /* ????????????????buffer */
        SOCP_REG_READ(SOCP_REG_DECDEST_BUFRPTR(u32ChanID), uPAddr);
        g_strSocpStat.sDecDstChan[u32ChanID].sDecDstBuf.u32Read = uPAddr;
        SOCP_REG_READ(SOCP_REG_DECDEST_BUFWPTR(u32ChanID), uPAddr);
        g_strSocpStat.sDecDstChan[u32ChanID].sDecDstBuf.u32Write= uPAddr;
        socp_get_data_buffer(&g_strSocpStat.sDecDstChan[u32ChanID].sDecDstBuf, pBuffer);
        g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpGetReadBufDecDstSucCnt[u32ChanID]++;
    }
    else if (SOCP_CODER_DEST_CHAN == u32ChanType)
    {
        g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpGetReadBufEncDstEtrCnt[u32ChanID]++;
        /*deflate????????deflate buffer*/
        if((SOCP_COMPRESS == g_strSocpStat.sEncDstChan[u32ChanID].struCompress.bcompress )
            &&(g_strSocpStat.sEncDstChan[u32ChanID].struCompress.ops.getbuffer))
        {
            g_strSocpStat.sEncDstChan[u32ChanID].struCompress.ops.getbuffer(pBuffer);
            return BSP_OK;
        }

        /* ????????id */
        SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_ENCDST_CHN);
        SOCP_CHECK_ENCDST_SET(u32ChanID);

        /* ????????????????buffer */
        SOCP_REG_READ(SOCP_REG_ENCDEST_BUFRPTR(u32ChanID), uPAddr);
        g_strSocpStat.sEncDstChan[u32ChanID].sEncDstBuf.u32Read = uPAddr;
        SOCP_REG_READ(SOCP_REG_ENCDEST_BUFWPTR(u32ChanID), uPAddr);
        g_strSocpStat.sEncDstChan[u32ChanID].sEncDstBuf.u32Write= uPAddr;
        socp_get_data_buffer(&g_strSocpStat.sEncDstChan[u32ChanID].sEncDstBuf, pBuffer);
        g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpGetReadBufEncDstSucCnt[u32ChanID]++;
    }
    else
    {
        socp_printf("GetReadBuff: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_read_data_done
*
* ????????  : ??????????????
*
* ????????  : u32DestChanID    ????????ID
*             u32ReadSize      ????????????
* ????????  : ??
*
* ?? ?? ??  : ??????????????????????
*****************************************************************************/
s32 bsp_socp_read_data_done(u32 u32DestChanID, u32 u32ReadSize)
{
    u32 u32ChanID;
    u32 u32ChanType;
    SOCP_BUFFER_RW_STRU RwBuff;
    u32  uPAddr;
    u32  uPAddr2;
    u32  uPAddr3;
    unsigned long lock_flag;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /*????MSP????????????????????????????0??????2011-04-29*/
    //SOCP_CHECK_PARA(u32ReadSize);

    /* ????????????id */
    u32ChanID   = SOCP_REAL_CHAN_ID(u32DestChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32DestChanID);

    if (SOCP_DECODER_DEST_CHAN == u32ChanType) /* ???????? */
    {
        u32 TfMaskReg = 0;
        SOCP_DECDST_CHAN_S *pChan;

        g_stSocpDebugInfo.sSocpDebugDecDst.u32socp_read_doneDecDstEtrCnt[u32ChanID]++;

        /* ????????id */
        SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECDST_CHN);
        SOCP_CHECK_DECDST_ALLOC(u32ChanID);

        //added by yangzhi 2011.7.25
        TfMaskReg = SOCP_REG_DEC_CORE0MASK0;
        pChan = &g_strSocpStat.sDecDstChan[u32ChanID];
        SOCP_REG_READ(SOCP_REG_DECDEST_BUFWPTR(u32ChanID), uPAddr);
        pChan->sDecDstBuf.u32Write= uPAddr;
        SOCP_REG_READ(SOCP_REG_DECDEST_BUFRPTR(u32ChanID), uPAddr);
        pChan->sDecDstBuf.u32Read = uPAddr;
        socp_get_data_buffer(&pChan->sDecDstBuf, &RwBuff);

        if(RwBuff.u32Size + RwBuff.u32RbSize < u32ReadSize)
        {
            socp_printf("ReadDataDone: dec dst, too large read size!\n");
            socp_printf("ReadDataDone: dec dst, write ptr is 0x%x, read ptr is 0x%x\n", pChan->sDecDstBuf.u32Write, pChan->sDecDstBuf.u32Read);
            socp_printf("ReadDataDone: dec dst, u32Size is 0x%x, u32RbSize is 0x%x\n", RwBuff.u32Size, RwBuff.u32RbSize);
            socp_printf("ReadDataDone: dec dst, u32ReadSize is 0x%x, u32DestChanID is 0x%x\n", u32ReadSize, u32DestChanID);
            spin_lock_irqsave(&lock, lock_flag);
            SOCP_REG_SETBITS(SOCP_REG_DEC_RAWINT0, u32ChanID, 1, 1);
            SOCP_REG_SETBITS(TfMaskReg, u32ChanID, 1, 0);
            spin_unlock_irqrestore(&lock, lock_flag);
            g_stSocpDebugInfo.sSocpDebugDecDst.u32socp_read_doneDecDstFailCnt[u32ChanID]++;

            return BSP_ERR_SOCP_INVALID_PARA;
        }

        /* ???????????? */
        socp_read_done(&pChan->sDecDstBuf, u32ReadSize);

        /* ????????????????????????*/
        uPAddr = pChan->sDecDstBuf.u32Read; /* [false alarm]:????Fortify???? */
        SOCP_REG_WRITE(SOCP_REG_DECDEST_BUFRPTR(u32ChanID), uPAddr);
        //added by yangzhi 2011.7.25
        spin_lock_irqsave(&lock, lock_flag);
        SOCP_REG_SETBITS(SOCP_REG_DEC_RAWINT0, u32ChanID, 1, 1);
        SOCP_REG_SETBITS(TfMaskReg, u32ChanID, 1, 0);
        spin_unlock_irqrestore(&lock, lock_flag);

        if (0 == u32ReadSize)
        {
            g_stSocpDebugInfo.sSocpDebugDecDst.u32socp_read_doneZeroDecDstCnt[u32ChanID]++;
        }
        else
        {
            g_stSocpDebugInfo.sSocpDebugDecDst.u32socp_read_doneValidDecDstCnt[u32ChanID]++;
        }

        g_stSocpDebugInfo.sSocpDebugDecDst.u32socp_read_doneDecDstSucCnt[u32ChanID]++;
    }
    else if (SOCP_CODER_DEST_CHAN == u32ChanType)/* ???????? */
    {

        u32 curmodestate;
        SOCP_ENCDST_CHAN_S *pChan;

	    curmodestate=bsp_socp_read_cur_mode(u32ChanID);
	    if(1==curmodestate)
        {
            socp_printf("socp ind delay mode is cycle 0x%x!\n",curmodestate);
            return BSP_OK;
        }
        
        g_stSocpDebugInfo.sSocpDebugEncDst.u32socp_read_doneEncDstEtrCnt[u32ChanID]++;

        /* ????????id */
        SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_ENCDST_CHN);
        SOCP_CHECK_ENCDST_SET(u32ChanID);
        if(u32ChanID == 1)
        {
            g_stEncDstStat[g_ulEncDstStatCount].ulReadDoneStartSlice = bsp_get_slice_value();
        }
        /*????deflate??????deflate readdone*/
        if(( SOCP_COMPRESS == g_strSocpStat.sEncDstChan[u32ChanID].struCompress.bcompress)
            &&(g_strSocpStat.sEncDstChan[u32ChanID].struCompress.ops.readdone))
        {
            g_strSocpStat.sEncDstChan[u32ChanID].struCompress.ops.readdone(u32ReadSize);
            return BSP_OK;
        }

        if (0 == u32ReadSize)
        {
            g_stSocpDebugInfo.sSocpDebugEncDst.u32socp_read_doneZeroEncDstCnt[u32ChanID]++;
        }
        else
        {
            g_stSocpDebugInfo.sSocpDebugEncDst.u32socp_read_doneValidEncDstCnt[u32ChanID]++;
        }

        pChan = &g_strSocpStat.sEncDstChan[u32ChanID];
        SOCP_REG_READ(SOCP_REG_ENCDEST_BUFWPTR(u32ChanID), uPAddr);
        pChan->sEncDstBuf.u32Write= uPAddr;
        SOCP_REG_READ(SOCP_REG_ENCDEST_BUFRPTR(u32ChanID), uPAddr);
        pChan->sEncDstBuf.u32Read = uPAddr;
        socp_get_data_buffer(&pChan->sEncDstBuf, &RwBuff);

        if(RwBuff.u32Size + RwBuff.u32RbSize < u32ReadSize)
        {
            socp_printf("ReadDataDone: enc dst, too large read size!\n");
            socp_printf("ReadDataDone: enc dst, write ptr is 0x%x, read ptr is 0x%x\n", pChan->sEncDstBuf.u32Write, pChan->sEncDstBuf.u32Read);
            socp_printf("ReadDataDone: enc dst, u32Size is 0x%x, u32RbSize is 0x%x\n", RwBuff.u32Size, RwBuff.u32RbSize);
            socp_printf("ReadDataDone: enc dst, u32ReadSize is 0x%x, u32DestChanID is 0x%x\n", u32ReadSize, u32DestChanID);
            spin_lock_irqsave(&lock, lock_flag);
            SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT0, u32ChanID, 1, 1);
            SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, u32ChanID, 1, 0);
            /* overflow int */
            SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT2, u32ChanID + 16, 1, 1);
            SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, u32ChanID + 16, 1, 0);
            spin_unlock_irqrestore(&lock, lock_flag);
            g_stSocpDebugInfo.sSocpDebugEncDst.u32socp_read_doneEncDstFailCnt[u32ChanID]++;
            return BSP_ERR_SOCP_INVALID_PARA;
        }

        /* ???????????? */
        socp_read_done(&pChan->sEncDstBuf, u32ReadSize);

        /* ????????????????????????*/
        uPAddr2 = pChan->sEncDstBuf.u32Read; /* [false alarm]:????Fortify???? */
        /*lint -save -e732*/
        SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFRPTR(u32ChanID), uPAddr2);
        SOCP_REG_READ(SOCP_REG_ENCDEST_BUFRPTR(u32ChanID), uPAddr3);
        /*lint -restore +e732*/
        SOCP_DEBUG_TRACE(SOCP_DEBUG_READ_DONE, pChan->sEncDstBuf.u32Write, uPAddr, uPAddr2, uPAddr3);

        spin_lock_irqsave(&lock, lock_flag);
        SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT0, u32ChanID, 1, 1);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, u32ChanID, 1, 0);
        /* overflow int */
        SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT2, u32ChanID + 16, 1, 1);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, u32ChanID + 16, 1, 0);
        spin_unlock_irqrestore(&lock, lock_flag);
        g_stSocpDebugInfo.sSocpDebugEncDst.u32socp_read_doneEncDstSucCnt[u32ChanID]++;

        if(u32ChanID == 1)
        {
            g_stEncDstStat[g_ulEncDstStatCount].ulReadDoneEndSlice = bsp_get_slice_value();
            g_ulEncDstStatCount = (g_ulEncDstStatCount+1)%SOCP_MAX_ENC_DST_COUNT;
        }
    }
    else
    {
        socp_printf("ReadDataDone: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_set_bbp_enable
*
* ????????  : ????/????BPP LOG??????
*
* ????????  : bEnable       ????????
*
* ????????  : ??
*
* ?? ?? ??  : ??????????????????????
*****************************************************************************/
s32 bsp_socp_set_bbp_enable(int bEnable)
{
    if(bEnable)
    {
        BBP_REG_SETBITS(BBP_REG_CH_EN, 0, 1, 1);
    }
    else
    {
        BBP_REG_SETBITS(BBP_REG_CH_EN, 0, 1, 0);
    }
    return BSP_OK;
}


/*****************************************************************************
* ?? ?? ??  : bsp_socp_set_bbp_ds_mode
*
* ????????  : ????BPP????????
*
* ????????  : eDsMode    ????????
*
* ????????  : ??
*
* ?? ?? ??  :
*****************************************************************************/
s32 bsp_socp_set_bbp_ds_mode(SOCP_BBP_DS_MODE_ENUM_UIN32 eDsMode)
{
    if(eDsMode >= SOCP_BBP_DS_MODE_BUTT)
    {
        socp_printf("SetBbpDsMode: invalid DS mode!\n");
        return BSP_ERR_SOCP_INVALID_PARA;
    }

    BBP_REG_SETBITS(BBP_REG_DS_CFG, 31, 1, eDsMode);
    return BSP_OK;
}
void bsp_socp_set_enc_dst_threshold(bool mode,u32 u32DestChanID)
{
    u32 bufLength;
    u32 threshold;

    u32DestChanID = SOCP_REAL_CHAN_ID(u32DestChanID);

    SOCP_REG_READ(SOCP_REG_ENCDEST_BUFCFG(u32DestChanID),bufLength);
    if(mode == true)/*true????????????????????????*/
    {
        threshold = (bufLength >> 2)*3;
    }
    else
    {
        threshold = 0x1000;
    }
    SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFTHRESHOLD(u32DestChanID),threshold);

    socp_printf("[socp] set encdst threshold success! 0x%x\n", threshold);

    return;
}
/*****************************************************************************
* ?? ?? ??  : bsp_socp_encdst_set_cycle
*
* ????????  : SOCP????????????
*
* ????????  : ????????????
*
* ????????  : ??
*
* ?? ?? ??  : ??
*****************************************************************************/
/*lint -save -e647*/
void bsp_socp_encdst_set_cycle(u32 chanid, u32 cycle)
{
    u32 u32modestate;
    u32 u32ChanID = SOCP_REAL_CHAN_ID(chanid);

    /* ???????????????????????????????????????? */
    SOCP_REG_SETBITS(SOCP_REG_CLKCTRL,0,1,0);

    u32modestate = SOCP_REG_GETBITS(SOCP_REG_ENCDEST_SBCFG(u32ChanID),1,1);
    if ((0==cycle||1==cycle) && u32modestate)
    {
        int i;

        SOCP_REG_SETBITS(SOCP_REG_ENCDEST_SBCFG(u32ChanID),0,1,0);
        for(i=0; i<1000; i++)
        {
            u32modestate = SOCP_REG_GETBITS(SOCP_REG_ENCDEST_SBCFG(u32ChanID),1,1);
            if(0 == u32modestate)
            {
                break;
            }
        }

        if(1000 == i)
        {
            socp_printf("set encdst cycle off timeout!\n");
        }

        SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT0, u32ChanID, 1, 1);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, u32ChanID, 1, 0);
        SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT2, u32ChanID, 1, 1);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, u32ChanID, 1, 0);

        SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT2, u32ChanID+16, 1, 1);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, u32ChanID+16, 1, 0);
    }
    else if((2==cycle) && (!u32modestate))
    {
        int i;

        SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT0, u32ChanID, 1, 1);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, u32ChanID, 1, 1);
        SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT2, u32ChanID, 1, 1);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, u32ChanID, 1, 1);

        SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT2, u32ChanID+16, 1, 1);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, u32ChanID+16, 1, 1);

        SOCP_REG_SETBITS(SOCP_REG_ENCDEST_SBCFG(u32ChanID),0,1,1);

        for(i=0; i<1000; i++)
        {
            u32modestate = SOCP_REG_GETBITS(SOCP_REG_ENCDEST_SBCFG(u32ChanID),1,1);
            if(1 == u32modestate)
            {
                break;
            }
        }

        if(1000 == i)
        {
            socp_printf("set encdst cycle on timeout!\n");
        }
    }

    /* ???????????????????????????????????????? */
    SOCP_REG_SETBITS(SOCP_REG_CLKCTRL,0,1,1);
    return ;
}
/*lint -restore +e647*/

/*****************************************************************************
* ?? ?? ??   : socp_enc_dst_stat
*
* ????????  : ????socp????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void show_socp_enc_dst_stat(void)
{
    int i ;
    int count = (g_ulEncDstStatCount+1)%SOCP_MAX_ENC_DST_COUNT;

    for(i=0;i<SOCP_MAX_ENC_DST_COUNT;i++)
    {
        printk("\r **********stat %d count************ \r\n",i);
        printk("Int   Start  : 0x%x,  End  : 0x%x ,Slice :0x%x\n",g_stEncDstStat[count].ulIntStartSlice,g_stEncDstStat[count].ulIntEndSlice,g_stEncDstStat[count].ulIntEndSlice-g_stEncDstStat[count].ulIntStartSlice);
        printk("Task  Start  : 0x%x,  End  : 0x%x ,Slice :0x%x\n",g_stEncDstStat[count].ulTaskStartSlice,g_stEncDstStat[count].ulTaskEndSlice,g_stEncDstStat[count].ulTaskEndSlice-g_stEncDstStat[count].ulTaskStartSlice);
        printk("Read  Start  : 0x%x,  End  : 0x%x ,Slice :0x%x\n",g_stEncDstStat[count].ulReadDoneStartSlice,g_stEncDstStat[count].ulReadDoneEndSlice,g_stEncDstStat[count].ulReadDoneEndSlice-g_stEncDstStat[count].ulReadDoneStartSlice);
        printk("Int  ==> Task 0x%x\n",g_stEncDstStat[count].ulTaskStartSlice-g_stEncDstStat[count].ulIntStartSlice);
        printk("Task  ==> Read 0x%x\n",g_stEncDstStat[count].ulReadDoneStartSlice-g_stEncDstStat[count].ulTaskEndSlice);
        count = (count+1)%SOCP_MAX_ENC_DST_COUNT;
    }
}

/*****************************************************************************
* ?? ?? ??   : socp_help
*
* ????????  : ????socp????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void socp_help(void)
{
    socp_printf("\r |*************************************|\n");
    socp_printf("\r socp_show_debug_gbl   : ????????????????:??????????????????????????????????\n");
    socp_printf("\r socp_show_enc_src_chan_cur : ??????????????????????????????ID\n");
    socp_printf("\r socp_show_enc_src_chan_add : ????????????????????????????????????ID\n");
    socp_printf("\r socp_show_enc_src_chan_add : ??????????????????????????????????????\n");
    socp_printf("\r socp_show_enc_dst_chan_cur : ????????????????????????????????ID\n");
    socp_printf("\r socp_show_enc_dst_chan_add : ??????????????????????????????????????ID\n");
    socp_printf("\r socp_show_enc_dst_chan_all : ????????????????????????????????????????\n");
    socp_printf("\r socp_show_dec_src_chan_cur : ??????????????????????????????ID\n");
    socp_printf("\r socp_show_dec_src_chan_add : ????????????????????????????????????ID\n");
    socp_printf("\r socp_show_dec_src_chan_all : ??????????????????????????????????????\n");
    socp_printf("\r socp_show_dec_dst_chan_cur : ????????????????????????????????ID\n");
    socp_printf("\r socp_show_dec_dst_chan_add : ??????????????????????????????????????ID\n");
    socp_printf("\r socp_show_dec_dst_chan_all : ????????????????????????????????????????\n");
    socp_printf("\r socp_show_ccore_head_err_cnt : ????C??????????????????????????????????????\n");
    socp_printf("\r socp_debug_cnt_show : ????????????????????????\n");
}

/*****************************************************************************
* ?? ?? ??   : socp_show_debug_gbl
*
* ????????  : ????????debug ????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void socp_show_debug_gbl(void)
{
    SOCP_DEBUG_GBL_S *sSocpDebugGblInfo;

    sSocpDebugGblInfo = &g_stSocpDebugInfo.sSocpDebugGBl;

    socp_printf(" SOCP????????????????:\n");
    socp_printf(" socp??????:                           : 0x%x\n", (s32)g_strSocpStat.baseAddr);
    socp_printf(" socp????????????????????              : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpAllocEncSrcCnt);
    socp_printf(" socp????????????????????????          : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpAllocEncSrcSucCnt);
    socp_printf(" socp??????????????????????            : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpSetEncDstCnt);
    socp_printf(" socp??????????????????????????        : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpSetEncDstSucCnt);
    socp_printf(" socp????????????????????              : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpSetDecSrcCnt);
    socp_printf(" socp????????????????????????          : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpSetDeSrcSucCnt);
    socp_printf(" socp??????????????????????            : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpAllocDecDstCnt);
    socp_printf(" socp??????????????????????????        : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpAllocDecDstSucCnt);
    socp_printf(" socp????APP??????????                 : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpAppEtrIntCnt);
    socp_printf(" socp????APP??????????                 : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpAppSucIntCnt);
}

/*****************************************************************************
* ?? ?? ??  : socp_show_ccore_head_err_cnt
*
* ????????  : ????C??????????????????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void socp_show_ccore_head_err_cnt(void)
{
    int i;
    for(i = SOCP_CCORE_ENCSRC_CHN_BASE; i < SOCP_CCORE_ENCSRC_CHN_BASE + SOCP_CCORE_ENCSRC_CHN_NUM; i++)
    {
        socp_printf("================== ?????????? 0x%x  ??????????????????:=================\n", i);
        socp_printf(" socp ISR ????????????????????????????????                  : 0x%x\n",
            (s32)g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpEncSrcIsrHeadIntCnt[i]);
    }
}

/*****************************************************************************
* ?? ?? ??   : socp_show_enc_src_chan_cur
*
* ????????  : ??????????????????????
*
* ????????  : ????ID
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/

u32 socp_show_enc_src_chan_cur(u32 u32UniqueId)
{
    u32 u32RealId   = 0;
    u32 u32ChanType = 0;

    u32RealId   = SOCP_REAL_CHAN_ID(u32UniqueId);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32UniqueId);

    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_CODER_SRC_CHAN);
    SOCP_CHECK_ENCSRC_CHAN_ID(u32RealId);

    socp_printf("================== ???????????????? 0x%x  ????:=================\n", u32UniqueId);
    socp_printf("????ID:\t\t%d\n", g_strSocpStat.sEncSrcChan[u32RealId].u32ChanID);
    socp_printf("????????????:\t\t%d\n", g_strSocpStat.sEncSrcChan[u32RealId].u32AllocStat);
    socp_printf("????????????:\t\t%d\n", g_strSocpStat.sEncSrcChan[u32RealId].u32ChanEn);
    socp_printf("????????ID:\t\t%d\n", g_strSocpStat.sEncSrcChan[u32RealId].u32DestChanID);
    socp_printf("??????????:\t\t%d\n", g_strSocpStat.sEncSrcChan[u32RealId].ePriority);
    socp_printf("????????????:\t\t%d\n", g_strSocpStat.sEncSrcChan[u32RealId].u32BypassEn);
    socp_printf("????????????????:\t\t%d\n", g_strSocpStat.sEncSrcChan[u32RealId].eChnMode);
    socp_printf("??????????????:\t\t%d\n", g_strSocpStat.sEncSrcChan[u32RealId].eDataType);
    socp_printf("????buffer ????????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sEncSrcBuf.Start);
    socp_printf("????buffer ????????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sEncSrcBuf.End);
    socp_printf("????buffer ??????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sEncSrcBuf.u32Read);
    socp_printf("????buffer ??????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sEncSrcBuf.u32Write);
    socp_printf("????buffer ????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sEncSrcBuf.u32Length);
    if (SOCP_ENCSRC_CHNMODE_LIST == g_strSocpStat.sEncSrcChan[u32RealId].eChnMode)
    {
        socp_printf("????RD buffer ????????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sRdBuf.Start);
        socp_printf("????RD buffer ????????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sRdBuf.End);
        socp_printf("????RD buffer ??????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sRdBuf.u32Read);
        socp_printf("????RD buffer ??????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sRdBuf.u32Write);
        socp_printf("????RD buffer ????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sRdBuf.u32Length);
        socp_printf("????RD buffer ????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].u32RdThreshold);
    }

    return BSP_OK;
}



/*****************************************************************************
* ?? ?? ??   : socp_show_enc_src_chan_add
*
* ????????  : ????????????????????????
*
* ????????  : ????ID
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
u32 socp_show_enc_src_chan_add(u32 u32UniqueId)
{
    u32 u32ChanType;
    u32 u32RealChanID;
    SOCP_DEBUG_ENCSRC_S *sSocpAddDebugEncSrc;

    u32RealChanID = SOCP_REAL_CHAN_ID(u32UniqueId);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32UniqueId);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_CODER_SRC_CHAN);

    sSocpAddDebugEncSrc = &g_stSocpDebugInfo.sSocpDebugEncSrc;
    SOCP_CHECK_ENCSRC_CHAN_ID(u32RealChanID);

    socp_printf("================== ?????????? 0x%x  ??????????:=================\n", u32UniqueId);
    socp_printf("socp????????????????????????                           : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpFreeEncSrcCnt[u32RealChanID]);
    socp_printf("socp????????????????????????                           : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpStartEncSrcCnt[u32RealChanID]);
    socp_printf("socp????????????????????????                           : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpStopEncSrcCnt[u32RealChanID]);
    socp_printf("socp??????????????????????????                         : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpSoftResetEncSrcCnt[u32RealChanID]);
    socp_printf("socp????????????????????????????????                   : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpRegEventEncSrcCnt[u32RealChanID]);
    socp_printf("socp????????????????????buffer??????                   : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpGetWBufEncSrcEtrCnt[u32RealChanID]);
    socp_printf("socp????????????????buffer??????????                   : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpGetWBufEncSrcSucCnt[u32RealChanID]);
    socp_printf("socp????????????????????buffer??????????               : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32socp_write_doneEncSrcEtrCnt[u32RealChanID]);
    socp_printf("socp????????????????buffer??????????????               : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32socp_write_doneEncSrcSucCnt[u32RealChanID]);
    socp_printf("socp????????????????buffer??????????????               : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32socp_write_doneEncSrcFailCnt[u32RealChanID]);
    socp_printf("socp??????????????RD buffer??????????????????          : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpRegRdCBEncSrcCnt[u32RealChanID]);
    socp_printf("socp??????????????????RD buffer??????                  : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpGetRdBufEncSrcEtrCnt[u32RealChanID]);
    socp_printf("socp??????????????RD buffer??????????                  : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpGetRdBufEncSrcSucCnt[u32RealChanID]);
    socp_printf("socp??????????????????RDbuffer??????????               : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpReadRdDoneEncSrcEtrCnt[u32RealChanID]);
    socp_printf("socp??????????????RDbuffer??????????????               : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpReadRdDoneEncSrcSucCnt[u32RealChanID]);
    socp_printf("socp??????????????RDbuffer??????????????               : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpReadRdDoneEncSrcFailCnt[u32RealChanID]);
    socp_printf("socp ISR ????????????????????????????????              : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpEncSrcIsrHeadIntCnt[u32RealChanID]);
    socp_printf("socp ????????????????????????????????????????????      : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpEncSrcTskHeadCbOriCnt[u32RealChanID]);
    socp_printf("socp ????????????????????????????????????????????      : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpEncSrcTskHeadCbCnt[u32RealChanID]);
    socp_printf("socp ISR ????????????????Rd ????????????               : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpEncSrcIsrRdIntCnt[u32RealChanID]);
    socp_printf("socp ????????????????????Rd ????????????????????       : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpEncSrcTskRdCbOriCnt[u32RealChanID]);
    socp_printf("socp ??????????????Rd ??????????????????????????       : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpEncSrcTskRdCbCnt[u32RealChanID]);

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_enc_src_chan_add
*
* ????????  : ??????????????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void  socp_show_enc_src_chan_all(void)
{
    u32 i;

    for (i = 0; i < SOCP_MAX_ENCSRC_CHN; i++)
    {
        (void)socp_show_enc_src_chan_cur(i);
        (void)socp_show_enc_src_chan_add(i);
    }

    return;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_enc_dst_chan_cur
*
* ????????  : ????????????????????
*
* ????????  : ????ID
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
u32 socp_show_enc_dst_chan_cur(u32 u32UniqueId)
{
    u32 u32RealId   = 0;
    u32 u32ChanType = 0;

    u32RealId   = SOCP_REAL_CHAN_ID(u32UniqueId);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32UniqueId);

    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_CODER_DEST_CHAN);

    socp_printf("================== ???????????? 0x%x  ????:=================\n", u32UniqueId);
    socp_printf("????ID                 :%d\n", g_strSocpStat.sEncDstChan[u32RealId].u32ChanID);
    socp_printf("????????????           :%d\n", g_strSocpStat.sEncDstChan[u32RealId].u32SetStat);
    socp_printf("????buffer ????????    :0x%x\n", g_strSocpStat.sEncDstChan[u32RealId].sEncDstBuf.Start);
    socp_printf("????buffer ????????    :0x%x\n", g_strSocpStat.sEncDstChan[u32RealId].sEncDstBuf.End);
    socp_printf("????buffer ??????      :0x%x\n", g_strSocpStat.sEncDstChan[u32RealId].sEncDstBuf.u32Read);
    socp_printf("????buffer ??????      :0x%x\n", g_strSocpStat.sEncDstChan[u32RealId].sEncDstBuf.u32Write);
    socp_printf("????buffer ????        :0x%x\n", g_strSocpStat.sEncDstChan[u32RealId].sEncDstBuf.u32Length);

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_enc_dst_chan_add
*
* ????????  : ??????????????????????????
*
* ????????  : ????ID
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
u32 socp_show_enc_dst_chan_add(u32 u32UniqueId)
{
    u32 u32RealChanID;
    u32 u32ChanType = 0;
    SOCP_DEBUG_ENCDST_S *sSocpAddDebugEncDst;

    u32ChanType = SOCP_REAL_CHAN_TYPE(u32UniqueId);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_CODER_DEST_CHAN);

    u32RealChanID = SOCP_REAL_CHAN_ID(u32UniqueId);
    sSocpAddDebugEncDst = &g_stSocpDebugInfo.sSocpDebugEncDst;

    socp_printf("================== ???????????? 0x%x  ??????????:=================\n", u32UniqueId);
    socp_printf("socp??????????????????????????????????                 : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpRegEventEncDstCnt[u32RealChanID]);
    socp_printf("socp????????????????????????????????????????           : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpRegReadCBEncDstCnt[u32RealChanID]);
    socp_printf("socp??????????????????????buffer ??????                : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpGetReadBufEncDstEtrCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer??????????                 : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpGetReadBufEncDstSucCnt[u32RealChanID]);
    socp_printf("socp??????????????????????buffer??????????             : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32socp_read_doneEncDstEtrCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer??????????????             : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32socp_read_doneEncDstSucCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer??????????????             : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32socp_read_doneEncDstFailCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer????????0 ??????????????   : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32socp_read_doneZeroEncDstCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer??????????0 ?????????????? : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32socp_read_doneValidEncDstCnt[u32RealChanID]);
    socp_printf("socpISR ??????????????????????????????????             : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpEncDstIsrTrfIntCnt[u32RealChanID]);
    socp_printf("socp??????????????????????????????????????????????     : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpEncDstTskTrfCbOriCnt[u32RealChanID]);
    socp_printf("socp??????????????????????????????????????????????     : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpEncDstTskTrfCbCnt[u32RealChanID]);
    socp_printf("socpISR ??????????????????buf ????????????             : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpEncDstIsrOvfIntCnt[u32RealChanID]);
    socp_printf("socp??????????????????????buf ????????????????????    : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpEncDstTskOvfCbOriCnt[u32RealChanID]);
    socp_printf("socp????????????????buf ??????????????????????????    : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpEncDstTskOvfCbCnt[u32RealChanID]);
    socp_printf("socpISR ??????????????????buf????????????????          : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpEncDstIsrThresholdOvfIntCnt[u32RealChanID]);
    socp_printf("socp??????????????????????buf????????????????????????  : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpEncDstTskThresholdOvfCbOriCnt[u32RealChanID]);
    socp_printf("socp????????????????buf??????????????????????????????  : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpEncDstTskThresholdOvfCbCnt[u32RealChanID]);

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_enc_dst_chan_all
*
* ????????  : ????????????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void socp_show_enc_dst_chan_all(void)
{
    u32 i;
    u32 u32UniqueId = 0;

    for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
    {
        u32UniqueId = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, i);
        (void)socp_show_enc_dst_chan_cur(u32UniqueId);
        (void)socp_show_enc_dst_chan_add(u32UniqueId);
    }

    return;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_dec_src_chan_cur
*
* ????????  : ??????????????????
*
* ????????  : ????ID
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
u32 socp_show_dec_src_chan_cur(u32 u32UniqueId)
{
    u32 u32RealId   = 0;
    u32 u32ChanType = 0;

    u32RealId   = SOCP_REAL_CHAN_ID(u32UniqueId);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32UniqueId);

    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_SRC_CHAN);

    socp_printf("================== ?????????? 0x%x  ????:=================\n", u32UniqueId);
    socp_printf("????ID                 :%d\n", g_strSocpStat.sDecSrcChan[u32RealId].u32ChanID);
    socp_printf("????????????           :%d\n", g_strSocpStat.sDecSrcChan[u32RealId].u32SetStat);
    socp_printf("????????????           :%d\n", g_strSocpStat.sDecSrcChan[u32RealId].u32ChanEn);
    socp_printf("????????               :%d\n", g_strSocpStat.sDecSrcChan[u32RealId].eChnMode);
    socp_printf("????buffer ????????    :0x%x\n", g_strSocpStat.sDecSrcChan[u32RealId].sDecSrcBuf.Start);
    socp_printf("????buffer ????????    :0x%x\n", g_strSocpStat.sDecSrcChan[u32RealId].sDecSrcBuf.End);
    socp_printf("????buffer ??????      :0x%x\n", g_strSocpStat.sDecSrcChan[u32RealId].sDecSrcBuf.u32Read);
    socp_printf("????buffer ??????      :0x%x\n", g_strSocpStat.sDecSrcChan[u32RealId].sDecSrcBuf.u32Write);
    socp_printf("????buffer ????        :0x%x\n", g_strSocpStat.sDecSrcChan[u32RealId].sDecSrcBuf.u32Length);

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_dec_src_chan_add
*
* ????????  : ????????????????????????
*
* ????????  : ????ID
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
u32 socp_show_dec_src_chan_add(u32 u32UniqueId)
{
    u32 u32RealChanID;
    SOCP_DEBUG_DECSRC_S *sSocpAddDebugDecSrc;
    u32 u32ChanType = 0;

    u32ChanType = SOCP_REAL_CHAN_TYPE(u32UniqueId);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_SRC_CHAN);

    u32RealChanID = SOCP_REAL_CHAN_ID(u32UniqueId);
    sSocpAddDebugDecSrc = &g_stSocpDebugInfo.sSocpDebugDecSrc;

    socp_printf("================== ?????????? 0x%x  ??????????:=================\n", u32UniqueId);
    socp_printf("socp??????????????????????????                     : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32SocpSoftResetDecSrcCnt[u32RealChanID]);
    socp_printf("socp????????????????????????                       : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32SocpStartDecSrcCnt[u32RealChanID]);
    socp_printf("socp????????????????????????                       : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32SocpStopDecSrcCnt[u32RealChanID]);
    socp_printf("socp????????????????????????????????               : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32SocpRegEventDecSrcCnt[u32RealChanID]);
    socp_printf("socp????????????????????buffer??????               : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32SocpGetWBufDecSrcEtrCnt[u32RealChanID]);
    socp_printf("socp????????????????buffer??????????               : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32SocpGetWBufDecSrcSucCnt[u32RealChanID]);
    socp_printf("socp????????????????????buffer??????????           : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32socp_write_doneDecSrcEtrCnt[u32RealChanID]);
    socp_printf("socp????????????????buffer??????????????           : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32socp_write_doneDecSrcSucCnt[u32RealChanID]);
    socp_printf("socp????????????????buffer??????????????           : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32socp_write_doneDecSrcFailCnt[u32RealChanID]);
    socp_printf("socpISR ????????????????????????????               : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32SocpDecSrcIsrErrIntCnt[u32RealChanID]);
    socp_printf("socp????????????????????????????????????????       : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32SocpDecSrcTskErrCbOriCnt[u32RealChanID]);
    socp_printf("socp????????????????????????????????????????       : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32SocpDecSrcTskErrCbCnt[u32RealChanID]);
    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_dec_src_chan_all
*
* ????????  : ??????????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void socp_show_dec_src_chan_all(void)
{
    u32 i;
    u32 u32UniqueId = 0;

    for (i = 0; i < SOCP_MAX_DECSRC_CHN; i++)
    {
        u32UniqueId = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN, i);
        (void)socp_show_dec_src_chan_cur(u32UniqueId);
        (void)socp_show_dec_src_chan_add(u32UniqueId);
    }

    return;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_dec_dst_chan_cur
*
* ????????  : ????????????????????
*
* ????????  : ????ID
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
u32 socp_show_dec_dst_chan_cur(u32 u32UniqueId)
{
    u32 u32RealId   = 0;
    u32 u32ChanType = 0;

    u32RealId   = SOCP_REAL_CHAN_ID(u32UniqueId);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32UniqueId);

    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_DEST_CHAN);

    socp_printf("================== ???????????? 0x%x  ????:=================\n", u32UniqueId); 
    socp_printf("????ID                 :%d\n", g_strSocpStat.sDecDstChan[u32RealId].u32ChanID);
    socp_printf("????????????           :%d\n", g_strSocpStat.sDecDstChan[u32RealId].u32AllocStat);
    socp_printf("??????????????         :%d\n", g_strSocpStat.sDecDstChan[u32RealId].eDataType);
    socp_printf("????buffer ????????    :0x%x\n", g_strSocpStat.sDecDstChan[u32RealId].sDecDstBuf.Start);
    socp_printf("????buffer ????????    :0x%x\n", g_strSocpStat.sDecDstChan[u32RealId].sDecDstBuf.End);
    socp_printf("????buffer ??????      :0x%x\n", g_strSocpStat.sDecDstChan[u32RealId].sDecDstBuf.u32Read);
    socp_printf("????buffer ??????      :0x%x\n", g_strSocpStat.sDecDstChan[u32RealId].sDecDstBuf.u32Write);
    socp_printf("????buffer ????        :0x%x\n", g_strSocpStat.sDecDstChan[u32RealId].sDecDstBuf.u32Length);

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_dec_dst_chan_add
*
* ????????  : ??????????????????????????
*
* ????????  : ????ID
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
u32 socp_show_dec_dst_chan_add(u32 u32UniqueId)
{
    u32 u32RealChanID;
    SOCP_DEBUG_DECDST_S *sSocpAddDebugDecDst;
    u32 u32ChanType = 0;

    u32ChanType = SOCP_REAL_CHAN_TYPE(u32UniqueId);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_DEST_CHAN);

    u32RealChanID = SOCP_REAL_CHAN_ID(u32UniqueId);
    sSocpAddDebugDecDst = &g_stSocpDebugInfo.sSocpDebugDecDst;

    socp_printf("================== ???????????? 0x%x  ??????????:=================\n", u32UniqueId);
    socp_printf("socp??????????????????????????                         : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpFreeDecDstCnt[u32RealChanID]);
    socp_printf("socp??????????????????????????????????                 : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpRegEventDecDstCnt[u32RealChanID]);
    socp_printf("socp????????????????????????????????????????           : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpRegReadCBDecDstCnt[u32RealChanID]);
    socp_printf("socp??????????????????????buffer??????                 : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpGetReadBufDecDstEtrCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer??????????                 : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpGetReadBufDecDstSucCnt[u32RealChanID]);
    socp_printf("socp??????????????????????buffer??????????             : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32socp_read_doneDecDstEtrCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer??????????????             : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32socp_read_doneDecDstSucCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer??????????????             : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32socp_read_doneDecDstFailCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer????????0 ??????????????   : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32socp_read_doneZeroDecDstCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer??????????0 ?????????????? : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32socp_read_doneValidDecDstCnt[u32RealChanID]);
    socp_printf("socpISR ??????????????????????????????????             : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpDecDstIsrTrfIntCnt[u32RealChanID]);
    socp_printf("socp?????? ??????????????????????????????????????????  : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpDecDstTskTrfCbOriCnt[u32RealChanID]);
    socp_printf("socp??????????????????????????????????????????????     : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpDecDstTskTrfCbCnt[u32RealChanID]);
    socp_printf("socpISR ??????????????????buf ????????????             : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpDecDstIsrOvfIntCnt[u32RealChanID]);
    socp_printf("socp?????? ????????????????buf ????????????????????    : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpDecDstTskOvfCbOriCnt[u32RealChanID]);
    socp_printf("socp????????????????buf ??????????????????????????     : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpDecDstTskOvfCbCnt[u32RealChanID]);

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_dec_dst_chan_all
*
* ????????  : ????????????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void socp_show_dec_dst_chan_all(void)
{
    u32 i;
    u32 u32UniqueId = 0;

    for (i = 0; i < SOCP_MAX_DECDST_CHN; i++)
    {
        u32UniqueId = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, i);
        (void)socp_show_dec_dst_chan_cur(u32UniqueId);
        (void)socp_show_dec_dst_chan_add(u32UniqueId);
    }

    return;
}

/*****************************************************************************
* ?? ?? ??   : socp_debug_cnt_show
*
* ????????  : ????debug ????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void socp_debug_cnt_show(void)
{
    socp_show_debug_gbl();
    socp_show_enc_src_chan_all();
    socp_show_enc_dst_chan_all();
    socp_show_dec_src_chan_all();
    socp_show_dec_dst_chan_all();
}

void socp_debug_set_trace(u32 v)
{
    g_ulSocpDebugTraceCfg = v;
}

#define MALLOC_MAX_SIZE     0x100000
#define MALLOC_MAX_INDEX    8           /*page_size ??4K*/
#define SOCP_PAGE_SIZE      0x1000

//__inline
s32 socp_get_index(u32 u32Size,u32 *index)
{
    u32 i = 0;
    if(u32Size > MALLOC_MAX_SIZE)
    {
        return BSP_ERROR;
    }
    for(i=0;i<=MALLOC_MAX_INDEX;i++)
    {
        if(u32Size <= (u32)(SOCP_PAGE_SIZE * (1<<i)))
        {
            *index = i;
            break;
        }
    }
    return BSP_OK;
}

void* socp_malloc(u32 u32Size)
{
    u8 *pItem= NULL;
    u32 index = 0;

    if(BSP_OK != socp_get_index(u32Size,&index))
    {
        return BSP_NULL;
    }

    index = 4;
    /* ???????? */
    pItem = (u8*)__get_free_pages(GFP_KERNEL,index);
    if(!pItem)
    {
        socp_printf("%s: malloc failed\n", __FUNCTION__);
        return BSP_NULL;
    }

    return (void*)pItem;
}

s32 socp_free(void* pMem)
{
    u32 *pItem;

    pItem = pMem;

    free_pages((unsigned long)pItem,4);
    return BSP_OK;
}

/* ?????????? begin */
/* ?????????????????? */
void BSP_SOCP_DrxRestoreRegAppOnly(void)
{
    u32 i= 0;

    for(i=0;i<SOCP_MAX_ENCDST_CHN;i++)
    {
        SOCP_REG_READ(SOCP_REG_ENCDEST_BUFRPTR(i),g_strSocpStat.sEncDstChan[i].sEncDstBuf.u32Read);
        SOCP_REG_READ(SOCP_REG_ENCDEST_BUFWPTR(i),g_strSocpStat.sEncDstChan[i].sEncDstBuf.u32Write);
    }

    for(i=0;i<SOCP_MAX_DECDST_CHN;i++)
    {
        SOCP_REG_READ(SOCP_REG_DECDEST_BUFRPTR(i),g_strSocpStat.sDecDstChan[i].sDecDstBuf.u32Read);
        SOCP_REG_READ(SOCP_REG_DECDEST_BUFWPTR(i),g_strSocpStat.sDecDstChan[i].sDecDstBuf.u32Write);
    }

    for(i=0;i<SOCP_MAX_ENCSRC_CHN;i++)
    {
        SOCP_REG_READ(SOCP_REG_ENCSRC_BUFRPTR(i),  g_strSocpStat.sEncSrcChan[i].sEncSrcBuf.u32Read);
        SOCP_REG_READ(SOCP_REG_ENCSRC_BUFWPTR(i),g_strSocpStat.sEncSrcChan[i].sEncSrcBuf.u32Write);

        SOCP_REG_READ(SOCP_REG_ENCSRC_RDQRPTR(i),  g_strSocpStat.sEncSrcChan[i].sRdBuf.u32Read);
        SOCP_REG_READ(SOCP_REG_ENCSRC_RDQWPTR(i),g_strSocpStat.sEncSrcChan[i].sRdBuf.u32Write);
    }

    for(i=0;i<SOCP_MAX_DECSRC_CHN;i++)
    {
        SOCP_REG_READ(SOCP_REG_DECSRC_BUFRPTR(i),  g_strSocpStat.sDecSrcChan[i].sDecSrcBuf.u32Read);
        SOCP_REG_READ(SOCP_REG_DECSRC_BUFWPTR(i),g_strSocpStat.sDecSrcChan[i].sDecSrcBuf.u32Write);
    }
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_get_state
*
* ????????  : ????SOCP????
*
* ?? ?? ??  : SOCP_IDLE    ????
*             SOCP_BUSY    ????
*****************************************************************************/
SOCP_STATE_ENUM_UINT32 bsp_socp_get_state(void)
{
    u32 u32EncChanState;
    u32 u32DecChanState;

    SOCP_REG_READ(SOCP_REG_ENCSTAT, u32EncChanState);
    SOCP_REG_READ(SOCP_REG_DECSTAT, u32DecChanState);
    if(u32EncChanState != 0 || u32DecChanState != 0)
    {
        return SOCP_BUSY;
    }

    return SOCP_IDLE;
}

/*****************************************************************************
* ?? ?? ??  : socp_is_encdst_chan_empty
*
* ????????  : SOCP??????????????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : u32 0:?????? ??0:????????????
*****************************************************************************/
u32 socp_is_encdst_chan_empty(void)
{
    u32 chanSet = 0;
    u32 i;
    u32 u32ReadPtr;
    u32 u32WritePtr;

    /* ???????????????????????????? */
    for(i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
    {
        SOCP_REG_READ(SOCP_REG_ENCDEST_BUFWPTR(i), u32WritePtr);
        SOCP_REG_READ(SOCP_REG_ENCDEST_BUFRPTR(i), u32ReadPtr);
        if(u32WritePtr != u32ReadPtr)
        {
            chanSet = chanSet | (1 << i);
        }
    }

    return chanSet;
}

module_init(socp_init);






/*****************************************************************************
* ?? ?? ??  : socp_set_clk_autodiv_enable
* ????????  : ????clk????clk_disable_unprepare??bypass??0??????????????
* ????????  : ??
* ????????  : ??
* ?? ?? ??  : ??
* ??    ??  :
              clk_prepare_enable ?????? clk_disable_unprepare ????????????????
              clk????????????????????????????????
              ?????????? clk_prepare_enable ???????? clk_disable_unprepare ????
*****************************************************************************/
void bsp_socp_set_clk_autodiv_enable(void)
{
}


/*****************************************************************************
* ?? ?? ??  : socp_set_clk_autodiv_disable
* ????????  : ????clk????clk_prepare_enable??bypass??1??????????????
* ????????  : ??
* ????????  : ??
* ?? ?? ??  : ??
* ??    ??  :
              clk_prepare_enable ?????? clk_disable_unprepare ????????????????
              clk????????????????????????????????
              ?????????? clk_prepare_enable ???????? clk_disable_unprepare ????
*****************************************************************************/
void bsp_socp_set_clk_autodiv_disable(void)
{
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_set_decode_timeout_register
*
* ????????  :??????????????????????????????
                            1 - ????????????INT_TIMEOUT(0x024)??????????????DEC_INT_TIMEOUT(0x20);
                            0 - ????????????????INT_TIMEOUT(0x024)

*
* ?? ?? ??  :  ??
*
*
*****************************************************************************/
s32 bsp_socp_set_decode_timeout_register(DECODE_TIMEOUT_MODULE module)
{
    if(module > DECODE_TIMEOUT_DEC_INT_TIMEOUT)
    {
        return BSP_ERR_SOCP_INVALID_PARA;
    }
    SOCP_REG_SETBITS(SOCP_REG_GBLRST, 1, 1, module);

    return BSP_OK;

}
EXPORT_SYMBOL(bsp_socp_set_decode_timeout_register);


EXPORT_SYMBOL(socp_reset_dec_chan);
EXPORT_SYMBOL(socp_soft_free_encdst_chan);
EXPORT_SYMBOL(socp_soft_free_decsrc_chan);

EXPORT_SYMBOL(bsp_socp_clean_encsrc_chan);
EXPORT_SYMBOL(socp_init);
EXPORT_SYMBOL(bsp_socp_coder_set_src_chan);
EXPORT_SYMBOL(bsp_socp_decoder_set_dest_chan);
EXPORT_SYMBOL(bsp_socp_coder_set_dest_chan_attr);
EXPORT_SYMBOL(bsp_socp_decoder_get_err_cnt);
EXPORT_SYMBOL(bsp_socp_decoder_set_src_chan_attr);
EXPORT_SYMBOL(bsp_socp_set_timeout);
EXPORT_SYMBOL(bsp_socp_set_dec_pkt_lgth);
EXPORT_SYMBOL(bsp_socp_set_debug);
EXPORT_SYMBOL(bsp_socp_free_channel);
EXPORT_SYMBOL(bsp_socp_chan_soft_reset);
EXPORT_SYMBOL(bsp_socp_start);
EXPORT_SYMBOL(bsp_socp_stop);
EXPORT_SYMBOL(bsp_socp_register_event_cb);
EXPORT_SYMBOL(bsp_socp_get_write_buff);
EXPORT_SYMBOL(bsp_socp_write_done);
EXPORT_SYMBOL(bsp_socp_register_rd_cb);
EXPORT_SYMBOL(bsp_socp_get_rd_buffer);
EXPORT_SYMBOL(bsp_socp_read_rd_done);
EXPORT_SYMBOL(bsp_socp_register_read_cb);
EXPORT_SYMBOL(bsp_socp_get_read_buff);
EXPORT_SYMBOL(bsp_socp_read_data_done);
EXPORT_SYMBOL(bsp_socp_set_bbp_enable);
EXPORT_SYMBOL(bsp_socp_set_bbp_ds_mode);

EXPORT_SYMBOL(socp_help);
EXPORT_SYMBOL(socp_show_debug_gbl);
EXPORT_SYMBOL(socp_show_ccore_head_err_cnt);
EXPORT_SYMBOL(socp_show_enc_src_chan_cur);
EXPORT_SYMBOL(socp_show_enc_src_chan_add);
EXPORT_SYMBOL(socp_show_enc_src_chan_all);
EXPORT_SYMBOL(socp_show_enc_dst_chan_cur);
EXPORT_SYMBOL(socp_show_enc_dst_chan_add);
EXPORT_SYMBOL(socp_show_enc_dst_chan_all);
EXPORT_SYMBOL(socp_show_dec_src_chan_cur);
EXPORT_SYMBOL(socp_show_dec_src_chan_add);
EXPORT_SYMBOL(socp_show_dec_src_chan_all);
EXPORT_SYMBOL(socp_show_dec_dst_chan_cur);
EXPORT_SYMBOL(socp_show_dec_dst_chan_add);
EXPORT_SYMBOL(socp_show_dec_dst_chan_all);

EXPORT_SYMBOL(socp_debug_cnt_show);
EXPORT_SYMBOL(socp_get_index);
EXPORT_SYMBOL(BSP_SOCP_DrxRestoreRegAppOnly);
EXPORT_SYMBOL(bsp_socp_get_state);
EXPORT_SYMBOL(socp_is_encdst_chan_empty);



