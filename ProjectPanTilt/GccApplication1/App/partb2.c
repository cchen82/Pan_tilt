/*
#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/sleep.h>


char MyString[10];

void LED_Initialize(void)
{
	//Configure PORTB 0,1,2 Output
	DDRB |= (1<<DDB0);
	PORTB |= (1<<PORTB0);
	DDRB |= (1<<DDB1);
	PORTB |= (1<<PORTB1);
	DDRB |= (1<<DDB2);
	PORTB |= (1<<PORTB2);
}

   
void vATaskFunction( void *pvParameters )
{
	for( ;; )
	{
		TickType_t xLastWakeTimeA;
		const TickType_t xLightupDelayA = 10;		// 15ms*10 = 150
		const TickType_t xPeriodFrequencyA = 50;// 10=5ms per tick  15ms*50 = 750
 
		xLastWakeTimeA = xTaskGetTickCount();

		for( ;; )
		{
			
			vTaskDelayUntil( &xLastWakeTimeA, xPeriodFrequencyA );
			//led on
			//sprintf(MyString,"TASKA on\n");
			//UART_putstring(MyString);
			taskENTER_CRITICAL();
			PORTB |= (1<<PORTB0);

			volatile long int i = 137143;
			while(i>0)
			{i--;}

			PORTB &= ~(1<<PORTB0);
			taskEXIT_CRITICAL();
			//sprintf(MyString,"TASKA off\n");
			//UART_putstring(MyString);
		}
	}
    vTaskDelete( NULL );
}
void vBTaskFunction( void *pvParameters )
{
	for( ;; )
	{
		TickType_t xLastWakeTimeB;
		const TickType_t xLightupDelayB = 20;		// 15ms*20 = 300
		const TickType_t xPeriodFrequencyB = 80;// 15ms per tick  15ms*80 = 1200
		
		xLastWakeTimeB = xTaskGetTickCount();

		for( ;; )
		{
			vTaskDelayUntil( &xLastWakeTimeB, xPeriodFrequencyB );
			//led on
			//sprintf(MyString,"TASKB on\n");
			//UART_putstring(MyString);
			taskENTER_CRITICAL();
			PORTB |= (1<<PORTB1);
			volatile long int j = 137143;
			while(j>0)
			{j--;}
			j = 137143;
			while(j>0)
			{j--;}
			PORTB &= ~(1<<PORTB1);
			taskEXIT_CRITICAL();
			//sprintf(MyString,"TASKB Off\n");
			//UART_putstring(MyString);	
		}
	}
	vTaskDelete( NULL );
}
void vCTaskFunction( void *pvParameters )
{
	for( ;; )
	{
		TickType_t xLastWakeTimeC;
		const TickType_t xLightupDelayC = 30;		// 15ms*30 = 450
		const TickType_t xPeriodFrequencyC = 93;// 15ms per tick  15ms*93 = 1395
		
		xLastWakeTimeC = xTaskGetTickCount();

		for( ;; )
		{
			vTaskDelayUntil( &xLastWakeTimeC, xPeriodFrequencyC );
			//led on
			//sprintf(MyString,"TASKC On\n");
			//UART_putstring(MyString);
			taskENTER_CRITICAL();
			PORTB |= (1<<PORTB2);
			volatile long int k = 137143;
			while(k>0)
			{k--;}
			k = 137143;
			while(k>0)
			{k--;}
			k = 137143;
			while(k)
			{k--;}
			PORTB &= ~(1<<PORTB2);
			taskEXIT_CRITICAL();
			//sprintf(MyString,"TASKC Off\n");
			//UART_putstring(MyString);

			
		}
	}
	vTaskDelete( NULL );
}

int main(void)
{

	UART_init(BAUD_PRESCALER);
	LED_Initialize();
	xTaskCreate( vATaskFunction,"TASKA",256,NULL,4,NULL);
	xTaskCreate( vBTaskFunction,"TASKB",256,NULL,3,NULL);
	xTaskCreate( vCTaskFunction,"TASKB",256,NULL,2,NULL);
	sprintf(MyString,"go\n");
	UART_putstring(MyString);
	vTaskStartScheduler();

}	
*/