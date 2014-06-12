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
* Software ICode EPC/UID Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:26:23 2011 $
*
* History:
*  CHu: Generated 8. September 2009
*
*/

#include <ph_Status.h>
#include <phTools.h>
#include <phhalHw.h>
#include <phpalEpcUid.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHPAL_EPCUID_SW

#include "phpalEpcUid_Sw.h"
#include "phpalEpcUid_Sw_Int.h"

phStatus_t phpalEpcUid_Sw_Init(
                               phpalEpcUid_Sw_DataParams_t * pDataParams,
                               uint16_t wSizeOfDataParams,
                               void * pHalDataParams
                               )
{
    /* Dataparam check */
    if (sizeof(phpalEpcUid_Sw_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_EPCUID);
    }

    /* Pointer check */
    PH_ASSERT_NULL (pDataParams);
    PH_ASSERT_NULL (pHalDataParams);

    /* init private data */
    pDataParams->wId            = PH_COMP_PAL_EPCUID | PHPAL_EPCUID_SW_ID;
    pDataParams->pHalDataParams = pHalDataParams;
    pDataParams->bUidValid      = PH_OFF;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_EPCUID);
}

phStatus_t phpalEpcUid_Sw_ActivateCard(
                                       phpalEpcUid_Sw_DataParams_t * pDataParams,
                                       uint8_t bTagType,
                                       uint8_t bNumSlots,
                                       uint8_t * pMask,
                                       uint8_t bMaskBitLength,
                                       uint8_t bHash,
                                       uint8_t * pRxBuffer,
                                       uint8_t * pRxLength,
                                       uint8_t * pMoreCardsAvailable
                                       )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    phStatus_t  PH_MEMLOC_REM statusReturned;
    uint8_t     PH_MEMLOC_REM bNumSlotsTmp;
    uint16_t    PH_MEMLOC_REM wNumSlotsDec;
    uint8_t     PH_MEMLOC_REM bCardsPresent;

    /* reset pMoreCardsAvailable flag */
    *pMoreCardsAvailable = PH_OFF;

    /* init. return status */
    statusReturned = PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);

    do
    {
        /* Reset card present state */
        bCardsPresent = PH_OFF;
        
        /* Start a new Response Round and scan slot 0 */
        status = phpalEpcUid_Sw_BeginRound(
            pDataParams,
            bTagType,
            bNumSlots,
            pMask,
            bMaskBitLength,
            bHash,
            pRxBuffer,
            pRxLength);

        /* Return on parameter error */
        if ((status & PH_ERR_MASK) == PH_ERR_INVALID_PARAMETER)
        {
            return status;
        }

        /* Calculate number of slots in decimal */
		wNumSlotsDec = 0x01;
        if (bNumSlots > PHPAL_EPCUID_NUMSLOTS_1)
        {
            bNumSlotsTmp = bNumSlots;
            do 
            {
                bNumSlotsTmp >>= 1;
                wNumSlotsDec <<= 1;
            } while (bNumSlotsTmp);

            wNumSlotsDec <<= 1;
        }
        bNumSlotsTmp = bNumSlots;

		/* Do for all further requested slots */
		while (wNumSlotsDec--)
		{
			/* Multiple labels found in current slot */
            if (((status & PH_ERR_MASK) == PH_ERR_COLLISION_ERROR) ||
                ((status & PH_ERR_MASK) == PH_ERR_INTEGRITY_ERROR))
			{
				bCardsPresent = PH_ON;
				*pMoreCardsAvailable = PH_ON;

                /* Store collision error in case it can't be resolved */
                if ((statusReturned & PH_ERR_MASK) == PH_ERR_SUCCESS)
                {
                    statusReturned = status;
                }
			}
            else
            {
                /* Store timeout error if integrity / collision error has not happened */
                if ((status & PH_ERR_MASK) == PH_ERR_IO_TIMEOUT)
                {
                    if ((statusReturned & PH_ERR_MASK) == PH_ERR_SUCCESS)
                    {
                        statusReturned = status;
                    }
                }
                /* Return on success or other errors */
                else
				{
					return status;
				}
			}

            /* Last slot -> send CloseSlotLast */
            if (wNumSlotsDec == 0)
            {
                /* Send CloseSlot command */
                PH_CHECK_SUCCESS_FCT(statusTmp, phpalEpcUid_Sw_CloseSlot(
                    pDataParams,
                    PHPAL_EPCUID_CLOSESLOT_LAST,
                    pRxBuffer,
                    pRxLength));
            }
            else
            {
                /* Send CloseSlot command */
                status = phpalEpcUid_Sw_CloseSlot(
                    pDataParams,
                    PHPAL_EPCUID_CLOSESLOT_NONLAST,
                    pRxBuffer,
                    pRxLength);
            }
        }

        /* Increment number of slots */
        bNumSlots = (bNumSlots << 1) | 0x01;
    }
    while ((bCardsPresent != PH_OFF) && (bNumSlotsTmp < PHPAL_EPCUID_NUMSLOTS_512));

    /* return error */
    return statusReturned;
}

phStatus_t phpalEpcUid_Sw_BeginRound(
                                     phpalEpcUid_Sw_DataParams_t * pDataParams,
                                     uint8_t bTagType,
                                     uint8_t bNumSlots,
                                     uint8_t * pMask,
                                     uint8_t bMaskBitLength,
                                     uint8_t bHash,
                                     uint8_t * pRxBuffer,
                                     uint8_t * pRxLength
                                     )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bCrc8;
    uint8_t     PH_MEMLOC_REM bBitCount;
    uint8_t     PH_MEMLOC_REM aCommand[PHPAL_EPCUID_IDD_LENGTH + 4];
    uint16_t    PH_MEMLOC_REM wCommandLen;
    uint16_t    PH_MEMLOC_REM wCommandBitLen;
    uint8_t *   PH_MEMLOC_REM pResponse;
    uint16_t    PH_MEMLOC_REM wResponseLen;

    /* Parameter check */
    switch (bNumSlots)
    {
    case PHPAL_EPCUID_NUMSLOTS_1:
    case PHPAL_EPCUID_NUMSLOTS_4:
    case PHPAL_EPCUID_NUMSLOTS_8:
    case PHPAL_EPCUID_NUMSLOTS_16:
    case PHPAL_EPCUID_NUMSLOTS_32:
    case PHPAL_EPCUID_NUMSLOTS_64:
    case PHPAL_EPCUID_NUMSLOTS_128:
    case PHPAL_EPCUID_NUMSLOTS_256:
    case PHPAL_EPCUID_NUMSLOTS_512:
        break;
    default:
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_EPCUID);
    }

    /* checks for EPC */
    if (bTagType == PHPAL_EPCUID_LABEL_EPC)
    {
        if (bMaskBitLength > (PHPAL_EPCUID_EPC_LENGTH << 3))
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_EPCUID);
        }

        /* Copy EPC mask */
        memcpy(pDataParams->LabelInfo.bEpc, pMask, bMaskBitLength >> 3); /* PRQA S 3200 */
    }
    /* checks for UID */
    else if (bTagType == PHPAL_EPCUID_LABEL_UID)
    {
        if (bMaskBitLength > (PHPAL_EPCUID_IDD_LENGTH << 3))
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_EPCUID);
        }

        /* Copy IDD mask */
        memcpy(pDataParams->LabelInfo.bIdd, pMask, bMaskBitLength >> 3); /* PRQA S 3200 */
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_EPCUID);
    }

    /* reset label data */
    pDataParams->bLabelType = bTagType;
    pDataParams->bMaskBitLength = bMaskBitLength;
    pDataParams->bUidValid = PH_OFF;

    /* Build first part of frame */
    aCommand[0] = PHPAL_EPCUID_SW_CMD_BEGINROUND;
    aCommand[1] = bMaskBitLength;

    /* Evaluate command length and copy mask */
    bBitCount = bMaskBitLength & 0x07;
    wCommandLen = (bBitCount == 0) ? (bMaskBitLength >> 3) : ((bMaskBitLength >> 3) + 1);
    memcpy(&aCommand[2], pMask, wCommandLen);  /* PRQA S 3200 */
    wCommandLen = wCommandLen + 2;

    /* append number of slots */
    if (bBitCount)
    {
        /* clear the last invalid bits of the mask */
        aCommand[wCommandLen - 1] &= (uint8_t) (0xFF << (8 - bBitCount));

        /* append number of slots */
        aCommand[wCommandLen - 1] |= (uint8_t) (bNumSlots >> bBitCount);
        aCommand[wCommandLen++] = (uint8_t) (bNumSlots << (8 - bBitCount));
    }
    else
    {
        aCommand[wCommandLen++] = bNumSlots;
    }

    /* Calculate full bit-length */
    wCommandBitLen = (bBitCount == 0) ? (wCommandLen << 3) : (((uint16_t)(wCommandLen - 1) << 3) + bBitCount);

    /* Calculate CRC for Epc */
    if (bTagType == PHPAL_EPCUID_LABEL_EPC)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phTools_CalculateCrc8(
            PH_TOOLS_CRC_OPTION_MSB_FIRST | PH_TOOLS_CRC_OPTION_BITWISE,
            PH_TOOLS_CRC8_PRESET_EPC,
            PH_TOOLS_CRC8_POLY_EPCUID,
            aCommand,
            wCommandBitLen,
            &bCrc8));
    }
    /* calculate CRC for Uid */
    else
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phTools_CalculateCrc8(
            PH_TOOLS_CRC_OPTION_MSB_FIRST | PH_TOOLS_CRC_OPTION_BITWISE,
            PH_TOOLS_CRC8_PRESET_UID,
            PH_TOOLS_CRC8_POLY_EPCUID,
            aCommand,
            wCommandBitLen,
            &bCrc8));
    }

    /* Insert CRC & Hashvalue if applicable */
    if (bBitCount)
    {
        /* Insert the crc */
        aCommand[wCommandLen - 1] |= bCrc8 >> bBitCount;
        aCommand[wCommandLen++] = bCrc8 << (8 - bBitCount);

        if (bTagType == PHPAL_EPCUID_LABEL_EPC)
        {
            /* Insert the hash value */
            aCommand[wCommandLen - 1] |= bHash >> bBitCount;
            aCommand[wCommandLen++] = bHash << (8 - bBitCount);
        }
    }
    else
    {
        /* Insert the crc */
        aCommand[wCommandLen++] = bCrc8;

        if (bTagType == PHPAL_EPCUID_LABEL_EPC)
        {
            /* Insert the hash value */
            aCommand[wCommandLen++] = bHash;
        }
    }

    /* Set TxLastBits to bBitCount */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_TXLASTBITS,
        bBitCount));

    /* set SSOF as start symbol */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams, 
        PHHAL_HW_CONFIG_SYMBOL_START,
        PHHAL_HW_SYMBOL_ICODEEPCUID_SSOF)
        );

    /* set CEOF as end symbol */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams, 
        PHHAL_HW_CONFIG_SYMBOL_END,
        PHHAL_HW_SYMBOL_ICODEEPCUID_CEOF)
        );

    /* Set RxWait */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_RXDEAFBITS,
        PHPAL_EPCUID_SW_BEGINROUND_DEAFTIME_ETU));

    /* Set the RxTimeout */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,
        PHPAL_EPCUID_SW_TIMEOUT_ANTICOLL_US));

    /* Exchange command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Exchange(
        pDataParams->pHalDataParams,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        wCommandLen,
        &pResponse,
        &wResponseLen));

    /* Parse response */
    PH_CHECK_SUCCESS_FCT(statusTmp, phpalEpcUid_Sw_ParseResponse(pDataParams, pResponse, wResponseLen));

    /* Return response */
    if (pDataParams->bLabelType == PHPAL_EPCUID_LABEL_EPC)
    {
        *pRxLength = PHPAL_EPCUID_EPC_LENGTH;
        memcpy(pRxBuffer, pDataParams->LabelInfo.bEpc, *pRxLength);  /* PRQA S 3200 */
    }
    else
    {
        *pRxLength = PHPAL_EPCUID_IDD_LENGTH;
        memcpy(pRxBuffer, pDataParams->LabelInfo.bIdd, *pRxLength);  /* PRQA S 3200 */
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_EPCUID);
}

phStatus_t phpalEpcUid_Sw_CloseSlot(
                                    phpalEpcUid_Sw_DataParams_t * pDataParams,
                                    uint8_t bOption,
                                    uint8_t * pRxBuffer,
                                    uint8_t * pRxLength
                                    )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM aCommand[1];
    uint8_t *   PH_MEMLOC_REM pResponse;
    uint16_t    PH_MEMLOC_REM wResponseLen;

    /* Set closeslot timeout*/
    if (bOption == PHPAL_EPCUID_CLOSESLOT_NONLAST)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
            pDataParams->pHalDataParams,
            PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,
            PHPAL_EPCUID_SW_TIMEOUT_ANTICOLL_US));
    }
    /* Set minimum timeout */
    else if (bOption == PHPAL_EPCUID_CLOSESLOT_LAST)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
            pDataParams->pHalDataParams,
            PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,
            1));
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_EPCUID);
    }

    /* set CS as start symbol */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_SYMBOL_START,
        PHHAL_HW_SYMBOL_ICODEEPCUID_CS));

    /* no stop symbol */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_SYMBOL_END,
        PHHAL_HW_SYMBOL_ICODEEPCUID_CEOF));

    /* Set RxWait */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_RXDEAFBITS,
        PHPAL_EPCUID_SW_DEAFTIME_DEFAULT_ETU));

    /* Exchange command */
    status = phhalHw_Exchange(
        pDataParams->pHalDataParams,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        0,
        &pResponse,
        &wResponseLen);

    if (bOption == PHPAL_EPCUID_CLOSESLOT_NONLAST)
    {
        /* Return on error */
        PH_CHECK_SUCCESS(status);

        /* Parse response */
        PH_CHECK_SUCCESS_FCT(statusTmp, phpalEpcUid_Sw_ParseResponse(pDataParams, pResponse, wResponseLen));

        /* Return response */
        if (pDataParams->bLabelType == PHPAL_EPCUID_LABEL_EPC)
        {
            *pRxLength = PHPAL_EPCUID_EPC_LENGTH;
            memcpy(pRxBuffer, pDataParams->LabelInfo.bEpc, *pRxLength);  /* PRQA S 3200 */
        }
        else
        {
            *pRxLength = PHPAL_EPCUID_IDD_LENGTH;
            memcpy(pRxBuffer, pDataParams->LabelInfo.bIdd, *pRxLength);  /* PRQA S 3200 */
        }
    }
    else
    {
        /* Reset received length */
        if (pRxLength)
        {
            *pRxLength = 0;
        }

        /* Timeout is the correct behaviour */
        if ((status & PH_ERR_MASK) != PH_ERR_IO_TIMEOUT)
        {
            if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
            {
                /* if data was received return an error */
                return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_EPCUID);
            }
            else
            {
                /* Return the received error */
                return status;
            }
        }
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_EPCUID);
}

phStatus_t phpalEpcUid_Sw_FixSlot(
                                  phpalEpcUid_Sw_DataParams_t * pDataParams,
                                  uint8_t bTagType,
                                  uint8_t * pMask,
                                  uint8_t bMaskBitLength
                                  )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM aCommand[2];
    uint8_t *   PH_MEMLOC_REM pResponse;
    uint16_t    PH_MEMLOC_REM wResponseLen;
    uint8_t     PH_MEMLOC_REM bResponseLen;
    uint16_t    PH_MEMLOC_REM wCrc16;

    /* checks for EPC */
    if (bTagType == PHPAL_EPCUID_LABEL_EPC)
    {
        if (bMaskBitLength != (PHPAL_EPCUID_EPC_LENGTH << 3))
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_EPCUID);
        }
    }
    /* checks for UID */
    else if (bTagType == PHPAL_EPCUID_LABEL_UID)
    {
        if (bMaskBitLength != (PHPAL_EPCUID_IDD_LENGTH << 3))
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_EPCUID);
        }
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_EPCUID);
    }

    /* Set TxWait */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams, 
        PHHAL_HW_CONFIG_TXWAIT_US,
        PHPAL_EPCUID_SW_T1_MIN_US));

    /* Execute Begin-Round with only 1 slot */
    PH_CHECK_SUCCESS_FCT(statusTmp, phpalEpcUid_Sw_BeginRound(
        pDataParams,
        bTagType,
        PHPAL_EPCUID_NUMSLOTS_1,
        pMask,
        bMaskBitLength,
        0x00,
        pDataParams->LabelInfo.bIdd,
        &bResponseLen));

    /* Calculate CRC */
    if (pDataParams->bLabelType == PHPAL_EPCUID_LABEL_EPC)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phTools_CalculateCrc16(
            PH_TOOLS_CRC_OPTION_MSB_FIRST | PH_TOOLS_CRC_OPTION_OUPUT_INVERTED,
            PH_TOOLS_CRC16_PRESET_EPCUID,
            PH_TOOLS_CRC16_POLY_EPCUID,
            pDataParams->LabelInfo.bEpc,
            PHPAL_EPCUID_EPC_LENGTH,
            &wCrc16));
    }
    else
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phTools_CalculateCrc16(
            PH_TOOLS_CRC_OPTION_MSB_FIRST | PH_TOOLS_CRC_OPTION_OUPUT_INVERTED,
            PH_TOOLS_CRC16_PRESET_EPCUID,
            PH_TOOLS_CRC16_POLY_EPCUID,
            &pDataParams->LabelInfo.bIdd[PHPAL_EPCUID_EPC_LENGTH + 2],
            PHPAL_EPCUID_IDD_LENGTH - (PHPAL_EPCUID_EPC_LENGTH + 2),
            &wCrc16));
    }

    /* Build fix-slot command (2 crc bytes) */
    aCommand[0] = (uint8_t)(wCrc16 >> 8);
    aCommand[1] = (uint8_t)wCrc16;

    /* set LSOF as start symbol */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams, 
        PHHAL_HW_CONFIG_SYMBOL_START,
        PHHAL_HW_SYMBOL_ICODEEPCUID_LSOF));

    /* set CEOF as end symbol */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams, 
        PHHAL_HW_CONFIG_SYMBOL_END,
        PHHAL_HW_SYMBOL_ICODEEPCUID_CEOF));

    /* Set RxWait */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_RXDEAFBITS,
        PHPAL_EPCUID_SW_DEAFTIME_DEFAULT_ETU));

    /* Set fix-slot timeout */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,
        1));

    /* Send the command */
    status = phhalHw_Exchange(
        pDataParams->pHalDataParams,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        2,
        &pResponse,
        &wResponseLen);

    /* Timeout is the correct behaviour */
    if ((status & PH_ERR_MASK) != PH_ERR_IO_TIMEOUT)
    {
        if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
        {
            /* if data was received return an error */
            return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_EPCUID);
        }
        else
        {
            /* Return the received error */
            return status;
        }
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_EPCUID);
}

phStatus_t phpalEpcUid_Sw_Write(
                                phpalEpcUid_Sw_DataParams_t * pDataParams,
                                uint8_t bTagType,
                                uint8_t bBlockNo,
                                uint8_t bData
                                )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM aCommand[4];
    uint8_t *   PH_MEMLOC_REM pResponse;
    uint16_t    PH_MEMLOC_REM wResponseLen;

    /* checks for EPC */
    if (bTagType == PHPAL_EPCUID_LABEL_EPC)
    {
        if (bBlockNo > PHPAL_EPCUID_EPC_MAXBLOCKNUMBER)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_EPCUID);
        }
    }
    /* checks for UID */
    else if (bTagType == PHPAL_EPCUID_LABEL_UID)
    {
        if (bBlockNo > PHPAL_EPCUID_UID_MAXBLOCKNUMBER)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_EPCUID);
        }
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_EPCUID);
    }

    /* set SSOF as start symbol */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams, 
        PHHAL_HW_CONFIG_SYMBOL_START,
        PHHAL_HW_SYMBOL_ICODEEPCUID_SSOF)
        );

    /* set CEOF as end symbol */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams, 
        PHHAL_HW_CONFIG_SYMBOL_END,
        PHHAL_HW_SYMBOL_ICODEEPCUID_CEOF)
        );

    /* Set timeout to 6.4ms */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,
        PHPAL_EPCUID_SW_TIMEOUT_DEFAULT_US));

    /* Build command frame */
    aCommand[0] = PHPAL_EPCUID_SW_CMD_WRITE;
    aCommand[1] = bBlockNo;
    aCommand[2] = bData;

    /* Calculate CRC */
    if (bTagType == PHPAL_EPCUID_LABEL_EPC)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phTools_CalculateCrc8(
            PH_TOOLS_CRC_OPTION_MSB_FIRST,
            PH_TOOLS_CRC8_PRESET_EPC,
            PH_TOOLS_CRC8_POLY_EPCUID,
            aCommand,
            3,
            &aCommand[3]));
    }
    else
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phTools_CalculateCrc8(
            PH_TOOLS_CRC_OPTION_MSB_FIRST,
            PH_TOOLS_CRC8_PRESET_UID,
            PH_TOOLS_CRC8_POLY_EPCUID,
            aCommand,
            3,
            &aCommand[3]));
    }

    /* Send the command */
    status = phhalHw_Exchange(
        pDataParams->pHalDataParams,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        4,
        &pResponse,
        &wResponseLen);

    /* Timeout is the correct behaviour */
    if ((status & PH_ERR_MASK) != PH_ERR_IO_TIMEOUT)
    {
        if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
        {
            /* if data was received return an error */
            return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_EPCUID);
        }
        else
        {
            /* Return the received error */
            return status;
        }
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_EPCUID);
}

phStatus_t phpalEpcUid_Sw_Destroy(
                                  phpalEpcUid_Sw_DataParams_t * pDataParams,
                                  uint8_t bTagType,
                                  uint8_t * pData,
                                  uint8_t bDataLength,
                                  uint8_t * pDestroyCode
                                  )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bCrc8;
    uint8_t     PH_MEMLOC_REM aCommand[1];
    uint8_t *   PH_MEMLOC_REM pResponse;
    uint16_t    PH_MEMLOC_REM wResponseLen;

    /* checks for EPC */
    if (bTagType == PHPAL_EPCUID_LABEL_EPC)
    {
        if (bDataLength != PHPAL_EPCUID_EPC_LENGTH)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_EPCUID);
        }
    }
    /* checks for UID */
    else if (bTagType == PHPAL_EPCUID_LABEL_UID)
    {
        if (bDataLength != PHPAL_EPCUID_IDD_LENGTH)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_EPCUID);
        }
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_EPCUID);
    }

    /* set SSOF as start symbol */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams, 
        PHHAL_HW_CONFIG_SYMBOL_START,
        PHHAL_HW_SYMBOL_ICODEEPCUID_SSOF)
        );

    /* set CEOF as end symbol */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams, 
        PHHAL_HW_CONFIG_SYMBOL_END,
        PHHAL_HW_SYMBOL_ICODEEPCUID_CEOF)
        );

    /* Set timeout to 6.4ms */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,
        PHPAL_EPCUID_SW_TIMEOUT_DEFAULT_US));

    /* Set command code */
    aCommand[0] = PHPAL_EPCUID_SW_CMD_DESTROY;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Exchange(
        pDataParams->pHalDataParams,
        PH_EXCHANGE_BUFFER_FIRST,
        aCommand,
        1,
        NULL,
        NULL));

    /* Append EPC/IDD */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Exchange(
        pDataParams->pHalDataParams,
        PH_EXCHANGE_BUFFER_CONT,
        pData,
        (uint16_t)bDataLength,
        NULL,
        NULL));

    /* Append Destroy Code */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Exchange(
        pDataParams->pHalDataParams,
        PH_EXCHANGE_BUFFER_CONT,
        pDestroyCode,
        PHPAL_EPCUID_DESTROYCODE_LENGTH,
        NULL,
        NULL));

    /* Calculate CRC over command */
    if (bTagType == PHPAL_EPCUID_LABEL_EPC)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phTools_CalculateCrc8(
            PH_TOOLS_CRC_OPTION_MSB_FIRST,
            PH_TOOLS_CRC8_PRESET_EPC,
            PH_TOOLS_CRC8_POLY_EPCUID,
            aCommand,
            1,
            &bCrc8));
    }
    else
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phTools_CalculateCrc8(
            PH_TOOLS_CRC_OPTION_MSB_FIRST,
            PH_TOOLS_CRC8_PRESET_UID,
            PH_TOOLS_CRC8_POLY_EPCUID,
            aCommand,
            1,
            &bCrc8));
    }

    /* Calculate CRC over data */
    PH_CHECK_SUCCESS_FCT(statusTmp, phTools_CalculateCrc8(
        PH_TOOLS_CRC_OPTION_MSB_FIRST,
        bCrc8,
        PH_TOOLS_CRC8_POLY_EPCUID,
        pData,
        (uint16_t)bDataLength,
        &bCrc8));

    /* Calculate CRC over destroy-code */
    PH_CHECK_SUCCESS_FCT(statusTmp, phTools_CalculateCrc8(
        PH_TOOLS_CRC_OPTION_MSB_FIRST,
        bCrc8,
        PH_TOOLS_CRC8_POLY_EPCUID,
        pDestroyCode,
        PHPAL_EPCUID_DESTROYCODE_LENGTH,
        &bCrc8));

    /* Append CRC and perform exchange */
    aCommand[0] = bCrc8;
    status = phhalHw_Exchange(
        pDataParams->pHalDataParams,
        PH_EXCHANGE_BUFFER_LAST,
        aCommand,
        1,
        &pResponse,
        &wResponseLen);

    /* Timeout is the correct behaviour */
    if ((status & PH_ERR_MASK) != PH_ERR_IO_TIMEOUT)
    {
        if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
        {
            /* if data was received return an error */
            return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_EPCUID);
        }
        else
        {
            /* Return the received error */
            return status;
        }
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_EPCUID);
}

phStatus_t phpalEpcUid_Sw_GetSerialNo(
                                      phpalEpcUid_Sw_DataParams_t * pDataParams,
                                      uint8_t * pUidOut,
                                      uint8_t * pLenUidOut
                                      )
{
    if (pDataParams->bUidValid != PH_OFF)
    {
        if (pDataParams->bLabelType == PHPAL_EPCUID_LABEL_EPC)
        {
            *pLenUidOut = PHPAL_EPCUID_EPC_LENGTH;
            memcpy(pUidOut, pDataParams->LabelInfo.bEpc, *pLenUidOut); /* PRQA S 3200 */
        }
        else
        {
            *pLenUidOut = PHPAL_EPCUID_IDD_LENGTH;
            memcpy(pUidOut, pDataParams->LabelInfo.bIdd, *pLenUidOut); /* PRQA S 3200 */
        }

        return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_EPCUID);
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_PAL_EPCUID);
    }
}

phStatus_t phpalEpcUid_Sw_ParseResponse(
                                        phpalEpcUid_Sw_DataParams_t * pDataParams,
                                        uint8_t * pRxBuffer,
                                        uint16_t wRxLength
                                        )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *   PH_MEMLOC_REM pEpcIddStorage;
    uint16_t    PH_MEMLOC_REM wCrc16;
	uint16_t	PH_MEMLOC_REM wLabelLenght;

    /* Response check */
    if ((
        (pDataParams->bLabelType == PHPAL_EPCUID_LABEL_EPC) &&
        (wRxLength != (PHPAL_EPCUID_EPC_LENGTH + 2 - (pDataParams->bMaskBitLength >> 3)))
        ) ||
        (
        (pDataParams->bLabelType == PHPAL_EPCUID_LABEL_UID) &&
        (wRxLength != (PHPAL_EPCUID_IDD_LENGTH + 2 - (pDataParams->bMaskBitLength >> 3)))
        ))
    {
        pDataParams->bUidValid = PH_OFF;
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_EPCUID);
    }

    /* Check where to store EPC/IDD */
    if (pDataParams->bLabelType == PHPAL_EPCUID_LABEL_EPC)
    {
        /* Copy EPC */
        memcpy(&pDataParams->LabelInfo.bEpc[pDataParams->bMaskBitLength >> 3], pRxBuffer, wRxLength - 2);  /* PRQA S 3200 */

        /* Set data paramters for CRC calculation */
        pEpcIddStorage = pDataParams->LabelInfo.bEpc;
		wLabelLenght = PHPAL_EPCUID_EPC_LENGTH;
    }
    else
    {
        /* Copy IDD */
        memcpy(&pDataParams->LabelInfo.bIdd[pDataParams->bMaskBitLength >> 3], pRxBuffer, wRxLength - 2);  /* PRQA S 3200 */

        /* Set data paramters for CRC calculation */
        pEpcIddStorage = &pDataParams->LabelInfo.bIdd[PHPAL_EPCUID_EPC_LENGTH + 2];
		wLabelLenght = PHPAL_EPCUID_IDD_LENGTH - (PHPAL_EPCUID_EPC_LENGTH + 2);
    }

    /* Calculate CRC */
    PH_CHECK_SUCCESS_FCT(statusTmp, phTools_CalculateCrc16(
        PH_TOOLS_CRC_OPTION_MSB_FIRST | PH_TOOLS_CRC_OPTION_OUPUT_INVERTED,
        PH_TOOLS_CRC16_PRESET_EPCUID,
        PH_TOOLS_CRC16_POLY_EPCUID,
        pEpcIddStorage,
        wLabelLenght,
        &wCrc16));

    /* Check CRC */
    if (((uint8_t)(wCrc16 >> 8) != pRxBuffer[wRxLength-2]) || ((uint8_t)(wCrc16) != pRxBuffer[wRxLength-1]))
    {
        pDataParams->bUidValid = PH_OFF;
        return PH_ADD_COMPCODE(PH_ERR_INTEGRITY_ERROR, PH_COMP_PAL_EPCUID);
    }

    pDataParams->bUidValid = PH_ON;
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_EPCUID);
}

#endif /* NXPBUILD__PHPAL_EPCUID_SW */
