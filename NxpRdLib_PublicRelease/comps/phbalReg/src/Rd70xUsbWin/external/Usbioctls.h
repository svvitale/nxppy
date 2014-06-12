/******************************************************************************
 * * * * * *  D A T A S O F T   I S D N   S Y S T E M   G M B H . * * * * * * *
 * * *  A - 3100 St. Poelten, Schillerplatz 3, Tel. +43 2742 78103 - 0  * * * *
 ******************************************************************************
 * $Header: /home/afc_impr/designsync/server1/server_vault/Projects/NxpRdLib/02_Libraries/NxpRdLib/comps/phbalReg/src/Rd70xUsbWin/external/Usbioctls.h.rca 1.2 Fri Apr 15 09:26:41 2011 santosh.d.araballi Experimental $
 * ----------------------------------------------------------------------------
 * File:        $RCSfile: Usbioctls.h.rca $
 *
 * Archive:     $Source: /home/afc_impr/designsync/server1/server_vault/Projects/NxpRdLib/02_Libraries/NxpRdLib/comps/phbalReg/src/Rd70xUsbWin/external/Usbioctls.h.rca $
 * Revision:    $Revision: 1.2 $
 * Date:        $Date: Fri Apr 15 09:26:41 2011 $
 * Author:      $Author: santosh.d.araballi $
 * ----------------------------------------------------------------------------
 * Description:
 *
 * usb ioctls codes.
 *
 * ----------------------------------------------------------------------------
 * History:
 *
 * $Log: Usbioctls.h.rca $
 * 
 *  Revision: 1.2 Tue Oct 27 12:19:26 2009 nxp13887
 *  *** empty comment string ***
 * 
 *  Revision: 1.1 Wed Oct 21 13:33:12 2009 nxp13887
 *  mvfile on Wed Oct 21 13:33:11 2009 by user nxp13887.
 *  Originated from sync://grk1l041:9520/Projects/aaru/Windows/03_Software/01_Development/02_Libraries/NxpRdLib/comps/phbalReg/src/PegodaUsbWin/ddk/phbalReg_Usbioctls.h;1.5
 * 
 *  Revision: 1.5 Tue Oct 13 11:15:50 2009 atp02165
 *  Multi pegoda support added
 * 
 *  Revision: 1.1 Thu Aug 27 09:05:05 2009 atp02165
 *  Initial Version
 * 
 *  Revision: 1.2 Mon Jan 12 13:39:08 2009 nxp13887
 *  *** empty comment string ***
 * 
 *  Revision: 1.1 Mon Mar 10 18:46:58 2003 wcr
 *  *** empty comment string ***
// 
// 4     2.05.01 10:01 Wu
 * Revision 1.2  2001/04/26 13:24:12  John
 * - added reset pipe, abort pipe as IOCTL code
 * Revision 1.1  2001/03/04 09:58:26  John
 * Initial revision
 * Revision 1.1  2001/03/04 09:48:46  John
 * Initial revision
 *
 *****************************************************************************/

#ifndef USBIOCTLS_H 
#define USBIOCTLS_H

#define FILE_DEVICE_USBIO FILE_DEVICE_UNKNOWN

#define USBIO_IOCTL_INDEX  0x0000


#define IOCTL_USB_GET_CONFIG_DESCRIPTOR     CTL_CODE(FILE_DEVICE_USBIO, \
                                                   USBIO_IOCTL_INDEX, \
                                                   METHOD_BUFFERED, \
                                                   FILE_ANY_ACCESS)

#define IOCTL_USB_RESET_DEVICE				CTL_CODE(FILE_DEVICE_USBIO,  \
                                                   USBIO_IOCTL_INDEX+1,\
                                                   METHOD_BUFFERED,  \
                                                   FILE_ANY_ACCESS)

#define IOCTL_USB_RESET_PIPE				CTL_CODE(FILE_DEVICE_USBIO,  \
                                                   USBIO_IOCTL_INDEX+2,\
                                                   METHOD_BUFFERED,  \
                                                   FILE_ANY_ACCESS)

#define IOCTL_USB_ABORT_PIPE				CTL_CODE(FILE_DEVICE_USBIO,  \
                                                   USBIO_IOCTL_INDEX+3,\
                                                   METHOD_BUFFERED,  \
                                                   FILE_ANY_ACCESS)

#define IOCTL_USB_STOP_ISO_STREAM			CTL_CODE(FILE_DEVICE_USBIO,  \
                                                   USBIO_IOCTL_INDEX+10,\
                                                   METHOD_BUFFERED,  \
                                                   FILE_ANY_ACCESS)

#define IOCTL_USB_START_ISO_STREAM			CTL_CODE(FILE_DEVICE_USBIO,  \
                                                   USBIO_IOCTL_INDEX+11,\
                                                   METHOD_BUFFERED,  \
                                                   FILE_ANY_ACCESS)

#define IOCTL_USB_GET_DEVICE_DESCRIPTOR     CTL_CODE(FILE_DEVICE_USBIO, \
                                                   USBIO_IOCTL_INDEX+12, \
                                                   METHOD_BUFFERED, \
                                                   FILE_ANY_ACCESS)

#define IOCTL_USB_SET_CONFIGURATION		    CTL_CODE(FILE_DEVICE_USBIO, \
                                                   USBIO_IOCTL_INDEX+13, \
                                                   METHOD_BUFFERED, \
                                                   FILE_ANY_ACCESS)

#define IOCTL_USB_SET_INTERFACE			    CTL_CODE(FILE_DEVICE_USBIO, \
                                                   USBIO_IOCTL_INDEX+14, \
                                                   METHOD_BUFFERED, \
                                                   FILE_ANY_ACCESS)

#define IOCTL_USB_VENDOR_REQUEST			    CTL_CODE(FILE_DEVICE_USBIO, \
                                                   USBIO_IOCTL_INDEX+15, \
                                                   METHOD_BUFFERED, \
                                                   FILE_ANY_ACCESS)

#define IOCTL_USB_GET_INTERFACE					CTL_CODE(FILE_DEVICE_USBIO, \
                                                   USBIO_IOCTL_INDEX+16, \
                                                   METHOD_BUFFERED, \
                                                   FILE_ANY_ACCESS)


#endif /* USBIOCTLS_H */
