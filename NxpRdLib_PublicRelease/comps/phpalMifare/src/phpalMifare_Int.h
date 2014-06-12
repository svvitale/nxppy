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
* Internal definitions for Software MIFARE(R) Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:26:53 2011 $
*
* History:
*  CHu: Generated 31. July 2009
*
*/

#ifndef PHPALMIFARE_INT_H
#define PHPALMIFARE_INT_H

#include <ph_Status.h>

/** \addtogroup ph_Private
* @{
*/

#define PHPAL_MIFARE_RESP_ACK    0x0A    /**< MIFARE ACK response code */
#define PHPAL_MIFARE_RESP_NAK0   0x00    /**< MIFARE NAK0 response code */
#define PHPAL_MIFARE_RESP_NAK1   0x01    /**< MIFARE NAK1 response code */
#define PHPAL_MIFARE_RESP_NAK4   0x04    /**< MIFARE NAK2 response code */
#define PHPAL_MIFARE_RESP_NAK5   0x05    /**< MIFARE NAK3 response code */

/** @}
* end of ph_Private
*/

#endif /* PHPALMIFARE_INT_H */
