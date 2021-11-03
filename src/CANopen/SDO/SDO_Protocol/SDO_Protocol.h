/*
 * SDO_Protocol.h
 *
 *  Created on: 3 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_SDO_SDO_PROTOCOL_SDO_PROTOCOL_H_
#define CANOPEN_SDO_SDO_PROTOCOL_SDO_PROTOCOL_H_

#include "../../Easy_CANopen/Structs.h"

void CANOpen_SDO_Protocol_Initiate_Response(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]);
void CANopen_SDO_Protocol_Segment_Response(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]);
void CANOpen_SDO_Protocol_Initiate_Request(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]);
void CANOpen_SDO_Protocol_Segment_Request(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]);

#endif /* CANOPEN_SDO_SDO_PROTOCOL_SDO_PROTOCOL_H_ */
