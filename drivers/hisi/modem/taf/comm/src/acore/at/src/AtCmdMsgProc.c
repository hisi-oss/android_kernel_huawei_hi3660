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
 
/*****************************************************************************
   1 ??????????
*****************************************************************************/
#include "ATCmdProc.h"
#include "siapppb.h"
#include "siappstk.h"
#include "AtMsgPrint.h"
#include "mdrv.h"
#include "AtPhyInterface.h"
#include "PppInterface.h"
#include "AtDataProc.h"
#include "AtCmdMsgProc.h"
#include "TafDrvAgent.h"
#include "AtCmdMsgProc.h"
#include "AtEventReport.h"
#include "AtRabmInterface.h"
#include "AtRnicInterface.h"
#include "AtDeviceCmd.h"
#include "AtInit.h"
#include "at_common.h"
#include "AcpuReset.h"

#include "AtInternalMsg.h"

#include "msp_nvim.h"

#include "LPsNvInterface.h"
#include "LNvCommon.h"
#include "at_lte_common.h"

#include "OmApi.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "GasNvInterface.h"
#include "AppVcApi.h"

#include "AtCmdImsProc.h"

#include  "product_config.h"

#include "AtCmdCallProc.h"

#include  "AtCmdFtmProc.h"

#include "AtCmdMiscProc.h"

#include "AtCmdCagpsProc.h"
#include "AtCmdCssProc.h"


#include "mdrv.h"
#include "TafAppCall.h"
#include "AtEventReport.h"

#include "AtCmdSupsProc.h"

#include "AtCtx.h"



/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_AT_CMDMSGPROC_C


/*****************************************************************************
  2 ????????
*****************************************************************************/

/*****************************************************************************
   3 ????????????
*****************************************************************************/

/* Added by L60609 for AT Project??2011-10-04,  Begin*/

/*AT ????????????AT AGENT??????????????*/
const AT_PROC_MSG_FROM_DRV_AGENT_STRU g_astAtProcMsgFromDrvAgentTab[]=
{
    /* ????ID */                            /* ???????????? */
    {DRV_AGENT_MSID_QRY_CNF,                AT_RcvDrvAgentMsidQryCnf},
    {DRV_AGENT_GAS_MNTN_CMD_RSP,            AT_RcvDrvAgentGasMntnCmdRsp},
    {DRV_AGENT_HARDWARE_QRY_RSP,            AT_RcvDrvAgentHardwareQryRsp},
    {DRV_AGENT_FULL_HARDWARE_QRY_RSP,       AT_RcvDrvAgentFullHardwareQryRsp},
    {DRV_AGENT_RXDIV_SET_CNF,               AT_RcvDrvAgentSetRxdivCnf},
    {DRV_AGENT_RXDIV_QRY_CNF,               AT_RcvDrvAgentQryRxdivCnf},
    {DRV_AGENT_SIMLOCK_SET_CNF,             AT_RcvDrvAgentSetSimlockCnf},


    {DRV_AGENT_VERTIME_QRY_CNF,             AT_RcvDrvAgentVertimeQryRsp},
    {DRV_AGENT_YJCX_SET_CNF,                AT_RcvDrvAgentYjcxSetCnf},
    {DRV_AGENT_YJCX_QRY_CNF,                AT_RcvDrvAgentYjcxQryCnf},
    {DRV_AGENT_GPIOPL_SET_CNF,              AT_RcvDrvAgentSetGpioplRsp},
    {DRV_AGENT_GPIOPL_QRY_CNF,              AT_RcvDrvAgentQryGpioplRsp},
    {DRV_AGENT_DATALOCK_SET_CNF,            AT_RcvDrvAgentSetDatalockRsp},
    {DRV_AGENT_TBATVOLT_QRY_CNF,            AT_RcvDrvAgentQryTbatvoltRsp},
    {DRV_AGENT_VERSION_QRY_CNF,             AT_RcvDrvAgentQryVersionRsp},
    {DRV_AGENT_FCHAN_SET_CNF,               AT_RcvDrvAgentSetFchanRsp},
    {DRV_AGENT_SFEATURE_QRY_CNF,            AT_RcvDrvAgentQrySfeatureRsp},
    {DRV_AGENT_PRODTYPE_QRY_CNF,            AT_RcvDrvAgentQryProdtypeRsp},

    /* Added by ??????/f62575 for CPULOAD&MFREELOCKSIZE????????????C??, 2011/11/15, begin */
    {DRV_AGENT_CPULOAD_QRY_CNF,             AT_RcvDrvAgentCpuloadQryRsp},
    {DRV_AGENT_MFREELOCKSIZE_QRY_CNF,       AT_RcvDrvAgentMfreelocksizeQryRsp},
    /* Added by ??????/f62575 for CPULOAD&MFREELOCKSIZE????????????C??, 2011/11/15, end */
    {DRV_AGENT_MEMINFO_QRY_CNF,             AT_RcvDrvAgentMemInfoQryRsp},
    /* Added by f62575 for AT Project, 2011-10-04,  Begin */
    {DRV_AGENT_DLOADINFO_QRY_CNF,           AT_RcvDrvAgentDloadInfoQryRsp},
    {DRV_AGENT_FLASHINFO_QRY_CNF,           AT_RcvDrvAgentFlashInfoQryRsp},
    {DRV_AGENT_AUTHORITYVER_QRY_CNF,        AT_RcvDrvAgentAuthorityVerQryRsp},
    {DRV_AGENT_AUTHORITYID_QRY_CNF,         AT_RcvDrvAgentAuthorityIdQryRsp},
    {DRV_AGENT_AUTHVER_QRY_CNF,             AT_RcvDrvAgentAuthVerQryRsp},
    {DRV_AGENT_GODLOAD_SET_CNF,             AT_RcvDrvAgentGodloadSetRsp},

    {DRV_AGENT_PFVER_QRY_CNF,               AT_RcvDrvAgentPfverQryRsp},
    {DRV_AGENT_HWNATQRY_QRY_CNF,            AT_RcvDrvAgentHwnatQryRsp},
    {DRV_AGENT_SDLOAD_SET_CNF,              AT_RcvDrvAgentSdloadSetRsp},
    {DRV_AGENT_APPDMVER_QRY_CNF,            AT_RcvDrvAgentAppdmverQryRsp},
    {DRV_AGENT_DLOADVER_QRY_CNF,            AT_RcvDrvAgentDloadverQryRsp},
    /* Added by f62575 for AT Project, 2011-10-04,  End */

    /* Added by l60609 for AT Project, 2011-11-03,  Begin */
    {DRV_AGENT_IMSICHG_QRY_CNF,             AT_RcvDrvAgentImsiChgQryRsp},
    {DRV_AGENT_INFORBU_SET_CNF,             AT_RcvDrvAgentInfoRbuSetRsp},
    {DRV_AGENT_INFORRS_SET_CNF,             AT_RcvDrvAgentInfoRrsSetRsp},
    {DRV_AGENT_CPNN_QRY_CNF,                AT_RcvDrvAgentCpnnQryRsp},
    {DRV_AGENT_CPNN_TEST_CNF,               AT_RcvDrvAgentCpnnTestRsp},
    {DRV_AGENT_NVBACKUP_SET_CNF,            AT_RcvDrvAgentNvBackupSetRsp},
    /* Added by l60609 for AT Project, 2011-11-03,  Begin */

    {DRV_AGENT_NVRESTORE_SET_CNF,           AT_RcvDrvAgentSetNvRestoreCnf},
    {DRV_AGENT_NVRSTSTTS_QRY_CNF,           AT_RcvDrvAgentQryNvRestoreRstCnf},
    {DRV_AGENT_NVRESTORE_MANU_DEFAULT_CNF,  AT_RcvDrvAgentNvRestoreManuDefaultRsp},

    {DRV_AGENT_ADC_SET_CNF,                 AT_RcvDrvAgentSetAdcRsp},
    /* Added by f62575 for SMALL IMAGE, 2012-1-3, Begin   */
    {DRV_AGENT_TSELRF_SET_CNF,              AT_RcvDrvAgentTseLrfSetRsp},
    {DRV_AGENT_HKADC_GET_CNF,               AT_RcvDrvAgentHkAdcGetRsp},
    /* Added by f62575 for SMALL IMAGE, 2012-1-3, end   */

    {DRV_AGENT_TBAT_QRY_CNF,                AT_RcvDrvAgentQryTbatRsp},
    /* Added by l60609 for B060 Project, 2012-2-21, Begin   */
    {DRV_AGENT_SPWORD_SET_CNF,              AT_RcvDrvAgentSetSpwordRsp},
    /* Added by l60609 for B060 Project, 2012-2-21, End   */

    {DRV_AGENT_NVBACKUPSTAT_QRY_CNF,        AT_RcvDrvAgentNvBackupStatQryRsp},
    {DRV_AGENT_NANDBBC_QRY_CNF,             AT_RcvDrvAgentNandBadBlockQryRsp},
    {DRV_AGENT_NANDVER_QRY_CNF,             AT_RcvDrvAgentNandDevInfoQryRsp},
    {DRV_AGENT_CHIPTEMP_QRY_CNF,            AT_RcvDrvAgentChipTempQryRsp},

    /* Added by h59254 for C50 SAR Project, 2012/03/10, begin */
    {DRV_AGENT_ANTSTATE_QRY_IND,            AT_RcvDrvAgentAntStateIndRsp},
    /* Added by h59254 for C50 SAR Project, 2012/03/10, end */

    {DRV_AGENT_MAX_LOCK_TIMES_SET_CNF,      AT_RcvDrvAgentSetMaxLockTmsRsp},

    {DRV_AGENT_AP_SIMST_SET_CNF,            AT_RcvDrvAgentSetApSimstRsp},

    {DRV_AGENT_HUK_SET_CNF,                 AT_RcvDrvAgentHukSetCnf},
    {DRV_AGENT_FACAUTHPUBKEY_SET_CNF,       AT_RcvDrvAgentFacAuthPubkeySetCnf},
    {DRV_AGENT_IDENTIFYSTART_SET_CNF,       AT_RcvDrvAgentIdentifyStartSetCnf},
    {DRV_AGENT_IDENTIFYEND_SET_CNF,         AT_RcvDrvAgentIdentifyEndSetCnf},
    {DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF,    AT_RcvDrvAgentSimlockDataWriteSetCnf},
    {DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF,    AT_RcvDrvAgentPhoneSimlockInfoQryCnf},
    {DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF,     AT_RcvDrvAgentSimlockDataReadQryCnf},
    {DRV_AGENT_PHONEPHYNUM_SET_CNF,         AT_RcvDrvAgentPhonePhynumSetCnf},
    {DRV_AGENT_PHONEPHYNUM_QRY_CNF,         AT_RcvDrvAgentPhonePhynumQryCnf},
    {DRV_AGENT_PORTCTRLTMP_SET_CNF,         AT_RcvDrvAgentPortctrlTmpSetCnf},
    {DRV_AGENT_PORTATTRIBSET_SET_CNF,       AT_RcvDrvAgentPortAttribSetCnf},
    {DRV_AGENT_PORTATTRIBSET_QRY_CNF,       AT_RcvDrvAgentPortAttribSetQryCnf},
    {DRV_AGENT_OPWORD_SET_CNF,              AT_RcvDrvAgentOpwordSetCnf},

    {DRV_AGENT_SWVER_SET_CNF,               AT_RcvDrvAgentSwverSetCnf},



    {DRV_AGENT_NVMANUFACTUREEXT_SET_CNF,    AT_RcvNvManufactureExtSetCnf},

    {DRV_AGENT_ANTSWITCH_SET_CNF,           AT_RcvDrvAgentAntSwitchSetCnf},
    {DRV_AGENT_ANTSWITCH_QRY_CNF,           AT_RcvDrvAgentAntSwitchQryCnf},

    {DRV_AGENT_QRY_CCPU_MEM_INFO_CNF,       AT_RcvDrvAgentQryCcpuMemInfoCnf},

};

/* Added by L60609 for AT Project??2011-10-04,  End*/

/* AT????????????MTA??????????????*/
const AT_PROC_MSG_FROM_MTA_STRU g_astAtProcMsgFromMtaTab[]=
{
    /* ????ID */                            /* ???????????? */
    {ID_MTA_AT_CPOS_SET_CNF,                AT_RcvMtaCposSetCnf},
    {ID_MTA_AT_CPOSR_IND,                   AT_RcvMtaCposrInd},
    {ID_MTA_AT_XCPOSRRPT_IND,               AT_RcvMtaXcposrRptInd},
    {ID_MTA_AT_CGPSCLOCK_SET_CNF,           AT_RcvMtaCgpsClockSetCnf},

    {ID_MTA_AT_SIMLOCKUNLOCK_SET_CNF,       AT_RcvMtaSimlockUnlockSetCnf},

    {ID_MTA_AT_QRY_NMR_CNF,                 AT_RcvMtaQryNmrCnf},

    {ID_MTA_AT_WRR_AUTOTEST_QRY_CNF,        AT_RcvMtaWrrAutotestQryCnf},
    {ID_MTA_AT_WRR_CELLINFO_QRY_CNF,        AT_RcvMtaWrrCellinfoQryCnf},
    {ID_MTA_AT_WRR_MEANRPT_QRY_CNF,         AT_RcvMtaWrrMeanrptQryCnf},
    {ID_MTA_AT_WRR_FREQLOCK_SET_CNF,        AT_RcvMtaWrrFreqLockSetCnf},
    {ID_MTA_AT_WRR_RRC_VERSION_SET_CNF,     AT_RcvMtaWrrRrcVersionSetCnf},
    {ID_MTA_AT_WRR_CELLSRH_SET_CNF,         AT_RcvMtaWrrCellSrhSetCnf},
    {ID_MTA_AT_WRR_FREQLOCK_QRY_CNF,        AT_RcvMtaWrrFreqLockQryCnf},
    {ID_MTA_AT_WRR_RRC_VERSION_QRY_CNF,     AT_RcvMtaWrrRrcVersionQryCnf},
    {ID_MTA_AT_WRR_CELLSRH_QRY_CNF,         AT_RcvMtaWrrCellSrhQryCnf},

    {ID_MTA_AT_BODY_SAR_SET_CNF,           AT_RcvMtaBodySarSetCnf},

    {ID_MTA_AT_CURC_QRY_CNF,                AT_RcvMtaQryCurcCnf},
    {ID_MTA_AT_UNSOLICITED_RPT_SET_CNF,     AT_RcvMtaSetUnsolicitedRptCnf},
    {ID_MTA_AT_UNSOLICITED_RPT_QRY_CNF,     AT_RcvMtaQryUnsolicitedRptCnf},

    {ID_MTA_AT_IMEI_VERIFY_QRY_CNF,         AT_RcvMtaImeiVerifyQryCnf},
    {ID_MTA_AT_CGSN_QRY_CNF,                AT_RcvMtaCgsnQryCnf},
    {ID_MTA_AT_NCELL_MONITOR_SET_CNF,       AT_RcvMtaSetNCellMonitorCnf},
    {ID_MTA_AT_NCELL_MONITOR_QRY_CNF,       AT_RcvMtaQryNCellMonitorCnf},
    {ID_MTA_AT_NCELL_MONITOR_IND,           AT_RcvMtaNCellMonitorInd},

    {ID_MTA_AT_REFCLKFREQ_SET_CNF,          AT_RcvMtaRefclkfreqSetCnf},
    {ID_MTA_AT_REFCLKFREQ_QRY_CNF,          AT_RcvMtaRefclkfreqQryCnf},
    {ID_MTA_AT_REFCLKFREQ_IND,              AT_RcvMtaRefclkfreqInd},

    {ID_MTA_AT_RFICSSIRD_QRY_CNF,           AT_RcvMtaRficSsiRdQryCnf},

    {ID_MTA_AT_HANDLEDECT_SET_CNF,          AT_RcvMtaHandleDectSetCnf},
    {ID_MTA_AT_HANDLEDECT_QRY_CNF,          AT_RcvMtaHandleDectQryCnf},

    {ID_MTA_AT_PS_TRANSFER_IND,             AT_RcvMtaPsTransferInd},

    {ID_MTA_AT_RRC_PROTECT_PS_CNF,          AT_RcvMtaPsProtectSetCnf},
    { ID_MTA_AT_PHY_INIT_CNF,               AT_RcvMtaPhyInitCnf},

    {ID_MTA_AT_ECID_SET_CNF,                AT_RcvMtaEcidSetCnf},

    {ID_MTA_AT_MIPICLK_QRY_CNF,             AT_RcvMtaMipiInfoCnf},
    {ID_MTA_AT_MIPICLK_INFO_IND,            AT_RcvMtaMipiInfoInd},
    {ID_MTA_AT_SET_DPDTTEST_FLAG_CNF,       AT_RcvMtaSetDpdtTestFlagCnf},
    {ID_MTA_AT_SET_DPDT_VALUE_CNF,          AT_RcvMtaSetDpdtValueCnf},
    {ID_MTA_AT_QRY_DPDT_VALUE_CNF,          AT_RcvMtaQryDpdtValueCnf},

    {ID_MTA_AT_SET_JAM_DETECT_CNF,          AT_RcvMtaSetJamDetectCnf},
    {ID_MTA_AT_JAM_DETECT_IND,              AT_RcvMtaJamDetectInd},

    {ID_MTA_AT_SET_FREQ_LOCK_CNF,           AT_RcvMtaSetRatFreqLockCnf},

    {ID_MTA_AT_SET_GSM_FREQLOCK_CNF,        AT_RcvMtaSetGFreqLockCnf},
    {ID_MTA_AT_SET_M2M_FREQLOCK_CNF,        AT_RcvMtaSetM2MFreqLockCnf},
    {ID_MTA_AT_QRY_M2M_FREQLOCK_CNF,        AT_RcvMtaQryM2MFreqLockCnf},
    {ID_MTA_AT_XPASS_INFO_IND,              AT_RcvMtaXpassInfoInd},

    {ID_AT_MTA_SET_FEMCTRL_CNF,             AT_RcvMtaSetFemctrlCnf},

    {ID_MTA_AT_NVWRSECCTRL_SET_CNF,         AT_RcvMtaNvwrSecCtrlSetCnf},

    {ID_MTA_AT_LTE_LOW_POWER_SET_CNF,           AT_RcvMtaLteLowPowerSetCnf},
    {ID_MTA_AT_LTE_WIFI_COEX_SET_CNF,           AT_RcvMtaIsmCoexSetCnf},
    {ID_MTA_AT_LTE_WIFI_COEX_QRY_CNF,           AT_RcvMtaIsmCoexQryCnf},

    {ID_MTA_AT_SET_FR_CNF,                  AT_RcvMtaSetFrCnf},

    {ID_MTA_AT_SIB16_TIME_UPDATE_IND,       AT_RcvMtaSib16TimeUpdateInd},

    {ID_MTA_AT_MEID_SET_CNF,                AT_RcvMtaMeidSetCnf},
    {ID_MTA_AT_MEID_QRY_CNF,                AT_RcvMtaMeidQryCnf},

    {ID_MTA_AT_EVDO_SYS_EVENT_CNF,          AT_RcvMtaEvdoSysEventSetCnf},
    {ID_MTA_AT_EVDO_SIG_MASK_CNF,           AT_RcvMtaEvdoSigMaskSetCnf},
    {ID_MTA_AT_EVDO_REVA_RLINK_INFO_IND,    AT_RcvMtaEvdoRevARLinkInfoInd},
    {ID_MTA_AT_EVDO_SIG_EXEVENT_IND,        AT_RcvMtaEvdoSigExEventInd},

    {ID_MTA_AT_TRANSMODE_QRY_CNF,           AT_RcvMtaTransModeQryCnf},

    {ID_MTA_AT_UE_CENTER_SET_CNF,           AT_RcvMtaUECenterSetCnf},
    {ID_MTA_AT_UE_CENTER_QRY_CNF,           AT_RcvMtaUECenterQryCnf},
    {ID_MTA_AT_SET_NETMON_SCELL_CNF,        AT_RcvMtaSetNetMonSCellCnf},
    {ID_MTA_AT_SET_NETMON_NCELL_CNF,        AT_RcvMtaSetNetMonNCellCnf},

    {ID_MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF, AT_RcvMtaAfcClkInfoCnf},
    {ID_MTA_AT_ANQUERY_QRY_CNF,             AT_RcvMtaAnqueryQryCnf},
    {ID_MTA_AT_CSNR_QRY_CNF,                AT_RcvMtaCsnrQryCnf},
    {ID_MTA_AT_CSQLVL_QRY_CNF,              AT_RcvMtaCsqlvlQryCnf},
    {ID_MTA_AT_XCPOSR_SET_CNF,              AT_RcvMtaSetXCposrCnf},
    {ID_MTA_AT_XCPOSR_QRY_CNF,              AT_RcvMtaQryXcposrCnf},
    {ID_MTA_AT_XCPOSRRPT_SET_CNF,           AT_RcvMtaSetXcposrRptCnf},
    {ID_MTA_AT_XCPOSRRPT_QRY_CNF,           AT_RcvMtaQryXcposrRptCnf},
    {ID_MTA_AT_CLEAR_HISTORY_FREQ_CNF,      AT_RcvMtaClearHistoryFreqCnf},
    {ID_MTA_AT_SET_SENSOR_CNF,              AT_RcvMtaSetSensorCnf},
    {ID_MTA_AT_SET_SCREEN_CNF,              AT_RcvMtaSetScreenCnf},
    {ID_MTA_AT_FRAT_IGNITION_QRY_CNF,       AT_RcvFratIgnitionQryCnf},
    {ID_MTA_AT_FRAT_IGNITION_SET_CNF,       AT_RcvFratIgnitionSetCnf},

    {ID_MTA_AT_SET_MODEM_TIME_CNF,          AT_RcvMtaSetModemTimeCnf},

    {ID_MTA_AT_RX_TEST_MODE_SET_CNF,        AT_RcvMtaSetRxTestModeCnf},

    {ID_MTA_AT_AFC_CLK_UNLOCK_CAUSE_IND,    AT_RcvMtaAfcClkUnlockCauseInd},

    {ID_MTA_AT_SLAVE_SET_CNF,               AT_RcvMtaSetSlaveCnf},

    {ID_MTA_AT_BESTFREQ_SET_CNF,            AT_RcvMtaSetBestFreqCnf},
    {ID_MTA_AT_BEST_FREQ_INFO_IND,          AT_RcvMtaBestFreqInfoInd},
    {ID_MTA_AT_BESTFREQ_QRY_CNF,            AT_RcvMtaQryBestFreqCnf},

    {ID_MTA_AT_RFIC_DIE_ID_QRY_CNF,         AT_RcvMtaRficDieIDQryCnf},

    {ID_MTA_AT_MIPI_WREX_CNF,               AT_RcvMtaMipiWrEXCnf},
    {ID_MTA_AT_MIPI_RDEX_CNF,               AT_RcvMtaMipiRdEXCnf},

    {ID_MTA_AT_PHY_COM_CFG_SET_CNF,         AT_RcvMtaPhyComCfgSetCnf},

    {ID_MTA_AT_CRRCONN_SET_CNF,             AT_RcvMtaSetCrrconnCnf},
    {ID_MTA_AT_CRRCONN_QRY_CNF,             AT_RcvMtaQryCrrconnCnf},
    {ID_MTA_AT_CRRCONN_STATUS_IND,          AT_RcvMtaCrrconnStatusInd},
    {ID_MTA_AT_VTRLQUALRPT_SET_CNF,         AT_RcvMtaSetVtrlqualrptCnf},
    {ID_MTA_AT_RL_QUALITY_INFO_IND,         AT_RcvMtaRlQualityInfoInd},
    {ID_MTA_AT_VIDEO_DIAG_INFO_RPT,         AT_RcvMtaVideoDiagInfoRpt},

    {ID_MTA_AT_PMU_DIE_SN_QRY_CNF,          AT_RcvMtaPmuDieSNQryCnf},

    {ID_MTA_AT_MODEM_CAP_UPDATE_CNF,        AT_RcvMtaModemCapUpdateCnf},

    {ID_MTA_AT_TAS_TEST_CFG_CNF,            AT_RcvMtaTasTestCfgCnf},
    {ID_MTA_AT_TAS_TEST_QRY_CNF,            AT_RcvMtaTasTestQryCnf},

    {ID_MTA_AT_LTE_CATEGORY_INFO_IND,       AT_RcvMtaLteCategoryInfoInd},

    {ID_MTA_AT_ACCESS_STRATUM_REL_IND,      AT_RcvMtaAccessStratumRelInd},

    {ID_MTA_AT_RS_INFO_QRY_CNF,             AT_RcvMtaRsInfoQryCnf},

};

const AT_PROC_MSG_FROM_XPDS_STRU g_astAtProcMsgFromXpdsTab[]=
{
    {ID_XPDS_AT_GPS_START_CNF,                    AT_RcvXpdsCagpsRlstCnf},
    {ID_XPDS_AT_GPS_CFG_MPC_ADDR_CNF,             AT_RcvXpdsCagpsRlstCnf},
    {ID_XPDS_AT_GPS_CFG_PDE_ADDR_CNF,             AT_RcvXpdsCagpsRlstCnf},
    {ID_XPDS_AT_GPS_CFG_MODE_CNF,                 AT_RcvXpdsCagpsRlstCnf},
    {ID_XPDS_AT_GPS_STOP_CNF,                     AT_RcvXpdsCagpsRlstCnf},

    {ID_XPDS_AT_GPS_TIME_INFO_IND,                AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_REFLOC_INFO_CNF,              AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_PDE_POSI_INFO_IND,            AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_NI_SESSION_IND,               AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_START_REQ,                    AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_CANCEL_IND,                   AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_ACQ_ASSIST_DATA_IND,          AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_ABORT_IND,                    AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_DEL_ASSIST_DATA_IND,          AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_ION_INFO_IND,                 AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_EPH_INFO_IND,                 AT_RcvXpdsEphInfoInd},
    {ID_XPDS_AT_GPS_ALM_INFO_IND,                 AT_RcvXpdsAlmInfoInd},
    {ID_XPDS_AT_GPS_NI_CP_STOP,                   AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_NI_CP_START,                  AT_RcvXpdsCagpsCnf},

    {ID_XPDS_AT_AP_DATA_CALL_REQ,                 AT_RcvXpdsAgpsDataCallReq},
    {ID_XPDS_AT_AP_SERVER_BIND_REQ,               AT_RcvXpdsAgpsServerBindReq},
    {ID_XPDS_AT_AP_REVERSE_DATA_IND,              AT_RcvXpdsAgpsReverseDataInd},

    {ID_XPDS_AT_GPS_UTS_TEST_START_REQ,           AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_UTS_TEST_STOP_REQ,            AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_UTS_GPS_POS_INFO_IND,             AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_OM_TEST_START_REQ,            AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_OM_TEST_STOP_REQ,             AT_RcvXpdsCagpsCnf},
};

const AT_PROC_MSG_FROM_CALL_STRU g_astAtProcMsgFromCallTab[]=
{
    {ID_TAF_CALL_APP_ENCRYPT_VOICE_CNF,                     AT_RcvXcallEncryptCallCnf},
    {ID_TAF_CALL_APP_ENCRYPT_VOICE_IND,                     AT_RcvXcallEncryptCallInd},
    {ID_TAF_CALL_APP_EC_REMOTE_CTRL_IND,                    AT_RcvXcallEccRemoteCtrlInd},
    {ID_TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF,                AT_RcvXcallRemoteCtrlAnsCnf},
    {ID_TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF,                   AT_RcvXcallEccCapSetCnf},
    {ID_TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF,                   AT_RcvXcallEccCapQryCnf},
    {ID_TAF_CALL_APP_PRIVACY_MODE_SET_CNF,                  AT_RcvXcallPrivacyModeSetCnf},
    {ID_TAF_CALL_APP_PRIVACY_MODE_QRY_CNF,                  AT_RcvXcallPrivacyModeQryCnf},
    {ID_TAF_CALL_APP_PRIVACY_MODE_IND,                      AT_RcvXcallPrivacyModeInd},
    {ID_TAF_CALL_APP_CNAP_INFO_IND,                         AT_RcvTafCallCnapInfoInd},
    {ID_TAF_CALL_APP_CNAP_QRY_CNF,                          AT_RcvTafCallCnapQryCnf},
};

const AT_PROC_MSG_FROM_MMA_STRU g_astAtProcMsgFromMmaTab[]=
{
    /* ????ID */                            /* ???????????? */
    {ID_TAF_MMA_OM_MAINTAIN_INFO_IND,   AT_RcvMmaOmMaintainInfoInd},

    {ID_TAF_MMA_USIM_STATUS_IND,            AT_RcvAtMmaUsimStatusInd},
    {ID_TAF_MMA_CMM_SET_CNF,            AT_RcvMmaCmmSetCmdRsp},
    {ID_TAF_MMA_SIMLOCK_STAUS_QUERY_CNF, AT_RcvSimLockQryRsp},
/* Modified by k902809 for Iteration 11, 2015-3-23, begin */
    {ID_TAF_MMA_AC_INFO_QRY_CNF,        AT_RcvMmaAcInfoQueryCnf},
    {ID_TAF_MMA_AC_INFO_CHANGE_IND,     AT_RcvMmaAcInfoChangeInd},
/* Modified by k902809 for Iteration 11, Iteration 11 2015-3-23, end */
    /* Added by k902809 for Iteration 11, 2015-3-25, begin */
    {ID_TAF_MMA_EOPLMN_SET_CNF,         AT_RcvMmaEOPlmnSetCnf},
    {ID_TAF_MMA_NET_SCAN_CNF,           AT_RcvMmaNetScanCnf},
    {ID_TAF_MMA_USER_SRV_STATE_QRY_CNF,   AT_RcvMmaUserSrvStateQryCnf},
    {ID_TAF_MMA_POWER_ON_AND_REG_TIME_QRY_CNF,     AT_RcvMmaPwrOnAndRegTimeQryCnf},
    {ID_TAF_MMA_SPN_QRY_CNF,            AT_RcvMmaSpnQryCnf},
    {ID_TAF_MMA_MMPLMNINFO_QRY_CNF,     AT_RcvMmaMMPlmnInfoQryCnf},
    {ID_TAF_MMA_LAST_CAMP_PLMN_QRY_CNF,           AT_RcvMmaPlmnQryCnf},
    {ID_TAF_MMA_EOPLMN_QRY_CNF,         AT_RcvMmaEOPlmnQryCnf},
    /* Added by k902809 for Iteration 11, Iteration 11 2015-3-25, end */
    {ID_TAF_MMA_COPN_INFO_QRY_CNF,      AT_RcvMmaCopnInfoQueryCnf},
    /* Modified by k902809 for Iteration 11, 2015-3-24, begin */
    {ID_TAF_MMA_SIM_INSERT_CNF,          AT_RcvMmaSimInsertRsp},
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-24, end */
    {ID_TAF_MMA_SYS_CFG_SET_CNF,        AT_RcvMmaSysCfgSetCnf},
    {ID_TAF_MMA_PHONE_MODE_SET_CNF,     AT_RcvMmaPhoneModeSetCnf},
    {ID_TAF_MMA_DETACH_CNF,             AT_RcvMmaDetachCnf},
    {ID_TAF_MMA_ATTACH_CNF,             AT_RcvMmaAttachCnf},
    {ID_TAF_MMA_ATTACH_STATUS_QRY_CNF,  AT_RcvMmaAttachStatusQryCnf},

    /* Modified by k902809 for Iteration 11, 2015-3-25, begin */
    {ID_TAF_MMA_CDMA_LOCINFO_QRY_CNF,   AT_RcvMmaCLocInfoQueryCnf},
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-25, end */
    {ID_TAF_MMA_CSID_IND,               AT_RcvMmaCSidInd},

    {ID_TAF_MMA_1X_EMC_CALL_BACK_NTF,   AT_RcvMmaEmcCallBackNtf},
    {ID_TAF_MMA_QUIT_CALLBACK_SET_CNF,  AT_RcvMmaQuitCallBackCnf},
    {ID_TAF_MMA_CSIDLIST_SET_CNF,       AT_RcvMmaSetCSidListCnf},
    {ID_TAF_MMA_1X_EMC_CALL_BACK_QRY_CNF,  AT_RcvMmaQryEmcCallBackCnf},
    {ID_TAF_MMA_CURR_SID_NID_QRY_CNF,   AT_RcvMmaQryCurrSidNidCnf},

    {ID_TAF_MMA_CLOCINFO_IND,           AT_RcvMmaClocinfoInd},
    {ID_TAF_MMA_ROAMING_MODE_SWITCH_IND,       AT_RcvMmaRoamingModeSwitchInd},
    {ID_TAF_MMA_CTCC_ROAMING_NW_INFO_QRY_CNF,    AT_RcvMmaCtRoamInfoCnf},
    {ID_TAF_MMA_CTCC_ROAMING_NW_INFO_REPORT_IND, AT_RcvMmaCtRoamingInfoChgInd},
    {ID_TAF_MMA_CTCC_OOS_COUNT_SET_CNF, AT_RcvMmaCtOosCountCnf},
    {ID_TAF_MMA_CTCC_ROAMING_NW_INFO_RTP_CFG_SET_CNF, AT_RcvMmaCtRoamRptCfgSetCnf},
    {ID_TAF_MMA_PRLID_QRY_CNF,           AT_RcvMmaPrlIdQryCnf},

    {ID_TAF_MMA_COMBINED_MODE_SWITCH_IND,       AT_RcvMmaCombinedModeSwitchInd},

    {ID_TAF_MMA_ICC_APP_TYPE_SWITCH_IND,        AT_RcvMmaIccAppTypeSwitchInd},
    {ID_TAF_MMA_RAT_COMBINED_MODE_QRY_CNF,      AT_RcvMmaRatCombinedModeQryCnf},

    {ID_TAF_MMA_CTIME_IND,              AT_RcvMmaCTimeInd},

    {ID_TAF_MMA_CDMA_FREQ_LOCK_SET_CNF, AT_RcvMmaCFreqLockSetCnf},
    {ID_TAF_MMA_CDMA_FREQ_LOCK_QRY_CNF, AT_RcvMmaCFreqLockQueryCnf},

    {ID_TAF_MMA_CDMACSQ_SET_CNF,        AT_RcvMmaCdmaCsqSetCnf},
    {ID_TAF_MMA_CDMACSQ_QRY_CNF,        AT_RcvMmaCdmaCsqQryCnf},
    {ID_TAF_MMA_CDMACSQ_IND,            AT_RcvMmaCdmaCsqInd},

    {ID_MMA_TAF_HDR_CSQ_VALUE_IND,      AT_RcvMmaHdrCsqInd},
    {ID_MMA_TAF_HDR_CSQ_SET_CNF,        AT_RcvMmaHdrCsqSetCnf},
    {ID_MMA_TAF_HDR_CSQ_QRY_SETTING_CNF,AT_RcvMmaHdrCsqQryCnf},

    {ID_TAF_MMA_CFPLMN_SET_CNF,         AT_RcvMmaCFPlmnSetCnf},
    {ID_TAF_MMA_CFPLMN_QUERY_CNF,       AT_RcvMmaCFPlmnQueryCnf},

    {ID_TAF_MMA_PREF_PLMN_SET_CNF,     AT_RcvMmaPrefPlmnSetCnf},
    {ID_TAF_MMA_PREF_PLMN_QUERY_CNF,   AT_RcvMmaPrefPlmnQueryCnf},
    {ID_TAF_MMA_PREF_PLMN_TEST_CNF,    AT_RcvMmaPrefPlmnTestCnf},

    {ID_TAF_MMA_PLMN_AUTO_RESEL_CNF,   AT_RcvMmaPlmnReselAutoSetCnf},
    {ID_TAF_MMA_PLMN_SPECIAL_SEL_CNF,  AT_RcvMmaPlmnSpecialSelSetCnf},
    {ID_TAF_MMA_PLMN_LIST_ABORT_CNF,   AT_RcvMmaPlmnListAbortCnf},
    {ID_TAF_MMA_LOCATION_INFO_QRY_CNF,       AT_RcvMmaLocInfoQueryCnf},
    {ID_TAF_MMA_CIPHER_QRY_CNF,        AT_RcvMmaCipherInfoQueryCnf},
    {ID_TAF_MMA_PREF_PLMN_TYPE_SET_CNF,  AT_RcvMmaPrefPlmnTypeSetCnf},
    {ID_TAF_MMA_MT_POWER_DOWN_CNF,     AT_RcvMmaPowerDownCnf},


    {ID_TAF_MMA_PHONE_MODE_QRY_CNF,   AT_RcvMmaPhoneModeQryCnf},
    {ID_TAF_MMA_TIME_CHANGE_IND,      AT_RcvMmaTimeChangeInd},
    {ID_TAF_MMA_MODE_CHANGE_IND,      AT_RcvMmaModeChangeInd},
    {ID_TAF_MMA_PLMN_CHANGE_IND,      AT_RcvMmaPlmnChangeInd},

    {ID_TAF_MMA_CERSSI_SET_CNF,        AT_RcvMmaCerssiSetCnf},
    {ID_TAF_MMA_CERSSI_QRY_CNF,        AT_RcvMmaCerssiInfoQueryCnf},
    {ID_TAF_MMA_ACCESS_MODE_QRY_CNF,   AT_RcvMmaAccessModeQryCnf},
    {ID_TAF_MMA_COPS_QRY_CNF,          AT_RcvMmaCopsQryCnf},
    {ID_TAF_MMA_REG_STATE_QRY_CNF,     AT_RcvMmaRegStateQryCnf},
    {ID_TAF_MMA_AUTO_ATTACH_QRY_CNF,   AT_RcvMmaAutoAttachQryCnf},
    {ID_TAF_MMA_SYSINFO_QRY_CNF,       AT_RcvMmaSysInfoQryCnf},
    /* ANTENNA_INFO_QRY_CNF ????MTA???????? */
    {ID_TAF_MMA_HOME_PLMN_QRY_CNF,     AT_RcvMmaEHplmnInfoQryCnf},

    {ID_TAF_MMA_SRV_STATUS_IND,        AT_RcvMmaSrvStatusInd},
    {ID_TAF_MMA_RSSI_INFO_IND,         AT_RcvMmaRssiInfoInd},
    {ID_TAF_MMA_REG_STATUS_IND,        AT_RcvMmaRegStatusInd},
    {ID_TAF_MMA_REG_REJ_INFO_IND,      AT_RcvMmaRegRejInfoInd},
    {ID_TAF_MMA_PLMN_SELECTION_INFO_IND,  AT_RcvMmaPlmnSelectInfoInd},


    {ID_TAF_MMA_QUICKSTART_SET_CNF,     AT_RcvTafMmaQuickStartSetCnf},
    {ID_TAF_MMA_AUTO_ATTACH_SET_CNF,    AT_RcvTafMmaAutoAttachSetCnf},
    {ID_TAF_MMA_SYSCFG_QRY_CNF,         AT_RcvTafMmaSyscfgQryCnf},
    {ID_TAF_MMA_SYSCFG_TEST_CNF,        AT_RcvTafMmaSyscfgTestCnf},
    {ID_TAF_MMA_CRPN_QRY_CNF,           AT_RcvTafMmaCrpnQryCnf},
    {ID_TAF_MMA_QUICKSTART_QRY_CNF,     AT_RcvTafMmaQuickStartQryCnf},
    /* CSNR_QRY_CNF????MTA???????? */
    {ID_TAF_MMA_CSQ_QRY_CNF,            AT_RcvTafMmaCsqQryCnf},
    /* CSQLVL_QRY_CNF????MTA???????? */

    {ID_TAF_MMA_BATTERY_CAPACITY_QRY_CNF, AT_RcvMmaCbcQryCnf},
    {ID_TAF_MMA_HAND_SHAKE_QRY_CNF,      AT_RcvMmaHsQryCnf},
    {ID_TAF_MMA_PLMN_LIST_CNF,          At_QryParaPlmnListProc},
    {ID_TAF_MSG_MMA_EONS_UCS2_CNF,      AT_RcvMmaEonsUcs2Cnf},

     {ID_TAF_MMA_CSG_LIST_SEARCH_CNF,       AT_RcvMmaCsgListSearchCnfProc},
     {ID_TAF_MMA_CSG_LIST_ABORT_CNF,        AT_RcvMmaCsgListAbortCnf},
	 {ID_TAF_MMA_CSG_SPEC_SEARCH_CNF,       AT_RcvMmaCsgSpecSearchCnfProc},
     {ID_TAF_MMA_QRY_CAMP_CSG_ID_INFO_CNF,  AT_RcvMmaQryCampCsgIdInfoCnfProc},
    {ID_TAF_MMA_IMS_SWITCH_SET_CNF,     AT_RcvMmaImsSwitchSetCnf},
    {ID_TAF_MMA_IMS_SWITCH_QRY_CNF,     AT_RcvMmaImsSwitchQryCnf},
    {ID_TAF_MMA_VOICE_DOMAIN_SET_CNF,   AT_RcvMmaVoiceDomainSetCnf},
    {ID_TAF_MMA_VOICE_DOMAIN_QRY_CNF,   AT_RcvMmaVoiceDomainQryCnf},

    {ID_TAF_MMA_IMS_DOMAIN_CFG_SET_CNF, AT_RcvMmaImsDomainCfgSetCnf},
    {ID_TAF_MMA_IMS_DOMAIN_CFG_QRY_CNF, AT_RcvMmaImsDomainCfgQryCnf},

    {ID_TAF_MMA_ROAM_IMS_SUPPORT_SET_CNF, AT_RcvMmaRoamImsSupportSetCnf},

    {ID_TAF_MMA_IMS_VIDEO_CALL_CAP_SET_CNF, AT_RcvMmaImsVideoCallCapSetCnf},

    {ID_TAF_MMA_IMS_SMS_CFG_QRY_CNF, AT_RcvMmaImsSmsCfgQryCnf},
    {ID_TAF_MMA_IMS_SMS_CFG_SET_CNF, AT_RcvMmaImsSmsCfgSetCnf},

    {ID_TAF_MMA_1XCHAN_SET_CNF,     AT_RcvMma1xChanSetCnf},
    {ID_TAF_MMA_1XCHAN_QUERY_CNF,   AT_RcvMma1xChanQueryCnf},
    {ID_TAF_MMA_CVER_QUERY_CNF,     AT_RcvMmaCVerQueryCnf},
    {ID_TAF_MMA_GETSTA_QUERY_CNF,   AT_RcvMmaStateQueryCnf},
    {ID_TAF_MMA_CHIGHVER_QUERY_CNF, AT_RcvMmaCHverQueryCnf},
    {ID_TAF_MMA_SRCHED_PLMN_INFO_IND, AT_RcvMmaSrchedPlmnInfoInd},

    {ID_TAF_MMA_DPLMN_SET_CNF,       AT_RcvMmaDplmnSetCnf},
    {ID_TAF_MMA_DPLMN_QRY_CNF,       AT_RcvMmaDplmnQryCnf},
    {ID_TAF_MMA_BORDER_INFO_SET_CNF,       AT_RcvMmaBorderInfoSetCnf},
    {ID_TAF_MMA_BORDER_INFO_QRY_CNF,       AT_RcvMmaBorderInfoQryCnf},

    {ID_TAF_MMA_CLMODE_IND,           AT_RcvMmaCLModInd},
    {ID_TAF_MMA_INIT_LOC_INFO_IND,    AT_RcvMmaInitLocInfoInd},

    {ID_TAF_MMA_EFLOCIINFO_SET_CNF,     AT_RcvMmaEflociInfoSetCnf},
    {ID_TAF_MMA_EFLOCIINFO_QRY_CNF,     AT_RcvMmaEflociInfoQryCnf},
    {ID_TAF_MMA_EFPSLOCIINFO_SET_CNF,   AT_RcvMmaPsEflociInfoSetCnf},
    {ID_TAF_MMA_EFPSLOCIINFO_QRY_CNF,   AT_RcvMmaPsEflociInfoQryCnf},

    {ID_TAF_MMA_IMSI_REFRESH_IND,       AT_RcvMmaImsiRefreshInd},

    {ID_TAF_MMA_PACSP_QRY_CNF,       AT_RcvMmaPacspQryCnf},
};

/* AT????????????(????AT??????????????)??
   ????????????????????:??????????????At_CmdStreamPreProc??????????????????(??????????????????????AT????),????
   ????AT??????????????????????????AT??????????????????AT????????????????????????????*/
AT_DATA_STREAM_BUFFER_STRU              g_aucAtDataBuff[AT_MAX_CLIENT_NUM];

/*CREG/CGREG??<CI>????4????????????????(VDF????)*/

AT_CLIENT_MANAGE_STRU                   gastAtClientTab[AT_MAX_CLIENT_NUM];

TAF_UINT32                              gulPBPrintTag = VOS_FALSE;

extern VOS_BOOL                         g_bSetFlg;

AT_FREQLOCK_MODE_TBL_STRU    g_astFreqLockModeTbl[] =
{
    {AT_FREQLOCK_MODE_TYPE_GSM          ,0, "01"},
    {AT_FREQLOCK_MODE_TYPE_WCDMA        ,0, "02"},
    {AT_FREQLOCK_MODE_TYPE_TDSCDMA      ,0, "03"},
    {AT_FREQLOCK_MODE_TYPE_LTE          ,0, "04"},
};

AT_FREQLOCK_GSM_BAND_TBL_STRU    g_astFreqLockGsmBandTbl[] =
{
    {AT_FREQLOCK_BAND_TYPE_GSM_850     ,0, "00"},
    {AT_FREQLOCK_BAND_TYPE_GSM_900     ,0, "01"},
    {AT_FREQLOCK_BAND_TYPE_GSM_1800    ,0, "02"},
    {AT_FREQLOCK_BAND_TYPE_GSM_1900    ,0, "03"},
};
/*****************************************************************************
   3 ??????????????
*****************************************************************************/

extern VOS_UINT32    AT_ProcTempprtEventInd(
    TEMP_PROTECT_EVENT_AT_IND_STRU     *pstMsg
);

/*****************************************************************************
   4 ????????
*****************************************************************************/

/* Modified by s62952 for BalongV300R002 Build???????? 2012-02-28, end */


TAF_VOID At_MmaMsgProc(
    MSG_HEADER_STRU                     *pstMsg
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /*??g_astAtProcMsgFromMmaTab??????????????*/
    ulMsgCnt = sizeof(g_astAtProcMsgFromMmaTab)/sizeof(AT_PROC_MSG_FROM_MMA_STRU);

    /*g_astAtProcMsgFromMtaTab??????????????????*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if (g_astAtProcMsgFromMmaTab[i].ulMsgName == pstMsg->ulMsgName)
        {
            ulRst = g_astAtProcMsgFromMmaTab[i].pProcMsgFunc(pstMsg);

            if (VOS_ERR == ulRst)
            {
                AT_ERR_LOG("At_MmaMsgProc: Msg Proc Err!");
            }

            return;
        }
    }

    /*??????????????????*/
    if (ulMsgCnt == i)
    {
        AT_ERR_LOG("At_MmaMsgProc: Msg Id is invalid!");
    }

    return;
}


TAF_UINT32 At_CallMsgProc(
    MSG_HEADER_STRU                     *pstMsg
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /*??g_astAtProcMsgFromXcallTab??????????????*/
    ulMsgCnt = sizeof(g_astAtProcMsgFromCallTab)/sizeof(AT_PROC_MSG_FROM_CALL_STRU);

    /*g_astAtProcMsgFromXcallTab??????????????????*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if ((g_astAtProcMsgFromCallTab[i].ulMsgName == pstMsg->ulMsgName)
         && (ID_TAF_CALL_APP_TYPE_BUTT != pstMsg->ulMsgName))
        {
            ulRst = g_astAtProcMsgFromCallTab[i].pProcMsgFunc(pstMsg);

            if (VOS_ERR == ulRst)
            {
                AT_ERR_LOG("AT_XcallMsgProc: Msg Proc Err!");
            }

            return AT_OK;
        }
    }

    /*??????????????????*/
    if (ulMsgCnt == i)
    {
        AT_ERR_LOG("AT_XcallMsgProc: Msg Id is invalid!");
    }

    return AT_ERROR;
}


TAF_VOID At_EventMsgProc(MN_AT_IND_EVT_STRU *pMsg)
{

    switch(pMsg->usMsgName)
    {
        case MN_CALLBACK_MSG:
            At_SmsMsgProc(pMsg, pMsg->usLen);
            return;

        case MN_CALLBACK_SET:
            At_SetMsgProc(pMsg->aucContent, pMsg->usLen);
            return;

        case MN_CALLBACK_QRY:
            At_QryMsgProc(pMsg->aucContent, pMsg->usLen);
            return;

        case MN_CALLBACK_PS_CALL:
            /* PS?????????? */
            AT_RcvTafPsEvt((TAF_PS_EVT_STRU*)pMsg);
            return;

        case MN_CALLBACK_DATA_STATUS:
            At_DataStatusMsgProc(pMsg->aucContent, pMsg->usLen);
            return;

        case MN_CALLBACK_CS_CALL:
            At_CsMsgProc(pMsg,pMsg->usLen);
            return;

        case MN_CALLBACK_SS:
            AT_RcvTafSsaEvt((TAF_SSA_EVT_STRU*)pMsg);
            return;

        case MN_CALLBACK_PHONE:
            At_PhMsgProc(pMsg->aucContent, pMsg->usLen);
            break;

        case MN_CALLBACK_PHONE_BOOK:
            At_TAFPbMsgProc(pMsg->aucContent, pMsg->usLen);
            break;

        case MN_CALLBACK_CMD_CNF:
            At_CmdCnfMsgProc(pMsg->aucContent, pMsg->usLen);
            break;

        /* Modified by s62952 for BalongV300R002 Build???????? 2012-02-28, begin */
        case MN_CALLBACK_VOICE_CONTROL:
            At_VcMsgProc(pMsg, pMsg->usLen);
            break;
        /* Modified by s62952 for BalongV300R002 Build???????? 2012-02-28, end */

        case MN_CALLBACK_LOG_PRINT:
            AT_LogPrintMsgProc((TAF_MNTN_LOG_PRINT_STRU *)pMsg);
            break;

        default:
            AT_LOG1("At_MsgProc: invalid message name.", pMsg->usMsgName);
            return;
    }
}



VOS_BOOL AT_E5CheckRight(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    static VOS_BOOL                     bIsRight = VOS_FALSE;
    VOS_UINT8                           aucCmdTmp[20]; /* ??????aucQuickCmd[]?????? */
    VOS_UINT8                           aucQuickCmd[] = "AT^OPENPORT=";
    VOS_UINT16                          usQuickCmdLen;
    VOS_UINT16                          usLeftLen;
    VOS_UINT8                           *pucPwdPos;
    VOS_CHAR                            acPassword[AT_RIGHT_PWD_LEN+1];
    VOS_UINT8                           *pucAtStart ;

    /* ??????????????,????????  */
    if ( AT_RIGHT_OPEN_FLAG_CLOSE == g_stAtRightOpenFlg.enRightOpenFlg )
    {
        return VOS_TRUE;
    }

    /* ??????????????????,?????????? */
    if ( VOS_TRUE == bIsRight )
    {
        return VOS_TRUE;
    }

    /* SSCOM ???????????????? 0x0A */
    pucAtStart = pucData;
    while( (*pucAtStart != 'a') && (*pucAtStart != 'A')  )
    {
        pucAtStart++;
        if ( pucAtStart >= (pucData+usLen) )
        {
            /* ?????? a ?? A break */
            break;
        }
    }
    usLen -= (VOS_UINT16)(pucAtStart - pucData);
    pucData = pucAtStart;

    /* ????????,?????????????? */
    usQuickCmdLen = (VOS_UINT16)VOS_StrLen((VOS_CHAR *)aucQuickCmd);
    if (usLen <= usQuickCmdLen)
    {
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_FALSE;
    }

    TAF_MEM_SET_S(aucCmdTmp, sizeof(aucCmdTmp), 0x00, (VOS_SIZE_T)sizeof(aucCmdTmp));
    TAF_MEM_CPY_S(aucCmdTmp, sizeof(aucCmdTmp), pucData, (VOS_SIZE_T)usQuickCmdLen);

    /* ????AT^OPENPORT?????????????????? */
    if (0 != VOS_StrNiCmp((VOS_CHAR *)aucCmdTmp,
                          (VOS_CHAR *)aucQuickCmd,
                          (VOS_SIZE_T)usQuickCmdLen))
    {
        At_FormatResultData(ucIndex,AT_ERROR);
        return VOS_FALSE;
    }

    usLeftLen = usLen - usQuickCmdLen;
    pucPwdPos = pucData + usQuickCmdLen;

    if ( usLeftLen >= sizeof(aucCmdTmp) )
    {
        At_FormatResultData(ucIndex,AT_ERROR);
        return VOS_FALSE;
    }

    TAF_MEM_SET_S(aucCmdTmp, sizeof(aucCmdTmp), 0x00, sizeof(aucCmdTmp));
    TAF_MEM_CPY_S(aucCmdTmp, sizeof(aucCmdTmp), pucPwdPos, usLeftLen);

    TAF_MEM_SET_S(acPassword, sizeof(acPassword), 0x00, sizeof(acPassword));
    TAF_MEM_CPY_S(acPassword, sizeof(acPassword), g_stAtRightOpenFlg.acPassword, sizeof(g_stAtRightOpenFlg.acPassword));

    /* ????????????????*/
    if ( 0 == VOS_StrCmp(acPassword, (VOS_CHAR *)aucCmdTmp))
    {
        /* ????OK???????????? */
        At_FormatResultData(ucIndex, AT_OK);
        bIsRight = VOS_TRUE;
        return VOS_FALSE;
    }

    /* ????ERROR */
    At_FormatResultData(ucIndex, AT_ERROR);
    return VOS_FALSE;
}


TAF_VOID At_PppProtocolRelIndProc(AT_PPP_PROTOCOL_REL_IND_MSG_STRU *pMsg)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usPppId;

    usPppId = pMsg->usPppId;
    ucIndex = gastAtPppIndexTab[usPppId];

    if ( (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
      || (AT_HSUART_USER == gastAtClientTab[ucIndex].UserType) )
    {
        if ( (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode)
          && (AT_PPP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
          && (AT_CMD_WAIT_PPP_PROTOCOL_REL_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) )
        {
            /* ??AT?????????????????? */
            At_SetMode(ucIndex, AT_CMD_MODE, AT_NORMAL_MODE);

            /* ?????????? */
            AT_STOP_TIMER_CMD_READY(ucIndex);

            /* ????NO CARRIER */
            gstAtSendData.usBufLen = 0;
            At_FormatResultData(ucIndex, AT_NO_CARRIER);
        }
    }

    return;
}


VOS_VOID AT_ModemMscIndProc(AT_PPP_MODEM_MSC_IND_MSG_STRU *pMsg)
{
    VOS_UINT8                           ucIndex;

    ucIndex = pMsg->ucIndex;

    AT_MNTN_TraceInputMsc(ucIndex, (AT_DCE_MSC_STRU *)pMsg->aucMscInd);

    if ( (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
      || (AT_HSUART_USER == gastAtClientTab[ucIndex].UserType) )
    {
        AT_ModemStatusPreProc(ucIndex, (AT_DCE_MSC_STRU *)pMsg->aucMscInd);
    }
    else
    {
        AT_WARN_LOG1("AT_ModemMscIndProc: index %d is unused", ucIndex);
    }

    return;
}


TAF_VOID At_PppMsgProc(MSG_HEADER_STRU *pMsg)
{
    switch  (pMsg->ulMsgName)
    {
        case AT_PPP_RELEASE_IND_MSG:
            At_PppReleaseIndProc(((AT_PPP_RELEASE_IND_MSG_STRU *)pMsg)->ucIndex);
            break;

        case AT_PPP_MODEM_MSC_IND_MSG:
            AT_ModemMscIndProc((AT_PPP_MODEM_MSC_IND_MSG_STRU *)pMsg);
            break;

        case AT_PPP_PROTOCOL_REL_IND_MSG:
            At_PppProtocolRelIndProc((AT_PPP_PROTOCOL_REL_IND_MSG_STRU *)pMsg);
            break;

        default:
            AT_LOG1("At_PppMsgProc: ulMsgName is abnormal!",pMsg->ulMsgName);
            break;
    }
}



VOS_UINT32  At_RfCfgCnfReturnErrProc(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRslt;

    switch (gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
       case AT_CMD_SET_FTXON:
           ulRslt = AT_FTXON_SET_FAIL;
           break;

       case AT_CMD_SET_FRXON:
           ulRslt = AT_FRXON_SET_FAIL;
           break;

       case AT_CMD_QUERY_RSSI:
           ulRslt = AT_FRSSI_OTHER_ERR;
           break;

       /* ????????????????????DSP?????????????????????????????? */
       case AT_CMD_SET_RXDIV:
       case AT_CMD_SET_RXPRI:
           ulRslt = AT_CME_RX_DIV_OTHER_ERR;
           break;

       default:
           ulRslt = AT_ERROR;
           break;
    }

   return ulRslt;
}


VOS_VOID  At_RfCfgCnfReturnSuccProc(
    VOS_UINT8                           ucIndex
)
{
    switch (gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        case AT_CMD_SET_FTXON:
            g_stAtDevCmdCtrl.ucTxOnOff = g_stAtDevCmdCtrl.ucTempRxorTxOnOff;

            /* ?????????????????????????????????????????????????????????????????????????? */
            if (AT_DSP_RF_SWITCH_ON == g_stAtDevCmdCtrl.ucTxOnOff)
            {
                g_stAtDevCmdCtrl.ucRxonOrTxon = AT_TXON_OPEN;
            }
            break;

        case AT_CMD_SET_FRXON:
            g_stAtDevCmdCtrl.ucRxOnOff = g_stAtDevCmdCtrl.ucTempRxorTxOnOff;

            /* ?????????????????????????????????????????????????????????????????????????? */
            if (AT_DSP_RF_SWITCH_ON == g_stAtDevCmdCtrl.ucRxOnOff)
            {
                g_stAtDevCmdCtrl.ucRxonOrTxon = AT_RXON_OPEN;
            }
            break;

        case AT_CMD_QUERY_RSSI:
            break;

        case AT_CMD_SET_RXDIV:
           if ((AT_OK == At_SaveRxDivPara(g_stAtDevCmdCtrl.usOrigBand, 1))
            && (AT_TMODE_FTM == g_stAtDevCmdCtrl.ucCurrentTMode))
           {
               g_stAtDevCmdCtrl.ucPriOrDiv = AT_RX_DIV_ON;
               g_stAtDevCmdCtrl.usRxDiv    = g_stAtDevCmdCtrl.usOrigBand;
           }
           break;

        case AT_CMD_SET_RXPRI:
            g_stAtDevCmdCtrl.ucPriOrDiv = AT_RX_PRI_ON;
            g_stAtDevCmdCtrl.usRxPri    = g_stAtDevCmdCtrl.usOrigBand;
            break;

        default:
            break;
    }

    return;

}


VOS_VOID  At_HpaRfCfgCnfProc(
    HPA_AT_RF_CFG_CNF_STRU              *pstMsg
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;

    /*??????????????????????*/
    ucIndex = g_stAtDevCmdCtrl.ucIndex;

    if (AT_HPA_RSLT_FAIL == pstMsg->usErrFlg)
    {
        AT_INFO_LOG("At_HpaRfCfgCnfProc: set rfcfg err");
        ulRslt = At_RfCfgCnfReturnErrProc(ucIndex);
        AT_STOP_TIMER_CMD_READY(ucIndex);
        At_FormatResultData(ucIndex, ulRslt);
    }
    else
    {
        ulRslt = AT_OK;
        At_RfCfgCnfReturnSuccProc(ucIndex);

        /* ^FRSSI???GDSP LOAD??????????ID_HPA_AT_RF_CFG_CNF????,????????,??????
           ID_HPA_AT_RF_RX_RSSI_IND???????????? */
        if (AT_CMD_QUERY_RSSI != gastAtClientTab[ucIndex].CmdCurrentOpt)
        {
            AT_STOP_TIMER_CMD_READY(ucIndex);
            At_FormatResultData(ucIndex, ulRslt);
        }
    }
    return;
}


VOS_VOID  At_CHpaRfCfgCnfProc(
    CHPA_AT_RF_CFG_CNF_STRU             *pstMsg
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;

    /*??????????????????????*/
    ucIndex = g_stAtDevCmdCtrl.ucIndex;

    if (AT_HPA_RSLT_FAIL == pstMsg->usErrFlg)
    {
        AT_INFO_LOG("At_CHpaRfCfgCnfProc: set rfcfg err");
        ulRslt = At_RfCfgCnfReturnErrProc(ucIndex);
        AT_STOP_TIMER_CMD_READY(ucIndex);
        At_FormatResultData(ucIndex, ulRslt);
    }
    else
    {
        ulRslt = AT_OK;
        At_RfCfgCnfReturnSuccProc(ucIndex);

        AT_STOP_TIMER_CMD_READY(ucIndex);
        At_FormatResultData(ucIndex, ulRslt);
    }
    return;
}



VOS_VOID  At_RfRssiIndProc(
    HPA_AT_RF_RX_RSSI_IND_STRU          *pstMsg
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;
    VOS_INT32                           lRssi;

    /*??????????????????????*/
    ucIndex  = g_stAtDevCmdCtrl.ucIndex;

    if (AT_DSP_RF_AGC_STATE_ERROR == pstMsg->sAGCGain)  /* ???? */
    {
        AT_WARN_LOG("AT_RfRssiIndProc err");
        ulRslt = AT_FRSSI_OTHER_ERR;
    }
    else
    {

        gstAtSendData.usBufLen = 0;

        /*????RSSI??????????0.125dBm????????????????*1000.*/
        lRssi = pstMsg->sRSSI * AT_DSP_RSSI_VALUE_MUL_THOUSAND;

        /*??????RSSI????????????????????????0.1dBm??????????????????????RSSI
          ????-85.1dBm??????????851. ??????????1000????????????0.1dBm????????100*/
        if (lRssi < 0 )
        {
            lRssi = (-1*lRssi)/100;
        }
        else
        {
            lRssi = lRssi/100;
        }

        /* ????V7R5????4RX??????GU??????????????????0??L????FTM??????????????4RX????????4??????????????????1???? */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           lRssi);

        gstAtSendData.usBufLen = usLength;
        ulRslt = AT_OK;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRslt);

    return;
}


VOS_VOID  At_HPAMsgProc(
    MsgBlock                            *pstMsg
)
{
    HPA_AT_HEADER_STRU                  *pHeader;

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_HpaMsgProc: pstMsg is NULL");
        return;
    }

    pHeader = (HPA_AT_HEADER_STRU *)pstMsg;

    switch (pHeader->usMsgID)
    {
        case ID_HPA_AT_RF_CFG_CNF:
            At_HpaRfCfgCnfProc((HPA_AT_RF_CFG_CNF_STRU *)pstMsg);
            break;

        case ID_HPA_AT_RF_RX_RSSI_IND:
            At_RfRssiIndProc((HPA_AT_RF_RX_RSSI_IND_STRU *)pstMsg);
            break;

        case ID_AT_WPHY_RF_PLL_STATUS_CNF:
            At_RfPllStatusCnfProc((PHY_AT_RF_PLL_STATUS_CNF_STRU *)pstMsg);
            break;

        case ID_AT_PHY_POWER_DET_CNF:
            At_RfFpowdetTCnfProc((PHY_AT_POWER_DET_CNF_STRU *)pstMsg);
            break;
        case ID_HPA_AT_MIPI_WR_CNF:
            At_MipiWrCnfProc((HPA_AT_MIPI_WR_CNF_STRU *)pstMsg);
            break;
        case ID_HPA_AT_MIPI_RD_CNF:
            At_MipiRdCnfProc((HPA_AT_MIPI_RD_CNF_STRU *)pstMsg);
            break;
        case ID_HPA_AT_SSI_WR_CNF:
            At_SsiWrCnfProc((HPA_AT_SSI_WR_CNF_STRU *)pstMsg);
            break;

        case ID_HPA_AT_SSI_RD_CNF:
            At_SsiRdCnfProc((HPA_AT_SSI_RD_CNF_STRU *)pstMsg);
            break;


        case ID_HPA_AT_PDM_CTRL_CNF:
            At_PdmCtrlCnfProc((HPA_AT_PDM_CTRL_CNF_STRU *)pstMsg);
            break;

        default:
            AT_WARN_LOG("At_HpaMsgProc: ulMsgName is Abnormal!");
            break;
    }

    return;
}


VOS_VOID  At_CHPAMsgProc(
    MsgBlock                            *pstMsg
)
{
    HPA_AT_HEADER_STRU                  *pHeader = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_HpaMsgProc: pstMsg is NULL");
        return;
    }

    pHeader = (HPA_AT_HEADER_STRU *)pstMsg;

    switch (pHeader->usMsgID)
    {
        case ID_CHPA_AT_RF_CFG_CNF:
            At_CHpaRfCfgCnfProc((CHPA_AT_RF_CFG_CNF_STRU *)pstMsg);
            break;

        case ID_AT_PHY_POWER_DET_CNF:
            At_RfFpowdetTCnfProc((VOS_VOID *)pstMsg);
            break;

        default:
            AT_WARN_LOG("At_CHPAMsgProc: ulMsgName is Abnormal!");
            break;
    }

    return;
}



VOS_VOID  At_GHPAMsgProc(
    MsgBlock                            *pstMsg
)
{
    HPA_AT_HEADER_STRU         *pHeader;

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_HpaMsgProc: pstMsg is NULL");
        return;
    }

    pHeader = (HPA_AT_HEADER_STRU *)pstMsg;

    switch (pHeader->usMsgID)
    {
        case ID_GHPA_AT_RF_MSG_CNF:
            At_HpaRfCfgCnfProc((HPA_AT_RF_CFG_CNF_STRU *)pstMsg);
            break;

        case ID_GHPA_AT_RF_RX_RSSI_IND:
            At_RfRssiIndProc((HPA_AT_RF_RX_RSSI_IND_STRU *)pstMsg);
            break;

        case ID_AT_GPHY_RF_PLL_STATUS_CNF:
            At_RfPllStatusCnfProc((PHY_AT_RF_PLL_STATUS_CNF_STRU *)pstMsg);
            break;

        case ID_HPA_AT_MIPI_WR_CNF:
            At_MipiWrCnfProc((HPA_AT_MIPI_WR_CNF_STRU *)pstMsg);
            break;

        case ID_HPA_AT_MIPI_RD_CNF:
            At_MipiRdCnfProc((HPA_AT_MIPI_RD_CNF_STRU *)pstMsg);
            break;

        case ID_HPA_AT_SSI_WR_CNF:
            At_SsiWrCnfProc((HPA_AT_SSI_WR_CNF_STRU *)pstMsg);
            break;

        case ID_HPA_AT_SSI_RD_CNF:
            At_SsiRdCnfProc((HPA_AT_SSI_RD_CNF_STRU *)pstMsg);
            break;


        case ID_AT_PHY_POWER_DET_CNF:
            At_RfFpowdetTCnfProc((VOS_VOID *)pstMsg);
            break;

        default:
            AT_WARN_LOG("At_HpaMsgProc: ulMsgName is Abnormal!");
            break;
    }

    return;
}


VOS_UINT32 AT_FormatAtiCmdQryString(
    MODEM_ID_ENUM_UINT16                enModemId,
    DRV_AGENT_MSID_QRY_CNF_STRU        *pstDrvAgentMsidQryCnf
)
{
    TAF_PH_MEINFO_STRU                  stMeInfo;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           aucTmp[AT_MAX_VERSION_LEN];
    VOS_UINT32                          ulI;
    VOS_UINT8                           ucCheckData;

    /* ?????? */
    usDataLen     = 0;
    ulI           = 0;
    ucCheckData   = 0;
    TAF_MEM_SET_S(&stMeInfo, sizeof(stMeInfo), 0x00, sizeof(TAF_PH_MEINFO_STRU));


    TAF_MEM_SET_S(aucTmp, sizeof(aucTmp), 0x00, sizeof(aucTmp));

    /* ????Model???? */
    if ( (VOS_NULL_PTR == pstDrvAgentMsidQryCnf)
      || (DRV_AGENT_MSID_QRY_NO_ERROR != pstDrvAgentMsidQryCnf->ulResult))
    {
        return AT_ERROR;
    }

    /* ????Manufacturer???? */
    usDataLen = TAF_MAX_MFR_ID_LEN + 1;
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_FMRID, aucTmp, usDataLen))
    {
        AT_WARN_LOG("AT_FormatAtiCmdQryString:WARNING:NVIM Read en_NV_Item_FMRID falied!");
        return AT_ERROR;
    }
    else
    {
        TAF_MEM_CPY_S(stMeInfo.FmrId.aucMfrId, sizeof(stMeInfo.FmrId.aucMfrId), aucTmp, usDataLen);
    }

    /* ????IMEI???? */
    for (ulI = 0; ulI < TAF_PH_IMEI_LEN; ulI++)
    {
        stMeInfo.ImeisV.aucImei[ulI] = pstDrvAgentMsidQryCnf->aucImei[ulI] + 0x30;
    }

    for (ulI = 0; ulI < (TAF_PH_IMEI_LEN - 2); ulI += 2)
    {
        ucCheckData += (TAF_UINT8)(((pstDrvAgentMsidQryCnf->aucImei[ulI])
                       +((pstDrvAgentMsidQryCnf->aucImei[ulI + 1UL] * 2) / 10))
                       +((pstDrvAgentMsidQryCnf->aucImei[ulI + 1UL] * 2) % 10));
    }
    ucCheckData = (10 - (ucCheckData%10)) % 10;

    stMeInfo.ImeisV.aucImei[TAF_PH_IMEI_LEN - 2] = ucCheckData + 0x30;
    stMeInfo.ImeisV.aucImei[TAF_PH_IMEI_LEN - 1] = 0;

    /* ????ATI???????????? */
    usDataLen = 0;
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","Manufacturer",stMeInfo.FmrId.aucMfrId);
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","Model",  pstDrvAgentMsidQryCnf->acModelId);
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","Revision",pstDrvAgentMsidQryCnf->acSoftwareVerId);
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","IMEI",stMeInfo.ImeisV.aucImei);
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s","+GCAP: +CGSM,+DS,+ES");

    gstAtSendData.usBufLen = usDataLen;

    return AT_OK;

}


VOS_UINT32 AT_RcvDrvAgentMsidQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_MSID_QRY_CNF_STRU        *pstDrvAgentMsidQryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;

    enModemId = MODEM_ID_0;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

    /* ?????? */
    pRcvMsg               = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDrvAgentMsidQryCnf = (DRV_AGENT_MSID_QRY_CNF_STRU *)(pRcvMsg->aucContent);

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDrvAgentMsidQryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentMsidQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentMsidQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    /* ????AT???????????????????? */
    if (AT_CMD_MSID_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);
        ulResult = AT_FormatAtiCmdQryString(enModemId, pstDrvAgentMsidQryCnf);
    }
    else if (AT_CMD_CGMM_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       "%s",
                                                       pstDrvAgentMsidQryCnf->acModelId);
        ulResult = AT_OK;
    }
    else if (AT_CMD_CGMR_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       "%s",
                                                       pstDrvAgentMsidQryCnf->acSoftwareVerId);
        ulResult = AT_OK;
    }
    else
    {
        return VOS_ERR;
    }

    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("At_SetImeiPara: Get modem id fail.");
        return VOS_ERR;
    }


    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */
    if (AT_ERROR == ulResult)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentGasMntnCmdRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_GAS_MNTN_CMD_CNF_STRU    *pstDrvAgentGasMntnCmdCnf;
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          i;
    VOS_UINT16                          usLength;

    /* ?????? */
    pRcvMsg                  = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDrvAgentGasMntnCmdCnf = (DRV_AGENT_GAS_MNTN_CMD_CNF_STRU *)(pRcvMsg->aucContent);
    ulResult                 = AT_OK;
    usLength                 = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDrvAgentGasMntnCmdCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentGasMntnCmdRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentGasMntnCmdRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    /* ????AT???????????????????? */
    if (AT_CMD_CGAS_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^CGAS???????? */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstDrvAgentGasMntnCmdCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        /* ???????? */
        if (GAS_AT_CMD_NCELL == pstDrvAgentGasMntnCmdCnf->ucCmd)
        {
            if ( (pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum > 0)
              && ((pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum % 3) == 0)
              && (pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum <= 20) )
            {
                AT_FormatGasAtCmdRslt(&pstDrvAgentGasMntnCmdCnf->stAtCmdRslt);
            }
            else if (0 == pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum)
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                   "0");
                gstAtSendData.usBufLen = usLength;
            }
            else
            {
                ulResult = AT_ERROR;
            }
        }
        else if (GAS_AT_CMD_SCELL == pstDrvAgentGasMntnCmdCnf->ucCmd)
        {
            /* ???????????? */
            if (3 != pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum)
            {
                ulResult = AT_ERROR;
            }
            else
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                   "%d,",
                                                   pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[0]);
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                   "0x%X,",
                                                   pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[1]&0xff);
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                   "%d",
                                                   pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[2]);
                gstAtSendData.usBufLen = usLength;
                ulResult = AT_OK;
            }
        }
        else if (pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum > 0)
        {
            /* ???????? */
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                               "%d",
                                               pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[0]);

            for (i = 1; i< pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum ;i++)
            {
                usLength +=(TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (TAF_CHAR *)pgucAtSndCodeAddr,
                                                  (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                  ",%d",
                                                  pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[i]);
            }
            gstAtSendData.usBufLen = usLength;
        }
        else
        {

        }
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentHardwareQryRsp(VOS_VOID *pMsg)
{
    VOS_UINT32                                  ulRet;
    TAF_UINT16                                  usLength;
    VOS_UINT8                                   ucIndex;
    DRV_AGENT_MSG_STRU                         *pRcvMsg;
    DRV_AGENT_HARDWARE_QRY_CNF_STRU            *pHardWareCnf;

    /* ?????? */
    pRcvMsg      = (DRV_AGENT_MSG_STRU*)pMsg;
    pHardWareCnf = (DRV_AGENT_HARDWARE_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pHardWareCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentHardwareQryRsp: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentHardwareQryRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_HARDWARE_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    usLength               = 0;
    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( DRV_AGENT_NO_ERROR == pHardWareCnf->ulResult )
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "\"%s\"",
                                           pHardWareCnf->aucHwVer);

        gstAtSendData.usBufLen = usLength;
        ulRet                  = AT_OK;
    }
    else
    {
        ulRet                  = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;

}


VOS_UINT32 AT_RcvDrvAgentVertimeQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_VERSION_TIME_STRU        *pstDrvAgentVersionTime;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pRcvMsg                     = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDrvAgentVersionTime      = (DRV_AGENT_VERSION_TIME_STRU *)(pRcvMsg->aucContent);
    ulResult                    = AT_OK;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDrvAgentVersionTime->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentVertimeQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentVertimeQryRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    /* ????AT???????????????????? */
    if (AT_CMD_VERSIONTIME_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^VERTIME???????? */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%s",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstDrvAgentVersionTime->aucData);

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentYjcxSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_YJCX_SET_CNF_STRU            *pstYjcxSetCnf;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usDataLen;

    /* ?????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstYjcxSetCnf   = (DRV_AGENT_YJCX_SET_CNF_STRU *)(pRcvMsg->aucContent);
    ulResult        = AT_OK;
    usDataLen       = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstYjcxSetCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentYjcxSetCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentYjcxSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    /* ????AT???????????????????? */
    if (AT_CMD_YJCX_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^YJCX???????????? */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstYjcxSetCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        usDataLen =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR*)pgucAtSndCodeAddr,
                                            "%s: ",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,
                                            "%s",
                                            pstYjcxSetCnf->aucflashInfo);
        gstAtSendData.usBufLen = usDataLen;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentYjcxQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_YJCX_QRY_CNF_STRU            *pstYjcxQryCnf;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usDataLen;

    /* ?????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstYjcxQryCnf   = (DRV_AGENT_YJCX_QRY_CNF_STRU *)(pRcvMsg->aucContent);
    ulResult        = AT_OK;
    usDataLen       = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstYjcxQryCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentYjcxQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentYjcxQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    /* ????AT???????????????????? */
    if (AT_CMD_YJCX_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^YJCX???????????? */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstYjcxQryCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        usDataLen =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR*)pgucAtSndCodeAddr,
                                            "%s: ",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,
                                            "%s",
                                            pstYjcxQryCnf->aucgpioInfo);

        gstAtSendData.usBufLen = usDataLen;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_VOID At_QryEonsUcs2RspProc(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulResult,
    TAF_MMA_EONS_UCS2_PLMN_NAME_STRU   *stEonsUcs2PlmnName,
    TAF_MMA_EONS_UCS2_HNB_NAME_STRU    *pstEonsUcs2HNBName
)
{
    TAF_MMA_EONS_UCS2_PLMN_NAME_STRU   *pstPlmnName = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulLoop;

    TAF_MMA_EONS_UCS2_HNB_NAME_STRU   *pstHnbName = VOS_NULL_PTR;
    VOS_UINT8                          ucHomeNodeBLen;

    pstHnbName = (TAF_MMA_EONS_UCS2_HNB_NAME_STRU *)pstEonsUcs2HNBName;

    usLength = 0;

    if (VOS_NULL_PTR != pstHnbName)
    {
        if (0 != pstHnbName->ucHomeNodeBNameLen)
        {
            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              "%s:",
                                              g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

            /* ????home NodeB Name, ucs2??????????????48???? */
            ucHomeNodeBLen = AT_MIN(pstHnbName->ucHomeNodeBNameLen, TAF_MMA_MAX_HOME_NODEB_NAME_LEN);

            for (ulLoop = 0; ulLoop < ucHomeNodeBLen; ulLoop++)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%02X",
                                                   pstHnbName->aucHomeNodeBName[ulLoop]);
            }
            gstAtSendData.usBufLen = usLength;

            At_FormatResultData(ucIndex,ulResult);

            return;
        }
    }


    /* ?????????? */
    pstPlmnName = (TAF_MMA_EONS_UCS2_PLMN_NAME_STRU *)stEonsUcs2PlmnName;

    if (VOS_NULL_PTR == pstPlmnName)
    {
        return;
    }

    /* ????LongName??ShortName */
    if ( pstPlmnName->ucLongNameLen <= TAF_PH_OPER_NAME_LONG
      && pstPlmnName->ucShortNameLen <= TAF_PH_OPER_NAME_SHORT )
    {

        /* ^EONSUCS2:<long name>,<short name> */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        for (ulLoop = 0; ulLoop < pstPlmnName->ucLongNameLen; ulLoop++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%02X",
                                               pstPlmnName->aucLongName[ulLoop]);
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr + usLength, ",");

        for (ulLoop = 0; ulLoop < pstPlmnName->ucShortNameLen; ulLoop++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%02X",
                                               pstPlmnName->aucShortName[ulLoop]);
        }

        gstAtSendData.usBufLen = usLength;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
    }

    At_FormatResultData(ucIndex,ulResult);

    return;
}


VOS_UINT32 AT_RcvMmaEonsUcs2Cnf(VOS_VOID *pMsg)
{
    TAF_MMA_EONS_UCS2_CNF_STRU         *pstEonsUcs2QryCnfMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pstEonsUcs2QryCnfMsg    = (TAF_MMA_EONS_UCS2_CNF_STRU *)pMsg;
    ulResult                = AT_OK;

    if (VOS_NULL_PTR == pstEonsUcs2QryCnfMsg)
    {
        AT_WARN_LOG("AT_RcvMmaCrpnQueryRsp:MSG IS NULL!");
        return VOS_ERR;
    }

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEonsUcs2QryCnfMsg->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCrpnQueryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaEonsUcs2Cnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_EONSUCS2_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^EONSUCS2???????????? */
    if (TAF_ERR_NO_ERROR != pstEonsUcs2QryCnfMsg->enRslt)
    {
        ulResult = At_ChgTafErrorCode(ucIndex, (VOS_UINT16)pstEonsUcs2QryCnfMsg->enErrorCause);

        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex,ulResult);
        return VOS_OK;
    }
    At_QryEonsUcs2RspProc(ucIndex,
                    pstEonsUcs2QryCnfMsg->ucOpId,
                    ulResult,
                    &pstEonsUcs2QryCnfMsg->stEonsUcs2PlmnName,
                    &pstEonsUcs2QryCnfMsg->stEonsUcs2HNBName);

    return VOS_OK;
}


VOS_UINT32 AT_RcvAtMmaUsimStatusInd(VOS_VOID *pMsg)
{
    /* Modified by l60609 for DSDA Phase II, 2012-12-24, Begin */
    AT_MMA_USIM_STATUS_IND_STRU        *pstAtMmaUsimStatusIndMsg;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_USIM_INFO_CTX_STRU              *pstUsimInfoCtx = VOS_NULL_PTR;

    /* ?????? */
    pstAtMmaUsimStatusIndMsg   = (AT_MMA_USIM_STATUS_IND_STRU *)pMsg;

    enModemId = AT_GetModemIDFromPid(pstAtMmaUsimStatusIndMsg->ulSenderPid);

    if (enModemId >= MODEM_ID_BUTT)
    {
        printk(KERN_ERR "\n AT_RcvAtMmaUsimStatusInd: enModemId :%d , ulSenderPid :%d\n", enModemId, pstAtMmaUsimStatusIndMsg->ulSenderPid);

        return VOS_ERR;
    }

    pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(enModemId);

    /* ?????????????????? */
    pstUsimInfoCtx->enCardType       = pstAtMmaUsimStatusIndMsg->enCardType;
    pstUsimInfoCtx->enCardMediumType = pstAtMmaUsimStatusIndMsg->enCardMediumType;
    pstUsimInfoCtx->enCardStatus     = pstAtMmaUsimStatusIndMsg->enCardStatus;
    pstUsimInfoCtx->ucIMSILen        = pstAtMmaUsimStatusIndMsg->ucIMSILen;
    TAF_MEM_CPY_S(pstUsimInfoCtx->aucIMSI, sizeof(pstUsimInfoCtx->aucIMSI), pstAtMmaUsimStatusIndMsg->aucIMSI, NAS_MAX_IMSI_LENGTH);
    /* Modified by l60609 for DSDA Phase II, 2012-12-24, End */

    printk(KERN_ERR "\nAT_RcvAtMmaUsimStatusInd: CardType: %d , CardStatus: %d , ulSenderPid: %d\n",
           pstAtMmaUsimStatusIndMsg->enCardType, pstAtMmaUsimStatusIndMsg->enCardStatus, pstAtMmaUsimStatusIndMsg->ulSenderPid);

    return VOS_OK;

}


VOS_UINT32 At_RcvAtCcMsgStateQryCnfProc(VOS_VOID *pMsg)
{
    AT_CC_STATE_QRY_CNF_MSG_STRU           *pstAtCcStateQryCnfMsg;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              i;
    VOS_UINT16                              usLength;

    /* ?????? */
    pstAtCcStateQryCnfMsg = (AT_CC_STATE_QRY_CNF_MSG_STRU *)pMsg;
    ulResult              = AT_OK;
    usLength              = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstAtCcStateQryCnfMsg->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("At_RcvAtCcMsgStateQryCnfProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvAtCcMsgStateQryCnfProc : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    /* ???????????????????? */
    if (AT_CMD_CC_STATE_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^CCC???????????? */
    gstAtSendData.usBufLen = 0;
    if (0 == pstAtCcStateQryCnfMsg->ucCallNum)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
        for ( i = 0 ; i < pstAtCcStateQryCnfMsg->ucCallNum ; i++ )
        {
            AT_ShowCccRst(&pstAtCcStateQryCnfMsg->astCcStateInfoList[i],&usLength);
        }

        if (0 == usLength)
        {
            ulResult = AT_ERROR;
        }
    }

    /* ???????? */
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaCmmSetCmdRsp(VOS_VOID *pMsg)
{
    TAF_MMA_CMM_SET_CNF_STRU           *pstMnMmTestCmdRspMsg;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          i;
    VOS_UINT16                          usLength;

    /* ?????? */
    pstMnMmTestCmdRspMsg = (TAF_MMA_CMM_SET_CNF_STRU *)pMsg;
    ulResult              = AT_OK;
    usLength              = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMnMmTestCmdRspMsg->stCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCmmSetCmdRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCmmSetCmdRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^CMM???????????? */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstMnMmTestCmdRspMsg->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        if (pstMnMmTestCmdRspMsg->stAtCmdRslt.ulRsltNum > 0)
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                               "%d",
                                               pstMnMmTestCmdRspMsg->stAtCmdRslt.aulRslt[0]);

            for (i = 1; i< pstMnMmTestCmdRspMsg->stAtCmdRslt.ulRsltNum ;i++)
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                                   ",%d",
                                                   pstMnMmTestCmdRspMsg->stAtCmdRslt.aulRslt[i]);
            }
            gstAtSendData.usBufLen = usLength;
        }
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentFullHardwareQryRsp(VOS_VOID *pMsg)
{
    TAF_UINT16                                       usLength;
    VOS_UINT8                                        ucIndex;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_FULL_HARDWARE_QRY_CNF_STRU            *pstEvent;

    /* ?????? */
    pRcvMsg  = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent = (DRV_AGENT_FULL_HARDWARE_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentFullHardwareQryRsp: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentFullHardwareQryRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_FULL_HARDWARE_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    usLength               = 0;
    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "\"%s ",
                                           pstEvent->aucModelId);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s,",
                                           pstEvent->aucRevisionId);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s\"",
                                           pstEvent->aucHwVer);

        gstAtSendData.usBufLen = usLength;

        At_FormatResultData(ucIndex, AT_OK);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }

    return VOS_OK;
}


VOS_UINT32 At_SendRfCfgAntSelToHPA(
    VOS_UINT8                           ucDivOrPriOn,
    VOS_UINT8                           ucIndex
)
{
    AT_HPA_RF_CFG_REQ_STRU              *pstMsg;
    VOS_UINT32                           ulLength;
    VOS_UINT16                           usMask;

    /* ????AT_HPA_RF_CFG_REQ_STRU???? */
    ulLength = sizeof(AT_HPA_RF_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (AT_HPA_RF_CFG_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_SendRfCfgAntSelToHPA: alloc msg fail!");
        return AT_FAILURE;
    }

    TAF_MEM_SET_S(pstMsg, sizeof(AT_HPA_RF_CFG_REQ_STRU), 0x00, sizeof(AT_HPA_RF_CFG_REQ_STRU));


    /* ?????????? */
    pstMsg->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid        = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid      = AT_GetDestPid(ucIndex, I0_DSP_PID_WPHY);
    pstMsg->ulLength           = ulLength;


    /* ?????????? */
    pstMsg->usMsgID            = ID_AT_HPA_RF_CFG_REQ;
    usMask                     = W_RF_MASK_RX_ARFCN | W_RF_MASK_RX_ANTSEL \
                                 | W_RF_MASK_RX_RXONOFF;

    /* ???????????????? */
    pstMsg->stRfCfgPara.usMask = usMask;

    if (AT_RX_DIV_ON == ucDivOrPriOn)
    {
        pstMsg->stRfCfgPara.usRxAntSel = ANT_TWO;
        pstMsg->stRfCfgPara.usRxEnable = DSP_CTRL_RX_ALL_ANT_ON;
    }
    else
    {
        pstMsg->stRfCfgPara.usRxAntSel = ANT_ONE;
        pstMsg->stRfCfgPara.usRxEnable = DSP_CTRL_RX_ANT1_ON;
    }

    pstMsg->stRfCfgPara.usRxBand       = g_stAtDevCmdCtrl.stDspBandArfcn.usDspBand;
    pstMsg->stRfCfgPara.usRxFreqNum    = g_stAtDevCmdCtrl.stDspBandArfcn.usDlArfcn;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("At_SendRfCfgAntSelToHPA: Send msg fail!");
        return AT_FAILURE;
    }

    return AT_SUCCESS;
}


VOS_UINT32 AT_RcvDrvAgentSetSimlockCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_SET_SIMLOCK_CNF_STRU                  *pstEvent;
    VOS_UINT32                                       ulRet;
    VOS_UINT8                                        ucIndex;

    /* ?????? */
    pRcvMsg  = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent = (DRV_AGENT_SET_SIMLOCK_CNF_STRU *)pRcvMsg->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetSimlockCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetSimlockCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_SIMLOCK_SET_REQ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;

}


VOS_UINT32 AT_RcvDrvAgentQryRxdivCnf(VOS_VOID *pMsg)
{
    VOS_UINT32                                       ulRet;
    VOS_UINT8                                        ucIndex;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_QRY_RXDIV_CNF_STRU                    *pstEvent;
    VOS_UINT32                                       ulUserDivBandsLow;
    VOS_UINT32                                       ulUserDivBandsHigh;
    VOS_UINT32                                       ulDrvDivBandsLow;
    VOS_UINT32                                       ulDrvDivBandsHigh;
    VOS_UINT16                                       usLen;

    /* ?????? */
    pRcvMsg  = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent = (DRV_AGENT_QRY_RXDIV_CNF_STRU *)pRcvMsg->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryRxdivCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryRxdivCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_RXDIV_QRY_REQ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    usLen                  = 0;
    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        At_CovertMsInternalRxDivParaToUserSet(pstEvent->usDrvDivBands,
                                             &ulDrvDivBandsLow,
                                             &ulDrvDivBandsHigh);
        At_CovertMsInternalRxDivParaToUserSet(pstEvent->usCurBandSwitch,
                                             &ulUserDivBandsLow,
                                             &ulUserDivBandsHigh);

        usLen +=  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (TAF_CHAR *)pgucAtSndCodeAddr,
                                         (TAF_CHAR*)pgucAtSndCodeAddr,
                                         "%s:",
                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        if (0 != ulDrvDivBandsHigh)
        {
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                            "%d,%X%08X,",
                                            0,
                                            ulDrvDivBandsHigh,ulDrvDivBandsLow);
        }
        else
        {
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                            "%d,%X,",
                                            0,
                                            ulDrvDivBandsLow);
        }

        if (0 != ulUserDivBandsHigh)
        {
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                            "%X%08X",
                                            ulUserDivBandsHigh,
                                            ulUserDivBandsLow);
        }
        else
        {
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                            "%X",
                                            ulUserDivBandsLow);
        }
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                        "\r\n");
        usLen +=  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (TAF_CHAR *)pgucAtSndCodeAddr,
                                         (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                         "%s:",
                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                        "%d,%X,%X",
                                        1,
                                        0,
                                        0);
        gstAtSendData.usBufLen = usLen;

        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_CME_UNKNOWN;
    }

    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;
}

VOS_UINT32 AT_RcvDrvAgentSetRxdivCnf(VOS_VOID *pMsg)
{
    VOS_UINT8                                        ucIndex;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_AT_RXDIV_CNF_STRU                     *pstEvent;

    /* ?????? */
    pRcvMsg  = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent = (DRV_AGENT_AT_RXDIV_CNF_STRU *)pRcvMsg->aucContent;


    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetRxdivCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetRxdivCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_RXDIV_SET_REQ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    if( DRV_AGENT_CME_RX_DIV_OTHER_ERR == pstEvent->ulResult )
    {
        gstAtSendData.usBufLen = 0;

        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_FormatResultData(ucIndex, AT_CME_RX_DIV_OTHER_ERR);

        return VOS_ERR;
    }

    if( DRV_AGENT_CME_RX_DIV_NOT_SUPPORTED == pstEvent->ulResult )
    {
        gstAtSendData.usBufLen = 0;

        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_FormatResultData(ucIndex, AT_CME_RX_DIV_NOT_SUPPORTED);

        return VOS_ERR;
    }

    if( AT_DSP_RF_SWITCH_ON == pstEvent->ucRxOnOff )
    {
        if( DRV_AGENT_CME_RX_DIV_BAND_ERR == pstEvent->ulResult )
        {
            gstAtSendData.usBufLen = 0;

            AT_STOP_TIMER_CMD_READY(ucIndex);

            At_FormatResultData(ucIndex, AT_CME_RX_DIV_NOT_SUPPORTED);

            return VOS_ERR;
        }

        if (AT_FAILURE == At_SendRfCfgAntSelToHPA(AT_RX_DIV_ON, ucIndex))
        {
            gstAtSendData.usBufLen = 0;

            AT_STOP_TIMER_CMD_READY(ucIndex);

            At_FormatResultData(ucIndex, AT_CME_RX_DIV_OTHER_ERR);

            return VOS_ERR;
        }

        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SET_RXDIV;
        g_stAtDevCmdCtrl.ucIndex               = ucIndex;
        g_stAtDevCmdCtrl.usOrigBand            = pstEvent->usSetDivBands;

        /* ???????????????????? */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        /* Added by f62575 for SMALL IMAGE, 2012-1-3, begin */
        gstAtSendData.usBufLen = 0;

        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_FormatResultData(ucIndex, AT_ERROR);
        /* Added by f62575 for SMALL IMAGE, 2012-1-3, end   */
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentSetNvRestoreCnf(VOS_VOID *pMsg)
{
    VOS_UINT8                                        ucIndex;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_NVRESTORE_RST_STRU                *pstEvent;

    /* ?????? */
    pRcvMsg                 = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent                = (DRV_AGENT_NVRESTORE_RST_STRU *)pRcvMsg->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetNvRestoreCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetNvRestoreCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    if (AT_CMD_NVRESTORE_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%d",
                                                    pstEvent->ulResult);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;

}


VOS_UINT32 AT_RcvDrvAgentQryNvRestoreRstCnf(VOS_VOID *pMsg)
{
    VOS_UINT8                                        ucIndex;
    VOS_UINT32                                       ulRestoreStatus;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_NVRESTORE_RST_STRU                    *pstEvent;

    /* ?????? */
    pRcvMsg                 = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent                = (DRV_AGENT_NVRESTORE_RST_STRU *)pRcvMsg->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryNvRestoreRstCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryNvRestoreRstCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    if (AT_CMD_NVRSTSTTS_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ((AT_NV_RESTORE_RESULT_INIT == pstEvent->ulResult)
     || (AT_NV_RESTORE_RUNNING == pstEvent->ulResult))
    {
        ulRestoreStatus = AT_NV_RESTORE_FAIL;
    }
    else if (VOS_OK == pstEvent->ulResult)
    {
        ulRestoreStatus = AT_NV_RESTORE_SUCCESS;
    }
    else
    {
        ulRestoreStatus = AT_NV_RESTORE_FAIL;
    }
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%d",
                                                     ulRestoreStatus);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;

}


VOS_UINT32 AT_RcvDrvAgentNvRestoreManuDefaultRsp(VOS_VOID *pMsg)
{
    VOS_UINT8                                        ucIndex;
    VOS_UINT32                                       ulRst;
    VOS_UINT32                                       ulResult;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_NVRESTORE_RST_STRU                    *pstEvent;

    /* ?????? */
    pRcvMsg                 = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent                = (DRV_AGENT_NVRESTORE_RST_STRU *)pRcvMsg->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNvRestoreManuDefaultRsp: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNvRestoreManuDefaultRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    if (AT_CMD_F_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    ulResult = pstEvent->ulResult;
    if ( NV_OK != ulResult )
    {
        ulRst = AT_ERROR;
    }
    else
    {
        g_bSetFlg = VOS_TRUE;

        /* E5????APP????????????  */
        AT_PhSendRestoreFactParm();

        ulRst = AT_OK;
    }
    At_FormatResultData(ucIndex, ulRst);

    return VOS_OK;

}



VOS_UINT32  AT_GetImeiValue(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           aucImei[TAF_PH_IMEI_LEN + 1]
)
{
    NV_SC_PERS_CTRL_STRU                    stScPersCtrl;
    VOS_UINT8                               aucBuf[TAF_PH_IMEI_LEN + 1];
    VOS_UINT8                               ucCheckData;
    VOS_UINT32                              ulDataLen;
    VOS_UINT32                              i;

    ucCheckData = 0;
    ulDataLen   = TAF_PH_IMEI_LEN;


    TAF_MEM_SET_S(aucBuf, sizeof(aucBuf), 0x00, sizeof(aucBuf));

    TAF_MEM_SET_S(&stScPersCtrl, sizeof(stScPersCtrl), 0x00, sizeof(NV_SC_PERS_CTRL_STRU));

    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_IMEI, aucBuf, ulDataLen))
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */
    {
        AT_WARN_LOG("TAF_GetImeiValue:Read IMEI Failed!");
        return VOS_ERR;
    }

    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_NV_SC_PERS_CTRL_CFG, &stScPersCtrl, sizeof(stScPersCtrl)))
    {
        AT_WARN_LOG("TAF_GetImeiValue:Read en_NV_Item_NV_SC_PERS_CTRL_CFG Failed!");
        return VOS_ERR;
    }

    /* NV 4008????????0x5a5a?????????????????????????? */
    if ((MODEM_ID_2 == enModemId)
     && (0x5A5A == stScPersCtrl.usImei0ReplaseImei2))
    {
        /* IMEI all zero */
        for (i = 0; i < ulDataLen; i++)
        {
            if (0 != aucBuf[i])
            {
                break;
            }
        }

        if (i >= ulDataLen)
        {
            TAF_MEM_SET_S(aucBuf, sizeof(aucBuf), 0x00, sizeof(aucBuf));

            if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_IMEI, aucBuf, ulDataLen))
            {
                AT_WARN_LOG("TAF_GetImeiValue:Read IMEI Failed!");
                return VOS_ERR;
            }
        }
    }

    ucCheckData = 0;
    for (i = 0; i < (TAF_PH_IMEI_LEN-2); i += 2)
    {
        ucCheckData += aucBuf[i]
                      +((aucBuf[i+1UL] + aucBuf[i+1UL])/10)
                      +((aucBuf[i+1UL] + aucBuf[i+1UL])%10);
    }
    ucCheckData = (10 - (ucCheckData%10))%10;
    AT_DeciDigit2Ascii(aucBuf, (VOS_UINT8)ulDataLen, aucImei);
    aucImei[TAF_PH_IMEI_LEN-2] = ucCheckData+0x30;
    aucImei[TAF_PH_IMEI_LEN-1] = 0;

    return VOS_OK;
}




VOS_UINT32 AT_RcvDrvAgentSetGpioplRsp(VOS_VOID *pMsg)
{

    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_GPIOPL_SET_CNF_STRU      *pstDrvAgentGpioSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pRcvMsg               = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDrvAgentGpioSetCnf = (DRV_AGENT_GPIOPL_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDrvAgentGpioSetCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentGpioplRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentGpioplRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    if (AT_CMD_GPIOPL_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_TRUE == pstDrvAgentGpioSetCnf->bFail)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ????AT_FormATResultDATa???????????? */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}




VOS_UINT32 AT_RcvDrvAgentQryGpioplRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                   *pRcvMsg;
    DRV_AGENT_GPIOPL_QRY_CNF_STRU        *pstGpioQryCnf;
    VOS_UINT16                            usLength;
    VOS_UINT32                            i;
    VOS_UINT8                             ucIndex;
    VOS_UINT32                            ulResult;

    /* ????????????????ucContent */
    pRcvMsg               = (DRV_AGENT_MSG_STRU *)pMsg;
    pstGpioQryCnf         = (DRV_AGENT_GPIOPL_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstGpioQryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryGpioplRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryGpioplRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    /* ??????????????????????AT_CMD_GPIOPL_QRY */
    if (AT_CMD_GPIOPL_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /*????AT????*/
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_TRUE != pstGpioQryCnf->bFail)
    {
        /* ???????? */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:", g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        for (i = 0; i < DRVAGENT_GPIOPL_MAX_LEN; i++)
        {
           usLength += (VOS_UINT16)At_sprintf (AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                               "%02X", pstGpioQryCnf->aucGpiopl[i]);
        }

        gstAtSendData.usBufLen = usLength;
        ulResult               = AT_OK;
    }
    else
    {
        /* ????AT_FormATResultDATa???????????? */
        gstAtSendData.usBufLen = 0;
        ulResult               = AT_ERROR;
    }
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}



VOS_UINT32 AT_RcvDrvAgentSetDatalockRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_DATALOCK_SET_CNF_STRU    *pstDatalockSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????? */
    pRcvMsg                   = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDatalockSetCnf         = (DRV_AGENT_DATALOCK_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDatalockSetCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetDatalockRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetDatalockRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    /* ??????????????????????AT_CMD_DATALOCK_SET */
    if (AT_CMD_DATALOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_TRUE != pstDatalockSetCnf->bFail)
    {
        /* ????dATalock?????? */
        g_bAtDataLocked    =  VOS_FALSE;
        ulResult           =  AT_OK;
    }
    else
    {
        ulResult           =  AT_ERROR;
    }

    /* ????AT_FormAtResultData????????????  */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
 }

/* Modified by f62575 for B050 Project, 2012-2-3, Begin   */

VOS_UINT32 AT_GetSimLockStatus(VOS_UINT8 ucIndex)
{

    /* ????????C??????SIMLOCK ???????? */
    if(TAF_SUCCESS != Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId, 0,
                                    TAF_PH_SIMLOCK_VALUE_PARA, VOS_NULL_PTR))
    {
        AT_WARN_LOG("AT_GetSimLockStatus: Taf_ParaQuery fail.");
        return VOS_ERR;
    }

    /* ^SIMLOCK=2????UE??????????????AT?????????????????????????????????????????????????????? */
    if (AT_SUCCESS != At_StartTimer(AT_SET_PARA_TIME, ucIndex))
    {
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_ERR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_SIMLOCKSTATUS_READ;

    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    return VOS_OK;
}
/* Modified by f62575 for B050 Project, 2012-2-3, end   */


VOS_UINT32 AT_RcvDrvAgentQryTbatvoltRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_TBATVOLT_QRY_CNF_STRU    *pstTbatvoltQryCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????? */
    pRcvMsg                   = (DRV_AGENT_MSG_STRU *)pMsg;
    pstTbatvoltQryCnf         = (DRV_AGENT_TBATVOLT_QRY_CNF_STRU *)pRcvMsg->aucContent;


    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstTbatvoltQryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryTbatvoltRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryTbatvoltRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    /*??????????????????????AT_CMD_TBATVOLT_QRY*/
    if (AT_CMD_TBATVOLT_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if (VOS_TRUE != pstTbatvoltQryCnf->bFail)
    {

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:%d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstTbatvoltQryCnf->lBatVol);
        ulResult = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulResult = AT_ERROR;
    }

    /* ????AT_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


VOS_VOID At_RcvVcMsgQryModeCnfProc(MN_AT_IND_EVT_STRU *pstData)
{

    MN_AT_IND_EVT_STRU                  *pRcvMsg;
    APP_VC_EVENT_INFO_STRU              *pstEvent;
    VOS_UINT8                            ucIndex;
    VOS_UINT16                           usVoiceMode;
    VOS_UINT16                           usDevMode;
    VOS_UINT32                           ulRet;


    /* ?????? */
    pRcvMsg         = pstData;
    pstEvent        = (APP_VC_EVENT_INFO_STRU *)pstData->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryModeCnfProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryModeCnfProc : AT_BROADCAST_INDEX.");
        return;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    /* ??????VMSET???????? */
    if (AT_CMD_VMSET_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        usDevMode = pstEvent->enDevMode;

        /* ????????????????????ERROR */
        if (usDevMode >= VC_PHY_DEVICE_MODE_BUTT)
        {
            gstAtSendData.usBufLen = 0;
            ulRet = AT_ERROR;
        }
        else
        {
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            "%s: %d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            usDevMode);
            ulRet = AT_OK;
        }
    }
    /* ??????CVOICE???????? */
    /* Modified by s62952 for BalongV300R002 Build???????? 2012-02-28, begin */
    else if ( AT_CMD_CVOICE_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* ????????????VC???????? */
        usVoiceMode     = APP_VC_VcPhyVoiceMode2AppVcVoiceMode(pstEvent->enDevMode);

        /* ????????????????????ERROR */
        if (usVoiceMode >= APP_VC_VOICE_MODE_BUTT)
        {
            gstAtSendData.usBufLen = 0;
            ulRet = AT_ERROR;
        }
        else
        {
            gstAtSendData.usBufLen =(VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                                           "%s: %d, %d, %d, %d",
                                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                           usVoiceMode,
                                                           AT_PCVOICE_SAMPLE_RATE,
                                                           AT_PCVOICE_DATA_BIT,
                                                           AT_PCVOICE_FRAME_PERIOD);
            ulRet = AT_OK;
        }
    }
    /* Modified by s62952 for BalongV300R002 Build???????? 2012-02-28, begin */
    else
    {
        return;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;
}


VOS_VOID At_RcvVcMsgSetPortCnfProc(MN_AT_IND_EVT_STRU *pstData)
{
    MN_AT_IND_EVT_STRU                 *pRcvMsg;
    APP_VC_EVENT_INFO_STRU             *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;

    /* ?????? */
    pRcvMsg         = pstData;
    pstEvent        = (APP_VC_EVENT_INFO_STRU *)pstData->aucContent;


    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetPortCnfProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetPortCnfProc : AT_BROADCAST_INDEX.");
        return;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    if (VOS_TRUE == pstEvent->bSuccess)
    {
        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;

}


VOS_VOID At_RcvVcMsgQryPortCnfProc(MN_AT_IND_EVT_STRU *pstData)
{
    MN_AT_IND_EVT_STRU                  *pRcvMsg;
    APP_VC_EVENT_INFO_STRU              *pstEvent;
    VOS_UINT8                            ucIndex;
    APP_VC_VOICE_PORT_ENUM_U8            ucVoicePort;                           /* ?????????????? */
    VOS_UINT32                           ulRet;

    /* ?????? */
    pRcvMsg         = pstData;
    pstEvent        = (APP_VC_EVENT_INFO_STRU *)pstData->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryPortCnfProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryPortCnfProc : AT_BROADCAST_INDEX.");
        return;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    /* ???????????? */
    ucVoicePort = pstEvent->enVoicePort;

    if (APP_VC_VOICE_PORT_BUTT > ucVoicePort)
    {
        gstAtSendData.usBufLen =
            (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   "%s: %d",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   ucVoicePort);
        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;

}


VOS_UINT32 AT_RcvRnicDsflowRsp(MsgBlock *pstMsg)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    RNIC_DATA_RATE_STRU                 stCurrentRateInfo;
    RNIC_AT_DSFLOW_RSP_STRU            *pstRcvMsg;

    usLength                            = 0;
    pstRcvMsg                           = (RNIC_AT_DSFLOW_RSP_STRU *)pstMsg;
    stCurrentRateInfo.ulULDataRate      = pstRcvMsg->stRnicDataRate.ulULDataRate;
    stCurrentRateInfo.ulDLDataRate      = pstRcvMsg->stRnicDataRate.ulDLDataRate;

    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryPortCnfProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryPortCnfProc : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    usLength =  (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       stCurrentRateInfo.ulULDataRate);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",%d",
                                       stCurrentRateInfo.ulDLDataRate);

    gstAtSendData.usBufLen = usLength;

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}

VOS_UINT32 AT_RcvRnicDialModeCnf(MsgBlock *pstMsg)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    RNIC_AT_DIAL_MODE_CNF_STRU         *pstRcvMsg;

    usLength                            = 0;
    pstRcvMsg                           = (RNIC_AT_DIAL_MODE_CNF_STRU *)pstMsg;

    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvRnicDialModeCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvRnicDialModeCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    usLength =  (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR*)pgucAtSndCodeAddr,
                                        "%s:",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "%d",
                                        pstRcvMsg->ulDialMode);

    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        ",%d",
                                        pstRcvMsg->ulEventReportFlag);

    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                         ",%d",
                                         pstRcvMsg->ulIdleTime);

    gstAtSendData.usBufLen = usLength;

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


VOS_VOID At_ZeroReplaceBlankInString( VOS_UINT8 *pData, VOS_UINT32 ulLen)
{
    TAF_UINT32 ulChkLen  = 0;
    TAF_UINT8  *pWrite   = pData;
    TAF_UINT8  *pRead    = pData;

    /* ???????????? */
    while ( ulChkLen < ulLen )
    {
        /* ???????? May  5 2011 17:08:00
           ??????   May 05 2011 17:08:00 */
        if (' ' == *pRead++)
        {
            if (' ' == *pRead)
            {
                pWrite++;
                *pWrite = '0';
                pRead++;
                ulChkLen++;
            }
        }
        pWrite++;
        ulChkLen++;
    }

    return;
}



VOS_UINT32 AT_RcvDrvAgentQryVersionRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_VERSION_QRY_CNF_STRU     *pstVersionQryCnfInfo;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulLen;
    VOS_CHAR                            acTmpTime[AT_AGENT_DRV_VERSION_TIME_LEN] = {0};
    VOS_UINT16                          usLength;
    VOS_BOOL                            bPhyNumIsNull;

    VOS_UINT32                          ulOpt;
    /* Modify by f62575 for V7????????, 2012-04-07, Begin   */
    VOS_UINT32                          ulRet;
    TAF_NVIM_CS_VER_STRU                stCsver;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

    stCsver.usCsver = 0;

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_Csver, &(stCsver.usCsver), sizeof(stCsver.usCsver));
    if (NV_OK != ulRet)
    {
        return AT_ERROR;
    }
    /* Modify by f62575 for V7????????, 2012-04-07, End   */

    /* ????????????????ucContent */
    ulLen                        = 0;
    pRcvMsg                      = (DRV_AGENT_MSG_STRU *)pMsg;
    pstVersionQryCnfInfo         = (DRV_AGENT_VERSION_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstVersionQryCnfInfo->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryVersionRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryVersionRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    /* ??????????????????????AT_CMD_VERSION_QRY/AT_CMD_RSFR_VERSION_QRY, ^RSFR???????????????? */
    if ((AT_CMD_VERSION_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
        && (AT_CMD_RSFR_VERSION_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt))
    {
        return VOS_ERR;
    }

    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RcvDrvAgentQryVersionRsp: Get modem id fail.");
        return VOS_ERR;
    }

    ulOpt = gastAtClientTab[ucIndex].CmdCurrentOpt;

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /*???????? */
    if(DRV_AGENT_VERSION_QRY_NO_ERROR != pstVersionQryCnfInfo->enResult)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_OK;
    }

    /*??????????????????????????????????????????????????????????0???? */
    ulLen = VOS_StrLen(pstVersionQryCnfInfo->acVerTime);
    TAF_MEM_CPY_S(acTmpTime, sizeof(acTmpTime), pstVersionQryCnfInfo->acVerTime, ulLen + 1);
    At_ZeroReplaceBlankInString((VOS_UINT8 *)acTmpTime, ulLen);

    /* ???????????? */
    usLength = TAF_CDROM_VERSION_LEN;
    At_DelCtlAndBlankCharWithEndPadding(pstVersionQryCnfInfo->stIsoVer.aucIsoInfo, &usLength);

    /* ???????????????????????? */
    if (AT_OK != AT_PhyNumIsNull(enModemId, AT_PHYNUM_TYPE_IMEI, &bPhyNumIsNull))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryVersionRsp(): AT_PhyNumIsNull Error!");
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_OK;
    }
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

    usLength = 0;

    /* ??????????????????????????????????????????????????????????????????????????????
       ?????????????????????????????????????????????????????????????????????????? */
    if (VOS_FALSE == g_bAtDataLocked || (VOS_TRUE == bPhyNumIsNull))
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:BDT:%s%s",
                                           "^VERSION", acTmpTime, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTS:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stSoftVersion.aucRevisionId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTS:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stSoftVersion.aucRevisionId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTD:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stIsoVer.aucIsoInfo, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTD:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stIsoVer.aucIsoInfo,gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTH:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stInterHwVer.aucHwVer, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTH:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stFullHwVer.aucHwVer, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTU:%s%s",
                                           "^VERSION",pstVersionQryCnfInfo->stModelId.aucModelId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTU:%s%s",
                                           "^VERSION",pstVersionQryCnfInfo->stInterModelId.aucModelId, gaucAtCrLf);

        /* Modify by f62575 for V7????????, 2012-04-07, Begin   */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:CFG:%d%s",
                                           "^VERSION",stCsver.usCsver, gaucAtCrLf);
        /* Modify by f62575 for V7????????, 2012-04-07, End   */

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:PRL:",
                                           "^VERSION");

        gstAtSendData.usBufLen = usLength;
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:BDT:%s%s",
                                           "^VERSION", acTmpTime, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTS:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stSoftVersion.aucRevisionId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTS:%s",
                                           "^VERSION", gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTD:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stIsoVer.aucIsoInfo, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTD:%s",
                                           "^VERSION", gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTH:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stInterHwVer.aucHwVer, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTH:%s",
                                           "^VERSION", gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTU:%s%s",
                                           "^VERSION",pstVersionQryCnfInfo->stModelId.aucModelId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTU:%s",
                                           "^VERSION", gaucAtCrLf);

        /* Modify by f62575 for V7????????, 2012-04-07, Begin   */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:CFG:%d%s",
                                           "^VERSION",stCsver.usCsver, gaucAtCrLf);
        /* Modify by f62575 for V7????????, 2012-04-07, End   */

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:PRL:",
                                           "^VERSION");

        gstAtSendData.usBufLen = usLength;
    }

    /* ??????^RSFR??????????????VERSION??????????,????^RSFR?????????? */
    if(AT_CMD_RSFR_VERSION_QRY == ulOpt)
    {
        AT_SetRsfrVersionCnf(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

        /* AT??????????????AT_SetRsfrVersionCnf?????? */
        return VOS_OK;
    }

    At_FormatResultData(ucIndex, AT_OK);
    return VOS_OK;

}



VOS_UINT32 AT_SetGlobalFchan(VOS_UINT8 ucRATMode)
{
    g_stAtDevCmdCtrl.ucDeviceRatMode = ucRATMode;

    return VOS_OK;
}



VOS_UINT32 AT_SetFchanRspErr(DRV_AGENT_FCHAN_SET_ERROR_ENUM_UINT32  enResult)
{
    if(DRV_AGENT_FCHAN_BAND_NOT_MATCH == enResult)
    {
        return AT_FCHAN_BAND_NOT_MATCH;
    }

    if(DRV_AGENT_FCHAN_BAND_CHANNEL_NOT_MATCH == enResult)
    {
        return AT_FCHAN_BAND_CHANNEL_NOT_MATCH;
    }

    if(DRV_AGENT_FCHAN_OTHER_ERR == enResult)
    {
        g_stAtDevCmdCtrl.bDspLoadFlag = VOS_FALSE;
        AT_WARN_LOG("AT_SetFChanPara: DSP Load fail!");
        return AT_FCHAN_OTHER_ERR;
    }

    return DRV_AGENT_FCHAN_SET_NO_ERROR;

}



VOS_UINT32 AT_RcvDrvAgentSetFchanRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_FCHAN_SET_CNF_STRU       *pstFchanSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulError;

    /* ?????? */
    pRcvMsg          = (DRV_AGENT_MSG_STRU *)pMsg;
    pstFchanSetCnf   = (DRV_AGENT_FCHAN_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstFchanSetCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetFchanRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetFchanRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    /* ??????????????????????AT_CMD_FCHAN_SET */
    if (AT_CMD_FCHAN_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????? */
    ulError =  AT_SetFchanRspErr(pstFchanSetCnf->enResult);
    if(DRV_AGENT_FCHAN_SET_NO_ERROR != ulError)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, ulError);
        return VOS_OK;
    }

    /* ???????????????? */
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_TRUE;
    g_stAtDevCmdCtrl.ucDeviceRatMode = (VOS_UINT8)pstFchanSetCnf->stFchanSetReq.ucDeviceRatMode;
    g_stAtDevCmdCtrl.ucDeviceAtBand  = (VOS_UINT8)pstFchanSetCnf->stFchanSetReq.ucDeviceAtBand;
    g_stAtDevCmdCtrl.stDspBandArfcn  = pstFchanSetCnf->stFchanSetReq.stDspBandArfcn;
    g_stAtDevCmdCtrl.usFDAC          = 0;                                       /* FDAC??????????G/W???????? */

    /* ????AT_FormATResultDATa???????????? */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex,AT_OK);
    return VOS_OK;
}



VOS_UINT32 AT_GetRxpriErr(DRV_AGENT_ERROR_ENUM_UINT32 enResult)
{
    if(DRV_AGENT_CME_RX_DIV_OTHER_ERR == enResult)
    {
        return AT_CME_RX_DIV_OTHER_ERR;
    }

    if(DRV_AGENT_CME_RX_DIV_NOT_SUPPORTED == enResult)
    {
        return AT_CME_RX_DIV_NOT_SUPPORTED;
    }

    return AT_OK;
}


VOS_VOID AT_SupportHsdpa(
    AT_NVIM_UE_CAPA_STRU               *pstUECapa,
    VOS_BOOL                           *pbSupportHsdpa
    )
{

    /* ??????????????DPA */
    *pbSupportHsdpa = VOS_FALSE;

    if (pstUECapa->enAsRelIndicator >= 2)
    {
        if (1 == pstUECapa->ulHspaStatus)
        {
            if (PS_TRUE == pstUECapa->enHSDSCHSupport)
            {
                *pbSupportHsdpa = VOS_TRUE;
            }
        }
        else
        {
            *pbSupportHsdpa = VOS_TRUE;
        }
    }
}



VOS_VOID AT_SupportHsupa(
    AT_NVIM_UE_CAPA_STRU               *pstUECapa,
    VOS_BOOL                           *pbSupportHsupa
)
{

    /* ??????????????UPA */
    *pbSupportHsupa = VOS_FALSE;

    if (pstUECapa->enAsRelIndicator >= 3)
    {
       if (1 == pstUECapa->ulHspaStatus)
       {
           if (PS_TRUE == pstUECapa->enEDCHSupport)
           {
               *pbSupportHsupa = VOS_TRUE;
           }
       }
       else
       {
            *pbSupportHsupa = VOS_TRUE;
       }
    }
}


VOS_UINT32 AT_GetWFeatureInfo(
    AT_FEATURE_SUPPORT_ST              *pstFeATure,
    DRV_AGENT_SFEATURE_QRY_CNF_STRU    *pstAtAgentSfeatureQryCnf
)
{
    AT_NVIM_UE_CAPA_STRU                stUECapa;
    VOS_UINT32                          ulLen;
    VOS_BOOL                            bSupportHsdpa;
    VOS_BOOL                            bSupportHsupa;
    VOS_UINT8                           aucStrTmp[50] = {0};
    VOS_UINT8                           aucStrDiv[AT_SFEATURE_DIV_STRING_LEN];
    VOS_UINT32                          ulDivLen;


    bSupportHsdpa = VOS_FALSE;
    bSupportHsupa = VOS_FALSE;

    TAF_MEM_SET_S(&stUECapa, sizeof(stUECapa), 0x00, sizeof(stUECapa));


    /* ????HSPA,HSPA+???????? */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WAS_RadioAccess_Capa_New, &stUECapa,
                        sizeof(AT_NVIM_UE_CAPA_STRU)))
    {
        AT_WARN_LOG("AT_GetWFeatureInfo: en_NV_Item_WAS_RadioAccess_Capa NV Read  Fail!");
        return VOS_ERR;
    }

    /* ????Wcdma???????? */
    /* !!!??????????????aucStrTmp ????????????!!! */
    ulLen = (VOS_UINT32)AT_GetWcdmaBandStr(aucStrTmp,&(pstAtAgentSfeatureQryCnf->stBandFeature));

    /* HSPA+???????? */
    if ((stUECapa.enAsRelIndicator >= 4)
     && (PS_TRUE == stUECapa.enMacEhsSupport)
     && (stUECapa.ucHSDSCHPhyCategory >= 10)
     && (0 != stUECapa.ucHSDSCHPhyCategoryExt)
     && (PS_TRUE == stUECapa.enHSDSCHSupport))
     {
        pstFeATure[AT_FEATURE_HSPAPLUS].ucFeatureFlag = AT_FEATURE_EXIST;
        TAF_MEM_CPY_S(pstFeATure[AT_FEATURE_HSPAPLUS].aucContent, sizeof(pstFeATure[AT_FEATURE_HSPAPLUS].aucContent), aucStrTmp, ulLen);
     }

    /* DPA???????? */
    AT_SupportHsdpa(&stUECapa, &bSupportHsdpa);
    if (VOS_TRUE == bSupportHsdpa)
    {
        pstFeATure[AT_FEATURE_HSDPA].ucFeatureFlag = AT_FEATURE_EXIST;
        TAF_MEM_CPY_S(pstFeATure[AT_FEATURE_HSDPA].aucContent, sizeof(pstFeATure[AT_FEATURE_HSDPA].aucContent), aucStrTmp, ulLen);
    }

    /*UPA????????*/
    AT_SupportHsupa(&stUECapa, &bSupportHsupa);
    if(VOS_TRUE == bSupportHsupa)
    {
        pstFeATure[AT_FEATURE_HSUPA].ucFeatureFlag = AT_FEATURE_EXIST;
        TAF_MEM_CPY_S(pstFeATure[AT_FEATURE_HSUPA].aucContent, sizeof(pstFeATure[AT_FEATURE_HSUPA].aucContent), aucStrTmp, ulLen);
    }


    /* ???????? */
    pstFeATure[AT_FEATURE_DIVERSITY].ucFeatureFlag = AT_FEATURE_EXIST;
    /* UMTS??????????????*/
    TAF_MEM_SET_S(aucStrDiv, sizeof(aucStrDiv), 0x00, sizeof(aucStrDiv));

    /* !!!??????????????aucStrDiv ????????????!!! */
    ulDivLen = (VOS_UINT32)AT_GetWcdmaDivBandStr(aucStrDiv);

    TAF_MEM_CPY_S(pstFeATure[AT_FEATURE_DIVERSITY].aucContent, sizeof(pstFeATure[AT_FEATURE_DIVERSITY].aucContent), aucStrDiv, ulDivLen);

    /* UMTS */
    pstFeATure[AT_FEATURE_UMTS].ucFeatureFlag = AT_FEATURE_EXIST;
    TAF_MEM_CPY_S(pstFeATure[AT_FEATURE_UMTS].aucContent, sizeof(pstFeATure[AT_FEATURE_UMTS].aucContent), aucStrTmp, ulLen);

    return VOS_OK;

}



VOS_VOID AT_GetGFeatureInfo(
    AT_FEATURE_SUPPORT_ST              *pstFeATure,
    DRV_AGENT_SFEATURE_QRY_CNF_STRU    *pstATAgentSfeatureQryCnf
)
{
    VOS_UINT32                          ulLen;

    VOS_UINT16                          usEgprsFlag;
    VOS_UINT8                           aucStrTmp[50] = {0};


    usEgprsFlag = 0;


    /* ????GSM???????? */
    /* !!!??????????????aucStrDiv ????????????!!! */
    ulLen = (VOS_UINT32)AT_GetGsmBandStr(aucStrTmp,&(pstATAgentSfeatureQryCnf->stBandFeature));

    if ( 0 == ulLen )
    {
        (VOS_VOID)vos_printf("AT_GetGFeatureInfo, Not Support G.\n");
        return;
    }

    /* ????EDGE???????? */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Egprs_Flag, &usEgprsFlag,
                        sizeof(VOS_UINT16)))
    {
        AT_WARN_LOG("AT_GetGFeatureInfo: en_NV_Item_Egprs_Flag NV Read  Fail!");
        pstFeATure[AT_FEATURE_EDGE].ucFeatureFlag = AT_FEATURE_EXIST;
        TAF_MEM_CPY_S(pstFeATure[AT_FEATURE_EDGE].aucContent, sizeof(pstFeATure[AT_FEATURE_EDGE].aucContent), aucStrTmp, ulLen);
    }
    else
    {
        if (usEgprsFlag != 0)
        {
            pstFeATure[AT_FEATURE_EDGE].ucFeatureFlag = AT_FEATURE_EXIST;
            TAF_MEM_CPY_S(pstFeATure[AT_FEATURE_EDGE].aucContent, sizeof(pstFeATure[AT_FEATURE_EDGE].aucContent), aucStrTmp, ulLen);
        }
    }

    /* GPRS */
    pstFeATure[AT_FEATURE_GPRS].ucFeatureFlag = AT_FEATURE_EXIST;
    TAF_MEM_CPY_S(pstFeATure[AT_FEATURE_GPRS].aucContent, sizeof(pstFeATure[AT_FEATURE_GPRS].aucContent), aucStrTmp, ulLen);

    /* GSM */
    pstFeATure[AT_FEATURE_GSM].ucFeatureFlag = AT_FEATURE_EXIST;
    TAF_MEM_CPY_S(pstFeATure[AT_FEATURE_GSM].aucContent, sizeof(pstFeATure[AT_FEATURE_GSM].aucContent), aucStrTmp, ulLen);
}


VOS_UINT32 AT_GetTdsFeatureInfo(AT_FEATURE_SUPPORT_ST * pstFeATure)
{
    VOS_UINT32 ulRst  = 0;
    NVIM_UE_TDS_SUPPORT_FREQ_BAND_LIST_STRU stTdsFeature;
    VOS_UINT32 i = 0;
    VOS_UINT32 ulLen;


    TAF_MEM_SET_S(&stTdsFeature, sizeof(stTdsFeature), 0x00, sizeof(stTdsFeature));

    ulRst = NV_ReadEx(MODEM_ID_0, en_NV_Item_UTRAN_TDD_FREQ_BAND, &stTdsFeature, sizeof(NVIM_UE_TDS_SUPPORT_FREQ_BAND_LIST_STRU));
    if( ulRst != ERR_MSP_SUCCESS )
    {
        (VOS_VOID)vos_printf("Read EN_NV_ID_TDS_SUPPORT_FREQ_BAND failed:0x%x.\n", en_NV_Item_UTRAN_TDD_FREQ_BAND);
        return ERR_MSP_FAILURE;
    }
    if(stTdsFeature.ucBandCnt > NVIM_TDS_MAX_SUPPORT_BANDS_NUM)
    {
        (VOS_VOID)vos_printf("Read en_NV_Item_UTRAN_TDD_FREQ_BAND stTdsFeature.ucBandCnt:%d.\n", stTdsFeature.ucBandCnt);
        return ERR_MSP_FAILURE;
    }

    /* ????NV??????????TDS */
    pstFeATure[AT_FEATURE_TDSCDMA].ucFeatureFlag = AT_FEATURE_EXIST;

    ulLen = 0;

    /* BandA:2000Hz, BanE:2300Hz, BandF:1900Hz */
    for(i = 0; i < stTdsFeature.ucBandCnt; i++)
    {
        if(ID_NVIM_TDS_FREQ_BAND_A == stTdsFeature.aucBandNo[i])
        {
            VOS_sprintf_s((VOS_CHAR*)(pstFeATure[AT_FEATURE_TDSCDMA].aucContent + ulLen), AT_FEATURE_CONTENT_LEN_MAX - ulLen, "2000,");
            ulLen = VOS_StrLen((VOS_CHAR *)pstFeATure[AT_FEATURE_TDSCDMA].aucContent);
            continue;
        }

        if(ID_NVIM_TDS_FREQ_BAND_E == stTdsFeature.aucBandNo[i])
        {
            VOS_sprintf_s((VOS_CHAR*)(pstFeATure[AT_FEATURE_TDSCDMA].aucContent + ulLen), AT_FEATURE_CONTENT_LEN_MAX - ulLen, "2300,");
            ulLen = VOS_StrLen((VOS_CHAR *)pstFeATure[AT_FEATURE_TDSCDMA].aucContent);
            continue;
        }

        if(ID_NVIM_TDS_FREQ_BAND_F == stTdsFeature.aucBandNo[i])
        {
            VOS_sprintf_s((VOS_CHAR*)(pstFeATure[AT_FEATURE_TDSCDMA].aucContent + ulLen), AT_FEATURE_CONTENT_LEN_MAX - ulLen, "1900,");
            ulLen = VOS_StrLen((VOS_CHAR *)pstFeATure[AT_FEATURE_TDSCDMA].aucContent);
            continue;
        }
    }

    if(ulLen > 0)
    {
        /* ?????????????????? */
        pstFeATure[AT_FEATURE_TDSCDMA].aucContent[ulLen - 1] = '\0';
    }

    return ERR_MSP_SUCCESS;
}


VOS_UINT32 AT_RcvDrvAgentQrySfeatureRsp(VOS_VOID *pMsg)
{
    /* ?????? */
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_SFEATURE_QRY_CNF_STRU    *pstAtAgentSfeatureQryCnf;
    VOS_UINT8                           ucIndex;
    AT_FEATURE_SUPPORT_ST              *pstFeATure;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulReult;
    VOS_UINT8                           ucFeATrueNum;
    VOS_UINT8                           ucIndexTmp;
    VOS_UINT8                           aucFeATureName[][AT_FEATURE_NAME_LEN_MAX] =
                                        {
                                            "LTE",
                                            "HSPA+",
                                            "HSDPA",
                                            "HSUPA",
                                            "DIVERSITY",
                                            "UMTS",
                                            "EVDO",
                                            "EDGE",
                                            "GPRS",
                                            "GSM",
                                            "CDMA1X",
                                            "WIMAX",
                                            "WIFI",
                                            "GPS",
                                            "TD"
                                        };

    pRcvMsg                      = (DRV_AGENT_MSG_STRU*)pMsg;
    pstAtAgentSfeatureQryCnf     = (DRV_AGENT_SFEATURE_QRY_CNF_STRU*)pRcvMsg->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstAtAgentSfeatureQryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQrySfeatureRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQrySfeatureRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    /*??????????????????????AT_CMD_SFEATURE_QRY */
    if (AT_CMD_SFEATURE_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    pstFeATure = (AT_FEATURE_SUPPORT_ST*)PS_MEM_ALLOC(WUEPS_PID_AT, AT_FEATURE_MAX*sizeof(AT_FEATURE_SUPPORT_ST));
    if (VOS_NULL == pstFeATure)
    {
        AT_WARN_LOG("AT_RcvDrvAgentQrySfeatureRsp: GET MEM Fail!");
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_OK;
    }
    TAF_MEM_SET_S(pstFeATure, AT_FEATURE_MAX*sizeof(AT_FEATURE_SUPPORT_ST), 0x00, AT_FEATURE_MAX*sizeof(AT_FEATURE_SUPPORT_ST));

    ulReult = AT_GetWFeatureInfo(pstFeATure,pstAtAgentSfeatureQryCnf);
    if (VOS_OK != ulReult)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        PS_MEM_FREE(WUEPS_PID_AT, pstFeATure);
        return VOS_OK;
    }

/* Modify by f62575 for V7????????, 2012-04-07, Begin   */
    ulReult = AT_GetLteFeatureInfo(pstFeATure);
    if (VOS_OK != ulReult)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        PS_MEM_FREE(WUEPS_PID_AT, pstFeATure);
        return VOS_OK;
    }
/* Modify by f62575 for V7????????, 2012-04-07, End   */

    ulReult = AT_GetTdsFeatureInfo(pstFeATure);
    if (VOS_OK != ulReult)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        PS_MEM_FREE(WUEPS_PID_AT, pstFeATure);
        return VOS_OK;
    }

    AT_GetGFeatureInfo(pstFeATure,pstAtAgentSfeatureQryCnf);

    /* Modified by s62952 for BalongV300R002 Build???????? 2012-02-28, begin */
    if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        /* WIFI */
        pstFeATure[AT_FEATURE_WIFI].ucFeatureFlag = AT_FEATURE_EXIST;
        VOS_sprintf_s((VOS_CHAR*)pstFeATure[AT_FEATURE_WIFI].aucContent, sizeof(pstFeATure[AT_FEATURE_WIFI].aucContent), "B,G,N");
    }
    /* Modified by s62952 for BalongV300R002 Build???????? 2012-02-28, begin */

    /* ?????????????????? */
    ucFeATrueNum = 0;
    for (ucIndexTmp = 0; ucIndexTmp < AT_FEATURE_MAX; ucIndexTmp++)
    {
        TAF_MEM_CPY_S(pstFeATure[ucIndexTmp].aucFeatureName, sizeof(pstFeATure[ucIndexTmp].aucFeatureName), aucFeATureName[ucIndexTmp],sizeof(aucFeATureName[ucIndexTmp]));
        if (AT_FEATURE_EXIST == pstFeATure[ucIndexTmp].ucFeatureFlag)
        {
            ucFeATrueNum++;
        }
    }

    ulLen = 0;
    /* ???????????????????? */
    ulLen = (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr + ulLen,
                                   "%s:%d%s",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   ucFeATrueNum,
                                   gaucAtCrLf);

    /* ?????????????????????? */
    for (ucIndexTmp = 0; ucIndexTmp < AT_FEATURE_MAX; ucIndexTmp++)
    {
        if (AT_FEATURE_EXIST == pstFeATure[ucIndexTmp].ucFeatureFlag)
        {
            ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + ulLen,
                                           "%s:%s,%s%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstFeATure[ucIndexTmp].aucFeatureName,
                                           pstFeATure[ucIndexTmp].aucContent,
                                           gaucAtCrLf);
        }
    }

    gstAtSendData.usBufLen = (VOS_UINT16)(ulLen - (VOS_UINT32)VOS_StrLen((VOS_CHAR*)gaucAtCrLf));

    At_FormatResultData(ucIndex, AT_OK);
    PS_MEM_FREE(WUEPS_PID_AT, pstFeATure);
    return VOS_OK;

}



VOS_UINT32 AT_RcvDrvAgentQryProdtypeRsp(VOS_VOID * pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_PRODTYPE_QRY_CNF_STRU    *stProdTypeCnf;
    VOS_UINT8                           ucIndex;

    /* ?????????? */
    pRcvMsg                  = (DRV_AGENT_MSG_STRU *)pMsg;
    stProdTypeCnf            = (DRV_AGENT_PRODTYPE_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ????ClientId????ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(stProdTypeCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryProdtypeRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryProdtypeRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    /* ??????????????????????AT_CMD_PRODTYPE_QRY */
    if (AT_CMD_PRODTYPE_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stProdTypeCnf->ulProdType);

    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, AT_OK);
    return VOS_OK;
}

/* Added by L60609 for AT Project??2011-10-04,  Begin*/

VOS_VOID At_ProcMsgFromDrvAgent(DRV_AGENT_MSG_STRU *pMsg)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulRst;

    /*??g_astDrvAgentMsgProcTab??????????????*/
    ulMsgCnt = sizeof(g_astAtProcMsgFromDrvAgentTab)/sizeof(AT_PROC_MSG_FROM_DRV_AGENT_STRU);

    /*??????????????MSG ID*/
    ulMsgId  = ((DRV_AGENT_MSG_STRU *)pMsg)->ulMsgId;

    /*g_astDrvAgentMsgProcTab??????????????????*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if (g_astAtProcMsgFromDrvAgentTab[i].ulMsgType == ulMsgId)
        {
            ulRst = g_astAtProcMsgFromDrvAgentTab[i].pProcMsgFunc(pMsg);

            if (VOS_ERR == ulRst)
            {
                AT_ERR_LOG("At_ProcMsgFromDrvAgent: Msg Proc Err!");
            }

            return;
        }
    }

    /*??????????????????*/
    if (ulMsgCnt == i)
    {
        AT_ERR_LOG("At_ProcMsgFromDrvAgent: Msg Id is invalid!");
    }

    return;
}


TAF_UINT32 At_PB_Unicode2UnicodePrint(TAF_UINT32 MaxLength,TAF_INT8 *headaddr,TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen)
{
    TAF_UINT16 usLen    = 0;
    TAF_UINT16 usChkLen = 0;
    TAF_UINT8  ucHigh1  = 0;
    TAF_UINT8  ucHigh2  = 0;
    TAF_UINT8 *pWrite   = pucDst;
    TAF_UINT8 *pRead    = pucSrc;

    if(((TAF_UINT32)(pucDst - (TAF_UINT8 *)headaddr) + (2 * usSrcLen)) >= MaxLength)
    {
        AT_ERR_LOG("At_Unicode2UnicodePrint too long");
        return 0;
    }

    /* ???????????? */
    while( usChkLen < usSrcLen )
    {
        /* ?????????? */
        ucHigh1 = 0x0F & (*pRead >> 4);
        ucHigh2 = 0x0F & *pRead;

        if(0x09 >= ucHigh1)   /* 0-9 */
        {
            *pWrite++ = ucHigh1 + 0x30;
        }
        else if(0x0A <= ucHigh1)    /* A-F */
        {
            *pWrite++ = ucHigh1 + 0x37;
        }
        else
        {

        }

        if(0x09 >= ucHigh2)   /* 0-9 */
        {
            *pWrite++ = ucHigh2 + 0x30;
        }
        else if(0x0A <= ucHigh2)    /* A-F */
        {
            *pWrite++ = ucHigh2 + 0x37;
        }
        else
        {

        }

        /* ?????????? */
        usChkLen++;
        pRead++;


        usLen += 2;    /* ???????? */
    }

    return usLen;
}


TAF_UINT16 At_PbGsmFormatPrint(TAF_UINT16 usMaxLength,
                               TAF_UINT8  *pucDst,
                               TAF_UINT8  *pucSrc,
                               TAF_UINT16 usSrcLen)
{
    TAF_UINT32  i;

    if (usSrcLen > usMaxLength)
    {
        AT_ERR_LOG("At_PbGsmFormatPrint error: too long");

        return 0;
    }

    for (i = 0; i < usSrcLen; i++)
    {
        /* ??????bit???? */
        pucDst[i] = pucSrc[i] & AT_PB_GSM7_CODE_MAX_VALUE;
    }

    return usSrcLen;
}


TAF_UINT32 At_PbOneUnicodeToIra(TAF_UINT16 usUnicodeChar, TAF_UINT8 *pucDst)
{
    TAF_UINT16 usIndex;

    for(usIndex = 0; usIndex < AT_PB_IRA_MAX_NUM; usIndex++)
    {
        if(usUnicodeChar == g_astIraToUnicode[usIndex].usUnicode)
        {
            *pucDst = g_astIraToUnicode[usIndex].ucOctet;

            return AT_SUCCESS;
        }
    }

    /* ??????UCS2??????IRA???? */
    AT_LOG1("At_PbOneUnicodeToIra error: no found [%x]",usUnicodeChar);

    return AT_FAILURE;
}


TAF_UINT16 At_PbUnicodeToIraFormatPrint(TAF_UINT16 usMaxLength,
                                        TAF_UINT8  *pucDst,
                                        TAF_UINT8  *pucSrc,
                                        TAF_UINT16 usSrcLen)
{
    TAF_UINT16      usIndex;
    TAF_UINT16      usRetLen = 0;
    TAF_UINT8       *pucData = pucSrc;
    TAF_UINT16      usUnicodeChar;

    /* IRA????????????UCS2?????????????? */
    usRetLen = usSrcLen >> 1;

    /* ???????????????????? */
    if (usRetLen > usMaxLength)
    {
       AT_ERR_LOG("At_PbUnicodeToIraFormatPrint error: too long");

       return 0;
    }

    /* ??????UCS2??????????????????IRA???? */
    for (usIndex = 0; usIndex < usRetLen; usIndex++)
    {
        /* ????UINT8????????UINT16 */
        usUnicodeChar = (*pucData << 8) | (*(pucData + 1));
        pucData += 2;

        if (AT_SUCCESS != At_PbOneUnicodeToIra(usUnicodeChar, &pucDst[usIndex]))
        {
            AT_ERR_LOG("At_PbUnicodeToIraFormatPrint error: no found");

            return 0;
        }
    }

    return usRetLen;
}


TAF_VOID At_PbUnicode82FormatPrint(TAF_UINT8  *puc82Code,
                                   TAF_UINT8  *pucDst,
                                   TAF_UINT16 *pusDstLen)
{

    TAF_UINT16      usIndex;
    TAF_UINT16      usBaseCode;
    TAF_UINT16      usUnicode;
    TAF_UINT16      usSrcLen;
    TAF_UINT16      usDstIndex  = 0;
    TAF_UINT16      usGsmCodeLen;
    TAF_UINT16      usGsm2UCS2CodeLen;
    TAF_UINT16      *pusUnicode = (TAF_UINT16 *)pucDst;
    TAF_UINT8       *pucSrc;

    /* ????82?????????? */
    usSrcLen = puc82Code[0];

    /* ????82??????Basecode */
    usBaseCode = (puc82Code[1] << 8) | puc82Code[2];

    if((SI_PB_ALPHATAG_MAX_LEN < usSrcLen)||(0xFFFF == usBaseCode)) /*????????????*/
    {
        *pusDstLen = 0;

        return;
    }

    /* ????82??????????, ??????????????Byte????82???????????? */
    pucSrc = puc82Code + 3;

    /* ??????????????????82?????????? */
    for(usIndex = 0; usIndex < usSrcLen; usIndex++)
    {
        usGsmCodeLen = 0;
        while((AT_PB_GSM7_CODE_MAX_VALUE >= pucSrc[usIndex + usGsmCodeLen])
           && ((usIndex + usGsmCodeLen) < usSrcLen))
        {
            usGsmCodeLen++;
        }

        if(0 != usGsmCodeLen)
        {
            usGsm2UCS2CodeLen = 0;
            At_PbGsmToUnicode((pucSrc + usIndex), usGsmCodeLen,
                             (TAF_UINT8 *)(pusUnicode + usDstIndex),
                             &usGsm2UCS2CodeLen);

            usIndex    += (usGsmCodeLen - 1);
            usDstIndex += (usGsm2UCS2CodeLen >> 1);

            continue;
        }

        /* 82 ??????????8bit?????????????????? */
        usUnicode = usBaseCode + (pucSrc[usIndex] & AT_PB_GSM7_CODE_MAX_VALUE);

        AT_UNICODE2VALUE(usUnicode);

        pusUnicode[usDstIndex++] = usUnicode;
    }

    *pusDstLen = (TAF_UINT16)(usDstIndex << 1);

    return;
}


TAF_VOID At_PbUnicode81FormatPrint(TAF_UINT8  *puc81Code,
                                   TAF_UINT8  *pucDst,
                                   TAF_UINT16 *pusDstLen)
{
    TAF_UINT16      usIndex;
    TAF_UINT16      usUnicode;
    TAF_UINT16      usBaseCode;
    TAF_UINT16      usSrcLen;
    TAF_UINT16      usDstIndex  = 0;
    TAF_UINT16      usGsmCodeLen;
    TAF_UINT16      usGsm2UCS2CodeLen;
    TAF_UINT16      *pusUnicode = (TAF_UINT16 *)pucDst;
    TAF_UINT8       *pucSrc;

    if(SI_PB_ALPHATAG_MAX_LEN < puc81Code[0])    /*????????????????????????????*/
    {
        *pusDstLen = 0;

        return;
    }

    /* ????81?????????? */
    usSrcLen = puc81Code[0];

    /* ????81???????????? */
    usBaseCode = puc81Code[1] << 7;

    /* ????81??????????, ??????????????Byte????81???????????? */
    pucSrc = puc81Code + 2;

    /* ??????????????????81?????????? */
    for (usIndex = 0; usIndex < usSrcLen; usIndex++)
    {
        usGsmCodeLen = 0;
        while ((AT_PB_GSM7_CODE_MAX_VALUE >= pucSrc[usIndex + usGsmCodeLen])
            && ((usIndex+usGsmCodeLen) < usSrcLen))
        {
            usGsmCodeLen++;
        }

        if (0 != usGsmCodeLen)
        {
            usGsm2UCS2CodeLen = 0;
            At_PbGsmToUnicode((pucSrc + usIndex), usGsmCodeLen,
                             (TAF_UINT8 *)(pusUnicode + usDstIndex),
                             &usGsm2UCS2CodeLen);

            usIndex    += (usGsmCodeLen - 1);
            usDstIndex += (usGsm2UCS2CodeLen >> 1);

            continue;
        }

        /* 81??????????8bit?????????????????? */
        usUnicode = usBaseCode + (pucSrc[usIndex] & AT_PB_GSM7_CODE_MAX_VALUE);

        AT_UNICODE2VALUE(usUnicode);

        pusUnicode[usDstIndex++] = usUnicode;
    }

    *pusDstLen = (TAF_UINT16)(usDstIndex << 1);

    return;
}


TAF_VOID At_PbUnicode80FormatPrint(TAF_UINT8  *pucSrc,
                                   TAF_UINT16 usSrcLen,
                                   TAF_UINT8  *pucDst,
                                   TAF_UINT16 *pusDstLen)
{
    if((0xFF == pucSrc[0])&&(0xFF == pucSrc[1]))   /*??????????FFFF??????????????????*/
    {
        *pusDstLen = 0;
    }
    else
    {
        /* ????80?????? */
        TAF_MEM_CPY_S(pucDst, 500, pucSrc, usSrcLen);

        *pusDstLen = usSrcLen;
    }

    return;
}


TAF_UINT32 At_PbGsmExtToUnicode(TAF_UINT8 ucGsmExtChar, TAF_UINT16 *pusUnicodeChar)
{
    TAF_UINT16      usIndex;

    /* ????GSM??UNICODE???????????????????????????????????? */
    for (usIndex = 0; usIndex < AT_PB_GSM7EXT_MAX_NUM; usIndex++)
    {
        if (ucGsmExtChar == g_astGsm7extToUnicode[usIndex].ucOctet)
        {
            *pusUnicodeChar = g_astGsm7extToUnicode[usIndex].usUnicode;

            return AT_SUCCESS;
        }
    }

    AT_LOG1("At_PbGsmExtToUnicode warning: no found [0x%x]", ucGsmExtChar);

    return AT_FAILURE;
}


TAF_VOID At_PbGsmToUnicode(TAF_UINT8  *pucSrc,
                           TAF_UINT16 usSrcLen,
                           TAF_UINT8  *pucDst,
                           TAF_UINT16 *pusDstLen)
{
    TAF_UINT16      usIndex;
    TAF_UINT16      usUnicodeLen = 0;
    TAF_UINT16      *pusUnicode  = (TAF_UINT16 *)pucDst;
    TAF_UINT16      usUnicodeChar;

    for (usIndex = 0; usIndex < usSrcLen; usIndex++)
    {
        /* ????????????????GSM????????????????????????BIT???? */
        pucSrc[usIndex] = pucSrc[usIndex] & AT_PB_GSM7_CODE_MAX_VALUE;

        /* ??0x1B????????????GSM??UNICODE?????? */
        if (AT_PB_GSM7EXT_SYMBOL != pucSrc[usIndex])
        {
            usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex]].usUnicode;
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;
            usUnicodeLen++;

            continue;
        }

        /* ????GSM??????0x1b??,?????????????? */
        if ((usSrcLen - usIndex) < 2)
        {
            /* ??????????????0x1B????GSM??UNICODE??????, ??0x1B????SPACE */
            usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex]].usUnicode;
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;
            usUnicodeLen++;

            continue;
        }

        /* ????0x1B 0x1B??????????????????????????????????????????????0x1B
            0x1B????SPACE SPACE */
        if (AT_PB_GSM7EXT_SYMBOL == pucSrc[usIndex + 1])
        {
            usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex]].usUnicode;
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;

            usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex + 1]].usUnicode;
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;

            usIndex++;
            usUnicodeLen += 2;

            continue;
        }

        /* 0x1B????????????????GSM??UNICODE?????? */
        if (AT_SUCCESS == At_PbGsmExtToUnicode(pucSrc[usIndex + 1], &usUnicodeChar))
        {
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;
            usIndex++;
            usUnicodeLen++;

            continue;
        }

       /* ????1BXX??????????????????XX????0x1B????????????SPACE+XX?????????? */
       usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex]].usUnicode;
       AT_UNICODE2VALUE(usUnicodeChar);
       *pusUnicode = usUnicodeChar;
       pusUnicode++;
       usUnicodeLen++;
    }

    /* GSM7BIT ??????????????????????????GSM7bit??UNICODE????????????????????????????2?? */
    *pusDstLen = (TAF_UINT16)(usUnicodeLen << 1);

    return;
}


TAF_VOID At_PbRecordToUnicode(SI_PB_EVENT_INFO_STRU *pstEvent,
                              TAF_UINT8             *pucDecode,
                              TAF_UINT16            *pusDecodeLen)
{
    TAF_UINT16      usDecodeLen = 0;

    switch(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
    {
        case SI_PB_ALPHATAG_TYPE_GSM:
            At_PbGsmToUnicode(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                              pstEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength,
                              pucDecode,
                              &usDecodeLen);
            break;
        case SI_PB_ALPHATAG_TYPE_UCS2_80:
            At_PbUnicode80FormatPrint(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                      pstEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength,
                                      pucDecode,
                                      &usDecodeLen);
            break;
        case SI_PB_ALPHATAG_TYPE_UCS2_81:
            At_PbUnicode81FormatPrint(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                      pucDecode,
                                      &usDecodeLen);
            break;
        case SI_PB_ALPHATAG_TYPE_UCS2_82:
            At_PbUnicode82FormatPrint(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                      pucDecode,
                                      &usDecodeLen);
            break;
        default:
            AT_ERR_LOG("At_PbRecordToUnicode error: not support code type");

            break;
    }

    *pusDecodeLen = usDecodeLen;

    return;
}


TAF_UINT32 At_Pb_AlaphPrint(TAF_UINT16            *pusDataLen,
                            SI_PB_EVENT_INFO_STRU *pstEvent,
                            TAF_UINT8             *pucData)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT16              usDecodeLen = 0;
    TAF_UINT16              usReturnLen = 0;
    TAF_UINT8               aucDecode[500] = {0};

    if (AT_CSCS_GSM_7Bit_CODE == gucAtCscsType)
    {
        /* ??GSM????????????????UCS2???? */
        if ((SI_PB_ALPHATAG_TYPE_UCS2_80 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
         || (SI_PB_ALPHATAG_TYPE_UCS2_81 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
         || (SI_PB_ALPHATAG_TYPE_UCS2_82 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType))
        {
            /* usReturnLen = 0; */

            AT_LOG1("At_Pb_AlaphPrint error: GSM7 doesn't read UCS code[%d]",
                    pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType);
            return AT_FAILURE;
        }

        usReturnLen = At_PbGsmFormatPrint((AT_CMD_MAX_LEN - usLength),
                                          (pucData + usLength),
                                          pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                          pstEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);
    }
    else  /* ????????????UCS2??IRA?? */
    {
        /* ????????????UCS2??IRA????????????????????????UCS2???? */
        At_PbRecordToUnicode(pstEvent, aucDecode, &usDecodeLen);

        /* ????????????IRA??????UCS2??????IRA????????*/
        if (AT_CSCS_IRA_CODE == gucAtCscsType)
        {
            usReturnLen = At_PbUnicodeToIraFormatPrint((AT_CMD_MAX_LEN - usLength),
                                                       (pucData + usLength),
                                                       aucDecode,
                                                       usDecodeLen);
        }

        /* ????????????UCS2??????UCS2??????????????????*/
        if (AT_CSCS_UCS2_CODE == gucAtCscsType)
        {
            usReturnLen = (TAF_UINT16)At_Unicode2UnicodePrint(AT_CMD_MAX_LEN,
                                                              (TAF_INT8 *)pucData,
                                                              (pucData + usLength),
                                                              aucDecode,
                                                              usDecodeLen);
        }
    }

    if (0 == usReturnLen)
    {
        gstAtSendData.usBufLen = 0;

        AT_LOG1("At_Pb_AlaphPrint error: usReturnLen = 0,gucAtCscsType = [%d]", gucAtCscsType);

        return AT_FAILURE;
    }

    usLength    += usReturnLen;
    *pusDataLen  = usLength;

    return AT_SUCCESS;
}


TAF_UINT32 At_Pb_CnumAlaphPrint(TAF_UINT16            *pusDataLen,
                            SI_PB_EVENT_INFO_STRU *pstEvent,
                            TAF_UINT8             *pucData)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT16              usDecodeLen = 0;
    TAF_UINT16              usReturnLen = 0;
    TAF_UINT8               aucDecode[500] = {0};

    if (AT_CSCS_GSM_7Bit_CODE == gucAtCscsType)
    {
        /* ??GSM????????????????UCS2???? */
        if ((SI_PB_ALPHATAG_TYPE_UCS2_80 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
         || (SI_PB_ALPHATAG_TYPE_UCS2_81 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
         || (SI_PB_ALPHATAG_TYPE_UCS2_82 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType))
        {

            AT_LOG1("At_Pb_AlaphPrint error: GSM7 doesn't read UCS code[%d]",
                    pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType);
            return AT_SUCCESS;
        }

        usReturnLen = At_PbGsmFormatPrint((AT_CMD_MAX_LEN - usLength),
                                          (pucData + usLength),
                                          pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                          pstEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);
    }
    else  /* ????????????UCS2??IRA?? */
    {
        /* ????????????UCS2??IRA????????????????????????UCS2???? */
        At_PbRecordToUnicode(pstEvent, aucDecode, &usDecodeLen);

        /* ????????????IRA??????UCS2??????IRA????????*/
        if (AT_CSCS_IRA_CODE == gucAtCscsType)
        {
            usReturnLen = At_PbUnicodeToIraFormatPrint((AT_CMD_MAX_LEN - usLength),
                                                       (pucData + usLength),
                                                       aucDecode,
                                                       usDecodeLen);
        }

        /* ????????????UCS2??????UCS2??????????????????*/
        if (AT_CSCS_UCS2_CODE == gucAtCscsType)
        {
            usReturnLen = (TAF_UINT16)At_Unicode2UnicodePrint(AT_CMD_MAX_LEN,
                                                              (TAF_INT8 *)pucData,
                                                              (pucData + usLength),
                                                              aucDecode,
                                                              usDecodeLen);
        }
    }

    if (0 == usReturnLen)
    {

        AT_LOG1("At_Pb_AlaphPrint error: usReturnLen = 0,gucAtCscsType = [%d]", gucAtCscsType);

        return AT_SUCCESS;
    }

    usLength    += usReturnLen;
    *pusDataLen  = usLength;

    return AT_SUCCESS;
}


TAF_VOID AT_Pb_NumberPrint(TAF_UINT16 *pusDataLen, SI_PB_EVENT_INFO_STRU *pstEvent, TAF_UINT8 *pucData)
{
    TAF_UINT16      usLength = *pusDataLen;

    if(0 == pstEvent->PBEvent.PBReadCnf.PBRecord.NumberLength)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pucData,
                                           (TAF_CHAR *)pucData+usLength,
                                           ",\"\",129");
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pucData,
                                           (TAF_CHAR *)pucData + usLength,
                                           ",\"");

        if (PB_NUMBER_TYPE_INTERNATIONAL == pstEvent->PBEvent.PBReadCnf.PBRecord.NumberType )
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pucData,
                                               (TAF_CHAR *)pucData+usLength,
                                               "+");
        }

        TAF_MEM_CPY_S(pucData + usLength, AT_CMD_MAX_LEN + 20 - 1 - usLength, pstEvent->PBEvent.PBReadCnf.PBRecord.Number,
                   pstEvent->PBEvent.PBReadCnf.PBRecord.NumberLength);

        usLength += (TAF_UINT16)pstEvent->PBEvent.PBReadCnf.PBRecord.NumberLength;

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pucData,
                                           (TAF_CHAR *)pucData + usLength,
                                           "\"");

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pucData,
                                           (TAF_CHAR *)pucData + usLength,
                                           ",%d",
                                           pstEvent->PBEvent.PBReadCnf.PBRecord.NumberType);
    }

    *pusDataLen  = usLength;

    return;
}


TAF_UINT32 At_PbCNUMCmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,TAF_UINT8 *pucData,SI_PB_EVENT_INFO_STRU *pEvent)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT32              ulResult;

    if(SI_PB_CONTENT_INVALID == pEvent->PBEvent.PBReadCnf.PBRecord.ValidFlag)
    {
        return AT_SUCCESS;
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* ????:????????????????????????????????????ASCII????????????????UNICODE???????? */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,"\"");

    if ( (pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength != 0)
      && (pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength <= SI_PB_ALPHATAG_MAX_LEN) )
    {
         ulResult = At_Pb_CnumAlaphPrint(&usLength, pEvent, pucData);

        if(AT_SUCCESS != ulResult)
        {
            At_FormatResultData(ucIndex, AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING);

            return AT_FAILURE;
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,"\"");


    /* ?????????????????????????????????? */
    AT_Pb_NumberPrint(&usLength, pEvent, pucData);

    *pusDataLen = usLength;

    return AT_SUCCESS;
}


TAF_UINT32 At_PbCPBR2CmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,TAF_UINT8 *pucData,SI_PB_EVENT_INFO_STRU *pEvent)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT32              ulResult;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                    (TAF_CHAR *)pucData+usLength, "%s: ",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                    (TAF_CHAR *)pucData+usLength, "%d",
                                    pEvent->PBEvent.PBReadCnf.PBRecord.Index);


    /* ?????????????????????????????????? */
    AT_Pb_NumberPrint(&usLength, pEvent, pucData);

    /* ????:????????????????????????????????????ASCII????????????????UNICODE???????? */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,",\"");

    if( (pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength != 0)
     && (pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength <= SI_PB_ALPHATAG_MAX_LEN) )
    {
        ulResult = At_Pb_AlaphPrint(&usLength, pEvent, pucData);

        if(AT_SUCCESS != ulResult)
        {
            At_FormatResultData(ucIndex, AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING);

            return AT_FAILURE;
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                (TAF_CHAR *)pucData+usLength, "\"");

    *pusDataLen = usLength;

    return AT_SUCCESS;
}



TAF_UINT32 At_PbCPBRCmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,TAF_UINT8 *pucData,SI_PB_EVENT_INFO_STRU *pEvent)
{
    TAF_UINT16              usLength = *pusDataLen;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                    (TAF_CHAR *)pucData+usLength, "%s: ",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                    (TAF_CHAR *)pucData+usLength, "%d",
                                    pEvent->PBEvent.PBReadCnf.PBRecord.Index);


    /* ?????????????????????????????????? */
    AT_Pb_NumberPrint(&usLength, pEvent, pucData);

    /* ????:????????????????????????????????????ASCII????????????????UNICODE???????? */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,",\"");

    if ( (pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength != 0)
      && (pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength <= SI_PB_ALPHATAG_MAX_LEN) )
    {

        if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType&0x80))  /* DATA:IRA */
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                                (TAF_CHAR *)pucData+usLength, "%X",
                                                pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType);

            usLength += (TAF_UINT16)At_PB_Unicode2UnicodePrint(AT_CMD_MAX_LEN,(TAF_INT8 *)pucData,
                                        pucData+usLength, pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                        pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

            if((pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength%2) == 0)/*??????????????????????????FF*/
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,"FF");
            }
        }
        else                                    /* DATA:UCS2 */
        {
            TAF_MEM_CPY_S((TAF_CHAR *)pucData + usLength,
                        AT_CMD_MAX_LEN + 20 - 1 - usLength,
                        pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                        pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

            usLength += pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength;
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                (TAF_CHAR *)pucData+usLength, "\"");

    if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType&0x80))
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                        (TAF_CHAR *)pucData+usLength, ",1");
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                        (TAF_CHAR *)pucData+usLength, ",0");
    }

    *pusDataLen = usLength;

    return AT_SUCCESS;
}


TAF_VOID At_PbEmailPrint(TAF_UINT8  *pucSrc,
                         TAF_UINT16 usSrcLen,
                         TAF_UINT8  *pucDst,
                         TAF_UINT16 *pusDstLen)
{
    TAF_UINT8   aucUCS2Code[2 * SI_PB_EMAIL_MAX_LEN];
    TAF_UINT16  usUCS2CodeLen;
    TAF_UINT16  usEMailLen = usSrcLen;

    TAF_UINT16  usReturnLen;

    /* ??EMAIL????????64Byte?????????????? */
    if(SI_PB_EMAIL_MAX_LEN < usEMailLen)
    {
        usEMailLen = SI_PB_EMAIL_MAX_LEN;
    }

    /* ????GSM????????UCS2???? */
    At_PbGsmToUnicode(pucSrc, usEMailLen, aucUCS2Code, &usUCS2CodeLen);

    /* ????UCS2????????IRA???? */
    usReturnLen = At_PbUnicodeToIraFormatPrint(usSrcLen, pucDst, aucUCS2Code, usUCS2CodeLen);
    if (0 == usReturnLen)
    {
        AT_INFO_LOG("At_PbEmailPrint error: usReturnLen = 0");
        return;
    }

    *pusDstLen = (TAF_UINT16)(usUCS2CodeLen >> 1);

    return;
}


TAF_UINT32 At_PbSCPBRCmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,SI_PB_EVENT_INFO_STRU *pEvent)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT16              i;
    TAF_UINT16              usEmailLen = 0;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                    (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "%s: ",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                    (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "%d",
                                    pEvent->PBEvent.PBReadCnf.PBRecord.Index);


    /* ?????????????????????????????????? */
    AT_Pb_NumberPrint(&usLength, pEvent, pgucAtSndCrLfAddr);

    for(i = 0; i < 3; i++)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                        (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",\"");

        if( (0 == pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberLength)
         || ((SI_PB_PHONENUM_MAX_LEN + 2) < pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberLength) )
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                            (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "\",129");

            continue;
        }

        if (PB_NUMBER_TYPE_INTERNATIONAL == pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberType )
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                        (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "+");
        }

        TAF_MEM_CPY_S(pgucAtSndCrLfAddr + usLength,
                        AT_CMD_MAX_LEN + 20 - 1 - usLength,
                        pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].Number,
                        pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberLength);

        usLength += (TAF_UINT16)pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberLength;

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                        (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "\"");

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                        (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",%d",
                                        pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberType);
    }

    /* ????:????????????????????????????????????ASCII????????????????UNICODE???????? */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,(TAF_CHAR *)pgucAtSndCrLfAddr + usLength,",\"");

    if( (pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength != 0)
     && (pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength <= SI_PB_ALPHATAG_MAX_LEN) )
    {
        if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType&0x80))  /* DATA:IRA */
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                                (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "%X",
                                                pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType);

            usLength += (TAF_UINT16)At_PB_Unicode2UnicodePrint(AT_CMD_MAX_LEN,(TAF_INT8 *)pgucAtSndCrLfAddr,
                                        pgucAtSndCrLfAddr+usLength, pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                        pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

            if((pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength%2) == 0)/*??????????????????????????FF*/
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,(TAF_CHAR *)pgucAtSndCrLfAddr + usLength,"FF");
            }
        }
        else                                    /* DATA:UCS2 */
        {
            TAF_MEM_CPY_S((TAF_CHAR *)pgucAtSndCrLfAddr + usLength,
                        AT_CMD_MAX_LEN + 20 - 1 - usLength,
                        pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                        pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

            usLength += pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength;
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "\"");

    if (AT_CMD_SCPBR_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {

        if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType&0x80))
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                            (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",1");
        }
        else
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                            (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",0");
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                    (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",\"");

    if ( 0 != pEvent->PBEvent.PBReadCnf.PBRecord.Email.EmailLen )
    {
        At_PbEmailPrint(pEvent->PBEvent.PBReadCnf.PBRecord.Email.Email,
                        (TAF_UINT16)pEvent->PBEvent.PBReadCnf.PBRecord.Email.EmailLen,
                        (TAF_UINT8 *)(pgucAtSndCrLfAddr + usLength),
                        &usEmailLen);

        usLength += usEmailLen;

    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                    (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "\"");

    *pusDataLen = usLength;

    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_PbSearchCnfProc
 Description    : ??????????????????????
 Input          : pEvent --- ????????
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : h59254
  1.Date        : 2009-03-14
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_VOID At_PbSearchCnfProc(VOS_UINT8 ucIndex,SI_PB_EVENT_INFO_STRU  *pEvent)
{
    TAF_UINT16              usLength = 0;

    gulPBPrintTag = TAF_TRUE;

/*
    if(0 != usLength)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr, (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);
    }
*/
    if(pEvent->PBEvent.PBSearchCnf.PBRecord.ValidFlag == SI_PB_CONTENT_INVALID)/*??????????????*/
    {
        return;              /*??????????*/
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%d",pEvent->PBEvent.PBSearchCnf.PBRecord.Index);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",\"");

    if (PB_NUMBER_TYPE_INTERNATIONAL == pEvent->PBEvent.PBSearchCnf.PBRecord.NumberType)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"+");
    }

    TAF_MEM_CPY_S(pgucAtSndCodeAddr + usLength,
        AT_CMD_MAX_LEN + 20 - 3 - usLength,
        pEvent->PBEvent.PBSearchCnf.PBRecord.Number,
        pEvent->PBEvent.PBSearchCnf.PBRecord.NumberLength);
    usLength += (TAF_UINT16)pEvent->PBEvent.PBSearchCnf.PBRecord.NumberLength;
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"\"");

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",%d,",pEvent->PBEvent.PBSearchCnf.PBRecord.NumberType);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
    /* PS_MEM_CPY((TAF_CHAR *)pgucAtSndCodeAddr + usLength,pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTag, pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength); */
    /* usLength += pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength; */

    if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTagType & 0x80))  /* DATA:IRA */
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr+usLength,"%X",pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTagType);

        usLength += (TAF_UINT16)At_PB_Unicode2UnicodePrint(AT_CMD_MAX_LEN,(TAF_INT8 *)pgucAtSndCodeAddr,pgucAtSndCodeAddr+usLength,pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTag,pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength);

        if((pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength%2) == 0)/*??????????????????????????FF*/
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"FF");
        }
    }
    else                                    /* DATA:UCS2 */
    {
        if(AT_CSCS_UCS2_CODE == gucAtCscsType)       /* +CSCS:UCS2 */
        {
            usLength += (TAF_UINT16)At_Ascii2UnicodePrint(AT_CMD_MAX_LEN,(TAF_INT8 *)pgucAtSndCodeAddr,pgucAtSndCodeAddr+usLength,pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTag,pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength);
        }
        else
        {
            TAF_MEM_CPY_S((TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                AT_CMD_MAX_LEN + 20 - 3 - usLength,
                pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTag,
                pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength);
            usLength += pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength;
        }
    }
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"\"");

    if(AT_V_ENTIRE_TYPE == gucAtVType)
    {
        TAF_MEM_CPY_S((TAF_CHAR *)pgucAtSndCrLfAddr, AT_CMD_MAX_LEN + 20 - 1, (TAF_CHAR *)gaucAtCrLf, 2);/*Code??????\r\n*/
        At_SendResultData(ucIndex,pgucAtSndCrLfAddr,usLength+2);
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);

        At_SendResultData(ucIndex,pgucAtSndCodeAddr,usLength);
    }
}



TAF_UINT32 At_PbReadCnfProc(VOS_UINT8 ucIndex,SI_PB_EVENT_INFO_STRU  *pEvent)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usPBReadPrintLength;
    ulResult                            = AT_FAILURE;
    usPBReadPrintLength                 = 0;

    if (SI_PB_CONTENT_INVALID == pEvent->PBEvent.PBReadCnf.PBRecord.ValidFlag)/*??????????????*/
    {
        return AT_SUCCESS;              /*??????????*/
    }
    else
    {
        if (TAF_FALSE == gulPBPrintTag)
        {
             usPBReadPrintLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,(TAF_CHAR *)pgucAtSndCrLfAddr,"%s","\r\n");
        }

        gulPBPrintTag = TAF_TRUE;

        if(AT_CMD_CPBR_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) /*???? ^CPBR ??????????????*/
        {
            ulResult = At_PbCPBRCmdPrint(ucIndex,&usPBReadPrintLength,pgucAtSndCrLfAddr,pEvent);
        }
        else if(AT_CMD_CPBR2_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) /*???? +CPBR ??????????????*/
        {
            ulResult = At_PbCPBR2CmdPrint(ucIndex,&usPBReadPrintLength,pgucAtSndCrLfAddr,pEvent);
        }
        else if(AT_CMD_SCPBR_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) /*???? ^SCPBR ??????????????*/
        {
            ulResult = At_PbSCPBRCmdPrint(ucIndex,&usPBReadPrintLength,pEvent);
        }
        else if(AT_CMD_CNUM_READ == gastAtClientTab[ucIndex].CmdCurrentOpt) /*???? CNUM ??????????????*/
        {
            ulResult = At_PbCNUMCmdPrint(ucIndex,&usPBReadPrintLength,pgucAtSndCrLfAddr,pEvent);
        }
        else
        {
            AT_ERR_LOG1("At_PbReadCnfProc: the Cmd Current Opt %d is Unknow", gastAtClientTab[ucIndex].CmdCurrentOpt);

            return AT_FAILURE;
        }
    }

    /* Modified by s62952 for BalongV300R002 Build???????? 2012-02-28, begin */
    if(AT_SUCCESS == ulResult)
    {
        usPBReadPrintLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                                (TAF_CHAR *)pgucAtSndCrLfAddr + usPBReadPrintLength,
                                                "%s","\r\n");
    }
    /* Modified by s62952 for BalongV300R002 Build???????? 2012-02-28, end */

    At_SendResultData(ucIndex,pgucAtSndCrLfAddr,usPBReadPrintLength);

    TAF_MEM_CPY_S((TAF_CHAR *)pgucAtSndCrLfAddr, AT_CMD_MAX_LEN + 20 - 1, (TAF_CHAR *)gaucAtCrLf,2);/*AT????Buffer??????????????????\r\n*/

    return ulResult;
}



TAF_VOID At_PbCallBackFunc(SI_PB_EVENT_INFO_STRU  *pEvent)
{
    TAF_UINT32 ulSendMsg = 0;
    TAF_UINT8  ucIndex;

    if(TAF_NULL_PTR == pEvent)      /*????????*/
    {
        AT_WARN_LOG("At_PbCallBackFunc pEvent NULL");

        return;
    }

    if(AT_FAILURE == At_ClientIdToUserId(pEvent->ClientId, &ucIndex))/*????????????????????*/
    {
        //At_SendReportMsg(MN_CALLBACK_PHONE_BOOK, (TAF_UINT8*)pEvent, sizeof(SI_PB_EVENT_INFO_STRU));

        return;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_PbMsgProc : AT_BROADCAST_INDEX.");
        return;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    if(AT_CMD_CNUM == gastAtClientTab[ucIndex].CmdIndex)
    {
        pEvent->PBError = ((TAF_ERR_PB_NOT_FOUND == pEvent->PBError)?TAF_ERR_NO_ERROR:pEvent->PBError);
    }

    if(TAF_ERR_NO_ERROR != pEvent->PBError)/*??????????????????*/
    {
        ulSendMsg = SI_TRUE;
    }
    else if(((pEvent->PBEventType == SI_PB_EVENT_READ_CNF)||(pEvent->PBEventType == SI_PB_EVENT_SREAD_CNF))
        && (pEvent->PBLastTag != SI_PB_LAST_TAG_TRUE))/*????????????????????????????????????????????????????????????*/
    {
        if ( AT_SUCCESS != At_PbReadCnfProc(ucIndex,pEvent) )
        {
            AT_WARN_LOG("At_PbCallBackFunc:At_PbReadCnfProc Error");
        }

        ulSendMsg = SI_FALSE;
    }
    else if(pEvent->PBEventType == SI_PB_EVENT_SEARCH_CNF)
    {
        if( SI_PB_LAST_TAG_TRUE == pEvent->PBLastTag )
        {
            ulSendMsg = SI_TRUE;
        }
        else
        {
            At_PbSearchCnfProc(ucIndex,pEvent);
            return;
        }
    }
    else        /*????????????????????????????????????????*/
    {
        ulSendMsg = SI_TRUE;
    }

    if (SI_TRUE == ulSendMsg)
    {
        At_SendReportMsg(MN_CALLBACK_PHONE_BOOK,(TAF_UINT8*)pEvent,sizeof(SI_PB_EVENT_INFO_STRU));
    }

    return;
}

/* Added by L60609 for AT Project??2011-10-04,  End*/


VOS_VOID At_RcvVcMsgSetGroundCnfProc(
    MN_AT_IND_EVT_STRU                 *pstData
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetGroundCnfProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetGroundCnfProc : AT_BROADCAST_INDEX.");
        return;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CBG_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_RcvVcMsgSetGroundCnfProc:WARNING:AT ARE WAITING ANOTHER CMD!");
        return;
    }

    if (VOS_OK == pstData->aucContent[0])
    {
        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    /* ???????????? */
    gstAtSendData.usBufLen = 0;

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;
}


VOS_VOID At_RcvVcMsgQryGroundRspProc(
    MN_AT_IND_EVT_STRU                 *pstData
)
{
    APP_VC_QRY_GROUNG_RSP_STRU         *pstQryRslt;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryGroundRspProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryGroundRspProc : AT_BROADCAST_INDEX.");
        return;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CBG_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_RcvVcMsgQryGroundRspProc:WARNING:AT ARE WAITING ANOTHER CMD!");
        return;
    }

    /* ?????? */
    pstQryRslt = (APP_VC_QRY_GROUNG_RSP_STRU *)pstData->aucContent;

    if (VOS_OK == pstQryRslt->ucQryRslt)
    {
        /* ???????????? */
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "^CBG:%d",
                                                        pstQryRslt->enGround);
        ulRet = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulRet = AT_ERROR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;
}



VOS_VOID At_RcvVcMsgQryTTYModeCnfProc(
    MN_AT_IND_EVT_STRU                 *pstData
)
{
    APP_VC_QRY_TTYMODE_CNF_STRU        *pstTTYMode;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pstTTYMode      = (APP_VC_QRY_TTYMODE_CNF_STRU *)pstData->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryTTYModeCnfProc: WARNING: AT INDEX NOT FOUND!");
        return;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryTTYModeCnfProc: AT_BROADCAST_INDEX.");
        return;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_TTYMODE_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_RcvVcMsgQryTTYModeCnfProc: WARNING:AT ARE WAITING ANOTHER CMD!");
        return;
    }

    /* ??????TTY MODE */
    if (VOS_OK == pstTTYMode->ucQryRslt)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   "%s: %u",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   pstTTYMode->enTTYMode);
        ulRet = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulRet = AT_ERROR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;
}


VOS_VOID At_RcvVcMsgSetTTYModeCnfProc(
    MN_AT_IND_EVT_STRU                 *pstData
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                          *pucResult;
    VOS_UINT8                           ucIndex;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetTTYModeCnfProc: WARNING: AT INDEX NOT FOUND!");
        return;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetTTYModeCnfProc: AT_BROADCAST_INDEX.");
        return;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_TTYMODE_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_RcvVcMsgSetTTYModeCnfProc: WARNING:AT ARE WAITING ANOTHER CMD!");
        return;
    }

    pucResult = pstData->aucContent;
    if (VOS_OK == *pucResult)
    {
        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    /* ???????????? */
    gstAtSendData.usBufLen = 0;

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;
}



VOS_VOID At_ProcMsgFromVc(MN_AT_IND_EVT_STRU *pMsg)
{
    switch(pMsg->usMsgName)
    {
        case APP_VC_MSG_CNF_QRY_MODE:
            At_RcvVcMsgQryModeCnfProc(pMsg);
            break;

        case APP_VC_MSG_CNF_SET_PORT:
            At_RcvVcMsgSetPortCnfProc(pMsg);
            break;

        case APP_VC_MSG_CNF_QRY_PORT:
            At_RcvVcMsgQryPortCnfProc(pMsg);
            break;

        case APP_VC_MSG_SET_FOREGROUND_CNF:
        case APP_VC_MSG_SET_BACKGROUND_CNF:
            /*AT ???? VC ????????????????????????CNF MSG*/
            At_RcvVcMsgSetGroundCnfProc(pMsg);
            break;

        case APP_VC_MSG_FOREGROUND_RSP:
            /*AT ????VC ??????????????????????????*/
            At_RcvVcMsgQryGroundRspProc(pMsg);
            break;
        case APP_VC_MSG_QRY_TTYMODE_CNF:
            At_RcvVcMsgQryTTYModeCnfProc(pMsg);
            break;
        case APP_VC_MSG_SET_TTYMODE_CNF:
            At_RcvVcMsgSetTTYModeCnfProc(pMsg);
            break;


        case APP_VC_MSG_DTMF_DECODER_IND:
            At_RcvVcMsgDtmfDecoderIndProc(pMsg);
            break;

        default:
            return;
    }
    return;
}


VOS_UINT32 At_RcvRnicMsg(MsgBlock *pstMsg)
{
    VOS_UINT32                          ulRst;
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader                        = (MSG_HEADER_STRU *)pstMsg;

    switch(pstMsgHeader->ulMsgName)
    {
        /* ????RNIC?????????????? */
        case ID_RNIC_AT_DSFLOW_RSP:

            ulRst = AT_RcvRnicDsflowRsp(pstMsg);
            break;

        /* ????RNIC?????????????????????? */
        case ID_RNIC_AT_DIAL_MODE_CNF:

            ulRst = AT_RcvRnicDialModeCnf(pstMsg);
            break;

        default:
            ulRst = VOS_OK;
            break;
    }
    return ulRst;
}


VOS_VOID At_ProcMsgFromCc(VOS_VOID *pMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU *)pMsg;

    switch(pstMsgHeader->ulMsgName)
    {
        case AT_CC_MSG_STATE_QRY_CNF:
            At_RcvAtCcMsgStateQryCnfProc(pMsg);
            break;

        default:
            break;
    }
    return;
}


VOS_VOID AT_RcvNdisMsg(MsgBlock* pMsg)
{
    VOS_UINT32                          ulResult;
    AT_FW_MSG_STRU                     *pstAtFwMsg;
    AT_FW_CMD_BINARY_MSG_STRU          *pstBinaryInfo;
    AT_NDIS_MSG_STRU                   *pstNdisMsg;

    pstAtFwMsg      = (AT_FW_MSG_STRU*)&(((MSG_HEADER_STRU *)pMsg)->ulMsgName);
    pstBinaryInfo   = (AT_FW_CMD_BINARY_MSG_STRU*)(pstAtFwMsg->pMsgParam);
    pstNdisMsg      = (AT_NDIS_MSG_STRU*)pstBinaryInfo;

    switch (pstNdisMsg->ulMsgId)
    {
        case ID_AT_NDIS_PDNINFO_CFG_CNF:
            ulResult = AT_RcvNdisPdnInfoCfgCnf(&pstNdisMsg->unMsg.stNdisPdnInfoCfgCnf);
            break;

        case ID_AT_NDIS_PDNINFO_REL_CNF:
            ulResult = AT_RcvNdisPdnInfoRelCnf(&pstNdisMsg->unMsg.stNdisPdnInfoRelCnf);
            break;

        default:
            AT_WARN_LOG("AT_RcvNdisMsg: Unexpected MSG is received.");
            ulResult = VOS_ERR;
            break;
    }

    if ( VOS_OK != ulResult )
    {
        AT_ERR_LOG1("AT_RcvNdisMsg: Process message failed. <MsgId>",
                    (VOS_INT32)pstNdisMsg->ulMsgId);
    }

    return;
}

/* Added by h44270 for V7R1 phase III, 2011-10-18, begin */

VOS_UINT32    AT_ProcRabmSetFastDormParaCnf(
    RABM_AT_SET_FASTDORM_PARA_CNF_STRU     *pstMsg
)
{
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulRslt;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("At_ProcRabmSetFastDormParaCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????? */
    gstAtSendData.usBufLen = 0;
    ulRslt = AT_ERROR;
    if (AT_RABM_PARA_SET_RSLT_SUCC == pstMsg->enRslt)
    {
        ulRslt = AT_OK;
    }

    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}


VOS_UINT32    AT_ProcRabmQryFastDormParaCnf(
    RABM_AT_QRY_FASTDORM_PARA_CNF_STRU     *pstMsg
)
{
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;

    ulResult = AT_ERROR;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("At_RcvAtCcMsgStateQryCnfProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* Added by l60609 for B070 Project, 2012/03/20, begin */
    if (VOS_TRUE == pstMsg->ucRslt)
    {
        /* ???????????? */
        usLength = 0;
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"^FASTDORM:%d",pstMsg->stFastDormPara.enFastDormOperationType);

        if (AT_RABM_FASTDORM_STOP_FD_ASCR != pstMsg->stFastDormPara.enFastDormOperationType)
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",%d",pstMsg->stFastDormPara.ulTimeLen);
        }

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);

        ulResult = AT_OK;
        gstAtSendData.usBufLen = usLength;
    }
    /* Added by l60609 for B070 Project, 2012/03/20, end */

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}


VOS_UINT32 AT_ProcRabmReleaseRrcCnf(RABM_AT_RELEASE_RRC_CNF_STRU *pstMsg)
{
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulRslt;

    ulRslt = AT_ERROR;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_ProcRabmReleaseRrcCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ???????????? */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK == pstMsg->ulRslt)
    {
        ulRslt = AT_OK;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}


VOS_UINT32    AT_ProcRabmSetVoicePreferParaCnf(
    RABM_AT_SET_VOICEPREFER_PARA_CNF_STRU     *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_ProcRabmSetVoicePreferParaCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????? */
    gstAtSendData.usBufLen = 0;
    ulRslt = AT_ERROR;
    if (AT_RABM_PARA_SET_RSLT_SUCC == pstMsg->enRslt)
    {
        ulRslt = AT_OK;
    }

    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}

VOS_UINT32 AT_ProcRabmQryVoicePreferEnableParaCnf(RABM_AT_QRY_VOICEPREFER_PARA_CNF_STRU *pstMsg)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    ulResult = AT_ERROR;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_ProcRabmQryVoicePreferEnableParaCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????? */
    usLength = 0;
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s:%d%s",
                                       gaucAtCrLf,
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       pstMsg->ulRslt,
                                       gaucAtCrLf);
    ulResult = AT_OK;
    gstAtSendData.usBufLen = usLength;

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}

VOS_UINT32 AT_ProcRabmVoicePreferStatusReport(RABM_AT_VOICEPREFER_STATUS_REPORT_STRU *pstMsg)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;

    ucIndex = 0;
    usLength = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_ProcRabmVoicePreferStatusReport:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ???????????? */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                      "%s^VOICEPREFERSTATUS:%d%s",
                                      gaucAtCrLf,
                                      pstMsg->ulVpStatus,
                                      gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}


TAF_VOID AT_RabmMsgProc(
    MSG_HEADER_STRU                    *pstMsg
)
{
    switch(pstMsg->ulMsgName)
    {
        case ID_RABM_AT_SET_FASTDORM_PARA_CNF:
            AT_ProcRabmSetFastDormParaCnf((RABM_AT_SET_FASTDORM_PARA_CNF_STRU*)pstMsg);
            break;

        case ID_RABM_AT_QRY_FASTDORM_PARA_CNF:
            AT_ProcRabmQryFastDormParaCnf((RABM_AT_QRY_FASTDORM_PARA_CNF_STRU*)pstMsg);
            break;

        case ID_RABM_AT_SET_RELEASE_RRC_CNF:
            AT_ProcRabmReleaseRrcCnf((RABM_AT_RELEASE_RRC_CNF_STRU*)pstMsg);
            break;

        case ID_RABM_AT_SET_VOICEPREFER_PARA_CNF:
            AT_ProcRabmSetVoicePreferParaCnf((RABM_AT_SET_VOICEPREFER_PARA_CNF_STRU*)pstMsg);
            break;

        case ID_RABM_AT_QRY_VOICEPREFER_PARA_CNF:
            AT_ProcRabmQryVoicePreferEnableParaCnf((RABM_AT_QRY_VOICEPREFER_PARA_CNF_STRU*)pstMsg);
            break;

        case ID_RABM_AT_VOICEPREFER_STATUS_REPORT:
            AT_ProcRabmVoicePreferStatusReport((RABM_AT_VOICEPREFER_STATUS_REPORT_STRU *)pstMsg);
            break;
        default:
            AT_WARN_LOG("At_RabmMsgProc:WARNING:Wrong Msg!");
            break;
    }
}

/* Added by h44270 for V7R1 phase III, 2011-10-18, end */


TAF_VOID At_MsgProc(MsgBlock* pMsg)
{
    VOS_UINT32                          ulSendPid;
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulSliceStart;
    VOS_UINT32                          ulSliceEnd;
    VOS_UINT32                          ulType;
    TAF_UINT32                          ulRet;

    ulSliceStart = VOS_GetSlice();
    ulSendPid    = pMsg->ulSenderPid;
    ulMsgName    = ((MSG_HEADER_STRU *)pMsg)->ulMsgName;

    /* ???????? */
    if ( VOS_PID_TIMER == pMsg->ulSenderPid )
    {
        At_TimeOutProc((REL_TIMER_MSG*)pMsg);
        ulSliceEnd = VOS_GetSlice();
        AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);

        return;
    }

    /* ?????????????? */
    switch ( pMsg->ulSenderPid )
    {
        case WUEPS_PID_AT:
            At_CmdMsgDistr((AT_MSG_STRU*)pMsg);
            ulSliceEnd = VOS_GetSlice();
            ulType     = ((AT_MSG_STRU*)pMsg)->ucType;
            ulMsgName  = (ulType<<16) | ulMsgName;
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_WUEPS_PID_TAF:
        case I1_WUEPS_PID_TAF:
        case I2_WUEPS_PID_TAF:
            ulRet = At_CallMsgProc((MSG_HEADER_STRU *)pMsg);
            if (AT_OK == ulRet)
            {
                return;
            }

            At_EventMsgProc((MN_AT_IND_EVT_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            ulMsgName = ((MN_AT_IND_EVT_STRU *)pMsg)->usMsgName;
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case PS_PID_APP_PPP:
            At_PppMsgProc((MSG_HEADER_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;


        case PS_PID_APP_NDIS:
            AT_RcvNdisMsg(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_DSP_PID_WPHY:
        case I1_DSP_PID_WPHY:
            At_HPAMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_DSP_PID_GPHY:
        case I1_DSP_PID_GPHY:
        case I2_DSP_PID_GPHY:
            At_GHPAMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_WUEPS_PID_MMA:
        case I1_WUEPS_PID_MMA:
        case I2_WUEPS_PID_MMA:
            At_MmaMsgProc((MSG_HEADER_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_WUEPS_PID_DRV_AGENT:
        case I1_WUEPS_PID_DRV_AGENT:
        case I2_WUEPS_PID_DRV_AGENT:
            At_ProcMsgFromDrvAgent((DRV_AGENT_MSG_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_WUEPS_PID_VC:
        case I1_WUEPS_PID_VC:
        case I2_WUEPS_PID_VC:
            At_ProcMsgFromVc((MN_AT_IND_EVT_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case ACPU_PID_RNIC:
            At_RcvRnicMsg(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_WUEPS_PID_CC:
        case I1_WUEPS_PID_CC:
        case I2_WUEPS_PID_CC:
            At_ProcMsgFromCc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_MSP_L4_L4A_PID:
        case I1_MSP_L4_L4A_PID:
            at_L4aCnfProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_MSP_SYS_FTM_PID:
        case I1_MSP_SYS_FTM_PID:
            At_FtmEventMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_MAPS_STK_PID:
        case I1_MAPS_STK_PID:
        case I2_MAPS_STK_PID:
            At_STKMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_MAPS_PB_PID:
        case I1_MAPS_PB_PID:
        case I2_MAPS_PB_PID:
            At_PbMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_MAPS_PIH_PID:
        case I1_MAPS_PIH_PID:
        case I2_MAPS_PIH_PID:
            At_PIHMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_WUEPS_PID_RABM:
        case I1_WUEPS_PID_RABM:
        case I2_WUEPS_PID_RABM:
            AT_RabmMsgProc((MSG_HEADER_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case WUEPS_PID_SPY:
            AT_SpyMsgProc((MSG_HEADER_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_UEPS_PID_MTA:
        case I1_UEPS_PID_MTA:
        case I2_UEPS_PID_MTA:
            At_ProcMtaMsg((AT_MTA_MSG_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_PS_PID_IMSA:
        case I1_PS_PID_IMSA:
            AT_ProcImsaMsg((AT_IMSA_MSG_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case PS_PID_CSS:
            AT_ProcCssMsg((CssAtInterface_MSG *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_UEPS_PID_XSMS:
        case I1_UEPS_PID_XSMS:
        case I2_UEPS_PID_XSMS:
            AT_ProcXsmsMsg((TAF_XSMS_APP_AT_CNF_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_UEPS_PID_XPDS:
        case I1_UEPS_PID_XPDS:
        case I2_UEPS_PID_XPDS:
            AT_ProcXpdsMsg((AT_XPDS_MSG_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            break;

         case DSP_PID_PROCSTUB:
            At_CHPAMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            break;

        default:
            AT_LOG1("At_MsgProc other PID msg",pMsg->ulSenderPid);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;
    }
}

/* Added by f62575 for AT Project, 2011/10/22, begin */

VOS_VOID AT_EventReport(
    VOS_UINT32                          ulPid,
    NAS_OM_EVENT_ID_ENUM_UINT16         enEventId,
    VOS_VOID                           *pPara,
    VOS_UINT32                          ulLen
)
{
    DIAG_EVENT_IND_STRU                 stDiagEvent;
    NAS_OM_EVENT_IND_STRUCT            *pstAtEvent = VOS_NULL_PTR;
    VOS_VOID                           *pData = pPara;
    VOS_UINT32                          ulAtEventMsgLen;
    VOS_UINT32                          ulRslt;

    /* ???????? */
    if ( (VOS_NULL_PTR == pData) && (ulLen != 0) )
    {
        /* ???????? */
        TAF_LOG(ulPid, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_EventReport:pPara is NULL.");
        return;
    }

    /* ???????? */
    if (4 >= ulLen)
    {
        ulAtEventMsgLen = sizeof(NAS_OM_EVENT_IND_STRUCT);
        pstAtEvent = (NAS_OM_EVENT_IND_STRUCT*)PS_MEM_ALLOC(ulPid, ulAtEventMsgLen);
    }
    else
    {
        ulAtEventMsgLen = sizeof(NAS_OM_EVENT_IND_STRUCT) + ulLen -4;
        pstAtEvent = (NAS_OM_EVENT_IND_STRUCT*)PS_MEM_ALLOC(ulPid, ulAtEventMsgLen);
    }

    if (VOS_NULL_PTR == pstAtEvent)
    {
        TAF_LOG(ulPid, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_EventReport:Alloc mem fail.");
        return;
    }

    /* ?????? */
    TAF_MEM_SET_S(pstAtEvent, ulAtEventMsgLen, 0x00, ulAtEventMsgLen);

    /* ???????????????? */
    pstAtEvent->usEventId    = enEventId;
    pstAtEvent->usReserve    = 0;
    if ( (VOS_NULL_PTR != pData) && (ulLen > 0) )
    {
        TAF_MEM_CPY_S(pstAtEvent->aucData, ulLen, pData, ulLen);
    }

    /* ????????DIAG???????? */
    stDiagEvent.ulLength        = sizeof(NAS_OM_EVENT_IND_STRUCT) - 4 + ulLen;
    stDiagEvent.ulPid           = ulPid;
    stDiagEvent.ulEventId       = (VOS_UINT32)enEventId;
    stDiagEvent.ulModule        = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(ulPid), DIAG_MODE_UMTS);
    stDiagEvent.pData           = pstAtEvent;

    ulRslt = DIAG_EventReport(&stDiagEvent);
    if (VOS_OK != ulRslt)
    {
        AT_WARN_LOG("AT_EventReport:OM_AcpuEvent Fail.");
    }

    PS_MEM_FREE(ulPid, pstAtEvent);

    return;
}

/* Added by f62575 for AT Project, 2011/10/22, end */


VOS_UINT32 AT_RcvDrvAgentSetAdcRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                        *pRcvMsg;
    DRV_AGENT_ADC_SET_CNF_STRU                *pstAdcCnf;
    VOS_UINT8                                  ucIndex;
    VOS_UINT32                                 ulResult;

    /* ?????????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstAdcCnf       = (DRV_AGENT_ADC_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ????ClientId????ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstAdcCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetAdcRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetAdcRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    /* ??????????????????????AT_CMD_ADC_SET */
    if (AT_CMD_ADC_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /*?????????????????? */
    if (VOS_TRUE != pstAdcCnf->bFail)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    /* ????AT_FormATResultDATa???????????? */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}



VOS_UINT32 AT_RcvDrvAgentQryTbatRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_TBAT_QRY_CNF_STRU        *stTbatTypeCnf;
    VOS_UINT8                           ucIndex;

    /* ?????????? */
    pRcvMsg                = (DRV_AGENT_MSG_STRU *)pMsg;
    stTbatTypeCnf          = (DRV_AGENT_TBAT_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ????ClientId????ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(stTbatTypeCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryTbatRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /*??????????????????????????????*/
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryTbatRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_TBAT_QRY */
    if (AT_CMD_TBAT_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stTbatTypeCnf->ulTbatType);

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, AT_OK);
    return VOS_OK;

}



VOS_UINT32 AT_RcvSimLockQryRsp(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;
    AT_MMA_SIMLOCK_STATUS_STRU         *pstEvent;

    pstEvent = (AT_MMA_SIMLOCK_STATUS_STRU *)pMsg;

    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvSimLockQryRsp: AT INDEX NOT FOUND!");

        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_SIMLOCKSTATUS_READ??AT_CMD_CSDFLT_READ */
    if ((AT_CMD_SIMLOCKSTATUS_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
     && (AT_CMD_CSDFLT_READ != gastAtClientTab[ucIndex].CmdCurrentOpt))
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    if (AT_CMD_SIMLOCKSTATUS_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:%d",
                                                        "SIMLOCK",
                                                        pstEvent->bSimlockEnableFlg);
        ulRet                  = AT_OK;

    }
    else
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = 0;
        ulRet                  = AT_OutputCsdfltDefault(ucIndex, pstEvent->bSimlockEnableFlg);
    }

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;
}

/* Added by f62575 for B050 Project, 2012-2-3, end   */



VOS_UINT32 AT_RcvDrvAgentSetSpwordRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                        *pRcvMsg;
    DRV_AGENT_SPWORD_SET_CNF_STRU             *pstSpwordSetCnf;
    VOS_UINT8                                  ucIndex;

    /* ?????????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstSpwordSetCnf = (DRV_AGENT_SPWORD_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ????ClientId????ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstSpwordSetCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("pstSpwordSetCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("pstSpwordSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_SPWORD_SET */
    if (AT_CMD_SPWORD_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ?????????????????????????????? */
    if (VOS_OK == pstSpwordSetCnf->ulResult)
    {
        g_stSpWordCtx.ucShellPwdCheckFlag = VOS_TRUE;
        g_stSpWordCtx.ucErrTimes          = 0;

        /* ????At_FormatResultData???????????? */
        At_FormatResultData(ucIndex, AT_OK);
    }
    /* ????????????????????????1 */
    else
    {
        g_stSpWordCtx.ucErrTimes++;

        /* ????At_FormatResultData???????????? */
        At_FormatResultData(ucIndex, AT_ERROR);
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaCipherInfoQueryCnf(VOS_VOID *pMsg)
{
    TAF_MMA_CIPHER_QRY_CNF_STRU        *pstCipherQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pstCipherQryCnf     = (TAF_MMA_CIPHER_QRY_CNF_STRU *)pMsg;
    ulResult            = AT_OK;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCipherQryCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCipherInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCipherInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_CIPERQRY_READ */
    if (AT_CMD_CIPERQRY_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^CIPERQRY???????????? */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstCipherQryCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR*)pgucAtSndCodeAddr,
                                                   "%s:%d",
                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                   pstCipherQryCnf->ucCipherInfo);
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}


VOS_UINT32 AT_RcvMmaLocInfoQueryCnf(VOS_VOID *pMsg)
{
    TAF_MMA_LOCATION_INFO_QRY_CNF_STRU *pstLocInfoCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pstLocInfoCnf       = (TAF_MMA_LOCATION_INFO_QRY_CNF_STRU *)pMsg;
    usLength            = 0;
    ulResult            = AT_OK;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstLocInfoCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaLocInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaLocInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_LOCINFO_READ */
    if (AT_CMD_LOCINFO_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT_STOP_TIMER_CMD_READY????AT??????????????READY???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^CIPERQRY???????????? */
    if (VOS_OK != pstLocInfoCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        /* ????MCC??MNC */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%X%X%X",
                                          (VOS_INT32)(pstLocInfoCnf->ulMcc & 0x0f) ,
                                          (VOS_INT32)(pstLocInfoCnf->ulMcc & 0x0f00) >> 8,
                                          (VOS_INT32)(pstLocInfoCnf->ulMcc & 0x0f0000) >> 16);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%X%X",
                                          (VOS_INT32)(pstLocInfoCnf->ulMnc & 0x0f) ,
                                          (VOS_INT32)(pstLocInfoCnf->ulMnc & 0x0f00) >> 8);

        /* MNC??????????????F????MNC?????????????????? */
        if (0x0f != ((pstLocInfoCnf->ulMnc & 0x0f0000) >> 16))
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%X",
                                          (VOS_INT32)(pstLocInfoCnf->ulMnc & 0x0f0000) >> 16);
        }

        /* Lac */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          ",0x%X",
                                          pstLocInfoCnf->usLac);

        /* Rac */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          ",0x%X",
                                          pstLocInfoCnf->ucRac);

        /* Cell ID */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          ",0x%X",
                                          pstLocInfoCnf->ulCellid);

        gstAtSendData.usBufLen = usLength;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentNvBackupStatQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_NVBACKUPSTAT_QRY_CNF_STRU    *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;

    /* ?????????????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_NVBACKUPSTAT_QRY_CNF_STRU *)pRcvMsg->aucContent;
    usLength        = 0;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentNvBackupStatQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNvBackupStatQryRsp: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_NVBACKUPSTAT_READ */
    if ( AT_CMD_NVBACKUPSTAT_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        if ( NV_OK == pstEvent->ulNvBackupStat )
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s: %d",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               VOS_TRUE);
        }
        else
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s: %d",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               VOS_FALSE);
        }

        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = usLength;
    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentNandBadBlockQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_NANDBBC_QRY_CNF_STRU         *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;
    VOS_UINT32                              uli;
    VOS_UINT32                              ulMaxBBNum;

    /* ?????????????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_NANDBBC_QRY_CNF_STRU *)pRcvMsg->aucContent;
    usLength        = 0;
    uli             = 0;
    ulMaxBBNum      = 0;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentNandBadBlockQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNandBadBlockQryRsp: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_NANDBBC_READ */
    if ( AT_CMD_NANDBBC_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: %d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstEvent->ulBadBlockNum);

        ulMaxBBNum = (pstEvent->ulBadBlockNum > DRV_AGENT_NAND_BADBLOCK_MAX_NUM) ? DRV_AGENT_NAND_BADBLOCK_MAX_NUM : pstEvent->ulBadBlockNum;
        for (uli = 0; uli < ulMaxBBNum; uli++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s%s: %d",
                                               gaucAtCrLf,
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               pstEvent->aulBadBlockIndex[uli]);
        }

        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = usLength;
    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentNandDevInfoQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_NANDVER_QRY_CNF_STRU         *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;

    /* ?????????????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_NANDVER_QRY_CNF_STRU *)pRcvMsg->aucContent;
    usLength        = 0;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentNandDevInfoQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNandDevInfoQryRsp: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_NANDVER_READ */
    if ( AT_CMD_NANDVER_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        /* ???????????? */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: %d,\"%s\",%d,\"%s\"",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstEvent->stNandDevInfo.ulMufId,
                                           pstEvent->stNandDevInfo.aucMufName,
                                           pstEvent->stNandDevInfo.ulDevId,
                                           pstEvent->stNandDevInfo.aucDevSpec);

        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = usLength;
    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentChipTempQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_CHIPTEMP_QRY_CNF_STRU    *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    /* ?????????????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_CHIPTEMP_QRY_CNF_STRU *)pRcvMsg->aucContent;
    usLength        = 0;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentChipTempQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentChipTempQryRsp: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_CHIPTEMP_READ */
    if ( AT_CMD_CHIPTEMP_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        /* ???????????? */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: %d,%d,%d,%d,%d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstEvent->lGpaTemp,
                                           pstEvent->lWpaTemp,
                                           pstEvent->lLpaTemp,
                                           pstEvent->lSimTemp,
                                           pstEvent->lBatTemp);

        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = usLength;
    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}






VOS_UINT32 AT_RcvMmaOmMaintainInfoInd(
    VOS_VOID                           *pstMsg
)
{
    ATMMA_OM_MAINTAIN_INFO_IND_STRU    *pstOmMaintainInfo;

    pstOmMaintainInfo = (ATMMA_OM_MAINTAIN_INFO_IND_STRU*)pstMsg;

    if ( (VOS_TRUE == pstOmMaintainInfo->ucOmConnectFlg)
      && (VOS_TRUE == pstOmMaintainInfo->ucOmPcRecurEnableFlg) )
    {
        AT_MNTN_TraceContextData();
        AT_MNTN_TraceClientData();
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentAntStateIndRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    VOS_UINT16                          usLength = 0;
    DRV_AGENT_ANT_STATE_IND_STRU       *pstAntState = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usAntState;

    gstAtSendData.usBufLen  = 0;
    pRcvMsg                 = (DRV_AGENT_MSG_STRU *)pMsg;
    pstAntState             = (DRV_AGENT_ANT_STATE_IND_STRU *)pRcvMsg->aucContent;
    ucIndex                 = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstAntState->stAtAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntStateIndRsp: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ????????????????????????0????????????1 */
    if (0 == ((pstAntState->usAntState) & AT_CMD_MAX_ANT_BIT_MASK))
    {
        AT_NORM_LOG("AT_RcvDrvAgentAntStateIndRsp: usAntState Set to 0");
        usAntState = 0;
    }
    else
    {
        AT_NORM_LOG("AT_RcvDrvAgentAntStateIndRsp: usAntState Set to 1");
        usAntState = 1;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       "%s:%d%s",
                                       "^ANTSTATE",
                                       usAntState,
                                       gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);


    return VOS_OK;
}

VOS_UINT32 AT_RcvDrvAgentSetMaxLockTmsRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                        *pRcvMsg;
    DRV_AGENT_MAX_LOCK_TMS_SET_CNF_STRU       *pstMaxlockTmsSetCnf;
    VOS_UINT8                                  ucIndex;

    /* ?????????? */
    pRcvMsg             = (DRV_AGENT_MSG_STRU *)pMsg;
    pstMaxlockTmsSetCnf = (DRV_AGENT_MAX_LOCK_TMS_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMaxlockTmsSetCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetMaxLockTmsRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetMaxLockTmsRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_MAXLCKTMS_SET */
    if (AT_CMD_MAXLCKTMS_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT_STOP_TIMER_CMD_READY????AT??????????????READY???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^MAXLCKTMS???????????? */
    if (VOS_OK != pstMaxlockTmsSetCnf->ulResult)
    {
        /* ????At_FormatResultData???????????? */
        At_FormatResultData(ucIndex, AT_DEVICE_OTHER_ERROR);
    }
    else
    {
        /* ????At_FormatResultData???????????? */
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentSetApSimstRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                        *pRcvMsg;
    DRV_AGENT_AP_SIMST_SET_CNF_STRU           *pstApSimStSetCnf;
    VOS_UINT8                                  ucIndex;

    /* ?????????? */
    pRcvMsg             = (DRV_AGENT_MSG_STRU *)pMsg;
    pstApSimStSetCnf    = (DRV_AGENT_AP_SIMST_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstApSimStSetCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetApSimstRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetApSimstRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_APSIMST_SET */
    if (AT_CMD_APSIMST_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT_STOP_TIMER_CMD_READY????AT??????????????READY???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^APSIMST???????????? */
    if (VOS_OK != pstApSimStSetCnf->ulResult)
    {
        /* ????At_FormatResultData???????????? */
        At_FormatResultData(ucIndex, AT_ERROR);
    }
    else
    {
        /* ????At_FormatResultData???????????? */
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}



VOS_UINT32 AT_RcvDrvAgentHukSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_HUK_SET_CNF_STRU             *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;

    printk(KERN_ERR "\n AT_RcvDrvAgentHukSetCnf enter\n");

    /* ?????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_HUK_SET_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    ulResult        = VOS_NULL;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentHukSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentHukSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_HUK_SET */
    if (AT_CMD_HUK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if (DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult)
    {
        /* ???????????? */
        ulResult    = AT_OK;
    }
    else
    {
        /* ????????, ?????????? */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentFacAuthPubkeySetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_FACAUTHPUBKEY_SET_CNF_STRU   *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;

    printk(KERN_ERR "\n AT_RcvDrvAgentFacAuthPubkeySetCnf enter \n");

    /* ?????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_FACAUTHPUBKEY_SET_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    ulResult        = VOS_NULL;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentFacAuthPubkeySetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentFacAuthPubkeySetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_FACAUTHPUBKEY_SET */
    if (AT_CMD_FACAUTHPUBKEYEX_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ???????????? */
        ulResult    = AT_OK;
    }
    else
    {
        /* ????????, ?????????? */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentIdentifyStartSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_IDENTIFYSTART_SET_CNF_STRU   *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;
    VOS_UINT32                              i;

    printk(KERN_ERR "\n AT_RcvDrvAgentIdentifyStartSetCnf enter\n");

    /* ?????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_IDENTIFYSTART_SET_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    usLength        = 0;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentIdentifyStartSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentIdentifyStartSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_IDENTIFYSTART_SET */
    if ( AT_CMD_IDENTIFYSTART_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ???????????? */
        ulResult    = AT_OK;
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s: ",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0; i < DRV_AGENT_RSA_CIPHERTEXT_LEN; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%02X",
                                          pstEvent->aucRsaText[i]);
        }
    }
    else
    {
        /* ????????, ?????????? */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = usLength;
    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentIdentifyEndSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_IDENTIFYEND_SET_CNF_STRU     *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;

    printk(KERN_ERR "\n AT_RcvDrvAgentIdentifyEndSetCnf enter \n");

    /* ?????????????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_IDENTIFYEND_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentIdentifyEndSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentIdentifyEndSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_IDENTIFYEND_SET */
    if ( AT_CMD_IDENTIFYEND_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ???????????? */
        ulResult    = AT_OK;
    }
    else
    {
        /* ????????, ?????????? */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentSimlockDataWriteSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                         *pRcvMsg;
    DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF_STRU    *pstEvent;
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ulResult;

    printk(KERN_ERR "\n AT_RcvDrvAgentSimlockDataWriteSetCnf enter\n");

    /* ?????????????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentSimlockDataWriteSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSimlockDataWriteSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_SIMLOCKDATAWRITE_SET */
    if ( AT_CMD_SIMLOCKDATAWRITE_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ???????????? */
        ulResult    = AT_OK;
    }
    else
    {
        /* ????????, ?????????? */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_CHAR AT_Num2AsciiNum(VOS_UINT8 ucNum)
{
    if (9 >= ucNum)
    {
        return (VOS_CHAR)('0' + ucNum);
    }
    else if (0x0F >= ucNum)
    {
        return (VOS_CHAR)('A' + (ucNum - 0x0A));
    }
    else
    {
        return '*';
    }
}


VOS_UINT32 AT_CheckSimlockCodeLast2Char(
    DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory,
    VOS_CHAR                                       *pcStrLast2Char
)
{
    VOS_UINT8                           i           = 0;

    /* ????????????????????, NET???????? */
    if (DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK < enCategory)
    {
        for (i = 0; i < 2; i++)
        {
            /* NETSUB????????: 0x00~0x99 */
            if ( ('0' <= pcStrLast2Char[i]) && ('9' >= pcStrLast2Char[i]) )
            {
                continue;
            }
            /* SP????????: 0x00~0xFF */
            else if ( (DRV_AGENT_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER == enCategory)
                   && ('A' <= pcStrLast2Char[i]) && ('F' >= pcStrLast2Char[i]) )
            {
                continue;
            }
            else
            {
                return VOS_ERR;
            }
        }
    }

    return VOS_OK;

}



VOS_UINT32 AT_CheckSimlockCodeStr(
    DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory,
    VOS_CHAR                                       *pcStrCode
)
{
    VOS_UINT8                           i           = 0;
    VOS_UINT8                           j           = 0;
    VOS_UINT8                           ucLen;              /* ???????????? */
    VOS_CHAR                           *pcTmpStr;

    pcTmpStr    = pcStrCode;

    switch(enCategory)
    {
        case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK:
            ucLen = AT_PERSONALIZATION_NET_CODE_LEN;
            break;
        default:
            ucLen = AT_PERSONALIZATION_CODE_LEN;
            break;
    }

    /* ????PLMN?????????????? */
    for (i = 0; i < AT_PERSONALIZATION_NET_CODE_LEN; i++)
    {
        if ( ('0' <= pcTmpStr[i]) && ('9' >= pcTmpStr[i]) )
        {
            continue;
        }
        else if ( ((AT_PERSONALIZATION_NET_CODE_LEN - 1) == i)
               && ('F' == pcTmpStr[i]) )
        {
            for (j = i + 1; j < ucLen; j++)
            {
                pcTmpStr[j - 1] = pcTmpStr[j];
            }
            ucLen = ucLen - 1;
            break;
        }
        else
        {
            return VOS_ERR;
        }
    }

    pcTmpStr[ucLen] = 0;

    /* ???????????????????????????????? */
    if (VOS_OK != AT_CheckSimlockCodeLast2Char(enCategory, &pcTmpStr[ucLen - 2]))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 AT_SimlockCodeBcd2Str(
    DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory,
    VOS_UINT8                                      *pucBcdNum,
    VOS_CHAR                                       *pcStrNum
)
{
    VOS_UINT8                           i               = 0;
    VOS_UINT8                           ucDecodeLen;
    VOS_UINT8                           ucFirstNum;
    VOS_UINT8                           ucSecondNum;
    VOS_CHAR                           *pcStrTmp        = pcStrNum;
    VOS_CHAR                            cTmpChar;

    switch(enCategory)
    {
        case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK:
            ucDecodeLen = AT_PERSONALIZATION_NET_CODE_BCD_LEN;
            break;
        case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK_SUBSET:
            ucDecodeLen = AT_PERSONALIZATION_SUBNET_CODE_BCD_LEN;
            break;
        case DRV_AGENT_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER:
            ucDecodeLen = AT_PERSONALIZATION_SP_CODE_BCD_LEN;
            break;
        default:
            return VOS_ERR;
    }

    /* ?????????????????????????????? */
    for (i = 0; i < ucDecodeLen; i++)
    {
        /* ???????????????? */
        ucFirstNum  = (VOS_UINT8)((*(pucBcdNum + i)) & 0x0F);
        ucSecondNum = (VOS_UINT8)(((*(pucBcdNum + i)) >> 4) & 0x0F);

        *pcStrTmp++ = AT_Num2AsciiNum(ucFirstNum);
        *pcStrTmp++ = AT_Num2AsciiNum(ucSecondNum);
    }

    /* ????????????????????????(??????????) */
    pcStrTmp        = &pcStrNum[AT_PERSONALIZATION_CODE_FOURTH_CHAR_INDEX];
    cTmpChar        = pcStrTmp[0];
    pcStrTmp[0]     = pcStrTmp[1];
    pcStrTmp[1]     = pcStrTmp[2];
    pcStrTmp[2]     = cTmpChar;

    /* ???????????????????????????????????????????? */
    if (VOS_OK != AT_CheckSimlockCodeStr(enCategory, pcStrNum))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_UINT32 AT_PhoneSimlockInfoPrint(
    DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU    *pstPhoneSimlockInfo,
    VOS_UINT8                                   ucIndex,
    VOS_UINT16                                 *pusLength
)
{
    VOS_UINT16                                  usLength        = *pusLength;
    VOS_UINT8                                   ucCatIndex      = 0;
    VOS_UINT8                                   ucGroupIndex    = 0;
    VOS_CHAR                                    acCodeBegin[AT_PERSONALIZATION_CODE_LEN + 1];
    VOS_CHAR                                    acCodeEnd[AT_PERSONALIZATION_CODE_LEN + 1];
    VOS_UINT32                                  ulCodeBeginRslt;
    VOS_UINT32                                  ulCodeEndRslt;

    TAF_MEM_SET_S(acCodeBegin, sizeof(acCodeBegin), 0x00,   (AT_PERSONALIZATION_CODE_LEN + 1));
    TAF_MEM_SET_S(acCodeEnd, sizeof(acCodeEnd), 0x00,   (AT_PERSONALIZATION_CODE_LEN + 1));
    ulCodeBeginRslt = VOS_NULL;
    ulCodeEndRslt   = VOS_NULL;

    for (ucCatIndex = 0; ucCatIndex < DRV_AGENT_SUPPORT_CATEGORY_NUM; ucCatIndex++)
    {
        if (0 != ucCatIndex)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s",
                                               gaucAtCrLf);
        }

        /* ^PHONESIMLOCKINFO: <cat>,<indicator> [,(<code_begin>,<code_end>)...] */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        switch (pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enCategory)
        {
            case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "NET");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK_SUBSET:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "NETSUB");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "SP");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_CORPORATE:
            case DRV_AGENT_PERSONALIZATION_CATEGORY_SIM_USIM:
            default:
                return VOS_ERR;
        }
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d",
                                           pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enIndicator);
        if (DRV_AGENT_PERSONALIZATION_INDICATOR_ACTIVE == pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enIndicator)
        {
            for (ucGroupIndex = 0; ucGroupIndex < pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].ucGroupNum; ucGroupIndex++)
            {
                ulCodeBeginRslt = AT_SimlockCodeBcd2Str(pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enCategory,
                                                        pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].astLockCode[ucGroupIndex].aucPhLockCodeBegin,
                                                        acCodeBegin);
                ulCodeEndRslt   = AT_SimlockCodeBcd2Str(pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enCategory,
                                                        pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].astLockCode[ucGroupIndex].aucPhLockCodeEnd,
                                                        acCodeEnd);
                if ( (VOS_OK == ulCodeBeginRslt)
                  && (VOS_OK == ulCodeEndRslt) )
                {
                    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                       ",(%s,%s)",
                                                       acCodeBegin,
                                                       acCodeEnd);
                }
                else
                {
                    return VOS_ERR;
                }
            }
        }

    }
    *pusLength = usLength;
    return VOS_OK;
}

VOS_UINT32 AT_RcvDrvAgentPhoneSimlockInfoQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                                     *pRcvMsg;
    DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU                *pstEvent;
    VOS_UINT8                                               ucIndex;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLength;

    /* ?????????????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;

    pstEvent        = (DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU *)pRcvMsg->aucContent;

    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    usLength        = 0;

    printk(KERN_ERR "\n AT_RcvDrvAgentPhoneSimlockI***QryCnf enter (AT^PHONESIMLOCKI***) %u \n", VOS_GetSlice());

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhoneSimlockInfoQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhoneSimlockInfoQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_PHONESIMLOCKINFO_READ */
    if ( AT_CMD_PHONESIMLOCKINFO_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ???????????? */
        ulResult    = AT_OK;
        /* ???????? */
        if (VOS_OK != AT_PhoneSimlockInfoPrint(pstEvent, ucIndex, &usLength))
        {
            ulResult = AT_PERSONALIZATION_OTHER_ERROR;
        }
    }
    else
    {
        /* ????????, ?????????? */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = usLength;
    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_SimlockDataReadPrint(
    DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU      stSimlockDataRead,
    VOS_UINT8                                   ucIndex,
    VOS_UINT16                                 *pusLength
)
{
    VOS_UINT16                                  usLength        = *pusLength;
    VOS_UINT8                                   ucCatIndex      = 0;
    VOS_UINT8                                   ucCatNum;

    ucCatNum = AT_MIN(stSimlockDataRead.ucSupportCategoryNum, DRV_AGENT_SUPPORT_CATEGORY_NUM);

    for (ucCatIndex = 0; ucCatIndex < ucCatNum; ucCatIndex++)
    {
        if (0 != ucCatIndex)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s",
                                               gaucAtCrLf);
        }

        /* ^SIMLOCKDATAREAD: <cat>,<indicator>,<lock_status>,<max_times>,<remain_times> */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        switch(stSimlockDataRead.astCategoryData[ucCatIndex].enCategory)
        {
            case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "NET");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK_SUBSET:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "NETSUB");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "SP");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_CORPORATE:
            case DRV_AGENT_PERSONALIZATION_CATEGORY_SIM_USIM:
            default:
                return VOS_ERR;
        }
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d",
                                           stSimlockDataRead.astCategoryData[ucCatIndex].enIndicator);
        if (DRV_AGENT_PERSONALIZATION_INDICATOR_ACTIVE == stSimlockDataRead.astCategoryData[ucCatIndex].enIndicator)
        {
            switch (stSimlockDataRead.astCategoryData[ucCatIndex].enStatus)
            {
            case DRV_AGENT_PERSONALIZATION_STATUS_READY:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   ",READY,,");
                break;
            case DRV_AGENT_PERSONALIZATION_STATUS_PIN:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   ",PIN,%d,%d",
                                                   stSimlockDataRead.astCategoryData[ucCatIndex].ucMaxUnlockTimes,
                                                   stSimlockDataRead.astCategoryData[ucCatIndex].ucRemainUnlockTimes);
                break;
            case DRV_AGENT_PERSONALIZATION_STATUS_PUK:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   ",PUK,,");
                break;
            default:
                return VOS_ERR;
            }
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",,,");
        }

    }
    *pusLength = usLength;
    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentSimlockDataReadQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                         *pRcvMsg;
    DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU     *pstEvent;
    VOS_UINT8                                   ucIndex;
    VOS_UINT8                                   ucSimlockType;
    VOS_UINT32                                  ulResult;
    VOS_UINT16                                  usLength;


    printk(KERN_ERR "\n AT_RcvDrvAgentSimlockDataReadQryCnf enter\n");


    /* ?????????????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    ucSimlockType   = (VOS_UINT8)AT_GetSimlockUnlockCategoryFromClck();
    usLength        = 0;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentSimlockDataReadQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSimlockDataReadQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    if ( AT_CMD_SIMLOCKDATAREAD_READ != gastAtClientTab[ucIndex].CmdCurrentOpt
      && AT_CMD_CLCK_SIMLOCKDATAREAD != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ???????????????????? */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ???????????? */
        ulResult    = AT_OK;
        /* ???????? */
        if ( AT_CMD_CLCK_SIMLOCKDATAREAD != gastAtClientTab[ucIndex].CmdCurrentOpt)
        {
            if ( VOS_OK != AT_SimlockDataReadPrint(*pstEvent, ucIndex, &usLength))
            {
                ulResult = AT_PERSONALIZATION_OTHER_ERROR;
            }
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s: %d",
                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                   pstEvent->astCategoryData[ucSimlockType].enIndicator);
        }
    }
    else
    {
        /* ????????, ?????????? */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = usLength;

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentPhonePhynumSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_PHONEPHYNUM_SET_CNF_STRU *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????????????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PHONEPHYNUM_SET_CNF_STRU *)pRcvMsg->aucContent;

    printk(KERN_ERR "\n AT_RcvDrvAgentPhonePhynumSetCnf enter \n");

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhonePhynumSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhonePhynumSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_PHONEPHYNUM_SET */
    if ( AT_CMD_PHONEPHYNUM_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ???????????? */
        ulResult    = AT_OK;
    }
    else
    {
        /* ????????, ?????????? */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentPhonePhynumQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_PHONEPHYNUM_QRY_CNF_STRU *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT32                          i;

    printk(KERN_ERR "\n AT_RcvDrvAgentPhonePhynumQryCnf enter \n");

    /* ?????????????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PHONEPHYNUM_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    usLength        = 0;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhonePhynumQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhonePhynumQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_PHONEPHYNUM_READ */
    if ( AT_CMD_PHONEPHYNUM_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        ulResult    = AT_OK;
        /* ?????????????????? */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s: IMEI,",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0; i < DRV_AGENT_RSA_CIPHERTEXT_LEN; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%02X",
                                          pstEvent->aucImeiRsa[i]);
        }
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s%s: SN,",
                                           gaucAtCrLf,
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0; i < DRV_AGENT_RSA_CIPHERTEXT_LEN; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%02X",
                                          pstEvent->aucSnRsa[i]);
        }
    }
    else
    {
        /* ????????, ?????????? */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = usLength;
    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32  AT_PortCtrlTmpSndMsg(VOS_VOID)
{
    OM_HSIC_CONNECT_MSG_STRU           *pstMsg;

    pstMsg = (OM_HSIC_CONNECT_MSG_STRU*)PS_ALLOC_MSG(WUEPS_PID_AT,
                                                     sizeof(OM_HSIC_CONNECT_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return AT_ERROR;
    }

    pstMsg->ulReceiverPid  = MSP_PID_DIAG_APP_AGENT;
    pstMsg->ulMsgName      = AT_OM_HSIC_PORT_CONNECT;

    if (VOS_OK !=  PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        return AT_ERROR;
    }

    return AT_OK;
}


VOS_UINT32 AT_RcvDrvAgentPortctrlTmpSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_PORTCTRLTMP_SET_CNF_STRU *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????????????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PORTCTRLTMP_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortctrlTmpSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortctrlTmpSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_PORTCTRLTMP_SET */
    if ( AT_CMD_PORTCTRLTMP_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ??OM??????????OM???? */
        ulResult    = AT_PortCtrlTmpSndMsg();
        if ( AT_OK != ulResult)
        {
             ulResult    = AT_ERROR;
        }
    }
    else
    {
        /* ????????????, ?????????? */
        ulResult         = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;;
    }

    gstAtSendData.usBufLen = 0;
    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentPortAttribSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                   *pRcvMsg;
    DRV_AGENT_PORTATTRIBSET_SET_CNF_STRU *pstEvent;
    VOS_UINT8                             ucIndex;
    VOS_UINT32                            ulResult;

    /* ?????????????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PORTATTRIBSET_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortAttribSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortAttribSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_PORTATTRIBSET_SET */
    if ( AT_CMD_PORTATTRIBSET_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        ulResult    = AT_OK;
    }
    else
    {
        /* ????????????, ?????????? */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentPortAttribSetQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                                     *pRcvMsg;
    DRV_AGENT_PORTATTRIBSET_QRY_CNF_STRU                   *pstEvent;
    VOS_UINT8                                               ucIndex;
    VOS_UINT32                                              ulResult;

    /* ?????????????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PORTATTRIBSET_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortAttribSetQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortAttribSetQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_PORTATTRIBSET_READ */
    if ( AT_CMD_PORTATTRIBSET_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* ???????????????????? */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        if( (DRV_AGENT_PORT_STATUS_OFF  == pstEvent->enPortStatus)
         || (DRV_AGENT_PORT_STATUS_ON   == pstEvent->enPortStatus))
        {
            ulResult = AT_OK;
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstEvent->enPortStatus);
        }
        else
        {
            ulResult = AT_PERSONALIZATION_OTHER_ERROR;
        }
    }
    else
    {
        /* ????????????, ?????????? */
        ulResult = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentOpwordSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                      *pRcvMsg;
    DRV_AGENT_OPWORD_SET_CNF_STRU           *pstEvent;
    VOS_UINT8                                ucIndex;
    VOS_UINT32                               ulResult;

    /* ?????????????? */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_OPWORD_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentOpwordSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentOpwordSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_OPWORD_SET */
    if ( AT_CMD_OPWORD_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ?????????????????????? */
        g_enATE5RightFlag   = AT_E5_RIGHT_FLAG_YES;
        ulResult            = AT_OK;
    }
    else
    {
        /* ????????????, ?????????? */
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;
    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}



VOS_UINT32 AT_RcvDrvAgentAntSwitchSetCnf(VOS_VOID *pstData)
{
    VOS_UINT8                           ucIndex = 0;
    DRV_AGENT_ANTSWITCH_SET_CNF_STRU   *pstAntSwitchCnf;
    DRV_AGENT_MSG_STRU                 *pRcvMsg;

    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pstData;
    pstAntSwitchCnf = (DRV_AGENT_ANTSWITCH_SET_CNF_STRU *)pRcvMsg->aucContent;
    /* ????ClientID???????????? */
    if(AT_FAILURE == At_ClientIdToUserId(pstAntSwitchCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchSetCnf: Get Index Fail!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* AT??????????^ANTSWITCH?????????????????????? */
    if (AT_CMD_ANTSWITCH_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchSetCnf: Error Option!");
        return VOS_ERR;
    }

    /* ????AT_STOP_TIMER_CMD_READY????AT??????????????READY???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_OK != pstAntSwitchCnf->ulResult)
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentAntSwitchQryCnf(VOS_VOID *pstData)
{
    VOS_UINT8                           ucIndex = 0;
    DRV_AGENT_ANTSWITCH_QRY_CNF_STRU   *pstAntSwitchCnf;
    DRV_AGENT_MSG_STRU                 *pRcvMsg;

    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pstData;
    pstAntSwitchCnf = (DRV_AGENT_ANTSWITCH_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ????ClientID???????????? */
    if(AT_FAILURE == At_ClientIdToUserId(pstAntSwitchCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchQryCnf: Get Index Fail!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* AT??????????^ANTSWITCH?????????????????????? */
    if (AT_CMD_ANTSWITCH_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchQryCnf: Error Option!");
        return VOS_ERR;
    }

    /* ????AT_STOP_TIMER_CMD_READY????AT??????????????READY???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = 0;

    if(pstAntSwitchCnf->ulResult == VOS_OK)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstAntSwitchCnf->ulState);

        At_FormatResultData(ucIndex, AT_OK);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }

    return VOS_OK;
}



VOS_UINT32 AT_RcvMtaCposSetCnf(VOS_VOID *pMsg)
{
    /* ???????????? */
    AT_MTA_MSG_STRU                  *pstCposMsg;
    MTA_AT_CPOS_CNF_STRU             *pstEvent;
    VOS_UINT8                         ucIndex;
    VOS_UINT32                        ulResult;

    /* ?????????????? */
    pstCposMsg  = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent    = (MTA_AT_CPOS_CNF_STRU*)pstCposMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCposMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaCposSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCposSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_CPOS_SET */
    if ( AT_CMD_CPOS_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaCposSetCnf: WARNING:Not AT_CMD_CPOS_SET!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( MTA_AT_RESULT_NO_ERROR == pstEvent->enResult )
    {
        ulResult            = AT_OK;
    }
    else
    {
        ulResult            = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;
    /* ????AT_FormatResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaCposrInd(VOS_VOID *pMsg)
{
    /* ???????????? */
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstCposrMsg;
    MTA_AT_CPOSR_IND_STRU              *pstEvent;
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, Begin */
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    /* ?????????????? */
    pstCposrMsg = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent    = (MTA_AT_CPOSR_IND_STRU*)pstCposrMsg->aucContent;

    /* ????ClientId????ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCposrMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCposrInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    /* ??????????AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->enCposrReport?????????????????????????????????????? */
    if (AT_CPOSR_ENABLE == pstAgpsCtx->enCposrReport)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s+CPOSR: %s%s",
                                                        gaucAtCrLf, pstEvent->acXmlText, gaucAtCrLf);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
    }
    else
    {
        AT_WARN_LOG1("AT_RcvMtaCposrInd: +CPOSR: ", pstAgpsCtx->enCposrReport);
    }
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, End */

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaXcposrRptInd(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstXcposrRptMsg;
    MTA_AT_XCPOSRRPT_IND_STRU          *pstEvent;
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, Begin */

    /* ?????????????? */
    pstXcposrRptMsg = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent        = (MTA_AT_XCPOSRRPT_IND_STRU*)pstXcposrRptMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstXcposrRptMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaXcposrRptInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ??????????AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->enXcposrReport???????????????????????????????? */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^XCPOSRRPT: %d%s",
                                                        gaucAtCrLf,
                                                        pstEvent->ulClearFlg,
                                                        gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaCgpsClockSetCnf(VOS_VOID *pMsg)
{
    /* ???????????? */
    VOS_BOOL                            bEnable;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg    = VOS_NULL_PTR;
    MTA_AT_CGPSCLOCK_CNF_STRU          *pstSetCnf    = VOS_NULL_PTR;

    pstMtaMsg = (AT_MTA_MSG_STRU*)pMsg;

    pstSetCnf = (MTA_AT_CGPSCLOCK_CNF_STRU*)pstMtaMsg->aucContent;

    /* ?????????????? */
    ucIndex             = 0;
    bEnable             = 0;
    enModemId           = MODEM_ID_0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCgpsClockSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCgpsClockSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CGPSCLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaCgpsClockSetCnf : Current Option is not AT_CMD_CGPSCLOCK_SET.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if (MTA_AT_RESULT_NO_ERROR != pstSetCnf->enResult)
    {
        gstAtSendData.usBufLen = 0;
        /* ????AT_FormATResultDATa???????????? */
        At_FormatResultData(ucIndex, AT_ERROR);

        return VOS_OK;
    }

    if (VOS_OK != AT_GetModemIdFromClient(gastAtClientTab[ucIndex].usClientId, &enModemId))
    {
        enModemId = MODEM_ID_0;
    }

    bEnable = AT_GetCgpsCLockEnableFlgByModemId(enModemId);

    if (VOS_OK != AT_SetCgpsClock( bEnable,
                                   pstSetCnf->enModemId,
                                   pstSetCnf->enRatMode) )
    {
        gstAtSendData.usBufLen = 0;
        /* ????AT_FormATResultDATa???????????? */
        At_FormatResultData(ucIndex, AT_ERROR);

        AT_ERR_LOG("AT_RcvMtaCgpsClockSetCnf: AT_CfgGpsRefClk() failed!");
        return VOS_OK;
    }

    gstAtSendData.usBufLen = 0;
    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}

VOS_VOID At_ProcMtaMsg(AT_MTA_MSG_STRU *pstMsg)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulRst;

    /*??g_astAtProcMsgFromMtaTab??????????????*/
    ulMsgCnt = sizeof(g_astAtProcMsgFromMtaTab)/sizeof(AT_PROC_MSG_FROM_MTA_STRU);

    /*??????????????MSG ID*/
    ulMsgId  = ((AT_MTA_MSG_STRU *)pstMsg)->ulMsgId;

    /*g_astAtProcMsgFromMtaTab??????????????????*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if (g_astAtProcMsgFromMtaTab[i].ulMsgType == ulMsgId)
        {
            ulRst = g_astAtProcMsgFromMtaTab[i].pProcMsgFunc(pstMsg);

            if (VOS_ERR == ulRst)
            {
                AT_ERR_LOG("At_ProcMtaMsg: Msg Proc Err!");
            }

            return;
        }
    }

    /*??????????????????*/
    if (ulMsgCnt == i)
    {
        AT_ERR_LOG("At_ProcMtaMsg: Msg Id is invalid!");
    }

    return;
}


VOS_VOID AT_ProcXpdsMsg(AT_XPDS_MSG_STRU *pstMsg)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulRst;

    /*??g_astAtProcMsgFromXpdsTab??????????????*/
    ulMsgCnt = sizeof(g_astAtProcMsgFromXpdsTab)/sizeof(AT_PROC_MSG_FROM_XPDS_STRU);

    /*??????????????MSG ID*/
    ulMsgId  = ((AT_XPDS_MSG_STRU *)pstMsg)->enMsgId;

    /*g_astAtProcMsgFromXpdsTab??????????????????*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if (g_astAtProcMsgFromXpdsTab[i].ulMsgType == ulMsgId)
        {
            ulRst = g_astAtProcMsgFromXpdsTab[i].pProcMsgFunc(pstMsg);

            if (VOS_ERR == ulRst)
            {
                AT_ERR_LOG("AT_ProcXpdsMsg: Msg Proc Err!");
            }

            return;
        }
    }

    /*??????????????????*/
    if (ulMsgCnt == i)
    {
        AT_ERR_LOG("At_ProcXpdsMsg: Msg Id is invalid!");
    }

    return;
}



VOS_UINT32 AT_RcvMtaSimlockUnlockSetCnf( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_SIMLOCKUNLOCK_CNF_STRU      *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????? */
    pstRcvMsg       = (AT_MTA_MSG_STRU *)pMsg;
    pstEvent        = (MTA_AT_SIMLOCKUNLOCK_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ????ClientId????ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSimlockUnlockSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSimlockUnlockSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    if (AT_CMD_SIMLOCKUNLOCK_SET    != gastAtClientTab[ucIndex].CmdCurrentOpt
     && AT_CMD_CLCK_SIMLOCKUNLOCK   != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSimlockUnlockSetCnf: NOT CURRENT CMD OPTION!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ?????????????????????? */
    if (MTA_AT_RESULT_NO_ERROR == pstEvent->enResult)
    {
        /* ??????????????OK */
        ulResult    = AT_OK;
    }
    else
    {
        /* ??????????????ERROR */
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaQryNmrCnf( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pRcvMsg      = VOS_NULL_PTR;
    MTA_AT_QRY_NMR_CNF_STRU            *pstQryNmrCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulNmrDataIndex;
    VOS_UINT16                          usLength;

    /* ?????? */
    pRcvMsg      = (AT_MTA_MSG_STRU *)pMsg;
    pstQryNmrCnf = (MTA_AT_QRY_NMR_CNF_STRU *)(pRcvMsg->aucContent);

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryNmrCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryNmrCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CNMR_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    if (MTA_AT_RESULT_ERROR == pstQryNmrCnf->enResult)
    {
        /* ????????????????error */
        gstAtSendData.usBufLen = 0;

        /* ????AT???? */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        /* ???????? */
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_OK;
    }

    usLength = 0;

    /* ??AT^CNMR?????????????????????????????????????????? */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    if (0 == pstQryNmrCnf->ucTotalIndex)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%d,%d",
                                           0,
                                           0);

        gstAtSendData.usBufLen = usLength;

        /* ????AT???? */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        /* ???????? */
        At_FormatResultData(ucIndex, AT_OK);
        return VOS_OK;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,%d,",
                                       pstQryNmrCnf->ucTotalIndex,
                                       pstQryNmrCnf->ucCurrIndex);

    for (ulNmrDataIndex = 0; ulNmrDataIndex < pstQryNmrCnf->usNMRLen; ulNmrDataIndex++)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%02x",
                                           pstQryNmrCnf->aucNMRData[ulNmrDataIndex]);
    }

    if (pstQryNmrCnf->ucTotalIndex != pstQryNmrCnf->ucCurrIndex)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s",
                                          gaucAtCrLf);

         At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
    }


    if (pstQryNmrCnf->ucTotalIndex == pstQryNmrCnf->ucCurrIndex)
    {
        At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

        gstAtSendData.usBufLen = 0;

        /* ????AT???? */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        /* ???????? */
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaWrrAutotestQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU   *pstWrrAutotestCnf   = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRsltNum;

    /* ?????? */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrAutotestCnf   = (MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;
    ulRsltNum           = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrAutotestQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrAutotestQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CWAS_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrAutotestQryCnf : Current Option is not AT_CMD_CWAS_QUERY.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^CWAS???????? */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrAutotestCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        if (pstWrrAutotestCnf->stWrrAutoTestRslt.ulRsltNum > 0)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                             "%d",
                                                             pstWrrAutotestCnf->stWrrAutoTestRslt.aulRslt[0]);

            ulRsltNum =  AT_MIN(pstWrrAutotestCnf->stWrrAutoTestRslt.ulRsltNum, (MTA_AT_WRR_AUTOTEST_MAX_RSULT_NUM - 1));

            for (i = 1; i < ulRsltNum; i++)
            {
                gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                                 (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                 (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                                 ",%d",
                                                                 pstWrrAutotestCnf->stWrrAutoTestRslt.aulRslt[i]);
            }
        }
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaWrrCellinfoQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg              = VOS_NULL_PTR;
    MTA_AT_WRR_CELLINFO_QRY_CNF_STRU   *pstWrrCellinfoQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          i;
    VOS_UINT32                          ulCellNum;

    /* ?????? */
    pRcvMsg                 = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrCellinfoQryCnf    = (MTA_AT_WRR_CELLINFO_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult                = AT_OK;
    ucIndex                 = 0;
    ulCellNum               = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellinfoQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellinfoQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CELLINFO_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellinfoQryCnf : Current Option is not AT_CMD_CELLINFO_QUERY.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^CELLINFO???????? */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrCellinfoQryCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        /*????????????????????????0*/
        if ( 0 == pstWrrCellinfoQryCnf->stWrrCellInfo.ulCellNum )
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR*)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                               "no cellinfo rslt");
        }

        ulCellNum = AT_MIN(pstWrrCellinfoQryCnf->stWrrCellInfo.ulCellNum, MTA_AT_WRR_MAX_NCELL_NUM);

        for (i = 0; i < ulCellNum; i++)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                             "%d,%d,%d,%d\r\n",
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].usCellFreq,
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].usPrimaryScramCode,
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].sCpichRscp,
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].sCpichEcN0);
        }
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}




VOS_UINT32 AT_RcvMtaWrrMeanrptQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_MEANRPT_QRY_CNF_STRU    *pstWrrMeanrptQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;
    VOS_UINT32                          i;
    VOS_UINT32                          ulCellNumLoop;
    VOS_UINT32                          ulRptNum;
    VOS_UINT16                          usCellNum;

    /* ?????? */
    pRcvMsg                 = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrMeanrptQryCnf     = (MTA_AT_WRR_MEANRPT_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult                = AT_OK;
    usLength                = 0;
    ucIndex                 = 0;
    ulRptNum                = 0;
    usCellNum               = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrMeanrptQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrMeanrptQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_MEANRPT_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrMeanrptQryCnf : Current Option is not AT_CMD_MEANRPT_QUERY.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^MEANRPT???????? */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrMeanrptQryCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                           "%d",
                                           pstWrrMeanrptQryCnf->stMeanRptRslt.ulRptNum);

        ulRptNum = AT_MIN(pstWrrMeanrptQryCnf->stMeanRptRslt.ulRptNum, MTA_AT_WRR_MAX_MEANRPT_NUM);

        for ( i = 0 ; i < ulRptNum; i++ )
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                               "\r\n0x%X,%d",
                                                pstWrrMeanrptQryCnf->stMeanRptRslt.astMeanRptInfo[i].usEventId,
                                                pstWrrMeanrptQryCnf->stMeanRptRslt.astMeanRptInfo[i].usCellNum );

            usCellNum = AT_MIN(pstWrrMeanrptQryCnf->stMeanRptRslt.astMeanRptInfo[i].usCellNum, MTA_AT_WRR_ONE_MEANRPT_MAX_CELL_NUM);

            for ( ulCellNumLoop = 0; ulCellNumLoop < usCellNum; ulCellNumLoop++ )
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                                   ",%d",
                                                   pstWrrMeanrptQryCnf->stMeanRptRslt.astMeanRptInfo[i].ausPrimaryScramCode[ulCellNumLoop]);
            }

        }
        gstAtSendData.usBufLen = usLength;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaWrrCellSrhSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_SET_CNF_STRU    *pstWrrCellSrhSetCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrCellSrhSetCnf = (MTA_AT_WRR_CELLSRH_SET_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_WAS_MNTN_SET_CELLSRH != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhSetCnf : Current Option is not AT_CMD_WAS_MNTN_SET_CELLSRH.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^CELLSRH???????? */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrCellSrhSetCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaWrrCellSrhQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_QRY_CNF_STRU    *pstWrrCellSrhQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrCellSrhQryCnf = (MTA_AT_WRR_CELLSRH_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_WAS_MNTN_QRY_CELLSRH != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhQryCnf : Current Option is not AT_CMD_WAS_MNTN_QRY_CELLSRH.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^FREQLOCK???????????? */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrCellSrhQryCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR*)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        (TAF_INT32)pstWrrCellSrhQryCnf->ucCellSearchType);

    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaWrrFreqLockSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg           = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_SET_CNF_STRU   *pstWrrFreqlockCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrFreqlockCnf   = (MTA_AT_WRR_FREQLOCK_SET_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_FREQLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockSetCnf : Current Option is not AT_CMD_FREQLOCK_SET.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^FREQLOCK???????? */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrFreqlockCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaWrrFreqLockQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg           = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU   *pstWrrFreqlockCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrFreqlockCnf   = (MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_FREQLOCK_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockQryCnf : Current Option is not AT_CMD_FREQLOCK_QUERY.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^FREQLOCK???????????? */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstWrrFreqlockCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        if (VOS_FALSE == pstWrrFreqlockCnf->stFreqLockInfo.ucFreqLockEnable)
        {
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                                            (TAF_CHAR*)pgucAtSndCodeAddr,
                                                            "%s: %d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            (TAF_INT32)pstWrrFreqlockCnf->stFreqLockInfo.ucFreqLockEnable);
        }
        else
        {
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                                            (TAF_CHAR*)pgucAtSndCodeAddr,
                                                            "%s: %d,%d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            (TAF_INT32)pstWrrFreqlockCnf->stFreqLockInfo.ucFreqLockEnable,
                                                            (TAF_INT32)pstWrrFreqlockCnf->stFreqLockInfo.usLockedFreq);
        }

    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaWrrRrcVersionSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                        *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU    *pstWrrVersionSetCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* ?????? */
    pRcvMsg                 = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrVersionSetCnf     = (MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU *)pRcvMsg->aucContent;
    ulResult                = AT_OK;
    ucIndex                 = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_RRC_VERSION_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionSetCnf : Current Option is not AT_CMD_RRC_VERSION_SET.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^FREQLOCK???????? */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrVersionSetCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        /* ??????????????????????NV */
        /* Modified by l60609 for DSDA Phase III, 2013-3-5, Begin */
        AT_ReadWasCapabilityNV();
        /* Modified by l60609 for DSDA Phase III, 2013-3-5, End */

        ulResult = AT_OK;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}




VOS_UINT32 AT_RcvMtaWrrRrcVersionQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                        *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU    *pstWrrVersionQryCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* ?????? */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrVersionQryCnf = (MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_RRC_VERSION_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionQryCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^FREQLOCK???????????? */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrVersionQryCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        (TAF_INT32)pstWrrVersionQryCnf->ucRrcVersion);

    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaAcInfoQueryCnf(VOS_VOID *pstMsg)
{
    TAF_MMA_AC_INFO_QRY_CNF_STRU       *pstAcInfoQueryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pstAcInfoQueryCnf       = (TAF_MMA_AC_INFO_QRY_CNF_STRU*)pstMsg;
    usLength                = 0;
    ulResult                = AT_OK;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstAcInfoQueryCnf->stCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAcInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAcInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_LOCINFO_READ */
    if (AT_CMD_ACINFO_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT_STOP_TIMER_CMD_READY????AT??????????????READY???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ????????????????????,??????????????ERROR */
    if (VOS_OK != pstAcInfoQueryCnf->ulRslt)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s:%d,%d,%d,%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellCsAcInfo.enSrvDomain),/* ?????????? */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellCsAcInfo.enCellAcType),/* ???????????????????? */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellCsAcInfo.ucRestrictRegister),/* ???????????????? */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellCsAcInfo.ucRestrictPagingRsp));/* ???????????????? */

        /* ???? */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s",
                                          gaucAtCrLf);

        usLength  += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s:%d,%d,%d,%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellPsAcInfo.enSrvDomain),/* ?????????? */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellPsAcInfo.enCellAcType),/* ???????????????????? */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellPsAcInfo.ucRestrictRegister),/* ???????????????? */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellPsAcInfo.ucRestrictPagingRsp));/* ???????????????? */

        gstAtSendData.usBufLen = usLength;

    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}



VOS_UINT32 AT_RcvMtaQryCurcCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg          = VOS_NULL_PTR;
    MTA_AT_CURC_QRY_CNF_STRU               *pstMtaAtQryCurcCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usLength;
    VOS_UINT8                               ucLoop;

    /* ?????? */
    pstRcvMsg           = (AT_MTA_MSG_STRU *)pstMsg;
    pstMtaAtQryCurcCnf  = (MTA_AT_CURC_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;
    usLength            = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryCurcCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryCurcCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CURC_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaQryCurcCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^CURC???????????? */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstMtaAtQryCurcCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        usLength        += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                  "%s: %d",
                                                  g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                  pstMtaAtQryCurcCnf->enCurcRptType);

        /* ????<mode>??????2??????????????<report_cfg> */
        if (AT_MTA_RPT_GENERAL_CONTROL_CUSTOM == pstMtaAtQryCurcCnf->enCurcRptType)
        {
            usLength    += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                  ",0x");

            for (ucLoop = 0; ucLoop < AT_CURC_RPT_CFG_MAX_SIZE; ucLoop++)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%02X",
                                                   pstMtaAtQryCurcCnf->aucRptCfg[ucLoop]);
            }
        }
    }

    gstAtSendData.usBufLen = usLength;

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaSetUnsolicitedRptCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg            = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU    *pstSetUnsolicitedCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* ?????? */
    pstRcvMsg               = (AT_MTA_MSG_STRU *)pstMsg;
    pstSetUnsolicitedCnf    = (MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult                = AT_OK;
    ucIndex                 = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetUnsolicitedRptCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetUnsolicitedRptCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_UNSOLICITED_RPT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetUnsolicitedRptCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ?????????????? */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstSetUnsolicitedCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}


VOS_UINT32 AT_RcvMtaQryUnsolicitedRptCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg            = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU    *pstQryUnsolicitedCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* ?????? */
    pstRcvMsg               = (AT_MTA_MSG_STRU *)pstMsg;
    pstQryUnsolicitedCnf    = (MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult                = AT_OK;
    ucIndex                 = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryUnsolicitedRptCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryUnsolicitedRptCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_UNSOLICITED_RPT_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaQryUnsolicitedRptCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ?????????????????? */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstQryUnsolicitedCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        /* ucIndex?????????? */
        ulResult = AT_ProcMtaUnsolicitedRptQryCnf(ucIndex, pstMsg);
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_ProcMtaUnsolicitedRptQryCnf(
    VOS_UINT8                               ucIndex,
    VOS_VOID                               *pstMsg
)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg            = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU    *pstQryUnsolicitedCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    /* ucIndex?????????????????? */

    pstRcvMsg               = (AT_MTA_MSG_STRU *)pstMsg;
    pstQryUnsolicitedCnf    = (MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult                = AT_OK;

    switch (pstQryUnsolicitedCnf->enReqType)
    {
        /* TIME?????????? */
        case AT_MTA_QRY_TIME_RPT_TYPE:
            gstAtSendData.usBufLen =
                (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: %d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       pstQryUnsolicitedCnf->u.ucTimeRptFlg);
            break;

        /* pstQryUnsolicitedCnf?????????????? */
        /* CTZR?????????? */
        case AT_MTA_QRY_CTZR_RPT_TYPE:
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: %d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       pstQryUnsolicitedCnf->u.ucCtzrRptFlg);
            break;

        /* CSSN?????????? */
        case AT_MTA_QRY_CSSN_RPT_TYPE:
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            "%s: %d,%d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            pstQryUnsolicitedCnf->u.stCssnRptFlg.ucCssiRptFlg,
                                                            pstQryUnsolicitedCnf->u.stCssnRptFlg.ucCssuRptFlg);
            break;

        /* CUSD?????????? */
        case AT_MTA_QRY_CUSD_RPT_TYPE:
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,"%s: %d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            pstQryUnsolicitedCnf->u.ucCusdRptFlg);
            break;

        default:
            ulResult = AT_CME_UNKNOWN;

    }

    return ulResult;
}



VOS_UINT32 AT_RcvMmaCerssiInfoQueryCnf(VOS_VOID *pstMsg)
{
    TAF_MMA_CERSSI_INFO_QRY_CNF_STRU   *pstCerssiInfoQueryCnf = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_UINT8                          *pucSystemAppConfig;

    /* ?????? */
    pstCerssiInfoQueryCnf   = (TAF_MMA_CERSSI_INFO_QRY_CNF_STRU*)pstMsg;
    usLength                = 0;
    pucSystemAppConfig      = AT_GetSystemAppConfigAddr();

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCerssiInfoQueryCnf->stCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCerssiInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCerssiInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    /*??????????????????????AT_CMD_CERSSI_READ */
    if (AT_CMD_CERSSI_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT_STOP_TIMER_CMD_READY????AT??????????????READY???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ????????????????????,??????????????ERROR */
    if (TAF_ERR_NO_ERROR != pstCerssiInfoQueryCnf->enErrorCause)
    {
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_ERR;
    }
    else
    {
        if (TAF_MMA_RAT_GSM == pstCerssiInfoQueryCnf->stCerssi.enRatType)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s%s%d,%d,%d,%d,%d,%d,%d,%d,%d%s",
                                               gaucAtCrLf,
                                               gastAtStringTab[AT_STRING_CERSSI].pucText,
                                               pstNetCtx->ucCerssiReportType,
                                               pstNetCtx->ucCerssiMinTimerInterval,
                                               pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stGCellSignInfo.sRssiValue,
                                               0,
                                               255,
                                               0,
                                               0,
                                               0,
                                               0,
                                               gaucAtCrLf);

            gstAtSendData.usBufLen = usLength;

            /* ???????? */
            At_FormatResultData(ucIndex, AT_OK);
            return VOS_OK;
        }

        if (TAF_MMA_RAT_WCDMA == pstCerssiInfoQueryCnf->stCerssi.enRatType)
        {
            if (TAF_UTRANCTRL_UTRAN_MODE_FDD == pstCerssiInfoQueryCnf->stCerssi.ucCurrentUtranMode)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s%s%d,%d,%d,%d,%d,%d,%d,%d,%d%s",
                                                   gaucAtCrLf,
                                                   gastAtStringTab[AT_STRING_CERSSI].pucText,
                                                   pstNetCtx->ucCerssiReportType,
                                                   pstNetCtx->ucCerssiMinTimerInterval,
                                                   0,      /* rssi */
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stWCellSignInfo.sRscpValue,
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stWCellSignInfo.sEcioValue,
                                                   0,
                                                   0,
                                                   0,
                                                   0,
                                                   gaucAtCrLf);

                gstAtSendData.usBufLen = usLength;

                /* ???????? */
                At_FormatResultData(ucIndex, AT_OK);
                return VOS_OK;
            }
            else
            {
                /* ??fdd 3g ??????ecio??????????255 */
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s%s%d,%d,%d,%d,%d,%d,%d,%d,%d%s",
                                                   gaucAtCrLf,
                                                   gastAtStringTab[AT_STRING_CERSSI].pucText,
                                                   pstNetCtx->ucCerssiReportType,
                                                   pstNetCtx->ucCerssiMinTimerInterval,
                                                   0,      /* rssi */
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stWCellSignInfo.sRscpValue,
                                                   255,
                                                   0,
                                                   0,
                                                   0,
                                                   0,
                                                   gaucAtCrLf);



                gstAtSendData.usBufLen = usLength;

                /* ???????? */
                At_FormatResultData(ucIndex, AT_OK);
                return VOS_OK;

            }
        }


        if (TAF_MMA_RAT_LTE == pstCerssiInfoQueryCnf->stCerssi.enRatType)
        {
            /* LTE????cerssi??????????L4A????NAS????atCerssiInfoCnfProc?????????? */
            if (SYSTEM_APP_ANDROID != *pucSystemAppConfig)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s%s%d,%d,0,0,255,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d%s",
                                                   gaucAtCrLf,
                                                   gastAtStringTab[AT_STRING_CERSSI].pucText,
                                                   pstNetCtx->ucCerssiReportType,
                                                   pstNetCtx->ucCerssiMinTimerInterval,
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.sRsrp,
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.sRsrq,
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.lSINR,
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stCQI.usRI,
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stCQI.ausCQI[0],
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stCQI.ausCQI[1],
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stRxAntInfo.ucRxANTNum,
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stRxAntInfo.asRsrpRx[0],
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stRxAntInfo.asRsrpRx[1],
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stRxAntInfo.asRsrpRx[2],
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stRxAntInfo.asRsrpRx[3],
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stRxAntInfo.alSINRRx[0],
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stRxAntInfo.alSINRRx[1],
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stRxAntInfo.alSINRRx[2],
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stRxAntInfo.alSINRRx[3],
                                                   gaucAtCrLf);

            }
            else
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s%s%d,%d,0,0,255,%d,%d,%d,%d,%d,%d%s",
                                                   gaucAtCrLf,
                                                   gastAtStringTab[AT_STRING_CERSSI].pucText,
                                                   pstNetCtx->ucCerssiReportType,
                                                   pstNetCtx->ucCerssiMinTimerInterval,
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.sRsrp,
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.sRsrq,
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.lSINR,
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stCQI.usRI,
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stCQI.ausCQI[0],
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stCQI.ausCQI[1],
                                                   gaucAtCrLf);
            }
            gstAtSendData.usBufLen = usLength;

            /* ???????? */
            At_FormatResultData(ucIndex, AT_OK);
            return VOS_OK;
        }
    }

    /* ???????????????????????????????????? */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s%d,%d,%d,%d,%d,%d,%d,%d,%d%s",
                                        gaucAtCrLf,
                                        gastAtStringTab[AT_STRING_CERSSI].pucText,
                                        pstNetCtx->ucCerssiReportType,
                                        pstNetCtx->ucCerssiMinTimerInterval,
                                        pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stGCellSignInfo.sRssiValue,      /* rssi */
                                        pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stWCellSignInfo.sRscpValue,
                                        255,
                                        0,
                                        0,
                                        0,
                                        0,
                                        gaucAtCrLf);

    gstAtSendData.usBufLen = usLength;

    /* ???????? */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}




VOS_UINT32 AT_RcvMtaBodySarSetCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU             *pstBodySarSetCnf    = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pRcvMsg          = (AT_MTA_MSG_STRU*)pstMsg;
    pstBodySarSetCnf = (MTA_AT_RESULT_CNF_STRU*)pRcvMsg->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaBodySarSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaBodySarSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_BODYSARON_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ?????????????????????? */
    if (MTA_AT_RESULT_NO_ERROR == pstBodySarSetCnf->enResult)
    {
        ulResult    = AT_OK;

        /* ????BODYSAR ???? */
        if (AT_MTA_BODY_SAR_OFF == g_enAtBodySarState)
        {
            g_enAtBodySarState = AT_MTA_BODY_SAR_ON;
        }
        else
        {
            g_enAtBodySarState = AT_MTA_BODY_SAR_OFF;
        }
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_VOID AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_ENUM_UINT32 enCause)
{
    VOS_UINT16                          usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "%s%s%d%s",
                                        gaucAtCrLf,
                                        gastAtStringTab[AT_STRING_RESET].pucText,
                                        enCause,
                                        gaucAtCrLf);

    /* ??????????????????RIL */
    At_SendResultData(AT_CLIENT_ID_APP,  pgucAtSndCodeAddr, usLength);
    At_SendResultData(AT_CLIENT_ID_PCUI, pgucAtSndCodeAddr, usLength);

    At_SendResultData(AT_CLIENT_ID_APP5, pgucAtSndCodeAddr, usLength);
    At_SendResultData(AT_CLIENT_ID_CTRL, pgucAtSndCodeAddr, usLength);
    At_SendResultData(AT_CLIENT_ID_APP20, pgucAtSndCodeAddr, usLength);
    At_SendResultData(AT_CLIENT_ID_PCUI2, pgucAtSndCodeAddr, usLength);

    return;
}


VOS_VOID AT_StopAllTimer(VOS_VOID)
{
    VOS_UINT8                           ucModemIndex;
    VOS_UINT8                           ucClientIndex;
    VOS_UINT32                          ulTimerName;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx         = VOS_NULL_PTR;
    AT_PARSE_CONTEXT_STRU              *pstParseContext = VOS_NULL_PTR;
    AT_CLIENT_MANAGE_STRU              *pstClientContext = VOS_NULL_PTR;

    for (ucModemIndex = 0; ucModemIndex < MODEM_ID_BUTT; ucModemIndex++)
    {
        pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucModemIndex);

        /* ????S0?????? */
        if (VOS_TRUE == pstCcCtx->stS0TimeInfo.bTimerStart)
        {
            ulTimerName = pstCcCtx->stS0TimeInfo.ulTimerName;

            AT_StopRelTimer(ulTimerName, &(pstCcCtx->stS0TimeInfo.s0Timer));
            pstCcCtx->stS0TimeInfo.bTimerStart = VOS_FALSE;
            pstCcCtx->stS0TimeInfo.ulTimerName = 0;
        }

    }

    for (ucClientIndex = 0; ucClientIndex < AT_MAX_CLIENT_NUM; ucClientIndex++)
    {
        pstParseContext = &(g_stParseContext[ucClientIndex]);
        AT_StopRelTimer(ucClientIndex, &pstParseContext->hTimer);

        pstClientContext = &(gastAtClientTab[ucClientIndex]);
        AT_StopRelTimer(ucClientIndex, &pstClientContext->hTimer);
    }

    return;
}


VOS_VOID AT_ResetParseCtx(VOS_VOID)
{
    VOS_UINT8                           ucClientIndex;
    AT_PARSE_CONTEXT_STRU              *pstParseContext = VOS_NULL_PTR;

    for (ucClientIndex = 0; ucClientIndex < AT_MAX_CLIENT_NUM; ucClientIndex++)
    {
        pstParseContext = &(g_stParseContext[ucClientIndex]);

        pstParseContext->ucClientStatus = AT_FW_CLIENT_STATUS_READY;

        /* ????????????????AT???? */
        AT_ClearBlockCmdInfo(ucClientIndex);

        /* ????AT?????????????????? */
        At_ResetCombinParseInfo(ucClientIndex);

        pstParseContext->ucMode    = AT_NORMAL_MODE;
        pstParseContext->usDataLen = 0;
        pstParseContext->usCmdLineLen = 0;

        TAF_MEM_SET_S(pstParseContext->aucDataBuff, sizeof(pstParseContext->aucDataBuff), 0x00, AT_CMD_MAX_LEN);

        if (NULL != pstParseContext->pucCmdLine)
        {
            AT_FREE(pstParseContext->pucCmdLine);
            pstParseContext->pucCmdLine = NULL;
        }
    }

    return;
}


VOS_VOID AT_ResetClientTab(VOS_VOID)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucClientIndex;

    for (ucClientIndex = 0; ucClientIndex < AT_MAX_CLIENT_NUM; ucClientIndex++)
    {
        /* ???????????? */
        TAF_MEM_SET_S(&gastAtClientTab[ucClientIndex], sizeof(AT_CLIENT_MANAGE_STRU), 0x00, sizeof(AT_CLIENT_MANAGE_STRU));
    }

    /* USB PCUI */
    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_PCUI;
    gastAtClientTab[ucIndex].ucPortNo        = AT_USB_COM_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_USBCOM_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* USB Control */
    ucIndex = AT_CLIENT_TAB_CTRL_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_CTRL;
    gastAtClientTab[ucIndex].ucPortNo        = AT_CTR_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_CTR_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    ucIndex = AT_CLIENT_TAB_PCUI2_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_PCUI2;
    gastAtClientTab[ucIndex].ucPortNo        = AT_PCUI2_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_PCUI2_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* USB MODEM */
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_MODEM;
    gastAtClientTab[ucIndex].ucPortType      = AT_USB_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].ucDlci          = AT_MODEM_USER_DLCI;
    gastAtClientTab[ucIndex].ucPortNo        = AT_USB_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_MODEM_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* NDIS MODEM */
    ucIndex = AT_CLIENT_TAB_NDIS_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_NDIS;
    gastAtClientTab[ucIndex].ucPortNo        = AT_NDIS_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_NDIS_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* USB UART */
    ucIndex = AT_CLIENT_TAB_UART_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_UART;
    gastAtClientTab[ucIndex].ucPortNo        = AT_UART_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_UART_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;


    /* SOCK */
    ucIndex = AT_CLIENT_TAB_SOCK_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_SOCK;
    gastAtClientTab[ucIndex].ucPortNo        = AT_SOCK_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_SOCK_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* APP SOCK */
    ucIndex = AT_CLIENT_TAB_APPSOCK_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_APPSOCK;
    gastAtClientTab[ucIndex].ucPortNo        = AT_APP_SOCK_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_APP_SOCK_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* MAX ??NV??????????CLIENT TAB?????????? AT_MuxInit???? */

    /* APP */
    for (ucLoop = 0; ucLoop < AT_VCOM_AT_CHANNEL_MAX; ucLoop++)
    {
        ucIndex = AT_CLIENT_TAB_APP_INDEX + ucLoop;
        gastAtClientTab[ucIndex].usClientId  = AT_CLIENT_ID_APP + ucLoop;
        gastAtClientTab[ucIndex].ucPortNo    = APP_VCOM_DEV_INDEX_0 + ucLoop;
        gastAtClientTab[ucIndex].UserType    = AT_APP_USER;
        gastAtClientTab[ucIndex].ucUsed      = AT_CLIENT_USED;
    }


}


VOS_VOID AT_ResetOtherCtx(VOS_VOID)
{
    /* <CR> */
    ucAtS3          = 13;

    gaucAtCrLf[0]   = ucAtS3;

    /* <LF> */
    ucAtS4          = 10;

    gaucAtCrLf[1]   = ucAtS4;

    /* <DEL> */
    ucAtS5          = 8;

    /* ?????????????????? */
    gucAtVType      = AT_V_ENTIRE_TYPE;

    /* ????TE???????? */
    gucAtCscsType   = AT_CSCS_IRA_CODE;

    gucAtEType      = AT_E_ECHO_CMD;

    /* CONNECT <text> result code is given upon entering online data state.
       Dial tone and busy detection are disabled. */
    gucAtXType      = 0;

    /* ????LTE??????category????6 */
    g_stAtDlRateCategory.ucLteUeDlCategory = 6;
    g_stAtDlRateCategory.ucLteUeUlCategory = 6;
}


VOS_UINT32 AT_RcvCcpuResetStartInd(
    VOS_VOID                           *pstMsg
)
{
    printk(KERN_ERR "\n AT_RcvCcpuResetStartInd enter %u \n", VOS_GetSlice());
    /* ????^RESET:0???? */
    AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_CCPU_START);

    /* ???????????????????????? */
    AT_StopAllTimer();

    /* ???????????????? */
    AT_InitCtx();

    printk(KERN_ERR "\n AT_RcvCcpuResetStartInd nv write begin %u \n", VOS_GetSlice());

    /* ??C????????????????????NV?? */
    AT_WriteCcpuResetRecordNvim(VOS_TRUE);

    printk(KERN_ERR "\n AT_RcvCcpuResetStartInd nv write end %u \n", VOS_GetSlice());

    /* ????NV?? */
    AT_ReadNV();

    /* ?????????? */
    AT_InitDeviceCmd();

    /* STK?????? */
    AT_InitStk();

        printk(KERN_ERR "\n AT_RcvCcpuResetStartInd nv read end %u \n", VOS_GetSlice());

    /* AT???????????????? */
    AT_InitPara();

    /* ?????????????????? */
    AT_ResetParseCtx();

    /* ???????????? */
    AT_ResetClientTab();


    /* ?????????????????????? */
    AT_ResetOtherCtx();

    printk(KERN_ERR "\n AT_RcvCcpuResetStartInd set modem state %u \n", VOS_GetSlice());

    /* C???????????????????????????????????? */
    mdrv_set_modem_state(PS_FALSE);

    printk(KERN_ERR "\n AT_RcvCcpuResetStartInd leave %u \n", VOS_GetSlice());

    /* ????????????????????API???????????? */
    VOS_SmV(AT_GetResetSem());

    return VOS_OK;
}

VOS_UINT32 AT_RcvCcpuResetEndInd(
    VOS_VOID                           *pstMsg
)
{
    printk(KERN_ERR "\n AT_RcvCcpuResetEndInd enter %u \n", VOS_GetSlice());

    /* ?????????????????? */
    AT_SetResetFlag(VOS_FALSE);

    /* ????^RESET:1???? */
    AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_CCPU_END);

    AT_WriteCcpuResetRecordNvim(VOS_FALSE);

    printk(KERN_ERR "\n AT_RcvCcpuResetEndInd leave %u \n", VOS_GetSlice());

    return VOS_OK;
}

VOS_UINT32 AT_RcvHifiResetStartInd(
    VOS_VOID                           *pstMsg
)
{
    printk(KERN_ERR "\n AT_RcvHifiResetStartInd %u \n", VOS_GetSlice());

    /* ????^RESET:2???? */
    AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_HIFI_START);

    AT_DBG_SAVE_HIFI_RESET_NUM(1);

    return VOS_OK;
}


VOS_UINT32 AT_RcvHifiResetEndInd(
    VOS_VOID                           *pstMsg
)
{
    printk(KERN_ERR "\n AT_RcvHifiResetEndInd %u \n", VOS_GetSlice());

    /* ????^RESET:3???? */
    AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_HIFI_END);

    return VOS_OK;
}


VOS_UINT32 AT_SpyMsgProc(VOS_VOID* pstMsg)
{
    VOS_UINT32 ulRet = VOS_OK;
    TEMP_PROTECT_EVENT_AT_IND_STRU* pDataMsg = (TEMP_PROTECT_EVENT_AT_IND_STRU*)pstMsg;

    switch(pDataMsg->ulMsgId)
    {
        case ID_TEMPPRT_AT_EVENT_IND:
            ulRet = AT_ProcTempprtEventInd(pDataMsg);
            break;

        case ID_TEMPPRT_STATUS_AT_EVENT_IND:
            ulRet = AT_RcvTempprtStatusInd(pDataMsg);
            break;

        default:
            AT_WARN_LOG("AT_SpyMsgProc:WARNING:Wrong Msg!\n");
            break;
    }

    return ulRet;
}


VOS_UINT32 AT_RcvTempprtStatusInd(VOS_VOID *pMsg)
{
    TEMP_PROTECT_EVENT_AT_IND_STRU     *pstTempPrt = VOS_NULL_PTR;
    TAF_TEMP_PROTECT_CONFIG_STRU        stTempProtectPara;
    VOS_UINT32                          ulResult;

    TAF_MEM_SET_S(&stTempProtectPara, sizeof(stTempProtectPara), 0x00, sizeof(stTempProtectPara));

    /* ????????????????????????NV?? */
    ulResult = NV_ReadEx(MODEM_ID_0,
                         en_NV_Item_TEMP_PROTECT_CONFIG,
                         &stTempProtectPara,
                         sizeof(TAF_TEMP_PROTECT_CONFIG_STRU));

    if (NV_OK != ulResult)
    {
        AT_ERR_LOG("AT_RcvTempprtStatusInd: Read NV fail");
        return VOS_ERR;
    }

    if (AT_TEMPPRT_STATUS_IND_ENABLE == stTempProtectPara.ucSpyStatusIndSupport)
    {
        pstTempPrt = (TEMP_PROTECT_EVENT_AT_IND_STRU*)pMsg;

        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^THERM: %d%s",
                                                         gaucAtCrLf, pstTempPrt->ulTempProtectEvent, gaucAtCrLf);

        At_SendResultData(AT_BROADCAST_CLIENT_INDEX_MODEM_0, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

        return VOS_OK;
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaImeiVerifyQryCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                    *pRcvMsg       = VOS_NULL_PTR;
    VOS_UINT32                         *pulImeiVerify = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pRcvMsg       = (AT_MTA_MSG_STRU*)pstMsg;
    pulImeiVerify = (VOS_UINT32*)pRcvMsg->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaImeiVerifyQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaImeiVerifyQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_IMEI_VERIFY_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ????^IMEIVERIFY */
    usLength  = 0;
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "^IMEIVERIFY: ");

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       *pulImeiVerify);

    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaCgsnQryCnf(VOS_VOID *pstMsg)
{
    VOS_UINT32                          ulI;
    VOS_UINT8                           ucCheckData;
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_CGSN_QRY_CNF_STRU           *pstCgsn;
    VOS_UINT8                           aucImeiAscii[TAF_PH_IMEI_LEN];

    /* ?????? */
    ucCheckData   = 0;
    TAF_MEM_SET_S(aucImeiAscii, sizeof(aucImeiAscii), 0x00, TAF_PH_IMEI_LEN);

    pstRcvMsg = (AT_MTA_MSG_STRU*)pstMsg;
    pstCgsn   = (MTA_AT_CGSN_QRY_CNF_STRU *)pstRcvMsg->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCgsnQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCgsnQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CGSN_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ????IMEI???? */
    for (ulI = 0; ulI < (TAF_PH_IMEI_LEN - 2); ulI += 2)
    {
        aucImeiAscii[ulI]     = pstCgsn->aucImei[ulI] + 0x30;
        aucImeiAscii[ulI + 1UL] = pstCgsn->aucImei[ulI + 1UL] + 0x30;

        ucCheckData += (TAF_UINT8)(pstCgsn->aucImei[ulI]
                       +((pstCgsn->aucImei[ulI + 1UL] * 2) / 10)
                       +((pstCgsn->aucImei[ulI + 1UL] * 2) % 10));
    }
    ucCheckData = (10 - (ucCheckData%10)) % 10;

    aucImeiAscii[TAF_PH_IMEI_LEN - 2] = ucCheckData + 0x30;
    aucImeiAscii[TAF_PH_IMEI_LEN - 1] = 0;

    gstAtSendData.usBufLen  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      "%s",
                                      aucImeiAscii);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


/* Added by f62575 for SS FDN&Call Control, 2013-05-06, begin */

VOS_UINT32 AT_RcvMmaCopnInfoQueryCnf(VOS_VOID *pMsg)
{
    /* Modified by k902809 for Iteration 11, 2015-3-24, begin */
    TAF_MMA_COPN_INFO_QRY_CNF_STRU     *pstCopnInfo = VOS_NULL_PTR;
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-24, end */
    TAF_PH_OPERATOR_NAME_STRU          *pstPlmnName = VOS_NULL_PTR;
    /* Modified by k902809 for Iteration 11, 2015-3-24, begin */
    VOS_UINT16                          usFromIndex;
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-24, end */
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRet;

    /* ?????? */
    /* Modified by k902809 for Iteration 11, 2015-3-24, begin */
    pstCopnInfo   = (TAF_MMA_COPN_INFO_QRY_CNF_STRU *)pMsg;
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-24, end */
    usLength      = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCopnInfo->stCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCopnInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCopnInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_COPN_QRY */
    if (AT_CMD_COPN_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????+COPS??^MMPLMNINFO???????? */
    pstPlmnName = (TAF_PH_OPERATOR_NAME_STRU *)pstCopnInfo->aucContent;

    for (ulLoop = 0; ulLoop < pstCopnInfo->usPlmnNum; ulLoop++)
    {
        /*  +COPN: <operator in numeric format><operator in long alphanumeric format>     */
        /* ?????????? */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s: ",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        /* ?????????????????????? */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "\"%X%X%X",
                                           (TAF_MMA_PLMN_MCC_DIGIT3_MASK & pstPlmnName->PlmnId.Mcc) >> TAF_MMA_PLMN_MCC_DIGIT3_OFFSET,
                                           (TAF_MMA_PLMN_MCC_DIGIT2_MASK & pstPlmnName->PlmnId.Mcc) >> TAF_MMA_PLMN_MCC_DIGIT2_OFFSET,
                                           (TAF_MMA_PLMN_MCC_DIGIT1_MASK & pstPlmnName->PlmnId.Mcc) >> TAF_MMA_PLMN_MCC_DIGIT1_OFFSET);

        if (TAF_MMA_PLMN_MNC_DIGIT3_MASK != (TAF_MMA_PLMN_MNC_DIGIT3_MASK & pstPlmnName->PlmnId.Mnc))
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                               "%X",
                                               (TAF_MMA_PLMN_MNC_DIGIT3_MASK & pstPlmnName->PlmnId.Mnc) >> TAF_MMA_PLMN_MNC_DIGIT3_OFFSET);

        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%X%X\"",
                                           (TAF_MMA_PLMN_MNC_DIGIT2_MASK & pstPlmnName->PlmnId.Mnc) >> TAF_MMA_PLMN_MNC_DIGIT2_OFFSET,
                                           (TAF_MMA_PLMN_MNC_DIGIT1_MASK & pstPlmnName->PlmnId.Mnc) >> TAF_MMA_PLMN_MNC_DIGIT1_OFFSET);

        /* ?????????????? */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"");

        /* ?????????????? */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s",
                                           pstPlmnName->aucOperatorNameLong);

        /* ???????? */
        /* ?????????????? */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "\"%s",
                                           gaucAtCrLf);

        At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

        usLength = 0;

        pstPlmnName++;

    }

    /*
    AT????????MMA????????????????????????????????????????????: ????????????????
    ??????????????????????????????????????????????:
    AT????????????50??????????????????????????????????????????????????????????????????????
    ??????????????????????????????50????????????????????
    ??????????????50??????????AT??????????????????????????MMA??????????????????????0
    */
    if (pstCopnInfo->usPlmnNum < TAF_MMA_COPN_PLMN_MAX_NUM)
    {
        /* ????AT_STOP_TIMER_CMD_READY????AT??????????????READY???? */
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_OK);
    }
    else
    {
        usFromIndex = pstCopnInfo->usFromIndex + pstCopnInfo->usPlmnNum;

        /* Modified by k902809 for Iteration 11, 2015-3-24, begin */
        ulRet = TAF_MMA_QryCopnInfoReq(WUEPS_PID_AT,
                                       gastAtClientTab[ucIndex].usClientId,
                                       usFromIndex,
                                       0);

        /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-24, end */
        if (VOS_TRUE != ulRet)
        {
            /* ????AT_STOP_TIMER_CMD_READY????AT??????????????READY???? */
            AT_STOP_TIMER_CMD_READY(ucIndex);
            gstAtSendData.usBufLen = 0;
            At_FormatResultData(ucIndex, AT_ERROR);
        }
    }
    return VOS_OK;
}

/* Added by f62575 for SS FDN&Call Control, 2013-05-06, end */


VOS_UINT32 AT_RcvMtaSetNCellMonitorCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                 *pstSetCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* ?????? */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pstMsg;
    pstSetCnf    = (MTA_AT_RESULT_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult     = AT_OK;
    ucIndex      = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetNCellMonitorCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetNCellMonitorCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_NCELL_MONITOR_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetNCellMonitorCnf : Current Option is not AT_CMD_NCELL_MONITOR_SET.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ?????????????? */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstSetCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}


VOS_UINT32 AT_RcvMtaQryNCellMonitorCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg      = VOS_NULL_PTR;
    MTA_AT_NCELL_MONITOR_QRY_CNF_STRU      *pstMtaAtQryCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usLength;

    /* ?????? */
    pstRcvMsg           = (AT_MTA_MSG_STRU *)pstMsg;
    pstMtaAtQryCnf      = (MTA_AT_NCELL_MONITOR_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;
    usLength            = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryNCellMonitorCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryNCellMonitorCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_NCELL_MONITOR_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaQryNCellMonitorCnf : Current Option is not AT_CMD_NCELL_MONITOR_READ.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^NCELLMONITOR???????????? */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstMtaAtQryCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        /* ?????????????????????????? */
        usLength        += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                  "%s: %d,%d",
                                                  g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                  pstMtaAtQryCnf->ucSwitch,
                                                  pstMtaAtQryCnf->ucNcellState);

    }

    gstAtSendData.usBufLen = usLength;

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaNCellMonitorInd(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg      = VOS_NULL_PTR;
    MTA_AT_NCELL_MONITOR_IND_STRU          *pstMtaAtInd    = VOS_NULL_PTR;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usLength;

    /* ?????? */
    pstRcvMsg           = (AT_MTA_MSG_STRU *)pstMsg;
    pstMtaAtInd         = (MTA_AT_NCELL_MONITOR_IND_STRU *)pstRcvMsg->aucContent;
    ucIndex             = 0;
    usLength            = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaNCellMonitorInd : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s^NCELLMONITOR: %d%s",
                                       gaucAtCrLf,
                                       pstMtaAtInd->ucNcellState,
                                       gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}



VOS_UINT32 AT_RcvMmaSimInsertRsp(VOS_VOID *pMsg)
{
    /* Modified by k902809 for Iteration 11, 2015-3-24, begin */
    TAF_MMA_SIM_INSERT_CNF_STRU        *pstSimInsertRsp = VOS_NULL_PTR;
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-24, end */
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstSimInsertRsp = (TAF_MMA_SIM_INSERT_CNF_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstSimInsertRsp->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSimInsertRsp : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSimInsertRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_SIMINSERT_SET */
    if (AT_CMD_SIMINSERT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_OK == pstSimInsertRsp->ulResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaRefclkfreqSetCnf(VOS_VOID *pMsg)
{
    /* ???????????? */
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_RESULT_CNF_STRU             *pstRltCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????????????? */
    ucIndex     = 0;
    pstMtaMsg   = (AT_MTA_MSG_STRU *)pMsg;
    pstRltCnf   = (MTA_AT_RESULT_CNF_STRU *)pstMtaMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_REFCLKFREQ_SET */
    if ( AT_CMD_REFCLKFREQ_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqSetCnf: WARNING:Not AT_CMD_REFCLKFREQ_SET!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( MTA_AT_RESULT_NO_ERROR == pstRltCnf->enResult )
    {
        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}



VOS_UINT32 AT_RcvMtaRficSsiRdQryCnf(VOS_VOID *pMsg)
{
    /* ???????????? */
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_RFICSSIRD_CNF_STRU          *pstRficSsiRdCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????????????? */
    ucIndex                 = 0;
    pstMtaMsg               = ( AT_MTA_MSG_STRU * )pMsg;
    pstRficSsiRdCnf         = ( MTA_AT_RFICSSIRD_CNF_STRU * )pstMtaMsg->aucContent;

    ucIndex                 = g_stAtDevCmdCtrl.ucIndex;

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaRficSsiRdQryCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_RFICSSIRD_SET */
    if ( AT_CMD_RFICSSIRD_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaRficSsiRdQryCnf: WARNING:Not AT_CMD_REFCLKFREQ_READ!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ?????????????? */
    gstAtSendData.usBufLen  = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                                     "%s: %d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     pstRficSsiRdCnf->ulRegValue );
    ulResult                = AT_OK;

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}



VOS_UINT32 AT_RcvMtaRefclkfreqQryCnf(VOS_VOID *pMsg)
{
    /* ???????????? */
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_REFCLKFREQ_QRY_CNF_STRU     *pstRefclkfreqCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????????????? */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU *)pMsg;
    pstRefclkfreqCnf    = (MTA_AT_REFCLKFREQ_QRY_CNF_STRU *)pstMtaMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqQryCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_REFCLKFREQ_READ */
    if ( AT_CMD_REFCLKFREQ_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqQryCnf: WARNING:Not AT_CMD_REFCLKFREQ_READ!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( MTA_AT_RESULT_NO_ERROR == pstRefclkfreqCnf->enResult )
    {
        /* ????GPS??????????????????????????????0 */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: 0,%d,%d,%d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstRefclkfreqCnf->ulFreq,
                                                        pstRefclkfreqCnf->ulPrecision,
                                                        pstRefclkfreqCnf->enStatus);
        ulResult    = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulResult    = AT_ERROR;
    }

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaRefclkfreqInd(VOS_VOID *pMsg)
{
    /* ???????????? */
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_REFCLKFREQ_IND_STRU         *pstRefclkfreqInd;

    /* ?????????????? */
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstRefclkfreqInd    = (MTA_AT_REFCLKFREQ_IND_STRU*)pstMtaMsg->aucContent;

    /* ????ClientId????ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ????GPS??????????????????????????????0 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s%s: 0,%d,%d,%d%s",
                                                    gaucAtCrLf,
                                                    gastAtStringTab[AT_STRING_REFCLKFREQ].pucText,
                                                    pstRefclkfreqInd->ulFreq,
                                                    pstRefclkfreqInd->ulPrecision,
                                                    pstRefclkfreqInd->enStatus,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaHandleDectSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg           = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_SET_CNF_STRU     *pstSetCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf           = (MTA_AT_HANDLEDECT_SET_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_HANDLEDECT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectSetCnf : Current Option is not AT_CMD_HANDLEDECT_SET.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;
    if (MTA_AT_RESULT_NO_ERROR != pstSetCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaHandleDectQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg           = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_QRY_CNF_STRU     *pstQryCnf         = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstQryCnf           = (MTA_AT_HANDLEDECT_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_HANDLEDECT_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectQryCnf : Current Option is not AT_CMD_HANDLEDECT_QRY.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^HANDLEDECT????????????? */
    gstAtSendData.usBufLen = 0;
    if (MTA_AT_RESULT_NO_ERROR != pstQryCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        (VOS_UINT16)pstQryCnf->usHandle);

    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaPsTransferInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_PS_TRANSFER_IND_STRU        *pstPsTransferInd;

    /* ?????????????? */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstPsTransferInd    = (MTA_AT_PS_TRANSFER_IND_STRU*)pstMtaMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaPsTransferInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^PSTRANSFER: %d%s",
                                                    gaucAtCrLf,
                                                    pstPsTransferInd->ucCause,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaMipiInfoInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_RF_LCD_MIPICLK_IND_STRU     *pstMipiClkCnf;

    /* ?????????????? */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstMipiClkCnf       = (MTA_AT_RF_LCD_MIPICLK_IND_STRU*)pstMtaMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaMipiInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^MIPICLK: %d%s",
                                                    gaucAtCrLf,
                                                    pstMipiClkCnf->usMipiClk,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaMipiInfoCnf(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_RF_LCD_MIPICLK_CNF_STRU     *pstMipiClkCnf;

    /* ?????????????? */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstMipiClkCnf       = (MTA_AT_RF_LCD_MIPICLK_CNF_STRU*)pstMtaMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaMipiInfoCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMipiInfoCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_MIPI_CLK_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstMipiClkCnf->usResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstMipiClkCnf->usMipiClk);
    }

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_VOID AT_RcvSwitchCmdModeMsg(VOS_UINT8 ucIndex)
{
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;

    pstLineCtrl = AT_GetUartLineCtrlInfo();

    /* ????????(enPortIndex??????????):
     * (1) ONLINE-DATA???? - ????OK
     * (2) ????????        - ????
     */

    /* ???????????? */
    if (ucIndex >= AT_CLIENT_BUTT)
    {
        return;
    }

    /* ??????UART???????????????????? */
    if (VOS_TRUE != AT_CheckHsUartUser(ucIndex))
    {
        return;
    }

    /* ??????????PPP??IP????????????ONLINE-COMMAND???? */
    if ( (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode)
      && ( (AT_PPP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
        || (AT_IP_DATA_MODE == gastAtClientTab[ucIndex].DataMode) ) )
    {
        if (AT_UART_DSR_MODE_CONNECT_ON == pstLineCtrl->enDsrMode)
        {
            AT_CtrlDSR(ucIndex, AT_IO_LEVEL_LOW);
        }

        At_SetMode(ucIndex, AT_ONLINE_CMD_MODE, AT_NORMAL_MODE);
        At_FormatResultData(ucIndex, AT_OK);
    }

    return;
}


VOS_VOID AT_RcvWaterLowMsg(VOS_UINT8 ucIndex)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;

    pstUartCtx = AT_GetUartCtxAddr();

    /* ???????????? */
    if (ucIndex >= AT_CLIENT_BUTT)
    {
        return;
    }

    /* ??????UART???????????????? */
    if (VOS_TRUE != AT_CheckHsUartUser(ucIndex))
    {
        return;
    }

    /* TX?????????? */
    if (VOS_NULL_PTR != pstUartCtx->pWmLowFunc)
    {
        pstUartCtx->pWmLowFunc(ucIndex);
    }

    return;
}


VOS_UINT32 AT_RcvMtaPsProtectSetCnf(VOS_VOID *pMsg)
{
    /* ???????????? */
    AT_MTA_MSG_STRU                    *pRcvMsg;
    MTA_AT_RRC_PROTECT_PS_CNF_STRU     *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    /* ?????????????? */
    pRcvMsg = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent = (MTA_AT_RRC_PROTECT_PS_CNF_STRU*)pRcvMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaPsProtectSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaPsProtectSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_PSPROTECTMODE_SET */
    if ( AT_CMD_PSPROTECTMODE_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaCgpsClockSetCnf: WARNING:Not AT_CMD_CGPSCLOCK_SET!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( MTA_AT_RESULT_NO_ERROR == pstEvent->enResult )
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaPhyInitCnf(VOS_VOID *pMsg)
{
    /* ???????????? */
    AT_MTA_MSG_STRU                    *pRcvMsg;
    MTA_AT_PHY_INIT_CNF_STRU           *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????????????? */
    pRcvMsg = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent = (MTA_AT_PHY_INIT_CNF_STRU*)pRcvMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaPhyInitCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaPhyInitCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_PHYINIT_SET */
    if ( AT_CMD_PHYINIT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaPhyInitCnf: WARNING:Not AT_CMD_PHYINIT!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( MTA_AT_RESULT_NO_ERROR == pstEvent->enResult )
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;
    /* ????AT_FormATResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}




VOS_UINT32 AT_RcvMtaEcidSetCnf(VOS_VOID *pMsg)
{
    /* ???????????? */
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_ECID_SET_CNF_STRU           *pstEcidSetCnf;
    VOS_UINT32                          ulResult;

    /* ?????????????? */
    ucIndex         = 0;
    pstMtaMsg       = (AT_MTA_MSG_STRU*)pMsg;
    pstEcidSetCnf   = (MTA_AT_ECID_SET_CNF_STRU*)pstMtaMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaEcidSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaEcidSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_REFCLKFREQ_READ */
    if ( AT_CMD_ECID_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaEcidSetCnf: WARNING:Not AT_CMD_REFCLKFREQ_READ!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( MTA_AT_RESULT_NO_ERROR == pstEcidSetCnf->enResult )
    {
        /* ???????????????????????? */
        /* +ECID=<version>,<rat>,[<cell_description>] */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s=%s",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstEcidSetCnf->aucCellInfoStr);
        ulResult    = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s=%s",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        "0,NONE:,");

        ulResult    = AT_OK;
    }

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}



VOS_UINT32 AT_RcvMmaSysCfgSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_SYS_CFG_CNF_STRU           *pstCnfMsg;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstCnfMsg = (TAF_MMA_SYS_CFG_CNF_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCnfMsg->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSysCfgSetCnf : WARNING:AT INDEX NOT FOUND!");

        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSysCfgSetCnf : AT_BROADCAST_INDEX.");

        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstCnfMsg->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstCnfMsg->enErrorCause);
    }

    gstAtSendData.usBufLen = 0;

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaPhoneModeSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_PHONE_MODE_SET_CNF_STRU    *pstCnfMsg;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucSptLteFlag;
    VOS_UINT8                           ucSptUtralTDDFlag;

    pstCnfMsg           = (TAF_MMA_PHONE_MODE_SET_CNF_STRU *)pMsg;
    ucIndex             = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    enModemId           = MODEM_ID_0;
    ulResult            = AT_FAILURE;

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG1("AT_RcvMmaPhoneModeSetCnf:Get ModemID From ClientID fail,ClientID=%d", ucIndex);

        return VOS_ERR;
    }

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCnfMsg->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSysCfgSetCnf : WARNING:AT INDEX NOT FOUND!");

        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPhoneModeSetCnf : AT_BROADCAST_INDEX.");

        return VOS_ERR;
    }

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstCnfMsg->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstCnfMsg->enErrorCause);       /* ???????? */
    }




    /* Added by c64416 for ^PSTANDBY low power proc, 2013-9-13, Begin */
    /* V7R2 ^PSTANDBY???????????????????? */
    if(AT_CMD_PSTANDBY_SET == (AT_LTE_CMD_CURRENT_OPT_ENUM)gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);

        return VOS_OK;
    }
    /* Added by c64416 for ^PSTANDBY low power proc, 2013-9-13, End */

    /* ????GU??????????????????????TL???????????? */
    if (ulResult == AT_OK)
    {
        ucSptLteFlag        = AT_IsModemSupportRat(enModemId, TAF_MMA_RAT_LTE);
        ucSptUtralTDDFlag   = AT_IsModemSupportUtralTDDRat(enModemId);

        if ((VOS_TRUE       == ucSptLteFlag)
         || (VOS_TRUE       == ucSptUtralTDDFlag))
        {
            if ((AT_CMD_TMODE_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
             || (AT_CMD_SET_TMODE == gastAtClientTab[ucIndex].CmdCurrentOpt))
            {
                AT_ProcOperModeWhenLteOn(ucIndex);
                return VOS_OK;
            }
        }
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaDetachCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_DETACH_CNF_STRU            *pstDetachCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstDetachCnf = (TAF_MMA_DETACH_CNF_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDetachCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaDetachCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaDetachCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstDetachCnf->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        gastAtClientTab[ucIndex].ulCause = pstDetachCnf->enErrorCause;
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}



VOS_UINT32 AT_RcvMmaAttachCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_ATTACH_CNF_STRU            *pstAttachCnf;
    VOS_UINT8                           ucIndex;

    pstAttachCnf = (TAF_MMA_ATTACH_CNF_STRU *)pstMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstAttachCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAttachCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ????????CLIENT?????????? */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAttachCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ?????????????? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????????(OK/ERROR)???????????????? */
    gstAtSendData.usBufLen = 0;

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstAttachCnf->enRslt)
    {
        /* ????At_FormatResultData???????????? */
        At_FormatResultData(ucIndex, AT_OK);
    }
    else
    {
        gastAtClientTab[ucIndex].ulCause = pstAttachCnf->enErrorCause;

        /* ????At_FormatResultData???????????? */
        At_FormatResultData(ucIndex, AT_ERROR);
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaAttachStatusQryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_ATTACH_STATUS_QRY_CNF_STRU *pstAttachStatusQryCnf;
    VOS_UINT8                           ucIndex;

    pstAttachStatusQryCnf = (TAF_MMA_ATTACH_STATUS_QRY_CNF_STRU *)pstMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstAttachStatusQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAttachStatusQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ????????CLIENT?????????? */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAttachStatusQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ???????????????? */
    if (AT_CMD_MMA_GET_CURRENT_ATTACH_STATUS != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaAttachStatusQryCnf : CmdCurrentOpt Not Match.");
        return VOS_ERR;
    }

    /* ?????????????? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????? */
    if (TAF_MMA_APP_OPER_RESULT_SUCCESS != pstAttachStatusQryCnf->enRslt)
    {
        At_FormatResultData(ucIndex,AT_ERROR);
        return AT_ERROR;
    }

    /* ????Domain Type???????????? */
    if (TAF_MMA_SERVICE_DOMAIN_CS_PS == pstAttachStatusQryCnf->enDomainType)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR*)pgucAtSndCodeAddr,
                                                        "%s: %d,%d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        (VOS_UINT32)pstAttachStatusQryCnf->enPsStatus,
                                                        (VOS_UINT32)pstAttachStatusQryCnf->enCsStatus);

        At_FormatResultData(ucIndex,AT_OK);
    }
    else if (TAF_MMA_SERVICE_DOMAIN_PS == pstAttachStatusQryCnf->enDomainType)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR*)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        (VOS_UINT32)pstAttachStatusQryCnf->enPsStatus);

        At_FormatResultData(ucIndex,AT_OK);
    }
    else
    {
        At_FormatResultData(ucIndex,AT_ERROR);
        return AT_ERROR;
    }

    return VOS_OK;
}





VOS_UINT32 AT_RcvMmaCLocInfoQueryCnf(
    VOS_VOID                           *pstMsg
)
{
    /* Modified by k902809 for Iteration 11, 2015-3-25, begin */
    TAF_MMA_CDMA_LOCINFO_QRY_CNF_STRU  *pstCLocInfoQueryCnf = VOS_NULL_PTR;
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-25, end */
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;


    /* ?????? */
    /* Modified by k902809 for Iteration 11, 2015-3-25, begin */
    pstCLocInfoQueryCnf = (TAF_MMA_CDMA_LOCINFO_QRY_CNF_STRU*)pstMsg;
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-25, end */
    usLength            = 0;
    ulResult            = AT_OK;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCLocInfoQueryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCLocInfoQueryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCLocInfoQueryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_CLOCINFO_QRY */
    if (AT_CMD_CLOCINFO_QRY == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);

        if (VOS_OK == pstCLocInfoQueryCnf->ulRslt)
        {


            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                             (VOS_CHAR *)pgucAtSndCodeAddr,
                                             (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                             "%s: %d,%d,%d,%d,%d,%d,%d,%d,%d",
                                             g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                             pstCLocInfoQueryCnf->stClocinfoPara.ucRatMode,
                                             pstCLocInfoQueryCnf->stClocinfoPara.usPrevInUse,
                                             pstCLocInfoQueryCnf->stClocinfoPara.ulMcc,
                                             pstCLocInfoQueryCnf->stClocinfoPara.ulMnc,
                                             pstCLocInfoQueryCnf->stClocinfoPara.lSid,
                                             pstCLocInfoQueryCnf->stClocinfoPara.lNid,
                                             pstCLocInfoQueryCnf->stClocinfoPara.ulBaseId,
                                             pstCLocInfoQueryCnf->stClocinfoPara.lBaseLatitude,
                                             pstCLocInfoQueryCnf->stClocinfoPara.lBaseLongitude);

            gstAtSendData.usBufLen = usLength;
        }
        else
        {
            /* IsClocInfoValid = VOS_FALSE; */

            /* ??????????????^CLOCINFO: 0*/
            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                             (VOS_CHAR *)pgucAtSndCodeAddr,
                                             (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                             "%s: %d",
                                             g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                             VOS_FALSE);

            gstAtSendData.usBufLen = usLength;
        }
    }
    else
    {
        return VOS_ERR;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaCSidInd(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CSID_IND_STRU              *pstCSidInd;

    /* ?????????????? */
    ucIndex             = 0;
    pstCSidInd       = (TAF_MMA_CSID_IND_STRU*)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCSidInd->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaCSidInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^CSID: %d%s",
                                                    gaucAtCrLf,
                                                    pstCSidInd->lSid,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}



VOS_UINT32 AT_RcvMmaEmcCallBackNtf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_1X_EMC_CALL_BACK_NTF_STRU  *pstEmcCallBack;

    /* ?????????????? */
    ucIndex             = 0;
    pstEmcCallBack      = (TAF_MMA_1X_EMC_CALL_BACK_NTF_STRU*)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEmcCallBack->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaEmcCallBackNtf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^EMCCBM: %d%s",
                                                    gaucAtCrLf,
                                                    pstEmcCallBack->ulIsInCallBack,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaQuitCallBackCnf(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_QUIT_CALLBACK_SET_CNF_STRU *pstQccbCnf;
    VOS_UINT32                          ulResult;

    /* ?????????????? */
    ucIndex            = 0;
    pstQccbCnf = (TAF_MMA_QUIT_CALLBACK_SET_CNF_STRU*)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstQccbCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaQuitCallBackCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaQuitCallBackCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_QCCB_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaQuitCallBackCnf : Current Option is not AT_CMD_QCCB_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^QCCB???????????? */
    gstAtSendData.usBufLen = 0;

    if (TAF_ERR_NO_ERROR == pstQccbCnf->enErrorCode)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}

VOS_UINT32 AT_RcvMmaQryEmcCallBackCnf(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_MMA_1X_EMC_CALL_BACK_QRY_CNF_STRU                  *pstQryEmcCallBackCnf;
    VOS_UINT16                                              usLength;
    VOS_UINT32                                              ulResult;

    /* ?????????????? */
    ucIndex            = 0;
    usLength           = 0;
    pstQryEmcCallBackCnf = (TAF_MMA_1X_EMC_CALL_BACK_QRY_CNF_STRU*)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstQryEmcCallBackCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaQryEmcCallBackCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaQryEmcCallBackCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_EMCCBM_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaQuitCallBackCnf : Current Option is not AT_CMD_EMCCBM_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^QCCB???????????? */
    gstAtSendData.usBufLen = 0;

    if (TAF_ERR_NO_ERROR == pstQryEmcCallBackCnf->enErrorCode)
    {
        ulResult = AT_OK;
        usLength = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (TAF_CHAR *)pgucAtSndCodeAddr,
                                         (TAF_CHAR *)pgucAtSndCodeAddr,
                                          "%s: %d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          pstQryEmcCallBackCnf->ucIsInCallBackMode);
        gstAtSendData.usBufLen = usLength;
    }
    else
    {
        ulResult = AT_CME_UNKNOWN;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}

VOS_UINT32 AT_RcvMmaSetCSidListCnf(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CSIDLIST_SET_CNF_STRU      *pstSetCSidListCnf;
    VOS_UINT32                          ulResult;

    /* ?????????????? */
    ucIndex            = 0;
    pstSetCSidListCnf = (TAF_MMA_CSIDLIST_SET_CNF_STRU*)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstSetCSidListCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSetCSidListCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSetCSidListCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CSIDLIST_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaSetCSidListCnf : Current Option is not AT_CMD_CSIDLIST_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^CSIDLIST???????? */
    gstAtSendData.usBufLen = 0;

    if (TAF_ERR_NO_ERROR == pstSetCSidListCnf->enErrorCode)
    {
     ulResult = AT_OK;
    }
    else
    {
     ulResult = AT_ERROR;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaQryCurrSidNidCnf(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_MMA_CURR_SID_NID_QRY_CNF_STRU                      *pstQryCurrSidNidCnf = VOS_NULL_PTR;
    VOS_UINT16                                              usLength;
    VOS_UINT32                                              ulResult;

    /* ?????????????? */
    ucIndex            = 0;
    usLength           = 0;
    pstQryCurrSidNidCnf = (TAF_MMA_CURR_SID_NID_QRY_CNF_STRU*)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstQryCurrSidNidCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaQryCurrSidNidCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaQryCurrSidNidCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CSNID_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaQryCurrSidNidCnf : Current Option is not AT_CMD_EMCCBM_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^CSNID???????????? */
    gstAtSendData.usBufLen = 0;

    if (TAF_ERR_NO_ERROR == pstQryCurrSidNidCnf->enErrorCode)
    {
        ulResult = AT_OK;
        usLength = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (TAF_CHAR *)pgucAtSndCodeAddr,
                                         (TAF_CHAR *)pgucAtSndCodeAddr,
                                          "%s: %d,%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          pstQryCurrSidNidCnf->lSid,
                                          pstQryCurrSidNidCnf->lNid);

        gstAtSendData.usBufLen = usLength;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaRoamingModeSwitchInd(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_ROAMING_MODE_SWITCH_IND_STRU                   *pstRoamingModeSwitchInd = VOS_NULL_PTR;
    VOS_UINT8                                               ucIndex;

    /* ?????????????? */
    ucIndex                 = 0;
    pstRoamingModeSwitchInd = (TAF_MMA_ROAMING_MODE_SWITCH_IND_STRU *)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRoamingModeSwitchInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaRoamingModeSwitchInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^ROAMINGMODESWITCH%s",
                                                    gaucAtCrLf,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

VOS_UINT32 AT_RcvMmaCombinedModeSwitchInd(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_COMBINED_MODE_SWITCH_IND_STRU                  *pstCombinedModeSwitchInd = VOS_NULL_PTR;
    VOS_UINT8                                               ucIndex;

    /* ?????????????? */
    ucIndex = 0;
    pstCombinedModeSwitchInd = (TAF_MMA_COMBINED_MODE_SWITCH_IND_STRU *)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCombinedModeSwitchInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaRoamingModeSwitchInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^RATCOMBINEDMODE: %d%s",
                                                    gaucAtCrLf,
                                                    pstCombinedModeSwitchInd->enCombinedMode,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaRatCombinedModeQryCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_MMA_RAT_COMBINED_MODE_QRY_CNF_STRU                 *pstRcvMsg;

    /* ?????????????? */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_MMA_RAT_COMBINED_MODE_QRY_CNF_STRU*)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaRatCombinedModeQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaRatCombinedModeQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_RATCOMBINEDMODE_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaRatCombinedModeQryCnf : Current Option is not AT_CMD_PRLID_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s^RATCOMBINEDMODE: %d%s",
                                       gaucAtCrLf,
                                       pstRcvMsg->enCombinedMode,
                                       gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaIccAppTypeSwitchInd(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_ICC_APP_TYPE_SWITCH_IND_STRU                   *pstIccAppTypeSwitchInd;
    VOS_UINT8                                               ucIndex;

    /* ?????????????? */
    ucIndex = 0;
    pstIccAppTypeSwitchInd = (TAF_MMA_ICC_APP_TYPE_SWITCH_IND_STRU *)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstIccAppTypeSwitchInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaIccAppTypeSwitchInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^ICCAPPTYPESWITCH: %d%s",
                                                    gaucAtCrLf,
                                                    pstIccAppTypeSwitchInd->enSwitchState,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaCtRoamInfoCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_MMA_CTCC_ROAMING_NW_INFO_QRY_CNF_STRU              *pstQryMultiModeSidMcc = VOS_NULL_PTR;
    VOS_UINT16                                              usLength;
    VOS_UINT32                                              ulResult;

    /* ?????????????? */
    ucIndex            = 0;
    usLength           = 0;
    pstQryMultiModeSidMcc = (TAF_MMA_CTCC_ROAMING_NW_INFO_QRY_CNF_STRU *)pstMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstQryMultiModeSidMcc->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCtRoamInfoCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCtRoamInfoCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CTROAMINFO_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaCtRoamInfoCnf : Current Option is not AT_CMD_MULTIMODESIDMCC_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^CSNID???????????? */
    gstAtSendData.usBufLen = 0;

    ulResult = AT_OK;
    usLength = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (TAF_CHAR *)pgucAtSndCodeAddr,
                                     (TAF_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d,%x%x%x,%x%x%x,%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      pstQryMultiModeSidMcc->lSid,
                                      (pstQryMultiModeSidMcc->ul3Gpp2Mcc & 0x0f00)>>8,
                                      (pstQryMultiModeSidMcc->ul3Gpp2Mcc & 0xf0)>>4,
                                      (pstQryMultiModeSidMcc->ul3Gpp2Mcc & 0x0f),
                                      (pstQryMultiModeSidMcc->ul3GppMcc & 0x0f00)>>8,
                                      (pstQryMultiModeSidMcc->ul3GppMcc & 0xf0)>>4,
                                      (pstQryMultiModeSidMcc->ul3GppMcc & 0x0f),
                                      pstQryMultiModeSidMcc->ulModeType);

    gstAtSendData.usBufLen = usLength;

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaCtRoamingInfoChgInd(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_MMA_CTCC_ROAMING_NW_INFO_REPORT_IND_STRU           *pstMultiModeSidMccChgInd = VOS_NULL_PTR;
    VOS_UINT16                                              usLength;

    /* ?????????????? */
    ucIndex            = 0;
    usLength           = 0;
    pstMultiModeSidMccChgInd = (TAF_MMA_CTCC_ROAMING_NW_INFO_REPORT_IND_STRU *)pstMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMultiModeSidMccChgInd->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCtRoamingInfoChgInd : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ??????AT^CSNID???????????? */
    gstAtSendData.usBufLen = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     "%s^CTROAMINFO: %d,%x%x%x,%x%x%x,%d%s",
                                     gaucAtCrLf,
                                     pstMultiModeSidMccChgInd->lSid,
                                     (pstMultiModeSidMccChgInd->ul3Gpp2Mcc & 0x0f00)>>8,
                                     (pstMultiModeSidMccChgInd->ul3Gpp2Mcc & 0xf0)>>4,
                                     (pstMultiModeSidMccChgInd->ul3Gpp2Mcc & 0x0f),
                                     (pstMultiModeSidMccChgInd->ul3GppMcc & 0x0f00)>>8,
                                     (pstMultiModeSidMccChgInd->ul3GppMcc & 0xf0)>>4,
                                     (pstMultiModeSidMccChgInd->ul3GppMcc & 0x0f),
                                     pstMultiModeSidMccChgInd->ulModeType,
                                     gaucAtCrLf);

    gstAtSendData.usBufLen = usLength;

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaCtOosCountCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_CTCC_OOS_COUNT_SET_CNF_STRU                    *pstOosCountCnf = VOS_NULL_PTR;
    VOS_UINT8                                               ucIndex;
    VOS_UINT32                                              ulResult;

    /* ?????????????? */
    ucIndex            = 0;
    pstOosCountCnf = (TAF_MMA_CTCC_OOS_COUNT_SET_CNF_STRU*)pstMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstOosCountCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCtOosCountCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCtOosCountCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CTOOSCOUNT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaCtOosCountCnf : Current Option is not AT_CMD_CTOOSCOUNT_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^QCCB???????????? */
    gstAtSendData.usBufLen = 0;

    if (TAF_ERR_NO_ERROR == pstOosCountCnf->enErrorCode)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}




VOS_UINT32 AT_RcvXcallEncryptCallCnf(
    VOS_VOID                                               *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_ENCRYPT_VOICE_CNF_STRU                    *pstRcvMsg;
    VOS_UINT32                                              ulResult;
    AT_ENCRYPT_VOICE_ERROR_ENUM_UINT32                      enEcnErr;

    /* ?????????????? */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_ENCRYPT_VOICE_CNF_STRU*)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallEncryptCallCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXcallEncryptCallCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_ECCALL_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvXcallEncryptCallCnf : Current Option is not AT_CMD_ECCALL_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;
    /* ??????AT^ECCALL  SET???????? */
    if (TAF_CALL_APP_ENCRYPT_VOICE_SUCC == pstRcvMsg->enEccVoiceStatus)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
        enEcnErr = AT_MapEncVoiceErr(pstRcvMsg->enEccVoiceStatus);

        /* ?????????????????????????? */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^ECCALL: %d%s",
                                                        gaucAtCrLf,
                                                        enEcnErr,
                                                        gaucAtCrLf);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvXcallEncryptCallInd(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_ENCRYPT_VOICE_IND_STRU                    *pstRcvMsg;
    VOS_UINT8                                               aucAsciiNum[MN_CALL_MAX_CALLED_BCD_NUM_LEN + 1];
    AT_ENCRYPT_VOICE_ERROR_ENUM_UINT32                      enEcnErr;

    /* ?????????????? */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_ENCRYPT_VOICE_IND_STRU*)pstMsg;
    TAF_MEM_SET_S(aucAsciiNum, sizeof(aucAsciiNum), 0x00, MN_CALL_MAX_CALLED_BCD_NUM_LEN + 1);

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallEncryptCallInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    enEcnErr = AT_MapEncVoiceErr(pstRcvMsg->enEccVoiceStatus);

    /* AT^ECCALL ind???????? */
    if (AT_ENCRYPT_VOICE_MT_CALL_NOTIFICATION == enEcnErr)
    {
        /* ???????????????? */
        AT_BcdNumberToAscii(pstRcvMsg->stCallingNumber.aucBcdNum,
                            pstRcvMsg->stCallingNumber.ucNumLen,
                            (VOS_CHAR *)aucAsciiNum);
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^ECCALL: %d,\"%s\"%s",
                                                        gaucAtCrLf,
                                                        enEcnErr,
                                                        aucAsciiNum,
                                                        gaucAtCrLf);
    }
    else if (AT_ENCRYPT_VOICE_ERROR_ENUM_BUTT == enEcnErr)
    {
        /* ???????? */
        return VOS_ERR;
    }
    else
    {
        /* ?????????????????????????? */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^ECCALL: %d%s",
                                                        gaucAtCrLf,
                                                        enEcnErr,
                                                        gaucAtCrLf);


    }

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;

}

VOS_UINT32 AT_RcvXcallEccRemoteCtrlInd(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_EC_REMOTE_CTRL_IND_STRU                   *pstRcvMsg;

    /* ?????????????? */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_EC_REMOTE_CTRL_IND_STRU*)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallEcRemoteCtrlInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^ECCTRL: %d%s",
                                                    gaucAtCrLf,
                                                    pstRcvMsg->enRemoteCtrlType,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;

}


VOS_UINT32 AT_RcvXcallRemoteCtrlAnsCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF_STRU               *pstRcvMsg;
    VOS_UINT32                                              ulResult;

    /* ?????????????? */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF_STRU*)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallRemoteCtrlAnsCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXcallRemoteCtrlAnsCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_ECCTRL_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvXcallRemoteCtrlAnsCnf : Current Option is not AT_CMD_ECCTRL_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;
    /* ??????AT^ECCTRL  SET???????? */
    if (TAF_CALL_SEND_RESULT_SUCC == pstRcvMsg->enResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}

VOS_UINT32 AT_RcvXcallEccCapSetCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF_STRU                  *pstRcvMsg;
    VOS_UINT32                                              ulResult;

    /* ?????????????? */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF_STRU*)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallEccCapSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXcallEccCapSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_ECCAP_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvXcallEccCapSetCnf : Current Option is not AT_CMD_ECCAP_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* ??????AT^ECCAP  SET???????? */
    if (TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_SUCC == pstRcvMsg->enResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}

VOS_UINT32 AT_RcvXcallEccCapQryCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF_STRU                  *pstRcvMsg;
    VOS_UINT32                                              ulResult;

    /* ?????????????? */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF_STRU*)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallEccCapQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXcallEccCapQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_ECCAP_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvXcallEccCapQryCnf : Current Option is not AT_CMD_ECCAP_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* ??????AT^ECCAP  SET???????? */
    if (TAF_CALL_APP_ECC_SRV_CAP_DISABLE == pstRcvMsg->enEccSrvCap)
    {
        ulResult               = AT_OK;
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           "%s^ECCAP: %d,%d%s",
                                           gaucAtCrLf,
                                           pstRcvMsg->enEccSrvCap,
                                           TAF_CALL_APP_ECC_SRV_STATUS_CLOSE,
                                           gaucAtCrLf);
    }
    else if (TAF_CALL_APP_ECC_SRV_CAP_ENABLE == pstRcvMsg->enEccSrvCap)
    {
        ulResult               = AT_OK;
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           "%s^ECCAP: %d,%d%s",
                                           gaucAtCrLf,
                                           pstRcvMsg->enEccSrvCap,
                                           pstRcvMsg->enEccSrvStatus,
                                           gaucAtCrLf);

    }
    else
    {
        ulResult = AT_ERROR;
    }

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}

VOS_UINT32 AT_RcvMmaClocinfoInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CLOCINFO_IND_STRU          *pstClocinfoInd;

    /* ?????????????? */
    ucIndex             = 0;
    pstClocinfoInd      = (TAF_MMA_CLOCINFO_IND_STRU*)pMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstClocinfoInd->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaClocinfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^CLOCINFO: %d,%d,%d,%d,%d,%d,%d,%d,%d%s",
                                                    gaucAtCrLf,
                                                    pstClocinfoInd->stClocinfoPara.ucRatMode,
                                                    pstClocinfoInd->stClocinfoPara.usPrevInUse,
                                                    pstClocinfoInd->stClocinfoPara.ulMcc,
                                                    pstClocinfoInd->stClocinfoPara.ulMnc,
                                                    pstClocinfoInd->stClocinfoPara.lSid,
                                                    pstClocinfoInd->stClocinfoPara.lNid,
                                                    pstClocinfoInd->stClocinfoPara.ulBaseId,
                                                    pstClocinfoInd->stClocinfoPara.lBaseLatitude,
                                                    pstClocinfoInd->stClocinfoPara.lBaseLongitude,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


VOS_UINT32 AT_RcvXcallPrivacyModeSetCnf(
    VOS_VOID                                               *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_PRIVACY_MODE_SET_CNF_STRU                 *pstRcvMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulResult;

    /* ?????????????? */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_PRIVACY_MODE_SET_CNF_STRU*)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallPrivacyModeSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXcallPrivacyModeSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CPMP_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvXcallPrivacyModeSetCnf : Current Option is not AT_CMD_CPMP_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* ??????AT^CPMP  SET???????? */
    if (TAF_CALL_APP_RESULT_TYPE_SUCCESS == pstRcvMsg->enResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvXcallPrivacyModeQryCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_PRIVACY_MODE_QRY_CNF_STRU                 *pstRcvMsg = VOS_NULL_PTR;

    /* ?????????????? */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_PRIVACY_MODE_QRY_CNF_STRU*)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallPrivacyModeQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXcallPrivacyModeQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CPMP_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvXcallPrivacyModeQryCnf : Current Option is not AT_CMD_ECCAP_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* X???????????????????????? */
    if (0 != pstRcvMsg->ucCallNums)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           "%s^CPMP: %d,%d,%d%s",
                                           gaucAtCrLf,
                                           pstRcvMsg->enPrivacyMode,
                                           pstRcvMsg->astCallVoicePrivacyInfo[0].ucCallId,
                                           pstRcvMsg->astCallVoicePrivacyInfo[0].enPrivacyMode,
                                           gaucAtCrLf);
    }
    else
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           "%s^CPMP: %d%s",
                                           gaucAtCrLf,
                                           pstRcvMsg->enPrivacyMode,
                                           gaucAtCrLf);
    }

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


VOS_UINT32 AT_RcvXcallPrivacyModeInd(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_PRIVACY_MODE_IND_STRU                     *pstRcvMsg = VOS_NULL_PTR;

    /* ?????????????? */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_PRIVACY_MODE_IND_STRU*)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallPrivacyModeInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^CPMP: %d,%d,%d%s",
                                                    gaucAtCrLf,
                                                    pstRcvMsg->enPrivacyMode,
                                                    pstRcvMsg->stCallVoicePrivacyInfo.ucCallId,
                                                    pstRcvMsg->stCallVoicePrivacyInfo.enPrivacyMode,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaCtRoamRptCfgSetCnf(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_MMA_CTCC_ROAMING_NW_INFO_RTP_CFG_SET_CNF_STRU      *pstCtRoamRptSetCnf;
    VOS_UINT32                                              ulResult;

    /* ?????????????? */
    ucIndex    = 0;
    pstCtRoamRptSetCnf = (TAF_MMA_CTCC_ROAMING_NW_INFO_RTP_CFG_SET_CNF_STRU*)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCtRoamRptSetCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCtRoamRptCfgSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCtRoamRptCfgSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CTROAMINFO_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaCtRoamRptCfgSetCnf : Current Option is not AT_CMD_CTROAMINFO_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^CTROAM???????????? */
    gstAtSendData.usBufLen = 0;

    if (TAF_ERR_NO_ERROR == pstCtRoamRptSetCnf->enErrorCode)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaPrlIdQryCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_PRLID_QRY_CNF_STRU         *pstRcvMsg = VOS_NULL_PTR;

    /* ?????????????? */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_MMA_PRLID_QRY_CNF_STRU*)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaPrlIdQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPrlIdQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_PRLID_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPrlIdQryCnf : Current Option is not AT_CMD_PRLID_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s^PRLID: %d,%d,%d,%d,%d%s",
                                       gaucAtCrLf,
                                       pstRcvMsg->lPrlSrcType,
                                       pstRcvMsg->lPrlId,
                                       pstRcvMsg->lMlplMsplSrcType,
                                       pstRcvMsg->lMlplId,
                                       pstRcvMsg->lMsplId,
                                       gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaCTimeInd(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CTIME_IND_STRU             *pstCTimeInd;
    VOS_INT8                            cTimeZone;

    /* ?????????????? */
    ucIndex           = 0;
    pstCTimeInd       = (TAF_MMA_CTIME_IND_STRU*)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCTimeInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaCTimeInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ??????????cTimeZone????30??????????????AP??????15?????????? */
    if(pstCTimeInd->stTimezoneCTime.cTimeZone < 0)
    {
        cTimeZone = (VOS_INT8)(-1 * 2 * pstCTimeInd->stTimezoneCTime.cTimeZone);
    }
    else
    {
        cTimeZone = (VOS_INT8)(2 * pstCTimeInd->stTimezoneCTime.cTimeZone);
    }

    gstAtSendData.usBufLen = 0;
    /*????????????: ^CTIME: "yy/mm/dd,hh:mm:ss(+/-)tz,dst" */
    if (pstCTimeInd->stTimezoneCTime.cTimeZone >= 0)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^CTIME: \"%02d/%02d/%02d,%02d:%02d:%02d+%d,%02d\"%s",
                                                        gaucAtCrLf,
                                                        pstCTimeInd->stTimezoneCTime.ucYear%100,
                                                        pstCTimeInd->stTimezoneCTime.ucMonth,
                                                        pstCTimeInd->stTimezoneCTime.ucDay,
                                                        pstCTimeInd->stTimezoneCTime.ucHour,
                                                        pstCTimeInd->stTimezoneCTime.ucMinute,
                                                        pstCTimeInd->stTimezoneCTime.ucSecond,
                                                        cTimeZone,
                                                        pstCTimeInd->stTimezoneCTime.ucDayltSavings,
                                                        gaucAtCrLf);
    }
    else
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^CTIME: \"%02d/%02d/%02d,%02d:%02d:%02d-%d,%02d\"%s",
                                                        gaucAtCrLf,
                                                        pstCTimeInd->stTimezoneCTime.ucYear%100,
                                                        pstCTimeInd->stTimezoneCTime.ucMonth,
                                                        pstCTimeInd->stTimezoneCTime.ucDay,
                                                        pstCTimeInd->stTimezoneCTime.ucHour,
                                                        pstCTimeInd->stTimezoneCTime.ucMinute,
                                                        pstCTimeInd->stTimezoneCTime.ucSecond,
                                                        cTimeZone,
                                                        pstCTimeInd->stTimezoneCTime.ucDayltSavings,
                                                        gaucAtCrLf);
    }

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}



VOS_UINT32 AT_RcvMmaCFreqLockSetCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CFREQ_LOCK_SET_CNF_STRU    *pstCFreqLockSetCnf;
    VOS_UINT32                          ulResult;

    /* ?????????????? */
    ucIndex             = 0;
    pstCFreqLockSetCnf  = (TAF_MMA_CFREQ_LOCK_SET_CNF_STRU*)pstMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCFreqLockSetCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCFreqLockSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCFreqLockSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CFREQLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaCFreqLockSetCnf : Current Option is not AT_CMD_CFREQLOCK_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^CFREQLOCK???????? */
    gstAtSendData.usBufLen = 0;

    if (VOS_TRUE != pstCFreqLockSetCnf->ulRslt)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaCFreqLockQueryCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CFREQ_LOCK_QUERY_CNF_STRU  *pstCFreqLockQryCnf;
    VOS_UINT16                          usLength;


    /* ?????????????? */
    ucIndex            = 0;
    usLength           = 0;
    pstCFreqLockQryCnf = (TAF_MMA_CFREQ_LOCK_QUERY_CNF_STRU*)pstMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCFreqLockQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCFreqLockQueryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCFreqLockQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CFREQLOCK_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaCFreqLockQueryCnf : Current Option is not AT_CMD_CFREQLOCK_QUERY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^CFREQLOCK???????????? */
    gstAtSendData.usBufLen = 0;
    if (TAF_MMA_CFREQ_LOCK_MODE_OFF == pstCFreqLockQryCnf->stCFreqLockPara.enFreqLockMode)
    {
       usLength = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.enFreqLockMode);
    }
    else
    {
       usLength = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d,%d,%d,%d,%d,%d,%d,%d,%d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.enFreqLockMode,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.usSid,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.usNid,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.usCdmaBandClass,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.usCdmaFreq,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.usCdmaPn,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.usEvdoBandClass,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.usEvdoFreq,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.usEvdoPn);
    }

    gstAtSendData.usBufLen = usLength;
    /* ???????? */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}



VOS_UINT32 AT_RcvMmaCdmaCsqSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_CDMACSQ_SET_CNF_STRU            *pstCdmaCsqCnf;
    VOS_UINT8                                ucIndex;
    VOS_UINT32                               ulResult;

    pstCdmaCsqCnf = (TAF_MMA_CDMACSQ_SET_CNF_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCdmaCsqCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCdmaCsqSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCdmaCsqSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstCdmaCsqCnf->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaCdmaCsqQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_CDMACSQ_QUERY_CNF_STRU     *pstCdmaCsqQueryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pstCdmaCsqQueryCnf  = (TAF_MMA_CDMACSQ_QUERY_CNF_STRU*)pMsg;
    usLength            = 0;
    ulResult            = AT_OK;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCdmaCsqQueryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCdmaCsqQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCdmaCsqQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_CDMACSQ_QRY */
    if (AT_CMD_CDMACSQ_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d,%d,%d,%d,%d,%d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     pstCdmaCsqQueryCnf->enMode,
                                     pstCdmaCsqQueryCnf->ucTimeInterval,
                                     pstCdmaCsqQueryCnf->ucRssiRptThreshold,
                                     pstCdmaCsqQueryCnf->ucEcIoRptThreshold,
                                     pstCdmaCsqQueryCnf->stSigQualityInfo.sCdmaRssi,
                                     pstCdmaCsqQueryCnf->stSigQualityInfo.sCdmaEcIo);


    gstAtSendData.usBufLen = usLength;

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaCdmaCsqInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CDMACSQ_IND_STRU           *pstCdmaCsqInd;

    /* ?????????????? */
    ucIndex             = 0;
    pstCdmaCsqInd       = (TAF_MMA_CDMACSQ_IND_STRU*)pMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCdmaCsqInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaCdmaCsqInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^CDMACSQ: %d,%d%s",
                                                    gaucAtCrLf,
                                                    pstCdmaCsqInd->sCdmaRssi,
                                                    pstCdmaCsqInd->sCdmaEcIo,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;

}



VOS_UINT32 AT_RcvMmaCLModInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CLMODE_IND_STRU            *pstCLModeInd;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                          *pucIsCLMode;

    /* ?????????????? */
    ucIndex             = 0;
    pstCLModeInd        = (TAF_MMA_CLMODE_IND_STRU*)pMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCLModeInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaCLModInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_RcvMmaCLModInd: Get modem id fail.");
        return VOS_ERR;
    }

    pucIsCLMode = AT_GetModemCLModeCtxAddrFromModemId(enModemId);

    *pucIsCLMode = pstCLModeInd->ucIsCLMode;
    return VOS_OK;

}

VOS_UINT32 AT_RcvMtaXpassInfoInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg       = VOS_NULL_PTR;
    MTA_AT_XPASS_INFO_IND_STRU         *pstXpassInfoInd = VOS_NULL_PTR;

    /* ?????????????? */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstXpassInfoInd     = (MTA_AT_XPASS_INFO_IND_STRU*)pstMtaMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaXpassInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^XPASSINFO: %d,%d%s",
                                                    gaucAtCrLf,
                                                    pstXpassInfoInd->enGphyXpassMode,
                                                    pstXpassInfoInd->enWphyXpassMode,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaCFPlmnSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_CFPLMN_SET_CNF_STRU        *pstCFPLmnCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstCFPLmnCnf = (TAF_MMA_CFPLMN_SET_CNF_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCFPLmnCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCFPlmnSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCFPlmnSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CFPLMN_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaCFPlmnSetCnf : Current Option is not AT_CMD_CFPLMN_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstCFPLmnCnf->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        /* ????????????????????????????????????????????GU????????????????????????????????????????AT_CME_UNKNOWN  */
        ulResult = AT_CME_UNKNOWN;
    }

    gstAtSendData.usBufLen = 0;

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

VOS_UINT32 AT_RcvMmaCFPlmnQueryCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CFPLMN_QUERY_CNF_STRU      *pstCFPlmnQrynf = VOS_NULL_PTR;
    TAF_USER_PLMN_LIST_STRU            *pstCFPlmnList  = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLoop;

    /* ?????????????? */
    ucIndex = 0;
    pstCFPlmnQrynf = (TAF_MMA_CFPLMN_QUERY_CNF_STRU *)pstMsg;
    pstCFPlmnList = (TAF_USER_PLMN_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(TAF_USER_PLMN_LIST_STRU));
    if (VOS_NULL_PTR == pstCFPlmnList)
    {
        AT_WARN_LOG("AT_RcvMmaCFPlmnQueryCnf : alloc fail");
        return VOS_ERR;
    }

    TAF_MEM_SET_S(pstCFPlmnList, sizeof(TAF_USER_PLMN_LIST_STRU), 0x00, sizeof(TAF_USER_PLMN_LIST_STRU));

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCFPlmnQrynf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCFPlmnQueryCnf : WARNING:AT INDEX NOT FOUND!");
        PS_MEM_FREE(WUEPS_PID_AT, pstCFPlmnList);
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCFPlmnQueryCnf : AT_BROADCAST_INDEX.");
        PS_MEM_FREE(WUEPS_PID_AT, pstCFPlmnList);
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CFPLMN_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaCFPlmnQueryCnf : Current Option is not AT_CMD_CFREQLOCK_QUERY.");
        PS_MEM_FREE(WUEPS_PID_AT, pstCFPlmnList);
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS != pstCFPlmnQrynf->enRslt)
    {
        gstAtSendData.usBufLen = 0;
        /* ????????????????????????????????????????????GU????????????????????????????????????????AT_CME_UNKNOWN  */
        ulResult = AT_CME_UNKNOWN;
        At_FormatResultData(ucIndex, ulResult);
    }
    else
    {
        if (pstCFPlmnQrynf->usPlmnNum > TAF_USER_MAX_PLMN_NUM)
        {
            pstCFPlmnQrynf->usPlmnNum = TAF_USER_MAX_PLMN_NUM;
        }

        pstCFPlmnList->usPlmnNum = pstCFPlmnQrynf->usPlmnNum;

        for (ulLoop = 0; (ulLoop < pstCFPlmnQrynf->usPlmnNum); ulLoop++ )
        {
            pstCFPlmnList->Plmn[ulLoop].Mcc = pstCFPlmnQrynf->astPlmn[ulLoop].Mcc;
            pstCFPlmnList->Plmn[ulLoop].Mnc = pstCFPlmnQrynf->astPlmn[ulLoop].Mnc;
        }

        At_QryParaRspCfplmnProc(ucIndex, pstCFPlmnQrynf->stCtrl.ucOpId, (TAF_VOID *)pstCFPlmnList);
    }

    PS_MEM_FREE(WUEPS_PID_AT, pstCFPlmnList);
    return VOS_OK;
}


VOS_VOID AT_ReportQryPrefPlmnCmdPara(
    TAF_MMA_PREF_PLMN_QUERY_CNF_STRU   *pstCpolQryCnf,
    AT_MODEM_NET_CTX_STRU              *pstNetCtx,
    VOS_UINT16                         *pusLength,
    VOS_UINT32                          ucIndex,
    VOS_UINT32                          ulLoop
)
{
    TAF_PLMN_NAME_LIST_STRU            *pstAvailPlmnInfo;
    AT_COPS_FORMAT_TYPE                 CurrFormat;

    pstAvailPlmnInfo = (TAF_PLMN_NAME_LIST_STRU*)&pstCpolQryCnf->stPlmnName;

    /* +CPOL:   */
    *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* <index> */
    *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                       "%d",
                                       ((ulLoop + pstCpolQryCnf->ulFromIndex) + 1));

    CurrFormat = pstNetCtx->ucCpolFormatType;

    if (('\0' == pstAvailPlmnInfo->astPlmnName[ulLoop].aucOperatorNameLong[0])
     && (AT_COPS_LONG_ALPH_TYPE == CurrFormat))
    {
        CurrFormat = AT_COPS_NUMERIC_TYPE;
    }

    if (('\0' == pstAvailPlmnInfo->astPlmnName[ulLoop].aucOperatorNameShort[0])
     && (AT_COPS_SHORT_ALPH_TYPE == CurrFormat))
    {
        CurrFormat = AT_COPS_NUMERIC_TYPE;
    }

    /* <format> */
    *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                       ",%d",
                                       CurrFormat);

    /* <oper1> */
    if (AT_COPS_LONG_ALPH_TYPE == CurrFormat)
    {
        *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                           ",\"%s\"",
                                           pstAvailPlmnInfo->astPlmnName[ulLoop].aucOperatorNameLong);
    }
    else if (AT_COPS_SHORT_ALPH_TYPE == CurrFormat)
    {
        *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                           ",\"%s\"",
                                           pstAvailPlmnInfo->astPlmnName[ulLoop].aucOperatorNameShort);
    }
    else
    {
        *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                           ",\"%X%X%X",
                                           (0x0f00 & pstAvailPlmnInfo->astPlmnName[ulLoop].PlmnId.Mcc) >> 8,
                                           (0x00f0 & pstAvailPlmnInfo->astPlmnName[ulLoop].PlmnId.Mcc) >> 4,
                                           (0x000f & pstAvailPlmnInfo->astPlmnName[ulLoop].PlmnId.Mcc));

        if (0x0F != ((0x0f00 & pstAvailPlmnInfo->astPlmnName[ulLoop].PlmnId.Mnc) >> 8))
        {
            *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                               "%X",
                                               (0x0f00 & pstAvailPlmnInfo->astPlmnName[ulLoop].PlmnId.Mnc) >> 8);

        }

        *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                           "%X%X\"",
                                           (0x00f0 & pstAvailPlmnInfo->astPlmnName[ulLoop].PlmnId.Mnc) >> 4,
                                           (0x000f & pstAvailPlmnInfo->astPlmnName[ulLoop].PlmnId.Mnc));
    }

    return;
}


VOS_VOID AT_ReportQryPrefPlmnCmd(
    TAF_MMA_PREF_PLMN_QUERY_CNF_STRU   *pstCpolQryCnf,
    VOS_UINT32                         *pulValidPlmnNum,
    AT_MODEM_NET_CTX_STRU              *pstNetCtx,
    VOS_UINT16                         *pusLength,
    VOS_UINT32                          ucIndex
)
{
    VOS_UINT32                          i;
    TAF_PLMN_NAME_LIST_STRU            *pstAvailPlmnInfo;
    TAF_MMC_USIM_RAT                    usPlmnRat;

    pstAvailPlmnInfo = (TAF_PLMN_NAME_LIST_STRU*)&pstCpolQryCnf->stPlmnName;

    for(i = 0; i < pstAvailPlmnInfo->ulPlmnNum; i++)
    {
        if (VOS_FALSE == AT_PH_IsPlmnValid(&(pstAvailPlmnInfo->astPlmnName[i].PlmnId)))
        {
            continue;
        }

        (*pulValidPlmnNum)++;

        if ((0 == pstCpolQryCnf->ulValidPlmnNum)
         && (1 == *pulValidPlmnNum))
        {
            /* ????V.250????5.7.2: ????V???????????????????????????????????????? */
            if (AT_V_ENTIRE_TYPE == gucAtVType)
            {
                *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                                   "%s",
                                                   gaucAtCrLf);
            }
        }
        else
        {
            *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                               "%s",
                                               gaucAtCrLf);
        }

        AT_ReportQryPrefPlmnCmdPara(pstCpolQryCnf, pstNetCtx, pusLength, ucIndex, i);

        if ((MN_PH_PREF_PLMN_UPLMN == pstNetCtx->enPrefPlmnType)
         && (VOS_TRUE == pstAvailPlmnInfo->bPlmnSelFlg))
        {
            continue;
        }


        /* <GSM_AcT1> */
        /* <GSM_Compact_AcT1> */
        /* <UTRAN_AcT1> */
        usPlmnRat = pstAvailPlmnInfo->ausPlmnRat[i];

        *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),",%d,%d,%d,%d",
                                           (usPlmnRat & TAF_MMC_USIM_GSM_RAT) >> 7,
                                           (usPlmnRat & TAF_MMC_USIM_GSM_COMPACT_RAT) >> 6,
                                           (usPlmnRat & TAF_MMC_USIM_UTRN_RAT) >> 15,
                                           (usPlmnRat & TAF_MMC_USIM_E_UTRN_RAT) >> 14);

    }

    return;

}

VOS_UINT32 AT_RcvMmaPrefPlmnSetCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_PREF_PLMN_SET_CNF_STRU     *pstPrefPlmnCnf;
    VOS_UINT32                          ulResult;

    /* ?????????????? */
    ucIndex            = 0;
    ulResult           = AT_ERROR;
    pstPrefPlmnCnf     = (TAF_MMA_PREF_PLMN_SET_CNF_STRU*)pstMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPrefPlmnCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPrefPlmnSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPrefPlmnSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CPOL_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPrefPlmnSetCnf : Current Option is not AT_CMD_CPOL_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_PREF_PLMN_OPER_RESULT_SUCCESS != pstPrefPlmnCnf->enRslt)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ??????AT+CPOL???????????? */
    gstAtSendData.usBufLen = 0;

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaPrefPlmnQueryCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT32                          ulResult = AT_FAILURE;
    VOS_UINT16                          usLength = 0;
    TAF_PLMN_NAME_LIST_STRU            *pstAvailPlmnInfo;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulValidPlmnNum;
    TAF_MMA_CPOL_INFO_QUERY_REQ_STRU    stCpolInfo;
    VOS_UINT8                           ucIndex;
    TAF_MMA_PREF_PLMN_QUERY_CNF_STRU   *pstCpolQryCnf = VOS_NULL_PTR;

    pstCpolQryCnf    = (TAF_MMA_PREF_PLMN_QUERY_CNF_STRU *)pstMsg;

    pstAvailPlmnInfo = (TAF_PLMN_NAME_LIST_STRU*)&pstCpolQryCnf->stPlmnName;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCpolQryCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_QryParaRspPrefPlmnProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_QryParaRspPrefPlmnProc : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    /*??????????????????????AT_CMD_CPOL_READ */
    if (AT_CMD_CPOL_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    if (TAF_MMA_APP_PREF_PLMN_OPER_RESULT_SUCCESS != pstCpolQryCnf->enRslt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);

        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_CME_UNKNOWN);

        return VOS_OK;
    }

    ulValidPlmnNum = 0;
    AT_ReportQryPrefPlmnCmd(pstCpolQryCnf, &ulValidPlmnNum, pstNetCtx, &usLength, ucIndex);

    /*
    AT????????MMA????????????????????????????????????????????: ????????????????
    ??????????????????????????????????????????????:
    AT????????????37??????????????????????????????????????????????????????????????????????
    ??????????????????????????????37????????????????????
    ??????????????37??????????AT??????????????????????????MMA??????????????????????0
    */
    if (pstAvailPlmnInfo->ulPlmnNum < TAF_MMA_MAX_PLMN_NAME_LIST_NUM)
    {
        /* ????V.250????5.7.2: ????V???????????????????????????????????????? */
        if ((AT_V_ENTIRE_TYPE == gucAtVType)
         && (0 != (pstCpolQryCnf->ulValidPlmnNum + ulValidPlmnNum)))
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s",
                                               gaucAtCrLf);

        }

        At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

        /* ????AT_STOP_TIMER_CMD_READY????AT??????????????READY???? */
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_OK);
    }
    else
    {
        At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

        stCpolInfo.enPrefPLMNType   = pstNetCtx->enPrefPlmnType;
        stCpolInfo.ulFromIndex      = (pstCpolQryCnf->ulFromIndex + pstAvailPlmnInfo->ulPlmnNum);
        stCpolInfo.ulPlmnNum        = TAF_MMA_MAX_PLMN_NAME_LIST_NUM;
        stCpolInfo.ulValidPlmnNum   = (pstCpolQryCnf->ulValidPlmnNum + ulValidPlmnNum);
        ulResult                    = TAF_MMA_QueryCpolReq(WUEPS_PID_AT,
                                      gastAtClientTab[ucIndex].usClientId,
                                      0,
                                      &stCpolInfo);
        if (VOS_TRUE != ulResult)
        {
            /* ????AT_STOP_TIMER_CMD_READY????AT??????????????READY???? */
            AT_STOP_TIMER_CMD_READY(ucIndex);
            gstAtSendData.usBufLen = 0;
            At_FormatResultData(ucIndex, AT_CME_UNKNOWN);
        }
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaPrefPlmnTestCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_PREF_PLMN_TEST_CNF_STRU    *pstPrefPlmnCnf;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulResult;

    /* ?????????????? */
    ucIndex            = 0;
    usLength           = 0;
    ulResult           = AT_ERROR;
    pstPrefPlmnCnf     = (TAF_MMA_PREF_PLMN_TEST_CNF_STRU*)pstMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPrefPlmnCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPrefPlmnTestCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPrefPlmnTestCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CPOL_TEST != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPrefPlmnTestCnf : Current Option is not AT_CMD_CPOL_TEST.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_PREF_PLMN_OPER_RESULT_SUCCESS != pstPrefPlmnCnf->enRslt)
    {
        gstAtSendData.usBufLen = usLength;
        At_FormatResultData(ucIndex, AT_CME_UNKNOWN);

        return VOS_OK;
    }

    /* ??????AT+CPOL???????????? */
    gstAtSendData.usBufLen = 0;
    if ( 0 == pstPrefPlmnCnf->usPlmnNum )
    {
        ulResult = AT_CME_OPERATION_NOT_ALLOWED;
    }
    else
    {
        usLength = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                         (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                         "%s: (1-%d),(0-2)",
                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                         pstPrefPlmnCnf->usPlmnNum);


        ulResult = AT_OK;
    }

    gstAtSendData.usBufLen = usLength;

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaAcInfoChangeInd(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT16                          usLength;
    TAF_MMA_CELL_AC_INFO_STRU          *pstCellAcInfo = VOS_NULL_PTR;
    /* Modified by l60609 for DSDA Phase III, 2013-2-25, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;
    /* Modified by k902809 for Iteration 11, 2015-3-24, begin */
    TAF_MMA_AC_INFO_CHANGE_IND_STRU    *psAcInfoChangeInd = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    psAcInfoChangeInd = (TAF_MMA_AC_INFO_CHANGE_IND_STRU*)pstMsg;

    if (AT_FAILURE == At_ClientIdToUserId(psAcInfoChangeInd->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAcInfoChangeInd : AT INDEX NOT FOUND!");
        return VOS_ERR;
    }
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-24, end */

    enModemId = MODEM_ID_0;

    usLength = 0;
    /* Modified by k902809 for Iteration 11, 2015-3-24, begin */
    pstCellAcInfo = (TAF_MMA_CELL_AC_INFO_STRU*)(&psAcInfoChangeInd->stCellAcInfo);
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-24, end */

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_RcvMmaAcInfoChangeInd: Get modem id fail.");
        return VOS_ERR;
    }

    /* ????AT^CURC?????????????????????? */
    /* Deleted by k902809 for Iteration 11, 2015-4-1, begin */
    /* Deleted by k902809 for Iteration 11, Iteration 11 2015-4-1, end */
    /* Modified by l60609 for DSDA Phase III, 2013-2-25, End */

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s%d,%d,%d,%d%s",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_ACINFO].pucText,
                                       pstCellAcInfo->enSrvDomain,/* ?????????? */
                                       pstCellAcInfo->enCellAcType,/* ???????????????????? */
                                       pstCellAcInfo->ucRestrictRegister,/* ???????????????? */
                                       pstCellAcInfo->ucRestrictPagingRsp,/* ???????????????? */
                                       gaucAtCrLf);

    gstAtSendData.usBufLen = usLength;

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}

/* Added by k902809 for Iteration 11, 2015-3-24, begin */

VOS_UINT32 AT_RcvMmaEOPlmnSetCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    TAF_MMA_EOPLMN_SET_CNF_STRU        *pstEOPlmnSetCnf = VOS_NULL_PTR;

    pstEOPlmnSetCnf  = (TAF_MMA_EOPLMN_SET_CNF_STRU *)pstMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEOPlmnSetCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaEOPlmnSetCnf At_ClientIdToUserId FAILURE");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaEOPlmnSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_EOPLMN_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMmaEOPlmnSetCnf: WARNING:Not AT_CMD_EOPLMN_SET!");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if( TAF_ERR_NO_ERROR == pstEOPlmnSetCnf->ulResult)
    {
        ulRslt = AT_OK;
    }
    else
    {
        ulRslt = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;


    At_FormatResultData(ucIndex,ulRslt);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaEOPlmnQryCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT16                                              usLen;
    VOS_UINT8                                               ucIndex;
    VOS_UINT32                                              ulRslt;
    TAF_MMA_EOPLMN_QRY_CNF_STRU                            *pstEOPlmnQryCnf = VOS_NULL_PTR;

    usLen            = 0;
    pstEOPlmnQryCnf  = (TAF_MMA_EOPLMN_QRY_CNF_STRU *)pstMsg;

    /* ????ClientId????ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstEOPlmnQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaEOPlmnQryCnf At_ClientIdToUserId FAILURE");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_EOPLMN_QRY */
    if (AT_CMD_EOPLMN_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMmaEOPlmnQryCnf: WARNING:Not AT_CMD_EOPLMN_QRY!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????? */
    if (TAF_ERR_NO_ERROR == pstEOPlmnQryCnf->ulResult)
    {
        usLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLen,
                                        "%s: \"%s\",%d,",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        pstEOPlmnQryCnf->aucVersion,
                                        pstEOPlmnQryCnf->usOPlmnNum * TAF_AT_PLMN_WITH_RAT_LEN);


        /* ??16????????????ASCII???????????????????? */
        usLen += (TAF_UINT16)At_HexText2AsciiStringSimple(AT_CMD_MAX_LEN,
                                                            (TAF_INT8 *)pgucAtSndCodeAddr,
                                                            (TAF_UINT8 *)pgucAtSndCodeAddr + usLen,
                                                            pstEOPlmnQryCnf->usOPlmnNum * TAF_SIM_PLMN_WITH_RAT_LEN,
                                                            pstEOPlmnQryCnf->aucOPlmnList);

        gstAtSendData.usBufLen = usLen;

        ulRslt = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulRslt = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaNetScanCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_NET_SCAN_CNF_STRU          *pstNetScanCnf       = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstNetScanCnf  = (TAF_MMA_NET_SCAN_CNF_STRU *)pstMsg;

    if (AT_FAILURE == At_ClientIdToUserId(pstNetScanCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaNetScanCnf At_ClientIdToUserId FAILURE");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaNetScanCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    if ( TAF_MMA_NET_SCAN_RESULT_SUCCESS == pstNetScanCnf->enResult )
    {
        AT_PhNetScanReportSuccess(ucIndex, pstNetScanCnf);
    }
    else
    {
        AT_PhNetScanReportFailure(ucIndex, pstNetScanCnf->enCause);
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaUserSrvStateQryCnf(
    VOS_VOID                           *pstMsg
)
{
    /* Modified by k902809 for Iteration 11, 2015-3-28, begin */
    TAF_MMA_USER_SRV_STATE_QRY_CNF_STRU                    *pstUserSrvStateCnf = VOS_NULL_PTR;
    VOS_UINT16                                              usLength;
    VOS_UINT8                                               ucIndex;

    pstUserSrvStateCnf = (TAF_MMA_USER_SRV_STATE_QRY_CNF_STRU *)pstMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstUserSrvStateCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaUserSrvStateQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaUserSrvStateQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_USER_SRV_STATE_READ */
    if (AT_CMD_USER_SRV_STATE_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-28, end */
    usLength  = 0;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "^USERSRVSTATE: ");

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,%d",
                                       pstUserSrvStateCnf->ulCsSrvExistFlg,
                                       pstUserSrvStateCnf->ulPsSrvExistFlg);

    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}



VOS_UINT32  AT_RcvMmaPwrOnAndRegTimeQryCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT32                                              ulCostTime;
    VOS_UINT16                                              usLength;
    VOS_UINT32                                              ulResult;
    /* Modified by k902809 for Iteration 11, 2015-3-28, begin */
    TAF_MMA_POWER_ON_AND_REG_TIME_QRY_CNF_STRU             *pstAppwronregCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstAppwronregCnf = (TAF_MMA_POWER_ON_AND_REG_TIME_QRY_CNF_STRU *)pstMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstAppwronregCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPwrOnAndRegTimeQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPwrOnAndRegTimeQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_REGISTER_TIME_READ */
    if (AT_CMD_REGISTER_TIME_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    ulCostTime = pstAppwronregCnf->ulCostTime;
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-28, end */

    /* ?????? */
    ulResult   = AT_OK;
    usLength   = 0;

    /* MMA????AT??????slice??????(32 * 1024)??slice??1S
       ????slice??0????????????????????????slice????1S,AT??1S???? */

    /* ????????????????APP*/
    if ( 0 ==  ulCostTime)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulCostTime = ulCostTime/(32 * 1024);

        if (0 == ulCostTime)
        {
            ulCostTime = 1;
        }

        ulResult   = AT_OK;

        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s",
                                          gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:%d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           ulCostTime);
    }

    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex,ulResult);

    return VOS_OK;
}


VOS_UINT32  AT_RcvMmaSpnQryCnf(
    VOS_VOID                           *pstMsg
)
{
    /* Added by k902809 for Iteration 11, 2015-3-30, begin */
    TAF_MMA_SPN_QRY_CNF_STRU           *pstSpnCnf;
    /* Added by k902809 for Iteration 11, Iteration 11 2015-3-30, end */
    VOS_UINT32                          ulResult;
    TAF_PH_USIM_SPN_STRU                stAtSPNRslt;
    VOS_UINT16                          usLength;
    VOS_UINT16                          usDatalen;
    /* Modified by s62952 for BalongV300R002 Build???????? 2012-02-28, begin */
    VOS_UINT8                          *pucSystemAppConfig;
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, Begin */
    VOS_UINT8                           ucIndex;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstSpnCnf = (TAF_MMA_SPN_QRY_CNF_STRU *)pstMsg ;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstSpnCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSpnQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSpnQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_SPN_QUERY */
    if (AT_CMD_SPN_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, End */

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();
    /* Modified by s62952 for BalongV300R002 Build???????? 2012-02-28, end */

    /* ?????? */
    ulResult  = AT_OK;
    usLength  = 0;
    usDatalen = 0;

    TAF_MEM_SET_S(&stAtSPNRslt, (VOS_SIZE_T)sizeof(stAtSPNRslt), 0x00, (VOS_SIZE_T)sizeof(TAF_PH_USIM_SPN_STRU));
    /* 0 ????SIM */
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, Begin */
    if (1 == pstNetCtx->ucSpnType)
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, End */
    {
        TAF_MEM_CPY_S(&stAtSPNRslt, sizeof(stAtSPNRslt), &(pstSpnCnf->stMnMmaSpnInfo.stUsimSpnInfo), sizeof(TAF_PH_USIM_SPN_STRU));
    }
    else
    {
        TAF_MEM_CPY_S(&stAtSPNRslt, sizeof(stAtSPNRslt), &(pstSpnCnf->stMnMmaSpnInfo.stSimSpnInfo), sizeof(TAF_PH_USIM_SPN_STRU));
    }

    if (0 == stAtSPNRslt.ucLength)
    {
        /*  SPN file not exist */
        ulResult = AT_CME_SPN_FILE_NOT_EXISTS;
    }
    else
    {
        /* display format: ^SPN:disp_rplmn,coding,spn_name */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr+usLength,
                                            "%s:",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName);


        /* Modified by s62952 for BalongV300R002 Build???????? 2012-02-28, begin */
        if ( SYSTEM_APP_WEBUI == *pucSystemAppConfig)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr+usLength,
                                               "%d,%d,",
                                               stAtSPNRslt.ucDispRplmnMode & 0x03,
                                               stAtSPNRslt.ucCoding);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr+usLength,
                                               "%d,%d,",
                                               stAtSPNRslt.ucDispRplmnMode & 0x01,
                                               stAtSPNRslt.ucCoding);
        }

        if ( stAtSPNRslt.ucCoding == TAF_PH_GSM_7BIT_DEFAULT )
        {
            usDatalen = stAtSPNRslt.ucLength;
            TAF_MEM_CPY_S(pgucAtSndCodeAddr + usLength,
                AT_CMD_MAX_LEN + 20 - 3 - usLength,
                stAtSPNRslt.aucSpnName,
                usDatalen);
            usLength = usLength + usDatalen;
        }
        else
        {
            usDatalen = stAtSPNRslt.ucLength;

            usLength += (VOS_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN,
                                                            (VOS_INT8 *)pgucAtSndCodeAddr,
                                                            (VOS_UINT8 *)pgucAtSndCodeAddr + usLength,
                                                            stAtSPNRslt.aucSpnName,
                                                            (VOS_UINT16)usDatalen);
        }
    }

    gstAtSendData.usBufLen = usLength;

    /* ???????????????? */
    At_FormatResultData(ucIndex,ulResult);

    return VOS_OK;
}



VOS_UINT32  AT_RcvMmaMMPlmnInfoQryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_MMPLMNINFO_QRY_CNF_STRU    *pstMMPlmnInfoCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT8                           i;
    VOS_UINT8                           ucIndex;

    /* ?????????? */
    pstMMPlmnInfoCnf = (TAF_MMA_MMPLMNINFO_QRY_CNF_STRU *)pstMsg;
    ulResult    = AT_ERROR;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMMPlmnInfoCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaMMPlmnInfoQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaMMPlmnInfoQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_MMPLMNINFO_QRY */
    if (AT_CMD_MMPLMNINFO_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ????LongName??ShortName */
    if ( pstMMPlmnInfoCnf->stMmPlmnInfo.ucLongNameLen <= TAF_PH_OPER_NAME_LONG
      && pstMMPlmnInfoCnf->stMmPlmnInfo.ucShortNameLen <= TAF_PH_OPER_NAME_SHORT )
    {

        /* ^MMPLMNINFO:<long name>,<short name> */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        for (i = 0; i < pstMMPlmnInfoCnf->stMmPlmnInfo.ucLongNameLen; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%02X",
                                               pstMMPlmnInfoCnf->stMmPlmnInfo.aucLongName[i]);
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr + usLength, ",");

        for (i = 0; i < pstMMPlmnInfoCnf->stMmPlmnInfo.ucShortNameLen; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%02X",
                                               pstMMPlmnInfoCnf->stMmPlmnInfo.aucShortName[i]);
        }

        ulResult = AT_OK;
        gstAtSendData.usBufLen = usLength;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
    }

    At_FormatResultData(ucIndex,ulResult);

    return VOS_OK;
}


VOS_UINT32  AT_RcvMmaPlmnQryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_LAST_CAMP_PLMN_QRY_CNF_STRU                    *pstPlmnCnf = VOS_NULL_PTR;
    VOS_UINT16                                              usLength;
    VOS_UINT8                                               ucIndex;

    pstPlmnCnf = (TAF_MMA_LAST_CAMP_PLMN_QRY_CNF_STRU *)pstMsg;
    usLength  = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPlmnCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPlmnQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPlmnQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_PLMN_QRY */
    if (AT_CMD_PLMN_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????PLMN */
    if ((0 == pstPlmnCnf->stPlmnId.Mcc)
     && (0 == pstPlmnCnf->stPlmnId.Mnc))
    {
        At_FormatResultData(ucIndex, AT_OK);
        return VOS_ERR;
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s^PLMN: ",
                                       gaucAtCrLf);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%x%x%x,",
                                       (pstPlmnCnf->stPlmnId.Mcc & 0x0f00)>>8,
                                       (pstPlmnCnf->stPlmnId.Mcc & 0xf0)>>4,
                                       (pstPlmnCnf->stPlmnId.Mcc & 0x0f));

    if (0x0f00 == (pstPlmnCnf->stPlmnId.Mnc & 0x0f00))
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%x%x",
                                           (pstPlmnCnf->stPlmnId.Mnc & 0xf0)>>4,
                                           (pstPlmnCnf->stPlmnId.Mnc & 0x0f));
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%x%x%x",
                                           (pstPlmnCnf->stPlmnId.Mnc & 0x0f00)>>8,
                                           (pstPlmnCnf->stPlmnId.Mnc & 0xf0)>>4,
                                           (pstPlmnCnf->stPlmnId.Mnc & 0x0f));
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s",
                                       gaucAtCrLf);

    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, AT_OK);
    return VOS_OK;

}

/* Added by k902809 for Iteration 11, Iteration 11 2015-3-24, end */



VOS_UINT32 AT_RcvMmaCerssiSetCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_CERSSI_SET_CNF_STRU        *pstCerssiSetCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstCerssiSetCnf = (TAF_MMA_CERSSI_SET_CNF_STRU *)pstMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCerssiSetCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCerssiSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCerssiSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CERSSI_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaCerssiSetCnf : Current Option is not AT_CMD_CERSSI_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_ERR_NO_ERROR == pstCerssiSetCnf->enErrorCause)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstCerssiSetCnf->enErrorCause);
    }

    gstAtSendData.usBufLen = 0;

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaPlmnReselAutoSetCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_PLMN_AUTO_RESEL_CNF_STRU   *pstPlmnReselAutoCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstPlmnReselAutoCnf = (TAF_MMA_PLMN_AUTO_RESEL_CNF_STRU *)pstMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPlmnReselAutoCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPlmnReselAutoSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPlmnReselAutoSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_COPS_SET_AUTOMATIC != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPlmnReselAutoSetCnf : Current Option is not AT_CMD_COPS_SET_AUTOMATIC.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_ERR_NO_ERROR == pstPlmnReselAutoCnf->enErrorCause)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstPlmnReselAutoCnf->enErrorCause);
    }

    gstAtSendData.usBufLen = 0;

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

VOS_UINT32 AT_RcvMmaPlmnSpecialSelSetCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_PLMN_SPECIAL_SEL_CNF_STRU  *pstPlmnSpecialSelCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstPlmnSpecialSelCnf = (TAF_MMA_PLMN_SPECIAL_SEL_CNF_STRU *)pstMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPlmnSpecialSelCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPlmnSpecialSelSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPlmnSpecialSelSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_COPS_SET_MANUAL != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPlmnSpecialSelSetCnf : Current Option is not AT_CMD_COPS_SET_MANUAL.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_ERR_NO_ERROR == pstPlmnSpecialSelCnf->enErrorCause)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstPlmnSpecialSelCnf->enErrorCause);
    }

    gstAtSendData.usBufLen = 0;

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

VOS_UINT32 AT_RcvMmaPlmnListAbortCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_PLMN_LIST_ABORT_CNF_STRU   *pstPlmnListAbortCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstPlmnListAbortCnf = (TAF_MMA_PLMN_LIST_ABORT_CNF_STRU *)pstMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPlmnListAbortCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPlmnSpecialSelSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPlmnSpecialSelSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    /* ????????, ??????????????ABORT??????????????ABORT.
       ??AT??ABORT????????????????, ??????????MMA??ABORT_CNF????????ABORT */
    if (AT_CMD_COPS_ABORT_PLMN_LIST != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPlmnSpecialSelSetCnf : Current Option is not AT_CMD_COPS_SET_MANUAL.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    ulResult = AT_ABORT;

    gstAtSendData.usBufLen = 0;

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

VOS_UINT32 AT_RcvMmaPowerDownCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_MT_POWER_DOWN_CNF_STRU     *pstPrefPlmnTypeSetCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstPrefPlmnTypeSetCnf = (TAF_MMA_MT_POWER_DOWN_CNF_STRU *)pstMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPrefPlmnTypeSetCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPowerDownCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPowerDownCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_MMA_MT_POWER_DOWN != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPowerDownCnf : Current Option is not AT_CMD_MMA_MT_POWER_DOWN.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_ERR_NO_ERROR == pstPrefPlmnTypeSetCnf->enErrorCause)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

VOS_UINT32 AT_RcvMmaPrefPlmnTypeSetCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_PREF_PLMN_TYPE_SET_CNF_STRU    *pstPrefPlmnTypeSetCnf = VOS_NULL_PTR;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    AT_MODEM_NET_CTX_STRU                  *pstNetCtx = VOS_NULL_PTR;

    pstPrefPlmnTypeSetCnf = (TAF_MMA_PREF_PLMN_TYPE_SET_CNF_STRU *)pstMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPrefPlmnTypeSetCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPrefPlmnTypeSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPrefPlmnTypeSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_MMA_SET_PREF_PLMN_TYPE != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPrefPlmnTypeSetCnf : Current Option is not AT_CMD_MMA_SET_PREF_PLMN_TYPE.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    pstNetCtx->enPrefPlmnType = pstPrefPlmnTypeSetCnf->enPrefPlmnType;

    ulResult = AT_OK;

    gstAtSendData.usBufLen = 0;

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

VOS_UINT32 AT_RcvMmaPhoneModeQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_PHONE_MODE_QRY_CNF_STRU    *pstPhoneModeQryCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstPhoneModeQryCnf = (TAF_MMA_PHONE_MODE_QRY_CNF_STRU *)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPhoneModeQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPhoneModeQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPhoneModeQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_CFUN_READ */
    if (AT_CMD_CFUN_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPhoneModeQryCnf : Current Option is not AT_CMD_CFUN_READ.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = 0;

    if (TAF_ERR_NO_ERROR == pstPhoneModeQryCnf->enErrorCause)
    {
        gstAtSendData.usBufLen  = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                         "%s: %d",
                                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                         pstPhoneModeQryCnf->ucPhMode);
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstPhoneModeQryCnf->enErrorCause);
    }

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvTafMmaQuickStartSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_QUICKSTART_SET_CNF_STRU    *pstQuickStartSetCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstQuickStartSetCnf = (TAF_MMA_QUICKSTART_SET_CNF_STRU *)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstQuickStartSetCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaQuickStartSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaQuickStartSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_CQST_SET */
    if (AT_CMD_CQST_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvTafMmaQuickStartSetCnf : Current Option is not AT_CMD_CQST_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_PARA_OK == pstQuickStartSetCnf->ucResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvTafMmaAutoAttachSetCnf(
    VOS_VOID                           *pMsg
)
{
     TAF_MMA_AUTO_ATTACH_SET_CNF_STRU   *pstAutoAttachSetCnf = VOS_NULL_PTR;
     VOS_UINT8                           ucIndex;
     AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_FAILURE;

     pstAutoAttachSetCnf = (TAF_MMA_AUTO_ATTACH_SET_CNF_STRU *)pMsg;

     ucIndex             = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

     /* ????clientid????index */
     if (AT_FAILURE == At_ClientIdToUserId(pstAutoAttachSetCnf->stCtrl.usClientId, &ucIndex))
     {
         AT_WARN_LOG("AT_RcvTafMmaAutoAttachSetCnf : WARNING:AT INDEX NOT FOUND!");
         return VOS_ERR;
     }

     if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
     {
         AT_WARN_LOG("AT_RcvTafMmaAutoAttachSetCnf : AT_BROADCAST_INDEX.");
         return VOS_ERR;
     }

     /* ??????????????????????AT_CMD_CAATT_SET */
     if (AT_CMD_CAATT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
     {
         AT_WARN_LOG("AT_RcvTafMmaAutoAttachSetCnf : Current Option is not AT_CMD_CAATT_SET.");
         return VOS_ERR;
     }

     AT_STOP_TIMER_CMD_READY(ucIndex);

     if (TAF_PARA_OK == pstAutoAttachSetCnf->ucResult)
     {
         ulResult = AT_OK;
     }
     else
     {
         ulResult = AT_ERROR;
     }

     /* ????At_FormatResultData???????????? */
     At_FormatResultData(ucIndex, ulResult);

     return VOS_OK;

}


VOS_UINT32 AT_RcvTafMmaSyscfgQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_SYSCFG_QRY_CNF_STRU        *pstSyscfgQryCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_FAILURE;
    TAF_UINT16                          usLength = VOS_NULL;

    pstSyscfgQryCnf = (TAF_MMA_SYSCFG_QRY_CNF_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstSyscfgQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaSyscfgQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaSyscfgQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    if(TAF_ERR_NO_ERROR != pstSyscfgQryCnf->enErrorCause)  /* MT???????? */
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstSyscfgQryCnf->enErrorCause);       /* ???????? */
    }
    else if(AT_CMD_SYSCFG_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);

        AT_ReportSysCfgQryCmdResult(&(pstSyscfgQryCnf->stSysCfg), ucIndex, &usLength);

        ulResult = AT_OK;
    }
    else if (AT_CMD_SYSCFGEX_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);

        AT_ReportSysCfgExQryCmdResult(&(pstSyscfgQryCnf->stSysCfg), ucIndex, &usLength);

        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}


VOS_UINT32 AT_RcvMmaAccessModeQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_ACCESS_MODE_QRY_CNF_STRU   *pstAccessModeCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pstAccessModeCnf    = (TAF_MMA_ACCESS_MODE_QRY_CNF_STRU *)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstAccessModeCnf->stCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAccessModeQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAccessModeQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_CPAM_READ */
    if (AT_CMD_CPAM_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* ??????????????????????????????????ERROR??????????LTE only??????GU */
    if (pstAccessModeCnf->enAccessMode >= MN_MMA_CPAM_RAT_TYPE_BUTT)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                                         "%s: %d,%d",
                                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                         pstAccessModeCnf->enAccessMode,
                                                         pstAccessModeCnf->ucPlmnPrio);
    }

    At_FormatResultData(ucIndex,ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaCopsQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_COPS_QRY_CNF_STRU          *pstCopsQryCnf;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pstCopsQryCnf    = (TAF_MMA_COPS_QRY_CNF_STRU *)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCopsQryCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCopsQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCopsQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_COPS_READ */
    if (AT_CMD_COPS_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    At_QryParaRspCopsProc(ucIndex, pstCopsQryCnf->ucOpId, (VOS_VOID *)&(pstCopsQryCnf->stCopsInfo));

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaRegStateQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_REG_STATE_QRY_CNF_STRU     *pstRegStateCnf;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pstRegStateCnf    = (TAF_MMA_REG_STATE_QRY_CNF_STRU *)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRegStateCnf->stCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaRegStateQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaRegStateQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_CREG_READ */
    if (AT_CMD_CREG_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* ????AT???? */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_QryParaRspCregProc(ucIndex, pstRegStateCnf->stCtrl.ucOpId, (VOS_VOID *)&(pstRegStateCnf->stRegInfo));
    }
    else if (AT_CMD_CGREG_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* ????AT???? */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_QryParaRspCgregProc(ucIndex, pstRegStateCnf->stCtrl.ucOpId, (VOS_VOID *)&(pstRegStateCnf->stRegInfo));
    }
    else if (AT_CMD_CEREG_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* ????AT???? */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        AT_QryParaRspCeregProc(ucIndex, pstRegStateCnf->stCtrl.ucOpId, (VOS_VOID *)&(pstRegStateCnf->stRegInfo));
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaAutoAttachQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_AUTO_ATTACH_QRY_CNF_STRU   *pstAutoAttachCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pstAutoAttachCnf    = (TAF_MMA_AUTO_ATTACH_QRY_CNF_STRU *)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstAutoAttachCnf->stCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAutoAttachQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAutoAttachQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_CAATT_READ */
    if (AT_CMD_CAATT_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (TAF_ERR_NO_ERROR == pstAutoAttachCnf->enErrorCause)
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                                         "%s: %d",
                                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                         pstAutoAttachCnf->ucAutoAttachFlag);
    }
    else
    {
        ulResult = AT_ERROR;
    }

    At_FormatResultData(ucIndex,ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaSysInfoQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_SYSINFO_QRY_CNF_STRU       *pstSysInfoCnf;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pstSysInfoCnf  = (TAF_MMA_SYSINFO_QRY_CNF_STRU *)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstSysInfoCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSysInfoQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (VOS_FALSE == pstSysInfoCnf->ucIsSupport)
    {
        /* ????AT???? */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_FormatResultData(ucIndex,AT_CMD_NOT_SUPPORT);

        return VOS_OK;

    }


    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSysInfoQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_SYSINFO_READ */
    if (AT_CMD_SYSINFO_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* ????AT???? */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_QryParaRspSysinfoProc(ucIndex, pstSysInfoCnf->ucOpId, (VOS_VOID *)&(pstSysInfoCnf->stSysInfo));

        return VOS_OK;
    }
    else if (AT_CMD_SYSINFOEX_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* ????AT???? */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        AT_QryParaRspSysinfoExProc(ucIndex, pstSysInfoCnf->ucOpId, (VOS_VOID *)&(pstSysInfoCnf->stSysInfo));

        return VOS_OK;
    }
    else
    {
        return VOS_ERR;
    }
}


VOS_UINT32 AT_RcvMtaAnqueryQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg              = VOS_NULL_PTR;
    MTA_AT_ANTENNA_INFO_QRY_CNF_STRU   *pstAntennaInfoQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pRcvMsg                 = (AT_MTA_MSG_STRU *)pMsg;
    pstAntennaInfoQryCnf    = (MTA_AT_ANTENNA_INFO_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaAnqueryQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaAnqueryQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_ANQUERY_READ */
    if (AT_CMD_ANQUERY_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (MTA_AT_RESULT_NO_ERROR == pstAntennaInfoQryCnf->enResult)
    {
        AT_QryParaAnQueryProc(ucIndex,
                              pRcvMsg->stAppCtrl.ucOpId,
                              (VOS_VOID *)&(pstAntennaInfoQryCnf->stAntennaInfo));
    }
    else
    {
        ulResult = AT_CME_UNKNOWN;

        At_FormatResultData(ucIndex, ulResult);
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaEHplmnInfoQryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_HOME_PLMN_QRY_CNF_STRU     *pstHplmnCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstHplmnCnf  = (TAF_MMA_HOME_PLMN_QRY_CNF_STRU *)pstMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstHplmnCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaEHplmnInfoQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaEHplmnInfoQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????????????????????^HPLMN/^APHPLMN?????? */
    if (AT_CMD_HOMEPLMN_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* ^APHPLMN */
        return AT_RcvMmaApHplmnQryCnf(ucIndex, pstMsg);
    }
    else if (AT_CMD_EHPLMN_LIST_QRY == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* ^HPLMN */
        return AT_RcvMmaHplmnQryCnf(ucIndex, pstMsg);
    }
    else
    {
        return VOS_ERR;
    }

}


VOS_UINT32 AT_RcvMmaApHplmnQryCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_HOME_PLMN_QRY_CNF_STRU     *pstHplmnCnf;
    VOS_UINT32                          ulResult;
    TAF_MMA_HPLMN_WITH_MNC_LEN_STRU     stHplmn;

    /* ?????? */
    pstHplmnCnf  = (TAF_MMA_HOME_PLMN_QRY_CNF_STRU *)pstMsg;

    /* index??????????????AT_RcvMmaEHplmnInfoQryCnf?? */

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_ERR_NO_ERROR == pstHplmnCnf->enErrorCause)
    {
        TAF_MEM_SET_S(&stHplmn, sizeof(stHplmn), 0x00, sizeof(TAF_MMA_HPLMN_WITH_MNC_LEN_STRU));
        stHplmn.ucHplmnMncLen   = pstHplmnCnf->stEHplmnInfo.ucHplmnMncLen;

        stHplmn.stHplmn.Mcc     = (pstHplmnCnf->stEHplmnInfo.aucImsi[1] & 0xF0) >> 4;
        stHplmn.stHplmn.Mcc     |= (pstHplmnCnf->stEHplmnInfo.aucImsi[2] & 0x0F) << 8;
        stHplmn.stHplmn.Mcc     |= (pstHplmnCnf->stEHplmnInfo.aucImsi[2] & 0xF0) << 12;

        stHplmn.stHplmn.Mnc     = (pstHplmnCnf->stEHplmnInfo.aucImsi[3] & 0x0F);
        stHplmn.stHplmn.Mnc     |= (pstHplmnCnf->stEHplmnInfo.aucImsi[3] & 0xF0) << 4;
        stHplmn.stHplmn.Mnc     |= (pstHplmnCnf->stEHplmnInfo.aucImsi[4] & 0x0F) << 16;

        AT_QryParaHomePlmnProc(ucIndex,
                               pstHplmnCnf->stCtrl.ucOpId,
                               (VOS_VOID *)&stHplmn);

        return VOS_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstHplmnCnf->enErrorCause);

        gstAtSendData.usBufLen = 0;

        At_FormatResultData(ucIndex,ulResult);

        return VOS_ERR;
    }
}


VOS_UINT32 AT_RcvMmaSrvStatusInd(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_SRV_STATUS_IND_STRU        *pstSrvStatusInd;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;

    /* ?????????????? */
    ucIndex             = 0;
    usLength            = 0;
    pstSrvStatusInd     = (TAF_MMA_SRV_STATUS_IND_STRU*)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstSrvStatusInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaSrvStatusInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG("AT_RcvMmaSrvStatusInd: Get modem id fail.");
        return VOS_ERR;
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s%d%s",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_SRVST].pucText,
                                       pstSrvStatusInd->ucSrvStatus,
                                       gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaImsiRefreshInd(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_IMSI_REFRESH_IND_STRU      *pstImsiRefreshInd;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;

    /* ?????????????? */
    ucIndex             = 0;
    usLength            = 0;
    pstImsiRefreshInd   = (TAF_MMA_IMSI_REFRESH_IND_STRU *)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstImsiRefreshInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaImsiRefreshInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG("AT_RcvMmaImsiRefreshInd: Get modem id fail.");
        return VOS_ERR;
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s%s",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_IMSI_REFRESH].pucText,
                                       gaucAtCrLf);

    gstAtSendData.usBufLen = usLength;

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}



VOS_UINT32 AT_RcvMmaRssiInfoInd(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_RSSI_INFO_IND_STRU         *pstRssiInfoInd;
    VOS_UINT8                           ucIndex;

    /* ?????????????? */
    ucIndex            = 0;
    pstRssiInfoInd     = (TAF_MMA_RSSI_INFO_IND_STRU*)pstMsg;

    /* ????ClientId????ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRssiInfoInd->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaRssiInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    AT_RcvMmaRssiChangeInd(ucIndex, pstRssiInfoInd);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaRegStatusInd(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_REG_STATUS_IND_STRU        *pstRegStatusInd;
    VOS_UINT8                           ucIndex;

    /* ?????????????? */
    ucIndex             = 0;
    pstRegStatusInd     = (TAF_MMA_REG_STATUS_IND_STRU*)pstMsg;

    /* ????ClientId????ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRegStatusInd->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaRegStatusInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    AT_ProcRegStatusInfoInd(ucIndex, pstRegStatusInd);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaRegRejInfoInd(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_REG_REJ_INFO_IND_STRU      *pstRegRejInd;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;

    /* ?????????????? */
    ucIndex          = 0;
    usLength         = 0;
    pstRegRejInd     = (TAF_MMA_REG_REJ_INFO_IND_STRU*)pstMsg;

    /* ????ClientId????ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRegRejInd->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaRegRejInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG("AT_RcvMmaRegRejInfoInd: Get modem id fail.");
        return VOS_ERR;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_REJINFO].pucText);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%x%x%x",
                                       (pstRegRejInd->stRegRejInfo.stPlmnId.Mcc & 0x0f00)>>8,
                                       (pstRegRejInd->stRegRejInfo.stPlmnId.Mcc & 0xf0)>>4,
                                       (pstRegRejInd->stRegRejInfo.stPlmnId.Mcc & 0x0f));

    if (0x0f00 == (pstRegRejInd->stRegRejInfo.stPlmnId.Mnc & 0x0f00))
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%x%x,",
                                           (pstRegRejInd->stRegRejInfo.stPlmnId.Mnc & 0xf0)>>4,
                                           (pstRegRejInd->stRegRejInfo.stPlmnId.Mnc & 0x0f));
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%x%x%x,",
                                           (pstRegRejInd->stRegRejInfo.stPlmnId.Mnc & 0x0f00)>>8,
                                           (pstRegRejInd->stRegRejInfo.stPlmnId.Mnc & 0xf0)>>4,
                                           (pstRegRejInd->stRegRejInfo.stPlmnId.Mnc & 0x0f));
    }
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,%d,%d,%d,%d,",
                                       pstRegRejInd->stRegRejInfo.enSrvDomain,
                                       pstRegRejInd->stRegRejInfo.ulRejCause,
                                       pstRegRejInd->stRegRejInfo.enRat,
                                       pstRegRejInd->stRegRejInfo.ucRejType,
                                       pstRegRejInd->stRegRejInfo.ucOriginalRejCause);

    /* lac */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucAtSndCodeAddr,
                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                "\"%X%X%X%X\",",
                0x000f & (pstRegRejInd->stRegRejInfo.usLac >> 12),
                0x000f & (pstRegRejInd->stRegRejInfo.usLac >> 8),
                0x000f & (pstRegRejInd->stRegRejInfo.usLac >> 4),
                0x000f & (pstRegRejInd->stRegRejInfo.usLac >> 0));

    /* Rac */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucAtSndCodeAddr,
                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                "\"%X%X\",",
                0x000f & (pstRegRejInd->stRegRejInfo.ucRac >> 4),
                0x000f & (pstRegRejInd->stRegRejInfo.ucRac >> 0));


    /* <CI>????4???????????? */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
            (VOS_CHAR *)pgucAtSndCodeAddr,
            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
            "\"%X%X%X%X%X%X%X%X\"%s",
            0x000f & (pstRegRejInd->stRegRejInfo.ulCellId >> 28),
            0x000f & (pstRegRejInd->stRegRejInfo.ulCellId >> 24),
            0x000f & (pstRegRejInd->stRegRejInfo.ulCellId >> 20),
            0x000f & (pstRegRejInd->stRegRejInfo.ulCellId >> 16),
            0x000f & (pstRegRejInd->stRegRejInfo.ulCellId >> 12),
            0x000f & (pstRegRejInd->stRegRejInfo.ulCellId >> 8),
            0x000f & (pstRegRejInd->stRegRejInfo.ulCellId >> 4),
            0x000f & (pstRegRejInd->stRegRejInfo.ulCellId >> 0),
            gaucAtCrLf);


    gstAtSendData.usBufLen = usLength;

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaPlmnSelectInfoInd(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_PLMN_SElECTION_INFO_IND_STRU   *pstPlmnSelecInd;
    MODEM_ID_ENUM_UINT16                    enModemId;
    VOS_UINT16                              usLength;
    VOS_UINT8                               ucIndex;

    /* ?????????????? */
    ucIndex             = 0;
    usLength            = 0;
    pstPlmnSelecInd     = (TAF_MMA_PLMN_SElECTION_INFO_IND_STRU*)pstMsg;

    /* ????ClientId????ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstPlmnSelecInd->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPlmnSelectInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG("AT_RcvMmaPlmnSelectInfoInd: Get modem id fail.");
        return VOS_ERR;
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_PLMNSELEINFO].pucText);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,%d%s",
                                       pstPlmnSelecInd->stPlmnSelectInfo.ulPlmnSelectFlag,
                                       pstPlmnSelecInd->stPlmnSelectInfo.ulPlmnSelectRlst,
                                       gaucAtCrLf);

    gstAtSendData.usBufLen = usLength;

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}


VOS_UINT32 AT_RcvTafMmaSyscfgTestCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_SYSCFG_TEST_CNF_STRU       *pstSysCfgTestCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstSysCfgTestCnf = (TAF_MMA_SYSCFG_TEST_CNF_STRU *)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstSysCfgTestCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaSyscfgTestCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaSyscfgTestCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* Modified by l60609 for DSDA Phase III, 2013-2-22, Begin */
    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    /* SYSCFG */
    if (AT_CMD_SYSCFG_TEST == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        if (AT_ROAM_FEATURE_OFF == pstNetCtx->ucRoamFeature)
        {
            AT_STOP_TIMER_CMD_READY(ucIndex);
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            "%s: (2,13,14,16),(0-3),%s,(0-2),(0-4)",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            pstSysCfgTestCnf->stBandInfo.strSysCfgBandGroup);
        }
        else
        {
            AT_STOP_TIMER_CMD_READY(ucIndex);
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            "%s: (2,13,14,16),(0-3),%s,(0-3),(0-4)",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            pstSysCfgTestCnf->stBandInfo.strSysCfgBandGroup);
        }

    }
    /* SYSCFGEX */
    else
    {
        if (AT_ROAM_FEATURE_OFF == pstNetCtx->ucRoamFeature)
        {
            AT_STOP_TIMER_CMD_READY(ucIndex);
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            "%s: (\"01\",\"02\",\"03\",\"04\",\"07\"),%s,(0-2),(0-4),((7fffffffffffffff,\"All bands\"))",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            pstSysCfgTestCnf->stBandInfo.strSysCfgBandGroup);
        }
        else
        {
            AT_STOP_TIMER_CMD_READY(ucIndex);
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            "%s: (\"01\",\"02\",\"03\",\"04\",\"07\"),%s,(0-3),(0-4),((7fffffffffffffff,\"All bands\"))",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            pstSysCfgTestCnf->stBandInfo.strSysCfgBandGroup);
        }
    }
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, End */

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}



VOS_UINT32 AT_RcvTafMmaQuickStartQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_QUICKSTART_QRY_CNF_STRU    *pstQuickStartQryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pstQuickStartQryCnf = (TAF_MMA_QUICKSTART_QRY_CNF_STRU *)pMsg;
    ulResult = AT_OK;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstQuickStartQryCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaQuickStartQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaQuickStartQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_CQST_READ */
    if (AT_CMD_CQST_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* ??????????????????????????????????ERROR??????????LTE only??????GU */
    if (TAF_ERR_NO_ERROR != pstQuickStartQryCnf->enErrorCause)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                                         "%s: %d",
                                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                         pstQuickStartQryCnf->ulQuickStartMode);
    }

    At_FormatResultData(ucIndex,ulResult);
    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaCsnrQryCnf(
    VOS_VOID                           *pMsg
)
{
    MTA_AT_CSNR_QRY_CNF_STRU           *pstrCsnrQryCnf    = VOS_NULL_PTR;
    AT_MTA_MSG_STRU                    *pstRcvMsg         = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pstRcvMsg      = (AT_MTA_MSG_STRU *)pMsg;
    pstrCsnrQryCnf = (MTA_AT_CSNR_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult       = AT_OK;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCsnrQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCsnrQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_CSNR_READ */
    if (AT_CMD_CSNR_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstrCsnrQryCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    (TAF_INT32)pstrCsnrQryCnf->stCsnrPara.sCpichRscp,
                                                    (TAF_INT32)pstrCsnrQryCnf->stCsnrPara.sCpichEcNo);
    }

    /* ???????????????? */
    At_FormatResultData(ucIndex,ulResult);
    return  VOS_OK;
}


VOS_UINT32 AT_RcvTafMmaCsqQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_CSQ_QRY_CNF_STRU           *pstrCsqQryCnf;
    VOS_UINT32                          ulResult = AT_FAILURE;
    VOS_UINT8                           ucIndex;
    TAF_UINT16                          usLength = 0;
    TAF_PH_RSSI_STRU                    stCsq;

    /* ?????? */
    pstrCsqQryCnf = (TAF_MMA_CSQ_QRY_CNF_STRU *)pMsg;
    ulResult = AT_OK;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstrCsqQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaCsqQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaCsqQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_CSQ_SET */
    if (AT_CMD_CSQ_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    TAF_MEM_CPY_S(&stCsq, sizeof(stCsq), &pstrCsqQryCnf->stCsq, sizeof(TAF_PH_RSSI_STRU));
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    if (TAF_ERR_NO_ERROR  != pstrCsqQryCnf->enErrorCause)
    {
        ulResult = AT_ERROR;
    }
    else{
        ulResult = AT_OK;
        if(stCsq.ucRssiNum > 0)
        {
            /* ???????????? */
            if((stCsq.aRssi[0].ucRssiValue >= 31) && (stCsq.aRssi[0].ucRssiValue < 99))
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%d",31);
            }
            else
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%d",stCsq.aRssi[0].ucRssiValue);
            }
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",%d",stCsq.aRssi[0].ucChannalQual);
        }
    }

    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex,ulResult);
    return VOS_OK;

}


VOS_UINT32 AT_RcvMtaCsqlvlQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg         = VOS_NULL_PTR;
    MTA_AT_CSQLVL_QRY_CNF_STRU         *pstrCsqlvlQryCnf  = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    AT_MTA_CSQLVL_PARA_STRU             stCsqlvl;
    AT_MTA_CSQLVLEXT_PARA_STRU          stCsqlvlext;

    /* ?????? */
    pstRcvMsg        = (AT_MTA_MSG_STRU *)pMsg;
    pstrCsqlvlQryCnf = (MTA_AT_CSQLVL_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult         = AT_OK;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCsqlvlQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCsqlvlQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    TAF_MEM_CPY_S(&stCsqlvlext, sizeof(stCsqlvlext), &pstrCsqlvlQryCnf->stCsqLvlExtPara, sizeof(AT_MTA_CSQLVLEXT_PARA_STRU));
    stCsqlvl = pstrCsqlvlQryCnf->stCsqLvlPara;

    if (MTA_AT_RESULT_NO_ERROR  == pstrCsqlvlQryCnf->enResult)
    {
        if (AT_CMD_CSQLVL_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
        {
            /* ????AT???? */
            AT_STOP_TIMER_CMD_READY(ucIndex);

            ulResult = AT_OK;
            /* ????MMA??????????????????Csqlvl????????*/
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,
                                                            "%s: %d,%d",
                                                             g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                             stCsqlvl.usLevel,
                                                             stCsqlvl.usRscp);
        }
        else if (AT_CMD_CSQLVLEXT_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
        {
            /* ????AT???? */
            AT_STOP_TIMER_CMD_READY(ucIndex);

            ulResult = AT_OK;
            /* ????MMA??????????????????Csqlvl????????*/
            /* ????MMA??????????????????CsqlvlExt????????*/
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,
                                                            "%s: %d,%d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            stCsqlvlext.enRssilv,
                                                            stCsqlvlext.enBer);
        }
        else
        {
            AT_WARN_LOG("AT_RcvMtaCsqlvlQryCnf : CmdCurrentOpt is invalid.");
            ulResult = AT_ERROR;
        }

    }
    else
    {
        ulResult = AT_ERROR;
    }


    At_FormatResultData(ucIndex,ulResult);
    return VOS_TRUE;
}


VOS_UINT32 AT_RcvMmaTimeChangeInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_TIME_CHANGE_IND_STRU       *pstTimeChangeInd;
    TAF_UINT16                          usLength;

    /* ?????????????? */
    ucIndex             = 0;
    pstTimeChangeInd    = (TAF_MMA_TIME_CHANGE_IND_STRU*)pMsg;
    usLength            = 0;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstTimeChangeInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaTimeChangeInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }


    if ((NAS_MM_INFO_IE_UTLTZ == (pstTimeChangeInd->ucIeFlg & NAS_MM_INFO_IE_UTLTZ))
     || (NAS_MM_INFO_IE_LTZ == (pstTimeChangeInd->ucIeFlg & NAS_MM_INFO_IE_LTZ)))
    {
        /* ???????????? */
        usLength += (TAF_UINT16)At_PrintMmTimeInfo(ucIndex,
                                                   pstTimeChangeInd,
                                                   (pgucAtSndCodeAddr + usLength));
    }

    At_SendResultData(ucIndex,pgucAtSndCodeAddr,usLength);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaModeChangeInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT16                          usLength;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;
    TAF_MMA_MODE_CHANGE_IND_STRU       *pstRcvMsg;
    pstRcvMsg = (TAF_MMA_MODE_CHANGE_IND_STRU *)pMsg;
    usLength  = 0;
    enModemId = MODEM_ID_0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaCsqlvlextQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_RcvMmaModeChangeInd: Get modem id fail.");
        return VOS_ERR;
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s%d,%d%s",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_MODE].pucText,
                                       pstRcvMsg->RatType,
                                       pstRcvMsg->ucSysSubMode,
                                       gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    /* ??????????????????????????????????????????C?????? */

    return VOS_TRUE;

}


VOS_UINT32 AT_RcvMmaPlmnChangeInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT16                          usLength;
    /* Modified by l60609 for DSDA Phase III, 2013-2-25, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;
    TAF_MMA_PLMN_CHANGE_IND_STRU       *pstRcvMsg;

    usLength  = 0;
    pstRcvMsg = (TAF_MMA_PLMN_CHANGE_IND_STRU *)pMsg;
    enModemId = MODEM_ID_0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaCsqlvlextQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }
    ulRslt    = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("At_RcvMmaPlmnChangeIndProc: Get modem id fail.");
        return VOS_ERR;
    }

    /* Modified by l60609 for DSDA Phase III, 2013-2-25, End */

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s^PLMN:",gaucAtCrLf);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr +
                                       usLength,
                                       "%x%x%x,",
                                       (pstRcvMsg->stCurPlmn.Mcc & 0x0f00)>>8,
                                       (pstRcvMsg->stCurPlmn.Mcc & 0xf0)>>4,
                                       (pstRcvMsg->stCurPlmn.Mcc & 0x0f));

    if (0x0f00 == (pstRcvMsg->stCurPlmn.Mnc & 0x0f00))
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr +
                                           usLength,
                                           "%x%x",
                                           (pstRcvMsg->stCurPlmn.Mnc & 0xf0)>>4,
                                           (pstRcvMsg->stCurPlmn.Mnc & 0x0f));
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr +
                                           usLength,
                                           "%x%x%x",
                                           (pstRcvMsg->stCurPlmn.Mnc & 0x0f00)>>8,
                                           (pstRcvMsg->stCurPlmn.Mnc & 0xf0)>>4,
                                           (pstRcvMsg->stCurPlmn.Mnc & 0x0f));
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s",gaucAtCrLf);

    At_SendResultData((VOS_UINT8)ucIndex, pgucAtSndCodeAddr, usLength);
    return VOS_TRUE;
}


VOS_UINT32 AT_RcvTafMmaCrpnQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_CRPN_QRY_CNF_STRU          *pstCrpnQryCnf;
    TAF_MMA_CRPN_QRY_INFO_STRU         *pstMnMmaCrpnQryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           aucPlmn[TAF_MAX_AUTHDATA_PLMN_LEN + 1];
    TAF_MMA_CRPN_QRY_PARA_STRU          stMnMmaCrpnQry;

    /* ?????? */
    pstCrpnQryCnf           = (TAF_MMA_CRPN_QRY_CNF_STRU *)pMsg;
    pstMnMmaCrpnQryCnf      = &pstCrpnQryCnf->stCrpnQryInfo;
    ulResult                = AT_OK;
    usLength                = 0;
    ulLoop                  = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCrpnQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaCrpnQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaCrpnQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ??????/f62575 for ??????????????????????????????, 2011/11/28, end */

    /* ????AT???????????????????? */
    if (AT_CMD_CRPN_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }


    /* ??????AT^CRPN???????????? */
    gstAtSendData.usBufLen = 0;
    if (TAF_ERR_NO_ERROR != pstCrpnQryCnf->enErrorCause)
    {
        ulResult = At_ChgTafErrorCode(ucIndex, (VOS_UINT16)pstCrpnQryCnf->enErrorCause);;

        /* ????AT_STOP_TIMER_CMD_READY????AT??????????????READY???? */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        /* ???????? */
        At_FormatResultData(ucIndex, ulResult);

        return VOS_OK;
    }

    ulResult = AT_OK;

    for (ulLoop = 0; ulLoop < pstMnMmaCrpnQryCnf->ucTotalNum; ulLoop++)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s",
                                           gaucAtCrLf);

        /* ^CRPN:  */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        /* <PLMN> */
        /* ????????????????????????????PLMN ID????????????????????????PLMN ID */
        if (2 == pstMnMmaCrpnQryCnf->stMnMmaCrpnQry.ucPlmnType)
        {
            TAF_MEM_SET_S(aucPlmn, sizeof(aucPlmn), 0x00, sizeof(aucPlmn));
            if (pstMnMmaCrpnQryCnf->stMnMmaCrpnQry.usPlmnNameLen > TAF_MAX_AUTHDATA_PLMN_LEN)
            {
                TAF_MEM_CPY_S(aucPlmn,
                       sizeof(aucPlmn),
                       pstMnMmaCrpnQryCnf->stMnMmaCrpnQry.aucPlmnName,
                       TAF_MAX_AUTHDATA_PLMN_LEN);
            }
            else
            {
                TAF_MEM_CPY_S(aucPlmn,
                       sizeof(aucPlmn),
                       pstMnMmaCrpnQryCnf->stMnMmaCrpnQry.aucPlmnName,
                       pstMnMmaCrpnQryCnf->stMnMmaCrpnQry.usPlmnNameLen);
            }
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "\"%s\"",
                                               aucPlmn);
        }
        else
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "\"%X%X%X",
                                               (0x0f00 & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mcc) >> 8,
                                               (0x00f0 & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mcc) >> 4,
                                               (0x000f & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mcc));


            if (6 == pstMnMmaCrpnQryCnf->ucMaxMncLen)
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%X",
                                                   (0x0f00 & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mnc) >> 8);

            }
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%X%X\"",
                                               (0x00f0 & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mnc) >> 4,
                                               (0x000f & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mnc));
        }

        /* <short name> */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"%s\"",
                                           pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].aucOperatorNameShort);

        /* <long name> */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"%s\"",
                                           pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].aucOperatorNameLong);
    }

    gstAtSendData.usBufLen = usLength;

    At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
    usLength = 0;

    /* ??????????????CRPN????????????????????????C??????Plmn list???????????????????????????????? */
    if (TAF_PH_CRPN_PLMN_MAX_NUM == pstMnMmaCrpnQryCnf->ucTotalNum)
    {
        TAF_MEM_CPY_S(&stMnMmaCrpnQry, sizeof(stMnMmaCrpnQry), &pstMnMmaCrpnQryCnf->stMnMmaCrpnQry, sizeof(TAF_MMA_CRPN_QRY_PARA_STRU));
        stMnMmaCrpnQry.ucCurrIndex = pstMnMmaCrpnQryCnf->ucCurrIndex + pstMnMmaCrpnQryCnf->ucTotalNum;
        stMnMmaCrpnQry.ucQryNum    = TAF_PH_CRPN_PLMN_MAX_NUM;

        /* ????ID_TAF_MMA_CRPN_QRY_REQ??????MMA???? */
        if (VOS_TRUE == TAF_MMA_QryCrpnReq( WUEPS_PID_AT,
                                            gastAtClientTab[ucIndex].usClientId,
                                            0,
                                            &stMnMmaCrpnQry))
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CRPN_QUERY;
        }
        else
        {
            /* ????AT_STOP_TIMER_CMD_READY????AT??????????????READY???? */
            AT_STOP_TIMER_CMD_READY(ucIndex);
            gstAtSendData.usBufLen = 0;
            At_FormatResultData(ucIndex, AT_ERROR);
        }
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s",
                                               gaucAtCrLf);
        At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
        usLength = 0;

        /* ????AT_STOP_TIMER_CMD_READY????AT??????????????READY???? */
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = usLength;
        At_FormatResultData(ucIndex, ulResult);
    }

    return VOS_OK;

}


VOS_UINT32 AT_RcvMmaCbcQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_BATTERY_CAPACITY_QRY_CNF_STRU                  *pstCbcCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_UINT16                          usLength = 0;

    /* ?????? */
    pstCbcCnf           = (TAF_MMA_BATTERY_CAPACITY_QRY_CNF_STRU *)pMsg;
    ulResult            = AT_OK;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCbcCnf->stCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCbcQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCbcQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_CBC_SET */
    if (AT_CMD_CBC_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                      "%s: %d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      pstCbcCnf->stBatteryStatus.BatteryPowerStatus);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                      ",%d",
                                      pstCbcCnf->stBatteryStatus.BatteryRemains);


    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex,ulResult);
    return VOS_OK;

}


VOS_UINT32 AT_RcvMmaHsQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_HAND_SHAKE_QRY_CNF_STRU    *pstHsCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_UINT16                          usLength = 0;

    /* ?????? */
    pstHsCnf            = (TAF_MMA_HAND_SHAKE_QRY_CNF_STRU *)pMsg;
    ulResult            = AT_OK;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstHsCnf->stCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaHsQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaHsQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_HS_READ */
    if (AT_CMD_HS_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }


    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: %d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      *(TAF_UINT32*)pstHsCnf->aucBuf);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                      ",%d",pstHsCnf->aucBuf[4]);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                      ",%d",pstHsCnf->aucBuf[5]);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                      ",%d",pstHsCnf->aucBuf[6]);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                      ",%d",pstHsCnf->aucBuf[7]);

    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex,ulResult);
    return VOS_OK;

}



VOS_UINT32 AT_RcvMmaHdrCsqInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    MMA_TAF_HDR_CSQ_VALUE_IND_STRU     *pstHdrcsqInd;

    /* ?????????????? */
    ucIndex             = 0;
    pstHdrcsqInd        = (MMA_TAF_HDR_CSQ_VALUE_IND_STRU*)pMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstHdrcsqInd->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaCdmaCsqInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^HDRCSQ: %d,%d,%d%s",
                                                    gaucAtCrLf,
                                                    pstHdrcsqInd->sHdrRssi,
                                                    pstHdrcsqInd->sHdrSnr,
                                                    pstHdrcsqInd->sHdrEcio,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;

}


VOS_UINT32 AT_RcvMmaHdrCsqSetCnf(
    VOS_VOID                           *pMsg
)
{
    MMA_TAF_HDR_CSQ_SET_CNF_STRU            *pstHdrCsqCnf;
    VOS_UINT8                                ucIndex;
    VOS_UINT32                               ulResult;

    pstHdrCsqCnf = (MMA_TAF_HDR_CSQ_SET_CNF_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstHdrCsqCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaHdrCsqSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaHdrCsqSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstHdrCsqCnf->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaHdrCsqQryCnf(
    VOS_VOID                           *pMsg
)
{
    MMA_TAF_HDR_CSQ_QRY_SETTING_CNF_STRU *pstHdrCsqQueryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pstHdrCsqQueryCnf  = (MMA_TAF_HDR_CSQ_QRY_SETTING_CNF_STRU*)pMsg;
    usLength            = 0;
    ulResult            = AT_OK;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstHdrCsqQueryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaHdrCsqQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaHdrCsqQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_HDR_CSQ_QRY */
    if (AT_CMD_HDR_CSQ_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d,%d,%d,%d,%d,%d,%d,%d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     pstHdrCsqQueryCnf->stHdrCsq.enMode,
                                     pstHdrCsqQueryCnf->stHdrCsq.ucTimeInterval,
                                     pstHdrCsqQueryCnf->stHdrCsq.ucRssiThreshold,
                                     pstHdrCsqQueryCnf->stHdrCsq.ucSnrThreshold,
                                     pstHdrCsqQueryCnf->stHdrCsq.ucEcioThreshold,
                                     pstHdrCsqQueryCnf->sHdrRssi,
                                     pstHdrCsqQueryCnf->sHdrSnr,
                                     pstHdrCsqQueryCnf->sHdrEcio);

    gstAtSendData.usBufLen = usLength;

    At_FormatResultData(ucIndex, ulResult);

    /* ???????? */
    return VOS_OK;
}




VOS_UINT32 AT_RcvMmaImsSwitchSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_IMS_SWITCH_SET_CNF_STRU   *pstCnfMsg = VOS_NULL_PTR;
    VOS_UINT8                          ucIndex;
    VOS_UINT32                         ulResult;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    pstCnfMsg = (TAF_MMA_IMS_SWITCH_SET_CNF_STRU*)pMsg;

    /* ????ClientId????ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCnfMsg->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaImsSwitchSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ?????????????? */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaImsSwitchSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* ???????????????? */
    if (AT_CMD_LTE_IMS_SWITCH_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaImsSwitchSetCnf: WARNING:Not AT_CMD_LTE_IMS_SWITCH_SET!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstCnfMsg->enResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstCnfMsg->enErrorCause);
    }

    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaImsSwitchQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_IMS_SWITCH_QRY_CNF_STRU    *pstSwitchQryCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????? */
    pstSwitchQryCnf     = (TAF_MMA_IMS_SWITCH_QRY_CNF_STRU *)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstSwitchQryCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaImsSwitchQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaImsSwitchQryCnf : AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_IMS_SWITCH_QRY */
    if (AT_CMD_LTE_IMS_SWITCH_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaImsSwitchQryCnf: WARNING:Not AT_CMD_LTE_IMS_SWITCH_QRY!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstSwitchQryCnf->enResult)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstSwitchQryCnf->enLteImsSwitch);
        ulResult = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulResult = At_ChgTafErrorCode(ucIndex, pstSwitchQryCnf->enErrorCause);
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}


VOS_UINT32 AT_RcvMmaVoiceDomainSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_VOICE_DOMAIN_SET_CNF_STRU  *pstCnfMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    ucIndex   = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    pstCnfMsg = (TAF_MMA_VOICE_DOMAIN_SET_CNF_STRU *)pMsg;

    /* ????ClientId????ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCnfMsg->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaVoiceDomainSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ?????????????? */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaVoiceDomainSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* ???????????????? */
    if (AT_CMD_VOICE_DOMAIN_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaVoiceDomainSetCnf: WARNING:Not AT_CMD_VOICE_DOMAIN_SET!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstCnfMsg->enResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstCnfMsg->enErrorCause);
    }

    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_VoiceDomainTransToOutputValue(
    TAF_MMA_VOICE_DOMAIN_ENUM_UINT32    enVoiceDoman,
    VOS_UINT32                         *pulValue
)
{
    VOS_UINT32                          ulRst;

    ulRst = VOS_TRUE;

    switch (enVoiceDoman)
    {
        case TAF_MMA_VOICE_DOMAIN_CS_ONLY:
            *pulValue = AT_VOICE_DOMAIN_TYPE_CS_ONLY;
            break;

        case TAF_MMA_VOICE_DOMAIN_IMS_PS_ONLY:
            *pulValue = AT_VOICE_DOMAIN_TYPE_IMS_PS_ONLY;
            break;

        case TAF_MMA_VOICE_DOMAIN_CS_PREFERRED:
            *pulValue = AT_VOICE_DOMAIN_TYPE_CS_PREFERRED;
            break;

        case TAF_MMA_VOICE_DOMAIN_IMS_PS_PREFERRED:
            *pulValue = AT_VOICE_DOMAIN_TYPE_IMS_PS_PREFERRED;
            break;

        default:
            *pulValue = AT_VOICE_DOMAIN_TYPE_BUTT;
            ulRst = VOS_FALSE;
            break;
    }

    return ulRst;

}


VOS_UINT32 AT_RcvMmaVoiceDomainQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_VOICE_DOMAIN_QRY_CNF_STRU  *pstDomainQryCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulValue;
    VOS_UINT32                          ulResult;

    /* ?????? */
    ulValue             = 0;
    pstDomainQryCnf     = (TAF_MMA_VOICE_DOMAIN_QRY_CNF_STRU *)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDomainQryCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaVoiceDomainQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaVoiceDomainQryCnf : AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_VOICE_DOMAIN_QRY */
    if (AT_CMD_VOICE_DOMAIN_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaVoiceDomainQryCnf: WARNING:Not AT_CMD_VOICE_DOMAIN_QRY!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_TRUE != AT_VoiceDomainTransToOutputValue(pstDomainQryCnf->enVoiceDomain, &ulValue))
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
        gstAtSendData.usBufLen = 0;
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       "%s: %d",
                                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                       ulValue);
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaImsDomainCfgSetCnf(VOS_VOID * pMsg)
{
    TAF_MMA_IMS_DOMAIN_CFG_SET_CNF_STRU     *pstDomainCfgSetCnf = VOS_NULL_PTR;
    VOS_UINT32                               ulResult;
    VOS_UINT8                                ucIndex;

    pstDomainCfgSetCnf = (TAF_MMA_IMS_DOMAIN_CFG_SET_CNF_STRU *)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDomainCfgSetCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaImsDomainCfgSetCnf :WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ?????????????? */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaImsDomainCfgSetCnf : AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_IMSDOMAIN_SET */
    if (AT_CMD_IMSDOMAINCFG_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaImsDomainCfgSetCnf : WARNING:Not AT_CMD_IMSDOMAINCFG_SET!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_IMS_DOMAIN_CFG_RESULT_SUCCESS == pstDomainCfgSetCnf->enImsDomainCfgResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaImsDomainCfgQryCnf(VOS_VOID *pMsg)
{
    TAF_MMA_IMS_DOMAIN_CFG_QRY_CNF_STRU     *pstDomainCfgQryCnf = VOS_NULL_PTR;
    VOS_UINT8                                ucIndex;

    pstDomainCfgQryCnf = (TAF_MMA_IMS_DOMAIN_CFG_QRY_CNF_STRU *)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDomainCfgQryCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaImsDomainCfgQryCnf :WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaImsDomainCfgQryCnf : AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_IMSDOMAINCFG_QRY */
    if (AT_CMD_IMSDOMAINCFG_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaImsDomainCfgQryCnf : WARNING:Not AT_CMD_IMSDOMAIN_QRY!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstDomainCfgQryCnf->enImsDomainCfgType);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaRoamImsSupportSetCnf(VOS_VOID * pMsg)
{
    TAF_MMA_ROAM_IMS_SUPPORT_SET_CNF_STRU   *pstRoamImsSupportSetCnf = VOS_NULL_PTR;
    VOS_UINT32                               ulResult;
    VOS_UINT8                                ucIndex;

    pstRoamImsSupportSetCnf = (TAF_MMA_ROAM_IMS_SUPPORT_SET_CNF_STRU *)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRoamImsSupportSetCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaRoamImsSupportSetCnf :WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ?????????????? */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaRoamImsSupportSetCnf : AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_ROAM_IMS_SET */
    if (AT_CMD_ROAM_IMS_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaRoamImsSupportSetCnf : WARNING:Not AT_CMD_ROAM_IMS_SET!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_ROAM_IMS_SUPPORT_RESULT_SUCCESS == pstRoamImsSupportSetCnf->enRoamImsSupportResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}



VOS_UINT32 AT_RcvMtaSetFemctrlCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_SET_FEMCTRL_CNF_STRU        *pstSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????? */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf    = (MTA_AT_SET_FEMCTRL_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex      = 0;
    ulResult     = AT_ERROR;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetFemctrlCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetFemctrlCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_FEMCTRL_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetFemctrlCnf : Current Option is not AT_CMD_FEMCTRL_SET.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ?????????????? */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR == pstSetCnf->enResult)
    {
        ulResult = AT_OK;
    }

    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


VOS_UINT32 AT_RcvMma1xChanSetCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CFREQ_LOCK_SET_CNF_STRU    *pstCFreqLockSetCnf;
    VOS_UINT32                          ulResult;

    /* ?????????????? */
    ucIndex             = 0;
    pstCFreqLockSetCnf  = (TAF_MMA_CFREQ_LOCK_SET_CNF_STRU*)pstMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCFreqLockSetCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMma1xChanSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMma1xChanSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_1XCHAN_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMma1xChanSetCnf : Current Option is not AT_CMD_CFREQLOCK_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^1XCHAN???????? */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstCFreqLockSetCnf->ulRslt)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMma1xChanQueryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_1XCHAN_QUERY_CNF_STRU      *pst1xChanQueryCnf;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    VOS_INT16                           sInvalidChan;

    /* ?????? */
    pst1xChanQueryCnf   = (TAF_MMA_1XCHAN_QUERY_CNF_STRU*)pstMsg;
    usLength            = 0;
    sInvalidChan        = -1;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pst1xChanQueryCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMma1xChanQueryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMma1xChanQueryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_CVER_QRY */
    if (AT_CMD_1XCHAN_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMma1xChanQueryCnf : Current Option is not AT_CMD_1XCHAN_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_OK == pst1xChanQueryCnf->ulRslt)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     pst1xChanQueryCnf->usChannel);

        gstAtSendData.usBufLen = usLength;
    }
    else
    {
        /* ??????????????^1XCHAN: BUTT */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     sInvalidChan);

        gstAtSendData.usBufLen = usLength;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaCVerQueryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_CVER_QUERY_CNF_STRU        *pstCVerQueryCnf;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    TAF_MMA_1X_CAS_P_REV_ENUM_UINT8     enInvalidVersion;

    /* ?????? */
    pstCVerQueryCnf     = (TAF_MMA_CVER_QUERY_CNF_STRU*)pstMsg;
    usLength            = 0;
    enInvalidVersion    = TAF_MMA_1X_CAS_P_REV_ENUM_BUTT;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCVerQueryCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCVerQueryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCVerQueryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_CVER_QRY */
    if (AT_CMD_CVER_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaCVerQueryCnf : Current Option is not AT_CMD_CVER_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_OK == pstCVerQueryCnf->ulRslt)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     pstCVerQueryCnf->enPrevInUse);

        gstAtSendData.usBufLen = usLength;
    }
    else
    {
        /* ??????????????^CVER: BUTT */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     enInvalidVersion);

        gstAtSendData.usBufLen = usLength;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaStateQueryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_STATE_QUERY_CNF_STRU       *pstStQryCnf;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    VOS_INT8                            cInvalidSta;

    /* ?????? */
    pstStQryCnf     = (TAF_MMA_STATE_QUERY_CNF_STRU*)pstMsg;
    usLength        = 0;
    cInvalidSta     = -1;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstStQryCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaStateQueryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaStateQueryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_CVER_QRY */
    if (AT_CMD_GETSTA_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaStateQueryCnf : Current Option is not AT_CMD_GETST_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_OK == pstStQryCnf->ulRslt)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d,%d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     pstStQryCnf->stHandsetSta.ucCasState,
                                     pstStQryCnf->stHandsetSta.ucCasSubSta);

        gstAtSendData.usBufLen = usLength;
    }
    else
    {
        /* ??????????????^GETSTA: BUTT */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d,%d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     cInvalidSta,
                                     cInvalidSta);

        gstAtSendData.usBufLen = usLength;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaCHverQueryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_CHIGHVER_QUERY_CNF_STRU    *pstStaQryCnf;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    TAF_MMA_1X_CAS_P_REV_ENUM_UINT8     enInvalidVer;

    /* ?????? */
    pstStaQryCnf     = (TAF_MMA_CHIGHVER_QUERY_CNF_STRU*)pstMsg;
    usLength         = 0;
    enInvalidVer     = TAF_MMA_1X_CAS_P_REV_ENUM_BUTT;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstStaQryCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCHverQueryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCHverQueryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*??????????????????????AT_CMD_CHIGHVER_QRY */
    if (AT_CMD_CHIGHVER_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaCHverQueryCnf : Current Option is not AT_CMD_CHIGHVER_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_OK == pstStaQryCnf->ulRslt)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     pstStaQryCnf->enHighRev);

        gstAtSendData.usBufLen = usLength;
    }
    else
    {
        /* ??????????????^CHIGHVER: BUTT */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     enInvalidVer);

        gstAtSendData.usBufLen = usLength;
    }

    /* ???????? */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}



VOS_UINT32 AT_RcvMmaHplmnQryCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_HOME_PLMN_QRY_CNF_STRU     *pstHplmnQryCnf = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT32                          i;
    VOS_UINT8                           aucImsiString[NAS_IMSI_STR_LEN + 1];

    /* ?????????????? */
    pstHplmnQryCnf = (TAF_MMA_HOME_PLMN_QRY_CNF_STRU *)pstMsg;
    usLength       = 0;

    /* index??????????????AT_RcvMmaEHplmnInfoQryCnf?? */

    /* ????AT??????READY???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ((0 == pstHplmnQryCnf->stEHplmnInfo.ulEHplmnNum)
     || (TAF_ERR_NO_ERROR != pstHplmnQryCnf->enErrorCause))
    {
        AT_WARN_LOG("AT_RcvMmaHplmnQryCnf : EHPLMN num error.");

        /* ?????????????????????????? */
        gstAtSendData.usBufLen = 0;

        At_FormatResultData(ucIndex, At_ChgTafErrorCode(ucIndex, pstHplmnQryCnf->enErrorCause));

        return VOS_ERR;
    }

    /* ??IMSI???????????????? */
    AT_ConvertImsiDigit2String(pstHplmnQryCnf->stEHplmnInfo.aucImsi, aucImsiString);

    /* ??????????????????AT^HPLMN */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                 (VOS_CHAR *)pgucAtSndCodeAddr,
                                 (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                 "%s: %s,%d,%d,",
                                 g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                 aucImsiString,
                                 pstHplmnQryCnf->stEHplmnInfo.ucHplmnMncLen,
                                 pstHplmnQryCnf->stEHplmnInfo.ulEHplmnNum);

    for ( i = 0; i < (VOS_UINT8)(pstHplmnQryCnf->stEHplmnInfo.ulEHplmnNum - 1); i++ )
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                   "%x%x%x",
                                   (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mcc & 0x0f00)>>8,
                                   (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mcc & 0xf0)>>4,
                                   (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mcc & 0x0f));

        if (0x0f00 == (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0x0f00))
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%x%x,",
                                               (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0xf0)>>4,
                                               (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0x0f));
        }
        else
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%x%x%x,",
                                               (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0x0f00)>>8,
                                               (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0xf0)>>4,
                                               (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0x0f));
        }
     }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                   "%x%x%x",
                                   (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mcc & 0x0f00)>>8,
                                   (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mcc & 0xf0)>>4,
                                   (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mcc & 0x0f));

    if (0x0f00 == (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0x0f00))
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%x%x",
                                           (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0xf0)>>4,
                                           (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0x0f));
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%x%x%x",
                                           (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0x0f00)>>8,
                                           (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0xf0)>>4,
                                           (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0x0f));
    }

    gstAtSendData.usBufLen = usLength;

    /* ???????? */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaDplmnQryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_DPLMN_QRY_CNF_STRU         *pstDplmnQryCnf = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucTempVersion[NAS_VERSION_LEN + 1];

    /* ??????????????*/
    pstDplmnQryCnf  = (TAF_MMA_DPLMN_QRY_CNF_STRU *)pstMsg;
    usLength        = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDplmnQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaDplmnQryCnf At_ClientIdToUserId FAILURE");
        return VOS_ERR;
    }

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG("AT_RcvMmaDplmnQryCnf: Get modem id fail.");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaDplmnQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_DPLMNLIST_QRY */
    if (AT_CMD_DPLMNLIST_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaDplmnQryCnf : Current Option is not AT_CMD_DPLMNLIST_READ.");
        return VOS_ERR;
    }

    /* ????AT??????READY???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??version???????????????? */
    TAF_MEM_CPY_S(aucTempVersion, sizeof(aucTempVersion), pstDplmnQryCnf->aucVersionId, NAS_VERSION_LEN);

    /* ?????????????? */
    aucTempVersion[NAS_VERSION_LEN]    = '\0';

    /* ??????????????????^DPLMN?????? */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                 (VOS_CHAR *)pgucAtSndCodeAddr,
                                 (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                 "%s: %s",
                                 g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                 aucTempVersion);

    gstAtSendData.usBufLen = usLength;

    /* ???????? */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaDplmnSetCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_DPLMN_SET_CNF_STRU         *pstDplmnSetCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulRetVal;

    /* ?????????????? */
    pstDplmnSetCnf = (TAF_MMA_DPLMN_SET_CNF_STRU *)pstMsg;
    ulRetVal       = VOS_ERR;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDplmnSetCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaDplmnSetCnf At_ClientIdToUserId FAILURE");
        return ulRetVal;
    }

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG("AT_RcvMmaDplmnSetCnf: Get modem id fail.");
        return ulRetVal;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaDplmnSetCnf: AT_BROADCAST_INDEX.");
        return ulRetVal;
    }

    /* ??????????????????????AT_CMD_DPLMNLIST_SET */
    if (AT_CMD_DPLMNLIST_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaDplmnSetCnf : Current Option is not AT_CMD_DPLMNLIST_SET.");
        return ulRetVal;
    }

    /* ????AT??????READY???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_OK == pstDplmnSetCnf->ulRslt)
    {
        ulResult = AT_OK;
        ulRetVal = VOS_OK;
    }
    else
    {
        ulResult = AT_CME_UNKNOWN;
    }

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return ulRetVal;
}



VOS_UINT32 AT_RcvMmaBorderInfoSetCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_BORDER_INFO_SET_CNF_STRU   *pstSetCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulRetVal;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucIndex;

    /* ?????????????? */
    pstSetCnf = (TAF_MMA_BORDER_INFO_SET_CNF_STRU *)pstMsg;
    ulRetVal  = VOS_ERR;
    enModemId = MODEM_ID_BUTT;
    ucIndex   = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstSetCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaBorderInfoSetCnf At_ClientIdToUserId FAILURE");
        return ulRetVal;
    }

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG("AT_RcvMmaBorderInfoSetCnf: Get modem id fail.");
        return ulRetVal;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaBorderInfoSetCnf: AT_BROADCAST_INDEX.");
        return ulRetVal;
    }

    /* ??????????????????????AT_CMD_BORDERINFO_SET */
    if (AT_CMD_BORDERINFO_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaBorderInfoSetCnf : Current Option is not AT_CMD_BORDERINFO_SET.");
        return ulRetVal;
    }

    /* ????AT??????READY???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_OK == pstSetCnf->ulRslt)
    {
        ulResult = AT_OK;
        ulRetVal = VOS_OK;
    }
    else
    {
        ulResult = AT_CME_UNKNOWN;
    }

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return ulRetVal;
}


VOS_UINT32 AT_RcvMmaBorderInfoQryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_BORDER_INFO_QRY_CNF_STRU   *pstQryCnf = VOS_NULL_PTR;
    VOS_UINT8                           aucTempVersion[NAS_VERSION_LEN + 1];
    VOS_UINT16                          usLength;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucIndex;

    /* ??????????????*/
    pstQryCnf  = (TAF_MMA_BORDER_INFO_QRY_CNF_STRU *)pstMsg;
    usLength   = 0;
    enModemId  = MODEM_ID_BUTT;
    ucIndex    = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaBorderInfoQryCnf At_ClientIdToUserId FAILURE");
        return VOS_ERR;
    }

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG("AT_RcvMmaBorderInfoQryCnf: Get modem id fail.");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaBorderInfoQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_BORDERINFO_QRY */
    if (AT_CMD_BORDERINFO_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaBorderInfoQryCnf : Current Option is not AT_CMD_BORDERINFO_QRY.");
        return VOS_ERR;
    }

    /* ????AT??????READY???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??version???????????????? */
    TAF_MEM_CPY_S(aucTempVersion, sizeof(aucTempVersion), pstQryCnf->aucVersionId, NAS_VERSION_LEN);

    /* ?????????????? */
    aucTempVersion[NAS_VERSION_LEN]    = '\0';

    /* ??????????????????^BORDERINFO?????? */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                 (VOS_CHAR *)pgucAtSndCodeAddr,
                                 (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                 "%s: %s",
                                 g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                 aucTempVersion);

    gstAtSendData.usBufLen = usLength;

    /* ???????? */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaSetFrCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg   = VOS_NULL_PTR;
    MTA_AT_SET_FR_CNF_STRU             *pstSetFrCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????? */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetFrCnf  = (MTA_AT_SET_FR_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex      = 0;
    ulResult     = AT_ERROR;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetFrCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetFrCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_FRSTATUS_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetFrCnf : Current Option is not AT_CMD_FRSTATUS_SET.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ?????????????? */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR == pstSetFrCnf->enRslt)
    {
        ulResult = AT_OK;
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaSib16TimeUpdateInd(
    VOS_VOID                           *pstMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg          = VOS_NULL_PTR;
    MTA_AT_SIB16_TIME_UPDATE_STRU      *pstSib16TimeUpdate = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;
    VOS_UINT16                          usLengthTemp;

    /* ?????????????? */
    pstRcvMsg           = (AT_MTA_MSG_STRU *)pstMsg;
    pstSib16TimeUpdate  = (MTA_AT_SIB16_TIME_UPDATE_STRU *)pstRcvMsg->aucContent;
    ucIndex             = 0;
    usLength            = 0;
    usLengthTemp        = 0;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaSib16TimeUpdateInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* "^SIB16TIME: */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s\"",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_SIB16TIME].pucText);

    /* Time Type */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d, ", pstSib16TimeUpdate->enTimeType);

    /* ???????? */
    switch(pstSib16TimeUpdate->enTimeType)
    {
        case MTA_AT_LOCAL_TIME:
            /* Local Time */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "Local Time: ");
            usLengthTemp = usLength;

            AT_FmtTimeStru(&pstSib16TimeUpdate->stLocalTime, &usLength, usLengthTemp);

            break;

        case MTA_AT_GPS_TIME:
            /* Gps Time */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "Gps Time: ");
            usLengthTemp = usLength;

            AT_FmtTimeStru(&pstSib16TimeUpdate->stGpsTime, &usLength, usLengthTemp);

            break;

        case MTA_AT_LOCAL_GPS_TIME:
            /* Local Gps Time */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "Local Time: ");
            usLengthTemp = usLength;

            AT_FmtTimeStru(&pstSib16TimeUpdate->stLocalTime, &usLength, usLengthTemp);

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "Gps Time: ");
            usLengthTemp = usLength;

            AT_FmtTimeStru(&pstSib16TimeUpdate->stGpsTime, &usLength, usLengthTemp);

            break;

        default:
            break;
    }

    /* ?????????????? */
    /* Day Light Saving Ind */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d\"%s", pstSib16TimeUpdate->enDayLightSavingInd, gaucAtCrLf);

    /* ???????? */
    gstAtSendData.usBufLen = usLength;
    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;

}


/*lint -save -e838 -specific(-e838)*/
/*lint -save -e826 -specific(-e826)*/
VOS_UINT32 AT_RcvMtaAccessStratumRelInd(
    VOS_VOID                           *pstMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg              = VOS_NULL_PTR;
    MTA_AT_ACCESS_STRATUM_REL_IND_STRU *pstAccessStratumRelInd = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    /* ?????????????? */
    pstRcvMsg              = (AT_MTA_MSG_STRU *)pstMsg;
    pstAccessStratumRelInd = (MTA_AT_ACCESS_STRATUM_REL_IND_STRU *)pstRcvMsg->aucContent;
    ucIndex                = 0;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaAccessStratumRelInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    switch(pstAccessStratumRelInd->enAccessStratumRel)
    {
        case MTA_AT_ACCESS_STRATUM_REL8:
            g_stReleaseInfo.enAccessStratumRel = AT_ACCESS_STRATUM_REL8;
            break;

        case MTA_AT_ACCESS_STRATUM_REL9:
            g_stReleaseInfo.enAccessStratumRel = AT_ACCESS_STRATUM_REL9;
            break;

        case MTA_AT_ACCESS_STRATUM_REL10:
            g_stReleaseInfo.enAccessStratumRel = AT_ACCESS_STRATUM_REL10;
            break;

        case MTA_AT_ACCESS_STRATUM_REL11:
            g_stReleaseInfo.enAccessStratumRel = AT_ACCESS_STRATUM_REL11;
            break;

        case MTA_AT_ACCESS_STRATUM_REL12:
            g_stReleaseInfo.enAccessStratumRel = AT_ACCESS_STRATUM_REL12;
            break;

        case MTA_AT_ACCESS_STRATUM_REL13:
            g_stReleaseInfo.enAccessStratumRel = AT_ACCESS_STRATUM_REL13;
            break;

        case MTA_AT_ACCESS_STRATUM_REL_SPARE2:
            g_stReleaseInfo.enAccessStratumRel = AT_ACCESS_STRATUM_REL_SPARE2;
            break;

        case MTA_AT_ACCESS_STRATUM_REL_SPARE1:
            g_stReleaseInfo.enAccessStratumRel = AT_ACCESS_STRATUM_REL_SPARE1;
            break;

        default:
            g_stReleaseInfo.enAccessStratumRel = AT_ACCESS_STRATUM_REL8;
            AT_NORM_LOG("AT_RcvMtaAccessStratumRelInd: Wrong Release Number!");
            break;
    }

    return VOS_OK;

}
/*lint -restore*/
/*lint -restore*/

/*lint -save -e838 -specific(-e838)*/
/*lint -save -e826 -specific(-e826)*/

VOS_UINT32 AT_RcvMtaRsInfoQryCnf(
    VOS_VOID                           *pstMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg       = VOS_NULL_PTR;
    MTA_AT_RS_INFO_QRY_CNF_STRU        *pstRsInfoQryCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pstRcvMsg           = (AT_MTA_MSG_STRU *)pstMsg;
    pstRsInfoQryCnf     = (MTA_AT_RS_INFO_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex             = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaRsInfoQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaRsInfoQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT??????????+RSRP/+RSRQ???????? */
    if ( (AT_CMD_RSRP_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
      && (AT_CMD_RSRQ_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt) )
    {
        AT_WARN_LOG("AT_RcvMtaRsInfoQryCnf : Current Option is not AT_CMD_RSRP_QRY or AT_CMD_RSRQ_QRY.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (AT_MTA_RSRP_TYPE == pstRsInfoQryCnf->stRsInfoRslt.enRsInfoType)
    {
        AT_FormatRsrp(pstRsInfoQryCnf);
    }
    else
    {
        AT_FormatRsrq(pstRsInfoQryCnf);
    }

    /* ???????? */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}
/*lint -restore*/
/*lint -restore*/


VOS_UINT32 AT_RcvMtaClearHistoryFreqCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg   = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU             *pstSetCnf   = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????? */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf    = (MTA_AT_RESULT_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex      = 0;
    ulResult     = AT_ERROR;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaClearHistoryFreqCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaClearHistoryFreqCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_CLEAR_HISTORY_FREQ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaClearHistoryFreqCnf : Current Option is not AT_CMD_CLEAR_HISTORY_FREQ.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ?????????????? */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR == pstSetCnf->enResult)
    {
        ulResult = AT_OK;
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}



VOS_UINT32 AT_RcvMmaSrchedPlmnInfoInd(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_SRCHED_PLMN_INFO_IND_STRU  *pstSrchedPlmnInfo = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          i;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    usLength    = 0;
    enModemId   = MODEM_ID_0;
    pstSrchedPlmnInfo  = (TAF_MMA_SRCHED_PLMN_INFO_IND_STRU*)pMsg;

    if (AT_FAILURE == At_ClientIdToUserId(pstSrchedPlmnInfo->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSrchedPlmnInfoInd At_ClientIdToUserId FAILURE");
        return VOS_ERR;
    }

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_RcvMmaSrchedPlmnInfoInd: Get modem id fail.");
        return VOS_ERR;
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_SRCHEDPLMNINFO].pucText);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,%d",
                                       pstSrchedPlmnInfo->enRat,
                                       pstSrchedPlmnInfo->ulLaiNum);

    for (i = 0; i < pstSrchedPlmnInfo->ulLaiNum; i++)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%x%x%x",
                                           (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mcc & 0x0f00) >> 8,
                                           (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mcc & 0xf0) >> 4,
                                           (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mcc & 0x0f));

        if (0x0f00 == (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mnc & 0x0f00))
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%x%x,",
                                               (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mnc & 0xf0) >> 4,
                                               (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mnc & 0x0f));
        }
        else
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%x%x%x,",
                                               (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mnc & 0x0f00) >> 8,
                                               (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mnc & 0xf0) >> 4,
                                               (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mnc & 0x0f));
        }

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%d",
                                           pstSrchedPlmnInfo->astLai[i].usLac);
    }


    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s",
                                       gaucAtCrLf);

    gstAtSendData.usBufLen = usLength;

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaTransModeQryCnf(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg               = VOS_NULL_PTR;
    MTA_AT_TRANSMODE_QRY_CNF_STRU          *pstMtaAtQryTransModeCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* ?????? */
    pstRcvMsg                = (AT_MTA_MSG_STRU *)pMsg;
    pstMtaAtQryTransModeCnf  = (MTA_AT_TRANSMODE_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult                 = AT_OK;
    ucIndex                  = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaTransModeQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaTransModeQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_TRANSMODE_READ!= gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaTransModeQryCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = 0;
    if (MTA_AT_RESULT_NO_ERROR != pstMtaAtQryTransModeCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       "%s: %d",
                                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                       pstMtaAtQryTransModeCnf->ucTransMode);
    }
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaUECenterQryCnf(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg               = VOS_NULL_PTR;
    MTA_AT_QRY_UE_CENTER_CNF_STRU          *pstMtaAtQryUECenterCnf  = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* ?????? */
    pstRcvMsg                = (AT_MTA_MSG_STRU *)pMsg;
    pstMtaAtQryUECenterCnf   = (MTA_AT_QRY_UE_CENTER_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult                 = AT_OK;
    ucIndex                  = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaUECenterQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaUECenterQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_UE_CENTER_QRY!= gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaUECenterQryCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = 0;
    if (MTA_AT_RESULT_NO_ERROR != pstMtaAtQryUECenterCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       "%s: %d",
                                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                       pstMtaAtQryUECenterCnf->enUeCenter);
    }
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaUECenterSetCnf(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg               = VOS_NULL_PTR;
    MTA_AT_SET_UE_CENTER_CNF_STRU          *pstMtaAtSetUECenterCnf  = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* ?????? */
    pstRcvMsg                = (AT_MTA_MSG_STRU *)pMsg;
    pstMtaAtSetUECenterCnf   = (MTA_AT_SET_UE_CENTER_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult                 = AT_OK;
    ucIndex                  = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaUECenterQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaUECenterQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_UE_CENTER_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaUECenterQryCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = 0;
    if (MTA_AT_RESULT_NO_ERROR != pstMtaAtSetUECenterCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


VOS_UINT32  At_MipiRdCnfProc( HPA_AT_MIPI_RD_CNF_STRU *pstMsg )
{
    VOS_UINT32                          usRslt;
    VOS_UINT32                          usData;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* ?????????????? */
    usLength        = 0;

    /*??????????????????????*/
    ucIndex         = g_stAtDevCmdCtrl.ucIndex;

    if (AT_CMD_MIPI_RD != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
          return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (AT_HPA_RSLT_FAIL == pstMsg->ulResult)
    {
        AT_INFO_LOG("At_MipiRdCnfProc: read mipi err");
        usRslt = AT_ERROR;
    }
    else
    {
        usRslt      = AT_OK;
        usData      = pstMsg->ulValue;

        usLength    = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              "%s:%d",
                                              g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                              usData);
    }
    gstAtSendData.usBufLen  = usLength;
    At_FormatResultData(ucIndex, usRslt);
    return VOS_OK;
}


VOS_UINT32  At_MipiWrCnfProc( HPA_AT_MIPI_WR_CNF_STRU       *pstMsg )
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;

    /*??????????????????????*/
    ucIndex = g_stAtDevCmdCtrl.ucIndex;

     if ( AT_CMD_MIPI_WR != gastAtClientTab[ucIndex].CmdCurrentOpt )
     {
          return VOS_ERR;
     }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (AT_HPA_RSLT_FAIL == pstMsg->usErrFlg)
    {
        AT_INFO_LOG("At_MipiWrCnfProc: set MipiCfg err");
        ulRslt  = AT_ERROR;
    }
    else
    {
        ulRslt  = AT_OK;
    }

    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}


VOS_UINT32  At_SsiWrCnfProc( HPA_AT_SSI_WR_CNF_STRU         *pstMsg )
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;

    /*??????????????????????*/
    ucIndex     = g_stAtDevCmdCtrl.ucIndex;

    if (AT_CMD_SSI_WR != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
          return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);


    if (AT_HPA_RSLT_FAIL == pstMsg->usErrFlg)
    {
        AT_INFO_LOG("At_SsiWrCnfProc: set rfcfg err");
        ulRslt = AT_ERROR;
    }
    else
    {
        ulRslt  = AT_OK;
    }

    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}


VOS_UINT32  At_SsiRdCnfProc( HPA_AT_SSI_RD_CNF_STRU          *pstMsg )
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulData;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* ?????????????? */
    usLength        = 0;

    /*??????????????????????*/
    ucIndex         = g_stAtDevCmdCtrl.ucIndex;

    if ( AT_CMD_SSI_RD != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
          return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (AT_HPA_RSLT_FAIL == pstMsg->ulResult)
    {
        AT_INFO_LOG("At_MipiRdCnfProc: read SSI err");
        ulRslt = AT_ERROR;
    }
    else
    {
        ulRslt      = AT_OK;
        ulData      = pstMsg->ulValue;

        usLength    = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            "%s:%d",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            ulData );
    }

    gstAtSendData.usBufLen  = usLength;
    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}


VOS_UINT32  At_PdmCtrlCnfProc( HPA_AT_PDM_CTRL_CNF_STRU *pstMsg )
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;

    /*??????????????????????*/
    ucIndex         = g_stAtDevCmdCtrl.ucIndex;

    if ( AT_CMD_PDM_CTRL != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
          return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (AT_HPA_RSLT_FAIL == pstMsg->ulResult)
    {
        AT_INFO_LOG("At_PdmCtrlCnfProc: read PdmCtrl err");
        ulRslt      = AT_ERROR;
    }
    else
    {
        ulRslt      = AT_OK;
    }

    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}



VOS_UINT32 AT_RcvMmaInitLocInfoInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_INIT_LOC_INFO_IND_STRU     *pstInitLocInfoInd;

    /* ?????????????? */
    ucIndex             = 0;
    pstInitLocInfoInd   = (TAF_MMA_INIT_LOC_INFO_IND_STRU *)pMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstInitLocInfoInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaInitLocInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^INITLOCINFO: %x%x%x,%d%s",
                                                    gaucAtCrLf,
                                                    (pstInitLocInfoInd->ulMcc & 0x0f00)>>8,
                                                    (pstInitLocInfoInd->ulMcc & 0x00f0)>>4,
                                                    (pstInitLocInfoInd->ulMcc & 0x000f),
                                                    pstInitLocInfoInd->lSid,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaEflociInfoSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_EFLOCIINFO_SET_CNF_STRU    *pstEflociInfoSetCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstEflociInfoSetCnf = (TAF_MMA_EFLOCIINFO_SET_CNF_STRU *)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEflociInfoSetCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaEflociInfoSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaEflociInfoSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_EFLOCIINFO_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaEflociInfoSetCnf : Current Option is not AT_CMD_EFLOCIINFO_SET.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ?????????????? */
    gstAtSendData.usBufLen = 0;

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstEflociInfoSetCnf->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaEflociInfoQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_EFLOCIINFO_QRY_CNF_STRU    *pstEfloiinfoQryCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    pstEfloiinfoQryCnf = (TAF_MMA_EFLOCIINFO_QRY_CNF_STRU *)pMsg;
    usLength = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEfloiinfoQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaEflociInfoQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaEflociInfoQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_EFLOCIINFO_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaEflociInfoQryCnf : Current Option is not AT_CMD_EFLOCIINFO_QRY.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ????????????????ERROR */
    if (TAF_MMA_APP_OPER_RESULT_SUCCESS != pstEfloiinfoQryCnf->enRslt)
    {
        ulResult = AT_ERROR;

        At_FormatResultData(ucIndex, ulResult);
        return VOS_OK;
    }

    /* <tmsi> */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                 (VOS_CHAR *)pgucAtSndCodeAddr,
                                 (VOS_CHAR *)pgucAtSndCodeAddr,
                                 "%s: 0x%08x",
                                 g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                 (VOS_UINT32)pstEfloiinfoQryCnf->stEflociInfo.ulTmsi);

    /* <plmn> */
    if (0xfff == pstEfloiinfoQryCnf->stEflociInfo.stPlmnId.Mcc
     && 0xfff == pstEfloiinfoQryCnf->stEflociInfo.stPlmnId.Mnc)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",\"ffffff\"");
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"%x%x%x",
                                           (0x0f00 & pstEfloiinfoQryCnf->stEflociInfo.stPlmnId.Mcc) >> 8,
                                           (0x00f0 & pstEfloiinfoQryCnf->stEflociInfo.stPlmnId.Mcc) >> 4,
                                           (0x000f & pstEfloiinfoQryCnf->stEflociInfo.stPlmnId.Mcc));

        if (0x0F != ((0x0f00 & pstEfloiinfoQryCnf->stEflociInfo.stPlmnId.Mnc) >> 8))
        {
            usLength +=(VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%x",
                                          (0x0f00 & pstEfloiinfoQryCnf->stEflociInfo.stPlmnId.Mnc) >> 8);
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%x%x\"",
                                           (0x00f0 & pstEfloiinfoQryCnf->stEflociInfo.stPlmnId.Mnc) >> 4,
                                           (0x000f & pstEfloiinfoQryCnf->stEflociInfo.stPlmnId.Mnc));
    }
    /* <lac> */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                   ",0x%04x",
                                   pstEfloiinfoQryCnf->stEflociInfo.usLac);

    /* <location_update_status> */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                   ",%d",
                                   pstEfloiinfoQryCnf->stEflociInfo.ucLocationUpdateStatus);

    /* <rfu> */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                   ",0x%02x",
                                   pstEfloiinfoQryCnf->stEflociInfo.ucRfu);

    gstAtSendData.usBufLen = usLength;

    /* ???????? */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaPsEflociInfoSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_EFPSLOCIINFO_SET_CNF_STRU  *pstPsEflociInfoSetCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstPsEflociInfoSetCnf = (TAF_MMA_EFPSLOCIINFO_SET_CNF_STRU *)pMsg;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPsEflociInfoSetCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPsEflociInfoSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPsEflociInfoSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_EFPSLOCIINFO_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPsEflociInfoSetCnf : Current Option is not AT_CMD_EFPSLOCIINFO_SET.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ?????????????? */
    gstAtSendData.usBufLen = 0;

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstPsEflociInfoSetCnf->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaPsEflociInfoQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_EFPSLOCIINFO_QRY_CNF_STRU  *pstPsefloiinfoQryCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    pstPsefloiinfoQryCnf = (TAF_MMA_EFPSLOCIINFO_QRY_CNF_STRU *)pMsg;
    usLength = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPsefloiinfoQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPsEflociInfoQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPsEflociInfoQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_EFPSLOCIINFO_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPsEflociInfoQryCnf : Current Option is not AT_CMD_EFPSLOCIINFO_QRY.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ????????????????ERROR */
    if (TAF_MMA_APP_OPER_RESULT_SUCCESS != pstPsefloiinfoQryCnf->enRslt)
    {
        ulResult = AT_ERROR;

        At_FormatResultData(ucIndex, ulResult);
        return VOS_OK;
    }

    /* <ptmsi> */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                 (VOS_CHAR *)pgucAtSndCodeAddr,
                                 (VOS_CHAR *)pgucAtSndCodeAddr,
                                 "%s: 0x%08x",
                                 g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                 pstPsefloiinfoQryCnf->stPsEflociInfo.ulPTmsi);

    /* <ptmsi_signature> */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                 (VOS_CHAR *)pgucAtSndCodeAddr,
                                 (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                 ",0x%6x",
                                 pstPsefloiinfoQryCnf->stPsEflociInfo.ulPTmsiSignature);

    /* <plmn> */
    if (0xfff == pstPsefloiinfoQryCnf->stPsEflociInfo.stPlmnId.Mcc
     && 0xfff == pstPsefloiinfoQryCnf->stPsEflociInfo.stPlmnId.Mnc)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",\"ffffff\"");
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"%x%x%x",
                                           (0x0f00 & pstPsefloiinfoQryCnf->stPsEflociInfo.stPlmnId.Mcc) >> 8,
                                           (0x00f0 & pstPsefloiinfoQryCnf->stPsEflociInfo.stPlmnId.Mcc) >> 4,
                                           (0x000f & pstPsefloiinfoQryCnf->stPsEflociInfo.stPlmnId.Mcc));

        if(0x0F != ((0x0f00 & pstPsefloiinfoQryCnf->stPsEflociInfo.stPlmnId.Mnc) >> 8))
        {
            usLength +=(VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%x",
                                          (0x0f00 & pstPsefloiinfoQryCnf->stPsEflociInfo.stPlmnId.Mnc) >> 8);
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%x%x\"",
                                           (0x00f0 & pstPsefloiinfoQryCnf->stPsEflociInfo.stPlmnId.Mnc) >> 4,
                                           (0x000f & pstPsefloiinfoQryCnf->stPsEflociInfo.stPlmnId.Mnc));
    }
    /* <lac> */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                   ",0x%04x",
                                   pstPsefloiinfoQryCnf->stPsEflociInfo.usLac);

    /* <rac> */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                   ",0x%02x",
                                   pstPsefloiinfoQryCnf->stPsEflociInfo.ucRac);

    /* <location_update_status> */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                   ",%d",
                                   pstPsefloiinfoQryCnf->stPsEflociInfo.ucPsLocationUpdateStatus);


    gstAtSendData.usBufLen = usLength;

    /* ???????? */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaSetM2MFreqLockCnf(
    VOS_VOID                            *pmsg
)
{
    AT_MTA_MSG_STRU                     *pstRcvMsg;
    MTA_AT_SET_M2M_FREQLOCK_CNF_STRU    *pstSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????? */
    pstRcvMsg       = (AT_MTA_MSG_STRU *)pmsg;
    pstSetCnf       = (MTA_AT_SET_M2M_FREQLOCK_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex         = 0;
    ulResult        = AT_ERROR;

    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId,&ucIndex))
    {
        return AT_ERROR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        return AT_ERROR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_M2M_FREQLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return AT_ERROR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if(MTA_AT_RESULT_NO_ERROR == pstSetCnf->ulResult)
    {
        ulResult = AT_OK;
    }

    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaQryM2MFreqLockCnf(
    VOS_VOID                            *pmsg
)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg           = VOS_NULL_PTR;
    MTA_AT_QRY_M2M_FREQLOCK_CNF_STRU       *pstQryFreqLockCnf   = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usLength;

    /* ?????? */
    pstRcvMsg           = (AT_MTA_MSG_STRU *)pmsg;
    pstQryFreqLockCnf   = (MTA_AT_QRY_M2M_FREQLOCK_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;
    usLength            = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryM2MFreqLockCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryM2MFreqLockCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_M2M_FREQLOCK_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaQryFreqLockCnf : Current Option is not AT_CMD_M2M_FREQLOCK_QRY.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ??????AT^FREQLOCK???????????? */
    gstAtSendData.usBufLen = 0;

    /* ??????????????G-W-T-L????????????  */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* ????GSM???????????????? */
    if (AT_MTA_M2M_FREQLOCK_FLAG_TYPE_OFF == pstQryFreqLockCnf->ucFreqState[AT_FREQLOCK_MODE_TYPE_GSM - 1])
    {
        /* <enable>,<mode> */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%d,\"%s\"",
                                            pstQryFreqLockCnf->ucFreqState[AT_FREQLOCK_MODE_TYPE_GSM - 1],
                                            g_astFreqLockModeTbl[AT_FREQLOCK_MODE_TYPE_GSM - 1].acStrMode);
    }
    else
    {
        /* <enable>,<freq>,<mode>,<band>,, */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%d,\"%s\",%d,\"%s\",,",
                                            pstQryFreqLockCnf->ucFreqState[AT_FREQLOCK_MODE_TYPE_GSM - 1],
                                            g_astFreqLockModeTbl[AT_FREQLOCK_MODE_TYPE_GSM - 1].acStrMode,
                                            pstQryFreqLockCnf->stGFreqLockInfo.usFreq,
                                            g_astFreqLockGsmBandTbl[pstQryFreqLockCnf->stGFreqLockInfo.enBand].acStrGsmBand);
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);

    /* ????WCDMA???????????????? */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    if (AT_MTA_M2M_FREQLOCK_FLAG_TYPE_OFF == pstQryFreqLockCnf->ucFreqState[AT_FREQLOCK_MODE_TYPE_WCDMA - 1])
    {
        /* <enable>,<mode> */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%d,\"%s\"",
                                            pstQryFreqLockCnf->ucFreqState[AT_FREQLOCK_MODE_TYPE_WCDMA - 1],
                                            g_astFreqLockModeTbl[AT_FREQLOCK_MODE_TYPE_WCDMA - 1].acStrMode);
    }
    else
    {
        /* ????WCDMA??????????:??????????????+???????? */
        if (AT_MTA_M2M_FREQLOCK_TYPE_ENUM_FREQ_ONLY == pstQryFreqLockCnf->stWFreqLockInfo.ucFreqType)
        {
            /* <enable>,<mode>,<freq>,,, */
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%d,\"%s\",%d,,,",
                                                pstQryFreqLockCnf->ucFreqState[AT_FREQLOCK_MODE_TYPE_WCDMA - 1],
                                                g_astFreqLockModeTbl[AT_FREQLOCK_MODE_TYPE_WCDMA - 1].acStrMode,
                                                pstQryFreqLockCnf->stWFreqLockInfo.usFreq);
        }
        else
        {
            /* <enable>,<mode>,<freq>,,<psc>, */
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%d,\"%s\",%d,,%d,",
                                                pstQryFreqLockCnf->ucFreqState[AT_FREQLOCK_MODE_TYPE_WCDMA - 1],
                                                g_astFreqLockModeTbl[AT_FREQLOCK_MODE_TYPE_WCDMA - 1].acStrMode,
                                                pstQryFreqLockCnf->stWFreqLockInfo.usFreq,
                                                pstQryFreqLockCnf->stWFreqLockInfo.usPsc);
        }
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);

    /* ????TDS-CDMA???????????????? */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    if (AT_MTA_M2M_FREQLOCK_FLAG_TYPE_OFF == pstQryFreqLockCnf->ucFreqState[AT_FREQLOCK_MODE_TYPE_TDSCDMA - 1])
    {
        /* <enable>,<mode> */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%d,\"%s\"",
                                            pstQryFreqLockCnf->ucFreqState[AT_FREQLOCK_MODE_TYPE_TDSCDMA - 1],
                                            g_astFreqLockModeTbl[AT_FREQLOCK_MODE_TYPE_TDSCDMA - 1].acStrMode);
    }
    else
    {
        /* ????WCDMA??????????:??????????????+???????? */
        if (AT_MTA_M2M_FREQLOCK_TYPE_ENUM_FREQ_ONLY == pstQryFreqLockCnf->stTFreqLockInfo.ucFreqType)
        {
            /* <enable>,<mode>,<freq>,,, */
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%d,\"%s\",%d,,,",
                                                pstQryFreqLockCnf->ucFreqState[AT_FREQLOCK_MODE_TYPE_TDSCDMA - 1],
                                                g_astFreqLockModeTbl[AT_FREQLOCK_MODE_TYPE_TDSCDMA - 1].acStrMode,
                                                pstQryFreqLockCnf->stTFreqLockInfo.usFreq);
        }
        else
        {
            /* <enable>,<mode>,<freq>,,<psc>, */
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%d,\"%s\",%d,,%d,",
                                                pstQryFreqLockCnf->ucFreqState[AT_FREQLOCK_MODE_TYPE_TDSCDMA - 1],
                                                g_astFreqLockModeTbl[AT_FREQLOCK_MODE_TYPE_TDSCDMA - 1].acStrMode,
                                                pstQryFreqLockCnf->stTFreqLockInfo.usFreq,
                                                pstQryFreqLockCnf->stTFreqLockInfo.usSc);
        }
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);

    /* ????LTE???????????????? */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    if (AT_MTA_M2M_FREQLOCK_FLAG_TYPE_OFF == pstQryFreqLockCnf->ucFreqState[AT_MTA_M2M_FREQLOCK_MODE_LTE - 1])
    {
        /* <enable>,<mode> */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%d,\"%s\"",
                                            pstQryFreqLockCnf->ucFreqState[AT_MTA_M2M_FREQLOCK_MODE_LTE - 1],
                                            g_astFreqLockModeTbl[AT_MTA_M2M_FREQLOCK_MODE_LTE - 1].acStrMode);
    }
    else
    {
        /* ????LTE??????????:??????????????+???????? */
        if (AT_MTA_M2M_FREQLOCK_TYPE_ENUM_FREQ_ONLY == pstQryFreqLockCnf->stLFreqLockInfo.ucFreqType)
        {
            /* <enable>,<mode>,<freq>,,, */
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%d,\"%s\",%d,,,",
                                                pstQryFreqLockCnf->ucFreqState[AT_MTA_M2M_FREQLOCK_MODE_LTE - 1],
                                                g_astFreqLockModeTbl[AT_MTA_M2M_FREQLOCK_MODE_LTE - 1].acStrMode,
                                                pstQryFreqLockCnf->stLFreqLockInfo.usFreq);
        }
        else
        {
            /* <enable>,<mode>,<freq>,,,<pci> */
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%d,\"%s\",%d,,,%d",
                                                pstQryFreqLockCnf->ucFreqState[AT_FREQLOCK_MODE_TYPE_LTE - 1],
                                                g_astFreqLockModeTbl[AT_FREQLOCK_MODE_TYPE_LTE - 1].acStrMode,
                                                pstQryFreqLockCnf->stLFreqLockInfo.usFreq,
                                                pstQryFreqLockCnf->stLFreqLockInfo.usPci);
        }
    }

    gstAtSendData.usBufLen = usLength;

    /* ???????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaSetXCposrCnf(
    VOS_VOID                                *pMsg
)
{
    /* ???????????? */
    AT_MTA_MSG_STRU                  *pstMtaMsg;
    MTA_AT_RESULT_CNF_STRU           *pstSetXcposrCnf;
    VOS_UINT8                         ucIndex;
    VOS_UINT32                        ulResult;

    /* ?????????????? */
    pstMtaMsg       = (AT_MTA_MSG_STRU*)pMsg;
    pstSetXcposrCnf = (MTA_AT_RESULT_CNF_STRU*)pstMtaMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaSetXCposrCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetXCposrCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_XCPOSR_SET */
    if (AT_CMD_XCPOSR_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetXCposrCnf: WARNING:Not AT_CMD_XCPOSR_SET!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( MTA_AT_RESULT_NO_ERROR == pstSetXcposrCnf->enResult )
    {
        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;
    /* ????AT_FormatResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaQryXcposrCnf(
    VOS_VOID                        *pMsg
)
{
    /* ???????????? */
    AT_MTA_MSG_STRU                  *pstMtaMsg;
    MTA_AT_QRY_XCPOSR_CNF_STRU       *pstQryXcposrCnf;
    VOS_UINT8                         ucIndex;
    VOS_UINT32                        ulResult;

    /* ?????????????? */
    pstMtaMsg       = (AT_MTA_MSG_STRU*)pMsg;
    pstQryXcposrCnf = (MTA_AT_QRY_XCPOSR_CNF_STRU*)pstMtaMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaQryXcposrCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryXcposrCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_XCPOSR_QRY */
    if (AT_CMD_XCPOSR_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaQryXcposrCnf: WARNING:Not AT_CMD_XCPOSR_QRY!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( MTA_AT_RESULT_NO_ERROR == pstQryXcposrCnf->enResult )
    {
        ulResult    = AT_OK;
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstQryXcposrCnf->enXcposrEnableCfg);
    }
    else
    {
        ulResult    = AT_ERROR;
        gstAtSendData.usBufLen = 0;
    }

    /* ????AT_FormatResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaSetXcposrRptCnf(
    VOS_VOID                        *pMsg
)
{
    /* ???????????? */
    AT_MTA_MSG_STRU                  *pstMtaMsg             = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU           *pstSetXcposrRptCnf    = VOS_NULL_PTR;
    VOS_UINT8                         ucIndex;
    VOS_UINT32                        ulResult;

    /* ?????????????? */
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstSetXcposrRptCnf  = (MTA_AT_RESULT_CNF_STRU*)pstMtaMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaSetXcposrRptCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetXcposrRptCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_XCPOSR_SET */
    if (AT_CMD_XCPOSRRPT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetXcposrRptCnf: WARNING:Not AT_CMD_XCPOSRRPT_SET!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( MTA_AT_RESULT_NO_ERROR == pstSetXcposrRptCnf->enResult )
    {
        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ????AT_FormatResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}


VOS_UINT32 AT_RcvMtaQryXcposrRptCnf(
    VOS_VOID                        *pMsg
)
{
    /* ???????????? */
    AT_MTA_MSG_STRU                  *pstMtaMsg;
    MTA_AT_QRY_XCPOSRRPT_CNF_STRU    *pstQryXcposrRptCnf;
    VOS_UINT8                         ucIndex;
    VOS_UINT32                        ulResult;

    /* ?????????????? */
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstQryXcposrRptCnf  = (MTA_AT_QRY_XCPOSRRPT_CNF_STRU*)pstMtaMsg->aucContent;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaQryXcposrCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryXcposrCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_XCPOSR_QRY */
    if (AT_CMD_XCPOSRRPT_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaQryXcposrCnf: WARNING:Not AT_CMD_XCPOSR_QRY!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( MTA_AT_RESULT_NO_ERROR == pstQryXcposrRptCnf->enResult )
    {
        ulResult                = AT_OK;
        gstAtSendData.usBufLen  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                         (VOS_CHAR*)pgucAtSndCodeAddr,
                                                         (VOS_CHAR*)pgucAtSndCodeAddr,
                                                         "%s: %d",
                                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                         pstQryXcposrRptCnf->ucXcposrRptFlg);
    }
    else
    {
        ulResult                = AT_ERROR;
        gstAtSendData.usBufLen  = 0;
    }

    /* ????AT_FormatResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


VOS_UINT32 AT_RcvFratIgnitionQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstMtaMsg           = VOS_NULL_PTR;
    MTA_AT_FRAT_IGNITION_QRY_CNF_STRU  *pstIgnitionCnf      = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    /* ?????????????? */
    pstMtaMsg       = (AT_MTA_MSG_STRU *)pMsg;
    pstIgnitionCnf  = (MTA_AT_FRAT_IGNITION_QRY_CNF_STRU *)pstMtaMsg->aucContent;
    ucIndex         = 0;
    ulRet           = AT_OK;

     /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvFratIgnitionQryCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvFratIgnitionQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_FRATIGNITION_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvFratIgnitionQryCnf : Current Option is not AT_CMD_FRATIGNITION_QRY.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstIgnitionCnf->enResult)
    {
        ulRet = AT_ERROR;
    }
    else
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %u",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstIgnitionCnf->enFratIgnitionState);
    }

    /* ???????? */
    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;
}


VOS_UINT32 AT_RcvFratIgnitionSetCnf(
    VOS_VOID                           *pMsg
)
{
    /* ???????????? */
    AT_MTA_MSG_STRU                    *pstMtaMsg           = VOS_NULL_PTR;
    MTA_AT_FRAT_IGNITION_SET_CNF_STRU  *pstCnfContent       = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????????????? */
    pstMtaMsg       = (AT_MTA_MSG_STRU *)pMsg;
    pstCnfContent   = (MTA_AT_FRAT_IGNITION_SET_CNF_STRU *)pstMtaMsg->aucContent;
    ulResult        = AT_ERROR;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvFratIgnitionSetCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvFratIgnitionSetCnf: AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_FRATIGNITION_SET */
    if (AT_CMD_FRATIGNITION_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvFratIgnitionSetCnf: Not AT_CMD_FRATIGNITION_SET!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if ( MTA_AT_RESULT_NO_ERROR == pstCnfContent->enResult )
    {
        ulResult    = AT_OK;
    }

    gstAtSendData.usBufLen = 0;

    /* ????AT_FormatResultDATa???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}




VOS_UINT32 AT_RcvMtaSetSensorCnf(
    VOS_VOID                            *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_SET_SENSOR_CNF_STRU         *pstSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????? */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf    = (MTA_AT_SET_SENSOR_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex      = 0;
    ulResult     = AT_ERROR;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetSensorCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetSensorCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_SENSOR_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetSensorCnf : Current Option is not AT_CMD_SENSOR_SET.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ?????????????? */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR == pstSetCnf->enResult)
    {
        ulResult = AT_OK;
    }

    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaSetScreenCnf(
    VOS_VOID                            *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_SET_SCREEN_CNF_STRU         *pstSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????? */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf    = (MTA_AT_SET_SCREEN_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex      = 0;
    ulResult     = AT_ERROR;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetScreenCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetScreenCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_SCREEN_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetScreenCnf : Current Option is not AT_CMD_SCREEN_SET.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ?????????????? */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR == pstSetCnf->enResult)
    {
        ulResult = AT_OK;
    }

    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}



VOS_UINT32 AT_RcvMtaSetModemTimeCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_SET_TIME_CNF_STRU           *pstSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????? */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf    = (MTA_AT_SET_TIME_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex      = 0;
    ulResult     = AT_ERROR;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetModemTimeCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetModemTimeCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_MODEM_TIME_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetModemTimeCnf : Current Option is not AT_CMD_MODEM_TIME_SET.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ?????????????? */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR == pstSetCnf->enResult)
    {
        ulResult = AT_OK;
    }

    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaAfcClkUnlockCauseInd(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg               = VOS_NULL_PTR;
    MTA_AT_AFC_CLK_UNLOCK_IND_STRU     *pstMtaAtAfcClkUnlockInd = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;

    /* ?????? */
    pstRcvMsg               = (AT_MTA_MSG_STRU *)pMsg;
    pstMtaAtAfcClkUnlockInd = (MTA_AT_AFC_CLK_UNLOCK_IND_STRU *)pstRcvMsg->aucContent;
    ucIndex                 = 0;
    usLength                = 0;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaAfcClkUnlockCauseInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ????^AFCCLKUNLOCK: */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s%d%s",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_AFCCLKUNLOCK].pucText,
                                       pstMtaAtAfcClkUnlockInd->usCause,
                                       gaucAtCrLf);

    gstAtSendData.usBufLen = usLength;

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}


/*lint -save -e838 -specific(-e838)*/
/*lint -save -e826 -specific(-e826)*/
VOS_UINT32 AT_RcvDrvAgentQryCcpuMemInfoCnf(VOS_VOID *pstData)
{
    VOS_UINT8                                               ucIndex              = 0;
    DRV_AGENT_QRY_CCPU_MEM_INFO_CNF_STRU                   *pstQryCcpuMemInfoCnf = VOS_NULL_PTR;
    DRV_AGENT_MSG_STRU                                     *pRcvMsg              = VOS_NULL_PTR;

    pRcvMsg              = (DRV_AGENT_MSG_STRU *)pstData;
    pstQryCcpuMemInfoCnf = (DRV_AGENT_QRY_CCPU_MEM_INFO_CNF_STRU *)pRcvMsg->aucContent;

    /* ????ClientID???????????? */
    if(AT_FAILURE == At_ClientIdToUserId(pstQryCcpuMemInfoCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryCcpuMemInfoCnf: Get Index Fail!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryCcpuMemInfoCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* AT??????????^CCPUMEMINFO?????????????????????? */
    if (AT_CMD_CCPUMEMINFO_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryCcpuMemInfoCnf: Error Option!");
        return VOS_ERR;
    }

    /* ????AT_STOP_TIMER_CMD_READY????AT??????????????READY???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d,%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstQryCcpuMemInfoCnf->ulChkPoolLeakRslt,
                                                    pstQryCcpuMemInfoCnf->ulChkNodeLeakRslt,
                                                    pstQryCcpuMemInfoCnf->ulChkRrmNodeLeakRslt);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}
/*lint -restore*/
/*lint -restore*/


VOS_UINT32 AT_RcvMtaSetBestFreqCnf(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU             *pstSetCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;

    pstRcvMsg    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf    = (MTA_AT_RESULT_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex      = 0;
    ulRslt       = AT_ERROR;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetBestFreqCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetBestFreqCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_BESTFREQ_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetBestFreqCnf : Current Option is not AT_CMD_RXTESTMODE_SET.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ?????????????? */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR == pstSetCnf->enResult)
    {
        ulRslt = AT_OK;
    }

    At_FormatResultData(ucIndex, ulRslt);
    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaBestFreqInfoInd(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstMtaMsg          = VOS_NULL_PTR;
    MTA_AT_BEST_FREQ_CASE_IND_STRU     *pstBestFreqCaseInd = VOS_NULL_PTR;
    VOS_UINT32                          ulLoop;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    ucIndex            = 0;
    usLength           = 0;
    pstMtaMsg          = (AT_MTA_MSG_STRU *)pMsg;
    pstBestFreqCaseInd = (MTA_AT_BEST_FREQ_CASE_IND_STRU *)pstMtaMsg->aucContent;

    /* ????ClientId????ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaBestFreqInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    for (ulLoop = 0; ulLoop < pstBestFreqCaseInd->ucRptDeviceNum; ulLoop++)
    {
        usLength = 0;

        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s^BESTFREQ: %d,%d,%d%s",
                                           gaucAtCrLf,
                                           pstBestFreqCaseInd->astDeviceFreqList[ulLoop].ucGroupID,
                                           pstBestFreqCaseInd->astDeviceFreqList[ulLoop].ucDeviceID,
                                           pstBestFreqCaseInd->astDeviceFreqList[ulLoop].ucCaseID,
                                           gaucAtCrLf);

       gstAtSendData.usBufLen = usLength;

       At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaQryBestFreqCnf(
    VOS_VOID                           *pMsg
)

{
    AT_MTA_MSG_STRU                    *pstMtaMsg      = VOS_NULL_PTR;
    MTA_AT_BESTFREQ_QRY_CNF_STRU       *pstBestFreqCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLoop;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* ?????????????? */
    ucIndex        = 0;
    usLength       = 0;
    pstMtaMsg      = (AT_MTA_MSG_STRU *)pMsg;
    pstBestFreqCnf = (MTA_AT_BESTFREQ_QRY_CNF_STRU *)pstMtaMsg->aucContent;

    /* ????ClientId????ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaBestFreqInfoCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaBestFreqInfoCnf: WARNING:AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_BESTFREQ_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (MTA_AT_RESULT_NO_ERROR != pstBestFreqCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        for (ulLoop = 0; ulLoop < pstBestFreqCnf->ucActiveDeviceNum; ulLoop++)
        {
            if (0 != ulLoop)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s",
                                                   gaucAtCrLf);
            }

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s: %d,%d,%d,%d",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               pstBestFreqCnf->astDeviceInfoList[ulLoop].ucGroupID,
                                               pstBestFreqCnf->astDeviceInfoList[ulLoop].ucDeviceID,
                                               pstBestFreqCnf->astDeviceInfoList[ulLoop].ucCaseID,
                                               pstBestFreqCnf->astDeviceInfoList[ulLoop].ucMode);
        }
    }

    gstAtSendData.usBufLen = usLength;

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*lint -e838 */

VOS_UINT32 AT_RcvMtaModemCapUpdateCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg = VOS_NULL_PTR;
    MTA_AT_MODEM_CAP_UPDATE_CNF_STRU   *pstSetCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????? */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf    = (MTA_AT_MODEM_CAP_UPDATE_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex      = 0;
    ulResult     = AT_ERROR;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaModemCapUpdateCnf : WARNING:AT INDEX NOT FOUND!");

        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaModemCapUpdateCnf : AT_BROADCAST_INDEX.");

        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_MODEM_CAP_UPDATE_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaModemCapUpdateCnf : Current Option is not AT_CMD_MODEM_CAP_UPDATE_SET.");

        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ?????????????? */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR == pstSetCnf->enRslt)
    {
        ulResult = AT_OK;
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/*lint +e838 */

/*lint -e838 */

VOS_UINT32 AT_RcvMmaPacspQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_PACSP_QRY_CNF_STRU         *pstPacspQryCnf = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    pstPacspQryCnf = (TAF_MMA_PACSP_QRY_CNF_STRU *)pMsg;
    usLength = 0;

    /* ????clientid????index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPacspQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPacspQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG("AT_RcvMmaDplmnQryCnf: Get modem id fail.");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPacspQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (AT_CMD_PACSP_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPacspQryCnf : Current Option is not AT_CMD_PACSP_QRY.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "+PACSP%d",pstPacspQryCnf->ucPlmnMode);

    gstAtSendData.usBufLen = usLength;

    /* ???????? */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}
/*lint +e838 */


VOS_UINT32 AT_RcvMtaLteCategoryInfoInd(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_LTE_CATEGORY_INFO_IND_STRU  *pstLteCategoryInfoInd;

    pstMtaMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstLteCategoryInfoInd = (MTA_AT_LTE_CATEGORY_INFO_IND_STRU *)pstMtaMsg->aucContent;

    if ((pstLteCategoryInfoInd->ucDlCategery >= AT_UE_LTE_CATEGORY_NUM_MAX)
     || (pstLteCategoryInfoInd->ucUlCategery >= AT_UE_LTE_CATEGORY_NUM_MAX))
    {
        AT_WARN_LOG2("AT_RcvMtaLteCategoryInfoInd: WARNING: illegal Category value <DlCategery, UlCategery>!",pstLteCategoryInfoInd->ucDlCategery,pstLteCategoryInfoInd->ucUlCategery);
        return VOS_ERR;
    }
    else
    {
        g_stAtDlRateCategory.ucLteUeDlCategory = pstLteCategoryInfoInd->ucDlCategery;
        g_stAtDlRateCategory.ucLteUeUlCategory = pstLteCategoryInfoInd->ucUlCategery;
    }

    return VOS_OK;
}


