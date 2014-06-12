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
* RC632 specific HAL-Component of Reader Library Framework.
* $Author: jayaprakash.desai $
* $Revision: 1.2 $
* $Date: Wed May 25 14:06:21 2011 $
*
* History:
*/
#include <ph_Status.h>
#include <string.h>
#include <stdlib.h>
#include <phbalReg.h>
#include <phhalHw.h>
#include <ph_RefDefs.h>
#include <math.h>

#ifdef NXPBUILD__PHHAL_HW_RC632

#include "phhalHw_Rc632.h"
#include "phhalHw_Rc632_Int.h"
#include "phhalHw_Rc632_Config.h"

/* Default shadow for ISO14443-3A Mode */
static uint16_t wRc632_DefaultShadow_14443a[][2] =
{
    {PHHAL_HW_CONFIG_PARITY,                PH_ON},
    {PHHAL_HW_CONFIG_TXCRC,                 PH_OFF},
    {PHHAL_HW_CONFIG_RXCRC,                 PH_OFF},
    {PHHAL_HW_CONFIG_RXDEAFBITS,            0x0008},
    {PHHAL_HW_CONFIG_TXDATARATE,            PHHAL_HW_RF_DATARATE_106},
    {PHHAL_HW_CONFIG_RXDATARATE,            PHHAL_HW_RF_DATARATE_106},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,      150}, 
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS,      0x0000}, 
    {PHHAL_HW_CONFIG_MODINDEX,              0x3F}, 
    {PHHAL_HW_CONFIG_ASK100,                PH_ON}
};

/* Default shadow for ISO14443-3B Mode */
static uint16_t wRc632_DefaultShadow_I14443b[][2] =
{
    {PHHAL_HW_CONFIG_PARITY,                PH_OFF},
    {PHHAL_HW_CONFIG_TXCRC,                 PH_ON},
    {PHHAL_HW_CONFIG_RXCRC,                 PH_ON},
    {PHHAL_HW_CONFIG_RXDEAFBITS,            0x0008},
    {PHHAL_HW_CONFIG_TXDATARATE,            PHHAL_HW_RF_DATARATE_106},
    {PHHAL_HW_CONFIG_RXDATARATE,            PHHAL_HW_RF_DATARATE_106},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,      150},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS,      0x0000},
    {PHHAL_HW_CONFIG_MODINDEX,              PHHAL_HW_RC632_MODINDEX_I14443B},
    {PHHAL_HW_CONFIG_ASK100,                PH_OFF}
};


/* Default shadow for ISO15693 Mode */
static uint16_t wRc632_DefaultShadow_15693[][2] =
{
    {PHHAL_HW_CONFIG_PARITY,                PH_OFF},
    {PHHAL_HW_CONFIG_TXCRC,                 PH_ON},
    {PHHAL_HW_CONFIG_RXCRC,                 PH_ON},
    {PHHAL_HW_CONFIG_RXDEAFBITS,            0x0009},
    {PHHAL_HW_CONFIG_TXDATARATE,            PHHAL_HW_RF_TX_DATARATE_1_OUT_OF_4},
    {PHHAL_HW_CONFIG_RXDATARATE,            PHHAL_HW_RF_RX_DATARATE_HIGH},
    {PHHAL_HW_CONFIG_SUBCARRIER,            PHHAL_HW_SUBCARRIER_SINGLE},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,      150},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS,      0x0000},
    {PHHAL_HW_CONFIG_MODINDEX,              PHHAL_HW_RC632_MODINDEX_I15693},
    {PHHAL_HW_CONFIG_ASK100,                PH_ON}
};

/* Default shadow for ICode EPC/UID Mode */
static uint16_t wRc632_DefaultShadow_ICodeEpcUid[][2] =
{
    {PHHAL_HW_CONFIG_PARITY,                PH_OFF},
    {PHHAL_HW_CONFIG_TXCRC,                 PH_OFF},
    {PHHAL_HW_CONFIG_RXCRC,                 PH_OFF},
    {PHHAL_HW_CONFIG_RXDEAFBITS,            0x0006},
    {PHHAL_HW_CONFIG_TXDATARATE,            PHHAL_HW_RF_DATARATE_EPCUID},
    {PHHAL_HW_CONFIG_RXDATARATE,            PHHAL_HW_RF_DATARATE_EPCUID},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,      150},
    {PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS,      0x0000},
    {PHHAL_HW_CONFIG_MODINDEX,              PHHAL_HW_RC632_MODINDEX_EPCUID},
    {PHHAL_HW_CONFIG_ASK100,                PH_OFF}
};

phStatus_t phhalHw_Rc632_Init(
                              phhalHw_Rc632_DataParams_t * pDataParams, 
                              uint16_t wSizeOfDataParams,
                              void * pBalDataParams,
                              uint8_t* pTxBuffer,
                              uint16_t wTxBufSize,
                              uint8_t* pRxBuffer,
                              uint16_t wRxBufSize
                              )
{
    /* Dataparam check */
    if (sizeof(phhalHw_Rc632_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_HAL);
    }
    if (wTxBufSize < PHHAL_HW_RC632_RESERVED_BUFFER_LEN|| wRxBufSize < PHHAL_HW_RC632_RESERVED_BUFFER_LEN)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }
    /* Pointer check*/
    PH_ASSERT_NULL (pDataParams);
    PH_ASSERT_NULL (pTxBuffer);
    PH_ASSERT_NULL (pRxBuffer);

    /* Init. private data */
    pDataParams->wId                    = PH_COMP_HAL | PHHAL_HW_RC632_ID;
    pDataParams->pBalDataParams			= pBalDataParams;
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
    pDataParams->bTimeoutUnit           = PHHAL_HW_TIME_MICROSECONDS;
    pDataParams->dwTimingUs				= 0;
    pDataParams->wFieldOffTime          = PHHAL_HW_FIELD_OFF_DEFAULT;
    pDataParams->wFieldRecoveryTime     = PHHAL_HW_FIELD_RECOVERY_DEFAULT;
    pDataParams->bSymbolStart			= PH_OFF;
    pDataParams->bSymbolEnd				= PH_OFF;
    pDataParams->wMaxPrecachedBytes     = PHHAL_HW_RC632_PRECACHED_BYTES;
    pDataParams->wAdditionalInfo        = 0;
    pDataParams->bFifoSize				= PHHAL_HW_RC632_PRECACHED_BYTES;
    pDataParams->bBalConnectionType     = PHHAL_HW_BAL_CONNECTION_SPI;
    pDataParams->bRfResetAfterTo        = PH_OFF;


    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc632_Exchange(
                                  phhalHw_Rc632_DataParams_t * pDataParams, 
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
    uint8_t *   PH_MEMLOC_REM pTxBufferPre = NULL;
    uint16_t    PH_MEMLOC_REM wFifoBytes;
    uint16_t    PH_MEMLOC_REM wRxBufLen;
    uint16_t    PH_MEMLOC_REM wRxBufSize;
    uint8_t     PH_MEMLOC_REM bIrqWaitFor;
    uint8_t     PH_MEMLOC_REM bIrqReg = 0x00;
    uint8_t     PH_MEMLOC_REM bRegister;
    uint8_t     PH_MEMLOC_REM bError;
    uint32_t    PH_MEMLOC_REM dwTimingSingle;

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
    if ((wOption & PH_EXCHANGE_BUFFERED_BIT)||
        (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_SPI))
    {
        if (wTxLength != 0)
        {
            /* TxBuffer overflow check */
            if ((pDataParams->wTxBufStartPos + pDataParams->wTxBufLen + wTxLength) > pDataParams->wTxBufSize)
            {
                pDataParams->wTxBufLen = 0;
                return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
            }

            /* copy data */
            memcpy(&pDataParams->pTxBuffer[pDataParams->wTxBufStartPos + pDataParams->wTxBufLen], pTxBuffer, wTxLength);  /* PRQA S 3200 */
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

    /* Terminate a probably running command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, 
        PHHAL_HW_RC632_REG_COMMAND, 
        PHHAL_HW_RC632_CMD_IDLE));

    /* Flush FiFo */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_FlushFifo(pDataParams));

    /* write data into FIFO */
    if (pDataParams->wTxBufLen || wTxLength)
    {
        /* write preset data into FiFo buffer */
        wNumPrecachedBytes = (pDataParams->wTxBufLen > pDataParams->wMaxPrecachedBytes) ? 
            pDataParams->wMaxPrecachedBytes : pDataParams->wTxBufLen;
        status = phhalHw_Rc632_WriteFifo(pDataParams, 
            &pDataParams->pTxBuffer[pDataParams->wTxBufStartPos], 
            wNumPrecachedBytes, 
            &wFifoBytes);
        /* ignore FiFo overflow warning */
        if ((wNumPrecachedBytes != pDataParams->wMaxPrecachedBytes) 
            && ((status & PH_ERR_MASK) != PH_ERR_BUFFER_OVERFLOW))
        {
            PH_CHECK_SUCCESS(status);

            /* No overflow, reset preset buffer length */
            pDataParams->wTxBufLen = 0;

            /* write data to transmit into FiFo buffer */
            wNumPrecachedBytes = (wTxLength > (pDataParams->wMaxPrecachedBytes - wNumPrecachedBytes)) ? 
                (pDataParams->wMaxPrecachedBytes - wNumPrecachedBytes) : wTxLength;
            status = phhalHw_Rc632_WriteFifo(pDataParams, pTxBuffer, wNumPrecachedBytes, &wFifoBytes);

            /* Ignore FiFo overflow warning */
            if ((status & PH_ERR_MASK) != PH_ERR_BUFFER_OVERFLOW)
            {
                PH_CHECK_SUCCESS(status);
            }

            /* Adjust TxBuffer */
            pTxBuffer += wFifoBytes;
            wTxLength = wTxLength - wFifoBytes;
        }
        else
        {
            /* Update preset buffer and length */
            pTxBufferPre = &pDataParams->pTxBuffer[pDataParams->wTxBufStartPos + wFifoBytes];
            pDataParams->wTxBufLen = pDataParams->wTxBufLen - wFifoBytes;
        }
    }

    /* clear all IRQ flags */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, 
        PHHAL_HW_RC632_REG_INT_REQ, 
        (uint8_t)~(uint8_t)PHHAL_HW_RC632_BIT_IRQ));

    /* start the command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, 
        PHHAL_HW_RC632_REG_COMMAND, 
        PHHAL_HW_RC632_CMD_TRANSCEIVE));
    /* Write the remaining data into the Fifo */
    /* (Only possible if interface to RC is fast enough!) */
    while (pDataParams->wTxBufLen || wTxLength)
    {
        /* read interrupt status */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, 
            PHHAL_HW_RC632_REG_INT_REQ, 
            &bIrqReg));

        /* If we got data to write to the FIFO but the command terminated, we were too slow! */
        if ((bIrqReg & PHHAL_HW_RC632_BIT_IDLEIRQ) || (bIrqReg & PHHAL_HW_RC632_BIT_TXIRQ))
        {
            /* stop the command */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(
                pDataParams, 
                PHHAL_HW_RC632_REG_COMMAND, 
                PHHAL_HW_RC632_CMD_IDLE));

            /* Flush FiFo */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_FlushFifo(pDataParams));

            /* Reset TxLastBits */
            if (pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXLASTBITS] != 0)
            {
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_SetConfig(pDataParams, 
                    PHHAL_HW_CONFIG_TXLASTBITS, 
                    0x00));
            }

            return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
        }

        /* write remaining data to transmit into FiFo buffer */
        if (pDataParams->wTxBufLen)
        {
            status = phhalHw_Rc632_WriteFifo(pDataParams, pTxBufferPre, pDataParams->wTxBufLen, &wFifoBytes);
        }
        else
        {
            status = phhalHw_Rc632_WriteFifo(pDataParams, pTxBuffer, wTxLength, &wFifoBytes);
        }

        /* Ignore FiFo overflow warning */
        if ((status & PH_ERR_MASK) != PH_ERR_BUFFER_OVERFLOW)
        {
            PH_CHECK_SUCCESS(status);
        }

        /* Adjust TxBuffer */
        if (pDataParams->wTxBufLen)
        {
            pTxBufferPre += wFifoBytes;
            pDataParams->wTxBufLen = pDataParams->wTxBufLen - wFifoBytes;
        }
        else
        {
            pTxBuffer += wFifoBytes;
            wTxLength = wTxLength - wFifoBytes;
        }
    }

    /* Set wait IRQs */
    bIrqWaitFor = PHHAL_HW_RC632_BIT_TXIRQ | PHHAL_HW_RC632_BIT_IDLEIRQ | PHHAL_HW_RC632_BIT_TIMERIRQ;

    /* wait until the transmission is finished */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WaitIrq(
        pDataParams, 
        bIrqWaitFor, 
        &bIrqReg));

    /* Let's now wait for the RX Irq.*/
    if (!(bIrqReg & PHHAL_HW_RC632_BIT_IDLEIRQ) && !(bIrqReg & PHHAL_HW_RC632_BIT_TIMERIRQ)) /* && !(bIrq0Reg & PHHAL_HW_RC632_BIT_ERRIRQ)) */
    {
        /* Clear high-alert irq flag */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, 
            PHHAL_HW_RC632_REG_INT_REQ, 
            PHHAL_HW_RC632_BIT_HIALERTIRQ));

        /* Change wait IRQs */
        bIrqWaitFor = PHHAL_HW_RC632_BIT_RXIRQ | 
            PHHAL_HW_RC632_BIT_HIALERTIRQ | 
            PHHAL_HW_RC632_BIT_IDLEIRQ | 
            PHHAL_HW_RC632_BIT_TIMERIRQ;

        /* wait until reception */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WaitIrq(
            pDataParams, 
            bIrqWaitFor, 
            &bIrqReg));
    }

    /* Reset TxLastBits */
    if (pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXLASTBITS] != 0)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_SetConfig(pDataParams, PHHAL_HW_CONFIG_TXLASTBITS, 0x00));
    }
    /* Timeout handling */
    if ((bIrqWaitFor & PHHAL_HW_RC632_BIT_TIMERIRQ) && (bIrqReg & PHHAL_HW_RC632_BIT_TIMERIRQ))
    {

        /* retrieve content of Timer Control register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, 
            PHHAL_HW_RC632_REG_TIMER_CONTROL, 
            &bRegister));
        /* manually stop timers */
        bRegister |= PHHAL_HW_RC632_BIT_TSTOPNOW;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, 
            PHHAL_HW_RC632_REG_TIMER_CONTROL, 
            bRegister));

        /* Reset after timeout behaviour */
        if (pDataParams->bRfResetAfterTo != PH_OFF)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_FieldReset(pDataParams));
        }

        status = PH_ERR_IO_TIMEOUT;
    }
    else
    {
        status = PH_ERR_SUCCESS;
    }

    /* Set receive buffer properties */
    pDataParams->wRxBufLen = pDataParams->wRxBufStartPos;
    wRxBufSize = pDataParams->wRxBufSize - pDataParams->wRxBufLen;
    wRxBufLen = 0;

    /* Do the following if no timeout occured */
    if (status == PH_ERR_SUCCESS)
    {
        /* mask out high-alert */
        bIrqWaitFor &= (uint8_t)~(uint8_t)PHHAL_HW_RC632_BIT_HIALERTIRQ;

        /* retrieve fifo bytes */
        do
        {
            /* retrieve bytes from FiFo */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadFifo(
                pDataParams, 
                wRxBufSize, 
                &pDataParams->pRxBuffer[pDataParams->wRxBufLen + wRxBufLen], 
                &wFifoBytes));

            /* advance receive buffer */
            wRxBufLen = wRxBufLen + wFifoBytes;
            wRxBufSize = wRxBufSize - wFifoBytes;

            /* read interrupt status */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, 
                PHHAL_HW_RC632_REG_INT_REQ, 
                &bIrqReg));
        }
        while ((!(bIrqReg & bIrqWaitFor) || (wFifoBytes != 0)));

        /* Check if an error occured */
        /*
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_PRIMARY_STATUS, &bError));
        if (bError & PHHAL_HW_RC632_BIT_ERRIRQ)
        {
        */
        /* read the error register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, 
            PHHAL_HW_RC632_REG_ERROR_FLAG, 
            &bError));

        /* buffer overflow */
        if (bError & PHHAL_HW_RC632_BIT_FIFO_OVF)
        {
            status = PH_ERR_BUFFER_OVERFLOW;
        }
        /* Framing error */
        else if (bError & PHHAL_HW_RC632_BIT_FRAMING_ERR)
        {
            status = PH_ERR_FRAMING_ERROR;
        }
        else if(bError & PHHAL_HW_RC632_BIT_COLL_ERR)
        {
            /* No bytes received -> timeout */
            if (wRxBufLen == 0)
            {
                status = PH_ERR_IO_TIMEOUT;
            }
            /* Else perform collision handling */
            else
            {
                status = PH_ERR_COLLISION_ERROR;

                /* Retreive collision position*/
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, 
                    PHHAL_HW_RC632_REG_COLL_POS, 
                    &bRegister));
                if(bRegister == 0x0)
                {
                    wRxBufLen = 0;

                }
                else
                {
                    wRxBufLen = ((uint8_t)(bRegister - 1) >> 3);
                }

                /* Restore wRxBufSize */
                wRxBufSize = wRxBufSize + wRxBufLen;

                /* Incomplete byte also counts as received byte */
                if (bRegister)
                {
                    /* Check for buffer overflow */
                    if (wRxBufLen == wRxBufSize)
                    {
                        status = PH_ERR_BUFFER_OVERFLOW;
                    }
                    else
                    {
                        ++wRxBufLen;
                    }
                    /* Store valid bits of last byte */
                    pDataParams->wAdditionalInfo = bRegister - 1;
                }
                else
                {
                    /* Store valid bits of last byte */
                    pDataParams->wAdditionalInfo = 0;
                }
            }			
        }
        /* Parity error */
        else if (bError & PHHAL_HW_RC632_BIT_PARITY_ERR)
        {
            status = PH_ERR_PROTOCOL_ERROR;
        }
        else if(bError & PHHAL_HW_RC632_BIT_CRC_ERR)
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
        /* No bytes received -> timeout */
        if (wRxBufLen == 0)
        {
            status = PH_ERR_IO_TIMEOUT;
        }
        /* Else retrieve valid bits of last byte */
        else
        {
            /* Retrieve valid bits of last byte */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, 
                PHHAL_HW_RC632_REG_SECONDARY_STATUS, 
                &bRegister));

            /* Mask out valid bits of last byte */
            bRegister &= PHHAL_HW_RC632_BIT_RXLASTBITS;

            /* Set RxLastBits */
            pDataParams->wAdditionalInfo = bRegister;

            /* Set incomplete byte status if applicable */
            if (bRegister != 0x00)
            {
                status = PH_ERR_SUCCESS_INCOMPLETE_BYTE;
            }
        }
    }

    /* Stop the command / flush the FIFO on error */
    if ((status != PH_ERR_SUCCESS) &&
        (status != PH_ERR_SUCCESS_INCOMPLETE_BYTE))
    {
        /* stop the command */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, 
            PHHAL_HW_RC632_REG_COMMAND, 
            PHHAL_HW_RC632_CMD_IDLE));

        /* Flush FiFo */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_FlushFifo(pDataParams));
    }

    /* Increment received data length */
    pDataParams->wRxBufLen = pDataParams->wRxBufLen + wRxBufLen;

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
    if ((pDataParams->wTimingMode & 
        (uint16_t)~(uint16_t)PHHAL_HW_TIMING_MODE_OPTION_MASK) == PHHAL_HW_TIMING_MODE_COMM)
    {
        /* Calculate FDT Value */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_CalculateFdt(pDataParams, status, &dwTimingSingle));

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

phStatus_t phhalHw_Rc632_FieldOn(phhalHw_Rc632_DataParams_t * pDataParams)
{
    return phhalHw_Rc632_SetBitMask(pDataParams, PHHAL_HW_RC632_REG_TXCONTROL, 0x03);    /* Tx2RF-En, Tx1RF-En enable */
}

phStatus_t phhalHw_Rc632_FieldOff(phhalHw_Rc632_DataParams_t *pDataParams)
{
    return phhalHw_Rc632_ClearBitMask(pDataParams, PHHAL_HW_RC632_REG_TXCONTROL, 0x03);  /* Tx2RF-En, Tx1RF-En disable */
}

phStatus_t phhalHw_Rc632_FieldReset(phhalHw_Rc632_DataParams_t* pDataParams)
{
    phStatus_t statusTmp = PH_ERR_SUCCESS;
    /* Switch off the field */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ClearBitMask(pDataParams, PHHAL_HW_RC632_REG_TXCONTROL, 0x03));  /* Tx2RF-En, Tx1RF-En disablen */

    /* wait for field-off timeout Delay for 1 ms */

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_Wait(
        pDataParams, 
        PHHAL_HW_TIME_MILLISECONDS, 
        pDataParams->wFieldOffTime));

    /* switch on the field again */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_SetBitMask(pDataParams, PHHAL_HW_RC632_REG_TXCONTROL, 0x03));    /* Tx2RF-En, Tx1RF-En enable */

    /* wait for field-recovery timeout */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_Wait(
        pDataParams,
        PHHAL_HW_TIME_MILLISECONDS,
        pDataParams->wFieldRecoveryTime));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc632_ReadRegister(phhalHw_Rc632_DataParams_t * pDataParams, uint8_t bAddress, uint8_t* pData)
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bTxBuffer[5];
    uint16_t    PH_MEMLOC_REM wTxLength;
    uint16_t    PH_MEMLOC_REM wBytesRead;
    uint8_t		PH_MEMLOC_REM bNumExpBytes;

    /* set RD/NWR bit to indicate read operation */
    bTxBuffer[0] = 0x0;
    bTxBuffer[1] = 0x1;
    bTxBuffer[2] = 0x0;
    bTxBuffer[3] = bAddress;
    wTxLength = 4;
    bNumExpBytes = 4;

    /* Write the address and retrieve the register content */
    PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Exchange(pDataParams->pBalDataParams, 
        PH_EXCHANGE_DEFAULT,
        bTxBuffer, 
        wTxLength, 
        bNumExpBytes, 
        bTxBuffer, 
        &wBytesRead));
    *pData = bTxBuffer[3];
    /* Check number of received bytes */
    if (wBytesRead != bNumExpBytes)
    { 
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_HAL);
    }
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc632_WriteRegister(phhalHw_Rc632_DataParams_t * pDataParams, uint8_t bAddress, uint8_t bValue)
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bDataBuffer[255];
    uint16_t    PH_MEMLOC_REM wBytesRead;
    uint8_t		PH_MEMLOC_REM bNumExpBytes;

    bDataBuffer[0] = 0x1;
    bDataBuffer[1] = 0x2;
    bDataBuffer[2] = 0x0;

    /* shift address and clear RD/NWR bit to indicate write operation */

    /* Write the address and data */

    bDataBuffer[3] = bAddress;	
    bDataBuffer[4] = bValue;

    bNumExpBytes = 3;

    PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Exchange(pDataParams->pBalDataParams, 
        PH_EXCHANGE_DEFAULT,
        bDataBuffer, 
        5, 
        bNumExpBytes, 
        bDataBuffer, 
        &wBytesRead));

    /* Check number of received bytes */
    if (wBytesRead != bNumExpBytes)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_HAL);
    }
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc632_ApplyProtocolSettings(
    phhalHw_Rc632_DataParams_t * pDataParams, 
    uint8_t bCardType
    )
{    
    phStatus_t statusTmp;
    uint16_t wIndex;
    uint16_t* pShadowDefault;
    uint16_t wShadowCount;
    uint8_t bUseDefaultShadow;
    uint16_t wConfig;

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
        /* configure hardware for ISO 14443A */
    case PHHAL_HW_CARDTYPE_ISO14443A:

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TXCONTROL, 0x5B)); /* with 100% ASK */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_MOD_WIDTH_SOF, 0x3F));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TYPEB_FRAMING, 0x3B));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_BIT_PHASE, 0xA9));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_CONTROL2, 0x01));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CHANNEL_REDUND, 0x03));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CLOCKQ_CONTROL,	0x07)); 
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_CONTROL,	0x06)); 
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_MF_OUT_SELECT,	0x00)); 
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_PRESET27,	0x63)); 
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CRC_PRESET_LSB,	0x63)); 
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CRC_PRESET_MSB,	0x63)); 
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIME_SLOT_PERIOD,	0x00)); 

        /* Use 14443a default shadow */
        pShadowDefault = (uint16_t*)wRc632_DefaultShadow_14443a;
        wShadowCount = sizeof(wRc632_DefaultShadow_14443a) / (sizeof(uint16_t) * 2);
        break;

        /* configure hardware for ISO 14443B */
    case PHHAL_HW_CARDTYPE_ISO14443B:

        /* test clock Q calibration - value in the range of 0x46 expected */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, 
            PHHAL_HW_RC632_REG_CLOCKQ_CONTROL, 
            0x0));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, 
            PHHAL_HW_RC632_REG_CLOCKQ_CONTROL, 
            0x40));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ClearBitMask(pDataParams, 
            PHHAL_HW_RC632_REG_CLOCKQ_CONTROL, 
            0x40)); /* clear bit ClkQCalib for  */
        /* further calibration enable auto power down */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, 
            PHHAL_HW_RC632_REG_RX_CONTROL1, 
            0x73));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, 
            PHHAL_HW_RC632_REG_RX_CONTROL2, 
            41));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, 
            PHHAL_HW_RC632_REG_IRQ_PIN_CONFIG, 
            0x3)); /* interrupt active low enable */
        /* Set Water Level of the FIFO */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, 
            PHHAL_HW_RC632_REG_FIFO_LEVEL, 
            0x3F)); /* interrupt active low enable */
        /* Use 14443b shadow */
        pShadowDefault = (uint16_t*)wRc632_DefaultShadow_I14443b;
        wShadowCount = sizeof(wRc632_DefaultShadow_I14443b) / (sizeof(uint16_t) * 2);
        break;

    case PHHAL_HW_CARDTYPE_ISO15693:

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TXCONTROL, 0x48)); /* standard value */
        /* PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TXCONTROL, 0x58)); // with 100% ASK */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CW_COND, 0x3F));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_MOD_COND, 0x02));    /* must	be measured for	15% Modulation Index */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CODER_CONTROL, 0x2C));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_MOD_WIDTH, 0x3F));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_MOD_WIDTH_SOF, 0x3F));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TYPEB_FRAMING, 0x00));

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_CONTROL1, 0x8B));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_DECODER_CONTROL, 0x00));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_BIT_PHASE, 0x52));	
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_THRESHOLD, 0x66));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_BPSK_DEM_CONTROL, 0x00));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_CONTROL2, 0x01));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CLOCKQ_CONTROL, 0x00));

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_WAIT, 0x09));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CHANNEL_REDUND, 0x0C));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CRC_PRESET_LSB, 0xFE));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CRC_PRESET_MSB, 0xFF));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIME_SLOT_PERIOD, 0x00));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_MF_OUT_SELECT, 0x02));      /* enable SIGOUT = envelope */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_PRESET27, 0x00));   				

        /* PAGE 5  FIFO, Timer and IRQ-Pin Configuration */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_FIFO_LEVEL, 0x20));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_CLOCK, 0x0B));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_CONTROL, 0x02)); /* TStopRxEnd=0, TStopRxBeg=1, */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_RELOAD, 0x00));

        /* Flush (empty) FIFO */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_FlushFifo(pDataParams));

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_IRQ_PIN_CONFIG, 0x03)); /* interrupt active low enable */
        /* Use 15693 default shadow */
        pShadowDefault = (uint16_t*)wRc632_DefaultShadow_15693;
        wShadowCount = sizeof(wRc632_DefaultShadow_15693) / (sizeof(uint16_t) * 2);

        /* Set default SOF */
        pDataParams->bSymbolStart = 0x05;

        break;

    case PHHAL_HW_CARDTYPE_ICODEEPCUID:

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TXCONTROL, 0x48)); /* standard value */
        /* PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TXCONTROL, 0x58)); // with 100% ASK */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CW_COND, 0x3F));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_MOD_COND, 0x02));    /* must	be measured for	15% Modulation Index */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CODER_CONTROL, 0x2C));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_MOD_WIDTH, 0x3F));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_MOD_WIDTH_SOF, 0x3F));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TYPEB_FRAMING, 0x00));

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_CONTROL1, 0x8B));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_DECODER_CONTROL, 0x00));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_BIT_PHASE, 0x52));	
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_THRESHOLD, 0x66));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_BPSK_DEM_CONTROL, 0x00));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_CONTROL2, 0x01));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CLOCKQ_CONTROL, 0x00));

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_WAIT, 0x08));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CHANNEL_REDUND, 0x0C));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CRC_PRESET_LSB, 0xFE));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CRC_PRESET_MSB, 0xFF));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIME_SLOT_PERIOD, 0x00));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_MF_OUT_SELECT, 0x02));      
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_PRESET27, 0x00));   				

        /* PAGE 5  FIFO, Timer and IRQ-Pin Configuration */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_FIFO_LEVEL, 0x20));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_CLOCK, 0x0B));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_CONTROL, 0x02)); /* TStopRxEnd=0, TStopRxBeg=1, */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_RELOAD, 0x00));

        /* Flush (empty) FIFO */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_FlushFifo(pDataParams));

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_IRQ_PIN_CONFIG, 0x03)); 
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CODER_CONTROL, 0x25));

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_MOD_WIDTH_SOF, 0x00));

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_CONTROL1, 0x6B));

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_DECODER_CONTROL, 0x04));

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_BIT_PHASE, 0x92));

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_WAIT, 0x04));

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CHANNEL_REDUND, 0x00));

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_CLOCK, 0x0B));

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_THRESHOLD, 0x88));


        /* Use ICode EPC/UID default shadow */
        pShadowDefault = (uint16_t*)wRc632_DefaultShadow_ICodeEpcUid;
        wShadowCount = sizeof(wRc632_DefaultShadow_ICodeEpcUid) / (sizeof(uint16_t) * 2);

        /* Set default SOF */
        pDataParams->bSymbolStart = PHHAL_HW_SYMBOL_ICODEEPCUID_SSOF;

        break;

    default:

        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Apply shadowed registers */
    for (wIndex = 0; wIndex < wShadowCount; ++wIndex)
    {
        /* Get wConfig */
        wConfig = pShadowDefault[wIndex << 1];

        /* Apply only one the correct timeout unit */
        if (!(((wConfig == PHHAL_HW_CONFIG_TIMEOUT_VALUE_US) &&
            (pDataParams->bTimeoutUnit != PHHAL_HW_TIME_MICROSECONDS)) ||
            ((wConfig == PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS) &&
            (pDataParams->bTimeoutUnit != PHHAL_HW_TIME_MILLISECONDS))))
        {
            /* Default shadow: */
            if (bUseDefaultShadow)
            {
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_SetConfig(pDataParams, wConfig, pShadowDefault[(wIndex << 1) + 1]));
            }
            /* Current shadow: */
            else
            {
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_SetConfig(pDataParams, wConfig, pDataParams->wCfgShadow[wConfig]));
            }
        }
    }
    /* MIFARE Crypto1 state is disabled by default */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_SetConfig(pDataParams, PHHAL_HW_CONFIG_DISABLE_MF_CRYPTO1, PH_ON));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}


phStatus_t phhalHw_Rc632_Wait(phhalHw_Rc632_DataParams_t * pDataParams, uint8_t bUnit, uint32_t wTimeout)
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

    /* Backup Rc632 register contents */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_CLOCK, &bRegTimerClock));
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_RELOAD, &bRegTimerReload));
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_CONTROL, &bRegTimerControl));

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
            if (fTimeoutUs > PHHAL_HW_RC632_TIMER_MAX_VALUE_US)
            {
                fTimeoutUs = PHHAL_HW_RC632_TIMER_MAX_VALUE_US;
                wTimeout = wTimeout - (uint16_t)(fTimeoutUs / 1000.0f);
            }
            else
            {
                wTimeout = 0;
            }
        }

        /* Calculate the prescaler value */
        /* [timeout[us]  = (2 ^ n) / 13.56] */
        fTemp = (float32_t)(log((fTimeoutUs * PHHAL_HW_RC632_TIMER_FREQ) / 255.0f) / log(2));

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
        fTemp = (float32_t)(fTimeoutUs * PHHAL_HW_RC632_TIMER_FREQ) / ((float32_t)(1 << wPrescaler));

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
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_COMMAND, 0x00));

        /* Set new timeout value */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_CLOCK, (uint8_t)wPrescaler));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_RELOAD, (uint8_t)wReload));

        /* Start the timer */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_CONTROL, &bTmp));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CONTROL, bTmp | PHHAL_HW_RC632_BIT_TSTARTNOW));

        /* wait for timer */
        do
        {
            /* Read secondary status register */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_SECONDARY_STATUS, &bTmp));
        }
        while (bTmp & PHHAL_HW_RC632_BIT_TRUNNING);
    }
    while (wTimeout > 0);

    /* Restore Rc632 register contents */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_CLOCK, bRegTimerClock));
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_RELOAD, bRegTimerReload));
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_CONTROL, bRegTimerControl));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}


phStatus_t phhalHw_Rc632_SetConfig(phhalHw_Rc632_DataParams_t * pDataParams, uint16_t wConfig, uint16_t wValue)
{    
    phStatus_t  PH_MEMLOC_REM	statusTmp;
    uint8_t		PH_MEMLOC_REM	bBackup;
    uint8_t		PH_MEMLOC_REM	bValue;
    uint16_t	PH_MEMLOC_REM	wOtherDataRate;

    switch (wConfig)
    {
    case PHHAL_HW_CONFIG_PARITY:

        /* Update the flags (enabled is disabled in this case) */
        if (wValue != PH_OFF)
        {
            pDataParams->bFlags |= PHHAL_HW_RC632_BIT_ENABLE_PARITY;
        }
        else
        {
            pDataParams->bFlags &= (uint8_t)~(uint8_t)PHHAL_HW_RC632_BIT_ENABLE_PARITY;
        }

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_CHANNEL_REDUND, &bBackup));

        if (wValue == PH_OFF)
        {
            bValue = bBackup & (uint8_t)~(uint8_t)PHHAL_HW_RC632_BIT_ENABLE_PARITY;
        }
        else
        {
            bValue = bBackup | PHHAL_HW_RC632_BIT_ENABLE_PARITY;
        }

        /* Only perform the operation, if the new value is different */
        if (bValue != bBackup)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CHANNEL_REDUND, bValue));
        }

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;

        break;

    case PHHAL_HW_CONFIG_TXCRC:

        /* Update the flags (enabled is disabled in this case) */
        if (wValue != PH_OFF)
        {
            pDataParams->bFlags |= PHHAL_HW_RC632_BIT_ENABLE_TXCRC;
        }
        else
        {
            pDataParams->bFlags &= (uint8_t)~(uint8_t)PHHAL_HW_RC632_BIT_ENABLE_TXCRC;
        }

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_CHANNEL_REDUND, &bBackup));

        if (wValue == PH_OFF)
        {
            bValue = bBackup & (uint8_t)~(uint8_t)PHHAL_HW_RC632_BIT_ENABLE_TXCRC;
        }
        else
        {
            bValue = bBackup | PHHAL_HW_RC632_BIT_ENABLE_TXCRC;
        }

        /* Only perform the operation, if the new value is different */
        if (bValue != bBackup)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CHANNEL_REDUND, bValue));
        }

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;

        break;

    case PHHAL_HW_CONFIG_RXCRC:

        /* Update the flags (enabled is disabled in this case) */
        if (wValue == PH_OFF)
        {
            pDataParams->bFlags |= PHHAL_HW_RC632_BIT_ENABLE_RXCRC;
        }
        else
        {
            pDataParams->bFlags &= (uint8_t)~(uint8_t)PHHAL_HW_RC632_BIT_ENABLE_RXCRC;
        }

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_CHANNEL_REDUND, &bBackup));

        if (wValue == PH_OFF)
        {
            bValue = bBackup & (uint8_t)~(uint8_t)PHHAL_HW_RC632_BIT_ENABLE_RXCRC;
        }
        else
        {
            bValue = bBackup | PHHAL_HW_RC632_BIT_ENABLE_RXCRC;
        }

        /* Only perform the operation, if the new value is different */
        if (bValue != bBackup)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CHANNEL_REDUND, bValue));
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
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_BIT_FRAMING, &bBackup));
        /* adjust register */
        bBackup &= (uint8_t)~(uint8_t)0x07;
        bBackup |= (uint8_t)(wValue);

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_BIT_FRAMING, bBackup));

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;
        break;

    case PHHAL_HW_CONFIG_RXALIGN:

        /* check parameter */
        if (wValue > 7)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_BIT_FRAMING, &bBackup));

        /* adjust register */
        bBackup &= (uint8_t)~(uint8_t)0x70;
        bBackup |= (uint8_t)(wValue << 4);

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_BIT_FRAMING, bBackup));

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;

        break;

    case PHHAL_HW_CONFIG_RXDEAFBITS:

        /* check parameter */
        if (wValue > 0xFF)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_WAIT, (uint8_t)wValue));

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;

        break;

    case PHHAL_HW_CONFIG_CLEARBITSAFTERCOLL:

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_DECODER_CONTROL, &bBackup));

        if (wValue)
        {
            bValue = bBackup | PHHAL_HW_RC632_BIT_ZEROAFTERCOLL;
        }
        else
        {
            bValue = bBackup & (uint8_t)~(uint8_t)PHHAL_HW_RC632_BIT_ZEROAFTERCOLL;
        }

        /* Only perform the operation, if the new value is different */
        if (bValue != bBackup)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_DECODER_CONTROL, bValue));
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
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CODER_CONTROL, 0x2E));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_DECODER_CONTROL, 0x34));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_WAIT, 0x09));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CHANNEL_REDUND, 0x2C));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CRC_PRESET_LSB, 0xFF));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CRC_PRESET_MSB, 0xFF));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_BIT_PHASE, 0xCD));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_MOD_WIDTH_SOF, 0x3F));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_CONTROL1, 0x8B));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_THRESHOLD, 0x88));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ClearBitMask(pDataParams, PHHAL_HW_RC632_REG_TXCONTROL, 0x10));   /* Set 10% Modulation. */
                break;
            case PHHAL_HW_RF_TX_DATARATE_1_OUT_OF_4:
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CODER_CONTROL, 0x2F));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_DECODER_CONTROL, 0x34));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_WAIT, 0x09));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CHANNEL_REDUND, 0x2C));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CRC_PRESET_LSB, 0xFF));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CRC_PRESET_MSB, 0xFF));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_BIT_PHASE, 0xCD));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_MOD_WIDTH_SOF, 0x3F));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_CONTROL1, 0x8B));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_THRESHOLD, 0x88));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ClearBitMask(pDataParams, PHHAL_HW_RC632_REG_TXCONTROL, 0x10));   /* Set 10% Modulation. */
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
        else if (pDataParams->bCardType == PHHAL_HW_CARDTYPE_ISO14443A || pDataParams->bCardType == PHHAL_HW_CARDTYPE_ISO14443B)
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
                wOtherDataRate = pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXDATARATE];
                /* set reader send baudrate */
                if(wValue != PHHAL_HW_RF_DATARATE_212)
                {
                    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CODER_CONTROL, 0x19));
                }
                else
                {
                    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CODER_CONTROL, 0x11));
                }
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_MOD_WIDTH, 0x13));
                /* set reader receive baudrate */
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_CONTROL1, 0x73));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_DECODER_CONTROL, 0x08));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_THRESHOLD, 0xEB));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_BPSK_DEM_CONTROL, 0x00));
                break;
            default:
                return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
            }
        }
        else if(pDataParams->bCardType == PHHAL_HW_CARDTYPE_ICODEEPCUID)
        {
            if (wValue == PHHAL_HW_RF_DATARATE_EPCUID)
            {
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CODER_CONTROL, 0xAC));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_MOD_WIDTH, 0x13));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_MOD_WIDTH_SOF, 0x3F));
                /* set reader receive baudrate */
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_CONTROL1, 0x8B));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_DECODER_CONTROL, 0x60));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_THRESHOLD, 0xEB));
            }
            else
            {
                return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
            }
        }
        else
        {
            return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_HAL);
        }

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;
        break;

    case PHHAL_HW_CONFIG_RXDATARATE:

        if (pDataParams->bCardType == PHHAL_HW_CARDTYPE_ISO15693)
        {
            switch (wValue)
            {
                /* Fast data-rate */
            case PHHAL_HW_RF_RX_DATARATE_FAST_HIGH:
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_RX_CONTROL1, &bValue));
                bValue &= (uint8_t)~(uint8_t)PHHAL_HW_RC632_MASK_SUBCPULSES;
                bValue |= PHHAL_HW_RC632_BITS_SUBCPULSES_8;
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_CONTROL1, bValue));
                break;
                /* High data-rate */
            case PHHAL_HW_RF_RX_DATARATE_HIGH:
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_RX_CONTROL1, &bValue));
                bValue &= (uint8_t)~(uint8_t)PHHAL_HW_RC632_MASK_SUBCPULSES;
                bValue |= PHHAL_HW_RC632_BITS_SUBCPULSES_16;
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_CONTROL1, bValue));
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
        else if (pDataParams->bCardType == PHHAL_HW_CARDTYPE_ISO14443A || pDataParams->bCardType == PHHAL_HW_CARDTYPE_ISO14443B)
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
                /* set reader send baudrate */
                if(wValue != PHHAL_HW_RF_DATARATE_212)
                {
                    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CODER_CONTROL, 0x19));
                }
                else
                {
                    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CODER_CONTROL, 0x11));
                }

                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_MOD_WIDTH, 0x13));
                /* set reader receive baudrate */
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_CONTROL1, 0x73));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_DECODER_CONTROL, 0x08));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_THRESHOLD, 0xEB));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_BPSK_DEM_CONTROL, 0x00));

                break;
            default:
                return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
            }
        }
        else if(pDataParams->bCardType == PHHAL_HW_CARDTYPE_ICODEEPCUID)
        {
            if (wValue == PHHAL_HW_RF_DATARATE_EPCUID)
            {
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CODER_CONTROL, 0xAC));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_MOD_WIDTH, 0x13));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_MOD_WIDTH_SOF, 0x3F));
                /* set reader receive baudrate */
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_CONTROL1, 0x8B));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_DECODER_CONTROL, 0x60));
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_THRESHOLD, 0xEB));
            }
            else
            {
                return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
            }
        }
        else
        {
            return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_HAL);
        }

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;
        break;

    case PHHAL_HW_CONFIG_MODINDEX:

        /* Set ModConductance register */
        if(wValue > 0x3F)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(
            pDataParams, 
            PHHAL_HW_RC632_REG_MOD_COND, 
            (uint8_t)(wValue & 0x3F)));

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;
        break;

    case PHHAL_HW_CONFIG_ASK100:

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_TXCONTROL, &bValue));

        /* switch on 100% ASK */
        if (wValue != PH_OFF)
        {
            bValue |= PHHAL_HW_RC632_BIT_FORCE_100ASK;
        }
        /* switch off 100% ASK */
        else
        {
            bValue &= (uint8_t)~(uint8_t)PHHAL_HW_RC632_BIT_FORCE_100ASK;
        }

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TXCONTROL, bValue));

        /* Write config data into shadow */
        pDataParams->wCfgShadow[wConfig] = wValue;
        break;

    case PHHAL_HW_CONFIG_TIMEOUT_VALUE_US:
    case PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS:

        /* Calculate values for Microsecond values */
        if (wConfig == PHHAL_HW_CONFIG_TIMEOUT_VALUE_US)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_SetTmo(pDataParams, wValue,PHHAL_HW_TIME_MICROSECONDS));
            pDataParams->bTimeoutUnit = PHHAL_HW_TIME_MICROSECONDS;
            /*pDataParams->dwTimeoutUs = (uint32_t)wValue;*/
        }
        /* Calculate values for Millisecond values */
        else
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_SetTmo(pDataParams, wValue,PHHAL_HW_TIME_MILLISECONDS));
            pDataParams->bTimeoutUnit = PHHAL_HW_TIME_MILLISECONDS;
            /*pDataParams->dwTimeoutUs = (uint32_t)wValue * 1000;*/
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
            pDataParams->dwTimingUs = 0;
        case PHHAL_HW_TIMING_MODE_COMM:
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
        /* Parameter check */
        if ((((pDataParams->bCardType != PHHAL_HW_CARDTYPE_ISO15693))))
        {
            return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_HAL);
        }

        /* Update Subcarrier setting */
        if(wValue > 1)
        {
            return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_HAL);
        }
        else
        {
            pDataParams->wCfgShadow[PHHAL_HW_CONFIG_SUBCARRIER] = wValue;
        }
        break;

    case PHHAL_HW_CONFIG_RXBUFFER_STARTPOS:

        /* Boundary check */
        if ((PHHAL_HW_RC632_RESERVED_BUFFER_LEN + wValue) >= pDataParams->wRxBufSize)
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
        if ((pDataParams->wTxBufStartPos + PHHAL_HW_RC632_RESERVED_BUFFER_LEN + wValue) >= pDataParams->wTxBufSize)
        {
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* set buffer length */
        pDataParams->wTxBufLen = wValue;
        break;

    case PHHAL_HW_CONFIG_TXBUFFER:

        /* Check additional info parameter */
        if ((pDataParams->wTxBufStartPos + PHHAL_HW_RC632_RESERVED_BUFFER_LEN + pDataParams->wAdditionalInfo) >= pDataParams->wTxBufSize || wValue == 0)
        {
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* Modify TxBuffer byte */
        pDataParams->pTxBuffer[pDataParams->wTxBufStartPos + pDataParams->wAdditionalInfo] = (uint8_t)wValue;
        break;

    case PHHAL_HW_CONFIG_DISABLE_MF_CRYPTO1:

        /* Disable crypto, enabling is not supported */
        if (wValue != PH_OFF)
        {
            /* Retrieve Control register */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_CONTROL, &bBackup));

            /* Clear Crypto1On bit */
            bBackup &= (uint8_t)~(uint8_t)PHHAL_HW_RC632_BIT_CRYPTO1ON;

            /* Write Control register */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CONTROL, bBackup));
            /* Retrieve Control register */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_CONTROL, &bBackup));

        }

        break;

    case PHHAL_HW_CONFIG_ADDITIONAL_INFO:

        /* Modify additional info parameter */
        pDataParams->wAdditionalInfo = wValue;
        break;

    case PHHAL_HW_CONFIG_MAX_PRECACHED_BYTES:

        /* Check parameter */
        if (wValue > 63)
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

    case PHHAL_HW_RC632_CONFIG_DISABLE_PCDRESET:

        pDataParams->bDisablePcdReset = (uint8_t)wValue;
        break;

    default:
        return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_HAL);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}


phStatus_t phhalHw_Rc632_GetConfig(phhalHw_Rc632_DataParams_t * pDataParams, uint16_t wConfig, uint16_t* pValue)
{
    phStatus_t	PH_MEMLOC_REM	statusTmp;
    uint8_t     PH_MEMLOC_REM	bRegister;

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
        *pValue = pDataParams->wRxBufSize - PHHAL_HW_RC632_RESERVED_BUFFER_LEN;
        break;

    case PHHAL_HW_CONFIG_TXBUFFER_BUFSIZE:

        /* Return parameter */
        *pValue = pDataParams->wTxBufSize - PHHAL_HW_RC632_RESERVED_BUFFER_LEN - pDataParams->wTxBufStartPos;
        break;

    case PHHAL_HW_CONFIG_TXBUFFER_LENGTH:

        /* Return parameter */
        *pValue = pDataParams->wTxBufLen;
        break;

    case PHHAL_HW_CONFIG_TXBUFFER:

        /* Check additional info parameter */
        if ((pDataParams->wTxBufStartPos + PHHAL_HW_RC632_RESERVED_BUFFER_LEN + pDataParams->wAdditionalInfo) >= pDataParams->wTxBufSize)
        {
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* Retrieve TxBuffer byte */
        *pValue = (uint16_t)pDataParams->pTxBuffer[pDataParams->wTxBufStartPos + pDataParams->wAdditionalInfo];
        break;

    case PHHAL_HW_CONFIG_MAX_PRECACHED_BYTES:

        /* Return parameter */
        *pValue = pDataParams->wMaxPrecachedBytes;
        break;

    case PHHAL_HW_CONFIG_BAL_CONNECTION:

        /* Return parameter */
        *pValue = (uint16_t)pDataParams->bBalConnectionType;
        break;

    case PHHAL_HW_CONFIG_DISABLE_MF_CRYPTO1:

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_CONTROL, &bRegister));

        /* Clear Crypto1On bit */
        if (bRegister & PHHAL_HW_RC632_BIT_CRYPTO1ON)
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

    case PHHAL_HW_RC632_CONFIG_DISABLE_PCDRESET:

        *pValue = (uint16_t)pDataParams->bDisablePcdReset;
        break;

    default:
        return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_HAL);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}


phStatus_t phhalHw_Rc632_MfcAuthenticateKeyNo(
    phhalHw_Rc632_DataParams_t * pDataParams, 
    uint8_t bBlockNo, 
    uint8_t bKeyType, 
    uint16_t wKeyNo, 
    uint16_t wKeyVersion, 
    uint8_t * pUid
    )
{    
    phStatus_t  PH_MEMLOC_REM	statusTmp;
    uint8_t     PH_MEMLOC_REM	bAuthMode;

    /* Evaluate which key to use */
    if ((bKeyType & 0x7F) == PHHAL_HW_MFC_KEYA)
    {
        bAuthMode = PHHAL_HW_RC632_AUTHMODE_KEYA;
    }
    else if ((bKeyType & 0x7F) == PHHAL_HW_MFC_KEYB)
    {
        bAuthMode = PHHAL_HW_RC632_AUTHMODE_KEYB;
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
    if (wKeyNo > PHHAL_HW_RC632_MAX_NUM_KEYS)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /*Load the Key from EEPROM into the Key buffer */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_Cmd_LoadKeyE2(pDataParams, (uint8_t)wKeyNo, bAuthMode));

    /* Authenticate */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_MfcAuthenticate_Int(pDataParams, bAuthMode, pUid, bBlockNo));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc632_MfcAuthenticate(
    phhalHw_Rc632_DataParams_t * pDataParams, 
    uint8_t bBlockNo, 
    uint8_t bKeyType, 
    uint8_t * pKey, 
    uint8_t * pUid
    )
{
    phStatus_t  PH_MEMLOC_REM	statusTmp;
    uint8_t     PH_MEMLOC_REM	bAuthMode;

    /* Evaluate which key to use */
    if ((bKeyType & 0x7F) == PHHAL_HW_MFC_KEYA)
    {
        bAuthMode = PHHAL_HW_RC632_AUTHMODE_KEYA;
    }
    else if ((bKeyType & 0x7F) == PHHAL_HW_MFC_KEYB)
    {
        bAuthMode = PHHAL_HW_RC632_AUTHMODE_KEYB;
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }
    /* Clear All Irqs */


    /* Load Key */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_Cmd_LoadKey(pDataParams, pKey));

    /* Authenticate */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_MfcAuthenticate_Int(pDataParams, bAuthMode, pUid, bBlockNo));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

#endif /* NXPBUILD__PHHAL_HW_RC632 */
