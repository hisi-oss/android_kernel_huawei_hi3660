

#ifndef __HMAC_PROXY_ARP_H__
#define __HMAC_PROXY_ARP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "oal_ext_if.h"
#include "mac_vap.h"
#include "hmac_vap.h"

/*****************************************************************************
  2 ??????
*****************************************************************************/
#define HMAC_PROXY_IPV4_HASHSIZE        MAC_VAP_USER_HASH_MAX_VALUE
#define HMAC_PROXY_IPV6_HASHSIZE        MAC_VAP_USER_HASH_MAX_VALUE

#define HMAC_PROXY_IPV4_HASH(n) \
        (((const oal_uint8 *)(&n))[3] % HMAC_PROXY_IPV4_HASHSIZE)

#define HMAC_PROXY_IPV6_HASH(n) \
        (((const oal_uint8 *)(n))[15] % HMAC_PROXY_IPV6_HASHSIZE)

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
typedef struct
{
    oal_dlist_head_stru     st_entry;
    oal_uint32              ul_ipv4;                        /* ??????????ipv4???? */
    oal_uint8               auc_mac[WLAN_MAC_ADDR_LEN];     /* ??????????mac???? */
    oal_uint8               auc_rsv[2];
}hmac_proxy_ipv4_hash_stru;

typedef struct
{
    oal_dlist_head_stru     st_entry;
    oal_in6_addr            st_ipv6;                        /* ??????????ipv4???? */
    oal_uint8               auc_mac[WLAN_MAC_ADDR_LEN];     /* ??????????mac???? */
    oal_uint8               auc_rsv[2];
}hmac_proxy_ipv6_hash_stru;

/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/

/*****************************************************************************
  10 ????????
*****************************************************************************/
extern oal_void hmac_proxy_arp_init(mac_vap_stru *pst_mac_vap);
extern oal_void hmac_proxy_exit(mac_vap_stru *pst_mac_vap);
extern oal_bool_enum_uint8 hmac_proxy_arp_proc(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_buf);
extern oal_err_code_enum_uint32 hmac_proxy_remove_mac(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac);
extern oal_void hmac_proxyarp_on(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_on);
extern oal_uint32 hmac_proxy_display_info(mac_vap_stru *pst_mac_vap);
//extern oal_err_code_enum_uint32 mac_proxy_init_vap(mac_vap_stru * pst_mac_vap);


#endif/* #ifdef _PRE_WLAN_FEATURE_PROXY_ARP */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



#endif


