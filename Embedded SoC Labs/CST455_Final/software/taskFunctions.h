/*************************************************************
* Author:		Cameron Robinson
* Filename:		taskFunctions.h
* Date Created:	12/9/23
**************************************************************/
#ifndef _TASKFUNCTIONS_H_
#define _TASKFUNCTIONS_H_

#include <stddef.h>
#include <stdint.h>

void displayBCD(void * hex01, void * hex23, void * hex45, uint8_t num1, uint8_t num2, uint8_t result);
uint16_t cylonShift(uint16_t displayValue, uint8_t* seqFlags, uint16_t leftVal, uint16_t rightVal);
uint16_t cylonPulse(uint32_t * hex01, uint32_t * hex23, uint32_t * hex45, uint32_t * leds);

#endif