/*
 * balance.c
 *
 * Created: 2020/12/7 17:40:45
 *  Author: Kennys
 */ 
#include "balance.h"
#include "../lib/uart.h"
#include <stdio.h>
extern char MyString[10];
// struct PID_Para PIDParaX;
// struct PID_Para PIDParaY;
// float last_error;
// float increment_error;
// float x_error;
// float y_error;
// float DEG1;
// float DEG2;

float PID(float error, float last_error, float increment_error)
{
	static float output;
	output = (float)error*Kp+increment_error*Ki+(error-last_error)*Kd;
// 	last_error = error;
// 	increment_error += error;
// 	if(increment_error >Increament_Max/Ki)
// 	{
// 		increment_error = Increament_Max/Ki;
// 	}
// 	if(increment_error < - Increament_Max/Ki)
// 	{
// 		increment_error = - Increament_Max/Ki;
// 	}

	if (output>85)
	{
		output = 85;
	}
	if (output<-85)
	{
		output = -85;
	}
	output += 90;
	return output;

}
// float PID(float error, float frequency, struct PID_Para Parameter)
// {
// 	static float output;
// 	output = (float)error*Kp+Parameter.increment_error*Ki+(error-Parameter.last_error)*Kd;
// 	Parameter.last_error = error;
// 	Parameter.increment_error += error;
// 	if(Parameter.increment_error >Increament_Max/Ki)
// 	{
// 		Parameter.increment_error = Increament_Max/Ki;
// 	}
// 	if(Parameter.increment_error < - Increament_Max/Ki)
// 	{
// 		Parameter.increment_error = - Increament_Max/Ki;
// 	}
// 
// 	if (output>90)
// 	{
// 		output = 90;
// 	}
// 	if (output<-90)
// 	{
// 		output = -90;
// 	}
// 	output += 90;
// 	return output;
// 	
// }
// 
// void BalanceControl(float pAngle[3])
// {
// 	x_error = - pAngle[0];
// 	y_error = - pAngle[1];
// 	DEG1 = PID(x_error,PID_Freq,PIDParaX);
// 	DEG2 = PID(y_error,PID_Freq,PIDParaY);
// 	
// 	sprintf(MyString,"Y %f \n",PIDParaY.increment_error);
// 	UART_putstring(MyString);
// 
// 	deg_to_servo1(DEG1);
// 	deg_to_servo2(DEG2);	
// 	
// }