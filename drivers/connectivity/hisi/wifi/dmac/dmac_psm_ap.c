    


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "oal_net.h"
#include "wlan_spec.h"
#include "mac_frame.h"
#include "mac_vap.h"
#include "mac_device.h"
#include "dmac_vap.h"
#include "dmac_main.h"
#include "dmac_user.h"
#include "dmac_psm_ap.h"
#include "dmac_uapsd.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_rx_data.h"
#include "hal_ext_if.h"
#include "dmac_blockack.h"
#include "dmac_tx_complete.h"
#ifdef _PRE_WLAN_FEATURE_P2P
#include "dmac_p2p.h"
#endif
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_PSM_AP_C
/*****************************************************************************
  2 ????????????
*****************************************************************************/


/*****************************************************************************
  3 ????????
*****************************************************************************/
extern oal_uint32  dmac_send_sys_event(
                mac_vap_stru                     *pst_mac_vap,
                wlan_cfgid_enum_uint16            en_cfg_id,
                oal_uint16                        us_len,
                oal_uint8                        *puc_param);
extern oal_uint32  dmac_encap_beacon(
                dmac_vap_stru               *pst_dmac_vap,
                oal_uint8                   *puc_beacon_buf,
                oal_uint16                  *pus_beacon_len);


OAL_INLINE oal_void dmac_psm_set_more_data(oal_netbuf_stru *pst_net_buf)
{
    mac_tx_ctl_stru     *pst_tx_ctrl;
    mac_ieee80211_frame_stru    *pst_frame_hdr;

    pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);
    pst_frame_hdr = mac_get_cb_frame_hdr(pst_tx_ctrl);
    pst_frame_hdr->st_frame_control.bit_more_data = 0x01;
}


oal_void dmac_psm_set_local_bitmap(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_uint8 uc_bitmap_flg)
{
    oal_uint16          us_user_assoc_id;
    oal_uint8           uc_tim_byte_idx;
    oal_uint8           uc_tim_bit_mask;
    oal_uint8           uc_tim_offset;
    oal_uint8           uc_PVBitmap_len;
    oal_uint8           uc_tim_min_offset;
    oal_uint8           uc_tim_max_offset;
    oal_uint8           uc_index;

    if (OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_set_local_bitmap::param null.}");
        return;
    }
    /***************************************************************************
     ---------------------------------------------------------------------------
     |TIM bitmap len |Bitmap Control            |Partial Virtual Bitmap|
     ---------------------------------------------------------------------------
     |1              |1 (bit1-7=offset bit0=BMC)|1~251                 |
     ---------------------------------------------------------------------------
    ***************************************************************************/

    /* the Partial Virtual Bitmap field consists of octets numbered N1 to N2
       of the traffic indication virtual bitmap, where N1 is the largest even
       number such that bits numbered 1 to (N1 * 8) - 1 in the bitmap are all
       0 and N2 is the smallest number such that bits numbered (N2 + 1) * 8 to
       2007 in the bitmap are all 0. In this  case, the Bitmap Offset subfield
       value contains the number N1/2 */
    uc_PVBitmap_len  = pst_dmac_vap->puc_tim_bitmap[0];
    uc_tim_offset    = 2 + (pst_dmac_vap->puc_tim_bitmap[1] & (oal_uint8)(~BIT0));

    /* ???????? */
    if (uc_PVBitmap_len + uc_tim_offset > pst_dmac_vap->uc_tim_bitmap_len)
    {
        OAM_ERROR_LOG3(0, OAM_SF_PWR, "{dmac_psm_set_local_bitmap::tim_offset[%d] + len[%d] >= bitmap_len[%d].}",
                       uc_tim_offset, uc_PVBitmap_len, pst_dmac_vap->uc_tim_bitmap_len);
        OAL_MEMZERO(pst_dmac_vap->puc_tim_bitmap, pst_dmac_vap->uc_tim_bitmap_len);
        /* TIM bitmap len is default 1*/
        pst_dmac_vap->puc_tim_bitmap[0] = 1;
        uc_PVBitmap_len = 1;
    }

    /* ????????????????????Bitmap Control??bit0??
       ????????????????id??????????Partial Virtual Bitmap?????????????????????? */
    if (OAL_TRUE == pst_dmac_user->st_user_base_info.en_is_multi_user)
    {
        uc_tim_byte_idx          = 1;
        uc_tim_bit_mask          = (oal_uint8)(BIT0);
    }
    else
    {
        us_user_assoc_id         = pst_dmac_user->st_user_base_info.us_assoc_id;
        uc_tim_byte_idx          = 2 + (oal_uint8)(us_user_assoc_id >> 3);
        uc_tim_bit_mask          = (oal_uint8)(BIT0 << (us_user_assoc_id & 0x07));
    }
    if (uc_tim_byte_idx >= pst_dmac_vap->uc_tim_bitmap_len)
    {
        OAM_ERROR_LOG3(0, OAM_SF_PWR, "{dmac_psm_set_local_bitmap::usr[%d] tim_byte_idx[%d] >= bitmap_len[%d].}",
                       pst_dmac_user->st_user_base_info.us_assoc_id, uc_tim_byte_idx, pst_dmac_vap->uc_tim_bitmap_len);
        return;
    }
    /* ??????????bit???? */
    if (0 == uc_bitmap_flg)
    {
        pst_dmac_vap->puc_tim_bitmap[uc_tim_byte_idx] &= (oal_uint8)(~uc_tim_bit_mask);
    }
    else
    {
        pst_dmac_vap->puc_tim_bitmap[uc_tim_byte_idx] |= (oal_uint8)uc_tim_bit_mask;
    }

    /* ??????????????????????dtim */
    if (1 == uc_tim_byte_idx)
    {
        return;
    }
    uc_tim_min_offset = OAL_MIN(uc_tim_byte_idx, uc_tim_offset);
    uc_tim_max_offset = OAL_MAX(uc_tim_byte_idx, uc_tim_offset + uc_PVBitmap_len - 1);
    /* ????????????0??????tim_offset(??????????)?????????????????????????????????????????????? */
    uc_tim_offset     = 2;
    for (uc_index = uc_tim_min_offset; uc_index <= uc_tim_max_offset; uc_index++)
    {
        if (0 != pst_dmac_vap->puc_tim_bitmap[uc_index])
        {
            uc_tim_offset = uc_index & (~1);
            break;
        }
    }

    /* ????????????0??????????PVBitmap_len */
    for (uc_index = uc_tim_max_offset; uc_index > uc_tim_offset; uc_index--)
    {
        if (0 != pst_dmac_vap->puc_tim_bitmap[uc_index])
        {
            break;
        }
    }
    /*????PVBitmap_len??Bitmap Control(bit1-bit7????offset??bit0????BMC */
    pst_dmac_vap->puc_tim_bitmap[0] = (uc_index - uc_tim_offset) + 1;
    pst_dmac_vap->puc_tim_bitmap[1] &= (oal_uint8)(BIT0);
    pst_dmac_vap->puc_tim_bitmap[1] += uc_tim_offset - 2;
}
#if 0

oal_uint8 dmac_psm_get_local_bitmap(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user)
{
    oal_uint16          us_user_assoc_id;
    oal_uint8           uc_byte_idx;
    oal_uint8           uc_bit_mask = (oal_uint8)(BIT0);

    /* Bitmap Control??bit0???????????? */
    if (pst_dmac_user->st_user_base_info.en_is_multi_user)
    {
        return ((pst_dmac_vap->puc_tim_bitmap[1] & uc_bit_mask) == uc_bit_mask);
    }

    /* ????????????id??????????bitmap?????????????????????? */
    us_user_assoc_id = pst_dmac_user->st_user_base_info.us_assoc_id;
    uc_byte_idx      = 2 + (oal_uint8)(us_user_assoc_id >> 3);
    uc_bit_mask      = (oal_uint8)(BIT0 << (us_user_assoc_id & 0x07));
    if (uc_byte_idx >= pst_dmac_vap->uc_tim_bitmap_len)
    {
        return 0;
    }

    return ((pst_dmac_vap->puc_tim_bitmap[uc_byte_idx] & uc_bit_mask) == uc_bit_mask);
}


oal_uint8 dmac_psm_get_bitmap_len(dmac_vap_stru *pst_dmac_vap)
{
    return pst_dmac_vap->puc_tim_bitmap[0];
}


oal_uint8 dmac_psm_get_bitmap_offset(dmac_vap_stru *pst_dmac_vap)
{
    return (oal_uint8)(2 + (pst_dmac_vap->puc_tim_bitmap[1] & (oal_uint8)(~BIT0)));
}
#endif


OAL_STATIC oal_netbuf_stru* dmac_psm_dequeue_first_mpdu(dmac_user_ps_stru  *pst_ps_structure)
{
    oal_netbuf_stru        *pst_first_net_buf;
    oal_netbuf_stru        *pst_tmp_net_buf;
    oal_netbuf_stru        *pst_net_buf;
    mac_tx_ctl_stru        *pst_tx_ctrl;
    oal_uint8               uc_netbuf_num_per_mpdu;
    oal_netbuf_head_stru   *pst_ps_queue_head;

    pst_ps_queue_head = &pst_ps_structure->st_ps_queue_head;

    pst_first_net_buf = OAL_NETBUF_HEAD_NEXT(pst_ps_queue_head);
    pst_tx_ctrl       = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_first_net_buf);

    /* mpdu????a-msdu????????????net_buff???? */
    if (OAL_FALSE == mac_get_cb_is_amsdu(pst_tx_ctrl))
    {
        pst_first_net_buf = oal_netbuf_delist(pst_ps_queue_head);
        oal_atomic_dec(&pst_ps_structure->uc_mpdu_num);
        return pst_first_net_buf;
    }

    if (OAL_FALSE == MAC_GET_CB_IS_FIRST_MSDU(pst_tx_ctrl))
    {
        /* ??????????????????????????????????????????????????????????????????????
           ????????????????????????????
        */
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_dequeue_first_mpdu::not the first msdu.}");
        return OAL_PTR_NULL;
    }

    /* ??????????????????mpdu??a-msdu??????skb???? */
    uc_netbuf_num_per_mpdu = MAC_GET_CB_NETBUF_NUM(pst_tx_ctrl);

    /* ????????mpdu????????skb??????????????????????????????net_buff?? */
    pst_first_net_buf = oal_netbuf_delist(pst_ps_queue_head);
    uc_netbuf_num_per_mpdu--;

    pst_tmp_net_buf = pst_first_net_buf;
    while (0 != uc_netbuf_num_per_mpdu)
    {
        pst_net_buf = oal_netbuf_delist(pst_ps_queue_head);
        oal_set_netbuf_prev(pst_net_buf, pst_tmp_net_buf);
        oal_set_netbuf_next(pst_net_buf, OAL_PTR_NULL);

        oal_set_netbuf_next(pst_tmp_net_buf, pst_net_buf);

        pst_tmp_net_buf = pst_net_buf;

        uc_netbuf_num_per_mpdu--;
    }

    oal_atomic_dec(&pst_ps_structure->uc_mpdu_num);

    return pst_first_net_buf;

}



oal_uint32 dmac_psm_user_ps_structure_init(dmac_user_stru *pst_dmac_user)
{
    dmac_user_ps_stru *pst_ps_structure;

    pst_ps_structure = &(pst_dmac_user->st_ps_structure);

    oal_spin_lock_init(&(pst_ps_structure->st_lock_ps));

    oal_netbuf_list_head_init(&(pst_ps_structure->st_ps_queue_head));

    oal_atomic_set(&pst_ps_structure->uc_mpdu_num, 0);

    pst_ps_structure->en_is_pspoll_rsp_processing = OAL_FALSE;

    pst_ps_structure->uc_ps_time_count = 0;

#ifdef _PRE_WLAN_DFT_STAT
    /* ?????????????????????? */
    pst_ps_structure->pst_psm_stats = (dmac_user_psm_stats_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,
                                                                               OAL_SIZEOF(dmac_user_psm_stats_stru),
                                                                               OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_ps_structure->pst_psm_stats))
    {
        OAM_ERROR_LOG1(0, OAM_SF_PWR, "{dmac_psm_user_ps_structure_init::alloc pst_ps_stats mem fail, size[%d].}", OAL_SIZEOF(dmac_user_psm_stats_stru));
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEMZERO(pst_ps_structure->pst_psm_stats, OAL_SIZEOF(dmac_user_psm_stats_stru));
#endif

    return OAL_SUCC;
}
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

oal_void dmac_psm_delete_ps_queue_head(dmac_user_stru *pst_dmac_user,oal_uint32 ul_psm_delete_num)
{
    dmac_user_ps_stru   *pst_ps_structure;
    oal_netbuf_stru     *pst_net_buf;

    pst_ps_structure = &(pst_dmac_user->st_ps_structure);
    oal_spin_lock(&pst_ps_structure->st_lock_ps);
    /* ????????????????????????????????????????mpdu */
    while (oal_atomic_read(&pst_ps_structure->uc_mpdu_num) && (ul_psm_delete_num--))
    {
        /* ????????????????mpdu????????wlan??????????lan????????????????????????
           ??????????????????mpdu??????????????????????mpdu??????????????
        */
        pst_net_buf = dmac_psm_dequeue_first_mpdu(pst_ps_structure);

        dmac_tx_excp_free_netbuf(pst_net_buf);

        oal_spin_unlock(&pst_ps_structure->st_lock_ps);
        oal_spin_lock(&pst_ps_structure->st_lock_ps);
    }
    oal_spin_unlock(&pst_ps_structure->st_lock_ps);

}
#endif


oal_void dmac_psm_clear_ps_queue(dmac_user_stru *pst_dmac_user)
{
    dmac_user_ps_stru   *pst_ps_structure;
    oal_netbuf_stru     *pst_net_buf;

    pst_ps_structure = &(pst_dmac_user->st_ps_structure);

    /* ????????????????????????????????????????mpdu */
    while (oal_atomic_read(&pst_ps_structure->uc_mpdu_num))
    {
        oal_spin_lock(&pst_ps_structure->st_lock_ps);

        /* ????????????????mpdu????????wlan??????????lan????????????????????????
           ??????????????????mpdu??????????????????????mpdu??????????????
        */
        pst_net_buf = dmac_psm_dequeue_first_mpdu(pst_ps_structure);

        dmac_tx_excp_free_netbuf(pst_net_buf);

        oal_spin_unlock(&pst_ps_structure->st_lock_ps);
    }

}


oal_uint32  dmac_psm_user_ps_structure_destroy(dmac_user_stru *pst_dmac_user)
{
    dmac_user_ps_stru   *pst_ps_structure;
    oal_netbuf_stru     *pst_net_buf;

    pst_ps_structure = &(pst_dmac_user->st_ps_structure);

#ifdef _PRE_WLAN_DFT_STAT
    if (OAL_PTR_NULL != pst_ps_structure->pst_psm_stats)
    {
        OAL_MEM_FREE(pst_ps_structure->pst_psm_stats, OAL_TRUE);
        pst_ps_structure->pst_psm_stats = OAL_PTR_NULL;
    }
#endif

    pst_ps_structure->en_is_pspoll_rsp_processing = OAL_FALSE;

    /* ????????????????????????????????????????mpdu */
    while (oal_atomic_read(&pst_ps_structure->uc_mpdu_num))
    {
        oal_spin_lock(&pst_ps_structure->st_lock_ps);

        /* ????????????????mpdu????????wlan??????????lan????????????????????????
           ??????????????????mpdu??????????????????????mpdu??????????????
        */
        pst_net_buf = dmac_psm_dequeue_first_mpdu(pst_ps_structure);

        dmac_tx_excp_free_netbuf(pst_net_buf);

        oal_spin_unlock(&pst_ps_structure->st_lock_ps);
    }

    return OAL_SUCC;
}

#if defined(_PRE_PRODUCT_ID_HI110X_DEV)

OAL_STATIC oal_bool_enum_uint8 dmac_is_null_data(oal_netbuf_stru *pst_net_buf)
{
    mac_ieee80211_frame_stru       *pst_mac_header;
    oal_uint8                       uc_mgmt_type;
    oal_uint8                       uc_mgmt_subtype;

    pst_mac_header  = (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_net_buf);
    uc_mgmt_type    = mac_frame_get_type_value((oal_uint8 *)pst_mac_header);
    uc_mgmt_subtype = mac_frame_get_subtype_value((oal_uint8 *)pst_mac_header);

    return (WLAN_DATA_BASICTYPE == uc_mgmt_type && WLAN_NULL_FRAME == uc_mgmt_subtype);
}
#endif


oal_uint8 dmac_psm_pkt_need_buff(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_netbuf_stru *pst_net_buf)
{
    mac_tx_ctl_stru                *pst_tx_ctrl;
    mac_ieee80211_frame_stru       *pst_mac_header;
    oal_uint8                       uc_mgmt_type;
    oal_uint8                       uc_mgmt_subtype;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_device_stru                *pst_mac_device;
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_user || OAL_PTR_NULL == pst_net_buf))
    {
        return OAL_FALSE;
    }
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_psm_pkt_need_buff::pst_device[%d] null!}", pst_dmac_vap->st_vap_base_info.uc_device_id);
        return OAL_FALSE;
    }
#endif
    /* sta??p2p noa??????????????*/
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if ((WLAN_VAP_MODE_BSS_AP != pst_dmac_vap->st_vap_base_info.en_vap_mode)
        &&(!IS_P2P_CL(&pst_dmac_vap->st_vap_base_info)))
#else
    if (WLAN_VAP_MODE_BSS_AP != pst_dmac_vap->st_vap_base_info.en_vap_mode)
#endif
    {
        return OAL_FALSE;
    }

    pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);

    if (OAL_FALSE == MAC_GET_CB_IS_MCAST(pst_tx_ctrl))
    {
        /*
           ??????????????????????????????????????????:
           1????????????
           2??????????????????????????????????????????????????
        */

#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
        if (IS_AP(&(pst_dmac_vap->st_vap_base_info))
            && (OAL_FALSE == MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctrl))
            && (OAL_TRUE == dmac_is_null_data(pst_net_buf)))
        {
            return OAL_TRUE;
        }
#endif
    #if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        if(WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
        {
            if ((OAL_FALSE == pst_dmac_user->bit_ps_mode) && (OAL_FALSE== pst_mac_device->st_p2p_info.en_p2p_ps_pause))
            {
                return OAL_FALSE;
            }
        }
        else if(IS_P2P_CL(&pst_dmac_vap->st_vap_base_info))
        {
            if(OAL_FALSE== pst_mac_device->st_p2p_info.en_p2p_ps_pause)
            {
                return OAL_FALSE;
            }
        }
    #else
        if (OAL_FALSE == pst_dmac_user->bit_ps_mode)
        {
            return OAL_FALSE;
        }
    #endif

        if (OAL_TRUE == MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctrl))
        {
            return OAL_FALSE;
        }
    }
    else
    {
        /*
           ??????????????????????????????????????????:
           1??????????????????????
           2????????????????????????????????????????????????????
           3??1102??????noa????????
        */
    #if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        if(WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
        {
            if ((0 == pst_dmac_vap->uc_ps_user_num) && (OAL_FALSE== pst_mac_device->st_p2p_info.en_p2p_ps_pause))
            {
                return OAL_FALSE;
            }
        }
        else if(IS_P2P_CL(&pst_dmac_vap->st_vap_base_info))
        {
            if(OAL_FALSE == pst_mac_device->st_p2p_info.en_p2p_ps_pause)
            {
                return OAL_FALSE;
            }
        }
    #else
        if (0 == pst_dmac_vap->uc_ps_user_num)
        {
            return OAL_FALSE;
        }
    #endif

        if (OAL_TRUE == MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctrl))
        {
            return OAL_FALSE;
        }
    }

    /* ACS AP??????probe req???????????? */
    pst_mac_header  = (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_net_buf);
    uc_mgmt_type    = mac_frame_get_type_value((oal_uint8 *)pst_mac_header);
    uc_mgmt_subtype = mac_frame_get_subtype_value((oal_uint8 *)pst_mac_header);

    if (WLAN_WME_AC_MGMT == mac_get_cb_ac(pst_tx_ctrl) && WLAN_MANAGEMENT == uc_mgmt_type && WLAN_PROBE_REQ == uc_mgmt_subtype)
    {
        return OAL_FALSE;
    }

    return OAL_TRUE;
}


oal_uint32 dmac_psm_enqueue(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_netbuf_stru *pst_net_buf)
{
    oal_netbuf_stru        *pst_next_net_buf     = OAL_PTR_NULL;
    mac_tx_ctl_stru        *pst_tx_ctrl          = OAL_PTR_NULL;
    oal_int32               l_ps_mpdu_num        = 0;
#ifdef _PRE_WLAN_DFT_STAT
    dmac_user_psm_stats_stru *pst_psm_stats;
#endif
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_user
        || OAL_PTR_NULL == pst_net_buf))
    {
        OAM_ERROR_LOG3(0, OAM_SF_PWR, "{dmac_psm_rx_process_data::param is null.vap=[%d], \
                       user=[%d],buf=[%d]}.", (oal_uint32)pst_dmac_vap, (oal_uint32)pst_dmac_user,
                       (oal_uint32)pst_net_buf);
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_DFT_STAT
    pst_psm_stats = pst_dmac_user->st_ps_structure.pst_psm_stats;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_psm_stats))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_enqueue::psm_stats is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif

    l_ps_mpdu_num = oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num);
    pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /*????APUT????????????????????????bitmap????????????????????????????????*/
    if((WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
         &&(((pst_dmac_user->bit_ps_mode == OAL_TRUE)&&(OAL_FALSE == MAC_GET_CB_IS_MCAST(pst_tx_ctrl)))
         ||((OAL_TRUE == MAC_GET_CB_IS_MCAST(pst_tx_ctrl))&&(0 != pst_dmac_vap->uc_ps_user_num))))
#endif
    {
        /* ??????????pvb */
        dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 1);
        dmac_encap_beacon(pst_dmac_vap, pst_dmac_vap->pauc_beacon_buffer[pst_dmac_vap->uc_beacon_idx], &(pst_dmac_vap->us_beacon_len));
    }


    /* ???????????????????????????? */
    oal_spin_lock(&pst_dmac_user->st_ps_structure.st_lock_ps);

    /* ??????????????mpdu?????? */
    l_ps_mpdu_num += MAC_GET_CB_MPDU_NUM(pst_tx_ctrl);
    oal_atomic_set(&pst_dmac_user->st_ps_structure.uc_mpdu_num, l_ps_mpdu_num);

#ifdef _PRE_WLAN_DFT_STAT
    pst_psm_stats->ul_psm_enqueue_succ_cnt     += MAC_GET_CB_NETBUF_NUM(pst_tx_ctrl);
#endif

    /* ??????netbuf?????????????????? */
    while (OAL_PTR_NULL != pst_net_buf)
    {
        pst_next_net_buf = oal_get_netbuf_next(pst_net_buf);
        oal_netbuf_add_to_list_tail(pst_net_buf, &pst_dmac_user->st_ps_structure.st_ps_queue_head);
        pst_net_buf = pst_next_net_buf;
    }

    oal_spin_unlock(&pst_dmac_user->st_ps_structure.st_lock_ps);

    OAM_INFO_LOG3(0, OAM_SF_PWR, "{dmac_psm_enqueue::user[%d] enqueue %d & total %d.}",
                  pst_dmac_user->st_user_base_info.us_assoc_id, MAC_GET_CB_NETBUF_NUM(pst_tx_ctrl), l_ps_mpdu_num);

    return OAL_SUCC;
}


OAL_STATIC oal_uint32 dmac_psm_queue_send(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user)
{
    dmac_user_ps_stru       *pst_ps_structure;
    oal_netbuf_stru         *pst_net_buf;
    oal_int32                l_ps_mpdu_num;
    mac_tx_ctl_stru         *pst_tx_ctrl;
    oal_uint32               ul_ret;
    mac_device_stru         *pst_mac_device;
#ifdef _PRE_WLAN_DFT_STAT
    dmac_user_psm_stats_stru *pst_psm_stats;
#endif

    pst_ps_structure = &pst_dmac_user->st_ps_structure;

#ifdef _PRE_WLAN_DFT_STAT
    pst_psm_stats = pst_ps_structure->pst_psm_stats;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_psm_stats))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_queue_send::psm_stats is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif

    /* ???????????????????????????????? */
    oal_spin_lock(&pst_ps_structure->st_lock_ps);

    /* ????????????????????mpdu,??????????mpdu??????1 */
    pst_net_buf = dmac_psm_dequeue_first_mpdu(pst_ps_structure);
    if (OAL_PTR_NULL == pst_net_buf)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_queue_send::pst_net_buf null.}");

        DMAC_PSM_STATS_INCR(pst_psm_stats->ul_psm_dequeue_fail_cnt);

        oal_spin_unlock(&pst_ps_structure->st_lock_ps);

        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_spin_unlock(&pst_ps_structure->st_lock_ps);

    DMAC_PSM_STATS_INCR(pst_psm_stats->ul_psm_dequeue_succ_cnt);

    l_ps_mpdu_num = oal_atomic_read(&pst_ps_structure->uc_mpdu_num);

    /* ??????????????????????????????????????????????????MORE DATA????1??????????
       ????????????????????????????????????????tim_bitmap???????? */
    if(WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        if (0 != l_ps_mpdu_num)
        {
            dmac_psm_set_more_data(pst_net_buf);
        }
        else
        {
            dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 0);
        }
    }

    pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);

    if(OAL_TRUE == MAC_GET_CB_IS_MCAST(pst_tx_ctrl))
    {
        mac_set_cb_ac(pst_tx_ctrl, WLAN_WME_AC_MGMT);
    }

    if (0 == MAC_GET_CB_MPDU_NUM(pst_tx_ctrl))
    {
        OAM_ERROR_LOG1(0, OAM_SF_TX, "{dmac_psm_queue_send::tid %d, uc_dscr_num is zero.}", mac_get_cb_tid(pst_tx_ctrl));
    }

    /*
       ????????????????:????????????dmac_tx_process_data??????????????????????????
       ??????????mpdu??????????????????????????????????????????????????mpdu??pspoll
       ????????????????????????
    */
    MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctrl) = OAL_TRUE;
    /* ?????????????????????????????? */
    if (WLAN_DATA_BASICTYPE == MAC_GET_CB_FRAME_TYPE(pst_tx_ctrl))
    {
        pst_mac_device = (mac_device_stru *)mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
        {
            OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_queue_send:: mac_res_get_dev is null.}");
            dmac_tx_excp_free_netbuf(pst_net_buf);
            DMAC_PSM_STATS_INCR(pst_psm_stats->ul_psm_send_data_fail_cnt);
            return OAL_ERR_CODE_PTR_NULL;
        }

        if (OAL_FALSE == pst_dmac_user->st_user_base_info.en_is_multi_user && OAL_TRUE == dmac_user_get_ps_mode(&pst_dmac_user->st_user_base_info))
        {
            dmac_tid_resume(pst_mac_device->pst_device_stru, &pst_dmac_user->ast_tx_tid_queue[mac_get_cb_tid(pst_tx_ctrl)], DMAC_TID_PAUSE_RESUME_TYPE_PS);
        }

#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
        if (MAC_GET_CB_EN_FRAME_SUBTYPE(pst_tx_ctrl) == WLAN_NULL_FRAME)
        {
            ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_net_buf, MAC_GET_CB_MPDU_LEN(pst_tx_ctrl) + MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctrl));
            if (OAL_SUCC != ul_ret)
            {
                oal_netbuf_free(pst_net_buf);

                OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                                 "{dmac_psm_queue_send::null data from ps queue. failed[%d].}", ul_ret);
                DMAC_PSM_STATS_INCR(pst_psm_stats->ul_psm_send_mgmt_fail_cnt);

                //return ul_ret;
            }
            else
            {
                OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                                "{dmac_psm_queue_send::null data from ps queue.succ}");
            }
            return ul_ret;
        }
#endif
        ul_ret = dmac_tx_process_data(pst_dmac_vap->pst_hal_device, pst_dmac_vap, pst_net_buf);
        if (OAL_SUCC != ul_ret)
        {
            pst_mac_device = (mac_device_stru *)mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
            OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                            "{dmac_psm_queue_send::dmac_tx_process_data failed[%d],dev_mpdu_num = %d}", ul_ret, pst_mac_device->us_total_mpdu_num);
            OAM_WARNING_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_queue_send:: be = %d, bk = %d, vi = %d, vo = %d}",
                             pst_mac_device->aus_ac_mpdu_num[WLAN_WME_AC_BE],
                             pst_mac_device->aus_ac_mpdu_num[WLAN_WME_AC_BK],
                             pst_mac_device->aus_ac_mpdu_num[WLAN_WME_AC_VI],
                             pst_mac_device->aus_ac_mpdu_num[WLAN_WME_AC_VO]);
            dmac_tx_excp_free_netbuf(pst_net_buf);
            DMAC_PSM_STATS_INCR(pst_psm_stats->ul_psm_send_data_fail_cnt);

            return ul_ret;
        }
    }
    else
    {
        ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_net_buf, MAC_GET_CB_MPDU_LEN(pst_tx_ctrl) + MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctrl));
        if (OAL_SUCC != ul_ret)
        {
            oal_netbuf_free(pst_net_buf);

            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                             "{dmac_psm_queue_send::dmac_tx_mgmt failed[%d].}", ul_ret);
            DMAC_PSM_STATS_INCR(pst_psm_stats->ul_psm_send_mgmt_fail_cnt);

            return ul_ret;
        }
    }

    return OAL_SUCC;
}


oal_void dmac_psm_queue_flush(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user)
{
    oal_int32       l_ps_mpdu_num;
    oal_uint32      ul_tid_num;
    oal_int32       l_ps_mpdu_send_succ = 0;
    oal_int32       l_ps_mpdu_send_fail = 0;
    oal_uint32      ul_ret;
#ifdef _PRE_WLAN_DFT_STAT
    dmac_user_psm_stats_stru *pst_psm_stats;
#endif

    l_ps_mpdu_num       = oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num);

    if (l_ps_mpdu_num == 0)
    {
        ul_tid_num      = dmac_psm_tid_mpdu_num(pst_dmac_user);
        if(WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
        {
            if (0 == ul_tid_num)
            {
                dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 0);
            }
            else
            {
                OAM_WARNING_LOG1(0,OAM_SF_PWR,"dmac_psm_queue_flush::ps queue is 0,but tid num is [%d]",ul_tid_num);
            }
        }

        return;
    }
    /* ???????????????????????????????? */
    while (l_ps_mpdu_num-- > 0)
    {
        ul_ret = dmac_psm_queue_send(pst_dmac_vap, pst_dmac_user);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_PWR, "{dmac_psm_queue_flush::dmac_psm_queue_send fail[%d].}", ul_ret);
            l_ps_mpdu_send_fail++;
        }
        else
        {
            l_ps_mpdu_send_succ++;
        }
    }
#ifdef _PRE_WLAN_DFT_STAT
    pst_psm_stats = pst_dmac_user->st_ps_structure.pst_psm_stats;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_psm_stats))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_queue_flush::psm_stats is null.}");
        return;
    }
    pst_psm_stats->ul_psm_dequeue_succ_cnt = (oal_uint32)l_ps_mpdu_send_succ;
    pst_psm_stats->ul_psm_dequeue_fail_cnt = (oal_uint32)l_ps_mpdu_send_fail;
#endif
    if (l_ps_mpdu_send_fail)
    {
        OAM_WARNING_LOG3(0, OAM_SF_PWR, "{dmac_psm_queue_flush::user[%d] send %d & fail %d}",
                       pst_dmac_user->st_user_base_info.us_assoc_id, l_ps_mpdu_send_succ, l_ps_mpdu_send_fail);
    }

    OAM_INFO_LOG3(0, OAM_SF_PWR, "{dmac_psm_queue_flush::user[%d] send %d & fail %d}",
                  pst_dmac_user->st_user_base_info.us_assoc_id, l_ps_mpdu_send_succ, l_ps_mpdu_send_fail);

}


oal_uint32  dmac_psm_tx_set_more_data(dmac_user_stru *pst_dmac_user,
                                               mac_tx_ctl_stru *pst_tx_cb)
{
    oal_int32               l_ps_mpdu_num;
    oal_bool_enum_uint8     en_tid_empty;
    mac_ieee80211_frame_stru  *pst_frame_hdr = OAL_PTR_NULL;

    if ((OAL_TRUE == pst_dmac_user->bit_ps_mode)
        && (OAL_TRUE == pst_dmac_user->st_ps_structure.en_is_pspoll_rsp_processing))
    {
        l_ps_mpdu_num = oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num);
        en_tid_empty  = dmac_psm_is_tid_empty(pst_dmac_user);

        if ((0 != l_ps_mpdu_num) || (OAL_FALSE == en_tid_empty))
        {
            pst_frame_hdr = mac_get_cb_frame_hdr(pst_tx_cb);
            if (OAL_LIKELY(OAL_PTR_NULL != pst_frame_hdr))
            {
                mac_get_cb_frame_hdr(pst_tx_cb)->st_frame_control.bit_more_data = 0x01;
            }
        }
    }

    return OAL_SUCC;
}
#if 0
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

oal_uint32  dmac_psm_enable_user_to_psm_back(dmac_vap_stru *pst_dmac_vap,
                                                        mac_device_stru *pst_mac_device,
                                                        dmac_user_stru *pst_dmac_user)
{
    hal_to_dmac_device_stru      *pst_hal_device;

    pst_hal_device = pst_mac_device->pst_device_stru;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device)) {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_enable_user_to_psm_back::pst_hal_device is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    hal_tx_enable_peer_sta_ps_ctrl(pst_hal_device, pst_dmac_user->uc_lut_index);

//    dmac_psm_flush_txq_to_psm(pst_dmac_vap, pst_dmac_user);

    return OAL_SUCC;

}


oal_uint32  dmac_psm_disable_user_to_psm_back(mac_device_stru *pst_mac_device,
                                                        dmac_user_stru *pst_dmac_user)
{
    hal_to_dmac_device_stru      *pst_hal_device;

    pst_hal_device = pst_mac_device->pst_device_stru;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device)) {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_disable_user_to_psm_back::pst_hal_device is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    hal_tx_disable_peer_sta_ps_ctrl(pst_hal_device, pst_dmac_user->uc_lut_index);

    return OAL_SUCC;

}
#if 0

oal_uint32  dmac_psm_flush_txq_to_psm(dmac_vap_stru  *pst_dmac_vap,
                                                        dmac_user_stru *pst_dmac_user)
{
    oal_int8                      c_queue_idx;
    hal_tx_dscr_stru             *pst_tx_dscr;
    oal_dlist_head_stru          *pst_dlist_pos;
    oal_dlist_head_stru          *pst_dlist_n;
    oal_netbuf_stru              *pst_netbuf;

    /* ????user??8??tid????????tid????????????psm???? */
    for (c_queue_idx = WLAN_TIDNO_BEST_EFFORT; c_queue_idx < WLAN_TIDNO_BUTT; c_queue_idx++) {
        /* UAPSD?????????????? */
        if (WLAN_TIDNO_UAPSD == c_queue_idx) {
            continue;
        }
        OAL_DLIST_SEARCH_FOR_EACH_SAFE (pst_dlist_pos, pst_dlist_n, &pst_dmac_user->ast_tx_tid_queue[c_queue_idx].st_hdr) {
            pst_tx_dscr = OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
            pst_netbuf = pst_tx_dscr->pst_skb_start_addr;
            oal_dlist_delete_entry(&pst_tx_dscr->st_entry);
            OAL_MEM_FREE(pst_tx_dscr, OAL_TRUE);

            dmac_psm_enqueue(pst_dmac_vap, pst_dmac_user, pst_netbuf);
            (pst_dmac_user->ast_tx_tid_queue[c_queue_idx].us_mpdu_num)--;
        }
    }
    return OAL_SUCC;

}
#endif
#else
#endif
#endif

oal_uint32  dmac_psm_flush_txq_to_tid(mac_device_stru *pst_mac_device,
                                                        dmac_vap_stru  *pst_dmac_vap,
                                                        dmac_user_stru *pst_dmac_user)
{
    oal_uint8                     uc_q_idx           = 0;
    hal_tx_dscr_stru             *pst_tx_dscr        = OAL_PTR_NULL;
    mac_tx_ctl_stru              *pst_cb             = OAL_PTR_NULL;
    dmac_tid_stru                *pst_tid_queue      = OAL_PTR_NULL;
    hal_to_dmac_device_stru      *pst_hal_device     = OAL_PTR_NULL;
    oal_dlist_head_stru          *pst_dlist_pos      = OAL_PTR_NULL;
    oal_dlist_head_stru          *pst_dlist_n        = OAL_PTR_NULL;
    oal_netbuf_stru              *pst_mgmt_buf       = OAL_PTR_NULL;
    dmac_user_stru               *pst_mcast_user     = OAL_PTR_NULL;
    oal_dlist_head_stru           ast_pending_q[WLAN_TID_MAX_NUM];
    oal_uint8                     auc_mpdu_num[WLAN_TID_MAX_NUM];
    oal_uint8                     uc_tid             = 0;
    oal_uint32                    ul_ret             = 0;
    oal_uint16                    us_seq_num         = 0;
    dmac_ba_tx_stru              *pst_ba_hdl;
    oal_uint8                     uc_dscr_status     = DMAC_TX_INVALID;
    hal_tx_dscr_stru             *pst_tx_dscr_next   = OAL_PTR_NULL;

    if(OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_flush_txq_to_tid::pst_mac_device is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device = pst_mac_device->pst_device_stru;
    if(OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_flush_txq_to_tid::pst_hal_device is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ???????????????????????????????????????????????????????????????????????????? */
    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_dlist_pos, pst_dlist_n, &pst_hal_device->ast_tx_dscr_queue[HAL_TX_QUEUE_HI].st_header)
    {
        pst_tx_dscr  = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
        pst_mgmt_buf = pst_tx_dscr->pst_skb_start_addr;
        pst_cb       = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_mgmt_buf);
        /* ?????????????????????????????????????? */
        if (MAC_GET_CB_TX_USER_IDX(pst_cb) != pst_dmac_user->st_user_base_info.us_assoc_id)
        {
            continue;
        }
        hal_tx_get_dscr_status(pst_hal_device, pst_tx_dscr, &uc_dscr_status);
        /* ???????????????????????????????????????? */
        if (DMAC_TX_INVALID != uc_dscr_status)
        {
            continue;
        }
        /* ?????????? */
        oal_dlist_delete_entry(&pst_tx_dscr->st_entry);
        OAL_MEM_FREE(pst_tx_dscr, OAL_TRUE);

        /* ????????????????????????????????enqueue???????????????????????????????????? */
        dmac_psm_enqueue(pst_dmac_vap, pst_dmac_user, pst_mgmt_buf);

        /* ??????????????ppdu??????????ppducnt??1 */
        pst_hal_device->ast_tx_dscr_queue[HAL_TX_QUEUE_HI].uc_ppdu_cnt
                = OAL_SUB(pst_hal_device->ast_tx_dscr_queue[HAL_TX_QUEUE_HI].uc_ppdu_cnt, 1);

    }
    /* ?????????????? */
    for (uc_tid = 0; uc_tid < WLAN_TID_MAX_NUM; uc_tid++)
    {
        oal_dlist_init_head(&ast_pending_q[uc_tid]);
        auc_mpdu_num[uc_tid] = 0;
    }

    /* ????????4??????????????????????????????mpud???????????????????????????????? */
    for (uc_q_idx = HAL_TX_QUEUE_BK; uc_q_idx < HAL_TX_QUEUE_HI; uc_q_idx++)
    {
        oal_bool_enum en_dscr_list_is_ampdu       = OAL_FALSE;  /*????????????????????????????????ampdu????*/
        oal_bool_enum en_dscr_list_first_flag     = OAL_TRUE;   /*????????????????????????????*/
        oal_bool_enum en_dscr_list_back_flag      = OAL_FALSE;   /*????????????????????tid????*/
        oal_bool_enum en_curr_dscr_back_flag      = OAL_FALSE;   /*??????????????????????tid????*/

        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_dlist_pos, pst_dlist_n, &pst_hal_device->ast_tx_dscr_queue[uc_q_idx].st_header)
        {
            pst_tx_dscr  = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
            pst_cb       = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_tx_dscr->pst_skb_start_addr);

            /* ??????????????????????????????TID???? */
            if (MAC_GET_CB_TX_USER_IDX(pst_cb) != pst_dmac_user->st_user_base_info.us_assoc_id)
            {
                continue;
            }

            /*??????????????????????????????????????????amdpu??????????mpdu????????*/
            if (OAL_TRUE == en_dscr_list_first_flag)
            {
                en_dscr_list_is_ampdu = (0 == pst_tx_dscr->bit_is_ampdu)? OAL_FALSE : OAL_TRUE;
            }

            /* ??????ampdu????????????????????????mpdu?????????????????????? */
            if (((OAL_TRUE == en_dscr_list_is_ampdu) &&  (OAL_TRUE == en_dscr_list_first_flag))
                 || (OAL_FALSE == en_dscr_list_is_ampdu))
            {
                /* ?????????????? */
                hal_tx_get_dscr_status(pst_hal_device, pst_tx_dscr, &uc_dscr_status);

                /* ????????????????????????????????9(??????????????????????????????????)??????????????TID???? */
                if ((DMAC_TX_INVALID == uc_dscr_status)||(DMAC_TX_PENDING == uc_dscr_status))
                {
                    /* ??????????????ppdu??????????ppducnt??1 */
                    pst_hal_device->ast_tx_dscr_queue[uc_q_idx].uc_ppdu_cnt
                                = OAL_SUB(pst_hal_device->ast_tx_dscr_queue[uc_q_idx].uc_ppdu_cnt, 1);

                    en_dscr_list_back_flag = OAL_TRUE;  /*????AMPDU??????????TID?????? MPDU????????????*/
                    en_curr_dscr_back_flag = OAL_TRUE;  /*????????????????????TID?????? AMPDU??/MPDU??????????*/
                }
                else /*????????????AMPDU???? ????MPDU???????????? ??????????tid????*/
                {
                    en_dscr_list_back_flag = OAL_FALSE; /*????AMPDU????????????TID?????? MPDU????????????*/
                    en_curr_dscr_back_flag = OAL_FALSE; /*??????????????????????TID?????? AMPDU??/MPDU??????????*/

                    /*
                        MPDU??????????????????MPDU??next????????????????????????????????????????????????????
                        ????????????????????next????????????????????????????????????????????????????????????
                        AMPDU????????????
                    */
                    if(OAL_FALSE == en_dscr_list_is_ampdu)
                    {
                        hal_tx_ctrl_dscr_unlink(pst_hal_device, pst_tx_dscr);
                    }
                }

            }
            else /*AMPDU??????????????AMPDU????????????????*/
            {
                en_curr_dscr_back_flag = en_dscr_list_back_flag;
            }

            /*????flag?????? ????????dev??????????????????????????*/
            if (OAL_TRUE == en_curr_dscr_back_flag)
            {
                /* ??device?????????????????? */
                oal_dlist_delete_entry(&pst_tx_dscr->st_entry);

                /* ???????????????? */
                pst_tx_dscr->bit_is_retried = OAL_TRUE;
                MAC_GET_CB_RETRIED_NUM(pst_cb)++;

                /* ??????????????????????????????????tid???? */
                oal_dlist_add_tail(&pst_tx_dscr->st_entry, &ast_pending_q[mac_get_cb_tid(pst_cb)]);
                /* ????????????????????mpdu???? */
                auc_mpdu_num[mac_get_cb_tid(pst_cb)]++;
            }

            /* ????????dscr list???? */
            hal_get_tx_dscr_next(pst_hal_device, pst_tx_dscr, &pst_tx_dscr_next);
            en_dscr_list_first_flag = (pst_tx_dscr_next == OAL_PTR_NULL) ? OAL_TRUE : OAL_FALSE;
        }
    }

    /* ??????????????mpdu????tid?????? */
    for (uc_tid = 0; uc_tid < WLAN_TID_MAX_NUM; uc_tid++)
    {
        if (oal_dlist_is_empty(&ast_pending_q[uc_tid]))
        {
            continue;
        }
        pst_tid_queue = &(pst_dmac_user->ast_tx_tid_queue[uc_tid]);

        ul_ret = dmac_tid_tx_queue_enqueue_head(pst_tid_queue, &ast_pending_q[uc_tid], auc_mpdu_num[uc_tid]);
        if (OAL_SUCC == ul_ret)
        {
            pst_tid_queue->uc_retry_num += auc_mpdu_num[uc_tid];
            /* ?????????????????????? */
            dmac_alg_tid_update_notify(pst_tid_queue);
            OAM_INFO_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                          "{dmac_psm_flush_txq_to_tid:: uc_tid[%d] mpdu_num[%d]} OK!", uc_tid, auc_mpdu_num[uc_tid]);
        #if (defined(_PRE_WLAN_DFT_STAT) && (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE))
            if (OAL_PTR_NULL != pst_tid_queue->pst_tid_stats)
            {
                DMAC_TID_STATS_INCR(pst_tid_queue->pst_tid_stats->ul_tid_retry_enqueue_cnt, auc_mpdu_num[uc_tid]);
            }
        #endif
        }
        else
        {
            /* ????????????????ba?????????? */
            pst_ba_hdl = pst_tid_queue->pst_ba_tx_hdl;
            if (OAL_PTR_NULL != pst_ba_hdl)
            {
                OAL_DLIST_SEARCH_FOR_EACH(pst_dlist_pos, &ast_pending_q[uc_tid])
                {
                    pst_tx_dscr  = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
                    hal_tx_get_dscr_seq_num(pst_hal_device, pst_tx_dscr, &us_seq_num);
                    dmac_ba_update_baw(pst_ba_hdl, us_seq_num);
                }
            }
        #if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
            pst_dmac_vap->st_vap_base_info.st_vap_stats.ul_tx_dropped_packets += auc_mpdu_num[uc_tid];
        #endif
            OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                             "{dmac_psm_flush_txq_to_tid::uc_tid[%d] mpdu_num[%d]} failed[%d].}", uc_tid, auc_mpdu_num[uc_tid], ul_ret);
            dmac_tx_excp_free_dscr(&ast_pending_q[uc_tid], pst_hal_device);
        }
    }

    /* ??VO????????????\??????????????????????vap??????????????????tid???? */
    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_dlist_pos, pst_dlist_n, &pst_hal_device->ast_tx_dscr_queue[HAL_TX_QUEUE_VO].st_header)
    {
        pst_tx_dscr  = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
        pst_cb       = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_tx_dscr->pst_skb_start_addr);

        /* ??????????\????????????????????vap(????vap)??????????vap????????????tid???? */
        if ((OAL_TRUE != MAC_GET_CB_IS_MCAST(pst_cb)) || (MAC_GET_CB_TX_VAP_INDEX(pst_cb) == pst_dmac_vap->st_vap_base_info.uc_vap_id))
        {
            continue;
        }

        /* ??????????????????mcast??bcast??????????vap????????????????tid???? */
        pst_mcast_user = mac_res_get_dmac_user(MAC_GET_CB_TX_USER_IDX(pst_cb));
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mcast_user))
        {
            OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_flush_txq_to_tid::pst_mcast_user is null.}");
            continue;
        }
        /* ????mpdu??????????????????????ppducnt??1 */
        oal_dlist_delete_entry(&pst_tx_dscr->st_entry);
        pst_hal_device->ast_tx_dscr_queue[HAL_TX_QUEUE_VO].uc_ppdu_cnt
                = OAL_SUB(pst_hal_device->ast_tx_dscr_queue[HAL_TX_QUEUE_VO].uc_ppdu_cnt, 1);

        pst_tid_queue = &pst_mcast_user->ast_tx_tid_queue[mac_get_cb_tid(pst_cb)];
    #ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
        pst_tx_dscr->bit_is_retried = OAL_TRUE;
        /* ?????????? */
        oal_dlist_join_head(&pst_tid_queue->st_retry_q, &pst_tx_dscr->st_entry);
    #else
        oal_dlist_add_head(&pst_tx_dscr->st_entry, &pst_tid_queue->st_hdr);
    #endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */

        /* ????tid??????????????dmac_tid_tx_queue_enqueue_head???????? */
        pst_tid_queue->us_mpdu_num++;
        pst_mac_device->us_total_mpdu_num++;
        pst_mac_device->aus_vap_mpdu_num[pst_tid_queue->uc_vap_id]++;
        pst_mac_device->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid_queue->uc_tid)]++;
        if (OAL_TRUE == pst_tx_dscr->bit_is_retried)
        {
            pst_tid_queue->uc_retry_num++;
        }

    #ifdef _PRE_WLAN_FEATURE_FLOWCTL
        dmac_alg_flowctl_backp_notify(&pst_dmac_vap->st_vap_base_info,
                                      pst_mac_device->us_total_mpdu_num,
                                      pst_mac_device->aus_ac_mpdu_num);
    #endif

    }
    /* ????????????????????????????????????mac */
    hal_clear_hw_fifo(pst_hal_device);

    /*?????????????????????????????????????? ????ppdu num??????????*/
    for (uc_q_idx = 0; uc_q_idx < HAL_TX_QUEUE_BUTT; uc_q_idx++)
    {
        oal_bool_enum en_dscr_list_is_ampdu   = OAL_FALSE;  /*????????????????????????????????ampdu????*/
        oal_bool_enum en_dscr_list_first_flag = OAL_TRUE;   /*????????????????????????????*/
        oal_bool_enum en_mpdu_list_put_flag   = OAL_FALSE;  /*????mpdu????????????????????????*/

        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_dlist_pos, pst_dlist_n, &pst_hal_device->ast_tx_dscr_queue[uc_q_idx].st_header)
        {
            pst_tx_dscr  = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
            if (OAL_TRUE == en_dscr_list_first_flag)
            {
                en_dscr_list_is_ampdu = (0 == pst_tx_dscr->bit_is_ampdu)? OAL_FALSE : OAL_TRUE;
                en_mpdu_list_put_flag = OAL_FALSE;
            }

            /*??????ampdu?????????????????? ??????mpdu??????????????????????????????????*/
            if (((OAL_TRUE == en_dscr_list_is_ampdu) && (OAL_TRUE == en_dscr_list_first_flag))
               || ((OAL_FALSE == en_dscr_list_is_ampdu) && (OAL_FALSE == en_mpdu_list_put_flag)))
            {
                /* ?????????????? */
                hal_tx_get_dscr_status(pst_hal_device, pst_tx_dscr, &uc_dscr_status);

                /* ????????????????????????????????????????FIFO */
                /* ??????????????????????????????????????FIFO?????????????????????? */
                if ((DMAC_TX_INVALID == uc_dscr_status)||(DMAC_TX_PENDING == uc_dscr_status))
                {
                    hal_tx_put_dscr(pst_hal_device, uc_q_idx, pst_tx_dscr);
                    if (OAL_FALSE == en_dscr_list_is_ampdu)
                    {
                        en_mpdu_list_put_flag = OAL_TRUE;
                    }
                }
            }

            /* ????????dscr list???? */
            hal_get_tx_dscr_next(pst_hal_device, pst_tx_dscr, &pst_tx_dscr_next);
            en_dscr_list_first_flag = (pst_tx_dscr_next == OAL_PTR_NULL) ? OAL_TRUE : OAL_FALSE;
        }
    }

    return OAL_SUCC;
}

//#endif


oal_uint32  dmac_psm_reset(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru          *pst_event;
    frw_event_hdr_stru      *pst_event_hdr;
    oal_uint16              *pus_user_id;
    dmac_user_stru          *pst_dmac_user;
    dmac_vap_stru           *pst_dmac_vap;
    oal_int32                ul_uapsd_qdepth = 0;
#if 0
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_device_stru             *pst_macdev;
#endif
#endif

    if ((OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_reset::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ????????????????????????payload?????? */
    pst_event       = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr   = &(pst_event->st_event_hdr);
    pus_user_id     = (oal_uint16 *)pst_event->auc_event_data;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(*pus_user_id);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_PWR, "{dmac_psm_reset::pst_dmac_user null.");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == pst_dmac_user->bit_ps_mode)
    {
        /* ???????????????????????????? */

        return OAL_SUCC;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_PWR, "{dmac_psm_reset::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
#if 0
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_macdev = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_doze:: mac_dev is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    dmac_psm_disable_user_to_psm_back(pst_macdev,pst_dmac_user);
#endif
#endif
    OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_PWR, "{dmac_psm_reset::user changes ps mode to active.}");

    DMAC_PSM_CHANGE_USER_PS_STATE(pst_dmac_user->bit_ps_mode, OAL_FALSE);


    pst_dmac_vap->uc_ps_user_num = OAL_SUB(pst_dmac_vap->uc_ps_user_num, 1);    /* ???????????????? */
    dmac_user_resume(pst_dmac_user);                                            /* ????user????????user????????tid */
    dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 0);                  /* ????????????beacon???????? */


    dmac_psm_queue_flush(pst_dmac_vap, pst_dmac_user);
#ifdef _PRE_WLAN_FEATURE_UAPSD
    ul_uapsd_qdepth = dmac_uapsd_flush_queue(pst_dmac_vap, pst_dmac_user);
    if(ul_uapsd_qdepth < 0)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_uapsd_flush_queue:: return value is -1.}");
        return OAL_FAIL;
    }
    /*uc_uapsd_send = dmac_uapsd_flush_queue(pst_dmac_vap, pst_dmac_user, &uc_uapsd_left);
    OAM_INFO_LOG2(pst_event_hdr->uc_vap_id, OAM_SF_PWR,
                  "{dmac_psm_reset::dmac_uapsd_flush_queue %d send & %d left}", uc_uapsd_send, uc_uapsd_left);*/
#endif
    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_psm_awake(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user)
{
#if 0
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_device_stru     *pst_macdev;
#endif
#endif

    DMAC_PSM_CHANGE_USER_PS_STATE(pst_dmac_user->bit_ps_mode, OAL_FALSE);
    pst_dmac_user->st_ps_structure.uc_ps_time_count = 0;
    pst_dmac_vap->uc_ps_user_num--;
#if 0
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_macdev = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_doze:: mac_dev is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    dmac_psm_disable_user_to_psm_back(pst_macdev,pst_dmac_user);
#endif
#endif
    /* ????user????????user????????tid */
    dmac_user_resume(pst_dmac_user);

    /* ?????????????????????? */
    dmac_psm_queue_flush(pst_dmac_vap, pst_dmac_user);

    OAM_INFO_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR,
                  "{dmac_psm_awake::user[%d] is active.}\r\n", pst_dmac_user->st_user_base_info.us_assoc_id);

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_psm_doze(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user)
{
    mac_device_stru     *pst_macdev;

    DMAC_PSM_CHANGE_USER_PS_STATE(pst_dmac_user->bit_ps_mode, OAL_TRUE);
    pst_dmac_user->st_ps_structure.uc_ps_time_count = 0;
    pst_dmac_vap->uc_ps_user_num++;

    /* suspend???????? */
    pst_macdev = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_doze:: mac_dev is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#if 0
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#else
    hal_set_machw_tx_suspend(pst_macdev->pst_device_stru);
#endif
#endif
    hal_set_machw_tx_suspend(pst_macdev->pst_device_stru);
    /* pause??????,????????pause uapsd????tid */
    dmac_user_pause(pst_dmac_user);
    dmac_tid_resume(pst_macdev->pst_device_stru, &pst_dmac_user->ast_tx_tid_queue[WLAN_TIDNO_UAPSD], DMAC_TID_PAUSE_RESUME_TYPE_PS);

#if 0
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* ????????????????????????????????????psm */
    dmac_psm_enable_user_to_psm_back(pst_dmac_vap, pst_macdev, pst_dmac_user);
    /* ????psm??????????????PVB */
    if ((OAL_FALSE == dmac_psm_is_psm_empty(pst_dmac_user))
        || (OAL_FALSE == dmac_psm_is_tid_empty(pst_dmac_user)))
    {
        dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 1);
        OAM_INFO_LOG2(0, OAM_SF_PWR, "{dmac_psm_doze::user[%d].%d mpdu in tid.}",
                       pst_dmac_user->st_user_base_info.us_assoc_id, oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num));
    }
#else
#endif
#endif
    /* ????????????????????????????????????tid */
    dmac_psm_flush_txq_to_tid(pst_macdev, pst_dmac_vap, pst_dmac_user);

    /* ????tid??????????????PVB */
    if (OAL_FALSE == dmac_psm_is_tid_empty(pst_dmac_user))
    {
        dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 1);
        OAM_INFO_LOG2(0, OAM_SF_PWR, "{dmac_psm_doze::user[%d].%d mpdu in tid.}",
                       pst_dmac_user->st_user_base_info.us_assoc_id, dmac_psm_tid_mpdu_num(pst_dmac_user));
    }
#if 0
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#else
    /* ???????????? */
    hal_set_machw_tx_resume(pst_macdev->pst_device_stru);
#endif
#endif
    /* ???????????? */
    hal_set_machw_tx_resume(pst_macdev->pst_device_stru);
    OAM_INFO_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR,
                  "{dmac_psm_doze::user[%d] is doze.}\r\n", pst_dmac_user->st_user_base_info.us_assoc_id);

    return OAL_SUCC;
}


oal_void dmac_psm_rx_process(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_netbuf_stru *pst_net_buf)
{
    mac_ieee80211_frame_stru        *pst_mac_header;
    mac_rx_ctl_stru                 *pst_rx_ctrl;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_user || OAL_PTR_NULL == pst_net_buf))
    {
        OAM_ERROR_LOG3(0, OAM_SF_PWR, "{dmac_psm_rx_process_data::param is null.vap=[%d], user=[%d],buf=[%d]}.",
                       (oal_uint32)pst_dmac_vap, (oal_uint32)pst_dmac_user, (oal_uint32)pst_net_buf);
        return;
    }

    pst_rx_ctrl = (mac_rx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);
    pst_mac_header = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(pst_rx_ctrl);
    /*
       ??????????????(bit_power_mgmt == 1),??????????????????????????????????
       ??????????,??????????????????????????????????ap??????????????????????;
       ??????????????(bit_power_mgmt == 0),??????????????????????????????????
       ??????????????????????????????????????????????????????????????????????
       ????????????????????????????ap??????????????????????
    */
    if ((OAL_TRUE == pst_mac_header->st_frame_control.bit_power_mgmt)
         && (OAL_FALSE == pst_dmac_user->bit_ps_mode))
    {
        dmac_psm_doze(pst_dmac_vap, pst_dmac_user);
    }
    if ((OAL_FALSE == pst_mac_header->st_frame_control.bit_power_mgmt)
         && (OAL_TRUE == pst_dmac_user->bit_ps_mode))
    {
        dmac_psm_awake(pst_dmac_vap, pst_dmac_user);
    }

#ifdef _PRE_WLAN_FEATURE_P2P
    /* P2P GO??????????????????P2P OppPS????*/
    if ((OAL_FALSE == pst_mac_header->st_frame_control.bit_power_mgmt)&&
        (IS_P2P_GO(&pst_dmac_vap->st_vap_base_info))&&
        (IS_P2P_OPPPS_ENABLED(pst_dmac_vap)))
    {
        pst_dmac_vap->st_p2p_ops_param.en_pause_ops = OAL_TRUE;
    }
    /* P2P GO??????????????????????P2P OppPS*/
    if ((OAL_TRUE == pst_mac_header->st_frame_control.bit_power_mgmt)&&
        (IS_P2P_GO(&pst_dmac_vap->st_vap_base_info))&&
        (IS_P2P_OPPPS_ENABLED(pst_dmac_vap)))
    {
        pst_dmac_vap->st_p2p_ops_param.en_pause_ops = OAL_FALSE;

    }

#endif
}


OAL_INLINE oal_void dmac_psm_set_ucast_mgmt_tx_rate(dmac_vap_stru *pst_dmac_vap,
                                                    wlan_channel_band_enum_uint8 en_band,
                                                    oal_uint8 uc_legacy_rate,
                                                    wlan_phy_protocol_enum_uint8 en_protocol_mode)
{
    /* ?????????????? */
    if ((OAL_PTR_NULL == pst_dmac_vap) || (en_band >= WLAN_BAND_BUTT))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PWR, "{dmac_psm_set_ucast_mgmt_tx_rate::input param error, pst_dmac_vap[%p], band[%d].}",
                       pst_dmac_vap, en_band);
        return;
    }
    /* ??????????0??????,1 2 3????????????,????????????????????????null?? */
    pst_dmac_vap->ast_tx_mgmt_ucast[en_band].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = uc_legacy_rate;
    pst_dmac_vap->ast_tx_mgmt_ucast[en_band].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = en_protocol_mode;
    return;
}


oal_uint32  dmac_psm_send_null_data(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_bool_enum_uint8 en_ps)
{
    oal_netbuf_stru                 *pst_net_buf;
    mac_tx_ctl_stru                 *pst_tx_ctrl;
    oal_uint32                       ul_ret;
    oal_uint16                       us_tx_direction = WLAN_FRAME_FROM_AP;
    mac_ieee80211_frame_stru        *pst_mac_header;
    oal_uint8                        uc_legacy_rate;
    wlan_phy_protocol_enum_uint8     en_protocol_mode;
    oal_uint8                        uc_null_protocol_mode;
    oal_uint8                        uc_null_legacy_rate;
    mac_device_stru                 *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                        "dmac_psm_send_null_data: mac_device is null.device_id[%d]",
                        pst_dmac_vap->st_vap_base_info.uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if ((MAC_SCAN_STATE_RUNNING == pst_mac_device->en_curr_scan_state) &&
        (MAC_VAP_STATE_PAUSE == pst_dmac_vap->st_vap_base_info.en_vap_state))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                        "dmac_psm_send_null_data: device is scaning and vap status is pause, do not send null!vap_mode[%d]",
                        pst_dmac_vap->st_vap_base_info.en_vap_mode);
        return OAL_FAIL;
    }

#ifdef _PRE_WLAN_FEATURE_P2P
    if (WLAN_P2P_DEV_MODE == mac_get_p2p_mode(&pst_dmac_vap->st_vap_base_info))
    {
        return OAL_FAIL;
    }
#endif

    /* ????net_buff */
    pst_net_buf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_SHORT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_HIGH);
    if (OAL_PTR_NULL == pst_net_buf)
    {
        
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_send_null_data::pst_net_buf null.}");
        OAL_MEM_INFO_PRINT(OAL_MEM_POOL_ID_NETBUF);
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    OAL_MEM_NETBUF_TRACE(pst_net_buf, OAL_TRUE);

    oal_set_netbuf_prev(pst_net_buf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_net_buf, OAL_PTR_NULL);

    /* null??????????From AP || To AP */
    us_tx_direction = (WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode) ? WLAN_FRAME_FROM_AP : WLAN_FRAME_TO_AP;
    /* ????????,????from ds??1??to ds??0??????frame control??????????????02 */
    mac_null_data_encap(OAL_NETBUF_HEADER(pst_net_buf),
                        ((oal_uint16)(WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_NODATA) | us_tx_direction),
                        pst_dmac_user->st_user_base_info.auc_user_mac_addr,
                        pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
    pst_mac_header = (mac_ieee80211_frame_stru*)OAL_NETBUF_HEADER(pst_net_buf);

    /*  NB: power management bit is never sent by an AP */
    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        pst_mac_header->st_frame_control.bit_power_mgmt = en_ps;
    }

    /* ????cb???? */
    pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);
    OAL_MEMZERO(pst_tx_ctrl, OAL_SIZEOF(mac_tx_ctl_stru));

    /* ????tx???? */
    mac_set_cb_ack_policy(pst_tx_ctrl, WLAN_TX_NORMAL_ACK);
    MAC_GET_CB_EVENT_TYPE(pst_tx_ctrl)         = FRW_EVENT_TYPE_WLAN_DTX;
    mac_set_cb_is_bar(pst_tx_ctrl, OAL_FALSE);
    MAC_GET_CB_IS_FIRST_MSDU(pst_tx_ctrl)         = OAL_TRUE;
    MAC_GET_CB_RETRIED_NUM(pst_tx_ctrl)           = 0;
    mac_set_cb_tid(pst_tx_ctrl, WLAN_TID_FOR_DATA);
    MAC_GET_CB_TX_VAP_INDEX(pst_tx_ctrl)          = pst_dmac_vap->st_vap_base_info.uc_vap_id;
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctrl)           = (oal_uint8) pst_dmac_user->st_user_base_info.us_assoc_id;

    /* ????tx rx???????? */
    //MAC_GET_CB_FRAME_TYPE(pst_tx_ctrl)          = WLAN_DATA_NULL;
    MAC_GET_CB_IS_MCAST(pst_tx_ctrl)            = OAL_FALSE;
    mac_set_cb_is_amsdu(pst_tx_ctrl, OAL_FALSE);

#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    if (IS_AP(&(pst_dmac_vap->st_vap_base_info)))
    {
        MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctrl)   = OAL_FALSE;/* AP ????null ?????????????? */
    }
    else
#endif  /* defined(_PRE_PRODUCT_ID_HI110X_DEV) */
    {
        MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctrl)   = OAL_TRUE;
    }
    MAC_GET_CB_IS_PROBE_DATA(pst_tx_ctrl)       = OAL_FALSE;
    mac_set_cb_is_use_4_addr(pst_tx_ctrl, OAL_FALSE);
    mac_set_cb_frame_hdr(pst_tx_ctrl, (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_net_buf));
    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctrl)    = OAL_SIZEOF(mac_ieee80211_frame_stru);
    MAC_GET_CB_MPDU_NUM(pst_tx_ctrl)               = 1;
    MAC_GET_CB_NETBUF_NUM(pst_tx_ctrl)             = 1;
    MAC_GET_CB_MPDU_LEN(pst_tx_ctrl)               = 0;
    mac_set_cb_ac(pst_tx_ctrl, WLAN_WME_AC_MGMT);


    /* 2.4G????????11b 1M, long preable, ????null??????????11g/a?????? */
    uc_legacy_rate   = pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate;
    en_protocol_mode = pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
    dmac_change_null_data_rate(pst_dmac_vap,pst_dmac_user,&uc_null_protocol_mode, &uc_null_legacy_rate);

    dmac_psm_set_ucast_mgmt_tx_rate(pst_dmac_vap, WLAN_BAND_2G, uc_null_legacy_rate, uc_null_protocol_mode);

    ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_net_buf, OAL_SIZEOF(mac_ieee80211_frame_stru));

    /* ????????????????????: 2.4G????????11b 1M, long preable */
    dmac_psm_set_ucast_mgmt_tx_rate(pst_dmac_vap, WLAN_BAND_2G, uc_legacy_rate, en_protocol_mode);

    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                         "{dmac_psm_send_null_data::dmac_tx_mgmt failed[%d].}", ul_ret);
        if (OAL_LIKELY(OAL_PTR_NULL != pst_dmac_user->st_ps_structure.pst_psm_stats))
        {
            DMAC_PSM_STATS_INCR(pst_dmac_user->st_ps_structure.pst_psm_stats->ul_psm_send_null_fail_cnt);
        }

        dmac_tx_excp_free_netbuf(pst_net_buf);
        return ul_ret;
    }

    return OAL_SUCC;
}


OAL_STATIC oal_uint32 dmac_psm_sch_tid_queue(dmac_user_stru  *pst_dmac_user, oal_uint32 ul_ps_mpdu_num)
{
    mac_device_stru              *pst_macdev         = OAL_PTR_NULL;
    oal_dlist_head_stru          *pst_dlist_pos      = OAL_PTR_NULL;
    hal_tx_dscr_stru             *pst_tx_dscr        = OAL_PTR_NULL;
    oal_netbuf_stru              *pst_mgmt_buf       = OAL_PTR_NULL;
    oal_uint8                     uc_tid_idx         = 0;
#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    dmac_tid_stru                *pst_txtid;
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
    pst_macdev = mac_res_get_dev(pst_dmac_user->st_user_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_sch_tid_queue:: mac_device is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    /* ?????????????? */
    for (uc_tid_idx = 0; uc_tid_idx < WLAN_TID_MAX_NUM; uc_tid_idx ++)
    {
        pst_txtid = &pst_dmac_user->ast_tx_tid_queue[uc_tid_idx];
        if (OAL_TRUE == oal_dlist_is_empty(&pst_txtid->st_retry_q))
        {
            continue;
        }
        OAL_DLIST_SEARCH_FOR_EACH(pst_dlist_pos, &pst_txtid->st_retry_q)
        {
            /* ??????????????????????TID?????????????? */
            dmac_tid_resume(pst_macdev->pst_device_stru, pst_txtid, DMAC_TID_PAUSE_RESUME_TYPE_PS);

            /* ????????????????????TID????????????mpdu??????????moredata */
            if (ul_ps_mpdu_num > 1)
            {
                pst_tx_dscr  = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
                pst_mgmt_buf = pst_tx_dscr->pst_skb_start_addr;
                dmac_psm_set_more_data(pst_mgmt_buf);
            }

            return OAL_SUCC;
        }
    }


    /* ?????????????? */
    for (uc_tid_idx = 0; uc_tid_idx < WLAN_TID_MAX_NUM; uc_tid_idx ++)
    {
        pst_txtid = &pst_dmac_user->ast_tx_tid_queue[uc_tid_idx];
        if (OAL_TRUE == oal_netbuf_list_empty(&pst_txtid->st_buff_head))
        {
            continue;
        }

        OAL_NETBUF_SEARCH_FOR_EACH(pst_mgmt_buf, &pst_txtid->st_buff_head)
        {
            /* ??????????????????????TID?????????????? */
            dmac_tid_resume(pst_macdev->pst_device_stru, pst_txtid, DMAC_TID_PAUSE_RESUME_TYPE_PS);

            /* ????????????????????TID????????????mpdu??????????moredata */
            if (ul_ps_mpdu_num > 1)
            {
                dmac_psm_set_more_data(pst_mgmt_buf);
            }

            return OAL_SUCC;
        }
    }
#else
    for (uc_tid_idx = 0; uc_tid_idx < WLAN_TID_MAX_NUM; uc_tid_idx ++)
    {
        if (OAL_TRUE == oal_dlist_is_empty(&pst_dmac_user->ast_tx_tid_queue[uc_tid_idx].st_hdr))
        {
            continue;
        }
        OAL_DLIST_SEARCH_FOR_EACH(pst_dlist_pos, &pst_dmac_user->ast_tx_tid_queue[uc_tid_idx].st_hdr)
        {
            /* ??????????????????????TID?????????????? */
            dmac_tid_resume(pst_macdev->pst_device_stru, &pst_dmac_user->ast_tx_tid_queue[uc_tid_idx], DMAC_TID_PAUSE_RESUME_TYPE_PS);

            /* ????????????????????TID????????????mpdu??????????moredata */
            if (ul_ps_mpdu_num > 1)
            {
                pst_tx_dscr  = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
                pst_mgmt_buf = pst_tx_dscr->pst_skb_start_addr;
                dmac_psm_set_more_data(pst_mgmt_buf);
            }
            break;
        }
    }
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_psm_sch_psm_queue(dmac_vap_stru *pst_dmac_vap, dmac_user_stru  *pst_dmac_user)
{
    oal_int32              l_ps_mpdu_num;
    oal_uint32             ul_ret;

    l_ps_mpdu_num       = oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num);

    if (l_ps_mpdu_num > 0)
    {
        ul_ret = dmac_psm_queue_send(pst_dmac_vap, pst_dmac_user);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG3(0, OAM_SF_PWR, "{dmac_psm_sch_psm_queue::user[%d] send fail[%d] & %d left.}",
                           pst_dmac_user->st_user_base_info.us_assoc_id, ul_ret, l_ps_mpdu_num - 1);
            return ul_ret;
        }
        OAM_INFO_LOG2(0, OAM_SF_PWR, "{dmac_psm_sch_psm_queue::user[%d] send 1 & %d left}",
                       pst_dmac_user->st_user_base_info.us_assoc_id, l_ps_mpdu_num - 1);
    }

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_psm_handle_pspoll(dmac_vap_stru *pst_dmac_vap, dmac_user_stru  *pst_dmac_user, oal_uint8 *puc_extra_qosnull)
{
    oal_uint32                    ul_ret            = OAL_SUCC;
    oal_uint32                    ul_tid_mpud_num   = 0;
#if 0
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_device_stru             *pst_macdev;
#endif
#endif

    /* ????tid?????? */
    ul_tid_mpud_num  = dmac_psm_tid_mpdu_num(pst_dmac_user);
#if 0
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_macdev = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_doze:: mac_dev is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    dmac_psm_disable_user_to_psm_back(pst_macdev,pst_dmac_user);
#endif
#endif

    if (ul_tid_mpud_num)
    {
        ul_tid_mpud_num += (oal_uint32)oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num);
        ul_ret = dmac_psm_sch_tid_queue(pst_dmac_user, ul_tid_mpud_num);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(0, OAM_SF_PWR, "{dmac_psm_handle_pspoll::dmac_psm_sch_tid_queue fail[%d].}", ul_ret);
            return ul_ret;
        }
        if (ul_tid_mpud_num == 1)
        {
            dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 0);
        }
    }
    /* ????psm?????????? */
    else if(oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num))
    {
        ul_ret = dmac_psm_sch_psm_queue(pst_dmac_vap, pst_dmac_user);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_PWR, "{dmac_psm_handle_pspoll::dmac_psm_sch_psm_queue fail[%d].}", ul_ret);
            return ul_ret;
        }
        if (0 == oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num))
        {
            dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 0);
        }
    }
    else
    {
        *puc_extra_qosnull = 1;
        return OAL_SUCC;
    }
    pst_dmac_user->st_ps_structure.en_is_pspoll_rsp_processing = OAL_TRUE;

    return ul_ret;
}


oal_uint32 dmac_psm_resv_ps_poll(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user)
{
    oal_uint32          ul_ret;
    oal_uint8           uc_extra_qosnull = 0;
#ifdef _PRE_WLAN_DFT_STAT
    dmac_user_psm_stats_stru *pst_psm_stats;

    pst_psm_stats = pst_dmac_user->st_ps_structure.pst_psm_stats;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_psm_stats))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_resv_ps_poll::psm_stats is null!.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif

    /* ????vap???? */
    if (WLAN_VAP_MODE_BSS_AP != pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                         "{dmac_psm_resv_ps_poll::ap is not in ap mode.}");
        return OAL_SUCC;
    }

    /* ??????????ps-poll??????????????????????????????ps-poll?????????? */
    if (OAL_TRUE == pst_dmac_user->st_ps_structure.en_is_pspoll_rsp_processing)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                         "{dmac_psm_resv_ps_poll::ignor excess ps-poll.}");
        return OAL_SUCC;
    }

    ul_ret = dmac_psm_handle_pspoll(pst_dmac_vap, pst_dmac_user, &uc_extra_qosnull);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                         "{dmac_psm_resv_ps_poll::hand_pspoll return [%d].}", ul_ret);
        DMAC_PSM_STATS_INCR(pst_psm_stats->ul_psm_rsp_pspoll_fail_cnt);
        return ul_ret;
    }

    if (uc_extra_qosnull)
    {
        dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 0);
        DMAC_PSM_STATS_INCR(pst_psm_stats->ul_psm_resv_pspoll_send_null);
        ul_ret = dmac_psm_send_null_data(pst_dmac_vap, pst_dmac_user, OAL_FALSE);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                             "{dmac_psm_resv_ps_poll::user[%d] send_null fail[%d].}", ul_ret);
        }
        return ul_ret;
    }

    DMAC_PSM_STATS_INCR(pst_psm_stats->ul_psm_rsp_pspoll_succ_cnt);
    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY

oal_uint32 dmac_psm_opmode_notify_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru          *pst_event;
    frw_event_hdr_stru      *pst_event_hdr;
    oal_uint16              *pus_user_id;
    dmac_user_stru          *pst_dmac_user;
    dmac_vap_stru           *pst_dmac_vap;

    if ((OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_psm_opmode_notify_process::pst_event_mem is NULL!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ????????????????????????payload?????? */
    pst_event       = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr   = &(pst_event->st_event_hdr);
    pus_user_id     = (oal_uint16 *)pst_event->auc_event_data;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(*pus_user_id);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_ANY, "{dmac_psm_opmode_notify_process::pst_mac_user is null, user id is = [%d]!}\r\n", *pus_user_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_psm_opmode_notify_process::pst_dmac_vap is NULL!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == pst_dmac_user->bit_ps_mode)
    {
        //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{mac_ie_proc_opmode_field::user changes ps mode to powersave!}\r\n");
        DMAC_PSM_CHANGE_USER_PS_STATE(pst_dmac_user->bit_ps_mode, OAL_TRUE);
        pst_dmac_vap->uc_ps_user_num++;
    }

    return OAL_SUCC;
}
#endif


oal_void  dmac_change_null_data_rate(dmac_vap_stru *pst_dmac_vap,dmac_user_stru *pst_dmac_user,oal_uint8 *uc_protocol_mode,oal_uint8 *uc_legacy_rate)
{
    switch (pst_dmac_user->st_user_base_info.en_avail_protocol_mode)
    {
        /* 11b 1M */
        case WLAN_LEGACY_11B_MODE:
            if (WLAN_BAND_2G == pst_dmac_vap->st_vap_base_info.st_channel.en_band)
            {
                *uc_protocol_mode = WLAN_11B_PHY_PROTOCOL_MODE;
                *uc_legacy_rate   = 0x1;
#ifdef _PRE_WLAN_FEATURE_P2P
                /* P2P ???????????????? */
                if (!IS_LEGACY_VAP((&pst_dmac_vap->st_vap_base_info)))
                {
                    *uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
                    *uc_legacy_rate   = 0xB;
                }
#endif
            }
            else
            {
                *uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
                *uc_legacy_rate   = 0xB;
            }
            break;

        /* OFDM 6M */
        case WLAN_MIXED_ONE_11G_MODE:
        case WLAN_HT_MODE:
        case WLAN_LEGACY_11A_MODE:
        case WLAN_LEGACY_11G_MODE:
        case WLAN_MIXED_TWO_11G_MODE:
        case WLAN_VHT_MODE:
        case WLAN_HT_11G_MODE:
            *uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
            *uc_legacy_rate   = 0xB;
            break;

        /* OFDM 24M */
        case WLAN_HT_ONLY_MODE:
        case WLAN_VHT_ONLY_MODE:
            *uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
            *uc_legacy_rate   = 0x9;
            break;

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                             "{dmac_change_null_data_rate::invalid en_protocol[%d].}", pst_dmac_user->st_user_base_info.en_avail_protocol_mode);
            return;
    }


}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

