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
* $Date: Fri Apr 15 09:26:55 2011 $
*
* History:
*  RSn: Generated 21. October 2009
*
*/

#ifndef PHPALSLI15693_SW_H
#define PHPALSLI15693_SW_H

#include <ph_Status.h>

phStatus_t phpalSli15693_Sw_Inventory(
                                      phpalSli15693_Sw_DataParams_t * pDataParams,
                                      uint8_t bFlags,
                                      uint8_t bAfi,
                                      uint8_t * pMask,
                                      uint8_t bMaskBitLength,
                                      uint8_t * pDsfid,
                                      uint8_t * pUid
                                      );
phStatus_t phpalSli15693_Sw_SendEof(
                                    phpalSli15693_Sw_DataParams_t * pDataParams,
                                    uint8_t bOption,                                   
                                    uint8_t * pDsfid,
                                    uint8_t * pUid,
                                    uint8_t * pUidLength,
                                    uint8_t * pData,
                                    uint16_t * pDataLength
                                    );

phStatus_t phpalSli15693_Sw_StayQuiet(
                                      phpalSli15693_Sw_DataParams_t * pDataParams
                                      );

phStatus_t phpalSli15693_Sw_Select(
                                   phpalSli15693_Sw_DataParams_t * pDataParams
                                   );

phStatus_t phpalSli15693_Sw_ResetToReady(
    phpalSli15693_Sw_DataParams_t * pDataParams
    );

phStatus_t phpalSli15693_Sw_Exchange(
                                     phpalSli15693_Sw_DataParams_t * pDataParams,
                                     uint16_t wOption,
                                     uint8_t * pTxBuffer,
                                     uint16_t wTxLength,
                                     uint8_t ** ppRxBuffer,
                                     uint16_t * pRxLength
                                     );

phStatus_t phpalSli15693_Sw_ActivateCard(
    phpalSli15693_Sw_DataParams_t * pDataParams,
    uint8_t  bOption,
    uint8_t bFlags,
    uint8_t bAfi,
    uint8_t * pMask,
    uint8_t MaskBitLength,
    uint8_t * pDsfid,
    uint8_t * pUid,
    uint8_t * pMoreCardsAvailable
    );

phStatus_t phpalSli15693_Sw_GetSerialNo(
                                        phpalSli15693_Sw_DataParams_t * pDataParams,
                                        uint8_t * pUid,
                                        uint8_t * bUidLength
                                        );

phStatus_t phpalSli15693_Sw_SetConfig(
                                      phpalSli15693_Sw_DataParams_t * pDataParams,
                                      uint16_t wConfig,
                                      uint16_t wValue
                                      );

phStatus_t phpalSli15693_Sw_GetConfig(
                                      phpalSli15693_Sw_DataParams_t * pDataParams,
                                      uint16_t wConfig,
                                      uint16_t * pValue
                                      );

phStatus_t phpalSli15693_Sw_InventoryRead(
    phpalSli15693_Sw_DataParams_t * pDataParams,
    uint8_t bFlags,
    uint8_t bAfi,
    uint8_t * pMask,
    uint8_t bMaskBitLength,
    uint8_t bBlockNo,
    uint16_t wNoOfBlocks,
    uint8_t * pUid,
    uint8_t * pUidLength,
    uint8_t * pData,
    uint16_t * pDataLength
    );

phStatus_t phpalSli15693_Sw_FastInventoryRead(
    phpalSli15693_Sw_DataParams_t * pDataParams,
    uint8_t bFlags,
    uint8_t bAfi,
    uint8_t * pMask,
    uint8_t bMaskBitLength,
    uint8_t bBlockNo,
    uint16_t wNoOfBlocks,
    uint8_t * pUid,
    uint8_t * pUidLength,
    uint8_t * pData,
    uint16_t * pDataLength
    );

phStatus_t phpalSli15693_Sw_InventoryPageRead(
    phpalSli15693_Sw_DataParams_t * pDataParams,
    uint8_t bFlags,
    uint8_t bAfi,
    uint8_t * pMask,
    uint8_t bMaskBitLength,
    uint8_t bPageNo,
    uint16_t wNoOfPages,
    uint8_t * pUid,
    uint8_t * pUidLength,
    uint8_t * pData,
    uint16_t * pDataLength
    );

phStatus_t phpalSli15693_Sw_FastInventoryPageRead(
    phpalSli15693_Sw_DataParams_t * pDataParams,
    uint8_t bFlags,
    uint8_t bAfi,
    uint8_t * pMask,
    uint8_t bMaskBitLength,
    uint8_t bPageNo,
    uint16_t wNoOfPages,
    uint8_t * pUid,
    uint8_t * pUidLength,
    uint8_t * pData,
    uint16_t * pDataLength
    );

#endif /* PHPALSLI15693_SW_H */
