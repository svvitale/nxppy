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
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:27:42 2011 $
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

phStatus_t phhalHw_Rd710_Cmd_InitReader(
                                        phhalHw_Rd710_DataParams_t * pDataParams
                                        )
{
    phStatus_t PH_MEMLOC_REM statusTmp;

    /* Set PCSC mode to direct */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_Cmd_RD_SetPcscMode(
        pDataParams,
        PHHAL_HW_RD710_PCSCMODE_DIRECT));

    /* Initialize RD710 HAL stack */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_INIT_HAL,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        NULL,
        NULL));

    /* Initialize RD710 I14443P3A stack */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P3A_INIT,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        NULL,
        NULL));

    /* Initialize RD710 I14443P4A stack */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P4A_INIT,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        NULL,
        NULL));

    /* Initialize RD710 I14443P4 stack */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P4_INIT,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        NULL,
        NULL));

    /* Initialize RD710 MIFARE stack */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_MIFARE_INIT,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        NULL,
        NULL));

    /* Initialize RD710 CID stack */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_CID_INIT,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        NULL,
        NULL));

    /* Initialize RD710 KEYSTORE stack */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_KS_INIT,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        NULL,
        NULL));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL); 
}


phStatus_t phhalHw_Rd710_Cmd_RD_LedOff ( 
									phhalHw_Rd710_DataParams_t * pDataParams,
									uint8_t bLeds  )
{
  	uint8_t PH_MEMLOC_REM aCommand[1];
    aCommand[0] = bLeds;
    return (phhalHw_Rd710_CommandReader(
									pDataParams,
									PHHAL_HW_RD710_CMD_RD_OPS_LED_OFF,
									PH_EXCHANGE_DEFAULT,
									aCommand,
									1,		
									NULL,
									NULL));
}

phStatus_t phhalHw_Rd710_Cmd_RD_LedOn ( 
                                    phhalHw_Rd710_DataParams_t * pDataParams,
                                    uint8_t bLeds )
{
    uint8_t PH_MEMLOC_REM aCommand[1];
    aCommand[0] = bLeds;
    return (phhalHw_Rd710_CommandReader(
									pDataParams,
									PHHAL_HW_RD710_CMD_RD_OPS_LED_ON,
									PH_EXCHANGE_DEFAULT,
									aCommand,
									1,		
									NULL,
									NULL));
}

phStatus_t phhalHw_Rd710_Cmd_RD_ResetReader ( 
									phhalHw_Rd710_DataParams_t * pDataParams   )
{
    return (phhalHw_Rd710_CommandReader(
									pDataParams,
									PHHAL_HW_RD710_CMD_RD_OPS_RESET_READER,
									PH_EXCHANGE_DEFAULT,
									NULL,
									0,
									NULL,
									NULL));
}

phStatus_t phhalHw_Rd710_Cmd_RD_ResetFactoryDefaults ( 
									phhalHw_Rd710_DataParams_t * pDataParams)
{
	return (phhalHw_Rd710_CommandReader(
									pDataParams,
									PHHAL_HW_RD710_CMD_RD_OPS_RESET_FACTORY,
									PH_EXCHANGE_DEFAULT,
									NULL,
									0,
									NULL,
									NULL));
}

phStatus_t phhalHw_Rd710_Cmd_RD_SetConfigOption ( 
									phhalHw_Rd710_DataParams_t * pDataParams,
									uint8_t * pConfig,
									uint8_t * pData,
									uint16_t wDataLength)
{
    phStatus_t PH_MEMLOC_REM statusTmp;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
									pDataParams,
									PHHAL_HW_RD710_CMD_RD_OPS_SET_CFG_OPTION,
									PH_EXCHANGE_BUFFER_FIRST,
									pConfig,					
									4,
									NULL,
									NULL));
    return (phhalHw_Rd710_CommandReader(
									pDataParams,
									PHHAL_HW_RD710_CMD_RD_OPS_SET_CFG_OPTION,
									PH_EXCHANGE_BUFFER_LAST,
									pData,						
									wDataLength,
									NULL,
									NULL));
}


phStatus_t phhalHw_Rd710_Cmd_RD_GetConfigOption ( 
									phhalHw_Rd710_DataParams_t * pDataParams,
									uint8_t * pConfig,
									uint8_t * pData,
									uint16_t * pDataLength)
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *   PH_MEMLOC_REM pRxBuffer;					

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
									pDataParams,
									PHHAL_HW_RD710_CMD_RD_OPS_GET_CFG_OPTION,
									PH_EXCHANGE_DEFAULT,
									pConfig,
									4,
									&pRxBuffer,
									pDataLength));
    if (*pDataLength < 1)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
    }
    memcpy (pData, pRxBuffer, *pDataLength); /* PRQA S 3200 */
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}


phStatus_t phhalHw_Rd710_Cmd_RD_SetPcscMode(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint8_t Mode
    )
{
    uint8_t PH_MEMLOC_REM aCommand[1];
    aCommand[0] = Mode;
    return (phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_RD_OPS_SET_PCSC_MODE,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        1,
        NULL,
        NULL));
}

phStatus_t phhalHw_Rd710_Cmd_RD_GetReaderStatus( 
											phhalHw_Rd710_DataParams_t * pDataParams,
											uint8_t * pReaderStatus)
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *   PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
													pDataParams,
													PHHAL_HW_RD710_CMD_RD_OPS_GET_READER_STATUS,
													PH_EXCHANGE_DEFAULT,
													NULL,
													0,
													&pRxBuffer,
													&wRxLength));
    if (wRxLength != 9)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
    }
    memcpy (pReaderStatus, pRxBuffer, wRxLength); /* PRQA S 3200 */
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL); 
}


phStatus_t phhalHw_Rd710_Cmd_CC_Activate( 
									phhalHw_Rd710_DataParams_t * pDataParams,
									uint8_t * pAtr,
									uint16_t * pAtrLen)	
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *   PH_MEMLOC_REM pRxBuffer;	
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
													pDataParams,
													PHHAL_HW_RD710_CMD_CC_ACTIVATE,
													PH_EXCHANGE_DEFAULT,
													NULL,		
													0,			
													&pRxBuffer,
													pAtrLen));
    memcpy (pAtr, pRxBuffer, *pAtrLen); /* PRQA S 3200 */
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL); 
}

phStatus_t phhalHw_Rd710_Cmd_CC_ColdReset( 
										phhalHw_Rd710_DataParams_t * pDataParams,
										uint8_t * pAtr,
										uint16_t * pAtrLen)	
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *   PH_MEMLOC_REM pRxBuffer;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
										pDataParams,
										PHHAL_HW_RD710_CMD_CC_COLD_RESET,
										PH_EXCHANGE_DEFAULT,
										NULL,
										0,
										&pRxBuffer,
										pAtrLen));
    memcpy (pAtr, pRxBuffer, *pAtrLen); /* PRQA S 3200 */
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL); 
}

phStatus_t phhalHw_Rd710_Cmd_CC_WarmReset( 
										phhalHw_Rd710_DataParams_t * pDataParams,
										uint8_t * pAtr,
										uint16_t * pAtrLen)	
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *   PH_MEMLOC_REM pRxBuffer;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
										pDataParams,
										PHHAL_HW_RD710_CMD_CC_WARM_RESET,
										PH_EXCHANGE_DEFAULT,
										NULL,
										0,
										&pRxBuffer,
										pAtrLen));
		
	
	memcpy (pAtr, pRxBuffer, *pAtrLen); /* PRQA S 3200 */
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL); 
}

/* Note: Not supportd by the P2_FW_v100 */
phStatus_t phhalHw_Rd710_Cmd_CC_StopClock( 
										phhalHw_Rd710_DataParams_t * pDataParams)
{
    return (phhalHw_Rd710_CommandReader(
										pDataParams,
										PHHAL_HW_RD710_CMD_CC_STOP_CLOCK,
										PH_EXCHANGE_DEFAULT,
										NULL,
										0,
										NULL,
										NULL));
}

/* Note: Not supportd by the P2_FW_v100 */
phStatus_t phhalHw_Rd710_Cmd_CC_StartClock( 
									   phhalHw_Rd710_DataParams_t * pDataParams)
{
    return (phhalHw_Rd710_CommandReader(
										pDataParams,
										PHHAL_HW_RD710_CMD_CC_START_CLOCK,
										PH_EXCHANGE_DEFAULT,
										NULL,
										0,
										NULL,
										NULL));
}

phStatus_t phhalHw_Rd710_Cmd_CC_Deactivate( 
										phhalHw_Rd710_DataParams_t * pDataParams)
{
    return (phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_CC_DEACTIVATE,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        NULL,
        NULL));
}

phStatus_t phhalHw_Rd710_Cmd_CC_PresenceCheck( 
										phhalHw_Rd710_DataParams_t * pDataParams,
										uint8_t * pCardInserted)
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *   PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;
	PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
										pDataParams,
										PHHAL_HW_RD710_CMD_CC_PRESENCE_CHECK,
										PH_EXCHANGE_DEFAULT,
										NULL,
										0,
										&pRxBuffer,
										&wRxLength));
    if (wRxLength != 1)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
    }
    *pCardInserted  = pRxBuffer[0];
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL); 
}

phStatus_t phhalHw_Rd710_Cmd_CC_TransmitData( 
									phhalHw_Rd710_DataParams_t * pDataParams,
									uint8_t * pTxBuffer,
									uint16_t wTxLength,
									uint8_t ** ppRxBuffer,
									uint16_t * pRxLength)
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *   PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;

    if (ppRxBuffer == NULL)
    {
        ppRxBuffer = &pRxBuffer;
    }
    if (pRxLength == NULL)
    {
        pRxLength = &wRxLength;
    }

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
										pDataParams,
										PHHAL_HW_RD710_CMD_CC_TRANSMIT_DATA,
										PH_EXCHANGE_DEFAULT,
										pTxBuffer,
										wTxLength,
										ppRxBuffer,
										pRxLength));
    if (*pRxLength < 2)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
    }
    *ppRxBuffer = &((*ppRxBuffer)[2]);				/* Omit the first two bytes */
    *pRxLength  = *pRxLength - 2;
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL); 
}

phStatus_t phhalHw_Rd710_Cmd_CC_SendPPS( 
                                        phhalHw_Rd710_DataParams_t * pDataParams,
                                        uint8_t bOption,
                                        uint8_t * pPPS,
                                        uint8_t * pRxBuffer)
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t    PH_MEMLOC_REM wPPSLen;
    uint8_t     PH_MEMLOC_REM pTxBuffer[5];
    uint8_t *   PH_MEMLOC_REM ppRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;

    /* 0x00 = send PPS, 
	   0x01 = set only the reader speed 
	*/
    pTxBuffer[0] = bOption;
    /* calculate length */
    wPPSLen = 1;
    /* check if we also want to send the PPS */
    if (!(bOption & 0x01))
    {
        /* PPS1 present */
        if (pPPS[0] & 0x10)
        {
            ++wPPSLen;
        }
        /* PPS2 present */
        if (pPPS[0] & 0x20)
        {
            ++wPPSLen;
        }
        /* PPS4 present */
        if (pPPS[0] & 0x40)
        {
            ++wPPSLen;
        }
    }
    memcpy(pTxBuffer + 1, pPPS, wPPSLen); /* PRQA S 3200 */
    
    ++wPPSLen; /* include the option byte in the length */

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
										pDataParams,
										PHHAL_HW_RD710_CMD_CC_SEND_PPS,
										PH_EXCHANGE_DEFAULT,
										pTxBuffer,
										wPPSLen,
										&ppRxBuffer,
										&wRxLength));
    if (wPPSLen != wRxLength + 1)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL); 
    }
    memcpy(pRxBuffer, ppRxBuffer, wRxLength); /* PRQA S 3200 */
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL); 
}


phStatus_t phhalHw_Rd710_Cmd_KS_FormatKeyEntry(
									phhalHw_Rd710_DataParams_t * pDataParams,
									uint16_t wKeyNo,
									uint16_t wNewKeyType) 
{
    uint8_t PH_MEMLOC_REM aCommand[4];
    aCommand[0] = (uint8_t)(wKeyNo & 0xFF);
    aCommand[1] = (uint8_t)(wKeyNo >> 8);
    aCommand[2] = (uint8_t)(wNewKeyType & 0xFF);
    aCommand[3] = (uint8_t)(wNewKeyType >> 8);
    return (phhalHw_Rd710_CommandReader(
								pDataParams,
								PHHAL_HW_RD710_CMD_KS_FORMAT_KEY_ENTRY,
								PH_EXCHANGE_DEFAULT,
								aCommand,
								4,
								NULL,
								NULL));
}

phStatus_t phhalHw_Rd710_Cmd_KS_SetKey(
                                       phhalHw_Rd710_DataParams_t * pDataParams,
                                       uint16_t wKeyType,
                                       uint16_t wKeyNo,
                                       uint16_t wKeyVersion,
                                       uint16_t wNewKeyVersion,
									   uint16_t wNewKeyLen,
                                       uint8_t* pNewKey)
{
    uint8_t		PH_MEMLOC_REM aCommand[40];
    aCommand[0] = (uint8_t)(wKeyType & 0xFF);
    aCommand[1] = (uint8_t)(wKeyType >> 8);
    aCommand[2] = (uint8_t)(wKeyNo & 0xFF);
    aCommand[3] = (uint8_t)(wKeyNo >> 8);
    aCommand[4] = (uint8_t)(wKeyVersion & 0xFF);
    aCommand[5] = (uint8_t)(wKeyVersion >> 8);
    aCommand[6] = (uint8_t)(wNewKeyVersion & 0xFF);
    aCommand[7] = (uint8_t)(wNewKeyVersion >> 8);
    memcpy (&aCommand[8], pNewKey, wNewKeyLen); /* PRQA S 3200 */
    return phhalHw_Rd710_CommandReader(
									pDataParams,
									PHHAL_HW_RD710_CMD_KS_SET_KEY,
									PH_EXCHANGE_DEFAULT,
									aCommand,
									8 + wNewKeyLen,
									NULL,
									NULL);
}


phStatus_t phhalHw_Rd710_Cmd_KS_SetKeyAtPos(
									phhalHw_Rd710_DataParams_t * pDataParams,
									uint16_t wKeyType,
									uint16_t wKeyNo,
									uint16_t wNewKeyVersion,
									uint16_t wPos,
									uint16_t wNewKeyLen,
									uint8_t * pNewKey)
{
    uint8_t		PH_MEMLOC_REM aCommand[40];
    aCommand[0] = (uint8_t)(wKeyType & 0xFF);
    aCommand[1] = (uint8_t)(wKeyType >> 8);
    aCommand[2] = (uint8_t)(wKeyNo & 0xFF);
    aCommand[3] = (uint8_t)(wKeyNo >> 8);
    aCommand[4] = (uint8_t)(wNewKeyVersion & 0xFF);
    aCommand[5] = (uint8_t)(wNewKeyVersion >> 8);
    aCommand[6] = (uint8_t)(wPos & 0xFF);
    aCommand[7] = (uint8_t)(wPos >> 8);
    memcpy (&aCommand[8], pNewKey, wNewKeyLen); /* PRQA S 3200 */
    return phhalHw_Rd710_CommandReader(
									pDataParams,
									PHHAL_HW_RD710_CMD_KS_SET_KEY_AT_POS,
									PH_EXCHANGE_DEFAULT,
									aCommand,
									8 + wNewKeyLen,
									NULL,
									NULL);
}

phStatus_t phhalHw_Rd710_Cmd_KS_SetKUC(
                                    phhalHw_Rd710_DataParams_t * pDataParams,
									uint16_t wKeyNo,
                                    uint16_t wRefNoKUC)
{
    uint8_t PH_MEMLOC_REM aCommand[4];
    aCommand[0] = (uint8_t)(wKeyNo & 0xFF);
    aCommand[1] = (uint8_t)(wKeyNo >> 8);
    aCommand[2] = (uint8_t)(wRefNoKUC & 0xFF);
    aCommand[3] = (uint8_t)(wRefNoKUC >> 8);
    return phhalHw_Rd710_CommandReader(
									pDataParams,
									PHHAL_HW_RD710_CMD_KS_SET_KUC,
									PH_EXCHANGE_DEFAULT,
									aCommand,
									4,
									NULL,
									NULL);
}

phStatus_t phhalHw_Rd710_Cmd_KS_SetFullKeyEntry(
											phhalHw_Rd710_DataParams_t * pDataParams,
											uint16_t wNoOfKeys,
											uint16_t wNewKeyType,
											uint16_t wKeyNo,
											uint16_t wNewRefNoKUC,
											uint16_t wSingleKeyLen,
											uint8_t * pNewKeys,
											uint16_t * pNewKeyVersionList)
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t		PH_MEMLOC_REM aCommand[10];
    uint16_t	PH_MEMLOC_REM wIndex;
    uint16_t	PH_MEMLOC_REM TxBufferLength;

    aCommand[0] = (uint8_t)(wNoOfKeys & 0xFF);
    aCommand[1] = (uint8_t)(wNoOfKeys >> 8);
    aCommand[2] = (uint8_t)(wNewKeyType & 0xFF);
    aCommand[3] = (uint8_t)(wNewKeyType >> 8);
    aCommand[4] = (uint8_t)(wKeyNo & 0xFF);
    aCommand[5] = (uint8_t)(wKeyNo >> 8);
    aCommand[6] = (uint8_t)(wNewRefNoKUC & 0xFF);
    aCommand[7] = (uint8_t)(wNewRefNoKUC >> 8);
    aCommand[8] = (uint8_t)(wSingleKeyLen & 0xFF);
    aCommand[9] = (uint8_t)(wSingleKeyLen >> 8);

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
													pDataParams,
													PHHAL_HW_RD710_CMD_KS_SET_FULL_KEY_ENTRY,
													PH_EXCHANGE_BUFFER_FIRST,
													aCommand,
													10,
													NULL,
													NULL));

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
													pDataParams,
													PHHAL_HW_RD710_CMD_KS_SET_FULL_KEY_ENTRY,
													PH_EXCHANGE_BUFFER_CONT,
													pNewKeys,
													wSingleKeyLen * wNoOfKeys,
													NULL,
													NULL));

    /* check wNoOfKeys is not higher than local aCommand */ 
    if ((wNoOfKeys * 2) > 10)
    {
        return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
    }

    TxBufferLength = 0;
    for (wIndex = 0; wIndex < wNoOfKeys; ++wIndex)
    {
        aCommand[TxBufferLength++] = (uint8_t)(pNewKeyVersionList[wIndex] & 0xFF);
        aCommand[TxBufferLength++] = (uint8_t)(pNewKeyVersionList[wIndex] >> 8);
    }

    return (phhalHw_Rd710_CommandReader(
										pDataParams,
										PHHAL_HW_RD710_CMD_KS_SET_FULL_KEY_ENTRY,
										PH_EXCHANGE_BUFFER_LAST,
										aCommand,
										TxBufferLength,
										NULL,
										NULL));
}

phStatus_t phhalHw_Rd710_Cmd_KS_GetKeyEntry(
										phhalHw_Rd710_DataParams_t * pDataParams,    
										uint16_t wKeyNo,
										uint16_t wKeyVersionBufSize,
										uint16_t * wKeyVersion,
										uint16_t * wKeyVersionLen,
										uint16_t * pKeyType)
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t		PH_MEMLOC_REM aCommand[2];
    uint8_t *	PH_MEMLOC_REM pRxBuffer;
    uint16_t	PH_MEMLOC_REM wRxLength;
    uint16_t	PH_MEMLOC_REM wOffset;
    uint16_t	PH_MEMLOC_REM wIndex;

    aCommand[0] = (uint8_t)(wKeyNo & 0xFF);
    aCommand[1] = (uint8_t)(wKeyNo >> 8);
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
													pDataParams,
													PHHAL_HW_RD710_CMD_KS_GET_KEY_ENTRY,
													PH_EXCHANGE_DEFAULT,
													aCommand,
													2,	
													&pRxBuffer,
													&wRxLength));
    if (wRxLength < 4)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
    }
    wOffset = 0;
    *pKeyType  = (uint16_t)pRxBuffer[wOffset++];
    *pKeyType |= (uint16_t)((uint16_t)pRxBuffer[wOffset++] << 8);
    *wKeyVersionLen = wRxLength - 2;			

    if (wKeyVersionBufSize < *wKeyVersionLen)
    {
        return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
    }

    for (wIndex = 0; wIndex < *wKeyVersionLen; wIndex += 2)
    {
        *wKeyVersion  = (uint16_t)pRxBuffer[wOffset++];
        *wKeyVersion |= (uint16_t)((uint16_t)pRxBuffer[wOffset++] << 8);
        ++wKeyVersion;
    }
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd710_Cmd_KS_GetKey(
                                       phhalHw_Rd710_DataParams_t * pDataParams,    
                                       uint16_t wKeyNo,
                                       uint16_t wKeyVersion,
                                       uint8_t bKeyBufSize,
                                       uint8_t * pKey,
                                       uint16_t * pKeyType)
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t		PH_MEMLOC_REM aCommand[4];
    uint8_t *	PH_MEMLOC_REM pRxBuffer;
    uint16_t	PH_MEMLOC_REM wRxLength;
    uint16_t	PH_MEMLOC_REM wOffset;
    aCommand[0] = (uint8_t)(wKeyNo & 0xFF);
    aCommand[1] = (uint8_t)(wKeyNo >> 8);
    aCommand[2] = (uint8_t)(wKeyVersion & 0xFF);
    aCommand[3] = (uint8_t)(wKeyVersion >> 8);
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
										pDataParams,
										PHHAL_HW_RD710_CMD_KS_GET_KEY,
										PH_EXCHANGE_DEFAULT,
										aCommand,
										4,
										&pRxBuffer,
										&wRxLength));
    if (wRxLength < 4)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
    }
    wOffset = 0;
    *pKeyType  = (uint16_t)pRxBuffer[wOffset++];
    *pKeyType |= (uint16_t)((uint16_t)pRxBuffer[wOffset++] << 8);

    wRxLength = wRxLength - wOffset;
    if (bKeyBufSize < (uint8_t)wRxLength)						/* check bKeyBufSize is large enough to recopy data */
    {
        return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
    }
    memcpy (pKey, &pRxBuffer[wOffset], wRxLength); /* PRQA S 3200 */
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}


phStatus_t phhalHw_Rd710_Cmd_KS_SetConfig(
										phhalHw_Rd710_DataParams_t * pDataParams,
										uint16_t wConfig,
										uint16_t wValue)
{
    uint8_t PH_MEMLOC_REM aCommand[4];
    aCommand[0] = (uint8_t)(wConfig & 0xFF);
    aCommand[1] = (uint8_t)(wConfig >> 8);
    aCommand[2] = (uint8_t)(wValue & 0xFF);
    aCommand[3] = (uint8_t)(wValue >> 8);
    return (phhalHw_Rd710_CommandReader(
										pDataParams,
										PHHAL_HW_RD710_CMD_KS_SET_CONFIG,
										PH_EXCHANGE_DEFAULT,
										aCommand,
										4,
										NULL,
										NULL));
}

phStatus_t phhalHw_Rd710_Cmd_KS_SetConfigStr(
										phhalHw_Rd710_DataParams_t * pDataParams,
										uint16_t wConfig,
										uint8_t *pBuffer,
										uint16_t wBufferLength)
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t		PH_MEMLOC_REM aCommand[4];
    aCommand[0] = (uint8_t)(wConfig & 0xFF);
    aCommand[1] = (uint8_t)(wConfig >> 8);
    aCommand[2] = (uint8_t)(wBufferLength & 0xFF);
    aCommand[3] = (uint8_t)(wBufferLength >> 8);

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
					pDataParams,
					PHHAL_HW_RD710_CMD_KS_SET_CONFIG_BUFFER,
					PH_EXCHANGE_BUFFER_FIRST,
					aCommand,
					4,
					NULL,
					NULL));

    return (phhalHw_Rd710_CommandReader(
					pDataParams,
					PHHAL_HW_RD710_CMD_KS_SET_CONFIG_BUFFER,
					PH_EXCHANGE_BUFFER_LAST,
					pBuffer,
					wBufferLength,
					NULL,
					NULL));
}

phStatus_t phhalHw_Rd710_Cmd_KS_GetConfig(
										phhalHw_Rd710_DataParams_t * pDataParams,
										uint16_t wConfig,
										uint16_t * pValue)
	{
		phStatus_t  PH_MEMLOC_REM statusTmp;
		uint8_t *	PH_MEMLOC_REM pRxBuffer;
		uint16_t	PH_MEMLOC_REM wRxLength;
		uint8_t		PH_MEMLOC_REM aCommand[2];
		aCommand[0] = (uint8_t)(wConfig & 0xFF);
		aCommand[1] = (uint8_t)(wConfig >> 8);
		PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
										pDataParams,
										PHHAL_HW_RD710_CMD_KS_GET_CONFIG,
										PH_EXCHANGE_DEFAULT,
										aCommand,
										2,
										&pRxBuffer,
										&wRxLength));
		if (wRxLength != 2)
		{
			return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
		}
		*pValue = (uint16_t)pRxBuffer[0];
		*pValue = *pValue | (uint16_t)((uint16_t)pRxBuffer[1] << 8);
		return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL); 
	}


phStatus_t phhalHw_Rd710_Cmd_KS_GetConfigStr(
										phhalHw_Rd710_DataParams_t * pDataParams,
										uint16_t wConfig,
										uint8_t ** ppBuffer,
										uint16_t * pBufferLength)
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t		PH_MEMLOC_REM aCommand[3];
    uint16_t	PH_MEMLOC_REM wRxLength;
    uint16_t	PH_MEMLOC_REM wOffset;
    aCommand[0] = (uint8_t)(wConfig & 0xFF);
    aCommand[1] = (uint8_t)(wConfig >> 8);
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
										pDataParams,
										PHHAL_HW_RD710_CMD_KS_GET_CONFIG_BUFFER,
										PH_EXCHANGE_DEFAULT,
										aCommand,
										3,
										ppBuffer,
										&wRxLength));
    if (wRxLength < 2)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
    }
    wOffset = 0;
    *pBufferLength  = (uint16_t)*ppBuffer[wOffset++];
    *pBufferLength |= (uint16_t)*ppBuffer[wOffset++] << 8;
    *ppBuffer = *ppBuffer + 2;
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}


phStatus_t phhalHw_Rd710_Cmd_KS_ChangeKUC(
										phhalHw_Rd710_DataParams_t * pDataParams,                    
										uint16_t wRefNoKUC,
										uint32_t dwLimit)
{
    uint8_t PH_MEMLOC_REM aCommand[6];
    aCommand[0] = (uint8_t)(wRefNoKUC & 0xFF);
    aCommand[1] = (uint8_t)(wRefNoKUC >> 8);
    aCommand[2] = (uint8_t)(dwLimit & 0xFF);
    aCommand[3] = (uint8_t)((dwLimit >>  8) & 0xFF);
    aCommand[4] = (uint8_t)((dwLimit >> 16) & 0xFF);
    aCommand[5] = (uint8_t)((dwLimit >> 24) & 0xFF);
    return (phhalHw_Rd710_CommandReader(
										pDataParams,
										PHHAL_HW_RD710_CMD_KS_CHANGE_KUC,
										PH_EXCHANGE_DEFAULT,
										aCommand,
										6,
										NULL,
										NULL));
}


phStatus_t phhalHw_Rd710_Cmd_KS_GetKUC(
                                       phhalHw_Rd710_DataParams_t * pDataParams,
                                       uint16_t wRefNoKUC,
                                       uint32_t * pdwLimit,
                                       uint32_t * pdwCurVal)
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *	PH_MEMLOC_REM pRxBuffer;
    uint16_t	PH_MEMLOC_REM wRxLength;
    uint8_t		PH_MEMLOC_REM aCommand[2];

    aCommand[0] = (uint8_t)(wRefNoKUC & 0xFF);
    aCommand[1] = (uint8_t)(wRefNoKUC >> 8);

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_KS_GET_KUC,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        2,
        &pRxBuffer,
        &wRxLength));

    if (wRxLength != 8)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
    }

    *pdwLimit	= (uint32_t)pRxBuffer[0];
    *pdwLimit  |= (uint32_t)((uint32_t)pRxBuffer[1] << 8);
    *pdwLimit  |= (uint32_t)((uint32_t)pRxBuffer[2] << 16);
    *pdwLimit  |= (uint32_t)((uint32_t)pRxBuffer[3] << 24);
    *pdwCurVal  = (uint32_t)pRxBuffer[4];
    *pdwCurVal |= (uint32_t)((uint32_t)pRxBuffer[5] << 8);
    *pdwCurVal |= (uint32_t)((uint32_t)pRxBuffer[6] << 16);
    *pdwCurVal |= (uint32_t)((uint32_t)pRxBuffer[7] << 24);

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL); 
}

phStatus_t phhalHw_Rd710_Cmd_CID_GetFreeCid(
										phhalHw_Rd710_DataParams_t * pDataParams,
										uint8_t * pCid  )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *    PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_CID_GET_FREE_CID,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        &pRxBuffer,
        &wRxLength
        ));

    if (wRxLength != 1)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
    }

    *pCid = pRxBuffer[0];
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd710_Cmd_CID_FreeCid(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint8_t bCid
    )
{
    return (phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_CID_FREE_CID,
        PH_EXCHANGE_DEFAULT,
        &bCid,
        1,
        NULL,
        NULL
        ));
}

phStatus_t phhalHw_Rd710_Cmd_I14443P4_SetProtocol(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint8_t   bCidEnable,
    uint8_t   bCid,
    uint8_t   bNadEnable,
    uint8_t   bNad,
    uint8_t   bFwi,
    uint8_t   bFsdi,
    uint8_t   bFsci
    )
{
    uint8_t PH_MEMLOC_REM aCommand[7];

    aCommand[0] = bCidEnable;
    aCommand[1] = bCid;
    aCommand[2] = bNadEnable;
    aCommand[3] = bNad;
    aCommand[4] = bFwi;
    aCommand[5] = bFsdi;
    aCommand[6] = bFsci;

    return phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P4_SET_PROTOCOL,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        7,
        NULL,
        NULL);
}

phStatus_t phhalHw_Rd710_Cmd_I14443P4_ResetProtocol(
    phhalHw_Rd710_DataParams_t * pDataParams
    )
{
    return (phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P4_RESET_PROTOCOL,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        NULL,
        NULL
        ));
}

phStatus_t phhalHw_Rd710_Cmd_I14443P4_Deselect(
    phhalHw_Rd710_DataParams_t * pDataParams
    )
{
    return (phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P4_DESELECT,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        NULL,
        NULL
        ));
}

phStatus_t phhalHw_Rd710_Cmd_I14443P4_PresCheck(
    phhalHw_Rd710_DataParams_t * pDataParams
    )
{
    return (phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P4_PRES_CHECK,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        NULL,
        NULL
        ));
}

phStatus_t phhalHw_Rd710_Cmd_I14443P4_Exchange(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint16_t wOption,
    uint8_t * pTxBuffer,
    uint16_t wTxLength,
    uint8_t ** ppRxBuffer,
    uint16_t * pRxLength
    )
{
    return phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P4_EXCHANGE,
        wOption,
        pTxBuffer,
        wTxLength,
        ppRxBuffer,
        pRxLength
        );
}

phStatus_t phhalHw_Rd710_Cmd_I14443P4_SetConfig(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint16_t wConfig,
    uint16_t wValue
    )
{
    uint8_t PH_MEMLOC_REM aCommand[4];

    aCommand[0] = (uint8_t)(wConfig & 0xFF);
    aCommand[1] = (uint8_t)(wConfig >> 8);
    aCommand[2] = (uint8_t)(wValue & 0xFF);
    aCommand[3] = (uint8_t)(wValue >> 8);

    return (phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P4_SET_CONFIG,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        4,
        NULL,
        NULL));
}

phStatus_t phhalHw_Rd710_Cmd_I14443P4_GetConfig(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint16_t wConfig,
    uint16_t * pValue
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *   PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;
    uint8_t     PH_MEMLOC_REM aCommand[2];

    aCommand[0] = (uint8_t)(wConfig & 0xFF);
    aCommand[1] = (uint8_t)(wConfig >> 8);

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P4_GET_CONFIG,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        2,
        &pRxBuffer,
        &wRxLength));

    if (wRxLength != 2)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
    }
    *pValue = (uint16_t)pRxBuffer[0] + ((uint16_t)pRxBuffer[1] << 8);

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL); 
}

phStatus_t phhalHw_Rd710_Cmd_I14443P4A_Rats(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint8_t bFsdi,
    uint8_t bCid,
    uint8_t * pAts
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *   PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;
    uint8_t     PH_MEMLOC_REM aCommand[2];

    aCommand[0] = bFsdi;
    aCommand[1] = bCid;

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P4A_RATS,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        2,
        &pRxBuffer,
        &wRxLength));

    if (wRxLength < 1)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
    }

    memcpy (pAts, pRxBuffer, wRxLength); /* PRQA S 3200 */
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd710_Cmd_I14443P4A_Pps(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint8_t bDri,
    uint8_t bDsi
    )
{
    uint8_t PH_MEMLOC_REM aCommand[2];

    aCommand[0] = bDri;
    aCommand[1] = bDsi;

    return (phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P4A_PPS,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        2,
        NULL,
        NULL));
}

phStatus_t phhalHw_Rd710_Cmd_I14443P4A_ActivateCard(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint8_t bFsdi,
    uint8_t bCid,
    uint8_t bDri,
    uint8_t bDsi,
    uint8_t * pAts
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *   PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;
    uint8_t     PH_MEMLOC_REM aCommand[4];

    aCommand[0] = bFsdi;
    aCommand[1] = bCid;
    aCommand[2] = bDri;
    aCommand[3] = bDsi;

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P4A_ACTIVATE_CARD,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        4,
        &pRxBuffer,
        &wRxLength));

    if (wRxLength < 1)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
    }
    memcpy (pAts, pRxBuffer, wRxLength); /* PRQA S 3200 */
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd710_Cmd_I14443P4A_GetProtocolParams(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint8_t * pCidEnabled,
    uint8_t * pCid,
    uint8_t * pNadSupported,
    uint8_t * pFwi,
    uint8_t * pFsdi,
    uint8_t * pFsci
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *    PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P4A_GET_PROTOCOL_PARAMS,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        &pRxBuffer,
        &wRxLength
        ));
    if (wRxLength != 6)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
    }

    * pCidEnabled    = *(pRxBuffer++);
    * pCid           = *(pRxBuffer++);
    * pNadSupported  = *(pRxBuffer++);
    * pFwi           = *(pRxBuffer++);
    * pFsdi          = *(pRxBuffer++);
    * pFsci          = *(pRxBuffer++);

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd710_Cmd_I14443P3A_RequestA(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint8_t * pAtqa
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *   PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P3A_REQUEST_A,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        &pRxBuffer,
        &wRxLength
        ));
    if (wRxLength != 2)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
    }
    memcpy (pAtqa, pRxBuffer, wRxLength); /* PRQA S 3200 */

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd710_Cmd_I14443P3A_WakeUpA(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint8_t * pAtqa
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *    PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P3A_WAKEUP_A,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        &pRxBuffer,
        &wRxLength
        ));
    if (wRxLength != 2)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
    }
    memcpy (pAtqa, pRxBuffer, wRxLength); /* PRQA S 3200 */

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd710_Cmd_I14443P3A_HaltA(
    phhalHw_Rd710_DataParams_t * pDataParams
    )
{
    return (phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P3A_HALT_A,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        NULL,
        NULL
        ));
}

phStatus_t phhalHw_Rd710_Cmd_I14443P3A_Anticollision(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint8_t bCascadeLevel,
    uint8_t * pUidIn,
    uint8_t bNvbUidIn,
    uint8_t * pUidOut,
    uint8_t * pNvbUidOut
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *   PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;
    uint16_t    PH_MEMLOC_REM wUidNbBytes;
    uint8_t     PH_MEMLOC_REM aCommand[12];
    uint16_t    PH_MEMLOC_REM TxBufferLength = 0;

    aCommand[TxBufferLength++] = bCascadeLevel;
    aCommand[TxBufferLength++] = bNvbUidIn;

    if ((pUidIn != NULL) && (bNvbUidIn != 0))
    {
        wUidNbBytes = (uint16_t)(bNvbUidIn >> 4);
        if (bNvbUidIn & 0x0F)
        {
            ++wUidNbBytes;
        }
        memcpy (&aCommand[TxBufferLength], pUidIn, wUidNbBytes); /* PRQA S 3200 */
        TxBufferLength = TxBufferLength + wUidNbBytes;
    }

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P3A_ANTICOLLISION,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        12,
        &pRxBuffer,
        &wRxLength));

    if (wRxLength < 1)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
    }

    *pNvbUidOut = pRxBuffer[0];
    wUidNbBytes = (uint16_t)(*pNvbUidOut >> 4);
    if ((*pNvbUidOut & 0xFF) != 0)
    {
        ++wUidNbBytes;
    }
    memcpy (pUidOut, &pRxBuffer[1], wUidNbBytes); /* PRQA S 3200 */

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd710_Cmd_I14443P3A_Select(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint8_t bCascadeLevel,
    uint8_t * pUidIn,
    uint8_t * pSak
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *   PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;
    uint8_t     PH_MEMLOC_REM aCommand[5];
    uint16_t    PH_MEMLOC_REM TxBufferLength = 0;

    aCommand[TxBufferLength++] = bCascadeLevel;
    memcpy(&aCommand[TxBufferLength], pUidIn, 4); /* PRQA S 3200 */

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P3A_SELECT,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        5,
        &pRxBuffer,
        &wRxLength));

    if (wRxLength != 1)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
    }
    *pSak = pRxBuffer[0];
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd710_Cmd_I14443P3A_ActivateCard(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint8_t * pUidIn,
    uint8_t bLenUidIn,
    uint8_t * pUidOut,
    uint8_t * pLenUidOut,
    uint8_t * pSak,
    uint8_t * pMoreCardsAvailable
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *    PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wRxLength;

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P3A_ACTIVATE_CARD,
        PH_EXCHANGE_DEFAULT,
        pUidIn,
        bLenUidIn,
        &pRxBuffer,
        &wRxLength));

    if (wRxLength < 2)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_HAL);
    }

    *pLenUidOut = (uint8_t)(wRxLength - 2);
    *pSak = pRxBuffer[0];
    *pMoreCardsAvailable = pRxBuffer[1];
    memcpy (pUidOut, &pRxBuffer[2], *pLenUidOut); /* PRQA S 3200 */

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd710_Cmd_I14443P3A_Exchange(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint16_t wOption,
    uint8_t * pTxBuffer,
    uint16_t wTxLength,
    uint8_t ** ppRxBuffer,
    uint16_t * pRxLength
    )
{
    return phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P3A_EXCHANGE,
        wOption,
        pTxBuffer,
        wTxLength,
        ppRxBuffer,
        pRxLength);
}

phStatus_t phhalHw_Rd710_Cmd_I14443P3A_GetSerialNo(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint8_t * pRxBuffer,
    uint8_t * pRxLength
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t *    PH_MEMLOC_REM pRxBufferTmp;
    uint16_t    PH_MEMLOC_REM wRxLength;

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_I14443P3A_GET_SERIAL_NO,
        PH_EXCHANGE_DEFAULT,
        NULL,
        0,
        &pRxBufferTmp,
        &wRxLength));

    *pRxLength = (uint8_t)wRxLength;
    memcpy (pRxBuffer, pRxBufferTmp, wRxLength); /* PRQA S 3200 */
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd710_Cmd_MIFARE_ExchangeL3(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint16_t wOption,
    uint8_t * pTxBuffer,
    uint16_t wTxLength,
    uint8_t ** ppRxBuffer,
    uint16_t * pRxLength
    )
{
    uint16_t	PH_MEMLOC_REM RxLength;
    uint8_t *	PH_MEMLOC_REM pRxBuffer;

    /* Check if caller has provided valid RxBuffer */
    if (ppRxBuffer == NULL)
    {
        ppRxBuffer = &pRxBuffer;
    }
    if (pRxLength == NULL)
    {
        pRxLength = &RxLength;
    }

    return phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_MIFARE_EXCHANGE_L3,
        wOption,
        pTxBuffer,
        wTxLength,
        ppRxBuffer,
        pRxLength);
}

phStatus_t phhalHw_Rd710_Cmd_MIFARE_ExchangeL4(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint16_t wOption,
    uint8_t * pTxBuffer,
    uint16_t wTxLength,
    uint8_t ** ppRxBuffer,
    uint16_t * pRxLength
    )
{
    uint16_t	PH_MEMLOC_REM RxLength;
    uint8_t *	PH_MEMLOC_REM pRxBuffer;

    /* Check if caller has provided valid RxBuffer */
    if (ppRxBuffer == NULL)
    {
        ppRxBuffer = &pRxBuffer;
    }
    if (pRxLength == NULL)
    {
        pRxLength = &RxLength;
    }

    return phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_MIFARE_EXCHANGE_L4,
        wOption,
        pTxBuffer,
        wTxLength,
        ppRxBuffer,
        pRxLength);
}

phStatus_t phhalHw_Rd710_Cmd_MIFARE_ExchangePc(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint16_t wOption,
    uint8_t * pTxBuffer,
    uint16_t wTxLength,
    uint8_t ** ppRxBuffer,
    uint16_t * pRxLength
    )
{
    uint16_t	PH_MEMLOC_REM RxLength;
    uint8_t *	PH_MEMLOC_REM pRxBuffer;

    /* Check if caller has provided valid RxBuffer */
    if (ppRxBuffer == NULL)
    {
        ppRxBuffer = &pRxBuffer;
    }
    if (pRxLength == NULL)
    {
        pRxLength = &RxLength;
    }

    return phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_MIFARE_EXCHANGE_PC,
        wOption,
        pTxBuffer,
        wTxLength,
        ppRxBuffer,
        pRxLength);
}

phStatus_t phhalHw_Rd710_Cmd_MIFARE_ExchangeRaw(
    phhalHw_Rd710_DataParams_t * pDataParams,
    uint16_t wOption,
    uint8_t * pTxBuffer,
    uint16_t wTxLength,
    uint8_t bTxLastBits,
    uint8_t ** ppRxBuffer,
    uint16_t * pRxLength,
    uint8_t * pRxLastBits
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t	PH_MEMLOC_REM RxLength;
    uint8_t *	PH_MEMLOC_REM pRxBuffer;

    /* Check if caller has provided valid RxBuffer */
    if (ppRxBuffer == NULL)
    {
        ppRxBuffer = &pRxBuffer;
    }
    if (pRxLength == NULL)
    {
        pRxLength = &RxLength;
    }

    /* Set TxLastBits */
    pDataParams->bTxLastBits = bTxLastBits;

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_MIFARE_EXCHANGE_RAW,
        wOption,
        pTxBuffer,
        wTxLength,
        ppRxBuffer,
        pRxLength));

    /* No buffered operation -> retrieve content */
    if (!(wOption & PH_EXCHANGE_BUFFERED_BIT))
    {
        /* Retrieve RxLastBits */
        *pRxLastBits = *ppRxBuffer[0];

        /* shift pointer and length */
        (*ppRxBuffer)++;
        (*pRxLength)--;
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rd710_Cmd_MIFARE_MfcAuthenticateKeyNo(
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
    memcpy(&aCommand[2], pUid, 4);  /* PRQA S 3200 */
    aCommand[6] = (uint8_t)(wKeyNo & 0xFF);
    aCommand[7] = (uint8_t)(wKeyNo >> 8);
    aCommand[8] = (uint8_t)(wKeyVersion & 0xFF);
    aCommand[9] = (uint8_t)(wKeyVersion >> 8);

    return phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_MIFARE_MFC_AUTH_KEY,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        10,
        NULL,
        NULL);
}

phStatus_t phhalHw_Rd710_Cmd_MIFARE_MfcAuthenticate(
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

    return phhalHw_Rd710_CommandReader(
        pDataParams,
        PHHAL_HW_RD710_CMD_MIFARE_MFC_AUTH,
        PH_EXCHANGE_DEFAULT,
        aCommand,
        12,
        NULL,
        NULL);
}

#endif /* NXPBUILD__PHHAL_HW_RD710 */
