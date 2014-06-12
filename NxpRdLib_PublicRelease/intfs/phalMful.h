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
* Generic MIFARE(R) Ultralight Application Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:27:18 2011 $
*
* History:
*  CHu: Generated 05. October 2009
*
*/

#ifndef PHALMFUL_H
#define PHALMFUL_H

#include <ph_Status.h>
#include <phpalMifare.h>
#include <phhalHw.h>

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#ifdef NXPBUILD__PHAL_MFUL_SW

/** \defgroup phalMful_Sw Component : Software
* @{
*/

#define PHAL_MFUL_SW_ID         0x01    /**< ID for Software MIFARE Ultralight layer */

/**
* \brief Private parameter structure
*/
typedef struct
{
    uint16_t wId;                   /**< Layer ID for this component, NEVER MODIFY! */
    void * pPalMifareDataParams;    /**< Pointer to palMifare parameter structure. */
    void * pKeyStoreDataParams;     /**< Pointer to phKeystore parameter structure. */
    void * pCryptoDataParams;       /**< Pointer to phCrypto data parameters structure. */
    void * pCryptoRngDataParams;    /**< Pointer to the parameter structure of the CryptoRng layer. */
} phalMful_Sw_DataParams_t;

/**
* \brief Initialise this layer.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phalMful_Sw_Init(
                            phalMful_Sw_DataParams_t * pDataParams,     /**< [In] Pointer to this layer's parameter structure. */
                            uint16_t wSizeOfDataParams,                 /**< [In] Specifies the size of the data parameter structure. */
                            void * pPalMifareDataParams,                /**< [In] Pointer to palMifare parameter structure. */
                            void * pKeyStoreDataParams,                 /**< [In] Pointer to phKeystore parameter structure. */
                            void * pCryptoDataParams,                   /**< [In] Pointer to phCrypto data parameters structure. */
                            void * pCryptoRngDataParams                 /**< [In] Pointer to the parameter structure of the CryptoRng layer. */
                            );

/** @} */
#endif /* NXPBUILD__PHAL_MFUL_SW */

#ifdef NXPBUILD__PHAL_MFUL

/** \defgroup phalMful MIFARE(R) Ultralight
* \brief These Components implement the MIFARE(R) Ultralight commands.
* @{
*/

/**
* \name Block definitions
*/
/*@{*/
#define PHAL_MFUL_READ_BLOCK_LENGTH         16U     /**< Length of a read MIFARE(R) Ultralight data block. */
#define PHAL_MFUL_WRITE_BLOCK_LENGTH        4U      /**< Length of a write MIFARE(R) Ultralight data block. */
#define PHAL_MFUL_COMPWRITE_BLOCK_LENGTH    16U     /**< Length of a compatibility write MIFARE(R) Ultralight data block. */
/*@}*/

/**
* \name Crypto definitions
*/
/*@{*/
#define PHAL_MFUL_DES_BLOCK_SIZE    8U      /**< Length of an MIFARE(R) Ultralight DES block. */
#define PHAL_MFUL_DES_KEY_LENGTH    16U     /**< Length of an MIFARE(R) Ultralight DES key. */
/*@}*/

/**
* \brief Perform MIFARE(R) Ultralight-C Authenticate command with Picc.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_AUTH_ERROR Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phalMful_UlcAuthenticate(
                                    void * pDataParams,     /**< [In] Pointer to this layer's parameter structure. */
                                    uint16_t wKeyNumber,    /**< [In] Key number to be used in authentication. */
                                    uint16_t wKeyVersion    /**< [In] Key version to be used in authentication. */
                                    );

/**
* \brief Perform MIFARE(R) Ultralight Read command with Picc.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phalMful_Read(
                         void * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                         uint8_t bAddress,      /**< [In] Address on Picc to read from. */
                         uint8_t * pData        /**< [Out] pData[#PHAL_MFUL_READ_BLOCK_LENGTH] containing data returned from the Picc. */
                         );

/**
* \brief Perform MIFARE(R) Ultralight Write command with Picc.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phalMful_Write(
                          void * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
                          uint8_t bAddress,     /**< [In] Address on Picc to write to. */
                          uint8_t * pData       /**< [In] pData[#PHAL_MFUL_WRITE_BLOCK_LENGTH] containing block to be written to the Picc. */
                          );

/**
* \brief Perform MIFARE(R) Ultralight Compatibility-Write command with Picc.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phalMful_CompatibilityWrite(
                                       void * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                                       uint8_t bAddress,    /**< [In] Address on Picc to write to. */
                                       uint8_t * pData      /**< [In] pData[#PHAL_MFUL_COMPWRITE_BLOCK_LENGTH] containing block to be written to the Picc. */
                                       );

/** @} */
#endif /* NXPBUILD__PHAL_MFUL */

#ifdef __cplusplus
} /* Extern C */
#endif

#endif /* PHALMFUL_H */
