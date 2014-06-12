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
* Internal functions for MIFARE (R) application layer.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:27:41 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHALMFC_INT_H
#define PHALMFC_INT_H

#include <ph_Status.h>

/** \addtogroup ph_Private
* @{
*/

#define PHAL_MFC_RESP_ACK       0x0A    /**< MIFARE Classic ACK response code */
#define PHAL_MFC_RESP_NAK0      0x00    /**< MIFARE Classic NAK0 response code */
#define PHAL_MFC_RESP_NAK1      0x01    /**< MIFARE Classic NAK1 response code */
#define PHAL_MFC_RESP_NAK4      0x04    /**< MIFARE Classic NAK4 response code */
#define PHAL_MFC_RESP_NAK5      0x05    /**< MIFARE Classic NAK5 response code */

#define PHAL_MFC_CMD_RESTORE    0xC2    /**< MIFARE Classic Restore command byte */
#define PHAL_MFC_CMD_INCREMENT  0xC1    /**< MIFARE Classic Increment command byte */
#define PHAL_MFC_CMD_DECREMENT  0xC0    /**< MIFARE Classic Decrement command byte */
#define PHAL_MFC_CMD_TRANSFER   0xB0    /**< MIFARE Classic Transfer command byte */
#define PHAL_MFC_CMD_READ       0x30    /**< MIFARE Classic Read command byte */
#define PHAL_MFC_CMD_WRITE      0xA0    /**< MIFARE Classic Write command byte */
#define PHAL_MFC_CMD_AUTHA      0x60    /**< MIFARE Classic Authenticate A command byte */
#define PHAL_MFC_CMD_AUTHB      0x61    /**< MIFARE Classic Authenticate B command byte */
#define PHAL_MFC_CMD_PERSOUID   0x40    /**< MIFARE Classic Personalize UID command */

/**
* \brief Perform MIFARE(R) Transfer command with MIFARE Picc.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phalMfc_Int_Transfer(
                                void * pPalMifareDataParams,    /**< [In] Pointer to a palMifare component context. */
                                uint8_t bBlockNo                /**< [In] block number the transfer buffer shall be transferred to. */
                                );

/**
* \brief Perform a MIFARE(R) Value operation with MIFARE Picc.
*
* This is used by INCREMENT, DECREMENT and RESTORE commands.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phalMfc_Int_Value(
                             void * pPalMifareDataParams,   /**< [In] Pointer to a palMifare component context. */
                             uint8_t bCmdCode,              /**< [In] Command Code - INC/DEC or RST. */
                             uint8_t bBlockNo,              /**< [In] Block Number. */
                             uint8_t * pValue               /**< [In] Value; (Needs to be zero in case of RST command). */
                             );

/**
* \brief Create a Value block for a given value/addr pair.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phalMfc_Int_CreateValueBlock(
                                        uint8_t * pValue,   /**< [In] Value to be converted. */
                                        uint8_t bAddrData,  /**< [In] bAddrData containing destination address. */
                                        uint8_t * pBlock    /**< [Out] Formatted Value block. */
                                        );

/**
* \brief Check value block format of a given block.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phalMfc_Int_CheckValueBlockFormat(
    uint8_t * pBlock    /**< [In] Formatted Value block. */
    );

/**
* \brief Resolve MIFARE(R) error code from response.
* \return Status code
* \retval #PH_ERR_SUCCESS ACK received.
* \retval #PHPAL_MIFARE_ERR_NAK0 NAK0 received.
* \retval #PHPAL_MIFARE_ERR_NAK1 NAK1 received.
* \retval #PHPAL_MIFARE_ERR_NAK4 NAK4 received.
* \retval #PHPAL_MIFARE_ERR_NAK5 NAK5 received.
* \retval #PH_ERR_PROTOCOL_ERROR Unspecified response.
*/
phStatus_t phalMfc_Int_ResolveReturnCode(
    uint8_t bRetCode   /**< [In] Return Code byte from Card. */
    );

/** @}
* end of ph_Private group
*/

#endif /* PHALMFC_INT_H */
