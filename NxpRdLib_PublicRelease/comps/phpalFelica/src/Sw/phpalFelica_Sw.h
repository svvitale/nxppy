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
* Software Felica Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.1 $
* $Date: Fri Apr 15 09:29:08 2011 $
*
* History:
*  RSn: Generated 26. January 2010
*
*/

#ifndef PHPALFELICA_SW_H
#define PHPALFELICA_SW_H

#include <ph_Status.h>

phStatus_t phpalFelica_Sw_ReqC(
                               phpalFelica_Sw_DataParams_t* pDataParams,
                               uint8_t* pSystemCode,
                               uint8_t bTimeSlot,
                               uint8_t* pRxBuffer
                               );

phStatus_t phpalFelica_Sw_ActivateCard(
                                       phpalFelica_Sw_DataParams_t* pDataParams,
                                       uint8_t * pIDmPMm,
                                       uint8_t bIDmPMmLength, 
                                       uint8_t* pSystemCode,
                                       uint8_t bTimeSlot,
                                       uint8_t* pRxBuffer,
                                       uint8_t* pRxLength,
                                       uint8_t* pMoreCardsAvailable
                                       );

phStatus_t phpalFelica_Sw_Exchange(
                                   phpalFelica_Sw_DataParams_t* pDataParams,
                                   uint16_t wOption,
                                   uint16_t wN,
                                   uint8_t* pTxBuffer,
                                   uint16_t wTxLength,
                                   uint8_t** ppRxBuffer,
                                   uint16_t* pRxLength
                                   );

phStatus_t phpalFelica_Sw_GetSerialNo(
                                      phpalFelica_Sw_DataParams_t* pDataParams,
                                      uint8_t * pIDmPMmOut,
                                      uint8_t * pLenIDmPMmOut
                                      );


#endif /* PHPALFELICA_SW_H */
