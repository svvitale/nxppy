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
* Software ISO14443-3B Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:26:31 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHPALI14443P3B_SW_H
#define PHPALI14443P3B_SW_H

#include <ph_Status.h>

#define PHPAL_I14443P3B_NUMSLOTS_1      0x00U   /**< Use 1 slot for anticollision. */
#define PHPAL_I14443P3B_NUMSLOTS_2      0x01U   /**< Use 2 slots for anticollision. */
#define PHPAL_I14443P3B_NUMSLOTS_4      0x02U   /**< Use 4 slots for anticollision. */
#define PHPAL_I14443P3B_NUMSLOTS_8      0x03U   /**< Use 8 slots for anticollision. */
#define PHPAL_I14443P3B_NUMSLOTS_16     0x04U   /**< Use 16 slots for anticollision. */

phStatus_t phpalI14443p3b_Sw_SetConfig(
                                    phpalI14443p3b_Sw_DataParams_t * pDataParams,  /**< [In] Pointer to this layers parameter structure. */
                                    uint16_t wConfig,    /**< [In]  */
                                    uint16_t wValue      /**< [In]  */
                                   );

phStatus_t phpalI14443p3b_Sw_GetConfig(
                                    phpalI14443p3b_Sw_DataParams_t * pDataParams,  /**< [In] Pointer to this layers parameter structure. */
                                    uint16_t wConfig,    /**< [In]  */
                                    uint16_t* pValue     /**< [In]  */
                                   );

phStatus_t phpalI14443p3b_Sw_RequestB(
                                      phpalI14443p3b_Sw_DataParams_t * pDataParams,
                                      uint8_t bNumSlots,
                                      uint8_t bAfi,
                                      uint8_t bExtAtqb,
                                      uint8_t * pAtqb,
                                      uint8_t * pAtqbLen
                                      );

phStatus_t phpalI14443p3b_Sw_WakeUpB(
                                     phpalI14443p3b_Sw_DataParams_t * pDataParams,
                                     uint8_t bNumSlots,
                                     uint8_t bAfi,
                                     uint8_t bExtAtqb,
                                     uint8_t * pAtqb,
                                     uint8_t * pAtqbLen
                                     );

phStatus_t phpalI14443p3b_Sw_SlotMarker(
                                        phpalI14443p3b_Sw_DataParams_t * pDataParams,
                                        uint8_t bSlotNumber,
                                        uint8_t * pAtqb,
                                        uint8_t * pAtqbLen
                                        );

phStatus_t phpalI14443p3b_Sw_HaltB(
                                   phpalI14443p3b_Sw_DataParams_t * pDataParams
                                   );

phStatus_t phpalI14443p3b_Sw_Attrib(
                                    phpalI14443p3b_Sw_DataParams_t * pDataParams,
                                    uint8_t * pAtqb,
                                    uint8_t bAtqbLen,
                                    uint8_t bFsdi,
                                    uint8_t bCid,
                                    uint8_t bDri,
                                    uint8_t bDsi,
                                    uint8_t * pMbli
                                    );

phStatus_t phpalI14443p3b_Sw_ActivateCard(
    phpalI14443p3b_Sw_DataParams_t * pDataParams,
    uint8_t * pPupi,
    uint8_t bPupiLength,
    uint8_t bNumSlots,
    uint8_t bAfi,
    uint8_t bExtAtqb,
    uint8_t bFsdi,
    uint8_t bCid,
    uint8_t bDri,
    uint8_t bDsi,
    uint8_t * pAtqb,
    uint8_t * pAtqbLen,
    uint8_t * pMbli,
    uint8_t * pMoreCardsAvailable
    );

phStatus_t phpalI14443p3b_Sw_Exchange(
                                      phpalI14443p3b_Sw_DataParams_t * pDataParams,
                                      uint16_t wOption,
                                      uint8_t * pTxBuffer,
                                      uint16_t wTxLength,
                                      uint8_t ** ppRxBuffer,
                                      uint16_t * pRxLength
                                      );

phStatus_t phpalI14443p3b_Sw_GetSerialNo(
    phpalI14443p3b_Sw_DataParams_t * pDataParams,
    uint8_t * pPupi
    );

phStatus_t phpalI14443p3b_Sw_SetHigherLayerInf(
    phpalI14443p3b_Sw_DataParams_t * pDataParams,
    uint8_t * pTxBuffer,
    uint16_t  wTxLength,
    uint8_t * pRxBuffer,
    uint16_t wRxBufSize
    );

phStatus_t phpalI14443p3b_Sw_GetHigherLayerResp(
    phpalI14443p3b_Sw_DataParams_t * pDataParams,
    uint8_t ** ppRxBuffer,
    uint16_t * pRxLength
    );

phStatus_t phpalI14443p3b_Sw_GetProtocolParams(
    phpalI14443p3b_Sw_DataParams_t * pDataParams,
    uint8_t * pCidEnabled,
    uint8_t * pCid,
    uint8_t * pNadSupported,
    uint8_t * pFwi,
    uint8_t * pFsdi,
    uint8_t * pFsci
    );

#endif /* PHPALI14443P3B_SW_H */
