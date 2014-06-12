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
* $Author: santosh.d.araballi $
* $Revision: 1.1 $
* $Date: Fri Apr 15 09:29:10 2011 $
*
* History:
*
*/

#ifndef PHHALHW_RC632_CONFIG_H
#define PHHALHW_RC632_CONFIG_H

#include <ph_Status.h>
#include <phhalHw.h>

/** \defgroup phhalHw_Rc632_Config Configuration
* \brief Custom Configuration of hardware related settings.
* @{
*/

/** \name Memory related constants
*/
/*@{*/
#define PHHAL_HW_RC632_PRECACHED_BYTES  0x40U   /**< Maximum number of bytes to precache into FIFO before triggering a command. */
/*@}*/

/** \name Modulation indices
*/
/*@{*/
#define PHHAL_HW_RC632_MODINDEX_I14443B     0x11U   /**< Default modulation index for ISO14443B. */
#define PHHAL_HW_RC632_MODINDEX_I15693      0x0AU   /**< Default modulation index for ISO15693.  */
#define PHHAL_HW_RC632_MODINDEX_EPCUID      0x0AU   /**< Default modulation index for EPC/UID. */
/*@}*/

/** \name RxThreshold values
*/
/*@{*/
#define PHHAL_HW_RC632_RXTHRESHOLD_I14443A          0x84U   /**< RxThreshold for ISO14443A @ 106kbit/s. */
#define PHHAL_HW_RC632_RXTHRESHOLD_I14443B          0x50U   /**< RxThreshold for ISO14443B @ 106kbit/s. */
/*@}*/

/** @}
* end of phhalHw_Rc632_Config group
*/

#endif /* PHHALHW_RC632_CONFIG_H */
