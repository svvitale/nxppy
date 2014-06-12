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
* Internal definitions for RS232 (Windows) BAL Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:04:38 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHBALREG_SERIALWIN_INT_H
#define PHBALREG_SERIALWIN_INT_H

#include <ph_Status.h>

#ifdef _WIN32
#pragma warning(push)           /* PRQA S 3116 */
#pragma warning(disable:4001)   /* PRQA S 3116 */
#include <Windows.h>
#pragma warning(pop)            /* PRQA S 3116 */
#endif

/** \addtogroup ph_Private
* @{
*/

/** Default timeout value to guarantee no deadlocks (ReadBus & WriteBus) */
#define PHBAL_REG_SERIALWIN_RX_TIMEOUT_VAL    500

/**
* \brief Change host bit rate
*
* Changes host bit rate, stop bits and applies default settings (parity and the like).
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phbalReg_SerialWin_SetMode(
    void * phPort,          /**< [In] handle to an open communication port */
    uint32_t dwBitRate,     /**< [In] bit rate value in windows-style (like '115200', in decimal) */
    uint8_t bStopBits       /**< [In] number of stop bits */
    );

/**
* \brief Change reception timeout
*
* Applies new serial reception timeout
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phbalReg_SerialWin_SetTimeout(
    void * phPort,          /**< [In] handle to an open communication port */
    uint32_t dwTimeout      /**< [In] timeout value in windows-style (like '500', in milliseconds) */
    );

/** @}
* end of ph_Private group
*/

#endif /* PHBALREG_SERIALWIN_INT_H */
