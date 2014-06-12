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
* Internal definitions for Rd710 specific HAL-Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:27:42 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHHALHW_RD710_INT_H
#define PHHALHW_RD710_INT_H

#include <ph_Status.h>

/** \defgroup phhalHw_Rd710_Int Internal
* \brief Internal definitions.
* @{
*/

#define PHHAL_HW_RD710_FRAME_HEADER_LEN     6U  /**< Length of a command header. */
#define PHHAL_HW_RD710_FRAME_CMD_POS        0U  /**< Position of the command code (ushort). */
#define PHHAL_HW_RD710_FRAME_STATUS_POS     2U  /**< Position of the status (ushort). */
#define PHHAL_HW_RD710_FRAME_LEN_POS        4U  /**< Position of the length (ushort). */
#define PHHAL_HW_RD710_FRAME_PAYLOAD_POS    6U  /**< Position of the payload. */

/**
* \name Command codes
*/
/*@{*/
#define PHHAL_HW_RD710_CMD_RD_OPS_LED_OFF                   0xA001U    /**< Turns the LEDs on the reader off. */
#define PHHAL_HW_RD710_CMD_RD_OPS_LED_ON                    0xA002U    /**< Turns the LEDs on the reader on. */
#define PHHAL_HW_RD710_CMD_RD_OPS_RESET_READER              0xA003U    /**< Issues reset of the reader. */
#define PHHAL_HW_RD710_CMD_RD_OPS_RESET_FACTORY             0xA004U    /**< Overwrites user configuration with factory defaults. */
#define PHHAL_HW_RD710_CMD_RD_OPS_SET_CFG_OPTION            0xA005U    /**< Sets a configuration option in the form of key=value. */
#define PHHAL_HW_RD710_CMD_RD_OPS_GET_READER_STATUS         0xA006U    /**< First returned byte is type of reader chip, 2nd byte is the state of DIP switches */
#define PHHAL_HW_RD710_CMD_RD_OPS_READ_REGISTER             0xA007U    /**< Read value from register address. */
#define PHHAL_HW_RD710_CMD_RD_OPS_WRITE_REGISTER            0xA008U    /**< Write value to register address. */
#define PHHAL_HW_RD710_CMD_RD_OPS_FIELD_ON                  0xA009U    /**< Switch on the RF-field. */
#define PHHAL_HW_RD710_CMD_RD_OPS_FIELD_OFF                 0xA00AU    /**< Switch off the RF-field. */
#define PHHAL_HW_RD710_CMD_RD_OPS_FIELD_RESET               0xA00BU    /**< Perform RF-Reset. */
#define PHHAL_HW_RD710_CMD_RD_OPS_GET_CFG_OPTION            0xA00CU    /**< Gets a configuration option . */
#define PHHAL_HW_RD710_CMD_RD_OPS_SET_PCSC_MODE             0xA00DU    /**< PCSC mode: Standard (0x00) or Direct (0x01). */

#define PHHAL_HW_RD710_CMD_INIT_HAL                         0xB001U    /**< Initialize RD710 HAL stack. */
#define PHHAL_HW_RD710_CMD_EXCHANGE                         0xB002U    /**< Perform Data Exchange with Picc. */
#define PHHAL_HW_RD710_CMD_SET_CONFIG                       0xB003U    /**< Set configuration parameter. */
#define PHHAL_HW_RD710_CMD_GET_CONFIG                       0xB004U    /**< Get configuration parameter. */
#define PHHAL_HW_RD710_CMD_APPLY_PROT_SETTINGS              0xB005U    /**< Apply protocol settings. */
#define PHHAL_HW_RD710_CMD_WAIT                             0xB006U    /**< Blocks until the time given by \c wTimeout elapsed. */
#define PHHAL_HW_RD710_CMD_MFC_AUTH                         0xB007U    /**< Perform MIFARE(R) Classic Authentication using a key. */
#define PHHAL_HW_RD710_CMD_EXECUTE                          0xB008U    /**< Execute a RC command. */
#define PHHAL_HW_RD710_CMD_MFC_AUTH_KEY_NO                  0xB009U    /**< Perform MIFARE(R) Classic Authentication using a key number. */

#define PHHAL_HW_RD710_CMD_I14443P3A_INIT                   0xC001U    /**< Initialize RD710 I14443P3A stack. */
#define PHHAL_HW_RD710_CMD_I14443P3A_REQUEST_A              0xC002U    /**< Perform a ISO14443-3A Request command. */
#define PHHAL_HW_RD710_CMD_I14443P3A_WAKEUP_A               0xC003U    /**< Perform a ISO14443-3A Request command. */
#define PHHAL_HW_RD710_CMD_I14443P3A_HALT_A                 0xC004U    /**< Perform a ISO14443-3A Halt command. */
#define PHHAL_HW_RD710_CMD_I14443P3A_ANTICOLLISION          0xC005U    /**< Perform a ISO14443-3A Anticollision or Select command.*/
#define PHHAL_HW_RD710_CMD_I14443P3A_SELECT                 0xC006U    /**< Perform a ISO14443-3A Select command. */
#define PHHAL_HW_RD710_CMD_I14443P3A_ACTIVATE_CARD          0xC007U    /**< Perform ISO14443-3A ReqA or WupA and Anticollision/Select commands for all cascade levels. */
#define PHHAL_HW_RD710_CMD_I14443P3A_EXCHANGE               0xC008U    /**< Perform ISO14443-3A Data Exchange with Picc. */
#define PHHAL_HW_RD710_CMD_I14443P3A_GET_SERIAL_NO          0xC009U    /**< Retrieve the serial number. */

#define PHHAL_HW_RD710_CMD_I14443P4A_INIT                   0xD001U    /**< Initialize RD710 I14443P4A stack. */
#define PHHAL_HW_RD710_CMD_I14443P4A_RATS                   0xD002U    /**< Perform a ISO14443-4A "Request Answer to Select" command. */
#define PHHAL_HW_RD710_CMD_I14443P4A_PPS                    0xD003U    /**< Perform a ISO14443-4A "Protocol and Parameter Selection" command. */
#define PHHAL_HW_RD710_CMD_I14443P4A_ACTIVATE_CARD          0xD004U    /**< Perform ISO14443-4A Rats and Pps commands. */
#define PHHAL_HW_RD710_CMD_I14443P4A_GET_PROTOCOL_PARAMS    0xD005U    /**< Retrieve the ISO14443-4A protocol parameters. */

#define PHHAL_HW_RD710_CMD_I14443P4_INIT                    0xE001U    /**< Initialize RD710 I14443P4 stack. */
#define PHHAL_HW_RD710_CMD_I14443P4_SET_PROTOCOL            0xE002U    /**< Set the ISO14443-4 protocol parameters. */
#define PHHAL_HW_RD710_CMD_I14443P4_RESET_PROTOCOL          0xE003U    /**< Reset the ISO14443-4 protocol parameters. */
#define PHHAL_HW_RD710_CMD_I14443P4_DESELECT                0xE004U    /**< Deselect ISO14443-4 card. */
#define PHHAL_HW_RD710_CMD_I14443P4_PRES_CHECK              0xE005U    /**< Perform presence check for current card. */
#define PHHAL_HW_RD710_CMD_I14443P4_EXCHANGE                0xE006U    /**< Perform ISO14443-4 Data Exchange with Picc. */
#define PHHAL_HW_RD710_CMD_I14443P4_SET_CONFIG              0xE007U    /**< Set configuration parameter. */
#define PHHAL_HW_RD710_CMD_I14443P4_GET_CONFIG              0xE008U    /**< Get configuration parameter. */

#define PHHAL_HW_RD710_CMD_MIFARE_EXCHANGE_L3               0xF001U    /**< Perform ISO14443-3 Data Exchange with MIFARE Picc. */
#define PHHAL_HW_RD710_CMD_MIFARE_EXCHANGE_L4               0xF002U    /**< Perform ISO14443-4 Data Exchange with MIFARE Picc. */
#define PHHAL_HW_RD710_CMD_MIFARE_EXCHANGE_PC               0xF003U    /**< Perform Proximity-Check Data Exchange with MIFARE Picc. */
#define PHHAL_HW_RD710_CMD_MIFARE_EXCHANGE_RAW              0xF004U    /**< Perform Raw (No CRC, No Parity) Data Exchange with MIFARE Picc. */
#define PHHAL_HW_RD710_CMD_MIFARE_MFC_AUTH                  0xF005U    /**< Perform MIFARE(R) Classic Authentication using a key. */
#define PHHAL_HW_RD710_CMD_MIFARE_MFC_AUTH_KEY              0xF006U    /**< Perform MIFARE(R) Classic Authentication using a key number. */
#define PHHAL_HW_RD710_CMD_MIFARE_INIT                      0xF007U    /**< Initialize RD710 Mifare stack. */

#define PHHAL_HW_RD710_CMD_CID_GET_FREE_CID                 0x9001U    /**< Retrieve the lowest free Card Identifier. */
#define PHHAL_HW_RD710_CMD_CID_FREE_CID                     0x9002U    /**< Free an occupied Cid. */
#define PHHAL_HW_RD710_CMD_CID_INIT                         0x9003U    /**< Initialize RD710 CID stack. */

#define PHHAL_HW_RD710_CMD_KS_INIT                          0x7001U    /**< Initialize RD710 Keystore stack. */
#define PHHAL_HW_RD710_CMD_KS_FORMAT_KEY_ENTRY              0x7002U    /**< Format a key entry to a new KeyType. */
#define PHHAL_HW_RD710_CMD_KS_SET_KEY                       0x7003U    /**< Change a key entry at a given version. */
#define PHHAL_HW_RD710_CMD_KS_SET_KEY_AT_POS                0x7004U    /**< Change a key entry at the specified position. */
#define PHHAL_HW_RD710_CMD_KS_SET_KUC                       0x7005U     /**< Change the KUC of a key entry. */
#define PHHAL_HW_RD710_CMD_KS_SET_CEK                       0x7006U    /**< Change the CEK of a key entry. */
#define PHHAL_HW_RD710_CMD_KS_SET_FULL_KEY_ENTRY            0x7007U    /**< Change a full key entry. */
#define PHHAL_HW_RD710_CMD_KS_GET_KEY_ENTRY                 0x7008U    /**< Get a key entry information block. */
#define PHHAL_HW_RD710_CMD_KS_GET_KEY                       0x7009U    /**< Get a key. */
#define PHHAL_HW_RD710_CMD_KS_SET_CONFIG                    0x700AU    /**< Set configuration parameter. */
#define PHHAL_HW_RD710_CMD_KS_GET_CONFIG                    0x700BU    /**< Get configuration parameter. */
#define PHHAL_HW_RD710_CMD_KS_CHANGE_KUC                    0x700CU    /**< Change a key usage counter entry. */
#define PHHAL_HW_RD710_CMD_KS_GET_KUC                       0x700DU    /**< Obtain a key usage counter entry. */
#define PHHAL_HW_RD710_CMD_KS_SET_CONFIG_BUFFER             0x700EU    /**< Set configuration buffer. */
#define PHHAL_HW_RD710_CMD_KS_GET_CONFIG_BUFFER             0x700FU    /**< Get configuration buffer. */

#define PHHAL_HW_RD710_CMD_CC_ACTIVATE                      0x8001U    /**< Activates a contact card and returns ATR. */
#define PHHAL_HW_RD710_CMD_CC_COLD_RESET                    0x8002U    /**< Performs cold reset in a contact card. */
#define PHHAL_HW_RD710_CMD_CC_WARM_RESET                    0x8003U    /**< Performs warm reset in a contact card. */
#define PHHAL_HW_RD710_CMD_CC_STOP_CLOCK                    0x8004U    /**< Stops the clock signal to the contact card. */
#define PHHAL_HW_RD710_CMD_CC_START_CLOCK                   0x8005U    /**< Starts the clock signal to the contact card. */
#define PHHAL_HW_RD710_CMD_CC_DEACTIVATE                    0x8006U    /**< Starts the clock signal to the contact card. */
#define PHHAL_HW_RD710_CMD_CC_PRESENCE_CHECK                0x8007U    /**< Check if the card is inserted. If inserted returns 0x01otherwise 0x00. */
#define PHHAL_HW_RD710_CMD_CC_TRANSMIT_DATA                 0x8008U    /**< Transport data to contact card. */
#define PHHAL_HW_RD710_CMD_CC_SEND_PPS                      0x8009U    /**< Switches the hardware to a specific baud rate and/or performs a PPS command for the contact card. */
/*@}*/


phStatus_t phhalHw_Rd710_CommandReader(
                                       phhalHw_Rd710_DataParams_t * pDataParams,
                                       uint16_t wCmd,
                                       uint16_t wOption, 
                                       uint8_t * pTxBuffer,
                                       uint16_t wTxLength,
                                       uint8_t ** ppRxBuffer,
                                       uint16_t * pRxLength
                                       );

/** @}
* end of phhalHw_Rd710_Internal group
*/

#endif /* PHHALHW_RD710_INT_H */
