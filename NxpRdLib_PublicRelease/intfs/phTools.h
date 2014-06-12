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
* Generic Tools Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.5 $
* $Date: Fri Apr 15 09:27:19 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHTOOLS_H
#define PHTOOLS_H

#include <ph_Status.h>

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/** \defgroup phTools Tools
*
* \brief This component implements tools that are necessary for many different software modules
* @{
*/

/**
* \name ToolsConfigs
*/
/*@{*/
#define PH_TOOLS_CRC16_PRESET_ISO14443A 0x6363U     /**< CRC16 Preset for ISO14443-A. */
#define PH_TOOLS_CRC16_PRESET_ISO14443B 0xFFFFU     /**< CRC16 Preset for ISO14443-B. */
#define PH_TOOLS_CRC16_PRESET_FELICA    0x0000U     /**< CRC16 Preset for Felica. */
#define PH_TOOLS_CRC16_POLY_ISO14443    0x8408U     /**< CRC16 Polynom for ISO14443. */
#define PH_TOOLS_CRC32_PRESET_DF8       0xFFFFFFFFU /**< CRC32 Preset for DesFire. */
#define PH_TOOLS_CRC32_POLY_DF8         0xEDB88320U /**< CRC32 Polynom for DesFire. */
#define PH_TOOLS_CRC8_PRESET_EPC        0xFFU       /**< Preset value for EPC CRC-8 generation. */
#define PH_TOOLS_CRC8_PRESET_UID        0xFDU       /**< Preset value for UID CRC-8 generation. */
#define PH_TOOLS_CRC8_POLY_EPCUID       0x1DU       /**< Polynomial for EPC/UID CRC-8 generation: x^8 + x^4 + x^3 + x^2 + 1 (MSB first). */
#define PH_TOOLS_CRC16_PRESET_EPCUID    0xFFFFU     /**< Preset value for EPC/UID CRC-16 generation. */
#define PH_TOOLS_CRC16_POLY_EPCUID      0x1021U     /**< Polynomial for EPC/UID CRC-16 generation: x^16 + x^12 + x^5 + 1 (MSB first). */
#define PH_TOOLS_CRC5_PRESET_I18000P3   0x09U       /**< Preset value for ISO18000-3 CRC-5 generation. */
#define PH_TOOLS_CRC5_POLY_I18000P3     0x09U       /**< Polynomial for ISO18000-3 CRC-5 generation: x^5 + x^3 + 1 (LSB first). */
#define PH_TOOLS_CRC16_PRESET_I18000P3  0xFFFFU     /**< Preset value for ISO18000-3 CRC-16 generation. */
#define PH_TOOLS_CRC16_POLY_I18000P3    0x8408U     /**< Polynomial for ISO18000-3 CRC-16 generation: x^16 + x^12 + x^5 + 1 (LSB first). */
#define PH_TOOLS_CRC16_POLY_FELICA      0x1021U     /**< Polynomial for Felica CRC-16 generation: x^16 + x^12 + x^5 + 1 (MSB first). */
#define PH_TOOLS_PARITY_OPTION_EVEN         0x00U   /**< Encode/Decode even parity bits. */
#define PH_TOOLS_PARITY_OPTION_ODD          0x01U   /**< Encode/Decode odd parity bits. */

#define PH_TOOLS_CRC_OPTION_DEFAULT         0x00U   /**< Default CRC operation. */
#define PH_TOOLS_CRC_OPTION_OUPUT_INVERTED  0x01U   /**< Inverts the bits after calculation. */
#define PH_TOOLS_CRC_OPTION_MSB_FIRST       0x02U   /**< Calculates CRC with MSB(it) first. */
#define PH_TOOLS_CRC_OPTION_BITWISE         0x04U   /**< Bitwise CRC, \c wDataLength represents the Bitlength. */
#define PH_TOOLS_CRC_OPTION_MASK            0x07U   /**< Mask of valid option bits. */
/*@}*/

/**
* \brief Calculate even or odd parity.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phTools_EncodeParity(
                                uint8_t bOption,                /**< [In] Parity option; e.g. #PH_TOOLS_PARITY_OPTION_EVEN. */
                                uint8_t * pInBuffer,            /**< [In] Array to input data. */
                                uint16_t wInBufferLength,       /**< [In] Length of input data in bytes. */
                                uint8_t bInBufferBits,          /**< [In] Number of valid bits in last byte of pInBuffer. */
                                uint16_t wOutBufferSize,        /**< [In] Size of the output buffer. */
                                uint8_t * pOutBuffer,           /**< [Out] Output buffer. */
                                uint16_t * pOutBufferLength,    /**< [Out] Number of valid bytes in pOutBuffer. */
                                uint8_t * pOutBufferBits        /**< [Out] Number of valid bits in last byte of pOutBuffer. */
                                );

/**
* \brief Verify and Remove even or odd parity.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phTools_DecodeParity(
                                uint8_t bOption,                /**< [In] Parity option; e.g. #PH_TOOLS_PARITY_OPTION_EVEN. */
                                uint8_t * pInBuffer,            /**< [In] Array to input data. */
                                uint16_t wInBufferLength,       /**< [In] Length of input data in bytes. */
                                uint8_t bInBufferBits,          /**< [In] Number of valid bits in last byte of pInBuffer. */
                                uint16_t wOutBufferSize,        /**< [In] Size of the output buffer. */
                                uint8_t * pOutBuffer,           /**< [Out] Output buffer. */
                                uint16_t * pOutBufferLength,    /**< [Out] Number of valid bytes in pOutBuffer. */
                                uint8_t * pOutBufferBits        /**< [Out] Number of valid bits in last byte of pOutBuffer. */
                                );

/**
* \brief Calculate a CRC 5
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phTools_CalculateCrc5(
                                 uint8_t bOption,       /**< [In] Specifies whether the output should be inverted or not. */
                                 uint8_t bPreset,       /**< [In] Preset used for CRC calculation, e.g. #PH_TOOLS_CRC5_PRESET_I18000P3. */
                                 uint8_t bPolynom,      /**< [In] Polynom used for reduction, e.g. #PH_TOOLS_CRC5_POLY_I18000P3. */
                                 uint8_t * pData,       /**< [In] Array to input data. */
                                 uint16_t wDataLength,  /**< [In] Length of input data. */
                                 uint8_t * pCrc         /**< [Out] Resulting CRC. */
                                 );

/**
* \brief Calculate a CRC 8
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phTools_CalculateCrc8(
                                 uint8_t bOption,       /**< [In] Specifies whether the output should be inverted or not. */
                                 uint8_t bPreset,       /**< [In] Preset used for CRC calculation, e.g. #PH_TOOLS_CRC8_PRESET_UID. */
                                 uint8_t bPolynom,      /**< [In] Polynom used for reduction, e.g. #PH_TOOLS_CRC8_POLY_EPCUID. */
                                 uint8_t * pData,       /**< [In] Array to input data. */
                                 uint16_t wDataLength,  /**< [In] Length of input data. */
                                 uint8_t * pCrc         /**< [Out] Resulting CRC. */
                                 );

/**
* \brief Calculate a CRC 16
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phTools_CalculateCrc16(
                                  uint8_t bOption,      /**< [In] Specifies whether the output should be inverted or not. */
                                  uint16_t wPreset,     /**< [In] Preset used for CRC calculation, e.g. #PH_TOOLS_CRC16_PRESET_ISO14443A. */
                                  uint16_t wPolynom,    /**< [In] Polynom used for reduction, e.g. #PH_TOOLS_CRC16_POLY_ISO14443. */
                                  uint8_t * pData,      /**< [In] Array to input data. */
                                  uint16_t wDataLength, /**< [In] Length of input data. */
                                  uint16_t * pCrc       /**< [Out] Resulting CRC. */
                                  );

/**
* \brief Calculate a CRC 32
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phTools_CalculateCrc32(
                                  uint8_t bOption,      /**< [In] Specifies whether the output should be inverted or not. */
                                  uint32_t dwPreset,    /**< [In] Preset used for CRC calculation, e.g. #PH_TOOLS_CRC32_PRESET_DF8. */
                                  uint32_t dwPolynom,   /**< [In] Polynom used for reduction, e.g. #PH_TOOLS_CRC32_POLY_DF8. */
                                  uint8_t * pData,      /**< [In] Array to input data. */
                                  uint16_t wDataLength, /**< [In] Length of input data. */
                                  uint32_t * pCrc       /**< [Out] Resulting CRC. */
                                  );

/** @}
* end of phTools group
*/

#ifdef __cplusplus
}/*Extern C*/
#endif

#endif /* PHTOOLS_H */
