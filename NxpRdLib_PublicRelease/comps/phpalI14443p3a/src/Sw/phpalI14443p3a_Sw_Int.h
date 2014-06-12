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
* Internal definitions for Software ISO14443-3A Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:27:53 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHPALI14443P3A_SW_INT_H
#define PHPALI14443P3A_SW_INT_H

#include <ph_Status.h>

/** \addtogroup ph_Private
* @{
*/

/** ReqA Command code */
#define PHPAL_I14443P3A_REQUEST_CMD         0x26U

/** WupA Command code */
#define PHPAL_I14443P3A_WAKEUP_CMD          0x52U

/** HltA Command code */
#define PHPAL_I14443P3A_HALT_CMD            0x50U

/** Cascade Tag (CT) value */
#define PHPAL_I14443P3A_CASCADE_TAG         0x88U

/** Length of AtqA */
#define PHPAL_I14443P3A_ATQA_LENGTH         2U

/** Wait time for selection command in microseconds */
#define PHPAL_I14443P3A_SELECTION_TIME_US   85U

/** Wait time for halt command in microseconds */
#define PHPAL_I14443P3A_HALT_TIME_US        1100U

/** Time extension in microseconds for all commands.  */
#define PHPAL_I14443P3A_EXT_TIME_US         60

/**
* \brief Perform a ISO14443-3A Request or Wakeup command.
*
* Request Codes:\n
* REQUEST: bReqCode = 0x52\n
* WAKEUP:  bReqCode = 0x26
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid response received.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalI14443p3a_Sw_RequestAEx(
                                        phpalI14443p3a_Sw_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
                                        uint8_t bReqCode,                               /**< [In] request code according to ISO14443-3A. */
                                        uint8_t * pAtqa                                 /**< [Out] AtqA; uint8_t[2]. */
                                        );

/** @}
* end of ph_Private
*/

#endif /* PHPALI14443P3A_SW_INT_H */
