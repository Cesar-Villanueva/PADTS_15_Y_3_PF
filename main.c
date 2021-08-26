/*
 * main.c
 *
 *  Created on: 21 ago. 2021
 *      Author: Cesar
 */
#include "Proyecto_Final_RTOS.h"


int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif


    static Init Init_config;
    // Init struct

    /********** Initializing Alarm Parameters*******/
    Init_config.hour   = Alarm_Hours;
    Init_config.minute = Alarm_Minutes;
    Init_config.second = Alarm_Seconds;

    /********** Initializing Time Parameters*******/
    Init_config.set_hour   = Set_Hours;
    Init_config.set_minute = Set_Minutes;
    Init_config.set_second = Set_Seconds;



    /* Before an event group can be used it must first be created. */
    Init_config.xEventGroup = xEventGroupCreate();

    /************ Semaphore to be created *********/

    LCD = xSemaphoreCreateBinary();
    xSemaphoreGive(LCD);
    Init_config.minutes_semaphore = xSemaphoreCreateBinary();
    Init_config.hours_semaphore   = xSemaphoreCreateBinary();

    /************ Queues to be created *********/
    mailbox = xQueueCreate(SIZE_QUEUE,sizeof(time_msg_t*));
    vQueueAddToRegistry(mailbox, "time_queue");

    /************ Mutex to be created *********/
    Mutex = xSemaphoreCreateMutex();




    /************ The tasks to be created. *********/
    xTaskCreate(seconds_task, "Function seconds", Stack, (void*) &Init_config, configMAX_PRIORITIES -3, NULL);
    xTaskCreate(minutes_task, "Function Minutes", Stack, (void*) &Init_config, configMAX_PRIORITIES -2, NULL);
    xTaskCreate(hours_task,   "Function Hours"  , Stack, (void*) &Init_config, configMAX_PRIORITIES -1, NULL);
    xTaskCreate(alarm_task,   "Function Alarm"  , Stack, (void*) &Init_config, configMAX_PRIORITIES -4, NULL);
    xTaskCreate(print_task,   "Function print"  , Stack,                NULL , configMAX_PRIORITIES -4, NULL);
    xTaskCreate(LCD_init  ,   "Function LCD"    , Stack, (void*) &Init_config , configMAX_PRIORITIES -1, NULL);


    /************ Start the calendarizer *********/
    /* Start the scheduler so the created tasks start executing. */
    vTaskStartScheduler();

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
