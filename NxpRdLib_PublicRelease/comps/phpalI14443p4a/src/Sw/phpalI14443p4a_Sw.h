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
* Software ISO14443-4A Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:27:32 2011 $
*
* History:
*  CHu: Generated 29. May 2009
*
*/

#ifndef PHPALI14443P4A_SW_H
#define PHPALI14443P4A_SW_H

#include <ph_Status.h>

phStatus_t phpalI14443p4a_Sw_Rats(
                                  phpalI14443p4a_Sw_DataParams_t * pDataParams,
                                  uint8_t bFsdi,
                                  uint8_t bCid,
                                  uint8_t * pAts
                                  );

phStatus_t phpalI14443p4a_Sw_Pps(
                                 phpalI14443p4a_Sw_DataParams_t * pDataParams,
                                 uint8_t bDri,
                                 uint8_t bDsi
                                 );

phStatus_t phpalI14443p4a_Sw_ActivateCard(
    phpalI14443p4a_Sw_DataParams_t * pDataParams,
    uint8_t bFsdi,
    uint8_t bCid,
    uint8_t bDri,
    uint8_t bDsi,
    uint8_t * pAts
    );

phStatus_t phpalI14443p4a_Sw_GetProtocolParams(
    phpalI14443p4a_Sw_DataParams_t * pDataParams,
    uint8_t * pCidEnabled,
    uint8_t * pCid,
    uint8_t * pNadSupported,
    uint8_t * pFwi,
    uint8_t * pFsdi,
    uint8_t * pFsci
    );

#endif /* PHPALI14443P4A_SW_H */
