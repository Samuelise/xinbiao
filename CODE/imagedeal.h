/*
 * imagedeal.h
 *
 *  Created on: 2021Äê5ÔÂ3ÈÕ
 *      Author: samuelise
 */


#include "MainInclude.h"

#define IMAGE_H MT9V03X_H
#define IMAGE_W MT9V03X_W

extern uint8 image[IMAGE_H][IMAGE_W];
extern uint16 point[2];
extern uint8 point_max[4];
extern int16 frames;
extern uint8 light_find;
void image_decompression(uint8 *src, uint8 *dst);
void image_deal(void);
void searchPoint(void);
void imagePredeal(void);
