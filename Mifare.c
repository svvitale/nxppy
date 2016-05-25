#include "Mifare.h"
#ifdef   DEBUG
#include <stdio.h>
#define  DEBUG_FLUSH(x)      //{char buff[1]; buff[0] = x; __sys_write(0, buff, 1);}
#else
#define  DEBUG_FLUSH(x)
#endif

#define NUMBER_OF_KEYENTRIES        2
#define NUMBER_OF_KEYVERSIONPAIRS   2
#define NUMBER_OF_KUCENTRIES        1

#define DATA_BUFFER_LEN             16 /* Buffer length */
#define MFC_BLOCK_DATA_SIZE         16 /* Block Data size - 16 Bytes */

/*******************************************************************************
**   Global Variable Declaration
*******************************************************************************/
phbalReg_Stub_DataParams_t         sBalReader;                 /* BAL component holder */

    /*HAL variables*/
phhalHw_Nfc_Ic_DataParams_t        sHal_Nfc_Ic;                /* HAL component holder for Nfc Ic's */
void                              *pHal;                       /* HAL pointer */
uint8_t                            bHalBufferTx[128];          /* HAL  TX buffer */
uint8_t                            bHalBufferRx[128];          /* HAL  RX buffer */

    /*PAL variables*/
phpalI14443p3a_Sw_DataParams_t     spalI14443p3a;              /* PAL  I14443-A component */
phpalI14443p4a_Sw_DataParams_t     spalI14443p4a;              /* PAL ISO I14443-4A component */
phpalI14443p3b_Sw_DataParams_t     spalI14443p3b;              /* PAL ISO I14443-B component */
phpalI14443p4_Sw_DataParams_t      spalI14443p4;               /* PAL ISO I14443-4 component */
phpalMifare_Sw_DataParams_t        spalMifare;                 /* PAL  MIFARE component */

phacDiscLoop_Sw_DataParams_t       sDiscLoop;                  /* Discovery loop component */
phalMfc_Sw_DataParams_t            salMfc;                     /* MIFARE Classic parameter structure */

phKeyStore_Sw_DataParams_t         sSwkeyStore;                /* Sw Key parameter structure */
phKeyStore_Sw_KeyEntry_t           sKeyEntries[NUMBER_OF_KEYENTRIES];                                  /* Sw KeyEntry structure */
phKeyStore_Sw_KUCEntry_t           sKUCEntries[NUMBER_OF_KUCENTRIES];                                  /* Sw Key usage counter structure */
phKeyStore_Sw_KeyVersionPair_t     sKeyVersionPairs[NUMBER_OF_KEYVERSIONPAIRS * NUMBER_OF_KEYENTRIES]; /* Sw KeyVersionPair structure */

uint8_t                            bDataBuffer[DATA_BUFFER_LEN];  /* universal data buffer */

uint8_t                            bSak;                      /* SAK  card type information */
uint16_t                           wAtqa;                     /* ATQA card type information */
uint8_t 						blockcnt=0;

/** General information bytes to be sent with ATR */
const uint8_t GI[] = { 0x46,0x66,0x6D,
                       0x01,0x01,0x10,       /*VERSION*/
                       0x03,0x02,0x00,0x01,  /*WKS*/
                       0x04,0x01,0xF1        /*LTO*/
                      };

static uint8_t    aData[50];              /* ATR response holder */

/* Set the key for the MIFARE (R) Classic cards. */
uint8_t Key[6] = {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};

/* Don't change the following line */
uint8_t Original_Key[6] = {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};

/***********************************************************************************************
 * \brief   Print a given array of integers on the console
 * \param   *pBuff   Buffer Reference
 * \param   size      data size to be print
 **********************************************************************************************/
#ifdef   DEBUG
static void PRINT_BUFF(uint8_t *pBuff, uint8_t size)
{
    uint8_t bBufIdx;

    for(bBufIdx = 0; bBufIdx < size; bBufIdx++)
    {
        DEBUG_PRINTF(" %02X",pBuff[bBufIdx]);
    }
}
#else
#define  PRINT_BUFF(x, y)
#endif /* DEBUG */

static phStatus_t LoadProfile(void)
{
    phStatus_t status = PH_ERR_SUCCESS;

    sDiscLoop.pPal1443p3aDataParams  = &spalI14443p3a;
	sDiscLoop.pPal1443p3bDataParams  = &spalI14443p3b;
    sDiscLoop.pPal1443p4aDataParams  = &spalI14443p4a;
    sDiscLoop.pPal14443p4DataParams  = &spalI14443p4;
    sDiscLoop.pHalDataParams         = &sHal_Nfc_Ic.sHal;
	
	/* These lines are added just to SIGSEG fault when non 14443-3 card is detected */
	/* Assign the GI for Type A */
    sDiscLoop.sTypeATargetInfo.sTypeA_P2P.pGi       = (uint8_t *)GI;
    sDiscLoop.sTypeATargetInfo.sTypeA_P2P.bGiLength = sizeof(GI);
    /* Assign the GI for Type F */
    sDiscLoop.sTypeFTargetInfo.sTypeF_P2P.pGi       = (uint8_t *)GI;
    sDiscLoop.sTypeFTargetInfo.sTypeF_P2P.bGiLength = sizeof(GI);
    /* Assign ATR response for Type A */
    sDiscLoop.sTypeATargetInfo.sTypeA_P2P.pAtrRes   = aData;
    /* Assign ATR response for Type F */
    sDiscLoop.sTypeFTargetInfo.sTypeF_P2P.pAtrRes   = aData;
    /* Assign ATS buffer for Type A */
    sDiscLoop.sTypeATargetInfo.sTypeA_I3P4.pAts     = aData;
	/* ******************************************************************************************** */	
	
    /* Passive Bailout bitmap configuration */
    status = phacDiscLoop_SetConfig(&sDiscLoop, PHAC_DISCLOOP_CONFIG_BAIL_OUT, 0x00);
    CHECK_STATUS(status);

    /* Passive poll bitmap configuration. Poll for only Type A Tags. */
    status = phacDiscLoop_SetConfig(&sDiscLoop, PHAC_DISCLOOP_CONFIG_PAS_POLL_TECH_CFG, PHAC_DISCLOOP_POS_BIT_MASK_A);
    CHECK_STATUS(status);

    /* Turn OFF Passive Listen. */
    status = phacDiscLoop_SetConfig(&sDiscLoop, PHAC_DISCLOOP_CONFIG_PAS_LIS_TECH_CFG, 0x00);
    CHECK_STATUS(status);

    /* Turn OFF active listen. */
    status = phacDiscLoop_SetConfig(&sDiscLoop, PHAC_DISCLOOP_CONFIG_ACT_LIS_TECH_CFG, 0x00);
    CHECK_STATUS(status);

    /* Turn OFF Active Poll */
    status = phacDiscLoop_SetConfig(&sDiscLoop, PHAC_DISCLOOP_CONFIG_ACT_POLL_TECH_CFG, 0x00);
    CHECK_STATUS(status);

    /* Disable LPCD feature. */
    status = phacDiscLoop_SetConfig(&sDiscLoop, PHAC_DISCLOOP_CONFIG_ENABLE_LPCD, PH_OFF);
    CHECK_STATUS(status);

    /* reset collision Pending */
    status = phacDiscLoop_SetConfig(&sDiscLoop, PHAC_DISCLOOP_CONFIG_COLLISION_PENDING, PH_OFF);
    CHECK_STATUS(status);

    /* whether anti-collision is supported or not. */
    status = phacDiscLoop_SetConfig(&sDiscLoop, PHAC_DISCLOOP_CONFIG_ANTI_COLL, PH_ON);
    CHECK_STATUS(status);

    /* Device limit for Type A */
    status = phacDiscLoop_SetConfig(&sDiscLoop, PHAC_DISCLOOP_CONFIG_TYPEA_DEVICE_LIMIT, 1);
    CHECK_STATUS(status);

    /* Discovery loop Operation mode */
    status = phacDiscLoop_SetConfig(&sDiscLoop, PHAC_DISCLOOP_CONFIG_OPE_MODE, RD_LIB_MODE_NFC);

    /* Bailout on Type A detect */
    status = phacDiscLoop_SetConfig(&sDiscLoop, PHAC_DISCLOOP_CONFIG_BAIL_OUT, PHAC_DISCLOOP_POS_BIT_MASK_A);
    CHECK_SUCCESS(status);

    /* Return Status */
    return status;
}

phStatus_t NfcRdLibInit(void)
{

    phStatus_t status;

    /* Initialize the Reader BAL (Bus Abstraction Layer) component */
    status = phbalReg_Stub_Init(&sBalReader, sizeof(phbalReg_Stub_DataParams_t));
    CHECK_SUCCESS(status);

    /* Initialize the OSAL Events. */
    status = phOsal_Event_Init();
    CHECK_STATUS(status);

	//Start interrupt thread
    Set_Interrupt();

    /* Set HAL type in BAL */
#ifdef NXPBUILD__PHHAL_HW_PN5180
    status = phbalReg_SetConfig(
        &sBalReader,
        PHBAL_REG_CONFIG_HAL_HW_TYPE,
        PHBAL_REG_HAL_HW_PN5180);
#endif
#ifdef NXPBUILD__PHHAL_HW_RC523
    status = phbalReg_SetConfig(
        &sBalReader,
        PHBAL_REG_CONFIG_HAL_HW_TYPE,
        PHBAL_REG_HAL_HW_RC523);
#endif
#ifdef NXPBUILD__PHHAL_HW_RC663
    status = phbalReg_SetConfig(
        &sBalReader,
        PHBAL_REG_CONFIG_HAL_HW_TYPE,
        PHBAL_REG_HAL_HW_RC663);
#endif
    CHECK_STATUS(status);

    status = phbalReg_SetPort(
        &sBalReader,
        SPI_CONFIG);
    CHECK_STATUS(status);

    /* Open BAL */
    status = phbalReg_OpenPort(&sBalReader);
    CHECK_STATUS(status);

    /* Initialize the Reader HAL (Hardware Abstraction Layer) component */
    status = phhalHw_Nfc_IC_Init(
                                &sHal_Nfc_Ic,
                                sizeof(phhalHw_Nfc_Ic_DataParams_t),
                                &sBalReader,
                                0,
                                bHalBufferTx,
                                sizeof(bHalBufferTx),
                                bHalBufferRx,
                                sizeof(bHalBufferRx));
    CHECK_SUCCESS(status);

    /* Set the parameter to use the SPI interface */
    sHal_Nfc_Ic.sHal.bBalConnectionType = PHHAL_HW_BAL_CONNECTION_SPI;

	Configure_Device(&sHal_Nfc_Ic);

    /* Set the generic pointer */
    pHal = &sHal_Nfc_Ic.sHal;

    /* Initializing specific objects for the communication with MIFARE (R) Classic cards.
     * The MIFARE (R) Classic card is compliant of ISO 14443-3 and ISO 14443-4
     */

	 /* Initialize the I14443-A PAL layer */
    status = phpalI14443p3a_Sw_Init(&spalI14443p3a, sizeof(phpalI14443p3a_Sw_DataParams_t), &sHal_Nfc_Ic.sHal);
    CHECK_STATUS(status);

    /* Initialize the I14443-A PAL component */
    status = phpalI14443p4a_Sw_Init(&spalI14443p4a, sizeof(phpalI14443p4a_Sw_DataParams_t), &sHal_Nfc_Ic.sHal);
    CHECK_STATUS(status);

    /* Initialize the I14443-4 PAL component */
    status = phpalI14443p4_Sw_Init(&spalI14443p4, sizeof(phpalI14443p4_Sw_DataParams_t), &sHal_Nfc_Ic.sHal);
    CHECK_STATUS(status);

    /* Initialize the I14443-B PAL  component */
    status = phpalI14443p3b_Sw_Init(&spalI14443p3b, sizeof(phpalI14443p3b_Sw_DataParams_t), &sHal_Nfc_Ic.sHal);
    CHECK_STATUS(status);
	
    /* Initialize the MIFARE PAL component */
    status = phpalMifare_Sw_Init(&spalMifare, sizeof(phpalMifare_Sw_DataParams_t), &sHal_Nfc_Ic.sHal, NULL);
    CHECK_STATUS(status);

    /* Initialize the keystore component */
    status = phKeyStore_Sw_Init(
                                &sSwkeyStore,
                                sizeof(phKeyStore_Sw_DataParams_t),
                                &sKeyEntries[0],
                                NUMBER_OF_KEYENTRIES,
                                &sKeyVersionPairs[0],
                                NUMBER_OF_KEYVERSIONPAIRS,
                                &sKUCEntries[0],
                                NUMBER_OF_KUCENTRIES);
    CHECK_SUCCESS(status);

    /* Initialize the discover component */
    status = phacDiscLoop_Sw_Init(&sDiscLoop, sizeof(phacDiscLoop_Sw_DataParams_t), &sHal_Nfc_Ic.sHal);
    CHECK_SUCCESS(status);

    /* Load profile for Discovery loop */
    LoadProfile();

    /* load a Key to the Store */
    /* Note: If You use Key number 0x00, be aware that in SAM
      this Key is the 'Host authentication key' !!! */
    status = phKeyStore_FormatKeyEntry(&sSwkeyStore, 1, PH_KEYSTORE_KEY_TYPE_MIFARE);
    CHECK_STATUS(status);

    /* Set Key Store */
    status = phKeyStore_SetKey(&sSwkeyStore, 1, 0, PH_KEYSTORE_KEY_TYPE_MIFARE, &Key[0], 0);
    CHECK_STATUS(status);

    /* Initialize the MIFARE (R) Classic AL component - set NULL because
     * the keys are loaded in E2 by the function */
    /* phKeyStore_SetKey */
    status = phalMfc_Sw_Init(&salMfc, sizeof(phalMfc_Sw_DataParams_t), &spalMifare, &sSwkeyStore);
    CHECK_STATUS(status);

    /* Read the version of the reader IC */
#if defined NXPBUILD__PHHAL_HW_RC523
    status = phhalHw_Rc523_ReadRegister(&sHal_Nfc_Ic.sHal, PHHAL_HW_RC523_REG_VERSION, &bDataBuffer[0]);
    CHECK_SUCCESS(status);
    //~ DEBUG_PRINTF("\nReader chip PN512: 0x%02x\n", bDataBuffer[0]);
#endif
#if defined NXPBUILD__PHHAL_HW_RC663
    status = phhalHw_Rc663_ReadRegister(&sHal_Nfc_Ic.sHal, PHHAL_HW_RC663_REG_VERSION, &bDataBuffer[0]);
    CHECK_SUCCESS(status);
    //~ DEBUG_PRINTF("\nReader chip RC663: 0x%02x\n", bDataBuffer[0]);
#endif

    /* Return Success */
    return PH_ERR_SUCCESS;
}


int Mifare_init(Mifare *self, PyObject *args, PyObject *kwds) {

	Set_Interface_Link();
	Reset_reader_device();
	NfcRdLibInit();
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
phStatus_t  status = 0;
    uint16_t    wTagsDetected = 0;
    uint8_t     bUid[PHAC_DISCLOOP_I3P3A_MAX_UID_LENGTH];
    uint8_t     bUidSize;
    while(1)    /* Continuous loop */
    {
        DEBUG_PRINTF("\nReady to detect\n");
        
        do
        {
            /* Field OFF */
            status = phhalHw_FieldOff(pHal);
            CHECK_STATUS(status);

            /* Configure Discovery loop for Poll Mode */
            status = phacDiscLoop_SetConfig(&sDiscLoop, PHAC_DISCLOOP_CONFIG_NEXT_POLL_STATE, PHAC_DISCLOOP_POLL_STATE_DETECTION);
            CHECK_STATUS(status);

            /* Run Discovery loop */
            status = phacDiscLoop_Run(&sDiscLoop, PHAC_DISCLOOP_ENTRY_POINT_POLL);

        }while((status & PH_ERR_MASK) != PHAC_DISCLOOP_DEVICE_ACTIVATED); /* Exit on Card detection */

        /* Card detected */
        /* Get the tag types detected info */
        status = phacDiscLoop_GetConfig(&sDiscLoop, PHAC_DISCLOOP_CONFIG_TECH_DETECTED, &wTagsDetected);

        /* Check for Status */
        if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
        {
            /* Check for Type A tag detection */
            if (PHAC_DISCLOOP_CHECK_ANDMASK(wTagsDetected, PHAC_DISCLOOP_POS_BIT_MASK_A))
            {

							uint8_t byteBufferSize = sDiscLoop.sTypeATargetInfo.aTypeA_I3P3[0].bUidSize + 1;
					    uint8_t byteBuffer[sDiscLoop.sTypeATargetInfo.aTypeA_I3P3[0].bUidSize + 1];
						        uint8_t i;
					        char asciiBuffer[sDiscLoop.sTypeATargetInfo.aTypeA_I3P3[0].bUidSize + 1];
					
					        if (byteBufferSize + 1 > sDiscLoop.sTypeATargetInfo.aTypeA_I3P3[0].bUidSize + 1) {
					            // Truncate if we got back too much data
					            byteBufferSize = sDiscLoop.sTypeATargetInfo.aTypeA_I3P3[0].bUidSize;
					        }
					
					        for (i = 0; i < byteBufferSize; i++) {
					            sprintf(&asciiBuffer[2 * i], "%02X", sDiscLoop.sTypeATargetInfo.aTypeA_I3P3[0].aUid[i]);
					        }
					
					        return PyUnicode_FromString(asciiBuffer);
    

            }
        }
    }

    Py_RETURN_NONE;
}

PyObject *Mifare_read_block(Mifare *self, PyObject *args)
{
   	    uint8_t blockIdx;
	if (!PyArg_ParseTuple(args, "b", &blockIdx)) {
        return NULL;
    }




    
    
phStatus_t  status = 0;
    uint16_t    wTagsDetected = 0;
    uint8_t     bUid[PHAC_DISCLOOP_I3P3A_MAX_UID_LENGTH];
    uint8_t     bUidSize;

    /* Set Interrupt */

    /* Initialize library */

                        

                        /* Read data from block 4 */
                        status = phalMful_Read(&salMfc, blockIdx, bDataBuffer);
                            if (status != PH_ERR_SUCCESS) {
						        return PyErr_Format(ReadError, "Read failed: %04x", status);
						    }
                        /* Check for Status */

                        return Py_BuildValue("s#", &bDataBuffer[0], MFC_BLOCK_DATA_SIZE);


}


PyObject *Mifare_read_sign(Mifare *self)
{
  	const size_t bufferSize = PHAL_MFUL_SIG_LENGTH;
	uint8_t data[bufferSize];
	uint8_t    *sign = data;
	


    
    
phStatus_t  status = 0;
    uint16_t    wTagsDetected = 0;
    uint8_t     bUid[PHAC_DISCLOOP_I3P3A_MAX_UID_LENGTH];
    uint8_t     bUidSize;


                        /* Read data from block 4 */
                        status = phalMful_ReadSign(&salMfc,'\0', &sign);
                            if (status != PH_ERR_SUCCESS) {
								printf("\nStatus = %X\n",status);
						        return PyErr_Format(ReadError, "Read failed: %04x", status);
						    }
                        /* Check for Status */

                        return Py_BuildValue("s#", sign, bufferSize);


                       
                   

}

PyObject *Mifare_write_block(Mifare *self, PyObject *args)
{
     phStatus_t  status = 0;
     uint8_t blockIdx;
    uint8_t *data;
    int dataLen;

    uint16_t    wTagsDetected = 0;
    uint8_t     bUid[PHAC_DISCLOOP_I3P3A_MAX_UID_LENGTH];
    uint8_t     bUidSize;
    if (!PyArg_ParseTuple(args, "bs#", &blockIdx, &data, &dataLen)) {
		
        return NULL;
	}


                
                        status = phalMful_Write(&salMfc, blockIdx, data);

                        /* Check for Status */
                        if (status != PH_ERR_SUCCESS)
                        {
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


