/*
 * MainInclude.h
 *
 *  Created on: 2021年4月8日
 *      Author: 18055
 */
#ifndef _MAININCLUDE_H
#define _MAININCLUDE_H

#include "headfile.h"
#include "common.h"
#include "drive.h"
#include "control.h"
#include "menu.h"
#include "params.h"
#include "imagedeal.h"

/*********************引脚****************************/
//电机引脚
#define MOTOR_A_PIN_1 P20_6
#define MOTOR_A_PIN_2 P20_7
#define MOTOR_B_PIN_1 P20_8
#define MOTOR_B_PIN_2 P20_9
#define MOTOR_A_PWM   ATOM0_CH1_P21_3
#define MOTOR_B_PWM   ATOM0_CH3_P21_5


//编码器引脚
#define MOTOR_A_ENCODER_1   GPT12_T2INB_P33_7
#define MOTOR_A_ENCODER_2   GPT12_T2EUDB_P33_6
#define MOTOR_B_ENCODER_1   GPT12_T3INA_P02_6
#define MOTOR_B_ENCODER_2   GPT12_T3EUDA_P02_7

//蜂鸣器
#define BEEP_PIN    ATOM0_CH4_P21_6

//拨码开关
#define BOMA_PIN_1    P10_1
#define BOMA_PIN_2    P10_2
#define BOMA_PIN_3    P10_3
#define BOMA_PIN_4    P10_5

//按键
#define KEY_PIN_1   P22_0
#define KEY_PIN_2   P22_1
#define KEY_PIN_3   P22_2
#define KEY_PIN_4   P22_3

//无线收发
#define SLAVE_TX    UART3_TX_P15_6
#define SLAVE_RX    UART3_RX_P15_7
#define SLAVE_UART  UART_3
#define SLAVE_BAUD  115200





#define DIANYA_MAX  2100
#define DIANYA_MIN  1300


extern int16 frames;
extern uint8 light_find;


#endif


