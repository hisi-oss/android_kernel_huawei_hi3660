


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "oam_ext_if.h"
#include "frw_ext_if.h"
#include "hal_ext_if.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "mac_regdomain.h"
#include "mac_vap.h"

//#include "dmac_reset.h"

#include "hmac_resource.h"
#include "hmac_device.h"
#include "hmac_vap.h"
#include "hmac_rx_filter.h"

#include "hmac_chan_mgmt.h"
#include "hmac_dfs.h"
#ifdef _PRE_WLAN_CHIP_TEST
#include "hmac_test_main.h"
#endif

#include "hmac_data_acq.h"
#include "hmac_rx_filter.h"

#include "hmac_hcc_adapt.h"

#include "hmac_dfs.h"
#include "hmac_config.h"
#include "hmac_resource.h"
#include "hmac_device.h"
#include "hmac_scan.h"
#include "hmac_rx_data.h"
#include "hmac_hcc_adapt.h"
#include "hmac_dfx.h"
#include "hmac_protection.h"

#ifdef _PRE_WLAN_TCP_OPT
#include "mac_data.h"
#include "hmac_tcp_opt_struc.h"
#include "hmac_tcp_opt.h"
#endif

#if ((_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE) &&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION))
#include <linux/fb.h>
#include <linux/list.h>
#include "plat_pm_wlan.h"
#endif
#ifdef _PRE_WLAN_FEATURE_CAR
#include "hmac_car.h"
#endif

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#include "hisi_customize_wifi.h"
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_DEVICE_C

/*****************************************************************************
  2 ????????????
*****************************************************************************/
/*lint -e578*//*lint -e19*/
oal_module_license("GPL");
/*lint +e578*//*lint +e19*/

/*****************************************************************************
  3 ????????
*****************************************************************************/



oal_uint32  hmac_device_exit_etc(mac_board_stru *pst_board, mac_chip_stru *pst_chip, hmac_device_stru *pst_hmac_device)
{
    mac_device_stru              *pst_device;
    oal_uint32                    ul_return;
    hmac_vap_stru                *pst_vap;
    mac_cfg_down_vap_param_stru   st_down_vap;
    oal_uint8                     uc_vap_idx;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint32                    ul_ret;
#endif

    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_device_exit_etc::pst_hmac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ???????????????? */
    hmac_scan_exit_etc(pst_hmac_device);

#ifdef _PRE_WLAN_FEATURE_CAR
    hmac_car_exit(pst_hmac_device);
#endif

#ifdef _PRE_WLAN_FEATURE_PKT_MEM_OPT
    hmac_pkt_mem_opt_exit_etc(pst_hmac_device);
#endif

    pst_device = pst_hmac_device->pst_device_base_info;
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_device_exit_etc::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ???????????? */
#if ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) && (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE))
#ifdef CONFIG_HAS_EARLYSUSPEND
    unregister_early_suspend(&pst_hmac_device->early_suspend);
#endif
#endif

    /* ????????vap????????HMAC????????????VAP????????HMAC?? */
    uc_vap_idx = pst_device->uc_cfg_vap_id;
    pst_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_idx);

    if (OAL_PTR_NULL == pst_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_device_exit_etc::pst_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_return = hmac_config_del_vap_etc(&pst_vap->st_vap_base_info,
                                 OAL_SIZEOF(mac_cfg_down_vap_param_stru),
                                 (oal_uint8 *)&st_down_vap);
    if (ul_return != OAL_SUCC)
    {
        OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_device_exit_etc::hmac_config_del_vap_etc failed[%d].}",ul_return);
        return ul_return;
    }

    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        /* ????????????????1????????????????vap?????????? */
        pst_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_device_exit_etc::mac_res_get_hmac_vap failed vap_idx[%u].}",uc_vap_idx);
            continue;
        }

        ul_return  = hmac_vap_destroy_etc(pst_vap);
        if (OAL_SUCC != ul_return)
        {
            OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_device_exit_etc::hmac_vap_destroy_etc failed[%d].}",ul_return);
            return ul_return;
        }
        pst_device->auc_vap_id[uc_vap_idx] = 0;
    }

    /*?????????????? ???? ????????????*/
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    ul_ret = mac_device_exit_etc(pst_device);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{mac_chip_exit_etc::p_device_destroy_fun failed[%d].}", ul_ret);

        return ul_ret;
    }
#endif

    /* ????????mac device?????????? */
    pst_hmac_device->pst_device_base_info = OAL_PTR_NULL;

    return OAL_SUCC;
}

#if 0

oal_uint32  hmac_device_exit_etc(mac_device_stru *pst_device)
{
    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_device_exit_etc::func enter.}");

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_device_exit_etc::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_device->uc_vap_num = 0;
    pst_device->uc_sta_num = 0;
    pst_device->st_p2p_info.uc_p2p_device_num   = 0;
    pst_device->st_p2p_info.uc_p2p_goclient_num = 0;
    mac_res_free_dev_etc(pst_device->uc_device_id);

#if 0
    pst_device->en_device_state = OAL_FALSE;
#else
    mac_device_set_state_etc(pst_device, OAL_FALSE);
#endif

    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_device_exit_etc::func out.}");

    return OAL_SUCC;
}
#endif


OAL_STATIC oal_uint32  hmac_chip_exit(mac_board_stru *pst_board, mac_chip_stru *pst_chip)
{
    hmac_device_stru  *pst_hmac_device;
    oal_uint32         ul_ret;
    oal_uint8          uc_device;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_chip || OAL_PTR_NULL == pst_board))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_chip_exit::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (uc_device = 0; uc_device < pst_chip->uc_device_nums; uc_device++)
    {
         pst_hmac_device = hmac_res_get_mac_dev_etc(pst_chip->auc_device_id[uc_device]);

         /* ?????????? ???????? */
         hmac_res_free_mac_dev_etc(pst_chip->auc_device_id[uc_device]);

         ul_ret = hmac_device_exit_etc(pst_board, pst_chip, pst_hmac_device);
         if (OAL_SUCC != ul_ret)
         {
             OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_chip_exit::hmac_device_exit_etc failed[%d].}", ul_ret);
             return ul_ret;
         }
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    ul_ret = mac_chip_exit_etc(pst_board, pst_chip);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_chip_exit::mac_chip_exit_etc failed[%d].}", ul_ret);
        return ul_ret;
    }
#endif

    return OAL_SUCC;
}


oal_uint32  hmac_board_exit_etc(mac_board_stru *pst_board)
{
    oal_uint8        uc_chip_idx;
    oal_uint32       ul_ret;
    oal_uint8        uc_chip_id_bitmap;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_board))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_board_exit_etc::pst_board null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_chip_id_bitmap = pst_board->uc_chip_id_bitmap;
    while (0 != uc_chip_id_bitmap)
    {
        /* ????????????????1????????????????chip?????????? */
        uc_chip_idx = oal_bit_find_first_bit_one_byte(uc_chip_id_bitmap);
        if (OAL_UNLIKELY(uc_chip_idx >= WLAN_CHIP_MAX_NUM_PER_BOARD))
        {
            OAM_ERROR_LOG2(0, OAM_SF_ANY, "{hmac_board_exit_etc::invalid uc_chip_idx[%d] uc_chip_id_bitmap=%d.}",
                           uc_chip_idx, uc_chip_id_bitmap);
            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }

        ul_ret = hmac_chip_exit(pst_board, &(pst_board->ast_chip[uc_chip_idx]));
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_board_exit_etc::mac_chip_exit_etc failed[%d].}", ul_ret);
            return ul_ret;
        }

        /* ??????????bitmap?? */
        oal_bit_clear_bit_one_byte(&uc_chip_id_bitmap, uc_chip_idx);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        /* ??????????bitmap?? */
        oal_bit_clear_bit_one_byte(&pst_board->uc_chip_id_bitmap, uc_chip_idx);
#endif
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /*????????????????*/
    mac_board_exit_etc(pst_board);
#endif

    return OAL_SUCC;
}


OAL_STATIC oal_uint32 hmac_cfg_vap_init(mac_device_stru *pst_device)
{
    oal_int8             ac_vap_netdev_name[MAC_NET_DEVICE_NAME_LENGTH];
#if defined(_PRE_PLAT_FEATURE_CUSTOMIZE) && (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    oal_int8             ac_chip_id_cfg[CHIPID_CFG_LEN];
    oal_int8             ac_vap_band_name[MAC_BAND_CAP_NAME_LENGTH];
    oal_int8            *puc_str;
#endif
    oal_uint32           ul_ret;
    hmac_vap_stru       *pst_vap;

    /* ??????????????????????????vap??????vap???????????????? */
    /*lint -e413*/
    ul_ret = mac_res_alloc_hmac_vap(&pst_device->uc_cfg_vap_id,
                                       OAL_OFFSET_OF(hmac_vap_stru, st_vap_base_info));
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_device->uc_cfg_vap_id, OAM_SF_ANY, "{hmac_cfg_vap_init::mac_res_alloc_hmac_vap failed[%d].}",ul_ret);
        return ul_ret;
    }
    /*lint +e413*/

    pst_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_device->uc_cfg_vap_id);
    if (OAL_PTR_NULL == pst_vap)
    {
        OAM_WARNING_LOG0(pst_device->uc_cfg_vap_id, OAM_SF_ANY, "{hmac_cfg_vap_init::pst_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ??hmac_vap_stru??????????????????0 */
    OAL_MEMZERO(pst_vap, OAL_SIZEOF(hmac_vap_stru));

    {
    mac_cfg_add_vap_param_stru  st_param = {0};       /* ????????VAP?????????? */
    st_param.en_vap_mode = WLAN_VAP_MODE_CONFIG;
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    st_param.bit_11ac2g_enable = OAL_TRUE;
    st_param.bit_disable_capab_2ght40 = OAL_FALSE;
#endif
    ul_ret = hmac_vap_init_etc(pst_vap,
                               pst_device->uc_chip_id,
                               pst_device->uc_device_id,
                               pst_device->uc_cfg_vap_id,
                               &st_param);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_device->uc_cfg_vap_id, OAM_SF_ANY, "{hmac_cfg_vap_init::hmac_vap_init_etc failed[%d].}",ul_ret);
        return ul_ret;
    }
    }

    /* ????vap??id????0??????????????????chip????????????????vap????????0,1 */
#if defined(_PRE_PLAT_FEATURE_CUSTOMIZE) && (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    if(OAL_PTR_NULL == hwifi_get_chip_id_cfg(pst_device->uc_chip_id))
    {
        /* ?????????????????????????????????? */
        OAL_SPRINTF(ac_vap_netdev_name, MAC_NET_DEVICE_NAME_LENGTH, "Hisilicon%d", pst_device->uc_chip_id);
    }
    else
    {
        oal_memcopy(ac_chip_id_cfg, hwifi_get_chip_id_cfg(pst_device->uc_chip_id), CHIPID_CFG_LEN);
        /* ???????????????????? */
        puc_str = OAL_STRSTR(ac_chip_id_cfg, "\n");
        if(puc_str != OAL_PTR_NULL)
        {
            *puc_str = '\0';
        }
        puc_str = OAL_STRSTR(ac_chip_id_cfg, ",");
        if(puc_str != OAL_PTR_NULL)
        {
            *puc_str = '\0';
            if (OAL_STRLEN(ac_chip_id_cfg) >= MAC_NET_DEVICE_NAME_LENGTH)
            {
                OAM_WARNING_LOG1(pst_device->uc_cfg_vap_id, OAM_SF_ANY, "{hmac_cfg_vap_init::input dev name too long: %d.}", OAL_STRLEN(ac_chip_id_cfg));
                return OAL_ERR_CODE_INVALID_CONFIG;
            }
            /* ?????????????????? \0, ????????????ac_chip_id_cfg?????????????????? */
            OAL_SPRINTF(ac_vap_netdev_name, MAC_NET_DEVICE_NAME_LENGTH, "%s", ac_chip_id_cfg);
            if(puc_str + 1 != OAL_PTR_NULL)
            {
                if (OAL_STRLEN(puc_str + 1) >= MAC_BAND_CAP_NAME_LENGTH)
                {
                    OAM_WARNING_LOG1(pst_device->uc_cfg_vap_id, OAM_SF_ANY, "{hmac_cfg_vap_init::input band name too long: %d.}", OAL_STRLEN(puc_str + 1));
                    return OAL_ERR_CODE_INVALID_CONFIG;
                }
                /* chip???????????????????????????????????? */
                OAL_SPRINTF(ac_vap_band_name, MAC_BAND_CAP_NAME_LENGTH, "%s", puc_str+1);
#ifdef _PRE_WLAN_PRODUCT_1151V200
                if (!oal_strcmp("2G", ac_vap_band_name))
                {
                    pst_device->en_band_cap = WLAN_BAND_CAP_2G;
                }
                else
                {
                    pst_device->en_band_cap = WLAN_BAND_CAP_5G;
                }
            }
            else
            {
                if (1 == pst_device->uc_chip_id)
                {
                    pst_device->en_band_cap = WLAN_BAND_CAP_5G;
                }
                else
                {
                    pst_device->en_band_cap = WLAN_BAND_CAP_2G;
                }
#endif
            }
        }
        else /* ?????????????????????????? */
        {
            OAL_SPRINTF(ac_vap_netdev_name, MAC_NET_DEVICE_NAME_LENGTH, "Hisilicon%d", pst_device->uc_chip_id);
#ifdef _PRE_WLAN_PRODUCT_1151V200
            if (1 == pst_device->uc_chip_id)
            {
                pst_device->en_band_cap = WLAN_BAND_CAP_5G;
            }
            else
            {
                pst_device->en_band_cap = WLAN_BAND_CAP_2G;
            }
#endif
        }
    }
#else
    OAL_SPRINTF(ac_vap_netdev_name, MAC_NET_DEVICE_NAME_LENGTH, "Hisilicon%d", pst_device->uc_chip_id);
#endif

    ul_ret = hmac_vap_creat_netdev_etc(pst_vap, ac_vap_netdev_name, (oal_int8 *)(pst_device->auc_hw_addr));
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_device->uc_cfg_vap_id, OAM_SF_ANY, "{hmac_cfg_vap_init::hmac_vap_creat_netdev_etc failed[%d].}",ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
extern oal_bool_enum g_wlan_pm_switch_etc;

oal_void  hmac_do_suspend_action_etc(mac_device_stru    *pst_mac_device, oal_uint8  uc_in_suspend)
{
    hmac_device_stru        *pst_hmac_device;
    oal_uint32               ul_ret;
    mac_vap_stru            *pst_cfg_mac_vap;
    mac_cfg_suspend_stru     st_suspend;
    oal_uint32               ul_is_wlan_poweron = OAL_TRUE;

    pst_hmac_device = hmac_res_get_mac_dev_etc(pst_mac_device->uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_WARNING_LOG0(pst_mac_device->uc_cfg_vap_id, OAM_SF_ANY, "{hmac_do_suspend_action_etc::pst_hmac_device null.}");
        return ;
    }

    oal_spin_lock(&pst_hmac_device->st_suspend_lock);

    pst_mac_device->uc_in_suspend   = uc_in_suspend;

    pst_cfg_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->uc_cfg_vap_id);
    if (OAL_PTR_NULL == pst_cfg_mac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_device->uc_cfg_vap_id, OAM_SF_ANY, "{hmac_do_suspend_action_etc::pst_vap null.}");
        oal_spin_unlock(&pst_hmac_device->st_suspend_lock);
        return ;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    ul_is_wlan_poweron = wlan_pm_is_poweron_etc();
#endif

    /* ????host??????????device??????????????????????????????device */
    if (g_wlan_pm_switch_etc && ul_is_wlan_poweron)
    {
        st_suspend.uc_in_suspend        = uc_in_suspend;

        if ((OAL_TRUE == uc_in_suspend)
#ifdef _PRE_WLAN_FEATURE_WAPI
        && (OAL_TRUE != pst_hmac_device->pst_device_base_info->uc_wapi)
#endif
            )
        {
            pst_hmac_device->pst_device_base_info->uc_arpoffload_switch = OAL_TRUE;
            st_suspend.uc_arpoffload_switch = OAL_TRUE;
        }
        else
        {
            pst_hmac_device->pst_device_base_info->uc_arpoffload_switch = OAL_FALSE;
            st_suspend.uc_arpoffload_switch = OAL_FALSE;
        }
        hmac_wake_lock();
        /***************************************************************************
            ????????DMAC??, ??????????????????DMAC
        ***************************************************************************/
        ul_ret = hmac_config_send_event_etc(pst_cfg_mac_vap, WLAN_CFGID_SUSPEND_ACTION_SYN, OAL_SIZEOF(mac_cfg_suspend_stru), (oal_uint8 *)&st_suspend);
        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_WARNING_LOG1(0, OAM_SF_CFG, "{hmac_suspend_action::hmac_config_send_event_etc failed[%d]}",ul_ret);
        }
        hmac_wake_unlock();
    }
    oal_spin_unlock(&pst_hmac_device->st_suspend_lock);
}

#ifdef CONFIG_HAS_EARLYSUSPEND

oal_void hmac_early_suspend(struct early_suspend *early_sup)
{
    hmac_device_stru    *pst_hmac_device;

    pst_hmac_device = OAL_CONTAINER_OF(early_sup, hmac_device_stru, early_suspend);
    hmac_do_suspend_action_etc(pst_hmac_device->pst_device_base_info,OAL_TRUE);
}


oal_void hmac_late_resume(struct early_suspend *early_sup)
{
    hmac_device_stru    *pst_hmac_device;

    pst_hmac_device = OAL_CONTAINER_OF(early_sup,hmac_device_stru, early_suspend);
    hmac_do_suspend_action_etc(pst_hmac_device->pst_device_base_info,OAL_FALSE);
}
#endif
#endif

oal_uint32 hmac_send_evt2wal_etc(mac_vap_stru *pst_mac_vap, oal_uint8 uc_evtid, oal_uint8 *puc_evt, oal_uint32 ul_evt_len)
{
    frw_event_mem_stru         *pst_event_mem;
    frw_event_stru             *pst_event;
    oal_uint32                  ul_ret;

    pst_event_mem = FRW_EVENT_ALLOC((oal_uint16)ul_evt_len);
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_mgmt_scan_req_exception::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ???????? */
    pst_event = frw_get_event_stru(pst_event_mem);

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_CTX,
                       uc_evtid,
                       (oal_uint16)ul_evt_len,
                       FRW_EVENT_PIPELINE_STAGE_0,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    oal_memcopy((oal_void *)pst_event->auc_event_data, (oal_void *)puc_evt, ul_evt_len);

    /* ???????? */
    ul_ret = frw_event_dispatch_event_etc(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);
    return ul_ret;
}

oal_uint32 hmac_config_host_dev_init_etc(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
#if defined (_PRE_WLAN_FEATURE_20_40_80_COEXIST) || defined (_PRE_WLAN_FEATURE_M2S)
    mac_device_stru     *pst_mac_device;
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    oal_uint32           ul_loop = 0;
#endif
#endif
#ifdef _PRE_WLAN_FEATURE_PKT_MEM_OPT
    hmac_device_stru    *pst_hmac_device;
#endif

    if(OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_device_init_etc:: pst_mac_device NULL pointer!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#if defined (_PRE_WLAN_FEATURE_20_40_80_COEXIST) || defined (_PRE_WLAN_FEATURE_M2S)
    pst_mac_device = mac_res_get_dev_etc(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_device_init_etc:: pst_mac_device[%d] NULL pointer!}", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    for (ul_loop = 0; ul_loop < MAC_MAX_SUPP_CHANNEL; ul_loop++)
    {
        pst_mac_device->st_ap_channel_list[ul_loop].us_num_networks = 0;
        pst_mac_device->st_ap_channel_list[ul_loop].en_ch_type      = MAC_CH_TYPE_NONE;
    }
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_PKT_MEM_OPT
    pst_hmac_device = hmac_res_get_mac_dev_etc(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_config_host_dev_init_etc::pst_hmac_device[%] null!}", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    hmac_pkt_mem_opt_init_etc(pst_hmac_device);
#endif

    /* TBD ??????????????????????????hmac_device_stru???????? */

    return OAL_SUCC;
}


oal_uint32 hmac_config_host_dev_exit_etc(mac_vap_stru *pst_mac_vap)
{
#ifdef _PRE_WLAN_FEATURE_PKT_MEM_OPT
    hmac_device_stru *pst_hmac_device = hmac_res_get_mac_dev_etc(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_config_host_dev_exit_etc::pst_hmac_device[%] null!}", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    hmac_pkt_mem_opt_exit_etc(pst_hmac_device);
#endif

    return OAL_SUCC;
}


oal_uint32  hmac_device_init_etc(oal_uint8 *puc_device_id, mac_chip_stru *pst_chip)
{
    oal_uint8            uc_dev_id;
    mac_device_stru     *pst_mac_device;
    hmac_device_stru    *pst_hmac_device;
    oal_uint32           ul_ret;
    oal_uint32           ul_loop = 0;

    /*????????mac device??????*/
    ul_ret = mac_res_alloc_hmac_dev_etc(&uc_dev_id);
    if(OAL_UNLIKELY(ul_ret != OAL_SUCC))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_device_init_etc::mac_res_alloc_dmac_dev_etc failed[%d].}", ul_ret);

        return OAL_FAIL;
    }

    /* ????mac device?????????? */
    pst_mac_device = mac_res_get_dev_etc(uc_dev_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
       OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_device_init_etc::pst_device null.}");

       return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = mac_device_init_etc(pst_mac_device, pst_chip->ul_chip_ver, pst_chip->uc_chip_id, uc_dev_id);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{hmac_device_init_etc::mac_device_init_etc failed[%d], chip_ver[0x%x].}", ul_ret, pst_chip->ul_chip_ver);

        mac_res_free_dev_etc(uc_dev_id);
        return ul_ret;
    }

    /* ????hmac device???? */
    if(OAL_UNLIKELY(hmac_res_alloc_mac_dev_etc(uc_dev_id) != OAL_SUCC))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_device_init_etc::hmac_res_alloc_mac_dev_etc failed.}");
        return OAL_FAIL;
    }

    /* ????hmac device???????????????????? */
    pst_hmac_device = hmac_res_get_mac_dev_etc(uc_dev_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_device_init_etc::pst_hmac_device[%] null!}", uc_dev_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ???????????? */
    OAL_MEMZERO(pst_hmac_device, OAL_SIZEOF(hmac_device_stru));

    pst_hmac_device->pst_device_base_info = pst_mac_device;

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    oal_spin_lock_init(&pst_hmac_device->st_suspend_lock);
#ifdef CONFIG_HAS_EARLYSUSPEND
    pst_hmac_device->early_suspend.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN + 20;
    pst_hmac_device->early_suspend.suspend = hmac_early_suspend;
    pst_hmac_device->early_suspend.resume  = hmac_late_resume;
    register_early_suspend(&pst_hmac_device->early_suspend);
#endif
#endif

    /* ?????????????? */
    hmac_scan_init_etc(pst_hmac_device);

#ifdef _PRE_WLAN_FEATURE_PKT_MEM_OPT
    hmac_pkt_mem_opt_init_etc(pst_hmac_device);
#endif

    /* ??????P2P ???????? */
    OAL_WAIT_QUEUE_INIT_HEAD(&(pst_hmac_device->st_netif_change_event));
#ifdef _PRE_WLAN_TCP_OPT
    pst_hmac_device->sys_tcp_tx_ack_opt_enable = DEFAULT_TX_TCP_ACK_OPT_ENABLE;
    pst_hmac_device->sys_tcp_rx_ack_opt_enable = DEFAULT_RX_TCP_ACK_OPT_ENABLE;

#endif

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    for (ul_loop = 0; ul_loop < MAC_MAX_SUPP_CHANNEL; ul_loop++)
    {
        pst_mac_device->st_ap_channel_list[ul_loop].us_num_networks = 0;
        pst_mac_device->st_ap_channel_list[ul_loop].en_ch_type      = MAC_CH_TYPE_NONE;
    }
#endif

    /* ??????device????rx tx BA???????? */
#ifndef _PRE_WLAN_FEATURE_AMPDU_VAP
    pst_mac_device->uc_rx_ba_session_num = 0;
    pst_mac_device->uc_tx_ba_session_num = 0;
#endif
    /* ??????????CHIP????????????device id */
    *puc_device_id = uc_dev_id;

    /* ????vap??????*/
    ul_ret = hmac_cfg_vap_init(pst_mac_device);
    if(OAL_UNLIKELY(ul_ret != OAL_SUCC))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_chip_init::hmac_cfg_vap_init failed[%d].}", ul_ret);
        return OAL_FAIL;
    }

#ifdef _PRE_WLAN_FEATURE_DFS
    hmac_dfs_init_etc(pst_mac_device);
#endif

#if 0
    /* dev????????????????????????wal????cfg80211??????????????offload???????????? */
    pst_mac_vap = (mac_vap_stru  *)mac_res_get_mac_vap(pst_mac_device->uc_cfg_vap_id);
    hmac_send_evt2wal_etc(pst_mac_vap, HMAC_HOST_CTX_EVENT_SUB_TYPE_INIT, OAL_PTR_NULL, 0);
#endif


    return OAL_SUCC;
}


#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
extern oal_uint8  g_auc_mac_device_radio_cap[];
#endif //#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE

OAL_STATIC oal_uint32  hmac_chip_init(mac_chip_stru *pst_chip, oal_uint8 uc_chip_id)
{
    oal_uint8  uc_device;
    oal_uint32 ul_ret;
    oal_uint8  uc_device_max;

    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_chip_init::func enter.}");

    pst_chip->uc_chip_id = uc_chip_id;

    /* CHIP???????? oal_get_chip_version*/
    pst_chip->ul_chip_ver = oal_chip_get_version_etc();

    /* OAL????????????device???? */
    uc_device_max = oal_chip_get_device_num_etc(pst_chip->ul_chip_ver);
    if (0 == uc_device_max)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_chip_init::device max num is zero.}");
        return OAL_FAIL;
    }

    if (uc_device_max > WLAN_SERVICE_DEVICE_MAX_NUM_PER_CHIP)
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{hmac_chip_init::device max num is %d,more than %d.}", uc_device_max, WLAN_SERVICE_DEVICE_MAX_NUM_PER_CHIP);
        return OAL_FAIL;
    }

    for (uc_device = 0; uc_device < uc_device_max; uc_device++)
    {
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
        if (MAC_DEVICE_DISABLE == g_auc_mac_device_radio_cap[uc_device])
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_chip_init::mac device id[%d] disable.}", uc_device);
            continue;
        }
#endif //#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
        /* hmac device?????????? */
        ul_ret = hmac_device_init_etc(&pst_chip->auc_device_id[uc_device], pst_chip);

        if(OAL_UNLIKELY(ul_ret != OAL_SUCC))
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_chip_init::hmac_device_init_etc failed[%d].}", ul_ret);
            return OAL_FAIL;
        }
    }

    mac_chip_init_etc(pst_chip, uc_device_max);

    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_chip_init::func out.}");

    return OAL_SUCC;
}


oal_uint32  hmac_board_init_etc(mac_board_stru *pst_board)
{
    oal_uint8               uc_chip;
    oal_uint32              ul_ret;
	oal_uint32              ul_chip_max_num;

    mac_board_init_etc();

    /* chip??????????????PCIe????????????; */
    ul_chip_max_num = oal_bus_get_chip_num_etc();

    for (uc_chip = 0; uc_chip < ul_chip_max_num; uc_chip++)
    {
        ul_ret = hmac_chip_init(&pst_board->ast_chip[uc_chip], uc_chip);
        if (OAL_SUCC != ul_ret)
        {
             OAM_WARNING_LOG2(0, OAM_SF_ANY, "{hmac_init_event_process_etc::hmac_chip_init failed[%d], uc_chip_id[%d].}", ul_ret, uc_chip);
             return OAL_FAIL;
        }

        oal_bit_set_bit_one_byte(&pst_board->uc_chip_id_bitmap, uc_chip);
    }
    return OAL_SUCC;
}
#else

oal_uint32  hmac_device_init_etc(oal_uint8  uc_device_id, mac_chip_stru *pst_dst_chip)
{
    mac_device_stru     *pst_mac_device;
    hmac_device_stru    *pst_hmac_device;
    oal_uint32           ul_ret;
    oal_uint32           ul_loop = 0;

    if(OAL_UNLIKELY(mac_res_alloc_hmac_dev_etc(uc_device_id) != OAL_SUCC))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_device_init_etc::mac_res_alloc_hmac_dev_etc failed.}");
        return OAL_FAIL;
    }

    /* ????mac device?????????? */
    pst_mac_device = mac_res_get_dev_etc(uc_device_id);

    /* ????hmac device???? */
    if(OAL_UNLIKELY(hmac_res_alloc_mac_dev_etc(uc_device_id) != OAL_SUCC))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_device_init_etc::hmac_res_alloc_mac_dev_etc failed.}");
        return OAL_FAIL;
    }

    /* ????hmac device???????????????????? */
    pst_hmac_device = hmac_res_get_mac_dev_etc(uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_device_init_etc::pst_hmac_device[%d] null!}", uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ???????????? */
    OAL_MEMZERO(pst_hmac_device, OAL_SIZEOF(hmac_device_stru));

    pst_hmac_device->pst_device_base_info = pst_mac_device;

    /* ?????????????? */
    hmac_scan_init_etc(pst_hmac_device);

#ifdef _PRE_WLAN_FEATURE_CAR
    hmac_car_init(pst_hmac_device);
#endif

    /* ??????P2P ???????? */
    OAL_WAIT_QUEUE_INIT_HEAD(&(pst_hmac_device->st_netif_change_event));
#ifdef _PRE_WLAN_TCP_OPT
    pst_hmac_device->sys_tcp_tx_ack_opt_enable = DEFAULT_TX_TCP_ACK_OPT_ENABLE;
    pst_hmac_device->sys_tcp_rx_ack_opt_enable = DEFAULT_RX_TCP_ACK_OPT_ENABLE;

#endif

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    for (ul_loop = 0; ul_loop < MAC_MAX_SUPP_CHANNEL; ul_loop++)
    {
        pst_mac_device->st_ap_channel_list[ul_loop].us_num_networks = 0;
        pst_mac_device->st_ap_channel_list[ul_loop].en_ch_type      = MAC_CH_TYPE_NONE;
    }
#endif

#ifndef _PRE_WLAN_FEATURE_AMPDU_VAP
    /* ??????device????rx tx BA???????? */
    pst_mac_device->uc_rx_ba_session_num = 0;
    pst_mac_device->uc_tx_ba_session_num = 0;
#endif
    /* ????vap??????*/
    ul_ret = hmac_cfg_vap_init(pst_mac_device);
    if(OAL_UNLIKELY(ul_ret != OAL_SUCC))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_chip_init::hmac_cfg_vap_init failed[%d].}", ul_ret);
        return OAL_FAIL;
    }

#ifdef _PRE_WLAN_FEATURE_DFS
    mac_dfs_init(pst_mac_device);
    hmac_dfs_init_etc(pst_mac_device);
#endif

    return OAL_SUCC;
}



OAL_STATIC oal_uint32  hmac_chip_init(mac_chip_stru *pst_chip)
{
    oal_uint8  uc_device;
    oal_uint32 ul_ret;

    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_chip_init::func enter.}");

    for (uc_device = 0; uc_device < pst_chip->uc_device_nums; uc_device++)
    {
        /* hmac device?????????? */
        ul_ret = hmac_device_init_etc(pst_chip->auc_device_id[uc_device], pst_chip);
        if(OAL_UNLIKELY(ul_ret != OAL_SUCC))
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_chip_init::hmac_device_init_etc failed[%d].}", ul_ret);
            return OAL_FAIL;
        }

#if 0
        /* ????vap????????HMAC?? */
        ul_ret = hmac_cfg_vap_init(mac_res_get_dev_etc(uc_dev_id));
        if(OAL_UNLIKELY(ul_ret != OAL_SUCC))
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_chip_init::hmac_cfg_vap_init failed[%d].}", ul_ret);
            return OAL_FAIL;
        }
#endif /*mac??????????????????*/
    }

    //mac_chip_init_etc(pst_dst_chip, pst_src_chip->uc_device_nums);

    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_chip_init::func out.}");

    return OAL_SUCC;
}


oal_uint32  hmac_board_init_etc(oal_uint32 ul_chip_max_num)
{
    oal_uint8              uc_chip;
    oal_uint32             ul_ret;

    /* dmac???? */
    //mac_board_init_etc();

    for (uc_chip = 0; uc_chip < ul_chip_max_num; uc_chip++)
    {
        ul_ret = hmac_chip_init(&g_pst_mac_board->ast_chip[uc_chip]);
        if (OAL_SUCC != ul_ret)
        {
             OAM_WARNING_LOG2(0, OAM_SF_ANY, "{hmac_board_init_etc::hmac_chip_init failed[%d], uc_chip_id[%d].}", ul_ret, uc_chip);
             return OAL_FAIL;
        }
        /* dmac???? */
        //oal_bit_set_bit_one_byte(&g_st_mac_board.uc_chip_id_bitmap, uc_chip);
    }

    return OAL_SUCC;
}
#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

