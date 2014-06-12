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
* Stub MIFARE(R) Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:26:50 2011 $
*
* History:
*  CHu: Generated 21. October 2009
*
*/

#ifndef PHPALMIFARE_STUB_H
#define PHPALMIFARE_STUB_H

#include <ph_Status.h>

phStatus_t phpalMifare_Stub_ExchangeL3(
                                       phpalMifare_Stub_DataParams_t * pDataParams,
                                       uint16_t wOption,
                                       uint8_t * pTxBuffer,
                                       uint16_t wTxLength,
                                       uint8_t ** ppRxBuffer,
                                       uint16_t * pRxLength
                                       );

phStatus_t phpalMifare_Stub_ExchangeL4(
                                       phpalMifare_Stub_DataParams_t * pDataParams,
                                       uint16_t wOption,
                                       uint8_t * pTxBuffer,
                                       uint16_t wTxLength,
                                       uint8_t ** ppRxBuffer,
                                       uint16_t * pRxLength
                                       );

phStatus_t phpalMifare_Stub_ExchangePc(
                                       phpalMifare_Stub_DataParams_t * pDataParams,
                                       uint16_t wOption,
                                       uint8_t * pTxBuffer,
                                       uint16_t wTxLength,
                                       uint8_t ** ppRxBuffer,
                                       uint16_t * pRxLength
                                       );

phStatus_t phpalMifare_Stub_ExchangeRaw(
                                        phpalMifare_Stub_DataParams_t * pDataParams,
                                        uint16_t wOption,
                                        uint8_t * pTxBuffer,
                                        uint16_t wTxLength,
                                        uint8_t bTxLastBits,
                                        uint8_t ** ppRxBuffer,
                                        uint16_t * pRxLength,
                                        uint8_t * pRxLastBits
                                        );

phStatus_t phpalMifare_Stub_MfcAuthenticateKeyNo(
    phpalMifare_Stub_DataParams_t * pDataParams,
    uint8_t bBlockNo,
    uint8_t bKeyType,
    uint16_t wKeyNo,
    uint16_t wKeyVersion,
    uint8_t * pUid
    );

phStatus_t  phpalMifare_Stub_MfcAuthenticate(
    phpalMifare_Stub_DataParams_t * pDataParams,
    uint8_t bBlockNo,
    uint8_t bKeyType,
    uint8_t * pKey,
    uint8_t * pUid
    );

#endif /* PHPALMIFARE_STUB_H */
