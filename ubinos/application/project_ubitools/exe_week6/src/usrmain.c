/*
  Copyright (C) 2009 Sung Ho Park
  Contact: ubinos.org@gmail.com

  This file is part of the exe_helloworld component of the Ubinos.

  GNU General Public License Usage
  This file may be used under the terms of the GNU
  General Public License version 3.0 as published by the Free Software
  Foundation and appearing in the file license_gpl3.txt included in the
  packaging of this file. Please review the following information to
  ensure the GNU General Public License version 3.0 requirements will be
  met: http://www.gnu.org/copyleft/gpl.html.

  GNU Lesser General Public License Usage
  Alternatively, this file may be used under the terms of the GNU Lesser
  General Public License version 2.1 as published by the Free Software
  Foundation and appearing in the file license_lgpl.txt included in the
  packaging of this file. Please review the following information to
  ensure the GNU Lesser General Public License version 2.1 requirements
  will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.

  Commercial Usage
  Alternatively, licensees holding valid commercial licenses may
  use this file in accordance with the commercial license agreement
  provided with the software or, alternatively, in accordance with the
  terms contained in a written agreement between you and rightful owner.
*/

/* -------------------------------------------------------------------------
	Include
 ------------------------------------------------------------------------- */
#include "../ubiconfig.h"

// standard c library include
#include <stdio.h>
#include <sam4e.h>

// ubinos library include
#include "itf_ubinos/itf/bsp.h"
#include "itf_ubinos/itf/ubinos.h"
#include "itf_ubinos/itf/bsp_fpu.h"
#include "itf_ubinos/itf/bsp_intr.h"

// chipset driver include
#include "ioport.h"
#include "pio/pio.h"

// new estk driver include
#include "lib_new_estk_api/itf/new_estk_led.h"
#include "lib_new_estk_api/itf/new_estk_glcd.h"
#include "lib_motor_driver/itf/lib_motor_driver.h"
#include "lib_switch/itf/lib_switch.h"

// custom library header file include
//#include "../../lib_default/itf/lib_default.h"

// user header file include

/* -------------------------------------------------------------------------
	Global variables
 ------------------------------------------------------------------------- */
#define STOP	0
#define RUN		1

static char g_state = RUN;

sem_pt g_sem;
int count = 0;
/* -------------------------------------------------------------------------
	Prototypes
 ------------------------------------------------------------------------- */
static void rootfunc(void * arg);
static void switch_isr(void);
static void switch_isr2(void);

static void timer_isr(void);
static void print_lcd(void *arg);

/* -------------------------------------------------------------------------
	Function Definitions
 ------------------------------------------------------------------------- */
int usrmain(int argc, char * argv[]) {
	int r;

	printf("\n\n\n\r");
	printf("================================================================================\n\r");
	printf("exe_week6 (build time: %s %s)\n\r", __TIME__, __DATE__);
	printf("================================================================================\n\r");

	r = sem_create(&g_sem);
	if (0 != r) {
		logme("fail at sem_create \r\n");
	}

	r = task_create(NULL, print_lcd, NULL, task_getmiddlepriority(), 256, "print_lcd");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	r = task_create(NULL, rootfunc, NULL, task_getmiddlepriority(), 256, "root");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	/* enable timer clock */
	PMC->PMC_PCER0 = 1 << ID_TC3;

	/* Timer Configuration */
	TC1->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKDIS;
	TC1->TC_CHANNEL[0].TC_IDR = 0xFFFFFFFF;

	/* Channel MODE */
	TC1->TC_CHANNEL[0].TC_CMR = (TC_CMR_TCCLKS_TIMER_CLOCK5 | TC_CMR_CPCTRG);
	TC1->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN;
	TC1->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;

	/* interrupt handler */
	intr_connectisr(TC3_IRQn, timer_isr, 0x40, INTR_OPT__LEVEL);

	/* enable interrupt*/
	intr_enable(TC3_IRQn);

	/* Timer Interrupt Period Configuration */
	TC1->TC_CHANNEL[0].TC_RC = 32768;

	/* Start timer */
	TC1->TC_CHANNEL[0].TC_CCR = TC_CCR_SWTRG;


	ubik_comp_start();

	return 0;
}

static void rootfunc(void * arg) {
	switch_init(switch_isr, switch_isr2);

//	for(;;){
//		if ((PIOA->PIO_PDSR & PIO_PA20) >> PIO_PA20_IDX == 0) {
//			count = 0;
//		}
//	}
}

static void print_lcd(void *arg) {
	glcd_init();

	while (1) {
		sem_take(g_sem);
		glcdGotoChar(0, 0);

		glcd_printf("HW_TIMER : %3d", count);
		task_sleep(100);
	}
}

static void switch_isr(void) {
	if (g_state == STOP) {
		g_state = RUN;
	} else if (g_state == RUN) {
		g_state = STOP;
	}
}

static void switch_isr2(void) {
	sem_give(g_sem);
	count = 0;
}

static void timer_isr(void) {
	unsigned int reg;

	sem_give(g_sem);
	if (g_state == RUN) count++;

	reg = TC1->TC_CHANNEL[0].TC_SR;
	printf("HW_TIMER [TC:%d] \r\n", reg);
}
