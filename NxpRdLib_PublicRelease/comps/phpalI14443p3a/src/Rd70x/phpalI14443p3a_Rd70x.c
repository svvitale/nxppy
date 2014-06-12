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
* $Revision: 1.6 $
* $Date: Fri Apr 15 09:28:02 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#include <ph_Status.h>
#include <ph_RefDefs.h>
#include <phhalHw.h>
#include <phpalI14443p3a.h>

#ifdef NXPBUILD__PHPAL_I14443P3A_RD70X

#include "phpalI14443p3a_Rd70x.h"
#include <phhalHw_Rd70x_Reg.h>
#include <phhalHw_Rd70x_Cmd.h>

phStatus_t phpalI14443p3a_Rd70x_Init(
                                     phpalI14443p3a_Rd70x_DataParams_t * pDataParams,
                                     uint16_t wSizeOfDataParams,
                                     phhalHw_Rd70x_DataParams_t * pHalDataParams
                                     )
{
    if (sizeof(phpalI14443p3a_Rd70x_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P3A);
    }
    PH_ASSERT_NULL (pDataParams);
    PH_ASSERT_NULL (pHalDataParams);

    /* init private data */
    pDataParams->wId            = PH_COMP_PAL_ISO14443P3A | PHPAL_I14443P3A_RD70X_ID;
    pDataParams->pHalDataParams = pHalDataParams;
    pDataParams->bUidLength     = 0;
    pDataParams->bUidComplete   = 0;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_ISO14443P3A);
}

phStatus_t phpalI14443p3a_Rd70x_RequestA(
    phpalI14443p3a_Rd70x_DataParams_t * pDataParams,
    uint8_t * pAtqa
    )
{
    phStatus_t PH_MEMLOC_REM statusTmp;

    /* Set RxDeafTime to 8 Bits */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_RXDEAFBITS, 8));

    /* Perform Command */
    return phhalHw_Rd70x_Cmd_MfPiccRequest(pDataParams->pHalDataParams, 0x26, pAtqa);
}

phStatus_t phpalI14443p3a_Rd70x_WakeUpA(
                                        phpalI14443p3a_Rd70x_DataParams_t * pDataParams,
                                        uint8_t * pAtqa
                                        )
{
    phStatus_t PH_MEMLOC_REM statusTmp;

    /* Set RxDeafTime to 8 Bits */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_RXDEAFBITS, 8));

    /* Perform Command */
    return phhalHw_Rd70x_Cmd_MfPiccRequest(pDataParams->pHalDataParams, 0x52, pAtqa);
}

phStatus_t phpalI14443p3a_Rd70x_HaltA(
                                      phpalI14443p3a_Rd70x_DataParams_t * pDataParams
                                      )
{
    return phhalHw_Rd70x_Cmd_MfPiccHalt(pDataParams->pHalDataParams);
}

phStatus_t phpalI14443p3a_Rd70x_Anticollision(
    phpalI14443p3a_Rd70x_DataParams_t * pDataParams,
    uint8_t bCascadeLevel,
    uint8_t * pUidIn,
    uint8_t bNvbUidIn,
    uint8_t * pUidOut,
    uint8_t * pNvbUidOut
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bSak;
    uint8_t     PH_MEMLOC_REM abUidTmp[4];
    uint8_t     PH_MEMLOC_REM bUidLen;

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

    /* ANTICOLLISION */
    if (bNvbUidIn != 0x40)
    {
        /* Get UIDin length */
        bUidLen = bNvbUidIn >> 4;
        if (bNvbUidIn & 0x0F)
        {
            ++bUidLen;
        }

        /* Copy UIDin to temporary buffer */
        memcpy(abUidTmp, pUidIn, bUidLen); /* PRQA S 3200 */

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_PiccCascAnticoll(pDataParams->pHalDataParams, bCascadeLevel, bNvbUidIn, abUidTmp));

        /* Save UID */
        switch (bCascadeLevel)
        {
        case PHPAL_I14443P3A_CASCADE_LEVEL_1:
            if (abUidTmp[0] != 0x88)
            {
                memcpy(pDataParams->abUid, &abUidTmp[0], 4); /* PRQA S 3200 */
                pDataParams->bUidLength = 4;
            }
            else
            {
                memcpy(pDataParams->abUid, &abUidTmp[1], 3); /* PRQA S 3200 */
                pDataParams->bUidLength = 3;
            }
            break;
        case PHPAL_I14443P3A_CASCADE_LEVEL_2:
            if (abUidTmp[0] != 0x88)
            {
                memcpy(&pDataParams->abUid[3], &abUidTmp[0], 4); /* PRQA S 3200 */
                pDataParams->bUidLength = 7;
            }
            else
            {
                memcpy(&pDataParams->abUid[3], &abUidTmp[1], 3); /* PRQA S 3200 */
                pDataParams->bUidLength = 6;
            }
            break;
        case PHPAL_I14443P3A_CASCADE_LEVEL_3:
            memcpy(&pDataParams->abUid[6], &abUidTmp[0], 4); /* PRQA S 3200 */
            pDataParams->bUidLength = 10;
            break;
        default:
            return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_PAL_ISO14443P3A);
        }

        /* Copy temporary buffer to UIDout */
        memcpy(pUidOut, abUidTmp, 4); /* PRQA S 3200 */
        *pNvbUidOut = 0x40;
    }
    /* SELECT */
    else
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phpalI14443p3a_Rd70x_Select(pDataParams, bCascadeLevel, pUidIn, &bSak));
        pUidOut[0] = bSak;

        /* Cascade Bit not set -> UID is complete */
        if (!(bSak & 0x04))
        {
            pDataParams->bUidComplete = 1;
        }
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_ISO14443P3A);
}

phStatus_t phpalI14443p3a_Rd70x_Select(
                                       phpalI14443p3a_Rd70x_DataParams_t * pDataParams,
                                       uint8_t bCascadeLevel,
                                       uint8_t * pUidIn,
                                       uint8_t * pSak
                                       )
{
    phStatus_t PH_MEMLOC_REM statusTmp;

    /* Check for invalid bCascadeIndex parameter */
    switch (bCascadeLevel)
    {
    case PHPAL_I14443P3A_CASCADE_LEVEL_1:
    case PHPAL_I14443P3A_CASCADE_LEVEL_2:
    case PHPAL_I14443P3A_CASCADE_LEVEL_3:
        break;
    default:
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_ISO14443P3A);
    }

    /* Reset UID complete flag */
    pDataParams->bUidComplete = 0;

    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_PiccCascSelect(pDataParams->pHalDataParams, bCascadeLevel, pUidIn, pSak));

    /* Cascade Bit not set -> UID is complete */
    if (!(*pSak & 0x04))
    {
        pDataParams->bUidComplete = 1;
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_ISO14443P3A);
}

phStatus_t phpalI14443p3a_Rd70x_ActivateCard(
    phpalI14443p3a_Rd70x_DataParams_t * pDataParams,
    uint8_t * pUidIn,
    uint8_t bLenUidIn,
    uint8_t * pUidOut,
    uint8_t * pLenUidOut,
    uint8_t * pSak,
    uint8_t * pMoreCardsAvailable
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM abAtqA[2];
    uint8_t     PH_MEMLOC_REM bRegVal;
    uint8_t *   PH_MEMLOC_REM pRxBuffer;
    uint16_t    PH_MEMLOC_REM wLength;

    /* Parameter check */
    if ((bLenUidIn != 0) &&
        (bLenUidIn != 4) &&
        (bLenUidIn != 7) &&
        (bLenUidIn != 10))
    {
        /* Given UID length is invalid, return error */
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_ISO14443P3A);
    }

    /* Reset UID complete flag */
    pDataParams->bUidComplete = 0;

    if (bLenUidIn == 0)
    {
        /* Disable CRC */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_TXCRC, PH_OFF));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_RXCRC, PH_OFF));

        /* Move Picc to READY state of 144443 */
        PH_CHECK_SUCCESS_FCT(statusTmp, phpalI14443p3a_Rd70x_RequestA(pDataParams, abAtqA));

        /* Perform anticollision */
        abAtqA[0] = 0x93;
        abAtqA[1] = 0x20;
        statusTmp = phpalI14443p3a_Rd70x_Exchange (pDataParams, PH_EXCHANGE_DEFAULT, abAtqA, 2, &pRxBuffer, &wLength);

        /* Check whether a collision has occured and set MoreCardsAvailable flag*/
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister (pDataParams->pHalDataParams, PHHAL_HW_RD70X_REG_ERROR_FLAG, &bRegVal));
        if ((bRegVal & PHHAL_HW_RD70X_BIT_COLL_ERR) == PHHAL_HW_RD70X_BIT_COLL_ERR)
        {
            *pMoreCardsAvailable = 1;
        }
        else
        {
            *pMoreCardsAvailable = 0;
        }

        /* Generate Picc error to move back to IDLE state of 144443 */
        statusTmp = phpalI14443p3a_Rd70x_RequestA(pDataParams, abAtqA);

        /* Now we can proceed with a complete 14443-3 activation */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_PiccActivateIdle(pDataParams->pHalDataParams, 0, abAtqA, pSak, pUidOut, pLenUidOut));
    }
    else
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rd70x_Cmd_PiccActivateWakeup(pDataParams->pHalDataParams, 0, abAtqA, pSak, pUidIn, bLenUidIn));

        /* Copy and Store UID */
        memcpy(pUidOut, pUidIn, bLenUidIn); /* PRQA S 3200 */
        *pLenUidOut = bLenUidIn;
    }

    /* Set UID complete flag */
    pDataParams->bUidComplete = 1;

    /* Copy and Store UID */
    memcpy(pDataParams->abUid, pUidOut, *pLenUidOut); /* PRQA S 3200 */
    pDataParams->bUidLength = *pLenUidOut;

    /* Enable CRC */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_TXCRC, PH_ON));
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_RXCRC, PH_ON));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_ISO14443P3A);
}

phStatus_t phpalI14443p3a_Rd70x_Exchange(
    phpalI14443p3a_Rd70x_DataParams_t * pDataParams,
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

phStatus_t phpalI14443p3a_Rd70x_GetSerialNo(
    phpalI14443p3a_Rd70x_DataParams_t * pDataParams,
    uint8_t * pRxBuffer,
    uint8_t * pRxLength
    )
{
    /* Return an error if UID is not complete */
    if (!pDataParams->bUidComplete)
    {
        return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_PAL_ISO14443P3A);
    }

    memcpy(pRxBuffer, pDataParams->abUid, pDataParams->bUidLength); /* PRQA S 3200 */
    *pRxLength = pDataParams->bUidLength;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_ISO14443P3A);
}

#endif /* NXPBUILD__PHPAL_I14443P3A_RD70X */
