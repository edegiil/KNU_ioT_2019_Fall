/**
 * @file PAL/MEGA_RF/ATMEGA128RFA1/Boards/RCB_6_3_PLAIN/pal_config.h
 *
 * @brief PAL configuration for for RCB_6_3_PLAIN with ATmega128RFA1
 *
 * This header file contains configuration parameters for
 * RCB_6_3_PLAIN with ATmega128RFA1.
 *
 * $Id: pal_config.h,v 1.2 2010-08-01 09:11:50 slb Exp $
 *
 * @author    Atmel Corporation: http://www.atmel.com
 * @author    Support email: avr@atmel.com
 */
/*
 * Copyright (c) 2009, Atmel Corporation All rights reserved.
 *
 * Licensed under Atmel's Limited License Agreement --> EULA.txt
 */

/**
 * @defgroup grpPal_ATMEGA128RFA1_RCB_6_3_PLAIN \
 *           (Plain) Radio Controller board RCB V6.3 with ATmega128RFA1
 *
 * @ingroup grpPlatforms
 *
 * @section secIntroduction Introduction
 *
 * This section describes the
 * Board Configuration for
 * RCB V6.3 with ATmega128RFA1.
 *
 * The board RCB V6.3 with ATmega128RFA1 provides an
 * IEEE 802.15.4 single chip solution for the 2.4 GHz band.
 *
 * For more information about this board see the
 * <a href="../../../MAC_User_Guide/AVR2025_User_Guide.pdf">AVR2025 MAC User Guide</a>.
 *
 * For more information about the complete API for all software layers
 * including PAL see the
 * <a href="../../MAC/html/index.html">AVR2025: IEEE 802.15.4-2006 MAC Reference Manual</a>.
 *
 * @section secTransceiverMCUInterface Transceiver-MCU interface
 *
 * Since the ATmega128RFA1 is a single chip including both MCU and transceiver,
 * there is no external interface between Transceiver and MCU such as SPI or GPIOs.
 * <BR>
 * All transceiver registers are memory mapped.
 *
 *
 * @section secFCPU Default clock speed (F_CPU)
 *
 * The default clock speed is defined by @ref F_CPU and is currently 16MHz.
 * The CPU clock source is selected in mcu_clock_init() in file pal_mcu_generic.c.
 *
 *
 * @section secIRQGeneration IRQ generation
 *
 * The ATmega128RFA1 provides 10 (see @ref NO_OF_TRX_IRQS) transceiver specific interrupts:
 *
 * - <B>Transceiver PLL lock interrupt:</B>
 * <BR>
 * This interrupt is used in the ISR for the transceiver  PLL lock interrupt
 * (@ref TRX24_PLL_LOCK_vect) in the corresponding file pal_irq.c.
 *
 * - <B>Transceiver PLL unlock interrupt:</B>
 * <BR>
 * This interrupt is used in the ISR for the transceiver  PLL unlock interrupt
 * (@ref TRX24_PLL_UNLOCK_vect) in the corresponding file pal_irq.c.
 *
 * - <B>Transceiver Receive Start interrupt:</B>
 * <BR>
 * By the time the SFD is detected, the hardware timestamps the
 * current frame in the SCTSR register.
 * This interrupt is used in the ISR for the transceiver receive start interrupt
 * (@ref TRX24_RX_START_vect) in the corresponding file pal_irq.c.
 *
 * - <B>Transceiver Receive End interrupt:</B>
 * <BR>
 * This interrupt is used in the ISR for the transceiver receive end interrupt
 * (@ref TRX24_RX_END_vect) in the corresponding file pal_irq.c.
 *
 * - <B>Transceiver CCA/ED Meassurement finished interrupt:</B>
 * <BR>
 * This interrupt is used in the ISR for the transceiver CCA/ED measurement
 * finished interrupt (@ref TRX24_CCA_ED_DONE_vect) in the corresponding file
 * pal_irq.c.
 *
 * - <B>Transceiver Frame Address Match interrupt:</B>
 * <BR>
 * This interrupt is used in the ISR for the transceiver frame address match interrupt
 * (@ref TRX24_XAH_AMI_vect) in the corresponding file pal_irq.c.
 *
 * - <B>Transceiver Transmit End interrupt:</B>
 * <BR>
 * This interrupt is used in the ISR for the transceiver transmit end interrupt
 * (@ref TRX24_TX_END_vect) in the corresponding file pal_irq.c.
 *
 * - <B>Transceiver Wakeup Finished interrupt:</B>
 * <BR>
 * This interrupt is used in the ISR for the transceiver awake interrupt
 * (@ref TRX24_AWAKE_vect) in the corresponding file pal_irq.c.
 *
 * - <B>AES Encryption Ready interrupt:</B>
 * <BR>
 * This interrupt is used in the ISR for the transceiver AES encryption ready interrupt
 * (@ref AES_READY_vect) in the corresponding file pal_irq.c.
 *
 * - <B>Batterie Monitor Alert interrupt:</B>
 * <BR>
 * This interrupt is used in the ISR for the transceiver battery low interruptt interrupt
 * (@ref BAT_LOW_vect) in the corresponding file pal_irq.c.
 *
 * @section secTimestamping Timestamping
 *
 * The function for reading the current timestamp (pal_trx_read_timestamp())
 * is located in the corresponding file pal_board.c.
 * <BR>
 * This function needs to be called explicitly at the instant when the current
 * timestamp shall be retrieved. For example in the AVR2025 MAC for ATmega128RFA1
 * this is done whenever a Transceiver Receive Start interrupt occurs.
 * For more implementation details see function trx_irq_timestamp_handler_cb()
 * in file TAL/ATMEGARF_TAL_1/Src/tal_irq_handler.c.
 *
 *
 * @section secLEDs LEDs
 *
 * This board provides 3 LEDs that are connected to pins 2-4 of port E.
 * See @ref LED_PORT and other corresponding defines.
 *
 *
 * @section secButtons Buttons
 *
 * This board provides 1 button that is connected to pin 5 of port E.
 * See @ref BUTTON_PORT and other corresponding defines.
 *
 *
 * @section secSIO SIO (Serial I/O)
 *
 * This board provides two UART channels - UART_0 and UART_1,
 * but usually SIO is not used with plain RCBs.
 *
 *
 * @section secEEPROM External EEPROM
 *
 * This board provides an external EEPROM,
 * i.e. the IEEE address of the plaform is already stored in the
 * external EEPROM based on AT25010.
 * <BR>
 * Once this switch is set (and thus the external EEPROM is enabled),
 * each call of function pal_ps_get() with parameter ps_type set to
 * @ref EXTERN_EEPROM (see pal.c) results in a call of
 * function extern_eeprom_get() (see pal_board.c).
 * <BR>
 * Note: In case the internal EEPROM from the MCU shall be used,
 * function  pal_ps_get() (see pal.c) nees to be called with
 * parameter ps_type set to @ref INTERN_EEPROM.
 * <BR>
 * Make sure that an appropiate IEEE address is stored in the internal EEPROM.
 *
 *
 * @section secFuseSettings Fuse settings
 *
 * The following fuse settings are recommended:
 * - LF: 0xC2
 * - HF: 0x91
 * - EF: 0xFE
 *
 * Make sure that the fuse CKDIV8 is NOT set.
 *
 */

/* Prevent double inclusion */
#ifndef PAL_CONFIG_H
#define PAL_CONFIG_H

#include "../../../../../../ubiconfig.h"

/* === Includes =============================================================*/

#include "../pal_boardtypes.h"

#if (BOARD_TYPE == RCB_6_3_PLAIN)

/**
 * \addtogroup grpPal_ATMEGA128RFA1_RCB_6_3_PLAIN
 * @{
 */

/*
 * This header file is required since a function with
 * return type retval_t is declared
 */
#include "../../../../../Include/return_val.h"

/* === Types ================================================================*/

/** Enumerations used to idenfify LEDs */
typedef enum led_id_tag
{
    LED_0,
    LED_1,
    LED_2
} led_id_t;

/** Number of LEDs provided by this board. */
#define NO_OF_LEDS                      (3)


/** Enumerations used to idenfify buttons */
typedef enum button_id_tag
{
    BUTTON_0
} button_id_t;

/** Number of buttons provided by this board. */
#define NO_OF_BUTTONS                   (1)

/* === Externals ============================================================*/


/* === Macros ===============================================================*/

/**
 * The default CPU clock
 *
 * The board must be configured for 16 MHz clock, which can be fused
 * for either the 16 MHz internal RC oscillator, or for the 16 MHz
 * crystal oscillator that is required for the transceiver operation.
 */
#define F_CPU                           (16000000UL)


/**
 * Wait for 65 ns.
 * time t7: SLP_TR time (see data sheet or SWPM).
 * In case the system clock is slower than 32 MHz we do not need
 * to have this value filled.
 */
#define PAL_WAIT_65_NS()                // empty


/*
 * PORT where LEDs are connected
 */
#define LED_PORT                        (PORTE) /**< Port for LEDs */
#define LED_PORT_DIR                    (DDRE)  /**< Port directions for LEDs */

/*
 * PINs where LEDs are connected
 */
#define LED_PIN_0                       (PE2)   /**< LED 0 pin */
#define LED_PIN_1                       (PE3)   /**< LED 1 pin */
#define LED_PIN_2                       (PE4)   /**< LED 2 pin */

/*
 * PORT where button is connected
 */
#define BUTTON_PORT                     (PORTE) /**< Port for buttons */
#define BUTTON_PORT_DIR                 (DDRE)  /**< Port directions for buttons */
#define BUTTON_INPUT_PINS               (PINE)  /**< Input pins for buttons */

/*
 * PINs where buttons are connected
 */
#define BUTTON_PIN_0                    (PE5)   /**< Button 0 pin */

/*
 * UART0 and UART1 non-generic (board specific) initialization part.
 */
/** UART0 non-generic (board specific) initialization part not used. */
#define UART_0_INIT_NON_GENERIC()
/** UART1 non-generic (board specific) initialization part not used. */
#define UART_1_INIT_NON_GENERIC()


/*
 * This board has an external eeprom that stores the IEEE address
 * and other information.
 */
#ifndef EXTERN_EEPROM_AVAILABLE
#define EXTERN_EEPROM_AVAILABLE            (1)
#endif

/**
 * IEEE address of board in external EEPROM
 */
#define EE_IEEE_ADDR                    (0)

/**
 * Storage location for crystal trim value in external EEPROM
 */
#define EE_XTAL_TRIM_ADDR               (21)


#if (EXTERN_EEPROM_AVAILABLE == 1) || defined(DOXYGEN)
/** Port where the external EEPROM's chip select is connected to */
#define EXT_EE_CS_PORT                  (PORTG)
/** Data direction register for the external EEPROM's chip select */
#define EXT_EE_CS_DDR                   (DDRG)

/** Pin where the external EEPROM's chip select is connected to */
#define EXT_EE_CS_PIN                   (0x20) /* PG5 */
#endif  /* #if (EXTERN_EEPROM_AVAILABLE == 1) || defined(DOXYGEN) */


/**
 * Alert initialization
 */
#define ALERT_INIT()                    do {    \
        LED_PORT = 0;                           \
        LED_PORT_DIR = 0xFF;                    \
} while (0)

/**
 * Alert indication
 * One loop cycle below is about 6 clock cycles (or more, depending
 * on optimization settings), so it takes 2...3 loop iterations per
 * microsecond.  60000 cycles thus results in 20...30 ms of delay,
 * so the LEDs should be seen as flickering.
 */
#define ALERT_INDICATE()                do {    \
        LED_PORT ^= 0xFF;                       \
} while (0)


/* === Prototypes ===========================================================*/
#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/** @} */

/* MCU pins used for debugging  */
#ifndef DOXYGEN
#define TST_PIN_0_HIGH()
#define TST_PIN_0_LOW()
#define TST_PIN_1_HIGH()
#define TST_PIN_1_LOW()
#define TST_PIN_2_HIGH()
#define TST_PIN_2_LOW()
#define TST_PIN_3_HIGH()
#define TST_PIN_3_LOW()
#define TST_PIN_4_HIGH()
#define TST_PIN_4_LOW()
#define TST_PIN_5_HIGH()
#define TST_PIN_5_LOW()
#define TST_PIN_6_HIGH()
#define TST_PIN_6_LOW()
#define TST_PIN_7_HIGH()
#define TST_PIN_7_LOW()
#define TST_PIN_8_HIGH()
#define TST_PIN_8_LOW()
#endif  /* #ifndef (DOXYGEN) */

#endif /* RCB_6_3_PLAIN */

#endif  /* PAL_CONFIG_H */
/* EOF */
