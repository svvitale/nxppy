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
* Generic ISO18092 passive initiator mode Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.1 $
* $Date: Fri Apr 15 09:29:04 2011 $
*
* History:
*  CEn: Generated 07. September 2010
*/

#ifndef PHPALI18092MPI_H
#define PHPALI18092MPI_H

#include <ph_Status.h>
#include <phhalHw.h>

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#ifdef NXPBUILD__PHPAL_I18092MPI_SW

/** \defgroup phpalI18092mPI_Sw Component : Software
* @{
*/

#define PHPAL_I18092MPI_SW_ID            0x01U /**< ID for Software ISO18092 layer. */

#define PHPAL_I18092MPI_NFCID3_LENGTH    0x0AU /**< Length of NFCID3. */

/**
* \brief ISO18092 mode passive initiator parameter structure
*/
typedef struct
{
    uint16_t wId;                                       /**< Layer ID for this component, NEVER MODIFY! */
    void * pHalDataParams;                              /**< Pointer to the parameter structure of the underlying layer. */
    uint8_t bNfcIdValid;                                /**< Whether current NfcID is valid or not. */
    uint8_t aNfcid3i[PHPAL_I18092MPI_NFCID3_LENGTH];    /**< Array holding 10 bytes long NFCID3. */
    uint8_t bStateNow;                                  /**< Current Exchange-State. */
    uint8_t bDid;                                       /**< Device Identifier; '0' to disable usage else 1-14. */
    uint8_t bNadEnabled;                                /**< Node Address Enabler; Unequal '0' if enabled. */
    uint8_t bNad;                                       /**< Node Address; Ignored if bNadEnabled is equal '0'. */
    uint8_t bWt;                                        /**< Waiting Time; 0-14 */
    uint8_t bFsl;                                       /**< Frame Length Byte; 0-3 */
    uint8_t bPni;                                       /**< Current Packet Number (Packet number information); 0-3 */
    uint8_t bDsi;                                       /**< Divisor Send (target to initiator) Integer; 0-2 */
    uint8_t bDri;                                       /**< Divisor Receive (initiator to target) Integer; 0-2 */
    uint8_t bMaxRetryCount;                             /**< Maximum retry count for retransmissions. */
} phpalI18092mPI_Sw_DataParams_t;

/**
* \brief Initialise this layer.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phpalI18092mPI_Sw_Init(
                                  phpalI18092mPI_Sw_DataParams_t * pDataParams,     /**< [In] Pointer to this layer's parameter structure. */
                                  uint16_t wSizeOfDataParams,                    /**< [In] Specifies the size of the data parameter structure. */
                                  void * pHalDataParams                          /**< [In] Pointer to the parameter structure of the underlying layer. */
                                  );

/** @} */
#endif /* NXPBUILD__PHPAL_I18092MPI_SW */

#ifdef NXPBUILD__PHPAL_I18092MPI

/** \addtogroup ph_Error
* phpalI18092 Custom Errors
* @{
*/

/** \name phpalI18092mPI Error Codes
*/
/*@{*/
#define PHPAL_I18092MPI_ERR_RECOVERY_FAILED  (PH_ERR_CUSTOM_BEGIN+0)     /**< ISO18092 error recovery failed. */
/*@}*/

/** @} */

/** \defgroup phpalI18092mPI ISO18092 Mode Passive Initiator
* \brief These Components implement the ISO/IEC ISO18092 contactless protocol. Supported mode is passive initiator, i.e.
* using these components it is possible to communicate with a passive target in peer to peer mode.
* @{
*/
#define PHPAL_I18092MPI_DID_MAX          0x0EU  /**< The last valid DID. */
#define PHPAL_I18092MPI_WT_MAX           0x0EU  /**< The maximum allowed WT value, NFCForum-TS-DigitalProtocol-1.0 section 14.11. */
#define PHPAL_I18092MPI_FSL_MAX          0x03U  /**< The maximum allowed FSL value. */
#define PHPAL_I18092MPI_PNI_MAX          0x03U  /**< The maximum allowed PNI value. */

/**
* \name ISO18092 Mode Passive Initiator Parameters
*/
/*@{*/
/**
* \brief Set / Get packet number.
*/
#define PHPAL_I18092MPI_CONFIG_PACKETNO          0x0000U
/**
* \brief Set / Get Device Identifier.
*/
#define PHPAL_I18092MPI_CONFIG_DID               0x0001U
/**
* \brief Set / Get Node Address.
*
* \c wValue is parsed as follows:
* \verbatim
* NadEnabled = (wValue & 0xFF00) ? 1 : 0;
* Nad = (wValue & 0x00FF);
* \endverbatim
*/
#define PHPAL_I18092MPI_CONFIG_NAD               0x0002U
/**
* \brief Set / Get Waiting Time.
*/
#define PHPAL_I18092MPI_CONFIG_WT                0x0003U
/**
* \brief Set / Get Frame Length.
*/
#define PHPAL_I18092MPI_CONFIG_FSL               0x0004U
/**
* \brief Set / Get Maximum Retry Count.
*/
#define PHPAL_I18092MPI_CONFIG_MAXRETRYCOUNT     0x0005U
/*@}*/

/**
* \name Values for #phpalI18092mPI_Deselect \c bDeselectCommand parameter.
*/
/*@{*/
#define PHPAL_I18092MPI_DESELECT_DSL   0x08U   /**< DSL is sent for deselection of target. */
#define PHPAL_I18092MPI_DESELECT_RLS   0x0AU   /**< RLS is sent for deselection of target. */
/*@}*/

/**
* \name DRI/DSI (BRI/BSI) Values
*/
/*@{*/
#define PHPAL_I18092MPI_DATARATE_106   0x00U   /**< DRI/DSI value for 106 kBit/s. */
#define PHPAL_I18092MPI_DATARATE_212   0x01U   /**< DRI/DSI value for 212 kBit/s. */
#define PHPAL_I18092MPI_DATARATE_424   0x02U   /**< DRI/DSI value for 424 kBit/s. */
/*@}*/

/**
* \name FSL/LRI Values
*/
/*@{*/
#define PHPAL_I18092MPI_FRAMESIZE_64   0x00U   /**< FSL value for max. framesize of 64 Bytes.  */
#define PHPAL_I18092MPI_FRAMESIZE_128  0x01U   /**< FSL value for max. framesize of 128 Bytes. */
#define PHPAL_I18092MPI_FRAMESIZE_192  0x02U   /**< FSL value for max. framesize of 192 Bytes. */
#define PHPAL_I18092MPI_FRAMESIZE_254  0x03U   /**< FSL value for max. framesize of 254 Bytes. */
/*@}*/

/**
* \name Maximum Values
*/
/*@{*/
#define PHPAL_I18092MPI_MAX_GI_LENGTH   48U /**< Maximum length of Gi data.  */
/*@}*/

/**
* \brief Reset the ISO18092 protocol parameters.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phpalI18092mPI_ResetProtocol(
                                        void * pDataParams   /**< [In] Pointer to this layer's parameter structure. */
                                        );

/**
* \brief Perform an ISO18092 "Attribute Request" command.
*
* The following values for \c bLri are possible:\n
* \li #PHPAL_I18092MPI_FRAMESIZE_64
* \li #PHPAL_I18092MPI_FRAMESIZE_128
* \li #PHPAL_I18092MPI_FRAMESIZE_192
* \li #PHPAL_I18092MPI_FRAMESIZE_254
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_PROTOCOL_ERROR Received response is not ISO/IEC 18092 compliant.
* \retval #PH_ERR_IO_TIMEOUT Timeout waiting for reply, e.g. target removal.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalI18092mPI_Atr(
                              void * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                              uint8_t * pNfcid3i,  /**< [In] NFCID3 - randomly generated in case of 106kbps initial datarate or
                                                   NFCID2 in case of 212/424kbps datarate; uint8_t[10] */
                                                   uint8_t bDid,            /**< [In] Device Identifier; '0' to disable usage else 1-14. */
                                                   uint8_t bLri,            /**< [In] Length Reduction of Initiator; 0-3  */
                                                   uint8_t bNadEnable,      /**< [In] Enable usage of Node Address; Unequal '0' to enable. */
                                                   uint8_t bNad,            /**< [In] Node Address; Ignored if bNadEnabled is equal '0'. */
                                                   uint8_t * pGi,           /**< [In] Optional General Information bytes. */
                                                   uint8_t bGiLength,       /**< [In] Number of General Information bytes; Not more than #PHPAL_I18092MPI_MAX_GI_LENGTH. */
                                                   uint8_t * pAtrRes,       /**< [Out] Attribute Response; uint8_t[64]. */
                                                   uint8_t * pAtrResLength  /**< [Out] Attribute Response Length. */
                                                   );

/**
* \brief Perform an ISO18092 "Parameter Select" command.
*
* The following values for \c bDri and \c bDsi are possible:\n
* \li #PHPAL_I18092MPI_DATARATE_106
* \li #PHPAL_I18092MPI_DATARATE_212
* \li #PHPAL_I18092MPI_DATARATE_424
*
* The following values for \c bFsl are possible:\n
* \li #PHPAL_I18092MPI_FRAMESIZE_64
* \li #PHPAL_I18092MPI_FRAMESIZE_128
* \li #PHPAL_I18092MPI_FRAMESIZE_192
* \li #PHPAL_I18092MPI_FRAMESIZE_254
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_PROTOCOL_ERROR Received response is not ISO/IEC 18092 compliant.
* \retval #PH_ERR_IO_TIMEOUT Timeout waiting for reply, e.g. target removal.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalI18092mPI_Psl(
                              void * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                              uint8_t bDsi,        /**< [In] Divisor Send (target to initiator) Integer; 0-2 */
                              uint8_t bDri,        /**< [In] Divisor Receive (initiator to target) Integer; 0-2 */
                              uint8_t bFsl         /**< [In] Frame Length Byte; 0-3  */
                              );

/**
* \brief Perform an ISO18092 ATR and PSL command.
*
* The following values for \c bDri and \c bDsi are possible:\n
* \li #PHPAL_I18092MPI_DATARATE_106
* \li #PHPAL_I18092MPI_DATARATE_212
* \li #PHPAL_I18092MPI_DATARATE_424
*
* The following values for \c bFsl are possible:\n
* \li #PHPAL_I18092MPI_FRAMESIZE_64
* \li #PHPAL_I18092MPI_FRAMESIZE_128
* \li #PHPAL_I18092MPI_FRAMESIZE_192
* \li #PHPAL_I18092MPI_FRAMESIZE_254
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful, target activated.
* \retval #PH_ERR_PROTOCOL_ERROR Received response is not ISO/IEC 18092 compliant.
* \retval #PH_ERR_IO_TIMEOUT Timeout waiting for reply, e.g. target removal.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalI18092mPI_ActivateCard(
                                       void * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                                       uint8_t * pNfcid3i,  /**< [In] NFCID3 - any number in case of 106kbps initial datarate.
                                                            For 212/424kbps datarate bytes 0 - 7 have to be NFCID2,
                                                            bytes 8 - 9 need to be set to 0; uint8_t[10] */
                                                            uint8_t bDid,           /**< [In] Device Identifier; '0' to disable usage else 1-14. */
                                                            uint8_t bNadEnable,     /**< [In] Enable usage of Node Address; Unequal '0' to enable. */
                                                            uint8_t bNad,           /**< [In] Node Address; Ignored if bNadEnabled is equal '0'. */
                                                            uint8_t bDsi,           /**< [In] Divisor Send (target to initiator) Integer; 0-7 */
                                                            uint8_t bDri,           /**< [In] Divisor Receive (initiator to target) Integer; 0-7 */
                                                            uint8_t bFsl,           /**< [In] Frame Length Byte; 0-3 */
                                                            uint8_t * pGi,          /**< [In] Optional General Information bytes. */
                                                            uint8_t bGiLength,      /**< [In] Number of General Information bytes. */
                                                            uint8_t * pAtrRes,      /**< [Out] Attribute Response; uint8_t[64]. */
                                                            uint8_t * pAtrResLength /**< [Out] Attribute Response Length. */
                                                            );

/**
* \brief Deselect ISO18092 target by either sending DSL or RLS request.
*
* The following values for \c bDeselectCommand are possible:\n
* \li #PHPAL_I18092MPI_DESELECT_DSL
* \li #PHPAL_I18092MPI_DESELECT_RLS
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful, target deselected.
* \retval #PH_ERR_PROTOCOL_ERROR Received response is not ISO/IEC 18092 compliant.
* \retval #PH_ERR_IO_TIMEOUT Timeout waiting for reply, e.g. target removal.
*/
phStatus_t phpalI18092mPI_Deselect(
                                   void * pDataParams,        /**< [In] Pointer to this layer's parameter structure. */
                                   uint8_t bDeselectCommand   /**< [In] Request to send, either #PHPAL_I18092MPI_DESELECT_DSL or #PHPAL_I18092MPI_DESELECT_RLS. */
                                   );

/**
* \brief Perform presence check for current target.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful, target is present.
* \retval #PH_ERR_PROTOCOL_ERROR Received response is not ISO/IEC 18092 compliant.
* \retval #PH_ERR_IO_TIMEOUT Timeout waiting for reply, e.g. target removal.
* \retval #PHPAL_I18092MPI_ERR_RECOVERY_FAILED Recovery failed, target does not respond any more.
*/
phStatus_t phpalI18092mPI_PresCheck(
                                    void * pDataParams   /**< [In] Pointer to this layer's parameter structure. */
                                    );

/**
* \brief Perform ISO18092 Data Exchange with target.
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
* \retval #PH_ERR_PROTOCOL_ERROR Received response is not ISO/IEC 18092 compliant.
* \retval #PH_ERR_IO_TIMEOUT Timeout waiting for reply, e.g. target removal.
* \retval #PHPAL_I18092MPI_ERR_RECOVERY_FAILED Recovery failed, target does not respond any more.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalI18092mPI_Exchange(
                                   void * pDataParams,       /**< [In] Pointer to this layer's parameter structure. */
                                   uint16_t wOption,         /**< [In] Option parameter. */
                                   uint8_t * pTxBuffer,      /**< [In] Data to transmit. */
                                   uint16_t wTxLength,       /**< [In] Length of data to transmit. */
                                   uint8_t ** ppRxBuffer,    /**< [Out] Pointer to received data. */
                                   uint16_t * pRxLength      /**< [Out] number of received data bytes. */
                                   );

/**
* \brief Set configuration parameter.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalI18092mPI_SetConfig(
                                    void * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                                    uint16_t wConfig,    /**< [In] Configuration Identifier. */
                                    uint16_t wValue      /**< [In] Configuration Value. */
                                    );

/**
* \brief Get configuration parameter.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalI18092mPI_GetConfig(
                                    void * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                                    uint16_t wConfig,    /**< [In] Configuration Identifier. */
                                    uint16_t * pValue    /**< [Out] Configuration Value. */
                                    );

/**
* \brief Retrieve the serial number (NFC ID3).
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phpalI18092mPI_GetSerialNo(
                                      void * pDataParams,     /**< [In] Pointer to this layer's parameter structure. */
                                      uint8_t * pNfcId3Out    /**< [Out] last NFCID3; uint8_t[10]. */
                                      );

/** @} */
#endif /* NXPBUILD__PHPAL_I18092MPI */

#ifdef __cplusplus
} /* Extern C */
#endif

#endif /* PHPALI18092MPI_H */
