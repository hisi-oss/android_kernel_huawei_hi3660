


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "wal_linux_ioctl.h"
#include "wal_main.h"
#include "wal_config.h"
#include "wal_linux_scan.h"



#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_LINUX_EVENT_C

/*****************************************************************************
  2 ????????????
*****************************************************************************/


/*****************************************************************************
  3 ????????
*****************************************************************************/


oal_int32 wal_cfg80211_start_req_etc(oal_net_device_stru    *pst_net_dev,
                                void                        *ps_param,
                                oal_uint16                   us_len,
                                wlan_cfgid_enum_uint16       en_wid,
                                oal_bool_enum_uint8          en_need_rsp)
{
    wal_msg_write_stru              st_write_msg;
    wal_msg_stru                   *pst_rsp_msg = OAL_PTR_NULL;
    oal_uint32                      ul_err_code;
    oal_int32                       l_ret;

    if (OAL_PTR_NULL == ps_param )
    {
         OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{wal_cfg80211_start_req_etc::param is null!}\r\n");
         return OAL_ERR_CODE_PTR_NULL;
    }

    /* ???? msg ??????*/
    st_write_msg.en_wid = en_wid;
    st_write_msg.us_len = us_len;

    /* ???? msg ?????? */
    if(WAL_MSG_WRITE_MAX_LEN < us_len)
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{wal_cfg80211_start_req_etc::us_len %d > WAL_MSG_WRITE_MAX_LEN %d err!}\r\n", us_len, WAL_MSG_WRITE_MAX_LEN);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }
    oal_memcopy(st_write_msg.auc_value, ps_param, us_len);

    /***************************************************************************
           ????????wal??????
    ***************************************************************************/
    l_ret = wal_send_cfg_event_etc(pst_net_dev,
                           WAL_MSG_TYPE_WRITE,
                           WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                           (oal_uint8 *)&st_write_msg,
                           en_need_rsp,
                           en_need_rsp ? &pst_rsp_msg : OAL_PTR_NULL);
    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{wal_cfg80211_start_req_etc::wal_send_cfg_event_etc return err code %d!}\r\n", l_ret);
        return l_ret;
    }

    if(en_need_rsp && (OAL_PTR_NULL != pst_rsp_msg))
    {
        /* ???????????????? */
        ul_err_code = wal_check_and_release_msg_resp_etc(pst_rsp_msg);
        if(OAL_SUCC != ul_err_code)
        {
            OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{wal_cfg80211_start_req_etc::wal_send_cfg_event_etc return err code:[%u]}",
                           ul_err_code);
            return -OAL_EFAIL;
        }
    }

    return OAL_SUCC;
}


oal_uint32  wal_cfg80211_start_scan_etc(oal_net_device_stru *pst_net_dev, mac_cfg80211_scan_param_stru *pst_scan_param)
{

    if (OAL_PTR_NULL == pst_scan_param)
    {
         OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{wal_cfg80211_start_scan_etc::scan failed, null ptr, pst_scan_param = null.}\r\n");
         return OAL_ERR_CODE_PTR_NULL;
    }

    return (oal_uint32)wal_cfg80211_start_req_etc(pst_net_dev, pst_scan_param,
                                    OAL_SIZEOF(mac_cfg80211_scan_param_stru), WLAN_CFGID_CFG80211_START_SCAN, OAL_FALSE);
}


oal_uint32  wal_cfg80211_start_sched_scan_etc(oal_net_device_stru *pst_net_dev, mac_pno_scan_stru *pst_pno_scan_info)
{
    mac_pno_scan_stru      *pst_pno_scan_params;
    oal_uint32              ul_ret = OAL_SUCC;
    /* ????pno??????????????????????hmac?????? */
    pst_pno_scan_params = (mac_pno_scan_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(mac_pno_scan_stru), OAL_FALSE);
    if (OAL_PTR_NULL == pst_pno_scan_params)
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{wal_cfg80211_start_sched_scan_etc::alloc pno scan param memory failed!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_memcopy(pst_pno_scan_params, pst_pno_scan_info, OAL_SIZEOF(mac_pno_scan_stru));

    ul_ret = (oal_uint32)wal_cfg80211_start_req_etc(pst_net_dev, &pst_pno_scan_params,
                                    OAL_SIZEOF(pst_pno_scan_params), WLAN_CFGID_CFG80211_START_SCHED_SCAN, OAL_TRUE);

    /* ????wal_cfg80211_start_req???????????????????????????????? */
    OAL_MEM_FREE(pst_pno_scan_params, OAL_FALSE);

    return ul_ret;
}



oal_int32  wal_cfg80211_start_connect_etc(oal_net_device_stru *pst_net_dev, mac_conn_param_stru *pst_mac_conn_param)
{
    return wal_cfg80211_start_req_etc(pst_net_dev,
                pst_mac_conn_param,
                OAL_SIZEOF(mac_conn_param_stru),
                WLAN_CFGID_CFG80211_START_CONNECT,
                OAL_TRUE);
}


oal_int32  wal_cfg80211_start_disconnect_etc(oal_net_device_stru *pst_net_dev, mac_cfg_kick_user_param_stru *pst_disconnect_param)
{
    mac_vap_stru    *pst_mac_vap;

    // ??????????????????
    if ((pst_mac_vap = OAL_NET_DEV_PRIV(pst_net_dev)) && (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode))
    {
        wal_force_scan_complete_for_disconnect_scene(pst_net_dev);
    }

    /* ???? ??????????????????????????????????WPA_SUPPLICANT??????????????????????????????????????????????????????????????????????????????
       ??????????????????????????????????????????????????????????????OAL_FALSE????OAL_TRUE */
    return wal_cfg80211_start_req_etc(pst_net_dev, pst_disconnect_param, OAL_SIZEOF(mac_cfg_kick_user_param_stru), WLAN_CFGID_KICK_USER, OAL_TRUE);
}
#ifdef _PRE_WLAN_FEATURE_HILINK

oal_int32  wal_cfg80211_fbt_kick_user(oal_net_device_stru *pst_net_dev, mac_cfg_kick_user_param_stru *pst_disconnect_param)
{
    return wal_cfg80211_start_req_etc(pst_net_dev, pst_disconnect_param, OAL_SIZEOF(mac_cfg_kick_user_param_stru), WLAN_CFGID_FBT_KICK_USER, OAL_TRUE);
}

#ifdef _PRE_WLAN_FEATURE_HILINK_HERA_PRODUCT

oal_int32 wal_cfg80211_set_okc_ie(oal_net_device_stru *pst_net_dev, oal_app_ie_stru *pst_okc_ie)
{
    return wal_cfg80211_start_req_etc(pst_net_dev, pst_okc_ie, OAL_SIZEOF(oal_app_ie_stru), WLAN_CFGID_SET_VENDOR_IE, OAL_TRUE);
}

oal_int32 wal_cfg80211_set_hiden_whitelist(oal_net_device_stru *pst_net_dev, oal_hilink_white_node_stru *pst_white_lst)
{
    return wal_cfg80211_start_req_etc(pst_net_dev, pst_white_lst, OAL_SIZEOF(oal_hilink_white_node_stru), WLAN_CFGID_SET_WHITE_LIST_SSIDHIDEN, OAL_TRUE);
}

oal_int32 wal_cfg80211_start_fbt_scan(oal_net_device_stru *pst_net_dev, oal_hilink_scan_params *pst_mac_cfg_fbt_scan_params)
{
    return wal_cfg80211_start_req_etc(pst_net_dev, pst_mac_cfg_fbt_scan_params, OAL_SIZEOF(oal_hilink_scan_params), WLAN_CFGID_FBT_START_SCAN, OAL_FALSE);
}

oal_int32 wal_cfg80211_set_mgmt_frame_filter(oal_net_device_stru *pst_net_dev, oal_uint32 *pul_mgmt_frame_filter)
{
    return wal_cfg80211_start_req_etc(pst_net_dev, pul_mgmt_frame_filter, OAL_SIZEOF(oal_uint32), WLAN_CFGID_SET_MGMT_FRAME_FILTERS, OAL_TRUE);
}

oal_int32 wal_cfg80211_set_sensing_bssid(oal_net_device_stru *pst_net_dev, oal_void *pst_sensing_bssid)
{
    return wal_cfg80211_start_req_etc(pst_net_dev, pst_sensing_bssid, OAL_SIZEOF(dmac_sensing_bssid_cfg_stru), WLAN_CFGID_SET_SENSING_BSSID, OAL_TRUE);
}

#endif
#endif

#ifdef _PRE_WLAN_FEATURE_AP_PM

oal_uint32 wal_config_sta_scan_connect_event(oal_net_device_stru * pst_net_dev,  oal_uint8 *puc_param)
{
    return (oal_uint32)wal_cfg80211_start_req_etc(pst_net_dev, puc_param, OAL_SIZEOF(oal_uint8), WLAN_CFGID_STA_SCAN_CONNECT, OAL_TRUE);
}
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

