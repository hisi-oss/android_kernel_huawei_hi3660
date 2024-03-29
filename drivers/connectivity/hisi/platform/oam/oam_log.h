

#ifndef __OAM_LOG_H__
#define __OAM_LOG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "oal_ext_if.h"

/*****************************************************************************
  2 ??????
*****************************************************************************/
#define OAM_LOG_PARAM_MAX_NUM           4                                       /* ???????????????????? */
#define OAM_LOG_PRINT_DATA_LENGTH       512                                     /* ?????????????????????? */

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
typedef struct
{
    oal_uint32  bit16_file_id:   16;
    oal_uint32  bit8_feature_id: 8;
    oal_uint32  bit4_vap_id:     4;
    oal_uint32  bit4_log_level:  4;
}om_log_wifi_para_stru;
/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/
extern oal_uint32  oam_log_init(oal_void);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oam_log.h */
