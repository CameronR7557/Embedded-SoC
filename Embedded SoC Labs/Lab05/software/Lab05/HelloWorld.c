/*************************************************************
* Name:			Cameron Robinson
**************************************************************
* Author:		Troy Scevers 
* Filename:		HelloWorld.c
* Date Created:	11/7/23
* Modifications:
**************************************************************/
/*************************************************************
*
* Lab/Assignment: Lab 05
*
* Overview: This program is made for the DE10-Standard HPS. When the program runs,
			it blinks all 10 LEDs on the DE10-Standard on for 1 second before turning
			them off again. 
*
* Input: Run program
* Output: LEDs on DE10-Standard blink on for one second, then turn off
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

int main(void)
{
	int retVal = 0;
	int fd = 0;
	void * virtual_base = NULL;
	void * led_addr = NULL;
	
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
			//Calc LED base addr
			led_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + LEDS_BASE) & (unsigned long)(HW_REGS_MASK));
			
			*(uint32_t*) led_addr = 0x3FF;	//Turn on LEDs
			usleep(1000 * 1000);			//Sleep 1 second
			*(uint32_t*) led_addr = 0x000;	//Turn off LEDs
			
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