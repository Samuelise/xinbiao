/*
 * imagedeal.c
 *
 *  Created on: 2021年5月3日
 *      Author: samuelise
 */

#include "imagedeal.h"

#define ABS(x) ( (x)>0?(x):-(x) )

uint8 point_max[4];//上下左右
uint16 point[2];//灯的中心点
uint8 image_last[IMAGE_H][IMAGE_W]; //存当前帧图像
uint8 image[IMAGE_H][IMAGE_W];      //结果图像

int16 frames_nolight;
uint8 light_find;
int16 frames;
void image_decompression(uint8 *src, uint8 *dst)
{
    int i,j;

    uint16 temp = 0;
//    for(i=0;i<IMAGE_H * (IMAGE_W/8);i++)
//    {
//        temp = *src;
//        src++;
//        for(j=0; j<8; j++)
//        {
//            if( (temp<<j)&0x80 )    *dst++ = 255;
//            else                    *dst++ = 0;
//        }
//    }
    for(i=0;i<IMAGE_H;i++)
    {
        for(j=0;j<IMAGE_W;j++){
            *dst++ = *src++;
        }


    }
}

void image_deal(void)
{
    point_max[0] = IMAGE_H-1; point_max[1] = 0; point_max[2] = IMAGE_W-1; point_max[3] = 0;
    point[0]=0;point[1]=0;
    image_decompression(mt9v03x_image[0],image[0]);

    //zhencha();

    if(carCtrl.mode==CTRL_DEBUG)
    {
        ips200_displayimage032(image[0], IMAGE_W, IMAGE_H);
        //seekfree_sendimg_03x(SLAVE_UART,image[0],IMAGE_W,IMAGE_H);
    }

    imagePredeal();   //预处理

    //ips200_displayimage032(image[0], IMAGE_W, IMAGE_H);


    searchPoint();

   // if(carCtrl.mode==CTRL_DEBUG)
        display();

}

#define Threshold 100
#define frames_delta 1
void zhencha(void)
{
    for(int i=0;i<IMAGE_H;i++)
        for(int j=0;j<IMAGE_W;j++)
        {
            uint8 temp;
            temp = image[i][j];
            image[i][j] = ABS(image[i][j] - image_last[i][j]);   //求帧差
            image_last[i][j] = temp;                      //记录当前帧

        }
}

#define LIGHT_TH 120
void imagePredeal(void){

   uint8 th=0;
   uint16 white_num=0;
   for (int i = 0; i < IMAGE_H; i++) {
        for (int j = 0; j < IMAGE_W; j++) {
            if (image[i][j] >= th)
                {
                    th = image[i][j];
                }
        }
    }
   th = th-3;
   if(th<=LIGHT_TH) th=LIGHT_TH;
   carCtrl.threshold_image=th;
   th=100;

   for (int i = 0; i < IMAGE_H; i++)
   {
        for (int j = 0; j < IMAGE_W; j++) {
            if (image[i][j] >= th)
            {
                image[i][j] = 255;
                white_num++;
            }
            else image[i][j] = 0;
        }
    }
   carCtrl.white_num=white_num;
}

void searchPoint(void)
{
    uint8 stage = 0;
    for (uint8 i = 0; i < IMAGE_H&&stage==0; i++)
    {
        for (uint8 j = 0; j < IMAGE_W; j++)
        {
            if (image[i][j] == 255) {
                point_max[0] = i-1;//上点所在行
                stage++;//找到上点
                break;
            }
        }
    }
    for(uint8 i=IMAGE_H-1;i>point_max[0]&&stage==1;i--)
        for (uint8 j = 0; j < IMAGE_W; j++) {
            if (image[i][j] == 255) {
                point_max[1] = i+1;//下点所在行
                stage++;
                break;
            }
        }
   for(uint8 j=0;j<IMAGE_W&&stage==2;j++)
       for (uint8 i = point_max[0]; i < point_max[1]; i++) {
           if (image[i][j] == 255) {
               point_max[2] = j-1;//左点所在列
               stage++;
               break;
           }
       }
   for(uint8 j =IMAGE_W-1;j>point_max[2]&&stage==3;j--)
       for (uint8 i = point_max[0]; i < point_max[1]; i++) {
           if (image[i][j] == 255)
           {
               point_max[3] = j+1;//右点所在列
               stage++;
               point[0] = (point_max[1] + point_max[0]) / 2;
               point[1] = (point_max[2] + point_max[3]) / 2;
               light_find=1;        //找灯标志置1
               differ = point[1] - 80;
               break;
           }
       }
   if (stage != 3&&frames_nolight>50)
   {
       differ = 80;//没找到中心
       frames_nolight =0;
   }
}

void display(void)
{
    ips200_showint16(0,200,leftspeed);ips200_showint16(100,200,rightspeed);//左右轮速度
    ips200_showint16(0,204,differ);ips200_showint16(100,204,carCtrl.differ);//实际偏差和计算偏差
    ips200_showuint8(0,205,point_max[0]);ips200_showuint8(100,205,point_max[1]);//上下行
    ips200_showuint8(0,206,point_max[2]);ips200_showuint8(100,206,point_max[3]);//左右列
    ips200_showuint16(0,207,point[0]);ips200_showuint16(100,207,point[1]);//灯中心坐标
    ips200_showuint16(0,208,carCtrl.mode);//运行模式
    ips200_showuint8(0,209,carCtrl.threshold_image);ips200_showuint16(100,209,carCtrl.white_num);//分割阈值
}
