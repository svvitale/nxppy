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
* PEGODA USB (Windows) BAL Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.7 $
* $Date: Fri Apr 15 09:26:54 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/
#include <ph_Status.h>
#include <phbalReg.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHBAL_REG_RD70XUSBWIN

#include "phbalReg_Rd70xUsbWin.h"
#include "phbalReg_Rd70xUsbWin_Int.h"

phStatus_t phbalReg_Rd70xUsbWin_Init(
									 phbalReg_Rd70xUsbWin_DataParams_t * pDataParams,
									 uint16_t wSizeOfDataParams
									 )
{
#ifdef _WIN32
	if (sizeof(phbalReg_Rd70xUsbWin_DataParams_t) != wSizeOfDataParams)
	{
		return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);
	}
	PH_ASSERT_NULL (pDataParams);

	/* initialize the data parameters to default values */
	pDataParams->wId            = PH_COMP_BAL | PHBAL_REG_RD70X_USBWIN_ID;
	pDataParams->ucTxSeq        = 0;
    pDataParams->pDeviceName    = NULL;
	pDataParams->pDeviceHandle  = INVALID_HANDLE_VALUE;
	pDataParams->pPipeOut       = INVALID_HANDLE_VALUE;
	pDataParams->pPipeIn        = INVALID_HANDLE_VALUE;
	pDataParams->wTimeoutWrMs   = PHBAL_REG_RD70XUBSWIN_DEFAULT_TIMEOUT_MS;
	pDataParams->wTimeoutRdMs   = PHBAL_REG_RD70XUBSWIN_DEFAULT_TIMEOUT_MS;

	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
    /* satisfy compiler */
	if (pDataParams || wSizeOfDataParams);
	return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_Rd70xUsbWin_GetPortList(
	phbalReg_Rd70xUsbWin_DataParams_t * pDataParams,
	uint16_t wPortBufSize,
	uint8_t * pPortNames,
	uint16_t * pNumOfPorts
	)
{
#ifdef _WIN32
    /* satisfy compiler */
    if (pDataParams);

    /* scan for devices */
	return phbalReg_Rd70xUsbWin_ScanForDevices(
		wPortBufSize,
		pPortNames,
		pNumOfPorts
		);
#else
    /* satisfy compiler */
	if (pDataParams || wPortBufSize || pPortNames || pNumOfPorts);
	return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_Rd70xUsbWin_SetPort(
										phbalReg_Rd70xUsbWin_DataParams_t * pDataParams,
										uint8_t * pPortName
										)
{
#ifdef _WIN32
	pDataParams->pDeviceName = pPortName;
	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
    /* satisfy compiler */
	if (pDataParams || pPortName);
	return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_Rd70xUsbWin_Exchange(
	phbalReg_Rd70xUsbWin_DataParams_t * pDataParams,
    uint16_t wOption,
	uint8_t * pTxBuffer,
	uint16_t wTxLength,
	uint16_t wRxBufSize,
	uint8_t * pRxBuffer,
	uint16_t * pRxLength
	)
{
#ifdef _WIN32
	phStatus_t  PH_MEMLOC_REM status;
	DWORD       PH_MEMLOC_REM dwBytesRead;
	DWORD       PH_MEMLOC_REM dwBytesWritten;
    uint8_t     PH_MEMLOC_BUF bTxRxBuffer[65];
    uint16_t    PH_MEMLOC_REM wTxRxBufferLen;
    uint16_t    PH_MEMLOC_REM wTxBytesSent;
    uint8_t *   PH_MEMLOC_REM pTxRxBufferPtr;

    /* Check options */
    if (wOption != PH_EXCHANGE_DEFAULT)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_BAL);
    }

    /* reset receive length */
    *pRxLength = 0;

	/* Length check */
	if (wTxLength < 2)
	{
		return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_BAL);
	}

    /* Transmit Loop */
    wTxBytesSent = 0;
    do
    {
        /* First Packet handling */
        if (wTxBytesSent == 0)
        {
            /* Evaluate packet length */
            wTxRxBufferLen = (wTxLength > (PHBAL_REG_RD70XUBSWIN_PACKET_SIZE - 1)) ? (PHBAL_REG_RD70XUBSWIN_PACKET_SIZE - 1) : wTxLength;

            /* Copy First-Frame-TxData */
            memcpy(&bTxRxBuffer[1], pTxBuffer, wTxRxBufferLen);  /* PRQA S 3200 */

            /* Prepend sequence number */
            bTxRxBuffer[0] = pDataParams->ucTxSeq;
            ++wTxRxBufferLen;

            /* Set transmit buffer pointer to local buffer */
            pTxRxBufferPtr = bTxRxBuffer;
        }
        else
        {
            /* Evaluate packet length */
            wTxRxBufferLen = (wTxLength > PHBAL_REG_RD70XUBSWIN_PACKET_SIZE) ? PHBAL_REG_RD70XUBSWIN_PACKET_SIZE : wTxLength;

            /* Set transmit buffer pointer to input buffer data */
            pTxRxBufferPtr = &pTxBuffer[wTxBytesSent];
        }

        /* transmit the data */
        status = phbalReg_Rd70xUsbWin_DoOverlappedWrite(
            pDataParams->pPipeOut,
            (uint32_t)pDataParams->wTimeoutWrMs,
            pTxRxBufferPtr,
            wTxRxBufferLen,
            &dwBytesWritten);

        /* check status */
        PH_CHECK_SUCCESS(status);

        /* Check for interface error */
        if (dwBytesWritten != (DWORD)wTxRxBufferLen)
        {
            return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
        }

        /* First packet -> do not count sequence number as sent byte */
        if (wTxBytesSent == 0)
        {
            --wTxRxBufferLen;
        }

        /* Increment Tx-Length information */
        wTxBytesSent = wTxBytesSent + wTxRxBufferLen;
        wTxLength = wTxLength - wTxRxBufferLen;
    }
    while (wTxLength > 0);

    /* Workaround: Driver does not handle USB protocol correctly, last block must not occupy the full frame */
    if (dwBytesWritten == PHBAL_REG_RD70XUBSWIN_PACKET_SIZE)
    {
        status = phbalReg_Rd70xUsbWin_DoOverlappedWrite(
            pDataParams->pPipeOut,
            (uint32_t)pDataParams->wTimeoutWrMs,
            pTxRxBufferPtr,
            1,
            &dwBytesWritten);

        /* check status */
        PH_CHECK_SUCCESS(status);
    }

    /* Receive Loop */
    pTxRxBufferPtr = bTxRxBuffer;
    do
    {
        /* read the received data */
        status = phbalReg_Rd70xUsbWin_DoOverlappedRead(
            pDataParams->pPipeIn,
            (uint32_t)pDataParams->wTimeoutRdMs,
            PHBAL_REG_RD70XUBSWIN_PACKET_SIZE,
            pTxRxBufferPtr,
            &dwBytesRead);

        /* Error check */
        if ((status & PH_ERR_MASK) != ERROR_SUCCESS)
        {
            break;
        }

        /* check received length */
        if (dwBytesRead == 0)
        {
            status = PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_BAL);
            break;
        }

        /* First Packet handling */
        if (*pRxLength == 0)
        {
            /* buffer overflow check */
            if ((*pRxLength + dwBytesRead - 1) > wRxBufSize)
            {
                status = PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_BAL);
                break;
            }

            /* check received sequence number */
            if (bTxRxBuffer[0] != pDataParams->ucTxSeq)
            {
                status = PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_BAL);
                break;
            }

            /* copy received contents (without sequence number) to receive buffer */
            memcpy(pRxBuffer, &pTxRxBufferPtr[1], dwBytesRead - 1);  /* PRQA S 3200 */
            *pRxLength = (uint16_t)(dwBytesRead - 1);
        }
        else
        {
            /* buffer overflow check */
            if ((*pRxLength + dwBytesRead) > wRxBufSize)
            {
                status = PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_BAL);
                break;
            }

            *pRxLength = *pRxLength + (uint16_t)dwBytesRead;
        }

        /* Update receive buffer pointer */
        pTxRxBufferPtr = &pRxBuffer[*pRxLength];
    }
    while (dwBytesRead == PHBAL_REG_RD70XUBSWIN_PACKET_SIZE);

	/* Increment the sequence number */
	++pDataParams->ucTxSeq;

	return status;
#else
    /* satisfy compiler */
	if (pDataParams || pTxBuffer || wTxLength || wRxBufSize || pRxBuffer || pRxLength);
	return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_Rd70xUsbWin_OpenPort(
	phbalReg_Rd70xUsbWin_DataParams_t * pDataParams
	)
{
#ifdef _WIN32
	phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_BUF pPipeName[512];

	/* check if device is open */
	if (pDataParams->pDeviceHandle != INVALID_HANDLE_VALUE)
	{
		return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_BAL);
	}

    /* open the reader device */
	PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Rd70xUsbWin_OpenHandle((char*)pDataParams->pDeviceName, &pDataParams->pDeviceHandle));

	/* switch to configuration 1 */
	status = phbalReg_Rd70xUsbWin_SetConfiguration(pDataParams->pDeviceHandle, 1);
	if ((status & PH_ERR_MASK) != PH_ERR_SUCCESS) 
	{
        PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Rd70xUsbWin_CloseHandle(pDataParams->pDeviceHandle));
        pDataParams->pDeviceHandle = INVALID_HANDLE_VALUE;
		return status;
	}

	/* switch to interface 0, alternate setting 1 */
	status = phbalReg_Rd70xUsbWin_SetInterface(pDataParams->pDeviceHandle, 0, 1);
	if ((status & PH_ERR_MASK) != PH_ERR_SUCCESS) 
	{
        PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Rd70xUsbWin_CloseHandle(pDataParams->pDeviceHandle));
        pDataParams->pDeviceHandle = INVALID_HANDLE_VALUE;
		return status;
	}

    /* check for internal buffer overflow */
    if (strlen((char*)pDataParams->pDeviceName) > (sizeof(pPipeName) - strlen(PHBAL_REG_RD70XUBSWIN_WRITE_PIPE) - 2))
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Rd70xUsbWin_CloseHandle(pDataParams->pDeviceHandle));
        pDataParams->pDeviceHandle = INVALID_HANDLE_VALUE;
        return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_BAL);
    }

    /* prepare Out-pipe identifier string */
    strcpy((char*)pPipeName, (char*)pDataParams->pDeviceName);  /* PRQA S 3200 */
    strcat((char*)pPipeName, "\\");                             /* PRQA S 3200 */
    strcat((char*)pPipeName, PHBAL_REG_RD70XUBSWIN_WRITE_PIPE); /* PRQA S 3200 */

    /* open pipe  */
    status = phbalReg_Rd70xUsbWin_OpenHandle((char*)pPipeName, &pDataParams->pPipeOut);
	if ((status & PH_ERR_MASK) != PH_ERR_SUCCESS) 
	{
        PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Rd70xUsbWin_CloseHandle(pDataParams->pDeviceHandle));
        pDataParams->pDeviceHandle = INVALID_HANDLE_VALUE;
		return status;
	}

    /* prepare In-pipe identifier string */
    pPipeName[strlen((char*)pPipeName) - strlen(PHBAL_REG_RD70XUBSWIN_WRITE_PIPE)] = '\0';
    strcat((char*)pPipeName, PHBAL_REG_RD70XUBSWIN_READ_PIPE); /* PRQA S 3200 */

    /* open pipe  */
    status = phbalReg_Rd70xUsbWin_OpenHandle((char*)pPipeName, &pDataParams->pPipeIn);
	if ((status & PH_ERR_MASK) != PH_ERR_SUCCESS) 
	{
        PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Rd70xUsbWin_CloseHandle(pDataParams->pPipeOut));
        pDataParams->pPipeOut = INVALID_HANDLE_VALUE;
        PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Rd70xUsbWin_CloseHandle(pDataParams->pDeviceHandle));
        pDataParams->pDeviceHandle = INVALID_HANDLE_VALUE;
		return status;
	}

	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
    /* satisfy compiler */
	if (pDataParams);
	return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_Rd70xUsbWin_ClosePort(
	phbalReg_Rd70xUsbWin_DataParams_t * pDataParams
	)
{
#ifdef _WIN32
	phStatus_t PH_MEMLOC_REM statusTmp;
    
    /* release all open handles */
	PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Rd70xUsbWin_CloseHandle(pDataParams->pPipeIn));
    PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Rd70xUsbWin_CloseHandle(pDataParams->pPipeOut));
    PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Rd70xUsbWin_CloseHandle(pDataParams->pDeviceHandle));

	/* reset the handles */
	pDataParams->pPipeIn = INVALID_HANDLE_VALUE;
    pDataParams->pPipeOut = INVALID_HANDLE_VALUE;
    pDataParams->pDeviceHandle = INVALID_HANDLE_VALUE;

	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
    /* satisfy compiler */
	if (pDataParams);
	return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_Rd70xUsbWin_SetConfig(
	phbalReg_Rd70xUsbWin_DataParams_t * pDataParams,
	uint16_t wConfig,
	uint16_t wValue
	)
{
#ifdef _WIN32
	switch(wConfig)
	{
	case PHBAL_REG_CONFIG_WRITE_TIMEOUT_MS:
		pDataParams->wTimeoutWrMs = wValue;
		break;
	case PHBAL_REG_CONFIG_READ_TIMEOUT_MS:
		pDataParams->wTimeoutRdMs = wValue;
		break;
	default:
		return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_BAL);
	}
	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
	/* satisfy compiler */
	if (pDataParams || wConfig || wValue);
	return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_Rd70xUsbWin_GetConfig(
	phbalReg_Rd70xUsbWin_DataParams_t * pDataParams,
	uint16_t wConfig,
	uint16_t * pValue
	)
{
#ifdef _WIN32
	switch(wConfig)
	{
	case PHBAL_REG_CONFIG_WRITE_TIMEOUT_MS:
		*pValue = pDataParams->wTimeoutWrMs;
		break;
	case PHBAL_REG_CONFIG_READ_TIMEOUT_MS:
		*pValue = pDataParams->wTimeoutRdMs;
		break;
	default:
		return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_BAL);
	}
	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
	/* satisfy compiler */
    if (pDataParams || wConfig || pValue);
	return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

#endif /* NXPBUILD__PHBAL_REG_RD70XUSBWIN */
