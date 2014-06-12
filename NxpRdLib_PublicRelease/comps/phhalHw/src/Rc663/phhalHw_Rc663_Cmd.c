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
* Command functions for Rc663 specific HAL-Component of Reader Library Framework.
* $Author: jayaprakash.desai $
* $Revision: 1.9 $
* $Date: Wed Apr 27 13:41:45 2011 $
*
* History:
*  CHu: Generated 19. March 2010
*
*/
#include <phhalHw.h>
#include <phbalReg.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHHAL_HW_RC663

#include "phhalHw_Rc663.h"
#include "phhalHw_Rc663_Int.h"
#include "phhalHw_Rc663_Config.h"
#include <phhalHw_Rc663_Reg.h>
#include <phhalHw_Rc663_Cmd.h>

phStatus_t phhalHw_Rc663_Cmd_Lpcd(
                                  phhalHw_Rc663_DataParams_t * pDataParams,
                                  uint8_t bMode,
                                  uint8_t bI,
                                  uint8_t bQ,
                                  uint16_t wPowerDownTimeMs,
                                  uint16_t wDetectionTimeUs
                                  )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM aCmd;
    uint16_t    PH_MEMLOC_REM wOption;
    uint8_t     PH_MEMLOC_REM bIrq0WaitFor;
    uint8_t     PH_MEMLOC_REM bIrq1WaitFor;
    float32_t   PH_MEMLOC_REM fReload;
    uint16_t    PH_MEMLOC_REM wReload;
    uint8_t     PH_MEMLOC_REM bRegister;
    uint8_t     PH_MEMLOC_REM bRxAnaBackup;
    uint8_t     PH_MEMLOC_REM bQMin;
    uint8_t     PH_MEMLOC_REM bQMax;
    uint8_t     PH_MEMLOC_REM bIMin;
    uint8_t     PH_MEMLOC_REM bIMax;

    /* Prepare command and option */
    aCmd = PHHAL_HW_RC663_CMD_LPCD;
    wOption = PH_EXCHANGE_DEFAULT;

    /* Prepare wait IRQs */
    bIrq0WaitFor = 0x00;
    bIrq1WaitFor = PHHAL_HW_RC663_BIT_LPCDIRQ;

    /* Check I/Q values */
    if (!(bMode & PHHAL_HW_RC663_CMD_LPCD_MODE_OPTION_IGNORE_IQ))
    {
        if ((bI == 0x00) || (bI >= 0x3F) || (bQ == 0x00) || (bQ >= 0x3F))
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }
    }

    /* Parameter check */
    switch (bMode & (uint8_t)~(uint8_t)PHHAL_HW_RC663_CMD_LPCD_MODE_OPTION_MASK)
    {
    case PHHAL_HW_RC663_CMD_LPCD_MODE_DEFAULT:

        /* start and wait for timer */
        wOption |= PHHAL_HW_RC663_OPTION_RXTX_TIMER_START;
        bIrq1WaitFor |= PHHAL_HW_RC663_BIT_TIMER1IRQ;

        /* Write default. T3 reload value */
        wReload = PHHAL_HW_RC663_LPCD_T3_RELOAD_MIN;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T3RELOADHI, (uint8_t)(wReload >> 8)));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T3RELOADLO, (uint8_t)(wReload)));

        /* Write min. T4 reload value */
        wReload = PHHAL_HW_RC663_LPCD_T4_RELOAD_MIN;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T4RELOADHI, (uint8_t)(wReload >> 8)));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T4RELOADLO, (uint8_t)(wReload)));

        /* Configure T4 for AutoLPCD & AutoRestart */
        bRegister = PHHAL_HW_RC663_BIT_T4AUTOLPCD | PHHAL_HW_RC663_BIT_T4AUTORESTARTED;
        /* Use 64Khz LFO */
        bRegister |= PHHAL_HW_RC663_VALUE_TCLK_LFO_64_KHZ;
        /* Start T4 */
        bRegister |= PHHAL_HW_RC663_BIT_T4STARTSTOPNOW | PHHAL_HW_RC663_BIT_T4RUNNING;
        /* Set AutoTrimm bit if requested */
        if (bMode & PHHAL_HW_RC663_CMD_LPCD_MODE_OPTION_TRIMM_LPO)
        {
            bRegister |= PHHAL_HW_RC663_BIT_T4AUTOTRIMM;
        }

        /* Write T4Control register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T4CONTROL, bRegister));

        break;

    case PHHAL_HW_RC663_CMD_LPCD_MODE_POWERDOWN_GUARDED:

        /* start and wait for timer */
        wOption |= PHHAL_HW_RC663_OPTION_RXTX_TIMER_START;
        bIrq1WaitFor |= PHHAL_HW_RC663_BIT_TIMER1IRQ;

    case PHHAL_HW_RC663_CMD_LPCD_MODE_POWERDOWN:

        /* Set standby bit */
        aCmd |= PHHAL_HW_RC663_BIT_STANDBY;

        /* Calculate timer 3 reload value */
        fReload = (float32_t)wDetectionTimeUs * PHHAL_HW_RC663_TIMER0_FREQ;
        if (fReload > (float32_t)PHHAL_HW_RC663_TIMER_RELOAD_MAX)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        /* Since timer IRQ is raised at underflow, wReload has to decremented by one.
        However, if the resulting reload value has commas, it must be 'ceiled' */
        wReload = (uint16_t)fReload;
        if (!(fReload > (float32_t)wReload))
        {
            --wReload;
        }

        /* Write T3 reload value */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T3RELOADHI, (uint8_t)(wReload >> 8)));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T3RELOADLO, (uint8_t)(wReload)));

        /* Calculate timer 4 reload value */
        fReload = (float32_t)(wPowerDownTimeMs * 2);
        if (fReload > (float32_t)PHHAL_HW_RC663_TIMER_RELOAD_MAX)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        /* Since timer IRQ is raised at underflow, wReload has to decremented by one.
        However, if the resulting reload value has commas, it must be 'ceiled' */
        wReload = (uint16_t)fReload;
        if (!(fReload > (float32_t)wReload))
        {
            --wReload;
        }

        /* Write T4 reload value */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T4RELOADHI, (uint8_t)(wReload >> 8)));
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T4RELOADLO, (uint8_t)(wReload)));

        /* Configure T4 for AutoLPCD and AutoRestart / Autowakeup */
        bRegister = PHHAL_HW_RC663_BIT_T4AUTOLPCD | PHHAL_HW_RC663_BIT_T4AUTORESTARTED | PHHAL_HW_RC663_BIT_T4AUTOWAKEUP;
        /* Use 2Khz LFO */
        bRegister |= PHHAL_HW_RC663_VALUE_TCLK_LFO_2_KHZ;
        /* Start T4 */
        bRegister |= PHHAL_HW_RC663_BIT_T4STARTSTOPNOW | PHHAL_HW_RC663_BIT_T4RUNNING;
        /* Set AutoTrimm bit if requested */
        if (bMode & PHHAL_HW_RC663_CMD_LPCD_MODE_OPTION_TRIMM_LPO)
        {
            bRegister |= PHHAL_HW_RC663_BIT_T4AUTOTRIMM;
        }

        /* Write T4Control register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T4CONTROL, bRegister));

        break;

    default:
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Clear LPCD result */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_LPCD_RESULT_Q, PHHAL_HW_RC663_BIT_LPCDIRQ_CLR));

    /* Set I & Q values */
    if (!(bMode & PHHAL_HW_RC663_CMD_LPCD_MODE_OPTION_IGNORE_IQ))
    {
        /* Calculate I/Q min/max. values */
        bQMin = bQ - 1;
        bQMax = bQ + 1;
        bIMin = bI - 1;
        bIMax = bI + 1;

        /* Set Qmin register */
        bRegister = bQMin | (uint8_t)((bIMax & 0x30) << 2);
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_LPCD_QMIN, bRegister));

        /* Set Qmax register */
        bRegister = bQMax | (uint8_t)((bIMax & 0x0C) << 4);
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_LPCD_QMAX, bRegister));

        /* Set Imin register */
        bRegister = bIMin | (uint8_t)((bIMax & 0x03) << 6);
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_LPCD_IMIN, bRegister));
    }

    /* Set Mix2Adc bit */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_RCV, &bRegister));
    bRegister |= PHHAL_HW_RC663_BIT_RX_SHORT_MIX2ADC;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_RCV, bRegister));

    /* Backup current RxAna setting */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_RXANA, &bRxAnaBackup));
    /* Raise receiver gain to maximum */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_RXANA, 0x03));

    /* Wait until T4 is started*/
    do
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_T4CONTROL, &bRegister));
    }
    while(!(bRegister & PHHAL_HW_RC663_BIT_T4RUNNING));

    /* Perform command */
    status = phhalHw_Rc663_Command_Int(
        pDataParams,
        aCmd,
        wOption,
        bIrq0WaitFor,
        bIrq1WaitFor,
        NULL,
        0,
        0,
        NULL,
        NULL);

    /* Restore RxAna register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_RXANA, bRxAnaBackup));

    /* Clear Mix2Adc bit */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_RCV, &bRegister));
    bRegister &= (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_RX_SHORT_MIX2ADC;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_RCV, bRegister));

    /* Stop Timer4 if started */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_T4CONTROL, &bRegister));
    bRegister |= PHHAL_HW_RC663_BIT_T4STARTSTOPNOW;
    bRegister &= (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_T4RUNNING;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T4CONTROL, bRegister));

    /* Command error check (ignore timeout since interface could have been too slow) */
    if ((status & PH_ERR_MASK) != PH_ERR_IO_TIMEOUT)
    {
        PH_CHECK_SUCCESS(status);
    }

    /* Check if LPCD-IRQ is set */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_IRQ1, &bRegister));
    if (!(bRegister & PHHAL_HW_RC663_BIT_LPCDIRQ))
    {
        return PH_ADD_COMPCODE(PH_ERR_IO_TIMEOUT, PH_COMP_HAL);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_Cmd_LpcdConfig(
                                        phhalHw_Rc663_DataParams_t * pDataParams,
                                        uint8_t * pI,
                                        uint8_t * pQ
                                        )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bMode;
    uint16_t    PH_MEMLOC_REM wTimeoutPrev;
    uint8_t     PH_MEMLOC_REM bTimeoutPrevInMs;

    /* Set Qmin register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_LPCD_QMIN, 0xC0));

    /* Set Qmax register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_LPCD_QMAX, 0xFF));

    /* Set Imin register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_LPCD_IMIN, 0xC0));

    /* Use default mode, trimm lpo and permit the function to set I and Q values */
    bMode = PHHAL_HW_RC663_CMD_LPCD_MODE_DEFAULT | PHHAL_HW_RC663_CMD_LPCD_MODE_OPTION_TRIMM_LPO | PHHAL_HW_RC663_CMD_LPCD_MODE_OPTION_IGNORE_IQ;

    /* Retrieve current timeout */
    status = phhalHw_Rc663_GetConfig(pDataParams, PHHAL_HW_CONFIG_TIMEOUT_VALUE_US, &wTimeoutPrev);
    bTimeoutPrevInMs = 0;

    /* Timeout is out of range, retrieve it in milliseconds */
    if ((status & PH_ERR_MASK) == PH_ERR_PARAMETER_OVERFLOW)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_GetConfig(pDataParams, PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS, &wTimeoutPrev));
        bTimeoutPrevInMs = 1;
    }
    else
    {
        PH_CHECK_SUCCESS(status);
    }

    /* Set configuration timeout */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetConfig(pDataParams, PHHAL_HW_CONFIG_TIMEOUT_VALUE_US, 150));

    /* Execute trimming procedure */
    status = phhalHw_Rc663_Cmd_Lpcd(
        pDataParams,
        bMode,
        0x00,
        0x00,
        0x00,
        0x00);

    /* Restore previous timeout */
    if (bTimeoutPrevInMs == 0)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetConfig(pDataParams, PHHAL_HW_CONFIG_TIMEOUT_VALUE_US, wTimeoutPrev));
    }
    else
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetConfig(pDataParams, PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS, wTimeoutPrev));
    }

    /* Ignore timeout error */
    if ((status & PH_ERR_MASK) != PH_ERR_IO_TIMEOUT)
    {
        PH_CHECK_SUCCESS(status);
    }

    /* Retrieve I and Q results */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_LPCD_RESULT_I, pI));
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_LPCD_RESULT_Q, pQ));

    /* Mask out irrelevant bits */
    *pI &= 0x3F;
    *pQ &= 0x3F;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_Cmd_LoadKey(
                                     phhalHw_Rc663_DataParams_t * pDataParams,
                                     uint8_t * pKey
                                     )
{
    uint8_t PH_MEMLOC_REM bIrq0WaitFor;
    uint8_t PH_MEMLOC_REM bIrq1WaitFor;

    /* Set wait IRQs */
    bIrq0WaitFor = 0x00;
    bIrq1WaitFor = 0x00;

    /* Perform command */
    return phhalHw_Rc663_Command_Int(
        pDataParams,
        PHHAL_HW_RC663_CMD_LOADKEY,
        PH_EXCHANGE_DEFAULT,
        bIrq0WaitFor,
        bIrq1WaitFor,
        pKey,
        PHHAL_HW_RC663_MFC_KEY_LENGTH,
        0,
        NULL,
        NULL);
}

phStatus_t phhalHw_Rc663_Cmd_Receive(
                                     phhalHw_Rc663_DataParams_t * pDataParams,
                                     uint16_t wOption,
                                     uint8_t ** ppRxBuffer,
                                     uint16_t * pRxLength
                                     )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t    PH_MEMLOC_REM wFifoBytes;
    uint8_t     PH_MEMLOC_REM bIrq0WaitFor;
    uint8_t     PH_MEMLOC_REM bIrq1WaitFor;
    uint8_t     PH_MEMLOC_REM bIrq0Reg = 0x00;
    uint8_t     PH_MEMLOC_REM bIrq1Reg = 0x00;
    uint8_t     PH_MEMLOC_REM bRegister;
    uint8_t     PH_MEMLOC_REM bRegRxWait;
    uint8_t     PH_MEMLOC_REM bError;
    uint32_t    PH_MEMLOC_REM dwTimingSingle;
    uint8_t *   PH_MEMLOC_REM pTmpBuffer;
    uint16_t    PH_MEMLOC_REM wTmpBufferLen;
    uint16_t    PH_MEMLOC_REM wTmpBufferSize;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phhalHw_Rc663_Cmd_Receive");
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wOption);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(ppRxBuffer);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wOption_log, &wOption);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);

    /* Check options */
    if (wOption & (uint16_t)~(uint16_t)(PHHAL_HW_RC663_OPTION_RXTX_TIMER_START))
    {
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);

        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
        return status;
    }

    /* Reduce RxWait to minimum */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_RXWAIT, &bRegRxWait));
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_RXWAIT, 0));

    /* set the receive length */
    if (pRxLength != NULL)
    {
        *pRxLength = 0;
    }

    /* Terminate a probably running command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_COMMAND, PHHAL_HW_RC663_CMD_IDLE));

    /* Flush FiFo */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_FlushFifo(pDataParams));

    /* clear all IRQ0 flags */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_WriteRegister(
        pDataParams,
        PHHAL_HW_RC663_REG_IRQ0,
        (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_SET));

    /* clear all IRQ1 flags */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_WriteRegister(
        pDataParams,
        PHHAL_HW_RC663_REG_IRQ1,
        (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_SET));

    /* timer should be running, otherwise we'd wait forever */
    if (!(wOption & PHHAL_HW_RC663_OPTION_RXTX_TIMER_START))
    {
        /* retrieve content of Timer Control register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_TCONTROL, &bRegister));

        /* Check T1Running flag */
        if (!(bRegister & PHHAL_HW_RC663_BIT_T1RUNNING))
        {
            status = PH_ADD_COMPCODE(PH_ERR_IO_TIMEOUT, PH_COMP_HAL);

            PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
            PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
            PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
            return status;
        }
    }

    /* start the command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_COMMAND, PHHAL_HW_RC663_CMD_RECEIVE));

    /* start timer manually if requested */
    if (wOption & PHHAL_HW_RC663_OPTION_RXTX_TIMER_START)
    {
        /* retrieve content of Timer Control register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_TCONTROL, &bRegister));
        /* manually start T0 */
        bRegister |= PHHAL_HW_RC663_BIT_T0STARTSTOPNOW | PHHAL_HW_RC663_BIT_T0RUNNING;
        /* manually start T1 */
        bRegister |= PHHAL_HW_RC663_BIT_T1STARTSTOPNOW | PHHAL_HW_RC663_BIT_T1RUNNING;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_TCONTROL, bRegister));
    }

    /* Set wait IRQs */
    bIrq0WaitFor = PHHAL_HW_RC663_BIT_RXIRQ | PHHAL_HW_RC663_BIT_HIALERTIRQ | PHHAL_HW_RC663_BIT_IDLEIRQ | PHHAL_HW_RC663_BIT_EMDIRQ;
    bIrq1WaitFor = PHHAL_HW_RC663_BIT_TIMER1IRQ;

    /* wait until the command is finished */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_WaitIrq(
        pDataParams,
        PH_ON,
        PH_OFF,
        bIrq0WaitFor,
        bIrq1WaitFor,
        &bIrq0Reg,
        &bIrq1Reg));

    /* Timeout handling */
    if ((bIrq1Reg & PHHAL_HW_RC663_BIT_TIMER1IRQ) && !(bIrq0Reg & PHHAL_HW_RC663_BIT_EMDIRQ))
    {
        /* stop the command */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_WriteRegister(
            pDataParams,
            PHHAL_HW_RC663_REG_COMMAND,
            PHHAL_HW_RC663_CMD_IDLE));

        /* Flush FiFo */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_FlushFifo(pDataParams));

        /* retrieve content of Timer Control register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_TCONTROL, &bRegister));

        /* manually stop timers */
        bRegister |= PHHAL_HW_RC663_BIT_T0STARTSTOPNOW | PHHAL_HW_RC663_BIT_T1STARTSTOPNOW;
        bRegister &= (uint8_t)~(uint8_t)(PHHAL_HW_RC663_BIT_T0RUNNING | PHHAL_HW_RC663_BIT_T1RUNNING);
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_TCONTROL, bRegister));

        /* Reset after timeout behaviour */
        if (pDataParams->bRfResetAfterTo != PH_OFF)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_FieldReset(pDataParams));
        }

        status = PH_ERR_IO_TIMEOUT;
    }
    else
    {
        status = PH_ERR_SUCCESS;
    }

    /* Reset receive buffer length */
    pDataParams->wRxBufLen = 0;

    /* Retrieve receive buffer properties */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_GetRxBuffer(pDataParams, PH_ON, &pTmpBuffer, &wTmpBufferLen, &wTmpBufferSize));

    /* Do the following if no timeout occured */
    if (status == PH_ERR_SUCCESS)
    {
        /* mask out high-alert */
        bIrq0WaitFor &= (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_HIALERTIRQ;

        /* retrieve fifo bytes */
        do
        {
            /* read interrupt status */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_IRQ0, &bIrq0Reg));
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_IRQ1, &bIrq1Reg));

            /* retrieve bytes from FiFo */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_ReadFifo(
                pDataParams,
                wTmpBufferSize,
                &pTmpBuffer[wTmpBufferLen],
                &wFifoBytes));

            /* advance receive buffer */
            wTmpBufferLen = wTmpBufferLen + wFifoBytes;
            wTmpBufferSize = wTmpBufferSize - wFifoBytes;
        }
        while ((!(bIrq0Reg & bIrq0WaitFor) && !(bIrq1Reg & bIrq1WaitFor)) || (wFifoBytes != 0));

        /* */
        /* Check if an error occured */
        /* read the error register */
        /* */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_ERROR, &bError));

        /* buffer overflow */
        if (bError & PHHAL_HW_RC663_BIT_FIFOOVL)
        {
            status = PH_ERR_BUFFER_OVERFLOW;
        }
        /* Fifo write error */
        else if (bError & PHHAL_HW_RC663_BIT_FIFOWRERR)
        {
            status = PH_ERR_READ_WRITE_ERROR;
        }
        /* framing error */
        else if (bError & PHHAL_HW_RC663_BIT_MINFRAMEERR)
        {
            status = PH_ERR_FRAMING_ERROR;
        }
        /* collision */
        else if (bError & PHHAL_HW_RC663_BIT_COLLDET)
        {
            /* No bytes received -> timeout */
            if (wTmpBufferLen == 0)
            {
                status = PH_ERR_IO_TIMEOUT;
            }
            /* Else perform collision handling */
            else
            {
                status = PH_ERR_COLLISION_ERROR;

                /* Retrieve collision position */
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_RXCOLL, &bRegister));

                /* check if collpos is valid */
                if (bRegister & PHHAL_HW_RC663_BIT_COLLPOSVALID)
                {
                    /* retrieve collpos */
                    bRegister &= PHHAL_HW_RC663_MASK_COLLPOS;
                }
                else
                {
                    /* collision position out of range --> max. */
                    bRegister = 0x3F;
                }

                /* Restore wRxBufSize */
                wTmpBufferSize = wTmpBufferSize + wTmpBufferLen;

                /* Check for buffer overflow */
                if ((uint16_t)(bRegister >> 3) > wTmpBufferSize)
                {
                    /* Return the maximum possible size of data */
                    wTmpBufferLen = wTmpBufferSize;
                    status = PH_ERR_BUFFER_OVERFLOW;
                }
                else
                {
                    /* Adjust valid byte count */
                    wTmpBufferLen = (uint16_t)(bRegister >> 3);
                }

                /* Mask out valid bits of last byte */
                bRegister &= PHHAL_HW_RC663_MASK_RXLASTBITS;

                /* Incomplete byte also counts as received byte */
                if (bRegister)
                {
                    /* Check for buffer overflow */
                    if (wTmpBufferLen == wTmpBufferSize)
                    {
                        status = PH_ERR_BUFFER_OVERFLOW;
                    }
                    else
                    {
                        ++wTmpBufferLen;
                    }
                }

                /* Store valid bits of last byte */
                pDataParams->wAdditionalInfo = bRegister;
            }
        }
        /* protocol error */
        else if (bError & PHHAL_HW_RC663_BIT_PROTERR)
        {
            status = PH_ERR_PROTOCOL_ERROR;
        }
        /* CRC / parity error */
        else if (bError & PHHAL_HW_RC663_BIT_INTEGERR)
        {
            status = PH_ERR_INTEGRITY_ERROR;
        }
        /* No error */
        else
        {
            status = PH_ERR_SUCCESS;
        }
    }

    /* Exchange was successfull */
    if (status == PH_ERR_SUCCESS)
    {
        /* Retrieve valid bits of last byte */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_RXBITCTRL, &bRegister));

        /* Mask out valid bits of last byte */
        bRegister &= PHHAL_HW_RC663_MASK_RXLASTBITS;

        /* Set RxLastBits */
        pDataParams->wAdditionalInfo = bRegister;

        /* Set incomplete byte status if applicable */
        if (bRegister != 0x00)
        {
            status = PH_ERR_SUCCESS_INCOMPLETE_BYTE;
        }
    }

    /* Stop the command / flush the FIFO on error */
    if ((status != PH_ERR_SUCCESS) &&
        (status != PH_ERR_SUCCESS_INCOMPLETE_BYTE))
    {
        /* stop the command */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_COMMAND, PHHAL_HW_RC663_CMD_IDLE));

        /* Flush FiFo */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_FlushFifo(pDataParams));
    }

    /* Store received data length in dataparams */
    pDataParams->wRxBufLen = pDataParams->wRxBufStartPos + wTmpBufferLen;

    /* Return RxBuffer pointer */
    if (ppRxBuffer != NULL)
    {
        *ppRxBuffer = pDataParams->pRxBuffer;
    }

    /* Return RxBuffer length */
    if (pRxLength != NULL)
    {
        *pRxLength = pDataParams->wRxBufLen;
    }

    /* Timing */
    if ((pDataParams->wTimingMode & (uint16_t)~(uint16_t)PHHAL_HW_TIMING_MODE_OPTION_MASK) == PHHAL_HW_TIMING_MODE_FDT)
    {
        /* Calculate FDT Value */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_GetFdt(pDataParams, status, &dwTimingSingle));

        /* FDT single -> replace the previous value */
        if (pDataParams->wTimingMode & PHHAL_HW_TIMING_MODE_OPTION_AUTOCLEAR)
        {
            pDataParams->dwTimingUs = dwTimingSingle;
        }
        /* FDT -> add current value to current count */
        else
        {
            /* Check for overflow */
            if ((0xFFFFFFFF - pDataParams->dwTimingUs) < dwTimingSingle)
            {
                pDataParams->dwTimingUs = 0xFFFFFFFF;
            }
            /* Update global timing value */
            else
            {
                pDataParams->dwTimingUs = pDataParams->dwTimingUs + dwTimingSingle;
            }
        }
    }

    /* Restore RxWait setting */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_RXWAIT, bRegRxWait));

    status = PH_ADD_COMPCODE(status, PH_COMP_HAL);

    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
#ifdef NXPBUILD__PH_LOG
    if ((((status & PH_ERR_MASK) == PH_ERR_SUCCESS) ||
        ((status & PH_ERR_MASK) == PH_ERR_SUCCESS_INCOMPLETE_BYTE)) &&
        !(wOption & PH_EXCHANGE_BUFFERED_BIT) &&
        (ppRxBuffer != NULL) &&
        (pRxLength != NULL))
    {
        PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, ppRxBuffer_log, *ppRxBuffer, *pRxLength);
    }
#endif
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
    return status;
}

phStatus_t phhalHw_Rc663_Cmd_Transmit(
                                      phhalHw_Rc663_DataParams_t * pDataParams,
                                      uint16_t wOption,
                                      uint8_t * pTxBuffer,
                                      uint16_t wTxLength
                                      )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t    PH_MEMLOC_REM wNumPrecachedBytes;
    uint16_t    PH_MEMLOC_REM wFifoBytes;
    uint8_t     PH_MEMLOC_REM bIrq0WaitFor;
    uint8_t     PH_MEMLOC_REM bIrq1WaitFor;
    uint8_t     PH_MEMLOC_REM bIrq0Reg = 0x00;
    uint8_t     PH_MEMLOC_REM bIrq1Reg = 0x00;
    uint8_t     PH_MEMLOC_REM bRegister;
    uint8_t     PH_MEMLOC_REM bError;
    uint8_t     PH_MEMLOC_REM bNoData;
    uint8_t     PH_MEMLOC_REM bRestoreTmrSet;
    uint8_t *   PH_MEMLOC_REM pTmpBuffer;
    uint16_t    PH_MEMLOC_REM wTmpBufferLen;
    uint16_t    PH_MEMLOC_REM wTmpBufferSize;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phhalHw_Rc663_Cmd_Transmit");
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wOption);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pTxBuffer);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wOption_log, &wOption);
    PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, pTxBuffer_log, pTxBuffer, wTxLength);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);

    /* Check options */
    if (wOption & (uint16_t)~(uint16_t)(PH_EXCHANGE_BUFFERED_BIT | PH_EXCHANGE_LEAVE_BUFFER_BIT | PHHAL_HW_RC663_OPTION_RXTX_TIMER_START))
    {
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);

        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
        return status;
    }

    /* Custom option: do not start timer */
    if (!(wOption & PHHAL_HW_RC663_OPTION_RXTX_TIMER_START))
    {
        /* Timer 0 */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_T0CONTROL, &bRegister));
        bRegister &= (uint8_t)~(uint8_t)PHHAL_HW_RC663_MASK_TSTART;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T0CONTROL, bRegister));
        /* Timer 1 */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_T1CONTROL, &bRegister));
        bRegister &= (uint8_t)~(uint8_t)PHHAL_HW_RC663_MASK_TSTART;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T1CONTROL, bRegister));

        bRestoreTmrSet = PH_ON;
    }
    else
    {
        /* To skip restoration sequence below */
        bRestoreTmrSet = PH_OFF;

        /* Clear custom option bit */
        wOption &= (uint16_t)~(uint16_t)PHHAL_HW_RC663_OPTION_RXTX_TIMER_START;
    }

    /* clear internal buffer if requested */
    if (!(wOption & PH_EXCHANGE_LEAVE_BUFFER_BIT))
    {
        pDataParams->wTxBufLen = 0;
    }

    /* Fill the global TxBuffer */
    /* Note: We always need to buffer for SPI, else the input buffer would get overwritten! */
    if ((wOption & PH_EXCHANGE_BUFFERED_BIT) ||
        (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_SPI) ||
        (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_I2C))
    {
        /* retrieve transmit buffer */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_GetTxBuffer(pDataParams, PH_ON, &pTmpBuffer, &wTmpBufferLen, &wTmpBufferSize));

        if (wTxLength != 0)
        {
            /* TxBuffer overflow check */
            if (wTxLength > (wTmpBufferSize - wTmpBufferLen))
            {
                pDataParams->wTxBufLen = 0;
                status = PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);

                PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
                PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
                PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
                return status;
            }

            /* copy data */
            memcpy(&pTmpBuffer[wTmpBufferLen], pTxBuffer, wTxLength);  /* PRQA S 3200 */
            pDataParams->wTxBufLen = pDataParams->wTxBufLen + wTxLength;
        }

        /* Buffer operation -> finished */
        if (wOption & PH_EXCHANGE_BUFFERED_BIT)
        {
            status = PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);

            PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
            PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
            PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
            return status;
        }
        /* Else reset the input length for SPI and continue */
        else
        {
            wTxLength = 0;
        }
    }

    /* retrieve transmit buffer */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_GetTxBuffer(pDataParams, PH_ON, &pTmpBuffer, &wTmpBufferLen, &wTmpBufferSize));

    /* Disable DataEn if no data is to be sent */
    if ((wTmpBufferLen == 0) && (wTxLength == 0))
    {
        /* Store that we sent no data */
        bNoData = PH_ON;

        /* Read out TxDataNum register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_TXDATANUM, &bRegister));

        /* Disable DataEn */
        bRegister &= (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_DATAEN;

        /* Write changed register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_TXDATANUM, bRegister));
    }
    else
    {
        /* Reset NoData flag */
        bNoData = PH_OFF;
    }

    /* Terminate a possibly running command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_COMMAND, PHHAL_HW_RC663_CMD_IDLE));

    /* Flush FiFo */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_FlushFifo(pDataParams));

    /* clear all IRQ0 flags */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_WriteRegister(
        pDataParams,
        PHHAL_HW_RC663_REG_IRQ0,
        (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_SET));

    /* clear all IRQ1 flags */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_WriteRegister(
        pDataParams,
        PHHAL_HW_RC663_REG_IRQ1,
        (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_SET));

    /* Precache buffered contents into FIFO */
    wNumPrecachedBytes = (wTmpBufferLen > pDataParams->wMaxPrecachedBytes) ? pDataParams->wMaxPrecachedBytes : wTmpBufferLen;
    if (wNumPrecachedBytes > 0)
    {
        /* Perform actual write to FIFO */
        status = phhalHw_Rc663_WriteFifo(pDataParams, pTmpBuffer, wNumPrecachedBytes, &wFifoBytes);

        /* Ignore FiFo overflow warning */
        if ((status & PH_ERR_MASK) != PH_ERR_BUFFER_OVERFLOW)
        {
            PH_CHECK_SUCCESS(status);
        }

        /* Update buffer pointer and length */
        pTmpBuffer += wFifoBytes;
        wTmpBufferLen = wTmpBufferLen - wFifoBytes;
    }
    else
    {
        status = PH_ERR_SUCCESS;
    }

    /* Precache given buffer contents into FIFO */
    if ((status & PH_ERR_MASK) != PH_ERR_BUFFER_OVERFLOW)
    {
        wNumPrecachedBytes = (wTxLength > (pDataParams->wMaxPrecachedBytes - wNumPrecachedBytes)) ? (pDataParams->wMaxPrecachedBytes - wNumPrecachedBytes) : wTxLength;

        if (wNumPrecachedBytes > 0)
        {
            /* Perform actual write to FIFO */
            status = phhalHw_Rc663_WriteFifo(pDataParams, pTxBuffer, wNumPrecachedBytes, &wFifoBytes);

            /* Ignore FiFo overflow warning */
            if ((status & PH_ERR_MASK) != PH_ERR_BUFFER_OVERFLOW)
            {
                PH_CHECK_SUCCESS(status);
            }

            /* Update buffer pointer and length */
            pTxBuffer += wFifoBytes;
            wTxLength = wTxLength - wFifoBytes;
        }
    }

    /* start the command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_COMMAND, PHHAL_HW_RC663_CMD_TRANSMIT));

    /* Write the remaining data into the Fifo */
    /* (Only possible if interface to RC is fast enough!) */
    while ((wTmpBufferLen != 0) || (wTxLength != 0))
    {
        /* Switch from prechache buffer to given buffer if it's empty */
        if (wTmpBufferLen == 0)
        {
            pTmpBuffer = pTxBuffer;
            wTmpBufferLen = wTxLength;
            wTxLength = 0;
        }
        /* */
        /* Check for FIFO underflow */
        /* */
#ifdef PHHAL_HW_RC663_FEATURE_FIFO_UNDERFLOW_CHECK
        /* read interrupt status */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_IRQ0, &bIrq0Reg));

        if ((bIrq0Reg & PHHAL_HW_RC663_BIT_IDLEIRQ) || (bIrq0Reg & PHHAL_HW_RC663_BIT_TXIRQ))
        {
            /* stop the command */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_WriteRegister(
                pDataParams,
                PHHAL_HW_RC663_REG_COMMAND,
                PHHAL_HW_RC663_CMD_IDLE));

            /* Flush FiFo */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_FlushFifo(pDataParams));

            return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_HAL);
        }
#endif
        /* write remaining data to transmit into FiFo buffer */
        status = phhalHw_Rc663_WriteFifo(pDataParams, pTmpBuffer, wTmpBufferLen, &wFifoBytes);

        /* Ignore FiFo overflow warning */
        if ((status & PH_ERR_MASK) != PH_ERR_BUFFER_OVERFLOW)
        {
            PH_CHECK_SUCCESS(status);
        }

        /* Update buffer pointer and length */
        pTmpBuffer += wFifoBytes;
        wTmpBufferLen = wTmpBufferLen - wFifoBytes;
    }

    /* Set wait IRQs */
    bIrq0WaitFor = PHHAL_HW_RC663_BIT_TXIRQ | PHHAL_HW_RC663_BIT_IDLEIRQ;
    bIrq1WaitFor = 0x00;

    /* wait until the command is finished */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_WaitIrq(
        pDataParams,
        PH_ON,
        PH_OFF,
        bIrq0WaitFor,
        bIrq1WaitFor,
        &bIrq0Reg,
        &bIrq1Reg));

    /* Check if an error occured */
    if (bIrq0Reg & PHHAL_HW_RC663_BIT_ERRIRQ)
    {
        /* read the error register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_ERROR, &bError));

        /* no data error */
        if (bError & PHHAL_HW_RC663_BIT_NODATAERR)
        {
            status = PH_ERR_INTERNAL_ERROR;
        }
        /* buffer overflow */
        else if (bError & PHHAL_HW_RC663_BIT_FIFOOVL)
        {
            status = PH_ERR_BUFFER_OVERFLOW;
        }
        /* Fifo write error */
        else if (bError & PHHAL_HW_RC663_BIT_FIFOWRERR)
        {
            status = PH_ERR_READ_WRITE_ERROR;
        }
        /* No error */
        else
        {
            status = PH_ERR_SUCCESS;
        }
    }
    /* No error */
    else
    {
        status = PH_ERR_SUCCESS;
    }

    /* Reset TxLastBits */
    if (pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXLASTBITS] != 0)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetConfig(pDataParams, PHHAL_HW_CONFIG_TXLASTBITS, 0x00));
    }

    /* Reset buffered bytes */
    pDataParams->wTxBufLen = 0;

    /* Enable DataEn again if no data has been sent */
    if (bNoData != PH_OFF)
    {
        /* Read out TxDataNum register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_TXDATANUM, &bRegister));

        /* Enable DataEn */
        bRegister |= PHHAL_HW_RC663_BIT_DATAEN;

        /* Write changed register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_TXDATANUM, bRegister));
    }

    /* Restore correct timer setting */
    if (bRestoreTmrSet)
    {
        /* Timer 0 */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_T0CONTROL, &bRegister));
        bRegister |= PHHAL_HW_RC663_BIT_TSTART_TX;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T0CONTROL, bRegister));
        /* Timer 1 */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_T1CONTROL, &bRegister));
        bRegister |= PHHAL_HW_RC663_BIT_TSTART_TX;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T1CONTROL, bRegister));
    }

    status = PH_ADD_COMPCODE(status, PH_COMP_HAL);

    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
    return status;
}

phStatus_t phhalHw_Rc663_Cmd_WriteE2(
                                     phhalHw_Rc663_DataParams_t * pDataParams,
                                     uint16_t wAddress,
                                     uint8_t bData
                                     )
{
    uint8_t PH_MEMLOC_REM aCmd[3];
    uint8_t PH_MEMLOC_REM bIrq0WaitFor;
    uint8_t PH_MEMLOC_REM bIrq1WaitFor;

    /* Check Address range */
    if (wAddress >= PHHAL_HW_RC663_EEPROM_SIZE)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Set wait IRQs */
    bIrq0WaitFor = 0x00;
    bIrq1WaitFor = 0x00;

    /* Prepare command */
    aCmd[0] = (uint8_t)(wAddress >> 8);
    aCmd[1] = (uint8_t)(wAddress);
    aCmd[2] = bData;

    /* Perform command */
    return phhalHw_Rc663_Command_Int(
        pDataParams,
        PHHAL_HW_RC663_CMD_WRITEE2,
        PH_EXCHANGE_DEFAULT,
        bIrq0WaitFor,
        bIrq1WaitFor,
        aCmd,
        3,
        0,
        NULL,
        NULL);
}

phStatus_t phhalHw_Rc663_Cmd_WriteE2Page(
    phhalHw_Rc663_DataParams_t * pDataParams,
    uint16_t wAddress,
    uint8_t * pData,
    uint8_t bDataLen
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM aCmd[2];
    uint8_t     PH_MEMLOC_REM bIrq0WaitFor;
    uint8_t     PH_MEMLOC_REM bIrq1WaitFor;
    uint16_t    PH_MEMLOC_REM wFifoBytes;

    /* Check Address range and data length */
    if ((wAddress >= PHHAL_HW_RC663_EEPROM_NUM_PAGES) || (bDataLen == 0) || (bDataLen > PHHAL_HW_RC663_EEPROM_PAGE_SIZE))
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Set wait IRQs */
    bIrq0WaitFor = 0x00;
    bIrq1WaitFor = 0x00;

    /* Flush FiFo */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_FlushFifo(pDataParams));

    /* Write Address into FIFO */
    aCmd[1] = (uint8_t)(wAddress);
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_WriteFifo(pDataParams, &aCmd[1], 1, &wFifoBytes));

    /* Perform command */
    return phhalHw_Rc663_Command_Int(
        pDataParams,
        PHHAL_HW_RC663_CMD_WRITEE2PAGE,
        PHHAL_HW_RC663_OPTION_FIFO_NOCLEAR,
        bIrq0WaitFor,
        bIrq1WaitFor,
        pData,
        (uint16_t)bDataLen,
        0,
        NULL,
        NULL);
}

phStatus_t phhalHw_Rc663_Cmd_ReadE2(
                                    phhalHw_Rc663_DataParams_t * pDataParams,
                                    uint16_t wAddress,
                                    uint16_t wNumBytes,
                                    uint8_t * pData
                                    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM aCmd[3];
    uint8_t     PH_MEMLOC_REM bIrq0WaitFor;
    uint8_t     PH_MEMLOC_REM bIrq1WaitFor;
    uint16_t    PH_MEMLOC_REM wDataLenTmp;

    /* Parameter check */
    if (wNumBytes > 0x100)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* 0 means 256, do this for the check below */
    if (wNumBytes == 0)
    {
        wNumBytes = 0x100;
    }

    /* Limit number of bytes to read to FiFo-Size */
    if (pDataParams->bFifoSize == PHHAL_HW_RC663_VALUE_FIFOSIZE_255)
    {
        if (wNumBytes > 0xFF)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }
    }

    /* Check Address range */
    if ((wAddress + wNumBytes) > PHHAL_HW_RC663_EEPROM_SIZE)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Set wait IRQs */
    bIrq0WaitFor = PHHAL_HW_RC663_BIT_HIALERTIRQ;
    bIrq1WaitFor = 0x00;

    /* Prepare command */
    aCmd[0] = (uint8_t)(wAddress >> 8);
    aCmd[1] = (uint8_t)(wAddress);
    aCmd[2] = (uint8_t)wNumBytes;

    /* Perform command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_Command_Int(
        pDataParams,
        PHHAL_HW_RC663_CMD_READE2,
        PH_EXCHANGE_DEFAULT,
        bIrq0WaitFor,
        bIrq1WaitFor,
        aCmd,
        3,
        wNumBytes,
        pData,
        &wDataLenTmp));

    /* Check received data */
    if (wDataLenTmp != wNumBytes)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_Cmd_LoadReg(
                                     phhalHw_Rc663_DataParams_t * pDataParams,
                                     uint16_t wEEAddress,
                                     uint8_t bRegAddress,
                                     uint8_t bNumBytes
                                     )
{
    uint8_t PH_MEMLOC_REM aCmd[4];
    uint8_t PH_MEMLOC_REM bIrq0WaitFor;
    uint8_t PH_MEMLOC_REM bIrq1WaitFor;

    /* Parameter check */
    if (bNumBytes == 0)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* EEPROM address check */
    if ((wEEAddress < PHHAL_HW_RC663_EEPROM_SECTION2_BEGIN) || ((wEEAddress + bNumBytes) > (PHHAL_HW_RC663_EEPROM_SECTION2_END + 1)))
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Register address check */
    if ((bRegAddress + bNumBytes) > PHHAL_HW_RC663_MAX_NUM_REGS)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Set wait IRQs */
    bIrq0WaitFor = 0x00;
    bIrq1WaitFor = 0x00;

    /* Prepare command */
    aCmd[0] = (uint8_t)(wEEAddress >> 8);
    aCmd[1] = (uint8_t)(wEEAddress);
    aCmd[2] = bRegAddress;
    aCmd[3] = bNumBytes;

    /* Perform command */
    return phhalHw_Rc663_Command_Int(
        pDataParams,
        PHHAL_HW_RC663_CMD_LOADREG,
        PH_EXCHANGE_DEFAULT,
        bIrq0WaitFor,
        bIrq1WaitFor,
        aCmd,
        4,
        0,
        NULL,
        NULL);
}

phStatus_t phhalHw_Rc663_Cmd_LoadProtocol(
    phhalHw_Rc663_DataParams_t * pDataParams,
    uint8_t bTxProtocol,
    uint8_t bRxProtocol
    )
{
    uint8_t PH_MEMLOC_REM aCmd[2];
    uint8_t PH_MEMLOC_REM bIrq0WaitFor;
    uint8_t PH_MEMLOC_REM bIrq1WaitFor;

    /* Parameter check */
    if ((bTxProtocol > PHHAL_HW_RC663_MAX_TX_SETTINGS) || (bRxProtocol > PHHAL_HW_RC663_MAX_RX_SETTINGS))
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Set wait IRQs */
    bIrq0WaitFor = 0x00;
    bIrq1WaitFor = 0x00;

    /* Prepare command */
    aCmd[0] = bRxProtocol;
    aCmd[1] = bTxProtocol;

    /* Perform command */
    return phhalHw_Rc663_Command_Int(
        pDataParams,
        PHHAL_HW_RC663_CMD_LOADPROTOCOL,
        PH_EXCHANGE_DEFAULT,
        bIrq0WaitFor,
        bIrq1WaitFor,
        aCmd,
        2,
        0,
        NULL,
        NULL);
}

phStatus_t phhalHw_Rc663_Cmd_LoadKeyE2(
                                       phhalHw_Rc663_DataParams_t * pDataParams,
                                       uint8_t  bKeyNo
                                       )
{
    uint8_t PH_MEMLOC_REM aCmd[1];
    uint8_t PH_MEMLOC_REM bIrq0WaitFor;
    uint8_t PH_MEMLOC_REM bIrq1WaitFor;

    /* Set wait IRQs */
    bIrq0WaitFor = 0x00;
    bIrq1WaitFor = 0x00;

    /* Prepare command */
    aCmd[0] = bKeyNo;

    /* Perform command */
    return phhalHw_Rc663_Command_Int(
        pDataParams,
        PHHAL_HW_RC663_CMD_LOADKEYE2,
        PH_EXCHANGE_DEFAULT,
        bIrq0WaitFor,
        bIrq1WaitFor,
        aCmd,
        1,
        0,
        NULL,
        NULL);
}

phStatus_t phhalHw_Rc663_Cmd_StoreKeyE2(
                                        phhalHw_Rc663_DataParams_t * pDataParams,
                                        uint8_t  bKeyNo,
                                        uint8_t * pKeys,
                                        uint8_t bNumberOfKeys
                                        )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM aCmd[2];
    uint8_t     PH_MEMLOC_REM bIrq0WaitFor;
    uint8_t     PH_MEMLOC_REM bIrq1WaitFor;
    uint16_t    PH_MEMLOC_REM wDataLen;
    uint16_t    PH_MEMLOC_REM wFifoBytes;

    /* Parameter check */
    if (bNumberOfKeys == 0)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Parameter check */
    if ((uint16_t)(bKeyNo + bNumberOfKeys) > PHHAL_HW_RC663_MAX_NUM_KEYS)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Calculate overal data length */
    wDataLen = (uint16_t)(bNumberOfKeys * PHHAL_HW_RC663_MFC_KEY_LENGTH);

    /* Limit number of bytes to write to FiFo-Size */
    if (pDataParams->bFifoSize == PHHAL_HW_RC663_VALUE_FIFOSIZE_255)
    {
        if (wDataLen > 0xFF)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }
    }
    else
    {
        if (wDataLen > 0x200)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }
    }

    /* Set wait IRQs */
    bIrq0WaitFor = 0x00;
    bIrq1WaitFor = 0x00;

    /* Flush FiFo */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_FlushFifo(pDataParams));

    /* Write Keynumber into FIFO */
    aCmd[1] = bKeyNo;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_WriteFifo(pDataParams, &aCmd[1], 1, &wFifoBytes));

    /* Perform command */
    return phhalHw_Rc663_Command_Int(
        pDataParams,
        PHHAL_HW_RC663_CMD_STOREKEYE2,
        PHHAL_HW_RC663_OPTION_FIFO_NOCLEAR,
        bIrq0WaitFor,
        bIrq1WaitFor,
        pKeys,
        wDataLen,
        0,
        NULL,
        NULL);
}

phStatus_t phhalHw_Rc663_Cmd_SoftReset(
                                       phhalHw_Rc663_DataParams_t * pDataParams
                                       )
{

    return phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_COMMAND, PHHAL_HW_RC663_CMD_SOFTRESET);
}

#endif /* NXPBUILD__PHHAL_HW_RC663 */
