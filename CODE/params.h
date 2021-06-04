/*
 * params.h
 *
 *  Created on: 2021年4月29日
 *      Author: 18055
 */



/*
 * @Description:
 * @Autor: samuelise
 * @Date: 2021-02-23 20:45:01
 * @LastEditors: samuelise
 * @LastEditTime: 2021-03-01 20:08:51
 */
#ifndef PARAMS_H
#define PARAMS_H

#include "mainInclude.h"

#define PID_NUM  9
#define SPEED_NUM 3
#define TOTAL_PARAMS_NUM (PID_NUM+SPEED_NUM)

#define PARAMS_SECTOR (0)

//参数存储结构体
typedef struct PARAMS{
    float32 pid[PID_NUM];  //pid
    int16 speed[SPEED_NUM]; //期望速度
}params;

extern params Params;
void params_write(void);
void params_read(void);
void params_load(void);
#endif

