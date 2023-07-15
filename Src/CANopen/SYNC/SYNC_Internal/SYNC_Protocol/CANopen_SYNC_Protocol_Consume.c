/*
 * CANopen_SYNC_Protocol_Consume.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */
 
#include "../../../PDO/PDO_Internal/PDO_Internal.h"

#include "SYNC_Protocol.h"

void CANopen_SYNC_Protocol_Consume_Synchronization(CANopen *canopen, uint8_t data[]){
	/* Save sync counter */
	canopen->slave.sync.counter = data[0];

	/* Call the PDO transmit */
	CANopen_Producer_PDO_Transmit_Data(canopen);
}
