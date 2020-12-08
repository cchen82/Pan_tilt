/*
 * balance.c
 *
 * Created: 2020/12/7 17:40:45
 *  Author: Kennys
 */ 
#include "balance.h"
#include "../lib/uart.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
extern char MyString[10];
struct PID_Para PIDParaX={0,0};
struct PID_Para PIDParaY={0,0};
float last_error;
float increment_error;

float PID(float error, int frequency, struct PID_Para Parameter)
{
	float output;
	output = error*Kp+Parameter.increment_error*Ki+(error-Parameter.last_error)*Kd;
	Parameter.last_error = error;
	Parameter.increment_error += error;
	if (output>90)
	{
		output = 90;
	}
	if (output<-90)
	{
		output = -90;
	}
	output += 90;
	return output;
}

void BalanceControl(float pAngle[3])
{
	float x_error = pAngle[0] - 0;
	float y_error = pAngle[1] - 0;
	float DEG1 = PID(x_error,PID_Freq,PIDParaX);
	float DEG2 = PID(y_error,PID_Freq,PIDParaY);
	sprintf(MyString,"X error %f\n",DEG1);
	UART_putstring(MyString);
	deg_to_servo1(DEG1);
	deg_to_servo2(DEG2);	
	
}