
#ifndef __DMAC_WITP_SCAN_H__
#define __DMAC_WITP_SCAN_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "wlan_spec.h"
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "hal_ext_if.h"
#include "mac_device.h"
#include "mac_vap.h"
#include "dmac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_SCAN_H

/*****************************************************************************
  2 ??????
*****************************************************************************/
#define DMAC_SCAN_CHANNEL_STATICS_PERIOD_US     (10 * 1000)    /* ????1???????????????? 15ms */
#define DMAC_SCAN_CHANNEL_MEAS_PERIOD_MS        10
#define DMAC_SCAN_CTS_MAX_DURATION              32767
#define DMAC_SCAN_MAX_TIMER                     60*1000     /*??????????timer????*/
#define DMAC_SCAN_CHANNEL_DWELL_TIME_MARGIN     2           /* ms */
#define DMAC_SCAN_P2PGO_SEND_BEACON_TIME        10          /* ms, go tbtt?????????????????? */
#define DMAC_SCAN_DBAC_SCAN_DELTA_TIME          1500        /* ms */
#define DMAC_SCAN_GO_MAX_SCAN_TIME              300         /* ms */


/*****************************************************************************
  3 ????????
*****************************************************************************/


/*****************************************************************************
  4 ????????????
****************************************************************************/
extern frw_timeout_stru g_csa_stop_timer;
extern oal_uint8 g_csa_scan_flag;
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
  9 ????????????
*****************************************************************************/

/*****************************************************************************
  10 ????????
*****************************************************************************/
extern oal_uint32 dmac_trigger_csa_scan(mac_scan_req_stru  *pst_scan_params,
                                           mac_vap_stru      *pst_mac_vap,
                                           mac_channel_stru  *pst_old_channel);
extern oal_void dmac_scan_start_obss_timer(mac_vap_stru *pst_mac_vap);
extern oal_uint32  dmac_scan_proc_scan_complete_event(dmac_vap_stru *pst_dmac_vap,
                                                      mac_scan_status_enum_uint8 en_scan_rsp_status);
extern oal_uint32  dmac_scan_mgmt_filter(dmac_vap_stru *pst_dmac_vap, oal_void *p_param, oal_bool_enum_uint8 *pen_report_bss, oal_uint8 *pen_go_on);
extern oal_uint32  dmac_scan_proc_sched_scan_req_event(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_scan_handle_scan_req_entry(mac_device_stru    *pst_mac_device,
                                                                 dmac_vap_stru      *pst_dmac_vap,
                                                                 mac_scan_req_stru  *pst_scan_req_params);
extern oal_uint32  dmac_scan_proc_scan_req_event(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_scan_process_scan_req_event(frw_event_mem_stru *pst_event_mem);
extern oal_void   dmac_scan_switch_channel_off(mac_device_stru *pst_mac_device);
extern oal_void  dmac_scan_switch_channel_back(mac_device_stru *pst_mac_device);
extern oal_uint32  dmac_switch_channel_off(
                mac_device_stru     *pst_mac_device,
                mac_vap_stru        *pst_mac_vap,
                mac_channel_stru    *pst_dst_chl,
                oal_uint16           us_protect_time);
extern oal_uint32  dmac_switch_same_channel_off(
                mac_device_stru     *pst_mac_device,
                mac_vap_stru        *pst_mac_vap,
                oal_uint16           us_protect_time);
extern oal_uint32  dmac_switch_channel_off_enhanced_self_channel(
                mac_device_stru     *pst_mac_device,
                mac_vap_stru        *pst_mac_vap1,
                mac_vap_stru        *pst_mac_vap2,
                oal_uint16           us_protect_time);

extern oal_void dmac_scan_begin(mac_device_stru *pst_mac_device);
extern oal_void dmac_scan_end(mac_device_stru *pst_mac_device);
extern oal_void  dmac_scan_abort(mac_device_stru *pst_mac_device);
extern oal_uint32  dmac_scan_after_p2pgo_send_noa(void *p_arg);
extern oal_void  dmac_scan_switch_home_channel_work(mac_device_stru *pst_mac_device);
extern oal_uint32 dmac_sta_csa_stop_timeout_fn(void *arg);

/* ???????????????? */
extern oal_uint32 dmac_scan_channel_statistics_complete(frw_event_mem_stru *pst_event_mem);
extern oal_void dmac_scan_radar_detected(mac_device_stru *pst_mac_device, hal_radar_det_event_stru *pst_radar_det_info);

/* ???????????????? */
extern oal_uint32 dmac_scan_init(mac_device_stru *pst_mac_device);
extern oal_uint32 dmac_scan_exit(mac_device_stru *pst_mac_device);

/* ???????????? */
extern oal_uint32  dmac_scan_send_probe_req_frame(dmac_vap_stru *pst_dmac_vap,
                                            oal_uint8 *puc_bssid,
                                            oal_int8 *pc_ssid);
extern oal_uint32  dmac_mgmt_switch_channel(mac_device_stru *pst_mac_device, mac_channel_stru *pst_channel, oal_uint8 en_clear_fifo);


/* ?????????? */
extern oal_uint32  dmac_scan_stop_pno_sched_scan_timer(void *p_arg);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_scan.h */
