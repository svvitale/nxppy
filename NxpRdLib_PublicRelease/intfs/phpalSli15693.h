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
* Generic Sli15693 Component of Reader Library Framework.
* $Author: jayaprakash.desai $
* $Revision: 1.3 $
* $Date: Tue May 31 13:56:20 2011 $
*
* History:
*  RSn: Generated 21. October 2009
*
*/

#ifndef PHPALSLI15693_H
#define PHPALSLI15693_H

#include <ph_Status.h>

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#ifdef NXPBUILD__PHPAL_SLI15693_SW

/** \defgroup phpalSli15693_Sw Component : Software
* @{
*/

#define PHPAL_SLI15693_SW_ID   0x01    /**< ID for Software Sli15693 layer. */

/**
* \brief Software Sli15693 PAL parameter structure
*/
typedef struct
{
    uint16_t wId;               /**< Layer ID for this component, NEVER MODIFY! */
    void  * pHalDataParams;     /**< Pointer to the parameter structure of the underlying layer.*/
    uint16_t wAdditionalInfo;   /**< Holds ther last error code sent by the VICC. */
    uint8_t bFlags;             /**< Flags. */
    uint8_t pUid[8];            /**< The VICC's Unique Identifier, which always is of 8 bytes. */
    uint8_t bUidBitLength;      /**< The current length of the UID in bits. */
} phpalSli15693_Sw_DataParams_t;

/**
* \brief Initialise this layer.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalSli15693_Sw_Init(
                                 phpalSli15693_Sw_DataParams_t * pDataParams,   /**< [In] Pointer to this layers parameter structure. */
                                 uint16_t wSizeOfDataParams,                    /**< [In] Specifies the size of the data parameter structure. */
                                 void * pHalDataParams                          /**< [In] Pointer to the parameter structure of the underlying layer.*/
                                 );

/** @} */
#endif /* NXPBUILD__PHPAL_SLI15693_SW */

#ifdef NXPBUILD__PHPAL_SLI15693

/** \defgroup phpalSli15693 ISO15693/ISO 18000-3m1
* \brief These Components implement the ISO/IEC 15693 + ICode SLI contactless protocol.
*
* \b Note: The "VCD waiting time before sending a subsequent request" <em>(see 9.3, ISO/IEC 15693-3:2009(E))</em>
* is handled in the respective functions.
*
* @{
*/

/**
* \name Configuration and Option definitions
*/
/*@{*/
#define PHPAL_SLI15693_CONFIG_FLAGS           0x0000U   /**< Set or get the flags byte. */
#define PHPAL_SLI15693_CONFIG_ADD_INFO        0x0001U   /**< Set or get the additional info word. */
#define PHPAL_SLI15693_CONFIG_TIMEOUT_US      0x0002U   /**< Set or get the current timeout in microseconds. */
#define PHPAL_SLI15693_CONFIG_TIMEOUT_MS      0x0003U   /**< Set or get the current timeout in milliseconds. */

#define PHPAL_SLI15693_EOF_NEXT_SLOT                0x00    /**< Send an EOF with timing configuration for an inventory round. */
#define PHPAL_SLI15693_EOF_NEXT_SLOT_INV_READ       0x01    /**< Send an EOF with configuration for an (fast-)inventory(page)read round. */
#define PHPAL_SLI15693_EOF_WRITE_ALIKE              0x02    /**< Send an EOF with timing configuration for write alike commands without waiting time. */
#define PHPAL_SLI15693_EOF_WRITE_ALIKE_WITH_WAIT    0x03    /**< Send an EOF with timing configuration for write alike commands with waiting time. */

#define PHPAL_SLI15693_ACTIVATE_ADDRESSED   0x0000U     /**<  Card will be in adressed state after ActivateCard command. */
#define PHPAL_SLI15693_ACTIVATE_SELECTED    0x0001U     /**<  Card will be in selected state after ActivateCard command. */
#define PHPAL_SLI15693_ACTIVATE_DEFAULT     0x0000U     /**< refer to #PHPAL_SLI15693_ACTIVATE_ADDRESSED. */

#define PHPAL_SLI15693_TIMEOUT_SHORT_US     324U        /**< Timeout T1 in us (ISO/IEC15693, 9.1.4.). */
#define PHPAL_SLI15693_TIMEOUT_LONG_US      20000U      /**< Extended timeout for some commands. */
/*@}*/

/**
* \name Request Flags 1 to 4 according to ISO15693.
*/
/*@{*/
#define PHPAL_SLI15693_FLAG_TWO_SUB_CARRIERS    0x01U   /**< Two sub-carriers shall be used (VICC to VCD). */
#define PHPAL_SLI15693_FLAG_DATA_RATE           0x02U   /**< High data rate shall be used (VICC to VCD). */
#define PHPAL_SLI15693_FLAG_INVENTORY           0x04U   /**< Shall be set for and inventory request. */
#define PHPAL_SLI15693_FLAG_PROTOCOL_EXTENSION  0x08U   /**< RFU, protocol format is extended. */
/*@}*/

/**
* \name Request Flags 5 to 7 according to ISO15693 when inventory flag is NOT set.
* Flag 8 is RFU and shall be set to zero.
*/
/*@{*/
#define PHPAL_SLI15693_FLAG_SELECTED    0x10U   /**< Only VICC in selected state shall respond. */
#define PHPAL_SLI15693_FLAG_ADDRESSED   0x20U   /**< UID field is included in command frame. */
#define PHPAL_SLI15693_FLAG_OPTION      0x40U   /**< Meaning defined by the command. */
/*@}*/

/**
* \name Request Flags 5 to 7 according to ISO15693 when inventory flag IS set.
* Flag 8 is RFU and shall be set to zero.
*/
/*@{*/
#define PHPAL_SLI15693_MASK_INVENTORY_FLAGS 0xF0U   /**< Inventory flags mask. */
#define PHPAL_SLI15693_FLAG_AFI             0x10U   /**< AFI field is present. */
#define PHPAL_SLI15693_FLAG_NBSLOTS         0x20U   /**< Use 1 slot instead of 16. */
/*#define PHPAL_SLI15693_FLAG_OPTION          0x40U*/   /**< Meaning defined by the command. */
/*@}*/

/**
* \name Response Flags 1 and 4 according to ISO15693.
* All others flags are RFU and shall not be interpreted.
*/
/*@{*/
#define PHPAL_SLI15693_FLAG_RESP_ERROR          0x01U   /**< An error occured. */
#define PHPAL_SLI15693_FLAG_RESP_EXTERNSION     0x08U   /**< RFU, protocol format is extended. */
/*@}*/

/**
* \name Response Errorcodes according to ISO15693.
* Codes ranging from A0 - DF are custom command error codes.
*/
/*@{*/
#define PHPAL_SLI15693_FLAG_ERROR_NOT_SUPPORTED 0x01U   /**< The command is not supported, i.e. the request code is not recognized. */
#define PHPAL_SLI15693_FLAG_ERROR_FORMAT        0x02U   /**< The command is not recognized, for example: a format error occurred. */
#define PHPAL_SLI15693_FLAG_ERROR_OPTION        0x03U   /**< The command option is not supported. */
#define PHPAL_SLI15693_FLAG_ERROR_GENERIC       0x04U   /**< Error with no information given or a specific error code is not supported. */
#define PHPAL_SLI15693_FLAG_ERROR_BLOCK_NA      0x05U   /**< The specified block is not available (doesn't exist). */
#define PHPAL_SLI15693_FLAG_ERROR_BLOCK_LOCKED1 0x06U   /**< The specified block is already locked and thus cannot be locked again. */
#define PHPAL_SLI15693_FLAG_ERROR_BLOCK_LOCKED2 0x07U   /**< The specified block is locked and its content cannot be changed. */
#define PHPAL_SLI15693_FLAG_ERROR_BLOCK_WRITE1  0x08U   /**< The specified block was not successfully programmed. */
#define PHPAL_SLI15693_FLAG_ERROR_BLOCK_WRITE2  0x09U   /**< The specified block was not successfully locked. */
/*@}*/

/** \name Lengths
*/
/*@{*/
/** UID length in bytes. */
#define PHPAL_SLI15693_UID_LENGTH       0x08U
/** block length in bytes. */
#define PHPAL_SLI15693_BLOCK_LENGTH     0x04U
/** number of bytes per page. */
#define PHPAL_SLI15693_PAGE_LENGTH      0x10U
/*@}*/

/** \name phpalSli15693 Error Codes
*/
/*@{*/
#define PHPAL_SLI15693_ERR_ISO15693     (PH_ERR_CUSTOM_BEGIN+0) /**< ISO15693 error from card; Errorcode can be accessed via #PHPAL_SLI15693_CONFIG_ADD_INFO. */
/*@}*/

/**
* \brief Perform a ISO15693 Inventory command.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid response received.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalSli15693_Inventory(
                                   void * pDataParams,      /**< [In] Pointer to this layers parameter structure. */
                                   uint8_t bFlags,          /**< [In] Request flags byte. */
                                   uint8_t bAfi,            /**< [In] Application Family Identifier. */
                                   uint8_t * pMask,         /**< [In] UID mask, holding known UID bits. */
                                   uint8_t bMaskBitLength,  /**< [In] Number of UID bits within pMask. */
                                   uint8_t * pDsfid,        /**< [Out] Data Storage Format Identifier. */
                                   uint8_t * pUid           /**< [Out] Received UID. */
                                   );

/**
* \brief Send a ISO15693 EOF.
*
* \c bOption can be one of:\n
* \li #PHPAL_SLI15693_EOF_NEXT_SLOT
* \li #PHPAL_SLI15693_EOF_WRITE_ALIKE
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid response received.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalSli15693_SendEof(
                                 void * pDataParams,        /**< [In] Pointer to this layers parameter structure. */
                                 uint8_t bOption,			/**< [In] Option parameter. */
                                 uint8_t * pDsfid,          /**< [Out] Data Storage Format Identifier. */
                                 uint8_t * pUid,            /**< [Out] Received Uid */
                                 uint8_t * pUidLength,      /**< [Out] Number of received UID bytes. */
                                 uint8_t * pData,           /**< [Out] Received data. */
                                 uint16_t * pDataLength     /**< [Out] Number of received data bytes. */
                                 );

/**
* \brief Perform a ISO15693 StayQuiet command.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid response received.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalSli15693_StayQuiet(
                                   void * pDataParams    /**< [In] Pointer to this layers parameter structure. */
                                   );

/**
* \brief Perform a ISO15693 Select command.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid response received.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalSli15693_Select(
                                void * pDataParams    /**< [In] Pointer to this layers parameter structure. */
                                );

/**
* \brief Perform a ISO15693 ResetToReady command.
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid response received.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalSli15693_ResetToReady(
                                      void * pDataParams    /**< [In] Pointer to this layers parameter structure. */
                                      );

/**
* \brief Perform ISO15693 Data Exchange with Picc.
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
phStatus_t phpalSli15693_Exchange(
                                  void * pDataParams,       /**< [In] Pointer to this layers parameter structure. */
                                  uint16_t wOption,         /**< [In] Option parameter. */
                                  uint8_t * pTxBuffer,      /**< [In] Data to transmit. Flags, IC MFC code and UID will be added automatically. */
                                  uint16_t wTxLength,       /**< [In] Length of data to transmit. */
                                  uint8_t ** ppRxBuffer,    /**< [Out] Pointer to received data. */
                                  uint16_t * pRxLength      /**< [Out] number of received data bytes. */
                                  );

/**
* \brief Perform ISO15693 ActivateCard command.
*
* \c wOption can be one of:\n
* \li #PHPAL_SLI15693_ACTIVATE_DEFAULT
* \li #PHPAL_SLI15693_ACTIVATE_SELECTED
* \li #PHPAL_SLI15693_ACTIVATE_ADDRESSED
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalSli15693_ActivateCard(
                                      void *   pDataParams,             /**< [In] Pointer to this layers parameter structure. */
                                      uint8_t  bOption,                 /**< [In] Selected or addressed */
                                      uint8_t  bFlags,                  /**< [In] Request flags byte. */
                                      uint8_t  bAfi,                    /**< [In] Application Family Identifier. */
                                      uint8_t * pMask,                  /**< [In] UID mask, holding known UID bits. */
                                      uint8_t  bMaskBitLength,          /**< [In] Number of UID bits within pMask. */
                                      uint8_t * pDsfid,                 /**< [Out] Data Storage Format Identifier. */
                                      uint8_t * pUid,                   /**< [Out]Received UID of first found card */
                                      uint8_t * pMoreCardsAvailable     /**< [Out] If there are more cards available this value is different from zero.    */
                                      );

/**
* \brief Retrieve the serial number.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_USE_CONDITION No UID available.
*/
phStatus_t phpalSli15693_GetSerialNo(
                                     void * pDataParams,    /**< [In] Pointer to this layers parameter structure. */
                                     uint8_t * pUid,        /**< [Out] Buffer, holding the UID (8 bytes) */
                                     uint8_t * bUidLength   /**< [Out] Length of received UID bytes. */
                                     );

/**
* \brief Perform a SetConfig command.
*
* \c wConfig can be one of:\n
* \li #PHPAL_SLI15693_CONFIG_FLAGS
* \li #PHPAL_SLI15693_CONFIG_ADD_INFO
* \li #PHPAL_SLI15693_CONFIG_TIMEOUT_US
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid response received.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalSli15693_SetConfig(
                                   void * pDataParams,  /**< [In] Pointer to this layers parameter structure. */
                                   uint16_t wConfig,    /**< [In] Item to configure. */
                                   uint16_t wValue      /**< [In] Value to set. */
                                   );

/**
* \brief Perform a GetConfig command.
*
* \c wConfig can be one of:\n
* \li #PHPAL_SLI15693_CONFIG_FLAGS
* \li #PHPAL_SLI15693_CONFIG_ADD_INFO
* \li #PHPAL_SLI15693_CONFIG_TIMEOUT_US
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid response received.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalSli15693_GetConfig(
                                   void * pDataParams,  /**< [In] Pointer to this layers parameter structure. */
                                   uint16_t wConfig,    /**< [In] Item to read. */
                                   uint16_t * pValue    /**< [In] Read value. */
                                   );

/**
* \brief Perform ISO15693 InventoryRead command.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_USE_CONDITION Feature not available.
*/
phStatus_t phpalSli15693_InventoryRead(
                                       void * pDataParams,      /**< [In] Pointer to this layers parameter structure. */
                                       uint8_t bFlags,          /**< [In] Request flags byte. */
                                       uint8_t bAfi,            /**< [In] Application Family Identifier. */
                                       uint8_t * pMask,         /**< [In] UID mask, holding known UID bits. */
                                       uint8_t bMaskBitLength,  /**< [In] Number of UID bits within pMask. */
                                       uint8_t bBlockNo,        /**< [In] Block number of first block to read. */
                                       uint16_t wNoOfBlocks,    /**< [In] Number of blocks to read */
                                       uint8_t * pUid,          /**< [Out] Received Uid */
                                       uint8_t * pUidLength,    /**< [Out] Number of received UID bytes. */
                                       uint8_t * pData,         /**< [Out] Received data. */
                                       uint16_t * pDataLength   /**< [Out] Number of received data bytes. */
                                       );

/**
* \brief Perform ISO15693 FastInventoryRead command.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_USE_CONDITION Feature not available.
*/
phStatus_t phpalSli15693_FastInventoryRead(
    void * pDataParams,         /**< [In] Pointer to this layers parameter structure. */
    uint8_t bFlags,             /**< [In] Request flags byte. */
    uint8_t bAfi,               /**< [In] Application Family Identifier. */
    uint8_t * pMask,            /**< [In] UID mask, holding known UID bits. */
    uint8_t bMaskBitLength,     /**< [In] Number of UID bits within pMask. */
    uint8_t bBlockNo,           /**< [In] Block number of first block to read. */
    uint16_t wNoOfBlocks,       /**< [In] Number of blocks to read */
    uint8_t * pUid,             /**< [Out] Received Uid */
    uint8_t * pUidLength,       /**< [Out]  Number of received UID bytes. */
    uint8_t * pData,            /**< [Out]  Received data. */
    uint16_t * pDataLength      /**< [Out]  Number of received data bytes. */
    );

/**
* \brief Perform ISO15693 InventoryPageRead command.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phpalSli15693_InventoryPageRead(
    void * pDataParams,         /**< [In] Pointer to this layers parameter structure. */
    uint8_t bFlags,             /**< [In] Request flags byte. */
    uint8_t bAfi,               /**< [In] Application Family Identifier. */
    uint8_t * pMask,            /**< [In] UID mask, holding known UID bits. */
    uint8_t bMaskBitLength,     /**< [In] Number of UID bits within pMask. */
    uint8_t bPageNo,            /**< [In] Block number of first page to read. */
    uint16_t wNoOfPages,        /**< [In] Number of pages to read */
    uint8_t * pUid,             /**< [Out] Received Uid */
    uint8_t * pUidLength,       /**< [Out] Number of received UID bytes. */
    uint8_t * pData,            /**< [Out] Received data. */
    uint16_t * pDataLength      /**< [Out] Number of received data bytes. */
    );

/**
* \brief Perform ISO15693 FastInventoryPageRead command.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phpalSli15693_FastInventoryPageRead(
    void * pDataParams,         /**< [In] Pointer to this layers parameter structure. */
    uint8_t bFlags,             /**< [In] Request flags byte. */
    uint8_t bAfi,               /**< [In] Application Family Identifier. */
    uint8_t * pMask,            /**< [In] UID mask, holding known UID bits. */
    uint8_t bMaskBitLength,     /**< [In] Number of UID bits within pMask. */
    uint8_t bPageNo,            /**< [In] Block number of first page to read. */
    uint16_t wNoOfPages,        /**< [In] Number of pages to read */
    uint8_t * pUid,             /**< [Out] Received Uid */
    uint8_t * pUidLength,       /**< [Out] Number of received UID bytes. */
    uint8_t * pData,            /**< [Out] Received data. */
    uint16_t * pDataLength      /**< [Out] Number of received data bytes. */
    );

/** @} */
#endif /* NXPBUILD__PHPAL_SLI15693 */

#ifdef __cplusplus
} /* Extern C */
#endif

#endif /* PHPALSLI15693_H */
