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
* Software MIFARE(R) Ultralight Component of Reader Library Framework.
* $Author: jayaprakash.desai $
* $Revision: 1.6 $
* $Date: Wed May 25 14:06:23 2011 $
*
* History:
*  CHu: Generated 05. October 2009
*
*/

#include <ph_Status.h>
#include <phalMful.h>
#include <phpalMifare.h>
#include <phKeyStore.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHAL_MFUL_SW

#include "phalMful_Sw.h"
#include "../phalMful_Int.h"

/*
* Private constants
*/
static const uint8_t PH_MEMLOC_CONST_ROM phalMful_Sw_FirstIv[PHAL_MFUL_DES_BLOCK_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

phStatus_t phalMful_Sw_Init(
                            phalMful_Sw_DataParams_t * pDataParams,
                            uint16_t wSizeOfDataParams,
                            void * pPalMifareDataParams,
                            void * pKeyStoreDataParams,
                            void * pCryptoDataParams,
                            void * pCryptoRngDataParams
                            )
{
    if (sizeof(phalMful_Sw_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_AL_MFUL);
    }
    PH_ASSERT_NULL (pDataParams);
    PH_ASSERT_NULL (pPalMifareDataParams);

    /* init private data */
    pDataParams->wId                    = PH_COMP_AL_MFUL | PHAL_MFUL_SW_ID;
    pDataParams->pPalMifareDataParams   = pPalMifareDataParams;
    pDataParams->pKeyStoreDataParams    = pKeyStoreDataParams;
    pDataParams->pCryptoDataParams      = pCryptoDataParams;
    pDataParams->pCryptoRngDataParams   = pCryptoRngDataParams;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_AL_MFUL);
}

phStatus_t phalMful_Sw_UlcAuthenticate(
                                       phalMful_Sw_DataParams_t * pDataParams,
                                       uint16_t wKeyNumber,
                                       uint16_t wKeyVersion
                                       )
{
#ifndef NXPBUILD__PH_CRYPTOSYM
    /* satisfy compiler */
    if (pDataParams || wKeyNumber || wKeyVersion);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_AL_MFUL);
#endif
}

phStatus_t phalMful_Sw_Read(
                            phalMful_Sw_DataParams_t * pDataParams,
                            uint8_t bAddress,
                            uint8_t * pData
                            )
{
    return phalMful_Int_Read(pDataParams->pPalMifareDataParams, bAddress, pData);
}

phStatus_t phalMful_Sw_Write(
                             phalMful_Sw_DataParams_t * pDataParams,
                             uint8_t bAddress,
                             uint8_t * pData
                             )
{
    return phalMful_Int_Write(pDataParams->pPalMifareDataParams, bAddress, pData);
}

phStatus_t phalMful_Sw_CompatibilityWrite(
    phalMful_Sw_DataParams_t * pDataParams,
    uint8_t bAddress,
    uint8_t * pData
    )
{
    return phalMful_Int_CompatibilityWrite(pDataParams->pPalMifareDataParams, bAddress, pData);
}

#endif /* NXPBUILD__PHAL_MFUL_SW */
