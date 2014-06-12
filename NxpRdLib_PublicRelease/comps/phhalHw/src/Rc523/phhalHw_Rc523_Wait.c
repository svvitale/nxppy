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
* Wait Routines for RC523 specific HAL-Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.4 $
* $Date: Fri Apr 15 09:27:50 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#include <ph_Status.h>
#include <phbalReg.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHHAL_HW_RC523

#include "phhalHw_Rc523.h"
#include "phhalHw_Rc523_Int.h"
#include <phhalHw_Rc523_Reg.h>

phStatus_t phhalHw_Rc523_WaitIrq(
                                 phhalHw_Rc523_DataParams_t * pDataParams,
                                 uint8_t bIrq0WaitFor,
								 uint8_t bIrq1WaitFor,
                                 uint8_t * pIrq0Reg,
								 uint8_t * pIrq1Reg
                                 )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bIrq0EnReg;
    uint8_t     PH_MEMLOC_REM bIrq1EnReg;
	uint8_t     PH_MEMLOC_REM bRegister;
    
    /* Parameter check */
    if (!bIrq0WaitFor && !bIrq1WaitFor)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
    }

    /* Enable IRQ0 interrupt sources */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC523_REG_COMMIEN, &bIrq0EnReg));
    bIrq0EnReg &= PHHAL_HW_RC523_BIT_IRQINV;
    bIrq0EnReg |= bIrq0WaitFor;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_COMMIEN, bIrq0EnReg));
    /* Enable IRQ1 interrupt sources */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC523_REG_DIVIEN, &bIrq1EnReg));
    bIrq1EnReg &= PHHAL_HW_RC523_BIT_IRQPUSHPULL;
    bIrq1EnReg |= bIrq1WaitFor;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_DIVIEN, bIrq1EnReg));

    /* wait until an IRQ occurs */
    do
    {
        /* INSERT CODE HERE */
        
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC523_REG_STATUS1, &bRegister));
    }
    while (!(bRegister & PHHAL_HW_RC523_BIT_IRQ));

    /* Clear IRQ0 interrupt sources */
    bIrq0EnReg &= PHHAL_HW_RC523_BIT_IRQINV;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_COMMIEN, bIrq0EnReg));
    /* Clear IRQ1 interrupt sources */
    bIrq1EnReg &= PHHAL_HW_RC523_BIT_IRQPUSHPULL;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC523_REG_DIVIEN, bIrq1EnReg));

    /* Return contents of IRQ0 register */
    if (pIrq0Reg)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC523_REG_COMMIRQ, pIrq0Reg));
    }

    /* Return contents of IRQ1 register */
    if (pIrq1Reg)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC523_REG_DIVIRQ, pIrq1Reg));
    }
    
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

#endif /* NXPBUILD__PHHAL_HW_RC523 */
