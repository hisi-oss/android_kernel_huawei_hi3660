


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "mac_frame.h"
#include "mac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_FRAME_RAM_C

/*****************************************************************************
  2 ????????????
*****************************************************************************/


/*****************************************************************************
  3 ????????????
*****************************************************************************/


/*****************************************************************************
  4 ????????
*****************************************************************************/


oal_void mac_set_rrm_enabled_cap_field_cb(oal_void *pst_vap, oal_uint8 *puc_buffer, oal_uint8 *puc_ie_len)
{
}


oal_void mac_set_vht_capabilities_ie_cb(oal_void *pst_vap, oal_uint8 *puc_buffer, oal_uint8 *puc_ie_len)
{
}

oal_void mac_set_ht_capabilities_ie_cb(oal_void *pst_vap, oal_uint8 *puc_buffer, oal_uint8 *puc_ie_len)
{
    mac_frame_ht_cap_stru *pst_ht_capinfo;
    mac_vap_stru          *pst_mac_vap;

    pst_mac_vap = (mac_vap_stru *)pst_vap;
    /* ??????pucbuffer??????????ht cap ie?????? */
    puc_buffer -= (MAC_IE_HDR_LEN + MAC_HT_CAPINFO_LEN + MAC_HT_AMPDU_PARAMS_LEN + MAC_HT_SUP_MCS_SET_LEN + MAC_HT_EXT_CAP_LEN + MAC_HT_TXBF_CAP_LEN);
    /* ???????????????????????????????????????????????????????? */
    puc_buffer += MAC_IE_HDR_LEN;
    /* ????ht_capinfo_field */
    pst_ht_capinfo = (mac_frame_ht_cap_stru *)puc_buffer;
    pst_ht_capinfo->bit_lsig_txop_protection = mac_mib_get_LsigTxopFullProtectionActivated(pst_mac_vap);
    
}


oal_void mac_set_ext_capabilities_ie_cb(oal_void *pst_mac_vap, oal_uint8 *puc_buffer, oal_uint8 *puc_ie_len)
{
}


oal_rom_cb_result_enum_uint8 mac_set_rsn_ie_cb(oal_void *pst_vap, oal_uint8 *puc_pmkid, oal_uint8 *puc_buffer, oal_uint8 *puc_ie_len, oal_uint32 *pul_ret)
{
    return OAL_CONTINUE;
}


oal_rom_cb_result_enum_uint8 mac_set_wpa_ie_cb(oal_void *pst_vap, oal_uint8 *puc_buffer, oal_uint8 *puc_ie_len, oal_uint32 *pul_ret)
{
    return OAL_CONTINUE;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

