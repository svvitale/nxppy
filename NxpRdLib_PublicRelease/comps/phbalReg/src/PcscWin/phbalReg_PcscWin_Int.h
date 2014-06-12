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
* Internal definitions for PCSC (Windows) BAL Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:26:41 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHBALREG_PCSCWIN_INT_H
#define PHBALREG_PCSCWIN_INT_H

#include <ph_Status.h>

/** \addtogroup ph_Private
* @{
*/

/* MS Windows PC/SC Subsystem */
#ifdef _WIN32
#pragma warning(push)                   /* PRQA S 3116 */
#pragma warning(disable:4201)           /* PRQA S 3116 */
#include <winscard.h>
#pragma warning(pop)                    /* PRQA S 3116 */
#pragma comment(lib, "Winscard.lib")    /* PRQA S 3116 */
#endif

/** @}
* end of ph_Private group
*/

#endif /* PHBALREG_PCSCWIN_INT_H */
