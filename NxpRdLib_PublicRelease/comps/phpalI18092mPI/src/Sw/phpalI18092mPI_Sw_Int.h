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
* Internal definitions for software ISO18092 passive initiator mode Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.1 $
* $Date: Fri Apr 15 09:29:15 2011 $
*
* History:
*  CEn: Generated 07. September 2010
*/

#ifndef PHPALI18092MPI_SW_INT_H
#define PHPALI18092MPI_SW_INT_H

#include <ph_Status.h>

/** \addtogroup ph_Private
* @{
*/

/** Macro which checks for invalid block status. */
#define PHPAL_I18092MPI_SW_IS_INVALID_BLOCK_STATUS(bStatus)                                             \
    ((                                                                                                  \
    (((bStatus) & PH_ERR_MASK) == PH_ERR_IO_TIMEOUT) ||                                                 \
    (((bStatus) & PH_ERR_MASK) == PH_ERR_INTEGRITY_ERROR) ||                                            \
    (((bStatus) & PH_ERR_MASK) == PH_ERR_FRAMING_ERROR) ||                                              \
    (((bStatus) & PH_ERR_MASK) == PH_ERR_COLLISION_ERROR))                                              \
    ? 1 : 0                                                                                             \
    )

/** Macro which checks if given PDU is timeout PDU. */
#define PHPAL_I18092MPI_SW_IS_TIMEOUT(bPfb)                                                             \
    ((                                                                                                  \
    (((bPfb) & PHPAL_I18092MPI_SW_PFB_PDU_TYPE_MASK) == PHPAL_I18092MPI_SW_PFB_SUPERVISORY_PDU_MASK) && \
    (((bPfb) & PHPAL_I18092MPI_SW_PFB_OPTION_MASK) == PHPAL_I18092MPI_SW_PFB_OPTION_MASK))              \
    ? 1 : 0                                                                                             \
    )

/** Macro which checks if given PDU is ATN PDU. */
#define PHPAL_I18092MPI_SW_IS_ATTENTION(bPfb)                                                           \
    ((                                                                                                  \
    (((bPfb) & PHPAL_I18092MPI_SW_PFB_PDU_TYPE_MASK) == PHPAL_I18092MPI_SW_PFB_SUPERVISORY_PDU_MASK) && \
    (((bPfb) & PHPAL_I18092MPI_SW_PFB_OPTION_MASK) == 0x00))                                            \
    ? 1 : 0                                                                                             \
    )

/** Macro which checks if given PDU is ACK PDU. */
#define PHPAL_I18092MPI_SW_IS_ACK(bPfb)                                                                 \
    ((                                                                                                  \
    (((bPfb) & PHPAL_I18092MPI_SW_PFB_PDU_TYPE_MASK) == PHPAL_I18092MPI_SW_PFB_ACK_PDU_MASK) &&         \
    (((bPfb) & PHPAL_I18092MPI_SW_PFB_OPTION_MASK) == 0x00))                                            \
    ? 1 : 0                                                                                             \
    )

/** Macro which checks if given PDU is NACK PDU. */
#define PHPAL_I18092MPI_SW_IS_NACK(bPfb)                                                                \
    ((                                                                                                  \
    (((bPfb) & PHPAL_I18092MPI_SW_PFB_PDU_TYPE_MASK) == PHPAL_I18092MPI_SW_PFB_ACK_PDU_MASK) &&         \
    (((bPfb) & PHPAL_I18092MPI_SW_PFB_OPTION_MASK) == PHPAL_I18092MPI_SW_PFB_OPTION_MASK))              \
    ? 1 : 0                                                                                             \
    )

/** Macro which checks if given I-PDU is chaining. */
#define PHPAL_I18092MPI_SW_IS_CHAINING(bPfb)                                                            \
    ((                                                                                                  \
    (((bPfb) & PHPAL_I18092MPI_SW_PFB_PDU_TYPE_MASK) == PHPAL_I18092MPI_SW_PFB_INFORMATION_PDU_MASK) && \
    (((bPfb) & PHPAL_I18092MPI_SW_PFB_OPTION_MASK) == PHPAL_I18092MPI_SW_PFB_OPTION_MASK))              \
    ? 1 : 0                                                                                             \
    )

/** Macro which checks if given I-PDU is not chaining. */
#define PHPAL_I18092MPI_SW_IS_NOT_CHAINING(bPfb)                                                        \
    ((                                                                                                  \
    (((bPfb) & PHPAL_I18092MPI_SW_PFB_PDU_TYPE_MASK) == PHPAL_I18092MPI_SW_PFB_INFORMATION_PDU_MASK) && \
    (((bPfb) & PHPAL_I18092MPI_SW_PFB_OPTION_MASK) == 0x00))                                            \
    ? 1 : 0                                                                                             \
    )

/** Macro which checks if given PDU is an I-PDU. */
#define PHPAL_I18092MPI_SW_IS_INFORMATION_PDU(bPfb)                                                     \
    (                                                                                                   \
    (((bPfb) & PHPAL_I18092MPI_SW_PFB_PDU_TYPE_MASK) == PHPAL_I18092MPI_SW_PFB_INFORMATION_PDU_MASK)    \
    ? 1 : 0                                                                                             \
    )

/** Macro used to increment PNI. */
#define PHPAL_I18092MPI_SW_INCREMENT_PNI(bPni)                                                          \
    (((bPni) == 3) ? 0 : ((bPni) + 1))

/** Start Byte to be added to the protocol header in case underlaying protocol is ISO14443. */
#define PHPAL_I18092MPI_SW_START_BYTE                   0xF0U

/** Request command code. */
#define PHPAL_I18092MPI_SW_CMD_REQUEST                  0xD4U

/** Response command code. */
#define PHPAL_I18092MPI_SW_CMD_RESPONSE                 0xD5U

/** Attribute request command code. */
#define PHPAL_I18092MPI_SW_CMD_ATR_REQ                  0x00U

/** Bit position of LRi field within PPi byte for attribute request command. */
#define PHPAL_I18092MPI_SW_ATR_PPI_LRI_BIT              0x04U

/** Attribute response command code. */
#define PHPAL_I18092MPI_SW_CMD_ATR_RES                  0x01U

/** Parameter select request command code. */
#define PHPAL_I18092MPI_SW_CMD_PSL_REQ                  0x04U

/** Parameter select response command code. */
#define PHPAL_I18092MPI_SW_CMD_PSL_RES                  0x05U

/** Data exchange protocol request command code. */
#define PHPAL_I18092MPI_SW_CMD_DEP_REQ                  0x06U

/** Data exchange protocol response command code. */
#define PHPAL_I18092MPI_SW_CMD_DEP_RES                  0x07U

/** Deselect request command code. */
#define PHPAL_I18092MPI_SW_CMD_DSL_REQ                  0x08U

/** Deselect response command code. */
#define PHPAL_I18092MPI_SW_CMD_DSL_RES                  0x09U

/** Release request command code. */
#define PHPAL_I18092MPI_SW_CMD_RLS_REQ                  0x0AU

/** Release response command code. */
#define PHPAL_I18092MPI_SW_CMD_RLS_RES                  0x0BU

/** Position of NFCID3 within ATR_RES. */
#define PHPAL_I18092MPI_SW_ATR_RES_NFCID3_POS           0x02U

/** Position of DID within ATR_RES. */
#define PHPAL_I18092MPI_SW_ATR_RES_DID_POS              12U

/** Position of BS(T) within ATR_RES. */
#define PHPAL_I18092MPI_SW_ATR_RES_BST_POS              13U

/** Position of BR(T) within ATR_RES. */
#define PHPAL_I18092MPI_SW_ATR_RES_BRT_POS              14U

/** Position of TO within ATR_RES. */
#define PHPAL_I18092MPI_SW_ATR_RES_TO_POS               15U

/** Position of PP(T) within ATR_RES. */
#define PHPAL_I18092MPI_SW_ATR_RES_PPT_POS              16U

/** Gt_available bit wihtin PP(T) byte of ATR_RES. */
#define PHPAL_I18092MPI_SW_ATR_RES_PPT_GT_AVAILABLE     0x02U

/** NAD_used bit wihtin PP(T) byte of ATR_RES. */
#define PHPAL_I18092MPI_SW_ATR_RES_PPT_NAD_USED         0x01U

/** Bit mask within PFB identifying an information PDU. */
#define PHPAL_I18092MPI_SW_PFB_INFORMATION_PDU_MASK     0x00U

/** Bit mask within PFB identifying an ACK/NACK PDU. */
#define PHPAL_I18092MPI_SW_PFB_ACK_PDU_MASK             0x40U

/** Bit mask within PFB identifying a supervisory PDU. */
#define PHPAL_I18092MPI_SW_PFB_SUPERVISORY_PDU_MASK     0x80U

/** Bit mask within PFB to get type of PDU. */
#define PHPAL_I18092MPI_SW_PFB_PDU_TYPE_MASK            0xE0U

/** Bit mask within PFB for checking NAD enabler. */
#define PHPAL_I18092MPI_SW_PFB_NAD_MASK                 0x08U

/** Bit mask within PFB for checking DID enabler. */
#define PHPAL_I18092MPI_SW_PFB_DID_MASK                 0x04U

/** Bit mask within PFB for getting PNI. */
#define PHPAL_I18092MPI_SW_PFB_PNI_MASK                 0x03U

/** Bit mask within PDU for getting option field (=ACK or ATTENTION or MI). */
#define PHPAL_I18092MPI_SW_PFB_OPTION_MASK              0x10U

/** Activation response waiting time in milliseconds, NFCForum-TS-DigitalProtocol-1.0 section A.10. */
#define PHPAL_I18092MPI_SW_DELTA_T_INITIATOR_MS         100U

/** Time extension in microseconds for all commands, NFCForum-TS-DigitalProtocol-1.0 section A.10. */
#define PHPAL_I18092MPI_SW_DELTA_RWT_US                 2U

/** Activation response waiting time in milliseconds, NFCForum-TS-DigitalProtocol-1.0 section A.10. deltaRWT is included in this case. */
#define PHPAL_I18092MPI_SW_RWT_ACTIVATION_MS            1239U

/** Minimum response waiting time, ISO/IEC 18092:2004(E) section 12.5.1.2.1. */
#define PHPAL_I18092MPI_SW_RWT_MIN_US                   302U

/** Maximum response waiting time, ISO/IEC 18092:2004(E) section A.10. */
#define PHPAL_I18092MPI_SW_RWT_MAX_US                   4947968UL

/** Minimum frame size, NFCForum-TS-DigitalProtocol-1.0. */
#define PHPAL_I18092MPI_SW_MIN_FRAMESIZE                3U

/** Maximum frame size, NFCForum-TS-DigitalProtocol-1.0. */
#define PHPAL_I18092MPI_SW_MAX_FRAMESIZE                255U

/** Maximum Retry count, NFCForum-TS-DigitalProtocol-1.0 section A.10. */
#define PHPAL_I18092MPI_SW_MAX_RETRIES                  5U

/** Default (=minimum) Maximum Retry count, NFCForum-TS-DigitalProtocol-1.0 section A.10. */
#define PHPAL_I18092MPI_SW_MAX_RETRIES_DEFAULT          2U

/** Frame length must be min. 17 bytes during activation. (NFCForum-TS-DigitalProtocol-1.0, section 14.6.1.1. */
#define PHPAL_I18092MPI_SW_MIN_ACTIVATION_FRAME_LENGTH  17U

/** Frame length is limited to 64 bytes during activation. (NFCForum-TS-DigitalProtocol-1.0, section 14.6.1.1. */
#define PHPAL_I18092MPI_SW_MAX_ACTIVATION_FRAME_LENGTH  64U

/** State information PDU to be transmitted. */
#define PHPAL_I18092MPI_SW_STATE_INFORMATION_PDU_TX     0x00U

/** State ACK PDU to be transmitted. */
#define PHPAL_I18092MPI_SW_STATE_ACK_PDU_TX             0x01U

/** State information PDU to be received. */
#define PHPAL_I18092MPI_SW_STATE_INFORMATION_PDU_RX     0x02U

/** Finished state. */
#define PHPAL_I18092MPI_SW_STATE_FINISHED               0x03U

/** State mask. */
#define PHPAL_I18092MPI_SW_STATE_MASK                   0x0FU

/** Retransmission of information PDU. */
#define PHPAL_I18092MPI_SW_STATE_RETRANSMIT_BIT         0x10U

/** Information PDU is chaining. */
#define PHPAL_I18092MPI_SW_STATE_CHAINING_BIT           0x20U

/** Information PDU is first block in chain. */
#define PHPAL_I18092MPI_SW_STATE_CHAINING_FIRST_BIT     0x40U

/** Information PDU is last block in chain. */
#define PHPAL_I18092MPI_SW_STATE_CHAINING_LAST_BIT      0x80U

/** Max length of the Header */
#define PHPAL_I18092MPI_SW_MAX_HEADER_LENGTH            0x07U

/**
* \brief Write header of transport protocol frame to internal buffer of HAL.
*
* Internal buffer is cleared first and protocol frame header is written without
* setting length field since frame size is not known at this point.
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalI18092mPI_Sw_WriteFrameHeader(
    phpalI18092mPI_Sw_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint16_t wOption,                               /**< [In] Option parameter. */
    uint8_t bCommandCode,                           /**< [In] Code of the request command to send. */
    uint8_t bDataLength                             /**< [In] Lenght of data field. */
    );

/**
* \brief Write PDU header to internal buffer of HAL.
*
* The following values for \c bPduMask are possible:\n
* \li #PHPAL_I18092MPI_SW_PFB_INFORMATION_PDU_MASK
* \li #PHPAL_I18092MPI_SW_PFB_ACK_PDU_MASK
* \li #PHPAL_I18092MPI_SW_PFB_SUPERVISORY_PDU_MASK
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phpalI18092mPI_Sw_WritePduHeader(
    phpalI18092mPI_Sw_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t bPduMask,                               /**< [In] Bit mask of the desired PDU type. */
    uint8_t bOption,                                /**< [In] Option bit; either #PH_ON or #PH_OFF. */
    uint8_t bDataLength                             /**< [In] Lenght of data field. */
    );

/**
* \brief Update the length field within protocol frame header.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phpalI18092mPI_Sw_UpdatePduHeader(
    phpalI18092mPI_Sw_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t bDataLength                             /**< [In] Lenght of data field. */
    );

/**
* \brief Retrieve the length of protocol frame header.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phpalI18092mPI_Sw_GetPduHeaderLength(
    phpalI18092mPI_Sw_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t * pProtLength                           /**< [Out] Complete protocol length starting at the command byte. */
    );

/**
* \brief Basic check if the received response is a valid frame.
*
* Frame is also normalized, i.e. start byte in case of 106kbps data rate is removed.
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful, frame seems to be a valid response frame.
* \retval #PH_ERR_PROTOCOL_ERROR Not a valid response frame.
*/
phStatus_t phpalI18092mPI_Sw_ValidateAndNormalizeResponseFrame(
    phpalI18092mPI_Sw_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t * pFrame,                               /**< [In] Pointer to the received data buffer. */
    uint16_t wFrameLength,                          /**< [In] Length of the received frame. */
    uint8_t bExpectedResponseCode,                  /**< [In] The expected response command code the frame should contain. */
    uint8_t ** ppValidatedFrame,                    /**< [Out] Pointer to validated and normalized frame. */
    uint16_t * pValidatedFrameLength,               /**< [Out] Length of validated and normalized frame. */
    uint8_t ** ppPayload,                           /**< [Out] Pointer to begin of data payload (header skipped). */
    uint16_t * pPayloadLength                       /**< [Out] Length of data payload. */
    );

/**
* \brief Convert data rate read out from HAL to ISO18092 compatible data rate value (PHPAL_I18092MPI_DATARATE_*).
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_INTERNAL_ERROR Data rate can't be converted.
*/
phStatus_t phpalI18092mPI_Sw_ConvertDatarate(
    uint16_t wHalDatarate,      /**< [In] Datarate read out from HAL. */
    uint8_t * pI18092Datarate   /**< [Out] Pointer to a converted datarate; uint8_t[1] */
    );

/**
* \brief Transmit PDU to target and receive response.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalI18092mPI_Sw_TransceivePdu(
    phpalI18092mPI_Sw_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint16_t wOption,                               /**< [In] Option parameter. */
    uint8_t * pTxBuffer,                            /**< [In] Data to transmit. */
    uint16_t wTxLength,                             /**< [In] Length of data to transmit. */
    uint8_t ** ppRawResponse,                       /**< [Out] Pointer to raw DEP frame. */
    uint16_t * pRawResponseLength,                  /**< [Out] Length of raw DEP frame. */
    uint8_t ** ppNormalizedResponse,                /**< [Out] Pointer to validated and normalized frame. */
    uint16_t * pNormalizedResponseLength,           /**< [Out] Length of validated and normalized frame. */
    uint8_t ** ppPayload,                           /**< [Out] Pointer to begin of data payload (header skipped). */
    uint16_t * pPayloadLength                       /**< [Out] Length of data payload. */
    );

/** @}
* end of ph_Private
*/

#endif /* PHPALI18092MPI_SW_INT_H */
