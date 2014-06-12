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
* Internal definitions for Keystore-Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:27:56 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHKEYSTORE_SW_INT_H
#define PHKEYSTORE_SW_INT_H

#include <ph_Status.h>

/** \addtogroup ph_Private
*  @{
*/

/**
* \brief Get the pointer to a KeyValue Pair given a Key number and a Key position.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phKeyStore_Sw_GetKeyValuePtrPos(
                                    phKeyStore_Sw_DataParams_t * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                                    uint16_t wKeyNumber,                         /**< [In] desired key number.*/
                                    uint16_t wPos,                               /**< [In] desired key position.*/
                                    phKeyStore_Sw_KeyVersionPair_t ** pKeyVersion /**< [Out] Pointer to the KeyVerison Pair.*/
                                   );

/**
* \brief Get the pointer to a KeyValue Pair given a Key number and a KeyVersion.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phKeyStore_Sw_GetKeyValuePtrVersion(
                                    phKeyStore_Sw_DataParams_t * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                                    uint16_t wKeyNumber,                         /**< [In] desired key number.*/
                                    uint16_t wKeyVersion,                        /**< [In] desired key version.*/
                                    phKeyStore_Sw_KeyVersionPair_t ** pKeyVersion /**< [Out] Pointer to the KeyVerison Pair.*/
                                   );

/**
* \brief Check value of a counter and increment it accordingly.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phKeyStore_Sw_CheckUpdateKUC(
                                    phKeyStore_Sw_DataParams_t * pDataParams,    /**< [In] Pointer to this layer's parameter structure. */
                                    uint16_t wKeyUsageCtrNumber                  /**< [In] KUC Number.*/
                                   );

/** @}
* end of ph_Private group
*/

#endif /* PHKEYSTORE_SW_INT_H */
