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
* Rc663 functions of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:27:40 2011 $
*
* History:
*  RSn: Generated 5. March 2010
*
*/

#ifndef PHKEYSTORE_RC663_INT_H
#define PHKEYSTORE_RC663_INT_H

#include <ph_Status.h>


#define PH_KEYSTORE_RC663_EEP_WR_TO_MS            06U   /**< Time out to perform EEPROM write in milliseconds. */ 

/**
* \name Rc663 register definitions
*/
/*@{*/
#define PH_KEYSTORE_RC663_REG_COMMAND           0x00U   /**< Command register. */
#define PH_KEYSTORE_RC663_REG_FIFOCONTROL       0x02U   /**< FIFO Control register. */
#define PH_KEYSTORE_RC663_REG_FIFODATA          0x05U   /**< FIFO Data register. */
#define PH_KEYSTORE_RC663_REG_IRQ0              0x06U   /**< Interrupt 0 register. */
#define PH_KEYSTORE_RC663_REG_IRQ1              0x07U   /**< Interrupt 1 register. */

/* Bit definitions */
#define PH_KEYSTORE_RC663_BIT_IRQ_SET           0x80U   /**< Bit SET of the Irq registers. */

/* Control register */
#define PH_KEYSTORE_RC663_BIT_FLUSHFIFO         0x10U   /**< Clears internal FIFO buffer when set. */

/* Command set */
#define PH_KEYSTORE_RC663_CMD_IDLE              0x00U    /**< Command Idle. */
#define PH_KEYSTORE_RC663_CMD_STOREKEYE2        0x0FU    /**< Command to store keys in EE. */
/*@}*/

/**
* \brief Write Store Keys in Eeprom command implementation.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phKeyStore_Rc663_StoreKeyE2_Int(
                                        phKeyStore_Rc663_DataParams_t * pDataParams,
                                        uint8_t bKeyNumber,
                                        uint8_t * pKey,
                                        uint8_t bNumKeys
                                        );
/** @}
* end of phKeyStore_Rc663
*/

#endif /* PHKEYSTORE_RC663_INT_H */
