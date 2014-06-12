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
* Software Cid Manager Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
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

#include "phCidManager_Sw.h"

phStatus_t phCidManager_Sw_Init(
                             phCidManager_Sw_DataParams_t * pDataParams,
                             uint16_t wSizeOfDataParams
                             )
{
    if (sizeof(phCidManager_Sw_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_CIDMANAGER);
    }
	PH_ASSERT_NULL (pDataParams);

    /* Set identifier */
    pDataParams->wId = PH_COMP_CIDMANAGER | PH_CIDMANAGER_SW_ID;

    /* Initialise Cid list */
    memset(pDataParams->bCidList, 0x00, sizeof(pDataParams->bCidList));  /* PRQA S 3200 */

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_CIDMANAGER);
}

phStatus_t phCidManager_Sw_GetFreeCid(
                                   phCidManager_Sw_DataParams_t * pDataParams,
                                   uint8_t * pCid
                                   )
{
    uint8_t PH_MEMLOC_COUNT bIndex;

    /* Search for first free Cid */
    for (bIndex = 0; bIndex < PH_CIDMANAGER_LAST_CID; ++bIndex)
    {
        if (pDataParams->bCidList[bIndex] == 0)
        {
            break;
        }
    }

    /* If a free slot has been found */
    if (bIndex < PH_CIDMANAGER_LAST_CID)
    {
        /* Set slot to occupied status */
        pDataParams->bCidList[bIndex] = 1;

        /* return the free Cid */
        *pCid = bIndex + 1;
    }
    /* return PH_ERR_USE_CONDITION if no free slot has been found */
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_CIDMANAGER);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_CIDMANAGER);
}

phStatus_t phCidManager_Sw_FreeCid(
                                phCidManager_Sw_DataParams_t * pDataParams,
                                uint8_t bCid
                                )
{
    /* Bail out if given Cid is out of range */
    if (bCid == 0 || bCid > PH_CIDMANAGER_LAST_CID)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_CIDMANAGER);
    }

    /* Bail out if given Cid is not occupied */
    if (pDataParams->bCidList[bCid-1] == 0)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_CIDMANAGER);
    }

    /* Free Cid slot */
    pDataParams->bCidList[bCid-1] = 0;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_CIDMANAGER);
}

#endif /* NXPBUILD__PH_CIDMANAGER_SW */
