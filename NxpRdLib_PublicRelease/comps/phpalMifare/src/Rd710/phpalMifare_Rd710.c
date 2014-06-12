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
* Rd710 MIFARE(R) Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:27:05 2011 $
*
* History:
*  CHu: Generated 31. July 2009
*
*/

#include <phpalMifare.h>
#include <ph_RefDefs.h>
#include <phTools.h>

#ifdef NXPBUILD__PHPAL_MIFARE_RD710

#include "../phpalMifare_Int.h"
#include "phpalMifare_Rd710.h"
#include <phhalHw_Rd710_Cmd.h>

phStatus_t phpalMifare_Rd710_Init(
                                  phpalMifare_Rd710_DataParams_t * pDataParams,
                                  uint16_t wSizeOfDataParams,
                                  phhalHw_Rd710_DataParams_t * pHalDataParams
                                  )
{
    if (sizeof(phpalMifare_Rd710_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_MIFARE);
    }
    PH_ASSERT_NULL (pDataParams);
    PH_ASSERT_NULL (pHalDataParams);

    /* init private data */
    pDataParams->wId                    = PH_COMP_PAL_MIFARE | PHPAL_MIFARE_RD710_ID;
    pDataParams->pHalDataParams         = pHalDataParams;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_MIFARE);
}

phStatus_t phpalMifare_Rd710_ExchangeL3(
                                        phpalMifare_Rd710_DataParams_t * pDataParams,
                                        uint16_t wOption,
                                        uint8_t * pTxBuffer,
                                        uint16_t wTxLength,
                                        uint8_t ** ppRxBuffer,
                                        uint16_t * pRxLength
                                        )
{
    return phhalHw_Rd710_Cmd_MIFARE_ExchangeL3(
        pDataParams->pHalDataParams,
        wOption,
        pTxBuffer,
        wTxLength,
        ppRxBuffer,
        pRxLength
        );
}

phStatus_t phpalMifare_Rd710_ExchangeL4(
                                        phpalMifare_Rd710_DataParams_t * pDataParams,
                                        uint16_t wOption,
                                        uint8_t * pTxBuffer,
                                        uint16_t wTxLength,
                                        uint8_t ** ppRxBuffer,
                                        uint16_t * pRxLength
                                        )
{
    return phhalHw_Rd710_Cmd_MIFARE_ExchangeL4(
        pDataParams->pHalDataParams,
        wOption,
        pTxBuffer,
        wTxLength,
        ppRxBuffer,
        pRxLength
        );
}

phStatus_t phpalMifare_Rd710_ExchangePc(
                                        phpalMifare_Rd710_DataParams_t * pDataParams,
                                        uint16_t wOption,
                                        uint8_t * pTxBuffer,
                                        uint16_t wTxLength,
                                        uint8_t ** ppRxBuffer,
                                        uint16_t * pRxLength
                                        )
{
    return phhalHw_Rd710_Cmd_MIFARE_ExchangePc(
        pDataParams->pHalDataParams,
        wOption,
        pTxBuffer,
        wTxLength,
        ppRxBuffer,
        pRxLength
        );
}

phStatus_t phpalMifare_Rd710_ExchangeRaw(
    phpalMifare_Rd710_DataParams_t * pDataParams,
    uint16_t wOption,
    uint8_t * pTxBuffer,
    uint16_t wTxLength,
    uint8_t bTxLastBits,
    uint8_t ** ppRxBuffer,
    uint16_t * pRxLength,
    uint8_t * pRxLastBits
    )
{
    return phhalHw_Rd710_Cmd_MIFARE_ExchangeRaw(
        pDataParams->pHalDataParams,
        wOption,
        pTxBuffer,
        wTxLength,
        bTxLastBits,
        ppRxBuffer,
        pRxLength,
        pRxLastBits
        );
}

phStatus_t phpalMifare_Rd710_MfcAuthenticateKeyNo(
    phpalMifare_Rd710_DataParams_t * pDataParams,
    uint8_t bBlockNo,
    uint8_t bKeyType,
    uint16_t wKeyNo,
    uint16_t wKeyVersion,
    uint8_t * pUid
    )
{    
    return phhalHw_Rd710_Cmd_MIFARE_MfcAuthenticateKeyNo(
        pDataParams->pHalDataParams,
        bBlockNo,
        bKeyType,
        wKeyNo,
        wKeyVersion,
        pUid);
}

phStatus_t phpalMifare_Rd710_MfcAuthenticate(
    phpalMifare_Rd710_DataParams_t * pDataParams,
    uint8_t bBlockNo,
    uint8_t bKeyType,
    uint8_t * pKey,
    uint8_t * pUid
    )
{
    return phhalHw_Rd710_Cmd_MIFARE_MfcAuthenticate(
        pDataParams->pHalDataParams,
        bBlockNo,
        bKeyType,
        pKey,
        pUid);
}

#endif /* NXPBUILD__PHPAL_MIFARE_RD710 */
