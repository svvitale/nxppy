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
* Command functions for Rc523 specific HAL-Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:27:50 2011 $
*
* History:
*  CHu: Generated 19. April 2010
*
*/
#include <phhalHw.h>
#include <phbalReg.h>
#include <ph_RefDefs.h>
#include <ph_Status.h>

#ifdef NXPBUILD__PHHAL_HW_RC523

#include "phhalHw_Rc523.h"
#include "phhalHw_Rc523_Int.h"
#include <phhalHw_Rc523_Cmd.h>
#include "phhalHw_Rc523_Config.h"

phStatus_t phhalHw_Rc523_Cmd_Mem(
                                 phhalHw_Rc523_DataParams_t * pDataParams,
                                 uint8_t * pDataIn,
                                 uint8_t bDataLength,
                                 uint8_t * pDataOut
                                 )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bIrq0WaitFor;
    uint8_t     PH_MEMLOC_REM bIrq1WaitFor;
    uint8_t		PH_MEMLOC_REM bIrq0Rq;
    uint8_t		PH_MEMLOC_REM bIrq1Rq;
    uint8_t     PH_MEMLOC_REM bError;
    uint16_t	PH_MEMLOC_REM wFifoBytes;
    uint8_t *   PH_MEMLOC_REM pTmpBuffer;
    uint16_t    PH_MEMLOC_REM wTmpBufferLen;
    uint16_t    PH_MEMLOC_REM wTmpBufferSize;

    /* Check input length */
    if ((bDataLength != 0) && (bDataLength != 25))
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Read Path */
    if (bDataLength == 0)
    {
        /* Flush FiFo */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_FlushFifo(pDataParams));

        /* start the command */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_COMMAND, PHHAL_HW_RC523_CMD_MEM));

        /* wait until the command is finished */
        bIrq0WaitFor = PHHAL_HW_RC523_BIT_IDLEI | PHHAL_HW_RC523_BIT_ERRI;
        bIrq1WaitFor = 0x00;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_WaitIrq(pDataParams, bIrq0WaitFor, bIrq1WaitFor, &bIrq0Rq, &bIrq1Rq));

        /* Retrieve receive buffer properties */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_GetRxBuffer(pDataParams, PH_OFF, &pTmpBuffer, &wTmpBufferLen, &wTmpBufferSize));

        /* retrieve bytes from FiFo */
        status = phhalHw_Rc523_ReadFifo(pDataParams, wTmpBufferSize, pTmpBuffer, &wFifoBytes);

        /* bail out on error */
        if ((status & PH_ERR_MASK) != PH_ERR_SUCCESS)
        {
            /* Flush FiFo */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_FlushFifo(pDataParams));

            return PH_ADD_COMPCODE(status, PH_COMP_HAL);
        }

        if (!(bIrq0Rq & PHHAL_HW_RC523_BIT_ERRI))
        {
            /* Check received length */
            if (wFifoBytes != 25)
            {
                return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
            }

            /* Return data */
            memcpy(pDataOut, pTmpBuffer, wFifoBytes); /* PRQA S 3200 */
        }
    }
    else /* Write Path */
    {
        /* Flush FiFo */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_FlushFifo(pDataParams));

        /* Retrieve transmit buffer properties */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_GetTxBuffer(pDataParams, PH_OFF, &pTmpBuffer, &wTmpBufferLen, &wTmpBufferSize));

        /* Check for buffer overflow */
        if (wTmpBufferSize < 25)
        {
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* Copy data */
        memcpy(pTmpBuffer, pDataIn, 25);  /* PRQA S 3200 */

        /* Write FIFO */
        status = phhalHw_Rc523_WriteFifo(pDataParams, pTmpBuffer, 25, &wFifoBytes);

        /* bail out on error */
        if ((status & PH_ERR_MASK) != PH_ERR_SUCCESS)
        {
            /* Flush FiFo */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_FlushFifo(pDataParams));

            return PH_ADD_COMPCODE(status, PH_COMP_HAL);
        }

        /* start the command */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_COMMAND, PHHAL_HW_RC523_CMD_MEM));

        /* wait until the command is finished */
        bIrq0WaitFor = PHHAL_HW_RC523_BIT_IDLEI | PHHAL_HW_RC523_BIT_ERRI;
        bIrq1WaitFor = 0x00;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_WaitIrq(pDataParams, bIrq0WaitFor, bIrq1WaitFor, &bIrq0Rq, &bIrq1Rq));
    }

    /* Check for errors */
    if (bIrq0Rq & PHHAL_HW_RC523_BIT_ERRI)
    {
        /* read the error register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC523_REG_ERROR, &bError));

        /* Fifo write error */
        if (bError & PHHAL_HW_RC523_BIT_WRERR)
        {
            status = PH_ERR_READ_WRITE_ERROR;
        }
        /* buffer overflow */
        if (bError & PHHAL_HW_RC523_BIT_BUFFEROVFL)
        {
            status = PH_ERR_BUFFER_OVERFLOW;
        }
        /* CRC / parity error */
        if ((bError & PHHAL_HW_RC523_BIT_CRCERR) || (bError & PHHAL_HW_RC523_BIT_PARITYERR))
        {
            status = PH_ERR_INTEGRITY_ERROR;
        }
    }

    return PH_ADD_COMPCODE(status, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc523_Cmd_Config(
                                    phhalHw_Rc523_DataParams_t * pDataParams,
                                    uint8_t * pSensRes,
                                    uint8_t * pNfcId1,
                                    uint8_t SelRes,
                                    uint8_t * pPollingResp,
                                    uint8_t bNfcId3
                                    )
{
    uint8_t PH_MEMLOC_BUF aCmd[25];

    memcpy(&aCmd[0], pSensRes, 2);      /* PRQA S 3200 */
    memcpy(&aCmd[2], pNfcId1, 3);       /* PRQA S 3200 */
    memcpy(&aCmd[5], &SelRes, 1);       /* PRQA S 3200 */
    memcpy(&aCmd[6], pPollingResp, 18); /* PRQA S 3200 */
    memcpy(&aCmd[24], &bNfcId3, 1);     /* PRQA S 3200 */

    return phhalHw_Rc523_Cmd_Mem(pDataParams, aCmd, 25, NULL);
}

phStatus_t phhalHw_Rc523_Cmd_GenerateRandomId(
    phhalHw_Rc523_DataParams_t * pDataParams
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bIrq0WaitFor = 0x0;
    uint8_t     PH_MEMLOC_REM bIrq1WaitFor = 0x0;
    uint8_t		PH_MEMLOC_REM bIrq0Rq;
    uint8_t		PH_MEMLOC_REM bIrq1Rq;

    /* start the command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_COMMAND, PHHAL_HW_RC523_CMD_RANDOMIDS));

    /* wait until the command is finished */
    bIrq0WaitFor = PHHAL_HW_RC523_BIT_IDLEI;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_WaitIrq(pDataParams, bIrq0WaitFor,bIrq1WaitFor,&bIrq0Rq,&bIrq1Rq));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc523_Cmd_CalcCrc(
                                     phhalHw_Rc523_DataParams_t * pDataParams,
                                     uint8_t * pData,
                                     uint16_t wDataLength,
                                     uint16_t * pCrcResult
                                     )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t    PH_MEMLOC_REM wFifoBytes;
    uint8_t     PH_MEMLOC_REM bIrq0WaitFor;
    uint8_t     PH_MEMLOC_REM bIrq1WaitFor;
    uint8_t     PH_MEMLOC_REM bIrq0Rq = 0x00;
    uint8_t     PH_MEMLOC_REM bIrq1Rq = 0x00;
    uint8_t		PH_MEMLOC_REM bRegister;
    uint8_t     PH_MEMLOC_REM bError;
    uint8_t		PH_MEMLOC_REM bCRCRes;
    uint8_t *   PH_MEMLOC_REM pTmpBuffer;
    uint16_t    PH_MEMLOC_REM wTmpBufferLen;
    uint16_t    PH_MEMLOC_REM wTmpBufferSize;

    /* Check length */
    if ((wDataLength == 0) || (wDataLength > 64))
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Flush FiFo */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_FlushFifo(pDataParams));

    /* Retrieve transmit buffer properties */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_GetTxBuffer(pDataParams, PH_OFF, &pTmpBuffer, &wTmpBufferLen, &wTmpBufferSize));

    /* Check for buffer overflow */
    if (wTmpBufferSize < wDataLength)
    {
        return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
    }

    /* Copy data */
    memcpy(pTmpBuffer, pData, wDataLength);  /* PRQA S 3200 */

    /* Write FIFO */
    status = phhalHw_Rc523_WriteFifo(pDataParams, pTmpBuffer, wDataLength, &wFifoBytes);

    /* bail out on error */
    if ((status & PH_ERR_MASK) != PH_ERR_SUCCESS)
    {
        /* Flush FiFo */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_FlushFifo(pDataParams));

        return PH_ADD_COMPCODE(status, PH_COMP_HAL);
    }

    /* start the command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_COMMAND, PHHAL_HW_RC523_CMD_CALCCRC));

    /* wait until the command is finished */
    bIrq0WaitFor = PHHAL_HW_RC523_BIT_IDLEI | PHHAL_HW_RC523_BIT_ERRI;
    bIrq1WaitFor = PHHAL_HW_RC523_BIT_CRCI;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_WaitIrq(pDataParams, bIrq0WaitFor, bIrq1WaitFor, &bIrq0Rq, &bIrq1Rq));

    /* Check for errors */
    if (bIrq0Rq & PHHAL_HW_RC523_BIT_ERRI)
    {
        /* read the error register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC523_REG_ERROR, &bError));

        /* Fifo write error */
        if (bError & PHHAL_HW_RC523_BIT_WRERR)
        {
            status = PH_ERR_READ_WRITE_ERROR;
        }
        /* buffer overflow */
        if (bError & PHHAL_HW_RC523_BIT_BUFFEROVFL)
        {
            status = PH_ERR_BUFFER_OVERFLOW;
        }
        /* CRC / parity error */
        if ((bError & PHHAL_HW_RC523_BIT_CRCERR) || (bError & PHHAL_HW_RC523_BIT_PARITYERR))
        {
            status = PH_ERR_INTEGRITY_ERROR;
        }
    }
    else
    {
        /* Read status1 register to check if the CRC READY bit is set */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC523_REG_STATUS1, &bRegister));

        /* Read the CRC registers and return the value */
        if (bRegister & PHHAL_HW_RC523_BIT_CRCREADY)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC523_REG_CRCRESULT1, &bCRCRes));
            *pCrcResult = (uint16_t)bCRCRes << 8;
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC523_REG_CRCRESULT2, &bCRCRes));
            *pCrcResult |= bCRCRes;

            status = PH_ERR_SUCCESS;
        }
        else
        {
            status = PH_ERR_INTERNAL_ERROR;
        }
    }

    return PH_ADD_COMPCODE(status, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc523_Cmd_Transmit(
                                      phhalHw_Rc523_DataParams_t * pDataParams,
                                      uint16_t wOption,
                                      uint8_t * pTxBuffer,
                                      uint16_t wTxLength
                                      )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bRegister;
    uint8_t     PH_MEMLOC_REM bRestoreTmrSet;
    uint8_t *   PH_MEMLOC_REM pTmpBuffer;
    uint16_t    PH_MEMLOC_REM wTmpBufferLen;
    uint16_t    PH_MEMLOC_REM wTmpBufferSize;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phhalHw_Rc523_Cmd_Transmit");
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wOption);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pTxBuffer);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wOption_log, &wOption);
    PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, pTxBuffer_log, pTxBuffer, wTxLength);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);

    /* Check options */
    if (wOption & (uint16_t)~(uint16_t)(PH_EXCHANGE_BUFFERED_BIT | PH_EXCHANGE_LEAVE_BUFFER_BIT | PHHAL_HW_RC523_OPTION_RXTX_TIMER_START))
    {
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);

        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
        return status;
    }

    /* Terminate a possibly running command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_COMMAND, PHHAL_HW_RC523_CMD_IDLE));

    /* Flush FiFo */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_FlushFifo(pDataParams));

    /* clear all IRQ0 flags */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_WriteRegister(
        pDataParams,
        PHHAL_HW_RC523_REG_COMMIRQ,
        (uint8_t)~(uint8_t)PHHAL_HW_RC523_BIT_SET));

    /* clear all IRQ1 flags */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_WriteRegister(
        pDataParams,
        PHHAL_HW_RC523_REG_DIVIRQ,
        (uint8_t)~(uint8_t)PHHAL_HW_RC523_BIT_SET));

    /* Custom option: do not start timer */
    if (!(wOption & PHHAL_HW_RC523_OPTION_RXTX_TIMER_START))
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC523_REG_TMODE, &bRegister));
        bRegister &= (uint8_t)~(uint8_t)PHHAL_HW_RC523_BIT_TAUTO;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_TMODE, bRegister));
        bRestoreTmrSet = PH_ON;
    }
    else
    {
        /* To skip restoration sequence below */
        bRestoreTmrSet = PH_OFF;

        /* Clear custom option bit */
        wOption &= (uint16_t)~(uint16_t)PHHAL_HW_RC523_OPTION_RXTX_TIMER_START;
    }

    /* clear internal buffer if requested */
    if (!(wOption & PH_EXCHANGE_LEAVE_BUFFER_BIT))
    {
        pDataParams->wTxBufLen = 0;
    }

    /* Fill the global TxBuffer */
    /* Note: We always need to buffer for SPI, else the input buffer would get overwritten! */
    if ((wOption & PH_EXCHANGE_BUFFERED_BIT) ||
        (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_SPI) ||
        (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_I2C))
    {
        /* retrieve transmit buffer */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_GetTxBuffer(pDataParams, PH_ON, &pTmpBuffer, &wTmpBufferLen, &wTmpBufferSize));

        if (wTxLength != 0)
        {
            /* TxBuffer overflow check */
            if (wTxLength > (wTmpBufferSize - wTmpBufferLen))
            {
                pDataParams->wTxBufLen = 0;
                status = PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);

                PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
                PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
                PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
                return status;
            }

            /* copy data */
            memcpy(&pTmpBuffer[wTmpBufferLen], pTxBuffer, wTxLength);  /* PRQA S 3200 */
            pDataParams->wTxBufLen = pDataParams->wTxBufLen + wTxLength;
        }

        /* Buffer operation -> finished */
        if (wOption & PH_EXCHANGE_BUFFERED_BIT)
        {
            status = PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);

            PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
            PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
            PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
            return status;
        }
        /* Else reset the input length for SPI and continue */
        else
        {
            wTxLength = 0;
        }
    }

    /* perform transmission */
    status = phhalHw_Rc523_ExchangeTransmit(pDataParams, PHHAL_HW_RC523_CMD_TRANSMIT, pTxBuffer, wTxLength);

    /* Restore correct timer setting */
    if (bRestoreTmrSet)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC523_REG_TMODE, &bRegister));
        bRegister |= PHHAL_HW_RC523_BIT_TAUTO;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_TMODE, bRegister));
    }

    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
    return status;
}

phStatus_t phhalHw_Rc523_Cmd_Receive(
                                     phhalHw_Rc523_DataParams_t * pDataParams,
                                     uint16_t wOption,
                                     uint8_t ** ppRxBuffer,
                                     uint16_t * pRxLength
                                     )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bRegister;
    uint8_t     PH_MEMLOC_REM bRegRxWait;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phhalHw_Rc523_Cmd_Receive");
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wOption);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(ppRxBuffer);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wOption_log, &wOption);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);

    /* Check options */
    if (wOption & (uint16_t)~(uint16_t)(PHHAL_HW_RC523_OPTION_RXTX_TIMER_START))
    {
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);

        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
        return status;
    }

    /* Reduce RxWait to minimum */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC523_REG_RXSEL, &bRegRxWait));
    bRegister = bRegRxWait & (uint8_t)~(uint8_t)PHHAL_HW_RC523_MASK_RXWAIT;
    bRegister |= 0x03;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_RXSEL, bRegister));

    /* set the receive length */
    if (pRxLength != NULL)
    {
        *pRxLength = 0;
    }

    /* Terminate a possibly running command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_COMMAND, PHHAL_HW_RC523_CMD_IDLE));

    /* Flush FiFo */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_FlushFifo(pDataParams));

    /* clear all IRQ0 flags */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_WriteRegister(
        pDataParams,
        PHHAL_HW_RC523_REG_COMMIRQ,
        (uint8_t)~(uint8_t)PHHAL_HW_RC523_BIT_SET));

    /* clear all IRQ1 flags */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_WriteRegister(
        pDataParams,
        PHHAL_HW_RC523_REG_DIVIRQ,
        (uint8_t)~(uint8_t)PHHAL_HW_RC523_BIT_SET));

    /* timer should be running, otherwise we'd wait forever */
    if (!(wOption & PHHAL_HW_RC523_OPTION_RXTX_TIMER_START))
    {
        /* retrieve content of Timer Control register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC523_REG_STATUS1, &bRegister));

        /* Check TRunning flag */
        if (!(bRegister & PHHAL_HW_RC523_BIT_TRUNNUNG))
        {
            status = PH_ADD_COMPCODE(PH_ERR_IO_TIMEOUT, PH_COMP_HAL);

            PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
            PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
            PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
            return status;
        }
    }

    /* start the command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_COMMAND, PHHAL_HW_RC523_CMD_RECEIVE));

    /* start timer manually if requested */
    if (wOption & PHHAL_HW_RC523_OPTION_RXTX_TIMER_START)
    {
        /* retrieve content of Timer Control register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC523_REG_CONTROL, &bRegister));
        /* manually start Timer */
        bRegister |= PHHAL_HW_RC523_BIT_TSTARTNOW;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_CONTROL, bRegister));
    }

    /* perform receive operation */
    status = phhalHw_Rc523_ExchangeReceive(pDataParams, ppRxBuffer, pRxLength);

    /* restore RxWait setting */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_RXSEL, bRegRxWait));

    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
#ifdef NXPBUILD__PH_LOG
    if ((((status & PH_ERR_MASK) == PH_ERR_SUCCESS) ||
        ((status & PH_ERR_MASK) == PH_ERR_SUCCESS_INCOMPLETE_BYTE)) &&
        !(wOption & PH_EXCHANGE_BUFFERED_BIT) &&
        (ppRxBuffer != NULL) &&
        (pRxLength != NULL))
    {
        PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, ppRxBuffer_log, *ppRxBuffer, *pRxLength);
    }
#endif
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
    return status;
}

phStatus_t phhalHw_Rc523_Cmd_Autocoll(
                                      phhalHw_Rc523_DataParams_t * pDataParams,
                                      uint8_t ** ppRxBuffer,
                                      uint16_t * pRxLength
                                      )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t    PH_MEMLOC_REM wFifoBytes;
    uint8_t     PH_MEMLOC_REM bIrq0WaitFor;
    uint8_t     PH_MEMLOC_REM bIrq1WaitFor;
    uint8_t     PH_MEMLOC_REM bIrq0Rq;
    uint8_t     PH_MEMLOC_REM bIrq1Rq;
    uint8_t     PH_MEMLOC_REM bRegister;
    uint8_t     PH_MEMLOC_REM bError;
    uint8_t *   PH_MEMLOC_REM pTmpBuffer;
    uint16_t    PH_MEMLOC_REM wTmpBufferLen;
    uint16_t    PH_MEMLOC_REM wTmpBufferSize;

    /* set the receive length */
    if (pRxLength != NULL)
    {
        *pRxLength = 0;
    }

    /* Terminate a probably running command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_COMMAND, PHHAL_HW_RC523_CMD_IDLE));

    /* Flush FiFo */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_FlushFifo(pDataParams));

    /* clear all IRQ0 flags */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_WriteRegister(
        pDataParams,
        PHHAL_HW_RC523_REG_COMMIRQ,
        (uint8_t)~(uint8_t)PHHAL_HW_RC523_BIT_SET));

    /* clear all IRQ1 flags */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_WriteRegister(
        pDataParams,
        PHHAL_HW_RC523_REG_DIVIRQ,
        (uint8_t)~(uint8_t)PHHAL_HW_RC523_BIT_SET));

    /* start the command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_COMMAND, PHHAL_HW_RC523_CMD_AUTOCOLL));

    /* Set wait IRQs */
    bIrq0WaitFor = PHHAL_HW_RC523_BIT_ERRI | PHHAL_HW_RC523_BIT_IDLEI;
    bIrq1WaitFor = 0x00;

    /* wait until the command is finished */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_WaitIrq(
        pDataParams,
        bIrq0WaitFor,
        bIrq1WaitFor,
        &bIrq0Rq,
        &bIrq1Rq));

    /* Timeout handling */
    if (bIrq0Rq & PHHAL_HW_RC523_BIT_TIMERI)
    {
        status = PH_ERR_IO_TIMEOUT;
    }
    else
    {
        status = PH_ERR_SUCCESS;
    }

    /* Reset receive buffer length */
    pDataParams->wRxBufLen = 0;

    /* Retrieve receive buffer properties */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_GetRxBuffer(pDataParams, PH_ON, &pTmpBuffer, &wTmpBufferLen, &wTmpBufferSize));

    /* Do the following if no timeout occured */
    if (status == PH_ERR_SUCCESS)
    {
        /* mask out high-alert */
        bIrq0WaitFor &= (uint8_t)~(uint8_t)PHHAL_HW_RC523_BIT_HIALERTI;

        /* retrieve fifo bytes */
        do
        {
            /* retrieve bytes from FiFo */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_ReadFifo(
                pDataParams,
                wTmpBufferSize,
                &pTmpBuffer[wTmpBufferLen],
                &wFifoBytes));

            /* advance receive buffer */
            wTmpBufferLen = wTmpBufferLen + wFifoBytes;
            wTmpBufferSize = wTmpBufferSize - wFifoBytes;

            /* read interrupt status */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC523_REG_COMMIRQ, &bIrq0Rq));
        }
        while ((!(bIrq0Rq & bIrq0WaitFor)) || (wFifoBytes != 0));

        /* Check for errors */
        if (bIrq0Rq & PHHAL_HW_RC523_BIT_ERRI)
        {
            /* read the error register */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC523_REG_ERROR, &bError));

            /* Fifo write error */
            if (bError & PHHAL_HW_RC523_BIT_WRERR)
            {
                status = PH_ERR_READ_WRITE_ERROR;
            }
            /* temperature error */
            else if (bError & PHHAL_HW_RC523_BIT_TEMPERR)
            {
                status = PH_ERR_TEMPERATURE_ERROR;
            }
            /* RF error (should not happen) */
            /*
            if (bError & PHHAL_HW_RC523_BIT_RFERR)
            {
            status = PH_ERR_RF_ERROR;
            }
            */
            /* buffer overflow */
            else if (bError & PHHAL_HW_RC523_BIT_BUFFEROVFL)
            {
                status = PH_ERR_BUFFER_OVERFLOW;
            }
            /* protocol error */
            else if (bError & PHHAL_HW_RC523_BIT_PROTERR)
            {
                status = PH_ERR_PROTOCOL_ERROR;
            }
            /* CRC / parity error */
            else if ((bError & PHHAL_HW_RC523_BIT_CRCERR) || (bError & PHHAL_HW_RC523_BIT_PARITYERR))
            {
                status = PH_ERR_INTEGRITY_ERROR;
            }
            /* No error */
            else
            {
                status = PH_ERR_SUCCESS;
            }
        }
    }

    /* Receive was successfull */
    if (status == PH_ERR_SUCCESS)
    {
        /* No bytes received -> timeout */
        if (wTmpBufferLen == 0)
        {
            status = PH_ERR_IO_TIMEOUT;
        }
        /* Else retrieve valid bits of last byte */
        else
        {
            /* Retrieve RxBits */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC523_REG_CONTROL, &bRegister));

            /* Mask out valid bits of last byte */
            bRegister &= PHHAL_HW_RC523_MASK_RXBITS;

            /* Set RxLastBits */
            pDataParams->wAdditionalInfo = bRegister;

            /* Set incomplete byte status if applicable */
            if (bRegister != 0x00)
            {
                status = PH_ERR_SUCCESS_INCOMPLETE_BYTE;
            }
        }
    }

    /* stop the command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_COMMAND, PHHAL_HW_RC523_CMD_IDLE));

    /* Flush the FIFO on error */
    if ((status != PH_ERR_SUCCESS) &&
        (status != PH_ERR_SUCCESS_INCOMPLETE_BYTE))
    {
        /* Flush FiFo */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc523_FlushFifo(pDataParams));
    }
    /* Switch on CRC after successfull activation */
    else
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams, PHHAL_HW_CONFIG_TXCRC, PH_ON));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams, PHHAL_HW_CONFIG_RXCRC, PH_ON));
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

    return PH_ADD_COMPCODE(status, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc523_Cmd_SoftReset(
                                       phhalHw_Rc523_DataParams_t * pDataParams
                                       )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;

    /* Terminate a probably running command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_COMMAND, PHHAL_HW_RC523_CMD_IDLE));

    /* clear all IRQ flags */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(
        pDataParams,
        PHHAL_HW_RC523_REG_COMMIRQ,
        (uint8_t)~(uint8_t)PHHAL_HW_RC523_BIT_IRQINV));

    /* start the command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_COMMAND, PHHAL_HW_RC523_CMD_SOFTRESET));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

#endif /* NXPBUILD__PHHAL_HW_RC523 */
