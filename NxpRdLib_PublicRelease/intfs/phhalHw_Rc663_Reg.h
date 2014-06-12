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
* Rc663 register definitions for Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:27:19 2011 $
*
* History:
*  CHu: Generated 19. November 2009
*
*/

#ifndef PHHALHW_RC663_REG_H
#define PHHALHW_RC663_REG_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/** \defgroup phhalHw_Rc663_Reg Register Definitions
* \brief Register definitions.
* @{
*/

/** \brief Command Register.
*
* Used for starting / stopping commands and for sending the IC into standby mode.
*/
#define PHHAL_HW_RC663_REG_COMMAND              0x00

/** \brief Host-Control Register.
*
* Configure Host and SAM interfaces.
*/
#define PHHAL_HW_RC663_REG_HOSTCTRL             0x01

/** \name Fifo Registers
*/
/*@{*/
/** \brief FIFO-Control Register.
*
* Set FIFO size and retrieve FIFO parameters.\n
* \b Note: Also contains 1 additional Water-Level bit (MSB) and 2 additional FIFO-Length bits (also MSB).
*/
#define PHHAL_HW_RC663_REG_FIFOCONTROL          0x02

/** \brief WaterLevel Register.
*
* FIFO WaterLevel configuration.
*/
#define PHHAL_HW_RC663_REG_WATERLEVEL           0x03

/** \brief FIFO-Length Register.
*
* Retrieve the number of bytes within the FIFO.
*/
#define PHHAL_HW_RC663_REG_FIFOLENGTH           0x04

/** \brief FIFO-Data Register.
*
* Writing to this register moves a byte into the FIFO
* while incrementing the FIFO length and raising the internal WaterLevel.
*/
#define PHHAL_HW_RC663_REG_FIFODATA             0x05
/*@}*/

/** \name IRQ Registers
*/
/*@{*/
/** \brief IRQ0 Register.
*
* Read or modify the first 7 IRQ bits.
*/
#define PHHAL_HW_RC663_REG_IRQ0                 0x06

/** \brief IRQ1 Register.
*
* Read or modify the second 7 IRQ bits.
*/
#define PHHAL_HW_RC663_REG_IRQ1                 0x07

/** \brief IRQ0EN Register.
*
* Enable or disable the first IRQ bits or invert the IRQ propagation.
*/
#define PHHAL_HW_RC663_REG_IRQ0EN               0x08

/** \brief IRQ1EN Register.
*
* Enable or disable the second IRQ bits or enable/disable PushPull mode.
*/
#define PHHAL_HW_RC663_REG_IRQ1EN               0x09
/*@}*/

/** \brief Error Register.
*
* Contains bits for the occured erros.
*/
#define PHHAL_HW_RC663_REG_ERROR                0x0A

/** \brief Status Register.
*
* Contains the Crypto1 state and information about the ComState.
*/
#define PHHAL_HW_RC663_REG_STATUS               0x0B

/** \brief Rx-Bit-Control Register.
*
* Set/Get Bit-granularity and collision information.
*/
#define PHHAL_HW_RC663_REG_RXBITCTRL            0x0C

/** \brief Rx-Coll Register.
*
* Contains information about the collision position after a collision.
*/
#define PHHAL_HW_RC663_REG_RXCOLL               0x0D

/** \name Timer Registers
*/
/*@{*/
/** \brief Timer Control Register.
*
* Provides timer control and status information for all timers.
*/
#define PHHAL_HW_RC663_REG_TCONTROL             0x0E

/** \brief Timer0 Control Register.
*
* Configure the timer.
*/
#define PHHAL_HW_RC663_REG_T0CONTROL            0x0F

/** \brief Timer0 Reload(High) Register.
*
* Set the most significant byte of the Reload-Value.
*/
#define PHHAL_HW_RC663_REG_T0RELOADHI           0x10

/** \brief Timer0 Reload(Low) Register.
*
* Set the least significant byte of the Reload-Value.
*/
#define PHHAL_HW_RC663_REG_T0RELOADLO           0x11

/** \brief Timer0 Counter(High) Register.
*
* Get the most significant byte of the Counter-Value.
*/
#define PHHAL_HW_RC663_REG_T0COUNTERVALHI       0x12

/** \brief Timer0 Counter(Low) Register.
*
* Get the least significant byte of the Counter-Value.
*/
#define PHHAL_HW_RC663_REG_T0COUNTERVALLO       0x13

/** \brief Timer1 Control Register.
*
* Configure the timer.
*/
#define PHHAL_HW_RC663_REG_T1CONTROL            0x14

/** \brief Timer1 Reload(High) Register.
*
* Set the most significant byte of the Reload-Value.
*/
#define PHHAL_HW_RC663_REG_T1RELOADHI           0x15

/** \brief Timer1 Reload(Low) Register.
*
* Set the least significant byte of the Reload-Value.
*/
#define PHHAL_HW_RC663_REG_T1RELOADLO           0x16

/** \brief Timer1 Counter(High) Register.
*
* Get the most significant byte of the Counter-Value.
*/
#define PHHAL_HW_RC663_REG_T1COUNTERVALHI       0x17

/** \brief Timer1 Counter(Low) Register.
*
* Get the least significant byte of the Counter-Value.
*/
#define PHHAL_HW_RC663_REG_T1COUNTERVALLO       0x18

/** \brief Timer2 Control Register.
*
* Configure the timer.
*/
#define PHHAL_HW_RC663_REG_T2CONTROL            0x19

/** \brief Timer2 Reload(High) Register.
*
* Set the most significant byte of the Reload-Value.
*/
#define PHHAL_HW_RC663_REG_T2RELOADHI           0x1A

/** \brief Timer2 Reload(Low) Register.
*
* Set the least significant byte of the Reload-Value.
*/
#define PHHAL_HW_RC663_REG_T2RELOADLO           0x1B

/** \brief Timer2 Counter(High) Register.
*
* Get the most significant byte of the Counter-Value.
*/
#define PHHAL_HW_RC663_REG_T2COUNTERVALHI       0x1C

/** \brief Timer2 Counter(Low) Register.
*
* Get the least significant byte of the Counter-Value.
*/
#define PHHAL_HW_RC663_REG_T2COUNTERVALLO       0x1D

/** \brief Timer3 Control Register.
*
* Configure the timer.
*/
#define PHHAL_HW_RC663_REG_T3CONTROL            0x1E

/** \brief Timer3 Reload(High) Register.
*
* Set the most significant byte of the Reload-Value.
*/
#define PHHAL_HW_RC663_REG_T3RELOADHI           0x1F

/** \brief Timer3 Reload(Low) Register.
*
* Set the least significant byte of the Reload-Value.
*/
#define PHHAL_HW_RC663_REG_T3RELOADLO           0x20

/** \brief Timer3 Counter(High) Register.
*
* Get the most significant byte of the Counter-Value.
*/
#define PHHAL_HW_RC663_REG_T3COUNTERVALHI       0x21

/** \brief Timer3 Counter(Low) Register.
*
* Get the least significant byte of the Counter-Value.
*/
#define PHHAL_HW_RC663_REG_T3COUNTERVALLO       0x22

/** \brief Timer4 Control Register.
*
* Configure the timer.
*/
#define PHHAL_HW_RC663_REG_T4CONTROL            0x23

/** \brief Timer4 Reload(High) Register.
*
* Set the most significant byte of the Reload-Value.
*/
#define PHHAL_HW_RC663_REG_T4RELOADHI           0x24

/** \brief Timer4 Reload(Low) Register.
*
* Set the least significant byte of the Reload-Value.
*/
#define PHHAL_HW_RC663_REG_T4RELOADLO           0x25

/** \brief Timer4 Counter(High) Register.
*
* Get the most significant byte of the Counter-Value.
*/
#define PHHAL_HW_RC663_REG_T4COUNTERVALHI       0x26

/** \brief Timer4 Counter(Low) Register.
*
* Get the least significant byte of the Counter-Value.
*/
#define PHHAL_HW_RC663_REG_T4COUNTERVALLO       0x27
/*@}*/

/** \brief Driver Mode Register.
*
* Enable / Invert the Tx-Driver and set the Clock Mode.
*/
#define PHHAL_HW_RC663_REG_DRVMODE              0x28

/** \brief Tx Amplifier Register.
*
* Modify Amplitude and Carrier settings.
*/
#define PHHAL_HW_RC663_REG_TXAMP                0x29

/** \brief Driver Control Register.
*
* Select / Invert drivers.
*/
#define PHHAL_HW_RC663_REG_DRVCON               0x2A

/** \brief TxI Register.
*
* Contains Overshoot prevention and current control settings.
*/
#define PHHAL_HW_RC663_REG_TXI                  0x2B

/** \brief Tx-CRC Control Register.
*
* Configure CRC parameters transmission.
*/
#define PHHAL_HW_RC663_REG_TXCRCCON             0x2C

/** \brief Rx-CRC Control Register.
*
* Configure CRC parameters for reception.
*/
#define PHHAL_HW_RC663_REG_RXCRCCON             0x2D

/** \brief Tx-DataNum Register.
*
* Set TxLastBits and configure KeepBitGrid functionality.
*/
#define PHHAL_HW_RC663_REG_TXDATANUM            0x2E

/** \brief Tx-Modwidth Register.
*
* Set the modulation width.
*/
#define PHHAL_HW_RC663_REG_TXMODWIDTH           0x2F

/** \brief Symbol 0 and 1 Register.
*
* Configure Burst-lengths of both symbols.
*/
#define PHHAL_HW_RC663_REG_TXSYM10BURSTLEN      0x30

/** \brief Tx-Wait Control Register.
*
* Enable / Configure Tx Waiting-Time.
*/
#define PHHAL_HW_RC663_REG_TXWAITCTRL           0x31

/** \brief TxWaitLo Register.
*
* Contains the Least-Significant-Bits for the Tx Waiting-Time.
*/
#define PHHAL_HW_RC663_REG_TXWAITLO             0x32

/** \brief Frame control register.
*
* Contains active Start/Stop symbol and Parity settings.
*/
#define PHHAL_HW_RC663_REG_FRAMECON             0x33

/** \brief RxSOFD Register.
*
* Contains Start-of-Frame and subcarrier detection bits.
*/
#define PHHAL_HW_RC663_REG_RXSOFD               0x34

/** \brief Rx Control Register.
*
* Configure Receiver settings such as baudrate and EMD-suppression feature.
*/
#define PHHAL_HW_RC663_REG_RXCTRL               0x35

/** \brief Rx-Wait Register.
*
* Configure Receiver Deaf-Time.
*/
#define PHHAL_HW_RC663_REG_RXWAIT               0x36

/** \brief Rx-Threshold Register.
*
* Configure Receiver Threshold.
*/
#define PHHAL_HW_RC663_REG_RXTHRESHOLD          0x37

/** \brief Receiver Register.
*
* Configure Collision-Level and other features.
*/
#define PHHAL_HW_RC663_REG_RCV                  0x38

/** \brief Rx-Analog Register.
*
* Configure analog settings and parameters for Receiver circuitry.
*/
#define PHHAL_HW_RC663_REG_RXANA                0x39

/** \brief Serial Speed Register.
*
* Configure serial baudrates.
*/
#define PHHAL_HW_RC663_REG_SERIALSPEED          0x3B

/** \brief LPO_TRIMM Register.
*
* Trimm Control Input for Low Power Oscillator.
*/
#define PHHAL_HW_RC663_REG_LPO_TRIMM            0x3C

/** \brief PLL Control Register.
*
* Configure PLL settings.
*/
#define PHHAL_HW_RC663_REG_PLL_CTRL             0x3D

/** \brief PLL DivO Register.
*
* Contains PLL output.
*/
#define PHHAL_HW_RC663_REG_PLL_DIV              0x3E

/** \brief LPCD QMin Register.
*
* Configure IMax(2) and QMin values for LPCD.
*/
#define PHHAL_HW_RC663_REG_LPCD_QMIN            0x3F

/** \brief LPCD QMax Register.
*
* Configure IMax(1) and QMax values for LPCD.
*/
#define PHHAL_HW_RC663_REG_LPCD_QMAX            0x40

/** \brief LPCD IMin Register.
*
* Configure IMax(0) and IMin values for LPCD.
*/
#define PHHAL_HW_RC663_REG_LPCD_IMIN            0x41

/** \brief LPCD Result(I) Register.
*
* Contains I-Channel results of LPCD.
*/
#define PHHAL_HW_RC663_REG_LPCD_RESULT_I        0x42

/** \brief LPCD Result(Q) Register.
*
* Contains Q-Channel results of LPCD.
*/
#define PHHAL_HW_RC663_REG_LPCD_RESULT_Q        0x43

/** \brief Version Register.
*
* Contains IC Version and Subversion.
*/
#define PHHAL_HW_RC663_REG_VERSION              0x7F

/** \name Command Register Contents (0x00)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_STANDBY              0x80U   /**< Standby bit; If set, the IC transits to standby mode. */
#define PHHAL_HW_RC663_CMD_IDLE                 0x00U   /**< No action; cancels current command execution. */
#define PHHAL_HW_RC663_CMD_LPCD                 0x01U   /**< Low Power Card Detection. */
#define PHHAL_HW_RC663_CMD_LOADKEY              0x02U   /**< Reads a key from the FIFO buffer and puts it into the key buffer. */
#define PHHAL_HW_RC663_CMD_MFAUTHENT            0x03U   /**< Performs the Mifare standard authentication (in Mifare Reader/Writer mode only). */
#define PHHAL_HW_RC663_CMD_ACKREQ               0x04U   /**< Performs a Query, a Ack and a Req-Rn for EPC V2. */
#define PHHAL_HW_RC663_CMD_RECEIVE              0x05U   /**< Activates the receiver circuitry. */
#define PHHAL_HW_RC663_CMD_TRANSMIT             0x06U   /**< Transmits data from the FIFO buffer to Card. */
#define PHHAL_HW_RC663_CMD_TRANSCEIVE           0x07U   /**< Like #PHHAL_HW_RC663_CMD_TRANSMIT but automatically activates the receiver after transmission is finished. */
#define PHHAL_HW_RC663_CMD_WRITEE2              0x08U   /**< Gets one byte from FIFO buffer and writes it to the internal EEPROM. */
#define PHHAL_HW_RC663_CMD_WRITEE2PAGE          0x09U   /**< Gets up to 64 Bytes from FIFO buffer and writes it to the EEPROM. */
#define PHHAL_HW_RC663_CMD_READE2               0x0AU   /**< Reads data from EEPROM and puts it into the FIFO buffer. */
#define PHHAL_HW_RC663_CMD_LOADREG              0x0CU   /**< Reads data from EEPROM and initializes the registers. */
#define PHHAL_HW_RC663_CMD_LOADPROTOCOL         0x0DU   /**< Reads data from EEPROM and initializes the registers needed for a protocol change. */
#define PHHAL_HW_RC663_CMD_LOADKEYE2            0x0EU   /**< Copies a Mifare key from the EEPROM into the key buffer. */
#define PHHAL_HW_RC663_CMD_STOREKEYE2           0x0FU   /**< Stores a Mifare key into the EEPROM. */
#define PHHAL_HW_RC663_CMD_SOFTRESET            0x1FU   /**< Resets the IC. */
#define PHHAL_HW_RC663_MASK_COMMAND             0x1FU   /**< Mask for Command-bits. */
/*@}*/

/** \name Host-Control Register Contents (0x01)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_REGEN                0x80U
#define PHHAL_HW_RC663_BIT_BUSHOST              0x40U
#define PHHAL_HW_RC663_BIT_BUSSAM               0x20U
#define PHHAL_HW_RC663_MASK_SAMINTERFACE        0x0CU
/*@}*/

/** \name FIFO-Control Register Contents (0x02)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_FIFOSIZE             0x80U
#define PHHAL_HW_RC663_BIT_HIALERT              0x40U
#define PHHAL_HW_RC663_BIT_LOALERT              0x20U
#define PHHAL_HW_RC663_BIT_FLUSHFIFO            0x10U
#define PHHAL_HW_RC663_BIT_WATERLEVEL_HI        0x04U
#define PHHAL_HW_RC663_MASK_FIFOLENGTH_HI       0x03U
/*@}*/

/** \name IRQ0 Register(s) Contents (0x06/0x08)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_SET                  0x80U
#define PHHAL_HW_RC663_BIT_IRQINV               0x80U
#define PHHAL_HW_RC663_BIT_HIALERTIRQ           0x40U
#define PHHAL_HW_RC663_BIT_LOALERTIRQ           0x20U
#define PHHAL_HW_RC663_BIT_IDLEIRQ              0x10U
#define PHHAL_HW_RC663_BIT_TXIRQ                0x08U
#define PHHAL_HW_RC663_BIT_RXIRQ                0x04U
#define PHHAL_HW_RC663_BIT_ERRIRQ               0x02U
#define PHHAL_HW_RC663_BIT_EMDIRQ               0x01U
/*@}*/

/** \name IRQ1 Register(s) Contents (0x07/0x09)
*/
/*@{*/
/* #define PHHAL_HW_RC663_BIT_SET                  0x80U */
#define PHHAL_HW_RC663_BIT_IRQPUSHPULL          0x80U
#define PHHAL_HW_RC663_BIT_GLOBALIRQ            0x40U
#define PHHAL_HW_RC663_BIT_IRQPINEN             0x40U
#define PHHAL_HW_RC663_BIT_LPCDIRQ              0x20U
#define PHHAL_HW_RC663_BIT_TIMER4IRQ            0x10U
#define PHHAL_HW_RC663_BIT_TIMER3IRQ            0x08U
#define PHHAL_HW_RC663_BIT_TIMER2IRQ            0x04U
#define PHHAL_HW_RC663_BIT_TIMER1IRQ            0x02U
#define PHHAL_HW_RC663_BIT_TIMER0IRQ            0x01U
/*@}*/

/** \name Error Register Contents (0x0A)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_EE_ERR               0x80U
#define PHHAL_HW_RC663_BIT_FIFOWRERR            0x40U
#define PHHAL_HW_RC663_BIT_FIFOOVL              0x20U
#define PHHAL_HW_RC663_BIT_MINFRAMEERR          0x10U
#define PHHAL_HW_RC663_BIT_NODATAERR            0x08U
#define PHHAL_HW_RC663_BIT_COLLDET              0x04U
#define PHHAL_HW_RC663_BIT_PROTERR              0x02U
#define PHHAL_HW_RC663_BIT_INTEGERR             0x01U
/*@}*/

/** \name Status Register Contents (0x0B)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_CRYPTO1ON            0x20U
#define PHHAL_HW_RC663_MASK_COMMSTATE           0x07U
/*@}*/

/** \name Rx-Bit-Control Register Contents (0x0C)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_VALUESAFTERCOLL      0x80U
#define PHHAL_HW_RC663_BIT_NOCOLL               0x08U
#define PHHAL_HW_RC663_MASK_RXALIGN             0x70U
#define PHHAL_HW_RC663_MASK_RXLASTBITS          0x07U
/*@}*/

/** \name Rx-Coll Register Contents (0x0D)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_COLLPOSVALID         0x80U
#define PHHAL_HW_RC663_MASK_COLLPOS             0x7FU
/*@}*/

/** \name Timer-Control Register Contents (0x0E)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_T3RUNNING            0x80U
#define PHHAL_HW_RC663_BIT_T2RUNNING            0x40U
#define PHHAL_HW_RC663_BIT_T1RUNNING            0x20U
#define PHHAL_HW_RC663_BIT_T0RUNNING            0x10U
#define PHHAL_HW_RC663_BIT_T3STARTSTOPNOW       0x08U
#define PHHAL_HW_RC663_BIT_T2STARTSTOPNOW       0x04U
#define PHHAL_HW_RC663_BIT_T1STARTSTOPNOW       0x02U
#define PHHAL_HW_RC663_BIT_T0STARTSTOPNOW       0x01U
/*@}*/

/** \name T[0-3]-Control Register Contents (0x0F/0x14/0x19/0x1E)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_TSTOP_RX             0x80U   /**< Stop timer on receive interrupt. */
#define PHHAL_HW_RC663_BIT_TAUTORESTARTED       0x08U   /**< Auto-restart timer after underflow. */
#define PHHAL_HW_RC663_BIT_TSTART_TX            0x10U   /**< Start timer on transmit interrupt. */
#define PHHAL_HW_RC663_BIT_TSTART_LFO           0x20U   /**< Use this timer for LFO trimming. */
#define PHHAL_HW_RC663_BIT_TSTART_LFO_UV        0x30U   /**< Use this timer for LFO trimming (generate UV at a trimming event). */
#define PHHAL_HW_RC663_MASK_TSTART              0x30U   /**< Mask for TSTART bits. */
#define PHHAL_HW_RC663_VALUE_TCLK_1356_MHZ      0x00U   /**< Use 13.56MHz as input clock. */
#define PHHAL_HW_RC663_VALUE_TCLK_212_KHZ       0x01U   /**< Use 212KHz as input clock. */
#define PHHAL_HW_RC663_VALUE_TCLK_T0            0x02U   /**< Use timer0 as input clock. */
#define PHHAL_HW_RC663_VALUE_TCLK_T1            0x03U   /**< Use timer1 as input clock. */
/*@}*/

/** \name T4-Control Register Contents (0x23)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_T4RUNNING            0x80U
#define PHHAL_HW_RC663_BIT_T4STARTSTOPNOW       0x40U
#define PHHAL_HW_RC663_BIT_T4AUTOTRIMM          0x20U
#define PHHAL_HW_RC663_BIT_T4AUTOLPCD           0x10U
#define PHHAL_HW_RC663_BIT_T4AUTORESTARTED      0x08U
#define PHHAL_HW_RC663_BIT_T4AUTOWAKEUP         0x04U
/*#define PHHAL_HW_RC663_MASK_TSTART              0x30U*/
#define PHHAL_HW_RC663_VALUE_TCLK_LFO_64_KHZ    0x00U
#define PHHAL_HW_RC663_VALUE_TCLK_LFO_8_KHZ     0x01U
#define PHHAL_HW_RC663_VALUE_TCLK_LFO_4_KHZ     0x02U
#define PHHAL_HW_RC663_VALUE_TCLK_LFO_2_KHZ     0x03U
/*@}*/

/** \name Driver Mode Register Contents (0x28)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_TX2INV               0x80U
#define PHHAL_HW_RC663_BIT_TX1INV               0x40U
#define PHHAL_HW_RC663_BIT_TXEN                 0x08U
#define PHHAL_HW_RC663_BIT_RFON                 0x04U
#define PHHAL_HW_RC663_BIT_TPUSHON              0x02U
#define PHHAL_HW_RC663_BIT_TPULLON              0x01U
/*@}*/

/** \name Tx Amplifier Register Contents (0x29)
*/
/*@{*/
#define PHHAL_HW_RC663_MASK_CW_AMPLITUDE        0xC0U
#define PHHAL_HW_RC663_MASK_RESIDUAL_CARRIER    0x1FU
/*@}*/

/** \name Driver Control Register Contents (0x2A)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_CWMAX                0x10U
#define PHHAL_HW_RC663_BIT_DISOVSHTPREV         0x08U
#define PHHAL_HW_RC663_BIT_DRIVERINV            0x04U
#define PHHAL_HW_RC663_VALUE_DRIVERSEL_LOW      0x00U
#define PHHAL_HW_RC663_VALUE_DRIVERSEL_TXENV    0x01U
#define PHHAL_HW_RC663_VALUE_DRIVERSEL_SIGIN    0x02U
/*@}*/

/** \name Tx-/Rx-CRC Control Register Contents (0x2C/0x2D)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_RXFORCECRCWRITE      0x80U
#define PHHAL_HW_RC663_BIT_CRCINVERT            0x02U
#define PHHAL_HW_RC663_BIT_CRCEN                0x01U
#define PHHAL_HW_RC663_MASK_CRCPRESETVAL        0x70U
#define PHHAL_HW_RC663_MASK_CRCTYPE             0x0CU
/*@}*/

/** \name Tx-DataNum Register Contents (0x2E)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_KEEPBITGRID          0x10U
#define PHHAL_HW_RC663_BIT_DATAEN               0x08U
#define PHHAL_HW_RC663_MASK_TXLASTBITS          0x07U
/*@}*/

/** \name Tx-Wait Control Register Contents (0x31)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_TXWAIT_START_RX      0x80U
#define PHHAL_HW_RC663_BIT_TXWAIT_DBFREQ        0x40U
#define PHHAL_HW_RC663_MASK_TXWAITHI            0x38U
#define PHHAL_HW_RC663_MASK_TXSTOPBITLEN        0x07U
/*@}*/

/** \name Frame Control Register Contents (0x33)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_TXPARITYEN           0x80U
#define PHHAL_HW_RC663_BIT_RXPARITYEN           0x40U
#define PHHAL_HW_RC663_VALUE_STOP_SYM3          0x0CU
#define PHHAL_HW_RC663_VALUE_STOP_SYM2          0x08U
#define PHHAL_HW_RC663_VALUE_STOP_SYM1          0x04U
#define PHHAL_HW_RC663_VALUE_START_SYM2         0x03U
#define PHHAL_HW_RC663_VALUE_START_SYM1         0x02U
#define PHHAL_HW_RC663_VALUE_START_SYM0         0x01U
#define PHHAL_HW_RC663_MASK_STARTSYM            0x03U
#define PHHAL_HW_RC663_MASK_STOPSYM             0x0CU
/*@}*/

/** \name Rx Control Register Contents (0x35)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_RXALLOWBITS          0x80U
#define PHHAL_HW_RC663_BIT_RXMULTIPLE           0x40U
#define PHHAL_HW_RC663_BIT_RXEOFTYPE            0x20U
#define PHHAL_HW_RC663_BIT_EGT_CHECK            0x10U
#define PHHAL_HW_RC663_BIT_EMD_SUPPRESSION      0x08U
#define PHHAL_HW_RC663_MASK_RXBAUDRATE          0x07U
/*@}*/

/** \name Rx-Wait Register Contents (0x36)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_RXWAITDBFREQ         0x80U
#define PHHAL_HW_RC663_MASK_RXWAIT              0x7FU
/*@}*/

/** \name Rx-Threshold Register Contents (0x37)
*/
/*@{*/
#define PHHAL_HW_RC663_MASK_MINLEVEL            0xF0U
#define PHHAL_HW_RC663_MASK_MINLEVELP           0x0FU
/*@}*/

/** \name Rx-Receiver Register Contents (0x38)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_RX_SINGLE            0x80U
#define PHHAL_HW_RC663_BIT_RX_SHORT_MIX2ADC     0x40U
#define PHHAL_HW_RC663_BIT_USE_SMALL_EVAL       0x04U
#define PHHAL_HW_RC663_MASK_RX_SIGPRO_IN_SEL    0x30U
#define PHHAL_HW_RC663_MASK_COLLLEVEL           0x03U
/*@}*/

/** \name Rx-Analog Register Contents (0x39)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_RX_OC_ENABLE         0x20U
#define PHHAL_HW_RC663_BIT_RX_HP_LOWF           0x10U
#define PHHAL_HW_RC663_MASK_VMID_R_SEL          0xC0U
#define PHHAL_HW_RC663_MASK_RCV_HPCF            0x0CU
#define PHHAL_HW_RC663_MASK_RCV_GAIN            0x03U
/*@}*/

/** \name Serial-Speed Register Contents (0x3B)
*/
/*@{*/
#define PHHAL_HW_RC663_MASK_BR_T0               0xE0U
#define PHHAL_HW_RC663_MASK_BR_T1               0x1FU
/*@}*/


/** \name LPCD Result(Q) Register Contents (0x43)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_LPCDIRQ_CLR          0x40U
/*@}*/

/** \name Tx-BitMod Register Contents (0x48)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_TXMSBFIRST           0x80U
#define PHHAL_HW_RC663_BIT_TXPARITYTYPE         0x20U
#define PHHAL_HW_RC663_BIT_TXSTOPBITTYPE        0x08U
#define PHHAL_HW_RC663_BIT_TXSTARTBITTYPE       0x02U
#define PHHAL_HW_RC663_BIT_TXSTARTBITEN         0x01U
/*@}*/

/** \name Rx-BitMod Register Contents (0x58)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_RXSTOPONINVPAR       0x20U
#define PHHAL_HW_RC663_BIT_RXSTOPONLEN          0x10U
#define PHHAL_HW_RC663_BIT_RXMSBFIRST           0x08U
#define PHHAL_HW_RC663_BIT_RXSTOPBITEN          0x04U
#define PHHAL_HW_RC663_BIT_RXPARITYTYPE         0x02U
/*@}*/

/** \name Rx-Mod Register Contents (0x5D)
*/
/*@{*/
#define PHHAL_HW_RC663_BIT_PREFILTER            0x20U
#define PHHAL_HW_RC663_BIT_RECTFILTER           0x10U
#define PHHAL_HW_RC663_BIT_SYNCHIGH             0x08U
#define PHHAL_HW_RC663_BIT_CORRINV              0x04U
#define PHHAL_HW_RC663_BIT_FSK                  0x02U
#define PHHAL_HW_RC663_BIT_BPSK                 0x01U
/*@}*/

/** @}
* end of phhalHw_Rc663_Reg group
*/

#ifdef __cplusplus
} /* Extern C */
#endif

#endif /* PHHALHW_RC663_REG_H */
