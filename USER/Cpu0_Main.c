/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/


#include "headfile.h"
#include "MainInclude.h"
#pragma section all "cpu0_dsram"
//���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��


void all_init(void);
//���̵��뵽���֮��Ӧ��ѡ�й���Ȼ����refreshˢ��һ��֮���ٱ���
//����Ĭ������Ϊ�ر��Ż��������Լ��һ�����ѡ��properties->C/C++ Build->Setting
//Ȼ�����Ҳ�Ĵ������ҵ�C/C++ Compiler->Optimization->Optimization level�������Ż��ȼ�
//һ��Ĭ���½����Ĺ��̶���Ĭ�Ͽ�2���Ż�����˴��Ҳ��������Ϊ2���Ż�

//����TCϵ��Ĭ���ǲ�֧���ж�Ƕ�׵ģ�ϣ��֧���ж�Ƕ����Ҫ���ж���ʹ��enableInterrupts();�������ж�Ƕ��
//�򵥵�˵ʵ���Ͻ����жϺ�TCϵ�е�Ӳ���Զ�������disableInterrupts();���ܾ���Ӧ�κε��жϣ������Ҫ�����Լ��ֶ�����enableInterrupts();�������жϵ���Ӧ��
int core0_main(void)
{
	get_clk();//��ȡʱ��Ƶ��  ��ر���
	//�û��ڴ˴����ø��ֳ�ʼ��������

    all_init();
    dianya=0;

    //�ȴ����к��ĳ�ʼ�����
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
    enableInterrupts();

    //menu_init();
    //params_read();
    //params_load();
    ips200_clear(WHITE);
    mt9v03x_finish_flag=0;

	frames_nolight=0;  //����֮���֡��
    frames = 0;        //֡���¼֡��
	light_find=0;      //�ҵƱ�־
	differ = 0;        //ƫ��

	//ע�� ��V1.1.6�汾֮��  printf��ӡ����Ϣ�Ӵ�������������ѧϰ������6-Printf_Demo
    //ע�� ��V1.1.6�汾֮��  printf��ӡ����Ϣ�Ӵ�������������ѧϰ������6-Printf_Demo
    //ע�� ��V1.1.6�汾֮��  printf��ӡ����Ϣ�Ӵ�������������ѧϰ������6-Printf_Demo
	while (TRUE)
	{
	    if(mt9v03x_finish_flag==1)
	    {

	        frames++;   //֡��+1
	        if(light_find==1)//��һ֡ͼ���ҵ�����
	        {
	            frames_nolight++;
	        }
	        image_deal();
	        mt9v03x_finish_flag=0;
	    }

//ע����������������С��10KB/S
	}
}

void all_init(void)
{
    drive_init();
    ips200_init();
    mt9v03x_init();

    gpt12_init(GPT12_T2,MOTOR_A_ENCODER_1,MOTOR_A_ENCODER_2);
    gpt12_init(GPT12_T3,MOTOR_B_ENCODER_1,MOTOR_B_ENCODER_2);

    pit_interrupt_ms(CCU6_0, PIT_CH0, 10);
    pit_interrupt_ms(CCU6_1,PIT_CH1,1000);

    uart_init(SLAVE_UART, 115200, SLAVE_TX, SLAVE_RX);  //��ʼ������
    adc_init(ADC_0,ADC0_CH4_A4);

    gtm_pwm_init(BEEP_PIN, 3000, 0);
    carControl_init();
}


#pragma section all restore


