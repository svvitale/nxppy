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
* Generic Tools Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.5 $
* $Date: Fri Apr 15 09:26:52 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#include <phTools.h>
#include <ph_RefDefs.h>

static uint8_t phTools_CalcParity(uint8_t bDataByte, uint8_t bMode);

phStatus_t phTools_EncodeParity(
                                uint8_t bOption,
                                uint8_t * pInBuffer,
                                uint16_t wInBufferLength,
                                uint8_t bInBufferBits,
                                uint16_t wOutBufferSize, 
                                uint8_t * pOutBuffer, 
                                uint16_t * pOutBufferLength,
                                uint8_t * pOutBufferBits
                                )
{
    uint16_t    PH_MEMLOC_REM wByteIndexIn;
    uint16_t    PH_MEMLOC_REM wByteIndexOut;
    uint8_t     PH_MEMLOC_REM bBitPosition;
    uint16_t    PH_MEMLOC_REM wInByteCount;

    /* Parameter check */
    if (((bOption != PH_TOOLS_PARITY_OPTION_EVEN) && (bOption != PH_TOOLS_PARITY_OPTION_ODD)) || (bInBufferBits > 7))
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_TOOLS);
    }

    /* Retrieve full input byte count */
    if (bInBufferBits == 0)
    {
        wInByteCount = wInBufferLength;
    }
    else
    {
        wInByteCount = wInBufferLength - 1;
    }

    /* Retrieve number of (additional) full bytes */
    *pOutBufferLength = (uint16_t)((uint16_t)(wInByteCount + bInBufferBits) >> 3);

    /* Retrieve output bits */
    *pOutBufferBits = (uint8_t)((uint16_t)(wInByteCount + bInBufferBits) % 8);

    /* Increment output length in case of incomplete byte */
    if (*pOutBufferBits > 0)
    {
        ++(*pOutBufferLength);
    }

    /* Overflow check */
    if (*pOutBufferLength > (0xFFFF - wInByteCount))
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_TOOLS);
    }

    /* Calculate number of output bytes */
    *pOutBufferLength = wInByteCount + *pOutBufferLength;

    /* Buffer overflow check*/
    if (wOutBufferSize < *pOutBufferLength)
    {
        *pOutBufferLength = 0;
        return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_TOOLS);
    }

    /* Prepare output buffer */
    pOutBuffer[0] = 0x00;

    /* Prepare loop vars */
    wByteIndexIn = 0;
    wByteIndexOut = 0;
    bBitPosition = 7;

    /* Do for each byte */
    for (; wByteIndexIn < wInBufferLength; ++wByteIndexIn, ++wByteIndexOut, --bBitPosition)
    {
        /* Append source bits to output */
        pOutBuffer[wByteIndexOut] |= (uint8_t)(pInBuffer[wByteIndexIn] << (7 - bBitPosition));

        /* If there is more data bits in the sourcebyte append it to next data byte */
        if ((wByteIndexOut + 1) < *pOutBufferLength)
        {
            pOutBuffer[wByteIndexOut + 1]  = (uint8_t)(pInBuffer[wByteIndexIn] >> (1 + bBitPosition));

            /* Perform parity appending if this isn't an incomplete byte */
            if ((bInBufferBits == 0) || ((wByteIndexIn + 1) < wInBufferLength))
            {
                pOutBuffer[wByteIndexOut + 1] |= (uint8_t)(phTools_CalcParity(pInBuffer[wByteIndexIn], bOption) << (7 - bBitPosition));
            }
        }

        /* We have reached the 8th parity bit, the output buffer index is now one ahead */
        if (bBitPosition == 0)
        {
            if ((wByteIndexOut + 2) < *pOutBufferLength)
            {
                bBitPosition = 8;
                pOutBuffer[++wByteIndexOut + 1] = 0x00;
            }
        }
    }

    /* Mask out invalid bits of last byte */
    if (*pOutBufferBits > 0)
    {
        pOutBuffer[*pOutBufferLength - 1] &= (uint8_t)(0xFF >> (8 - *pOutBufferBits));
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_TOOLS);
}

phStatus_t phTools_DecodeParity(
                                uint8_t bOption,
                                uint8_t * pInBuffer, 
                                uint16_t wInBufferLength,
                                uint8_t bInBufferBits, 
                                uint16_t wOutBufferSize,
                                uint8_t * pOutBuffer,
                                uint16_t * pOutBufferLength,
                                uint8_t * pOutBufferBits
                                )
{
    uint16_t    PH_MEMLOC_REM wByteIndexIn;
    uint16_t    PH_MEMLOC_REM wByteIndexOut;
    uint8_t     PH_MEMLOC_REM bBitPosition;
    uint16_t    PH_MEMLOC_REM wDiv;
    uint8_t     PH_MEMLOC_REM bMod;
    uint8_t     PH_MEMLOC_REM bParity;

    /* Parameter check */
    if (((bOption != PH_TOOLS_PARITY_OPTION_EVEN) && (bOption != PH_TOOLS_PARITY_OPTION_ODD)) || (bInBufferBits > 7))
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_TOOLS);
    }

    /* Parameter check */
    if (wInBufferLength == 0)
    {
        /* Zero input length is simply passed through */
        if (bInBufferBits == 0)
        {
            *pOutBufferLength = 0;
            *pOutBufferBits = 0;
            return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_TOOLS);
        }
        /* Invalid parameter */
        else
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_TOOLS);
        }
    }

    /* Retrieve DIV and MOD */
    if (bInBufferBits == 0)
    {
        wDiv = (uint16_t)(wInBufferLength / 9);
        bMod = (uint8_t)(wInBufferLength % 9);
    }
    else
    {
        wDiv = (uint16_t)((wInBufferLength - 1) / 9);
        bMod = (uint8_t)((wInBufferLength - 1) % 9);
    }

    /* Calculate number of output bytes */
    *pOutBufferLength = (uint16_t)((wDiv << 3) + bMod);
    if (bMod > bInBufferBits)
    {
        --(*pOutBufferLength);
    }

    /* Calculate number of rest-bits of output */
    *pOutBufferBits = (uint8_t)((8 - (((8 + (*pOutBufferLength % 8)) - bInBufferBits) % 8)) % 8);

    /* Increment output length in case of incomplete byte */
    if (*pOutBufferBits > 0)
    {
        ++(*pOutBufferLength);
    }

    /* Buffer overflow check*/
    if (wOutBufferSize < *pOutBufferLength)
    {
        *pOutBufferLength = 0;
        return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_TOOLS);
    }

    /* Prepare loop vars */
    wByteIndexIn = 0;
    wByteIndexOut = 0;
    bBitPosition = 7;

    /* Do for each byte */
    for (; wByteIndexOut < *pOutBufferLength; ++wByteIndexOut, ++wByteIndexIn, --bBitPosition)
    {
        /* Append source bits to output */
        pOutBuffer[wByteIndexOut] = (uint8_t)(pInBuffer[wByteIndexIn] >> (7 - bBitPosition));

        /* If there is more data bits in the sourcebyte append it to next data byte */
        if ((wByteIndexIn + 1) < wInBufferLength)
        {
            /* Append remaining bits to output */
            pOutBuffer[wByteIndexOut] |= (uint8_t)(pInBuffer[wByteIndexIn + 1] << (1 + bBitPosition));

            /* Perform parity checking if this isn't an incomplete byte */
            if ((*pOutBufferBits == 0) || ((wByteIndexOut + 1) < *pOutBufferLength))
            {
                bParity = phTools_CalcParity(pOutBuffer[wByteIndexOut], bOption);
                if ((pInBuffer[wByteIndexIn + 1] & (uint8_t)(1 << (7 - bBitPosition))) != (bParity << (7 - bBitPosition)))
                {
                    return PH_ADD_COMPCODE(PH_ERR_INTEGRITY_ERROR, PH_COMP_TOOLS);
                }
            }
        }

        /* We have reached the 8th parity bit, the input buffer index is now one ahead */
        if (bBitPosition == 0)
        {
            bBitPosition = 8;
            ++wByteIndexIn;
        }
    }

    /* Mask out invalid bits of last byte */
    if (*pOutBufferBits > 0)
    {
        pOutBuffer[*pOutBufferLength - 1] &= (uint8_t)(0xFF >> (8 - *pOutBufferBits));
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_TOOLS);
}

phStatus_t phTools_CalculateCrc5(
                                 uint8_t bOption,
                                 uint8_t bPreset,
                                 uint8_t bPolynom,
                                 uint8_t * pData,
                                 uint16_t wDataLength,
                                 uint8_t * pCrc
                                 )
{
    uint16_t PH_MEMLOC_REM wDataIndex = 0;
    uint8_t  PH_MEMLOC_REM bBitIndex;
    uint8_t  PH_MEMLOC_REM bBitMax;

    if (bOption & (uint8_t)~(uint8_t)PH_TOOLS_CRC_OPTION_MASK)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_TOOLS);
    }

    *pCrc = bPreset;

    if (bOption & PH_TOOLS_CRC_OPTION_MSB_FIRST)
    {
        /* Shift 5bit preset to 8bit (data) alignment */
        *pCrc <<= 3;

        /* Shift 5bit polinom to 8bit (data) alignment */
        bPolynom <<= 3;
    }

    /* Loop through all data bytes */
    while (wDataLength)
    {
        /* XOR input data */
        if (bOption & PH_TOOLS_CRC_OPTION_BITWISE)
        {
            if (wDataLength < 8)
            {
                bBitMax = (uint8_t)wDataLength;
                wDataLength = 0;
            }
            else
            {
                bBitMax = 8;
                wDataLength -= 8;
            }
        }
        else
        {
            bBitMax = 8;
            /* Decrement DataLen */
            --wDataLength;
        }

        /* CRC polynom (MSB first) */
        if (bOption & PH_TOOLS_CRC_OPTION_MSB_FIRST)
        {
            *pCrc ^= pData[wDataIndex++] & (0xFFU << (8 - bBitMax));

            for (bBitIndex = 0; bBitIndex < bBitMax; ++bBitIndex)
            {
                if ((*pCrc) & 0x80)
                {
                    *pCrc = (uint8_t)(((*pCrc) << 1) ^ bPolynom);
                }
                else
                {
                    *pCrc = (*pCrc) << 1;
                }
            }
        }
        /* CRC polynom (LSB first) */
        else
        {
            *pCrc ^= pData[wDataIndex++] & (0xFFU >> (8 - bBitMax));

            for (bBitIndex = 0; bBitIndex < bBitMax; ++bBitIndex)
            {
                if ((*pCrc) & 0x01)
                {
                    *pCrc = (uint8_t)(((*pCrc) >> 1) ^ bPolynom);
                }
                else
                {
                    *pCrc = ((*pCrc) >> 1);
                }
            }
        }
    }

    if (bOption & PH_TOOLS_CRC_OPTION_MSB_FIRST)
    {
        /* Shift back for 5bit alignment */
        *pCrc >>= 3;
    }

    /* Invert CRC if requested */
    if (bOption & PH_TOOLS_CRC_OPTION_OUPUT_INVERTED)
    {
        *pCrc ^= 0x1FU;
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_TOOLS);
}

phStatus_t phTools_CalculateCrc8(
                                 uint8_t bOption,
                                 uint8_t bPreset,
                                 uint8_t bPolynom,
                                 uint8_t * pData,
                                 uint16_t wDataLength,
                                 uint8_t * pCrc
                                 )
{
    uint16_t PH_MEMLOC_REM wDataIndex = 0;
    uint8_t  PH_MEMLOC_REM bBitIndex;
    uint8_t  PH_MEMLOC_REM bBitMax;

    if (bOption & (uint8_t)~(uint8_t)PH_TOOLS_CRC_OPTION_MASK)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_TOOLS);
    }

    *pCrc = bPreset;

    /* Loop through all data bytes */
    while (wDataLength)
    {
        /* XOR input data */
        if (bOption & PH_TOOLS_CRC_OPTION_BITWISE)
        {
            if (wDataLength < 8)
            {
                bBitMax = (uint8_t)wDataLength;
                wDataLength = 0;
            }
            else
            {
                bBitMax = 8;
                wDataLength -= 8;
            }
        }
        else
        {
            bBitMax = 8;
            /* Decrement DataLen */
            --wDataLength;
        }

        /* CRC polynom (MSB first) */
        if (bOption & PH_TOOLS_CRC_OPTION_MSB_FIRST)
        {
            *pCrc ^= pData[wDataIndex++] & (0xFFU << (8 - bBitMax));

            for (bBitIndex = 0; bBitIndex < bBitMax; ++bBitIndex)
            {
                if ((*pCrc) & 0x80)
                {
                    *pCrc = (uint8_t)(((*pCrc) << 1) ^ bPolynom);
                }
                else
                {
                    *pCrc = ((*pCrc) << 1);
                }
            }
        }
        /* CRC polynom (LSB first) */
        else
        {
            *pCrc ^= pData[wDataIndex++] & (0xFFU >> (8 - bBitMax));

            for (bBitIndex = 0; bBitIndex < bBitMax; ++bBitIndex)
            {
                if ((*pCrc) & 0x01)
                {
                    *pCrc = (uint8_t)(((*pCrc) >> 1) ^ bPolynom);
                }
                else
                {
                    *pCrc = ((*pCrc) >> 1);
                }
            }
        }
    }

    /* Invert CRC if requested */
    if (bOption & PH_TOOLS_CRC_OPTION_OUPUT_INVERTED)
    {
        *pCrc ^= 0xFFU;
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_TOOLS);
}

phStatus_t phTools_CalculateCrc16(
                                  uint8_t bOption,
                                  uint16_t wPreset,
                                  uint16_t wPolynom,
                                  uint8_t * pData,
                                  uint16_t wDataLength,
                                  uint16_t * pCrc
                                  )
{
    uint16_t PH_MEMLOC_REM wDataIndex = 0;
    uint8_t  PH_MEMLOC_REM bBitIndex;
    uint8_t  PH_MEMLOC_REM bBitMax;

    if (bOption & (uint8_t)~(uint8_t)PH_TOOLS_CRC_OPTION_MASK)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_TOOLS);
    }

    *pCrc = wPreset;

    /* Loop through all data bytes */
    while (wDataLength)
    {
        /* XOR input data */
        if (bOption & PH_TOOLS_CRC_OPTION_BITWISE)
        {
            if (wDataLength < 8)
            {
                bBitMax = (uint8_t)wDataLength;
                wDataLength = 0;
            }
            else
            {
                bBitMax = 8;
                wDataLength -= 8;
            }
        }
        else
        {
            bBitMax = 8;
            /* Decrement DataLen */
            --wDataLength;
        }

        /* CRC polynom (MSB first) */
        if (bOption & PH_TOOLS_CRC_OPTION_MSB_FIRST)
        {
            *pCrc ^= (uint16_t)pData[wDataIndex++] << 8;

            for (bBitIndex = 0; bBitIndex < bBitMax; ++bBitIndex)
            {
                if ((*pCrc) & 0x8000)
                {
                    *pCrc = (uint16_t)(((*pCrc) << 1) ^ wPolynom);
                }
                else
                {
                    *pCrc = ((*pCrc) << 1);
                }
            }
        }
        /* CRC polynom (LSB first) */
        else
        {
            *pCrc ^= pData[wDataIndex++];

            for (bBitIndex = 0; bBitIndex < bBitMax; ++bBitIndex)
            {
                if ((*pCrc) & 0x0001)
                {
                    *pCrc = (uint16_t)(((*pCrc) >> 1) ^ wPolynom);
                }
                else
                {
                    *pCrc = ((*pCrc) >> 1);
                }
            }
        }
    }

    /* Invert CRC if requested */
    if (bOption & PH_TOOLS_CRC_OPTION_OUPUT_INVERTED)
    {
        *pCrc ^= 0xFFFFU;
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_TOOLS);
}

phStatus_t phTools_CalculateCrc32(
                                  uint8_t bOption,
                                  uint32_t dwPreset,
                                  uint32_t dwPolynom,
                                  uint8_t * pData,
                                  uint16_t wDataLength,
                                  uint32_t * pCrc
                                  )
{
    uint16_t PH_MEMLOC_REM wDataIndex = 0;
    uint8_t  PH_MEMLOC_REM bBitIndex;
    uint8_t  PH_MEMLOC_REM bBitMax;

    if (bOption & (uint8_t)~(uint8_t)PH_TOOLS_CRC_OPTION_MASK)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_TOOLS);
    }

    *pCrc = dwPreset;

    /* Loop through all data bytes */
    while (wDataLength)
    {
        /* XOR input data */
        if (bOption & PH_TOOLS_CRC_OPTION_BITWISE)
        {
            if (wDataLength < 8)
            {
                bBitMax = (uint8_t)wDataLength;
                wDataLength = 0;
            }
            else
            {
                bBitMax = 8;
                wDataLength -= 8;
            }
        }
        else
        {
            bBitMax = 8;
            /* Decrement DataLen */
            --wDataLength;
        }

        /* CRC polynom (MSB first) */
        if (bOption & PH_TOOLS_CRC_OPTION_MSB_FIRST)
        {
            *pCrc ^= (uint32_t)pData[wDataIndex++] << 24;

            for (bBitIndex = 0; bBitIndex < bBitMax; ++bBitIndex)
            {
                if ((*pCrc) & 0x80000000)
                {
                    *pCrc = (uint32_t)(((*pCrc) << 1) ^ dwPolynom);
                }
                else
                {
                    *pCrc = ((*pCrc) << 1);
                }
            }
        }
        /* CRC polynom (LSB first) */
        else
        {
            *pCrc ^= pData[wDataIndex++];

            for (bBitIndex = 0; bBitIndex < bBitMax; ++bBitIndex)
            {
                if ((*pCrc) & 0x00000001)
                {
                    *pCrc = (uint32_t)(((*pCrc) >> 1) ^ dwPolynom);
                }
                else
                {
                    *pCrc = ((*pCrc) >> 1);
                }
            }
        }
    }

    /* Invert CRC if requested */
    if (bOption & PH_TOOLS_CRC_OPTION_OUPUT_INVERTED)
    {
        *pCrc ^= 0xFFFFFFFFU;
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_TOOLS);
}

static uint8_t phTools_CalcParity(
                                  uint8_t bDataByte,
                                  uint8_t bOption
                                  )
{
    uint8_t PH_MEMLOC_REM bBit;
    uint8_t PH_MEMLOC_REM bParity;

    if (bOption == PH_TOOLS_PARITY_OPTION_EVEN)
    {
        bParity = 0x00;
    }
    else
    {
        bParity = 0x01;
    }

    for (bBit = 0; bBit < 8; ++bBit)
    {
        if (bDataByte & (uint8_t)(1 << bBit))
        {
            ++bParity;
        }
    }
    return bParity & 0x01;
}
