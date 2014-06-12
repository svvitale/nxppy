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
* Stub MIFARE(R) Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:26:50 2011 $
*
* History:
*  CHu: Generated 21. October 2009
*
*/

#include <ph_Status.h>
#include <phhalHw.h>
#include <phpalMifare.h>
#include <ph_RefDefs.h>
#include <phTools.h>

#ifdef NXPBUILD__PHPAL_MIFARE_STUB

#include "phpalMifare_Stub.h"
#include "../phpalMifare_Int.h"

phStatus_t phpalMifare_Stub_Init(
                                 phpalMifare_Stub_DataParams_t * pDataParams,
                                 uint16_t wSizeOfDataParams
                                 )
{
    if (sizeof(phpalMifare_Stub_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_MIFARE);
    }
	PH_ASSERT_NULL (pDataParams);

    /* init private data */
    pDataParams->wId                 = PH_COMP_PAL_MIFARE | PHPAL_MIFARE_STUB_ID;

    /* TODO: Replace and insert initialisation code here */
    pDataParams = NULL;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_MIFARE);
}

phStatus_t phpalMifare_Stub_ExchangeL3(
                                       phpalMifare_Stub_DataParams_t * pDataParams,
                                       uint16_t wOption,
                                       uint8_t * pTxBuffer,
                                       uint16_t wTxLength,
                                       uint8_t ** ppRxBuffer,
                                       uint16_t * pRxLength
                                       )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t    PH_MEMLOC_REM wCrcIn;
    uint16_t    PH_MEMLOC_REM wCrcCalc;

    /* satisfy compiler */
    pDataParams = NULL;
    pTxBuffer = NULL;
    wTxLength = 0;
    status = 0;

    /* Switch CRC modes in case of first part of exchange. */
    if (!(wOption & PH_EXCHANGE_LEAVE_BUFFER_BIT))
    {
        /* TODO: Enable TxCrc, Disable RxCrc */
    }

    /* TODO: Perform Exchange */

    /* Return if no real exchange is done */
    if (wOption & PH_EXCHANGE_BUFFERED_BIT)
    {
        return status;
    }

    /* ACK/NAK Handling if we received exactly 4 bits*/
    {
        /* ACK/NAK Mapping */
        switch ((*ppRxBuffer)[0])
        {
            /* ACK -> everything OK */
        case PHPAL_MIFARE_RESP_ACK:
            status = PH_ERR_SUCCESS;
            break;
            /* Mapping of NAK codes: */
        case PHPAL_MIFARE_RESP_NAK0:
            status = PHPAL_MIFARE_ERR_NAK0;
            break;
        case PHPAL_MIFARE_RESP_NAK1:
            status = PHPAL_MIFARE_ERR_NAK1;
            break;
        case PHPAL_MIFARE_RESP_NAK4:
            status = PHPAL_MIFARE_ERR_NAK4;
            break;
        case PHPAL_MIFARE_RESP_NAK5:
            status = PHPAL_MIFARE_ERR_NAK5;
            break;
        default:
            status = PH_ERR_PROTOCOL_ERROR;
            break;
        }
    }
    /* Normal data stream with CRC */
    {
        /* TODO: Check for success */

        /* TODO: Check if bitcount indicates no incomplete byte */

        /* Retrieve CRC */
        wCrcIn  = (uint16_t)(((uint16_t)(*ppRxBuffer)[(*pRxLength) - 1]) << 8);
        wCrcIn |= (uint16_t)((*ppRxBuffer)[(*pRxLength) - 2]);

        /* Remove CRC from input data */
        *pRxLength -= 2;

        /* Calculate CRC */
        PH_CHECK_SUCCESS_FCT(statusTmp, phTools_CalculateCrc16(
            PH_TOOLS_CRC_OPTION_DEFAULT,
            PH_TOOLS_CRC16_PRESET_ISO14443A,
            PH_TOOLS_CRC16_POLY_ISO14443,
            *ppRxBuffer, 
            *pRxLength, 
            &wCrcCalc));

        /* CRC Check -> Compare input and calculated crc */
        if (wCrcIn == wCrcCalc)
        {
            status = PH_ERR_SUCCESS;
        }
        else
        {
            status = PH_ERR_INTEGRITY_ERROR;
        }
    }

    return PH_ADD_COMPCODE(status, PH_COMP_PAL_MIFARE);
}

phStatus_t phpalMifare_Stub_ExchangeL4(
                                       phpalMifare_Stub_DataParams_t * pDataParams,
                                       uint16_t wOption,
                                       uint8_t * pTxBuffer,
                                       uint16_t wTxLength,
                                       uint8_t ** ppRxBuffer,
                                       uint16_t * pRxLength
                                       )
{
#ifdef NXPBUILD__PHPAL_I14443P4

    /* satisfy compiler */
    pDataParams = NULL;
    wOption = 0;
    pTxBuffer = NULL;
    wTxLength = 0;
    ppRxBuffer = NULL;
    pRxLength = NULL;

    /* TODO: Enable TxCrc, Enable RxCrc  */

    /* TODO: Perform Exchange */

    /* TODO: Check for success */

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_MIFARE);
#else
    /* satisfy compiler */
    if (pDataParams || wOption || pTxBuffer || wTxLength || ppRxBuffer || pRxLength);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_PAL_MIFARE);
#endif
}

phStatus_t phpalMifare_Stub_ExchangePc(
                                       phpalMifare_Stub_DataParams_t * pDataParams,
                                       uint16_t wOption,
                                       uint8_t * pTxBuffer,
                                       uint16_t wTxLength,
                                       uint8_t ** ppRxBuffer,
                                       uint16_t * pRxLength
                                       )
{
#ifdef NXPBUILD__PHPAL_I14443P4
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bIsoFrame[3];
    uint16_t    PH_MEMLOC_REM wIsoFrameLen;
    uint16_t    PH_MEMLOC_REM wBlockNo;
    uint16_t    PH_MEMLOC_REM wCidConfig;
    uint16_t    PH_MEMLOC_REM wNadConfig;
    uint16_t    PH_MEMLOC_REM wCrcIn;
    uint16_t    PH_MEMLOC_REM wCrcCalc;

    /* satisfy compiler */
    pDataParams = NULL;
    wBlockNo = 0;
    wCidConfig = 0;
    wNadConfig = 0;

    /* Ignore wOption byte */
    wOption = PH_EXCHANGE_DEFAULT;

    /* TODO: Disable TxCrc, Disable RxCrc */

    /* TODO: Retrieve ISO 14443-4 Protocol Parameters */

    /* Build ISO 14443-4 I-Block Frame */
    bIsoFrame[0] = (uint8_t)(0x02 | wBlockNo);
    wIsoFrameLen = 1;

    /* Append CID if needed */
    {
        bIsoFrame[0] |= 0x08;
        bIsoFrame[wIsoFrameLen++] = (uint8_t)(wCidConfig & 0x00FF);
    }

    /* Append NAD if needed */
    {
        bIsoFrame[0] |= 0x04;
        bIsoFrame[wIsoFrameLen++] = (uint8_t)(wNadConfig & 0x00FF);
    }

    /* Calculate CRC over the frame */
    PH_CHECK_SUCCESS_FCT(statusTmp, phTools_CalculateCrc16(
        PH_TOOLS_CRC_OPTION_DEFAULT,
        PH_TOOLS_CRC16_PRESET_ISO14443A,
        PH_TOOLS_CRC16_POLY_ISO14443,
        bIsoFrame, 
        wIsoFrameLen, 
        &wCrcCalc));

    /* Calculate CRC over the data to send */
    PH_CHECK_SUCCESS_FCT(statusTmp, phTools_CalculateCrc16(
        PH_TOOLS_CRC_OPTION_DEFAULT,
        wCrcCalc,
        PH_TOOLS_CRC16_POLY_ISO14443,
        pTxBuffer, 
        wTxLength, 
        &wCrcCalc));

    /* TODO: Preload the frame */

    /* TODO: Perform Exchange */

    /* TODO: Check for success */

    /* Response length check */
    if (*pRxLength < 2)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_MIFARE);
    }

    /* Retrieve CRC */
    wCrcIn  = (uint16_t)(((uint16_t)(*ppRxBuffer)[(*pRxLength) - 1]) << 8);
    wCrcIn |= (uint16_t)((*ppRxBuffer)[(*pRxLength) - 2]);

    /* Remove CRC from input data */
    *pRxLength -= 2;

    /* Calculate CRC over the received data */
    PH_CHECK_SUCCESS_FCT(statusTmp, phTools_CalculateCrc16(
        PH_TOOLS_CRC_OPTION_DEFAULT,
        wCrcCalc,
        PH_TOOLS_CRC16_POLY_ISO14443,
        *ppRxBuffer, 
        *pRxLength, 
        &wCrcCalc));

    /* CRC Check -> Compare input and calculated crc */
    if (wCrcIn != wCrcCalc)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTEGRITY_ERROR, PH_COMP_PAL_MIFARE);
    }

    /* TODO: Update ISO14443-4 Block Number */

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_MIFARE);
#else
    /* satisfy compiler */
    if (pDataParams || wOption || pTxBuffer || wTxLength || ppRxBuffer || pRxLength);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_PAL_MIFARE);
#endif
}

phStatus_t phpalMifare_Stub_ExchangeRaw(
                                        phpalMifare_Stub_DataParams_t * pDataParams,
                                        uint16_t wOption,
                                        uint8_t * pTxBuffer,
                                        uint16_t wTxLength,
                                        uint8_t bTxLastBits,
                                        uint8_t ** ppRxBuffer,
                                        uint16_t * pRxLength,
                                        uint8_t * pRxLastBits
                                        )
{
    phStatus_t PH_MEMLOC_REM status = PH_ERR_SUCCESS;

    /* satisfy compiler */
    if (pDataParams || pTxBuffer || wTxLength || bTxLastBits || ppRxBuffer || pRxLength || pRxLastBits); 

    /* Do not switch Parity / CRC modes if no real exchange is done */
    if (!(wOption & PH_EXCHANGE_BUFFERED_BIT))
    {
        /* TODO: Disable Parity */

        /* TODO: Disable TxCrc, Disable RxCrc  */

        /* TODO: Set TxLastBits */
    }

    /* TODO: Perform Exchange */

    /* Return if no real exchange is done */
    if (wOption & PH_EXCHANGE_BUFFERED_BIT)
    {
        return status;
    }

    /* TODO: Restore Parity-setting again since many PAL layers expect it */

    /* TODO: Retrieve and return RxLastBits */

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_MIFARE);
}

phStatus_t phpalMifare_Stub_MfcAuthenticateKeyNo(
    phpalMifare_Stub_DataParams_t * pDataParams,
    uint8_t bBlockNo,
    uint8_t bKeyType,
    uint16_t wKeyNo,
    uint16_t wKeyVersion,
    uint8_t * pUid
    )
{
    /* satisfy compiler */
    if (pDataParams || bBlockNo || bKeyType || wKeyNo || wKeyVersion || pUid);

    /* TODO : Authenticate to card (a one-to-one mapping to phhalHw_MfcAuthenticateKeyNo is preferred here!) */

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_MIFARE);
}

phStatus_t phpalMifare_Stub_MfcAuthenticate(
    phpalMifare_Stub_DataParams_t * pDataParams,
    uint8_t bBlockNo,
    uint8_t bKeyType,
    uint8_t * pKey,
    uint8_t * pUid
    )
{
    /* satisfy compiler */
    if (pDataParams || bBlockNo || bKeyType || pKey || pUid);

    /* TODO : Authenticate to card (a one-to-one mapping to phhalHw_MfcAuthenticateKeyNo is preferred here!) */

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_MIFARE);
}

#endif /* NXPBUILD__PHPAL_MIFARE_STUB */
