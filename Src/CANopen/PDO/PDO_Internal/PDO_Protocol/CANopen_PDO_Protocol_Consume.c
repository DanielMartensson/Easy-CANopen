/*
 * CANopen_PDO_Protocol_Consume.c
 *
 *  Created on: 7 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "PDO_Protocol.h"

/* Layers */
#include "../../../OD/OD.h"

void CANopen_PDO_Protocol_Consume_Data(CANopen *canopen, struct PDO_mapping *pdo_mapping, uint8_t data[]) {
	/* Collect data and save */
	uint8_t position = 0;
	for(uint8_t i = 0; i < pdo_mapping->number_of_mapped_objects_in_PDO; i++){

		/* Get the mapping parameters of PDO */
		uint16_t index = pdo_mapping->object_to_be_mapped[i] >> 16;
		uint8_t sub_index = pdo_mapping->object_to_be_mapped[i] >> 8;
		uint8_t length = pdo_mapping->object_to_be_mapped[i];
		uint8_t length_in_bytes = length / 8;

		/* Quick check if the data array is full */
		if(length_in_bytes + position >= 8)
			break;

		/* Insert data to value */
		uint32_t value = 0;
		switch(length){
		case 8:
			value = data[position++];
			break;
		case 16:
			value = data[position++];
			value |= data[position++] << 8;
			break;
		case 32:
			value = data[position++];
			value |= data[position++] << 8;
			value |= data[position++] << 16;
			value |= data[position++] << 24;
			break;
		}

		/* Get the value from OD */
		CANopen_OD_Set_Value(canopen, index, sub_index, value);
	}
}
