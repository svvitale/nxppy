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
* $Author: jayaprakash.desai $
* $Revision: 1.5 $
* $Date: Mon Apr 18 11:33:15 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/
#include <phbalReg.h>
#include <phhalHw.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHHAL_HW_RD710

#include "phhalHw_Rd710.h"
#include "phhalHw_Rd710_Int.h"
#include <phhalHw_Rd710_Cmd.h>

phStatus_t phhalHw_Rd710_Init(
                              phhalHw_Rd710_DataParams_t * pDataParams,
                              uint16_t wSizeOfDataParams,
                              void * pBalDataParams,
                              uint8_t bSlotNumber,
                              uint8_t * pTxBuffer,
                              uint16_t wTxBufSize,
                              uint8_t * pRxBuffer,
                              uint16_t wRxBufSize
                              )
{
    /* Dataparam check */
    if (sizeof(phhalHw_Rd710_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_HAL);
    }
    if ((wTxBufSize < PHHAL_HW_RD710_RESERVED_BUFFER_LEN) || (wRxBufSize < PHHAL_HW_RD710_RESERVED_BUFFER_LEN))
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }
    /* Pointer check*/
    PH_ASSERT_NULL (pDataParams);
    PH_ASSERT_NULL (pBalDataParams);
    PH_ASSERT_NULL (pTxBuffer);
    PH_ASSERT_NULL (pRxBuffer);

    /* Modify Tx-/RxBuffer pointers/lengths */
    pTxBuffer += PHHAL_HW_RD710_RESERVED_BUFFER_LEN;
    wTxBufSize = wTxBufSize - PHHAL_HW_RD710_RESERVED_BUFFER_LEN;
    pRxBuffer += PHHAL_HW_RD710_RESERVED_BUFFER_LEN;
    wRxBufSize = wRxBufSize - PHHAL_HW_RD710_RESERVED_BUFFER_LEN;

    /* Init. private data */
    pDataParams->wId                    = PH_COMP_HAL | PHHAL_HW_RD710_ID;
    pDataParams->pBalDataParams         = pBalDataParams;
    pDataParams->bSlotNumber            = bSlotNumber;
    pDataParams->pTxBuffer              = pTxBuffer;
    pDataParams->wTxBufSize             = wTxBufSize;
    pDataParams->wTxBufLen              = 0;
    pDataParams->wTxBufStart            = 0;
    pDataParams->pRxBuffer              = pRxBuffer;
    pDataParams->wRxBufSize             = wRxBufSize;
    pDataParams->wRxBufLen              = 0;
    pDataParams->wRxBufStartPos         = 0;
    pDataParams->wTxBufStartPos         = 0;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd710_Command(
                                 phhalHw_Rd710_DataParams_t * pDataParams,
                                 uint8_t bCmd,
                                 uint16_t wOption, 
                                 uint8_t * pTxBuffer,
                                 uint16_t wTxLength,
                                 uint8_t ** ppRxBuffer,
                                 uint16_t * pRxLength
                                 )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM aCommand[3];

    aCommand[0] = bCmd;
    aCommand[1] = (uint8_t)(wOption & 0xFF);
    aCommand[2] = (uint8_t)(wOption >> 8);

    /* Buffer the command-frame */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_EXECUTE,
        PH_EXCHANGE_BUFFER_FIRST,
        aCommand,
        3,
        NULL,
        NULL));

    /* Append given data and Exchange with lower layer */
    return phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_EXECUTE,
        PH_EXCHANGE_BUFFER_LAST,
        pTxBuffer,
        wTxLength,
        ppRxBuffer,
        pRxLength);
}

phStatus_t phhalHw_Rd710_Exchange(
                                  phhalHw_Rd710_DataParams_t * pDataParams,
                                  uint16_t wOption,
                                  uint8_t * pTxBuffer,
                                  uint16_t wTxLength,
                                  uint8_t ** ppRxBuffer,
                                  uint16_t * pRxLength
                                  )
{
    phStatus_t  PH_MEMLOC_REM status;
    uint16_t    PH_MEMLOC_REM wPosition;
    uint16_t	PH_MEMLOC_REM RxLength;
    uint8_t *	PH_MEMLOC_REM pRxBuffer;

    /* Check options */
    if ((wOption & (uint16_t)~(uint16_t)(PH_EXCHANGE_BUFFERED_BIT | PH_EXCHANGE_LEAVE_BUFFER_BIT)) != 0x0000)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
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

    /* clear internal buffer if requested */
    if (!(wOption & PH_EXCHANGE_LEAVE_BUFFER_BIT))
    {
        pDataParams->wTxBufLen = 0;
    }

    /* Calculate start position */
    wPosition = PHHAL_HW_RD710_RESERVED_BUFFER_LEN + pDataParams->wTxBufStartPos + pDataParams->wTxBufLen;

    /* Buffer overflow check */
    if ((wPosition + wTxLength) > pDataParams->wTxBufSize)
    {
        pDataParams->wTxBufLen = 0;
        return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
    }

    /* Copy transmit buffer*/
    memcpy(&pDataParams->pTxBuffer[wPosition], pTxBuffer, wTxLength);  /* PRQA S 3200 */
    pDataParams->wTxBufLen = pDataParams->wTxBufLen + wTxLength;

    /* Set receive buffer properties */
    pDataParams->wRxBufLen = pDataParams->wRxBufStartPos;

    /* Perform the actual exchange */
    /* Execute via Hal Command */
    status = phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_EXCHANGE,
        wOption,
        pTxBuffer,
        wTxLength,
        ppRxBuffer,
        pRxLength);

    /* Return correct data length */
    *ppRxBuffer -= pDataParams->wRxBufStartPos;
    *pRxLength = *pRxLength + pDataParams->wRxBufStartPos;

    /* Store RxBufLen in DataParams */
    pDataParams->wRxBufLen = *pRxLength;

    /* Reset buffered bytes */
    pDataParams->wTxBufLen = 0;

    return status;
}

phStatus_t phhalHw_Rd710_WriteRegister(
                                       phhalHw_Rd710_DataParams_t * pDataParams,
                                       uint8_t bAddress,
                                       uint8_t bValue
                                       )
{    
    uint8_t PH_MEMLOC_REM aCommand[2];

    aCommand[0] = bAddress;
    aCommand[1] = bValue;

    /* Execute via Hal Command */
    return phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_RD_OPS_WRITE_REGISTER,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        2,
        NULL,
        NULL);
}

phStatus_t phhalHw_Rd710_ReadRegister(
                                      phhalHw_Rd710_DataParams_t * pDataParams,
                                      uint8_t bAddress,
                                      uint8_t * pValue
                                      )
{    
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM aCommand[1];
    uint8_t *   PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;

    /* Prepare command */
    aCommand[0] = bAddress;

    /* Execute via Hal Command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_RD_OPS_READ_REGISTER,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        1,
        &pRxBuffer,
        &wRxLength));

    /* check received length */
    if (wRxLength < 1)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
    }

    *pValue = pRxBuffer[0];

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL); 
}

phStatus_t phhalHw_Rd710_ApplyProtocolSettings(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint8_t bCardType
    )
{
    uint8_t PH_MEMLOC_REM aCommand[1];

    /* Prepare command */
    aCommand[0] = bCardType;

    /* Execute via Hal Command */
    return phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_APPLY_PROT_SETTINGS,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        1,
        NULL,
        NULL);
}

phStatus_t phhalHw_Rd710_SetConfig(
                                   phhalHw_Rd710_DataParams_t * pDataParams,
                                   uint16_t wConfig,
                                   uint16_t wValue
                                   )
{    
    uint8_t PH_MEMLOC_REM aCommand[4];

    switch(wConfig)
    {

    case PHHAL_HW_CONFIG_RXBUFFER_STARTPOS:

        /* Boundary check */
        if ((PHHAL_HW_RD710_RESERVED_BUFFER_LEN + wValue) >= pDataParams->wRxBufSize)
        {
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* Set start position */
        pDataParams->wRxBufStartPos = wValue;
        pDataParams->wRxBufLen = wValue;

        /* Preserve RxBuffer contents if needed */
        if (pDataParams->pTxBuffer == pDataParams->pRxBuffer)
        {
            pDataParams->wTxBufStartPos = pDataParams->wRxBufStartPos;
        }
        else
        {
            pDataParams->wTxBufStartPos = 0;
        }
        break;    

    default:

        aCommand[0] = (uint8_t)(wConfig & 0xFF);
        aCommand[1] = (uint8_t)(wConfig >> 8);
        aCommand[2] = (uint8_t)(wValue & 0xFF);
        aCommand[3] = (uint8_t)(wValue >> 8);

        /* Execute via Hal Command */
        return phhalHw_Rd710_CommandReader(
            pDataParams,
            PHHAL_HW_RD710_CMD_SET_CONFIG,
            PH_EXCHANGE_DEFAULT,
            aCommand,
            4,
            NULL,
            NULL);
    }
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd710_GetConfig(
                                   phhalHw_Rd710_DataParams_t * pDataParams,
                                   uint16_t wConfig,
                                   uint16_t * pValue
                                   )
{    
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *   PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;
    uint8_t     PH_MEMLOC_REM aCommand[2];

    switch(wConfig)
    {
    case PHHAL_HW_CONFIG_RXBUFFER_STARTPOS:

        /* Return parameter */
        *pValue = pDataParams->wRxBufStartPos;
        break;

    case PHHAL_HW_CONFIG_RXBUFFER_BUFSIZE:

        /* Return parameter */
        *pValue = pDataParams->wRxBufSize;
        break;

    case PHHAL_HW_CONFIG_TXBUFFER_BUFSIZE:

        /* Return parameter */
        *pValue = pDataParams->wTxBufSize - pDataParams->wTxBufStartPos;
        break;

    default:

        aCommand[0] = (uint8_t)(wConfig & 0xFF);
        aCommand[1] = (uint8_t)(wConfig >> 8);

        /* Execute via Hal Command */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
            pDataParams,
            PHHAL_HW_RD710_CMD_GET_CONFIG,
            PH_EXCHANGE_DEFAULT,
            aCommand,
            2,
            &pRxBuffer,
            &wRxLength));

        /* check received length */
        if (wRxLength != 2)
        {
            return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
        }

        *pValue = (uint16_t)pRxBuffer[0] | ((uint16_t)pRxBuffer[1] << 8);
        break;
    }
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL); 
}

phStatus_t phhalHw_Rd710_FieldOn(
                                 phhalHw_Rd710_DataParams_t * pDataParams
                                 )
{    
    /* Execute via Hal Command */
    return phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_RD_OPS_FIELD_ON,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        NULL,
        NULL);
}

phStatus_t phhalHw_Rd710_FieldOff(
                                  phhalHw_Rd710_DataParams_t * pDataParams
                                  )
{    
    /* Execute via Hal Command */
    return phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_RD_OPS_FIELD_OFF,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        NULL,
        NULL);
}

phStatus_t phhalHw_Rd710_FieldReset(
                                    phhalHw_Rd710_DataParams_t * pDataParams
                                    )
{
    /* Execute via Hal Command */
    return phhalHw_Rd710_CommandReader (
        pDataParams,
        PHHAL_HW_RD710_CMD_RD_OPS_FIELD_RESET,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        NULL,
        NULL);
}

phStatus_t phhalHw_Rd710_Wait(
                              phhalHw_Rd710_DataParams_t * pDataParams,
                              uint8_t bUnit,
                              uint16_t wTimeout
                              )
{
    uint8_t PH_MEMLOC_REM aCommand[3];

    aCommand[0] = bUnit;
    aCommand[1] = (uint8_t)(wTimeout & 0xFF);
    aCommand[2] = (uint8_t)(wTimeout >> 8);

    /* Execute via Hal Command */
    return phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_WAIT,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        3,
        NULL,
        NULL);
}

phStatus_t phhalHw_Rd710_MfcAuthenticateKeyNo(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint8_t bBlockNo,
    uint8_t bKeyType,
    uint16_t wKeyNo,
    uint16_t wKeyVersion,
    uint8_t * pUid
    )
{    
    uint8_t PH_MEMLOC_REM aCommand[10];

    aCommand[0] = bBlockNo;
    aCommand[1] = bKeyType;
    memcpy (&aCommand[2], pUid, 4); /* PRQA S 3200 */
    aCommand[6] = (uint8_t)(wKeyNo & 0xFF);
    aCommand[7] = (uint8_t)(wKeyNo >> 8);
    aCommand[8] = (uint8_t)(wKeyVersion & 0xFF);
    aCommand[9] = (uint8_t)(wKeyVersion >> 8);

    /* Exchange with lower layer */
    return phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_MFC_AUTH_KEY_NO,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        10,
        NULL,
        NULL);
}

phStatus_t phhalHw_Rd710_MfcAuthenticate(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint8_t bBlockNo,
    uint8_t bKeyType,
    uint8_t * pKey,
    uint8_t * pUid
    )
{
    uint8_t PH_MEMLOC_REM aCommand[12];

    aCommand[0] = bBlockNo;
    aCommand[1] = bKeyType;
    memcpy(&aCommand[2], pKey, 6);  /* PRQA S 3200 */
    memcpy(&aCommand[8], pUid, 4);  /* PRQA S 3200 */

    /* Exchange with lower layer */
    return phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_MFC_AUTH,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        12,
        NULL,
        NULL);
}

#endif /* NXPBUILD__PHHAL_HW_RD710 */
