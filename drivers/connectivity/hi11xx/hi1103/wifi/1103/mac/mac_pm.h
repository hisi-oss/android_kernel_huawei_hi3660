

#ifndef __MAC_PM_H__
#define __MAC_PM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if defined(_PRE_WLAN_FEATURE_AP_PM) || defined(_PRE_WLAN_FEATURE_STA_PM)
/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "mac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_PM_H
/*****************************************************************************
  2 ??????
*****************************************************************************/
#define MAC_PM_ARBITER_MAX_REQUESTORS   16      /*??????????????????*/
#define MAC_PM_ARBITER_MAX_REQ_NAME     16      /*??????????????????????*/
#define MAC_PWR_ARBITER_ID_INVALID      255     /* invalid arbiter id */

/*****************************************************************************
  3 ????????
*****************************************************************************/
typedef enum {
    MAC_PWR_ARBITER_TYPE_INVALID = 0,  /*????????*/
    MAC_PWR_ARBITER_TYPE_AP,           /*AP????*/
    MAC_PWR_ARBITER_TYPE_STA,          /*STA????*/
    MAC_PWR_ARBITER_TYPE_P2P,          /*P2P????*/

    MAC_PWR_ARBITER_TYPE_BUTT
} mac_pm_arbiter_type_enum;

/*device????????????VAP????????????device????????????????????????AP????vap??sta????VAP
P2P????vap??????????????????????????????????????device??????*/
typedef enum {
    DEV_PWR_STATE_WORK = 0,         /*????????*/
    DEV_PWR_STATE_DEEP_SLEEP,      /*????????*/
    DEV_PWR_STATE_WOW,             /*WOW????*/
    DEV_PWR_STATE_IDLE,            /*idle????????????????*/
    DEV_PWR_STATE_OFF,             /*????????*/

    DEV_PWR_STATE_BUTT             /*????????*/
} device_pwr_state_enum;

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
typedef struct _mac_pwr_event_info{
    oal_uint32           ul_event_id;           /*event??????,????????????????*/
    const oal_int8      *auc_event_name;         /*event????*/
}mac_pwr_event_info;

struct mac_pm_arbiter_requestor_info {
    oal_uint8                   auc_id_name[MAC_PM_ARBITER_MAX_REQ_NAME]; /* names of the requestors */
    mac_pm_arbiter_type_enum    en_arbiter_type;
} ;

typedef struct _mac_pm_arbiter_state_info{
    oal_uint32               ul_state;               /*state??????,????????????????*/
    const oal_int8          *auc_state_name;         /*state????*/
}mac_pm_arbiter_state_info;

typedef struct _mac_pm_arbiter_info {
    oal_uint32   ul_id_bitmap;                          /*??????requestor id bitmaps */
    oal_uint32   ul_state_bitmap[DEV_PWR_STATE_BUTT];   /*????????????????bitmap*/
    oal_uint8    uc_cur_state;                          /*????device????????????*/
    oal_uint8    uc_prev_state;                         /*????device????????????*/
    oal_uint8    uc_requestor_num;                      /*????????????????????*/
    oal_uint8    uc_rsv;
    mac_pm_arbiter_state_info   *pst_state_info;
    struct mac_pm_arbiter_requestor_info requestor[MAC_PM_ARBITER_MAX_REQUESTORS];  /*????????????????????*/
}mac_pm_arbiter_stru;


/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/
extern oal_uint32 mac_pm_arbiter_init(mac_device_stru* pst_device);
extern oal_uint32 mac_pm_arbiter_destroy(mac_device_stru* pst_device);
extern oal_uint32 mac_pm_arbiter_alloc_id(mac_device_stru* pst_device, oal_uint8* pst_name,mac_pm_arbiter_type_enum en_arbiter_type);
extern oal_uint32 mac_pm_arbiter_free_id(mac_device_stru* pst_device, oal_uint32 ul_arbiter_id);
extern oal_void mac_pm_arbiter_to_state(mac_device_stru *pst_device, mac_vap_stru *pst_mac_vap, oal_uint32 ul_arbiter_id,
                                            oal_uint8  uc_state_from, oal_uint8  uc_state_to);
extern oal_uint32 mac_pm_set_hal_state(mac_device_stru *pst_device,mac_vap_stru *pst_mac_vap,oal_uint8 uc_state_to);


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_fsm.h */
