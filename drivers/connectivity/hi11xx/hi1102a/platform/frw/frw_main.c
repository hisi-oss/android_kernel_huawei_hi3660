


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "frw_main.h"
#include "frw_task.h"
#include "frw_event_main.h"
#include "frw_event_deploy.h"
#include "frw_ext_if.h"
#include "frw_timer.h"

#if defined(_PRE_PRODUCT_ID_HI110X_HOST)
#include "oal_hcc_host_if.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_MAIN_C
/*****************************************************************************
  2 ????????????
*****************************************************************************/
frw_init_enum_uint16 g_en_wlan_driver_init_state = FRW_INIT_STATE_BUTT;
OAL_STATIC frw_event_sub_table_item_stru g_ast_frw_timeout_event_sub_table[FRW_TIMEOUT_SUB_TYPE_BUTT];

/*****************************************************************************
  3 ????????
*****************************************************************************/

oal_uint32  frw_event_fsm_register(oal_void)
{
    g_ast_frw_timeout_event_sub_table[FRW_TIMEOUT_TIMER_EVENT].p_func = frw_timer_timeout_proc;
    frw_event_table_register(FRW_EVENT_TYPE_TIMEOUT, FRW_EVENT_PIPELINE_STAGE_0, g_ast_frw_timeout_event_sub_table);

    return OAL_SUCC;
}

/*lint -save -e578 -e19 */
DEFINE_GET_BUILD_VERSION_FUNC(frw);
/*lint -restore*/


oal_int32  frw_main_init(oal_void)
{
    oal_uint32          ul_ret;

    OAL_RET_ON_MISMATCH(frw, -OAL_EFAIL);

    frw_set_init_state(FRW_INIT_STATE_START);

    /* ?????????????????????????????????????? TBD */

    /* ?????????????????? */
    ul_ret = frw_event_init();
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_main_init:: frw_event_init return err code: %d}", ul_ret);
        return -OAL_EFAIL;
    }

    frw_task_init();

#if (_PRE_MULTI_CORE_MODE_PIPELINE_AMP == _PRE_MULTI_CORE_MODE)
    /* ?????????????????????? */
    ul_ret = frw_event_deploy_init();
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_main_init:: frw_event_deploy_init return err code: %d}", ul_ret);
        return -OAL_EFAIL;
    }
#endif

    frw_timer_init(FRW_TIMER_DEFAULT_TIME, frw_timer_timeout_proc_event, 0);

    frw_event_fsm_register();


    /* ???????????????????? ?????????????????? */
    frw_set_init_state(FRW_INIT_STATE_FRW_SUCC);

    return OAL_SUCC;
}


oal_void  frw_main_exit(oal_void)
{
    /* HCC???????? TBD */

    /* ?????????? */
    frw_timer_exit();

    /* ???????????????? */
    frw_event_exit();

    frw_task_exit();

#if (_PRE_MULTI_CORE_MODE_PIPELINE_AMP == _PRE_MULTI_CORE_MODE)
    /* ???????????????????? */
    frw_event_deploy_exit();
#endif

    /* ???????????????????? */
    frw_set_init_state(FRW_INIT_STATE_START);

    /* ???????????????????? */

    return ;
}


oal_void  frw_set_init_state(frw_init_enum_uint16 en_init_state)
{
    if (en_init_state >= FRW_INIT_STATE_BUTT)
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_set_init_state:: en_init_state >= FRW_INIT_STATE_BUTT: %d}", en_init_state);
        return;
    }

    g_en_wlan_driver_init_state = en_init_state;

    return ;
}


frw_init_enum_uint16  frw_get_init_state(oal_void)
{
    return g_en_wlan_driver_init_state;
}


/*lint -e578*//*lint -e19*/
#if (_PRE_PRODUCT_ID_HI1151==_PRE_PRODUCT_ID)
oal_module_init(frw_main_init);
oal_module_exit(frw_main_exit);

#endif

oal_module_symbol(frw_main_init);
oal_module_symbol(frw_main_exit);

oal_module_symbol(frw_set_init_state);
oal_module_symbol(frw_get_init_state);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

