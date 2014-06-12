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
* Generic HAL Component of Reader Library Framework.
* $Author: jayaprakash.desai $
* $Revision: 1.14 $
* $Date: Wed May 25 14:06:20 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHHALHW_H
#define PHHALHW_H

#include <ph_Status.h>
#include <phbalReg.h>

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#ifdef NXPBUILD__PHHAL_HW_RC663

	/** \defgroup phhalHw_Rc663 Component : Rc663
	* \brief RC663 Reader HAL
	*
	* \b Note: This HAL takes care about the "Request Guard Time".
	* \see phpalI14443p3a_RequestA
	* \see phpalI14443p3a_WakeUpA
	* @{
	*/

#define PHHAL_HW_RC663_ID               0x01    /**< ID for Rc663 HAL component. */

#define PHHAL_HW_RC663_DEFAULT_TIMEOUT  150U    /**< Default timeout in microseconds. */
#define PHHAL_HW_RC663_SHADOW_COUNT     0x0010U /**< Number of shadowed configurations. */

	/**
	* \name Custom Configs
	*/
	/*@{*/
	/** Configure FIFO-Size. */
#define PHHAL_HW_RC663_CONFIG_FIFOSIZE      (PH_CONFIG_CUSTOM_BEGIN)
	/**
	* \brief Enable (#PH_ON) or disable (#PH_OFF) LoadReg Mode.
	*
	* If this mode is enabled (it's disabled by default) then LoadReg is used\n
	* if an operation mode changes instead of applying library constants.\n
	* This is useful if custom antenna configuration values are required to be applied.\n
	* The parameters for LoadReg are taken from \b pLoadRegConfig which is an input parameter\n
	* of \ref phhalHw_Rc663_Init. Refer there for a detailed description of \b pLoadRegConfig.
	*/
#define PHHAL_HW_RC663_CONFIG_LOADREG_MODE  (PH_CONFIG_CUSTOM_BEGIN+1)
	/*@}*/

	/**
	* \name Fifo Configuration Values
	*/
	/*@{*/
#define PHHAL_HW_RC663_VALUE_FIFOSIZE_255   0x0000U /**< Configure FIFO-Size to 256 bytes */
#define PHHAL_HW_RC663_VALUE_FIFOSIZE_512   0x0001U /**< Configure FIFO-Size to 512 bytes */
	/*@}*/

	/** \name Custom Option Bits
	*
	* Can be used for \ref phhalHw_Exchange, \ref phhalHw_Rc663_Cmd_Receive and \ref phhalHw_Rc663_Cmd_Transmit.
	*/
	/*@{*/

	/**
	Do not start timer after transmission / before reception; (only for \ref phhalHw_Rc663_Cmd_Receive and \ref phhalHw_Rc663_Cmd_Transmit).
	*/
#define PHHAL_HW_RC663_OPTION_RXTX_TIMER_NOSTART        0x0000U

	/**
	Start timer after transmission / before reception, reset timer counter value; (only for \ref phhalHw_Rc663_Cmd_Receive and \ref phhalHw_Rc663_Cmd_Transmit).
	*/
#define PHHAL_HW_RC663_OPTION_RXTX_TIMER_START          0x0010U

	/*@}*/

	/**
	* \brief Rc663 HAL parameter structure
	*/
	typedef struct
	{
		uint16_t wId;                                       /**< Layer ID for this component, NEVER MODIFY! */
		void  * pBalDataParams;                             /**< Pointer to the lower layers parameter structure. */
		uint8_t bLoadRegMode;                               /**< Whether LoadReg-Mode is enabled or not. */
		uint8_t * pLoadRegConfig;                           /**< Pointer to configuration buffer for LoadReg mode; Refer to \ref phhalHw_Rc663_Init. */
		uint8_t * pTxBuffer;                                /**< Pointer to global transmit buffer used by the Exchange() function. */
		uint16_t wTxBufSize;                                /**< Size of the global transmit buffer. */
		uint16_t wTxBufLen;                                 /**< Number of valid bytes within the transmit buffer. */
		uint8_t * pRxBuffer;                                /**< Pointer to global receive buffer used by the Exchange() function. */
		uint16_t wRxBufSize;                                /**< Size of the global receive buffer. */
		uint16_t wRxBufLen;                                 /**< Number of valid bytes within the receive buffer. */
		uint16_t wRxBufStartPos;                            /**< Starting position within the global receive buffer. */
		uint16_t wMaxPrecachedBytes;                        /**< Holds the max. number of bytes which are precached prior to command execution. */
		uint8_t bCardType;                                  /**< Type of card for which the hal is configured for. */
		uint16_t wCfgShadow[PHHAL_HW_RC663_SHADOW_COUNT];   /**< Configuration shadow; Stores configuration for current cardtype. */
		uint16_t wTimingMode;                               /**< Current timing measurement mode. */
		uint8_t bTimeoutUnit;                               /**< Unit of current timeout value (either #PHHAL_HW_TIME_MICROSECONDS or #PHHAL_HW_TIME_MILLISECONDS). */
		uint32_t dwTimingUs;                                /**< Current timing value. */
		uint16_t wFieldOffTime;                             /**< Field-Off-Time in milliseconds. */
		uint16_t wFieldRecoveryTime;                        /**< Field-Recovery-Time in milliseconds. */
		uint8_t bSymbolStart;                               /**< Preamble of a frame. */
		uint8_t bSymbolEnd;                                 /**< Trailer symbol of a frame. */
		uint8_t bFifoSize;                                  /**< Fifo-Size setting. */
		uint16_t wAdditionalInfo;                           /**< Storage for additional error information. */
		uint8_t bBalConnectionType;                         /**< Type of the underlying BAL connection. Refer to #PHHAL_HW_CONFIG_BAL_CONNECTION. */
		uint8_t bRfResetAfterTo;                            /**< Storage for #PHHAL_HW_CONFIG_RFRESET_ON_TIMEOUT setting. */
	} phhalHw_Rc663_DataParams_t;

	/**
	* \brief Initialise the HAL component.
	*
	* A note on <b>pLoadRegConfig</b>:\n
	* This is used if #PHHAL_HW_RC663_CONFIG_LOADREG_MODE is enabled.\n
	* It is defined as follows:
	\code
	[MSB]                                              [LSB]
	31...............16..................8.................0
	+------------------+------------------+----------------+
	| wEEAddress (16b) | bRegAddress (8b) | bNumBytes (8b) |
	+------------------+------------------+----------------+
	\endcode
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
	phStatus_t phhalHw_Rc663_Init(
		phhalHw_Rc663_DataParams_t * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
		uint16_t wSizeOfDataParams,               /**< [In] Specifies the size of the data parameter structure. */
		void * pBalDataParams,                    /**< [In] Pointer to the lower layers parameter structure. */
		uint8_t * pLoadRegConfig,                 /**< [In] Pointer to configuration buffer for LoadReg mode; See description above. */
		uint8_t * pTxBuffer,                      /**< [In] Pointer to global transmit buffer used by the Exchange() function. */
		uint16_t wTxBufSize,                      /**< [In] Size of the global transmit buffer. */
		uint8_t * pRxBuffer,                      /**< [In] Pointer to global receive buffer used by the Exchange() function. */
		uint16_t wRxBufSize                       /**< [In] Size of the global receive buffer. Specify the buffer +1 byte, because one byte is reserved for SPI communication. */
		);

#include <phhalHw_Rc663_Reg.h>
#include <phhalHw_Rc663_Cmd.h>

	/** @} */
#endif /* NXPBUILD__PHHAL_HW_RC663 */

#ifdef NXPBUILD__PHHAL_HW_RC523

	/** \defgroup phhalHw_Rc523 Component : Rc523
	* \brief RC523 Reader HAL
	*
	* Since RC523 and PN512 are quite compatible, the following PN512 features are also supported:\n
	* \li #PHHAL_HW_CARDTYPE_FELICA
	* \li #PHHAL_HW_CARDTYPE_I18092MPI
	* \li #PHHAL_HW_CARDTYPE_I18092MPT
	* \li \ref phhalHw_Rc523_Cmd_Config
	* \li \ref phhalHw_Rc523_Cmd_Autocoll
	*
	* If #PHHAL_HW_CARDTYPE_I18092MPT is chosen, Exchange performs the reception BEFORE the transmission.
	*
	* This makes it neccessary for the application to know what to send before actually having received\n
	* the request. Therefore using phhalHw_Exchange for PN512 operation is only useful for test applications.\n
	* For other applications it's recommended to use \ref phhalHw_Rc523_Cmd_Transmit and \ref phhalHw_Rc523_Cmd_Receive.
	*
	* @{
	*/

#define PHHAL_HW_RC523_ID               0x02    /**< ID for Rc523 HAL component. */

#define PHHAL_HW_RC523_SHADOW_COUNT     0x000FU /**< Number of shadowed configurations. */

	/** \name Custom Option Bits
	*
	* Can be used for \ref phhalHw_Exchange, \ref phhalHw_Rc663_Cmd_Receive and \ref phhalHw_Rc663_Cmd_Transmit.
	*/
	/*@{*/
	/**
	Do not start timer after transmission / before reception; (only for \ref phhalHw_Rc523_Cmd_Receive and \ref phhalHw_Rc523_Cmd_Transmit).
	*/
#define PHHAL_HW_RC523_OPTION_RXTX_TIMER_NOSTART    0x0000U

	/**
	Start timer after transmission / before reception, reset timer counter value; (only for \ref phhalHw_Rc523_Cmd_Receive and \ref phhalHw_Rc523_Cmd_Transmit).
	*/
#define PHHAL_HW_RC523_OPTION_RXTX_TIMER_START  0x0010U
	/*@}*/

	/**
	* \brief Rc523 HAL parameter structure
	*/
	typedef struct
	{
		uint16_t wId;                                       /**< Layer ID for this component, NEVER MODIFY! */
		void  * pBalDataParams;                             /**< Pointer to the lower layers parameter structure. */
		void  * pKeyStoreDataParams;                        /**< Pointer to the parameter structure of the keyStore layer. */
		uint8_t * pTxBuffer;                                /**< Pointer to global transmit buffer used by the Exchange() function. */
		uint16_t wTxBufSize;                                /**< Size of the global transmit buffer. */
		uint16_t wTxBufLen;                                 /**< Number of valid bytes within the transmit buffer. */
		uint8_t * pRxBuffer;                                /**< Pointer to global receive buffer used by the Exchange() function. */
		uint16_t wRxBufSize;                                /**< Size of the global receive buffer. */
		uint16_t wRxBufLen;                                 /**< Number of valid bytes within the receive buffer. */
		uint16_t wRxBufStartPos;                            /**< Starting position within the global receive buffer. */
		uint16_t wMaxPrecachedBytes;                        /**< Holds the max. number of bytes which are precached prior to command execution. */
		uint8_t bCardType;                                  /**< Type of card for which the hal is configured for. */
		uint16_t wCfgShadow[PHHAL_HW_RC523_SHADOW_COUNT];   /**< Configuration shadow; Stores configuration for current cardtype. */
		uint16_t wTimingMode;                               /**< Current timing measurement mode. */
		uint8_t bTimeoutUnit;                               /**< Unit of current timeout value (either #PHHAL_HW_TIME_MICROSECONDS or #PHHAL_HW_TIME_MILLISECONDS). */
		uint32_t dwTimingUs;                                /**< Current timing value. */
		uint16_t wFieldOffTime;                             /**< Field-Off-Time in milliseconds. */
		uint16_t wFieldRecoveryTime;                        /**< Field-Recovery-Time in milliseconds. */
		uint16_t wAdditionalInfo;                           /**< Storage for additional error information. */
		uint8_t bBalConnectionType;                         /**< Type of the underlying BAL connection. Refer to #PHHAL_HW_CONFIG_BAL_CONNECTION. */
		uint8_t bRfResetAfterTo;                            /**< Storage for #PHHAL_HW_CONFIG_RFRESET_ON_TIMEOUT setting. */
	} phhalHw_Rc523_DataParams_t;

	/**
	* \brief Initialise the HAL component.
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
	phStatus_t phhalHw_Rc523_Init(
		phhalHw_Rc523_DataParams_t * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
		uint16_t wSizeOfDataParams,               /**< [In] Specifies the size of the data parameter structure. */
		void * pBalDataParams,                    /**< [In] Pointer to the lower layers parameter structure. */
		void * pKeyStoreDataParams,               /**< [In] Pointer to the parameter structure of the keyStore layer. */
		uint8_t * pTxBuffer,                      /**< [In] Pointer to global transmit buffer used by the Exchange() function. */
		uint16_t wTxBufSize,                      /**< [In] Size of the global transmit buffer. */
		uint8_t * pRxBuffer,                      /**< [In] Pointer to global receive buffer used by the Exchange() function. */
		uint16_t wRxBufSize                       /**< [In] Size of the global receive buffer. Specify the buffer +1 byte, because one byte is reserved for SPI communication. */
		);

#include <phhalHw_Rc523_Reg.h>
#include <phhalHw_Rc523_Cmd.h>

	/** @} */
#endif /* NXPBUILD__PHHAL_HW_RC523 */

#ifdef NXPBUILD__PHHAL_HW_RD70X

	/** \defgroup phhalHw_Rd70x Component : Rd70x
	* \brief RD70x (Pegoda1) Reader HAL
	*
	* It is neccessary to make use of #PHHAL_HW_RD70X_CONFIG_DISABLE_PCDRESET for this reader to support multiple cards.
	* @{
	*/

#define PHHAL_HW_RD70X_ID   0x04    /**< ID for Rd70x HAL component. */

	/**
	* \name Rd70x specific configs
	*/
	/*@{*/
	/**
	* \brief Disable PcdReset call in \ref phhalHw_ApplyProtocolSettings function.
	*
	* Set this to #PH_ON on every HAL instance to prevent the reader from resetting powered cards\n
	* on an \ref phhalHw_ApplyProtocolSettings call.\n
	* Ensure that it is set to #PH_OFF when you set the protocol the first time to have essential parameters set in the firmware.
	*/
#define PHHAL_HW_RD70X_CONFIG_DISABLE_PCDRESET  (PH_CONFIG_CUSTOM_BEGIN)
	/*@}*/

#define PHHAL_HW_RD70X_SHADOW_COUNT             0x000DU     /**< Number of shadowed configurations. */
#define PHHAL_HW_RD70X_RESERVED_BUFFER_LEN      32U         /**< Amount of needed and reserved memory for the protocol overhead. */
#define PHHAL_HW_RD70X_FIFOSIZE                 256U        /**< Size of RC internal FiFo buffer. */
#define PHHAL_HW_RD70X_DEFAULT_TIMEOUT_MS       5U          /**< Default timeout in milliseconds. */

	/**
	* \brief Rd70x HAL parameter structure
	*/
	typedef struct 
	{
		uint16_t wId;                                               /**< Layer ID for this component, NEVER MODIFY! */
		phbalReg_Rd70xUsbWin_DataParams_t * pBalDataParams;         /**< pointer to the lower layers parameter structure */
		uint8_t * pTxBuffer;                                        /**< Pointer to global transmit buffer used by the Exchange() function. */
		uint16_t wTxBufSize;                                        /**< Size of the global transmit buffer. */
		uint16_t wTxBufLen;                                         /**< Number of valid bytes within the transmit buffer. */
		uint8_t * pRxBuffer;                                        /**< Pointer to global receive buffer used by the Exchange() function. */
		uint16_t wRxBufSize;                                        /**< Size of the global receive buffer. */
		uint16_t wRxBufLen;                                         /**< Number of valid bytes within the receive buffer. */
		uint16_t wRxBufStartPos;                                    /**< Starting position within the global receive buffer. */
		uint16_t wTxBufStartPos;                                    /**< Starting position within the global transmit buffer (used if \b TxBuffer equals \b RxBuffer). */
		uint8_t bCardType;                                          /**< Type of card for which the hal is configured for. */
		uint16_t wCfgShadow[PHHAL_HW_RD70X_SHADOW_COUNT];           /**< Configuration shadow; Stores configuration for current cardtype. */
		uint16_t wTimingMode;                                       /**< Current timing measurement mode. */
		uint32_t dwTimeoutUs;                                       /**< TO value to be used with phhalHwRd700PiccExchgBitByte function. */
		uint32_t dwTimingUs;                                        /**< Current timing value. */
		uint16_t wAdditionalInfo;                                   /**< Storage for additional error information. */
		uint16_t wTxRxStartBackup;                                  /**< Absolute Start-Position for transmission / reception used by buffer preservation mechanism. */
		uint16_t wFieldOffTime;                                     /**< Field-Off-Time in milliseconds. */
		uint16_t wFieldRecoveryTime;                                /**< Field-Recovery-Time in milliseconds. */
		uint8_t bSymbolStart;                                       /**< Preamble of a frame. */
		uint8_t bSymbolEnd;                                         /**< Trailer symbol of a frame. */
		uint8_t bDisablePcdReset;                                   /**< Whether to disable PcdReset call in \ref phhalHw_ApplyProtocolSettings function or not. */
		uint8_t bFlags;                                             /**< Flags to be used with phhalHwRd700PiccExchgBitByte function. */
		uint8_t bProtBuffer[PHHAL_HW_RD70X_RESERVED_BUFFER_LEN];    /**< Protocol buffer. */
		uint8_t bProtBufferLen;                                     /**< Length of protocol data. */
		uint16_t wProtRxBufReadPos;                                 /**< Read position within \b pRxBuffer for protocol. */
		uint8_t bRfResetAfterTo;                                    /**< Storage for #PHHAL_HW_CONFIG_RFRESET_ON_TIMEOUT setting. */
	} phhalHw_Rd70x_DataParams_t;

	/**
	* \brief Initialise the HAL component.
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
	phStatus_t phhalHw_Rd70x_Init(
		phhalHw_Rd70x_DataParams_t * pDataParams,             /**< [In] Pointer to this layer's parameter structure. */
		uint16_t wSizeOfDataParams,                           /**< [In] Specifies the size of the data parameter structure. */
		phbalReg_Rd70xUsbWin_DataParams_t * pBalDataParams,   /**< [In] Pointer to the lower layers parameter structure. */
		uint8_t * pTxBuffer,                                  /**< [In] Pointer to global transmit buffer used by the Exchange() function. */
		uint16_t wTxBufSize,                                  /**< [In] Size of the global transmit buffer. */
		uint8_t * pRxBuffer,                                  /**< [In] Pointer to global receive buffer used by the Exchange() function. */
		uint16_t wRxBufSize                                   /**< [In] Size of the global receive buffer. */
		);

#include <phhalHw_Rd70x_Reg.h>
#include <phhalHw_Rd70x_Cmd.h>

	/** @} */
#endif /* NXPBUILD__PHHAL_HW_RD70X */

#ifdef NXPBUILD__PHHAL_HW_RC632

	/** \defgroup phhalHw_Rc632 Component : Rc632
	* \brief RC632 Reader HAL
	*
	* @{
	*/
#define PHHAL_HW_RC632_ID   0x09                            /**< ID for Rc632 HAL component. */

#define PHHAL_HW_RC632_SHADOW_COUNT             0x000DU     /**< Number of shadowed configurations. */
#define PHHAL_HW_RC632_DEFAULT_TIMEOUT_MS       5U          /**< Default timeout in milliseconds. */

	/**
	* \brief Rc632 HAL parameter structure
	*/
	typedef struct
	{
		unsigned short wId;                                       /**< Layer ID for this HAL component, NEVER MODIFY! */
		void  * pBalDataParams;                                   /**< Pointer to the lower layers parameter structure. */
		unsigned char * pTxBuffer;                                /**< Pointer to global transmit buffer used by the Exchange() function. */
		unsigned short wTxBufSize;                                /**< Size of the global transmit buffer. */
		unsigned short wTxBufLen;                                 /**< Number of valid bytes within the transmit buffer. */
		unsigned char * pRxBuffer;                                /**< Pointer to global receive buffer used by the Exchange() function. */
		unsigned short wRxBufSize;                                /**< Size of the global receive buffer. */
		unsigned short wRxBufLen;                                 /**< Number of valid bytes within the receive buffer. */
		unsigned short wRxBufStartPos;                            /**< Starting position within the global receive buffer. */
		unsigned short wTxBufStartPos;                            /**< Starting position within the global transmit buffer (used if TxBuffer = RxBuffer). */
		unsigned short wMaxPrecachedBytes;                        /**< Holds the max. number of bytes which are precached prior to command execution. */
		unsigned char bCardType;                                  /**< Type of card for which the hal is configured for. */
		unsigned short wCfgShadow[0x10];						  /**< Configuration shadow; Stores configuration for current cardtype. */
		unsigned short wTimingMode;                               /**< Current timing measurement mode. */
		unsigned char bTimeoutUnit;                               /**< Unit of current timeout value (either #PHHAL_HW_TIME_MICROSECONDS or #PHHAL_HW_TIME_MILLISECONDS). */
		unsigned int dwTimingUs;                                  /**< Current timing value. */
		unsigned int dwTimeoutUs;                                 /**< Current timing value. */
		unsigned short wFieldOffTime;                             /**< Field-Off-Time in milliseconds. */
		unsigned short wFieldRecoveryTime;                        /**< Field-Recovery-Time in milliseconds. */
		unsigned char bSymbolStart;                               /**< Preamble of a frame. */
		unsigned char bSymbolEnd;                                 /**< Trailer symbol of a frame. */
		unsigned char bDisablePcdReset;                           /**< Whether to disable PcdReset call in \ref phhalHw_ApplyProtocolSettings function or not. */
		unsigned char bFlags;                                     /**< Flags to be used.*/ 
		unsigned char bFifoSize;                                  /**< Fifo-Size setting. */
		unsigned short wAdditionalInfo;                           /**< Storage for additional error information. */
		unsigned char bBalConnectionType;                         /**< Type of the underlying BAL connection. Refer to #PHHAL_HW_CONFIG_BAL_CONNECTION. */
		unsigned char bRfResetAfterTo;                            /**< Storage for #PHHAL_HW_CONFIG_RFRESET_ON_TIMEOUT setting. */
	} phhalHw_Rc632_DataParams_t;

	/**
	* \brief Initialise the HAL component.
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
	phStatus_t phhalHw_Rc632_Init(
		phhalHw_Rc632_DataParams_t * pDataParams,/**< [In] Pointer to this layer's parameter structure. */
		uint16_t wSizeOfDataParams,			   /**< [In] Specifies the size of the data parameter structure. */
		void * pBalDataParams,				   /**< [In] Pointer to the lower layers parameter structure. */
		uint8_t* pTxBuffer,					   /**< [In] Pointer to global transmit buffer used by the Exchange() function. */
		uint16_t wTxBufSize,					   /**< [In] Size of the global transmit buffer. */
		uint8_t* pRxBuffer,					   /**< [In] Pointer to global receive buffer used by the Exchange() function. */
		uint16_t wRxBufSize					   /**< [In] Size of the global receive buffer. Specify the buffer +1 byte, because one byte is reserved for SPI communication. */
		);									   

#include <phhalHw_Rc632_Reg.h>										   
#include <phhalHw_Rc632_Cmd.h>										   

	/** @} */															   

#endif /* NXPBUILD__PHHAL_HW_RC632 */

#ifdef NXPBUILD__PHHAL_HW_CALLBACK

	/** \defgroup phhalHw_Callback Component : Callback
	* \brief Callback Reader HAL
	*
	* Virtual reader device which can be used to implement custom reader devices.
	* @{
	*/

#define PHHAL_HW_CALLBACK_ID    0xAB    /**< ID for Rc523 HAL component. */

	/**
	* \brief Callback Delegate for \ref phhalHw_Exchange
	*/
	typedef phStatus_t (*cbExchange)(
		uint16_t wOption,      /**< [In] Option parameter. */
		uint8_t * pTxBuffer,   /**< [In] Data to transmit. */
		uint16_t wTxLength,    /**< [In] Length of data to transmit. */
		uint8_t ** ppRxBuffer, /**< [Out] Pointer to received data. */
		uint16_t * pRxLength,  /**< [Out] number of received data bytes. */
		void * pContext        /**< [Out] User Defined Context. */
		);

	/**
	* \brief Callback Delegate for \ref phhalHw_WriteRegister
	*/
	typedef phStatus_t (*cbWriteRegister)(
		uint8_t bAddress, /**< [In] Register Address. */
		uint8_t bValue,   /**< [In] Register Value. */
		void * pContext   /**< [Out] User Defined Context. */
		);

	/**
	* \brief Callback Delegate for \ref phhalHw_ReadRegister
	*/
	typedef phStatus_t (*cbReadRegister)(
		uint8_t bAddress,  /**< [In] Register Address. */
		uint8_t * pValue,  /**< [Out] Register Value. */
		void * pContext    /**< [Out] User Defined Context. */
		);

	/**
	* \brief Callback Delegate for \ref phhalHw_ApplyProtocolSettings
	*/
	typedef phStatus_t (*cbApplyProtocolSettings)(
		uint8_t bCardType,  /**< [In] Type of card for which the hal should be configured for. */
		void * pContext     /**< [Out] User Defined Context. */
		);

	/**
	* \brief Callback Delegate for \ref phhalHw_MfcAuthenticate
	*/
	typedef phStatus_t (*cbMfcAuthenticate)(
		uint8_t bBlockNo,       /**< [In] Blocknumber on card to authenticate to. */
		uint8_t bKeyType,       /**< [In] Either #PHHAL_HW_MFC_KEYA or #PHHAL_HW_MFC_KEYB. */
		uint16_t wKeyNo,        /**< [In] Key number to be used in authentication. */
		uint16_t wKeyVersion,   /**< [In] Key version to be used in authentication. */
		uint8_t * pUid,         /**< [In] Serial number of current cascade level; uint8_t[4]. */
		void * pContext         /**< [Out] User Defined Context. */
		);

	/**
	* \brief Callback Delegate for \ref phhalHw_MfcAuthenticateKeyNo
	*/
	typedef phStatus_t (*cbMfcAuthenticateKey)(
		uint8_t bBlockNo,   /**< [In] Blocknumber on card to authenticate to. */
		uint8_t bKeyType,   /**< [In] Either #PHHAL_HW_MFC_KEYA or #PHHAL_HW_MFC_KEYB */
		uint8_t * pKey,     /**< [In] Key to be used in authentication. */
		uint8_t * pUid,     /**< [In] Serial number of current cascade level; uint8_t[4]. */
		void * pContext     /**< [Out] User Defined Context. */
		);

	/**
	* \brief Callback Delegate for \ref phhalHw_SetConfig
	*/
	typedef phStatus_t (*cbSetConfig)(
		uint16_t wConfig, /**< [In] Configuration Identifier. */
		uint16_t wValue,  /**< [In] Configuration Value. */
		void * pContext   /**< [Out] User Defined Context. */
		);

	/**
	* \brief Callback Delegate for \ref phhalHw_GetConfig
	*/
	typedef phStatus_t (*cbGetConfig)(
		uint16_t wConfig,     /**< [In] Configuration Identifier. */
		uint16_t * pValue,    /**< [Out] Configuration Value. */
		void * pContext       /**< [Out] User Defined Context. */
		);

	/**
	* \brief Callback Delegate for \ref phhalHw_FieldOn
	*/
	typedef phStatus_t (*cbFieldOn)(
		void * pContext /**< [Out] User Defined Context. */
		);

	/**
	* \brief Callback Delegate for \ref phhalHw_FieldOff
	*/
	typedef phStatus_t (*cbFieldOff)(
		void * pContext    /**< [Out] User Defined Context. */
		);

	/**
	* \brief Callback Delegate for \ref phhalHw_FieldReset
	*/
	typedef phStatus_t (*cbFieldReset)(
		void * pContext  /**< [Out] User Defined Context. */
		);

	/**
	* \brief Callback Delegate for \ref phhalHw_Wait
	*/
	typedef phStatus_t (*cbWait)(
		uint8_t bUnit,     /**< [In] Unit of given timeout value (either #PHHAL_HW_TIME_MICROSECONDS or #PHHAL_HW_TIME_MILLISECONDS). */
		uint16_t wTimeout, /**< [In] Timeout value. */
		void * pContext    /**< [Out] User Defined Context. */
		);

	/**
	* \brief Callback HAL parameter structure
	*/
	typedef struct 
	{
		uint16_t wId;                                       /**< Layer ID for this component, NEVER MODIFY! */
		cbExchange pExchangeCb;                             /**< Pointer to \ref cbExchange Callback. */
		cbWriteRegister pWriteRegisterCb;                   /**< Pointer to \ref cbWriteRegister Callback. */
		cbReadRegister pReadRegisterCb;                     /**< Pointer to \ref cbReadRegister Callback. */
		cbApplyProtocolSettings pApplyProtocolSettingsCb;   /**< Pointer to \ref cbApplyProtocolSettings Callback. */
		cbMfcAuthenticate pMfcAuthenticateCb;               /**< Pointer to \ref cbMfcAuthenticate Callback. */
		cbMfcAuthenticateKey pMfcAuthenticateKeyCb;         /**< Pointer to \ref cbMfcAuthenticateKey Callback. */
		cbSetConfig pSetConfigCb;                           /**< Pointer to \ref cbSetConfig Callback. */
		cbGetConfig pGetConfigCb;                           /**< Pointer to \ref cbGetConfig Callback. */
		cbFieldOn pFieldOnCb;                               /**< Pointer to \ref cbFieldOn Callback. */
		cbFieldOff pFieldOffCb;                             /**< Pointer to \ref cbFieldOff Callback. */
		cbFieldReset pFieldResetCb;                         /**< Pointer to \ref cbFieldReset Callback. */
		cbWait pWaitCb;                                     /**< Pointer to \ref cbWait Callback. */
		void * pCbContext;                                  /**< Custom context which is passed back to each Callback. */
	} phhalHw_Callback_DataParams_t;

	/**
	* \brief Initialise the HAL component.
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
	phStatus_t phhalHw_Callback_Init(
		phhalHw_Callback_DataParams_t * pDataParams,       /**< [In] Pointer to this layer's parameter structure. */
		uint16_t wSizeOfDataParams,                        /**< [In] Specifies the size of the data parameter structure. */
		cbExchange pExchangeCb,                            /**< [In] Pointer to \ref cbExchange Callback. */
		cbWriteRegister pWriteRegisterCb,                  /**< [In] Pointer to \ref cbWriteRegister Callback. */
		cbReadRegister pReadRegisterCb,                    /**< [In] Pointer to \ref cbReadRegister Callback. */
		cbApplyProtocolSettings pApplyProtocolSettingsCb,  /**< [In] Pointer to \ref cbApplyProtocolSettings Callback. */
		cbMfcAuthenticate pMfcAuthenticateCb,              /**< [In] Pointer to \ref cbMfcAuthenticate Callback. */
		cbMfcAuthenticateKey pMfcAuthenticateKeyCb,        /**< [In] Pointer to \ref cbMfcAuthenticateKey Callback. */
		cbSetConfig pSetConfigCb,                          /**< [In] Pointer to \ref cbSetConfig Callback. */
		cbGetConfig pGetConfigCb,                          /**< [In] Pointer to \ref cbGetConfig Callback. */
		cbFieldOn pFieldOnCb,                              /**< [In] Pointer to \ref cbFieldOn Callback. */
		cbFieldOff pFieldOffCb,                            /**< [In] Pointer to \ref cbFieldOff Callback. */
		cbFieldReset pFieldResetCb,                        /**< [In] Pointer to \ref cbFieldReset Callback. */
		cbWait pWaitCb,                                    /**< [In] Pointer to \ref cbWait Callback. */
		void * pCallbackContext                            /**< [In] Custom context which is passed back to each Callback. */
		);

	/** @} */
#endif /* NXPBUILD__PHHAL_HW_CALLBACK */

#ifdef NXPBUILD__PHHAL_HW_RD710

	/** \defgroup phhalHw_Rd710 Component : Rd710
	* \brief RD710 (Pegoda2) Reader HAL
	* @{
	*/

#define PHHAL_HW_RD710_ID   0x06    /**< ID for Rd710 HAL component. */

#define PHHAL_HW_RD710_RESERVED_BUFFER_LEN  8U  /**< Amount of needed and reserved memory for the protocol overhead. */

	/**
	* \brief Rd710 HAL parameter structure
	*/
	typedef struct 
	{
		uint16_t wId;               /**< Layer ID for this component, NEVER MODIFY! */
		void  * pBalDataParams;     /**< pointer to the lower layers parameter structure. */
		uint8_t bSlotNumber;        /**< Slot number. */
		uint8_t bTxLastBits;        /**< TxLastbits for ExchangeRaw function. */
		uint8_t * pTxBuffer;        /**< Pointer to global transmit buffer used by the Exchange() function. */
		uint16_t wTxBufSize;        /**< Size of the global transmit buffer. */
		uint16_t wTxBufLen;         /**< Number of valid bytes within the transmit buffer. */
		uint16_t wTxBufStart;       /**< Startposition in case of buffering within the transmit buffer. */
		uint8_t * pRxBuffer;        /**< Pointer to global receive buffer used by the Exchange() function. */
		uint16_t wRxBufSize;        /**< Size of the global receive buffer. */
		uint16_t wRxBufLen;         /**< Number of valid bytes within the receive buffer. */
		uint16_t wRxBufStartPos;    /**< Starting position within the global receive buffer. */
		uint16_t wTxBufStartPos;    /**< Starting position within the global transmit buffer (used if \b TxBuffer equals \b RxBuffer). */
	} phhalHw_Rd710_DataParams_t;

	/**
	* \name PCSC Modes
	*/
	/*@{*/
#define PHHAL_HW_RD710_PCSCMODE_DEFAULT     0x0000U /**< Default PC/SC operation. */
#define PHHAL_HW_RD710_PCSCMODE_DIRECT      0x0001U /**< Direct PC/SC mode (Exchange raw reader commands). */
	/*@}*/

	/**
	* \brief Initialise the HAL component.
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
	phStatus_t phhalHw_Rd710_Init(
		phhalHw_Rd710_DataParams_t * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
		uint16_t wSizeOfDataParams,               /**< [In] Specifies the size of the data parameter structure. */
		void * pBalDataParams,                    /**< [In] Pointer to the lower layers parameter structure. */
		uint8_t bSlotNumber,                      /**< [In] Slot number. */
		uint8_t * pTxBuffer,                      /**< [In] Pointer to global transmit buffer used by the Exchange() function. */
		uint16_t wTxBufSize,                      /**< [In] Size of the global transmit buffer. */
		uint8_t * pRxBuffer,                      /**< [In] Pointer to global receive buffer used by the Exchange() function. */
		uint16_t wRxBufSize                       /**< [In] Size of the global receive buffer. */
		);

#include <phhalHw_Rd710_Cmd.h>

	/** @} */
#endif /* NXPBUILD__PHHAL_HW_RD710 */

#ifdef NXPBUILD__PHHAL_HW

	/** \defgroup phhalHw Hardware Abstraction Layer
	* \brief These are the Components which are used to abstract the
	* functionality of the physical reader device to a generic interface.
	* @{
	*/

	/**
	* \name Communication Configs
	*/
	/*@{*/
#define PHHAL_HW_CONFIG_PARITY              0x0000U     /**< Enable or Disable Parity. */
#define PHHAL_HW_CONFIG_TXCRC               0x0001U     /**< Enable or Disable TxCrc. */
#define PHHAL_HW_CONFIG_RXCRC               0x0002U     /**< Enable or Disable RxCrc. */
#define PHHAL_HW_CONFIG_TXLASTBITS          0x0003U     /**< Set number of valid bits of last Tx-Byte. */
#define PHHAL_HW_CONFIG_RXLASTBITS          0x0004U     /**< Get number of valid bits of last Rx-Byte. */
#define PHHAL_HW_CONFIG_RXALIGN             0x0005U     /**< Set Rx-Aligned Bits. */
#define PHHAL_HW_CONFIG_RXDEAFBITS          0x0006U     /**< Configure Receiver Deaf-Time in ETUs. */
#define PHHAL_HW_CONFIG_TXWAIT_US           0x0007U     /**< Set TxWait (= time between last RxIrq and Tx of succeeding frame) in microseconds. */
#define PHHAL_HW_CONFIG_CLEARBITSAFTERCOLL  0x0008U     /**< Enable or Disable clearing of bits after coll. */
#define PHHAL_HW_CONFIG_TXDATARATE          0x0009U     /**< Configure Data-Rate for Transmission. */
#define PHHAL_HW_CONFIG_RXDATARATE          0x000AU     /**< Configure Data-Rate for Reception. */
#define PHHAL_HW_CONFIG_MODINDEX            0x000BU     /**< Set modulation index (unit and value are hardware-dependent). */
#define PHHAL_HW_CONFIG_ASK100              0x000CU     /**< Enable (#PH_ON) or disable (#PH_OFF) 100% modulation. */
#define PHHAL_HW_CONFIG_TIMEOUT_VALUE_US    0x000DU     /**< Set RC Timeout (in [us]). */
#define PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS    0x000EU     /**< Set RC Timeout (in [ms]). */
#define PHHAL_HW_CONFIG_SUBCARRIER          0x000FU     /**< Subcarrier setting for ISO 15693. */
#define PHHAL_HW_CONFIG_TIMING_MODE         0x0010U     /**< Set the timing mode. */
#define PHHAL_HW_CONFIG_TIMING_US           0x0011U     /**< Retrieve elapsed time of RC timer ([us]). */
#define PHHAL_HW_CONFIG_TIMING_MS           0x0012U     /**< Retrieve elapsed time of RC timer ([ms]). */
#define PHHAL_HW_CONFIG_FIELD_OFF_TIME      0x0013U     /**< Set the field off time for field-reset ([ms]); \b Note: A value of \c 0 is not allowed. */
#define PHHAL_HW_CONFIG_FIELD_RECOVERY_TIME 0x0014U     /**< Set the field recovery time for field-reset ([ms]); \b Note: For ISO15693 operation, this should be at least set to \c 1ms. */
#define PHHAL_HW_CONFIG_SYMBOL_START        0x0015U     /**< Disable / Set the SOF symbol of a frame. */
#define PHHAL_HW_CONFIG_SYMBOL_END          0x0016U     /**< Disable / Set the EOF symbol of a frame. */
#define PHHAL_HW_CONFIG_DISABLE_MF_CRYPTO1  0x002EU     /**< Disable MIFARE(R) Classic Crypto1. */
#define PHHAL_HW_CONFIG_ADDITIONAL_INFO     0x002FU     /**< Set / Get additional information. */
#define PHHAL_HW_CONFIG_RXBUFFER_STARTPOS   0x0030U     /**< Start position of RX buffer to be used (never changed by HAL). */
#define PHHAL_HW_CONFIG_RXBUFFER_BUFSIZE    0x0031U     /**< Buffer size of RX buffer set at Init. */
#define PHHAL_HW_CONFIG_TXBUFFER_BUFSIZE    0x0032U     /**< Buffer size of TX buffer set at Init. */
#define PHHAL_HW_CONFIG_TXBUFFER_LENGTH     0x0033U     /**< Amount of valid bytes in TX buffer. */
#define PHHAL_HW_CONFIG_TXBUFFER            0x0034U     /**< Access the TxBuffer at the address defined by #PHHAL_HW_CONFIG_ADDITIONAL_INFO. */
#define PHHAL_HW_CONFIG_MAX_PRECACHED_BYTES 0x0035U     /**< Configures the max. number of bytes which are precached prior to command execution. */
#define PHHAL_HW_CONFIG_BAL_CONNECTION      0x0040U     /**< Set the BAL connection type. The default value is always #PHHAL_HW_BAL_CONNECTION_RS232. */
#define PHHAL_HW_CONFIG_SERIAL_BITRATE      0x0041U     /**< Bitrate for serial communication. */
#define PHHAL_HW_CONFIG_RFRESET_ON_TIMEOUT  0x0050U     /**< Perform an Rf-Reset in case of a timeout (only for \ref phhalHw_Exchange). */
	/*@}*/

	/**
	* \name Card Configs
	*/
	/*@{*/
#define PHHAL_HW_CARDTYPE_CURRENT           0x0000U /**< Re-Apply settings for current Communication Mode. */
#define PHHAL_HW_CARDTYPE_ISO14443A         0x0001U /**< ISO/IEC 14443A Mode. */
#define PHHAL_HW_CARDTYPE_ISO14443B         0x0002U /**< ISO/IEC 14443B Mode. */
#define PHHAL_HW_CARDTYPE_FELICA            0x0003U /**< Felica (JIS X 6319) Mode. */
#define PHHAL_HW_CARDTYPE_ISO15693          0x0004U /**< ISO/IEC 15693 Mode. */
#define PHHAL_HW_CARDTYPE_ICODEEPCUID       0x0005U /**< NXP I-Code EPC/UID Mode. */
#define PHHAL_HW_CARDTYPE_I18000P3M3        0x0006U /**< ISO/IEC 18000-3 Mode3. */
#define PHHAL_HW_CARDTYPE_I18092MPI         0x0007U /**< ISO/IEC ISO18092 (NFC) Passive Initiator Mode. */
#define PHHAL_HW_CARDTYPE_I18092MPT         0x0008U /**< ISO/IEC ISO18092 (NFC) Passive Target Mode. */
	/*@}*/

	/**
	* \name Rf Datarate Values
	*/
	/*@{*/
#define PHHAL_HW_RF_DATARATE_106                0x0000U /**< Data rate setting for 106 kBit/s. */
#define PHHAL_HW_RF_DATARATE_212                0x0001U /**< Data rate setting for 212 kBit/s. */
#define PHHAL_HW_RF_DATARATE_424                0x0002U /**< Data rate setting for 424 kBit/s. */
#define PHHAL_HW_RF_DATARATE_848                0x0003U /**< Data rate setting for 848 kBit/s. */

#define PHHAL_HW_RF_TX_DATARATE_1_OUT_OF_256    0x000AU /**< Data rate setting for ISO15693 '1 out of 256' mode. */
#define PHHAL_HW_RF_TX_DATARATE_1_OUT_OF_4      0x000BU /**< Data rate setting for ISO15693 '1 out of 4' mode. */
#define PHHAL_HW_RF_RX_DATARATE_LOW             0x000CU /**< Data rate setting for ISO15693 low datarate. */
#define PHHAL_HW_RF_RX_DATARATE_HIGH            0x000DU /**< Data rate setting for ISO15693 high datarate. */
#define PHHAL_HW_RF_RX_DATARATE_FAST_LOW        0x000EU /**< Data rate setting for ISO15693 fast (low*2) datarate (FAST INVENTORY (PAGE) READ). */
#define PHHAL_HW_RF_RX_DATARATE_FAST_HIGH       0x000FU /**< Data rate setting for ISO15693 fast (high*2) datarate (FAST INVENTORY (PAGE) READ). */

#define PHHAL_HW_RF_DATARATE_EPCUID             0x0010U /**< Data rate setting for EPC/UID. */

#define PHHAL_HW_RF_TX_DATARATE_I18000P3M3      0x0011U /**< Tx Data rate setting for ISO18000-3 Mode3. */
#define PHHAL_HW_RF_RX_DATARATE_I18000P3M3_MAN2 0x0012U /**< Rx Data rate setting for ISO18000-3 Mode3 Manchester 2SCP. */
#define PHHAL_HW_RF_RX_DATARATE_I18000P3M3_MAN4 0x0013U /**< Rx Data rate setting for ISO18000-3 Mode3 Manchester 4SCP. */
	/*@}*/

	/**
	* \name Rf Subcarrier Values
	*/
	/*@{*/
#define PHHAL_HW_SUBCARRIER_SINGLE  0x0000U /**< Sub carrier setting for ISO15693 single subcarrier. */
#define PHHAL_HW_SUBCARRIER_DUAL    0x0001U /**< Sub carrier setting for ISO15693 / EPC V2 dual subcarrier. */
#define PHHAL_HW_SUBCARRIER_QUAD    0x0002U /**< Sub carrier setting for EPC V2 quad subcarrier. */
	/*@}*/

	/**
	* \name Time Units
	*/
	/*@{*/
#define PHHAL_HW_TIME_MICROSECONDS  0x0000U /**< Time in microseconds (us). */
#define PHHAL_HW_TIME_MILLISECONDS  0x0001U /**< Time in milliseconds (ms). */
	/*@}*/

	/**
	* \name Timing Mode settings
	*/
	/*@{*/
#define PHHAL_HW_TIMING_MODE_OFF                0x0000U /**< Time Measurement disabled. */
#define PHHAL_HW_TIMING_MODE_FDT                0x0001U /**< Measures time from Tx-End until Rx-Begin. */
#define PHHAL_HW_TIMING_MODE_COMM               0x0002U /**< Measures the duration of the complete communication. */
#define PHHAL_HW_TIMING_MODE_OPTION_MASK        0xFF00U /**< Additional option-mask for time measurement. */
#define PHHAL_HW_TIMING_MODE_OPTION_DEFAULT     0x0000U /**< The timing value is cummulated on each Exchange until it gets retrieved by \ref phhalHw_GetConfig. */
#define PHHAL_HW_TIMING_MODE_OPTION_AUTOCLEAR   0x0100U /**< Automatically resets the current timing value prior to any communication. */
	/*@}*/

	/**
	* \name Field Reset default times
	*/
	/*@{*/
#define PHHAL_HW_FIELD_OFF_DEFAULT          0x0005U     /**< Default Field-Off time. */
#define PHHAL_HW_FIELD_RECOVERY_DEFAULT     0x0005U     /**< Default Field-Recovery time. */
	/*@}*/

	/**
	* \name Frame Symbols (use #PH_OFF to disable)
	*/
	/*@{*/
#define PHHAL_HW_SYMBOL_ICODEEPCUID_SSOF    0x0001U /**< ICode EPC/UID Short Start Of Frame. */
#define PHHAL_HW_SYMBOL_ICODEEPCUID_LSOF    0x0002U /**< ICode EPC/UID Long Start Of Frame. */
#define PHHAL_HW_SYMBOL_ICODEEPCUID_CEOF    0x0003U /**< ICode EPC/UID Common End Of Frame. */
#define PHHAL_HW_SYMBOL_ICODEEPCUID_CS      0x0004U /**< ICode EPC/UID Close Slot. */
#define PHHAL_HW_SYMBOL_I15693_SOF          0x0005U /**< ISO15693 SOF (aumatically choosen between 1/256 and 1/4). */
#define PHHAL_HW_SYMBOL_I18000P3M3_PREAMBLE 0x0006U /**< ISO18000-3 Mode3 Preamble. */
#define PHHAL_HW_SYMBOL_I18000P3M3_FSYNC    0x0007U /**< ISO18000-3 Mode3 Frame-Sync. */
	/*@}*/

	/**
	* \name MIFARE Classic Authenticate Options
	*/
	/*@{*/
#define PHHAL_HW_MFC_KEYA               0x0AU   /**< MIFARE Classic Key Type A. */
#define PHHAL_HW_MFC_KEYB               0x0BU   /**< MIFARE Classic Key Type B. */
#define PHHAL_HW_MFC_KEY_LENGTH         0x06U   /**< Length of a MIFARE Classic key (for completeness). */
	/*@}*/

	/**
	* \name BAL Connection types
	*/
	/*@{*/
#define PHHAL_HW_BAL_CONNECTION_RS232   0x0000U     /**< ReaderIC is connected via RS232. */
#define PHHAL_HW_BAL_CONNECTION_SPI     0x0001U     /**< ReaderIC is connected via SPI. */
#define PHHAL_HW_BAL_CONNECTION_I2C     0x0002U     /**< ReaderIC is connected via I2C. */
	/*@}*/

	/**
	* \name RS232 Bitrate Values
	*/
	/*@{*/
#define PHHAL_HW_RS232_BITRATE_7200     0x0000U     /**< 7.200 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_9600     0x0001U     /**< 9.600 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_14400    0x0002U     /**< 14.400 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_19200    0x0003U     /**< 19.200 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_38400    0x0004U     /**< 38.400 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_57600    0x0005U     /**< 57.500 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_115200   0x0006U     /**< 115.200 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_128000   0x0007U     /**< 128.000 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_230400   0x0008U     /**< 230.400 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_460800   0x0009U     /**< 460.800 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_921600   0x000AU     /**< 921.600 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_1228800  0x000BU     /**< 1.228.800 kBit/s. */
	/*@}*/

	/**
	* \brief Perform Data Exchange with Picc.
	*
	* \b wOption can be one of:\n
	* \li #PH_EXCHANGE_DEFAULT
	*
	* \b wOption can be combined with:\n
	* \li #PH_EXCHANGE_BUFFERED_BIT
	* \li #PH_EXCHANGE_LEAVE_BUFFER_BIT
	*
	* \ref phhalHw_Rc523 <em>Special Behaviour:</em>\n
	* If #PHHAL_HW_CARDTYPE_I18092MPT is chosen, Exchange performs the reception BEFORE the transmission.\n
	* For details refer to \ref phhalHw_Rc523.
	*
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval #PH_ERR_INVALID_PARAMETER \b wOption is invalid.
	* \retval #PH_ERR_SUCCESS_INCOMPLETE_BYTE Operation successful, incomplete byte received; Retrieve number of valid bits of last byte with #PHHAL_HW_CONFIG_RXLASTBITS.
	* \retval #PH_ERR_IO_TIMEOUT No response detected within the configured time frame.
	* \retval #PH_ERR_INTEGRITY_ERROR Response received but CRC or Parity is invalid.
	* \retval #PH_ERR_COLLISION_ERROR Response received but a collision occured; Retrieve number of valid bits of last byte with #PHHAL_HW_CONFIG_RXLASTBITS.
	* \retval #PH_ERR_BUFFER_OVERFLOW Internal receive buffer is too small for transmission or smaller than the response.
	* \retval #PH_ERR_FRAMING_ERROR Frame format is either invalid for configured protocol or corrupted.
	* \retval #PH_ERR_PROTOCOL_ERROR Frame format is definitely invalid for configured protocol.
	* \retval #PH_ERR_READ_WRITE_ERROR Hardware problem.
	* \retval #PH_ERR_TEMPERATURE_ERROR Hardware problem.
	* \retval #PH_ERR_RF_ERROR Hardware problem.
	* \retval #PH_ERR_INTERFACE_ERROR Hardware problem.
	*/
	phStatus_t phhalHw_Exchange(
		void * pDataParams,     /**< [In] Pointer to this layer's parameter structure. */
		uint16_t wOption,       /**< [In] Option parameter. */
		uint8_t * pTxBuffer,    /**< [In] Data to transmit. */
		uint16_t wTxLength,     /**< [In] Number of bytes to transmit. */
		uint8_t ** ppRxBuffer,  /**< [Out] Pointer to received data. */
		uint16_t * pRxLength    /**< [Out] Number of received data bytes. */
		);

	/**
	* \brief Write value to register address.
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval #PH_ERR_INTERFACE_ERROR Hardware problem.
	*/
	phStatus_t phhalHw_WriteRegister(
		void * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
		uint8_t bAddress,      /**< [In] Register Address. */
		uint8_t bValue         /**< [In] Register Value. */
		);

	/**
	* \brief Read value from register address.
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval #PH_ERR_INTERFACE_ERROR Hardware problem.
	*/
	phStatus_t phhalHw_ReadRegister(
		void * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
		uint8_t bAddress,   /**< [In] Register Address. */
		uint8_t * pValue    /**< [Out] Register Value. */
		);

	/**
	* \brief Apply protocol settings.
	*
	* To keep the current card type, use #PHHAL_HW_CARDTYPE_CURRENT for bCardType.\n
	*
	* \ref phhalHw_Rc523 <em>Special Behaviour:</em>\n
	* If #PHHAL_HW_CARDTYPE_I18092MPT is chosen, Rx- and TxBuffers have to be different.
	*
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval #PH_ERR_INVALID_PARAMETER \b bCardType is invalid or not supported.
	* \retval #PH_ERR_INTERFACE_ERROR Hardware problem.
	*/
	phStatus_t phhalHw_ApplyProtocolSettings(
		void * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
		uint8_t bCardType   /**< [In] Type of card for which the HAL should be configured for. */
		);

	/**
	* \brief Perform MIFARE(R) Classic Authentication using a key number.
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval #PH_ERR_INVALID_PARAMETER \b bKeyType, \b wKeyNo or \b wKeyVersion is invalid.
	* \retval #PH_ERR_IO_TIMEOUT Error in authentication.
	* \retval #PH_ERR_AUTH_ERROR Error in authentication.
	*/
	phStatus_t phhalHw_MfcAuthenticateKeyNo(
		void * pDataParams,     /**< [In] Pointer to this layer's parameter structure. */
		uint8_t bBlockNo,       /**< [In] Blocknumber on card to authenticate to. */
		uint8_t bKeyType,       /**< [In] Either #PHHAL_HW_MFC_KEYA or #PHHAL_HW_MFC_KEYB. */
		uint16_t wKeyNo,        /**< [In] Key number to be used in authentication. */
		uint16_t wKeyVersion,   /**< [In] Key version to be used in authentication. */
		uint8_t * pUid          /**< [In] Serial number of current cascade level; uint8_t[4]. */
		);

	/**
	* \brief Perform MIFARE(R) Classic Authentication using a key.
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval #PH_ERR_INVALID_PARAMETER \b bKeyType is invalid.
	* \retval #PH_ERR_IO_TIMEOUT Error in authentication.
	* \retval #PH_ERR_AUTH_ERROR Error in authentication.
	*/
	phStatus_t phhalHw_MfcAuthenticate(
		void * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
		uint8_t bBlockNo,    /**< [In] Blocknumber on card to authenticate to. */
		uint8_t bKeyType,    /**< [In] Either #PHHAL_HW_MFC_KEYA or #PHHAL_HW_MFC_KEYB */
		uint8_t * pKey,      /**< [In] Key to be used in authentication. */
		uint8_t * pUid       /**< [In] Serial number of current cascade level; uint8_t[4]. */
		);

	/**
	* \brief Set configuration parameter.
	*
	* phhalHw_SamAV2 <em>Special Behaviour:</em>\n
	* In NonX-Mode every setting (except PHHAL_HW_CONFIG_DISABLE_MF_CRYPTO1 and PHHAL_HW_SAMAV2_CONFIG_HOSTMODE)\n
	* is passed on to the linked Reader-HAL.
	*
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval #PH_ERR_UNSUPPORTED_PARAMETER Configuration is not supported or invalid.
	* \retval #PH_ERR_INVALID_PARAMETER Parameter value is invalid.
	* \retval #PH_ERR_PARAMETER_OVERFLOW Setting the parameter value would lead to an overflow.
	* \retval #PH_ERR_INTERFACE_ERROR Communication error.
	*/
	phStatus_t phhalHw_SetConfig(
		void * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
		uint16_t wConfig,      /**< [In] Configuration Identifier. */
		uint16_t wValue        /**< [In] Configuration Value. */
		);

	/**
	* \brief Get configuration parameter.
	*
	* phhalHw_SamAV2 <em>Special Behaviour:</em>\n
	* In NonX-Mode every query (except #PHHAL_HW_CONFIG_RXLASTBITS, PHHAL_HW_CONFIG_DISABLE_MF_CRYPTO1 and PHHAL_HW_SAMAV2_CONFIG_HOSTMODE)\n
	* is passed on to the linked Reader-HAL.
	*
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval #PH_ERR_UNSUPPORTED_PARAMETER Configuration is not supported or invalid.
	* \retval #PH_ERR_INVALID_PARAMETER Parameter value is invalid.
	* \retval #PH_ERR_PARAMETER_OVERFLOW The parameter value is larger than the range of \b pValue.
	* \retval #PH_ERR_INTERFACE_ERROR Communication error.
	*/
	phStatus_t phhalHw_GetConfig(
		void * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
		uint16_t wConfig,      /**< [In] Configuration Identifier. */
		uint16_t * pValue      /**< [Out] Configuration Value. */
		);

	/**
	* \brief Switch on the RF-field.
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval #PH_ERR_INTERFACE_ERROR Communication error.
	*/
	phStatus_t phhalHw_FieldOn(
		void * pDataParams   /**< [In] Pointer to this layer's parameter structure. */
		);

	/**
	* \brief Switch off the RF-field.
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval #PH_ERR_INTERFACE_ERROR Communication error.
	*/
	phStatus_t phhalHw_FieldOff(
		void * pDataParams  /**< [In] Pointer to this layer's parameter structure. */
		);

	/**
	* \brief Perform RF-Reset.
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval #PH_ERR_INTERFACE_ERROR Communication error.
	*/
	phStatus_t phhalHw_FieldReset(
		void * pDataParams    /**< [In] Pointer to this layer's parameter structure. */
		);
	/**
	* \brief Blocks until the time given by \b wTimeout elapsed.
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval #PH_ERR_INVALID_PARAMETER \b bUnit is invalid.
	* \retval #PH_ERR_INTERFACE_ERROR Communication error.
	*/
	phStatus_t phhalHw_Wait(
		void * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
		uint8_t bUnit,      /**< [In] Unit of given timeout value (either #PHHAL_HW_TIME_MICROSECONDS or #PHHAL_HW_TIME_MILLISECONDS). */
		uint16_t wTimeout   /**< [In] Timeout value. */
		);

	/** @} */
#endif /* NXPBUILD__PHHAL_HW */

#ifdef __cplusplus
} /* Extern C */
#endif

#endif /* PHHALHW_H */
