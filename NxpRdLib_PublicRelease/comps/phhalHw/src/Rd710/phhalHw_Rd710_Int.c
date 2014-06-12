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
* RD710 specific HAL-Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.6 $
* $Date: Thu Jun 30 11:04:56 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/
#include <phhalHw.h>
#include <phbalReg.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHHAL_HW_RD710

#include "phhalHw_Rd710.h"
#include "phhalHw_Rd710_Int.h"
#include <phhalHw_Rd710_Cmd.h>

phStatus_t phhalHw_Rd710_CommandReader(
                                       phhalHw_Rd710_DataParams_t * pDataParams,
                                       uint16_t wCmd,
                                       uint16_t wOption, 
                                       uint8_t * pTxBuffer,
                                       uint16_t wTxLength,
                                       uint8_t ** ppRxBuffer,
                                       uint16_t * pRxLength
                                       )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *   PH_MEMLOC_REM pTxBufferTmp;
    uint16_t    PH_MEMLOC_REM wTxBufferTmpSize;
    uint16_t    PH_MEMLOC_REM wTxBufferTmpOffset;
    uint8_t *   PH_MEMLOC_REM pRxBufferTmp;
    uint16_t    PH_MEMLOC_REM wRxBufferTmpSize;
    uint16_t    PH_MEMLOC_REM wRxBufferTmpLength;
    uint8_t     PH_MEMLOC_REM bUseBuffering;
    uint8_t     PH_MEMLOC_REM abTxBufferBackup[PHHAL_HW_RD710_RESERVED_BUFFER_LEN];
    uint8_t     PH_MEMLOC_REM abRxBufferBackup[PHHAL_HW_RD710_FRAME_HEADER_LEN];
    uint16_t    PH_MEMLOC_REM wTransmitStart = 0;
    uint16_t    PH_MEMLOC_REM wReceiveStart = 0;
    /* Check if buffering needs to be used */
    switch (wCmd)
    {
    case PHHAL_HW_RD710_CMD_EXCHANGE:
    case PHHAL_HW_RD710_CMD_I14443P3A_EXCHANGE:
    case PHHAL_HW_RD710_CMD_I14443P4_EXCHANGE:
    case PHHAL_HW_RD710_CMD_MIFARE_EXCHANGE_L3:
    case PHHAL_HW_RD710_CMD_MIFARE_EXCHANGE_L4:
    case PHHAL_HW_RD710_CMD_MIFARE_EXCHANGE_PC:
    case PHHAL_HW_RD710_CMD_MIFARE_EXCHANGE_RAW:
        bUseBuffering = PH_OFF;
        break;
    default:
        bUseBuffering = PH_ON;
        break;
    }

    wTransmitStart = PHHAL_HW_RD710_RESERVED_BUFFER_LEN + pDataParams->wTxBufStartPos;
    wReceiveStart = PHHAL_HW_RD710_FRAME_HEADER_LEN + pDataParams->wRxBufStartPos;

    /* Init. temporary status (satisfy compiler) */
    statusTmp = PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);

    /* */
    /* Evaluate temporary buffer */
    /* */
    if (bUseBuffering != PH_OFF)
    {
        /* TxBuffer equals RxBuffer */
        if (pDataParams->pTxBuffer == pDataParams->pRxBuffer)
        {
            /* Start at TxLenght if neccessary */
            if (pDataParams->wTxBufLen >= pDataParams->wRxBufLen)
            {
                pTxBufferTmp = &pDataParams->pTxBuffer[pDataParams->wTxBufLen + wTransmitStart];
                wTxBufferTmpSize = pDataParams->wTxBufSize - pDataParams->wTxBufLen - wTransmitStart;
            }
            /* Else start at RxLenght */
            else
            {
                pTxBufferTmp = &pDataParams->pRxBuffer[pDataParams->wRxBufLen + wTransmitStart];
                wTxBufferTmpSize = pDataParams->wRxBufSize - pDataParams->wRxBufLen - wTransmitStart;
            }

            /* RxBuffer uses same buffer position as TxBuffer */
            pRxBufferTmp = pTxBufferTmp;
            wRxBufferTmpSize = wTxBufferTmpSize;
        }
        /* Buffers are different */
        else
        {
            pTxBufferTmp = &pDataParams->pTxBuffer[pDataParams->wTxBufLen + wTransmitStart];
            wTxBufferTmpSize = pDataParams->wTxBufSize - pDataParams->wTxBufLen - wTransmitStart;
            pRxBufferTmp = &pDataParams->pRxBuffer[pDataParams->wRxBufLen + wReceiveStart];
            wRxBufferTmpSize = pDataParams->wRxBufSize - pDataParams->wRxBufLen - wReceiveStart;
        }

        /* If a buffered command begins, reset TxBufferStart position */
        if (!(wOption & PH_EXCHANGE_LEAVE_BUFFER_BIT))
        {
            pDataParams->wTxBufStart = pDataParams->wTxBufLen;
        }

        /* If a buffered command is being sent, save Tx-/RxBuffer Contents */
        if (!(wOption & PH_EXCHANGE_BUFFERED_BIT))
        {
            memcpy(abTxBufferBackup, pTxBufferTmp - PHHAL_HW_RD710_RESERVED_BUFFER_LEN, PHHAL_HW_RD710_RESERVED_BUFFER_LEN);  /* PRQA S 3200 */
            memcpy(abRxBufferBackup, pRxBufferTmp - PHHAL_HW_RD710_FRAME_HEADER_LEN, PHHAL_HW_RD710_FRAME_HEADER_LEN);  /* PRQA S 3200 */
        }
    }
    else
    {
        pTxBufferTmp = &pDataParams->pTxBuffer[wTransmitStart];
        wTxBufferTmpSize = pDataParams->wTxBufSize;
        pRxBufferTmp = &pDataParams->pRxBuffer[wReceiveStart];
        wRxBufferTmpSize = pDataParams->wRxBufSize - wReceiveStart;
        pDataParams->wTxBufLen = 0;
        pDataParams->wRxBufLen = 0;
    }

    /* Buffer overflow check */
    if (wTxLength > wTxBufferTmpSize)
    {
        pDataParams->wTxBufLen = pDataParams->wTxBufStart;
        return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
    }

    /* Copy transmit buffer */
    memcpy(pTxBufferTmp, pTxBuffer, wTxLength);  /* PRQA S 3200 */    

    /* Set Buffer pointer to start */
    if (bUseBuffering != PH_OFF)
    {
        /* Increment TxLenght */
        pDataParams->wTxBufLen = pDataParams->wTxBufLen + wTxLength;

        /* Shall we already perform the Exchange? */
        if (wOption & PH_EXCHANGE_BUFFERED_BIT)
        {
            return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
        }

        /* Save buffer length then Reset our transmit buffer contents */
        wTxLength = pDataParams->wTxBufLen - pDataParams->wTxBufStart;
        pDataParams->wTxBufLen = pDataParams->wTxBufStart;
    }

    /* Move RxBuffer pointer to start of receive header */
    pRxBufferTmp -= PHHAL_HW_RD710_FRAME_HEADER_LEN;
    wRxBufferTmpSize = wRxBufferTmpSize + PHHAL_HW_RD710_FRAME_HEADER_LEN;

    switch (wCmd)
    {
        /* CID MANAGER */
    case PHHAL_HW_RD710_CMD_CID_INIT:
    case PHHAL_HW_RD710_CMD_CID_GET_FREE_CID:
    case PHHAL_HW_RD710_CMD_CID_FREE_CID:

        /* KEYSTORE */
    case PHHAL_HW_RD710_CMD_KS_INIT:
    case PHHAL_HW_RD710_CMD_KS_FORMAT_KEY_ENTRY:
    case PHHAL_HW_RD710_CMD_KS_SET_KEY:
    case PHHAL_HW_RD710_CMD_KS_SET_KEY_AT_POS:
    case PHHAL_HW_RD710_CMD_KS_SET_KUC:
    case PHHAL_HW_RD710_CMD_KS_SET_FULL_KEY_ENTRY:
    case PHHAL_HW_RD710_CMD_KS_GET_KEY_ENTRY:
    case PHHAL_HW_RD710_CMD_KS_GET_KEY:
    case PHHAL_HW_RD710_CMD_KS_SET_CONFIG:
    case PHHAL_HW_RD710_CMD_KS_GET_CONFIG:
    case PHHAL_HW_RD710_CMD_KS_CHANGE_KUC:
    case PHHAL_HW_RD710_CMD_KS_GET_KUC:
    case PHHAL_HW_RD710_CMD_KS_SET_CONFIG_BUFFER:
    case PHHAL_HW_RD710_CMD_KS_GET_CONFIG_BUFFER:

        /* READER OPERATION */
    case PHHAL_HW_RD710_CMD_RD_OPS_LED_OFF:
    case PHHAL_HW_RD710_CMD_RD_OPS_LED_ON:
    case PHHAL_HW_RD710_CMD_RD_OPS_RESET_READER:
    case PHHAL_HW_RD710_CMD_RD_OPS_RESET_FACTORY:
    case PHHAL_HW_RD710_CMD_RD_OPS_SET_CFG_OPTION:
    case PHHAL_HW_RD710_CMD_RD_OPS_GET_READER_STATUS:
    case PHHAL_HW_RD710_CMD_RD_OPS_READ_REGISTER:
    case PHHAL_HW_RD710_CMD_RD_OPS_WRITE_REGISTER:
    case PHHAL_HW_RD710_CMD_RD_OPS_FIELD_ON:
    case PHHAL_HW_RD710_CMD_RD_OPS_FIELD_OFF:
    case PHHAL_HW_RD710_CMD_RD_OPS_GET_CFG_OPTION:
    case PHHAL_HW_RD710_CMD_RD_OPS_SET_PCSC_MODE:

        /* CONTACT CARD COMMUNICATION */
    case PHHAL_HW_RD710_CMD_CC_ACTIVATE:
    case PHHAL_HW_RD710_CMD_CC_COLD_RESET:
    case PHHAL_HW_RD710_CMD_CC_WARM_RESET:
    case PHHAL_HW_RD710_CMD_CC_STOP_CLOCK:
    case PHHAL_HW_RD710_CMD_CC_START_CLOCK:
    case PHHAL_HW_RD710_CMD_CC_DEACTIVATE:
    case PHHAL_HW_RD710_CMD_CC_PRESENCE_CHECK:
    case PHHAL_HW_RD710_CMD_CC_TRANSMIT_DATA:
    case PHHAL_HW_RD710_CMD_CC_SEND_PPS:

        wTxBufferTmpOffset = 4;
        pTxBufferTmp -= wTxBufferTmpOffset;
        pTxBufferTmp[0] = (uint8_t)((uint16_t)wCmd >> 8);
        pTxBufferTmp[1] = (uint8_t)wCmd;
        pTxBufferTmp[2] = (uint8_t)(wTxLength);
        pTxBufferTmp[3] = (uint8_t)(wTxLength >> 8);
        wTxLength = wTxLength + wTxBufferTmpOffset;
        break;

        /* HAL */
    case PHHAL_HW_RD710_CMD_RD_OPS_FIELD_RESET:
    case PHHAL_HW_RD710_CMD_INIT_HAL:
    case PHHAL_HW_RD710_CMD_SET_CONFIG:
    case PHHAL_HW_RD710_CMD_GET_CONFIG:
    case PHHAL_HW_RD710_CMD_APPLY_PROT_SETTINGS:
    case PHHAL_HW_RD710_CMD_WAIT:
    case PHHAL_HW_RD710_CMD_MFC_AUTH:
    case PHHAL_HW_RD710_CMD_EXECUTE:
    case PHHAL_HW_RD710_CMD_MFC_AUTH_KEY_NO:

        /* I14443P3A */
    case PHHAL_HW_RD710_CMD_I14443P3A_INIT:
    case PHHAL_HW_RD710_CMD_I14443P3A_REQUEST_A:
    case PHHAL_HW_RD710_CMD_I14443P3A_WAKEUP_A:
    case PHHAL_HW_RD710_CMD_I14443P3A_HALT_A:
    case PHHAL_HW_RD710_CMD_I14443P3A_ANTICOLLISION:
    case PHHAL_HW_RD710_CMD_I14443P3A_SELECT:
    case PHHAL_HW_RD710_CMD_I14443P3A_ACTIVATE_CARD:
    case PHHAL_HW_RD710_CMD_I14443P3A_GET_SERIAL_NO:

        /* I14443P4A */
    case PHHAL_HW_RD710_CMD_I14443P4A_INIT:
    case PHHAL_HW_RD710_CMD_I14443P4A_RATS:
    case PHHAL_HW_RD710_CMD_I14443P4A_PPS:
    case PHHAL_HW_RD710_CMD_I14443P4A_ACTIVATE_CARD:
    case PHHAL_HW_RD710_CMD_I14443P4A_GET_PROTOCOL_PARAMS:

        /* I14443P4 */
    case PHHAL_HW_RD710_CMD_I14443P4_INIT:
    case PHHAL_HW_RD710_CMD_I14443P4_SET_PROTOCOL:
    case PHHAL_HW_RD710_CMD_I14443P4_RESET_PROTOCOL:
    case PHHAL_HW_RD710_CMD_I14443P4_DESELECT:
    case PHHAL_HW_RD710_CMD_I14443P4_PRES_CHECK:
    case PHHAL_HW_RD710_CMD_I14443P4_SET_CONFIG:
    case PHHAL_HW_RD710_CMD_I14443P4_GET_CONFIG:

        /* MIFARE */
    case PHHAL_HW_RD710_CMD_MIFARE_INIT:
    case PHHAL_HW_RD710_CMD_MIFARE_MFC_AUTH:
    case PHHAL_HW_RD710_CMD_MIFARE_MFC_AUTH_KEY:

        wTxBufferTmpOffset = 5;
        pTxBufferTmp -= wTxBufferTmpOffset;
        pTxBufferTmp[0] = (uint8_t)((uint16_t)wCmd >> 8);
        pTxBufferTmp[1] = (uint8_t)wCmd;
        pTxBufferTmp[2] = (uint8_t)(wTxLength+1);
        pTxBufferTmp[3] = (uint8_t)((wTxLength+1) >> 8);
        pTxBufferTmp[4] = pDataParams->bSlotNumber;
        wTxLength = wTxLength + wTxBufferTmpOffset;
        break;

    case PHHAL_HW_RD710_CMD_EXCHANGE:
    case PHHAL_HW_RD710_CMD_I14443P3A_EXCHANGE:
    case PHHAL_HW_RD710_CMD_I14443P4_EXCHANGE:
    case PHHAL_HW_RD710_CMD_MIFARE_EXCHANGE_L3:
    case PHHAL_HW_RD710_CMD_MIFARE_EXCHANGE_L4:
    case PHHAL_HW_RD710_CMD_MIFARE_EXCHANGE_PC:

        wTxBufferTmpOffset = 7;
        pTxBufferTmp -= wTxBufferTmpOffset;
        pTxBufferTmp[0] = (uint8_t)((uint16_t)wCmd >> 8);
        pTxBufferTmp[1] = (uint8_t)wCmd;
        pTxBufferTmp[2] = (uint8_t)(wTxLength+3);
        pTxBufferTmp[3] = (uint8_t)((wTxLength+3) >> 8);
        pTxBufferTmp[4] = pDataParams->bSlotNumber;
        pTxBufferTmp[5] = (uint8_t)(wOption);
        pTxBufferTmp[6] = (uint8_t)(wOption >> 8);
        wTxLength = wTxLength + wTxBufferTmpOffset;
        break;

    case PHHAL_HW_RD710_CMD_MIFARE_EXCHANGE_RAW:

        wTxBufferTmpOffset = 8;
        pTxBufferTmp -= wTxBufferTmpOffset;
        pTxBufferTmp[0] = (uint8_t)((uint16_t)wCmd >> 8);
        pTxBufferTmp[1] = (uint8_t)wCmd;
        pTxBufferTmp[2] = (uint8_t)(wTxLength+4);
        pTxBufferTmp[3] = (uint8_t)((wTxLength+4) >> 8);
        pTxBufferTmp[4] = pDataParams->bSlotNumber;
        pTxBufferTmp[5] = (uint8_t)(wOption);
        pTxBufferTmp[6] = (uint8_t)(wOption >> 8);
        pTxBufferTmp[7] = pDataParams->bTxLastBits;
        wTxLength = wTxLength + wTxBufferTmpOffset;
        break;

    default:
        return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_HAL);
    }

    /* Perform command exchange */
    status = phbalReg_Exchange(
        pDataParams->pBalDataParams,
        PH_EXCHANGE_DEFAULT,
        pTxBufferTmp,
        wTxLength,
        wRxBufferTmpSize,
        pRxBufferTmp,
        &wRxBufferTmpLength);

    /* Frame check */
    if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
    {
        /* Frame has to be at least 6 bytes */
        if (wRxBufferTmpLength < PHHAL_HW_RD710_FRAME_HEADER_LEN)
        {
            status = PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
        }
        else
        {
            /* Retrieve length */
            wRxBufferTmpSize = pRxBufferTmp[PHHAL_HW_RD710_FRAME_LEN_POS];
            wRxBufferTmpSize |= ((uint16_t)pRxBufferTmp[PHHAL_HW_RD710_FRAME_LEN_POS+1] << 8);

            /* Length should match */
            if ((wRxBufferTmpLength - PHHAL_HW_RD710_FRAME_HEADER_LEN) != wRxBufferTmpSize)
            {
                status = PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
            }
            else
            {
                /* Command Code should match */
                if ((pRxBufferTmp[PHHAL_HW_RD710_FRAME_CMD_POS] != (uint8_t)((uint16_t)wCmd >> 8)) ||
                    (pRxBufferTmp[PHHAL_HW_RD710_FRAME_CMD_POS+1] != ((uint8_t)wCmd | 0x80)))
                {
                    status = PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
                }
                else
                {
                    /* Retrieve status */
                    statusTmp = PH_ADD_COMPCODE(
                        (uint16_t)pRxBufferTmp[PHHAL_HW_RD710_FRAME_STATUS_POS],
                        ((uint16_t)pRxBufferTmp[PHHAL_HW_RD710_FRAME_STATUS_POS+1] << 8));
                }
            }
        }
    }

    /* If a buffered command has been sent, restore Tx-/RxBuffer Contents */
    if (bUseBuffering != PH_OFF)
    {
        memcpy(pTxBufferTmp, abTxBufferBackup, wTxBufferTmpOffset); /* PRQA S 3200 */ /* PRQA S 3354 */
        memcpy(pRxBufferTmp, abRxBufferBackup, PHHAL_HW_RD710_FRAME_HEADER_LEN); /* PRQA S 3200 */ /* PRQA S 3354 */
    }

    /* Bail out on error */
    PH_CHECK_SUCCESS(status);

    /* Return RxBuffer length */
    if (pRxLength != NULL)
    {
        *pRxLength = wRxBufferTmpLength - PHHAL_HW_RD710_FRAME_HEADER_LEN; /* PRQA S 3382 */
    }

    /* Return RxBuffer pointer */
    if ((ppRxBuffer != NULL) && (pRxLength != NULL))
    {
        memcpy(&pRxBufferTmp[PHHAL_HW_RD710_FRAME_PAYLOAD_POS - PHHAL_HW_RD710_FRAME_HEADER_LEN], &pRxBufferTmp[PHHAL_HW_RD710_FRAME_PAYLOAD_POS], *pRxLength);  /* PRQA S 3200 */
        *ppRxBuffer = pRxBufferTmp;
    }

    /* Unbuffered command: store RxLength */
    if (bUseBuffering == PH_OFF)
    {
        pDataParams->wRxBufLen = wRxBufferTmpLength - PHHAL_HW_RD710_FRAME_HEADER_LEN; /* PRQA S 3382 */
    }

    return statusTmp; 
}

#endif /* NXPBUILD__PHHAL_HW_RD710 */
