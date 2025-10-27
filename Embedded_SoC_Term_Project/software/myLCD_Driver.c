/*************************************************************
* Author:		Cameron Robinson
* Filename:		myLCD_Driver.c
* Date Created:	11/16/23
* Modifications: 12/6/23:  Fixed lidar display function
**************************************************************/

#include <math.h>
#include <stdlib.h>
#include "myLCD_Driver.h"

/**********************************************************************
* Purpose: Initalizes LCD on DE10-Standard
* Precondition:
*		   Function called and passed pointer to lcd struct,
			starting x coord, and starting y coord.
*
* Postcondition:
*		   LCD is initialized
************************************************************************/
void myLCD_Init(LCD_Dev* lcd, uint8_t startX, uint8_t startY)
{
	LCDHW_Write8(0, 0xC8);//Set common output mode
	LCDHW_Write8(0, 0x2F);//Set power control
	myLCD_SetDrawAddress(lcd, startX, startY);//Set starting addr
	LCDHW_Write8(0, 0xAF);//Turn on LCD
}

/**********************************************************************
* Purpose: Sets drawing address of LCD on DE10-Standard
* Precondition:
*		   Function is called and passed lcd struct pointer, and new coords.
*
* Postcondition:
*		   Draw address is set to passed x and y coords.
************************************************************************/
void myLCD_SetDrawAddress(LCD_Dev* lcd, uint8_t x, uint8_t y)
{
	uint8_t page = y / 8;			//Var for calculated page of LCD 
	uint8_t line = 1 << (y % 8);	//Var for calculated line of LCD
	uint8_t col = 0;				//Var for calculated column of LCD
	
	if(x > 127)
		col = 127;
	else
		col = x;
	
	LCDHW_Write8(0, (0xB0 | page));      //Set page  (Y values divided into 8 pages)
	LCDHW_Write8(0, (0x40 | line));		 //Set line (i.e., bit 0-7)
	LCDHW_Write8(0, (0x10 | (col >> 4)));//Set upper col addr
	LCDHW_Write8(0, (0x0F & col));		 //Set lower col addr
	
	lcd->cur_col = col;
	lcd->cur_page = page;
	lcd->cur_line = line;
}

/**********************************************************************
* Purpose: Fills screen of DE10-Standard's LCD with what is in lcd struct's buffer
* Precondition:
*		   Function called and passed pointer to lcd struct
*
* Postcondition:
*		   All data in struct buffer is displayed on LCD
************************************************************************/
void myLCD_FillScreen(LCD_Dev* lcd)
{
	myLCD_SetDrawAddress(lcd, 0, 0);
	
	for(uint8_t page = 0; page < 8; ++page)
	{
		LCDHW_Write8(0, (0xB0 | page));			 				//Set page number
		LCDHW_Write8(0, 0x10);									//Set upper col addr to 0
		LCDHW_Write8(0, 0x00);		 							//Set lower col addr to 0
		for(uint8_t col = 0; col < 128; ++col)
		{
			//Column address should increment automatically after write
			LCDHW_Write8(1, lcd->LCD_buffer[(col + page*128)]); //Write data to pixel column
		}
		
	}
}

/**********************************************************************
* Purpose: Displays LD19 distance data on DE10-Standard's LCD
* Precondition:
*		   Function is called and passed pointer to lcd struct,
*			start angle of data in 0.01 deg, end angle in 0.01 deg,
*			and a pointer to a buffer holding the ditance data
*
* Postcondition:
*		   Data in buffer is displayed on LCD in directions specified by start and
*			end angle. Displays up to a max distance specified in header file.
************************************************************************/
void myLCD_DisplayData(LCD_Dev* lcd, uint16_t startAngle, uint16_t endAngle, uint16_t* data)
{
	printf("StartAngle: %d, EndAngle: %d\r\n", startAngle, endAngle);
	float beginAngle = ((float)(startAngle) / 100.0f) * DEG_TO_RAD;		//Convert from .01 deg to deg. Var for angle to begin displaying
	float stopAngle = ((float)(endAngle) / 100.0f) * DEG_TO_RAD;		//Convert from .01 deg to deg. Var for end angle of display
	float deltaAngle = stopAngle - beginAngle;							//Var for change in angle b/w measurements
	uint16_t x = 0;														//Var for x coord of LCD
	uint16_t y = 0;														//Var for y coord of LCD
	
	if(deltaAngle < 0)		//Only place where delta is - is when completing a rotation
		deltaAngle += 360.0f;
	
	deltaAngle = deltaAngle/11.0f;
	
	for(uint8_t i = 0; i < 12; ++i)
	{
		//Clear lines
  		for(uint8_t r = 1; r < 33; ++r)
		{
			x = round(r * sinf(beginAngle) + (lcd->width/2));//switch sin and cos since 0 deg is vertical
			y = round(r * cosf(beginAngle) + (lcd->height/2));
			DRAW_Pixel2(lcd, x, y, WHITE);
		}  
		
		if(data[i] <= MAX_DISPLAY_DIST)
		{
			//Get location of obj
			x = (uint16_t)(round(fabs((lcd->width/2) + ((float)(data[i]) * sinf(beginAngle)) * ((float)(lcd->height) / (float)(MAX_DISPLAY_DIST)))));
			y = (uint16_t)(round(fabs((lcd->height/2) + ((float)(data[i]) * cosf(beginAngle)) * ((float)(lcd->height) / (float)(MAX_DISPLAY_DIST)))));
			printf("X: %d, Y: %d, Begin: %0.3f, End: %0.3f, Delta: %0.3f\r\n", x, y, beginAngle, stopAngle, deltaAngle);
			//Draw obj at location
			DRAW_Pixel2(lcd, x, y, BLACK);
		}
		beginAngle += deltaAngle;
	}
	
}

/**********************************************************************
* Purpose: Modified version of DRAW_Pixel from LCD demonstration in DE10 CD.
			Directly draws a pixel on LCD at specified coordinates
* Precondition:
*		   Function called and passed lcd struct pointer, x and y coords, and color.
*		   Only colors are BLACK and WHITE.
* Postcondition:
*		   Pixel at (x,y) is written to on the LCD 
************************************************************************/
void DRAW_Pixel2(LCD_Dev* pCanvas, int X, int Y, int Color){//Want to combine draw pixel and frame funcs
    int nLine;				//Var for line number
    uint8_t *pFrame, Mask;	//Vars for byte and byte mask of LCD (1 bit/pixel so need to write to a specific bit)

	myLCD_SetDrawAddress(pCanvas, X, Y);
    nLine = Y >> 3; //Y/8;
    Mask = 0x01 << (Y % 8);
    pFrame = pCanvas->LCD_buffer + pCanvas->width*nLine + X;
    if (Color == 0x00)
        *pFrame &= ~Mask;
    else
        *pFrame |= Mask;
	
	LCDHW_Write8(1, *pFrame);
}
