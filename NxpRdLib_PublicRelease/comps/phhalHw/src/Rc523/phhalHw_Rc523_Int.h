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
* Internal definitions for Rc523 specific HAL-Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.4 $
* $Date: Fri Apr 15 09:27:50 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHHALHW_RC523_INT_H
#define PHHALHW_RC523_INT_H

#include <ph_Status.h>

/** \defgroup phhalHw_Rc523_Int Internal
* \brief Internal definitions.
* @{
*/

#define PHHAL_HW_RC523_TIMER_FREQ               13.56f      /**< RC internal timer frequency. */
#define PHHAL_HW_RC523_TIMER_MAX_VALUE_US       39586813    /**< RC maximum timer value in microseconds. */
#define PHHAL_HW_RC523_TIMER_SHIFT              4.8f        /**< Shift of the internal RC timer in ETUs. */
#define PHHAL_HW_RC523_ETU_106                  9.44f       /**< Duration of one ETU at 106 kBit/s in [us]. */

/** \name Timing related constants
*/
/*@{*/
#define PHHAL_HW_RC523_FELICA_ADD_DELAY_US      240U        /**< Additional digital timeout delay for Felica. */
/*@}*/

/** \name RS232 speed settings
*/
/*@{*/
#define PHHAL_HW_RC523_SERIALSPEED_7200     0xFAU       /**< 7.200 kBit/s. */
#define PHHAL_HW_RC523_SERIALSPEED_9600     0xEBU       /**< 9.600 kBit/s. */
#define PHHAL_HW_RC523_SERIALSPEED_14400    0xDAU       /**< 14.400 kBit/s. */
#define PHHAL_HW_RC523_SERIALSPEED_19200    0xCBU       /**< 19.200 kBit/s. */
#define PHHAL_HW_RC523_SERIALSPEED_38400    0xABU       /**< 38.400 kBit/s. */
#define PHHAL_HW_RC523_SERIALSPEED_57600    0x9AU       /**< 57.500 kBit/s. */
#define PHHAL_HW_RC523_SERIALSPEED_115200   0x7AU       /**< 115.200 kBit/s. */
#define PHHAL_HW_RC523_SERIALSPEED_128000   0x74U       /**< 128.000 kBit/s. */
#define PHHAL_HW_RC523_SERIALSPEED_230400   0x5AU       /**< 230.400 kBit/s. */
#define PHHAL_HW_RC523_SERIALSPEED_460800   0x3AU       /**< 460.800 kBit/s. */
#define PHHAL_HW_RC523_SERIALSPEED_921600   0x1CU       /**< 921.600 kBit/s. */
#define PHHAL_HW_RC523_SERIALSPEED_1228800  0x15U       /**< 1.228.800 kBit/s. */
/*@}*/

#define PHHAL_HW_RC523_MFC_AUTHA_CMD          0x60U     /**< MIFARE(R) Classic AUTHA command code. */
#define PHHAL_HW_RC523_MFC_AUTHB_CMD          0x61U     /**< MIFARE(R) Classic AUTHB command code. */

/**
* \brief Write Data to Fifo buffer.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc523_WriteFifo(
                                   phhalHw_Rc523_DataParams_t * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                                   uint8_t * pData,                             /**< [In] input data */
                                   uint16_t wLength,                            /**< [In] length of input data */
                                   uint16_t * pBytesWritten                     /**< [Out] Number of written bytes */
                                   );

/**
* \brief Read Data from Fifo buffer.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc523_ReadFifo(
                                  phhalHw_Rc523_DataParams_t * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
                                  uint16_t wBufSize,                        /**< [In] size of output buffer */
                                  uint8_t * pData,                          /**< [Out] output data */
                                  uint16_t * pLength                        /**< [Out] number of output data bytes */
                                  );

/**
* \brief Clear Fifo buffer.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc523_FlushFifo(
                                   phhalHw_Rc523_DataParams_t * pDataParams /**< [In] Pointer to this layer's parameter structure. */
                                   );

/**
* \brief Write multiple values to a single register address.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc523_WriteData(
                                   phhalHw_Rc523_DataParams_t * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                                   uint8_t bAddress,                            /**< [In] Start-Register Address */
                                   uint8_t * pData,                             /**< [In] Register Values; uint8_t[wLength] */
                                   uint16_t wLength                             /**< [In] Number of Values */
                                   );

/**
* \brief Read multiple values from single register address.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc523_ReadData(
                                  phhalHw_Rc523_DataParams_t * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
                                  uint8_t bAddress,                         /**< [In] Register Address */
                                  uint16_t wLength,                         /**< [In] Number of Values */
                                  uint8_t * pData                           /**< [Out] Register Values; uint8_t[wLength] */
                                  );

/**
* \brief Transmit part of Exchange command.
*
* \see phhalHw_Exchange
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc523_ExchangeTransmit(
    phhalHw_Rc523_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t bCmdCode,                           /**< [In] Command-Code of command. */
    uint8_t * pTxBuffer,                        /**< [In] Data to transmit. */
    uint16_t wTxLength                          /**< [In] Length of data to transmit. */
    );

/**
* \brief Receive part of Exchange command.
*
* \see phhalHw_Exchange
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc523_ExchangeReceive(
    phhalHw_Rc523_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t ** ppRxBuffer,                      /**< [Out] Pointer to received data. */
    uint16_t * pRxLength                        /**< [Out] Number of received data bytes. */
    );

/**
* \brief Sets the Frame Delay Time (Timeout).
*
* \b Note: Frame Delay Time is defined between the last transmitted bit and the first received bit.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc523_SetFdt(
                                phhalHw_Rc523_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
                                uint8_t bUnit,                              /**< [In] Unit of given timeout value (either #PHHAL_HW_TIME_MICROSECONDS or #PHHAL_HW_TIME_MILLISECONDS). */
                                uint16_t wTimeout                           /**< [In] Timeout value. */
                                );

/**
* \brief Retrieves the Frame Delay Time of the last command.
*
* \b Note: Frame Delay Time is defined between the last transmitted bit and the first received bit.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc523_GetFdt(
                                phhalHw_Rc523_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
                                phStatus_t wExchangeStatus,                 /**< [In] Status code returned by exchange function. */
                                uint32_t * pTime                            /**< [Out] Calculated time in microseconds from timer contents. */
                                );

/**
* \brief Returns the TxBuffer pointer, length and size.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phhalHw_Rc523_GetTxBuffer(
                                     phhalHw_Rc523_DataParams_t * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                                     uint8_t bIsExchange,                       /**< [In] Whether this is for Exchange (#PH_ON) or not (#PH_OFF). */
                                     uint8_t ** pTxBuffer,                      /**< [Out] Pointer to the TxBuffer. */
                                     uint16_t * pTxBufferLen,                   /**< [Out] Number of bytes already in the TxBuffer. */
                                     uint16_t * pTxBufferSize                   /**< [Out] Size of the TxBuffer. */
                                     );

/**
* \brief Returns the RxBuffer pointer, length and size.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phhalHw_Rc523_GetRxBuffer(
                                     phhalHw_Rc523_DataParams_t * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                                     uint8_t bIsExchange,                       /**< [In] Whether this is for Exchange (#PH_ON) or not (#PH_OFF). */
                                     uint8_t ** pRxBuffer,                      /**< [Out] Pointer to the RxBuffer. */
                                     uint16_t * pRxBufferLen,                   /**< [Out] Number of bytes already in the RxBuffer. */
                                     uint16_t * pRxBufferSize                   /**< [Out] Size of the RxBuffer. */
                                     );

/**
* \brief Wait until one of the given interrupts occurs.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc523_WaitIrq(
                                 phhalHw_Rc523_DataParams_t * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                                 uint8_t bIrq0WaitFor,                      /**< [In] Bitmask of interrupts in CommIrq register to wait for. */
                                 uint8_t bIrq1WaitFor,                      /**< [In] Bitmask of interrupts in DivIrq register to wait for. */
                                 uint8_t * pIrq0Reg,                        /**< [Out] Contents of CommIrq register. */
                                 uint8_t * pIrq1Reg                         /**< [Out] Contents of DivIrq register. */
                                 );

/** @}
* end of phhalHw_Rc523_Internal group
*/

#endif /* PHHALHW_RC523_INT_H */
