/*
 * Structs.h
 *
 *  Created on: 6 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef EASY_CANOPEN_STRUCTS_H_
#define EASY_CANOPEN_STRUCTS_H_

/* C standard library */
#include <stdint.h>
#include <stdbool.h>

typedef struct {
	/* Latest CAN message */
	uint32_t COB_ID;													/* This is the CAN bus ID */
	uint8_t data[8];													/* This is the CAN bus data */
	bool COB_ID_and_data_is_updated;									/* This is a flag that going to be set to true for every time ID and data

	/* Information about this node */
	uint8_t this_node_address; 											/* If this address is 0, then this node is the master */


} CANopen;

#endif /* EASY_CANOPEN_STRUCTS_H_ */
