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
* PCSC (Windows) BAL Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.5 $
* $Date: Fri Apr 15 16:07:05 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#include <ph_Status.h>
#include <phbalReg.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHBAL_REG_PCSCWIN

#include "phbalReg_PcscWin.h"
#include "phbalReg_PcscWin_Int.h"

phStatus_t phbalReg_PcscWin_Init(
                                 phbalReg_PcscWin_DataParams_t * pDataParams,
                                 uint16_t wSizeOfDataParams,
                                 uint8_t * pAtrBuffer,
                                 uint16_t wAtrBufSize
                                 )
{
    if (sizeof(phbalReg_PcscWin_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);
    }
    /* Verify ATR buffer */
    if (wAtrBufSize == 0)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_BAL);
    }
	PH_ASSERT_NULL (pDataParams);
    PH_ASSERT_NULL (pAtrBuffer);

    /* initialize the data parameters to default values */
    pDataParams->wId            = PH_COMP_BAL |PHBAL_REG_PCSCWIN_ID;
    pDataParams->bProtocolType  = PHBAL_REG_PCSCWIN_VALUE_PROTOCOL_T1;
    pDataParams->bShare         = PHBAL_REG_PCSCWIN_VALUE_SHARE_EXCLUSIVE;
    pDataParams->pAtrBuffer     = pAtrBuffer;
    pDataParams->wAtrBufSize    = wAtrBufSize;
    pDataParams->hContext       = NULL;
    pDataParams->hCard          = NULL;
    pDataParams->pReaderName    = NULL;

    /* Reset ATR length */
    pDataParams->pAtrBuffer[0] = 0x00;

#ifdef _WIN32
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_PcscWin_GetPortList(
    phbalReg_PcscWin_DataParams_t * pDataParams,
    uint16_t wPortBufSize,
    uint8_t * pPortNames,
    uint16_t * pNumOfPorts
    )
{
#ifdef _WIN32
    LONG    PH_MEMLOC_REM status;
    DWORD   PH_MEMLOC_REM dwReaderListLen;
    LPSTR   PH_MEMLOC_REM pReaderList;
    LPSTR   PH_MEMLOC_REM pReaderListTmp;
    uint16_t PH_MEMLOC_REM i;
    SCARDCONTEXT PH_MEMLOC_REM hContext;

    /* satisfy compiler */
    if (pDataParams);

    *pNumOfPorts = 0;

    /* Establish connection to SmartCard Context */
    status = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &hContext);
    if (status != SCARD_S_SUCCESS)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    /* Force auto allocation of reader list */
    dwReaderListLen = (uint32_t)SCARD_AUTOALLOCATE;

    /* Retrieve the reader-list */
    status = SCardListReadersA(hContext, NULL, (LPSTR)&pReaderList, &dwReaderListLen);
    if (status != SCARD_S_SUCCESS)
    {
        /* Release the resource manager context. */
        status = SCardReleaseContext(hContext);
        if (status != SCARD_S_SUCCESS)
        {
            return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_BAL);
        }
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    /* Check for buffer overflow */
    if (dwReaderListLen > wPortBufSize)
    {
        return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_BAL);
    }

    /* copy the reader nymes into the port buffer */
    pReaderListTmp = pReaderList;
    while (*pReaderListTmp != 0x00)
    {
        /* get the string length including the '\0' character of the actual reader name */
        i = (uint16_t)strlen(pReaderListTmp) + 1;
        /* copy the found reader name */
        memcpy(pPortNames, pReaderListTmp, i);  /* PRQA S 3200 */
        /* go to the next string */
        pPortNames += i;
        pReaderListTmp += i;
        /* increase found reader counter */
        ++(*pNumOfPorts);
    }

    /* Release the memory block automatically allocated for the multi-string of readers. */
    status = SCardFreeMemory((hContext), pReaderList);
    if (status != SCARD_S_SUCCESS)
    {
        SCardReleaseContext(hContext);  /* PRQA S 3200 */
        return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_BAL);
    }

    /* Release the resource manager context. */
    status = SCardReleaseContext(hContext);
    if (status != SCARD_S_SUCCESS)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_BAL);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
    /* satisfy compiler */
    if (pDataParams || wPortBufSize || pPortNames || pNumOfPorts);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_PcscWin_SetPort(
                            phbalReg_PcscWin_DataParams_t * pDataParams,
                            uint8_t * pPortName
                            )
{
#ifdef _WIN32
    pDataParams->pReaderName = pPortName;
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
    /* satisfy compiler */
    if (pDataParams || pPortName);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_PcscWin_Exchange(
                                     phbalReg_PcscWin_DataParams_t * pDataParams,
                                     uint16_t wOption,
                                     uint8_t * pTxBuffer,
                                     uint16_t wTxLength,
                                     uint16_t wRxBufSize,
                                     uint8_t * pRxBuffer,
                                     uint16_t * pRxLength
                                     )
{
#ifdef _WIN32
    HRESULT             PH_MEMLOC_REM status;
    HRESULT             PH_MEMLOC_REM statusTmp;
    DWORD               PH_MEMLOC_REM dwControlCode;
    DWORD               PH_MEMLOC_REM dwExchangeLen;
    LPCSCARD_IO_REQUEST PH_MEMLOC_REM pIoRequest;

    /* Reset received length */
    *pRxLength = 0;

    /* Default Smartcard transaction */
    if (wOption == PH_EXCHANGE_DEFAULT)
    {
        /* begin transaction */
        statusTmp = SCardBeginTransaction((SCARDHANDLE)pDataParams->hCard);
        if (statusTmp != SCARD_S_SUCCESS)
        {
            return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
        }

        /* prepare exchange */
        dwExchangeLen = (DWORD)wRxBufSize;
        switch (pDataParams->bProtocolType)
        {
        case PHBAL_REG_PCSCWIN_VALUE_PROTOCOL_T0:
            pIoRequest = SCARD_PCI_T0;
            break;
        case PHBAL_REG_PCSCWIN_VALUE_PROTOCOL_T1:
            pIoRequest = SCARD_PCI_T1;
            break;
        case PHBAL_REG_PCSCWIN_VALUE_PROTOCOL_UNDEFINED:
        default:
            pIoRequest = NULL;
            break;
        }

        /* perform exchange */
        status = SCardTransmit(
            (SCARDHANDLE)pDataParams->hCard,
            pIoRequest,
            pTxBuffer,
            (DWORD)wTxLength,
            NULL,
            pRxBuffer,
            &dwExchangeLen);

        /* end transaction */
        statusTmp = SCardEndTransaction((SCARDHANDLE)pDataParams->hCard, SCARD_LEAVE_CARD);
        if (statusTmp != SCARD_S_SUCCESS)
        {
            return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
        }
    }
    /* SCardControl mode */
    else if (wOption == PHBAL_REG_PCSCWIN_OPTION_SCARDCONTROL)
    {
        /* TxLength must be min. 4 bytes */
        if (wTxLength < 4)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_BAL);
        }

        /* Parse Control-Code */
        dwControlCode = ((DWORD)pTxBuffer[0] << 24) | ((DWORD)pTxBuffer[1] << 16) | ((DWORD)pTxBuffer[2] << 8) | (DWORD)(pTxBuffer[3]);

        /* Advance buffer pointer and length */
        pTxBuffer = &pTxBuffer[4];
        wTxLength = wTxLength - 4;

        /* perform exchange */
        status = SCardControl(
            (SCARDHANDLE)pDataParams->hCard,
            dwControlCode,
            pTxBuffer,
            (DWORD)wTxLength,
            pRxBuffer,
            (DWORD)wRxBufSize,
            &dwExchangeLen);
    }
    /* Invalid option */
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_BAL);
    }

    /* Return-Code mapping */
    switch (status)
    {
    case SCARD_S_SUCCESS:                   /* PRQA S 274 */
        /* return the received length */
        *pRxLength = (uint16_t)dwExchangeLen;
        return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
    case SCARD_E_INSUFFICIENT_BUFFER:       /* PRQA S 274 */
    case ERROR_INSUFFICIENT_BUFFER:         /* PRQA S 274 */
    case SCARD_E_PCI_TOO_SMALL:             /* PRQA S 274 */
        return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_BAL);
    case SCARD_E_INVALID_PARAMETER:         /* PRQA S 274 */
    case SCARD_E_INVALID_VALUE:             /* PRQA S 274 */
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_BAL);
    case SCARD_F_WAITED_TOO_LONG:           /* PRQA S 274 */
    case SCARD_E_TIMEOUT:                   /* PRQA S 274 */
        return PH_ADD_COMPCODE(PH_ERR_IO_TIMEOUT, PH_COMP_BAL);
    case SCARD_E_SHARING_VIOLATION:         /* PRQA S 274 */
    case SCARD_E_NO_SMARTCARD:              /* PRQA S 274 */
    case SCARD_E_UNKNOWN_CARD:              /* PRQA S 274 */
    case SCARD_E_PROTO_MISMATCH:            /* PRQA S 274 */
    case SCARD_E_NOT_READY:                 /* PRQA S 274 */
    case SCARD_E_NOT_TRANSACTED:            /* PRQA S 274 */
    case SCARD_E_READER_UNAVAILABLE:        /* PRQA S 274 */
    case SCARD_E_READER_UNSUPPORTED:        /* PRQA S 274 */
    case SCARD_E_CARD_UNSUPPORTED:          /* PRQA S 274 */
    case SCARD_W_CARD_NOT_AUTHENTICATED:    /* PRQA S 274 */
        return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_BAL);
    default:
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

#else
    /* satisfy compiler */
    if (pDataParams || pTxBuffer || wTxLength || wRxBufSize || pRxBuffer || pRxLength);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_PcscWin_OpenPort(
                                     phbalReg_PcscWin_DataParams_t * pDataParams
                                     )
{
#ifdef _WIN32
    LONG        PH_MEMLOC_REM status;
    DWORD       PH_MEMLOC_REM dwShareMode;
    DWORD       PH_MEMLOC_REM dwProtocol;
    DWORD       PH_MEMLOC_REM dwActiveProtocol;
    DWORD       PH_MEMLOC_REM dwAtrLen;
    uint8_t *   PH_MEMLOC_REM pReaderName;

    /* Port should be closed */
    if (pDataParams->hContext != NULL || pDataParams->hCard != NULL)
    {
        return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_BAL);
    }

    /* Reset ATR length */
    pDataParams->pAtrBuffer[0] = 0x00;

    /* establish smartcard context */
    status = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, (LPSCARDCONTEXT)&pDataParams->hContext);
    if (status != SCARD_S_SUCCESS)
    {
        pDataParams->hContext = NULL;
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    /* resolve share mode */
    switch(pDataParams->bShare)
    {
    case PHBAL_REG_PCSCWIN_VALUE_SHARE_SHARED:
        dwShareMode = SCARD_SHARE_SHARED;
        break;
    case PHBAL_REG_PCSCWIN_VALUE_SHARE_EXCLUSIVE:
        dwShareMode = SCARD_SHARE_EXCLUSIVE;
        break;
    case PHBAL_REG_PCSCWIN_VALUE_SHARE_DIRECT:
        dwShareMode = SCARD_SHARE_DIRECT;
        break;
    default:
        return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_BAL);
    }

    /* resolve communication protocol */
    switch(pDataParams->bProtocolType)
    {
    case PHBAL_REG_PCSCWIN_VALUE_PROTOCOL_T0:
        dwProtocol = SCARD_PROTOCOL_T0;
        break;
    case PHBAL_REG_PCSCWIN_VALUE_PROTOCOL_T1:
        dwProtocol = SCARD_PROTOCOL_T1;
        break;
    case PHBAL_REG_PCSCWIN_VALUE_PROTOCOL_UNDEFINED:
        dwProtocol = SCARD_PROTOCOL_UNDEFINED;
        break;
    default:
        return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_BAL);
    }

    /*  Try to connect to a card in the current reader. */
    status = SCardConnectA(
        (SCARDCONTEXT)pDataParams->hContext,
        (LPCSTR)pDataParams->pReaderName,
        dwShareMode,
        dwProtocol,
        (LPSCARDHANDLE)&pDataParams->hCard,
        &dwActiveProtocol);

    /* check status */
    if (status != SCARD_S_SUCCESS)
    {
        /* release the resource manager context. */
        status = SCardReleaseContext((SCARDCONTEXT)pDataParams->hContext);
        if (status != SCARD_S_SUCCESS)
        {
            pDataParams->hContext = NULL;
            pDataParams->hCard = NULL;
            return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_BAL);
        }
        pDataParams->hContext = NULL;
        pDataParams->hCard = NULL;
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    /* Obtain active protocol */
    switch (dwActiveProtocol)
    {
    case SCARD_PROTOCOL_T0:
        pDataParams->bProtocolType = PHBAL_REG_PCSCWIN_VALUE_PROTOCOL_T0;
        break;
    case SCARD_PROTOCOL_T1:
        pDataParams->bProtocolType = PHBAL_REG_PCSCWIN_VALUE_PROTOCOL_T1;
        break;
    case SCARD_PROTOCOL_UNDEFINED:
        pDataParams->bProtocolType = PHBAL_REG_PCSCWIN_VALUE_PROTOCOL_UNDEFINED;
        break;
    default:
        return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_BAL);
    }

    /* Retrieve ATR */
    pReaderName = NULL;
    dwShareMode = SCARD_AUTOALLOCATE;
    dwAtrLen = pDataParams->wAtrBufSize;
    status = SCardStatusA(
        (SCARDHANDLE)pDataParams->hCard,
        (LPTSTR)&pReaderName,
        &dwShareMode,
        &dwProtocol,
        &dwProtocol,
        (LPBYTE)pDataParams->pAtrBuffer,
        &dwAtrLen);

    /* check status */
    if (status != SCARD_S_SUCCESS)
    {
        /* Map buffer overflow */
        if (status == SCARD_E_INSUFFICIENT_BUFFER) /* PRQA S 274 */
        {
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_BAL);
        }
        /* Return interface error on other errors */
        else
        {
            return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
        }
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
    /* satisfy compiler */
    if (pDataParams);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_PcscWin_ClosePort(
                                      phbalReg_PcscWin_DataParams_t * pDataParams
                                      )
{
#ifdef _WIN32
    LONG PH_MEMLOC_REM status;

    /* Port should be open */
    if (pDataParams->hContext == NULL || pDataParams->hCard == NULL)
    {
        return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_BAL);
    }

    /* Reset ATR length */
    pDataParams->pAtrBuffer[0] = 0x00;

    /*  Disonnect from the card. */
    status = SCardDisconnect((SCARDHANDLE)pDataParams->hCard, SCARD_UNPOWER_CARD);
    if (status != SCARD_S_SUCCESS)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_BAL);
    }

    /*  Release the resource manager context. */
    status = SCardReleaseContext((SCARDCONTEXT)pDataParams->hContext);
    if (status != SCARD_S_SUCCESS)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_BAL);
    }

    pDataParams->hContext = NULL;
    pDataParams->hCard = NULL;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#else
    /* satisfy compiler */
    if (pDataParams);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_BAL);
#endif
}

phStatus_t phbalReg_PcscWin_SetConfig(
                                      phbalReg_PcscWin_DataParams_t * pDataParams,
                                      uint16_t wConfig,
                                      uint16_t wValue
                                      )
{
#ifdef _WIN32
    switch(wConfig)
    {
    case PHBAL_REG_PCSCWIN_CONFIG_SHARE:

        /* check parameter */
        if (wValue > PHBAL_REG_PCSCWIN_VALUE_SHARE_DIRECT)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_BAL);
        }

        /* store configuration*/
        pDataParams->bShare = (uint8_t)wValue;

        break;

    case PHBAL_REG_PCSCWIN_CONFIG_PROTOCOL:

        /* check parameter */
        if (wValue > PHBAL_REG_PCSCWIN_VALUE_PROTOCOL_UNDEFINED)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_BAL);
        }

        /* store configuration*/
        pDataParams->bProtocolType = (uint8_t)wValue;

        break;

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

phStatus_t phbalReg_PcscWin_GetConfig(
                                      phbalReg_PcscWin_DataParams_t * pDataParams,
                                      uint16_t wConfig,
                                      uint16_t * pValue
                                      )
{
#ifdef _WIN32
    switch(wConfig)
    {
    case PHBAL_REG_PCSCWIN_CONFIG_SHARE:
        *pValue = pDataParams->bShare;
        break;
    case PHBAL_REG_PCSCWIN_CONFIG_PROTOCOL:
        *pValue = pDataParams->bProtocolType;
        break;
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

#endif /* NXPBUILD__PHBAL_REG_PCSCWIN */
