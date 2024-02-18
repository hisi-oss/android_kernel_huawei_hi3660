


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
  1 ??????????
*****************************************************************************/
/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "oal_net.h"
#include "oal_types.h"
#include "oam_ext_if.h"
#include  "mac_vap.h"
#include  "mac_resource.h"
#include  "hmac_vap.h"
#include  "hmac_auto_adjust_freq.h"
#include  "hmac_ext_if.h"
#include  "hmac_blockack.h"
#include "hmac_tx_data.h"

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include "plat_pm_wlan.h"
#include <linux/pm_qos.h>
#endif


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_AUTO_ADJUST_FREQ_C

#ifdef _PRE_WLAN_FEATURE_NEGTIVE_DET
#define INVALID_PKMODE_TH  (0xFFFFFFFF)
#endif
/*****************************************************************************
  2 ????????????
*****************************************************************************/
#ifdef WIN32
oal_uint32 jiffies;
#endif

freq_lock_control_stru g_freq_lock_control_etc = {0};
wifi_txrx_pkt_stat g_st_wifi_rxtx_total = {0};
/* Wi-Fi?????????????????????? */
freq_wifi_load_stru g_st_wifi_load = {0};

#ifdef _PRE_WLAN_FEATURE_NEGTIVE_DET
oal_bool_enum_uint8 g_en_pk_mode_swtich = OAL_TRUE;

/* pk mode?????????????????????????? */
/*
PK????????????:
{(????Mbps)  20M     40M    80M   160M   80+80M
lagency:    {valid, valid, valid, valid, valid},   (????????????????pk mode )
HT:         {62, 123, valid, valid, valid},
VHT:        {77, 167, 329, 660, 660},
HE:         {valid, valid, valid, valid, valid},   (????????11ax??pk mode)
};


PK????????????:
??????????: g_st_pk_mode_high_th_table = PK???????????? * 70% *1024 *1024 /8  (????????)
??????????: g_st_pk_mode_low_th_table  = PK???????????? * 30% *1024 *1024 /8  (????????)

*/
#if 1
oal_uint32 g_st_pk_mode_high_th_table[WLAN_PROTOCOL_CAP_BUTT][WLAN_BW_CAP_BUTT] = {
    {INVALID_PKMODE_TH, INVALID_PKMODE_TH, INVALID_PKMODE_TH, INVALID_PKMODE_TH, INVALID_PKMODE_TH},
    {45,                        110,        INVALID_PKMODE_TH, INVALID_PKMODE_TH, INVALID_PKMODE_TH},
    {60,                        130,               280,               562,               562},
#ifdef _PRE_WLAN_FEATURE_11AX
    {INVALID_PKMODE_TH, INVALID_PKMODE_TH, INVALID_PKMODE_TH, INVALID_PKMODE_TH, INVALID_PKMODE_TH},
#endif /* #ifdef _PRE_WLAN_FEATURE_11AX */

};

oal_uint32 g_st_pk_mode_low_th_table[WLAN_PROTOCOL_CAP_BUTT][WLAN_BW_CAP_BUTT] = {
    {INVALID_PKMODE_TH, INVALID_PKMODE_TH, INVALID_PKMODE_TH, INVALID_PKMODE_TH, INVALID_PKMODE_TH},
    {30,                        80,        INVALID_PKMODE_TH, INVALID_PKMODE_TH, INVALID_PKMODE_TH},
    {40,                        100,                 240,              400,               400},
#ifdef _PRE_WLAN_FEATURE_11AX
    {INVALID_PKMODE_TH, INVALID_PKMODE_TH, INVALID_PKMODE_TH, INVALID_PKMODE_TH, INVALID_PKMODE_TH},
#endif /* #ifdef _PRE_WLAN_FEATURE_11AX */

};
#endif

#endif

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
oal_uint32 g_ul_orig_cpu_min_freq       = 0;
oal_uint32 g_ul_orig_cpu_max_freq       = 0;
oal_uint32 g_ul_orig_ddr_min_freq       = 0;
oal_uint32 g_ul_orig_ddr_max_freq       = 0;

#ifndef WIN32
/*??????????????????*/
host_speed_freq_level_stru g_host_speed_freq_level_etc[4] = {
    /*pps????                   CPU????????                     DDR????????*/
    {PPS_VALUE_0,          CPU_MIN_FREQ_VALUE_0,            DDR_MIN_FREQ_VALUE_0},
    {PPS_VALUE_1,          CPU_MIN_FREQ_VALUE_1,            DDR_MIN_FREQ_VALUE_1},
    {PPS_VALUE_2,          CPU_MIN_FREQ_VALUE_2,            DDR_MIN_FREQ_VALUE_2},
    {PPS_VALUE_3,          CPU_MIN_FREQ_VALUE_3,            DDR_MIN_FREQ_VALUE_3},
};
host_speed_freq_level_stru g_host_no_ba_freq_level_etc[4] = {
    /*pps????                        CPU????????                      DDR????????*/
    {NO_BA_PPS_VALUE_0,          CPU_MIN_FREQ_VALUE_0,            DDR_MIN_FREQ_VALUE_0},
    {NO_BA_PPS_VALUE_1,          CPU_MIN_FREQ_VALUE_1,            DDR_MIN_FREQ_VALUE_1},
    {NO_BA_PPS_VALUE_2,          CPU_MIN_FREQ_VALUE_2,            DDR_MIN_FREQ_VALUE_2},
    {NO_BA_PPS_VALUE_3,          CPU_MIN_FREQ_VALUE_2,            DDR_MIN_FREQ_VALUE_2},
};
device_speed_freq_level_stru g_device_speed_freq_level_etc[] = {
    /*device????????*/
    {FREQ_IDLE},
    {FREQ_MIDIUM},
    {FREQ_HIGHER},
    {FREQ_HIGHEST},
};

struct pm_qos_request *g_pst_wifi_auto_ddr_etc = NULL;

#else
host_speed_freq_level_stru g_host_speed_freq_level_etc[] = {
    /*pps????                   CPU????????                     DDR????????*/
    {PPS_VALUE_0,          CPU_MIN_FREQ_VALUE_0,            DDR_MIN_FREQ_VALUE_0},
    {PPS_VALUE_1,          CPU_MIN_FREQ_VALUE_1,            DDR_MIN_FREQ_VALUE_1},
    {PPS_VALUE_2,          CPU_MIN_FREQ_VALUE_2,            DDR_MIN_FREQ_VALUE_2},
    {PPS_VALUE_3,          CPU_MIN_FREQ_VALUE_3,            DDR_MIN_FREQ_VALUE_3},
};
device_speed_freq_level_stru g_device_speed_freq_level_etc[] = {
    /*device????????*/
    {FREQ_IDLE},
    {FREQ_MIDIUM},
    {FREQ_HIGHEST},
    {FREQ_HIGHEST},
};

#define mutex_init(mux)
#define mutex_lock(mux)
#define mutex_unlock(mux)
#define spin_lock_init(mux)
#define mutex_destroy(mux)
#define spin_unlock_bh(mux)
#endif

extern hmac_rxdata_thread_stru     g_st_rxdata_thread_etc;

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)

OAL_STATIC oal_bool_enum_uint8 hmac_get_cpu_freq_raw(oal_uint8 uc_freq_type, oal_uint32 * pst_ul_freq_value)
{
#if 0
    struct file* filp = NULL;
    mm_segment_t old_fs;
    oal_int8 buf[12] = {0};

    if (uc_freq_type == SCALING_MAX_FREQ)
        filp = filp_open(CPU_MAX_FREQ, O_RDONLY, 0);
    else if (uc_freq_type == SCALING_MIN_FREQ)
        filp = filp_open(CPU_MIN_FREQ, O_RDONLY, 0);
    else
        return -1;

    if (OAL_IS_ERR_OR_NULL(filp))
    {
        OAM_ERROR_LOG1(0,OAM_SF_ANY,"{hmac_get_cpu_freq_raw:??freq??= %d error !}",uc_freq_type);
        return -1;
    }
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    filp->f_pos = 0;
    filp->f_op->read(filp, buf, 12, &filp->f_pos);
    filp_close(filp, NULL);
    set_fs(old_fs);

    if (kstrtouint(buf, 10, pst_ul_freq_value) != 0)
    {
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"{error to get cpu freq !}");
        return -1;
    }
#endif
    return 0;
}


oal_bool_enum_uint8 hmac_set_cpu_freq_raw_etc(oal_uint8 uc_freq_type, oal_uint32 ul_freq_value)
{
#if 0
    struct file* filp = NULL;
    mm_segment_t old_fs;
    oal_int8 buf[12] = {0};

    OAL_SPRINTF(buf, 12, "%d", ul_freq_value);

    if (uc_freq_type == SCALING_MIN_FREQ)
        filp = filp_open(CPU_MIN_FREQ, O_RDWR, 0);
    else if (uc_freq_type == SCALING_MAX_FREQ)
        filp = filp_open(CPU_MAX_FREQ, O_RDWR, 0);
    else
        return -1;

    if (OAL_IS_ERR_OR_NULL(filp))
    {
        OAM_WARNING_LOG2(0,OAM_SF_ANY,"{hmac_set_cpu_freq_raw_etc:?ffreq type[%d]?freq??= %d error !}",uc_freq_type, ul_freq_value);
        return -1;
    }
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    filp->f_pos = 0;
    filp->f_op->write(filp, buf, 12, &filp->f_pos);
    filp_close(filp, NULL);
    set_fs(old_fs);
#endif
    return 0;
}

#if 0

OAL_STATIC oal_bool_enum_uint8 hmac_get_ddr_freq_raw(oal_uint8 uc_freq_type, oal_uint32 * pst_ul_freq_value)
{
    struct file* filp = NULL;
    mm_segment_t old_fs;
    oal_int8 buf[12] = {0};

    if (uc_freq_type == SCALING_MAX_FREQ)
        filp = filp_open(DDR_MAX_FREQ, O_RDONLY, 0);
    else if (uc_freq_type == SCALING_MIN_FREQ)
        filp = filp_open(DDR_MIN_FREQ, O_RDONLY, 0);
    else
        return -1;

    if (OAL_IS_ERR_OR_NULL(filp))
    {
        OAM_ERROR_LOG1(0,OAM_SF_ANY,"{hmac_get_ddr_freq_raw:??freq??= %d error !}",uc_freq_type);
        return -1;
    }
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    filp->f_pos = 0;
    filp->f_op->read(filp, buf, 12, &filp->f_pos);
    filp_close(filp, NULL);
    set_fs(old_fs);

    if (kstrtouint(buf, 10, pst_ul_freq_value) != 0)
    {
        printk("error to get cpu freq\n");
        return -1;
    }
    return 0;
}
#endif



oal_bool_enum_uint8 hmac_set_ddr_freq_raw_etc(oal_uint8 uc_freq_type, oal_uint32 ul_freq_value)
{
#if 0
    pm_qos_update_request(g_pst_wifi_auto_ddr_etc, ul_freq_value);
#endif
    return 0;
}

oal_void hmac_wifi_auto_ddr_init_etc(oal_void)
{
#if 0
    g_pst_wifi_auto_ddr_etc = kmalloc(sizeof(struct pm_qos_request), GFP_KERNEL);
    if (g_pst_wifi_auto_ddr_etc == NULL)
    {
        OAL_IO_PRINT("[AUTODDR]pm_qos_request alloc memory failed.\n");
        return;
    }
    g_pst_wifi_auto_ddr_etc->pm_qos_class = 0;
    pm_qos_add_request(g_pst_wifi_auto_ddr_etc, PM_QOS_MEMORY_THROUGHPUT,
                       PM_QOS_MEMORY_THROUGHPUT_DEFAULT_VALUE);
#endif
    return;
}
oal_void hmac_wifi_auto_ddr_exit_etc(oal_void)
{
#if 0
    pm_qos_remove_request(g_pst_wifi_auto_ddr_etc);
    kfree(g_pst_wifi_auto_ddr_etc);
    g_pst_wifi_auto_ddr_etc = NULL;
#endif
}
#endif


oal_uint8 hmac_set_auto_freq_mod_etc(oal_uint8 uc_freq_enable)
{
    g_freq_lock_control_etc.uc_lock_mod = uc_freq_enable;

    /* ????device???????? */
    if(FREQ_LOCK_ENABLE == uc_freq_enable)
    {
        /* ??????????idle */
        g_freq_lock_control_etc.uc_curr_lock_level = FREQ_IDLE;
        /* ??????????idle */
        g_freq_lock_control_etc.uc_req_lock_level = FREQ_IDLE;
        /* WIFI??????,?????????????? */
        g_freq_lock_control_etc.ul_pre_jiffies = jiffies;
    }
    else
    {
        /* ????WIFI??,??CPU???????????????? */
        mutex_lock(&g_freq_lock_control_etc.st_lock_freq_mtx);
        hmac_set_cpu_freq_raw_etc(SCALING_MIN_FREQ, g_ul_orig_cpu_min_freq);
        hmac_set_cpu_freq_raw_etc(SCALING_MAX_FREQ, g_ul_orig_cpu_max_freq);
        mutex_unlock(&g_freq_lock_control_etc.st_lock_freq_mtx);

        g_freq_lock_control_etc.uc_curr_lock_level = FREQ_BUTT;
        OAM_WARNING_LOG2(0,OAM_SF_ANY,"{hmac_set_auto_freq_mod_etc: freq,min[%d]max[%d]!}",
                       g_ul_orig_cpu_min_freq, g_ul_orig_cpu_max_freq);
    }

    return OAL_SUCC;
}

oal_void hmac_adjust_set_freq(oal_void)
{
    oal_uint8 uc_req_lock_level = g_freq_lock_control_etc.uc_req_lock_level;

    /* ???????????????????????? */
    if (uc_req_lock_level == g_freq_lock_control_etc.uc_curr_lock_level)
    {
        return;
    }

    OAM_WARNING_LOG2(0,OAM_SF_PWR,"{hmac_adjust_set_freq: freq [%d]to[%d]}",g_freq_lock_control_etc.uc_curr_lock_level,uc_req_lock_level);

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    if(hmac_is_device_ba_setup_etc())
    {
        hmac_set_cpu_freq_raw_etc(SCALING_MIN_FREQ,g_host_speed_freq_level_etc[uc_req_lock_level].ul_min_cpu_freq);
        hmac_set_ddr_freq_raw_etc(SCALING_MIN_FREQ,g_host_speed_freq_level_etc[uc_req_lock_level].ul_min_ddr_freq);
    }
    else
    {
        hmac_set_cpu_freq_raw_etc(SCALING_MIN_FREQ,g_host_no_ba_freq_level_etc[uc_req_lock_level].ul_min_cpu_freq);
        hmac_set_ddr_freq_raw_etc(SCALING_MIN_FREQ,g_host_no_ba_freq_level_etc[uc_req_lock_level].ul_min_ddr_freq);
    }
#endif

    g_freq_lock_control_etc.uc_curr_lock_level = uc_req_lock_level;
}

oal_uint8 hmac_get_freq_level_etc(oal_uint32 ul_speed)//??????????????????????????
{
    oal_uint8 level_idx;

    if(hmac_is_device_ba_setup_etc())
    {
        if (ul_speed <= g_host_speed_freq_level_etc[1].ul_speed_level)
        {
            level_idx = 0;
        }
        else if ((ul_speed > g_host_speed_freq_level_etc[1].ul_speed_level)
            && (ul_speed <= g_host_speed_freq_level_etc[2].ul_speed_level))
        {
            level_idx = 1;
        }
        else if ((ul_speed > g_host_speed_freq_level_etc[2].ul_speed_level)
            && (ul_speed <= g_host_speed_freq_level_etc[3].ul_speed_level))
        {
            level_idx = 2;
        }
        else
        {
            level_idx = 3;
        }
    }
    else
    {
        if (ul_speed <= g_host_no_ba_freq_level_etc[1].ul_speed_level)
        {
            level_idx = 0;
        }
        else if ((ul_speed > g_host_no_ba_freq_level_etc[1].ul_speed_level)
            && (ul_speed <= g_host_no_ba_freq_level_etc[2].ul_speed_level))
        {
            level_idx = 1;
        }
        else if ((ul_speed > g_host_no_ba_freq_level_etc[2].ul_speed_level)
            && (ul_speed <= g_host_no_ba_freq_level_etc[3].ul_speed_level))
        {
            level_idx = 2;
        }
        else
        {
            level_idx = 3;
        }
    }
    return level_idx;
}


oal_void hmac_adjust_freq_etc(oal_void)
{
    oal_uint8          uc_req_lock_level = 0; //????????????
    oal_uint32         ul_cur_jiffies;
    oal_uint32         ul_sdio_dur_ms; //????
    oal_uint32         ul_trx_total = 0;
    oal_uint32         ul_tx_total;
    oal_uint32         ul_rx_total;

    if(FREQ_LOCK_DISABLE == g_freq_lock_control_etc.uc_lock_mod)
    {
        return;
    }

    ul_trx_total = g_st_wifi_rxtx_total.ul_rx_pkts + g_st_wifi_rxtx_total.ul_tx_pkts;
    ul_tx_total  = g_st_wifi_rxtx_total.ul_tx_pkts;
    ul_rx_total  = g_st_wifi_rxtx_total.ul_rx_pkts;
    g_st_wifi_rxtx_total.ul_rx_pkts = 0;
    g_st_wifi_rxtx_total.ul_tx_pkts = 0;

    ul_cur_jiffies = jiffies; //jiffies??Linux????????????????????????????????????????????????????????????
    ul_sdio_dur_ms = OAL_JIFFIES_TO_MSECS(ul_cur_jiffies - g_freq_lock_control_etc.ul_pre_jiffies);
    g_freq_lock_control_etc.ul_pre_jiffies = ul_cur_jiffies;

    /* ????????????????????????????????????,??????????PPS?????????? */
    if ((0 == ul_sdio_dur_ms) || (ul_sdio_dur_ms < (WLAN_FREQ_TIMER_PERIOD >> 1)))
    {
        return;
    }

    //????PPS
    g_freq_lock_control_etc.ul_total_sdio_pps = (ul_trx_total*1000)/ul_sdio_dur_ms;
    g_freq_lock_control_etc.ul_tx_pps         = (ul_tx_total*1000)/ul_sdio_dur_ms;
    g_freq_lock_control_etc.ul_rx_pps         = (ul_rx_total*1000)/ul_sdio_dur_ms;

    //OAM_WARNING_LOG4(0,OAM_SF_ANY,"{SDIO perform tx statistic: packet_rate = %lu pps, sumlen = %lu B, [use time] = %lu ms,g_adjust_count = %d!}",
        //g_freq_lock_control_etc.ul_total_sdio_pps , ul_trx_total, ul_sdio_dur_ms,g_freq_lock_control_etc.ul_adjust_count);
    //OAM_WARNING_LOG2(0,OAM_SF_ANY,"{SDIO perform tx statistic: tx pps  = %lu pps, rx pps = %lu pps}",
        //g_freq_lock_control_etc.ul_tx_pps, g_freq_lock_control_etc.ul_rx_pps);

    g_freq_lock_control_etc.uc_req_lock_level = hmac_get_freq_level_etc(g_freq_lock_control_etc.ul_total_sdio_pps);

    uc_req_lock_level = g_freq_lock_control_etc.uc_req_lock_level;
    if (uc_req_lock_level == g_freq_lock_control_etc.uc_curr_lock_level) //??????????????????????????????????
    {
        g_freq_lock_control_etc.ul_adjust_count = 0;
        return;
    }

    mutex_lock(&g_freq_lock_control_etc.st_lock_freq_mtx);

    if(uc_req_lock_level < g_freq_lock_control_etc.uc_curr_lock_level)
    {
        /*????MAX_DEGRADE_FREQ_TIME_THRESHOLD??????????????????*/
        g_freq_lock_control_etc.ul_adjust_count++;

        if(0 != ul_trx_total) //??????????????????
        {
            if(g_freq_lock_control_etc.ul_adjust_count >= MAX_DEGRADE_FREQ_COUNT_THRESHOLD_SUCCESSIVE_10)//??????????100??????????????????????
            {
                g_freq_lock_control_etc.ul_adjust_count = 0;
                /*??????????????????????*/
                hmac_adjust_set_freq();
            }
        }
        else //????????????3??????????????????????
        {
            if(g_freq_lock_control_etc.ul_adjust_count >= MAX_DEGRADE_FREQ_COUNT_THRESHOLD_SUCCESSIVE_3)
            {
                g_freq_lock_control_etc.ul_adjust_count = 0;
                hmac_adjust_set_freq();
            }
        }
    }
    else
    {
           /*????????????????????????????*/
           g_freq_lock_control_etc.ul_adjust_count = 0;
          hmac_adjust_set_freq();
    }

   mutex_unlock(&g_freq_lock_control_etc.st_lock_freq_mtx);
}


oal_void hmac_wifi_auto_freq_ctrl_init_etc(void)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    if(OAL_TRUE != g_freq_lock_control_etc.en_is_inited)
    {
        mutex_init(&g_freq_lock_control_etc.st_lock_freq_mtx);
        mutex_lock(&g_freq_lock_control_etc.st_lock_freq_mtx);

        hmac_get_cpu_freq_raw(SCALING_MIN_FREQ, &g_ul_orig_cpu_min_freq);
        hmac_get_cpu_freq_raw(SCALING_MAX_FREQ, &g_ul_orig_cpu_max_freq);

        hmac_wifi_auto_ddr_init_etc();

        OAM_WARNING_LOG4(0,OAM_SF_ANY,"{hmac_wifi_auto_freq_ctrl_init_etc g_ul_orig_cpu_min_freq = %d,g_ul_orig_cpu_max_freq = %d,g_ul_orig_ddr_max_freq = %d,g_ul_orig_ddr_max_freq = %d}",
            g_ul_orig_cpu_min_freq,g_ul_orig_cpu_max_freq,g_ul_orig_ddr_min_freq,g_ul_orig_ddr_max_freq);

        g_freq_lock_control_etc.en_is_inited = OAL_TRUE;

        mutex_unlock(&g_freq_lock_control_etc.st_lock_freq_mtx);
    }

    //OAL_INIT_WORK(&(g_freq_lock_control_etc.st_work), hmac_del_virtual_inf_worker_etc);

    //hmac_freq_timer_init(); //????????????
#endif
}

oal_void hmac_wifi_auto_freq_ctrl_deinit_etc(void)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    //hmac_freq_timer_deinit();

    mutex_lock(&g_freq_lock_control_etc.st_lock_freq_mtx);

    if (OAL_TRUE == g_freq_lock_control_etc.en_is_inited)
    {
        hmac_wifi_auto_ddr_exit_etc();
    }
    else
    {
        OAM_WARNING_LOG0(0,OAM_SF_ANY,"{hw_wifi_freq_ctrl_destroy freq lock has already been released!}");
    }
    //oal_cancel_work_sync(&(pst_hmac_vap->st_del_virtual_inf_worker));

    mutex_unlock(&g_freq_lock_control_etc.st_lock_freq_mtx);
    mutex_destroy(&g_freq_lock_control_etc.st_lock_freq_mtx);

    g_freq_lock_control_etc.en_is_inited = OAL_FALSE;
#endif
}

oal_void hmac_auto_freq_wifi_rx_stat(oal_uint32 ul_pkt_count)
{
    g_st_wifi_rxtx_total.ul_rx_pkts += ul_pkt_count;
}

oal_void hmac_auto_freq_wifi_tx_stat(oal_uint32 ul_pkt_count)
{
    g_st_wifi_rxtx_total.ul_tx_pkts += ul_pkt_count;
}
#endif

oal_void hmac_auto_freq_wifi_rx_bytes_stat(oal_uint32 ul_pkt_bytes)
{
    g_st_wifi_rxtx_total.ul_rx_bytes += ul_pkt_bytes;
}

oal_void hmac_auto_freq_wifi_tx_bytes_stat(oal_uint32 ul_pkt_bytes)
{
    g_st_wifi_rxtx_total.ul_tx_bytes += ul_pkt_bytes;
}

oal_bool_enum_uint8 hmac_wifi_rx_is_busy(oal_void)
{
    return g_st_wifi_load.en_wifi_rx_busy;
}

oal_void hmac_adjust_set_irq(oal_uint8 uc_cpu_id)
{
    if (uc_cpu_id == g_freq_lock_control_etc.uc_cur_irq_cpu)
    {
        return;
    }

    g_freq_lock_control_etc.uc_cur_irq_cpu = uc_cpu_id;

    //OAM_WARNING_LOG1(0,OAM_SF_PWR,"{hmac_adjust_set_irq: irq to cpu[%d]}",uc_cpu_id);
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    hi110x_hcc_dev_bindcpu(uc_cpu_id >= WLAN_IRQ_AFFINITY_BUSY_CPU ? 1 : 0);

#if defined(CONFIG_ARCH_HISI)
#ifdef CONFIG_NR_CPUS
#if CONFIG_NR_CPUS > OAL_BUS_HPCPU_NUM
    if( g_st_rxdata_thread_etc.pst_rxdata_thread)
    {
        struct cpumask fast_cpus;
        if(uc_cpu_id >= WLAN_IRQ_AFFINITY_BUSY_CPU)
        {
            hisi_get_fast_cpus(&fast_cpus);
            cpumask_clear_cpu(OAL_BUS_HPCPU_NUM, &fast_cpus);
            //cpumask_clear_cpu(OAL_BUS_HPCPU_NUM_1, &fast_cpus);
            set_cpus_allowed_ptr( g_st_rxdata_thread_etc.pst_rxdata_thread , &fast_cpus);
        }
        else
        {
            set_cpus_allowed_ptr( g_st_rxdata_thread_etc.pst_rxdata_thread , cpumask_of(1));
        }
        g_st_rxdata_thread_etc.uc_allowed_cpus = uc_cpu_id;
    }
#endif
#endif
#endif

#endif
}

#ifdef _PRE_WLAN_FEATURE_NEGTIVE_DET

oal_void hmac_update_pk_mode_info(oal_uint8 *puc_vap_id)
{
    oal_uint8            uc_vap_id;
    mac_vap_stru        *pst_mac_vap;
    mac_user_stru       *pst_mac_user;
    oal_dlist_head_stru *pst_entry;
    oal_dlist_head_stru *pst_dlist_tmp;

    g_st_wifi_pk_mode_status.en_curr_bw_cap = WLAN_BW_CAP_BUTT;
    g_st_wifi_pk_mode_status.en_curr_protocol_cap       = WLAN_PROTOCOL_CAP_BUTT;
    g_st_wifi_pk_mode_status.en_curr_num_spatial_stream = WLAN_SINGLE_NSS;

    for (uc_vap_id = 0; uc_vap_id < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; uc_vap_id++)
    {
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(uc_vap_id);
        if (OAL_PTR_NULL == pst_mac_vap)
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_update_pk_mode_info::pst_mac_vap(%d) is null.}", uc_vap_id);
            continue;
        }

        if (!IS_LEGACY_STA(pst_mac_vap))
        {
            continue;
        }

        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_mac_vap->st_mac_user_list_head))
        {
            pst_mac_user      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
            if (OAL_PTR_NULL == pst_mac_user)
            {
                OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_update_pk_mode_info::pst_user_tmp null.}");
                continue;
            }

            /* ???????????????????????????????????? */
            /* TBD ????????????????????????LEGACY_STA??LEGACY_STA?????????????????????????????????????????? */
            g_st_wifi_pk_mode_status.en_curr_bw_cap             = pst_mac_user->en_bandwidth_cap;
            g_st_wifi_pk_mode_status.en_curr_num_spatial_stream = pst_mac_user->en_avail_num_spatial_stream;

            switch(pst_mac_user->en_protocol_mode)
            {
                case WLAN_LEGACY_11A_MODE:
                case WLAN_LEGACY_11B_MODE:
                case WLAN_LEGACY_11G_MODE:
                case WLAN_MIXED_ONE_11G_MODE:
                case WLAN_MIXED_TWO_11G_MODE:
                    g_st_wifi_pk_mode_status.en_curr_protocol_cap  = WLAN_PROTOCOL_CAP_LEGACY;
                    break;
                case WLAN_HT_MODE:
                case WLAN_HT_ONLY_MODE:
                case WLAN_HT_11G_MODE:
                    g_st_wifi_pk_mode_status.en_curr_protocol_cap  = WLAN_PROTOCOL_CAP_HT;
                    break;
                case WLAN_VHT_MODE:
                case WLAN_VHT_ONLY_MODE:
                    g_st_wifi_pk_mode_status.en_curr_protocol_cap  = WLAN_PROTOCOL_CAP_VHT;
                    break;
#ifdef _PRE_WLAN_FEATURE_11AX
                case WLAN_HE_MODE:
                    g_st_wifi_pk_mode_status.en_curr_protocol_cap  = WLAN_PROTOCOL_CAP_HE;
                    break;
#endif
                case WLAN_PROTOCOL_BUTT:
                default:
                     g_st_wifi_pk_mode_status.en_curr_protocol_cap  = WLAN_PROTOCOL_CAP_BUTT;
                     break;
            }

            *puc_vap_id = uc_vap_id;
        }

    }

    return;
}


oal_void hmac_update_pk_mode(oal_uint32 ul_tx_throughput,
                                        oal_uint32 ul_rx_throughput,
                                        oal_uint32 ul_dur_time)
{
    oal_bool_enum_uint8          en_curr_pk_mode = OAL_FALSE;
    oal_uint8                    uc_vap_id;
    mac_cfg_pk_mode_stru         st_pk_mode_info;
    mac_vap_stru                *pst_mac_vap = OAL_PTR_NULL;
    oal_uint32                   ul_ret;
    oal_uint32                   ul_txrx_throughput;
    oal_uint32                   ul_pk_mode_th;
    mac_device_stru             *pst_mac_device;

    if (OAL_FALSE == g_en_pk_mode_swtich)
    {
        return;
    }
    /* ????????????ul_dur_time??????????????????????????return????????????PK MODE */
#if 0
    /* ul_dur_time????????????????????????pk mode?????? */
    if (ul_dur_time < (WLAN_FREQ_TIMER_PERIOD * WLAN_THROUGHPUT_STA_PERIOD))
    {
        return;
    }
#endif
    pst_mac_device = mac_res_get_dev_etc(0);
    /* ????????VAP,???????????????? */
    if (1 != mac_device_calc_up_vap_num_etc(pst_mac_device))
    {
        return;
    }

    /* ?????????????? */
    hmac_update_pk_mode_info(&uc_vap_id);

    /* ?????????????????????????? */
    if ((WLAN_BW_CAP_BUTT  == g_st_wifi_pk_mode_status.en_curr_bw_cap)||
    (WLAN_PROTOCOL_CAP_BUTT == g_st_wifi_pk_mode_status.en_curr_protocol_cap))
    {
        return;
    }

    /* ??????????: rxtx???????? / ??????????????(????s) */
    ul_txrx_throughput = ul_tx_throughput + ul_rx_throughput;

    /* ??????????????pk mode???? */
    if (OAL_TRUE == g_st_wifi_pk_mode_status.en_is_pk_mode)
    {
        ul_pk_mode_th = (g_st_pk_mode_low_th_table[g_st_wifi_pk_mode_status.en_curr_protocol_cap][g_st_wifi_pk_mode_status.en_curr_bw_cap]) * (1 + g_st_wifi_pk_mode_status.en_curr_num_spatial_stream);
        en_curr_pk_mode = (ul_txrx_throughput < ul_pk_mode_th) ? OAL_FALSE : OAL_TRUE;
    }
    else
    {
        ul_pk_mode_th = (g_st_pk_mode_high_th_table[g_st_wifi_pk_mode_status.en_curr_protocol_cap][g_st_wifi_pk_mode_status.en_curr_bw_cap]) * (1 + g_st_wifi_pk_mode_status.en_curr_num_spatial_stream);
        en_curr_pk_mode = (ul_txrx_throughput > ul_pk_mode_th) ? OAL_TRUE : OAL_FALSE;
    }
    /* dmac????????????????????????????pk mode */
    if((OAL_TRUE == en_curr_pk_mode) && (ul_rx_throughput < ul_tx_throughput))
    {
        en_curr_pk_mode = OAL_FALSE;
    }
    /* PK mode?????????????????????? */
    if (en_curr_pk_mode == g_st_wifi_pk_mode_status.en_is_pk_mode)
    {
        return;
    }

    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(uc_vap_id);
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_update_pk_mode::pst_mac_vap(%d) is null.}", uc_vap_id);
        return;
    }
    if ((WLAN_VHT_MODE != pst_mac_vap->en_protocol) &&
        (WLAN_VHT_ONLY_MODE != pst_mac_vap->en_protocol)
#ifdef _PRE_WLAN_FEATURE_11AX
         &&(WLAN_HE_MODE != pst_mac_vap->en_protocol)
#endif
        )
    {
        return;
    }
    OAM_WARNING_LOG4(0,OAM_SF_ANY,"{hmac_update_pk_mode: pk_mode changed (%d) -> (%d),tx_throughput[%d],rx_throughput[%d]!}",
            g_st_wifi_pk_mode_status.en_is_pk_mode,en_curr_pk_mode,ul_tx_throughput,ul_rx_throughput);
    g_st_wifi_pk_mode_status.en_is_pk_mode = en_curr_pk_mode;
    g_st_wifi_pk_mode_status.ul_rx_bytes   = ul_rx_throughput;
    g_st_wifi_pk_mode_status.ul_tx_bytes   = ul_tx_throughput;
    g_st_wifi_pk_mode_status.ul_dur_time   = ul_dur_time;


    /***************************************************************************
        ????????DMAC??, ????VAP??????????DMAC
    ***************************************************************************/
    st_pk_mode_info.ul_rx_bytes = g_st_wifi_pk_mode_status.ul_rx_bytes;
    st_pk_mode_info.ul_tx_bytes = g_st_wifi_pk_mode_status.ul_tx_bytes;
    st_pk_mode_info.ul_dur_time = g_st_wifi_pk_mode_status.ul_dur_time;
    st_pk_mode_info.en_is_pk_mode  = g_st_wifi_pk_mode_status.en_is_pk_mode;
    st_pk_mode_info.en_curr_bw_cap = g_st_wifi_pk_mode_status.en_curr_bw_cap;
    st_pk_mode_info.en_curr_protocol_cap       = g_st_wifi_pk_mode_status.en_curr_protocol_cap;
    st_pk_mode_info.en_curr_num_spatial_stream = g_st_wifi_pk_mode_status.en_curr_num_spatial_stream;

    ul_ret = hmac_config_send_event_etc(pst_mac_vap, WLAN_CFGID_SYNC_PK_MODE, OAL_SIZEOF(mac_cfg_pk_mode_stru), (oal_uint8 *)(&st_pk_mode_info));
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_update_pk_mode::hmac_config_send_event_etc failed[%d].}", ul_ret);
    }


    return;
}
#endif


void hmac_perform_calc_throughput(oal_uint32 ul_tx_throughput_mbps,
                                  oal_uint32 ul_rx_throughput_mbps,
                                  oal_uint32 ul_trx_pps)
{
    oal_uint32 ul_limit_throughput_high;
    oal_uint32 ul_limit_throughput_low;
    oal_uint32   ul_limit_pps_high = 0;
    oal_uint32   ul_limit_pps_low = 0;

    if (OAL_FALSE == g_freq_lock_control_etc.en_irq_affinity)
    {
        return;
    }
    /* ?????????????? */
    if ((0 != g_freq_lock_control_etc.us_throughput_irq_high) && (0 != g_freq_lock_control_etc.us_throughput_irq_low))
    {
        ul_limit_throughput_high = g_freq_lock_control_etc.us_throughput_irq_high;
        ul_limit_throughput_low  = g_freq_lock_control_etc.us_throughput_irq_low;
    }
    else
    {
        ul_limit_throughput_high = WLAN_IRQ_THROUGHPUT_THRESHOLD_HIGH;
        ul_limit_throughput_low  = WLAN_IRQ_THROUGHPUT_THRESHOLD_LOW;
    }

    /* ????PPS???? */
    if ((0 != g_freq_lock_control_etc.ul_irq_pps_high) && (0 != g_freq_lock_control_etc.ul_irq_pps_low))
    {
        ul_limit_pps_high = g_freq_lock_control_etc.ul_irq_pps_high;
        ul_limit_pps_low  = g_freq_lock_control_etc.ul_irq_pps_low;
    }
    else
    {
        ul_limit_pps_high = WLAN_IRQ_PPS_THRESHOLD_HIGH;
        ul_limit_pps_low  = WLAN_IRQ_PPS_THRESHOLD_LOW;
    }

    /* ????200M??????????????150M?????? */
    if ((ul_tx_throughput_mbps > ul_limit_throughput_high)
        || (ul_rx_throughput_mbps >  ul_limit_throughput_high)
        || (ul_trx_pps >= ul_limit_pps_high))
    {
        g_freq_lock_control_etc.uc_req_irq_cpu = WLAN_IRQ_AFFINITY_BUSY_CPU;
    }
    else if((ul_tx_throughput_mbps < ul_limit_throughput_low)
           && (ul_rx_throughput_mbps <  ul_limit_throughput_low)
           && (ul_trx_pps < ul_limit_pps_low))
    {
        g_freq_lock_control_etc.uc_req_irq_cpu = WLAN_IRQ_AFFINITY_IDLE_CPU;
    }
    else
    {
        return;
    }

    if (g_freq_lock_control_etc.uc_req_irq_cpu != g_freq_lock_control_etc.uc_cur_irq_cpu)
    {
        OAM_WARNING_LOG4(0,OAM_SF_ANY,"{hmac_perform_calc_throughput: rx = %d , tx = %d, pps_high = %d, pps low = %d!}",
            ul_rx_throughput_mbps , ul_tx_throughput_mbps,ul_limit_pps_high,ul_limit_pps_low);
        OAM_WARNING_LOG4(0,OAM_SF_ANY,"{hmac_perform_calc_throughput: req cpu id[%d],cur cpu id[%d],high_th = %d,low_th = %d!}",
              g_freq_lock_control_etc.uc_req_irq_cpu, g_freq_lock_control_etc.uc_cur_irq_cpu,ul_limit_throughput_high,ul_limit_throughput_low);
        OAM_WARNING_LOG3(0,OAM_SF_ANY,"{hmac_perform_calc_throughput: rx pps = %d , tx pps = %d, trx pps = %d,!}",
            g_freq_lock_control_etc.ul_rx_pps, g_freq_lock_control_etc.ul_tx_pps,ul_trx_pps);
    }

    hmac_adjust_set_irq(g_freq_lock_control_etc.uc_req_irq_cpu);

}


void hmac_adjust_throughput(oal_void)
{
    oal_uint32 ul_tx_throughput      = 0;
    oal_uint32 ul_rx_throughput      = 0;
    oal_uint32 ul_dur_time;
    oal_uint32 ul_tx_throughput_mbps = 0;
    oal_uint32 ul_rx_throughput_mbps = 0;

    /* ???????????? */
    g_freq_lock_control_etc.uc_timer_cycles++;

    ul_dur_time = OAL_JIFFIES_TO_MSECS(jiffies - g_freq_lock_control_etc.ul_pre_time);

    /* ????????????,?????? */
    if (ul_dur_time < WLAN_FREQ_TIMER_PERIOD - 10)
    {
        return;
    }

    /* ????????????????????,?????????????? */
    if (ul_dur_time > ((WLAN_FREQ_TIMER_PERIOD * WLAN_THROUGHPUT_STA_PERIOD) << 2))
    {
        g_freq_lock_control_etc.ul_pre_time = jiffies;
        g_freq_lock_control_etc.uc_timer_cycles = 0;

        g_st_wifi_rxtx_total.ul_rx_bytes = 0;
        g_st_wifi_rxtx_total.ul_tx_bytes = 0;

        return;
    }


    /* ???????? */
    ul_rx_throughput = g_st_wifi_rxtx_total.ul_rx_bytes;
    ul_tx_throughput = g_st_wifi_rxtx_total.ul_tx_bytes;
    if(0 != ul_dur_time)
    {
        ul_tx_throughput_mbps = (ul_tx_throughput >> 7) / ul_dur_time;
        ul_rx_throughput_mbps = (ul_rx_throughput >> 7) / ul_dur_time;
    }

    /* Wi-Fi???????????? */
    if (ul_rx_throughput_mbps <= WLAN_THROUGHPUT_LOAD_LOW)
    {
        g_st_wifi_load.en_wifi_rx_busy = OAL_FALSE;
    }
    else
    {
        g_st_wifi_load.en_wifi_rx_busy = OAL_TRUE;
    }
    if(OAL_TRUE == g_st_wifi_rxtx_total.uc_trx_stat_log_en)
    {
        OAM_WARNING_LOG4(0,OAM_SF_ANY,"{hmac_tx_tcp_ack_buf_switch: rx_throught= [%d],tx_throughput = [%d],smooth_throughtput = [%d],dur_time = [%d]ms!}",
                ul_rx_throughput_mbps, ul_tx_throughput_mbps, g_st_tcp_ack_buf_switch.us_tcp_ack_smooth_throughput,ul_dur_time);
    }

#ifdef _PRE_WLAN_FEATURE_MULTI_NETBUF_AMSDU
    /* AMSDU+AMPDU???????????? */
    hmac_tx_amsdu_ampdu_switch(ul_tx_throughput_mbps);
#endif
    hmac_tx_small_amsdu_switch(ul_rx_throughput_mbps, g_freq_lock_control_etc.ul_tx_pps);

#ifdef _PRE_WLAN_FEATURE_TCP_ACK_BUFFER
    hmac_tx_tcp_ack_buf_switch(ul_rx_throughput_mbps);
#endif

#ifdef _PRE_WLAN_FEATURE_AMPDU_TX_HW
    /* ??????????????????,???????????????? */
    hmac_tx_ampdu_switch(ul_tx_throughput_mbps);
#endif
#ifdef _PRE_WLAN_TCP_OPT
    hmac_tcp_ack_filter_switch(ul_rx_throughput_mbps);
#endif
    /* ????????????????????????bypass ????LNA */
    hmac_rx_dyn_bypass_extlna_switch(ul_tx_throughput_mbps, ul_rx_throughput_mbps);


    /* irq 2s ???????? */
    if (g_freq_lock_control_etc.uc_timer_cycles < WLAN_THROUGHPUT_STA_PERIOD)
    {
        return;
    }
    g_freq_lock_control_etc.uc_timer_cycles = 0;

    /* 2s???????????? */
    g_st_wifi_rxtx_total.ul_rx_bytes = 0;
    g_st_wifi_rxtx_total.ul_tx_bytes = 0;

    g_freq_lock_control_etc.ul_pre_time = jiffies;

#ifdef _PRE_WLAN_FEATURE_NEGTIVE_DET
    /* ????pk mode */
    hmac_update_pk_mode(ul_tx_throughput_mbps, ul_rx_throughput_mbps, ul_dur_time);
#endif
    /* ???????????? */
    hmac_perform_calc_throughput(ul_tx_throughput_mbps, ul_rx_throughput_mbps,g_freq_lock_control_etc.ul_total_sdio_pps);

}


oal_void hmac_wlan_freq_wdg_timeout(oal_void)
{
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    /* CPU???? */
    hmac_adjust_freq_etc();
#endif
    /* ???????? */
    hmac_adjust_throughput();

}



oal_void  hmac_freq_timer_init(oal_void)
{
    /*??????????????????????????????????????????????????????????????*/
    if (OAL_TRUE == g_freq_lock_control_etc.hmac_freq_timer.en_is_registerd)
    {
        return;
    }

    g_freq_lock_control_etc.ul_pre_time = jiffies;
    /* uc_timer_cycles ????????????????????????????????????????????????PK mode???????????????? */
    //g_freq_lock_control_etc.uc_timer_cycles = 0;
    /* ???????? */
    OAL_MEMZERO(&g_st_wifi_rxtx_total, OAL_SIZEOF(g_st_wifi_rxtx_total));

    FRW_TIMER_CREATE_TIMER(&g_freq_lock_control_etc.hmac_freq_timer, //pst_timeout
                        (oal_void*)hmac_wlan_freq_wdg_timeout,   //p_timeout_func
                        WLAN_FREQ_TIMER_PERIOD,                 //ul_timeout
                        OAL_PTR_NULL,                          // p_timeout_arg
                        OAL_TRUE,                             //en_is_periodic
                        OAM_MODULE_ID_HMAC,0 );             //en_module_id && ul_core_id

    //OAM_WARNING_LOG1(0,OAM_SF_ANY,"{hmac_freq_timer_init: throughput timer period[%d]ms enabled!}",WLAN_FREQ_TIMER_PERIOD);
}


oal_void  hmac_freq_timer_deinit(oal_void)
{
    /*??????????????????????????????????????????????*/
    if (OAL_FALSE == g_freq_lock_control_etc.hmac_freq_timer.en_is_registerd)
    {
        return;
    }

    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&g_freq_lock_control_etc.hmac_freq_timer);
}

oal_void  hmac_wifi_pm_state_notify(oal_bool_enum_uint8 en_wake_up)
{
    if (OAL_TRUE == en_wake_up)
    {
        /* WIFI????,???????????????????? */
        hmac_freq_timer_init();
    }
    else
    {
        /* WIFI????,???????????????????? */
        hmac_freq_timer_deinit();
    }
}


oal_void  hmac_wifi_state_notify(oal_bool_enum_uint8 en_wifi_on)
{
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    if (OAL_TRUE == en_wifi_on)
    {
        /* WIFI????,????????????????????,???????????? */
        hmac_freq_timer_init();
        hmac_set_device_freq_mode_etc(FREQ_LOCK_ENABLE);
    }
    else
    {
        /* WIFI????,????????????????????,???????????? */
        hmac_freq_timer_deinit();
        hmac_set_device_freq_mode_etc(FREQ_LOCK_DISABLE);
    }
#endif
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

