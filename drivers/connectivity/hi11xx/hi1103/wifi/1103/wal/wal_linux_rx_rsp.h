

#ifndef __WAL_LINUX_RX_RSP_H__
#define __WAL_LINUX_RX_RSP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "oal_ext_if.h"
#include "oal_types.h"
#include "wal_ext_if.h"
#include "frw_ext_if.h"
#include "hmac_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_LINUX_RX_RSP_H
/*****************************************************************************
  2 ??????
*****************************************************************************/


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
/* ????sta?????????????????? */
typedef struct
{
    oal_int32               l_signal;      /* ???????? */

    oal_int16               s_freq;        /* bss?????????????????? */
    oal_uint8               auc_arry[2];

    oal_uint32                ul_mgmt_len;   /* ?????????? */
    oal_ieee80211_mgmt_stru  *pst_mgmt;      /* ?????????????? */

}wal_scanned_bss_info_stru;

/* ????sta?????????????????? */
typedef struct
{
    oal_uint8       auc_bssid[WLAN_MAC_ADDR_LEN];  /* sta??????ap mac???? */
    oal_uint16      us_status_code;                /* ieee??????????16???????? */

    oal_uint8       *puc_rsp_ie;                 /* asoc_req_ie  */
    oal_uint8       *puc_req_ie;

    oal_uint32      ul_req_ie_len;               /* asoc_req_ie len */
    oal_uint32      ul_rsp_ie_len;

    oal_uint16      us_connect_status;
    oal_uint8       auc_resv[2];

}oal_connet_result_stru;

/* ????sta???????????????????? */
typedef struct
{
    oal_uint16  us_reason_code;         /* ?????? reason code */
    oal_uint8   auc_resv[2];

    oal_uint8  *pus_disconn_ie;        /* ???????????? ie */
    oal_uint32  us_disconn_ie_len;      /* ???????????? ie ???? */
}oal_disconnect_result_stru;


/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/
extern oal_uint32  wal_scan_comp_proc_sta_etc(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  wal_asoc_comp_proc_sta_etc(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  wal_disasoc_comp_proc_sta_etc(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  wal_connect_new_sta_proc_ap_etc(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  wal_disconnect_sta_proc_ap_etc(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  wal_mic_failure_proc_etc(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  wal_send_mgmt_to_host_etc(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  wal_p2p_listen_timeout_etc(frw_event_mem_stru *pst_event_mem);

#ifdef _PRE_WLAN_FEATURE_HILINK_TEMP_PROTECT

extern oal_void wal_init_all_sta_rssi_info(oal_void);
extern oal_uint32 wal_get_rssi_by_mac_addr(oal_net_device_stru *pst_dev, oal_uint8 *puc_mac_addr, oal_uint32 *pul_rssi);
extern oal_uint32 wal_receive_all_sta_rssi_proc(frw_event_mem_stru *pst_event_mem);

#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of wal_linux_rx_rsp.h */
