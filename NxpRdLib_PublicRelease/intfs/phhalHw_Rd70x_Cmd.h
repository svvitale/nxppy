/*
*         Copyright (c), NXP Semiconductors Gratkorn / Austria
*
*                     (C)NXP Semiconductors
*       All rights are reserved. Reproduction in whole or in part is 
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
* particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

/** \file
* Rd70x specific HAL-Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.4 $
* $Date: Fri Apr 15 09:27:19 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHHALHW_RD70X_CMD_H
#define PHHALHW_RD70X_CMD_H

#include <ph_Status.h>
#include <phhalHw.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifdef NXPBUILD__PHHAL_HW_RD70X

/** \defgroup phhalHw_Rd70x_Cmd Commands
* \brief Supported ReaderIC commands.
* @{
*/

/**
* \brief The function performs hardware configuration of the PCD - the hardware is reset, 
send and receive buffers are intialized and basic register configuration is set. Finally the HF is also reset.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed
* \retval Other Invalid parameters or conditions - the error status is returned by the underlayed functions. If the parameters are correct the function
returns the command execution status of the PCD. The PCD command execution status is mapped to a library status codes.
*/
phStatus_t phhalHw_Rd70x_Cmd_PcdConfig(
                                       phhalHw_Rd70x_DataParams_t * pDataParams /**< [In] Pointer to an initialized HAL parameter structure. */
                                       );

/**
* \brief The function outputs the parameters after the RATS-ATS exchange: FSDI, FSCI, DR, DS, 'equal/different divisior flag'.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PcdGetAttrib(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In]  Pointer to an initialized HAL parameter structure. */
    uint8_t * FSCImax,							/**< [Out] Pointer to maximum size of a frame accepted by the PICC. */
    uint8_t * FSDImax,							/**< [Out] Pointer to maximum size of a frame accepted by the PCD. */
    uint8_t * DSsupp,							/**< [Out] Pointer to the supported baudrate divider PICC to PCD. */
    uint8_t * DRsupp,							/**< [Out] Pointer to the supported baudrate divider PCD to PICC. */
    uint8_t * DREQDS							/**< [Out] Pointer to equal/different (1/0) dividers in each direction. */
    );

/**
* \brief The function initializes the of DSI and DRI values with provided parameters.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed
* \retval #PH_ERR_INTERNAL_ERROR Invalid SDI or DRI parameter i.e. the parameter is bigger than the maximum baudrate divider supported by the PCD.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PcdSetAttrib(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t DSI,								/**< [In] PPS division integer PICC to PCD. */ 
    uint8_t DRI 								/**< [In] PPS division integer PCD to PICC. */ 
    );

/**
* \brief The function initializes the baud rate PCD->PICC to the same value as for PICC->PCD, if the serial number of the IC
is equal to the cryptogram parameter.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed
* \retval #PH_ERR_INTERNAL_ERROR Invalid parameter, the four bytes of cryptogram paramter are not equal to the PCD's serial numner.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PcdEnableHighBaudRates(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * cryptogram 						/**< [In] Pointer to a cryptogram of 4 bytes, corresponding to the serial number of the reader IC.*/
    );


/**
* \brief The function switches the PCD-PICC baud-rate to the default of 106 kB, if the last reader receive or transmit baud rate has been different from the default one.
* \return Status code
* \retval #PH_ERR_SUCCESS Command successfully executed
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PcdSetDefaultAttrib(
    phhalHw_Rd70x_DataParams_t * pDataParams	/**< [In] Pointer to an initialized HAL parameter structure. */
    );	

/**
* \brief The function initiates an ISO14443-3A short frame command-response exchange with the PICC using the provided command code - REQA or WUPA.
Two bytes of the PICC response ATQA are stored at the provided address.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. Any PICC response collision, that might happen is also considered a successful command execution. 
* \retval #PH_ERR_PROTOCOL_ERROR The PICC does not return the expected number of bytes.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_MfPiccRequest(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t req_code,							/**< [In] Command to be executed REQA or WUPA */
    uint8_t * atq								/**< [Out] Pointer to a location where two bytes of the response ATQA will be stored. */
    );

/**
* \brief The function initiates an ISO14443-3A short frame command-response exchange with the PICC using the provided command code - REQA or WUPA.
Two bytes of the PICC response ATQA are stored at the provided address. This function has an identical functionallity to phhalHw_Rd70x_Cmd_MfPiccRequest function.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. Any PICC response collision, that might happen is still a successful command execution. 
* \retval #PH_ERR_PROTOCOL_ERROR The PICC does not return the expected number of bytes.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PiccCommonRequest(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t req_code,							/**< [In] Command to be executed REQA or WUPA. */
    uint8_t * atq								/**< [Out] Pointer to a location where two bytes of the response ATQA will be stored. */
    );

/**
* \brief The function initates the first cascade level of the ISO14443-3A anticollision procedure.
The UID bytes returned by the PICC are stored at the provided address. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. In case of collision the function exits also with success. 
* \retval #PH_ERR_PROTOCOL_ERROR Inconsistent CRC
* \retval #PH_ERR_INTERNAL_ERROR Wrong parameter - number of valid bits NVB.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_MfPiccAnticoll(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t bcnt,								/**< [In] Number of valid bits (NVB) */
    uint8_t * snr								/**< [Out] Pointer to a location where the UID of the first collision-free detected PICC will be stored. */
    );

/**
* \brief The function initiates the specified cascade level of the ISO14443-3A anticollision.
The UID bytes returned by the PICC are stored at the provided address. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. In case of collision the function exits also with success. 
* \retval #PH_ERR_PROTOCOL_ERROR Inconsistent CRC
* \retval #PH_ERR_INTERNAL_ERROR Wrong parameter - number of valid bits NVB.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PiccCascAnticoll(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t select_code,						/**< [In] Select command code */
    uint8_t bcnt,								/**< [In] Number of valid bits (NVB) */
    uint8_t * snr								/**< [Out] Pointer to a location where the UID of the first collision-free detected PICC will be stored. */
    );

/**
* \brief The function starts the ISO14443-3A 'Select' command at the first cascade level(command code 0x93). 
The SAK byte returned by the PICC is stored at the provided address. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_MfPiccSelect(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * snr,								/**< [Out] UID, 4 bytes serial number of the PICC to be selected. */
    uint8_t * sak								/**< [Out] Pointer to a location where the SAK byte returned from the PICC will be stored. */
    );

/**
* \brief The function starts the ISO14443-3A 'Select' command at the specified cascade level. 
The SAK byte returned by the PICC is stored at the provided address. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PiccCascSelect(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t select_code,						/**< [In] 'Select' command code according to ISO14443-3A for the required cascade level */
    uint8_t * snr,								/**< [Out] UID, 4 bytes serial number of the PICC to be selected. */ 
    uint8_t * sak								/**< [Out] Pointer to a location where the SAK byte returned from the PICC will be stored. */
    );

/**
* \brief The function authenticates one sector of the last selected PICC using the master key stored in the PCD's EEPROM.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_AUTH_ERROR Protocol or integrity error.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_MfPiccAuth(
                                        phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
                                        uint8_t keyAB,								/**< [In] Selects master key <em>PICC_AUTHENT1A</em> or <em>PICC_AUTHENT1B</em>. */
                                        uint8_t key_addr,							/**< [In] EEPROM address where the keys are stored in the PCD, range [0,15] */
                                        uint8_t block								/**< [In] Number of PICC block defining the sector that should be authenticated. */
                                        );

/**
* \brief The function authenticates one sector of the defined by the UID PICC using the master key stored in the PCD's EEPROM.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by the an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_MfPiccAuthE2(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t auth_mode,							/**< [In] Selects master key <em>PICC_AUTHENT1A</em> or <em>PICC_AUTHENT1B</em>. */
    uint8_t * snr,								/**< [In] UID, 4 bytes serial number of the PICC to be authenticated. */
    uint8_t key_sector,							/**< [In] EEPROM address where the keys are stored in the PCD, range [0,15]*/
    uint8_t block								/**< [In] Number of PICC block defining the sector that should be authenticated. */
    );
/**
* \brief The function performs a proprietary coding over 6 bytes of key source uncoded data and stores the coded result at the destination address.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_AUTH_ERROR Protocol or integrity error.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_HostCodeKey(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * uncoded,							/**< [In] Pointer to a 6-byte buffer holding the source of uncoded data. */
    uint8_t * coded								/**< [In] Pointer to a 12-byte buffer for the destination coded data. */
    );

/**
* \brief The function performs a proprietary coding of the provided key (6 bytes) and stores it coded (12 bytes) into 
the defined PCD internal EEPROM sector. 
If key B is specified, then it is stored with an additional offset 12 bytes.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PcdLoadKeyE2(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t auth_mode,							/**< [In] Key <em>PICC_AUTHENT1A</em> or <em>PICC_AUTHENT1B</em>. */
    uint8_t key_sector,							/**< [In] Sector in the PCD internal EEPROM, where to store the key */
    uint8_t * keys								/**< [In] Pointer to a 6-byte buffer uncoded key */
    );

/**
* \brief The function authenticates one PICC's sector using keys stored in the PCD.
The key needed for authentication is first loaded by this function into PCD's EEPROM in a coded form. 
The proprietary coding of the key shall be done first by phhalHw_Rd70x_Cmd_HostCodeKey function.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_AUTH_ERROR Protocol or integrity error.
* \retval Other Invalid parameters or conditions - the error status is returned by the an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_MfPiccAuthKey(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t auth_mode,							/**< [In] Key <em>PICC_AUTHENT1A</em> or <em>PICC_AUTHENT1B</em>. */
    uint8_t * snr,								/**< [In] Pointer to a 4-byte buffer of the PICC's serial numner(UID) */
    uint8_t * keys,							   	/**< [In] Pointer to a 12-byte buffer of coded key */
    uint8_t  block								/**< [In] Number of the block to be authenticated */
    );

/**
* \brief The function reads from PICC 16 byte data block from the defined address and stores it into the data buffer.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_MfPiccRead(
                                        phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
                                        uint8_t addr,								/**< [In] Block address to read from. */
                                        uint8_t * data								/**< [Out] Pointer to 16-byte destination data buffer. */
                                        );

/**
* \brief The function reads from the PICC data with specified length and stores it into destination data buffer.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PiccCommonRead(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t cmd,								/**< [In] Read command. */
    uint8_t addr,								/**< [In] Block address to read from. */
    uint8_t datalen,							/**< [In] Length of data to read. */
    uint8_t * data								/**< [Out] Pointer to destination data buffer. */
    );

/**
* \brief The function writes 16 byte data block at the defined block address in the PICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_MfPiccWrite(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t addr,								/**< [In] PICC block destination address. */
    uint8_t * data								/**< [In] Pointer to 16-byte source data buffer. */
    );


/**
* \brief The function writes a 4 byte data block at the defined block address in the PICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PiccWrite4(
                                        phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
                                        uint8_t addr,								/**< [In] Destination block address in the PICC. */	
                                        uint8_t * data								/**< [In] Pointer to 4-byte source data buffer. */
                                        );

/**
* \brief The function writes data with the defined length at the destination block address in the PICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_PROTOCOL_ERROR The number of received bits is not equal to the expected.
* \retval #PH_ERR_INTERNAL_ERROR Write error. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PiccCommonWrite(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t cmd,								/**< [In] Write command */
    uint8_t addr,								/**< [In] Destination block address in the PICC */
    uint8_t datalen,							/**< [In] Length of data to be written. */
    uint8_t * data								/**< [In] Pointer to source data buffer. */
    );

/**
* \brief The function performs PICC value block manipulation using an increment, decrement or restore operation. 
The PICC internally reads the stored value block and takes it as initial value for the calculation. The other operand is the value parameter from this function.
Finally the result is transferred at the defined in the parameter PICC's block address. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_PROTOCOL_ERROR The number of received bits is not equal to the expected.
* \retval #PH_ERR_INTERNAL_ERROR Value error or the command isn't authenticated for this sector
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_MfPiccValue(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t dd_mode,							/**< [In] Operation code - increment, decrement or restore. */
    uint8_t addr,								/**< [In] Address of PICC's value block to be manipulated. */
    uint8_t * value,							/**< [In] Pointer to 4-byte buffer holding a positive value, which will be involved in the operation. */
    uint8_t trans_addr							/**< [In] PICC's block address, to which the result of the calculation shall be transferred. */
    );


/**
* \brief The function performs PICC value block decrement operation. 
The PICC internally reads the stored value block and takes it as initial value for the calculation. The other operand is the value parameter from this function.
Finally the result is transferred to the initial value block address. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_PROTOCOL_ERROR The number of received bits is not equal to the expected.
* \retval #PH_ERR_INTERNAL_ERROR Value error or the command isn't authenticated for this sector
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_MfPiccValueDebit(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t dd_mode,							/**< [In] Operation code - only decrement operation is allowed */
    uint8_t addr,								/**< [In] Address of PICC's value block to be decremented. */
    uint8_t * value								/**< [In] Pointer to 4-byte buffer holding a positive value, which will be involved in the operation. */
    );

/**
* \brief The function transmits ISO14443-3A two bytes standard frame containing HALT command and sets the PICC into halted state. 
Having send the command to the PICC, the function does not expect a response.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. Timeout of the PICC response.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_MfPiccHalt(
                                        phhalHw_Rd70x_DataParams_t * pDataParams	/**< [In] Pointer to an initialized HAL parameter structure. */
                                        );



/**
* \brief The function starts with the common request command REAQ/WUPA and stores the returned ATQA in the provided buffer. 
Further it performs ISO14443-3A anticollisiion sending the select commands according to the casade level
and stores the UID, the UID length and the SAK response in the provided locations.
According to the passed baudrate parameter, both PCD and PICC are switched to the new transfer rate by this function.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_PROTOCOL_ERROR Invalid UID CLn check byte(BCC).
* \retval #PH_ERR_INTERNAL_ERROR Selected baudrate is not supported or no PICC supports bitwise anticollision or wrong parameter value.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PiccActivation(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t ctrl_flag,							/**< [In] Dummy */
    uint8_t req_code,							/**< [In] Common request command code ISO14443-3A REQA/WUPA */
    uint8_t * br,								/**< [In] Baudrate for PICC communication. 
                                                *                  <ul>
                                                *                   <li> 0  106 kBaud
                                                *                   <li> 1  212 kBaud
                                                *                   <li> 2  424 kBaud
                                                *                   <li> 3  848 kBaud
                                                *                  </ul> */
                                                uint8_t * atq,								/**< [Out] Pointer to 2-byte buffer for the ATQA. */
                                                uint8_t * sak,								/**< [Out] Pointer to a byte holding the SAK returned by the PICC. */
                                                uint8_t * uid,								/**< [Out] Pointer to 10-byte byffer holding the PICC's UID. */
                                                uint8_t * uid_len,							/**< [Out] Pointer to the UID length. */
                                                uint8_t * script,							/**< [In] Additional bytes to send directly after activation (for debugging) */
                                                uint16_t script_len,						/**< [In] length of additional bytes to send (0 if not used). */
                                                uint8_t * resp,								/**< [Out] Full response (used for debugging) */
                                                uint16_t * resp_len,						/**< [Out] Length of full response */
                                                uint8_t sec									/**< [In] Timeout in seconds */
                                                );

/**
* \brief The function performs PICC activation. 
It is similar to 'Picc Activation' with the difference, that the request code is fixed to the ISO14443-3A command REQA. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_PROTOCOL_ERROR Invalid UID CLn check byte(BCC).
* \retval #PH_ERR_INTERNAL_ERROR Selected baudrate is not supported or no PICC supports bitwise anticollision or wrong parameter value.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PiccActivateIdle(
    phhalHw_Rd70x_DataParams_t * pDataParams,		/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t br,										/**< [In] Baudrate for PICC communication. */
    uint8_t * atq,									/**< [Out] Pointer to 2-byte buffer for the ATQA. */
    uint8_t * sak,									/**< [Out] Pointer to a byte holding the SAK returned by the PICC. */
    uint8_t * uid,									/**< [Out] Pointer to 10-byte byffer holding the PICC's UID. */	
    uint8_t * uid_len								/**< [Out] Pointer to the UID length. */
    );

/**
* \brief The function performs PICC activation. 
It is similar to 'Picc Activate Idle' with the difference that it has an additional timeout parameter that is considered. 
This function returns with either a selected PICC's UID or a status if timeout occured.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_PROTOCOL_ERROR Invalid UID CLn check byte(BCC).
* \retval #PH_ERR_INTERNAL_ERROR Selected baudrate is not supported or no PICC supports bitwise anticollision or wrong parameter value <em>sec</em>.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PiccActivateIdleLoop(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t br,									/**< [In] Baudrate for PICC communication. */
    uint8_t * atq,								/**< [Out] Pointer to 2-byte buffer for the ATQA. */
    uint8_t * sak,								/**< [Out] Pointer to a byte holding the SAK returned by the PICC. */
    uint8_t * uid,								/**< [Out] Pointer to 10-byte byffer holding the PICC's UID. */	
    uint8_t * uid_len,							/**< [Out] Pointer to the UID length. */
    uint8_t sec									/**< [In] Time-out value in seconds. */ 					
    );

/**
* \brief The function performs PICC activation. 
It is similar to 'Picc Activation' with the difference that the request code is fixed to the ISO14443-3A command WUPA. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_PROTOCOL_ERROR Invalid UID CLn check byte(BCC).
* \retval #PH_ERR_INTERNAL_ERROR Selected baudrate is not supported or no PICC supports bitwise anticollision or wrong parameter value.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PiccActivateWakeup(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In]  Pointer to an initialized HAL parameter structure. */
    uint8_t br,									/**< [In]  Baudrate for PICC communication. */
    uint8_t * atq,								/**< [Out] Pointer to 2-byte buffer for the ATQA. */
    uint8_t * sak,								/**< [Out] Pointer to a byte holding the SAK returned by the PICC. */
    uint8_t * uid,								/**< [Out] Pointer to 10-byte byffer holding the PICC's UID. */
    uint8_t uid_len								/**< [Out] Pointer to the selected PICC's UID length. */
    );

/**
* \name Exchange Commands
*/

/**
* \brief The function initiates a block exchange between the PCD and PICC.
If <em>append_crc</em> is not equal to 0, the last two CRC bytes of the send data block are replaced by internally generatated CRC bytes.
The same value causes also the last two (CRC)bytes of the received data block to be set both to 0.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTERNAL_ERROR Invalid parameter <em>send_bytelen</em>
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PiccExchangeBlock(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * send_buffer,						/**< [In] Pointer to a buffer holding the data block to be sent to the PICC */
    uint16_t send_bytelen,						/**< [In] Length of the data block to be sent to the PICC */
    uint8_t ** rec_data,						/**< [In] Pointer to pointer to received data buffer.  */
    uint16_t * rec_bytelen,						/**< [Out] Pointer to received data length. */
    uint8_t append_crc,							/**< [In]  Append internally generated CRC bytes if not equal to 0. */
    uint32_t timeout							/**< [In] Timeout for the exchnge */
    );

/**
* \brief The function executes a block exchange between the PCD and PICC and initiates a reset procedure in case of timeout.
If <em>append_crc</em> is not equal to 0, the last two CRC bytes of the send data block are replaced by internally generatated CRC bytes.
The same value causes also the last two (CRC)bytes of the received data block to be set both to 0.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTERNAL_ERROR Invalid parameter <em>send_bytelen</em>
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PiccExchangeBlockRfCycle(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * send_buffer,						/**< [In] Pointer to a buffer holding the data block to be sent to the PICC */
    uint16_t send_bytelen,						/**< [In] Length of the data block to be sent to the PICC */
    uint8_t ** rec_data,						/**< [In] Pointer to pointer to received data buffer.  */
    uint16_t * rec_bytelen,						/**< [Out] Pointer to received data length. */
    uint8_t append_crc,							/**< [In]  Append internally generated CRC bytes if not equal to 0. */
    uint32_t timeout							/**< [In] Timeout for the PICC answer */
    );

/** 
* \brief The function performs a bitwise data exchange between the PCD and PICC, where the send and/or receive data does not end at a byte boundary.
Note that it is not needed to increment <em>send_bytelen</em> by two if TxCRC is enabled. Further, no CRC bytes are appended to the receive buffer. 
This behaviour is different to <em>phhalHw_Rd70x_Cmd_PiccExchangeBlock</em> function.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_BUFFER_OVERFLOW <em>send_bytelen</em> it too long and crosses the boundary of the available transmit buffer in the library.
* \retval #PH_ERR_INTERNAL_ERROR  <em>send_bytelen</em> is 0 or it's too long and crosses the boundary of the available buffer in the PCD.
* \retval #PH_ERR_COLLISION_ERROR Collision in SOF. Received lengts variables <em>rec_bytelen</em> and <em>rec_validbits</em> are set to 0.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PiccExchgBitByte(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * send_buffer,						/**< [In] Pointer to a buffer holding the data block to be sent to the PICC */
    uint16_t send_bytelen,						/**< [In] Length of the data block to be sent to the PICC. In the last byte only its first <em>send_validbits</em> are valid. */
    uint8_t send_validbits,						/**< [In] Length of the additional valid bits to be sent. */
    uint8_t ** rec_data,						/**< [In] Pointer to pointer to received data buffer. In the last byte only its first <em>rec_validbits</em> are valid. */
    uint16_t * rec_bytelen,						/**< [Out] Pointer to received data length in bytes. */
    uint8_t * rec_validbits,					/**< [Out] Pointer to received number of valid bits in the last byte. */
    uint8_t flags,								/**< [In] Disables the settings of <em>regModify</em> [b0..b3]. b7, if 1, enables the EMD Suppression. */
    uint32_t timeout							/**< [In] Timeout for the PICC answer. */
    );

/** 
* \brief The function performs a bitwise data exchange between the PCD and PICC, where the send and/or receive data does not end at a byte boundary.
The exchange command is to proceed with RfReset in case of Timeout.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_BUFFER_OVERFLOW <em>send_bytelen</em> it too long and crosses the boundary of the available transmit buffer in the library.
* \retval #PH_ERR_INTERNAL_ERROR  <em>send_bytelen</em> is 0 or it's too long and crosses the boundary of the available buffer in the PCD.
* \retval #PH_ERR_COLLISION_ERROR Collision in SOF. Received lengts variables <em>rec_bytelen</em> and <em>rec_validbits</em> are set to 0.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PiccExchgBitByteRfCycle(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * send_buffer,						/**< [In] Pointer to a buffer holding the data block to be sent to the PICC */
    uint16_t send_bytelen,						/**< [In] Length of the data in bytes to be sent to the PICC. In the last byte only its first <em>send_validbits</em> are valid. */
    uint8_t send_validbits,						/**< [In] Length of the additional valid bits in the last byte.*/
    uint8_t ** rec_data,						/**< [In] Pointer to pointer to received data buffer. In the last byte only its first <em>rec_validbits</em> are valid. */
    uint16_t * rec_bytelen,						/**< [Out] Pointer to received data length in bytes. */
    uint8_t * rec_validbits,					/**< [Out] Pointer to received number of valid bits in the last byte. */
    uint8_t flags,								/**< [In] Disables the settings of <em>regModify</em> [b0..b3]. b7, if 1, enables the EMD Suppression. */
    uint32_t timeout							/**< [In] Timeout for the PICC answer. */
    );

/**
* \brief  The function performs transparent VCD to VICC data exchange according to ISO15693-3 standard.
* The SOF, EOF and two CRC bytes are added by the reader. The returned data contains a flags byte followed by a command response data.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_BUFFER_OVERFLOW <em>send_bytelen</em> it too long and crosses the boundary of the available transmit buffer in the library.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Exchange(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * send_buffer,						/**< [In] Pointer to a buffer holding the data block to be sent to the PICC. */
    uint16_t send_bytelen,						/**< [In] Length of the data to be sent to the VICC. */
    uint8_t ** rec_data,						/**< [In] Pointer to pointer to received data buffer. */
    uint16_t * rec_bytelen						/**< [Out] Pointer to received data length. */
    );


/**
* \brief The function performs transparent 'read/write device'(RWD) to EPC/UID data exchange.
The different 'start/end of frame' symbols: SSOF, LSOF, CEOF and the 'close slot sequence'(CS) are added by the RWD
according to the <em>bOption</em> parameter:
* \li	0x00	-	SSOF 
* \li	0x01	-	LSOF
* \li	0x02	-	CS     
Note that the CRC8 or CRC16 have to be calculated by the caller and included in the data block as well as and eventual hash value after it, if
Begin Round command is exchanged with this function.
The returned data contains a flags byte followed by a command response data.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_BUFFER_OVERFLOW <em>send_bytelen</em> it too long and crosses the boundary of the available transmit buffer in the library.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_EPCUID_Exchange(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t bOption,							/**< [In] Defines the type of SOF */
    uint8_t * send_buffer,						/**< [In] Pointer to a buffer holding the data block to be sent to the PICC. */
    uint16_t send_bytelen,						/**< [In] Length of the data to be sent to the VICC. */
    uint8_t bTxLastBits,						/**< [In] Number of the last bits within the last byte in the <em>send buffer</em>, which are not part of the exchange data. */
    uint8_t ** rec_data,						/**< [In] Pointer to pointer to received data buffer. */
    uint16_t * rec_bytelen						/**< [Out] Pointer to received data length. */
    );
/*@}*/



/**
* \name Shared Commands
*/
/*@{*/


/**
* \brief The function initializes the RF communication timeout. 
The timeout value is measured between the last bit sent to the tag and the first bit received from the tag.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PcdSetTmo(
                                       phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
                                       uint32_t tmoLength							/**< [In] Timeout period calculated in etu's of 9.44 us */
                                       );

/**
* \brief The function performs a reset of reader IC's hardware, if the MF RC500 reset pin is connected to a dedicated uController port pin. 
The reset is triggered with a delay of 500 [ms], the reader reset pin is set active for 100[ms].
After each reset, the automatic interface recognition of the reader IC is activated. Both, resetting the reader IC and determining the interface is done by this function. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTERNAL_ERROR Interface error while resetting the reader IC
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PcdReset(
                                      phhalHw_Rd70x_DataParams_t * pDataParams		/**< [In] Pointer to an initialized HAL parameter structure. */
                                      );

/**
* \brief The function turns-off the HF field of the reader for a specified time in milliseconds. Elapsing this time the HF-field is turned-on again with a delay of 1[ms].
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PcdRfReset(
                                        phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
                                        uint16_t ms									/**< [In] Defines the switch-OFF time of the reader's HF-field in milliseconds. */
                                        );

/**
* \brief The function starts a transaction timer on the microcontroller, which counts every microsecond until the corresponding stop-function is called.
The measured microseconds count is returned by the stop-function <em>phhalHw_Rd70x_Cmd_HostTransTmrStop</em>. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_HostTransTmrStart(
    phhalHw_Rd70x_DataParams_t * pDataParams	/**< [In] Pointer to an initialized HAL parameter structure. */
    );

/**
* \brief The function stops the transaction timer on the microcontroller, 
which has been counting every microsecond from the moment the start-function <em>phhalHw_Rd70x_Cmd_HostTransTmrStart</em> has been called.
The timer period can cover a couple of Mifare commands, but in this case the processing time also includes the communication time between the host and the microcontroller.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_HostTransTmrStop(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint32_t * us								/**< [Out] Time period between the start function call and this function call in microseconds. */
    );


/**
* \brief The function initializes a counter for command execution. When enabled, the command execution counter is decremented after each command
executi0n. Reaching value 0 the execution of the current command is disabled.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_HostTransTmrSetCMDCount(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint16_t lvtime								/**< [In] Initial value of the command execution counter. */
    );

/**
* \brief The function outputs the result of the last execution time.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_HostGetExecutionTime(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint32_t *us								/**< [Out] Execution time in microseconds. */
    );

/**
* \brief This function writes one byte to the reader IC address space.
It sets the necessary register page address in the page register. After that it writes a byte value into the specified register.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_WriteRC(
                                     phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
                                     uint8_t addr,								/**< [In] Reader's IC register address to be written */
                                     uint8_t value								/**< [In] Value to write into the speified register */
                                     );

/**
* \brief This function reads one byte from the reader IC address space.
It sets the necessary register page address in the page register. After that it reads a byte value from the specified register.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ReadRC(
                                    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
                                    uint8_t addr,								/**< [In] Reader's IC register address to read from. */	
                                    uint8_t *value								/**< [Out] Value read from the specified register */
                                    );
/**
* \brief The function writes multiple registers. The register addresses and their corresponding values to be written with this command
are stored in pairs in <em>addr_value</em> buffer so that the value appears as second.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_WriteMultiple(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * addr_value,						/**< [In] Pointer to buffer holding the required register addresses and the values to be written. */
    uint16_t len								/**< [In] Number of register to write. */
    );

/**
* \brief The function reads multiple registers. 
In the <em>addr_value</em> buffer the register addresses and their corresponding values are stored in pairs, so that the value appears
immediately after the address it has been read from.  
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ReadMultiple(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t *addr_value,						/**< [In/Out] Pointer to buffer holding the required register addresses and the values to be written. */
    uint16_t len								/**< [In] Number of register to be read. */
    );

/**
* \brief The function reads out data stored in the reader IC's EERPOM  beginning at address <em>startaddr</em>. 
The number of bytes to be read are given by the variable <em>length</em> and the read out data are stored in the provided <em>data</em> buffer  
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PcdReadE2(
                                       phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */ 
                                       uint16_t startaddr,							/**< [In] Start address to read from in the EEPROM. */
                                       uint8_t length,								/**< [In] Lenght in bytes of data to read.  */
                                       uint8_t * data								/**< [Out] Pointer to buffer where the data read shall be stored. */
                                       );

/**
* \brief The function writes a given <em>length</em> of data bytes stored in the <em>data</em> buffer to the reader IC's EEPROM 
beginning at address <em>startaddr</em>.  
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PcdWriteE2(
                                        phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */ 
                                        uint16_t startaddr,							/**< [In] Start address to write within the EEPROM. */	
                                        uint8_t length,								/**< [In] Lenght in bytes of data to written. */
                                        uint8_t* data								/**< [In] Pointer to buffer holdin the write data. */
                                        );

/**
* \brief The function sets the reader IC in idle mode. This turns-off all internal current sinks 
including the oscillator. The digital input buffers are not separated from the input pads but keep their functionality. The digital output pins 
don't change. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PcdSetIdleMode(
    phhalHw_Rd70x_DataParams_t * pDataParams);	/**< [In] Pointer to an initialized HAL parameter structure. */


/**
* \brief The function changes the reader IC mode from idle back to operating mode.
\note This function need not to be called explicitely, because every reader command checks the idle mode itself and calls this function automatically.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PcdClearIdleMode(
    phhalHw_Rd70x_DataParams_t * pDataParams);	/**< [In] Pointer to an initialized HAL parameter structure. */

/**
* \brief The function outputs a firmware version string and its length in the specified buffers.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PcdGetFwVersion(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * version,							/**< [Out] Pointer to null terminated version string, max.length 128 bytes. */
    uint16_t * versionLen						/**< [Out] Pointer to the length of the version string. */
    );

/**
* \brief The function outputs the product ID of the reader IC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PcdGetRicVersion(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t * version							/**< [Out] Pointer to null terminated version string length 5 bytes. */
    );

/**
* \brief This function initializes the reader IC EEPROM with factory values. First the function initializes the registers of the reader IC with 
RC500 factory default values. After reading back the product ID of the reader IC, all factory default values are written to the EEPROM.  
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PcdInitializeE2(
    phhalHw_Rd70x_DataParams_t * pDataParams	/**< [In] Pointer to an initialized HAL parameter structure. */
    );

/**
* \brief The function reads data from memory address space word aligned. If an odd address is passed to this function, the address will be converted
to the next lower even address and the two byte data will be returned.  
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ReadWord(
                                      phhalHw_Rd70x_DataParams_t * pDataParams,			/**< [In] Pointer to an initialized HAL parameter structure. */ 
                                      uint32_t address,									/**< [In] Address to read from. */
                                      uint16_t * value									/**< [Out] Pointer to a variable, where the 16 bit word read data will be stored.*/ 
                                      );

/**
* \brief The function reads out a 4 bytes serial number of the used reader IC. The serial number is unique for all delivered reader ICs.  
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_PcdGetSnr(
                                       phhalHw_Rd70x_DataParams_t * pDataParams,		/**< [In] Pointer to an initialized HAL parameter structure. */ 
                                       uint8_t * snr									/**< [Out] Pointer to 4-byte buffer, where the serian number will stored. */
                                       );


/**
* \brief The function controls the 5 LEDs situated in the middle of the antenna. The <em>onoff</em> parameter defines the state of the LEDs.
0		- All LEDs are Off
!= 0	- All LEDs are On
255		- LEDs are ON and flash during command execution.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_SwitchLED(
                                       phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */ 
                                       uint8_t onoff								/**< [In] LEDs control */ 
                                       );

/**
* \brief The function initializes port pin for a trigger(debug) or a release mode. 
In trigger(debug) mode two ports are served - Port P2.1 is high during ISR execution and port P6.3 is high during the command processing.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_DbgTrigger(
                                        phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */ 
                                        uint8_t enableTrigger						/**< [In] The ports P2.1 and P6.3 are triggered high according to the program execution. */	
                                        );
/**
* \name ICode1 Commands
*/
/*@{*/

/**
* \brief The function configures the reader IC for ICode mode. It performs also reader IC reset and 10[ms] reset of the HF. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTERNAL_ERROR Interface error.

* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_I1PcdConfig(
    phhalHw_Rd70x_DataParams_t * pDataParams		/**< [In] Pointer to an initialized HAL parameter structure. */ 
    );

/**
* \brief The function performs a HF reset. The HF is kept-off for the indicated time of miliseconds.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_I1PcdRfReset(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint16_t ms									/**< [In] miliseconds to keep the HF-off. */
    );
/*@}*/

/**
* \name ISO15693 Commands
*/
/*@{*/

/**
* \brief The function initializes the reader IC to ISO15693 standard mode "1 out of 256 coding".
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_I2init_StdMode_15693(
    phhalHw_Rd70x_DataParams_t * pDataParams	/**< [In] Pointer to an initialized HAL parameter structure. */
    );

/**
* \brief The function initializes reader IC to fast mode "1 out of 256 coding". 
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_I2init_FastMode_15693(
    phhalHw_Rd70x_DataParams_t * pDataParams);	/**< [In] Pointer to an initialized HAL parameter structure. */

/**
* \brief The function executes the READ SINGLE BLOCK and READ MULTIPLE BLOCK commands. 
*   If the number of blocks is equal 0 or 1, the READ SINGLE BLOCK command is used, otherwise the READ MULTIPLE BLOCK one.
The first byte in the response buffer contains the status byte followed by the read block data. 
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Read_Sm(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t flags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t * uid,								/**< [In] UID of the VICC to read from. */
    uint8_t blnr,								/**< [In] Block address, where the read operation starts. */
    uint8_t nbl,								/**< [In] Number of blocks to read. This value is decreased by 1 in the FW in order to comply with the ISO15683-3 standard.*/
    uint16_t * resplen,							/**< [Out] Pointer to the length of the response buffer */
    uint8_t * resp								/**< [Out] Pointer to the response buffer. */
    );
/**
* \brief The function executes the ISO15693-3 INVENTORY command. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Inventory(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t flags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */	
    uint8_t AFI,								/**< [In] Application family identifier, optional and dependent on <em>flags settings</em> */
    uint8_t masklengh,							/**< [In] Length of mask in number of valid bits. */
    uint8_t * uid,								/**< [In] Pointer to a buffer holding an UID inventory operation mask. */
    uint16_t * resplen,							/**< [Out] Pointer to the length of the response buffer */
    uint8_t * resp								/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the WRITE SINGLE BLOCK and WRITE MULTIPLE BLOCK commands.
The number of blocks  parameter <em>nbl</em> decides if a WRITE SINGLE BLOCK or WRITE MULTIPLE BLOCK command is used. 
If the command is successful the response buffer contains the FW function exit status and the 'flags' byte returned by the VICC.
Otherwise the response buffer contains the FW function exit status only.
* return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Write_Sm(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t flags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */	
    uint8_t * uid,								/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint8_t blnr,								/**< [In] Block address, where the write operation starts. */
    uint8_t nbl,								/**< [In] Number of blocks to write. This value is decreased by 1 in the FW in order to comply with the ISO15683-3 standard.*/
    uint8_t * data,								/**< [In] Pointer to a buffer holding the write data. */
    uint16_t * resplen,							/**< [Out] Pointer to the length of the response buffer */
    uint8_t * resp								/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the ISO15693-3 STAY QUIET command. 
* \note There shall be no response from the VICC to this command.
* \return Status code
* \retval #PH_ERR_IO_TIMEOUT The command is successfully executed. The VICC is in quite state.
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Stay_Quiet(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t flags,								/**< [In] Command 'Flags' byte including the OPTION_flag according to ISO15693-3. */
    uint8_t * uid,								/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint16_t * resplen,							/**< [Out] Pointer to the length of the response buffer */			
    uint8_t * resp								/**< [Out] Pointer to the response buffer. */			
    );

/**
* \brief The function executes the ISO15693-3 LOCK BLOCK command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No VICC is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Lock_Block(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t flags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t * uid,								/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint8_t blnr,								/**< [In] Block address, of the block to be locked. */
    uint16_t * resplen,							/**< [Out] Pointer to the length of the response buffer. */
    uint8_t *resp								/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the ISO15693-3 SELECT command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No VICC is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Select(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t flags,								/**< [In] Command 'Flags' byte according to ISO15693-3, 'Address_flag'=1 and 'Select_flag'=0. */	
    uint8_t * uid,								/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint16_t * resplen,							/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * resp								/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the ISO15693-3 RESET TO READY command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Reset_To_Ready(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t flags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t * uid,								/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint16_t * resplen,							/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * resp								/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the ISO15693-3 WRITE_AFI command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Write_AFI(
    phhalHw_Rd70x_DataParams_t * pDataParams,/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t flags,							/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t * uid,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint8_t AFI,							/**< [In] Application Family ID that shall be written in the VICC#S memory. */
    uint16_t * resplen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * resp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the ISO15693-3 LOCK_AFI command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Lock_AFI(
    phhalHw_Rd70x_DataParams_t * pDataParams,/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t flags,							/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t * uid,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint16_t * resplen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * resp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the ISO15693-3 WRITE DSFID command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Write_DSFID(
    phhalHw_Rd70x_DataParams_t * pDataParams,/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t flags,							/**< [In] Command 'Flags' byte according to ISO15693-3. */ 
    uint8_t * uid,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint8_t DSFID,							/**< [In] 'Data storage format identifier' byte to be writen. */
    uint16_t * resplen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * resp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the ISO15693-3 LOCK DSFID command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Lock_DSFID(
    phhalHw_Rd70x_DataParams_t * pDataParams, /**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t flags,							/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t * uid,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint16_t * resplen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * resp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the ISO15693-3 GET SYSTEM INFORMATION command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Get_System_Information(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t flags,							/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t * uid,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint16_t * resplen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * resp							/**< [Out] Pointer to the response buffer. */
    );


/**
* \brief The function executes the ISO15693-3 GET MULTIPLE BLOCK SECURITY STATUS command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Get_Multiple_Block_Security(
    phhalHw_Rd70x_DataParams_t * pDataParams,/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t flags,							/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t * uid,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */ 
    uint8_t blnr,							/**< [In] Block address, where the operation starts. */
    uint8_t nbl,							/**< [In] Number of blocks. This value is decreased by 1 in the FW */
    uint16_t * resplen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * resp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the custom INVENTORY READ command for VICCs with SLI tiype. 
Dependent on 'Number of time slots' flag, in the 'Flags' byte the command is executed for 1 or 16 time slots.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Inventory_Read(
    phhalHw_Rd70x_DataParams_t * pDataParams,/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t flags,							/**< [In] Command 'Flags' byte according to VICC specification. */
    uint8_t ManCode,						/**< [In] 'IC Manufacturer code' of the VICC. */
    uint8_t AFI,							/**< [In] Application Family ID byte,which is available only if 'AFI_flag' is set in the 'Flags' byte. */
    uint8_t masklengh,						/**< [In] Length of UID mask in number of valid bits. */
    uint8_t * uid,							/**< [In] Pointer to a buffer holding an UID mask. */
    uint8_t blnr,							/**< [In] Block address, where the read operation starts. */
    uint8_t nbl,							/**< [In] Number of blocks to read from the inventorized VICCs. */
    uint16_t * resplen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * resp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the custom FAST INVENTORY READ command for VICCs with SLI tiype. 
Dependent on 'Number of time slots' flag, in the 'Flags' byte the command is executed for 1 or 16 time slots. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Fast_Inventory_Read(
    phhalHw_Rd70x_DataParams_t * pDataParams,/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t flags,							/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t ManCode,						/**< [In] 'IC Manufacturer code' of the VICC. */
    uint8_t AFI,							/**< [In] Application Family ID byte,which is available only if 'AFI_flag' is set in the 'Flags' byte. */
    uint8_t masklengh,						/**< [In] Length of UID mask in number of valid bits. */
    uint8_t * uid,							/**< [In] Pointer to a buffer holding an mask UID.  */
    uint8_t blnr,							/**< [In] Block address, where the read operation starts. */
    uint8_t nbl,							/**< [In] Number of blocks to read from the inventorized VICCs. */
    uint16_t * resplen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * resp							/**< [Out] Pointer to the response buffer. */
    );
/**
* \brief The function executes the custom SET EAS command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Set_Eas(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t flags,							/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t ManCode,						/**< [In] 'IC Manufacturer code' of the VICC. */
    uint8_t * uid,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint16_t * resplen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * resp							/**< [Out] Pointer to the response buffer. */	
    );

/**
* \brief The function executes the custom RESET EAS command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Reset_Eas(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
    uint8_t flags,							/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t ManCode,						/**< [In] 'IC Manufacturer code' of the VICC. */
    uint8_t * uid,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint16_t * resplen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * resp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the custom LOCK EAS command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Lock_Eas(
    phhalHw_Rd70x_DataParams_t * pDataParams,/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t flags,							/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t ManCode,						/**< [In] 'IC Manufacturer code' of the VICC. */
    uint8_t * uid,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */	
    uint16_t * resplen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * resp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the custom EAS ALARM command. 
After a successful command execution the response buffer containd the EAS sequence or the EAS ID, depending on the 'Option_flag' and the EAS ID length. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Eas_Alarm(
    phhalHw_Rd70x_DataParams_t * pDataParams,/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t flags,							/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t ManCode,						/**< [In] 'IC Manufacturer code' of the VICC. */
    uint8_t * uid,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint8_t bEAS_ID_MaskLength,				/**< [In] EAS ID length - indicates how many bits of the following EAS ID data are valid. Multiple of 8, i.e. 0, 8 or 16. */
    uint8_t * pbEAS_ID,						/**< [In] Pointer to a buffer holding the EAS ID used to select the VICCs, which are to response with the EAS sequence. */ 
    uint16_t * resplen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * resp							/**< [Out] Pointer to the response buffer. */
    );
/*@}*/



/**
* \name ICode EPC Commands
*/
/*@{*/

/**
* \brief The function configures the reader IC for EPC mode.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_EPCPcdConfig(
    phhalHw_Rd70x_DataParams_t * pDataParams	/**< [In] Pointer to an initialized HAL parameter structure. */ 
    );


/**
* \brief  The function executes the EPC BEGIN ROUND command.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_EPCBeginRound(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t * mask,								/**< [In] Pointer to a buffer holding a selction mask. Specifies the bits to be compared with ICODE EPC data in the selection process. */
    uint8_t masklength,							/**< [In] Number of valid bits in the selection mask. */
    uint8_t nbrslots,							/**< [In] Number of slots coded according the ICODE EPC specification. */ 
    uint8_t hash,								/**< [In] Hash value used by the ICODE EPC to generate random time slot positions. */
    uint16_t * resplen,							/**< [Out] Pointer to the length of the response buffer. */
    uint8_t *resp								/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief  The function executes the EPC WRITE command. It writes a byte data into the ICODE EPC memory. 
The ICODE EPC specified CRC8 parameter for this command is calculated by the RWD. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTERNAL_ERROR Invalid parameter.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_EPCWrite(
                                      phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */  
                                      uint8_t blnr,								/**< [In] Address, where the write operation starts. */
                                      uint8_t data								/**< [In] Data to be written at the indicated write address. */
                                      );

/**
* \brief  The function executes the EPC DESTROY command. When executed it renders the ICODE EPC label permanently unable to give any replies. 
The ICODE EPC specified CRC8 parameter for this command is calculated by the RWD.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_EPCDestroy(
                                        phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */
                                        uint8_t * epc,								/**< [In] Pointer to a buffer holding a 12 bytes of EPC data. */
                                        uint8_t * destroy_code						/**< [In] Pointer to a buffer holding a 3 bytes of destroy code. */
                                        );

/*@}*/

/**
* \name ICode UID Commands
*/
/*@{*/

/**
* \brief The function configures the reader IC for UID mode.

* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_UIDPcdConfig(
    phhalHw_Rd70x_DataParams_t * pDataParams	/**< [In] Pointer to an initialized HAL parameter structure. */
    );

/**
* \brief  The function executes the UID BEGIN ROUND command.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_UIDBeginRound(
    phhalHw_Rd70x_DataParams_t * pDataParams,/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t * mask,							/**< [In] Pointer to a buffer holding a selction mask. Specifies the bits to be compared with ICODE EPC data in the selection process. */
    uint8_t masklength,						/**< [In] Number of valid bits in the selection mask. */
    uint8_t nbrslots,						/**< [In] Number of slots coded according the ICODE UID specification. */ 
    uint16_t * resplen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * resp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief  The function executes the EPC WRITE command. It writes a byte data into the ICODE UID memory. 
The ICODE UID specified CRC8 parameter for this command is calculated by the RWD. 
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTERNAL_ERROR Invalid parameter.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_UIDWrite(
                                      phhalHw_Rd70x_DataParams_t * pDataParams,/**< [In] Pointer to an initialized HAL parameter structure. */ 
                                      uint8_t blnr,							/**< [In] Address, where the write operation starts. */
                                      uint8_t data							/**< [In] Data to be written at the indicated write address. */
                                      );

/**
* \brief  The function executes the UID DESTROY command. When executed it renders the ICODE UID label permanently unable to give any replies. 
The ICODE UID specified CRC8 parameter for this command is calculated by the RWD.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_UIDDestroy(
                                        phhalHw_Rd70x_DataParams_t * pDataParams,/**< [In] Pointer to an initialized HAL parameter structure. */ 
                                        uint8_t * idd,							/**< [In] Pointer to a buffer holding a 19 bytes of Identifier data(IDD) data. */
                                        uint8_t * destroy_code					/**< [In] Pointer to a buffer holding a 3 bytes of destroy code. */
                                        );
/*@}*/

/**
* \name ICode SLI Commands
*/
/*@{*/

/**
* \brief The function executes the custom PASSWORD PROTECT EAS command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_PwdProtectEAS(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t bFlags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t bManCode,							/**< [In] 'IC Manufacturer code' of the VICC. */
    uint8_t * pbUID,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint16_t * pwRespLen,						/**< [Out] Pointer to the length of the response buffer. */ 
    uint8_t * pbResp							/**< [Out] Pointer to the response buffer. */
    );


/**
* \brief The function executes the custom WRITE EAS command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_WriteEAS_ID(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t bFlags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t bManCode,							/**< [In] 'IC Manufacturer code' of the VICC. */
    uint8_t * pbUID,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint16_t wEAS_ID,							/**< [In] 16 bits of the EAS ID to be written to the VICC' memory. */
    uint16_t * pwRespLen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * pbResp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the custom READ EPC command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_ReadEPC(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t bFlags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */	
    uint8_t bManCode,							/**< [In] 'IC Manufacturer code' of the VICC. */	
    uint8_t * pbUID,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint16_t * pwRespLen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * pbResp							/**< [Out] Pointer to the response buffer. EPC data */
    );

/**
* \brief The function executes the custom GET RANDOM NUMBER command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_GetRandomNumber(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t bFlags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t bManCode,							/**< [In] 'IC Manufacturer code' of the VICC. */
    uint8_t * pbUID,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint16_t * pwRespLen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * pbResp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the custom GET PASSWORD command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_SetPwd(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t bFlags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t bManCode,							/**< [In] 'IC Manufacturer code' of the VICC. */
    uint8_t * pbUID,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint8_t bPwdID,								/**< [In] Rassword ID. Indicates the type of the password to be set. */
    uint8_t * pbPwd,							/**< [In] Pointer to a buffer holding 4 bytes of XOR password */
    uint16_t * pwRespLen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * pbResp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the custom WRITE PASSWORD command. It writes in the VICC's memory the submitted password.
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_WritePwd(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t bFlags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t bManCode,							/**< [In] 'IC Manufacturer code' of the VICC. */
    uint8_t * pbUID,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */	
    uint8_t bPwdID,								/**< [In] Rassword ID. Indicates the type of the password to be written. */
    uint8_t * pbPwd,							/**< [In] Pointer to a buffer holding 4 bytes of password to be written.*/
    uint16_t * pwRespLen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * pbResp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the custom LOCK PASSWORD command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_LockPWD(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t bFlags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t bManCode,							/**< [In] 'IC Manufacturer code' of the VICC. */	
    uint8_t * pbUID,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint8_t bPWD_ID,							/**< [In] Rassword ID. Indicates the type of the password to be locked. */
    uint16_t * pwRespLen,						/**< [Out] Pointer to the length of the response buffer. */ 	
    uint8_t * pbResp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The  function executes the custom 64 BIT PASSWORD PROTECTION command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_64BitPWDProtection(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t bFlags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t bManCode,							/**< [In] 'IC Manufacturer code' of the VICC. */
    uint8_t * pbUID,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint16_t * pwRespLen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * pbResp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the custom PROTECT PAGE command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_ProtectPage(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t bFlags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t bManCode,							/**< [In] 'IC Manufacturer code' of the VICC. */
    uint8_t * pbUID,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */	
    uint8_t bPageNo,							/**< [In] Page number from the VICC's memory that shall be protected. */
    uint8_t bProtectionStatus, 					/**< [In] Protection status that shall be set. */
    uint16_t * pwRespLen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * pbResp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the custom LOCK PAGE PROTECTION CONDITIONS command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_LockPageProtectionCondition(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t bFlags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t bManCode,							/**< [In] 'IC Manufacturer code' of the VICC. */
    uint8_t * pbUID,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint8_t bPageNo,							/**< [In] Page number from the VICC's memory, whose protection coditions shall be locked. */
    uint16_t * pwRespLen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * pbResp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the custom DESTROY SLI-S command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \note The VICC returns a respose message and after that it get destroyed.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_DestroyS(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */  
    uint8_t bFlags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */	
    uint8_t bManCode,							/**< [In] 'IC Manufacturer code' of the VICC. */
    uint8_t * pbUID,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint16_t * pwRespLen,						/**< [Out] Pointer to the length of the response buffer. */ 
    uint8_t * pbResp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the custom INVENTORY PAGE READ command for VICCs with SLI-S tiype. 
Dependent on 'Number of time slots' flag, in the 'Flags' byte the command is executed for 1 or 16 time slots.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_InventoryReadS(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */  
    uint8_t bFlags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t bManCode,							/**< [In] 'IC Manufacturer code' of the VICC. */
    uint8_t bAFI,								/**< [In] Application Family ID byte,which is available only if 'AFI_flag' is set in the 'Flags' byte. */
    uint8_t bMaskLen,							/**< [In] Length of UID mask in number of valid bits. */
    uint8_t * pbUID,							/**< [In] Pointer to a buffer holding an UID mask. */
    uint8_t bBlockNo,							/**< [In] Address of the first pages, where the reading operation shall start. */
    uint8_t bNoOfBlocks,						/**< [In] Number of pages that shall be read from the inventorized VICCs */
    uint16_t * pwRespLen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * pbResp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the custom FAST INVENTORY PAGE READ command for VICCs with SLI-S tiype. 
Dependent on 'Number of time slots' flag, in the 'Flags' byte the command is executed for 1 or 16 time slots.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_FastInventoryReadS(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t bFlags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t bManCode,							/**< [In] 'IC Manufacturer code' of the VICC. */
    uint8_t bAFI,								/**< [In] Application Family ID byte,which is available only if 'AFI_flag' is set in the 'Flags' byte. */
    uint8_t bMaskLen,							/**< [In] Length of UID mask in number of valid bits. */
    uint8_t * pbUID,							/**< [In] Pointer to a buffer holding an UID mask. */
    uint8_t bBlockNo,							/**< [In] Page address, where the read operation starts. */
    uint8_t bNoOfBlocks,						/**< [In] Number of pages to read from the inventorized VICCs. */
    uint16_t * pwRespLen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * pbResp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the custom GET MULTIPLE BLOCK PROTECTION CONDITIONS command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_GetMultipleBlockProtStatus(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */ 
    uint8_t bFlags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t bManCode,							/**< [In] 'IC Manufacturer code' of the VICC. */ 
    uint8_t * pbUID,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */	
    uint8_t bFirstBlock,						/**< [In] Block address, where the write operation starts. */
    uint8_t bNoOfBlocks,						/**< [In] Number of blocks, which protection status shall be returned. */
    uint16_t * pwRespLen,						/**< [Out] Pointer to the length of the response buffer. */
    uint8_t * pbResp							/**< [Out] Pointer to the response buffer. */
    );

/**
* \brief The function executes the custom ENABLE PRIVACY command. 
The response buffer contains the return status byte of the FW fuction followed by the bytes received from VICC.
* \return Status code
* \retval #PH_ERR_SUCCESS Command is successfully executed. 
* \retval #PH_ERR_INTEGRITY_ERROR CRC or parity error.
* \retval #PH_ERR_FRAMING_ERROR Framing error occured during the transmit/recive operation.
* \retval #PH_ERR_IO_TIMEOUT No tag is present in the HF of the reader.
* \retval Other Invalid parameters or conditions - the error status is returned by an underlayed function.
*/
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_EnablePrivacy(
    phhalHw_Rd70x_DataParams_t * pDataParams,	/**< [In] Pointer to an initialized HAL parameter structure. */  
    uint8_t bFlags,								/**< [In] Command 'Flags' byte according to ISO15693-3. */
    uint8_t bManCode,							/**< [In] 'IC Manufacturer code' of the VICC. */
    uint8_t * pbUID,							/**< [In] Pointer to a buffer holding the UID of the referenced VICC. */
    uint16_t * pwRespLen,						/**< [Out] Pointer to the length of the response buffer. */ 
    uint8_t * pbResp							/**< [Out] Pointer to the response buffer. */
    );
/*@}*/

/** @} */
#endif /* NXPBUILD__PHHAL_HW_RD70X */

#ifdef __cplusplus
} /* Extern C */
#endif

#endif /* PHHALHW_RD70X_CMD_H */
