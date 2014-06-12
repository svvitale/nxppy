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
* Internal definitions ICode EPC/UID Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:26:23 2011 $
*
* History:
*  CHu: Generated 9. September 2009
*
*/

#ifndef PHPALEPCUID_SW_INT_H
#define PHPALEPCUID_SW_INT_H

#include <ph_Status.h>

/** \addtogroup ph_Private
* @{
*/

#define PHPAL_EPCUID_SW_CMD_BEGINROUND          0x30U   /**< BEGIN ROUND command code. */
#define PHPAL_EPCUID_SW_CMD_WRITE               0x01U   /**< WRITE command code. */
#define PHPAL_EPCUID_SW_CMD_DESTROY             0x02U   /**< DESTROY command code. */

#define PHPAL_EPCUID_SW_UID_LENGTH              12U     /**< The UID length in bytes. */

#define PHPAL_EPCUID_SW_T0_MIN_US               111U    /**< t0(min) in microseconds. */
#define PHPAL_EPCUID_SW_T1_MIN_US               302U    /**< t1(min) in microseconds. */
#define PHPAL_EPCUID_SW_T2_MIN_US               302U    /**< t2(min) in microseconds. */
#define PHPAL_EPCUID_SW_T3_MIN_US               378U    /**< t3(min) in microseconds. */
#define PHPAL_EPCUID_SW_T4_MIN_US               300U    /**< t4(min) in microseconds. */
#define PHPAL_EPCUID_SW_T5_MIN_US               149U    /**< t5(min) in microseconds. */

/** Time extension in microseconds for all timeouts. */
#define PHPAL_EPCUID_SW_EXT_TIME_US             60U

/** Deaf time for BEGIN ROUND in ETUs.
*
* deaf time = t5 + RSOF + some spare time. (= 11 ETUs)
* Note: This is needed to ignore Slot-F response if any.
*/
#define PHPAL_EPCUID_SW_BEGINROUND_DEAFTIME_ETU 11U

/** Timeout for anticollision commands in microseconds. */
#define PHPAL_EPCUID_SW_TIMEOUT_ANTICOLL_US     PHPAL_EPCUID_SW_T3_MIN_US + PHPAL_EPCUID_SW_EXT_TIME_US

/** Timeout for all other commands in microseconds. */
#define PHPAL_EPCUID_SW_TIMEOUT_DEFAULT_US      6400U

/** Deaf time for all other commands in ETUs. */
#define PHPAL_EPCUID_SW_DEAFTIME_DEFAULT_ETU    6U

/**
* \brief Parse EPC/UID response after BeginRound / CloseSlot Command.
*
* Fills either \ref phpalEpcUid_Sw_DataParams_t::bEpc or \ref phpalEpcUid_Sw_DataParams_t::bIdd.
*
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_PROTOCOL_ERROR Invalid response.
* \retval Other Depending on implementation and underlaying component.
*/
phStatus_t phpalEpcUid_Sw_ParseResponse(
                                        phpalEpcUid_Sw_DataParams_t * pDataParams,  /**< [In] Pointer to this layer's parameter structure. */
                                        uint8_t * pRxBuffer,                        /**< [In] Data returned by the tag. */
                                        uint16_t wRxLength                          /**< [In] Length of the received data. */
                                        );

/** @}
* end of ph_Private
*/

#endif /* PHPALEPCUID_SW_INT_H */
