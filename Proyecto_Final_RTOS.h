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

#define Stack 200						/* Value Stack from tasks */
#define Alarm_Hours    1u				/* Time value in the alarm Hours*/
#define Alarm_Minutes 27u				/* Time value in the alarm Minutes */
#define Alarm_Seconds 33u				/* Time value in the alarm  Seconds*/
#define Set_Hours	   1u				/* Initial clock value Hours */
#define Set_Minutes	  27u				/* Initial clock value Minutes */
#define Set_Seconds	   5u				/* Initial clock value Seconds */
#define SECONDS_TASK_BIT ( 1UL << 0UL ) /* Event bit 0 */
#define MINUTES_TASK_BIT ( 1UL << 1UL ) /* Event bit 1 */
#define HOURS_TASK_BIT ( 1UL << 2UL )   /* Event bit 2 */
#define HOURS_MAX     24u				/* Limit value */
#define MINUTES_MAX   60u				/* Limit value */
#define SECONDS_MAX   60u				/* Limit value */
#define SIZE_QUEUE     5u				/* Queue size value */



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

typedef enum {
	seconds_type,
	minutes_type,
	hours_type
}time_types_t;

typedef struct{
	time_types_t time_type;
	uint8_t Value;
}time_msg_t;

static QueueHandle_t mailbox;


/************ Declaration of functions *********/

void Set_Time(void *args); // uint8_t *3

/************ The tasks to be created. *********/
static void seconds_task (void *args);
static void minutes_task (void *args);
static void hours_task   (void *args);
static void alarm_task   (void *args);
static void print_task   (void *args);




/************ Coding functions *********/


/************ Coding tasks *********/
static void seconds_task (void *args){

	Init* Init_Config = (Init*) args;
	TickType_t xLastWakeTime;
	const TickType_t xDelay1ms = pdMS_TO_TICKS(200);
	xLastWakeTime = xTaskGetTickCount();

	time_msg_t Time_Second;
	time_msg_t *Send;

	for (;;) {


		if(Init_Config->second == Init_Config->set_second){
			//PRINTF("Alarma !!!");
			xEventGroupSetBits(Init_Config->xEventGroup, SECONDS_TASK_BIT);
		}
		Init_Config->set_second++;
		Time_Second.time_type = seconds_type;
		Time_Second.Value     = Init_Config->set_second;
		Send = pvPortMalloc(sizeof(time_msg_t));
		*Send = Time_Second;
		xQueueSend(mailbox,&Send,portMAX_DELAY);
		//PRINTF("Task Running seconds %d \n",Init_Config->set_second);
		if(SECONDS_MAX <= Init_Config->set_second)
		{
			Init_Config->set_second = 0;
			PRINTF("Reset seconds %d\n",Init_Config->set_second);
			xSemaphoreGive(Init_Config->minutes_semaphore);
		}
		vTaskDelayUntil(&xLastWakeTime,xDelay1ms);
	}

}

static void minutes_task (void *args){

	Init* Init_Config = (Init*) args;
	time_msg_t Time_minutes;
	time_msg_t *Send;

	for(;;){

		if(Init_Config->minute == Init_Config->set_minute){
			//PRINTF("Alarma !!!\n");
			xEventGroupClearBits(Init_Config->xEventGroup,SECONDS_TASK_BIT);
			xEventGroupSetBits(Init_Config->xEventGroup, MINUTES_TASK_BIT);
		}
		xSemaphoreTake(Init_Config->minutes_semaphore,portMAX_DELAY);
		Init_Config->set_minute++;
		Time_minutes.time_type = minutes_type;
		Time_minutes.Value     = Init_Config->set_minute;
		Send = pvPortMalloc(sizeof(time_msg_t));
		*Send = Time_minutes;
		xQueueSend(mailbox,&Send,portMAX_DELAY);
		//PRINTF("Task Running minutes %d \n",Init_Config->set_minute);
		if(SECONDS_MAX <= Init_Config->set_minute)
		{
			Init_Config->set_minute = 0;
			PRINTF("Reset seconds %d\n",Init_Config->set_minute);
			xSemaphoreGive(Init_Config->hours_semaphore);
		}
	}
}

static void hours_task   (void *args){

	Init* Init_Config = (Init*) args;
	time_msg_t Time_hours;
	time_msg_t *Send;
	for(;;){

		if(Init_Config->hour == Init_Config->set_hour){
			//PRINTF("Alarma !!!\n");
			xEventGroupClearBits(Init_Config->xEventGroup,MINUTES_TASK_BIT);
			xEventGroupSetBits(Init_Config->xEventGroup, HOURS_TASK_BIT);
		}
		xSemaphoreTake(Init_Config->hours_semaphore,portMAX_DELAY);
		Init_Config->set_hour++;
		Time_hours.time_type = hours_type;
		Time_hours.Value     = Init_Config->set_hour;
		Send = pvPortMalloc(sizeof(time_msg_t));
		*Send = Time_hours;
		xQueueSend(mailbox,&Send,portMAX_DELAY);
		//PRINTF("Task Running minutes %d \n",Init_Config->set_hour);
		if(SECONDS_MAX <= Init_Config->set_hour)
		{
			Init_Config->set_hour = 0;
			PRINTF("Reset seconds %d\n",Init_Config->set_hour);
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

static void print_task   (void *args){

	time_msg_t *Recived;
	for (;;) {
		xQueueReceive(mailbox, &Recived, portMAX_DELAY);

		if(Recived->time_type == seconds_type ){
			PRINTF("Value seconds %i\n",Recived->Value);
			vPortFree(Recived);
		}
		if(Recived->time_type == minutes_type){
			PRINTF("Value minutes %i\n",Recived->Value);
			vPortFree(Recived);
		}
		if(Recived->time_type == hours_type){
			PRINTF("Value hours %i\n",Recived->Value);
			vPortFree(Recived);
		}
	}
}
#endif /* PROYECTO_FINAL_RTOS_H_ */
