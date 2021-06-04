/*
 * menu.c
 *
 *  Created on: 2021年4月29日
 *      Author: 18055
 */
/*
 * @Description:
 * @Autor: samuelise
 * @Date: 2021-02-08 21:32:14
 * @LastEditors: samuelise
 * @LastEditTime: 2021-03-01 20:06:33
 */
#include "menu.h"
#include "stdlib.h"

int8 arrstr[] = "-->";
menuitem main_menu[Main_Page_Items+1];
menuitem params_menu[Params_Page_Items+1];


//菜单项添加格式：索引，当前页选项总数， 选项名称，跳转函数，子菜单，父菜单
//主菜单
menuitem main_menu[Main_Page_Items+1]={
    { DEBUG_PAGE, Main_Page_Items, "Debug Mode", debug_run, NULL, NULL},
    { TEST_PAGE, Main_Page_Items, "Module Test", test_all, NULL, NULL},
    { SETTING_PAGE, Main_Page_Items, "Setting Parameters", setting_params, params_menu, NULL},
    { PARAMS_PAGE, Main_Page_Items, "Show Parameters", show_params, params_menu, NULL}
};
//参数相关菜单
menuitem params_menu[Params_Page_Items+1]={
    { SERVO_S_P, Params_Page_Items, "Straight Servo P: ", change, NULL, main_menu},
    { SERVO_S_D, Params_Page_Items, "Straight Servo D: ", change, NULL, main_menu},
    { SERVO_T_P, Params_Page_Items, "Turn Servo P: ", change, NULL, main_menu},
    { SERVO_T_D, Params_Page_Items, "Turn Servo D: ", change, NULL, main_menu},
    { SERVO_BT_P, Params_Page_Items, "BigTurn Servo P: ", change, NULL, main_menu},
    { SERVO_BT_D, Params_Page_Items, "BigTurn Servo D: ", change, NULL, main_menu},
    { MOTOR_P, Params_Page_Items, "Motor P: ", change, NULL, main_menu},
    { MOTOR_I, Params_Page_Items, "Motor I: ", change, NULL, main_menu},
    { MOTOR_D, Params_Page_Items, "Motor D: ", change, NULL, main_menu},
    { SPEED_LOW, Params_Page_Items, "low speed: ", change, NULL, main_menu},
    { SPEED_MID, Params_Page_Items, "mid speed: ", change, NULL, main_menu},
    { SPEED_HIGH, Params_Page_Items, "high speed: ", change, NULL, main_menu}
};

//菜单指针，主要用于菜单的切换和回退
menuitem* pcurmenu;   //当前菜单
menuitem* pparenmenu; //当前菜单的父菜单
menuitem* pcuritem;   //当前菜单的当前项


//改参数
void change(int8 index)
{
    float pid_step;
    int16 speed_step;
    int8 mode;
    pid_step=0.01;speed_step=1;
    params_read();  //读取参数
    menu_show(params_menu);  //参数显示
    ips200_showstr(0,index,arrstr);
    if(index<=PID_NUM) mode = 0;   //改pid还是改速度(0：改pid 1：改速度)
    else mode=1;
    while(1){
        uint8 key=0;
        key = get_keyvalue();
        switch (key)
        {
        case OK:
            params_write(); //写入到flash中
            show_params();
            break;
        case UP:
            if(mode==0) {
                Params.pid[index-1]+=pid_step;
                ips200_showfloat(160,index,Params.pid[index-1],3,2);
            }
            if(mode==1) {
                Params.speed[index-PID_NUM-1]+=speed_step;
                ips200_showint16(160,index,Params.speed[index-PID_NUM-1]);
            }
            break;
        case DOWN:
            if(mode==0){
                Params.pid[index-1]-=pid_step;
                ips200_showfloat(160,index,Params.pid[index-1],3,2);
            }
            if(mode==1){
                Params.speed[index-PID_NUM-1]-=speed_step;
                ips200_showint16(160,index,Params.speed[index-PID_NUM-1]);
            }
            break;
        default:
            break;
        }
    }
}

//debug模式
void debug_run(void)
{
    ips200_clear(WHITE);
    systick_delay_ms(STM0,1000);
    ips200_showstr(0,0,"debug mode :D");
    carCtrl.mode = CTRL_DEBUG;

}

//测试模式
void test_all(void)
{
    ips200_clear(WHITE);
    systick_delay_ms(STM0,1000);
    ips200_showstr(0,0,"test mode :D");

}

//参数选择
void setting_params(void)
{
    int8 index=1;
    menu_show(pcurmenu);
    ips200_showstr(0,0,"setting params mode :)");
    ips200_showstr(0,1,arrstr);
    while(1){
        uint8 key=0;
        key = get_keyvalue();
        switch (key)
        {
        case OK:
            pparenmenu = pcurmenu;
            pcurmenu = pcurmenu[index].pchildmenu;
            pparenmenu[index-1].itemfunc(index);
            break;
        case UP:
            index--;
            if(index<=0)index = pcurmenu[0].itemCnt;
            pcuritem = &(pcurmenu[index]);
            ips200_clear(WHITE);
            systick_delay_ms(STM0,100);
            menu_show(pcurmenu);
            ips200_showstr(0,index,arrstr);
            break;
        case DOWN:
            index++;
            if(index>pcurmenu[0].itemCnt) index = 1;
            pcuritem = &(pcurmenu[index]);
            ips200_clear(WHITE);
            systick_delay_ms(STM0,100);
            menu_show(pcurmenu);
            ips200_showstr(0,index,arrstr);
            break;
        default:
            break;
        }
    }
}

//显示参数
void show_params(void)
{
    menu_show(params_menu);
    ips200_showstr(0,0,"show params mode :)");
    params_read();
    int16 i;
    for(i=0;i<PID_NUM;i++){
        ips200_showfloat(160,i+1,Params.pid[i],3,2);
    }
    for(i=PID_NUM;i<PID_NUM+SPEED_NUM;i++){
        ips200_showint16(160,i+1,Params.speed[i-PID_NUM]);
    }
}

//菜单初始化
void menu_init(void)
{
    int8 index=0;
    pcurmenu = main_menu;
    pparenmenu = NULL;
    menu_show(pcurmenu);
    while(1){
        uint8 key=0;
        key = get_keyvalue();
        if(pcuritem==NULL&&key==OK&&carCtrl.mode==CTRL_STOP){
//            carCtrl.mode = CTRL_START;
            return ;
        }
        if(carCtrl.mode==CTRL_DEBUG)return ;
        switch (key)
        {
        case OK:
            if(pcurmenu[index-1].pchildmenu!=NULL){
                pparenmenu = pcurmenu;
                pcurmenu = pcurmenu[index-1].pchildmenu;
                pparenmenu[index-1].itemfunc();
            }
            else pcurmenu[index-1].itemfunc();
            break;
        case UP:
            index--;
            if(index<=0)index = pcurmenu[0].itemCnt;
            pcuritem = &(pcurmenu[index]);
            ips200_clear(WHITE);
            systick_delay_ms(STM0,100);
            menu_show(pcurmenu);
            ips200_showstr(0,index,arrstr);
            break;
        case DOWN:
            index++;
            if(index>pcurmenu[0].itemCnt) index = 1;
            pcuritem = &(pcurmenu[index]);
            ips200_clear(WHITE);
            systick_delay_ms(STM0,100);
            menu_show(pcurmenu);
            ips200_showstr(0,index,arrstr);
            break;
        default:
            break;
        }
    }
}

//显示菜单内容
void menu_show(menuitem* menu)
{
    uint16 row = Itembegin_Y;
    uint8 index = 0;
    ips200_clear(WHITE);systick_delay_ms(STM0,100);
    // ips200_showstr(0,Itembegin_Y,arrstr);           //箭头指示选项
    while(menu[index].itemCnt!=0){
        ips200_showstr(Itembegin_X, row, menu[index].displaystr);row++;
        index++;
    }

}

void key_init(void)
{
    gpio_init(KEY_OK, GPI, 0, PULLUP);
    gpio_init(KEY_UP, GPI, 0, PULLUP);
    gpio_init(KEY_DOWN, GPI, 0, PULLUP);
}

//读取键值
uint8 get_keyvalue(void)
{
    uint8 keyvalue=0;
    keyvalue = (GET_VALUE(KEY_OK))*4+(GET_VALUE(KEY_DOWN))*2+GET_VALUE(KEY_UP);
    if(keyvalue!=0){
        systick_delay_ms(STM0,10);
        keyvalue = (GET_VALUE(KEY_OK))*4+(GET_VALUE(KEY_DOWN))*2+GET_VALUE(KEY_UP);
        switch (keyvalue)
        {
        case 4:
            keyvalue = OK;
            break;
        case 2:
            keyvalue = DOWN;
            break;
        case 1:
            keyvalue = UP;
            break;
        default:
            keyvalue = NOTHING;
            break;
        }
    }
    return keyvalue;
}




