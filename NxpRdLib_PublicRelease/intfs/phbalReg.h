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
* Generic BAL Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.13 $
* $Date: Fri Apr 15 16:07:07 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHBALREG_H
#define PHBALREG_H

#include <ph_Status.h>

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#ifdef NXPBUILD__PHBAL_REG_SERIALWIN

/** \defgroup phbalReg_SerialWin Component : RS232 (Windows)
* \brief RS232 BAL (Windows)
*
* Serial-Line (COM-Port) interface for Windows.
* @{
*/

#define PHBAL_REG_SERIALWIN_ID          0x01U       /**< ID for Serial BAL component (Win32) */

/**
* \brief RS232 (Windows) BAL parameter structure
*/
typedef struct
{
    uint16_t wId;               /**< Layer ID for this BAL component, NEVER MODIFY! */
    int8_t * pComPortString;    /**< Com-Port string. */
    void * pComHandle;          /**< Handle to communication port. */
    uint32_t dwBitRate;         /**< Storage for bit rate setting. */
    uint16_t wTimeout;          /**< Storage for timeout setting. */
    uint16_t wEnumBufSize;      /**< Size of the enumeration buffer. Maximum possible size is 255 bytes. */
    uint8_t * pEnumBuffer;      /**< Pointer to the enumeration buffer for the GetPortList() function. */
    uint8_t bStopBits;          /**< Number of stopbits. */
} phbalReg_SerialWin_DataParams_t;

/**
* \name BAL Communication Configs
*/
/*@{*/
#define PHBAL_REG_SERIALWIN_CONFIG_BITRATE      (PH_CONFIG_CUSTOM_BEGIN)    /**< Configure communication speed. */
#define PHBAL_REG_SERIALWIN_CONFIG_STOPBITS     (PH_CONFIG_CUSTOM_BEGIN+1)  /**< Configure number of stop bits. */
/*@}*/

/**
* \name BAL Configuration Values
*/
/*@{*/
#define PHBAL_REG_SERIALWIN_VALUE_BITRATE_9600      0x0000U     /**< 9600 kBit/s. */
#define PHBAL_REG_SERIALWIN_VALUE_BITRATE_19200     0x0001U     /**< 19200 kBit/s. */
#define PHBAL_REG_SERIALWIN_VALUE_BITRATE_38400     0x0002U     /**< 38400 kBit/s. */
#define PHBAL_REG_SERIALWIN_VALUE_BITRATE_57600     0x0003U     /**< 57600 kBit/s. */
#define PHBAL_REG_SERIALWIN_VALUE_BITRATE_115200    0x0004U     /**< 115200 kBit/s. */
#define PHBAL_REG_SERIALWIN_VALUE_BITRATE_230400    0x0005U     /**< 230400 kBit/s. */
#define PHBAL_REG_SERIALWIN_VALUE_BITRATE_460800    0x0006U     /**< 460800 kBit/s. */

#define PHBAL_REG_SERIALWIN_VALUE_STOPBITS_ONE    0x0000U     /**< One stopbit. */
#define PHBAL_REG_SERIALWIN_VALUE_STOPBITS_ONE5   0x0001U     /**< One and a half stopbit. */
#define PHBAL_REG_SERIALWIN_VALUE_STOPBITS_TWO    0x0002U     /**< Two stopbit. */
/*@}*/

/**
* \brief Initialise the RS232 BAL component.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_INVALID_DATA_PARAMS Parameter structure size is invalid.
* \retval #PH_ERR_INVALID_PARAMETER \b wEnumBufSize is invalid.
*/
phStatus_t phbalReg_SerialWin_Init(
                                   phbalReg_SerialWin_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
                                   uint16_t wSizeOfDataParams,                      /**< [In] Specifies the size of the data parameter structure. */
                                   uint16_t wEnumBufSize,                           /**< [In] Size of the enumeration buffer. Maximum possible size is 255 bytes. */
                                   uint8_t * pEnumBuffer                            /**< [In] Pointer to the enumeration buffer for the GetPortList() function. */
                                   );

/** @} */
#endif /* NXPBUILD__PHBAL_REG_SERIALWIN */

#ifdef NXPBUILD__PHBAL_REG_RD70XUSBWIN

/** \defgroup phbalReg_Rd70xUsbWin Component : Rd70x USB (Windows)
* \brief Rd70x BAL (Windows)
* @{
*/

#define PHBAL_REG_RD70X_USBWIN_ID         0x05U       /**< ID for PEGODA USB component */

/**
* \brief Rd70x USB (Windows) BAL parameter structure
*/
typedef struct
{
    uint16_t wId;           /**< Layer ID for this BAL component, NEVER MODIFY! */
    uint8_t ucTxSeq;        /**< Sequence counter for packets. */
    uint8_t * pDeviceName;  /**< Name of currently open USB device. */
    void * pDeviceHandle;   /**< Handle to the USB device. */
    void * pPipeOut;        /**< Handle to Usb Out-pipe */
    void * pPipeIn;         /**< Handle to Usb In-pipe. */
    uint16_t wTimeoutWrMs;  /**< TO value for Usb Write pipe transfer. */
    uint16_t wTimeoutRdMs;  /**< TO value for Usb Read pipe transfer. */
} phbalReg_Rd70xUsbWin_DataParams_t;

/**
* \brief Initialise the PEGODA USB BAL component.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_INVALID_DATA_PARAMS Parameter structure size is invalid.
*/
phStatus_t phbalReg_Rd70xUsbWin_Init(
                                     phbalReg_Rd70xUsbWin_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
                                     uint16_t wSizeOfDataParams                         /**< [In] Specifies the size of the data parameter structure. */
                                     );

/** @} */
#endif /* NXPBUILD__PHBAL_REG_RD70XUSBWIN */

#ifdef NXPBUILD__PHBAL_REG_PCSCWIN

/** \defgroup phbalReg_PcscWin Component : PCSC (Windows)
* \brief PC/SC BAL Windows
*
* Smartcard Interface.
* @{
*/

#define PHBAL_REG_PCSCWIN_ID            0x06U       /**< ID for PCSC BAL component (Win32) */

/** \name Custom Option Bits
*
* Can be used for \ref phhalHw_Exchange.
*/
/*@{*/
/**
* \brief Calls \b SCardControl with given parameters.
*
* Make sure \b pTxBuffer contents are as follows:
\code
        pTxBuffer[0]               pTxBuffer[1]               pTxBuffer[2]               pTxBuffer[3]           [pTxBuffer[4-n]]
+--------------------------+--------------------------+--------------------------+--------------------------+----------------------+
| dwControlCode(bit 31-24) | dwControlCode(bit 23-16) |  dwControlCode(bit 15-8) |  dwControlCode(bit 7-0)  |       [Data]         |
+--------------------------+--------------------------+--------------------------+--------------------------+----------------------+
\endcode
*/
#define PHBAL_REG_PCSCWIN_OPTION_SCARDCONTROL   0x0010U
/*@}*/

/**
* \brief PCSC (Windows) BAL parameter structure
*/
typedef struct
{
    uint16_t wId;           /**< Layer ID for this BAL component, NEVER MODIFY! */
    uint8_t bProtocolType;  /**< Define protocol type of contact interface. */
    uint8_t bShare;         /**< Define share type of PCSC interface. */
    uint8_t * pAtrBuffer;   /**< Pointer to buffer used for storing the ATR after card activation. */
    uint16_t wAtrBufSize;   /**< Size of the ATR buffer. */
    void * hContext;        /**< Context for SmartCard class. */
    void * hCard;           /**< Handle of card. */ 
    uint8_t * pReaderName;  /**< Name of the reader. */
    uint16_t wTimeoutWrMs;  /**< TO value for Write transfer. */
    uint16_t wTimeoutRdMs;  /**< TO value for Read transfer. */
} phbalReg_PcscWin_DataParams_t;

/**
* \name BAL Communication Configs
*/
/*@{*/
#define PHBAL_REG_PCSCWIN_CONFIG_PROTOCOL   (PH_CONFIG_CUSTOM_BEGIN)    /**< Used Protocol; e.g. #PHBAL_REG_PCSCWIN_VALUE_PROTOCOL_T0. */
#define PHBAL_REG_PCSCWIN_CONFIG_SHARE      (PH_CONFIG_CUSTOM_BEGIN+1)  /**< Used Access mode; e.g. #PHBAL_REG_PCSCWIN_VALUE_SHARE_SHARED. */
/*@}*/

/**
* \name BAL Communication Configuration values
*/
/*@{*/
#define PHBAL_REG_PCSCWIN_VALUE_PROTOCOL_T0         0x0000U /**< T=0 protocol. */
#define PHBAL_REG_PCSCWIN_VALUE_PROTOCOL_T1         0x0001U /**< T=1 protocol. */
#define PHBAL_REG_PCSCWIN_VALUE_PROTOCOL_UNDEFINED  0x0002U /**< UNDEFINED protocol. */
#define PHBAL_REG_PCSCWIN_VALUE_SHARE_SHARED        0x0000U /**< SHARED access. */
#define PHBAL_REG_PCSCWIN_VALUE_SHARE_EXCLUSIVE     0x0001U /**< EXCLUSIVE access. */
#define PHBAL_REG_PCSCWIN_VALUE_SHARE_DIRECT        0x0002U /**< DIRECT access. */
/*@}*/

/**
* \brief Initialise the PCSC BAL component.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_INVALID_DATA_PARAMS Parameter structure size is invalid.
* \retval #PH_ERR_INVALID_PARAMETER \b wAtrBufSize is invalid.
*/
phStatus_t phbalReg_PcscWin_Init(
                                 phbalReg_PcscWin_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
                                 uint16_t wSizeOfDataParams,                    /**< [In] Specifies the size of the data parameter structure. */
                                 uint8_t * pAtrBuffer,                          /**< [In] Pointer to buffer used for storing the ATR after card activation. */
                                 uint16_t wAtrBufSize                           /**< [In] Size of the ATR buffer. */
                                 );

/** @} */
#endif /* NXPBUILD__PHBAL_REG_PCSCWIN */

#ifdef NXPBUILD__PHBAL_REG_STUB

/** \defgroup phbalReg_Stub Component : Stub
* \brief Component without functionality to ease implementation of additional busses.
* @{
*/

#define PHBAL_REG_STUB_ID               0x08U       /**< ID for Stub BAL component */

/**
* \brief BAL Stub parameter structure
*/
typedef struct
{
    uint16_t       wId;         /**< Layer ID for this BAL component, NEVER MODIFY! */
    /* TODO: Place private parameters which are needed across different functions here. */
} phbalReg_Stub_DataParams_t;

/**
* \brief Initialise the BAL Stub layer.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_INVALID_DATA_PARAMS Parameter structure size is invalid.
*/
phStatus_t phbalReg_Stub_Init(
                              phbalReg_Stub_DataParams_t * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
                              uint16_t wSizeOfDataParams                /**< [In] Specifies the size of the data parameter structure. */
                              );

/** @} */
#endif /* NXPBUILD__PHBAL_REG_SERIALWIN */

#ifdef NXPBUILD__PHBAL_REG_R_PI_SPI

/** \defgroup phbalReg_Stub Component : Stub
* \brief Component without functionality to ease implementation of additional busses.
* @{
*/

#define PHBAL_REG_R_PI_SPI_ID               0x09U       /**< ID for Stub BAL component */

/**
* \brief BAL Stub parameter structure
*/
typedef struct
{
    uint16_t       wId;         /**< Layer ID for this BAL component, NEVER MODIFY! */
    uint32_t		spiFD;		/* SPI device file descriptor */
    uint8_t     	spiMode;
    uint8_t     	spiBPW;
    uint16_t		spiDelay;
    uint32_t		spiSpeed;
} phbalReg_R_Pi_spi_DataParams_t;

/**
* \brief Initialise the BAL Stub layer.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_INVALID_DATA_PARAMS Parameter structure size is invalid.
*/
phStatus_t phbalReg_R_Pi_spi_Init(
                              phbalReg_R_Pi_spi_DataParams_t * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
                              uint16_t wSizeOfDataParams                /**< [In] Specifies the size of the data parameter structure. */
                              );

/** @} */
#endif /* NXPBUILD__PHBAL_REG_R_PI_SPI */

#ifdef NXPBUILD__PHBAL_REG

/** \defgroup phbalReg Bus Abstraction Layer
* \brief These Components implement the interfaces between physical Host-Device and physical Reader-Device.
* @{
*/

/**
* \name Generic BAL Configs
*/
/*@{*/
#define PHBAL_REG_CONFIG_WRITE_TIMEOUT_MS   0x0000U /**< Configure transmission timeout. */
#define PHBAL_REG_CONFIG_READ_TIMEOUT_MS    0x0001U /**< Configure reception timeout. */
/*@}*/

/**
* \brief List all available ports.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_BUFFER_OVERFLOW Given enumeration buffer is too small.
* \retval #PH_ERR_INTERFACE_ERROR Error while enumerating devices.
*/
phStatus_t phbalReg_GetPortList(
                                void * pDataParams,     /**< [In] Pointer to this layer's parameter structure. */
                                uint16_t wPortBufSize,  /**< [In] Buffer Size of Port Name String. */ 
                                uint8_t * pPortNames,   /**< [Out] Port Name as Multi-String. */
                                uint16_t * pNumOfPorts  /**< [Out] Number of found port strings. */ 
                                );

/**
* \brief Select Port to be used.
*
* <em>Example SerialWin:</em> The caller has to ensure that \c pPortName
* is valid throughout the whole lifetime of \c pDataParams.\n
* Furthermore, the caller is responsible for prepending "\\.\" if COM ports above
* COM9 need to be accessed.\n\n
* \b Example:
\code
strcpy(pPortName, "COM9");         <-- correct
strcpy(pPortName, "\\\\.\\COM9");  <-- correct
strcpy(pPortName, "\\\\.\\COM10"); <-- correct
strcpy(pPortName, "COM10");        <-- wrong
\endcode
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phbalReg_SetPort(
                            void * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
                            uint8_t * pPortName /**< [In] Port Name as String. */
                            );

/**
* \brief Open communication port.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_USE_CONDITION Communication port is already open.
* \retval #PH_ERR_INTERFACE_ERROR Error while opening port.
*/
phStatus_t phbalReg_OpenPort(
                             void * pDataParams /**< [In] Pointer to this layer's parameter structure. */
                             );

/**
* \brief Close communication port.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_USE_CONDITION Communication port is not open.
* \retval #PH_ERR_INTERFACE_ERROR Error while closing port.
*/
phStatus_t phbalReg_ClosePort(
                              void * pDataParams    /**< [In] Pointer to this layer's parameter structure. */
                              );

/**
* \brief Perform Data Exchange on the bus.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_INVALID_PARAMETER \b wOption is invalid.
* \retval #PH_ERR_IO_TIMEOUT No response received within given time frame.
* \retval #PH_ERR_BUFFER_OVERFLOW Response is too big for either given receive buffer or internal buffer.
* \retval #PH_ERR_INTERFACE_ERROR Communication error.
*/
phStatus_t phbalReg_Exchange(
                             void * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                             uint16_t wOption,      /**< [In] Option parameter. */
                             uint8_t * pTxBuffer,   /**< [In] Data to transmit. */
                             uint16_t wTxLength,    /**< [In] Number of bytes to transmit. */
                             uint16_t wRxBufSize,   /**< [In] Size of receive buffer / Number of bytes to receive (depending on implementation). */
                             uint8_t * pRxBuffer,   /**< [Out] Received data. */
                             uint16_t * pRxLength   /**< [Out] Number of received data bytes. */
                             );

/**
* \brief Set configuration parameter.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_UNSUPPORTED_PARAMETER Configuration is not supported or invalid.
* \retval #PH_ERR_INVALID_PARAMETER Parameter value is invalid.
* \retval #PH_ERR_INTERFACE_ERROR Communication error.
*/
phStatus_t phbalReg_SetConfig(
                              void * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
                              uint16_t wConfig,     /**< [In] Configuration Identifier. */
                              uint16_t wValue       /**< [In] Configuration Value. */
                              );
/**
* \brief Get configuration parameter.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_UNSUPPORTED_PARAMETER Configuration is not supported or invalid.
* \retval #PH_ERR_INTERFACE_ERROR Communication error.
*/
phStatus_t phbalReg_GetConfig(
                              void * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
                              uint16_t wConfig,     /**< [In] Configuration Identifier. */
                              uint16_t * pValue     /**< [Out] Configuration Value. */
                              );

/** @} */
#endif /* NXPBUILD__PHBAL_REG */

#ifdef __cplusplus
} /* Extern C */
#endif

#endif /* PHBALREG_H */
