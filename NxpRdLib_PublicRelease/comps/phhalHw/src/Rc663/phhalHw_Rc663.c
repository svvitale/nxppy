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
* RC663 specific HAL-Component of Reader Library Framework.
* $Author: jayaprakash.desai $
* $Revision: 1.12 $
* $Date: Wed May 25 14:06:19 2011 $
*
* History:
*  CHu: Generated 12. January 2010
*
*/

#include <ph_Status.h>
#include <phbalReg.h>
#include <phhalHw.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PH_KEYSTORE
#include <phKeyStore.h>
#endif

#ifdef NXPBUILD__PHHAL_HW_RC663

#include "phhalHw_Rc663.h"
#include "phhalHw_Rc663_Int.h"
#include "phhalHw_Rc663_Config.h"
#include <phhalHw_Rc663_Reg.h>
#include <phhalHw_Rc663_Cmd.h>

/** Default shadow for ISO14443-3A Mode */
static const uint16_t PH_MEMLOC_CONST_ROM wRc663_DefaultShadow_I14443a[][2] =
{
    {PHHAL_HW_CONFIG_PARITY,                PH_ON},
    {PHHAL_HW_CONFIG_TXCRC,                 PH_OFF},
    {PHHAL_HW_CONFIG_RXCRC,                 PH_OFF},
    {PHHAL_HW_CONFIG_RXDEAFBITS,            0x0008},
    {PHHAL_HW_CONFIG_TXWAIT_US,             81},
    {PHHAL_HW_CONFIG_TXDATARATE,            PHHAL_HW_RF_DATARATE_106},
    {PHHAL_HW_CONFIG_RXDATARATE,            PHHAL_HW_RF_DATARATE_106},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,      PHHAL_HW_RC663_DEFAULT_TIMEOUT},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS,      0x0000},
    {PHHAL_HW_CONFIG_ASK100,                PH_ON}
};

/** Default shadow for ISO14443-3B Mode */
static const uint16_t PH_MEMLOC_CONST_ROM wRc663_DefaultShadow_I14443b[][2] =
{
    {PHHAL_HW_CONFIG_PARITY,                PH_OFF},
    {PHHAL_HW_CONFIG_TXCRC,                 PH_ON},
    {PHHAL_HW_CONFIG_RXCRC,                 PH_ON},
    {PHHAL_HW_CONFIG_RXDEAFBITS,            0x0008},
    {PHHAL_HW_CONFIG_TXWAIT_US,             85},
    {PHHAL_HW_CONFIG_TXDATARATE,            PHHAL_HW_RF_DATARATE_106},
    {PHHAL_HW_CONFIG_RXDATARATE,            PHHAL_HW_RF_DATARATE_106},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,      PHHAL_HW_RC663_DEFAULT_TIMEOUT},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS,      0x0000},
    {PHHAL_HW_CONFIG_MODINDEX,              PHHAL_HW_RC663_MODINDEX_I14443B},
    {PHHAL_HW_CONFIG_ASK100,                PH_OFF}
};

/** Default shadow for FeliCa Mode */
static const uint16_t PH_MEMLOC_CONST_ROM wRc663_DefaultShadow_Felica[][2] =
{
    {PHHAL_HW_CONFIG_PARITY,                PH_OFF},
    {PHHAL_HW_CONFIG_TXCRC,                 PH_ON},
    {PHHAL_HW_CONFIG_RXCRC,                 PH_ON},
    {PHHAL_HW_CONFIG_RXDEAFBITS,            0x0003},
    {PHHAL_HW_CONFIG_TXWAIT_US,             0x0000},
    {PHHAL_HW_CONFIG_TXDATARATE,            PHHAL_HW_RF_DATARATE_212},
    {PHHAL_HW_CONFIG_RXDATARATE,            PHHAL_HW_RF_DATARATE_212},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,      PHHAL_HW_RC663_DEFAULT_TIMEOUT},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS,      0x0000},
    {PHHAL_HW_CONFIG_MODINDEX,              PHHAL_HW_RC663_MODINDEX_FELICA},
    {PHHAL_HW_CONFIG_ASK100,                PH_OFF}
};

/** Default shadow for ISO15693 Mode */
static const uint16_t PH_MEMLOC_CONST_ROM wRc663_DefaultShadow_I15693[][2] =
{
    {PHHAL_HW_CONFIG_PARITY,                PH_OFF},
    {PHHAL_HW_CONFIG_TXCRC,                 PH_ON},
    {PHHAL_HW_CONFIG_RXCRC,                 PH_ON},
    {PHHAL_HW_CONFIG_RXDEAFBITS,            0x0003},
    {PHHAL_HW_CONFIG_TXWAIT_US,             0x0000},
    {PHHAL_HW_CONFIG_TXDATARATE,            PHHAL_HW_RF_TX_DATARATE_1_OUT_OF_4},
    {PHHAL_HW_CONFIG_RXDATARATE,            PHHAL_HW_RF_RX_DATARATE_HIGH},
    {PHHAL_HW_CONFIG_SUBCARRIER,            PHHAL_HW_SUBCARRIER_SINGLE},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,      PHHAL_HW_RC663_DEFAULT_TIMEOUT},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS,      0x0000},
    {PHHAL_HW_CONFIG_MODINDEX,              PHHAL_HW_RC663_MODINDEX_I15693},
    {PHHAL_HW_CONFIG_ASK100,                PH_ON}
};

/** Default shadow for ICode EPC/UID Mode */
static const uint16_t PH_MEMLOC_CONST_ROM wRc663_DefaultShadow_EpcUid[][2] =
{
    {PHHAL_HW_CONFIG_PARITY,                PH_OFF},
    {PHHAL_HW_CONFIG_TXCRC,                 PH_OFF},
    {PHHAL_HW_CONFIG_RXCRC,                 PH_OFF},
    {PHHAL_HW_CONFIG_RXDEAFBITS,            0x0006},
    {PHHAL_HW_CONFIG_TXWAIT_US,             302},
    {PHHAL_HW_CONFIG_TXDATARATE,            PHHAL_HW_RF_DATARATE_EPCUID},
    {PHHAL_HW_CONFIG_RXDATARATE,            PHHAL_HW_RF_DATARATE_EPCUID},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,      PHHAL_HW_RC663_DEFAULT_TIMEOUT},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS,      0x0000},
    {PHHAL_HW_CONFIG_MODINDEX,              PHHAL_HW_RC663_MODINDEX_EPCUID},
    {PHHAL_HW_CONFIG_ASK100,                PH_OFF}
};

/** Default shadow for ISO18000-3 Mode3 */
static const uint16_t PH_MEMLOC_CONST_ROM wRc663_DefaultShadow_I18000p3m3[][2] =
{
    {PHHAL_HW_CONFIG_PARITY,                PH_OFF},
    {PHHAL_HW_CONFIG_TXCRC,                 PH_ON},
    {PHHAL_HW_CONFIG_RXCRC,                 PH_ON},
    {PHHAL_HW_CONFIG_RXDEAFBITS,            0x0001},
    {PHHAL_HW_CONFIG_TXWAIT_US,             0x0000},
    {PHHAL_HW_CONFIG_TXDATARATE,            PHHAL_HW_RF_TX_DATARATE_I18000P3M3},
    {PHHAL_HW_CONFIG_RXDATARATE,            PHHAL_HW_RF_RX_DATARATE_I18000P3M3_MAN2},
    {PHHAL_HW_CONFIG_SUBCARRIER,            PHHAL_HW_SUBCARRIER_DUAL},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,      PHHAL_HW_RC663_DEFAULT_TIMEOUT},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS,      0x0000},
    {PHHAL_HW_CONFIG_MODINDEX,              PHHAL_HW_RC663_MODINDEX_I18000P3M3},
    {PHHAL_HW_CONFIG_ASK100,                PH_OFF}
};

/** Default shadow for ISO18092 Passive Initiator Mode */
static const uint16_t PH_MEMLOC_CONST_ROM wRc663_DefaultShadow_I18092mPI[][2] =
{
    {PHHAL_HW_CONFIG_PARITY,                PH_ON},
    {PHHAL_HW_CONFIG_TXCRC,                 PH_ON},
    {PHHAL_HW_CONFIG_RXCRC,                 PH_ON},
    {PHHAL_HW_CONFIG_RXDEAFBITS,            0x0003},
    {PHHAL_HW_CONFIG_TXWAIT_US,             81},
    {PHHAL_HW_CONFIG_TXDATARATE,            PHHAL_HW_RF_DATARATE_106},
    {PHHAL_HW_CONFIG_RXDATARATE,            PHHAL_HW_RF_DATARATE_106},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,      PHHAL_HW_RC663_DEFAULT_TIMEOUT},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS,      0x0000},
    {PHHAL_HW_CONFIG_MODINDEX,              PHHAL_HW_RC663_MODINDEX_FELICA},
    {PHHAL_HW_CONFIG_ASK100,                PH_ON}
};

phStatus_t phhalHw_Rc663_Init(
                              phhalHw_Rc663_DataParams_t * pDataParams,
                              uint16_t wSizeOfDataParams,
                              void * pBalDataParams,
                              uint8_t * pLoadRegConfig,
                              uint8_t * pTxBuffer,
                              uint16_t wTxBufSize,
                              uint8_t * pRxBuffer,
                              uint16_t wRxBufSize
                              )
{
    if (sizeof(phhalHw_Rc663_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_HAL);
    }
    if (wTxBufSize == 0 || wRxBufSize == 0)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }
    PH_ASSERT_NULL (pDataParams);
    PH_ASSERT_NULL (pBalDataParams);
    PH_ASSERT_NULL (pTxBuffer);
    PH_ASSERT_NULL (pRxBuffer);

    /* We need to reserve 1 byte at the beginning of the buffers for SPI operation */
    ++pTxBuffer;
    --wTxBufSize;
    ++pRxBuffer;
    --wRxBufSize;

    /* Init. private data */
    pDataParams->wId                    = PH_COMP_HAL | PHHAL_HW_RC663_ID;
    pDataParams->pBalDataParams         = pBalDataParams;
    pDataParams->bLoadRegMode           = PH_OFF;
    pDataParams->pLoadRegConfig         = pLoadRegConfig;
    pDataParams->pTxBuffer              = pTxBuffer;
    pDataParams->wTxBufSize             = wTxBufSize;
    pDataParams->wTxBufLen              = 0;
    pDataParams->pRxBuffer              = pRxBuffer;
    pDataParams->wRxBufSize             = wRxBufSize;
    pDataParams->wRxBufLen              = 0;
    pDataParams->wRxBufStartPos         = 0;
    pDataParams->bCardType              = PHHAL_HW_CARDTYPE_ISO14443A;
    pDataParams->wTimingMode            = PHHAL_HW_TIMING_MODE_OFF;
    pDataParams->bTimeoutUnit           = PHHAL_HW_TIME_MICROSECONDS;
    pDataParams->dwTimingUs             = 0;
    pDataParams->wFieldOffTime          = PHHAL_HW_FIELD_OFF_DEFAULT;
    pDataParams->wFieldRecoveryTime     = PHHAL_HW_FIELD_RECOVERY_DEFAULT;
    pDataParams->bSymbolStart           = PH_OFF;
    pDataParams->bSymbolEnd             = PH_OFF;
    pDataParams->bFifoSize              = PHHAL_HW_RC663_VALUE_FIFOSIZE_255;
    pDataParams->wMaxPrecachedBytes     = PHHAL_HW_RC663_PRECACHED_BYTES;
    pDataParams->wAdditionalInfo        = 0;
    pDataParams->bBalConnectionType     = PHHAL_HW_BAL_CONNECTION_RS232;
    pDataParams->bRfResetAfterTo        = PH_OFF;

    /* Reset subcarrier setting, needed for phhalHw_Rc663_SetCardMode */
    pDataParams->wCfgShadow[PHHAL_HW_CONFIG_SUBCARRIER] = PHHAL_HW_SUBCARRIER_SINGLE;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_Exchange(
                                  phhalHw_Rc663_DataParams_t * pDataParams,
                                  uint16_t wOption,
                                  uint8_t * pTxBuffer,
                                  uint16_t wTxLength,
                                  uint8_t ** ppRxBuffer,
                                  uint16_t * pRxLength
                                  )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t    PH_MEMLOC_REM wNumPrecachedBytes;
    uint16_t    PH_MEMLOC_REM wFifoBytes;
    uint8_t     PH_MEMLOC_REM bIrq0WaitFor;
    uint8_t     PH_MEMLOC_REM bIrq1WaitFor;
    uint8_t     PH_MEMLOC_REM bIrq0Reg = 0x00;
    uint8_t     PH_MEMLOC_REM bIrq1Reg = 0x00;
    uint8_t     PH_MEMLOC_REM bRegister;
    uint8_t     PH_MEMLOC_REM bError;
    uint8_t     PH_MEMLOC_REM bNoData;
    uint32_t    PH_MEMLOC_REM dwTimingSingle;
    uint8_t *   PH_MEMLOC_REM pTmpBuffer;
    uint16_t    PH_MEMLOC_REM wTmpBufferLen;
    uint16_t    PH_MEMLOC_REM wTmpBufferSize;

    /* Check options */
    if (wOption & (uint16_t)~(uint16_t)(PH_EXCHANGE_BUFFERED_BIT | PH_EXCHANGE_LEAVE_BUFFER_BIT))
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* clear internal buffer if requested */
    if (!(wOption & PH_EXCHANGE_LEAVE_BUFFER_BIT))
    {
        pDataParams->wTxBufLen = 0;
    }

    /* set the receive length */
    if (pRxLength != NULL)
    {
        *pRxLength = 0;
    }

    /* Fill the global TxBuffer */
    /* Note: We always need to buffer for SPI, else the input buffer would get overwritten! */
    if ((wOption & PH_EXCHANGE_BUFFERED_BIT) ||
        (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_SPI) ||
        (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_I2C))
    {
        /* retrieve transmit buffer */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_GetTxBuffer(pDataParams, PH_ON, &pTmpBuffer, &wTmpBufferLen, &wTmpBufferSize));

        if (wTxLength != 0)
        {
            /* TxBuffer overflow check */
            if (wTxLength > (wTmpBufferSize - wTmpBufferLen))
            {
                pDataParams->wTxBufLen = 0;
                return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
            }

            /* copy data */
            memcpy(&pTmpBuffer[wTmpBufferLen], pTxBuffer, wTxLength);  /* PRQA S 3200 */
            pDataParams->wTxBufLen = pDataParams->wTxBufLen + wTxLength;
        }

        /* Buffer operation -> finished */
        if (wOption & PH_EXCHANGE_BUFFERED_BIT)
        {
            return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
        }
        /* Else reset the input length for SPI and continue */
        else
        {
            wTxLength = 0;
        }
    }

    /* retrieve transmit buffer */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_GetTxBuffer(pDataParams, PH_ON, &pTmpBuffer, &wTmpBufferLen, &wTmpBufferSize));

    /* Disable DataEn if no data is to be sent */
    if ((wTmpBufferLen == 0) && (wTxLength == 0))
    {
        /* Store that we sent no data */
        bNoData = PH_ON;

        /* Read out TxDataNum register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_TXDATANUM, &bRegister));

        /* Disable DataEn */
        bRegister &= (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_DATAEN;

        /* Write changed register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_TXDATANUM, bRegister));
    }
    else
    {
        /* Reset NoData flag */
        bNoData = PH_OFF;
    }

    /* Terminate a possibly running command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_COMMAND, PHHAL_HW_RC663_CMD_IDLE));

    /* Flush FiFo */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_FlushFifo(pDataParams));

    /* clear all IRQ0 flags */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(
        pDataParams,
        PHHAL_HW_RC663_REG_IRQ0,
        (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_SET));

    /* clear all IRQ1 flags */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(
        pDataParams,
        PHHAL_HW_RC663_REG_IRQ1,
        (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_SET));

    /* Precache buffered contents into FIFO */
    wNumPrecachedBytes = (wTmpBufferLen > pDataParams->wMaxPrecachedBytes) ? pDataParams->wMaxPrecachedBytes : wTmpBufferLen;
    if (wNumPrecachedBytes > 0)
    {
        /* Perform actual write to FIFO */
        status = phhalHw_Rc663_WriteFifo(pDataParams, pTmpBuffer, wNumPrecachedBytes, &wFifoBytes);

        /* Ignore FiFo overflow warning */
        if ((status & PH_ERR_MASK) != PH_ERR_BUFFER_OVERFLOW)
        {
            PH_CHECK_SUCCESS(status);
        }

        /* Update buffer pointer and length */
        pTmpBuffer += wFifoBytes;
        wTmpBufferLen = wTmpBufferLen - wFifoBytes;
    }
    else
    {
        status = PH_ERR_SUCCESS;
    }

    /* Precache given buffer contents into FIFO */
    if ((status & PH_ERR_MASK) != PH_ERR_BUFFER_OVERFLOW)
    {
        wNumPrecachedBytes = (wTxLength > (pDataParams->wMaxPrecachedBytes - wNumPrecachedBytes)) ? (pDataParams->wMaxPrecachedBytes - wNumPrecachedBytes) : wTxLength;

        if (wNumPrecachedBytes > 0)
        {
            /* Perform actual write to FIFO */
            status = phhalHw_Rc663_WriteFifo(pDataParams, pTxBuffer, wNumPrecachedBytes, &wFifoBytes);

            /* Ignore FiFo overflow warning */
            if ((status & PH_ERR_MASK) != PH_ERR_BUFFER_OVERFLOW)
            {
                PH_CHECK_SUCCESS(status);
            }

            /* Update buffer pointer and length */
            pTxBuffer += wFifoBytes;
            wTxLength = wTxLength - wFifoBytes;
        }
    }

    /* start the command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_COMMAND, PHHAL_HW_RC663_CMD_TRANSCEIVE));

    /* Write the remaining data into the Fifo */
    /* (Only possible if interface to RC is fast enough!) */
    while ((wTmpBufferLen != 0) || (wTxLength != 0))
    {
        /* Switch from prechache buffer to given buffer if it's empty */
        if (wTmpBufferLen == 0)
        {
            pTmpBuffer = pTxBuffer;
            wTmpBufferLen = wTxLength;
            wTxLength = 0;
        }
        /* */
        /* Check for FIFO underflow */
        /* */
#ifdef PHHAL_HW_RC663_FEATURE_FIFO_UNDERFLOW_CHECK
        /* read interrupt status */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_IRQ0, &bIrq0Reg));

        /* If we got data to transmit but the Tx-command aborted, we were too slow! */
        if ((bIrq0Reg & PHHAL_HW_RC663_BIT_IDLEIRQ) || (bIrq0Reg & PHHAL_HW_RC663_BIT_TXIRQ))
        {
            /* stop the command */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_WriteRegister(
                pDataParams,
                PHHAL_HW_RC663_REG_COMMAND,
                PHHAL_HW_RC663_CMD_IDLE));

            /* Flush FiFo */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_FlushFifo(pDataParams));

            return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_HAL);
        }
#endif
        /* write remaining data to transmit into FiFo buffer */
        status = phhalHw_Rc663_WriteFifo(pDataParams, pTmpBuffer, wTmpBufferLen, &wFifoBytes);

        /* Ignore FiFo overflow warning */
        if ((status & PH_ERR_MASK) != PH_ERR_BUFFER_OVERFLOW)
        {
            PH_CHECK_SUCCESS(status);
        }

        /* Update buffer pointer and length */
        pTmpBuffer += wFifoBytes;
        wTmpBufferLen = wTmpBufferLen - wFifoBytes;
    }

    /* Set wait IRQs */
    bIrq0WaitFor = PHHAL_HW_RC663_BIT_TXIRQ | PHHAL_HW_RC663_BIT_IDLEIRQ;
    bIrq1WaitFor = PHHAL_HW_RC663_BIT_TIMER1IRQ;

    /* wait until the transmission is finished */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_WaitIrq(
        pDataParams,
        PH_ON,
        PH_OFF,
        bIrq0WaitFor,
        bIrq1WaitFor,
        &bIrq0Reg,
        &bIrq1Reg));

    /* Let's now wait for the RX Irq.*/
    if (!(bIrq0Reg & PHHAL_HW_RC663_BIT_IDLEIRQ) && !(bIrq0Reg & PHHAL_HW_RC663_BIT_ERRIRQ))
    {
        /* Clear high-alert irq flag */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_IRQ0, PHHAL_HW_RC663_BIT_HIALERTIRQ));

        /* Change wait IRQs */
        bIrq0WaitFor = PHHAL_HW_RC663_BIT_RXIRQ | PHHAL_HW_RC663_BIT_HIALERTIRQ | PHHAL_HW_RC663_BIT_IDLEIRQ | PHHAL_HW_RC663_BIT_EMDIRQ;

        /* wait until reception */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_WaitIrq(
            pDataParams,
            PH_ON,
            PH_OFF,
            bIrq0WaitFor,
            bIrq1WaitFor,
            &bIrq0Reg,
            &bIrq1Reg));
    }

    /* Reset TxLastBits */
    if (pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXLASTBITS] != 0)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetConfig(pDataParams, PHHAL_HW_CONFIG_TXLASTBITS, 0x00));
    }

    /* Reset buffered bytes */
    pDataParams->wTxBufLen = 0;

    /* Enable DataEn again if no data has been sent */
    if (bNoData != PH_OFF)
    {
        /* Read out TxDataNum register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_TXDATANUM, &bRegister));

        /* Enable DataEn */
        bRegister |= PHHAL_HW_RC663_BIT_DATAEN;

        /* Write changed register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_TXDATANUM, bRegister));
    }

    /* Timeout handling */
    if ((bIrq1Reg & PHHAL_HW_RC663_BIT_TIMER1IRQ) && !(bIrq0Reg & PHHAL_HW_RC663_BIT_EMDIRQ))
    {
        /* retrieve content of Timer Control register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_TCONTROL, &bRegister));

        /* manually stop timers */
        bRegister |= PHHAL_HW_RC663_BIT_T0STARTSTOPNOW | PHHAL_HW_RC663_BIT_T1STARTSTOPNOW;
        bRegister &= (uint8_t)~(uint8_t)(PHHAL_HW_RC663_BIT_T0RUNNING | PHHAL_HW_RC663_BIT_T1RUNNING);
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_TCONTROL, bRegister));

        /* Reset after timeout behaviour */
        if (pDataParams->bRfResetAfterTo != PH_OFF)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_FieldReset(pDataParams));
        }

        status = PH_ERR_IO_TIMEOUT;
    }
    else
    {
        status = PH_ERR_SUCCESS;
    }

    /* Reset receive buffer length */
    pDataParams->wRxBufLen = 0;

    /* Retrieve receive buffer properties */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_GetRxBuffer(pDataParams, PH_ON, &pTmpBuffer, &wTmpBufferLen, &wTmpBufferSize));

    /* Do the following if no timeout occured */
    if (status == PH_ERR_SUCCESS)
    {
        /* mask out high-alert */
        bIrq0WaitFor &= (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_HIALERTIRQ;

        /* retrieve fifo bytes */
        do
        {
            /* read interrupt status */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_IRQ0, &bIrq0Reg));
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_IRQ1, &bIrq1Reg));

            /* retrieve bytes from FiFo */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_ReadFifo(
                pDataParams,
                wTmpBufferSize,
                &pTmpBuffer[wTmpBufferLen],
                &wFifoBytes));

            /* advance receive buffer */
            wTmpBufferLen = wTmpBufferLen + wFifoBytes;
            wTmpBufferSize = wTmpBufferSize - wFifoBytes;
        }
        while ((!(bIrq0Reg & bIrq0WaitFor) && !(bIrq1Reg & bIrq1WaitFor)) || (wFifoBytes != 0));

        /* */
        /* Check if an error occured */
        /* read the error register */
        /* */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_ERROR, &bError));

        /* no data error */
        if (bError & PHHAL_HW_RC663_BIT_NODATAERR)
        {
            status = PH_ERR_INTERNAL_ERROR;
        }
        /* buffer overflow */
        else if (bError & PHHAL_HW_RC663_BIT_FIFOOVL)
        {
            status = PH_ERR_BUFFER_OVERFLOW;
        }
        /* Fifo write error */
        else if (bError & PHHAL_HW_RC663_BIT_FIFOWRERR)
        {
            status = PH_ERR_READ_WRITE_ERROR;
        }
        /* framing error */
        else if (bError & PHHAL_HW_RC663_BIT_MINFRAMEERR)
        {
            status = PH_ERR_FRAMING_ERROR;
        }
        /* collision */
        else if (bError & PHHAL_HW_RC663_BIT_COLLDET)
        {
            /* No bytes received -> timeout */
            if (wTmpBufferLen == 0)
            {
                status = PH_ERR_IO_TIMEOUT;
            }
            /* Else perform collision handling */
            else
            {
                status = PH_ERR_COLLISION_ERROR;

                /* Retrieve collision position */
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_RXCOLL, &bRegister));

                /* check if collpos is valid */
                if (bRegister & PHHAL_HW_RC663_BIT_COLLPOSVALID)
                {
                    /* retrieve collpos */
                    bRegister &= PHHAL_HW_RC663_MASK_COLLPOS;
                }
                else
                {
                    /* collision position out of range --> max. */
                    bRegister = 0x3F;
                }

                /* Restore wRxBufSize */
                wTmpBufferSize = wTmpBufferSize + wTmpBufferLen;

                /* Check for buffer overflow */
                if ((uint16_t)(bRegister >> 3) > wTmpBufferSize)
                {
                    /* Return the maximum possible size of data */
                    wTmpBufferLen = wTmpBufferSize;
                    status = PH_ERR_BUFFER_OVERFLOW;
                }
                else
                {
                    /* Adjust valid byte count */
                    wTmpBufferLen = (uint16_t)(bRegister >> 3);
                }

                /* Mask out valid bits of last byte */
                bRegister &= PHHAL_HW_RC663_MASK_RXLASTBITS;

                /* Incomplete byte also counts as received byte */
                if (bRegister)
                {
                    /* Check for buffer overflow */
                    if (wTmpBufferLen == wTmpBufferSize)
                    {
                        status = PH_ERR_BUFFER_OVERFLOW;
                    }
                    else
                    {
                        ++wTmpBufferLen;
                    }
                }

                /* Store valid bits of last byte */
                pDataParams->wAdditionalInfo = bRegister;
            }
        }
        /* protocol error */
        else if (bError & PHHAL_HW_RC663_BIT_PROTERR)
        {
            status = PH_ERR_PROTOCOL_ERROR;
        }
        /* CRC / parity error */
        else if (bError & PHHAL_HW_RC663_BIT_INTEGERR)
        {
            status = PH_ERR_INTEGRITY_ERROR;
        }
        /* No error */
        else
        {
            status = PH_ERR_SUCCESS;
        }
    }

    /* Exchange was successfull */
    if (status == PH_ERR_SUCCESS)
    {
        /* Retrieve valid bits of last byte */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_RXBITCTRL, &bRegister));

        /* Mask out valid bits of last byte */
        bRegister &= PHHAL_HW_RC663_MASK_RXLASTBITS;

        /* Set RxLastBits */
        pDataParams->wAdditionalInfo = bRegister;

        /* Set incomplete byte status if applicable */
        if (bRegister != 0x00)
        {
            status = PH_ERR_SUCCESS_INCOMPLETE_BYTE;
        }
    }

    /* Stop the command / flush the FIFO on error */
    if ((status != PH_ERR_SUCCESS) &&
        (status != PH_ERR_SUCCESS_INCOMPLETE_BYTE))
    {
        /* stop the command */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_COMMAND, PHHAL_HW_RC663_CMD_IDLE));

        /* Flush FiFo */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_FlushFifo(pDataParams));
    }

    /* Store received data length in dataparams */
    pDataParams->wRxBufLen = pDataParams->wRxBufStartPos + wTmpBufferLen;

    /* Return RxBuffer pointer */
    if (ppRxBuffer != NULL)
    {
        *ppRxBuffer = pDataParams->pRxBuffer;
    }

    /* Return RxBuffer length */
    if (pRxLength != NULL)
    {
        *pRxLength = pDataParams->wRxBufLen;
    }

    /* Timing */
    if ((pDataParams->wTimingMode & (uint16_t)~(uint16_t)PHHAL_HW_TIMING_MODE_OPTION_MASK) == PHHAL_HW_TIMING_MODE_FDT)
    {
        /* Calculate FDT Value */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_GetFdt(pDataParams, status, &dwTimingSingle));

        /* FDT single -> replace the previous value */
        if (pDataParams->wTimingMode & PHHAL_HW_TIMING_MODE_OPTION_AUTOCLEAR)
        {
            pDataParams->dwTimingUs = dwTimingSingle;
        }
        /* FDT -> add current value to current count */
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

    return PH_ADD_COMPCODE(status, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_WriteRegister(
                                       phhalHw_Rc663_DataParams_t * pDataParams,
                                       uint8_t bAddress,
                                       uint8_t bValue
                                       )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bDataBuffer[2];
    uint16_t    PH_MEMLOC_REM wBytesRead;
    uint8_t		PH_MEMLOC_REM bNumExpBytes;

    /* RS232 protocol */
    if (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_RS232)
    {
        /* clear RD/NWR bit to indicate write operation */
        bAddress &= 0x7FU;
        bNumExpBytes = 1;
    }
    /* SPI protocol */
    else if (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_SPI)
    {
        /* shift address and clear RD/NWR bit to indicate write operation */
        bAddress = (uint8_t)(bAddress << 1);
        bNumExpBytes = 2;
    }
    /* I2C protocol */
    else if (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_I2C)
    {
        bNumExpBytes = 0;
    }
    else
    {
        /* Insert Code for other protocols here */
        bNumExpBytes = 0;
    }

    /* Write the address and data */
    bDataBuffer[0] = bAddress;
    bDataBuffer[1] = bValue;
    PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Exchange(
        pDataParams->pBalDataParams,
        PH_EXCHANGE_DEFAULT,
        bDataBuffer,
        2,
        bNumExpBytes,
        bDataBuffer,
        &wBytesRead));

    /* Check number of received bytes */
    if (wBytesRead != bNumExpBytes)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_HAL);
    }

    /* RS232 protocol */
    if (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_RS232)
    {
        /* Returned address should match */
        if (bDataBuffer[0] != bAddress)
        {
            return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_HAL);
        }
    }
    /* SPI protocol */
    else if (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_SPI)
    {
        /* nothing to be done */
    }
    /* I2C protocol */
    else if (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_I2C)
    {
        /* nothing to be done */
    }
    else
    {
        /* Insert Code for other protocols here */
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_ReadRegister(
                                      phhalHw_Rc663_DataParams_t * pDataParams,
                                      uint8_t bAddress,
                                      uint8_t * pValue
                                      )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bTxBuffer[2];
    uint16_t    PH_MEMLOC_REM wTxLength;
    uint16_t    PH_MEMLOC_REM wBytesRead;
    uint8_t		PH_MEMLOC_REM bNumExpBytes;

    /* RS232 protocol */
    if (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_RS232)
    {
        /* set RD/NWR bit to indicate read operation */
        bTxBuffer[0] = bAddress | 0x80U;
        wTxLength = 1;
        bNumExpBytes = 1;
    }
    /* SPI protocol */
    else if (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_SPI)
    {
        /* set RD/NWR bit to indicate read operation */
        bTxBuffer[0] = (uint8_t)(bAddress << 1) | 0x01U;
        bTxBuffer[1] = 0x00;
        wTxLength = 2;
        bNumExpBytes = 2;
    }
    /* I2C protocol */
    else if (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_I2C)
    {
        /* nothing to be modified */
        bTxBuffer[0] = bAddress;
        wTxLength = 1;
        bNumExpBytes = 1;
    }
    else
    {
        /* Insert Code for other protocols here */
        wTxLength = 0;
        bNumExpBytes = 0;
    }

    /* Write the address and retrieve the register content */
    PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Exchange(
        pDataParams->pBalDataParams,
        PH_EXCHANGE_DEFAULT,
        bTxBuffer,
        wTxLength,
        bNumExpBytes,
        bTxBuffer,
        &wBytesRead));

    /* Check number of received bytes */
    if (wBytesRead != bNumExpBytes)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_HAL);
    }

    /* in case of SPI 2 bytes are recieved from a read */
    if (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_SPI)
    {
        *pValue = bTxBuffer[1];
    }
    else
    {
        *pValue = bTxBuffer[0];
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_ApplyProtocolSettings(
    phhalHw_Rc663_DataParams_t * pDataParams,
    uint8_t bCardType
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t    PH_MEMLOC_COUNT wIndex;
    uint16_t *  PH_MEMLOC_REM pShadowDefault;
    uint16_t    PH_MEMLOC_REM wShadowCount;
    uint8_t     PH_MEMLOC_REM bUseDefaultShadow;
    uint16_t    PH_MEMLOC_REM wConfig;

    /* Store new card type */
    if (bCardType != PHHAL_HW_CARDTYPE_CURRENT)
    {
        pDataParams->bCardType = bCardType;
        pDataParams->bTimeoutUnit = PHHAL_HW_TIME_MICROSECONDS;
        bUseDefaultShadow = 1;
    }
    else
    {
        bUseDefaultShadow = 0;
    }

    /* configure reader IC for current card */
    switch (pDataParams->bCardType)
    {
        /* configure hardware for ISO 14443A */
    case PHHAL_HW_CARDTYPE_ISO14443A:

        /* Use 14443a default shadow */
        pShadowDefault = (uint16_t*)wRc663_DefaultShadow_I14443a;
        wShadowCount = sizeof(wRc663_DefaultShadow_I14443a) / (sizeof(uint16_t) * 2);
        break;

        /* configure hardware for ISO 14443B */
    case PHHAL_HW_CARDTYPE_ISO14443B:

        /* Use 14443b shadow */
        pShadowDefault = (uint16_t*)wRc663_DefaultShadow_I14443b;
        wShadowCount = sizeof(wRc663_DefaultShadow_I14443b) / (sizeof(uint16_t) * 2);
        break;

        /* configure hardware for FeliCa */
    case PHHAL_HW_CARDTYPE_FELICA:

        /* Use Felica shadow */
        pShadowDefault = (uint16_t*)wRc663_DefaultShadow_Felica;
        wShadowCount = sizeof(wRc663_DefaultShadow_Felica) / (sizeof(uint16_t) * 2);
        break;

        /* configure hardware for ISO15693 */
    case PHHAL_HW_CARDTYPE_ISO15693:

        /* Use ISO15693 shadow */
        pShadowDefault = (uint16_t*)wRc663_DefaultShadow_I15693;
        wShadowCount = sizeof(wRc663_DefaultShadow_I15693) / (sizeof(uint16_t) * 2);
        break;

        /* configure hardware for ICode EPC/UID */
    case PHHAL_HW_CARDTYPE_ICODEEPCUID:

        /* Use EPC/UID shadow */
        pShadowDefault = (uint16_t*)wRc663_DefaultShadow_EpcUid;
        wShadowCount = sizeof(wRc663_DefaultShadow_EpcUid) / (sizeof(uint16_t) * 2);
        break;

        /* configure hardware for ISO18000 Part 3 Mode 3 */
    case PHHAL_HW_CARDTYPE_I18000P3M3:

        /* Use I18000P3M3 shadow */
        pShadowDefault = (uint16_t*)wRc663_DefaultShadow_I18000p3m3;
        wShadowCount = sizeof(wRc663_DefaultShadow_I18000p3m3) / (sizeof(uint16_t) * 2);

        /* Set default start symbol */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetConfig(pDataParams, PHHAL_HW_CONFIG_SYMBOL_START, PHHAL_HW_SYMBOL_I18000P3M3_FSYNC));
        break;

        /* configure hardware for ISO18092 Passive Initiator */
    case PHHAL_HW_CARDTYPE_I18092MPI:

        /* Use ISO18092MPI shadow */
        pShadowDefault = (uint16_t*)wRc663_DefaultShadow_I18092mPI;
        wShadowCount = sizeof(wRc663_DefaultShadow_I18092mPI) / (sizeof(uint16_t) * 2);
        break;

    default:
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Configure generic IC settings */
    if (bCardType != PHHAL_HW_CARDTYPE_CURRENT)
    {
        /* Configure T0 */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(
            pDataParams,
            PHHAL_HW_RC663_REG_T0CONTROL,
            PHHAL_HW_RC663_BIT_TAUTORESTARTED | PHHAL_HW_RC663_BIT_TSTOP_RX | PHHAL_HW_RC663_BIT_TSTART_TX | PHHAL_HW_RC663_VALUE_TCLK_1356_MHZ));

        /* Configure T1 and cascade it with T0 */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(
            pDataParams,
            PHHAL_HW_RC663_REG_T1CONTROL,
            PHHAL_HW_RC663_BIT_TSTOP_RX | PHHAL_HW_RC663_BIT_TSTART_TX | PHHAL_HW_RC663_VALUE_TCLK_T0));

        /* Configure T2 for LFO AutoTrimm */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(
            pDataParams,
            PHHAL_HW_RC663_REG_T2CONTROL,
            PHHAL_HW_RC663_BIT_TSTART_LFO | PHHAL_HW_RC663_VALUE_TCLK_1356_MHZ));

        /* T2 reload value for LFO AutoTrimm*/
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T2RELOADHI, 0x03));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T2RELOADLO, 0xFF));

        /* Configure T3 (for LPCD/ AutoTrimm) */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(
            pDataParams,
            PHHAL_HW_RC663_REG_T3CONTROL,
            PHHAL_HW_RC663_VALUE_TCLK_1356_MHZ));

        /* Set FiFo-Size and Waterlevel */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetConfig(
            pDataParams,
            PHHAL_HW_RC663_CONFIG_FIFOSIZE,
            (uint16_t)pDataParams->bFifoSize));

        /* Init. RxBitCtrl register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_RXBITCTRL, PHHAL_HW_RC663_BIT_VALUESAFTERCOLL));

        /* Init RxSOFD register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_RXSOFD, 0x00));
    }

    /* Copy over default shadow contents into current shadow. */
    if (bUseDefaultShadow)
    {
        /* Initialize config shadow */
        memset(pDataParams->wCfgShadow, 0x00, PHHAL_HW_RC663_SHADOW_COUNT);  /* PRQA S 3200 */

        for (wIndex = 0; wIndex < wShadowCount; ++wIndex)
        {
            wConfig = pShadowDefault[wIndex << 1];
            pDataParams->wCfgShadow[wConfig] = pShadowDefault[(wIndex << 1) + 1];
        }
    }

    /* Evaluate hardware settings */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetCardMode(
        pDataParams,
        pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXDATARATE],
        pDataParams->wCfgShadow[PHHAL_HW_CONFIG_RXDATARATE],
        pDataParams->wCfgShadow[PHHAL_HW_CONFIG_SUBCARRIER]));

    /* Apply shadowed registers */
    for (wIndex = 0; wIndex < wShadowCount; ++wIndex)
    {
        /* Get wConfig */
        wConfig = pShadowDefault[wIndex << 1];

        switch (wConfig)
        {
            /* The following have been already set by phhalHw_Rc663_SetCardMode */
        case PHHAL_HW_CONFIG_TXDATARATE:
        case PHHAL_HW_CONFIG_RXDATARATE:
        case PHHAL_HW_CONFIG_SUBCARRIER:
        case PHHAL_HW_CONFIG_PARITY:
        case PHHAL_HW_CONFIG_TXCRC:
        case PHHAL_HW_CONFIG_RXCRC:
            break;
        case PHHAL_HW_CONFIG_TIMEOUT_VALUE_US:
            if (pDataParams->bTimeoutUnit == PHHAL_HW_TIME_MICROSECONDS)
            {
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetConfig(pDataParams, wConfig, pDataParams->wCfgShadow[wConfig]));
            }
            break;
        case PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS:
            if (pDataParams->bTimeoutUnit == PHHAL_HW_TIME_MILLISECONDS)
            {
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetConfig(pDataParams, wConfig, pDataParams->wCfgShadow[wConfig]));
            }
            break;
        default:
            /* LoadReg Mode */
            if (pDataParams->bLoadRegMode != PH_OFF)
            {
                switch (wConfig)
                {
                    /* Do not overwrite the following configurations */
                case PHHAL_HW_CONFIG_RXDEAFBITS:
                case PHHAL_HW_CONFIG_TXWAIT_US:
                case PHHAL_HW_CONFIG_MODINDEX:
                case PHHAL_HW_CONFIG_ASK100:
                    break;
                    /* Apply all other configurations */
                default:
                    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetConfig(pDataParams, wConfig, pDataParams->wCfgShadow[wConfig]));
                    break;
                }
            }
            /* Default Mode, apply all configurations */
            else
            {
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetConfig(pDataParams, wConfig, pDataParams->wCfgShadow[wConfig]));
            }
            break;
        }
    }

    /* MIFARE Crypto1 state is disabled by default */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams, PHHAL_HW_CONFIG_DISABLE_MF_CRYPTO1, PH_ON));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_SetConfig(
                                   phhalHw_Rc663_DataParams_t * pDataParams,
                                   uint16_t wConfig,
                                   uint16_t wValue
                                   )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t    PH_MEMLOC_REM wDataRate;
    uint8_t     PH_MEMLOC_REM bValue;
    uint8_t     PH_MEMLOC_REM bRegister;
    uint8_t *   PH_MEMLOC_REM pBuffer;
    uint16_t    PH_MEMLOC_REM wBufferLen;
    uint16_t    PH_MEMLOC_REM wBufferSize;

    switch (wConfig)
    {
    case PHHAL_HW_CONFIG_PARITY:
    case PHHAL_HW_CONFIG_TXCRC:
    case PHHAL_HW_CONFIG_RXCRC:
    case PHHAL_HW_CONFIG_TXLASTBITS:
    case PHHAL_HW_CONFIG_ASK100:

        /* Use internal SetConfig */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetConfig_Int(pDataParams, wConfig, wValue));

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;
        break;

    case PHHAL_HW_CONFIG_RXALIGN:

        /* check parameter */
        if (wValue > (PHHAL_HW_RC663_MASK_RXALIGN >> 4))
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_RXBITCTRL, &bRegister));
        bValue = bRegister & (uint8_t)~(uint8_t)PHHAL_HW_RC663_MASK_RXALIGN;
        bValue |= (uint8_t)(wValue << 4);

        /* Only perform the operation, if the new value is different */
        if (bValue != bRegister)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_RXBITCTRL, bValue));
        }

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;
        break;

    case PHHAL_HW_CONFIG_RXDEAFBITS:

        /* Set RxWait */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetRxWait(pDataParams, wValue));

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;
        break;

    case PHHAL_HW_CONFIG_TXWAIT_US:

        /* Set TxWait */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetTxWait(pDataParams, wValue));

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;
        break;

    case PHHAL_HW_CONFIG_CLEARBITSAFTERCOLL:

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_RXBITCTRL, &bRegister));

        /* Disable */
        if (wValue == PH_OFF)
        {
            bValue = bRegister | PHHAL_HW_RC663_BIT_VALUESAFTERCOLL;
        }
        /* Enable */
        else
        {
            bValue = bRegister & (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_VALUESAFTERCOLL;
        }

        /* Only perform the operation, if the new value is different */
        if (bValue != bRegister)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_RXBITCTRL, bValue));
        }

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;
        break;

    case PHHAL_HW_CONFIG_TXDATARATE:

        /* Felica card -> RxDataRate eqals the new TxDataRate */
        if (pDataParams->bCardType == PHHAL_HW_CARDTYPE_FELICA)
        {
            wDataRate = wValue;
        }
        /* Other Cards -> read RxDataRate from shadow */
        else
        {
            wDataRate = pDataParams->wCfgShadow[PHHAL_HW_CONFIG_RXDATARATE];
        }

        /* Update ASK100 value for ISO18092 MPI protocol */
        if (pDataParams->bCardType == PHHAL_HW_CARDTYPE_I18092MPI)
        {
            /* ISO14443 Mode: ASK100 = ON */
            if (wValue == PHHAL_HW_RF_DATARATE_106)
            {
                pDataParams->wCfgShadow[PHHAL_HW_CONFIG_ASK100] = PH_ON;
            }
            /* Felica Mode: ASK100 = OFF */
            else
            {
                pDataParams->wCfgShadow[PHHAL_HW_CONFIG_ASK100] = PH_OFF;
            }
        }

        /* Evaluate hardware settings */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetCardMode(
            pDataParams,
            wValue,
            wDataRate,
            pDataParams->wCfgShadow[PHHAL_HW_CONFIG_SUBCARRIER]));

        /* Felica card -> Update RxDataRate in shadow */
        if (pDataParams->bCardType == PHHAL_HW_CARDTYPE_FELICA)
        {
            pDataParams->wCfgShadow[PHHAL_HW_CONFIG_RXDATARATE] = wDataRate;
        }

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;
        break;

    case PHHAL_HW_CONFIG_RXDATARATE:

        /* Felica card -> TxDataRate eqals the new RxDataRate */
        if (pDataParams->bCardType == PHHAL_HW_CARDTYPE_FELICA)
        {
            wDataRate = wValue;
        }
        /* Other Cards -> read TxDataRate from shadow */
        else
        {
            wDataRate = pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXDATARATE];
        }

        /* Evaluate hardware settings */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetCardMode(
            pDataParams,
            wDataRate,
            wValue,
            pDataParams->wCfgShadow[PHHAL_HW_CONFIG_SUBCARRIER]));

        /* Felica card -> Update TxDataRate in shadow*/
        if (pDataParams->bCardType == PHHAL_HW_CARDTYPE_FELICA)
        {
            pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXDATARATE] = wDataRate;
        }

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;
        break;

    case PHHAL_HW_CONFIG_MODINDEX:

        if(wValue >= 0x20)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        /* Parameter masking */
        wValue &= PHHAL_HW_RC663_MASK_RESIDUAL_CARRIER;

        /* Read out TxAmp register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_TXAMP, &bRegister));

        /* Set modulation index value */
        bValue = (bRegister & (uint8_t)~(uint8_t)PHHAL_HW_RC663_MASK_RESIDUAL_CARRIER) | (uint8_t)wValue;

        /* Only perform the operation, if the new value is different */
        if (bValue != bRegister)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_TXAMP, bValue));
        }

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;
        break;

    case PHHAL_HW_CONFIG_TIMEOUT_VALUE_US:
    case PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS:

        /* Calculate values for Microsecond values */
        if (wConfig == PHHAL_HW_CONFIG_TIMEOUT_VALUE_US)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetFdt(pDataParams, PHHAL_HW_TIME_MICROSECONDS, wValue));
            pDataParams->bTimeoutUnit = PHHAL_HW_TIME_MICROSECONDS;
        }
        /* Calculate values for Millisecond values */
        else
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetFdt(pDataParams, PHHAL_HW_TIME_MILLISECONDS, wValue));
            pDataParams->bTimeoutUnit = PHHAL_HW_TIME_MILLISECONDS;
        }

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;
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
        case PHHAL_HW_TIMING_MODE_FDT:
            pDataParams->dwTimingUs = 0;
            pDataParams->wTimingMode = wValue;
            break;
        case PHHAL_HW_TIMING_MODE_COMM:
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
            (pDataParams->bCardType != PHHAL_HW_CARDTYPE_ISO15693) &&
            (pDataParams->bCardType != PHHAL_HW_CARDTYPE_I18000P3M3))
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
        case PHHAL_HW_SYMBOL_I18000P3M3_PREAMBLE:
        case PHHAL_HW_SYMBOL_I18000P3M3_FSYNC:
            if (pDataParams->bCardType != PHHAL_HW_CARDTYPE_I18000P3M3)
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

        /* Read out TxFrameCon register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_FRAMECON, &bRegister));
        bValue = bRegister & (uint8_t)~(uint8_t)PHHAL_HW_RC663_MASK_STARTSYM;

        /* Set new symbol */
        switch (pDataParams->bSymbolStart)
        {
        case PHHAL_HW_SYMBOL_ICODEEPCUID_SSOF:
            bValue |= PHHAL_HW_RC663_VALUE_START_SYM2;
            break;
        case PHHAL_HW_SYMBOL_ICODEEPCUID_LSOF:
            bValue |= PHHAL_HW_RC663_VALUE_START_SYM0;
            break;
        case PHHAL_HW_SYMBOL_ICODEEPCUID_CS:
            bValue |= PHHAL_HW_RC663_VALUE_START_SYM1;
            break;
        case PHHAL_HW_SYMBOL_I15693_SOF:
            bValue |= PHHAL_HW_RC663_VALUE_START_SYM2;
            break;
        case PHHAL_HW_SYMBOL_I18000P3M3_PREAMBLE:
            bValue |= PHHAL_HW_RC663_VALUE_START_SYM0;
            break;
        case PHHAL_HW_SYMBOL_I18000P3M3_FSYNC:
            bValue |= PHHAL_HW_RC663_VALUE_START_SYM1;
            break;
        default:
            break;
        }

        /* Only perform the operation, if the new value is different */
        if (bValue != bRegister)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_FRAMECON, bValue));
        }
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

        /* Read out TxFrameCon register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_FRAMECON, &bRegister));
        bValue = bRegister & (uint8_t)~(uint8_t)PHHAL_HW_RC663_MASK_STOPSYM;

        /* Set new symbol */
        switch (pDataParams->bSymbolEnd)
        {
        case PHHAL_HW_SYMBOL_ICODEEPCUID_CEOF:
            bValue |= PHHAL_HW_RC663_VALUE_STOP_SYM3;
            break;
        default:
            break;
        }

        /* Only perform the operation, if the new value is different */
        if (bValue != bRegister)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_FRAMECON, bValue));
        }
        break;

    case PHHAL_HW_CONFIG_SUBCARRIER:

        /* Parameter check */
        if ((pDataParams->bCardType != PHHAL_HW_CARDTYPE_ISO15693) &&
            (pDataParams->bCardType != PHHAL_HW_CARDTYPE_I18000P3M3))
        {
            return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_HAL);
        }

        /* Evaluate hardware settings */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetCardMode(
            pDataParams,
            pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXDATARATE],
            pDataParams->wCfgShadow[PHHAL_HW_CONFIG_RXDATARATE],
            wValue));

        /* Update Subcarrier setting */
        pDataParams->wCfgShadow[PHHAL_HW_CONFIG_SUBCARRIER] = wValue;
        break;

    case PHHAL_HW_CONFIG_DISABLE_MF_CRYPTO1:

        /* Disable crypto, enabling is not supported */
        if (wValue != PH_OFF)
        {
            /* Retrieve Status register */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_STATUS, &bRegister));

            /* Clear Crypto1On bit */
            bValue = bRegister & (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_CRYPTO1ON;

            /* Only perform the operation, if the new value is different */
            if (bValue != bRegister)
            {
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_STATUS, bValue));
            }
        }
        break;

    case PHHAL_HW_CONFIG_ADDITIONAL_INFO:

        /* Modify additional info parameter */
        pDataParams->wAdditionalInfo = wValue;
        break;

    case PHHAL_HW_CONFIG_RXBUFFER_STARTPOS:

        /* Retrieve RxBuffer parameters */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_GetRxBuffer(pDataParams, PH_ON, &pBuffer, &wBufferLen, &wBufferSize));

        /* Boundary check */
        if (wValue >= wBufferSize)
        {
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* Set start position */
        pDataParams->wRxBufStartPos = wValue;
        break;

    case PHHAL_HW_CONFIG_TXBUFFER_LENGTH:

        /* Retrieve TxBuffer parameters */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_GetTxBuffer(pDataParams, PH_ON, &pBuffer, &wBufferLen, &wBufferSize));

        /* Check parameter, must not exceed TxBufferSize */
        if (wValue > wBufferSize)
        {
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* set buffer length */
        pDataParams->wTxBufLen = wValue;
        break;

    case PHHAL_HW_CONFIG_TXBUFFER:

        /* Retrieve TxBuffer parameters */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_GetTxBuffer(pDataParams, PH_ON, &pBuffer, &wBufferLen, &wBufferSize));

        /* Check parameter, must not exceed TxBufferSize */
        if (pDataParams->wAdditionalInfo >= wBufferSize)
        {
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* Modify TxBuffer byte */
        pBuffer[pDataParams->wAdditionalInfo] = (uint8_t)wValue;
        break;

    case PHHAL_HW_CONFIG_MAX_PRECACHED_BYTES:

        /* Check parameter */
        if (((pDataParams->bFifoSize == PHHAL_HW_RC663_VALUE_FIFOSIZE_255) && (wValue > 0xFF)) ||
            ((pDataParams->bFifoSize == PHHAL_HW_RC663_VALUE_FIFOSIZE_512) && (wValue > 0x200)))
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        /* Store parameter*/
        pDataParams->wMaxPrecachedBytes = wValue;
        break;

    case PHHAL_HW_CONFIG_BAL_CONNECTION:

        /* parameter check */
        if (wValue > PHHAL_HW_BAL_CONNECTION_I2C)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        pDataParams->bBalConnectionType = (uint8_t)wValue;
        break;

    case PHHAL_HW_CONFIG_SERIAL_BITRATE:

        switch (wValue)
        {
        case PHHAL_HW_RS232_BITRATE_7200:
            bRegister = PHHAL_HW_RC663_SERIALSPEED_7200;
            break;
        case PHHAL_HW_RS232_BITRATE_9600:
            bRegister = PHHAL_HW_RC663_SERIALSPEED_9600;
            break;
        case PHHAL_HW_RS232_BITRATE_14400:
            bRegister = PHHAL_HW_RC663_SERIALSPEED_14400;
            break;
        case PHHAL_HW_RS232_BITRATE_19200:
            bRegister = PHHAL_HW_RC663_SERIALSPEED_19200;
            break;
        case PHHAL_HW_RS232_BITRATE_38400:
            bRegister = PHHAL_HW_RC663_SERIALSPEED_38400;
            break;
        case PHHAL_HW_RS232_BITRATE_57600:
            bRegister = PHHAL_HW_RC663_SERIALSPEED_57600;
            break;
        case PHHAL_HW_RS232_BITRATE_115200:
            bRegister = PHHAL_HW_RC663_SERIALSPEED_115200;
            break;
        case PHHAL_HW_RS232_BITRATE_128000:
            bRegister = PHHAL_HW_RC663_SERIALSPEED_128000;
            break;
        case PHHAL_HW_RS232_BITRATE_230400:
            bRegister = PHHAL_HW_RC663_SERIALSPEED_230400;
            break;
        case PHHAL_HW_RS232_BITRATE_460800:
            bRegister = PHHAL_HW_RC663_SERIALSPEED_460800;
            break;
        case PHHAL_HW_RS232_BITRATE_921600:
            bRegister = PHHAL_HW_RC663_SERIALSPEED_921600;
            break;
        case PHHAL_HW_RS232_BITRATE_1228800:
            bRegister = PHHAL_HW_RC663_SERIALSPEED_1228800;
            break;
        default:
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        /* Set the register value */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_SERIALSPEED, bRegister));
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

    case PHHAL_HW_RC663_CONFIG_FIFOSIZE:

        /* configure the water level */
        if (wValue == PHHAL_HW_RC663_VALUE_FIFOSIZE_255)
        {
            /* Set 255 bytes and clear Waterlevel High-Bit */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(
                pDataParams,
                PHHAL_HW_RC663_REG_FIFOCONTROL,
                PHHAL_HW_RC663_BIT_FIFOSIZE | PHHAL_HW_RC663_BIT_FLUSHFIFO));

            /* Also reset max. precached bytes if neccessary */
            if (pDataParams->wMaxPrecachedBytes > PHHAL_HW_RC663_PRECACHED_BYTES)
            {
                pDataParams->wMaxPrecachedBytes = PHHAL_HW_RC663_PRECACHED_BYTES;
            }

            /* Set Waterlevel to FifoSize - 1 */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(
                pDataParams,
                PHHAL_HW_RC663_REG_WATERLEVEL,
                0xFE));
        }
        else if (wValue == PHHAL_HW_RC663_VALUE_FIFOSIZE_512)
        {
            /* Set 512 bytes and Waterlevel High-Bit */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(
                pDataParams,
                PHHAL_HW_RC663_REG_FIFOCONTROL,
                PHHAL_HW_RC663_BIT_FLUSHFIFO | PHHAL_HW_RC663_BIT_WATERLEVEL_HI));

            /* Set Waterlevel to FifoSize - 1 */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(
                pDataParams,
                PHHAL_HW_RC663_REG_WATERLEVEL,
                0xFF));
        }
        else
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        /* Save Fifo-Size */
        pDataParams->bFifoSize = (uint8_t)wValue;
        break;

    case PHHAL_HW_RC663_CONFIG_LOADREG_MODE:

        if (wValue != PH_OFF)
        {
            /* Check use condition */
            if (pDataParams->pLoadRegConfig == NULL)
            {
                return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_HAL);
            }
            pDataParams->bLoadRegMode = PH_ON;
        }
        else
        {
            pDataParams->bLoadRegMode = PH_OFF;
        }
        break;

    default:
        return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_HAL);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_GetConfig(
                                   phhalHw_Rc663_DataParams_t * pDataParams,
                                   uint16_t wConfig,
                                   uint16_t * pValue
                                   )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bRegister;
    uint8_t *   PH_MEMLOC_REM pBuffer;
    uint16_t    PH_MEMLOC_REM wBufferLen;
    uint16_t    PH_MEMLOC_REM wBufferSize;

    switch (wConfig)
    {
    case PHHAL_HW_CONFIG_PARITY:
    case PHHAL_HW_CONFIG_TXCRC:
    case PHHAL_HW_CONFIG_RXCRC:
    case PHHAL_HW_CONFIG_TXLASTBITS:

        /* Read config from shadow */
        *pValue = pDataParams->wCfgShadow[wConfig];
        break;

    case PHHAL_HW_CONFIG_ADDITIONAL_INFO:
    case PHHAL_HW_CONFIG_RXLASTBITS:

        *pValue = pDataParams->wAdditionalInfo;
        break;

    case PHHAL_HW_CONFIG_RXDEAFBITS:
    case PHHAL_HW_CONFIG_TXWAIT_US:
    case PHHAL_HW_CONFIG_CLEARBITSAFTERCOLL:
    case PHHAL_HW_CONFIG_TXDATARATE:
    case PHHAL_HW_CONFIG_RXDATARATE:
    case PHHAL_HW_CONFIG_MODINDEX:
    case PHHAL_HW_CONFIG_ASK100:

        /* Read config from shadow */
        *pValue = pDataParams->wCfgShadow[wConfig];
        break;

    case PHHAL_HW_CONFIG_TIMEOUT_VALUE_US:

        if (pDataParams->bTimeoutUnit == PHHAL_HW_TIME_MICROSECONDS)
        {
            *pValue = pDataParams->wCfgShadow[wConfig];
        }
        else
        {
            if (pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS] > (0xFFFF / 1000))
            {
                return PH_ADD_COMPCODE(PH_ERR_PARAMETER_OVERFLOW, PH_COMP_HAL);
            }
            *pValue = pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS] * 1000;
        }
        break;

    case PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS:

        if (pDataParams->bTimeoutUnit == PHHAL_HW_TIME_MILLISECONDS)
        {
            *pValue = pDataParams->wCfgShadow[wConfig];
        }
        else
        {
            *pValue = pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TIMEOUT_VALUE_US] / 1000;
        }
        break;

    case PHHAL_HW_CONFIG_TIMING_MODE:

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

    case PHHAL_HW_CONFIG_SUBCARRIER:

        /* Read config from shadow */
        *pValue = pDataParams->wCfgShadow[wConfig];
        break;

    case PHHAL_HW_CONFIG_FIELD_OFF_TIME:

        *pValue = pDataParams->wFieldOffTime;
        break;

    case PHHAL_HW_CONFIG_FIELD_RECOVERY_TIME:

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

    case PHHAL_HW_CONFIG_DISABLE_MF_CRYPTO1:

        /* Retrieve Status register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_STATUS, &bRegister));

        /* Check Crypto1On bit */
        if (bRegister & PHHAL_HW_RC663_BIT_CRYPTO1ON)
        {
            *pValue = PH_OFF; /* OFF in this case means "Crypto1 not disabled --> enabled" */
        }
        else
        {
            *pValue = PH_ON; /* ON in this case means "Crypto1 is disabled" */
        }
        break;

    case PHHAL_HW_CONFIG_RXBUFFER_STARTPOS:

        /* Return parameter */
        *pValue = pDataParams->wRxBufStartPos;
        break;

    case PHHAL_HW_CONFIG_RXBUFFER_BUFSIZE:

        /* Retrieve RxBuffer parameters */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_GetRxBuffer(pDataParams, PH_ON, &pBuffer, &wBufferLen, &wBufferSize));

        /* Return parameter */
        *pValue = wBufferSize;
        break;

    case PHHAL_HW_CONFIG_TXBUFFER_BUFSIZE:

        /* Retrieve TxBuffer parameters */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_GetTxBuffer(pDataParams, PH_ON, &pBuffer, &wBufferLen, &wBufferSize));

        /* Return parameter */
        *pValue = wBufferSize;
        break;

    case PHHAL_HW_CONFIG_TXBUFFER_LENGTH:

        /* Retrieve TxBuffer parameters */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_GetTxBuffer(pDataParams, PH_ON, &pBuffer, &wBufferLen, &wBufferSize));

        /* Return parameter */
        *pValue = wBufferLen;
        break;

    case PHHAL_HW_CONFIG_TXBUFFER:

        /* Retrieve TxBuffer parameters */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_GetTxBuffer(pDataParams, PH_ON, &pBuffer, &wBufferLen, &wBufferSize));

        /* Check additional info parameter */
        if (pDataParams->wAdditionalInfo >= wBufferSize)
        {
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* Retrieve TxBuffer byte */
        *pValue = (uint16_t)pBuffer[pDataParams->wAdditionalInfo];
        break;

    case PHHAL_HW_CONFIG_MAX_PRECACHED_BYTES:

        /* Return parameter */
        *pValue = pDataParams->wMaxPrecachedBytes;
        break;

    case PHHAL_HW_CONFIG_BAL_CONNECTION:

        /* Return parameter */
        *pValue = (uint16_t)pDataParams->bBalConnectionType;
        break;

    case PHHAL_HW_CONFIG_SERIAL_BITRATE:

        /* Read the register value */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_SERIALSPEED, &bRegister));

        switch (bRegister)
        {
        case PHHAL_HW_RC663_SERIALSPEED_7200:
            *pValue = PHHAL_HW_RS232_BITRATE_7200;
            break;
        case PHHAL_HW_RC663_SERIALSPEED_9600:
            *pValue = PHHAL_HW_RS232_BITRATE_9600;
            break;
        case PHHAL_HW_RC663_SERIALSPEED_14400:
            *pValue = PHHAL_HW_RS232_BITRATE_14400;
            break;
        case PHHAL_HW_RC663_SERIALSPEED_19200:
            *pValue = PHHAL_HW_RS232_BITRATE_19200;
            break;
        case PHHAL_HW_RC663_SERIALSPEED_38400:
            *pValue = PHHAL_HW_RS232_BITRATE_38400;
            break;
        case PHHAL_HW_RC663_SERIALSPEED_57600:
            *pValue = PHHAL_HW_RS232_BITRATE_57600;
            break;
        case PHHAL_HW_RC663_SERIALSPEED_115200:
            *pValue = PHHAL_HW_RS232_BITRATE_115200;
            break;
        case PHHAL_HW_RC663_SERIALSPEED_128000:
            *pValue = PHHAL_HW_RS232_BITRATE_128000;
            break;
        case PHHAL_HW_RC663_SERIALSPEED_230400:
            *pValue = PHHAL_HW_RS232_BITRATE_230400;
            break;
        case PHHAL_HW_RC663_SERIALSPEED_460800:
            *pValue = PHHAL_HW_RS232_BITRATE_460800;
            break;
        case PHHAL_HW_RC663_SERIALSPEED_921600:
            *pValue = PHHAL_HW_RS232_BITRATE_921600;
            break;
        case PHHAL_HW_RC663_SERIALSPEED_1228800:
            *pValue = PHHAL_HW_RS232_BITRATE_1228800;
            break;
        default:
            return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
        }
        break;

    case PHHAL_HW_CONFIG_RFRESET_ON_TIMEOUT:

        /* Return parameter */
        *pValue = (uint16_t)pDataParams->bRfResetAfterTo;
        break;

    case PHHAL_HW_RC663_CONFIG_FIFOSIZE:

        /* Return parameter */
        *pValue = (uint16_t)pDataParams->bFifoSize;
        break;

    case PHHAL_HW_RC663_CONFIG_LOADREG_MODE:

        /* Return parameter */
        *pValue = (uint16_t)pDataParams->bLoadRegMode;
        break;

    default:
        return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_HAL);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_FieldOn(
                                 phhalHw_Rc663_DataParams_t * pDataParams
                                 )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bRegister;

    /* Read out DrvMode register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_DRVMODE, &bRegister));

    /* Enable Drivers */
    bRegister |= PHHAL_HW_RC663_BIT_TXEN;

    /* Write DrvMode register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_DRVMODE, bRegister));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_FieldOff(
                                  phhalHw_Rc663_DataParams_t * pDataParams
                                  )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bRegister;

    /* Read out DrvMode register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_DRVMODE, &bRegister));

    /* Disable Drivers */
    bRegister &= (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_TXEN;

    /* Write DrvMode register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_DRVMODE, bRegister));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_FieldReset(
                                    phhalHw_Rc663_DataParams_t * pDataParams
                                    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;

    /* Switch off the field */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_FieldOff(pDataParams));

    /* wait for field-off timeout */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_Wait(
        pDataParams,
        PHHAL_HW_TIME_MILLISECONDS,
        pDataParams->wFieldOffTime));

    /* switch on the field again */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_FieldOn(pDataParams));

    /* wait for field-recovery timeout */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_Wait(
        pDataParams,
        PHHAL_HW_TIME_MILLISECONDS,
        pDataParams->wFieldRecoveryTime));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_Wait(
                              phhalHw_Rc663_DataParams_t * pDataParams,
                              uint8_t bUnit,
                              uint16_t wTimeout
                              )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bControlReg;
    uint8_t     PH_MEMLOC_REM bIrqRq;

    /* Parameter check */
    if ((bUnit != PHHAL_HW_TIME_MICROSECONDS) && (bUnit != PHHAL_HW_TIME_MILLISECONDS))
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Set temporary timeout */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetFdt(pDataParams, bUnit, wTimeout));

    /* retrieve content of Timer Control register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_TCONTROL, &bControlReg));

    /* clear all irq flags */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_IRQ1, (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_SET));

    /* manually start T0 */
    bControlReg |= PHHAL_HW_RC663_BIT_T0STARTSTOPNOW | PHHAL_HW_RC663_BIT_T0RUNNING;
    /* manually start T1 */
    bControlReg |= PHHAL_HW_RC663_BIT_T1STARTSTOPNOW | PHHAL_HW_RC663_BIT_T1RUNNING;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_TCONTROL, bControlReg));

    /* wait for timer interrupt */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_WaitIrq(pDataParams, PH_ON, PH_OFF, 0x00, PHHAL_HW_RC663_BIT_TIMER1IRQ, NULL, &bIrqRq));

    /* manually stop T0 */
    bControlReg &= (uint8_t)~(uint8_t)(PHHAL_HW_RC663_BIT_T0RUNNING | PHHAL_HW_RC663_BIT_T1RUNNING);
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_TCONTROL, bControlReg));

    /* Restore previous timeout */
    if (pDataParams->bTimeoutUnit == PHHAL_HW_TIME_MICROSECONDS)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetFdt(
            pDataParams,
            PHHAL_HW_TIME_MICROSECONDS,
            pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TIMEOUT_VALUE_US]));
    }
    else
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetFdt(
            pDataParams,
            PHHAL_HW_TIME_MILLISECONDS,
            pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS]));
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_MfcAuthenticateKeyNo(
    phhalHw_Rc663_DataParams_t * pDataParams,
    uint8_t bBlockNo,
    uint8_t bKeyType,
    uint16_t wKeyNo,
    uint16_t wKeyVersion,
    uint8_t * pUid
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bKeyNoInt;

    /* check key version */
    if (wKeyVersion != 0)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* set keytype and keynumber */
    if (bKeyType == PHHAL_HW_MFC_KEYA)
    {
        /* check key number */
        if (wKeyNo >= (PHHAL_HW_RC663_MAX_NUM_KEYS >> 1))
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }
        bKeyNoInt = (uint8_t)(wKeyNo << 1);
    }
    else if (bKeyType == PHHAL_HW_MFC_KEYB)
    {
        /* check key number */
        if (wKeyNo >= ((PHHAL_HW_RC663_MAX_NUM_KEYS >> 1) - 1))
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }
        bKeyNoInt = (uint8_t)(wKeyNo << 1) + 1;
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* load key from EEPROM */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_Cmd_LoadKeyE2(
        pDataParams,
        bKeyNoInt));

    /* execute Authenticate command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_MfcAuthenticate_Int(
        pDataParams,
        bBlockNo,
        bKeyType,
        pUid));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_MfcAuthenticate(
    phhalHw_Rc663_DataParams_t * pDataParams,
    uint8_t bBlockNo,
    uint8_t bKeyType,
    uint8_t * pKey,
    uint8_t * pUid
    )
{
    phStatus_t PH_MEMLOC_REM statusTmp;

    /* load key directly */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_Cmd_LoadKey(
        pDataParams,
        pKey));

    /* execute Authenticate command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_MfcAuthenticate_Int(
        pDataParams,
        bBlockNo,
        bKeyType,
        pUid));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

#endif /* NXPBUILD__PHHAL_HW_RC663 */
