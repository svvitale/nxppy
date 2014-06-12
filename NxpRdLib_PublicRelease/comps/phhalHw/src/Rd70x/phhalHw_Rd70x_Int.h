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
* Internal definitions for Rd70x specific HAL-Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.5 $
* $Date: Fri Apr 15 09:04:41 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHHALHW_RD70X_INT_H
#define PHHALHW_RD70X_INT_H

#include <ph_Status.h>
#include <math.h>

/** \defgroup phhalHw_Rd70x_Int Internal
* \brief Internal definitions.
* @{
*/

#define PHHAL_HW_RD70X_TIMER_FREQ           13.56f              /**< RC internal timer frequency. */
#define PHHAL_HW_RD70X_TIMER_MAX_VALUE_US   39437592.0f         /**< RC maximum timer value in microseconds. */
#define PHHAL_HW_RD70X_ETU_106              1000.0f / 106.0f    /**< Duration of one ETU at 106 kBit/s in [us]. */

#define PHHAL_HW_RD70X_RX_OVERLAP_LEN_EX_BLOCK          5U  /**< Number of bytes which are to be overlapped for Exchange Block Rx-Buffering. */
#define PHHAL_HW_RD70X_RX_OVERLAP_LEN_EX_BITBYTE        6U  /**< Number of bytes which are to be overlapped for Exchange BitByte Rx-Buffering. */
#define PHHAL_HW_RD70X_RX_OVERLAP_LEN_EX_BITBYTE_MP     5U  /**< Number of bytes which are to be overlapped for Exchange BitByte Multiple Rx-Buffering. */

#define PHHAL_HW_RD70X_MODINDEX_I14443B     0x13U   /**< Default modulation index for ISO14443B. */
#define PHHAL_HW_RD70X_MODINDEX_EPCUID      0x03U   /**< Default modulation index for ICode EPC/UID. */
#define PHHAL_HW_RD70X_AUTHMODE_KEYA        0x60U   /**< MFC KeyA Authentication Mode. */
#define PHHAL_HW_RD70X_AUTHMODE_KEYB        0x61U   /**< MFC KeyA Authentication Mode. */
#define PHHAL_HW_RD70X_MAX_NUM_KEYS         16U     /**< Maximum possible number of keys in the EEPROM. */

#define PHHAL_HW_RD70X_RC632_CMD_IDLE           0x00U   /**< IDLE command code of ReaderIC. */
#define PHHAL_HW_RD70X_RC632_CMD_LOADKEY        0x19U   /**< LOADKEY command code of ReaderIC. */
#define PHHAL_HW_RD70X_RC632_CMD_LOADKEYE2      0x0BU   /**< LOADKEYE2 command code of ReaderIC. */
#define PHHAL_HW_RD70X_RC632_CMD_AUTHENT1       0x0CU   /**< AUTHENT1 command code of ReaderIC. */
#define PHHAL_HW_RD70X_RC632_CMD_AUTHENT2       0x14U   /**< AUTHENT2 command code of ReaderIC. */
#define	PHHAL_HW_RD70X_VALUE_FIFOSIZE			0x40U	/**< Buffer size of the FIFO. */
#define PHHAL_HW_RD70X_EEPROM_SIZE				0xFFFU	/**< EEPROM size of the RD70x chip. */
#define PHHAL_HW_RD70X_EEPROM_PAGE_SIZE			0x10U	/**< Size of a page in EEPROM. */
#define PHHAL_HW_RD70X_MAX_NUM_REGS				0x40U	/**< NUMBER of registers in RC632/Rd70x. */


/** \name Rd70x Error Codes
*/
/*@{*/
#define MI_OK                   0
#define MI_NOTAGERR             (-1)
#define MI_CRCERR               (-2)
#define MI_AUTHERR              (-4)
#define MI_PARITYERR            (-5)
#define MI_CODEERR              (-6)
#define MI_SERNRERR             (-8)
#define MI_BITCOUNTERR          (-11)
#define MI_BYTECOUNTERR         (-12)
#define MI_POLLING              (-20)
#define MI_FRAMINGERR           (-21)
#define MI_UNKNOWN_COMMAND      (-23)
#define MI_COLLERR              (-24)
#define MI_SENDBUF_OVERFLOW     (-53)
#define I1_TIMEOUT              (-70)
#define I2_NO_TAG               (1)
#define I2_CRCERR               (2)
#define I2_COLLERR              (3)
#define I2_SNRERR               (4)
#define I2_COUNTERR             (5)
#define I2_FRAMINGERR           (7)
/*@}*/

/** \name Low Level Command Codes
*/
/*@{*/
#define uC_Write                0x01
#define uC_Read                 0x02
#define uC_ExchangeByteStream   0x03
#define uC_WriteMultiple        0x04
#define uC_ReadMultiple         0x05
#define uC_ReadWord             0x06
/*@}*/

/** \name MIFARE Classic Command Codes
*/
/*@{*/
#define uC_PcdConfig            0x10
#define uC_PiccRequest          0x11
#define uC_PiccAnticoll         0x12
#define uC_PiccSelect           0x13
#define uC_PiccAuth             0x14
#define uC_PiccAuthE2           0x15
#define uC_HostCodeKey          0x16
#define uC_PcdLoadKeyE2         0x17
#define uC_PiccAuthKey          0x18
#define uC_PiccRead             0x19
#define uC_PiccWrite            0x1A
#define uC_PiccValue            0x1B
#define uC_PiccValueDebit       0x1C
#define uC_PiccHalt             0x1D
#define uC_PiccWrite4           0x1E
#define uC_PiccCommonWrite      0x1F
#define uC_PiccCommonRead       0x28
/*@}*/

/** \name Generic Command Codes
*/
/*@{*/
#define uC_PcdRfReset           0x20
#define uC_PcdReset             0x21
#define uC_PcdGetSnr            0x22
#define uC_PcdReadE2            0x23
#define uC_PcdWriteE2           0x24
#define uC_PcdSetIdleMode       0x25
#define uC_PcdClearIdleMode     0x26
#define uC_PcdSetTmo            0x27
/* 0x28 is reserved for uC_PiccCommonRead */
#define uC_PcdInitializeE2      0x29
/* 0x2A is reserved for uC_ActiveAntennaMasterConfig*/
/* 0x2B is reserved for uC_ActiveAntennaSlaveConfig*/
/*@}*/

/** \name Timing Command Codes
*/
/*@{*/
#define uC_HostTransTmrStart    0x30
#define uC_HostTransTmrStop     0x31
#define uC_HostGetExecutionTime 0x32
#define uC_HostTransTmrSteps    0x33
/*@}*/

/** \name ISO14443 Command Codes
*/
/*@{*/
#define uC_PiccCommonRequest            0x40
#define uC_PiccCascAnticoll             0x41
#define uC_PiccCascSelect               0x42
#define uC_PiccActivateIdle             0x43
#define uC_PiccActivateWakeup           0x44
#define uC_PcdSetDefaultAttrib          0x45
#define uC_PcdSetAttrib                 0x46
#define uC_PcdGetAttrib                 0x47
#define uC_PiccExchangeBlock            0x48
#define uC_PiccActivateIdleLoop         0x49
#define uC_PiccActivation               0x4A
#define uC_PcdEnableHighBaudRates       0x4B
#define uC_PiccExchangeBlockRfCycle     0x4C
#define uC_PiccExchangeBitByteRfCycle   0x4E
#define uC_PiccExchangeBitByte          0x4F
#define uC_PiccExchangeBitByteMultiple  0x3F
/*@}*/

/** \name Debug Command Codes
*/
/*@{*/
#define uC_SwitchLED            0x60
#define uC_FlashSnr             0x61
#define uC_StartDownload        0x62
#define uC_PcdGetFwVersion      0x63
#define uC_PcdGetRicVersion     0x64
#define uC_DbgTrigger           0x65
#define uC_MirrorData           0x66
#define uC_TestCmds             0x67
#define uC_RicTestAllRegs       0x70
#define uC_RicTestCard          0x71
#define uC_RicTestCommunication 0x72
/*@}*/

/** \name ICode1 Command Codes
*/
/*@{*/
#define uC_I1PcdConfig              0x80
#define uC_init_StdMode             0x81
#define uC_calc_tse_hash            0x82
#define uC_init_FastMode            0x83
#define uC_output_read              0x85
#define uC_output_anticoll_select   0x86
#define uC_I1_write                 0x87
#define uC_I1_halt                  0x88
#define uC_I1_eas                   0x89
#define uC_I1_reset_quiet_bit       0x8A
#define uC_I1PcdRfReset             0x8B
#define uc_SetBitPhase              0x8C
/*@}*/

/** \name ISO15693 Command Codes
*/
/*@{*/
#define uC_init_StdMode_15693                       0x90
#define uC_init_FastMode_15693                      0x91
#define uC_ISO15693_Read_sm                         0x92
#define uc_ISO15693_Inventory                       0x93
#define uC_ISO15693_Write_sm                        0x94
#define uC_ISO15693_Stay_Quiet                      0x95
#define uC_ISO15693_Lock_Block                      0x96
#define uC_ISO15693_Select                          0x97
#define uC_ISO15693_Reset_To_Ready                  0x98
#define uC_ISO15693_Write_AFI                       0x99
#define uC_ISO15693_Lock_AFI                        0x9A
#define uC_ISO15693_Write_DSFID                     0x9B
#define uC_ISO15693_Lock_DSFID                      0x9C
#define uC_ISO15693_Get_System_Information          0x9D
#define uC_ISO15693_Get_Multiple_Block_Security     0x9E
#define uC_ISO15693_Inventory_Read                  0x9F
#define uC_ISO15693_Fast_Inventory_Read             0xA0
#define uC_ISO15693_Set_Eas                         0xA1
#define uC_ISO15693_Reset_Eas                       0xA2
#define uC_ISO15693_Lock_Eas                        0xA3
#define uC_ISO15693_Eas_Alarm                       0xA4
#define uC_ISO15693_Pwd_Protect_EAS                 0xA5
#define uC_ISO15693_Write_EAS_ID                    0xA6
#define uC_ISO15693_Read_EPC                        0xA7
#define uC_ISO15693_Exchange                        0xA8
/*@}*/

/** \name ICode EPC/UID Command Codes
*/
/*@{*/
#define uC_EPC_PcdConfig        0xB0
#define uC_EPC_BeginRound       0xB1
#define uC_EPC_Write            0xB2
#define uC_EPC_Destroy          0xB3
#define uC_UID_PcdConfig        0xB8
#define uC_UID_BeginRound       0xB9
#define uC_UID_Write            0xBA
#define uC_UID_Destroy          0xBB
#define uC_UID_Exchange         0xBF
/*@}*/

/** \name ICode SLI Command Codes
*/
/*@{*/
#define uC_ISO15693_Get_Rnd                         0xC0
#define uC_ISO15693_Set_Pwd                         0xC1
#define uC_ISO15693_Write_Pwd                       0xC2
#define uC_ISO15693_Lock_Pwd                        0xC3
#define uC_ISO15693_64Bit_Pwd_Protection            0xC4
#define uC_ISO15693_Protect_Page                    0xC5
#define uC_ISO15693_Lock_Page_Protection_Condition  0xC6
#define uC_ISO15693_Get_Multi_Block_Prot_Status     0xC7
#define uC_ISO15693_S_Destroy                       0xC8
#define uC_ISO15693_Enable_Privacy                  0xC9
#define uC_ISO15693_S_Inventory_Read                0xCA
#define uC_ISO15693_S_Fast_Inventory_Read           0xCB
/*@}*/

/** \name ICode EPC / UID Exchange Options
*/
/*@{*/
#define PHHAL_HW_RD70X_EPCUID_OPTION_SSOF   0x00
#define PHHAL_HW_RD70X_EPCUID_OPTION_LSOF   0x01
#define PHHAL_HW_RD70X_EPCUID_OPTION_CS     0x02
/*@}*/

phStatus_t phhalHw_Rd70x_SendCommand(
                                     phhalHw_Rd70x_DataParams_t * pDataParams   /**< [In] Pointer to this layer's parameter structure. */
                                     );

void phhalHw_Rd70x_SetCommand(
                              phhalHw_Rd70x_DataParams_t * pDataParams,     /**< [In] Pointer to this layer's parameter structure. */
                              uint8_t bCmd                                  /**< [In] Command code. */
                              );

void phhalHw_Rd70x_AddParam_Uint8(
                                  phhalHw_Rd70x_DataParams_t * pDataParams,     /**< [In] Pointer to this layer's parameter structure. */
                                  uint8_t bData                                 /**< [In] Data. */
                                  );

void phhalHw_Rd70x_AddParam_Uint16(
                                   phhalHw_Rd70x_DataParams_t * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                                   uint16_t wData                               /**< [In] Data. */
                                   );

void phhalHw_Rd70x_AddParam_Uint32(
                                   phhalHw_Rd70x_DataParams_t * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                                   uint32_t dwData                              /**< [In] Data. */
                                   );

void phhalHw_Rd70x_AddParam_Buffer(
                                   phhalHw_Rd70x_DataParams_t * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                                   uint8_t * pData,                             /**< [In] Data buffer. */
                                   uint16_t wDataLen                            /**< [In] Length of data buffer. */
                                   );

phStatus_t phhalHw_Rd70x_GetStatus(
                                   phhalHw_Rd70x_DataParams_t * pDataParams     /**< [In] Pointer to this layer's parameter structure. */
                                   );

phStatus_t phhalHw_Rd70x_EvaluateStatus(
                                        uint8_t bStatus     /**< [In] Rd70x status byte. */
                                        );

void phhalHw_Rd70x_GetParam_Uint8(
                                  phhalHw_Rd70x_DataParams_t * pDataParams,     /**< [In] Pointer to this layer's parameter structure. */
                                  uint8_t * pData                               /**< [Out] Data. */
                                  );

void phhalHw_Rd70x_GetParam_Uint16(
                                   phhalHw_Rd70x_DataParams_t * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                                   uint16_t * pData                             /**< [Out] Data. */
                                   );

void phhalHw_Rd70x_GetParam_Uint32(
                                   phhalHw_Rd70x_DataParams_t * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                                   uint32_t * pData                             /**< [Out] Data. */
                                   );

void phhalHw_Rd70x_GetParam_Buffer(
                                   phhalHw_Rd70x_DataParams_t * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                                   uint16_t wDataLen,                           /**< [In] Length of data to fetch. */
                                   uint8_t * pData                              /**< [Out] Data. */
                                   );

void phhalHw_Rd70x_GetParam_BufferPointer(
    phhalHw_Rd70x_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
    uint8_t ** pData                            /**< [Out] Pointer to data. */
    );

/**
* \brief Write Data to Fifo buffer.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rd70x_WriteFifo(
                                   phhalHw_Rd70x_DataParams_t * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                                   uint8_t * pData,                             /**< [In] input data. */
                                   uint16_t wLength,                            /**< [In] length of input data. */
                                   uint16_t * pBytesWritten                     /**< [Out] Number of written bytes. */
                                   );

/**
* \brief Read Data from Fifo buffer.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rd70x_ReadFifo(
                                  phhalHw_Rd70x_DataParams_t * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
                                  uint16_t wBufSize,                        /**< [In] size of output buffer */
                                  uint8_t * pData,                          /**< [Out] output data */
                                  uint16_t * pLength                        /**< [Out] number of output data bytes */
                                  );

/**
* \brief Set neccessary TypeB registers.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phhalHw_Rd70x_SetTypeBRegs(
                                      phhalHw_Rd70x_DataParams_t * pDataParams  /**< [In] Pointer to this layer's parameter structure. */
                                      );

/** @}
* end of phhalHw_Rd70x_Internal group
*/

#endif /* PHHALHW_RD70X_INT_H */
