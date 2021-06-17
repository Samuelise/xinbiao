/*
 * drive.c
 *
 *  Created on: 2021年4月8日
 *      Author: 18055
 */

#include "drive.h"

float32 motorP = 50;
float32 motorI = 1;
float32 motorD = 0;

float32 servoP = 1.1;   //舵机的p值
float32 servoD = 0.1; //d值

void motor_test(void)
{
    //gpio_set(MOTOR_A_PIN_1, 0);
    drive_motor(7000,-7000);
}


void drive_init(void)
{
    leftspeed=0;rightspeed=0;
    gpio_init(MOTOR_A_PIN_1, GPO, 0, PUSHPULL);
    gpio_init(MOTOR_A_PIN_2, GPO, 0, PUSHPULL);
    gpio_init(MOTOR_B_PIN_1, GPO, 0, PUSHPULL);
    gpio_init(MOTOR_B_PIN_2, GPO, 0, PUSHPULL);

    gtm_pwm_init(MOTOR_A_PWM, 17000, 0);
    gtm_pwm_init(MOTOR_B_PWM, 17000, 0);
}

void drive_motor(int16 leftspeed, int16 rightspeed)
{
    int8 leftmode,rightmode;

    //调向
    leftmode = leftspeed>0?1: -1;
    rightmode = rightspeed>0?1: -1;

    gpio_set(MOTOR_A_PIN_1, rightmode==1?1:0);
    gpio_set(MOTOR_A_PIN_2, rightmode==1?0:1);
    gpio_set(MOTOR_B_PIN_1, leftmode==1?0:1);
    gpio_set(MOTOR_B_PIN_2, leftmode==1?1:0);

    //调速
    pwm_duty(MOTOR_B_PWM, leftmode*leftspeed);
    pwm_duty(MOTOR_A_PWM, rightmode*rightspeed);


}

float32 pid_servo(const int16 nowError)
{
    static int16 lastError;
    int16 D = nowError - lastError;
    float32 result = (servoP * nowError + servoD * D);
    lastError = nowError;
    float32 duty = result;
    // duty = (duty < 200) ? duty : 200;
    // duty = (duty > -200) ? duty : -200;
    //限幅
    duty = (duty < 80) ? duty : 80;
    duty = (duty > -80) ? duty : -80;
    return duty;
}

void pid_motor(const int16 leftSpeedHope, const int16 rightSpeedHope, const int16 leftSpeed, const int16 rightSpeed)
{
    int16 nowErr_L, nowErr_R;
    static int16 preErr_L, prepreErr_L, preErr_R, prepreErr_R;
    static int16 adjustLeft, adjustRight;
    nowErr_L = leftSpeedHope - leftSpeed;
    nowErr_R = rightSpeedHope - rightSpeed;
    adjustLeft += motorP * (nowErr_L - preErr_L) + motorI * nowErr_L + motorD * (nowErr_L + prepreErr_L - 2 * preErr_L);
    adjustRight += motorP * (nowErr_R - preErr_R) + motorI * nowErr_R + motorD * (nowErr_R + prepreErr_R - 2 * preErr_R);
    prepreErr_L = preErr_L;
    preErr_L = nowErr_L;
    prepreErr_R = preErr_R;
    preErr_R = nowErr_R;
    adjustLeft = adjustLeft > -8000 ? adjustLeft : -8000;
    adjustRight = adjustRight > -8000 ? adjustRight : -8000;
    adjustLeft = adjustLeft < 8000 ? adjustLeft : 8000;
    adjustRight = adjustRight < 8000 ? adjustRight : 8000;

    //    debugFlag.leftPwn=adjustLeft;
    //    debugFlag.rightPwm=adjustRight;
    drive_motor(adjustLeft, adjustRight);
}




