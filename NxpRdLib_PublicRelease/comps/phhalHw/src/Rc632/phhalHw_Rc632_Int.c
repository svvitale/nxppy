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
* $Revision: 1.3 $
* $Date: Thu Jun 30 11:04:55 2011 $
*
* History:
*
*/
#include <ph_Status.h>
#include <phbalReg.h>
#include <ph_RefDefs.h>
#include <string.h>
#include <math.h>

#ifdef NXPBUILD__PHHAL_HW_RC632

#include "phhalHw_Rc632.h"
#include "phhalHw_Rc632_Int.h"
#include "phhalHw_Rc632_Config.h"


/* Digital delay for all protocols and speeds in microseconds */
static uint16_t wRc632_DigiDelays_Us[][4] =
{
	/* PHHAL_HW_CARDTYPE_ISO14443A */
	{/* 106KBaud */ 17, /* 212KBaud */ 49, /* 424KBaud */ 45, /* 848KBaud */ 42}, 

	/* PHHAL_HW_CARDTYPE_ISO14443B */
	{/* 106KBaud */ 0, /* 212KBaud */ 0, /* 424KBaud */ 0, /* 848KBaud */ 0}, 

	/* PHHAL_HW_CARDTYPE_FELICA */
	{/* N/A */ 0, /* 212KBaud */ 322, /* 424KBaud */ 165, /* N/A */ 0}, 

	/* PHHAL_HW_CARDTYPE_ISO15693 */
	{/* LOW */ 0, /* HIGH */ 193, /* FAST_LOW */ 0, /* FAST_HIGH */ 89}, 

	/* PHHAL_HW_CARDTYPE_ICODEEPCUID */
	{/* ALL */ 61, /* N/A */ 0, /* N/A */ 0, /* N/A */ 0}, 

	/* PHHAL_HW_CARDTYPE_I18000P3M3 */
	{/* ALL */ 73, /* N/A */ 0, /* N/A */ 0, /* N/A */ 0}, 

	/* PHHAL_HW_CARDTYPE_I18092MPI */
	{/* 106KBaud */ 17, /* 212KBaud */ 322, /* 424KBaud */ 165, /* N/A */ 0}
};


/* Utility / Internal functions */

phStatus_t phhalHw_Rc632_SetBitMask(phhalHw_Rc632_DataParams_t* pDataParams, uint8_t reg, uint8_t mask) 
{
	uint8_t		PH_MEMLOC_REM	tmp    = 0x0;
	phStatus_t	PH_MEMLOC_REM	statusTmp = PH_ERR_SUCCESS;

	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, reg, &tmp));
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, reg, tmp | mask));  /* set bit mask */
	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc632_ClearBitMask(phhalHw_Rc632_DataParams_t* pDataParams, uint8_t reg, uint8_t mask)  
{
	uint8_t		PH_MEMLOC_REM	tmp    = 0x0;
	phStatus_t	PH_MEMLOC_REM	statusTmp = PH_ERR_SUCCESS;

	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, reg, &tmp));
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, reg, tmp & (uint8_t)~(uint8_t)mask));  /* clear bit mask */
	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc632_FlushFifo(phhalHw_Rc632_DataParams_t* pDataParams)
{  
	return phhalHw_Rc632_SetBitMask(pDataParams, PHHAL_HW_RC632_REG_CONTROL, 0x01);
}


phStatus_t phhalHw_Rc632_SetTmo(phhalHw_Rc632_DataParams_t* pDataParams, uint16_t wTimeout, uint8_t bUnit)
{
	phStatus_t  PH_MEMLOC_REM statusTmp;
	uint16_t    PH_MEMLOC_REM wPrescaler;
	uint16_t    PH_MEMLOC_REM wReload;
	float32_t   PH_MEMLOC_REM fTimeoutUs;
	float32_t   PH_MEMLOC_REM fTemp;
	uint16_t	PH_MEMLOC_REM wDelay = 0x0;

	/* Parameter check */
	if ((bUnit != PHHAL_HW_TIME_MICROSECONDS) && (bUnit != PHHAL_HW_TIME_MILLISECONDS))
	{
		return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
	}

    /* Retrieve and add digital delay */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_GetDigiDelay(pDataParams, PH_ON, &wDelay));

	/* Handle timeout in microseconds */
	if (bUnit == PHHAL_HW_TIME_MICROSECONDS)
	{
        fTimeoutUs = (float32_t)wTimeout + (float32_t)wDelay;
		wTimeout = 0;
	}
	else
	{
		fTimeoutUs = (float32_t)wTimeout * 1000.0f + (float32_t)wDelay / 1000.0f;
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
	/* Set new timeout value */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_CLOCK, (uint8_t)wPrescaler));
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_RELOAD, (uint8_t)wReload));

	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc632_GetTxBuffer(
									 phhalHw_Rc632_DataParams_t * pDataParams, 
									 uint8_t bIsExchange, 
									 uint8_t ** pTxBuffer, 
									 uint16_t * pTxBufferLen, 
									 uint16_t * pTxBufferSize
									 )
{
	/* Exchange command -> RxBuffer overwriting is allowed */
	if (bIsExchange != PH_OFF)
	{
		/* We need to watch that we do not overwrite content below the RxStartPos though */
		if (pDataParams->pTxBuffer == pDataParams->pRxBuffer)
		{
			*pTxBuffer = &pDataParams->pTxBuffer[pDataParams->wRxBufStartPos];
			*pTxBufferSize = pDataParams->wTxBufSize - pDataParams->wRxBufStartPos;
		}
		/* Else just return the actual Buffer */
		else
		{
			*pTxBuffer = pDataParams->pTxBuffer;
			*pTxBufferSize = pDataParams->wTxBufSize;
		}

		/* Return stored length */
		*pTxBufferLen = pDataParams->wTxBufLen;
	}
	/* Normal command -> do not overwrite Tx- and Rx-Contents */
	else
	{
		/* Redundant code */
		return phhalHw_Rc632_GetRxBuffer(pDataParams, bIsExchange, pTxBuffer, pTxBufferLen, pTxBufferSize);
	}

	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc632_GetRxBuffer(
									 phhalHw_Rc632_DataParams_t * pDataParams, 
									 uint8_t bIsExchange, 
									 uint8_t ** pRxBuffer, 
									 uint16_t * pRxBufferLen, 
									 uint16_t * pRxBufferSize
									 )
{
	/* Exchange command -> TxBuffer overwriting is allowed */
	if (bIsExchange != PH_OFF)
	{
		*pRxBuffer = &pDataParams->pRxBuffer[pDataParams->wRxBufStartPos];
		*pRxBufferSize = pDataParams->wRxBufSize - pDataParams->wRxBufStartPos;
		*pRxBufferLen = pDataParams->wRxBufLen;
	}
	/* Normal command -> do not overwrite Tx- and Rx-Contents */
	else
	{
		/* Command buffering is NOT supported by this HAL */
		*pRxBufferLen = 0;

		/* TxBuffer equals RxBuffer */
		if ((pDataParams->pTxBuffer == pDataParams->pRxBuffer) &&
			((pDataParams->wTxBufLen != 0) || (pDataParams->wRxBufLen != 0) || (pDataParams->wRxBufStartPos != 0)))
		{
			/* Start at TxLenght if neccessary */
			if ((pDataParams->wRxBufStartPos + pDataParams->wTxBufLen) >= pDataParams->wRxBufLen)
			{
				*pRxBuffer = &pDataParams->pTxBuffer[pDataParams->wRxBufStartPos + pDataParams->wTxBufLen];
				*pRxBufferSize = pDataParams->wTxBufSize - (pDataParams->wRxBufStartPos + pDataParams->wTxBufLen);
			}
			/* Else start at RxLenght */
			else
			{
				*pRxBuffer = &pDataParams->pRxBuffer[pDataParams->wRxBufLen];
				*pRxBufferSize = pDataParams->wRxBufSize - pDataParams->wRxBufLen;
			}
		}
		/* Buffers are different */
		else
		{
			/* Use TxBuffer if it has more space than RxBuffer */
			if ((pDataParams->wTxBufSize - pDataParams->wTxBufLen) >= (pDataParams->wRxBufSize - pDataParams->wRxBufLen))
			{
				*pRxBuffer = &pDataParams->pTxBuffer[pDataParams->wTxBufLen];
				*pRxBufferSize = pDataParams->wTxBufSize - pDataParams->wTxBufLen;
			}
			/* Else use RxBuffer */
			else
			{
				*pRxBuffer = &pDataParams->pRxBuffer[pDataParams->wRxBufLen];
				*pRxBufferSize = pDataParams->wRxBufSize - pDataParams->wRxBufLen;
			}
		}
	}

	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}


phStatus_t phhalHw_Rc632_Command_Int(
									 phhalHw_Rc632_DataParams_t * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
									 uint8_t bCmd,                              /**< [In] Command code. */
									 uint16_t wOption,                          /**< [In] Option parameter. */
									 uint8_t bIrqWaitFor,                      /**< [In] Bitmask of interrupts in Irq0 register to wait for. */
									 uint8_t * pTxBuffer,                       /**< [In] Data to transmit. */
									 uint16_t wTxLength,                        /**< [In] Length of input data. */
									 uint16_t wRxBufferSize,                    /**< [In] Size of receive buffer. */
									 uint8_t * pRxBuffer,                       /**< [Out] Pointer to received data. */
									 uint16_t * pRxLength                       /**< [Out] Number of received data bytes. */
									 )
{

	phStatus_t  PH_MEMLOC_REM	status = PH_ERR_SUCCESS;
	phStatus_t  PH_MEMLOC_REM	statusTmp;
	uint16_t    PH_MEMLOC_REM	wFifoBytes;
	uint8_t     PH_MEMLOC_REM	bIrqReg = 0x00;
	uint8_t     PH_MEMLOC_REM	bRegister;
	uint8_t     PH_MEMLOC_REM	bCmdNoWrite;
	uint8_t     PH_MEMLOC_REM	bError;
	uint8_t *   PH_MEMLOC_REM	pTmpBuffer;
	uint16_t    PH_MEMLOC_REM	wTmpBufferSize;


	/* Check option byte, buffering is not allowed */
	if ((wOption & PH_EXCHANGE_BUFFERED_BIT) || (wOption & PH_EXCHANGE_LEAVE_BUFFER_BIT))
	{
		return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
	}

	/* For this command it is not allowed to write to registers during execution */
	if (bCmd == PHHAL_HW_RC632_CMD_LOADCONFIG) 
	{
		bCmdNoWrite = PH_ON;
	}
	else
	{
		bCmdNoWrite = PH_OFF;
	}

	/* reset received length */
	if (pRxLength != NULL)
	{
		*pRxLength = 0;
	}

	/* */
	/* Evaluate temporary buffer */
	/* */

	/* TxBuffer equals RxBuffer */
	if ((pDataParams->pTxBuffer == pDataParams->pRxBuffer) &&
		((pDataParams->wTxBufLen != 0) || (pDataParams->wRxBufLen != 0)))
	{
		/* Start at TxLenght if neccessary */
		if ((pDataParams->wTxBufStartPos + pDataParams->wTxBufLen) >= pDataParams->wRxBufLen)
		{
			pTmpBuffer = &pDataParams->pTxBuffer[pDataParams->wTxBufStartPos + pDataParams->wTxBufLen];
			wTmpBufferSize = pDataParams->wTxBufSize - (pDataParams->wTxBufStartPos + pDataParams->wTxBufLen);
		}
		/* Else start at RxLenght */
		else
		{
			pTmpBuffer = &pDataParams->pRxBuffer[pDataParams->wRxBufLen];
			wTmpBufferSize = pDataParams->wRxBufSize - pDataParams->wRxBufLen;
		}
	}
	/* Buffers are different */
	else
	{
		/* Use TxBuffer if it has more space than RxBuffer */
		if ((pDataParams->wTxBufSize - pDataParams->wTxBufLen) >= (pDataParams->wRxBufSize - pDataParams->wRxBufLen))
		{
			pTmpBuffer = &pDataParams->pTxBuffer[pDataParams->wTxBufLen];
			wTmpBufferSize = pDataParams->wTxBufSize - pDataParams->wTxBufLen;
		}
		/* Else use RxBuffer */
		else
		{
			pTmpBuffer = &pDataParams->pRxBuffer[pDataParams->wRxBufLen];
			wTmpBufferSize = pDataParams->wRxBufSize - pDataParams->wRxBufLen;
		}
	}

	/* Check for buffer overflow */
	if (wTxLength > wTmpBufferSize)
	{
		return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
	}

	/* always wait for idle interrupt */
	bIrqWaitFor |= PHHAL_HW_RC632_BIT_IDLEIRQ;

	/* Terminate a probably running command */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_COMMAND, PHHAL_HW_RC632_CMD_IDLE));

	/* Flush FiFo */
	if (!(wOption & PHHAL_HW_RC632_OPTION_FIFO_NOCLEAR))
	{
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_FlushFifo(pDataParams));
	}

	/* clear all IRQ flags */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(
		pDataParams, 
		PHHAL_HW_RC632_REG_INT_REQ, 
		(uint8_t)~(uint8_t)PHHAL_HW_RC632_BIT_IRQ));

	/* write data into FIFO */
	if (wTxLength)
	{
		/* Buffer the data into the temporary buffer */
		memcpy(pTmpBuffer, pTxBuffer, wTxLength);  /* PRQA S 3200 */

		/* write data to transmit into FiFo buffer */
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteFifo(pDataParams, pTmpBuffer, wTxLength, &wFifoBytes));
	}
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_INT_REQ, &bRegister));

	/* Enable IRQ interrupt sources */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_INT_EN, &bRegister));
	bRegister |= bIrqWaitFor;
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_INT_EN, bRegister));

	/* start timer manually if requested */
	if (wOption & PHHAL_HW_RC632_OPTION_RXTX_TIMER_START)
	{
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

	/* start the command */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_COMMAND, bCmd));

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

		return PH_ADD_COMPCODE(PH_ERR_IO_TIMEOUT, PH_COMP_HAL);
	}

	/* mask out high-alert */
	bIrqWaitFor &= (uint8_t)~(uint8_t)PHHAL_HW_RC632_BIT_HIALERTIRQ;

	/* retrieve fifo bytes */
	if ((pRxBuffer != NULL) && (pRxLength != NULL))
	{
		do
		{
			/* retrieve bytes from FiFo */
			PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadFifo(
				pDataParams, 
				wTmpBufferSize - *pRxLength, 
				&pTmpBuffer[*pRxLength], 
				&wFifoBytes));

			/* advance receive buffer */
			*pRxLength = *pRxLength + wFifoBytes;

			/* read interrupt status */
			PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_INT_REQ, &bIrqReg));
		}
		while ((!(bIrqReg & bIrqWaitFor)) || (wFifoBytes != 0));

		/* Check for buffer overflow */
		if (*pRxLength > wRxBufferSize)
		{
			*pRxLength = 0;
			return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
		}
		/* Copy data to Receive Buffer */
		memcpy(pRxBuffer, pTmpBuffer, *pRxLength);  /* PRQA S 3200 */
	}
	/* Flush FIFO if contents are not retrieved */
	else
	{
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_FlushFifo(pDataParams));
	}

	/* Check if an error occured */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_PRIMARY_STATUS, &bError));
	if(bError & 0x4)
	{
		/* read the error register */
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_ERROR_FLAG, &bError));

		/* key error */
		/*if (bError & PHHAL_HW_RC632_BIT_KEY_ERR)
		{
			status = PH_ERR_KEY;
		}*/
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

	/* Stop Timer 0/1 if started */
	if (wOption & PHHAL_HW_RC632_OPTION_RXTX_TIMER_START)
	{
		/* retrieve content of Timer Control register */
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_CONTROL, &bRegister));

		/* manually stop timer */
		bRegister |= PHHAL_HW_RC632_BIT_TSTOPNOW ;
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_CONTROL, bRegister));
	}
	return PH_ADD_COMPCODE(status, PH_COMP_HAL);
}

phStatus_t  phhalHw_Rc632_MfcAuthenticate_Int(phhalHw_Rc632_DataParams_t* pDataParams, 
											  uint8_t bAuthMode, 
											  uint8_t *pUid, 
											  uint8_t bBlockNo)
{
	phStatus_t	PH_MEMLOC_REM	statusTmp = PH_ERR_SUCCESS;
	uint8_t		PH_MEMLOC_REM	bRegister = 0;
	uint8_t		PH_MEMLOC_REM	bTxBuffer[6];
	uint8_t		PH_MEMLOC_REM	bIrqWaitFor;
	void*		PH_MEMLOC_REM	pMem = NULL;

	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CHANNEL_REDUND, 0x07)); /* RxCRC disable, TxCRC, Parity enable */

	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_SetTmo(pDataParams, 1500, PHHAL_HW_TIME_MICROSECONDS));
	bTxBuffer[0] = bAuthMode;        /* write authentication command */

	bTxBuffer[1] = bBlockNo;    /* write block number for authentication */
	pMem = memcpy(&bTxBuffer[2], pUid, 4); /* write 4 bytes card serial number  */
	if(pMem == NULL)
	{
		return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);		
	}
	bIrqWaitFor = PHHAL_HW_RC632_BIT_TXIRQ | PHHAL_HW_RC632_BIT_TIMERIRQ | PHHAL_HW_RC632_BIT_IDLEIRQ;
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_Command_Int(pDataParams, PHHAL_HW_RC632_CMD_AUTHENT1, PH_EXCHANGE_DEFAULT, bIrqWaitFor, bTxBuffer, sizeof(bTxBuffer), 0, NULL, NULL));

	/* Send the Authenticate2 command */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_CHANNEL_REDUND, 0x03)); /* RxCRC, TxCRC disable, Parity enable */
	bIrqWaitFor = PHHAL_HW_RC632_BIT_TXIRQ | PHHAL_HW_RC632_BIT_TIMERIRQ | PHHAL_HW_RC632_BIT_IDLEIRQ;
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_Command_Int(pDataParams, PHHAL_HW_RC632_CMD_AUTHENT2, PH_EXCHANGE_DEFAULT, bIrqWaitFor, NULL, 0, 0, NULL, NULL));
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_CONTROL, &bRegister));
	if (bRegister & PHHAL_HW_RC632_BIT_CRYPTO1ON ) /* Crypto1 activated */
	{
		statusTmp = PH_ERR_SUCCESS;
	}
	else
	{
		statusTmp = PH_ERR_AUTH_ERROR;
	}
	/* Restore CRC settings */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams, PHHAL_HW_CONFIG_TXCRC, pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXCRC]));
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams, PHHAL_HW_CONFIG_RXCRC, pDataParams->wCfgShadow[PHHAL_HW_CONFIG_RXCRC]));

	return PH_ADD_COMPCODE(statusTmp, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc632_WriteFifo(
								   phhalHw_Rc632_DataParams_t * pDataParams, 
								   uint8_t * pData, 
								   uint16_t wLength, 
								   uint16_t * pBytesWritten
								   )
{
	phStatus_t  PH_MEMLOC_REM	statusTmp;
	uint16_t    PH_MEMLOC_REM	wIndex;
    uint8_t    PH_MEMLOC_REM	bFifoLen;
    /* Read out the lower FiFo Level bits */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_FIFO_LENGTH, &bFifoLen));

    /* Check if FiFO has enough space */
    if (wLength > (PHHAL_HW_RC632_VALUE_FIFOSIZE - bFifoLen))
    {
        /* Truncate byte count */
        wLength = PHHAL_HW_RC632_VALUE_FIFOSIZE - bFifoLen;

        /* Return buffer overflow error */
        statusTmp = PH_ERR_BUFFER_OVERFLOW;
    }
    else
    {
        statusTmp = PH_ERR_SUCCESS;
    }

    /* Perform actual write to FiFo */
    if (wLength > 0)
    {
		/* Write each single data byte */
		for (wIndex = 0; wIndex < wLength; ++wIndex)
		{
			PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_FIFO_DATA, pData[wIndex]));
		}
	}
	*pBytesWritten = wLength;
	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc632_ReadFifo(
								  phhalHw_Rc632_DataParams_t * pDataParams, 
								  uint16_t wBufSize, 
								  uint8_t * pData, 
								  uint16_t * pLength
								  )
{
	phStatus_t  PH_MEMLOC_REM	status;
	phStatus_t  PH_MEMLOC_REM	statusTmp;
	uint8_t     PH_MEMLOC_REM	bIndex;
	uint8_t     PH_MEMLOC_REM	bFifoLen;

	/* read out the FiFo Length register */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_FIFO_LENGTH, &bFifoLen));

	/* check for buffer overflow */
	if (bFifoLen > wBufSize)
	{
		/* read maximum possible number of bytes */
        bFifoLen = (uint8_t)((wBufSize > bFifoLen) ? PHHAL_HW_RC632_VALUE_FIFOSIZE : wBufSize);

		/* return buffer overflow status */
		status = PH_ERR_BUFFER_OVERFLOW;
	}
	else
	{
		/* Buffer is big enough */
		status = PH_ERR_SUCCESS;
	}
	/* Read each single data byte */
	for (bIndex = 0; bIndex < bFifoLen; ++bIndex)
	{
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_FIFO_DATA, &pData[bIndex]));
	}
	*pLength = (uint16_t)bFifoLen;

	return PH_ADD_COMPCODE(status, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc632_WriteData(
								   phhalHw_Rc632_DataParams_t * pDataParams, 
								   uint8_t bAddress, 
								   uint8_t * pData, 
								   uint16_t wLength
								   )
{
	phStatus_t  PH_MEMLOC_REM statusTmp;
	uint16_t    PH_MEMLOC_REM wBytesRead;
	uint8_t *   PH_MEMLOC_REM pTxBufferTmp;

	if(wLength == 0)
	{
		return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
	}
	/* shift address and clear RD/NWR bit to indicate write operation */
	bAddress = (uint8_t)(bAddress << 1);

	/* Write each single data byte */
	pTxBufferTmp = &pDataParams->pTxBuffer[pDataParams->wTxBufLen];
	/* Copy transmit buffer */
	memcpy(pTxBufferTmp, pData, wLength);  /* PRQA S 3200 */    
	pTxBufferTmp -= 4;
	pTxBufferTmp[0] = 0xB;
	pTxBufferTmp[1] = (uint8_t)(wLength);
	pTxBufferTmp[2] = (uint8_t)(wLength >> 8);
	pTxBufferTmp[3] = bAddress;
	wLength = wLength + 4;
	/* perform exchange */
	PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Exchange(pDataParams->pBalDataParams, PH_EXCHANGE_DEFAULT, pTxBufferTmp, wLength, wLength, pTxBufferTmp, &wBytesRead));
	/* check number of received bytes */
	if (wBytesRead != 5)
	{
		return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_HAL);
	}
	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc632_ReadData(
								  phhalHw_Rc632_DataParams_t * pDataParams, 
								  uint8_t bAddress, 
								  uint16_t wLength, 
								  uint8_t * pData
								  )
{
	phStatus_t  PH_MEMLOC_REM statusTmp;
	uint16_t    PH_MEMLOC_REM wBytesRead;
	uint8_t *   PH_MEMLOC_REM pTxBufferTmp;
	if(wLength == 0)
	{
		return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
	}
	/* shift address and set RD/NWR bit to indicate read operation */
	bAddress = (uint8_t)(bAddress << 1) | 0x01U;

	/* Write each single data byte */
	pTxBufferTmp = &pDataParams->pTxBuffer[pDataParams->wTxBufLen];
	/* Copy transmit buffer */
	memcpy(pTxBufferTmp, pData, wLength);  /* PRQA S 3200 */    
	pTxBufferTmp -= 4;
	pTxBufferTmp[0] = 0xA;
	pTxBufferTmp[1] = (uint8_t)(wLength);
	pTxBufferTmp[2] = (uint8_t)(wLength >> 8);
	pTxBufferTmp[3] = bAddress;
	wLength = wLength + 4;
	/* perform exchange */
	PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Exchange(pDataParams->pBalDataParams, PH_EXCHANGE_DEFAULT, pTxBufferTmp, wLength, wLength, pData, &wBytesRead));
	pData +=3;
	/* check number of received bytes */
	if (wBytesRead != (wLength - 1))
	{
		return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_HAL);
	}
	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc632_WaitIrq(
								 phhalHw_Rc632_DataParams_t * pDataParams, 
								 uint8_t bIrqWaitFor, 
								 uint8_t * pIrqReg
								 )
{
	phStatus_t PH_MEMLOC_REM	statusTmp;
	uint8_t    PH_MEMLOC_REM	bRegister;

	/* Parameter check */
	if (!bIrqWaitFor)
	{
		return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
	}

	/* Clear IRQ interrupt sources */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_INT_EN, 0x7F));          /* disable all interrupts */
	/* Enable IRQ interrupt sources */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_INT_EN, bIrqWaitFor | PHHAL_HW_RC632_BIT_IRQ));  /* enable neccessary interrupts */

	/* wait until an IRQ occurs */
	do
	{
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_PRIMARY_STATUS, &bRegister));
	}
	while (!(bRegister & PHHAL_HW_RC632_BIT_STATUS_IRQ));

	/* Clear IRQ interrupt sources */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_WriteRegister(pDataParams, PHHAL_HW_RC632_REG_INT_EN, 0x7F));          /* disable all interrupts */

	/* Return contents of IRQ register */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_INT_REQ, pIrqReg));
	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc632_CalculateFdt(
									  phhalHw_Rc632_DataParams_t * pDataParams, 
									  phStatus_t wExchangeStatus, 
									  uint32_t * pTime
									  )
{
	phStatus_t  PH_MEMLOC_REM	statusTmp;
	uint8_t     PH_MEMLOC_REM	bRegister;
	uint8_t     PH_MEMLOC_REM	bTReload;
	uint8_t		PH_MEMLOC_REM	bTValue;
	float32_t	PH_MEMLOC_REM	fTime;
	float32_t	PH_MEMLOC_REM	fTimeCurrent;
	uint8_t		PH_MEMLOC_REM	bTPrescaler;
	uint16_t    PH_MEMLOC_REM	wDelay;

	/* Get T reload value */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_RELOAD, &bRegister));
	bTReload = bRegister;

	/* Get T prescaler value */
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_CLOCK, &bRegister));
	bTPrescaler = bRegister;

	/* Get T counter value */
	if ((wExchangeStatus & PH_ERR_MASK) != PH_ERR_IO_TIMEOUT)
	{
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_ReadRegister(pDataParams, PHHAL_HW_RC632_REG_TIMER_VALUE, &bRegister));
		bTValue = bRegister;
	}
	else
	{
		bTValue = 0;
	}
	fTime = (float32_t)((float32_t)(bTReload * (1 << bTPrescaler)) / (float32_t)(PHHAL_HW_RC632_TIMER_FREQ));
	fTimeCurrent = (float32_t)((float32_t)(bTValue * (1 << bTPrescaler)) / (float32_t)(PHHAL_HW_RC632_TIMER_FREQ));

	/* Subtract reload- and counter values */
	fTime = fTime - fTimeCurrent;

	/*
	Now we can calculate the time in microseconds according to the following formular:
	{
	time[us] = (wTValue * (1 / (PHHAL_HW_RC632_TIMER_FREQ / wTReload))) + (wTValue * (1 / PHHAL_HW_RC632_TIMER_FREQ))
	}
	*/

	/* Return the value */
	*pTime = (uint32_t)fTime;
	if ((float32_t)*pTime < fTime)
	{
		++(*pTime);
	}

	/* Retrieve and subtract digital delay */
	if ((wExchangeStatus & PH_ERR_MASK) != PH_ERR_IO_TIMEOUT)
	{
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc632_GetDigiDelay(pDataParams, PH_OFF, &wDelay));
		*pTime = *pTime - wDelay;
	}

	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc632_GetDigiDelay(
									  phhalHw_Rc632_DataParams_t * pDataParams, 
									  uint8_t bIsTimeout, 
									  uint16_t * pDelayUs
									  )
{
	uint16_t    PH_MEMLOC_REM	wDataRate;
	uint8_t     PH_MEMLOC_REM	bIndex;

	wDataRate = pDataParams->wCfgShadow[PHHAL_HW_CONFIG_RXDATARATE];
	bIndex = pDataParams->bCardType - 1;

	switch (pDataParams->bCardType)
	{
	case PHHAL_HW_CARDTYPE_ISO14443A:
	case PHHAL_HW_CARDTYPE_ISO14443B:
		*pDelayUs = wRc632_DigiDelays_Us[bIndex][wDataRate];
		/* In a timeout case we have to add an additional delay */
		if (bIsTimeout != PH_OFF)
		{
			*pDelayUs = *pDelayUs + PHHAL_HW_RC632_I14443_ADD_DELAY_US;
		}
		break;
	case PHHAL_HW_CARDTYPE_FELICA:
		*pDelayUs = wRc632_DigiDelays_Us[bIndex][wDataRate];
		break;
	case PHHAL_HW_CARDTYPE_ISO15693:
		*pDelayUs = wRc632_DigiDelays_Us[bIndex][wDataRate - PHHAL_HW_RF_RX_DATARATE_LOW];
		/* In a timeout case we have to add an additional delay */
		if (bIsTimeout != PH_OFF)
		{
			if (wDataRate == PHHAL_HW_RF_RX_DATARATE_HIGH)
			{
				*pDelayUs = *pDelayUs + PHHAL_HW_RC632_I15693_ADD_DELAY_US;
			}
			else
			{
				*pDelayUs = *pDelayUs + (PHHAL_HW_RC632_I15693_ADD_DELAY_US >> 1);
			}
		}
		break;
	case PHHAL_HW_CARDTYPE_ICODEEPCUID:
		*pDelayUs = wRc632_DigiDelays_Us[bIndex][0];
		break;
	case PHHAL_HW_CARDTYPE_I18000P3M3:
		*pDelayUs = wRc632_DigiDelays_Us[bIndex][0];
		break;
	case PHHAL_HW_CARDTYPE_I18092MPI:
		*pDelayUs = wRc632_DigiDelays_Us[bIndex][wDataRate];
		/* In a timeout case we have to add an additional delay */
		if ((wDataRate == PHHAL_HW_RF_DATARATE_106) && (bIsTimeout != PH_OFF))
		{
			*pDelayUs = *pDelayUs + PHHAL_HW_RC632_I14443_ADD_DELAY_US;
		}
		break;
	default:
		return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
	}

	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

#endif /* NXPBUILD__PHHAL_HW_RC632 */
