/*
 * lib_sam4e16e_board.h
 *
 *  Created on: 2015. 4. 21.
 *      Author: geoyun
 */

#ifndef APPLICATION_LIB_I2C_MASTER_ITF_LIB_SAM4E16E_BOARD_H_
#define APPLICATION_LIB_I2C_MASTER_ITF_LIB_SAM4E16E_BOARD_H_

/**
 * \brief Set peripheral mode for IOPORT pins.
 * It will configure port mode and disable pin mode (but enable peripheral).
 * \param port IOPORT port to configure
 * \param masks IOPORT pin masks to configure
 * \param mode Mode masks to configure for the specified pin (\ref ioport_modes)
 */
#define ioport_set_port_peripheral_mode(port, masks, mode) \
	do {\
		ioport_set_port_mode(port, masks, mode);\
		ioport_disable_port(port, masks);\
	} while (0)

/**
 * \brief Set peripheral mode for one single IOPORT pin.
 * It will configure port mode and disable pin mode (but enable peripheral).
 * \param pin IOPORT pin to configure
 * \param mode Mode masks to configure for the specified pin (\ref ioport_modes)
 */
#define ioport_set_pin_peripheral_mode(pin, mode) \
	do {\
		ioport_set_pin_mode(pin, mode);\
		ioport_disable_pin(pin);\
	} while (0)

/**
 * \brief Set input mode for one single IOPORT pin.
 * It will configure port mode and disable pin mode (but enable peripheral).
 * \param pin IOPORT pin to configure
 * \param mode Mode masks to configure for the specified pin (\ref ioport_modes)
 * \param sense Sense for interrupt detection (\ref ioport_sense)
 */
#define ioport_set_pin_input_mode(pin, mode, sense) \
	do {\
		ioport_set_pin_dir(pin, IOPORT_DIR_INPUT);\
		ioport_set_pin_mode(pin, mode);\
		ioport_set_pin_sense_mode(pin, sense);\
	} while (0)



///** \name IOPORT Mode bit definitions */
///** @{ */
//#define IOPORT_MODE_MUX_MASK            (0x7 << 0) /*!< MUX bits mask */
//#define IOPORT_MODE_MUX_BIT0            (  1 << 0) /*!< MUX BIT0 mask */
//
//#if SAM3N || SAM3S || SAM4S || SAM4E || SAM4N || SAM4C || SAM4CM || SAMG || SAM4CP
//#define IOPORT_MODE_MUX_BIT1            (  1 << 1) /*!< MUX BIT1 mask */
//#endif
//
#define IOPORT_MODE_MUX_A               (  0 << 0) /*!< MUX function A */
#define IOPORT_MODE_MUX_B               (  1 << 0) /*!< MUX function B */
//
//#if SAM3N || SAM3S || SAM4S || SAM4E || SAM4N || SAM4C || SAM4CM || SAMG || SAM4CP
//#define IOPORT_MODE_MUX_C               (  2 << 0) /*!< MUX function C */
//#define IOPORT_MODE_MUX_D               (  3 << 0) /*!< MUX function D */
//#endif
//
//#define IOPORT_MODE_PULLUP              (  1 << 3) /*!< Pull-up */
//
//#if SAM3N || SAM3S || SAM4S || SAM4E || SAM4N || SAM4C || SAM4CM || SAMG || SAM4CP
//#define IOPORT_MODE_PULLDOWN            (  1 << 4) /*!< Pull-down */
//#endif
//
//#define IOPORT_MODE_OPEN_DRAIN          (  1 << 5) /*!< Open drain */
//
//#define IOPORT_MODE_GLITCH_FILTER       (  1 << 6) /*!< Glitch filter */
//#define IOPORT_MODE_DEBOUNCE            (  1 << 7) /*!< Input debounce */
///** @} */


///*  Default pin configuration (no attribute). */
//#define PIO_DEFAULT             (0u << 0)
///*  The internal pin pull-up is active. */
//#define PIO_PULLUP              (1u << 0)
///*  The internal glitch filter is active. */
//#define PIO_DEGLITCH            (1u << 1)
///*  The pin is open-drain. */
//#define PIO_OPENDRAIN           (1u << 2)
//
///*  The internal debouncing filter is active. */
//#define PIO_DEBOUNCE            (1u << 3)
//
///*  Enable additional interrupt modes. */
//#define PIO_IT_AIME             (1u << 4)
//
///*  Interrupt High Level/Rising Edge detection is active. */
//#define PIO_IT_RE_OR_HL         (1u << 5)
///*  Interrupt Edge detection is active. */
//#define PIO_IT_EDGE             (1u << 6)
//
///*  Low level interrupt is active */
//#define PIO_IT_LOW_LEVEL        (0               | 0 | PIO_IT_AIME)
///*  High level interrupt is active */
//#define PIO_IT_HIGH_LEVEL       (PIO_IT_RE_OR_HL | 0 | PIO_IT_AIME)
///*  Falling edge interrupt is active */
//#define PIO_IT_FALL_EDGE        (0               | PIO_IT_EDGE | PIO_IT_AIME)
///*  Rising edge interrupt is active */
//#define PIO_IT_RISE_EDGE        (PIO_IT_RE_OR_HL | PIO_IT_EDGE | PIO_IT_AIME)

///** Push button pin definition. */
//#define PUSH_BUTTON_PIO          PIOA
//#define PUSH_BUTTON_ID           ID_PIOA
//#define	PUSH_BUTTON_DEBOUNCE_HZ	 10
//#define PUSH_BUTTON_ATTR         (PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)


#define UBI_PIO_DEFAULT			( 1 << 0 )
#define	UBI_PIO_PULL_UP			( 1 << 1 )
#define UBI_PIO_PULL_DOWN		( 1 << 2 )
#define UBI_PIO_PULL_UPNDOWN_MASK	(UBI_PIO_PULL_UP | UBI_PIO_PULL_DOWN)

#define	UBI_PIO_DEGLITCH		( 1 << 3 )
#define	UBI_PIO_OPENDRAIN		( 1 << 4 )
#define UBI_PIO_DEBOUNCE		( 1 << 5 )

#define	UBI_PIO_IT_AIME			( 1 << 6 )
#define	UBI_PIO_IT_RE_OR_HL		( 1 << 7 )
#define UBI_PIO_IT_EDGE			( 1 << 8 )

#define UBI_PIO_IT_LOWLEVEL		( 1 << 9 )
#define	UBI_PIO_IT_HIGHLEVEL	( 1 << 10 )
#define	UBI_PIO_IT_FALL_EDGE	( 1 << 11 )
#define	UBI_PIO_IT_RISE_EDGE	( 1 << 12 )
#define UBI_PIO_IT_BOTH_EDGE	( UBI_PIO_IT_FALL_EDGE | UBI_PIO_IT_RISE_EDGE)
#define	UBI_PIO_IT_TRI_MASK		(UBI_PIO_IT_LOWLEVEL | UBI_PIO_IT_HIGHLEVEL | UBI_PIO_IT_FALL_EDGE | UBI_PIO_IT_RISE_EDGE)

#define	PUSH_BUTTON_DEBOUNCE_HZ	 10

#define	PORTA	0
#define	PORTB	1
#define	PORTC	2
#define	PORTD	3
#define	PORTE	4

#define	NOT_INIT		-3
#define	ALREADY_INIT	-2
#define	FAILE 			-1
#define	SUCCESS			0


int sam4e16e_board_init(void);
void configure_button(void);


#endif /* APPLICATION_LIB_I2C_MASTER_ITF_LIB_SAM4E16E_BOARD_H_ */
