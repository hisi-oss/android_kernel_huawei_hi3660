/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2018. All rights reserved.
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

#ifndef __ATNDISINTERFACE_H__
#define __ATNDISINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "mdrv.h"
#include "msp_at.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

#ifndef IPV4_ADDR_LEN
#define   IPV4_ADDR_LEN      4       /*IPV4????????*/
#endif

#ifndef	IPV6_ADDR_LEN
#define   IPV6_ADDR_LEN      16      /*IPV6????????*/
#endif

#define   MIN_VAL_EPSID      5
#define   MAX_VAL_EPSID      15

#define   NDIS_MSG_ID_BASE                  0x3000
#define   NDIS_MSG_ID_END                   0x3100


#define   MIN_VAL_HANDLE                  (0x5A0000)
#define   MAX_VAL_HANDLE                  (0x5A003F)

#define NDIS_INVALID_HANDLEINDEX          (0x7F)
#define NDIS_INVALID_HANDLE               (0x7FFFFFFF)
#define NDIS_INVALID_RABID                (0x7F)

#define NDIS_INVALID_SPEPORT              (0)

#define   AT_NDIS_IPV4_ADDR_LENGTH          (4)
#define   AT_NDIS_IPV6_ADDR_LENGTH          (16)
#define   AT_NDIS_MAX_PREFIX_NUM_IN_RA      (6)
#define   AT_NDIS_IPV6_IFID_LENGTH          (8)
/*****************************************************************************
 ??????    : NDIS_MSG_ID_SECTION_ENUM
 ????????  :
 ASN.1???? :
 ????????  : MSP??NDIS????????????????
*****************************************************************************/
enum NDIS_MSG_ID_SECTION_ENUM
{
    NDIS_MSG_ID_AT_TO_NDIS_BASE   = NDIS_MSG_ID_BASE,                         /*??MSP AT????NDIS??????ID????????*/

    NDIS_MSG_ID_NDIS_TO_AT_BASE   = NDIS_MSG_ID_AT_TO_NDIS_BASE + 0x20        /*??NDIS????MSP AT??????ID????????*/
};
/*****************************************************************************
 ??????    : AT_NDIS_MSG_TYPE_ENUM
 ????????  :
 ASN.1???? :
 ????????  : MSP??NDIS????????????????
*****************************************************************************/
enum AT_NDIS_MSG_TYPE_ENUM
{
    ID_AT_NDIS_PDNINFO_CFG_REQ               = (NDIS_MSG_ID_AT_TO_NDIS_BASE + 0x01), /*0x3001*/    /* _H2ASN_MsgChoice AT_NDIS_PDNINFO_CFG_REQ_STRU*/      /* MSP????PDN???? */
    ID_AT_NDIS_PDNINFO_CFG_CNF               = (NDIS_MSG_ID_NDIS_TO_AT_BASE + 0x01), /*0x3021*/    /* _H2ASN_MsgChoice AT_NDIS_PDNINFO_CFG_CNF_STRU*/      /* ???????????????? */

    ID_AT_NDIS_PDNINFO_REL_REQ               = (NDIS_MSG_ID_AT_TO_NDIS_BASE + 0x02),  /*0x3002*/   /* _H2ASN_MsgChoice  AT_NDIS_PDNINFO_REL_REQ_STRU*/      /* MSP????PDN???????????? */
    ID_AT_NDIS_PDNINFO_REL_CNF               = (NDIS_MSG_ID_NDIS_TO_AT_BASE + 0x02),  /*0x3022*/   /* _H2ASN_MsgChoice  AT_NDIS_PDNINFO_REL_CNF_STRU*/      /* ???????????????? */

    ID_AT_NDIS_MSG_TYPE_END
};
typedef VOS_UINT32 AT_NDIS_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 ??????    : OM_NDIS_KEY_EVENT_ENUM
 ????????  : ????????????????????
*****************************************************************************/
enum OM_NDIS_KEY_EVENT_ENUM
{

    NDIS_OM_PDN_INFO_CFG       = 1,
    NDIS_OM_PDN_INFO_REL
};
typedef VOS_UINT32 OM_NDIS_KEY_EVENT_ENUM_UINT32;


/*****************************************************************************
 ??????    : AT_NDIS_ENUM
 ????????  :
 ASN.1???? :
 ????????  : MSP??????????:????????????
*****************************************************************************/
enum AT_NDIS_ENUM
{
    AT_NDIS_SUCC                            = 0,
    AT_NDIS_FAIL                            = 1,
    AT_NDIS_BUTT
};
typedef VOS_UINT8   AT_NDIS_RSLT_ENUM_UINT8;

/*****************************************************************************
 ??????    : AT_NDIS_PDNCFG_CNF_TYPE
 ????????  :
 ASN.1???? :
 ????????  : NDIS??AT????PDN????????????
*****************************************************************************/
enum AT_NDIS_PDNCFG_CNF_TYPE
{
    AT_NDIS_PDNCFG_CNF_SUCC                       = 0,   /*????????*/
    AT_NDIS_PDNCFG_CNF_FAIL                       = 1,   /*????????*/
    AT_NDIS_PDNCFG_CNF_IPV4ONLY_SUCC              = 2,   /*IPV4??IPV6????????????????????IPV4????????????*/
    AT_NDIS_PDNCFG_CNF_IPV6ONLY_SUCC              = 3,   /*IPV4??IPV6????????????????????IPV6????????????*/
    AT_NDIS_PDNCFG_CNF_BUUT
};
typedef VOS_UINT8   AT_NDIS_PDNCFG_CNF_UINT8;

/*****************************************************************************
 ??????    : AT_NDIS_DHCP_INFO_TYPE
 ????????  :
 ASN.1???? :
 ????????  : AT??NDIS????????PDN????????
*****************************************************************************/
enum AT_NDIS_DHCP_INFO_TYPE_ENUM
{
    AT_NDIS_DHCP_INFO_TYPE_IPV4         = 0,     /*??????IPV4????*/
    AT_NDIS_DHCP_INFO_TYPE_IPV6         = 1,     /*??????IPV6????*/

    AT_NDIS_DHCP_INFO_TYPE_BUTT
};
typedef VOS_UINT8 AT_NDIS_DHCP_INFO_TYPE_ENUM_UINT8;

/*****************************************************************************
 ??????    : AT_NDIS_IPV4_ADDR_STRU
 ????????  :
 ASN.1???? :
 ????????  : IPV4????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucIpV4Addr[AT_NDIS_IPV4_ADDR_LENGTH];
}AT_NDIS_IPV4_ADDR_STRU;

/*****************************************************************************
 ??????    : AT_NDIS_IPV4_PDN_INFO_STRU
 ????????  :
 ASN.1???? :
 ????????  : IPV4 ????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPdnAddr         :1;
    VOS_UINT32                          bitOpDnsPrim         :1;
    VOS_UINT32                          bitOpDnsSec          :1;
    VOS_UINT32                          bitOpWinsPrim        :1;
    VOS_UINT32                          bitOpWinsSec         :1;
    VOS_UINT32                          bitOpPcscfPrim       :1;
    VOS_UINT32                          bitOpPcscfSec        :1;
    VOS_UINT32                          bitOpSpare           :25;

    AT_NDIS_IPV4_ADDR_STRU              stPDNAddrInfo;
    AT_NDIS_IPV4_ADDR_STRU              stSubnetMask;         /*????????*/
    AT_NDIS_IPV4_ADDR_STRU              stGateWayAddrInfo;    /*????*/
    AT_NDIS_IPV4_ADDR_STRU              stDnsPrimAddrInfo;    /*??DNS???? */
    AT_NDIS_IPV4_ADDR_STRU              stDnsSecAddrInfo;     /*??DNS???? */
    AT_NDIS_IPV4_ADDR_STRU              stWinsPrimAddrInfo;   /*??DNS???? */
    AT_NDIS_IPV4_ADDR_STRU              stWinsSecAddrInfo;    /*??DNS???? */
    AT_NDIS_IPV4_ADDR_STRU              stPcscfPrimAddrInfo;  /*??PCSCF???? */
    AT_NDIS_IPV4_ADDR_STRU              stPcscfSecAddrInfo;   /*??PCSCF???? */
}AT_NDIS_IPV4_PDN_INFO_STRU;

/*****************************************************************************
 ??????    : AT_NDIS_IPV6_DNS_SER_STRU
 ????????  :
 ASN.1???? :
 ????????  : IPV6 DNS????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSerNum;           /*??????????*/
    VOS_UINT8                           aucReserved[3];

    VOS_UINT8                           aucPriServer[AT_NDIS_IPV6_ADDR_LENGTH];
    VOS_UINT8                           aucSecServer[AT_NDIS_IPV6_ADDR_LENGTH];
}AT_NDIS_IPV6_DNS_SER_STRU;

/*****************************************************************************
 ??????    : AT_NDIS_IPV6_PCSCF_SER_STRU
 ????????  :
 ASN.1???? :
 ????????  : IPV6 PCSCF????????
*****************************************************************************/
typedef AT_NDIS_IPV6_DNS_SER_STRU AT_NDIS_IPV6_PCSCF_SER_STRU;

/*****************************************************************************
 ??????    : AT_NDIS_IPV6_PREFIX_STRU
 ????????  :
 ASN.1???? :
 ????????  : IPV6 ????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBitL          :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ulBitA          :1;
    VOS_UINT32                          ulBitPrefixLen  :8;
    VOS_UINT32                          ulBitRsv        :22;

    VOS_UINT32                          ulValidLifeTime;
    VOS_UINT32                          ulPreferredLifeTime;
    VOS_UINT8                           aucPrefix[AT_NDIS_IPV6_ADDR_LENGTH];
}AT_NDIS_IPV6_PREFIX_STRU;

/*****************************************************************************
 ??????    : AT_NDIS_IPV6_PDN_INFO_STRU
 ????????  :
 ASN.1???? :
 ????????  : IPV6 ????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBitOpMtu              :1;
    VOS_UINT32                          ulBitRsv1               :31;

    VOS_UINT32                          ulBitCurHopLimit        :8;
    VOS_UINT32                          ulBitM                  :1;
    VOS_UINT32                          ulBitO                  :1;
    VOS_UINT32                          ulBitRsv2               :22;

    VOS_UINT8                           aucInterfaceId[AT_NDIS_IPV6_IFID_LENGTH];
    VOS_UINT32                          ulMtu;
    VOS_UINT32                          ulPrefixNum;
    AT_NDIS_IPV6_PREFIX_STRU            astPrefixList[AT_NDIS_MAX_PREFIX_NUM_IN_RA];

    AT_NDIS_IPV6_DNS_SER_STRU           stDnsSer;
    AT_NDIS_IPV6_PCSCF_SER_STRU         stPcscfSer;
} AT_NDIS_IPV6_PDN_INFO_STRU;

/*****************************************************************************
 ??????    : AT_NDIS_PDNINFO_CFG_REQ_STRU
 ????????  :
 ASN.1???? :
 ????????  : PDN????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpIpv4PdnInfo : 1;
    VOS_UINT32                          bitOpIpv6PdnInfo : 1;
    VOS_UINT32                          bitOpSpare       : 30;

    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucRabId;            /* ?????? */
    VOS_UINT8                           aucRev[1];          /* ??????????????*/

    UDI_HANDLE                          ulHandle;           /* ????ID?????????? */

    AT_NDIS_IPV4_PDN_INFO_STRU          stIpv4PdnInfo;
    AT_NDIS_IPV6_PDN_INFO_STRU          stIpv6PdnInfo;

    VOS_UINT32                          ulMaxRxbps;         /*????????bps*/
    VOS_UINT32                          ulMaxTxbps;         /*????????bps*/

    VOS_INT32                           lSpePort;           /*SPE????*/
    VOS_UINT32                          ulIpfFlag;          
}AT_NDIS_PDNINFO_CFG_REQ_STRU;

/*****************************************************************************
 ??????    : AT_NDIS_PDNINFO_CFG_CNF_STRU
 ????????  :
 ASN.1???? :
 ????????  : PDN??????????????
*****************************************************************************/
typedef struct
{
    MODEM_ID_ENUM_UINT16                  enModemId;
    VOS_UINT8                             ucRabId;
    AT_NDIS_PDNCFG_CNF_UINT8              enResult;
    VOS_UINT8                             ucRabType;
    VOS_UINT8                             aucRsv[3];
}AT_NDIS_PDNINFO_CFG_CNF_STRU;

/*****************************************************************************
 ??????    : AT_NDIS_PDNINFO_REL_REQ_STRU
 ????????  :
 ASN.1???? :
 ????????  : PDN????????
*****************************************************************************/
typedef struct
{
    MODEM_ID_ENUM_UINT16                  enModemId;
    VOS_UINT8                             ucRabId;          /*????5-15*/
    VOS_UINT8                             ucRcv[1];
}AT_NDIS_PDNINFO_REL_REQ_STRU;

/*****************************************************************************
 ??????    : AT_NDIS_PDNINFO_REL_REQ_STRU
 ????????  :
 ASN.1???? :
 ????????  : PDN????????????
*****************************************************************************/
typedef struct
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                             ucRabId;      /*????5-15*/
    AT_NDIS_RSLT_ENUM_UINT8               enResult;
    VOS_UINT8                             ucRabType;
    VOS_UINT8                           aucRsv[3];
}AT_NDIS_PDNINFO_REL_CNF_STRU;

/*****************************************************************************
 ??????    : AT_NDIS_USBABNORMAL_IND_STRU
 ????????  :
 ASN.1???? :
 ????????  : USB??????????MSP
*****************************************************************************/
typedef struct
{
    VOS_UINT8                             aucRev[4];
}AT_NDIS_USBABNORMAL_IND_STRU;



/*

typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucSysMode;
    VOS_UINT16 usMsgSize;
    VOS_UINT32 ulMsgId;
    VOS_UINT8  pMsg[0];
} AT_FW_CMD_BINARY_MSG_STRU;
*/




#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
