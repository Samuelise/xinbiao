#ifndef _DRIVE_H
#define _DRIVE_H

#include "MainInclude.h"

extern float32 motorP;
extern float32 motorI;
extern float32 motorD;


void motor_test(void);
void drive_init(void);
void drive_motor(int16 leftspeed, int16 rightspeed);
float32 pid_servo(const int16 nowError);
void pid_motor(const int16 leftSpeedHope, const int16 rightSpeedHope, const int16 leftSpeed, const int16 rightSpeed);

#endif
