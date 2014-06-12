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
* Generic KeyStore Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.4 $
* $Date: Fri Apr 15 09:27:56 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#include <ph_Status.h>
#include <phKeyStore.h>
#include <ph_RefDefs.h>
#include "phKeyStore_Int.h"

#ifdef NXPBUILD__PH_KEYSTORE_SW
#include "Sw/phKeyStore_Sw.h"
#endif /* NXPBUILD__PH_KEYSTORE_SW */

#ifdef NXPBUILD__PH_KEYSTORE_RC632
#include "Rc632/phKeyStore_Rc632.h"
#endif /* NXPBUILD__PH_KEYSTORE_RC632 */

#ifdef NXPBUILD__PH_KEYSTORE_RC663
#include "Rc663/phKeyStore_Rc663.h"
#endif /* NXPBUILD__PH_KEYSTORE_RC663 */

#ifdef NXPBUILD__PH_KEYSTORE_RD710
#include "Rd710/phKeyStore_Rd710.h"
#endif /* NXPBUILD__PH_KEYSTORE_RD710 */

#ifdef NXPBUILD__PH_KEYSTORE

phStatus_t phKeyStore_FormatKeyEntry(
                                     void * pDataParams,            /**< [In] Pointer to this layer's parameter structure. */                           
                                     uint16_t wKeyNo,               /**< [In] KeyEntry number to be Formatted (0x00 to F0). */
                                     uint16_t wNewKeyType            /**< [In] New Key type of the KeyEntry (predefined type of KeyType).*/ 
                                     )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phKeyStore_FormatKeyEntry");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wKeyNo);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wNewKeyType);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wKeyNo_log, &wKeyNo);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wNewKeyType_log, &wNewKeyType);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_KEYSTORE)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_KEYSTORE_SW
    case PH_KEYSTORE_SW_ID:
        status = phKeyStore_Sw_FormatKeyEntry((phKeyStore_Sw_DataParams_t *)pDataParams,wKeyNo,wNewKeyType);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_SW */

#ifdef NXPBUILD__PH_KEYSTORE_RC632
    case PH_KEYSTORE_RC632_ID:
        status = phKeyStore_Rc632_FormatKeyEntry((phKeyStore_Rc632_DataParams_t *)pDataParams,wKeyNo,wNewKeyType);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC632 */

#ifdef NXPBUILD__PH_KEYSTORE_RC663
    case PH_KEYSTORE_RC663_ID:
        status = phKeyStore_Rc663_FormatKeyEntry((phKeyStore_Rc663_DataParams_t *)pDataParams,wKeyNo,wNewKeyType);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC663 */

#ifdef NXPBUILD__PH_KEYSTORE_RD710
    case PH_KEYSTORE_RD710_ID:
        status = phKeyStore_Rd710_FormatKeyEntry((phKeyStore_Rd710_DataParams_t *)pDataParams,wKeyNo,wNewKeyType);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
        break;
    }
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}


phStatus_t phKeyStore_SetKey(
                             void * pDataParams,
                             uint16_t wKeyNo,
                             uint16_t wKeyVersion,
                             uint16_t wKeyType,
                             uint8_t * pNewKey,
                             uint16_t wNewKeyVersion
                             )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phKeyStore_SetKey");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wKeyNo);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wKeyVersion);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wKeyType);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pNewKey);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wNewKeyVersion);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wKeyNo_log, &wKeyNo);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wKeyVersion_log, &wKeyVersion);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wKeyType_log, &wKeyType);
    PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, pNewKey_log, pNewKey, phKeyStore_GetKeySize(wKeyType));
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wNewKeyVersion_log, &wNewKeyVersion);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);
	PH_ASSERT_NULL (pNewKey);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_KEYSTORE)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_KEYSTORE_SW
    case PH_KEYSTORE_SW_ID:
        status = phKeyStore_Sw_SetKey((phKeyStore_Sw_DataParams_t *)pDataParams, wKeyNo, wKeyVersion, wKeyType, pNewKey, wNewKeyVersion);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_SW */

#ifdef NXPBUILD__PH_KEYSTORE_RC632
    case PH_KEYSTORE_RC632_ID:
        status = phKeyStore_Rc632_SetKey((phKeyStore_Rc632_DataParams_t *)pDataParams, wKeyNo, wKeyVersion, wKeyType, pNewKey, wNewKeyVersion);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC632 */

#ifdef NXPBUILD__PH_KEYSTORE_RC663
    case PH_KEYSTORE_RC663_ID:
        status = phKeyStore_Rc663_SetKey((phKeyStore_Rc663_DataParams_t *)pDataParams, wKeyNo, wKeyVersion, wKeyType, pNewKey, wNewKeyVersion);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC663 */

#ifdef NXPBUILD__PH_KEYSTORE_RD710
    case PH_KEYSTORE_RD710_ID:
        status = phKeyStore_Rd710_SetKey((phKeyStore_Rd710_DataParams_t *)pDataParams, wKeyNo, wKeyVersion, wKeyType, pNewKey, wNewKeyVersion);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
        break;
    }
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;

}
phStatus_t phKeyStore_SetKeyAtPos(
                                  void * pDataParams,
                                  uint16_t wKeyNo,
                                  uint16_t wPos,
                                  uint16_t wKeyType,
                                  uint8_t * pNewKey,
                                  uint16_t wNewKeyVersion
                                  )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phKeyStore_SetKeyAtPos");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wKeyNo);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wPos);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wKeyType);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pNewKey);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wNewKeyVersion);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wKeyNo_log, &wKeyNo);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wPos_log, &wPos);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wKeyType_log, &wKeyType);
    PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, pNewKey_log, pNewKey, phKeyStore_GetKeySize(wKeyType));
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wNewKeyVersion_log, &wNewKeyVersion);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);
	PH_ASSERT_NULL (pNewKey);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_KEYSTORE)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_KEYSTORE_SW
    case PH_KEYSTORE_SW_ID:
        status = phKeyStore_Sw_SetKeyAtPos((phKeyStore_Sw_DataParams_t *)pDataParams, wKeyNo, wPos, wKeyType, pNewKey, wNewKeyVersion);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_SW */

#ifdef NXPBUILD__PH_KEYSTORE_RC632
    case PH_KEYSTORE_RC632_ID:
        status = phKeyStore_Rc632_SetKeyAtPos((phKeyStore_Rc632_DataParams_t *)pDataParams, wKeyNo, wPos, wKeyType, pNewKey, wNewKeyVersion);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC632 */

#ifdef NXPBUILD__PH_KEYSTORE_RC663
    case PH_KEYSTORE_RC663_ID:
        status = phKeyStore_Rc663_SetKeyAtPos((phKeyStore_Rc663_DataParams_t *)pDataParams, wKeyNo, wPos, wKeyType, pNewKey, wNewKeyVersion);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC663 */

#ifdef NXPBUILD__PH_KEYSTORE_RD710
    case PH_KEYSTORE_RD710_ID:
        status = phKeyStore_Rd710_SetKeyAtPos((phKeyStore_Rd710_DataParams_t *)pDataParams, wKeyNo, wPos, wKeyType, pNewKey, wNewKeyVersion);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
        break;
    }
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}

phStatus_t phKeyStore_SetKUC(
                                void * pDataParams,
                                uint16_t wKeyNo,
                                   uint16_t wRefNoKUC
                                   )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phKeyStore_SetKUC");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wKeyNo);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wRefNoKUC);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wKeyNo_log, &wKeyNo);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wRefNoKUC_log, &wRefNoKUC);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_KEYSTORE)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_KEYSTORE_SW
    case PH_KEYSTORE_SW_ID:
        status = phKeyStore_Sw_SetKUC((phKeyStore_Sw_DataParams_t *)pDataParams, wKeyNo, wRefNoKUC);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_SW */

#ifdef NXPBUILD__PH_KEYSTORE_RC632
    case PH_KEYSTORE_RC632_ID:
        status = phKeyStore_Rc632_SetKUC((phKeyStore_Rc632_DataParams_t *)pDataParams, wKeyNo, wRefNoKUC);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC632 */

#ifdef NXPBUILD__PH_KEYSTORE_RC663
    case PH_KEYSTORE_RC663_ID:
        status = phKeyStore_Rc663_SetKUC((phKeyStore_Rc663_DataParams_t *)pDataParams, wKeyNo, wRefNoKUC);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC663 */

#ifdef NXPBUILD__PH_KEYSTORE_RD710
    case PH_KEYSTORE_RD710_ID:
        status = phKeyStore_Rd710_SetKUC((phKeyStore_Rd710_DataParams_t *)pDataParams, wKeyNo, wRefNoKUC);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
        break;
    }
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;

}

phStatus_t phKeyStore_SetFullKeyEntry(
                                      void * pDataParams,
                                      uint16_t wNoOfKeys,
                                      uint16_t wKeyNo,
                                      uint16_t wNewRefNoKUC,
                                      uint16_t wNewKeyType,
                                      uint8_t * pNewKeys,
                                      uint16_t * pNewKeyVersionList
                                      )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phKeyStore_SetFullKeyEntry");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wNoOfKeys);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wKeyNo);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wNewRefNoKUC);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wNewKeyType);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pNewKeys);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pNewKeyVersionList);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wNoOfKeys_log, &wNoOfKeys);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wKeyNo_log, &wKeyNo);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wNewRefNoKUC_log, &wNewRefNoKUC);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wNewKeyType_log, &wNewKeyType);
    PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, pNewKeys_log, pNewKeys, phKeyStore_GetKeySize(wNewKeyType)*wNoOfKeys);
    PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, pNewKeyVersionList_log, pNewKeyVersionList, wNoOfKeys);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);
	PH_ASSERT_NULL (pNewKeys);
	PH_ASSERT_NULL (pNewKeyVersionList);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_KEYSTORE)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_KEYSTORE_SW
    case PH_KEYSTORE_SW_ID:
        status = phKeyStore_Sw_SetFullKeyEntry((phKeyStore_Sw_DataParams_t *)pDataParams, wNoOfKeys, wKeyNo, wNewRefNoKUC, wNewKeyType, pNewKeys, pNewKeyVersionList);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_SW */

#ifdef NXPBUILD__PH_KEYSTORE_RC632
    case PH_KEYSTORE_RC632_ID:
        status = phKeyStore_Rc632_SetFullKeyEntry((phKeyStore_Rc632_DataParams_t *)pDataParams, wNoOfKeys, wKeyNo, wNewRefNoKUC, wNewKeyType, pNewKeys, pNewKeyVersionList);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC632 */

#ifdef NXPBUILD__PH_KEYSTORE_RC663
    case PH_KEYSTORE_RC663_ID:
        status = phKeyStore_Rc663_SetFullKeyEntry((phKeyStore_Rc663_DataParams_t *)pDataParams, wNoOfKeys, wKeyNo, wNewRefNoKUC, wNewKeyType, pNewKeys, pNewKeyVersionList);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC663 */

#ifdef NXPBUILD__PH_KEYSTORE_RD710
    case PH_KEYSTORE_RD710_ID:
        status = phKeyStore_Rd710_SetFullKeyEntry((phKeyStore_Rd710_DataParams_t *)pDataParams, wNoOfKeys, wKeyNo, wNewRefNoKUC, wNewKeyType, pNewKeys, pNewKeyVersionList);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
        break;
    }
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}

phStatus_t phKeyStore_GetKeyEntry(
                                    void * pDataParams,    
                                    uint16_t wKeyNo,
                                    uint16_t wKeyVersionBufSize,
                                    uint16_t * wKeyVersion,
                                    uint16_t * wKeyVersionLength,
                                    uint16_t * pKeyType
                                    )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phKeyStore_GetKeyEntry");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wKeyNo);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wKeyVersionBufSize);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wKeyVersion);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pKeyType);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wKeyNo_log, &wKeyNo);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wKeyVersionBufSize_log, &wKeyVersionBufSize);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);
	PH_ASSERT_NULL (wKeyVersion);
	PH_ASSERT_NULL (wKeyVersionLength);
	PH_ASSERT_NULL (pKeyType);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_KEYSTORE)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_KEYSTORE_SW
    case PH_KEYSTORE_SW_ID:
        status = phKeyStore_Sw_GetKeyEntry((phKeyStore_Sw_DataParams_t *)pDataParams, wKeyNo, wKeyVersionBufSize, wKeyVersion, wKeyVersionLength, pKeyType);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_SW */

#ifdef NXPBUILD__PH_KEYSTORE_RC632
    case PH_KEYSTORE_RC632_ID:
        status = phKeyStore_Rc632_GetKeyEntry((phKeyStore_Rc632_DataParams_t *)pDataParams, wKeyNo, wKeyVersionBufSize, wKeyVersion, wKeyVersionLength, pKeyType);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC632 */

#ifdef NXPBUILD__PH_KEYSTORE_RC663
    case PH_KEYSTORE_RC663_ID:
        status = phKeyStore_Rc663_GetKeyEntry((phKeyStore_Rc663_DataParams_t *)pDataParams, wKeyNo, wKeyVersionBufSize, wKeyVersion, wKeyVersionLength, pKeyType);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC663 */

#ifdef NXPBUILD__PH_KEYSTORE_RD710
    case PH_KEYSTORE_RD710_ID:
        status = phKeyStore_Rd710_GetKeyEntry((phKeyStore_Rd710_DataParams_t *)pDataParams, wKeyNo, wKeyVersionBufSize, wKeyVersion, wKeyVersionLength, pKeyType);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
        break;
    }
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
#ifdef NXPBUILD__PH_LOG
    if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
    {
        PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, wKeyVersion_log, wKeyVersion, *wKeyVersionLength);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, pKeyType_log, pKeyType);
    }
#endif
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}

phStatus_t phKeyStore_GetKey(
                            void * pDataParams,
                            uint16_t wKeyNo,
                            uint16_t wKeyVersion,
                            uint8_t bKeyBufSize,
                            uint8_t * pKey,
                            uint16_t * pKeyType
                             )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phKeyStore_GetKey");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wKeyNo);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wKeyVersion);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(bKeyBufSize);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pKey);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pKeyType);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wKeyNo_log, &wKeyNo);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wKeyVersion_log, &wKeyVersion);
    PH_LOG_HELPER_ADDPARAM_UINT8(PH_LOG_LOGTYPE_DEBUG, bKeyBufSize_log, &bKeyBufSize);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);
	PH_ASSERT_NULL (pKey);
	PH_ASSERT_NULL (pKeyType);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_KEYSTORE)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_KEYSTORE_SW
    case PH_KEYSTORE_SW_ID:
        status = phKeyStore_Sw_GetKey((phKeyStore_Sw_DataParams_t *)pDataParams, wKeyNo, wKeyVersion, bKeyBufSize, pKey, pKeyType);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_SW */

#ifdef NXPBUILD__PH_KEYSTORE_RC632
    case PH_KEYSTORE_RC632_ID:
        status = phKeyStore_Rc632_GetKey((phKeyStore_Rc632_DataParams_t *)pDataParams, wKeyNo, wKeyVersion, bKeyBufSize, pKey, pKeyType);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC632 */

#ifdef NXPBUILD__PH_KEYSTORE_RC663
    case PH_KEYSTORE_RC663_ID:
        status = phKeyStore_Rc663_GetKey((phKeyStore_Rc663_DataParams_t *)pDataParams, wKeyNo, wKeyVersion, bKeyBufSize, pKey, pKeyType);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC663 */

#ifdef NXPBUILD__PH_KEYSTORE_RD710
    case PH_KEYSTORE_RD710_ID:
        status = phKeyStore_Rd710_GetKey((phKeyStore_Rd710_DataParams_t *)pDataParams, wKeyNo, wKeyVersion, bKeyBufSize, pKey, pKeyType);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
        break;
    }
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
#ifdef NXPBUILD__PH_LOG
    if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
    {
        PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, pKey_log, pKey, phKeyStore_GetKeySize(*pKeyType));
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, pKeyType_log, pKeyType);
    }
#endif
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}


phStatus_t phKeyStore_SetConfig(
                                void * pDataParams,
                                uint16_t wConfig,
                                uint16_t wValue
                                )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phKeyStore_SetConfig");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wConfig);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wValue);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wConfig_log, &wConfig);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wValue_log, &wValue);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_KEYSTORE)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_KEYSTORE_SW
    case PH_KEYSTORE_SW_ID:
        status = phKeyStore_Sw_SetConfig((phKeyStore_Sw_DataParams_t *)pDataParams,wConfig,wValue);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_SW */

#ifdef NXPBUILD__PH_KEYSTORE_RC632
    case PH_KEYSTORE_RC632_ID:
        status = phKeyStore_Rc632_SetConfig((phKeyStore_Rc632_DataParams_t *)pDataParams,wConfig,wValue);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC632 */

#ifdef NXPBUILD__PH_KEYSTORE_RC663
    case PH_KEYSTORE_RC663_ID:
        status = phKeyStore_Rc663_SetConfig((phKeyStore_Rc663_DataParams_t *)pDataParams,wConfig,wValue);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC663 */

#ifdef NXPBUILD__PH_KEYSTORE_RD710
    case PH_KEYSTORE_RD710_ID:
        status = phKeyStore_Rd710_SetConfig((phKeyStore_Rd710_DataParams_t *)pDataParams,wConfig,wValue);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
        break;
    }
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}


phStatus_t phKeyStore_SetConfigStr(
                                   void * pDataParams,
                                   uint16_t wConfig,
                                   uint8_t *pBuffer,
                                   uint16_t wBufferLength
                                   )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phKeyStore_SetConfigStr");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wConfig);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pBuffer);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wBufferLength);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wConfig_log, &wConfig);
    PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, pBuffer_log, pBuffer, wBufferLength);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wBufferLength_log, &wBufferLength);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);
	PH_ASSERT_NULL (pBuffer);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_KEYSTORE)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_KEYSTORE_SW
    case PH_KEYSTORE_SW_ID:
        status = phKeyStore_Sw_SetConfigStr((phKeyStore_Sw_DataParams_t *)pDataParams,wConfig,pBuffer,wBufferLength);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_SW */

#ifdef NXPBUILD__PH_KEYSTORE_RC632
    case PH_KEYSTORE_RC632_ID:
        status = phKeyStore_Rc632_SetConfigStr((phKeyStore_Rc632_DataParams_t *)pDataParams,wConfig,pBuffer,wBufferLength);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC632 */

#ifdef NXPBUILD__PH_KEYSTORE_RC663
    case PH_KEYSTORE_RC663_ID:
        status = phKeyStore_Rc663_SetConfigStr((phKeyStore_Rc663_DataParams_t *)pDataParams,wConfig,pBuffer,wBufferLength);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC663 */

#ifdef NXPBUILD__PH_KEYSTORE_RD710
    case PH_KEYSTORE_RD710_ID:
        status = phKeyStore_Rd710_SetConfigStr((phKeyStore_Rd710_DataParams_t *)pDataParams,wConfig,pBuffer,wBufferLength);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
        break;
    }
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}


phStatus_t phKeyStore_GetConfig(
                                void * pDataParams,
                                uint16_t wConfig,
                                uint16_t * pValue
                                )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phKeyStore_GetConfig");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wConfig);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pValue);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wConfig_log, &wConfig);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);
	PH_ASSERT_NULL (pValue);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_KEYSTORE)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_KEYSTORE_SW
    case PH_KEYSTORE_SW_ID:
        status = phKeyStore_Sw_GetConfig((phKeyStore_Sw_DataParams_t *)pDataParams,wConfig,pValue);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_SW */

#ifdef NXPBUILD__PH_KEYSTORE_RC632
    case PH_KEYSTORE_RC632_ID:
        status = phKeyStore_Rc632_GetConfig((phKeyStore_Rc632_DataParams_t *)pDataParams,wConfig,pValue);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC632 */

#ifdef NXPBUILD__PH_KEYSTORE_RC663
    case PH_KEYSTORE_RC663_ID:
        status = phKeyStore_Rc663_GetConfig((phKeyStore_Rc663_DataParams_t *)pDataParams,wConfig,pValue);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC663 */

#ifdef NXPBUILD__PH_KEYSTORE_RD710
    case PH_KEYSTORE_RD710_ID:
        status = phKeyStore_Rd710_GetConfig((phKeyStore_Rd710_DataParams_t *)pDataParams,wConfig,pValue);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
        break;
    }
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
#ifdef NXPBUILD__PH_LOG
    if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
    {
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, pValue_log, pValue);
    }
#endif
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}

phStatus_t phKeyStore_GetConfigStr(
                                   void * pDataParams,
                                   uint16_t wConfig,
                                   uint8_t ** ppBuffer,
                                   uint16_t * pBufferLength
                                   )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phKeyStore_GetConfigStr");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wConfig);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(ppBuffer);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pBufferLength);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wConfig_log, &wConfig);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);
	PH_ASSERT_NULL (ppBuffer);
	PH_ASSERT_NULL (pBufferLength);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_KEYSTORE)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_KEYSTORE_SW
    case PH_KEYSTORE_SW_ID:
        status = phKeyStore_Sw_GetConfigStr((phKeyStore_Sw_DataParams_t *)pDataParams,wConfig,ppBuffer,pBufferLength);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_SW */

#ifdef NXPBUILD__PH_KEYSTORE_RC632
    case PH_KEYSTORE_RC632_ID:
        status = phKeyStore_Rc632_GetConfigStr((phKeyStore_Rc632_DataParams_t *)pDataParams,wConfig,ppBuffer,pBufferLength);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC632 */

#ifdef NXPBUILD__PH_KEYSTORE_RC663
    case PH_KEYSTORE_RC663_ID:
        status = phKeyStore_Rc663_GetConfigStr((phKeyStore_Rc663_DataParams_t *)pDataParams,wConfig,ppBuffer,pBufferLength);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC663 */

#ifdef NXPBUILD__PH_KEYSTORE_RD710
    case PH_KEYSTORE_RD710_ID:
        status = phKeyStore_Rd710_GetConfigStr((phKeyStore_Rd710_DataParams_t *)pDataParams,wConfig,ppBuffer,pBufferLength);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
        break;
    }
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
#ifdef NXPBUILD__PH_LOG
    if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
    {
        PH_LOG_HELPER_ADDPARAM_BUFFER(PH_LOG_LOGTYPE_DEBUG, ppBuffer_log, *ppBuffer, *pBufferLength);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, pBufferLength_log, pBufferLength);
    }
#endif
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}




phStatus_t phKeyStore_ChangeKUC(
    void * pDataParams,
    uint16_t wRefNoKUC,
    uint32_t dwLimit
    )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phKeyStore_ChangeKUC");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wRefNoKUC);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(dwLimit);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wRefNoKUC_log, &wRefNoKUC);
    PH_LOG_HELPER_ADDPARAM_UINT32(PH_LOG_LOGTYPE_DEBUG, dwLimit_log, &dwLimit);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_KEYSTORE)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_KEYSTORE_SW
    case PH_KEYSTORE_SW_ID:
        status = phKeyStore_Sw_ChangeKUC((phKeyStore_Sw_DataParams_t *)pDataParams, wRefNoKUC, dwLimit);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_SW */

#ifdef NXPBUILD__PH_KEYSTORE_RC632
    case PH_KEYSTORE_RC632_ID:
        status = phKeyStore_Rc632_ChangeKUC((phKeyStore_Rc632_DataParams_t *)pDataParams, wRefNoKUC, dwLimit);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC632 */

#ifdef NXPBUILD__PH_KEYSTORE_RC663
    case PH_KEYSTORE_RC663_ID:
        status = phKeyStore_Rc663_ChangeKUC((phKeyStore_Rc663_DataParams_t *)pDataParams, wRefNoKUC, dwLimit);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC663 */

#ifdef NXPBUILD__PH_KEYSTORE_RD710
    case PH_KEYSTORE_RD710_ID:
        status = phKeyStore_Rd710_ChangeKUC((phKeyStore_Rd710_DataParams_t *)pDataParams, wRefNoKUC, dwLimit);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
        break;
    }
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}

phStatus_t phKeyStore_GetKUC(
    void * pDataParams,
    uint16_t wRefNoKUC,
    uint32_t * pdwLimit,
    uint32_t * pdwCurVal
    )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phKeyStore_GetKUC");
    /*PH_LOG_HELPER_ALLOCATE_PARAMNAME(pDataParams);*/
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wRefNoKUC);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pdwLimit);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pdwCurVal);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wRefNoKUC_log, &wRefNoKUC);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
	PH_ASSERT_NULL (pDataParams);
	PH_ASSERT_NULL (pdwLimit);
	PH_ASSERT_NULL (pdwCurVal);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_KEYSTORE)
    {
        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
    }

    /* perform operation on active layer */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_KEYSTORE_SW
    case PH_KEYSTORE_SW_ID:
        status = phKeyStore_Sw_GetKUC((phKeyStore_Sw_DataParams_t *)pDataParams, wRefNoKUC, pdwLimit, pdwCurVal);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_SW */

#ifdef NXPBUILD__PH_KEYSTORE_RC632
    case PH_KEYSTORE_RC632_ID:
        status = phKeyStore_Rc632_GetKUC((phKeyStore_Rc632_DataParams_t *)pDataParams, wRefNoKUC, pdwLimit, pdwCurVal);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC632 */

#ifdef NXPBUILD__PH_KEYSTORE_RC663
    case PH_KEYSTORE_RC663_ID:
        status = phKeyStore_Rc663_GetKUC((phKeyStore_Rc663_DataParams_t *)pDataParams, wRefNoKUC, pdwLimit, pdwCurVal);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RC663 */

#ifdef NXPBUILD__PH_KEYSTORE_RD710
    case PH_KEYSTORE_RD710_ID:
        status = phKeyStore_Rd710_GetKUC((phKeyStore_Rd710_DataParams_t *)pDataParams, wRefNoKUC, pdwLimit, pdwCurVal);
        break;
#endif /* NXPBUILD__PH_KEYSTORE_RD710 */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_KEYSTORE);
        break;
    }
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
#ifdef NXPBUILD__PH_LOG
    if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
    {
        PH_LOG_HELPER_ADDPARAM_UINT32(PH_LOG_LOGTYPE_DEBUG, pdwLimit_log, pdwLimit);
        PH_LOG_HELPER_ADDPARAM_UINT32(PH_LOG_LOGTYPE_DEBUG, pdwCurVal_log, pdwCurVal);
    }
#endif
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}

uint16_t phKeyStore_GetKeySize(uint16_t wKeyType)
{
    switch (wKeyType)
    {
        case PH_KEYSTORE_KEY_TYPE_MIFARE:
            /* 6 bytes for key A + 6 bytes for key B */
            return 12;

        case PH_KEYSTORE_KEY_TYPE_DES:
            return 8;

        case PH_KEYSTORE_KEY_TYPE_2K3DES:
        case PH_KEYSTORE_KEY_TYPE_AES128:
            return 16;

        case PH_KEYSTORE_KEY_TYPE_3K3DES:
        case PH_KEYSTORE_KEY_TYPE_AES192:
            return 24;

        case PH_KEYSTORE_KEY_TYPE_AES256:
            return 32;

        default:
            return 0;
    }
}

#endif /* NXPBUILD__PH_KEYSTORE */
