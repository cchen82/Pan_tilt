/*
 * MahonyIMU.h
 *
 * Created: 2020/11/25 10:17:52
 *  Author: Kennys
 */ 


#ifndef MAHONYIMU_H_
#define MAHONYIMU_H_


void MahonyAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);
void q2Angle(float angle[3]);

#define twoKi 0.0f
#define twoKp 1.0f
#define sampleFreq 100.0f




#endif /* MAHONYIMU_H_ */