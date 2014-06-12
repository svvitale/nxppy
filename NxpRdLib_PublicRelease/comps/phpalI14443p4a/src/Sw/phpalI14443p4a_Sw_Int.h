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
* Internal definitions for Software ISO14443-4A Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:27:32 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHPALI14443P4A_SW_INT_H
#define PHPALI14443P4A_SW_INT_H

#include <ph_Status.h>

/** \addtogroup ph_Private
* @{
*/

/** HltA Command code. */
#define PHPAL_I14443P4A_SW_HALT_CMD             0x50U

/** Rats Command code. */
#define PHPAL_I14443P4A_SW_RATS                 0xE0U

/** PPS Command code. */
#define PHPAL_I14443P4A_SW_PPSS                 0xD0U

/** PPS0 code. */
#define PHPAL_I14443P4A_SW_PPS0                 0x11U

/** ISO 14443-4 S-Block. */
#define PHPAL_I14443P4A_SW_S_BLOCK              0xC0U

/** ISO 14443-4 S-Block RFU bits. */
#define PHPAL_I14443P4A_SW_S_BLOCK_RFU_BITS     0x02U

/** Bit within PCB which signals presence of CID byte .*/
#define PHPAL_I14443P4A_SW_PCB_CID_FOLLOWING    0x08U

/** Bits within PCB which signal a DESELECT command. */
#define PHPAL_I14443P4A_SW_PCB_DESELECT         0x00U

/** Activation FTW in microseconds. */
#define PHPAL_I14443P4A_SW_FWT_ACTIVATION_US    4833

/** Position of T0 within ATS. */
#define PHPAL_I14443P4A_SW_ATS_T0               1

/** Bit which signals TA(1) presence. */
#define PHPAL_I14443P4A_SW_ATS_TA1_PRESENT      0x10U

/** Bit which signals TB(1) presence. */
#define PHPAL_I14443P4A_SW_ATS_TB1_PRESENT      0x20U

/** Bit which signals TC(1) presence. */
#define PHPAL_I14443P4A_SW_ATS_TC1_PRESENT      0x40U

/** Bit within TC(1) which signals NAD support. */
#define PHPAL_I14443P4A_SW_ATS_TC1_NAD_SUPPORT  0x01U

/** Bit within TC(1) which signals CID support. */
#define PHPAL_I14443P4A_SW_ATS_TC1_CID_SUPPORT  0x02U

/** FWI default value. */
#define PHPAL_I14443P4A_SW_FWI_DEFAULT          0x04U

/** SFGI default value. */
#define PHPAL_I14443P4A_SW_SFGI_DEFAULT         0x00U

/** FSCI default value. */
#define PHPAL_I14443P4A_SW_FSCI_DEFAULT         0x02U

/** FTW min in microseconds. */
#define PHPAL_I14443P4A_SW_FWT_MIN_US           303

/** Wait time for halt command in microseconds. */
#define PHPAL_I14443P4A_SW_HALT_TIME_US         1100U

/** Time extension in microseconds for all commands.  */
#define PHPAL_I14443P4A_SW_EXT_TIME_US          60

/** @}
* end of ph_Private
*/

#endif /* PHPALI14443P4A_SW_INT_H */
