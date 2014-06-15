#include "Mifare.h"

int init(phbalReg_R_Pi_spi_DataParams_t *balReader, phhalHw_Rc523_DataParams_t *pHal) {

    phStatus_t status;

    uint8_t bHalBufferReader[0x40];

    /* Initialize the Reader BAL (Bus Abstraction Layer) component */
    status = phbalReg_R_Pi_spi_Init(balReader, sizeof(phbalReg_R_Pi_spi_DataParams_t));
    if (PH_ERR_SUCCESS != status)
    {
        printf("Failed to initialize SPI\n");
        return 1;
    }

    status = phbalReg_OpenPort((void*)balReader);
    if (PH_ERR_SUCCESS != status)
    {
        printf("Failed to open bal\n");
        return 2;
    }

    /* we have a board with PN512,
    * but on the software point of view,
    * it's compatible to the RC523 */
    status = phhalHw_Rc523_Init(pHal,
        sizeof(phhalHw_Rc523_DataParams_t),
        balReader,
        0,
        bHalBufferReader,
        sizeof(bHalBufferReader),
        bHalBufferReader,
        sizeof(bHalBufferReader));

    if (PH_ERR_SUCCESS != status)
    {
        printf("Failed to initialize the HAL\n");
        return 3;
    }

    /* Set the HAL configuration to SPI */
    status = phhalHw_SetConfig(pHal, PHHAL_HW_CONFIG_BAL_CONNECTION,
        PHHAL_HW_BAL_CONNECTION_SPI);
    if (PH_ERR_SUCCESS != status)
    {
        printf("Failed to set hal connection SPI\n");
        return 4;
    }

    return 0;
}

uint32_t DetectMifare(void *halReader, uint8_t uid[], uint8_t *uidLength)
{
    phpalI14443p4_Sw_DataParams_t I14443p4;
    phpalMifare_Sw_DataParams_t palMifare;
    phpalI14443p3a_Sw_DataParams_t I14443p3a;

    phalMful_Sw_DataParams_t alMful;

    uint8_t bMoreCardsAvailable;
    uint8_t pAtqa[2];
    uint8_t bSak[1];
    phStatus_t status;

    /* Initialize the 14443-3A PAL (Protocol Abstraction Layer) component */
    PH_CHECK_SUCCESS_FCT(status, phpalI14443p3a_Sw_Init(&I14443p3a,
        sizeof(phpalI14443p3a_Sw_DataParams_t), halReader));

    /* Initialize the 14443-4 PAL component */
    PH_CHECK_SUCCESS_FCT(status, phpalI14443p4_Sw_Init(&I14443p4,
        sizeof(phpalI14443p4_Sw_DataParams_t), halReader));

    /* Initialize the Mifare PAL component */
    PH_CHECK_SUCCESS_FCT(status, phpalMifare_Sw_Init(&palMifare,
        sizeof(phpalMifare_Sw_DataParams_t), halReader, &I14443p4));

    /* Initialize Ultralight(-C) AL component */
    PH_CHECK_SUCCESS_FCT(status, phalMful_Sw_Init(&alMful,
        sizeof(phalMful_Sw_DataParams_t), &palMifare, NULL, NULL, NULL));

    /* Reset the RF field */
    PH_CHECK_SUCCESS_FCT(status, phhalHw_FieldReset(halReader));

    /* Apply the type A protocol settings
    * and activate the RF field. */
    PH_CHECK_SUCCESS_FCT(status,
        phhalHw_ApplyProtocolSettings(halReader, PHHAL_HW_CARDTYPE_ISO14443A));

    /* Empty the pAtqa */
    memset(pAtqa, '\0', 2);
    status = phpalI14443p3a_RequestA(&I14443p3a, pAtqa);

    /* Reset the RF field */
    PH_CHECK_SUCCESS_FCT(status, phhalHw_FieldReset(halReader));

    /* Empty the bSak */
    memset(bSak, '\0', 1);

    /* Activate the communication layer part 3
    * of the ISO 14443A standard. */
    status = phpalI14443p3a_ActivateCard(&I14443p3a,
        NULL, 0x00, uid, uidLength, bSak, &bMoreCardsAvailable);

    return status;
}

phStatus_t readerIC_Cmd_SoftReset(phhalHw_Rc523_DataParams_t *halReader)
{
    phStatus_t status = PH_ERR_INVALID_DATA_PARAMS;

    switch (PH_GET_COMPID(halReader))
    {
    case PHHAL_HW_RC523_ID:
        status = phhalHw_Rc523_Cmd_SoftReset(halReader);
        break;
    }

    return status;
}
