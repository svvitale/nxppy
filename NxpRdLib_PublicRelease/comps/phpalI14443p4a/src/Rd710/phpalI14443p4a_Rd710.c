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
* Software ISO14443-4A Component of Basic Function Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:28:03 2011 $
*
* History:
*  CHu: Generated 29. May 2009
*
*/

#include <phpalI14443p4a.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHPAL_I14443P4A_RD710

#include <phhalHw_Rd710_Cmd.h>
#include "phpalI14443p4a_Rd710.h"

phStatus_t phpalI14443p4a_Rd710_Init(
                                      phpalI14443p4a_Rd710_DataParams_t * pDataParams,
                                      uint16_t wSizeOfDataParams,
                                      phhalHw_Rd710_DataParams_t * pHalDataParams
                                      )
{
    if (sizeof(phpalI14443p4a_Rd710_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P4A);
    }
	PH_ASSERT_NULL (pDataParams);
	PH_ASSERT_NULL (pHalDataParams);

    /* init private data */
    pDataParams->wId            = PH_COMP_PAL_ISO14443P4A | PHPAL_I14443P4A_RD710_ID;
    pDataParams->pHalDataParams = pHalDataParams;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_ISO14443P4A);
}

phStatus_t phpalI14443p4a_Rd710_Rats(
                                      phpalI14443p4a_Rd710_DataParams_t * pDataParams,
                                      uint8_t bFsdi,
                                      uint8_t bCid,
                                      uint8_t * pAts
                                      )
{
    return phhalHw_Rd710_Cmd_I14443P4A_Rats(
        pDataParams->pHalDataParams,
        bFsdi,
        bCid,
        pAts
        );
}

phStatus_t phpalI14443p4a_Rd710_Pps(
                                     phpalI14443p4a_Rd710_DataParams_t * pDataParams,
                                     uint8_t bDri,
                                     uint8_t bDsi
                                     )
{
    return phhalHw_Rd710_Cmd_I14443P4A_Pps(
        pDataParams->pHalDataParams,
        bDri,
        bDsi
        );
}

phStatus_t phpalI14443p4a_Rd710_ActivateCard(
                                                phpalI14443p4a_Rd710_DataParams_t * pDataParams,
                                                uint8_t bFsdi,
                                                uint8_t bCid,
                                                uint8_t bDri,
                                                uint8_t bDsi,
                                                uint8_t * pAts
                                                )
{
    return phhalHw_Rd710_Cmd_I14443P4A_ActivateCard(
        pDataParams->pHalDataParams,
        bFsdi,
        bCid,
        bDri,
        bDsi,
        pAts
        );
}

phStatus_t phpalI14443p4a_Rd710_GetProtocolParams(
												phpalI14443p4a_Rd710_DataParams_t * pDataParams,
                                                uint8_t * pCidEnabled,
                                                uint8_t * pCid,
                                                uint8_t * pNadSupported,
                                                uint8_t * pFwi,
                                                uint8_t * pFsdi,
                                                uint8_t * pFsci
                                                )
{
    return phhalHw_Rd710_Cmd_I14443P4A_GetProtocolParams(
	    pDataParams->pHalDataParams,
        pCidEnabled,
        pCid,
        pNadSupported,
        pFwi,
        pFsdi,
        pFsci
        );
}

#endif /* NXPBUILD__PHPAL_I14443P4A_RD710 */
