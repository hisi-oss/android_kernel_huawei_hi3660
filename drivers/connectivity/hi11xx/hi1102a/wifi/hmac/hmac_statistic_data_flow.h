

#ifndef __MAC_STATISTIC_DATA_FLOW_H__
#define __MAC_STATISTIC_DATA_FLOW_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "hmac_main.h"
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#include "hisi_customize_wifi.h"
#endif
/*****************************************************************************
  2 ??????
*****************************************************************************/
#define WLAN_STATIS_DATA_TIMER_PERIOD    (100)          /*??????100ms????*/
#define WLAN_THROUGHPUT_STA_PERIOD        (20)
#define WLAN_THROUGHPUT_LOAD_LOW          (10)           /* ??????10M */
/* WIFI?????????????????????????????????? */
#define WLAN_IRQ_AFFINITY_IDLE_CPU   0
#define WLAN_IRQ_AFFINITY_BUSY_CPU   4

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
typedef struct {
    oal_uint8               uc_timer_cycles; /* ???????????? */
    oal_uint8               uc_req_irq_cpu;  /* ???????????? */
    oal_uint8               uc_txop_limit_en;/* ????????txop */
    oal_uint8               uc_res;
    oal_uint32              ul_tx_pkts;
    oal_uint32              ul_rx_pkts;
    oal_uint32              ul_tx_bytes;  /* WIFI ?????????????? */
    oal_uint32              ul_rx_bytes;   /* WIFI ?????????????? */
    oal_uint32              ul_pre_time; /*??????????????*/
    oal_uint32              ul_total_sdio_pps; /*????????*/
    oal_uint32              ul_tx_pps;
    oal_uint32              ul_rx_pps;
    frw_timeout_stru        st_statis_data_timer;
}wifi_txrx_pkt_statis_stru;

/* ????wifi???????? */
typedef struct
{
    oal_bool_enum_uint8         en_wifi_rx_busy;
    oal_bool_enum_uint8         en_wifi_tx_busy;
    oal_uint8                   uc_res[2];
}statis_wifi_load_stru;
extern statis_wifi_load_stru g_st_wifi_load;

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ

enum
{
    /* frequency lock disable mode */
    H2D_FREQ_MODE_DISABLE                 = 0,
    /* frequency lock enable mode */
    H2D_FREQ_MODE_ENABLE                  = 1,
};
typedef oal_uint8 oal_freq_mode_enum_uint8;

typedef enum
{
    CMD_SET_DEVICE_FREQ_ENDABLE, //cmd type 0
    CMD_SET_DEVICE_FREQ_VALUE,
    CMD_SET_AUTO_BYPASS_DEVICE_AUTO_FREQ,
    CMD_GET_DEVICE_AUTO_FREQ,
    CMD_AUTO_FREQ_BUTT,
}oal_h2d_freq_cmd_enum;
typedef oal_uint8 oal_h2d_freq_cmd_enum_uint8;

typedef struct {
    oal_uint8  uc_device_type;   /*device????????*/
    oal_uint8  uc_reserve[3];   /*????????*/
} device_speed_freq_level_stru;
typedef struct {
    oal_uint32  ul_speed_level;    /*??????????*/
    oal_uint32  ul_min_cpu_freq;  /*CPU????????*/
    oal_uint32  ul_min_ddr_freq;   /*DDR????????*/
} host_speed_freq_level_stru;
typedef struct {
    oal_bool_enum_uint8  en_irq_bindcpu;
    oal_uint8            uc_cpumask;
    oal_uint16           us_tx_throughput_irq_high;
    oal_uint16           us_tx_throughput_irq_low;
    oal_uint16           us_rx_throughput_irq_high;
    oal_uint16           us_rx_throughput_irq_low;
} thread_bindcpu_stru;

extern host_speed_freq_level_stru g_host_speed_freq_level[];
extern device_speed_freq_level_stru g_device_speed_freq_level[];
extern thread_bindcpu_stru g_st_thread_bindcpu;

#endif
/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/
extern oal_void                 hmac_wifi_statistic_rx_packets(oal_uint32 ul_pkt_count);
extern oal_void                 hmac_wifi_statistic_tx_packets(oal_uint32 ul_pkt_count);
extern oal_void                 hmac_wifi_statistic_rx_bytes(oal_uint32 ul_pkt_bytes);
extern oal_void                 hmac_wifi_statistic_tx_bytes(oal_uint32 ul_pkt_bytes);
extern oal_bool_enum_uint8      hmac_wifi_rx_is_busy(oal_void);
extern oal_void                 hmac_wifi_calculate_throughput(oal_void);
extern oal_void                 hmac_wifi_statis_data_timeout(oal_void);
extern oal_void                 hmac_wifi_statis_data_timer_init(oal_void);
extern oal_void                 hmac_wifi_statis_data_timer_deinit(oal_void);
extern oal_void                 hmac_wifi_pm_state_notify(oal_bool_enum_uint8 en_wake_up);
extern oal_void                 hmac_wifi_state_notify(oal_bool_enum_uint8 en_wifi_on);

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif




