/*
 * params.c
 *
 *  Created on: 2021年4月29日
 *      Author: 18055
 */

/*
 * @Description:
 * @Autor: samuelise
 * @Date: 2021-02-23 20:44:50
 * @LastEditors: samuelise
 * @LastEditTime: 2021-03-01 20:08:00
 */

#include "params.h"

params Params;

void params_write(void)
{
    if(flash_check(PARAMS_SECTOR, 0))   eeprom_erase_sector(PARAMS_SECTOR);
    //统一转存为uint32类型
    uint32 params_buff[TOTAL_PARAMS_NUM];
    params_buff[SERVO_S_P]=float_conversion_uint32(Params.pid[SERVO_S_P]);params_buff[SERVO_S_D]=float_conversion_uint32(Params.pid[SERVO_S_D]);
    params_buff[SERVO_T_P]=float_conversion_uint32(Params.pid[SERVO_T_P]);params_buff[SERVO_T_D]=float_conversion_uint32(Params.pid[SERVO_T_D]);
    params_buff[SERVO_BT_P]=float_conversion_uint32(Params.pid[SERVO_BT_P]);params_buff[SERVO_BT_D]=float_conversion_uint32(Params.pid[SERVO_BT_D]);
    params_buff[MOTOR_P]=float_conversion_uint32(Params.pid[MOTOR_P]);params_buff[MOTOR_I]=float_conversion_uint32(Params.pid[MOTOR_I]);params_buff[MOTOR_D]=float_conversion_uint32(Params.pid[MOTOR_D]);
    params_buff[SPEED_LOW]=Params.speed[SPEED_LOW-PID_NUM];
    params_buff[SPEED_MID]=Params.speed[SPEED_MID-PID_NUM];
    params_buff[SPEED_HIGH]=Params.speed[SPEED_HIGH-PID_NUM];
    int16 page;
    for(page=0;page<TOTAL_PARAMS_NUM;page++){
        eeprom_page_program(PARAMS_SECTOR,page,&params_buff[page]);
    }
}

void params_read(void)
{
    int16 page;
    for(page=0;page<PID_NUM;page++){
        Params.pid[page]=flash_read(PARAMS_SECTOR,page,float);
    }
    for(page=PID_NUM;page<PID_NUM+SPEED_NUM;page++){
        Params.speed[page-PID_NUM]=flash_read(PARAMS_SECTOR,page,int16);
    }
}

void params_load(void)
{
    motorP = Params.pid[MOTOR_P];
    motorI = Params.pid[MOTOR_I];
    motorD = Params.pid[MOTOR_D];
}



