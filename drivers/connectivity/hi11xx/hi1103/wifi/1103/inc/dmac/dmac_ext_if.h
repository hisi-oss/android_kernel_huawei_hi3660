

#ifndef __DMAC_EXT_IF_H__
#define __DMAC_EXT_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "oal_types.h"
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "oal_mm.h"
#include "oal_net.h"
#include "frw_ext_if.h"
#include "wal_ext_if.h"
#include "wlan_types.h"
#include "mac_frame.h"
#include "mac_device.h"
#include "mac_user.h"
#include "mac_vap.h"
#include "mac_data.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_EXT_IF_H

/*****************************************************************************
  2 ??????
*****************************************************************************/
#if defined (_PRE_PRODUCT_ID_HI110X_HOST) || defined (_PRE_PRODUCT_ID_HI110X_DEV)
#define DMAC_UCAST_FRAME_TX_COMP_TIMES      10          /* ????BA???????????????????????????????????? */
#else
#define DMAC_UCAST_FRAME_TX_COMP_TIMES      5           /* ????BA???????????????????????????????????? */
#endif /* _PRE_PRODUCT_ID_HI110X_DEV */

/* DMAC CB?????????????????????????? */
#define DMAC_CB_ALG_TAGS_MUCTRL_MASK        0x1         /* CB???????????????????????????????? */
#define DMAC_CB_ALG_TAGS_TIDSCH_MASK        0x2         /* CB???????????????????????????????? */

#define DMAC_BA_SEQNO_MASK                  0x0FFF      /* max sequece number */
#define DMAC_BA_MAX_SEQNO_BY_TWO            2048
#define DMAC_BA_RX_ALLOW_MIN_SEQNO_BY_TWO   64
#define DMAC_BA_RX_ALLOW_MAX_SEQNO_BY_TWO   4032

#define DMAC_BA_GREATER_THAN_SEQHI          1
#define DMAC_BA_BETWEEN_SEQLO_SEQHI         2
#define DMAC_BA_AMSDU_BACK_SUPPORTED_FLAG   1           /* BA??????AMSDU?????????? */

#define DMAC_BA_DELBA_TIMEOUT               0
#define DMAC_BATX_WIN_STALL_THRESHOLD       6

#define MAC_TX_CTL_SIZE                     OAL_NETBUF_CB_SIZE()

/* DMAC TID??TCP ACK???? */
#define DMAC_TID_TCK_ACK_PROPORTION_MAX     32
#define DMAC_TID_TCK_ACK_PROPORTION_MIN     1
#define DMAC_TID_TCK_ACK_PROPORTION_THRES   28

#define DMAC_BA_SEQ_ADD(_seq1, _seq2)       (((_seq1) + (_seq2)) & DMAC_BA_SEQNO_MASK)
#define DMAC_BA_SEQ_SUB(_seq1, _seq2)       (((_seq1) - (_seq2)) & DMAC_BA_SEQNO_MASK)
#define DMAC_BA_SEQNO_ADD(_seq1, _seq2)     (((_seq1) + (_seq2)) & DMAC_BA_SEQNO_MASK)
#define DMAC_BA_SEQNO_SUB(_seq1, _seq2)     (((_seq1) - (_seq2)) & DMAC_BA_SEQNO_MASK)

#define DMAC_BA_BMP_SIZE                    64

#define DMAC_IS_BA_INFO_PRESENT(_flags)     (_flags & BIT0)

#define DMAC_INVALID_SIGNAL_DELTA      (30)
#define DMAC_RSSI_SIGNAL_MIN           (-103)    /*?????????????? */
#define DMAC_RSSI_SIGNAL_MAX           (5)       /*?????????????? */
#define DMAC_INVALID_SIGNAL_INITIAL    (100)     /*??????????????????*/

#define MAC_INVALID_RX_BA_LUT_INDEX           HAL_MAX_RX_BA_LUT_SIZE

/* ????BA????????seq number??????????????????2?????????? */
#define DMAC_TID_MAX_BUFS       128
/* ????BA????????seq number??bitmap???????????????? */
#define DMAC_TX_BUF_BITMAP_WORD_SIZE        32
/* ????BA????????seq number??bit map?????? */
#define DMAC_TX_BUF_BITMAP_WORDS \
    ((DMAC_TID_MAX_BUFS+DMAC_TX_BUF_BITMAP_WORD_SIZE-1) / DMAC_TX_BUF_BITMAP_WORD_SIZE)

/* ???????? :  bss_info ??????AP ?????????? WPA or WPA2*/
#define DMAC_WPA_802_11I    BIT0
#define DMAC_RSNA_802_11I   BIT1

#define DMAC_TX_MAX_RISF_NUM    6
#define DMAC_TX_QUEUE_AGGR_DEPTH     2
#define DMAX_TX_QUEUE_SINGLE_DEPTH   2
#define DMAC_TX_QEUEU_MAX_PPDU_NUM   2
#define DMAC_TX_QUEUE_FAIL_CHECK_NUM    1000
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_DFT_STAT
#define DMAC_TID_STATS_INCR(_member, _cnt)      ((_member) += (_cnt))
#else
#define DMAC_TID_STATS_INCR(_member, _cnt)
#endif
#else
#define DMAC_TID_STATS_INCR(_member, _cnt)
#endif

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#define CUSTOM_MSG_DATA_HDR_LEN      (OAL_SIZEOF(custom_cfgid_enum_uint32) + OAL_SIZEOF(oal_uint32))   /*????dmac??????????????*/
#endif //#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE

#if (defined(_PRE_DEBUG_MODE) && (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE))
extern oal_uint32 g_ul_desc_addr[HAL_TX_QUEUE_BUTT];
#endif
#ifdef _PRE_WLAN_FEATURE_IP_FILTER
extern oal_uint8 g_auc_ip_filter_btable[MAC_MAX_IP_FILTER_BTABLE_SIZE];  /* rx ip???????????????? */
#endif //_PRE_WLAN_FEATURE_IP_FILTER

#define DMAC_SCAN_MAX_AP_NUM_TO_GNSS            32
#define GNSS_DMAC_SCAN_RESULTS_VALID_MS         5000

#ifdef _PRE_WLAN_FEATURE_TAS_ANT_SWITCH
#define DMAC_WLAN_EVENT_TAS_ANT_RSSI_INVALID_TYPE    OAL_RSSI_INIT_VALUE       /* ????TAS???????????????? */
#define DMAC_WLAN_EVENT_TAS_RSSI_MEASURING_TYPE      (-129)                    /* ????TAS?????????????????? */
#define DMAC_WLAN_EVENT_TAS_ANT_AVAILABLE_TYPE       (-130)                    /* ????TAS???????????????????? */
#define DMAC_WLAN_EVENT_TAS_ANT_MEASURE_TIMEOUT_TYPE (-131)                    /* ????TAS???????????????? */

#define DMAC_WLAN_TAS_RSSI_MEASURE_TIMER_PERIOD     (5000)                    /*??????????????????5s????*/
#endif

/*****************************************************************************
  3 ????????
*****************************************************************************/
/*****************************************************************************
  ??????  : dmac_tx_host_drx_subtype_enum_uint8
  ????????:
  ????????: HOST DRX??????????????
*****************************************************************************/
/* WLAN_CRX?????????? */
typedef enum
{
    DMAC_TX_HOST_DRX = 0,
    HMAC_TX_HOST_DRX = 1,

    DMAC_TX_HOST_DRX_BUTT
}dmac_tx_host_drx_subtype_enum;
typedef oal_uint8 dmac_tx_host_drx_subtype_enum_uint8;

/*****************************************************************************
  ??????  : dmac_tx_wlan_dtx_subtype_enum_uint8
  ????????:
  ????????: WLAN DTX??????????????
*****************************************************************************/
typedef enum
{
    DMAC_TX_WLAN_DTX = 0,

    DMAC_TX_WLAN_DTX_BUTT
}dmac_tx_wlan_dtx_subtype_enum;
typedef oal_uint8 dmac_tx_wlan_dtx_subtype_enum_uint8;

/*****************************************************************************
  ??????  : dmac_wlan_ctx_event_sub_type_enum_uint8
  ????????:
  ????????: WLAN CTX??????????????
*****************************************************************************/
typedef enum
{
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_MGMT    = 0,  /* ?????????? */
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_ADD_USER,
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_NOTIFY_ALG_ADD_USER,
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_DEL_USER,

    DMAC_WLAN_CTX_EVENT_SUB_TYPE_BA_SYNC,      /* ????wlan??Delba??addba rsp??????dmac?????? */
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_PRIV_REQ,     /* 11N?????????????????????? */

    DMAC_WLAN_CTX_EVENT_SUB_TYPE_SCAN_REQ,               /* ???????? */
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_SCHED_SCAN_REQ,         /* PNO???????????? */
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_RESET_PSM,              /* ???????????? ???????????????????????????? */

    DMAC_WLAN_CTX_EVENT_SUB_TYPE_JOIN_SET_REG,
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_JOIN_DTIM_TSF_REG,
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_CONN_RESULT,            /* ???????? */

    DMAC_WLAN_CTX_EVENT_SUB_TYPE_ASOC_WRITE_REG,         /* AP??????????????????SEQNUM_DUPDET_CTRL??????*/

    DMAC_WLAN_CTX_EVENT_SUB_TYPE_STA_SET_EDCA_REG,       /* STA????beacon??assoc rsp????????EDCA?????? */
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_STA_SET_DEFAULT_VO_REG, /* ????AP????WMM??????STA????????EDCA??????????????VO?????? */

    DMAC_WLAN_CTX_EVENT_SUB_TYPE_SWITCH_TO_NEW_CHAN,     /* ???????????????? */
    DMAC_WALN_CTX_EVENT_SUB_TYPR_SELECT_CHAN,            /* ???????????? */
    DMAC_WALN_CTX_EVENT_SUB_TYPR_DISABLE_TX,             /* ???????????? */
    DMAC_WALN_CTX_EVENT_SUB_TYPR_ENABLE_TX,              /* ???????????? */
    DMAC_WLAN_CTX_EVENT_SUB_TYPR_RESTART_NETWORK,        /* ????????????????BSS?????? */
#ifdef _PRE_WLAN_FEATURE_DFS
#ifdef _PRE_WLAN_FEATURE_OFFCHAN_CAC
    DMAC_WLAN_CTX_EVENT_SUB_TYPR_SWITCH_TO_OFF_CHAN,     /* ??????offchan??off-chan cac???? */
    DMAC_WLAN_CTX_EVENT_SUB_TYPR_SWITCH_TO_HOME_CHAN,    /* ????home chan */
#endif
    DMAC_WLAN_CTX_EVENT_SUB_TYPR_DFS_TEST,
    DMAC_WALN_CTX_EVENT_SUB_TYPR_DFS_CAC_CTRL_TX,        /* DFS 1min CAC??vap??????????pause????up,???????????????????????? */
#endif

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    DMAC_WLAN_CTX_EVENT_SUB_TYPR_EDCA_OPT,               /* edca?????????????????????? */
#endif
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_CALI_HMAC2DMAC,
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_DSCR_OPT,
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_CALI_MATRIX_HMAC2DMAC,
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_APP_IE_H2D,
#ifdef _PRE_WLAN_FEATURE_IP_FILTER
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_IP_FILTER,
#endif //_PRE_WLAN_FEATURE_IP_FILTER
#ifdef _PRE_WLAN_FEATURE_APF
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_APF_CMD,
#endif

#ifdef _PRE_WLAN_FEATURE_11AX
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_STA_SET_MU_EDCA_REG,       /* STA????beacon??assoc rsp????????MU EDCA?????? */
#endif
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_BUTT
}dmac_wlan_ctx_event_sub_type_enum;
typedef oal_uint8 dmac_wlan_ctx_event_sub_type_enum_uint8;

/* DMAC???? WLAN_DRX?????????? */
typedef enum
{
    DMAC_WLAN_DRX_EVENT_SUB_TYPE_RX_DATA,     /* AP????: DMAC WLAN DRX ???? */
    DMAC_WLAN_DRX_EVENT_SUB_TYPE_TKIP_MIC_FAILE,/* DMAC tkip mic faile ??????HMAC */

    DMAC_WLAN_DRX_EVENT_SUB_TYPE_BUTT
}dmac_wlan_drx_event_sub_type_enum;
typedef oal_uint8 dmac_wlan_drx_event_sub_type_enum_uint8;

/* DMAC???? WLAN_CRX?????????? */
typedef enum
{
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_INIT,      /* DMAC ?? HMAC???????????? */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_RX,        /* DMAC WLAN CRX ???? */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_DELBA,     /* DMAC??????????DELBA?? */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_EVERY_SCAN_RESULT,  /* ??????????bss?????????????? */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_SCAN_COMP,          /* DMAC??????????????HMAC */
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_OBSS_SCAN_COMP,     /* DMAC OBSS??????????????HMAC */
#endif
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_CHAN_RESULT,        /* ?????????????????????? */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_ACS_RESP,           /* DMAC ACS ????????????????????????HMAC */

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_FLOWCTL_BACKP,     /* dmac??hmac?????????????????? */
#endif
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_DISASSOC,  /* DMAC????????????????HMAC, HMAC?????????? */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_DEAUTH,    /* DMAC????????????????HMAC */

    DMAC_WLAN_CRX_EVENT_SUB_TYPR_CH_SWITCH_COMPLETE,   /* ???????????????? */
#ifdef _PRE_WLAN_FEATURE_DBAC
    DMAC_WLAN_CRX_EVENT_SUB_TYPR_DBAC,                 /* DBAC enable/disable???? */
#endif
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_BUTT
}dmac_wlan_crx_event_sub_type_enum;
typedef oal_uint8 dmac_wlan_crx_event_sub_type_enum_uint8;

/* TBTT?????????????? */
typedef enum
{
    DMAC_TBTT_EVENT_SUB_TYPE,

    DMAC_TBTT_EVENT_SUB_TYPE_BUTT
}dmac_tbtt_event_sub_type_enum;
typedef oal_uint8 dmac_tbtt_event_sub_type_enum_uint8;

/* ????HOST???????????? */
typedef enum
{
    DMAC_TO_HMAC_SYN_UP_REG_VAL = 1,//FRW_SDT_REG_EVENT_LOG_SYN_SUB_TYPE = 0
    DMAC_TO_HMAC_CREATE_BA      = 2,
    DMAC_TO_HMAC_DEL_BA         = 3,
    DMAC_TO_HMAC_SYN_CFG        = 4,
#ifdef _PRE_WLAN_CHIP_TEST_ALG
    DMAC_TO_HMAC_ALG_TEST       = 5,
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    DMAC_TO_HMAC_ALG_INFO_SYN   = 6,
    DMAC_TO_HMAC_VOICE_AGGR     = 7,
#endif
#if defined(_PRE_WLAN_FEATURE_DATA_SAMPLE) || defined(_PRE_WLAN_FEATURE_PSD_ANALYSIS)
    DMAC_TO_HMAC_SYN_UP_SAMPLE_DATA = 8,
#endif

#ifdef _PRE_WLAN_RF_AUTOCALI
    DMAC_TO_HMAC_AUTOCALI_DATA = 9,
#endif

#ifdef _PRE_WLAN_FEATURE_M2S
        DMAC_TO_HMAC_M2S_DATA = 10,
#endif

    DMAC_TO_HMAC_BANDWIDTH_INFO_SYN  = 11,  /* dmac??hmac?????????????? */
    DMAC_TO_HMAC_PROTECTION_INFO_SYN = 12, /* dmac??hmac????????mib???? */
    DMAC_TO_HMAC_CH_STATUS_INFO_SYN  = 13,  /* dmac??hmac???????????????? */

    /* ??????????????????????????????????????device????host??????????????????
       ????????????????????????????????????????????????????????????
    */
    DMAC_TO_HMAC_SYN_BUTT
}dmac_to_hmac_syn_type_enum;

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
/* hmac to dmac?????????????????????? */
typedef enum
{
    CUSTOM_CFGID_NV_ID                 = 0,
    CUSTOM_CFGID_INI_ID,
    CUSTOM_CFGID_DTS_ID,
    CUSTOM_CFGID_PRIV_INI_ID,

    CUSTOM_CFGID_BUTT,
}custom_cfgid_enum;
typedef unsigned int custom_cfgid_enum_uint32;

typedef enum
{
    CUSTOM_CFGID_INI_ENDING_ID         = 0,
    CUSTOM_CFGID_INI_FREQ_ID,
    CUSTOM_CFGID_INI_PERF_ID,
    CUSTOM_CFGID_INI_LINKLOSS_ID,
    CUSTOM_CFGID_INI_PM_SWITCH_ID,
    CUSTOM_CFGID_INI_PS_FAST_CHECK_CNT_ID,

    /* ???????? */
    CUSTOM_CFGID_PRIV_INI_RADIO_CAP_ID,
    CUSTOM_CFGID_PRIV_FASTSCAN_SWITCH_ID,
    CUSTOM_CFGID_PRIV_ANT_SWITCH_ID,
    CUSTOM_CFGID_PRIV_LINKLOSS_THRESHOLD_FIXED_ID,
    CUSTOM_CFGID_PRIV_INI_BW_MAX_WITH_ID,
    CUSTOM_CFGID_PRIV_INI_LDPC_CODING_ID,
    CUSTOM_CFGID_PRIV_INI_RX_STBC_ID,
    CUSTOM_CFGID_PRIV_INI_TX_STBC_ID,
    CUSTOM_CFGID_PRIV_INI_SU_BFER_ID,
    CUSTOM_CFGID_PRIV_INI_SU_BFEE_ID,
    CUSTOM_CFGID_PRIV_INI_MU_BFER_ID,
    CUSTOM_CFGID_PRIV_INI_MU_BFEE_ID,
    CUSTOM_CFGID_PRIV_INI_11N_TXBF_ID,
    CUSTOM_CFGID_PRIV_INI_1024_QAM_ID,
    CUSTOM_CFGID_PRIV_INI_CALI_MASK_ID,
    CUSTOM_CFGID_PRIV_CALI_DATA_MASK_ID,
    CUSTOM_CFGID_PRIV_INI_AUTOCALI_MASK_ID,
    CUSTOM_CFGID_PRIV_INI_DOWNLOAD_RATELIMIT_PPS,
    CUSTOM_CFGID_PRIV_INI_TXOPPS_SWITCH_ID,
    CUSTOM_CFGID_PRIV_INI_OVER_TEMPER_PROTECT_THRESHOLD_ID,
    CUSTOM_CFGID_PRIV_INI_TEMP_PRO_ENABLE_ID,
    CUSTOM_CFGID_PRIV_INI_TEMP_PRO_REDUCE_PWR_ENABLE_ID,
    CUSTOM_CFGID_PRIV_INI_TEMP_PRO_SAFE_TH_ID,
    CUSTOM_CFGID_PRIV_INI_TEMP_PRO_OVER_TH_ID,
    CUSTOM_CFGID_PRIV_INI_TEMP_PRO_PA_OFF_TH_ID,
    CUSTOM_CFGID_PRIV_INI_DSSS2OFDM_DBB_PWR_BO_VAL_ID,
    CUSTOM_CFGID_PRIV_INI_EVM_PLL_REG_FIX_ID,
    CUSTOM_CFGID_PRIV_INI_VOE_SWITCH_ID,
    CUSTOM_CFGID_PRIV_M2S_FUNCTION_MASK_ID,
    CUSTOM_CFGID_PRIV_INI_11AX_SWITCH_ID,
    CUSTOM_CFGID_PRIV_DYN_BYPASS_EXTLNA_ID,
    CUSTOM_CFGID_PRIV_CTRL_FRAME_TX_CHAIN_ID,
    CUSTOM_CFGID_PRIV_CTRL_UPC_FOR_18DBM_C0_ID,
    CUSTOM_CFGID_PRIV_CTRL_UPC_FOR_18DBM_C1_ID,
    CUSTOM_CFGID_PRIV_INI_LDAC_M2S_TH_ID,

    CUSTOM_CFGID_INI_BUTT,
}custom_cfgid_h2d_ini_enum;
typedef unsigned int custom_cfgid_h2d_ini_enum_uint32;

typedef struct
{
    custom_cfgid_enum_uint32            en_syn_id;      /* ????????ID*/
    oal_uint32                          ul_len;         /* DATA payload???? */
    oal_uint8                           auc_msg_body[4];/* DATA payload */
}hmac_to_dmac_cfg_custom_data_stru;
#endif //#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE

/* MISC???????? */
typedef enum
{
    DMAC_MISC_SUB_TYPE_RADAR_DETECT,
    DMAC_MISC_SUB_TYPE_DISASOC,
    DMAC_MISC_SUB_TYPE_CALI_TO_HMAC,
    DMAC_MISC_SUB_TYPE_HMAC_TO_CALI,


#ifdef _PRE_WLAN_FEATURE_ROAM
    DMAC_MISC_SUB_TYPE_ROAM_TRIGGER,
#endif //_PRE_WLAN_FEATURE_ROAM

#ifdef _PRE_SUPPORT_ACS
    DMAC_MISC_SUB_TYPE_RESCAN,
#endif

#ifdef _PRE_WLAN_ONLINE_DPD
    DMAC_TO_HMAC_DPD,
#endif

#ifdef _PRE_WLAN_FEATURE_APF
    DMAC_MISC_SUB_TYPE_APF_REPORT,
#endif

    DMAC_MISC_SUB_TYPE_BUTT
}dmac_misc_sub_type_enum;

typedef enum{
    DMAC_DISASOC_MISC_LINKLOSS             = 0,
    DMAC_DISASOC_MISC_KEEPALIVE            = 1,
    DMAC_DISASOC_MISC_CHANNEL_MISMATCH     = 2,
    DMAC_DISASOC_MISC_LOW_RSSI             = 3,
#ifdef _PRE_WLAN_FEATURE_BAND_STEERING
    DMAC_DISASOC_MISC_BSD                  = 4,
#endif
    DMAC_DISASOC_MISC_GET_CHANNEL_IDX_FAIL = 5,
#ifdef _PRE_FEATURE_FAST_AGING
    DMAC_DISASOC_MISC_FAST_AGINIG          = 6,
#endif

    DMAC_DISASOC_MISC_BUTT
}dmac_disasoc_misc_reason_enum;
typedef oal_uint16 dmac_disasoc_misc_reason_enum_uint16;


/* HMAC to DMAC???????? */
typedef enum
{
    HMAC_TO_DMAC_SYN_INIT,
    HMAC_TO_DMAC_SYN_CREATE_CFG_VAP,
    HMAC_TO_DMAC_SYN_CFG,
    HMAC_TO_DMAC_SYN_ALG,
    HMAC_TO_DMAC_SYN_REG,
#if defined(_PRE_WLAN_FEATURE_DATA_SAMPLE) || defined(_PRE_WLAN_FEATURE_PSD_ANALYSIS)
    HMAC_TO_DMAC_SYN_SAMPLE,
#endif
#ifdef _PRE_WLAN_RF_AUTOCALI
    HMAC_TO_DMAC_AUTOCALI_CMD = 7,
#endif

    HMAC_TO_DMAC_SYN_BUTT
}hmac_to_dmac_syn_type_enum;
typedef oal_uint8 hmac_to_dmac_syn_type_enum_uint8;

/* TXRX???????????????? */
typedef enum
{
    DMAC_TXRX_PASS = 0,     /* ???????? */
    DMAC_TXRX_DROP = 1,     /* ???????? */
    DMAC_TXRX_SENT = 2,     /* ???????? */
    DMAC_TXRX_BUFF = 3,     /* ???????? */

    DMAC_TXRX_BUTT
}dmac_txrx_output_type_enum;
typedef oal_uint8 dmac_txrx_output_type_enum_uint8;


/* ???????????? */
typedef enum
{
    DMAC_USER_SMARTANT_NON_TRAINING        = 0,
    DMAC_USER_SMARTANT_NULLDATA_TRAINING   = 1,
    DMAC_USER_SMARTANT_DATA_TRAINING       = 2,

    DMAC_USER_SMARTANT_TRAINING_BUTT
}dmac_user_smartant_training_enum;
typedef oal_uint8 dmac_user_smartant_training_enum_uint8;

/* ?????????????????? (??:????1102????????????????3bit????, ????????????????????7) */
typedef enum
{
    DMAC_USER_ALG_NON_PROBE                     = 0,    /* ?????????? */
    DMAC_USER_ALG_TXBF_SOUNDING                 = 1,    /* TxBf sounding???? */
    DMAC_USER_ALG_AUOTRATE_PROBE                = 2,    /* Autorate???????? */
    DMAC_USER_ALG_AGGR_PROBE                    = 3,    /* ???????????? */
    DMAC_USER_ALG_TPC_PROBE                     = 4,    /* TPC???????? */
    DMAC_USER_ALG_TX_MODE_PROBE                 = 5,    /* ????????????????(TxBf, STBC, Chain) */
    DMAC_USER_ALG_SMARTANT_NULLDATA_PROBE       = 6,    /* ????????NullData???????? */
    DMAC_USER_ALG_SMARTANT_DATA_PROBE           = 7,    /* ????????Data???????? */

    DMAC_USER_ALG_PROBE_BUTT
}dmac_user_alg_probe_enum;
typedef oal_uint8 dmac_user_alg_probe_enum_uint8;

/* BA?????????????? */
typedef enum
{
    DMAC_BA_INIT        = 0,    /* BA?????????? */
    DMAC_BA_INPROGRESS,         /* BA?????????????? */
    DMAC_BA_COMPLETE,           /* BA???????????? */
    DMAC_BA_HALTED,             /* BA???????????? */
    DMAC_BA_FAILED,             /* BA???????????? */

    DMAC_BA_BUTT
}dmac_ba_conn_status_enum;
typedef oal_uint8 dmac_ba_conn_status_enum_uint8;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/* Type of Tx Descriptor status */
typedef enum
{
      DMAC_TX_INVALID   = 0,                /*????*/
      DMAC_TX_SUCC,                         /*????*/
      DMAC_TX_FAIL,                         /*????????????????????????????????????????*/
      DMAC_TX_TIMEOUT,                      /*lifetime??????????????????*/
      DMAC_TX_RTS_FAIL,                     /*RTS ????????????????????????????cts??????*/
      DMAC_TX_NOT_COMPRASS_BA,              /*??????BA??????????????*/
      DMAC_TX_TID_MISMATCH,                 /*??????BA??TID????????????????????????TID??????*/
      DMAC_TX_KEY_SEARCH_FAIL,              /* Key search failed*/
      DMAC_TX_AMPDU_MISMATCH,               /*??????????*/
      DMAC_TX_PENDING,                      /*02:????????????pending;03:????????????pending */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
      DMAC_TX_FAIL_ACK_ERROR,               /*????????????????????????????????????????????*/
      DMAC_TX_RTS_FAIL_CTS_ERROR,           /*RTS????????????????????????????????CTS??????*/
#else
      DMAC_TX_FAIL_RESV,                    /* resv */
      DMAC_TX_FAIL_BW_TOO_BIG,              /* ????????PHY???????????????????????????????????? ???????????? */
#endif
      DMAC_TX_FAIL_ABORT,                   /*??????????????abort??*/
      DMAC_TX_FAIL_STATEMACHINE_PHY_ERROR,  /*MAC??????????????????????????????phy????????????????*/
      DMAC_TX_SOFT_PSM_BACK,                /*????????????*/
      DMAC_TX_AMPDU_BITMAP_MISMATCH,        /*????????bitmap??????mpdu????????*/
} dmac_tx_dscr_status_enum;
#else
/* Type of Tx Descriptor status */
typedef enum
{
      DMAC_TX_INVALID   = 0,
      DMAC_TX_SUCC,
      DMAC_TX_FAIL,
      DMAC_TX_TIMEOUT,
      DMAC_TX_RTS_FAIL,
      DMAC_TX_NOT_COMPRASS_BA,
      DMAC_TX_TID_MISMATCH,
      DMAC_TX_KEY_SEARCH_FAIL,
      DMAC_TX_AMPDU_MISMATCH,
      DMAC_TX_PENDING,
      DMAC_TX_SOFT_PSM_BACK,    /*????????????*/
      DMAC_TX_SOFT_RESET_BACK,  /*????RESET????*/
} dmac_tx_dscr_status_enum;
#endif
typedef oal_uint8 dmac_tx_dscr_status_enum_uint8;

typedef enum
{
    DMAC_TX_MODE_NORMAL  = 0,
    DMAC_TX_MODE_RIFS    = 1,
    DMAC_TX_MODE_AGGR    = 2,
    DMAC_TX_MODE_BUTT
}dmac_tx_mode_enum;
typedef oal_uint8 dmac_tx_mode_enum_uint8;

typedef enum
{
    DMAC_TID_PAUSE_RESUME_TYPE_BA   = 0,
    DMAC_TID_PAUSE_RESUME_TYPE_PS   = 1,
    DMAC_TID_PAUSE_RESUME_TYPE_BUTT
}dmac_tid_pause_type_enum;
typedef oal_uint8 dmac_tid_pause_type_enum_uint8;

/* ??????CB???????????????????????????????? */
typedef enum
{
    WLAN_CB_FRAME_TYPE_START   = 0,    /* cb????????????0 */
    WLAN_CB_FRAME_TYPE_ACTION  = 1,    /* action?? */
    WLAN_CB_FRAME_TYPE_DATA    = 2,    /* ?????? */
    WLAN_CB_FRAME_TYPE_MGMT    = 3,    /* ????????????p2p??????????host */

    WLAN_CB_FRAME_TYPE_BUTT
}wlan_cb_frame_type_enum;
typedef oal_uint8 wlan_cb_frame_type_enum_uint8;

/* cb????action???????????????? */
typedef enum
{
    WLAN_ACTION_BA_ADDBA_REQ  = 0,         /* ????action */
    WLAN_ACTION_BA_ADDBA_RSP,
    WLAN_ACTION_BA_DELBA,
#ifdef _PRE_WLAN_FEATURE_WMMAC
    WLAN_ACTION_BA_WMMAC_ADDTS_REQ,
    WLAN_ACTION_BA_WMMAC_ADDTS_RSP,
    WLAN_ACTION_BA_WMMAC_DELTS,
#endif
    WLAN_ACTION_SMPS_FRAME_SUBTYPE,        /* SMPS????action */
    WLAN_ACTION_OPMODE_FRAME_SUBTYPE,      /* ????????????action */
    WLAN_ACTION_P2PGO_FRAME_SUBTYPE,       /* host??????P2P go??????????discoverability request */

    WLAN_FRAME_TYPE_ACTION_BUTT
}wlan_cb_action_subtype_enum;
typedef oal_uint8 wlan_cb_frame_subtype_enum_uint8;

#ifdef _PRE_WLAN_FEATURE_BTCOEX
typedef enum
{
    BTCOEX_RX_WINDOW_SIZE_INDEX_0   = 0,
    BTCOEX_RX_WINDOW_SIZE_INDEX_1   = 1,
    BTCOEX_RX_WINDOW_SIZE_INDEX_2   = 2,
    BTCOEX_RX_WINDOW_SIZE_INDEX_3   = 3,

    BTCOEX_RX_WINDOW_SIZE_INDEX_BUTT
}btcoex_rx_window_size_index_enum;
typedef oal_uint8 btcoex_rx_window_size_index_enum_uint8;

typedef enum
{
    BTCOEX_RATE_THRESHOLD_MIN   = 0,
    BTCOEX_RATE_THRESHOLD_MAX   = 1,

    BTCOEX_RATE_THRESHOLD_BUTT
}btcoex_rate_threshold_enum;
typedef oal_uint8 btcoex_rate_threshold_enum_uint8;

typedef enum
{
    BTCOEX_RX_WINDOW_SIZE_HOLD       = 0,
    BTCOEX_RX_WINDOW_SIZE_DECREASE   = 1,
    BTCOEX_RX_WINDOW_SIZE_INCREASE   = 2,

    BTCOEX_RX_WINDOW_SIZE_BUTT
}btcoex_rx_window_size_enum;
typedef oal_uint8 btcoex_rx_window_size_enum_uint8;

typedef enum
{
    BTCOEX_RX_WINDOW_SIZE_GRADE_0   = 0,
    BTCOEX_RX_WINDOW_SIZE_GRADE_1   = 1,

    BTCOEX_RX_WINDOW_SIZE_GRADE_BUTT
}btcoex_rx_window_size_grade_enum;
typedef oal_uint8 btcoex_rx_window_size_grade_enum_uint8;

typedef enum
{
    BTCOEX_ACTIVE_MODE_A2DP      = 0,
    BTCOEX_ACTIVE_MODE_SCO       = 1,
    BTCOEX_ACTIVE_MODE_TRANSFER  = 2,

    BTCOEX_ACTIVE_MODE_BUTT
}btcoex_active_mode_enum;
typedef oal_uint8 btcoex_active_mode_enum_uint8;

typedef enum
{
    BTCOEX_RATE_STATE_H       = 0,
    BTCOEX_RATE_STATE_M       = 1,
    BTCOEX_RATE_STATE_L       = 2,
    BTCOEX_RATE_STATE_SL      = 3,

    BTCOEX_RATE_STATE_BUTT
}btcoex_rate_state_enum;
typedef oal_uint8 btcoex_rate_state_enum_uint8;
#endif

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
/* DMAC_WLAN_CRX_EVENT_SUB_TYPE_SCAN_COMP */
typedef struct
{
    dmac_disasoc_misc_reason_enum_uint16     en_disasoc_reason;
    oal_uint16                               us_user_idx;
}dmac_disasoc_misc_stru;

typedef struct
{
    oal_uint8               uc_tid_num;                         /* ??????????tid?????? */
    dmac_tx_mode_enum_uint8 en_tx_mode;                         /* ????tid?????????? */
    oal_uint8               uc_mpdu_num[DMAC_TX_QUEUE_AGGR_DEPTH];   /* ????????????????????mpdu???? */
    oal_uint16              us_user_idx;                        /* ????????tid??????????user */
#ifdef _PRE_WLAN_FEATURE_DFR
    oal_bool_enum_uint8     en_ba_is_jamed;                     /* ????BA?????????????????? */
    oal_uint8               uc_resv;
#else
    oal_uint8               auc_resv[2];
#endif
}mac_tid_schedule_output_stru;

/* DMAC??HMAC??????????WLAN DRX?????????? */
typedef struct
{
    oal_netbuf_stru        *pst_netbuf;         /* netbuf???????????? */
    oal_uint16              us_netbuf_num;      /* netbuf?????????? */
    oal_uint8               auc_resv[2];        /* ???????? */
}dmac_wlan_drx_event_stru;

/* DMAC??HMAC??????????WLAN CRX?????????? */
typedef struct
{
    oal_netbuf_stru        *pst_netbuf;         /* ????????????????netbuf */
//    oal_uint8              *puc_chtxt;          /* Shared Key????????challenge text */
}dmac_wlan_crx_event_stru;

#ifdef _PRE_WLAN_FEATURE_BTCOEX
typedef struct
{
    oal_uint16 us_user_id;
    oal_uint8  uc_ba_size;
    oal_bool_enum_uint8 en_need_delba;
}dmac_to_hmac_btcoex_rx_delba_trigger_event_stru;
#endif

typedef struct
{
    oal_uint16      us_user_index;
    oal_uint8       uc_tid;
    oal_uint8       uc_vap_id;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint8       uc_cur_protocol;
    oal_uint8       auc_reserve[3];
#endif
}dmac_to_hmac_ctx_event_stru;


typedef struct
{
    oal_uint16      us_user_index;
    oal_uint8       uc_cur_bandwidth;
    oal_uint8       uc_cur_protocol;
}dmac_to_hmac_syn_info_event_stru;

typedef struct
{
    oal_uint8       uc_vap_id;
    oal_uint8       en_voice_aggr;              /* ????????Voice???? */
    oal_uint8       auc_resv[2];
}dmac_to_hmac_voice_aggr_event_stru;

typedef struct
{
    oal_uint8                      uc_device_id;
    wlan_nss_enum_uint8            en_m2s_nss;
    wlan_m2s_type_enum_uint8       en_m2s_type;  /*0:?????? 1:??????*/
    oal_uint8                      auc_reserve[1];
}dmac_to_hmac_m2s_event_stru;

/*mic????*/
typedef struct
{
    oal_uint8                  auc_user_mac[WLAN_MAC_ADDR_LEN];
    oal_uint8                  auc_reserve[2];
    oal_nl80211_key_type       en_key_type;
    oal_int32                  l_key_id;
}dmac_to_hmac_mic_event_stru;

/*DMAC??HMAC??????????DTX?????????? */
typedef struct
{
    oal_netbuf_stru        *pst_netbuf;         /* netbuf???????????? */
    oal_uint16              us_frame_len;
    oal_uint16              us_remain;
}dmac_tx_event_stru;
/* ????MIMO??????AP??????????????hmac?????????????????? */
typedef struct
{
    oal_uint16                 us_user_id;
    mac_ap_type_enum_uint16    en_ap_type;
    oal_uint8                  auc_mac_addr[WLAN_MAC_ADDR_LEN];
    oal_uint8                  auc_resv[2];
}dmac_to_hmac_mimo_compatibility_event_stru;

typedef struct
{
    mac_channel_stru                     st_channel;
    mac_ch_switch_info_stru              st_ch_switch_info;

    oal_bool_enum_uint8                  en_switch_immediately; /* 1 - ????????  0 - ????????, ??????tbtt??????*/
    oal_bool_enum_uint8                  en_check_cac;
    oal_bool_enum_uint8                  en_dot11FortyMHzIntolerant;
    oal_uint8                            auc_resv[1];
}dmac_set_chan_stru;

typedef struct
{
    wlan_ch_switch_status_enum_uint8     en_ch_switch_status;      /* ???????????? */
    oal_uint8                            uc_announced_channel;     /* ???????? */
    wlan_channel_bandwidth_enum_uint8    en_announced_bandwidth;   /* ?????????? */
    oal_uint8                            uc_ch_switch_cnt;         /* ???????????? */
    oal_bool_enum_uint8                  en_csa_present_in_bcn;    /* Beacon????????????CSA IE */
    oal_uint8                            uc_csa_vap_cnt;           /* ????????csa??vap???? */
    wlan_csa_mode_tx_enum_uint8          en_csa_mode;
    mac_csa_flag_enum_uint8              en_csa_debug_flag;
}dmac_set_ch_switch_info_stru;

typedef struct
{
    oal_uint8                            uc_cac_machw_en;          /* 1min cac ???????????????? */
}dmac_set_cac_machw_info_stru;

#ifdef _PRE_WLAN_FEATURE_WMMAC
/*??????dmac_ctx_action_event_stru.uc_resv[2]??????dmac*/
typedef struct
{
    oal_uint8   uc_ac;
    oal_uint8   bit_psb       : 1;
    oal_uint8   bit_direction : 7;
}dmac_addts_info_stru;
#endif

/*
    (1)DMAC??HMAC??????????CTX??????ACTION??????????????????
    (2)??DMAC????????DELBA????????????????????HMAC??????????
*/
 typedef struct
 {
    mac_category_enum_uint8     en_action_category;     /* ACTION???????? */
    oal_uint8                   uc_action;              /* ????ACTION?????????????? */
    oal_uint16                  us_user_idx;
    oal_uint16                  us_frame_len;           /* ?????? */
    oal_uint8                   uc_hdr_len;             /* ???????? */
    oal_uint8                   uc_tidno;               /* tidno??????action?????? */
    oal_uint8                   uc_initiator;           /* ?????????? */

    /* ????????????req????????rsp????????????????dmac?????? */
    oal_uint8                       uc_status;              /* rsp?????????? */
    oal_uint16                      us_baw_start;           /* ?????????????? */
    oal_uint16                      us_baw_size;            /* ???????? */
    oal_uint8                       uc_ampdu_max_num;       /* BA??????????????????AMPDU?????? */
    oal_bool_enum_uint8             en_amsdu_supp;          /* ????????AMSDU */
    oal_uint16                      us_ba_timeout;          /* BA???????????????? */
    mac_back_variant_enum_uint8     en_back_var;            /* BA?????????? */
    oal_uint8                       uc_dialog_token;        /* ADDBA????????dialog token */
    oal_uint8                       uc_ba_policy;           /* Immediate=1 Delayed=0 */
    oal_uint8                       uc_lut_index;           /* LUT???? */
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* ????DELBA/DELTS????HMAC???? */
#ifdef _PRE_WLAN_FEATURE_WMMAC
    oal_uint8                       uc_tsid;                /* TS????Action??????tsid?? */
    oal_uint8                       uc_ts_dialog_token;     /* ADDTS????????dialog token */
    dmac_addts_info_stru            st_addts_info;
#endif
 }dmac_ctx_action_event_stru;

/* ????????????payload?????? */
typedef struct
{
    oal_uint16  us_user_idx;     /* ????index */
    oal_uint8   auc_user_mac_addr[WLAN_MAC_ADDR_LEN];
    oal_uint16  us_sta_aid;
    oal_uint8   auc_bssid[WLAN_MAC_ADDR_LEN];

    mac_vht_hdl_stru          st_vht_hdl;
    mac_user_ht_hdl_stru      st_ht_hdl;
    mac_ap_type_enum_uint16   en_ap_type;
    oal_int8                  c_rssi;                          /* ????bss?????????? */
    oal_uint8                 auc_rev[1];

//    oal_uint8   bit_transmit_staggered_sounding_cap : 1,
//                bit_exp_comp_feedback               : 2,
//                bit_su_beamformer_cap               : 1,                       /* SU bfer??????????AP????????????1 */
//                bit_su_beamformee_cap               : 1,                       /* SU bfee??????????STA????????????1 */
//                bit_resv                            : 3;

 //   oal_uint8   bit_num_bf_ant_supported            : 3,                       /* SU????????????NDP??Nsts????????1 */
 //               bit_num_sounding_dim                : 3,                       /* SU????????Nsts??????????????1 */
 //               bit_mu_beamformer_cap               : 1,                       /* ????????set to 0 */
//                bit_mu_beamformee_cap               : 1;                       /* ????????set to 0 */
}dmac_ctx_add_user_stru;

/* ?????????????????? */
typedef struct
{
    oal_uint16                us_user_idx;     /* ????index */
    oal_uint8                 auc_user_mac_addr[WLAN_MAC_ADDR_LEN];
    mac_ap_type_enum_uint16   en_ap_type;
    oal_uint8                 auc_resv[2];
}dmac_ctx_del_user_stru;

/* ????????????payload?????? */
typedef struct
{
    mac_scan_req_stru   *pst_scan_params;   /* ???????????????? */
}dmac_ctx_scan_req_stru;

typedef struct
{
    oal_uint8                   uc_scan_idx;
    oal_uint8                   auc_resv[3];
    wlan_scan_chan_stats_stru    st_chan_result;
}dmac_crx_chan_result_stru;

/* Update join req ???????????????????? */
typedef struct
{
    union
    {
        oal_uint8           uc_value;
        struct
        {
            oal_uint8     bit_support_11b  : 1;   /* ??AP????????11b */
            oal_uint8     bit_support_11ag : 1;  /* ??AP????????11ag */
            oal_uint8     bit_ht_capable   : 1;    /* ????????ht */
            oal_uint8     bit_vht_capable  : 1;   /* ????????vht */
            oal_uint8     bit_reserved     : 4;
        }st_capable;/* ??dmac??wlan_phy_protocol_enum???? */
    }un_capable_flag;
    oal_uint8               uc_min_rate[2];/*??????????11b??????????????????????????11ag??????????????*/
    oal_uint8               uc_reserved;
}dmac_set_rate_stru;

/* Update join req ???????????????????????? */
typedef struct
{
    oal_uint8               auc_bssid[WLAN_MAC_ADDR_LEN];    /* ??????AP??BSSID  */
    oal_uint16              us_beacon_period;
    mac_channel_stru        st_current_channel;              /* ???????????????? */
    oal_uint32              ul_beacon_filter;                /* ????beacon???????????????????? */
    oal_uint32              ul_non_frame_filter;              /* ????no_frame???????????????????? */
    oal_uint8               auc_ssid[WLAN_SSID_MAX_LEN];    /* ??????AP??SSID  */
    oal_uint8               uc_dtim_period;                 /* dtim period      */
    oal_bool_enum_uint8     en_dot11FortyMHzOperationImplemented;         /* dot11FortyMHzOperationImplemented */
    oal_uint8               auc_resv;
    dmac_set_rate_stru      st_min_rate;          /* Update join req ???????????????????? */
    mac_ap_type_enum_uint16 en_ap_type;
}dmac_ctx_join_req_set_reg_stru;

/* wait join???????????????????????? */
typedef struct
{
    oal_uint32              ul_dtim_period;                  /* dtim period */
    oal_uint32              ul_dtim_cnt;                     /* dtim count  */
    oal_uint8               auc_bssid[WLAN_MAC_ADDR_LEN];    /* ??????AP??BSSID  */
    oal_uint16              us_tsf_bit0;                     /* tsf bit0  */
}dmac_ctx_set_dtim_tsf_reg_stru;

/* wait join misc???????????????????????? */
typedef struct
{
    oal_uint32              ul_beacon_filter;                /* ????beacon???????????????????? */
}dmac_ctx_join_misc_set_reg_stru;

/* wait join???????????????????????? */
typedef struct
{
    oal_uint16             uc_user_index;                    /* user index */
    oal_uint8              auc_resv[2];
}dmac_ctx_asoc_set_reg_stru;

/* sta????edca?????????????????????? */
typedef struct
{
    oal_uint8                            uc_vap_id;
    mac_wmm_set_param_type_enum_uint8    en_set_param_type;
    oal_uint16                           us_user_index;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    wlan_mib_Dot11QAPEDCAEntry_stru      ast_wlan_mib_qap_edac[WLAN_WME_AC_BUTT];
#ifdef _PRE_WLAN_FEATURE_WMMAC
    mac_ts_info_stru                     st_ts_info[WLAN_WME_AC_BUTT];
#endif
#endif
}dmac_ctx_sta_asoc_set_edca_reg_stru;

#if 0
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
#pragma pack(push,1)
/* ????????DMAC??????HMAC??????????????????????????????????????, ??hal_rx_ctl_stru??????????????*/
typedef struct
{
    /*byte 0*/
    oal_uint8                   bit_vap_id            :5;   /* ??????5bits????RX DSCR??????????bss WLAN_HAL_OHTER_BSS_ID = 14 */
    oal_uint8                   bit_amsdu_enable      :1;
    oal_uint8                   bit_is_first_buffer   :1;
    oal_uint8                   bit_is_fragmented     :1;

    /*byte 1*/
    oal_uint8                   uc_msdu_in_buffer;

    /*byte 2*/
    oal_uint8                   bit_ta_user_idx       :5;
    oal_uint8                   bit_reserved2         :1;
    oal_uint8                   bit_reserved3         :1;
    oal_uint8                   bit_reserved4         :1;

    /*byte 3*/
    oal_uint8                   bit_mac_header_len    :6;   /* mac header???????? */
    oal_uint8                   bit_is_beacon         :1;
    oal_uint8                   bit_reserved1         :1;

    /*byte 4-5 */
    oal_uint16                  us_frame_len;               /* ?????????????????? */

    /*byte 6 */
    oal_uint8                   uc_mac_vap_id         :4;
    oal_uint8                   bit_buff_nums         :4; /* ????MPDU??????buf?? */

    /*byte 7 */
    oal_uint8                   uc_channel_number;          /* ???????????? */

}mac_rx_ctl_stru;
#pragma pack(pop)

#else
/* DMAC??????HMAC??????????????????????????????????????, ??hal_rx_ctl_stru??????????????*/
typedef struct
{
    /*word 0*/
    oal_uint8                   bit_vap_id            :5;
    oal_uint8                   bit_mgmt_to_hostapd   :1;
    oal_uint8                   bit_reserved1         :2;

    oal_uint8                   uc_msdu_in_buffer;
    oal_uint8                   bit_amsdu_enable      :1;
    oal_uint8                   bit_is_first_buffer   :1;
    oal_uint8                   bit_is_fragmented     :1;
    oal_uint8                   bit_is_beacon         :1;
    oal_uint8                   bit_buff_nums         :4;   /* ????MPDU??????buf???? */

    oal_uint8                   uc_mac_header_len;          /* mac header???????? */
    /*word 1*/
    oal_uint16                  us_frame_len;               /* ?????????????????? */
    oal_uint16                  us_da_user_idx;             /* ???????????????? */
    /*word 2*/
    oal_uint32                 *pul_mac_hdr_start_addr;     /* ??????????????????,???????? */
    /*word 3*/
    oal_uint16                  us_ta_user_idx;             /* ?????????????????? */
    oal_uint8                   uc_mac_vap_id;
    oal_uint8                   uc_channel_number;          /* ???????????? */
}mac_rx_ctl_stru;
#endif
#endif

typedef  hal_rx_ctl_stru   mac_rx_ctl_stru;

/* DMAC??????????????????????????????????????netbuf??CB????????????????48????,
   ????????????????????sdt??????????????????????????!!!!!!!!!!!!!!!!!!!!!!!!!*/
typedef struct
{
    hal_rx_ctl_stru             st_rx_info;         /* dmac????????hmac?????????? */
    hal_rx_status_stru          st_rx_status;       /* ?????????????????????? */
    hal_rx_statistic_stru       st_rx_statistic;    /* ???????????????????????? */
}dmac_rx_ctl_stru;

/* hmac to dmac???????????????? */
typedef struct
{
    wlan_cfgid_enum_uint16              en_syn_id;      /* ????????ID*/
    oal_uint16                          us_len;         /* ????payload???? */
    oal_uint8                           auc_msg_body[4];/* ????payload */
}hmac_to_dmac_cfg_msg_stru;

typedef hmac_to_dmac_cfg_msg_stru dmac_to_hmac_cfg_msg_stru;

/* HMAC??DMAC???????????? */
typedef struct
{
    wlan_cfgid_enum_uint16      en_cfgid;
    oal_uint8                   auc_resv[2];
    oal_uint32                  (*p_set_func)(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
}dmac_config_syn_stru;
typedef dmac_config_syn_stru hmac_config_syn_stru;



#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/* 1???????? */
#pragma pack(push,1)
typedef struct
{
    mac_ieee80211_frame_stru               *pst_frame_header;                           /* ??MPDU?????????? */
    oal_uint16                              us_seqnum;                                  /* ??????????????seqnum*/
    wlan_frame_type_enum_uint8              en_frame_type;                              /* ???????????????????????????? */
    oal_uint8                               bit_80211_mac_head_type     :1;             /* 0: 802.11 mac??????skb???????????????????????? 1: 802.11 mac????skb??*/
    oal_uint8                               en_res                      :7;             /* ????????4????????WDS???????? */
}mac_tx_expand_cb_stru;


/* ??????cb???? ????20????????, ????????19????; HCC[8]+PAD[1]+CB[19]+MAC HEAD[36] */
struct  mac_tx_ctl
{
    /* byte1 */
    frw_event_type_enum_uint8               bit_event_type              :5;          /* ????:FRW_EVENT_TYPE_WLAN_DTX??FRW_EVENT_TYPE_HOST_DRX??????:??????????????????????netbuf???????????? */
    oal_uint8                               bit_event_sub_type          :3;
    /* byte2-3 */
    wlan_cb_frame_type_enum_uint8           uc_frame_type;                           /* ???????????? */
    wlan_cb_frame_subtype_enum_uint8        uc_frame_subtype;                        /* ?????????????? */
    /* byte4 */
    oal_uint8                               bit_mpdu_num                :7;          /* ampdu????????MPDU????,????????????????????????-1 */
    oal_uint8                               bit_netbuf_num              :1;          /* ????MPDU??????netbuf???? *//* ??????MPDU????????NETBUF?????? */
    /* byte5-6 */
    oal_uint16                              us_mpdu_payload_len;                     /* ????MPDU????????????mac header length */
    /* byte7 */
    oal_uint8                               bit_frame_header_length     :6;          /* 51??????32 */ /* ??MPDU??802.11?????? */
    oal_uint8                               bit_is_amsdu                :1;          /* ????AMSDU: OAL_FALSE??????OAL_TRUE?? */
    oal_uint8                               bit_is_first_msdu           :1;          /* ??????????????????OAL_FALSE???? OAL_TRUE?? */
    /* byte8 */
    oal_uint8                               bit_tid                     :4;          /* dmac tx ?? tx complete ??????user???????????????????? */
    wlan_wme_ac_type_enum_uint8             bit_ac                      :3;          /* ac */
    oal_uint8                               bit_ismcast                 :1;          /* ??MPDU??????????????:OAL_FALSE??????OAL_TRUE???? */
    /* byte9 */
    oal_uint8                               bit_retried_num             :4;          /* ???????? */
    oal_uint8                               bit_mgmt_frame_id           :4;          /* wpas ????????????frame id */
    /* byte10 */
    oal_uint8                               bit_tx_user_idx             :6;          /* ??????????userindex??????bit????????????index */
    oal_uint8                               bit_roam_data               :1;          /* ?????????????????? */
    oal_uint8                               bit_is_get_from_ps_queue    :1;          /* ????????????????????MPDU???????????????????????? */
    /* byte11 */
    oal_uint8                               bit_tx_vap_index            :3;
    wlan_tx_ack_policy_enum_uint8           en_ack_policy               :3;
    oal_uint8                               bit_is_needretry            :1;
    oal_uint8                               bit_need_rsp                :1;          /* WPAS send mgmt,need dmac response tx status */
    /* byte12 */
    dmac_user_alg_probe_enum_uint8          en_is_probe_data            :3;          /* ?????????? */
    oal_uint8                               bit_is_eapol_key_ptk        :1;          /* 4 ????????????????????????EAPOL KEY ?????? */
    oal_uint8                               bit_is_m2u_data             :1;          /* ?????????????????????? */
    oal_uint8                               bit_is_large_skb_amsdu      :1;          /* ???????????????????? */
    oal_uint8                               bit_ether_head_including    :1;          /* offload??netbuf????LLC??????????etherhead */
    oal_uint8                               en_use_4_addr               :1;             /* ????????4????????WDS???????? */
    /* byte13-16 */
    oal_uint32                              ul_timestamp_us;                         /* ??????????TID????????????, ????1us???? */
    /* byte17-18 */
    oal_uint8                               uc_alg_pktno;                            /* ?????????????????????????????? */
    oal_uint8                               uc_alg_frame_tag;                        /* ???????????????????? */
    /* byte19 */
    oal_uint8                               bit_align_padding_offset    :2;
    oal_uint8                               bit_is_tcp_ack              :1;          /* ????????tcp ack */
    oal_uint8                               bit_resv                    :5;

#ifndef _PRE_PRODUCT_ID_HI110X_DEV
    /* OFFLOAD????????HOST????DEVICE??CB???? */
    mac_tx_expand_cb_stru                   st_expand_cb;
#endif
}__OAL_DECLARE_PACKED;
typedef struct mac_tx_ctl  mac_tx_ctl_stru;
#pragma pack(pop)

#else
/* netbuf????????(CB)??????????48????, ????????????????????sdt????????. */
typedef struct
{
    oal_uint8                               uc_mpdu_num;                                /* ampdu????????MPDU????,????????????????????????-1 */
    oal_uint8                               uc_netbuf_num;                              /* ????MPDU??????netbuf???? */
    oal_uint16                              us_mpdu_payload_len;                        /* ????MPDU????????????mac header length */
    oal_uint8                               uc_frame_header_length;                     /* ??MPDU??802.11?????? */

    oal_uint8                               bit_is_amsdu                :1;             /* ????AMSDU: OAL_FALSE??????OAL_TRUE?? */
    oal_uint8                               bit_ismcast                 :1;             /* ??MPDU??????????????:OAL_FALSE??????OAL_TRUE???? */
    oal_uint8                               en_use_4_addr               :1;             /* ????????4????????WDS???????? */
    oal_uint8                               bit_is_get_from_ps_queue    :1;             /* ????????????????????MPDU???????????????????????? */
    oal_uint8                               bit_is_first_msdu           :1;             /* ??????????????????OAL_FALSE???? OAL_TRUE?? */
    oal_uint8                               bit_is_m2u_data             :1;             /* ?????????????????????? */
    oal_uint8                               en__res                     :2;

    oal_uint8                               en_is_qosdata               :1;             /* ??????????????qos data */
    oal_uint8                               bit_80211_mac_head_type     :1;             /* 0: 802.11 mac??????skb???????????????????????? 1: 802.11 mac????skb??*/
    oal_uint8                               en_is_bar                   :1;
    oal_uint8                               bit_is_needretry            :1;
    oal_uint8                               en_seq_ctrl_bypass          :1;             /* ??????SN??????????????????????????(????????????QOS?????? ) */
    oal_uint8                               bit_need_rsp                :1;             /* WPAS send mgmt,need dmac response tx status */
    oal_uint8                               bit_is_eapol_key_ptk        :1;             /* 4 ????????????????????????EAPOL KEY ?????? */
    oal_uint8                               bit_roam_data               :1;

    wlan_frame_type_enum_uint8              en_frame_type;                              /* ??????????????????????... */
    mac_ieee80211_frame_stru               *pst_frame_header;                           /* ??MPDU?????????? */
    wlan_wme_ac_type_enum_uint8             uc_ac;                                      /* ac */
    oal_uint8                               uc_tid;                                     /* tid */
    frw_event_type_enum_uint8               en_event_type;                              /* ????:FRW_EVENT_TYPE_WLAN_DTX??FRW_EVENT_TYPE_HOST_DRX??????:??????????????????????netbuf???????????? */
    oal_uint8                               uc_event_sub_type;                          /* amsdu?????????? */
    wlan_tx_ack_policy_enum_uint8           en_ack_policy;                              /* ACK ???? */
    oal_uint8                               uc_tx_vap_index;
    oal_uint16                              us_tx_user_idx;                             /* dmac tx ?? tx complete ??????user???????????????????? */
    oal_uint8                               uc_retried_num;
    dmac_user_alg_probe_enum_uint8          en_is_probe_data;                           /* ???????????? */
    oal_uint16                              us_seqnum;                                  /* ??????????????seqnum*/
    hal_tx_dscr_stru                       *pst_bar_dscr;


    oal_uint8                               bit_mgmt_frame_id           :4;             /* wpas ????????????frame id */
    oal_uint8                               bit_is_large_skb_amsdu      :1;          /* ???????????????????? */
    oal_uint8                               bit_ether_head_including    :1;
    oal_uint8                               bit_reserved3               :2;

    wlan_cb_frame_type_enum_uint8           uc_frame_type;                              /* ???????????? */
    wlan_cb_frame_subtype_enum_uint8        uc_frame_subtype;                           /* ?????????????? */


    oal_uint32                              ul_timestamp_us;                            /* ??????????TID??????????????, ????1us???? */

    oal_uint32                              ul_alg_pktno;                               /* ?????????????????????????????? */
    oal_uint8                               uc_alg_frame_tag;                           /* ???????????????????? */

}mac_tx_ctl_stru;
#endif


typedef struct
{
    oal_uint32      ul_best_rate_goodput_kbps;
    oal_uint32      ul_rate_kbps;           /* ????????(????:kbps) */
    oal_uint8       uc_aggr_subfrm_size;    /* ???????????????? */
    oal_uint8       uc_per;                 /* ????????PER(????:%) */
#ifdef _PRE_WLAN_DFT_STAT
    oal_uint8       uc_best_rate_per;       /* ??????????PER(????:%) */
    oal_uint8       uc_resv[1];
#else
    oal_uint8       uc_resv[2];
#endif
}dmac_tx_normal_rate_stats_stru;

typedef struct
{
    oal_bool_enum_uint8                     in_use;                     /* ????BUF?????????? */
    oal_uint8                               uc_num_buf;                 /* MPDU?????????????????? */
    oal_uint16                              us_seq_num;                 /* MPDU???????????? */
    oal_netbuf_head_stru                    st_netbuf_head;             /* MPDU?????????????????? */
    oal_uint32                              ul_rx_time;                 /* ?????????????????? */
} dmac_rx_buf_stru;


typedef struct
{
    oal_void                               *pst_ba;
    oal_uint8                               uc_tid;
    mac_delba_initiator_enum_uint8          en_direction;
    oal_uint16                              us_mac_user_idx;
    oal_uint8                               uc_vap_id;
    oal_uint16                              us_timeout_times;
    oal_uint8                               uc_resv[1];
}dmac_ba_alarm_stru;


/* ??????????????????TID?????????????????????? */
typedef struct
{
    dmac_ba_conn_status_enum_uint8  en_ba_conn_status;    /* BA?????????? */
    oal_uint8                       uc_lut_index;         /* ??????Session H/w LUT Index */
    mac_ba_policy_enum_uint8        uc_ba_policy;         /* Immediate=1 Delayed=0 */
    oal_uint8                       resv;
}dmac_ba_rx_stru;

typedef struct
{
    oal_uint8   uc_in_use;
    oal_uint8   uc_resv[1];
    oal_uint16  us_seq_num;
    oal_void*   p_tx_dscr;
}dmac_retry_queue_stru;

typedef struct
{
    oal_uint16                      us_baw_start;           /* ??????????????MPDU???????? */
    oal_uint16                      us_last_seq_num;        /* ??????????????MPDU???????? */
    oal_uint16                      us_baw_size;            /* Block_Ack??????buffer size???? */
    oal_uint16                      us_baw_head;            /* bitmap?????????????????????????????? */
    oal_uint16                      us_baw_tail;            /* bitmap???????????????????? */
    oal_bool_enum_uint8             en_is_ba;               /* Session Valid Flag */
    dmac_ba_conn_status_enum_uint8  en_ba_conn_status;      /* BA?????????? */
    mac_back_variant_enum_uint8     en_back_var;            /* BA?????????? */
    oal_uint8                       uc_dialog_token;        /* ADDBA????????dialog token */
    oal_uint8                       uc_ba_policy;           /* Immediate=1 Delayed=0 */
    oal_bool_enum_uint8             en_amsdu_supp;          /* BLOCK ACK????AMSDU?????? */
    oal_uint8                      *puc_dst_addr;           /* BA?????????????? */
    oal_uint16                      us_ba_timeout;          /* BA???????????????? */
    oal_uint8                       uc_ampdu_max_num;       /* BA????????????????????????mpdu?????? */
    oal_uint8                       uc_tx_ba_lut;           /* BA????LUT session index */
    oal_uint16                      us_mac_user_idx;
#ifdef _PRE_WLAN_FEATURE_DFR
    oal_uint16                      us_pre_baw_start;       /* ??????????????ba??????????????ssn */
    oal_uint16                      us_pre_last_seq_num;    /* ??????????????ba??????????????lsn */
    oal_uint16                      us_ba_jamed_cnt;        /* BA?????????????? */
#else
    oal_uint8                       auc_resv[2];
#endif
    oal_uint32                      aul_tx_buf_bitmap[DMAC_TX_BUF_BITMAP_WORDS];
}dmac_ba_tx_stru;

/* 11n?????????????????????????????? */
typedef struct
{
    oal_uint8               uc_ampdu_max_num;
    oal_uint8               uc_he_ampdu_len_exponent;
    oal_uint16              us_ampdu_max_size;
    oal_uint32              ul_ampdu_max_size_vht;
}dmac_ht_handle_stru;

#ifdef _PRE_WLAN_DFT_STAT
typedef struct
{
    /* ???????? */
    oal_uint32              ul_tid_enqueue_total_cnt;            /* ?????????????? */
    oal_uint32              ul_tid_enqueue_ptr_null_cnt;         /* ?????????????????????????????? */
    oal_uint32              ul_tid_enqueue_full_cnt;             /* ???????????????????????? */
    oal_uint32              ul_tid_enqueue_head_ptr_null_cnt;    /* ?????????????????????????????? */
    oal_uint32              ul_tid_enqueue_head_full_cnt;        /* ?????????????????????????????? */

    /* ???????? */
    oal_uint32              ul_tid_dequeue_total_cnt;            /* ?????????????? */
    oal_uint32              ul_tid_dequeue_normal_cnt;           /* ??AMPDU?????????? */
    oal_uint32              ul_tid_dequeue_ampdu_cnt;            /* AMPDU???????? */

    /* ???????? */
    oal_uint32              ul_tid_video_dropped_cnt;            /* ????????????????tid?????????????? */
    oal_uint32              ul_tid_traffic_ctl_dropped_cnt;      /* ????????????????tid?????????????? */
    oal_uint32              ul_tid_txbuf_overflow_dropped_cnt;   /* ??????buf???????? */
    oal_uint32              ul_tid_dbac_reset_dropped_cnt;             /* dbac????case???????? */

    /* ???????? */
    oal_uint32              ul_tid_retry_enqueue_cnt;            /* ?????????????????? */
    oal_uint32              ul_tid_retry_dequeue_cnt;            /* ?????????????????? */
}dmac_tid_stats_stru;
#endif

#ifdef _PRE_DEBUG_MODE
typedef oam_stats_ampdu_stat_stru dmac_tid_ampdu_stat_stru;
#endif

#ifdef _PRE_WLAN_FEATURE_TCP_ACK_BUFFER
typedef struct
{
    oal_netbuf_head_stru            st_hdr;
    frw_timeout_stru                st_timer;
    oal_spin_lock_stru              st_spin_lock;
    oal_uint16                      us_tcp_ack_num;
    oal_uint8                       auc_resv[2];
}dmac_tid_tcp_ack_buf_stru;
#endif

typedef struct
{
    frw_timeout_stru                st_bar_send_timeout_timer;
}dmac_tid_rom_stru;

extern dmac_tid_rom_stru g_dmac_tid_rom[][WLAN_TID_MAX_NUM];

#define DMAC_USER_TID_STRU(_pst_tid_queue)       ((dmac_tid_rom_stru *)(((dmac_tid_stru *)_pst_tid_queue)->_rom))

typedef struct
{
    oal_uint8               uc_tid;                 /* ?????????? */
    oal_uint8               uc_is_paused;           /* TID?????????? */
    oal_uint8               uc_num_dq;              /* ????????ba???????????? */
    oal_uint8               uc_retry_num;           /* tid???????????????????? */
    oal_uint16              us_mpdu_num;            /* MPDU???? */
    oal_uint16              us_user_idx;            /* ????????MAC_RES_MAC_USER_NUM */

    oal_uint32              ul_mpdu_avg_len;        /* mpdu???????????? */
#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    oal_dlist_head_stru     st_retry_q;             /* ???????????? */
    oal_netbuf_head_stru    st_buff_head;           /* ???????????????? */
#else
    oal_dlist_head_stru     st_hdr;                 /* tid?????????? */
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
    oal_void               *p_alg_priv;             /* TID?????????????????? */
    dmac_tx_normal_rate_stats_stru st_rate_stats;   /* ???????????????????????????????? */
    dmac_ba_tx_stru        *pst_ba_tx_hdl;
    dmac_ba_rx_stru         st_ba_rx_hdl;           /* dmac rx ba info */

    dmac_ht_handle_stru     st_ht_tx_hdl;
    oal_uint8               uc_num_tx_ba;
    oal_uint8               uc_num_rx_ba;
    oal_uint8               uc_vap_id;
    dmac_tx_mode_enum_uint8 en_tx_mode;             /* ????????: rifs,aggr,normal???? */
    oal_bool_enum_uint8     en_is_delba_ing;        /* ??tid??????????delba */
    oal_uint8               uc_rx_wrong_ampdu_num;  /* ??tid??????BA??????????????????????(??????DELBA????) */
    oal_uint8               uc_tcp_ack_proportion;  /* ????tid??tck ack???????? */
    oal_uint8               uc_last_is_amsdu;       /* ????????????amsdu */

    /* ROM???????????????? */
    oal_void                           *_rom;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_DFT_STAT
    dmac_tid_stats_stru    *pst_tid_stats;           /* ??TID???????????????????????????? */
#endif
#endif
#ifdef _PRE_DEBUG_MODE
    dmac_tid_ampdu_stat_stru *pst_tid_ampdu_stat;    /* ampdu???????????????? */
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    oal_uint16             us_last_seq_frag_num;          /* ????????????QoS????seq + frag num */
    oal_uint8              auc_resv2[2];
#endif

}dmac_tid_stru;

/* ????MPDU??MSDU???????????????????????? */
typedef struct
{
    oal_netbuf_stru        *pst_curr_netbuf;              /* ??????????netbuf???? */
    oal_uint8              *puc_curr_netbuf_data;         /* ??????????netbuf??data???? */
    oal_uint16              us_submsdu_offset;            /* ??????????submsdu????????,   */
    oal_uint8               uc_msdu_nums_in_netbuf;       /* ????netbuf??????????msdu???? */
    oal_uint8               uc_procd_msdu_in_netbuf;      /* ????netbuf??????????msdu???? */
    oal_uint8               uc_netbuf_nums_in_mpdu;       /* ????MPDU??????????netbuf?????? */
    oal_uint8               uc_procd_netbuf_nums;         /* ????MPDU??????????netbuf?????? */
    oal_uint8               uc_procd_msdu_nums_in_mpdu;   /* ????MPDU??????????MSDU???? */

    oal_uint8               uc_flag;
}dmac_msdu_proc_state_stru;

/* ??????MSDU???????????????????????? */
typedef struct
{
    oal_uint8               auc_sa[WLAN_MAC_ADDR_LEN];      /* MSDU???????????? */
    oal_uint8               auc_da[WLAN_MAC_ADDR_LEN];      /* MSDU?????????????? */
    oal_uint8               auc_ta[WLAN_MAC_ADDR_LEN];      /* MSDU?????????????? */
    oal_uint8               uc_priority;
    oal_uint8               auc_resv[1];

    oal_netbuf_stru        *pst_netbuf;                     /* MSDU??????netbuf????(??????clone??netbuf) */
}dmac_msdu_stru;

/* ???????????? */
typedef enum
{
    DMAC_RESET_REASON_SW_ERR = 0,
    DMAC_RESET_REASON_HW_ERR,
    DMAC_RESET_REASON_CONFIG,
    DMAC_RETST_REASON_OVER_TEMP,
    DMAC_RESET_REASON_TX_COMP_TIMEOUT,

    DMAC_RESET_REASON_BUTT
}dmac_reset_mac_submod_enum;
typedef oal_uint8 dmac_reset_mac_submod_enum_uint8;

typedef struct
{
    hal_reset_hw_type_enum_uint8     uc_reset_type;        /*????????0|1|2|3(all|phy|mac|debug)*/
    hal_reset_mac_submod_enum_uint8  uc_reset_mac_mod;
    dmac_reset_mac_submod_enum_uint8 en_reason;
    oal_uint8 uc_reset_phy_reg;
    oal_uint8 uc_reset_mac_reg;
    oal_uint8 uc_debug_type;                              /*debug????????2????????????0|1|2(mac reg|phy reg|lut)*/
    oal_uint8 uc_reset_rf_reg;
    oal_uint8 auc_resv[1];
}dmac_reset_para_stru;

typedef struct
{
    oal_uint8 uc_reason;
    oal_uint8 uc_event;
    oal_uint8 auc_des_addr[WLAN_MAC_ADDR_LEN];
}dmac_diasoc_deauth_event;

#ifdef _PRE_DEBUG_MODE_USER_TRACK
/* ?????????????????????????? */
typedef struct
{
    oal_uint32      ul_best_rate_kbps;          /* ???????????????????? */
    oal_uint16      us_best_rate_per;           /* ??????????????????????????per */
    oal_uint8       uc_best_rate_aggr_num;      /* ????????????????????aggr */
    oal_uint8       uc_resv;
}dmac_best_rate_traffic_stat_info_stru;

typedef struct
{
    dmac_best_rate_traffic_stat_info_stru    ast_best_rate_stat[WLAN_WME_AC_BUTT];
}dmac_best_rate_stat_info_stru;
#endif

#define DMAC_QUERY_EVENT_LEN  (48)   /*?????????????? */
typedef enum
{
    OAL_QUERY_STATION_INFO_EVENT      = 1,
    OAL_ATCMDSRV_DBB_NUM_INFO_EVENT   = 2,
    OAL_ATCMDSRV_FEM_PA_INFO_EVENT    = 3,
    OAL_ATCMDSRV_GET_RX_PKCG          = 4,
    OAL_ATCMDSRV_LTE_GPIO_CHECK       = 5,
    OAL_ATCMDSRV_GET_ANT              = 6,
#ifdef _PRE_WLAN_FEATURE_SMARTANT
    OAL_ATCMDSRV_GET_ANT_INFO         = 7,
    OAL_ATCMDSRV_DOUBLE_ANT_SW        = 8,
#endif
    OAL_QUERY_EVNET_BUTT
}oal_query_event_id_enum;

typedef struct
{
    oal_uint8        query_event;
    oal_uint8        auc_query_sta_addr[WLAN_MAC_ADDR_LEN];
}dmac_query_request_event;
typedef struct
{
    oal_uint8        query_event;
    oal_int8        reserve[DMAC_QUERY_EVENT_LEN];
}dmac_query_response_event;
typedef struct
{
    oal_uint32   ul_event_para;       /*??????????????*/
    oal_uint32   ul_fail_num;
    oal_int16    s_always_rx_rssi;
    oal_uint8    uc_event_id;         /*??????*/
    oal_uint8    uc_reserved;
}dmac_atcmdsrv_atcmd_response_event;

#ifdef _PRE_WLAN_FEATURE_SMARTANT
typedef struct
{
    oal_uint8       uc_event_id;                            /*??????*/
    oal_uint8       uc_ant_type;                            //??????????????0??WIFI????????1??????????
    oal_uint8       auc_rsv[2];
    oal_uint32      ul_last_ant_change_time_ms;                //????????????????
    oal_uint32      ul_ant_change_number;                   //????????????
    oal_uint32      ul_main_ant_time_s;                       //????WIFI??????????
    oal_uint32      ul_aux_ant_time_s;                        //??????????(????????)????
    oal_uint32      ul_total_time_s;                        //WIFI????????
}dmac_atcmdsrv_ant_info_response_event;
#endif

typedef struct
{
    oal_uint8        query_event;
    oal_uint8 auc_query_sta_addr[WLAN_MAC_ADDR_LEN];/*sta mac????*/
}dmac_query_station_info_request_event;
typedef struct
{
    oal_uint8    query_event;        /* ?????? */
    oal_int8     c_signal;           /* ???????? */
    oal_uint16   us_asoc_id;         /* Association ID of the STA */
    oal_uint32   ul_rx_packets;      /* total packets received */
    oal_uint32   ul_tx_packets;      /* total packets transmitted */
    oal_uint32   ul_rx_bytes;        /* total bytes received     */
    oal_uint32   ul_tx_bytes;        /* total bytes transmitted  */
    oal_uint32   ul_tx_retries;      /* ???????????? */
    oal_uint32   ul_rx_dropped_misc; /* ???????????? */
    oal_uint32   ul_tx_failed;       /* ???????????? */
    oal_int16    s_free_power;       /* ???? */
    oal_uint16   s_chload;          /* ????????????*/

    station_info_extend_stru    st_station_info_extend;
    mac_rate_info_stru st_txrate;    /*vap????????*/
}dmac_query_station_info_response_event;

typedef struct
{
    oal_uint8   uc_p2p0_hal_vap_id;
    oal_uint8   uc_p2p_gocl_hal_vap_id;
    oal_uint8   uc_rsv[2];
}mac_add_vap_sync_data_stru;

typedef struct
{
    oal_uint32  ul_cycles;              /* ?????????????????? */
    oal_uint32  ul_sw_tx_succ_num;     /* ????????????????ppdu???? */
    oal_uint32  ul_sw_tx_fail_num;     /* ????????????????ppdu???? */
    oal_uint32  ul_sw_rx_ampdu_succ_num;     /* ??????????????????ampdu???? */
    oal_uint32  ul_sw_rx_mpdu_succ_num;      /* ??????????????????mpdu???? */
    oal_uint32  ul_sw_rx_ppdu_fail_num;      /* ??????????????????ppdu???? */
    oal_uint32  ul_hw_rx_ampdu_fcs_fail_num;   /* ????????????ampdu fcs???????????? */
    oal_uint32  ul_hw_rx_mpdu_fcs_fail_num;    /* ????????????mpdu fcs???????????? */
}dmac_thruput_info_sync_stru;

typedef struct
{
    oal_uint32                   uc_dscr_status;
    oal_uint8                   mgmt_frame_id;
    oal_uint8                   auc_resv[1];
    oal_uint16                  us_user_idx;
}dmac_crx_mgmt_tx_status_stru;

#ifdef _PRE_WLAN_FEATURE_M2S
typedef struct
{
    wlan_m2s_mgr_vap_stru            ast_m2s_comp_vap[WLAN_SERVICE_STA_MAX_NUM_PER_DEVICE];
    oal_uint8                        uc_m2s_state;                         /* ????m2s???? */
    union
    {
        struct
        {
            oal_bool_enum_uint8      en_m2s_result;
            oal_uint8                uc_m2s_mode;                          /* ???????????? */
            oal_uint8                uc_vap_num;
        }mss_result;

        struct
        {
            oal_bool_enum_uint8  en_arp_detect_on;
        }arp_detect_result;
    }pri_data;
}dmac_m2s_complete_syn_stru;
#endif

#ifdef _PRE_WLAN_FEATURE_TAS_ANT_SWITCH
typedef struct
{
    oal_int32                       l_core_idx;
    oal_int32                       l_rssi;
    oal_int32                       aul_rsv[4];
}dmac_tas_rssi_notify_stru;
#endif

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
typedef struct
{
    oal_uint32           ul_chan_report_for_te_a;  /* Channel Bit Map to register TE-A */
    oal_bool_enum_uint8  en_te_b;                  /* 20/40M intolerant for TE-B */
}dmac_obss_te_a_b_stru;
#endif


#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
typedef enum
{
    DMAC_CONFIG_IPV4 = 0,                /* ????IPv4???? */
    DMAC_CONFIG_IPV6,                    /* ????IPv6???? */
    DMAC_CONFIG_BUTT
}dmac_ip_type;
typedef oal_uint8 dmac_ip_type_enum_uint8;

typedef enum
{
    DMAC_IP_ADDR_ADD = 0,                /* ????IP???? */
    DMAC_IP_ADDR_DEL,                    /* ????IP???? */
    DMAC_IP_OPER_BUTT
}dmac_ip_oper;
typedef oal_uint8 dmac_ip_oper_enum_uint8;

typedef struct
{
    dmac_ip_type_enum_uint8           en_type;
    dmac_ip_oper_enum_uint8           en_oper;

    oal_uint8                         auc_resv[2];

    oal_uint8                         auc_ip_addr[OAL_IP_ADDR_MAX_SIZE];
    oal_uint8                         auc_mask_addr[OAL_IP_ADDR_MAX_SIZE];
}dmac_ip_addr_config_stru;
#endif


/* ???????????????? */
typedef enum
{
    DMAC_RX_FRAME_CTRL_GOON,        /* ???????????????????? */
    DMAC_RX_FRAME_CTRL_DROP,        /* ???????????????? */
    DMAC_RX_FRAME_CTRL_BA_BUF,      /* ??????????BA???????? */

    DMAC_RX_FRAME_CTRL_BUTT
}dmac_rx_frame_ctrl_enum;
typedef oal_uint8 dmac_rx_frame_ctrl_enum_uint8;

#if defined(_PRE_WLAN_FEATURE_DATA_SAMPLE) || defined(_PRE_WLAN_FEATURE_PSD_ANALYSIS)
typedef enum
{
    DMAC_RX_SAMPLE,           /* DMAC???????????? */
    DMAC_RX_PSD,              /* DMAC????PSD???? */
    DMAC_RX_BUTT
}dmac_rx_sdt_sample_enum;
typedef oal_uint8 dmac_rx_sdt_sample_enum_uint8;
typedef struct
{
    oal_uint32      ul_type;
    oal_uint32      ul_reg_num;
    oal_uint32      ul_count;
    oal_uint32      ul_event_data;
}dmac_sdt_sample_frame_stru;
#endif
#ifdef _PRE_WLAN_RF_AUTOCALI
typedef enum
{
    AUTOCALI_DATA,            /*????????????????*/
    AUTOCALI_ACK,             /*??????????????????*/
    AUTOCALI_SWITCH,          /*??????????????????*/
}dmac_sdt_autocali_msg_type;
typedef struct
{
    oal_uint32      ul_type;
    oal_uint8       auc_msg_data[4];
}dmac_sdt_autocali_frame_stru;
#endif

#ifdef _PRE_WLAN_11K_STAT
#define DMAC_STAT_TX_DELAY_HIST_BIN_NUM                  6
/*dot11MACStatistics Group*/
typedef struct
{
    oal_uint32              ul_tx_retry_succ_msdu_num;          /*????????????????????MSDU????*/
    oal_uint32              ul_tx_multi_retry_succ_msud_num;    /*??????????????MSDU???? */
    oal_uint32              ul_rx_dup_frm_num;                  /*????????????*/
    oal_uint32              ul_rts_suc_num;                     /*RTS????????????*/
    oal_uint32              ul_rts_fail_num;                    /*RTS????????????*/
    oal_uint32              ul_ack_fail_mpdu_num;               /*??????ACK??MPDU????*/
}dmac_stat_mac_stat_stru;

/* user statistics */
typedef struct
{
    oal_uint32              ul_tx_frag_mpdu_num;                /*??????????????MPDU????*/
    oal_uint32              ul_tx_fail_msdu_num;                /*??????????????????????MSDU????*/
    dmac_stat_mac_stat_stru st_stat_mac_stat;
    oal_uint32              ul_rx_frag_mpdu_num;                /*??????????MPDU????*/
    oal_uint32              ul_tx_succ_msdu_num;                /*??????????MSDU????*/
    oal_uint32              ul_tx_discard_msdu_num;            /*??????MSDU????*/
    oal_uint32              ul_rx_mpdu_num;                    /*??????MPDU????*/
    oal_uint32              ul_rx_retry_mpdu_num;              /*??????????MPDU????*/
    oal_uint32              ul_rx_fail_num;
    oal_uint32              ul_tx_succ_bytes;                  /*tx succ????*/
    oal_uint32              ul_rx_succ_bytes;                  /*rx succ????*/
    oal_uint32              ul_tx_fail_bytes;                  /*tx fail????*/
    oal_uint32              ul_rx_fail_bytes;                  /*rx fail????*/
    oal_uint32              ul_forward_num;
    oal_uint32              ul_forward_bytes;                  /*forward????*/
}dmac_stat_count_tid_stru;

/*dot11Counters Group*/
typedef struct
{
    oal_uint32              ul_tx_frag_mpdu_num;                /*??????????????MPDU????*/
    oal_uint32              ul_tx_multicast_msdu_num;           /*??????????????MSDU????*/
    oal_uint32              ul_tx_fail_msdu_num;                /*??????????????????????MSDU????*/
    oal_uint32              ul_rx_frag_mpdu_num;                /*??????????MPDU????*/
    oal_uint32              ul_rx_msdu_num;                     /*??????MPDU????*/
    oal_uint32              ul_rx_multicast_msdu_num;           /*??????????MPDU????*/
    oal_uint32              ul_fcs_err_mpdu_num;                /*????????????*/
    oal_uint32              ul_tx_succ_msdu_num;                /*??????????MSDU????*/
#ifdef _PRE_WLAN_FEATURE_HILINK_HERA_PRODUCT
    oal_uint32              ul_tx_mcast_bytes;                  /* ??????????????????:  */
    oal_uint32              ul_rx_mcast_bytes;                  /* ??????????????????:  */
    oal_uint32              aul_sta_tx_mcs_cnt[16];
    oal_uint32              aul_sta_rx_mcs_cnt[16];
#endif
}dmac_stat_count_mpdu_stru;

typedef struct
{
    oal_uint32                  ul_tx_frag_mpdu_num;                /*??????????????MPDU????*/
    oal_uint32                  ul_tx_multicast_mpdu_num;           /*??????????????MSDU????*/
    oal_uint32                  ul_tx_fail_mpdu_num;                /*??????????????????????MSDU????*/
    oal_uint32                  ul_rx_frag_mpdu_num;                /*??????????MPDU????*/
    oal_uint32                  ul_rx_multicast_mpdu_num;           /*??????MPDU????*/
    oal_uint32                  ul_fcs_err_mpdu_num;                /*????????????*/
    oal_uint32                  ul_tx_succ_mpdu_num;                /*??????????MSDU????*/
    oal_uint32                  ul_tx_retry_succ_mpdu_num;          /*????????????????????MSDU????*/
    oal_uint32                  ul_tx_multi_retry_succ_mpdu_num;    /*??????????????MSDU???? */
    oal_uint32                  ul_rx_dup_frm_num;                  /*????????????*/
    oal_uint32                  ul_rts_suc_num;                     /*RTS????????????*/
    oal_uint32                  ul_rts_fail_num;                    /*RTS????????????*/
    oal_uint32                  ul_ack_fail_mpdu_num;               /*??????ACK??MPDU????*/

    oal_uint32                  ul_tx_discard_mpdu_num;            /*??????MSDU????*/
    oal_uint32                  ul_rx_mpdu_num;                    /*??????MPDU????*/
    oal_uint32                  ul_rx_retry_mpdu_num;              /*??????????MPDU????*/
}dmac_stat_count_common_stru;

/*dot11CountersGroup3 (A-MSDU):*/
typedef struct
{
    oal_uint32              ul_tx_succ_num;                         /*??????????AMSDU????*/
    oal_uint32              ul_tx_fail_num;                         /*??????????????????????AMSDU????*/
    oal_uint32              ul_tx_retry_succ_num;                   /*????????????????????AMSDU????*/
    oal_uint32              ul_tx_multi_retry_succ_num;             /*??????????????AMSDU???? */
    oal_uint64              ull_tx_succ_octets_num;                 /*??????????AMSDU??????octets????*/
    oal_uint32              ul_ack_fail_num;                        /*??????ACK??AMSUD????*/
    oal_uint32              ul_rx_num;                              /*??????AMSUD????*/
    oal_uint64              ull_rx_octets_num;                       /*??????AMSUD??????octets????*/
}dmac_stat_count_amsdu_stru;

/*dot11CountersGroup3 (A-MPDU)*/
typedef struct
{
    oal_uint32              ul_tx_num;                              /*??????AMPDU????*/
    oal_uint32              ul_tx_mpdu_num;                         /*??????AMPDU??MDPU????*/
    oal_uint64              ull_tx_octets_num;                      /*??????AMPDU??????octets????*/
    oal_uint32              ul_rx_num;                              /*??????AMPDU????*/
    oal_uint32              ul_rx_mpdu_num;                         /*??????AMPDU??MPDU????*/
    oal_uint64              ull_rx_octets_num;                      /*??????AMPDU??????octets????*/
    //oal_uint32              ul_rx_mpdu_delimiter_crc_err;         /*MPDU???????????? mac????????*/
}dmac_stat_count_ampdu_stru;

/*device, vap, use statistic structure*/
typedef struct
{
    dmac_stat_count_mpdu_stru           st_count_mpdu;
    dmac_stat_mac_stat_stru             st_mac_stat;
    dmac_stat_count_amsdu_stru          st_count_amsdu;
    dmac_stat_count_ampdu_stru          st_count_ampdu;

    oal_uint32                          aul_tx_dropped[WLAN_TIDNO_BUTT];
}dmac_stat_count_stru;

/*tid queue delay*/
typedef struct
{
    oal_uint64              ull_queue_delay_sum;                 /*TID??????????????????*/
    oal_uint32              ul_queue_delay_cnt;                 /*TID dely??????????*/
}dmac_stat_tid_queue_delay_stru;

/*tid tx delay*/
typedef struct
{
    oal_uint64              ull_tx_delay_sum;                    /*????????:TID??????????????????????????????????*/
    oal_uint32              ul_tx_delay_cnt;                    /*tx delay??????????*/
    oal_uint32              ul_max_tx_delay;                    /*????????????*/
    oal_uint32              ul_min_tx_delay;                    /*????????????*/
}dmac_stat_tid_tx_delay_stru;

/*tid tx delay hist*/
typedef struct
{
    oal_uint32              auc_tx_delay_hist_bin[DMAC_STAT_TX_DELAY_HIST_BIN_NUM];   /*delay??????????????*/
    oal_uint8               uc_tx_delay_hist_flag;                                    /*????????delay??????*/
    oal_uint8               uc_tidno;
    oal_uint16              aus_hist_range[DMAC_STAT_TX_DELAY_HIST_BIN_NUM];           /*delay??????????????*/
}dmac_stat_tid_tx_delay_hist_stru;

/*frame report*/
typedef struct
{
    oal_uint32                              ul_sum_rcpi;
    oal_uint8                               uc_last_rcpi;
    oal_uint8                               uc_avrg_rcpi;
    oal_uint8                               uc_last_rsni;
    oal_uint8                               auc_res[1];
    oal_uint32                              ul_rx_mag_data_frm_num;
}dmac_stat_frm_rpt_stru;

/*tsc report*/
typedef struct
{
    dmac_stat_tid_queue_delay_stru          ast_tid_queue_delay[WLAN_TIDNO_BUTT];
    dmac_stat_tid_tx_delay_hist_stru        st_tid_tx_delay_hist;
}dmac_stat_tsc_rpt_stru;

typedef struct
{
    oal_uint32  bit_enable                         : 1,
                bit_count                          : 1,
                bit_tid_count                      : 1,
                bit_tid_tx_delay                   : 1,
                bit_tsc_rpt                        : 1,
                bit_frm_rpt                        : 1,
                bit_user_tid_count                 : 1,
                bit_resv                           : 25;
}dmac_stat_cap_flag_stru;
#endif

#ifdef _PRE_WLAN_FEATURE_APF
typedef struct
{
    oal_void         *p_program;         /* netbuf???????????? */
    oal_uint16        us_program_len;
}dmac_apf_report_event_stru;
#endif

#ifdef _PRE_WLAN_FEATURE_GNSS_SCAN
#pragma pack(1)
/* scan parameter */
typedef struct
{
    oal_uint8                           uc_chan_number;     /* ??20MHz?????? */
    wlan_channel_band_enum_uint8        en_band;            /* ???? */
}gnss_scan_channel_stru;

typedef struct
{
    oal_uint8              uc_ch_valid_num;
    gnss_scan_channel_stru ast_wlan_channel[WLAN_MAX_CHANNEL_NUM];
} dmac_gscan_params_stru;

/* scan results */
typedef struct
{
    oal_uint8   auc_bssid[WLAN_MAC_ADDR_LEN];   /* ????bssid */
    oal_uint8   uc_channel_num;
    oal_int8    c_rssi;                       /* bss?????????? */
    oal_uint8   uc_serving_flag;
    oal_uint8   uc_rtt_unit;
    oal_uint8   uc_rtt_acc;
    oal_uint32  ul_rtt_value;
}wlan_ap_measurement_info_stru;

/* Change Feature: ??????GNSS??????????????????????DMAC???????????????????? */
typedef struct
{
    oal_uint8   auc_bssid[WLAN_MAC_ADDR_LEN];   /* ????bssid */
    oal_uint8   uc_channel_num;
    oal_int8    c_rssi;                       /* bss?????????? */
}wlan_ap_report_info_stru;

/* ??????gnss???????????????? */
typedef struct
{
    oal_uint32                     ul_interval_from_last_scan;
    oal_uint8                      uc_ap_valid_number;
    wlan_ap_report_info_stru       ast_wlan_ap_measurement_info[DMAC_SCAN_MAX_AP_NUM_TO_GNSS];
}dmac_gscan_report_info_stru;
#pragma pack()

extern dmac_gscan_params_stru         g_st_gnss_scan_params;
extern dmac_gscan_report_info_stru    g_st_gnss_scan_result_info;

typedef struct
{
    oal_dlist_head_stru            st_entry;                    /* ???????? */
    wlan_ap_measurement_info_stru  st_wlan_ap_measurement_info; /*????gnss?????????? */
}dmac_scanned_bss_info_stru;

typedef struct
{
    oal_uint32                     ul_scan_end_timstamps;/* ????????????????????,????????????????,??????????ap???????? */
    oal_dlist_head_stru            st_dmac_scan_info_list;
    oal_dlist_head_stru            st_scan_info_res_list;  /* ???????????????????? */
    dmac_scanned_bss_info_stru     ast_scan_bss_info_member[DMAC_SCAN_MAX_AP_NUM_TO_GNSS];
}dmac_scan_for_gnss_stru;
#endif

/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/
#define HMAC_TO_DMAC_CFG_MSG_HDR_LEN  (OAL_SIZEOF(hmac_to_dmac_cfg_msg_stru) - 4)   /* ??????????????????4????auc_msg_body???? */

/* 1us???? */
#define DMAC_TIME_USEC_INT64(_pst_time) \
    ((oal_int64)((_pst_time)->i_sec) * 1000000 + (oal_int64)((_pst_time)->i_usec))

/* ??????offload??????CB???? */
#define MAC_GET_CB_IS_4ADDRESS(_pst_tx_ctrl)             ((_pst_tx_ctrl)->en_use_4_addr)
#define MAC_GET_CB_IS_AMSDU(_pst_tx_ctrl)                ((_pst_tx_ctrl)->bit_is_amsdu)
#define MAC_GET_CB_IS_LARGE_SKB_AMSDU(_pst_tx_ctrl)      ((_pst_tx_ctrl)->bit_is_large_skb_amsdu)
#define MAC_GET_CB_HAS_EHTER_HEAD(_pst_tx_ctrl)          ((_pst_tx_ctrl)->bit_ether_head_including)
#define MAC_GET_CB_IS_FIRST_MSDU(_pst_tx_ctrl)           ((_pst_tx_ctrl)->bit_is_first_msdu)
#define MAC_GET_CB_IS_NEED_RESP(_pst_tx_ctrl)            ((_pst_tx_ctrl)->bit_need_rsp)
#define MAC_GET_CB_IS_EAPOL_KEY_PTK(_pst_tx_ctrl)        ((_pst_tx_ctrl)->bit_is_eapol_key_ptk)
#define MAC_GET_CB_IS_ROAM_DATA(_pst_tx_ctrl)            ((_pst_tx_ctrl)->bit_roam_data)
#define MAC_GET_CB_IS_FROM_PS_QUEUE(_pst_tx_ctrl)        ((_pst_tx_ctrl)->bit_is_get_from_ps_queue)
#define MAC_GET_CB_IS_MCAST(_pst_tx_ctrl)                ((_pst_tx_ctrl)->bit_ismcast)
#define MAC_GET_CB_IS_NEEDRETRY(_pst_tx_ctrl)            ((_pst_tx_ctrl)->bit_is_needretry)
#define MAC_GET_CB_IS_PROBE_DATA(_pst_tx_ctrl)           ((_pst_tx_ctrl)->en_is_probe_data)
#define MAC_GET_CB_ALG_TAGS(_pst_tx_ctrl)                ((_pst_tx_ctrl)->uc_alg_frame_tag)

#define MAC_GET_CB_MGMT_FRAME_ID(_pst_tx_ctrl)           ((_pst_tx_ctrl)->bit_mgmt_frame_id)
#define MAC_GET_CB_MPDU_LEN(_pst_tx_ctrl)                ((_pst_tx_ctrl)->us_mpdu_payload_len)
#define MAC_GET_CB_FRAME_TYPE(_pst_tx_ctrl)              ((_pst_tx_ctrl)->uc_frame_type)
#define MAC_GET_CB_FRAME_SUBTYPE(_pst_tx_ctrl)           ((_pst_tx_ctrl)->uc_frame_subtype)
#define MAC_GET_CB_TIMESTAMP(_pst_tx_ctrl)               ((_pst_tx_ctrl)->ul_timestamp_us)

/* VIP?????? */
#define MAC_GET_CB_IS_VIPFRAME(_pst_tx_ctrl)    \
         ((WLAN_CB_FRAME_TYPE_DATA == MAC_GET_CB_FRAME_TYPE(_pst_tx_ctrl)) &&    \
          (MAC_DATA_VIP_FRAME >= MAC_GET_CB_FRAME_SUBTYPE(_pst_tx_ctrl)))

#define MAC_GET_CB_IS_SMPS_FRAME(_pst_tx_ctrl)   \
        ((WLAN_CB_FRAME_TYPE_ACTION == MAC_GET_CB_FRAME_TYPE(_pst_tx_ctrl)) &&    \
         (WLAN_ACTION_SMPS_FRAME_SUBTYPE == MAC_GET_CB_FRAME_SUBTYPE(_pst_tx_ctrl)))
#define MAC_GET_CB_IS_OPMODE_FRAME(_pst_tx_ctrl)  \
        ((WLAN_CB_FRAME_TYPE_ACTION == MAC_GET_CB_FRAME_TYPE(_pst_tx_ctrl)) &&    \
         (WLAN_ACTION_OPMODE_FRAME_SUBTYPE == MAC_GET_CB_FRAME_SUBTYPE(_pst_tx_ctrl)))
#define MAC_GET_CB_IS_P2PGO_FRAME(_pst_tx_ctrl)  \
                ((WLAN_CB_FRAME_TYPE_MGMT == MAC_GET_CB_FRAME_TYPE(_pst_tx_ctrl)) &&    \
                 (WLAN_ACTION_P2PGO_FRAME_SUBTYPE == MAC_GET_CB_FRAME_SUBTYPE(_pst_tx_ctrl)))

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/* ???????????????????????????????????????? */
#define MAC_GET_CB_MPDU_NUM(_pst_tx_ctrl)                ((_pst_tx_ctrl)->bit_mpdu_num)
#define MAC_GET_CB_NETBUF_NUM(_pst_tx_ctrl)              ((_pst_tx_ctrl)->bit_netbuf_num)
#define MAC_GET_CB_FRAME_HEADER_LENGTH(_pst_tx_ctrl)     ((_pst_tx_ctrl)->bit_frame_header_length)
#define MAC_GET_CB_ACK_POLACY(_pst_tx_ctrl)              ((_pst_tx_ctrl)->en_ack_policy)
#define MAC_GET_CB_TX_VAP_INDEX(_pst_tx_ctrl)            ((_pst_tx_ctrl)->bit_tx_vap_index)
#define MAC_GET_CB_TX_USER_IDX(_pst_tx_ctrl)             ((_pst_tx_ctrl)->bit_tx_user_idx)
#define MAC_GET_CB_WME_AC_TYPE(_pst_tx_ctrl)             ((_pst_tx_ctrl)->bit_ac)
#define MAC_GET_CB_WME_TID_TYPE(_pst_tx_ctrl)            ((_pst_tx_ctrl)->bit_tid)
#define MAC_GET_CB_EVENT_TYPE(_pst_tx_ctrl)              ((_pst_tx_ctrl)->bit_event_type)
#define MAC_GET_CB_EVENT_SUBTYPE(_pst_tx_ctrl)           ((_pst_tx_ctrl)->bit_event_sub_type)
#define MAC_GET_CB_RETRIED_NUM(_pst_tx_ctrl)             ((_pst_tx_ctrl)->bit_retried_num)
#define MAC_GET_CB_ALG_PKTNO(_pst_tx_ctrl)               ((_pst_tx_ctrl)->uc_alg_pktno)
#define MAC_GET_CB_TCP_ACK(_pst_tx_ctrl)                 ((_pst_tx_ctrl)->bit_is_tcp_ack)

#define MAC_GET_CB_IS_DATA_FRAME(_pst_tx_ctrl)       \
        ((WLAN_DATA_BASICTYPE == MAC_GET_CB_WLAN_FRAME_TYPE(_pst_tx_ctrl)) &&    \
         ((WLAN_DATA == MAC_GET_CB_WLAN_FRAME_SUBTYPE(_pst_tx_ctrl)) ||       \
          (WLAN_QOS_DATA == MAC_GET_CB_WLAN_FRAME_SUBTYPE(_pst_tx_ctrl))))

#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
#define MAC_GET_CB_SEQ_NUM(_pst_tx_ctrl)                 (((mac_ieee80211_frame_stru *)((oal_uint8 *)_pst_tx_ctrl + OAL_MAX_CB_LEN))->bit_seq_num)
#define MAC_SET_CB_80211_MAC_HEAD_TYPE(_pst_tx_ctrl, _flag)
#define MAC_GET_CB_80211_MAC_HEAD_TYPE(_pst_tx_ctrl)      1 /* offload????,MAC HEAD??netbuf index????,?????????? */

#define MAC_GET_CB_WLAN_FRAME_TYPE(_pst_tx_ctrl)     \
        (((mac_ieee80211_frame_stru *)((oal_uint8 *)(_pst_tx_ctrl) + OAL_MAX_CB_LEN))->st_frame_control.bit_type)
#define MAC_GET_CB_WLAN_FRAME_SUBTYPE(_pst_tx_ctrl)   \
        (((mac_ieee80211_frame_stru *)((oal_uint8 *)(_pst_tx_ctrl) + OAL_MAX_CB_LEN))->st_frame_control.bit_sub_type)


#define MAC_SET_CB_FRAME_HEADER_ADDR(_pst_tx_ctrl, _addr)
#define MAC_GET_CB_FRAME_HEADER_ADDR(_pst_tx_ctrl)       ((mac_ieee80211_frame_stru *)((oal_uint8 *)_pst_tx_ctrl + OAL_MAX_CB_LEN))

#define MAC_SET_CB_IS_QOS_DATA(_pst_tx_ctrl, _flag)
#define MAC_GET_CB_IS_QOS_DATA(_pst_tx_ctrl)         \
        ((WLAN_DATA_BASICTYPE == MAC_GET_CB_WLAN_FRAME_TYPE(_pst_tx_ctrl)) &&    \
         ((WLAN_QOS_DATA == MAC_GET_CB_WLAN_FRAME_SUBTYPE(_pst_tx_ctrl)) ||       \
          (WLAN_QOS_NULL_FRAME == MAC_GET_CB_WLAN_FRAME_SUBTYPE(_pst_tx_ctrl))))

#define MAC_SET_CB_IS_BAR(_pst_tx_ctrl, _flag)
#define MAC_GET_CB_IS_BAR(_pst_tx_ctrl)           \
        ((WLAN_CONTROL == MAC_GET_CB_WLAN_FRAME_TYPE(_pst_tx_ctrl)) &&    \
         (WLAN_BLOCKACK_REQ == MAC_GET_CB_WLAN_FRAME_SUBTYPE(_pst_tx_ctrl)))

/* OFFLOAD ?????????? */
#define MAC_SET_CB_BAR_DSCR_ADDR(_pst_tx_ctrl, _addr)
#define MAC_GET_CB_BAR_DSCR_ADDR(_pst_tx_ctrl)           OAL_PTR_NULL
#else
#define MAC_GET_CB_WLAN_FRAME_TYPE(_pst_tx_ctrl)                ((_pst_tx_ctrl)->st_expand_cb.en_frame_type)
#define MAC_GET_CB_WLAN_FRAME_SUBTYPE(_pst_tx_ctrl)             (((_pst_tx_ctrl)->pst_frame_header)->st_frame_control.bit_sub_type)
#define MAC_GET_CB_SEQ_NUM(_pst_tx_ctrl)                        ((_pst_tx_ctrl)->st_expand_cb.us_seqnum)
#define MAC_SET_CB_FRAME_HEADER_ADDR(_pst_tx_ctrl, _addr)       ((_pst_tx_ctrl)->st_expand_cb.pst_frame_header = _addr)
#define MAC_GET_CB_FRAME_HEADER_ADDR(_pst_tx_ctrl)              ((_pst_tx_ctrl)->st_expand_cb.pst_frame_header)
#define MAC_SET_CB_80211_MAC_HEAD_TYPE(_pst_tx_ctrl, _flag)     ((_pst_tx_ctrl)->st_expand_cb.bit_80211_mac_head_type = _flag)
#define MAC_GET_CB_80211_MAC_HEAD_TYPE(_pst_tx_ctrl)            ((_pst_tx_ctrl)->st_expand_cb.bit_80211_mac_head_type)
#define MAC_SET_CB_IS_QOS_DATA(_pst_tx_ctrl, _flag)
#define MAC_GET_CB_IS_QOS_DATA(_pst_tx_ctrl)             OAL_FALSE
#endif //#if defined(_PRE_PRODUCT_ID_HI110X_DEV)


#else
/* ???????????????? */
#define MAC_GET_CB_MPDU_NUM(_pst_tx_ctrl)                       ((_pst_tx_ctrl)->uc_mpdu_num)
#define MAC_GET_CB_NETBUF_NUM(_pst_tx_ctrl)                     ((_pst_tx_ctrl)->uc_netbuf_num)
#define MAC_GET_CB_FRAME_HEADER_LENGTH(_pst_tx_ctrl)            ((_pst_tx_ctrl)->uc_frame_header_length)
#define MAC_GET_CB_ACK_POLACY(_pst_tx_ctrl)                     ((_pst_tx_ctrl)->en_ack_policy)
#define MAC_GET_CB_WLAN_FRAME_TYPE(_pst_tx_ctrl)                ((_pst_tx_ctrl)->en_frame_type)
#define MAC_GET_CB_WLAN_FRAME_SUBTYPE(_pst_tx_ctrl)             (((_pst_tx_ctrl)->pst_frame_header)->st_frame_control.bit_sub_type)
#define MAC_GET_CB_TX_VAP_INDEX(_pst_tx_ctrl)                   ((_pst_tx_ctrl)->uc_tx_vap_index)
#define MAC_GET_CB_TX_USER_IDX(_pst_tx_ctrl)                    ((_pst_tx_ctrl)->us_tx_user_idx)
#define MAC_GET_CB_WME_AC_TYPE(_pst_tx_ctrl)                    ((_pst_tx_ctrl)->uc_ac)
#define MAC_GET_CB_WME_TID_TYPE(_pst_tx_ctrl)                   ((_pst_tx_ctrl)->uc_tid)
#define MAC_GET_CB_EVENT_TYPE(_pst_tx_ctrl)                     ((_pst_tx_ctrl)->en_event_type)
#define MAC_GET_CB_EVENT_SUBTYPE(_pst_tx_ctrl)                  ((_pst_tx_ctrl)->uc_event_sub_type)
#define MAC_GET_CB_RETRIED_NUM(_pst_tx_ctrl)                    ((_pst_tx_ctrl)->uc_retried_num)
#define MAC_SET_CB_80211_MAC_HEAD_TYPE(_pst_tx_ctrl, _flag)     ((_pst_tx_ctrl)->bit_80211_mac_head_type = _flag)
#define MAC_GET_CB_80211_MAC_HEAD_TYPE(_pst_tx_ctrl)            ((_pst_tx_ctrl)->bit_80211_mac_head_type)
#define MAC_GET_CB_SEQ_CTRL_BYPASS(_pst_tx_ctrl)                ((_pst_tx_ctrl)->en_seq_ctrl_bypass)
#define MAC_SET_CB_FRAME_HEADER_ADDR(_pst_tx_ctrl, _addr)       ((_pst_tx_ctrl)->pst_frame_header = _addr)
#define MAC_GET_CB_FRAME_HEADER_ADDR(_pst_tx_ctrl)              ((_pst_tx_ctrl)->pst_frame_header)
#define MAC_GET_CB_BAR_DSCR_ADDR(_pst_tx_ctrl)                  ((_pst_tx_ctrl)->pst_bar_dscr)
#define MAC_SET_CB_BAR_DSCR_ADDR(_pst_tx_ctrl, _addr)           ((_pst_tx_ctrl)->pst_bar_dscr = _addr)
#define MAC_GET_CB_SEQ_NUM(_pst_tx_ctrl)                        ((_pst_tx_ctrl)->us_seqnum)
#define MAC_GET_CB_ALG_PKTNO(_pst_tx_ctrl)                      ((_pst_tx_ctrl)->ul_alg_pktno)

#define MAC_SET_CB_IS_BAR(_pst_tx_ctrl, _flag)                  ((_pst_tx_ctrl)->en_is_bar = _flag)
#define MAC_GET_CB_IS_BAR(_pst_tx_ctrl)                         ((_pst_tx_ctrl)->en_is_bar)
#define MAC_SET_CB_IS_QOS_DATA(_pst_tx_ctrl, _flag)             ((_pst_tx_ctrl)->en_is_qosdata = _flag)
#define MAC_GET_CB_IS_QOS_DATA(_pst_tx_ctrl)                    ((_pst_tx_ctrl)->en_is_qosdata)
#define MAC_GET_CB_IS_DATA_FRAME(_pst_tx_ctrl)                  (WLAN_DATA_BASICTYPE == MAC_GET_CB_WLAN_FRAME_TYPE(_pst_tx_ctrl))
#define MAC_GET_CB_IS_MORE_FRAGMENTS(_pst_tx_ctrl)              (((_pst_tx_ctrl)->pst_frame_header)->st_frame_control.bit_more_frag)
#endif //#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)


#define MAC_GET_RX_CB_FRAME_LEN(_pst_rx_ctl)                    ((_pst_rx_ctl)->us_frame_len)
#define MAC_GET_RX_CB_MAC_HEADER_LEN(_pst_rx_ctl)               ((_pst_rx_ctl)->uc_mac_header_len)
#define MAC_GET_RX_CB_MAC_VAP_ID(_pst_rx_ctl)                   ((_pst_rx_ctl)->uc_mac_vap_id)
#define MAC_GET_RX_CB_HAL_VAP_IDX(_pst_rx_ctl)                  ((_pst_rx_ctl)->bit_vap_id)

/* DMAC???????????????????????????????????????? */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#define MAC_GET_RX_CB_TA_USER_IDX(_pst_rx_ctl)                  ((_pst_rx_ctl)->bit_ta_user_idx)
#define MAC_GET_RX_CB_PAYLOAD_LEN(_pst_rx_ctl)                  ((_pst_rx_ctl)->us_frame_len - (_pst_rx_ctl)->uc_mac_header_len)
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
#define MAC_GET_RX_PAYLOAD_ADDR(_pst_rx_ctl,_pst_buf)           (OAL_NETBUF_PAYLOAD(_pst_buf))
#else
#define MAC_GET_RX_CB_MAC_HEADER_ADDR(_pst_rx_ctl)              ((_pst_rx_ctl)->st_expand_cb.pul_mac_hdr_start_addr)
#define MAC_GET_RX_CB_DA_USER_IDX(_pst_rx_ctl)                  ((_pst_rx_ctl)->st_expand_cb.us_da_user_idx)
#define MAC_GET_RX_PAYLOAD_ADDR(_pst_rx_ctl, _pst_buf) \
            ((oal_uint8 *)(mac_get_rx_cb_mac_hdr(_pst_rx_ctl)) + MAC_GET_RX_CB_MAC_HEADER_LEN(_pst_rx_ctl))
#endif

#else
#define MAC_GET_RX_CB_TA_USER_IDX(_pst_rx_ctl)                  ((_pst_rx_ctl)->us_ta_user_idx)
#define MAC_GET_RX_CB_MAC_HEADER_ADDR(_pst_rx_ctl)              ((_pst_rx_ctl)->pul_mac_hdr_start_addr)
#define MAC_GET_RX_CB_DA_USER_IDX(_pst_rx_ctl)                  ((_pst_rx_ctl)->us_da_user_idx)
#define MAC_GET_RX_CB_PAYLOAD_LEN(_pst_rx_ctl)                  ((_pst_rx_ctl)->us_frame_len - (_pst_rx_ctl)->uc_mac_header_len)
#define MAC_GET_RX_PAYLOAD_ADDR(_pst_rx_ctl, _pst_buf) \
            ((oal_uint8 *)(mac_get_rx_cb_mac_hdr(_pst_rx_ctl)) + MAC_GET_RX_CB_MAC_HEADER_LEN(_pst_rx_ctl))
#endif





OAL_STATIC OAL_INLINE oal_void  dmac_board_get_instance(mac_board_stru **ppst_dmac_board)
{
    *ppst_dmac_board = g_pst_mac_board;
}


OAL_STATIC OAL_INLINE oal_uint32  dmac_rx_free_netbuf_list(
                oal_netbuf_head_stru       *pst_netbuf_hdr,
                oal_netbuf_stru           **pst_netbuf,
                oal_uint16                  us_nums)
{
    oal_netbuf_stru    *pst_netbuf_temp;
    oal_uint16          us_netbuf_num;

#if defined(_PRE_MEM_DEBUG_MODE) && (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#ifdef SW_DEBUG
    oal_uint32 ul_return_addr      = __return_address();
#endif
#endif

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_netbuf_hdr) || (OAL_PTR_NULL == pst_netbuf)))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (us_netbuf_num = 0; us_netbuf_num < us_nums; us_netbuf_num++)
    {
        pst_netbuf_temp = oal_get_netbuf_next(*pst_netbuf);

        oal_netbuf_delete(*pst_netbuf, pst_netbuf_hdr);

        if(OAL_ERR_CODE_OAL_MEM_ALREADY_FREE==oal_netbuf_free(*pst_netbuf))
        {
            #if defined(_PRE_MEM_DEBUG_MODE) && (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
            #ifdef SW_DEBUG
                OAL_IO_PRINT("double free caller[%x]!\r\n",ul_return_addr);
            #endif
            #endif
        }

        *pst_netbuf = pst_netbuf_temp;
        if (pst_netbuf_hdr ==  (oal_netbuf_head_stru*)(*pst_netbuf))
        {
            break;
        }
    }

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
OAL_STATIC OAL_INLINE oal_uint8 mac_get_cb_is_seq_ctrl_bypass(mac_tx_ctl_stru *pst_cb)
{
    oal_uint8                   uc_frame_type = 0;           /* 802.11?? */

    uc_frame_type = (oal_uint8)((MAC_GET_CB_FRAME_HEADER_ADDR(pst_cb))->st_frame_control.bit_type);

    /* ??????Qos????????seq_ctl_hw_bypass ???? */
    if ((OAL_TRUE != MAC_GET_CB_IS_QOS_DATA(pst_cb)) && (WLAN_DATA_BASICTYPE == uc_frame_type))
    {
        return MAC_GET_CB_SEQ_CTRL_BYPASS(pst_cb);
    }

    return OAL_FALSE;
}
#endif


OAL_STATIC OAL_INLINE oal_void mac_set_rx_cb_mac_hdr(mac_rx_ctl_stru *pst_cb_ctrl, oal_uint32 *pul_mac_hdr_start_addr)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return;
#else
    MAC_GET_RX_CB_MAC_HEADER_ADDR(pst_cb_ctrl) = pul_mac_hdr_start_addr;

#endif
}

OAL_STATIC OAL_INLINE oal_uint32 *mac_get_rx_cb_mac_hdr(mac_rx_ctl_stru *pst_cb_ctrl)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return (oal_uint32 *)((oal_uint8 *)pst_cb_ctrl + OAL_MAX_CB_LEN);
#else
    return MAC_GET_RX_CB_MAC_HEADER_ADDR(pst_cb_ctrl);
#endif
}


OAL_STATIC OAL_INLINE oal_uint8* mac_netbuf_get_payload(oal_netbuf_stru *pst_netbuf)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return OAL_NETBUF_PAYLOAD(pst_netbuf);
#else
    return OAL_NETBUF_PAYLOAD(pst_netbuf)+ MAC_80211_FRAME_LEN;
#endif
}

/*****************************************************************************
  10 ????????
*****************************************************************************/
extern oal_void  dmac_alg_config_event_register(oal_uint32 p_func(frw_event_mem_stru *));
extern oal_void  dmac_alg_config_event_unregister(oal_void);
#ifdef _PRE_WLAN_PERFORM_STAT

/* ???????????????????? */

typedef enum
{
    DMAC_STAT_TX      = 0,      /* ??DMAC_STAT_PER_MAC_TOTAL???? */
    DMAC_STAT_RX      = 1,      /* ??DMAC_STAT_PER_BUFF_OVERFLOW???? */
    DMAC_STAT_BOTH    = 2,      /* ??DMAC_STAT_PER_BUFF_BE_SEIZED???? */

    DMAC_STAT_BUTT
}dmac_stat_direct;
typedef oal_uint8 dmac_stat_direct_enum_uint8;

typedef enum
{
    DMAC_STAT_PER_MAC_TOTAL             = 0,

    DMAC_STAT_PER_BUFF_OVERFLOW         = 1,
    DMAC_STAT_PER_BUFF_BE_SEIZED        = 2,
    DMAC_STAT_PER_DELAY_OVERTIME        = 3,
    DMAC_STAT_PER_SW_RETRY_AMPDU        = 4,
    DMAC_STAT_PER_SW_RETRY_SUB_AMPDU    = 5,
    DMAC_STAT_PER_SW_RETRY_MPDU         = 6,
    DMAC_STAT_PER_SW_RETRY_OVERFLOW     = 7,

    DMAC_STAT_PER_RTS_FAIL              = 8,
    DMAC_STAT_PER_HW_SW_FAIL            = 9,

    DMAC_STAT_PER_BUTT
}dmac_stat_per_reason;
typedef oal_uint8 dmac_stat_per_reason_enum_uint8;

typedef struct
{
    mac_stat_module_enum_uint16    en_module_id;                    /* ??????????id */
    mac_stat_type_enum_uint8       en_stat_type;                    /* ???????? */
    oal_uint8                      uc_resv[1];

    oal_void                      *p_void;                          /* tid,user????vap???? */
    oal_uint32                     aul_stat_avg[DMAC_STAT_PER_BUTT];    /* ?????????????????? */
}dmac_stat_param_stru;

/* ?????????????????????????????????????????? */
typedef oal_uint32  (*dmac_stat_timeout_func)(dmac_stat_param_stru *);

extern oal_uint32  dmac_stat_register(  mac_stat_module_enum_uint16     en_module_id,
                                        mac_stat_type_enum_uint8        en_stat_type,
                                        oal_void                       *p_void,
                                        dmac_stat_param_stru           *p_output_param,
                                        dmac_stat_timeout_func          p_func,
										oal_uint32						ul_core_id);

extern oal_uint32	dmac_stat_start( mac_stat_module_enum_uint16   en_module_id,
                                     mac_stat_type_enum_uint8      en_stat_type,
                                     oal_uint16                    us_stat_period,
                                     oal_uint16                    us_stat_num,
                                     oal_void                      *p_void);

extern oal_uint32	dmac_stat_stop(  mac_stat_module_enum_uint16  en_module_id,
                                     mac_stat_type_enum_uint8     en_stat_type,
                                     oal_void                    *p_void);

extern oal_uint32	dmac_stat_unregister(mac_stat_module_enum_uint16    en_module_id,
                                         mac_stat_type_enum_uint8       en_stat_type,
                                         oal_void                      *p_void);

#endif

#ifdef _PRE_DEBUG_MODE_USER_TRACK
extern oal_uint32  mac_user_check_txrx_protocol_change(
                                  mac_user_stru *pst_mac_user,
                                  oal_uint8      uc_present_mode,
                                  oam_user_info_change_type_enum_uint8  en_type);
#endif

#ifdef _PRE_WLAN_PERFORM_STAT
extern oal_uint32 dmac_stat_tid_per(mac_user_stru *pst_dmac_user,
                                    oal_uint8 uc_tidno,
                                    oal_uint16 us_mpdu_num,
                                    oal_uint16 us_err_mpdu_num,
                                    dmac_stat_per_reason_enum_uint8 en_per_reason);
#endif
extern oal_uint32  dmac_tid_pause(dmac_tid_stru *pst_tid, oal_uint8 uc_type);
extern oal_uint32  dmac_tid_resume(hal_to_dmac_device_stru *pst_hal_device, dmac_tid_stru *pst_tid, oal_uint8 uc_type);

extern oal_void mac_set_rx_cb_mac_hdr(mac_rx_ctl_stru *pst_cb_ctrl, oal_uint32 *pul_mac_hdr_start_addr);
extern oal_uint32 *mac_get_rx_cb_mac_hdr(mac_rx_ctl_stru *pst_cb_ctrl);

#if (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
extern oal_uint32 dmac_init_event_process(frw_event_mem_stru *pst_event_mem);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32 dmac_cfg_vap_init_event(frw_event_mem_stru *pst_event_mem);
#endif
#endif
extern oal_uint32 dmac_tx_reinit_tx_queue(mac_device_stru *pst_mac_device, hal_to_dmac_device_stru *pst_hal_device);
extern oal_uint32  mac_vap_set_cb_tx_user_idx(mac_vap_stru *pst_mac_vap, mac_tx_ctl_stru *pst_tx_ctl, oal_uint8 *puc_data);

extern oal_void dmac_tid_tx_queue_init_cb(dmac_tid_stru *past_tx_tid_queue, mac_user_stru *pst_user, oal_uint32 *pul_result);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_ext_if.h */
