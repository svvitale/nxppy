#include "Mifare.h"

int Mifare_init(Mifare *self, PyObject *args, PyObject *kwds) {

    phStatus_t status;

    /* Initialize the Reader BAL (Bus Abstraction Layer) component */
    status = phbalReg_RpiSpi_Init(&self->data.balReader, sizeof(phbalReg_RpiSpi_DataParams_t));
    if (PH_ERR_SUCCESS != status)
    {
        PyErr_Format(InitError, "SPI Init failed: %04x", status);
        return -1;
    }

    status = phbalReg_OpenPort(&self->data.balReader);
    if (PH_ERR_SUCCESS != status)
    {
        PyErr_Format(InitError, "OpenPort failed: %04x", status);
        return -1;
    }

    /* we have a board with PN512,
    * but on the software point of view,
    * it's compatible to the RC523 */
    status = phhalHw_Rc523_Init(&self->data.hal,
        sizeof(phhalHw_Rc523_DataParams_t),
        &self->data.balReader,
        0,
        &self->data.bHalBufferReader[0],
        sizeof(self->data.bHalBufferReader),
        &self->data.bHalBufferReader[0],
        sizeof(self->data.bHalBufferReader));

    if (PH_ERR_SUCCESS != status)
    {
        PyErr_Format(InitError, "Rc523_Init failed: %04x", status);
        return -1;
    }

    /* Set the HAL configuration to SPI */
    status = phhalHw_SetConfig(&self->data.hal, PHHAL_HW_CONFIG_BAL_CONNECTION,
        PHHAL_HW_BAL_CONNECTION_SPI);
    if (PH_ERR_SUCCESS != status)
    {
        PyErr_Format(InitError, "SetConfig failed: %04x", status);
        return -1;
    }

    /* Initialize the 14443-3A PAL (Protocol Abstraction Layer) component */
    PH_CHECK_SUCCESS_FCT(status, phpalI14443p3a_Sw_Init(&self->data.I14443p3a,
        sizeof(phpalI14443p3a_Sw_DataParams_t), &self->data.hal));

    /* Initialize the 14443-4 PAL component */
    PH_CHECK_SUCCESS_FCT(status, phpalI14443p4_Sw_Init(&self->data.I14443p4,
        sizeof(phpalI14443p4_Sw_DataParams_t), &self->data.hal));

    /* Initialize the Mifare PAL component */
    PH_CHECK_SUCCESS_FCT(status, phpalMifare_Sw_Init(&self->data.palMifare,
        sizeof(phpalMifare_Sw_DataParams_t), &self->data.hal, &self->data.I14443p4));

    /* Initialize Ultralight(-C) AL component */
    PH_CHECK_SUCCESS_FCT(status, phalMful_Sw_Init(&self->data.alMful,
        sizeof(phalMful_Sw_DataParams_t), &self->data.palMifare, NULL, NULL, NULL));

    return 0;
}

phStatus_t Mifare_activate_card(phpalI14443p3a_Sw_DataParams_t *I14443p3a, uint8_t byteBuffer[], uint8_t *byteBufferSize)
{
    uint8_t bSak;
    uint8_t bMoreCardsAvailable;

    /* Activate the communication layer part 3
    * of the ISO 14443A standard. */
    return phpalI14443p3a_ActivateCard(I14443p3a,
        NULL, 0x00, byteBuffer, byteBufferSize, &bSak, &bMoreCardsAvailable);
}

PyObject *Mifare_select(Mifare *self)
{
    uint8_t byteBufferSize = UID_BUFFER_SIZE;
    uint8_t byteBuffer[UID_BUFFER_SIZE];

    uint8_t pAtqa[2];
    phStatus_t status;

    uint8_t bSak;
    uint8_t bMoreCardsAvailable;

    /* reset the IC  */
    phhalHw_Rc523_Cmd_SoftReset(&self->data.hal);

    /* Reset the RF field */
    if ((status = phhalHw_FieldReset(&self->data.hal)) != PH_ERR_SUCCESS) {
        return PyErr_Format(SelectError, "FieldReset command failed: %04x", status);
    }

    /* Apply the type A protocol settings
    * and activate the RF field. */
    if ((status = phhalHw_ApplyProtocolSettings(&self->data.hal, PHHAL_HW_CARDTYPE_ISO14443A)) != PH_ERR_SUCCESS) {
        return PyErr_Format(SelectError, "ApplyProtocolSettings command failed: %04x", status);
    }

    /* Empty the pAtqa */
    memset(pAtqa, '\0', 2);

    if ((status = phpalI14443p3a_RequestA(&self->data.I14443p3a, pAtqa)) != PH_ERR_SUCCESS) {
        return PyErr_Format(SelectError, "RequestA command failed: %04x", status);
    }

    /* Reset the RF field */
    if ((status = phhalHw_FieldReset(&self->data.hal)) != PH_ERR_SUCCESS) {
        return PyErr_Format(SelectError, "FieldReset command failed: %04x", status);
    }
    /* Activate the communication layer part 3 of the ISO 14443A standard. */
    if ( phpalI14443p3a_ActivateCard(&self->data.I14443p3a, NULL, 0x00, byteBuffer, &byteBufferSize, &bSak, &bMoreCardsAvailable) == PH_ERR_SUCCESS) {
        // Card is present, return it as a python object.
        uint8_t i;
        char asciiBuffer[UID_ASCII_BUFFER_SIZE];

        if (byteBufferSize + 1 > UID_ASCII_BUFFER_SIZE) {
            // Truncate if we got back too much data
            byteBufferSize = UID_ASCII_BUFFER_SIZE - 1;
        }

        for (i = 0; i < byteBufferSize; i++) {
            sprintf(&asciiBuffer[2 * i], "%02X", byteBuffer[i]);
        }

        return PyUnicode_FromString(asciiBuffer);
    }

    Py_RETURN_NONE;
}

PyObject *Mifare_read_block(Mifare *self, PyObject *args)
{
    const size_t bufferSize = PHAL_MFUL_READ_BLOCK_LENGTH;
    uint8_t data[bufferSize];
    uint8_t blockIdx;
    phStatus_t status;

    if (!PyArg_ParseTuple(args, "b", &blockIdx)) {
        return NULL;
    }

    status = phalMful_Read(&self->data.alMful, blockIdx, data);

    if (status != PH_ERR_SUCCESS) {
        return PyErr_Format(ReadError, "Read failed: %04x", status);
    }

#if PY_MAJOR_VERSION >= 3
    return Py_BuildValue("y#", data, bufferSize);
#else
    return Py_BuildValue("s#", data, bufferSize);
#endif
}

PyObject *Mifare_write_block(Mifare *self, PyObject *args)
{
    uint16_t status;
    uint8_t blockIdx;
    uint8_t *data;
    int dataLen;

#if PY_MAJOR_VERSION >= 3
    if (!PyArg_ParseTuple(args, "by#", &blockIdx, &data, &dataLen)) {
#else
    if (!PyArg_ParseTuple(args, "bs#", &blockIdx, &data, &dataLen)) {
#endif
        return NULL;
    }

    if ((status = phalMful_Write(&self->data.alMful, blockIdx, data)) != 0) {
        return PyErr_Format(WriteError, "Write failed: %04x", status);
    }

    Py_RETURN_NONE;
}

/***********************************
** Python Type Definiton
***********************************/
PyMethodDef Mifare_methods[] = {
    {"select", (PyCFunction) Mifare_select, METH_NOARGS, "Select a Mifare card if present. Returns the card UID"},
    {"read_block", (PyCFunction) Mifare_read_block, METH_VARARGS, "Read 16 bytes starting at the specified block."},
    {"write_block", (PyCFunction) Mifare_write_block, METH_VARARGS, "Write 4 bytes starting at the specified block."},
    {NULL}  /* Sentinel */
};

PyTypeObject MifareType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "nxppy.Mifare",             /* tp_name */
    sizeof(Mifare), /* tp_basicsize */
    0,                         /* tp_itemsize */
    0,                         /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,        /* tp_flags */
    "Mifare objects",          /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    Mifare_methods,            /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)Mifare_init,      /* tp_init */
};


