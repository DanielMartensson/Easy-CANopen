/*
 * CANopen_SYNC_Protocol_Consume.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "SYNC_Protocol.h"

void CANopen_SYNC_Protocol_Consume_Synchronization(CANopen *canopen, uint8_t data[]){
	canopen->slave.sync.counter = data[0];
}
