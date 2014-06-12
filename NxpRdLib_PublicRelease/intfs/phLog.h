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
* Log Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.2 $
* $Date: Fri Apr 15 09:27:19 2011 $
*
* History:
*  CHu: Generated 9. October 2009
*
*/

#ifndef PHLOG_H
#define PHLOG_H

#include <ph_Status.h>
#include <ph_TypeDefs.h>

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#ifdef NXPBUILD__PH_LOG

/** \defgroup phLog Log
*
* \brief This layer provides logging and debug functionality.
* It is different from the other layers in the way it is initialised.
* It stores it's data parameters internally and only once, thus
* there can be only one instance.
* @{
*/

#define PH_LOG_DATATYPE_BUFFER  0x00    /**< Data type buffer */
#define PH_LOG_DATATYPE_VALUE   0x01    /**< Data type value */

#define PH_LOG_LOGTYPE_INFO     0x00    /**< Log Type : Info */
#define PH_LOG_LOGTYPE_ERROR    0x01    /**< Log Type : Error */
#define PH_LOG_LOGTYPE_WARN     0x02    /**< Log Type : Warn */
#define PH_LOG_LOGTYPE_DEBUG    0x03    /**< Log Type : Debug */

#define PH_LOG_OPTION_CATEGORY_ENTER    0x01    /**< Execute Option: Logging takes place at function entry. */
#define PH_LOG_OPTION_CATEGORY_GEN      0x02    /**< Execute Option: Logging takes place in the middle of a function. */
#define PH_LOG_OPTION_CATEGORY_LEAVE    0x03    /**< Execute Option: Logging takes place before leaving the function. */

/**
* \brief Definition of a singe Log entry
*/
typedef struct
{
    uint8_t bLogType;           /**< Type of Entry (one of the \c PH_LOG_LOGTYPE_* values). */
    uint8_t const * pString;    /**< Null-terminated string. */
    void const * pData;         /**< Pointer to the data. */
    uint16_t wDataLen;          /**< Length of the data. */
    uint8_t bDataType;          /**< Indicates the value type (either #PH_LOG_DATATYPE_BUFFER or #PH_LOG_DATATYPE_VALUE). */
} phLog_LogEntry_t;

/**
* \brief Definition of a Register Entry
*/
typedef struct
{
    void * pDataParams;             /**< Component for which logging shall be performed. */
    phLog_LogEntry_t * pLogEntries; /**< An array of \ref phLog_LogEntry_t structures. */
    uint16_t wNumLogEntries;        /**< Number of valid entries within the array. */
    uint16_t wMaxLogEntries;        /**< Number of log entries the \ref phLog_LogEntry_t array can hold. */
} phLog_RegisterEntry_t;

/** Function definition for log callback function */
typedef void (*pphLog_Callback_t)(void * pDataParams, uint8_t bOption, phLog_LogEntry_t * pLogEntries, uint16_t wEntryCount);

/**
* \brief Log parameter structure
*/
typedef struct
{
    pphLog_Callback_t pLogCallback;             /**< Pointer to a log callback function. */
    phLog_RegisterEntry_t * pRegisterEntries;   /**< An array of \ref phLog_RegisterEntry_t structures. */
    uint16_t wNumRegisterEntries;               /**< Number of valid entries within the array. */
    uint16_t wMaxRegisterEntries;               /**< Number of log entries the \ref phLog_RegisterEntry_t array can hold. */
} phLog_DataParams_t;

/**
* \brief Allocate space in memory for a \c pString value. \see phLog_LogEnty_t
*/
#define PH_LOG_ALLOCATE_PARAMNAME(pParam) char const * pParam##_log = #pParam
#define PH_LOG_ALLOCATE_TEXT(pIdent, pText) char const * (pIdent) = (pText)

/**
* \brief Initialise Logging.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_INVALID_PARAMETER Input parameter combination is invalid.
*/
phStatus_t phLog_Init(
                      pphLog_Callback_t pLogCallback,           /**< [In] Pointer to a log callback function. */
                      phLog_RegisterEntry_t * pRegisterEntries, /**< [In] An array of \ref phLog_RegisterEntry_t memory. */
                      uint16_t wMaxRegisterEntries              /**< [In] Number of log entries the \ref phLog_RegisterEntry_t array can hold. */
                      );

/**
* \brief Register component for logging.
* \return Status code
* \retval #PH_ERR_SUCCESS Operation successful.
* \retval #PH_ERR_USE_CONDITION Logging is not properly initialized.
* \retval #PH_ERR_INVALID_PARAMETER \c wMaxLogEntries is invalid.
* \retval #PH_ERR_BUFFER_OVERFLOW The maximum Register Entry count is reached.
*/
phStatus_t phLog_Register(
                          void * pDataParams,               /**< [In] Component for which logging shall be performed. */
                          phLog_LogEntry_t * pLogEntries,   /**< [In] An array of \ref phLog_LogEntry_t structures. */
                          uint16_t wMaxLogEntries           /**< [In] Number of log entries the \ref phLog_LogEntry_t array can hold. */
                          );

/**
* \brief Add a new log entry containing just a string. \see phLog_LogEnty_t
*/
void phLog_AddString(
                     void * pDataParams,    /**< [In] The DataParams of the calling function. */
                     uint8_t bLogType,      /**< [In] Type of Entry (one of the \c PH_LOG_LOGTYPE_* values). */
                     char const * pString   /**< [In] The Null-terminated string to add. */
                     );

/**
* \brief Add a new log entry containing an #uint8_t parameter. \see phLog_LogEnty_t
*/
void phLog_AddParam_Uint8(
                          void * pDataParams,   /**< [In] The DataParams of the calling function. */
                          uint8_t bLogType,     /**< [In] Type of Entry (one of the \c PH_LOG_LOGTYPE_* values). */
                          char const * pName,   /**< [In] The Null-terminated name of the parameter. */
                          uint8_t * pParam      /**< [In] Pointer to the memory where the parameter resides. */
                          );

/**
* \brief Add a new log entry containing an #uint16_t parameter. \see phLog_LogEnty_t
*/
void phLog_AddParam_Uint16(
                           void * pDataParams,  /**< [In] The DataParams of the calling function. */
                           uint8_t bLogType,    /**< [In] Type of Entry (one of the \c PH_LOG_LOGTYPE_* values). */
                           char const * pName,  /**< [In] The Null-terminated name of the parameter. */
                           uint16_t * pParam    /**< [In] Pointer to the memory where the parameter resides. */
                           );

/**
* \brief Add a new log entry containing an #uint32_t parameter. \see phLog_LogEnty_t
*/
void phLog_AddParam_Uint32(
                           void * pDataParams,   /**< [In] The DataParams of the calling function. */
                           uint8_t bLogType,    /**< [In] Type of Entry (one of the \c PH_LOG_LOGTYPE_* values). */
                           char const * pName,  /**< [In] The Null-terminated name of the parameter. */
                           uint32_t * pParam    /**< [In] Pointer to the memory where the parameter resides. */
                           );

/**
* \brief Add a new log entry containing a byte-buffer of variable length. \see phLog_LogEnty_t
*/
void phLog_AddParam_Buffer(
                           void * pDataParams,   /**< [In] The DataParams of the calling function. */
                           uint8_t bLogType,    /**< [In] Type of Entry (one of the \c PH_LOG_LOGTYPE_* values). */
                           char const * pName,  /**< [In] The Null-terminated name of the parameter. */
                           void const * pParam, /**< [In] Pointer to the memory where the parameter resides. */
                           uint16_t wLength     /**< [In] The length in bytes to the supplied buffer. */
                           );

/**
* \brief Execute the callback function to process the log buffer.
*/
void phLog_Execute(
                   void * pDataParams,  /**< [In] The DataParams of the calling function. */
                   uint8_t bOption      /**< [In] Option byte (one of the PH_LOG_OPTION* defines). */
                   );

/** @} */
#endif /* NXPBUILD__PH_LOG */

#ifdef __cplusplus
} /* Extern C */
#endif

#endif  /* PHLOG_H */
