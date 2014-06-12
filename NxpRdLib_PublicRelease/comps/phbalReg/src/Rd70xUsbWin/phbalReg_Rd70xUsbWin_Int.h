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
* Internal definitions for Rd70x USB (Windows) BAL Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.4 $
* $Date: Fri Apr 15 09:26:54 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHBALREG_RD70XUSBWIN_INT_H
#define PHBALREG_RD70XUSBWIN_INT_H

#include <ph_Status.h>
#include "phbalReg_Rd70xUsbWin.h"

/** \addtogroup ph_Private
* @{
*/

#ifdef _WIN32

#pragma warning(push)                   /* PRQA S 3116 */
#pragma warning(disable:4001)           /* PRQA S 3116 */
#pragma warning(disable:4201)           /* PRQA S 3116 */
#pragma warning(disable:4200)           /* PRQA S 3116 */
#include <windows.h>
#include <initguid.h>
#include <setupapi.h>
#include <basetyps.h>
#pragma warning(pop)                    /* PRQA S 3116 */
#pragma comment (lib, "Setupapi.lib")   /* PRQA S 3116 */

#define PHBAL_REG_RD70XUBSWIN_DEFAULT_TIMEOUT_MS    0xFFFFU
#define PHBAL_REG_RD70XUBSWIN_WRITE_PIPE            "PIPE01"
#define PHBAL_REG_RD70XUBSWIN_READ_PIPE             "PIPE00"
#define PHBAL_REG_RD70XUBSWIN_PACKET_SIZE           64

#define PHBAL_REG_RD70XUBSWIN_ERR_OUT_OF_MEMORY     0x204199AA

phStatus_t phbalReg_Rd70xUsbWin_ScanForDevices(
    uint16_t wPortBufSize,
    uint8_t * pPortNames,
    uint16_t * pNumOfPorts
    );

phStatus_t phbalReg_Rd70xUsbWin_SetInterface(
    HANDLE hDevice,
    uint8_t bInterfaceNo, 
    uint8_t bAlternateSettingNo 
    );

phStatus_t phbalReg_Rd70xUsbWin_SetConfiguration(
    HANDLE hDevice,
    uint8_t bConfigurationNo 
    );

phStatus_t phbalReg_Rd70xUsbWin_OpenHandle(
    char * pFilename,
    HANDLE * phDevice
    );

phStatus_t phbalReg_Rd70xUsbWin_CloseHandle(
    HANDLE hDevice
    );

phStatus_t phbalReg_Rd70xUsbWin_DoOverlappedWrite(
    HANDLE hDevice,
    uint32_t dwTimeout,
    uint8_t * pBuffer,
    uint32_t dwBytesToWrite,
    uint32_t * pBytesWritten
    );

phStatus_t phbalReg_Rd70xUsbWin_DoOverlappedRead(
    HANDLE hDevice,
    uint32_t dwTimeout,
    uint32_t dwBytesToRead,
    uint8_t * pBuffer,
    uint32_t * pBytesRead
    );

phStatus_t phbalReg_Rd70xUsbWin_AbortPipe(
    HANDLE hDevice
    );

phStatus_t phbalReg_Rd70xUsbWin_ResetPipe(
    HANDLE hDevice 
    );

phStatus_t phbalReg_Rd70xUsbWin_ConvertError(
    DWORD dwError
    );

#endif

/** @}
* end of ph_Private group
*/

#endif /* PHBALREG_RD70XUSBWIN_INT_H */
