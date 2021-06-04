/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/


#include "headfile.h"
#include "MainInclude.h"
#pragma section all "cpu0_dsram"
//将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中


void all_init(void);
//工程导入到软件之后，应该选中工程然后点击refresh刷新一下之后再编译
//工程默认设置为关闭优化，可以自己右击工程选择properties->C/C++ Build->Setting
//然后在右侧的窗口中找到C/C++ Compiler->Optimization->Optimization level处设置优化等级
//一般默认新建立的工程都会默认开2级优化，因此大家也可以设置为2级优化

//对于TC系列默认是不支持中断嵌套的，希望支持中断嵌套需要在中断内使用enableInterrupts();来开启中断嵌套
//简单点说实际上进入中断后TC系列的硬件自动调用了disableInterrupts();来拒绝响应任何的中断，因此需要我们自己手动调用enableInterrupts();来开启中断的响应。
int core0_main(void)
{
	get_clk();//获取时钟频率  务必保留
	//用户在此处调用各种初始化函数等

    all_init();
    menu_init();
//    params_read();
//    params_load();
    ips200_clear(WHITE);
    mt9v03x_finish_flag=0;

    //等待所有核心初始化完毕
	IfxCpu_emitEvent(&g_cpuSyncEvent);
	IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
	enableInterrupts();

	frames_nolight=0;  //丢灯之后的帧数
    frames = 0;        //帧差法记录帧数
	light_find=0;      //找灯标志
	differ = 0;        //偏差

	//注意 从V1.1.6版本之后  printf打印的信息从串口输出具体可以学习库例程6-Printf_Demo
    //注意 从V1.1.6版本之后  printf打印的信息从串口输出具体可以学习库例程6-Printf_Demo
    //注意 从V1.1.6版本之后  printf打印的信息从串口输出具体可以学习库例程6-Printf_Demo
	while (TRUE)
	{

	    uint16 dianya=0;
	    dianya = adc_convert(ADC_0,ADC0_CH4_A4,ADC_12BIT);
	    if(dianya>=DIANYA_MAX) carCtrl.mode = CTRL_START;
	    if(dianya<=DIANYA_MIN) carCtrl.mode = CTRL_STOP;
	    if(mt9v03x_finish_flag==1)
	    {
	        frames++;   //帧数+1
	        if(light_find==1)//上一帧图像找到灯了
	        {
	            frames_nolight++;
	        }
	        //printf("dianya: %d\n", dianya);
	        image_deal();


	        mt9v03x_finish_flag=0;
	    }

//注：串口数据数据流小于10KB/S
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

    uart_init(SLAVE_UART, 115200, SLAVE_TX, SLAVE_RX);  //初始化蓝牙
    adc_init(ADC_0,ADC0_CH4_A4);
}


#pragma section all restore


