/*************************************************************
* Author:		Cameron Robinson
* Filename:		ld19.h
* Date Created:	11/16/23
**************************************************************/
#ifndef _LD19_H_
#define _LD19_H_

#include "stddef.h"

#define PACKET_LENGTH 47
#define PACKET_HEADER 0x54
#define PACKET_VERSION 0x2C

uint8_t CalCRC8(uint8_t *packet, uint8_t len);
void getLiDARMeasurements(uint8_t* packet, uint16_t* dataPacket);

#endif