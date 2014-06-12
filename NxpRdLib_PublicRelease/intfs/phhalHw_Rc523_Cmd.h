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
* Command functions for Rc523 specific HAL-Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:27:19 2011 $
*
* History:
*  CHu: Generated 19. April 2010
*
*/

#ifndef PHHALHW_RC523_CMD_H
#define PHHALHW_RC523_CMD_H

#include <ph_Status.h>
#include <phhalHw.h>

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#ifdef  NXPBUILD__PHHAL_HW_RC523

/** \defgroup phhalHw_Rc523_Cmd Commands
* \brief Supported ReaderIC commands.
* @{
*/

/**
* \brief Transfers either 25 bytes into internal buffer or returns 25 bytes from internal buffer.
*
* If \c bDataLength equals zero, 25 bytes from the internal buffer are put into \c pDataOut.\n
* If \c bDataLength is 25, 25 bytes from \c pDataIn are copied into the internal buffer.
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_INVALID_PARAMETER \c bDataLength is neither zero nor 25.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc523_Cmd_Mem(
                                 phhalHw_Rc523_DataParams_t * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                                 uint8_t * pDataIn,                         /**< [In] 25 bytes In-data or ignored if \c bDataLength equals zero. */
                                 uint8_t bDataLength,                       /**< [In] Data length. Either zero or 25. */
                                 uint8_t * pDataOut                         /**< [Out] 25 bytes Out-data or ignored if \c bDataLength is nonzero. */
                                 );

/**
* \brief Stores data for \ref phhalHw_Rc523_Cmd_Autocoll command into internal buffer.
*
* \b Note: Only applicable if in Target mode (e.g. #PHHAL_HW_CARDTYPE_I18092MPT).
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_INVALID_PARAMETER \c bDataLength is neither zero nor 25.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc523_Cmd_Config(
                                    phhalHw_Rc523_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
                                    uint8_t * pSensRes,                         /**< [In] 2 bytes. */
                                    /** [In] 3 bytes; The first NfcId1 byte is fixed to \c 08h and the check byte is calculated automatically. */
                                    uint8_t * pNfcId1,
                                    uint8_t SelRes,                             /**< [In] 1 byte. */
                                    /** [In] 2 bytes (shall be 01h, FEh) + 6 bytes NfcId2 + 8 bytes Pad + 2 bytes SystemCode. */
                                    uint8_t * pPollingResp,
                                    uint8_t bNfcId3                             /**< [In] 1 byte. */
                                    );

/**
* \brief Generates a 10 byte random ID.
*
* The generated RandomId is stored in the internal buffer (the first 10 bytes get overridden).\n
* It can be retrieved using the function \ref phhalHw_Rc523_Cmd_Mem.
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc523_Cmd_GenerateRandomId(
    phhalHw_Rc523_DataParams_t * pDataParams    /**< [In] Pointer to this layer's parameter structure. */
    );

/**
* \brief Calculates a CRC over the input data and returns the result.
*
* Note: The CRC calculation parameters are taken from the respective registers.
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc523_Cmd_CalcCrc(
                                     phhalHw_Rc523_DataParams_t * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                                     uint8_t * pData,                           /**< [In] CRC input data. */
                                     uint16_t wDataLength,                      /**< [In] Length of input data. */
                                     uint16_t * pCrcResult                      /**< [Out] Calculated CRC. */
                                     );

/**
* \brief Transmit bytes to card without starting receiver afterwards.
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc523_Cmd_Transmit(
                                      phhalHw_Rc523_DataParams_t * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
                                      uint16_t wOption,                         /**< [In] Option parameter. */
                                      uint8_t * pTxBuffer,                      /**< [In] Data to transmit. */
                                      uint16_t wTxLength                        /**< [In] Length of data to transmit. */
                                      );

/**
* \brief Start receiver and wait until reception or timeout.
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_IO_TIMEOUT No response received.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc523_Cmd_Receive(
                                     phhalHw_Rc523_DataParams_t * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                                     uint16_t wOption,                          /**< [In] Option parameter. */
                                     uint8_t ** ppRxBuffer,                     /**< [Out] Pointer to received data. */
                                     uint16_t * pRxLength                       /**< [Out] Number of received data bytes. */
                                     );

/**
* \brief Handles Felica polling or MIFARE anticollision.
*
* Only applicable if in Target mode (e.g. #PHHAL_HW_CARDTYPE_I18092MPT).\n
* \b Note: Ensure that the correct configuration has been loaded using the \ref phhalHw_Rc523_Cmd_Config command.
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_IO_TIMEOUT No response received.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc523_Cmd_Autocoll(
                                      phhalHw_Rc523_DataParams_t * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
                                      uint8_t ** ppRxBuffer,                    /**< [Out] Pointer to received data. */
                                      uint16_t * pRxLength                      /**< [Out] Number of received data bytes. */
                                      );

/**
* \brief Performs a Softreset.
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc523_Cmd_SoftReset(
                                       phhalHw_Rc523_DataParams_t * pDataParams /**< [In] Pointer to this layer's parameter structure. */
                                       );

/** @} */
#endif /* NXPBUILD__PHHAL_HW_RC523 */

#ifdef __cplusplus
} /* Extern C */
#endif

#endif /* PHHALHW_RC523_CMD_H */
