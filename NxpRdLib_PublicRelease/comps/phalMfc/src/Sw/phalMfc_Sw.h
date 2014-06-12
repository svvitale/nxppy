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
* Software MIFARE(R) Application Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:04:56 2011 $
*
* History:
*  CHu: Generated 31. July 2009
*
*/

#ifndef PHALMFC_SW_H
#define PHALMFC_SW_H

#include <ph_Status.h>
#include <phalMfc.h>

phStatus_t phalMfc_Sw_Authenticate(
                                   phalMfc_Sw_DataParams_t * pDataParams,
                                   uint8_t bBlockNo,
                                   uint8_t bKeyType, 
                                   uint16_t wKeyNumber,
                                   uint16_t wKeyVersion,
                                   uint8_t * pUid,
                                   uint8_t bUidLength
                                   );

phStatus_t phalMfc_Sw_Read(
                           phalMfc_Sw_DataParams_t * pDataParams,
                           uint8_t bBlockNo,
                           uint8_t * pBlockData
                           );

phStatus_t phalMfc_Sw_ReadValue(
                                phalMfc_Sw_DataParams_t * pDataParams,
                                uint8_t bBlockNo,
                                uint8_t * pValue,
                                uint8_t * pAddrData
                                );

phStatus_t phalMfc_Sw_Write(
                            phalMfc_Sw_DataParams_t * pDataParams,
                            uint8_t bBlockNo,
                            uint8_t * pBlockData
                            );

phStatus_t phalMfc_Sw_WriteValue(
                                 phalMfc_Sw_DataParams_t * pDataParams,
                                 uint8_t bBlockNo,
                                 uint8_t * pValue,
                                 uint8_t bAddrData
                                 );

phStatus_t phalMfc_Sw_Increment(
                                phalMfc_Sw_DataParams_t * pDataParams,
                                uint8_t bBlockNo,
                                uint8_t * pValue
                                );

phStatus_t phalMfc_Sw_Decrement(
                                phalMfc_Sw_DataParams_t * pDataParams, 
                                uint8_t bBlockNo,
                                uint8_t * pValue
                                );

phStatus_t phalMfc_Sw_Transfer(
                               phalMfc_Sw_DataParams_t * pDataParams, 
                               uint8_t bBlockNo
                               );

phStatus_t phalMfc_Sw_Restore(
                              phalMfc_Sw_DataParams_t * pDataParams,
                              uint8_t bBlockNo
                              );

phStatus_t phalMfc_Sw_IncrementTransfer(
                                        phalMfc_Sw_DataParams_t * pDataParams,
                                        uint8_t bSrcBlockNo,
                                        uint8_t bDstBlockNo,
                                        uint8_t * pValue
                                        );

phStatus_t phalMfc_Sw_DecrementTransfer(
                                        phalMfc_Sw_DataParams_t * pDataParams,
                                        uint8_t bSrcBlockNo,
                                        uint8_t bDstBlockNo,
                                        uint8_t * pValue
                                        );

phStatus_t phalMfc_Sw_RestoreTransfer(
                                      phalMfc_Sw_DataParams_t * pDataParams,
                                      uint8_t bSrcBlockNo,
                                      uint8_t bDstBlockNo
                                      );

phStatus_t phalMfc_Sw_PersonalizeUid(
                                     phalMfc_Sw_DataParams_t * pDataParams,
                                     uint8_t bUidType
                                     );

#endif /* PHALMFC_SW_H */
