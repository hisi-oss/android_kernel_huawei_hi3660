


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_DAQ

/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "dmac_data_acq.h"
#include "hal_ext_if.h"
#include "dmac_main.h"
#include "dmac_config.h"



#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_DATA_ACQ_C

extern oal_uint32  dmac_get_cmd_one_arg(oal_int8 *pc_cmd, oal_int8 *pc_arg, oal_uint32 *pul_cmd_offset);


#define DMAC_DATA_ACQ_PER_MAX_NUM             (64)
#define DMAC_DATA_ACQ_UNIT_MAX_LEN            (1000)                          //????????????????????
#define DMAC_DATA_ACQ_DATA_HEAD_LEN           OAL_SIZEOF(dmac_data_acq_data_head_stru)
#define DMAC_DATA_ACQ_UNIT_DATA_LEN           (DMAC_DATA_ACQ_UNIT_MAX_LEN - DMAC_DATA_ACQ_DATA_HEAD_LEN)  //??????????
#define DMAC_DATA_ACQ_MAX_WAIT_TIME           (200)

/*****************************************************************************
  2 ????????????
*****************************************************************************/
dmac_data_acq_stru           g_st_data_acq;         /* ?????????????????????????????? */

/*****************************************************************************
  3 ????????
*****************************************************************************/

OAL_STATIC oal_bool_enum_uint8 dmac_data_acq_get_send_flag(oal_void)
{
    return g_st_data_acq.en_daq_apprecv_ready;
}


OAL_STATIC oal_void dmac_data_acq_set_send_flag(oal_bool_enum_uint8  en_bool)
{
    g_st_data_acq.en_daq_apprecv_ready = en_bool;
}


oal_uint32  dmac_data_acq_mem_free(oal_void)
{
    if (OAL_PTR_NULL != g_st_data_acq.st_daq_prep_info.puc_start_addr)
    {
        oal_free((void *)g_st_data_acq.st_daq_prep_info.puc_start_addr);
        g_st_data_acq.st_daq_prep_info.puc_start_addr = OAL_PTR_NULL;
    }

    return OAL_SUCC;
}


oal_uint32 dmac_data_acq_mem_alloc(oal_void)
{
    /*  ?????????? */
    dmac_data_acq_mem_free();

    OAL_MEMZERO(&(g_st_data_acq.st_daq_prep_info), OAL_SIZEOF(dmac_data_acq_prep_stru));

    /* ???????? */
    g_st_data_acq.st_daq_prep_info.puc_start_addr = (oal_uint8 *)oal_memalloc(DMAC_DATA_ACQ_MAX_LEN);

    if (OAL_PTR_NULL == g_st_data_acq.st_daq_prep_info.puc_start_addr)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_data_acq_mem_alloc::puc_start_addr null.}");

        return OAL_FAIL;
    }

    return OAL_SUCC;
}


oal_uint32  dmac_data_acq_prepare(mac_vap_stru *pst_mac_vap,oal_uint8 *puc_param, mac_device_stru *pst_device)
{
    oal_uint32                  ul_offset = 0;
    oal_uint16                  us_left = 0;
    oal_int8                    ac_name[DMAC_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                  ul_ret;
    oal_uint32                  ul_unit_num = 0;

    OAL_MEMZERO(ac_name, DMAC_HIPRIV_CMD_NAME_MAX_LEN);

    if (DMAC_DATA_ACQ_STATUS_ENABLE == g_st_data_acq.en_daq_status)
    {
        /* ???????????????????????????? */

        return OAL_SUCC;
    }

    ul_ret = dmac_data_acq_mem_alloc();
    if (OAL_SUCC != ul_ret)
    {
       /* ?????????? */
       OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_data_acq_prepare::g_puc_mem_daq_addr null.}");

       g_st_data_acq.en_daq_status = DMAC_DATA_ACQ_STATUS_INIT;
       return ul_ret;
    }

    /* 1?????????????????????? */
    dmac_get_cmd_one_arg((oal_int8*)puc_param, ac_name, &ul_offset);
    g_st_data_acq.st_daq_prep_info.us_len_unit = (oal_uint16)oal_atoi(ac_name);

    puc_param = puc_param + ul_offset;

    /* ?????????????????????????????????????????????????? */
    if (DMAC_DATA_ACQ_MAX_UNITLEN < g_st_data_acq.st_daq_prep_info.us_len_unit )
    {
        g_st_data_acq.st_daq_prep_info.us_len_unit = DMAC_DATA_ACQ_MAX_UNITLEN;
    }

    /* ????????????????8????????????????8?????? */
    us_left = g_st_data_acq.st_daq_prep_info.us_len_unit % 8;

    g_st_data_acq.st_daq_prep_info.us_len_unit -= us_left;

    /* 2?????????????????????? */
    dmac_get_cmd_one_arg((oal_int8*)puc_param, ac_name, &ul_offset);
    ul_unit_num = (oal_uint32)oal_atoi(ac_name);

    /* ?????????????????? */
    puc_param = puc_param + ul_offset;
    g_st_data_acq.st_daq_prep_info.us_num = (oal_uint16)ul_unit_num;

    /* ?????????????????????????????????????????? */
    if (DMAC_DATA_ACQ_MAX_UNITNUM < ul_unit_num)
    {
        g_st_data_acq.st_daq_prep_info.us_num = DMAC_DATA_ACQ_MAX_UNITNUM;
    }

    /* 3?????????????????????? */
    dmac_get_cmd_one_arg((oal_int8*)puc_param, ac_name, &ul_offset);
    g_st_data_acq.st_daq_prep_info.us_depth = (oal_uint16)oal_atoi(ac_name);

    /* ???????????????????????????????????????????? */
    if (g_st_data_acq.st_daq_prep_info.us_depth > g_st_data_acq.st_daq_prep_info.us_num)
    {
        g_st_data_acq.st_daq_prep_info.us_depth = g_st_data_acq.st_daq_prep_info.us_num;
    }

    g_st_data_acq.ul_length = ((g_st_data_acq.st_daq_prep_info.us_depth) * (g_st_data_acq.st_daq_prep_info.us_len_unit));

    /* ?????????????????? */
    puc_param = puc_param + ul_offset;

    /* ???????????????????????????????????????????????????????????????????? */
    if (DMAC_DATA_ACQ_MAX_LEN < g_st_data_acq.ul_length)
    {
        g_st_data_acq.st_daq_prep_info.us_depth = (oal_uint16)(DMAC_DATA_ACQ_MAX_LEN / g_st_data_acq.st_daq_prep_info.us_len_unit);
        g_st_data_acq.ul_length = (oal_uint32)((g_st_data_acq.st_daq_prep_info.us_len_unit) * (g_st_data_acq.st_daq_prep_info.us_depth));
    }

    /* ????MAC?????? */
    hal_set_daq_mac_reg(pst_device->pst_device_stru,
                       (oal_uint32 *)g_st_data_acq.st_daq_prep_info.puc_start_addr,
                       g_st_data_acq.st_daq_prep_info.us_len_unit,
                       g_st_data_acq.st_daq_prep_info.us_num,
                       g_st_data_acq.st_daq_prep_info.us_depth);

    g_st_data_acq.en_daq_status = DMAC_DATA_ACQ_STATUS_MAC_REG;

    return OAL_SUCC;
}


oal_uint32  dmac_data_acq_condition(mac_vap_stru *pst_mac_vap,oal_uint8 *puc_param, mac_device_stru *pst_device)
{
    oal_uint32                  ul_offset = 0;
    oal_int8                    ac_name[DMAC_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint8                   uc_value;
    oal_uint32                  ul_val;

    OAL_MEMZERO(ac_name, DMAC_HIPRIV_CMD_NAME_MAX_LEN);

    if ((DMAC_DATA_ACQ_STATUS_BUTT > g_st_data_acq.en_daq_status) && ((DMAC_DATA_ACQ_STATUS_INIT == g_st_data_acq.en_daq_status) || (DMAC_DATA_ACQ_STATUS_ENABLE == g_st_data_acq.en_daq_status)))
    {
        /* ???????????????????????????? */
        return OAL_SUCC;
    }

    OAL_MEMZERO(&(g_st_data_acq.st_daq_cond), OAL_SIZEOF(dmac_data_acq_cond_stru));

    /* 1?????????????? */
    dmac_get_cmd_one_arg((oal_int8*)puc_param, ac_name, &ul_offset);
    uc_value = (oal_uint8)oal_atoi(ac_name);

    if (WITP_RF_CHANNEL_NUMS < uc_value)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_data_acq_condition::invalid uc_value[%d].}", uc_value);

        g_st_data_acq.en_daq_status = DMAC_DATA_ACQ_STATUS_MAC_REG;
        return OAL_FAIL;
    }

    g_st_data_acq.st_daq_cond.bit_cfg_real_sample_ch_sel = uc_value;

    /* ?????????????????? */
    puc_param = puc_param + ul_offset;

    /* 2?????????????????? */
    dmac_get_cmd_one_arg((oal_int8*)puc_param, ac_name, &ul_offset);
    uc_value = (oal_uint8)oal_atoi(ac_name);

    if ((DMAC_DATA_ACQ_COND_BUTT <= (dmac_data_acq_cond_enum_uint8)uc_value)
       || (DMAC_DATA_ACQ_COND_ADC_TH > (dmac_data_acq_cond_enum_uint8)uc_value))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_data_acq_condition::invalid uc_value[%d].}", uc_value);

        g_st_data_acq.en_daq_status = DMAC_DATA_ACQ_STATUS_MAC_REG;
        return OAL_FAIL;
    }

    g_st_data_acq.st_daq_cond.bit_cfg_real_sample_cond_ctrl = uc_value;
    /* ?????????????????? */
    puc_param = puc_param + ul_offset;

    /* 3?????????????????????? */
    dmac_get_cmd_one_arg((oal_int8*)puc_param, ac_name, &ul_offset);
    uc_value = (oal_uint8)oal_atoi(ac_name);
    /* ?????????????????? */
    puc_param = puc_param + ul_offset;

    if (DMAC_DATA_ACQ_COND_ADC_TH == (g_st_data_acq.st_daq_cond.bit_cfg_real_sample_cond_ctrl & DMAC_DATA_ACQ_COND_ADC_TH))
    {
        if (0 == uc_value)
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_data_acq_prepare::uc_value=0.}");

            g_st_data_acq.en_daq_status = DMAC_DATA_ACQ_STATUS_MAC_REG;
            return OAL_FAIL;
        }

        g_st_data_acq.st_daq_cond.bit_cfg_real_sample_data_th = uc_value;
    }

    /* 4??????????????bit???? */
    dmac_get_cmd_one_arg((oal_int8*)puc_param, ac_name, &ul_offset);
    uc_value = (oal_uint8)oal_atoi(ac_name);
    /* ?????????????????? */
    puc_param = puc_param + ul_offset;

    if (DMAC_DATA_ACQ_BIT_BUTT <= (dmac_data_acq_bit_enum_uint8)uc_value)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_data_acq_prepare::invalid uc_value[%d].}", uc_value);

        g_st_data_acq.en_daq_status = DMAC_DATA_ACQ_STATUS_MAC_REG;
        return OAL_FAIL;
    }

    g_st_data_acq.st_daq_cond.bit_cfg_real_sample_bits_sel = uc_value;

    ul_val = *((oal_uint32 *)(&g_st_data_acq.st_daq_cond));

    /* ????PHY?????? */
    hal_set_daq_phy_reg(pst_device->pst_device_stru, ul_val);

    /* ?????????????????????????????? */
    g_st_data_acq.en_daq_status = DMAC_DATA_ACQ_STATUS_PHY_REG;

    return OAL_SUCC;
}

oal_uint32  dmac_data_acq_enable(mac_vap_stru *pst_mac_vap,oal_uint8 *puc_param, mac_device_stru *pst_device)
{
    if ((DMAC_DATA_ACQ_STATUS_PHY_REG != g_st_data_acq.en_daq_status) && (DMAC_DATA_ACQ_STATUS_COMPLETE != g_st_data_acq.en_daq_status))
    {
        /* ???????????????????????????????? */
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_data_acq_enable::invalid en_daq_status[%d].}", g_st_data_acq.en_daq_status);

        return OAL_FAIL;
    }

    g_st_data_acq.st_daq_prep_info.en_daq_enable = OAL_TRUE;
    g_st_data_acq.st_daq_cond.bit_cfg_real_sample_en = OAL_TRUE;

    /* ???????????? */
    g_st_data_acq.en_daq_status = DMAC_DATA_ACQ_STATUS_ENABLE;

    /* ????MAC??PHY?????? */
    hal_set_daq_en(pst_device->pst_device_stru, (oal_uint8)(g_st_data_acq.st_daq_prep_info.en_daq_enable));

    return OAL_SUCC;
}


oal_uint32  dmac_data_acq_get_status(mac_vap_stru *pst_mac_vap,oal_uint8 *puc_param, mac_device_stru *pst_device)
{
    oal_uint32                  ul_reg_value = 0;

    /* ?????????? */
    hal_get_daq_status(pst_device->pst_device_stru, &ul_reg_value);

    /* ???????? */
    if (BIT0 == ul_reg_value)
    {
        g_st_data_acq.en_daq_status = DMAC_DATA_ACQ_STATUS_COMPLETE;
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_data_acq_get_status::end func.}");
    }

    return OAL_SUCC;
}


oal_uint32 dmac_data_acq_report_data_info(oal_uint8 *puc_daq_addr, oal_uint32 ul_len, oal_netbuf_stru *pst_netbuf)
{
    dmac_data_acq_info_stru        *pst_daq_data_info           = OAL_PTR_NULL;
    dmac_data_acq_data_head_stru   *pst_daq_data_head           = OAL_PTR_NULL;
    oal_int32                       l_bytes = 0;
    oal_uint32                      ul_time = 0;

    /***** ??????????????????app ?????????? *****/
    pst_daq_data_head = (dmac_data_acq_data_head_stru *)oal_netbuf_data(pst_netbuf);

    pst_daq_data_head->en_send_type = DMAC_DATA_ACQ_SEND_TYPE_INFO;
    pst_daq_data_head->ul_msg_sn    = 0;
    pst_daq_data_head->ul_data_len  = OAL_SIZEOF(dmac_data_acq_info_stru);

    /***** ??????????????????app ???????????? *****/
    pst_daq_data_info = (dmac_data_acq_info_stru *)(oal_netbuf_data(pst_netbuf) + DMAC_DATA_ACQ_DATA_HEAD_LEN);

    pst_daq_data_info->ul_daq_addr    = (oal_uint32)puc_daq_addr;
    pst_daq_data_info->ul_data_len    = ul_len;
    pst_daq_data_info->ul_unit_len    = DMAC_DATA_ACQ_UNIT_DATA_LEN;


    /***** ??daq info????app?? *****/
    l_bytes = oam_netlink_kernel_send(oal_netbuf_data(pst_netbuf), OAL_SIZEOF(dmac_data_acq_info_stru) + DMAC_DATA_ACQ_DATA_HEAD_LEN, OAM_NL_CMD_DAQ);

    if (l_bytes <= 0)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_data_acq_report_data_info::invalid l_bytes[%d].}", l_bytes);

        return OAL_FAIL;
    }

    g_st_data_acq.uc_ack_flag = OAL_FALSE;

    while(!g_st_data_acq.uc_ack_flag)
    {

        oal_msleep(1000);

        if (DMAC_DATA_ACQ_MAX_WAIT_TIME <= ul_time)
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_data_acq_report_data_info::wait app ack timeout. Try again.}");

            return OAL_FAIL;
        }

        ul_time++;
    }

    return OAL_SUCC;
}


oal_uint32 dmac_data_acq_report_data_unit(oal_uint8 *puc_daq_addr, oal_uint32 ul_len, oal_netbuf_stru *pst_netbuf)
{
    dmac_data_acq_data_head_stru   *pst_daq_data_head;
    oal_int32                       l_bytes = 0;

    pst_daq_data_head = (dmac_data_acq_data_head_stru *)oal_netbuf_data(pst_netbuf);

    /* ?????????? */
    pst_daq_data_head->en_send_type    = DMAC_DATA_ACQ_SEND_TYPE_UNIT;
    pst_daq_data_head->ul_msg_sn       = g_st_data_acq.ul_daq_sn;
    pst_daq_data_head->ul_data_len     = ul_len;

    oal_memcopy((oal_uint8 *)pst_daq_data_head + DMAC_DATA_ACQ_DATA_HEAD_LEN, puc_daq_addr, ul_len);

    l_bytes = oam_netlink_kernel_send(oal_netbuf_data(pst_netbuf), OAL_SIZEOF(dmac_data_acq_info_stru) + ul_len, OAM_NL_CMD_DAQ);

    if (l_bytes <= 0)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_data_acq_report_data_unit::invalid l_bytes[%d].}", l_bytes);

        return OAL_FAIL;
    }

    g_st_data_acq.ul_daq_sn++;

    /* ????APP?????????? */
    if (0 == g_st_data_acq.ul_daq_sn % DMAC_DATA_ACQ_PER_MAX_NUM)
    {
        dmac_data_acq_set_send_flag(OAL_FALSE);
    }

    return OAL_SUCC;
}


oal_uint32 dmac_data_acq_report_data(oal_uint8 *puc_daq_addr, oal_uint32 ul_len, oal_netbuf_stru *pst_netbuf)
{
    oal_uint8                      *puc_data_offset             = OAL_PTR_NULL;
    oal_uint32                      ul_trans_remainder_len      = 0;
    oal_uint32                      ul_unit_len;
    oal_uint32                      ul_ret;
    oal_uint32                      ul_time = 0;

    ul_trans_remainder_len  = ul_len;
    ul_unit_len             = DMAC_DATA_ACQ_UNIT_DATA_LEN;
    puc_data_offset         = puc_daq_addr;

    g_st_data_acq.ul_daq_sn  = 0;

    dmac_data_acq_set_send_flag(OAL_TRUE);

    /* ????daq ???????? */
    while (ul_trans_remainder_len >= ul_unit_len)
    {
        if (OAL_FALSE == g_st_data_acq.en_daq_app_error)
        {
            if (OAL_TRUE == dmac_data_acq_get_send_flag())
            {
                ul_ret = dmac_data_acq_report_data_unit(puc_data_offset, ul_unit_len, pst_netbuf);
                if (ul_ret != OAL_SUCC)
                {
                    /* ???????? */
                    OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_data_acq_report_data::dmac_data_acq_report_data_unit failed[%d].}", ul_ret);

                    return ul_ret;
                }

                ul_trans_remainder_len  -= ul_unit_len;
                puc_data_offset         += ul_unit_len;
            }
            else
            {
                oal_msleep(1000);

                if (DMAC_DATA_ACQ_MAX_WAIT_TIME <= ul_time)
                {
                    OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_report_data_acq_record::send data uint failed. Try again.}");

                    return OAL_FAIL;
                }

                ul_time++;
            }
        }
        else
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_report_data_acq_record::send data uint failed. app error, Try again.}");

            return OAL_FAIL;
        }
    }

    /* ???????????????????? */
    if ((ul_trans_remainder_len != 0) && (OAL_FALSE == g_st_data_acq.en_daq_app_error))
    {

        ul_ret = dmac_data_acq_report_data_unit(puc_data_offset, ul_trans_remainder_len,pst_netbuf);
        if (ul_ret != OAL_SUCC)
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_report_data_acq_record::dmac_data_acq_report_data_unit failed[%d].}", ul_ret);

            return ul_ret;
        }
    }

    g_st_data_acq.uc_ack_flag = OAL_FALSE;

    while(!g_st_data_acq.uc_ack_flag)
    {

        oal_msleep(1000);

        if ((OAL_TRUE == g_st_data_acq.en_daq_app_error) || (DMAC_DATA_ACQ_MAX_WAIT_TIME <= ul_time))
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_data_acq_report_data::wait app ack timeout or app error. Try again.}");

            return OAL_FAIL;
        }

        ul_time++;
    }

    return OAL_SUCC;
}


oal_void dmac_data_acq_workqueue(oal_work_stru *pst_work)
{
    oal_uint32                      ul_ret;
    oal_netbuf_stru                *pst_netbuf;
    dmac_data_acq_info_stru        *pst_daq_info;
    oal_uint8                      *puc_daq_addr;
    oal_uint32                      ul_len;

    pst_netbuf = oal_netbuf_delist(&g_st_data_acq.st_daq_workqueue.rx_daq_dbg_seq);

    while (OAL_PTR_NULL != pst_netbuf)
    {

        pst_daq_info = (dmac_data_acq_info_stru *)oal_netbuf_data(pst_netbuf);
        puc_daq_addr = (oal_uint8 *)pst_daq_info->ul_daq_addr;
        ul_len       = pst_daq_info->ul_data_len;

        /* ??????????????APP????app??????????????FAIL ????APP?????????? */
        ul_ret = dmac_data_acq_report_data_info(puc_daq_addr, ul_len, pst_netbuf);
        if (OAL_SUCC == ul_ret)
        {
            dmac_data_acq_report_data(puc_daq_addr, ul_len, pst_netbuf);
        }

        oal_netbuf_free(pst_netbuf);

        pst_netbuf = oal_netbuf_delist(&g_st_data_acq.st_daq_workqueue.rx_daq_dbg_seq);
    }
}


oal_uint32  dmac_data_acq_get_record(oal_void)
{
    oal_netbuf_stru                *pst_queue_netbuf;
    dmac_data_acq_info_stru        *pst_daq_info;
    oal_uint32                      ul_ret = OAL_FAIL;

    /* ???????????????????? */
    if (DMAC_DATA_ACQ_STATUS_COMPLETE == g_st_data_acq.en_daq_status)
    {
        /* ???????? */
        g_st_data_acq.en_daq_app_error = OAL_FALSE;
        pst_queue_netbuf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, DMAC_DATA_ACQ_UNIT_MAX_LEN, OAL_NETBUF_PRIORITY_MID);

        if (OAL_PTR_NULL == pst_queue_netbuf)
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_data_acq_get_record::pst_queue_netbuf null.}");

            return OAL_ERR_CODE_PTR_NULL;
        }
        pst_daq_info = (dmac_data_acq_info_stru *)oal_netbuf_data(pst_queue_netbuf);

        pst_daq_info->ul_daq_addr = (oal_uint32)g_st_data_acq.st_daq_prep_info.puc_start_addr;
        pst_daq_info->ul_data_len = g_st_data_acq.ul_length;
        pst_daq_info->ul_unit_len = DMAC_DATA_ACQ_UNIT_DATA_LEN;

        oal_netbuf_add_to_list_tail(pst_queue_netbuf, &g_st_data_acq.st_daq_workqueue.rx_daq_dbg_seq);

        oal_queue_work(g_st_data_acq.st_daq_workqueue.daq_rx_workqueue, &g_st_data_acq.st_daq_workqueue.rx_daq_work);

        ul_ret = OAL_SUCC;
    }
    else
    {
        /* ?????????????????????????????? */
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_data_acq_get_record::data acq is running.}");

        ul_ret = OAL_FAIL;
    }

    return ul_ret;
}



oal_uint32  dmac_config_data_acq(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_data_acq_enum_uint8    en_data_acq = 0;
    oal_uint32                  ul_ret = OAL_SUCC;
    mac_device_stru            *pst_device;
    oal_uint32                  ul_offset = 0;
    oal_int8                    ac_name[DMAC_HIPRIV_CMD_NAME_MAX_LEN];

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    /* ???????????????? */
    if(OAL_PTR_NULL == pst_device)
    {
        return OAL_FAIL;
    }

    OAL_MEMZERO(ac_name, DMAC_HIPRIV_CMD_NAME_MAX_LEN);

    /* ?????????????????????? */
    dmac_get_cmd_one_arg((oal_int8*)puc_param, ac_name, &ul_offset);
    en_data_acq = (dmac_data_acq_enum_uint8)oal_atoi(ac_name);
    /* ?????????????????? */
    puc_param = puc_param + ul_offset;

    switch(en_data_acq)
    {
        case DMAC_DATA_ACQ_PRE:
             /* ????MAC?????? */
             ul_ret = dmac_data_acq_prepare(pst_mac_vap, puc_param, pst_device);

             break;
        case DMAC_DATA_ACQ_COND:
             /* ????PHY?????? */
             ul_ret = dmac_data_acq_condition(pst_mac_vap, puc_param, pst_device);

             break;
        case DMAC_DATA_ACQ_ENABLE:
            /* ???????????????? */
             ul_ret = dmac_data_acq_enable(pst_mac_vap, puc_param, pst_device);

             break;
        case DMAC_DATA_ACQ_STATUS:
            /* ???????????????? */
             ul_ret = dmac_data_acq_get_status(pst_mac_vap, puc_param, pst_device);

             break;
        case DMAC_DATA_ACQ_RECODE:
            /* ???????????????? */
             ul_ret = dmac_data_acq_get_record();

             break;
        default:
             break;
    }

    return ul_ret;
}


oal_uint32  dmac_data_acq_recv_msg(oal_uint8 *puc_data, oal_uint32 ul_len)
{
    dmac_data_acq_data_head_stru   *pst_frag_hdr;

    pst_frag_hdr = (dmac_data_acq_data_head_stru *)puc_data;

    switch (pst_frag_hdr->en_send_type)
    {
        case DMAC_DATA_ACQ_SEND_TYPE_READY:
            /*  APP????????????????????????  */
            dmac_data_acq_set_send_flag(OAL_TRUE);
            break;

        case DMAC_DATA_ACQ_SEND_TYPE_FAIL:
            /*  APP??????????????  */
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_data_acq_report_data_info::DMAC_DATA_ACQ_SEND_TYPE_FAIL.}");

            g_st_data_acq.en_daq_app_error = OAL_TRUE;
            break;

        case DMAC_DATA_ACQ_SEND_TYPE_ACK:
            /* APP????ACK */

            g_st_data_acq.uc_ack_flag = OAL_TRUE;
            break;
        default:
            return OAL_FAIL;
    }

    return OAL_SUCC;

}

oal_uint32  dmac_data_acq_init(oal_void)
{
    /* ???????????????????? */
    OAL_MEMZERO(&g_st_data_acq, OAL_SIZEOF(dmac_data_acq_stru));

    g_st_data_acq.en_daq_apprecv_ready = OAL_TRUE;

    /* ????DAQ??netlink???????? */
    oam_netlink_ops_register(OAM_NL_CMD_DAQ, dmac_data_acq_recv_msg);

    /* ?????????????? */
    OAL_MEMZERO((void *)&g_st_data_acq.st_daq_workqueue, OAL_SIZEOF(dmac_data_acq_workqueue_stru));
    g_st_data_acq.st_daq_workqueue.daq_rx_workqueue = OAL_CREATE_SINGLETHREAD_WORKQUEUE("daq_rx_queue");
    OAL_INIT_WORK(&g_st_data_acq.st_daq_workqueue.rx_daq_work, dmac_data_acq_workqueue);
    oal_netbuf_list_head_init(&g_st_data_acq.st_daq_workqueue.rx_daq_dbg_seq);

    return OAL_SUCC;
}


oal_uint32  dmac_data_acq_exit(oal_void)
{
    /* ???????? */
    dmac_data_acq_mem_free();

    /* ??????DAQ??netlink???????? */
    oam_netlink_ops_unregister(OAM_NL_CMD_DAQ);

    /* ???????????? */
    oal_destroy_workqueue(g_st_data_acq.st_daq_workqueue.daq_rx_workqueue);
    oal_netbuf_queue_purge(&g_st_data_acq.st_daq_workqueue.rx_daq_dbg_seq);

    return OAL_SUCC;
}

/*lint -e578*//*lint -e19*/
oal_module_license("GPL");
/*lint +e578*//*lint +e19*/

#endif /* end of _PRE_WLAN_FEATURE_DAQ */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

