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
* Software Felica Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.1 $
* $Date: Fri Apr 15 09:29:08 2011 $
*
* History:
*  RSn: Generated 26. January 2010
*
*/

#include <ph_Status.h>
#include <phhalHw.h>
#include <phpalFelica.h>
#include <ph_RefDefs.h>

#ifdef  NXPBUILD__PHPAL_FELICA_SW

#include "phpalFelica_Sw.h"
#include "phpalFelica_Sw_Int.h"

/* Table for 4^E evaluation (E is only 2 bits, so more values are not possible). */
static const uint8_t PH_MEMLOC_CONST_ROM aFelica_E_Table[] = {1, 4, 16, 64};

phStatus_t phpalFelica_Sw_Init(
                               phpalFelica_Sw_DataParams_t * pDataParams,
                               uint16_t wSizeOfDataParams,
                               void * pHalDataParams
                               )
{
    /* parameter structure length check */
    if (sizeof(phpalFelica_Sw_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_FELICA);
    }
    PH_ASSERT_NULL (pDataParams);
    PH_ASSERT_NULL (pHalDataParams);

    /* init private data */
    pDataParams->wId            = PH_COMP_PAL_FELICA | PHPAL_FELICA_SW_ID;
    pDataParams->pHalDataParams = pHalDataParams;
    pDataParams->bIDmPMmValid   = PHPAL_FELICA_SW_IDMPMM_INVALID;
    pDataParams->bLength        = 0x00;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_FELICA);
}

phStatus_t phpalFelica_Sw_ReqC(
                               phpalFelica_Sw_DataParams_t* pDataParams,
                               uint8_t * pSystemCode,
                               uint8_t  bNumTimeSlots,
                               uint8_t * pRxBuffer
                               )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM aCmd[6];
    uint8_t *   PH_MEMLOC_REM pRxBufferTmp;
    uint16_t    PH_MEMLOC_REM wRxLengthTmp;
    uint16_t    PH_MEMLOC_REM wTimeOutUs;

    /* reset validity of stored card IDs */
    pDataParams->bIDmPMmValid = PHPAL_FELICA_SW_IDMPMM_INVALID;

    /* parameter check and timeout setting */
    switch (bNumTimeSlots)
    {
    case PHPAL_FELICA_NUMSLOTS_1:
    case PHPAL_FELICA_NUMSLOTS_2:
    case PHPAL_FELICA_NUMSLOTS_4:
    case PHPAL_FELICA_NUMSLOTS_8:
    case PHPAL_FELICA_NUMSLOTS_16:
        wTimeOutUs = PHPAL_FELICA_SW_RESP_TIME_A_US + (bNumTimeSlots * PHPAL_FELICA_SW_RESP_TIME_B_US);
        break;
    default:
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_FELICA);
    }

    /* build the command frame */
    aCmd[0] = 6;
    aCmd[1] = PHPAL_FELICA_SW_CMD_REQC;
    aCmd[2] = pSystemCode[0];
    aCmd[3] = pSystemCode[1];
    aCmd[4] = 0x00; /* Reserved */
    aCmd[5] = bNumTimeSlots;

    /* Set ReqC timeout according to the number of slots */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,
        wTimeOutUs));

    /* Exchange command */
    status = phhalHw_Exchange(
        pDataParams->pHalDataParams,
        PH_EXCHANGE_DEFAULT,
        aCmd,
        6,
        &pRxBufferTmp,
        &wRxLengthTmp);

    /* Wait until all slots are finished if we did not wait the whole timeout */
    if ((status & PH_ERR_MASK) != PH_ERR_IO_TIMEOUT)
    {
        /* Only wait if we have timeslots left */
        if (bNumTimeSlots > 0)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Wait(
                pDataParams->pHalDataParams,
                PHHAL_HW_TIME_MICROSECONDS,
                ((bNumTimeSlots) * PHPAL_FELICA_SW_RESP_TIME_B_US)));
        }
    }

    /* Error check */
    PH_CHECK_SUCCESS(status);

    /* Check length */
    if ((wRxLengthTmp != (PHPAL_FELICA_ATQC_LENGTH + 1)) ||
        (pRxBufferTmp[0] != wRxLengthTmp) ||
        (pRxBufferTmp[1] != PHPAL_FELICA_SW_RSP_REQC))
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_FELICA);
    }

    /* Store IDm and PMm */
    memcpy(pDataParams->aIDmPMm, &pRxBufferTmp[2], (wRxLengthTmp - 2));  /* PRQA S 3200 */
    pDataParams->bIDmPMmValid = PHPAL_FELICA_SW_IDMPMM_VALID;

    /* Return IDm and PMm */
    memcpy(pRxBuffer, pDataParams->aIDmPMm, sizeof(pDataParams->aIDmPMm)); /* PRQA S 3200 */

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_FELICA);
}

phStatus_t phpalFelica_Sw_ActivateCard(
                                       phpalFelica_Sw_DataParams_t* pDataParams,
                                       uint8_t* pIDmPMm, 
                                       uint8_t bIDmPMmLength, 
                                       uint8_t * pSystemCode,
                                       uint8_t bNumTimeSlots,
                                       uint8_t * pRxBuffer,
                                       uint8_t * pRxLength,
                                       uint8_t * pMoreCardsAvailable
                                       )
{
    phStatus_t PH_MEMLOC_REM status;

    *pRxLength = 0;
    *pMoreCardsAvailable = 0;

    /* if serial number is given only store it */
    /* Note: Since the library doesn't support multi read, it is not possible to check, if a card
    with the given IDm PMm is currently in the field. */
    if (bIDmPMmLength)
    {
        /* check if IDm length is valid. */
        if (bIDmPMmLength != (PHPAL_FELICA_IDM_LENGTH + PHPAL_FELICA_PMM_LENGTH))
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_FELICA);
        }

        /* Store IDm/PMm */
        memcpy(pDataParams->aIDmPMm, pIDmPMm, bIDmPMmLength);  /* PRQA S 3200 */
        pDataParams->bIDmPMmValid = PHPAL_FELICA_SW_IDMPMM_VALID;

        return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_FELICA);
    }

    /* RequestC == ReqC command (not requesting the system code) */
    /* In the case of a collision repeat the ReqC up to 16 slots. */
    do
    {
        status = phpalFelica_Sw_ReqC(
            pDataParams,
            pSystemCode,
            bNumTimeSlots,
            pRxBuffer);

        if ((status & PH_ERR_MASK) != PH_ERR_COLLISION_ERROR)
        {
            if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
            {
                *pRxLength = PHPAL_FELICA_IDM_LENGTH + PHPAL_FELICA_PMM_LENGTH;
            }
            return status;
        }

        *pMoreCardsAvailable = 1;
        bNumTimeSlots = (bNumTimeSlots << 1) + 1;
    }
    while (bNumTimeSlots <= PHPAL_FELICA_NUMSLOTS_16);

    return status;
}

phStatus_t phpalFelica_Sw_Exchange(
                                   phpalFelica_Sw_DataParams_t* pDataParams,
                                   uint16_t wOption,
                                   uint16_t wN,
                                   uint8_t* pTxBuffer, 
                                   uint16_t wTxLength, 
                                   uint8_t ** ppRxBuffer, 
                                   uint16_t * pRxLength
                                   )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM aHeader[2];
    uint16_t    PH_MEMLOC_REM wCmd;
    uint32_t    PH_MEMLOC_REM dwTimeoutUs;
    uint8_t     PH_MEMLOC_REM bTparam;
    uint8_t     PH_MEMLOC_REM bA;
    uint8_t     PH_MEMLOC_REM bB;
    uint8_t     PH_MEMLOC_REM bE;
    uint8_t *   PH_MEMLOC_REM pPMm;

    /* [len][cmd] [IDm ... 8 bytes] [cmd parameters ...] */

    /* Check if we do have an IDm */
    if (pDataParams->bIDmPMmValid == PHPAL_FELICA_SW_IDMPMM_INVALID)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_FELICA);
    }

    /* Parameter check */
    if ((wTxLength + 2) > PHPAL_FELICA_TXLENGTH_MAX)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_FELICA);
    }

    /* If the PH_EXCHANGE_LEAVE_BUFFER_BIT is NOT set, wOption is:
    ~ PH_EXCHANGE_DEFAULT:      we have the command byte and eventually parameter bytes (data),
    how ever, we already have all data to exchange the complete frame.
    ~ PH_EXCHANGE_BUFFER_FIRST: we have the command byte and eventually parameter bytes (data),
    but the callee wants to transmit some more.
    pDataParams->bLength < 2 -> the cmd byte was not transmitted yet
    */
    if (!(wOption & PH_EXCHANGE_LEAVE_BUFFER_BIT) || (pDataParams->bLength < 2))
    {
        /* If there is nothing to transmit, we are done. */
        if (wTxLength == 0)
        {
            return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_FELICA);
        }

        /* Prepare header */
        aHeader[0] = 0x00;          /* This is just a dummy which is updated with the correct value later on,
                                    when the last chunk is ready to transmit. */
        aHeader[1] = pTxBuffer[0];

        /* Buffer the header */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Exchange(
            pDataParams->pHalDataParams,
            PH_EXCHANGE_BUFFER_FIRST,
            aHeader,
            2,
            ppRxBuffer,
            pRxLength));

        /* until now, we have transmitted 2 bytes: */
        pDataParams->bLength = 2;

        /* following Hw_Echange calls shall not overwrite already buffered data */
        wOption |= PH_EXCHANGE_LEAVE_BUFFER_BIT;

        /* Check if IDm has to be send */
        wCmd = (uint16_t)pTxBuffer[0];
        switch (wCmd)
        {
        case PHPAL_FELICA_SW_CMD_REQ_RESP:
        case PHPAL_FELICA_SW_CMD_REQ_SERVICE:
        case PHPAL_FELICA_SW_CMD_READ:
        case PHPAL_FELICA_SW_CMD_WRITE:
        case PHPAL_FELICA_SW_CMD_AUTH1:
        case PHPAL_FELICA_SW_CMD_AUTH2:

            /* If there is no more parameter bytes (data) to send, we adjust pointer and length
            for the LAST Exchange, the IDm */
            if (wTxLength == 1)
            {
                pTxBuffer = pDataParams->aIDmPMm;  
                wTxLength = PHPAL_FELICA_IDM_LENGTH;
            }
            else
            {
                /* Set pointer and length for the LAST exchange. */
                pTxBuffer = pTxBuffer + 1;
                wTxLength = wTxLength - 1;

                /* Transmit the IDm */
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Exchange(
                    pDataParams->pHalDataParams,
                    PH_EXCHANGE_BUFFER_CONT,
                    pDataParams->aIDmPMm,
                    PHPAL_FELICA_IDM_LENGTH,
                    ppRxBuffer,
                    pRxLength));

                pDataParams->bLength = pDataParams->bLength + PHPAL_FELICA_IDM_LENGTH;
            }

            break;
        default:

            /* Set pointer and length for the LAST exchange. */
            pTxBuffer = pTxBuffer + 1;
            wTxLength = wTxLength - 1;
            break;
        }
    }
    else
    {
        /* command byte already buffered */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_ADDITIONAL_INFO, 0x01));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_GetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_TXBUFFER, &wCmd));
    }

    /* Length check */
    if ((pDataParams->bLength + wTxLength) > PHPAL_FELICA_TXLENGTH_MAX)
    {
        return PH_ADD_COMPCODE(PH_ERR_LENGTH_ERROR, PH_COMP_PAL_FELICA);
    }

    /* If the PH_EXCHANGE_BUFFERED_BIT IS set, wOption is:
    ~ PH_EXCHANGE_BUFFER_FIRST, or
    ~ PH_EXCHANGE_BUFFER_CONT: This means that there is data which shall be put into the
    buffer but not to be sent yet since more data will follow. */
    if (wOption & PH_EXCHANGE_BUFFERED_BIT)
    {
        if (wTxLength > 0)
        {
            /* Exchange command */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Exchange(
                pDataParams->pHalDataParams,
                wOption,
                pTxBuffer,
                wTxLength,
                ppRxBuffer,
                pRxLength));

            pDataParams->bLength = pDataParams->bLength + (uint8_t)wTxLength;
        }

        return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_FELICA);
    }

    /* If the PH_EXCHANGE_BUFFERED_BIT is NOT set, wOption is:
    ~ PH_EXCHANGE_DEFAULT, or
    ~ PH_EXCHANGE_BUFFER_LAST: This means that either this is the last (or only) chunk
    of command parameters (data), which also could be of zero bytes.

    So this is the last chunk and we should received a response,
    which we extrakt the IDm bytes from and also check them. */
    pDataParams->bLength = pDataParams->bLength + (uint8_t)(wTxLength);

    /* Update the length byte which had been sent before */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_ADDITIONAL_INFO, 0x00));
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_TXBUFFER, (uint16_t)pDataParams->bLength));  

    /* Reset precached length */
    pDataParams->bLength = 0x00;

    /* Get stored PMm */
    pPMm = &pDataParams->aIDmPMm[PHPAL_FELICA_IDM_LENGTH];

    /* Command and PMm evaluation */
    switch(wCmd)
    {
    case PHPAL_FELICA_SW_CMD_REQ_SERVICE:
        bTparam = pPMm[2];
        break;
    case PHPAL_FELICA_SW_CMD_REQ_RESP:
        bTparam = pPMm[3];
        break;
    case PHPAL_FELICA_SW_CMD_AUTH1:
    case PHPAL_FELICA_SW_CMD_AUTH2:
        bTparam = pPMm[4];
        break;
    case PHPAL_FELICA_SW_CMD_READ:
    case PHPAL_FELICA_SW_CMD_READ_SECF:
        bTparam = pPMm[5];
        break;
    case PHPAL_FELICA_SW_CMD_WRITE:
    case PHPAL_FELICA_SW_CMD_WRITE_SECF:
        bTparam = pPMm[6];
        break;
    default:
        bTparam = pPMm[7];
        break;
    }

    /* Get timing parameters */
    bA = bTparam & 0x07;
    bB = (bTparam >> 3) & 0x07;
    bE = (bTparam >> 6) & 0x03;

    /* Timeout calculation */
    /* Response time = T x [(B + 1) x n + (A + 1)] x 4^E */
    dwTimeoutUs = PHPAL_FELICA_SW_TIME_T_US * ((bB + 1) * wN + (bA + 1)) * aFelica_E_Table[bE];

    /* Timeout setting in Milliseconds */
    if (dwTimeoutUs > 0xFFFF)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
            pDataParams->pHalDataParams,
            PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS,
            (uint16_t)(dwTimeoutUs / 1000)));
    }
    /* Timeout setting in Microseconds */
    else
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
            pDataParams->pHalDataParams,
            PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,
            (uint16_t)dwTimeoutUs));
    }

    /* Exchange command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Exchange(
        pDataParams->pHalDataParams,
        PH_EXCHANGE_BUFFER_LAST,
        pTxBuffer,
        wTxLength,
        ppRxBuffer,
        pRxLength));

    /* Check length */
    if ((*pRxLength < 1) || ((*ppRxBuffer)[0] != *pRxLength))
    {
        *pRxLength = 0;
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_FELICA);
    }

    /* Skip length */
    --(*pRxLength);
    ++(*ppRxBuffer);

    /* Check response code */
    if ((*pRxLength < 1) || ((*ppRxBuffer)[0] != (wCmd + 1)))
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_FELICA);
    }

    /* Skip response code */
    --(*pRxLength);
    ++(*ppRxBuffer);

    /* Check and skip IDm if received */
    switch (wCmd)
    {
    case PHPAL_FELICA_SW_CMD_REQ_RESP:
    case PHPAL_FELICA_SW_CMD_REQ_SERVICE:
    case PHPAL_FELICA_SW_CMD_READ:
    case PHPAL_FELICA_SW_CMD_WRITE:
    case PHPAL_FELICA_SW_CMD_AUTH1:

        /* Protocol error check */
        if (*pRxLength < PHPAL_FELICA_IDM_LENGTH)
        {
            return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_FELICA);
        }

        /* We can only check the IDm if we have a valid one stored */
        if (memcmp(*ppRxBuffer, pDataParams->aIDmPMm, PHPAL_FELICA_IDM_LENGTH) != 0)
        {
            return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_FELICA);
        }

        /* Skip IDm */
        *pRxLength = *pRxLength - PHPAL_FELICA_IDM_LENGTH;
        *ppRxBuffer = *ppRxBuffer + PHPAL_FELICA_IDM_LENGTH;
        break;
    default:
        break;
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_FELICA);
}

phStatus_t phpalFelica_Sw_GetSerialNo(
                                      phpalFelica_Sw_DataParams_t* pDataParams,
                                      uint8_t * pIDmPMmOut,
                                      uint8_t * pLenIDmPMmOut
                                      )
{
    /* Return an error if IDm and PMm are not valid */
    if (pDataParams->bIDmPMmValid == PHPAL_FELICA_SW_IDMPMM_INVALID)
    {
        *pLenIDmPMmOut = 0;
        return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_PAL_FELICA);
    }

    /* copy the IDm and PMm */
    memcpy(pIDmPMmOut, pDataParams->aIDmPMm, PHPAL_FELICA_IDM_LENGTH + PHPAL_FELICA_PMM_LENGTH); /* PRQA S 3200 */
    *pLenIDmPMmOut = PHPAL_FELICA_IDM_LENGTH + PHPAL_FELICA_PMM_LENGTH;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_FELICA);
}

#endif /* NXPBUILD__PHPAL_FELICA_SW */
