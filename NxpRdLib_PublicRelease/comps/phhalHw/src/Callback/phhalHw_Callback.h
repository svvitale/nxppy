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
* Callback HAL-Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:28:03 2011 $
*
* History:
*  CHu: Generated 17. July 2009
*
*/

#ifndef PHHALHW_CALLBACK_H
#define PHHALHW_CALLBACK_H

#include <ph_Status.h>
#include <phhalHw.h>

phStatus_t phhalHw_Callback_Exchange(
                                     phhalHw_Callback_DataParams_t * pDataParams,
                                     uint16_t wOption,
                                     uint8_t * pTxBuffer,
                                     uint16_t wTxLength,
                                     uint8_t ** ppRxBuffer,
                                     uint16_t * pRxLength
                                     );

phStatus_t phhalHw_Callback_Command(
                                    phhalHw_Callback_DataParams_t * pDataParams,
                                    uint8_t bCmd,
                                    uint16_t wOption, 
                                    uint8_t * pTxBuffer,
                                    uint16_t wTxLength,
                                    uint8_t ** ppRxBuffer,
                                    uint16_t * pRxLength
                                    );

phStatus_t phhalHw_Callback_WriteRegister(
    phhalHw_Callback_DataParams_t * pDataParams,
    uint8_t bAddress,
    uint8_t bValue
    );

phStatus_t phhalHw_Callback_ReadRegister(
    phhalHw_Callback_DataParams_t * pDataParams,
    uint8_t bAddress,
    uint8_t * pValue
    );

phStatus_t phhalHw_Callback_ApplyProtocolSettings(
    phhalHw_Callback_DataParams_t * pDataParams,
    uint8_t bCardType
    );

phStatus_t phhalHw_Callback_MfcAuthenticateKeyNo(
    phhalHw_Callback_DataParams_t * pDataParams,
    uint8_t bBlockNo,
    uint8_t bKeyType,
    uint16_t wKeyNo,
    uint16_t wKeyVersion,
    uint8_t * pUid
    );

phStatus_t phhalHw_Callback_MfcAuthenticate(
    phhalHw_Callback_DataParams_t * pDataParams,
    uint8_t bBlockNo,
    uint8_t bKeyType,
    uint8_t * pKey,
    uint8_t * pUid
    );

phStatus_t phhalHw_Callback_SetConfig(
                                      phhalHw_Callback_DataParams_t * pDataParams,
                                      uint16_t wConfig,
                                      uint16_t wValue
                                      );

phStatus_t phhalHw_Callback_GetConfig(
                                      phhalHw_Callback_DataParams_t * pDataParams,
                                      uint16_t wConfig,
                                      uint16_t * pValue
                                      );

phStatus_t phhalHw_Callback_FieldOn(
                                    phhalHw_Callback_DataParams_t * pDataParams
                                    );

phStatus_t phhalHw_Callback_FieldOff(
                                     phhalHw_Callback_DataParams_t * pDataParams
                                     );

phStatus_t phhalHw_Callback_FieldReset(
                                       phhalHw_Callback_DataParams_t * pDataParams
                                       );

phStatus_t phhalHw_Callback_Wait(
                                 phhalHw_Callback_DataParams_t * pDataParams,
                                 uint8_t bUnit,
                                 uint16_t wTimeout
                                 );

#endif
