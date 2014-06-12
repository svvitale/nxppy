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
* Internal definitions for Rc632 specific HAL-Component of Reader Library Framework.
* $Author: jayaprakash.desai $
* $Revision: 1.2 $
* $Date: Thu May 12 10:42:40 2011 $
*
* History:
*
*/

#ifndef PHHALHW_RC632_INT_H
#define PHHALHW_RC632_INT_H

#include <ph_Status.h>
#include <phhalHw_Rc632_Cmd.h>

/** \defgroup phhalHw_Rc632_Int Internal
* \brief Internal definitions.
* @{
*/
/** \name Custom command option
*/
/*@{*/
#define PHHAL_HW_RC632_OPTION_FIFO_NOCLEAR  0x0080U /**< Do not clear FIFO prior to command execution. */
/**
Do not start timer after transmission / before reception; (only for phhalHw_Rc632_Cmd_Receive).
*/
#define PHHAL_HW_RC632_OPTION_RXTX_TIMER_NOSTART    0x0000U

/**
Start timer after transmission / before reception, reset timer counter value; (only for phhalHw_Rc632_Cmd_Receive).
*/
#define PHHAL_HW_RC632_OPTION_RXTX_TIMER_START  0x0010U

/**
Do not stop the receive command after execution, do not flush the FIFO.
*/
#define PHHAL_HW_RC632_EXCHANGE_CMD_NOSTOP			0x0020U
#define PHHAL_HW_RC632_RESERVED_BUFFER_LEN			7U							/**< Amount of needed and reserved memory for the protocol overhead. */
#define PHHAL_HW_RC632_DEFAULT_TIMEOUT_MS			5U							/**< Default timeout in milliseconds. */
#define PHHAL_HW_RC632_SHADOW_COUNT					0x000DU						/**< Number of shadowed configurations. */
#define PHHAL_HW_RC632_FIFOSIZE						256U						/**< Size of RC internal FiFo buffer. */
#define PHHAL_HW_RC632_DEFAULT_TIMEOUT_MS			5U							/**< Default timeout in milliseconds. */
#define PHHAL_HW_RC632_CONFIG_DISABLE_PCDRESET		(PH_CONFIG_CUSTOM_BEGIN)    /**< Disable PcdReset call in \ref phhalHw_ApplyProtocolSettings function. */
#define PHHAL_HW_RC632_TIMER_FREQ					13.56							/**< RC internal timer frequency. */
#define PHHAL_HW_RC632_TIMER_MAX_VALUE_US			39437592					/**< RC maximum timer value in microseconds. */
#define PHHAL_HW_RC632_ETU_106						1000 / 106					/**< Duration of one ETU at 106 kBit/s in [us]. */
#define PHHAL_HW_RC632_MFC_KEY_LENGTH				0x06U						/**< Lengh of a MIFARE(R) Classic key. */
#define	PHHAL_HW_RC632_VALUE_FIFOSIZE				0x40U						/**< Buffer size of the FIFO. */
#define PHHAL_HW_RC632_EEPROM_SIZE					0xFFFU						/**< EEPROM size of the Rc632 chip*/
#define PHHAL_HW_RC632_EEPROM_PAGE_SIZE				0x10U						/**< Size of a page in EEPROM. */
#define PHHAL_HW_RC632_MAX_NUM_REGS					0x40U						/**< NUMBER of registers in RC632. */
#define PHHAL_HW_RC632_ETU_I14443                   9.44f						/**< Duration of one ETU for ISO14443 at 106 kBit/s in [us]. */
#define PHHAL_HW_RC632_ETU_I15693                   37.76f						/**< Duration of one ETU for ISO15693 in [us]. */
#define PHHAL_HW_RC632_ETU_EPCUID                   37.76f						/**< Duration of one ETU for EPC/UID in [us]. */
#define PHHAL_HW_RC632_I14443_ADD_DELAY_US          15							/**< Additional digital timeout delay for ISO14443. */
#define PHHAL_HW_RC632_I15693_ADD_DELAY_US          120							/**< Additional digital timeout delay for ISO15693. */
#define PHHAL_HW_RC632_DIGI_DELAY_TXWAIT_DBFREQ     8U							/**< Chip digital delay in ETUs for TxWait. */
#define PHHAL_HW_RC632_TIMER_SHIFT					4.8f						/**< Shift of the internal RC timer in ETUs. */


#define PHHAL_HW_RC632_AUTHMODE_KEYA				0x60U						/**< MFC KeyA Authentication Mode. */
#define PHHAL_HW_RC632_AUTHMODE_KEYB				0x61U						/**< MFC KeyA Authentication Mode. */
#define PHHAL_HW_RC632_MAX_NUM_KEYS					16U							/**< Maximum possible number of keys in the EEPROM. */


/* Utility / Internal function prototypes */
/**
* \brief Write Data to Fifo buffer.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc632_WriteFifo(
								   phhalHw_Rc632_DataParams_t * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
								   uint8_t * pData,                             /**< [In] input data. */
								   uint16_t wLength,                            /**< [In] length of input data. */
								   uint16_t * pBytesWritten                     /**< [Out] Number of written bytes. */
								   );
/**
* \brief Read Data from Fifo buffer.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc632_ReadFifo(
								  phhalHw_Rc632_DataParams_t * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
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
phStatus_t phhalHw_Rc632_FlushFifo(phhalHw_Rc632_DataParams_t* pDataParams);

/**
* \brief Write multiple values to a single register address.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc632_WriteData(
								   phhalHw_Rc632_DataParams_t * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
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
phStatus_t phhalHw_Rc632_ReadData(
								  phhalHw_Rc632_DataParams_t * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
								  uint8_t bAddress,                         /**< [In] Register Address */
								  uint16_t wLength,                         /**< [In] Number of Values */
								  uint8_t * pData                           /**< [Out] Register Values; uint8_t[wLength] */
								  );
/**
* \brief Wait until one of the given interrupts occurs.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc632_WaitIrq(
								 phhalHw_Rc632_DataParams_t * pDataParams,
								 uint8_t bIrqWaitFor,
								 uint8_t * pIrqReg
								 );

phStatus_t phhalHw_Rc632_SetBitMask(
									phhalHw_Rc632_DataParams_t* pDataParams, 
									uint8_t reg,
									uint8_t mask
									);
phStatus_t phhalHw_Rc632_ClearBitMask(phhalHw_Rc632_DataParams_t* pDataParams,
									  uint8_t reg,
									  uint8_t mask
									  );
phStatus_t phhalHw_Rc632_SetTmo(phhalHw_Rc632_DataParams_t* pDataParams,uint16_t tmoLength,uint8_t bUnit);
phStatus_t phhalHw_Rc632_GetTxBuffer(
									 phhalHw_Rc632_DataParams_t * pDataParams,
									 uint8_t bIsExchange,
									 uint8_t ** pTxBuffer,
									 uint16_t * pTxBufferLen,
									 uint16_t * pTxBufferSize
									 );
phStatus_t phhalHw_Rc632_GetRxBuffer(
									 phhalHw_Rc632_DataParams_t * pDataParams,
									 uint8_t bIsExchange,
									 uint8_t ** pRxBuffer,
									 uint16_t * pRxBufferLen,
									 uint16_t * pRxBufferSize
									 );
/**
* \brief Execute a Reader-specific command.
*
* Internal function for executing all commands except Transceive/Transmit/Receive.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc632_Command_Int(
									 phhalHw_Rc632_DataParams_t * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
									 uint8_t bCmd,                              /**< [In] Command code. */
									 uint16_t wOption,                          /**< [In] Option parameter. */
									 uint8_t bIrqWaitFor,                       /**< [In] Bitmask of interrupts in Irq0 register to wait for. */
									 uint8_t * pTxBuffer,                       /**< [In] Data to transmit. */
									 uint16_t wTxLength,                        /**< [In] Length of input data. */
									 uint16_t wRxBufferSize,                    /**< [In] Size of receive buffer. */
									 uint8_t * pRxBuffer,                       /**< [Out] Pointer to received data. */
									 uint16_t * pRxLength                       /**< [Out] Number of received data bytes. */
									 );
/**
* \brief Build and Execute MIFARE(R) Classic Authentication command.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t  phhalHw_Rc632_MfcAuthenticate_Int(
	phhalHw_Rc632_DataParams_t* pDataParams,
	uint8_t bAuthMode,
	uint8_t *pUid,
	uint8_t bBlockNo
	);
/**
* \brief Calculates the frame delay time between transmission and reception of the last command.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rc632_CalculateFdt(
									  phhalHw_Rc632_DataParams_t * pDataParams,     /**< [In] Pointer to this layer's parameter structure. */
									  phStatus_t wExchangeStatus,                   /**< [In] Status code returned by exchange function. */
									  uint32_t * pTime                              /**< [Out] Calculated time in microseconds from timer contents. */
									  );

/**
* \brief Returns the delay of the digital circutry for the current protocol.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phhalHw_Rc632_GetDigiDelay(
									  phhalHw_Rc632_DataParams_t * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
									  uint8_t bIsTimeout,                       /**< [In] Wheter the returned delay is added to a timeout (#PH_ON) or is used for measurement (#PH_OFF). */
									  uint16_t * pDelayUs                       /**< [Out] The digital delay in microseconds. */
									  );


/*@}*/

/** @}
* end of phhalHw_Rc632_Internal group
*/

#endif /* PHHALHW_RC632_INT_H */
