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
* RS232 (Windows) BAL Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.6 $
* $Date: Fri Apr 15 09:04:38 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#include <ph_Status.h>
#include <phbalReg.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHBAL_REG_SERIALWIN

#include "phbalReg_SerialWin.h"
#include "phbalReg_SerialWin_Int.h"

#ifndef ONESTOPBIT
#define ONESTOPBIT 1
#endif

phStatus_t phbalReg_SerialWin_Init(
                                   phbalReg_SerialWin_DataParams_t * pDataParams,
                                   uint16_t wSizeOfDataParams,
                                   uint16_t wEnumBufSize,
                                   uint8_t * pEnumBuffer
                                   )
{
    if (sizeof(phbalReg_SerialWin_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);
    }
    if (wEnumBufSize > 0) PH_ASSERT_NULL (pEnumBuffer);
    /* set enumeration buffer to NULL if no size is given */
    if (wEnumBufSize == 0)
    {
        pEnumBuffer = NULL;
    }

    /* initialize the data parameters to default values */
    pDataParams->wId            = PH_COMP_BAL | PHBAL_REG_SERIALWIN_ID;
    pDataParams->pComHandle     = NULL;
    pDataParams->dwBitRate      = 9600;
    pDataParams->wTimeout       = PHBAL_REG_SERIALWIN_RX_TIMEOUT_VAL;
    pDataParams->pComPortString = NULL;
    pDataParams->wEnumBufSize   = wEnumBufSize;
    pDataParams->pEnumBuffer    = pEnumBuffer;
    pDataParams->bStopBits      = ONESTOPBIT;

#ifdef _WIN32
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
    /* satisfy compiler */
    if (pDataParams || wSizeOfDataParams || wEnumBufSize || pEnumBuffer);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_SerialWin_GetPortList(
    phbalReg_SerialWin_DataParams_t * pDataParams,
    uint16_t wPortBufSize,
    uint8_t * pPortNames,
    uint16_t * pNumOfPorts
    )
{
#ifdef _WIN32
    HKEY hKey;
    LONG eRetCode;
    DWORD eCnt;
    DWORD eDataLen; 
    DWORD eValueLen;

    /* GetPortList requires an enumeration buffer */
    if (pDataParams->pEnumBuffer == NULL)
    {
        return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_BAL);
    }

    *pNumOfPorts = 0;

    /* open a registry key to query the serial com ports */
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS) /* PRQA S 274 */
    {
        return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
    }

    eCnt = 0;
    do
    {
        eValueLen = pDataParams->wEnumBufSize;
        if (eValueLen > 0)
        {
            pDataParams->pEnumBuffer[0] = '\0'; 
        }
        eDataLen = wPortBufSize;

        /* query the values of the given registry key */
        eRetCode = RegEnumValue(
            hKey, 
            eCnt++, 
            (LPSTR)pDataParams->pEnumBuffer, 
            &eValueLen, 
            NULL, 
            NULL,
            pPortNames,
            &eDataLen);

        /* check for buffer overflow */
        if (eRetCode == ERROR_MORE_DATA)
        {
            eRetCode = RegCloseKey(hKey);
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_BAL);
        }

        /* valid entry found */
        if (eRetCode == ERROR_SUCCESS) 
        { 
            pPortNames += eDataLen;
            wPortBufSize = (uint16_t)wPortBufSize - (uint16_t)eDataLen;
            ++(*pNumOfPorts);
        } 
    } while (eRetCode != ERROR_NO_MORE_ITEMS);

    /* close the handle */
    if (RegCloseKey(hKey) != ERROR_SUCCESS)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
    /* satisfy compiler */
    if (pDataParams || wPortBufSize || pPortNames || pNumOfPorts);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_SerialWin_SetPort(
                                      phbalReg_SerialWin_DataParams_t * pDataParams,
                                      uint8_t * pPortName
                                      )
{
#ifdef _WIN32

    pDataParams->pComPortString = (int8_t*)pPortName;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
    /* satisfy compiler */
    if (pDataParams || pPortName);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_SerialWin_OpenPort(
                                       phbalReg_SerialWin_DataParams_t * pDataParams
                                       )
{
#ifdef _WIN32
    phStatus_t PH_MEMLOC_REM status;

    /* Check if port is already open */
    if (pDataParams->pComHandle != NULL)
    {
        return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_BAL);
    }

    /* Open port */
    pDataParams->pComHandle = CreateFile(
        (LPCSTR)pDataParams->pComPortString,    /* Serial port file name. */
        GENERIC_READ | GENERIC_WRITE,           /* Access (read-write) mode. */
        0,                                      /* Share mode. */
        NULL,                                   /* Pointer to the security attribute. */
        OPEN_EXISTING,                          /* How to open the serial port. */
        0,                                      /* Port attributes. */
        NULL);                                  /* Handle to port with attribute to copy. */

    /* Error Checking */
    if (pDataParams->pComHandle == INVALID_HANDLE_VALUE || pDataParams->pComHandle == NULL)
    {
        pDataParams->pComHandle = NULL;
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    /* Apply default settings to the port */
    status = phbalReg_SerialWin_SetMode(pDataParams->pComHandle, pDataParams->dwBitRate, pDataParams->bStopBits);
    if (status != PH_ERR_SUCCESS)
    {
        CloseHandle(pDataParams->pComHandle);  /* PRQA S 3200 */
        pDataParams->pComHandle = NULL;
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    /* Set the communication timeout */
    status = phbalReg_SerialWin_SetTimeout(pDataParams->pComHandle, (uint32_t)pDataParams->wTimeout);
    if (status != PH_ERR_SUCCESS)
    {
        CloseHandle(pDataParams->pComHandle);  /* PRQA S 3200 */
        pDataParams->pComHandle = NULL;
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
    /* satisfy compiler */
    if (pDataParams);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_SerialWin_ClosePort(
                                        phbalReg_SerialWin_DataParams_t * pDataParams
                                        )
{
#ifdef _WIN32
    BOOL status;

    if (pDataParams->pComHandle == NULL)
    {
        return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_BAL);
    }

    status = CloseHandle(pDataParams->pComHandle);
    pDataParams->pComHandle = NULL;

    /* Close the handle if it exists */
    if (status == FALSE)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
    /* satisfy compiler */
    pDataParams = NULL;
    return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_SerialWin_Exchange(
                                       phbalReg_SerialWin_DataParams_t * pDataParams,
                                       uint16_t wOption,
                                       uint8_t * pTxBuffer,
                                       uint16_t wTxLength,
                                       uint16_t wRxBufSize,
                                       uint8_t * pRxBuffer,
                                       uint16_t * pRxLength
                                       )
{
#ifdef _WIN32
    BOOL        PH_MEMLOC_REM status;
    uint32_t    PH_MEMLOC_REM dwBytesRead;
    uint32_t    PH_MEMLOC_REM dwBytesWritten;
    DWORD       PH_MEMLOC_REM dwErrors;
    COMSTAT     PH_MEMLOC_BUF abComstat;

    /* Check options */
    if (wOption != PH_EXCHANGE_DEFAULT)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_BAL);
    }

    /* Write the transmit data */
    status = WriteFile(pDataParams->pComHandle, pTxBuffer, wTxLength, &dwBytesWritten, NULL);

    /* Error check */
    if ((status == FALSE) || (dwBytesWritten != (uint32_t)wTxLength))
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    /* Read the received data */
    status = ReadFile(pDataParams->pComHandle, pRxBuffer, wRxBufSize, &dwBytesRead, NULL);

    /* General error check */
    if (status == FALSE)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    /* Retrieve Comm-Status */
    status = ClearCommError(pDataParams->pComHandle, &dwErrors, &abComstat);

    /* General error check */
    if (status == FALSE)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    /* Buffer overflow check */
    if (abComstat.cbInQue > 0)
    {
        return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_BAL);
    }

    /* Check for timeout error */
    if (dwBytesRead == 0)
    {
        return PH_ADD_COMPCODE(PH_ERR_IO_TIMEOUT, PH_COMP_BAL);
    }

    /* Return received length */
    *pRxLength = (uint16_t)dwBytesRead;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
    /* satisfy compiler */
    if (pDataParams || pTxBuffer || wTxLength || wRxBufSize || pRxBuffer || pRxLength);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_SerialWin_SetConfig(
                                        phbalReg_SerialWin_DataParams_t * pDataParams,
                                        uint16_t wConfig,
                                        uint16_t wValue
                                        )
{
#ifdef _WIN32
    phStatus_t PH_MEMLOC_REM statusTmp;

    switch (wConfig)
    {
        /* set a new bit rate rate */
    case PHBAL_REG_SERIALWIN_CONFIG_BITRATE:
        {
            switch (wValue)
            {
            case PHBAL_REG_SERIALWIN_VALUE_BITRATE_9600:
                pDataParams->dwBitRate = 9600;
                break;
            case PHBAL_REG_SERIALWIN_VALUE_BITRATE_19200:
                pDataParams->dwBitRate = 19200;
                break;
            case PHBAL_REG_SERIALWIN_VALUE_BITRATE_38400:
                pDataParams->dwBitRate = 38400;
                break;
            case PHBAL_REG_SERIALWIN_VALUE_BITRATE_57600:
                pDataParams->dwBitRate = 57600;
                break;
            case PHBAL_REG_SERIALWIN_VALUE_BITRATE_115200:
                pDataParams->dwBitRate = 115200;
                break;
            case PHBAL_REG_SERIALWIN_VALUE_BITRATE_230400:
                pDataParams->dwBitRate = 230400;
                break;
            case PHBAL_REG_SERIALWIN_VALUE_BITRATE_460800:
                pDataParams->dwBitRate = 460800;
                break;
            default:
                return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_BAL);
            }

            /* set bit rate */
            PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_SerialWin_SetMode(pDataParams->pComHandle, pDataParams->dwBitRate, pDataParams->bStopBits));

            break;
        }

        /* set a new bit rate rate */
    case PHBAL_REG_SERIALWIN_CONFIG_STOPBITS:
        {
            switch (wValue)
            {
            case PHBAL_REG_SERIALWIN_VALUE_STOPBITS_ONE:
                pDataParams->bStopBits = ONESTOPBIT;
                break;

            case PHBAL_REG_SERIALWIN_VALUE_STOPBITS_ONE5:
                pDataParams->bStopBits = ONE5STOPBITS;
                break;

            case PHBAL_REG_SERIALWIN_VALUE_STOPBITS_TWO:
                pDataParams->bStopBits = TWOSTOPBITS;
                break;

            default:
                return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_BAL);
            }

            /* set bit rate */
            PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_SerialWin_SetMode(pDataParams->pComHandle, pDataParams->dwBitRate, pDataParams->bStopBits));

            break;
        }

        /* set the communication timeout */
    case PHBAL_REG_CONFIG_WRITE_TIMEOUT_MS:
    case PHBAL_REG_CONFIG_READ_TIMEOUT_MS:
        {
            pDataParams->wTimeout = wValue;
            if (pDataParams->pComHandle != NULL)
            {
                PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_SerialWin_SetTimeout(pDataParams->pComHandle, (uint32_t)pDataParams->wTimeout));
            }
            break;
        }
        /* configuration parameter not available */
    default:
        {
            return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_BAL);
        }
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
    /* satisfy compiler */
    if (pDataParams || wConfig || wValue);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_SerialWin_GetConfig(
                                        phbalReg_SerialWin_DataParams_t * pDataParams,
                                        uint16_t wConfig,
                                        uint16_t * pValue
                                        )
{
#ifdef _WIN32
    switch (wConfig)
    {
    case PHBAL_REG_SERIALWIN_CONFIG_BITRATE:
        {
            switch (pDataParams->dwBitRate)
            {
            case 9600:
                *pValue = PHBAL_REG_SERIALWIN_VALUE_BITRATE_9600;
                break;
            case 19200:
                *pValue = PHBAL_REG_SERIALWIN_VALUE_BITRATE_19200;
                break;
            case 38400:
                *pValue = PHBAL_REG_SERIALWIN_VALUE_BITRATE_38400;
                break;
            case 57600:
                *pValue = PHBAL_REG_SERIALWIN_VALUE_BITRATE_57600;
                break;
            case 115200:
                *pValue = PHBAL_REG_SERIALWIN_VALUE_BITRATE_115200;
                break;
            case 230400:
                *pValue = PHBAL_REG_SERIALWIN_VALUE_BITRATE_230400;
                break;
            case 460800:
                *pValue = PHBAL_REG_SERIALWIN_VALUE_BITRATE_460800;
                break;
            default:
                return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_BAL);
            }
            break;
        }

    case PHBAL_REG_SERIALWIN_CONFIG_STOPBITS:
        {
            switch (pDataParams->bStopBits)
            {
            case ONESTOPBIT:
                *pValue = PHBAL_REG_SERIALWIN_VALUE_STOPBITS_ONE;
                break;

            case ONE5STOPBITS:
                *pValue = PHBAL_REG_SERIALWIN_VALUE_STOPBITS_ONE5;
                break;

            case TWOSTOPBITS:
                *pValue = PHBAL_REG_SERIALWIN_VALUE_STOPBITS_TWO;
                break;

            default:
                return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_BAL);
            }
            break;
        }
    case PHBAL_REG_CONFIG_WRITE_TIMEOUT_MS:
    case PHBAL_REG_CONFIG_READ_TIMEOUT_MS:
        {
            *pValue = pDataParams->wTimeout;
            break;
        }
        /* configuration parameter not available */
    default:
        {
            return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_BAL);
        }
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
    /* satisfy compiler */
    if (pDataParams || wConfig || pValue);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_SerialWin_SetMode(
                                      void * phPort,
                                      uint32_t dwBitRate,
                                      uint8_t bStopBits
                                      )
{
#ifdef _WIN32
    DCB PH_MEMLOC_BUF dcb;

    /* Prepare CDB structure */
    SecureZeroMemory(&dcb, sizeof(DCB));  /* PRQA S 3200 */
    dcb.DCBlength = sizeof(DCB);
    dcb.BaudRate = dwBitRate;
    dcb.fBinary = TRUE;
    dcb.fParity = FALSE;
    dcb.fOutxCtsFlow = FALSE;
    dcb.fOutxDsrFlow = FALSE;
    dcb.fDtrControl = DTR_CONTROL_DISABLE;
    dcb.fDsrSensitivity = FALSE;
    dcb.fTXContinueOnXoff = TRUE;
    dcb.fOutX = FALSE;
    dcb.fInX = FALSE;
    dcb.fErrorChar = FALSE;
    dcb.fNull = FALSE; 
    dcb.fRtsControl = RTS_CONTROL_DISABLE; 
    dcb.fAbortOnError = FALSE;
    dcb.XonLim = 0; 
    dcb.XoffLim = 0;  
    dcb.ByteSize = 8; 
    dcb.Parity = NOPARITY; 
    dcb.StopBits = bStopBits;

    /* Apply the settings */
    if (SetCommState(phPort, &dcb) == FALSE)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    /* Set DTR, some boards needs a DTR = 1 level */
    if (EscapeCommFunction(phPort, SETDTR) == FALSE)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
    /* satisfy compiler */
    if (phPort || dwBitRate);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_SerialWin_SetTimeout(
    void * phPort,
    uint32_t dwTimeout
    )
{
#ifdef _WIN32
    COMMTIMEOUTS PH_MEMLOC_BUF cto;

    /* Prepare CTO structure */
    cto.ReadTotalTimeoutConstant = dwTimeout;
    cto.ReadTotalTimeoutMultiplier = 0;
    cto.ReadIntervalTimeout = 10;
    cto.WriteTotalTimeoutConstant = 0;
    cto.WriteTotalTimeoutMultiplier = 0;

    /* Apply timeouts */
    if (SetCommTimeouts(phPort, &cto) == FALSE)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
    /* satisfy compiler */
    if (phPort || dwTimeout);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

#endif /* NXPBUILD__PHBAL_REG_SERIALWIN */
