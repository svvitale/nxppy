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
* Software ISO14443-4A Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.5 $
* $Date: Fri Apr 15 09:27:32 2011 $
*
* History:
*  CHu: Generated 29. May 2009
*
*/

#include <ph_Status.h>
#include <phhalHw.h>
#include <phpalI14443p4a.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHPAL_I14443P4A_SW

#include "phpalI14443p4a_Sw.h"
#include "phpalI14443p4a_Sw_Int.h"

#define I14443P4A_SW_IS_INVALID_BLOCK_STATUS(bStatus)                       \
    ((                                                                      \
    (((bStatus) & PH_ERR_MASK) == PH_ERR_IO_TIMEOUT) ||                     \
    (((bStatus) & PH_ERR_MASK) == PH_ERR_INTEGRITY_ERROR) ||                \
    (((bStatus) & PH_ERR_MASK) == PH_ERR_FRAMING_ERROR) ||                  \
    (((bStatus) & PH_ERR_MASK) == PH_ERR_COLLISION_ERROR))                  \
    ? 1 : 0                                                                 \
    )

phStatus_t phpalI14443p4a_Sw_Init(
                                  phpalI14443p4a_Sw_DataParams_t * pDataParams,
                                  uint16_t wSizeOfDataParams,
                                  void * pHalDataParams
                                  )
{
    if (sizeof(phpalI14443p4a_Sw_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_PAL_ISO14443P4A);
    }
	PH_ASSERT_NULL (pDataParams);
	PH_ASSERT_NULL (pHalDataParams);

    /* init private data */
    pDataParams->wId            = PH_COMP_PAL_ISO14443P4A | PHPAL_I14443P4A_SW_ID;
    pDataParams->pHalDataParams = pHalDataParams;
    pDataParams->bCidSupported  = PH_OFF;
    pDataParams->bNadSupported  = PH_OFF;
    pDataParams->bCid           = 0x00;
    pDataParams->bBitRateCaps   = 0x00;
    pDataParams->bFwi           = PHPAL_I14443P4A_SW_FWI_DEFAULT;
    pDataParams->bFsci          = PHPAL_I14443P4A_SW_FSCI_DEFAULT;
    pDataParams->bFsdi          = 0x00;
    pDataParams->bDri           = 0x00;
    pDataParams->bDsi           = 0x00;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_ISO14443P4A);
}

phStatus_t phpalI14443p4a_Sw_Rats(
                                  phpalI14443p4a_Sw_DataParams_t * pDataParams,
                                  uint8_t bFsdi,
                                  uint8_t bCid,
                                  uint8_t * pAts
                                  )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM cmd[2];
    uint8_t     PH_MEMLOC_REM bAtsIndex;
    uint8_t     PH_MEMLOC_REM bSfgi;
    uint32_t    PH_MEMLOC_REM dwSfgt;
    uint32_t    PH_MEMLOC_REM dwFwt;
    uint8_t *   PH_MEMLOC_REM pResp;
    uint16_t    PH_MEMLOC_REM wRespLength;

    /* Parameter check */
    if ((bFsdi > 8) || (bCid > 14))
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_ISO14443P4A);
    }

    /* Set Activation timeout */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
        pDataParams->pHalDataParams,
        PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,
        PHPAL_I14443P4A_SW_FWT_ACTIVATION_US + PHPAL_I14443P4A_SW_EXT_TIME_US));

    /* Send Rats command */
    cmd[0] = PHPAL_I14443P4A_SW_RATS;
    cmd[1] = (uint8_t)(((bFsdi << 4) & 0xF0) | (bCid & 0x0F));
    status = phhalHw_Exchange(
        pDataParams->pHalDataParams,
        PH_EXCHANGE_DEFAULT,
        cmd,
        2,
        &pResp,
        &wRespLength);

    if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
    {
        /* Check for protocol error */
        if (((uint8_t)wRespLength != pResp[0]) || (wRespLength < 1))
        {
            return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_ISO14443P4A);
        }

        /* Copy ATS buffer */
        memcpy(pAts, pResp, wRespLength);  /* PRQA S 3200 */

        /* Set default values */
        /* */
        pDataParams->bCidSupported  = PH_ON;
        pDataParams->bCid           = bCid;
        pDataParams->bNadSupported  = PH_OFF;
        pDataParams->bBitRateCaps   = 0x00;
        pDataParams->bFwi           = PHPAL_I14443P4A_SW_FWI_DEFAULT;
        pDataParams->bFsdi          = bFsdi;
        pDataParams->bFsci          = PHPAL_I14443P4A_SW_FSCI_DEFAULT;
        pDataParams->bDri           = 0x00;
        pDataParams->bDsi           = 0x00;
        bSfgi                       = PHPAL_I14443P4A_SW_SFGI_DEFAULT;

        /* Retrieve ATS information */
        /* Start parsing with T0 byte */
        bAtsIndex = PHPAL_I14443P4A_SW_ATS_T0;

        /* Parse T0/TA/TB/TC */
        if (wRespLength > 1)
        {
            /* Parse T0 */
            pDataParams->bFsci = pAts[bAtsIndex] & 0x0F;
            if (pDataParams->bFsci > 8)
            {
                pDataParams->bFsci = 8;
            }
            bAtsIndex++;

            /* Parse TA(1) */
            if (pAts[PHPAL_I14443P4A_SW_ATS_T0] & PHPAL_I14443P4A_SW_ATS_TA1_PRESENT)
            {
                /* Check for protocol error */
                if (wRespLength <= bAtsIndex)
                {
                    return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_ISO14443P4A);
                }
                else
                {
                    /* Store Bitrate capabilities */
                    pDataParams->bBitRateCaps = pAts[bAtsIndex];

                    bAtsIndex++;
                }
            }

            /* Parse TB(1) */
            if (pAts[PHPAL_I14443P4A_SW_ATS_T0] & PHPAL_I14443P4A_SW_ATS_TB1_PRESENT)
            {
                /* Check for protocol error */
                if (wRespLength <= bAtsIndex)
                {
                    return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_ISO14443P4A);
                }
                else
                {
                    /* Store Sfgi */
                    bSfgi = pAts[bAtsIndex] & 0x0F;
                    if (bSfgi == 0x0F)
                    {
                        bSfgi = PHPAL_I14443P4A_SW_SFGI_DEFAULT;
                    }

                    /* Store Fwi */
                    pDataParams->bFwi = (pAts[bAtsIndex] >> 4) & 0x0F;
                    if (pDataParams->bFwi == 0x0F)
                    {
                        pDataParams->bFwi = PHPAL_I14443P4A_SW_FWI_DEFAULT;
                    }

                    bAtsIndex++;
                }
            }

            /* Parse TC(1) */
            if (pAts[PHPAL_I14443P4A_SW_ATS_T0] & PHPAL_I14443P4A_SW_ATS_TC1_PRESENT)
            {
                /* Check for protocol error */
                if (wRespLength <= bAtsIndex)
                {
                    return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_ISO14443P4A);
                }
                else
                {
                    /* Check NAD Support */
                    if (pAts[bAtsIndex] & PHPAL_I14443P4A_SW_ATS_TC1_NAD_SUPPORT)
                    {
                        pDataParams->bNadSupported = 1;
                    }

                    /* Check CID Support */
                    if (!(pAts[bAtsIndex] & PHPAL_I14443P4A_SW_ATS_TC1_CID_SUPPORT))
                    {
                        pDataParams->bCidSupported = 0;
                        pDataParams->bCid = 0;
                    }
                }
            }
        }

        /* Calculate SFGT in Microseconds */
        dwSfgt = (uint32_t)(PHPAL_I14443P4A_SW_FWT_MIN_US * (1 << bSfgi));

        /* Perform SFGT Wait */
        if (dwSfgt > 0xFFFF)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Wait(
                pDataParams->pHalDataParams,
                PHHAL_HW_TIME_MILLISECONDS,
                (uint16_t)(dwSfgt / 1000)));
        }
        else
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Wait(
                pDataParams->pHalDataParams,
                PHHAL_HW_TIME_MICROSECONDS,
                (uint16_t)dwSfgt));
        }

        /* Calculate FWT timeout */
        dwFwt = (uint32_t)(PHPAL_I14443P4A_SW_FWT_MIN_US * (1 << pDataParams->bFwi));

        /* Add extension time */
        dwFwt = dwFwt + PHPAL_I14443P4A_SW_EXT_TIME_US;

        /* Set FWT timeout */
        if (dwFwt > 0xFFFF)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
                pDataParams->pHalDataParams,
                PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS,
                (uint16_t)(dwFwt / 1000)));
        }
        else
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
                pDataParams->pHalDataParams,
                PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,
                (uint16_t)dwFwt));
        }
    }
    /* Perform protocol error handling */
    else
    {
        if (!I14443P4A_SW_IS_INVALID_BLOCK_STATUS(status))
        {
            return status;
        }

        /* Wait FWTmin after RATS */
        if ((status & PH_ERR_MASK) != PH_ERR_IO_TIMEOUT)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Wait(
                pDataParams->pHalDataParams,
                PHHAL_HW_TIME_MICROSECONDS,
                PHPAL_I14443P4A_SW_FWT_MIN_US + PHPAL_I14443P4A_SW_EXT_TIME_US));
        }

        /* Send S(DESELECT) command */
        cmd[0] = PHPAL_I14443P4A_SW_S_BLOCK | PHPAL_I14443P4A_SW_S_BLOCK_RFU_BITS | PHPAL_I14443P4A_SW_PCB_CID_FOLLOWING | PHPAL_I14443P4A_SW_PCB_DESELECT;
        cmd[1] = bCid;
        statusTmp = phhalHw_Exchange(
            pDataParams->pHalDataParams,
            PH_EXCHANGE_DEFAULT,
            cmd,
            2,
            &pResp,
            &wRespLength);

        /* S(DESELECT) failure */
        if (((statusTmp & PH_ERR_MASK) != PH_ERR_SUCCESS) || (wRespLength != 2) || (pResp[0] != cmd[0]) || (pResp[1] != cmd[1]))
        {
            /* Set HLTA timeout */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(
                pDataParams->pHalDataParams,
                PHHAL_HW_CONFIG_TIMEOUT_VALUE_US,
                PHPAL_I14443P4A_SW_HALT_TIME_US));

            /* Send HLTA */
            cmd[0] = PHPAL_I14443P4A_SW_HALT_CMD;
            cmd[1] = 0x00;
            statusTmp = phhalHw_Exchange(
                pDataParams->pHalDataParams,
                PH_EXCHANGE_DEFAULT,
                cmd,
                2,
                &pResp,
                &wRespLength);
        }
    }

    return PH_ADD_COMPCODE(status, PH_COMP_PAL_ISO14443P4A);
}

phStatus_t phpalI14443p4a_Sw_Pps(
                                 phpalI14443p4a_Sw_DataParams_t * pDataParams,
                                 uint8_t bDri,
                                 uint8_t bDsi
                                 )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM cmd[3];
    uint8_t *   PH_MEMLOC_REM pResp;
    uint16_t    PH_MEMLOC_REM wRespLength;
    uint16_t    PH_MEMLOC_REM wTxDataRate;
    uint16_t    PH_MEMLOC_REM wRxDataRate;

    /* Check and convert Dri value */
    switch (bDri)
    {
    case PHPAL_I14443P4A_DATARATE_106:
        wTxDataRate = PHHAL_HW_RF_DATARATE_106;
        break;
    case PHPAL_I14443P4A_DATARATE_212:
        wTxDataRate = PHHAL_HW_RF_DATARATE_212;
        break;
    case PHPAL_I14443P4A_DATARATE_424:
        wTxDataRate = PHHAL_HW_RF_DATARATE_424;
        break;
    case PHPAL_I14443P4A_DATARATE_848:
        wTxDataRate = PHHAL_HW_RF_DATARATE_848;
        break;
    default:
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_ISO14443P4A);
    }

    /* Check and convert Dsi value */
    switch (bDsi)
    {
    case PHPAL_I14443P4A_DATARATE_106:
        wRxDataRate = PHHAL_HW_RF_DATARATE_106;
        break;
    case PHPAL_I14443P4A_DATARATE_212:
        wRxDataRate = PHHAL_HW_RF_DATARATE_212;
        break;
    case PHPAL_I14443P4A_DATARATE_424:
        wRxDataRate = PHHAL_HW_RF_DATARATE_424;
        break;
    case PHPAL_I14443P4A_DATARATE_848:
        wRxDataRate = PHHAL_HW_RF_DATARATE_848;
        break;
    default:
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_ISO14443P4A);
    }

    /* Send Pps command */
    cmd[0] = PHPAL_I14443P4A_SW_PPSS | pDataParams->bCid;
    cmd[1] = PHPAL_I14443P4A_SW_PPS0;
    cmd[2] = ((bDsi << 2) & 0x0C) | (bDri & 0x03);
    status = phhalHw_Exchange(
        pDataParams->pHalDataParams,
        PH_EXCHANGE_DEFAULT,
        cmd,
        3,
        &pResp,
        &wRespLength);

    /* NAK means protocol error */
    if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS_INCOMPLETE_BYTE)
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_ISO14443P4A);
    }

    /* Success check */
    PH_CHECK_SUCCESS(status);

    /* Check length and start byte of PPS */
    if ((wRespLength != 1) || (pResp[0] != (PHPAL_I14443P4A_SW_PPSS | pDataParams->bCid)))
    {
        return PH_ADD_COMPCODE(PH_ERR_PROTOCOL_ERROR, PH_COMP_PAL_ISO14443P4A);
    }

    /* Store data rates */
    pDataParams->bDri = bDri;
    pDataParams->bDsi = bDsi;

    /* Apply new data rates to Pcd */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_TXDATARATE, wTxDataRate));
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_SetConfig(pDataParams->pHalDataParams, PHHAL_HW_CONFIG_RXDATARATE, wRxDataRate));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_ISO14443P4A);
}

phStatus_t phpalI14443p4a_Sw_ActivateCard(
    phpalI14443p4a_Sw_DataParams_t * pDataParams,
    uint8_t bFsdi,
    uint8_t bCid,
    uint8_t bDri,
    uint8_t bDsi,
    uint8_t * pAts
    )
{
    phStatus_t PH_MEMLOC_REM statusTmp;

    /* Check Dri value */
    switch (bDri)
    {
    case PHPAL_I14443P4A_DATARATE_106:
    case PHPAL_I14443P4A_DATARATE_212:
    case PHPAL_I14443P4A_DATARATE_424:
    case PHPAL_I14443P4A_DATARATE_848:
        break;
    default:
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_ISO14443P4A);
    }

    /* Check Dri value */
    switch (bDsi)
    {
    case PHPAL_I14443P4A_DATARATE_106:
    case PHPAL_I14443P4A_DATARATE_212:
    case PHPAL_I14443P4A_DATARATE_424:
    case PHPAL_I14443P4A_DATARATE_848:
        break;
    default:
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_PAL_ISO14443P4A);
    }

    /* Perform RATS */
    PH_CHECK_SUCCESS_FCT(statusTmp, phpalI14443p4a_Sw_Rats(pDataParams, bFsdi, bCid, pAts));

    /* Perform PPS */
    if ((bDri != PHPAL_I14443P4A_DATARATE_106) || (bDsi != PHPAL_I14443P4A_DATARATE_106))
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phpalI14443p4a_Sw_Pps(pDataParams, bDri, bDsi));
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_ISO14443P4A);
}

phStatus_t phpalI14443p4a_Sw_GetProtocolParams(
    phpalI14443p4a_Sw_DataParams_t * pDataParams,
    uint8_t * pCidEnabled,
    uint8_t * pCid,
    uint8_t * pNadSupported,
    uint8_t * pFwi,
    uint8_t * pFsdi,
    uint8_t * pFsci
    )
{
    *pCidEnabled    = pDataParams->bCidSupported;
    *pCid           = pDataParams->bCid;
    *pNadSupported  = pDataParams->bNadSupported;
    *pFwi           = pDataParams->bFwi;
    *pFsdi          = pDataParams->bFsdi;
    *pFsci          = pDataParams->bFsci;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_PAL_ISO14443P4A);
}

#endif /* NXPBUILD__PHPAL_I14443P4A_SW */
