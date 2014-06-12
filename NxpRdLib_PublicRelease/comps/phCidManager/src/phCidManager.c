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
* Cid Manager Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:26:53 2011 $
*
* History:
*  CHu: Generated 27. July 2009
*
*/

#include <ph_Status.h>
#include <phCidManager.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PH_CIDMANAGER_SW
#include "Sw/phCidManager_Sw.h"
#endif /* NXPBUILD__PH_CIDMANAGER_SW */

#ifdef NXPBUILD__PH_CIDMANAGER_RD710
#include "Rd710/phCidManager_Rd710.h"
#endif /* NXPBUILD__PH_CIDMANAGER_RD710 */

#ifdef NXPBUILD__PH_CIDMANAGER

phStatus_t phCidManager_GetFreeCid(
                                   void * pDataParams,
                                   uint8_t * pCid
                                   )
{
   phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phCidManager_GetFreeCid");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pCid);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);
	PH_ASSERT_NULL (pCid);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_CIDMANAGER)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
        
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_CIDMANAGER);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_CIDMANAGER_SW
    case PH_CIDMANAGER_SW_ID:
        status = phCidManager_Sw_GetFreeCid((phCidManager_Sw_DataParams_t *)pDataParams, pCid);
        break;
#endif /* NXPBUILD__PH_CIDMANAGER_SW */

#ifdef NXPBUILD__PH_CIDMANAGER_RD710
    case PH_CIDMANAGER_RD710_ID:
        status = phCidManager_Rd710_GetFreeCid((phCidManager_Rd710_DataParams_t *)pDataParams, pCid);
        break;
#endif /* NXPBUILD__PH_CIDMANAGER_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_CIDMANAGER);
        break;
    }
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
#ifdef NXPBUILD__PH_LOG
    if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
    {
        PH_LOG_HELPER_ADDPARAM_UINT8(PH_LOG_LOGTYPE_INFO, pCid_log, pCid);
    }
#endif
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}

phStatus_t phCidManager_FreeCid(
                                void * pDataParams,
                                uint8_t bCid
                                )
{
   phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phCidManager_FreeCid");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(bCid);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT8(PH_LOG_LOGTYPE_INFO, bCid_log, &bCid);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_CIDMANAGER)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
        
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_CIDMANAGER);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_CIDMANAGER_SW
    case PH_CIDMANAGER_SW_ID:
        status = phCidManager_Sw_FreeCid((phCidManager_Sw_DataParams_t *)pDataParams, bCid);
        break;
#endif /* NXPBUILD__PH_CIDMANAGER_SW */

#ifdef NXPBUILD__PH_CIDMANAGER_RD710
    case PH_CIDMANAGER_RD710_ID:
        status = phCidManager_Rd710_FreeCid((phCidManager_Rd710_DataParams_t *)pDataParams, bCid);
        break;
#endif /* NXPBUILD__PH_CIDMANAGER_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_CIDMANAGER);
        break;
    }
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}

#endif /* NXPBUILD__PH_CIDMANAGER */
