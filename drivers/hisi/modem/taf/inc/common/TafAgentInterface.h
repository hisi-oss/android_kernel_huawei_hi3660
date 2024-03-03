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

#ifndef _TAFAGENTAPSINTERFACE_H_
#define _TAFAGENTAPSINTERFACE_H_

/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "vos.h"
#include "TafTypeDef.h"
#include "AtMnInterface.h"
#include "TafApsApi.h"
#include "MnCallApi.h"
#include "TafAppMma.h"

#pragma pack(4)


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


/*****************************************************************************
  2 ??????
*****************************************************************************/

/*****************************************************************************
  3 ????????????
*****************************************************************************/


/*****************************************************************************
  4 ????????
*****************************************************************************/

enum TAFAGENT_MSG_ID_ENUM
{

    /* TAFAGENT->APS ????CID???????? */
    ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ   = 0x1000,                           /* _H2ASN_MsgChoice TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ_STRU */

    /* TAFAGENT->APS ????CID?????????????? */
    ID_TAFAGENT_APS_SET_CID_PARA_REQ        = 0x1001,                           /* _H2ASN_MsgChoice TAFAGENT_APS_SET_CID_PARA_REQ_STRU */

    /* TAFAGENT->APS ????CID?????????????? */
    ID_TAFAGENT_APS_GET_CID_PARA_REQ        = 0x1002,                           /* _H2ASN_MsgChoice TAFAGENT_APS_GET_CID_PARA_REQ_STRU */

    /* TAFAGENT->APS ????CID??QOS???????????? */
    ID_TAFAGENT_APS_SET_CID_QOS_PARA_REQ    = 0x1003,                           /* _H2ASN_MsgChoice TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU */

    /* TAFAGENT->APS ????CID??QOS???????????? */
    ID_TAFAGENT_APS_GET_CID_QOS_PARA_REQ    = 0x1004,                           /* _H2ASN_MsgChoice TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU */

    ID_TAFAGENT_MTA_GET_SYSMODE_REQ         = 0x1005,                           /* _H2ASN_MsgChoice TAFAGENT_MTA_GET_SYSMODE_REQ_STRU */

    ID_TAFAGENT_MTA_GET_ANT_STATE_REQ       = 0x1006,                           /* _H2ASN_MsgChoice TAFAGENT_MTA_GET_ANT_STATE_REQ_STRU */


    /* APS->TAFAGENT ????CID???????? */
    ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF   = 0x2000,                           /* _H2ASN_MsgChoice TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU */

    /* APS->TAFAGENT ????CID?????????????? */
    ID_TAFAGENT_APS_SET_CID_PARA_CNF        = 0x2001,                           /* _H2ASN_MsgChoice TAFAGENT_APS_SET_CID_PARA_CNF_STRU */

    /* APS->TAFAGENT ????CID?????????????? */
    ID_TAFAGENT_APS_GET_CID_PARA_CNF        = 0x2002,                           /* _H2ASN_MsgChoice TAFAGENT_APS_GET_CID_PARA_CNF_STRU */

    /* APS->TAFAGENT ????CID??QOS???????????? */
    ID_TAFAGENT_APS_SET_CID_QOS_PARA_CNF    = 0x2003,                           /* _H2ASN_MsgChoice TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU */

    /* APS->TAFAGENT ????CID??QOS???????????? */
    ID_TAFAGENT_APS_GET_CID_QOS_PARA_CNF    = 0x2004,                           /* _H2ASN_MsgChoice TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU */

    /* TAFAGENT->MTA  ????????????????????????*/
    ID_TAFAGENT_MTA_GET_SYSMODE_CNF         = 0x2005,                           /* _H2ASN_MsgChoice TAFAGENT_MTA_GET_SYSMODE_CNF_STRU */

    /* TAFAGENT->MN  ????????????????????*/
    ID_TAFAGENT_MN_GET_CALL_INFO_CNF        = 0x2006,                           /* _H2ASN_MsgChoice TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU */



    /* MTA->TAFAGENT  ????????????????????*/
    ID_TAFAGENT_MTA_GET_ANT_STATE_CNF       = 0x2007,                           /* _H2ASN_MsgChoice TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU */

    ID_TAFAGENT_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32  TAFAGENT_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  5 ????????
*****************************************************************************/


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulClientID;                             /* CLIENT ID */
    TAF_PDP_PRIM_CONTEXT_EXT_STRU       stPdpPrimContextExt;                    /* CID???? */
} TAFAGENT_APS_SET_CID_PARA_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

} TAFAGENT_APS_QUERY_ERROR_CODE_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

} TAFAGENT_APS_CLEAR_ERROR_CODE_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT8                           ucCid;                                  /* ????????????CID */

    VOS_UINT8                           aucReserved[3];
} TAFAGENT_APS_GET_CID_PARA_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

} TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */
} TAFAGENT_MTA_GET_SYSMODE_REQ_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRet;                                  /* ???????? */
} TAFAGENT_APS_CLEAR_ERROR_CODE_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRet;                                  /* ???????? */
    TAF_PDP_PRIM_CONTEXT_STRU           stCidInfo;                     /* ????????????CID?????? */
} TAFAGENT_APS_GET_CID_PARA_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRet;                                  /* ???????? */
} TAFAGENT_APS_SET_CID_PARA_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRet;                                  /* ???????? */
    VOS_UINT8                           ucCid;                                  /* ????????CID */
    VOS_UINT8                           aucReserved[3];                         /* ?????? */
} TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU;



typedef struct
{
    MN_CALL_ID_T                        callId;                                 /* ?????????????????? */
    MN_CALL_TYPE_ENUM_U8                enCallType;                             /* ????????*/
    MN_CALL_STATE_ENUM_U8               enCallState;                            /* ????????*/
    VOS_UINT8                           aucReserved[1];                         /* ?????? */
}TAFAGERNT_MN_CALL_INFO_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT8                           ucNumOfCalls;                           /* ?????????????????? */
    VOS_UINT8                           aucReserved[3];                         /* ?????? */
    TAFAGERNT_MN_CALL_INFO_STRU         stCallInfo[MN_CALL_MAX_NUM];            /*????????????*/
}TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_SYS_MODE_STRU
 ????????  : ????????????????, ????:
             (1) RAT Type ????????
             (2) Sub Mode ??????????
*****************************************************************************/
typedef struct
{
    TAF_SYS_MODE_ENUM_UINT8             enRatType;           /* ????????   */
    TAF_SYS_SUBMODE_ENUM_UINT8          enSysSubMode;        /* ?????????? */
    VOS_UINT8                           aucReserve[2];
} TAF_AGENT_SYS_MODE_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT32                          ulRet;                                  /* ???????? */
    TAF_AGENT_SYS_MODE_STRU             stSysMode;                              /* ?????????????????????????????????? */
}TAFAGENT_MTA_GET_SYSMODE_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */

    VOS_UINT16                          usClientId;                             /* CLIENT ID */

    VOS_UINT8                           ucRsv1[2];

    TAF_PS_PDP_QOS_SET_PARA_STRU        stQosPara;
} TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */

    VOS_UINT8                           ucCid;                                  /* ????????????CID */

    VOS_UINT8                           ucRsv1[3];
} TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRet;                                  /* ???????? */
} TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRet;                                  /* ???????? */

    TAF_PS_PDP_QOS_QUERY_PARA_STRU      stQosPara;

} TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU;




typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */
} TAFAGENT_MTA_GET_ANT_STATE_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usAntState;                             /* ???????? */
    VOS_UINT8                           aucReserved1[2];

} TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU;
/*****************************************************************************
  H2ASN????????????????
*****************************************************************************/
typedef struct
{
    TAFAGENT_MSG_ID_ENUM_UINT32         ulMsgId;                                /*_H2ASN_MsgChoice_Export TAFAGENT_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAFAGENT_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_AGENT_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_AGENT_MSG_DATA                  stMsgData;
}TafAgentInterface_MSG;


/*****************************************************************************
  5 ????????
*****************************************************************************/




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

