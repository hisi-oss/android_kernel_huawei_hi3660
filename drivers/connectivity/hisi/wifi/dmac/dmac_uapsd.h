

#ifndef __DMAC_UAPSD_H__
#define __DMAC_UAPSD_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_UAPSD

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "oal_ext_if.h"
#include "dmac_vap.h"
#include "dmac_user.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_UAPSD_H
/*****************************************************************************
  2 ??????
*****************************************************************************/
#define DMAC_UAPSD_NOT_SEND_FRAME   -1
#define DMAC_UAPSD_QDEPTH_DEFAULT   32
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
extern oal_uint32 dmac_uapsd_user_init(dmac_user_stru *pst_dmac_usr);
extern oal_void dmac_uapsd_user_destroy(dmac_user_stru *pst_dmac_usr);
extern oal_uint32 dmac_uapsd_tx_enqueue(dmac_vap_stru *pst_dmac_vap,dmac_user_stru *pst_dmac_user,oal_netbuf_stru *pst_net_buf);
extern oal_void dmac_uapsd_rx_trigger_check (dmac_vap_stru *pst_dmac_vap,dmac_user_stru *pst_dmac_user,oal_netbuf_stru *pst_net_buf);
extern oal_void dmac_uapsd_tx_complete(dmac_user_stru *pst_dmac_user,mac_tx_ctl_stru *pst_cb);
extern oal_uint32 dmac_config_set_uapsden(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_uint32 dmac_config_set_uapsd_update(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_uint32  dmac_config_uapsd_debug(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);

extern oal_int32 dmac_uapsd_process_queue (dmac_vap_stru* pst_dmac_vap,dmac_user_stru *pst_dmac_user,oal_uint8 uc_ac);
extern oal_uint32 dmac_uapsd_send_qosnull(dmac_vap_stru *pst_dmac_vap,dmac_user_stru *pst_dmac_user,oal_uint8 uc_ac);
extern oal_void dmac_uapsd_process_trigger (dmac_vap_stru *pst_dmac_vap,dmac_user_stru *pst_dmac_user,oal_uint8 uc_ac,oal_netbuf_stru *pst_net_buf);
extern oal_int32 dmac_uapsd_flush_queue (dmac_vap_stru* pst_dmac_vap, dmac_user_stru *pst_dmac_user);


#endif /* _PRE_WLAN_FEATURE_UAPSD */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_uapsd.h */
