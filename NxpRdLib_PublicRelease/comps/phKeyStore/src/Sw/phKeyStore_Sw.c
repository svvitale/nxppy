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
* Software Keystore Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:27:56 2011 $
*
* History:
*  CHu: Generated 29. May 2009
*
*/

#include <ph_Status.h>
#include <phKeyStore.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PH_KEYSTORE_SW

#include "phKeyStore_Sw.h"
#include "phKeyStore_Sw_Int.h"
#include "../phKeyStore_Int.h"

phStatus_t phKeyStore_Sw_Init(
                              phKeyStore_Sw_DataParams_t * pDataParams,
                              uint16_t wSizeOfDataParams, 
                              phKeyStore_Sw_KeyEntry_t * pKeyEntries, 
                              uint16_t wNoOfKeyEntries, 
                              phKeyStore_Sw_KeyVersionPair_t * pKeyVersionPairs,
                              uint16_t wNoOfVersionPairs,
                              phKeyStore_Sw_KUCEntry_t * pKUCEntries,
                              uint16_t wNoOfKUCEntries
                              )
{
    uint16_t i;
    uint16_t j;
    phStatus_t statusTmp;
    phKeyStore_Sw_KeyVersionPair_t * pKeyVersion;

    if (sizeof(phKeyStore_Sw_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
    }
	PH_ASSERT_NULL (pDataParams);
	PH_ASSERT_NULL (pKeyEntries);
	PH_ASSERT_NULL (pKeyVersionPairs);
	PH_ASSERT_NULL (pKUCEntries);

    /* Init private data */
    pDataParams->wId = PH_COMP_KEYSTORE | PH_KEYSTORE_SW_ID;
    pDataParams->pKeyEntries = pKeyEntries;
    pDataParams->pKeyVersionPairs = pKeyVersionPairs;
    pDataParams->wNoOfKeyEntries = wNoOfKeyEntries;
    pDataParams->wNoOfVersions = wNoOfVersionPairs;
    pDataParams->pKUCEntries = pKUCEntries;
    pDataParams->wNoOfKUCEntries = wNoOfKUCEntries;

    for (i = 0; i < pDataParams->wNoOfKeyEntries; i++)
    {
        pDataParams->pKeyEntries[i].wKeyType = PH_KEYSTORE_INVALID_ID;
        pDataParams->pKeyEntries[i].wRefNoKUC = PH_KEYSTORE_INVALID_ID;

        for (j = 0; j < pDataParams->wNoOfVersions; j++)
        {      
            PH_CHECK_SUCCESS_FCT(statusTmp, phKeyStore_Sw_GetKeyValuePtrPos(pDataParams, i, j, &pKeyVersion));
            pKeyVersion->wVersion = PH_KEYSTORE_DEFAULT_ID;
        }
    }

    for (i = 0; i < pDataParams->wNoOfKUCEntries; i++)
    {
        pDataParams->pKUCEntries[i].dwLimit = 0xFFFFFFFF;
        pDataParams->pKUCEntries[i].dwCurVal = 0;
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Sw_FormatKeyEntry(
                                        phKeyStore_Sw_DataParams_t * pDataParams,                /**< [In] Pointer to this layer's parameter structure. */                           
                                        uint16_t wKeyNo,                /**< [In] KeyEntry number to be Formatted (0x00 to F0). */
                                        uint16_t wNewKeyType            /**< [In] New Key type of the KeyEntry (predefined type of KeyType).*/ 
                                        )
{
    phStatus_t statusTmp;
    uint8_t    i;
	phKeyStore_Sw_KeyVersionPair_t * pKeyVersion;
    /* Overflow checks */
    if (wKeyNo >= pDataParams->wNoOfKeyEntries)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
    }

    switch(wNewKeyType)
    {
    case PH_KEYSTORE_KEY_TYPE_AES128:
    case PH_KEYSTORE_KEY_TYPE_DES:
    case PH_KEYSTORE_KEY_TYPE_2K3DES:
    case PH_KEYSTORE_KEY_TYPE_MIFARE:
    case PH_KEYSTORE_KEY_TYPE_AES192:
    case PH_KEYSTORE_KEY_TYPE_3K3DES:
    case PH_KEYSTORE_KEY_TYPE_AES256:
        break;
    default:
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
	}

    pDataParams->pKeyEntries[wKeyNo].wKeyType = wNewKeyType;

    /* Reset CEK to master Key */
    pDataParams->pKeyEntries[wKeyNo].wRefNoKUC = PH_KEYSTORE_INVALID_ID;

    /* Reset all keys to 0x00*/
    for (i = 0; i < pDataParams->wNoOfVersions; ++i)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phKeyStore_Sw_GetKeyValuePtrPos(pDataParams,wKeyNo,i,&pKeyVersion));
        pKeyVersion->wVersion = 0;
        memset(pKeyVersion->pKey, 0x00, PH_KEYSTORE_SW_MAX_KEY_SIZE); /* PRQA S 3200 */
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_KEYSTORE);

}


phStatus_t phKeyStore_Sw_SetKey(
                                phKeyStore_Sw_DataParams_t * pDataParams,
                                uint16_t wKeyNo,
                                uint16_t wKeyVersion,
                                uint16_t wKeyType,
                                uint8_t * pNewKey,
                                uint16_t wNewKeyVersion
                                )
{
    phStatus_t statusTmp;
    phKeyStore_Sw_KeyVersionPair_t * pKeyVersion;
    PH_CHECK_SUCCESS_FCT(statusTmp, phKeyStore_Sw_GetKeyValuePtrVersion(pDataParams,wKeyNo,wKeyVersion,&pKeyVersion));

    /* Check that Key type matches with current Key Type format */
    if (pDataParams->pKeyEntries[wKeyNo].wKeyType != wKeyType)
	{
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
	}

	/* copy the key and version */
    memcpy(pKeyVersion->pKey, pNewKey, phKeyStore_GetKeySize(wKeyType)); /* PRQA S 3200 */
    pKeyVersion->wVersion = wNewKeyVersion;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Sw_SetKeyAtPos(
                                     phKeyStore_Sw_DataParams_t * pDataParams,
                                     uint16_t wKeyNo,
                                     uint16_t wPos,
                                     uint16_t wKeyType,
                                     uint8_t * pNewKey,
                                     uint16_t wNewKeyVersion
                                     )
{

    phStatus_t statusTmp;
    phKeyStore_Sw_KeyVersionPair_t * pKeyVersion;
    PH_CHECK_SUCCESS_FCT(statusTmp, phKeyStore_Sw_GetKeyValuePtrPos(pDataParams,wKeyNo,wPos,&pKeyVersion));

    /* Check that Key type matches with current Key Type format */
    if (pDataParams->pKeyEntries[wKeyNo].wKeyType != wKeyType)
	{
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
	}

	/* copy the key and version */
    memcpy(pKeyVersion->pKey, pNewKey, phKeyStore_GetKeySize(wKeyType)); /* PRQA S 3200 */
    pKeyVersion->wVersion = wNewKeyVersion;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Sw_SetKUC(
                                phKeyStore_Sw_DataParams_t * pDataParams,
                                uint16_t wKeyNo,
                                uint16_t wRefNoKUC
                                )
{
    /* Overflow checks */
    if (wKeyNo >= pDataParams->wNoOfKeyEntries)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
    }
    /* Check for a valid KUC entry */
    if (wRefNoKUC >= pDataParams->wNoOfKUCEntries)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
    }
    pDataParams->pKeyEntries[wKeyNo].wRefNoKUC = wRefNoKUC;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_KEYSTORE);

}

phStatus_t phKeyStore_Sw_SetFullKeyEntry(
    phKeyStore_Sw_DataParams_t * pDataParams,
    uint16_t wNoOfKeys,
    uint16_t wKeyNo,
    uint16_t wNewRefNoKUC,
    uint16_t wNewKeyType,
    uint8_t * pNewKeys,
    uint16_t * pNewKeyVersionList
    )
{
    phStatus_t statusTmp;
    uint8_t    i;
    uint8_t bKeyLength;
    phKeyStore_Sw_KeyVersionPair_t * pKeyVersion;

    /* Overflow checks */
    if (wKeyNo >= pDataParams->wNoOfKeyEntries)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
    }
    /* Check for a valid KUC entry */
    if (wNewRefNoKUC >= pDataParams->wNoOfKUCEntries)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
    }
    /* Overflow checks */
    if (wNoOfKeys > pDataParams->wNoOfVersions)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
    }

    switch(wNewKeyType)
    {
		case PH_KEYSTORE_KEY_TYPE_AES128:
		case PH_KEYSTORE_KEY_TYPE_2K3DES:
		case PH_KEYSTORE_KEY_TYPE_AES192:
		case PH_KEYSTORE_KEY_TYPE_3K3DES:
		case PH_KEYSTORE_KEY_TYPE_AES256:
		case PH_KEYSTORE_KEY_TYPE_DES:
		case PH_KEYSTORE_KEY_TYPE_MIFARE:
			bKeyLength = (uint8_t)phKeyStore_GetKeySize(wNewKeyType);
			break;

		default:
			return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
    }

    pDataParams->pKeyEntries[wKeyNo].wKeyType = wNewKeyType;

    /* Reset KUC to master Key */
    pDataParams->pKeyEntries[wKeyNo].wRefNoKUC = wNewRefNoKUC;

    /* Reset all keys to 0x00*/
    for (i=0; i < wNoOfKeys ; i++)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phKeyStore_Sw_GetKeyValuePtrPos(pDataParams,wKeyNo,i,&pKeyVersion));
        pKeyVersion->wVersion = pNewKeyVersionList[i];
        memcpy(pKeyVersion->pKey, &pNewKeys[i*bKeyLength], bKeyLength); /* PRQA S 3200 */
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Sw_GetKeyEntry(
                                     phKeyStore_Sw_DataParams_t * pDataParams,    
                                     uint16_t wKeyNo,
                                     uint16_t wKeyVersionBufSize,
                                     uint16_t * wKeyVersion,
                                     uint16_t * wKeyVersionLength,
                                     uint16_t * pKeyType
                                     )
{
    phStatus_t statusTmp;
    uint16_t i;
    phKeyStore_Sw_KeyVersionPair_t * pKeyVersion;

    /* Check for overflow */
    if (wKeyVersionBufSize < (sizeof(uint16_t) * pDataParams->wNoOfVersions))
    {
        return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_KEYSTORE);
    }

    for (i = 0; i < pDataParams->wNoOfVersions; i++)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phKeyStore_Sw_GetKeyValuePtrPos(pDataParams,wKeyNo,i,&pKeyVersion));
        wKeyVersion[i] = pKeyVersion->wVersion;
    }
    *wKeyVersionLength = pDataParams->wNoOfVersions;
    *pKeyType = pDataParams->pKeyEntries[wKeyNo].wKeyType;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Sw_GetKey(
                                phKeyStore_Sw_DataParams_t * pDataParams,    
                                uint16_t wKeyNo,
                                uint16_t wKeyVersion,
                                uint8_t bKeyBufSize,
                                uint8_t * pKey,
                                uint16_t * pKeyType
                                )
{
    phStatus_t statusTmp;
	uint16_t wKeySize;
    phKeyStore_Sw_KeyVersionPair_t * pKeyVersion;
    PH_CHECK_SUCCESS_FCT(statusTmp, phKeyStore_Sw_GetKeyValuePtrVersion(pDataParams,wKeyNo,wKeyVersion,&pKeyVersion));

    /* Check for Counter overflow */
    PH_CHECK_SUCCESS_FCT(statusTmp, phKeyStore_Sw_CheckUpdateKUC(pDataParams,pDataParams->pKeyEntries[wKeyNo].wRefNoKUC));

	/* check buffer size */
	wKeySize = phKeyStore_GetKeySize(pDataParams->pKeyEntries[wKeyNo].wKeyType);
    if (bKeyBufSize < wKeySize)
    {
        return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_KEYSTORE);
    }
	/* copy the key */
    memcpy(pKey, pKeyVersion->pKey, wKeySize); /* PRQA S 3200 */

	*pKeyType = pDataParams->pKeyEntries[wKeyNo].wKeyType;
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Sw_SetConfig(
                                   phKeyStore_Sw_DataParams_t * pDataParams,
                                   uint16_t wConfig,
                                   uint16_t wValue
                                   )
{
    /* satisfy compiler */
    if (pDataParams || wConfig || wValue);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Sw_SetConfigStr(
                                      phKeyStore_Sw_DataParams_t * pDataParams,
                                      uint16_t wConfig,
                                      uint8_t *pBuffer,
                                      uint16_t wBufferLength
                                      )
{
    /* satisfy compiler */
    if (pDataParams || wConfig || pBuffer || wBufferLength);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_KEYSTORE);
}


phStatus_t phKeyStore_Sw_GetConfig(
                                   phKeyStore_Sw_DataParams_t * pDataParams,
                                   uint16_t wConfig,
                                   uint16_t * pValue
                                   )
{
    /* satisfy compiler */
    if (pDataParams || wConfig || pValue);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Sw_GetConfigStr(
                                      phKeyStore_Sw_DataParams_t * pDataParams,
                                      uint16_t wConfig,
                                      uint8_t ** ppBuffer,
                                      uint16_t * pBufferLength
                                      )
{
    /* satisfy compiler */
    if (pDataParams || wConfig || ppBuffer || pBufferLength);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_KEYSTORE);
}


phStatus_t phKeyStore_Sw_GetKeyValuePtrPos(
    phKeyStore_Sw_DataParams_t * pDataParams,
    uint16_t wKeyNumber,
    uint16_t wPos,
    phKeyStore_Sw_KeyVersionPair_t ** pKeyVersion
    )
{
    *pKeyVersion = NULL;
    /* Overflow checks */
    if (wKeyNumber >= pDataParams->wNoOfKeyEntries)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
    }

    /* Overflow checks */
    if (wPos >= pDataParams->wNoOfVersions)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
    }

    *pKeyVersion = &pDataParams->pKeyVersionPairs[wKeyNumber * pDataParams->wNoOfVersions + wPos]; 

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Sw_GetKeyValuePtrVersion(
    phKeyStore_Sw_DataParams_t * pDataParams,
    uint16_t wKeyNumber,
    uint16_t wKeyVersion,
    phKeyStore_Sw_KeyVersionPair_t ** pKeyVersion
    )
{
    uint16_t i;
    *pKeyVersion = NULL;
    /* Overflow checks */
    if (wKeyNumber >= pDataParams->wNoOfKeyEntries)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
    }

    for (i=0;i<pDataParams->wNoOfVersions; i++)
    {
        *pKeyVersion = &pDataParams->pKeyVersionPairs[wKeyNumber * pDataParams->wNoOfVersions + i];
        if ((*pKeyVersion)->wVersion == wKeyVersion)
        {
            break;
        }
    }
    /* No entry found */
    if (i == pDataParams->wNoOfVersions)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);   
    }
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Sw_CheckUpdateKUC(
                                        phKeyStore_Sw_DataParams_t * pDataParams,
                                        uint16_t wKeyUsageCtrNumber
                                        )
{
    if (wKeyUsageCtrNumber != PH_KEYSTORE_INVALID_ID)
    {
        /* Check for a valid KUC entry */
        if (wKeyUsageCtrNumber >= pDataParams->wNoOfKUCEntries)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
        }

        /* Now let's check the limit*/
        if (pDataParams->pKUCEntries[wKeyUsageCtrNumber].dwCurVal >= pDataParams->pKUCEntries[wKeyUsageCtrNumber].dwLimit)
        {
            return PH_ADD_COMPCODE(PH_ERR_KEY, PH_COMP_KEYSTORE);
        }
        pDataParams->pKUCEntries[wKeyUsageCtrNumber].dwCurVal++;
    }   
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Sw_ChangeKUC(
                                   phKeyStore_Sw_DataParams_t * pDataParams,                    
                                   uint16_t wRefNoKUC,
                                   uint32_t dwLimit
                                   )
{
    /* Overflow checks */
    if (wRefNoKUC >= pDataParams->wNoOfKUCEntries)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
    }
    pDataParams->pKUCEntries[wRefNoKUC].dwLimit = dwLimit;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Sw_GetKUC(
                                phKeyStore_Sw_DataParams_t * pDataParams,
                                uint16_t wRefNoKUC,
                                uint32_t * pdwLimit,
                                uint32_t * pdwCurVal
                                )
{
    /* Overflow checks */
    if (wRefNoKUC >= pDataParams->wNoOfKUCEntries)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
    }

    *pdwLimit = pDataParams->pKUCEntries[wRefNoKUC].dwLimit;
    *pdwCurVal = pDataParams->pKUCEntries[wRefNoKUC].dwCurVal;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_KEYSTORE);
}

#endif /* NXPBUILD__PH_KEYSTORE_SW */
