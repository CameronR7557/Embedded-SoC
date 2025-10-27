/*************************************************************
* Author:		Cameron Robinson
* Filename:		myLCD_Driver.h
* Date Created:	11/16/23
**************************************************************/
#ifndef _MYLCD_DRIVER_H_
#define _MYLCD_DRIVER_H_

#include "LCD_Hw.h"
#include <stdint.h>
#include "alt_interrupt.h"
#include "alt_interrupt_common.h"

#define MAX_DISPLAY_DIST 2000 
#define BLACK 0xff
#define WHITE 0x00
#define PI 3.14159f
#define DEG_TO_RAD	(float)(PI/180.0F)

typedef struct
{
	uint16_t width;
	uint16_t height;
	uint16_t frameSize;
	uint8_t* LCD_buffer;
	
	uint8_t cur_col;
	uint8_t cur_line;
	uint8_t cur_page;
}LCD_Dev;

void myLCD_Init(LCD_Dev* lcd, uint8_t startX, uint8_t startY);
void myLCD_SetDrawAddress(LCD_Dev* lcd, uint8_t x, uint8_t y);
void myLCD_FillScreen(LCD_Dev* lcd);
void myLCD_DisplayData(LCD_Dev* lcd, uint16_t startAngle, uint16_t endAngle, uint16_t* data);
void DRAW_Pixel2(LCD_Dev* pCanvas, int X, int Y, int Color);


#endif