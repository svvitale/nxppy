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
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:27:26 2011 $
*
* History:
*  CHu: Generated 09. October 2009
*
*/

#include <phLog.h>

#ifdef NXPBUILD__PH_LOG

#include <ph_Status.h>
#include <ph_RefDefs.h>
#include "phLog_Int.h"

static const uint8_t *      PH_MEMLOC_CONST_ROM gpkphLog_String_BufferOverflow = (uint8_t*)"OVERFLOW";
static phLog_DataParams_t   PH_MEMLOC_REM gphLog_LogDataParams = {NULL, NULL, 0, 0};

phStatus_t phLog_Init(
                      pphLog_Callback_t pLogCallback,
                      phLog_RegisterEntry_t * pRegisterEntries,
                      uint16_t wMaxRegisterEntries
                      )
{
    /* Check parameters */
    if (pLogCallback != NULL)
    {
        if (wMaxRegisterEntries == 0)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_LOG);
        }
        PH_ASSERT_NULL (pRegisterEntries)
    }

    gphLog_LogDataParams.pLogCallback           = pLogCallback;
    gphLog_LogDataParams.pRegisterEntries       = pRegisterEntries;
    gphLog_LogDataParams.wNumRegisterEntries    = 0;
    gphLog_LogDataParams.wMaxRegisterEntries    = wMaxRegisterEntries;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_LOG);
}

phStatus_t phLog_Register(
                          void * pDataParams,
                          phLog_LogEntry_t * pLogEntries,
                          uint16_t wMaxLogEntries
                          )
{
    /* Parameter check */
    if ((pDataParams == NULL) || (pLogEntries == NULL) || (wMaxLogEntries == 0))
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_LOG);
    }

    /* Logging has to be initialized */
    if (gphLog_LogDataParams.pLogCallback == NULL)
    {
        return PH_ADD_COMPCODE(PH_ERR_USE_CONDITION, PH_COMP_LOG);
    }

    /* Check for buffer overflow */
    if (gphLog_LogDataParams.wMaxRegisterEntries < (gphLog_LogDataParams.wNumRegisterEntries + 1))
    {
        return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_LOG);
    }

    /* Add Register Entry */
    gphLog_LogDataParams.pRegisterEntries[gphLog_LogDataParams.wNumRegisterEntries].pDataParams = pDataParams;
    gphLog_LogDataParams.pRegisterEntries[gphLog_LogDataParams.wNumRegisterEntries].pLogEntries = pLogEntries;
    gphLog_LogDataParams.pRegisterEntries[gphLog_LogDataParams.wNumRegisterEntries].wNumLogEntries = 0;
    gphLog_LogDataParams.pRegisterEntries[gphLog_LogDataParams.wNumRegisterEntries].wMaxLogEntries = wMaxLogEntries;

    /* Increment number of registered entry pairs */
    ++gphLog_LogDataParams.wNumRegisterEntries;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_LOG);
}

void phLog_AddString(
                     void * pDataParams,
                     uint8_t bLogType,
                     char const * pFunctionName
                     )
{
    phLog_AddParam_Raw(pDataParams, bLogType, pFunctionName, NULL, 0, PH_LOG_DATATYPE_BUFFER);
}

void phLog_AddParam_Uint8(
                          void * pDataParams,
                          uint8_t bLogType,
                          char const * pName,
                          uint8_t * pParam
                          )
{
    phLog_AddParam_Raw(pDataParams, bLogType, pName, pParam, sizeof(uint8_t), PH_LOG_DATATYPE_VALUE);
}

void phLog_AddParam_Uint16(
                           void * pDataParams,
                           uint8_t bLogType,
                           char const * pName,
                           uint16_t * pParam
                           )
{
    phLog_AddParam_Raw(pDataParams, bLogType, pName, pParam, sizeof(uint16_t), PH_LOG_DATATYPE_VALUE);
}

void phLog_AddParam_Uint32(
                           void * pDataParams,
                           uint8_t bLogType,
                           char const * pName,
                           uint32_t * pParam
                           )
{
    phLog_AddParam_Raw(pDataParams, bLogType, pName, pParam, sizeof(uint32_t), PH_LOG_DATATYPE_VALUE);
}

void phLog_AddParam_Buffer(
                           void * pDataParams,
                           uint8_t bLogType,
                           char const * pName,
                           void const * pParam,
                           uint16_t wLength
                           )
{
    phLog_AddParam_Raw(pDataParams, bLogType, pName, pParam, wLength, PH_LOG_DATATYPE_BUFFER);
}

void phLog_Execute(
                   void * pDataParams,
                   uint8_t bOption
                   )
{
    phLog_RegisterEntry_t * PH_MEMLOC_REM pRegisterEntry;

    /* Don't do anything if no callback has been registered */
    if (gphLog_LogDataParams.pLogCallback == NULL)
    {
        return;
    }

    /* Retrieve corresponding Register Entry */
    pRegisterEntry = phLog_GetRegisteredEntry(pDataParams);
    if (pRegisterEntry == NULL)
    {
        return;
    }

    /* Invoke the external callback */
    (*(gphLog_LogDataParams.pLogCallback))(pDataParams, bOption, pRegisterEntry->pLogEntries, pRegisterEntry->wNumLogEntries);

    /* Reset entries */
    pRegisterEntry->wNumLogEntries = 0;
}

phLog_RegisterEntry_t * phLog_GetRegisteredEntry(
    void * pDataParams
    )
{
    phLog_RegisterEntry_t * PH_MEMLOC_REM pRegisterEntry;
    uint16_t                PH_MEMLOC_COUNT wIndex;

    /* Init. return value to NULL */
    pRegisterEntry = NULL;

    /* Iterate through all Register Entrys to find given one */
    for (wIndex = 0; wIndex < gphLog_LogDataParams.wNumRegisterEntries; ++wIndex)
    {
        if (pDataParams == gphLog_LogDataParams.pRegisterEntries[wIndex].pDataParams)
        {
            pRegisterEntry = &gphLog_LogDataParams.pRegisterEntries[wIndex];
        }
    }

    return pRegisterEntry;
}

void phLog_AddParam_Raw(
                        void * pDataParams,
                        uint8_t bLogType,
                        char const * pName,
                        void const * pParam,
                        uint16_t wLength,
                        uint8_t bDataType
                        )
{
    phLog_RegisterEntry_t * PH_MEMLOC_REM pRegisterEntry;

    /* Don't do anything if no callback has been registered */
    if (gphLog_LogDataParams.pLogCallback == NULL)
    {
        return;
    }

    /* Retrieve corresponding Register Entry */
    pRegisterEntry = phLog_GetRegisteredEntry(pDataParams);
    if (pRegisterEntry == NULL)
    {
        return;
    }

    /* check if entry is available */
    if (pRegisterEntry->wMaxLogEntries <= pRegisterEntry->wNumLogEntries)
    {
        return;
    }

    /* Build up the paramter */
    if (pRegisterEntry->wMaxLogEntries > (pRegisterEntry->wNumLogEntries + 1))
    {
        pRegisterEntry->pLogEntries[pRegisterEntry->wNumLogEntries].bLogType = bLogType;
        pRegisterEntry->pLogEntries[pRegisterEntry->wNumLogEntries].pString = (uint8_t const*)pName;
        pRegisterEntry->pLogEntries[pRegisterEntry->wNumLogEntries].pData = pParam;
        pRegisterEntry->pLogEntries[pRegisterEntry->wNumLogEntries].wDataLen = wLength;
    }
    /* Else return buffer overflow error */
    else
    {
        pRegisterEntry->pLogEntries[pRegisterEntry->wNumLogEntries].bLogType = PH_LOG_LOGTYPE_ERROR;
        pRegisterEntry->pLogEntries[pRegisterEntry->wNumLogEntries].pString = (uint8_t const*)gpkphLog_String_BufferOverflow;
        pRegisterEntry->pLogEntries[pRegisterEntry->wNumLogEntries].pData = NULL;
        pRegisterEntry->pLogEntries[pRegisterEntry->wNumLogEntries].wDataLen = 0;
    }

    /* Also store the endianness of the data */
    pRegisterEntry->pLogEntries[pRegisterEntry->wNumLogEntries].bDataType = bDataType;

    /* Increment buffer entries */
    ++pRegisterEntry->wNumLogEntries;
}

#endif /* NXPBUILD__PH_LOG */
