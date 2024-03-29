

#ifndef __HMAC_ENCAP_FRAME_H__
#define __HMAC_ENCAP_FRAME_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "oal_ext_if.h"
#include "hmac_user.h"
#include "mac_vap.h"

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


/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/
extern oal_uint16  hmac_mgmt_encap_deauth(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_data, oal_uint8 *puc_da, oal_uint16 us_err_code);
extern oal_uint16  hmac_mgmt_encap_disassoc(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_data, oal_uint8 *puc_da, oal_uint16 us_err_code);
extern oal_uint16  hmac_encap_sa_query_req(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_data, oal_uint8 *puc_da,oal_uint16 us_trans_id);
extern oal_uint16  hmac_encap_sa_query_rsp(mac_vap_stru *pst_mac_vap, oal_uint8 *pst_hdr, oal_uint8 *puc_data);
extern oal_void  hmac_check_sta_base_rate(oal_uint8 *pst_user, mac_status_code_enum_uint16 *pen_status_code);
extern oal_uint16 hmac_encap_notify_chan_width(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_data, oal_uint8 *puc_da);










#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_encap_frame.h */
