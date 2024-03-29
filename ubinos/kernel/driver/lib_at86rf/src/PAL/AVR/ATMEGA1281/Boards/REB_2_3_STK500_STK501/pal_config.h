/**
 * @file pal_config.h
 *
 * @brief PAL configuration for ATmega1281
 *
 * This header file contains configuration parameters for ATmega1281.
 *
 * $Id: pal_config.h,v 1.2 2010-08-01 11:59:10 slb Exp $
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

#if (BOARD_TYPE == REB_2_3_STK500_STK501)

/*
 * This header file is required since a function with
 * return type retval_t is declared
 */
#include "../../../../../Include/return_val.h"

/* === Types ================================================================*/

typedef enum port_type_tag
{
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E,
    PORT_F,
    PORT_G
} port_type_t;

typedef enum port_pin_direction_type_tag
{
    DDR_A,
    DDR_B,
    DDR_C,
    DDR_D,
    DDR_E,
    DDR_F,
    DDR_G
} port_pin_direction_type_t;

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
    BUTTON_3
} button_id_t;

#define NO_OF_BUTTONS                   (4)

/* === Externals ============================================================*/


/* === Macros ===============================================================*/

/** The default CPU clock */
#ifndef F_CPU
#define F_CPU                   (8000000UL)
#endif

/*
 * IRQ macros for ATmega1281
 */

/*
 * AT86RF230:
 *
 * TRX_MAIN_IRQ_HDLR_IDX       TRX interrupt mapped to MCU input capture pin
 * TRX_TSTAMP_IRQ_HDLR_IDX       Not used
 */

/* Number of used TRX IRQs in this implementation */
#define NO_OF_TRX_IRQS                  (1)

/* Mapping of TRX IRQs to MCU pins */
#define TRX_IRQ                         (TIMER1_CAPT_vect)

/** Enables the transceiver interrupts. */
#define ENABLE_TRX_IRQ(trx_irq_num)     do {    \
    if (trx_irq_num == TRX_MAIN_IRQ_HDLR_IDX)          \
    {                                           \
        /* Enable RX TIME STAMP interrupt */    \
        TIMSK1 |= _BV(ICIE1);                   \
    }                                           \
} while (0)

/** Disables the transceiver interrupts. */
#define DISABLE_TRX_IRQ(trx_irq_num)     do {   \
    if (trx_irq_num == TRX_MAIN_IRQ_HDLR_IDX)          \
    {                                           \
        /* Disable RX TIME STAMP interrupt */   \
        TIMSK1 &= ~(_BV(ICIE1));                \
    }                                           \
} while (0)

/** Clears the transceiver interrupts. */
#define CLEAR_TRX_IRQ(trx_irq_num)     do {     \
    if (trx_irq_num == TRX_MAIN_IRQ_HDLR_IDX)          \
    {                                           \
        /* Clear RX TIME STAMP interrupt */     \
        TIFR1 = _BV(ICF1);                      \
    }                                           \
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
#define ENTER_TRX_REGION()      { uint8_t irq_mask = TIMSK1; TIMSK1 &= ~(_BV(ICIE1))

/*
 *  This macro restores the transceiver interrupt status
 */
#define LEAVE_TRX_REGION()      TIMSK1 = irq_mask; }


/*
 * GPIO macros for ATmega1281
 */

/*
 * This board uses an SPI-attached transceiver.
 */
#define PAL_USE_SPI_TRX                 (1)

/* Actual Ports */
/*
 * PortB DDR is data direction register for the transceiver
 */
#define TRX_PORT1_DDR                   (DDRB)

/*
 * PORTB is transceiver port
 */
#define TRX_PORT1                       (PORTB)

/*
 * Slave select pin is PORTB 0
 */
#define SEL                             (PB0)

/*
 * SPI serial clock pin is PORTB 1
 */
#define SCK                             (PB1)

/*
 * SPI Bus Master Output/Slave Input pin is PORTB 2
 */
#define MOSI                            (PB2)

/*
 * SPI Bus Master Input/Slave Output pin is PORTB 3
 */
#define MISO                            (PB3)

/*
 * Sleep Transceiver pin is PORTB 4
 */
#define SLP_TR                          (PB4)

/*
 * RESET pin is PORTB 5
 */
#define RST                             (PB5)

/*
 * Set TRX GPIO pins.
 */
#define RST_HIGH()                      (TRX_PORT1 |= _BV(RST))
#define RST_LOW()                       (TRX_PORT1 &= ~_BV(RST))
#define SLP_TR_HIGH()                   (TRX_PORT1 |= _BV(SLP_TR))
#define SLP_TR_LOW()                    (TRX_PORT1 &= ~_BV(SLP_TR))

/*
 * PORT where LEDs are connected
 */
#define LED_PORT                        (PORTE)
#define LED_PORT_DIR                    (DDRE)

/*
 * PINs where LEDs are connected
 */
#define LED_PIN_0                       (PE0)
#define LED_PIN_1                       (PE1)
#define LED_PIN_2                       (PE2)
#define LED_PIN_3                       (PE3)
#define LED_PIN_4                       (PE4)
#define LED_PIN_5                       (PE5)
#define LED_PIN_6                       (PE6)
#define LED_PIN_7                       (PE7)

/*
 * PORT where button is connected
 */
#define BUTTON_PORT                     (PORTF)
#define BUTTON_PORT_DIR                 (DDRF)
#define BUTTON_INPUT_PINS               (PINF)

/*
 * PINs where buttons are connected
 */
#define BUTTON_PIN_0                    (PF0)
#define BUTTON_PIN_1                    (PF1)
#define BUTTON_PIN_2                    (PF2)
#define BUTTON_PIN_3                    (PF3)

/*
 * Value of an external PA gain.
 * If no external PA is available, the value is 0.
 */
#define EXTERN_PA_GAIN                  (0)

/*
 * Timer macros for ATmega1281
 */

/*
 * This value is used by the calibration routine as target value of the timer
 * to be calibrated. At the end of a calibration cycle this value is compared
 * with the counter result.
 * TARGETVAL_CALIBRATION = CLK(Cal) * Count(Ref) / CLK(Ref) = 8,000,000 * 256 / 32,768
 *
 * CLK(Cal): Frequency of clock source of timer to be calibrated
 * CLK(Ref): Frequency of clock source of reference timer
 * Count(Ref): Value of reference timer after 1 full cycle (until overflow)
 *             for timer width of 8 bit
 */
#if (F_CPU == (8000000UL))
#define TARGETVAL_CALIBRATION           (62500)
#elif  (F_CPU == (4000000UL))
#define TARGETVAL_CALIBRATION           (31250)
#elif  (F_CPU == (2000000UL))
#define TARGETVAL_CALIBRATION           (15625)
#elif  (F_CPU == (1000000UL))
#define TARGETVAL_CALIBRATION           (7813)
#else
#error "Unsupported F_CPU value"
#endif

/** This value is the loop counter for calibration routine. */
#define MAX_CAL_LOOP_CNT                (100)

/*
 * These macros are placeholders for delay functions for high speed processors.
 *
 * The following delay are not reasonbly implemented via delay functions,
 * but rather via a certain number of NOP operations.
 * The actual number of NOPs for each delay is fully MCU and frequency
 * dependent, so it needs to be updated for each board configuration.
 *
 * ATmega1281 @ 8MHz
 */
/*
 * Wait for 65 ns.
 * time t7: SLP_TR time (see data sheet or SWPM).
 * In case the system clock is slower than 32 MHz we do not need
 * to have this value filled.
 */
#define PAL_WAIT_65_NS()                // empty

/* Wait for 500 ns. */
#define PAL_WAIT_500_NS()               {nop(); nop(); nop(); nop(); }

/* Wait for 1 us. */
#define PAL_WAIT_1_US()                 {nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();}

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
 */
#define TIMER_SRC_DURING_TRX_AWAKE() \
        (TCCR1B = ((1 << ICES1) | (1 << CS12) | (1 << CS11) | (1 << CS10)))

/*
 * Timer clock source while radio is sleeping.
 */
#define TIMER_SRC_DURING_TRX_SLEEP() \
        (TCCR1B = (1 << ICES1) | (1 << CS11))

/*
 * Maximum numbers of software timers running at a time
 */
#define MAX_NO_OF_TIMERS (25)
#if (MAX_NO_OF_TIMERS > 255)
#error "MAX_NO_OF_TIMERS must not be larger than 255"
#endif

/*
 * Hardware register that holds Rx timestamp
 */
#define TIME_STAMP_REGISTER             (ICR1)


/*
 * TRX Access macros for ATmega1281
 */

/*
 * Bit mask for slave select
 */
#define SS_BIT_MASK                     (1 << SEL)

/*
 * Slave select made low
 */
#define SS_LOW()                        ((TRX_PORT1) &= (~SS_BIT_MASK))

/*
 * Slave select made high
 */
#define SS_HIGH()                       ((TRX_PORT1) |= (SS_BIT_MASK))

/*
 * Mask for SPIF bit in SPSR register
 */
#define SPIF_MASK                       (1 << SPIF)

/*
 * Wait for SPI interrupt flag
 */
#define SPI_WAIT()                      while (!(SPSR & SPIF_MASK))

/*
 * Dummy value written in SPDR to retrieve data form it
 */
#define SPI_DUMMY_VALUE                 (0x00)

/*
 * TRX Initialization
 */
#define TRX_INIT()                      do {                        \
    /* Enable the SPI and make the microcontroller as SPI master */ \
    SPCR = _BV(SPE) | _BV(MSTR);                                    \
    SPSR = _BV(SPI2X); /* Double the SPI clock frequency */         \
    /* Select the serial clock SCK to be (FOSC/4)                   \
     * For Example for ATmega1281, FOSC = 8Mhz                      \
     * (Microcontroller operating frequency)                        \
     * SPI clock is thus set to (8/4)*2 = 4 Mhz                     \
     */                                                             \
    SPCR &= ~(_BV(SPR0) | _BV(SPR1));                               \
                                                                    \
    /* Set SEL pin which is on PortB to high */                     \
    TRX_PORT1 |= _BV(SEL);                                          \
} while (0)

/*
 * SPI Interrupt enable macro
 */
#define SPI_IRQ_ENABLE()    SPCR |= _BV(SPIE)

/*
 * SPI Interrupt disable macro
 */
#define SPI_IRQ_DISABLE()    SPCR &= ~_BV(SPIE)

/*
 * SPI Interrupt clear macro
 */
#define SPI_IRQ_CLEAR()     SPSR &= ~_BV(SPIF)


/*
 * UART0 and UART1 non-generic (board specific) initialization part.
 */
/* Data Length is 8 bit */
#define UART_0_INIT_NON_GENERIC()   (UCSR0C = (1 << UCSZ01) | (1 << UCSZ00))
#define UART_1_INIT_NON_GENERIC()   (UCSR1C = (1 << UCSZ11) | (1 << UCSZ10))


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
        LED_PORT = 0;                           \
        LED_PORT_DIR = 0xFF;                    \
} while (0)

/*
 * Alert indication
 */
#define ALERT_INDICATE()                (LED_PORT = (uint8_t)(~(uint16_t)(LED_PORT)))


/* === Prototypes ===========================================================*/
#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif


/*
 * MCU pins used for debugging
 */
#ifdef ENABLE_DEBUG_PINS
// Pin and port assignment
#define TST_PIN_0_HIGH()                PORTF |= (1 << 0)
#define TST_PIN_0_LOW()                 PORTF &= ~(1 << 0)
#define TST_PIN_1_HIGH()                PORTF |= (1 << 1)
#define TST_PIN_1_LOW()                 PORTF &= ~(1 << 1)
#define TST_PIN_2_HIGH()                PORTF |= (1 << 2)
#define TST_PIN_2_LOW()                 PORTF &= ~(1 << 2)
#define TST_PIN_3_HIGH()                PORTF |= (1 << 3)
#define TST_PIN_3_LOW()                 PORTF &= ~(1 << 3)
#define TST_PIN_4_HIGH()                PORTE |= (1 << 2)
#define TST_PIN_4_LOW()                 PORTE &= ~(1 << 2)
#define TST_PIN_5_HIGH()                PORTE |= (1 << 3)
#define TST_PIN_5_LOW()                 PORTE &= ~(1 << 3)
#define TST_PIN_6_HIGH()                PORTE |= (1 << 4)
#define TST_PIN_6_LOW()                 PORTE &= ~(1 << 4)
#define TST_PIN_7_HIGH()                PORTE |= (1 << 6)
#define TST_PIN_7_LOW()                 PORTE &= ~(1 << 6)
#define TST_PIN_8_HIGH()                PORTE |= (1 << 7)
#define TST_PIN_8_LOW()                 PORTE &= ~(1 << 7)
#else   /* ENABLE_DEBUG_PINS */
// empty pin assignment
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
#endif  /* ENABLE_DEBUG_PINS */


#endif /* REB_2_3_STK500_STK501 */

#endif  /* PAL_CONFIG_H */
/* EOF */
