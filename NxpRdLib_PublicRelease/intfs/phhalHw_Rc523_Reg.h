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
* Rc523 register definitions for Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:27:18 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHHALHW_RC523_REG_H
#define PHHALHW_RC523_REG_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/** \defgroup phhalHw_Rc523_Reg Register Definitions
* \brief Register definitions.
* @{
*/

/** \name Register definitions of Page 0
*  Following all register defintions of Page 0.
*/
/*@{*/
/** \brief Page register.
*/
#define PHHAL_HW_RC523_REG_PAGE         0x00U

/** \brief Command register.
*
* Contains Command bits, PowerDown bit and bit to switch receiver off.
*/
#define PHHAL_HW_RC523_REG_COMMAND      0x01U

/** \brief CommIEn register.
*
* Contains Communication interrupt enable bits and bit for Interrupt inversion.
*/
#define PHHAL_HW_RC523_REG_COMMIEN      0x02U

/** \brief DivIEn register.
*
* Contains RfOn, RfOff, CRC and Mode Interrupt enable and bit to switch Interrupt pin to PushPull mode.
*/
#define PHHAL_HW_RC523_REG_DIVIEN       0x03U

/** \brief CommIrq register.
*
* Contains Communication interrupt request bits.
*/
#define PHHAL_HW_RC523_REG_COMMIRQ      0x04U

/** \brief DivIrq register.
*
* Contains RfOn, RfOff, CRC and Mode Interrupt request.
*/
#define PHHAL_HW_RC523_REG_DIVIRQ       0x05U

/** \brief Error register.
*
* Contains Protocol, Parity, CRC, Collision, Buffer overflow, Temperature and RF error flags.
*/
#define PHHAL_HW_RC523_REG_ERROR        0x06U

/** \brief Status1 register.
*
* Contains status information about Lo- and HiAlert, RF-field on, Timer, Interrupt request and CRC status.
*/
#define PHHAL_HW_RC523_REG_STATUS1      0x07U

/** \brief Status2 register.
*
* Contains information about internal states and Temperature sensor switch.
*/
#define PHHAL_HW_RC523_REG_STATUS2      0x08U

/** \brief Fifo register.
*
* Read/Write Fifo. Writing to register increments the Fifo level, reading decrements it.
*/
#define PHHAL_HW_RC523_REG_FIFODATA     0x09U

/** \brief FifoLevel register.
*
* Contains the actual level (number of bytes) of the Fifo.
*/
#define PHHAL_HW_RC523_REG_FIFOLEVEL    0x0AU

/** \brief WaterLevel register.
*
* Contains the Waterlevel value for the Fifo.
*/
#define PHHAL_HW_RC523_REG_WATERLEVEL   0x0BU

/** \brief Control register.
*
* Contains information about last received bits, and to Start and stop the Timer unit.
*/
#define PHHAL_HW_RC523_REG_CONTROL      0x0CU

/** \brief Bitframing register.
*
* Contains information of last bits to send, to align received bits in Fifo and activate sending.
*/
#define PHHAL_HW_RC523_REG_BITFRAMING   0x0DU

/** \brief Collision register.
*
* Contains all necessary bits for Collision handling.
*/
#define PHHAL_HW_RC523_REG_COLL         0x0EU
/*@}*/

/** \name Register definitions of Page 1
*  Following all register defintions of Page 1.
*/
/*@{*/
/** \brief Mode register.
*
* Contains bits for auto wait on Rf and MSB first for CRC calculation.
*/
#define PHHAL_HW_RC523_REG_MODE         0x11U

/** \brief TxMode register.
*
* Contains Transmit Framing, Speed, CRC enable, bit for inverse mode and TXMix bit.
*/
#define PHHAL_HW_RC523_REG_TXMODE       0x12U

/** \brief RxMode register.
*
* Contains Transmit Framing, Speed, CRC enable, bit for multiple receive and to filter errors.
*/
#define PHHAL_HW_RC523_REG_RXMODE       0x13U

/** \brief TxControl register.
*
* Contains bits to activate and configure Tx1 and Tx2 and bit to activate 100% modulation.
*/
#define PHHAL_HW_RC523_REG_TXCONTROL    0x14U

/** \brief TxAsk register.
*
* Contains Tx ASK settings.
*/
#define PHHAL_HW_RC523_REG_TXASK        0x15U

/** \brief TxSel register.
*
* Contains SigoutSel, DriverSel and LoadModSel bits.
*/
#define PHHAL_HW_RC523_REG_TXSEL        0x16U

/** \brief RxSel register.
*
* Contains UartSel and RxWait bits.
*/
#define PHHAL_HW_RC523_REG_RXSEL        0x17U

/** \brief RxThreshold register.
*
* Contains MinLevel and CollLevel for detection.
*/
#define PHHAL_HW_RC523_REG_RXTHRESHOLD  0x18U

/** \brief Demod register.
*
* Contains bits for time constants, hysteresis and IQ demodulator settings.
*/
#define PHHAL_HW_RC523_REG_DEMOD        0x19U

/** \brief MfTx register.
*
* Mifare transmission settings.
*/
#define PHHAL_HW_RC523_REG_MFTX         0x1CU

/** \brief MfRx register.
*
* Mifare reception settings.
*/
#define PHHAL_HW_RC523_REG_MFRX         0x1DU

/** \brief TypeB register.
*
* Used for ISO/IEC 14443 Type B configuration.
*/
#define PHHAL_HW_RC523_REG_TYPEB        0x1EU

/** \brief SerialSpeed register.
*
* Contains speed settings for RS232 interface.
*/
#define PHHAL_HW_RC523_REG_SERIALSPEED  0x1FU
/*@}*/

/** \name Register definitions of Page 2
*  Following all register defintions of Page 2.
*/
/*@{*/
/** \brief CRCResult1 register.
*
* Contains MSByte of CRC Result.
*/
#define PHHAL_HW_RC523_REG_CRCRESULT1   0x21U

/** \brief CRCResult2 register.
*
* Contains LSByte of CRC Result.
*/
#define PHHAL_HW_RC523_REG_CRCRESULT2   0x22U

/** \brief GSNOff register.
*
* Contains the conductance and the modulation settings for the N-MOS transistor for LoadModulation.
*/
#define PHHAL_HW_RC523_REG_GSNOFF       0x23U

/** \brief ModWidth register.
*
* Contains modulation width setting.
*/
#define PHHAL_HW_RC523_REG_MODWIDTH     0x24U

/** \brief RfCfg register.
*
* Contains sensitivity of Rf Level detector, the receiver gain factor and the RfLevelAmp.
*/
#define PHHAL_HW_RC523_REG_RFCFG        0x26U

/** \brief GSN register.
*
* Contains the conductance and the modulation settings for the N-MOS transistor during active modulation.
*/
#define PHHAL_HW_RC523_REG_GSN          0x27U

/** \brief CWGSP register.
*
* Contains the conductance for the P-Mos transistor.
*/
#define PHHAL_HW_RC523_REG_CWGSP        0x28U

/** \brief MODGSP register.
*
* Contains the modulation index for the PMos transistor.
*/
#define PHHAL_HW_RC523_REG_MODGSP       0x29U

/** \brief TMode register.
*
* Contains all settings for the timer and the highest 4 bits of the prescaler.
*/
#define PHHAL_HW_RC523_REG_TMODE        0x2AU

/** \brief TPrescaler register.
*
* Contais the lowest byte of the prescaler.
*/
#define PHHAL_HW_RC523_REG_TPRESCALER   0x2BU

/** \brief TReloadHi register.
*
* Contains the high byte of the reload value.
*/
#define PHHAL_HW_RC523_REG_TRELOADHI    0x2CU

/** \brief TReloadLo register.
*
* Contains the low byte of the reload value.
*/
#define PHHAL_HW_RC523_REG_TRELOADLO    0x2DU

/** \brief TCounterValHi register.
*
* Contains the high byte of the counter value.
*/
#define PHHAL_HW_RC523_REG_TCOUNTERVALHI    0x2EU

/** \brief TCounterValLo register.
*
* Contains the low byte of the counter value.
*/
#define PHHAL_HW_RC523_REG_TCOUNTERVALLO    0x2FU
/*@}*/

/** \name Register definitions of Page 3
*  Following all register defintions of Page 3.
*/
/*@{*/
#define PHHAL_HW_RC523_REG_TESTSEL1         0x31U   /**< Test register. */
#define PHHAL_HW_RC523_REG_TESTSEL2         0x32U   /**< Test register. */
#define PHHAL_HW_RC523_REG_TESTPINEN        0x33U   /**< Test register. */
#define PHHAL_HW_RC523_REG_TESTPINVALUE     0x34U   /**< Test register. */
#define PHHAL_HW_RC523_REG_TESTBUS          0x35U   /**< Test register .*/
#define PHHAL_HW_RC523_REG_AUTOTEST         0x36U   /**< Test register. */
#define PHHAL_HW_RC523_REG_VERSION          0x37U   /**< Contains the product number and the version. */
#define PHHAL_HW_RC523_REG_ANALOGTEST       0x38U   /**< Test register. */
#define PHHAL_HW_RC523_REG_TESTDAC1         0x39U   /**< Test register. */
#define PHHAL_HW_RC523_REG_TESTDAC2         0x3AU   /**< Test register. */
#define PHHAL_HW_RC523_REG_TESTADC          0x3BU   /**< Test register. */
/*@}*/

/** \name Command Register Contents (0x01)
*/
/*@{*/
#define PHHAL_HW_RC523_BIT_RCVOFF       0x20U   /**< Switches the receiver on/off. */
#define PHHAL_HW_RC523_BIT_POWERDOWN    0x10U   /**< Switches Ic to Power Down mode. */
#define PHHAL_HW_RC523_CMD_IDLE         0x00U   /**< No action; cancels current command execution. */
#define PHHAL_HW_RC523_CMD_MEM          0x01U   /**< Copy configuration data from Fifo to internal Buffer or if Fifo empty vice versa. */
#define PHHAL_HW_RC523_CMD_RANDOMIDS    0x02U   /**< Replaces stored IDs with random ones. */
/** \brief Activate the CRC-Coprocessor.
*
* <b>Remark:</b> The result of the CRC calculation can be read from e.g. #PHHAL_HW_RC523_REG_CRCRESULT1.
*/
#define PHHAL_HW_RC523_CMD_CALCCRC      0x03U
#define PHHAL_HW_RC523_CMD_TRANSMIT     0x04U   /**< Transmits data from the FIFO buffer to Card. */
#define PHHAL_HW_RC523_CMD_NOCMDCHANGE  0x07U   /**< No change; Use together with e.g. #PHHAL_HW_RC523_BIT_POWERDOWN to keep current command-state. */
#define PHHAL_HW_RC523_CMD_RECEIVE      0x08U   /**< Activates the receiver circuitry. */
#define PHHAL_HW_RC523_CMD_TRANSCEIVE   0x0CU   /**< Like #PHHAL_HW_RC523_CMD_TRANSMIT but automatically activates the receiver after transmission is finished. */
#define PHHAL_HW_RC523_CMD_AUTOCOLL     0x0DU   /**< Handles Felica polling or MIFARE anticollision in Target mode. */
#define PHHAL_HW_RC523_CMD_AUTHENT      0x0EU   /**< Performs the Mifare Classic authentication (in Mifare Reader/Writer mode only). */
#define PHHAL_HW_RC523_CMD_SOFTRESET    0x0FU   /**< Resets the IC. */
#define PHHAL_HW_RC523_MASK_COMMAND     0x0FU   /**< Mask for Command-bits. */
/*@}*/

/** \name CommIEn/CommIrq Register Contents (0x02/0x04)
*/
/*@{*/
#define PHHAL_HW_RC523_BIT_SET          0x80U   /**< Bit position to set/clear dedicated IRQ bits. */
#define PHHAL_HW_RC523_BIT_IRQINV       0x80U   /**< Inverts the output of IRQ Pin. */
#define PHHAL_HW_RC523_BIT_TXI          0x40U   /**< Bit position for Transmit Interrupt Enable/Request. */
#define PHHAL_HW_RC523_BIT_RXI          0x20U   /**< Bit position for Receive Interrupt Enable/Request. */
#define PHHAL_HW_RC523_BIT_IDLEI        0x10U   /**< Bit position for Idle Interrupt Enable/Request. */
#define PHHAL_HW_RC523_BIT_HIALERTI     0x08U   /**< Bit position for HiAlert Interrupt Enable/Request. */
#define PHHAL_HW_RC523_BIT_LOALERTI     0x04U   /**< Bit position for LoAlert Interrupt Enable/Request. */
#define PHHAL_HW_RC523_BIT_ERRI         0x02U   /**< Bit position for Error Interrupt Enable/Request. */
#define PHHAL_HW_RC523_BIT_TIMERI       0x01U   /**< Bit position for Timer Interrupt Enable/Request. */
/*@}*/

/** \name DivIEn/DivIrq Register Contents (0x03/0x05)
*/
/*@{*/
/* #define PHHAL_HW_RC523_BIT_SET          0x80U */
#define PHHAL_HW_RC523_BIT_IRQPUSHPULL  0x80U   /**< Sets the IRQ pin to Push Pull mode. */
#define PHHAL_HW_RC523_BIT_MFINACT      0x10U   /**< Bit position for MfInAct Interrupt Enable/Request. */
#define PHHAL_HW_RC523_BIT_CRCI         0x04U   /**< Bit position for CRC Interrupt Enable/Request. */
/*@}*/

/** \name Error Register Contents (0x06)
*/
/*@{*/
#define PHHAL_HW_RC523_BIT_WRERR        0x80U   /**< Bit position for Write Access Error. */
#define PHHAL_HW_RC523_BIT_TEMPERR      0x40U   /**< Bit position for Temerature Error. */
#define PHHAL_HW_RC523_BIT_BUFFEROVFL   0x10U   /**< Bit position for Buffer Overflow Error. */
#define PHHAL_HW_RC523_BIT_COLLERR      0x08U   /**< Bit position for Collision Error. */
#define PHHAL_HW_RC523_BIT_CRCERR       0x04U   /**< Bit position for CRC Error. */
#define PHHAL_HW_RC523_BIT_PARITYERR    0x02U   /**< Bit position for Parity Error. */
#define PHHAL_HW_RC523_BIT_PROTERR      0x01U   /**< Bit position for Protocol Error. */
/*@}*/

/** \name Status1 Register Contents (0x07)
*/
/*@{*/
#define PHHAL_HW_RC523_BIT_CRCOK        0x40U   /**< Bit position for status CRC OK. */
#define PHHAL_HW_RC523_BIT_CRCREADY     0x20U   /**< Bit position for status CRC Ready. */
#define PHHAL_HW_RC523_BIT_IRQ          0x10U   /**< Bit position for status IRQ is active. */
#define PHHAL_HW_RC523_BIT_TRUNNUNG     0x08U   /**< Bit position for status Timer is running. */
#define PHHAL_HW_RC523_BIT_HIALERT      0x02U   /**< Bit position for status HiAlert. */
#define PHHAL_HW_RC523_BIT_LOALERT      0x01U   /**< Bit position for status LoAlert. */
/*@}*/

/** \name Status2 Register Contents (0x08)
*/
/*@{*/
#define PHHAL_HW_RC523_BIT_TEMPSENSOFF  0x80U   /**< Bit position to switch Temperture sensors on/off. */
#define PHHAL_HW_RC523_BIT_I2CFORCEHS   0x40U   /**< Bit position to forece High speed mode for I2C Interface. */
#define PHHAL_HW_RC523_BIT_CRYPTO1ON    0x08U   /**< Bit position for reader status Crypto is on. */
/*@}*/

/** \name FifoLevel Register Contents (0x0A)
*/
/*@{*/
#define PHHAL_HW_RC523_BIT_FLUSHBUFFER  0x80U   /**< Clears Fifo buffer if set to 1. */
/*@}*/

/** \name WaterLevel Register Contents (0x0B)
*/
/*@{*/
#define PHHAL_HW_RC523_MASK_WATERLEVEL  0x3FU   /**< Bitmask for Waterlevel bits. */
/*@}*/

/** \name Control Register Contents (0x0C)
*/
/*@{*/
#define PHHAL_HW_RC523_BIT_TSTOPNOW     0x80U   /**< Stops timer if set to 1. */
#define PHHAL_HW_RC523_BIT_TSTARTNOW    0x40U   /**< Starts timer if set to 1. */
#define PHHAL_HW_RC523_BIT_INITIATOR    0x10U   /**< If set to 1, the IC acts as initiator, otherwise as target. */
#define PHHAL_HW_RC523_MASK_RXBITS      0x07U   /**< Bitmask for RxLast bits. */
/*@}*/

/** \name BitFraming Register Contents (0x0D)
*/
/*@{*/
#define PHHAL_HW_RC523_BIT_STARTSEND    0x80U   /**< Starts transmission in transceive command if set to 1. */
#define PHHAL_HW_RC523_MASK_TXBITS      0x07U   /**< Bitmask for TxLast bits. */
#define PHHAL_HW_RC523_MASK_RXALIGN     0x70U   /**< Bitmask for RxAlign bits. */
/*@}*/

/** \name Collision Register Contents (0x0E)
*/
/*@{*/
#define PHHAL_HW_RC523_BIT_VALUESAFTERCOLL  0x80U   /**< Activates mode to keep data after collision. */
#define PHHAL_HW_RC523_BIT_COLLPOSNOTVALID  0x20U   /**< Whether collision position is valid or not. */
#define PHHAL_HW_RC523_MASK_COLLPOS         0x1FU   /**< Bitmask for CollPos bits. */
/*@}*/

/** \name Mode Register Contents (0x11)
*/
/*@{*/
#define PHHAL_HW_RC523_BIT_MSBFIRST     0x80U   /**< Sets CRC coprocessor with MSB first. */
#define PHHAL_HW_RC523_BIT_TXWAITRF     0x20U   /**< Waits until RF is enabled until transmission is startet, else starts immideately. */
#define PHHAL_HW_RC523_BIT_POLMFIN      0x08U   /**< Inverts polarity of MfinActIrq. If bit is set to 1 IRQ occures when Sigin line is 0. */
#define PHHAL_HW_RC523_BIT_MODEDETOFF   0x04U   /**< Set to logic 1, the internal mode detector is switched off during #PHHAL_HW_RC523_CMD_AUTOCOLL. */
#define PHHAL_HW_RC523_MASK_CRCPRESET   0x03U   /**< Bitmask for CRCPreset bits. */
/*@}*/

/** \name TxMode / RxMode Register Contents (0x12/0x13)
*/
/*@{*/
#define PHHAL_HW_RC523_BIT_CRCEN        0x80U   /**< Activates transmit or receive CRC. */
#define PHHAL_HW_RC523_BIT_848KBPS      0x30U   /**< Activates speed of 848kbps. */
#define PHHAL_HW_RC523_BIT_424KBPS      0x20U   /**< Activates speed of 424kbps. */
#define PHHAL_HW_RC523_BIT_212KBPS      0x10U   /**< Activates speed of 212kbps. */
#define PHHAL_HW_RC523_BIT_106KBPS      0x00U   /**< Activates speed of 106kbps. */
#define PHHAL_HW_RC523_BIT_INVMOD       0x08U   /**< Activates inverted transmission mode. */
#define PHHAL_HW_RC523_BIT_RXNOERR      0x08U   /**< If set, receiver ignores less than 4 bits. */
#define PHHAL_HW_RC523_BIT_RXMULTIPLE   0x04U   /**< Activates reception mode for multiple responses. */
#define PHHAL_HW_RC523_BIT_TYPEB        0x03U   /**< Activates Type B communication mode. */
#define PHHAL_HW_RC523_BIT_FELICA       0x02U   /**< Activates Felica communication mode. */
#define PHHAL_HW_RC523_BIT_ACTIVE       0x01U   /**< Activates Active communication mode. */
#define PHHAL_HW_RC523_BIT_MIFARE       0x00U   /**< Activates Mifare communication mode. */
#define PHHAL_HW_RC523_MASK_SPEED       0x70U   /**< Bitmask for Tx/RxSpeed bits. */
#define PHHAL_HW_RC523_MASK_FRAMING     0x03U   /**< Bitmask for Tx/RxFraming bits. */
/*@}*/

/** \name TxControl Register Contents (0x14)
*/
/*@{*/
#define PHHAL_HW_RC523_BIT_INVTX2ON     0x80U   /**< Inverts the Tx2 output if drivers are switched on. */
#define PHHAL_HW_RC523_BIT_INVTX1ON     0x40U   /**< Inverts the Tx1 output if drivers are switched on. */
#define PHHAL_HW_RC523_BIT_INVTX2OFF    0x20U   /**< Inverts the Tx2 output if drivers are switched off. */
#define PHHAL_HW_RC523_BIT_INVTX1OFF    0x10U   /**< Inverts the Tx1 output if drivers are switched off. */
#define PHHAL_HW_RC523_BIT_TX2CW        0x08U   /**< Does not modulate the Tx2 output, only constant wave. */
#define PHHAL_HW_RC523_BIT_CHECKRF      0x04U   /**< Set to logic 1, RF field cannot be activated if external RF field is detected. */
#define PHHAL_HW_RC523_BIT_TX2RFEN      0x02U   /**< Switches the driver for Tx2 pin on. */
#define PHHAL_HW_RC523_BIT_TX1RFEN      0x01U   /**< Switches the driver for Tx1 pin on. */
/*@}*/

/** \name TxASK Register Contents (0x15)
*/
/*@{*/
#define PHHAL_HW_RC523_BIT_FORCE100ASK  0x40U   /**< Activates 100%ASK mode independent of driver settings. */
/*@}*/

/** \name TxSel Register Contents (0x16)
*/
/*@{*/
#define PHHAL_HW_RC523_MASK_DRIVERSEL   0x30U   /**< Bitmask for DriverSel bits. */
#define PHHAL_HW_RC523_MASK_MFOUTSEL    0x0FU   /**< Bitmask for MfOutSel bits. */
/*@}*/

/** \name RxSel Register Contents (0x17)
*/
/*@{*/
#define PHHAL_HW_RC523_MASK_UARTSEL     0xC0U   /**< Bitmask for UartSel bits. */
#define PHHAL_HW_RC523_MASK_RXWAIT      0x3FU   /**< Bitmask for RxWait bits. */
/*@}*/

/** \name RxThreshold Register Contents (0x18)
*/
/*@{*/
#define PHHAL_HW_RC523_MASK_MINLEVEL    0xF0U   /**< Bitmask for MinLevel bits. */
#define PHHAL_HW_RC523_MASK_COLLEVEL    0x07U   /**< Bitmask for CollLevel bits. */
/*@}*/

/** \name Demod Register Contents (0x19)
*/
/*@{*/
/**
* If set and the lower bit of AddIQ is cleared, the receiving is fixed to I channel.\n
* If set and the lower bit of AddIQ is set, the receiving is fixed to Q channel.
*/
#define PHHAL_HW_RC523_BIT_FIXIQ        0x20U
#define PHHAL_HW_RC523_MASK_ADDIQ       0xC0U   /**< Bitmask for ADDIQ bits. */
#define PHHAL_HW_RC523_MASK_TAURCV      0x0CU   /**< Bitmask for TauRcv bits. */
#define PHHAL_HW_RC523_MASK_TAUSYNC     0x03U   /**< Bitmask for TauSync bits. */
/*@}*/

/** \name MfTx Register Contents (0x1C)
*/
/*@{*/
#define PHHAL_HW_RC523_MASK_TXWAIT      0x03U   /**< Bitmask for TxWait bits. */
/*@}*/

/** \name MfRx Register Contents (0x1D)
*/
/*@{*/
#define PHHAL_HW_RC523_BIT_PARITYDISABLE    0x10U   /**< Disables the parity generation and sending independent from the mode. */
/*@}*/

/** \name RFCfg Register Contents (0x26)
*/
/*@{*/
#define PHHAL_HW_RC523_MASK_RXGAIN      0x70U   /**< Bitmask for RxGain bits. */
/*@}*/

/** \name GsN Register Contents (0x27)
*/
/*@{*/
#define PHHAL_HW_RC523_MASK_CWGSN       0xF0U   /**< Bitmask for CWGsN bits. */
#define PHHAL_HW_RC523_MASK_MODGSN      0x0FU   /**< Bitmask for ModGsN bits. */
/*@}*/

/** \name CWGsP Register Contents (0x28)
*/
/*@{*/
#define PHHAL_HW_RC523_MASK_CWGSP       0x3FU   /**< Bitmask for CWGsP bits. */
/*@}*/

/** \name ModGsP Register Contents (0x29)
*/
/*@{*/
#define PHHAL_HW_RC523_MASK_MODGSP      0x3FU   /**< Bitmask for ModGsP bits. */
/*@}*/

/** \name TMode Register Contents (0x2A)
*/
/*@{*/
#define PHHAL_HW_RC523_BIT_TAUTO            0x80U   /**< Sets the Timer start/stop conditions to Auto mode. */
#define PHHAL_HW_RC523_BIT_TAUTORESTART     0x10U   /**< Restarts the timer automatically after counting down to 0. */
#define PHHAL_HW_RC523_MASK_TGATED          0x60U   /**< Bitmask for TGated bits. */
#define PHHAL_HW_RC523_MASK_TPRESCALER_HI   0x0FU   /**< Bitmask for TPrescalerHi bits. */
/*@}*/

/** @}
* end of phhalHw_Rc523_Reg group
*/

#ifdef __cplusplus
} /* Extern C */
#endif

#endif /* PHHALHW_RC523_REG_H */
