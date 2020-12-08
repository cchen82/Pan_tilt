/*
 * balance.h
 *
 * Created: 2020/12/7 17:40:53
 *  Author: Kennys
 */ 


#ifndef BALANCE_H_
#define BALANCE_H_
#define Kp 0.5
#define Ki 0.001/PID_Freq
#define Kd 0*PID_Freq
#define PID_Freq 66.7
#include "../App/servo_joystick.h"
struct PID_Para
{
	float last_error;
	float increment_error;
};

float PID(float error, int frequency, struct PID_Para Parameter);
void BalanceControl(float pAngle[3]);


#endif /* BALANCE_H_ */