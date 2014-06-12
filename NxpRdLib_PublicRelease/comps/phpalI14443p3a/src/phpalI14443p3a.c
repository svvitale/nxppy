/*
*         Copyright (c), NXP Semiconductors Gratkorn / Austria
*
*                     (C)NXP Semiconductors
*       All rights are reserved. Reproduction in whole or in part is 
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
*particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

/** \file
* Generic ISO14443-3A Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.4 $
* $Date: Fri Apr 15 09:04:37 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#include <ph_Status.h>
#include <phpalI14443p3a.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHPAL_I14443P3A_SW
#include "Sw/phpalI14443p3a_Sw.h"
#endif /* NXPBUILD__PHPAL_I14443P3A_SW */

#ifdef NXPBUILD__PHPAL_I14443P3A_RD70X
#include "Rd70x/phpalI14443p3a_Rd70x.h"
#endif /* NXPBUILD__PHPAL_I14443P3A_RD70X */

#ifdef NXPBUILD__PHPAL_I14443P3A_RD710
#include "Rd710/phpalI14443p3a_Rd710.h"
#endif /* NXPBUILD__PHPAL_I14443P3A_RD710 */

#ifdef NXPBUILD__PHPAL_I14443P3A

phStatus_t phpalI14443p3a_RequestA(
                                   void * pDataParams,
                                   uint8_t * pAtqa
                                   )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phpalI14443p3a_RequestA");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pAtqa);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);
	PH_ASSERT_NULL (pAtqa);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_PAL_ISO14443P3A)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P3A);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PHPAL_I14443P3A_SW
    case PHPAL_I14443P3A_SW_ID:
        status = phpalI14443p3a_Sw_RequestA((phpalI14443p3a_Sw_DataParams_t *)pDataParams, pAtqa);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_SW */

#ifdef NXPBUILD__PHPAL_I14443P3A_RD70X
    case PHPAL_I14443P3A_RD70X_ID:
        status = phpalI14443p3a_Rd70x_RequestA((phpalI14443p3a_Rd70x_DataParams_t *)pDataParams, pAtqa);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_RD70X */

#ifdef NXPBUILD__PHPAL_I14443P3A_RD710
    case PHPAL_I14443P3A_RD710_ID:
        status = phpalI14443p3a_Rd710_RequestA((phpalI14443p3a_Rd710_DataParams_t *)pDataParams, pAtqa);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P3A);
        break;
    }

    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
#ifdef NXPBUILD__PH_LOG
    if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
    {
        PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, pAtqa_log, pAtqa, 2);
    }
#endif
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}

phStatus_t phpalI14443p3a_WakeUpA(
                                  void * pDataParams,
                                  uint8_t * pAtqa
                                  )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phpalI14443p3a_WakeUpA");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pAtqa);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);
	PH_ASSERT_NULL (pAtqa);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_PAL_ISO14443P3A)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P3A);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PHPAL_I14443P3A_SW
    case PHPAL_I14443P3A_SW_ID:
        status = phpalI14443p3a_Sw_WakeUpA((phpalI14443p3a_Sw_DataParams_t *)pDataParams, pAtqa);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_SW */

#ifdef NXPBUILD__PHPAL_I14443P3A_RD70X
    case PHPAL_I14443P3A_RD70X_ID:
        status = phpalI14443p3a_Rd70x_WakeUpA((phpalI14443p3a_Rd70x_DataParams_t *)pDataParams, pAtqa);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_RD70X */

#ifdef NXPBUILD__PHPAL_I14443P3A_RD710
    case PHPAL_I14443P3A_RD710_ID:
        status = phpalI14443p3a_Rd710_WakeUpA((phpalI14443p3a_Rd710_DataParams_t *)pDataParams, pAtqa);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P3A);
        break;
    }

    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
#ifdef NXPBUILD__PH_LOG
    if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
    {
        PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, pAtqa_log, pAtqa, 2);
    }
#endif
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}

phStatus_t phpalI14443p3a_HaltA(
                                void * pDataParams
                                )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phpalI14443p3a_HaltA");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_PAL_ISO14443P3A)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P3A);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PHPAL_I14443P3A_SW
    case PHPAL_I14443P3A_SW_ID:
        status = phpalI14443p3a_Sw_HaltA((phpalI14443p3a_Sw_DataParams_t *)pDataParams);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_SW */

#ifdef NXPBUILD__PHPAL_I14443P3A_RD70X
    case PHPAL_I14443P3A_RD70X_ID:
        status = phpalI14443p3a_Rd70x_HaltA((phpalI14443p3a_Rd70x_DataParams_t *)pDataParams);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_RD70X */

#ifdef NXPBUILD__PHPAL_I14443P3A_RD710
    case PHPAL_I14443P3A_RD710_ID:
        status = phpalI14443p3a_Rd710_HaltA((phpalI14443p3a_Rd710_DataParams_t *)pDataParams);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P3A);
        break;
    }

    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}

phStatus_t phpalI14443p3a_Anticollision(
                                        void * pDataParams,
                                        uint8_t bCascadeLevel,
                                        uint8_t * pUidIn,
                                        uint8_t bNvbUidIn,
                                        uint8_t * pUidOut,
                                        uint8_t * pNvbUidOut
                                        )
{
    phStatus_t PH_MEMLOC_REM status;
#ifdef NXPBUILD__PH_LOG
    uint8_t    PH_MEMLOC_REM bNvBUid;
#endif

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phpalI14443p3a_Anticollision");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(bCascadeLevel);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pUidIn);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(bNvbUidIn);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pUidOut);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pNvbUidOut);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT8(PH_LOG_LOGTYPE_DEBUG, bCascadeLevel_log, &bCascadeLevel);
#ifdef NXPBUILD__PH_LOG
	bNvBUid = bNvbUidIn >> 4;
    /* check for incomplete bytes */
    if (bNvbUidIn & 0x07) 
    {
        ++bNvBUid;
    }
    PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, pUidIn_log, pUidIn, bNvBUid);
#endif
    PH_LOG_HELPER_ADDPARAM_UINT8(PH_LOG_LOGTYPE_DEBUG, bNvbUidIn_log, &bNvbUidIn);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);
	if (bNvbUidIn) PH_ASSERT_NULL (pUidIn);
	PH_ASSERT_NULL (pUidOut);
	PH_ASSERT_NULL (pNvbUidOut);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_PAL_ISO14443P3A)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P3A);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PHPAL_I14443P3A_SW
    case PHPAL_I14443P3A_SW_ID:
        status = phpalI14443p3a_Sw_Anticollision((phpalI14443p3a_Sw_DataParams_t *)pDataParams, bCascadeLevel, pUidIn, bNvbUidIn, pUidOut, pNvbUidOut);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_SW */

#ifdef NXPBUILD__PHPAL_I14443P3A_RD70X
    case PHPAL_I14443P3A_RD70X_ID:
        status = phpalI14443p3a_Rd70x_Anticollision((phpalI14443p3a_Rd70x_DataParams_t *)pDataParams, bCascadeLevel, pUidIn, bNvbUidIn, pUidOut, pNvbUidOut);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_RD70X */

#ifdef NXPBUILD__PHPAL_I14443P3A_RD710
    case PHPAL_I14443P3A_RD710_ID:
        status = phpalI14443p3a_Rd710_Anticollision((phpalI14443p3a_Rd710_DataParams_t *)pDataParams, bCascadeLevel, pUidIn, bNvbUidIn, pUidOut, pNvbUidOut);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P3A);
        break;
    }

    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
#ifdef NXPBUILD__PH_LOG
    if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
    {
		bNvBUid = (*pNvbUidOut) >> 4;
        /* check for incomplete bytes */
        if ((*pNvbUidOut) & 0x07) 
        {
            ++bNvBUid;
        }
        PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, pUidOut_log, pUidOut, bNvBUid);
    }
#endif
    PH_LOG_HELPER_ADDPARAM_UINT8(PH_LOG_LOGTYPE_DEBUG, pNvbUidOut_log, pNvbUidOut);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}

phStatus_t phpalI14443p3a_Select(
                                 void * pDataParams,
                                 uint8_t bCascadeLevel,
                                 uint8_t * pUidIn,
                                 uint8_t * pSak
                                 )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phpalI14443p3a_Select");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(bCascadeLevel);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pUidIn);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pSak);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT8(PH_LOG_LOGTYPE_DEBUG, bCascadeLevel_log, &bCascadeLevel);
    PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, pUidIn_log, pUidIn, 4);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);
	PH_ASSERT_NULL (pUidIn);
	PH_ASSERT_NULL (pSak);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_PAL_ISO14443P3A)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P3A);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PHPAL_I14443P3A_SW
    case PHPAL_I14443P3A_SW_ID:
        status = phpalI14443p3a_Sw_Select((phpalI14443p3a_Sw_DataParams_t *)pDataParams, bCascadeLevel, pUidIn, pSak);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_SW */

#ifdef NXPBUILD__PHPAL_I14443P3A_RD70X
    case PHPAL_I14443P3A_RD70X_ID:
        status = phpalI14443p3a_Rd70x_Select((phpalI14443p3a_Rd70x_DataParams_t *)pDataParams, bCascadeLevel, pUidIn, pSak);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_RD70X */

#ifdef NXPBUILD__PHPAL_I14443P3A_RD710
    case PHPAL_I14443P3A_RD710_ID:
        status = phpalI14443p3a_Rd710_Select((phpalI14443p3a_Rd710_DataParams_t *)pDataParams, bCascadeLevel, pUidIn, pSak);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P3A);
        break;
    }

    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT8(PH_LOG_LOGTYPE_DEBUG, pSak_log, pSak);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}

phStatus_t phpalI14443p3a_ActivateCard(
                                       void * pDataParams,
                                       uint8_t * pUidIn,
                                       uint8_t bLenUidIn,
                                       uint8_t * pUidOut,
                                       uint8_t * pLenUidOut,
                                       uint8_t * pSak,
                                       uint8_t * pMoreCardsAvailable
                                       )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phpalI14443p3a_ActivateCard");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pUidIn);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pUidOut);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pSak);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pMoreCardsAvailable);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, pUidIn_log, pUidIn, bLenUidIn);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);
	if (bLenUidIn) PH_ASSERT_NULL (pUidIn);
	PH_ASSERT_NULL (pUidOut);
	PH_ASSERT_NULL (pLenUidOut);
	PH_ASSERT_NULL (pSak);
	PH_ASSERT_NULL (pMoreCardsAvailable);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_PAL_ISO14443P3A)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P3A);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PHPAL_I14443P3A_SW
    case PHPAL_I14443P3A_SW_ID:
        status = phpalI14443p3a_Sw_ActivateCard((phpalI14443p3a_Sw_DataParams_t *)pDataParams, pUidIn, bLenUidIn, pUidOut, pLenUidOut, pSak, pMoreCardsAvailable);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_SW */

#ifdef NXPBUILD__PHPAL_I14443P3A_RD70X
    case PHPAL_I14443P3A_RD70X_ID:
        status = phpalI14443p3a_Rd70x_ActivateCard((phpalI14443p3a_Rd70x_DataParams_t *)pDataParams, pUidIn, bLenUidIn, pUidOut, pLenUidOut, pSak, pMoreCardsAvailable);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_RD70X */

#ifdef NXPBUILD__PHPAL_I14443P3A_RD710
    case PHPAL_I14443P3A_RD710_ID:
        status = phpalI14443p3a_Rd710_ActivateCard((phpalI14443p3a_Rd710_DataParams_t *)pDataParams, pUidIn, bLenUidIn, pUidOut, pLenUidOut, pSak, pMoreCardsAvailable);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P3A);
        break;
    }

    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
#ifdef NXPBUILD__PH_LOG
    if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
    {
        PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, pUidOut_log, pUidOut, *pLenUidOut);
    }
#endif
    PH_LOG_HELPER_ADDPARAM_UINT8(PH_LOG_LOGTYPE_DEBUG, pSak_log, pSak);
    PH_LOG_HELPER_ADDPARAM_UINT8(PH_LOG_LOGTYPE_DEBUG, pMoreCardsAvailable_log, pMoreCardsAvailable);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}

phStatus_t phpalI14443p3a_Exchange(
                                   void * pDataParams,
                                   uint16_t wOption,
                                   uint8_t * pTxBuffer,
                                   uint16_t wTxLength,
                                   uint8_t ** ppRxBuffer,
                                   uint16_t * pRxLength
                                   )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phpalI14443p3a_Exchange");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wOption);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pTxBuffer);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(ppRxBuffer);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wOption_log, &wOption);
    PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, pTxBuffer_log, pTxBuffer, wTxLength);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);
	if (wTxLength) PH_ASSERT_NULL (pTxBuffer);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_PAL_ISO14443P3A)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P3A);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PHPAL_I14443P3A_SW
    case PHPAL_I14443P3A_SW_ID:
        status = phpalI14443p3a_Sw_Exchange((phpalI14443p3a_Sw_DataParams_t *)pDataParams, wOption, pTxBuffer, wTxLength, ppRxBuffer, pRxLength);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_SW */

#ifdef NXPBUILD__PHPAL_I14443P3A_RD70X
    case PHPAL_I14443P3A_RD70X_ID:
        status = phpalI14443p3a_Rd70x_Exchange((phpalI14443p3a_Rd70x_DataParams_t *)pDataParams, wOption, pTxBuffer, wTxLength, ppRxBuffer, pRxLength);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_RD70X */

#ifdef NXPBUILD__PHPAL_I14443P3A_RD710
    case PHPAL_I14443P3A_RD710_ID:
        status = phpalI14443p3a_Rd710_Exchange((phpalI14443p3a_Rd710_DataParams_t *)pDataParams, wOption, pTxBuffer, wTxLength, ppRxBuffer, pRxLength);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P3A);
        break;
    }

    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
#ifdef NXPBUILD__PH_LOG
    if ((((status & PH_ERR_MASK) == PH_ERR_SUCCESS) ||
        ((status & PH_ERR_MASK) == PH_ERR_SUCCESS_CHAINING) ||
        ((status & PH_ERR_MASK) == PH_ERR_SUCCESS_INCOMPLETE_BYTE)) &&
        !(wOption & PH_EXCHANGE_BUFFERED_BIT) &&
        (ppRxBuffer != NULL))
    {
        PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, ppRxBuffer_log, *ppRxBuffer, *pRxLength);
    }
#endif
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}

phStatus_t phpalI14443p3a_GetSerialNo(
                                      void * pDataParams,
                                      uint8_t * pUidOut,
                                      uint8_t * pLenUidOut
                                      )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phpalI14443p3a_GetSerialNo");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pUidOut);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);
	PH_ASSERT_NULL (pUidOut);
	PH_ASSERT_NULL (pLenUidOut);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_PAL_ISO14443P3A)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P3A);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PHPAL_I14443P3A_SW
    case PHPAL_I14443P3A_SW_ID:
        status = phpalI14443p3a_Sw_GetSerialNo((phpalI14443p3a_Sw_DataParams_t *)pDataParams, pUidOut, pLenUidOut);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_SW */

#ifdef NXPBUILD__PHPAL_I14443P3A_RD70X
    case PHPAL_I14443P3A_RD70X_ID:
        status = phpalI14443p3a_Rd70x_GetSerialNo((phpalI14443p3a_Rd70x_DataParams_t *)pDataParams, pUidOut, pLenUidOut);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_RD70X */

#ifdef NXPBUILD__PHPAL_I14443P3A_RD710
    case PHPAL_I14443P3A_RD710_ID:
        status = phpalI14443p3a_Rd710_GetSerialNo((phpalI14443p3a_Rd710_DataParams_t *)pDataParams, pUidOut, pLenUidOut);
        break;
#endif /* NXPBUILD__PHPAL_I14443P3A_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P3A);
        break;
    }

    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
#ifdef NXPBUILD__PH_LOG
    if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
    {
        PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, pUidOut_log, pUidOut, *pLenUidOut);
    }
#endif
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}

#endif /* NXPBUILD__PHPAL_I14443P3A */
