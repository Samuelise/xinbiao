/*
 * menu.h
 *
 *  Created on: 2021年4月29日
 *      Author: 18055
 */

/*
 * @Description:
 * @Autor: samuelise
 * @Date: 2021-02-08 21:32:25
 * @LastEditors: samuelise
 * @LastEditTime: 2021-03-01 20:07:41
 */
#ifndef MENU_H
#define MENU_H
#include "mainInclude.h"

#define Page_MAXItems 10
#define Main_Page_Items 4
#define Test_Page_Items 6
#define Setting_Page_Items TOTAL_PARAMS_NUM
#define Params_Page_Items TOTAL_PARAMS_NUM

#define Itembegin_X 24
#define Itembegin_Y 1

#define KEY_OK P22_2
#define KEY_UP P22_1
#define KEY_DOWN P22_3
#define GET_VALUE(pin)  !gpio_get(pin)

typedef struct MenuItem
{
    uint8 itemindex;
    uint8 itemCnt;
    int8* displaystr;
    void (*itemfunc)();
    struct MenuItem *pchildmenu;
    struct MenuItem *pparentmenu;
}menuitem;

typedef enum
{
    DEBUG_PAGE=0,MAIN_PAGE_1,MAIN_PAGE_2,MAIN_PAGE_3,
    TEST_PAGE,TEST_PAGE_1,TEST_PAGE_2,TEST_PAGE_3,
    SETTING_PAGE,SETTING_PAGE_1,SETTING_PAGE_2,SETTING_PAGE_3,
    PARAMS_PAGE
}MENU_INDEX; //菜单索引

typedef enum
{
    SERVO_S_P=0, SERVO_S_D,
    SERVO_T_P, SERVO_T_D,
    SERVO_BT_P, SERVO_BT_D,
    MOTOR_P, MOTOR_I, MOTOR_D,
    SPEED_LOW, SPEED_MID, SPEED_HIGH
}PARAMS_INDEX; //参数索引

typedef enum
{
    NOTHING=0,
    OK,CANCEL,
    UP,DOWN
}KEY_VALUE; //键值

void debug_run(void);
void test_all(void);
void setting_params(void);
void show_params(void);
void change(int8 index);
void menu_init(void);
void menu_show(menuitem* menu);
void key_init(void);
uint8 get_keyvalue(void);


#endif



