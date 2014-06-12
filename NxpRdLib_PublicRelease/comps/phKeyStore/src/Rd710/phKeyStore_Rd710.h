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
* RD710 functions of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:27:53 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHKEYSTORE_RD710_H
#define PHKEYSTORE_RD710_H

#include <ph_Status.h>
#include <phhalHw.h>
#include <phKeyStore.h>

phStatus_t phKeyStore_Rd710_FormatKeyEntry(
                                phKeyStore_Rd710_DataParams_t * pDataParams,
                                uint16_t wKeyNo,
                                uint16_t wNewKeyType
                                );

phStatus_t phKeyStore_Rd710_SetKey(
                                   phKeyStore_Rd710_DataParams_t * pDataParams,
                                   uint16_t wKeyNo,
                                   uint16_t wKeyVersion,
                                   uint16_t wKeyType,
                                   uint8_t * pNewKey,
                                   uint16_t wNewKeyVersion
                                   );

phStatus_t phKeyStore_Rd710_SetKeyAtPos(
                                phKeyStore_Rd710_DataParams_t * pDataParams,
                                uint16_t wKeyNo,
                                uint16_t wPos,
                                uint16_t wKeyType,
                                uint8_t * pNewKey,
                                uint16_t wNewKeyVersion
                                );       

phStatus_t phKeyStore_Rd710_SetKUC(
                                phKeyStore_Rd710_DataParams_t * pDataParams,
                                uint16_t wKeyNo,
                                uint16_t wRefNoKUC
                                );

phStatus_t phKeyStore_Rd710_SetFullKeyEntry(
                                phKeyStore_Rd710_DataParams_t * pDataParams,
                                uint16_t wNoOfKeys,
                                uint16_t wKeyNo,
                                uint16_t wNewRefNoKUC,
                                uint16_t wNewKeyType,
                                uint8_t * pNewKeys,
                                uint16_t * pNewKeyVersionList
                                );

phStatus_t phKeyStore_Rd710_GetKeyEntry(
                                phKeyStore_Rd710_DataParams_t * pDataParams,    
                                uint16_t wKeyNo,
                                uint16_t wKeyVersionBufSize,
                                uint16_t * wKeyVersion,
                                uint16_t * wKeyVersionLength,
                                uint16_t * pKeyType
                                );

phStatus_t phKeyStore_Rd710_GetKey(
                                 phKeyStore_Rd710_DataParams_t * pDataParams,    
                                 uint16_t wKeyNo,
                                 uint16_t wKeyVersion,
                                 uint8_t bKeyBufSize,
                                 uint8_t * pKey,
                                 uint16_t * pKeyType
                                 );


phStatus_t phKeyStore_Rd710_SetConfig(
                                phKeyStore_Rd710_DataParams_t * pDataParams,
                                uint16_t wConfig,
                                uint16_t wValue
                                );


phStatus_t phKeyStore_Rd710_GetConfig(
                                phKeyStore_Rd710_DataParams_t * pDataParams,
                                uint16_t wConfig,
                                uint16_t * pValue
                                );

phStatus_t phKeyStore_Rd710_ChangeKUC(
                                phKeyStore_Rd710_DataParams_t * pDataParams,
                                uint16_t wRefNoKUC,
                                uint32_t dwLimit
                                );

phStatus_t phKeyStore_Rd710_GetKUC(
                                phKeyStore_Rd710_DataParams_t * pDataParams,
                                uint16_t wRefNoKUC,
                                uint32_t * pdwLimit,
                                uint32_t * pdwCurVal
                                );

phStatus_t phKeyStore_Rd710_SetConfigStr(
                                phKeyStore_Rd710_DataParams_t * pDataParams,
                                uint16_t wConfig,
                                uint8_t *pBuffer,
                                uint16_t wBufferLength
                                );

phStatus_t phKeyStore_Rd710_GetConfigStr(
                                phKeyStore_Rd710_DataParams_t * pDataParams,
                                uint16_t wConfig,
                                uint8_t ** ppBuffer,
                                uint16_t * pBufferLength
                                );

#endif /* PHKEYSTORE_RD710_H */
