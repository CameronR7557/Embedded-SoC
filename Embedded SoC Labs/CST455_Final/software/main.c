/*************************************************************
* Author:		Cameron Robinson
* Filename:		main.c
* Date Created:	12/8/23
* Modifications: 12/10/23 Added custom pattern. Fixed issues with other code.
**************************************************************/
/*************************************************************
*
* Lab/Assignment: CST 455 Final
*
* Overview: 
* This project handles inputs from the DE10-Standard's switches and pushbuttons and outputs
* to the board's six 7-segment displays and the LEDs. There are four different functions 
* performed depending on the pushbutton selected. KEY0 uses SW3 - SW0 and SW7 - SW4 as two input
* numbers to perform math operations on. SW9 - SW8 select which operation to perform. The operations
* include add, subtract, multiply, and blank the hex displays. The input numbers and the result of the
* math operations are displayed on the 7-segs. KEY1 uses SW3 - SW0 as an input value into a Fibonacci
* sequence calculator and outputs the result on the 7-segs. KEY2 blanks the 7-segs and performs the 
* Cylon pattern on the LEDs. KEY3 does a custom pattern using both the 7-seg displays and the LEDs.
* This pattern is called Cylon Pulse since the LEDs perform the Cylon pattern but also 
* light up the 7-segs in a snaking pattern as the lights pass them. 
*
* Inputs: KEY3 - KEY0, SW9 - SW0
* Outputs: HEX5 - HEX0, LED9 -LED0  
*
************************************************************/

//Includes
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <math.h>
#include "hwlib.h"
#include "socal/socal.h"
#include "socal/hps.h"
#include "socal/alt_gpio.h"
#include "hps_0.h"
#include "taskFunctions.h"

//Defines
#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

//Variables
void * sw_addr = NULL;						//Address for switches 
void * pb_addr = NULL;						//Address for pushbuttons
pthread_mutex_t lock_switch;				//Mutex lock for switch task
pthread_mutex_t lock_pb;					//Lock for pushbutton task
uint16_t shared_sw_vals = 0;				//Shared variable for switch values
uint8_t shared_pb_vals = 0;					//Shared variable for pushbutton values

//Function Declarations
static void* SwitchTask(void* arg);
static void* PushbuttonTask(void* arg);

int main(void)
{
	int retVal = 0;					//var to store main return value
	int fd = 0;						//file descriptor
	uint8_t pb_vals = 0;			//var to store state of switches
	uint16_t sw_vals = 0;			//var to hold switch values
	uint8_t result;					//result of math operations
	uint8_t num1;					//Number read from SW3-SW0
	uint8_t num2;					//Number read from SW7-SW4
	uint8_t operation;				//Number read from SW9-SW8
	uint16_t displayVal = 0;		//Value to display on LEDs or HEX displays
	uint8_t startCylSeq = 1;		//Flag var for cylon seq
	uint8_t seqFlags = 0;			//Flag to switch b/w left and right shift for cylon
	pthread_t switch_id;			//Thread for switch task
	pthread_t pb_id;			   	//Thread for pushbutton task
	
	//Base addr variables
	void * virtual_base = NULL;		//Base address
	void * hex01_addr = NULL;		//HEX1-HEX0 decoder address
	void * hex23_addr = NULL;		//HEX3-HEX2 decoder address
	void * hex45_addr = NULL;		//HEX5-HEX4 decoder address
	void * led_addr = NULL;			//LED address
	void * fibSeq_addr = NULL;		//Fibonacci seq module address

	printf("Starting Final Project Program\r\n");
	
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
			fibSeq_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + FIBONACCISEQ_0_BASE) & (unsigned long)(HW_REGS_MASK));
			pb_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + PUSHBUTTONS_0_BASE) & (unsigned long)(HW_REGS_MASK));
			led_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + LEDS_0_BASE) & (unsigned long)(HW_REGS_MASK));
			sw_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + SWITCHES_0_BASE) & (unsigned long)(HW_REGS_MASK));
			hex01_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + HEX01_BASE) & (unsigned long)(HW_REGS_MASK));
			hex23_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + HEX23_BASE) & (unsigned long)(HW_REGS_MASK));
			hex45_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + HEX45_BASE) & (unsigned long)(HW_REGS_MASK));
			
			//Init/Start threads and mutexes
			if(pthread_mutex_init(&lock_switch, NULL) != 0)
			{
				printf("Failed to create mutex.\r\n");
				retVal = 1;
			}
			if(pthread_create(&switch_id, NULL, &SwitchTask, NULL) != 0)
			{
				 printf("Failed to create thread.\r\n");
				 retVal = 1;
			}
			
			if(pthread_mutex_init(&lock_pb, NULL) != 0)
			{
				printf("Failed to create mutex.\r\n");
				retVal = 1;
			}
			if(pthread_create(&pb_id, NULL, &PushbuttonTask, NULL) != 0)
			{
				 printf("Failed to create thread.\r\n");
				 retVal = 1;
			}
			
			while(!retVal)
			{
				pthread_mutex_lock(&lock_pb);
				pb_vals = shared_pb_vals;
				pthread_mutex_unlock(&lock_pb);
				
				if(!(pb_vals & 0b0100))//Reset cylon sequence flag if not doing cylon
				{
					startCylSeq = 1;
				}
				
				if(pb_vals & 0b0001)//Blank Hex / Add / Sub / Multiply
				{
					*(uint32_t*)led_addr = 0;
					pthread_mutex_lock(&lock_switch);
					sw_vals = shared_sw_vals;
					pthread_mutex_unlock(&lock_switch);
					
					num1 = sw_vals & 0x00F;
					num2 = (sw_vals >> 4) & 0x0F;
					operation = (sw_vals >> 8) & 0x03;
					
					if(operation == 0b00)
					{
						*(uint32_t*) hex01_addr = 0xFFFFFFFF;
						*(uint32_t*) hex23_addr = 0xFFFFFFFF;
						*(uint32_t*) hex45_addr = 0xFFFFFFFF;
					}
					else if(operation == 0b01)
					{
						result = num1 + num2;
					}
					else if(operation == 0b10)
					{
						result = abs(num1 - num2);
					}
					else if(operation == 0b11)
					{
						result = num1 * num2;
					}
					
					if(operation)
						displayBCD(hex01_addr, hex23_addr, hex45_addr, num1, num2, result);
					usleep(1000 * 50);//sleep 50ms
				}
				else if(pb_vals & 0b0010)//Fibonacci Sequence
				{
					*(uint32_t*) led_addr = 0x000;
					
					pthread_mutex_lock(&lock_switch);
					sw_vals = (shared_sw_vals & 0x00F);
					pthread_mutex_unlock(&lock_switch);
					
					if(sw_vals > 0)	//Fibonacci seq calculates to at least 1 since initial conditions are a0 = 0 and a1 = 1
					{
						*(uint32_t*)fibSeq_addr = 0x00F & sw_vals;
						fibSeq_addr = (uint32_t)0x1 + (uint32_t*)fibSeq_addr;
						
						*(uint32_t*)fibSeq_addr = 1;
						fibSeq_addr = (uint32_t)0x1 + (uint32_t*)fibSeq_addr;
						
						while(!(*(uint32_t*)fibSeq_addr));//Wait for calculation to be done
						fibSeq_addr = (uint32_t)0x1 + (uint32_t*)fibSeq_addr;
						
						displayVal = *(uint32_t*)fibSeq_addr;
						fibSeq_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + FIBONACCISEQ_0_BASE) & (unsigned long)(HW_REGS_MASK));//Reset address to 0
						displayBCD(hex01_addr, hex23_addr, hex45_addr, 0x00, ((uint8_t)(displayVal/100)), (displayVal % 100));
					}
					else//Turn off hex displays if trying to calc to 0
					{
						*(uint32_t*) hex01_addr = 0xFFFFFFFF;
						*(uint32_t*) hex23_addr = 0xFFFFFFFF;
						*(uint32_t*) hex45_addr = 0xFFFFFFFF;
					}
					
					usleep(1000 * 100);//sleep 100ms
				}
				else if(pb_vals & 0b0100)//Cylon
				{
					if(startCylSeq)
					{
						displayVal = 3;
						startCylSeq = 0;
						seqFlags = 1;
						
						//Blank hex displays
						*(uint32_t*) hex01_addr = 0x3FF;
						*(uint32_t*) hex23_addr = 0x3FF;
						*(uint32_t*) hex45_addr = 0x3FF;
					}

					*(uint32_t*)led_addr = displayVal;
					
					displayVal = cylonShift(displayVal, &seqFlags, 0x300, 3);
					
					usleep(1000 * 75);//sleep 75ms
				}
				else if(pb_vals & 0b1000)//Custom Pattern
				{
					cylonPulse((uint32_t*) hex01_addr, (uint32_t*) hex23_addr, (uint32_t*) hex45_addr, led_addr);
					usleep(1000 * 50);
				}
				
				
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
* Purpose: Task function for reading and sending the pushbutton values to main task

* Precondition: Thread created and sent to function. Pushbutton addresses assigned properly
*
* Postcondition: Task is created and stores PB values in a shared variable
************************************************************************/
static void* PushbuttonTask(void* arg)
{
	uint8_t pb_vals = 0;									//Variable for pushbutton values
	while(1)
	{
		pb_vals = ~(*(uint32_t*)pb_addr) & 0x0F;			//Read values of pushbuttons
		while((~(*(uint32_t*)pb_addr) & 0x0F) && pb_vals);
		
		if(pb_vals > 0)
		{
			pthread_mutex_lock(&lock_pb);
			shared_pb_vals = pb_vals;
			pthread_mutex_unlock(&lock_pb);
		}
		
		usleep(1000 * 50);
	}
	return NULL;
}

/**********************************************************************
* Purpose: Task function for reading and sending the switch values to main task

* Precondition: Thread created and sent to function. Switch addresses assigned properly
*
* Postcondition: Task is created and stores switch values in a shared variable
************************************************************************/
static void* SwitchTask(void* arg)
{
	uint16_t sw_vals = 0;									//Variable to store switch values
	
	while(1)
	{
		sw_vals = (*(uint32_t*)sw_addr) & 0x3FF;			//Read values of switches
	    usleep(10000);										//Wait 10ms
		if(sw_vals == ((*(uint32_t*)sw_addr) & 0x3FF))		//Check if switch values are the same (Debounce)
		{
			pthread_mutex_lock(&lock_switch);
			shared_sw_vals = sw_vals;
			pthread_mutex_unlock(&lock_switch);
		}
		usleep(1000 * 10);
		
	}
	return NULL;
}