

#ifndef __WLAN_SPEC_H__
#define __WLAN_SPEC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "platform_spec.h"
#include "wlan_types.h"
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))
#include "wlan_spec_1102.h"
#elif ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_HOST))
#include "wlan_spec_1103.h"
#elif (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#include "wlan_spec_1151.h"
#endif

/*****************************************************************************
  2 ??????
*****************************************************************************/
#define ALG_SCH_WMM_ENSURE                      1       /* ????WMM???? */
#define ALG_SCH_ROUND_ROBIN                     2       /* ???????? */
#define ALG_SCH_PROPO_FAIR                      3       /* ???????????? */

#define WLAN_MU_BFEE_ENABLE                     1       /* ????mu bfee */
#define WLAN_MU_BFEE_DISABLE                    0       /* ??????mu bfee */

#define WLAN_M2S_BLACKLIST_MAX_NUM             (16)    /* m2s???????????????????????????????????? */

#define WLAN_NSS_MAX_NUM_LIMIT                             (WLAN_MAX_NSS_NUM + 1)  /* ????????????????????????????????+1 */
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
/* hal device id ????*/
typedef enum {
    HAL_DEVICE_ID_MASTER        = 0,    /* master??hal device id */
    HAL_DEVICE_ID_SLAVE         = 1,    /* slave??hal device id */

    HAL_DEVICE_ID_BUTT                  /* ????id */
} hal_device_id_enum;
typedef oal_uint8 hal_device_id_enum_enum_uint8;


/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/
/* TX ?????? 12?? b23:b22 phy???????? */
/* hmac????phy????????????, ?????????? */
typedef enum
{
    WLAN_11B_PHY_PROTOCOL_MODE              = 0,   /* 11b CCK */
    WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE      = 1,   /* 11g/a OFDM */
    WLAN_HT_PHY_PROTOCOL_MODE               = 2,   /* 11n HT */
    WLAN_VHT_PHY_PROTOCOL_MODE              = 3,   /* 11ac VHT */
#ifdef _PRE_WLAN_FEATURE_11AX
    WLAN_HE_SU_FORMAT                       = 0,
    WLAN_HE_MU_FORMAT                       = 1,   /*??1103????????*/
    WLAN_HE_EXT_SU_FORMAT                   = 2,
    WLAN_HE_TRIG_FORMAT                     = 3,
#endif
    WLAN_PHY_PROTOCOL_BUTT                  = 4,
}wlan_phy_protocol_enum;
typedef oal_uint8 wlan_phy_protocol_enum_uint8;

#ifdef _PRE_WLAN_1103_PILOT
typedef enum
{
    WLAN_PHY_HE_GI_POINT8us   = 0,
    WLAN_PHY_HE_GI_1POINT6us  = 1,
    WLAN_PHY_HE_GI_3POINT2us  = 2,
    WLAN_PHY_HE_GI_BUTT
}wlan_phy_he_gi_type_enum;
typedef oal_uint8 wlan_phy_he_gi_type_enum_uint8;

typedef enum
{
    WLAN_PHY_HE_LTF_1x   = 0,
    WLAN_PHY_HE_LTF_2x   = 1,
    WLAN_PHY_HE_LTF_4x   = 2,
    WLAN_PHY_HE_LTF_BUTT
}wlan_phy_he_ltf_type_enum;
typedef oal_uint8 wlan_phy_he_ltf_type_enum_uint8;


#endif



/*****************************************************************************
  10 ????????
*****************************************************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of wlan_spec.h */

