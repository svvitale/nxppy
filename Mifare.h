#pragma once
/*******************************************************************************
* Copyright (c), NXP Semiconductors Gratkorn / Austria
*
* (C)NXP Semiconductors
* All rights are reserved. Reproduction in whole or in part is
* prohibited without the written consent of the copyright owner.
* NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
* particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
* arising from its use.
********************************************************************************
*
* Filename: main.c
* Processor family: ARM11
*
* Description: This file contains main entry.
*
*******************************************************************************/

#include <Python.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * Header for hardware configuration: bus interface, reset of attached reader ID, onboard LED handling etc.
 * */
#include <phhwConfig.h>

/**
 * Reader Library Headers
 */
#include <ph_Status.h>

/*
 * BAL Headers
 */
#include <phbalReg.h>

/*
 * PAL Headers
 */
#include <phpalI14443p3a.h>
#include <phpalI14443p4.h>
#include <phpalI14443p3b.h>
#include <phpalI14443p4a.h>
#include <phpalMifare.h>

/*
 * AL Headers
 */
#include <phalMfc.h>

#include <phacDiscLoop.h>

/*
 * Printf macro
 */

/*
 * Configuration Headers
 */
/*
 * Controls build behavior of components
 */
#include <ph_NxpBuild.h>
/*
 * Status code definitions
 */
#include <ph_Status.h>

/*
 * Reader Library Headers
 */
/*
 * Generic ISO14443-3A Component of Reader Library Framework
 */
#include <phpalI14443p3a.h>
/*
 * Generic ISO14443-4 Component of Reader Library Framework
 */
#include <phpalI14443p4.h>
/*
 * Generic ISO14443-4A Component of Reader Library Framework
 */
#include <phpalI14443p4a.h>
/*
 * Generic MIFARE(R) Ultralight Application Component of Reader Library Framework
 */
#include <phalMful.h>
#include <phalMfc.h>

#include <phpalI14443p3b.h>

#define UID_BUFFER_SIZE 20
#define UID_ASCII_BUFFER_SIZE ((UID_BUFFER_SIZE * 2) + 1)

#define TX_RX_BUFFER_SIZE           128 // 128 Byte buffer
#define READ_BUFFER_LEN             PHAL_MFUL_READ_BLOCK_LENGTH  /* Buffer length */
#define WRITE_BUFFER_LEN            PHAL_MFUL_WRITE_BLOCK_LENGTH  /* Buffer length */
#define MFC_BLOCK_DATA_SIZE         16   /* Block Data size - 16 Bytes */
#define PHAL_MFC_VERSION_LENGTH     0x08 // from src/phalMFC_Int.h
#define PHAL_AUTH_PACK_LENGTH       0x02 

typedef struct {
    /* BAL component holder */
    phbalReg_Stub_DataParams_t sBalReader;

    /* HAL variables */
    phhalHw_Nfc_Ic_DataParams_t sHal_Nfc_Ic;        /* HAL component holder for Nfc Ic's */
    uint8_t bHalBufferTx[TX_RX_BUFFER_SIZE];        /* HAL TX buffer */
    uint8_t bHalBufferRx[TX_RX_BUFFER_SIZE];        /* HAL RX buffer */
    uint8_t aData[50];                              /* ATR response buffer */

    /* PAL variables */
    phpalI14443p3a_Sw_DataParams_t spalI14443p3a;   /* PAL I14443-A component */
    phpalI14443p4a_Sw_DataParams_t spalI14443p4a;   /* PAL ISO I14443-4A component */
    phpalI14443p3b_Sw_DataParams_t spalI14443p3b;   /* PAL ISO I14443-B component */
    phpalI14443p4_Sw_DataParams_t spalI14443p4;     /* PAL ISO I14443-4 component */
    phpalMifare_Sw_DataParams_t spalMifare; /* PAL MIFARE component */

    phacDiscLoop_Sw_DataParams_t sDiscLoop; /* Discovery loop component */
    phalMfc_Sw_DataParams_t salMfc; /* MIFARE Classic parameter structure */
} nfc_data;

typedef struct {
    PyObject_HEAD nfc_data nfcData;
} Mifare;

PyObject *Mifare_init(Mifare * self, PyObject * args, PyObject * kwds);
PyObject *Mifare_select(Mifare * self);
PyObject *Mifare_read_block(Mifare * self, PyObject * args);
PyObject *Mifare_read_sign(Mifare * self);
PyObject *Mifare_write_block(Mifare * self, PyObject * args);
PyObject *Mifare_pwd_auth(Mifare * self, PyObject * args);

extern PyObject *InitError;
extern PyObject *SelectError;
extern PyObject *ReadError;
extern PyObject *WriteError;
extern PyObject *AuthError;

extern PyMethodDef Mifare_methods[];
extern PyTypeObject MifareType;
