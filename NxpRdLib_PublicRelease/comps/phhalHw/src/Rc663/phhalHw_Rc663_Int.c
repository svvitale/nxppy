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
* Internal functions for Rc663 specific HAL-Component of Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.10 $
* $Date: Fri Apr 15 09:27:29 2011 $
*
* History:
*  CHu: Generated 27. April 2010
*
*/
#include <phhalHw.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHHAL_HW_RC663

#include "phhalHw_Rc663.h"
#include "phhalHw_Rc663_Int.h"
#include "phhalHw_Rc663_Config.h"
#include <phhalHw_Rc663_Reg.h>

/** Register Settings to return */
static const uint8_t PH_MEMLOC_CONST_ROM gkphhalHw_Rc663_Registers[] =
{
    PHHAL_HW_RC663_REG_DRVMODE,
    PHHAL_HW_RC663_REG_TXAMP,
    PHHAL_HW_RC663_REG_DRVCON,
    PHHAL_HW_RC663_REG_TXI,
    PHHAL_HW_RC663_REG_TXCRCCON,
    PHHAL_HW_RC663_REG_RXCRCCON,
    PHHAL_HW_RC663_REG_TXDATANUM,
    PHHAL_HW_RC663_REG_TXMODWIDTH,
    PHHAL_HW_RC663_REG_TXSYM10BURSTLEN,
    PHHAL_HW_RC663_REG_TXWAITCTRL,
    PHHAL_HW_RC663_REG_FRAMECON,
    PHHAL_HW_RC663_REG_RXCTRL,
    PHHAL_HW_RC663_REG_RXTHRESHOLD,
    PHHAL_HW_RC663_REG_RCV,
    PHHAL_HW_RC663_REG_RXANA
};

/** Register Settings for ISO14443A @ 106kbit/s */
static const uint8_t PH_MEMLOC_CONST_ROM gkphhalHw_Rc663_I14443A_106[] =
{
    0x8E,
    0x15,
    0x11,
    0x0A,
    0x18,
    0x18,
    0x0F,
    0x27,
    0x00,
    0xC0,
    0xCF,
    0x04,
    PHHAL_HW_RC663_RXTHRESHOLD_I14443A_106,
    0x12,
    0x0A
};

/** Register Settings for ISO14443A @ 212kbit/s */
static const uint8_t PH_MEMLOC_CONST_ROM gkphhalHw_Rc663_I14443A_212[] =
{
    0x8E,
    0x12,
    0x11,
    0x0A,
    0x18,
    0x18,
    0x0F,
    0x10,
    0x00,
    0xC0,
    0xCF,
    0x05,
    PHHAL_HW_RC663_RXTHRESHOLD_I14443A_212,
    0x12,
    0x02
};

/** Register Settings for ISO14443A @ 424kbit/s */
static const uint8_t PH_MEMLOC_CONST_ROM gkphhalHw_Rc663_I14443A_424[] =
{
    0x8E,
    0x12,
    0x11,
    0x0A,
    0x18,
    0x18,
    0x0F,
    0x08,
    0x00,
    0xC0,
    0xCF,
    0x06,
    PHHAL_HW_RC663_RXTHRESHOLD_I14443A_424,
    0x12,
    0x0A
};

/** Register Settings for ISO14443A @ 848kbit/s */
static const uint8_t PH_MEMLOC_CONST_ROM gkphhalHw_Rc663_I14443A_848[] =
{
    0x8F,
    0xDB,
    0x11,
    0x0A,
    0x18,
    0x18,
    0x0F,
    0x02,
    0x00,
    0xC0,
    0xCF,
    0x07,
    PHHAL_HW_RC663_RXTHRESHOLD_I14443A_848,
    0x12,
    0x02
};

/** Register Settings for ISO14443B @ 106kbit/s */
static const uint8_t PH_MEMLOC_CONST_ROM gkphhalHw_Rc663_I14443B_106[] =
{
    0x8F,
    0x00 | PHHAL_HW_RC663_MODINDEX_I14443B,
    0x01,
    0x0A,
    0x7B,
    0x7B,
    0x08,
    0x00,
    0x00,
    0x0F,
    0x05,
    0x34,
    PHHAL_HW_RC663_RXTHRESHOLD_I14443B_106,
    0x12,
    0x0A
};

/** Register Settings for ISO14443B @ 212kbit/s */
static const uint8_t PH_MEMLOC_CONST_ROM gkphhalHw_Rc663_I14443B_212[] =
{
    0x8F,
    0x00 | PHHAL_HW_RC663_MODINDEX_I14443B,
    0x01,
    0x0A,
    0x7B,
    0x7B,
    0x08,
    0x00,
    0x00,
    0x01,
    0x05,
    0x35,
    PHHAL_HW_RC663_RXTHRESHOLD_I14443B_212,
    0x12,
    0x02
};

/** Register Settings for ISO14443B @ 424kbit/s */
static const uint8_t PH_MEMLOC_CONST_ROM gkphhalHw_Rc663_I14443B_424[] =
{
    0x8F,
    0x00 | PHHAL_HW_RC663_MODINDEX_I14443B,
    0x01,
    0x0A,
    0x7B,
    0x7B,
    0x08,
    0x00,
    0x00,
    0x01,
    0x05,
    0x36,
    PHHAL_HW_RC663_RXTHRESHOLD_I14443B_424,
    0x12,
    0x09
};

/** Register Settings for ISO14443B @ 848kbit/s */
static const uint8_t PH_MEMLOC_CONST_ROM gkphhalHw_Rc663_I14443B_848[] =
{
    0x8F,
    0x00 | PHHAL_HW_RC663_MODINDEX_I14443B,
    0x01,
    0x0A,
    0x7B,
    0x7B,
    0x08,
    0x00,
    0x00,
    0x01,
    0x05,
    0x37,
    PHHAL_HW_RC663_RXTHRESHOLD_I14443B_848,
    0x12,
    0x02
};

/** Register Settings for Felica @ 212kbit/s */
static const uint8_t PH_MEMLOC_CONST_ROM gkphhalHw_Rc663_Felica_212[] =
{
    0x8F,
    0x00 | PHHAL_HW_RC663_MODINDEX_FELICA,
    0x01,
    0x0A,
    0x09,
    0x09,
    0x08,
    0x00,
    0x03,
    0x80,
    0x01,
    0x05,
    PHHAL_HW_RC663_RXTHRESHOLD_FELICA_212,
    0x12,
    0x02
};

/** Register Settings for Felica @ 424kbit/s */
static const uint8_t PH_MEMLOC_CONST_ROM gkphhalHw_Rc663_Felica_424[] =
{
    0x8F,
    0x00 | PHHAL_HW_RC663_MODINDEX_FELICA,
    0x01,
    0x0A,
    0x09,
    0x09,
    0x08,
    0x00,
    0x03,
    0x80,
    0x01,
    0x06,
    PHHAL_HW_RC663_RXTHRESHOLD_FELICA_424,
    0x12,
    0x02
};

/** Register Settings for I15693 @ High */
static const uint8_t PH_MEMLOC_CONST_ROM gkphhalHw_Rc663_I15693_High[] =
{
    0x8F,
    0x00 | PHHAL_HW_RC663_MODINDEX_I15693,
    0x01,
    0x0A,
    0x7B,
    0x7B,
    0x08,
    0x00,
    0x00,
    0x88,
    0x0F,
    0x02,
    PHHAL_HW_RC663_RXTHRESHOLD_I15693_FAST,
    0x12,
    0x06
};

/** Register Settings for I15693 @ Fast_High */
static const uint8_t PH_MEMLOC_CONST_ROM gkphhalHw_Rc663_I15693_Fast_High[] =
{
    0x8F,
    0x00 | PHHAL_HW_RC663_MODINDEX_I15693,
    0x01,
    0x0A,
    0x7B,
    0x7B,
    0x08,
    0x00,
    0x00,
    0x88,
    0x0F,
    0x03,
    PHHAL_HW_RC663_RXTHRESHOLD_I15693_FAST_HIGH,
    0x12,
    0x06
};

/** Register Settings for EPC/UID */
static const uint8_t PH_MEMLOC_CONST_ROM gkphhalHw_Rc663_EpcUid[] =
{
    0x8F,
    0x00 | PHHAL_HW_RC663_MODINDEX_EPCUID,
    0x01,
    0x0A,
    0x74,
    0x7B,
    0x18,
    0x00,
    0x00,
    0x50,
    0x0F,
    0x03,
    PHHAL_HW_RC663_RXTHRESHOLD_EPCUID,
    0x12,
    0x06
};

/** Register Settings for ISO18000-3 Mode3 @ 2/424kbit/s */
static const uint8_t PH_MEMLOC_CONST_ROM gkphhalHw_Rc663_I18000p3m3_DSM2[] =
{
    0x8F,
    0x00 | PHHAL_HW_RC663_MODINDEX_I18000P3M3,
    0x01,
    0x0A,
    0x11,
    0x91,
    0x09,
    0x00,
    0x00,
    0x80,
    0x01,
    0x04,
    PHHAL_HW_RC663_RXTHRESHOLD_I18000P3M3,
    0x12,
    0x0A
};

/** Register Settings for ISO18000-3 Mode3 @ 4/424kbit/s */
static const uint8_t PH_MEMLOC_CONST_ROM gkphhalHw_Rc663_I18000p3m3_DSM4[] =
{
    0x8F,
    0x00 | PHHAL_HW_RC663_MODINDEX_I18000P3M3,
    0x01,
    0x0A,
    0x11,
    0x91,
    0x09,
    0x00,
    0x00,
    0x80,
    0x01,
    0x03,
    PHHAL_HW_RC663_RXTHRESHOLD_I18000P3M3,
    0x12,
    0x0A
};

/** Register Settings for ISO18000-3 Mode3 @ 2/848kbit/s */
static const uint8_t PH_MEMLOC_CONST_ROM gkphhalHw_Rc663_I18000p3m3_QSM2[] =
{
    0x8F,
    0x00 | PHHAL_HW_RC663_MODINDEX_I18000P3M3,
    0x01,
    0x0A,
    0x11,
    0x91,
    0x09,
    0x00,
    0x00,
    0x80,
    0x01,
    0x05,
    PHHAL_HW_RC663_RXTHRESHOLD_I18000P3M3,
    0x12,
    0x0A
};

/** Register Settings for ISO18000-3 Mode3 @ 4/848kbit/s */
static const uint8_t PH_MEMLOC_CONST_ROM gkphhalHw_Rc663_I18000p3m3_QSM4[] =
{
    0x8F,
    0x00 | PHHAL_HW_RC663_MODINDEX_I18000P3M3,
    0x01,
    0x0A,
    0x11,
    0x91,
    0x09,
    0x00,
    0x00,
    0x80,
    0x01,
    0x04,
    PHHAL_HW_RC663_RXTHRESHOLD_I18000P3M3,
    0x12,
    0x0A
};

/* Digital delay for all protocols and speeds in microseconds */
static const uint16_t PH_MEMLOC_CONST_ROM gkphhalHw_Rc663_DigiDelays_Us[][4] =
{
    /* PHHAL_HW_CARDTYPE_ISO14443A */
    {/* 106KBaud */ 17, /* 212KBaud */ 49, /* 424KBaud */ 45, /* 848KBaud */ 42},

    /* PHHAL_HW_CARDTYPE_ISO14443B */
    {/* 106KBaud */ 0, /* 212KBaud */ 0, /* 424KBaud */ 0, /* 848KBaud */ 0},

    /* PHHAL_HW_CARDTYPE_FELICA */
    {/* N/A */ 0, /* 212KBaud */ 322, /* 424KBaud */ 165, /* N/A */ 0},

    /* PHHAL_HW_CARDTYPE_ISO15693 */
    {/* LOW */ 0, /* HIGH */ 193, /* FAST_LOW */ 0, /* FAST_HIGH */ 89},

    /* PHHAL_HW_CARDTYPE_ICODEEPCUID */
    {/* ALL */ 61, /* N/A */ 0, /* N/A */ 0, /* N/A */ 0},

    /* PHHAL_HW_CARDTYPE_I18000P3M3 */
    {/* 2/424 */ 75, /* 4/424 */ 121, /* 2/848 */ 11, /* 4/848 */ 47},

    /* PHHAL_HW_CARDTYPE_I18092MPI */
    {/* 106KBaud */ 17, /* 212KBaud */ 322, /* 424KBaud */ 165, /* N/A */ 0}
};

phStatus_t phhalHw_Rc663_WriteFifo(
                                   phhalHw_Rc663_DataParams_t * pDataParams,
                                   uint8_t * pData,
                                   uint16_t wLength,
                                   uint16_t * pBytesWritten
                                   )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bValue;
    uint16_t    PH_MEMLOC_REM wFifoLen;

    /* Read out the lower FiFo Level bits */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_FIFOLENGTH, &bValue));
    wFifoLen = (uint16_t)bValue;

    /* Read out the higher FiFo Level bits if applicable */
    if (pDataParams->bFifoSize == PHHAL_HW_RC663_VALUE_FIFOSIZE_512)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_FIFOCONTROL, &bValue));

        /* If higher bits are set, we ignore the lower bits since they would change too fast in case of a slow interface. */
        wFifoLen = wFifoLen + ((uint16_t)(bValue & PHHAL_HW_RC663_MASK_FIFOLENGTH_HI) << 8);

        /* Check if FiFO has enough space */
        if (wLength > (0x200 - wFifoLen))
        {
            /* Truncate byte count */
            wLength = 0x200 - wFifoLen;

            /* Return buffer overflow error */
            status = PH_ERR_BUFFER_OVERFLOW;
        }
        else
        {
            status = PH_ERR_SUCCESS;
        }
    }
    else
    {
        /* Check if FiFO has enough space */
        if (wLength > (0xFF - wFifoLen))
        {
            /* Truncate byte count */
            wLength = 0xFF - wFifoLen;

            /* Return buffer overflow error */
            status = PH_ERR_BUFFER_OVERFLOW;
        }
        else
        {
            status = PH_ERR_SUCCESS;
        }
    }

    /* Perform actual write to FiFo */
    if (wLength > 0)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_WriteData(pDataParams, PHHAL_HW_RC663_REG_FIFODATA, pData, wLength));
    }

    /* Return number of written bytes */
    *pBytesWritten = wLength;

    return PH_ADD_COMPCODE(status, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_ReadFifo(
                                  phhalHw_Rc663_DataParams_t * pDataParams,
                                  uint16_t wDataSize,
                                  uint8_t * pData,
                                  uint16_t * pLength
                                  )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bValue;
    uint16_t    PH_MEMLOC_REM wFifoLen;

    /* Read out the lower FiFo Level bits */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_FIFOLENGTH, &bValue));
    wFifoLen = (uint16_t)bValue;

    /* Read out the higher FiFo Level bits if applicable */
    if ((bValue == 0x00) && (pDataParams->bFifoSize == PHHAL_HW_RC663_VALUE_FIFOSIZE_512))
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_FIFOCONTROL, &bValue));

        /* If higher bits are set, we ignore the lower bits since they would change too fast in case of a slow interface. */
        wFifoLen = (uint16_t)(bValue & PHHAL_HW_RC663_MASK_FIFOLENGTH_HI) << 8;
    }

    /* check for buffer overflow */
    if (wFifoLen > wDataSize)
    {
        /* read maximum possible number of bytes */
        *pLength = wDataSize;

        /* return buffer overflow status */
        status = PH_ERR_BUFFER_OVERFLOW;
    }
    else
    {
        /* read all bytes */
        *pLength = wFifoLen;

        /* Buffer is big enough */
        status = PH_ERR_SUCCESS;
    }

    /* Perform actual reading operation */
    if (*pLength > 0)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_ReadData(pDataParams, PHHAL_HW_RC663_REG_FIFODATA, *pLength, pData));
    }

    /* Clear FIFO on buffer overflow */
    if ((status & PH_ERR_MASK) == PH_ERR_BUFFER_OVERFLOW)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_FlushFifo(pDataParams));
    }

    return PH_ADD_COMPCODE(status, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_FlushFifo(
                                   phhalHw_Rc663_DataParams_t * pDataParams
                                   )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bValue;

    /* Read FIFO Control register*/
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_FIFOCONTROL, &bValue));

    /* Set FlushFifo bit */
    bValue |= PHHAL_HW_RC663_BIT_FLUSHFIFO;

    /* Write to FIFO Control register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_FIFOCONTROL, bValue));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_WriteData(
                                   phhalHw_Rc663_DataParams_t * pDataParams,
                                   uint8_t bAddress,
                                   uint8_t * pData,
                                   uint16_t wLength
                                   )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t    PH_MEMLOC_COUNT wIndex;
    uint16_t    PH_MEMLOC_REM wBytesRead;
    uint8_t     PH_MEMLOC_REM bBackup;

    /* SPI protocol */
    if (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_SPI)
    {
        /* shift address and clear RD/NWR bit to indicate write operation */
        bAddress = (uint8_t)(bAddress << 1);

        /* decrement the buffer pointer and backup first byte (for chaining) */
        --pData;
        bBackup = pData[0];

        /* add address as first byte */
        pData[0] = bAddress;
        ++wLength;

        /* perform exchange */
        PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Exchange(
            pDataParams->pBalDataParams,
            PH_EXCHANGE_DEFAULT,
            pData,
            wLength,
            wLength,
            pData,
            &wBytesRead));

        /* restore backuped byte */
        pData[0] = bBackup;

        /* check number of received bytes */
        if (wBytesRead != wLength)
        {
            return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_HAL);
        }
    }
    /* I2C protocol */
    else if (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_I2C)
    {
        /* decrement the buffer pointer and backup first byte (for chaining) */
        --pData;
        bBackup = pData[0];

        /* add address as first byte */
        pData[0] = bAddress;
        ++wLength;

        /* perform exchange */
        PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Exchange(
            pDataParams->pBalDataParams,
            PH_EXCHANGE_DEFAULT,
            pData,
            wLength,
            0,
            NULL,
            NULL));

        /* restore backuped byte */
        pData[0] = bBackup;
    }
    /* RS232 protocol */
    else
    {
        /* Write each single data byte */
        for (wIndex = 0; wIndex < wLength; ++wIndex)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, bAddress, pData[wIndex]));
        }
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_ReadData(
                                  phhalHw_Rc663_DataParams_t * pDataParams,
                                  uint8_t bAddress,
                                  uint16_t wLength,
                                  uint8_t * pData
                                  )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t    PH_MEMLOC_COUNT wIndex;
    uint16_t    PH_MEMLOC_REM wBytesRead;
    uint8_t     PH_MEMLOC_REM aProtocol[1];
    uint8_t     PH_MEMLOC_REM bBackup;

    /* SPI protocol */
    if (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_SPI)
    {
        /* shift address and set RD/NWR bit to indicate read operation */
        bAddress = (uint8_t)(bAddress << 1) | 0x01U;

        /* decrement the buffer pointer and backup first byte (for chaining) */
        --pData;
        bBackup = pData[0];

        /* Write each single data byte */
        memset(pData, (int)bAddress, wLength); /* PRQA S 3200 */

        /* add the 0x00 byte on the end */
        pData[++wLength] = 0x00;

        /* perform exchange */
        PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Exchange(
            pDataParams->pBalDataParams,
            PH_EXCHANGE_DEFAULT,
            pData,
            wLength,
            wLength,
            pData,
            &wBytesRead));

        /* restore backuped byte */
        pData[0] = bBackup;

        /* check number of received bytes */
        if (wBytesRead != wLength)
        {
            return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_HAL);
        }
    }
    /* I2C protocol */
    else if (pDataParams->bBalConnectionType == PHHAL_HW_BAL_CONNECTION_I2C)
    {
        /* add address as first byte */
        aProtocol[0] = bAddress;

        /* perform exchange */
        PH_CHECK_SUCCESS_FCT(statusTmp, phbalReg_Exchange(
            pDataParams->pBalDataParams,
            PH_EXCHANGE_DEFAULT,
            aProtocol,
            1,
            wLength,
            pData,
            &wBytesRead));

        /* check number of received bytes */
        if (wBytesRead != wLength)
        {
            return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_HAL);
        }
    }
    /* RS232 protocol */
    else
    {
        /* Read each single data byte */
        for (wIndex = 0; wIndex < wLength; ++wIndex)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, bAddress, &pData[wIndex]));
        }
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_SetCardMode(
                                     phhalHw_Rc663_DataParams_t * pDataParams,
                                     uint16_t wTxDataRate,
                                     uint16_t wRxDataRate,
                                     uint16_t wSubcarrier
                                     )
{
    phStatus_t      PH_MEMLOC_REM statusTmp;
    uint16_t        PH_MEMLOC_COUNT wIndex;
    uint8_t         PH_MEMLOC_REM bTxConfig;
    uint8_t         PH_MEMLOC_REM bRxConfig;
    const uint8_t * PH_MEMLOC_REM pTxRegisterSet;
    const uint8_t * PH_MEMLOC_REM pRxRegisterSet;
    uint16_t        PH_MEMLOC_REM wEEAddress;
    uint8_t         PH_MEMLOC_REM bRegAddress;
    uint8_t         PH_MEMLOC_REM bNumBytes;
    uint8_t         PH_MEMLOC_REM bRegister;

    /* No RegisterSet by default */
    pTxRegisterSet = NULL;

    switch (pDataParams->bCardType)
    {
    case PHHAL_HW_CARDTYPE_ISO14443A:

        switch (wTxDataRate)
        {
        case PHHAL_HW_RF_DATARATE_106:
            bTxConfig = PHHAL_HW_RC663_RXTX_I14443A_106;
            pTxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I14443A_106;
            break;
        case PHHAL_HW_RF_DATARATE_212:
            bTxConfig = PHHAL_HW_RC663_RXTX_I14443A_212;
            pTxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I14443A_212;
            break;
        case PHHAL_HW_RF_DATARATE_424:
            bTxConfig = PHHAL_HW_RC663_RXTX_I14443A_424;
            pTxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I14443A_424;
            break;
        case PHHAL_HW_RF_DATARATE_848:
            bTxConfig = PHHAL_HW_RC663_RXTX_I14443A_848;
            pTxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I14443A_848;
            break;
        default:
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        switch (wRxDataRate)
        {
        case PHHAL_HW_RF_DATARATE_106:
            bRxConfig = PHHAL_HW_RC663_RXTX_I14443A_106;
            pRxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I14443A_106;
            break;
        case PHHAL_HW_RF_DATARATE_212:
            bRxConfig = PHHAL_HW_RC663_RXTX_I14443A_212;
            pRxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I14443A_212;
            break;
        case PHHAL_HW_RF_DATARATE_424:
            bRxConfig = PHHAL_HW_RC663_RXTX_I14443A_424;
            pRxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I14443A_424;
            break;
        case PHHAL_HW_RF_DATARATE_848:
            bRxConfig = PHHAL_HW_RC663_RXTX_I14443A_848;
            pRxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I14443A_848;
            break;
        default:
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }
        break;

    case PHHAL_HW_CARDTYPE_ISO14443B:

        switch (wTxDataRate)
        {
        case PHHAL_HW_RF_DATARATE_106:
            bTxConfig = PHHAL_HW_RC663_RXTX_I14443B_106;
            pTxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I14443B_106;
            break;
        case PHHAL_HW_RF_DATARATE_212:
            bTxConfig = PHHAL_HW_RC663_RXTX_I14443B_212;
            pTxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I14443B_212;
            break;
        case PHHAL_HW_RF_DATARATE_424:
            bTxConfig = PHHAL_HW_RC663_RXTX_I14443B_424;
            pTxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I14443B_424;
            break;
        case PHHAL_HW_RF_DATARATE_848:
            bTxConfig = PHHAL_HW_RC663_RXTX_I14443B_848;
            pTxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I14443B_848;
            break;
        default:
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        switch (wRxDataRate)
        {
        case PHHAL_HW_RF_DATARATE_106:
            bRxConfig = PHHAL_HW_RC663_RXTX_I14443B_106;
            pRxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I14443B_106;
            break;
        case PHHAL_HW_RF_DATARATE_212:
            bRxConfig = PHHAL_HW_RC663_RXTX_I14443B_212;
            pRxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I14443B_212;
            break;
        case PHHAL_HW_RF_DATARATE_424:
            bRxConfig = PHHAL_HW_RC663_RXTX_I14443B_424;
            pRxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I14443B_424;
            break;
        case PHHAL_HW_RF_DATARATE_848:
            bRxConfig = PHHAL_HW_RC663_RXTX_I14443B_848;
            pRxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I14443B_848;
            break;
        default:
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }
        break;

    case PHHAL_HW_CARDTYPE_FELICA:

        /* Felica only supports symmetric baudrates */
        if (wTxDataRate != wRxDataRate)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        /* No additional register set for RX */
        pRxRegisterSet = NULL;

        switch (wTxDataRate)
        {
        case PHHAL_HW_RF_DATARATE_212:
            bTxConfig = PHHAL_HW_RC663_RXTX_FELICA_212;
            bRxConfig = PHHAL_HW_RC663_RXTX_FELICA_212;
            pTxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_Felica_212;
            break;
        case PHHAL_HW_RF_DATARATE_424:
            bTxConfig = PHHAL_HW_RC663_RXTX_FELICA_424;
            bRxConfig = PHHAL_HW_RC663_RXTX_FELICA_424;
            pTxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_Felica_424;
            break;
        default:
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }
        break;

    case PHHAL_HW_CARDTYPE_ISO15693:

        /* No additional register set for TX */
        pTxRegisterSet = NULL;

        switch (wTxDataRate)
        {
        case PHHAL_HW_RF_TX_DATARATE_1_OUT_OF_256:
            bTxConfig = PHHAL_HW_RC663_RXTX_I15693_1OO256;
            break;
        case PHHAL_HW_RF_TX_DATARATE_1_OUT_OF_4:
            bTxConfig = PHHAL_HW_RC663_RXTX_I15693_1OO4;
            break;
        default:
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        switch (wRxDataRate)
        {
        case PHHAL_HW_RF_RX_DATARATE_HIGH:
            if (wSubcarrier == PHHAL_HW_SUBCARRIER_SINGLE)
            {
                bRxConfig = PHHAL_HW_RC663_RXTX_I15693_HIGH_SSC;
            }
            else if (wSubcarrier == PHHAL_HW_SUBCARRIER_DUAL)
            {
                bRxConfig = PHHAL_HW_RC663_RXTX_I15693_HIGH_DSC;
            }
            else
            {
                return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
            }
            pRxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I15693_High;
            break;
        case PHHAL_HW_RF_RX_DATARATE_FAST_HIGH:
            bRxConfig = PHHAL_HW_RC663_RXTX_I15693_FAST;
            pRxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I15693_Fast_High;
            break;
        case PHHAL_HW_RF_RX_DATARATE_LOW:
        case PHHAL_HW_RF_RX_DATARATE_FAST_LOW:
            return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_HAL);
        default:
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }
        break;

    case PHHAL_HW_CARDTYPE_ICODEEPCUID:

        /* No additional register set for RX */
        pRxRegisterSet = NULL;

        if ((wTxDataRate == PHHAL_HW_RF_DATARATE_EPCUID) && (wRxDataRate == PHHAL_HW_RF_DATARATE_EPCUID))
        {
            bTxConfig = PHHAL_HW_RC663_RXTX_EPC_UID;
            bRxConfig = PHHAL_HW_RC663_RXTX_EPC_UID;
            pTxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_EpcUid;
        }
        else
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }
        break;

    case PHHAL_HW_CARDTYPE_I18000P3M3:

        /* Datarate check */
        if (wTxDataRate != PHHAL_HW_RF_TX_DATARATE_I18000P3M3)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        /* Subcarrier check */
        if ((wSubcarrier != PHHAL_HW_SUBCARRIER_DUAL) &&
            (wSubcarrier != PHHAL_HW_SUBCARRIER_QUAD))
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        /* No additional register set for TX */
        pTxRegisterSet = NULL;

        bTxConfig = PHHAL_HW_RC663_RXTX_I18000P3M3_DS_M2;

        switch (wRxDataRate)
        {
        case PHHAL_HW_RF_RX_DATARATE_I18000P3M3_MAN2:
            if (wSubcarrier == PHHAL_HW_SUBCARRIER_DUAL)
            {
                bRxConfig = PHHAL_HW_RC663_RXTX_I18000P3M3_DS_M2;
                pRxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I18000p3m3_DSM2;
            }
            else
            {
                bRxConfig = PHHAL_HW_RC663_RXTX_I18000P3M3_QS_M2;
                pRxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I18000p3m3_QSM2;
            }
            break;
        case PHHAL_HW_RF_RX_DATARATE_I18000P3M3_MAN4:
            if (wSubcarrier == PHHAL_HW_SUBCARRIER_DUAL)
            {
                bRxConfig = PHHAL_HW_RC663_RXTX_I18000P3M3_DS_M4;
                pRxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I18000p3m3_DSM4;
            }
            else
            {
                bRxConfig = PHHAL_HW_RC663_RXTX_I18000P3M3_QS_M4;
                pRxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I18000p3m3_QSM4;
            }
            break;
        default:
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }
        break;

    case PHHAL_HW_CARDTYPE_I18092MPI:

        /* TX-Datarate evaluation */
        switch (wTxDataRate)
        {
        case PHHAL_HW_RF_DATARATE_106:
            bTxConfig = PHHAL_HW_RC663_RXTX_I14443A_106;
            pTxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I14443A_106;
            break;
        case PHHAL_HW_RF_DATARATE_212:
            bTxConfig = PHHAL_HW_RC663_RXTX_FELICA_212;
            pTxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_Felica_212;
            break;
        case PHHAL_HW_RF_DATARATE_424:
            bTxConfig = PHHAL_HW_RC663_RXTX_FELICA_424;
            pTxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_Felica_424;
            break;
        default:
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        /* RX-Datarate evaluation */
        switch (wRxDataRate)
        {
        case PHHAL_HW_RF_DATARATE_106:
            bRxConfig = PHHAL_HW_RC663_RXTX_I14443A_106;
            pRxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_I14443A_106;
            break;
        case PHHAL_HW_RF_DATARATE_212:
            bRxConfig = PHHAL_HW_RC663_RXTX_FELICA_212;
            pRxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_Felica_212;
            break;
        case PHHAL_HW_RF_DATARATE_424:
            bRxConfig = PHHAL_HW_RC663_RXTX_FELICA_424;
            pRxRegisterSet = (const uint8_t*)gkphhalHw_Rc663_Felica_424;
            break;
        default:
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }
        break;

    default:

        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Perform LoadProtocol */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_Cmd_LoadProtocol(
        pDataParams,
        bTxConfig,
        bRxConfig));

    /* Apply RegisterSet using LoadReg */
    if (pDataParams->bLoadRegMode != PH_OFF)
    {
        /* Retrieve LoadReg parameters */
        wEEAddress  = (uint16_t)pDataParams->pLoadRegConfig[0] << 8;
        wEEAddress |= (uint16_t)pDataParams->pLoadRegConfig[1];
        bRegAddress = pDataParams->pLoadRegConfig[2];
        bNumBytes   = pDataParams->pLoadRegConfig[3];

        /* Perform LoadReg */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_Cmd_LoadReg(
            pDataParams,
            wEEAddress,
            bRegAddress,
            bNumBytes));
    }
    /* Apply RegisterSet using library register set */
    else
    {
        /* Apply all registers */
        for (wIndex = 0; wIndex < sizeof(gkphhalHw_Rc663_Registers); ++wIndex)
        {
            /* TX register set is valid */
            if (pTxRegisterSet)
            {
                /* Initially take everything from TX register set */
                bRegister = pTxRegisterSet[wIndex];

                /* RX register set is also valid */
                if (pRxRegisterSet)
                {
                    switch (gkphhalHw_Rc663_Registers[wIndex])
                    {
                        /* Take the following registers from the RX register set */
                    case PHHAL_HW_RC663_REG_RXCRCCON:
                    case PHHAL_HW_RC663_REG_RXSOFD:
                    case PHHAL_HW_RC663_REG_RXCTRL:
                    case PHHAL_HW_RC663_REG_RXWAIT:
                    case PHHAL_HW_RC663_REG_RXTHRESHOLD:
                    case PHHAL_HW_RC663_REG_RCV:
                    case PHHAL_HW_RC663_REG_RXANA:
                        bRegister = pRxRegisterSet[wIndex];
                        break;
                    default:
                        break;
                    }
                }
            }
            /* ONLY RX register set is valid */
            else if (pRxRegisterSet)
            {
                /* Take everything from RX register set */
                bRegister = pRxRegisterSet[wIndex];
            }
            /* At least one register set is mandatory */
            else
            {
                return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
            }

            /* Preserve TxEn bit in DrvMode register */
            if (gkphhalHw_Rc663_Registers[wIndex] == PHHAL_HW_RC663_REG_DRVMODE)
            {
                /* Read out DrvMode register */
                PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_DRVMODE, &bTxConfig));

                /* Preserve TxEn bit, take other bits from register set */
                bRegister = (bTxConfig & PHHAL_HW_RC663_BIT_TXEN) | (bRegister & (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_TXEN);
            }

            /* Actual write to register */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(
                pDataParams,
                gkphhalHw_Rc663_Registers[wIndex],
                bRegister));
        }

        /* Restore ASK 100 Setting */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetConfig_Int(pDataParams, PHHAL_HW_CONFIG_ASK100, pDataParams->wCfgShadow[PHHAL_HW_CONFIG_ASK100]));

        /* A change in the bitrate also affects TxWait */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetTxWait(pDataParams, pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXWAIT_US]));
    }

    /* Update Datarate in shadow for parity setting */
    pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXDATARATE] = wTxDataRate;
    pDataParams->wCfgShadow[PHHAL_HW_CONFIG_RXDATARATE] = wRxDataRate;

    /* Apply Parity settings from Shadow */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetConfig_Int(pDataParams, PHHAL_HW_CONFIG_PARITY, pDataParams->wCfgShadow[PHHAL_HW_CONFIG_PARITY]));

    /* Apply Tx-CRC settings from Shadow */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetConfig_Int(pDataParams, PHHAL_HW_CONFIG_TXCRC, pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXCRC]));

    /* Apply Rx-CRC settings from Shadow */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetConfig_Int(pDataParams, PHHAL_HW_CONFIG_RXCRC, pDataParams->wCfgShadow[PHHAL_HW_CONFIG_RXCRC]));

    /* Apply TxLastBits settings from Shadow */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_SetConfig_Int(pDataParams, PHHAL_HW_CONFIG_TXLASTBITS, pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXLASTBITS]));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_SetConfig_Int(
                                       phhalHw_Rc663_DataParams_t * pDataParams,
                                       uint16_t wConfig,
                                       uint16_t wValue
                                       )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bValue;
    uint8_t     PH_MEMLOC_REM bRegister;

    switch (wConfig)
    {
    case PHHAL_HW_CONFIG_PARITY:

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_FRAMECON, &bRegister));

        /* Special Handling for I18092MPI */
        if (pDataParams->bCardType == PHHAL_HW_CARDTYPE_I18092MPI)
        {
            /* In case nothing changes... */
            bValue = bRegister;

            /* Tx-Parity is only applicable for 106kBit/s */
            if (pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXDATARATE] == PHHAL_HW_RF_DATARATE_106)
            {
                /* Tx-Parity is OFF */
                if (wValue == PH_OFF)
                {
                    bValue = bRegister & (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_TXPARITYEN;
                }
                /* Tx-Parity is ON */
                else
                {
                    bValue = bRegister | PHHAL_HW_RC663_BIT_TXPARITYEN;
                }
            }

            /* Rx-Parity is only applicable for 106kBit/s */
            if (pDataParams->wCfgShadow[PHHAL_HW_CONFIG_RXDATARATE] == PHHAL_HW_RF_DATARATE_106)
            {
                /* Tx-Parity is OFF */
                if (wValue == PH_OFF)
                {
                    bValue = bRegister & (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_RXPARITYEN;
                }
                /* Tx-Parity is ON */
                else
                {
                    bValue = bRegister | PHHAL_HW_RC663_BIT_RXPARITYEN;
                }
            }
        }
        /* All other protocols */
        else
        {
            /* Parity is OFF */
            if (wValue == PH_OFF)
            {
                bValue = bRegister & (uint8_t)~(uint8_t)(PHHAL_HW_RC663_BIT_TXPARITYEN | PHHAL_HW_RC663_BIT_RXPARITYEN);
            }
            /* Parity is ON */
            else
            {
                bValue = bRegister | PHHAL_HW_RC663_BIT_TXPARITYEN | PHHAL_HW_RC663_BIT_RXPARITYEN;
            }
        }

        /* Only perform the operation, if the new value is different */
        if (bValue != bRegister)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_FRAMECON, bValue));
        }
        break;

    case PHHAL_HW_CONFIG_TXCRC:

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_TXCRCCON, &bRegister));

        if (wValue == PH_OFF)
        {
            bValue = bRegister & (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_CRCEN;
        }
        else
        {
            /* Set CRC-16 for I18000p3m3 */
            if (pDataParams->bCardType == PHHAL_HW_CARDTYPE_I18000P3M3)
            {
                bValue = PHHAL_HW_RC663_I18000P3M3_CRC_TYPE_PRESET;
            }
            else
            {
                bValue = bRegister;
            }

            /* Enable CRC */
            bValue |= PHHAL_HW_RC663_BIT_CRCEN;
        }

        /* Only perform the operation, if the new value is different */
        if (bValue != bRegister)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_TXCRCCON, bValue));
        }
        break;

    case PHHAL_HW_CONFIG_RXCRC:

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_RXCRCCON, &bRegister));

        if (wValue == PH_OFF)
        {
            bValue = bRegister & (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_CRCEN;
        }
        else
        {
            /* Set CRC-16 for I18000p3m3 */
            if (pDataParams->bCardType == PHHAL_HW_CARDTYPE_I18000P3M3)
            {
                bValue = PHHAL_HW_RC663_I18000P3M3_CRC_TYPE_PRESET;
            }
            else
            {
                bValue = bRegister;
            }

            /* Enable CRC */
            bValue |= PHHAL_HW_RC663_BIT_CRCEN;
        }

        /* Only perform the operation, if the new value is different */
        if (bValue != bRegister)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_RXCRCCON, bValue));
        }
        break;

    case PHHAL_HW_CONFIG_TXLASTBITS:

        /* check parameter */
        if (wValue > PHHAL_HW_RC663_MASK_TXLASTBITS)
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }

        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_TXDATANUM, &bRegister));
        bRegister &= (uint8_t)~(uint8_t)PHHAL_HW_RC663_MASK_TXLASTBITS;
        bRegister |= (uint8_t)wValue;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_TXDATANUM, bRegister));
        break;

    case PHHAL_HW_CONFIG_ASK100:

        /* Read out DrvMode register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_DRVMODE, &bRegister));

        /* Clear ClkMode bits */
        bValue = bRegister & (uint8_t)~(uint8_t)(PHHAL_HW_RC663_BIT_RFON | PHHAL_HW_RC663_BIT_TPUSHON | PHHAL_HW_RC663_BIT_TPULLON);

        /* Update DrvMode register */
        if (wValue == PH_OFF)
        {
            bValue |= PHHAL_HW_RC663_BIT_RFON | PHHAL_HW_RC663_BIT_TPUSHON | PHHAL_HW_RC663_BIT_TPULLON;
        }
        else
        {
            if (pDataParams->bCardType == PHHAL_HW_CARDTYPE_ISO14443A)
            {
                switch (pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXDATARATE])
                {
                case PHHAL_HW_RF_DATARATE_106:
                    bValue |= gkphhalHw_Rc663_I14443A_106[0] & (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_TXEN;
                    break;
                case PHHAL_HW_RF_DATARATE_212:
                    bValue |= gkphhalHw_Rc663_I14443A_212[0] & (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_TXEN;
                    break;
                case PHHAL_HW_RF_DATARATE_424:
                    bValue |= gkphhalHw_Rc663_I14443A_424[0] & (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_TXEN;
                    break;
                case PHHAL_HW_RF_DATARATE_848:
                    bValue |= gkphhalHw_Rc663_I14443A_848[0] & (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_TXEN;
                    break;
                default:
                    return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
                }
            }
            else
            {
                /* I18092 MPI @ 106 */
                if ((pDataParams->bCardType == PHHAL_HW_CARDTYPE_I18092MPI) &&
                    (pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXDATARATE]) == PHHAL_HW_RF_DATARATE_106)
                {
                    bValue |= gkphhalHw_Rc663_I14443A_106[0] & (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_TXEN;
                }
                /* Default: Outputs switch to Z: M1 and M2 are off */
                else
                {
                    bValue |= PHHAL_HW_RC663_BIT_TPULLON;
                }
            }
        }

        /* Only perform the operation, if the new value is different */
        if (bValue != bRegister)
        {
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_DRVMODE, bValue));
        }
        break;

    default:
        return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_SetRxWait(
                                   phhalHw_Rc663_DataParams_t * pDataParams,
                                   uint16_t wTimeEtu
                                   )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bRegister;
    uint16_t    PH_MEMLOC_REM wDataRate;

    /* Retrieve Rx-Datarate */
    wDataRate = pDataParams->wCfgShadow[PHHAL_HW_CONFIG_RXDATARATE];

    /* Since we use DBFREQ*2, we need to adjust the value for ETU granularity */
    switch (wDataRate)
    {
        /* DBFREQ*2 = 1/2 ETU */
    case PHHAL_HW_RF_DATARATE_106:
    case PHHAL_HW_RF_DATARATE_212:
    case PHHAL_HW_RF_DATARATE_424:
    case PHHAL_HW_RF_DATARATE_848:
        /* DBFREQ*2 = 53KHz*2 = 106KHz = 1/2 ETU */
    case PHHAL_HW_RF_RX_DATARATE_FAST_HIGH:
        /* parameter check */
        if (wTimeEtu > (PHHAL_HW_RC663_MASK_RXWAIT >> 1))
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }
        wTimeEtu <<= 1;
        break;
        /* DBFREQ*2 = 53KHz*2 = 106KHz = 1/4 ETU */
    case PHHAL_HW_RF_RX_DATARATE_HIGH:
        /* DBFREQ*2 = 106KHz*2 = 212KHz = 1/4 ETU (RX ETUs have half duration (18.88us) than TX ETUs) */
    case PHHAL_HW_RF_DATARATE_EPCUID:
        /* parameter check */
        if (wTimeEtu > (PHHAL_HW_RC663_MASK_RXWAIT >> 2))
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }
        wTimeEtu <<= 2;
        break;
        /* DBFREQ*2 = 1/2 ETU */
    case PHHAL_HW_RF_RX_DATARATE_I18000P3M3_MAN2:
    case PHHAL_HW_RF_RX_DATARATE_I18000P3M3_MAN4:
        /* parameter check */
        if (wTimeEtu > (PHHAL_HW_RC663_MASK_RXWAIT >> 1))
        {
            return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
        }
        wTimeEtu <<= 1;
        break;
    default:
        return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
    }

    /* set the RxWait register  */
    bRegister = PHHAL_HW_RC663_BIT_RXWAITDBFREQ | (uint8_t)wTimeEtu;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_RXWAIT, bRegister));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_SetTxWait(
                                   phhalHw_Rc663_DataParams_t * pDataParams,
                                   uint16_t wTimeUs
                                   )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bRegister;
    float32_t   PH_MEMLOC_REM fTime;
    uint16_t    PH_MEMLOC_REM wDataRate;

    /* Retrieve Tx-Datarate */
    wDataRate = pDataParams->wCfgShadow[PHHAL_HW_CONFIG_TXDATARATE];

    /* Since we use DBFREQ*2, we need to adjust the value for ETU granularity */
    switch (wDataRate)
    {
        /* DBFREQ*2 = 1/2 ETU */
    case PHHAL_HW_RF_DATARATE_106:
    case PHHAL_HW_RF_DATARATE_212:
    case PHHAL_HW_RF_DATARATE_424:
    case PHHAL_HW_RF_DATARATE_848:
        fTime = ((float32_t)wDataRate + 1.0f) * (PHHAL_HW_RC663_ETU_I14443 / 2.0f);
        break;
        /* DBFREQ*2 = 53KHz*2 = 106KHz = 1/4 ETU */
    case PHHAL_HW_RF_TX_DATARATE_1_OUT_OF_256:
    case PHHAL_HW_RF_TX_DATARATE_1_OUT_OF_4:
        fTime = PHHAL_HW_RC663_ETU_I15693 / 4.0f;
        break;
        /* DBFREQ*2 = 106KHz*2 = 212KHz = 1/8 ETU */
    case PHHAL_HW_RF_DATARATE_EPCUID:
        fTime = PHHAL_HW_RC663_ETU_EPCUID / 8.0f;
        break;
    case PHHAL_HW_RF_TX_DATARATE_I18000P3M3:
        fTime = PHHAL_HW_RC663_ETU_EPCUID / 8.0f;
        break;
    default:
        return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
    }

    /* perform calculation [value] / [timer granularity] */
    fTime = (float32_t)wTimeUs / fTime;
    wTimeUs = (uint16_t)fTime;
    if ((float32_t)wTimeUs < fTime)
    {
        ++wTimeUs;
    }

    /* remove digital circutry delay */
    if (wTimeUs > PHHAL_HW_RC663_DIGI_DELAY_TXWAIT_DBFREQ)
    {
        wTimeUs = wTimeUs - PHHAL_HW_RC663_DIGI_DELAY_TXWAIT_DBFREQ;
    }
    else
    {
        wTimeUs = 0;
    }

    /* check parameter */
    if (wTimeUs > 0x7FF)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* Read TxWaitControl register*/
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_TXWAITCTRL, &bRegister));

    /* Set TxWait configuration */
    bRegister |= PHHAL_HW_RC663_BIT_TXWAIT_START_RX | PHHAL_HW_RC663_BIT_TXWAIT_DBFREQ;

    /* Set the 3 MSBits */
    bRegister &= (uint8_t)~(uint8_t)PHHAL_HW_RC663_MASK_TXWAITHI;
    bRegister |= (uint8_t)((wTimeUs >> 5) & PHHAL_HW_RC663_MASK_TXWAITHI);

    /* Write changed register */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_TXWAITCTRL, bRegister));

    /* Set the 8 LSBs */
    bRegister = (uint8_t)wTimeUs;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_TXWAITLO, bRegister));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_SetFdt(
                                phhalHw_Rc663_DataParams_t * pDataParams,
                                uint8_t bUnit,
                                uint16_t wTimeout
                                )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t    PH_MEMLOC_REM wT0Reload;
    uint16_t    PH_MEMLOC_REM wT1Reload;
    float32_t   PH_MEMLOC_REM fTime;
    uint16_t    PH_MEMLOC_REM wDelay;

    /* Calculate values for Microsecond values */
    if (bUnit == PHHAL_HW_TIME_MICROSECONDS)
    {
        /* Retrieve and add digital delay */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_GetDigiDelay(pDataParams, PH_ON, &wDelay));
        fTime = (float32_t)wTimeout + (float32_t)wDelay;

        /* Timeout can be realized with just one timer */
        if (!((fTime * PHHAL_HW_RC663_TIMER0_FREQ) > (float32_t)PHHAL_HW_RC663_TIMER_RELOAD_MAX))
        {
            fTime = fTime * PHHAL_HW_RC663_TIMER0_FREQ;
            wT0Reload = (uint16_t)fTime;

            /* Since timer IRQ is raised at underflow, wReload has to decremented by one.
            However, if the resulting reload value has commas, it must be 'ceiled' */
            if (!(fTime > (float32_t)wT0Reload))
            {
                --wT0Reload;
            }

            /* No timer 1 */
            wT1Reload = 0x0000;
        }
        /* If not, set prescaler to 1 ETU */
        else
        {
            /* T0 Overflow occurs at exactly 1 ETU (from ISO14443 protocol @ 106) */
            wT0Reload = (uint16_t)(PHHAL_HW_RC663_TIMER0_FREQ * PHHAL_HW_RC663_ETU_I14443);

            /* T1 reload is the given value divided by the prescaler T0 frequency */
            fTime = fTime / PHHAL_HW_RC663_ETU_I14443;
            wT1Reload = (uint16_t)fTime;

            /* Since timer IRQ is raised at underflow, wReload has to decremented by one.
            However, if the resulting reload value has commas, it must be 'ceiled' */
            if (!(fTime > (float32_t)wT1Reload))
            {
                --wT1Reload;
            }
        }
    }
    /* Calculate values for Millisecond values */
    else
    {
        /* T0 overflow occurs every millisecond */
        wT0Reload = (uint16_t)(1000.0f * PHHAL_HW_RC663_TIMER0_FREQ);

        /* T1 reload matches exactly the given value */
        wT1Reload = ((wTimeout > 0) ? --wTimeout : wTimeout);
    }

    /* Write T0 reload value */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T0RELOADHI, (uint8_t)(wT0Reload >> 8)));
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T0RELOADLO, (uint8_t)(wT0Reload)));

    /* Write T1 reload value */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T1RELOADHI, (uint8_t)(wT1Reload >> 8)));
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_T1RELOADLO, (uint8_t)(wT1Reload)));

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_GetFdt(
                                phhalHw_Rc663_DataParams_t * pDataParams,
                                phStatus_t wExchangeStatus,
                                uint32_t * pTime
                                )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bRegister;
    uint16_t    PH_MEMLOC_REM wT0Reload;
    uint16_t    PH_MEMLOC_REM wT1Reload;
    uint16_t    PH_MEMLOC_REM wT0Value;
    uint16_t    PH_MEMLOC_REM wT1Value;
    float32_t   PH_MEMLOC_REM fTime;
    uint16_t    PH_MEMLOC_REM wDelay;

    /* Get T0 reload value */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_T0RELOADHI, &bRegister));
    wT0Reload = (uint16_t)bRegister << 8;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_T0RELOADLO, &bRegister));
    wT0Reload |= (uint16_t)bRegister;

    /* Get T1 reload value */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_T1RELOADHI, &bRegister));
    wT1Reload = (uint16_t)bRegister << 8;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_T1RELOADLO, &bRegister));
    wT1Reload |= (uint16_t)bRegister;

    /* Get T0 counter value */
    if ((wExchangeStatus & PH_ERR_MASK) != PH_ERR_IO_TIMEOUT)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_T0COUNTERVALHI, &bRegister));
        wT0Value = (uint16_t)bRegister << 8;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_T0COUNTERVALLO, &bRegister));
        wT0Value |= (uint16_t)bRegister;
    }
    else
    {
        wT0Value = 0;
    }

    /* Get T1 counter value */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_T1COUNTERVALHI, &bRegister));
    wT1Value = (uint16_t)bRegister << 8;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_T1COUNTERVALLO, &bRegister));
    wT1Value |= (uint16_t)bRegister;

    /* Subtract reload- and counter values */
    wT0Value = wT0Reload - wT0Value;
    wT1Value = wT1Reload - wT1Value;

    /*
    Now we can calculate the time in microseconds according to the following formular:
    {
    time[us] = (wT1Value * (1 / (PHHAL_HW_RC663_TIMER0_FREQ / wT0Reload))) + (wT0Value * (1 / PHHAL_HW_RC663_TIMER0_FREQ))
    }
    */
    fTime = (float32_t)wT1Value / (PHHAL_HW_RC663_TIMER0_FREQ / (float32_t)wT0Reload);
    fTime = fTime + ((float32_t)wT0Value / PHHAL_HW_RC663_TIMER0_FREQ);

    /* Return the value */
    *pTime = (uint32_t)fTime;
    if ((float32_t)*pTime < fTime)
    {
        ++(*pTime);
    }

    /* Retrieve and subtract digital delay */
    if ((wExchangeStatus & PH_ERR_MASK) != PH_ERR_IO_TIMEOUT)
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_GetDigiDelay(pDataParams, PH_OFF, &wDelay));
        *pTime = *pTime - wDelay;
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_GetTxBuffer(
                                     phhalHw_Rc663_DataParams_t * pDataParams,
                                     uint8_t bIsExchange,
                                     uint8_t ** pTxBuffer,
                                     uint16_t * pTxBufferLen,
                                     uint16_t * pTxBufferSize
                                     )
{
    /* Exchange command -> RxBuffer overwriting is allowed */
    if (bIsExchange != PH_OFF)
    {
        /* We need to watch that we do not overwrite content below the RxStartPos though */
        if (pDataParams->pTxBuffer == pDataParams->pRxBuffer)
        {
            *pTxBuffer = &pDataParams->pTxBuffer[pDataParams->wRxBufStartPos];
            *pTxBufferSize = pDataParams->wTxBufSize - pDataParams->wRxBufStartPos;
        }
        /* Else just return the actual Buffer */
        else
        {
            *pTxBuffer = pDataParams->pTxBuffer;
            *pTxBufferSize = pDataParams->wTxBufSize;
        }

        /* Return stored length */
        *pTxBufferLen = pDataParams->wTxBufLen;
    }
    /* Normal command -> do not overwrite Tx- and Rx-Contents */
    else
    {
        /* Redundant code */
        return phhalHw_Rc663_GetRxBuffer(pDataParams, bIsExchange, pTxBuffer, pTxBufferLen, pTxBufferSize);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_GetRxBuffer(
                                     phhalHw_Rc663_DataParams_t * pDataParams,
                                     uint8_t bIsExchange,
                                     uint8_t ** pRxBuffer,
                                     uint16_t * pRxBufferLen,
                                     uint16_t * pRxBufferSize
                                     )
{
    /* Exchange command -> TxBuffer overwriting is allowed */
    if (bIsExchange != PH_OFF)
    {
        *pRxBuffer = &pDataParams->pRxBuffer[pDataParams->wRxBufStartPos];
        *pRxBufferSize = pDataParams->wRxBufSize - pDataParams->wRxBufStartPos;
        *pRxBufferLen = pDataParams->wRxBufLen;
    }
    /* Normal command -> do not overwrite Tx- and Rx-Contents */
    else
    {
        /* Command buffering is NOT supported by this HAL */
        *pRxBufferLen = 0;

        /* TxBuffer equals RxBuffer */
        /* And the buffer contains something that needs to be preserved */
        if ((pDataParams->pTxBuffer == pDataParams->pRxBuffer) &&
            ((pDataParams->wTxBufLen != 0) || (pDataParams->wRxBufStartPos != 0)))
        {
            /* Start at TxLenght if neccessary */
            if ((pDataParams->wRxBufStartPos + pDataParams->wTxBufLen) >= pDataParams->wRxBufStartPos)
            {
                *pRxBuffer = &pDataParams->pTxBuffer[pDataParams->wRxBufStartPos + pDataParams->wTxBufLen];
                *pRxBufferSize = pDataParams->wTxBufSize - (pDataParams->wRxBufStartPos + pDataParams->wTxBufLen);
            }
            /* Else start at wRxBufStartPos */
            else
            {
                *pRxBuffer = &pDataParams->pRxBuffer[pDataParams->wRxBufStartPos];
                *pRxBufferSize = pDataParams->wRxBufSize - pDataParams->wRxBufStartPos;
            }
        }
        /* Buffers are different */
        else
        {
            /* Use TxBuffer if it has more space than RxBuffer */
            if ((pDataParams->wTxBufSize - pDataParams->wTxBufLen) >= (pDataParams->wRxBufSize - pDataParams->wRxBufStartPos))
            {
                *pRxBuffer = &pDataParams->pTxBuffer[pDataParams->wTxBufLen];
                *pRxBufferSize = pDataParams->wTxBufSize - pDataParams->wTxBufLen;
            }
            /* Else use RxBuffer */
            else
            {
                *pRxBuffer = &pDataParams->pRxBuffer[pDataParams->wRxBufStartPos];
                *pRxBufferSize = pDataParams->wRxBufSize - pDataParams->wRxBufStartPos;
            }
        }
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_GetDigiDelay(
                                      phhalHw_Rc663_DataParams_t * pDataParams,
                                      uint8_t bIsTimeout,
                                      uint16_t * pDelayUs
                                      )
{
    uint16_t    PH_MEMLOC_REM wDataRate;
    uint16_t    PH_MEMLOC_REM wSubcarrier;
    uint8_t     PH_MEMLOC_REM bIndex;

    wDataRate = pDataParams->wCfgShadow[PHHAL_HW_CONFIG_RXDATARATE];
    wSubcarrier = pDataParams->wCfgShadow[PHHAL_HW_CONFIG_SUBCARRIER];
    bIndex = pDataParams->bCardType - 1;

    switch (pDataParams->bCardType)
    {
    case PHHAL_HW_CARDTYPE_ISO14443A:
    case PHHAL_HW_CARDTYPE_ISO14443B:
        *pDelayUs = gkphhalHw_Rc663_DigiDelays_Us[bIndex][wDataRate];
        /* In a timeout case we have to add an additional delay */
        if (bIsTimeout != PH_OFF)
        {
            *pDelayUs = *pDelayUs + PHHAL_HW_RC663_I14443_ADD_DELAY_US;
        }
        break;
    case PHHAL_HW_CARDTYPE_FELICA:
        *pDelayUs = gkphhalHw_Rc663_DigiDelays_Us[bIndex][wDataRate];
        break;
    case PHHAL_HW_CARDTYPE_ISO15693:
        *pDelayUs = gkphhalHw_Rc663_DigiDelays_Us[bIndex][wDataRate - PHHAL_HW_RF_RX_DATARATE_LOW];
        /* In a timeout case we have to add an additional delay */
        if (bIsTimeout != PH_OFF)
        {
            if (wDataRate == PHHAL_HW_RF_RX_DATARATE_HIGH)
            {
                *pDelayUs = *pDelayUs + PHHAL_HW_RC663_I15693_ADD_DELAY_US;
            }
            else
            {
                *pDelayUs = *pDelayUs + (PHHAL_HW_RC663_I15693_ADD_DELAY_US >> 1);
            }
        }
        break;
    case PHHAL_HW_CARDTYPE_ICODEEPCUID:
        *pDelayUs = gkphhalHw_Rc663_DigiDelays_Us[bIndex][0];
        break;
    case PHHAL_HW_CARDTYPE_I18000P3M3:
        switch (wDataRate)
        {
        case PHHAL_HW_RF_RX_DATARATE_I18000P3M3_MAN2:
            if (wSubcarrier == PHHAL_HW_SUBCARRIER_DUAL)
            {
                *pDelayUs = gkphhalHw_Rc663_DigiDelays_Us[bIndex][0];
            }
            else
            {
                *pDelayUs = gkphhalHw_Rc663_DigiDelays_Us[bIndex][2];
            }
            break;
        case PHHAL_HW_RF_RX_DATARATE_I18000P3M3_MAN4:
            if (wSubcarrier == PHHAL_HW_SUBCARRIER_DUAL)
            {
                *pDelayUs = gkphhalHw_Rc663_DigiDelays_Us[bIndex][1];
            }
            else
            {
                *pDelayUs = gkphhalHw_Rc663_DigiDelays_Us[bIndex][3];
            }
            break;
        default:
            return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
        }
        break;
    case PHHAL_HW_CARDTYPE_I18092MPI:
        *pDelayUs = gkphhalHw_Rc663_DigiDelays_Us[bIndex][wDataRate];
        /* In a timeout case we have to add an additional delay */
        if ((wDataRate == PHHAL_HW_RF_DATARATE_106) && (bIsTimeout != PH_OFF))
        {
            *pDelayUs = *pDelayUs + PHHAL_HW_RC663_I14443_ADD_DELAY_US;
        }
        break;
    default:
        return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_MfcAuthenticate_Int(
    phhalHw_Rc663_DataParams_t * pDataParams,
    uint8_t bBlockNo,
    uint8_t bKeyType,
    uint8_t * pUid
    )
{
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint8_t     PH_MEMLOC_REM bRegister;
    uint8_t     PH_MEMLOC_REM bIrq0WaitFor;
    uint8_t     PH_MEMLOC_REM bIrq1WaitFor;
    uint8_t     PH_MEMLOC_REM aTxBuffer[6];

    /* set keytype and keynumber */
    if (bKeyType == PHHAL_HW_MFC_KEYA)
    {
        aTxBuffer[0] = PHHAL_HW_RC663_MFC_AUTHA_CMD;
    }
    else if (bKeyType == PHHAL_HW_MFC_KEYB)
    {
        aTxBuffer[0] = PHHAL_HW_RC663_MFC_AUTHB_CMD;
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_HAL);
    }

    /* set block number */
    aTxBuffer[1] = bBlockNo;

    /* set serial number */
    memcpy(&aTxBuffer[2], pUid, 4);  /* PRQA S 3200 */

    /* Set wait IRQs */
    bIrq0WaitFor = PHHAL_HW_RC663_BIT_RXIRQ;
    bIrq1WaitFor = PHHAL_HW_RC663_BIT_TIMER1IRQ;

    /* Execute Authenticate command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_Command_Int(
        pDataParams,
        PHHAL_HW_RC663_CMD_MFAUTHENT,
        PH_EXCHANGE_DEFAULT,
        bIrq0WaitFor,
        bIrq1WaitFor,
        aTxBuffer,
        6,
        0,
        NULL,
        NULL));

    /* Check auth success */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_STATUS, &bRegister));
    if (!(bRegister & PHHAL_HW_RC663_BIT_CRYPTO1ON))
    {
        return PH_ADD_COMPCODE(PH_ERR_AUTH_ERROR, PH_COMP_HAL);
    }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_HAL);
}

phStatus_t phhalHw_Rc663_Command_Int(
                                     phhalHw_Rc663_DataParams_t * pDataParams,
                                     uint8_t bCmd,
                                     uint16_t wOption,
                                     uint8_t bIrq0WaitFor,
                                     uint8_t bIrq1WaitFor,
                                     uint8_t * pTxBuffer,
                                     uint16_t wTxLength,
                                     uint16_t wRxBufferSize,
                                     uint8_t * pRxBuffer,
                                     uint16_t * pRxLength
                                     )
{
    phStatus_t  PH_MEMLOC_REM status;
    phStatus_t  PH_MEMLOC_REM statusTmp;
    uint16_t    PH_MEMLOC_REM wFifoBytes;
    uint8_t     PH_MEMLOC_REM bIrq0Reg = 0x00;
    uint8_t     PH_MEMLOC_REM bIrq1Reg = 0x00;
    uint8_t     PH_MEMLOC_REM bWaitIrqEn;
    uint8_t     PH_MEMLOC_REM bWaitIrqPowerDownCheck;
    uint8_t     PH_MEMLOC_REM bRegister;
    uint8_t     PH_MEMLOC_REM bCmdNoWrite;
    uint8_t     PH_MEMLOC_REM bError;
    uint8_t *   PH_MEMLOC_REM pTmpBuffer;
    uint16_t    PH_MEMLOC_REM wTmpBufferSize;

    /* Check option byte, buffering is not allowed */
    if ((wOption & PH_EXCHANGE_BUFFERED_BIT) || (wOption & PH_EXCHANGE_LEAVE_BUFFER_BIT))
    {
        return PH_ADD_COMPCODE(PH_ERR_INTERNAL_ERROR, PH_COMP_HAL);
    }

    /* For these commands it is not allowed to write to registers during execution */
    if ((bCmd & PHHAL_HW_RC663_BIT_STANDBY) ||
        (bCmd == PHHAL_HW_RC663_CMD_LOADREG) ||
        (bCmd == PHHAL_HW_RC663_CMD_LOADPROTOCOL) ||
        (bCmd == PHHAL_HW_RC663_CMD_SOFTRESET))
    {
        bCmdNoWrite = PH_ON;
    }
    else
    {
        bCmdNoWrite = PH_OFF;
    }

    /* reset received length */
    if (pRxLength != NULL)
    {
        *pRxLength = 0;
    }

    /* Evaluate temporary buffer */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_GetRxBuffer(pDataParams, PH_OFF, &pTmpBuffer, &wFifoBytes, &wTmpBufferSize));

    /* Check for buffer overflow */
    if (wTxLength > wTmpBufferSize)
    {
        return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
    }

    /* always wait for idle interrupt */
    bIrq0WaitFor |= PHHAL_HW_RC663_BIT_IDLEIRQ;

    /* Terminate a probably running command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_COMMAND, PHHAL_HW_RC663_CMD_IDLE));

    /* Flush FiFo */
    if (!(wOption & PHHAL_HW_RC663_OPTION_FIFO_NOCLEAR))
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_FlushFifo(pDataParams));
    }

    /* clear all IRQ0 flags */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(
        pDataParams,
        PHHAL_HW_RC663_REG_IRQ0,
        (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_SET));

    /* clear all IRQ1 flags */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(
        pDataParams,
        PHHAL_HW_RC663_REG_IRQ1,
        (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_SET));

    /* write data into FIFO */
    if (wTxLength)
    {
        /* Buffer the data into the temporary buffer */
        memcpy(pTmpBuffer, pTxBuffer, wTxLength);  /* PRQA S 3200 */

        /* write data to transmit into FiFo buffer */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_WriteFifo(pDataParams, pTmpBuffer, wTxLength, &wFifoBytes));
    }

    /* Enable IRQs now if we're not allowed after starting the command */
    if (bCmdNoWrite)
    {
        /* Enable IRQ0 interrupt sources */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_IRQ0EN, &bRegister));
        bRegister &= PHHAL_HW_RC663_BIT_IRQINV;
        bRegister |= bIrq0WaitFor;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_IRQ0EN, bRegister));

        /* Enable IRQ1 interrupt sources */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_IRQ1EN, &bRegister));
        bRegister &= PHHAL_HW_RC663_BIT_IRQPUSHPULL;
        bRegister |= PHHAL_HW_RC663_BIT_GLOBALIRQ | bIrq1WaitFor;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_IRQ1EN, bRegister));
    }

    /* start timer manually if requested */
    if (wOption & PHHAL_HW_RC663_OPTION_RXTX_TIMER_START)
    {
        /* retrieve content of Timer Control register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_TCONTROL, &bRegister));
        /* manually start T0 */
        bRegister |= PHHAL_HW_RC663_BIT_T0STARTSTOPNOW | PHHAL_HW_RC663_BIT_T0RUNNING;
        /* manually start T1 */
        bRegister |= PHHAL_HW_RC663_BIT_T1STARTSTOPNOW | PHHAL_HW_RC663_BIT_T1RUNNING;
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_TCONTROL, bRegister));
    }

    /* start the command */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_COMMAND, bCmd));

    /* wait until the command is finished */
    bWaitIrqEn = (bCmdNoWrite != PH_OFF) ? PH_OFF : PH_ON;
    bWaitIrqPowerDownCheck = ((bCmd == PHHAL_HW_RC663_CMD_SOFTRESET) || (bCmd & PHHAL_HW_RC663_BIT_STANDBY)) ? PH_ON : PH_OFF;
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_WaitIrq(
        pDataParams,
        bWaitIrqEn,
        bWaitIrqPowerDownCheck,
        bIrq0WaitFor,
        bIrq1WaitFor,
        &bIrq0Reg,
        &bIrq1Reg));

    /* Timeout handling */
    if ((bIrq1WaitFor & PHHAL_HW_RC663_BIT_TIMER1IRQ) && (bIrq1Reg & PHHAL_HW_RC663_BIT_TIMER1IRQ))
    {
        /* stop the command */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(
            pDataParams,
            PHHAL_HW_RC663_REG_COMMAND,
            PHHAL_HW_RC663_CMD_IDLE));

        /* Flush FiFo */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_FlushFifo(pDataParams));

        /* retrieve content of Timer Control register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_TCONTROL, &bRegister));

        /* manually stop timers */
        bRegister |= PHHAL_HW_RC663_BIT_T0STARTSTOPNOW | PHHAL_HW_RC663_BIT_T1STARTSTOPNOW;
        bRegister &= (uint8_t)~(uint8_t)(PHHAL_HW_RC663_BIT_T0RUNNING | PHHAL_HW_RC663_BIT_T1RUNNING);
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_TCONTROL, bRegister));

        return PH_ADD_COMPCODE(PH_ERR_IO_TIMEOUT, PH_COMP_HAL);
    }

    /* mask out high-alert */
    bIrq0WaitFor &= (uint8_t)~(uint8_t)PHHAL_HW_RC663_BIT_HIALERTIRQ;

    /* retrieve fifo bytes */
    if ((pRxBuffer != NULL) && (pRxLength != NULL))
    {
        do
        {
            /* retrieve bytes from FiFo */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_ReadFifo(
                pDataParams,
                wTmpBufferSize - *pRxLength,
                &pTmpBuffer[*pRxLength],
                &wFifoBytes));

            /* advance receive buffer */
            *pRxLength = *pRxLength + wFifoBytes;

            /* read interrupt status */
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_IRQ0, &bIrq0Reg));
            PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_IRQ1, &bIrq1Reg));
        }
        while ((!(bIrq0Reg & bIrq0WaitFor) && !(bIrq1Reg & bIrq1WaitFor)) || (wFifoBytes != 0));

        /* Check for buffer overflow */
        if (*pRxLength > wRxBufferSize)
        {
            *pRxLength = 0;
            return PH_ADD_COMPCODE(PH_ERR_BUFFER_OVERFLOW, PH_COMP_HAL);
        }

        /* Copy data to Receive Buffer */
        memcpy(pRxBuffer, pTmpBuffer, *pRxLength);  /* PRQA S 3200 */
    }
    /* Flush FIFO if contents are not retrieved */
    else
    {
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_Rc663_FlushFifo(pDataParams));
    }

    /* */
    /* Check if an error occured */
    /* read the error register */
    /* */
    PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_ERROR, &bError));

    /* no data error */
    if (bError & PHHAL_HW_RC663_BIT_NODATAERR)
    {
        status = PH_ERR_INTERNAL_ERROR;
    }
    /* buffer overflow */
    else if (bError & PHHAL_HW_RC663_BIT_FIFOOVL)
    {
        status = PH_ERR_BUFFER_OVERFLOW;
    }
    /* Fifo write error */
    else if (bError & PHHAL_HW_RC663_BIT_FIFOWRERR)
    {
        status = PH_ERR_READ_WRITE_ERROR;
    }
    /* EEPROM error */
    else if (bError & PHHAL_HW_RC663_BIT_EE_ERR)
    {
        status = PH_ERR_READ_WRITE_ERROR;
    }
    /* No error */
    else
    {
        status = PH_ERR_SUCCESS;
    }

    /* Stop Timer 0/1 if started */
    if (wOption & PHHAL_HW_RC663_OPTION_RXTX_TIMER_START)
    {
        /* retrieve content of Timer Control register */
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_ReadRegister(pDataParams, PHHAL_HW_RC663_REG_TCONTROL, &bRegister));

        /* manually stop timers */
        bRegister |= PHHAL_HW_RC663_BIT_T0STARTSTOPNOW | PHHAL_HW_RC663_BIT_T1STARTSTOPNOW;
        bRegister &= (uint8_t)~(uint8_t)(PHHAL_HW_RC663_BIT_T0RUNNING | PHHAL_HW_RC663_BIT_T1RUNNING);
        PH_CHECK_SUCCESS_FCT(statusTmp, phhalHw_WriteRegister(pDataParams, PHHAL_HW_RC663_REG_TCONTROL, bRegister));
    }

    return PH_ADD_COMPCODE(status, PH_COMP_HAL);
}

#endif /* NXPBUILD__PHHAL_HW_RC663 */
