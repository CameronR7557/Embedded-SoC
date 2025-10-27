/*************************************************************
* Author:		Cameron Robinson
* Filename:		main.c
* Date Created:	10/27/23
* Modifications:
**************************************************************/
/*************************************************************
*
* Lab/Assignment: Lab 04
*
* Overview: This program reads four pushbuttons on the DE10-Standard and illuminates the
* 			board's 10 LEDs in a specific pattern for each pushbutton.
* 			The patters are as follows:
* 			KEY0 -> Cylon
* 			KEY1 -> Up Counter
* 			Key2 -> Blink
* 			Key3 -> TBird Tail Light Sequence
*
* Input: Any of the four pushbuttons labeled KEY0 - KEY3
* Output: LED sequences in one of the four specific patterns mentioned above.
*
************************************************************/

//Includes
#include <stdio.h>
#include <stdint.h>
#include <sys/alt_irq.h>
#include <system.h>
#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>
#include "altera_avalon_pio_regs.h"

//Function Declarations
void taskLEDControl (void* p);
void taskReadPBs (void* p);

//Variable Declarations
QueueHandle_t pushbutton_queue;		//Queue for communication b/w LED tasks and PB task

int main()
{
  printf("Hello from Nios II running FreeRTOS!\n");

  //Create Queues
  pushbutton_queue = xQueueCreate(1, sizeof(uint8_t));	//LED task and PB task queue

  //Create Tasks
  xTaskCreate(taskLEDControl, "LED Task", 512, NULL, 2, NULL);
  xTaskCreate(taskReadPBs, "Pushbutton Task", 512, NULL, 2, NULL);

  //Start Scheduler
  vTaskStartScheduler();

  while(1)//Should not reach here
  {}

  return 0;
}

/**********************************************************************
* Purpose: Task to scan pushbuttons 0 - 3 and send the value correlating
* 			to the buttons pressed to the LED task.
*
* Precondition:
*		   Task is created. Scheduler is running
*
* Postcondition:
*		   Records 4-bit value of which buttons are pressed and sends them
*		   to a queue.
************************************************************************/
void taskReadPBs (void* p)
{
	//PBs are already debounced
	uint8_t pb_num = 0;

	while(1)
	{
		//Scan PBs, negate, and send to queue
		pb_num = (0x0F & (~(IORD_ALTERA_AVALON_PIO_DATA(PUSHBUTTONS_BASE))));//PBs are active low
		if(pb_num != 0)
			xQueueSendToBack(pushbutton_queue, &pb_num, 0);
		vTaskDelay(100);
	}
}

/**********************************************************************
* Purpose: Task that lights up 10 LEDs in a specific pattern depending on the value
* 			received in the task's queue.
*
* Precondition:
*		   Task is created. Scheduler is running.
*
* Postcondition:
*		   Illuminates LEDs in cylon, up counter, blink, or TBird sequences.
************************************************************************/
void taskLEDControl (void* p)
{
	uint8_t pb_num = 0;			//Var to store queue PB value
	uint8_t cur_seq = 0;		//Var to store current LED pattern
	uint16_t displayVal = 0;	//Var to store LED values to be written
	uint8_t startSeq = 1;		//Var to track initial start of patterns
	uint8_t seqFlags = 1;		//Var to track cases within patters (i.e. cylon traveling left/right)
	uint16_t TBSeqL = 0;		//T-bird tail light pattern for left
	uint16_t TBSeqR = 0;		//T-bird tail light pattern for right

	while(1)
	{
		if(xQueueReceive(pushbutton_queue, &pb_num, 0))//Receive from queue
		{
			if(!(pb_num & cur_seq))
			{
				cur_seq = pb_num;
				startSeq = 1;
			}
		}

		switch(cur_seq)//Run specified pattern
		{
		case 1:	//0001 --> Cylon
			if(startSeq)
			{
				displayVal = 3;
				startSeq = 0;
				seqFlags = 1;
			}

			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, displayVal);//Make sure it is fine to send 16bits

			if(seqFlags)//Travel left
			{
				displayVal = (displayVal << 1);
				if(displayVal == 0x300)
					seqFlags = 0;
			}
			else		//Travel right
			{
				displayVal = (displayVal >> 1);
				if(displayVal == 3)
					seqFlags = 1;
			}
			vTaskDelay(75);
			break;
		case 2:	//0010 --> Up Counter
			if(startSeq)
			{
				startSeq = 0;
				displayVal = 0;
			}

			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, displayVal);

			displayVal++;
			if(displayVal == 0x3FF)//Reset counter
			{
				displayVal = 0;
			}
			vTaskDelay(50);
			break;
		case 4:	//0100 --> Blink
			if(startSeq)
			{
				startSeq = 0;
				displayVal = 0;
			}

			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, displayVal);

			displayVal = ~displayVal;	//Toggle LEDs
			vTaskDelay(300);
			break;
		case 8:	//1000 --> TB Tail Light Sequence
			if(startSeq == 1)
			{
				startSeq = 0;
				displayVal = 0;
				seqFlags = 0;
				TBSeqL = 0;
				TBSeqR = 0;
			}

			switch(seqFlags)
			{
			case 0://Left and Right
				TBSeqL |= ((TBSeqL << 1) | 0x1)&0x1F;
				TBSeqR |= ((TBSeqR >> 1) | 0x10)&0x1F;
				displayVal = (((displayVal >> 5) | (TBSeqL)) << 5) | (displayVal | TBSeqR);
				break;
			case 1://Right
				TBSeqR |= ((TBSeqR >> 1) | 0x10)&0x1F;
				displayVal = (0b00000 | ((displayVal)|(TBSeqR)));
				break;
			case 2://Left
				TBSeqL |= ((TBSeqL << 1) | 0x1)&0x1F;
				displayVal = ((((displayVal >> 5) | (TBSeqL)) << 5) | 0b00000);
				break;
			}

			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, displayVal);

			if(TBSeqL == 0x1F || TBSeqR == 0x1F)//Reset sequence
			{
				displayVal = 0;
				TBSeqL = 0;
				TBSeqR = 0;
				if(seqFlags < 2)
					seqFlags++;
				else
					seqFlags = 0;
			}


			vTaskDelay(100);
			break;
		default:
			displayVal = 0;
			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, displayVal);
			vTaskDelay(200);
			break;
		}
	}

}

