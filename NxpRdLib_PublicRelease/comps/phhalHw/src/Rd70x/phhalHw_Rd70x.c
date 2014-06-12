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
* RD700 specific HAL-Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.9 $
* $Date: Fri Apr 15 09:04:41 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/
#include <ph_Status.h>
#include <phbalReg.h>
#include <phhalHw.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PH_KEYSTORE
#include <phKeyStore.h>
#endif

#ifdef NXPBUILD__PHHAL_HW_RD70X

#include "phhalHw_Rd70x.h"
#include "phhalHw_Rd70x_Int.h"
#include <phhalHw_Rd70x_Cmd.h>

/* Default shadow for ISO14443-3A Mode */
static const uint16_t PH_MEMLOC_CONST_ROM wRd70x_DefaultShadow_14443a[][2] =
{
    {PHHAL_HW_CONFIG_PARITY,                PH_ON},
    {PHHAL_HW_CONFIG_TXCRC,                 PH_OFF},
    {PHHAL_HW_CONFIG_RXCRC,                 PH_OFF},
    {PHHAL_HW_CONFIG_RXDEAFBITS,            0x0008},
    {PHHAL_HW_CONFIG_TXDATARATE,            PHHAL_HW_RF_DATARATE_106},
    {PHHAL_HW_CONFIG_RXDATARATE,            PHHAL_HW_RF_DATARATE_106},
    {PHHAL_HW_CONFIG_ASK100,                PH_ON}
};

/* Default shadow for ISO14443-3B Mode */
static const uint16_t PH_MEMLOC_CONST_ROM wRd70x_DefaultShadow_14443b[][2] =
{
    {PHHAL_HW_CONFIG_PARITY,                PH_OFF},
    {PHHAL_HW_CONFIG_TXCRC,                 PH_ON},
    {PHHAL_HW_CONFIG_RXCRC,                 PH_ON},
    {PHHAL_HW_CONFIG_RXDEAFBITS,            0x0003},
    {PHHAL_HW_CONFIG_TXDATARATE,            PHHAL_HW_RF_DATARATE_106},
    {PHHAL_HW_CONFIG_RXDATARATE,            PHHAL_HW_RF_DATARATE_106},
    {PHHAL_HW_CONFIG_MODINDEX,              PHHAL_HW_RD70X_MODINDEX_I14443B},
    {PHHAL_HW_CONFIG_ASK100,                PH_OFF}
};

/* Default shadow for ISO15693 Mode */
static const uint16_t PH_MEMLOC_CONST_ROM wRd70x_DefaultShadow_15693[][2] =
{
    {PHHAL_HW_CONFIG_TXCRC,                 PH_ON},
    {PHHAL_HW_CONFIG_RXCRC,                 PH_ON},
    {PHHAL_HW_CONFIG_RXDEAFBITS,            0x0003},
    {PHHAL_HW_CONFIG_TXDATARATE,            PHHAL_HW_RF_TX_DATARATE_1_OUT_OF_4},
    {PHHAL_HW_CONFIG_RXDATARATE,            PHHAL_HW_RF_RX_DATARATE_HIGH},
    {PHHAL_HW_CONFIG_ASK100,                PH_ON}
};

/* Default shadow for ICode EPC/UID Mode */
static const uint16_t PH_MEMLOC_CONST_ROM wRd70x_DefaultShadow_ICodeEpcUid[][2] =
{
    {PHHAL_HW_CONFIG_TXCRC,                 PH_OFF},
    {PHHAL_HW_CONFIG_RXCRC,                 PH_OFF},
    {PHHAL_HW_CONFIG_RXDEAFBITS,            0x0006},
    {PHHAL_HW_CONFIG_MODINDEX,              PHHAL_HW_RD70X_MODINDEX_EPCUID},
    {PHHAL_HW_CONFIG_ASK100,                PH_OFF}
};

phStatus_t phhalHw_Rd70x_Init(
                              phhalHw_Rd70x_DataParams_t * pDataParams,
                              uint16_t wSizeOfDataParams,
                              phbalReg_Rd70xUsbWin_DataParams_t * pBalDataParams,
                              uint8_t * pTxBuffer,
                              uint16_t wTxBufSize,
                              uint8_t * pRxBuffer,
                              uint16_t wRxBufSize
                              )
{
    if (sizeof(phhalHw_Rd70x_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_HAL);
    }
    PH_ASSERT_NULL (pDataParams);
    PH_ASSERT_NULL (pBalDataParams);
    PH_ASSERT_NULL (pTxBuffer);
    PH_ASSERT_NULL (pRxBuffer);

    /* Init. private data */
    pDataParams->wId                    = PH_COMP_HAL | PHHAL_HW_RD70X_ID;
    pDataParams->pBalDataParams         = pBalDataParams;
    pDataParams->pTxBuffer              = pTxBuffer;
    pDataParams->wTxBufSize             = wTxBufSize;
    pDataParams->wTxBufLen              = 0;
    pDataParams->pRxBuffer              = pRxBuffer;
    pDataParams->wRxBufSize             = wRxBufSize;
    pDataParams->wRxBufLen              = 0;
    pDataParams->wRxBufStartPos         = 0;
    pDataParams->wTxBufStartPos         = 0;
    pDataParams->bCardType              = PHHAL_HW_CARDTYPE_ISO14443A;
    pDataParams->wTimingMode            = PHHAL_HW_TIMING_MODE_OFF;
    pDataParams->dwTimeoutUs            = PHHAL_HW_RD70X_DEFAULT_TIMEOUT_MS * 1000;
    pDataParams->dwTimingUs             = 0;
    pDataParams->wAdditionalInfo        = 0;
    pDataParams->wTxRxStartBackup       = 0;
    pDataParams->wFieldOffTime          = PHHAL_HW_FIELD_OFF_DEFAULT;
    pDataParams->wFieldRecoveryTime     = PHHAL_HW_FIELD_RECOVERY_DEFAULT;
    pDataParams->bSymbolStart           = PH_OFF;
    pDataParams->bSymbolEnd             = PH_OFF;
    pDataParams->bDisablePcdReset       = PH_OFF;
    pDataParams->bFlags                 = 0;
    pDataParams->bProtBufferLen         = 0;
    pDataParams->wProtRxBufReadPos      = 0;
    pDataParams->bRfResetAfterTo        = PH_OFF;

    /* Verify exchange buffers */
    if (wTxBufSize == 0 || wRxBufSize == 0)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd70x_Exchange(
                                  phhalHw_Rd70x_DataParams_t * pDataParams,
                                  uint16_t wOption,
                                  uint8_t * pTxBuffer,
                                  uint16_t wTxLength,
                                  uint8_t ** ppRxBuffer,
                                  uint16_t * pRxLength
                                  )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t    PH_MEMLOC_REM wPosition;
    uint8_t     PH_MEMLOC_REM bOption;
    uint8_t     PH_MEMLOC_REM bReg;
    uint32_t    PH_MEMLOC_REM dwTimeoutEtu;
    uint32_t    PH_MEMLOC_REM dwTimingSingle;
    uint8_t     PH_MEMLOC_REM bRxLastBits = 0;
    uint16_t	PH_MEMLOC_REM RxLength;
    uint8_t *	PH_MEMLOC_REM pRxBuffer;

    /* Check options */
    if ((wOption & (uint16_t)~(uint16_t)(PH_EXCHANGE_BUFFERED_BIT | PH_EXCHANGE_LEAVE_BUFFER_BIT)) != 0x0000)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Check if caller has provided valid RxBuffer */
    if (ppRxBuffer == NULL)
    {
        ppRxBuffer = &pRxBuffer;
    }
    if (pRxLength == NULL)
    {
        pRxLength = &RxLength;
    }

    /* clear internal buffer if requested */
    if (!(wOption & PH_EXCHANGE_LEAVE_BUFFER_BIT))
    {
        pDataParams->wTxBufLen = 0;
    }

    /* Calculate start position */
    wPosition = PHHAL_HW_RD70X_RESERVED_BUFFER_LEN + pDataParams->wTxBufStartPos + pDataParams->wTxBufLen;

    /* Buffer overflow check */
    if ((wPosition + wTxLength) > pDataParams->wTxBufSize)
    {
        pDataParams->wTxBufLen = 0;
        return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
    }

    /* Copy transmit buffer*/
    memcpy(&pDataParams->pTxBuffer[wPosition], pTxBuffer, wTxLength);  /* PRQA S 3200 */
    pDataParams->wTxBufLen = pDataParams->wTxBufLen + wTxLength;

    /* Shall we already perform the Exchange? */
    if (wOption & PH_EXCHANGE_BUFFERED_BIT)
    {
        return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
    }

    /* Prepare timing measurement */
    if ((pDataParams->wTimingMode & (uint16_t)~(uint16_t)PHHAL_HW_TIMING_MODE_OPTION_MASK) == PHHAL_HW_TIMING_MODE_COMM)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_HostTransTmrSetCMDCount(pDataParams, 1));
    }

    /* Perform the actual exchange */
    switch (pDataParams->bCardType)
    {
    case PHHAL_HW_CARDTYPE_ISO15693:

        /* Read Coder-Control register*/
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(
            pDataParams,
            PHHAL_HW_RD70X_REG_CODER_CONTROL,
            &bReg));

        /* Enable SendOnePulse if requested */
        if (pDataParams->bSymbolStart == PH_OFF)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(
                pDataParams,
                PHHAL_HW_RD70X_REG_CODER_CONTROL,
                bReg | PHHAL_HW_RD70X_BIT_SENDONEPULSE));
        }

        /* Perform actual exchange */
        status = phhalHw_Rd70x_Cmd_ISO15693_Exchange(
            pDataParams,
            NULL,
            pDataParams->wTxBufLen,
            ppRxBuffer,
            pRxLength);

        /* Disable SendOnePulse if enabled before */
        if (pDataParams->bSymbolStart == PH_OFF)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(
                pDataParams,
                PHHAL_HW_RD70X_REG_CODER_CONTROL,
                (bReg & (uint8_t)~(uint8_t)PHHAL_HW_RD70X_BIT_SENDONEPULSE)));
        }

        break;

    case PHHAL_HW_CARDTYPE_ICODEEPCUID:

        /* Evaluate start symbol */
        switch (pDataParams->bSymbolStart)
        {
        case PHHAL_HW_SYMBOL_ICODEEPCUID_SSOF:
            bOption = PHHAL_HW_RD70X_EPCUID_OPTION_SSOF;
            break;
        case PHHAL_HW_SYMBOL_ICODEEPCUID_LSOF:
            bOption = PHHAL_HW_RD70X_EPCUID_OPTION_LSOF;
            break;
        case PHHAL_HW_SYMBOL_ICODEEPCUID_CS:
            bOption = PHHAL_HW_RD70X_EPCUID_OPTION_CS;
            break;
        default:
            return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
        }

        status = phhalHw_Rd70x_Cmd_EPCUID_Exchange(
            pDataParams,
            bOption,
            NULL,
            pDataParams->wTxBufLen,
            (uint8_t)pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXLASTBITS],
            ppRxBuffer,
            pRxLength);

        break;

    case PHHAL_HW_CARDTYPE_ISO14443A:
    case PHHAL_HW_CARDTYPE_ISO14443B:
        /* Calculate timeout in ETUs */
        dwTimeoutEtu = (uint32_t)((float32_t)pDataParams->dwTimeoutUs / (PHHAL_HW_RD70X_ETU_106 / (float32_t)(pDataParams->wCfgShadow[PHHAL_HW_CONFIG_RXDATARATE] + 1)));
        if (dwTimeoutEtu == 0)
        {
            ++dwTimeoutEtu;
        }

        /* Perform actual exchange*/
        if (pDataParams->bRfResetAfterTo == PH_ON)
        {
            status = phhalHw_Rd70x_Cmd_PiccExchgBitByteRfCycle(
                pDataParams,
                NULL,
                pDataParams->wTxBufLen,
                (uint8_t)pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXLASTBITS],
                ppRxBuffer,
                pRxLength,
                &bRxLastBits,
                pDataParams->bFlags,
                dwTimeoutEtu);
        }
        else
        {
            status = phhalHw_Rd70x_Cmd_PiccExchgBitByte(
                pDataParams,
                NULL,
                pDataParams->wTxBufLen,
                (uint8_t)pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXLASTBITS],
                ppRxBuffer,
                pRxLength,
                &bRxLastBits,
                pDataParams->bFlags,
                dwTimeoutEtu);
        }

        /* Save RxLastBits */
        pDataParams->wAdditionalInfo = (uint16_t)bRxLastBits;
        break;

    default:
        return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_HAL);
    }

    /* Retrieve timing */
    if ((pDataParams->wTimingMode & (uint16_t)~(uint16_t)PHHAL_HW_TIMING_MODE_OPTION_MASK) == PHHAL_HW_TIMING_MODE_COMM)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_HostGetExecutionTime(pDataParams, &dwTimingSingle));

        if (pDataParams->wTimingMode & PHHAL_HW_TIMING_MODE_OPTION_AUTOCLEAR)
        {
            pDataParams->dwTimingUs = dwTimingSingle;
        }
        else
        {
            /* Check for overflow */
            if ((0xFFFFFFFF - pDataParams->dwTimingUs) < dwTimingSingle)
            {
                pDataParams->dwTimingUs = 0xFFFFFFFF;
            }
            /* Update global timing value */
            else
            {
                pDataParams->dwTimingUs = pDataParams->dwTimingUs + dwTimingSingle;
            }
        }
    }

    /* Return correct data length */
    *ppRxBuffer -= pDataParams->wRxBufStartPos;
    *pRxLength = *pRxLength + pDataParams->wRxBufStartPos;

    /* Store RxBufLen in DataParams */
    pDataParams->wRxBufLen = *pRxLength;

    /* Reset TxLastBits */
    pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXLASTBITS] = 0;

    /* Reset buffered bytes */
    pDataParams->wTxBufLen = 0;

    /* Incomplete byte check */
    if (((status & PH_ERR_MASK) == PH_ERR_SUCCESS) && (bRxLastBits != 0))
    {
        status = PH_ADD_COMPCODE(PH_ERR_SUCCESS_INCOMPLETE_BYTE, PH_COMP_HAL);
    }

    /* Buffer Overflow mapping */
    if ((status & PH_ERR_MASK) == PH_ERR_BUFFER_OVERFLOW)
    {
        status = PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
    }

    /* Firmware only has 1ms recovery-time, wait the remaining time */
    if ((status & PH_ERR_MASK) == PH_ERR_IO_TIMEOUT)
    {
        if ((pDataParams->bRfResetAfterTo != PH_OFF) && (pDataParams->wFieldRecoveryTime > 1))
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Wait(
                pDataParams,
                PHHAL_HW_TIME_MILLISECONDS,
                pDataParams->wFieldRecoveryTime - 1));
        }
    }

    return status;
}

phStatus_t phhalHw_Rd70x_WriteRegister(
                                       phhalHw_Rd70x_DataParams_t * pDataParams,
                                       uint8_t bAddress,
                                       uint8_t bValue
                                       )
{    
    return phhalHw_Rd70x_Cmd_WriteRC(pDataParams, bAddress, bValue);
}

phStatus_t phhalHw_Rd70x_ReadRegister(
                                      phhalHw_Rd70x_DataParams_t * pDataParams,
                                      uint8_t bAddress,
                                      uint8_t * pValue
                                      )
{    
    return phhalHw_Rd70x_Cmd_ReadRC(pDataParams, bAddress, pValue);
}

phStatus_t phhalHw_Rd70x_ApplyProtocolSettings(
    phhalHw_Rd70x_DataParams_t * pDataParams,
    uint8_t bCardType
    )
{    
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t    PH_MEMLOC_COUNT wIndex;
    uint16_t *  PH_MEMLOC_REM pShadowDefault;
    uint16_t    PH_MEMLOC_REM wShadowCount;
    uint8_t     PH_MEMLOC_REM bUseDefaultShadow;
    uint16_t    PH_MEMLOC_REM wConfig;
    uint8_t     PH_MEMLOC_REM bSerialNo[4];

    /* Store new card type */
    if (bCardType != PHHAL_HW_CARDTYPE_CURRENT)
    {
        pDataParams->bCardType = bCardType;
        bUseDefaultShadow = 1;
    }
    else
    {
        bUseDefaultShadow = 0;
    }

    /* configure reader IC for current card */
    switch (pDataParams->bCardType)
    {
        /* configure hardware for ISO 14443 */
    case PHHAL_HW_CARDTYPE_ISO14443A:
    case PHHAL_HW_CARDTYPE_ISO14443B:

        if (!pDataParams->bDisablePcdReset)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_PcdConfig(pDataParams));
            if (bCardType != PHHAL_HW_CARDTYPE_CURRENT)
            {
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_PcdGetSnr(pDataParams, bSerialNo));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_PcdEnableHighBaudRates(pDataParams, bSerialNo));
            }
        }

        /* TypeA specific */
        if (pDataParams->bCardType == PHHAL_HW_CARDTYPE_ISO14443A)
        {
            /* Use 14443a default shadow */
            pShadowDefault = (uint16_t*)wRd70x_DefaultShadow_14443a;
            wShadowCount = sizeof(wRd70x_DefaultShadow_14443a) / (sizeof(uint16_t) * 2);

            /* Write CRCPreset(LSB) Register */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(
                pDataParams,
                PHHAL_HW_RD70X_REG_CRC_PRESET_LSB,
                0x63));

            /* Write CRCPreset(MSB) Register */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(
                pDataParams,
                PHHAL_HW_RD70X_REG_CRC_PRESET_MSB,
                0x63));
        }
        /* TypeB specific */
        else
        {
            /* Use 14443b default shadow */
            pShadowDefault = (uint16_t*)wRd70x_DefaultShadow_14443b;
            wShadowCount = sizeof(wRd70x_DefaultShadow_14443b) / (sizeof(uint16_t) * 2);

            /* Write CRCPreset(LSB) Register */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(
                pDataParams,
                PHHAL_HW_RD70X_REG_CRC_PRESET_LSB,
                0xFF));

            /* Write CRCPreset(MSB) Register */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(
                pDataParams,
                PHHAL_HW_RD70X_REG_CRC_PRESET_MSB,
                0xFF));
        }
        break;

    case PHHAL_HW_CARDTYPE_ISO15693:

        if (!pDataParams->bDisablePcdReset)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_I1PcdConfig(pDataParams));
        }

        /* Use 15693 default shadow */
        pShadowDefault = (uint16_t*)wRd70x_DefaultShadow_15693;
        wShadowCount = sizeof(wRd70x_DefaultShadow_15693) / (sizeof(uint16_t) * 2);

        /* Set default SOF */
        pDataParams->bSymbolStart = PHHAL_HW_SYMBOL_I15693_SOF;

        break;

    case PHHAL_HW_CARDTYPE_ICODEEPCUID:

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_I1PcdConfig(pDataParams));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_UIDPcdConfig(pDataParams));

        /* Use ICode EPC/UID default shadow */
        pShadowDefault = (uint16_t*)wRd70x_DefaultShadow_ICodeEpcUid;
        wShadowCount = sizeof(wRd70x_DefaultShadow_ICodeEpcUid) / (sizeof(uint16_t) * 2);

        /* Set default SOF */
        pDataParams->bSymbolStart = PHHAL_HW_SYMBOL_ICODEEPCUID_SSOF;

        break;

    default:

        return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_HAL);
    }

    /* Initialize config shadow */
    if (bCardType != PHHAL_HW_CARDTYPE_CURRENT)
    {
        memset(pDataParams->wCfgShadow, 0x00, PHHAL_HW_RD70X_SHADOW_COUNT);  /* PRQA S 3200 */
    }

    /* Apply shadowed registers */
    for (wIndex = 0; wIndex < wShadowCount; ++wIndex)
    {
        /* Get wConfig */
        wConfig = pShadowDefault[wIndex << 1];

        /* Default shadow: */
        if (bUseDefaultShadow)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_SetConfig(pDataParams, wConfig, pShadowDefault[(wIndex << 1) + 1]));
        }
        /* Current shadow: */
        else
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_SetConfig(pDataParams, wConfig, pDataParams->wCfgShadow[wConfig]));
        }
    }

    /* Apply default timeout if neccessary */
    if (bUseDefaultShadow)
    {
        pDataParams->dwTimeoutUs = PHHAL_HW_RD70X_DEFAULT_TIMEOUT_MS * 1000;
    }

    /* MIFARE Crypto1 state is disabled by default */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams, PHHAL_HW_CONFIG_DISABLE_MF_CRYPTO1, PH_ON));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd70x_SetConfig(
                                   phhalHw_Rd70x_DataParams_t * pDataParams,
                                   uint16_t wConfig,
                                   uint16_t wValue
                                   )
{    

    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bBackup;
    uint8_t     PH_MEMLOC_REM bValue;
    uint16_t    PH_MEMLOC_REM wOtherDataRate;

    switch (wConfig)
    {
    case PHHAL_HW_CONFIG_PARITY:

        /* Update the flags (enabled is disabled in this case) */
        if (wValue == PH_OFF)
        {
            pDataParams->bFlags |= PHHAL_HW_RD70X_BIT_ENABLE_PARITY;
        }
        else
        {
            pDataParams->bFlags &= (uint8_t)~(uint8_t)PHHAL_HW_RD70X_BIT_ENABLE_PARITY;
        }

        /* Directly change the the register for protocols which are not using ExchangeBitByte with flags */
        if ((pDataParams->bCardType != PHHAL_HW_CARDTYPE_ISO14443A) && (pDataParams->bCardType != PHHAL_HW_CARDTYPE_ISO14443B))
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_CHANNEL_REDUND, &bBackup));

            if (wValue == PH_OFF)
            {
                bValue = bBackup & (uint8_t)~(uint8_t)PHHAL_HW_RD70X_BIT_ENABLE_PARITY;
            }
            else
            {
                bValue = bBackup | PHHAL_HW_RD70X_BIT_ENABLE_PARITY;
            }

            /* Only perform the operation, if the new value is different */
            if (bValue != bBackup)
            {
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_CHANNEL_REDUND, bBackup));
            }
        }

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;

        break;

    case PHHAL_HW_CONFIG_TXCRC:

        /* Update the flags (enabled is disabled in this case) */
        if (wValue == PH_OFF)
        {
            pDataParams->bFlags |= PHHAL_HW_RD70X_BIT_ENABLE_TXCRC;
        }
        else
        {
            pDataParams->bFlags &= (uint8_t)~(uint8_t)PHHAL_HW_RD70X_BIT_ENABLE_TXCRC;
        }

        /* Directly change the the register for protocols which are not using ExchangeBitByte with flags */
        if ((pDataParams->bCardType != PHHAL_HW_CARDTYPE_ISO14443A) && (pDataParams->bCardType != PHHAL_HW_CARDTYPE_ISO14443B))
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_CHANNEL_REDUND, &bBackup));

            if (wValue == PH_OFF)
            {
                bValue = bBackup & (uint8_t)~(uint8_t)PHHAL_HW_RD70X_BIT_ENABLE_TXCRC;
            }
            else
            {
                bValue = bBackup | PHHAL_HW_RD70X_BIT_ENABLE_TXCRC;
            }

            /* Only perform the operation, if the new value is different */
            if (bValue != bBackup)
            {
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_CHANNEL_REDUND, bBackup));
            }
        }

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;

        break;

    case PHHAL_HW_CONFIG_RXCRC:

        /* Update the flags (enabled is disabled in this case) */
        if (wValue == PH_OFF)
        {
            pDataParams->bFlags |= PHHAL_HW_RD70X_BIT_ENABLE_RXCRC;
        }
        else
        {
            pDataParams->bFlags &= (uint8_t)~(uint8_t)PHHAL_HW_RD70X_BIT_ENABLE_RXCRC;
        }

        /* Directly change the the register for protocols which are not using ExchangeBitByte with flags */
        if ((pDataParams->bCardType != PHHAL_HW_CARDTYPE_ISO14443A) && (pDataParams->bCardType != PHHAL_HW_CARDTYPE_ISO14443B))
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_CHANNEL_REDUND, &bBackup));

            if (wValue == PH_OFF)
            {
                bValue = bBackup & (uint8_t)~(uint8_t)PHHAL_HW_RD70X_BIT_ENABLE_RXCRC;
            }
            else
            {
                bValue = bBackup | PHHAL_HW_RD70X_BIT_ENABLE_RXCRC;
            }

            /* Only perform the operation, if the new value is different */
            if (bValue != bBackup)
            {
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_CHANNEL_REDUND, bBackup));
            }
        }

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;

        break;

    case PHHAL_HW_CONFIG_TXLASTBITS:

        /* check parameter */
        if (wValue > 7)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;

        break;

    case PHHAL_HW_CONFIG_RXALIGN:

        /* check parameter */
        if (wValue > 7)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_BIT_FRAMING, &bBackup));

        /* adjust register */
        bBackup &= (uint8_t)~(uint8_t)0x70;
        bBackup |= (uint8_t)(wValue << 4);

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_BIT_FRAMING, bBackup));

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;

        break;

    case PHHAL_HW_CONFIG_RXDEAFBITS:

        /* check parameter */
        if (wValue > 0xFF)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_RX_WAIT, (uint8_t)wValue));

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;

        break;

    case PHHAL_HW_CONFIG_CLEARBITSAFTERCOLL:

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_DECODER_CONTROL, &bBackup));

        if (wValue)
        {
            bValue = bBackup | PHHAL_HW_RD70X_BIT_ZEROAFTERCOLL;
        }
        else
        {
            bValue = bBackup & (uint8_t)~(uint8_t)PHHAL_HW_RD70X_BIT_ZEROAFTERCOLL;
        }

        /* Only perform the operation, if the new value is different */
        if (bValue != bBackup)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_DECODER_CONTROL, bBackup));
        }

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;
        break;

    case PHHAL_HW_CONFIG_TXDATARATE:

        if (pDataParams->bCardType == PHHAL_HW_CARDTYPE_ISO15693)
        {
            switch (wValue)
            {
            case PHHAL_HW_RF_TX_DATARATE_1_OUT_OF_256:
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_I2init_StdMode_15693(pDataParams));
                break;
            case PHHAL_HW_RF_TX_DATARATE_1_OUT_OF_4:
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_I2init_FastMode_15693(pDataParams));
                break;
            case PHHAL_HW_RF_DATARATE_106:
            case PHHAL_HW_RF_DATARATE_212:
            case PHHAL_HW_RF_DATARATE_424:
            case PHHAL_HW_RF_DATARATE_848:
                return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_HAL);
            default:
                return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
            }
        }
        else if (
            (pDataParams->bCardType == PHHAL_HW_CARDTYPE_ISO14443A) ||
            (pDataParams->bCardType == PHHAL_HW_CARDTYPE_ISO14443B))
        {
            switch (wValue)
            {
            case PHHAL_HW_RF_TX_DATARATE_1_OUT_OF_256:
            case PHHAL_HW_RF_TX_DATARATE_1_OUT_OF_4:
            case PHHAL_HW_RF_RX_DATARATE_LOW:
            case PHHAL_HW_RF_RX_DATARATE_HIGH:
            case PHHAL_HW_RF_RX_DATARATE_FAST_LOW:
            case PHHAL_HW_RF_RX_DATARATE_FAST_HIGH:
                return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_HAL);
            case PHHAL_HW_RF_DATARATE_106:
            case PHHAL_HW_RF_DATARATE_212:
            case PHHAL_HW_RF_DATARATE_424:
            case PHHAL_HW_RF_DATARATE_848:
                wOtherDataRate = pDataParams->wCfgShadow[PHHAL_HW_CONFIG_RXDATARATE];
                if (wOtherDataRate > PHHAL_HW_RF_DATARATE_848)
                {
                    wOtherDataRate = wValue;
                }
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_PcdSetAttrib(
                    pDataParams,
                    (uint8_t)wOtherDataRate,
                    (uint8_t)wValue));
                break;
            default:
                return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
            }
        }
        else
        {
            return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_HAL);
        }

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;

        /* Set TypeB Registers */
        if (pDataParams->bCardType == PHHAL_HW_CARDTYPE_ISO14443B)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_SetTypeBRegs(pDataParams));
        }
        break;

    case PHHAL_HW_CONFIG_RXDATARATE:

        if (pDataParams->bCardType == PHHAL_HW_CARDTYPE_ISO15693)
        {
            switch (wValue)
            {
                /* Fast data-rate */
            case PHHAL_HW_RF_RX_DATARATE_FAST_HIGH:
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_RX_CONTROL1, &bValue));
                bValue &= (uint8_t)~(uint8_t)PHHAL_HW_RD70X_MASK_SUBCPULSES;
                bValue |= PHHAL_HW_RD70X_BITS_SUBCPULSES_8;
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_RX_CONTROL1, bValue));
                break;
                /* High data-rate */
            case PHHAL_HW_RF_RX_DATARATE_HIGH:
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_RX_CONTROL1, &bValue));
                bValue &= (uint8_t)~(uint8_t)PHHAL_HW_RD70X_MASK_SUBCPULSES;
                bValue |= PHHAL_HW_RD70X_BITS_SUBCPULSES_16;
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_RX_CONTROL1, bValue));
                break;
                /* Pegoda does not support 15693 Low Datarate*/
            case PHHAL_HW_RF_RX_DATARATE_LOW:
            case PHHAL_HW_RF_RX_DATARATE_FAST_LOW:
                return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_HAL);
            case PHHAL_HW_RF_DATARATE_106:
            case PHHAL_HW_RF_DATARATE_212:
            case PHHAL_HW_RF_DATARATE_424:
            case PHHAL_HW_RF_DATARATE_848:
                return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_HAL);
            default:
                return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
            }
        }
        else if (
            (pDataParams->bCardType == PHHAL_HW_CARDTYPE_ISO14443A) ||
            (pDataParams->bCardType == PHHAL_HW_CARDTYPE_ISO14443B))
        {
            switch (wValue)
            {
            case PHHAL_HW_RF_TX_DATARATE_1_OUT_OF_256:
            case PHHAL_HW_RF_TX_DATARATE_1_OUT_OF_4:
            case PHHAL_HW_RF_RX_DATARATE_LOW:
            case PHHAL_HW_RF_RX_DATARATE_HIGH:
            case PHHAL_HW_RF_RX_DATARATE_FAST_LOW:
            case PHHAL_HW_RF_RX_DATARATE_FAST_HIGH:
                return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_HAL);
            case PHHAL_HW_RF_DATARATE_106:
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_RX_CONTROL1, &bValue));
                bValue &= (uint8_t)~(uint8_t)PHHAL_HW_RD70X_MASK_SUBCPULSES;
                bValue |= PHHAL_HW_RD70X_BITS_SUBCPULSES_8;
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_RX_CONTROL1, bValue));
                break;
            case PHHAL_HW_RF_DATARATE_212:
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_RX_CONTROL1, &bValue));
                bValue &= (uint8_t)~(uint8_t)PHHAL_HW_RD70X_MASK_SUBCPULSES;
                bValue |= PHHAL_HW_RD70X_BITS_SUBCPULSES_4;
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_RX_CONTROL1, bValue));
                break;
            case PHHAL_HW_RF_DATARATE_424:
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_RX_CONTROL1, &bValue));
                bValue &= (uint8_t)~(uint8_t)PHHAL_HW_RD70X_MASK_SUBCPULSES;
                bValue |= PHHAL_HW_RD70X_BITS_SUBCPULSES_2;
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_RX_CONTROL1, bValue));
                break;
            case PHHAL_HW_RF_DATARATE_848:
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_RX_CONTROL1, &bValue));
                bValue &= (uint8_t)~(uint8_t)PHHAL_HW_RD70X_MASK_SUBCPULSES;
                bValue |= PHHAL_HW_RD70X_BITS_SUBCPULSES_1;
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_RX_CONTROL1, bValue));
                break;
            default:
                return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
            }

            /* Perform SetAttrib */
            wOtherDataRate = pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXDATARATE];
            if (wOtherDataRate > PHHAL_HW_RF_DATARATE_848)
            {
                wOtherDataRate = wValue;
            }
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_PcdSetAttrib(
                pDataParams,
                (uint8_t)wValue,
                (uint8_t)wOtherDataRate));
        }
        else
        {
            return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_HAL);
        }

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;

        /* Set TypeB Registers */
        if (pDataParams->bCardType == PHHAL_HW_CARDTYPE_ISO14443B)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_SetTypeBRegs(pDataParams));
        }
        break;

    case PHHAL_HW_CONFIG_MODINDEX:

        /* Set ModConductance register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(
            pDataParams,
            PHHAL_HW_RD70X_REG_MOD_COND,
            (uint8_t)(wValue & 0x3F)));

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;
        break;

    case PHHAL_HW_CONFIG_ASK100:

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_TXCONTROL, &bValue));

        /* switch on 100% ASK */
        if (wValue != PH_OFF)
        {
            bValue |= PHHAL_HW_RD70X_BIT_FORCE_100ASK;
        }
        /* switch off 100% ASK */
        else
        {
            bValue &= (uint8_t)~(uint8_t)PHHAL_HW_RD70X_BIT_FORCE_100ASK;
        }

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_TXCONTROL, bValue));

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;
        break;

    case PHHAL_HW_CONFIG_TIMEOUT_VALUE_US:

        pDataParams->dwTimeoutUs = (uint32_t)wValue;
        break;

    case PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS:

        pDataParams->dwTimeoutUs = (uint32_t)(wValue * 1000);
        break;

    case PHHAL_HW_CONFIG_TIMING_MODE:

        /* Check supported option bits */
        switch (wValue & PHHAL_HW_TIMING_MODE_OPTION_MASK)
        {
        case PHHAL_HW_TIMING_MODE_OPTION_DEFAULT:
        case PHHAL_HW_TIMING_MODE_OPTION_AUTOCLEAR:
            break;
        default:
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        /* Check supported timing modes */
        switch (wValue & (uint16_t)~(uint16_t)PHHAL_HW_TIMING_MODE_OPTION_MASK)
        {
        case PHHAL_HW_TIMING_MODE_OFF:
        case PHHAL_HW_TIMING_MODE_COMM:
            pDataParams->dwTimingUs = 0;
            pDataParams->wTimingMode = wValue;
            break;
        case PHHAL_HW_TIMING_MODE_FDT:
            return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_HAL);
        default:
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        break;

    case PHHAL_HW_CONFIG_FIELD_OFF_TIME:

        /* Parameter Check */
        if (wValue == 0)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        /* Store config data */
        pDataParams->wFieldOffTime = wValue;
        break;

    case PHHAL_HW_CONFIG_FIELD_RECOVERY_TIME:

        /* Store config data */
        pDataParams->wFieldRecoveryTime = wValue;
        break;

    case PHHAL_HW_CONFIG_SYMBOL_START:

        /* Parameter check */
        if ((pDataParams->bCardType != PHHAL_HW_CARDTYPE_ICODEEPCUID) &&
            (pDataParams->bCardType != PHHAL_HW_CARDTYPE_ISO15693))
        {
            return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_HAL);
        }

        /* Parameter check #2 */
        switch (wValue)
        {
        case PHHAL_HW_SYMBOL_ICODEEPCUID_SSOF:
        case PHHAL_HW_SYMBOL_ICODEEPCUID_LSOF:
        case PHHAL_HW_SYMBOL_ICODEEPCUID_CS:
            if (pDataParams->bCardType != PHHAL_HW_CARDTYPE_ICODEEPCUID)
            {
                return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
            }
            break;
        case PHHAL_HW_SYMBOL_I15693_SOF:
            if (pDataParams->bCardType != PHHAL_HW_CARDTYPE_ISO15693)
            {
                return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
            }
            break;
        case PH_OFF:
            break;
        default:
            return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_HAL);
        }

        /* Store Start-Symbol */
        pDataParams->bSymbolStart = (uint8_t)wValue;
        break;

    case PHHAL_HW_CONFIG_SYMBOL_END:

        /* Parameter check */
        if (pDataParams->bCardType != PHHAL_HW_CARDTYPE_ICODEEPCUID)
        {
            return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_HAL);
        }

        /* Parameter check #2 */
        switch (wValue)
        {
        case PHHAL_HW_SYMBOL_ICODEEPCUID_CEOF:
        case PH_OFF:
            break;
        default:
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        /* Store End-Symbol */
        pDataParams->bSymbolEnd = (uint8_t)wValue;
        break;

    case PHHAL_HW_CONFIG_SUBCARRIER:

        if (wValue != PHHAL_HW_SUBCARRIER_SINGLE)
        {
            if (wValue > PHHAL_HW_SUBCARRIER_QUAD)
            {
                return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
            }
            else
            {
                return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_HAL);
            }
        }
        break;

    case PHHAL_HW_CONFIG_RXBUFFER_STARTPOS:

        /* Boundary check */
        if ((PHHAL_HW_RD70X_RESERVED_BUFFER_LEN + wValue) >= pDataParams->wRxBufSize)
        {
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* Set start position */
        pDataParams->wRxBufStartPos = wValue;
        pDataParams->wRxBufLen = wValue;

        /* Preserve RxBuffer contents if needed */
        if (pDataParams->pTxBuffer == pDataParams->pRxBuffer)
        {
            pDataParams->wTxBufStartPos = pDataParams->wRxBufStartPos;
        }
        else
        {
            pDataParams->wTxBufStartPos = 0;
        }
        break;

    case PHHAL_HW_CONFIG_TXBUFFER_LENGTH:

        /* Check parameter */
        if ((pDataParams->wTxBufStartPos + PHHAL_HW_RD70X_RESERVED_BUFFER_LEN + wValue) > pDataParams->wTxBufSize)
        {
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* set buffer length */
        pDataParams->wTxBufLen = wValue;
        break;

    case PHHAL_HW_CONFIG_TXBUFFER:

        /* Check additional info parameter */
        if ((pDataParams->wTxBufStartPos + PHHAL_HW_RD70X_RESERVED_BUFFER_LEN + pDataParams->wAdditionalInfo) >= pDataParams->wTxBufSize)
        {
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* Modify TxBuffer byte */
        pDataParams->pTxBuffer[pDataParams->wTxBufStartPos + PHHAL_HW_RD70X_RESERVED_BUFFER_LEN + pDataParams->wAdditionalInfo] = (uint8_t)wValue;
        break;

    case PHHAL_HW_CONFIG_DISABLE_MF_CRYPTO1:

        /* Disable crypto, enabling is not supported */
        if (wValue != PH_OFF)
        {
            /* Retrieve Control register */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_CONTROL, &bBackup));

            /* Clear Crypto1On bit */
            bBackup &= (uint8_t)~(uint8_t)PHHAL_HW_RD70X_BIT_CRYPTO1ON;

            /* Write Control register */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_CONTROL, bBackup));
        }

        break;

    case PHHAL_HW_CONFIG_ADDITIONAL_INFO:

        /* Modify additional info parameter */
        pDataParams->wAdditionalInfo = wValue;
        break;

    case PHHAL_HW_CONFIG_RFRESET_ON_TIMEOUT:

        if (wValue == PH_OFF)
        {
            pDataParams->bRfResetAfterTo = PH_OFF;
        }
        else
        {
            pDataParams->bRfResetAfterTo = PH_ON;
        }
        break;

    case PHHAL_HW_RD70X_CONFIG_DISABLE_PCDRESET:

        pDataParams->bDisablePcdReset = (uint8_t)wValue;
        break;

    default:
        return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_HAL);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd70x_GetConfig(
                                   phhalHw_Rd70x_DataParams_t * pDataParams,
                                   uint16_t wConfig,
                                   uint16_t * pValue
                                   )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bRegister;

    switch (wConfig)
    {
    case PHHAL_HW_CONFIG_PARITY:

        /* Read config from shadow */
        *pValue = pDataParams->wCfgShadow[wConfig];
        break;

    case PHHAL_HW_CONFIG_TXCRC:

        /* Read config from shadow */
        *pValue = pDataParams->wCfgShadow[wConfig];
        break;

    case PHHAL_HW_CONFIG_RXCRC:

        /* Read config from shadow */
        *pValue = pDataParams->wCfgShadow[wConfig];
        break;

    case PHHAL_HW_CONFIG_TXLASTBITS:

        /* Read config from shadow */
        *pValue = pDataParams->wCfgShadow[wConfig];
        break;

    case PHHAL_HW_CONFIG_ADDITIONAL_INFO:
    case PHHAL_HW_CONFIG_RXLASTBITS:

        *pValue = pDataParams->wAdditionalInfo;
        break;

    case PHHAL_HW_CONFIG_RXDEAFBITS:

        /* Read config from shadow */
        *pValue = pDataParams->wCfgShadow[wConfig];
        break;

    case PHHAL_HW_CONFIG_CLEARBITSAFTERCOLL:

        /* Read config from shadow */
        *pValue = pDataParams->wCfgShadow[wConfig];
        break;

    case PHHAL_HW_CONFIG_TXDATARATE:

        /* Read config from shadow */
        *pValue = pDataParams->wCfgShadow[wConfig];
        break;

    case PHHAL_HW_CONFIG_RXDATARATE:

        /* Read config from shadow */
        *pValue = pDataParams->wCfgShadow[wConfig];
        break;

    case PHHAL_HW_CONFIG_MODINDEX:

        /* Read config from shadow */
        *pValue = pDataParams->wCfgShadow[wConfig];
        break;

    case PHHAL_HW_CONFIG_ASK100:

        /* Read config from shadow */
        *pValue = pDataParams->wCfgShadow[wConfig];
        break;

    case PHHAL_HW_CONFIG_TIMEOUT_VALUE_US:

        /* Overflow check */
        if (pDataParams->dwTimeoutUs > 0xFFFF)
        {
            return PH_ADD_COMPCODE(PH_ERR_PARAMETER_OVERFLOW, PH_COMP_HAL);
        }
        *pValue = (uint16_t)pDataParams->dwTimeoutUs;
        break;

    case PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS:

        /* Return parameter */
        *pValue = (uint16_t)(pDataParams->dwTimeoutUs / 1000);
        break;

    case PHHAL_HW_CONFIG_TIMING_MODE:

        /* Return parameter */
        *pValue = pDataParams->wTimingMode;
        break;

    case PHHAL_HW_CONFIG_TIMING_US:

        if (pDataParams->dwTimingUs > 0xFFFF)
        {
            return PH_ADD_COMPCODE(PH_ERR_PARAMETER_OVERFLOW, PH_COMP_HAL);
        }

        *pValue = (uint16_t)pDataParams->dwTimingUs;
        pDataParams->dwTimingUs = 0;
        break;

    case PHHAL_HW_CONFIG_TIMING_MS:

        if (pDataParams->dwTimingUs > (0xFFFF * 1000))
        {
            pDataParams->dwTimingUs = 0;
            return PH_ADD_COMPCODE(PH_ERR_PARAMETER_OVERFLOW, PH_COMP_HAL);
        }

        *pValue = (uint16_t)(pDataParams->dwTimingUs / 1000);
        pDataParams->dwTimingUs = 0;
        break;

    case PHHAL_HW_CONFIG_FIELD_OFF_TIME:

        /* Return parameter */
        *pValue = pDataParams->wFieldOffTime;
        break;

    case PHHAL_HW_CONFIG_FIELD_RECOVERY_TIME:

        /* Return parameter */
        *pValue = pDataParams->wFieldRecoveryTime;
        break;

    case PHHAL_HW_CONFIG_SYMBOL_START:

        /* Return parameter */
        *pValue = pDataParams->bSymbolStart;
        break;

    case PHHAL_HW_CONFIG_SYMBOL_END:

        /* Return parameter */
        *pValue = pDataParams->bSymbolEnd;
        break;

    case PHHAL_HW_CONFIG_SUBCARRIER:

        /* Return parameter */
        *pValue = PHHAL_HW_SUBCARRIER_SINGLE;
        break;

    case PHHAL_HW_CONFIG_RXBUFFER_STARTPOS:

        /* Return parameter */
        *pValue = pDataParams->wRxBufStartPos;
        break;

    case PHHAL_HW_CONFIG_RXBUFFER_BUFSIZE:

        /* Return parameter */
        *pValue = pDataParams->wRxBufSize - PHHAL_HW_RD70X_RESERVED_BUFFER_LEN;
        break;

    case PHHAL_HW_CONFIG_TXBUFFER_BUFSIZE:

        /* Return parameter */
        *pValue = pDataParams->wTxBufSize - PHHAL_HW_RD70X_RESERVED_BUFFER_LEN - pDataParams->wTxBufStartPos;
        break;

    case PHHAL_HW_CONFIG_TXBUFFER_LENGTH:

        /* Return parameter */
        *pValue = pDataParams->wTxBufLen;
        break;

    case PHHAL_HW_CONFIG_TXBUFFER:

        /* Check additional info parameter */
        if ((pDataParams->wTxBufStartPos + PHHAL_HW_RD70X_RESERVED_BUFFER_LEN + pDataParams->wAdditionalInfo) >= pDataParams->wTxBufSize)
        {
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* Retrieve TxBuffer byte */
        *pValue = (uint16_t)pDataParams->pTxBuffer[pDataParams->wTxBufStartPos + PHHAL_HW_RD70X_RESERVED_BUFFER_LEN + pDataParams->wAdditionalInfo];
        break;

    case PHHAL_HW_CONFIG_DISABLE_MF_CRYPTO1:

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_CONTROL, &bRegister));

        /* Clear Crypto1On bit */
        if (bRegister & PHHAL_HW_RD70X_BIT_CRYPTO1ON)
        {
            *pValue = PH_OFF;
        }
        else
        {
            *pValue = PH_ON;
        }
        break;

    case PHHAL_HW_CONFIG_RFRESET_ON_TIMEOUT:

        *pValue = (uint16_t)pDataParams->bRfResetAfterTo;
        break;

    case PHHAL_HW_RD70X_CONFIG_DISABLE_PCDRESET:

        *pValue = (uint16_t)pDataParams->bDisablePcdReset;
        break;

    default:
        return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_HAL);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd70x_FieldOn(
                                 phhalHw_Rd70x_DataParams_t * pDataParams
                                 )
{    
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bTxControlReg;

    /* Retrieve the content of the TxControl register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_TXCONTROL, &bTxControlReg));

    /* Switch on the field again */
    bTxControlReg |= PHHAL_HW_RD70X_BIT_TX1RFEN | PHHAL_HW_RD70X_BIT_TX2RFEN;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_TXCONTROL, bTxControlReg));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd70x_FieldOff(
                                  phhalHw_Rd70x_DataParams_t * pDataParams
                                  )
{    
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bTxControlReg;

    /* Retrieve the content of the TxControl register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_TXCONTROL, &bTxControlReg));

    /* Switch off the field */
    bTxControlReg &= (uint8_t)~(uint8_t)(PHHAL_HW_RD70X_BIT_TX1RFEN | PHHAL_HW_RD70X_BIT_TX2RFEN);
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_TXCONTROL, bTxControlReg));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd70x_FieldReset(
                                    phhalHw_Rd70x_DataParams_t * pDataParams
                                    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t    PH_MEMLOC_REM wFieldOffTmp;

    /* Pegoda Rf-Reset is about 14% too long, so correct the Off-Time */
    if (pDataParams->wFieldOffTime > 1)
    {
        wFieldOffTmp = (uint16_t)((float32_t)pDataParams->wFieldOffTime * 0.86);
    }
    else
    {
        wFieldOffTmp = 1;
    }

    switch (pDataParams->bCardType)
    {
    case PHHAL_HW_CARDTYPE_ISO14443A:

        /* perfrom RF-Reset */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_PcdRfReset(pDataParams, wFieldOffTmp));
        break;

    case PHHAL_HW_CARDTYPE_ISO14443B:

        /* perfrom RF-Reset */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_PcdRfReset(pDataParams, wFieldOffTmp));
        /* Set TypeB Registers */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_SetTypeBRegs(pDataParams));
        break;

    case PHHAL_HW_CARDTYPE_ISO15693:
    case PHHAL_HW_CARDTYPE_ICODEEPCUID:

        /* perfrom RF-Reset */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_I1PcdRfReset(pDataParams, wFieldOffTmp));
        break;

    default:

        return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_HAL);
    }

    /* Firmware only has 1ms recovery-time, wait the remaining time */
    if (pDataParams->wFieldRecoveryTime > 1)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Wait(
            pDataParams,
            PHHAL_HW_TIME_MILLISECONDS,
            pDataParams->wFieldRecoveryTime - 1));
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd70x_Wait(
                              phhalHw_Rd70x_DataParams_t * pDataParams,
                              uint8_t bUnit,
                              uint16_t wTimeout
                              )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bRegTimerClock;
    uint8_t     PH_MEMLOC_REM bRegTimerReload;
    uint8_t     PH_MEMLOC_REM bRegTimerControl;
    uint8_t     PH_MEMLOC_REM bTmp;
    uint16_t    PH_MEMLOC_REM wPrescaler;
    uint16_t    PH_MEMLOC_REM wReload;
    float32_t   PH_MEMLOC_REM fTimeoutUs;
    float32_t   PH_MEMLOC_REM fTemp;

    /* Parameter check */
    if ((bUnit != PHHAL_HW_TIME_MICROSECONDS) && (bUnit != PHHAL_HW_TIME_MILLISECONDS))
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Backup Rd70x register contents */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_TIMER_CLOCK, &bRegTimerClock));
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_TIMER_RELOAD, &bRegTimerReload));
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_TIMER_CONTROL, &bRegTimerControl));

    /* do as long as we have an overflow in the IC timer */
    do
    {
        /* Handle timeout in microseconds */
        if (bUnit == PHHAL_HW_TIME_MICROSECONDS)
        {
            fTimeoutUs = (float32_t)wTimeout;
            wTimeout = 0;
        }
        else
        {
            fTimeoutUs = (float32_t)wTimeout * 1000.0f;

            /* Max. timeout check */
            if (fTimeoutUs > PHHAL_HW_RD70X_TIMER_MAX_VALUE_US)
            {
                fTimeoutUs = PHHAL_HW_RD70X_TIMER_MAX_VALUE_US;
                wTimeout = wTimeout - ((uint16_t)(PHHAL_HW_RD70X_TIMER_MAX_VALUE_US / 1000.0f) + 1);
            }
            else
            {
                wTimeout = 0;
            }
        }

        /* Calculate the prescaler value */
        /* [timeout[us]  = (2 ^ n) / 13.56] */
        fTemp = (float32_t)(log((fTimeoutUs * PHHAL_HW_RD70X_TIMER_FREQ) / 255.0f) / log(2));

        /* Evaluate prescaler value */
        if (fTemp > 1.0f)
        {
            if (fTemp < 21.0f)
            {
                wPrescaler = (uint16_t)(fTemp + 1);
            }
            else
            {
                wPrescaler = 21;
            }
        }
        else
        {
            wPrescaler = 1;
        }

        /* Calculate the reload value */
        fTemp = (fTimeoutUs * PHHAL_HW_RD70X_TIMER_FREQ) / (float32_t)(1 << wPrescaler);

        /* Except for a special case, the float value will have some commas
        and therefore needs to be "ceiled" */
        if (fTemp > (float32_t)(uint16_t)fTemp)
        {
            wReload = (uint16_t)(fTemp + 1);
        }
        else
        {
            wReload = (uint16_t)fTemp;
        }

        /* stop a probably running command */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_COMMAND, 0x00));

        /* Set new timeout value */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_TIMER_CLOCK, (uint8_t)wPrescaler));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_TIMER_RELOAD, (uint8_t)wReload));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_TIMER_CONTROL, 0x00));

        /* Start the timer */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_CONTROL, &bTmp));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_CONTROL, bTmp | PHHAL_HW_RD70X_BIT_TSTARTNOW));

        /* wait for timer */
        do
        {
            /* Read secondary status register */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_SECONDARY_STATUS, &bTmp));
        }
        while (bTmp & PHHAL_HW_RD70X_BIT_TRUNNING);
    }
    while (wTimeout > 0);

    /* Restore Rd70x register contents */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_TIMER_CLOCK, bRegTimerClock));
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_TIMER_RELOAD, bRegTimerReload));
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(pDataParams, PHHAL_HW_RD70X_REG_TIMER_CONTROL, bRegTimerControl));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd70x_MfcAuthenticateKeyNo(
    phhalHw_Rd70x_DataParams_t * pDataParams,
    uint8_t bBlockNo,
    uint8_t bKeyType,
    uint16_t wKeyNo,
    uint16_t wKeyVersion,
    uint8_t * pUid
    )
{    
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bAuthMode;

    /* Evaluate which key to use */
    if ((bKeyType & 0x7F) == PHHAL_HW_MFC_KEYA)
    {
        bAuthMode = PHHAL_HW_RD70X_AUTHMODE_KEYA;
    }
    else if ((bKeyType & 0x7F) == PHHAL_HW_MFC_KEYB)
    {
        bAuthMode = PHHAL_HW_RD70X_AUTHMODE_KEYB;
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* check key version */
    if (wKeyVersion != 0)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* check key number */
    if (wKeyNo > PHHAL_HW_RD70X_MAX_NUM_KEYS)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Perform authentication */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_MfPiccAuthE2(
        pDataParams, 
        bAuthMode,
        pUid,
        (uint8_t)wKeyNo,
        bBlockNo
        ));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd70x_MfcAuthenticate(
    phhalHw_Rd70x_DataParams_t * pDataParams,
    uint8_t bBlockNo,
    uint8_t bKeyType,
    uint8_t * pKey,
    uint8_t * pUid
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bAuthMode;
    uint8_t     PH_MEMLOC_REM bKey[PHHAL_HW_MFC_KEY_LENGTH * 2];

    /* Evaluate which key to use */
    if ((bKeyType & 0x7F) == PHHAL_HW_MFC_KEYA)
    {
        bAuthMode = PHHAL_HW_RD70X_AUTHMODE_KEYA;
    }
    else if ((bKeyType & 0x7F) == PHHAL_HW_MFC_KEYB)
    {
        bAuthMode = PHHAL_HW_RD70X_AUTHMODE_KEYB;
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Code the key */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_HostCodeKey(
        pDataParams,
        pKey, 
        bKey));

    /* Perform authentication */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_MfPiccAuthKey(
        pDataParams, 
        bAuthMode,
        pUid,
        bKey,
        bBlockNo
        ));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

#endif /* NXPBUILD__PHHAL_HW_RD70X */
