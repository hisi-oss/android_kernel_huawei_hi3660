

#ifndef __WLAN_TYPES_H__
#define __WLAN_TYPES_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "platform_spec.h"
#include "oal_ext_if.h"

/*****************************************************************************
  2 ??????
*****************************************************************************/

/*****************************************************************************
  2.1 ??????????
*****************************************************************************/

#define MAC_BYTE_ALIGN_VALUE                4           /* 4???????? */

#define WLAN_MAC_ADDR_LEN                   6           /* MAC?????????? */
#define WLAN_MAX_FRAME_HEADER_LEN           36          /* ??????MAC????????????????36??????????28 */
#define WLAN_MIN_FRAME_HEADER_LEN           10          /* ack??cts????????????10 */
#define WLAN_MAX_FRAME_LEN                  1600        /* ???????????????? */
#define WLAN_MGMT_FRAME_HEADER_LEN          24          /* ????????MAC????????????????36??????????28 */
#ifdef _PRE_WLAN_FEATURE_HILINK_HERA_PRODUCT
#define WLAN_IWPRIV_MAX_BUFF_LEN            200         /* iwpriv???????????????????? */
#else
#define WLAN_IWPRIV_MAX_BUFF_LEN            100         /* iwpriv???????????????????? */
#endif
/* SSID????????, +1??\0???????? */
#define WLAN_SSID_MAX_LEN                   (32 + 1)

/* 80211MAC????FC?????????? */
#define WLAN_PROTOCOL_VERSION               0x00        /* ???????? */
#define WLAN_FC0_TYPE_MGT                   0x00        /* ?????? */
#define WLAN_FC0_TYPE_CTL                   0x04        /* ?????? */
#define WLAN_FC0_TYPE_DATA                  0x08        /* ?????? */

/* ??????subtype */
#define WLAN_FC0_SUBTYPE_ASSOC_REQ          0x00
#define WLAN_FC0_SUBTYPE_ASSOC_RSP          0x10
#define WLAN_FC0_SUBTYPE_REASSOC_REQ        0x20
#define WLAN_FC0_SUBTYPE_REASSOC_RSP        0x30
#define WLAN_FC0_SUBTYPE_PROBE_REQ          0x40
#define WLAN_FC0_SUBTYPE_PROBE_RSP          0x50
#define WLAN_FC0_SUBTYPE_BEACON             0x80
#define WLAN_FC0_SUBTYPE_ATIM               0x90
#define WLAN_FC0_SUBTYPE_DISASSOC           0xa0
#define WLAN_FC0_SUBTYPE_AUTH               0xb0
#define WLAN_FC0_SUBTYPE_DEAUTH             0xc0
#define WLAN_FC0_SUBTYPE_ACTION             0xd0
#define WLAN_FC0_SUBTYPE_ACTION_NO_ACK      0xe0

/* ??????subtype */
#define WLAN_FC0_SUBTYPE_NDPA               0x50
#define WLAN_FC0_SUBTYPE_Control_Wrapper    0x70        /* For TxBF RC */
#define WLAN_FC0_SUBTYPE_BAR                0x80
#define WLAN_FC0_SUBTYPE_BA                 0x90

#define WLAN_FC0_SUBTYPE_PS_POLL            0xa0
#define WLAN_FC0_SUBTYPE_RTS                0xb0
#define WLAN_FC0_SUBTYPE_CTS                0xc0
#define WLAN_FC0_SUBTYPE_ACK                0xd0
#define WLAN_FC0_SUBTYPE_CF_END             0xe0
#define WLAN_FC0_SUBTYPE_CF_END_ACK         0xf0

/* ??????subtype */
#define WLAN_FC0_SUBTYPE_DATA               0x00
#define WLAN_FC0_SUBTYPE_CF_ACK             0x10
#define WLAN_FC0_SUBTYPE_CF_POLL            0x20
#define WLAN_FC0_SUBTYPE_CF_ACPL            0x30
#define WLAN_FC0_SUBTYPE_NODATA             0x40
#define WLAN_FC0_SUBTYPE_CFACK              0x50
#define WLAN_FC0_SUBTYPE_CFPOLL             0x60
#define WLAN_FC0_SUBTYPE_CF_ACK_CF_ACK      0x70
#define WLAN_FC0_SUBTYPE_QOS                0x80
#define WLAN_FC0_SUBTYPE_QOS_NULL           0xc0

#define WLAN_FC1_DIR_MASK                   0x03
#define WLAN_FC1_DIR_NODS                   0x00        /* STA->STA */
#define WLAN_FC1_DIR_TODS                   0x01        /* STA->AP  */
#define WLAN_FC1_DIR_FROMDS                 0x02        /* AP ->STA */
#define WLAN_FC1_DIR_DSTODS                 0x03        /* AP ->AP  */

#define WLAN_FC1_MORE_FRAG                  0x04
#define WLAN_FC1_RETRY                      0x08
#define WLAN_FC1_PWR_MGT                    0x10
#define WLAN_FC1_MORE_DATA                  0x20
#define WLAN_FC1_WEP                        0x40
#define WLAN_FC1_ORDER                      0x80

#define WLAN_HDR_DUR_OFFSET                 2           /* duartion??????mac???????????? */
#define WLAN_HDR_ADDR1_OFFSET               4           /* addr1??????mac???????????? */
#define WLAN_HDR_ADDR2_OFFSET               10          /* addr1??????mac???????????? */
#define WLAN_HDR_ADDR3_OFFSET               16          /* addr1??????mac???????????? */
#define WLAN_HDR_FRAG_OFFSET                22          /* ??????????????mac?????????? */

#define WLAN_REASON_CODE_LEN                2

/* ????DS?? */
#define WLAN_FRAME_TO_AP                   0x0100
#define WLAN_FRAME_FROM_AP                 0x0200
/* FCS????(4????) */
#define WLAN_HDR_FCS_LENGTH                 4

#define WLAN_RANDOM_MAC_OUI_LEN            3            /* ????mac????OUI???? */

#define WLAN_MAX_BAR_DATA_LEN               20  /* BAR???????????? */
#define WLAN_CHTXT_SIZE                     128 /* challenge text?????? */

#define WLAN_SEQ_SHIFT                      4
/* AMPDU Delimeter????(4????) */
#define WLAN_DELIMETER_LENGTH               4

/* ???????? */
#define GET_ABS(val)                        ((val) > 0 ? (val) : -(val))

/* ????????????????: ??????????????????????????"alg" */
#define DMAC_ALG_CONFIG_MAX_ARG     7

/* ???????????? */
#define WLAN_CHAN_SWITCH_DEFAULT_CNT        6
#define WLAN_CHAN_SWITCH_DETECT_RADAR_CNT   1

/* 5G?????????? */
#define WLAN_5G_SUB_BAND_NUM        7
#define WLAN_5G_20M_SUB_BAND_NUM    7
#define WLAN_5G_80M_SUB_BAND_NUM    7
#define WLAN_5G_CALI_SUB_BAND_NUM   (WLAN_5G_20M_SUB_BAND_NUM + WLAN_5G_80M_SUB_BAND_NUM)

#if defined(_PRE_WLAN_FEATURE_EQUIPMENT_TEST) && (defined _PRE_WLAN_FIT_BASED_REALTIME_CALI)
#define WLAN_DYNC_CALI_POW_PD_PARAM_NUM   3    /* ????????power&pdet?????????????? */
#define WLAN_DYNC_CALI_2G_PD_PARAM_NUMS   18
#define WLAN_DYNC_CALI_5G_PD_PARAM_NUMS   36
#define WLAN_DYNC_CALI_5G_UPC_PARAM_NUMS  14
#define WLAN_DYNC_CALI_5G_UPC_PARAM_STR_LEN  69 /* 5G upc??????????????:4(????????????????)*14(????????)+13(??????)=69 */
#define WLAN_DYNC_CALI_2G_UPC_PARAM_STR_LEN  29 /* 2G upc??????????????:4(????????????????)*6(????????)+5(??????)=29 */
#define WLAN_DYNC_CALI_PDET_MAX           800  /* ????????pdet?????????? */
#endif

#define WLAN_DIEID_MAX_LEN   40

#define WLAN_FIELD_TYPE_AID            0xC000
#define WLAN_AID(AID)                  ((AID) &~ 0xc000)

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#define WLAN_MAX_VAP_NUM            4   /*??????????????VAP????*/
#define WLAN_SIFS_OFDM_POWLVL_NUM   1   /*OFDM SIFS????????????????*/
#if (_PRE_TARGET_PRODUCT_TYPE_E5 == _PRE_CONFIG_TARGET_PRODUCT)
#define WLAN_2G_SUB_BAND_NUM        13   /*2G??????????*/
#else
#define WLAN_2G_SUB_BAND_NUM        3   /*2G??????????*/
#endif

#else
#define WLAN_MAX_VAP_NUM            2
#define WLAN_2G_SUB_BAND_NUM        13
#define WLAN_SIFS_OFDM_POWLVL_NUM   4
#endif

#define WLAN_BW_CAP_TO_BANDWIDTH(_bw_cap) \
    ((WLAN_BW_CAP_20M == (_bw_cap)) ? WLAN_BAND_ASSEMBLE_20M :   \
     (WLAN_BW_CAP_40M == (_bw_cap)) ? WLAN_BAND_ASSEMBLE_40M :   \
     (WLAN_BW_CAP_80M == (_bw_cap)) ? WLAN_BAND_ASSEMBLE_80M :   \
     (WLAN_BW_CAP_160M == (_bw_cap)) ? WLAN_BAND_ASSEMBLE_160M : \
     (WLAN_BAND_ASSEMBLE_20M))

#define WLAN_INVALD_VHT_MCS     0xff
#define WLAN_GET_VHT_MAX_SUPPORT_MCS(_us_vht_mcs_map)   \
     ((3 == (_us_vht_mcs_map)) ? WLAN_INVALD_VHT_MCS:     \
      (2 == (_us_vht_mcs_map)) ? WLAN_VHT_MCS9:           \
      (1 == (_us_vht_mcs_map)) ? WLAN_VHT_MCS8: WLAN_VHT_MCS7)

/*****************************************************************************
  2.2 WME??????
*****************************************************************************/
#define WLAN_WME_AC_TO_TID(_ac) (       \
        ((_ac) == WLAN_WME_AC_VO) ? 6 : \
        ((_ac) == WLAN_WME_AC_VI) ? 5 : \
        ((_ac) == WLAN_WME_AC_BK) ? 1 : \
        0)



#define WLAN_WME_TID_TO_AC(_tid) (      \
        (((_tid) == 0) || ((_tid) == 3)) ? WLAN_WME_AC_BE : \
        (((_tid) == 1) || ((_tid) == 2)) ? WLAN_WME_AC_BK : \
        (((_tid) == 4) || ((_tid) == 5)) ? WLAN_WME_AC_VI : \
        WLAN_WME_AC_VO)

/*****************************************************************************
  2.3 HT??????
*****************************************************************************/
/* 11n: Maximum A-MSDU Length Indicates maximum A-MSDU length.See 9.11. Set to 0 for 3839 octetsSet to 1 for 7935 octets */
/* 11AC(9.11): A VHT STA that sets the Maximum MPDU Length in the VHT Capabilities element to indicate 3895 octets
   shall set the Maximum A-MSDU Length in the HT Capabilities element to indicate 3839 octets. A VHT STA
   that sets the Maximum MPDU Length in the VHT Capabilities element to indicate 7991 octets or 11 454 oc-
   tets shall set the Maximum A-MSDU Length in the HT Capabilities element to indicate 7935 octets. */

#define WLAN_AMSDU_FRAME_MAX_LEN_SHORT      3839
#define WLAN_AMSDU_FRAME_MAX_LEN_LONG       7935

/* Maximum A-MSDU Length Indicates maximum A-MSDU length.See 9.11. Set to 0 for 3839 octetsSet to 1 for 7935 octets */
#define WLAN_HT_GET_AMSDU_MAX_LEN(_bit_amsdu_max_length)  \
       ((0 == (_bit_amsdu_max_length)) ? WLAN_AMSDU_FRAME_MAX_LEN_SHORT : WLAN_AMSDU_FRAME_MAX_LEN_LONG)

/* RSSI??????????RSSI??????-128~127, ????????????127??????????????127??????MARKER,???????? */
#define WLAN_RSSI_DUMMY_MARKER              0x7F

/*****************************************************************************
  2.4 ??????????????
*****************************************************************************/
/* ????????????????????????????????????????????????????????????????????!! */
/* cipher suite selectors */
#ifndef WLAN_CIPHER_SUITE_USE_GROUP
#define WLAN_CIPHER_SUITE_USE_GROUP 0x000FAC00
#endif

#ifndef WLAN_CIPHER_SUITE_WEP40
#define WLAN_CIPHER_SUITE_WEP40     0x000FAC01
#endif

#ifndef WLAN_CIPHER_SUITE_TKIP
#define WLAN_CIPHER_SUITE_TKIP      0x000FAC02
#endif

/* reserved:                0x000FAC03 */
#ifndef WLAN_CIPHER_SUITE_CCMP
#define WLAN_CIPHER_SUITE_CCMP      0x000FAC04
#endif

#ifndef WLAN_CIPHER_SUITE_WEP104
#define WLAN_CIPHER_SUITE_WEP104    0x000FAC05
#endif

#ifndef WLAN_CIPHER_SUITE_AES_CMAC
#define WLAN_CIPHER_SUITE_AES_CMAC  0x000FAC06
#endif

#ifndef WLAN_CIPHER_SUITE_GCMP
#define WLAN_CIPHER_SUITE_GCMP      0x000FAC08
#endif

#ifndef WLAN_CIPHER_SUITE_GCMP_256
#define WLAN_CIPHER_SUITE_GCMP_256  0x000FAC09
#endif

#ifndef WLAN_CIPHER_SUITE_CCMP_256
#define WLAN_CIPHER_SUITE_CCMP_256  0x000FAC0A
#endif

#ifndef WLAN_CIPHER_SUITE_BIP_GMAC_128
#define WLAN_CIPHER_SUITE_BIP_GMAC_128  0x000FAC0B
#endif

#ifndef WLAN_CIPHER_SUITE_BIP_GMAC_256
#define WLAN_CIPHER_SUITE_BIP_GMAC_256  0x000FAC0C
#endif

#ifndef WLAN_CIPHER_SUITE_BIP_CMAC_256
#define WLAN_CIPHER_SUITE_BIP_CMAC_256  0x000FAC0D
#endif

#undef  WLAN_CIPHER_SUITE_SMS4
#define WLAN_CIPHER_SUITE_SMS4      0x00147201

/* AKM suite selectors */
#define WITP_WLAN_AKM_SUITE_8021X        0x000FAC01
#define WITP_WLAN_AKM_SUITE_PSK          0x000FAC02
#define WITP_WLAN_AKM_SUITE_WAPI_PSK     0x000FAC04
#define WITP_WLAN_AKM_SUITE_WAPI_CERT    0x000FAC12



#define WLAN_PMKID_LEN           16
#define WLAN_PMKID_CACHE_SIZE    32
#define WLAN_NONCE_LEN           32
#define WLAN_PTK_PREFIX_LEN      22
#define WLAN_GTK_PREFIX_LEN      19
#define WLAN_GTK_DATA_LEN        (NONCE_LEN + WLAN_MAC_ADDR_LEN)
#define WLAN_PTK_DATA_LEN        (2 * NONCE_LEN + 2 * WLAN_MAC_ADDR_LEN)


#define WLAN_KCK_LENGTH          16
#define WLAN_KEK_LENGTH          16
#define WLAN_TEMPORAL_KEY_LENGTH 16
#define WLAN_MIC_KEY_LENGTH      8

#define WLAN_PMK_SIZE        32 /* In Bytes */
#define WLAN_PTK_SIZE        64 /* In Bytes */
#define WLAN_GTK_SIZE        32 /* In Bytes */
#define WLAN_GMK_SIZE        32 /* In Bytes */

#define WLAN_WEP40_KEY_LEN              5
#define WLAN_WEP104_KEY_LEN             13
#define WLAN_TKIP_KEY_LEN               32      /* TKIP KEY length 256 BIT */
#define WLAN_CCMP_KEY_LEN               16      /* CCMP KEY length 128 BIT */
#define WLAN_BIP_KEY_LEN                16      /* BIP KEY length 128 BIT */

#define WLAN_NUM_DOT11WEPDEFAULTKEYVALUE       4
#define WLAN_MAX_WEP_STR_SIZE                  27 /* 5 for WEP 40; 13 for WEP 104 */
#define WLAN_WEP_SIZE_OFFSET                   0
#define WLAN_WEP_KEY_VALUE_OFFSET              1
#define WLAN_WEP_40_KEY_SIZE                  40
#define WLAN_WEP_104_KEY_SIZE                104

#define WLAN_COUNTRY_STR_LEN        3

/* crypto status */
#define WLAN_ENCRYPT_BIT        (1 << 0)
#define WLAN_WEP_BIT            (1 << 1)
#define WLAN_WEP104_BIT         ((1 << 2) | (1 << 1))
#define WLAN_WPA_BIT            (1 << 3)
#define WLAN_WPA2_BIT           (1 << 4)
#define WLAN_CCMP_BIT           (1 << 5)
#define WLAN_TKIP_BIT           (1 << 6)

#define WLAN_WAPI_BIT           (1 << 5)

/* 11i???? */
/*WPA ????????*/
#define WLAN_WPA_KEY_LEN                    32
#define WLAN_CIPHER_KEY_LEN                 16
#define WLAN_TKIP_MIC_LEN                   16
/*WPA ????????*/
#define WLAN_WPA_SEQ_LEN                    16

/* auth */
#define WLAN_OPEN_SYS_BIT       (1 << 0)
#define WLAN_SHARED_KEY_BIT     (1 << 1)
#define WLAN_8021X_BIT          (1 << 2)

#define WLAN_WITP_CAPABILITY_PRIVACY BIT4

#define WLAN_NUM_TK             4
#define WLAN_NUM_IGTK           2
#define WLAN_MAX_IGTK_KEY_INDEX 5
#define WLAN_MAX_WEP_KEY_COUNT  4


/*****************************************************************************
  2.5 ??????????????
*****************************************************************************/
#define  WLAN_BIP_REPLAY_FAIL_FLT  BIT0               /* BIP???????????? */
#define  WLAN_CCMP_REPLAY_FAIL_FLT  BIT1              /* CCMP???????????? */
#define  WLAN_OTHER_CTRL_FRAME_FLT BIT2               /* direct??????????*/
#define  WLAN_BCMC_MGMT_OTHER_BSS_FLT BIT3            /*????BSS????????????????????*/
/*????1151V100????????*/
#define  WLAN_UCAST_MGMT_OTHER_BSS_FLT BIT4           /*????BSS????????????????????*/

#define  WLAN_UCAST_DATA_OTHER_BSS_FLT BIT5           /*????BSS????????????????????*/

/*****************************************************************************
  2.6 TXBF??????????
*****************************************************************************/

/*****************************************************************************
  2.7  TX & RX Chain Macro
*****************************************************************************/
/* RF??????????*/
/* RF0 */
#define WLAN_RF_CHANNEL_ZERO        0
/* RF1 */
#define WLAN_RF_CHANNEL_ONE         1

/* PHY???????? */
/* ????0 */
#define WLAN_PHY_CHAIN_ZERO_IDX     0
/* ????1 */
#define WLAN_PHY_CHAIN_ONE_IDX      1

/* ?????????? */
#define WLAN_RF_CHAIN_DOUBLE        3
#define WLAN_RF_CHAIN_ONE           2
#define WLAN_RF_CHAIN_ZERO          1

/* ?????????? */
#define WLAN_PHY_CHAIN_DOUBLE       3
#define WLAN_TX_CHAIN_DOUBLE        WLAN_PHY_CHAIN_DOUBLE
#define WLAN_RX_CHAIN_DOUBLE        WLAN_PHY_CHAIN_DOUBLE
/*  ????0 ????*/
#define WLAN_PHY_CHAIN_ZERO         1
#define WLAN_TX_CHAIN_ZERO          WLAN_PHY_CHAIN_ZERO
#define WLAN_RX_CHAIN_ZERO          WLAN_PHY_CHAIN_ZERO
/*  ????1 ????*/
#define WLAN_PHY_CHAIN_ONE          2
#define WLAN_TX_CHAIN_ONE           WLAN_PHY_CHAIN_ONE
#define WLAN_RX_CHAIN_ONE           WLAN_PHY_CHAIN_ONE

#define WLAN_2G_CHANNEL_NUM         14
#define WLAN_5G_CHANNEL_NUM         29
/* wifi 5G 2.4G???????????? */
#define WLAN_MAX_CHANNEL_NUM        (WLAN_2G_CHANNEL_NUM + WLAN_5G_CHANNEL_NUM)

/* PLL0 */
#define WLAN_RF_PLL_ID_0            0
/* PLL1 */
#define WLAN_RF_PLL_ID_1            1
/*****************************************************************************
  2.8 linkloss
*****************************************************************************/
#define WLAN_LINKLOSS_REPORT            10 /* linkloss??10??????????????*/
#define WLAN_LINKLOSS_MIN_THRESHOLD     10 /* linkloss?????????????? */
#define WLAN_LINKLOSS_MAX_THRESHOLD     250 /* linkloss?????????????? */

#ifdef _PRE_WLAN_FEATURE_11AX
/* 11AX MCS?????????? */
#define MAC_MAX_SUP_MCS7_11AX_EACH_NSS             0   /* 11AX??????????????????MCS??????????0-7*/
#define MAC_MAX_SUP_MCS9_11AX_EACH_NSS             1   /* 11AX??????????????????MCS??????????0-9*/
#define MAC_MAX_SUP_MCS11_11AX_EACH_NSS            2   /* 11AX??????????????????MCS??????????0-11*/
#define MAC_MAX_SUP_INVALID_11AX_EACH_NSS          3   /* ??????*/


#define MAC_MAX_RATE_SINGLE_NSS_20M_11AX           106  /* 1????????20MHz??????????-??ax????28.5-HE-MCSs*/
#define MAC_MAX_RATE_SINGLE_NSS_40M_11AX           212 /* 1????????40MHz??????Long GI????*/
#define MAC_MAX_RATE_SINGLE_NSS_80M_11AX           212 /* 1????????40MHz??????Long GI????*/

#define MAC_MAX_RATE_DOUBLE_NSS_20M_11AX           211 /* 2????????20MHz??????Long GI????*/
#define MAC_MAX_RATE_DOUBLE_NSS_40M_11AX           423 /* 2????????20MHz??????Long GI????*/
#define MAC_MAX_RATE_DOUBLE_NSS_80M_11AX           869 /* 2????????20MHz??????Long GI????*/

#define MAC_TRIGGER_FRAME_PADDING_DURATION0us      0
#define MAC_TRIGGER_FRAME_PADDING_DURATION8us      1
#define MAC_TRIGGER_FRAME_PADDING_DURATION16us     2
#endif

/*****************************************************************************
  3 ????????
*****************************************************************************/
/*****************************************************************************
  3.1 ????????????
*****************************************************************************/
/* ???????????? */
typedef enum
{
    WLAN_ASSOC_REQ              = 0,    /* 0000 */
    WLAN_ASSOC_RSP              = 1,    /* 0001 */
    WLAN_REASSOC_REQ            = 2,    /* 0010 */
    WLAN_REASSOC_RSP            = 3,    /* 0011 */
    WLAN_PROBE_REQ              = 4,    /* 0100 */
    WLAN_PROBE_RSP              = 5,    /* 0101 */
    WLAN_TIMING_AD              = 6,    /* 0110 */
    WLAN_MGMT_SUBTYPE_RESV1     = 7,    /* 0111 */
    WLAN_BEACON                 = 8,    /* 1000 */
    WLAN_ATIM                   = 9,    /* 1001 */
    WLAN_DISASOC                = 10,   /* 1010 */
    WLAN_AUTH                   = 11,   /* 1011 */
    WLAN_DEAUTH                 = 12,   /* 1100 */
    WLAN_ACTION                 = 13,   /* 1101 */
    WLAN_ACTION_NO_ACK          = 14,   /* 1110 */
    WLAN_MGMT_SUBTYPE_RESV2     = 15,   /* 1111 */

    WLAN_MGMT_SUBTYPE_BUTT      = 16,   /* ????16?????????????? */
}wlan_frame_mgmt_subtype_enum;

/*TBD????????BUTT????????????*/
typedef enum
{
    WLAN_WME_AC_BE = 0,    /* best effort */
    WLAN_WME_AC_BK = 1,    /* background */
    WLAN_WME_AC_VI = 2,    /* video */
    WLAN_WME_AC_VO = 3,    /* voice */

    WLAN_WME_AC_BUTT = 4,
    WLAN_WME_AC_MGMT = WLAN_WME_AC_BUTT,   /* ????AC??????????,????????????????????*/

    WLAN_WME_AC_PSM = 5    /* ????AC, ?????????????????????????? */
}wlan_wme_ac_type_enum;
typedef oal_uint8 wlan_wme_ac_type_enum_uint8;

/* TID??????8,0~7 */
#define WLAN_TID_MAX_NUM                    WLAN_TIDNO_BUTT

/* TID???????? */
typedef enum
{
    WLAN_TIDNO_BEST_EFFORT              = 0, /* BE???? */
    WLAN_TIDNO_BACKGROUND               = 1, /* BK???? */
    WLAN_TIDNO_UAPSD                    = 2, /* U-APSD */
    WLAN_TIDNO_ANT_TRAINING_LOW_PRIO    = 3, /* ?????????????????????? */
    WLAN_TIDNO_ANT_TRAINING_HIGH_PRIO   = 4, /* ?????????????????????? */
    WLAN_TIDNO_VIDEO                    = 5, /* VI???? */
    WLAN_TIDNO_VOICE                    = 6, /* VO???? */
    WLAN_TIDNO_BCAST                    = 7, /* ?????????????????????????? */

    WLAN_TIDNO_BUTT
}wlan_tidno_enum;
typedef oal_uint8 wlan_tidno_enum_uint8;

/* TID???????????????? */

/* VAP?????????? */
typedef enum
{
    WLAN_VAP_MODE_CONFIG,        /* ???????? */
    WLAN_VAP_MODE_BSS_STA,       /* BSS STA???? */
    WLAN_VAP_MODE_BSS_AP,        /* BSS AP???? */
    WLAN_VAP_MODE_WDS,           /* WDS???? */
    WLAN_VAP_MODE_MONITOER,      /* ???????? */
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    WLAN_VAP_MODE_PROXYSTA,     /* proxysta??????????????hal?????????? */
#endif
    WLAN_VAP_HW_TEST,

    WLAN_VAP_MODE_BUTT
}wlan_vap_mode_enum;
typedef oal_uint8 wlan_vap_mode_enum_uint8;

/* ??????transaction number */
typedef enum
{
    WLAN_AUTH_TRASACTION_NUM_ONE    = 0x0001,
    WLAN_AUTH_TRASACTION_NUM_TWO    = 0x0002,
    WLAN_AUTH_TRASACTION_NUM_THREE  = 0x0003,
    WLAN_AUTH_TRASACTION_NUM_FOUR   = 0x0004,

    WLAN_AUTH_TRASACTION_NUM_BUTT
}wlan_auth_transaction_number_enum;
typedef oal_uint16 wlan_auth_transaction_number_enum_uint16;
typedef enum
{
    WLAN_BAND_2G,
    WLAN_BAND_5G,

    WLAN_BAND_BUTT
} wlan_channel_band_enum;
typedef oal_uint8 wlan_channel_band_enum_uint8;

/* Protection mode for MAC */
typedef enum
{
    WLAN_PROT_NO,           /* Do not use any protection       */
    WLAN_PROT_ERP,          /* Protect all ERP frame exchanges */
    WLAN_PROT_HT,           /* Protect all HT frame exchanges  */
    WLAN_PROT_GF,           /* Protect all GF frame exchanges  */

    WLAN_PROT_BUTT
}wlan_prot_mode_enum;
typedef oal_uint8 wlan_prot_mode_enum_uint8;

typedef enum
{
    WLAN_RTS_RATE_SELECT_MODE_REG,  /* 0: RTS???? = PROT_DATARATE??????                           */
    WLAN_RTS_RATE_SELECT_MODE_DESC, /* 1: RTS???? = ????????TX????????????????                    */
    WLAN_RTS_RATE_SELECT_MODE_MIN,  /* 2: RTS???? = min(PROT_DATARATE,????????TX????????????????) */
    WLAN_RTS_RATE_SELECT_MODE_MAX,  /* 3: RTS???? = max(PROT_DATARATE,????????TX????????????????) */

    WLAN_RTS_RATE_SELECT_MODE_BUTT
}wlan_rts_rate_select_mode_enum;

#if IS_HOST
typedef enum
{
    WLAN_WITP_AUTH_OPEN_SYSTEM = 0,
    WLAN_WITP_AUTH_SHARED_KEY,
    WLAN_WITP_AUTH_FT,
    WLAN_WITP_AUTH_NETWORK_EAP,
    WLAN_WITP_AUTH_SAE,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 10, 0))
    /* 4.10????????????3??FILS???????????? */
    WLAN_WITP_AUTH_FILS_SK,
    WLAN_WITP_AUTH_FILS_SK_PFS,
    WLAN_WITP_AUTH_FILS_PK,
#endif
    WLAN_WITP_AUTH_NUM,
    WLAN_WITP_AUTH_MAX = WLAN_WITP_AUTH_NUM - 1,
    WLAN_WITP_AUTH_AUTOMATIC,
    WLAN_WITP_AUTH_BUTT
}wlan_auth_alg_mode_enum;
#else
typedef enum
{
    WLAN_WITP_AUTH_OPEN_SYSTEM = 0,
    WLAN_WITP_AUTH_SHARED_KEY,
    WLAN_WITP_AUTH_FT,
    WLAN_WITP_AUTH_NETWORK_EAP,
    WLAN_WITP_AUTH_SAE,
}wlan_auth_alg_mode_enum;
#endif

typedef oal_uint8 wlan_auth_alg_mode_enum_uint8;

typedef enum
{
    /*
    *  ????: wlan_cipher_key_type_enum??hal_key_type_enum ??????,
    *        ????????????????????????HAL ??????
    */

    /* TBD:???????????????????????????????? */
    WLAN_KEY_TYPE_TX_GTK              = 0,  /* TX GTK */
    WLAN_KEY_TYPE_PTK                 = 1,  /* PTK */
    WLAN_KEY_TYPE_RX_GTK              = 2,  /* RX GTK */
    WLAN_KEY_TYPE_RX_GTK2             = 3,  /* RX GTK2 51???? */
    WLAN_KEY_TYPE_BUTT
} wlan_cipher_key_type_enum;
typedef oal_uint8 wlan_cipher_key_type_enum_uint8;

typedef enum
{
    /*
    *  ????: wlan_key_origin_enum_uint8??hal_key_origin_enum_uint8 ??????,
    *        ????????????????????????HAL ??????
    */

    WLAN_AUTH_KEY = 0,      /* Indicates that for this key, this STA is the authenticator */
    WLAN_SUPP_KEY = 1,      /* Indicates that for this key, this STA is the supplicant */

    WLAN_KEY_ORIGIN_BUTT,
}wlan_key_origin_enum;
typedef oal_uint8 wlan_key_origin_enum_uint8;

typedef enum
{
    NARROW_BW_10M = 0x80,
    NARROW_BW_5M = 0x81,
    NARROW_BW_1M = 0x82,
    NARROW_BW_BUTT
}mac_narrow_bw_enum;
typedef oal_uint8 mac_narrow_bw_enum_uint8;

typedef enum
{
    WLAN_ADDBA_MODE_AUTO,
    WLAN_ADDBA_MODE_MANUAL,

    WLAN_ADDBA_MODE_BUTT
}wlan_addba_mode_enum;
typedef oal_uint8 wlan_addba_mode_enum_uint8;


typedef enum
{
    /* ????80211-2012/ 11ac-2013 ???? Table 8-99 Cipher suite selectors ???? */
    WLAN_80211_CIPHER_SUITE_GROUP_CIPHER = 0,
    WLAN_80211_CIPHER_SUITE_WEP_40       = 1,
    WLAN_80211_CIPHER_SUITE_TKIP         = 2,
    WLAN_80211_CIPHER_SUITE_RSV          = 3,
    WLAN_80211_CIPHER_SUITE_NO_ENCRYP    = WLAN_80211_CIPHER_SUITE_RSV, /* ???????????????????????????????? */
    WLAN_80211_CIPHER_SUITE_CCMP         = 4,
    WLAN_80211_CIPHER_SUITE_WEP_104      = 5,
    WLAN_80211_CIPHER_SUITE_BIP          = 6,
    WLAN_80211_CIPHER_SUITE_GROUP_DENYD  = 7,
    WLAN_80211_CIPHER_SUITE_GCMP         = 8,             /* GCMP-128 default for a DMG STA */
    WLAN_80211_CIPHER_SUITE_GCMP_256     = 9,
    WLAN_80211_CIPHER_SUITE_CCMP_256     = 10,
    WLAN_80211_CIPHER_SUITE_BIP_GMAC_128 = 11,           /* BIP GMAC 128 */
    WLAN_80211_CIPHER_SUITE_BIP_GMAC_256 = 12,           /* BIP GMAC 256 */
    WLAN_80211_CIPHER_SUITE_BIP_CMAC_256 = 13,           /* BIP CMAC 256 */

    WLAN_80211_CIPHER_SUITE_WAPI         = 14,           /* ??????????????11i???? */
} wlan_ciper_protocol_type_enum;
typedef oal_uint8 wlan_ciper_protocol_type_enum_uint8;

/* ????80211-2012 ???? Table 8-101 AKM suite selectors ???? */
#define WLAN_AUTH_SUITE_RSV              0
#define WLAN_AUTH_SUITE_1X               1
#define WLAN_AUTH_SUITE_PSK              2
#define WLAN_AUTH_SUITE_FT_1X            3
#define WLAN_AUTH_SUITE_FT_PSK           4
#define WLAN_AUTH_SUITE_1X_SHA256        5
#define WLAN_AUTH_SUITE_PSK_SHA256       6
#define WLAN_AUTH_SUITE_TDLS             7
#define WLAN_AUTH_SUITE_SAE_SHA256       8
#define WLAN_AUTH_SUITE_FT_SHA256        9

typedef enum
{
    WITP_WPA_VERSION_1 = 1,
    WITP_WPA_VERSION_2 = 2,
#ifdef _PRE_WLAN_WEB_CMD_COMM
    WITP_WPA_VERSION_C = 3,
#endif
#ifdef _PRE_WLAN_FEATURE_WAPI
    WITP_WAPI_VERSION = 1 << 2,
#endif
}witp_wpa_versions_enum;
typedef oal_uint8 witp_wpa_versions_enum_uint8;


typedef struct
{
    wlan_cipher_key_type_enum_uint8          en_cipher_key_type;      /* ????ID/???? */
    wlan_ciper_protocol_type_enum_uint8      en_cipher_protocol_type;
    oal_uint8                                uc_cipher_key_id;
    oal_uint8                                auc_resv[1];
}wlan_security_txop_params_stru;

/* ???????????? */
typedef enum
{
    WLAN_PROTOCOL_CAP_LEGACY,
    WLAN_PROTOCOL_CAP_HT,
    WLAN_PROTOCOL_CAP_VHT,
#ifdef _PRE_WLAN_FEATURE_11AX
    WLAN_PROTOCOL_CAP_HE,
#endif

    WLAN_PROTOCOL_CAP_BUTT,
}wlan_protocol_cap_enum;
typedef oal_uint8 wlan_protocol_cap_enum_uint8;

/* ???????????? */
typedef enum
{
    WLAN_BAND_CAP_2G,        /* ??????2G */
    WLAN_BAND_CAP_5G,        /* ??????5G */
    WLAN_BAND_CAP_2G_5G,     /* ????2G 5G */

    WLAN_BAND_CAP_BUTT
}wlan_band_cap_enum;
typedef oal_uint8 wlan_band_cap_enum_uint8;

/* ???????????? */
typedef enum
{
    WLAN_BW_CAP_20M,
    WLAN_BW_CAP_40M,
    WLAN_BW_CAP_80M,
    WLAN_BW_CAP_160M,
    WLAN_BW_CAP_80PLUS80,    /* ??????80+80 */

    WLAN_BW_CAP_BUTT
}wlan_bw_cap_enum;
typedef oal_uint8 wlan_bw_cap_enum_uint8;

/* ???????????? */
typedef enum
{
    WLAN_MOD_DSSS,
    WLAN_MOD_OFDM,

    WLAN_MOD_BUTT
}wlan_mod_enum;
typedef oal_uint8 wlan_mod_enum_uint8;

typedef enum
{
   REGDOMAIN_FCC        = 0,
   REGDOMAIN_ETSI       = 1,
   REGDOMAIN_JAPAN      = 2,
   REGDOMAIN_COMMON     = 3,

   REGDOMAIN_COUNT
} regdomain_enum;
typedef oal_uint8 regdomain_enum_uint8;


/*****************************************************************************
  3.4 VHT????????
*****************************************************************************/

typedef enum
{
    WLAN_VHT_MCS0,
    WLAN_VHT_MCS1,
    WLAN_VHT_MCS2,
    WLAN_VHT_MCS3,
    WLAN_VHT_MCS4,
    WLAN_VHT_MCS5,
    WLAN_VHT_MCS6,
    WLAN_VHT_MCS7,
    WLAN_VHT_MCS8,
    WLAN_VHT_MCS9,
#ifdef _PRE_WLAN_FEATURE_1024QAM
    WLAN_VHT_MCS10,
    WLAN_VHT_MCS11,
#endif

    WLAN_VHT_MCS_BUTT,
}wlan_vht_mcs_enum;
typedef oal_uint8 wlan_vht_mcs_enum_uint8;

/*
    ????1101??????????
    TBD???????S??????????????????????????
*/
typedef enum
{
    WLAN_LEGACY_11b_RESERVED1       = 0,
    WLAN_SHORT_11b_2M_BPS           = 1,
    WLAN_SHORT_11b_5_HALF_M_BPS     = 2,
    WLAN_SHORT_11b_11_M_BPS         = 3,

    WLAN_LONG_11b_1_M_BPS           = 4,
    WLAN_LONG_11b_2_M_BPS           = 5,
    WLAN_LONG_11b_5_HALF_M_BPS      = 6,
    WLAN_LONG_11b_11_M_BPS          = 7,

    WLAN_LEGACY_OFDM_48M_BPS        = 8,
    WLAN_LEGACY_OFDM_24M_BPS        = 9,
    WLAN_LEGACY_OFDM_12M_BPS        = 10,
    WLAN_LEGACY_OFDM_6M_BPS         = 11,
    WLAN_LEGACY_OFDM_54M_BPS        = 12,
    WLAN_LEGACY_OFDM_36M_BPS        = 13,
    WLAN_LEGACY_OFDM_18M_BPS        = 14,
    WLAN_LEGACY_OFDM_9M_BPS         = 15,

    WLAN_LEGACY_RATE_VALUE_BUTT
}wlan_legacy_rate_value_enum;
typedef oal_uint8 wlan_legacy_rate_value_enum_uint8;

/* WIFI???????????? */
typedef enum
{
    WLAN_LEGACY_11A_MODE            = 0,    /* 11a, 5G, OFDM */
    WLAN_LEGACY_11B_MODE            = 1,    /* 11b, 2.4G */
    WLAN_LEGACY_11G_MODE            = 2,    /* ????11g only??????, 2.4G, OFDM */
    WLAN_MIXED_ONE_11G_MODE         = 3,    /* 11bg, 2.4G */
    WLAN_MIXED_TWO_11G_MODE         = 4,    /* 11g only, 2.4G */
    WLAN_HT_MODE                    = 5,    /* 11n(11bgn????11an??????????????) */
    WLAN_VHT_MODE                   = 6,    /* 11ac */
    WLAN_HT_ONLY_MODE               = 7,    /* 11n only mode,??????HT???????????????? */
    WLAN_VHT_ONLY_MODE              = 8,    /* 11ac only mode ??????VHT???????????????? */
    WLAN_HT_11G_MODE                = 9,    /* 11ng,??????11b*/
#if defined(_PRE_WLAN_FEATURE_11AX) || defined(_PRE_WLAN_FEATURE_11AX_ROM)
    WLAN_HE_MODE                    = 10,   /*11ax*/
#endif

    WLAN_PROTOCOL_BUTT
}wlan_protocol_enum;
typedef oal_uint8 wlan_protocol_enum_uint8;

/* ????:????VAP??preamble??????????????????????0????long preamble; 1????short preamble */
typedef enum
{
    WLAN_LEGACY_11B_MIB_LONG_PREAMBLE    = 0,
    WLAN_LEGACY_11B_MIB_SHORT_PREAMBLE   = 1,
}wlan_11b_mib_preamble_enum;
typedef oal_uint8 wlan_11b_mib_preamble_enum_uint8;

/* ????:??????????????????(??????????????????pramble????)??0????short preamble; 1????long preamble */
typedef enum
{
    WLAN_LEGACY_11B_DSCR_SHORT_PREAMBLE  = 0,
    WLAN_LEGACY_11B_DSCR_LONG_PREAMBLE   = 1,

    WLAN_LEGACY_11b_PREAMBLE_BUTT
}wlan_11b_dscr_preamble_enum;
typedef oal_uint8 wlan_11b_dscr_preamble_enum_uint8;

/*****************************************************************************
  3.3 HT????????
*****************************************************************************/
typedef enum
{
    WLAN_BAND_WIDTH_20M                 = 0,
    WLAN_BAND_WIDTH_40PLUS,                     /* ??20????+1 */
    WLAN_BAND_WIDTH_40MINUS,                    /* ??20????-1 */
    WLAN_BAND_WIDTH_80PLUSPLUS,                 /* ??20????+1, ??40????+1 */
    WLAN_BAND_WIDTH_80PLUSMINUS,                /* ??20????+1, ??40????-1 */
    WLAN_BAND_WIDTH_80MINUSPLUS,                /* ??20????-1, ??40????+1 */
    WLAN_BAND_WIDTH_80MINUSMINUS,               /* ??20????-1, ??40????-1 */
#ifdef _PRE_WLAN_FEATURE_160M
    WLAN_BAND_WIDTH_160PLUSPLUSPLUS,            /* ??20????+1, ??40????+1, ??80????+1 */
    WLAN_BAND_WIDTH_160PLUSPLUSMINUS,           /* ??20????+1, ??40????+1, ??80????-1 */
    WLAN_BAND_WIDTH_160PLUSMINUSPLUS,           /* ??20????+1, ??40????-1, ??80????+1 */
    WLAN_BAND_WIDTH_160PLUSMINUSMINUS,          /* ??20????+1, ??40????-1, ??80????-1 */
    WLAN_BAND_WIDTH_160MINUSPLUSPLUS,           /* ??20????-1, ??40????+1, ??80????+1 */
    WLAN_BAND_WIDTH_160MINUSPLUSMINUS,          /* ??20????-1, ??40????+1, ??80????-1 */
    WLAN_BAND_WIDTH_160MINUSMINUSPLUS,          /* ??20????-1, ??40????-1, ??80????+1 */
    WLAN_BAND_WIDTH_160MINUSMINUSMINUS,         /* ??20????-1, ??40????-1, ??80????-1 */
#endif
    WLAN_BAND_WIDTH_40M,
    WLAN_BAND_WIDTH_80M,
    WLAN_BAND_WIDTH_BUTT
}wlan_channel_bandwidth_enum;
typedef oal_uint8 wlan_channel_bandwidth_enum_uint8;

typedef enum
{
    WLAN_CH_SWITCH_DONE     = 0,   /* ??????????????????AP???????????? */
    WLAN_CH_SWITCH_STATUS_1 = 1,   /* AP??????????????????????????????(????CSA??/IE) */
    WLAN_CH_SWITCH_STATUS_2 = 2,

    WLAN_CH_SWITCH_BUTT
}wlan_ch_switch_status_enum;
typedef oal_uint8 wlan_ch_switch_status_enum_uint8;
typedef enum
  {
    WLAN_AP_CHIP_OUI_NORMAL     = 0,
    WLAN_AP_CHIP_OUI_RALINK     = 1,   /* ??????????RALINK */
    WLAN_AP_CHIP_OUI_RALINK1    = 2,
    WLAN_AP_CHIP_OUI_ATHEROS    = 3,   /* ??????????ATHEROS */
    WLAN_AP_CHIP_OUI_BCM        = 4,   /* ??????????BROADCOM */

    WLAN_AP_CHIP_OUI_BUTT
}wlan_ap_chip_oui_enum;
typedef oal_uint8 wlan_ap_chip_oui_enum_uint8;


typedef enum
{
    WLAN_CSA_MODE_TX_ENABLE = 0,
    WLAN_CSA_MODE_TX_DISABLE,

    WLAN_CSA_MODE_TX_BUTT
}wlan_csa_mode_tx_enum;
typedef oal_uint8 wlan_csa_mode_tx_enum_uint8;


typedef enum
{
    WLAN_BW_SWITCH_DONE     = 0,    /* ?????????????? */
    WLAN_BW_SWITCH_40_TO_20 = 1,    /* ??40MHz??????????20MHz???? */
    WLAN_BW_SWITCH_20_TO_40 = 2,    /* ??20MHz??????????40MHz???? */

    /* ???????? */

    WLAN_BW_SWITCH_BUTT
}wlan_bw_switch_status_enum;
typedef oal_uint8 wlan_bw_switch_status_enum_uint8;


typedef enum
{
    WLAN_BAND_ASSEMBLE_20M                   = 0,

    WLAN_BAND_ASSEMBLE_40M                   = 4,
    WLAN_BAND_ASSEMBLE_40M_DUP               = 5,

    WLAN_BAND_ASSEMBLE_80M                   = 8,
    WLAN_BAND_ASSEMBLE_80M_DUP               = 9,

    WLAN_BAND_ASSEMBLE_160M                  = 12,
    WLAN_BAND_ASSEMBLE_160M_DUP              = 13,

    WLAN_BAND_ASSEMBLE_80M_80M               = 15,

    WLAN_BAND_ASSEMBLE_AUTO,

    WLAN_BAND_ASSEMBLE_BUTT
}hal_channel_assemble_enum;
typedef oal_uint8 hal_channel_assemble_enum_uint8;


typedef enum
{
    WLAN_HT_MIXED_PREAMBLE          = 0,
    WLAN_HT_GF_PREAMBLE             = 1,

    WLAN_HT_PREAMBLE_BUTT
}wlan_ht_preamble_enum;
typedef oal_uint8 wlan_ht_preamble_enum_uint8;

typedef enum
{
    WLAN_HT_MCS0,
    WLAN_HT_MCS1,
    WLAN_HT_MCS2,
    WLAN_HT_MCS3,
    WLAN_HT_MCS4,
    WLAN_HT_MCS5,
    WLAN_HT_MCS6,
    WLAN_HT_MCS7,
    WLAN_HT_MCS8,
    WLAN_HT_MCS9,
    WLAN_HT_MCS10,
    WLAN_HT_MCS11,
    WLAN_HT_MCS12,
    WLAN_HT_MCS13,
    WLAN_HT_MCS14,
    WLAN_HT_MCS15,

    WLAN_HT_MCS_BUTT
}wlan_ht_mcs_enum;
typedef oal_uint8 wlan_ht_mcs_enum_uint8;
#define WLAN_HT_MCS32   32
#define WLAN_MIN_MPDU_LEN_FOR_MCS32   12
#define WLAN_MIN_MPDU_LEN_FOR_MCS32_SHORTGI   13

/* ?????????? */
#define WLAN_SINGLE_NSS                 0
#define WLAN_DOUBLE_NSS                 1
#define WLAN_TRIPLE_NSS                 2
#define WLAN_FOUR_NSS                   3
#define WLAN_NSS_LIMIT                   4
/* ?????????????????????????????????????????????????????????????????????? */
typedef oal_uint8 wlan_nss_enum_uint8;

typedef enum
{
    WLAN_HT_NON_STBC                   = 0,
    WLAN_HT_ADD_ONE_NTS                = 1,
    WLAN_HT_ADD_TWO_NTS                = 2,

    WLAN_HT_STBC_BUTT
}wlan_ht_stbc_enum;
typedef oal_uint8 wlan_ht_stbc_enum_uint8;

typedef enum
{
    WLAN_NO_SOUNDING                = 0,
    WLAN_NDP_SOUNDING               = 1,
    WLAN_STAGGERED_SOUNDING         = 2,
    WLAN_LEGACY_SOUNDING            = 3,

    WLAN_SOUNDING_BUTT
}wlan_sounding_enum;
typedef oal_uint8 wlan_sounding_enum_uint8;

typedef struct
{
    oal_uint8                               uc_group_id;      /* group_id   */
    oal_uint8                               uc_txop_ps_not_allowed;
    oal_uint16                              us_partial_aid;   /* partial_aid */
}wlan_groupid_partial_aid_stru;


/* channel?????? */
typedef struct
{
    oal_uint8                           uc_chan_number;     /* ??20MHz?????? */
    wlan_channel_band_enum_uint8        en_band;            /* ???? */
    wlan_channel_bandwidth_enum_uint8   en_bandwidth;       /* ???????? */
    oal_uint8                           uc_chan_idx;        /* ?????????? */
}mac_channel_stru;

/*****************************************************************************
  3.4 ??????,????????
*****************************************************************************/
typedef enum
{
    WLAN_NON_TXBF                   = 0,
    WLAN_EXPLICIT_TXBF              = 1,
    WLAN_LEGACY_TXBF                = 2,

    WLAN_TXBF_BUTT
}wlan_txbf_enum;
typedef oal_uint8 wlan_txbf_enum_uint8;

/* TPC???????? */
typedef enum
{
    WLAN_TPC_WORK_MODE_DISABLE        = 0,   /* ????TPC????????????????: ??????????????????????????????Data0??????????, Data1~3?????????????????????????????? */
    WLAN_TPC_WORK_MODE_ENABLE         = 1,   /* ??????????????: ????????Data0??????????????, Data1~3?????????????????????????????? */

    WLAN_TPC_WORK_MODE_BUTT
}wlan_tpc_work_mode_enum;
typedef oal_uint8 wlan_tpc_mode_enum_uint8;

/* CCA_OPT???????? */
#define WLAN_CCA_OPT_DISABLE                0   /* ???????????? */
#define WLAN_CCA_OPT_ENABLE                 1   /* ??????????????EDCA???? */

/* EDCA_OPT STA?????????????? */
#define WLAN_EDCA_OPT_STA_DISABLE           0   /* ???????????? */
#define WLAN_EDCA_OPT_STA_ENABLE            1   /* ??????????????EDCA???? */

/* EDCA_OPT AP?????????????? */
#define WLAN_EDCA_OPT_AP_EN_DISABLE         0   /* ???????????? */
#define WLAN_EDCA_OPT_AP_EN_DEFAULT         1   /* ??????????????EDCA???? */
#define WLAN_EDCA_OPT_AP_EN_WITH_COCH       2   /* ?????????????????? */

/* ?????????????????????? */
#define WLAN_ANTI_INTF_EN_OFF               0   /* ???????? */
#define WLAN_ANTI_INTF_EN_ON                1   /* ???????? */
#define WLAN_ANTI_INTF_EN_PROBE             2   /* ??????????????????/?? */

/* ????byass????LNA???????? */
#define WLAN_EXTLNA_BYPASS_EN_OFF               0   /* ????bypass????LNA?? */
#define WLAN_EXTLNA_BYPASS_EN_ON                1   /* ????bypass????LNA?? */
#define WLAN_EXTLNA_BYPASS_EN_FORCE             2   /* ????bypass????LNA?????? */

/* DFS???????? */
#define WLAN_DFS_EN_OFF               0   /* ???????? */
#define WLAN_DFS_EN_ON                1   /* ????????,?????????????????? */

/*****************************************************************************
  3.5 WME????????
*****************************************************************************/

/*WMM????????????????*/

/* ?????? (2-bit) */
typedef enum
{
    WLAN_MANAGEMENT            = 0,
    WLAN_CONTROL               = 1,
    WLAN_DATA_BASICTYPE        = 2,
    WLAN_RESERVED              = 3,

    WLAN_FRAME_TYPE_BUTT
} wlan_frame_type_enum;
typedef oal_uint8 wlan_frame_type_enum_uint8;

/* ???????? (4-bit) */
/* ????????????????????SPEC */

/* ?????????????? */
typedef enum
{
    /* 0~6 reserved */
    WLAN_HE_TRIG_FRAME          = 2,     /* 0010 */
    WLAN_VHT_NDPA               = 5,     /* 0101 */
    WLAN_CONTROL_WRAPPER        = 7,
    WLAN_BLOCKACK_REQ           = 8,
    WLAN_BLOCKACK               = 9,
    WLAN_PS_POLL                = 10,
    WLAN_RTS                    = 11,
    WLAN_CTS                    = 12,
    WLAN_ACK                    = 13,
    WLAN_CF_END                 = 14,
    WLAN_CF_END_CF_ACK          = 15,

    WLAN_CONTROL_SUBTYPE_BUTT   = 16,
}wlan_frame_control_subtype_enum;

/* ???????????? */
typedef enum
{
    WLAN_DATA                   = 0,
    WLAN_DATA_CF_ACK            = 1,
    WLAN_DATA_CF_POLL           = 2,
    WLAN_DATA_CF_ACK_POLL       = 3,
    WLAN_NULL_FRAME             = 4,
    WLAN_CF_ACK                 = 5,
    WLAN_CF_POLL                = 6,
    WLAN_CF_ACK_POLL            = 7,
    WLAN_QOS_DATA               = 8,
    WLAN_QOS_DATA_CF_ACK        = 9,
    WLAN_QOS_DATA_CF_POLL       = 10,
    WLAN_QOS_DATA_CF_ACK_POLL   = 11,
    WLAN_QOS_NULL_FRAME         = 12,
    WLAN_DATA_SUBTYPE_RESV1     = 13,
    WLAN_QOS_CF_POLL            = 14,
    WLAN_QOS_CF_ACK_POLL        = 15,

    WLAN_DATA_SUBTYPE_MGMT      = 16,
}wlan_frame_data_subtype_enum;

/* ACK???????? */
typedef enum
{
    WLAN_TX_NORMAL_ACK = 0,
    WLAN_TX_NO_ACK,
    WLAN_TX_NO_EXPLICIT_ACK,
    WLAN_TX_BLOCK_ACK,

    WLAN_TX_NUM_ACK_BUTT
}wlan_tx_ack_policy_enum;
typedef oal_uint8   wlan_tx_ack_policy_enum_uint8;

/* Trig?????????? */
typedef enum
{
    WLAN_HE_BASIC_TRIG              = 0,
    WLAN_BEAM_REPORT_POLL           = 1,
    WLAN_MU_BAR                     = 2,
    WLAN_MU_RTS                     = 3,
    WLAN_BUFFER_STATUS_REPORT_POLL  = 4,
    WLAN_GCR_MU_BAR                 = 5,
    WLAN_BW_QUERY_REPORT_POLL       = 6,
    WLAN_NDP_FEEDBACK_REPORT_POLL   = 7,

    WLAN_HE_TRIG_TYPE_BUTT
}wlan_frame_trig_type_enum;

/*****************************************************************************
  3.6 ????????
*****************************************************************************/

/* ???????????? */
typedef enum
{
    WLAN_BCC_CODE                   = 0,
    WLAN_LDPC_CODE                  = 1,
    WLAN_CHANNEL_CODE_BUTT
}wlan_channel_code_enum;
typedef oal_uint8 wlan_channel_code_enum_uint8;

/* ???????? */
typedef enum
{
    WLAN_SCAN_TYPE_PASSIVE       = 0,
    WLAN_SCAN_TYPE_ACTIVE        = 1,

    WLAN_SCAN_TYPE_BUTT
}wlan_scan_type_enum;
typedef oal_uint8 wlan_scan_type_enum_uint8;

/* ???????? */
typedef enum
{
    WLAN_SCAN_MODE_FOREGROUND     = 0,          /* ????????????AP/STA(??????????????????) */
    WLAN_SCAN_MODE_BACKGROUND_STA = 1,      /* STA???????? */
    WLAN_SCAN_MODE_BACKGROUND_AP  = 2,       /* AP????????(??????) */
    WLAN_SCAN_MODE_BACKGROUND_OBSS = 3,     /* 20/40MHz??????obss???? */
    WLAN_SCAN_MODE_BACKGROUND_CCA  = 4,
    WLAN_SCAN_MODE_BACKGROUND_PNO  = 5,      /* PNO???????? */
    WLAN_SCAN_MODE_RRM_BEACON_REQ  = 6,
    WLAN_SCAN_MODE_BACKGROUND_CSA  = 7,      /* ???????????? */
    WLAN_SCAN_MODE_BACKGROUND_HILINK = 8,   /* hilink?????????????? */
    WLAN_SCAN_MODE_FTM_REQ      = 9,
    WLAN_SCAN_MODE_GNSS_SCAN    = 10,
    WLAN_SCAN_MODE_ROAM_SCAN    = 11,

    WLAN_SCAN_MODE_BUTT
} wlan_scan_mode_enum;
typedef oal_uint8 wlan_scan_mode_enum_uint8;

/*Android P ????????????????????????????*/
typedef enum
{
    WLAN_SCAN_FLAG_LOW_PRIORITY  = 0,
    WLAN_SCAN_FLAG_LOW_FLUSH     = 1,
    WLAN_SCAN_FLAG_AP            = 2,
    WLAN_SCAN_FLAG_RANDOM_ADDR   = 3,
    WLAN_SCAN_FLAG_LOW_SPAN      = 4,/*????????*/
    WLAN_SCAN_FLAG_LOW_POWER     = 5,
    WLAN_SCAN_FLAG_HIFH_ACCURACY = 6,/*????????,?????? */
    WLAN_SCAN_FLAG_BUTT
} wlan_scan_flag_enum;

/*???????? flag??????*/
typedef enum
{
    WLAN_NL80211_SCAN_FLAG_BIT_LOW_PRIORITY   = 0,
    WLAN_NL80211_SCAN_FLAG_BIT_FLUSH          = 1,
    WLAN_NL80211_SCAN_FLAG_BIT_AP             = 2,
    WLAN_NL80211_SCAN_FLAG_BIT_RANDOM_ADDR    = 3,
    WLAN_NL80211_SCAN_FLAG_BIT_LOW_SPAN       = 8,
    WLAN_NL80211_SCAN_FLAG_BIT_LOW_POWER      = 9,
    WLAN_NL80211_SCAN_FLAG_BIT_HIGH_ACCURACY  = 10,
    WLAN_NL80211_SCAN_FLAG_BIT_BUTT
}wlan_nl80211_scan_flag_bit_enum;

/* ???????????? */
typedef enum
{
    WLAN_SCAN_EVENT_COMPLETE    = 0,
    WLAN_SCAN_EVENT_FAILED,
    WLAN_SCAN_EVENT_ABORT,  /* ?????????????????? */
    WLAN_SCAN_EVENT_TIMEOUT,
    WLAN_SCAN_EVENT_BUTT
}dmac_scan_event_enum;
typedef oal_uint8 wlan_scan_event_enum_uint8;

typedef enum
{
    WLAN_LEGACY_VAP_MODE     = 0,    /* ??P2P???? */
    WLAN_P2P_GO_MODE         = 1,    /* P2P_GO */
    WLAN_P2P_DEV_MODE        = 2,    /* P2P_Device */
    WLAN_P2P_CL_MODE         = 3,    /* P2P_CL */

    WLAN_P2P_BUTT
}wlan_p2p_mode_enum;
typedef oal_uint8 wlan_p2p_mode_enum_uint8;

/*****************************************************************************
  3.7 ????????
*****************************************************************************/

/* pmf?????? */
typedef enum
{
    MAC_PMF_DISABLED  = 0, /* ??????pmf???? */
    MAC_PMF_ENABLED,       /* ????pmf?????????????? */
    MAC_PMF_REQUIRED,       /* ????????pmf???? */

    MAC_PMF_BUTT
}wlan_pmf_cap_status;
typedef oal_uint8 wlan_pmf_cap_status_uint8;

/* ???????????? */
typedef enum
{
    WLAN_DISTANCE_NEAR       = 0,
    WLAN_DISTANCE_NORMAL     = 1,
    WLAN_DISTANCE_FAR        = 2,

    WLAN_DISTANCE_BUTT
}wlan_user_distance_enum;
typedef oal_uint8 wlan_user_distance_enum_uint8;

/*****************************************************************************
  3.8 linkloss????????
*****************************************************************************/

/*linkloss????????*/
typedef enum
{
    WLAN_LINKLOSS_MODE_BT = 0,
    WLAN_LINKLOSS_MODE_DBAC,
    WLAN_LINKLOSS_MODE_NORMAL,

    WLAN_LINKLOSS_MODE_BUTT
}wlan_linkloss_mode_enum;
typedef oal_uint8 wlan_linkloss_mode_enum_uint8;

typedef enum
{
    WALN_LINKLOSS_SCAN_SWITCH_CHAN_DISABLE = 0,
    WALN_LINKLOSS_SCAN_SWITCH_CHAN_EN      = 1,

    WALN_LINKLOSS_SCAN_SWITCH_CHAN_BUTT
}wlan_linkloss_scan_switch_chan_enum;
typedef oal_uint8 wlan_linkloss_scan_switch_chan_enum_uint8;


/*****************************************************************************
  3.9 roc????????
*****************************************************************************/

typedef enum {
    IEEE80211_ROC_TYPE_NORMAL  = 0,
    IEEE80211_ROC_TYPE_MGMT_TX,
    IEEE80211_ROC_TYPE_BUTT,
}wlan_ieee80211_roc_type;
typedef oal_uint8 wlan_ieee80211_roc_type_uint8;

/*****************************************************************************
  3.10 roam????????
*****************************************************************************/
/* ???????????? */
typedef enum
{
    WLAN_ROAM_MAIN_BAND_STATE_2TO2          = 0,
    WLAN_ROAM_MAIN_BAND_STATE_5TO2          = 1,
    WLAN_ROAM_MAIN_BAND_STATE_2TO5          = 2,
    WLAN_ROAM_MAIN_BAND_STATE_5TO5          = 3,

    WLAN_ROAM_MAIN_BAND_STATE_BUTT
}wlan_roam_main_band_state_enum;
typedef oal_uint8  wlan_roam_main_band_state_enum_uint8;

/*****************************************************************************
  3.10 m2s????????
*****************************************************************************/
/* mimo-siso????tpye */
typedef enum
{
    WLAN_M2S_TYPE_SW = 0,
    WLAN_M2S_TYPE_HW = 1,

    WLAN_M2S_TYPE_BUTT,
}wlan_m2s_tpye_enum;
typedef oal_uint8 wlan_m2s_type_enum_uint8;

/*ldac m2s  ????????????*/
typedef enum
{
    WLAN_M2S_LDAC_RSSI_TO_SISO = 0,
    WLAN_M2S_LDAC_RSSI_TO_MIMO,

    WLAN_M2S_LDAC_RSSI_BUTT
}wlan_m2s_ldac_rssi_th_enum;
typedef oal_uint8 wlan_m2s_ldac_rssi_th_enum_uint8;

/* mimo-siso????mode */
typedef enum
{
    WLAN_M2S_TRIGGER_MODE_DBDC      = BIT0,
    WLAN_M2S_TRIGGER_MODE_FAST_SCAN = BIT1,
    WLAN_M2S_TRIGGER_MODE_RSSI      = BIT2,
    WLAN_M2S_TRIGGER_MODE_BTCOEX    = BIT3,
    WLAN_M2S_TRIGGER_MODE_COMMAND   = BIT4,
    WLAN_M2S_TRIGGER_MODE_TEST      = BIT5,
    WLAN_M2S_TRIGGER_MODE_CUSTOM    = BIT6,   /* ?????????????????????????????? */
    WLAN_M2S_TRIGGER_MODE_SPEC      = BIT7,   /* spec?????????????????????? */

    WLAN_M2S_TRIGGER_MODE_BUTT,
}wlan_m2s_trigger_mode_enum;
typedef oal_uint8 wlan_m2s_trigger_mode_enum_uint8;

typedef enum
{
    WLAN_OFDM_ACK_CTS_TYPE_24M = 0,
    WLAN_OFDM_ACK_CTS_TYPE_36M = 1,
    WLAN_OFDM_ACK_CTS_TYPE_48M = 2,
    WLAN_OFDM_ACK_CTS_TYPE_54M = 3,
    WLAN_OFDM_ACK_CTS_TYPE_BUTT,
}wlan_ofdm_ack_cts_type_enum;
typedef oal_uint8 wlan_ofdm_ack_cts_type_enum_uint8;

/*****************************************************************************
  3.11 m2s????????
*****************************************************************************/
typedef enum
{
    WLAN_SPECIAL_FRM_RTS,
    WLAN_SPECIAL_FRM_ONE_PKT,
    WLAN_SPECIAL_FRM_ABORT_SELFCTS,
    WLAN_SPECIAL_FRM_ABORT_CFEND,
    WLAN_SPECIAL_FRM_CFEND,
    WLAN_SPECIAL_FRM_NDP,
    WLAN_SPECIAL_FRM_VHT_REPORT,
    WLAN_SPECIAL_FRM_ABORT_NULL_DATA,
    WLAN_SPECIAL_FRM_BUTT,
}wlan_special_frm_enum;
typedef oal_uint8 wlan_special_frm_enum_uint8;


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
typedef struct
{
    oal_uint32                      ul_cipher;                      /*????????*/
    oal_uint32                      ul_key_len;                     /*??????*/
    oal_uint32                      ul_seq_len;                     /*sequnece??*/
    oal_uint8                       auc_key[WLAN_WPA_KEY_LEN];      /*????*/
    oal_uint8                       auc_seq[WLAN_WPA_SEQ_LEN];      /*sequence*/
}wlan_priv_key_param_stru;

/* DMAC SCAN ?????????????????????? */
typedef struct
{
    oal_uint8   uc_channel_number;      /* ?????? */
    oal_uint8   uc_stats_valid;
    oal_uint8   uc_stats_cnt;           /* ?????????????????? */
    oal_uint8   uc_free_power_cnt;      /* ???????????? */

    /* PHY???????????? */
    oal_uint8   uc_bandwidth_mode;
    oal_uint8   auc_resv[1];
    oal_int16   s_free_power_stats_20M;
    oal_int16   s_free_power_stats_40M;
    oal_int16   s_free_power_stats_80M;

    /* MAC???????????? */
    oal_uint32  ul_total_stats_time_us;
    oal_uint32  ul_total_free_time_20M_us;
    oal_uint32  ul_total_free_time_40M_us;
    oal_uint32  ul_total_free_time_80M_us;
    oal_uint32  ul_total_send_time_us;
    oal_uint32  ul_total_recv_time_us;

    oal_uint8   uc_radar_detected;  // FIXME: feed value
    oal_uint8   uc_radar_bw;
    oal_uint8   uc_radar_type;
    oal_uint8   uc_radar_freq_offset;

    oal_int16   s_free_power_stats_160M;
    oal_uint16  us_phy_total_stats_time_ms;
}wlan_scan_chan_stats_stru;

typedef struct
{
    oal_uint16  us_chan_ratio_20M;
    oal_uint16  us_chan_ratio_40M;
    oal_uint16  us_chan_ratio_80M;
    oal_int8    c_free_power_20M;
    oal_int8    c_free_power_40M;
    oal_int8    c_free_power_80M;
    oal_uint8   auc_resv[3];
    oal_uint8   _rom[4];
}wlan_chan_ratio_stru;

/* m2s???????? */
typedef struct
{
    oal_uint8   bit_dbdc         : 1,        /* dbdc???? */
                bit_fast_on      : 1,        /* ???????????? */
                bit_rssi_snr     : 1,        /* rssi/snr???? */
                bit_btcoex       : 1,        /* btcoex???? */
                bit_command      : 1,        /* ???????????? */
                bit_test         : 1,        /* ???????????? */
                bit_custom       : 1,        /* ?????????? */
                bit_spec         : 1;        /* RF???????? */
}wlan_m2s_mode_stru;

/* action?????????????? */
typedef enum
{
    WLAN_M2S_ACTION_TYPE_SMPS      = 0,         /* action????smps */
    WLAN_M2S_ACTION_TYPE_OPMODE    = 1,         /* action????opmode */
    WLAN_M2S_ACTION_TYPE_NONE      = 2,         /* ????????action?? */

    WLAN_M2S_ACTION_TYPE_BUTT,
}wlan_m2s_action_type_enum;
typedef oal_uint8 wlan_m2s_action_type_enum_uint8;

typedef struct
{
    oal_uint8 auc_user_mac_addr[WLAN_MAC_ADDR_LEN];           /* ??????????AP MAC???? */
    wlan_m2s_action_type_enum_uint8  en_action_type;          /* ??????????????????action??????????????vap??ori???????? */
    oal_bool_enum_uint8   en_m2s_result;   /* ????????????????action????????vap???????????????? */
} wlan_m2s_mgr_vap_stru;

/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/

OAL_STATIC OAL_INLINE oal_uint8  wlan_hdr_get_frame_type(oal_uint8 *puc_header)
{
    return ((puc_header[0] & (0x0c)) >> 2);
}

/*****************************************************************************
  10 ????????
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of wlan_types.h */
