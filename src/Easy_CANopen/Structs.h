/*
 * Structs.h
 *
 *  Created on: 6 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef EASY_CANOPEN_STRUCTS_H_
#define EASY_CANOPEN_STRUCTS_H_

/* C standard library */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* Enums */
#include "../CANopen/Global_Enums/Enum_Object_Dictionary_Codes.h"

/* Our dictionary object */
struct Object_dictionary{
    uint32_t key;                                                       /* Key value = index << 16 | sub_index */
    OD_ACCESS access;													/* Read, Write, Read-Write */
    uint32_t value;                                                     /* Unsigned value - If I had use a pointer, it would take more memory */
};

typedef struct {
	/* Latest CAN message */
	uint32_t COB_ID;													/* This is the CAN bus ID */
	uint8_t data[8];													/* This is the CAN bus data */
	bool COB_ID_and_data_is_updated;									/* This is a flag that going to be set to true for every time ID and data */

	/* Dictionary objects */
	uint16_t length_object_dictionaries;								/* How many index the pointer struct contains */
	struct Object_dictionary* object_dictionaries;						/* This is a dynamic map that holds object dictionaries of CANopen */

	/* Toggle variables */
	uint8_t toggle_heartbeat;											/* Toggle variable for heartbeat */
} CANopen;

#endif /* EASY_CANOPEN_STRUCTS_H_ */
