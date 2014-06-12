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
* Generic MIFARE(R) Application Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:27:19 2011 $
*
* History:
*  CHu: Generated 31. July 2009
*
*/

#ifndef PHALMFC_H
#define PHALMFC_H

#include <ph_Status.h>
#include <phhalHw.h>
#include <phpalMifare.h>

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#ifdef NXPBUILD__PHAL_MFC_SW

/** \defgroup phalMfc_Sw Component : Software
* @{
*/

#define PHAL_MFC_SW_ID          0x01    /**< ID for Software MIFARE layer */

/**
* \brief Private parameter structure
*/
typedef struct
{
    uint16_t wId;                   /**< Layer ID for this component, NEVER MODIFY! */
    void * pPalMifareDataParams;    /**< Pointer to the parameter structure of the palMifare component. */
    void * pKeyStoreDataParams;     /**< Pointer to the parameter structure of the KeyStore component. */
} phalMfc_Sw_DataParams_t;

/**
* \brief Initialise this layer.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phalMfc_Sw_Init(
                           phalMfc_Sw_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
                           uint16_t wSizeOfDataParams,              /**< [In] Specifies the size of the data parameter structure. */
                           void * pPalMifareDataParams,             /**< [In] Pointer to the parameter structure of the palMifare component. */
                           void * pKeyStoreDataParams               /**< [In] Pointer to the parameter structure of the KeyStore component. */
                           );

/** @} */
#endif /* NXPBUILD__PHAL_MFC_SW */

#ifdef NXPBUILD__PHAL_MFC

/** \defgroup phalMfc MIFARE(R) Classic
* \brief These Functions implement the MIFARE(R) Classic commands.
* @{
*/

/**
* \name Authentication Parameters
*/
/*@{*/
#define PHAL_MFC_KEYA           0x0AU   /**< MIFARE(R) Key A. */
#define PHAL_MFC_KEYB           0x0BU   /**< MIFARE(R) Key B. */
/*@}*/

/**
* \name Block definitions
*/
/*@{*/
#define PHAL_MFC_DATA_BLOCK_LENGTH      16U     /**< Length of a MIFARE(R) Classic data block. */
#define PHAL_MFC_VALUE_BLOCK_LENGTH      4U     /**< Length of a MIFARE(R) Classic value block. */
/*@}*/

/**
* \name UID Type definitions
*/
/*@{*/
#define PHAL_MFC_UID_TYPE_UIDF0      0x00U     /**< MIFARE(R) Classic UID type UIDF0. */
#define PHAL_MFC_UID_TYPE_UIDF1      0x40U     /**< MIFARE(R) Classic UID type UIDF1. */
#define PHAL_MFC_UID_TYPE_UIDF2      0x20U     /**< MIFARE(R) Classic UID type UIDF2. */
#define PHAL_MFC_UID_TYPE_UIDF3      0x60U     /**< MIFARE(R) Classic UID type UIDF3. */
/*@}*/

/**
* \brief Perform MIFARE(R) Authenticate command with MIFARE Picc.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phalMfc_Authenticate(
                                void * pDataParams,     /**< [In] Pointer to this layer's parameter structure. */
                                uint8_t bBlockNo,       /**< [In] Blocknumber on card to authenticate to. */
                                uint8_t bKeyType,       /**< [In] Either #PHAL_MFC_KEYA or #PHAL_MFC_KEYB. */
                                uint16_t wKeyNumber,    /**< [In] Key number to be used in authentication. */
                                uint16_t wKeyVersion,   /**< [In] Key version to be used in authentication. */
                                uint8_t * pUid,         /**< [In] Complete serial number; uint8_t[4/7/10]. */
                                uint8_t bUidLength      /**< [In] Length of provided serial number (4/7/10). */
                                );

/**
* \brief Perform MIFARE(R) Read command with MIFARE Picc.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phalMfc_Read(
                        void * pDataParams,     /**< [In] Pointer to this layer's parameter structure. */
                        uint8_t bBlockNo,       /**< [In] block number to be read. */
                        uint8_t * pBlockData    /**< [Out] pBlockData[16] containing block read from the MIFARE(R) card */
                        );

/**
* \brief Perform MIFARE(R) Read Value command with MIFARE Picc.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful  
*/
phStatus_t phalMfc_ReadValue(
                             void * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                             uint8_t bBlockNo,      /**< [In] block number to be read. */
                             uint8_t * pValue,      /**< [Out] pValue[4] containing value (LSB first) read from the MIFARE(R) card */
                             uint8_t * pAddrData    /**< [Out] pAddrData containing address read from the MIFARE(R) card value block */
                             );

/**
* \brief Perform MIFARE(R) Write command with MIFARE Picc.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phalMfc_Write(
                         void * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                         uint8_t bBlockNo,      /**< [In] block number to be written. */
                         uint8_t * pBlockData   /**< [In] pBlockData[16] containing block to be written to the MIFARE(R) card */
                         );
/**
* \brief Perform MIFARE(R) Write Value command with MIFARE Picc.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phalMfc_WriteValue(
                              void * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
                              uint8_t bBlockNo,     /**< [In] block number to be written. */
                              uint8_t * pValue,     /**< [In] pValue[4] containing value (LSB first) to be written to the MIFARE(R) card */
                              uint8_t bAddrData     /**< [In] bAddrData containing address written to the MIFARE(R) card value block*/
                              );

/**
* \brief Perform MIFARE(R) Increment command with MIFARE Picc.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phalMfc_Increment(
                             void * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                             uint8_t bBlockNo,      /**< [In] block number to be incremented. */
                             uint8_t * pValue       /**< [In] pValue[4] containing value (LSB first) to be incremented on the MIFARE(R) card */
                             );

/**
* \brief Perform MIFARE(R) Decrement command with MIFARE Picc.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phalMfc_Decrement(
                             void * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                             uint8_t bBlockNo,      /**< [In] block number to be decremented. */
                             uint8_t * pValue       /**< [In] pValue[4] containing value (LSB first) to be decremented on the MIFARE(R) card */
                             );

/**
* \brief Perform MIFARE(R) Transfer command with MIFARE Picc.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phalMfc_Transfer(
                            void * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
                            uint8_t bBlockNo    /**< [In] block number the transfer buffer shall be transferred to. */
                            );

/**
* \brief Perform MIFARE(R) Restore command with MIFARE Picc.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phalMfc_Restore(
                           void * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                           uint8_t bBlockNo     /**< [In] block number the transfer buffer shall be restored from. */                                  
                           );

/**
* \brief Perform MIFARE(R) Increment Transfer command sequence with MIFARE Picc.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phalMfc_IncrementTransfer(
                                     void * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                                     uint8_t bSrcBlockNo,   /**< [In] block number to be incremented. */
                                     uint8_t bDstBlockNo,   /**< [In] block number to be transferred to. */
                                     uint8_t * pValue       /**< [In] pValue[4] containing value (LSB first) to be incremented on the MIFARE(R) card */
                                     );

/**
* \brief Perform MIFARE(R) Decrement Transfer command sequence with MIFARE Picc.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phalMfc_DecrementTransfer(
                                     void * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                                     uint8_t bSrcBlockNo,   /**< [In] block number to be decremented. */
                                     uint8_t bDstBlockNo,   /**< [In] block number to be transferred to. */
                                     uint8_t * pValue       /**< [In] pValue[4] containing value (LSB first) to be decremented on the MIFARE(R) card */
                                     );
/**
* \brief Perform MIFARE(R) Restore Transfer command sequence with MIFARE Picc.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phalMfc_RestoreTransfer(
                                   void * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                                   uint8_t bSrcBlockNo, /**< [In] block number to be decremented. */
                                   uint8_t bDstBlockNo  /**< [In] block number to be transferred to. */
                                   );

/**
* \brief Perform MIFARE(R) Personalize UID usage command sequence with MIFARE Picc.
* UID type can be one of 
* \li #PHAL_MFC_UID_TYPE_UIDF0
* \li #PHAL_MFC_UID_TYPE_UIDF1
* \li #PHAL_MFC_UID_TYPE_UIDF2
* \li #PHAL_MFC_UID_TYPE_UIDF3
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phalMfc_PersonalizeUid(
                                  void * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
                                  uint8_t bUidType      /**< [In] UID type. */
                                  );
/** @} */
#endif /* NXPBUILD__PHAL_MFC */

#ifdef __cplusplus
} /* Extern C */
#endif

#endif /* PHALMFC_H */
