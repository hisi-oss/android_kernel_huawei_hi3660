


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "oal_profiling.h"
#include "oam_ext_if.h"
#include "frw_ext_if.h"
#include "wlan_spec.h"

#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
#include "hal_ext_if.h"
#endif

#include "hmac_vap.h"
#include "mac_vap.h"
#include "mac_resource.h"
#include "mac_data.h"
#include "hmac_ext_if.h"

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#include "hmac_vap.h"
#endif

#include "wal_main.h"
#include "wal_linux_bridge.h"

#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "hmac_device.h"
#include "hmac_resource.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_LINUX_BRIDGE_C


/*****************************************************************************
  2 ????????????
*****************************************************************************/


/*****************************************************************************
  3 ????????
*****************************************************************************/
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)


oal_net_dev_tx_enum  wal_vap_start_xmit(oal_netbuf_stru *pst_buf, oal_net_device_stru *pst_dev)
{
    return hmac_vap_start_xmit(pst_buf, pst_dev);
}

#endif


oal_uint8    g_sk_pacing_shift = 6;

oal_net_dev_tx_enum  wal_bridge_vap_xmit(oal_netbuf_stru *pst_buf, oal_net_device_stru *pst_dev)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    if (OAL_UNLIKELY(skb_linearize(pst_buf)))
    {
        OAM_WARNING_LOG0(0, OAM_SF_TX, "{wal_bridge_vap_xmit::[GSO] failed at skb_linearize}");
        oal_netbuf_free(pst_buf);
        return OAL_NETDEV_TX_OK;
    }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,9,0))
    sk_pacing_shift_update(pst_buf->sk, g_sk_pacing_shift);
#endif
#endif /* _PRE_OS_VERSION_LINUX == _PRE_OS_VERSION */

    return hmac_bridge_vap_xmit(pst_buf, pst_dev);
}

/*lint -e19*/
oal_module_symbol(wal_bridge_vap_xmit);
/*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

