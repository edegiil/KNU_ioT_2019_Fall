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

// custom library header file include
//#include "../../lib_default/itf/lib_default.h"

// user header file include

/* -------------------------------------------------------------------------
	Global variables
 ------------------------------------------------------------------------- */
volatile static int number = 0;

/* -------------------------------------------------------------------------
	Prototypes
 ------------------------------------------------------------------------- */
static void addfunc(void* arg);
static void subfunc(void* arg);
static void printfunc(void* arg);

static void task1_send(void* arg);
static void task2_recv(void* arg);
static void task3_recv(void* arg);

task_pt task_handle_add;
task_pt task_handle_sub;
task_pt task_handle_print;

static mutex_pt g_mutex = NULL;
static msgq_pt _g_msgq = NULL;
/* -------------------------------------------------------------------------
	Function Definitions
 ------------------------------------------------------------------------- */
int usrmain(int argc, char * argv[]) {
	int r;
	task_pt task_a[3];

	printf("\n\n\n\r");
	printf("================================================================================\n\r");
	printf("exe_ubinos_test (build time: %s %s)\n\r", __TIME__, __DATE__);
	printf("================================================================================\n\r");

//	r = task_create(&task_handle_add, addfunc, NULL, task_getmiddlepriority() + 1, 256, "ADD_Num");
//	if (0 != r) {
//		logme("fail at task_create\r\n");
//	}
//
//	r = task_create(&task_handle_sub, subfunc, NULL, task_getmiddlepriority() + 1, 256, "SUB_Num");
//	if (0 != r) {
//		logme("fail at task_create\r\n");
//	}
//
//	r = task_create(&task_handle_print, printfunc, NULL, task_getmiddlepriority(), 256, "PRINT_Num");
//	if (0 != r) {
//		logme("fail at task_create\r\n");
//	}
//
//	r = mutex_create(&g_mutex);

	r = msgq_create(&_g_msgq, 2, 10);
	if (0 != r) {
		logme("fail at msgq_create\r\n, err=%d\r\n", r);
		return r;
	}


	r = task_create(&task_a[0], task1_send, NULL, task_getmiddlepriority(), 0, "task 1");
	if (0 != r) {
		logme("fail at task_create\r\n, err=%d\r\n", r);
		goto fail;
	}

	r = task_create(&task_a[1], task2_recv, NULL, task_getmiddlepriority(), 0, "task 2");
	if (0 != r) {
		logme("fail at task_create\r\n, err=%d\r\n", r);
		goto fail;
	}

	r = task_create(&task_a[2], task3_recv, NULL, task_getmiddlepriority(), 0, "task 3");
	if (0 != r) {
		logme("fail at task_create\r\n, err=%d\r\n", r);
		goto fail;
	}

	ubik_comp_start();

	return 0;

	fail:
		msgq_delete(&_g_msgq);
		return r;
}

static void addfunc(void* arg) {
	for(int i = 0; i < 1000; i++) {
		mutex_lock(g_mutex);
		int temp = number;
		temp++;
		bsp_busywait(10);
		number = temp;
		mutex_unlock(g_mutex);
	}
}

static void subfunc(void* arg) {
	for(int i = 0; i < 1000; i++) {
		mutex_lock(g_mutex);
		int temp = number;
		temp--;
		bsp_busywait(10);
		number = temp;
		mutex_unlock(g_mutex);
	}
}

static void printfunc(void* arg) {
	mutex_delete(&g_mutex);
	glcd_init();
	glcd_clear();

	for(;;) {
		glcdGotoChar(0, 0);
		glcd_printf("number : %d\n", number);
		printf("number : %d\r\n", number);
	}
}


static void task1_send(void* arg) {
	unsigned int i;
	unsigned char buf[2];

	for (i = 0; i < 2; i++) {
		buf[i] = i;
	}

	for (i=0; i < 100; i++) {
		bsp_busywait((unsigned int) rand() % 100 * bsp_getbusywaitcountperms());
		printf("task 1 has produced one\r\n");

		msgq_send(_g_msgq, buf);
	}
}

static void task2_recv(void* arg) {
	unsigned int i;
	unsigned int j;
	unsigned char buf[2];

	for (i = 0; i < 100 / 2; i++) {
		msgq_receive(_g_msgq, buf);

		for (j = 0; j < 2; j++) {
			if (j != buf[j]) {
				printf("task 2: received message is wrong\r\n");
				break;
			}
		}

		printf("task 2 consumes one\r\n");
		bsp_busywait((unsigned int)rand() % 100 * bsp_getbusywaitcountperms());
	}
}

static void task3_recv(void* arg) {
	unsigned int i;
	unsigned int j;
	unsigned char buf[2];

	for (i = 0; i < 100 / 2; i++) {
		msgq_receive(_g_msgq, buf);

		for (j = 0; j < 2; j++) {
			if (j != buf[j]) {
				printf("task 3: received message is wrong\r\n");
				break;
			}
		}

		printf("task 3 consumes one\r\n");
		bsp_busywait((unsigned int)rand() % 100 * bsp_getbusywaitcountperms());
	}
}
