/**
 * @file pal.c
 *
 * @brief General PAL functions for AVR 8-Bit MCUs
 *
 * This file implements generic PAL function and performs
 * USB related handling if required for AVR 8-Bit MCUs.
 *
 * $Id: pal.c,v 1.3 2010-08-05 02:18:15 slb Exp $
 *
 * @author    Atmel Corporation: http://www.atmel.com
 * @author    Support email: avr@atmel.com
 */
/*
 * Copyright (c) 2009, Atmel Corporation All rights reserved.
 *
 * Licensed under Atmel's Limited License Agreement --> EULA.txt
 */

#include "../../../../../ubiconfig.h"

#if (AVR == PAL_GENERIC_TYPE)

/* === Includes ============================================================ */

#include <stdint.h>
#include <stdbool.h>
#include "../../../Inc/pal.h"
#include "../../../../Include/_pal_config.h"
#include "../Inc/pal_timer.h"
#include "../Inc/pal_trx_access.h"
#include "../Inc/pal_internal.h"
#include "../../../../Include/_app_config.h"

#ifdef USB0
#include "../Inc/pal_usb.h"
#endif /* USB0 */

/* === Globals ============================================================= */

/*
 * This section defines all global variables for the PAL
 */

/**
 * This is the most significant part of the system time. The least one is
 * timer1 (TCNT1) itself.  Exported since input capture units might want
 * to know about this value as well.
 */
volatile uint16_t sys_time;

/* === Prototypes ========================================================== */

static void mcu_clock_init(void);

/* === Implementation ====================================================== */

/**
 * @brief Initialization of PAL
 *
 * This function initializes the PAL.
 * This includes selecting the proper system clock source, initializing the
 * GPIOs, the interface to the transceiver, and the timers.
 *
 * @return MAC_SUCCESS if PAL initialization is successful, FAILURE otherwise
 */
retval_t pal_init(void)
{
    mcu_clock_init();
    gpio_init();
    trx_interface_init();
    timer_init();

    return MAC_SUCCESS;
}



/**
 * @brief Services timer and sio handler
 *
 * This function calls sio & timer handling functions.
 */
void pal_task(void)
{
#if (TOTAL_NUMBER_OF_TIMERS > 0)
    timer_service();
#endif

/*
 * If the serial communication is done using USB, only then the 'usb_handler'
 * needs to be called. For UART, the data handling is done in the UART ISR.
 */
#ifdef USB0
    usb_handler();
#endif /* USB0 */
}



/**
 * @brief Get data from persistence storage
 *
 * @param[in]  ps_type Persistence storage type
 * @param[in]  start_addr Start offset within EEPROM
 * @param[in]  length Number of bytes to read from EEPROM
 * @param[out] value Data from persistence storage
 *
 * @return MAC_SUCCESS  if everything went OK else FAILURE
 */
retval_t pal_ps_get(ps_type_t ps_type, uint16_t start_addr, uint16_t length, void *value)
{
#if (EXTERN_EEPROM_AVAILABLE == 1)
    if (ps_type == EXTERN_EEPROM)
    {
        return extern_eeprom_get(start_addr, length, value);
    }
    else
#endif

    if (ps_type == INTERN_EEPROM)
    {
        uint16_t index;
        uint8_t *data_ptr;

        if ((start_addr + length) > E2END)
        {
            return FAILURE;
        }

        data_ptr = (uint8_t *)(value);
        for (index = 0; index < length; index++)
        {
            EEGET(*data_ptr, start_addr);
            start_addr++;
            data_ptr++;
        }
    }
    else    // no internal eeprom and no external eeprom available
    {
        return MAC_INVALID_PARAMETER;
    }

    return MAC_SUCCESS;
}



/**
 * @brief Write data to persistence storage
 *
 * @param[in]  start_addr Start address offset within EEPROM
 * @param[in]  length Number of bytes to be written to EEPROM
 * @param[in]  value Data to persistence storage
 *
 * @return MAC_SUCCESS  if everything went OK else FAILURE
 */
retval_t pal_ps_set(uint16_t start_addr, uint16_t length, void *value)
{
    uint8_t *data_ptr;
    uint16_t i;
    uint8_t read_data;

    if ((start_addr + length) > E2END)
    {
        return FAILURE;
    }

    data_ptr = (uint8_t *)(value);
    for (i = 0; i < length; i++)
    {
        EEGET(read_data, start_addr);
        if (read_data != *data_ptr)
        {
            EEPUT(start_addr, *data_ptr);
        }
        data_ptr++;
        start_addr++;
    }

    return MAC_SUCCESS;
}



/**
 * @brief Alert indication
 *
 * This Function can be used by any application to indicate an error condition.
 * The function is blocking and does never return.
 */
void pal_alert(void)
{
#if (DEBUG > 0)
    bool debug_flag = false;
#endif
    ALERT_INIT();

    while (1)
    {
        pal_timer_delay(0xFFFF);
        ALERT_INDICATE();

#if (DEBUG > 0)
        /* Used for debugging purposes only */
        if (debug_flag == true)
        {
            break;
        }
#endif
    }
}



/**
 * @brief Initialize the system clock
 *
 * This function sets the system clock by enabling the internal RC oscillator
 * with the proper prescaler (if available).
 * Ensure that CKDIV8 fuse does not affect the system clock prescaler.
 *
 */
static void mcu_clock_init(void)
{
/*
 * This is only allowed if the AVR 8-bit MCU already has a clock prescaler.
 * For older devices this function does not make sense.
 * Therefore the existence of register CLKPR is checked.
 */
#ifdef CLKPR    /* Is clock prescaler existing? */

#if (F_CPU == (8000000UL))
#ifdef __ICCAVR__
    ENTER_CRITICAL_REGION();
    CLKPR = 0x80;
    CLKPR = 0x00;
    LEAVE_CRITICAL_REGION();
#else
    clock_prescale_set(clock_div_1);
#endif  /* __ICCAVR__ */
#endif  /* (F_CPU == (8000000UL) */

#if (F_CPU == (4000000UL))
#ifdef __ICCAVR__
    ENTER_CRITICAL_REGION();
    CLKPR = 0x80;
    CLKPR = 0x01;
    LEAVE_CRITICAL_REGION();
#else
    clock_prescale_set(clock_div_2);
#endif  /* __ICCAVR__ */
#endif  /* (F_CPU == (4000000UL) */

#if (F_CPU == (2000000UL))
#ifdef __ICCAVR__
    ENTER_CRITICAL_REGION();
    CLKPR = 0x80;
    CLKPR = 0x02;
    LEAVE_CRITICAL_REGION();
#else
    clock_prescale_set(clock_div_4);
#endif  /* __ICCAVR__ */
#endif  /* (F_CPU == (2000000UL) */

#if (F_CPU == (1000000UL))
#ifdef __ICCAVR__
    ENTER_CRITICAL_REGION();
    CLKPR = 0x80;
    CLKPR = 0x03;
    LEAVE_CRITICAL_REGION();
#else
    clock_prescale_set(clock_div_8);
#endif  /* __ICCAVR__ */
#endif  /* (F_CPU == (1000000UL) */

#endif  /* CLKPR */
}

#endif /* (AVR == PAL_GENERIC_TYPE) */

/* EOF */
