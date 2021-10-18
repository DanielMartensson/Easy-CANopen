/*
 * Transmitting_Messages.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "Easy_CANopen.h"

/* Layers */
#include "../CANopen/CANopen.h"

void Easy_CANopen_Transmitting_Of_Messages(CANopen *canopen){
	CANopen_Producer_HEARTBEAT_Transmit_Heartbeat(canopen);
}

