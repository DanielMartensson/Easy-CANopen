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

typedef struct{
	/* Information about this node */
	uint8_t this_node_address;										/* If this address is 0, then this node is the master */


}CANopen;

#endif /* EASY_CANOPEN_STRUCTS_H_ */
