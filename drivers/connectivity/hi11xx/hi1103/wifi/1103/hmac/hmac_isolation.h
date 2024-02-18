

#ifndef __HMAC_ISOLATION_H__
#define __HMAC_ISOLATION_H__

#ifdef _PRE_WLAN_FEATURE_ISOLATION

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

/*****************************************************************************
  2 ??????
*****************************************************************************/

/*****************************************************************************
  3 ????????
*****************************************************************************/

/* ???????? mode*/
typedef enum
{
    CS_ISOLATION_MODE_BROADCAST=0x01,        /* ????     */
    CS_ISOLATION_MODE_MULTICAST=0x02,        /* ????     */
    CS_ISOLATION_MODE_UNICAST=0x04,          /* ????     */
}cs_isolation_mode_enum;

/* ???????? */
typedef enum
{
    CS_ISOLATION_TYPE_NONE,             /* ????????        */
    CS_ISOLATION_TYPE_MULTI_BSS,        /* ??BSS????       */
    CS_ISOLATION_TYPE_SINGLE_BSS,       /* ??BSS????       */

    CS_ISOLATION_TYPE_BUTT
}cs_isolation_type_enum;
typedef oal_uint8 cs_isolation_type_enum_uint8;

/* ????forwording???? */
typedef enum
{
    CS_ISOLATION_FORWORD_NONE,         /* ????forword????????       */
    CS_ISOLATION_FORWORD_TOLAN,        /* ????forword????????lan  */
    CS_ISOLATION_FORWORD_DROP,         /* ????forword??????       */

    CS_ISOLATION_FORWORD_BUTT
}cs_isolation_forward_enum;
typedef oal_uint8 cs_isolation_forward_enum_uint8;

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
extern oal_uint32 hmac_isolation_set_mode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_mode);
extern oal_uint32 hmac_isolation_set_type(mac_vap_stru *pst_mac_vap, oal_uint8 uc_bss_type, oal_uint8 uc_isolation_type);
extern oal_uint32 hmac_isolation_set_forward(mac_vap_stru *pst_mac_vap, oal_uint8 uc_forward);
extern cs_isolation_forward_enum hmac_isolation_filter(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr);

extern oal_uint32 hmac_isolation_clear_counter(mac_vap_stru *pst_mac_vap);
extern oal_void hmac_show_isolation_info(mac_vap_stru *pst_mac_vap);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif  /* #ifdef _PRE_WLAN_FEATURE_ISOLATION */

#endif /* end of hmac_isolation.h */

