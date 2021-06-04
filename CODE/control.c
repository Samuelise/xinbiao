/*
 * @Description: 
 * @Autor: samuelise
 * @Date: 2021-02-25 15:36:25
 * @LastEditors: samuelise
 * @LastEditTime: 2021-03-01 19:31:37
 */
#include "control.h"
struct _carControl carCtrl;
int16 hopeSpeed;
int16 leftspeed;
int16 rightspeed;
int16 speed;
int16 differ;
/********************车辆控制信息初始化********************/
void carControl_init(void)
{
    carCtrl.mode = CTRL_STOP;
    carCtrl.distance = 0;
    differ = 0;
    hopeSpeed=100;
    speed=0;
}

/********************车辆控制主函数********************/
//设定不同的运行模式
void carControl(void)
{
    switch (carCtrl.mode)
    {
        case CTRL_START:   //正常跑
            speedControl();
            break;
        case CTRL_STOP:    //刹车
            hopeSpeed=0;
            speedControl();
            break;
        case CTRL_DEBUG:   //debug模式，小车不跑
            drive_motor(0,0);
            break;
        default:
        break;
    }
}

//速度控制函数，根据赛道信息，设定不同的速度期望值
void speedControl(void)
{
    int16 speed=(rightspeed+leftspeed)/2;
    hopeSpeed=100;
    int16 rightSpeedHope ;
    int16 leftSpeedHope ;
    rightSpeedHope = hopeSpeed - hopeSpeed * (carCtrl.differ / 80.0);
    leftSpeedHope = hopeSpeed + hopeSpeed * (carCtrl.differ / 80.0);
    if(differ>=80){
        leftSpeedHope=hopeSpeed;
        rightSpeedHope=-hopeSpeed;
    }
    pid_motor(leftSpeedHope, rightSpeedHope, leftspeed, rightspeed);
    //motor_test();
}

