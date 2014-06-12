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
* Software ICode EPC/UID Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:26:23 2011 $
*
* History:
*  CHu: Generated 8. September 2009
*
*/

#ifndef PHPALEPCUID_SW_H
#define PHPALEPCUID_SW_H

#include <ph_Status.h>

phStatus_t phpalEpcUid_Sw_ActivateCard(
                                       phpalEpcUid_Sw_DataParams_t * pDataParams,
                                       uint8_t bTagType,
                                       uint8_t bNumSlots,
                                       uint8_t * pMask,
                                       uint8_t bMaskLength,
                                       uint8_t bHash,
                                       uint8_t * pRxBuffer,
                                       uint8_t * pRxLength,
                                       uint8_t * pMoreCardsAvailable
                                       );

phStatus_t phpalEpcUid_Sw_BeginRound(
                                     phpalEpcUid_Sw_DataParams_t * pDataParams,
                                     uint8_t bTagType,
                                     uint8_t bNumSlots,
                                     uint8_t * pMask,
                                     uint8_t bMaskLength,
                                     uint8_t bHash,
                                     uint8_t * pRxBuffer,
                                     uint8_t * pRxLength
                                     );

phStatus_t phpalEpcUid_Sw_CloseSlot(
                                    phpalEpcUid_Sw_DataParams_t * pDataParams,
                                    uint8_t bOption,
                                    uint8_t * pRxBuffer,
                                    uint8_t * pRxLength
                                    );

phStatus_t phpalEpcUid_Sw_FixSlot(
                                  phpalEpcUid_Sw_DataParams_t * pDataParams,
                                  uint8_t bTagType,
                                  uint8_t * pMask,
                                  uint8_t bMaskLength
                                  );

phStatus_t phpalEpcUid_Sw_Write(
                                phpalEpcUid_Sw_DataParams_t * pDataParams,
                                uint8_t bTagType,
                                uint8_t bBlockNo,
                                uint8_t bData 
                                );

phStatus_t phpalEpcUid_Sw_Destroy(
                                  phpalEpcUid_Sw_DataParams_t * pDataParams,
                                  uint8_t bTagType,
                                  uint8_t * pData,
                                  uint8_t bDataLength,
                                  uint8_t * pDestroyCode
                                  );

phStatus_t phpalEpcUid_Sw_GetSerialNo(
                                      phpalEpcUid_Sw_DataParams_t * pDataParams,
                                      uint8_t * pUidOut,
                                      uint8_t * pLenUidOut
                                      );

#endif /* PHPALEPCUID_SW_H */
