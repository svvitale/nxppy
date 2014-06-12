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
* Rc632 Keystore Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:27:54 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#include <ph_Status.h>
#include <ph_RefDefs.h>
#include <phKeyStore.h>
#include <phhalHw.h>

#ifdef NXPBUILD__PH_KEYSTORE_RC632

#include "phKeyStore_Rc632.h"
#include "phKeyStore_Rc632_Int.h"

phStatus_t phKeyStore_Rc632_Init(
                                 phKeyStore_Rc632_DataParams_t * pDataParams,
                                 uint16_t wSizeOfDataParams, 
                                 void * pHalDataParams
                                 )
{
    /* Dataparam structure check */
    if (sizeof(phKeyStore_Rc632_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
    }
    PH_ASSERT_NULL (pDataParams);
    PH_ASSERT_NULL (pHalDataParams);

    /* Init private data */
    pDataParams->wId = PH_COMP_KEYSTORE| PH_KEYSTORE_RC632_ID;
    pDataParams->pHalDataParams = pHalDataParams;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Rc632_FormatKeyEntry(
    phKeyStore_Rc632_DataParams_t * pDataParams,
    uint16_t wKeyNo,
    uint16_t wNewKeyType 
    )
{
    uint8_t PH_MEMLOC_BUF bKey[PH_KEYSTORE_KEY_TYPE_MIFARE_SIZE];

    /* clear key buffer */
    memset(bKey, 0x00, PH_KEYSTORE_KEY_TYPE_MIFARE_SIZE); /* PRQA S 3200 */

    return phKeyStore_Rc632_SetKeyAtPos(pDataParams, wKeyNo, 0, wNewKeyType, bKey, 0);
}

phStatus_t phKeyStore_Rc632_SetKey(
                                   phKeyStore_Rc632_DataParams_t * pDataParams,
                                   uint16_t wKeyNo,
                                   uint16_t wKeyVersion,
                                   uint16_t wKeyType,
                                   uint8_t * pNewKey,
                                   uint16_t wNewKeyVersion
                                   )
{
    /* satisfy compiler */
    if (wKeyVersion);
    return (phKeyStore_Rc632_SetKeyAtPos(pDataParams, wKeyNo, 0, wKeyType, pNewKey, wNewKeyVersion));
}

phStatus_t phKeyStore_Rc632_SetKeyAtPos(
                                        phKeyStore_Rc632_DataParams_t * pDataParams,
                                        uint16_t wKeyNo,
                                        uint16_t wPos,
                                        uint16_t wKeyType,
                                        uint8_t * pNewKey,
                                        uint16_t wNewKeyVersion
                                        )
{
    uint8_t     PH_MEMLOC_BUF Cmd[2 + PH_KEYSTORE_RC632_EEP_KEY_LENGTH];
    uint8_t *   PH_MEMLOC_REM pCmd = Cmd;
    uint16_t    PH_MEMLOC_REM EepAddr;
    uint16_t    PH_MEMLOC_COUNT i;

    /* satisfy compiler */
    if (wPos || wNewKeyVersion);

    /* Check if wKeyNo is out of range */
    if (wKeyNo >= PH_KEYSTORE_RC632_NUM_KEYS)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
    }

    /* Retrieve Key type */
    switch(wKeyType)
    {
        /* MIFARE keys are the only supported keys */
    case PH_KEYSTORE_KEY_TYPE_MIFARE:

        /* prepare the header command to be sent */
        EepAddr = PH_KEYSTORE_RC632_EEP_KEY_BASE_ADDR + (wKeyNo * PH_KEYSTORE_RC632_EEP_KEY_LENGTH);
        *(pCmd++) = (uint8_t)(EepAddr & 0xFF);
        *(pCmd++) = (uint8_t)(EepAddr >> 8);

        /* convert key in eeprom key storage format */
        for (i = 0; i < PH_KEYSTORE_KEY_TYPE_MIFARE_SIZE; ++i)
        {
            *(pCmd++) = (uint8_t)((pNewKey[i] >> 4) | ((uint8_t)(pNewKey[i] & 0xF0) ^ 0xF0));
            *(pCmd++) = (uint8_t)(((uint8_t)(pNewKey[i] << 4) ^ 0xF0) | (pNewKey[i] & 0x0F));
        }
        return (phKeyStore_Rc632_WriteE2_Int(pDataParams, Cmd, (2 + PH_KEYSTORE_RC632_EEP_KEY_LENGTH)));

    case PH_KEYSTORE_KEY_TYPE_AES128:
    case PH_KEYSTORE_KEY_TYPE_AES192:
    case PH_KEYSTORE_KEY_TYPE_AES256:
    case PH_KEYSTORE_KEY_TYPE_DES:
    case PH_KEYSTORE_KEY_TYPE_2K3DES:
    case PH_KEYSTORE_KEY_TYPE_3K3DES:

        return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_KEYSTORE);

    default:

        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
    }
}

phStatus_t phKeyStore_Rc632_SetKUC(
                                   phKeyStore_Rc632_DataParams_t * pDataParams,
                                   uint16_t wKeyNo,
                                   uint16_t wRefNoKUC
                                   )
{
    /* satisfy compiler */
    if (pDataParams || wKeyNo || wRefNoKUC);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Rc632_SetFullKeyEntry(
    phKeyStore_Rc632_DataParams_t * pDataParams,
    uint16_t wNoOfKeys,
    uint16_t wKeyNo,
    uint16_t wNewRefNoKUC,
    uint16_t wNewKeyType,
    uint8_t * pNewKeys,
    uint16_t * pNewKeyVersionList
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t    PH_MEMLOC_REM wKeyVersion = 0;
    uint16_t    PH_MEMLOC_COUNT i;

    /* satisfy compiler */
    if (pNewKeyVersionList || wNewRefNoKUC);

    /* check wNoOfKeys */
    if (wNoOfKeys > PH_KEYSTORE_RC632_NUM_VERSIONS)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_KEYSTORE);
    }

    /* set keys */
    for (i = 0; i < wNoOfKeys; ++i)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phKeyStore_Rc632_SetKeyAtPos(pDataParams, wKeyNo,  i, wNewKeyType, &pNewKeys[i*PH_KEYSTORE_KEY_TYPE_MIFARE_SIZE], wKeyVersion));
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Rc632_GetKeyEntry(
                                        phKeyStore_Rc632_DataParams_t * pDataParams,    
                                        uint16_t wKeyNo,
                                        uint16_t wKeyVersionBufSize,
                                        uint16_t * wKeyVersion,
                                        uint16_t * wKeyVersionLength,
                                        uint16_t * pKeyType
                                        )
{
    /* satisfy compiler */
    if (pDataParams || wKeyNo || wKeyVersionBufSize || wKeyVersion || wKeyVersionLength || pKeyType);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Rc632_GetKey(
                                   phKeyStore_Rc632_DataParams_t * pDataParams,    
                                   uint16_t wKeyNo,
                                   uint16_t wKeyVersion,
                                   uint8_t bKeyBufSize,
                                   uint8_t * pKey,
                                   uint16_t * pKeyType
                                   )
{
    /* satisfy compiler */
    if (pDataParams || wKeyNo || wKeyVersion || bKeyBufSize || pKey || pKeyType);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Rc632_SetConfig(
                                      phKeyStore_Rc632_DataParams_t * pDataParams,
                                      uint16_t wConfig,
                                      uint16_t wValue
                                      )
{
    /* satisfy compiler */
    if (pDataParams || wConfig || wValue);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Rc632_SetConfigStr(
    phKeyStore_Rc632_DataParams_t * pDataParams,
    uint16_t wConfig,
    uint8_t *pBuffer,
    uint16_t wBufferLength
    )
{
    /* satisfy compiler */
    if (pDataParams || wConfig || pBuffer || wBufferLength);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Rc632_GetConfig(
                                      phKeyStore_Rc632_DataParams_t * pDataParams,
                                      uint16_t wConfig,
                                      uint16_t * pValue
                                      )
{
    /* satisfy compiler */
    if (pDataParams || wConfig || pValue);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Rc632_GetConfigStr(
    phKeyStore_Rc632_DataParams_t * pDataParams,
    uint16_t wConfig,
    uint8_t ** ppBuffer,
    uint16_t * pBufferLength
    )
{
    /* satisfy compiler */
    if (pDataParams || wConfig || ppBuffer || pBufferLength);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Rc632_ChangeKUC(
                                      phKeyStore_Rc632_DataParams_t * pDataParams,                    
                                      uint16_t wRefNoKUC,
                                      uint32_t dwLimit
                                      )
{
    /* satisfy compiler */
    if (pDataParams || wRefNoKUC || dwLimit);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Rc632_GetKUC(
                                   phKeyStore_Rc632_DataParams_t * pDataParams,
                                   uint16_t wRefNoKUC,
                                   uint32_t * pdwLimit,
                                   uint32_t * pdwCurVal
                                   )
{

    /* satisfy compiler */
    if (pDataParams || wRefNoKUC || pdwLimit || pdwCurVal);
    return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_COMMAND, PH_COMP_KEYSTORE);
}

phStatus_t phKeyStore_Rc632_WriteE2_Int(
                                        phKeyStore_Rc632_DataParams_t * pDataParams,
                                        uint8_t    *pData,
                                        uint16_t DataLength
                                        )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bCmdReg;
    uint16_t    PH_MEMLOC_COUNT i;

    /* disable all interrupt */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(    
        pDataParams->pHalDataParams, 
        PH_KEYSTORE_RC632_REG_INT_EN, 
        0x7F
        ));

    /* Stop an eventual previous Command (enter Idle state) */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(    
        pDataParams->pHalDataParams,
        PH_KEYSTORE_RC632_REG_COMMAND,
        PH_KEYSTORE_RC632_CMD_IDLE
        ));

    /* Flush Rc632 fifo */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(    
        pDataParams->pHalDataParams,
        PH_KEYSTORE_RC632_REG_CONTROL,
        PH_KEYSTORE_RC632_BIT_FLUSHFIFO
        ));

    /* Fill up Rc632 fifo with data associated to WriteE2 command */
    for (i = 0; i < DataLength; ++i)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(    
            pDataParams->pHalDataParams,
            PH_KEYSTORE_RC632_REG_FIFO_DATA,
            *pData++
            ));
    }

    /* Execute Rc632 WriteE2 command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(    
        pDataParams->pHalDataParams,
        PH_KEYSTORE_RC632_REG_COMMAND,
        PH_KEYSTORE_RC632_CMD_WRITE_E2
        ));

    /* Wait end of execution of Rc632 WriteE2 command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Wait(    
        pDataParams->pHalDataParams,
        PHHAL_HW_TIME_MILLISECONDS,
        PH_KEYSTORE_RC632_EEP_WR_TO_MS
        ));

    /* Check if eeprom is ready */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(    
        pDataParams->pHalDataParams,
        PH_KEYSTORE_RC632_REG_SECONDARY_STATUS,
        &bCmdReg
        ));

    /* Command has to be stopped manually to get back to Idle */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(    
        pDataParams->pHalDataParams,
        PH_KEYSTORE_RC632_REG_COMMAND,
        PH_KEYSTORE_RC632_CMD_IDLE
        ));

    /* Check for write error */
    if (!(bCmdReg & PH_KEYSTORE_RC632_BIT_E2READY))
    {
        return PH_ADD_COMPCODE(PH_ERR_READ_WRITE_ERROR, PH_COMP_KEYSTORE);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_KEYSTORE);
}

#endif /* NXPBUILD__PH_KEYSTORE_RC632 */
