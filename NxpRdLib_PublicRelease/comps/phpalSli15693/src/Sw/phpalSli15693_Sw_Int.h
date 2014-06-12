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
* Internal definitions for Software ISO14443-3A Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:26:55 2011 $
*
* History:
*  RSn: Generated 21. October 2009
*
*/

#ifndef PHPALSLI15693_SW_INT_H
#define PHPALSLI15693_SW_INT_H

#include <ph_Status.h>

/** \addtogroup ph_Private
* @{
*/

/** \name Constats
*/
/*@{*/
/** IC Manufacturer Code of NXP. */
#define PHPAL_SLI15693_SW_NXP_MFG_CODE              0x04U
/** Time extension in microseconds for all commands.  */
#define PHPAL_SLI15693_SW_EXT_TIME_US               60
/** Waiting time T1 in us (ISO/IEC15693, 9.1.4.) */
#define PHPAL_SLI15693_SW_T1_WAITING_TIME           324U
/** Waiting time T2 in us (ISO/IEC15693, 9.1.4.) */
#define PHPAL_SLI15693_SW_T2_WAITING_TIME           310U
/** UID length in bits when complete. */
#define PHPAL_SLI15693_SW_UID_COMPLETE              64U
/** Default flags (DATA_RATE is set). */
#define PHPAL_SLI15693_SW_FLAGS_DEFAULT             0x02U
/** Slot timeout */
#define PHPAL_SLI15693_SW_TIMEOUT_SLOT_US           PHPAL_SLI15693_SW_T1_WAITING_TIME + PHPAL_SLI15693_SW_T2_WAITING_TIME
/*@}*/

/** \name Mandatory commands
*/
/*@{*/
/** Anticollision inventory cmd code */
#define PHPAL_SLI15693_SW_CMD_INVENTORY        0x01U
/** Stay Quiet cmd code */
#define PHPAL_SLI15693_SW_CMD_STAY_QUIET       0x02U
/*@}*/

/** \name Optional commands
*/
/*@{*/
/** Select cmd code */
#define PHPAL_SLI15693_SW_CMD_SELECT            0x25U
/** Reset to ready cmd code */
#define PHPAL_SLI15693_SW_CMD_RESET_TO_READY    0x26U
/*@}*/

/** \name Custom commands
*/
/*@{*/
/** Inventory read cmd code */
#define PHPAL_SLI15693_SW_CMD_INVENTORY_READ            0xA0U
/** Fast inventory read cmd code */
#define PHPAL_SLI15693_SW_CMD_FAST_INVENTORY_READ       0xA1U
/** Inventory page read cmd code */
#define PHPAL_SLI15693_SW_CMD_INVENTORY_PAGE_READ       0xB0U
/** Fast inventory page read cmd code */
#define PHPAL_SLI15693_SW_CMD_FAST_INVENTORY_PAGE_READ  0xB1U
/*@}*/

/**
* \brief Perform all kinds of Inventory commands.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid response received.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalSli15693_Sw_InventoryEx(
                                        phpalSli15693_Sw_DataParams_t* pDataParams,     /**< [In] Pointer to this layers parameter structure. */
                                        /** [In] defines which way of (Fast)Inventory(Page)Read is done.\n
                                        * \c bOption bits are defined as follows:\n
                                        * \li b1 = 0 -> InventoryRead
                                        * \li b1 = 1 -> InventoryPageRead
                                        * \li b2 = 0 -> normal
                                        * \li b2 = 1 -> FAST */
                                        uint8_t bOption,                                
                                        uint8_t bFlags,             /**< [In] Request flags byte. */
                                        uint8_t bAfi,               /**< [In] Application Family Identifier. */
                                        uint8_t * pMask,            /**< [In] UID mask, holding known UID bits. */
                                        uint8_t bMaskBitLength,     /**< [In] Number of UID bits within pMask. */
                                        uint8_t bBlockNo,           /**< [In] Block number of first block to read. */
                                        uint16_t wNoOfBlocks,       /**< [In] Number of blocks to read */
                                        uint8_t * pUid,             /**< [Out] Received Uid */
                                        uint8_t * pUidLength,       /**< [Out]  Number of received UID bytes. */
                                        uint8_t * pData,            /**< [Out]  Received data. */
                                        uint16_t * pLength          /**< [Out]  Number of received data bytes. */
                                        );

/** @}
* end of ph_Private
*/

#endif /* PHPALSLI15693_SW_INT_H */
