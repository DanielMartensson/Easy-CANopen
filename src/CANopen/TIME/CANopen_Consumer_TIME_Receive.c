/*
 * CANopen_Consumer_TIME_Receive.c
 *
 *  Created on: 19 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "TIME.h"

void CANopen_Consumer_TIME_Receive_Clock(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	canopen->from_other_node.consumer.time.milliseconds_since_midnight = (data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0];
	canopen->from_other_node.consumer.time.days_since_1_janunary_1984 = (data[5] << 8) | data[4];
	canopen->from_other_node.consumer.time.from_node_ID = node_ID;
}
