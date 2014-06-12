/*
*         Copyright (c), NXP Semiconductors Gratkorn / Austria
*
*                     (C)NXP Semiconductors
*       All rights are reserved. Reproduction in whole or in part is 
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
* particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

/** \file
* Rc632 specific HAL-Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.1 $
* $Date: Fri Apr 15 09:29:04 2011 $
*
* History:
*
*/

#ifndef PHHALHW_RC632_CMD_H
#define PHHALHW_RC632_CMD_H

#include <ph_Status.h>
#include <phhalHw.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifdef NXPBUILD__PHHAL_HW_RC632

	/** \defgroup phhalHw_Rc632_Cmd Commands
	* \brief Supported Reader commands.
	* @{
	*/
	/*                   P C D - C O M M A N D S			*/
	/**
	*    @addtogroup RC632 HAL CmdCode
	*/

#define PHHAL_HW_RD710_CMD_RD_OPS_READ_REGISTER             0xA007U	 /**< Read value from register address. */
#define PHHAL_HW_RD710_CMD_RD_OPS_WRITE_REGISTER            0xA008U	 /**< Write value to register address. */
#define PHHAL_HW_RD710_CMD_RD_OPS_FIELD_ON                  0xA009U	 /**< Switch on the RF-field. */
#define PHHAL_HW_RD710_CMD_RD_OPS_FIELD_OFF                 0xA00AU	 /**< Switch off the RF-field. */
#define PHHAL_HW_RD710_CMD_RD_OPS_FIELD_RESET               0xA00BU	 /**< Perform RF-Reset. */
#define PHHAL_HW_RD710_CMD_INIT_HAL                         0xB001U	 /**< Initialize RC632 HAL stack. */
#define PHHAL_HW_RD710_CMD_EXCHANGE                         0xB002U	 /**< Perform Data Exchange with Picc. */
#define PHHAL_HW_RD710_CMD_SET_CONFIG                       0xB003U	 /**< Set configuration parameter. */
#define PHHAL_HW_RD710_CMD_GET_CONFIG                       0xB004U	 /**< Get configuration parameter. */
#define PHHAL_HW_RD710_CMD_APPLY_PROT_SETTINGS              0xB005U	 /**< Apply protocol settings. */
#define PHHAL_HW_RD710_CMD_WAIT                             0xB006U	 /**< Blocks until the time given by \c wTimeout elapsed. */
#define PHHAL_HW_RD710_CMD_MFC_AUTH                         0xB007U	 /**< Perform MIFARE(R) Classic Authentication using a key. */
#define PHHAL_HW_RD710_CMD_EXECUTE                          0xB008U	 /**< Execute a RC command. */
#define PHHAL_HW_RD710_CMD_MFC_AUTH_KEY_NO                  0xB009U	 /**< Perform MIFARE(R) Classic Authentication using a key number. */
#define PHHAL_HW_RD710_CMD_IDLE								0xB00AU	 /**< Perform IDLE command. */	
#define PHHAL_HW_RD710_CMD_WRITEE2							0xB00BU	 /**< Perform WRITEE2 command. */
#define PHHAL_HW_RD710_CMD_READE2							0xB00CU  /**< Perform READE2 command. */
#define PHHAL_HW_RD710_CMD_LOADCONFIG						0xB00DU  /**< Perform LOADCONFIG command. */
#define PHHAL_HW_RD710_CMD_LOADKEY							0xB00EU  /**< Perform LOADKEY command. */
#define PHHAL_HW_RD710_CMD_LOADKEYE2						0xB00FU  /**< Perform LOADKEYE2 command. */
#define PHHAL_HW_RD710_CMD_AUTHENT1							0xB010U  /**< Perform AUTHENTICATE1 command. */
#define PHHAL_HW_RD710_CMD_AUTHENT2							0xB011U  /**< Perform AUTHENTICATE2 command. */
#define PHHAL_HW_RD710_CMD_CALCCRC							0xB012U  /**< Perform CALCULATECRC command. */
#define PHHAL_HW_RD710_CMD_RECEIVE							0xB013U  /**< Perform RECEIVE command. */
#define PHHAL_HW_RD710_CMD_TRANSMIT							0xB014U  /**< Perform TRANSMIT command. */
#define PHHAL_HW_RD710_CMD_TRANSCEIVE						0xB002U  /**< Perform TRANCEIVE / EXCHANGE command. */
#define PHHAL_HW_RD710_CMD_RESETPHASE						0xB015U  /**< Perform RESETPHASE command. */


#define PHHAL_HW_RC632_PRECACHED_BYTES						0x40U   /**< Maximum number of bytes to precache into FIFO before triggering a command. */
#define PHHAL_HW_RC632_CMD_IDLE								0x00	/**< No action: cancel current command or home state */
#define PHHAL_HW_RC632_CMD_WRITEE2							0x01	/**< Get data from FIFO and write it to the E2PROM*/
#define PHHAL_HW_RC632_CMD_READE2							0x03	/**< Read data from E2PROM and put it into the FIFO */
#define PHHAL_HW_RC632_CMD_LOADCONFIG						0x07	/**< Read data from E2PROM and initialise the registers */
#define PHHAL_HW_RC632_CMD_LOADKEYE2						0x0B	/**< Read a master key from the E2PROM and put it into the master key buffer */
#define PHHAL_HW_RC632_CMD_AUTHENT1							0x0C	
	/**< Perform the first part of the card 
	authentication using the Crypto1 algorithm.
	Remark: The master key is automatically taken 
	from the master key buffer. this implies, 
	that the command LoadKeyE2 has to be executed
	before using a certain key for card 
	authentication */
#define PHHAL_HW_RC632_CMD_CALCCRC							0x12 
	/**< Activate the CRC-Coprocessor
	Remark: The result of the CRC calculation can
	be read from the register CRCResultXXX */
#define PHHAL_HW_RC632_CMD_AUTHENT2							0x14 
	/**< Perform the second part of the card 
	authentication using the Crypto1 algorithm. */
#define PHHAL_HW_RC632_CMD_RECEIVE							0x16 
	/**< Activate Receiver Circuitry. Before the 
	receiver actually starts, the state machine 
	waits until the time configured in the 
	register RxWait has passed.

	Remark: It is possible to read any received 
	data from the FIFO while the Receive command
	is active. Thus it is possible to receive an 
	unlimited number of bytes by reading them 
	from the FIFO in timer. */
#define PHHAL_HW_RC632_CMD_LOADKEY							0x19 
	/**< Read a master key from the FIFO and put it 
	into the master key buffer
	Remark: The master key has to be prepared in
	a certain format. Thus, 12 byte have to be 
	passed to load a 6 byte master key */
#define PHHAL_HW_RC632_CMD_TRANSMIT							0x1A 
	/**< Transmit data from FIFO to the card
	Remark: If data is already in the FIFO when 
	the command is activated, this data is 
	transmitted immediately. It is possible to 
	write data to the FIFO while the Transmit 
	command is active. Thus it is possible to 
	transmit an unlimited number of bytes in one
	stream by writting them to the FIFO in time.*/
#define PHHAL_HW_RC632_CMD_TRANSCEIVE						0x1E 
	/**< Transmits data from FIFO to the card and 
	after that automatically activates the 
	receiver. Before the receiver actually 
	starts,the state machine waits until the 
	time configured in the register RxWait has 
	passed. 
	Remark: This command is the combination of 
	Transmit and Receive.*/
#define PHHAL_HW_RC632_CMD_RESETPHASE						0x3F 
	/**< Runs the Reset- and Initialisation Phase
	Remark: This command can not be activated by 
	software, but only by a Power-On or 
	Hard Reset */

	/** @} */

	/**
	* \brief Load a MIFARE key from EEPROM into the key-buffer.
	*
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
	phStatus_t phhalHw_Rc632_Cmd_LoadKeyE2(
		phhalHw_Rc632_DataParams_t* pDataParams,
		uint8_t bKeyNo,
		uint8_t bAuthMode
		); 

	/**
	* \brief Load a MIFARE key into the key-buffer.
	*
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
	phStatus_t  phhalHw_Rc632_Cmd_LoadKey(phhalHw_Rc632_DataParams_t * pDataParams,uint8_t *pKey);
	/**
	* \brief Read one byte from a given EEPROM address.
	*
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
	phStatus_t  phhalHw_Rc632_Cmd_ReadE2(
		phhalHw_Rc632_DataParams_t* pDataParams,
		uint16_t wAddress,
		uint16_t wNumBytes,
		uint8_t * pData
		);
	/**
	* \brief Write one byte of data to a given EEPROM address.
	*
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
	phStatus_t  phhalHw_Rc632_Cmd_WriteE2(
		phhalHw_Rc632_DataParams_t * pDataParams,
		uint16_t wAddress,
		uint8_t * pData,
		uint8_t bDataLen
		);

	/**
	* \brief Copies a defined number of bytes from the EEPROM into the register set, beginning at the given register address RegAdr.
	*
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
	phStatus_t  phhalHw_Rc632_Cmd_LoadConfig(phhalHw_Rc632_DataParams_t * pDataParams,uint16_t wEEAddress);
	/**
	* \brief Calculates a CRC over the input data and returns the result.
	*
	* Note: The CRC calculation parameters are taken from the respective registers.
	*
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
	phStatus_t phhalHw_Rc632_Cmd_CalcCrc(
		phhalHw_Rc632_DataParams_t *pDataParams,
		uint8_t * pData,
		uint16_t wDataLength,
		uint16_t * pCrcResult
		);
	/**
	* \brief Transmit bytes to card without starting receiver afterwards.
	*
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
	phStatus_t phhalHw_Rc632_Cmd_Transmit(
		phhalHw_Rc632_DataParams_t * pDataParams,
		uint16_t wOption,
		uint8_t * pTxBuffer,
		uint16_t wTxLength
		);
	/**
	* \brief Start receiver and wait until reception or timeout.
	*
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval #PH_ERR_IO_TIMEOUT No response received.
	* \retval Other Depending on implementation and underlaying component.
	*/
	phStatus_t phhalHw_Rc632_Cmd_Receive(
		phhalHw_Rc632_DataParams_t * pDataParams,
		uint16_t wOption,
		uint8_t ** ppRxBuffer,
		uint16_t * pRxLength);


#endif /* NXPBUILD__PHHAL_HW_RC632 */

#ifdef __cplusplus
} /* Extern C */
#endif

#endif /* PHHALHW_RC632_CMD_H */
