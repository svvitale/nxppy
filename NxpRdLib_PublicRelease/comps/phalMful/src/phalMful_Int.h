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
* Internal functions of Software implementation of MIFARE (R) Ultralight application layer.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:26:24 2011 $
*
* History:
*  CHu: Generated 05. October 2009
*
*/

#ifndef PHALMFUL_INT_H
#define PHALMFUL_INT_H

#include <ph_Status.h>

/** \addtogroup ph_Private
* @{
*/

#define PHAL_MFUL_RESP_ACK      0x0AU   /**< MIFARE Ultralight ACK response code */
#define PHAL_MFUL_RESP_NAK0     0x00U   /**< MIFARE Ultralight NAK0 response code */
#define PHAL_MFUL_RESP_NAK1     0x01U   /**< MIFARE Ultralight NAK1 response code */
#define PHAL_MFUL_RESP_NAK4     0x04U   /**< MIFARE Ultralight NAK4 response code */
#define PHAL_MFUL_RESP_NAK5     0x05U   /**< MIFARE Ultralight NAK5 response code */

#define PHAL_MFUL_CMD_READ      0x30U   /**< MIFARE Ultralight Read command byte */
#define PHAL_MFUL_CMD_COMPWRITE 0xA0U   /**< MIFARE Ultralight Compatibility Write command byte */
#define PHAL_MFUL_CMD_WRITE     0xA2U   /**< MIFARE Ultralight Write command byte */
#define PHAL_MFUL_CMD_AUTH      0x1AU   /**< MIFARE Ultralight Authenticate command byte */

#define PHAL_MFUL_PREAMBLE_TX   0xAFU   /**< MIFARE Ultralight preamble byte (tx) for authentication. */
#define PHAL_MFUL_PREAMBLE_RX   0x00U   /**< MIFARE Ultralight preamble byte (rx) for authentication. */

#define PHAL_MFUL_COMPWRITE_BLOCK_LENGTH    16U /**< Length of a compatibility write MIFARE(R) Ultralight data block. */

/** @} */

phStatus_t phalMful_Int_Read(
                             void * pPalMifareDataParams,
                             uint8_t bAddress,
                             uint8_t * pData
                             );

phStatus_t phalMful_Int_Write(
                              void * pPalMifareDataParams,
                              uint8_t bAddress,
                              uint8_t * pData
                              );

phStatus_t phalMful_Int_CompatibilityWrite(
    void * pPalMifareDataParams,
    uint8_t bAddress,
    uint8_t * pData
    );

#endif /* PHALMFUL_INT_H */
