/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : DrvNvInterface.h
  Description     : DrvNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __DRVNVINTERFACE_H__
#define __DRVNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

/*****************************************************************************
  2 Macro
*****************************************************************************/
typedef signed int          BSP_S32;
typedef signed short        BSP_S16;
typedef signed char         BSP_S8;
typedef char                BSP_CHAR;

typedef unsigned int        BSP_U32;
typedef unsigned short      BSP_U16;
typedef unsigned char       BSP_U8;

#define KPD_NV_UNIT               (16)  /* total 16 * 32Bit = 64bytes */
#define KPD_EVENT_MAX             (KPD_NV_UNIT-3)

#define DYN_MAX_PORT_CNT          (17)

/* ???????????????????? */
#if defined (DYNAMIC_PID_MAX_PORT_NUM)
#undef DYNAMIC_PID_MAX_PORT_NUM
#endif
#define DYNAMIC_PID_MAX_PORT_NUM  (17)

/* ?????????????????????? */
#if defined (VER_MAX_LENGTH)
#undef VER_MAX_LENGTH
#endif
#define VER_MAX_LENGTH            (30)

#define NV_HW_CFG_LENTH           (0x40)

/*NPNP ????????????????????*/
#define NPNP_OPEN    1
#define NPNP_CLOSE    0

/*NPNP????NV??????????*/
#define NV_NPNP_ENABLE    1
#define NV_NPNP_DISABLE    0
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                           ????????????????                                 *
*                                                                            *
******************************************************************************/

/*****************************************************************************
 ??????    : NV_WDT_TIMEOUT_STRU
 ????????  : NV_WDT_TIMEOUT???? ID=11
*****************************************************************************/
typedef struct
{
    BSP_U32   ulWdtTimeOut;
}NV_WDT_TIMEOUT_STRU;


/*****************************************************************************
 ??????    : USIM_TEMP_SENSOR_TABLE
 ????????  : USIM_TEMP_SENSOR_TABLE????
*****************************************************************************/
typedef struct
{
    BSP_S16   Temperature;
    BSP_U16   Voltage;
}USIM_TEMP_SENSOR_TABLE;

/*****************************************************************************
 ??????    : USIM_TEMP_SENSOR_TABLE_STRU
 ????????  : USIM_TEMP_SENSOR_TABLE????
*****************************************************************************/
typedef struct
{
    USIM_TEMP_SENSOR_TABLE UsimTempSensorTable[19];
}USIM_TEMP_SENSOR_TABLE_STRU;

/*****************************************************************************
 ??????    : NV_SYS_PRT_STRU
 ????????  : NV_SYS_PRT????
*****************************************************************************/
typedef struct
{
    BSP_U32    uintValue;
}NV_SYS_PRT_STRU;

/*****************************************************************************
 ??????    : nv_pid_enable_type
 ????????  : nv_pid_enable_type????
*****************************************************************************/
typedef struct
{
    BSP_U32    pid_enabled;
}nv_pid_enable_type;

/*****************************************************************************
 ??????    : NV_HW_CONFIG_STRU
 ????????  : NV_HW_CONFIG????
*****************************************************************************/
/* PMU??????????,8Byte */
typedef struct
{
	BSP_U8 PowerEn;
	BSP_U8 ModuleID;
	BSP_U8 DevID;
	BSP_U8 PowerID;
	BSP_U8 ConsumerID;
	BSP_U8 Reserve;
	BSP_U16 Voltage;
}PMU_POWER_CFG;

/*????????????????????????????????,??????????????,????????????*/
/*BUCK1*/
typedef struct
{
	BSP_U8 PowerEn;
	BSP_U8 ModuleID;
	BSP_U8 DevID;
	BSP_U8 PowerID;
	BSP_U8 ConsumerID;
	BSP_U8 Reserve;
	BSP_U16 Voltage;  /*Range:[0,2200]*/
}PMU_POWER_CFG_RFICTX;

/* PMU????,16?? */
typedef struct
{
	PMU_POWER_CFG 		 RF0_PA;
	PMU_POWER_CFG_RFICTX RFIC0_TX;
	PMU_POWER_CFG 		 RFIC0_RX;
	PMU_POWER_CFG 		 FEM0;
	PMU_POWER_CFG 		 RF0_VBIAS;

	PMU_POWER_CFG 		 RF1_PA;
	PMU_POWER_CFG_RFICTX RFIC1_TX;
	PMU_POWER_CFG 		 RFIC1_RX;
	PMU_POWER_CFG 		 FEM1;
	PMU_POWER_CFG 		 RF1_VBIAS;

	PMU_POWER_CFG FEM0_AUX;
	PMU_POWER_CFG PMU_RESERVE1;
	PMU_POWER_CFG PMU_RESERVE2;
	PMU_POWER_CFG PMU_RESERVE3;
	PMU_POWER_CFG PMU_RESERVE4;
	PMU_POWER_CFG PMU_RESERVE5;
}PMU_CFG_STRU;


typedef struct
{
    BSP_U16 ConsumerID;
    BSP_U16 PowerEn;/*0:??????????????1: ????????*/
    BSP_U16 Voltage;
    BSP_U16 ModuleID;
    BSP_U16 DevID;
    BSP_U16 PowerID;
    BSP_U16 Reserve;
}RF_PMU_CFG_STRU;

#define RF_POWER_MAX_NUM (24)
#define RF_POWER_RESERVE_NUM  (8)/*??????24-14-2??????HIMS??????????*/

typedef struct
{
    BSP_U16 W_PA_VCC;
    BSP_U16 G_PA_VCC;
    BSP_U16 CH0_W_RFIC_TX_ANA;
    BSP_U16 CH0_G_RFIC_TX_ANA;
    BSP_U16 CH1_W_RFIC_TX_ANA;
    BSP_U16 CH1_G_RFIC_TX_ANA;
    RF_PMU_CFG_STRU CH0_PA_VCC;
    RF_PMU_CFG_STRU CH0_PA_VBIAS;
    RF_PMU_CFG_STRU CH0_SWITCH_VCC;
    RF_PMU_CFG_STRU CH0_RFIC_TX_ANA;
    RF_PMU_CFG_STRU CH0_RFIC_RX_ANA;
    RF_PMU_CFG_STRU CH0_FEM_VIO;
    RF_PMU_CFG_STRU CH0_TUNNER_VCC;
    RF_PMU_CFG_STRU CH1_PA_VCC;
    RF_PMU_CFG_STRU CH1_PA_VBIAS;
    RF_PMU_CFG_STRU CH1_SWITCH_VCC;
    RF_PMU_CFG_STRU CH1_RFIC_TX_ANA;
    RF_PMU_CFG_STRU CH1_RFIC_RX_ANA;
    RF_PMU_CFG_STRU CH1_FEM_VIO;
    RF_PMU_CFG_STRU CH1_TUNNER_VCC;
    RF_PMU_CFG_STRU CH0_RFIC_XO_2P85;
    RF_PMU_CFG_STRU CH1_RFIC_XO_2P85;
    RF_PMU_CFG_STRU PMU_CFG[RF_POWER_RESERVE_NUM];
 }RF_VOLT_CONFIG_STRU;

/*----------------------??TDS/L B34/39 & GSM B3????????????????Begin--------------------------------*/

#define NV_GSM_GPIO_RESERVED_NUM_L 2
/*****************************************************************************
 ??????    : UCOM_NV_GSM_GPIO_FUNC_SEL_STRU
 ????????  :
 ASN.1???? :
 ????????  : GPIO2~5????????
*****************************************************************************/
typedef struct
{
    BSP_U16 uhwGpioAndOrSel;        /* GPIO????????????
                                        bit0~1	 	Reserved
                                        bit2    	GPIO2??????????    0--GPIO??modem????????(????)??1--GPIO??modem????????
                                        bit3 		GPIO3??????????    ????
                                        bit4 		GPIO4??????????    ????
                                        bit5 		GPIO5??????????    ????
                                        bit6~15	Reserved*/
    BSP_U16 uhwGpioCtrlAbbTxSel;    /* GPIO????????????????abb tx
                                        bit0~1	 	Reserved
                                        bit2    	GPIO2??????????????????abb tx   0--??????abb??tx(????)??1--????abb??tx
                                        bit3 		GPIO3??????????????????abb tx   	????
                                        bit4~15	Reserved*/
}UCOM_NV_GSM_GPIO_FUNC_SEL_STRU;

/*----------------------??TDS/L B34/39 & GSM B3????????????????End--------------------------------*/


enum UART_SWITCH_ENUM
{
    UART_SWITCH_DISABLE = 0,
    UART_SWITCH_ENABLE  = 1,
    UART_SWITCH_BUTT
};

typedef BSP_U8 UART_SWITCH_ENUM_UINT8;

typedef struct
{
    UART_SWITCH_ENUM_UINT8  enUartEnableCfg;
    BSP_U8  uartRsv[3];
}NV_UART_SWITCH_STRU;

/*****************************************************************************
 ??????    : DR_NV_ENHANCE_SIMCARD_LOCK_STATUS_STRU
 ????????  : ????????????????????   ID=8517
*****************************************************************************/
typedef struct
{
    BSP_U8  EnhanceSimcardStatus;     /* ?????????????????????? 0:??????, 1: ???? */
    BSP_U8  SimcardStatus;            /* SimCardLockStatus???????? 1: ????????, 2: ?????????? */
}DR_NV_ENHANCE_SIMCARD_LOCK_STATUS_STRU;

/*****************************************************************************
 ??????    : NV_BREATH_LED_STR
 ????????  : NV_BREATH_LED????     ID=9051
*****************************************************************************/
typedef struct
{
    BSP_U8 ucBreathOnTime;
    BSP_U8 ucBreathOffTime;
    BSP_U8 ucBreathRiseTime;
    BSP_U8 ucBreathFallTime;
}NV_BREATH_LED_STR;

/*****************************************************************************
 ??????    : CHG_BATTERY_TEMP_PROTECT_NV_TYPE
 ????????  : CHG_BATTERY_TEMP_PROTECT_NV_TYPE????     ID=50016
*****************************************************************************/
typedef struct
{
    BSP_U32  ulIsEnable;
    BSP_S32  lCloseAdcThreshold;
    BSP_U32  ulTempOverCount;
}CHG_BATTERY_TEMP_PROTECT_NV_TYPE;

/*****************************************************************************
 ??????    : PROIDNvInfo
 ????????  : PROIDNvInfo????     ID=50018,ID=50048
*****************************************************************************/
typedef struct _productIDNvInfo
{
    BSP_U32   NvStatus;
    BSP_U8    ucCompVer[VER_MAX_LENGTH];
} PROIDNvInfo;

/*****************************************************************************
 ??????    : NV_HUAWEI_PCCW_HS_HSPA_BLUE_STRU
 ????????  : NV_HUAWEI_PCCW_HS_HSPA_BLUE???? ID=50032
*****************************************************************************/
typedef struct
{
    BSP_U32  NVhspa_hs_blue; /*Range:[0,3]*/
}NV_HUAWEI_PCCW_HS_HSPA_BLUE_STRU;

/*****************************************************************************
 ??????    : nv_huawei_dynamic_pid_type
 ????????  : nv_huawei_dynamic_pid_type???? ID=50091 ????????
*****************************************************************************/
typedef struct PACKED_POST
{
    BSP_U32 nv_status;
    BSP_U8  first_port_style[DYNAMIC_PID_MAX_PORT_NUM];
    BSP_U8  rewind_port_style[DYNAMIC_PID_MAX_PORT_NUM];
    BSP_U8  reserved[22];
} nv_huawei_dynamic_pid_type;


/*****************************************************************************
 ??????    : USB_NV_SN_INFO_T
 ????????  : USB_NV_SN_INFO_T????
*****************************************************************************/
typedef struct tagUSB_NV_SN_INFO_T
{
    BSP_U32 u32USBNvState;
    BSP_U32 u32USBReserved1;
    BSP_U32 u32USBReserved2;
    BSP_U32 u32USBNvResult;
} USB_NV_SN_INFO_T;

/*****************************************************************************
 ??????    : USB_NV_DEV_INFO_T
 ????????  : USB_NV_DEV_INFO_T????
*****************************************************************************/
typedef struct tagUSB_NV_DEV_INFO_T
{
    BSP_U32 u32USBNvState;
    BSP_U32 u32USBDevTypeIdx;
    BSP_U32 u32USBReserved1;
    BSP_U32 u32USBReserved2;
/*    BSP_U32 u32USBNvResult;*/
} USB_NV_DEV_INFO_T;

/*****************************************************************************
 ??????    : USB_NV_SERIAL_NUM_T
 ????????  : USB_NV_SERIAL_NUM_T????
*****************************************************************************/
typedef struct tagUSB_NV_SERIAL_NUM_T
{
    BSP_U32 u32USBSerialNumSupp;
    BSP_U32 u32USBReserved1;
    BSP_U32 u32USBReserved2;
    BSP_U32 u32USBNvResult;
} USB_NV_SERIAL_NUM_T;

/*****************************************************************************
 ??????    : USB_NV_NEW_PID_INFO_T
 ????????  : USB_NV_NEW_PID_INFO_T????
*****************************************************************************/
typedef struct tagUSB_NV_NEW_PID_INFO_T
{
    BSP_U32 u32USBNewPidSupp;
} USB_NV_NEW_PID_INFO_T;

/*****************************************************************************
 ??????    : USB_NV_PID_UNION_T
 ????????  : USB_NV_PID_UNION_T????
*****************************************************************************/
typedef struct tagUSB_NV_PID_UNION_T
{
    BSP_U32 u32USBNvState;
    BSP_U32 u32USBProtOfs;   /* change from "u32USBVDFCust" to "u32USBProtOfs" */
    BSP_U32 u32USBCdromPid;
    BSP_U32 u32USBUniquePid;
} USB_NV_PID_UNION_T;

/*****************************************************************************
 ??????    : USB_NV_DEV_PROFILE_T
 ????????  : USB_NV_DEV_PROFILE_T????
*****************************************************************************/
typedef struct tagUSB_NV_DEV_PROFILE_T
{
    BSP_U32 u32USBNvState;
    BSP_U8  u8USBFirstPortSeq[DYN_MAX_PORT_CNT];
    BSP_U8  u8USBMultiPortSeq[DYN_MAX_PORT_CNT];
    BSP_U8  u8USBPortReserved[2];
} USB_NV_DEV_PROFILE_T;

/*****************************************************************************
 ??????    : NV_GCF_TYPE_CONTENT_STRU
 ????????  : NV_GCF_TYPE_CONTENT???? ID=8250
*****************************************************************************/
typedef struct
{
    BSP_U8 GCFTypeContent[4];
}NV_GCF_TYPE_CONTENT_STRU;

/*****************************************************************************
 ??????    : TEM_VOLT_TABLE
 ????????  : TEM_VOLT_TABLE????
*****************************************************************************/
typedef struct tem_volt_table
{
    BSP_S16   temperature;
    BSP_U16   voltage;
}TEM_VOLT_TABLE;

/*****************************************************************************
 ??????    : NV_TCXO_CFG_STRU
 ????????  : NV_TCXO_CFG???? ID=9217
*****************************************************************************/
typedef struct
{
    BSP_U32 tcxo_cfg;
}NV_TCXO_CFG_STRU;

/*****************************************************************************
 ??????    : NV_KADC_PHYTOLOGICAL_CONFIGTCXO_CFG_STRU
 ????????  : NV_KADC_PHYTOLOGICAL_CONFIGTCXO_CFG???? ID=9216
*****************************************************************************/
typedef struct
{
    BSP_U16 hkadc[14];
}NV_KADC_PHYTOLOGICAL_CONFIGTCXO_CFG_STRU;

/*****************************************************************************
 ??????    : NV_THERMAL_HKADC_CONFIG
 ????????  : NV_THERMAL_HKADC_CONFIG???? ID=9232
*****************************************************************************/
typedef struct
{
    BSP_U16 hkadc[32];
}NV_KADC_CHANNEL_CFG_STRU;
typedef struct
{
    BSP_U32   outconfig;
    BSP_U16   outperiod;
    BSP_U16   convertlistlen;
    BSP_U32   reserved[2];
}NV_THERMAL_HKADC_CONFIG;

/*****************************************************************************
 ??????    : NV_THERMAL_HKADC_CONFIG_STRU
 ????????  : NV_THERMAL_HKADC_CONFIG???? ID=9215
*****************************************************************************/
typedef struct
{
    NV_THERMAL_HKADC_CONFIG   hkadcCfg[14];
}NV_THERMAL_HKADC_CONFIG_STRU;

/*****************************************************************************
 ??????    : NV_THERMAL_BAT_CONFIG_STRU
 ????????  : NV_THERMAL_BAT_CONFIG???? ID=9214
*****************************************************************************/
typedef struct
{
    BSP_U16       enable;
    BSP_U16       hkadcid;
    BSP_S16       highthres;
    BSP_U16       highcount;
    BSP_S16       lowthres;
    BSP_U16       lowcount;
    BSP_U32       reserved[2];

}NV_THERMAL_BAT_CONFIG_STRU;

/*****************************************************************************
 ??????    : NV_THERMAL_TSENSOR_CONFIG_STRU
 ????????  : NV_THERMAL_TSENSOR_CONFIG???? ID=9213
*****************************************************************************/
typedef struct
{
    BSP_U32       enable;
    BSP_U32       lagvalue0;
    BSP_U32       lagvalue1;
    BSP_U32       thresvalue0;
    BSP_U32       thresvalue1;
    BSP_U32       rstthresvalue0;
    BSP_U32       rstthresvalue1;
    BSP_U32       alarmcount1;
    BSP_U32       alarmcount2;
    BSP_U32       resumecount;
    BSP_U32       acpumaxfreq;
    BSP_U32       gpumaxfreq;
    BSP_U32       ddrmaxfreq;
    BSP_U32       reserved[4];
}NV_THERMAL_TSENSOR_CONFIG_STRU;

/*****************************************************************************
 ??????    : NV_TUNER_MIPI_INIT_CONFIG_STRU
 ????????  : NV_TUNER_MIPI_INIT_CONFIG_STRU???? ID=10046
*****************************************************************************/
#define TUNER_USER_DATA_MAX_NUM (9)
#define TUNER_MAX_NUM           (2)
typedef struct
{
    BSP_U8 mipiChan;
    BSP_U8 validNum;
    BSP_U16 cmdFrame[TUNER_USER_DATA_MAX_NUM];
    BSP_U16 dataFrame[TUNER_USER_DATA_MAX_NUM];
}NV_TUNER_MIPI_FRAME_CONFIG_STRU;

typedef struct
{
    NV_TUNER_MIPI_FRAME_CONFIG_STRU RFInitReg[TUNER_MAX_NUM];
}NV_GU_RF_FEND_MIPI_INIT_CONFIG_STRU;
/*****************************************************************************
 ??????    : WG_DRX_RESUME_TIME_STRU
 ????????  : WG_DRX_RESUME_TIME_STRU???? ID=10031
*****************************************************************************/
typedef struct
{
    unsigned long ulAbbPwrRsmTime;
    unsigned long ulRfPwrRsmTime;
    unsigned long ulAntSwitchPwrRsmTime;
    unsigned long ulAbbWpllRsmTime;
    unsigned long ulAbbGpllRsmTime;
    unsigned long ulBbpPllRsmTime;
    unsigned long ulPaStarRsmTime;
    unsigned long ulSysProtectTime;
    unsigned long ulTcxoRsmTime;
    unsigned long ulDcxoRsmTime;
    unsigned long ulSlowToMcpuRsmTime;
    unsigned long ulWphyRsmTime;
    unsigned long ulGphyRsmTime;
    unsigned long ulTaskSwitchRsmTime;
    unsigned long ulPaPwrRsmTime;
}WG_DRX_RESUME_TIME_STRU;

/*****************************************************************************
 ??????    : NV_NPNP_CONFIG_INFO
 ????????  : NV_NPNP_CONFIG_INFO
*****************************************************************************/
typedef struct
{
    BSP_U32 npnp_open_flag;                           /* NPNP ????????NV????, 0??????????????????, 1?????????????? */
    BSP_U32 npnp_enable_flag;                         /* NPNP ????????NV??, 0????????????, 1??????????             */
}NV_NPNP_CONFIG_INFO;
/*****************************************************************************
 ??????    : NV_RF_GPIO_CFG_STRU
 ????????  : RF_GPIO??????????????????DRV_GPIO
             ??????????????????????????????RF_GPIO????????????????????????
             ??????NV???? ID=10047
*****************************************************************************/
typedef struct
{
    BSP_U16 is_used;    /*Range:[0,1]*/
	BSP_U16 gpio_level; /*Range:[0,1]*/
}RF_MODEM_CONTROL;
typedef struct
{
    BSP_U32 rf_gpio_num;
    RF_MODEM_CONTROL modem_inside;
    RF_MODEM_CONTROL modem_outside;
}RF_GPIO_CFG;
typedef struct
{
    RF_GPIO_CFG rf_switch_cfg[16];
}NV_RF_SWITCH_CFG_STRU;
/*****************************************************************************
 ??????    : NV_RF_ANT_OTG_CFG_STRU
 ????????  : ????????????????????????????????????????????????????????????????
             ??????NV????????????????NV??????????????GPIO????????????????
             ID=10051
*****************************************************************************/
typedef struct
{
    BSP_U16 ANT0_GPIO_NUM;
    BSP_U16 ANT1_GPIO_NUM;
}NV_RF_ANT_OTG_CFG_STRU;

/*****************************************************************************
 ??????    : NV_T1_CTRL_PARA_STRU
 ????????  : NV_T1_CTRL_PARA_STRU ID=71
*****************************************************************************/
typedef struct
{
    BSP_U32             TMode;
    BSP_U32             enEDM;
    BSP_U32             aulRsv[4];
}NV_T1_CTRL_PARA_STRU;

/*****************************************************************************
 ??????    : NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY
 ????????  : NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY ID=148
*****************************************************************************/
typedef struct
{
    BSP_U16         usProductType;/*0:MBB V3R3 stick/E5,etc.; 1:V3R3 M2M & V7R2; 2:V9R1 phone; 3:K3V3&V8R1;*/
    BSP_U16         usRsv;
}NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY;

/*****************************************************************************
 ??????    : UCOM_NV_NV_ITEM_XO_DEFINE_STRU
 ????????  :
 ASN.1???? :
 ????????  : ?????????????? ID=10056
*****************************************************************************/
typedef struct
{
    BSP_U16      enSingleXoType;                     /* ??????????????,0:????????1:??tcxo??2:??dcxo */
    BSP_U16      en32kType;                          /* 0:32000,1:32764??2:32768*/
}DRV_NV_SINGLE_XO_DEFINE_STRU;
/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of DrvNvInterface.h */
