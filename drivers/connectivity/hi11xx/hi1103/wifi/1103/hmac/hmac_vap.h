

#ifndef __HMAC_VAP_H__
#define __HMAC_VAP_H__

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
#include "hmac_ext_if.h"
#include "hmac_user.h"
#include "hmac_main.h"
#include "mac_resource.h"
#ifdef _PRE_WLAN_TCP_OPT
#include "hmac_tcp_opt_struc.h"
#include "oal_hcc_host_if.h"
#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "hmac_btcoex.h"
#endif
#ifdef _PRE_WLAN_FEATURE_M2S
#include "hmac_m2s.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_VAP_H

/*****************************************************************************
  2 ??????
*****************************************************************************/
#ifdef _PRE_WLAN_DFT_STAT
#define   HMAC_VAP_DFT_STATS_PKT_INCR(_member, _cnt)        ((_member) += (_cnt))
#else
#define   HMAC_VAP_DFT_STATS_PKT_INCR(_member, _cnt)
#endif
#define   HMAC_VAP_STATS_PKT_INCR(_member, _cnt)            ((_member) += (_cnt))

#ifdef _PRE_WLAN_FEATURE_HS20
#define MAX_QOS_UP_RANGE  8
#define MAX_DSCP_EXCEPT   21  /* maximum of DSCP Exception fields for QoS Map set */
#endif

#ifdef _PRE_WLAN_FEATURE_EQUIPMENT_TEST
#define  HMAC_HIPRIV_ACK_BUF_SIZE  3
#endif

#ifdef _PRE_WLAN_FEATURE_SINGLE_PROXYSTA
#define MAC_VAP_PROXYSTA_MAP_MAX_VALUE       16                                 /* PROXYSTA HASH???????? ????????32?????? ????16???? */
#define MAC_VAP_PROXYSTA_MAP_UNKNOW_VALUE     4                                 /* PROXYSTA HASH???????????????????? ????4???? */
#endif
#define HMAC_MAX_DSCP_VALUE_NUM      64
#define HMAC_DSCP_VALUE_INVALID      0xA5
/*****************************************************************************
  3 ????????
*****************************************************************************/
/*****************************************************************************
    ??????vap????????
*****************************************************************************/



/*****************************************************************************
  4 ????????????
*****************************************************************************/
#ifdef _PRE_WLAN_REPORT_PRODUCT_LOG
extern oal_uint8   g_auc_vapid_to_chipid[2 * WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT];
#endif

extern oal_uint8   g_uc_host_rx_ampdu_amsdu;
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
    oal_dlist_head_stru st_timeout_head;
}hmac_mgmt_timeout_stru;

typedef struct
{
    oal_uint16                  us_user_index;
    mac_vap_state_enum_uint8    en_state;
    oal_uint8                   uc_vap_id;
    mac_status_code_enum_uint16 en_status_code;
    oal_uint8                   auc_rsv[2];
}hmac_mgmt_timeout_param_stru;

#ifdef _PRE_WLAN_FEATURE_HS20
typedef struct
{
    oal_uint8  auc_up_low[MAX_QOS_UP_RANGE];             /* User Priority */
    oal_uint8  auc_up_high[MAX_QOS_UP_RANGE];
    oal_uint8  auc_dscp_exception_up[MAX_DSCP_EXCEPT];   /* User Priority of DSCP Exception field */
    oal_uint8  uc_valid;
    oal_uint8  uc_num_dscp_except;
    oal_uint8  auc_dscp_exception[MAX_DSCP_EXCEPT];      /* DSCP exception field  */
}hmac_cfg_qos_map_param_stru;
#endif

/*????????????????????????SDT??????????????????*/
typedef struct
{

    /***************************************************************************
                                ??????????
    ***************************************************************************/
    /* ????lan???????????? */
    oal_uint32  ul_rx_pkt_to_lan;                               /* ????????????????????????????????MSDU */
    oal_uint32  ul_rx_bytes_to_lan;                             /* ?????????????????????????? */

   /***************************************************************************
                                ??????????
    ***************************************************************************/
   /* ??lan?????????????????? */
   oal_uint32  ul_tx_pkt_num_from_lan;                         /* ??lan????????????,MSDU */
   oal_uint32  ul_tx_bytes_from_lan;                           /* ??lan???????????? */

}hmac_vap_query_stats_stru;
/*????????*/
typedef struct
{
    oal_uint32                       ul_rx_pkct_succ_num;                       /*????????????*/
    oal_uint32                       ul_dbb_num;                                /*DBB??????*/
    oal_uint32                       ul_check_fem_pa_status;                    /*fem??pa????????????*/
    oal_int16                        s_rx_rssi;
    oal_bool_enum_uint8              uc_get_dbb_completed_flag;                 /*????DBB??????????????????*/
    oal_bool_enum_uint8              uc_check_fem_pa_flag;                      /*fem??pa????????????????*/
    oal_bool_enum_uint8              uc_get_rx_pkct_flag;                       /*????????????????????*/
    oal_bool_enum_uint8              uc_lte_gpio_check_flag;                    /*????????????????????*/
    oal_bool_enum_uint8              uc_report_efuse_reg_flag;              /*efuse ??????????*/
    oal_bool_enum_uint8              uc_report_reg_flag;                    /*??????????????*/
    oal_uint32                       ul_reg_value;
    oal_uint8                        uc_ant_status : 4,
                                     uc_get_ant_flag : 4;
}hmac_atcmdsrv_get_stats_stru;

#ifdef _PRE_WLAN_FEATURE_EQUIPMENT_TEST
/*51???????? hipriv????????*/
typedef struct
{
    oal_uint8                   auc_data[HMAC_HIPRIV_ACK_BUF_SIZE];
    oal_bool_enum_uint8         uc_get_hipriv_ack_flag;
    oal_int8                    *pc_buffer;
    oal_uint8                   auc_reserved[3];
    oal_uint32                  ul_buf_len;
}hmac_hipriv_ack_stats_stru;
#endif
typedef struct
{
    oal_dlist_head_stru           st_entry;
    oal_uint8                     auc_bssid[WLAN_MAC_ADDR_LEN];
    oal_uint8                     uc_reserved[2];
    oal_uint8                     auc_pmkid[WLAN_PMKID_LEN];
}hmac_pmksa_cache_stru;

typedef enum _hmac_tcp_opt_queue_
{
    HMAC_TCP_ACK_QUEUE = 0,
    HMAC_TCP_OPT_QUEUE_BUTT
} hmac_tcp_opt_queue;

#ifdef _PRE_WLAN_TCP_OPT
typedef oal_uint16 (* hmac_trans_cb_func)(void *pst_hmac_device, hmac_tcp_opt_queue type,hcc_chan_type dir, void* data);
/*tcp_ack????*/
typedef struct
{
    struct wlan_perform_tcp      hmac_tcp_ack;
    struct wlan_perform_tcp_list hmac_tcp_ack_list;
    wlan_perform_tcp_impls       filter_info;
    hmac_trans_cb_func           filter[HMAC_TCP_OPT_QUEUE_BUTT];	//????????????????
    oal_uint64                   all_ack_count[HMAC_TCP_OPT_QUEUE_BUTT];	//??????TCP ACK????
    oal_uint64                   drop_count[HMAC_TCP_OPT_QUEUE_BUTT];	//??????TCP ACK????
    oal_netbuf_head_stru         data_queue[HMAC_TCP_OPT_QUEUE_BUTT];
    oal_spin_lock_stru           data_queue_lock[HMAC_TCP_OPT_QUEUE_BUTT];
}hmac_tcp_ack_stru;
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
typedef struct hmac_psta_rep
{
    oal_rwlock_stru         st_lock;
    oal_dlist_head_stru     st_vsta_list;   // proxysta device list
    oal_dlist_head_stru     st_msta_list;   // main sta list
    oal_dlist_head_stru     st_pbss_list;   // proxy bss list
    oal_dlist_head_stru     ast_hash[MAC_VAP_PROXY_STA_HASH_MAX_VALUE];
    oal_bool_enum_uint8     en_isolation;
    oal_uint8               uc_use_cnt;
    oal_uint8               uc_resv[2];
} hmac_psta_rep_stru;

typedef struct hmac_psta_mgr
{
    hmac_psta_rep_stru       ast_rep[WLAN_PROXY_STA_MAX_REP];
    oal_proc_dir_entry_stru *pst_proc_entry;
} hmac_psta_mgr_stru;

typedef  struct
{
    oal_dlist_head_stru     st_hash_entry;
    oal_dlist_head_stru     st_xsta_entry;
    oal_uint8               auc_oma[WLAN_MAC_ADDR_LEN];
    oal_uint8               uc_rep_id;
    oal_uint8               auc_resv[1];
} hmac_psta_stru;

#define hmac_vap_psta_oma(vap)  ((vap)->st_psta.auc_oma)
#define hmac_vap_psta_in_rep(vap)   (!oal_dlist_is_empty(&(vap)->st_psta.st_hash_entry))
#endif

#if defined (_PRE_WLAN_FEATURE_WDS) || defined (_PRE_WLAN_FEATURE_VIRTUAL_MULTI_STA)
#define WDS_HASH_NUM                    (1<<2)
#define WDS_AGING_TIME                  (300 * OAL_TIME_HZ)

typedef enum
{
    WDS_MODE_NONE = 0,
    WDS_MODE_ROOTAP,
    WDS_MODE_REPEATER_STA,
    WDS_MODE_BUTT
}hmac_vap_wds_vap_mode_enum;
typedef oal_uint8 hmac_vap_wds_vap_mode_enum_uint8;

typedef struct
{
    oal_rwlock_stru                     st_lock;
    frw_timeout_stru                    st_wds_timer;
    oal_dlist_head_stru                 st_peer_node[WDS_HASH_NUM];
    oal_dlist_head_stru                 st_wds_stas[WDS_HASH_NUM];
    oal_dlist_head_stru                 st_neigh[WDS_HASH_NUM];
    oal_uint32                          ul_wds_aging;
    hmac_vap_wds_vap_mode_enum_uint8    en_wds_vap_mode;
    oal_uint8                           uc_wds_node_num;
    oal_uint16                          uc_wds_stas_num;
    oal_uint16                          uc_neigh_num;
    oal_uint8                           auc_resv[2];
}hmac_vap_wds_stru;
#endif

/* ????????ID???? */
typedef enum
{
    QUERY_ID_KO_VERSION = 0,
    QUERY_ID_PWR_REF    = 1,
    QUERY_ID_BCAST_RATE = 2,
    QUERY_ID_STA_INFO   = 3,
    QUERY_ID_ANT_RSSI   = 4,
    QUERY_ID_STA_DIAG_INFO = 5,
    QUERY_ID_VAP_DIAG_INFO = 6,
    QUERY_ID_SENSING_BSSID_INFO = 7,
    QUERY_ID_BG_NOISE           = 8,
#ifdef _PRE_FEATURE_FAST_AGING
    QUERY_ID_FAST_AGING         = 9,
#endif
#ifdef _PRE_WLAN_FEATURE_TCP_ACK_BUFFER
    QUERY_ID_TCP_ACK_BUF        = 10,
#endif
    QUERY_ID_MODE_BUTT
}hmac_vap_query_enent_id_enum;
typedef oal_uint8 hmac_vap_query_enent_id_enumm_uint8;

#ifdef _PRE_WLAN_FEATURE_11K_EXTERN
typedef struct mac_vap_rrm_info_tag
{
    mac_action_rm_rpt_stru              *pst_rm_rpt_action;         /* Report Frame Addr*/
    mac_meas_rpt_ie_stru                *pst_meas_rpt_ie;           /* Measurement Report IE Addr */
    oal_netbuf_stru                     *pst_rm_rpt_mgmt_buf;       /* Report Frame Addr for Transfer */

    oal_uint8                            uc_action_code;
    oal_uint8                            uc_dialog_token;
    oal_bool_enum_uint8                  en_is_measuring;
    oal_uint8                            auc_rsv1[1];

    oal_uint16                           us_req_user_id;
    oal_uint16                           us_rm_rpt_action_len;      /* Report Frame Length for Transfer */
    mac_meas_req_ie_stru                *pst_meas_req_ie;

#ifdef _PRE_WLAN_FEATURE_11K
    mac_scan_req_stru                   *pst_scan_req;
    mac_bcn_rpt_stru                    *pst_bcn_rpt_item;          /* Beacon Report Addr */

    oal_uint8                            uc_quiet_count;
    oal_uint8                            uc_quiet_period;
    oal_mac_quiet_state_uint8            en_quiet_state;
    oal_uint8                            uc_link_dialog_token;

    oal_uint8                            uc_ori_max_reg_pwr;
    oal_uint8                            uc_local_pwr_constraint;
    oal_uint8                            uc_ori_max_pwr_flush_flag;
    oal_uint8                            uc_rsv;

    oal_int8                             c_link_tx_pwr_used;
    oal_int8                             c_link_max_tx_pwr;
    oal_uint16                           us_quiet_duration;

    oal_uint16                           us_quiet_offset;
    oal_uint8                            auc_rsv2[2];

    oal_dlist_head_stru                  st_meas_rpt_list;  /*Report????*/
    frw_timeout_stru                     st_quiet_timer;    /* quiet????????????????quiet????????quiet duration??????????????quiet */
    frw_timeout_stru                     st_offset_timer;   /* ????????tbtt??????????????offset????????offset??????????????????quiet????????quiet?????? */
#endif
    mac_bcn_req_info_stru                st_bcn_req_info;   /*??????????bcn????*/
    mac_neighbor_req_info_stru           st_neighbor_req_info;   /*??????????neighbor????*/
    oal_uint32                           aul_act_meas_start_time[2];

    frw_timeout_stru                     st_meas_status_timer;
}mac_vap_rrm_info_stru;
#endif //_PRE_WLAN_FEATURE_11K_EXTERN

#ifdef _PRE_WLAN_FEATURE_SINGLE_PROXYSTA
typedef struct
{
    oal_rwlock_stru                     st_lock;                                                /* ?????????? */
    oal_dlist_head_stru                 ast_map_ipv4_head[MAC_VAP_PROXYSTA_MAP_MAX_VALUE];      /* IPV4??map hash?? */
    oal_dlist_head_stru                 ast_map_ipv6_head[MAC_VAP_PROXYSTA_MAP_MAX_VALUE];      /* IPV6??map hash?? */
    oal_dlist_head_stru                 ast_map_unknow_head[MAC_VAP_PROXYSTA_MAP_UNKNOW_VALUE]; /* ??????????map hash?? */
    oal_uint8                           uc_map_ipv4_num;        /* ????ipv4?????? */
    oal_uint8                           uc_map_ipv6_num;        /* ????ipv6?????? */
    oal_uint8                           uc_map_unknow_num;      /* ?????????????????? */
    oal_uint8                           uc_resv;
}hmac_vap_proxysta_stru;
#endif  //_PRE_WLAN_FEATURE_SINGLE_PROXYSTA

typedef struct
{
    oal_uint8               uc_type;
    oal_uint8               uc_eid;
    oal_uint8               auc_resv[2];
}hmac_remove_ie_stru;

#ifdef _PRE_WLAN_FEATURE_M2S
typedef struct
{
    frw_timeout_stru      st_arp_probe_timer;          /* ????ARP REQ???????????? */
    oal_atomic            ul_rx_unicast_pkt_to_lan;    /* ?????????????????? */
    oal_uint8             uc_rx_no_pkt_count;          /* ?????????????????????????? */
    oal_bool_enum_uint8   en_arp_probe_on;             /* ????????arp?????????????????? */
    wlan_m2s_action_type_enum_uint8  en_action_type;
} hmac_vap_m2s_stru;
#endif

/* hmac vap?????? */
/* ??????????????????????????????????????????????8????????*/
typedef struct hmac_vap_tag
{
    /* ap sta???????? */
    oal_net_device_stru            *pst_net_device;                             /* VAP??????net_devices */
    oal_uint8                       auc_name[OAL_IF_NAME_SIZE];                 /* VAP????*/
    hmac_vap_cfg_priv_stru          st_cfg_priv;                                /* wal hmac???????????? */

    oal_spin_lock_stru              st_lock_state;                              /* ????????????????VAP???????????? */

    oal_mgmt_tx_stru                st_mgmt_tx;
    frw_timeout_stru                st_mgmt_timer;
    hmac_mgmt_timeout_param_stru    st_mgmt_timetout_param;

    frw_timeout_stru                st_scan_timeout;                            /* vap???????????????????????????????????????? */

#ifdef _PRE_WLAN_FEATURE_AMPDU_TX_HW
    oal_delayed_work                st_ampdu_work;
    oal_spin_lock_stru              st_ampdu_lock;
    oal_delayed_work                st_set_hw_work;
    mac_cfg_ampdu_tx_on_param_stru  st_mode_set;
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    hmac_psta_stru                  st_psta;
#endif
    hmac_remove_ie_stru             st_remove_ie;                           /* ??????????????IE???? */

#if (_PRE_WLAN_FEATURE_BLACKLIST_LEVEL != _PRE_WLAN_FEATURE_BLACKLIST_NONE)
    mac_blacklist_info_stru        *pst_blacklist_info;                          /* ?????????? */
#endif
#ifdef _PRE_WLAN_FEATURE_ISOLATION
    mac_isolation_info_stru         st_isolation_info;                          /* ???????????? */
#endif

#ifdef _PRE_WLAN_FEATURE_P2P
    oal_net_device_stru            *pst_p2p0_net_device;                        /* ????p2p0 net device */
    oal_net_device_stru            *pst_del_net_device;                         /* ????????????cfg80211 ?????????? net device */
    oal_work_stru                   st_del_virtual_inf_worker;                  /* ????net_device ???????? */
    oal_bool_enum_uint8             en_wait_roc_end;
    oal_uint8                       auc_resv6[3];
    oal_completion                  st_roc_end_ready;                           /* roc end completion */

#endif

#ifdef _PRE_WLAN_FEATURE_HS20
    hmac_cfg_qos_map_param_stru     st_cfg_qos_map_param;
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    oal_netbuf_head_stru            st_tx_queue_head[2];                        /* 2????????????2??????pinpon???? */
    oal_uint8                       uc_in_queue_id;
    oal_uint8                       uc_out_queue_id;
    oal_uint8                       auc_resv0[2];
    oal_atomic                      ul_tx_event_num;                            /* frw?????????????? */
    oal_uint32                      ul_tx_quata;                                /* ?????????????????? */
    oal_spin_lock_stru              st_smp_lock;
#endif

#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    oal_uint8                       bit_init_flag:1;                            /* ???????????????????? */
    oal_uint8                       bit_ack_policy:1;                           /* ack policy: 0:normal ack 1:normal ack */
    oal_uint8                       bit_reserved:6;
    oal_uint8                       auc_resv1[3];
#endif

#ifdef _PRE_WLAN_FEATURE_ROAM
    oal_uint32                     *pul_roam_info;
    oal_bool_enum_uint8             en_roam_prohibit_on;                        /* ???????????? */
#endif

    /* ?????????????? */
#if defined(_PRE_WLAN_FEATURE_MCAST) || defined(_PRE_WLAN_FEATURE_HERA_MCAST)
    oal_void                        *pst_m2u;
#endif

#ifdef _PRE_WLAN_DFT_STAT
    oal_uint8                       uc_device_distance;
    oal_uint8                       uc_intf_state_cca;
    oal_uint8                       uc_intf_state_co;
    oal_uint8                       auc_resv2[1];
#endif

    oal_uint16                      us_rx_timeout[WLAN_WME_AC_BUTT];            /* ?????????????????????? */
    oal_uint16                      us_rx_timeout_min[WLAN_WME_AC_BUTT];        /* ?????????????????????? */

    oal_uint16                      us_del_timeout;                             /* ????????????????ba???? ??????0???????? */
    mac_cfg_mode_param_stru         st_preset_para;                             /* STA?????????????????????????? */
    oal_uint8                       auc_supp_rates[WLAN_MAX_SUPP_RATES];        /* ???????????? */

#if defined(_PRE_WLAN_FEATURE_DBAC) && defined(_PRE_WLAN_FEATRUE_DBAC_DOUBLE_AP_MODE)
    oal_bool_enum_uint8             en_omit_acs_chan;
#else
    oal_uint8                       auc_resv3[1];
#endif

#ifdef _PRE_WLAN_FEATURE_SINGLE_CHIP_DUAL_BAND
    wlan_channel_band_enum          en_restrict_band;
#else
    oal_uint8                       auc_resv4[1];
#endif

#ifdef _PRE_WLAN_FEATURE_WMMAC
    oal_uint8                       uc_ts_dialog_token;                         /* TS???????????????? */
    oal_bool_enum_uint8             en_wmmac_auth_flag;
    oal_uint8                       uc_resv5[2];
#endif //_PRE_WLAN_FEATURE_WMMAC

    oal_bool_enum_uint8             auc_query_flag[QUERY_ID_MODE_BUTT];
    mac_cfg_param_char_stru         st_param_char;

    /* sta???????? */
    oal_bool_enum_uint8               en_no_beacon;
    oal_uint8                         uc_no_smps_user_cnt_ap;                     /* AP????????????SMPS????????  */
    oal_uint8                         uc_ba_dialog_token;                         /* BA???????????????? */
    oal_bool_enum_uint8               en_updata_rd_by_ie_switch;                  /*??????????????ap????????????????*/

    oal_uint8                       bit_sta_protocol_cfg    :   1;
    oal_uint8                       bit_protocol_fall       :   1;              /* ???????????? */
    oal_uint8                       bit_reassoc_flag        :   1;             /* ?????????????????????????????? */
    oal_uint8                       bit_rx_ampduplusamsdu_active:1;
#if defined(_PRE_WLAN_FEATURE_11K) || defined(_PRE_WLAN_FEATURE_11R) || defined(_PRE_WLAN_FEATURE_11K_EXTERN) || defined(_PRE_WLAN_FEATURE_11V_ENABLE)
    oal_uint8                       bit_11k_auth_flag       :   1;             /* 11k ??????????*/
    oal_uint8                       bit_voe_11r_auth        :   1;
    oal_uint8                       bit_11k_auth_oper_class :   2;
    oal_uint8                       bit_11r_over_ds         :   1;             /*????????11r over ds??0????over ds??over air????*/
    oal_uint8                       bit_resv                :   7;
    oal_uint8                       auc_resv[2];
    oal_uint8                       bit_11k_enable          :   1;
    oal_uint8                       bit_11v_enable          :   1;
    oal_uint8                       bit_11r_enable          :   1;
    oal_uint8                       bit_bcn_table_switch    :   1;
#else
    oal_uint8                       bit_resv                :   4;
#endif // _PRE_WLAN_FEATURE_11K
    oal_int8                        ac_desired_country[3];                      /* ????????AP????????????????????????????????????????????\0 */

    oal_dlist_head_stru             st_pmksa_list_head;

    /* ???????? */
    oal_wait_queue_head_stru         query_wait_q;                              /*????????????*/
    oal_station_info_stru            station_info;
    station_info_extend_stru         st_station_info_extend;                    /*CHR2.0??????STA????????*/

    oal_bool_enum_uint8              station_info_query_completed_flag;         /*??????????????OAL_TRUE????????????OAL_FALSE????????????*/
    oal_int16                        s_free_power;                              /* ???? */
    oal_bool_enum_uint8              en_addr_filter;

    oal_int32                        center_freq;                               /* ???????? */
#if defined(_PRE_WLAN_FEATURE_EQUIPMENT_TEST) && (defined _PRE_WLAN_FIT_BASED_REALTIME_CALI)
    mac_cfg_show_pd_paras_stru       st_polynomial_paras;
    mac_cfg_show_upc_paras_stru      st_upc_paras;
#endif
    mac_cfg_show_dieid_stru          st_dieid;
    hmac_atcmdsrv_get_stats_stru     st_atcmdsrv_get_status;
    oal_proc_dir_entry_stru         *pst_proc_dir;                              /* vap??????proc???? */

#ifdef _PRE_WLAN_DFT_STAT
    /*????????+????????????????????????????????????????SDT????????????*/
    hmac_vap_query_stats_stru        st_query_stats;
#endif

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    frw_timeout_stru                 st_edca_opt_timer;                         /* edca?????????????? */
    oal_uint32                       ul_edca_opt_time_ms;                       /* edca?????????????????? */
    oal_uint8                        uc_edca_opt_flag_ap;                       /* ap??????????????edca???????? */
    oal_uint8                        uc_edca_opt_flag_sta;                      /* sta??????????????edca???????? */
    oal_uint8                        uc_edca_opt_weight_sta;                    /* ????beacon??edca???????????????????? 3*/
    oal_uint8                        uc_idle_cycle_num;                         /* vap????????idle?????????????? */
#endif

#ifdef _PRE_WLAN_TCP_OPT
    hmac_tcp_ack_stru          st_hamc_tcp_ack[HCC_DIR_COUNT];
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_h2d_protection_stru          st_prot;
#endif

#ifdef _PRE_WLAN_FEATURE_STA_PM
    frw_timeout_stru                 st_ps_sw_timer;                             /* ?????????? */
    oal_uint8                        uc_cfg_sta_pm_manual;                       /* ????????sta pm mode?????? */
    oal_uint8                        uc_ps_mode;
    oal_uint16                       us_check_timer_pause_cnt;                   /* ??????pause???? */
#endif

#ifdef _PRE_WLAN_FEATURE_EQUIPMENT_TEST
    hmac_hipriv_ack_stats_stru       st_hipriv_ack_stats;
#endif
#ifdef _PRE_WLAN_FEATURE_SMARTANT
    oal_bool_enum_uint8             en_ant_info_query_completed_flag;           /*??????????????OAL_TRUE????????????OAL_FALSE????????????*/
    oal_bool_enum_uint8             en_double_ant_switch_query_completed_flag;  /*??????????????OAL_TRUE????????????OAL_FALSE????????????*/
    oal_uint8                       auc_resv10[2];
    oal_uint32                      ul_double_ant_switch_ret;
#endif

    oal_int32                               l_temp;
#if defined (_PRE_WLAN_FEATURE_WDS) || defined (_PRE_WLAN_FEATURE_VIRTUAL_MULTI_STA)
    hmac_vap_wds_stru                st_wds_table;
#endif
#ifdef _PRE_WLAN_FEATURE_11R_AP
    oal_mlme_ie_stru                *pst_mlme;
#endif

#ifdef _PRE_WLAN_FEATURE_CAR
       hmac_car_limit_stru                    st_car_vap_cfg[HMAC_CAR_BUTT];    /* vap??????????,0-up 1-down */
#endif

#ifdef _PRE_WLAN_FEATURE_11K_EXTERN
    mac_vap_rrm_info_stru                  *pst_rrm_info;
#endif

#ifdef _PRE_WLAN_WEB_CMD_COMM
    oal_machw_flow_stat_stru            st_machw_stat;
#ifdef _PRE_WLAN_11K_STAT
    oal_wme_stat_stru                   st_wme_stat;
    oal_tx_delay_ac_stru                st_tx_delay_ac;
#endif
#endif
    oal_uint8                           auc_dscp_tid_map[HMAC_MAX_DSCP_VALUE_NUM];
#ifdef _PRE_WLAN_FEATURE_SINGLE_PROXYSTA
    hmac_vap_proxysta_stru              *pst_vap_proxysta;                                /* Proxy STA ?????????????????? */
    proxysta_mode_enum_uint8            en_proxysta_mode;                                 /* Proxy STA ??VAP???????? */
    oal_uint8                           auc_resv8[3];
#endif

#ifdef _PRE_WLAN_FEATURE_M2S
    hmac_vap_m2s_stru                   st_hmac_vap_m2s;
#endif

    mac_vap_stru                        st_vap_base_info;                           /* MAC vap??????????????! */
}hmac_vap_stru;

typedef enum _hmac_cac_event_
{
    HMAC_CAC_STARTED = 0,
    HMAC_CAC_FINISHED,
    HMAC_CAC_ABORTED,

    HMAC_CAC_BUTT
} hmac_cac_event;


typedef struct
{
    hmac_cac_event                          en_type;
    oal_uint32                              ul_freq;
    wlan_channel_bandwidth_enum_uint8       en_bw_mode;
    oal_uint8                               auc[23];
}hmac_cac_event_stru;

/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/



/*****************************************************************************
  10 ????????
*****************************************************************************/
extern oal_uint32  hmac_vap_destroy_etc(hmac_vap_stru *pst_vap);
extern oal_uint32  hmac_vap_init_etc(
                       hmac_vap_stru              *pst_hmac_vap,
                       oal_uint8                   uc_chip_id,
                       oal_uint8                   uc_device_id,
                       oal_uint8                   uc_vap_id,
                       mac_cfg_add_vap_param_stru *pst_param);

extern oal_uint32  hmac_vap_creat_netdev_etc(hmac_vap_stru *pst_hmac_vap, oal_int8 *puc_netdev_name, oal_int8 *puc_mac_addr);

extern oal_uint16 hmac_vap_check_ht_capabilities_ap_etc(
            hmac_vap_stru                  *pst_hmac_vap,
            oal_uint8                      *puc_payload,
            oal_uint32                      ul_msg_len,
            hmac_user_stru                 *pst_hmac_user_sta);
extern  oal_uint32  hmac_search_ht_cap_ie_ap_etc(
                hmac_vap_stru               *pst_hmac_vap,
                hmac_user_stru              *pst_hmac_user_sta,
                oal_uint8                   *puc_payload,
                oal_uint16                   us_index,
                oal_bool_enum                en_prev_asoc_ht);
extern oal_bool_enum_uint8 hmac_vap_addba_check(
                hmac_vap_stru      *pst_hmac_vap,
                hmac_user_stru     *pst_hmac_user,
                oal_uint8           uc_tidno);

extern oal_void hmac_vap_net_stopall_etc(oal_void);
extern oal_void hmac_vap_net_startall_etc(oal_void);

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
extern oal_bool_enum_uint8 hmac_flowctl_check_device_is_sta_mode_etc(oal_void);
extern oal_void hmac_vap_net_start_subqueue_etc(oal_uint16 us_queue_idx);
extern oal_void hmac_vap_net_stop_subqueue_etc(oal_uint16 us_queue_idx);
#endif
extern oal_void hmac_handle_disconnect_rsp_etc(hmac_vap_stru *pst_hmac_vap, hmac_user_stru *pst_hmac_user,
                                                  mac_reason_code_enum_uint16  en_disasoc_reason);
extern oal_uint8 * hmac_vap_get_pmksa_etc(hmac_vap_stru *pst_hmac_vap, oal_uint8 *puc_bssid);
oal_uint32 hmac_tx_get_mac_vap_etc(oal_uint8 uc_vap_id, mac_vap_stru **pst_vap_stru);
extern oal_uint32 hmac_restart_all_work_vap(oal_uint8 uc_chip_id);
#ifdef _PRE_WLAN_FEATURE_AMPDU_TX_HW
extern oal_void hmac_set_ampdu_worker(oal_delayed_work *pst_work);
extern oal_void hmac_set_ampdu_hw_worker(oal_delayed_work *pst_work);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_vap.h */
