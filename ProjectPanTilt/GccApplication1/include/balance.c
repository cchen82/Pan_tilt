/*
 * balance.c
 *
 * Created: 2020/12/7 17:40:45
 *  Author: Kennys
 */ 
#include "balance.h"

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
	return output;
}

void BalanceControl(float pAngle[3])
{
	float x_error = pAngle[0] - 0;
	float y_error = pAngle[1] - 0;	
	deg_to_servo1(PID(x_error,PID_Freq,PIDParaX));
	deg_to_servo2(PID(y_error,PID_Freq,PIDParaY));	
	
}