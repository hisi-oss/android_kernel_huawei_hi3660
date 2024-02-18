

#ifndef __PLATFORM_COMMON_CLK_H__
#define __PLATFORM_COMMON_CLK_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "oal_types.h"
#include "plat_type.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_PLATFORM_COMMON_CLK_H

/*****************************************************************************
  2 ??????
*****************************************************************************/

#define HI_STATIC_ASSERT(cond_, name_)  typedef char assert_failed_ ## name_ [ (cond_) ? 1 : -1 ]


#define DCXO_DEVICE_MAX_BUF_LEN         64
#define DCXO_CALI_DATA_BUF_LEN          (sizeof(dcxo_dl_para_stru))

/*??????DCXO ??????NV????????*/

#define MALLOC_LEN                      104
#define NV_NUM                          2
#define NV_GNSS_ID                      236
#define NV_GNSS_SIZE                    32
#define NV_GNSS_NAME                    "XOCOE"
#define NV_FAC_ID                       235
#define NV_FAC_SIZE                     88
#define NV_FAC_NAME                     "XOA1A0"
#define PLAT_DEF_ID                    (-1)
#define PLAT_DEF_NAME                   "PLAT_DEF_COEFF"
#define NVRAM_READ                      1
#define NV_MIN_PAIR_POS                 1
#define NV_MAX_PAIR_POS                 0
#define NV_CHK_PAIR                     2
#define COEFF_NUM                       5
#define GNSS_COEFF_NUM                  4
#define RSV_NUM                         2
#define DCXO_NV_CHK_OK                  1
#define T0_BIT_WIDTH_10                 0
#define T0_WIDTH10_TO_WIDTH16           (1 << 6)
#define DCXO_PARA_READ_OK               0x01

#define DEFAULT_T0                      0x1E0000
#define DEFAULT_A0                      0
#define DEFAULT_A1                      0x1c0000
#define DEFAULT_A2                      0
#define DEFAULT_A3                      0x68db8b
#define DEFAULT_MODE                    0
#define DCXO_CHECK_MAGIC                0xA0A0A0A0

#define COEFF_TP                        0xFFFFFFFF
#define COEFF_BT                        0


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
    oal_int32 para[COEFF_NUM];         //????a0, a1, a2, a3, t0
    oal_int32 reserve[RSV_NUM];
}dcxo_coeff_stru;

typedef struct
{
    oal_int32 check_value[COEFF_NUM][NV_CHK_PAIR];
    oal_int32 t0_bit_width_fix;        // 0: t0????????10????????????2^6????, 1:t0????????16??????????????
}dcxo_nv_coeff_th_stru;


typedef struct
{
    oal_int32                   valid;
    union {
        dcxo_coeff_stru         fac;
        struct {
            oal_uint32 para[GNSS_COEFF_NUM];
        }                       gnss;
    } coeff_u;
    dcxo_nv_coeff_th_stru       coeff_th;
}dcxo_nv_info_stru;


typedef struct
{
    dcxo_coeff_stru coeff;
    oal_uint32      tcxo_dcxo_flag;
    oal_uint32      check_data;
}dcxo_dl_para_stru;

// ????devcie??????????????????????????????????
HI_STATIC_ASSERT((DCXO_DEVICE_MAX_BUF_LEN > (sizeof(dcxo_dl_para_stru))), device_mem_must_big_than_host);


typedef struct
{
    oal_uint32      use_part_id;
    int64           nv_init_flag;
}dcxo_manage_stru;


/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/
extern oal_uint8 *g_pucDcxoDataBuf;
extern dcxo_manage_stru g_st_dcxo_info;

/*****************************************************************************
  10 ????????
*****************************************************************************/
extern oal_void update_dcxo_coeff(oal_uint32 *coeff);
extern oal_int32 read_dcxo_cali_data(oal_void);
extern oal_int32 dcxo_data_buf_malloc(oal_void);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of platform_common_clk.h */
