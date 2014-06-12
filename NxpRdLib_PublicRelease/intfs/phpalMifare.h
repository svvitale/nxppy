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
* Generic MIFARE(R) Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.6 $
* $Date: Fri Apr 15 09:27:18 2011 $
*
* History:
*  CHu: Generated 31. July 2009
*
*/

#ifndef PHPALMIFARE_H
#define PHPALMIFARE_H

#include <ph_Status.h>
#include <phhalHw.h>

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#ifdef NXPBUILD__PHPAL_MIFARE_STUB

/** \defgroup phpalMifare_Stub Component : Stub
* \brief Component without functionality to ease implementation of additional busses.
* @{
*/

#define PHPAL_MIFARE_STUB_ID        0x01    /**< ID for Stub MIFARE layer. */
    
/**
* \brief Stub PAL-MIFARE parameter structure
*/
typedef struct
{
    uint16_t       wId;         /**< Layer ID for this BAL component, NEVER MODIFY! */
    /* TODO: Place private parameters which are needed across different functions here. */
} phpalMifare_Stub_DataParams_t;

/**
* \brief Initialise this layer.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phpalMifare_Stub_Init(
                                 phpalMifare_Stub_DataParams_t * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                                 uint16_t wSizeOfDataParams                      /**< [In] Specifies the size of the data parameter structure. */
                                 /* TODO: Place additional parameters here if needed. */
                                 );

/** @} */
#endif /* NXPBUILD__PHPAL_MIFARE_STUB */

#ifdef NXPBUILD__PHPAL_MIFARE_SW

/** \defgroup phpalMifare_Sw Component : Software
* @{
*/

#define PHPAL_MIFARE_SW_ID          0x02    /**< ID for Software MIFARE layer. */

/**
* \brief Software PAL-MIFARE parameter structure
*/
typedef struct
{
    uint16_t wId;                       /**< Layer ID for this component, NEVER MODIFY! */
    void  * pHalDataParams;             /**< Pointer to the parameter structure of the underlying HAL layer. */
    void  * pPalI14443p4DataParams;     /**< Pointer to the parameter structure of the underlying ISO14443-4 layer. */
} phpalMifare_Sw_DataParams_t;

/**
* \brief Initialise this layer.
*
* \b Remark: \c pPalI14443p4DataParams can be NULL in case \ref phpalMifare_ExchangeL4 and
* \ref phpalMifare_ExchangePc are not needed.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phpalMifare_Sw_Init(
                               phpalMifare_Sw_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
                               uint16_t wSizeOfDataParams,                  /**< [In] Specifies the size of the data parameter structure. */
                               void * pHalDataParams,                       /**< [In] Pointer to the parameter structure of the underlying HAL layer. */
                               void * pPalI14443p4DataParams                /**< [In] Pointer to the parameter structure of the underlying ISO14443-4 layer. */
                               );

/** @} */
#endif /* NXPBUILD__PHPAL_MIFARE_SW */


#ifdef NXPBUILD__PHPAL_MIFARE_RD710

/** \defgroup phpalMifare_Rd710 Component : Rd710
* \brief Component without functionality to ease implementation of additional busses.
* @{
*/

#define PHPAL_MIFARE_RD710_ID          0x04    /**< ID for RD710 MIFARE layer. */

/**
* \brief Software PAL-MIFARE parameter structure
*/
typedef struct
{
    uint16_t wId;                       /**< Layer ID for this component, NEVER MODIFY! */
    phhalHw_Rd710_DataParams_t * pHalDataParams;             /**< Pointer to the parameter structure of the underlying HAL layer. */
} phpalMifare_Rd710_DataParams_t;

/**
* \brief Initialise this layer.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phpalMifare_Rd710_Init(
                                        phpalMifare_Rd710_DataParams_t * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                                        uint16_t wSizeOfDataParams,                      /**< [In] Specifies the size of the data parameter structure. */
                                        phhalHw_Rd710_DataParams_t * pHalDataParams      /**< [In] Pointer to the parameter structure of the underlying HAL layer. */
                                        );

/** @} */
#endif /* NXPBUILD__PHPAL_MIFARE_RD710 */



#ifdef NXPBUILD__PHPAL_MIFARE

/** \addtogroup ph_Error
* phpalMifare Custom Errors
* @{
*/

/** \name phpalMifare Error Codes
*/
/*@{*/
#define PHPAL_MIFARE_ERR_NAK0   (PH_ERR_CUSTOM_BEGIN+0)     /**< NAK 0 */
#define PHPAL_MIFARE_ERR_NAK1   (PH_ERR_CUSTOM_BEGIN+1)     /**< NAK 1 */
#define PHPAL_MIFARE_ERR_NAK4   (PH_ERR_CUSTOM_BEGIN+2)     /**< NAK 4 */
#define PHPAL_MIFARE_ERR_NAK5   (PH_ERR_CUSTOM_BEGIN+3)     /**< NAK 5 */
/*@}*/

/** @} */

/** \defgroup phpalMifare MIFARE(R)
* \brief These Components implement the MIFARE(R) Classic, MIFARE(R) Ultralight,
* MIFARE(R) DESFire and MIFARE(R) Plus products.
* @{
*/

/**
* \name Authenticate Options
*/
/*@{*/
#define PHPAL_MIFARE_KEYA               0x0AU   /**< MIFARE Classic Key Type A. */
#define PHPAL_MIFARE_KEYB               0x0BU   /**< MIFARE Classic Key Type B. */
#define PHPAL_MIFARE_KEY_LENGTH         0x06U   /**< Length of a MIFARE Classic key (for completeness). */
/*@}*/

/**
* \brief Perform ISO14443-3 Data Exchange with MIFARE Picc.
*
* \c wOption can be one of:\n
* \li #PH_EXCHANGE_DEFAULT
* \li #PH_EXCHANGE_BUFFER_FIRST
* \li #PH_EXCHANGE_BUFFER_CONT
* \li #PH_EXCHANGE_BUFFER_LAST
*
* Alternatively, the following bits can be combined:\n
* \li #PH_EXCHANGE_BUFFERED_BIT
* \li #PH_EXCHANGE_LEAVE_BUFFER_BIT
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalMifare_ExchangeL3(
                                  void * pDataParams,       /**< [In] Pointer to this layer's parameter structure. */
                                  uint16_t wOption,         /**< [In] Option parameter. */
                                  uint8_t * pTxBuffer,      /**< [In] Data to transmit. */
                                  uint16_t wTxLength,       /**< [In] Length of data to transmit. */
                                  uint8_t ** ppRxBuffer,    /**< [Out] Pointer to received data. */
                                  uint16_t * pRxLength      /**< [Out] number of received data bytes. */
                                  );

/**
* \brief Perform ISO14443-4 Data Exchange with MIFARE Picc.
*
* \c wOption can be one of:\n
* \li #PH_EXCHANGE_DEFAULT
* \li #PH_EXCHANGE_TXCHAINING
* \li #PH_EXCHANGE_RXCHAINING
* \li #PH_EXCHANGE_RXCHAINING_BUFSIZE
*
* Additionally, the following options are also available:\n
* \li #PH_EXCHANGE_BUFFER_FIRST
* \li #PH_EXCHANGE_BUFFER_CONT
* \li #PH_EXCHANGE_BUFFER_LAST
*
* Alternatively to the FIRST/CONT/LAST options, the following bits can be combined:\n
* \li #PH_EXCHANGE_BUFFERED_BIT
* \li #PH_EXCHANGE_LEAVE_BUFFER_BIT
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalMifare_ExchangeL4(
                                  void * pDataParams,       /**< [In] Pointer to this layer's parameter structure. */
                                  uint16_t wOption,         /**< [In] Option parameter. */
                                  uint8_t * pTxBuffer,      /**< [In] Data to transmit. */
                                  uint16_t wTxLength,       /**< [In] Length of data to transmit. */
                                  uint8_t ** ppRxBuffer,    /**< [Out] Pointer to received data. */
                                  uint16_t * pRxLength      /**< [Out] number of received data bytes. */
                                  );

/**
* \brief Perform Proximity-Check Data Exchange with MIFARE Picc.
*
* \b Note: The \c wOption parameter is currently RFU.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalMifare_ExchangePc(
                                  void * pDataParams,       /**< [In] Pointer to this layer's parameter structure. */
                                  uint16_t wOption,         /**< [In] Option parameter. */
                                  uint8_t * pTxBuffer,      /**< [In] Data to transmit. */
                                  uint16_t wTxLength,       /**< [In] Length of data to transmit. */
                                  uint8_t ** ppRxBuffer,    /**< [Out] Pointer to received data. */
                                  uint16_t * pRxLength      /**< [Out] number of received data bytes. */
                                  );

/**
* \brief Perform Raw (No CRC, No Parity) Data Exchange with MIFARE Picc.
*
* \c wOption can be one of:\n
* \li #PH_EXCHANGE_DEFAULT
* \li #PH_EXCHANGE_BUFFER_FIRST
* \li #PH_EXCHANGE_BUFFER_CONT
* \li #PH_EXCHANGE_BUFFER_LAST
*
* Alternatively, the following bits can be combined:\n
* \li #PH_EXCHANGE_BUFFERED_BIT
* \li #PH_EXCHANGE_LEAVE_BUFFER_BIT
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalMifare_ExchangeRaw(
                                   void * pDataParams,      /**< [In] Pointer to this layer's parameter structure. */
                                   uint16_t wOption,        /**< [In] Option parameter. */
                                   uint8_t * pTxBuffer,     /**< [In] Data to transmit. */
                                   uint16_t wTxLength,      /**< [In] Length of input data. */
                                   uint8_t bTxLastBits,     /**< [In] Number of valid bits of last byte (Tx). */
                                   uint8_t ** ppRxBuffer,   /**< [Out] Pointer to received data. */
                                   uint16_t * pRxLength,    /**< [Out] Number of received data bytes including incomplete byte. */
                                   uint8_t * pRxLastBits    /**< [Out] Number of valid bits of last byte (Rx). */
                                   );

/**
* \brief Perform MIFARE(R) Authenticate command with Picc using a key number.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_IO_TIMEOUT Error in authentication.
* \retval #PH_ERR_AUTH_ERROR Error in authentication.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalMifare_MfcAuthenticateKeyNo(
    void * pDataParams,     /**< [In] Pointer to this layer's parameter structure. */
    uint8_t bBlockNo,       /**< [In] Blocknumber on card to authenticate to. */
    uint8_t bKeyType,       /**< [In] Either #PHPAL_MIFARE_KEYA or #PHPAL_MIFARE_KEYB */
    uint16_t wKeyNo,        /**< [In] Key number to be used in authentication. */
    uint16_t wKeyVersion,   /**< [In] Key version to be used in authentication. */
    uint8_t * pUid          /**< [In] Serial number of current cascade level; uint8_t[4]. */
    );

/**
* \brief Perform MIFARE(R) Authenticate command with Picc using a key.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_IO_TIMEOUT Error in authentication.
* \retval #PH_ERR_AUTH_ERROR Error in authentication.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalMifare_MfcAuthenticate(
                                       void * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                                       uint8_t bBlockNo,    /**< [In] Blocknumber on card to authenticate to. */
                                       uint8_t bKeyType,    /**< [In] Either #PHPAL_MIFARE_KEYA or #PHPAL_MIFARE_KEYB */
                                       uint8_t * pKey,      /**< [In] Key to be used in authentication. */
                                       uint8_t * pUid       /**< [In] Serial number of current cascade level; uint8_t[4]. */
                                       );

/** @} */
#endif /* NXPBUILD__PHPAL_MIFARE */

#ifdef __cplusplus
} /* Extern C */
#endif

#endif /* PHPALMIFARE_H */
