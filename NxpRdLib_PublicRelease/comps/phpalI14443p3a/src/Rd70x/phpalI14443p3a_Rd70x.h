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
* $Date: Fri Apr 15 09:28:02 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHPALI14443P3A_RD70X_H
#define PHPALI14443P3A_RD70X_H

#include <ph_Status.h>

phStatus_t phpalI14443p3a_Rd70x_RequestA(
                phpalI14443p3a_Rd70x_DataParams_t * pDataParams,
                uint8_t * pAtqa
                );

phStatus_t phpalI14443p3a_Rd70x_WakeUpA(
                phpalI14443p3a_Rd70x_DataParams_t * pDataParams,
                uint8_t * pAtqa
                );

phStatus_t phpalI14443p3a_Rd70x_HaltA(
                phpalI14443p3a_Rd70x_DataParams_t * pDataParams
                );

phStatus_t phpalI14443p3a_Rd70x_Anticollision(
                phpalI14443p3a_Rd70x_DataParams_t * pDataParams,
                uint8_t bCascadeLevel,
                uint8_t * pUidIn,
                uint8_t bNvbUidIn,
                uint8_t * pUidOut,
                uint8_t * pNvbUidOut
                );

phStatus_t phpalI14443p3a_Rd70x_Select(
                phpalI14443p3a_Rd70x_DataParams_t * pDataParams,
                uint8_t bCascadeLevel,
                uint8_t * pUidIn,
                uint8_t * pSak
                );

phStatus_t phpalI14443p3a_Rd70x_ActivateCard(
                phpalI14443p3a_Rd70x_DataParams_t * pDataParams,
                uint8_t * pUidIn,
                uint8_t bLenUidIn,
                uint8_t * pUidOut,
                uint8_t * pLenUidOut,
                uint8_t * pSak,
                uint8_t * pMoreCardsAvailable
                );

phStatus_t phpalI14443p3a_Rd70x_Exchange(
                phpalI14443p3a_Rd70x_DataParams_t * pDataParams,
                uint16_t wOption,
                uint8_t * pTxBuffer,                                
                uint16_t wTxLength,
                uint8_t ** ppRxBuffer,
                uint16_t * pRxLength
                );

phStatus_t phpalI14443p3a_Rd70x_GetSerialNo(
                phpalI14443p3a_Rd70x_DataParams_t * pDataParams,
                uint8_t * pRxBuffer,
                uint8_t * pRxLength
                );

#endif /* PHPALI14443P3A_RD70X_H */
