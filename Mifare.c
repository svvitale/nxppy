#include "Mifare.h"
#include "errors.h"

#include <stdio.h>

/** General information bytes to be sent with ATR */
const uint8_t GI[] = { 0x46, 0x66, 0x6D,
    0x01, 0x01, 0x10, /*VERSION*/ 0x03, 0x02, 0x00, 0x01, /*WKS*/ 0x04, 0x01, 0xF1 /*LTO*/
};

static phStatus_t LoadProfile(nfc_data *nfcData)
{
    phStatus_t status = PH_ERR_SUCCESS;

    nfcData->sDiscLoop.pPal1443p3aDataParams = &(nfcData->spalI14443p3a);
    nfcData->sDiscLoop.pPal1443p3bDataParams = &(nfcData->spalI14443p3b);
    nfcData->sDiscLoop.pPal1443p4aDataParams = &(nfcData->spalI14443p4a);
    nfcData->sDiscLoop.pPal14443p4DataParams = &(nfcData->spalI14443p4);
    nfcData->sDiscLoop.pHalDataParams = &(nfcData->sHal_Nfc_Ic.sHal);

    /*
     * These lines are added just to SIGSEG fault when non 14443-3 card is detected
     */
    /*
     * Assign the GI for Type A
     */
    nfcData->sDiscLoop.sTypeATargetInfo.sTypeA_P2P.pGi = (uint8_t *) GI;
    nfcData->sDiscLoop.sTypeATargetInfo.sTypeA_P2P.bGiLength = sizeof(GI);
    /*
     * Assign the GI for Type F
     */
    nfcData->sDiscLoop.sTypeFTargetInfo.sTypeF_P2P.pGi = (uint8_t *) GI;
    nfcData->sDiscLoop.sTypeFTargetInfo.sTypeF_P2P.bGiLength = sizeof(GI);
    /*
     * Assign ATR response for Type A
     */
    nfcData->sDiscLoop.sTypeATargetInfo.sTypeA_P2P.pAtrRes = nfcData->aData;
    /*
     * Assign ATR response for Type F
     */
    nfcData->sDiscLoop.sTypeFTargetInfo.sTypeF_P2P.pAtrRes = nfcData->aData;
    /*
     * Assign ATS buffer for Type A
     */
    nfcData->sDiscLoop.sTypeATargetInfo.sTypeA_I3P4.pAts = nfcData->aData;
    /*
     ******************************************************************************************** */

    /*
     * Passive Bailout bitmap configuration
     */
    status = phacDiscLoop_SetConfig(&(nfcData->sDiscLoop), PHAC_DISCLOOP_CONFIG_BAIL_OUT, PH_OFF);
    PH_CHECK_SUCCESS(status);

    /*
     * Passive poll bitmap configuration. Poll for only Type A Tags.
     */
    status = phacDiscLoop_SetConfig(&(nfcData->sDiscLoop), PHAC_DISCLOOP_CONFIG_PAS_POLL_TECH_CFG, PHAC_DISCLOOP_POS_BIT_MASK_A);
    PH_CHECK_SUCCESS(status);

    /*
     * Turn OFF Passive Listen.
     */
    status = phacDiscLoop_SetConfig(&(nfcData->sDiscLoop), PHAC_DISCLOOP_CONFIG_PAS_LIS_TECH_CFG, PH_OFF);
    PH_CHECK_SUCCESS(status);

    /*
     * Turn OFF active listen.
     */
    status = phacDiscLoop_SetConfig(&(nfcData->sDiscLoop), PHAC_DISCLOOP_CONFIG_ACT_LIS_TECH_CFG, PH_OFF);
    PH_CHECK_SUCCESS(status);

    /*
     * Turn OFF Active Poll
     */
    status = phacDiscLoop_SetConfig(&(nfcData->sDiscLoop), PHAC_DISCLOOP_CONFIG_ACT_POLL_TECH_CFG, PH_OFF);
    PH_CHECK_SUCCESS(status);

    /*
     * Disable LPCD feature.
     */
    status = phacDiscLoop_SetConfig(&(nfcData->sDiscLoop), PHAC_DISCLOOP_CONFIG_ENABLE_LPCD, PH_OFF);
    PH_CHECK_SUCCESS(status);

    /*
     * reset collision Pending
     */
    status = phacDiscLoop_SetConfig(&(nfcData->sDiscLoop), PHAC_DISCLOOP_CONFIG_COLLISION_PENDING, PH_OFF);
    PH_CHECK_SUCCESS(status);

    /*
     * whether anti-collision is supported or not.
     */
    status = phacDiscLoop_SetConfig(&(nfcData->sDiscLoop), PHAC_DISCLOOP_CONFIG_ANTI_COLL, PH_ON);
    PH_CHECK_SUCCESS(status);

    /*
     * Device limit for Type A
     */
    status = phacDiscLoop_SetConfig(&(nfcData->sDiscLoop), PHAC_DISCLOOP_CONFIG_TYPEA_DEVICE_LIMIT, PH_ON);
    PH_CHECK_SUCCESS(status);

    /*
     * Discovery loop Operation mode
     */
    status = phacDiscLoop_SetConfig(&(nfcData->sDiscLoop), PHAC_DISCLOOP_CONFIG_OPE_MODE, RD_LIB_MODE_NFC);
    PH_CHECK_SUCCESS(status);

    /*
     * Bailout on Type A detect
     */
    status = phacDiscLoop_SetConfig(&(nfcData->sDiscLoop), PHAC_DISCLOOP_CONFIG_BAIL_OUT, PHAC_DISCLOOP_POS_BIT_MASK_A);
    PH_CHECK_SUCCESS(status);

    /*
     * Return Status
     */
    return status;
}

phStatus_t NfcRdLibInit(nfc_data *nfcData)
{
    phStatus_t status;

    /*
     * Initialize the Reader BAL (Bus Abstraction Layer) component
     */
    status = phbalReg_Stub_Init(&(nfcData->sBalReader), sizeof(phbalReg_Stub_DataParams_t));
    PH_CHECK_SUCCESS(status);

    /*
     * Initialize the OSAL Events.
     */
    status = phOsal_Event_Init();
    PH_CHECK_SUCCESS(status);

    // Start interrupt thread
    Set_Interrupt();

    /*
     * Set HAL type in BAL
     */
#ifdef NXPBUILD__PHHAL_HW_PN5180
    status = phbalReg_SetConfig(&(nfcData->sBalReader), PHBAL_REG_CONFIG_HAL_HW_TYPE, PHBAL_REG_HAL_HW_PN5180);
#endif
#ifdef NXPBUILD__PHHAL_HW_RC523
    status = phbalReg_SetConfig(&(nfcData->sBalReader), PHBAL_REG_CONFIG_HAL_HW_TYPE, PHBAL_REG_HAL_HW_RC523);
#endif
#ifdef NXPBUILD__PHHAL_HW_RC663
    status = phbalReg_SetConfig(&(nfcData->sBalReader), PHBAL_REG_CONFIG_HAL_HW_TYPE, PHBAL_REG_HAL_HW_RC663);
#endif
    PH_CHECK_SUCCESS(status);

    status = phbalReg_SetPort(&(nfcData->sBalReader), (uint8_t *) SPI_CONFIG);
    PH_CHECK_SUCCESS(status);

    /*
     * Open BAL
     */
    status = phbalReg_OpenPort(&(nfcData->sBalReader));
    PH_CHECK_SUCCESS(status);

    /*
     * Initialize the Reader HAL (Hardware Abstraction Layer) component
     */
    status = phhalHw_Nfc_IC_Init(&(nfcData->sHal_Nfc_Ic),
                                 sizeof(phhalHw_Nfc_Ic_DataParams_t),
                                 &(nfcData->sBalReader),
                                 0,
                                 nfcData->bHalBufferTx, sizeof(nfcData->bHalBufferTx),
                                 nfcData->bHalBufferRx, sizeof(nfcData->bHalBufferRx));
    PH_CHECK_SUCCESS(status);

    /*
     * Set the parameter to use the SPI interface
     */
    nfcData->sHal_Nfc_Ic.sHal.bBalConnectionType = PHHAL_HW_BAL_CONNECTION_SPI;

    Configure_Device(&(nfcData->sHal_Nfc_Ic));

    /*
     * Initializing specific objects for the communication with MIFARE (R) Classic cards. The MIFARE (R) Classic card
     * is compliant of ISO 14443-3 and ISO 14443-4
     */

    /*
     * Initialize the I14443-A PAL layer
     */
    status = phpalI14443p3a_Sw_Init(&(nfcData->spalI14443p3a), sizeof(phpalI14443p3a_Sw_DataParams_t), &(nfcData->sHal_Nfc_Ic.sHal));
    PH_CHECK_SUCCESS(status);

    /*
     * Initialize the I14443-A PAL component
     */
    status = phpalI14443p4a_Sw_Init(&(nfcData->spalI14443p4a), sizeof(phpalI14443p4a_Sw_DataParams_t), &(nfcData->sHal_Nfc_Ic.sHal));
    PH_CHECK_SUCCESS(status);

    /*
     * Initialize the I14443-4 PAL component
     */
    status = phpalI14443p4_Sw_Init(&(nfcData->spalI14443p4), sizeof(phpalI14443p4_Sw_DataParams_t), &(nfcData->sHal_Nfc_Ic.sHal));
    PH_CHECK_SUCCESS(status);

    /*
     * Initialize the I14443-B PAL component
     */
    status = phpalI14443p3b_Sw_Init(&(nfcData->spalI14443p3b), sizeof(phpalI14443p3b_Sw_DataParams_t), &(nfcData->sHal_Nfc_Ic.sHal));
    PH_CHECK_SUCCESS(status);

    /*
     * Initialize the MIFARE PAL component
     */
    status = phpalMifare_Sw_Init(&(nfcData->spalMifare), sizeof(phpalMifare_Sw_DataParams_t), &(nfcData->sHal_Nfc_Ic.sHal), NULL);
    PH_CHECK_SUCCESS(status);

    /*
     * Initialize the discover component
     */
    status = phacDiscLoop_Sw_Init(&(nfcData->sDiscLoop), sizeof(phacDiscLoop_Sw_DataParams_t), &(nfcData->sHal_Nfc_Ic.sHal));
    PH_CHECK_SUCCESS(status);

    /*
     * Load profile for Discovery loop
     */
    status = LoadProfile(nfcData);
    PH_CHECK_SUCCESS(status);

    status = phalMfc_Sw_Init(&(nfcData->salMfc), sizeof(phalMfc_Sw_DataParams_t), &(nfcData->spalMifare), NULL);
    PH_CHECK_SUCCESS(status);

    /*
     * Read the version of the reader IC
     */
    uint8_t icVersion = 0;
#if defined NXPBUILD__PHHAL_HW_RC523
    status = phhalHw_Rc523_ReadRegister(&(nfcData->sHal_Nfc_Ic.sHal), PHHAL_HW_RC523_REG_VERSION, &icVersion);
#endif
#if defined NXPBUILD__PHHAL_HW_RC663
    status = phhalHw_Rc663_ReadRegister(&(nfcData->sHal_Nfc_Ic.sHal), PHHAL_HW_RC663_REG_VERSION, &icVersion);
#endif
    PH_CHECK_SUCCESS(status);

    /*
     * Return Success
     */
    return PH_ERR_SUCCESS;
}

static PyObject *Mifare_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    // Constructs a singleton object so we don't try to control a single
    // piece of hardware from multiple python instances.
    static Mifare *self = NULL;

    if (self == NULL) {
        self = (Mifare *) type->tp_alloc(type, 0);
    }

    Py_XINCREF(self);
    return (PyObject *) self;
}


PyObject *Mifare_init(Mifare * self, PyObject * args, PyObject * kwds)
{
    int ret;
    ret = Set_Interface_Link();
    if (handle_error(ret, InitError)) return NULL;

    Reset_reader_device();

    ret = NfcRdLibInit(&(self->nfcData));
    if (handle_error(ret, InitError)) return NULL;

    return 0;
}

PyObject *Mifare_select(Mifare * self)
{
    phStatus_t status = 0;
    uint16_t wTagsDetected = 0;

    // Convenience pointers
    nfc_data *nfcData = &(self->nfcData);
    phacDiscLoop_Sw_DataParams_t *pDiscLoop = &(self->nfcData.sDiscLoop);

    /*
     * Field OFF
     */
    status = phhalHw_FieldOff(&(nfcData->sHal_Nfc_Ic.sHal));
    CHECK_STATUS(status);
    if (handle_error(status, SelectError)) return NULL;

    /*
     * Configure Discovery loop for Poll Mode
     */
    status = phacDiscLoop_SetConfig(pDiscLoop,
                                    PHAC_DISCLOOP_CONFIG_NEXT_POLL_STATE,
                                    PHAC_DISCLOOP_POLL_STATE_DETECTION);
    CHECK_STATUS(status);
    if (handle_error(status, SelectError)) return NULL;

    /*
     * Run Discovery loop
     */
    status = phacDiscLoop_Run(pDiscLoop, PHAC_DISCLOOP_ENTRY_POINT_POLL);
    if ((status & PH_ERR_MASK) != PHAC_DISCLOOP_DEVICE_ACTIVATED) {
        if (handle_error(status, SelectError)) {
            return NULL;
        } else { // handle_error should catch everything, but if it doesn't
            return PyErr_Format(SelectError, "DiscLoop_Run command failed: %02X", (status & PH_ERR_MASK));
        }
    }

    /*
     * Card detected
     * Get the tag types detected info
     */
    status = phacDiscLoop_GetConfig(pDiscLoop, PHAC_DISCLOOP_CONFIG_TECH_DETECTED, &wTagsDetected);
    if (handle_error(status, SelectError)) return NULL;

    /*
     * Check for Type A tag detection
     */
    if (PHAC_DISCLOOP_CHECK_ANDMASK(wTagsDetected, PHAC_DISCLOOP_POS_BIT_MASK_A)) {

        phacDiscLoop_Sw_TypeA_Info_t *pTypeATargetInfo = &(pDiscLoop->sTypeATargetInfo);

        uint8_t byteBufferSize = pTypeATargetInfo->aTypeA_I3P3[0].bUidSize;
        char asciiBuffer[byteBufferSize * 2];

        for (uint8_t i = 0; i < byteBufferSize; i++) {
            sprintf(&asciiBuffer[2 * i], "%02X", pTypeATargetInfo->aTypeA_I3P3[0].aUid[i]);
        }

        return PyUnicode_FromString(asciiBuffer);

    } else {
        return PyErr_Format(SelectError, "DISCLOOP_CHECK_ANDMASK failed: %02X", (status & PH_ERR_MASK));
    }

    Py_RETURN_NONE;
}

PyObject *Mifare_read_block(Mifare * self, PyObject * args)
{
    uint8_t blockIdx;
    uint8_t bDataBuffer[READ_BUFFER_LEN];

    if (!PyArg_ParseTuple(args, "b", &blockIdx)) {
        return NULL;
    }

    phStatus_t status = 0;

    status = phalMful_Read(&(self->nfcData.salMfc), blockIdx, bDataBuffer);
    if (handle_error(status, ReadError)) return NULL;

    // The read command reads a full 16 bytes, but we only want to return 1 page worth of data for this command.
#if PY_MAJOR_VERSION >= 3
    return Py_BuildValue("y#", bDataBuffer, 4);
#else
    return Py_BuildValue("s#", bDataBuffer, 4);
#endif
}

PyObject *Mifare_read_sign(Mifare * self)
{
    const size_t bufferSize = PHAL_MFUL_SIG_LENGTH;
    uint8_t data[bufferSize];
    uint8_t *sign = data;

    phStatus_t status = 0;

    status = phalMful_ReadSign(&(self->nfcData.salMfc), '\0', &sign);
    if (handle_error(status, ReadError)) return NULL;

#if PY_MAJOR_VERSION >= 3
    return Py_BuildValue("y#", sign, bufferSize);
#else
    return Py_BuildValue("s#", sign, bufferSize);
#endif
}

PyObject *Mifare_write_block(Mifare * self, PyObject * args)
{
    phStatus_t status = 0;
    uint8_t blockIdx;
    uint8_t *data;
    int dataLen;

    if (!PyArg_ParseTuple(args, "bs#", &blockIdx, &data, &dataLen)) {
        return NULL;
    }

    if (dataLen != WRITE_BUFFER_LEN) {
        return PyErr_Format(WriteError, "Write data MUST be specified as %d bytes", WRITE_BUFFER_LEN);
    }

    status = phalMful_Write(&(self->nfcData.salMfc), blockIdx, data);
    if (handle_error(status, WriteError)) return NULL;

    Py_RETURN_NONE;
}

PyObject *Mifare_get_version(Mifare* self)
{
    uint8_t version[PHAL_MFC_VERSION_LENGTH];

    phStatus_t status = 0;

    status = phalMful_GetVersion(&(self->nfcData.salMfc), version);
    if (handle_error(status, ReadError)) return NULL;

    return Py_BuildValue("{s:B, s:B, s:B, s:B, s:B, s:B, s:B}",
                         "vendor\0",       version[1],
                         "tag_type\0",     version[2],
                         "tag_subtype\0",  version[3],
                         "version_major\0",version[4],
                         "version_minor\0",version[5],
                         "tag_size\0",     version[6],
                         "protocol\0",     version[7]
                        );
}

PyObject* Mifare_clear_block(Mifare* self, PyObject* args) {
    phStatus_t status = 0;
    uint8_t blockIdx;
    uint8_t clearData[WRITE_BUFFER_LEN];

    if (!PyArg_ParseTuple(args, "b", &blockIdx)) {
        return NULL;
    }

    memset(clearData, 0, WRITE_BUFFER_LEN);

    status = phalMful_Write(&(self->nfcData.salMfc), blockIdx, clearData);
    if (handle_error(status, WriteError)) return NULL;

    Py_RETURN_NONE;
}

uint8_t * _Mifare_read(Mifare *self, uint16_t *bytesRead) {

    phStatus_t status = 0;
    uint8_t capContainerBuffer[READ_BUFFER_LEN];

    // Read the capability container
    status = phalMful_Read(&(self->nfcData.salMfc), 3, capContainerBuffer);
    if (handle_error(status, ReadError)) return NULL;

    uint8_t memorySize = capContainerBuffer[2];
    uint16_t userMemorySizeBytes = memorySize * 8;  // According to NFC Forum Type 2 Tag Operation Specification

    uint8_t remainder = userMemorySizeBytes % MFC_BLOCK_DATA_SIZE;

    // Round up to the neared MFC_BLOCK_DATA_SIZE so we have enough buffer space to read to the end.
    if (remainder != 0) {
        userMemorySizeBytes += (MFC_BLOCK_DATA_SIZE - remainder);
    }

    uint16_t userMemorySizePages = userMemorySizeBytes / MFC_BLOCK_DATA_SIZE;

    // Allocate our read buffer
    uint8_t *readBuffer = malloc(userMemorySizeBytes);

    if (readBuffer == NULL) {
        *bytesRead = 0;
        return NULL;
    }

    uint16_t userDataStartPage = 4;

    // Perform the read
    // The read command reads 16 bytes or 4 full pages at once.
    for (uint16_t pageIdx = 0; pageIdx < userMemorySizePages; pageIdx++) {

        uint16_t pageToRead = userDataStartPage + (pageIdx * 4);
        uint16_t bufferOffset = pageIdx * MFC_BLOCK_DATA_SIZE;
        
        status = phalMful_Read(&(self->nfcData.salMfc), pageToRead, &readBuffer[bufferOffset]);

        if (handle_error(status, ReadError)) {
            free(readBuffer);
            *bytesRead = 0;
            return NULL;
        }
    }

    *bytesRead = userMemorySizeBytes;
    return readBuffer;
}

PyObject* Mifare_read(Mifare *self, PyObject *args) {

    uint16_t bytesRead = 0;
    uint8_t * readBuffer = _Mifare_read(self, &bytesRead);

    if (readBuffer == NULL) {
        return PyErr_NoMemory();
    }
      
    PyObject * retval =
#if PY_MAJOR_VERSION >= 3
        Py_BuildValue("y#", readBuffer, bytesRead);
#else
        Py_BuildValue("s#", readBuffer, bytesRead);
#endif

    // Data is all copied, we can free the read buffer now.
    free(readBuffer);

    return retval;
}

PyObject* Mifare_read_ndef(Mifare *self, PyObject *args) {

    uint16_t bytesRead = 0;
    uint8_t * readBuffer = _Mifare_read(self, &bytesRead);

    if (readBuffer == NULL) {
        return PyErr_NoMemory();
    }
 
    // Now search for the first NDEF TLV
    uint16_t dataIdx = 0;

    PyObject * ndefData = NULL;

    while (dataIdx <= bytesRead) {
        // Pull out the TLV type
        uint8_t tlv_type = readBuffer[dataIdx];
        dataIdx++;

        // Pull out the TLV length
        uint16_t tlv_length = 0;

        if (readBuffer[dataIdx] == 0xff) {
            // Multi-byte length
            tlv_length = *((uint16_t *) &readBuffer[dataIdx + 1]);
            dataIdx += 3;
        }
        else {
            // Single-byte length
            tlv_length = readBuffer[dataIdx];
            dataIdx++;
        }

        if (tlv_type == 0x03) {
            // Found an NDEF record, return it in its entirety.
            ndefData =
        #if PY_MAJOR_VERSION >= 3
                Py_BuildValue("y#", &readBuffer[dataIdx], tlv_length);
        #else
                Py_BuildValue("s#", &readBuffer[dataIdx], tlv_length);
        #endif
            break;
        }

        // Some other TLV type found, increcement past it.
        dataIdx += tlv_length;
    }

    // Data is all copied, we can free the read buffer now.
    free(readBuffer);

    if (ndefData == NULL) {
        return PyErr_Format(ReadError, "Could not find NDEF TLV segment");
    }

    return ndefData;
}

PyObject* Mifare_pwd_auth(Mifare *self, PyObject *args) {

    uint8_t *pwd;
    uint8_t packBuffer[PHAL_AUTH_PACK_LENGTH];

    if (!PyArg_ParseTuple(args, "s", &pwd)) {
        return NULL;
    }

    phStatus_t status = 0;

    status = phalMful_PwdAuth(&(self->nfcData.salMfc), pwd, packBuffer);
    if (handle_error(status, AuthError)) return NULL;

#if PY_MAJOR_VERSION >= 3
    return Py_BuildValue("y#", packBuffer, 4);
#else
    return Py_BuildValue("s#", packBuffer, 4);
#endif
}

/***********************************
** Python Type Definiton
***********************************/
PyMethodDef Mifare_methods[] = {
    {"select", (PyCFunction) Mifare_select, METH_NOARGS, "Select a Mifare card if present. Returns the card UID"}
    ,
    {"read_block", (PyCFunction) Mifare_read_block, METH_VARARGS, "Read 4 bytes starting at the specified block."}
    ,
    {"read_sign", (PyCFunction) Mifare_read_sign, METH_NOARGS, "Read 32 bytes card manufacturer signature."}
    ,
    {"write_block", (PyCFunction) Mifare_write_block, METH_VARARGS, "Write 4 bytes starting at the specified block."}
    ,
    {"get_version", (PyCFunction) Mifare_get_version, METH_NOARGS, "Read version data as a dict."}
    ,
    {"clear_block", (PyCFunction) Mifare_clear_block, METH_VARARGS, "Clear 4 bytes starting at the specifed block."}
    ,
    {"read", (PyCFunction) Mifare_read, METH_VARARGS, "Reads all user data stored on the selected tag. Currently supports NTAG213/215/216."}
    ,
    {"read_ndef", (PyCFunction) Mifare_read_ndef, METH_VARARGS, "Attempt to read the first NDEF Message stored on the selected tag."}
    ,
    {"pwd_auth", (PyCFunction) Mifare_pwd_auth, METH_VARARGS, "Authenticate with password"}
    ,
    {NULL}                      /* Sentinel */
};

PyTypeObject MifareType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        "nxppy.Mifare",         /* tp_name */
    sizeof(Mifare),             /* tp_basicsize */
    0,                          /* tp_itemsize */
    0,                          /* tp_dealloc */
    0,                          /* tp_print */
    0,                          /* tp_getattr */
    0,                          /* tp_setattr */
    0,                          /* tp_reserved */
    0,                          /* tp_repr */
    0,                          /* tp_as_number */
    0,                          /* tp_as_sequence */
    0,                          /* tp_as_mapping */
    0,                          /* tp_hash */
    0,                          /* tp_call */
    0,                          /* tp_str */
    0,                          /* tp_getattro */
    0,                          /* tp_setattro */
    0,                          /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,         /* tp_flags */
    "Mifare objects",           /* tp_doc */
    0,                          /* tp_traverse */
    0,                          /* tp_clear */
    0,                          /* tp_richcompare */
    0,                          /* tp_weaklistoffset */
    0,                          /* tp_iter */
    0,                          /* tp_iternext */
    Mifare_methods,             /* tp_methods */
    0,                          /* tp_members */
    0,                          /* tp_getset */
    0,                          /* tp_base */
    0,                          /* tp_dict */
    0,                          /* tp_descr_get */
    0,                          /* tp_descr_set */
    0,                          /* tp_dictoffset */
    (initproc) Mifare_init,     /* tp_init */
    0,                          /* tp_alloc */
    (newfunc) Mifare_new,       /* tp_new */
};
