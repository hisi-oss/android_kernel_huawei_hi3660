


/*****************************************************************************
   1 ??????????
*****************************************************************************/
#include "PsCommonDef.h"
#include "TafSsaApi.h"





/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
#define THIS_FILE_ID                    PS_FILE_ID_TAF_SSA_API_C


/*****************************************************************************
   2 ????????????
*****************************************************************************/


/*****************************************************************************
   3 ????????????
*****************************************************************************/

extern VOS_UINT32 AT_GetDestPid(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulRcvPid
);


/*****************************************************************************
   4 ????????
*****************************************************************************/

VOS_VOID TAF_SSA_SndTafMsg(
    TAF_SSA_MSG_ID_ENUM_UINT32          enMsgId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    TAF_SSA_MSG_STRU                   *pstMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulPid;

    TAF_CTRL_STRU                      *pstCtrl  = VOS_NULL_PTR;

    pstCtrl = (TAF_CTRL_STRU *)pData;

    /* ?????????? */
    ulPid = AT_GetDestPid(pstCtrl->usClientId, WUEPS_PID_TAF);

    /* ???????? */
    pstMsg = (TAF_SSA_MSG_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                ulPid,
                                sizeof(MSG_HEADER_STRU) + ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->stHeader.ulReceiverPid      = ulPid;
    pstMsg->stHeader.ulMsgName          = enMsgId;

    /* ???????????? */
    TAF_MEM_CPY_S(pstMsg->aucContent, ulLength, pData, ulLength);

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulPid, pstMsg);

    return;
}


VOS_VOID TAF_SSA_SetCmolrInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_SSA_LCS_MOLR_PARA_SET_STRU     *pstMolrPara
)
{
    TAF_SSA_SET_LCS_MOLR_REQ_STRU       stSetCmolrReq;

    /* ?????? */
    TAF_MEM_SET_S(&stSetCmolrReq, sizeof(stSetCmolrReq), 0x00, sizeof(stSetCmolrReq));

    /* ????CTRL???? */
    TAF_API_CTRL_HEADER(&stSetCmolrReq, ulModuleId, usClientId, ucOpId);

    stSetCmolrReq.stMolrPara  = *pstMolrPara;

    /* ???????? */
    TAF_SSA_SndTafMsg(ID_TAF_SSA_SET_LCS_MOLR_REQ,
                      &stSetCmolrReq,
                      sizeof(stSetCmolrReq));

    return;
}


VOS_VOID TAF_SSA_GetCmolrInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_SSA_GET_LCS_MOLR_REQ_STRU       stGetCmolrReq;

    /* ?????? */
    TAF_MEM_SET_S(&stGetCmolrReq, sizeof(stGetCmolrReq), 0x00, sizeof(stGetCmolrReq));

    /* ????CTRL???? */
    TAF_API_CTRL_HEADER(&stGetCmolrReq, ulModuleId, usClientId, ucOpId);

    /* ???????? */
    TAF_SSA_SndTafMsg(ID_TAF_SSA_GET_LCS_MOLR_REQ,
                      &stGetCmolrReq,
                      sizeof(stGetCmolrReq));

    return;
}


VOS_VOID TAF_SSA_SetCmtlrInfo(
    VOS_UINT32                              ulModuleId,
    VOS_UINT16                              usClientId,
    VOS_UINT8                               ucOpId,
    TAF_SSA_LCS_MTLR_SUBSCRIBE_ENUM_UINT8   enSubscribe
)
{
    TAF_SSA_SET_LCS_MTLR_REQ_STRU       stSetCmtlrReq;

    /* ?????? */
    TAF_MEM_SET_S(&stSetCmtlrReq, sizeof(stSetCmtlrReq), 0x00, sizeof(stSetCmtlrReq));

    /* ????CTRL???? */
    TAF_API_CTRL_HEADER(&stSetCmtlrReq, ulModuleId, usClientId, ucOpId);

    stSetCmtlrReq.enSubscribe   = enSubscribe;

    /* ???????? */
    TAF_SSA_SndTafMsg(ID_TAF_SSA_SET_LCS_MTLR_REQ,
                      &stSetCmtlrReq,
                      sizeof(stSetCmtlrReq));

    return;
}


VOS_VOID TAF_SSA_GetCmtlrInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_SSA_GET_LCS_MTLR_REQ_STRU       stGetCmtlrReq;

    /* ?????? */
    TAF_MEM_SET_S(&stGetCmtlrReq, sizeof(stGetCmtlrReq), 0x00, sizeof(stGetCmtlrReq));

    /* ????CTRL???? */
    TAF_API_CTRL_HEADER(&stGetCmtlrReq, ulModuleId, usClientId, ucOpId);

    /* ???????? */
    TAF_SSA_SndTafMsg(ID_TAF_SSA_GET_LCS_MTLR_REQ,
                      &stGetCmtlrReq,
                      sizeof(stGetCmtlrReq));

    return;
}


VOS_VOID TAF_SSA_SetCmtlraInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_SSA_LCS_MTLRA_PARA_SET_STRU    *pstCmtlraPara
)
{
    TAF_SSA_SET_LCS_MTLRA_REQ_STRU      stSetCmtlraReq;

    /* ?????? */
    TAF_MEM_SET_S(&stSetCmtlraReq, sizeof(stSetCmtlraReq), 0x00, sizeof(stSetCmtlraReq));

    /* ????CTRL???? */
    TAF_API_CTRL_HEADER(&stSetCmtlraReq, ulModuleId, usClientId, ucOpId);

    stSetCmtlraReq.stCmtlraPara  = *pstCmtlraPara;

    /* ???????? */
    TAF_SSA_SndTafMsg(ID_TAF_SSA_SET_LCS_MTLRA_REQ,
                      &stSetCmtlraReq,
                      sizeof(stSetCmtlraReq));

    return;
}


VOS_VOID TAF_SSA_GetCmtlraInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_SSA_GET_LCS_MTLRA_REQ_STRU      stGetCmtlraReq;

    /* ?????? */
    TAF_MEM_SET_S(&stGetCmtlraReq, sizeof(stGetCmtlraReq), 0x00, sizeof(stGetCmtlraReq));

    /* ????CTRL???? */
    TAF_API_CTRL_HEADER(&stGetCmtlraReq, ulModuleId, usClientId, ucOpId);

    /* ???????? */
    TAF_SSA_SndTafMsg(ID_TAF_SSA_GET_LCS_MTLRA_REQ,
                      &stGetCmtlraReq,
                      sizeof(stGetCmtlraReq));

    return;
}







