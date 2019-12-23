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

// custom library header file include
//#include "../../lib_default/itf/lib_default.h"
#include "lib_bluetooth/itf/BT_Module_Interface.h"
#include "lib_bluetooth/itf/lib_BT.h"

// user header file include

#define BLE_MODULE_ID_0	0x01
#define BLE_MODULE_ID_1	0x02
#define BLE_MODULE_ID_2	0x03
#define BLE_MODULE_ID_3	0x58

#define R_MOTOR_PORT	0

/* -------------------------------------------------------------------------
	Global variables
 ------------------------------------------------------------------------- */
uint8_t print_packet[DATA_SEND_BUFFER_SIZE] = {0,};
int motorset = 0;

// Main Task Message Queue
msgq_pt BT_user_event_queue;
mutex_pt _g_mutex;

/* -------------------------------------------------------------------------
	Prototypes
 ------------------------------------------------------------------------- */
static void BT_peripheraltask(void * arg);
static void lcd_outputtask(void);
static void BT_centraltask(void *arg);

/* -------------------------------------------------------------------------
	Function Definitions
 ------------------------------------------------------------------------- */
int usrmain(int argc, char * argv[]) {
	int r;

	printf("\n\n\n\r");
	printf("================================================================================\n\r");
	printf("exe_week7 (build time: %s %s)\n\r", __TIME__, __DATE__);
	printf("================================================================================\n\r");

	glcd_init();
	motor_init();
	mutex_create(&_g_mutex);

	r = task_create(NULL, lcd_outputtask, NULL, task_getmiddlepriority(), 256, "lcd_output_task");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}
//	r = task_create(NULL, BT_peripheraltask, NULL, task_getmiddlepriority(), 512, "bluetooth_task");
//	if (0 != r) {
//		logme("fail at task_create\r\n");
//	}
	r = task_create(NULL, BT_centraltask, NULL, task_getmiddlepriority(), 512, "bluetooth_task");
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

static void BT_peripheraltask(void *arg) {
	int r = 0;
	module_id_st BT_ID;
	BT_Evt_t BT_usr_msgRXBuffer = { 0, };

	BT_ID.module_id[0] = BLE_MODULE_ID_0;
	BT_ID.module_id[1] = BLE_MODULE_ID_1;
	BT_ID.module_id[2] = BLE_MODULE_ID_2;
	BT_ID.module_id[3] = BLE_MODULE_ID_3;

	task_sleep(200);

	BT_INIT(INIT_ROLE_PERIPHERAL, BT_ID, BT_user_event_queue);

	BT_ADV_START();

	for (;;) {
		r = msgq_receive(BT_user_event_queue, (unsigned char*) &BT_usr_msgRXBuffer);
		if (0 != r) {
			logme("fail at message receive\r\n");
		} else {
			switch (BT_usr_msgRXBuffer.status) {
			case BT_EVT_PE_DATA_READ: {
				mutex_lock(_g_mutex);
//				motorset = (int)((BT_usr_msgRXBuffer.msg[1] << 8) | (BT_usr_msgRXBuffer.msg[0]));

				for (int i = 0; i < 20; i++) {
					print_packet[i] = BT_usr_msgRXBuffer.msg[i];
				}
				mutex_unlock(_g_mutex);

//				motor_set(R_MOTOR_PORT, motorset);
//				bsp_busywaitms(1000);
//				motor_set(R_MOTOR_PORT, 0);

				BT_DATA_SEND(INIT_ROLE_PERIPHERAL, print_packet);
				task_sleep(500);
			}
			break;

			case BT_EVT_DISCONNECTED:
				break;

			case BT_EVT_CONNECTED:
				break;
			}
		}
	}
}

static void lcd_outputtask(void) {
	task_sleep(300);

	while (1) {
		mutex_lock(_g_mutex);

		glcdGotoChar(1, 2);
		glcd_printf("%d", print_packet[0]);

		mutex_unlock(_g_mutex);

		task_sleep(200);
	}
}

static void BT_centraltask(void *arg) {
	int r = 0;
	module_id_st target_BT_ID;
	BT_Evt_t BT_usr_msgRXBuffer = { 0, };

	target_BT_ID.module_id[0] = BLE_MODULE_ID_0;
	target_BT_ID.module_id[1] = BLE_MODULE_ID_1;
	target_BT_ID.module_id[2] = BLE_MODULE_ID_2;
	target_BT_ID.module_id[3] = BLE_MODULE_ID_3;

	uint8_t BT_msg[DATA_SEND_BUFFER_SIZE] = {0x01};

	BT_INIT(INIT_ROLE_CENTRAL, target_BT_ID, BT_user_event_queue);

	BT_SCAN_START();

	BT_CONNECT(target_BT_ID);

	task_sleep(500);

	BT_DATA_SEND(INIT_ROLE_CENTRAL, BT_msg);

	for (;;) {
		r = msgq_receive(BT_user_event_queue, (unsigned char*) &BT_usr_msgRXBuffer);
		if (0 != r) {
			logme("fail at message receive\r\n");
		} else {
			switch (BT_usr_msgRXBuffer.status) {
			case BT_EVT_CE_DATA_READ: {
				mutex_lock(_g_mutex);

				for (int i = 0; i < 20; i++) {
					print_packet[i] = BT_usr_msgRXBuffer.msg[i];

					if (print_packet[0] >= 20) {
						mutex_unlock(_g_mutex);

						BT_DISCONNECT();
					} else {
						print_packet[0] = print_packet[0] + 1;
						mutex_unlock(_g_mutex);

						BT_DATA_SEND(INIT_ROLE_CENTRAL, print_packet);
						task_sleep(500);
					}
				}
			}
			break;

			case BT_EVT_DISCONNECTED:
				break;

			case BT_EVT_CONNECTED:
				break;
			}
		}
	}
}
