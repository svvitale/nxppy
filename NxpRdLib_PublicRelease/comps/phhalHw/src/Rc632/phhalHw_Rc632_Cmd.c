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
* Rc632 specific HAL-Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.1 $
* $Date: Fri Apr 15 09:29:10 2011 $
*
* History:
*
*/
#include <ph_Status.h>
#include <phbalReg.h>
#include <phhalHw.h>
#include <ph_RefDefs.h>
#include <string.h>

#ifdef NXPBUILD__PHHAL_HW_RC632

#include "phhalHw_Rc632.h"
#include "phhalHw_Rc632_Int.h"
#include "phhalHw_Rc632_Config.h"
/* Implementation of the Commands specific to RC632 */

phStatus_t phhalHw_Rc632_Cmd_LoadKeyE2(phhalHw_Rc632_DataParams_t* pDataParams, 
									   uint8_t bKeyNo, 	    /* 0 <= bKeyNo <= 15 */
									   uint8_t bAuthMode) 
{
	phStatus_t statusTmp = PH_ERR_SUCCESS;
	/* eeprom address calculation
	0x80 ... offset
	key_sector ... sector
	0x18 ... 2 * 12 = 24 = 0x18 */
	uint16_t wAddress = 0x80 + (uint16_t)bKeyNo * 0x18;
	uint8_t *pE2Buf = (uint8_t*)&wAddress;
	uint8_t bIrqWaitfor = 0x0;

	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_SetTmo(pDataParams, 6800, PHHAL_HW_TIME_MICROSECONDS));
	if (bAuthMode == PHHAL_HW_RC632_AUTHMODE_KEYB)
		wAddress += 12; /* key B offset    */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_FlushFifo(pDataParams));    /* empty FIFO */

	bIrqWaitfor = PHHAL_HW_RC632_BIT_LOWALERTIRQ | PHHAL_HW_RC632_BIT_IDLEIRQ | PHHAL_HW_RC632_BIT_TIMERIRQ;
	/* write load key E2 command */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_Command_Int(pDataParams, PHHAL_HW_RC632_CMD_LOADKEYE2, PH_EXCHANGE_DEFAULT, bIrqWaitfor, pE2Buf, 2, 0, NULL, NULL));
	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}


phStatus_t  phhalHw_Rc632_Cmd_LoadKey(phhalHw_Rc632_DataParams_t * pDataParams, uint8_t *pKey)
{
	phStatus_t statusTmp = PH_ERR_SUCCESS;
	uint8_t bcnt = 0;
	uint8_t bIndex = 0;

	uint8_t bKey[13];
	uint8_t bIrqWaitfor = PHHAL_HW_RC632_BIT_IDLEIRQ | PHHAL_HW_RC632_BIT_TIMERIRQ;

	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_FlushFifo(pDataParams));    /* empty FIFO */
	/* Code the uncoded key*/
	for (bcnt = 0; bcnt < PHHAL_HW_RC632_MFC_KEY_LENGTH; ++bcnt)
	{
		bKey[bIndex++] = (uint8_t)((pKey[bcnt] >> 4) | ((uint8_t)(pKey[bcnt] & 0xF0) ^ 0xF0));
		bKey[bIndex++] = (uint8_t)(((uint8_t)(pKey[bcnt] << 4) ^ 0xF0) | (pKey[bcnt] & 0x0F));
	}

	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_Command_Int(
		pDataParams, 
		PHHAL_HW_RC632_CMD_LOADKEY, 
		PH_EXCHANGE_DEFAULT, 
		bIrqWaitfor, 
		bKey, PHHAL_HW_RC632_MFC_KEY_LENGTH*2, 0, NULL, NULL));
	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}


phStatus_t  phhalHw_Rc632_Cmd_ReadE2(
									 phhalHw_Rc632_DataParams_t* pDataParams, 
									 uint16_t wAddress, 
									 uint16_t wNumBytes, 
									 uint8_t * pData
									 )
{
	phStatus_t  statusTmp;
	uint8_t     bCmd[3];
	uint8_t     bIrqWaitFor;
	uint16_t    wDataLenTmp;

	/* Parameter check */
	if (wNumBytes > PHHAL_HW_RC632_VALUE_FIFOSIZE)
	{
		return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
	}

	/* 0 means 64, do this for the check below */
	if (wNumBytes == 0)
	{
		wNumBytes = PHHAL_HW_RC632_VALUE_FIFOSIZE;
	}

	/* Check Address range */
	if ((wAddress + wNumBytes) > PHHAL_HW_RC632_EEPROM_SIZE)
	{
		return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
	}

	/* Set wait IRQs */
	bIrqWaitFor = PHHAL_HW_RC632_BIT_LOWALERTIRQ | PHHAL_HW_RC632_BIT_HIALERTIRQ | PHHAL_HW_RC632_BIT_IDLEIRQ;

	/* Prepare command */
	bCmd[0] = (uint8_t)(wAddress);
	bCmd[1] = (uint8_t)(wAddress >> 8);
	bCmd[2] = (uint8_t)wNumBytes;

	/* Perform command */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_Command_Int(
		pDataParams, 
		PHHAL_HW_RC632_CMD_READE2, 
		PH_EXCHANGE_DEFAULT, 
		bIrqWaitFor, 
		bCmd, 
		sizeof(bCmd), 
		wNumBytes, 
		pData, 
		&wDataLenTmp));

	/* Check received data */
	if (wDataLenTmp != wNumBytes)
	{
		return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
	}

	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t  phhalHw_Rc632_Cmd_WriteE2(
									  phhalHw_Rc632_DataParams_t * pDataParams, 
									  uint16_t wAddress, 
									  uint8_t * pData, 
									  uint8_t bDataLen
									  )
{
	phStatus_t  statusTmp;
	uint8_t     bCmd[2];
	uint8_t     bIrqWaitFor;
	uint16_t    wFifoBytes;

	/* Check Address range and data length */
	if ((wAddress >= (PHHAL_HW_RC632_EEPROM_SIZE/PHHAL_HW_RC632_EEPROM_PAGE_SIZE)) 
		|| (bDataLen == 0) || (bDataLen > PHHAL_HW_RC632_EEPROM_PAGE_SIZE))
	{
		return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
	}

	/* Set wait IRQs */
	bIrqWaitFor = PHHAL_HW_RC632_BIT_TXIRQ | PHHAL_HW_RC632_BIT_LOWALERTIRQ;

	/* Flush FiFo */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_FlushFifo(pDataParams));

	/* Write Address into FIFO */
	bCmd[0] = (uint8_t)(wAddress);
	bCmd[1] = (uint8_t)(wAddress >> 8);
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteFifo(pDataParams, bCmd, 2, &wFifoBytes));

	/* Perform command */
	PH_CHECK_SUCCESS_FCT(statusTmp,phhalHw_Rc632_Command_Int(
		pDataParams, 
		PHHAL_HW_RC632_CMD_WRITEE2, 
		PHHAL_HW_RC632_OPTION_FIFO_NOCLEAR, 
		bIrqWaitFor, 
		pData, 
		(uint16_t)bDataLen, 
		0, 
		NULL, 
		NULL));

    /* Wait end of execution of Rc632 WriteE2 command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_Wait(    
        pDataParams,
        PHHAL_HW_TIME_MILLISECONDS,
        12
        ));

    /* Command has to be stopped manually to get back to Idle */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(    
        pDataParams,
        PHHAL_HW_RC632_REG_COMMAND,
        PHHAL_HW_RC632_CMD_IDLE
        ));
	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t  phhalHw_Rc632_Cmd_LoadConfig(phhalHw_Rc632_DataParams_t * pDataParams, 
										 uint16_t wEEAddress)
{
	uint8_t bCmd[2];
	uint8_t bIrqWaitFor;

	/* Parameter check */

	/* EEPROM address check */
	/* Check Address range */
	if ((wEEAddress + PHHAL_HW_RC632_MAX_NUM_REGS) > PHHAL_HW_RC632_EEPROM_SIZE)
	{
		return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
	}

	/* Set wait IRQs */
	bIrqWaitFor = 0x00;

	/* Prepare command */
	bCmd[0] = (uint8_t)(wEEAddress);
	bCmd[1] = (uint8_t)(wEEAddress >> 8);

	/* Perform command */
	return phhalHw_Rc632_Command_Int(
		pDataParams, 
		PHHAL_HW_RC632_CMD_LOADCONFIG, 
		PH_EXCHANGE_DEFAULT, 
		bIrqWaitFor, 
		bCmd, 
		sizeof(bCmd), 
		0, 
		NULL, 
		NULL);
}

phStatus_t phhalHw_Rc632_Cmd_CalcCrc(
									 phhalHw_Rc632_DataParams_t *pDataParams, 
									 uint8_t * pData, 
									 uint16_t wDataLength, 
									 uint16_t * pCrcResult
									 )
{
	phStatus_t  PH_MEMLOC_REM	status;
	phStatus_t  PH_MEMLOC_REM	statusTmp;
	uint16_t    PH_MEMLOC_REM	wFifoBytes;
	uint8_t     PH_MEMLOC_REM	bIrqWaitFor;
	uint8_t     PH_MEMLOC_REM	bIrqRq = 0x00;
	uint8_t		PH_MEMLOC_REM	bRegister;
	uint8_t     PH_MEMLOC_REM	bError;
	uint8_t		PH_MEMLOC_REM	bCRCRes;
	uint8_t *   PH_MEMLOC_REM	pTmpBuffer;
	uint16_t    PH_MEMLOC_REM	wTmpBufferLen;
	uint16_t    PH_MEMLOC_REM	wTmpBufferSize;

	/* Check length */
	if ((wDataLength == 0) || (wDataLength > 64))
	{
		return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
	}

	/* Flush FiFo */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_FlushFifo(pDataParams));

	/* Retrieve transmit buffer properties */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_GetTxBuffer(pDataParams, PH_OFF, &pTmpBuffer, &wTmpBufferLen, &wTmpBufferSize));

	/* Check for buffer overflow */
	if (wTmpBufferSize < wDataLength)
	{
		return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
	}

	/* Copy data */
	memcpy(pTmpBuffer, pData, wDataLength);  /* PRQA S 3200 */

	/* Write FIFO */
	status = phhalHw_Rc632_WriteFifo(pDataParams, pTmpBuffer, wDataLength, &wFifoBytes);

	/* bail out on error */
	if ((status & PH_ERR_MASK) != PH_ERR_SUCCESS)
	{
		/* Flush FiFo */
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_FlushFifo(pDataParams));

		return PH_ADD_COMPCODE(status, PH_COMP_HAL);
	}

	/* start the command */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_COMMAND, PHHAL_HW_RC632_CMD_CALCCRC));

	/* wait until the command is finished */

	bIrqWaitFor = PHHAL_HW_RC632_BIT_TXIRQ;
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WaitIrq(pDataParams, bIrqWaitFor, &bIrqRq));

	/* Stop the command explicitly by writing IDLE command */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_COMMAND, PHHAL_HW_RC632_CMD_IDLE));


	/* Check for errors */
	/* Check if an error occured */
	/* read the error register */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_ERROR_FLAG, &bError));

	/* key error */
	if (bError & PHHAL_HW_RC632_BIT_KEY_ERR)
	{
		status = PH_ERR_KEY;
	}
	else if(bError & PHHAL_HW_RC632_BIT_ACCESS_ERR)
	{
		status = PH_ERR_INTERNAL_ERROR;
	}
	/* buffer overflow */
	else if (bError & PHHAL_HW_RC632_BIT_FIFO_OVF)
	{
		status = PH_ERR_BUFFER_OVERFLOW;
	}
	/* Framing error */
	else if (bError & PHHAL_HW_RC632_BIT_FRAMING_ERR)
	{
		status = PH_ERR_FRAMING_ERROR;
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
		/* Read Secondarystatus1 register to check if the CRC READY bit is set */
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_SECONDARY_STATUS, &bRegister));

		/* Read the CRC registers and return the value */
		if (bRegister & PHHAL_HW_RC632_BIT_CRCREADY)
		{
			PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_CRC_RES_MSB, &bCRCRes));
			*pCrcResult = (uint16_t)bCRCRes;
			PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_CRC_RES_LSB, &bCRCRes));
			*pCrcResult = (*pCrcResult << 8) | (uint16_t)bCRCRes;
			status = PH_ERR_SUCCESS;
		}
		else
		{
			status = PH_ERR_INTERNAL_ERROR;
		}
	}
	return PH_ADD_COMPCODE(status, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc632_Cmd_Transmit(
									  phhalHw_Rc632_DataParams_t * pDataParams, 
									  uint16_t wOption, 
									  uint8_t * pTxBuffer, 
									  uint16_t wTxLength
									  )
{
	phStatus_t  PH_MEMLOC_REM	status;
	phStatus_t  PH_MEMLOC_REM	statusTmp;
	uint16_t    PH_MEMLOC_REM	wNumPrecachedBytes;
	uint16_t    PH_MEMLOC_REM	wFifoBytes;
	uint8_t     PH_MEMLOC_REM	bIrqWaitFor;
	uint8_t     PH_MEMLOC_REM	bIrqReg = 0x00;
	uint8_t     PH_MEMLOC_REM	bRegister;
	uint8_t     PH_MEMLOC_REM	bError;
	uint8_t     PH_MEMLOC_REM	bRestoreTmrSet;
	uint8_t *   PH_MEMLOC_REM	pTmpBuffer;
	uint16_t    PH_MEMLOC_REM	wTmpBufferLen;
	uint16_t    PH_MEMLOC_REM	wTmpBufferSize;

	/* Check options */
	if (wOption & (uint16_t)~(uint16_t)(PH_EXCHANGE_BUFFERED_BIT | 
										PH_EXCHANGE_LEAVE_BUFFER_BIT | 
										PHHAL_HW_RC632_OPTION_RXTX_TIMER_START))
	{
		return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
	}

	/* Custom option: do not start timer */
	if (!(wOption & PHHAL_HW_RC632_OPTION_RXTX_TIMER_START))
	{
		/* Timer */
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_CONTROL, &bRegister));
		bRegister &= (uint8_t)~(uint8_t)PHHAL_HW_RC632_BIT_TSTARTNOW;
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CONTROL, bRegister));
		bRestoreTmrSet = PH_ON;
	}
	else
	{
		/* To skip restoration sequence below */
		bRestoreTmrSet = PH_OFF;

		/* Clear custom option bit */
		wOption &= (uint16_t)~(uint16_t)PHHAL_HW_RC632_OPTION_RXTX_TIMER_START;
	}

	/* clear internal buffer if requested */
	if (!(wOption & PH_EXCHANGE_LEAVE_BUFFER_BIT))
	{
		pDataParams->wTxBufLen = 0;
	}

	/* Fill the global TxBuffer */
	/* Note: We always need to buffer for SPI, else the input buffer would get overwritten! */
	if ((wOption & PH_EXCHANGE_BUFFERED_BIT) ||
		(pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_SPI))
	{
		/* retrieve transmit buffer */
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_GetTxBuffer(pDataParams, PH_ON, &pTmpBuffer, &wTmpBufferLen, &wTmpBufferSize));

		if (wTxLength != 0)
		{
			/* TxBuffer overflow check */
			if (wTxLength > (wTmpBufferSize - wTmpBufferLen))
			{
				pDataParams->wTxBufLen = 0;
				return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
			}

			/* copy data */
			memcpy(pTmpBuffer, pTxBuffer, wTxLength);  /* PRQA S 3200 */
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
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_GetTxBuffer(pDataParams, PH_ON, &pTmpBuffer, &wTmpBufferLen, &wTmpBufferSize));

	/* Terminate a possibly running command */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_COMMAND, PHHAL_HW_RC632_CMD_IDLE));

	/* Flush FiFo */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_FlushFifo(pDataParams));


	/* Precache buffered contents into FIFO */
	wNumPrecachedBytes = (wTmpBufferLen > pDataParams->wMaxPrecachedBytes) ? pDataParams->wMaxPrecachedBytes : wTmpBufferLen;
	if (wNumPrecachedBytes > 0)
	{
		/* Perform actual write to FIFO */
		status = phhalHw_Rc632_WriteFifo(pDataParams, pTmpBuffer, wNumPrecachedBytes, &wFifoBytes);

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
			status = phhalHw_Rc632_WriteFifo(pDataParams, pTxBuffer, wNumPrecachedBytes, &wFifoBytes);

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
	/* clear all IRQ flags */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(
		pDataParams, 
		PHHAL_HW_RC632_REG_INT_REQ, 
		(uint8_t)~(uint8_t)PHHAL_HW_RC632_BIT_IRQ));

	/* start the command */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_COMMAND, PHHAL_HW_RC632_CMD_TRANSMIT));

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
#ifdef PHHAL_HW_RC632_FEATURE_FIFO_UNDERFLOW_CHECK
		/* read interrupt status */
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_INT_REQ, &bIrqReg));

		if ((bIrqReg & PHHAL_HW_RC632_BIT_IDLEIRQ) || (bIrq0Reg & PHHAL_HW_RC632_BIT_TXIRQ))
		{
			/* stop the command */
			PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(
				pDataParams, 
				PHHAL_HW_RC632_REG_COMMAND, 
				PHHAL_HW_RC632_CMD_IDLE));

			/* Flush FiFo */
			PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_FlushFifo(pDataParams));

			return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
		}
#endif
		/* write remaining data to transmit into FiFo buffer */
		status = phhalHw_Rc632_WriteFifo(pDataParams, pTmpBuffer, wTmpBufferLen, &wFifoBytes);

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
	bIrqWaitFor = PHHAL_HW_RC632_BIT_IDLEIRQ | PHHAL_HW_RC632_BIT_LOWALERTIRQ; 

	/* wait until the command is finished */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WaitIrq(
		pDataParams, 
		bIrqWaitFor, 
		&bIrqReg));

	/* Check if an error occured */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_PRIMARY_STATUS, &bError));
	if (bError & PHHAL_HW_RC632_BIT_ERRIRQ)
	{
		/* read the error register */
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_ERROR_FLAG, &bError));

		if(bError & PHHAL_HW_RC632_BIT_ACCESS_ERR)
		{
			status = PH_ERR_INTERNAL_ERROR;
		}
		/* buffer overflow */
		else if (bError & PHHAL_HW_RC632_BIT_FIFO_OVF)
		{
			status = PH_ERR_BUFFER_OVERFLOW;
		}
		/* Framing error */
		else if (bError & PHHAL_HW_RC632_BIT_FRAMING_ERR)
		{
			status = PH_ERR_FRAMING_ERROR;
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

	/* Reset TxLastBits */
	if (pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXLASTBITS] != 0)
	{
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_SetConfig(pDataParams, PHHAL_HW_CONFIG_TXLASTBITS, 0x00));
	}

	/* Restore correct timer setting */
	if (bRestoreTmrSet)
	{
		/* Timer */
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_CONTROL, &bRegister));
		bRegister |= PHHAL_HW_RC632_BIT_TSTARTNOW;
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_CONTROL, bRegister));
	}
	return PH_ADD_COMPCODE(status, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc632_Cmd_Receive(
									 phhalHw_Rc632_DataParams_t * pDataParams, 
									 uint16_t wOption, 
									 uint8_t ** ppRxBuffer, 
									 uint16_t * pRxLength)
{
	phStatus_t  PH_MEMLOC_REM	status;
	phStatus_t  PH_MEMLOC_REM	statusTmp;
	uint16_t    PH_MEMLOC_REM	wFifoBytes;
	uint8_t     PH_MEMLOC_REM	bIrqWaitFor;
	uint8_t     PH_MEMLOC_REM	bIrqReg = 0x00;
	uint8_t     PH_MEMLOC_REM	bRegister;
	uint8_t     PH_MEMLOC_REM	bRegRxWait;
	uint8_t     PH_MEMLOC_REM	bError;
	uint32_t    PH_MEMLOC_REM	dwTimingSingle = 0x0;
	uint8_t *   PH_MEMLOC_REM	pTmpBuffer;
	uint16_t    PH_MEMLOC_REM	wTmpBufferLen;
	uint16_t    PH_MEMLOC_REM	wTmpBufferSize;

	/* Check options */
	if (wOption & (uint16_t)~(uint16_t)(PHHAL_HW_RC632_OPTION_RXTX_TIMER_START))
	{
		return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
	}

	/* Reduce RxWait to minimum */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_RX_WAIT, &bRegRxWait));
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_WAIT, 0x3)); 

	/* set the receive length */
	if (pRxLength != NULL)
	{
		*pRxLength = 0;
	}

	/* Terminate a probably running command */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_COMMAND, PHHAL_HW_RC632_CMD_IDLE));

	/* Flush FiFo */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_FlushFifo(pDataParams));

	/* clear all IRQ flags */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(
		pDataParams, 
		PHHAL_HW_RC632_REG_INT_REQ, 
		(uint8_t)~(uint8_t)PHHAL_HW_RC632_BIT_IRQ));

	/* timer should be running, otherwise we'd wait forever */
	if (!(wOption & PHHAL_HW_RC632_OPTION_RXTX_TIMER_START))
	{
		/* retrieve content of Timer Control register */
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_SECONDARY_STATUS, &bRegister));

		/* Check TRunning flag */
		if (!(bRegister & PHHAL_HW_RC632_BIT_TRUNNING))
		{
			return PH_ADD_COMPCODE(PH_ERR_IO_TIMEOUT, PH_COMP_HAL);
		}
	}

	/* start the command */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_COMMAND, PHHAL_HW_RC632_CMD_RECEIVE));

	/* start timer manually if requested */
	if (wOption & PHHAL_HW_RC632_OPTION_RXTX_TIMER_START)
	{
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_RELOAD, &bRegister));
		/* retrieve content of Timer Control register */
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_CONTROL, &bRegister));
		/* manually start Timer */
		bRegister |= PHHAL_HW_RC632_BIT_TSTARTNOW;

		/* Write the changed value*/
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(
			pDataParams, 
			PHHAL_HW_RC632_REG_CONTROL, 
			bRegister));
	}

	/* Set wait IRQs */
	bIrqWaitFor = PHHAL_HW_RC632_BIT_RXIRQ | PHHAL_HW_RC632_BIT_HIALERTIRQ | PHHAL_HW_RC632_BIT_IDLEIRQ | PHHAL_HW_RC632_BIT_TIMERIRQ;

	/* wait until the command is finished */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WaitIrq(
		pDataParams, 
		bIrqWaitFor, 
		&bIrqReg));

	/* Timeout handling */
	if ((bIrqWaitFor & PHHAL_HW_RC632_BIT_TIMERIRQ) && (bIrqReg & PHHAL_HW_RC632_BIT_TIMERIRQ))
	{
		/* stop the command */
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(
			pDataParams, 
			PHHAL_HW_RC632_REG_COMMAND, 
			PHHAL_HW_RC632_CMD_IDLE));

		/* Flush FiFo */
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_FlushFifo(pDataParams));

		/* retrieve content of Timer Control register */
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_CONTROL, &bRegister));

		/* manually stop timers */
		bRegister |= PHHAL_HW_RC632_BIT_TSTOPNOW;
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_CONTROL, bRegister));

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

	/* Reset receive buffer length */
	pDataParams->wRxBufLen = 0;

	/* Retrieve receive buffer properties */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_GetRxBuffer(pDataParams, PH_ON, &pTmpBuffer, &wTmpBufferLen, &wTmpBufferSize));

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
				wTmpBufferSize, 
				&pTmpBuffer[wTmpBufferLen], 
				&wFifoBytes));

			/* advance receive buffer */
			wTmpBufferLen = wTmpBufferLen + wFifoBytes;
			wTmpBufferSize = wTmpBufferSize - wFifoBytes;

			/* read interrupt status */
			PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_INT_REQ, &bIrqReg));
		}
		while ((!(bIrqReg & bIrqWaitFor)) || (wFifoBytes != 0));

		/* Check if an error occured */
		/* read the error register */
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_ERROR_FLAG, &bError));

		if(bError & PHHAL_HW_RC632_BIT_ACCESS_ERR)
		{
			status = PH_ERR_INTERNAL_ERROR;
		}
		/* buffer overflow */
		else if (bError & PHHAL_HW_RC632_BIT_FIFO_OVF)
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
			if (wTmpBufferLen == 0)
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
					wTmpBufferLen = 0;

				}
				else
				{
					wTmpBufferLen = ((uint8_t)(bRegister - 1) >> 3);
				}

                /* Restore wRxBufSize */
                wTmpBufferSize = wTmpBufferSize + wTmpBufferLen;

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
		if (wTmpBufferLen == 0)
		{
			status = PH_ERR_IO_TIMEOUT;
		}
		else
		{
		/* Retrieve valid bits of last byte */
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_SECONDARY_STATUS, &bRegister));

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
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_COMMAND, PHHAL_HW_RC632_CMD_IDLE));

		/* Flush FiFo */
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_FlushFifo(pDataParams));
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
	if ((pDataParams->wTimingMode & (uint16_t)~(uint16_t)PHHAL_HW_TIMING_MODE_OPTION_MASK) == PHHAL_HW_TIMING_MODE_COMM)
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

	/* Restore RxWait setting */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_RX_WAIT, bRegRxWait));

	return PH_ADD_COMPCODE(status, PH_COMP_HAL);
}

#endif /* NXPBUILD__PHHAL_HW_RC632 */
