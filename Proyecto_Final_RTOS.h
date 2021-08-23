/*
 * Proyecto_Final_RTOS.h
 *
 *  Created on: 21 ago. 2021
 *      Author: Cesar
 */

#ifndef PROYECTO_FINAL_RTOS_H_
#define PROYECTO_FINAL_RTOS_H_


#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"

/* TODO: insert other include files here. */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"
#include "queue.h"

/* TODO: insert other definitions and declarations here. */

#define Stack 200
#define NOT NULL
#define Alarm_Hours    1u
#define Alarm_Minutes 28u
#define Alarm_Seconds 33u
#define Set_Hours	   1u
#define Set_Minutes	  27u
#define Set_Seconds	   5u
#define SECONDS_TASK_BIT ( 1UL << 0UL ) /* Event bit 0 */
#define MINUTES_TASK_BIT ( 1UL << 1UL ) /* Event bit 0 */
#define HOURS_TASK_BIT ( 1UL << 2UL ) /* Event bit 0 */
#define HOURS_MAX     24u
#define MINUTES_MAX   60u
#define SECONDS_MAX   60u



typedef struct {
	/**** Dates alarm ****/
	uint8_t second;
	uint8_t minute;
	uint8_t hour;

	/**** Set Time  ****/
	uint8_t set_second;
	uint8_t set_minute;
	uint8_t set_hour;

	/* Event Group*/
	EventGroupHandle_t xEventGroup;

	/************ Semaphores *********/
	SemaphoreHandle_t minutes_semaphore;
	SemaphoreHandle_t hours_semaphore;

}Init;





/************ Declaration of functions *********/

void Set_Time(void *args); // uint8_t *3

/************ The tasks to be created. *********/
static void seconds_task (void *args);
static void minutes_task (void *args);
static void hours_task   (void *args);
static void alarm_task   (void *args);




/************ Coding functions *********/


/************ Coding tasks *********/
static void seconds_task (void *args){

	Init* Init_Config = (Init*) args;
	uint8_t seconds = Init_Config->set_second;
	TickType_t xLastWakeTime;
	const TickType_t xDelay1ms = pdMS_TO_TICKS(1000);
	xLastWakeTime = xTaskGetTickCount();


	for (;;) {


		if(Init_Config->second == seconds){
			//PRINTF("Alarma !!!");
			xEventGroupSetBits(Init_Config->xEventGroup, SECONDS_TASK_BIT);
		}
		seconds++;
		PRINTF("Task Running seconds %d \n",seconds);
		if(SECONDS_MAX <= seconds)
		{
			seconds = 0;
			PRINTF("Reset seconds %d\n",seconds);
			xSemaphoreGive(Init_Config->minutes_semaphore);
		}
		vTaskDelayUntil(&xLastWakeTime,xDelay1ms);
	}

}

static void minutes_task (void *args){

	Init* Init_Config = (Init*) args;
	uint8_t minutes = Init_Config->set_minute;

	for(;;){

		if(Init_Config->minute == minutes){
			//PRINTF("Alarma !!!\n");
			xEventGroupSetBits(Init_Config->xEventGroup, MINUTES_TASK_BIT);
		}
		xSemaphoreTake(Init_Config->minutes_semaphore,portMAX_DELAY);
		minutes++;
		PRINTF("Task Running minutes %d \n",minutes);
		if(SECONDS_MAX <= minutes)
		{
			minutes = 0;
			PRINTF("Reset seconds %d\n",minutes);
			xSemaphoreGive(Init_Config->hours_semaphore);
		}
	}
}

static void hours_task   (void *args){

	Init* Init_Config = (Init*) args;
	uint8_t hours = Init_Config->set_hour;

	for(;;){

		if(Init_Config->hour == hours){
			//PRINTF("Alarma !!!\n");
			xEventGroupSetBits(Init_Config->xEventGroup, HOURS_TASK_BIT);
		}
		xSemaphoreTake(Init_Config->hours_semaphore,portMAX_DELAY);
		hours++;
		PRINTF("Task Running minutes %d \n",hours);
		if(SECONDS_MAX <= hours)
		{
			hours = 0;
			PRINTF("Reset seconds %d\n",hours);
		}
	}
}

static void alarm_task   (void *args){

	Init* Init_Config = (Init*) args;
	const EventBits_t xBitsToWaitFor = (SECONDS_TASK_BIT| MINUTES_TASK_BIT| HOURS_TASK_BIT);
	EventBits_t xEventGroupValue;

	for(;;){
		xEventGroupValue = xEventGroupWaitBits(Init_Config->xEventGroup, xBitsToWaitFor, pdTRUE,pdTRUE, portMAX_DELAY);
		if(0 != xEventGroupValue){
			PRINTF("Alarm !!!\n");
		}
	}
}

#endif /* PROYECTO_FINAL_RTOS_H_ */
