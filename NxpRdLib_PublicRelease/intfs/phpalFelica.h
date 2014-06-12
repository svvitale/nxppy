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
* Generic Felica Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.1 $
* $Date: Fri Apr 15 09:29:04 2011 $
*
* History:
*  RSn: Generated 25. January 2010
*
*/

#ifndef PHPALFELICA_H
#define PHPALFELICA_H

#include <ph_Status.h>

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#ifdef NXPBUILD__PHPAL_FELICA

/** \defgroup phpalFelica Felica
* \brief These Components implement the Felica (contactless) protocol.
* @{
*/

/** \name Lengths
*/
/*@{*/
/** UID length in bytes. */
#define PHPAL_FELICA_IDM_LENGTH     8U
/** PMm length in bytes. */
#define PHPAL_FELICA_PMM_LENGTH     8U
/** Block length in bytes. */
#define PHPAL_FELICA_BLOCK_LENGTH   4U
/** Number of bytes per page. */
#define PHPAL_FELICA_PAGE_LENGTH    16U
/** Length of ATQC. */
#define PHPAL_FELICA_ATQC_LENGTH    17U
/** Maximum length of a transmission package. */
#define PHPAL_FELICA_TXLENGTH_MAX   254U
/*@}*/

/** @} */
#endif /* NXPBUILD__PHPAL_EPCUID */

#ifdef NXPBUILD__PHPAL_FELICA_SW

/** \defgroup phpalFelica_Sw Component : Software
* @{
*/

#define PHPAL_FELICA_SW_ID      0x01    /**< ID for Software Felica layer */

/**
* \brief Felica parameter structure
*/
typedef struct
{
    uint16_t  wId;                                                          /**< Layer ID for this component, NEVER MODIFY! */
    void    * pHalDataParams;                                               /**< Pointer to the parameter structure of the underlying layer. */
    uint8_t   aIDmPMm[PHPAL_FELICA_IDM_LENGTH + PHPAL_FELICA_PMM_LENGTH];   /**< The Cards Manufacture ID (IDm) and Manufacture Parameters (PMm). */
    uint8_t   bIDmPMmValid;                                                 /**< Whether the stored IDm and PMm are valid (\c 1) or not (\c 0). */
    uint8_t   bLength;                                                      /**< Current data length, used internally for Exchange function. */
} phpalFelica_Sw_DataParams_t;

/**
* \brief Initialise this layer.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
*/
phStatus_t phpalFelica_Sw_Init(
                               phpalFelica_Sw_DataParams_t * pDataParams,   /**< [In] Pointer to this layer's parameter structure. */
                               uint16_t wSizeOfDataParams,                  /**< [In] Specifies the size of the data parameter structure. */
                               void * pHalDataParams                        /**< [In] Pointer to the parameter structure of the underlying layer. */
                               );

/** @} */
#endif /* NXPBUILD__PHPAL_FELICA */

#ifdef NXPBUILD__PHPAL_FELICA
 
/** \addtogroup phpalFelica
* @{
*/

/**
* \name Definitions of the time slots for the ReqC command
*/
/*@{*/
#define PHPAL_FELICA_NUMSLOTS_1     0x00    /**< Value for \c bNumSlots = 1. */
#define PHPAL_FELICA_NUMSLOTS_2     0x01    /**< Value for \c bNumSlots = 2. */
#define PHPAL_FELICA_NUMSLOTS_4     0x03    /**< Value for \c bNumSlots = 4. */
#define PHPAL_FELICA_NUMSLOTS_8     0x07    /**< Value for \c bNumSlots = 8. */
#define PHPAL_FELICA_NUMSLOTS_16    0x0F    /**< Value for \c bNumSlots = 16. */
/*@}*/

/**
* \brief Perform the Felica ReqC command.
*
* \b Note: This function waits until all cards in all timeslots have had time to reply even though only the first response is returned.\n
* The formula used is <b><em>1208us * (n-1)</em></b> according to JIS X 6319-4:2005.
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalFelica_ReqC(
                            void* pDataParams,      /**< [In] Pointer to this layer's parameter structure. */
                            uint8_t * pSystemCode,  /**< [In] System-Code; uint8_t[2]. */
                            uint8_t bNumTimeSlots,  /**< [In] Number of timeslots to use. Refer to e.g. #PHPAL_FELICA_NUMSLOTS_1 for valid values. */
                            uint8_t * pRxBuffer     /**< [Out] 8 bytes IDm + 8 bytes PMm; uint8_t[16]. */
                            );

/**
* \brief This command activates a Felica card.
*
* \b Note: If an IDm is passed to this function, it is stored as the current IDm and no real activation is done.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalFelica_ActivateCard(
                                    void* pDataParams,              /**< [In] Pointer to this layer's parameter structure. */
                                    uint8_t * pIDmPMm,              /**< [In] IDm followed by PMm; If supplied it is stored and no real activation is done. */
                                    uint8_t bIDmPMmLength,          /**< [In] IDm length; 0 or 16. */
                                    uint8_t * pSystemCode,          /**< [In] System-Code; uint8_t[2]. */
                                    uint8_t bNumTimeSlots,          /**< [In] Number of timeslots to use. Refer to e.g. #PHPAL_FELICA_NUMSLOTS_1 for valid values. */
                                    uint8_t * pRxBuffer,            /**< [Out] 8 bytes NFCID2 + 8 bytes PAD; uint8_t[16]. */
                                    uint8_t * pRxLength,            /**< [Out] Length of received data. 0 or 16. */
                                    uint8_t * pMoreCardsAvailable   /**< [Out] Whether there are more cards in the field or not; uint8_t. */
                                    );

/**
* \brief Exchange data with the Picc.
*
* \c wOption can be one of:\n
* \li #PH_EXCHANGE_DEFAULT
* \li #PH_EXCHANGE_BUFFER_FIRST
* \li #PH_EXCHANGE_BUFFER_CONT
* \li #PH_EXCHANGE_BUFFER_LAST
*
* Alternatively, the following bits can be combined:\n
* \li #PH_EXCHANGE_BUFFERED_BIT
* \li #PH_EXCHANGE_LEAVE_BUFFER_BIT
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalFelica_Exchange(
                                void* pDataParams,      /**< [In] Pointer to this layer's parameter structure. */
                                uint16_t wOption,       /**< [In] Option parameter. */
                                uint16_t wN,            /**< [In] N to calulate the response timeout. */
                                uint8_t* pTxBuffer,     /**< [In] Data to transmit; Length and IDm is added automatically. */
                                uint16_t wTxLength,     /**< [In] Length of data to transmit. */
                                uint8_t ** ppRxBuffer,  /**< [Out] Pointer to received data; Length, response code and IDm are removed automatically. */
                                uint16_t * pRxLength    /**< [Out] number of received data bytes. */
                                );

/**
* \brief As the card receives the Get Serial Number command, it shall respond with that one.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_USE_CONDITION No Serial number available at the moment.
*/
phStatus_t phpalFelica_GetSerialNo(
                                   void * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                                   uint8_t * pUidOut,   /**< [Out] Last Uid (IDm + PMm); uint8_t[16]. */
                                   uint8_t * pLenUidOut /**< [Out] Length of Uid; 0 or 16. */
                                   );

/** @} */
#endif /* NXPBUILD__PHPAL_FELICA */

#ifdef __cplusplus
} /* Extern C */
#endif

#endif /* PHPALFELICA_H */
