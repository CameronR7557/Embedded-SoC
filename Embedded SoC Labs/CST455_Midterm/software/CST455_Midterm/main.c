/*************************************************************
* Author:		Cameron Robinson
* Filename:		main.c
* Date Created:	10/29/23
* Modifications:
**************************************************************/
/*************************************************************
*
* Lab/Assignment: CST 455 Midterm
*
* Date: October 30, 2023
*
* Overview: Program for the DE10-Standard that reads 4 pushbuttons and illuminates
* 			them in different patterns. The patterns include off, cylon, up counter,
* 			and custom. The program also reads 10 switches. SW0-3 and SW4-7
* 			are used as input numbers into a math operation. SW8-9 determine the math
* 			operation being performed (0 - off, 1 - add, 2 - subtract, 3 - multiply).
* 			The values for the input numbers and the result of the operation are
* 			sent to six 7-segment displays.
*
*
* Input:   SW0-9 and KEY0-3
* 		   SW0-3: Input number 1
* 		   SW4-7: Input number 2
* 		   SW8-9: Operation code
* 		   KEY0: LEDs off
* 		   KEY1: Cylon
* 		   KEY2: Up counter
* 		   KEY3: custom pattern (Shuffle)
*
* Output:  Hex0-5 and LED0-9
* 		   HEX4-5: display input number 1
* 		   HEX2-3: display input number 2
* 		   HEX0-1: display result
* 		   LED0-9: Illuminate in specified pattern
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
#include <io.h>

//Function Declarations
void taskLEDControl (void* p);
void taskReadPBs (void* p);
void taskDisplaySevenSeg(void* p);
void taskReadSWs (void* p);

//Variable Declarations
QueueHandle_t pushbutton_queue;		//Queue for communication b/w LED tasks and PB task
QueueHandle_t switch_queue;			//Queue for communication b/w 7Seg tasks and SW task

struct hex_results		//Struct to send through SW queue
{
	uint8_t num1;		//input value for operations
	uint8_t num2;		//input value for operations
	uint8_t result;		//result of operation
	uint8_t operation;	//code of operation
};

int main()
{
  printf("Hello from Nios II running FreeRTOS!\n");

  //Create Queues
  pushbutton_queue = xQueueCreate(1, sizeof(uint8_t));
  switch_queue = xQueueCreate(1, sizeof(struct hex_results));

  //Create Tasks
  xTaskCreate(taskLEDControl, "LED Task", 512, NULL, 2, NULL);
  xTaskCreate(taskReadPBs, "Pushbutton Task", 512, NULL, 2, NULL);
  xTaskCreate(taskReadSWs, "Switch Task", 512, NULL, 2, NULL);
  xTaskCreate(taskDisplaySevenSeg, "7Seg Display Task", 512, NULL, 2, NULL);

  //Start Scheduler
  vTaskStartScheduler();

  while(1)//Should not reach here
  {}

  return 0;
}

/**********************************************************************
* Purpose: Task to display values on 6 seven-segment displays or blank
* 		   all of the displays.
*
* Precondition:
*		   Task is created. Scheduler is running
*
* Postcondition:
*		   Decodes values less than 99 to decimal values and
*		   sends them to 7-deg display. Values > 99 are displayed as hex.
************************************************************************/
void taskDisplaySevenSeg(void* p)
{
	struct hex_results msg = {0, 0, 0, 0};		//Struct to store values to send to queue
	uint8_t displayVals[6] = {0};				//Values to send to 7-seg displays

	while(1)
	{
		if(xQueueReceive(switch_queue, &msg, 0))//Receive from queue
		{

			if(msg.operation > 0)
			{
				displayVals[4] = msg.num1 % 10;
				displayVals[5] = msg.num1/10;
				displayVals[2] = msg.num2 % 10;
				displayVals[3] = msg.num2/10;

				displayVals[0] = msg.result % 10;
				if(msg.result >= 100)//2x 7-segs cannot display decimal value > 99
				{
					displayVals[1] = ((int)(msg.result/10))%10;//Display lowest two digits
					//Most significant value = msg.result / 100
				}
				else
				{
					displayVals[0] = msg.result % 10;//Display values <= 99 in decimal
					displayVals[1] = msg.result/10;
				}
			}
			else
			{
				for(int displayIndex = 0; displayIndex < 6; ++displayIndex)
				{
					displayVals[displayIndex] = 16;
				}
			}

			IOWR(SEVENSEGDECODER_0_BASE, 0, displayVals[0]);
			IOWR(SEVENSEGDECODER_1_BASE, 0, displayVals[1]);
			IOWR(SEVENSEGDECODER_2_BASE, 0, displayVals[2]);
			IOWR(SEVENSEGDECODER_3_BASE, 0, displayVals[3]);
			IOWR(SEVENSEGDECODER_4_BASE, 0, displayVals[4]);
			IOWR(SEVENSEGDECODER_5_BASE, 0, displayVals[5]);
		}
		vTaskDelay(30);
	}
}

/**********************************************************************
* Purpose: Task to scan switches 0 - 9 and send the value correlating
* 			to the switches to the 7-seg display task.
*
* Precondition:
*		   Task is created. Scheduler is running
*
* Postcondition:
*		   Records 10-bit value of which switches are active and sends them
*		   to a queue.
************************************************************************/
void taskReadSWs (void* p)
{
	struct hex_results msg = {0,0,0,0};		//Var to store queue messages
	uint16_t switches = 0;					//Var to store values of switches

	while (1)
	{
		//Read switches
		switches = IORD(SWITCHES_0_BASE, 0);
		vTaskDelay(30);
		if(switches == IORD(SWITCHES_0_BASE, 0))//Debounce
		{
			//Parse 0-3 into num1 and 4-7 into num2
			msg.num1 = (switches & 0x00F);
			msg.num2 = ((switches >> 4) & 0x00F);

			//Parse operation (SW8-9)
			msg.operation = ((switches >> 8) & 0x003);

			//Perform operation and store numbers and result
			switch(msg.operation)
			{
			case 1:		//Add
				msg.result = msg.num1 + msg.num2;
				break;
			case 2:		//Subtract
				msg.result = (abs(msg.num1 - msg.num2));
				break;
			case 3:	    //Multiply
				msg.result = msg.num1 * msg.num2;
				break;
			}
		}

		//Send struct to hex task
		xQueueSendToBack(switch_queue, &msg, 0);
		vTaskDelay(100);
	}
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
	uint8_t pb_num = 0;				//Number to store PB values

	while(1)
	{
		//Scan PBs, negate, and send to queue
		pb_num = (0x0F & (~(IORD(PUSHBUTTONS_0_BASE, 0))));//PBs are active low
		while((0x0F & (~(IORD(PUSHBUTTONS_0_BASE, 0))) && pb_num))
		{}

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
*		   Illuminates LEDs in cylon, up counter, or custom.
*		   Otherwise, LEDs will be off.
************************************************************************/
void taskLEDControl (void* p)
{
	uint8_t pb_num = 0;			//Var to store queue PB value
	uint8_t cur_seq = 0;		//Var to store current LED pattern
	uint16_t displayVal = 0;	//Var to store LED values to be written
	uint8_t startSeq = 1;		//Var to track initial start of patterns
	uint8_t seqFlags = 1;		//Var to track cases within patters (i.e. cylon traveling left/right)
	uint16_t SeqL = 0;			//Var to store custom pattern for left LEDs
	uint16_t SeqR = 0;			//Var to store custom pattern for right LEDs
	uint16_t delay = 0; 		//Var to store delay values

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
		case 2:	//0010 --> Cylon
			if(startSeq)
			{
				displayVal = 3;
				startSeq = 0;
				seqFlags = 1;
			}

			IOWR(LEDS_0_BASE, 0, displayVal);

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
		case 4:	//0100 --> Up Counter
			if(startSeq)
			{
				startSeq = 0;
				displayVal = 0;
			}

			IOWR(LEDS_0_BASE, 0, displayVal);

			displayVal++;
			if(displayVal == 0x3FF)//Reset counter
			{
				displayVal = 0;
			}
			vTaskDelay(15);
			break;
		case 8:	//1000 --> Custom Sequence (Shuffle)
			if(startSeq == 1)
			{
				startSeq = 0;
				displayVal = 0;
				seqFlags = 1;
				SeqL = 0;
				SeqR = 0;
				delay = 100;
			}
			if(SeqR < 0b10101 && SeqL < 0x2a0)
			{
				SeqR = ((SeqR << 1) | seqFlags);//00001 -> 00101 -> 10101
				SeqL = ((SeqL >> 1) | (seqFlags << 9));//1000000000 -> 1010000000 -> 1010100000
				seqFlags = (seqFlags ^ 0b1);
				delay = 100;
			}
			else if(SeqL > 1 && (SeqR & 0x3FF) <= 0x2000)
			{
				SeqR = (SeqR << 1);
				SeqL = (SeqL >> 1);
				if((SeqR | SeqL) == 0b0011111100)
					delay = 50;
				else
					delay = 100;

			}
			else
			{
				startSeq = 1;
				delay = 50;
			}

			displayVal = (SeqL | SeqR);
			IOWR(LEDS_0_BASE, 0, displayVal);

			vTaskDelay(delay);
			break;
		default:
			displayVal = 0;
			IOWR(LEDS_0_BASE, 0, displayVal);
			vTaskDelay(200);
			break;
		}
	}
}

