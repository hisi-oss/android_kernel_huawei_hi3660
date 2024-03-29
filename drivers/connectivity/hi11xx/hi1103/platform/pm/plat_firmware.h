

#ifndef __PLAT_FIRMWARE_H__
#define __PLAT_FIRMWARE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "plat_type.h"
#include "oal_net.h"
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include "plat_exception_rst.h"
#endif
/*****************************************************************************
  2 ??????
*****************************************************************************/

/* string */
#define OS_MEM_SET(dst, data, size)         memset(dst, data, size)
#define OS_MEM_CPY(dst, src, size)          memcpy(dst, src, size)
#define OS_MEM_CMP(dst, src, size)          memcmp(dst, src, size)
#define OS_STR_CMP(dst, src)                strcmp(dst, src)
#define OS_STR_LEN(s)                       strlen(s)
#define OS_STR_CHR(str, chr)                strchr(str, chr)
#define OS_STR_STR(dst, src)                strstr(dst, src)

/* memory */
#define OS_MEM_KFREE(p)                     kfree(p)
#define OS_KMALLOC_GFP(size)                kmalloc(size, (GFP_KERNEL | __GFP_NOWARN))
#define OS_KZALLOC_GFP(size)                kzalloc(size, (GFP_KERNEL | __GFP_NOWARN))
#define OS_VMALLOC_GFP(size)                vmalloc(size)
#define OS_MEM_VFREE(p)                     vfree(p)

#define READ_MEG_TIMEOUT            (2000)      /* 200ms */
#define READ_MEG_JUMP_TIMEOUT       (15000)   /* 15s */

#define FILE_CMD_WAIT_TIME_MIN      (5000)     /* 5000us */
#define FILE_CMD_WAIT_TIME_MAX      (5100)     /* 5100us */

#define SEND_BUF_LEN                (520)
#define RECV_BUF_LEN                (512)
#define VERSION_LEN                 (64)

#define READ_CFG_BUF_LEN            (2048)

#define DOWNLOAD_CMD_LEN            (32)
#define DOWNLOAD_CMD_PARA_LEN       (800)

#define HOST_DEV_TIMEOUT            (3)
#define INT32_STR_LEN               (32)

#define SHUTDOWN_TX_CMD_LEN         (64)

#define CMD_JUMP_EXEC_RESULT_SUCC   (0)
#define CMD_JUMP_EXEC_RESULT_FAIL   (1)

#define WIFI_MODE_DISABLE           (0)
#define WIFI_MODE_2G                (1)
#define WIFI_MODE_5G                (2)
#define WIFI_MODE_2G_5G             (3)

#define SOFT_WCPU_EN_ADDR           "0x50000c00"
#define SOFT_BCPU_EN_ADDR           "0x50000c04"
#define BCPU_DE_RESET_ADDR          "0x50000094"

/*??????????device????????????*/
#define VER_CMD_KEYWORD             "VERSION"
#define JUMP_CMD_KEYWORD            "JUMP"
#define FILES_CMD_KEYWORD           "FILES"
#define SETPM_CMD_KEYWORD           "SETPM"
#define SETBUCK_CMD_KEYWORD         "SETBUCK"
#define SETSYSLDO_CMD_KEYWORD       "SETSYSLDO"
#define SETNFCRETLDO_CMD_KEYWORD    "SETNFCRETLDO"
#define SETPD_CMD_KEYWORD           "SETPD"
#define SETNFCCRG_CMD_KEYWORD       "SETNFCCRG"
#define SETABB_CMD_KEYWORD          "SETABB"
#define SETTCXODIV_CMD_KEYWORD      "SETTCXODIV"
#define RMEM_CMD_KEYWORD            "READM"
#define WMEM_CMD_KEYWORD            "WRITEM"
#define QUIT_CMD_KEYWORD            "QUIT"

/*??????????????????device????????????????????????????????cfg??????*/
#define SLEEP_CMD_KEYWORD           "SLEEP"
#define CALI_COUNT_CMD_KEYWORD      "CALI_COUNT"
#define CALI_BFGX_DATA_CMD_KEYWORD  "CALI_BFGX_DATA"
#define SHUTDOWN_WIFI_CMD_KEYWORD   "SHUTDOWN_WIFI"
#define SHUTDOWN_BFGX_CMD_KEYWORD   "SHUTDOWN_BFGX"

/*??????device????????????????????????????host????????????????????????????*/
#define MSG_FROM_DEV_WRITEM_OK      "WRITEM OK"
#define MSG_FROM_DEV_READM_OK       ""
#define MSG_FROM_DEV_FILES_OK       "FILES OK"
#define MSG_FROM_DEV_READY_OK       "READY"
#define MSG_FROM_DEV_JUMP_OK        "JUMP OK"
#define MSG_FROM_DEV_SET_OK         "SET OK"
#define MSG_FROM_DEV_QUIT_OK        ""

/*??????cfg????????????????????????????????cfg??????????:??????+??????????(QUIT????????)*/
#define FILE_TYPE_CMD_KEY           "ADDR_FILE_"
#define NUM_TYPE_CMD_KEY            "PARA_"

#define COMPART_KEYWORD             ' '
#define CMD_LINE_SIGN               ';'

#define CFG_INFO_RESERVE_LEN        (8)

#define HI1103_ASIC_MPW2               (0)
#define HI1103_ASIC_PILOT              (1)

#define BFGX_AND_WIFI_CFG_PATH                    "/vendor/firmware/bfgx_and_wifi_cfg"
#define WIFI_CFG_PATH                             "/vendor/firmware/wifi_cfg"
#define BFGX_CFG_PATH                             "/vendor/firmware/bfgx_cfg"
#define RAM_CHECK_CFG_PATH                        "/vendor/firmware/ram_reg_test_cfg"

#define BFGX_AND_WIFI_CFG_HI1103_MPW2_PATH        "/vendor/firmware/hi1103/mpw2/bfgx_and_wifi_cfg"
#define WIFI_CFG_HI1103_MPW2_PATH                 "/vendor/firmware/hi1103/mpw2/wifi_cfg"
#define BFGX_CFG_HI1103_MPW2_PATH                 "/vendor/firmware/hi1103/mpw2/bfgx_cfg"
#define RAM_CHECK_CFG_HI1103_MPW2_PATH            "/vendor/firmware/hi1103/mpw2/ram_reg_test_cfg"

#define BFGX_AND_WIFI_CFG_HI1103_PILOT_PATH       "/vendor/firmware/hi1103/pilot/bfgx_and_wifi_cfg"
#define WIFI_CFG_HI1103_PILOT_PATH                "/vendor/firmware/hi1103/pilot/wifi_cfg"
#define BFGX_CFG_HI1103_PILOT_PATH                "/vendor/firmware/hi1103/pilot/bfgx_cfg"
#define RAM_CHECK_CFG_HI1103_PILOT_PATH           "/vendor/firmware/hi1103/pilot/ram_reg_test_cfg"
#define RAM_BCPU_CHECK_CFG_HI1103_PILOT_PATH      "/vendor/firmware/hi1103/pilot/reg_bcpu_mem_test_cfg"

#define HI1103_MPW2_BOOTLOADER_VERSION            "Hi1103V100R001C01B060 Feb 10 2017"
#define HI1103_PILOT_BOOTLOADER_VERSION           "Hi1103V100R001C01B083 Dec 16 2017"

#define FILE_COUNT_PER_SEND           (1)
#define MIN_FIRMWARE_FILE_TX_BUF_LEN  (4096)
#define MAX_FIRMWARE_FILE_TX_BUF_LEN  (512*1024)

/*****************************************************************************
  3 ????????
*****************************************************************************/
enum return_type
{
    SUCC = 0,
    EFAIL,
};

enum FIRMWARE_CFG_CMD_ENUM
{
    ERROR_TYPE_CMD = 0,            /* ?????????? */
    FILE_TYPE_CMD,                 /* ?????????????? */
    NUM_TYPE_CMD,                  /* ?????????????????? */
    QUIT_TYPE_CMD,                 /* ???????? */
    SHUTDOWN_WIFI_TYPE_CMD,        /* SHUTDOWN WCPU???? */
    SHUTDOWN_BFGX_TYPE_CMD         /* SHUTDOWN BCPU???? */
};

/*
*1.????????????????BFGN_AND_WIFI_CFG????????????????????host????????????????????device????
*2.deivce????????????wifi??????BFGN_AND_WIFI_CFG
*3.deivce????????????bt??????BFGX_CFG
*4.bt??????????wifi??????WIFI_CFG
*5.wifi??????????bt??????sdio??????BCPU
*/
enum FIRMWARE_CFG_FILE_ENUM
{
    BFGX_AND_WIFI_CFG = 0,         /*????BFGIN??wifi fimware??????????index??????????????*/
    WIFI_CFG,                      /*??????wifi firmware????????????????????????????*/
    BFGX_CFG,                      /*??????bfgx firmware??????????????????????????????*/
    RAM_REG_TEST_CFG,              /*????????mem reg????????*/

    CFG_FILE_TOTAL
};

enum FIRMWARE_SUBSYS_ENUM
{
    DEV_WCPU = 0,
    DEV_BCPU,
    DEV_CPU_BUTT,
};

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
typedef struct cmd_type_st
{
    int32       cmd_type;
    uint8       cmd_name[DOWNLOAD_CMD_LEN];
    uint8       cmd_para[DOWNLOAD_CMD_PARA_LEN];

}CMD_TYPE_STRUCT;

typedef struct firmware_globals_st
{
    int32            al_count[CFG_FILE_TOTAL];      /*????????cfg????????????????????????*/
    CMD_TYPE_STRUCT *apst_cmd[CFG_FILE_TOTAL];      /*????????cfg??????????????*/
    uint8            auc_CfgVersion[VERSION_LEN];   /*????cfg??????????????????????*/
    uint8            auc_DevVersion[VERSION_LEN];   /*??????????device??????????????????*/
}FIRMWARE_GLOBALS_STRUCT;

/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/
typedef struct file OS_KERNEL_FILE_STRU;

/*****************************************************************************
  10 ????????
*****************************************************************************/
extern void set_hi1103_asic_type(uint32 ul_asic_type);
extern uint32 get_hi1103_asic_type(void);
extern int32 firmware_download_etc(uint32 ul_index);
extern int32 firmware_cfg_init_etc(void);
extern int32 firmware_get_cfg_etc(uint8 *puc_CfgPatch, uint32 ul_index);
extern int32 firmware_cfg_clear_etc(void);
extern int32 wifi_device_mem_dump(struct st_wifi_dump_mem_info *pst_mem_dump_info, uint32 count);
extern void save_nfc_lowpower_log_2_sdt_etc(void);
extern int32 read_device_reg16(uint32 address, int16* value);
extern int32 write_device_reg16(uint32 address, int16 value);
extern int32 is_device_mem_test_succ(void);
extern int32 get_device_ram_test_result(int32 is_wcpu, uint32* cost);
extern uint8 **g_auc_cfg_path_etc;
extern uint8 *g_auc_pilot_cfg_patch_in_vendor[CFG_FILE_TOTAL];
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of plat_firmware.h */
