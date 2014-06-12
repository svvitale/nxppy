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
* Internal functions of Software implementation of MIFARE (R) Ultralight application layer.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:26:24 2011 $
*
* History:
*  CHu: Generated 25. November 2009
*
*/

#include <ph_Status.h>
#include <phpalMifare.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHAL_MFUL

#include <phalMful.h>
#include "phalMful_Int.h"

phStatus_t phalMful_Int_Read(
                             void * pPalMifareDataParams,
                             uint8_t bAddress,
                             uint8_t * pData
                             )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bCommand[2];
    uint8_t *   PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;

    /* build command frame */
    bCommand[0] = PHAL_MFUL_CMD_READ;
    bCommand[1] = bAddress;

    /* transmit the command frame */
    PH_CHECK_SUCCESS_FCT(statusTmp, phpalMifare_ExchangeL3(
        pPalMifareDataParams,
        PH_EXCHANGE_DEFAULT,
        bCommand,
        2,
        &pRxBuffer,
        &wRxLength
        ));

    /* check received length */
    if (wRxLength != PHAL_MFUL_READ_BLOCK_LENGTH)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_AL_MFUL);
    }

    /* copy received data block */
    memcpy(pData, pRxBuffer, wRxLength);  /* PRQA S 3200 */

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_AL_MFUL); 
}

phStatus_t phalMful_Int_Write(
                              void * pPalMifareDataParams,
                              uint8_t bAddress,
                              uint8_t * pData
                              )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bCommand[2];
    uint8_t *   PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;

    /* build command frame */
    bCommand[0] = PHAL_MFUL_CMD_WRITE;
    bCommand[1] = bAddress;

    /* buffer the command frame */
    PH_CHECK_SUCCESS_FCT(statusTmp, phpalMifare_ExchangeL3(
        pPalMifareDataParams,
        PH_EXCHANGE_BUFFER_FIRST,
        bCommand,
        2,
        &pRxBuffer,
        &wRxLength
        ));

    /* transmit the data */
    PH_CHECK_SUCCESS_FCT(statusTmp, phpalMifare_ExchangeL3(
        pPalMifareDataParams,
        PH_EXCHANGE_BUFFER_LAST,
        pData,
        PHAL_MFUL_WRITE_BLOCK_LENGTH,
        &pRxBuffer,
        &wRxLength
        ));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_AL_MFUL);
}

phStatus_t phalMful_Int_CompatibilityWrite(
    void * pPalMifareDataParams,
    uint8_t bAddress,
    uint8_t * pData
    )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bCommand[2];
    uint8_t *   PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;

    /* build command frame */
    bCommand[0] = PHAL_MFUL_CMD_COMPWRITE;
    bCommand[1] = bAddress;

    /* send the first part */
    status = phpalMifare_ExchangeL3(
        pPalMifareDataParams,
        PH_EXCHANGE_DEFAULT,
        bCommand,
        2,
        &pRxBuffer,
        &wRxLength);

    /* Either ACK (newer UL cards) or TO (older UL cards) is expected */
    if ((status & PH_ERR_MASK) != PH_ERR_IO_TIMEOUT)
    {
        PH_CHECK_SUCCESS(status);
    }

    /* buffer the data */
    PH_CHECK_SUCCESS_FCT(statusTmp, phpalMifare_ExchangeL3(
        pPalMifareDataParams,
        PH_EXCHANGE_DEFAULT,
        pData,
        PHAL_MFUL_COMPWRITE_BLOCK_LENGTH,
        &pRxBuffer,
        &wRxLength));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_AL_MFUL);
}

#endif /* NXPBUILD__PHAL_MFUL */
