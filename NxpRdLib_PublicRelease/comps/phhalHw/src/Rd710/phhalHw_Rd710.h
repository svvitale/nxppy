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
* Rd710 specific HAL-Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:27:42 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHHALHW_RD710_H
#define PHHALHW_RD710_H

#include <ph_Status.h>
#include "phhalHw.h"

phStatus_t phhalHw_Rd710_Exchange(
                                  phhalHw_Rd710_DataParams_t * pDataParams,
                                  uint16_t wOption,
                                  uint8_t * pTxBuffer,
                                  uint16_t wTxLength,
                                  uint8_t ** ppRxBuffer,
                                  uint16_t * pRxLength
                                  );

phStatus_t phhalHw_Rd710_Command(
                                 phhalHw_Rd710_DataParams_t * pDataParams,
                                 uint8_t bCmd,
                                 uint16_t wOption, 
                                 uint8_t * pTxBuffer,
                                 uint16_t wTxLength,
                                 uint8_t ** ppRxBuffer,
                                 uint16_t * pRxLength
                                 );

phStatus_t phhalHw_Rd710_WriteRegister(
                                       phhalHw_Rd710_DataParams_t * pDataParams,
                                       uint8_t bAddress,
                                       uint8_t bValue
                                       );

phStatus_t phhalHw_Rd710_ReadRegister(
                                      phhalHw_Rd710_DataParams_t * pDataParams,
                                      uint8_t bAddress,
                                      uint8_t * pValue
                                      );

phStatus_t phhalHw_Rd710_ApplyProtocolSettings(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint8_t bCardType
    );

phStatus_t phhalHw_Rd710_MfcAuthenticateKeyNo(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint8_t bBlockNo,
    uint8_t bKeyType,
    uint16_t wKeyNo,
    uint16_t wKeyVersion,
    uint8_t * pUid
    );

phStatus_t phhalHw_Rd710_MfcAuthenticate(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint8_t bBlockNo,
    uint8_t bKeyType,
    uint8_t * pKey,
    uint8_t * pUid
    );

phStatus_t phhalHw_Rd710_SetConfig(
                                   phhalHw_Rd710_DataParams_t * pDataParams,
                                   uint16_t wConfig,
                                   uint16_t wValue
                                   );

phStatus_t phhalHw_Rd710_GetConfig(
                                   phhalHw_Rd710_DataParams_t * pDataParams,
                                   uint16_t wConfig,
                                   uint16_t * pValue
                                   );

phStatus_t phhalHw_Rd710_FieldOn(
                                 phhalHw_Rd710_DataParams_t * pDataParams
                                 );

phStatus_t phhalHw_Rd710_FieldOff(
                                  phhalHw_Rd710_DataParams_t * pDataParams
                                  );

phStatus_t phhalHw_Rd710_FieldReset(
                                    phhalHw_Rd710_DataParams_t * pDataParams
                                    );

phStatus_t phhalHw_Rd710_Wait(
                              phhalHw_Rd710_DataParams_t * pDataParams,
                              uint8_t bUnit,
                              uint16_t wTimeout
                              );

#endif /* PHHALHW_RD710_H */
