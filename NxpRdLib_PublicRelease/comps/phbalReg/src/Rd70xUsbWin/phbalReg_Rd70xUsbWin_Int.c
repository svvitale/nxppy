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
* PEGODA USB (Windows) BAL Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:26:54 2011 $
*
* History:
*  MLb: Generated 20. August 2009
*
*/

#include <ph_Status.h>

#ifdef NXPBUILD__PHBAL_REG_RD70XUSBWIN

#include "phbalReg_Rd70xUsbWin.h"
#include "phbalReg_Rd70xUsbWin_Int.h"

#ifdef _WIN32
#define DLL_EXPORT

#include <ph_RefDefs.h>
#pragma warning(push)                   /* PRQA S 3116 */
#pragma warning(disable:4200)           /* PRQA S 3116 */
#include "external/Devioctl.h"
#include "external/Usbdi.h"
#include "external/Usbioctls.h"
#pragma warning(pop)                    /* PRQA S 3116 */
#include <conio.h>
#include <stdlib.h>
#include <assert.h>

/* {DE939260-03EE-11d4-A130-00105ACCCE85} */
DEFINE_GUID(GUID_CLASS_DEVICE_USBIO, 0xde939260, 0x3ee, 0x11d4, 0xa1, 0x30, 0x0, 0x10, 0x5a, 0xcc, 0xce, 0x85);  /* PRQA S 3408 */

phStatus_t phbalReg_Rd70xUsbWin_ScanForDevices(
    uint16_t wPortBufSize,
    uint8_t * pPortNames,
    uint16_t * pNumOfPorts
    )
{
    BOOL                                PH_MEMLOC_REM status;
    HDEVINFO                            PH_MEMLOC_REM pHwDevInfo;
    SP_DEVICE_INTERFACE_DATA            PH_MEMLOC_REM sDevIfData;
    PSP_DEVICE_INTERFACE_DETAIL_DATA_A  PH_MEMLOC_REM pDevIfDetail;
    DWORD                               PH_MEMLOC_REM dwIndex;
    DWORD                               PH_MEMLOC_REM dwLastError;
    DWORD                               PH_MEMLOC_REM dwDetailInfoLength;
    uint16_t                            PH_MEMLOC_REM wPortNamesLength = 0;
    uint8_t  *                          PH_MEMLOC_REM pPortNameCurrent;
    uint16_t                            PH_MEMLOC_REM wPortNameCurrentLength;

    /* Reset number of found ports */
    *pNumOfPorts = 0;

    /* Retrieve handle to USB device list */
    pHwDevInfo = SetupDiGetClassDevs(&GUID_CLASS_DEVICE_USBIO, NULL, NULL, DIGCF_DEVICEINTERFACE);
    if (pHwDevInfo == INVALID_HANDLE_VALUE) 
    {
        dwLastError = GetLastError();
        return phbalReg_Rd70xUsbWin_ConvertError(dwLastError);
    }

    /* Prepare interface data structure */
    sDevIfData.cbSize = sizeof(sDevIfData);

    dwIndex = 0;
    do
    {
        /* Retrieve next USB device */
        status = SetupDiEnumDeviceInterfaces(pHwDevInfo, 0, &GUID_CLASS_DEVICE_USBIO, dwIndex++, &sDevIfData);
        if ((status == TRUE) && (sDevIfData.Flags == SPINT_ACTIVE))
        {
            /* Retrieve length of detail information of device */
            status = SetupDiGetDeviceInterfaceDetailA(pHwDevInfo, &sDevIfData, NULL, 0, &dwDetailInfoLength, NULL);
            if (status == FALSE)
            {
                dwLastError = GetLastError();
                if (dwLastError != ERROR_INSUFFICIENT_BUFFER)
                {
                    return (phbalReg_Rd70xUsbWin_ConvertError(dwLastError));
                }
            }

            /* Buffer overflow check */
            if ((wPortNamesLength + dwDetailInfoLength) >= wPortBufSize)
            {
                return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_BAL);
            }

            /* Prepare current port detail structure */
            pPortNameCurrent = &pPortNames[wPortNamesLength];
            pDevIfDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA_A)pPortNameCurrent;
            pDevIfDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_A);
            wPortNameCurrentLength = (uint16_t)(dwDetailInfoLength - sizeof(pDevIfDetail->cbSize));

            /* Retrieve detail information of device */
            status = SetupDiGetDeviceInterfaceDetailA(pHwDevInfo, &sDevIfData, pDevIfDetail, dwDetailInfoLength, NULL, NULL);
            if (status == FALSE)
            {
                dwLastError = GetLastError();
                return phbalReg_Rd70xUsbWin_ConvertError(dwLastError);
            }

            /* Store the device name (path) */
            memmove(pPortNameCurrent, pDevIfDetail->DevicePath, wPortNameCurrentLength);  /* PRQA S 3200 */
            wPortNamesLength = wPortNamesLength + wPortNameCurrentLength;
            ++(*pNumOfPorts);
        }
    }
    while (status == TRUE);

    /* Terminate portlist */
    pPortNames[wPortNamesLength] = '\0';

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
}

phStatus_t phbalReg_Rd70xUsbWin_SetInterface( 
    HANDLE hDevice,
    uint8_t bInterfaceNo,
    uint8_t bAlternateSettingNo
    )
{
    BOOL        PH_MEMLOC_REM status;
    uint8_t     PH_MEMLOC_REM aConfigBuf[2];
    DWORD       PH_MEMLOC_REM dwBytesReturned;
    DWORD       PH_MEMLOC_REM dwLastError;

    /* check if device is open */
    if (hDevice == INVALID_HANDLE_VALUE)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    /* parameter check */
    if ((bInterfaceNo > 9) || (bAlternateSettingNo > 9))
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_BAL);
    }

    /* prepare set interface */
    aConfigBuf[0] = '0' + bInterfaceNo;
    aConfigBuf[1] = '0' + bAlternateSettingNo;

    /* perform IO control */
    status = DeviceIoControl(
        hDevice,
        IOCTL_USB_SET_INTERFACE,
        aConfigBuf,
        sizeof(aConfigBuf),
        aConfigBuf,
        sizeof(aConfigBuf),
        &dwBytesReturned,
        NULL
        );

    /* error check */
    if (status == FALSE)
    {
        dwLastError = GetLastError();
        return phbalReg_Rd70xUsbWin_ConvertError(dwLastError);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
}

phStatus_t phbalReg_Rd70xUsbWin_SetConfiguration( 
    HANDLE hDevice,
    uint8_t bConfigurationNo
    )
{
    BOOL    PH_MEMLOC_REM status;
    uint8_t PH_MEMLOC_REM aConfigBuf[1];
    DWORD   PH_MEMLOC_REM dwBytesReturned;
    DWORD   PH_MEMLOC_REM dwLastError;

    /* check if device is open */
    if (hDevice == INVALID_HANDLE_VALUE)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    /* parameter check */
    if (bConfigurationNo > 9)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_BAL);
    }

    /* prepare configuration */
    aConfigBuf[0] = '0' + bConfigurationNo;

    /* perform IO control */
    status = DeviceIoControl(
        hDevice,
        IOCTL_USB_SET_CONFIGURATION,
        aConfigBuf,
        sizeof(aConfigBuf),
        aConfigBuf,
        sizeof(aConfigBuf),
        &dwBytesReturned,
        NULL
        );

    /* error check */
    if (status == FALSE)
    {
        dwLastError = GetLastError();
        /* No error means generic failure */
        if (dwLastError == ERROR_SUCCESS)
        {
            status = ERROR_GEN_FAILURE;
        }
        return phbalReg_Rd70xUsbWin_ConvertError(dwLastError);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
}

phStatus_t phbalReg_Rd70xUsbWin_OpenHandle(
    char * pFilename,
    HANDLE * phDevice
    )
{
    *phDevice = CreateFileA(
        pFilename,
        GENERIC_WRITE | GENERIC_READ,
        FILE_SHARE_WRITE | FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED,
        NULL
        );

    /* error check */
    if (*phDevice == INVALID_HANDLE_VALUE)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
}

phStatus_t phbalReg_Rd70xUsbWin_CloseHandle( 
    HANDLE hDevice
    )
{ 
    BOOL    PH_MEMLOC_REM status;
    DWORD   PH_MEMLOC_REM dwLastError;

    /* check if device is open */
    if (hDevice == INVALID_HANDLE_VALUE)
    {
        return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_BAL);
    }

    /* Close the handle */
    status = CloseHandle(hDevice);
    if (status == FALSE)
    {
        dwLastError = GetLastError();
        return phbalReg_Rd70xUsbWin_ConvertError(dwLastError);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
}

phStatus_t phbalReg_Rd70xUsbWin_DoOverlappedWrite(
    HANDLE hDevice,
    uint32_t dwTimeout,
    uint8_t * pBuffer,
    uint32_t dwBytesToWrite,
    uint32_t * pBytesWritten
    )
{
    BOOL        PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    DWORD       PH_MEMLOC_REM dwLastError;
    OVERLAPPED  PH_MEMLOC_REM sOverlapped = {0};

    /* check if device is open */
    if (hDevice == INVALID_HANDLE_VALUE)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    /* initialize overlapped operation */
    sOverlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (sOverlapped.hEvent == NULL)
    {
        dwLastError = GetLastError();
        return phbalReg_Rd70xUsbWin_ConvertError(dwLastError);
    }

    /* perform write operation */
    status = WriteFile(
        hDevice, 
        pBuffer, 
        dwBytesToWrite, 
        pBytesWritten, 
        &sOverlapped
        );

    if (status == FALSE)
    {
        dwLastError = GetLastError();
        if (dwLastError == ERROR_IO_PENDING)
        {
            /* wait until write operation is finished */
            dwLastError = WaitForSingleObject(sOverlapped.hEvent, dwTimeout);
            switch (dwLastError)
            {
            case WAIT_OBJECT_0:
                /* retrieve status of operation */
                status = GetOverlappedResult(hDevice, &sOverlapped, pBytesWritten, FALSE);
                if (status == FALSE)
                {
                    dwLastError = GetLastError();
                }
                else
                {
                    dwLastError = ERROR_SUCCESS;
                }
                break;

            case WAIT_TIMEOUT:
            default:

                /* cancel IO operation manually if it's not finished */
                status = CancelIo(hDevice);
                if (status == FALSE) 
                {
                    dwLastError = GetLastError();
                }
                else
                {
                    /* Note: phbalReg_Rd70xUsbWin_AbortPipe() would fail due to page fault, so reset the pipe instead */
                    PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Rd70xUsbWin_ResetPipe(hDevice));
                }
                break;
            }
        }
    }
    else
    {
        dwLastError = ERROR_SUCCESS;
    }

    /* end overlapped operation */
    status = CloseHandle(sOverlapped.hEvent);
    if (status == FALSE)
    {
        dwLastError = GetLastError();
    }

    return phbalReg_Rd70xUsbWin_ConvertError(dwLastError);
}

phStatus_t phbalReg_Rd70xUsbWin_DoOverlappedRead(
    HANDLE hDevice,
    uint32_t dwTimeout,
    uint32_t dwBytesToRead,
    uint8_t * pBuffer,
    uint32_t * pBytesRead
    )
{
    BOOL        PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    DWORD       PH_MEMLOC_REM dwLastError;
    OVERLAPPED  PH_MEMLOC_REM sOverlapped = {0};

    /* reset number of read bytes */
    *pBytesRead = 0;

    /* check if device is open */
    if (hDevice == INVALID_HANDLE_VALUE)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    /* initialize overlapped operation */
    sOverlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (sOverlapped.hEvent == NULL)
    {
        dwLastError = GetLastError();
        return phbalReg_Rd70xUsbWin_ConvertError(dwLastError);
    }

    /* perform read operation */
    status = ReadFile(
        hDevice, 
        pBuffer, 
        dwBytesToRead, 
        pBytesRead, 
        &sOverlapped
        );

    if (status == FALSE)
    {
        dwLastError = GetLastError();
        if (dwLastError == ERROR_IO_PENDING)
        {
            /* wait until write operation is finished */
            dwLastError = WaitForSingleObject(sOverlapped.hEvent, dwTimeout);
            switch (dwLastError)
            {
            case WAIT_OBJECT_0:
                /* retrieve status of operation */
                status = GetOverlappedResult(hDevice, &sOverlapped, pBytesRead, FALSE);
                if (status == FALSE)
                {
                    dwLastError = GetLastError();
                }
                else
                {
                    dwLastError = ERROR_SUCCESS;
                }
                break;

            case WAIT_TIMEOUT:
            case WAIT_ABANDONED:
            default:

                /* cancel IO operation manually if it's not finished */
                status = CancelIo(hDevice);
                if (status == FALSE) 
                {
                    dwLastError = GetLastError();
                }
                else
                {
                    /* Note: phbalReg_Rd70xUsbWin_AbortPipe() would fail due to page fault, so reset the pipe instead */
                    PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Rd70xUsbWin_ResetPipe(hDevice));
                }
                break;
            }
        }
        else
        {
            /* cancel IO operation manually if it's not finished */
            status = CancelIo(hDevice);
            if (status == FALSE) 
            {
                dwLastError = GetLastError();
            }
        }
    }
    else
    {
        dwLastError = ERROR_SUCCESS;
    }

    /* end overlapped operation */
    status = CloseHandle(sOverlapped.hEvent);
    if (status == FALSE)
    {
        dwLastError = GetLastError();
    }

    return phbalReg_Rd70xUsbWin_ConvertError(dwLastError);
}

phStatus_t phbalReg_Rd70xUsbWin_AbortPipe(
    HANDLE hDevice
    )
{
    BOOL        PH_MEMLOC_REM status;
    DWORD       PH_MEMLOC_REM dwLastError;
    DWORD       PH_MEMLOC_REM dwBytesReturned;

    /* check if device is open */
    if (hDevice == INVALID_HANDLE_VALUE)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }

    /* perform IO control */
    status = DeviceIoControl(
        hDevice,
        IOCTL_USB_ABORT_PIPE,
        NULL,
        0,
        NULL,
        0,
        &dwBytesReturned,
        NULL
        );

    if (status == FALSE)
    {
        dwLastError = GetLastError();
        return phbalReg_Rd70xUsbWin_ConvertError(dwLastError);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
}

phStatus_t phbalReg_Rd70xUsbWin_ResetPipe( 
    HANDLE hDevice 
    )
{
    BOOL        PH_MEMLOC_REM status;
    DWORD       PH_MEMLOC_REM dwLastError;
    DWORD       PH_MEMLOC_REM dwBytesReturned;

    /* check if device is open */
    if (hDevice == INVALID_HANDLE_VALUE)
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }
    
    /* perform IO control */
    status = DeviceIoControl(
        hDevice,
        IOCTL_USB_RESET_PIPE,
        NULL,
        0,
        NULL,
        0,
        &dwBytesReturned,
        NULL
        );

    if (status == FALSE)
    {
        dwLastError = GetLastError();
        return phbalReg_Rd70xUsbWin_ConvertError(dwLastError);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
}

phStatus_t phbalReg_Rd70xUsbWin_ConvertError(
    DWORD dwError
    )
{
    switch (dwError)
    {
    case ERROR_SUCCESS:
        return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
    case ERROR_INSUFFICIENT_BUFFER:
    case PHBAL_REG_RD70XUBSWIN_ERR_OUT_OF_MEMORY:
    case ERROR_GEN_FAILURE:
        return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_BAL);
    default:
        return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
    }
}

#endif

#endif /* NXPBUILD__PHBAL_REG_RD70XUSBWIN */
