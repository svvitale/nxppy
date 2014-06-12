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
* Software ISO18092 passive initiator mode Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.1 $
* $Date: Fri Apr 15 09:29:15 2011 $
*
* History:
*  CEn: Generated 07. September 2010
*/

#ifndef PHPALI18092MPI_SW_H
#define PHPALI18092MPI_SW_H

#include <ph_Status.h>
#include <phpalI18092mPI.h>

phStatus_t phpalI18092mPI_Sw_ResetProtocol(
    phpalI18092mPI_Sw_DataParams_t * pDataParams
    );

phStatus_t phpalI18092mPI_Sw_Atr(
                                 phpalI18092mPI_Sw_DataParams_t * pDataParams,
                                 uint8_t * pNfcid3i,
                                 uint8_t bDid,
                                 uint8_t bLri,
                                 uint8_t bNadEnabled,
                                 uint8_t bNad,
                                 uint8_t * pGi,
                                 uint8_t bGiLength,
                                 uint8_t * pAtrRes,
                                 uint8_t * pAtrResLength
                                 );

phStatus_t phpalI18092mPI_Sw_Psl(
                                 phpalI18092mPI_Sw_DataParams_t * pDataParams,
                                 uint8_t bDsi,
                                 uint8_t bDri,
                                 uint8_t bFsl
                                 );

phStatus_t phpalI18092mPI_Sw_ActivateCard(
    phpalI18092mPI_Sw_DataParams_t * pDataParams,
    uint8_t * pNfcid3i,
    uint8_t bDid,
    uint8_t bNadEnable,
    uint8_t bNad,
    uint8_t bDsi,
    uint8_t bDri,
    uint8_t bFsl,
    uint8_t * pGi,
    uint8_t bGiLength,
    uint8_t * pAtrRes,
    uint8_t * pAtrResLength
    );

phStatus_t phpalI18092mPI_Sw_Deselect(
                                      phpalI18092mPI_Sw_DataParams_t * pDataParams,
                                      uint8_t bDeselectCommand
                                      );

phStatus_t phpalI18092mPI_Sw_PresCheck(
                                       phpalI18092mPI_Sw_DataParams_t * pDataParams
                                       );

phStatus_t phpalI18092mPI_Sw_Exchange(
                                      phpalI18092mPI_Sw_DataParams_t * pDataParams,
                                      uint16_t wOption,
                                      uint8_t * pTxBuffer,
                                      uint16_t wTxLength,
                                      uint8_t ** ppRxBuffer,
                                      uint16_t * pRxLength
                                      );

phStatus_t phpalI18092mPI_Sw_GetSerialNo(
    phpalI18092mPI_Sw_DataParams_t * pDataParams,
    uint8_t * pNfcId3Out
    );

phStatus_t phpalI18092mPI_Sw_SetConfig(
                                       phpalI18092mPI_Sw_DataParams_t * pDataParams,
                                       uint16_t wConfig,
                                       uint16_t wValue
                                       );

phStatus_t phpalI18092mPI_Sw_GetConfig(
                                       phpalI18092mPI_Sw_DataParams_t * pDataParams,
                                       uint16_t wConfig,
                                       uint16_t * pValue
                                       );

#endif /* PHPALI18092MPI_SW_H */
