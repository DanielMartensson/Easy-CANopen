/*
 * CANopen_Consumer_EMCY_Receive.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "EMCY.h"

/* Layers */
#include "../../Hardware/Hardware.h"

/*
 * Receive and save the EMCY error code and error register and also from where the EMCY message came from
 */
void CANopen_Consumer_EMCY_Receive_Error_Message(CANopen *canopen, uint8_t node_ID, uint8_t data[]) {
	canopen->consumer.emcy.error_code = (data[1] << 8) | data[0];
	canopen->consumer.emcy.error_register = data[2];
	canopen->consumer.emcy.from_node_ID = node_ID;
}
