/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include <linux/slab.h>
#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/rtc.h>
#include <asm/string.h>
#include "drv_comm.h"
#include "osl_types.h"
#include "bsp_dump.h"
#include "bsp_slice.h"
#include "bsp_reset.h"
#include "bsp_coresight.h"
#include "bsp_wdt.h"
#include "gunas_errno.h"
#include "dump_modem.h"
#include "dump_modem_rdr.h"
#include "dump_config.h"
#include "dump_print.h"
#include "dump_modem_baseinfo.h"
#include "dump_cp_agent.h"
#include "dump_modem_hook.h"
#include "dump_modem_area.h"
#include "dump_modem_field.h"
#include "dump_cp_wdt.h"
#include "dump_modem_save.h"
#include "dump_exc_ctrl.h"


rdr_exc_info_s     g_rdr_exc_info;

struct rdr_exception_info_s g_phone_exc_info[] = {
    {
        .e_modid            = (unsigned int)RDR_MODEM_AP_MOD_ID,
        .e_modid_end        = (unsigned int)RDR_MODEM_AP_MOD_ID,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_CP | RDR_LPM3 ,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_DISALLOW,
        .e_exce_type        = CP_S_MODEMAP,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem ap reset system",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_MOD_ID,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_MOD_ID,
        .e_process_priority = RDR_WARN,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_CP| RDR_HIFI | RDR_LPM3,
        .e_reset_core_mask  = RDR_CP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_EXCEPTION,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem self-reset ipc",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_RESET_SIM_SWITCH_MOD_ID,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_RESET_SIM_SWITCH_MOD_ID,
        .e_process_priority = RDR_WARN,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = 0,
        .e_reset_core_mask  = RDR_CP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_NORMALRESET,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem reboot without log",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_RESET_FAIL_MOD_ID,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_RESET_FAIL_MOD_ID,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_CP | RDR_LPM3,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_DISALLOW,
        .e_exce_type        = CP_S_RESETFAIL,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem self-reset fail",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_WDT_MOD_ID,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_WDT_MOD_ID,
        .e_process_priority = RDR_WARN,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_CP | RDR_LPM3,
        .e_reset_core_mask  = RDR_CP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_EXCEPTION,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem self-reset wdt",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_RESET_RILD_MOD_ID,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_RESET_RILD_MOD_ID,
        .e_process_priority = RDR_WARN,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_CP | RDR_LPM3,
        .e_reset_core_mask  = RDR_CP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_RILD_EXCEPTION,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem reset by rild",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_RESET_3RD_MOD_ID,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_RESET_3RD_MOD_ID,
        .e_process_priority = RDR_WARN,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_CP | RDR_HIFI | RDR_LPM3,
        .e_reset_core_mask  = RDR_CP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_3RD_EXCEPTION,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem reset by 3rd modem",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_RESET_REBOOT_REQ_MOD_ID,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_RESET_REBOOT_REQ_MOD_ID,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_CP | RDR_LPM3 ,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_DISALLOW,
        .e_exce_type        = CP_S_NORMALRESET,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem reset stub",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_NOC_MOD_ID,
        .e_modid_end        = (unsigned int)RDR_MODEM_NOC_MOD_ID,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_CP| RDR_LPM3 ,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_DISALLOW,
        .e_exce_type        = CP_S_MODEMNOC,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem noc error",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_AP_NOC_MOD_ID,
        .e_modid_end        = (unsigned int)RDR_MODEM_AP_NOC_MOD_ID,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_CP| RDR_LPM3 ,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_DISALLOW,
        .e_exce_type        = CP_S_MODEMNOC,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem noc reset system",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_RESET_USER_RESET_MOD_ID,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_RESET_USER_RESET_MOD_ID,
        .e_process_priority = RDR_WARN,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = 0,
        .e_reset_core_mask  = RDR_CP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_NORMALRESET,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem user reset without log",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_DMSS_MOD_ID,
        .e_modid_end        = (unsigned int)RDR_MODEM_DMSS_MOD_ID,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_CP | RDR_LPM3 ,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_DISALLOW,
        .e_exce_type        = CP_S_MODEMDMSS,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem dmss error",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_RESET_DLOCK_MOD_ID,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_RESET_DLOCK_MOD_ID,
        .e_process_priority = RDR_WARN,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP |RDR_CP | RDR_LPM3,
        .e_reset_core_mask  = RDR_CP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_EXCEPTION,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP DLOCK",
        .e_desc             = "modem reset by bus error",
    },

};
struct rdr_exception_info_s g_mbb_exc_info[] =
{
    {
        .e_modid            = (unsigned int)RDR_MODEM_AP_MOD_ID,
        .e_modid_end        = (unsigned int)RDR_MODEM_AP_MOD_ID,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_CP | RDR_LPM3 ,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_AP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_DISALLOW,
        .e_exce_type        = CP_S_MODEMAP,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "MDMAP",
        .e_desc             = "modem ap reset system",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_DRV_MOD_ID_START,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_DRV_MOD_ID_END,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_LPM3,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_EXCEPTION,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP DRV",
        .e_desc             = "modem cp DRV reset",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_OSA_MOD_ID_START,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_OSA_MOD_ID_END,
        .e_process_priority = RDR_WARN,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_LPM3,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_EXCEPTION,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP OSA",
        .e_desc             = "modem cp OSA reset",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_OAM_MOD_ID_START,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_OAM_MOD_ID_END,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_LPM3,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_EXCEPTION,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP OAM",
        .e_desc             = "modem cp OAM reset",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_GUL2_MOD_ID_START,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_GUL2_MOD_ID_END,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_LPM3,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_EXCEPTION,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP GUL2",
        .e_desc             = "modem cp GUL2 reset",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_GUWAS_MOD_ID_START,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_GUWAS_MOD_ID_END,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_LPM3,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_EXCEPTION,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP GUWAS",
        .e_desc             = "modem cp GUWAS reset",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_GUGAS_MOD_ID_START,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_GUGAS_MOD_ID_END,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_LPM3,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_EXCEPTION,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP GUGAS",
        .e_desc             = "modem cp GUGAS reset",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_GUNAS_MOD_ID_START,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_GUNAS_MOD_ID_END,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_LPM3,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_EXCEPTION,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP GUNAS",
        .e_desc             = "modem cp GUNAS reset",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_GUDSP_MOD_ID_START,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_GUDSP_MOD_ID_END,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_LPM3,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_EXCEPTION,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP GUDSP",
        .e_desc             = "modem cp GUDSP reset",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_LPS_MOD_ID_START,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_LPS_MOD_ID_END,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_LPM3,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_EXCEPTION,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP LPS",
        .e_desc             = "modem cp LPS reset",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_LMSP_MOD_ID_START,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_LMSP_MOD_ID_END,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_LPM3,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_EXCEPTION,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP LMSP",
        .e_desc             = "modem cp LMSP reset",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_TLDSP_MOD_ID_START,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_TLDSP_MOD_ID_END,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_LPM3,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_EXCEPTION,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP TLDSP",
        .e_desc             = "modem cp TLDSP reset",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_WDT_MOD_ID,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_WDT_MOD_ID,
        .e_process_priority = RDR_WARN,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_CP | RDR_LPM3,
        .e_reset_core_mask  = RDR_CP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_EXCEPTION,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP WDT",
        .e_desc             = "modem self-reset wdt",
    },
    {
        .e_modid            = (unsigned int)RDR_MODEM_CP_RESET_DLOCK_MOD_ID,
        .e_modid_end        = (unsigned int)RDR_MODEM_CP_RESET_DLOCK_MOD_ID,
        .e_process_priority = RDR_WARN,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP |RDR_CP | RDR_LPM3,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = (unsigned int)RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_EXCEPTION,
        .e_upload_flag      = (unsigned int)RDR_UPLOAD_YES,
        .e_from_module      = "CP DLOCK",
        .e_desc             = "modem reset by bus error",
    },
};

/*****************************************************************************
* ?? ?? ??  : dump_save_balong_rdr_info
* ????????  : ????????????????rdr??global ??
*
* ????????  :
* ????????  :

* ?? ?? ??  :

*
* ????????  : 2016??1??4??17:05:33   lixiaofan  creat
*
*****************************************************************************/
void dump_save_balong_rdr_info(u32 mod_id)
{


}

/*****************************************************************************
* ?? ?? ??  : dump_save_modem_exc_info
* ????????  : ????rdr??????????
*
* ????????  :
* ????????  :

* ?? ?? ??  :

*
* ????????  : 2016??1??4??17:05:33   lixiaofan  creat
*
*****************************************************************************/
void dump_save_rdr_exc_info(u32 modid, u32 etype, u64 coreid, char* logpath, pfn_cb_dump_done fndone)
{

    g_rdr_exc_info.modid  = modid;
    g_rdr_exc_info.coreid = coreid;
    g_rdr_exc_info.dump_done = fndone;

    if((strlen(logpath) + strlen(RDR_DUMP_FILE_CP_PATH)) >= RDR_DUMP_FILE_PATH_LEN - 1)
    {
        dump_fetal("log path is too long %s\n", logpath);
        return ;
    }
    /*coverity[secure_coding]*/
    memset(g_rdr_exc_info.log_path,'\0',(unsigned long)RDR_DUMP_FILE_PATH_LEN);
    /*coverity[secure_coding]*/
    memcpy(g_rdr_exc_info.log_path, logpath, strlen(logpath));
    /*coverity[secure_coding]*/
    memcpy(g_rdr_exc_info.log_path + strlen(logpath) , RDR_DUMP_FILE_CP_PATH, strlen(RDR_DUMP_FILE_CP_PATH));

    dump_fetal("log path is %s\n", g_rdr_exc_info.log_path);

}
/*****************************************************************************
* ?? ?? ??  : modem_error_proc
* ????????  : modem????????????????????????dmss??noc????
*
* ????????  :
* ????????  :

* ?? ?? ??  :

*
* ????????  : 2016??1??4??17:05:33   lixiaofan  creat
*
*****************************************************************************/
void dump_callback_dmss_noc_proc(u32 modid)
{


}

/*****************************************************************************
* ?? ?? ??  : dump_callback
* ????????  : modem??????????????????
*
* ????????  :
* ????????  :

* ?? ?? ??  :

*
* ????????  : 2016??1??4??17:05:33   lixiaofan  creat
*
*****************************************************************************/
u32 dump_callback(u32 modid, u32 etype, u64 coreid, char* logpath, pfn_cb_dump_done fndone)
{

    fndone(modid,coreid);
    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : dump_reset_fail_proc
* ????????  : ??????????????????
*
* ????????  :
* ????????  :

* ?? ?? ??  :

*
* ????????  : 2016??1??4??17:05:33   lixiaofan  creat
*
*****************************************************************************/
void dump_reset_fail_proc(u32 rdr_modid)
{

    rdr_system_error(rdr_modid, 0, 0);
}

/*****************************************************************************
* ?? ?? ??  : dump_reset_success_proc
* ????????  : ????????????????
*
* ????????  :
* ????????  :

* ?? ?? ??  :

*
* ????????  : 2016??1??4??17:05:33   lixiaofan  creat
*
*****************************************************************************/
void dump_reset_success_proc(void)
{

}

/*****************************************************************************
* ?? ?? ??  : dump_reset
* ????????  : modem ????????????
*
* ????????  :
* ????????  :

* ?? ?? ??  :

*
* ????????  : 2016??1??4??17:05:33   lixiaofan  creat
*
*****************************************************************************/
void dump_reset(u32 modid, u32 etype, u64 coreid)
{
    s32 ret;
    dump_fetal("enter dump reset, mod id:0x%x\n", modid);

    if(DUMP_PHONE == dump_get_product_type())
    {
        if ((RDR_MODEM_AP_MOD_ID == modid)
            || (RDR_MODEM_CP_RESET_REBOOT_REQ_MOD_ID == modid))
        {
            return;
        }
        else if((RDR_MODEM_CP_MOD_ID == modid)
                || (RDR_MODEM_CP_WDT_MOD_ID == modid)
                || (RDR_MODEM_CP_RESET_SIM_SWITCH_MOD_ID == modid)
                || (RDR_MODEM_CP_RESET_RILD_MOD_ID == modid)
                || (RDR_MODEM_CP_RESET_3RD_MOD_ID == modid)
                || (RDR_MODEM_CP_RESET_USER_RESET_MOD_ID == modid)
                || (RDR_MODEM_CP_RESET_DLOCK_MOD_ID == modid))
        {
            ret = bsp_cp_reset();
            if(ret == -1)
            {
                dump_reset_fail_proc(RDR_MODEM_CP_RESET_REBOOT_REQ_MOD_ID);
                return;
            }

            if(!bsp_reset_is_successful(RDR_MODEM_CP_RESET_TIMEOUT))
            {
                dump_reset_fail_proc(RDR_MODEM_CP_RESET_FAIL_MOD_ID);
            }
            else
            {
                dump_reset_success_proc();
            }
        }
        else
        {
            dump_fetal("invalid mod id: 0x%x\n", modid);
        }
    }

}


/*****************************************************************************
* ?? ?? ??  : dump_register_rdr_exc
* ????????  : modem dump??????????????
*
* ????????  :
* ????????  :

* ?? ?? ??  :

*
* ????????  : 2016??1??4??17:05:33   lixiaofan  creat
*
*****************************************************************************/
s32 dump_register_rdr_exc(void)
{
    u32 i = 0;
    struct rdr_module_ops_pub soc_ops = {
    .ops_dump = NULL,
    .ops_reset = NULL
    };

    if(DUMP_PHONE == dump_get_product_type())
    {
        for(i=0; i<sizeof(g_phone_exc_info)/sizeof(struct rdr_exception_info_s); i++)
        {

            if(rdr_register_exception(&g_phone_exc_info[i]) == 0)
            {
                dump_fetal("dump init: rdr_register_exception 0x%x fail\n", g_phone_exc_info[i].e_modid);
                return BSP_ERROR;
            }
        }
    }
    else
    {
        for(i=0; i<sizeof(g_mbb_exc_info)/sizeof(struct rdr_exception_info_s); i++)
        {
            if(rdr_register_exception(&g_mbb_exc_info[i]) == 0)
            {
                dump_fetal("dump init: rdr_register_exception 0x%x fail\n", g_mbb_exc_info[i].e_modid);
                return BSP_ERROR;
            }
        }
    }


    soc_ops.ops_dump  = (pfn_dump)dump_callback;
    soc_ops.ops_reset = (pfn_reset)dump_reset;

    if(rdr_register_module_ops(RDR_CP, &soc_ops, &(g_rdr_exc_info.soc_rst)) != BSP_OK)
    {
        dump_fetal("dump init: rdr_register_soc_ops fail\n");
        return BSP_ERROR;
    }

    g_rdr_exc_info.dump_done = NULL;

    return BSP_OK;

}
/*****************************************************************************
* ?? ?? ??  : dump_get_rdr_exc_info
* ????????  : ????rdr??????????????
*
* ????????  :
* ????????  :

* ?? ?? ??  :

*
* ????????  : 2016??1??4??17:05:33   lixiaofan  creat
*
*****************************************************************************/

rdr_exc_info_s* dump_get_rdr_exc_info(void)
{
    return &g_rdr_exc_info;
}

/*****************************************************************************
* ?? ?? ??  : dump_match_rdr_mod_id
* ????????  : ??drv??????????????rdr????????
*
* ????????  :
* ????????  :

* ?? ?? ??  :

*
* ????????  : 2016??1??4??17:05:33   lixiaofan  creat
*
*****************************************************************************/
u32 dump_match_rdr_mod_id(u32 drv_mod_id)
{
    u32 rdr_mod_id = RDR_MODEM_AP_MOD_ID;

    if(DUMP_PHONE == dump_get_product_type())
    {
        switch(drv_mod_id)
        {
        case DRV_ERRNO_RESET_SIM_SWITCH:
            rdr_mod_id = RDR_MODEM_CP_RESET_SIM_SWITCH_MOD_ID;
            return rdr_mod_id;
        case NAS_REBOOT_MOD_ID_RILD:
            rdr_mod_id = RDR_MODEM_CP_RESET_RILD_MOD_ID;
            return rdr_mod_id;
        case DRV_ERRNO_RESET_3RD_MODEM:
            rdr_mod_id = RDR_MODEM_CP_RESET_3RD_MOD_ID;
            return rdr_mod_id;
        case DRV_ERRNO_RESET_REBOOT_REQ:
            rdr_mod_id = RDR_MODEM_CP_RESET_REBOOT_REQ_MOD_ID;
            return rdr_mod_id;
        case DRV_ERROR_USER_RESET:
            rdr_mod_id = RDR_MODEM_CP_RESET_USER_RESET_MOD_ID;
            return rdr_mod_id;
        case DRV_ERRNO_DLOCK:
            rdr_mod_id = RDR_MODEM_CP_RESET_DLOCK_MOD_ID;
            return rdr_mod_id;
        default:
            break;
        }
    }

    if((DRV_ERRNO_DUMP_CP_WDT == drv_mod_id))
    {
        rdr_mod_id = RDR_MODEM_CP_WDT_MOD_ID;
    }
    else if((DRV_ERRNO_DLOCK == drv_mod_id))
    {
        rdr_mod_id = RDR_MODEM_CP_RESET_DLOCK_MOD_ID;
    }
    else
    {
        rdr_mod_id = RDR_MODEM_AP_MOD_ID;
    }

    return rdr_mod_id;

}

