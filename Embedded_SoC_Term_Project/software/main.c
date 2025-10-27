/*************************************************************
* Author:		Cameron Robinson
* Filename:		main.c
* Date Created:	11/16/23
* Modifications: 11/27/23 - 12/4/23: Implemented LCD and display functions.
*				 12/6/23: Added hardware CRC check
**************************************************************/
/*************************************************************
*
* Lab/Assignment: Term Project
*
* Overview: Receives distance data from an LD19 LiDAR through a custom UART RX module, 
			checks the data for validity using a CRC, parses the data, and displays 
			it on the DE10-Standard's LCD. Also sends general
			direction of the closest object to the 7-segment displays on the DE10-Standard.
* Input: LiDAR distance data
* Output: Direction of closest object on 7-segs (Front, behind, left, right).
*		  Displays distances on LCD screen to indicate where objects are.
************************************************************/

//Includes
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "hwlib.h"
#include "socal/socal.h"
#include "socal/hps.h"
#include "socal/alt_gpio.h"
#include "hps_0.h"
#include "LCD_Hw.h"
#include "myLCD_Driver.h"
#include "ld19.h"


//Defines
#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

//Vars
static const uint8_t fwd_hex[6] = {0xff, 0xf, 27, 24, 23, 29}; 			//Front (w doesn't work on 7segs, so can't do fwd)
static const uint8_t behind_hex[6] = {0xb, 0xe, 17, 18, 23, 0xd};		//behind
static const uint8_t left_hex[6] = {0xff, 0xff, 21, 0xe, 0xf, 29};  	//Left
static const uint8_t right_hex[6] = {0xff, 27, 18, 16, 17, 29}; 		//Right
static const uint8_t error_hex[6] = {0xff, 0xe, 27, 27, 24, 27}; 		//Error

pthread_mutex_t lock;				//Mutex lock for shared buffer b/w uart function and main
uint8_t packetReady = 0;			//Shared variable to indicate data packet is valid
uint8_t sharedBuffer[47] = {0};		//Shared buffer holding data packet

//Base addr variables
void * hex0_addr = NULL;			//Base address ptr for HEX0
void * hex1_addr = NULL;			//Base address ptr for HEX1
void * hex2_addr = NULL;			//Base address ptr for HEX2
void * hex3_addr = NULL;			//Base address ptr for HEX3
void * hex4_addr = NULL;			//Base address ptr for HEX4
void * hex5_addr = NULL;			//Base address ptr for HEX5
void * virtual_base = NULL;			//Base virtual address
void * uart_addr = NULL;			//Base address ptr for UART module



//Function Declarations
static void* uart_task(void* arg);
void displaySmallestDistance(float dir);

int main(void)
{
	uint8_t redisplay = 0;
	int retVal = 0;										//var to store main return value
	int fd = 0;											//file descriptor
	uint16_t smallestDistance = 0xFFFF;					//Smallest distance detected by LiDAR
	float direction = 0;								//Direction of current measurement
	float smallestDir = 0;								//Direction of smallest distance 
	uint8_t lcd_buffer[1024] = {0};						//Array for storing LCD values
	LCD_Dev lcd = {128, 64, 1024, lcd_buffer, 0, 0, 0}; //Struct for LCD 
	uint8_t waitingForPacket = 1;						//Flag for switching b/w waiting for LiDAR data and displaying it
	void * crc_addr = NULL;								//Base address ptr for CRC module 
	
	uint16_t dataPacket[14] = {0};						//Parsed distance and direction data
	uint8_t crc = 0;									//var to hold calculated SW crc
	uint8_t crc_hw = 0;									//var to hol calculated HW crc
	uint8_t dataValid = 0;								//Flag for whether data crc matched calculated crc
	uint8_t lpacket[47] = {0};							//Raw packet data buffer
	pthread_t uart_id;									//Thread for uart task
	
	printf("LD19 Display Program Running\r\n");
	
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
			hex0_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + SEVENSEGDECODER_0_BASE) & (unsigned long)(HW_REGS_MASK));
			hex1_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + SEVENSEGDECODER_1_BASE) & (unsigned long)(HW_REGS_MASK));
			hex2_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + SEVENSEGDECODER_2_BASE) & (unsigned long)(HW_REGS_MASK));
			hex3_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + SEVENSEGDECODER_3_BASE) & (unsigned long)(HW_REGS_MASK));
			hex4_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + SEVENSEGDECODER_4_BASE) & (unsigned long)(HW_REGS_MASK));
			hex5_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + SEVENSEGDECODER_5_BASE) & (unsigned long)(HW_REGS_MASK));
			uart_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + UART_RX_0_BASE) & (unsigned long)(HW_REGS_MASK));
			crc_addr = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + CRC_0_BASE) & (unsigned long)(HW_REGS_MASK));
			
			//Init LCD
			LCDHW_Init(virtual_base);
			LCDHW_BackLight(true);
			myLCD_Init(&lcd, 0, 0);
			printf("Clearing screen\r\n");
			myLCD_FillScreen(&lcd);
			
			//Init HEX displays
			*(uint32_t*) hex5_addr = 0xff;
			*(uint32_t*) hex4_addr = 0xff;
			*(uint32_t*) hex3_addr = 0xff;
			*(uint32_t*) hex2_addr = 0xff;
			*(uint32_t*) hex1_addr = 0xff;
			*(uint32_t*) hex0_addr = 0xff;
			
			//Init/Start threads and mutexes
			if(pthread_mutex_init(&lock, NULL) != 0)
			{
				printf("Failed to create mutex.\r\n");
				retVal = 1;
			}
			if(pthread_create(&uart_id, NULL, &uart_task, NULL) != 0)
			{
				 printf("Failed to create thread.\r\n");
				 retVal = 1;
			}
				 
			
			while(retVal != 1)
			{
				while(!dataValid)
				{
					while(waitingForPacket)
					{
						pthread_mutex_lock(&lock);
						if(packetReady)
						{
							for(uint8_t i = 0; i < PACKET_LENGTH; ++i)
							{
								lpacket[i] = sharedBuffer[i];
							}
							packetReady = 0;
							waitingForPacket = 0;
						}
						pthread_mutex_unlock(&lock);
					}
					
					
					//Send frame to CRC and read results (if invalid, throw out and restart)
					//Get SW CRC
 					crc = CalCRC8(lpacket, 46);
					
					//Get HW CRC
					for(uint8_t i = 0; i < 47; i+=4)
					{
						if(i < 44)
							*(uint32_t*)crc_addr = ( lpacket[i+3] << 24)|( lpacket[i+2] << 16)|( lpacket[i+1] << 8)|(lpacket[i]);
						else
							*(uint32_t*)crc_addr = ( 0x00 << 24)|( lpacket[i+2] << 16)|( lpacket[i+1] << 8)|(lpacket[i]);
					}
					
					while((*(uint32_t*)crc_addr & 0x200) != 0x200);
					
					crc_hw = (0xff & (*(uint16_t*)crc_addr));
					
					printf("Packet CRC: %d\r\nSoftware CRC: %d\r\nHardware CRC: %d\r\n", lpacket[46], crc, crc_hw);
					
					if(crc_hw == crc)
						printf("HW CRC Correct\r\n");

					//Make sure packet data is valid
					if(crc == lpacket[46])
					{
						printf("Data Valid \r\n");
						dataValid = 1;
					}
					else
					{
						printf("Data Invalid \r\n");
						dataValid = 0;
					}
					waitingForPacket = 1;
					
				}
				
				//Parse frame and only keep distance data, start angle, and stop angle
				getLiDARMeasurements(lpacket, dataPacket);
				
				//Check if smallest distance is smaller than stored smallest (init to max int)
						//if smaller, store new smallest distance and the angle
				redisplay = 0;
				for(uint8_t i = 2; i < 14; ++i)
				{
					direction = (float)(dataPacket[1] - dataPacket[0]);
					if(direction < 0)
						direction += 360.0f;
					direction = (direction / 1100.0f) * (i - 2) + (float)(dataPacket[0])/100.0f; //deltaAngle * measurementNumber + startAngle = currentAngle
					
					if(dataPacket[i] <= smallestDistance)
					{
						smallestDistance = dataPacket[i];
						smallestDir = direction;
						redisplay = 1;
					}
					else if(round(smallestDir) == round(direction))
					{
						smallestDistance = dataPacket[i];
					}
					
				}
				printf("Smallest: %d, Dir: %0.3f\r\n", smallestDistance, direction);
				
				//Send direction of smallest distance to 7SegDecoders
				if(redisplay)
				{
					displaySmallestDistance(direction);
				}
				
				//Store new distances in array
				myLCD_DisplayData(&lcd, dataPacket[0], dataPacket[1], &dataPacket[2]);
				dataValid = 0;
				
				usleep(1000 * 25);	//Sleep .025 seconds
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
* Purpose: Read bytes of lidar data in from UART module and store in a packet.
*				Once complete, stores packet in a shared buffer.
* Precondition:
*		   Thread is started by main.
*
* Postcondition:
*		   Reads bytes in and stores in 47-byte buffer
************************************************************************/
static void* uart_task(void* arg)
{
	uint8_t lidarPacket[47] = {0};		//array to store raw packet data
	uint16_t lidarByte;					//data read from UART. 8-bits of data + 2-bits for status
	uint8_t packetIndex = 0;			//Index var for storing 47-byte packet of lidar data
	
	while(1)
	{
		lidarPacket[0] = 0;
		lidarPacket[1] = 0;
		//Read LiDAR Data from UART RX (into header)
		while((lidarPacket[0] != PACKET_HEADER) || (lidarPacket[1] != PACKET_VERSION) || (lidarPacket[3] != 0xe))
		{
			while((!(lidarByte & 0x100) || (lidarByte & 0x200)) || ((lidarByte & 0x0ff) != PACKET_HEADER))//Blocking. Waiting for data to be ready
			{
				//Read header into lidarByte
				lidarByte = (uint32_t)(*(uint16_t*)uart_addr & 0x3FF);
				
			}
			
			lidarPacket[0] = (uint8_t)(0xFF & lidarByte);
			
			do
			{
				lidarByte = (uint32_t)(*(uint16_t*)uart_addr & 0x3FF);
			}
			while(!(lidarByte & 0x100) || (lidarByte & 0x200));
			
			lidarPacket[1] = (uint8_t)(0xFF & lidarByte);
			
			do
			{
				lidarByte = (uint16_t)(*(uint32_t*)uart_addr & 0x3FF);
			}
			while(!(lidarByte & 0x100) || (lidarByte & 0x200));
			
			lidarPacket[2] = (uint8_t)(0xFF & lidarByte);
			
			do
			{
				lidarByte = (uint16_t)(*(uint32_t*)uart_addr & 0x3FF);
			}
			while(!(lidarByte & 0x100) || (lidarByte & 0x200));
			
			lidarPacket[3] = (uint8_t)(0xFF & lidarByte);
						
		}
		
		for(packetIndex = 4; packetIndex < 47; packetIndex++)
		{
			do
			{ 
				lidarByte = (uint16_t)((*(uint32_t*)uart_addr) & 0x3FF);
			}
			while(!(lidarByte & 0x100) || (lidarByte & 0x200));//While not valid
			
			lidarPacket[packetIndex] = (uint8_t)(0xFF & lidarByte);
			
		} 
		
		pthread_mutex_lock(&lock);
		for(uint8_t j = 0; j < 47; ++j)
		{
			sharedBuffer[j] = lidarPacket[j];
		}
		packetReady = 1;
		pthread_mutex_unlock(&lock);

	}
	
	return NULL;
}

/**********************************************************************
* Purpose: Sends values to 7-seg decoders to indicate direction of smallest distance
*
* Precondition:
*		   Function is called and passed direction of smallest distance
*
* Postcondition:
*		   Depending on direction, sends hex values for Front, Behind,
			Left, and Right to the 7-seg decoders.
************************************************************************/
void displaySmallestDistance(float dir)
{
	if((dir > 315.0f && dir < 360.0f) || (dir > 0.0f && dir < 45.0f))
	{
		//Forward
		*(uint32_t*) hex5_addr = fwd_hex[0];
		*(uint32_t*) hex4_addr = fwd_hex[1];
		*(uint32_t*) hex3_addr = fwd_hex[2];
		*(uint32_t*) hex2_addr = fwd_hex[3];
		*(uint32_t*) hex1_addr = fwd_hex[4];
		*(uint32_t*) hex0_addr = fwd_hex[5];
	}
	else if(dir <= 315.0f && dir >= 225.0f)
	{
		//Left
		*(uint32_t*) hex5_addr = left_hex[0];
		*(uint32_t*) hex4_addr = left_hex[1];
		*(uint32_t*) hex3_addr = left_hex[2];
		*(uint32_t*) hex2_addr = left_hex[3];
		*(uint32_t*) hex1_addr = left_hex[4];
		*(uint32_t*) hex0_addr = left_hex[5];
	}
	else if(dir >= 45.0f && dir <= 135.0f)
	{
		//Right
		*(uint32_t*) hex5_addr = right_hex[0];
		*(uint32_t*) hex4_addr = right_hex[1];
		*(uint32_t*) hex3_addr = right_hex[2];
		*(uint32_t*) hex2_addr = right_hex[3];
		*(uint32_t*) hex1_addr = right_hex[4];
		*(uint32_t*) hex0_addr = right_hex[5];
	}
	else if(dir > 135.0f && dir < 225.0f)
	{
		//Backward
		*(uint32_t*) hex5_addr = behind_hex[0];
		*(uint32_t*) hex4_addr = behind_hex[1];
		*(uint32_t*) hex3_addr = behind_hex[2];
		*(uint32_t*) hex2_addr = behind_hex[3];
		*(uint32_t*) hex1_addr = behind_hex[4];
		*(uint32_t*) hex0_addr = behind_hex[5];
	}
	else
	{
		//Error
		*(uint32_t*) hex5_addr = error_hex[0];
		*(uint32_t*) hex4_addr = error_hex[1];
		*(uint32_t*) hex3_addr = error_hex[2];
		*(uint32_t*) hex2_addr = error_hex[3];
		*(uint32_t*) hex1_addr = error_hex[4];
		*(uint32_t*) hex0_addr = error_hex[5];
	}
	
}