


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "mac_user.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_USER_RAM_C

/*****************************************************************************
  2 ????????????
*****************************************************************************/


/*****************************************************************************
  3 ????????
*****************************************************************************/

oal_rom_cb_result_enum_uint8 mac_user_init_cb(mac_user_stru *pst_mac_user, oal_uint32 *pul_cb_ret)
{
    *pul_cb_ret = OAL_SUCC;

    return OAL_CONTINUE;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

