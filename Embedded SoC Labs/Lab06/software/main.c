/*************************************************************
* Author:		Cameron Robinson
* Filename:		main.c
* Date Created:	11/14/23
* Modifications:
**************************************************************/
/*************************************************************
*
* Lab/Assignment: Lab 06
*
* Overview: Reads in the values of the 10 toggle switches on the DE10-Standard
*			and displays the values as  hexidecimal values on three 7-segment displays.
*			The the state of the switches is also written to the LEDs.
* Input: SW0 - SW9
* Output: Hex representation of the switches on the HEX0 - HEX2.
*		  Binary representation on the LEDs.
*
************************************************************/

//Includes
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "hwlib.h"
#include "socal/socal.h"
#include "socal/hps.h"
#include "socal/alt_gpio.h"
#include "hps_0.h"

//Defines
#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

//Function Declarations
void decodeToSevenSegs(uint32_t* hex, uint8_t segs);

int main(void)
{
	int retVal = 0;					//var to store main return value
	int fd = 0;						//file descriptor
	uint16_t sw_vals = 0;			//var to store state of switches
	
	//Base addr variables
	void * virtual_base = NULL;
	void * led_addr = NULL;
	void * sw_addr = NULL;
	void * hex0_addr = NULL;
	void * hex1_addr = NULL;
	void * hex2_addr = NULL;
	void * hex3_addr = NULL;
	void * hex4_addr = NULL;
	void * hex5_addr = NULL;
	
	printf("Hello World!\r\n");
	
	if((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1)
	{
		printf("ERROR: Could not open \"/dev/mem\"...\r\n");
		retVal = 1;
	}
	else
	{
		virtual_base = mmap(NULL, HW_REGS_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, HW_REGS_BASE);
		
		if(virtual_base == MAP_FAILED)
		{
			printf("ERROR mmap() failed\r\n");
			close(fd);
			retVal = 1;
			
		}
		else
		{
			//Calc base addresses
			led_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + LEDS_BASE) & (unsigned long)(HW_REGS_MASK));
			sw_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + SWITCHES_BASE) & (unsigned long)(HW_REGS_MASK));
			hex0_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + HEX0_BASE) & (unsigned long)(HW_REGS_MASK));
			hex1_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + HEX1_BASE) & (unsigned long)(HW_REGS_MASK));
			hex2_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + HEX2_BASE) & (unsigned long)(HW_REGS_MASK));
			hex3_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + HEX3_BASE) & (unsigned long)(HW_REGS_MASK));
			hex4_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + HEX4_BASE) & (unsigned long)(HW_REGS_MASK));
			hex5_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + HEX5_BASE) & (unsigned long)(HW_REGS_MASK));
			
			//Make sure HEX3-HEX5 are turned off
			*(uint32_t*) hex3_addr = 0x7F;
			*(uint32_t*) hex4_addr = 0x7F;
			*(uint32_t*) hex5_addr = 0x7F;
			
			while(1)
			{
				sw_vals = (*(uint32_t*)sw_addr) & 0x3FF;						       //Read values of switches
				usleep(10000);													   	   //Wait 10ms
				if(sw_vals == ((*(uint32_t*)sw_addr) & 0x3FF))					   	   //Check if switch values are the same (Debounce)
				{
					*(uint32_t*) led_addr = sw_vals;								   //Set LEDs to switch values
					decodeToSevenSegs((uint32_t*) hex0_addr, (sw_vals & 0x0F)); 	   //Decode and set HEX0
					decodeToSevenSegs((uint32_t*) hex1_addr, ((sw_vals >> 4) & 0x0F)); //Decode and set HEX1
					decodeToSevenSegs((uint32_t*) hex2_addr, ((sw_vals >> 8) & 0x03)); //Decode and set HEX2
				}
				
				usleep(1000 * 25);											           //Sleep .025 seconds
			}
			//Cleanup
			if(munmap(virtual_base, HW_REGS_SPAN) != 0)
			{
				printf("ERROR: munmap() failed...\r\n");
				retVal = 1;
			}
			
			close(fd);
		}
		
	}
	
	return retVal;
}

/**********************************************************************
* Purpose: Decodes hex values into 7-segment display equivalents and
* 		   displays them on the specified 7-segment display.
*
* Precondition:
*		   Function is called. Pointer is valid for display.
*
* Postcondition:
*		   Specified 7-seg display displays the number passed
*		   as the second parameter.
************************************************************************/
void decodeToSevenSegs(uint32_t* hex, uint8_t num)
{
	if(hex != NULL)
	{
		switch(num)		//Decode num into seven-seg equivalent
		{
			case 0:
				*hex = 0b01000000;
			break;
			case 1:
				*hex = 0b01111001;
			break;
			case 2:
				*hex = 0b00100100;
			break;
			case 3:
				*hex = 0b00110000;
			break;
			case 4:
				*hex = 0b00011001;
			break;
			case 5:
				*hex = 0b00010010;
			break;
			case 6:
				*hex = 0b00000010;
			break;
			case 7:
				*hex = 0b01111000;
			break;
			case 8:
				*hex = 0b00000000;
			break;
			case 9:
				*hex = 0b00010000;
			break;
			case 0xA:
				*hex = 0b00001000;
			break;
			case 0xB:
				*hex = 0b00000011;
			break;
			case 0xC:
				*hex = 0b01000110;
			break;
			case 0xD:
				*hex = 0b00100001;
			break;
			case 0xE:
				*hex = 0b00000110;
			break;
			case 0xF:
				*hex = 0b00001110;
			break;
			default:
				*hex = 0b01111111;
			break;
		}
		
	}
	
}