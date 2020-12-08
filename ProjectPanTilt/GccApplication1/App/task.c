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
#include "../include/balance.h"
/* system time include file. */
#include "time.h"

extern float AccData[3];
extern float GyroData[3];
extern float Angle[3];
extern char MyString[10];
float ADC_Value;
// static TickType_t time1;
// static TickType_t time2;
// static int period;
void vMahonyTaskFunction( void *pvParameters )
{
	for( ;; )
	{
		TickType_t xLastWakeTimeMahony;
		const TickType_t xPeriodFrequencyMahony = 1;// 15ms per tick

		xLastWakeTimeMahony = xTaskGetTickCount();

		for( ;; )
		{
			vTaskDelayUntil( &xLastWakeTimeMahony, xPeriodFrequencyMahony );
// 			time1 = xTaskGetTickCount();
// 			sprintf(MyString,"time1: %i ms\n",time1);
// 			UART_putstring(MyString);
			MahonyAHRSupdateIMU(GyroData[0],GyroData[1],GyroData[2],AccData[0],AccData[1],AccData[2]);
			q2Angle(Angle);
			sprintf(MyString,"Angle x: %f ms\n",Angle[0]);
			UART_putstring(MyString);
			sprintf(MyString,"Angle y: %f ms\n",Angle[1]);
			UART_putstring(MyString);
// 			time2 = xTaskGetTickCount();
// 			sprintf(MyString,"time1: %i ms\n",time2);
// 			UART_putstring(MyString);
// 			period = (time2-time1)*15;
// 			sprintf(MyString,"Task Mahony: %i ms\n",period);
// 			UART_putstring(MyString);
		}
	}
	vTaskDelete( NULL );
}
void vMPU6050TaskFunction( void *pvParameters )
{
	for( ;; )
	{
		TickType_t xLastWakeTimeMPU;
		const TickType_t xPeriodFrequencyMPU = 1;// 15ms per tick
		
		xLastWakeTimeMPU = xTaskGetTickCount();

		for( ;; )
		{
			vTaskDelayUntil( &xLastWakeTimeMPU, xPeriodFrequencyMPU );
//			TickType_t time1 = xTaskGetTickCount();
			MPU_read(AccData,GyroData);
// 			TickType_t time2 = xTaskGetTickCount();
// 			sprintf(MyString,"Task MPU: %i ms\n",(time2-time1)*15);
// 			UART_putstring(MyString);
		}
	}
	vTaskDelete( NULL );
}

// Task C for control
void vControlTaskFunction( void *pvParameters )
{
	for( ;; )
	{
		TickType_t xLastWakeTimeControl;
		const TickType_t xPeriodFrequencyControl = 1;// 15ms per tick  15ms*93 = 1395
		
		xLastWakeTimeControl = xTaskGetTickCount();

		for( ;; )
		{
			vTaskDelayUntil( &xLastWakeTimeControl, xPeriodFrequencyControl );
			BalanceControl(Angle);
// 			sprintf(MyString,"Task Control\n");
// 			UART_putstring(MyString);
			
		}
	}
	vTaskDelete( NULL );
}
void vADCTaskFunction( void *pvParameters )
{
	for( ;; )
	{
		TickType_t xLastWakeTimeADC;
		const TickType_t xPeriodFrequencyADC = 1;// 15ms per tick  15ms*93 = 1395
		
		xLastWakeTimeADC = xTaskGetTickCount();

		for( ;; )
		{
			vTaskDelayUntil( &xLastWakeTimeADC, xPeriodFrequencyADC);
			//ADC
			ADC_Value = ADC;
			if(OCR0B>10&&OCR0B<40){
				if ((ADC_Value*5/1024)==0){
					OCR0B--;
				}
				else if ((ADC_Value*5/1024)==4){
					OCR0B++;

				}
			}
			else if (OCR0B<=10){
				OCR0B=11;
			}
			else if (OCR0B>=40){
				OCR0B=39;
			}
			sprintf(MyString,"Task ADC:%f\n",ADC_Value);
			UART_putstring(MyString);
// 			
		}
	}
	vTaskDelete( NULL );
}
//
void MytaskCreate(void)
{
	/* Create tasks and make some magic*/

	xTaskCreate( vMahonyTaskFunction,"TASKA",256,NULL,3,NULL);
	xTaskCreate( vMPU6050TaskFunction,"TASKB",256,NULL,2,NULL);
	xTaskCreate( vControlTaskFunction,"TASKC",256,NULL,1,NULL);
	xTaskCreate( vADCTaskFunction,"TASKD",256,NULL,4,NULL);
	
}
