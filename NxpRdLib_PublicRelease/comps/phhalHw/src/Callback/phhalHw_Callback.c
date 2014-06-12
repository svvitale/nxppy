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
* RC523 specific HAL-Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:28:03 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#include <ph_Status.h>
#include <phhalHw.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHHAL_HW_CALLBACK

#include "phhalHw_Callback.h"

phStatus_t phhalHw_Callback_Init(
                                 phhalHw_Callback_DataParams_t * pDataParams,
                                 uint16_t wSizeOfDataParams,
                                 cbExchange pExchangeCb,
                                 cbWriteRegister pWriteRegisterCb,
                                 cbReadRegister pReadRegisterCb,
                                 cbApplyProtocolSettings pApplyProtocolSettingsCb,
                                 cbMfcAuthenticate pMfcAuthenticateCb,
                                 cbMfcAuthenticateKey pMfcAuthenticateKeyCb,
                                 cbSetConfig pSetConfigCb,
                                 cbGetConfig pGetConfigCb,
                                 cbFieldOn pFieldOnCb,
                                 cbFieldOff pFieldOffCb,
                                 cbFieldReset pFieldResetCb,
                                 cbWait pWaitCb,
                                 void * pCallbackContext
                                 )
{
    if (sizeof(phhalHw_Callback_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_HAL);
    }
	PH_ASSERT_NULL (pDataParams);

    pDataParams->wId                = PH_COMP_HAL | PHHAL_HW_CALLBACK_ID;
    pDataParams->pExchangeCb        = pExchangeCb;
    pDataParams->pWriteRegisterCb   = pWriteRegisterCb;
    pDataParams->pReadRegisterCb    = pReadRegisterCb;
    pDataParams->pApplyProtocolSettingsCb = pApplyProtocolSettingsCb;
    pDataParams->pMfcAuthenticateCb = pMfcAuthenticateCb;
    pDataParams->pMfcAuthenticateKeyCb = pMfcAuthenticateKeyCb;
    pDataParams->pSetConfigCb       = pSetConfigCb;
    pDataParams->pGetConfigCb       = pGetConfigCb;
    pDataParams->pFieldOnCb         = pFieldOnCb;
    pDataParams->pFieldOffCb        = pFieldOffCb;
    pDataParams->pFieldResetCb      = pFieldResetCb;
    pDataParams->pWaitCb            = pWaitCb;
    pDataParams->pCbContext         = pCallbackContext;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Callback_Exchange(
                                     phhalHw_Callback_DataParams_t * pDataParams,
                                     uint16_t wOption,
                                     uint8_t * pTxBuffer,
                                     uint16_t wTxLength,
                                     uint8_t ** ppRxBuffer,
                                     uint16_t * pRxLength
                                     )
{
	uint16_t	PH_MEMLOC_REM RxLength;
	uint8_t *	PH_MEMLOC_REM pRxBuffer;

	/* Check if caller has provided valid RxBuffer */
	if (ppRxBuffer == NULL)
	{
		ppRxBuffer = &pRxBuffer;
	}
	if (pRxLength == NULL)
	{
		pRxLength = &RxLength;
	}

    if (pDataParams->pExchangeCb == NULL)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_HAL);
    }

    return (*pDataParams->pExchangeCb)(wOption, pTxBuffer, wTxLength, ppRxBuffer, pRxLength, pDataParams->pCbContext);
}

phStatus_t phhalHw_Callback_WriteRegister(
    phhalHw_Callback_DataParams_t * pDataParams,
    uint8_t bAddress,
    uint8_t bValue
    )
{
    if (pDataParams->pWriteRegisterCb)
    {
        return (*pDataParams->pWriteRegisterCb)(bAddress, bValue, pDataParams->pCbContext);
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_HAL);
    }
}

phStatus_t phhalHw_Callback_ReadRegister(
    phhalHw_Callback_DataParams_t * pDataParams,
    uint8_t bAddress,
    uint8_t * pValue
    )
{
    if (pDataParams->pReadRegisterCb)
    {
        return (*pDataParams->pReadRegisterCb)(bAddress, pValue, pDataParams->pCbContext);
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_HAL);
    }
}

phStatus_t phhalHw_Callback_ApplyProtocolSettings(
    phhalHw_Callback_DataParams_t * pDataParams,
    uint8_t bCardType
    )
{
    if (pDataParams->pApplyProtocolSettingsCb)
    {
        return (*pDataParams->pApplyProtocolSettingsCb)(bCardType, pDataParams->pCbContext);
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
    }
}

phStatus_t phhalHw_Callback_MfcAuthenticateKeyNo(
    phhalHw_Callback_DataParams_t * pDataParams,
    uint8_t bBlockNo,
    uint8_t bKeyType,
    uint16_t wKeyNo,
    uint16_t wKeyVersion,
    uint8_t * pUid
    )
{
    if (pDataParams->pMfcAuthenticateCb)
    {
        return (*pDataParams->pMfcAuthenticateCb)(bBlockNo, bKeyType, wKeyNo, wKeyVersion, pUid, pDataParams->pCbContext);
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
    }
}

phStatus_t phhalHw_Callback_MfcAuthenticate(
    phhalHw_Callback_DataParams_t * pDataParams,
    uint8_t bBlockNo,
    uint8_t bKeyType,
    uint8_t * pKey,
    uint8_t * pUid
    )
{
    if (pDataParams->pMfcAuthenticateKeyCb)
    {
        return (*pDataParams->pMfcAuthenticateKeyCb)(bBlockNo, bKeyType, pKey, pUid, pDataParams->pCbContext);
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
    }
}

phStatus_t phhalHw_Callback_SetConfig(
                                      phhalHw_Callback_DataParams_t * pDataParams,
                                      uint16_t wConfig,
                                      uint16_t wValue
                                      )
{
    if (pDataParams->pSetConfigCb)
    {
        return (*pDataParams->pSetConfigCb)(wConfig, wValue, pDataParams->pCbContext);
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
    }
}

phStatus_t phhalHw_Callback_GetConfig(
                                      phhalHw_Callback_DataParams_t * pDataParams,
                                      uint16_t wConfig,
                                      uint16_t * pValue
                                      )
{
    if (pDataParams->pGetConfigCb)
    {
        return (*pDataParams->pGetConfigCb)(wConfig, pValue, pDataParams->pCbContext);
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
    }
}

phStatus_t phhalHw_Callback_FieldOn(
                                    phhalHw_Callback_DataParams_t * pDataParams
                                    )
{
    if (pDataParams->pFieldOnCb)
    {
        return (*pDataParams->pFieldOnCb)(pDataParams->pCbContext);
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
    }
}

phStatus_t phhalHw_Callback_FieldOff(
                                     phhalHw_Callback_DataParams_t * pDataParams
                                     )
{
    if (pDataParams->pFieldOffCb)
    {
        return (*pDataParams->pFieldOffCb)(pDataParams->pCbContext);
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
    }
}

phStatus_t phhalHw_Callback_FieldReset(
                                       phhalHw_Callback_DataParams_t * pDataParams
                                       )
{
    if (pDataParams->pFieldResetCb)
    {
        return (*pDataParams->pFieldResetCb)(pDataParams->pCbContext);
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
    }
}

phStatus_t phhalHw_Callback_Wait(
                                 phhalHw_Callback_DataParams_t * pDataParams,
                                 uint8_t bUnit,
                                 uint16_t wTimeout
                                 )
{
    if (pDataParams->pWaitCb)
    {
        return (*pDataParams->pWaitCb)(bUnit, wTimeout, pDataParams->pCbContext);
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_HAL);
    }
}

#endif /* NXPBUILD__PHHAL_HW_CALLBACK */
