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
* Rc632 register definitions for Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.1 $
* $Date: Fri Apr 15 09:29:04 2011 $
*
* History:
*
*/

#ifndef PHHALHW_RC632_REG_H
#define PHHALHW_RC632_REG_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

	/** \defgroup phhalHw_Rc632_Reg Register Definitions
	* @{
	*/

	/** \name RC632 Register definitions of Page 0
	*  Following all register defintions of Page 0.
	*/
	/*@{*/
#define     PHHAL_HW_RC632_REG_PAGE_0				0x00U   
#define     PHHAL_HW_RC632_REG_COMMAND				0x01U
#define     PHHAL_HW_RC632_REG_FIFO_DATA			0x02U
#define     PHHAL_HW_RC632_REG_PRIMARY_STATUS		0x03U
#define     PHHAL_HW_RC632_REG_FIFO_LENGTH			0x04U
#define     PHHAL_HW_RC632_REG_SECONDARY_STATUS		0x05U
#define     PHHAL_HW_RC632_REG_INT_EN				0x06U
#define     PHHAL_HW_RC632_REG_INT_REQ				0x07U
	/*@}*/

	/** \name RC632 Register definitions of Page 1
	*  Following all register defintions of Page 1.
	*/
	/*@{*/
#define     PHHAL_HW_RC632_REG_PAGE_1				0x08U
#define     PHHAL_HW_RC632_REG_CONTROL				0x09U
#define     PHHAL_HW_RC632_REG_ERROR_FLAG			0x0AU
#define     PHHAL_HW_RC632_REG_COLL_POS				0x0BU
#define     PHHAL_HW_RC632_REG_TIMER_VALUE			0x0CU
#define     PHHAL_HW_RC632_REG_CRC_RES_LSB			0x0DU
#define     PHHAL_HW_RC632_REG_CRC_RES_MSB			0x0EU
#define     PHHAL_HW_RC632_REG_BIT_FRAMING			0x0FU
	/*@}*/

	/** \name RC632 Register definitions of Page 2
	*  Following all register defintions of Page 2.
	*/
	/*@{*/
#define     PHHAL_HW_RC632_REG_PAGE_2				0x10U
#define     PHHAL_HW_RC632_REG_TXCONTROL			0x11U
#define     PHHAL_HW_RC632_REG_CW_COND				0x12U
#define     PHHAL_HW_RC632_REG_MOD_COND				0x13U
#define     PHHAL_HW_RC632_REG_CODER_CONTROL		0x14U
#define     PHHAL_HW_RC632_REG_MOD_WIDTH			0x15U
#define     PHHAL_HW_RC632_REG_MOD_WIDTH_SOF		0x16U
#define     PHHAL_HW_RC632_REG_TYPEB_FRAMING		0x17U
	/*@}*/

	/** \name RC632 Register definitions of Page 3
	*  Following all register defintions of Page 3.
	*/
	/*@{*/
#define     PHHAL_HW_RC632_REG_PAGE_3				0x18U
#define     PHHAL_HW_RC632_REG_RX_CONTROL1			0x19U
#define     PHHAL_HW_RC632_REG_DECODER_CONTROL		0x1AU
#define     PHHAL_HW_RC632_REG_BIT_PHASE			0x1BU
#define     PHHAL_HW_RC632_REG_RX_THRESHOLD			0x1CU
#define     PHHAL_HW_RC632_REG_BPSK_DEM_CONTROL		0x1DU
#define     PHHAL_HW_RC632_REG_RX_CONTROL2			0x1EU
#define     PHHAL_HW_RC632_REG_CLOCKQ_CONTROL		0x1FU
	/*@}*/

	/** \name RC632 Register definitions of Page 4
	*  Following all register defintions of Page 4.
	*/
	/*@{*/
#define     PHHAL_HW_RC632_REG_PAGE4				0x20U
#define     PHHAL_HW_RC632_REG_RX_WAIT				0x21U
#define     PHHAL_HW_RC632_REG_CHANNEL_REDUND		0x22U
#define     PHHAL_HW_RC632_REG_CRC_PRESET_LSB		0x23U
#define     PHHAL_HW_RC632_REG_CRC_PRESET_MSB		0x24U
#define     PHHAL_HW_RC632_REG_TIME_SLOT_PERIOD		0x25U
#define     PHHAL_HW_RC632_REG_MF_OUT_SELECT		0x26U
#define     PHHAL_HW_RC632_REG_PRESET27				0x27U
	/*@}*/

	/** \name RC632 Register definitions of Page 5
	*  Following all register defintions of Page 5.
	*/
	/*@{*/
#define     PHHAL_HW_RC632_REG_PAGE5				0x28U
#define     PHHAL_HW_RC632_REG_FIFO_LEVEL			0x29U
#define     PHHAL_HW_RC632_REG_TIMER_CLOCK			0x2AU
#define     PHHAL_HW_RC632_REG_TIMER_CONTROL		0x2BU
#define     PHHAL_HW_RC632_REG_TIMER_RELOAD			0x2CU
#define     PHHAL_HW_RC632_REG_IRQ_PIN_CONFIG		0x2DU
#define     PHHAL_HW_RC632_REG_PRESET_2E			0x2EU
#define     PHHAL_HW_RC632_REG_PRESET_2F			0x2FU
	/*@}*/


	/** \name Bit definitions of Page 0
	*  Below there are useful bit definition of the register set of Page 0.
	*/
	/*@{*/

	/* Secondary status register        (05) */
#define     PHHAL_HW_RC632_BIT_TRUNNING			0x80U
#define     PHHAL_HW_RC632_BIT_E2READY			0x40U
#define     PHHAL_HW_RC632_BIT_CRCREADY			0x20U
#define		PHHAL_HW_RC632_BIT_RXLASTBITS		0x07U

	/* IrqEn/IrqReq registers        (06 / 07) */
#define		PHHAL_HW_RC632_BIT_LOWALERTIRQ		0x01U
#define		PHHAL_HW_RC632_BIT_HIALERTIRQ		0x02U
#define     PHHAL_HW_RC632_BIT_IDLEIRQ          0x04U
#define		PHHAL_HW_RC632_BIT_TIMERIRQ		    0x20U
#define		PHHAL_HW_RC632_BIT_TXIRQ			0x10U
#define		PHHAL_HW_RC632_BIT_RXIRQ			0x08U
#define		PHHAL_HW_RC632_BIT_ERRIRQ			0x04U

	/* Control register                    (09) */
#define     PHHAL_HW_RC632_BIT_STANDBY			0x20U	/**< Set to 1 to enter in Soft Standby mode. */
#define     PHHAL_HW_RC632_BIT_POWERDOWN		0x10U	/**< Set to 1 to enter in Soft PowerDown mode. */
#define     PHHAL_HW_RC632_BIT_CRYPTO1ON        0x08U   /**< Bit position for reader status Crypto is on. */
#define     PHHAL_HW_RC632_BIT_TSTOPNOW			0x04U	/**< Set to 1 to stop immediatly the timer. */
#define     PHHAL_HW_RC632_BIT_TSTARTNOW		0x02U	/**< Set to 1 to start immediatly the timer. */
#define     PHHAL_HW_RC632_BIT_FLUSHFIFO		0x01U	/**< Set to 1 to clear the internal FIFO buffer. */

	/* Control register / Error Flag Register (0A) */
#define     PHHAL_HW_RC632_BIT_KEY_ERR			0x40U
#define     PHHAL_HW_RC632_BIT_ACCESS_ERR		0x20U
#define     PHHAL_HW_RC632_BIT_FIFO_OVF			0x10U
#define     PHHAL_HW_RC632_BIT_CRC_ERR			0x08U
#define     PHHAL_HW_RC632_BIT_FRAMING_ERR		0x04U
#define     PHHAL_HW_RC632_BIT_PARITY_ERR		0x02U
#define     PHHAL_HW_RC632_BIT_COLL_ERR			0x01U

	/* TxControl Register                (11) */
#define     PHHAL_HW_RC632_BIT_MODULATOR_SRC_1	0x40U   /**< Select the source for the modulator input, bit1. */
#define     PHHAL_HW_RC632_BIT_MODULATOR_SRC_0  0x20U   /**< Select the source for the modulator input, bit0. */
#define     PHHAL_HW_RC632_BIT_FORCE_100ASK     0x10U   /**< Force a 100% ASK modulation. */
#define     PHHAL_HW_RC632_BIT_TX2INV			0x08U   /**< Deliver on pin TX2 an inverted 13.56MHz energy carrier. */
#define     PHHAL_HW_RC632_BIT_TX2CW            0x04U   /**< Does not modulate the Tx2 output, only constant wave. */
#define     PHHAL_HW_RC632_BIT_TX2RFEN          0x02U   /**< Switches the driver for Tx2 pin on. */
#define     PHHAL_HW_RC632_BIT_TX1RFEN          0x01U   /**< Switches the driver for Tx1 pin on. */

	/* Coder Control Register           (14) */
#define     PHHAL_HW_RC632_BIT_SENDONEPULSE     0x80U   /**< If set, this only sends one pulse for 15693 SlotMarker. */

	/* RxControl1 Register         (19) */
#define     PHHAL_HW_RC632_MASK_SUBCPULSES      0xE0U   /*!< Bitmask for Subcarrier pulses. */
#define     PHHAL_HW_RC632_BITS_SUBCPULSES_8    0x60U   /*!< Bitmask for 8 Subcarrier pulses per Bit. */
#define     PHHAL_HW_RC632_BITS_SUBCPULSES_16   0x80U   /*!< Bitmask for 16 Subcarrier pulses per Bit. */

	/* Decoder Control Register         (1A) */
#define	    PHHAL_HW_RC632_BIT_ZEROAFTERCOLL    0x20U   /*!< Zero After Collision Bit. */

	/* Control register                 (22) */
#define	    PHHAL_HW_RC632_BIT_ENABLE_PARITY    0x01U   /*!< Enable Parity Bit*/
#define	    PHHAL_HW_RC632_BIT_PARITY_ODD       0x02U   /*!< Parity odd (ISO 14443A) instead of even (ISO 14443B) */
#define	    PHHAL_HW_RC632_BIT_ENABLE_TXCRC     0x04U   /*!< Enable TxCRC */
#define	    PHHAL_HW_RC632_BIT_ENABLE_RXCRC     0x08U   /*!< Enable RxCRC */
	/*@}*/

#define PHHAL_HW_RC632_BIT_IRQ 0x80U
#define	PHHAL_HW_RC632_BIT_STATUS_IRQ 0x08U

	/** @}
	* end of phhalHw_Rc632_Reg group
	*/

#ifdef __cplusplus
} /* Extern C */
#endif

#endif /* PHHALHW_RC632_REG_H */
