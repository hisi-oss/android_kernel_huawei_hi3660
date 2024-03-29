

#ifndef __HMAC_ROAM_CONNECT_H__
#define __HMAC_ROAM_CONNECT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_ROAM

/*****************************************************************************
  1 ??????????????
*****************************************************************************/


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_ROAM_CONNECT_H
/*****************************************************************************
  2 ??????
*****************************************************************************/
#define ROAM_JOIN_TIME_MAX        (1 * 1000)       /* JOIN???????? ????ms*/
#define ROAM_AUTH_TIME_MAX        (300)            /* AUTH???????? ????ms*/
#define ROAM_ASSOC_TIME_MAX       (300)            /* ASSOC???????? ????ms*/
#define ROAM_HANDSHAKE_TIME_MAX   (7 * 1000)       /* ???????????? ????ms*/

#define ROAM_MAC_ADDR(_puc_mac)   ((oal_uint32)(((oal_uint32)_puc_mac[2] << 24) |\
                                              ((oal_uint32)_puc_mac[3] << 16) |\
                                              ((oal_uint32)_puc_mac[4] << 8) |\
                                              ((oal_uint32)_puc_mac[5])))

/*****************************************************************************
  3 ????????
*****************************************************************************/
/* ????connect?????????? */
typedef enum
{
    ROAM_CONNECT_STATE_INIT               = 0,
    ROAM_CONNECT_STATE_FAIL               = ROAM_CONNECT_STATE_INIT,
    ROAM_CONNECT_STATE_WAIT_JOIN          = 1,
    ROAM_CONNECT_STATE_WAIT_FT_COMP       = 2,
    ROAM_CONNECT_STATE_WAIT_AUTH_COMP     = 3,
    ROAM_CONNECT_STATE_WAIT_ASSOC_COMP    = 4,
    ROAM_CONNECT_STATE_HANDSHAKING        = 5,
    ROAM_CONNECT_STATE_UP                 = 6,

    ROAM_CONNECT_STATE_BUTT
}roam_connect_state_enum;
typedef oal_uint8  roam_connect_state_enum_uint8;

/* ????connect?????????????? */
typedef enum
{
    ROAM_CONNECT_FSM_EVENT_START          = 0,
    ROAM_CONNECT_FSM_EVENT_MGMT_RX        = 1,
    ROAM_CONNECT_FSM_EVENT_KEY_DONE       = 2,
    ROAM_CONNECT_FSM_EVENT_TIMEOUT        = 3,
    ROAM_CONNECT_FSM_EVENT_FT_OVER_DS     = 4,
    ROAM_CONNECT_FSM_EVENT_TYPE_BUTT
}roam_connect_fsm_event_type_enum;

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
oal_uint32 hmac_roam_connect_set_join_reg_etc(mac_vap_stru *pst_mac_vap, hmac_user_stru *pst_hmac_user);
oal_uint32 hmac_roam_connect_set_dtim_param_etc(mac_vap_stru *pst_mac_vap, oal_uint8 uc_dtim_cnt, oal_uint8 uc_dtim_period);
oal_uint32 hmac_roam_connect_timeout_etc(oal_void *p_arg);
oal_uint32 hmac_roam_connect_start_etc(hmac_vap_stru *pst_hmac_vap, mac_bss_dscr_stru *pst_bss_dscr);
oal_uint32 hmac_roam_connect_stop_etc(hmac_vap_stru *pst_hmac_vap);
oal_void hmac_roam_connect_rx_mgmt_etc(hmac_vap_stru *pst_hmac_vap, dmac_wlan_crx_event_stru *pst_crx_event);
oal_void hmac_roam_connect_fsm_init_etc(oal_void);
oal_void hmac_roam_connect_key_done_etc(hmac_vap_stru *pst_hmac_vap);
#ifdef _PRE_WLAN_FEATURE_11R
oal_uint32 hmac_roam_connect_ft_reassoc_etc(hmac_vap_stru *pst_hmac_vap);
#endif //_PRE_WLAN_FEATURE_11R

#endif //_PRE_WLAN_FEATURE_ROAM

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_roam_connect.h */
