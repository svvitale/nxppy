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
* RC632 functions of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:27:54 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHKEYSTORE_RC632_INT_H
#define PHKEYSTORE_RC632_INT_H

#include <ph_Status.h>

#define PH_KEYSTORE_RC632_EEP_KEY_BASE_ADDR     0x80U   /**< Base address of keys storage in eeprom of RC632. */
#define PH_KEYSTORE_RC632_EEP_KEY_LENGTH        24U     /**< Size needed in eeprom to store a (mifare) key. */ 
#define PH_KEYSTORE_RC632_EEP_WR_TO_MS          12U     /**< Time out to perform EEPROM write in milliseconds. */ 

/**
* \name Rc632 register definitions
*/
/*@{*/
#define PH_KEYSTORE_RC632_REG_COMMAND           0x01U   /**< Command register. */
#define PH_KEYSTORE_RC632_REG_FIFO_DATA         0x02U   /**< FIFO register. */
#define PH_KEYSTORE_RC632_REG_SECONDARY_STATUS  0x05U   /**< Secondary status register. */
#define PH_KEYSTORE_RC632_REG_INT_EN            0x06U   /**< Interrupt enable register. */
#define PH_KEYSTORE_RC632_REG_INT_REQ           0x07U   /**< Interrupt request register. */
#define PH_KEYSTORE_RC632_REG_CONTROL           0x09U   /**< Control register. */

/* Secondary status register (05) */
#define PH_KEYSTORE_RC632_BIT_E2READY           0x40U   /**< Set by IC when E2 programming is finished. */

/* Control register (09) */
#define PH_KEYSTORE_RC632_BIT_FLUSHFIFO         0x01U   /**< Clears internal FIFO buffer when set. */

/* Command set */
#define PH_KEYSTORE_RC632_CMD_IDLE              0x00    /**< Set IC to IDLE state. */
#define PH_KEYSTORE_RC632_CMD_WRITE_E2          0x01    /**< Set IC to IDLE state. */
/*@}*/

/**
* \brief Write EEPROM command implementation.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phKeyStore_Rc632_WriteE2_Int(
                                        phKeyStore_Rc632_DataParams_t * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                                        uint8_t    * pData,                                /**< [In] Data to write to EEPROM. */
                                        uint16_t DataLength                             /**< [In] Length of Data to be written. */
                                        );

/** @}
* end of phKeyStore_Rc632
*/

#endif /* PHKEYSTORE_RC632_INT_H */
