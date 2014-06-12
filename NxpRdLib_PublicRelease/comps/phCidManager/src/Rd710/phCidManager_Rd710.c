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
* Rd710 Cid Manager Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:04:42 2011 $
*
* History:
*  CHu: Generated 27. July 2009
*
*/

#include <phCidManager.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PH_CIDMANAGER_RD710

#include "phCidManager_Rd710.h"
#include <phhalHw_Rd710_Cmd.h>

phStatus_t phCidManager_Rd710_Init(
                                    phCidManager_Rd710_DataParams_t * pDataParams,
                                    uint16_t wSizeOfDataParams,
                                    phhalHw_Rd710_DataParams_t * pHalDataParams
                                    )
{
    if (sizeof(phCidManager_Rd710_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_CIDMANAGER);
    }
	PH_ASSERT_NULL (pDataParams);
	PH_ASSERT_NULL (pHalDataParams);

    /* Set identifier */
    pDataParams->wId            = PH_COMP_CIDMANAGER | PH_CIDMANAGER_RD710_ID;
    pDataParams->pHalDataParams = pHalDataParams;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_CIDMANAGER);
}

phStatus_t phCidManager_Rd710_GetFreeCid(
                                    phCidManager_Rd710_DataParams_t * pDataParams,
                                    uint8_t * pCid
                                    )
{
    return phhalHw_Rd710_Cmd_CID_GetFreeCid(
                pDataParams->pHalDataParams,
                pCid
                );
}

phStatus_t phCidManager_Rd710_FreeCid(
                                    phCidManager_Rd710_DataParams_t * pDataParams,
                                    uint8_t bCid
                                    )
{
    return phhalHw_Rd710_Cmd_CID_FreeCid(
                pDataParams->pHalDataParams,
                bCid
                );
}
#endif    /* NXPBUILD__PH_CIDMANAGER_RD710 */
