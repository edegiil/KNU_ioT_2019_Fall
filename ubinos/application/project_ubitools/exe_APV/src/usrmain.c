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
#include <math.h>
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
//#include "../../lib_default/itf/lib_default.h"
#include "lib_bluetooth/itf/BT_Module_Interface.h"
#include "lib_bluetooth/itf/lib_BT.h"

// user header file include
#include "define.h"

/* -------------------------------------------------------------------------
	Global variables
 ------------------------------------------------------------------------- */
static bool stranger = false;
static bool door_open = false;
static int current_password = 0;
static int direction = 0;
static bool time_to_input = false;
static int message = 0;
static bool send = false;
static int distance = 255;

uint8_t print_packet[DATA_SEND_BUFFER_SIZE] = {0,};
msgq_pt BT_user_event_queue;
mutex_pt _g_mutex;

/* -------------------------------------------------------------------------
	Prototypes
 ------------------------------------------------------------------------- */
static void stranger_detect(void *arg);
static void turret_lock(void * arg);
static void input_password(void *arg);
static void encode_password(void *arg);
static void lock_door(void *arg);
static void check_vibration(void *arg);
static void BT_task(void *arg);
static void test(void *arg);

void turn_random(int motor);
void turn(int motor, int degree, int direction);
void lock(void);
void open(void);
void send_msg(int type);

/* -------------------------------------------------------------------------
	Main Functions
 ------------------------------------------------------------------------- */
int usrmain(int argc, char * argv[]) {
	int r;

	printf("\n\n\n\r");
	printf("================================================================================\n\r");
	printf("exe_APV (build time: %s %s)\n\r", __TIME__, __DATE__);
	printf("================================================================================\n\r");

	// sensor init
	glcd_init();
	motor_init();
	encoder_init();
	sensor_init(EV3_IMU_SENSOR, 0, NXT_DIGITAL_SENSOR_SONA, 0);
	ev3_sensor_init(LIGHT_SENSOR, COL_COLOR);
	modeSelectIMU(IMU_ACC_ONLY);

	mutex_create(&_g_mutex);

//	r = task_create(NULL, test, NULL, task_gethighestpriority(), 256, "test");
//	if (0 != r) {
//		logme("fail at task_create\r\n");
//	}
	r = task_create(NULL, stranger_detect, NULL, task_getmiddlepriority(), 256, "stranger_detect");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}
	r = task_create(NULL, turret_lock, NULL, task_getmiddlepriority(), 256, "turret_lock");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}
	r = task_create(NULL, input_password, NULL, task_getmiddlepriority(), 256, "input_password");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}
	r = task_create(NULL, encode_password, NULL, task_getmiddlepriority(), 256, "encode_password");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}
	r = task_create(NULL, lock_door, NULL, task_getmiddlepriority(), 256, "lock_door");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}
	r = task_create(NULL, check_vibration, NULL, task_getmiddlepriority(), 256, "check_vibration");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}
	r = task_create(NULL, BT_task, NULL, task_getmiddlepriority() + 1, 512, "bluetooth_task");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	r = msgq_create(&BT_user_event_queue, sizeof(BT_Evt_t), MAIN_MSGQ_MAX_COUNT);
	if (0 != r) {
		logme("fail at msgq_create\r\n");
	}

	ubik_comp_start();

	return 0;
}

/* -------------------------------------------------------------------------
	Tasks
 ------------------------------------------------------------------------- */

static void test(void *arg) {
	while(1) {
		glcd_printf("%d\n", sensor_get(SONIC_SENSOR));

		task_sleep(500);
	}
}

static void stranger_detect(void *arg) {
	while (true) {
		distance = sensor_get(SONIC_SENSOR);
		task_sleep(300);
	}
}

static void turret_lock(void *arg) {
	while (true) {
		while(distance > 80) {
			distance = sensor_get(SONIC_SENSOR);
			stranger = false;
			turn_random(AIM_MOTOR);
		}
		motor_set(AIM_MOTOR, 0);

		stranger = true;

		task_sleep(1000);
	}
}

static void input_password(void *arg) {
	int password[4] = { 1, 2, 1, 2 };

	while (true) {
		int chance_left = 3;
		bool check = true;

		if (stranger && !door_open) {
			start:

			printf("start password input\r\n");
			turn(ENCODER_MOTOR, 75, 1);

			time_to_input = true;
			for (int i = 1; i < 5; i++) {
				encoder_reset(ENCODER_MOTOR);
				task_sleep(3000);

				if (password[i - 1] == current_password) {
					check *= true;
				} else {
					check *= false;
				}
			}

			time_to_input = false;

			if (!check) {
				chance_left--;

				if (chance_left < 1) {
					turn(TURRET_MOTOR, 15, 1);
					glcd_clear();
//					printf("shoot!\n");
				} else {
					check = true;
//					printf("try again\n");
					glcd_clear();
					goto start;
				}
			} else {
				open();
				send_msg(OPENED);
//				printf("open door\n");
				glcd_clear();
				door_open = true;
			}
		}
	}
}

static void encode_password(void *arg) {
	while (true) {
		int value = encoder_get(ENCODER_MOTOR);
		int coefficient = 20;

		current_password = (int)floor(abs(value / coefficient));

		if (current_password > 9) current_password = 9;

		if (time_to_input) {
			glcdGotoChar(0, 0);
			glcd_printf("PW : %d\n", current_password);
		}

		task_sleep(100);
	}
}

static void lock_door(void *arg) {
	while (true) {
		int current_color = ev3_sensor_get(LIGHT_SENSOR);

		if (door_open && current_color == 5) {
			lock();
			door_open = false;
			send_msg(LOCKED);
			printf("locked\r\n");
		}
	}
	task_sleep(100);
}

static void check_vibration(void *arg) {
	int acc_array[3];
	int checker[3] = { 0, };

	getACC(ACC_SENSOR, acc_array);
	task_sleep(100);
	getACC(ACC_SENSOR, acc_array);
	while (true) {
		checker[0] = acc_array[0];
		checker[1] = acc_array[1];
		checker[2] = acc_array[2];

		task_sleep(500);
		getACC(ACC_SENSOR, acc_array);

		int x_diff = abs(acc_array[0] - checker[0]);
		int y_diff = abs(acc_array[1] - checker[1]);
		int z_diff = abs(acc_array[2] - checker[2]);

		if (x_diff > 100 || y_diff > 100 || z_diff > 100) {
			send_msg(ATTACKED);
			printf("attacked\r\n");
		}
		task_sleep(100);
	}
}

static void BT_task(void *arg) {
	int r = 0;
	module_id_st target_BT_ID;
	BT_Evt_t BT_usr_msgRXBuffer = { 0, };

	target_BT_ID.module_id[0] = BLE_MODULE_ID_0;
	target_BT_ID.module_id[1] = BLE_MODULE_ID_1;
	target_BT_ID.module_id[2] = BLE_MODULE_ID_2;
	target_BT_ID.module_id[3] = BLE_MODULE_ID_3;

	BT_INIT(INIT_ROLE_PERIPHERAL, target_BT_ID, BT_user_event_queue);

	BT_ADV_START();

	for (;;) {
		r = msgq_receive(BT_user_event_queue, (unsigned char *) &BT_usr_msgRXBuffer);
		if (0 != r) {
			logme("fail at msgq\r\n");
		} else {
			switch(BT_usr_msgRXBuffer.status) {
			case BT_EVT_CONNECTED:
				break;
			}
		}

		task_sleep(100);
	}
}

/* -------------------------------------------------------------------------
	Functions Definitions
 ------------------------------------------------------------------------- */
void turn_random(int motor) {
	direction = !direction;

	turn(motor, 5, direction);
}

void turn(int motor, int degree, int direction) {
	double coefficient = 5;
	int value = 0;

	encoder_reset(motor);
	int time = 0;

	if (motor == AIM_MOTOR) {
		while (abs(value) < degree * coefficient && distance > 80) {
			value = encoder_get(motor);

			int speed = direction ? 100 : -100;

			if (motor == TURRET_MOTOR) {
				speed = 450;
			}

			motor_set(motor, speed);

			if (time > 5) break;

			task_sleep(1000);
			time++;
		}
	} else {
		while (abs(value) < degree * coefficient) {
			value = encoder_get(motor);

			int speed = direction ? 100 : -100;

			if (motor == TURRET_MOTOR) {
				speed = 450;
			}

			motor_set(motor, speed);

			if (time > 5) break;

			task_sleep(1000);
			time++;
		}
	}
	motor_set(motor, 0);
}

void lock(void) {
	turn(LOCKER_MOTOR, 20, 0);
}

void open(void) {
	turn(LOCKER_MOTOR, 10, 1);
}

void send_msg(int type) {
	message = type;
	send = true;

	print_packet[0] = message;
	BT_DATA_SEND(INIT_ROLE_PERIPHERAL, print_packet);

	send = false;
}
