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
* Cid Manager Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.5 $
* $Date: Fri Apr 15 09:27:18 2011 $
*
* History:
*  CHu: Generated 27. July 2009
*
*/

#ifndef PHCIDMANAGER_H
#define PHCIDMANAGER_H

#include <ph_Status.h>
#include <phhalHw.h>

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#ifdef NXPBUILD__PH_CIDMANAGER

/** \defgroup phCidManager Cid Manager
* \brief Eases Multiple-Card-Management by providing and locking CIDs.
* @{
*/

#define PH_CIDMANAGER_LAST_CID  14      /**< The last managable CID. */

/**
* \brief Retrieve the lowest free Card Identifier.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_USE_CONDITION No free Cid available.
*/
phStatus_t phCidManager_GetFreeCid(
                                   void * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                                   uint8_t * pCid       /**< [Out] Card Identifier */
                                   );

/**
* \brief Free an occupied Cid.
*
* Note: This should be called after discarding a card.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_INVALID_PARAMETER Invalid or unoccupied Cid supplied.
*/
phStatus_t phCidManager_FreeCid(
                                void * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
                                uint8_t bCid        /**< [In] Card Identifier */
                                );

/** @} */
#endif /* NXPBUILD__PH_CIDMANAGER */

#ifdef NXPBUILD__PH_CIDMANAGER_SW

/** \defgroup phCidManager_Sw Component : Software
* \brief Software implementation.
* @{
*/

#define PH_CIDMANAGER_SW_ID     0x01U   /**< ID for Software component. */

/**
* \brief Cid Manager parameter structure
*/
typedef struct
{
    uint16_t wId;                                   /**< Layer ID for this component, NEVER MODIFY! */
    uint8_t bCidList[PH_CIDMANAGER_LAST_CID];       /**< Contains a list of Cids, where a value
                                                    of /c 0 means free and a value of /c 1 means occupied. */
} phCidManager_Sw_DataParams_t;

/**
* \brief Initialise this layer.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phCidManager_Sw_Init(
                                phCidManager_Sw_DataParams_t * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                                uint16_t wSizeOfDataParams                   /**< [In] Specifies the size of the data parameter structure. */
                                );

/** @} */
#endif /* NXPBUILD__PH_CIDMANAGER_SW */


#ifdef NXPBUILD__PH_CIDMANAGER_RD710

/** \defgroup phCidManager_Rd710 Component : Rd710
* \brief Rd710 implementation.
* @{
*/

#define PH_CIDMANAGER_RD710_ID     0x02U   /**< ID for RD710 component. */

/**
* \brief Cid Manager parameter structure
*/
typedef struct
{
    uint16_t wId;                            /**< Layer ID for this component, NEVER MODIFY! */
    phhalHw_Rd710_DataParams_t * pHalDataParams;  /**< [In] Pointer to the parameter structure of the underlying layer.*/
} phCidManager_Rd710_DataParams_t;

/**
* \brief Initialise this layer.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phCidManager_Rd710_Init(
                                    phCidManager_Rd710_DataParams_t * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                                    uint16_t wSizeOfDataParams,                     /**< [In] Specifies the size of the data parameter structure. */
                                    phhalHw_Rd710_DataParams_t * pHalDataParams     /**< pointer to the HAL parameter structure */
                                    );

/** @} */
#endif /* NXPBUILD__PH_CIDMANAGER_RD710 */

#ifdef __cplusplus
} /* Extern C */
#endif

#endif /* PHCIDMANAGER_H */
