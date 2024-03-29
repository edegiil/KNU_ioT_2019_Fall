/**
 * @file pal_board.c
 *
 * @brief PAL board specific functionality
 *
 * This file implements PAL board specific functionality.
 *
 * $Id: pal_board.c,v 1.3 2010-08-04 04:39:49 slb Exp $
 *
 * @author    Atmel Corporation: http://www.atmel.com
 * @author    Support email: avr@atmel.com
 */
/*
 * Copyright (c) 2009, Atmel Corporation All rights reserved.
 *
 * Licensed under Atmel's Limited License Agreement --> EULA.txt
 */

#include "../../../../../../ubiconfig.h"

#if (AVR == PAL_GENERIC_TYPE) && (AT90USB1287 == PAL_TYPE) && (USBSTICK_C == BOARD_TYPE)

/* === Includes ============================================================ */

#include <stdbool.h>
#include <stdlib.h>
#include "../../../../Inc/pal.h"
#include "../pal_boardtypes.h"
#include "../../../../../Include/_pal_config.h"
/*
 * 'sys_time' is a entity of timer module which is given to other modules
 * through the interface file below. 'sys_time' is required to obtain the
 * frame timestamp
 */
#include "../../../Generic/Inc/pal_timer.h"

#if (BOARD_TYPE == USBSTICK_C)

/* === Globals ============================================================== */


/* === Implementation ======================================================= */

/**
 * @brief Provides timestamp of the last received frame
 *
 * This function provides the timestamp (in microseconds)
 * of the last received frame.
 *
 * @param[out] Timestamp in microseconds
 */
void pal_trx_read_timestamp(uint32_t *timestamp)
{
    /*
     * Everytime a transceiver interrupt is triggred, input capture register of
     * the AVR is latched. The 'sys_time' is concatenated to the ICR to
     * generate the time stamp of the received frame.
     * 'sys_time'   'ICR'
     *  ---------|--------- => 32 bit timestamp
     *   16 bits   16 bits
     */
    *timestamp = (uint32_t)sys_time << (uint32_t)16;
    *timestamp |= (uint32_t)TIME_STAMP_REGISTER;
}



/**
 * @brief Calibrates the internal RC oscillator
 *
 * This function calibrates the internal RC oscillator.
 *
 * @return True since internal RC oscillator is not used and thus does not need
 *         to be calibrated.
 */
bool pal_calibrate_rc_osc(void)
{
    return (true);
}



/**
 * @brief Initializes the GPIO pins
 *
 * This function is used to initialize the port pins used to connect
 * the microcontroller to transceiver.
 */
void gpio_init(void)
{
    /* The following pins are output pins.  */
    TRX_PORT1_DDR |= _BV(SEL);
    TRX_PORT1_DDR |= _BV(SCK);
    TRX_PORT1_DDR |= _BV(RST);
    TRX_PORT1_DDR |= _BV(MOSI);
    TRX_PORT1_DDR |= _BV(SLP_TR);

    /* The following pins are input pins.  */
    TRX_PORT1_DDR &= ~_BV(MISO);
}



/**
 * @brief Initialize LEDs
 */
void pal_led_init(void)
{
    LED_PORT_LED_0 &= ~(1 << LED_PIN_0); // high active
    LED_PORT_LED_1 |= (1 << LED_PIN_1); // low active
    LED_PORT_LED_2 |= (1 << LED_PIN_2); // low active
    LED_PORT_LED_3 |= (1 << LED_PIN_3); // low active
    LED_PORT_DIR_LED_0 |= (1 << LED_PIN_0);
    LED_PORT_DIR_LED_1 |= (1 << LED_PIN_1);
    LED_PORT_DIR_LED_2 |= (1 << LED_PIN_2);
    LED_PORT_DIR_LED_3 |= (1 << LED_PIN_3);
}



/**
 * @brief Control LED status
 *
 * @param[in]  led_no LED ID
 * @param[in]  led_setting LED_ON, LED_OFF, LED_TOGGLE
 */
void pal_led(led_id_t led_no, led_action_t led_setting)
{
    uint8_t pin;
    uint8_t *port;
    bool active_dir;

    switch (led_no)
    {
        case LED_0: /* high active */
            pin = LED_PIN_0;
            port = (uint8_t *)&LED_PORT_LED_0;
            active_dir = HIGH;
            break;

        case LED_1: /* low active */
            pin = LED_PIN_1;
            port = (uint8_t *)&LED_PORT_LED_1;
            active_dir = LOW; break;

        case LED_2: /* low active */
            pin = LED_PIN_2;
            port = (uint8_t *)&LED_PORT_LED_2;
            active_dir = LOW; break;

        case LED_3: /* low active */
            pin = LED_PIN_3;
            port = (uint8_t *)&LED_PORT_LED_3;
            active_dir = LOW;
            break;

        default: return;
    }

    switch (led_setting)
    {
        case LED_ON:
            if (active_dir == HIGH)
            {
                *port = *port | (1 << pin);
            }
            else
            {
                *port = *port & (~(1 << pin));
            }
            break;

        case LED_OFF:
            if (active_dir == HIGH)
            {
                *port = *port & (~(1 << pin));
            }
            else
            {
                *port = *port | (1 << pin);
            }
            break;

        case LED_TOGGLE:
        default:
            if ((*port & (1 << pin)) == 0x00)
            {
                *port = *port | (1 << pin);
            }
            else
            {
                *port = *port & (~(1 << pin));
            }
            break;
    }
}



/*
 * This function is called by timer_init() to perform the non-generic portion
 * of the initialization of the timer module.
 */
void timer_init_non_generic(void)
{
    /* Select proper clock as timer clock source when radio is sleeping */
    TIMER_SRC_DURING_TRX_SLEEP();

    /*
     * Clear pending output compare matches of all the OCR1A, OCR1B and
     * OCR1C.
     */
    TIFR1 = _BV(OCF1A);
    TIFR1 = _BV(OCF1B);
    TIFR1 = _BV(OCF1C);

    /* Enable the timer overflow interrupt */
    TIMSK1 |= _BV(TOIE1);
}



/**
 * @brief Generation of random seed for function srand() in case this
 *        is not supported by the transceiver (e.g. AT86RF230)
 *
 * @return uint16_t Random number to be used as seed for function srand()
 * @ingroup apiPalApi
 */
uint16_t pal_generate_rand_seed(void)
{
    uint8_t cur_random_seed;

    /* Init the ADC. */
    ADMUX = (1 << REFS0) | 0xD;     /* ADC3 and ADC2 with 200x gain */

    ADCSRA |= (1 << ADATE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADEN) | (1 << ADIF) | (1 << ADSC);

    /* Start conversion. */
    while ((ADCSRA & (1 << ADIF)) == 0);

    cur_random_seed = ADCL;

    ADMUX = 0;

    ADCSRA = 0;

    return ((uint16_t)cur_random_seed);
}

#endif /* USBSTICK_C */

#endif /* (AVR == PAL_GENERIC_TYPE) && (AT90USB1287 == PAL_TYPE) && (USBSTICK_C == BOARD_TYPE) */

/* EOF */
