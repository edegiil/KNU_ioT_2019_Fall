/**
 * @file pal_types.h
 *
 * @brief Definition of supported PAL types
 *
 * This header file contains the supported PAL types.
 *
 * $Id: pal_types.h,v 1.4 2012-02-13 01:31:11 essusige Exp $
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
#ifndef PAL_TYPES_H
#define PAL_TYPES_H

#include "../../../ubiconfig.h"

/* PAL_GENERIC_TYPE */
#define AVR                             (0x01)
#define MEGA_RF                         (0x02)
#define XMEGA                           (0x03)
#define AVR32                           (0x04)
#define ARM7                            (0x05)
#define ARM9                            (0x06)
#define SAM3S                           (0x07)

#if (PAL_GENERIC_TYPE == AVR)
    /* PAL_TYPE for AVR 8-bit MCUs */
    #define AT90USB1287                 (0x01)
    #define ATMEGA1281                  (0x02)
    #define ATMEGA1284P                 (0x03)
    #define ATMEGA2561                  (0x04)
    #define ATMEGA644P                  (0x05)

#elif (PAL_GENERIC_TYPE == XMEGA)
    /* PAL_TYPE for XMEGA MCUs */
    #define ATXMEGA128A1                (0x01)
    #define ATXMEGA256A3                (0x02)

#elif (PAL_GENERIC_TYPE == AVR32)
    /* PAL_TYPE for AVR 32-bit MCUs */

#elif (PAL_GENERIC_TYPE == ARM7)
    /* PAL_TYPE for ARM7 MCUs */

    /* AT91SAM7X256 and AT91SAM7CX256:
     *
     * AT91SAM7CX256 is the same as AT91SAM7X256 except hardware AES engine.
     * If this boardtype is used, the file are actually taken from the
     * directory PAL/ARM7/AT91SAM7X256.
     * Only in case security shall be used, separate security files are selected
     * based on this PAL type.
     */
    #define AT91SAM7X256                (0x01)
    #define AT91SAM7XC256               (0x02)

#elif (PAL_GENERIC_TYPE == ARM9)
    /* PAL_TYPE for ARM9 MCUs */

    /* AT91SAM9XE512: */
    #define AT91SAM9XE512               (0x01)

#elif (PAL_GENERIC_TYPE == MEGA_RF)
    /* PAL_TYPE for MEGA-RF single chips (MCU plus transceiver) */
    #define ATMEGA128RFA1               (0x01)

#elif (PAL_GENERIC_TYPE == SAM3S)
    /* PAL_TYPE for SAM3S MCUs */

    /* AT91SAM3S4: */
    #define AT91SAM3S4  	            (0x01)

#else
    #error "Undefined PAL_GENERIC_TYPE"
#endif

/* Depending on the generic device type include platform-dependend types (IAR, GCC) */
#if ((PAL_GENERIC_TYPE == AVR) || (PAL_GENERIC_TYPE == XMEGA) || (PAL_GENERIC_TYPE == MEGA_RF))
#include "avrtypes.h"
#elif ((PAL_GENERIC_TYPE == ARM7) || (PAL_GENERIC_TYPE == ARM9)||(PAL_GENERIC_TYPE == SAM3S))
#include "armtypes.h"
#else
#error "Unknown PAL_GENERIC_TYPE"
#endif

#endif  /* PAL_TYPES_H */
/* EOF */
