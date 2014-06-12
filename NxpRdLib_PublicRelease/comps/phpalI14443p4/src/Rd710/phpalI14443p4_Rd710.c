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
* Software ISO14443-4 Component of Basic Function Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:27:04 2011 $
*
* History:
*  CHu: Generated 29. May 2009
*
*/

#include <phpalI14443p4.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHPAL_I14443P4_RD710

#include "phpalI14443p4_Rd710.h"
#include <phhalHw_Rd710_Cmd.h>

phStatus_t phpalI14443p4_Rd710_Init(
                                    phpalI14443p4_Rd710_DataParams_t * pDataParams,
                                    uint16_t wSizeOfDataParams,
                                    phhalHw_Rd710_DataParams_t * pHalDataParams
                                    )
{
    if (sizeof(phpalI14443p4_Rd710_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P4);
    }
    PH_ASSERT_NULL (pDataParams);
    PH_ASSERT_NULL (pHalDataParams);

    /* Init private data */
    pDataParams->wId            = PH_COMP_PAL_ISO14443P4 | PHPAL_I14443P4_RD710_ID;
    pDataParams->pHalDataParams = pHalDataParams;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_ISO14443P4);
}

phStatus_t phpalI14443p4_Rd710_SetProtocol(
    phpalI14443p4_Rd710_DataParams_t * pDataParams,
    uint8_t   bCidEnable,
    uint8_t   bCid,
    uint8_t   bNadEnable,
    uint8_t   bNad,
    uint8_t   bFwi,
    uint8_t   bFsdi,
    uint8_t   bFsci
    )
{
    return phhalHw_Rd710_Cmd_I14443P4_SetProtocol(
        pDataParams->pHalDataParams,
        bCidEnable,
        bCid,
        bNadEnable,
        bNad,
        bFwi,
        bFsdi,
        bFsci
        );
}

phStatus_t phpalI14443p4_Rd710_ResetProtocol(
    phpalI14443p4_Rd710_DataParams_t * pDataParams
    )
{
    return phhalHw_Rd710_Cmd_I14443P4_ResetProtocol(
        pDataParams->pHalDataParams
        );
}

phStatus_t phpalI14443p4_Rd710_Deselect(
                                        phpalI14443p4_Rd710_DataParams_t * pDataParams
                                        )
{
    return phhalHw_Rd710_Cmd_I14443P4_Deselect(
        pDataParams->pHalDataParams
        );
}

phStatus_t phpalI14443p4_Rd710_PresCheck(
    phpalI14443p4_Rd710_DataParams_t * pDataParams
    )
{
    return phhalHw_Rd710_Cmd_I14443P4_PresCheck(
        pDataParams->pHalDataParams
        );
}

phStatus_t phpalI14443p4_Rd710_Exchange(
                                        phpalI14443p4_Rd710_DataParams_t * pDataParams,
                                        uint16_t wOption,
                                        uint8_t * pTxBuffer,
                                        uint16_t wTxLength,
                                        uint8_t ** ppRxBuffer,
                                        uint16_t * pRxLength
                                        )
{
    return phhalHw_Rd710_Cmd_I14443P4_Exchange(
        pDataParams->pHalDataParams,
        wOption,
        pTxBuffer,
        wTxLength,
        ppRxBuffer,
        pRxLength
        );
}

phStatus_t phpalI14443p4_Rd710_SetConfig(
    phpalI14443p4_Rd710_DataParams_t * pDataParams,
    uint16_t wConfig,
    uint16_t wValue
    )
{
    return phhalHw_Rd710_Cmd_I14443P4_SetConfig(
        pDataParams->pHalDataParams,
        wConfig,
        wValue
        );
}

phStatus_t phpalI14443p4_Rd710_GetConfig(
    phpalI14443p4_Rd710_DataParams_t * pDataParams,
    uint16_t wConfig,
    uint16_t * pValue
    )
{
    return phhalHw_Rd710_Cmd_I14443P4_GetConfig(
        pDataParams->pHalDataParams,
        wConfig,
        pValue
        );
}

#endif /* NXPBUILD__PHPAL_I14443P4_RD710 */
