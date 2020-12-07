////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////    main.c
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

#define F_CPU 16000000UL

/*--------------------Libraries---------------------------*/
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/sleep.h>
#include "main.h"
/* Scheduler include files. */
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"
#include "../FreeRTOS/queue.h"
#include "../FreeRTOS/semphr.h"

/* system time include file. */
#include "time.h"

/*global variables*/
extern float AccData[3];
extern float GyroData[3];
extern float Angle[3];

char MyString[10];
/*-----------------------------------------------------*/
int main(void)
{
	/* Replace with your application code */
	UART_init(BAUD_PRESCALER);
	I2C_Init();
	MPU_Init();

	while(1)
	{
		/*
		MPU_read(AccData,GyroData);
		MahonyAHRSupdateIMU(GyroData[0],GyroData[1],GyroData[2],AccData[0],AccData[1],AccData[2]);
		q2Angle(Angle);
		sprintf(MyString,"Angle x:%.3f\n", Angle[0]);
		UART_putstring(MyString);
		*/
		MytaskCreate();
		vTaskStartScheduler();
	}

}	
