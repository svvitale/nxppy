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
* Status Code definitions for Reader Library Framework.
* $Author: jayaprakash.desai $
* $Revision: 1.4 $
* $Date: Tue Jun 28 07:55:25 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PH_STATUS_H
#define PH_STATUS_H

#ifndef NXPBUILD_DELETE
#include <ph_NxpBuild.h>
#endif /* NXPBUILD_DELETE */

#include <ph_TypeDefs.h>

#ifdef _WIN32
#pragma warning(push)           /* PRQA S 3116 */
#pragma warning(disable:4001)   /* PRQA S 3116 */
#include <string.h>
#pragma warning(pop)            /* PRQA S 3116 */
#else
#include <string.h>
#endif

#ifdef NXPBUILD__PH_LOG
#include <phLog.h>
#endif

/** \defgroup ph_Error Error Code Collection
* \brief Common Error Codes
* @{
*/

/** \name Success Codes
*/
/*@{*/
#define PH_ERR_SUCCESS                  0x0000U /**< Returned in case of no error. */
#define PH_ERR_SUCCESS_CHAINING         0x0071U /**< Rx chaining is not complete, further action needed. */
#define PH_ERR_SUCCESS_INCOMPLETE_BYTE  0x0072U /**< An incomplete byte was received. */
/*@}*/

/** \name Communication Errors
*/
/*@{*/
#define PH_ERR_IO_TIMEOUT               0x0001U /**< No reply received, e.g. PICC removal. */
#define PH_ERR_INTEGRITY_ERROR          0x0002U /**< Wrong CRC or parity detected. */
#define PH_ERR_COLLISION_ERROR          0x0003U /**< A collision occured. */
#define PH_ERR_BUFFER_OVERFLOW          0x0004U /**< Attempt to write beyond buffer size. */
#define PH_ERR_FRAMING_ERROR            0x0005U /**< Invalid frame format. */
#define PH_ERR_PROTOCOL_ERROR           0x0006U /**< Received response violates protocol. */
#define PH_ERR_AUTH_ERROR               0x0007U /**< Authentication error. */
#define PH_ERR_READ_WRITE_ERROR         0x0008U /**< A Read or Write error occured in RAM/ROM or Flash. */
#define PH_ERR_TEMPERATURE_ERROR        0x0009U /**< The RC sensors signal overheating. */
#define PH_ERR_RF_ERROR                 0x000AU /**< Error on RF-Interface. */
#define PH_ERR_INTERFACE_ERROR          0x000BU /**< An error occured in RC communication. */
#define PH_ERR_LENGTH_ERROR             0x000CU /**< A length error occured. */
#define PH_ERR_INTERNAL_ERROR           0x007FU /**< An internal error occured. */
/*@}*/

/** \name Parameter & Command Errors
*/
/*@{*/
#define PH_ERR_INVALID_DATA_PARAMS      0x0020U /**< Invalid data parameters supplied (layer id check failed). */
#define PH_ERR_INVALID_PARAMETER        0x0021U /**< Invalid parameter supplied. */
#define PH_ERR_PARAMETER_OVERFLOW       0x0022U /**< Reading/Writing a parameter would produce an overflow. */
#define PH_ERR_UNSUPPORTED_PARAMETER    0x0023U /**< Parameter not supported. */
#define PH_ERR_UNSUPPORTED_COMMAND      0x0024U /**< Command not supported. */
#define PH_ERR_USE_CONDITION            0x0025U /**< Condition of use not satisfied. */
#define PH_ERR_KEY                      0x0026U /**< A key error occured. */
/*@}*/

/** @} */

/** \defgroup ph_Status Generic Definitions
* \brief Contains definitions which are generic throughout the library
* @{
*/

/**
* \name Boolean Values
*/
/*@{*/
#define PH_ON                           0x0001U /**< Enabled. */
#define PH_OFF                          0x0000U /**< Disabled. */
#define PH_SUPPORTED                    0x0001U /**< Supported. */
#define PH_UNSUPPORTED                  0x0000U /**< Not Supported. */
/*@}*/

/**
* \name Configuration
*/
/*@{*/
#define PH_CONFIG_CUSTOM_BEGIN          0xE000U /**< Starting number of custom configs. */
/*@}*/

/**
* \name Component identifiers
*/
/*@{*/
#define PH_COMP_MASK                    0xFF00U /**< Component Mask for status code and component ID. */
#define PH_COMPID_MASK                  0x00FFU /**< ID Mask for component ID. */
#define PH_ERR_MASK                     0x00FFU /**< Error Mask for status code. */
#define PH_ERR_CUSTOM_BEGIN             0x0080U /**< Starting number of custom error codes. */
#define PH_COMP_GENERIC                 0x0000U /**< Generic Component Code. */
#define PH_COMP_BAL                     0x0100U /**< BAL Component Code. */
#define PH_COMP_HAL                     0x0200U /**< HAL Component Code. */
#define PH_COMP_PAL_ISO14443P3A         0x0300U /**< ISO14443-3A PAL-Component Code. */
#define PH_COMP_PAL_ISO14443P3B         0x0400U /**< ISO14443-3B PAL-Component Code. */
#define PH_COMP_PAL_ISO14443P4A         0x0500U /**< ISO14443-4A PAL-Component Code. */
#define PH_COMP_PAL_ISO14443P4          0x0600U /**< ISO14443-4 PAL-Component Code. */
#define PH_COMP_PAL_MIFARE              0x0700U /**< MIFARE(R) PAL-Component Code. */
#define PH_COMP_PAL_FELICA              0x0800U /**< Open FeliCa PAL-Component Code. */
#define PH_COMP_PAL_EPCUID              0x0900U /**< ICode EPC/UID PAL-Component Code. */
#define PH_COMP_PAL_SLI15693            0x0A00U /**< ICode SLI/ISO15693 PAL-Component Code. */
#define PH_COMP_PAL_I18000P3M3          0x0B00U /**< ISO18000-3 Mode3 PAL-Component Code. */
#define PH_COMP_PAL_I18092MPI           0x0C00U /**< ISO18092 passive initiator mode PAL-Component Code. */
#define PH_COMP_AL_MFC                  0x1000U /**< MIFARE(R) Classic AL-Component Code. */
#define PH_COMP_AL_MFUL                 0x1100U /**< MIFARE(R) Ultralight AL-Component Code. */
#define PH_COMP_AL_MFP                  0x1200U /**< MIFARE(R) Plus AL-Component Code. */
#define PH_COMP_AL_VCA                  0x1300U /**< Virtual Card Architecture AL-Component Code. */
#define PH_COMP_AL_FELICA               0x1400U /**< Open FeliCa AL-Component Code. */
#define PH_COMP_AL_I15693               0x1500U /**< ISO15693 AL-Component Code. */
#define PH_COMP_AL_SLI                  0x1600U /**< ICode SLI AL-Component Code. */
#define PH_COMP_AL_I18000P3M3           0x1800U /**< ISO18000-3 Mode3 AL-Component Code. */
#define PH_COMP_AL_MFDF                 0x1900U /**< MIFARE DESFIRE EV1 AL Component Code. */
#define PH_COMP_AL_P40CMDPRIV           0x1A00U /**< P40 command libraryAL-Component Code. */
#define PH_COMP_AL_P40CMDPUB			0x1B00U /**< P40 command libraryAL-Component Code. */
#define PH_COMP_DL_AMP					0x3000U /**< Amplifier DL-Component Code. */
#define PH_COMP_DL_THSTRM				0x3100U /**< Thermostream DL-Component Code. */
#define PH_COMP_DL_OSCI					0x3200U /**< Oscilloscope DL-Component Code. */
#define PH_COMP_DL_RDFPGA				0x3300U	/**< Reader FPGA Box DL-Component Code. */
#define PH_COMP_DL_MSTAMPOSC			0x3400U /**< Master Amplifier Oscilloscope DL-Component Code. */
#define PH_COMP_DL_STEPPER				0x3500U /**< Stepper DL-Component Code. */
#define PH_COMP_CIDMANAGER              0xE000U /**< Cid Manager Component Code. */
#define PH_COMP_CRYPTOSYM               0xE100U /**< CryptoSym Component Code. */
#define PH_COMP_KEYSTORE                0xE200U /**< KeyStore Component Code. */
#define PH_COMP_TOOLS                   0xE300U /**< Tools Component Code. */
#define PH_COMP_CRYPTORNG               0xE400U /**< CryptoRng Component Code. */
#define PH_COMP_LOG                     0xEF00U /**< Log Component Code. */
/*@}*/

/** 
* Macro for error handling of underlaying layer and exit.
*/
#define PH_CHECK_SUCCESS(status)         {if ((status) != PH_ERR_SUCCESS) {return (status);}}
#define PH_CHECK_SUCCESS_FCT(status,fct) {(status) = (fct); PH_CHECK_SUCCESS(status);}

/**
*  Macro for component-error-code adding of current layer.
*/
#define PH_ADD_COMPCODE(stat, code)     ((phStatus_t)(((stat) == PH_ERR_SUCCESS) || ((stat) & PH_COMP_MASK) ? (stat) : (((stat) & PH_ERR_MASK) | ((code) & PH_COMP_MASK))))

/**
*  Macro to get the component code or id using a pointer to a memory.
*/
#define PH_GET_COMPCODE(pId)            ( (*((uint16_t*)(pId))) & PH_COMP_MASK )
#define PH_GET_COMPID(pId)              ( (uint8_t)(*((uint16_t*)(pId))) )

/** \name Exchange Options
*/
/*@{*/
/**
Default exchange mode.
Combine with #PH_EXCHANGE_BUFFERED_BIT and
#PH_EXCHANGE_LEAVE_BUFFER_BIT to perform buffering.
\c ISO14443-4 specific:
Performs Tx/Rx chaining with the card.
Returns #PH_ERR_SUCCESS_CHAINING when RxBuffer is full and
does not ACK the last received block.
*/
#define PH_EXCHANGE_DEFAULT             0x0000U

/**
\c ISO14443-4 specific:
Chains given data to card.
Combine with #PH_EXCHANGE_BUFFERED_BIT and
#PH_EXCHANGE_LEAVE_BUFFER_BIT to perform buffering.
Does not receive any data.
*/
#define PH_EXCHANGE_TXCHAINING          0x0001U

/**
\c ISO14443-4 specific:
Starts transmission with and R(ACK) block and
performs Rx chaining with the card.
Returns #PH_ERR_SUCCESS_CHAINING when RxBuffer is full and
does not ACK the last received block.
*/
#define PH_EXCHANGE_RXCHAINING          0x0002U

/**
\c ISO14443-4 specific:
Starts transmission with and R(ACK) block and
performs Rx chaining with the card.
Completes Rx chaining with the card if RxBuffer is full.
*/
#define PH_EXCHANGE_RXCHAINING_BUFSIZE  0x0003U

/** Mask for the above modes. All other bits are reserved. */
#define PH_EXCHANGE_MODE_MASK           0x000FU

/** Mask for custom exchange bits. These 4 bits can be used for custom exchange behaviour. */
#define PH_EXCHANGE_CUSTOM_BITS_MASK    0x00F0U

/**
Does not clear the internal buffer before operation.
If this bit is set and data is transmitted,
the contents of the internal buffer are sent first.
*/
#define PH_EXCHANGE_LEAVE_BUFFER_BIT    0x4000U

/**
Buffers Tx-Data into internal buffer
instead of transmitting it.
*/
#define PH_EXCHANGE_BUFFERED_BIT        0x8000U

/**
The given data is the first part of a stream.
(Helper definition for buffering).
*/
#define PH_EXCHANGE_BUFFER_FIRST   (PH_EXCHANGE_DEFAULT | PH_EXCHANGE_BUFFERED_BIT)

/**
The given data is a subsequent part of a stream.
(Helper definition for buffering).
*/
#define PH_EXCHANGE_BUFFER_CONT    (PH_EXCHANGE_DEFAULT | PH_EXCHANGE_BUFFERED_BIT | PH_EXCHANGE_LEAVE_BUFFER_BIT)

/**
The given data is the last part of a stream.
(Helper definition for buffering).
*/
#define PH_EXCHANGE_BUFFER_LAST    (PH_EXCHANGE_DEFAULT | PH_EXCHANGE_LEAVE_BUFFER_BIT)
/*@}*/

/** \name Log Interface
*/
/*@{*/
#ifdef NXPBUILD__PH_LOG

#define PH_LOG_HELPER_ALLOCATE_PARAMNAME(pParam) PH_LOG_ALLOCATE_PARAMNAME(pParam)
#define PH_LOG_HELPER_ALLOCATE_TEXT(pIdent, pText) PH_LOG_ALLOCATE_TEXT(pIdent, pText)
#define PH_LOG_HELPER_ADDSTRING(bLogType,pString) phLog_AddString(pDataParams, (bLogType), (pString))
#define PH_LOG_HELPER_ADDPARAM_UINT8(bLogType,pName,pParam) phLog_AddParam_Uint8(pDataParams, (bLogType), (pName), (pParam))
#define PH_LOG_HELPER_ADDPARAM_UINT16(bLogType,pName,pParam) phLog_AddParam_Uint16(pDataParams, (bLogType), (pName), (pParam))
#define PH_LOG_HELPER_ADDPARAM_UINT32(bLogType,pName,pParam) phLog_AddParam_Uint32(pDataParams, (bLogType), (pName), (pParam))
#define PH_LOG_HELPER_ADDPARAM_BUFFER(bLogType,pName,pParam,wLength) phLog_AddParam_Buffer(pDataParams, (bLogType),(pName),(pParam),(wLength))
#define PH_LOG_HELPER_EXECUTE(bOption) phLog_Execute(pDataParams, (bOption))

#else

#define PH_LOG_HELPER_ALLOCATE_PARAMNAME(pParam)
#define PH_LOG_HELPER_ALLOCATE_TEXT(pIdent, pText)
#define PH_LOG_HELPER_ADDSTRING(bLogType,pString)
#define PH_LOG_HELPER_ADDPARAM_UINT8(bLogType,pName,pParam)
#define PH_LOG_HELPER_ADDPARAM_UINT16(bLogType,pName,pParam)
#define PH_LOG_HELPER_ADDPARAM_UINT32(bLogType,pName,pParam)
#define PH_LOG_HELPER_ADDPARAM_BUFFER(bLogType,pName,pParam,wLength)
#define PH_LOG_HELPER_EXECUTE(bOption)

#endif
/*@}*/

/** @}
* end of ph_Status group
*/

/** \name Debug Definitions
*/
/*@{*/
#ifdef NXPBUILD__PH_DEBUG
#define PH_ASSERT_NULL(a) while((a) == NULL);
#else
#define PH_ASSERT_NULL(a)
#endif
/*@}*/

#endif /* PH_STATUS_H */
