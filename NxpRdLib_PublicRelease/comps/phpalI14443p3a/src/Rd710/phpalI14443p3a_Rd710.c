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
* Software ISO14443-3A Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:27:31 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#include <ph_RefDefs.h>
#include <phpalI14443p3a.h>

#ifdef NXPBUILD__PHPAL_I14443P3A_RD710

#include "phpalI14443p3a_Rd710.h"
#include <phhalHw_Rd710_Cmd.h>

phStatus_t phpalI14443p3a_Rd710_Init(
                                     phpalI14443p3a_Rd710_DataParams_t * pDataParams,
                                     uint16_t wSizeOfDataParams,
                                     phhalHw_Rd710_DataParams_t * pHalDataParams
                                     )
{
    if (sizeof(phpalI14443p3a_Rd710_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P3A);
    }
    PH_ASSERT_NULL (pDataParams);
    PH_ASSERT_NULL (pHalDataParams);

    /* init private data */
    pDataParams->wId            = PH_COMP_PAL_ISO14443P3A | PHPAL_I14443P3A_RD710_ID;
    pDataParams->pHalDataParams = pHalDataParams;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_ISO14443P3A);
}

phStatus_t phpalI14443p3a_Rd710_RequestA(
    phpalI14443p3a_Rd710_DataParams_t * pDataParams,
    uint8_t * pAtqa
    )
{
    return phhalHw_Rd710_Cmd_I14443P3A_RequestA(
        pDataParams->pHalDataParams,
        pAtqa
        );
}

phStatus_t phpalI14443p3a_Rd710_WakeUpA(
                                        phpalI14443p3a_Rd710_DataParams_t * pDataParams,
                                        uint8_t * pAtqa
                                        )
{
    return phhalHw_Rd710_Cmd_I14443P3A_WakeUpA(
        pDataParams->pHalDataParams,
        pAtqa
        );
}

phStatus_t phpalI14443p3a_Rd710_HaltA(
                                      phpalI14443p3a_Rd710_DataParams_t * pDataParams
                                      )
{
    return phhalHw_Rd710_Cmd_I14443P3A_HaltA(
        pDataParams->pHalDataParams
        );
}

phStatus_t phpalI14443p3a_Rd710_Anticollision(
    phpalI14443p3a_Rd710_DataParams_t * pDataParams,
    uint8_t bCascadeLevel,
    uint8_t * pUidIn,
    uint8_t bNvbUidIn,
    uint8_t * pUidOut,
    uint8_t * pNvbUidOut
    )
{
    return phhalHw_Rd710_Cmd_I14443P3A_Anticollision(
        pDataParams->pHalDataParams,
        bCascadeLevel,
        pUidIn,
        bNvbUidIn,
        pUidOut,
        pNvbUidOut
        );
}

phStatus_t phpalI14443p3a_Rd710_Select(
                                       phpalI14443p3a_Rd710_DataParams_t * pDataParams,
                                       uint8_t bCascadeLevel,
                                       uint8_t * pUidIn,
                                       uint8_t * pSak
                                       )
{
    return phhalHw_Rd710_Cmd_I14443P3A_Select(
        pDataParams->pHalDataParams,
        bCascadeLevel,
        pUidIn,
        pSak
        );
}

phStatus_t phpalI14443p3a_Rd710_ActivateCard(
    phpalI14443p3a_Rd710_DataParams_t * pDataParams,
    uint8_t * pUidIn,
    uint8_t bLenUidIn,
    uint8_t * pUidOut,
    uint8_t * pLenUidOut,
    uint8_t * pSak,
    uint8_t * pMoreCardsAvailable
    )
{
    return phhalHw_Rd710_Cmd_I14443P3A_ActivateCard(
        pDataParams->pHalDataParams,
        pUidIn,
        bLenUidIn,
        pUidOut,
        pLenUidOut,
        pSak,
        pMoreCardsAvailable
        );
}

phStatus_t phpalI14443p3a_Rd710_Exchange(
    phpalI14443p3a_Rd710_DataParams_t * pDataParams,
    uint16_t wOption,
    uint8_t * pTxBuffer,
    uint16_t wTxLength,
    uint8_t ** ppRxBuffer,
    uint16_t * pRxLength
    )
{
    return phhalHw_Rd710_Cmd_I14443P3A_Exchange(
        pDataParams->pHalDataParams,
        wOption,
        pTxBuffer,
        wTxLength,
        ppRxBuffer,
        pRxLength
        );
}

phStatus_t phpalI14443p3a_Rd710_GetSerialNo(
    phpalI14443p3a_Rd710_DataParams_t * pDataParams,
    uint8_t * pRxBuffer,
    uint8_t * pRxLength
    )
{
    return phhalHw_Rd710_Cmd_I14443P3A_GetSerialNo(
        pDataParams->pHalDataParams,
        pRxBuffer,
        pRxLength
        );
}

#endif /* NXPBUILD__PHPAL_I14443P3A_RD710 */
