/*************************************************************
* Author:		Cameron Robinson
* Filename:		main.c
* Date Created:	10/18/23
* Modifications:
**************************************************************/
/*************************************************************
*
* Lab/Assignment: Lab 03
*
* Overview: This program reads switches on the DE10-Standard, converts them to hex values,
* 			and displays the hex values on the DE10-Standard 7-seg displays. The displays
* 			refresh every 0.1 seconds.
*
* Input: All 10 switches on DE10-Standard. Switches are grouped from right to left
* 		 with each switch acting as a bit.
* Output: Displays hex values corresponding to the switches on 7-seg displays.
* 		  HEX0 displays the value of SW0-SW3, HEX1 displays the value of SW4-SW7,
* 		  and HEX2 displays the value of SW8-SW9.
*
************************************************************/

//Includes:
#include "sys/alt_stdio.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "stdint.h"

//Function declarations:
void displayValue(uint8_t val, uint16_t address_base);

int main()
{ 
	uint16_t sw_vals = 0;						//Var to store switch values

	printf("Hello from Nios II!\n");

	/* Event loop never exits. */
	while (1)
	{
		sw_vals = 0;
		//Read Switches
		sw_vals = IORD_ALTERA_AVALON_PIO_DATA(SW_BASE);

		//Display Switch Values
		displayValue((sw_vals & 0x000F), DISPLAY0_BASE);
		displayValue(((sw_vals >> 4) & 0x000F),DISPLAY1_BASE);
		displayValue(((sw_vals >> 8) & 0x0003),DISPLAY2_BASE);

		//Sleep for 0.1 seconds
		usleep(100000);
	}

	return 0;
}

/**********************************************************************
* Purpose: Decodes hex values into 7-segment display equivalents and
* 		   displays them on the specified 7-segment display.
*
* Precondition:
*		   Function is called. Address base is valid for display.
*
* Postcondition:
*		   Specified 7-seg display displays the hex value passed
*		   as the first parameter, val.
************************************************************************/
void displayValue(uint8_t val, uint16_t address_base)
{
	uint8_t segs = 0;			//Var to store 7-seg values

	switch(val)	//Decodes hex value to 7-seg display equivalent
	{
	case 0:
		segs = 0b01000000;
		break;
	case 1:
		segs = 0b01111001;
		break;
	case 2:
		segs = 0b00100100;
		break;
	case 3:
		segs = 0b00110000;
		break;
	case 4:
		segs = 0b00011001;
		break;
	case 5:
		segs = 0b00010010;
		break;
	case 6:
		segs = 0b00000010;
		break;
	case 7:
		segs = 0b01111000;
		break;
	case 8:
		segs = 0b00000000;
		break;
	case 9:
		segs = 0b00010000;
		break;
	case 10:
		segs = 0b00001000;
		break;
	case 11:
		segs = 0b00000011;
		break;
	case 12:
		segs = 0b01000110;
		break;
	case 13:
		segs = 0b00100001;
		break;
	case 14:
		segs = 0b00000110;
		break;
	case 15:
		segs = 0b00001110;
		break;
	default:
		segs = 0b01111111;
		break;
	}

	IOWR_ALTERA_AVALON_PIO_DATA(address_base, segs); //Write value to segments
}
