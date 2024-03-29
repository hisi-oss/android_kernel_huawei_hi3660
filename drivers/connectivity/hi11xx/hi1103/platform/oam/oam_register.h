

#ifndef __OAM_REGISTER_H__
#define __OAM_REGISTER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
//#include "oam_main.h"
#include "oam_ext_if.h"
#include "oal_ext_if.h"


//#include "hal_ext_if.h"
#ifdef _PRE_WLAN_DFT_REG


/*****************************************************************************
  2 ??????
*****************************************************************************/
#define OAM_REG_PRD_DFT                 (oal_uint32)1   /* ?????????????????????????? */
#define OAM_REG_TYPE_NUM                (oal_uint8)5
#define OAM_REG_NAME_MAX_LEN            (oal_uint8)32
#define OAM_REG_REFRESH_EVT_LEN         (oal_uint8)8
#define OAM_REGSTER_REFRESH_TIME_MS     (oal_uint8)100
#define OAM_REG_MAX_RETRY_TIME          (oal_uint32)(200)
#define OAM_REG_UNIT_MAX_LEN            (oal_uint32)(32)        /* ???????????????? */
#define OAM_REG_MAX_RPT_NUM_ONE_TIME    (oal_uint32)(64)

#define OAM_REG_MAX_SEND_BUF_SIZE       (oal_uint32)2000


//#define OAM_REG_MAX_MAC_NUM     OAL_ARRAY_SIZE(g_ast_mac_reg)
//#define OAM_REG_MAX_PHY_NUM     OAL_ARRAY_SIZE(g_ast_phy_reg)
//#define OAM_REG_MAX_SOC_NUM     OAL_ARRAY_SIZE(g_ast_soc_reg)



#define OAM_REG_RPT_START               0
#define OAM_REG_RPT_DATA                1
#define OAM_REG_RPT_END                 2

#define OAM_PHY_REG_NUM             OAL_ARRAY_SIZE(g_ast_phy_reg)
#define OAM_SOC_REG_NUM             OAL_ARRAY_SIZE(g_ast_soc_reg)
#define OAM_MAC_REG_NUM             OAL_ARRAY_SIZE(g_ast_mac_reg)


#define OAM_REG_NETLINK_SEND(puc_data, ul_data_len, en_type) do{\
g_st_oam_reg_mng_etc.ul_rpt_count++;\
oam_netlink_kernel_send_etc((puc_data), (ul_data_len), en_type);\
l_bytes = oam_netlink_kernel_send_etc(puc_data, ul_data_len, en_type);\
    if (l_bytes <= 0)\
    {\
        OAL_IO_PRINT("netlink l_bytes is invalid.Try again! the bytes is %u\n", l_bytes);\
        return OAL_FAIL;\
    }\
}while(0);


typedef enum
{
    OAM_REG_PHY = 0,
    OAM_REG_SOC = 1,
    OAM_REG_MAC = 2,
    OAM_REG_ABB = 3,
    OAM_REG_RF  = 4,
    OAM_REG_BUTT,
}oam_reg_type_enum;
typedef oal_uint32 oam_reg_type_enum_uint8;



/*****************************************************************************
  3 ????????
*****************************************************************************/
typedef enum
{
    OAM_REG_EVT_TX      = 0,     /* ???????? */
    OAM_REG_EVT_RX      = 1,     /* ???????? */
    OAM_REG_EVT_TBTT    = 2,     /* TBTT???? */
    OAM_REG_EVT_PRD     = 3,     /* ?????????? */
    OAM_REG_EVT_USR     = 4,     /* ???????? */
    OAM_REG_EVT_ERR     = 5,     /* ???????? */
    OAM_REG_EVT_BUTT,
}oam_reg_evt_enum;
typedef oal_uint32 oam_reg_evt_enum_uint32;


typedef enum
{
    /* mac ??????6????mac */
    PG_REG = 0x01,
    PA_REG = 0x02,
    CE_REG = 0x04,

    /* phy ??????4????phy*/
    PHY_REG_BANK0 = 0x200,
    PHY_REG_BANK1 = 0x400,
    PHY_REG_BANK2 = 0x800,
    PHY_REG_BANK3 = 0x1000,
    PHY_REG_BANK4 = 0x2000,

    /* soc ??????3????soc*/
    GLB_SYS_CTL_REGBANK = 0x40000,
    PMU_CMU_CTL_REGBANK = 0x80000,
    RF_ABB_CTL_REGBANK  = 0x100000,
    LCL_CTL_REGBANK     = 0x200000,
    SSI_BRG_REGBANK     = 0x400000,
    SSI_EFUSE_REGBANK   = 0x800000,

    OAM_SUBREG_ALL = 0xffffffff
}oam_reg_subtype_enum;
typedef oal_uint32 oam_reg_subtype_enum_uint32;

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
    oal_int8                       *pc_name;
    oal_uint32                      ul_addr;
    oal_uint32                      ul_sub_type;
}oam_reg_cfg_stru;

typedef struct
{
    oam_reg_cfg_stru    *pst_reg_cfg;               /* ?????????????? */
    oal_uint32           ul_value;                  /* ??????????????????????????*/
    oal_bool_enum_uint8  en_rpt_flag;               /* ?????????????????????? */
    oal_uint8            auc_reserve[3];
}oam_reg_stru;

typedef struct
{
    oal_work_stru                            st_wk;
    oal_netbuf_head_stru                     st_netbuf_head;
}oam_reg_workqueue_stru;

typedef struct
{
    oal_uint32                               ul_pkt_num;
    oal_uint32                               ul_sn;
}oam_reg_send_head_stru;



typedef struct
{
    oal_uint32              aul_refresh_evt[OAM_REG_EVT_BUTT];     /* ???????????????????????????????? */
    oal_uint32              aul_evt_tick[OAM_REG_EVT_BUTT];       /* ????evt??????????,??????0?????????????????? */
    oal_uint32              aul_evt_tick_cfg[OAM_REG_EVT_BUTT];   /* ??????????????evt?????? */

    oal_bool_enum_uint8     en_refresh_flag;                      /* ?????????????????????????????????????????????????????????? */
    oal_uint8               uc_ack_flag;        /* ????app?????????????????? */
    oal_bool_enum_uint8     en_netbuf_flag;        /* ??workqueue????????netbuf????????0 */
    oal_uint8               uc_reserve[1];

    oal_uint32              ul_refresh_cnt;     /* ???????????????????? */
    oal_uint32              ul_time_stamp_start;      /* ??????????????????????????*/
    oal_uint32              ul_time_stamp_end;      /* ??????????????????????????*/
    oam_reg_evt_enum_uint32 en_evt_type;        /* ???????????????????????????? */
    oal_uint32              ul_reg_flag_bitmap; /* ?????????????????????? */
    oal_uint32              aul_reg_num[OAM_REG_BUTT];      /* ?????????????????????????? */
    oam_reg_stru            *past_reg[OAM_REG_BUTT];      /*?????????????????????????????????????????? */

    oal_uint32              ul_rpt_count;      /* ????????????????????????*/

    oam_reg_workqueue_stru  st_wq;
    oal_uint32              ul_sn;              /* ????????????????????????????????*/

    oal_uint32              ul_nb;              /* ????????netbuf???????????????? */

    oal_uint8               *puc_send_buff;     /* ???????????? */
}oam_reg_manage_stru;

typedef struct
{
    oal_uint32                      ul_addr;
    oal_uint32                      ul_value;
}oam_reg_rpt_data;

typedef struct
{
    oal_uint32                      ul_timestamp;
    oam_reg_evt_enum_uint32         en_evt;
}oam_reg_rpt_head;

typedef struct
{
    oal_uint16      us_flag; /* 0/1/2 ????/????/???? */
    oal_uint16      us_sn;
    union{
            oam_reg_rpt_head st_rpt_head;
            oam_reg_rpt_data st_rpt_data;
    }un_rpt;
}oam_reg_rpt;

/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/
#define OAM_REG_MAX_PKT_ONE_BUFF        ((OAM_REG_MAX_SEND_BUF_SIZE - sizeof(oam_reg_send_head_stru)) / (sizeof(oam_reg_rpt)))

/*****************************************************************************
  4 ????????????
*****************************************************************************/
extern oam_reg_manage_stru g_st_oam_reg_mng_etc;
/*****************************************************************************
  10 ????????
*****************************************************************************/
oal_void oam_reg_init_etc(oal_void);
oal_void oam_reg_set_flag_etc(oam_reg_type_enum_uint8 en_type, oam_reg_subtype_enum_uint32 en_subtype, oal_uint8 uc_flag);
oal_void oam_reg_set_evt_etc(oam_reg_evt_enum_uint32 ul_evt, oal_uint32 ul_tick);
oal_uint8 oam_reg_is_need_refresh_etc(oam_reg_evt_enum_uint32 en_evt_type);
oal_uint32 oam_reg_get_evt_name_etc(oam_reg_evt_enum_uint32 en_evt_type, oal_uint8 *puc_evt_name);
oal_void oam_reg_report_etc(oal_void);
oal_void oam_reg_exit_etc(oal_void);
oal_void  oam_reg_info_etc(oal_void);
oal_void oam_reg_set_flag_addr_etc(oam_reg_type_enum_uint8 en_type, oal_uint32 ul_startaddr, oal_uint32 ul_endaddr, oal_uint8 uc_flag);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* #ifdef _PRE_WLAN_DFT_REG */
#endif /* #ifndef __OAM_REGISTER_H__ */


