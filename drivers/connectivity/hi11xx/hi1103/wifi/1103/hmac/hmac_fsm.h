

#ifndef __HMAC_FSM_H__
#define __HMAC_FSM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "oal_ext_if.h"
#include "hmac_main.h"
#include "hmac_vap.h"
#include "hmac_rx_filter.h"
#include "hmac_config.h"

#if defined (WIN32) && (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_HOST)
#include "plat_pm_wlan.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_FSM_H
/*****************************************************************************
  2 ??????
*****************************************************************************/
typedef oal_uint32  (*hmac_fsm_func)(hmac_vap_stru *pst_hmac_vap, oal_void *p_param);

extern oal_uint32  hmac_config_sta_update_rates_etc(mac_vap_stru *pst_mac_vap, mac_cfg_mode_param_stru *pst_cfg_mode, mac_bss_dscr_stru *pst_bss_dscr);

/*****************************************************************************
  3 ????????
*****************************************************************************/
/* ?????????????????? */
typedef enum
{
    /* AP STA?????????????? */
    HMAC_FSM_INPUT_RX_MGMT,
    HMAC_FSM_INPUT_RX_DATA,
    HMAC_FSM_INPUT_TX_DATA,
    HMAC_FSM_INPUT_TIMER0_OUT,
    HMAC_FSM_INPUT_MISC,        /* TBTT ???? ?????????????? */

    /* AP ?????????????? */
    HMAC_FSM_INPUT_START_REQ,

    /* STA?????????????? */
    HMAC_FSM_INPUT_SCAN_REQ,
    HMAC_FSM_INPUT_JOIN_REQ,
    HMAC_FSM_INPUT_AUTH_REQ,
    HMAC_FSM_INPUT_ASOC_REQ,

    HMAC_FSM_INPUT_LISTEN_REQ,  /*  ???????? */
    HMAC_FSM_INPUT_LISTEN_TIMEOUT,
    HMAC_FSM_INPUT_SCHED_SCAN_REQ,      /* PNO???????????? */

#ifdef _PRE_WLAN_FEATURE_ROAM
    HMAC_FSM_INPUT_ROAMING_START,
    HMAC_FSM_INPUT_ROAMING_STOP,
#endif //_PRE_WLAN_FEATURE_ROAM

    HMAC_FSM_INPUT_TYPE_BUTT
}hmac_fsm_input_type_enum;
typedef oal_uint8 hmac_fsm_input_type_enum_uint8;

#define HMAC_FSM_AP_INPUT_TYPE_BUTT     (HMAC_FSM_INPUT_MISC + 1)
#define HMAC_FSM_STA_INPUT_TYPE_BUTT    HMAC_FSM_INPUT_TYPE_BUTT
#define HMAC_SWITCH_STA_PSM_PERIOD      120000                  //staut????????????????????????1101 120s
#define HMAC_SWITCH_STA_PSM_MAX_CNT     (HMAC_SWITCH_STA_PSM_PERIOD / WLAN_SLEEP_TIMER_PERIOD)

/* MISC???????????????????? */
typedef enum
{
    HMAC_MISC_TBTT,
    HMAC_MISC_ERROR,
    HMAC_MISC_RADAR,

    HMAC_MISC_BUTT
}hmac_misc_input_enum;
typedef oal_uint8 hmac_misc_input_enum_uint8;

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
/* MISC???????????????????????? */
typedef struct
{
    hmac_misc_input_enum_uint8  en_type;
    oal_uint8                   auc_resv[3];
    oal_void                   *p_data;
}hmac_misc_input_stru;


/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/
extern oal_void  hmac_fsm_init_etc(oal_void);
extern oal_uint32  hmac_fsm_call_func_ap_etc(hmac_vap_stru *pst_hmac_vap, hmac_fsm_input_type_enum_uint8 en_input, oal_void *p_param);
extern oal_uint32  hmac_fsm_call_func_sta_etc(hmac_vap_stru *pst_hmac_vap, hmac_fsm_input_type_enum_uint8 en_input, oal_void *p_param);
extern oal_void  hmac_fsm_change_state_etc(hmac_vap_stru *pst_hmac_vap, mac_vap_state_enum_uint8 en_vap_state);
extern oal_void  hmac_fsm_change_state_check_etc(hmac_vap_stru *pst_hmac_vap, mac_vap_state_enum_uint8 en_comp_vap_state, mac_vap_state_enum_uint8 en_new_vap_state);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_fsm.h */
