/*
 * @Description: 
 * @Autor: samuelise
 * @Date: 2021-02-25 15:36:37
 * @LastEditors: samuelise
 * @LastEditTime: 2021-03-01 19:32:17
 */
#ifndef CODE_CONTROL_H_
#define CODE_CONTROL_H_
#include"mainInclude.h"

//����ģʽ�궨�壬�϶�ʱʹ��ö��
#define CTRL_START 1
#define CTRL_NEED 2
#define CTRL_STOP 0
#define CTRL_DEBUG 3
struct _carControl
{
	uint8 mode;      //����ģʽ
	int32 distance;  //��ʻ����
	int16 differ;    //ƫ��
	uint16 threshold_image;//�ָ�ֵ
	uint16 white_num;
};
extern struct _carControl carCtrl;
extern int16 hopeSpeed;
extern int16 speed;
extern int16 differ;
extern int16 leftspeed;
extern int16 rightspeed;
extern uint16 dianya;

void carControl_init(void);
void carControl(void);
void speedControl(void);
#endif /* CODE_CONTROL_H_ */
