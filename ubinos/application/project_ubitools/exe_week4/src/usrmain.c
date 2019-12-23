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

// chipset driver include
#include "ioport.h"
#include "pio/pio.h"

// new estk driver include
#include "lib_new_estk_api/itf/new_estk_led.h"
#include "lib_new_estk_api/itf/new_estk_glcd.h"
#include "lib_motor_driver/itf/lib_motor_driver.h"
#include "lib_EV3_sensor/itf/lib_EV3_sensor.h"

// custom library header file include
//#include "../../lib_default/itf/lib_default.h"

// user header file include

/* -------------------------------------------------------------------------
	Global variables
 ------------------------------------------------------------------------- */
#define IDLE_PRIORITY 0

/* -------------------------------------------------------------------------
	Prototypes
 ------------------------------------------------------------------------- */
task_pt task_handle01;
task_pt task_handle02;

static void taskfunc01(void *arg);
static void taskfunc02(void *arg);


/* -------------------------------------------------------------------------
	Function Definitions
 ------------------------------------------------------------------------- */
int usrmain(int argc, char * argv[]) {
	int r;
	int color = 0;

	printf("\n\n\n\r");
	printf("================================================================================\n\r");
	printf("exe_homework #4 (build time: %s %s)\n\r", __TIME__, __DATE__);
	printf("================================================================================\n\r");

	// create task of color sensor
	r = task_create(&task_handle01, taskfunc01, &color, IDLE_PRIORITY + 2, 256, "color_task");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	// create task of motor
	r = task_create(&task_handle02, taskfunc02, &color, IDLE_PRIORITY + 1, 256, "motor_task");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	ubik_comp_start();

	return 0;
}

static void taskfunc01(void *arg) {
	// initialize lcd and sensor
	glcd_init();
	ev3_sensor_init(0, COL_COLOR);

	for (;;) {
		glcd_clear();

		// receive color pointer as arg, and put sensor data in it
		*(int*)arg = ev3_sensor_get(0);
		glcd_printf("%d\n", arg);

		// pause for 0.1s
		task_sleep(100);
	}
}

static void taskfunc02(void *arg) {
	// initialize motor
	//	**lcd initialization is not necessary because it has already been initialized in prior task_01
	motor_init();
	for (;;) {
		glcdGotoChar(0, 0);

		// receive color as arg
		switch (*(int*)arg) {
			case 1:
				motor_set(0, 100);
				glcd_printf("color : black\nmotor speed : 100");
				break;
			case 2:
				motor_set(0, 200);
				glcd_printf("color : blue\nmotor speed : 200");
				break;
			case 3:
				motor_set(0, 300);
				glcd_printf("color : green\nmotor speed : 300");
				break;
			case 4:
				motor_set(0, 400);
				glcd_printf("color : yellow\nmotor speed : 400");
				break;
			case 5:
				motor_set(0, 500);
				glcd_printf("color : red\nmotor speed : 500");
				break;
			case 6:
				motor_set(0, 600);
				glcd_printf("color : white\nmotor speed : 600");
				break;
			case 7:
				motor_set(0, 700);
				glcd_printf("color : brown\nmotor speed : 700");
				break;
			default:
				motor_set(0, 0);
				glcd_printf("color : undefined\nmotor speed : 0");
		}

		// pause for 0.1s
		task_sleep(100);
	}
}
