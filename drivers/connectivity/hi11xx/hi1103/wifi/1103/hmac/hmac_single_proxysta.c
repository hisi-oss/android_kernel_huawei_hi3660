


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#ifdef _PRE_WLAN_FEATURE_SINGLE_PROXYSTA

/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "wlan_spec.h"
#include "mac_frame.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "hmac_device.h"
#include "hmac_resource.h"
#include "hmac_single_proxysta.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_SINGLE_PROXYSTA_C




oal_uint32  hmac_proxysta_map_aging_timer(void *p_arg)
{
    oal_uint32          ul_present_time = 0;
    oal_uint32          ul_map_idle_time = 0;
    hmac_vap_stru        *pst_hmac_vap = OAL_PTR_NULL;
    oal_uint32          ul_loop = 0;
    oal_dlist_head_stru             *pst_entry = OAL_PTR_NULL;
    oal_dlist_head_stru             *pst_dlist_temp = OAL_PTR_NULL;
    hmac_proxysta_ipv4_hash_stru    *pst_hash_ipv4 = OAL_PTR_NULL;
    hmac_proxysta_ipv6_hash_stru    *pst_hash_ipv6 = OAL_PTR_NULL;
    hmac_proxysta_unknow_hash_stru  *pst_hash_unknow = OAL_PTR_NULL;

    if (OAL_PTR_NULL == p_arg)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA, "{hmac_proxysta_map_aging_timer::p_arg null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_hmac_vap = (hmac_vap_stru *)p_arg;
    if (OAL_PTR_NULL == pst_hmac_vap->pst_vap_proxysta)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA, "{hmac_proxysta_map_aging_timer::pst_vap_proxysta null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ???????????? */
    ul_present_time = (oal_uint32)OAL_TIME_GET_STAMP_MS();
    /* ????????????????????????????????????MAP?? ???????? */
    oal_rw_lock_read_lock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
    for (ul_loop = 0; ul_loop < MAC_VAP_PROXYSTA_MAP_MAX_VALUE; ul_loop++)
    {
        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_temp, &(pst_hmac_vap->pst_vap_proxysta->ast_map_ipv4_head[ul_loop]))
        {
            pst_hash_ipv4 = OAL_DLIST_GET_ENTRY(pst_entry, hmac_proxysta_ipv4_hash_stru, st_entry);
            ul_map_idle_time = (oal_uint32)OAL_TIME_GET_RUNTIME(pst_hash_ipv4->ul_last_active_timestamp, ul_present_time);
            if (HMAC_PROXYSTA_MAP_AGING_TIME < ul_map_idle_time)
            {
                oal_rw_lock_read_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
#ifdef _PRE_DEBUG_MODE
                OAM_WARNING_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                    "{hmac_proxysta_map_aging_timer:: remove ipv4 map[%d:%d:%d:%d].}",
                    pst_hash_ipv4->auc_ipv4[0], pst_hash_ipv4->auc_ipv4[1], pst_hash_ipv4->auc_ipv4[2], pst_hash_ipv4->auc_ipv4[3]);
                OAM_WARNING_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                    "{hmac_proxysta_map_aging_timer:: remove ipv4 map[%x:%x:ff:ff:%x:%x].}",
                    pst_hash_ipv4->auc_mac[0], pst_hash_ipv4->auc_mac[1], pst_hash_ipv4->auc_mac[4], pst_hash_ipv4->auc_mac[5]);
#endif
                oal_rw_lock_write_lock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
                oal_dlist_delete_entry(&pst_hash_ipv4->st_entry);
                OAL_MEM_FREE(pst_hash_ipv4, OAL_TRUE);
                pst_hmac_vap->pst_vap_proxysta->uc_map_ipv4_num --;
                oal_rw_lock_write_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
                oal_rw_lock_read_lock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
            }
        }
    }

    for (ul_loop = 0; ul_loop < MAC_VAP_PROXYSTA_MAP_MAX_VALUE; ul_loop++)
    {
        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_temp, &(pst_hmac_vap->pst_vap_proxysta->ast_map_ipv6_head[ul_loop]))
        {
            pst_hash_ipv6 = OAL_DLIST_GET_ENTRY(pst_entry, hmac_proxysta_ipv6_hash_stru, st_entry);
            ul_map_idle_time = (oal_uint32)OAL_TIME_GET_RUNTIME(pst_hash_ipv6->ul_last_active_timestamp, ul_present_time);
            if (HMAC_PROXYSTA_MAP_AGING_TIME < ul_map_idle_time)
            {
                oal_rw_lock_read_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
#ifdef _PRE_DEBUG_MODE
                OAM_WARNING_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                    "{hmac_proxysta_map_aging_timer:: remove one ipv6 map[%x:%x:xx:xx:xx:xx:%x:%x].}",
                    pst_hash_ipv6->auc_ipv6[0]*pst_hash_ipv6->auc_ipv6[1], pst_hash_ipv6->auc_ipv6[2]*pst_hash_ipv6->auc_ipv6[3],
                    pst_hash_ipv6->auc_ipv6[12]*pst_hash_ipv6->auc_ipv6[13], pst_hash_ipv6->auc_ipv6[14]*pst_hash_ipv6->auc_ipv6[15]);
                OAM_WARNING_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                    "{hmac_proxysta_map_aging_timer:: remove one ipv6 map[%x:%x:ff:ff:%x:%x].}",
                    pst_hash_ipv6->auc_mac[0], pst_hash_ipv6->auc_mac[1], pst_hash_ipv6->auc_mac[4], pst_hash_ipv6->auc_mac[5]);
#endif
                oal_rw_lock_write_lock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
                oal_dlist_delete_entry(&pst_hash_ipv6->st_entry);
                OAL_MEM_FREE(pst_hash_ipv6, OAL_TRUE);
                pst_hmac_vap->pst_vap_proxysta->uc_map_ipv6_num --;
                oal_rw_lock_write_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
                oal_rw_lock_read_lock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
            }
        }
    }

    for (ul_loop = 0; ul_loop < MAC_VAP_PROXYSTA_MAP_UNKNOW_VALUE; ul_loop++)
    {
        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_temp, &(pst_hmac_vap->pst_vap_proxysta->ast_map_unknow_head[ul_loop]))
        {
            pst_hash_unknow = OAL_DLIST_GET_ENTRY(pst_entry, hmac_proxysta_unknow_hash_stru, st_entry);
            ul_map_idle_time = (oal_uint32)OAL_TIME_GET_RUNTIME(pst_hash_unknow->ul_last_active_timestamp, ul_present_time);
            if (HMAC_PROXYSTA_MAP_AGING_TIME < ul_map_idle_time)
            {
                oal_rw_lock_read_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
#ifdef _PRE_DEBUG_MODE
                OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                    "{hmac_proxysta_map_aging_timer:: remove unknow map [%x].}", pst_hash_unknow->us_protocol);
                OAM_WARNING_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                    "{hmac_proxysta_map_aging_timer:: remove unknow map [%x:%x:ff:ff:%x:%x].}",
                    pst_hash_unknow->auc_mac[0], pst_hash_unknow->auc_mac[1], pst_hash_unknow->auc_mac[4], pst_hash_unknow->auc_mac[5]);
#endif
                oal_rw_lock_write_lock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
                oal_dlist_delete_entry(&pst_hash_unknow->st_entry);
                OAL_MEM_FREE(pst_hash_unknow, OAL_TRUE);
                pst_hmac_vap->pst_vap_proxysta->uc_map_unknow_num --;
                oal_rw_lock_write_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
                oal_rw_lock_read_lock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
            }
        }
    }
    oal_rw_lock_read_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);

    return OAL_SUCC;
}


oal_uint32  hmac_proxysta_init_vap(hmac_vap_stru *pst_hmac_vap, mac_cfg_add_vap_param_stru *pst_param)
{
    oal_uint32          ul_loop = 0;
    hmac_device_stru    *pst_hmac_device = OAL_PTR_NULL;

    /* ?????????????? */
    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PROXYSTA, "{hmac_proxysta_init_vap::null param: hmac_vap[%d] param[%d]!}",
            pst_hmac_vap, pst_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap->en_proxysta_mode = pst_param->en_proxysta_mode;
    /* repeater?????? ??proxysta?????????????????? AP??????????map?? */
    if (PROXYSTA_MODE_SSTA == pst_param->en_proxysta_mode)
    {
        pst_hmac_vap->pst_vap_proxysta = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(hmac_vap_proxysta_stru), OAL_TRUE);
        if (OAL_PTR_NULL == pst_hmac_vap->pst_vap_proxysta)
        {
            OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                "hmac_proxysta_init_vap malloc error: pointer null!");
            return OAL_ERR_CODE_PTR_NULL;
        }
        oal_rw_lock_init(&pst_hmac_vap->pst_vap_proxysta->st_lock);
        /* ?????????? */
        for (ul_loop = 0; ul_loop < MAC_VAP_PROXYSTA_MAP_MAX_VALUE; ul_loop++)
        {
            oal_dlist_init_head(&(pst_hmac_vap->pst_vap_proxysta->ast_map_ipv4_head[ul_loop]));
        }
        pst_hmac_vap->pst_vap_proxysta->uc_map_ipv4_num = 0;
        for (ul_loop = 0; ul_loop < MAC_VAP_PROXYSTA_MAP_MAX_VALUE; ul_loop++)
        {
            oal_dlist_init_head(&(pst_hmac_vap->pst_vap_proxysta->ast_map_ipv6_head[ul_loop]));
        }
        pst_hmac_vap->pst_vap_proxysta->uc_map_ipv6_num = 0;
        for (ul_loop = 0; ul_loop < MAC_VAP_PROXYSTA_MAP_UNKNOW_VALUE; ul_loop++)
        {
            oal_dlist_init_head(&(pst_hmac_vap->pst_vap_proxysta->ast_map_unknow_head[ul_loop]));
        }
        pst_hmac_vap->pst_vap_proxysta->uc_map_unknow_num = 0;
        /* ??????????????????????proxysta??map???????????? */
        /* ????hmac device?????????????? */
        pst_hmac_device = hmac_res_get_mac_dev_etc(pst_hmac_vap->st_vap_base_info.uc_device_id);
        if (OAL_PTR_NULL == pst_hmac_device)
        {
            OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                "{hmac_proxysta_init_vap::null param: pst_hmac_device[%d]!}", pst_hmac_device);
            return OAL_ERR_CODE_PTR_NULL;
        }
        /* ????map keepalive??????, ??????????????, ???????????? */
        if (!pst_hmac_device->st_proxysta_map_timer.en_is_registerd)
        {
            FRW_TIMER_CREATE_TIMER(&(pst_hmac_device->st_proxysta_map_timer),
                                   hmac_proxysta_map_aging_timer,
                                   HMAC_PROXYSTA_MAP_AGING_TRIGGER_TIME,                /* 60s???????? */
                                   pst_hmac_vap,
                                   OAL_TRUE,
                                   OAM_MODULE_ID_HMAC,
                                   pst_hmac_device->pst_device_base_info->ul_core_id);
        }
    }
    return OAL_SUCC;
}


oal_uint32  hmac_proxysta_exit_vap(hmac_vap_stru *pst_hmac_vap)
{
    oal_dlist_head_stru             *pst_entry = OAL_PTR_NULL;
    hmac_proxysta_ipv4_hash_stru    *pst_hash_ipv4 = OAL_PTR_NULL;
    hmac_proxysta_ipv6_hash_stru    *pst_hash_ipv6 = OAL_PTR_NULL;
    hmac_proxysta_unknow_hash_stru  *pst_hash_unknow = OAL_PTR_NULL;
    oal_dlist_head_stru             *pst_dlist_tmp = OAL_PTR_NULL;
    hmac_device_stru                *pst_hmac_device = OAL_PTR_NULL;
    oal_uint32                      ul_loop = 0;

    /* ?????????????? */
    if (OAL_PTR_NULL == pst_hmac_vap )
    {
        OAM_ERROR_LOG1(0, OAM_SF_PROXYSTA, "{hmac_proxysta_exit_vap::null param: hmac_vap[%d]!}", pst_hmac_vap);
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* ??PROXYSTA??map??????????????  ???????????????? */
    if ( (PROXYSTA_MODE_SSTA != pst_hmac_vap->en_proxysta_mode) ||
        (OAL_PTR_NULL == pst_hmac_vap->pst_vap_proxysta) )
    {
        return OAL_SUCC;
    }
    /* ????hmac_device?????????? */
    pst_hmac_device = hmac_res_get_mac_dev_etc(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_exit_vap::null param: pst_hmac_device[%d]!}", pst_hmac_device);
        return OAL_ERR_CODE_PTR_NULL;
    }
    if (pst_hmac_device->st_proxysta_map_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_hmac_device->st_proxysta_map_timer);
    }
    /* ???????? */
    for (ul_loop = 0; ul_loop < MAC_VAP_PROXYSTA_MAP_MAX_VALUE; ul_loop++)
    {
        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_hmac_vap->pst_vap_proxysta->ast_map_ipv4_head[ul_loop]))
        {
            pst_hash_ipv4 = OAL_DLIST_GET_ENTRY(pst_entry, hmac_proxysta_ipv4_hash_stru, st_entry);
            oal_dlist_delete_entry(pst_entry);
            OAL_MEM_FREE(pst_hash_ipv4, OAL_TRUE);
        }
    }
    pst_hmac_vap->pst_vap_proxysta->uc_map_ipv4_num = 0;
    for (ul_loop = 0; ul_loop < MAC_VAP_PROXYSTA_MAP_MAX_VALUE; ul_loop++)
    {
        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_hmac_vap->pst_vap_proxysta->ast_map_ipv6_head[ul_loop]))
        {
            pst_hash_ipv6 = OAL_DLIST_GET_ENTRY(pst_entry, hmac_proxysta_ipv6_hash_stru, st_entry);
            oal_dlist_delete_entry(pst_entry);
            OAL_MEM_FREE(pst_hash_ipv6, OAL_TRUE);
        }
    }
    pst_hmac_vap->pst_vap_proxysta->uc_map_ipv6_num = 0;
    for (ul_loop = 0; ul_loop < MAC_VAP_PROXYSTA_MAP_UNKNOW_VALUE; ul_loop++)
    {
        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_hmac_vap->pst_vap_proxysta->ast_map_unknow_head[ul_loop]))
        {
            pst_hash_unknow = OAL_DLIST_GET_ENTRY(pst_entry, hmac_proxysta_unknow_hash_stru, st_entry);
            oal_dlist_delete_entry(pst_entry);
            OAL_MEM_FREE(pst_hash_unknow, OAL_TRUE);
        }
    }
    pst_hmac_vap->pst_vap_proxysta->uc_map_unknow_num = 0;

    OAL_MEM_FREE(pst_hmac_vap->pst_vap_proxysta, OAL_TRUE);
    pst_hmac_vap->pst_vap_proxysta = OAL_PTR_NULL;

    return OAL_SUCC;
}


OAL_STATIC oal_uint16  hmac_proxysta_cal_checksum(oal_uint16   us_protocol,
                                                 oal_uint16   us_len,
                                                 oal_uint8    auc_src_addr[],
                                                 oal_uint8    auc_dest_addr[],
                                                 oal_uint16   us_addrleninbytes,
                                                 oal_uint8   *puc_buff)
{
    oal_uint16 us_pad = 0;
    oal_uint16 us_word16;
    oal_uint32 ul_sum = 0;
    oal_int    l_loop;

    if (us_len & 1)
    {
        us_len -= 1;
        us_pad  = 1;
    }

    for (l_loop = 0; l_loop < us_len; l_loop = l_loop + 2)
    {
        us_word16 = puc_buff[l_loop];
        us_word16 = (oal_uint16)((us_word16 << 8) + puc_buff[l_loop+1]);
        ul_sum = ul_sum + (oal_uint32)us_word16;
    }

    if (us_pad)
    {
        us_word16 = puc_buff[us_len];
        us_word16 <<= 8;
        ul_sum = ul_sum + (oal_uint32)us_word16;
    }

    for (l_loop = 0; l_loop < us_addrleninbytes; l_loop = l_loop + 2)
    {
        us_word16 = auc_src_addr[l_loop];
        us_word16 = (oal_uint16)((us_word16 << 8) + auc_src_addr[l_loop + 1]);
        ul_sum = ul_sum + (oal_uint32)us_word16;
    }


    for (l_loop = 0; l_loop < us_addrleninbytes; l_loop = l_loop + 2)
    {
        us_word16 = auc_dest_addr[l_loop];
        us_word16 = (oal_uint16)((us_word16 << 8) + auc_dest_addr[l_loop + 1]);
        ul_sum = ul_sum + (oal_uint32)us_word16;
    }

    ul_sum = ul_sum + (oal_uint32)us_protocol + (oal_uint32)(us_len+us_pad);

    while (ul_sum >> 16)
    {
        ul_sum = (ul_sum & 0xFFFF) + (ul_sum >> 16);
    }

    ul_sum = ~ul_sum;

    return ((oal_uint16) ul_sum);
}


OAL_STATIC oal_uint8 *hmac_proxysta_find_tlv(oal_uint8 *puc_buff,
                                             oal_uint16 us_buff_len,
                                             oal_uint8 uc_type,
                                             oal_uint8 uc_length)
{
    if (OAL_PTR_NULL == puc_buff)
    {
        return OAL_PTR_NULL;
    }
    while (us_buff_len > 0)
    {
        /* ????data????????????length????0 ?????????????? ?????????????????????? */
        if(*(puc_buff+1) == 0)
        {
            return OAL_PTR_NULL;
        }
        /* type??length?? ????????????TLV???? ??TLV????????????????  length????????8???????????? */
        if ((*puc_buff == uc_type) && (*(puc_buff+1) == uc_length) && (us_buff_len >= uc_length*8))
        {
            return puc_buff;
        }
        us_buff_len -= (*(puc_buff+1))*8;
        puc_buff += (*(puc_buff+1))*8;
    }
    /* ?????????????????? */
    return OAL_PTR_NULL;
}


OAL_STATIC oal_uint32  hmac_proxysta_find_ipv4_mac(hmac_vap_stru *pst_hmac_vap,
                                                   oal_uint8 *puc_ip_addr,
                                                   oal_uint8 *puc_mac_addr)
{
    oal_uint8   uc_hash = 0;
    hmac_proxysta_ipv4_hash_stru    *pst_hash_ipv4 = OAL_PTR_NULL;
    oal_dlist_head_stru             *pst_entry = OAL_PTR_NULL;

    if ( (OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == puc_ip_addr) )
    {
        OAM_ERROR_LOG2(0, OAM_SF_PROXYSTA, "{hmac_proxysta_find_ipv4_mac:: null param, mac_vap:%d ip_addr:%d.}",
            pst_hmac_vap, puc_ip_addr);
        return OAL_ERR_CODE_PTR_NULL;
    }
    if (OAL_PTR_NULL == pst_hmac_vap->pst_vap_proxysta)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_find_ipv4_mac:: vap_proxysta  null param.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ????HASH???? ????HASH???? */
    uc_hash = (oal_uint8)HMAC_PROXYSTA_CAL_IPV4_HASH(puc_ip_addr);
    /* ???????? ??????????MAC???? */
    oal_rw_lock_read_lock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_hmac_vap->pst_vap_proxysta->ast_map_ipv4_head[uc_hash]))
    {
        pst_hash_ipv4 = OAL_DLIST_GET_ENTRY(pst_entry, hmac_proxysta_ipv4_hash_stru, st_entry);
        /* ????IP???? */
        if (HMAC_PROXYSTA_MEMCMP_EQUAL == OAL_MEMCMP(pst_hash_ipv4->auc_ipv4, puc_ip_addr, ETH_TARGET_IP_ADDR_LEN))
        {
            oal_memcopy(puc_mac_addr, pst_hash_ipv4->auc_mac, WLAN_MAC_ADDR_LEN);
            /* ????????????MAP???????????? */
            pst_hash_ipv4->ul_last_active_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
            oal_rw_lock_read_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
            return OAL_SUCC;
        }
    }
    oal_rw_lock_read_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
    /* ???????????????? ???????? */
    return OAL_FAIL;
}


OAL_STATIC oal_uint32  hmac_proxysta_find_ipv6_mac(hmac_vap_stru *pst_hmac_vap,
                                                   oal_uint8 *puc_ip_addr,
                                                   oal_uint8 *puc_mac_addr)
{
    oal_uint8   uc_hash = 0;
    hmac_proxysta_ipv6_hash_stru    *pst_hash_ipv6 = OAL_PTR_NULL;
    oal_dlist_head_stru             *pst_entry = OAL_PTR_NULL;

    if ( (OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == puc_ip_addr) )
    {
        OAM_ERROR_LOG2(0, OAM_SF_PROXYSTA, "{hmac_proxysta_find_ipv6_mac:: null param, mac_vap:%d ip_addr:%d.}",
            pst_hmac_vap, puc_ip_addr);
        return OAL_ERR_CODE_PTR_NULL;
    }
    if (OAL_PTR_NULL == pst_hmac_vap->pst_vap_proxysta)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_find_ipv6_mac:: vap_proxysta  null param.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ????HASH???? ????HASH???? */
    uc_hash = (oal_uint8)HMAC_PROXYSTA_CAL_IPV6_HASH(puc_ip_addr);
    /* ???????? ??????????MAC???? */
    oal_rw_lock_read_lock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_hmac_vap->pst_vap_proxysta->ast_map_ipv6_head[uc_hash]))
    {
        pst_hash_ipv6 = OAL_DLIST_GET_ENTRY(pst_entry, hmac_proxysta_ipv6_hash_stru, st_entry);
        /* ????IP???? */
        if (HMAC_PROXYSTA_MEMCMP_EQUAL == OAL_MEMCMP(pst_hash_ipv6->auc_ipv6, puc_ip_addr, HMAC_PROXYSTA_IPV6_ADDR_LEN))
        {
            oal_memcopy(puc_mac_addr, pst_hash_ipv6->auc_mac, WLAN_MAC_ADDR_LEN);
            /* ????????????MAP???????????? */
            pst_hash_ipv6->ul_last_active_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
            oal_rw_lock_read_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
            return OAL_SUCC;
        }
    }
    oal_rw_lock_read_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
    /* ???????????????? ???????? */
    return OAL_FAIL;
}


OAL_STATIC oal_uint32  hmac_proxysta_find_unknow_mac(hmac_vap_stru *pst_hmac_vap,
                                                     oal_uint16 us_protocol,
                                                     oal_uint8 *puc_mac_addr)
{
    oal_uint8   uc_hash = 0;
    hmac_proxysta_unknow_hash_stru      *pst_hash_unknow = OAL_PTR_NULL;
    oal_dlist_head_stru                 *pst_entry = OAL_PTR_NULL;

    if ( OAL_PTR_NULL == pst_hmac_vap )
    {
        OAM_ERROR_LOG1(0, OAM_SF_PROXYSTA, "{hmac_proxysta_find_ipv4_mac:: null param, mac_vap:%d.}",
            pst_hmac_vap);
        return OAL_ERR_CODE_PTR_NULL;
    }
    if (OAL_PTR_NULL == pst_hmac_vap->pst_vap_proxysta)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_find_unknow_mac:: vap_proxysta  null param.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ????HASH???? ????HASH???? */
    uc_hash = (oal_uint8)HMAC_PROXYSTA_CAL_UNKNOW_HASH(us_protocol);
    /* ???????? ??????????MAC???? */
    oal_rw_lock_read_lock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_hmac_vap->pst_vap_proxysta->ast_map_unknow_head[uc_hash]))
    {
        pst_hash_unknow = OAL_DLIST_GET_ENTRY(pst_entry, hmac_proxysta_unknow_hash_stru, st_entry);
        /* ????IP???? */
        if (pst_hash_unknow->us_protocol == us_protocol)
        {
            oal_memcopy(puc_mac_addr, pst_hash_unknow->auc_mac, WLAN_MAC_ADDR_LEN);
            /* ????????????MAP???????????? */
            pst_hash_unknow->ul_last_active_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
            oal_rw_lock_read_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
            return OAL_SUCC;
        }
    }
    oal_rw_lock_read_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
    /* ???????????????? ???????? */
    return OAL_FAIL;
}


OAL_STATIC oal_uint32 hmac_proxysta_rx_arp_addr_replace(hmac_vap_stru *pst_hmac_vap,
                                                        mac_ether_header_stru *pst_ether_header,
                                                        oal_uint32 ul_pkt_len)
{
    oal_eth_arphdr_stru *pst_arp          = OAL_PTR_NULL;
    oal_uint8           *puc_eth_body     = OAL_PTR_NULL;
    oal_uint8           *puc_des_mac      = OAL_PTR_NULL;
    oal_bool_enum_uint8 en_is_mcast;
    oal_uint32          ul_contig_len;
    oal_uint8           *puc_oma          = OAL_PTR_NULL;
    oal_uint32          ul_ret = OAL_SUCC;

    /***************************************************************************/
    /*                      ARP Frame Format                                   */
    /* ----------------------------------------------------------------------- */
    /* |??????????????|????????????|??????|????????|????????|????????????|     */
    /* ----------------------------------------------------------------------- */
    /* | 6 (??????)   |6           |2     |2       |2       |1           |     */
    /* ----------------------------------------------------------------------- */
    /* |????????????|op|????????????????|??????IP????|??????????????|????IP????*/
    /* ----------------------------------------------------------------------- */
    /* | 1          |2 |6               |4           |6 (??????)    |4         */
    /* ----------------------------------------------------------------------- */
    /*                                                                         */
    /***************************************************************************/

    /* ?????????????? */
    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_ether_header))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PROXYSTA,
                       "{hmac_proxysta_rx_arp_addr_replace:: null param, mac_vap:%d ether_header:%d.}",
                       pst_hmac_vap, pst_ether_header);
        return OAL_ERR_CODE_PTR_NULL;
    }
    ul_contig_len = OAL_SIZEOF(mac_ether_header_stru);
    /* ??????????????mac???????? */
    puc_des_mac = pst_ether_header->auc_ether_dhost;
    puc_eth_body = (oal_uint8 *)(pst_ether_header + 1);

    /* ?????????????????????????????????? */
    en_is_mcast = ETHER_IS_MULTICAST(puc_des_mac);
    /* ARP ?????????? */
    pst_arp = (oal_eth_arphdr_stru *)puc_eth_body;
    ul_contig_len += OAL_SIZEOF(oal_eth_arphdr_stru);

    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_proxysta_rx_arp_addr_replace::The length of buf is invalid.}");
        return OAL_FAIL;
    }
    /*  ??????????????IP???? ????MAP?? ????????????MAC???? */
    puc_oma = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, WLAN_MAC_ADDR_LEN, OAL_TRUE);
    if (OAL_PTR_NULL == puc_oma)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_rx_arp_addr_replace::mem alloc oma ptr null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    ul_ret = hmac_proxysta_find_ipv4_mac(pst_hmac_vap, pst_arp->auc_ar_tip, puc_oma);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_psta_rx_arp_match_addr:: can't find mac addr of ip:%d:%d:%d:%d.}",
            pst_arp->auc_ar_tip[0], pst_arp->auc_ar_tip[1], pst_arp->auc_ar_tip[2], pst_arp->auc_ar_tip[3]);
        /* ???????? */
        OAL_MEM_FREE(puc_oma, OAL_TRUE);
        puc_oma = OAL_PTR_NULL;
        return ul_ret;
    }

    /* ????arp????????mac????????????MAC???? */
    oal_set_mac_addr(pst_arp->auc_ar_tha, puc_oma);
    /* ???????????????????????? ??????????APR?????????????????? */
    /* ????????????????ARP???????????????????????????????? */
    if (!en_is_mcast)
    {
        oal_set_mac_addr(puc_des_mac, puc_oma);
    }

    /* ???????? */
    OAL_MEM_FREE(puc_oma, OAL_TRUE);
    puc_oma = OAL_PTR_NULL;
    return OAL_SUCC;
}


OAL_STATIC oal_uint32 hmac_proxysta_rx_ip_addr_replace(hmac_vap_stru *pst_hmac_vap,
                                                       mac_ether_header_stru *pst_ether_header,
                                                       oal_uint32 ul_pkt_len)
{
    oal_ip_header_stru   *pst_ip_header    = OAL_PTR_NULL;
    oal_udp_header_stru  *pst_udp_header   = OAL_PTR_NULL;
    oal_dhcp_packet_stru *pst_dhcp_packet  = OAL_PTR_NULL;
    oal_uint8            *puc_eth_body     = OAL_PTR_NULL;
    oal_uint8            *puc_des_mac      = OAL_PTR_NULL;
    oal_uint16           us_ip_header_len = 0;
    oal_uint32           ul_contig_len = 0;
    oal_uint32           ul_ret = OAL_SUCC;
    oal_uint8            *puc_oma          = OAL_PTR_NULL;
    oal_bool_enum_uint8  en_is_mcast = OAL_FALSE;
    oal_uint8            *puc_ipv4  = OAL_PTR_NULL;
    oal_uint16           us_old_flag = 0;
    oal_uint32           ul_new_sum = 0;

    /* ?????????????? */
    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_ether_header))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PROXYSTA, "{hmac_proxysta_rx_ip_addr_replace::null param vap:%d ether_header:%d.}",
            pst_hmac_vap, pst_ether_header);
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_contig_len = OAL_SIZEOF(mac_ether_header_stru);
    /* ??????????????mac???????? */
    puc_des_mac = pst_ether_header->auc_ether_dhost;
    puc_eth_body = (oal_uint8 *)(pst_ether_header + 1);
    /* ?????????????????????????????????? */
    en_is_mcast = ETHER_IS_MULTICAST(puc_des_mac);
    /*************************************************************************/
    /*                      DHCP Frame Format                                */
    /* --------------------------------------------------------------------- */
    /* |????????        |   IP??         | UDP??           |DHCP????       | */
    /* --------------------------------------------------------------------- */
    /* | 14             |20              |8                | ????          | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    pst_ip_header = (oal_ip_header_stru *)puc_eth_body;

    /*************************************************************************/
    /*                    IP?????? (oal_ip_header_stru)                      */
    /* --------------------------------------------------------------------- */
    /* | ???? | ???????? | ???????? | ??????  |????  |????  |???????? |      */
    /* --------------------------------------------------------------------- */
    /* | 4bits|  4bits   | 1        | 2       | 2    |3bits | 13bits  |      */
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* | ?????? | ????        | ??????????| ????????SrcIp??|??????????DstIp??*/
    /* --------------------------------------------------------------------- */
    /* | 1      |  1 (17??UDP)| 2         | 4              | 4               */
    /* --------------------------------------------------------------------- */
    /*************************************************************************/

    ul_contig_len += OAL_SIZEOF(oal_ip_header_stru);
    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_proxysta_rx_ip_addr_replace::The length of buf is invalid.}");
        return OAL_FAIL;
    }
    /* IP?????????? */
    us_ip_header_len = pst_ip_header->us_ihl * 4;

    /* ??????UDP??????????DHCP?????????????????? */
    if (OAL_IPPROTO_UDP == pst_ip_header->uc_protocol)
    {
        pst_udp_header  = (oal_udp_header_stru *)((oal_uint8 *)pst_ip_header + us_ip_header_len);
        ul_contig_len += OAL_SIZEOF(oal_udp_header_stru);
        if (ul_pkt_len < ul_contig_len)
        {
            OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                "{hmac_proxysta_rx_ip_addr_replace::The length of buf is invalid.}");
            return OAL_FAIL;
        }
        /*************************************************************************/
        /*                      UDP ?? (oal_udp_header_stru)                     */
        /* --------------------------------------------------------------------- */
        /* |??????????SrcPort??|????????????DstPort??| UDP????    | UDP??????  | */
        /* --------------------------------------------------------------------- */
        /* | 2                 | 2                   |2           | 2          | */
        /* --------------------------------------------------------------------- */
        /*                                                                       */
        /*************************************************************************/
        /* DHCP request UDP Client SP = 68 (bootpc), DP = 67 (bootps) */
        /* Repeater STA??????DHCP REQUEST??????????DHCP SERVER??????????????ACK????
           ????REPEATER??????DHCP?????????????????????? ???????????????? */
/*lint -e778*/
        if ( DHCP_PORT_BOOTPS == OAL_HOST2NET_SHORT(pst_udp_header->dest) )
/*lint +e778*/
        {
            pst_dhcp_packet = (oal_dhcp_packet_stru *)(((oal_uint8 *)pst_udp_header) + OAL_SIZEOF(oal_udp_header_stru));
            ul_contig_len += OAL_SIZEOF(oal_dhcp_packet_stru);
            if (ul_pkt_len < ul_contig_len)
            {
                return OAL_FAIL;
            }
            /* ??????????????DHCP???????? ????????????????????????????????????ACK ????????????DHCP???????? ???????????????????????? */
            /* STA????????????????????????DHCP REQUEST(????DHCP????????????REPEATER????????????????)??
                ??????????????????DHCP REQUEST ???????????????????????????????????? */
            if (OAL_MEMCMP(mac_mib_get_StationID(&pst_hmac_vap->st_vap_base_info), pst_dhcp_packet->chaddr, WLAN_MAC_ADDR_LEN))
            {
                us_old_flag = pst_dhcp_packet->flags;
/*lint -e778*/
                pst_dhcp_packet->flags = OAL_NET2HOST_SHORT(DHCP_FLAG_BCAST);
/*lint +e778*/
                /* ??????????????UDP???????? */
                ul_new_sum = (oal_uint32)pst_udp_header->check;
                ul_new_sum += us_old_flag + (~(pst_dhcp_packet->flags) & 0XFFFF);
                ul_new_sum  = (ul_new_sum >> 16) + (ul_new_sum & 0XFFFF);
                pst_udp_header->check = (oal_uint16)((ul_new_sum >> 16) + ul_new_sum);
            }
            return OAL_SUCC;
        }
    }

    /* ????????IP????????????DHCP??????UDP?? ?????????????? */
    /* ????????????????????????proxysta??oma */
    if (en_is_mcast)      /* ?????????????????????????? */
    {
        return OAL_SUCC;
    }
    puc_oma = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, WLAN_MAC_ADDR_LEN, OAL_TRUE);
    if (OAL_PTR_NULL == puc_oma)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_rx_ip_addr_replace::mem alloc oma ptr null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    ul_ret = hmac_proxysta_find_ipv4_mac(pst_hmac_vap, (oal_uint8 *)(&pst_ip_header->ul_daddr), puc_oma);
    if (OAL_SUCC != ul_ret)
    {
        puc_ipv4 = (oal_uint8 *)(&pst_ip_header->ul_daddr);
        OAM_ERROR_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_rx_ip_addr_replace:: can't find mac addr of ip:%d:%d:%d:%d.}",
            puc_ipv4[0], puc_ipv4[1], puc_ipv4[2], puc_ipv4[3]);
        /* ???????? */
        OAL_MEM_FREE(puc_oma, OAL_TRUE);
        puc_oma = OAL_PTR_NULL;
        return ul_ret;
    }

    /* ????????????????????proxysta??vma */
    oal_set_mac_addr(puc_des_mac, puc_oma);
    /* ???????? */
    OAL_MEM_FREE(puc_oma, OAL_TRUE);
    puc_oma = OAL_PTR_NULL;
    return OAL_SUCC;
}


OAL_STATIC oal_uint32 hmac_proxysta_rx_ipv6_addr_replace(hmac_vap_stru *pst_hmac_vap,
                                                         mac_ether_header_stru *pst_ether_header,
                                                         oal_uint32 ul_pkt_len)
{
    oal_ipv6_header_stru    *pst_ipv6_hdr_data = OAL_PTR_NULL;
    oal_uint8           *puc_eth_body     = OAL_PTR_NULL;
    oal_uint8           *puc_des_mac      = OAL_PTR_NULL;
    oal_bool_enum_uint8 en_is_mcast = OAL_FALSE;
    oal_uint32          ul_contig_len = 0;
    oal_uint8           *puc_oma          = OAL_PTR_NULL;
    oal_uint32          ul_ret = OAL_SUCC;
    oal_uint16          *pus_ipv6 = OAL_PTR_NULL;

    /*************************************************************************/
    /*                      IPV6 Frame Format                                */
    /* --------------------------------------------------------------------- */
    /* |????????        |   IPV6??         | Next Frame Boady              | */
    /* --------------------------------------------------------------------- */
    /* | 14             |   40             |  ????                         | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    /* ?????????????? */
    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_ether_header))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PROXYSTA,
                       "{hmac_proxysta_rx_ipv6_addr_replace:: null param, mac_vap:%d ether_header:%d.}",
                       pst_hmac_vap, pst_ether_header);
        return OAL_ERR_CODE_PTR_NULL;
    }
    ul_contig_len = OAL_SIZEOF(mac_ether_header_stru);
    /* ??????????????mac???????? */
    puc_des_mac = pst_ether_header->auc_ether_dhost;
    puc_eth_body = (oal_uint8 *)(pst_ether_header + 1);

    /* ?????????????????????????????????? */
    en_is_mcast = ETHER_IS_MULTICAST(puc_des_mac);
    /* ??????????????????MAC?????????????? */
    if (en_is_mcast)
    {
        return OAL_SUCC;
    }
    /*************************************************************************/
    /*                   IPV6?????? (oal_ipv6_header_stru)                   */
    /* --------------------------------------------------------------------- */
    /* | ???? | Traffic Class |                 Flow label            |      */
    /* --------------------------------------------------------------------- */
    /* | 4bits|  8bits        |                 20bits                |      */
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* | Payload Length             | Next Header    |   Hop Limit    |      */
    /* --------------------------------------------------------------------- */
    /* | 2                          | 1              |   1            |      */
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* |                           Source Address                            */
    /* --------------------------------------------------------------------- */
    /* |                                 16                                  */
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* |                           Destination Address                       */
    /* --------------------------------------------------------------------- */
    /* |                                 16                                  */
    /* --------------------------------------------------------------------- */
    /*************************************************************************/
    pst_ipv6_hdr_data = (oal_ipv6_header_stru *)puc_eth_body;
    ul_contig_len += OAL_SIZEOF(oal_ipv6_header_stru);

    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_proxysta_rx_ipv6_addr_replace::The length of buf is invalid.}");
        return OAL_FAIL;
    }

    /*  ??????????????IP???? ????MAP?? ????????????MAC???? */
    puc_oma = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, WLAN_MAC_ADDR_LEN, OAL_TRUE);
    if (OAL_PTR_NULL == puc_oma)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_rx_ipv6_addr_replace::mem alloc oma ptr null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    ul_ret = hmac_proxysta_find_ipv6_mac(pst_hmac_vap, pst_ipv6_hdr_data->st_daddr.auc_ipv6_union_addr, puc_oma);
    if (OAL_SUCC != ul_ret)
    {
        pus_ipv6 = pst_ipv6_hdr_data->st_daddr.aus_ipv6_union_addr;
        OAM_ERROR_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_rx_ipv6_addr_replace:: can't find mac addr of ip:%d:%d:%d:%d.}",
            pus_ipv6[0], pus_ipv6[1], pus_ipv6[2], pus_ipv6[3]);
        OAM_ERROR_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_rx_ipv6_addr_replace:: can't find mac addr of ip:%d:%d:%d:%d.}",
            pus_ipv6[4], pus_ipv6[5], pus_ipv6[6], pus_ipv6[7]);
        /* ???????? */
        OAL_MEM_FREE(puc_oma, OAL_TRUE);
        puc_oma = OAL_PTR_NULL;
        return ul_ret;
    }

    /* ????????????????MAC */
    oal_set_mac_addr(puc_des_mac, puc_oma);
    /* ???????? */
    OAL_MEM_FREE(puc_oma, OAL_TRUE);
    puc_oma = OAL_PTR_NULL;
    return OAL_SUCC;
}


OAL_STATIC oal_uint32 hmac_proxysta_rx_unknow_addr_replace(hmac_vap_stru *pst_hmac_vap,
                                                           mac_ether_header_stru *pst_ether_header,
                                                           oal_uint32 ul_pkt_len)
{
    oal_uint8            *puc_des_mac      = OAL_PTR_NULL;
    oal_uint32           ul_contig_len = 0;
    oal_uint32           ul_ret = OAL_SUCC;
    oal_uint8            *puc_oma           = OAL_PTR_NULL;
    oal_bool_enum_uint8  en_is_mcast = OAL_FALSE;

    /* ?????????????? */
    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_ether_header))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PROXYSTA, "{hmac_proxysta_rx_unknow_addr_replace::null param vap:%d ether_header:%d device:%d.}",
            pst_hmac_vap, pst_ether_header);
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_contig_len = OAL_SIZEOF(mac_ether_header_stru);
    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_rx_unknow_addr_replace::::The length of buf:%d is less than mac_ether_header_stru.}", ul_pkt_len);
        return OAL_FAIL;
    }

    /* ??????????????mac???????? */
    puc_des_mac = pst_ether_header->auc_ether_dhost;
    /* ?????????????????????????????????? */
    en_is_mcast = ETHER_IS_MULTICAST(puc_des_mac);
    if (en_is_mcast)      /* ?????????????????????????? */
    {
        return OAL_SUCC;
    }
    puc_oma = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, WLAN_MAC_ADDR_LEN, OAL_TRUE);
    if (OAL_PTR_NULL == puc_oma)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_rx_unknow_addr_replace::mem alloc oma ptr null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    ul_ret = hmac_proxysta_find_unknow_mac(pst_hmac_vap, pst_ether_header->us_ether_type , puc_oma);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_rx_unknow_addr_replace:: can't find mac addr of unknow protocol:0x%x.}",
            pst_ether_header->us_ether_type);
        /* ???????? */
        OAL_MEM_FREE(puc_oma, OAL_TRUE);
        puc_oma = OAL_PTR_NULL;
        return ul_ret;
    }
    /* ??????????????????????????STA MAC???? */
    oal_set_mac_addr(puc_des_mac, puc_oma);

    /* ???????? */
    OAL_MEM_FREE(puc_oma, OAL_TRUE);
    puc_oma = OAL_PTR_NULL;
    return OAL_SUCC;
}


oal_uint32  hmac_proxysta_rx_process(oal_netbuf_stru *pst_buf, hmac_vap_stru *pst_hmac_vap)
{
    mac_ether_header_stru   *pst_ether_header;
    oal_uint16               us_ether_type;
    oal_uint32              ul_pkt_len = 0;
    oal_uint32              ul_ret = OAL_SUCC;

    if ((OAL_PTR_NULL == pst_buf) || (OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PROXYSTA, "{hmac_proxysta_rx_process:null ptr pst_buf=%x pst_hmac_vap=%x.}",
            pst_buf, pst_hmac_vap);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ??skb??data???????????????????? */
    oal_netbuf_push(pst_buf, ETHER_HDR_LEN);
    pst_ether_header = (mac_ether_header_stru *)OAL_NETBUF_HEADER(pst_buf);
    ul_pkt_len = OAL_NETBUF_LEN(pst_buf);
    /* ????skb??data???? */
    oal_netbuf_pull(pst_buf, ETHER_HDR_LEN);
    /* ???????????????????? PROXYSTA?????????????????????????????????????? */
    /******************************************/
    /*        Ethernet Frame Format           */
    /* -------------------------------------  */
    /* |Dst      MAC | Source MAC   | TYPE |  */
    /* -------------------------------------  */
    /* | 6           | 6            | 2    |  */
    /* -------------------------------------  */
    /*                                        */
    /******************************************/
    us_ether_type = pst_ether_header->us_ether_type;

    /* ether_type ????0x0600?????????? ?????? */
/*lint -e778*/
    if (HMAC_ETHERTYPE_PROTOCOL_START > OAL_HOST2NET_SHORT(us_ether_type) )
/*lint +e778*/
    {
        return OAL_SUCC;
    }
    /* IP?????????? */
/*lint -e778*/
    if (OAL_HOST2NET_SHORT(ETHER_TYPE_IP) == us_ether_type)
/*lint +e778*/
    {
        ul_ret = hmac_proxysta_rx_ip_addr_replace(pst_hmac_vap, pst_ether_header, ul_pkt_len);
        return ul_ret;
    }
    /* ARP ?????????? */
/*lint -e778*/
    else if (OAL_HOST2NET_SHORT(ETHER_TYPE_ARP) == us_ether_type)
/*lint +e778*/
    {
        ul_ret = hmac_proxysta_rx_arp_addr_replace(pst_hmac_vap, pst_ether_header, ul_pkt_len);
        return ul_ret;
    }
    /*icmpv6 ?????????? */
/*lint -e778*/
    else if (OAL_HOST2NET_SHORT(ETHER_TYPE_IPV6) == us_ether_type)
/*lint +e778*/
    {
        ul_ret = hmac_proxysta_rx_ipv6_addr_replace(pst_hmac_vap, pst_ether_header, ul_pkt_len);
        return ul_ret;
    }
    /* IPX ???????????? */
/*lint -e778*/
    else if (OAL_HOST2NET_SHORT(ETHER_TYPE_IPX) == us_ether_type)
/*lint +e778*/
    {
        /* TO BE DONE */
        return ul_ret;
    }
    /* APPLE TALK  & AARP???????????? */
/*lint -e778*/
    else if (OAL_HOST2NET_SHORT(ETHER_TYPE_AARP) == us_ether_type)
/*lint +e778*/
    {
        /* TO BE DONE */
        return ul_ret;
    }
    /* PPOE ???????????? */
/*lint -e778*/
    else if ( (OAL_HOST2NET_SHORT(ETHER_TYPE_PPP_DISC) == us_ether_type) ||
              (OAL_HOST2NET_SHORT(ETHER_TYPE_PPP_SES) == us_ether_type) )
    {
/*lint +e778*/
        /* TO BE DONE */
        return ul_ret;
    }
    /* ?????????????????? 0xe2ae 0xe2af??realtek?????????????????????????????????? */
/*lint -e778*/
    else if ( (OAL_HOST2NET_SHORT(ETHER_TYPE_PAE) == us_ether_type) ||
              (OAL_HOST2NET_SHORT(0xe2ae) == us_ether_type) ||
              (OAL_HOST2NET_SHORT(0xe2af) == us_ether_type) )
/*lint +e778*/
    {
        return OAL_SUCC;
    }
    /* ?????????????????????? */
    else
    {
        ul_ret = hmac_proxysta_rx_unknow_addr_replace(pst_hmac_vap, pst_ether_header, ul_pkt_len);
        return ul_ret;
    }
}


OAL_STATIC oal_uint32  hmac_proxysta_insert_ipv4_mac(hmac_vap_stru *pst_hmac_vap,
                                                     oal_uint8 *puc_ip_addr,
                                                     oal_uint8 *puc_src_mac)
{
    oal_uint8   uc_hash = 0;
    hmac_proxysta_ipv4_hash_stru    *pst_hash_ipv4 = OAL_PTR_NULL;
    hmac_proxysta_ipv4_hash_stru    *pst_hash_ipv4_new = OAL_PTR_NULL;
    oal_dlist_head_stru             *pst_entry = OAL_PTR_NULL;

    if ( (OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == puc_ip_addr) || (OAL_PTR_NULL == puc_src_mac) )
    {
        OAM_ERROR_LOG3(0, OAM_SF_PROXYSTA, "{hmac_proxysta_insert_ipv4_mac:: null param, mac_vap:%d ip_addr:%d src_mac.}",
            pst_hmac_vap, puc_ip_addr, puc_src_mac);
        return OAL_ERR_CODE_PTR_NULL;
    }
    if (OAL_PTR_NULL == pst_hmac_vap->pst_vap_proxysta)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_insert_ipv4_mac:: vap_proxysta  null param.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ????HASH???? ????HASH???? */
    uc_hash = HMAC_PROXYSTA_CAL_IPV4_HASH(puc_ip_addr);
    /* ???????? ????????????MAP????????????????IP */
    oal_rw_lock_read_lock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_hmac_vap->pst_vap_proxysta->ast_map_ipv4_head[uc_hash]))
    {
        pst_hash_ipv4 = OAL_DLIST_GET_ENTRY(pst_entry, hmac_proxysta_ipv4_hash_stru, st_entry);
        /* ????IP???? ????IP??????????MAC???????????? */
        if (HMAC_PROXYSTA_MEMCMP_EQUAL == OAL_MEMCMP(pst_hash_ipv4->auc_ipv4, puc_ip_addr, ETH_TARGET_IP_ADDR_LEN))
        {
            /* IP??????MAC?????? ????????MAC */
            if (HMAC_PROXYSTA_MEMCMP_EQUAL != OAL_MEMCMP(pst_hash_ipv4->auc_mac, puc_src_mac, WLAN_MAC_ADDR_LEN))
            {
                oal_set_mac_addr(pst_hash_ipv4->auc_mac, puc_src_mac);
            }
            /* ??????MAP???????????? */
            pst_hash_ipv4->ul_last_active_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
            oal_rw_lock_read_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
            return OAL_SUCC;
        }
    }
    oal_rw_lock_read_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);

    /* ???????????????? ??????????????????????????MAP?????? */
    /* ????????????????????????128???????????? */
    if (HMAC_PROXYSTA_MAP_MAX_NUM < (pst_hmac_vap->pst_vap_proxysta->uc_map_ipv4_num +
                                     pst_hmac_vap->pst_vap_proxysta->uc_map_ipv6_num +
                                     pst_hmac_vap->pst_vap_proxysta->uc_map_unknow_num) )
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_insert_ipv4_mac:: map num exceed max size: %d.}", HMAC_PROXYSTA_MAP_MAX_NUM);
        return OAL_SUCC;
    }
    pst_hash_ipv4_new = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(hmac_proxysta_ipv4_hash_stru), OAL_TRUE);
    if (OAL_PTR_NULL == pst_hash_ipv4_new)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_insert_ipv4_mac:: mem alloc null pointer.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* ????MAP?????????? */
    oal_memcopy(pst_hash_ipv4_new->auc_ipv4, puc_ip_addr, ETH_TARGET_IP_ADDR_LEN);
    oal_memcopy(pst_hash_ipv4_new->auc_mac, puc_src_mac, WLAN_MAC_ADDR_LEN);
    pst_hash_ipv4_new->ul_last_active_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
    /* ???????? */
    oal_rw_lock_write_lock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
    oal_dlist_add_head(&(pst_hash_ipv4_new->st_entry), &(pst_hmac_vap->pst_vap_proxysta->ast_map_ipv4_head[uc_hash]));
    pst_hmac_vap->pst_vap_proxysta->uc_map_ipv4_num ++;
    oal_rw_lock_write_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);

#ifdef _PRE_DEBUG_MODE
    OAM_WARNING_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
        "{hmac_proxysta_insert_ipv4_mac:: insert ipv4 map ip[%d:%d:%d:%d.}",
        puc_ip_addr[0], puc_ip_addr[1], puc_ip_addr[2], puc_ip_addr[3]);
    OAM_WARNING_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
        "{hmac_proxysta_insert_ipv4_mac:: insert ipv4 map mac[%x:%x:ff:ff:%x:%x.}",
        puc_src_mac[0], puc_src_mac[1], puc_src_mac[4], puc_src_mac[5]);
#endif

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  hmac_proxysta_insert_ipv6_mac(hmac_vap_stru *pst_hmac_vap,
                                                     oal_uint8 *puc_ip_addr,
                                                     oal_uint8 *puc_src_mac)
{
    oal_uint8   uc_hash = 0;
    hmac_proxysta_ipv6_hash_stru    *pst_hash_ipv6 = OAL_PTR_NULL;
    hmac_proxysta_ipv6_hash_stru    *pst_hash_ipv6_new = OAL_PTR_NULL;
    oal_dlist_head_stru             *pst_entry = OAL_PTR_NULL;

    if ( (OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == puc_ip_addr) || (OAL_PTR_NULL == puc_src_mac) )
    {
        OAM_ERROR_LOG3(0, OAM_SF_PROXYSTA, "{hmac_proxysta_insert_ipv6_mac:: null param, mac_vap:%d ip_addr:%d src_mac.}",
            pst_hmac_vap, puc_ip_addr, puc_src_mac);
        return OAL_ERR_CODE_PTR_NULL;
    }
    if (OAL_PTR_NULL == pst_hmac_vap->pst_vap_proxysta)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_insert_ipv6_mac:: vap_proxysta  null param.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ????HASH???? ????HASH???? */
    uc_hash = (oal_uint8)HMAC_PROXYSTA_CAL_IPV6_HASH(puc_ip_addr);
    /* ???????? ????????????MAP????????????????IP */
    oal_rw_lock_read_lock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_hmac_vap->pst_vap_proxysta->ast_map_ipv6_head[uc_hash]))
    {
        pst_hash_ipv6 = OAL_DLIST_GET_ENTRY(pst_entry, hmac_proxysta_ipv6_hash_stru, st_entry);
        /* ????IP???? ????IP??????????MAC???????????? */
        if (HMAC_PROXYSTA_MEMCMP_EQUAL == OAL_MEMCMP(pst_hash_ipv6->auc_ipv6, puc_ip_addr, HMAC_PROXYSTA_IPV6_ADDR_LEN))
        {
            /* IP??????MAC?????? ????????MAC */
            if (HMAC_PROXYSTA_MEMCMP_EQUAL != OAL_MEMCMP(pst_hash_ipv6->auc_mac, puc_src_mac, WLAN_MAC_ADDR_LEN))
            {
                oal_set_mac_addr(pst_hash_ipv6->auc_mac, puc_src_mac);
            }
            /* ??????MAP???????????? */
            pst_hash_ipv6->ul_last_active_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
            oal_rw_lock_read_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
            return OAL_SUCC;
        }
    }
    oal_rw_lock_read_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);

    /* ???????????????? ??????????????????????????MAP?????? */
    /* ????????????????????????128???????????? */
    if (HMAC_PROXYSTA_MAP_MAX_NUM < (pst_hmac_vap->pst_vap_proxysta->uc_map_ipv4_num +
                                     pst_hmac_vap->pst_vap_proxysta->uc_map_ipv6_num +
                                     pst_hmac_vap->pst_vap_proxysta->uc_map_unknow_num) )
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_insert_ipv6_mac:: map num exceed max size: %d.}", HMAC_PROXYSTA_MAP_MAX_NUM);
        return OAL_SUCC;
    }
    pst_hash_ipv6_new = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(hmac_proxysta_ipv6_hash_stru), OAL_TRUE);
    if (OAL_PTR_NULL == pst_hash_ipv6_new)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_insert_ipv6_mac:: mem alloc null pointer.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* ????MAP?????????? */
    oal_memcopy(pst_hash_ipv6_new->auc_ipv6, puc_ip_addr, HMAC_PROXYSTA_IPV6_ADDR_LEN);
    oal_memcopy(pst_hash_ipv6_new->auc_mac, puc_src_mac, WLAN_MAC_ADDR_LEN);
    pst_hash_ipv6_new->ul_last_active_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
    /* ???????? */
    oal_rw_lock_write_lock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
    oal_dlist_add_head(&(pst_hash_ipv6_new->st_entry), &(pst_hmac_vap->pst_vap_proxysta->ast_map_ipv6_head[uc_hash]));
    pst_hmac_vap->pst_vap_proxysta->uc_map_ipv6_num ++;
    oal_rw_lock_write_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);

#ifdef _PRE_DEBUG_MODE
    OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
    "{hmac_proxysta_insert_ipv6_mac:: ipv6 map number:%d.}", pst_hmac_vap->pst_vap_proxysta->uc_map_ipv6_num);
    OAM_WARNING_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
        "{hmac_proxysta_insert_ipv6_mac:: insert ipv6 map ip:0x%x-mac:0x%x.}",puc_ip_addr[15], puc_src_mac[5]);
#endif

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  hmac_proxysta_insert_unknow_mac(hmac_vap_stru *pst_hmac_vap,
                                                       oal_uint16 us_protocol,
                                                       oal_uint8 *puc_src_mac)
{
    oal_uint8   uc_hash = 0;
    hmac_proxysta_unknow_hash_stru      *pst_hash_unknow = OAL_PTR_NULL;
    hmac_proxysta_unknow_hash_stru      *pst_hash_unknow_new = OAL_PTR_NULL;
    oal_dlist_head_stru                 *pst_entry = OAL_PTR_NULL;

    if ( (OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == puc_src_mac) )
    {
        OAM_ERROR_LOG2(0, OAM_SF_PROXYSTA, "{hmac_proxysta_insert_unknow_mac:: null param, mac_vap:%d src_mac.}",
            pst_hmac_vap, puc_src_mac);
        return OAL_ERR_CODE_PTR_NULL;
    }
    if (OAL_PTR_NULL == pst_hmac_vap->pst_vap_proxysta)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_insert_unknow_mac:: vap_proxysta  null param.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* ????HASH???? ????HASH???? */
    uc_hash = (oal_uint8)HMAC_PROXYSTA_CAL_UNKNOW_HASH(us_protocol);
    /* ???????? ????????????MAP????????????????IP */
    oal_rw_lock_read_lock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_hmac_vap->pst_vap_proxysta->ast_map_unknow_head[uc_hash]))
    {
        pst_hash_unknow = OAL_DLIST_GET_ENTRY(pst_entry, hmac_proxysta_unknow_hash_stru, st_entry);
        /* ???????????? ??????????????????MAC???????????? */
        if (pst_hash_unknow->us_protocol == us_protocol)
        {
            /* ??????????MAC?????? ????????MAC */
            if (HMAC_PROXYSTA_MEMCMP_EQUAL != OAL_MEMCMP(pst_hash_unknow->auc_mac, puc_src_mac, WLAN_MAC_ADDR_LEN))
            {
                oal_set_mac_addr(pst_hash_unknow->auc_mac, puc_src_mac);
            }
            /* ??????MAP???????????? */
            pst_hash_unknow->ul_last_active_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
            oal_rw_lock_read_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
            return OAL_SUCC;
        }
    }
    oal_rw_lock_read_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);

    /* ???????????????? ??????????????????????????MAP?????? */
    /* ????????????????????????128???????????? */
    if (HMAC_PROXYSTA_MAP_MAX_NUM < (pst_hmac_vap->pst_vap_proxysta->uc_map_ipv4_num +
                                     pst_hmac_vap->pst_vap_proxysta->uc_map_ipv6_num +
                                     pst_hmac_vap->pst_vap_proxysta->uc_map_unknow_num) )
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_insert_unknow_mac:: map num exceed max size: %d.}", HMAC_PROXYSTA_MAP_MAX_NUM);
        return OAL_SUCC;
    }
    pst_hash_unknow_new = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(hmac_proxysta_unknow_hash_stru), OAL_TRUE);
    if (OAL_PTR_NULL == pst_hash_unknow_new)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_insert_unknow_mac:: mem alloc null pointer.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ????MAP?????????? */
    pst_hash_unknow_new->us_protocol = us_protocol;
    oal_memcopy(pst_hash_unknow_new->auc_mac, puc_src_mac, WLAN_MAC_ADDR_LEN);
    pst_hash_unknow_new->ul_last_active_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
    /* ???????? */
    oal_rw_lock_write_lock(&pst_hmac_vap->pst_vap_proxysta->st_lock);
    oal_dlist_add_head(&(pst_hash_unknow_new->st_entry), &(pst_hmac_vap->pst_vap_proxysta->ast_map_unknow_head[uc_hash]));
    pst_hmac_vap->pst_vap_proxysta->uc_map_unknow_num ++;
    oal_rw_lock_write_unlock(&pst_hmac_vap->pst_vap_proxysta->st_lock);

#ifdef _PRE_DEBUG_MODE
    OAM_WARNING_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
        "{hmac_proxysta_insert_unknow_mac:: insert unknow map protocol:0x%x-mac:%x:FF:FF:FF:%x:%x.}",
        us_protocol, puc_src_mac[0], puc_src_mac[4], puc_src_mac[5]);
#endif

    return OAL_SUCC;
}


OAL_STATIC oal_uint32 hmac_proxysta_tx_ip_addr_insert(hmac_vap_stru *pst_hmac_vap,
                                                      mac_ether_header_stru *pst_ether_header,
                                                      oal_uint32 ul_pkt_len)
{
    oal_ip_header_stru   *pst_ip_header    = OAL_PTR_NULL;
    oal_udp_header_stru  *pst_udp_header   = OAL_PTR_NULL;
    oal_dhcp_packet_stru *pst_dhcp_packet  = OAL_PTR_NULL;
    oal_uint8            *puc_eth_body     = OAL_PTR_NULL;
    oal_uint8            *puc_src_mac      = OAL_PTR_NULL;
    oal_uint8            *puc_proxysta_mac = OAL_PTR_NULL;
    oal_uint16           us_ip_header_len  = 0;
    oal_uint16           us_old_flag       = 0;
    oal_uint32           ul_contig_len     = 0;
    oal_uint32           ul_new_sum        = 0;
    oal_uint8            *puc_ip_addr      = OAL_PTR_NULL;

    /* ?????????????? */
    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_ether_header))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PROXYSTA, "{hmac_proxysta_rx_ip_addr_insert::null param vap:%d ether_header:%d.}",
            pst_hmac_vap, pst_ether_header);
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* Proxysta ??????MAC???? */
    puc_proxysta_mac = mac_mib_get_StationID(&pst_hmac_vap->st_vap_base_info);
    ul_contig_len = OAL_SIZEOF(mac_ether_header_stru);
    /* ????????????mac???????? */
    puc_src_mac = pst_ether_header->auc_ether_shost;
    puc_eth_body = (oal_uint8 *)(pst_ether_header + 1);
    /*************************************************************************/
    /*                      DHCP Frame Format                                */
    /* --------------------------------------------------------------------- */
    /* |????????        |   IP??         | UDP??           |DHCP????       | */
    /* --------------------------------------------------------------------- */
    /* | 14             |20              |8                | ????          | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    pst_ip_header = (oal_ip_header_stru *)puc_eth_body;

    /*************************************************************************/
    /*                    IP?????? (oal_ip_header_stru)                      */
    /* --------------------------------------------------------------------- */
    /* | ???? | ???????? | ???????? | ??????  |????  |????  |???????? |      */
    /* --------------------------------------------------------------------- */
    /* | 4bits|  4bits   | 1        | 2       | 2    |3bits | 13bits  |      */
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* | ?????? | ????        | ??????????| ????????SrcIp??|??????????DstIp??*/
    /* --------------------------------------------------------------------- */
    /* | 1      |  1 (17??UDP)| 2         | 4              | 4               */
    /* --------------------------------------------------------------------- */
    /*************************************************************************/

    ul_contig_len += OAL_SIZEOF(oal_ip_header_stru);
    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_tx_ip_addr_insert::The length of buf is less than the sum of mac_ether_header_stru and oal_ip_header_stru.}");
        return OAL_FAIL;
    }
    /* IP?????????? */
    us_ip_header_len = pst_ip_header->us_ihl * 4;

    /* ??????UDP??????????DHCP?????????????????? */
    if (OAL_IPPROTO_UDP == pst_ip_header->uc_protocol)
    {
        pst_udp_header  = (oal_udp_header_stru *)((oal_uint8 *)pst_ip_header + us_ip_header_len);
        ul_contig_len += OAL_SIZEOF(oal_udp_header_stru);
        if (ul_pkt_len < ul_contig_len)
        {
            OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                "{hmac_proxysta_tx_ip_addr_insert::The length of udp buf is invalid.}");
            return OAL_FAIL;
        }
        /*************************************************************************/
        /*                      UDP ?? (oal_udp_header_stru)                     */
        /* --------------------------------------------------------------------- */
        /* |??????????SrcPort??|????????????DstPort??| UDP????    | UDP??????  | */
        /* --------------------------------------------------------------------- */
        /* | 2                 | 2                   |2           | 2          | */
        /* --------------------------------------------------------------------- */
        /*                                                                       */
        /*************************************************************************/

        /* DHCP request UDP Client SP = 68 (bootpc), DP = 67 (bootps) */
        /* Repeater STA??????DHCP REQUEST??????????DHCP SERVER??????????????ACK???? ????REPEATER??????DHCP?????????????????????? ???????????????? */
/*lint -e778*/
        if (DHCP_PORT_BOOTPS == OAL_NET2HOST_SHORT(pst_udp_header->dest))
/*lint +e778*/
        {
            pst_dhcp_packet = (oal_dhcp_packet_stru *)(((oal_uint8 *)pst_udp_header) + OAL_SIZEOF(oal_udp_header_stru));
            ul_contig_len += OAL_SIZEOF(oal_dhcp_packet_stru);
            if (ul_pkt_len < ul_contig_len)
            {
                OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                    "{hmac_proxysta_tx_ip_addr_insert::The length of dhcp buf is invalid.}");
                return OAL_FAIL;
            }
            /* DHCP??????????????MAC???????? */
            oal_set_mac_addr(puc_src_mac, puc_proxysta_mac);
            /* ??????????????DHCP???????? ????????????????????????????????????ACK ????????????DHCP???????? ???????????????????????? */
            if (OAL_MEMCMP(puc_proxysta_mac, pst_dhcp_packet->chaddr, WLAN_MAC_ADDR_LEN))
            {
                us_old_flag = pst_dhcp_packet->flags;
/*lint -e778*/
                pst_dhcp_packet->flags = OAL_NET2HOST_SHORT(DHCP_FLAG_BCAST);
/*lint +e778*/
                /* ??????????????UDP???????? */
                ul_new_sum = (oal_uint32)pst_udp_header->check;
                ul_new_sum += us_old_flag + (~(pst_dhcp_packet->flags) & 0XFFFF);
                ul_new_sum  = (ul_new_sum >> 16) + (ul_new_sum & 0XFFFF);
                pst_udp_header->check = (oal_uint16)((ul_new_sum >> 16) + ul_new_sum);
            }
            return OAL_SUCC;
        }
    }

    puc_ip_addr = (oal_uint8 *)(&pst_ip_header->ul_saddr);
    /* ????????IP????????????DHCP??????UDP?? ?????????????? ??IP??????MAC??????????MA?????? ????MAP?????????????????????? */
    hmac_proxysta_insert_ipv4_mac(pst_hmac_vap, puc_ip_addr, puc_src_mac);
    /* ??????MAC???? */
    oal_set_mac_addr(puc_src_mac, puc_proxysta_mac);
    return OAL_SUCC;
}


OAL_STATIC oal_uint32 hmac_proxysta_tx_arp_addr_insert(hmac_vap_stru *pst_hmac_vap,
                                                       mac_ether_header_stru *pst_ether_header,
                                                       oal_uint32 ul_pkt_len)
{
    oal_eth_arphdr_stru *pst_arp          = OAL_PTR_NULL;
    oal_uint8           *puc_eth_body     = OAL_PTR_NULL;
    oal_uint8           *puc_src_mac      = OAL_PTR_NULL;
    oal_uint32          ul_contig_len;
    oal_uint8           *puc_proxysta_mac = OAL_PTR_NULL;

    /***************************************************************************/
    /*                      ARP Frame Format                                   */
    /* ----------------------------------------------------------------------- */
    /* |??????????????|????????????|??????|????????|????????|????????????|     */
    /* ----------------------------------------------------------------------- */
    /* | 6 (??????)   |6           |2     |2       |2       |1           |     */
    /* ----------------------------------------------------------------------- */
    /* |????????????|op|????????????????|??????IP????|??????????????|????IP????*/
    /* ----------------------------------------------------------------------- */
    /* | 1          |2 |6               |4           |6 (??????)    |4         */
    /* ----------------------------------------------------------------------- */
    /*                                                                         */
    /***************************************************************************/

    /* ?????????????? */
    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_ether_header))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PROXYSTA, "{hmac_proxysta_tx_arp_addr_insert:: null param, mac_vap:%d ether_header:%d.}",
            pst_hmac_vap, pst_ether_header);
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* ????proxysta??????MAC???? */
    puc_proxysta_mac = mac_mib_get_StationID(&pst_hmac_vap->st_vap_base_info);
    /* ??????????????mac???????? */
    ul_contig_len = OAL_SIZEOF(mac_ether_header_stru);
    puc_src_mac = pst_ether_header->auc_ether_shost;
    puc_eth_body = (oal_uint8 *)(pst_ether_header + 1);
    /* ARP ?????????? */
    pst_arp = (oal_eth_arphdr_stru *)puc_eth_body;
    ul_contig_len += OAL_SIZEOF(oal_eth_arphdr_stru);

    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_proxysta_tx_arp_addr_insert::The length of buf is invalid.}");
        return OAL_FAIL;
    }
    /* ??IPV4??ARP?????????? */
/*lint -e778*/
    if ((ETHER_ADDR_LEN != pst_arp->uc_ar_hln) || (ETHER_TYPE_IP != OAL_HOST2NET_SHORT(pst_arp->us_ar_pro)))
/*lint +e778*/
    {
        OAM_ERROR_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_proxysta_tx_arp_addr_insert::arp hln:%d, arp pro: %d ,not to process.}",
                       pst_arp->uc_ar_hln, pst_arp->us_ar_pro);
        return OAL_SUCC;
    }

    /*  ??????????????IP???? ????MAP?? ????????????MAC???? */
    hmac_proxysta_insert_ipv4_mac(pst_hmac_vap, pst_arp->auc_ar_sip, puc_src_mac);
    /* ????arp????????mac??????proxysta??MAC???? */
    oal_set_mac_addr(pst_arp->auc_ar_sha, puc_proxysta_mac);
    /* ???????????????????? */
    oal_set_mac_addr(puc_src_mac, puc_proxysta_mac);
    return OAL_SUCC;
}


OAL_STATIC oal_uint32 hmac_proxysta_tx_icmpv6_mac_replace(hmac_vap_stru *pst_hmac_vap,
                                                          oal_ipv6_header_stru *pst_ipv6_hdr,
                                                          oal_uint32 ul_pkt_len)
{
    oal_icmp6hdr_stru         *pst_icmp6hdr         = OAL_PTR_NULL;
    oal_eth_icmp6_lladdr_stru *pst_eth_icmp6_lladdr = OAL_PTR_NULL;
    oal_uint8                 *puc_option_buff      = OAL_PTR_NULL;
    oal_uint16                 us_check_sum = 0;
    oal_uint32                 ul_contig_len = 0;
    oal_bool_enum_uint8        en_packet_need_change = OAL_FALSE;

    /* ?????????????? */
    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_ipv6_hdr))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PROXYSTA, "{hmac_proxysta_tx_icmpv6_mac_replace:: null param hmac_vap[0x%x] ipv6_hdr[0x%x].}",
            pst_hmac_vap, pst_ipv6_hdr);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_icmp6hdr = (oal_icmp6hdr_stru *)(pst_ipv6_hdr+1);
    ul_contig_len = OAL_SIZEOF(oal_icmp6hdr_stru);
    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG3(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_tx_icmpv6_mac_replace::The length of buf is invalid ul_pkt_len[%d], ul_contig_len[%d] icmp6_type[%d].}",
            ul_pkt_len, ul_contig_len, pst_icmp6hdr->icmp6_type);
        return OAL_FAIL;
    }
    /* ??????????????????????????????????????????????????MAC???? */
    switch (pst_icmp6hdr->icmp6_type)
    {
        case OAL_NDISC_NEIGHBOUR_SOLICITATION:
        case OAL_NDISC_NEIGHBOUR_ADVERTISEMENT:
        {
            /* ???????????????? ???????? */
            ul_contig_len += OAL_IPV6_MAC_ADDR_LEN;
            if (ul_pkt_len < ul_contig_len)
            {
                OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                    "{hmac_proxysta_tx_icmpv6_mac_replace::neighbor-ad buf len is invalid.}");
                return OAL_FAIL;
            }
            en_packet_need_change = OAL_TRUE;
            /* ????????????option???????? */
            puc_option_buff = (oal_uint8 *)(pst_icmp6hdr) + OAL_SIZEOF(oal_icmp6hdr_stru) + OAL_IPV6_MAC_ADDR_LEN;
            break;
        }
        case OAL_NDISC_ROUTER_SOLICITATION:
        {
            en_packet_need_change = OAL_TRUE;
            /* ????????????option???????? */
            puc_option_buff = (oal_uint8 *)(pst_icmp6hdr) + OAL_SIZEOF(oal_icmp6hdr_stru);
            break;
        }
        case OAL_NDISC_ROUTER_ADVERTISEMENT:
        {
            /* ???????????????? ???????? */
            ul_contig_len += PROTOCOL_ICMPV6_ROUTER_AD_OFFLOAD;
            if (ul_pkt_len < ul_contig_len)
            {
                OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                    "{hmac_proxysta_tx_icmpv6_mac_replace::router-ad buf len is invalid.}");
                return OAL_FAIL;
            }
            en_packet_need_change = OAL_TRUE;
            /* ????????????option???????? */
            puc_option_buff = (oal_uint8 *)(pst_icmp6hdr) + OAL_SIZEOF(oal_icmp6hdr_stru) + PROTOCOL_ICMPV6_ROUTER_AD_OFFLOAD;
            break;
        }
        case OAL_NDISC_REDIRECT:
        {
            /* ???????????????? ???????? */
            ul_contig_len += (OAL_IPV6_MAC_ADDR_LEN + OAL_IPV6_MAC_ADDR_LEN);
            if (ul_pkt_len < ul_contig_len)
            {
                OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                    "{hmac_proxysta_tx_icmpv6_mac_replace::redirect buf len is invalid.}");
                return OAL_FAIL;
            }
            en_packet_need_change = OAL_TRUE;
            /* ????????????option???????? ????????????2??IP address???? */
            puc_option_buff = (oal_uint8 *)(pst_icmp6hdr) + OAL_SIZEOF(oal_icmp6hdr_stru) + OAL_IPV6_MAC_ADDR_LEN + OAL_IPV6_MAC_ADDR_LEN;
            break;
        }
        /* ????????????????????????MAC???? */
        default:
            break;
    }

    if (en_packet_need_change)
    {
        /* Source MAC??????type??1 Length????1 */
        pst_eth_icmp6_lladdr = (oal_eth_icmp6_lladdr_stru *)hmac_proxysta_find_tlv(puc_option_buff, (oal_uint16)(ul_pkt_len-ul_contig_len), 1, 1);
        if (OAL_PTR_NULL == pst_eth_icmp6_lladdr)
        {
#ifdef _PRE_DEBUG_MOE
            OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                "{hmac_proxysta_tx_icmpv6_mac_replace:: frame[%d] no source addr.}", pst_icmp6hdr->icmp6_type);
#endif
            return OAL_SUCC;
        }
        /* ???????????????????????? */
        oal_set_mac_addr(pst_eth_icmp6_lladdr->uc_addr, mac_mib_get_StationID(&pst_hmac_vap->st_vap_base_info));
        us_check_sum = hmac_proxysta_cal_checksum((oal_uint16)OAL_IPPROTO_ICMPV6,
                                                  pst_ipv6_hdr->us_payload_len,
                                                  pst_ipv6_hdr->st_saddr.auc_ipv6_union_addr,
                                                  pst_ipv6_hdr->st_daddr.auc_ipv6_union_addr,
                                                  OAL_IPV6_MAC_ADDR_LEN,
                                                  (oal_uint8 *)pst_icmp6hdr);

        pst_icmp6hdr->icmp6_cksum = OAL_HOST2NET_SHORT(us_check_sum);
    }
    return OAL_SUCC;
}


OAL_STATIC oal_uint32 hmac_proxysta_tx_ipv6_addr_insert(hmac_vap_stru *pst_hmac_vap,
                                                        mac_ether_header_stru *pst_ether_header,
                                                        oal_uint32 ul_pkt_len)
{
    oal_ipv6_header_stru    *pst_ipv6_hdr_data = OAL_PTR_NULL;
    oal_uint8           *puc_eth_body     = OAL_PTR_NULL;
    oal_uint8           *puc_src_mac      = OAL_PTR_NULL;
    oal_uint8           *puc_proxysta_mac = OAL_PTR_NULL;
    oal_uint32          ul_contig_len = 0;

    /*************************************************************************/
    /*                      IPV6 Frame Format                                */
    /* --------------------------------------------------------------------- */
    /* |????????        |   IPV6??         | Next Frame Boady              | */
    /* --------------------------------------------------------------------- */
    /* | 14             |   40             |  ????                         | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    /* ?????????????? */
    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_ether_header))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PROXYSTA, "{hmac_proxysta_tx_ipv6_addr_insert:: null param, mac_vap:%d ether_header:%d.}",
                       pst_hmac_vap, pst_ether_header);
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* ????PROXYSTA ??????MAC???? */
    puc_proxysta_mac = mac_mib_get_StationID(&pst_hmac_vap->st_vap_base_info);
    ul_contig_len = OAL_SIZEOF(mac_ether_header_stru);
    /* ??????????????mac???????? */
    puc_src_mac= pst_ether_header->auc_ether_shost;
    puc_eth_body = (oal_uint8 *)(pst_ether_header + 1);
    /*************************************************************************/
    /*                   IPV6?????? (oal_ipv6_header_stru)                   */
    /* --------------------------------------------------------------------- */
    /* | ???? | Traffic Class |                 Flow label            |      */
    /* --------------------------------------------------------------------- */
    /* | 4bits|  8bits        |                 20bits                |      */
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* | Payload Length             | Next Header    |   Hop Limit    |      */
    /* --------------------------------------------------------------------- */
    /* | 2                          | 1              |   1            |      */
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* |                           Source Address                            */
    /* --------------------------------------------------------------------- */
    /* |                                 16                                  */
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* |                           Destination Address                       */
    /* --------------------------------------------------------------------- */
    /* |                                 16                                  */
    /* --------------------------------------------------------------------- */
    /*************************************************************************/
    pst_ipv6_hdr_data = (oal_ipv6_header_stru *)puc_eth_body;
    ul_contig_len += OAL_SIZEOF(oal_ipv6_header_stru);

    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_proxysta_tx_ipv6_addr_insert::The length of buf is invalid.}");
        return OAL_FAIL;
    }
    /* ??????ICMPV6??????????????????????????MAC???? */
    if (PROTOCOL_ICMPV6 == pst_ipv6_hdr_data->uc_nexthdr)
    {
        hmac_proxysta_tx_icmpv6_mac_replace(pst_hmac_vap, pst_ipv6_hdr_data, ul_pkt_len-ul_contig_len);
    }
    /*  ??????????????IP???? ????MAP?? ????????????MAC???? */
    hmac_proxysta_insert_ipv6_mac(pst_hmac_vap, pst_ipv6_hdr_data->st_saddr.auc_ipv6_union_addr, puc_src_mac);
    oal_set_mac_addr(puc_src_mac, puc_proxysta_mac);
    return OAL_SUCC;
}


OAL_STATIC oal_uint32 hmac_proxysta_tx_unknow_addr_insert(hmac_vap_stru *pst_hmac_vap,
                                                          mac_ether_header_stru *pst_ether_header,
                                                          oal_uint32 ul_pkt_len)
{
    oal_uint8            *puc_src_mac      = OAL_PTR_NULL;
    oal_uint8            *puc_proxysta_mac = OAL_PTR_NULL;
    oal_uint32           ul_contig_len = 0;

    /* ?????????????? */
    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_ether_header))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PROXYSTA, "{hmac_proxysta_tx_unknow_addr_insert::null param vap:%d ether_header:%d device:%d.}",
            pst_hmac_vap, pst_ether_header);
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_contig_len = OAL_SIZEOF(mac_ether_header_stru);
    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
            "{hmac_proxysta_tx_unknow_addr_insert::::The length of buf:%d is less than mac_ether_header_stru.}", ul_pkt_len);
        return OAL_FAIL;
    }
    /* ????PROXYSTA??????MAC???? */
    puc_proxysta_mac = mac_mib_get_StationID(&pst_hmac_vap->st_vap_base_info);
    /* ????????????mac???????? */
    puc_src_mac= pst_ether_header->auc_ether_shost;

    hmac_proxysta_insert_unknow_mac(pst_hmac_vap, pst_ether_header->us_ether_type , puc_src_mac);
    /* ??????????????????????????STA MAC???? */
    oal_set_mac_addr(puc_src_mac, puc_proxysta_mac);
    return OAL_SUCC;
}


oal_uint32 hmac_proxysta_tx_process(oal_netbuf_stru *pst_buf, hmac_vap_stru *pst_hmac_vap)
{
    mac_ether_header_stru  *pst_ether_header;
    oal_uint16             us_ether_type = 0;
    oal_uint32             ul_pkt_len = 0;

    if ((OAL_PTR_NULL == pst_buf) || (OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PROXYSTA, "{hmac_proxysta_tx_process::null param: netbuf:%d vap:%d.}",
                       pst_buf, pst_hmac_vap);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_ether_header = (mac_ether_header_stru *)OAL_NETBUF_HEADER(pst_buf);
    /* ?????????? ???????????????? */
    ul_pkt_len = OAL_NETBUF_LEN(pst_buf);
    us_ether_type = pst_ether_header->us_ether_type;

    /* ?????????????????????????? */
/*lint -e778*/
    if (OAL_HOST2NET_SHORT(ETHER_TYPE_IP) == us_ether_type)
/*lint +e778*/
    {
        return hmac_proxysta_tx_ip_addr_insert(pst_hmac_vap, pst_ether_header, ul_pkt_len);
    }
    /* ARP ?????????? */
/*lint -e778*/
    else if (OAL_HOST2NET_SHORT(ETHER_TYPE_ARP) == us_ether_type)
/*lint +e778*/
    {
        return hmac_proxysta_tx_arp_addr_insert(pst_hmac_vap, pst_ether_header, ul_pkt_len);
    }
    /*icmpv6 ?????????? */
/*lint -e778*/
    else if (OAL_HOST2NET_SHORT(ETHER_TYPE_IPV6) == us_ether_type)
/*lint +e778*/
    {
        return hmac_proxysta_tx_ipv6_addr_insert(pst_hmac_vap, pst_ether_header, ul_pkt_len);
    }
    /* IPX ???????????? */
/*lint -e778*/
    else if (OAL_HOST2NET_SHORT(ETHER_TYPE_IPX) == us_ether_type)
/*lint +e778*/
    {
        /* TO BE DONE */
        return OAL_SUCC;
    }
    /* APPLE TALK  & AARP???????????? */
/*lint -e778*/
    else if (OAL_HOST2NET_SHORT(ETHER_TYPE_AARP) == us_ether_type)
/*lint +e778*/
    {
        /* TO BE DONE */
        return OAL_SUCC;
    }
    /* PPOE ???????????? */
/*lint -e778*/
    else if ( (OAL_HOST2NET_SHORT(ETHER_TYPE_PPP_DISC) == us_ether_type) ||
              (OAL_HOST2NET_SHORT(ETHER_TYPE_PPP_SES) == us_ether_type) )
/*lint +e778*/
    {
        /* TO BE DONE */
        return OAL_SUCC;
    }
    /* ?????????????????? 0xe2ae 0xe2af??realtek??????????????????????????????????????  ?????? */
/*lint -e778*/
    else if ( (OAL_HOST2NET_SHORT(ETHER_TYPE_PAE) == us_ether_type) ||
              (OAL_HOST2NET_SHORT(0xe2ae) == us_ether_type) ||
              (OAL_HOST2NET_SHORT(0xe2af) == us_ether_type) )
/*lint +e778*/
    {
        return OAL_SUCC;
    }
    /* ?????????????????????? */
    else
    {
        return hmac_proxysta_tx_unknow_addr_insert(pst_hmac_vap, pst_ether_header, ul_pkt_len);
    }
}

#endif  //_PRE_WLAN_FEATURE_SINGLE_PROXYSTA

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
