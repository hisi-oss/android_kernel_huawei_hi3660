

#ifndef __MTACOMMINTERFACE_H__
#define __MTACOMMINTERFACE_H__

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include  "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/
/*network monitor GSM???? ???????????? */
#define NETMON_MAX_GSM_NCELL_NUM                (6)

/*network monitor UTRAN ???? ???????????? */
#define NETMON_MAX_UTRAN_NCELL_NUM              (16)

/*network monitor LTE ???? ???????????? */
#define NETMON_MAX_LTE_NCELL_NUM                (16)

/*****************************************************************************
  3 ????????
*****************************************************************************/

enum MTA_RRC_GSM_BAND_ENUM
{
    MTA_RRC_GSM_BAND_850  = 0x00,
    MTA_RRC_GSM_BAND_900,
    MTA_RRC_GSM_BAND_1800,
    MTA_RRC_GSM_BAND_1900,

    MTA_RRC_GSM_BAND_BUTT
};
typedef VOS_UINT16 MTA_RRC_GSM_BAND_ENUM_UINT16;


enum MTA_NETMON_CELL_TYPE_ENUM
{
    MTA_NETMON_SCELL_TYPE               = 0,
    MTA_NETMON_NCELL_TYPE               = 1,
    MTA_NETMON_CELL_TYPE_BUTT
};

typedef VOS_UINT32 MTA_NETMON_CELL_TYPE_ENUM_UINT32;


enum MTA_NETMON_UTRAN_TYPE_ENUM
{
    MTA_NETMON_UTRAN_FDD_TYPE           = 0,
    MTA_NETMON_UTRAN_TDD_TYPE           = 1,
    MTA_NETMON_UTRAN_TYPE_BUTT
};
typedef VOS_UINT32 MTA_NETMON_UTRAN_TYPE_ENUM_UINT32;


enum MTA_NETMON_RESULT_ENUM
{
    MTA_NETMON_RESULT_NO_ERR            = 0,
    MTA_NETMON_RESULT_ERR               = 1,
    MTA_NETMON_RESULT_BUTT
};
typedef VOS_UINT32 MTA_NETMON_RESULT_ENUM_UINT32;

/*****************************************************************************
 ??????    : MTA_NETMON_CELL_QRY_MODULE_ENUM
 ????????  :
 ASN.1???? :
 ????????  : ????????????????????????????????
*****************************************************************************/
enum MTA_NETMON_CELL_QRY_MODULE_ENUM
{
    MTA_NETMON_CELL_QRY_MODULE_AT    = 0x00,    /* AT??????????????????????????AT^MONSC/AT^MONNC???? */
    MTA_NETMON_CELL_QRY_MODULE_MTC   = 0x01,    /* MTC???????????????????????? */
    MTA_NETMON_CELL_QRY_MODULE_BUTT
};
typedef VOS_UINT32 MTA_NETMON_CELL_QRY_MODULE_ENUM_UINT32;

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

/* ========??????????????MTA????????????????======== */

/**************************network monitor??????????????????????**********************************************************/

/* MTA??????????????????????????????2G/3G/????????/???? */

typedef struct
{
    VOS_MSG_HEADER                                     /* ??????*/              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;     /*????????*/             /*_H2ASN_Skip*/
    MTA_NETMON_CELL_TYPE_ENUM_UINT32    enCelltype;    /*0:??????????????1:????????*/
    VOS_UINT32                          ulQryModule;   /* ?????????????????? */
}MTA_RRC_NETMON_CELL_QRY_REQ_STRU;

/*GSM ????????*/

typedef struct
{
    VOS_UINT32                          bitOpBsic     : 1;
    VOS_UINT32                          bitOpCellID   : 1;
    VOS_UINT32                          bitOpLAC      : 1;
    VOS_UINT32                          bitOpSpare    : 29;
    VOS_UINT32                          ulCellID;       /*????ID*/
    VOS_UINT16                          usLAC;          /*????????*/
    VOS_UINT16                          usAfrcn;        /*????*/
    VOS_INT16                           sRSSI;          /* ??????RSSI */
    MTA_RRC_GSM_BAND_ENUM_UINT16        enBand;         /* band 0-3 */
    VOS_UINT8                           ucBsic;         /*??????????*/
    VOS_UINT8                           aucReserved[3];
}MTA_NETMON_GSM_NCELL_INFO_STRU;


/*LTE ????????,????????????????????????????????????*/

typedef struct
{
    VOS_UINT32                          ulPID;            /*????????ID*/
    VOS_UINT16                          usArfcn;          /*????*/
    VOS_INT16                           sRSRP;            /* RSRP????????????????*/
    VOS_INT16                           sRSRQ;            /* RSRQ????????????????*/
    VOS_INT16                           sRSSI;            /* Receiving signal strength in dbm */
}MTA_NETMON_LTE_NCELL_INFO_STRU;


/*WCDMA ????????*/

typedef struct
{
    VOS_UINT16                          usArfcn;          /*????*/
    VOS_UINT16                          usPSC;            /*??????*/
    VOS_INT16                           sECN0;            /*ECN0*/
    VOS_INT16                           sRSCP;            /*RSCP*/
}MTA_NETMON_UTRAN_NCELL_INFO_FDD_STRU;


/*TD_SCDMA ????????,??????????????????????????????*/

typedef struct
{
    VOS_UINT16                          usArfcn;          /*????*/
    VOS_UINT16                          usSC;             /*????*/
    VOS_UINT16                          usSyncID;         /*??????????*/
    VOS_INT16                           sRSCP;            /*RSCP*/
}MTA_NETMON_UTRAN_NCELL_INFO_TDD_STRU;


/*????????????*/

typedef struct
{
    VOS_UINT8                                ucGsmNCellCnt;      /*GSM ????????*/
    VOS_UINT8                                ucUtranNCellCnt;    /*WCDMA ????????*/
    VOS_UINT8                                ucLteNCellCnt;      /*LTE ????????*/
    VOS_UINT8                                ucReserved;
    MTA_NETMON_GSM_NCELL_INFO_STRU           astGsmNCellInfo[NETMON_MAX_GSM_NCELL_NUM];          /*GSM ????????????*/
    MTA_NETMON_UTRAN_TYPE_ENUM_UINT32        enCellMeasTypeChoice;     /* NETMON????????????:FDD,TDD */
    union
    {
        MTA_NETMON_UTRAN_NCELL_INFO_FDD_STRU astFddNCellInfo[NETMON_MAX_UTRAN_NCELL_NUM];         /* FDD???????????? */
        MTA_NETMON_UTRAN_NCELL_INFO_TDD_STRU astTddNCellInfo[NETMON_MAX_UTRAN_NCELL_NUM];         /*  TDD???????????? */
    }u;
    MTA_NETMON_LTE_NCELL_INFO_STRU           astLteNCellInfo[NETMON_MAX_LTE_NCELL_NUM];      /*LTE ????????????*/
}RRC_MTA_NETMON_NCELL_INFO_STRU;


/*********************network monitor????GSM ????????????************************************************/

typedef struct
{
    VOS_MSG_HEADER                                     /* ?????? */             /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;     /* ???????? */           /*_H2ASN_Skip*/
}MTA_GRR_NETMON_TA_QRY_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /* ?????? */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;          /* ???????? */      /*_H2ASN_Skip*/
    MTA_NETMON_RESULT_ENUM_UINT32       enResult;           /* ???????? */
    VOS_UINT16                          usTa;               /* ??????TA?? */
    VOS_UINT8                           aucReserved[2];     /* ?????????????????? */
}GRR_MTA_NETMON_TA_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulMcc;              /* ?????????? */
    VOS_UINT32                          ulMnc;              /* ?????????? */
    VOS_UINT32                          ulCellID;           /* ????ID */
    VOS_UINT16                          usLac;              /* ???????? */
    VOS_UINT16                          usArfcn;            /* ?????????? */
    VOS_INT16                           sRssi;              /* Receiving signal strength in dbm */
    MTA_RRC_GSM_BAND_ENUM_UINT16        enBand;             /* GSM????(0-3) */
    VOS_UINT8                           ucBsic;             /* ?????????? */
    VOS_UINT8                           ucRxQuality;        /* IDLE????????PS????????????,????????????????????????????[0,7] ,??????99*/
    VOS_UINT8                           aucReserved[2];     /* ?????????????????? */
}GRR_MTA_NETMON_SCELL_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;      /* ???????? */          /*_H2ASN_Skip*/
    MTA_NETMON_RESULT_ENUM_UINT32       enResult;
    MTA_NETMON_CELL_TYPE_ENUM_UINT32    enCelltype;     /* 0:??????????????1:???????? */
    VOS_UINT32                          ulQryModule;    /* ?????????????????? */
    union
    {
        GRR_MTA_NETMON_SCELL_INFO_STRU  stSCellinfo;    /* GSM???????????????? */
        RRC_MTA_NETMON_NCELL_INFO_STRU  stNCellinfo;    /* GSM???????????? */
    }u;
}GRR_MTA_NETMON_CELL_QRY_CNF_STRU;

/******************************network monitor????UTRAN ????????????****************************************************/


/*FDD ????????????????*/

typedef struct
{
    VOS_UINT32                          bitOpDRX      : 1;
    VOS_UINT32                          bitOpURA      : 1;
    VOS_UINT32                          bitOpSpare    : 30;
    VOS_UINT32                          ulDrx;          /* Discontinuous reception cycle length */
    VOS_INT16                           sECN0;          /*ECN0*/
    VOS_INT16                           sRSSI;          /* Receiving signal strength in dbm */
    VOS_INT16                           sRSCP;          /*Received Signal Code Power in dBm????????????????*/
    VOS_UINT16                          usPSC;          /*??????*/
    VOS_UINT16                          usURA;          /* UTRAN Registration Area Identity */
    VOS_UINT8                           aucReserved[2];

} MTA_NETMON_UTRAN_SCELL_INFO_FDD_STRU;


/*TDD ??????????????????????????????????*/

typedef struct
{
    VOS_UINT32                          ulDrx;              /* Discontinuous reception cycle length */
    VOS_UINT16                          usSC;               /*????*/
    VOS_UINT16                          usSyncID;           /*??????????*/
    VOS_UINT16                          usRac;              /*RAC*/
    VOS_INT16                           sRSCP;              /*RSCP*/
} MTA_NETMON_UTRAN_SCELL_INFO_TDD_STRU;



 /*UTRAN ????????????*/
 
typedef struct
{
    VOS_UINT32                                  bitOpCellID  : 1;
    VOS_UINT32                                  bitOpLAC     : 1;
    VOS_UINT32                                  bitOpSpare   : 30;
    VOS_UINT32                                  ulMcc;                  /*??????????*/
    VOS_UINT32                                  ulMnc;                  /*??????????*/
    VOS_UINT32                                  ulCellID;               /*????ID*/
    VOS_UINT16                                  usArfcn;                /*????*/
    VOS_UINT16                                  usLAC;                  /*????????*/
    MTA_NETMON_UTRAN_TYPE_ENUM_UINT32           enCellMeasTypeChoice;   /* NETMON????????????:FDD,TDD */
    union
    {
        MTA_NETMON_UTRAN_SCELL_INFO_FDD_STRU    stCellMeasResultsFDD;    /* FDD */
        MTA_NETMON_UTRAN_SCELL_INFO_TDD_STRU    stCellMeasResultsTDD;    /*  TDD */
    }u;
}RRC_MTA_NETMON_UTRAN_SCELL_INFO_STRU;



typedef struct
{
    VOS_MSG_HEADER                                              /* ??????*/     /*_H2ASN_Skip*/
    VOS_UINT32                                ulMsgName;        /*????????*/    /*_H2ASN_Skip*/
    MTA_NETMON_RESULT_ENUM_UINT32             enResult;
    MTA_NETMON_CELL_TYPE_ENUM_UINT32          enCelltype;       /*0:??????????????1:????????*/
    VOS_UINT32                                ulQryModule;      /* ?????????????????? */
    union
    {
        RRC_MTA_NETMON_UTRAN_SCELL_INFO_STRU  stSCellinfo;      /* UTRAN???????????????? */
        RRC_MTA_NETMON_NCELL_INFO_STRU        stNCellinfo;      /* UTRAN???????????? */
    }u;
}RRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU;

/*LTE ????????????*/

typedef struct
{
    VOS_UINT32                                  ulMcc;                  /*??????????*/
    VOS_UINT32                                  ulMnc;                  /*??????????*/
    VOS_UINT32                                  ulCellID;               /*????ID*/
    VOS_UINT32                                  ulPID;                  /*????????ID*/
    VOS_UINT16                                  usArfcn;                /*????*/
    VOS_UINT16                                  usTAC;
    VOS_INT16                                   sRSRP;
    VOS_INT16                                   sRSRQ;
    VOS_INT16                                   sRSSI;
    VOS_UINT8                                   aucReserved[2];
} MTA_NETMON_EUTRAN_SCELL_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                  /* ?????? */                /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;   /* ???????? */             /*_H2ASN_Skip*/
    MTA_NETMON_CELL_TYPE_ENUM_UINT32    enCelltype;  /* 0????????????????1?????????? */
    VOS_UINT32                          ulQryModule; /* ?????????????????? */
}MTA_LRRC_NETMON_CELL_QRY_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                              /* ??????*/     /*_H2ASN_Skip*/
    VOS_UINT32                                ulMsgName;        /*????????*/    /*_H2ASN_Skip*/
    MTA_NETMON_RESULT_ENUM_UINT32             enResult;
    MTA_NETMON_CELL_TYPE_ENUM_UINT32          enCelltype;       /*0:??????????????1:????????*/
    VOS_UINT32                                ulQryModule;      /* ?????????????????? */
    union
    {
        MTA_NETMON_EUTRAN_SCELL_INFO_STRU     stSCellinfo;      /* LTE???????????????? */
        RRC_MTA_NETMON_NCELL_INFO_STRU        stNCellinfo;      /* LTE???????????? */
    }u;
}LRRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU;


/*****************************************************************************
  10 ????????
*****************************************************************************/

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MtaCommInterface.h */
