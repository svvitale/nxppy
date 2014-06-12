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
* Rd710 specific HAL-Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:27:18 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHHALHW_RD710_CMD_H
#define PHHALHW_RD710_CMD_H

#include <ph_Status.h>
#include "phhalHw.h"

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/** \defgroup phhalHw_Rd710_Cmd Commands
* \brief Supported Reader commands.
* @{
*/

/**
* \brief The function starts the reader in direct PCSC mode and initializes the following stack components: 
HAL, I14443P3A, I14443P4A, I14443P4, MIFARE, CID and KEYSTORE.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_InitReader(
                                        phhalHw_Rd710_DataParams_t * pDataParams    /**< [In] Pointer to an initialized HAL parameter structure. */
                                        );

/**
* \brief The function turns-off the LEDs of the reader device.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_RD_LedOff(
                                       phhalHw_Rd710_DataParams_t * pDataParams,    /**< [In] Pointer to an initialized HAL parameter structure. */
                                       uint8_t bLeds                                /**< [In] Bitmap of the LEDs to be swichted OFF, 1=switch-off, 0=don't change. */
                                       );
/**
* \brief The function turns-on the LEDs of the reader device. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_RD_LedOn( 
                                      phhalHw_Rd710_DataParams_t * pDataParams, /**< [In] Pointer to an initialized HAL parameter structure. */
                                      uint8_t bLeds                             /**< [In] Bitmap of the LEDs to be swichted ON, 1=switch-on, 0=don't change. */
                                      );
/**
* \brief The function resets the reader IC.
* \retval #PH_ERR_SUCCESS Command successfully executed.	
*/
phStatus_t phhalHw_Rd710_Cmd_RD_ResetReader( 
    phhalHw_Rd710_DataParams_t * pDataParams    /**< [In] Pointer to an initialized HAL parameter structure. */
    );
/**
* \brief The function overwrites the current user configuration with factory defaults.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_RD_ResetFactoryDefaults( 
    phhalHw_Rd710_DataParams_t * pDataParams    /**< [In] Pointer to an initialized HAL parameter structure. */
    );
/**
* \brief The function writes data for a configuration option in the NVM of the reader.
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_RD_SetConfigOption(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * pConfig,                          /**< [In] Pointer to a 4-byte buffer holding the ID of a configuration option. */
    uint8_t * pData,                            /**< [In] Pointer to buffer holding the configuration data that shall be written. */
    uint16_t wDataLength                        /**< [In] Length of the configuration data */
    );

/**
* \brief The function reads a configuration option from the reader's NVM 
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_RD_GetConfigOption( 
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * pConfig,                          /**< [In] Pointer to a 4-byte buffer holding the ID of a configuration option. */
    uint8_t * pData,                            /**< [Out] Pointer to buffer holding the read-out data corresponding to the configuration ID. */
    uint16_t * pDataLength                      /**< [Out] Length of the read configuration data. */
    );
/**
* \brief The function outputs the current reader status.
*  The first byte in the reader response buffer is type of the reader chip, the second byte is the current state of DIP switches.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_RD_GetReaderStatus( 
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * pReaderStatus                     /**< [Out] Pointer to a buffer holding the reader response. */
    );
/**
* \brief The function sets the reader PCSC mode to standard or direct.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_RD_SetPcscMode(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t Mode                                /**< [In] The PCSC mode to be set: 0 for standard or 1 for direct. */
    );

/**
* \brief The function performs contact card activation procedure according to ISO7816-3 and 
when successful outputs the returned ATR.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_CC_Activate( 
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * pAtr,                             /**< [Out] Pointer to a buffer holding the returned ATR string from the contact card. */
    uint16_t * pAtrLen                          /**< [Out] Pointer to a buffer where the length of the returned ATR string shall be saved. */
    );

/**
* \brief The function performs contact card cold reset.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_CC_ColdReset( 
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * pAtr,                             /**< [Out] Pointer to a buffer holding the returned ATR string from the contact card. */
    uint16_t * pAtrLen                          /**< [Out] Pointer to a buffer where the length of the returned ATR string shall be saved. */
    );

/**
* \brief The function performs contact card warm reset.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_CC_WarmReset( 
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * pAtr,                             /**< [Out] Pointer to a buffer holding the returned ATR string from the contact card. */
    uint16_t * pAtrLen                          /**< [Out] Pointer to a buffer where the length of the returned ATR string shall be saved. */
    );

/**
* \brief The function stops the clock of the contact card interface.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_CC_StopClock(									
    phhalHw_Rd710_DataParams_t * pDataParams    /**< [In] Pointer to an initialized HAL parameter structure. */
    );

/**
* \brief The function starts the clock pulse of the contact card interface.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_CC_StartClock( 
    phhalHw_Rd710_DataParams_t * pDataParams    /**< [In] Pointer to an initialized HAL parameter structure. */
    );

/**
* \brief The function deactivates the card connected to the contact inteface.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_CC_Deactivate( 
    phhalHw_Rd710_DataParams_t * pDataParams    /**< [In] Pointer to an initialized HAL parameter structure. */
    );
/**
* \brief The function checks if a card is present at the contact inteface.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_CC_PresenceCheck( 
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * pCardInserted                     /**< [Out] Pointer to a byte variable indicating if a card is present(0x01) or not present(0x00). */
    );

/**
* \brief The function transmits data with the indicated length to a contact card. The response data and its length is
stored at the pointed addresses.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_CC_TransmitData( 
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * pTxBuffer,                        /**< [In] Pointer to a buffer with data to be transmitted over the contact interface. */
    uint16_t wTxLength,                         /**< [In] Length of the transmit data. */
    uint8_t ** ppRxBuffer,                      /**< [Out] Pointer to pointer to a buffer where the received data from the contact card shall be stored. */
    uint16_t * pRxLength                        /**< [Out] Pointer to a buffer where the received data length shall be stored. */
    );

/**
* \brief The function performs protocol and parameter exchange(PPS) with a contact card according to ISO7816-3.
* Note that the PPSS identifier byte, having value 0xff is not included in the <em>pPPS</em> buffer. The first byte in the pPPS buffer, i.e. <em>pPPS[0]</em> is PPS0.
In case of set exchange speed <em>bOption=0x01</em>, the first byte in the pPPS buffer, i.e. <em>pPPS[0]</em> indicates the transmission factors Fi[b7-b4],Di[b3-b0]. 
Supported are the following values:
* \li 0x12,  etu=186
* \li 0x13,  etu=93
* \li 0x18,  etu=31  speed 145.161 bit/s
* \li 0x95,  etu=32
* \li 0x96,  etu=16 - speed 281.250 bit/s

* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_CC_SendPPS( 
                                        phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
                                        uint8_t bOption,                            /**< [in] 0x00=Perform PPS, 0x01=Set only the exchange speed. */
                                        uint8_t * pPPS,                             /**< [In] Pointer to a buffer holding valid PPS exchange data. The presence of the optional bytes, respectively the length the PPS message is indicated by pPPS[0] */
                                        uint8_t * pRxBuffer                         /**< [Out] Pointer to a buffer where the received data from the contact card shall be stored. */
                                        );
/**
* \brief The function resets to 0 all key versions and their corresponding key values for the indicated key <em>wKeyNo</em>.
The key type, which is valid for all key versions of <em>wKeyNo</em> is initialized through this function to the specified <em>wNewKeyType</em>.

* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_INVALID_PARAMETER The key number <em>wKeyNo</em> is beyond the available or <em>wNewKeyType</em> is not among the predefined types. 
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_KS_FormatKeyEntry(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
    uint16_t wKeyNo,                            /**< [In] Key number of the key, which has to be formated [0-15]. */
    uint16_t wNewKeyType                        /**< [In] Key type of the key (predefined type).*/ 
    );

/**
* \brief The function initializes a new version of the indicated <em>wKeyNo</em>, having key type <em>wKeyType</em>.
Note that the key type is not set here, but this done by the <em>phhalHw_Rd710_Cmd_KS_FormatKeyEntry</em> function. 
All key versions of <em>wKeyNo</em> are searched for the indicated <em>wKeyVersion</em> and when found it gets overwritten together with its key data 
by the new version and data. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_INVALID_PARAMETER Key type <em>wKeyType</em> mismatches with current key type for the indicated <em>wKeyNo</em>. 
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_KS_SetKey(
                                       phhalHw_Rd710_DataParams_t * pDataParams,    /**< [In] Pointer to an initialized HAL parameter structure. */
                                       uint16_t wKeyType,                           /**< [In] Key type of the key which has to be initialized. */	
                                       uint16_t wKeyNo,                             /**< [In] Key number of the key, which has to be initialized [0-15]. */
                                       uint16_t wKeyVersion,                        /**< [In] Key version of the key, which has to be initialized. */
                                       uint16_t wNewKeyVersion,                     /**< [In] New key version for the indicated key number */
                                       uint16_t wNewKeyLen,                         /**< [In] Length of the new key */
                                       uint8_t* pNewKey                             /**< [In] Pointer to a buffer holding the new key data for the indicated key number and version. */
                                       );

/**
* \brief The function initializes a new version of the indicated <em>wKeyNo</em>, having key type <em>wKeyType</em>.
Note that the key type is not set here, but this is done by the <em>phhalHw_Rd710_Cmd_KS_FormatKeyEntry</em> function. 
The key version at position <em>wPos</em> gets overwritten togther with its key data by the new version and data. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_INVALID_PARAMETER Key type <em>wKeyType</em> mismatches with current key type for the indicated <em>wKeyNo</em>. 
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_KS_SetKeyAtPos(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
    uint16_t wKeyType,                          /**< [In] Key type of the key, which has to be initialized. */	
    uint16_t wKeyNo,                            /**< [In] Key number of the key, which has to be initialized [0-15]. */
    uint16_t wNewKeyVersion,                    /**< [In] New key version for the indicated key number */
    uint16_t wPos,                              /**< [In] Position of the key version for the indicated key */
    uint16_t wKeyLen,                           /**< [In] Length of the new key data. */	
    uint8_t * pNewKey                           /**< [In] Pointer to a buffer holding the new key data for the indicated key number and version. */	
    );

/**
* \brief The function changes the key usage counter(KUC) pertaing to a key number <em>wKeyNo</em> to the specified value <em>wRefNoKUC</em>.
The current KUC gets overwritten with the indicated value.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_INVALID_PARAMETER Invalid KUC entry 
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_KS_SetKUC(
                                       phhalHw_Rd710_DataParams_t * pDataParams,    /**< [In] Pointer to an initialized HAL parameter structure. */
                                       uint16_t wKeyNo,                             /**< [In] Key number of the key, which has to be [0-15]. */
                                       uint16_t wRefNoKUC                           /**< [In] Key usage counter(KUC) value for the indicated key <em>wKeyNo</em>*/   
                                       );

/**
* \brief The function initializes all key versions and the corresponding key data for the indicated key <em>wKeyNo</em>.
The key usage couter(KUC) and the key type are set equal to the specified values. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_INVALID_PARAMETER Key type <em>wNewKeyType</em> is not among the specified or invalid <em>wKeyNo</em> ,<em>wNoOfKeys</em>.
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_KS_SetFullKeyEntry(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
    uint16_t wNoOfKeys,                         /**< [In] Number of keys versions in <em>pNewKeys</em> buffer. */
    uint16_t wNewKeyType,                       /**< [In] Key type to be initialized */	
    uint16_t wKeyNo,                            /**< [In] Key number of the key to be initialized. */
    uint16_t wNewRefNoKUC,                      /**< [In] Key usage counter(KUC) value for the indicated key. */	
    uint16_t wSingleKeyLen,                     /**< [In] Length of a single key */
    uint8_t * pNewKeys,                         /**< [In] Pointer to array of key entries to load. The order of the key-data entriey corresponds to the order of the version numbers in <em>pNewKeyVersionList</em>. */
    uint16_t * pNewKeyVersionList               /**< [In] Pointer to key version list of the key to be loaded. */
    );

/**
* \brief The function retrieves the key type and the available key versions of the indicated key.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Key version buffer size <em>wKeyVersionBufSize</em> is smaller than the received data <em>wKeyVersionLength</em>.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_KS_GetKeyEntry(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
    uint16_t wKeyNo,                            /**< [In] Key number of the key, whose version data is retrieved. */
    uint16_t wKeyVersionBufSize,                /**< [In] Size of the key versions buffer <em>wKeyVersion</em>. */
    uint16_t * wKeyVersion,                     /**< [Out] Pointer to a byffer where the key versions shall be stored. */
    uint16_t * wKeyVersionLength,               /**< [Out] Pointer to a variable holding the number of the retrieved key versions. */
    uint16_t * pKeyType                         /**< [Out] Pointer to a variable that shall store the key type of the retrived key. */	
    );

/**
* \brief The function retrieves the key type and the available key versions of the indicated key.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Key buffer size <em>bKeyBufSize</em> is smaller than the received key data.
* \retval #PH_ERR_INVALID_PARAMETER The buffer size <em>bKeyBufSize</em> is not enough to receive all key data of the specified type. 
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_KS_GetKey(
                                       phhalHw_Rd710_DataParams_t * pDataParams,    /**< [In] Pointer to an initialized HAL parameter structure. */   
                                       uint16_t wKeyNo,                             /**< [In] Key number of the key whose data is retrieved. */
                                       uint16_t wKeyVersion,                        /**< [In] Key version of the key which has to be retrieved. */
                                       uint8_t bKeyBufSize,                         /**< [In] Size of the key buffer <em>pKey</em>. */
                                       uint8_t * pKey,                              /**< [Out] Pointer to a buffer receiving the key data for the indicated key number and version. */
                                       uint16_t * pKeyType                          /**< [Out] Pointer to a variable that shall store the key type of the retrived key. */	
                                       );

/**
* \brief This function is void.
* \return Status code
* \retval #PH_ERR_UNSUPPORTED_PARAMETER Always
*/
phStatus_t phhalHw_Rd710_Cmd_KS_SetConfig(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
    uint16_t wConfig,                           /**< [In] Dummy */
    uint16_t wValue                             /**< [In] Dummy */
    );

/**
* \brief This function is not implemented in P2 FW v100
* \return Status code
* \retval #PH_ERR_UNSUPPORTED_PARAMETER Always
*/
phStatus_t phhalHw_Rd710_Cmd_KS_SetConfigStr(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
    uint16_t wConfig,                           /**< [In] Dummy */
    uint8_t *pBuffer,                           /**< [In] Dummy */
    uint16_t wBufferLength                      /**< [In] Dummy */
    );

/**
* \brief This function is not implemented in P2 FW v100
* \return Status code
* \retval #PH_ERR_UNSUPPORTED_PARAMETER Always
*/
phStatus_t phhalHw_Rd710_Cmd_KS_GetConfig(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
    uint16_t wConfig,                           /**< [In] Confog Id */
    uint16_t * pValue                           /**< [In] Value */
    );
/**
* \brief This function is void.
* \return Status code
* \retval #PH_ERR_UNSUPPORTED_PARAMETER Always
*/
phStatus_t phhalHw_Rd710_Cmd_KS_GetConfigStr(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
    uint16_t wConfig,                           /**< [In] Dummy */
    uint8_t ** ppBuffer,                        /**< [In] Dummy */
    uint16_t * pBufferLength                    /**< [In] Dummy */
    );

/**
* \brief The function initalizes the indicated key usage counter(KUC) with a limit value <em>dwLimit</em>. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_INVALID_PARAMETER The indicated key usage counter number is beyond the limits of the available KUCs.
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_KS_ChangeKUC(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */                  
    uint16_t wRefNoKUC,                         /**< [In] Reference number of the key usage counter. */
    uint32_t dwLimit                            /**< [In] Limit of the key usage counter(KUC). */
    );


/**
* \brief The function retrieves the indicated key usage counter(KUC) and stores its limit and current values at the indicated <em>dwLimit</em> and <em>pdwCurVal</em> respectively. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_INVALID_PARAMETER The indicate key usage counter number is beyond the limits of the available KUCs.
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_KS_GetKUC(
                                       phhalHw_Rd710_DataParams_t * pDataParams,    /**< [In] Pointer to an initialized HAL parameter structure. */
                                       uint16_t wRefNoKUC,                          /**< [In] Reference number of the key usage counter. */
                                       uint32_t * pdwLimit,                         /**< [Out] Pointer to received limit of key usage counter. */
                                       uint32_t * pdwCurVal                         /**< [Out] Pointer to received current key usage counter. */
                                       );
/**
* \brief The function returns a free CID for communication with ISO14443-4 card.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_CID_GetFreeCid(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * pCid                              /**< [Out] Pointer to a byte variable where the returned CID value shall be stored. */
    );
/**
* \brief The function frees the indicated CID.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_CID_FreeCid(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t bCid                                /**< [In] CID to be disposed. */
    );
/**
* \brief The function intializes the ISO14443-4 protocol parameters.
* It is recommended to input this function with the parameters retrieved from either
* <em>phpalI14443p4a_GetProtocolParams</em> or <em>phpalI14443p3b_GetProtocolParams</em> after card activation.
* \b Note: Refer to the ISO/IEC 14443-4:2008(E) specification for a detailed description of the parameters.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_I14443P4_SetProtocol(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t bCidEnable,                         /**< [In] CID is enabled if not equal to 0, otherwise it is disabled. */
    uint8_t bCid,                               /**< [In] Card identifier(CID). Ignored if <em>bCidEnable</em> is equal to '0'. */
    uint8_t bNadEnable,                         /**< [In] NAD is enabled if not equal to 0, otherwise it is disabled. */
    uint8_t bNad,                               /**< [In] Node addrss(NAD). Ignored if <em>bNadEnabled</em> is equal 0. */
    uint8_t bFwi,                               /**< [In] Frame waiting time integer. */
    uint8_t bFsdi,                              /**< [In] PCD Frame size PCD integer; 0-8 */
    uint8_t bFsci                               /**< [In] PICC Frame size PICC integer; 0-8 */
    );

/**
* \brief The function resets the ISO14443-4 protocol parameters.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_I14443P4_ResetProtocol(
    phhalHw_Rd710_DataParams_t * pDataParams    /**< [In] Pointer to this layer's parameter structure. */
    );

/**
* \brief The function executes DESELECT command in S-Block PCB in order to deactivate a PICC 
according to ISO14443-4 specification. The function can also be applied for transmission and protocol error recovery.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_I14443P4_Deselect(
    phhalHw_Rd710_DataParams_t * pDataParams    /**< [In] Pointer to this layer's parameter structure. */
    );

/**
* \brief The function performs presence check for current PICC 
through R(NAK) polling. It forces the PICC to response with R(ACK) and consecutive last I-block retransmission, as defined in ISO 14443-4:2008(E) scenario 6.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_I14443P4_PresCheck(
    phhalHw_Rd710_DataParams_t * pDataParams    /**< [In] Pointer to this layer's parameter structure. */
    );

/**
* \brief The function performs ISO14443-4 data exchange with PICC. <em>wOption</em> can be one of:
* \li #PH_EXCHANGE_DEFAULT
* \li #PH_EXCHANGE_TXCHAINING
* \li #PH_EXCHANGE_RXCHAINING
* \li #PH_EXCHANGE_RXCHAINING_BUFSIZE
*
<em>wOption</em> can be combined with:
* \li #PH_EXCHANGE_BUFFERED_BIT
*
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_I14443P4_Exchange(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint16_t wOption,                           /**< [In] Option parameter. */
    uint8_t * pTxBuffer,                        /**< [In] Pointer to a buffer with transmit data. */
    uint16_t wTxLength,                         /**< [In] Length of transmit data. */
    uint8_t ** ppRxBuffer,                      /**< [Out] Pointer to pointer of buffer holding the received data. */
    uint16_t * pRxLength                        /**< [Out] Number of received data bytes. */
    );

/**
* \brief The function sets a configuration parameter to a indicated value. The configuration parameter can have following identiferes:
*
* \li PHPAL_I14443P4_PARAM_BLOCKNO			0x0000
* \li PHPAL_I14443P4_PARAM_CID				0x0001	
* \li PHPAL_I14443P4_PARAM_NAD				0x0002
* \li PHPAL_I14443P4_PARAM_FWI				0x0003
* \li PHPAL_I14443P4_PARAM_FSI				0x0004
* \li PHPAL_I14443P4_PARAM_MAXRETRYCOUNT	0x0005

* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_INVALID_PARAMETER Invalid CID or ivalid FWI or invalid FSI or invalid configuration identifier.
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_I14443P4_SetConfig(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint16_t wConfig,                           /**< [In] Configuration identifier */
    uint16_t wValue                             /**< [In] Configuration value */
    );

/**
* \brief The function retrieves a configuration parameter.The configuration parameter can have following identiferes:
*
* \li PHPAL_I14443P4_PARAM_BLOCKNO			0x0000
* \li PHPAL_I14443P4_PARAM_CID				0x0001	
* \li PHPAL_I14443P4_PARAM_NAD				0x0002
* \li PHPAL_I14443P4_PARAM_FWI				0x0003
* \li PHPAL_I14443P4_PARAM_FSI				0x0004
* \li PHPAL_I14443P4_PARAM_MAXRETRYCOUNT	0x0005
*
* \n
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_INVALID_PARAMETER Invalid configuration identifier.
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_I14443P4_GetConfig(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint16_t wConfig,                           /**< [In] Configuration identifier */
    uint16_t * pValue                           /**< [Out] Pointer to a variable where the configuration value shall be stored. */
    );


/**
* \brief The function performs the "Request Answer to Select" command according to ISO14443-4A.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_I14443P4A_Rats(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t bFsdi,                              /**< [In] Frame Size Integer, 0-8 */
    uint8_t bCid,                               /**< [In] Card Identifier, 0-14 */
    uint8_t * pAts                              /**< [Out]Pointer to a buffer that shall store the received ATS. */
    );

/**
* \brief The function performs the "Protocol and Parameter Selection" procedure according to ISO14443-4A.
* The following values for <em>bDri</em> and <em>bDsi</em> are possible:\n
* \li #PHPAL_I14443P4A_DATARATE_106
* \li #PHPAL_I14443P4A_DATARATE_212
* \li #PHPAL_I14443P4A_DATARATE_424
* \li #PHPAL_I14443P4A_DATARATE_848
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_I14443P4A_Pps(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t bDri,                               /**< [In] Divisor Receive (PCD to PICC) Integer; 0-3 */
    uint8_t bDsi                                /**< [In] Divisor Send (PICC to PCD) Integer; 0-3 */
    );


/**
* \brief The function performs ISO14443-4A RATS and PPS commands.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_I14443P4A_ActivateCard(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t bFsdi,                              /**< [In] Frame Size Integer, 0-8 */
    uint8_t bCid,                               /**< [In] Card Identifier, 0-14 */
    uint8_t bDri,                               /**< [In] Divisor receive PCD to PICC integer, 0-3 */
    uint8_t bDsi,                               /**< [In] Divisor send PICC to PCD integer, 0-3 */
    uint8_t * pAts                              /**< [Out]Pointer to a buffer storing the received ATS. */
    );

/**
* \brief The function retrieves the ISO14443-4A protocol parameters.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_I14443P4A_GetProtocolParams(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t * pCidEnabled,                      /**< [Out] Pointer to storage for CID enabled variable. */
    uint8_t * pCid,                             /**< [Out] Pointer to storage for CID. */
    uint8_t * pNadSupported,                    /**< [Out] Pointer to storage for NAD enabled variable. */
    uint8_t * pFwi,                             /**< [Out] Pointer to storage for FWI. */
    uint8_t * pFsdi,                            /**< [Out] Pointer to a storage for FSDI. */
    uint8_t * pFsci                             /**< [Out] Pointer to a storage for FSCI. */
    );


/**
* \brief The function performs the "Request" command according to ISO14443-3A.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_I14443P3A_RequestA(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t * pAtqa                             /**< [Out]Pointer to a buffer storing the received ATS. */
    );

/**
* \brief The function performs the "Wakeup" command according to ISO14443-3A.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_I14443P3A_WakeUpA(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t * pAtqa                             /**< [Out] Pointer to a buffer storing the AtqA. */
    );



/**
* \brief The function performs the ISO14443-3A "Halt" command.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_I14443P3A_HaltA(
    phhalHw_Rd710_DataParams_t * pDataParams    /**< [In] Pointer to this layer's parameter structure. */
    );


/**
* \brief The function perform a ISO14443-3A Anticollision or Select command.
* <em>bNvbUidIn</em> != 0x40: Perform Anticollision command.\n
* <em>bNvbUidIn</em>  = 0x40: Perform Select command.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_I14443P3A_Anticollision(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t bCascadeLevel,                      /**< [In] Cascade level code.  */
    uint8_t * pUidIn,                           /**< [In] Known UID, can also be NULL. */
    uint8_t bNvbUidIn,                          /**< [In] Number of valid bits of <em>UidIn</em>. MSB codes the valid bytes, LSB codes the valid bits.  */
    uint8_t * pUidOut,                          /**< [Out] Pointer to the complete UID. */
    uint8_t * pNvbUidOut                        /**< [Out] Pointer to number of valid bits of <em>UidOut</em>. MSB codes the valid bytes, LSB codes the valid bits.  */
    );

/**
* \brief The function performs a ISO14443-3A "Select" command.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_I14443P3A_Select(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t bCascadeLevel,                      /**< [In] Cascade level code. */
    uint8_t * pUidIn,                           /**< [In] Pointer to UID.  */
    uint8_t * pSak                              /**< [Out] Pointer to select acknowledge; uint8_t. */
    );


/**
* \brief The function performs ISO14443-3A "ReqA" or "WupA" and "Anticollision"/"Select" commands for all cascade levels.
* If <em>bLenUidIn</em> is equal to '0', CardUid not given, a ReqA command is performed.
* If CardUid is given, a WupA is performed.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_I14443P3A_ActivateCard(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t * pUidIn,                           /**< [In] Known UID, can be NULL if <em>bLenUidIn</em> is 0. */
    uint8_t bLenUidIn,                          /**< [In] Length of known UID. */
    uint8_t * pUidOut,                          /**< [Out] Pointer to Complete UID. */
    uint8_t * pLenUidOut,                       /**< [Out] Pointer to Length of UID. */
    uint8_t * pSak,                             /**< [Out] Pointer to  Select Acknowledge. */
    uint8_t * pMoreCardsAvailable               /**< [Out] Pointer to a variable indicating whether more cards are in the HF or not. */
    );

/**
* \brief The function performs data exchange with PICC according to ISO14443-3A. 
* \c <em>wOption</em> can be one of:
*
* \li #PH_EXCHANGE_DEFAULT 
*
* \c <em>wOption</em> can be combined with:
*
* \li #PH_EXCHANGE_BUFFERED_BIT
*
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_I14443P3A_Exchange(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint16_t wOption,                           /**< [In] Option parameter. */
    uint8_t * pTxBuffer,                        /**< [In] Pointer to a buffer holding the transmit data. */
    uint16_t wTxLength,                         /**< [In] Length of data to transmit. */ 
    uint8_t ** ppRxBuffer,                      /**< [Out] Pointer to pointer to the received data buffer. */ 
    uint16_t * pRxLength                        /**< [Out] Pointer to the number of the received data bytes. */
    );

/**
* \brief The function petrieves the serial number of the indicated PICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_I14443P3A_GetSerialNo(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t * pRxBuffer,                        /**< [Out] Pointer to the last UID. */
    uint8_t * pRxLength                         /**< [Out] Pointer to the length of UID. */
    );


/**
* \brief The function performs ISO14443-3 data exchange with MIFARE PICC.
* \c <em>wOption</em> can be one of:
*
* \li #PH_EXCHANGE_DEFAULT
*
* \c <em>wOption</em> can be combined with:
*
* \li #PH_EXCHANGE_BUFFERED_BIT
*
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_MIFARE_ExchangeL3(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint16_t wOption,                           /**< [In] Option parameter. */
    uint8_t * pTxBuffer,                        /**< [In] Pointer to a buffer holding the transmit data. */
    uint16_t wTxLength,                         /**< [In] Length of data to transmit. */
    uint8_t ** ppRxBuffer,                      /**< [Out] Pointer to pointer to the received data buffer. */ 
    uint16_t * pRxLength                        /**< [Out] Pointer to the number of the received data bytes. */
    );


/**
* \brief The function performs ISO14443-4 data exchange with MIFARE PICC.
* \c <em>wOption</em> can be one of:
*
* \li #PH_EXCHANGE_DEFAULT
* \li #PH_EXCHANGE_TXCHAINING
* \li #PH_EXCHANGE_RXCHAINING
* \li #PH_EXCHANGE_RXCHAINING_BUFSIZE
*
* \c <em>wOption</em> can be combined with:\n
*
* \li #PH_EXCHANGE_BUFFERED_BIT
*
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_MIFARE_ExchangeL4(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint16_t wOption,                           /**< [In] Option parameter. */
    uint8_t * pTxBuffer,                        /**< [In] Pointer to a buffer holding the transmit data. */
    uint16_t wTxLength,                         /**< [In] Length of data to transmit. */
    uint8_t ** ppRxBuffer,                      /**< [Out] Pointer to pointer to the received data buffer. */ 
    uint16_t * pRxLength                        /**< [Out] Pointer to the number of the received data bytes. */
    );


/**
* \brief The function performs proximity-check data exchange with MIFARE Picc.
* \b Note: The \c wOption parameter is currently RFU.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_MIFARE_ExchangePc(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint16_t wOption,                           /**< [In] Option parameter. */
    uint8_t * pTxBuffer,                        /**< [In] Pointer to a buffer holding the transmit data. */
    uint16_t wTxLength,                         /**< [In] Length of data to transmit. */
    uint8_t ** ppRxBuffer,                      /**< [Out] Pointer to pointer to the received data buffer. */ 
    uint16_t * pRxLength                        /**< [Out] Pointer to the number of the received data bytes. */
    );


/**
* \brief The function performs raw data exchange with MIFARE PICC. No CRC or parity bytes are transferred to PICC.
* \c <em>wOption</em> can be one of:
*
* \li #PH_EXCHANGE_DEFAULT
*
* \c <em>wOption</em> can be combined with:
*
* \li #PH_EXCHANGE_BUFFERED_BIT
*
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_MIFARE_ExchangeRaw(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint16_t wOption,                           /**< [In] Option parameter. */
    uint8_t * pTxBuffer,                        /**< [In] Pointer to a buffer holding the transmit data. */
    uint16_t wTxLength,                         /**< [In] Length of the transmit data. */
    uint8_t bTxLastBits,                        /**< [In] Number of valid bits of last byte in the transmit buffer. */
    uint8_t ** ppRxBuffer,                      /**< [Out] Pointer to pointer to the received data buffer. */ 
    uint16_t * pRxLength,                       /**< [Out] Pointer to the number of the received data bytes. */
    uint8_t * pRxLastBits                       /**< [Out] Number of valid bits of last byte in the receive buffer. */
    );

/**
* \brief The function performs MIFARE "Authenticate" command with PICC using a key number.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_MIFARE_MfcAuthenticateKeyNo(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t bBlockNo,                           /**< [In] Block number whithin a card sector that shall be authenticated. */
    uint8_t bKeyType,                           /**< [In] Either #PHPAL_MIFARE_KEYA or #PHPAL_MIFARE_KEYB */
    uint16_t wKeyNo,                            /**< [In] Key number to be used in authentication. */
    uint16_t wKeyVersion,                       /**< [In] Key version to be used in authentication. */
    uint8_t * pUid                              /**< [In] Serial number of current cascade level; uint8_t[4]. */
    );

/**
* \brief The function performs MIFARE "Authenticate" command with PICC using a key.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed.	
* \retval #PH_ERR_BUFFER_OVERFLOW Transimit data length is longer than the allocated transmit buffer size.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid frame or unexpected receive data length or command code mismatch.
* \retval Other Status word returned from the reader after the exchange function.
*/
phStatus_t phhalHw_Rd710_Cmd_MIFARE_MfcAuthenticate(
    phhalHw_Rd710_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t bBlockNo,                           /**< [In] Block number whithin a card sector that shall be authenticated. */
    uint8_t bKeyType,                           /**< [In] Either #PHPAL_MIFARE_KEYA or #PHPAL_MIFARE_KEYB */
    uint8_t * pKey,                             /**< [In] Key to be used in authentication. */
    uint8_t * pUid                              /**< [In] Serial number of current cascade level; uint8_t[4]. */
    );

/** @}
* end of phhalHw_Rd710_Cmd group
*/

#ifdef __cplusplus
} /* Extern C */
#endif

#endif /* PHHALHW_RD710_CMD_H */
