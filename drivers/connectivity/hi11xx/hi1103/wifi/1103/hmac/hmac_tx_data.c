


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "oal_profiling.h"
#include "oal_net.h"
#include "frw_ext_if.h"
#include "hmac_tx_data.h"
#include "hmac_tx_amsdu.h"
#include "mac_frame.h"
#include "mac_data.h"
#include "hmac_frag.h"
#include "hmac_11i.h"
#if defined(_PRE_WLAN_FEATURE_MCAST) || defined(_PRE_WLAN_FEATURE_HERA_MCAST) /* ?????????? */
#include "hmac_m2u.h"
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
#include "hmac_proxy_arp.h"
#endif

#ifdef _PRE_WLAN_FEATURE_WAPI
#include "hmac_wapi.h"
#endif

#ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
#include "hmac_traffic_classify.h"
#endif

#include "hmac_crypto_tkip.h"
#include "hmac_device.h"
#include "hmac_resource.h"

#include "hmac_tcp_opt.h"

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#include "hisi_customize_wifi.h"
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#include "hmac_proxysta.h"
#endif
#ifdef _PRE_WLAN_FEATURE_SINGLE_PROXYSTA
#include "hmac_single_proxysta.h"
#endif

#if defined (_PRE_WLAN_FEATURE_WDS) || defined (_PRE_WLAN_FEATURE_VIRTUAL_MULTI_STA)
#include "hmac_wds.h"
#endif

#ifdef _PRE_WLAN_FEATURE_CAR
#include "hmac_car.h"
#endif
#include "mem_trace.h"

#include "hmac_auto_adjust_freq.h"  //??????????????????

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include "plat_pm_wlan.h"
#endif

#ifdef _PRE_WLAN_PKT_TIME_STAT
#include  <hwnet/ipv4/wifi_delayst.h>
#endif

#ifdef _PRE_WLAN_FEATURE_SNIFFER
#include <hwnet/ipv4/sysctl_sniffer.h>
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_TX_DATA_C
/*
 * definitions of king of games feature
 */
#ifdef CONFIG_NF_CONNTRACK_MARK
#define VIP_APP_VIQUE_TID              WLAN_TIDNO_VIDEO
#define VIP_APP_MARK                   0x5a
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 0))
#define PKTMARK(p)                     (((struct sk_buff *)(p))->mark)
#define PKTSETMARK(p, m)               ((struct sk_buff *)(p))->mark = (m)
#else /* !2.6.0 */
#define PKTMARK(p)                     (((struct sk_buff *)(p))->nfmark)
#define PKTSETMARK(p, m)               ((struct sk_buff *)(p))->nfmark = (m)
#endif /* 2.6.0 */
#else /* CONFIG_NF_CONNTRACK_MARK */
#define PKTMARK(p)                     0
#define PKTSETMARK(p, m)
#endif /* CONFIG_NF_CONNTRACK_MARK */


/*****************************************************************************
  2 ????????????
*****************************************************************************/
#if defined(_PRE_PRODUCT_ID_HI110X_HOST)
OAL_STATIC oal_uint8 g_uc_ac_new = 0;
#endif
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
static oal_uint16 us_noqos_frag_seqnum= 0; /*??????qos??????seqnum*/
#endif

#ifdef _PRE_WLAN_FEATURE_AMPDU_TX_HW
hmac_tx_ampdu_hw_stru   g_st_ampdu_hw = {0};
#endif

/*****************************************************************************
  3 ????????
*****************************************************************************/
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
oal_uint32 hmac_tx_data(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf);
#endif



OAL_STATIC OAL_INLINE oal_bool_enum_uint8 hmac_tx_is_dhcp(mac_ether_header_stru  *pst_ether_hdr)
{
    mac_ip_header_stru     *puc_ip_hdr;

    puc_ip_hdr = (mac_ip_header_stru *)(pst_ether_hdr + 1);

    return mac_is_dhcp_port_etc(puc_ip_hdr);
}



OAL_STATIC oal_void hmac_tx_report_dhcp_and_arp(
                                            mac_vap_stru  *pst_mac_vap,
                                            mac_ether_header_stru  *pst_ether_hdr,
                                            oal_uint16   us_ether_len)
{
    oal_bool_enum_uint8     en_flg = OAL_FALSE;

    switch (OAL_HOST2NET_SHORT(pst_ether_hdr->us_ether_type))
    {
        case ETHER_TYPE_ARP:
            en_flg = OAL_TRUE;
        break;

        case ETHER_TYPE_IP:
            en_flg = hmac_tx_is_dhcp(pst_ether_hdr);
        break;

        default:
            en_flg = OAL_FALSE;
        break;
    }

    if (en_flg && oam_report_dhcp_arp_get_switch_etc())
    {
        if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
        {
            oam_report_eth_frame_etc(pst_ether_hdr->auc_ether_dhost, (oal_uint8 *)pst_ether_hdr, us_ether_len, OAM_OTA_FRAME_DIRECTION_TYPE_TX);
        }
        else if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
        {
            oam_report_eth_frame_etc(pst_mac_vap->auc_bssid, (oal_uint8 *)pst_ether_hdr, us_ether_len, OAM_OTA_FRAME_DIRECTION_TYPE_TX);
        }
        else
        {
        }
    }

}


oal_uint32  hmac_tx_report_eth_frame_etc(mac_vap_stru   *pst_mac_vap,
                                           oal_netbuf_stru *pst_netbuf)
{
    oal_uint16              us_user_idx = 0;
    mac_ether_header_stru  *pst_ether_hdr = OAL_PTR_NULL;
    oal_uint32              ul_ret;
    oal_uint8               auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0};
    oal_switch_enum_uint8   en_eth_switch = 0;
    hmac_vap_stru           *pst_hmac_vap = OAL_PTR_NULL;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap) || OAL_UNLIKELY(OAL_PTR_NULL == pst_netbuf))
    {
        OAM_ERROR_LOG2(0, OAM_SF_TX, "{hmac_tx_report_eth_frame_etc::input null %x %x}", pst_mac_vap, pst_netbuf);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG1(0, OAM_SF_TX, "{hmac_tx_report_eth_frame_etc::mac_res_get_hmac_vap fail. vap_id = %u}", pst_mac_vap->uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ?????????????????????????? */
    /* ???????? ??1)????pst_hmac_vap ??????????ifdef ????????2)   ul_rx_pkt_to_lan ??????ul_rx_bytes_to_lan???????????? */
#ifdef _PRE_WLAN_DFT_STAT
    HMAC_VAP_DFT_STATS_PKT_INCR(pst_hmac_vap->st_query_stats.ul_rx_pkt_to_lan,1);
    HMAC_VAP_DFT_STATS_PKT_INCR(pst_hmac_vap->st_query_stats.ul_rx_bytes_to_lan,OAL_NETBUF_LEN(pst_netbuf));
#endif
    OAM_STAT_VAP_INCR(pst_mac_vap->uc_vap_id, tx_pkt_num_from_lan, 1);
    OAM_STAT_VAP_INCR(pst_mac_vap->uc_vap_id, tx_bytes_from_lan, OAL_NETBUF_LEN(pst_netbuf));

    /* ??????????????????id??????MAC?????????????? */
    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        pst_ether_hdr = (mac_ether_header_stru *)oal_netbuf_data(pst_netbuf);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_ether_hdr))
        {
            OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_tx_report_eth_frame_etc::ether_hdr is null!\r\n");
            return OAL_ERR_CODE_PTR_NULL;
        }

        ul_ret = mac_vap_find_user_by_macaddr_etc(pst_mac_vap, pst_ether_hdr->auc_ether_dhost, &us_user_idx);
        if (OAL_ERR_CODE_PTR_NULL == ul_ret)
        {
            OAM_ERROR_LOG1(0, OAM_SF_TX, "{hmac_tx_report_eth_frame_etc::find user return ptr null!!\r\n", ul_ret);
            return ul_ret;
        }

#if defined (_PRE_WLAN_FEATURE_WDS) || defined (_PRE_WLAN_FEATURE_VIRTUAL_MULTI_STA)
        if (OAL_SUCC != ul_ret)
        {
            ul_ret = hmac_find_valid_user_by_wds_sta(pst_hmac_vap, pst_ether_hdr->auc_ether_dhost, &us_user_idx);
        }
#endif

        if (OAL_FAIL == ul_ret)
        {
            /* ??????????????????????????dhcp????arp request?????????? */
            hmac_tx_report_dhcp_and_arp(pst_mac_vap, pst_ether_hdr, (oal_uint16)OAL_NETBUF_LEN(pst_netbuf));
            return OAL_SUCC;
        }

        oal_set_mac_addr(auc_user_macaddr, pst_ether_hdr->auc_ether_dhost);
    }

    else if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        if (0 == pst_mac_vap->us_user_nums)
        {
            return OAL_SUCC;
        }
#if 1
        pst_ether_hdr = (mac_ether_header_stru *)oal_netbuf_data(pst_netbuf);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_ether_hdr))
        {
            OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_tx_report_eth_frame_etc::ether_hdr is null!\r\n");
            return OAL_ERR_CODE_PTR_NULL;
        }
        /* ??????????????????????????dhcp????arp request?????????? */
        hmac_tx_report_dhcp_and_arp(pst_mac_vap, pst_ether_hdr, (oal_uint16)OAL_NETBUF_LEN(pst_netbuf));

#endif
        us_user_idx = pst_mac_vap->us_assoc_vap_id;
        oal_set_mac_addr(auc_user_macaddr, pst_mac_vap->auc_bssid);
    }

    /* ?????????????????????? */
    ul_ret = oam_report_eth_frame_get_switch_etc(us_user_idx, OAM_OTA_FRAME_DIRECTION_TYPE_TX, &en_eth_switch);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_TX, "{hmac_tx_report_eth_frame_etc::get tx eth frame switch fail!\r\n");
        return ul_ret;
    }

    if (OAL_SWITCH_ON == en_eth_switch)
    {
        /* ???????????????????? */
        ul_ret = oam_report_eth_frame_etc(auc_user_macaddr,
                             oal_netbuf_data(pst_netbuf),
                             (oal_uint16)OAL_NETBUF_LEN(pst_netbuf),
                             OAM_OTA_FRAME_DIRECTION_TYPE_TX);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_TX, "{hmac_tx_report_eth_frame_etc::oam_report_eth_frame_etc return err: 0x%x.}\r\n", ul_ret);
        }
    }

    return OAL_SUCC;
}


oal_uint16 hmac_free_netbuf_list_etc(oal_netbuf_stru  *pst_buf)
{
    oal_netbuf_stru     *pst_buf_tmp;
    mac_tx_ctl_stru     *pst_tx_cb;
    oal_uint16           us_buf_num = 0;

    if(OAL_PTR_NULL != pst_buf)
    {
        pst_tx_cb = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_buf);

        while (OAL_PTR_NULL != pst_buf)
        {
            pst_buf_tmp = oal_netbuf_list_next(pst_buf);
            us_buf_num++;

            pst_tx_cb = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_buf);
            
            if ((oal_netbuf_headroom(pst_buf) <  MAC_80211_QOS_HTC_4ADDR_FRAME_LEN) && (OAL_PTR_NULL != MAC_GET_CB_FRAME_HEADER_ADDR(pst_tx_cb)))
            {
                OAL_MEM_FREE(MAC_GET_CB_FRAME_HEADER_ADDR(pst_tx_cb), OAL_TRUE);
                MAC_GET_CB_FRAME_HEADER_ADDR(pst_tx_cb) = OAL_PTR_NULL;
            }

            oal_netbuf_free(pst_buf);

            pst_buf = pst_buf_tmp;
        }
    }
    else
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_free_netbuf_list_etc::pst_buf is null}");
    }

    return us_buf_num;
}

#if 0

OAL_STATIC oal_void hmac_tx_classify_wlan_to_wlan(mac_tx_ctl_stru *pst_tx_ctl, oal_uint8 *puc_tid)
{
    mac_ieee80211_frame_stru            *pst_frame_header;
    mac_ieee80211_qos_frame_stru        *pst_qos_header;
    mac_ieee80211_qos_frame_addr4_stru  *pst_qos_addr4_headder;
    oal_uint8                            uc_tid = 0;


    OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_classify_wlan_to_wlan::enter func.}");
    pst_frame_header = pst_tx_ctl->pst_frame_header;

    /* ????????????????QoS data??????????????Qos????????tid?? */
    if (WLAN_DATA_BASICTYPE == pst_frame_header->st_frame_control.bit_type
        && WLAN_QOS_DATA == pst_frame_header->st_frame_control.bit_sub_type)
    {
        if (OAL_TRUE == pst_tx_ctl->en_use_4_addr)                /* ????4???? */
        {
            pst_qos_addr4_headder = (mac_ieee80211_qos_frame_addr4_stru *)pst_frame_header;

            uc_tid = pst_qos_addr4_headder->bit_qc_tid;
        }
        else
        {
            pst_qos_header = (mac_ieee80211_qos_frame_stru *)pst_frame_header;

            uc_tid = pst_qos_header->bit_qc_tid;
        }
    }

    /* ???????? */
    *puc_tid = uc_tid;

}
#endif

#ifdef _PRE_WLAN_FEATURE_HS20

oal_void hmac_tx_set_qos_map(oal_netbuf_stru *pst_buf, oal_uint8 *puc_tid)
{
    mac_ether_header_stru  *pst_ether_header;
    mac_ip_header_stru     *pst_ip;
    oal_uint8               uc_dscp = 0;
    mac_tx_ctl_stru        *pst_tx_ctl;
    hmac_vap_stru          *pst_hmac_vap     = OAL_PTR_NULL;
    oal_uint8               uc_idx;

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_buf);
    pst_hmac_vap     = (hmac_vap_stru *)mac_res_get_hmac_vap(MAC_GET_CB_TX_VAP_INDEX(pst_tx_ctl));

    /* ???????????? */
    pst_ether_header = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);

    /* ?????????????? */
    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_ether_header))
    {
        OAM_ERROR_LOG0(0, OAM_SF_HS20,
                       "{hmac_tx_set_qos_map::The input parameter of QoS_Map_Configure_frame_with_QoSMap_Set_element is OAL_PTR_NULL.}");
        return;
    }

    /* ??IP TOS????????DSCP?????? */
    /*---------------------------------
      tos??????
      ---------------------------------
    |    bit7~bit2      | bit1~bit0 |
    |    DSCP??????     | ????      |
    ---------------------------------*/

    /* ????????????????????ip?? */
    pst_ip = (mac_ip_header_stru *)(pst_ether_header + 1);
    uc_dscp = pst_ip->uc_tos >> WLAN_DSCP_PRI_SHIFT;
    OAM_INFO_LOG2(0, OAM_SF_HS20, "{hmac_tx_set_qos_map::tos = %d, uc_dscp=%d.}", pst_ip->uc_tos, uc_dscp);

    if ((pst_hmac_vap->st_cfg_qos_map_param.uc_num_dscp_except > 0)
        &&(pst_hmac_vap->st_cfg_qos_map_param.uc_num_dscp_except <= MAX_DSCP_EXCEPT)
        && (pst_hmac_vap->st_cfg_qos_map_param.uc_valid))
    {
        for (uc_idx = 0; uc_idx < pst_hmac_vap->st_cfg_qos_map_param.uc_num_dscp_except; uc_idx++)
        {
            if (uc_dscp == pst_hmac_vap->st_cfg_qos_map_param.auc_dscp_exception[uc_idx])
            {
               *puc_tid  = pst_hmac_vap->st_cfg_qos_map_param.auc_dscp_exception_up[uc_idx];
                MAC_GET_CB_FRAME_TYPE(pst_tx_ctl) = WLAN_CB_FRAME_TYPE_DATA;
                MAC_GET_CB_FRAME_SUBTYPE(pst_tx_ctl) = MAC_DATA_HS20;
                MAC_GET_CB_IS_NEEDRETRY(pst_tx_ctl)   = OAL_TRUE;
                pst_hmac_vap->st_cfg_qos_map_param.uc_valid = 0;
                return;
            }
        }
    }

    for (uc_idx = 0; uc_idx < MAX_QOS_UP_RANGE; uc_idx++)
    {
        if ((uc_dscp < pst_hmac_vap->st_cfg_qos_map_param.auc_up_high[uc_idx])
            && (uc_dscp > pst_hmac_vap->st_cfg_qos_map_param.auc_up_low[uc_idx]))
        {
           *puc_tid  = uc_idx;
            MAC_GET_CB_FRAME_TYPE(pst_tx_ctl) = WLAN_CB_FRAME_TYPE_DATA;
            MAC_GET_CB_FRAME_SUBTYPE(pst_tx_ctl) = MAC_DATA_HS20;
            MAC_GET_CB_IS_NEEDRETRY(pst_tx_ctl)             = OAL_TRUE;
            pst_hmac_vap->st_cfg_qos_map_param.uc_valid = 0;
            return;
        }
        else
        {
            *puc_tid = 0;
        }
    }
    pst_hmac_vap->st_cfg_qos_map_param.uc_valid = 0;
    return;
}
#endif //_PRE_WLAN_FEATURE_HS20

#ifdef _PRE_WLAN_FEATURE_CLASSIFY

OAL_STATIC OAL_INLINE oal_void  hmac_tx_classify_lan_to_wlan(oal_netbuf_stru *pst_buf, oal_uint8 *puc_tid)
{
    mac_ether_header_stru  *pst_ether_header;
    mac_ip_header_stru     *pst_ip;
    oal_vlan_ethhdr_stru   *pst_vlan_ethhdr;
    oal_uint32              ul_ipv6_hdr;
    oal_uint32              ul_pri;
    oal_uint16              us_vlan_tci;
    oal_uint8               uc_tid = 0;
    oal_uint8               uc_dscp;
    mac_tx_ctl_stru        *pst_tx_ctl;
    hmac_vap_stru          *pst_hmac_vap     = OAL_PTR_NULL;
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    oal_uint8               uc_data_type;
#endif
#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    hmac_user_stru         *pst_hmac_user    = OAL_PTR_NULL;
#endif
#ifdef _PRE_WLAN_FEATURE_SCHEDULE
    mac_tcp_header_stru    *pst_tcp;
#endif
#if defined(_PRE_WLAN_FEATURE_MCAST) || defined(_PRE_WLAN_FEATURE_HERA_MCAST)
    hmac_m2u_stru          *pst_m2u;
#endif

    pst_tx_ctl     = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_buf);
    pst_hmac_vap   = (hmac_vap_stru *)mac_res_get_hmac_vap(MAC_GET_CB_TX_VAP_INDEX(pst_tx_ctl));
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_WARNING_LOG1(0,OAM_SF_TX,"{hmac_tx_classify_lan_to_wlan::mac_res_get_hmac_vap fail.vap_index[%u]}",MAC_GET_CB_TX_VAP_INDEX(pst_tx_ctl));
        return;
    }

#if defined(_PRE_WLAN_FEATURE_MCAST) || defined(_PRE_WLAN_FEATURE_HERA_MCAST)
    pst_m2u = (hmac_m2u_stru *)(pst_hmac_vap->pst_m2u);
    if ((pst_tx_ctl->bit_is_m2u_data) && (OAL_PTR_NULL != pst_m2u))
    {
        *puc_tid = pst_m2u->en_tid_num;
        return;
    }
#endif
#ifdef CONFIG_NF_CONNTRACK_MARK
    /*the king of game feature will mark packets
     *and we will use VI queue to send these packets.
     */
    if(PKTMARK(pst_buf) == VIP_APP_MARK) {
        *puc_tid = VIP_APP_VIQUE_TID;
        pst_tx_ctl->bit_is_needretry = OAL_TRUE;
        return;
    }
#endif

    /* ???????????? */
    pst_ether_header = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);

    switch (pst_ether_header->us_ether_type)
    {
        /*lint -e778*//* ????Info -- Constant expression evaluates to 0 in operation '&' */
        case OAL_HOST2NET_SHORT(ETHER_TYPE_IP):
            OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::ETHER_TYPE_IP.}");

        #ifdef _PRE_WLAN_FEATURE_HS20
            if (pst_hmac_vap->st_cfg_qos_map_param.uc_valid)
            {
                hmac_tx_set_qos_map(pst_buf, &uc_tid);
                *puc_tid = uc_tid;
                return;
            }
        #endif //_PRE_WLAN_FEATURE_HS20

            /* ??IP TOS?????????????? */
            /*----------------------------------------------------------------------
                tos??????
             ----------------------------------------------------------------------
            | bit7~bit5 | bit4 |  bit3  |  bit2  |   bit1   | bit0 |
            | ????????  | ???? | ?????? | ?????? | ???????? | ???? |
             ----------------------------------------------------------------------*/
            pst_ip = (mac_ip_header_stru *)(pst_ether_header + 1);      /* ????????????????????ip?? */

            uc_dscp = pst_ip->uc_tos >> WLAN_DSCP_PRI_SHIFT;
            if (HMAC_DSCP_VALUE_INVALID != pst_hmac_vap->auc_dscp_tid_map[uc_dscp])
            {
                uc_tid = pst_hmac_vap->auc_dscp_tid_map[uc_dscp];
                break;
            }

            uc_tid  = pst_ip->uc_tos >> WLAN_IP_PRI_SHIFT;

        #ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
            if (OAL_SWITCH_ON == mac_mib_get_TxTrafficClassifyFlag(&pst_hmac_vap->st_vap_base_info))
            {
                if (0 != uc_tid)
                {
                    break;
                }
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
                /* RTP RTSP ???????? P2P???????????????? */
                if (!IS_LEGACY_VAP(&(pst_hmac_vap->st_vap_base_info)))
#endif
                {
                    hmac_tx_traffic_classify_etc(pst_tx_ctl, pst_ip, &uc_tid);
                }
            }
        #endif  /* _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN */

            OAM_INFO_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::tos = %d, uc_tid=%d.}", pst_ip->uc_tos, uc_tid);
            /* ??????DHCP??????????VO???????? */
            if (OAL_TRUE == mac_is_dhcp_port_etc(pst_ip))
            {
                uc_tid = WLAN_DATA_VIP_TID;
                MAC_GET_CB_FRAME_TYPE(pst_tx_ctl) = WLAN_CB_FRAME_TYPE_DATA;
                MAC_GET_CB_FRAME_SUBTYPE(pst_tx_ctl) = MAC_DATA_DHCP;
                MAC_GET_CB_IS_NEEDRETRY(pst_tx_ctl) = OAL_TRUE;
            }
#ifdef _PRE_WLAN_FEATURE_SCHEDULE
            /* ????chariot?????????????????????????????? */
            else if (MAC_TCP_PROTOCAL == pst_ip->uc_protocol)
            {
                pst_tcp = (mac_tcp_header_stru *)(pst_ip + 1);

                if ((OAL_NTOH_16(pst_tcp->us_dport) == MAC_CHARIOT_NETIF_PORT)
                        || (OAL_NTOH_16(pst_tcp->us_sport) == MAC_CHARIOT_NETIF_PORT))
                {
                    OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::chariot netif tcp pkt.}");
                    uc_tid = WLAN_DATA_VIP_TID;
                    MAC_GET_CB_FRAME_TYPE(pst_tx_ctl) = WLAN_CB_FRAME_TYPE_DATA;
                    MAC_GET_CB_FRAME_SUBTYPE(pst_tx_ctl) = MAC_DATA_CHARIOT_SIG;
                    MAC_GET_CB_IS_NEEDRETRY(pst_tx_ctl) = OAL_TRUE;
                }
            }
#endif

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
            pst_hmac_user    = (hmac_user_stru *)mac_res_get_hmac_user_etc(MAC_GET_CB_TX_USER_IDX(pst_tx_ctl));
            if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_user))
            {
                OAM_WARNING_LOG1(0, OAM_SF_CFG, "{hmac_edca_opt_rx_pkts_stat_etc::null param,pst_hmac_user[%d].}",MAC_GET_CB_TX_USER_IDX(pst_tx_ctl));
                break;
            }

            if ((OAL_TRUE == pst_hmac_vap->uc_edca_opt_flag_ap) && (WLAN_VAP_MODE_BSS_AP == pst_hmac_vap->st_vap_base_info.en_vap_mode))
            {
                /* mips????:??????????????????????10M???? */
                if (((MAC_UDP_PROTOCAL == pst_ip->uc_protocol) && (pst_hmac_user->aaul_txrx_data_stat[WLAN_WME_TID_TO_AC(uc_tid)][WLAN_TX_UDP_DATA] < (HMAC_EDCA_OPT_PKT_NUM + 10)))
                    || ((MAC_TCP_PROTOCAL == pst_ip->uc_protocol) && (pst_hmac_user->aaul_txrx_data_stat[WLAN_WME_TID_TO_AC(uc_tid)][WLAN_TX_TCP_DATA] < (HMAC_EDCA_OPT_PKT_NUM + 10))))
                {
                    hmac_edca_opt_tx_pkts_stat_etc(pst_tx_ctl, uc_tid, pst_ip);
                }
            }
#endif
            break;

        case OAL_HOST2NET_SHORT(ETHER_TYPE_IPV6):
            OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::ETHER_TYPE_IPV6.}");
            /* ??IPv6 traffic class?????????????? */
            /*----------------------------------------------------------------------
                IPv6???? ??32??????
             -----------------------------------------------------------------------
            | ?????? | traffic class   | ???????? |
            | 4bit   | 8bit(??ipv4 tos)|  20bit   |
            -----------------------------------------------------------------------*/
            ul_ipv6_hdr = *((oal_uint32 *)(pst_ether_header + 1));  /* ????????????????????ip?? */

            ul_pri = (OAL_NET2HOST_LONG(ul_ipv6_hdr) & WLAN_IPV6_PRIORITY_MASK) >> WLAN_IPV6_PRIORITY_SHIFT;

            uc_tid = (oal_uint8)(ul_pri >> WLAN_IP_PRI_SHIFT);
            OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::uc_tid=%d.}", uc_tid);

            /* ??????DHCPV6??????????VO???????? */
            if (OAL_TRUE == mac_is_dhcp6_etc((oal_ipv6hdr_stru *)(pst_ether_header + 1)))
            {
                OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::ETHER_TYPE_DHCP6.}");
                uc_tid = WLAN_DATA_VIP_TID;
                MAC_GET_CB_FRAME_TYPE(pst_tx_ctl) = WLAN_CB_FRAME_TYPE_DATA;
                MAC_GET_CB_FRAME_SUBTYPE(pst_tx_ctl) = MAC_DATA_DHCPV6;
                MAC_GET_CB_IS_NEEDRETRY(pst_tx_ctl) = OAL_TRUE;
            }

            break;

        case OAL_HOST2NET_SHORT(ETHER_TYPE_PAE):
            /* ??????EAPOL??????????VO???????? */
            OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::trace_eapol::ETHER_TYPE_PAE.}");
            uc_tid = WLAN_DATA_VIP_TID;
            MAC_GET_CB_FRAME_TYPE(pst_tx_ctl) = WLAN_CB_FRAME_TYPE_DATA;
            MAC_GET_CB_FRAME_SUBTYPE(pst_tx_ctl) = MAC_DATA_EAPOL;
            MAC_GET_CB_IS_NEEDRETRY(pst_tx_ctl) = OAL_TRUE;

            /* ??????4 ??????????????????????????tx cb ??bit_is_eapol_key_ptk ??????dmac ?????????? */
            if (OAL_TRUE == mac_is_eapol_key_ptk_etc((mac_eapol_header_stru *)(pst_ether_header + 1)))
            {
                MAC_GET_CB_IS_EAPOL_KEY_PTK(pst_tx_ctl) = OAL_TRUE;
            }

            OAM_WARNING_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CONN, "{hmac_tx_classify_lan_to_wlan:: EAPOL tx : uc_tid=%d,IS_EAPOL_KEY_PTK=%d.}", uc_tid, MAC_GET_CB_IS_EAPOL_KEY_PTK(pst_tx_ctl));

            break;

        /* TDLS????????????????????????????TID???? */
        case OAL_HOST2NET_SHORT(ETHER_TYPE_TDLS):
            OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::ETHER_TYPE_TDLS.}");
            uc_tid = WLAN_DATA_VIP_TID;
            OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::uc_tid=%d.}", uc_tid);
            break;

        /* PPPOE????????????????(????????, ????????)????????????TID???? */
        case OAL_HOST2NET_SHORT(ETHER_TYPE_PPP_DISC):
        case OAL_HOST2NET_SHORT(ETHER_TYPE_PPP_SES):
            OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::ETHER_TYPE_PPP_DISC, ETHER_TYPE_PPP_SES.}");
            uc_tid = WLAN_DATA_VIP_TID;
            MAC_GET_CB_FRAME_TYPE(pst_tx_ctl) = WLAN_CB_FRAME_TYPE_DATA;
            MAC_GET_CB_FRAME_SUBTYPE(pst_tx_ctl) = MAC_DATA_PPPOE;
            MAC_GET_CB_IS_NEEDRETRY(pst_tx_ctl) = OAL_TRUE;

            OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::uc_tid=%d.}", uc_tid);
            break;

#ifdef _PRE_WLAN_FEATURE_WAPI
        case OAL_HOST2NET_SHORT(ETHER_TYPE_WAI):
            OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::ETHER_TYPE_WAI.}");
            uc_tid = WLAN_DATA_VIP_TID;
            MAC_GET_CB_FRAME_TYPE(pst_tx_ctl) = WLAN_CB_FRAME_TYPE_DATA;
            MAC_GET_CB_FRAME_SUBTYPE(pst_tx_ctl) = MAC_DATA_WAPI;
            MAC_GET_CB_IS_NEEDRETRY(pst_tx_ctl) = OAL_TRUE;
            break;
#endif

        case OAL_HOST2NET_SHORT(ETHER_TYPE_VLAN):
            OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::ETHER_TYPE_VLAN.}");
            /* ????vlan tag???????? */
            pst_vlan_ethhdr = (oal_vlan_ethhdr_stru *)oal_netbuf_data(pst_buf);

            /*------------------------------------------------------------------
                802.1Q(VLAN) TCI(tag control information)??????
             -------------------------------------------------------------------
            |Priority | DEI  | Vlan Identifier |
            | 3bit    | 1bit |      12bit      |
             ------------------------------------------------------------------*/
            us_vlan_tci = OAL_NET2HOST_SHORT(pst_vlan_ethhdr->h_vlan_TCI);

            uc_tid = us_vlan_tci >> OAL_VLAN_PRIO_SHIFT;    /* ????13??????????3???????? */
            OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::uc_tid=%d.}", uc_tid);

            break;

#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
        case OAL_HOST2NET_SHORT(ETHER_TYPE_ARP):
            uc_tid = WLAN_DATA_VIP_TID;
            MAC_GET_CB_FRAME_TYPE(pst_tx_ctl) = WLAN_CB_FRAME_TYPE_DATA;
            uc_data_type = mac_get_data_type_from_8023_etc((oal_uint8 *)oal_netbuf_payload(pst_buf), MAC_NETBUFF_PAYLOAD_ETH);
            MAC_GET_CB_FRAME_SUBTYPE(pst_tx_ctl) = uc_data_type;
            MAC_GET_CB_IS_NEEDRETRY(pst_tx_ctl) = OAL_TRUE;
            break;
#endif

        /*lint +e778*/
        default:
            OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::default us_ether_type[%d].}", pst_ether_header->us_ether_type);
            break;
    }

    /* ???????? */
    *puc_tid = uc_tid;
}


OAL_STATIC OAL_INLINE oal_void hmac_tx_update_tid(oal_bool_enum_uint8  en_wmm, oal_uint8 *puc_tid)
{

    if (OAL_LIKELY(OAL_TRUE == en_wmm)) /*wmm????*/
    {
        *puc_tid = (*puc_tid < WLAN_TIDNO_BUTT) ? WLAN_TOS_TO_TID(*puc_tid): WLAN_TIDNO_BCAST;
    }
    else   /*wmm??????*/
    {
        *puc_tid = MAC_WMM_SWITCH_TID;
    }
}


oal_uint8 hmac_tx_wmm_acm_etc(oal_bool_enum_uint8  en_wmm, hmac_vap_stru *pst_hmac_vap, oal_uint8 *puc_tid)
{
#if defined(_PRE_PRODUCT_ID_HI110X_HOST)
    oal_uint8                   uc_ac;

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == puc_tid))
    {
        return OAL_FALSE;
    }

    if (OAL_FALSE == en_wmm)
    {
        return OAL_FALSE;
    }

    uc_ac = WLAN_WME_TID_TO_AC(*puc_tid);
    g_uc_ac_new = uc_ac;
    while ((g_uc_ac_new != WLAN_WME_AC_BK) && (OAL_TRUE == mac_mib_get_QAPEDCATableMandatory(&pst_hmac_vap->st_vap_base_info, g_uc_ac_new)))
    {
        switch (g_uc_ac_new)
        {
            case WLAN_WME_AC_VO:
                g_uc_ac_new = WLAN_WME_AC_VI;
                break;

            case WLAN_WME_AC_VI:
                g_uc_ac_new = WLAN_WME_AC_BE;
                break;

            default:
                g_uc_ac_new = WLAN_WME_AC_BK;
                break;
        }
    }

    if (g_uc_ac_new != uc_ac)
    {
        *puc_tid = WLAN_WME_AC_TO_TID(g_uc_ac_new);
    }
#endif /* defined(_PRE_PRODUCT_ID_HI110X_HOST) */

    return OAL_TRUE;
}


 OAL_STATIC OAL_INLINE oal_void  hmac_tx_classify(
                hmac_vap_stru   *pst_hmac_vap,
                mac_user_stru   *pst_user,
                oal_netbuf_stru *pst_buf)
{
    oal_uint8               uc_tid = 0;
    mac_tx_ctl_stru        *pst_tx_ctl;
    mac_device_stru        *pst_mac_dev = OAL_PTR_NULL;

    /* ??qos????????????EAPOL???????????? */
    hmac_tx_classify_lan_to_wlan(pst_buf, &uc_tid);

    /* ??QoS?????????????? */
    if (OAL_UNLIKELY(OAL_TRUE != pst_user->st_cap_info.bit_qos))
    {
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_classify::user is a none QoS station.}");
        return;
    }

    pst_mac_dev = mac_res_get_dev_etc(pst_user->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_classify::pst_mac_dev null.}");
        return;
    }

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_buf);

#if defined(_PRE_PRODUCT_ID_HI110X_HOST) && defined(_PRE_WLAN_FEATURE_WMMAC)
    if (g_en_wmmac_switch_etc)
    {
        oal_uint8  uc_ac_num;
        uc_ac_num = WLAN_WME_TID_TO_AC(uc_tid);
        /* ????ACM????1????????AC??TS????????????????????AC??????????????BE???????? */
        if((OAL_TRUE == mac_mib_get_QAPEDCATableMandatory(&(pst_hmac_vap->st_vap_base_info), uc_ac_num))
           && (MAC_TS_SUCCESS != pst_user->st_ts_info[uc_ac_num].en_ts_status) && (MAC_GET_CB_IS_VIPFRAME(pst_tx_ctl) == OAL_FALSE))
        {
            uc_tid = WLAN_WME_AC_BE;
        }
    }
    else
#endif //#if defined(_PRE_PRODUCT_ID_HI110X_HOST) && defined(_PRE_WLAN_FEATURE_WMMAC)
    {
        hmac_tx_wmm_acm_etc(pst_mac_dev->en_wmm, pst_hmac_vap, &uc_tid);

        
        /* 1102????????????????4??tid:0 1 5 6 */
        if ((!MAC_GET_CB_IS_VIPFRAME(pst_tx_ctl)) || (OAL_FALSE == pst_mac_dev->en_wmm))
        {
            hmac_tx_update_tid(pst_mac_dev->en_wmm, &uc_tid);
        }
    }

    /* ??????????vap????????????????????vap?????? */
    if (OAL_TRUE == pst_mac_dev->en_vap_classify)
    {
        uc_tid = mac_mib_get_VAPClassifyTidNo(&pst_hmac_vap->st_vap_base_info);
    }

    /* ????ap??????WMM??????????????BE ????*/
    if (!pst_hmac_vap->st_vap_base_info.en_vap_wmm)
    {
        uc_tid = WLAN_TIDNO_BEST_EFFORT;
    }

    /* ????ac??tid??cb???? */
    MAC_GET_CB_WME_TID_TYPE(pst_tx_ctl)  = uc_tid;
    MAC_GET_CB_WME_AC_TYPE(pst_tx_ctl)   = WLAN_WME_TID_TO_AC(uc_tid);

    return;
}
#endif


oal_void hmac_rx_dyn_bypass_extlna_switch(oal_uint32 ul_tx_throughput_mbps, oal_uint32 ul_rx_throughput_mbps)
{
    mac_device_stru  *pst_mac_device;
    mac_vap_stru     *pst_mac_vap;
    oal_uint32      ul_limit_throughput_high;
    oal_uint32      ul_limit_throughput_low;
    oal_uint32      ul_throughput_mbps = OAL_MAX(ul_tx_throughput_mbps, ul_rx_throughput_mbps);
    oal_uint32      ul_ret;
    oal_bool_enum_uint8   en_is_pm_test;

    /* ????????????????????????bypass????LNA */
    if (OAL_FALSE == g_st_rx_dyn_bypass_extlna_switch.uc_ini_en)
    {
        return;
    }

    /* ?????????????? */
    if ((0 != g_st_rx_dyn_bypass_extlna_switch.us_throughput_high) && (0 != g_st_rx_dyn_bypass_extlna_switch.us_throughput_low))
    {
        ul_limit_throughput_high = g_st_rx_dyn_bypass_extlna_switch.us_throughput_high;
        ul_limit_throughput_low  = g_st_rx_dyn_bypass_extlna_switch.us_throughput_low;
    }
    else
    {
        ul_limit_throughput_high = WLAN_DYN_BYPASS_EXTLNA_THROUGHPUT_THRESHOLD_HIGH;
        ul_limit_throughput_low  = WLAN_DYN_BYPASS_EXTLNA_THROUGHPUT_THRESHOLD_LOW;
    }
    if (ul_throughput_mbps > ul_limit_throughput_high)
    {
        /* ????100M,???????????????? */
        en_is_pm_test = OAL_FALSE;
    }
    else if (ul_throughput_mbps < ul_limit_throughput_low)
    {
        /* ????50M,?????????????? */
        en_is_pm_test = OAL_TRUE;
    }
    else
    {
        /* ????50M-100M????,???????? */
        return;
    }

    /* ??????????????????????????device???? */
    pst_mac_device = mac_res_get_dev_etc(0);

    /* ????????VAP,???????? */
    if (1 != mac_device_calc_up_vap_num_etc(pst_mac_device))
    {
        return;
    }

    ul_ret = mac_device_find_up_vap_etc(pst_mac_device, &pst_mac_vap);
    if ((OAL_SUCC != ul_ret) || (OAL_PTR_NULL == pst_mac_vap))
    {
        return;
    }

    /* ????????????,?????? */
    if (g_st_rx_dyn_bypass_extlna_switch.uc_cur_status == en_is_pm_test)
    {
        return;
    }

    ul_ret = hmac_config_send_event_etc(pst_mac_vap, WLAN_CFGID_DYN_EXTLNA_BYPASS_SWITCH, OAL_SIZEOF(oal_uint8), (oal_uint8 *)(&en_is_pm_test));
    if (OAL_SUCC == ul_ret)
    {
        g_st_rx_dyn_bypass_extlna_switch.uc_cur_status = en_is_pm_test;
    }

    OAM_WARNING_LOG4(0,OAM_SF_ANY,"{hmac_rx_dyn_bypass_extlna_switch: limit_high[%d],limit_low[%d],throughput[%d], uc_cur_status[%d](0:not pm, 1:pm))!}",
        ul_limit_throughput_high,ul_limit_throughput_low, ul_throughput_mbps, en_is_pm_test);
}

#ifdef _PRE_WLAN_FEATURE_MULTI_NETBUF_AMSDU

oal_void hmac_tx_amsdu_ampdu_switch(oal_uint32 ul_tx_throughput_mbps)
{
    mac_device_stru      *pst_mac_device;
    oal_uint32            ul_limit_throughput_high;
    oal_uint32            ul_limit_throughput_low;
    oal_bool_enum_uint8   en_large_amsdu_ampdu;
    /* ???????????????????????? */
    if (OAL_FALSE == g_st_tx_large_amsdu.uc_host_large_amsdu_en)
    {
        return;
    }

    /* ?????????????? */
    if ((0 != g_st_tx_large_amsdu.us_amsdu_throughput_high) && (0 != g_st_tx_large_amsdu.us_amsdu_throughput_low))
    {
        ul_limit_throughput_high = g_st_tx_large_amsdu.us_amsdu_throughput_high;
        ul_limit_throughput_low  = g_st_tx_large_amsdu.us_amsdu_throughput_low;
    }
    else
    {
        ul_limit_throughput_high = WLAN_AMPDU_THROUGHPUT_THRESHOLD_HIGH;
        ul_limit_throughput_low  = WLAN_AMPDU_THROUGHPUT_THRESHOLD_LOW;
    }
    if (ul_tx_throughput_mbps > ul_limit_throughput_high)
    {
        /* ????300M,????amsdu???????? */
        en_large_amsdu_ampdu = OAL_TRUE;
    }
    else if (ul_tx_throughput_mbps < ul_limit_throughput_low)
    {
        /* ????200M,????amsdu???????? */
        en_large_amsdu_ampdu = OAL_FALSE;
    }
    else
    {
        /* ????200M-300M????,???????? */
        return;
    }
    /* ????????????????,?????? */
    if (g_st_tx_large_amsdu.uc_cur_amsdu_enable == en_large_amsdu_ampdu)
    {
        return;
    }

    /* ??????amsdu??????????,???????????????????????? */
    if (OAL_TRUE == en_large_amsdu_ampdu)
    {
        pst_mac_device = mac_res_get_dev_etc(0);
        /* ????????VAP,????????tx amsdu???????? */
        if (1 != mac_device_calc_up_vap_num_etc(pst_mac_device))
        {
            return;
        }

    }
    g_st_tx_large_amsdu.uc_cur_amsdu_enable = en_large_amsdu_ampdu;

    OAM_WARNING_LOG3(0,OAM_SF_ANY,"{hmac_tx_amsdu_ampdu_switch: limit_high = [%d],limit_low = [%d],tx_throught= [%d]!}",
          ul_limit_throughput_high,ul_limit_throughput_low, ul_tx_throughput_mbps);
}
#endif
#ifdef _PRE_WLAN_TCP_OPT

oal_void hmac_tcp_ack_filter_switch(oal_uint32 ul_rx_throughput_mbps)
{
    mac_device_stru      *pst_mac_device;
    hmac_device_stru     *pst_hmac_device;
    mac_vap_stru         *pst_mac_vap;
    oal_uint32            ul_limit_throughput_high;
    oal_uint32            ul_limit_throughput_low;
    oal_uint32            ul_ret;
    oal_bool_enum_uint8   en_tcp_ack_filter;
    /* ????????????????tcp ack???????????? */
    if (OAL_FALSE == g_st_tcp_ack_filter.uc_tcp_ack_filter_en)
    {
        return;
    }

    /* ?????????????? */
    if ((0 != g_st_tcp_ack_filter.us_rx_filter_throughput_high) && (0 != g_st_tcp_ack_filter.us_rx_filter_throughput_low))
    {
        ul_limit_throughput_high = g_st_tcp_ack_filter.us_rx_filter_throughput_high;
        ul_limit_throughput_low  = g_st_tcp_ack_filter.us_rx_filter_throughput_low;
    }
    else
    {
        ul_limit_throughput_high = WLAN_TCP_ACK_FILTER_THROUGHPUT_TH_HIGH;
        ul_limit_throughput_low  = WLAN_TCP_ACK_FILTER_THROUGHPUT_TH_LOW;
    }
    if (ul_rx_throughput_mbps > ul_limit_throughput_high)
    {
        /* ????60M, ????tcp ack???? */
        en_tcp_ack_filter = OAL_TRUE;
    }
    else if (ul_rx_throughput_mbps < ul_limit_throughput_low)
    {
        /* ????20M,????tcp ack???? */
        en_tcp_ack_filter = OAL_FALSE;
    }
    else
    {
        /* ????20M-60M????,???????? */
        return;
    }
    if (g_st_tcp_ack_filter.uc_cur_filter_status == en_tcp_ack_filter)
    {
        return;
    }

    pst_mac_device = mac_res_get_dev_etc(0);
    /* ????????VAP,???????? */
    if (1 != mac_device_calc_up_vap_num_etc(pst_mac_device))
    {
        return;
    }

    ul_ret = mac_device_find_up_vap_etc(pst_mac_device, &pst_mac_vap);
    if ((OAL_SUCC != ul_ret) || (OAL_PTR_NULL == pst_mac_vap))
    {
        return;
    }
    pst_hmac_device = hmac_res_get_mac_dev_etc(pst_mac_device->uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        return;
    }
    pst_hmac_device->sys_tcp_tx_ack_opt_enable = en_tcp_ack_filter;
    g_st_tcp_ack_filter.uc_cur_filter_status = en_tcp_ack_filter;

    OAM_WARNING_LOG3(0,OAM_SF_ANY,"{hmac_tcp_ack_filter_switch: limit_high = [%d],limit_low = [%d],rx_throught= [%d]!}",
          ul_limit_throughput_high,ul_limit_throughput_low, ul_rx_throughput_mbps);

}
#endif

oal_void  hmac_tx_small_amsdu_switch(oal_uint32 ul_rx_throughput_mbps,oal_uint32 ul_tx_pps)
{
    mac_device_stru  *pst_mac_device;
    mac_vap_stru     *pst_mac_vap = OAL_PTR_NULL;
    mac_cfg_ampdu_tx_on_param_stru   st_ampdu_tx_on = {0};
    oal_uint32      ul_limit_throughput_high;
    oal_uint32      ul_limit_throughput_low;
    oal_uint32      ul_limit_pps_high;
    oal_uint32      ul_limit_pps_low;
    oal_uint32      ul_ret;
    oal_bool_enum_uint8   en_small_amsdu;

    /* ???????????????????????? */
    if (OAL_FALSE ==  g_st_small_amsdu_switch.uc_ini_small_amsdu_en)
    {
        return;
    }

    /* ?????????????? */
    if ((0 != g_st_small_amsdu_switch.us_small_amsdu_throughput_high) && (0 != g_st_small_amsdu_switch.us_small_amsdu_throughput_low))
    {
        ul_limit_throughput_high = g_st_small_amsdu_switch.us_small_amsdu_throughput_high;
        ul_limit_throughput_low  = g_st_small_amsdu_switch.us_small_amsdu_throughput_low;
    }
    else
    {
        ul_limit_throughput_high = WLAN_SMALL_AMSDU_THROUGHPUT_THRESHOLD_HIGH;
        ul_limit_throughput_low  = WLAN_SMALL_AMSDU_THROUGHPUT_THRESHOLD_LOW;
    }
    /* ????PPS???? */
    if ((0 != g_st_small_amsdu_switch.us_small_amsdu_pps_high) && (0 != g_st_small_amsdu_switch.us_small_amsdu_pps_low))
    {
        ul_limit_pps_high = g_st_small_amsdu_switch.us_small_amsdu_pps_high;
        ul_limit_pps_low  = g_st_small_amsdu_switch.us_small_amsdu_pps_low;
    }
    else
    {
        ul_limit_pps_high = WLAN_SMALL_AMSDU_PPS_THRESHOLD_HIGH;
        ul_limit_pps_low  = WLAN_SMALL_AMSDU_PPS_THRESHOLD_LOW;
    }

    if ((ul_rx_throughput_mbps > ul_limit_throughput_high) || (ul_tx_pps > ul_limit_pps_high))
    {
        /* rx??????????300M????tx pps????25000,????????amsdu???? */
        en_small_amsdu = OAL_TRUE;
    }
    else if ((ul_rx_throughput_mbps < ul_limit_throughput_low) && (ul_tx_pps < ul_limit_pps_low))
    {
        /* rx??????????200M??tx pps????15000,????????amsdu?????????????????? */
        en_small_amsdu = OAL_FALSE;
    }
    else
    {
        /* ????200M-300M????,???????? */
        return;
    }


     /* ????????????????,?????? */
    if (g_st_small_amsdu_switch.uc_cur_small_amsdu_en == en_small_amsdu)
    {
        return;
    }

    pst_mac_device = mac_res_get_dev_etc(0);
    /* ????????VAP,???????? */
    if (1 != mac_device_calc_up_vap_num_etc(pst_mac_device))
    {
        return;
    }

    ul_ret = mac_device_find_up_vap_etc(pst_mac_device, &pst_mac_vap);
    if ((OAL_SUCC != ul_ret) || (OAL_PTR_NULL == pst_mac_vap))
    {
        return;
    }
#if 0
    /* VHT/HE?????????? */
    if ((WLAN_VHT_MODE != pst_mac_vap->en_protocol) &&
        (WLAN_VHT_ONLY_MODE != pst_mac_vap->en_protocol)
#ifdef _PRE_WLAN_FEATURE_11AX
         &&(WLAN_HE_MODE != pst_mac_vap->en_protocol)
#endif
        )
    {
        return;
    }

    /* 80M?????????????????? */
    if (WLAN_BAND_WIDTH_80PLUSPLUS > pst_mac_vap->st_channel.en_bandwidth)
    {
        return;
    }
#endif

    OAM_WARNING_LOG3(0,OAM_SF_ANY,"{hmac_tx_small_amsdu_switch: limit_high = [%d],limit_low = [%d],rx_throught= [%d]!}",
          ul_limit_throughput_high,ul_limit_throughput_low, ul_rx_throughput_mbps);
    OAM_WARNING_LOG3(0,OAM_SF_ANY,"{hmac_tx_small_amsdu_switch: PPS limit_high = [%d],PPS limit_low = [%d],tx_pps = %d!}",
      ul_limit_pps_high,ul_limit_pps_low,ul_tx_pps);

    st_ampdu_tx_on.uc_aggr_tx_on = en_small_amsdu;

    g_st_small_amsdu_switch.uc_cur_small_amsdu_en = en_small_amsdu;

    hmac_config_set_amsdu_tx_on_etc(pst_mac_vap, OAL_SIZEOF(mac_cfg_ampdu_tx_on_param_stru), (oal_uint8*)&st_ampdu_tx_on);
}


#ifdef _PRE_WLAN_FEATURE_TCP_ACK_BUFFER

oal_void  hmac_tx_tcp_ack_buf_switch(oal_uint32 ul_rx_throughput_mbps)
{
    mac_device_stru  *pst_mac_device;
    mac_vap_stru     *pst_mac_vap = OAL_PTR_NULL;
    mac_cfg_tcp_ack_buf_stru       st_tcp_ack_param = {0};
    oal_uint32      ul_limit_throughput_high = 550;
    oal_uint32      ul_limit_throughput_low = 450;
    oal_uint32      ul_ret;
    oal_bool_enum_uint8   en_tcp_ack_buf = OAL_FALSE;

    /* ?????????????????????????????????? */
    if (OAL_FALSE ==  g_st_tcp_ack_buf_switch.uc_ini_tcp_ack_buf_en)
    {
        return;
    }

    pst_mac_device = mac_res_get_dev_etc(0);
    /* ????????VAP,???????? */
    if (1 != mac_device_calc_up_vap_num_etc(pst_mac_device))
    {
        return;
    }
    ul_ret = mac_device_find_up_vap_etc(pst_mac_device, &pst_mac_vap);
    if ((OAL_SUCC != ul_ret) || (OAL_PTR_NULL == pst_mac_vap))
    {
        return;
    }
    if (pst_mac_vap->st_channel.en_bandwidth == WLAN_BAND_WIDTH_20M)
    {
        /* ?????????????? */
        if ((0 != g_st_tcp_ack_buf_switch.us_tcp_ack_buf_throughput_high) && (0 != g_st_tcp_ack_buf_switch.us_tcp_ack_buf_throughput_low))
        {
            ul_limit_throughput_high = g_st_tcp_ack_buf_switch.us_tcp_ack_buf_throughput_high;
            ul_limit_throughput_low  = g_st_tcp_ack_buf_switch.us_tcp_ack_buf_throughput_low;
        }
        else
        {
            ul_limit_throughput_high = WLAN_TCP_ACK_BUF_THROUGHPUT_THRESHOLD_HIGH;
            ul_limit_throughput_low  = WLAN_TCP_ACK_BUF_THROUGHPUT_THRESHOLD_LOW;
        }
    }
    else if ((pst_mac_vap->st_channel.en_bandwidth == WLAN_BAND_WIDTH_40PLUS)
            || (pst_mac_vap->st_channel.en_bandwidth == WLAN_BAND_WIDTH_40MINUS))
    {
        /* ?????????????? */
        if ((0 != g_st_tcp_ack_buf_switch.us_tcp_ack_buf_throughput_high_40M) && (0 != g_st_tcp_ack_buf_switch.us_tcp_ack_buf_throughput_low_40M))
        {
            ul_limit_throughput_high = g_st_tcp_ack_buf_switch.us_tcp_ack_buf_throughput_high_40M;
            ul_limit_throughput_low  = g_st_tcp_ack_buf_switch.us_tcp_ack_buf_throughput_low_40M;
        }
        else
        {
            ul_limit_throughput_high = WLAN_TCP_ACK_BUF_THROUGHPUT_THRESHOLD_HIGH_40M;
            ul_limit_throughput_low  = WLAN_TCP_ACK_BUF_THROUGHPUT_THRESHOLD_LOW_40M;
        }
    }
    else if ((pst_mac_vap->st_channel.en_bandwidth >= WLAN_BAND_WIDTH_80PLUSPLUS)
            && (pst_mac_vap->st_channel.en_bandwidth <= WLAN_BAND_WIDTH_80MINUSMINUS))
    {
        /* ?????????????? */
        if ((0 != g_st_tcp_ack_buf_switch.us_tcp_ack_buf_throughput_high_80M) && (0 != g_st_tcp_ack_buf_switch.us_tcp_ack_buf_throughput_low_80M))
        {
            ul_limit_throughput_high = g_st_tcp_ack_buf_switch.us_tcp_ack_buf_throughput_high_80M;
            ul_limit_throughput_low  = g_st_tcp_ack_buf_switch.us_tcp_ack_buf_throughput_low_80M;
        }
        else
        {
            ul_limit_throughput_high = WLAN_TCP_ACK_BUF_THROUGHPUT_THRESHOLD_HIGH_80M;
            ul_limit_throughput_low  = WLAN_TCP_ACK_BUF_THROUGHPUT_THRESHOLD_LOW_80M;
        }
    }
#ifdef _PRE_WLAN_FEATURE_160M
    else if ((pst_mac_vap->st_channel.en_bandwidth >= WLAN_BAND_WIDTH_160PLUSPLUSPLUS)
            && (pst_mac_vap->st_channel.en_bandwidth <= WLAN_BAND_WIDTH_160MINUSMINUSMINUS))
    {
        /* ?????????????? */
        if ((0 != g_st_tcp_ack_buf_switch.us_tcp_ack_buf_throughput_high_160M) && (0 != g_st_tcp_ack_buf_switch.us_tcp_ack_buf_throughput_low_160M))
        {
            ul_limit_throughput_high = g_st_tcp_ack_buf_switch.us_tcp_ack_buf_throughput_high_160M;
            ul_limit_throughput_low  = g_st_tcp_ack_buf_switch.us_tcp_ack_buf_throughput_low_160M;
        }
        else
        {
            ul_limit_throughput_high = WLAN_TCP_ACK_BUF_THROUGHPUT_THRESHOLD_HIGH_160M;
            ul_limit_throughput_low  = WLAN_TCP_ACK_BUF_THROUGHPUT_THRESHOLD_LOW_160M;
        }
    }
#endif
    else
    {
        return;
    }

    g_st_tcp_ack_buf_switch.us_tcp_ack_smooth_throughput >>= 1;
    g_st_tcp_ack_buf_switch.us_tcp_ack_smooth_throughput += (ul_rx_throughput_mbps >> 1);
    if (g_st_tcp_ack_buf_switch.us_tcp_ack_smooth_throughput > ul_limit_throughput_high)
    {
        /* ??????????,????tcp ack buf*/
        en_tcp_ack_buf = OAL_TRUE;
    }
    else if (g_st_tcp_ack_buf_switch.us_tcp_ack_smooth_throughput < ul_limit_throughput_low)
    {
        /* ??????????,????tcp ack buf */
        en_tcp_ack_buf = OAL_FALSE;
    }
    else
    {
        /* ?????????????????? ???????? */
        return;
    }

     /* ?????????? ,?????? */
    if (g_st_tcp_ack_buf_switch.uc_cur_tcp_ack_buf_en == en_tcp_ack_buf)
    {
        return;
    }

    OAM_WARNING_LOG4(0,OAM_SF_ANY,"{hmac_tx_tcp_ack_buf_switch: limit_high = [%d],limit_low = [%d],rx_throught= [%d]! en_tcp_ack_buf=%d}",
          ul_limit_throughput_high,ul_limit_throughput_low, ul_rx_throughput_mbps, en_tcp_ack_buf);

    g_st_tcp_ack_buf_switch.uc_cur_tcp_ack_buf_en = en_tcp_ack_buf;


    st_tcp_ack_param.en_cmd = MAC_TCP_ACK_BUF_ENABLE;
    st_tcp_ack_param.en_enable = en_tcp_ack_buf;

    hmac_config_tcp_ack_buf(pst_mac_vap, OAL_SIZEOF(mac_cfg_tcp_ack_buf_stru), (oal_uint8*)&st_tcp_ack_param);


}
#endif

#ifdef _PRE_WLAN_FEATURE_AMPDU_TX_HW

oal_void  hmac_tx_ampdu_switch(oal_uint32 ul_tx_throughput_mbps)
{
    mac_device_stru                 *pst_mac_device;
    mac_vap_stru                    *pst_mac_vap;
    mac_cfg_ampdu_tx_on_param_stru   st_ampdu_tx_on = {0};
    oal_uint32                       ul_limit_throughput_high = 0;
    oal_uint32                       ul_limit_throughput_low = 0;
    oal_uint32                       ul_ret;
    oal_bool_enum_uint8              en_ampdu_hw;
    hmac_user_stru                   *pst_hmac_user;
    /* ???????????????????????? */
    if (OAL_FALSE == g_st_ampdu_hw.uc_ampdu_hw_en)
    {
        return;
    }
    /* ?????????????? */
    if ((0 != g_st_ampdu_hw.us_throughput_high) && (0 != g_st_ampdu_hw.us_throughput_low))
    {
        ul_limit_throughput_high = g_st_ampdu_hw.us_throughput_high;
        ul_limit_throughput_low  = g_st_ampdu_hw.us_throughput_low;
    }
    else
    {
        ul_limit_throughput_high = WLAN_AMPDU_THROUGHPUT_THRESHOLD_HIGH;
        ul_limit_throughput_low  = WLAN_AMPDU_THROUGHPUT_THRESHOLD_LOW;
    }

    pst_mac_device = mac_res_get_dev_etc(0);
    /* ????????VAP,???????????????? */
    if (1 != mac_device_calc_up_vap_num_etc(pst_mac_device))
    {
        en_ampdu_hw = OAL_FALSE;
    }
    else
    {
        if (ul_tx_throughput_mbps > ul_limit_throughput_high)
        {
            /* ????300M,???????????? */
            en_ampdu_hw = OAL_TRUE;
        }
        else if (ul_tx_throughput_mbps < ul_limit_throughput_low)
        {
            /* ????200M,???????????? */
            en_ampdu_hw = OAL_FALSE;
        }
        else
        {
            /* ????200M-300M????,???????? */
            return;
        }

    }

    /* ????????????????,?????? */
    if (g_st_ampdu_hw.uc_ampdu_hw_enable == en_ampdu_hw)
    {
        return;
    }

    /* ????????????????,???????????????????????? */
    if (OAL_TRUE == en_ampdu_hw)
    {
        g_st_ampdu_hw.us_remain_hw_cnt = 0;

        ul_ret = mac_device_find_up_vap_etc(pst_mac_device, &pst_mac_vap);
        if ((OAL_SUCC != ul_ret) || (OAL_PTR_NULL == pst_mac_vap))
        {
            return;
        }

        /* VHT/HE?????????? */
        if ((WLAN_VHT_MODE != pst_mac_vap->en_protocol) &&
            (WLAN_VHT_ONLY_MODE != pst_mac_vap->en_protocol)
#ifdef _PRE_WLAN_FEATURE_11AX
             &&(WLAN_HE_MODE != pst_mac_vap->en_protocol)
#endif
            )
        {
            return;
        }

        /* 80M?????????????????? */
        if (WLAN_BAND_WIDTH_80PLUSPLUS > pst_mac_vap->st_channel.en_bandwidth)
        {
            return;
        }
        /* ????????AP?????????????????? */
        if(IS_LEGACY_STA(pst_mac_vap))
        {
            pst_hmac_user = mac_res_get_hmac_user_etc(pst_mac_vap->us_assoc_vap_id);
            if (OAL_PTR_NULL == pst_hmac_user)
            {
                OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_M2S, "hmac_tx_ampdu_switch: pst_hmac_user is null ptr.");
                return;
            }
            if(pst_hmac_user->en_user_ap_type & MAC_AP_TYPE_AGGR_BLACKLIST)
            {
                return;
            }

        }
    }
    else
    {
        /* ????????????????,??????????????????????,??????????????????????,
           ?????????????????????????????????? */
        /* ????vap,???????? */
        if (1 == mac_device_calc_up_vap_num_etc(pst_mac_device))
        {
            g_st_ampdu_hw.us_remain_hw_cnt++;
            if (WLAN_AMPDU_HW_SWITCH_PERIOD > g_st_ampdu_hw.us_remain_hw_cnt)
            {
                return;
            }
            g_st_ampdu_hw.us_remain_hw_cnt = 0;
        }
        pst_mac_vap = mac_res_get_mac_vap(0);
        if (OAL_PTR_NULL == pst_mac_vap)
        {
            return;
        }
    }

    g_st_ampdu_hw.uc_ampdu_hw_enable = en_ampdu_hw;

    OAM_WARNING_LOG3(0,OAM_SF_ANY,"{hmac_tx_ampdu_switch: limit_high = [%d],limit_low = [%d],tx_throught= [%d]!}",
          ul_limit_throughput_high,ul_limit_throughput_low, ul_tx_throughput_mbps);

    if (OAL_TRUE == en_ampdu_hw)
    {
        st_ampdu_tx_on.uc_aggr_tx_on = 4;
    }
    else
    {
        st_ampdu_tx_on.uc_aggr_tx_on = 8;
    }

    st_ampdu_tx_on.uc_snd_type = 1;
    st_ampdu_tx_on.en_aggr_switch_mode = AMPDU_SWITCH_BY_BA_LUT;
    hmac_config_set_ampdu_tx_on_etc(pst_mac_vap, OAL_SIZEOF(mac_cfg_ampdu_tx_on_param_stru), (oal_uint8*)&st_ampdu_tx_on);
}
#endif


OAL_STATIC OAL_INLINE oal_uint32 hmac_tx_filter_security(hmac_vap_stru     *pst_hmac_vap,
                                        oal_netbuf_stru  *pst_buf,
                                        hmac_user_stru   *pst_hmac_user)
{
    mac_ether_header_stru   *pst_ether_header = OAL_PTR_NULL;
    mac_user_stru           *pst_mac_user     = OAL_PTR_NULL;
    mac_vap_stru            *pst_mac_vap      = OAL_PTR_NULL;
    oal_uint32               ul_ret           = OAL_SUCC;
    oal_uint16               us_ether_type;

    pst_mac_vap  = &(pst_hmac_vap->st_vap_base_info);
    pst_mac_user = &(pst_hmac_user->st_user_base_info);

    if (OAL_TRUE == mac_mib_get_rsnaactivated(pst_mac_vap))/* ????????????WPA/WPA2 */
    {
        if (pst_mac_user->en_port_valid != OAL_TRUE)/* ???????????????? */
        {
            /* ???????????? */
            pst_ether_header = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);
            /* ??????????????????EAPOL ?????????????? */

            if (oal_byteorder_host_to_net_uint16(ETHER_TYPE_PAE) != pst_ether_header->us_ether_type)
            {
                us_ether_type = oal_byteorder_host_to_net_uint16(pst_ether_header->us_ether_type);
                OAM_WARNING_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_filter_security::TYPE 0x%04x, 0x%04x.}",
                               us_ether_type, ETHER_TYPE_PAE);
                ul_ret = OAL_FAIL;
            }
        }
    }


    return ul_ret;

}


oal_void  hmac_tx_ba_setup_etc(
                hmac_vap_stru    *pst_hmac_vap,
                hmac_user_stru   *pst_user,
                oal_uint8         uc_tidno)
{
    mac_action_mgmt_args_stru   st_action_args;   /* ????????ACTION???????? */

    /*
    ????BA????????st_action_args????????????????????
    (1)uc_category:action??????
    (2)uc_action:BA action????????
    (3)ul_arg1:BA??????????TID
    (4)ul_arg2:BUFFER SIZE????
    (5)ul_arg3:BA??????????????
    (6)ul_arg4:TIMEOUT????
    */
    st_action_args.uc_category = MAC_ACTION_CATEGORY_BA;
    st_action_args.uc_action   = MAC_BA_ACTION_ADDBA_REQ;
    st_action_args.ul_arg1     = uc_tidno;                     /* ??????????????TID?? */
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    st_action_args.ul_arg2     = (oal_uint32)g_st_wlan_customize_etc.ul_ampdu_tx_max_num;       /* ADDBA_REQ????buffer_size?????????? */
    OAM_WARNING_LOG1(0, OAM_SF_TX, "hmac_tx_ba_setup_etc::[ba buffer size:%d]", st_action_args.ul_arg2);
#else
    st_action_args.ul_arg2     = WLAN_AMPDU_TX_MAX_BUF_SIZE;       /* ADDBA_REQ????buffer_size?????????? */
#endif

    st_action_args.ul_arg3     = MAC_BA_POLICY_IMMEDIATE;     /* BA?????????????? */
    st_action_args.ul_arg4     = 0;                            /* BA????????????????????0 */

    /* ????BA???? */
    hmac_mgmt_tx_action_etc(pst_hmac_vap, pst_user, &st_action_args);
}


oal_uint32 hmac_tx_ucast_process_etc(
                hmac_vap_stru     *pst_hmac_vap,
                oal_netbuf_stru   *pst_buf,
                hmac_user_stru    *pst_user,
                mac_tx_ctl_stru   *pst_tx_ctl)
{
    oal_uint32         ul_ret = HMAC_TX_PASS;
#ifdef _PRE_WLAN_FEATURE_CAR
    hmac_device_stru     *pst_hmac_dev;
#endif
#ifdef _PRE_WLAN_FEATURE_QOS_ENHANCE
       mac_qos_enhance_sta_stru    *pst_qos_enhance_hash = OAL_PTR_NULL;
       oal_uint8                    uc_old_tid;
       oal_uint8                    uc_new_tid;
#endif


   /*????????*/
#if defined(_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)
    if (OAL_UNLIKELY(OAL_SUCC != hmac_tx_filter_security(pst_hmac_vap, pst_buf, pst_user)))
    {
        OAM_STAT_VAP_INCR(pst_hmac_vap->st_vap_base_info.uc_vap_id, tx_security_check_faild, 1);
        return HMAC_TX_DROP_SECURITY_FILTER;
    }
#endif

    /*??????????????*/
#ifdef _PRE_WLAN_FEATURE_CLASSIFY
    hmac_tx_classify(pst_hmac_vap, &(pst_user->st_user_base_info), pst_buf);
#endif

#ifdef _PRE_WLAN_FEATURE_QOS_ENHANCE
    /* ????ap??????WMM??????qos_enhance???? */
    if ((OAL_TRUE == pst_hmac_vap->st_vap_base_info.en_vap_wmm) && (WLAN_VAP_MODE_BSS_AP == pst_hmac_vap->st_vap_base_info.en_vap_mode) && (OAL_TRUE == pst_hmac_vap->st_vap_base_info.st_qos_enhance.en_qos_enhance_enable))
    {
        if (pst_hmac_vap->st_vap_base_info.st_qos_enhance.uc_qos_enhance_sta_count > 0)
        {
            uc_old_tid = MAC_GET_CB_WME_TID_TYPE(pst_tx_ctl);
            uc_new_tid = uc_old_tid;
            pst_qos_enhance_hash = mac_tx_find_qos_enhance_list(&(pst_hmac_vap->st_vap_base_info), pst_user->st_user_base_info.auc_user_mac_addr);

            if (OAL_PTR_NULL != pst_qos_enhance_hash && pst_qos_enhance_hash->uc_add_num >= MAC_QOS_ENHANCE_ADD_NUM)
            {
                if (uc_old_tid == WLAN_TIDNO_BEST_EFFORT || uc_old_tid == WLAN_TIDNO_BACKGROUND || uc_old_tid == WLAN_TIDNO_VIDEO)
                {
                    uc_new_tid = WLAN_TIDNO_VOICE;
                }
            }
            else
            {
                /* ???????? */
                if( MAC_USER_QOS_ENHANCE_NEAR == pst_user->st_user_base_info.en_qos_enhance_sta_state)
                {
                    uc_new_tid = WLAN_TIDNO_VIDEO;
                }
                /* ???????? */
                else if (MAC_USER_QOS_ENHANCE_FAR == pst_user->st_user_base_info.en_qos_enhance_sta_state)
                {
                    uc_new_tid = WLAN_TIDNO_BEST_EFFORT;
                }
            }

            if (uc_old_tid != uc_new_tid)
            {
                /* ????ac??tid??cb???? */
                MAC_GET_CB_WME_TID_TYPE(pst_tx_ctl)  = uc_new_tid;
                MAC_GET_CB_WME_AC_TYPE(pst_tx_ctl)   = WLAN_WME_TID_TO_AC(uc_new_tid);
            }
        }
    }
#endif

#ifdef _PRE_WLAN_FEATURE_TRAFFIC_CTL
    /* TBD */
#endif

    OAL_MIPS_TX_STATISTIC(HMAC_PROFILING_FUNC_TRAFFIC_CLASSIFY);
    OAM_PROFILING_TX_STATISTIC(OAL_PTR_NULL, OAM_PROFILING_FUNC_TRAFFIC_CLASSIFY);

    /* ??????EAPOL??DHCP????????????????????BA???? */
    if (MAC_GET_CB_IS_VIPFRAME(pst_tx_ctl))
    {
        return HMAC_TX_PASS;
    }

#ifdef _PRE_WLAN_FEATURE_AMPDU
    if (OAL_TRUE == hmac_tid_need_ba_session(pst_hmac_vap, pst_user, MAC_GET_CB_WME_TID_TYPE(pst_tx_ctl), pst_buf))
    {
        /* ????????????BA??????????AMPDU??????????????DMAC??????????addba rsp???????????? */
        hmac_tx_ba_setup_etc(pst_hmac_vap, pst_user, MAC_GET_CB_WME_TID_TYPE(pst_tx_ctl));
    }
#endif

    OAL_MIPS_TX_STATISTIC(HMAC_PROFILING_FUNC_SETUP_BA);
    OAM_PROFILING_TX_STATISTIC(OAL_PTR_NULL, OAM_PROFILING_FUNC_SETUP_BA);

#ifdef _PRE_WLAN_FEATURE_CAR
    /* ??????car???????????? */
    pst_hmac_dev = hmac_res_get_mac_dev_etc(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if(OAL_TRUE == pst_hmac_dev->en_car_enable_flag)
    {
        ul_ret = hmac_car_process(pst_hmac_dev, pst_hmac_vap, pst_user, pst_buf, HMAC_CAR_DOWNLINK);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, 0, "hmac_tx_ucast_process_etc:hmac_car_process: downlink car: DROP PACKET! ul_ret[%d]", ul_ret);
            return HMAC_TX_DROP_CAR_LIMIT;
        }
    }
#endif

#ifdef _PRE_WLAN_FEATURE_AMSDU
    ul_ret = hmac_amsdu_notify_etc(pst_hmac_vap, pst_user, pst_buf);
    if (OAL_UNLIKELY(HMAC_TX_PASS != ul_ret))
    {
        return ul_ret;
    }
#endif
    OAL_MIPS_TX_STATISTIC(HMAC_PROFILING_FUNC_AMSDU);

    return HMAC_TX_PASS;
}


OAL_STATIC oal_uint32 hmac_tx_need_frag(hmac_vap_stru *pst_hmac_vap, hmac_user_stru *pst_hmac_user, oal_netbuf_stru *pst_netbuf, mac_tx_ctl_stru *pst_tx_ctl)
{
    oal_uint32        ul_threshold;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    oal_uint32        uc_last_frag;
#endif
    /* ???????????????????????? */
    /* 1??????????????          */
    /* 2????legac????????       */
    /* 3????????????            */
    /* 4????????????            */
    /* 6??DHCP????????????      */

    if (MAC_GET_CB_IS_VIPFRAME(pst_tx_ctl))
    {
        return OAL_FALSE;
    }

    ul_threshold = mac_mib_get_FragmentationThreshold(&pst_hmac_vap->st_vap_base_info);
    ul_threshold = (ul_threshold & (~(BIT0|BIT1))) + 2;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    /* ????1151????bug,??????????????TKIP????????????????????????payload????????????8???????????????? */
    if (WLAN_80211_CIPHER_SUITE_TKIP == pst_hmac_user->st_user_base_info.st_key_info.en_cipher_type)
    {
        uc_last_frag = (OAL_NETBUF_LEN(pst_netbuf) + 8) % (ul_threshold - MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl) - (WEP_IV_FIELD_SIZE + EXT_IV_FIELD_SIZE));
        if ((uc_last_frag > 0) && (uc_last_frag <= 8))
        {
            ul_threshold = ul_threshold + 8;
        }
    }
#endif
    if(((OAL_NETBUF_LEN(pst_netbuf) + MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl)) > ul_threshold)
                     && (OAL_FALSE == MAC_GET_CB_IS_MCAST(pst_tx_ctl))
                     && (OAL_FALSE == MAC_GET_CB_IS_AMSDU(pst_tx_ctl))
                #ifdef _PRE_WLAN_FEATURE_MULTI_NETBUF_AMSDU
                     && (OAL_FALSE == MAC_GET_CB_HAS_EHTER_HEAD(pst_tx_ctl))
                #endif
                     && (pst_hmac_user->st_user_base_info.en_cur_protocol_mode < WLAN_HT_MODE || pst_hmac_vap->st_vap_base_info.en_protocol < WLAN_HT_MODE)
                     &&(OAL_FALSE == hmac_tid_ba_is_setup(pst_hmac_user, MAC_GET_CB_WME_TID_TYPE(pst_tx_ctl))))
    {
        return ul_threshold;
    }

    return 0;
}



/*lint -e695*/
oal_uint32  hmac_tx_encap_etc(hmac_vap_stru *pst_vap, hmac_user_stru *pst_user, oal_netbuf_stru *pst_buf)/*lint !e695*/
{
    oal_uint8                                *puc_80211_hdr;           /* 802.11?? */
    //mac_ether_header_stru                    *pst_ether_hdr;
    oal_uint32                                ul_qos = HMAC_TX_BSS_NOQOS;
    mac_tx_ctl_stru                          *pst_tx_ctl;
    //oal_uint16                                us_ether_type = 0;
    oal_uint32                                ul_ret = OAL_SUCC;
    oal_uint32                                ul_threshold    = 0;
    mac_ieee80211_frame_stru                 *pst_head;
    oal_uint8                                 uc_buf_is_amsdu = OAL_FALSE;
    oal_uint8                                 uc_ic_header    = 0;
    oal_uint16                                us_mpdu_len = 0;
    mac_ether_header_stru                     st_ether_hdr;
#ifdef _PRE_DEBUG_MODE
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_buf)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_TX, "{hmac_tx_encap_etc::param null,%d %d.}", pst_vap, pst_buf);
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif

    /* ????CB */
    pst_tx_ctl = (mac_tx_ctl_stru *)(oal_netbuf_cb(pst_buf));
    uc_buf_is_amsdu = MAC_GET_CB_IS_AMSDU(pst_tx_ctl);

#if defined _PRE_WLAN_FEATURE_WDS || defined _PRE_WLAN_FEATURE_VIRTUAL_MULTI_STA
    if ((WDS_MODE_REPEATER_STA == pst_vap->st_wds_table.en_wds_vap_mode)
        ||((WDS_MODE_ROOTAP == pst_vap->st_wds_table.en_wds_vap_mode) && (OAL_TRUE == pst_user->uc_is_wds)))
    {
        MAC_GET_CB_IS_4ADDRESS(pst_tx_ctl) = OAL_TRUE;
    }
#endif

    /* ????????????, ????????????????, ?????????? */
    //pst_ether_hdr = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);
    oal_memcopy(&st_ether_hdr, oal_netbuf_data(pst_buf), ETHER_HDR_LEN);


    /*??amsdu??*/
    if (OAL_TRUE == uc_buf_is_amsdu)
    {
        st_ether_hdr.us_ether_type = 0;
    }
    else
    {
        /* len = EHTER HEAD LEN + PAYLOAD LEN */
        us_mpdu_len = (oal_uint16)oal_netbuf_get_len(pst_buf);

        /* ????frame??????????skb payload--LLC HEAD */
        MAC_GET_CB_MPDU_LEN(pst_tx_ctl) = (us_mpdu_len - ETHER_HDR_LEN + SNAP_LLC_FRAME_LEN);

        pst_tx_ctl->bit_align_padding_offset = 0;

#ifdef _PRE_WLAN_FEATURE_MULTI_NETBUF_AMSDU
        hmac_tx_encap_large_skb_amsdu(pst_vap, pst_user, pst_buf, pst_tx_ctl);

        if (MAC_GET_CB_HAS_EHTER_HEAD(pst_tx_ctl))
        {
            /* ????data??????ETHER HEAD - LLC HEAD */
            oal_netbuf_pull(pst_buf, SNAP_LLC_FRAME_LEN);
        }
#endif
        /* ????LLC HEAD */
        mac_set_snap(pst_buf, st_ether_hdr.us_ether_type);

#ifdef _PRE_WLAN_FEATURE_MULTI_NETBUF_AMSDU
        if (MAC_GET_CB_HAS_EHTER_HEAD(pst_tx_ctl))
        {
            /* ????data??????ETHER HEAD */
            oal_netbuf_push(pst_buf, ETHER_HDR_LEN);

            /* ????4bytes???? */
            if((oal_uint)oal_netbuf_data(pst_buf) != OAL_ROUND_DOWN((oal_uint)oal_netbuf_data(pst_buf), 4))
            {
                pst_tx_ctl->bit_align_padding_offset = (oal_uint)oal_netbuf_data(pst_buf)- OAL_ROUND_DOWN((oal_uint)oal_netbuf_data(pst_buf), 4);
                oal_netbuf_push(pst_buf, pst_tx_ctl->bit_align_padding_offset);
            }
        }
#endif
    }



    /*????skb??data????????????????????802.11 mac head len??????????????????????????802.11??*/
    if (oal_netbuf_headroom(pst_buf) >=  MAC_80211_QOS_HTC_4ADDR_FRAME_LEN)
    {
        puc_80211_hdr = (OAL_NETBUF_HEADER(pst_buf)- MAC_80211_QOS_HTC_4ADDR_FRAME_LEN);

        MAC_GET_CB_80211_MAC_HEAD_TYPE(pst_tx_ctl) = 1;  /*????mac??????skb??*/
    }
    else
    {
        /* ??????????80211?? */
        puc_80211_hdr = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_SHARED_DATA_PKT, MAC_80211_QOS_HTC_4ADDR_FRAME_LEN, OAL_FALSE);
        if (OAL_UNLIKELY(OAL_PTR_NULL == puc_80211_hdr))
        {
            OAM_ERROR_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_encap_etc::pst_hdr null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }

        MAC_GET_CB_80211_MAC_HEAD_TYPE(pst_tx_ctl) = 0;  /*????mac????????skb????????????????????????*/
    }

    /* ????????????????????QOS?????????? */
    if (OAL_FALSE == MAC_GET_CB_IS_MCAST(pst_tx_ctl))
    {
        /* ????????????????cap_info????????????QOS???? */
        ul_qos = pst_user->st_user_base_info.st_cap_info.bit_qos;
        MAC_SET_CB_IS_QOS_DATA(pst_tx_ctl, ul_qos);
    }

    /* ?????????? */
    hmac_tx_set_frame_ctrl(ul_qos, pst_tx_ctl, (mac_ieee80211_qos_htc_frame_addr4_stru *)puc_80211_hdr);

    /* ???????? */
    hmac_tx_set_addresses(pst_vap, pst_user, pst_tx_ctl, &st_ether_hdr, (mac_ieee80211_qos_htc_frame_addr4_stru *)puc_80211_hdr);

    /* ????802.11?? */
    pst_head = (mac_ieee80211_frame_stru *)puc_80211_hdr;
    MAC_GET_CB_FRAME_HEADER_ADDR(pst_tx_ctl) = pst_head;

    /* ???????? */
    ul_threshold = hmac_tx_need_frag(pst_vap, pst_user, pst_buf, pst_tx_ctl);
    if (0 != ul_threshold)
    {
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
        pst_head->bit_seq_num = (us_noqos_frag_seqnum++) & 0x0fff;
        MAC_GET_CB_SEQ_CTRL_BYPASS(pst_tx_ctl) = OAL_TRUE;
#endif
        /* TBD??????????????????TKIP????MSDU???????????????????? */
        ul_ret = hmac_en_mic_etc(pst_vap, pst_user, pst_buf, &uc_ic_header);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_tx_encap_etc::hmac_en_mic_etc failed[%d].}", ul_ret);
            return ul_ret;
        }

        /* ???????????? */
        ul_ret = hmac_frag_process(pst_vap, pst_buf, pst_tx_ctl, (oal_uint32)uc_ic_header, ul_threshold);
    }

#ifdef _PRE_WLAN_FEATURE_SNIFFER
	proc_sniffer_write_file((const oal_uint8*)pst_head, MAC_80211_QOS_FRAME_LEN,
	                      (const oal_uint8 *)oal_netbuf_data(pst_buf), OAL_NETBUF_LEN(pst_buf), 1);
#endif

    return ul_ret;
}
/*lint +e695*/


OAL_STATIC oal_uint32  hmac_tx_lan_mpdu_process_sta(
                hmac_vap_stru      *pst_vap,
                oal_netbuf_stru    *pst_buf,
                mac_tx_ctl_stru    *pst_tx_ctl)
{
    hmac_user_stru          *pst_user;      /* ????STA?????? */
    mac_ether_header_stru   *pst_ether_hdr; /* ???????? */
    oal_uint32              ul_ret;
    oal_uint16              us_user_idx;
    oal_uint8               *puc_ether_payload;

    pst_ether_hdr  = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);
    MAC_GET_CB_TX_VAP_INDEX(pst_tx_ctl) = pst_vap->st_vap_base_info.uc_vap_id;

    us_user_idx = pst_vap->st_vap_base_info.us_assoc_vap_id;

    pst_user = (hmac_user_stru *)mac_res_get_hmac_user_etc(us_user_idx);
    if (OAL_PTR_NULL == pst_user)
    {
        OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);
        return HMAC_TX_DROP_USER_NULL;
    }
#if defined (_PRE_WLAN_FEATURE_WDS) || defined (_PRE_WLAN_FEATURE_VIRTUAL_MULTI_STA)
    if (WDS_MODE_REPEATER_STA == pst_vap->st_wds_table.en_wds_vap_mode)
    {
        hmac_wds_update_neigh(pst_vap, pst_ether_hdr->auc_ether_shost);
    }
    else if ((WDS_MODE_NONE == pst_vap->st_wds_table.en_wds_vap_mode)
        && (oal_byteorder_host_to_net_uint16(ETHER_TYPE_ARP) == pst_ether_hdr->us_ether_type))
#else
    if (oal_byteorder_host_to_net_uint16(ETHER_TYPE_ARP) == pst_ether_hdr->us_ether_type)
#endif
    {
        pst_ether_hdr++;
        puc_ether_payload = (oal_uint8 *)pst_ether_hdr;
        /* The source MAC address is modified only if the packet is an   */
        /* ARP Request or a Response. The appropriate bytes are checked. */
        /* Type field (2 bytes): ARP Request (1) or an ARP Response (2)  */
        if((puc_ether_payload[6] == 0x00) &&
          (puc_ether_payload[7] == 0x02 || puc_ether_payload[7] == 0x01))
        {
            /* Set Address2 field in the WLAN Header with source address */
            oal_set_mac_addr(puc_ether_payload + 8, mac_mib_get_StationID(&pst_vap->st_vap_base_info));
        }
    }

    MAC_GET_CB_TX_USER_IDX(pst_tx_ctl) = us_user_idx;

    ul_ret = hmac_tx_ucast_process_etc(pst_vap, pst_buf, pst_user, pst_tx_ctl);
    if (OAL_UNLIKELY(HMAC_TX_PASS != ul_ret))
    {
        return ul_ret;
    }

    /* ????802.11?? */
    ul_ret = hmac_tx_encap_etc(pst_vap, pst_user, pst_buf);
    if (OAL_UNLIKELY((OAL_SUCC != ul_ret) ))
    {
        OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_mpdu_process_sta::hmac_tx_encap_etc failed[%d].}", ul_ret);
        OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);
        return HMAC_TX_DROP_80211_ENCAP_FAIL;
    }

    OAL_MIPS_TX_STATISTIC(HMAC_PROFILING_FUNC_ENCAP_HEAD);
    return HMAC_TX_PASS;
}

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP

OAL_STATIC OAL_INLINE oal_bool_enum_uint8  hmac_tx_proxyarp_is_en(hmac_vap_stru *pst_vap)
{

   return (oal_bool_enum_uint8)((OAL_PTR_NULL != pst_vap->st_vap_base_info.pst_vap_proxyarp)
           && (OAL_TRUE == pst_vap->st_vap_base_info.pst_vap_proxyarp->en_is_proxyarp));

}
#endif
#if (_PRE_TARGET_PRODUCT_TYPE_5630HERA == _PRE_CONFIG_TARGET_PRODUCT)

OAL_STATIC oal_bool_enum_uint8 hmac_tx_netbuf_is_hilink_mulicast(oal_netbuf_stru *pst_buf)
{
    mac_ether_header_stru                *pst_ether_header;
    mac_ip_header_stru                   *puc_ip_hdr;
    oal_uint32                            ul_grp_addr;

    pst_ether_header  = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);

    /* Hera HILINK????????IP????:239.126.x.x,239.118.x.x,239.10.x.x,
        239.20.x.x,239.30.x.x,239.40.x.x */
    if (OAL_HOST2NET_SHORT(ETHER_TYPE_IP) == pst_ether_header->us_ether_type)
    {
        puc_ip_hdr  = (mac_ip_header_stru *)(pst_ether_header + 1);
        ul_grp_addr = OAL_HOST2NET_LONG(puc_ip_hdr->ul_daddr);

        if ((ul_grp_addr == 0xeeeeeeee)
        || ((ul_grp_addr & 0xffff0000)>>16 == 0xef7e)
        || ((ul_grp_addr & 0xffff0000)>>16 == 0xef76)
        || ((ul_grp_addr & 0xffff0000)>>16 == 0xef0a)
        || ((ul_grp_addr & 0xffff0000)>>16 == 0xef14)
        || ((ul_grp_addr & 0xffff0000)>>16 == 0xef1e)
        || ((ul_grp_addr & 0xffff0000)>>16 == 0xef28))
        {
            return OAL_TRUE;
        }
    }
    return OAL_FALSE;

}
#endif


OAL_STATIC OAL_INLINE oal_uint32  hmac_tx_lan_mpdu_process_ap(
                hmac_vap_stru      *pst_vap,
                oal_netbuf_stru    *pst_buf,
                mac_tx_ctl_stru    *pst_tx_ctl)
{
    hmac_user_stru          *pst_user;      /* ????STA?????? */
    mac_ether_header_stru   *pst_ether_hdr; /* ???????? */
    oal_uint8               *puc_addr;      /* ???????? */
    oal_uint32               ul_ret;
    oal_uint16               us_user_idx = MAC_INVALID_USER_ID;
#ifdef _PRE_WLAN_FEATURE_CAR
    hmac_device_stru        *pst_hmac_dev;
#endif
#if defined (_PRE_WLAN_FEATURE_WDS) || defined (_PRE_WLAN_FEATURE_VIRTUAL_MULTI_STA)
    oal_uint8               *src_addr;      /* ?????? */
#endif

    /* ????????????????,????lan to wlan???????????????????????? */
    pst_ether_hdr   = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);
    puc_addr        = pst_ether_hdr->auc_ether_dhost;
#if defined (_PRE_WLAN_FEATURE_WDS) || defined (_PRE_WLAN_FEATURE_VIRTUAL_MULTI_STA)
    src_addr        = pst_ether_hdr->auc_ether_shost;
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
    /*????proxy arp ????????*/
    if (OAL_TRUE == hmac_tx_proxyarp_is_en(pst_vap))
    {
        if(OAL_TRUE == hmac_proxy_arp_proc(pst_vap, pst_buf))
        {
            return HMAC_TX_DROP_PROXY_ARP;
        }
    }
#endif

    /*??????????*/
#ifdef _PRE_WLAN_CHIP_TEST
    if (OAL_LIKELY(!ETHER_IS_MULTICAST(puc_addr)) && pst_vap->st_vap_base_info.bit_al_tx_flag != OAL_SWITCH_ON)
#else
    if (OAL_LIKELY(!ETHER_IS_MULTICAST(puc_addr)))
#endif
    {
        ul_ret = mac_vap_find_user_by_macaddr_etc(&(pst_vap->st_vap_base_info), puc_addr, &us_user_idx);
#if defined (_PRE_WLAN_FEATURE_WDS) || defined (_PRE_WLAN_FEATURE_VIRTUAL_MULTI_STA)
        if (OAL_SUCC != ul_ret)
        {
            ul_ret = hmac_find_valid_user_by_wds_sta(pst_vap, puc_addr, &us_user_idx);
        }
#endif

        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_WARNING_LOG4(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                             "{hmac_tx_lan_mpdu_process_ap::hmac_tx_find_user failed %2x:%2x:%2x:%2x}", puc_addr[2], puc_addr[3], puc_addr[4], puc_addr[5]);
            OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);
            return HMAC_TX_DROP_USER_UNKNOWN;
        }

        /* ????HMAC??USER?????? */
        pst_user = (hmac_user_stru *)mac_res_get_hmac_user_etc(us_user_idx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_user))
        {
            OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);
            return HMAC_TX_DROP_USER_NULL;
        }

        /* ???????????? */
        if (OAL_UNLIKELY(MAC_USER_STATE_ASSOC != pst_user->st_user_base_info.en_user_asoc_state))
        {
             OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);
             return HMAC_TX_DROP_USER_INACTIVE;
        }

        /* ????user???? */
        MAC_GET_CB_TX_USER_IDX(pst_tx_ctl) = us_user_idx;

        ul_ret = hmac_tx_ucast_process_etc(pst_vap, pst_buf, pst_user, pst_tx_ctl);
        if (OAL_UNLIKELY(HMAC_TX_PASS != ul_ret))
        {
            return ul_ret;
        }
    }
    else /* ???? or ???? */
    {
        /* ?????????????? */
        MAC_GET_CB_IS_MCAST(pst_tx_ctl) = OAL_TRUE;

        /* ????ACK???? */
        MAC_GET_CB_ACK_POLACY(pst_tx_ctl) = WLAN_TX_NO_ACK;

        /* ???????????? */
        pst_user = mac_res_get_hmac_user_etc(pst_vap->st_vap_base_info.us_multi_user_idx);

        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_user))
        {
            OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                                 "{hmac_tx_lan_mpdu_process_ap::get multi user failed[%d].}", pst_vap->st_vap_base_info.us_multi_user_idx);
            OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);
            return HMAC_TX_DROP_MUSER_NULL;
        }

        MAC_GET_CB_TX_USER_IDX(pst_tx_ctl) = pst_vap->st_vap_base_info.us_multi_user_idx;
        MAC_GET_CB_WME_TID_TYPE(pst_tx_ctl)  = WLAN_TIDNO_BCAST;
        MAC_GET_CB_WME_AC_TYPE(pst_tx_ctl)   = WLAN_WME_TID_TO_AC(WLAN_TIDNO_BCAST);

        #if defined(_PRE_WLAN_FEATURE_MCAST) || defined(_PRE_WLAN_FEATURE_HERA_MCAST) /* ?????????? */
            if ((!ETHER_IS_BROADCAST(puc_addr)) && (OAL_PTR_NULL != pst_vap->pst_m2u))
            {
                if ((ETHER_IS_IPV4_MULTICAST(puc_addr)) ||(ETHER_IS_IPV6_MULTICAST(puc_addr)))
                {
                    ul_ret = hmac_m2u_snoop_convert(pst_vap, pst_buf);
                    if (ul_ret != HMAC_TX_PASS)
                    {
                        return ul_ret;
                    }
        #ifdef _PRE_WLAN_FEATURE_HERA_MCAST
                    else/* ???????????? */
                    {
                        /* ????STA???????? */
                        hmac_m2u_adaptive_inspecting(pst_vap, pst_buf);
                        ul_ret = hmac_m2u_multicast_drop(pst_vap, pst_buf);
                        if (ul_ret != HMAC_TX_PASS)
                        {
                            return ul_ret;
                        }
                     }
        #endif
                }
            }
        #endif

        #ifdef _PRE_WLAN_FEATURE_CAR
            /* ??????????car???????????? */
            pst_hmac_dev = hmac_res_get_mac_dev_etc(pst_vap->st_vap_base_info.uc_device_id);
            if((OAL_TRUE == pst_hmac_dev->en_car_enable_flag) && (WLAN_VAP_MODE_BSS_AP == pst_vap->st_vap_base_info.en_vap_mode))
            {
                ul_ret = hmac_car_multicast_process(pst_hmac_dev, pst_buf);
                if (OAL_SUCC != ul_ret)
                {
                    OAM_WARNING_LOG1(0, 0, "hmac_tx_lan_mpdu_process_ap: device downlink car multicast : DROP PACKET! ul_ret[%d]", ul_ret);
                    return HMAC_TX_DROP_CAR_LIMIT;
                }
            }
        #endif

        #if defined (_PRE_WLAN_FEATURE_WDS) || defined (_PRE_WLAN_FEATURE_VIRTUAL_MULTI_STA)
            if ((WDS_MODE_ROOTAP == pst_vap->st_wds_table.en_wds_vap_mode) && ETHER_IS_BROADCAST(puc_addr))
            {
                hmac_wds_node_ergodic(pst_vap, src_addr, hmac_wds_tx_broadcast_pkt, (void *)pst_buf);
            }
        #endif
    }

    /* ????802.11?? */
    ul_ret = hmac_tx_encap_etc(pst_vap, pst_user, pst_buf);
    if (OAL_UNLIKELY((OAL_SUCC != ul_ret) ))
    {
        OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                             "{hmac_tx_lan_mpdu_process_ap::hmac_tx_encap_etc failed[%d].}", ul_ret);
        OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);
        return HMAC_TX_DROP_80211_ENCAP_FAIL;
    }

    return HMAC_TX_PASS;
}


oal_void hmac_tx_lan_mpdu_info(mac_vap_stru *pst_vap, oal_uint8 uc_data_type, oal_netbuf_stru *pst_buf, mac_tx_ctl_stru *pst_tx_ctl)
{
#ifndef WIN32
    mac_eapol_type_enum_uint8 en_eapol_type = MAC_EAPOL_PTK_BUTT;
    oal_uint8  uc_dhcp_type;
    mac_ieee80211_qos_htc_frame_addr4_stru *pst_mac_header;
    mac_llc_snap_stru *pst_llc;
    oal_ip_header_stru   *pst_rx_ip_hdr;
    oal_eth_arphdr_stru  *puc_arp_head;

    oal_uint8  auc_ar_sip[ETH_SENDER_IP_ADDR_LEN];   /* sender IP address */
    oal_uint8  auc_ar_dip[ETH_SENDER_IP_ADDR_LEN];   /* sender IP address */

    /* ????skb????????80211?? */

    /* ????LLC SNAP */
    pst_llc = (mac_llc_snap_stru*)oal_netbuf_data(pst_buf);

    if (MAC_DATA_EAPOL == uc_data_type)
    {
        en_eapol_type = mac_get_eapol_key_type_etc((oal_uint8*)(pst_llc + 1));
        OAM_WARNING_LOG2(pst_vap->uc_vap_id, OAM_SF_ANY, "{hmac_tx_lan_mpdu_info::EAPOL type=%u, len==%u}[1:1/4 2:2/4 3:3/4 4:4/4]",
                en_eapol_type , OAL_NETBUF_LEN(pst_buf));
    }
    else if(MAC_DATA_DHCP == uc_data_type)
    {
        pst_rx_ip_hdr = (oal_ip_header_stru*)(pst_llc + 1);

        oal_memcopy((oal_uint8*)auc_ar_sip, (oal_uint8*)&pst_rx_ip_hdr->ul_saddr, OAL_SIZEOF(oal_uint32));
        oal_memcopy((oal_uint8*)auc_ar_dip, (oal_uint8*)&pst_rx_ip_hdr->ul_daddr, OAL_SIZEOF(oal_uint32));

        uc_dhcp_type = mac_get_dhcp_frame_type_etc(pst_rx_ip_hdr);
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{hmac_tx_lan_mpdu_info:: DHCP type=%d.[1:discovery 2:offer 3:request 4:decline 5:ack 6:nack 7:release 8:inform.]",
            uc_dhcp_type);
        OAM_WARNING_LOG4(pst_vap->uc_vap_id, OAM_SF_ANY, "{hmac_tx_lan_mpdu_info:: DHCP sip: %d.%d, dip: %d.%d.",
            auc_ar_sip[2],auc_ar_sip[3], auc_ar_dip[2], auc_ar_dip[3]);
    }
    else
    {
        puc_arp_head = (oal_eth_arphdr_stru*)(pst_llc + 1);
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{hmac_tx_lan_mpdu_info:: ARP type=%d.[2:arp resp 3:arp req.]",
            uc_data_type);
        OAM_WARNING_LOG4(pst_vap->uc_vap_id, OAM_SF_ANY, "{hmac_tx_lan_mpdu_info:: ARP sip: %d.%d, dip: %d.%d",
             puc_arp_head->auc_ar_sip[2],puc_arp_head->auc_ar_sip[3],
             puc_arp_head->auc_ar_tip[2],puc_arp_head->auc_ar_tip[3]);
    }

    pst_mac_header = (mac_ieee80211_qos_htc_frame_addr4_stru*)MAC_GET_CB_FRAME_HEADER_ADDR(pst_tx_ctl);
    if (OAL_PTR_NULL != pst_mac_header)
    {
        OAM_WARNING_LOG4(pst_vap->uc_vap_id, OAM_SF_ANY, "{hmac_tx_lan_mpdu_info::send to wlan smac: %x:%x, dmac: %x:%x]",
                pst_mac_header->auc_address2[4], pst_mac_header->auc_address2[5],
                pst_mac_header->auc_address1[4], pst_mac_header->auc_address1[5]);
    }
#endif
}


/*lint -e695*/
OAL_INLINE oal_uint32  hmac_tx_lan_to_wlan_no_tcp_opt_etc(mac_vap_stru *pst_vap, oal_netbuf_stru *pst_buf)
{
    frw_event_stru        *pst_event;        /* ?????????? */
    frw_event_mem_stru    *pst_event_mem;
    hmac_vap_stru         *pst_hmac_vap;     /* VAP?????? */
    mac_tx_ctl_stru       *pst_tx_ctl;       /* SKB CB */
    oal_uint32             ul_ret = HMAC_TX_PASS;
    dmac_tx_event_stru    *pst_dtx_stru;
    oal_uint8              uc_data_type;
#ifdef _PRE_WLAN_FEATURE_WAPI
    hmac_wapi_stru              *pst_wapi;
    mac_ieee80211_frame_stru    *pst_mac_hdr;
    oal_bool_enum_uint8          en_is_mcast = OAL_FALSE;
#endif

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_vap->uc_vap_id);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan_no_tcp_opt_etc::pst_hmac_vap null.}");
        OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, tx_abnormal_msdu_dropped, 1);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* VAP???????? */
    if (OAL_UNLIKELY(WLAN_VAP_MODE_BSS_AP != pst_vap->en_vap_mode && WLAN_VAP_MODE_BSS_STA != pst_vap->en_vap_mode))
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan_no_tcp_opt_etc::en_vap_mode=%d.}", pst_vap->en_vap_mode);
        OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, tx_abnormal_msdu_dropped, 1);
        return OAL_ERR_CODE_CONFIG_UNSUPPORT;
    }

    /* ??????????????????0???????????? */
    if (OAL_UNLIKELY(0 == pst_hmac_vap->st_vap_base_info.us_user_nums))
    {
#if (_PRE_TARGET_PRODUCT_TYPE_5630HERA == _PRE_CONFIG_TARGET_PRODUCT)
        if (OAL_FALSE == hmac_tx_netbuf_is_hilink_mulicast(pst_buf))
#endif
        {
            OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, tx_abnormal_msdu_dropped, 1);
            return OAL_FAIL;
        }
    }
    OAM_PROFILING_TX_STATISTIC(OAL_PTR_NULL, OAM_PROFILING_FUNC_NO_TCP_OPT);

    /* ??????????????????????????????????dev???????????????????????????????? */
    uc_data_type =  mac_get_data_type_from_8023_etc((oal_uint8 *)oal_netbuf_data(pst_buf), MAC_NETBUFF_PAYLOAD_ETH);
    /* ??????CB tx rx???? , CB?????????????????????? ????????????????????????????????*/
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_buf);
    MAC_GET_CB_MPDU_NUM(pst_tx_ctl)       = 1;
    MAC_GET_CB_NETBUF_NUM(pst_tx_ctl)     = 1;
    MAC_GET_CB_WLAN_FRAME_TYPE(pst_tx_ctl)     = WLAN_DATA_BASICTYPE;
    MAC_GET_CB_ACK_POLACY(pst_tx_ctl)     = WLAN_TX_NORMAL_ACK;
    MAC_GET_CB_TX_VAP_INDEX(pst_tx_ctl)   = pst_vap->uc_vap_id;
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctl)    = MAC_INVALID_USER_ID;
    MAC_GET_CB_WME_AC_TYPE(pst_tx_ctl)    = WLAN_WME_AC_BE;  /* ????????BE???? */
    MAC_GET_CB_FRAME_TYPE(pst_tx_ctl) = WLAN_CB_FRAME_TYPE_DATA;
    MAC_GET_CB_FRAME_SUBTYPE(pst_tx_ctl) = uc_data_type;

#ifdef _PRE_WLAN_FEATURE_SPECIAL_PKT_LOG
    hmac_parse_special_ipv4_packet(oal_netbuf_data(pst_buf),oal_netbuf_get_len(pst_buf), HMAC_PKT_DIRECTION_TX);
#endif

    /* ????LAN TO WLAN??WLAN TO WLAN??netbuf??????????????????????????????????
       ??????????????netbuf????????CB?????????????????? */
    if (FRW_EVENT_TYPE_WLAN_DTX != MAC_GET_CB_EVENT_TYPE(pst_tx_ctl))
    {
        MAC_GET_CB_EVENT_TYPE(pst_tx_ctl)             = FRW_EVENT_TYPE_HOST_DRX;
        MAC_GET_CB_EVENT_SUBTYPE(pst_tx_ctl)         = DMAC_TX_HOST_DRX;
    }

#if ((_PRE_TARGET_PRODUCT_TYPE_E5 == _PRE_CONFIG_TARGET_PRODUCT || _PRE_TARGET_PRODUCT_TYPE_CPE == _PRE_CONFIG_TARGET_PRODUCT)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION))
    if ((MAC_DATA_ARP_REQ == uc_data_type || MAC_DATA_ARP_RSP == uc_data_type) && (WLAN_VAP_MODE_BSS_AP == pst_vap->en_vap_mode))
    {
        if (OAL_TRUE == wlan_check_arp_spoofing((struct net_device*)(hmac_vap_get_net_device_etc(pst_vap->uc_vap_id)), (struct sk_buff*)pst_buf))
        {
            OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{hmac_tx_lan_to_wlan_no_tcp_opt_etc::ARP spoofing, type is %d", uc_data_type);
            oam_report_eth_frame_etc(pst_vap->auc_bssid,
                             oal_netbuf_data(pst_buf),
                             (oal_uint16)OAL_NETBUF_LEN(pst_buf),
                             OAM_OTA_FRAME_DIRECTION_TYPE_TX);
            return OAL_FAIL;
        }
    }
#endif

#ifdef _PRE_WLAN_PRODUCT_1151V200
    if (WLAN_BAND_5G == pst_vap->st_channel.en_band)
    {
        oal_notify_wlan_status(OAL_WIFI_BAND_5G, OAL_WIFI_TX);
    }
    else
    {
        oal_notify_wlan_status(OAL_WIFI_BAND_2G, OAL_WIFI_TX);
    }
#endif

    oal_spin_lock_bh(&pst_hmac_vap->st_lock_state);
    /* ????host???????????????????? */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    HMAC_TX_PKTS_STAT(1);
    hmac_auto_freq_wifi_tx_bytes_stat(OAL_NETBUF_LEN(pst_buf));
#endif

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    /*????????????????*/
    hmac_auto_freq_wifi_tx_stat(1);
#endif

    if (WLAN_VAP_MODE_BSS_AP == pst_hmac_vap->st_vap_base_info.en_vap_mode)
    {
        /*  ???????? MPDU */
        if( OAL_FALSE == mac_mib_get_dot11QosOptionImplemented(&pst_hmac_vap->st_vap_base_info))
        {
            MAC_GET_CB_WME_AC_TYPE(pst_tx_ctl)     = WLAN_WME_AC_VO;            /*AP???? ??WMM ??VO???? */
            MAC_GET_CB_WME_TID_TYPE(pst_tx_ctl) =  WLAN_WME_AC_TO_TID(MAC_GET_CB_WME_AC_TYPE(pst_tx_ctl));
        }

        ul_ret = hmac_tx_lan_mpdu_process_ap(pst_hmac_vap, pst_buf, pst_tx_ctl);
    }
    else if (WLAN_VAP_MODE_BSS_STA == pst_hmac_vap->st_vap_base_info.en_vap_mode)
    {
        /* ????????MPDU */
        MAC_GET_CB_WME_AC_TYPE(pst_tx_ctl)       = WLAN_WME_AC_VO;                  /* STA???? ??qos????VO???? */
        MAC_GET_CB_WME_TID_TYPE(pst_tx_ctl) =  WLAN_WME_AC_TO_TID(MAC_GET_CB_WME_AC_TYPE(pst_tx_ctl));

        OAL_MIPS_TX_STATISTIC(HMAC_PROFILING_FUNC_CB_INIT);

        ul_ret = hmac_tx_lan_mpdu_process_sta(pst_hmac_vap, pst_buf, pst_tx_ctl);
#ifdef _PRE_WLAN_FEATURE_WAPI
        if(HMAC_TX_PASS == ul_ret)
            //&& OAL_UNLIKELY(WAPI_IS_WORK(pst_hmac_vap)))
        {
            /* ????wapi???? ????/???? */
            pst_mac_hdr = MAC_GET_CB_FRAME_HEADER_ADDR((mac_tx_ctl_stru *)oal_netbuf_cb(pst_buf));
            en_is_mcast = ETHER_IS_MULTICAST(pst_mac_hdr->auc_address1);
            /*lint -e730*/
            pst_wapi = hmac_user_get_wapi_ptr_etc(pst_vap, !en_is_mcast, pst_vap->us_assoc_vap_id);
            if (OAL_PTR_NULL == pst_wapi)
            {
                OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, tx_abnormal_msdu_dropped, 1);
                OAM_WARNING_LOG1(0, OAM_SF_ANY, "hmac_tx_lan_to_wlan_no_tcp_opt_etc::hmac_user_get_wapi_ptr_etc fail! us_assoc_id[%u]}", pst_vap->us_assoc_vap_id);
                oal_spin_unlock_bh(&pst_hmac_vap->st_lock_state);
                return OAL_ERR_CODE_PTR_NULL;
            }

            /*lint +e730*/
            if ((OAL_TRUE == WAPI_PORT_FLAG(pst_wapi))
              && (OAL_PTR_NULL != pst_wapi->wapi_netbuff_txhandle))
            {
                pst_buf = pst_wapi->wapi_netbuff_txhandle(pst_wapi, pst_buf);
                if (pst_buf == OAL_PTR_NULL)
                {
                    OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, tx_abnormal_msdu_dropped, 1);
                    OAM_WARNING_LOG0(pst_vap->uc_vap_id, OAM_SF_ANY, "{hmac_tx_lan_to_wlan_no_tcp_opt_etc:: wapi_netbuff_txhandle fail!}");
                    oal_spin_unlock_bh(&pst_hmac_vap->st_lock_state);
                    return OAL_ERR_CODE_PTR_NULL;
                }
                /*  ????wapi????????netbuff??????????????????????cb */
                pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_buf);
            }
        }

#endif /* #ifdef _PRE_WLAN_FEATURE_WAPI */

    }

    oal_spin_unlock_bh(&pst_hmac_vap->st_lock_state);
    OAM_PROFILING_TX_STATISTIC(OAL_PTR_NULL, OAM_PROFILING_FUNC_TX_EVENT_TO_DMAC);

    if (OAL_LIKELY(HMAC_TX_PASS == ul_ret))
    {
        /* ???????????????????????? */
        if(MAC_DATA_ARP_REQ >= uc_data_type)
        {
            hmac_tx_lan_mpdu_info(pst_vap, uc_data_type, pst_buf, pst_tx_ctl);
        }

#ifdef _PRE_WLAN_PKT_TIME_STAT
    if (DELAY_STATISTIC_SWITCH_ON && IS_NEED_RECORD_DELAY(pst_buf,TP_SKB_HMAC_XMIT))
        {
            skbprobe_record_time(pst_buf, TP_SKB_HMAC_TX);
        }
#endif

        /* ????????????DMAC */
        pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
        {
            OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan_etc::FRW_EVENT_ALLOC failed.}");
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
            pst_vap->st_vap_stats.ul_tx_dropped_packets++;
#endif
            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }

        pst_event = frw_get_event_stru(pst_event_mem);

        /* ?????????? */
        FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                            FRW_EVENT_TYPE_HOST_DRX,
                            DMAC_TX_HOST_DRX,
                            OAL_SIZEOF(dmac_tx_event_stru),
                            FRW_EVENT_PIPELINE_STAGE_1,
                            pst_vap->uc_chip_id,
                            pst_vap->uc_device_id,
                            pst_vap->uc_vap_id);

        pst_dtx_stru             = (dmac_tx_event_stru *)pst_event->auc_event_data;
        pst_dtx_stru->pst_netbuf = pst_buf;
        //pst_dtx_stru->us_frame_len = (oal_uint16)oal_netbuf_get_len(pst_buf);
        pst_dtx_stru->us_frame_len = MAC_GET_CB_MPDU_LEN(pst_tx_ctl);

        /* ???????? */
        ul_ret = frw_event_dispatch_event_etc(pst_event_mem);
        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan_etc::frw_event_dispatch_event_etc failed[%d].}", ul_ret);
            OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, tx_abnormal_msdu_dropped, 1);
        }

         /* ???????? */
        FRW_EVENT_FREE(pst_event_mem);

        OAL_MIPS_TX_STATISTIC(HMAC_PROFILING_FUNC_TX_EVENT_TO_DMAC);
#ifdef _PRE_WLAN_PROFLING_MIPS
        oal_profiling_stop_tx_save();
#endif
    }
    else if (OAL_UNLIKELY(HMAC_TX_BUFF == ul_ret))
    {
        ul_ret = OAL_SUCC;
    }
    else if ((HMAC_TX_DONE == ul_ret))
    {
        ul_ret = OAL_SUCC;
    }
    #if 0
    else if ((HMAC_TX_DROP_MTOU_FAIL == ul_ret))
    {
        /* ??????????????????STA?????????????????????????????????? */
        OAM_INFO_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan_no_tcp_opt_etc::HMAC_TX_DROP.reason[%d]!}", ul_ret);
    }
    #endif
#ifdef _PRE_WLAN_FEATURE_HERA_MCAST
    else if ((HMAC_TX_DROP_NOSMART == ul_ret))
    {
        /* ??????????????????????????(??????????????)?????????????????????? */
        OAM_INFO_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan_no_tcp_opt_etc::HMAC_TX_DROP.reason[%d]!}", ul_ret);
    }
    else if ((HMAC_TX_DROP_NOADAP == ul_ret))
    {
        /* ??????????????????????????(??????????)?????????????????????? */
        OAM_INFO_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan_no_tcp_opt_etc::HMAC_TX_DROP.reason[%d]!}", ul_ret);
    }
#endif

    else
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan_no_tcp_opt_etc::HMAC_TX_DROP.reason[%d]!}", ul_ret);
    }

    return ul_ret;
}
/*lint +e695*/

#ifdef _PRE_WLAN_TCP_OPT
OAL_STATIC  oal_uint32 hmac_transfer_tx_handler(hmac_device_stru * hmac_device,hmac_vap_stru * hmac_vap,oal_netbuf_stru* netbuf)
{
    mac_tx_ctl_stru        *pst_tx_ctl;
    oal_uint32              ul_ret = OAL_SUCC;

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
    if(WLAN_TCP_ACK_QUEUE == oal_netbuf_select_queue_etc(netbuf))
    {
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
        OAM_WARNING_LOG0(0, OAM_SF_TX,
                             "{hmac_transfer_tx_handler::netbuf is tcp ack.}\r\n");
#endif
        oal_spin_lock_bh(&hmac_vap->st_hamc_tcp_ack[HCC_TX].data_queue_lock[HMAC_TCP_ACK_QUEUE]);
        oal_netbuf_list_tail(&hmac_vap->st_hamc_tcp_ack[HCC_TX].data_queue[HMAC_TCP_ACK_QUEUE], netbuf);

        /* ????TCP ACK????????, ???????????????? */
        if(hmac_judge_tx_netbuf_is_tcp_ack_etc((oal_ether_header_stru *)oal_netbuf_data(netbuf)))
        {
        #if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
            pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(netbuf);
            MAC_GET_CB_TCP_ACK(pst_tx_ctl) = OAL_TRUE;
        #endif
            oal_spin_unlock_bh(&hmac_vap->st_hamc_tcp_ack[HCC_TX].data_queue_lock[HMAC_TCP_ACK_QUEUE]);
            hmac_sched_transfer_etc();
        }
        else
        {
            oal_spin_unlock_bh(&hmac_vap->st_hamc_tcp_ack[HCC_TX].data_queue_lock[HMAC_TCP_ACK_QUEUE]);
            hmac_tcp_ack_process_etc();
        }
    }
    else
    {
        ul_ret = hmac_tx_lan_to_wlan_no_tcp_opt_etc(&(hmac_vap->st_vap_base_info),netbuf);
    }
#endif
    return ul_ret;
}
#endif

#ifdef _PRE_WLAN_FEATURE_DHCP_REQ_DISABLE
OAL_STATIC oal_uint8 mac_get_dhcp_type(oal_uint8 *puc_pos, oal_uint8 *puc_packet_end)
{
    oal_uint8       *puc_opt;
    while ((puc_pos < puc_packet_end) && (*puc_pos != 0xFF))
    {
        puc_opt = puc_pos++;
        if (0 == *puc_opt)
        {
            continue;  /* Padding */
        }
        puc_pos += *puc_pos + 1;
        if (puc_pos >= puc_packet_end)
        {
            break;
        }
        if ((53 == *puc_opt) && (puc_opt[1] != 0))  /* Message type */
        {
            return puc_opt[2];
        }
    }
    return 0xFF;//unknow type
}

oal_bool_enum_uint8 mac_dhcp_frame_should_drop(oal_uint8 *puc_frame_hdr, wlan_vap_mode_enum_uint8 mode)
{
        //oal_uint8                       uc_data_type         = MAC_DATA_BUTT;
        oal_uint8 *                   puc_pos =  puc_frame_hdr;
        oal_ip_header_stru                  *pst_rx_ip_hdr;
        oal_dhcp_packet_stru                *pst_rx_dhcp_hdr;
        oal_uint8                           *puc_packet_end;
        oal_uint8                            uc_type;

    if (OAL_UNLIKELY(OAL_PTR_NULL == puc_frame_hdr))
    {
        return OAL_TRUE;
    }

    puc_pos        += ETHER_HDR_LEN;        /* ????IP Header */
    pst_rx_ip_hdr   = (oal_ip_header_stru *)puc_pos;
    puc_pos        += (puc_pos[0] & 0x0F) << 2;  /* point udp header */
    pst_rx_dhcp_hdr = (oal_dhcp_packet_stru *)(puc_pos + 8);

    puc_packet_end  = (oal_uint8 *)pst_rx_ip_hdr + OAL_NET2HOST_SHORT(pst_rx_ip_hdr->us_tot_len);
    puc_pos         = &(pst_rx_dhcp_hdr->options[4]);

    uc_type = mac_get_dhcp_type(puc_pos, puc_packet_end);

	/* ??????AP??????????????DHCP Request??discovery????????????STA??????????????DHCP offer??DHCP ACK????*/
    if ((WLAN_VAP_MODE_BSS_STA == mode && (MAC_DHCP_OFFER == uc_type || MAC_DHCP_ACK == uc_type)) ||
        (WLAN_VAP_MODE_BSS_AP == mode && (MAC_DHCP_DISCOVER == uc_type || MAC_DHCP_REQUEST == uc_type)))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;

}
#endif


oal_uint32  hmac_tx_wlan_to_wlan_ap_etc(oal_mem_stru *pst_event_mem)
{
    frw_event_stru         *pst_event;        /* ?????????? */
    mac_vap_stru           *pst_mac_vap;
    oal_netbuf_stru        *pst_buf;          /* ??netbuf????????????????netbuf?????? */
    oal_netbuf_stru        *pst_buf_tmp;      /* ????netbuf??????????while???? */
    mac_tx_ctl_stru        *pst_tx_ctl;
    oal_uint32              ul_ret;
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#ifdef _PRE_DEBUG_MODE
    oal_uint16              us_buf_num = 0;
#endif
#endif
    /* ???????? */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_tx_wlan_to_wlan_ap_etc::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* ???????? */
    pst_event = frw_get_event_stru(pst_event_mem);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_tx_wlan_to_wlan_ap_etc::pst_event null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ????PAYLOAD????netbuf?? */
    pst_buf = (oal_netbuf_stru *)(*((oal_uint *)(pst_event->auc_event_data)));

    ul_ret = hmac_tx_get_mac_vap_etc(pst_event->st_event_hdr.uc_vap_id, &pst_mac_vap);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_ERROR_LOG1(pst_event->st_event_hdr.uc_vap_id, OAM_SF_TX, "{hmac_tx_wlan_to_wlan_ap_etc::hmac_tx_get_mac_vap_etc failed[%d].}", ul_ret);
    #ifdef _PRE_DEBUG_MODE
    #if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
        us_buf_num = hmac_free_netbuf_list_etc(pst_buf);
        OAM_STAT_VAP_INCR(pst_event->st_event_hdr.uc_vap_id, tx_abnormal_msdu_dropped, us_buf_num);
    #else
        hmac_free_netbuf_list_etc(pst_buf);
    #endif
    #else
        hmac_free_netbuf_list_etc(pst_buf);
    #endif
        return ul_ret;
    }

    /* ??????????????netbuf???????????????????????? */
    while (OAL_PTR_NULL != pst_buf)
    {
        pst_buf_tmp = OAL_NETBUF_NEXT(pst_buf);

        OAL_NETBUF_NEXT(pst_buf) = OAL_PTR_NULL;
        OAL_NETBUF_PREV(pst_buf) = OAL_PTR_NULL;

        
        pst_tx_ctl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_buf);
        OAL_MEMZERO(pst_tx_ctl, sizeof(mac_tx_ctl_stru));

        MAC_GET_CB_EVENT_TYPE(pst_tx_ctl) = FRW_EVENT_TYPE_WLAN_DTX;
        MAC_GET_CB_EVENT_SUBTYPE(pst_tx_ctl) = DMAC_TX_WLAN_DTX;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        /*set the queue map id when wlan to wlan*/
        oal_skb_set_queue_mapping(pst_buf, WLAN_NORMAL_QUEUE);
#endif

        ul_ret = hmac_tx_lan_to_wlan_etc(pst_mac_vap, pst_buf);

        /* ??????????????????????????netbuff???? */
        if(OAL_SUCC != ul_ret)
        {
            hmac_free_netbuf_list_etc(pst_buf);
        }

        pst_buf = pst_buf_tmp;
    }

    return OAL_SUCC;
}


/*lint -e695*/
OAL_INLINE oal_uint32  hmac_tx_lan_to_wlan_etc(mac_vap_stru *pst_vap, oal_netbuf_stru *pst_buf)
{
    oal_uint32             ul_ret = HMAC_TX_PASS;
#ifdef _PRE_WLAN_TCP_OPT
    hmac_device_stru    *pst_hmac_device;
    hmac_vap_stru         *pst_hmac_vap;     /* VAP?????? */
#endif


#ifdef _PRE_WLAN_TCP_OPT

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_tx_lan_to_wlan_tcp_opt::pst_dmac_vap null.}\r\n");
        return OAL_FAIL;
    }
    pst_hmac_device = hmac_res_get_mac_dev_etc(pst_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_device))
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan_tcp_opt::pst_hmac_device null.}\r\n");
        return OAL_FAIL;
    }
    if(OAL_TRUE == pst_hmac_device->sys_tcp_tx_ack_opt_enable)
    {
        ul_ret = hmac_transfer_tx_handler(pst_hmac_device,pst_hmac_vap,pst_buf);
    }
    else
 #endif
    {
        ul_ret = hmac_tx_lan_to_wlan_no_tcp_opt_etc(pst_vap, pst_buf);
    }
    return ul_ret;
}
/*lint +e695*/

oal_net_dev_tx_enum  hmac_bridge_vap_xmit_etc(oal_netbuf_stru *pst_buf, oal_net_device_stru *pst_dev)
{
    mac_vap_stru                *pst_vap;
    hmac_vap_stru               *pst_hmac_vap;
    oal_uint32                   ul_ret;
#ifdef _PRE_WLAN_FEATURE_ROAM
    oal_uint8                    uc_data_type;
#endif
#ifdef _PRE_WLAN_FEATURE_VIRTUAL_MULTI_STA
    hmac_user_stru              *pst_hmac_user;
#endif

#if defined(_PRE_WLAN_FEATURE_PROXYSTA) ||  defined(_PRE_WLAN_FEATURE_ALWAYS_TX)
    hmac_device_stru  *pst_hmac_device;
#endif
    oal_bool_enum_uint8          en_drop_frame = OAL_FALSE;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_buf))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_bridge_vap_xmit_etc::pst_buf = OAL_PTR_NULL!}\r\n");
        return OAL_NETDEV_TX_OK;
    }

#ifdef _PRE_SKB_TRACE
    mem_trace_add_node((oal_ulong)pst_buf);
#endif


    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_bridge_vap_xmit_etc::pst_dev = OAL_PTR_NULL!}\r\n");
        oal_netbuf_free(pst_buf);
        OAM_STAT_VAP_INCR(0, tx_abnormal_msdu_dropped, 1);
        return OAL_NETDEV_TX_OK;
    }

    /* ????VAP?????? */
    pst_vap = (mac_vap_stru *)OAL_NET_DEV_PRIV(pst_dev);

    /* ????VAP???????????????????????? */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        /* will find vap fail when receive a pkt from
         * kernel while vap is deleted, return OAL_NETDEV_TX_OK is so. */
        OAM_WARNING_LOG0(0, OAM_SF_TX, "{hmac_bridge_vap_xmit_etc::pst_vap = OAL_PTR_NULL!}\r\n");
        oal_netbuf_free(pst_buf);
        OAM_STAT_VAP_INCR(0, tx_abnormal_msdu_dropped, 1);
        return OAL_NETDEV_TX_OK;
    }

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    // pst_vap maybe changed by proxysta
    if (mac_vap_is_msta(pst_vap) || mac_vap_is_vsta(pst_vap))
    {
        if (OAL_SUCC != hmac_psta_tx_process(pst_buf, &pst_vap))
        {
            oal_netbuf_free(pst_buf);
            return OAL_NETDEV_TX_OK;
        }
    }
#endif

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_CFG, "{hmac_bridge_vap_xmit_etc::pst_hmac_vap null.}");
        oal_netbuf_free(pst_buf);
        return OAL_NETDEV_TX_OK;
    }

#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX

    pst_hmac_device = hmac_res_get_mac_dev_etc(pst_vap->uc_device_id);
    if ( OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_PROXYSTA, "{hmac_bridge_vap_xmit_etc::pst_hmac_device is null!}");
        oal_netbuf_free(pst_buf);

        return OAL_NETDEV_TX_OK;
    }

    /*????????????pst_device_stru??????????????, ??????????????????????*/
    if ((OAL_SWITCH_ON == pst_vap->bit_al_tx_flag))
    //|| (HAL_ALWAYS_RX_DISABLE != pst_mac_device->pst_device_stru->bit_al_rx_flag))
    {
        OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_bridge_vap_xmit_etc::the vap alway tx/rx!}\r\n");
        oal_netbuf_free(pst_buf);
        return OAL_NETDEV_TX_OK;
    }
#endif

    pst_buf = oal_netbuf_unshare(pst_buf, GFP_ATOMIC);
    if (OAL_UNLIKELY(pst_buf == OAL_PTR_NULL))
    {
        OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_bridge_vap_xmit_etc::the unshare netbuf = OAL_PTR_NULL!}\r\n");
        return OAL_NETDEV_TX_OK;
    }
 #ifdef _PRE_WLAN_PKT_TIME_STAT
    if(DELAY_STATISTIC_SWITCH_ON && IS_NEED_RECORD_DELAY(pst_buf,TP_SKB_IP))
    {
        skbprobe_record_time(pst_buf, TP_SKB_HMAC_XMIT);
    }
 #endif

    /* ????????????????????SDT */
    hmac_tx_report_eth_frame_etc(pst_vap, pst_buf);

    if(OAL_GET_THRUPUT_BYPASS_ENABLE(OAL_TX_LINUX_BYPASS))
    {
        oal_netbuf_free(pst_buf);
        return OAL_NETDEV_TX_OK;
    }

    /* ????VAP?????????????????????????????? */
    oal_spin_lock_bh(&pst_hmac_vap->st_lock_state);

    /* ????VAP????????????ROAM???????????? MAC_DATA_DHCP/MAC_DATA_ARP */
#ifdef _PRE_WLAN_FEATURE_ROAM
    if(MAC_VAP_STATE_ROAMING == pst_vap->en_vap_state)
    {
        uc_data_type =  mac_get_data_type_from_8023_etc((oal_uint8 *)oal_netbuf_payload(pst_buf), MAC_NETBUFF_PAYLOAD_ETH);
        if(MAC_DATA_EAPOL != uc_data_type)
        {
            oal_netbuf_free(pst_buf);
            oal_spin_unlock_bh(&pst_hmac_vap->st_lock_state);
            return OAL_NETDEV_TX_OK;
        }
    }
    else
    {
#endif  //_PRE_WLAN_FEATURE_ROAM
    /* ????VAP????????????????UP/PAUSE????????????. */
    if (OAL_UNLIKELY(!((MAC_VAP_STATE_UP == pst_vap->en_vap_state) || (MAC_VAP_STATE_PAUSE == pst_vap->en_vap_state))))
    {
        /* ??????????????p2p????????dhcp??eapol???????????????? */
        if (MAC_VAP_STATE_STA_LISTEN != pst_vap->en_vap_state)
        {
            en_drop_frame = OAL_TRUE;
        }
        else
        {
            uc_data_type =  mac_get_data_type_from_8023_etc((oal_uint8 *)oal_netbuf_payload(pst_buf), MAC_NETBUFF_PAYLOAD_ETH);
            if ((MAC_DATA_EAPOL != uc_data_type) && (MAC_DATA_DHCP != uc_data_type))
            {
                en_drop_frame = OAL_TRUE;
            }
            else
            {
                OAM_WARNING_LOG2(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_bridge_vap_xmit_etc::donot drop [%d]frame[EAPOL:1,DHCP:0]. vap state[%d].}",uc_data_type, pst_vap->en_vap_state);
            }
        }

        if (OAL_TRUE == en_drop_frame)
        {
        #if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
            /*filter the tx xmit pkts print*/
            if(MAC_VAP_STATE_INIT == pst_vap->en_vap_state || MAC_VAP_STATE_BUTT == pst_vap->en_vap_state)
            {
                OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_bridge_vap_xmit_etc::vap state[%d] != MAC_VAP_STATE_{UP|PAUSE}!}\r\n", pst_vap->en_vap_state);
            }
            else
            {
                OAM_INFO_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_bridge_vap_xmit_etc::vap state[%d] != MAC_VAP_STATE_{UP|PAUSE}!}\r\n", pst_vap->en_vap_state);
            }
        #else
            OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_bridge_vap_xmit_etc::vap state[%d] != MAC_VAP_STATE_{UP|PAUSE}!}\r\n", pst_vap->en_vap_state);
        #endif
            oal_netbuf_free(pst_buf);
            OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, tx_abnormal_msdu_dropped, 1);

            oal_spin_unlock_bh(&pst_hmac_vap->st_lock_state);
            return OAL_NETDEV_TX_OK;
        }
    }
#ifdef _PRE_WLAN_FEATURE_ROAM
    }
#endif

    OAL_NETBUF_NEXT(pst_buf) = OAL_PTR_NULL;
    OAL_NETBUF_PREV(pst_buf) = OAL_PTR_NULL;

#ifdef _PRE_WLAN_PKT_TIME_STAT
    OAL_MEMZERO(OAL_NETBUF_CB(pst_buf), OAL_NETBUF_CB_ORIGIN);
#else
    OAL_MEMZERO(OAL_NETBUF_CB(pst_buf), OAL_NETBUF_CB_SIZE());
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    /* ARP??DHCP??ICMPv6?????????????????? (????proxy STA????????????????????????)*/
    if (mac_vap_is_vsta(pst_vap))
    {
        ul_ret = hmac_psta_tx_mat(pst_buf, pst_hmac_vap);
        if (OAL_SUCC != ul_ret)
        {
            oal_netbuf_free(pst_buf);
            oal_spin_unlock_bh(&pst_hmac_vap->st_lock_state);
            return OAL_NETDEV_TX_OK;
        }
    }
#endif

#ifdef _PRE_WLAN_FEATURE_SINGLE_PROXYSTA
    /* proxysta ???????????????????????? */
    if ( PROXYSTA_MODE_SSTA == pst_hmac_vap->en_proxysta_mode )
    {
#ifdef _PRE_WLAN_FEATURE_VIRTUAL_MULTI_STA
        /* Single-STA??????????Virtual Multi STA??????????4???????? ??????????????4????????????????Single-STA MAC???? */
        pst_hmac_user = mac_res_get_hmac_user_etc(pst_vap->us_assoc_vap_id);
        if (OAL_PTR_NULL == pst_hmac_user)
        {
            OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_CFG, "{hmac_bridge_vap_xmit_etc::pst_hmac_user null.}");
            oal_netbuf_free(pst_buf);
            oal_spin_unlock_bh(&pst_hmac_vap->st_lock_state);
            return OAL_NETDEV_TX_OK;
        }
        /* MULTI-STA????WDS?????? ??4??????????????????single-sta MAC???? */
        if ( (pst_hmac_vap->st_wds_table.en_wds_vap_mode != WDS_MODE_REPEATER_STA) || (OAL_FALSE == pst_hmac_user->uc_is_wds) )
#endif  //   _PRE_WLAN_FEATURE_VIRTUAL_MULTI_STA
        {
            hmac_proxysta_tx_process(pst_buf, pst_hmac_vap);
        }
    }
#endif

    if (IS_STA(&(pst_hmac_vap->st_vap_base_info)))
    {
#ifdef _PRE_WLAN_FEATURE_BTCOEX
        /* ??????????arp_req ????????ba?????? */
        hmac_btcoex_arp_fail_delba_process_etc(pst_buf, &(pst_hmac_vap->st_vap_base_info));
#endif

#ifdef _PRE_WLAN_FEATURE_M2S
        /* ??????????arp_req ?????????????????? */
        hmac_m2s_arp_fail_process(pst_buf, pst_hmac_vap);
#endif
    }

    oal_spin_unlock_bh(&pst_hmac_vap->st_lock_state);
    OAL_MIPS_TX_STATISTIC(HMAC_PROFILING_FUNC_BRIDGE_VAP_XMIT);

    ul_ret = hmac_tx_lan_to_wlan_etc(pst_vap, pst_buf);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        /* ??????????????????????????netbuff?????? */
        oal_netbuf_free(pst_buf);
    }

    return OAL_NETDEV_TX_OK;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
oal_uint8 g_tx_debug = 0;
oal_uint32 hmac_tx_data(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf)
{
    mac_vap_stru        *pst_vap = &(pst_hmac_vap->st_vap_base_info);
    oal_uint32           ul_ret;
#ifdef _PRE_WLAN_FEATURE_VIRTUAL_MULTI_STA
    hmac_user_stru      *pst_hmac_user;
#endif
#if 0
    mac_ether_header_stru  *pst_ether_hdr;
    pkt_trace_type_enum_uint8 en_trace_pkt_type;
#endif

    if(g_tx_debug)
    {
       OAL_IO_PRINT("hmac_tx_data start\n");
    }

#ifdef _PRE_WLAN_CHIP_TEST
    if (OAL_SWITCH_ON == pst_vap->bit_al_tx_flag)
    {
        OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_data::the vap alway tx!}\r\n");
        oal_netbuf_free(pst_netbuf);
        return OAL_NETDEV_TX_OK;
    }
#endif

    OAM_PROFILING_TX_STATISTIC(OAL_PTR_NULL, OAM_PROFILING_FUNC_HMAC_TX_DATA);

    /* ????????????????????SDT */
    hmac_tx_report_eth_frame_etc(pst_vap, pst_netbuf);
#if 0
#ifdef _PRE_WLAN_DFT_STAT
    if (OAL_TRUE == pst_vap->st_vap_dft.ul_flg && OAL_PTR_NULL != pst_vap->st_vap_dft.pst_vap_dft_stats)
    {
        MAC_VAP_STATS_PKT_INCR(pst_vap->st_vap_dft.pst_vap_dft_stats->ul_lan_tx_pkts, 1);
        MAC_VAP_STATS_BYTE_INCR(pst_vap->st_vap_dft.pst_vap_dft_stats->ul_lan_tx_bytes,
                                OAL_NETBUF_LEN(pst_netbuf) - ETHER_HDR_LEN);
    }
#endif
#endif
    /* ????VAP?????????????????????????????? */
    //oal_spin_lock(&pst_vap->st_lock_state);

     /* ????VAP????????????????UP???????????? */
    if (OAL_UNLIKELY(!((MAC_VAP_STATE_UP == pst_vap->en_vap_state) || (MAC_VAP_STATE_PAUSE == pst_vap->en_vap_state))))
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_data::vap state[%d] != MAC_VAP_STATE_{UP|PAUSE}!}\r\n", pst_vap->en_vap_state);

        oal_netbuf_free(pst_netbuf);

        //oal_spin_unlock(&pst_vap->st_lock_state);
        OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, tx_abnormal_msdu_dropped, 1);

        return OAL_NETDEV_TX_OK;
    }

    OAL_NETBUF_NEXT(pst_netbuf) = OAL_PTR_NULL;
    OAL_NETBUF_PREV(pst_netbuf) = OAL_PTR_NULL;

    OAL_MEMZERO(OAL_NETBUF_CB(pst_netbuf), OAL_NETBUF_CB_SIZE());

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    /* ARP??DHCP??ICMPv6?????????????????? (????proxy STA????????????????????????)*/
    if (mac_vap_is_vsta(pst_vap))
    {
        ul_ret = hmac_psta_tx_mat(pst_netbuf, pst_hmac_vap);

        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA, "{hmac_tx_data::hmac_tx_proxysta_mat fail.}");
            oal_netbuf_free(pst_netbuf);
            //oal_spin_unlock(&pst_vap->st_lock_state);

            return OAL_NETDEV_TX_OK;
        }
    }
#endif
#ifdef _PRE_WLAN_FEATURE_SINGLE_PROXYSTA
    /* proxysta ???????????????????????? */
    if ( PROXYSTA_MODE_SSTA == pst_hmac_vap->en_proxysta_mode )
    {
#ifdef _PRE_WLAN_FEATURE_VIRTUAL_MULTI_STA
        /* Single-STA??????????Virtual Multi STA??????????4???????? ??????????????4????????????????Single-STA MAC???? */
        pst_hmac_user = mac_res_get_hmac_user_etc(pst_vap->us_assoc_vap_id);
        if (OAL_PTR_NULL == pst_hmac_user)
        {
            OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_PROXYSTA, "{hmac_tx_data::pst_hmac_user null.}");
            oal_netbuf_free(pst_netbuf);
            return OAL_NETDEV_TX_OK;
        }
        /* MULTI-STA????WDS?????? ??4??????????????????single-sta MAC???? */
        if ( (pst_hmac_vap->st_wds_table.en_wds_vap_mode != WDS_MODE_REPEATER_STA) || (OAL_FALSE == pst_hmac_user->uc_is_wds) )
#endif  //   _PRE_WLAN_FEATURE_VIRTUAL_MULTI_STA
        {
            hmac_proxysta_tx_process(pst_netbuf, pst_hmac_vap);
        }
    }
#endif // _PRE_WLAN_FEATURE_SINGLE_PROXYSTA

    ul_ret = hmac_tx_lan_to_wlan_etc(pst_vap, pst_netbuf);

    /* ??????????????????????????netbuff?????? */
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        hmac_free_netbuf_list_etc(pst_netbuf);
    }

    //oal_spin_unlock(&pst_vap->st_lock_state);

    return OAL_NETDEV_TX_OK;
}


OAL_STATIC oal_void  hmac_lock_resource(oal_spin_lock_stru *pst_lock, oal_uint *pui_flags)
{
#ifdef _PRE_WLAN_SPE_SUPPORT
    oal_spin_lock_irq_save(pst_lock, pui_flags);        //??????E5??????????
#else
    oal_spin_lock_bh(pst_lock);
#endif
}

OAL_STATIC oal_void  hmac_unlock_resource(oal_spin_lock_stru *pst_lock, oal_uint *pui_flags)
{
#ifdef _PRE_WLAN_SPE_SUPPORT
    oal_spin_unlock_irq_restore(pst_lock, pui_flags);   //??????E5??????????
#else
    oal_spin_unlock_bh(pst_lock);
#endif
}


oal_net_dev_tx_enum  hmac_vap_start_xmit(oal_netbuf_stru *pst_buf, oal_net_device_stru *pst_dev)
{
    mac_vap_stru               *pst_vap;
    hmac_vap_stru              *pst_hmac_vap;
    oal_ulong                   ul_lock_flag;
    oal_uint8                   uc_data_type;
    oal_uint8                  *puc_frame_hdr;
#ifdef _PRE_DEBUG_MODE
    pkt_trace_type_enum_uint8   en_trace_pkt_type;
    oal_uint8                   auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0};
#endif

   OAM_PROFILING_TX_STATISTIC(OAL_PTR_NULL, OAM_PROFILING_FUNC_CONFIG_XMIT_START);

#ifdef _PRE_SKB_TRACE
    mem_trace_add_node((oal_ulong)pst_buf);
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_vap_start_xmit::pst_dev = OAL_PTR_NULL!}\r\n");
        oal_netbuf_free(pst_buf);
        OAM_STAT_VAP_INCR(0, tx_abnormal_msdu_dropped, 1);
        return OAL_NETDEV_TX_OK;
    }

    /* ????VAP?????? */
    pst_vap = (mac_vap_stru *)OAL_NET_DEV_PRIV(pst_dev);

    /* ????VAP???????????????????????? */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_vap_start_xmit::pst_vap = OAL_PTR_NULL!}\r\n");
        oal_netbuf_free(pst_buf);
        OAM_STAT_VAP_INCR(0, tx_abnormal_msdu_dropped, 1);
        return OAL_NETDEV_TX_OK;
    }

    pst_buf = oal_netbuf_unshare(pst_buf, GFP_ATOMIC);
    if (pst_buf == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_vap_start_xmit::the unshare netbuf = OAL_PTR_NULL!}\r\n");
        return OAL_NETDEV_TX_OK;
    }

#ifdef _PRE_DEBUG_MODE
    //????????????????????????????????????????????????????????????????
    en_trace_pkt_type = mac_pkt_should_trace( OAL_NETBUF_DATA(pst_buf), MAC_NETBUFF_PAYLOAD_ETH);
    if( PKT_TRACE_BUTT != en_trace_pkt_type)
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_vap_start_xmit::type%d from eth[0:dhcp 1:arp_req 2:arp_rsp 3:eapol 4:icmp 5:assoc_req 6:assoc_rsp 9:dis_assoc 10:auth 11:deauth]}\r\n", en_trace_pkt_type);
        oal_set_mac_addr(auc_user_macaddr, pst_vap->auc_bssid);
        oam_report_eth_frame_etc(auc_user_macaddr,
                                oal_netbuf_data(pst_buf),
                                (oal_uint16)OAL_NETBUF_LEN(pst_buf),
                                OAM_OTA_FRAME_DIRECTION_TYPE_TX);
    }
#endif

    puc_frame_hdr = (oal_uint8 *)oal_netbuf_payload(pst_buf);
    uc_data_type = mac_get_data_type_from_8023_etc(puc_frame_hdr, MAC_NETBUFF_PAYLOAD_ETH);
#ifdef _PRE_WLAN_FEATURE_DHCP_REQ_DISABLE
    /* ??????AP??????????????DHCP Request??discovery??????
        ??????STA??????????????DHCP offer??DHCP ACK????*/
    if (OAL_TRUE == pst_vap->en_dhcp_req_disable_switch && MAC_DATA_DHCP == uc_data_type &&
        OAL_TRUE == mac_dhcp_frame_should_drop(puc_frame_hdr, pst_vap->en_vap_mode))
    {
            OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_vap_start_xmit::dhcp pkt is dropped!}\r\n");
            oal_netbuf_free(pst_buf);
            return OAL_NETDEV_TX_OK;
    }
#endif
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    // warning:pst_vap maybe changed in this function!!!
    if (mac_vap_is_msta(pst_vap) || mac_vap_is_vsta(pst_vap))
    {
        if (OAL_SUCC != hmac_psta_tx_process(pst_buf, &pst_vap))
        {
            oal_netbuf_free(pst_buf);
            return OAL_NETDEV_TX_OK;
        }
    }
#endif

    pst_hmac_vap = mac_res_get_hmac_vap(pst_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG1(0, OAM_SF_TX, "{hmac_vap_start_xmit::pst_hmac_vap[%d] = OAL_PTR_NULL!}", pst_vap->uc_vap_id);
        oal_netbuf_free(pst_buf);
        OAM_STAT_VAP_INCR(0, tx_abnormal_msdu_dropped, 1);
        return OAL_NETDEV_TX_OK;
    }

#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    if ((OAL_SWITCH_ON == pst_vap->bit_al_tx_flag))
    {
        OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_vap_start_xmit::the vap alway tx!}\r\n");
        oal_netbuf_free(pst_buf);
        return OAL_NETDEV_TX_OK;
    }
#endif

    /* ??????????????????????????????????????????????????????????skb????????????????????????????????300??MIPS?????????????????????? */
    if(OAL_NETBUF_LIST_NUM(&pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_in_queue_id]) >= HMAC_TXQUEUE_DROP_LIMIT_LOW)
    {
        /* ????????100???????????????????????????? */
        if(OAL_NETBUF_LIST_NUM(&pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_in_queue_id]) < HMAC_TXQUEUE_DROP_LIMIT_HIGH)
        {

            if(MAC_DATA_ARP_REQ >= uc_data_type)
            {
                hmac_lock_resource(&pst_hmac_vap->st_smp_lock, &ul_lock_flag);
                oal_netbuf_add_to_list_tail(pst_buf, &(pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_in_queue_id]));
                hmac_unlock_resource(&pst_hmac_vap->st_smp_lock, &ul_lock_flag);
            }
            else
            {
                OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_vap_start_xmit: txqueue full drop}");
                oal_netbuf_free(pst_buf);
            }
        }
        else
        {
            oal_netbuf_free(pst_buf);
        }

        if(g_tx_debug)
        {
            /* ????????????????tx_event_num????????????????????????????????????ping??????????g_tx_debug??????????????????????1???????????? */
            OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_vap_start_xmit::tx_event_num value is [%d].}", (oal_int32)oal_atomic_read(&(pst_hmac_vap->ul_tx_event_num)));
            OAL_IO_PRINT("hmac_vap_start_xmit too fast\n");
        }
    }
    else
    {
        if(g_tx_debug)
            OAL_IO_PRINT("hmac_vap_start_xmit enqueue and post event\n");

        hmac_lock_resource(&pst_hmac_vap->st_smp_lock, &ul_lock_flag);
        oal_netbuf_add_to_list_tail(pst_buf, &(pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_in_queue_id]));
        hmac_unlock_resource(&pst_hmac_vap->st_smp_lock, &ul_lock_flag);
    }

    hmac_tx_post_event(pst_vap);

   OAM_PROFILING_TX_STATISTIC(OAL_PTR_NULL, OAM_PROFILING_FUNC_CONFIG_XMIT_END);

    return OAL_NETDEV_TX_OK;
}

oal_uint32 hmac_tx_post_event(mac_vap_stru *pst_mac_vap)
{
    oal_uint32              ul_ret;
    frw_event_stru          *pst_event;
    frw_event_mem_stru      *pst_event_mem;
    hmac_vap_stru           *pst_hmac_vap;

    pst_hmac_vap = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_post_event::mac_res_get_hmac_vap null.}");
        OAL_IO_PRINT("Hmac_tx_post_event fail to get hmac vap\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* tx_event_num??1??????0????eth to wlan?????????????????????????????????????????????????????????????????????????????????????????????????????? */
    if(oal_atomic_dec_and_test(&(pst_hmac_vap->ul_tx_event_num)))
    {
        /* ???????????? */
        pst_event_mem = FRW_EVENT_ALLOC(0);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
        {
            oal_atomic_inc(&(pst_hmac_vap->ul_tx_event_num)); /* ??????????????tx_event_num??????????????????????1 */
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_post_event::pst_event_mem null.}");
            OAL_IO_PRINT("Hmac_tx_post_event fail to alloc event mem\n");
            return OAL_ERR_CODE_PTR_NULL;
        }

        pst_event = frw_get_event_stru(pst_event_mem);

        /* ???????? */
        FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                           FRW_EVENT_TYPE_HOST_DRX,
                           HMAC_TX_HOST_DRX,
                           0,
                           FRW_EVENT_PIPELINE_STAGE_0,
                           pst_mac_vap->uc_chip_id,
                           pst_mac_vap->uc_device_id,
                           pst_mac_vap->uc_vap_id);


        /* ?????????? */
        ul_ret = frw_event_post_event_etc(pst_event_mem,pst_mac_vap->ul_core_id);
        if (OAL_SUCC != ul_ret)
        {
            oal_atomic_inc(&(pst_hmac_vap->ul_tx_event_num)); /* ??????????????tx_event_num??????????????????????1 */
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_post_event::frw_event_dispatch_event_etc failed[%d].}", ul_ret);
            OAL_IO_PRINT("{hmac_tx_post_event::frw_event_dispatch_event_etc failed}\n");
        }

        /* ???????????? */
        FRW_EVENT_FREE(pst_event_mem);
    }
    else
    {
        /* ??????????????????????????(tx_event_num????0)????????????????????????????????tx_event_num????????0 */
        oal_atomic_inc(&(pst_hmac_vap->ul_tx_event_num));

        if(g_tx_debug)
        {
            OAL_IO_PRINT("do not post tx event, data in queue len %d,out queue len %d\n",
                            OAL_NETBUF_LIST_NUM(&pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_in_queue_id]),
                            OAL_NETBUF_LIST_NUM(&pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_out_queue_id]));
        }
    }

    return OAL_SUCC;
}

OAL_STATIC oal_uint8 hmac_vap_user_is_bw_limit(mac_vap_stru *pst_vap, oal_netbuf_stru *pst_netbuf)
{
    mac_ether_header_stru   *pst_ether_hdr; /* ???????? */
    oal_uint16               us_user_idx;
    hmac_user_stru          *pst_hmac_user;
    oal_uint32               ul_ret;

    pst_ether_hdr   = (mac_ether_header_stru *)oal_netbuf_data(pst_netbuf);
    ul_ret = mac_vap_find_user_by_macaddr_etc(pst_vap, pst_ether_hdr->auc_ether_dhost, &us_user_idx);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        return OAL_FALSE;
    }
    pst_hmac_user    = (hmac_user_stru *)mac_res_get_hmac_user_etc(us_user_idx);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    return (oal_uint8)(pst_vap->bit_vap_bw_limit || pst_hmac_user->en_user_bw_limit);
}

oal_uint32  hmac_tx_event_process(oal_mem_stru *pst_event_mem)
{
    frw_event_stru          *pst_event;
    hmac_vap_stru           *pst_hmac_vap;
    oal_uint32               ul_work = 0;
    oal_uint32               ul_reschedule = OAL_TRUE;
    oal_netbuf_stru         *pst_netbuf;

    OAM_PROFILING_TX_STATISTIC(OAL_PTR_NULL, OAM_PROFILING_FUNC_HMAC_TX_EVENT);

    /* ???????? */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_tx_event_process::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;//lint !e527
    }

    /* ???????? */
    pst_event = frw_get_event_stru(pst_event_mem);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_tx_event_process::pst_event null.}");
        return OAL_ERR_CODE_PTR_NULL;//lint !e527
    }

    pst_hmac_vap = mac_res_get_hmac_vap(pst_event->st_event_hdr.uc_vap_id);
    if(OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_tx_event_process::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;//lint !e527
    }
    if(g_tx_debug)
        OAL_IO_PRINT("hmac_tx_event_process start\n");

    /* ????????????hmac_tx_post_event????????????????0??????????????????????1 */
    oal_atomic_inc(&(pst_hmac_vap->ul_tx_event_num));

    if(g_tx_debug)
        OAL_IO_PRINT("oal_atomic_dec OK\n");

    oal_spin_lock_bh(&pst_hmac_vap->st_smp_lock);
    if(0 == OAL_NETBUF_LIST_NUM(&pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_out_queue_id]))
    {
        /*????????out queue????, ??????out_queue_id*/
        pst_hmac_vap->uc_in_queue_id = pst_hmac_vap->uc_out_queue_id;
        pst_hmac_vap->uc_out_queue_id = (pst_hmac_vap->uc_out_queue_id + 1) & 1;

    }
    oal_spin_unlock_bh(&pst_hmac_vap->st_smp_lock);

    do
    {
        oal_spin_lock_bh(&pst_hmac_vap->st_smp_lock);
        pst_netbuf = oal_netbuf_delist(&pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_out_queue_id]);
        oal_spin_unlock_bh(&pst_hmac_vap->st_smp_lock);

        if (!pst_netbuf)
        {
            if(g_tx_debug)
                OAL_IO_PRINT("oal netbuf delist OK\n");
            ul_reschedule = OAL_FALSE;
            break;
        }

        if(OAL_TRUE == hmac_vap_user_is_bw_limit(&(pst_hmac_vap->st_vap_base_info), pst_netbuf))
        {
            /* ????????????????????????vap????????????????????????????????ping???????? */
            OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_event_process::vap id[%d] hmac_vap_user_is_bw_limit.}", pst_hmac_vap->st_vap_base_info.uc_vap_id);
            oal_spin_lock_bh(&pst_hmac_vap->st_smp_lock);
            oal_netbuf_add_to_list_tail(pst_netbuf, &pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_out_queue_id]);
            oal_spin_unlock_bh(&pst_hmac_vap->st_smp_lock);
            continue;
        }

        hmac_tx_data(pst_hmac_vap,pst_netbuf);
    } while(++ul_work < pst_hmac_vap->ul_tx_quata); // && jiffies == ul_start_time

    if(OAL_TRUE == ul_reschedule)
    {
        hmac_tx_post_event(&(pst_hmac_vap->st_vap_base_info));
    }

    return OAL_SUCC;
}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/* ???????????????? */
oal_uint8  g_uc_tx_ba_policy_select = OAL_TRUE;
#endif

oal_void hmac_tx_ba_cnt_vary_etc(
                       hmac_vap_stru   *pst_hmac_vap,
                       hmac_user_stru  *pst_hmac_user,
                       oal_uint8        uc_tidno,
                       oal_netbuf_stru *pst_buf)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint32             ul_current_timestamp;

    if ((WLAN_VAP_MODE_BSS_STA == pst_hmac_vap->st_vap_base_info.en_vap_mode) &&
        (OAL_TRUE == g_uc_tx_ba_policy_select))
    {
        
        pst_hmac_user->auc_ba_flag[uc_tidno]++;
    }
    else
    {
        ul_current_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();

        /* ??????????????????
           ??????????????????????????BA;
           TCP ACK???????????????????????? */
        if((0 == pst_hmac_user->auc_ba_flag[uc_tidno])
           || (oal_netbuf_is_tcp_ack_etc((oal_ip_header_stru *)(oal_netbuf_data(pst_buf) + ETHER_HDR_LEN)))
           || ((oal_uint32)OAL_TIME_GET_RUNTIME(pst_hmac_user->aul_last_timestamp[uc_tidno], ul_current_timestamp) < WLAN_BA_CNT_INTERVAL))
        {
            pst_hmac_user->auc_ba_flag[uc_tidno]++;
        }
        else
        {
            pst_hmac_user->auc_ba_flag[uc_tidno] = 0;
        }

        pst_hmac_user->aul_last_timestamp[uc_tidno] = ul_current_timestamp;
    }
#else
    pst_hmac_user->auc_ba_flag[uc_tidno]++;
#endif
}


/*lint -e19*/
oal_module_symbol(hmac_tx_wlan_to_wlan_ap_etc);
oal_module_symbol(hmac_tx_lan_to_wlan_etc);
oal_module_symbol(hmac_free_netbuf_list_etc);

oal_module_symbol(hmac_tx_report_eth_frame_etc);
oal_module_symbol(hmac_bridge_vap_xmit_etc);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
oal_module_symbol(g_tx_debug);
oal_module_symbol(hmac_vap_start_xmit);
oal_module_symbol(hmac_tx_post_event);
#endif
/*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


