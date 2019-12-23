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

#include "lib_can/itf/lib_can.h"
#include "lib_sensor/itf/lib_sensor.h"
// custom library header file include
//#include "../../lib_default/itf/lib_default.h"

// user header file include

/* -------------------------------------------------------------------------
	Global variables
 ------------------------------------------------------------------------- */
#define CAN_DEV_ID	0
static char _g_str_lcd[9] = "STOP\0";

int gyroarr[3];

/* -------------------------------------------------------------------------
	Prototypes
 ------------------------------------------------------------------------- */
static void lcd_outputtask(void);
static void can_mastertask(void);
static void rootfunc(void *arg);

/* -------------------------------------------------------------------------
	Function Definitions
 ------------------------------------------------------------------------- */
int usrmain(int argc, char * argv[]) {
	int r;

	printf("\n\n\n\r");
	printf("================================================================================\n\r");
	printf("exe_week8 (build time: %s %s)\n\r", __TIME__, __DATE__);
	printf("================================================================================\n\r");

	glcd_init();

	// CAN task
	r = task_create(NULL, lcd_outputtask, NULL, task_getmiddlepriority(), 256, "output");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	r = task_create(NULL, can_mastertask, NULL, task_getmiddlepriority(), 256, "can_master");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

//	// Device Driver task
//	r = task_create(NULL, rootfunc, NULL, task_getmiddlepriority(), 256, "rootfunc");
//	if (0 != r) {
//		logme("fail at task_create\r\n");
//	}

	ubik_comp_start();

	return 0;
}

static void lcd_outputtask(void) {
	glcd_clear();

	// 1st line
	glcdGotoChar(1, 1);
	glcd_printf("CAN Master");
//	glcd_printf("CAN Slave");

	while(1) {
		glcdGotoChar(1, 2);
		glcd_printf("%s", _g_str_lcd);

		task_sleep(500);
	}
}

static void can_mastertask(void) {
	char tx_buf[8] = "master \0";
//	char tx_buf[8] = "slave \0";
	char rx_buf[9];
	uint8_t rx_length;
	int count = 0;
	CAN_PORT CAN_PORT1;
	CAN_PORT1.cbox_num = 0;

	// open the CAN device
	can_open(CAN_DEV_ID, CAN_BPS_500K);

	// open the CAN port
	can_port_open(CAN_DEV_ID, &CAN_PORT1, 1, true, 255);
	can_port_set_protocol(CAN_DEV_ID, &CAN_PORT1, CAN_PROTOCOL_2_0_A);
	can_port_set_recvid(CAN_DEV_ID, &CAN_PORT1, 0);
	can_port_set_recvidmask(CAN_DEV_ID, &CAN_PORT1, 0);

	// set the CAN port
	can_port_set(CAN_DEV_ID, &CAN_PORT1);

	task_sleep(1000);

	while(1) {
		// create transit data "MASTER.."
		tx_buf[7] = '0' + count++;

		// create transit data "SLAVE.."
		// tx_but[6] = '0' + count++;

		if(count == 10) count = 0;

		// send CAN data to the CAN slave
		can_port_send(CAN_DEV_ID, &CAN_PORT1, tx_buf, sizeof(tx_buf), 0);

		// receive CAN data from the CAN slave
		rx_length = can_port_recv(CAN_DEV_ID, &CAN_PORT1, rx_buf, 8, 0);

		if(rx_length > 0) {
			_g_str_lcd[8] = '\0';
			memcpy(_g_str_lcd, rx_buf, rx_length);
		}
		printf("%s", rx_buf);
		task_sleep(1000);
	}
}

static void rootfunc(void *arg) {
	glcd_init();

	// initialize sensor
	sensor_init(EV3_IMU_SENSOR, 0, 0, 0);

	// select sensor mode
	modeSelectIMU(0);

	while(1) {
		// get sensor data
		getGyro(0, gyroarr);

		// print sensor data
		glcdGotoChar(0, 0);
		glcd_printf("%d       %d       %d       ", gyroarr[0], gyroarr[1], gyroarr[2]);

		task_sleep(100);
	}
}
