/*
 * task.c
 *
 * Created: 2020/12/7 15:42:33
 *  Author: Kennys
 */ 

/*--------------------Libraries---------------------------*/
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/sleep.h>

/* Scheduler include files. */
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"
#include "../FreeRTOS/queue.h"
#include "../FreeRTOS/semphr.h"
/* TASK include file. */
#include "../lib/uart.h"
#include "../include/MahonyIMU.h"
#include "../include/MPU6050.h"
/* system time include file. */
#include "time.h"

extern float AccData[3];
extern float GyroData[3];
extern float Angle[3];
extern char MyString[10];

void vMahonyTaskFunction( void *pvParameters )
{
	for( ;; )
	{
		TickType_t xLastWakeTimeMahony;
		const TickType_t xPeriodFrequencyMahony = 10;// 15ms per tick  15ms*50 = 150

		xLastWakeTimeMahony = xTaskGetTickCount();

		for( ;; )
		{
			vTaskDelayUntil( &xLastWakeTimeMahony, xPeriodFrequencyMahony );
			MahonyAHRSupdateIMU(GyroData[0],GyroData[1],GyroData[2],AccData[0],AccData[1],AccData[2]);
			q2Angle(Angle);
			sprintf(MyString,"Angle x:%.3f\n", Angle[0]);
			UART_putstring(MyString);
		}
	}
	vTaskDelete( NULL );
}
void vMPU6050TaskFunction( void *pvParameters )
{
	for( ;; )
	{
		TickType_t xLastWakeTimeMPU;
		const TickType_t xPeriodFrequencyMPU = 8;// 10ms per tick  15ms*80 = 120
		
		xLastWakeTimeMPU = xTaskGetTickCount();

		for( ;; )
		{
			vTaskDelayUntil( &xLastWakeTimeMPU, xPeriodFrequencyMPU );
			MPU_read(AccData,GyroData);
		}
	}
	vTaskDelete( NULL );
}

// Task C for control
void vCTaskFunction( void *pvParameters )
{
	for( ;; )
	{
		TickType_t xLastWakeTimeC;
		const TickType_t xLightupDelayC = 30;		// 15ms*30 = 450
		const TickType_t xPeriodFrequencyC = 100;// 15ms per tick  15ms*93 = 1395
		
		xLastWakeTimeC = xTaskGetTickCount();

		for( ;; )
		{
			vTaskDelayUntil( &xLastWakeTimeC, xPeriodFrequencyC );
			//led on
			//sprintf(MyString,"TASKC On\n");
			//UART_putstring(MyString);
			PORTB |= (1<<PORTB2);
			vTaskDelay(xLightupDelayC);
			PORTB &= ~(1<<PORTB2);
			//sprintf(MyString,"TASKC Off\n");
			//UART_putstring(MyString);

			
		}
	}
	vTaskDelete( NULL );
}
//
void MytaskCreate(void)
{
	/* Create tasks and make some magic*/

	xTaskCreate( vMahonyTaskFunction,"TASKA",256,NULL,4,NULL);
	xTaskCreate( vMPU6050TaskFunction,"TASKB",256,NULL,3,NULL);
	xTaskCreate( vCTaskFunction,"TASKC",256,NULL,2,NULL);

}
