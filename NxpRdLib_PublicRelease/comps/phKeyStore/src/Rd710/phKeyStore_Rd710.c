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
* Rc632 Keystore Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:27:53 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#include <ph_Status.h>
#include <ph_RefDefs.h>
#include <phKeyStore.h>
#include <phhalHw.h>

#ifdef NXPBUILD__PH_KEYSTORE_RD710

#include <phhalHw_Rd710_Cmd.h>
#include "phKeyStore_Rd710.h"
#include "../phKeyStore_Int.h"

phStatus_t phKeyStore_Rd710_Init(
                                 phKeyStore_Rd710_DataParams_t * pDataParams,
                                 uint16_t wSizeOfDataParams, 
                                 phhalHw_Rd710_DataParams_t * pHalDataParams
                                 )
{
    if (sizeof(phKeyStore_Rd710_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
    }
    PH_ASSERT_NULL (pDataParams);
    PH_ASSERT_NULL (pHalDataParams);

    /* Init private data */
    pDataParams->wId			= PH_COMP_KEYSTORE| PH_KEYSTORE_RD710_ID;
    pDataParams->pHalDataParams = pHalDataParams;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Rd710_FormatKeyEntry(
    phKeyStore_Rd710_DataParams_t * pDataParams,
    uint16_t wKeyNo,
    uint16_t wNewKeyType 
    )
{
    return phhalHw_Rd710_Cmd_KS_FormatKeyEntry(
        pDataParams->pHalDataParams,
        wKeyNo,
        wNewKeyType);
}

phStatus_t phKeyStore_Rd710_SetKey(
                                   phKeyStore_Rd710_DataParams_t * pDataParams,
                                   uint16_t wKeyNo,
                                   uint16_t wKeyVersion,
                                   uint16_t wKeyType,
                                   uint8_t * pNewKey,
                                   uint16_t wNewKeyVersion
                                   )
{
    uint16_t PH_MEMLOC_REM wKeyLength;

    /* Retrieve KeyLength */
    wKeyLength = phKeyStore_GetKeySize(wKeyType);
    if (!wKeyLength)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
    }

    return phhalHw_Rd710_Cmd_KS_SetKey(
        pDataParams->pHalDataParams, 
        wKeyType,
        wKeyNo,
        wKeyVersion,
		wNewKeyVersion,
        wKeyLength,
		pNewKey);
}

phStatus_t phKeyStore_Rd710_SetKeyAtPos(
                                        phKeyStore_Rd710_DataParams_t * pDataParams,
                                        uint16_t wKeyNo,
                                        uint16_t wPos,
                                        uint16_t wKeyType,
                                        uint8_t * pNewKey,
                                        uint16_t wNewKeyVersion
                                        )
{
    uint16_t PH_MEMLOC_REM wKeyLength;

    /* Retrieve KeyLength */
    wKeyLength = phKeyStore_GetKeySize(wKeyType);
    if (!wKeyLength)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
    }

    return phhalHw_Rd710_Cmd_KS_SetKey(
        pDataParams->pHalDataParams, 
        wKeyType,
        wKeyNo,
        wPos,
		wNewKeyVersion,
        wKeyLength,
		pNewKey);
}

phStatus_t phKeyStore_Rd710_SetKUC(
                                   phKeyStore_Rd710_DataParams_t * pDataParams,
                                   uint16_t wKeyNo,
                                   uint16_t wRefNoKUC
                                   )
{
    return phhalHw_Rd710_Cmd_KS_SetKUC(
        pDataParams->pHalDataParams,
        wKeyNo,
        wRefNoKUC);
}

phStatus_t phKeyStore_Rd710_SetFullKeyEntry(
    phKeyStore_Rd710_DataParams_t * pDataParams,
    uint16_t wNoOfKeys,
    uint16_t wKeyNo,
    uint16_t wNewRefNoKUC,
    uint16_t wNewKeyType,
    uint8_t * pNewKeys,
    uint16_t * pNewKeyVersionList
    )
{
    uint16_t PH_MEMLOC_REM wKeyLength;

    /* Retrieve KeyLength */
    wKeyLength = phKeyStore_GetKeySize(wNewKeyType);
    if (!wKeyLength)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
    }

    return phhalHw_Rd710_Cmd_KS_SetFullKeyEntry(
        pDataParams->pHalDataParams,
        wNoOfKeys,
        wNewKeyType,
        wKeyNo,
        wNewRefNoKUC,
		wKeyLength,
        pNewKeys,
        pNewKeyVersionList);
}

phStatus_t phKeyStore_Rd710_GetKeyEntry(
                                        phKeyStore_Rd710_DataParams_t * pDataParams,    
                                        uint16_t wKeyNo,
                                        uint16_t wKeyVersionBufSize,
                                        uint16_t * wKeyVersion,
                                        uint16_t * wKeyVersionLength,
                                        uint16_t * pKeyType
                                        )
{
    return phhalHw_Rd710_Cmd_KS_GetKeyEntry(
        pDataParams->pHalDataParams,    
        wKeyNo,
        wKeyVersionBufSize,
        wKeyVersion,
        wKeyVersionLength,
        pKeyType);
}

phStatus_t phKeyStore_Rd710_GetKey(
                                   phKeyStore_Rd710_DataParams_t * pDataParams,    
                                   uint16_t wKeyNo,
                                   uint16_t wKeyVersion,
                                   uint8_t bKeyBufSize,
                                   uint8_t * pKey,
                                   uint16_t * pKeyType
                                   )
{
    return phhalHw_Rd710_Cmd_KS_GetKey(
        pDataParams->pHalDataParams,    
        wKeyNo,
        wKeyVersion,
        bKeyBufSize,
        pKey,
        pKeyType);
}

phStatus_t phKeyStore_Rd710_SetConfig(
                                      phKeyStore_Rd710_DataParams_t * pDataParams,
                                      uint16_t wConfig,
                                      uint16_t wValue
                                      )
{
    return phhalHw_Rd710_Cmd_KS_SetConfig(
        pDataParams->pHalDataParams,
        wConfig,
        wValue);
}

phStatus_t phKeyStore_Rd710_SetConfigStr(
    phKeyStore_Rd710_DataParams_t * pDataParams,
    uint16_t wConfig,
    uint8_t *pBuffer,
    uint16_t wBufferLength
    )
{
    return phhalHw_Rd710_Cmd_KS_SetConfigStr(
        pDataParams->pHalDataParams,
        wConfig,
        pBuffer,
        wBufferLength);
}

phStatus_t phKeyStore_Rd710_GetConfig(
                                      phKeyStore_Rd710_DataParams_t * pDataParams,
                                      uint16_t wConfig,
                                      uint16_t * pValue
                                      )
{
    return phhalHw_Rd710_Cmd_KS_GetConfig(
        pDataParams->pHalDataParams,
        wConfig,
        pValue);
}

phStatus_t phKeyStore_Rd710_GetConfigStr(
    phKeyStore_Rd710_DataParams_t * pDataParams,
    uint16_t wConfig,
    uint8_t ** ppBuffer,
    uint16_t * pBufferLength
    )
{
    return phhalHw_Rd710_Cmd_KS_GetConfigStr(
        pDataParams->pHalDataParams,
        wConfig,
        ppBuffer,
        pBufferLength);
}

phStatus_t phKeyStore_Rd710_ChangeKUC(
                                      phKeyStore_Rd710_DataParams_t * pDataParams,                    
                                      uint16_t wRefNoKUC,
                                      uint32_t dwLimit
                                      )
{
    return phhalHw_Rd710_Cmd_KS_ChangeKUC(
        pDataParams->pHalDataParams,                    
        wRefNoKUC,
        dwLimit);
}

phStatus_t phKeyStore_Rd710_GetKUC(
                                   phKeyStore_Rd710_DataParams_t * pDataParams,
                                   uint16_t wRefNoKUC,
                                   uint32_t * pdwLimit,
                                   uint32_t * pdwCurVal
                                   )
{
    return phhalHw_Rd710_Cmd_KS_GetKUC(
        pDataParams->pHalDataParams,
        wRefNoKUC,
        pdwLimit,
        pdwCurVal);
}

#endif /* NXPBUILD__PH_KEYSTORE_RD710 */
