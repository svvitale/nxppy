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
* $Revision: 1.5 $
* $Date: Fri Apr 15 09:27:53 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#include <ph_Status.h>
#include <phhalHw.h>
#include <phpalI14443p3a.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHPAL_I14443P3A_SW

#include "phpalI14443p3a_Sw.h"
#include "phpalI14443p3a_Sw_Int.h"

phStatus_t phpalI14443p3a_Sw_Init(
                                  phpalI14443p3a_Sw_DataParams_t * pDataParams,
                                  uint16_t wSizeOfDataParams,
                                  void * pHalDataParams
                                  )
{
    if (sizeof(phpalI14443p3a_Sw_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P3A);
    }
	PH_ASSERT_NULL (pDataParams);
	PH_ASSERT_NULL (pHalDataParams);

    /* init private data */
    pDataParams->wId            = PH_COMP_PAL_ISO14443P3A | PHPAL_I14443P3A_SW_ID;
    pDataParams->pHalDataParams = pHalDataParams;
    pDataParams->bUidLength     = 0;
    pDataParams->bUidComplete   = 0;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_ISO14443P3A);
}

phStatus_t phpalI14443p3a_Sw_RequestA(
                                      phpalI14443p3a_Sw_DataParams_t * pDataParams,
                                      uint8_t * pAtqa
                                      )
{
    return phpalI14443p3a_Sw_RequestAEx(pDataParams, PHPAL_I14443P3A_REQUEST_CMD, pAtqa);
}

phStatus_t phpalI14443p3a_Sw_WakeUpA(
                                     phpalI14443p3a_Sw_DataParams_t * pDataParams,
                                     uint8_t * pAtqa
                                     )
{
    return phpalI14443p3a_Sw_RequestAEx(pDataParams, PHPAL_I14443P3A_WAKEUP_CMD, pAtqa);
}

phStatus_t phpalI14443p3a_Sw_HaltA(
                                   phpalI14443p3a_Sw_DataParams_t * pDataParams
                                   )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM cmd[2];
    uint8_t *   PH_MEMLOC_REM pResp;
    uint16_t    PH_MEMLOC_REM wRespLength;

    /* Set halt timeout */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,
        PHPAL_I14443P3A_HALT_TIME_US + PHPAL_I14443P3A_EXT_TIME_US));

    /* Send HltA command */
    cmd[0] = PHPAL_I14443P3A_HALT_CMD;
    cmd[1] = 0x00;
    status = phhalHw_Exchange(pDataParams->pHalDataParams, PH_EXCHANGE_DEFAULT, cmd, 2, &pResp, &wRespLength);

    switch (status & PH_ERR_MASK)
    {
        /* HltA command should timeout -> success */
    case PH_ERR_IO_TIMEOUT:
        return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_ISO14443P3A);
        /* Return protocol error */
    case PH_ERR_SUCCESS:
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_ISO14443P3A);
        /* Return other errors */
    default:
        return status;
    }
}

phStatus_t phpalI14443p3a_Sw_Anticollision(
    phpalI14443p3a_Sw_DataParams_t * pDataParams,
    uint8_t bCascadeLevel,
    uint8_t * pUidIn,
    uint8_t bNvbUidIn,
    uint8_t * pUidOut,
    uint8_t * pNvbUidOut
    )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bIsSelect;
    uint8_t     PH_MEMLOC_REM bCmdBuffer[7];
    uint8_t *   PH_MEMLOC_REM pRcvBuffer;
    uint16_t    PH_MEMLOC_REM wSndBytes;
    uint16_t    PH_MEMLOC_REM wRcvBytes;
    uint16_t    PH_MEMLOC_REM wRcvBits;
    uint8_t     PH_MEMLOC_REM bUidStartIndex;
    uint8_t     PH_MEMLOC_REM bBitCount;

    /* Check for invalid bNvbUidIn parameter */
    if ((bNvbUidIn > 0x40) || ((bNvbUidIn & 0x0F) > 0x07))
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_ISO14443P3A);
    }

    /* Check for invalid bCascadeIndex parameter */
    switch (bCascadeLevel)
    {
    case PHPAL_I14443P3A_CASCADE_LEVEL_1:
        /* Reset UID length */
        pDataParams->bUidLength = 0;
    case PHPAL_I14443P3A_CASCADE_LEVEL_2:
    case PHPAL_I14443P3A_CASCADE_LEVEL_3:
        break;
    default:
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_ISO14443P3A);
    }

    /* Reset UID complete flag */
    pDataParams->bUidComplete = 0;

    /* ANTICOLLISION: Disable CRC */
    if (bNvbUidIn != 0x40)
    {
        bIsSelect = 0;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_TXCRC, PH_OFF));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_RXCRC, PH_OFF));
    }
    /* SELECT: Enable CRC */
    else
    {
        bIsSelect = 1;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_TXCRC, PH_ON));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_RXCRC, PH_ON));
    }

    /* Init. command buffer */
    bCmdBuffer[0] = bCascadeLevel;
    memset(&bCmdBuffer[2], 0x00, 5);  /* PRQA S 3200 */

    /* Copy valid UID bits */
    wSndBytes = (uint16_t)(((bNvbUidIn & 0xF0) >> 4) + ((bNvbUidIn & 0x0F) ? 1 : 0));
    memcpy(&bCmdBuffer[2], pUidIn, (size_t)wSndBytes);  /* PRQA S 3200 */
    wSndBytes += 2;

    /* SELECT: Add BCC */
    if (bIsSelect)
    {
        bNvbUidIn = 0x50;
        bCmdBuffer[6] = pUidIn[0] ^ pUidIn[1] ^ pUidIn[2] ^ pUidIn[3];
        ++wSndBytes;
    }

    /* Encode NVB */
    bCmdBuffer[1] = bNvbUidIn + 0x20;

    /* Adjust Rx-Align */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_RXALIGN, bNvbUidIn & 0x07));

    /* Adjust TxBits */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_TXLASTBITS, bNvbUidIn & 0x07));

    /* Enable Clearing of bits after collision */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_CLEARBITSAFTERCOLL, PH_ON));

    /* Send the ANTICOLLISION command */
    status = phhalHw_Exchange(pDataParams->pHalDataParams, PH_EXCHANGE_DEFAULT, bCmdBuffer, wSndBytes, &pRcvBuffer, &wRcvBytes);

    /* Disable Clearing of bits after collision */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_CLEARBITSAFTERCOLL, PH_OFF));

    /* Reset RxAlignment */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_RXALIGN, 0));

    /* Check status, Collision is allowed for anticollision command */
    if ((bIsSelect == 0) && ((status & PH_ERR_MASK) == PH_ERR_COLLISION_ERROR))
    {
        /* Retrieve number of valid bits of last byte */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_GetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_RXLASTBITS, &wRcvBits));
    }
    else
    {
        /* Check for protocol error */
        if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS_INCOMPLETE_BYTE)
        {
            return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_ISO14443P3A);
        }
        /* Return on other errors */
        else
        {
            PH_CHECK_SUCCESS(status);
        }

        /* whole byte valid */
        wRcvBits = 0;
    }

    /* Add received data to UID */
    if (bIsSelect == 0)
    {
        /* Retrieve byte-starting-index of received Uid */
        bUidStartIndex = (uint8_t)((bNvbUidIn & 0xF0) >> 4);
        
        /* Add new bitcount */
        bBitCount = (uint8_t)(((bNvbUidIn >> 4) << 3) + (wRcvBytes << 3) + wRcvBits);

        /* Last incomplete byte is added to wRcvBytes, so remove that again */
        if (wRcvBits > 0)
        {
            bBitCount -= 8;
        }

        /* Convert bitcount to NVB format */
        *pNvbUidOut = (uint8_t)(((bBitCount >> 3) << 4) + (bBitCount & 0x07));

        /* We do not tolerate more than (5 * 8 =)40 bits because it would lead to buffer overflows */
        if (*pNvbUidOut > 0x50)
        {
            return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_ISO14443P3A);
        }

        /* After successfull reception, the UID must be exact 40 bits */
        if (((status & PH_ERR_MASK) == PH_ERR_SUCCESS) && (*pNvbUidOut != 0x50))
        {
            return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_ISO14443P3A);
        }

        /* Copy received bytes to uid */
        if (wRcvBytes > 0)
        {
            /* Incomplete byte sent: Merge Rx-Aligned first byte */
            if (bNvbUidIn & 0x07)
            {
                bCmdBuffer[2 + bUidStartIndex] |= pRcvBuffer[0];
            }
            /* Else just copy the first byte */
            else
            {
                bCmdBuffer[2 + bUidStartIndex] = pRcvBuffer[0];
            }

            /* Add the rest of the uid bytes */
            memcpy(&bCmdBuffer[2 + bUidStartIndex + 1], &pRcvBuffer[1], (size_t)(wRcvBytes - 1));  /* PRQA S 3200 */
        }

        /* Anticollision finished */
        if (*pNvbUidOut > 0x40)
        {
            /* Collision in BCC byte can never happen */
            if (*pNvbUidOut < 0x50)
            {
                return PH_ADD_COMPCODE(PH_ERR_FRAMING_ERROR, PH_COMP_PAL_ISO14443P3A);
            }

            /* Remove BCC from NvbUidOut */
            *pNvbUidOut = 0x40;
            --wRcvBytes;

            /* BCC Check */
            if ((bCmdBuffer[2] ^ bCmdBuffer[3] ^ bCmdBuffer[4] ^ bCmdBuffer[5]) != bCmdBuffer[6])
            {
                return PH_ADD_COMPCODE(PH_ERR_FRAMING_ERROR, PH_COMP_PAL_ISO14443P3A);
            }
        }

        /* Copy UID */
        memcpy(pUidOut, &bCmdBuffer[2], bUidStartIndex + wRcvBytes);  /* PRQA S 3200 */
    }
    /* Return SAK instead of the UID */
    else
    {
        /* only one byte allowed */
        if (wRcvBytes != 1)
        {
            return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_ISO14443P3A);
        }

        /* Cascade Bit is set */
        if (pRcvBuffer[0] & 0x04)
        {
            /* If additional cascade levels are impossible -> protocol error */
            if (bCascadeLevel == PHPAL_I14443P3A_CASCADE_LEVEL_3)
            {
                return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_ISO14443P3A);
            }

            /* Cascade tag does not match -> protocol error */
            if (pUidIn[0] != PHPAL_I14443P3A_CASCADE_TAG)
            {
                return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_ISO14443P3A);
            }

            /* Ignore Cascade Tag */
            memcpy(&pDataParams->abUid[pDataParams->bUidLength], &pUidIn[1], 3);  /* PRQA S 3200 */

            /* Increment Uid length */
            pDataParams->bUidLength += 3;
        }
        /* Cascade Bit is cleared -> no further cascade levels */
        else
        {
            /* Cascade tag does not match -> protocol error */
            if (pUidIn[0] == PHPAL_I14443P3A_CASCADE_TAG)
            {
                return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_ISO14443P3A);
            }

            /* Copy all uid bytes except BCC */
            memcpy(&pDataParams->abUid[pDataParams->bUidLength], &pUidIn[0], 4);  /* PRQA S 3200 */

            /* Increment Uid length */
            pDataParams->bUidLength += 4;

            /* Set UID complete flag */
            pDataParams->bUidComplete = 1;

            /* set default card timeout */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
                pDataParams->pHalDataParams,
                PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS,
                PHPAL_I14443P3A_TIMEOUT_DEFAULT_MS));
        }

        /* Copy SAK */
        pUidOut[0] = pRcvBuffer[0];
    }

    return PH_ADD_COMPCODE(status, PH_COMP_PAL_ISO14443P3A);
}

phStatus_t phpalI14443p3a_Sw_Select(
                                    phpalI14443p3a_Sw_DataParams_t * pDataParams,
                                    uint8_t bCascadeLevel,
                                    uint8_t * pUidIn,
                                    uint8_t * pSak
                                    )
{
    uint8_t PH_MEMLOC_REM bDummy;
    return phpalI14443p3a_Sw_Anticollision(pDataParams, bCascadeLevel, pUidIn, 0x40, pSak, &bDummy);
}

phStatus_t phpalI14443p3a_Sw_ActivateCard(
    phpalI14443p3a_Sw_DataParams_t * pDataParams,
    uint8_t * pUidIn,
    uint8_t bLenUidIn,
    uint8_t * pUidOut,
    uint8_t * pLenUidOut,
    uint8_t * pSak,
    uint8_t * pMoreCardsAvailable
    )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bCascadeLevel;
    uint8_t     PH_MEMLOC_COUNT bCascadeIndex;
    uint8_t     PH_MEMLOC_REM bUidIndex;
    uint8_t     PH_MEMLOC_REM bNvbUid;
    uint8_t     PH_MEMLOC_REM bAtqa[2];
    uint8_t     PH_MEMLOC_REM bUid[4];

    /* Parameter check */
    if ((bLenUidIn != 0) &&
        (bLenUidIn != 4) &&
        (bLenUidIn != 7) &&
        (bLenUidIn != 10))
    {
        /* Given UID length is invalid, return error */
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_ISO14443P3A);
    }

    /* Clear Uid */
    memset(bUid, 0x00, 4);  /* PRQA S 3200 */

    /* Clear Uid lengths */
    bUidIndex = 0;
    *pLenUidOut = 0;

    /* Clear the more cards available flag */
    *pMoreCardsAvailable = PH_OFF;

    /* UidIn is not given -> ReqA */
    if (bLenUidIn == 0)
    {
        status = phpalI14443p3a_Sw_RequestA(pDataParams, bAtqa);
    }
    /* UidIn is given -> WupA */
    else
    {
        status = phpalI14443p3a_Sw_WakeUpA(pDataParams, bAtqa);
    }

    /* Collision error may happen */
    if ((status & PH_ERR_MASK) == PH_ERR_COLLISION_ERROR)
    {
        /* Set the more cards available flag */
        *pMoreCardsAvailable = PH_ON;
    }
    /* Status check */
    else
    {
        PH_CHECK_SUCCESS(status);
    }

    /* Go through all cascade levels */
    for (bCascadeIndex = 0; bCascadeIndex < 3; bCascadeIndex++)
    {
        /* Set cascade level tags */
        switch (bCascadeIndex)
        {
        case 0:
            bCascadeLevel = PHPAL_I14443P3A_CASCADE_LEVEL_1;
            break;
        case 1:
            bCascadeLevel = PHPAL_I14443P3A_CASCADE_LEVEL_2;
            break;
        case 2:
            bCascadeLevel = PHPAL_I14443P3A_CASCADE_LEVEL_3;
            break;
        default:
            return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_PAL_ISO14443P3A);
        }

        /* Copy know Uid part if neccessary */
        if (bLenUidIn == (bUidIndex + 4))
        {
            /* Copy whole Uid if this is the only cascade level */
            memcpy(&bUid[0], &pUidIn[bUidIndex], 4);  /* PRQA S 3200 */

            /* [Incrementing Uid index would have no effect] */

            /* All bits except BCC are valid */
            bNvbUid = 0x40;
        }
        else if (bLenUidIn > (bUidIndex + 4))
        {
            /* Prepend cascade tag if we expect more cascade levels*/
            bUid[0] = PHPAL_I14443P3A_CASCADE_TAG;

            /* Only three more uid bytes are valid for this level */
            memcpy(&bUid[1], &pUidIn[bUidIndex], 3);  /* PRQA S 3200 */

            /* Increment Uid index */
            bUidIndex += 3;

            /* All bits except BCC are valid */
            bNvbUid = 0x40;
        }
        else
        {
            /* No Uid given */
            bNvbUid = 0;
        }

        /* Anticollision Loop */
        while (bNvbUid != 0x40)
        {
            /* Perform single anticollision command */
            status = phpalI14443p3a_Sw_Anticollision(pDataParams, bCascadeLevel, bUid, bNvbUid, bUid, &bNvbUid);

            /* Collision error occured, add one (zero-)bit to Uid */
            if ((status & PH_ERR_MASK) == PH_ERR_COLLISION_ERROR)
            {
                /* Set the more cards available flag */
                *pMoreCardsAvailable = PH_ON;

                /* Increment NvbUid by one bit */
                if ((bNvbUid & 0x07) < 7)
                {
                    bNvbUid++;
                }
                /* This is more difficult if we have to increment the bytecount */
                else
                {
                    bNvbUid = (uint8_t)((((bNvbUid & 0xF0) >> 4) + 1) << 4);
                }
            }
            else
            {
                /* Check success */
                PH_CHECK_SUCCESS(status);
            }
        }

        /* Select cascade level */
        PH_CHECK_SUCCESS_FCT(statusTmp, phpalI14443p3a_Sw_Select(pDataParams, bCascadeLevel, bUid, pSak));

        /* Cascade Bit is cleared -> no further cascade levels */
        if (!(pSak[0] & 0x04))
        {
            break;
        }
    }

    /* Return UID */
    memcpy(pUidOut, pDataParams->abUid, pDataParams->bUidLength);  /* PRQA S 3200 */
    *pLenUidOut = pDataParams->bUidLength;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_ISO14443P3A);
}

phStatus_t phpalI14443p3a_Sw_Exchange(
                                      phpalI14443p3a_Sw_DataParams_t * pDataParams,
                                      uint16_t wOption,
                                      uint8_t * pTxBuffer,
                                      uint16_t wTxLength,
                                      uint8_t ** ppRxBuffer,
                                      uint16_t * pRxLength
                                      )
{
    /* direct mapping of hal exchange function */
    return phhalHw_Exchange(
        pDataParams->pHalDataParams,
        wOption,
        pTxBuffer,
        wTxLength,
        ppRxBuffer,
        pRxLength);
}

phStatus_t phpalI14443p3a_Sw_RequestAEx(
                                        phpalI14443p3a_Sw_DataParams_t * pDataParams,
                                        uint8_t bReqCode,
                                        uint8_t * pAtqa
                                        )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM cmd[1];
    uint8_t *   PH_MEMLOC_REM pResp;
    uint16_t    PH_MEMLOC_REM wRespLength;

    /* Disable MIFARE(R) Crypto1 */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_DISABLE_MF_CRYPTO1,
        PH_ON));

    /* Reset default data rates */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_TXDATARATE,
        PHHAL_HW_RF_DATARATE_106));
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_RXDATARATE,
        PHHAL_HW_RF_DATARATE_106));

    /* Set selection timeout */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,
        PHPAL_I14443P3A_SELECTION_TIME_US + PHPAL_I14443P3A_EXT_TIME_US));

    /* Set RxDeafTime to 8 Bits */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_RXDEAFBITS, 8));

    /* Switch off CRC */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_TXCRC, PH_OFF));
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_RXCRC, PH_OFF));

    /* Only 7 bits are valid */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_TXLASTBITS, 7));

    /* Send ReqA command */
    cmd[0] = bReqCode;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Exchange(pDataParams->pHalDataParams, PH_EXCHANGE_DEFAULT, cmd, 1, &pResp, &wRespLength));

    /* Check and copy ATQA */
    if (wRespLength == PHPAL_I14443P3A_ATQA_LENGTH)
    {
        memcpy(pAtqa, pResp, PHPAL_I14443P3A_ATQA_LENGTH);  /* PRQA S 3200 */
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_ISO14443P3A);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_ISO14443P3A);
}

phStatus_t phpalI14443p3a_Sw_GetSerialNo(
    phpalI14443p3a_Sw_DataParams_t * pDataParams,
    uint8_t * pUidOut,
    uint8_t * pLenUidOut
    )
{
    /* Return an error if UID is not complete */
    if (!pDataParams->bUidComplete)
    {
        return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_PAL_ISO14443P3A);
    }
    
    /* Copy UID */
    memcpy(pUidOut, pDataParams->abUid, pDataParams->bUidLength);  /* PRQA S 3200 */
    *pLenUidOut = pDataParams->bUidLength;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_ISO14443P3A);
}

#endif /* NXPBUILD__PHPAL_I14443P3A_SW */
