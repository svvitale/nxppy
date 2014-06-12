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
* RD700 specific HAL-Component of Reader Library Framework.
* $Author: jayaprakash.desai $
* $Revision: 1.5 $
* $Date: Wed May  4 16:01:03 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/
#include <ph_Status.h>
#include <phbalReg.h>
#include <phhalHw.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHHAL_HW_RD70X

#include "phhalHw_Rd70x.h"
#include "phhalHw_Rd70x_Int.h"
#include <phhalHw_Rd70x_Cmd.h>

phStatus_t phhalHw_Rd70x_Cmd_PcdConfig(phhalHw_Rd70x_DataParams_t * pDataParams)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PcdConfig);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_MfPiccRequest(phhalHw_Rd70x_DataParams_t * pDataParams,
                                           uint8_t req_code,
                                           uint8_t *atq)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccRequest);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, req_code);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, 2, atq);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PiccCommonRequest(phhalHw_Rd70x_DataParams_t * pDataParams,
                                               uint8_t req_code,
                                               uint8_t *atq)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccCommonRequest);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, req_code);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, 2, atq);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_MfPiccAnticoll (phhalHw_Rd70x_DataParams_t * pDataParams,
                                             uint8_t bcnt,
                                             uint8_t *snr)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccAnticoll);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bcnt);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, snr,4);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, 4, snr);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PiccCascAnticoll (phhalHw_Rd70x_DataParams_t * pDataParams,
                                               uint8_t select_code,
                                               uint8_t bcnt,
                                               uint8_t *snr)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccCascAnticoll);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, select_code);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bcnt);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, snr,4);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, 4, snr);
        }
    }
    return status;  
}

phStatus_t phhalHw_Rd70x_Cmd_MfPiccSelect(phhalHw_Rd70x_DataParams_t * pDataParams,
                                          uint8_t *snr,
                                          uint8_t *sak)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccSelect);    
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, snr,4);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            phhalHw_Rd70x_GetParam_Uint8(pDataParams, sak);
        }
    }
    return status;  
}

phStatus_t phhalHw_Rd70x_Cmd_PiccCascSelect(phhalHw_Rd70x_DataParams_t * pDataParams,
                                            uint8_t select_code,
                                            uint8_t *snr, /* full qualified 4 bytes serial number */
                                            uint8_t *sak) /* select aknowledge*/
{
    phStatus_t PH_MEMLOC_REM status; 


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccCascSelect);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, select_code);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, snr,4);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            phhalHw_Rd70x_GetParam_Uint8(pDataParams, sak);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_MfPiccAuth(phhalHw_Rd70x_DataParams_t * pDataParams,
                                        uint8_t keyAB,
                                        uint8_t key_addr,
                                        uint8_t block)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccAuth);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, keyAB);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, key_addr);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, block);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        /* Map protocol errors to AUTH_ERROR */
        if (((status & PH_ERR_MASK) == PH_ERR_PROTOCOL_ERROR) ||
            ((status & PH_ERR_MASK) == PH_ERR_INTEGRITY_ERROR))
        {
            status = PH_ADD_COMPCODE(PH_ERR_AUTH_ERROR, PH_COMP_HAL);
        }

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_MfPiccAuthE2(phhalHw_Rd70x_DataParams_t * pDataParams,
                                          uint8_t auth_mode,
                                          uint8_t *snr,
                                          uint8_t key_sector,
                                          uint8_t block)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccAuthE2);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, auth_mode);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, snr,4); 
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, key_sector);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, block);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        /* Map protocol errors to AUTH_ERROR */
        if (((status & PH_ERR_MASK) == PH_ERR_PROTOCOL_ERROR) ||
            ((status & PH_ERR_MASK) == PH_ERR_INTEGRITY_ERROR))
        {
            status = PH_ADD_COMPCODE(PH_ERR_AUTH_ERROR, PH_COMP_HAL);
        }

    }
    return status;
}                        

phStatus_t phhalHw_Rd70x_Cmd_HostCodeKey(phhalHw_Rd70x_DataParams_t * pDataParams,
                                         uint8_t *uncoded,
                                         uint8_t *coded)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_HostCodeKey);    
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uncoded,6);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, 12, coded);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PcdLoadKeyE2(phhalHw_Rd70x_DataParams_t * pDataParams,
                                          uint8_t auth_mode,
                                          uint8_t key_sector,
                                          uint8_t *keys)
{
    phStatus_t PH_MEMLOC_REM status;


	if(((auth_mode != 0x60) && (auth_mode != 0x61)) || (key_sector >= 0x1F))
	{
		return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
	}
    phhalHw_Rd70x_SetCommand(pDataParams, uC_PcdLoadKeyE2);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, auth_mode);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, key_sector);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, keys,6);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_MfPiccAuthKey(phhalHw_Rd70x_DataParams_t * pDataParams,
                                           uint8_t auth_mode,
                                           uint8_t *snr,
                                           uint8_t *keys,
                                           uint8_t block)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccAuthKey);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, auth_mode);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, snr,4);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, keys,12);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, block);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        /* Map protocol errors to AUTH_ERROR */
        if (((status & PH_ERR_MASK) == PH_ERR_PROTOCOL_ERROR) ||
            ((status & PH_ERR_MASK) == PH_ERR_INTEGRITY_ERROR))
        {
            status = PH_ADD_COMPCODE(PH_ERR_AUTH_ERROR, PH_COMP_HAL);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_MfPiccRead(phhalHw_Rd70x_DataParams_t * pDataParams,
                                        uint8_t addr,
                                        uint8_t* data)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccRead);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, addr);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, 16, data);
        }
    }
    return status; 
}

phStatus_t phhalHw_Rd70x_Cmd_PiccCommonRead(phhalHw_Rd70x_DataParams_t * pDataParams,
                                            uint8_t cmd,
                                            uint8_t addr,
                                            uint8_t datalen,
                                            uint8_t* data)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccCommonRead);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, cmd);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, addr);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, datalen);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, datalen, data);
        }
    }
    return status; 
}

phStatus_t phhalHw_Rd70x_Cmd_MfPiccWrite(phhalHw_Rd70x_DataParams_t * pDataParams,
                                         uint8_t addr,
                                         uint8_t *data)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccWrite);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, addr);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, data,16);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PiccWrite4(phhalHw_Rd70x_DataParams_t * pDataParams,
                                        uint8_t addr,
                                        uint8_t *data)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccWrite4);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, addr);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, data,4);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PiccCommonWrite(phhalHw_Rd70x_DataParams_t * pDataParams,
                                             uint8_t cmd,
                                             uint8_t addr,
                                             uint8_t datalen,
                                             uint8_t *data)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccCommonWrite);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, cmd);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, addr);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, datalen);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, data,datalen);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_MfPiccValue(phhalHw_Rd70x_DataParams_t * pDataParams,
                                         uint8_t dd_mode,
                                         uint8_t addr,
                                         uint8_t *value,
                                         uint8_t trans_addr)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccValue);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, dd_mode);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, addr);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, value,4);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, trans_addr);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_MfPiccValueDebit(phhalHw_Rd70x_DataParams_t * pDataParams,
                                              uint8_t dd_mode,
                                              uint8_t addr,
                                              uint8_t *value)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccValueDebit);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, dd_mode);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, addr);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, value,4);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_MfPiccHalt(phhalHw_Rd70x_DataParams_t * pDataParams)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccHalt);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status; 
}

phStatus_t phhalHw_Rd70x_Cmd_PiccActivation(
    phhalHw_Rd70x_DataParams_t * pDataParams,
    uint8_t ctrl_flag,
    uint8_t req_code,
    uint8_t *br,
    uint8_t *atq, 
    uint8_t *sak, 
    uint8_t *uid, 
    uint8_t *uid_len,
    uint8_t *script,
    uint16_t script_len,
    uint8_t *resp,
    uint16_t *resp_len,
    uint8_t sec)

{
    phStatus_t PH_MEMLOC_REM status;

    uint16_t tmp_resp_len;
    uint8_t uid_tmp[10];

    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccActivation);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, *br);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, ctrl_flag);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, req_code);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, sec);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, *uid_len);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid,10);       /* always full length of 10 bytes ( 3 cascade levels)*/
    phhalHw_Rd70x_AddParam_Uint16(pDataParams, script_len);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, script,script_len);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            phhalHw_Rd70x_GetParam_Uint8(pDataParams, br);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, 2, atq);
            phhalHw_Rd70x_GetParam_Uint8(pDataParams, sak);
            phhalHw_Rd70x_GetParam_Uint8(pDataParams, uid_len);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, 10, uid_tmp); /* always all 10 bytes (3 cascade levels)*/
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, &tmp_resp_len);

            /* check, if there is enough space reserved for the received data*/
            if (tmp_resp_len <= *resp_len)
            {
                *resp_len = tmp_resp_len;
            }
            else
            {
                /* and return an error*/
                status = PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
            }

            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resp_len, resp);

            /*the USB pegoda may report 0xFC as uid_len*/
            if ( *uid_len > 10 )
                *uid_len = 10;
            memcpy(uid,uid_tmp,*uid_len); /* PRQA S 3200 */
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PiccActivateIdle(phhalHw_Rd70x_DataParams_t * pDataParams,
                                              uint8_t br,
                                              uint8_t *atq, 
                                              uint8_t *sak, 
                                              uint8_t *uid, 
                                              uint8_t *uid_len)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccActivateIdle);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, br);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, 2, atq);
            phhalHw_Rd70x_GetParam_Uint8(pDataParams, sak);
            phhalHw_Rd70x_GetParam_Uint8(pDataParams, uid_len);

            /*the USB pegoda may report 0xFC as uid_len*/
            if ( *uid_len > 10 )
                *uid_len = 10;
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *uid_len, uid);
        }
    }
    return status;
}


phStatus_t phhalHw_Rd70x_Cmd_PiccActivateIdleLoop(phhalHw_Rd70x_DataParams_t * pDataParams,
                                                  uint8_t br,
                                                  uint8_t *atq, 
                                                  uint8_t *sak, 
                                                  uint8_t *uid, 
                                                  uint8_t *uid_len,
                                                  uint8_t sec)
{
    phStatus_t PH_MEMLOC_REM status;

    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccActivateIdleLoop);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, br);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, sec);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, 2, atq);
            phhalHw_Rd70x_GetParam_Uint8(pDataParams, sak);
            phhalHw_Rd70x_GetParam_Uint8(pDataParams, uid_len);

            /*the USB pegoda may report 0xFC as uid_len*/
            if ( *uid_len > 10 )
                *uid_len = 10;
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *uid_len, uid);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PiccActivateWakeup(phhalHw_Rd70x_DataParams_t * pDataParams,
                                                uint8_t br,
                                                uint8_t *atq, 
                                                uint8_t *sak, 
                                                uint8_t *uid, 
                                                uint8_t uid_len)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccActivateWakeup);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, br);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, uid_len);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid,uid_len);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, 2, atq);
            phhalHw_Rd70x_GetParam_Uint8(pDataParams, sak);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PiccExchangeBlock(
    phhalHw_Rd70x_DataParams_t * pDataParams,
    uint8_t * send_buffer,
    uint16_t  send_bytelen,
    uint8_t ** rec_data,
    uint16_t * rec_bytelen,
    uint8_t  append_crc,
    uint32_t  timeout)
{
    phStatus_t  PH_MEMLOC_REM status;
    uint16_t    PH_MEMLOC_REM wPosition;

    /* Build command*/
    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccExchangeBlock);    
    phhalHw_Rd70x_AddParam_Uint16(pDataParams, send_bytelen);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, append_crc);
    phhalHw_Rd70x_AddParam_Uint32(pDataParams, timeout);

    /* Copy sendbuffer if neccessary */
    if (send_buffer != NULL)
    {
        /* Calculate start position */
        wPosition = PHHAL_HW_RD70X_RESERVED_BUFFER_LEN + pDataParams->wTxBufStartPos + pDataParams->wTxBufLen;

        /* Buffer overflow check */
        if ((wPosition + send_bytelen) > pDataParams->wTxBufSize)
        {
            pDataParams->wTxBufLen = 0;
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* Copy transmit buffer*/
        memcpy(&pDataParams->pTxBuffer[wPosition], send_buffer, send_bytelen);  /* PRQA S 3200 */
        pDataParams->wTxBufLen = pDataParams->wTxBufLen + send_bytelen;
    }

    /* reset received length */
    *rec_bytelen = 0;

    /* execute the command*/
    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        /* Fetch the values only, if the status is in the Range of -128 to 0*/
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            /* Retrieve number of received bytes*/
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, rec_bytelen);

            /* Retrieve received data */
            phhalHw_Rd70x_GetParam_BufferPointer(pDataParams, rec_data);
        }
    }

    /* Reset our transmit buffer contents */
    if (send_buffer != NULL)
    {
        pDataParams->wTxBufLen = pDataParams->wTxBufLen - send_bytelen;
    }

    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PiccExchangeBlockRfCycle(
    phhalHw_Rd70x_DataParams_t * pDataParams,
    uint8_t * send_buffer,
    uint16_t  send_bytelen,
    uint8_t ** rec_data,
    uint16_t * rec_bytelen,
    uint8_t  append_crc,
    uint32_t  timeout)
{
    phStatus_t  PH_MEMLOC_REM status;
    uint16_t    PH_MEMLOC_REM wPosition;

    /* Build command*/
    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccExchangeBlockRfCycle);    
    phhalHw_Rd70x_AddParam_Uint16(pDataParams, send_bytelen);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, append_crc);
    phhalHw_Rd70x_AddParam_Uint32(pDataParams, timeout);

    /* Copy sendbuffer if neccessary */
    if (send_buffer != NULL)
    {
        /* Calculate start position */
        wPosition = PHHAL_HW_RD70X_RESERVED_BUFFER_LEN + pDataParams->wTxBufStartPos + pDataParams->wTxBufLen;

        /* Buffer overflow check */
        if ((wPosition + send_bytelen) > pDataParams->wTxBufSize)
        {
            pDataParams->wTxBufLen = 0;
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* Copy transmit buffer*/
        memcpy(&pDataParams->pTxBuffer[wPosition], send_buffer, send_bytelen);  /* PRQA S 3200 */
        pDataParams->wTxBufLen = pDataParams->wTxBufLen + send_bytelen;
    }

    /* reset received length */
    *rec_bytelen = 0;

    /* execute the command*/
    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        /* Fetch the values only, if the status is in the Range of -128 to 0*/
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            /* Retrieve number of received bytes*/
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, rec_bytelen);

            /* Retrieve received data */
            phhalHw_Rd70x_GetParam_BufferPointer(pDataParams, rec_data);
        }
    }

    /* Reset our transmit buffer contents */
    if (send_buffer != NULL)
    {
        pDataParams->wTxBufLen = pDataParams->wTxBufLen - send_bytelen;
    }

    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PiccExchgBitByte(
    phhalHw_Rd70x_DataParams_t * pDataParams,
    uint8_t * send_buffer,
    uint16_t send_bytelen,
    uint8_t send_validbits,
    uint8_t ** rec_data,
    uint16_t * rec_bytelen,
    uint8_t * rec_validbits,
    uint8_t flags,
    uint32_t timeout)
{
    phStatus_t  PH_MEMLOC_REM status;
    uint16_t    PH_MEMLOC_REM wPosition;

    /* Build command*/
    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccExchangeBitByte);    
    phhalHw_Rd70x_AddParam_Uint16(pDataParams, send_bytelen);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, send_validbits);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Uint32(pDataParams, timeout);

    /* Copy sendbuffer if neccessary */
    if (send_buffer != NULL)
    {
        /* Calculate start position */
        wPosition = PHHAL_HW_RD70X_RESERVED_BUFFER_LEN + pDataParams->wTxBufStartPos + pDataParams->wTxBufLen;

        /* Buffer overflow check */
        if ((wPosition + send_bytelen) > pDataParams->wTxBufSize)
        {
            pDataParams->wTxBufLen = 0;
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* Copy transmit buffer*/
        memcpy(&pDataParams->pTxBuffer[wPosition], send_buffer, send_bytelen);  /* PRQA S 3200 */
        pDataParams->wTxBufLen = pDataParams->wTxBufLen + send_bytelen;
    }

    /* reset received length */
    *rec_bytelen = 0;

    /* execute the command*/
    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        /* Fetch the values only, if the status is in the Range of -128 to 0*/
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            /* Retrieve number of received bytes*/
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, rec_bytelen);

            /* Retrieve number of received bits*/
            phhalHw_Rd70x_GetParam_Uint8(pDataParams, rec_validbits);

            /* Retrieve received data */
            phhalHw_Rd70x_GetParam_BufferPointer(pDataParams, rec_data);
        }
    }

    /* Reset our transmit buffer contents */
    if (send_buffer != NULL)
    {
        pDataParams->wTxBufLen = pDataParams->wTxBufLen - send_bytelen;
    }

    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PiccExchgBitByteRfCycle(
    phhalHw_Rd70x_DataParams_t * pDataParams,
    uint8_t * send_buffer,
    uint16_t send_bytelen,
    uint8_t send_validbits,
    uint8_t ** rec_data,
    uint16_t * rec_bytelen,
    uint8_t * rec_validbits,
    uint8_t flags,
    uint32_t timeout)
{
    phStatus_t  PH_MEMLOC_REM status;
    uint16_t    PH_MEMLOC_REM wPosition;

    /* Build command*/
    phhalHw_Rd70x_SetCommand(pDataParams, uC_PiccExchangeBitByteRfCycle);    
    phhalHw_Rd70x_AddParam_Uint16(pDataParams, send_bytelen);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, send_validbits);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Uint32(pDataParams, timeout);

    /* Copy sendbuffer if neccessary */
    if (send_buffer != NULL)
    {
        /* Calculate start position */
        wPosition = PHHAL_HW_RD70X_RESERVED_BUFFER_LEN + pDataParams->wTxBufStartPos + pDataParams->wTxBufLen;

        /* Buffer overflow check */
        if ((wPosition + send_bytelen) > pDataParams->wTxBufSize)
        {
            pDataParams->wTxBufLen = 0;
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* Copy transmit buffer*/
        memcpy(&pDataParams->pTxBuffer[wPosition], send_buffer, send_bytelen);  /* PRQA S 3200 */
        pDataParams->wTxBufLen = pDataParams->wTxBufLen + send_bytelen;
    }

    /* reset received length */
    *rec_bytelen = 0;

    /* execute the command*/
    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        /* Fetch the values only, if the status is in the Range of -128 to 0 */
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            /* Retrieve number of received bytes */
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, rec_bytelen);

            /* Retrieve number of received bits */
            phhalHw_Rd70x_GetParam_Uint8(pDataParams, rec_validbits);

            /* Retrieve received data */
            phhalHw_Rd70x_GetParam_BufferPointer(pDataParams, rec_data);
        }
    }

    /* Reset our transmit buffer contents */
    if (send_buffer != NULL)
    {
        pDataParams->wTxBufLen = pDataParams->wTxBufLen - send_bytelen;
    }

    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PcdGetAttrib(phhalHw_Rd70x_DataParams_t * pDataParams,
                                          uint8_t *FSCImax,
                                          uint8_t *FSDImax,
                                          uint8_t *DSsupp,
                                          uint8_t *DRsupp,
                                          uint8_t *DREQDS)
{
    phStatus_t PH_MEMLOC_REM status;
    phhalHw_Rd70x_SetCommand(pDataParams, uC_PcdGetAttrib);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint8(pDataParams, FSCImax);
            phhalHw_Rd70x_GetParam_Uint8(pDataParams, FSDImax);
            phhalHw_Rd70x_GetParam_Uint8(pDataParams, DSsupp);
            phhalHw_Rd70x_GetParam_Uint8(pDataParams, DRsupp);
            phhalHw_Rd70x_GetParam_Uint8(pDataParams, DREQDS);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PcdSetAttrib(phhalHw_Rd70x_DataParams_t * pDataParams,
                                          uint8_t DSI,
                                          uint8_t DRI)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PcdSetAttrib);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, DSI);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, DRI);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PcdEnableHighBaudRates(phhalHw_Rd70x_DataParams_t * pDataParams,
                                                    uint8_t *cryptogram)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PcdEnableHighBaudRates);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, cryptogram, 4);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PcdSetDefaultAttrib(phhalHw_Rd70x_DataParams_t * pDataParams)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PcdSetDefaultAttrib);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_I1PcdConfig(phhalHw_Rd70x_DataParams_t * pDataParams)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_I1PcdConfig);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PcdSetTmo(phhalHw_Rd70x_DataParams_t * pDataParams,
                                       uint32_t tmoLength)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PcdSetTmo);
    phhalHw_Rd70x_AddParam_Uint32(pDataParams, tmoLength);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PcdReset(phhalHw_Rd70x_DataParams_t * pDataParams)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PcdReset);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PcdRfReset(
                                        phhalHw_Rd70x_DataParams_t * pDataParams,
                                        uint16_t ms
                                        )
{
    phStatus_t PH_MEMLOC_REM status;

    phhalHw_Rd70x_SetCommand(pDataParams, uC_PcdRfReset);    
    phhalHw_Rd70x_AddParam_Uint16(pDataParams, ms);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_HostTransTmrStart(
    phhalHw_Rd70x_DataParams_t * pDataParams
    )
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_HostTransTmrStart);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_HostTransTmrStop(phhalHw_Rd70x_DataParams_t * pDataParams,
                                              uint32_t *us)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_HostTransTmrStop);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint32(pDataParams, us);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_HostTransTmrSetCMDCount(phhalHw_Rd70x_DataParams_t * pDataParams,
                                                     uint16_t lvtime)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_HostTransTmrSteps);
    phhalHw_Rd70x_AddParam_Uint16(pDataParams, lvtime);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_HostGetExecutionTime(phhalHw_Rd70x_DataParams_t * pDataParams,
                                                  uint32_t *us)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_HostGetExecutionTime);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint32(pDataParams, us);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_WriteRC(phhalHw_Rd70x_DataParams_t * pDataParams,
                                     uint8_t addr,
                                     uint8_t value)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_Write);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, addr);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, value);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ReadRC(phhalHw_Rd70x_DataParams_t * pDataParams,
                                    uint8_t addr,
                                    uint8_t *value)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_Read);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, addr);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint8(pDataParams, value);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_WriteMultiple(phhalHw_Rd70x_DataParams_t * pDataParams,
                                           uint8_t *addr_value,
                                           uint16_t len)
{
    phStatus_t PH_MEMLOC_REM status;

    phhalHw_Rd70x_SetCommand(pDataParams, uC_WriteMultiple);
    phhalHw_Rd70x_AddParam_Uint16(pDataParams, len);

    /* Copy address/value buffer into transmit buffer */
    memcpy(&pDataParams->pTxBuffer[PHHAL_HW_RD70X_RESERVED_BUFFER_LEN-1], addr_value, len * 2);  /* PRQA S 3200 */
    pDataParams->wTxBufLen = len * 2;

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ReadMultiple(phhalHw_Rd70x_DataParams_t * pDataParams,
                                          uint8_t * addr_value,
                                          uint16_t len)
{
    phStatus_t  PH_MEMLOC_REM status;
    uint8_t *   PH_MEMLOC_REM pRxContents;

    phhalHw_Rd70x_SetCommand(pDataParams, uC_ReadMultiple);    
    phhalHw_Rd70x_AddParam_Uint16(pDataParams, len);
  
    /* Copy address/value buffer into transmit buffer */
    memcpy(&pDataParams->pTxBuffer[PHHAL_HW_RD70X_RESERVED_BUFFER_LEN-1], addr_value, len * 2);  /* PRQA S 3200 */
    pDataParams->wTxBufLen = len * 2;

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            /* Retrieve received contents */
            phhalHw_Rd70x_GetParam_BufferPointer(pDataParams, &pRxContents);
            memcpy(addr_value, pRxContents, len * 2);  /* PRQA S 3200 */
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PcdReadE2(phhalHw_Rd70x_DataParams_t * pDataParams,
                                       uint16_t startaddr,  
                                       uint8_t length,
                                       uint8_t* data)
{
    phStatus_t PH_MEMLOC_REM status;
	/* Parameter check */
	if (length > PHHAL_HW_RD70X_VALUE_FIFOSIZE)
	{
		return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
	}

	/* 0 means 64, do this for the check below */
	if (length == 0)
	{
		length = PHHAL_HW_RD70X_VALUE_FIFOSIZE;
	}

	/* Check Address range */
	if ((startaddr + length) > PHHAL_HW_RD70X_EEPROM_SIZE)
	{
		return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
	}
    phhalHw_Rd70x_SetCommand(pDataParams, uC_PcdReadE2);    
    phhalHw_Rd70x_AddParam_Uint16(pDataParams, startaddr);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, length);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, length, data);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PcdWriteE2(phhalHw_Rd70x_DataParams_t * pDataParams,
                                        uint16_t startaddr,  
                                        uint8_t length,
                                        uint8_t* data)
{
    phStatus_t PH_MEMLOC_REM status;

	/* Check Address range and data length */
	if ((startaddr >= (PHHAL_HW_RD70X_EEPROM_SIZE/PHHAL_HW_RD70X_EEPROM_PAGE_SIZE)) 
		|| (length == 0) || (length > PHHAL_HW_RD70X_EEPROM_PAGE_SIZE))
	{
		return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
	}

    phhalHw_Rd70x_SetCommand(pDataParams, uC_PcdWriteE2);    
    phhalHw_Rd70x_AddParam_Uint16(pDataParams, startaddr);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, length);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, data,length);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PcdSetIdleMode(phhalHw_Rd70x_DataParams_t * pDataParams)
{
    phStatus_t PH_MEMLOC_REM status;

    phhalHw_Rd70x_SetCommand(pDataParams, uC_PcdSetIdleMode);    

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PcdClearIdleMode(phhalHw_Rd70x_DataParams_t * pDataParams)
{
    phStatus_t PH_MEMLOC_REM status;

    phhalHw_Rd70x_SetCommand(pDataParams, uC_PcdClearIdleMode);    

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PcdGetFwVersion(phhalHw_Rd70x_DataParams_t * pDataParams,
                                             uint8_t* version,
                                             uint16_t* versionLen)
{
    phStatus_t PH_MEMLOC_REM status;

    phhalHw_Rd70x_SetCommand(pDataParams, uC_PcdGetFwVersion);    

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, versionLen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *versionLen, version);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PcdGetRicVersion(phhalHw_Rd70x_DataParams_t * pDataParams,
                                              uint8_t* version)
{
    phStatus_t PH_MEMLOC_REM status;

    phhalHw_Rd70x_SetCommand(pDataParams, uC_PcdGetRicVersion);    

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, 5, version);
        }
    }
    return status;
}


phStatus_t phhalHw_Rd70x_Cmd_PcdInitializeE2(phhalHw_Rd70x_DataParams_t * pDataParams)
{
    phStatus_t PH_MEMLOC_REM status;

    phhalHw_Rd70x_SetCommand(pDataParams, uC_PcdInitializeE2);    
    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ReadWord(phhalHw_Rd70x_DataParams_t * pDataParams,
                                      uint32_t address,
                                      uint16_t* value)
{
    phStatus_t PH_MEMLOC_REM status;

    phhalHw_Rd70x_SetCommand(pDataParams, uC_ReadWord);    
    phhalHw_Rd70x_AddParam_Uint32(pDataParams, address);
    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, value);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_PcdGetSnr(phhalHw_Rd70x_DataParams_t * pDataParams,
                                       uint8_t *snr)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_PcdGetSnr);    
    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, 4, snr);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_SwitchLED(phhalHw_Rd70x_DataParams_t * pDataParams,
                                       uint8_t onoff)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_SwitchLED);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, onoff);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_DbgTrigger(phhalHw_Rd70x_DataParams_t * pDataParams,
                                        uint8_t enableTrigger)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_DbgTrigger);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, enableTrigger);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_I1PcdRfReset(phhalHw_Rd70x_DataParams_t * pDataParams,
                                          uint16_t ms)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_I1PcdRfReset);    
    phhalHw_Rd70x_AddParam_Uint16(pDataParams, ms);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_I2init_StdMode_15693(phhalHw_Rd70x_DataParams_t * pDataParams)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_init_StdMode_15693);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_I2init_FastMode_15693(phhalHw_Rd70x_DataParams_t * pDataParams)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_init_FastMode_15693);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}


phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Read_Sm(phhalHw_Rd70x_DataParams_t * pDataParams,
                                              uint8_t flags, 
                                              uint8_t *uid, 
                                              uint8_t blnr, 
                                              uint8_t nbl, 
                                              uint16_t *resplen, 
                                              uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Read_sm);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid, 8);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, blnr);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, nbl);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Inventory(phhalHw_Rd70x_DataParams_t * pDataParams,
                                                uint8_t flags, 
                                                uint8_t AFI, 
                                                uint8_t masklengh, 
                                                uint8_t *uid, 
                                                uint16_t *resplen, 
                                                uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uc_ISO15693_Inventory);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, AFI);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, masklengh);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid, 8);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}
phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Write_Sm(phhalHw_Rd70x_DataParams_t * pDataParams,
                                               uint8_t flags, 
                                               uint8_t *uid, 
                                               uint8_t blnr,
                                               uint8_t nbl, 
                                               uint8_t *data,                         
                                               uint16_t *resplen, 
                                               uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Write_sm);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid, 8);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, blnr);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, nbl);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, data, nbl*4);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Stay_Quiet(phhalHw_Rd70x_DataParams_t * pDataParams,
                                                 uint8_t flags, 
                                                 uint8_t *uid, 
                                                 uint16_t *resplen, 
                                                 uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams,  uC_ISO15693_Stay_Quiet);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid, 8);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Lock_Block(phhalHw_Rd70x_DataParams_t * pDataParams,
                                                 uint8_t flags, 
                                                 uint8_t *uid, 
                                                 uint8_t blnr,
                                                 uint16_t *resplen, 
                                                 uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Lock_Block);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid, 8);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, blnr);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Select(phhalHw_Rd70x_DataParams_t * pDataParams,
                                             uint8_t flags, 
                                             uint8_t *uid, 
                                             uint16_t *resplen, 
                                             uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Select);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid, 8);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Reset_To_Ready(phhalHw_Rd70x_DataParams_t * pDataParams,
                                                     uint8_t flags, 
                                                     uint8_t *uid, 
                                                     uint16_t *resplen, 
                                                     uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Reset_To_Ready);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid, 8);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Write_AFI(phhalHw_Rd70x_DataParams_t * pDataParams,
                                                uint8_t flags, 
                                                uint8_t *uid, 
                                                uint8_t AFI,
                                                uint16_t *resplen, 
                                                uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Write_AFI);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid, 8);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, AFI);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Lock_AFI(phhalHw_Rd70x_DataParams_t * pDataParams,
                                               uint8_t flags, 
                                               uint8_t *uid, 
                                               uint16_t *resplen, 
                                               uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Lock_AFI);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid, 8);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Write_DSFID(phhalHw_Rd70x_DataParams_t * pDataParams,
                                                  uint8_t flags, 
                                                  uint8_t *uid, 
                                                  uint8_t DSFID,
                                                  uint16_t *resplen, 
                                                  uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Write_DSFID);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid, 8);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, DSFID);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Lock_DSFID(phhalHw_Rd70x_DataParams_t * pDataParams,
                                                 uint8_t flags, 
                                                 uint8_t *uid, 
                                                 uint16_t *resplen, 
                                                 uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Lock_DSFID);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid, 8);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Get_System_Information(phhalHw_Rd70x_DataParams_t * pDataParams,
                                                             uint8_t flags, 
                                                             uint8_t *uid, 
                                                             uint16_t *resplen, 
                                                             uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Get_System_Information);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid, 8);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Get_Multiple_Block_Security(phhalHw_Rd70x_DataParams_t * pDataParams,
                                                                  uint8_t flags, 
                                                                  uint8_t *uid, 
                                                                  uint8_t blnr,
                                                                  uint8_t nbl, 
                                                                  uint16_t *resplen, 
                                                                  uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Get_Multiple_Block_Security);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid, 8);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, blnr);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, nbl);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Inventory_Read(phhalHw_Rd70x_DataParams_t * pDataParams,
                                                     uint8_t flags, 
                                                     uint8_t ManCode, 
                                                     uint8_t AFI, 
                                                     uint8_t masklengh, 
                                                     uint8_t *uid, 
                                                     uint8_t blnr, 
                                                     uint8_t nbl, 
                                                     uint16_t *resplen, 
                                                     uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Inventory_Read);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, ManCode);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, AFI);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, masklengh);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid, 8);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, blnr);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, nbl);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Fast_Inventory_Read(phhalHw_Rd70x_DataParams_t * pDataParams,
                                                          uint8_t flags, 
                                                          uint8_t ManCode, 
                                                          uint8_t AFI, 
                                                          uint8_t masklengh, 
                                                          uint8_t *uid, 
                                                          uint8_t blnr, 
                                                          uint8_t nbl, 
                                                          uint16_t *resplen, 
                                                          uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Fast_Inventory_Read);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, ManCode);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, AFI);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, masklengh);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid, 8);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, blnr);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, nbl);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Set_Eas(phhalHw_Rd70x_DataParams_t * pDataParams,
                                              uint8_t flags, 
                                              uint8_t ManCode, 
                                              uint8_t *uid, 
                                              uint16_t *resplen, 
                                              uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Set_Eas);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, ManCode);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid, 8);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}


phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Reset_Eas(phhalHw_Rd70x_DataParams_t * pDataParams,
                                                uint8_t flags, 
                                                uint8_t ManCode, 
                                                uint8_t *uid, 
                                                uint16_t *resplen, 
                                                uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Reset_Eas);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, ManCode);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid, 8);


    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Lock_Eas(phhalHw_Rd70x_DataParams_t * pDataParams,
                                               uint8_t flags, 
                                               uint8_t ManCode, 
                                               uint8_t *uid, 
                                               uint16_t *resplen, 
                                               uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Lock_Eas);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, ManCode);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid, 8);


    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Eas_Alarm(phhalHw_Rd70x_DataParams_t * pDataParams,
                                                uint8_t flags, 
                                                uint8_t ManCode, 
                                                uint8_t *uid, 
                                                uint8_t  bEAS_ID_MaskLength,
                                                uint8_t  *pbEAS_ID,
                                                uint16_t *resplen, 
                                                uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Eas_Alarm);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, flags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, ManCode);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, uid, 8);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bEAS_ID_MaskLength);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, pbEAS_ID, 2);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}



phStatus_t phhalHw_Rd70x_Cmd_EPCPcdConfig(phhalHw_Rd70x_DataParams_t * pDataParams)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_EPC_PcdConfig);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_EPCBeginRound(phhalHw_Rd70x_DataParams_t * pDataParams,
                                           uint8_t *mask,
                                           uint8_t masklength,
                                           uint8_t nbrslots,
                                           uint8_t hash,
                                           uint16_t *resplen,
                                           uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_EPC_BeginRound);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, nbrslots);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, hash);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, masklength);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, mask, masklength);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_EPCWrite(phhalHw_Rd70x_DataParams_t * pDataParams,
                                      uint8_t blnr,
                                      uint8_t data)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_EPC_Write);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, blnr);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, data);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_EPCDestroy(phhalHw_Rd70x_DataParams_t * pDataParams,
                                        uint8_t *epc,
                                        uint8_t *destroy_code)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_EPC_Destroy);    
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, epc, 12);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, destroy_code, 3);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}


phStatus_t phhalHw_Rd70x_Cmd_UIDPcdConfig(phhalHw_Rd70x_DataParams_t * pDataParams)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_UID_PcdConfig);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_UIDBeginRound(phhalHw_Rd70x_DataParams_t * pDataParams,
                                           uint8_t *mask,
                                           uint8_t masklength,
                                           uint8_t nbrslots,
                                           uint16_t *resplen,
                                           uint8_t *resp)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_UID_BeginRound);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, nbrslots);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, masklength);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, mask, masklength);
    /* AR: FIX ME BEGIN */
    /* Increased Timeout by factor of four to avoid ICODE timing problems */
    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
        /* AR: FIX ME END */
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, resplen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *resplen, resp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_UIDWrite(phhalHw_Rd70x_DataParams_t * pDataParams,
                                      uint8_t blnr,
                                      uint8_t data)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_UID_Write);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, blnr);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, data);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_UIDDestroy(phhalHw_Rd70x_DataParams_t * pDataParams,
                                        uint8_t *idd,
                                        uint8_t *destroy_code)
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_UID_Destroy);    
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, idd, 19);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, destroy_code, 3);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_PwdProtectEAS( phhalHw_Rd70x_DataParams_t * pDataParams,
                                                    uint8_t  bFlags, 
                                                    uint8_t  bManCode, 
                                                    uint8_t  *pbUID,
                                                    uint16_t *pwRespLen, 
                                                    uint8_t  *pbResp )
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Pwd_Protect_EAS);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bFlags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bManCode);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, pbUID, 8);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, pwRespLen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *pwRespLen, pbResp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_WriteEAS_ID( phhalHw_Rd70x_DataParams_t * pDataParams,
                                                  uint8_t  bFlags, 
                                                  uint8_t  bManCode, 
                                                  uint8_t  *pbUID,
                                                  uint16_t wEAS_ID,
                                                  uint16_t *pwRespLen, 
                                                  uint8_t  *pbResp )
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Write_EAS_ID);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bFlags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bManCode);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, pbUID, 8);
    phhalHw_Rd70x_AddParam_Uint16(pDataParams, wEAS_ID);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, pwRespLen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *pwRespLen, pbResp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_ReadEPC( phhalHw_Rd70x_DataParams_t * pDataParams,
                                              uint8_t  bFlags, 
                                              uint8_t  bManCode, 
                                              uint8_t  *pbUID,
                                              uint16_t *pwRespLen, 
                                              uint8_t  *pbResp )
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Read_EPC);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bFlags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bManCode);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, pbUID, 8);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, pwRespLen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *pwRespLen, pbResp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_GetRandomNumber( phhalHw_Rd70x_DataParams_t * pDataParams,
                                                      uint8_t  bFlags, 
                                                      uint8_t  bManCode, 
                                                      uint8_t  *pbUID,
                                                      uint16_t *pwRespLen, 
                                                      uint8_t  *pbResp )
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Get_Rnd);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bFlags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bManCode);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, pbUID, 8);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, pwRespLen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *pwRespLen, pbResp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_SetPwd( phhalHw_Rd70x_DataParams_t * pDataParams, 
                                             uint8_t  bFlags, 
                                             uint8_t  bManCode, 
                                             uint8_t  *pbUID, 
                                             uint8_t  bPwdID, 
                                             uint8_t  *pbPwd, 
                                             uint16_t *pwRespLen, 
                                             uint8_t  *pbResp )
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Set_Pwd);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bFlags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bManCode);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, pbUID, 8);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bPwdID);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, pbPwd, 8);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, pwRespLen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *pwRespLen, pbResp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_WritePwd( phhalHw_Rd70x_DataParams_t * pDataParams, 
                                               uint8_t  bFlags, 
                                               uint8_t  bManCode, 
                                               uint8_t  *pbUID, 
                                               uint8_t  bPwdID, 
                                               uint8_t  *pbPwd, 
                                               uint16_t *pwRespLen, 
                                               uint8_t  *pbResp )
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Write_Pwd);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bFlags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bManCode);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, pbUID, 8);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bPwdID);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, pbPwd, 8);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, pwRespLen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *pwRespLen, pbResp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_LockPWD( phhalHw_Rd70x_DataParams_t * pDataParams, 
                                              uint8_t  bFlags, 
                                              uint8_t  bManCode, 
                                              uint8_t  *pbUID,
                                              uint8_t  bPWD_ID, 
                                              uint16_t *pwRespLen, 
                                              uint8_t  *pbResp )
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Lock_Pwd);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bFlags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bManCode);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, pbUID, 8);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bPWD_ID);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, pwRespLen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *pwRespLen, pbResp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_64BitPWDProtection( phhalHw_Rd70x_DataParams_t * pDataParams, 
                                                         uint8_t  bFlags, 
                                                         uint8_t  bManCode, 
                                                         uint8_t  *pbUID,
                                                         uint16_t *pwRespLen, 
                                                         uint8_t  *pbResp )
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_64Bit_Pwd_Protection);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bFlags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bManCode);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, pbUID, 8);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, pwRespLen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *pwRespLen, pbResp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_ProtectPage( phhalHw_Rd70x_DataParams_t * pDataParams, 
                                                  uint8_t  bFlags, 
                                                  uint8_t  bManCode, 
                                                  uint8_t  *pbUID, 
                                                  uint8_t  bPageNo, 
                                                  uint8_t  bProtectionStatus, 
                                                  uint16_t *pwRespLen, 
                                                  uint8_t  *pbResp )
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Protect_Page);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bFlags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bManCode);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, pbUID, 8);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bPageNo);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bProtectionStatus);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, pwRespLen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *pwRespLen, pbResp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_LockPageProtectionCondition( phhalHw_Rd70x_DataParams_t * pDataParams, 
                                                                  uint8_t  bFlags, 
                                                                  uint8_t  bManCode, 
                                                                  uint8_t  *pbUID, 
                                                                  uint8_t  bPageNo, 
                                                                  uint16_t *pwRespLen, 
                                                                  uint8_t  *pbResp )
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Lock_Page_Protection_Condition);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bFlags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bManCode);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, pbUID, 8);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bPageNo);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, pwRespLen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *pwRespLen, pbResp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_DestroyS( phhalHw_Rd70x_DataParams_t * pDataParams, 
                                               uint8_t  bFlags, 
                                               uint8_t  bManCode, 
                                               uint8_t  *pbUID, 
                                               uint16_t *pwRespLen, 
                                               uint8_t  *pbResp )
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_S_Destroy);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bFlags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bManCode);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, pbUID, 8);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, pwRespLen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *pwRespLen, pbResp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_InventoryReadS( phhalHw_Rd70x_DataParams_t * pDataParams, 
                                                     uint8_t  bFlags, 
                                                     uint8_t  bManCode, 
                                                     uint8_t  bAFI, 
                                                     uint8_t  bMaskLen, 
                                                     uint8_t  *pbUID, 
                                                     uint8_t  bBlockNo, 
                                                     uint8_t  bNoOfBlocks, 
                                                     uint16_t *pwRespLen, 
                                                     uint8_t  *pbResp )
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_S_Inventory_Read);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bFlags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bManCode);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bAFI);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bMaskLen);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, pbUID, 8);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bBlockNo);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bNoOfBlocks);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, pwRespLen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *pwRespLen, pbResp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_FastInventoryReadS( phhalHw_Rd70x_DataParams_t * pDataParams, 
                                                         uint8_t  bFlags, 
                                                         uint8_t  bManCode, 
                                                         uint8_t  bAFI, 
                                                         uint8_t  bMaskLen, 
                                                         uint8_t  *pbUID, 
                                                         uint8_t  bBlockNo, 
                                                         uint8_t  bNoOfBlocks, 
                                                         uint16_t *pwRespLen, 
                                                         uint8_t  *pbResp )
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_S_Fast_Inventory_Read);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bFlags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bManCode);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bAFI);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bMaskLen);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, pbUID, 8);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bBlockNo);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bNoOfBlocks);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, pwRespLen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *pwRespLen, pbResp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_GetMultipleBlockProtStatus( phhalHw_Rd70x_DataParams_t * pDataParams, 
                                                                 uint8_t  bFlags, 
                                                                 uint8_t  bManCode, 
                                                                 uint8_t  *pbUID,
                                                                 uint8_t  bFirstBlock, 
                                                                 uint8_t  bNoOfBlocks, 
                                                                 uint16_t *pwRespLen, 
                                                                 uint8_t  *pbResp )
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Get_Multi_Block_Prot_Status);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bFlags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bManCode);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, pbUID, 8);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bFirstBlock);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bNoOfBlocks);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, pwRespLen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *pwRespLen, pbResp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_EnablePrivacy( phhalHw_Rd70x_DataParams_t * pDataParams, 
                                                    uint8_t  bFlags, 
                                                    uint8_t  bManCode, 
                                                    uint8_t  *pbUID,
                                                    uint16_t *pwRespLen, 
                                                    uint8_t  *pbResp )
{
    phStatus_t PH_MEMLOC_REM status;


    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Enable_Privacy);    
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bFlags);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bManCode);
    phhalHw_Rd70x_AddParam_Buffer(pDataParams, pbUID, 8);

    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if (status == PH_ERR_SUCCESS)
    {
        status = phhalHw_Rd70x_GetStatus(pDataParams);

        if (status == PH_ERR_SUCCESS)
        {
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, pwRespLen);
            phhalHw_Rd70x_GetParam_Buffer(pDataParams, *pwRespLen, pbResp);
        }
    }
    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_ISO15693_Exchange(
    phhalHw_Rd70x_DataParams_t * pDataParams,
    uint8_t * send_buffer,
    uint16_t  send_bytelen,
    uint8_t ** rec_data,
    uint16_t * rec_bytelen)
{
    phStatus_t  PH_MEMLOC_REM status;
    uint16_t    PH_MEMLOC_REM wPosition;

    /* Build command*/
    phhalHw_Rd70x_SetCommand(pDataParams, uC_ISO15693_Exchange);    
    phhalHw_Rd70x_AddParam_Uint16(pDataParams, send_bytelen);

    /* Copy sendbuffer if neccessary */
    if (send_buffer != NULL)
    {
        /* Calculate start position */
        wPosition = PHHAL_HW_RD70X_RESERVED_BUFFER_LEN + pDataParams->wTxBufStartPos + pDataParams->wTxBufLen;

        /* Buffer overflow check */
        if ((wPosition + send_bytelen) > pDataParams->wTxBufSize)
        {
            pDataParams->wTxBufLen = 0;
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* Copy transmit buffer*/
        memcpy(&pDataParams->pTxBuffer[wPosition], send_buffer, send_bytelen);  /* PRQA S 3200 */
        pDataParams->wTxBufLen = pDataParams->wTxBufLen + send_bytelen;
    }

    /* reset received length */
    *rec_bytelen = 0;

    /* execute the command*/
    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
    {
        /* Fetch the values only, if the status is in the Range of -128 to 0*/
        status = phhalHw_Rd70x_GetStatus(pDataParams);
        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            /* Retrieve number of received bytes*/
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, rec_bytelen);

            /* Retrieve received data */
            phhalHw_Rd70x_GetParam_BufferPointer(pDataParams, rec_data);

            /* Retrieve status and advance receive buffer pointer to actual data */
            if (*rec_bytelen > 0)
            {
                status = phhalHw_Rd70x_EvaluateStatus((*rec_data)[0]);
                ++(*rec_data);
                --(*rec_bytelen);
            }
        }
    }

    /* Reset our transmit buffer contents */
    if (send_buffer != NULL)
    {
        pDataParams->wTxBufLen = pDataParams->wTxBufLen - send_bytelen;
    }

    return status;
}

phStatus_t phhalHw_Rd70x_Cmd_EPCUID_Exchange(
    phhalHw_Rd70x_DataParams_t * pDataParams,
    uint8_t bOption,
    uint8_t * send_buffer,
    uint16_t  send_bytelen,
    uint8_t bTxLastBits,
    uint8_t ** rec_data,
    uint16_t * rec_bytelen)
{
    phStatus_t  PH_MEMLOC_REM status;
    uint16_t    PH_MEMLOC_REM wPosition;

    /* Build command*/
    phhalHw_Rd70x_SetCommand(pDataParams, uC_UID_Exchange);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bOption);
    phhalHw_Rd70x_AddParam_Uint8(pDataParams, bTxLastBits);
    phhalHw_Rd70x_AddParam_Uint16(pDataParams, send_bytelen);

    /* Copy sendbuffer if neccessary */
    if (send_buffer != NULL)
    {
        /* Calculate start position */
        wPosition = PHHAL_HW_RD70X_RESERVED_BUFFER_LEN + pDataParams->wTxBufStartPos + pDataParams->wTxBufLen;

        /* Buffer overflow check */
        if ((wPosition + send_bytelen) > pDataParams->wTxBufSize)
        {
            pDataParams->wTxBufLen = 0;
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* Copy transmit buffer*/
        memcpy(&pDataParams->pTxBuffer[wPosition], send_buffer, send_bytelen);  /* PRQA S 3200 */
        pDataParams->wTxBufLen = pDataParams->wTxBufLen + send_bytelen;
    }

    /* reset received length */
    *rec_bytelen = 0;

    /* execute the command*/
    status = phhalHw_Rd70x_SendCommand(pDataParams);
    if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
    {
        /* Fetch the values only, if the status is in the Range of -128 to 0*/
        status = phhalHw_Rd70x_GetStatus(pDataParams);
        if ((status & PH_ERR_MASK) != PH_ERR_INTERNAL_ERROR)
        {
            /* Retrieve number of received bytes*/
            phhalHw_Rd70x_GetParam_Uint16(pDataParams, rec_bytelen);

            /* Retrieve received data */
            phhalHw_Rd70x_GetParam_BufferPointer(pDataParams, rec_data);

            /* Retrieve status and advance receive buffer pointer to actual data */
            if (*rec_bytelen > 0)
            {
                status = phhalHw_Rd70x_EvaluateStatus((*rec_data)[0]);
                ++(*rec_data);
                --(*rec_bytelen);
            }
        }
    }

    /* Reset our transmit buffer contents */
    if (send_buffer != NULL)
    {
        pDataParams->wTxBufLen = pDataParams->wTxBufLen - send_bytelen;
    }

    return status;
}

#endif /* NXPBUILD__PHHAL_HW_RD70X */
