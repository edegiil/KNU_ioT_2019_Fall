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
#include <stdbool.h>
#include <stdlib.h>

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
#include "lib_EV3_sensor/itf/lib_EV3_sensor.h"
#include "lib_motor_driver/itf/lib_motor_driver.h"
#include "lib_sensor/itf/lib_sensor.h"

// custom library header file include

// user header file include
#include "define.h"

/* -------------------------------------------------------------------------
	Global variables
 ------------------------------------------------------------------------- */
static mutex_pt mutex = NULL;
static bool game_state = false;
static int current_color = 0;
static bool direction = true;
static bool enemy_detect = false;
static bool last_10sec = false;

/* -------------------------------------------------------------------------
	Prototypes
 ------------------------------------------------------------------------- */
static void start_end_task(void * arg);
static void set_state_task(void * arg);
static void set_movement_task(void * arg);

void turn_left(int degree);
void turn_right(int degree);
void turn_random(void);
void go_forward(int speed);
void go_backward(int speed);
void stop(void);
void direction_check(void);

/* -------------------------------------------------------------------------
	main function
 ------------------------------------------------------------------------- */
int usrmain(int argc, char * argv[]) {
	int r;

	printf("\n\n\n\r");
	printf("================================================================================\n\r");
	printf("exe_robot (build time: %s %s)\n\r", __TIME__, __DATE__);
	printf("================================================================================\n\r");

	// sensor initialization
	glcd_init();
	motor_init();
	encoder_init();
	// sensor initialization
	sensor_init(0, NXT_DIGITAL_SENSOR_SONA, 0, NXT_SENSOR_SOUND);
	ev3_sensor_init(LIGHT_SENSOR_PORT, COL_COLOR);

	r = mutex_create(&mutex);
	if (0 != r) {
		logme("fail at mutex_create(), err=%d\r\n", r);
		return r;
	}

	r = task_create(NULL, start_end_task, NULL, task_getmiddlepriority(), 256, "start_end");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	r = task_create(NULL, set_state_task, NULL, task_getmiddlepriority(), 256, "state setter");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	r = task_create(NULL, set_movement_task, NULL, task_getmiddlepriority(), 256, "movement");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	ubik_comp_start();

	return 0;
}

/* -------------------------------------------------------------------------
	Task Definitions
 ------------------------------------------------------------------------- */

// task for start end checking
static void start_end_task(void *arg) {
	glcd_clear();

	while(true) {
		int sound_volume = sensor_get(SOUND_SENSOR_PORT);
		printf("%d \n\r", sound_volume);

		if (sound_volume < 550 && game_state == false) break;
	}

	turn_left(90);
	go_forward(DEFAULT_SPEED);
	task_sleep(1.5 * 1000);
	game_state = true;
	task_sleep(45 * 1000);
	last_10sec = true;
	task_sleep(15 * 1000);
	game_state = false;
	while (true) {
		stop();
	}
}

//////////////////////////////////////
// task for setting state			//
// 1. current_color					//
// 2. correct direction?			//
// 3. check enemy front				//
//////////////////////////////////////
static void set_state_task(void *arg) {
	while(true) {
		direction_check();
		int distance = sensor_get(SONIC_SENSOR_PORT);

		if (last_10sec || current_color == 4) {
			enemy_detect = false;
		}
		if (!last_10sec && current_color < 4){
			if (distance < 50) {
				enemy_detect = true;
			} else {
				enemy_detect = false;
			}
		}
	}
}

// task for setting motor movement
static void set_movement_task(void *arg) {
	while(true) {
		if (game_state) {
			if (current_color == 6) {
				go_backward(DEFAULT_SPEED);
				task_sleep(1 * 1000);
				turn_right(10);
				if (current_color == 6) {
					turn_left(70);
				} else {
					turn_right(60);
				}
				continue;
			}

			if (current_color != 1) {
				if (direction && !enemy_detect) {
					go_forward(DEFAULT_SPEED);
				}
				if (!direction && !enemy_detect) {
					turn_random();
				}
				if (enemy_detect) {
					go_forward(MAX_SPEED);
				}
			} else {
				if (last_10sec) {
					stop();
					go_forward(DEFAULT_SPEED);
					task_sleep(0.3 * 1000);
					while (true) {
						turn_right(10);
						turn_left(10);
						if (current_color != 1) {
							stop();
							task_sleep(3 * 1000);
							go_forward(300);
							task_sleep(0.5 * 1000);
							go_backward(300);
							task_sleep(0.5 * 1000);
						}
						if (!game_state) {
							stop();
							break;
						}
					}
				} else {
					task_sleep(0.3 * 1000);
					go_forward(DEFAULT_SPEED);
					task_sleep(0.3 * 1000);
					go_backward(DEFAULT_SPEED);
					if (enemy_detect) {
						go_forward(MAX_SPEED);
					}
				}
			}
		} else {

		}
	}
}

/* -------------------------------------------------------------------------
	Function Definitions
 ------------------------------------------------------------------------- */
void turn_left(int degree) {
	int degree_diff;
	int coefficient = 2.9;

	encoder_reset(MOTOR_R);
	encoder_reset(MOTOR_L);

	do {
		int r_degree = encoder_get(MOTOR_R);
		int l_degree = encoder_get(MOTOR_L);

		degree_diff = l_degree - r_degree;

		motor_set(MOTOR_R, -ROTATION_SPEED);
		motor_set(MOTOR_L, ROTATION_SPEED);

	} while (degree_diff < degree * coefficient);
}

void turn_right(int degree) {
	int degree_diff;
	int coefficient = 2.9;

	encoder_reset(MOTOR_R);
	encoder_reset(MOTOR_L);

	do {
		int r_degree = encoder_get(MOTOR_R);
		int l_degree = encoder_get(MOTOR_L);

		degree_diff = r_degree - l_degree;

		motor_set(MOTOR_R, ROTATION_SPEED);
		motor_set(MOTOR_L, -ROTATION_SPEED);
	} while (degree_diff < degree * coefficient);
}

void turn_random(void) {
	srand(2015112182);
	int random_degree;
	random_degree = !last_10sec ? (rand() % 125) + 50 : (rand() % 50) + 120;
	int random_direction = rand() % 2;

	if (direction) {
		task_sleep(0.5 * 1000);
		return;
	}

	if (random_direction == 1) {
		turn_right(random_degree);
	} else {
		turn_left(random_degree);
	}
}

void go_forward(int speed) {
	motor_set(MOTOR_R, -speed);
	motor_set(MOTOR_L, -speed);
}

void go_backward(int speed) {
	motor_set(MOTOR_R, speed);
	motor_set(MOTOR_L, speed);
}

void stop(void) {
	motor_set(MOTOR_R, 0);
	motor_set(MOTOR_L, 0);
}

void direction_check(void) {
	int former = current_color;
	current_color = ev3_sensor_get(LIGHT_SENSOR_PORT);
	if (current_color - former > 0) {
		direction = false;
	} else if (current_color - former < 0){
		direction = true;
	}
}
