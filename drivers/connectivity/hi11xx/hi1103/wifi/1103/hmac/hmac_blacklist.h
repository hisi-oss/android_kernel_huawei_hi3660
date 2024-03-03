

#ifndef __HMAC_BLAKLIST_H__
#define __HMAC_BLAKLIST_H__

#if (_PRE_WLAN_FEATURE_BLACKLIST_LEVEL != _PRE_WLAN_FEATURE_BLACKLIST_NONE)

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "oal_ext_if.h"
#include "mac_vap.h"
#include "hmac_vap.h"

/*****************************************************************************
  2 ??????
*****************************************************************************/
#define CS_INVALID_AGING_TIME         0
#define CS_DEFAULT_AGING_TIME         3600
#define CS_DEFAULT_RESET_TIME         3600
#define CS_DEFAULT_THRESHOLD          100



/*****************************************************************************
  3 ????????
*****************************************************************************/

/* ?????????? */
typedef enum
{
    CS_BLACKLIST_TYPE_ADD,           /* ????       */
    CS_BLACKLIST_TYPE_DEL,           /* ????       */

    CS_BLACKLIST_TYPE_BUTT
}cs_blacklist_type_enum;
typedef oal_uint8 cs_blacklist_type_enum_uint8;




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
/* ?????????????????? */
typedef struct
{
    oal_uint8                       uc_enabled;               /* ???????? 0:??????  1:???? */
    oal_uint8                       auc_reserved[3];          /* ????????                  */
    oal_uint32                      ul_threshold;             /* ????                      */
    oal_uint32                      ul_reset_time;            /* ????????                  */
    oal_uint32                      ul_aging_time;            /* ????????                  */
} hmac_autoblacklist_cfg_stru;

/* ???????????? */
typedef struct
{
    oal_uint8                       uc_type;                  /* ????????    */
    oal_uint8                       uc_mode;                  /* ????????    */
    oal_uint8                       auc_sa[6];                /* mac????     */
} hmac_blacklist_cfg_stru;

/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/
extern oal_uint32 hmac_autoblacklist_enable_etc(mac_vap_stru *pst_mac_vap, oal_uint8 uc_enabled);
extern oal_uint32 hmac_autoblacklist_set_aging_etc(mac_vap_stru *pst_mac_vap, oal_uint32 ul_aging_time);
extern oal_uint32 hmac_autoblacklist_set_threshold_etc(mac_vap_stru *pst_mac_vap, oal_uint32 ul_threshold);
extern oal_uint32 hmac_autoblacklist_set_reset_time_etc(mac_vap_stru *pst_mac_vap, oal_uint32 ul_reset_time);
extern oal_void hmac_autoblacklist_filter_etc(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr);
extern oal_uint32 hmac_blacklist_set_mode_etc(mac_vap_stru *pst_mac_vap, oal_uint8 uc_mode);
extern oal_uint32 hmac_blacklist_get_mode(mac_vap_stru *pst_mac_vap, oal_uint8 *uc_mode);
extern oal_uint32 hmac_blacklist_add_etc(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr, oal_uint32 ul_aging_time);
extern oal_uint32 hmac_blacklist_add_only_etc(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr, oal_uint32 ul_aging_time);
extern oal_uint32 hmac_blacklist_del_etc(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr);
extern oal_bool_enum_uint8 hmac_blacklist_filter_etc(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr);
extern oal_void hmac_show_blacklist_info_etc(mac_vap_stru *pst_mac_vap);
extern oal_uint32 hmac_backlist_get_drop_etc(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr);
extern oal_uint8 hmac_backlist_get_list_num_etc(mac_vap_stru *pst_mac_vap);
extern oal_bool_enum_uint8 hmac_blacklist_get_assoc_ap(mac_vap_stru *pst_cur_vap, oal_uint8 *puc_mac_addr, mac_vap_stru **pst_assoc_vap);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif  /* #if (_PRE_WLAN_FEATURE_BLACKLIST_LEVEL != _PRE_WLAN_FEATURE_BLACKLIST_NONE) */

#endif /* end of hmac_blacklist.h */

