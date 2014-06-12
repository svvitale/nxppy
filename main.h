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

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>

/* Configuration Headers */
/* Controls build behavior of components */
#include <ph_NxpBuild.h>
/* Status code definitions */
#include <ph_Status.h>

/* Reader Library Headers */
/* Generic ISO14443-3A Component of
 * Reader Library Framework */
#include <phpalI14443p3a.h>
/* Generic ISO14443-4 Component of
 * Reader Library Framework */
#include <phpalI14443p4.h>
/* Generic ISO14443-4A Component of
 * Reader Library Framework */
#include <phpalI14443p4a.h>
/* Generic MIFARE(R) Ultralight Application
 * Component of Reader Library Framework */
#include <phalMful.h>
#include <phalMfc.h>
/* Generic KeyStore Component of
 * Reader Library Framework */
/* In that example we don't use any
 * key. But we need the key components
 * for some function calls and you maight
 * need it when using crypto with
 * Ultralight-C cards. */
#include <phKeyStore.h>

#include <phpalSli15693.h>
#include <phpalSli15693_Sw.h>
#include <phpalFelica.h>
#include <phpalI14443p3b.h>

#define sak_ul                0x00
#define sak_ulc               0x00
#define sak_mini              0x09
#define sak_mfc_1k            0x08
#define sak_mfc_4k            0x18
#define sak_mfp_2k_sl1        0x08
#define sak_mfp_4k_sl1        0x18
#define sak_mfp_2k_sl2        0x10
#define sak_mfp_4k_sl2        0x11
#define sak_mfp_2k_sl3        0x20
#define sak_mfp_4k_sl3        0x20
#define sak_desfire           0x20
#define sak_jcop              0x28
#define sak_layer4            0x20

#define atqa_ul               0x4400
#define atqa_ulc              0x4400
#define atqa_mfc              0x0200
#define atqa_mfp_s            0x0400
#define atqa_mfp_s_2K         0x4400
#define atqa_mfp_x            0x4200
#define atqa_desfire          0x4403
#define atqa_jcop             0x0400
#define atqa_mini             0x0400
#define atqa_nPA              0x0800

#define mifare_ultralight     0x01
#define mifare_ultralight_c   0x02
#define mifare_classic        0x03
#define mifare_classic_1k     0x04
#define mifare_classic_4k     0x05
#define mifare_plus           0x06
#define mifare_plus_2k_sl1    0x07
#define mifare_plus_4k_sl1    0x08
#define mifare_plus_2k_sl2    0x09
#define mifare_plus_4k_sl2    0x0A
#define mifare_plus_2k_sl3    0x0B
#define mifare_plus_4k_sl3    0x0C
#define mifare_desfire        0x0D
#define jcop                  0x0F
#define mifare_mini           0x10
#define nPA                   0x11

#define RET_ANSWER				0x9000
#define FILE_NAME				0x840E
#define PSE1					"1PAY.SYS.DDF01"
#define PSE2					"2PAY.SYS.DDF01"

#define AID_JCOP							0xF0505053451010
#define AID_VISA							0xA0000000031010
#define AID_VISA_ELECTRON					0xA0000000032010
#define AID_VISA_VPAY						0xA0000000032020
#define AID_VISA_PLUS						0xA0000000038010
#define AID_MASTERCARD						0xA0000000041010
#define AID_MASTERCARD_WORLDWIDE			0xA0000000049999
#define AID_MASTERCARD_MAESTRO				0xA0000000043060
#define AID_MASTERCARD_CIRRUS				0xA0000000046000
#define AID_MASTERCARD_MAESTRO_UK			0xA0000000050001
#define AID_AMERICAN_EXPRESS				0xA00000002501
#define AID_LINK							0xA0000000291010
#define AID_CB								0xA0000000421010
#define AID_CB_DEBIT						0xA0000000422010
#define AID_JCB								0xA0000000651010
#define AID_DANKORT							0xA0000001211010
#define AID_COGEBAN							0xA0000001410001
#define AID_DINERSCLUB_DISCOVER				0xA0000001523010
#define AID_BANRISUL						0xA0000001544442
#define AID_SPAN2							0xA0000002281010 //??? Attention! There are two different descriptions at wikipedia EMV.
#define AID_INTERAC							0xA0000002771010
#define AID_DISCOVER						0xA0000003241010
#define AID_CHINA_UNIONPAY_DEBIT			0xA000000333010101
#define AID_CHINA_UNIONPAY_CREDIT			0xA000000333010102
#define AID_CHINA_UNIONPAY_QUASI_CREDIT		0xA000000333010103
//#define AID_ZKA								0xA0000003591010028001  //Too long value
//#define AID_EAPS							0xA00000035910100380  //Too long value
#define AID_VERVE							0xA0000003710001
#define AID_RUPAY							0xA0000005241010
#define AID_CHINA_UNIONPAY_ELECTRONIC_CASH	0xA000000333010106

#define JCOP							1
#define VISA							2
#define VISA_ELECTRON					3
#define VISA_VPAY						4
#define VISA_PLUS						5
#define MASTERCARD						6
#define MASTERCARD_WORLDWIDE			7
#define MASTERCARD_MAESTRO				8
#define MASTERCARD_CIRRUS				9
#define MASTERCARD_MAESTRO_UK			10
#define AMERICAN_EXPRESS				11
#define LINK							12
#define CB								13
#define CB_DEBIT						14
#define JCB								15
#define DANKORT							16
#define COGEBAN							17
#define DINERSCLUB_DISCOVER				18
#define BANRISUL						19
#define SPAN2							20
#define INTERAC							21
#define DISCOVER						22
#define CHINA_UNIONPAY_DEBIT			23
#define CHINA_UNIONPAY_CREDIT			24
#define CHINA_UNIONPAY_QUASI_CREDIT		25
//#define ZKA								26
//#define EAPS							27
#define VERVE							28
#define RUPAY							29
#define CHINA_UNIONPAY_ELECTRONIC_CASH	30

// Forward declarations
uint32_t DetectMifare(void *halReader);
uint8_t DetectTag15693(void *halReader);
uint8_t DetectFelica(void *halReader);
uint8_t DetectTypB(void *halReader);
phStatus_t readerIC_Cmd_SoftReset(void *halReader);
static int PaymentCard(void *pHal, uint8_t *uid);
static int Compare(uint8_t *input, uint8_t length);
static int Card_Scheme(uint8_t *input, uint8_t length);

// Arrays
/* Set the HEX code for the Select App command */
static const uint8_t AppSelection1[20] = {0x00, 0xA4, 0x04, 0x00, 0x0E, 0x31, 0x50, 0x41, 0x59,
		0x2E, 0x53, 0x59, 0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31, 0x00};
/* Set the HEX code for the Select App command */
static const uint8_t AppSelection2[20] = {0x00, 0xA4, 0x04, 0x00, 0x0E, 0x32, 0x50, 0x41, 0x59,
		0x2E, 0x53, 0x59, 0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31, 0x00};

int main(int argc, char **argv)
{
    phbalReg_R_Pi_spi_DataParams_t spi_balReader;
    void *balReader;

    phhalHw_Rc523_DataParams_t halReader;
    void *pHal;
    phStatus_t status;
    uint8_t blueboardType;
    uint8_t volatile card_or_tag_detected;

    uint8_t bHalBufferReader[0x40];

    /* Initialize the Reader BAL (Bus Abstraction Layer) component */
    status = phbalReg_R_Pi_spi_Init(&spi_balReader, sizeof(phbalReg_R_Pi_spi_DataParams_t));
    if (PH_ERR_SUCCESS != status)
    {
        printf("Failed to initialize SPI\n");
        return 1;
    }
    balReader = (void *)&spi_balReader;

    status = phbalReg_OpenPort((void*)balReader);
    if (PH_ERR_SUCCESS != status)
    {
        printf("Failed to open bal\n");
        return 2;
    }

    /* we have a board with PN512,
     * but on the software point of view,
     * it's compatible to the RC523 */
    status = phhalHw_Rc523_Init(&halReader,
                                sizeof(phhalHw_Rc523_DataParams_t),
                                balReader,
                                0,
                                bHalBufferReader,
                                sizeof(bHalBufferReader),
                                bHalBufferReader,
                                sizeof(bHalBufferReader));
    pHal = &halReader;

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

    /**************************************************************************
     * Begin the polling
     *************************************************************************/
    printf("/****** Begin Polling ******/\n");

    for(;;)
    {

        /*
         * Detecting Mifare cards */
        if (DetectMifare(pHal))
        {
            /* reset the IC  */
            readerIC_Cmd_SoftReset(pHal);
        }
        /*
         * Detecting Felica cards */
        else if (DetectFelica(pHal))
        {
            /* reset the IC  */
            readerIC_Cmd_SoftReset(pHal);
        }
        /*
         * Detecting Typ B cards */
        else if (DetectTypB(pHal))
        {
            /* reset the IC  */
            readerIC_Cmd_SoftReset(pHal);
        }
        else
        {
            printf("No card or Tag detected\n");
        }

        sleep(1);
    }

    phhalHw_FieldOff(pHal);
    return 0;
}

uint32_t DetectMifare(void *halReader)
{
    phpalI14443p4_Sw_DataParams_t I14443p4;
    phpalMifare_Sw_DataParams_t palMifare;
    phpalI14443p3a_Sw_DataParams_t I14443p3a;

    uint8_t cryptoEnc[8];
    uint8_t cryptoRng[8];

    phalMful_Sw_DataParams_t alMful;

    uint8_t bUid[10];
    uint8_t bLength;
    uint8_t bMoreCardsAvailable;
    uint32_t sak_atqa = 0;
    uint8_t pAtqa[2];
    uint8_t bSak[1];
    phStatus_t status;
    uint16_t detected_card = 0xFFFF;


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

    /* Activate one card after another
	 * and check it's type. */
	bMoreCardsAvailable = 1;
	uint8_t cards = 0;
	while (bMoreCardsAvailable)
	{
		cards++;
		/* Activate the communication layer part 3
		 * of the ISO 14443A standard. */
		status = phpalI14443p3a_ActivateCard(&I14443p3a,
				NULL, 0x00, bUid, &bLength, bSak, &bMoreCardsAvailable);
		uint8_t pUidOut[10];

		sak_atqa = bSak[0] << 24 | pAtqa[0] << 8 | pAtqa[1];
		sak_atqa &= 0xFFFF0FFF;

		if (!status)
		{
			// Detect mini or classic
			switch (sak_atqa)
			{
			case sak_mfc_1k << 24 | atqa_mfc:
				printf("MIFARE Classic detected\n");
				detected_card &= mifare_classic;
			break;
			case sak_mfc_4k << 24 | atqa_mfc:
				printf("MIFARE Classic detected\n");
				detected_card &= mifare_classic;
			break;
			case sak_mfp_2k_sl1 << 24 | atqa_mfp_s:
				printf("MIFARE Classic detected\n");
				detected_card &= mifare_classic;
			break;
			case sak_mini << 24 | atqa_mini:
				printf("MIFARE Mini detected\n");
				detected_card &= mifare_mini;
			break;
			case sak_mfp_4k_sl1 << 24 | atqa_mfp_s:
				printf("MIFARE Classic detected\n");
				detected_card &= mifare_classic;
			break;
			case sak_mfp_2k_sl1 << 24 | atqa_mfp_x:
				printf("MIFARE Classic detected\n");
				detected_card &= mifare_classic;
			break;
			case sak_mfp_4k_sl1 << 24 | atqa_mfp_x:
				printf("MIFARE Classic detected\n");
				detected_card &= mifare_classic;
			break;
			default:
			break;
			}

			if (detected_card == 0xFFFF)
			{
				sak_atqa = bSak[0] << 24 | pAtqa[0] << 8 | pAtqa[1];
				switch (sak_atqa)
				{
				case sak_ul << 24 | atqa_ul:
					printf("MIFARE Ultralight detected\n");
					detected_card &= mifare_ultralight;
				break;
				case sak_mfp_2k_sl2 << 24 | atqa_mfp_s:
					printf("MIFARE Plus detected\n");
					detected_card &= mifare_plus;
				break;
				case sak_mfp_2k_sl3 << 24 | atqa_mfp_s_2K:
					printf("MIFARE Plus detected\n");
					detected_card &= mifare_plus;
				break;
				case sak_mfp_2k_sl3 << 24 | atqa_mfp_s:
					printf("MIFARE Plus detected\n");
					detected_card &= mifare_plus;
				break;
				case sak_mfp_4k_sl2 << 24 | atqa_mfp_s:
					printf("MIFARE Plus detected\n");
					detected_card &= mifare_plus;
				break;
				case sak_mfp_2k_sl2 << 24 | atqa_mfp_x:
					printf("MIFARE Plus detected\n");
					detected_card &= mifare_plus;
				break;
				case sak_mfp_2k_sl3 << 24 | atqa_mfp_x:
					printf("MIFARE Plus detected\n");
					detected_card &= mifare_plus;
				break;
				case sak_mfp_4k_sl2 << 24 | atqa_mfp_x:
					printf("MIFARE Plus detected\n");
					detected_card &= mifare_plus;
				break;
				case sak_desfire << 24 | atqa_desfire:
					printf("MIFARE DESFire detected\n");
					detected_card &= mifare_desfire;
				break;
				case sak_jcop << 24 | atqa_jcop:
					printf("JCOP detected\n");
					detected_card &= jcop;
					PaymentCard(halReader, bUid);
				break;
				case sak_layer4 << 24 | atqa_nPA:
					printf("German eID (neuer Personalausweis) detected\n");
					detected_card &= nPA;
				break;
				default:
				break;
				}
			}
		}
		else
			// No MIFARE card is in the field
			return false;

		// There is a MIFARE card in the field, but we cannot determine it
		if (!status && detected_card == 0xFFFF)
		{
			printf("MIFARE card detected\n");
			return true;
		}
		printf("UID: ");
		uint8_t i;
		for(i = 0; i < bLength; i++)
		{
			printf("%02X ", bUid[i]);
		}
		printf("\n\n");
		status = phpalI14443p3a_HaltA(&I14443p3a);
		detected_card = 0xFFFF;
	}
	return detected_card;
}

uint8_t DetectFelica(void *halReader)
{
    phStatus_t status;
    uint8_t bBufferReader[0x60];
    uint8_t bMoreCardsAvailable;
    phpalFelica_Sw_DataParams_t palFelica;
    uint8_t bLength;
    uint8_t pIDmPMmOut[16];
    uint8_t pLenIDmPMmOut;

    uint8_t pIDmPMm[16], bIDmPMmLength = 0;
    uint8_t bNumTimeSlots = PHPAL_FELICA_NUMSLOTS_1;
    uint8_t pSysCode[2] = {0xFF, 0xFF};

    PH_CHECK_SUCCESS_FCT(status, phpalFelica_Sw_Init(&palFelica,
            sizeof(phpalFelica_Sw_DataParams_t), halReader));

    PH_CHECK_SUCCESS_FCT(status, phhalHw_ApplyProtocolSettings(halReader,
            PHHAL_HW_CARDTYPE_FELICA));

    PH_CHECK_SUCCESS_FCT(status, phhalHw_FieldReset(halReader));

    status = phpalFelica_ActivateCard(&palFelica,
            pIDmPMm, bIDmPMmLength, pSysCode, bNumTimeSlots, bBufferReader,
            &bLength, &bMoreCardsAvailable);

    phpalFelica_GetSerialNo(&palFelica, (uint8_t*)&pIDmPMmOut, &pLenIDmPMmOut);

    if (PH_ERR_SUCCESS == status)
    {
        if (pIDmPMmOut[0] == 0x01 && pIDmPMmOut[1] == 0xFE)
            printf("NFC Forum compliant device detected\n");
        else
            printf("JIS X 6319-4 compatible card detected\n");

        return true;
    }

    return false;
}

uint8_t DetectTypB(void *halReader)
{
    phStatus_t status = 0;
    phpalI14443p3b_Sw_DataParams_t  palI14443p3B;
    uint8_t pPupi[4];
    uint8_t bPupiLength = 0;
    uint8_t bNumSlots = 0;
    uint8_t bAfi = 0, pAtqb[13], bAtqbLen = 0, bExtAtqb = 0;
    uint8_t bCid = 0, bFsdi = 0, bDri = 0, bDsi = 0;
    uint8_t bMbli = 0, bMoreCardsAvaliable = 0;

    PH_CHECK_SUCCESS_FCT(status, phpalI14443p3b_Sw_Init(&palI14443p3B, sizeof(palI14443p3B),
                                                        halReader));

    PH_CHECK_SUCCESS_FCT(status, phhalHw_ApplyProtocolSettings(halReader,
                                                               PHHAL_HW_CARDTYPE_ISO14443B));

    PH_CHECK_SUCCESS_FCT(status, phhalHw_FieldReset(halReader));

    status = phpalI14443p3b_ActivateCard(&palI14443p3B, pPupi, bPupiLength, bNumSlots, bAfi,
            bExtAtqb, bFsdi, bCid, bDri, bDsi, pAtqb, &bAtqbLen, &bMbli,
            &bMoreCardsAvaliable);

    if (PH_ERR_SUCCESS == status)
    {
        printf("Type B card detected\n");
        return true;
    }

    return false;
}

phStatus_t readerIC_Cmd_SoftReset(void *halReader)
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

/*******************************************************************************
**   PaymentCard
**   This function checks whether the card has a PSE or not.
**   If it does, the AID of the card will be read and the
**   card type will be returned.
*******************************************************************************/
int PaymentCard(void *pHal, uint8_t *uid)
{
	phpalI14443p4_Sw_DataParams_t I14443p4;
	phpalMifare_Sw_DataParams_t palMifare;
	phpalI14443p3a_Sw_DataParams_t I14443p3a;
	phpalI14443p4a_Sw_DataParams_t I14443p4a;

	uint8_t cryptoEnc[8];
	uint8_t cryptoRng[8];

	phKeyStore_Sw_DataParams_t SwkeyStore;
	phKeyStore_Sw_KeyEntry_t   pKeyEntries;
	phKeyStore_Sw_KeyVersionPair_t   pKeyVersionPairs;
	phKeyStore_Sw_KUCEntry_t   pKUCEntries;

	phalMful_Sw_DataParams_t alMful;

	uint8_t bUid[10];
	uint8_t bLength;
	uint8_t bMoreCardsAvailable;
	uint32_t sak_atqa = 0;
	uint8_t pAtqa[2];
	uint8_t bSak[1];
	phStatus_t status;
	uint16_t detected_card = 0xFFFF;
	uint8_t bBufferReader[0x60];
	uint8_t **ppRxBuffer = (void *)&bBufferReader[0];
	uint16_t bRxLength;
	uint32_t volatile i;
	uint8_t ansSize = 0;
	uint16_t retValue;
	uint16_t fileName;
	uint8_t aidSize = 0;
	uint8_t cardType = 0;
	int pseFlag = 0;


	/* Initialize the 14443-3A PAL (Protocol Abstraction Layer) component */
	PH_CHECK_SUCCESS_FCT(status, phpalI14443p3a_Sw_Init(&I14443p3a,
			sizeof(phpalI14443p3a_Sw_DataParams_t), pHal));

	/* Initialize the 14443-4 PAL component */
	PH_CHECK_SUCCESS_FCT(status, phpalI14443p4_Sw_Init(&I14443p4,
			sizeof(phpalI14443p4_Sw_DataParams_t), pHal));

	/* Initialize the 14443-4A PAL component */
	PH_CHECK_SUCCESS_FCT(status, phpalI14443p4a_Sw_Init(&I14443p4a,
			sizeof(phpalI14443p4a_Sw_DataParams_t), pHal));

	/* Initialize the Mifare PAL component */
	PH_CHECK_SUCCESS_FCT(status, phpalMifare_Sw_Init(&palMifare,
			sizeof(phpalMifare_Sw_DataParams_t), pHal, &I14443p4));

	/* Initialize the keystore component */
	PH_CHECK_SUCCESS_FCT(status, phKeyStore_Sw_Init(&SwkeyStore, sizeof(phKeyStore_Sw_DataParams_t),
		&pKeyEntries, 1,&pKeyVersionPairs, 1, &pKUCEntries, 1));

	/* Initialize Ultralight(-C) AL component */
	PH_CHECK_SUCCESS_FCT(status, phalMful_Sw_Init(&alMful,
		  sizeof(phalMful_Sw_DataParams_t), &palMifare, &SwkeyStore,
		  &cryptoEnc, &cryptoRng));


	/* Reset the RF field */
	PH_CHECK_SUCCESS_FCT(status, phhalHw_FieldReset(pHal));

	/* Apply the type A protocol settings
	 * and activate the RF field. */
	PH_CHECK_SUCCESS_FCT(status,
			phhalHw_ApplyProtocolSettings(pHal, PHHAL_HW_CARDTYPE_ISO14443A));

	/* Empty the pAtqa */
	memset(pAtqa, '\0', 2);
	status = phpalI14443p3a_RequestA(&I14443p3a, pAtqa);

	/* Reset the RF field */
	PH_CHECK_SUCCESS_FCT(status, phhalHw_FieldReset(pHal));

	/* Empty the bSak */
	memset(bSak, '\0', 1);

	/* Get the right payment card,
	 * use it's UID. */
	bMoreCardsAvailable = 1;
	uint8_t cards = 0;
	while (bMoreCardsAvailable)
	{
		cards++;
		/* Activate the communication layer part 3
		 * of the ISO 14443A standard. */
		status = phpalI14443p3a_ActivateCard(&I14443p3a,
				NULL, 0x00, bUid, &bLength, bSak, &bMoreCardsAvailable);

		/* Check the UID of the active card with
		 * the UID of the payment card detected
		 * in detectMifare(). */
		for(i = 0; i < sizeof(uid); i++)
		{
			if(bUid[0] != uid[0])
			{
				status = phpalI14443p3a_HaltA(&I14443p3a);
				detected_card = 0xFFFF;
				break;
			}
		}
	}

	sak_atqa = bSak[0] << 24 | pAtqa[0] << 8 | pAtqa[1];
	sak_atqa &= 0xFFFF0FFF;

	if (PH_ERR_SUCCESS == status)
	{
		/* Iso-4 card, send RATS */
		PH_CHECK_SUCCESS_FCT(status, phpalI14443p4a_Rats(&I14443p4a,
				I14443p4a.bFsdi, I14443p4a.bCid, bBufferReader));
		printf("\n**** ATS successful");

		/* Iso-4 card, set protocol */
		PH_CHECK_SUCCESS_FCT(status, phpalI14443p4_SetProtocol(&I14443p4,
				PH_OFF, I14443p4a.bCid, PH_OFF, PH_OFF,
				I14443p4a.bFwi, I14443p4a.bFsdi, I14443p4a.bFsci));
		printf("\n**** Set Protocol successful");

		/* Let's perform the "AppSelection" command.
		 * We have to perform one of the following commands to find
		 * out which card this is.
		 * We start with the second one ('2PAY.SYS.DDF01') and when this one
		 * does not work, we check the other one ('1PAY.SYS.DDF01').
		 */

		/* Send the Application Selection code '2PAY.SYS.DDF01' to the card and get the card's answer. */
		printf("\nTry PSE 2PAY.SYS.DDF01.");
		memcpy(&bBufferReader[3], AppSelection2, sizeof(AppSelection2));
		PH_CHECK_SUCCESS_FCT(status, phpalI14443p4_Exchange(&I14443p4,
				PH_EXCHANGE_DEFAULT, &bBufferReader[3], sizeof(AppSelection2),
				(void *)&bBufferReader[0], &bRxLength));

		/* Check the return value. Get the output size and pick the return value. */
		ansSize = ppRxBuffer[0][1] + 2;
		retValue = ppRxBuffer[0][ansSize];
		retValue = (retValue << 8) | ppRxBuffer[0][ansSize + 1];
		printf("\nThe return value is: ");
		printf("%X", retValue);
		/* Check if the return value is an error code. When it is, do the same execution
		 * again, but with '1PAY.SYS.DDF01'. */
		if(retValue != RET_ANSWER)
		{
			printf("\nAn error code was returned. Try PSE 1PAY.SYS.DDF01.");
			memcpy(&bBufferReader[3], AppSelection1, sizeof(AppSelection1));
			PH_CHECK_SUCCESS_FCT(status, phpalI14443p4_Exchange(&I14443p4,
					PH_EXCHANGE_DEFAULT, &bBufferReader[3], sizeof(AppSelection1),
					(void *)&bBufferReader[0], &bRxLength));
			ansSize = ppRxBuffer[0][1] + 2;
			retValue = ppRxBuffer[0][ansSize];
			retValue = (retValue << 8) | ppRxBuffer[0][ansSize + 1];
			printf("\nThe return value is:");
			printf("%X", retValue);
		}
		/* Check the new return value. It it is an error code again, there is no PSE on the card. */
		if(retValue != RET_ANSWER)
		{
			printf("\nAn error code was returned. There is no PSE on this card.");
			return 0;
		}

		/* START! Let's parse the card's answer. First copy the card output to an array. */
		uint8_t appSelection[ansSize];

		for(i = 0; i < ansSize; i++)
		{
			appSelection[i] = ppRxBuffer[0][i];
		}
		printf("\nThe output is: ");
		for(i = 0; i < ansSize; i++)
		{
			printf("%X ", appSelection[i]);
		}

		/* Check the file name. It's supposed to be 0x840E. 0x0E is the size
		 * of the PSE, it should always be the same. '1PAY.SYS.DDF01' and '2PAY.SYS.DDF01' have 14 symbols. */
		fileName = appSelection[2];
		fileName = (fileName << 8) | appSelection[3];
		printf("\nThe file name is: ");
		printf("%X", fileName);
		if(fileName != FILE_NAME)
		{
			printf("\nWrong file name.");
			return 0;
		}

		/* Check with function Compare whether the PSE is correct. */
		pseFlag = Compare(&appSelection[4], appSelection[3]);
		if(pseFlag != 1)
		{
			printf("\nwrong PSE.");
			return 0;
		}

		/* Check the FCI Proprietary Template identifier byte and the its size. */
		if((appSelection[18] != 0xA5) && ((appSelection[1] - 18) != appSelection[20]))
		{
			printf("\nWrong FCI Proprietary Template.");
			return 0;
		}

		/* Check the ADF identifier byte. */
		if(appSelection[23] != 0x61)
		{
			printf("\nWrong ADF.");
			return 0;
		}

		/* Check the AID identifier byte. */
		if(appSelection[25] == 0x4F)
		{
			aidSize = appSelection[26];
		}
		else
		{
			printf("\nNo or wrong AID.");
			return 0;
		}
		/* The AID gets copied into an extra array. */
		uint8_t aid[aidSize];
		for(i = 0; i < aidSize; i++)
		{
			aid[i] = appSelection[27 + i];
		}
		printf("\nThe AID is: ");
		for(i = 0; i < aidSize; i++)
		{
			printf("%X ", aid[i]);
		}

		/* Check which kind of card is on the field. Card_Scheme returns a uint8_t value.
		 * With this value the card can be identified and use in further progress. */
		printf("\nCheck AID.");
		cardType = Card_Scheme(&aid[0], aidSize);
		switch(cardType)
			{
			case VISA:
				printf("\nVisa credit or debit Card");
				break;
			case VISA_ELECTRON:
				printf("\nVisa Electron Card");
				break;
			case VISA_VPAY:
				printf("\nVisa V PAY Card");
				break;
			case VISA_PLUS:
				printf("\nVisa Plus Card");
				break;
			case MASTERCARD:
				printf("\nMasterCard credit or debit Card");
				break;
			case MASTERCARD_WORLDWIDE:
				printf("\nMasterCard worldwide Card");
				break;
			case MASTERCARD_MAESTRO:
				printf("\nMasterCard Maestro (debit) Card");
				break;
			case MASTERCARD_CIRRUS:
				printf("\nMasterCard Cirrus (ATM only) Card");
				break;
			case MASTERCARD_MAESTRO_UK:
				printf("\nMasterCard Maestro UK (Switch) Card");
				break;
			case AMERICAN_EXPRESS:
				printf("\nAmerican Express Card");
				break;
			case LINK:
				printf("\nLINK (UK) (ATM) Card");
				break;
			case CB:
				printf("\nCB credit or debit Card");
				break;
			case CB_DEBIT:
				printf("\nCB debit only Card");
				break;
			case JCB:
				printf("\nJCB (Japan Credit Bureau) Card");
				break;
			case DANKORT:
				printf("\nDankort debit Card");
				break;
			case COGEBAN:
				printf("\nCoGeBan PagoBANCOMAT (Italy) Card");
				break;
			case DINERSCLUB_DISCOVER:
				printf("\nDiners Club/Discover Card");
				break;
			case BANRISUL:
				printf("\nBanrisul (Brasil) Card");
				break;
			case SPAN2:
				printf("\nSPAn2 (Saudi Arabia) Card");
				break;
			case INTERAC:
				printf("\nInterac (Canada) debit Card");
				break;
			case DISCOVER:
				printf("\nDiscover ZIP Card");
				break;
			case CHINA_UNIONPAY_DEBIT:
				printf("\nChina UnionPay debit Card");
				break;
			case CHINA_UNIONPAY_CREDIT:
				printf("\nChina UnionPay credit Card");
				break;
			case CHINA_UNIONPAY_QUASI_CREDIT:
				printf("\nChina UnionPay quasi credit Card");
				break;
			case CHINA_UNIONPAY_ELECTRONIC_CASH:
				printf("\nChina UnionPay Electronic Cash Card");
				break;
	/*			case ZKA:
				printf("\nZKA (Germany) (Girocard) Card");
				break;
			case EAPS:
				printf("\nEAPS BANCOMAT (Italy) Card");
				break;*/
			case VERVE:
				printf("\nVerve (Nigeria) Card");
				break;
			case RUPAY:
				printf("\nRuPay (India) Card");
				break;
			case JCOP:
				printf("\nJCOP Card");
				break;
			default:
				printf("\nOther Card");
				break;
			}

		PH_CHECK_SUCCESS_FCT(status, phpalI14443p4_Deselect(&I14443p4));
		printf("\n**** Deselect successful");
		printf("\n/****** End of execution ******/\n\n");

		return detected_card;
	}

	return detected_card;
}

/*******************************************************************************
**   Compare
**   This function checks the PSE of the card.
*******************************************************************************/
static int Compare(uint8_t *input, uint8_t length)
{
	uint8_t i = 0;
	for(i = 0; i < length; i++)
	{
		if(input[i] == PSE1[i] || input[i] == PSE2[i])
		{
			//nothing to be done. just check the next PSE value.
		}
		else
		{
			return 0;
		}
	}
	printf("\nPSE okay.");
	return 1;
}

/*******************************************************************************
**   Card_Scheme
**   This function checks the AID of the card.
*******************************************************************************/
static int Card_Scheme(uint8_t *input, uint8_t length)
{
	uint8_t i = 0;
	uint8_t j = length;
	uint8_t comp;
	uint8_t card = VISA;
	uint64_t ref = AID_VISA;

	for(i = 0; i < length; i++)
	{
		comp = (ref  >> (j - (i+1))*8);
		if(input[i] == comp)
		{
			//nothing to be done.
		}
		else
		{
			/* Get next AID and change card via card-number */
			switch(ref)
			{
			case AID_VISA:
				ref = AID_VISA_ELECTRON;
				card = VISA_ELECTRON;
				break;
			case AID_VISA_ELECTRON:
				ref = AID_VISA_VPAY;
				card = VISA_VPAY;
				break;
			case AID_VISA_VPAY:
				ref = AID_VISA_PLUS;
				card = VISA_PLUS;
				break;
			case AID_VISA_PLUS:
				ref = AID_MASTERCARD;
				card = MASTERCARD;
				break;
			case AID_MASTERCARD:
				ref = AID_MASTERCARD_WORLDWIDE;
				card = MASTERCARD_WORLDWIDE;
				break;
			case AID_MASTERCARD_WORLDWIDE:
				ref = AID_MASTERCARD_MAESTRO;
				card = MASTERCARD_MAESTRO;
				break;
			case AID_MASTERCARD_MAESTRO:
				ref = AID_MASTERCARD_CIRRUS;
				card = MASTERCARD_CIRRUS;
				break;
			case AID_MASTERCARD_CIRRUS:
				ref = AID_MASTERCARD_MAESTRO_UK;
				card = MASTERCARD_MAESTRO_UK;
				break;
			case AID_MASTERCARD_MAESTRO_UK:
				ref = AID_AMERICAN_EXPRESS;
				card = AMERICAN_EXPRESS;
				break;
			case AID_AMERICAN_EXPRESS:
				ref = AID_LINK;
				card = LINK;
				break;
			case AID_LINK:
				ref = AID_CB;
				card = CB;
				break;
			case AID_CB:
				ref = AID_CB_DEBIT;
				card = CB_DEBIT;
				break;
			case AID_CB_DEBIT:
				ref = AID_JCB;
				card = JCB;
				break;
			case AID_JCB:
				ref = AID_DANKORT;
				card = DANKORT;
				break;
			case AID_DANKORT:
				ref = AID_COGEBAN;
				card = COGEBAN;
				break;
			case AID_COGEBAN:
				ref = AID_DINERSCLUB_DISCOVER;
				card = DINERSCLUB_DISCOVER;
				break;
			case AID_DINERSCLUB_DISCOVER:
				ref = AID_BANRISUL;
				card = BANRISUL;
				break;
			case AID_BANRISUL:
				ref = AID_SPAN2;
				card = SPAN2;
				break;
			case AID_SPAN2:
				ref = AID_INTERAC;
				card = INTERAC;
				break;
			case AID_INTERAC:
				ref = AID_DISCOVER;
				card = DISCOVER;
				break;
			case AID_DISCOVER:
				ref = AID_CHINA_UNIONPAY_DEBIT;
				card = CHINA_UNIONPAY_DEBIT;
				break;
			case AID_CHINA_UNIONPAY_DEBIT:
				ref = AID_CHINA_UNIONPAY_CREDIT;
				card = CHINA_UNIONPAY_CREDIT;
				break;
			case AID_CHINA_UNIONPAY_CREDIT:
				ref = AID_CHINA_UNIONPAY_QUASI_CREDIT;
				card = CHINA_UNIONPAY_QUASI_CREDIT;
				break;
			case AID_CHINA_UNIONPAY_QUASI_CREDIT:
				ref = AID_CHINA_UNIONPAY_ELECTRONIC_CASH;
				card = CHINA_UNIONPAY_ELECTRONIC_CASH;
				break;
			case AID_CHINA_UNIONPAY_ELECTRONIC_CASH:
/*				ref = AID_ZKA;
				card = ZKA;
				break;
			case AID_ZKA:
				ref = AID_EAPS;
				card = EAPS;
				break;
			case AID_EAPS:*/
				ref = AID_VERVE;
				card = VERVE;
				break;
			case AID_VERVE:
				ref = AID_RUPAY;
				card = RUPAY;
				break;
			case AID_RUPAY:
				ref = AID_JCOP;
				card = JCOP;
				break;
			case AID_JCOP:
				card = 0;
				break;
			default:
				card = 0;
				printf("\nOther Card or Wrong Card.");
				break;
			}
			/* Reset the counter to start from 0 for the new AID */
			if(card != 0)
			{
				i = 0;
				continue;
			}
			else
			{
				break;
			}
		}
	}
	return card;
}
