/*************************************************************
* Author:		Cameron Robinson
* Filename:		taskFunctions.c
* Date Created:	12/9/23
* Modifications: 
**************************************************************/

#include <unistd.h>
#include <pthread.h>
#include "taskFunctions.h"

/**********************************************************************
* Purpose: Function that converts three integers into BCD values and displayes them
*		   on six 7-seg displays.
*
* Precondition: Function called and passed address for hex diaplays.
*
* Postcondition: BCD for num1, num2, and result are displayed
				 on HEX5-HEX4, HEX3-HEX2, and HEX1-HEX0 respectively
************************************************************************/
void displayBCD(void * hex01, void * hex23, void * hex45, uint8_t num1, uint8_t num2, uint8_t result)
{
	uint16_t displayVals[3] = {0};//Variable array to hold BCD display values
	
	displayVals[2] = (((uint8_t)(num1 / 10) & 0x1F) << 5) | ((num1 % 10) & 0x1F);
	displayVals[1] = (((uint8_t)(num2 / 10) & 0x1F) << 5) | ((num2 % 10) & 0x1F);

	displayVals[0] = (result % 10) & 0x1F;
	if(result >= 100)//2x 7-segs cannot display decimal value > 99
	{
		displayVals[0] |= (((uint8_t)(result/10))%10) << 5;//Display lowest two digits
	}
	else
	{
		displayVals[0] |= ((uint8_t)(result/10)) << 5;
	}
	
	*(uint32_t*)hex45 = displayVals[2];
	*(uint32_t*)hex23 = displayVals[1];
	*(uint32_t*)hex01 = displayVals[0];
}

/**********************************************************************
* Purpose: Function to shift and adjust shift direction for the cylon pattern.
*
* Precondition: Funciton called and passed LED values that will be displayed,
*				flag var for what direction the LEDs are beinng shifted, and the 
*				boundary conditions of when to switch the shift direction.
*
* Postcondition: Display value passed in is shifted and returned.
************************************************************************/
uint16_t cylonShift(uint16_t displayValue, uint8_t* seqFlags, uint16_t leftVal, uint16_t rightVal)
{
	if((*seqFlags))//Travel left
	{
		displayValue = (displayValue << 1);
		if(displayValue >= leftVal)
			*seqFlags = 0;
	}
	else		//Travel right
	{
		displayValue = (displayValue >> 1);
		if(displayValue == rightVal)
			*seqFlags = 1;
	}
	
	return displayValue;
					
}

/**********************************************************************
* Purpose: Function that performs a custom pattern on the LEDs and HEX displays

* Precondition: Function called and sent valid LED and HEX5-HEX0 display addresses.
*
* Postcondition: Steps through one step of custom pattern sequence.
************************************************************************/
uint16_t cylonPulse(uint32_t * hex01, uint32_t * hex23, uint32_t * hex45, uint32_t * leds)
{
	static uint8_t activeLEDs = 1;			//Static var to hold number of LEDs active
	static uint16_t ledDisplay = 1;			//Static var to display on LEDs
	static uint8_t ledFlag = 1;				//Flag for switching direction of LED cylon
	static uint16_t rightBoundary;			//Right boundary condition for LED cylon
	static uint32_t displayVal = 0x0e739ce7;//HEX display varibale: (unused)00 (hex5)00011 (hex4)00111 (hex3)00111 (hex2)00111 (hex1)00111 (hex0)00111
	static uint8_t seq = 0;					//Sequence number for Hed display pattern
	static uint8_t nextSeq = 0;				//Flag variable for continuing to next step of HEX display sequence
	static uint8_t beginSeq = 0;			//Flag to start a new full sequence on HEX displays 
	
	//Switch to next step of seq or rest to default values is seq is done
	if(nextSeq)
	{
		if(seq == 6)
		{
			seq = 0;
			if(activeLEDs < 9)
			{
				activeLEDs++;
				ledDisplay = ((ledDisplay & 0x1) == 1) ? ((ledDisplay << 1) | 1) : (ledDisplay | (ledDisplay >> 1));
			}
			else
			{
				activeLEDs = 1;
				ledDisplay = 1;
				ledFlag = 1;
			}

			beginSeq = 0;
		}
		else
			seq++;
		nextSeq = 0;
	}
	
	//Calculate right boundary of LEDs to account for growing cylon
	rightBoundary = (((1 << (activeLEDs-1)) | ((1 << (activeLEDs-1)) - 1)) & (0x3FF));
	
	//Display LEDs and shift values
	*leds = ledDisplay;
	ledDisplay = cylonShift(ledDisplay, &ledFlag, 0x200, rightBoundary);
	
	//Begin new seq when cylon is travelling past HEX5 from the right or left (if no seq is active already)
	if(!beginSeq && ((ledFlag && (ledDisplay & 0x10)) || ((ledDisplay & 0x08))))
	{
		beginSeq = 1;
		displayVal = 0x06739ce7;
	}
	
	//display first. Add 16 to display vals to decode individual segments
	*hex01 = ((0x3FF) & displayVal) + 0x210;
	*hex23 = ((0x3FF) & (displayVal >> 10)) + 0x210;
	*hex45 = ((0x3FF) & (displayVal >> 20)) + 0x210;
	
	//HEX display sequence 
	if(beginSeq)
	{
		switch(seq)
		{
			case 0://Shifting bottom segs right
				displayVal = ((displayVal >> 5) | (0x0e000000));
				if((displayVal & 0x1F) == 0x3)
					nextSeq = 1;
			break;
			case 1://Corner
				displayVal--;
				if((displayVal & 0x1F) == 0)
					nextSeq = 1;
			break;
			case 2://Shifting top segs left
				displayVal = ((displayVal << 5) | (0x7));
				if((displayVal & 0x3E000000) == 0)
				{
					nextSeq = 1;
					//displayVal = (displayVal & 0x01FFFFFF) | (0x0A000000);
				}
			break;
			case 3://Corner
				if((displayVal & 0x3E000000) == 0)
					displayVal = (displayVal & 0x01FFFFFF) | (0x0A000000);
				else if((displayVal & 0x3E000000) == 0x0A000000)
					displayVal = displayVal + 0x02000000;
				else
					nextSeq = 1;
			break;
			case 4://Shifting middle segs right
				displayVal = ((displayVal >> 5) | (0x0e000000));
				if((displayVal & 0x03e0) == 0xC0)
					nextSeq = 1;
			break;
			case 5://Corner
				if((displayVal & 0x03e0) == 0xC0)
					displayVal = (displayVal & 0xFFFFFC1F) | 0x040;
				else if((displayVal & 0x03e0) == 0x040)
					displayVal = (displayVal & 0xFFFFFC1F) | 0x060;
				else
					nextSeq = 1;
			break;
			case 6://Shifting bottom segs left until done
				displayVal = ((displayVal << 5) | (0x7));
				if((displayVal & 0xF8000) == (0x18000))
				{
					displayVal = 0x0e739ce7;
					nextSeq = 1;
				}
			break;
		}
	}
	
	return ledDisplay;
	
}