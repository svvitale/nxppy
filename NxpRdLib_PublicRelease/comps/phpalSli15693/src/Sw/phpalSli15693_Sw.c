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
* Software ISO14443-3A Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:26:55 2011 $
*
* History:
*  RSn: Generated 21. October 2009
*
*/

#include <ph_Status.h>
#include <phhalHw.h>
#include <phpalSli15693.h>
#include <ph_RefDefs.h>

#ifdef  NXPBUILD__PHPAL_SLI15693_SW

#include "phpalSli15693_Sw.h"
#include "phpalSli15693_Sw_Int.h"

phStatus_t phpalSli15693_Sw_Init(
                                 phpalSli15693_Sw_DataParams_t * pDataParams,
                                 uint16_t wSizeOfDataParams,
                                 void * pHalDataParams
                                 )
{
    PH_ASSERT_NULL (pDataParams);
    PH_ASSERT_NULL (pHalDataParams);

    /* parameter structure length check */
    if (sizeof(phpalSli15693_Sw_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_SLI15693);
    }

    /* init private data */
    pDataParams->wId                = PH_COMP_PAL_SLI15693 | PHPAL_SLI15693_SW_ID;
    pDataParams->pHalDataParams     = pHalDataParams;
    pDataParams->wAdditionalInfo    = 0;
    pDataParams->bFlags             = PHPAL_SLI15693_SW_FLAGS_DEFAULT;
    pDataParams->bUidBitLength      = 0;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_ISO14443P3B);
}

phStatus_t phpalSli15693_Sw_Inventory(
                                      phpalSli15693_Sw_DataParams_t * pDataParams,
                                      uint8_t bFlags,
                                      uint8_t bAfi,
                                      uint8_t * pMask,
                                      uint8_t bMaskBitLength,
                                      uint8_t * pDsfid,
                                      uint8_t * pUid
                                      )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bUidLength;
    uint16_t    PH_MEMLOC_REM wDataLength;

    PH_CHECK_SUCCESS_FCT(statusTmp, phpalSli15693_Sw_InventoryEx(
        pDataParams,
        PHPAL_SLI15693_SW_CMD_INVENTORY,
        bFlags,
        bAfi,
        pMask,
        bMaskBitLength,
        0,
        0,
        pUid,
        &bUidLength,
        pDsfid,
        &wDataLength));

    /* wait T2 */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Wait(
        pDataParams->pHalDataParams,
        PHHAL_HW_TIME_MICROSECONDS,
        PHPAL_SLI15693_SW_T2_WAITING_TIME));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_SLI15693);
}

phStatus_t phpalSli15693_Sw_SendEof(
                                    phpalSli15693_Sw_DataParams_t * pDataParams,
                                    uint8_t bOption,
                                    uint8_t * pDsfid,
                                    uint8_t * pUid,
                                    uint8_t * pUidLength,
                                    uint8_t * pData,
                                    uint16_t * pDataLength
                                    )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *   PH_MEMLOC_REM pResp;
    uint16_t    PH_MEMLOC_REM wRespLength;
    uint8_t     PH_MEMLOC_REM bStoredUidLength;

    /* Check bOption */
    switch (bOption)
    {
    case PHPAL_SLI15693_EOF_NEXT_SLOT:
    case PHPAL_SLI15693_EOF_NEXT_SLOT_INV_READ:
    case PHPAL_SLI15693_EOF_WRITE_ALIKE:
    case PHPAL_SLI15693_EOF_WRITE_ALIKE_WITH_WAIT:
        break;
    default:
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_SLI15693);
    }

    /* Reset UID and data lengths */
    *pDsfid = 0;
    *pUidLength = 0;
    *pDataLength = 0;

    /* if requested, wait ~20ms upon sending EOF */
    if (bOption == PHPAL_SLI15693_EOF_WRITE_ALIKE_WITH_WAIT)
    {
        /* in case of write alike commands wait 20 ms. */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Wait(
            pDataParams->pHalDataParams,
            PHHAL_HW_TIME_MICROSECONDS,
            PHPAL_SLI15693_TIMEOUT_LONG_US));
    }

    /* Set short timeout. */
    PH_CHECK_SUCCESS_FCT(statusTmp, phpalSli15693_SetConfig(
        pDataParams,
        PHPAL_SLI15693_CONFIG_TIMEOUT_US,
        PHPAL_SLI15693_SW_TIMEOUT_SLOT_US));

    /* Disable SOF, so only EOF is sent */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_SYMBOL_START,
        PH_OFF));

    /* Exchange command */
    status = phhalHw_Exchange(
        pDataParams->pHalDataParams,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        &pResp,
        &wRespLength);

    /* Reset HAL to send SOF and EOF */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_SYMBOL_START,
        PHHAL_HW_SYMBOL_I15693_SOF));

    /* Check Success */
    PH_CHECK_SUCCESS(status);

    /* Check RespLength */
    if (wRespLength == 0)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_SLI15693);
    }

    /* check error flag */
    if (pResp[0] & PHPAL_SLI15693_FLAG_RESP_ERROR)
    {
        /* check the length in case of error */
        if (wRespLength != 2)
        {
            return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_SLI15693);
        }

        pDataParams->wAdditionalInfo = pResp[1];
        return PH_ADD_COMPCODE(PHPAL_SLI15693_ERR_ISO15693, PH_COMP_PAL_SLI15693);
    }

    if (bOption == PHPAL_SLI15693_EOF_NEXT_SLOT)
    {
        /* ignore flag byte */
        ++pResp;
        --wRespLength;

        /* the UID is only returned on a next slot command. */
        if (wRespLength != (1 + PHPAL_SLI15693_UID_LENGTH))
        {
            return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_SLI15693);
        }

        /* wait T2 */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Wait(
            pDataParams->pHalDataParams,
            PHHAL_HW_TIME_MICROSECONDS,
            PHPAL_SLI15693_SW_T2_WAITING_TIME));

        /* Copy the DSFID to the data buffer */
        *pDsfid = pResp[0];

        /* retrieve the UID */
        memcpy(pDataParams->pUid, &pResp[1], PHPAL_SLI15693_UID_LENGTH); /* PRQA S 3200 */
        pDataParams->bUidBitLength = PHPAL_SLI15693_SW_UID_COMPLETE;

        /* return the UID */
        memcpy(pUid, &pResp[1], PHPAL_SLI15693_UID_LENGTH); /* PRQA S 3200 */
        *pUidLength = PHPAL_SLI15693_UID_LENGTH;

        /* set addressed flag */
        pDataParams->bFlags |= PHPAL_SLI15693_FLAG_ADDRESSED;
    }
    else if (bOption == PHPAL_SLI15693_EOF_NEXT_SLOT_INV_READ)
    {
        /* ignore flag byte */
        ++pResp;
        --wRespLength;

        /* Option flag is set -> we also received (partial) UID */
        if (pDataParams->bFlags & PHPAL_SLI15693_FLAG_OPTION)
        {
            /* The response length should not be less than the remaining UID */
            bStoredUidLength = pDataParams->bUidBitLength >> 3;
            *pUidLength = PHPAL_SLI15693_UID_LENGTH - bStoredUidLength;
            if (wRespLength < *pUidLength)
            {
                return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_SLI15693);
            }

            if (bStoredUidLength < PHPAL_SLI15693_UID_LENGTH)
            {
                /* We need to merge the contents of the mask buffer and the received data */
                if (pDataParams->bUidBitLength % 8)
                {
                    if (bStoredUidLength < 7)
                    {
                        /* copy the UID bytes we received from the card */
                        memcpy(&(pDataParams->pUid[bStoredUidLength + 1]), &pResp[1], (*pUidLength)-1); /* PRQA S 3200 */
                    }

                    /* merge mask-bits with received bits */
                    pDataParams->pUid[bStoredUidLength] |= pResp[0];
                }
                else
                {
                    /* copy the UID bytes we received from the card */
                    memcpy(&(pDataParams->pUid[bStoredUidLength]), pResp, *pUidLength); /* PRQA S 3200 */
                }

                /* Return the received (partial) UID */
                memcpy(pUid, pResp, *pUidLength); /* PRQA S 3200 */
            }

            /* UID is now complete */
            pDataParams->bUidBitLength = PHPAL_SLI15693_SW_UID_COMPLETE;

            /* shift pointer and length */
            pResp += *pUidLength;
            wRespLength = wRespLength - *pUidLength;
        }

        /* copy the received data to the provided buffer */
        memcpy(pData, pResp, wRespLength); /* PRQA S 3200 */

        /* the remaining bytes of the response are the data bytes */
        *pDataLength = wRespLength;

        /* clear option flag */
        pDataParams->bFlags &= (uint8_t)~(uint8_t)PHPAL_SLI15693_FLAG_OPTION;

        /* set addressed flag */
        pDataParams->bFlags |= PHPAL_SLI15693_FLAG_ADDRESSED;

        /* wait T2 */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Wait(
            pDataParams->pHalDataParams,
            PHHAL_HW_TIME_MICROSECONDS,
            PHPAL_SLI15693_SW_T2_WAITING_TIME));
    }
    else
    {
        /* 1 byte is only returned on a eof for a write alike command. */
        if (wRespLength != 1)
        {
            return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_SLI15693);
        }
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_SLI15693);
}

phStatus_t phpalSli15693_Sw_StayQuiet(
                                      phpalSli15693_Sw_DataParams_t * pDataParams
                                      )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM aCmd[1];
    uint8_t *   PH_MEMLOC_REM pResp;
    uint16_t    PH_MEMLOC_REM wRespLength;

    /* clear selected flag */
    pDataParams->bFlags &= (uint8_t)~(uint8_t)PHPAL_SLI15693_FLAG_SELECTED;

    /* set addressed flag */
    pDataParams->bFlags |= PHPAL_SLI15693_FLAG_ADDRESSED;

    /* reset to ready command */
    aCmd[0] = PHPAL_SLI15693_SW_CMD_STAY_QUIET;

    /* Set short timeout. */
    PH_CHECK_SUCCESS_FCT(statusTmp, phpalSli15693_SetConfig(
        pDataParams,
        PHPAL_SLI15693_CONFIG_TIMEOUT_US,
        PHPAL_SLI15693_TIMEOUT_SHORT_US));

    /* Exchange command */
    status = phpalSli15693_Exchange(
        pDataParams,
        PH_EXCHANGE_DEFAULT,
        aCmd,
        1,
        &pResp,
        &wRespLength);

    /* No response to the command allowed */
    if ((status & PH_ERR_MASK) != PH_ERR_IO_TIMEOUT)
    {
        PH_CHECK_SUCCESS(status);
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_SLI15693);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_SLI15693);
}

phStatus_t phpalSli15693_Sw_Select(
                                   phpalSli15693_Sw_DataParams_t * pDataParams
                                   )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM aCmd[1];
    uint8_t *   PH_MEMLOC_REM pResp;
    uint16_t    PH_MEMLOC_REM wRespLength;

    /* clear selected flag */
    pDataParams->bFlags &= (uint8_t)~(uint8_t)PHPAL_SLI15693_FLAG_SELECTED;

    /* set addressed flag */
    pDataParams->bFlags |= PHPAL_SLI15693_FLAG_ADDRESSED;

    /* reset to ready command */
    aCmd[0] = PHPAL_SLI15693_SW_CMD_SELECT;

    /* Set short timeout. */
    PH_CHECK_SUCCESS_FCT(statusTmp, phpalSli15693_SetConfig(
        pDataParams,
        PHPAL_SLI15693_CONFIG_TIMEOUT_US,
        PHPAL_SLI15693_TIMEOUT_SHORT_US));

    /* Exchange command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phpalSli15693_Exchange(
        pDataParams,
        PH_EXCHANGE_DEFAULT,
        aCmd,
        1,
        &pResp,
        &wRespLength));

    /* We shall not receive any data */
    if (wRespLength != 0)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_SLI15693);
    }
    
    /* clear addressed flag */
    pDataParams->bFlags &= (uint8_t)~(uint8_t)PHPAL_SLI15693_FLAG_ADDRESSED;

    /* set selected flag */
    pDataParams->bFlags |= PHPAL_SLI15693_FLAG_SELECTED;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_SLI15693);
}

phStatus_t phpalSli15693_Sw_ResetToReady(
    phpalSli15693_Sw_DataParams_t * pDataParams
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM aCmd[1];
    uint8_t *   PH_MEMLOC_REM pResp;
    uint16_t    PH_MEMLOC_REM wRespLength;

    /* reset to ready command */
    aCmd[0] = PHPAL_SLI15693_SW_CMD_RESET_TO_READY;

    /* Set short timeout. */
    PH_CHECK_SUCCESS_FCT(statusTmp, phpalSli15693_SetConfig(
        pDataParams,
        PHPAL_SLI15693_CONFIG_TIMEOUT_US,
        PHPAL_SLI15693_TIMEOUT_SHORT_US));

    /* Exchange command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phpalSli15693_Exchange(
        pDataParams,
        PH_EXCHANGE_DEFAULT,
        aCmd,
        1,
        &pResp,
        &wRespLength));

    /* We shall not receive any data */
    if (wRespLength != 0)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_SLI15693);
    }

    /* clear selected flag */
    pDataParams->bFlags &= (uint8_t)~(uint8_t)PHPAL_SLI15693_FLAG_SELECTED;
    
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_SLI15693);
}

phStatus_t phpalSli15693_Sw_Exchange(
                                     phpalSli15693_Sw_DataParams_t * pDataParams,
                                     uint16_t wOption,
                                     uint8_t * pTxBuffer,
                                     uint16_t wTxLength,
                                     uint8_t ** ppRxBuffer,
                                     uint16_t * pRxLength
                                     )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bFirstBlock[3];
    uint16_t    PH_MEMLOC_REM wTransmitLength;
    uint16_t    PH_MEMLOC_REM RxLength;
    uint8_t *   PH_MEMLOC_REM pRxBuffer;

    /* the frame to exchange looks like the following:
    {optional} [one byte]
    [flags][CMD]{[MFC]}{[UID0] .. [UID3]}[CMDParam(0)] .. [CMDParam(N)] */

    /* Check for valid UID in addressed mode */
    if (!(pDataParams->bFlags & PHPAL_SLI15693_FLAG_INVENTORY) && (pDataParams->bFlags & PHPAL_SLI15693_FLAG_ADDRESSED))
    {
        /* Return an error if UID is not valid */
        if (pDataParams->bUidBitLength != PHPAL_SLI15693_SW_UID_COMPLETE)
        {
            return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_PAL_SLI15693);
        }
    }

    /* Check if caller has provided valid RxBuffer */
    if (ppRxBuffer == NULL)
    {
        ppRxBuffer = &pRxBuffer;
    }
    if (pRxLength == NULL)
    {
        pRxLength = &RxLength;
    }

    if (!(wOption & PH_EXCHANGE_LEAVE_BUFFER_BIT))
    {
        /* This is the first chunk of a command frame. Add the Flags byte and ... */
        bFirstBlock[0] = pDataParams->bFlags;
        bFirstBlock[1] = pTxBuffer[0];
        wTransmitLength = 2;

        /* add MFC byte for custom commands */
        if ((pTxBuffer[0] > 0x9F) && (pTxBuffer[0] < 0xE0))
        {
            /* if no serial number is valid we assume that we use only NXP tags. */
            bFirstBlock[2] = PHPAL_SLI15693_SW_NXP_MFG_CODE;
            ++wTransmitLength;
        }

        /* Exchange command */
        /* clear buffer but do not send */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Exchange(
            pDataParams->pHalDataParams,
            PH_EXCHANGE_BUFFERED_BIT,
            bFirstBlock,
            wTransmitLength,
            ppRxBuffer,
            pRxLength));

        /* First byte was the command byte */
        ++pTxBuffer;
        --wTxLength;

        /* If we are not waiting any more we can transmit the UID bytes, if necessary. */
        if (!(pDataParams->bFlags & PHPAL_SLI15693_FLAG_INVENTORY) && (pDataParams->bFlags & PHPAL_SLI15693_FLAG_ADDRESSED))
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Exchange(
                pDataParams->pHalDataParams,
                PH_EXCHANGE_BUFFER_CONT,    /* do not clear, do not send */
                pDataParams->pUid,
                PHPAL_SLI15693_UID_LENGTH,
                ppRxBuffer,
                pRxLength));
        }

        /* Now we need to keep our buffered contents */
        wOption |= PH_EXCHANGE_LEAVE_BUFFER_BIT;
    }

    /* Exchange command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Exchange(
        pDataParams->pHalDataParams,
        wOption,
        pTxBuffer,
        wTxLength,
        ppRxBuffer,
        pRxLength));

    /* If this was the last (or only) chunk, we shoult have received a response,
    so we extract the Flags byte and check the status */
    if (!(wOption & PH_EXCHANGE_BUFFERED_BIT))
    {
        /* First Check RespLength*/
        if (*pRxLength == 0)
        {
            return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_SLI15693);
        }

        /*check error flag*/
        if ((*ppRxBuffer[0]) & PHPAL_SLI15693_FLAG_RESP_ERROR)
        {
            /* check the length in case of error */
            if (*pRxLength != 2)
            {
                return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_SLI15693);
            }

            /* Copy error code to additional info */
            pDataParams->wAdditionalInfo = (*ppRxBuffer)[1];

            /* Return empty receive buffer */
            *ppRxBuffer = NULL;
            *pRxLength = 0;

            return PH_ADD_COMPCODE(PHPAL_SLI15693_ERR_ISO15693, PH_COMP_PAL_SLI15693);
        }

        /* adjust pointer and length */
        ++(*ppRxBuffer);
        --(*pRxLength);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_SLI15693);
}

phStatus_t phpalSli15693_Sw_ActivateCard(
    phpalSli15693_Sw_DataParams_t * pDataParams,
    uint8_t  bOption,
    uint8_t bFlags,
    uint8_t bAfi,
    uint8_t * pMask,
    uint8_t bMaskBitLength,
    uint8_t * pDsfid,
    uint8_t * pUid,
    uint8_t * pMoreCardsAvailable
    )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bSlot;
    uint8_t     PH_MEMLOC_REM bTimeOutNotAllowed;
    uint8_t     PH_MEMLOC_REM aMaskBuffer[PHPAL_SLI15693_UID_LENGTH];
    uint8_t     PH_MEMLOC_REM bMaskByteLength;
    uint8_t     PH_MEMLOC_REM bUidLengthDummy;
    uint8_t     PH_MEMLOC_REM bDataDummy[1];
    uint16_t    PH_MEMLOC_REM wDataLengthDummy;

    /* Check option byte */
    if ((bOption != PHPAL_SLI15693_ACTIVATE_ADDRESSED) && (bOption != PHPAL_SLI15693_ACTIVATE_SELECTED))
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_SLI15693);
    }

    /* init return value */
    *pMoreCardsAvailable = 0;
    
    /* Perform inventory command */
    status = phpalSli15693_Sw_Inventory(pDataParams, bFlags, bAfi, pMask, bMaskBitLength, pDsfid, pUid);

    /* Check for invalid parameter */
    if ((status & PH_ERR_MASK) == PH_ERR_INVALID_PARAMETER)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_SLI15693);
    }

    /* Retrieve mask byte length */
    bMaskByteLength = (bMaskBitLength % 8) ? ((bMaskBitLength >> 3) + 1) : (bMaskBitLength >> 3);

    /* init mask buffer */
	memset(aMaskBuffer, 0, sizeof(aMaskBuffer));  /* PRQA S 3200 */
    memcpy(aMaskBuffer, pMask, bMaskByteLength);  /* PRQA S 3200 */

    /* if we have more than one slot, we need to send slot markers (b6 = 0) */
    if (!(bFlags & PHPAL_SLI15693_FLAG_NBSLOTS))
    {
        /* Slot marker loop */
        bSlot = 0;
        while ((status & PH_ERR_MASK) != PH_ERR_SUCCESS)
        {
            switch (status & PH_ERR_MASK)
            {
                /*  If a CRC error or collision error occured --> resolve collision */
            case PH_ERR_COLLISION_ERROR:
            case PH_ERR_INTEGRITY_ERROR:

                *pMoreCardsAvailable = 1;

                /* Get bit-length of last valid byte */
                bUidLengthDummy = bMaskBitLength % 8;

                /* Whole byte is valid -> append slot number to next byte */
                if (bUidLengthDummy == 0)
                {
                    aMaskBuffer[bMaskBitLength >> 3] = bSlot;
                }
                /* Partial byte is valid */
                else
                {
                    /* Fill the invalid bits of the incomple byte with the 4 bits slot number */
                    aMaskBuffer[bMaskBitLength >> 3] &= (uint8_t)(0xFF >> (8 - bUidLengthDummy));
                    aMaskBuffer[bMaskBitLength >> 3] |= (uint8_t)(bSlot << bUidLengthDummy);

                    /* If not all 4 bits of the Slot number fit in the incomplete byte, put the rest in the next byte */
                    if (bUidLengthDummy > 4)
                    {
                        aMaskBuffer[(bMaskBitLength >> 3) + 1] = (uint8_t)(bSlot >> bUidLengthDummy);
                    }
                }

                /* Increment the bitlength by the 4 bits slot number */
                bMaskBitLength = bMaskBitLength + 4;

                /* Start again from Slot number 0 */
                bSlot = 0;
                status = phpalSli15693_Sw_Inventory(pDataParams, bFlags, bAfi, aMaskBuffer, bMaskBitLength, pDsfid, pUid);
                break;

                /* Timeout -> advance to next slot */
            case PH_ERR_IO_TIMEOUT:

                /* Send EOF and increment slot number */
                ++bSlot;
                status = phpalSli15693_Sw_SendEof(
                    pDataParams,
                    PHPAL_SLI15693_EOF_NEXT_SLOT,
                    pDsfid,
                    pUid,
                    &bUidLengthDummy,
                    bDataDummy,
                    &wDataLengthDummy);
                break;

                /* Other error -> bail out */
            default:
                return status;
            }

            /* if we ran through all slots, we are done */
            if (bSlot == 15)
            {
                break;
            }
        }
    }
    /* use only one slot */
    else
    {
        /* Do not allow a time out after the first Inventory command since then, no
        card with the specified mask is present in the field. */
        bTimeOutNotAllowed = 1;

        /* Bit mask loop */
        while (bMaskBitLength < PHPAL_SLI15693_SW_UID_COMPLETE)
        {
            switch (status & PH_ERR_MASK)
            {
                /* If there was a card, the loop is done */
            case PH_ERR_SUCCESS:
                bMaskBitLength = PHPAL_SLI15693_SW_UID_COMPLETE;
                break;

                /* In case of a timeout, no card with the actual mask is in the field, so toggle the last bit of the mask */
            case PH_ERR_IO_TIMEOUT:
                /* Abort, if this bit was already tested */
                if (bTimeOutNotAllowed)
                {
                    return status;
                }

                /* the bit mask is > 0, because in the case of bitmask = 0 a timeout can not happen */
                aMaskBuffer[(uint8_t)(bMaskBitLength - 1) >> 3] = aMaskBuffer[(uint8_t)(bMaskBitLength - 1) >> 3] ^ (uint8_t)(0x01 << (uint8_t)((bMaskBitLength - 1) % 8));
                bTimeOutNotAllowed = 1;
                break;

                /*  If a CRC error or collision error occured add one bit to the mask. */
            case PH_ERR_COLLISION_ERROR:
            case PH_ERR_INTEGRITY_ERROR:
                /* Note: The value of this bit does not realy matter since it will be toggled in case of a timeout */
                *pMoreCardsAvailable = 1;

                ++bMaskBitLength;
                bTimeOutNotAllowed = 0;
                break;

                /* If it is an other error than Collision, Crc or Timeout Error the function should return the error */
            default:
                return status;
            }

            /* Perform next inventory command to perform anticollision */
            if (bMaskBitLength < PHPAL_SLI15693_SW_UID_COMPLETE)
            {
                status = phpalSli15693_Sw_Inventory(pDataParams, bFlags, bAfi, aMaskBuffer, bMaskBitLength, pDsfid, pUid);
            }
        }
    }

    /* no need to proceed if an error occured. */
    if ((status & PH_ERR_MASK) != PH_ERR_SUCCESS)
    {
        /* clear option flag */
        pDataParams->bFlags &= (uint8_t)~(uint8_t)PHPAL_SLI15693_FLAG_OPTION;
        return status;
    }

    /* Select the card if neccessary */
    if (bOption & PHPAL_SLI15693_ACTIVATE_SELECTED)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phpalSli15693_Select(pDataParams));
    }

    /* Set long timeout. */
    PH_CHECK_SUCCESS_FCT(statusTmp, phpalSli15693_SetConfig(
        pDataParams,
        PHPAL_SLI15693_CONFIG_TIMEOUT_US,
        PHPAL_SLI15693_TIMEOUT_LONG_US));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_SLI15693);
}

phStatus_t phpalSli15693_Sw_GetSerialNo(
                                        phpalSli15693_Sw_DataParams_t * pDataParams,
                                        uint8_t * pUid,
                                        uint8_t * pUidLength
                                        )
{
    /* Return an error if UID is not valid */
    if (pDataParams->bUidBitLength != PHPAL_SLI15693_SW_UID_COMPLETE)
    {
        *pUidLength = 0;
        return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_PAL_SLI15693);
    }

    /* copy the UID */
    memcpy(pUid, pDataParams->pUid, PHPAL_SLI15693_UID_LENGTH); /* PRQA S 3200 */
    *pUidLength = PHPAL_SLI15693_UID_LENGTH;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_SLI15693);
}

phStatus_t phpalSli15693_Sw_SetConfig(
                                      phpalSli15693_Sw_DataParams_t * pDataParams,
                                      uint16_t wConfig,
                                      uint16_t wValue
                                      )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t    PH_MEMLOC_REM wValueOld;

    switch (wConfig)
    {
    case PHPAL_SLI15693_CONFIG_FLAGS:

        /* Retrieve current subcarrier setting */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_GetConfig(
            pDataParams->pHalDataParams,
            PHHAL_HW_CONFIG_SUBCARRIER,
            &wValueOld));

        /* Set dual subcarrier if HAL is not already configured for it */
        if (wValue & PHPAL_SLI15693_FLAG_TWO_SUB_CARRIERS)
        {
            if (wValueOld != PHHAL_HW_SUBCARRIER_DUAL)
            {
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
                    pDataParams->pHalDataParams,
                    PHHAL_HW_CONFIG_SUBCARRIER,
                    PHHAL_HW_SUBCARRIER_DUAL));
            }
        }
        /* Set single subcarrier if HAL is not already configured for it */
        else
        {
            if (wValueOld != PHHAL_HW_SUBCARRIER_SINGLE)
            {
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
                    pDataParams->pHalDataParams,
                    PHHAL_HW_CONFIG_SUBCARRIER,
                    PHHAL_HW_SUBCARRIER_SINGLE));
            }
        }

        /* Retrieve current datarate setting */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_GetConfig(
            pDataParams->pHalDataParams,
            PHHAL_HW_CONFIG_RXDATARATE,
            &wValueOld));

        /* Set high datarate if HAL is not already configured for it */
        if (wValue & PHPAL_SLI15693_FLAG_DATA_RATE)
        {
            if (wValueOld != PHHAL_HW_RF_RX_DATARATE_HIGH)
            {
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
                    pDataParams->pHalDataParams,
                    PHHAL_HW_CONFIG_RXDATARATE,
                    PHHAL_HW_RF_RX_DATARATE_HIGH));  
            }
        }
        /* Set low datarate if HAL is not already configured for it */
        else
        {
            if (wValueOld != PHHAL_HW_RF_RX_DATARATE_LOW)
            {
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
                    pDataParams->pHalDataParams,
                    PHHAL_HW_CONFIG_RXDATARATE,
                    PHHAL_HW_RF_RX_DATARATE_LOW));
            }
        }

        /* retrieve flags */
        pDataParams->bFlags = (uint8_t)wValue;

        /* mask out the inventory flag */
        pDataParams->bFlags &= (uint8_t)~(uint8_t)PHPAL_SLI15693_FLAG_INVENTORY;
        break;

    case PHPAL_SLI15693_CONFIG_TIMEOUT_US:

        /* Extend timeout a little */
        wValue += PHPAL_SLI15693_SW_EXT_TIME_US;

        /* Retrieve current timeout */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_GetConfig(
            pDataParams->pHalDataParams,
            PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,
            &wValueOld));

        /* Set the new timeout */
        if (wValue != wValueOld)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
                pDataParams->pHalDataParams,
                PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,
                wValue));
        }
        break;

    case PHPAL_SLI15693_CONFIG_TIMEOUT_MS:

        /* Retrieve current timeout */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_GetConfig(
            pDataParams->pHalDataParams,
            PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS,
            &wValueOld));

        /* Set the new timeout */
        if (wValue != wValueOld)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
                pDataParams->pHalDataParams,
                PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS,
                wValue));
        }
        break;

    default:
        return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_PAL_SLI15693);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_SLI15693);
}

phStatus_t phpalSli15693_Sw_GetConfig(
                                      phpalSli15693_Sw_DataParams_t * pDataParams,
                                      uint16_t wConfig,
                                      uint16_t * pValue
                                      )
{
    phStatus_t PH_MEMLOC_REM statusTmp;

    switch (wConfig)
    {
    case PHPAL_SLI15693_CONFIG_FLAGS:
        *pValue = pDataParams->bFlags;
        break;

    case PHPAL_SLI15693_CONFIG_ADD_INFO:
        *pValue = pDataParams->wAdditionalInfo;
        break;

    case PHPAL_SLI15693_CONFIG_TIMEOUT_US:
        /* Get HAL timeout value */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_GetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,
        pValue));

        /* Remove timeout extension */
        *pValue -= PHPAL_SLI15693_SW_EXT_TIME_US;
        break;

    case PHPAL_SLI15693_CONFIG_TIMEOUT_MS:
        /* Get HAL timeout value */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_GetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS,
        pValue));

        break;

    default:
        return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_PAL_SLI15693);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_SLI15693);
}

phStatus_t phpalSli15693_Sw_InventoryRead(
    phpalSli15693_Sw_DataParams_t * pDataParams,
    uint8_t bFlags,
    uint8_t bAfi,
    uint8_t * pMask,
    uint8_t bMaskBitLength,
    uint8_t bBlockNo,
    uint16_t wNoOfBlocks,
    uint8_t * pUid,
    uint8_t * bUidLength,
    uint8_t * pData,
    uint16_t * wLength
    )
{
    return phpalSli15693_Sw_InventoryEx(
        pDataParams,
        PHPAL_SLI15693_SW_CMD_INVENTORY_READ,
        bFlags,
        bAfi,
        pMask,
        bMaskBitLength,
        bBlockNo,
        wNoOfBlocks,
        pUid,
        bUidLength,
        pData,
        wLength);
}

phStatus_t phpalSli15693_Sw_FastInventoryRead(
    phpalSli15693_Sw_DataParams_t * pDataParams,
    uint8_t bFlags,
    uint8_t bAfi,
    uint8_t * pMask,
    uint8_t bMaskBitLength,
    uint8_t bBlockNo,
    uint16_t wNoOfBlocks,
    uint8_t * pUid,
    uint8_t * pUidLength,
    uint8_t * pData,
    uint16_t * pDataLength
    )
{
    return phpalSli15693_Sw_InventoryEx(
        pDataParams,
        PHPAL_SLI15693_SW_CMD_FAST_INVENTORY_READ,
        bFlags,
        bAfi,
        pMask,
        bMaskBitLength,
        bBlockNo,
        wNoOfBlocks,
        pUid,
        pUidLength,
        pData,
        pDataLength);
}

phStatus_t phpalSli15693_Sw_InventoryPageRead(
    phpalSli15693_Sw_DataParams_t * pDataParams,
    uint8_t bFlags,
    uint8_t bAfi,
    uint8_t * pMask,
    uint8_t bMaskBitLength,
    uint8_t bPageNo,
    uint16_t wNoOfPages,
    uint8_t * pUid,
    uint8_t * pUidLength,
    uint8_t * pData,
    uint16_t * pDataLength
    )
{
    return phpalSli15693_Sw_InventoryEx(
        pDataParams,
        PHPAL_SLI15693_SW_CMD_INVENTORY_PAGE_READ,
        bFlags,
        bAfi,
        pMask,
        bMaskBitLength,
        bPageNo,
        wNoOfPages,
        pUid,
        pUidLength,
        pData,
        pDataLength);
}

phStatus_t phpalSli15693_Sw_FastInventoryPageRead(
    phpalSli15693_Sw_DataParams_t * pDataParams,
    uint8_t bFlags,
    uint8_t bAfi,
    uint8_t * pMask,
    uint8_t bMaskBitLength,
    uint8_t bPageNo,
    uint16_t wNoOfPages,
    uint8_t * pUid,
    uint8_t * pUidLength,
    uint8_t * pData,
    uint16_t * pDataLength
    )
{
    return phpalSli15693_Sw_InventoryEx(
        pDataParams,
        PHPAL_SLI15693_SW_CMD_FAST_INVENTORY_PAGE_READ,
        bFlags,
        bAfi,
        pMask,
        bMaskBitLength,
        bPageNo,
        wNoOfPages,
        pUid,
        pUidLength,
        pData,
        pDataLength);
}

phStatus_t phpalSli15693_Sw_InventoryEx(
                                        phpalSli15693_Sw_DataParams_t * pDataParams,
                                        uint8_t bCmd,
                                        uint8_t bFlags,
                                        uint8_t bAfi,
                                        uint8_t * pMask,
                                        uint8_t bMaskBitLength,
                                        uint8_t bPage_Block_No,
                                        uint16_t wNoOfPages_Blocks,
                                        uint8_t * pUid,
                                        uint8_t * pUidLength,
                                        uint8_t * pData,
                                        uint16_t * pDataLength
                                        )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bCmdBuffer[15];
    uint8_t     PH_MEMLOC_REM bCmdBufferLen = 0;
    uint8_t     PH_MEMLOC_REM bMaskByteLength;
    uint8_t *   PH_MEMLOC_REM pResp;
    uint16_t    PH_MEMLOC_REM wRespLength;
    uint8_t     PH_MEMLOC_REM bStoredUidLength;

    /* Reset UID and data length */
    pDataParams->bUidBitLength = 0;
    *pUidLength = 0;
    *pDataLength = 0;

    /* first of all we check the bMaskBitLength according to ISO/IEC15693, 8.1, assuming
    the inventory flag to be set, si b6 deines the number of slots
    b6 = 1: --> one slot --> mask length = [0 .. 64] bits
    b6 = 0: --> 16 slots --> mask length = [0 .. 60] bits */
    if (((bFlags & PHPAL_SLI15693_FLAG_NBSLOTS) && (bMaskBitLength > 64)) ||
        (!(bFlags & PHPAL_SLI15693_FLAG_NBSLOTS) && (bMaskBitLength > 60)))
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_SLI15693);
    }

    /* Number of Pages/Blocks check */
    if (bCmd != PHPAL_SLI15693_SW_CMD_INVENTORY)
    {
        /* Number of Pages/Blocks can't be zero */
        if (wNoOfPages_Blocks == 0)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_SLI15693);
        }

        /* Number of pages (or blocks). The card always sends one page (block) more than requested,
        so we adjust the value of wNoOfPages_Blocks */
        --wNoOfPages_Blocks;

        /* check if the block number exceeds the limit */
        if (((uint16_t)bPage_Block_No + wNoOfPages_Blocks) >= 0x100)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_SLI15693);
        }
    }

    /* Add command code */
    bCmdBuffer[bCmdBufferLen++] = bCmd;

    /* Apply flag settings */
    PH_CHECK_SUCCESS_FCT(statusTmp, phpalSli15693_SetConfig(
        pDataParams,
        PHPAL_SLI15693_CONFIG_FLAGS,
        bFlags));

    /* Overwrite datarate for fast inventory (page-)read */
    if ((bCmd == PHPAL_SLI15693_SW_CMD_FAST_INVENTORY_READ) ||
        (bCmd == PHPAL_SLI15693_SW_CMD_FAST_INVENTORY_PAGE_READ))
    {
        if (bFlags & PHPAL_SLI15693_FLAG_DATA_RATE)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
                pDataParams->pHalDataParams,
                PHHAL_HW_CONFIG_RXDATARATE,
                PHHAL_HW_RF_RX_DATARATE_FAST_HIGH));
        }
        else
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
                pDataParams->pHalDataParams,
                PHHAL_HW_CONFIG_RXDATARATE,
                PHHAL_HW_RF_RX_DATARATE_FAST_LOW));
        }
    }

    /* check if AFI shall be sent: */
    if (bFlags & PHPAL_SLI15693_FLAG_AFI)
    {
        bCmdBuffer[bCmdBufferLen++] = bAfi;
    }

    /* Add mask length */
    bCmdBuffer[bCmdBufferLen++] = bMaskBitLength;

    /* Retrieve mask byte length */
    bMaskByteLength = (bMaskBitLength % 8) ? ((bMaskBitLength >> 3) + 1) : (bMaskBitLength >> 3);

    /* prepare mask in dataparams */
    memcpy(pDataParams->pUid, pMask, bMaskByteLength ); /* PRQA S 3200 */
    pDataParams->bUidBitLength = bMaskBitLength;

    /* prepare mask to send */
    memcpy(&bCmdBuffer[bCmdBufferLen], pMask, bMaskByteLength ); /* PRQA S 3200 */
    bCmdBufferLen = bCmdBufferLen + bMaskByteLength;

    /* mask out invalid bits */
    if (bMaskBitLength & 0x07)
    {
        bCmdBuffer[bCmdBufferLen - 1] &= (uint8_t)(0xFF >> (8 - (bMaskBitLength & 0x07)));
    }

    /* Page (or block) number and count */
    if (bCmd != PHPAL_SLI15693_SW_CMD_INVENTORY)
    {
        bCmdBuffer[bCmdBufferLen++] = bPage_Block_No;
        bCmdBuffer[bCmdBufferLen++] = (uint8_t)wNoOfPages_Blocks;
    }

    /* Set short timeout. */
    PH_CHECK_SUCCESS_FCT(statusTmp, phpalSli15693_SetConfig(
        pDataParams,
        PHPAL_SLI15693_CONFIG_TIMEOUT_US,
        PHPAL_SLI15693_TIMEOUT_SHORT_US));

    /* Set (temporary) inventory flag */
    pDataParams->bFlags |= PHPAL_SLI15693_FLAG_INVENTORY;

    /* Exchange command. */
    status = phpalSli15693_Exchange(
        pDataParams,
        PH_EXCHANGE_DEFAULT,
        bCmdBuffer,
        bCmdBufferLen,
        &pResp,
        &wRespLength);

    /* Clear INVENTORY, AFI and NBSLOTS flag */
    pDataParams->bFlags &= (uint8_t)~(uint8_t)(PHPAL_SLI15693_FLAG_INVENTORY | PHPAL_SLI15693_FLAG_AFI | PHPAL_SLI15693_FLAG_NBSLOTS);

    /* Error check */
    PH_CHECK_SUCCESS(status);

    /* Check the response length */
    /* we expect bNoOfPages * Page length plus, if the option flag was set,
    the rest of the UID which is not part of the mask and slot number */

    /* set the length (amount) of expected UID bytes */
    if (bCmd == PHPAL_SLI15693_SW_CMD_INVENTORY)
    {
        /* The response length should be exactly the complete UID */
        if (wRespLength != (1 + PHPAL_SLI15693_UID_LENGTH))
        {
            return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_SLI15693);
        }

        /* Copy the DSFID to the data buffer */
        pData[0] = pResp[0];
        *pDataLength = 1;

        /* Store the UID */
        memcpy(pDataParams->pUid, &pResp[1], PHPAL_SLI15693_UID_LENGTH); /* PRQA S 3200 */
        pDataParams->bUidBitLength = PHPAL_SLI15693_SW_UID_COMPLETE;

        /* Return the UID */
        memcpy(pUid, pDataParams->pUid, PHPAL_SLI15693_UID_LENGTH); /* PRQA S 3200 */
        *pUidLength = PHPAL_SLI15693_UID_LENGTH;
    }
    else
    {
        if (bFlags & PHPAL_SLI15693_FLAG_OPTION)
        {
            /* The response length should not be less than the remaining UID */
            bStoredUidLength = pDataParams->bUidBitLength >> 3;
            *pUidLength = PHPAL_SLI15693_UID_LENGTH - bStoredUidLength;
            if (wRespLength < (*pUidLength + 2))
            {
                return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_SLI15693);
            }

            if (bStoredUidLength < PHPAL_SLI15693_UID_LENGTH)
            {
                /* Return the received (partial) UID */
                memcpy(pUid, pResp, *pUidLength); /* PRQA S 3200 */

                /* We need to merge the contents of the mask buffer and the received data */
                if (bMaskBitLength % 8)
                {
                    if (bStoredUidLength < 7)
                    {
                        /* copy the UID bytes we received from the card */
                        memcpy(&(pDataParams->pUid[bStoredUidLength + 1]), &pResp[1], (*pUidLength)-1); /* PRQA S 3200 */
                    }

                    /* merge mask-bits with received bits */
                    pDataParams->pUid[bStoredUidLength] |= pResp[0];
                }
                else
                {
                    /* copy the UID bytes we received from the card */
                    memcpy(&(pDataParams->pUid[bStoredUidLength]), pResp, *pUidLength); /* PRQA S 3200 */
                }
            }

            /* shift pointer and length */
            pResp += *pUidLength;
            wRespLength = wRespLength - *pUidLength;
        }

        /* copy the received data to the provided buffer */
        memcpy(pData, pResp, wRespLength); /* PRQA S 3200 */

        /* the remaining bytes of the response are the data bytes */
        *pDataLength = wRespLength;
    }

    /* clear option flag */
    pDataParams->bFlags &= (uint8_t)~(uint8_t)PHPAL_SLI15693_FLAG_OPTION;

    /* set addressed flag */
    pDataParams->bFlags |= PHPAL_SLI15693_FLAG_ADDRESSED;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_SLI15693);
}

#endif /* NXPBUILD__PHPAL_SLI15693_SW */
