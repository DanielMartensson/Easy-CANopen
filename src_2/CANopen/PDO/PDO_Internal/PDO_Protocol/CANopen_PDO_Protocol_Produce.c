/*
 * CANopen_PDO_Protocol_Produce.c
 *
 *  Created on: 7 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "PDO_Protocol.h"

/* Layers */
#include "../../../OD/OD.h"
#include "../../../../Hardware/Hardware.h"

void CANopen_PDO_Protocol_Produce_Data(CANopen *canopen, uint16_t CAN_ID, struct PDO_mapping *pdo_mapping){
	/* Collect data and send */
	uint8_t data[8] = {0};
	uint8_t position = 0;
	for(uint8_t i = 0; i < pdo_mapping->number_of_mapped_objects_in_PDO; i++){

		/* Get the mapping parameters of PDO */
		uint16_t index = pdo_mapping->object_to_be_mapped[i] >> 16;
		uint8_t sub_index = pdo_mapping->object_to_be_mapped[i] >> 8;
		uint8_t length = pdo_mapping->object_to_be_mapped[i];
		uint8_t length_in_bytes = length / 8;

		/* Get the value from OD */
		uint32_t value = CANopen_OD_Get_Value(canopen, index, sub_index);

		/* Quick check if the data array is full */
		if(length_in_bytes + position >= 8)
			break;

		/* Insert value to data  */
		switch(length){
		case 8:
			data[position++] = value;
			break;
		case 16:
			data[position++] = value;
			data[position++] = value >> 8;
			break;
		case 32:
			data[position++] = value;
			data[position++] = value >> 8;
			data[position++] = value >> 16;
			data[position++] = value >> 24;
			break;
		}
	}

	/* Send the message to client */
	Hardware_CAN_Send_Message(CAN_ID, data);
}

void CANopen_PDO_Protocol_Produce_Request(uint16_t CAN_ID){
	/* PDO request has zero bytes */
	uint8_t data[8] = {0};
	Hardware_CAN_Send_Message(CAN_ID, data);
}
