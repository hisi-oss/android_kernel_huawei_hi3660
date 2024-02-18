

#ifndef __HMAC_BTCOEX_H__
#define __HMAC_BTCOEX_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "frw_ext_if.h"
#include "oal_ext_if.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_BTCOEX_H

/*****************************************************************************
  2 ??????
*****************************************************************************/
#define BTCOEX_BSS_NUM_IN_BLACKLIST 16
#define BTCOEX_ARP_FAIL_DELBA_NUM   2
#define BTCOEX_ARP_FAIL_REASSOC_NUM 4
#define BTCOEX_ARP_PROBE_TIMEOUT        (300)  //ms

/*****************************************************************************
  3 ????????
*****************************************************************************/
typedef enum
{
    BTCOEX_BLACKLIST_TPYE_FIX_BASIZE  = 0,
    BTCOEX_BLACKLIST_TPYE_NOT_AGGR    = 1,

    BTCOEX_BLACKLIST_TPYE_BUTT
}btcoex_blacklist_type_enum;
typedef oal_uint8 btcoex_blacklist_type_enum_uint8;

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
    oal_uint16 us_last_baw_start;       /* ????????????ADDBA REQ????baw_start?? */
    oal_uint16 us_last_seq_num;         /* ????????????ADDBA REQ????seq_num?? */
    btcoex_blacklist_type_enum_uint8 en_blacklist_tpye;     /* ?????????? */
    oal_bool_enum_uint8              en_ba_handle_allow;    /* ??????????1:???????????????????? ??????????2:???????????????? */
} hmac_btcoex_addba_req_stru;

typedef struct
{
    oal_uint8 auc_user_mac_addr[WLAN_MAC_ADDR_LEN];     /* ??????MAC???? */
    oal_uint8 uc_type;                                  /* ???????????????? */
    oal_uint8 uc_used;                                  /* ??????????????????MAC???? */
} hmac_btcoex_delba_exception_stru;

typedef struct
{
    frw_timeout_stru st_delba_opt_timer;    /* ????ARP REQ???????????? */
    oal_atomic ul_rx_unicast_pkt_to_lan;    /* ?????????????????? */
} hmac_btcoex_arp_req_process_stru;

typedef struct
{
    hmac_btcoex_delba_exception_stru ast_hmac_btcoex_delba_exception[BTCOEX_BSS_NUM_IN_BLACKLIST];
    oal_uint8 uc_exception_bss_index;       /* ??????MAC?????????????? */
    oal_uint8 auc_resv[3];
} hmac_device_btcoex_stru;

typedef struct
{
    hmac_btcoex_arp_req_process_stru st_hmac_btcoex_arp_req_process;
    hmac_btcoex_addba_req_stru       st_hmac_btcoex_addba_req;
    oal_uint16                       us_ba_size;
    oal_uint8                        uc_rx_no_pkt_count;                /* ?????????????????????????? */
    oal_bool_enum_uint8              en_delba_btcoex_trigger;           /* ????btcoex????????BA */
    oal_bool_enum_uint8              en_arp_probe_on;                   /* ????????arp?????????????????? */
} hmac_user_btcoex_stru;

#define HMAC_BTCOEX_GET_BLACKLIST_TYPE(_pst_hmac_user) \
    ((_pst_hmac_user)->st_hmac_user_btcoex.st_hmac_btcoex_addba_req.en_blacklist_tpye)

#define HMAC_BTCOEX_GET_BLACKLIST_DELBA_HANDLE_ALLOW(_pst_hmac_user) \
    ((_pst_hmac_user)->st_hmac_user_btcoex.st_hmac_btcoex_addba_req.en_ba_handle_allow)

/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/
extern oal_void hmac_btcoex_check_rx_same_baw_start_from_addba_req_etc(oal_void *p_arg,
                                                        oal_void *p_arg1,
                                                        mac_ieee80211_frame_stru *pst_frame_hdr,
                                                        oal_uint8 *puc_action);
extern oal_uint32 hmac_btcoex_check_exception_in_list_etc(oal_void *p_arg, oal_uint8 *auc_addr);
extern oal_void hmac_btcoex_blacklist_handle_init(oal_void *p_arg);


#endif /* #ifdef _PRE_WLAN_FEATURE_BTCOEX */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of __HMAC_BTCOEX_H__ */

