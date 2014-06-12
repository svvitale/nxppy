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
* Internal definitions for ISO14443-4 Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.4 $
* $Date: Fri Apr 15 09:27:26 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHPALI14443P4_SW_INT_H
#define PHPALI14443P4_SW_INT_H

#include <ph_Status.h>

/** \addtogroup ph_Private
* @{
*/

/** ISO 14443-4 Block Mask */
#define PHPAL_I14443P4_SW_BLOCK_MASK            0xC0U

/** ISO 14443-4 I-Block */
#define PHPAL_I14443P4_SW_I_BLOCK               0x00U
/** ISO 14443-4 I-Block RFU mask */
#define PHPAL_I14443P4_SW_I_BLOCK_RFU_MASK      0x22U
/** ISO 14443-4 I-Block RFU bits */
#define PHPAL_I14443P4_SW_I_BLOCK_RFU_BITS      0x02U

/** ISO 14443-4 R-Block */
#define PHPAL_I14443P4_SW_R_BLOCK               0x80U
/** ISO 14443-4 R-Block RFU mask */
#define PHPAL_I14443P4_SW_R_BLOCK_RFU_MASK      0x26U
/** ISO 14443-4 R-Block RFU bits */
#define PHPAL_I14443P4_SW_R_BLOCK_RFU_BITS      0x22U

/** ISO 14443-4 S-Block */
#define PHPAL_I14443P4_SW_S_BLOCK               0xC0U
/** ISO 14443-4 S-Block RFU mask */
#define PHPAL_I14443P4_SW_S_BLOCK_RFU_MASK      0x03U
/** ISO 14443-4 S-Block RFU bits */
#define PHPAL_I14443P4_SW_S_BLOCK_RFU_BITS      0x02U

/** Byte position of PCB byte */
#define PHPAL_I14443P4_SW_PCB_POS               0x00U

/** Blocknumber Bit within PCB */
#define PHPAL_I14443P4_SW_PCB_BLOCKNR           0x01U

/** Bit within PCB which signals presence of NAD byte */
#define PHPAL_I14443P4_SW_PCB_NAD_FOLLOWING     0x04U

/** Bit within PCB which signals presence of CID byte */
#define PHPAL_I14443P4_SW_PCB_CID_FOLLOWING     0x08U

/** Bit within PCB which signals chaining */
#define PHPAL_I14443P4_SW_PCB_CHAINING          0x10U

/** Bit within PCB which signals ACK */
#define PHPAL_I14443P4_SW_PCB_ACK               0x00U

/** Bit within PCB which signals NAK */
#define PHPAL_I14443P4_SW_PCB_NAK               0x10U

/** Bits within PCB which signal a DESELECT command */
#define PHPAL_I14443P4_SW_PCB_DESELECT          0x00U

/** Bits within PCB which signal a WTX command */
#define PHPAL_I14443P4_SW_PCB_WTX               0x30U

/** WTXM Bits of WTX INF byte */
#define PHPAL_I14443P4_SW_WTXM_BITS             0x3FU

/** FWI default value */
#define PHPAL_I14443P4_SW_FWI_DEFAULT           0x04U

/** FSCI default value */
#define PHPAL_I14443P4_SW_FSCI_DEFAULT          0x02U

/** FTW min in microseconds */
#define PHPAL_I14443P4_SW_FWT_MIN_US            302

/** FTW max in microseconds */
#define PHPAL_I14443P4_SW_FWT_MAX_US            4949000

/** S(DESELECT) FTW in microseconds */
#define PHPAL_I14443P4_SW_FWT_DESELECT_US       4833

/** Valid CID bits within CID field */
#define PHPAL_I14443P4_SW_CID_MASK              0x0FU

/** I-Block transmission mode  */
#define PHPAL_I14443P4_SW_STATE_I_BLOCK_TX      0x01U

/** I-Block reception mode  */
#define PHPAL_I14443P4_SW_STATE_I_BLOCK_RX      0x02U

/** Exchange finished mode  */
#define PHPAL_I14443P4_SW_STATE_FINISHED        0x0FU

/** An I-Block mode is retramsmitting */
#define PHPAL_I14443P4_SW_STATE_RETRANSMIT_BIT  0x40U

/** An I-Block mode is chaining */
#define PHPAL_I14443P4_SW_STATE_CHAINING_BIT    0x80U

/** Only 6 bits of the state are pure state codes */
#define PHPAL_I14443P4_SW_STATE_MASK            0x0FU

/** Default Maximum Retry count for ISO/IEC 14443-4:2008(E) Rule 4 and 5 */
#define PHPAL_I14443P4_SW_MAX_RETRIES_DEFAULT   2U

/** Time extension in microseconds for all commands.  */
#define PHPAL_I14443P4_EXT_TIME_US              60

/**
* \brief Build I-Block frame header
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalI14443p4_Sw_BuildIBlock(
                                        uint8_t bCidEnabled,    /**< [In] Set to != 0 to enable CID byte */
                                        uint8_t bCid,           /**< [In] CID byte */
                                        uint8_t bNadEnabled,    /**< [In] Set to != 0 to enable NAD byte */
                                        uint8_t bNad,           /**< [In] NAD byte */
                                        uint8_t bPcbBlockNum,   /**< [In] PCB block number bit */
                                        uint8_t bChaining,      /**< [In] Set to != 0 if chaining bit should be set */
                                        uint8_t * pTxBuffer,    /**< [Out] transmit buffer */
                                        uint16_t * pTxLength    /**< [Out] number of bytes to send */
                                        );

/**
* \brief Build R(ACK) / R(NAK) frames
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalI14443p4_Sw_BuildRBlock(
                                        uint8_t bCidEnabled,    /**< [In] Set to != 0 to enable CID byte */
                                        uint8_t bCid,           /**< [In] CID byte */
                                        uint8_t bPcbBlockNum,   /**< [In] PCB block number bit */
                                        uint8_t bIsAck,         /**< [In] Set to != 0 if an ACK should be generated */
                                        uint8_t * pTxBuffer,    /**< [Out] transmit buffer */
                                        uint16_t * pTxLength    /**< [Out] number of bytes to send */
                                        );

/**
* \brief Build S-Block frames
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalI14443p4_Sw_BuildSBlock(
                                        uint8_t bCidEnabled,    /**< [In] Set to != 0 to enable CID byte */
                                        uint8_t bCid,           /**< [In] CID byte */
                                        uint8_t bIsWtx,         /**< [In] Set to != 0 if a WTX frame should be generated */
                                        uint8_t bWtxm,          /**< [In] WTXM bits, used if /ref bIsWtx is set */
                                        uint8_t * pTxBuffer,    /**< [Out] transmit buffer */
                                        uint16_t * pTxLength    /**< [Out] number of bytes to send */
                                        );

/**
* \brief Check if received I-Block is valid.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_PROTOCOL_ERROR Block invalid.
*/
phStatus_t phpalI14443p4_Sw_IsValidIBlock(
    uint8_t bCheckCid,      /**< [In] Set to != 0 to enable CID check */
    uint8_t bCid,           /**< [In] Current CID for comparison */
    uint8_t bCheckNad,      /**< [In] Set to != 0 to enable NAD check */
    uint8_t bNad,           /**< [In] Current NAD for comparison */
    uint8_t * pRxBuffer,    /**< [In] Received data */
    uint16_t wRxLength      /**< [In] Number of received data bytes */
    );

/**
* \brief Check if received R-Block is valid.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_PROTOCOL_ERROR Block invalid.
*/
phStatus_t phpalI14443p4_Sw_IsValidRBlock(
    uint8_t bCheckCid,      /**< [In] Set to != 0 to enable CID check */
    uint8_t bCid,           /**< [In] Current CID for comparison */
    uint8_t * pRxBuffer,    /**< [In] Received data */
    uint16_t wRxLength      /**< [In] Number of received data bytes */
    );

/**
* \brief Check if received S-Block is valid.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_PROTOCOL_ERROR Block invalid.
*/
phStatus_t phpalI14443p4_Sw_IsValidSBlock(
    uint8_t bCheckCid,      /**< [In] Set to != 0 to enable CID check */
    uint8_t bCid,           /**< [In] Current CID for comparison */
    uint8_t * pRxBuffer,    /**< [In] Received data */
    uint16_t wRxLength      /**< [In] Number of received data bytes */
    );

/**
* \brief Perform actual exchanging and take care about error handling etc.
*
* Checks response and performs state transition and complete error & WTX handling if neecessary.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalI14443p4_Sw_IsoHandling(
                                        phpalI14443p4_Sw_DataParams_t * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                                        uint16_t wOption,                               /**< [In] option parameter. */
                                        uint8_t bRetryCount,                            /**< [In] number of already performed retries. */
                                        uint8_t * pTxBuffer,                            /**< [In] data to transmit */
                                        uint16_t wTxLength,                             /**< [In] length of input data */
                                        uint8_t ** ppRxBuffer,                          /**< [Out] Pointer to received data */
                                        uint16_t * pRxLength                            /**< [In] Received data bytes */
                                        );

/** @}
* end of ph_Private
*/

#endif /* PHPALI14443P4_SW_INT_H */
