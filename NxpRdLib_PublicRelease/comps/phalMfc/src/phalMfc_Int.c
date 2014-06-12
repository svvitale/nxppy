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
* Internal functions for MIFARE (R) application layer.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:27:41 2011 $
*
* History:
*  CHu: Generated 05. November 2009
*
*/

#include <ph_Status.h>
#include <phhalHw.h>
#include <phalMfc.h>
#include "phalMfc_Int.h"
#include <phpalMifare.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHAL_MFC

phStatus_t phalMfc_Int_Transfer(
                                void * pPalMifareDataParams,
                                uint8_t bBlockNo
                                )
{
    uint8_t     PH_MEMLOC_REM aCommand[2];
    uint8_t *   PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;

    /* build command frame */
    aCommand[0] = PHAL_MFC_CMD_TRANSFER;
    aCommand[1] = bBlockNo;

    /* transmit the command frame */
    return phpalMifare_ExchangeL3(
        pPalMifareDataParams,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        2,
        &pRxBuffer,
        &wRxLength
        );
}

phStatus_t phalMfc_Int_Value(
                             void * pPalMifareDataParams,
                             uint8_t bCmdCode,                                   
                             uint8_t bBlockNo,
                             uint8_t * pValue
                             )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM aCommand[2];
    uint8_t *   PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;

    /* build command frame */
    aCommand[0] = bCmdCode;
    aCommand[1] = bBlockNo;

    /* transmit the command frame (first part) */
    PH_CHECK_SUCCESS_FCT(statusTmp, phpalMifare_ExchangeL3(
        pPalMifareDataParams,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        2,
        &pRxBuffer,
        &wRxLength
        ));

    /* transmit the data (second part) */
    status = phpalMifare_ExchangeL3(
        pPalMifareDataParams,
        PH_EXCHANGE_DEFAULT,
        pValue,
        PHAL_MFC_VALUE_BLOCK_LENGTH,
        &pRxBuffer,
        &wRxLength
        );

    /* there should be no response in case of successful operation */
    if ((status & PH_ERR_MASK) != PH_ERR_IO_TIMEOUT)
    {
        /* Resolve NAK Code */
        PH_CHECK_SUCCESS(status);

        /* ACK means protocol error */
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_AL_MFC);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_AL_MFC);
}

phStatus_t phalMfc_Int_CreateValueBlock(
                                        uint8_t * pValue,
                                        uint8_t bAddrData,
                                        uint8_t * pBlock
                                        )
{
    pBlock[0]  = (uint8_t)pValue[0];
    pBlock[1]  = (uint8_t)pValue[1]; 
    pBlock[2]  = (uint8_t)pValue[2];
    pBlock[3]  = (uint8_t)pValue[3];
    pBlock[4]  = (uint8_t)~(uint8_t)pValue[0];
    pBlock[5]  = (uint8_t)~(uint8_t)pValue[1];
    pBlock[6]  = (uint8_t)~(uint8_t)pValue[2];
    pBlock[7]  = (uint8_t)~(uint8_t)pValue[3];
    pBlock[8]  = (uint8_t)pValue[0];
    pBlock[9]  = (uint8_t)pValue[1];
    pBlock[10] = (uint8_t)pValue[2];
    pBlock[11] = (uint8_t)pValue[3];
    pBlock[12] = (uint8_t)bAddrData;
    pBlock[13] = (uint8_t)~(uint8_t)bAddrData;
    pBlock[14] = (uint8_t)bAddrData;
    pBlock[15] = (uint8_t)~(uint8_t)bAddrData;
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_AL_MFP);
}

phStatus_t phalMfc_Int_CheckValueBlockFormat(
    uint8_t * pBlock
    )
{
    /* check format of value block */
    if ((pBlock[0] != pBlock[8]) ||
        (pBlock[1] != pBlock[9]) ||
        (pBlock[2] != pBlock[10]) ||
        (pBlock[3] != pBlock[11]) ||
        (pBlock[4] != (pBlock[0] ^ 0xFF)) ||
        (pBlock[5] != (pBlock[1] ^ 0xFF)) ||
        (pBlock[6] != (pBlock[2] ^ 0xFF)) ||
        (pBlock[7] != (pBlock[3] ^ 0xFF)) ||
        (pBlock[12] != pBlock[14]) ||
        (pBlock[13] != pBlock[15]) ||
        (pBlock[12] != (pBlock[13]^ 0xFF)))
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_AL_MFP);
    }
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_AL_MFP);
}

phStatus_t phalMfc_Int_ResolveReturnCode(
    uint8_t bRetCode
    )
{
    switch(bRetCode)
    {
    case PHAL_MFC_RESP_ACK:
        return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_AL_MFC);
    case PHAL_MFC_RESP_NAK0:
        return PH_ADD_COMPCODE(PHPAL_MIFARE_ERR_NAK0, PH_COMP_PAL_MIFARE);
    case PHAL_MFC_RESP_NAK1:
        return PH_ADD_COMPCODE(PHPAL_MIFARE_ERR_NAK1, PH_COMP_PAL_MIFARE);
    case PHAL_MFC_RESP_NAK4:
        return PH_ADD_COMPCODE(PHPAL_MIFARE_ERR_NAK4, PH_COMP_PAL_MIFARE);
    case PHAL_MFC_RESP_NAK5:
        return PH_ADD_COMPCODE(PHPAL_MIFARE_ERR_NAK5, PH_COMP_PAL_MIFARE);
    default:
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_AL_MFC);
    }
}

#endif /* NXPBUILD__PHAL_MFC */
