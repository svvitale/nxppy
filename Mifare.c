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
    status =phpalI14443p3a_ActivateCard(&self->data.I14443p3a, NULL, 0x00, byteBuffer, &byteBufferSize, &bSak, &bMoreCardsAvailable) ;
    /* Activate the communication layer part 3 of the ISO 14443A standard. */
    if (status == PH_ERR_SUCCESS) {
	    self->data.Sak=bSak;
        uint8_t i;
        char asciiBuffer[UID_ASCII_BUFFER_SIZE];

        if (byteBufferSize + 1 > UID_ASCII_BUFFER_SIZE) {
            // Truncate if we got back too much data
            byteBufferSize = UID_ASCII_BUFFER_SIZE - 1;
        }
        self->data.uidSize= byteBufferSize;
		self->data.uid = malloc(sizeof(uint8_t)*byteBufferSize);
        for (i = 0; i < byteBufferSize; i++) {
            sprintf(&asciiBuffer[2 * i], "%02X", byteBuffer[i]);
            self->data.uid[i]=byteBuffer[i];
        }

        return PyUnicode_FromString(asciiBuffer);
    }

    Py_RETURN_NONE;
}

PyObject *MifareClassic_read_block(Mifare *self, PyObject *args)
{
	uint8_t blockIdx;
	uint8_t *data = malloc(sizeof(uint8_t)*MIFARECLASSIC_BUFFER_SIZE);
	if(!PyArg_ParseTuple(args, "b", &blockIdx))
	{
	  Py_RETURN_NONE;
	}
	phalMfc_Read(
           &self->data.palMifareClassic,     /**< [In] Pointer to this layer's parameter structure. */
           blockIdx,       /**< [In] block number to be read. */
           data   /**< [Out] pBlockData[16] containing block read from the MIFARE(R) card */
    );
	char asciiBuffer[(MIFARECLASSIC_BUFFER_SIZE*2)+1];
	int i;
	for (i = 0; i < MIFARECLASSIC_BUFFER_SIZE; i++) {
		sprintf(&asciiBuffer[2 * i], "%02X", data[i]);
	}
    return PyUnicode_FromString(asciiBuffer);

}
PyObject *Mifare_get_type(Mifare * self)
{
	if(self->data.Sak==0x24)
	{
		return PyUnicode_FromString("MIFARE DESFire");
	}
	else if(self->data.Sak==0x00)
	{
		return PyUnicode_FromString("MIFARE Ultralight");
	}
	else if(self->data.Sak==0x09)
	{
		return PyUnicode_FromString("MIFARE Mini");
	}
	else if(self->data.Sak==0x08)
	{
		return PyUnicode_FromString("MIFARE Classic 1k");
	}
	else if(self->data.Sak==0x18)
	{
		return PyUnicode_FromString("MIFARE Classic 4k");
	}
	else
		Py_RETURN_NONE;
}
PyObject *Mifare_read_block(Mifare *self, PyObject *args)
{
    const size_t bufferSize = PHAL_MFUL_READ_BLOCK_LENGTH;
    uint8_t data[bufferSize];
    uint8_t blockIdx;
    phStatus_t status;

    if (!PyArg_ParseTuple(args, "b", &blockIdx)) {
		Py_RETURN_NONE;
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

PyObject *Mifare_read_sign(Mifare *self)
{
    const size_t bufferSize = PHAL_MFUL_SIG_LENGTH;
    uint8_t data[bufferSize];
    uint8_t *sign = data;

    phStatus_t status;

    status = phalMful_ReadSign(&self->data.alMful, '\0', &sign);

    if (status != PH_ERR_SUCCESS) {
        return PyErr_Format(ReadError, "Read failed: %04x", status);
    }

#if PY_MAJOR_VERSION >= 3
    return Py_BuildValue("y#", sign, bufferSize);
#else
    return Py_BuildValue("s#", sign, bufferSize);
#endif
}

PyObject *MifareClassic_Init(Mifare *self)
{

    Py_RETURN_NONE;
	//phalMfc_Sw_Init(
}
PyObject *MifareClassic_Write(Mifare *self, PyObject *args)
{
	uint8_t blockIdx,status;
	uint8_t *data;
	#if PY_MAJOR_VERSION >= 3
	if (!PyArg_ParseTuple(args, "by", &blockIdx, &data)) {
	#else
	if (!PyArg_ParseTuple(args, "bs", &blockIdx, &data)) {
	#endif
		//printf("Cry");
		return NULL;
	}
	if(status=phalMfc_Write(&self->data.palMifareClassic,blockIdx,data)!=0)
	{
		return PyErr_Format(WriteError, "Write failed: %04x", status);
	}
	return Py_BuildValue("#",1);
}
PyObject *MifareClassic_Authenticate(Mifare *self, PyObject *args)
{
	phKeyStore_Sw_DataParams_t SwkeyStore;
 	phKeyStore_Sw_KeyEntry_t   pKeyEntries;
 	phKeyStore_Sw_KeyVersionPair_t   pKeyVersionPairs;
 	phKeyStore_Sw_KUCEntry_t   pKUCEntries;

	uint16_t status;
    uint8_t blockIdx;
    char *key;
    uint8_t keyLength=6;
    int dataLen;
    int i;
    PyObject* transferTuple;
    uint8_t KeyType;
    #if PY_MAJOR_VERSION >= 3
    if (!PyArg_ParseTuple(args, "bOb", &blockIdx, &transferTuple,&KeyType)) {
#else
    if (!PyArg_ParseTuple(args, "bOb", &blockIdx, &transferTuple,&KeyType)) {
#endif
		printf("Cry");
        return NULL;
    }
    key= malloc(sizeof(char)*6);
    for (i = 0; i < PyList_Size(transferTuple); i++) {
		uint8_t k;
		PyArg_Parse(PyList_GetItem(transferTuple, (Py_ssize_t)i),"b",&k);
		key[i]=k;
	}
	/* initialise the Key Store: */
	status = phKeyStore_Sw_Init(&self->data.KeyStore,   /**< [In] Keystore parameter structure */
		sizeof(self->data.KeyStore),                    /**< [In] Size of Keystore parameter structure */
		&pKeyEntries,                         /**< [In] Array of key entries */
		1,                     /**< [In] Number of key entries */
		&pKeyVersionPairs,                    /**< [In] Array of key version pairs */
		1,                /**< [In] Number of key version pairs */
		&pKUCEntries,                         /**< [In] Key usage counter entry storage */
		1);                    /**< [In] Number of Key usage counter entries */
	//TODO: Erase
	//printf("\n phKeyStore_Sw_Init status: %d",status);

	/* load a Key to the Store */
	int wKeyNumber = 0;
	int wKeyVersion = 0;
	int wKeyStoreKeyType = PH_KEYSTORE_KEY_TYPE_MIFARE;
	status = phKeyStore_FormatKeyEntry(&self->data.KeyStore, wKeyNumber, wKeyStoreKeyType);
	//TODO: Erase
	//printf("\n phKeyStore_FormatKeyEntry status: %d",status);

	/* Store the key in keystore */
	status = phKeyStore_SetKey(&self->data.KeyStore,   /**< [In] Keystore parameter structure */
		wKeyNumber,                         /**< [In] Key number */
		wKeyVersion,                        /**< [In] Key version */
		wKeyStoreKeyType,                   /**< [In] MiFare type key */
		key,                            /**< [In] Key array */
		wKeyVersion);                       /**< [In] Key version */
	//TODO: Erase
	//printf("\n phKeyStore_SetKey status: %d",status);
	/* Initialise the MiFare Classic */
	status = phalMfc_Sw_Init(&self->data.palMifareClassic,   /**< [In] Pointer to application layer's parameter structure */
		sizeof(self->data.palMifareClassic),                 /**< [In] size of this layer's parameter structure */
		&self->data.palMifare,                               /**< [In] Pointer to a palMifare component */
		&self->data.KeyStore);                               /**< [In] Pointer to a Keystore component */
	//TODO: Erase
	//printf("\n phalMfc_Sw_Init status: %d",status);
    uint16_t bKeyType = PHPAL_MIFARE_KEYA;
    if(KeyType!=0)
        bKeyType =PHPAL_MIFARE_KEYB;
	status = phalMfc_Authenticate(&self->data.palMifareClassic,   /**< [In] Pointer to application layer's parameter structure */
		blockIdx,                    /**< [In] Block number to be authenticated */
		bKeyType,                    /**< [In] KeyB, MiFare type */
        wKeyNumber,                  /**< [In] Key number */
        wKeyVersion,                 /**< [In] Key Version */
        self->data.uid,              /**< [In] Uid of the card */
        self->data.uidSize);         /**< [In] Length of the Uid specified */
	//TODO: Erase
    //printf("\n phalMfc_Authenticate: %d--",status);
    if(status== PH_ERR_SUCCESS)
    {
		char asciiBuffer[UID_ASCII_BUFFER_SIZE];

		for (i = 0; i < self->data.uidSize; i++) {
				sprintf(&asciiBuffer[2 * i], "%02X",self->data.uid[i]);
		}
		return PyUnicode_FromString(asciiBuffer);
	}
    Py_RETURN_NONE;
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
    {"read_sign", (PyCFunction) Mifare_read_sign, METH_NOARGS, "Read 32 bytes card manufacturer signature."},
    {"write_block", (PyCFunction) Mifare_write_block, METH_VARARGS, "Write 4 bytes starting at the specified block."},
    {"classic_authenticate",(PyCFunction)MifareClassic_Authenticate, METH_VARARGS,"Authenticate using a 6 bytes key." },
    {"classic_read",(PyCFunction)MifareClassic_read_block,METH_VARARGS,"Read a full 16 bytes block."},
    {"get_type",(PyCFunction)Mifare_get_type,METH_NOARGS,"Get the type of the mifare card."},
    {"classic_write",(PyCFunction)MifareClassic_Write,METH_VARARGS,"write the data 16 bytes in the block."},
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