

#ifndef __PLATFORM_SPEC_1102A_H__
#define __PLATFORM_SPEC_1102A_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102A_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102A_HOST))

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "oal_types.h"
#include "platform_oneimage_define.h"
/*****************************************************************************
  2 ??????
*/
/*****************************************************************************
  1.1.1 ????spec
*****************************************************************************/
/* ???????? */
#define WLAN_CHIP_VERSION           0x110202

/*????????Host??Device??????????????????????mac_xxx????????????????????????????????????*/
#define IS_HOST (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102A_HOST)
#define IS_DEVICE (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102A_DEV)

/*****************************************************************************
  1.1.2 ??Core????spec
*****************************************************************************/
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
    /* WiFi??????????CORE?????? ??1*/
    #define WLAN_FRW_MAX_NUM_CORES          1
#else
    /* WiFi????Linux????CORE?????? ??1*/
    #define WLAN_FRW_MAX_NUM_CORES          1
#endif


/*****************************************************************************
  2 WLAN ??????
*****************************************************************************/
/*****************************************************************************
  2.1 WLAN??????????spec
*****************************************************************************/
#define WLAN_SERVICE_VAP_START_ID_PER_BOARD         1               /* ??????????????board??????vap id??1???? */
#define WLAN_CHIP_MAX_NUM_PER_BOARD         1                       /* ????board????chip????????????????????????8?? */
#define WLAN_DEVICE_MAX_NUM_PER_CHIP        1                       /* ????chip????device????????????????????????8?? */
#define WLAN_MAC_DEV_MAX_CNT                1                       /* ??????????MAC???????????? */

#define WLAN_SERVICE_DEVICE_MAX_NUM_PER_CHIP        WLAN_DEVICE_MAX_NUM_PER_CHIP

#define WLAN_CHIP_DBSC_DEVICE_NUM           1

/* ????BOARD????????????device???? */
#define WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC    (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_DEVICE_MAX_NUM_PER_CHIP)

#define WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE      2   /* AP????????????????WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE????*/
#define WLAN_SERVICE_STA_MAX_NUM_PER_DEVICE     3   /* STA?????? */
#define WLAN_AP_STA_COEXIST_VAP_NUM             0   /* ap sta??????vap????,Hi1102????STA+AP?????????? */

/* PROXY STA??????VAP?????????? */
#define WLAN_PROXY_STA_MAX_NUM_PER_DEVICE              1   /* PROXY STA?????? */
#define WLAN_REPEATER_SERVICE_VAP_MAX_NUM_PER_DEVICE  (WLAN_PROXY_STA_MAX_NUM_PER_DEVICE + 1)  /* PROXY STA??????????????VAP????:PROXY STA + 1??????STA */

/* ????????????VAP???????????????????????????????????????????????????????????????????? */
//#define WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE     (OAL_MAX(WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE, WLAN_SERVICE_STA_MAX_NUM_PER_DEVICE)) /* ????VAP???? */
#define WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE     WLAN_SERVICE_STA_MAX_NUM_PER_DEVICE /* ????VAP???? */
#define WLAN_CONFIG_VAP_MAX_NUM_PER_DEVICE      1   /* ????VAP???? */

/* ????device????vap??????????=????????VAP????+????VAP???? */
/* ????????:P2P_dev/CL??STA??????????P2P_GO??AP????????
    1)AP ????:  2??ap + 1??????vap
    2)STA ????: 3??sta + 1??????vap
    3)STA+P2P????????:  1??sta + 1??P2P_dev + 1??P2P_GO/Client + 1??????vap
    4)STA+Proxy STA????????:  1??sta + 1??proxy STA + 1??????vap
*/
#define WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT      (WLAN_CONFIG_VAP_MAX_NUM_PER_DEVICE + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE) /* 3??????VAP + 1??????vap */

/* ????BOARD????????????VAP???? */
#define WLAN_VAP_SUPPORT_MAX_NUM_LIMIT      (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_DEVICE_MAX_NUM_PER_CHIP * WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT)  /* 18??:1??ap,1??sta,15??proxysta,1??????vap */

/* ????BOARD??????????????VAP?????? */
#define WLAN_SERVICE_VAP_SUPPOTR_MAX_NUM_LIMIT    (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_DEVICE_MAX_NUM_PER_CHIP * (WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT-1)) /* 20??:4??ap,1??sta,15??proxysta,*/

#define WLAN_ASSOC_USER_MAX_NUM       8  /* ?????????????????? */

#define WLAN_ACTIVE_USER_MAX_NUM      WLAN_ASSOC_USER_MAX_NUM     /* ?????????????????? = ?????????? */

/*board?????????? = (??APUT????)?????????????? + ????????????(8+1=9),???????????????????? */
#define WLAN_USER_MAX_USER_LIMIT      9

/*****************************************************************************
  2.2 WLAN??????????spec
*****************************************************************************/

/*****************************************************************************
  2.3 oam??????spec
*****************************************************************************/
#if (((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)) || (_PRE_OS_VERSION_WINDOWS == _PRE_OS_VERSION))
#define WLAN_OAM_FILE_PATH      "C:\\OAM.log"                   /* WIN32??WINDOWS??,LOG?????????????????? */
#elif ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION))
#define WLAN_OAM_FILE_PATH      "\\home\\oam.log"               /* LINUX??????????,LOG?????????????????? */
#endif

/*****************************************************************************
  2.4 mem??????spec
*****************************************************************************/
/*****************************************************************************
  2.4.1
*****************************************************************************/

#define WLAN_MEM_MAX_BYTE_LEN               (32100 + 1)   /* ???????????????????? */
#define WLAN_MAX_MAC_HDR_LEN                     36           /* ??????mac?????? oal_mem.h???????????? */

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
#define WLAN_MEM_MAX_SUBPOOL_NUM            6             /* ????????????????netbuf???????????????????????? */
#else
#define WLAN_MEM_MAX_SUBPOOL_NUM            8             /* ???????????????????????? */
#endif
#define WLAN_MEM_MAX_USERS_NUM              4             /* ?????????????????????????? */

/*****************************************************************************
  2.4.2 ????????????????????????
*****************************************************************************/
/* ????device????TID??????MPDU????????
    ????????????????????????????
*/
#define WLAN_TID_MPDU_NUM_BIT               9
#define WLAN_TID_MPDU_NUM_LIMIT             (1 << WLAN_TID_MPDU_NUM_BIT)

#define WLAN_MEM_SHARED_RX_DSCR_SIZE        68              /*??????????????????????????????????????????????????????????*/
#define WLAN_MEM_SHARED_TX_DSCR_SIZE1       88              /*??????????????????????????????????????????????????????????*/
#define WLAN_MEM_SHARED_TX_DSCR_SIZE2       88              /*??????????????????????????????????????????????????????????*/

#if defined(_PRE_DEBUG_MODE)  || defined(_PRE_WLAN_CACHE_COHERENT_SUPPORT)
#define WLAN_MEM_SHARED_RX_DSCR_CNT         110             /* ????512(????????????) + 64(????????????) */ /* ????! ??????????????????????oal_mem.c????OAL_MEM_BLK_TOTAL_CNT */
#define WLAN_MEM_SHARED_TX_DSCR_CNT1        172             /* ??????????512 */
#define WLAN_MEM_SHARED_TX_DSCR_CNT2        0               /* ????amsdu???????? */
#else
#define WLAN_MEM_SHARED_RX_DSCR_CNT         0
#define WLAN_MEM_SHARED_TX_DSCR_CNT1        0
#define WLAN_MEM_SHARED_TX_DSCR_CNT2        0
#endif
#define TOTAL_WLAN_MEM_SHARED_DSCR_SIZE     ((WLAN_MEM_SHARED_RX_DSCR_SIZE + OAL_MEM_INFO_SIZE + OAL_DOG_TAG_SIZE)*WLAN_MEM_SHARED_RX_DSCR_CNT \
                                            + (WLAN_MEM_SHARED_TX_DSCR_SIZE1 + OAL_MEM_INFO_SIZE + OAL_DOG_TAG_SIZE)*WLAN_MEM_SHARED_TX_DSCR_CNT1 \
                                            + (WLAN_MEM_SHARED_TX_DSCR_SIZE2 + OAL_MEM_INFO_SIZE + OAL_DOG_TAG_SIZE)*WLAN_MEM_SHARED_TX_DSCR_CNT2)
/*****************************************************************************
  2.4.3 ????????????????????????
*****************************************************************************/
#define WLAN_MEM_SHARED_MGMT_PKT_SIZE1      800
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#define WLAN_MEM_SHARED_MGMT_PKT_CNT1       0  /* ????????host???????? */
#else
#define WLAN_MEM_SHARED_MGMT_PKT_CNT1       1  /* ???????? UT ?????? */
#endif
#define TOTAL_WLAN_MEM_SHARED_MGMT_PKT_SIZE ((WLAN_MEM_SHARED_MGMT_PKT_SIZE1 + OAL_MEM_INFO_SIZE + OAL_DOG_TAG_SIZE)*WLAN_MEM_SHARED_MGMT_PKT_CNT1)

/*****************************************************************************
  2.4.4 ????????????????????????
*****************************************************************************/
#define WLAN_MEM_SHARED_DATA_PKT_SIZE       44              /* 80211mac???????? */
#define WLAN_MEM_SHARED_DATA_PKT_CNT        200             /* Hi1102?????????????????????????????????? */
#define TOTAL_WLAN_MEM_SHARED_DATA_PKT_SIZE ((WLAN_MEM_SHARED_DATA_PKT_SIZE + OAL_MEM_INFO_SIZE + OAL_DOG_TAG_SIZE)*WLAN_MEM_SHARED_DATA_PKT_CNT)

/*****************************************************************************
  2.4.5 ??????????????????
*****************************************************************************/
#define WLAN_MEM_LOCAL_SIZE1                32
#define WLAN_MEM_LOCAL_CNT1                 69            /* 256(32*8)??dmac_alg_tid_stru + 256??alg_tid_entry_stru + 5??????????(NON_RESET_ERR)*/

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#define WLAN_MEM_LOCAL_SIZE2                144
#define WLAN_MEM_LOCAL_CNT2                 800             /* 200(????) */
#else
#define WLAN_MEM_LOCAL_SIZE2                104
#define WLAN_MEM_LOCAL_CNT2                 50             /* 200(????) */
#endif

#define WLAN_MEM_LOCAL_SIZE3                264             /* ????hmac_vap_cfg_priv_stru??????VAP???? + ???????? FRW_EVENT_TYPE_BUTT * WLAN_VAP_SUPPORT_MAX_NUM_LIMIT  */

/* ????WL_L2_DRAM??????????????????????2??????vap???????????????????????? TBD */
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
/*??????????????????????*/
#define WLAN_MEM_LOCAL_CNT3                 (WLAN_VAP_SUPPORT_MAX_NUM_LIMIT + 60)/* ????????????????1?? +1 */
#else
/*Linux????????????????????????????????????????????*/
#define WLAN_MEM_LOCAL_CNT3                 (WLAN_VAP_SUPPORT_MAX_NUM_LIMIT + 60)
#endif

#define WLAN_MEM_LOCAL_SIZE4                512             /* ??????128???????????? */
#define WLAN_MEM_LOCAL_CNT4                 20

#define WLAN_MEM_LOCAL_SIZE5                4304
#define WLAN_MEM_LOCAL_CNT5                 64

#define WLAN_MEM_LOCAL_SIZE6                16000           /* ???????????????????? */
#define WLAN_MEM_LOCAL_CNT6                 0               /* host????????????????kmalloc????,???????????????? */

/*****************************************************************************
  2.4.6 ??????????????(????TCM??)????????
*****************************************************************************/

/*****************************************************************************
  2.4.6 ????????????????
*****************************************************************************/
#define WLAN_MEM_EVENT_SIZE1                72              /* ????: ????????????????4????IPC?????? */
#define WLAN_MEM_EVENT_SIZE2                528             /* ????: ????????????????4????IPC?????? */

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
/*??????????????????????*/
#define WLAN_MEM_EVENT_CNT1                 180
#define WLAN_MEM_EVENT_CNT2                 4

#else
/*Linux??????????????????????????????????????????*/
#define WLAN_MEM_EVENT_CNT1                 (180 * WLAN_FRW_MAX_NUM_CORES)
#define WLAN_MEM_EVENT_CNT2                 4
#endif

#define WLAN_WPS_IE_MAX_SIZE                WLAN_MEM_EVENT_SIZE2 - 32   /* 32?????????????????????? */
#ifdef _PRE_WLAN_FEATURE_HILINK
#define WLAN_OKC_IE_MAX_SIZE                WLAN_MEM_EVENT_SIZE2 - 32   /* 32?????????????????????? */
#endif
/*****************************************************************************
  2.4.7 ??????????
*****************************************************************************/
/*****************************************************************************
  2.4.8 MIB??????  TBD :??????????????????????????????????????
*****************************************************************************/
#define WLAN_MEM_MIB_SIZE1                  920           /* mib?????????? 20180508????FTM??????????864 */
#define WLAN_MEM_MIB_CNT1                   (WLAN_VAP_SUPPORT_MAX_NUM_LIMIT - 1)               /* ??????((WLAN_VAP_SUPPORT_MAX_NUM_LIMIT - 1) * 2) */ /* ????VAP????MIB */

/*****************************************************************************
  2.4.9 netbuf??????  TBD :??????????????????????????????????????
*****************************************************************************/

#if ((_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION))
#define  WLAN_MEM_NETBUF_SIZE1              180     /* ????netbufpayload???? */
#define  WLAN_MEM_NETBUF_CNT1               70     /* ????netbufpayload????2 */

#define  WLAN_MEM_NETBUF_SIZE2              800     /* ??????netbufpayload???? */
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#define  WLAN_MEM_NETBUF_CNT2               8      /* ??????netbufpayload???? 8*/
#elif (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
#define  WLAN_MEM_NETBUF_CNT2               16      /* ??????????????????????????UT??????????????????????????????UT???????????????????????????????????? */
#endif

#define  WLAN_MEM_NETBUF_SIZE3              1568    /* ????netbufpayload???? */
#define  WLAN_MEM_NETBUF_CNT3               176     /* ????netbufpayload???? */

#define  WLAN_MEM_NETBUF_SIZE4              512     /* SDT ?????????? */
#define  WLAN_MEM_NETBUF_CNT4               4       /* SDT ???????? */

#define  OAL_NETBUF_MACHDR_BYTE_LEN         64      /* netbuf mac?????? */

#define WLAN_LARGE_NETBUF_SIZE        WLAN_MEM_NETBUF_SIZE3 /* NETBUF?????????????????????????????? */
#define WLAN_MGMT_NETBUF_SIZE         WLAN_MEM_NETBUF_SIZE2 /* NETBUF???????????????????????????????? */
#define WLAN_SHORT_NETBUF_SIZE        WLAN_MEM_NETBUF_SIZE1 /* NETBUF?????????????????????????????? */
#define WLAN_SDT_NETBUF_SIZE          WLAN_MEM_NETBUF_SIZE4 /* NETBUF??????SDT???????????????????? */

#define WLAN_MAX_NETBUF_SIZE         (WLAN_LARGE_NETBUF_SIZE + WLAN_MAX_MAC_HDR_LEN)  /* netbuf?????????????? + payload */

#else
#define WLAN_MEM_NETBUF_SIZE1               0       /* ??????SKB */
#define WLAN_MEM_NETBUF_CNT1                192     /* ????????????AMSDU????????????MSDU????????????netbuf */

#ifndef _PRE_WLAN_PHY_PERFORMANCE
#define WLAN_MEM_NETBUF_SIZE2               1600    /* 1500 + WLAN_MAX_FRAME_HEADER_LEN(36) + WLAN_HDR_FCS_LENGTH(4) + (????????????,????????????????(20)) */
#define WLAN_MEM_NETBUF_CNT2                512     /* ????192(??????????) + 32(??????????) + 32(??????????) */
                                                            /* ????????wlan2wlan????????????????????????x2 */
#define WLAN_MEM_NETBUF_SIZE3               2500    /* ??????????????????skb */
#define WLAN_MEM_NETBUF_CNT3                32      /* ???????????????????? */

#else
#define WLAN_MEM_NETBUF_SIZE2               5100
#define WLAN_MEM_NETBUF_CNT2                512

#define WLAN_MEM_NETBUF_SIZE3               5100    /* ??????????????????skb */
#define WLAN_MEM_NETBUF_CNT3                32      /* ???????????????????? */
#endif

#define  WLAN_MEM_NETBUF_SIZE4              512     /* SDT ?????????? */
#define  WLAN_MEM_NETBUF_CNT4               4       /* SDT ???????? */

#define WLAN_LARGE_NETBUF_SIZE        WLAN_MEM_NETBUF_SIZE2   /* NETBUF?????????????????????????????? */
#define WLAN_MGMT_NETBUF_SIZE         WLAN_MEM_NETBUF_SIZE2   /* NETBUF???????????????????????????????? */
#define WLAN_SHORT_NETBUF_SIZE        WLAN_MEM_NETBUF_SIZE2   /* NETBUF?????????????????????????????? */
#define WLAN_MAX_NETBUF_SIZE          WLAN_LARGE_NETBUF_SIZE  /* netbuf?????????????? + payload */
#define WLAN_SDT_NETBUF_SIZE          WLAN_MEM_NETBUF_SIZE4   /* NETBUF??????SDT???????????????????? */

#endif

#define WLAN_MEM_NETBUF_ALIGN               4       /* netbuf???? */
#define WLAN_MEM_ETH_HEADER_LEN             14      /* ?????????????? */

/*****************************************************************************
  2.4.9.1 sdt netbuf??????
*****************************************************************************/

/*  sdt??????????????????????netbuf??????????????????????????????????????????send????
    ??????????????????Payload??????
*/
/************************* sdt report msg format*********************************/
/* NETLINK_HEAD     | SDT_MSG_HEAD  | Payload    | SDT_MSG_TAIL  |    pad       */
/* ---------------------------------------------------------------------------- */
/* NLMSG_HDRLEN     |    8Byte      |     ...    |   1Byte       |    ...       */
/********************************************************************************/
#define WLAN_SDT_SKB_HEADROOM_LEN       8
#define WLAN_SDT_SKB_TAILROOM_LEN       1
#define WLAN_SDT_SKB_RESERVE_LEN        (WLAN_SDT_SKB_HEADROOM_LEN + WLAN_SDT_SKB_TAILROOM_LEN)

/*
    SDT??????????????SDT??????????????????
*/
#define WLAN_MEM_SDT_NETBUF_PAYLOAD1            37          //????????????
#define WLAN_MEM_SDT_NETBUF_PAYLOAD2            100
#define WLAN_MEM_SDT_NETBUF_PAYLOAD3            512
#define WLAN_MEM_SDT_NETBUF_PAYLOAD4            1600

#define WLAN_SDT_NETBUF_MAX_PAYLOAD             WLAN_MEM_SDT_NETBUF_PAYLOAD4

#define WLAN_MEM_SDT_NETBUF_SIZE1       (WLAN_MEM_SDT_NETBUF_PAYLOAD1 + WLAN_SDT_SKB_RESERVE_LEN)
#define WLAN_MEM_SDT_NETBUF_SIZE1_CNT   250
#define WLAN_MEM_SDT_NETBUF_SIZE2       (WLAN_MEM_SDT_NETBUF_PAYLOAD2 + WLAN_SDT_SKB_RESERVE_LEN)
#define WLAN_MEM_SDT_NETBUF_SIZE2_CNT   250
#define WLAN_MEM_SDT_NETBUF_SIZE3       (WLAN_MEM_SDT_NETBUF_PAYLOAD3 + WLAN_SDT_SKB_RESERVE_LEN)
#define WLAN_MEM_SDT_NETBUF_SIZE3_CNT   250
#define WLAN_MEM_SDT_NETBUF_SIZE4       (WLAN_MEM_SDT_NETBUF_PAYLOAD4 + WLAN_SDT_SKB_RESERVE_LEN)
#define WLAN_MEM_SDT_NETBUF_SIZE4_CNT   256

#define WLAN_SDT_MSG_FLT_HIGH_THD           800
#define WLAN_SDT_MSG_QUEUE_MAX_LEN          (WLAN_MEM_SDT_NETBUF_SIZE1_CNT + \
                                                     WLAN_MEM_SDT_NETBUF_SIZE2_CNT + \
                                                     WLAN_MEM_SDT_NETBUF_SIZE3_CNT + \
                                                     WLAN_MEM_SDT_NETBUF_SIZE4_CNT - 6)  /* ????????????????????????????1000 */

/*****************************************************************************
  2.4.10 RF????????????????WLAN_SPEC
*****************************************************************************/

/*****************************************************************************
  2.4.11 TCP ACK????
*****************************************************************************/

#define DEFAULT_TX_TCP_ACK_OPT_ENABLE (OAL_FALSE)
#define DEFAULT_RX_TCP_ACK_OPT_ENABLE (OAL_FALSE)
#define DEFAULT_TX_TCP_ACK_THRESHOLD (1) /*????????ack ??????*/
#define DEFAULT_RX_TCP_ACK_THRESHOLD (1) /*????????ack ??????*/
/*****************************************************************************
  2.5 frw??????spec
*****************************************************************************/


/******************************************************************************
    ??????????????????
    ????: ????????????????????????????????????2??????????
*******************************************************************************/
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
#define FRW_EVENT_MAX_NUM_QUEUES    FRW_EVENT_TYPE_BUTT

/*Device*/
#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
#define WLAN_FRW_EVENT_CFG_TABLE \
  { /* ????????       ????????   ??????????????????????????   ???????????????? */  \
    /* HIGH_PRIO */     {   1,               32,                      0, 0}, \
    /* HOST_CRX */      {   1,                8,                      1, 0}, \
    /* HOST_DRX */      {   1,               64,                      1, 0}, \
    /* HOST_CTX */      {   1,                8,                      1, 0}, \
    /* HOST_SDT */      {   1,               64,                      1, 0}, \
    /* WLAN_CRX */      {   1,                8,                      1, 0}, \
    /* WLAN_DRX */      {   1,               64,                      1, 0}, \
    /* WLAN_CTX */      {   1,                8,                      1, 0}, \
    /* WLAN_DTX */      {   1,               64,                      1, 0}, \
    /* WLAN_TX_COMP */  {   1,               64,                      1, 0}, \
    /* TBTT */          {   1,                8,                      1, 0}, \
    /* TIMEOUT */       {   1,                2,                      1, 0}, \
    /* HMAC MISC */     {   1,                0,                      1, 0}, \
    /* DMAC MISC */     {   1,               64,                      0, 0}, \
    /*HMAC_HCC_TEST*/   {   1,               64,                      1, 0},  \
  }
#else
#define WLAN_FRW_EVENT_CFG_TABLE \
  { /* ????????       ????????   ??????????????????????????   ???????????????? */  \
    /* HIGH_PRIO */     {   1,               32,                      0, 0}, \
    /* HOST_CRX */      {   1,                8,                      1, 0}, \
    /* HOST_DRX */      {   1,               64,                      1, 0}, \
    /* HOST_CTX */      {   1,                8,                      1, 0}, \
    /* HOST_SDT */      {   1,               64,                      1, 0}, \
    /* WLAN_CRX */      {   1,                8,                      1, 0}, \
    /* WLAN_DRX */      {   1,               64,                      1, 0}, \
    /* WLAN_CTX */      {   1,                8,                      1, 0}, \
    /* WLAN_DTX */      {   1,               64,                      1, 0}, \
    /* WLAN_TX_COMP */  {   1,               64,                      1, 0}, \
    /* TBTT */          {   1,                8,                      1, 0}, \
    /* TIMEOUT */       {   1,                2,                      1, 0}, \
    /* HMAC MISC */     {   1,                0,                      1, 0}, \
    /* DMAC MISC */     {   1,               64,                      0, 0}, \
    /*HMAC_HCC_TEST*/   {   1,               64,                      1, 0}, \
  }
#endif
#else

#define FRW_EVENT_MAX_NUM_QUEUES    (FRW_EVENT_TYPE_BUTT * WLAN_VAP_SUPPORT_MAX_NUM_LIMIT)

#define WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    /* ????????       ????????   ??????????????????????????   ???????????????? */  \
    /* HIGH_PRIO */     {   1,               32,                      0, 0}, \
    /* HOST_CRX */      {   1,               64,                      1, 0}, \
    /* HOST_DRX */      {   1,               64,                      1, 0}, \
    /* HOST_CTX */      {   1,               64,                      1, 0}, \
    /* HOST_SDT */      {   1,               64,                      1, 0}, \
    /* WLAN_CRX */      {   1,               64,                      1, 0}, \
    /* WLAN_DRX */      {   1,               64,                      1, 0}, \
    /* WLAN_CTX */      {   1,               64,                      1, 0}, \
    /* WLAN_DTX */      {   1,               64,                      1, 0}, \
    /* WLAN_TX_COMP */  {   1,                0,                      1, 0}, \
    /* TBTT */          {   1,                0,                      1, 0}, \
    /* TIMEOUT */       {   1,                2,                      1, 0}, \
    /* HMAC MISC */     {   1,                0,                      1, 0}, \
    /* DMAC MISC */     {   1,               64,                      0, 0}, \
    /*HMAC_HCC_TEST*/   {   1,               128,                     1, 0},

/*Host*/
#define WLAN_FRW_EVENT_CFG_TABLE \
  { \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
  }
#endif

/*****************************************************************************
  2.8.0 ????OS????
*****************************************************************************/
/* 11i???? */
/*WPA ????????*/
#define WLAN_WPA_KEY_LEN                    32
/*WPA ????????*/
#define WLAN_WPA_SEQ_LEN                    16

/*****************************************************************************
  2.9 DFT
*****************************************************************************/
/*****************************************************************************
  2.9.0 ????
*****************************************************************************/
/*****************************************************************************
  2.9.15 WiFi????????????
*****************************************************************************/
#define WLAN_MAC_ADDR_LEN                   6           /* MAC?????????? */
#define WLAN_MAX_FRAME_HEADER_LEN           36          /* ??????MAC????????????????36??????????28 */
#define WLAN_MIN_FRAME_HEADER_LEN           10          /* ack??cts????????????10 */
#define WLAN_MAX_FRAME_LEN                  1600        /* ???????????????? */
#define WLAN_MGMT_FRAME_HEADER_LEN          24          /* ????????MAC????????????????36??????????28 */

/*****************************************************************************
  3 ????????
*****************************************************************************/

/*****************************************************************************
  4 ????????????
*****************************************************************************/


/*****************************************************************************
  5 ??????????
*****************************************************************************/


/*****************************************************************************
  6 ????????
*****************************************************************************/


/*****************************************************************************
  7 STRUCT????
*****************************************************************************/


/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/
#endif /* #if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* #ifndef __PLATFORM_SPEC_1102_H__ */



