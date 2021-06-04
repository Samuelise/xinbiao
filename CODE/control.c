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
/********************����������Ϣ��ʼ��********************/
void carControl_init(void)
{
    carCtrl.mode = CTRL_STOP;
    carCtrl.distance = 0;
    differ = 0;
    hopeSpeed=100;
    speed=0;
}

/********************��������������********************/
//�趨��ͬ������ģʽ
void carControl(void)
{
    switch (carCtrl.mode)
    {
        case CTRL_START:   //������
            speedControl();
            break;
        case CTRL_STOP:    //ɲ��
            hopeSpeed=0;
            speedControl();
            break;
        case CTRL_DEBUG:   //debugģʽ��С������
            drive_motor(0,0);
            break;
        default:
        break;
    }
}

//�ٶȿ��ƺ���������������Ϣ���趨��ͬ���ٶ�����ֵ
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

