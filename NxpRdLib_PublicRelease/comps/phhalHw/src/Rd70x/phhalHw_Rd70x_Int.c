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
* RD700 specific HAL-Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.5 $
* $Date: Fri Apr 15 09:04:41 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/
#include <ph_Status.h>
#include <phbalReg.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHHAL_HW_RD70X

#include "phhalHw_Rd70x.h"
#include "phhalHw_Rd70x_Int.h"

phStatus_t phhalHw_Rd70x_SendCommand(
                                     phhalHw_Rd70x_DataParams_t * pDataParams
                                     )
{
    phStatus_t  PH_MEMLOC_REM status;
    uint16_t    PH_MEMLOC_REM wCommandLen;
    uint8_t     PH_MEMLOC_REM bOverlapLen;
    uint16_t    PH_MEMLOC_REM wTransmitStart;
    uint16_t    PH_MEMLOC_REM wReceiveStart;
    uint16_t    PH_MEMLOC_REM wRxBackupLen;
    uint16_t    PH_MEMLOC_REM wRespLen;

    /* Calculate Command length */
    switch (pDataParams->bProtBuffer[0])
    {
    case uC_PiccExchangeBlock:
    case uC_PiccExchangeBlockRfCycle:
    case uC_ISO15693_Exchange:
    case uC_UID_Exchange:

        wCommandLen = pDataParams->bProtBufferLen + pDataParams->wTxBufLen;
        bOverlapLen = PHHAL_HW_RD70X_RX_OVERLAP_LEN_EX_BLOCK;
        wTransmitStart = PHHAL_HW_RD70X_RESERVED_BUFFER_LEN + pDataParams->wTxBufStartPos - pDataParams->bProtBufferLen;
        wReceiveStart = PHHAL_HW_RD70X_RESERVED_BUFFER_LEN + pDataParams->wRxBufStartPos - bOverlapLen;
        break;

    case uC_PiccExchangeBitByteRfCycle:
    case uC_PiccExchangeBitByte:

        wCommandLen = pDataParams->bProtBufferLen + pDataParams->wTxBufLen;
        bOverlapLen = PHHAL_HW_RD70X_RX_OVERLAP_LEN_EX_BITBYTE;
        wTransmitStart = PHHAL_HW_RD70X_RESERVED_BUFFER_LEN + pDataParams->wTxBufStartPos - pDataParams->bProtBufferLen;
        wReceiveStart = PHHAL_HW_RD70X_RESERVED_BUFFER_LEN + pDataParams->wRxBufStartPos - bOverlapLen;
        break;

    case uC_PiccExchangeBitByteMultiple:

        wCommandLen = pDataParams->bProtBufferLen + pDataParams->wTxBufLen;
        bOverlapLen = PHHAL_HW_RD70X_RX_OVERLAP_LEN_EX_BITBYTE_MP;
        wTransmitStart = PHHAL_HW_RD70X_RESERVED_BUFFER_LEN + pDataParams->wTxBufStartPos - pDataParams->bProtBufferLen;
        wReceiveStart = PHHAL_HW_RD70X_RESERVED_BUFFER_LEN + pDataParams->wRxBufStartPos - bOverlapLen;
        break;

    case uC_WriteMultiple:
    case uC_ReadMultiple:
        wCommandLen = pDataParams->bProtBufferLen + pDataParams->wTxBufLen;
        bOverlapLen = 0;
        wTransmitStart = 0;
        wReceiveStart = 0;
        break;

    default:
        wCommandLen = pDataParams->bProtBufferLen;
        bOverlapLen = 0;
        wTransmitStart = 0;
        wReceiveStart = 0;
        break;
    }

    /* Buffer overflow check */
    if ((wTransmitStart + wCommandLen) > pDataParams->wTxBufSize)
    {
        return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
    }

    /* [1st backup step]: if RxBuffer == TxBuffer, backup the data of the RxBuffer that gets overwritten by the (TX) pegoda protocol. */
    /* As Backup buffer, the reserved area of the TxBuffer is used. */
    /* wAdditional info is used to store the starting position for restoration. */
    if ((pDataParams->pRxBuffer == pDataParams->pTxBuffer) && (pDataParams->wTxBufStartPos > 0))
    {
        wRxBackupLen = pDataParams->bProtBufferLen - bOverlapLen;
        memmove(pDataParams->pTxBuffer, &pDataParams->pTxBuffer[wTransmitStart], wRxBackupLen); /* PRQA S 3200 */
        pDataParams->wTxRxStartBackup = wTransmitStart;
    }
    else
    {
        pDataParams->wTxRxStartBackup = 0;
        wRxBackupLen = 0;
    }

    /* [2nd backup step]: Backup the valid contents of the RxBuffer which would get overwritten by the (RX) pegoda protocol. */
    /* As Backup buffer, the reserved area of the TxBuffer is used. */
    if (pDataParams->wRxBufStartPos > 0)
    {
        memcpy(&pDataParams->pTxBuffer[wRxBackupLen], &pDataParams->pRxBuffer[wReceiveStart], bOverlapLen);  /* PRQA S 3200 */
        if (wRxBackupLen == 0)
        {
            pDataParams->wTxRxStartBackup = wReceiveStart;
        }
        wRxBackupLen = wRxBackupLen + bOverlapLen;
    }

    /* Copy protocol header */
    memcpy(&(pDataParams->pTxBuffer[wTransmitStart]), pDataParams->bProtBuffer, pDataParams->bProtBufferLen);  /* PRQA S 3200 */

    /* Set command length */
    pDataParams->pTxBuffer[wTransmitStart + 1] = (uint8_t)(wCommandLen & 0xFF);
    pDataParams->pTxBuffer[wTransmitStart + 2] = (uint8_t)((wCommandLen >> 8) & 0xFF);

    /* Perform actual exchange */
    status = phbalReg_Exchange(
        pDataParams->pBalDataParams, 
        PH_EXCHANGE_DEFAULT,
        &pDataParams->pTxBuffer[wTransmitStart],
        wCommandLen,
        (pDataParams->wRxBufSize - wReceiveStart), 
        &pDataParams->pRxBuffer[wReceiveStart],
        &wRespLen);

    /* Since we provide the buffer, it's a HAL buffer overflow */
    if ((status & PH_ERR_MASK) == PH_ERR_BUFFER_OVERFLOW)
    {
        status = PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
    }

    /* [3rd backup step]: bProtBufferLen is re-used to store the backuped data bytes of the receive buffer */
    /* The restoration of backuped RxBuffer bytes is done by the phhalHw_Rd70x_GetParam_BufferPointer() */
    /* function since this is where the actual receive buffer is retrieved. */
    pDataParams->bProtBufferLen = (uint8_t)wRxBackupLen;

    /* Set initial read position for Rx-Buffer */
    pDataParams->wProtRxBufReadPos = wReceiveStart;

    /* Bail out on error */
    PH_CHECK_SUCCESS(status);

    /* retrieve overall data length */
    wCommandLen = (uint16_t)((uint16_t)pDataParams->pRxBuffer[wReceiveStart + 2] << 8) | (uint16_t)pDataParams->pRxBuffer[wReceiveStart + 1];

    /* protocol error check */
    if ((wCommandLen + 3) != wRespLen)
    {
        /* Workaround: Driver does not handle USB protocol correctly, last block must not occupy the full frame */
        /* --> allow one dummy byte at the end */
        if  ((wCommandLen + 4) != wRespLen)
        {
            status = PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
        }
    }

    return status;
}

void phhalHw_Rd70x_SetCommand(
                              phhalHw_Rd70x_DataParams_t * pDataParams,
                              uint8_t bCmd
                              )
{
    /* Buffer overflow check */
    if ((pDataParams->wTxBufSize - pDataParams->wTxBufLen) < 3)
    {
        return;
    }

    /* Also add 2 dummy length bytes */
    pDataParams->bProtBuffer[0] = bCmd;
    pDataParams->bProtBuffer[1] = 0x00;
    pDataParams->bProtBuffer[2] = 0x00;
    pDataParams->bProtBufferLen = 3;
}

void phhalHw_Rd70x_AddParam_Uint8(
                                  phhalHw_Rd70x_DataParams_t * pDataParams,
                                  uint8_t bData
                                  )
{
    /* Buffer overflow check */
    if ((pDataParams->wTxBufSize - pDataParams->wTxBufLen) < sizeof(uint8_t))
    {
        return;
    }

    /* Add the data */
    pDataParams->bProtBuffer[pDataParams->bProtBufferLen++] = bData;
}

void phhalHw_Rd70x_AddParam_Uint16(
                                   phhalHw_Rd70x_DataParams_t * pDataParams,
                                   uint16_t wData
                                   )
{
    /* Buffer overflow check */
    if ((pDataParams->wTxBufSize - pDataParams->wTxBufLen) < sizeof(uint16_t))
    {
        return;
    }

    /* Add the data */
    pDataParams->bProtBuffer[pDataParams->bProtBufferLen++] = (uint8_t)(wData & 0xFF);
    pDataParams->bProtBuffer[pDataParams->bProtBufferLen++] = (uint8_t)((wData >> 8) & 0xFF);
}

void phhalHw_Rd70x_AddParam_Uint32(
                                   phhalHw_Rd70x_DataParams_t * pDataParams,
                                   uint32_t dwData
                                   )
{
    /* Buffer overflow check */
    if ((pDataParams->wTxBufSize - pDataParams->wTxBufLen) < sizeof(uint32_t))
    {
        return;
    }

    /* Add the data */
    pDataParams->bProtBuffer[pDataParams->bProtBufferLen++] = (uint8_t)(dwData & 0xFF);
    pDataParams->bProtBuffer[pDataParams->bProtBufferLen++] = (uint8_t)((dwData >> 8) & 0xFF);
    pDataParams->bProtBuffer[pDataParams->bProtBufferLen++] = (uint8_t)((dwData >> 16) & 0xFF);
    pDataParams->bProtBuffer[pDataParams->bProtBufferLen++] = (uint8_t)((dwData >> 24) & 0xFF);
}

void phhalHw_Rd70x_AddParam_Buffer(
                                   phhalHw_Rd70x_DataParams_t * pDataParams,
                                   uint8_t * pData,
                                   uint16_t wDataLen
                                   )
{
    /* Ignore NULL pointers */
    if (pData == NULL)
    {
        return;
    }

    /* Buffer overflow check */
    if ((pDataParams->wTxBufSize - pDataParams->wTxBufLen) < wDataLen)
    {
        return;
    }

    /* Copy over all data bytes */
    memcpy(&pDataParams->bProtBuffer[pDataParams->bProtBufferLen], pData, wDataLen);  /* PRQA S 3200 */
    pDataParams->bProtBufferLen = pDataParams->bProtBufferLen + (uint8_t)wDataLen;
}

phStatus_t phhalHw_Rd70x_GetStatus(
                                   phhalHw_Rd70x_DataParams_t * pDataParams
                                   )
{
    uint8_t PH_MEMLOC_REM bStatus;

    /* Receive buffer check */
    if ((pDataParams->wProtRxBufReadPos + sizeof(uint8_t)) > pDataParams->wRxBufSize)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
    }

    /* Retrieve status byte */
    bStatus = pDataParams->pRxBuffer[pDataParams->wProtRxBufReadPos];

    /* Ignore length byte */
    pDataParams->wProtRxBufReadPos = pDataParams->wProtRxBufReadPos + 3;

    /* Evaluate status */
    return phhalHw_Rd70x_EvaluateStatus(bStatus);
}

phStatus_t phhalHw_Rd70x_EvaluateStatus(
                                        uint8_t bStatus
                                        )
{
    phStatus_t PH_MEMLOC_REM status;

    switch (bStatus)
    {
    case (uint8_t)MI_OK:
    case (uint8_t)MI_POLLING:
        status = PH_ERR_SUCCESS;
        break;
    case (uint8_t)MI_NOTAGERR:
    case (uint8_t)I1_TIMEOUT:
    case (uint8_t)I2_NO_TAG:
        status = PH_ERR_IO_TIMEOUT;
        break;
    case (uint8_t)MI_CRCERR:
    case (uint8_t)I2_CRCERR:
    case (uint8_t)MI_PARITYERR:
        status = PH_ERR_INTEGRITY_ERROR;
        break;
    case (uint8_t)MI_AUTHERR:
        status = PH_ERR_AUTH_ERROR;
        break;
    case (uint8_t)MI_CODEERR:
    case (uint8_t)MI_SERNRERR:
    case (uint8_t)MI_BITCOUNTERR:
    case (uint8_t)MI_BYTECOUNTERR:
    case (uint8_t)I2_SNRERR:
    case (uint8_t)I2_COUNTERR:
        status = PH_ERR_PROTOCOL_ERROR;
        break;
    case (uint8_t)MI_FRAMINGERR:
    case (uint8_t)I2_FRAMINGERR:
        status = PH_ERR_FRAMING_ERROR;
        break;
    case (uint8_t)MI_UNKNOWN_COMMAND:
        status = PH_ERR_UNSUPPORTED_COMMAND;
        break;
    case (uint8_t)MI_COLLERR:
    case (uint8_t)I2_COLLERR:
        status = PH_ERR_COLLISION_ERROR;
        break;
    case (uint8_t)MI_SENDBUF_OVERFLOW:
        status = PH_ERR_BUFFER_OVERFLOW;
        break;
    default:
        status = PH_ERR_INTERNAL_ERROR;
        break;
    }

    return PH_ADD_COMPCODE(status, PH_COMP_HAL); 
}

void phhalHw_Rd70x_GetParam_Uint8(
                                  phhalHw_Rd70x_DataParams_t * pDataParams,
                                  uint8_t * pData
                                  )
{
    /* Receive buffer check */
    if ((pDataParams->wProtRxBufReadPos + sizeof(uint8_t)) > pDataParams->wRxBufSize)
    {
        return;
    }

    *pData = pDataParams->pRxBuffer[pDataParams->wProtRxBufReadPos++];
}

void phhalHw_Rd70x_GetParam_Uint16(
                                   phhalHw_Rd70x_DataParams_t * pDataParams,
                                   uint16_t * pData
                                   )
{
    /* Receive buffer check */
    if ((pDataParams->wProtRxBufReadPos + sizeof(uint16_t)) > pDataParams->wRxBufSize)
    {
        return;
    }

    *pData  = (uint16_t)pDataParams->pRxBuffer[pDataParams->wProtRxBufReadPos++];
    *pData |= (uint16_t)((uint16_t)pDataParams->pRxBuffer[pDataParams->wProtRxBufReadPos++] << 8);
}

void phhalHw_Rd70x_GetParam_Uint32(
                                   phhalHw_Rd70x_DataParams_t * pDataParams,
                                   uint32_t * pData
                                   )
{
    /* Receive buffer check */
    if ((pDataParams->wProtRxBufReadPos + sizeof(uint32_t)) > pDataParams->wRxBufSize)
    {
        return;
    }

    *pData  = (uint32_t)pDataParams->pRxBuffer[pDataParams->wProtRxBufReadPos++];
    *pData |= (uint32_t)((uint32_t)pDataParams->pRxBuffer[pDataParams->wProtRxBufReadPos++] << 8);
    *pData |= (uint32_t)((uint32_t)pDataParams->pRxBuffer[pDataParams->wProtRxBufReadPos++] << 16);
    *pData |= (uint32_t)((uint32_t)pDataParams->pRxBuffer[pDataParams->wProtRxBufReadPos++] << 24);
}

void phhalHw_Rd70x_GetParam_Buffer(
                                   phhalHw_Rd70x_DataParams_t * pDataParams,
                                   uint16_t wDataLen,
                                   uint8_t * pData
                                   )
{
    /* Receive buffer check */
    if ((pDataParams->wProtRxBufReadPos + wDataLen) > pDataParams->wRxBufSize)
    {
        return;
    }

    /* Copy over all data bytes */
    memcpy(pData, &pDataParams->pRxBuffer[pDataParams->wProtRxBufReadPos], wDataLen);  /* PRQA S 3200 */
    pDataParams->wProtRxBufReadPos = pDataParams->wProtRxBufReadPos + wDataLen;
}

void phhalHw_Rd70x_GetParam_BufferPointer(
    phhalHw_Rd70x_DataParams_t * pDataParams,
    uint8_t ** pData
    )
{
    /* Restore the overlapped data if neccessary */
    if (pDataParams->bProtBufferLen > 0)
    {
        memcpy(&pDataParams->pRxBuffer[pDataParams->wTxRxStartBackup], pDataParams->pTxBuffer, pDataParams->bProtBufferLen);  /* PRQA S 3200 */
    }

    /* Return the pointer to the actual data */
    *pData = &pDataParams->pRxBuffer[pDataParams->wProtRxBufReadPos];
}

phStatus_t phhalHw_Rd70x_WriteFifo(
                                   phhalHw_Rd70x_DataParams_t * pDataParams,
                                   uint8_t * pData,
                                   uint16_t wLength,
                                   uint16_t * pBytesWritten
                                   )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t    PH_MEMLOC_COUNT wIndex;

    /* Write each single data byte */
    for (wIndex = 0; wIndex < wLength; ++wIndex)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(
            pDataParams,
            PHHAL_HW_RD70X_REG_FIFO_DATA,
            pData[wIndex]));
    }

    *pBytesWritten = wLength;
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd70x_ReadFifo(
                                  phhalHw_Rd70x_DataParams_t * pDataParams,
                                  uint16_t wBufSize,
                                  uint8_t * pData,
                                  uint16_t * pLength
                                  )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_COUNT bIndex;
    uint8_t     PH_MEMLOC_COUNT bFifoLen;

    /* read out the FiFo Length register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(pDataParams, PHHAL_HW_RD70X_REG_FIFO_LENGTH, &bFifoLen));

    /* check for buffer overflow */
    if (bFifoLen > (uint8_t)wBufSize)
    {
        /* read maximum possible number of bytes */
        bFifoLen = (uint8_t)wBufSize;

        /* return buffer overflow status */
        status = PH_ERR_BUFFER_OVERFLOW;
    }
    else
    {
        /* Buffer is big enough */
        status = PH_ERR_SUCCESS;
    }

    /* Read each single data byte */
    for (bIndex = 0; bIndex < bFifoLen; ++bIndex)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(
            pDataParams,
            PHHAL_HW_RD70X_REG_FIFO_DATA,
            &pData[bIndex]));
    }

    *pLength = (uint16_t)bFifoLen;
    return PH_ADD_COMPCODE(status, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd70x_SetTypeBRegs(
                                      phhalHw_Rd70x_DataParams_t * pDataParams
                                      )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bRegister;

    /* Retrieve ChannelRedundancy Register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(
        pDataParams,
        PHHAL_HW_RD70X_REG_CHANNEL_REDUND,
        &bRegister));

    /* Set CRC for TypeB */
    bRegister |= PHHAL_HW_RD70X_BIT_CRC3309;

    /* Write changed ChannelRedundancy Register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(
        pDataParams,
        PHHAL_HW_RD70X_REG_CHANNEL_REDUND,
        bRegister));

    /* Retrieve CoderControl Register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(
        pDataParams,
        PHHAL_HW_RD70X_REG_CODER_CONTROL,
        &bRegister));

    /* Mask out current CoderRate and TxCoding settings */
    bRegister &= (uint8_t)~(uint8_t)(PHHAL_HW_RD70X_MASK_CODERRATE | PHHAL_HW_RD70X_MASK_TXCODING);

    /* Set TypeB settings */
    bRegister |= PHHAL_HW_RD70X_BIT_TXCODING_TYPEB;

    switch (pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXDATARATE])
    {
    case PHHAL_HW_RF_DATARATE_106:
        bRegister |= PHHAL_HW_RD70X_BIT_CODERRATE_TYPEB;
        break;
    case PHHAL_HW_RF_DATARATE_212:
        bRegister |= PHHAL_HW_RD70X_BIT_CODERRATE_106K;
        break;
    case PHHAL_HW_RF_DATARATE_424:
        bRegister |= PHHAL_HW_RD70X_BIT_CODERRATE_212K;
        break;
    case PHHAL_HW_RF_DATARATE_848:
        bRegister |= PHHAL_HW_RD70X_BIT_CODERRATE_424K;
        break;
    default:
        return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
    }

    /* Write changed CoderControl Register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(
        pDataParams,
        PHHAL_HW_RD70X_REG_CODER_CONTROL,
        bRegister));

    /* Retrieve DeoderControl Register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_ReadRegister(
        pDataParams,
        PHHAL_HW_RD70X_REG_DECODER_CONTROL,
        &bRegister));

    /* Mask out current RxFraming settings */
    bRegister &= (uint8_t)~(uint8_t)PHHAL_HW_RD70X_MASK_RXFRAMING;

    /* Set TypeB settings */
    bRegister |= PHHAL_HW_RD70X_BITS_RXFRAMING_TYPEB | PHHAL_HW_RD70X_BIT_RXCODING_BPSK;

    /* Write changed DeoderControl Register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(
        pDataParams,
        PHHAL_HW_RD70X_REG_DECODER_CONTROL,
        bRegister));

    /* Write BPSKDemControl Register */
    bRegister = 0x0C;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(
        pDataParams,
        PHHAL_HW_RD70X_REG_BPSK_DEM_CONTROL,
        bRegister));

    /* Write TypeBFraming Register */
    bRegister = 0x00;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_WriteRegister(
        pDataParams,
        PHHAL_HW_RD70X_REG_TYPEB_FRAMING,
        bRegister));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

#endif /* NXPBUILD__PHHAL_HW_RD70X */
