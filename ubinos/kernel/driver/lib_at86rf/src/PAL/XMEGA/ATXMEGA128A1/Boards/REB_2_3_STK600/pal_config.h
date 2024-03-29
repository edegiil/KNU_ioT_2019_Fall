/**
 * @file pal_config.h
 *
 * @brief PAL configuration for ATxmega128A1
 *
 * This header file contains configuration parameters for ATxmega128A1.
 *
 * $Id: pal_config.h,v 1.2 2010-08-01 10:00:27 slb Exp $
 *
 * @author    Atmel Corporation: http://www.atmel.com
 * @author    Support email: avr@atmel.com
 */
/*
 * Copyright (c) 2009, Atmel Corporation All rights reserved.
 *
 * Licensed under Atmel's Limited License Agreement --> EULA.txt
 */

/* Prevent double inclusion */
#ifndef PAL_CONFIG_H
#define PAL_CONFIG_H

#include "../../../../../../ubiconfig.h"

/* === Includes =============================================================*/

#include "../pal_boardtypes.h"

#if (BOARD_TYPE == REB_2_3_STK600)

/*
 * This header file is required since a function with
 * return type retval_t is declared
 */
#include "../../../../../Include/return_val.h"

/* === Types ================================================================*/

/* Enumerations used to idenfify LEDs */
typedef enum led_id_tag
{
    LED_0,
    LED_1,
    LED_2,
    LED_3,
    LED_4,
    LED_5,
    LED_6,
    LED_7
} led_id_t;

#define NO_OF_LEDS                      (8)


/* Enumerations used to idenfify buttons */
typedef enum button_id_tag
{
    BUTTON_0,
    BUTTON_1,
    BUTTON_2,
    BUTTON_3,
    BUTTON_4,
    BUTTON_5,
    BUTTON_6,
    BUTTON_7
} button_id_t;

#define NO_OF_BUTTONS                   (8)

/* === Externals ============================================================*/


/* === Macros ===============================================================*/

/** The default CPU clock */
#define F_CPU                   (16000000UL)

/*
 * IRQ macros for ATxmega128A1
 */

/*
 * AT86RF230:
 *
 * TRX_MAIN_IRQ_HDLR_IDX        TRX interrupt mapped to MCU input capture pin (PORTC Pin1)
 * TRX_TSTAMP_IRQ_HDLR_IDX      Not used
 */

/* Number of used TRX IRQs in this implementation */
#define NO_OF_TRX_IRQS                  (1)

/* Mapping of TRX interrupts to ISR vectors */
#define TRX_MAIN_ISR_VECTOR             (PORTC_INT0_vect)

/** Enables the transceiver interrupts. */
#define ENABLE_TRX_IRQ(trx_irq_num)     do {                \
    if (trx_irq_num == TRX_MAIN_IRQ_HDLR_IDX)               \
    {                                                       \
        /* Enable PORTC interrupt 0 with high priority */   \
        PORTC.INTCTRL |= PORT_INT0LVL_gm;                   \
    }                                                       \
} while (0)

/** Disables the transceiver interrupts. */
#define DISABLE_TRX_IRQ(trx_irq_num)    do {                \
    if (trx_irq_num == TRX_MAIN_IRQ_HDLR_IDX)               \
    {                                                       \
        /* Disable PORTC interrupt 0 with high priority */  \
        PORTC.INTCTRL &= ~PORT_INT0LVL_gm;                  \
    }                                                       \
} while (0)

/** Clears the transceiver interrupts. */
#define CLEAR_TRX_IRQ(trx_irq_num)     do {                 \
    if (trx_irq_num == TRX_MAIN_IRQ_HDLR_IDX)               \
    {                                                       \
        PORTC.INTFLAGS = PORT_INT0IF_bm;                    \
    }                                                       \
} while (0)

/** Enables the global interrupts. */
#define ENABLE_GLOBAL_IRQ()             sei()

/** Disables the global interrupts. */
#define DISABLE_GLOBAL_IRQ()            cli()

/*
 * This macro saves the global interrupt status
 */
#define ENTER_CRITICAL_REGION()         {uint8_t sreg = SREG; cli()

/*
 *  This macro restores the global interrupt status
 */
#define LEAVE_CRITICAL_REGION()         SREG = sreg;}

/*
 * This macro saves the trx interrupt status and disables the trx interrupt.
 */
#define ENTER_TRX_REGION()      { uint8_t irq_mask = PORTC.INTCTRL; PORTC.INTCTRL &= ~PORT_INT0LVL_gm

/*
 *  This macro restores the transceiver interrupt status
 */
#define LEAVE_TRX_REGION()      PORTC.INTCTRL = irq_mask; }


/*
 * GPIO macros for ATxmega128A1
 */

/*
 * This board uses an SPI-attached transceiver.
 */
#define PAL_USE_SPI_TRX                 (1)

/* Actual Ports */
/*
 * The data direction register for the transceiver
 */
#define TRX_PORT1_DDR                   (PORTC.DIR)

/*
 * The transceiver port
 */
#define TRX_PORT1                       (PORTC)

/*
 * RESET pin of transceiver
 */
#define TRX_RST                         (0)

/*
 * Sleep Transceiver pin
 */
#define SLP_TR                          (3)

/*
 * Slave select pin
 */
#define SEL                             (4)

/*
 * SPI Bus Master Output/Slave Input pin
 */
#define MOSI                            (5)

/*
 * SPI Bus Master Input/Slave Output pin
 */
#define MISO                            (6)

/*
 * SPI serial clock pin
 */
#define SCK                             (7)

/*
 * Set TRX GPIO pins.
 */
#define RST_HIGH()                      (TRX_PORT1.OUTSET = _BV(TRX_RST))
#define RST_LOW()                       (TRX_PORT1.OUTCLR = _BV(TRX_RST))
#define SLP_TR_HIGH()                   (TRX_PORT1.OUTSET = _BV(SLP_TR))
#define SLP_TR_LOW()                    (TRX_PORT1.OUTCLR = _BV(SLP_TR))

/*
 * PORT where LEDs are connected
 */
#define LED_PORT                        (PORTE)

/*
 * PINs where LEDs are connected
 */
#define LED_PIN_0                       (0)
#define LED_PIN_1                       (1)
#define LED_PIN_2                       (2)
#define LED_PIN_3                       (3)
#define LED_PIN_4                       (4)
#define LED_PIN_5                       (5)
#define LED_PIN_6                       (6)
#define LED_PIN_7                       (7)

/*
 * PORT where button is connected
 */
#define BUTTON_PORT                     (PORTF)

/*
 * PINs where buttons are connected
 */
#define BUTTON_PIN_0                    (0)
#define BUTTON_PIN_1                    (1)
#define BUTTON_PIN_2                    (2)
#define BUTTON_PIN_3                    (3)
#define BUTTON_PIN_4                    (4)
#define BUTTON_PIN_5                    (5)
#define BUTTON_PIN_6                    (6)
#define BUTTON_PIN_7                    (7)

/*
 * Value of an external PA gain.
 * If no external PA is available, the value is 0.
 */
#define EXTERN_PA_GAIN                  (0)

/*
 * Timer macros for ATxmega128A1
 */

/*
 * These macros are placeholders for delay functions for high speed processors.
 *
 * The following delay are not reasonbly implemented via delay functions,
 * but rather via a certain number of NOP operations.
 * The actual number of NOPs for each delay is fully MCU and frequency
 * dependent, so it needs to be updated for each board configuration.
 *
 * ATxmega128A1 @ 16MHz
 */
/*
 * Wait for 65 ns.
 * time t7: SLP_TR time (see data sheet or SWPM).
 * In case the system clock is slower than 32 MHz we do not need
 * to have this value filled.
 */
#define PAL_WAIT_65_NS()                // empty

/* Wait for 500 ns. */
#define PAL_WAIT_500_NS()               {nop(); nop(); nop(); nop(); \
                                         nop(); nop(); nop(); nop();}
/* Wait for 1 us. */
#define PAL_WAIT_1_US()                 {nop(); nop(); nop(); nop(); \
                                         nop(); nop(); nop(); nop(); \
                                         nop(); nop(); nop(); nop(); \
                                         nop(); nop(); nop(); nop();}

/*
 * The smallest timeout in microseconds
 */
#define MIN_TIMEOUT                     (0x80)

/*
 * The largest timeout in microseconds
 */
#define MAX_TIMEOUT                     (0x7FFFFFFF)

/**
 * Minimum time in microseconds, accepted as a delay request
 */
#define MIN_DELAY_VAL                   (5)

/*
 * Timer clock source while radio is awake.
 *
 * T1 & T0:
 * clk source is event channel 0 triggered by system clock (16MHz) with prescaler 16
 * TRX's clock (CLKM) is never used with Xmega, keep macro empty.
 */
#define TIMER_SRC_DURING_TRX_AWAKE()

/*
 * Timer clock source while radio is sleeping.
 *
 * T1 & T0:
 * clk source is event channel 0 triggered by system clock (16MHz) with prescaler 16
 */
#define TIMER_SRC_DURING_TRX_SLEEP() {TCC0_CTRLA = TC0_CLKSEL3_bm; TCC1_CTRLA = TC1_CLKSEL3_bm;}

/*
 * Maximum numbers of software timers running at a time
 */
#define MAX_NO_OF_TIMERS                (25)
#if (MAX_NO_OF_TIMERS > 255)
#error "MAX_NO_OF_TIMERS must not be larger than 255"
#endif

/*
 * Hardware register that holds Rx timestamp
 */
#define TIME_STAMP_REGISTER             (TCC1_CCA)


/*
 * TRX Access macros for ATxmega128A1
 */

/*
 * Bit mask for slave select
 */
#define SS_BIT_MASK                     (1 << SEL)

/*
 * Slave select made low
 */
#define SS_LOW()                        (TRX_PORT1.OUTCLR = SS_BIT_MASK)

/*
 * Slave select made high
 */
#define SS_HIGH()                       (TRX_PORT1.OUTSET = SS_BIT_MASK)

/*
 * Mask for SPIF bit in status register
 */
#define SPIF_MASK                       (SPI_IF_bm)

/*
 * SPI Data Register
 */
#define SPI_DATA_REG                    (SPIC.DATA)

/*
 * Wait for SPI interrupt flag
 */
#define SPI_WAIT()                      do {                        \
    while ((SPIC.STATUS & SPIF_MASK) == 0) { ; }                    \
} while (0)

/*
 * Dummy value written in SPDR to retrieve data form it
 */
#define SPI_DUMMY_VALUE                 (0x00)

/*
 * TRX Initialization
 */
#define TRX_INIT()                      do {                        \
    /* Enable the SPI and make the microcontroller as SPI master */ \
    SPIC.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm | (0 << SPI_MODE0_bp);\
    /* Set SEL pin to high */                                       \
    TRX_PORT1.OUTSET = _BV(SEL);                                    \
} while (0)


/*
 * This board does NOT have an external eeprom available.
 */
#ifndef EXTERN_EEPROM_AVAILABLE
#define EXTERN_EEPROM_AVAILABLE            (0)
#endif

/*
 * Alert initialization
 */
#define ALERT_INIT()                    do {    \
        LED_PORT.OUT    = 0;                    \
        LED_PORT.DIRSET = 0xFF;                 \
} while (0)

/*
 * Alert indication
 */
#define ALERT_INDICATE()                (LED_PORT.OUTTGL = 0xFF)


/*
 * Macros for random seed generation by means of the ADC
 */
#define COMMON_MODE_CYCLES              (16)
#define SAMPLE_COUNT                    (16)
#define LSB_MASK_INT_16                 (0x0001)

/*
 * ADC used for random seed generation
 */
#define ADC_FOR_RANDOM_SEED             (ADCA)

/*
 * Channel used from the ADC for random seed generation
 * ! Do not put the define in "()"
 */
#define ADC_CHANNEL                     CH0

/*
 * Positive and negative input multiplexer selection.
 *
 * The pin were selected based on test with this board, but might need to be
 * retested and updated for a new hardware platform.
 */
#define ADC_POS_MUX_SEL                 (2)
#define ADC_NEG_MUX_SEL                 (2)

/*
 * This macro returns the channel conversion complete flag.
 */
#define ADC_CH_CONVERSION_COMPLETEs(_adc_ch)    (((_adc_ch)->INTFLAGS & ADC_CH_CHIF_bm) != 0x00)

/* === Prototypes ===========================================================*/
#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* REB_2_3_STK600 */

#endif  /* PAL_CONFIG_H */
/* EOF */
