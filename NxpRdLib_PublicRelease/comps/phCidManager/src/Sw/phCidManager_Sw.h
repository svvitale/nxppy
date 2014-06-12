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
* Software Cid Manager Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:26:53 2011 $
*
* History:
*  CHu: Generated 27. July 2009
*
*/

#ifndef PHCIDMANAGER_SW_H
#define PHCIDMANAGER_SW_H

#include <ph_Status.h>

phStatus_t phCidManager_Sw_GetFreeCid(
                                      phCidManager_Sw_DataParams_t * pDataParams,
                                      uint8_t * pCid
                                      );

phStatus_t phCidManager_Sw_FreeCid(
                                   phCidManager_Sw_DataParams_t * pDataParams,
                                   uint8_t bCid
                                   );

#endif /* PHCIDMANAGER_SW_H */
