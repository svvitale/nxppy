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
* Internal definitions for Log Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.1 $
* $Date: Fri Apr 15 09:29:17 2011 $
*
* History:
*  CHu: Generated 17. February 2011
*
*/

#ifndef PHLOG_INT_H
#define PHLOG_INT_H

#include <ph_Status.h>
#include <ph_TypeDefs.h>

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/** \addtogroup ph_Private
*  @{
*/

/**
* \brief Retreive \ref phLog_RegisterEntry_t corresponding to given DataParams pointer
*/
phLog_RegisterEntry_t * phLog_GetRegisteredEntry(
    void * pDataParams  /**< [In] The DataParams of the calling function. */
    );

/**
* \brief Add a new log entry containing raw data. \see phLog_LogEnty_t
*/
void phLog_AddParam_Raw(
                        void * pDataParams,     /**< [In] The DataParams of the calling function. */
                        uint8_t bLogType,       /**< [In] Type of Entry (one of the \c PH_LOG_LOGTYPE_* values). */
                        const char * pName,     /**< [In] The Null-terminated name of the parameter. */
                        const void * pParam,    /**< [In] Pointer to the memory where the parameter resides. */
                        uint16_t wLength,       /**< [In] The length in bytes to the supplied buffer. */
                        uint8_t bDataType       /**< [In] Indicates the value type (either #PH_LOG_DATATYPE_BUFFER or #PH_LOG_DATATYPE_VALUE). */
                        );

/** @} */

#ifdef __cplusplus
} /* Extern C */
#endif

#endif  /* PHLOG_INT_H */
