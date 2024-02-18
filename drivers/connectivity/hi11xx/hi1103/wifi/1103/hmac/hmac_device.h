

#ifndef __HMAC_DEVICE_H__
#define __HMAC_DEVICE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "wlan_spec.h"
#include "hal_ext_if.h"
#include "dmac_ext_if.h"
#include "mac_vap.h"
#include "hmac_vap.h"
#ifdef _PRE_WLAN_TCP_OPT
#include "hmac_tcp_opt_struc.h"
#include "oal_hcc_host_if.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_DEVICE_H
/*****************************************************************************
  2 ??????
*****************************************************************************/
#ifdef _PRE_WLAN_TCP_OPT
#define HCC_TRANS_THREAD_POLICY    SCHED_FIFO
#define HCC_TRANS_THERAD_PRIORITY       (10)
#define HCC_TRANS_THERAD_NICE           (-10)
#endif

#define IS_EQUAL_RATES(rate1, rate2)    (((rate1) & 0x7f) == ((rate2) & 0x7f))

typedef enum
{
    HMAC_ACS_TYPE_INIT  = 0,         /* ???????????????? */
    HMAC_ACS_TYPE_CMD   = 1,         /* ?????????????????????? */
    HMAC_ACS_TYPE_FREE  = 2,         /* ?????????????????? */
}hmac_acs_type_enum;
typedef oal_uint8 hmac_acs_type_enum_uint8;
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

/* ????????????????bss???? */
typedef struct
{
    oal_dlist_head_stru    st_dlist_head;	    /* ???????? */
    //oal_spin_lock_stru     st_lock;             /* ?? */
    mac_bss_dscr_stru      st_bss_dscr_info;	/* bss?????????????????????????? */
}hmac_scanned_bss_info;

/* ??????hmac device???????????????????????? */
typedef struct
{
    oal_spin_lock_stru  st_lock;
    oal_dlist_head_stru st_bss_list_head;
    oal_uint32          ul_bss_num;
}hmac_bss_mgmt_stru;

/* ACS???????? */
typedef struct
{
    mac_scan_op_enum_uint8  en_scan_op;
    oal_bool_enum_uint8     en_switch_chan;
    oal_uint8               uc_acs_type;
    oal_uint8               auc_rsv[1];
}hmac_acs_cfg_stru;

/* ???????????????? */
typedef struct
{
    hmac_bss_mgmt_stru           st_bss_mgmt;                              /* ????????BSS?????????????? */
    wlan_scan_chan_stats_stru     ast_chan_results[WLAN_MAX_CHANNEL_NUM];   /* ????????/???????? */
    oal_uint8                    uc_chan_numbers;                          /* ?????????????????????????????? */
    oal_uint8                    uc_device_id : 4;
    oal_uint8                    uc_chip_id   : 4;
    oal_uint8                    uc_vap_id;                                /* ??????????????vap id */
    mac_scan_status_enum_uint8   en_scan_rsp_status;                       /* ?????????????????????????????????????????? */

    oal_time_us_stru             st_scan_start_timestamp;                  /* ???????????? */
    mac_scan_cb_fn               p_fn_cb;                                  /* ?????????????????????????? */

    oal_uint64                   ull_cookie;                               /* ????P2P ??????????????cookie ?? */
    mac_vap_state_enum_uint8     en_vap_last_state;                        /* ????VAP????????????????,AP/P2P GO??????20/40M???????? */
    oal_time_t_stru              st_scan_start_time;                       /* ?????????????? */
}hmac_scan_record_stru;


/* ???????????????????? */
typedef struct
{
    /* scan ???????????? */
    oal_bool_enum_uint8                    en_is_scanning;               /* host???????????????????????? */
    oal_bool_enum_uint8                    en_is_random_mac_addr_scan;   /* ??????????mac addr??????????????(??????????????????) */
    oal_bool_enum_uint8                    en_complete;                   /* ???????????????????????????? */
    oal_bool_enum_uint8                    en_sched_scan_complete;        /* ???????????????????????? */

    oal_cfg80211_scan_request_stru        *pst_request;               /* ???????????????????????? */
    oal_cfg80211_sched_scan_request_stru  *pst_sched_scan_req;        /* ???????????????????????????? */

    oal_wait_queue_head_stru               st_wait_queue;
    oal_spin_lock_stru                     st_scan_request_spinlock;            /* ??????????request?????? */

    frw_timeout_stru                       st_scan_timeout;            /* ????????host?????????????????????????? */
#if defined(_PRE_SUPPORT_ACS) || defined(_PRE_WLAN_FEATURE_DFS) || defined(_PRE_WLAN_FEATURE_20_40_80_COEXIST)
    frw_timeout_stru                       st_init_scan_timeout;
#endif
    oal_uint8                              auc_random_mac[WLAN_MAC_ADDR_LEN]; /* ????????????????MAC */
    oal_uint8                              auc_resv[2];

    hmac_scan_record_stru                  st_scan_record_mgmt;        /* ???????????????????????????????????????????????????????? */
}hmac_scan_stru;

typedef struct
{

    frw_timeout_stru    st_rx_dscr_opt_timer;     /* rx_dscr?????????? */
    oal_uint32          ul_rx_pkt_num;
    oal_uint32          ul_rx_pkt_opt_limit;
    oal_uint32          ul_rx_pkt_reset_limit;
    oal_bool_enum_uint8 en_dscr_opt_state;        /* TRUE?????????? */
    oal_bool_enum_uint8 en_dscr_opt_enable;
}hmac_rx_dscr_opt_stru;

/* hmac device????????????????????hmac??device???????? */
typedef struct
{
    hmac_scan_stru                      st_scan_mgmt;                           /* ?????????????? */
#if  defined(_PRE_WIFI_DMT ) || (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)
    oal_uint8                           uc_desired_bss_num;                         /* ??????????????bss???? */
    oal_uint8                           auc_resv[3];
    oal_uint8                           auc_desired_bss_idx[WLAN_MAX_SCAN_BSS_NUM]; /* ??????????bss??bss list???????? */
#endif
    oal_uint32                          ul_p2p_intf_status;
    oal_wait_queue_head_stru            st_netif_change_event;
    mac_device_stru                    *pst_device_base_info;                   /* ????????????mac device */
#if defined(_PRE_SUPPORT_ACS) || defined(_PRE_WLAN_FEATURE_DFS) || defined(_PRE_WLAN_FEATURE_20_40_80_COEXIST)
    oal_bool_enum_uint8                 en_init_scan      : 1;
    oal_bool_enum_uint8                 en_rfu            : 1;
    oal_bool_enum_uint8                 en_in_init_scan   : 1;
    oal_bool_enum_uint8                 en_rescan_idle    : 1;
	oal_uint8                           uc_resv_bit		  : 4;
    oal_uint8                           auc_resvx[3];
    mac_channel_stru                    ast_best_channel[WLAN_BAND_BUTT];
#endif

#if defined(_PRE_SUPPORT_ACS)
    frw_timeout_stru                    st_rescan_timer;
    oal_uint32                          ul_rescan_timeout;  // ms
#endif

#ifdef _PRE_WLAN_FEATURE_CAR
    frw_timeout_stru                    st_car_timer;           /* ?????????????? */
    oal_uint16                          us_car_ctl_cycle_ms;    /* ??????????????????, 100ms*/
    oal_bool_enum_uint8                 en_car_enable_flag;     /* car???????? */
    oal_uint8                           auc_resv_car[1];
    hmac_car_limit_stru                 st_car_device_cfg[HMAC_CAR_BUTT];   /* device??????????,0-???? 1-???? */
    hmac_car_limit_stru                 st_car_device_multicast_cfg;
    oal_uint32                          ul_car_packet_drop_num[HMAC_CAR_BUTT];
    oal_uint32                          ul_car_multicast_packet_drop_num;
    oal_uint32                          ul_car_multicast_packet_pps_drop_num;
#endif


#ifdef _PRE_WLAN_TCP_OPT
    oal_bool_enum_uint8        sys_tcp_rx_ack_opt_enable;
    oal_bool_enum_uint8        sys_tcp_tx_ack_opt_enable;
    oal_bool_enum_uint8        en_start_via_priv : 1;
    oal_uint8                  uc_rfu_bit		 : 7;
    oal_uint8                  uc_rfu;
#else
    oal_bool_enum_uint8        en_start_via_priv : 1;
    oal_uint8                  uc_rfu_bit		 : 7;
    oal_uint8                  auc_rfu[3];
#endif

    hmac_rx_dscr_opt_stru      st_rx_dscr_opt;
#if ((_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE) && (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION))
#ifdef CONFIG_HAS_EARLYSUSPEND
        struct early_suspend            early_suspend;      //early_suspend????
#endif
        oal_spin_lock_stru              st_suspend_lock;
#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    hmac_device_btcoex_stru     st_hmac_device_btcoex;
#endif

#ifdef _PRE_WLAN_FEATURE_M2S
        hmac_device_m2s_stru    st_hmac_device_m2s;
#endif

    frw_timeout_stru                    st_scan_timer;                          /* host?????????????????????? */
#ifdef _PRE_WLAN_FEATURE_SINGLE_PROXYSTA
    frw_timeout_stru                    st_proxysta_map_timer;                  /* ????????????????proxysta ip-mac map???? */
#endif
}hmac_device_stru;

/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/
extern oal_uint32  hmac_board_exit_etc(mac_board_stru *pst_board);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32 hmac_config_host_dev_init_etc(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_host_dev_exit_etc(mac_vap_stru *pst_mac_vap);
extern oal_uint32  hmac_board_init_etc(mac_board_stru *pst_board);
#else
extern oal_uint32  hmac_board_init_etc(oal_uint32 ul_chip_max_num);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of mac_device.h */
