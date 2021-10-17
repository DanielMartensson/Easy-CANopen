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
#include "../CANopen/Global_Enums/Global_Enums.h"

/**********************************************************************************************************/

/* Our dictionary object */
struct Object_dictionary{
    uint32_t key;                                                       /* Key value = index << 16 | sub_index */
    OD_ACCESS access;													/* Read, Write, Read-Write */
    uint32_t value;                                                     /* Unsigned value - If I had use a pointer, it would take more memory */
};

struct Node_status_operation{
	uint8_t toggle;														/* Toggle 1 or 0 to see if the process is alive */
	uint8_t status_operational;											/* The status of the node */
	uint16_t count_tick;												/* Used for time counting */
	uint8_t from_node_ID;												/* From where this message came from */
	bool is_enabled;													/* Check if this process is enabled */
};

struct LSS{
	uint8_t switch_mode_global_protocol;								/* Disable or enable the LSS service */
	uint8_t status_code;												/* Status code */
	uint8_t status_code_specific;										/* Status code specific */
	uint8_t cs;															/* Command specifier */
	uint8_t node_ID;													/* Node ID address of this device */
	uint32_t vendor_ID;													/* Vendor ID of this device */
	uint32_t product_code;												/* Product code of this device */
	uint32_t revision_number;											/* Revision number of this device */
	uint32_t serial_number;												/* Serial number of this device */
	uint8_t table_index;												/* Baud rate table index */
	bool identity_found;												/* If vendor ID, product code, revision number or serial number has been found */
	bool non_configured_node_ID;										/* If the node ID is at the error address 0xFF */
};


/**********************************************************************************************************/

struct Producer {
	struct Node_status_operation heartbeat;								/* Heartbreat container */
};

struct Consumer {
	struct Node_status_operation heartbeat;								/* Heartbreat container */
};

struct Server{
	struct Node_status_operation guard;									/* Guard container */
};

struct Client{
	struct Node_status_operation guard;									/* Guard container */
};

struct Master{
	struct LSS lss;														/* LSS container */
};

struct Slave{
	struct LSS lss;														/* LSS container */
};



typedef struct {
	/* Latest CAN message */
	uint32_t COB_ID;													/* This is the CAN bus ID */
	uint8_t data[8];													/* This is the CAN bus data */
	bool COB_ID_and_data_is_updated;									/* This is a flag that going to be set to true for every time ID and data */

	/* Dictionary objects */
	uint16_t length_object_dictionaries;								/* How many index the pointer struct contains */
	struct Object_dictionary* object_dictionaries;						/* This is a dynamic map that holds object dictionaries of CANopen */

	/* Consumer & Producer */
	struct Consumer consumer;											/* Store values from the producer */
	struct Producer producer;											/* Values are going to be sent to the consumers */

	/* Server & Client */
	struct Server server;												/* Server values */
	struct Client client;												/* Client values */

	/* Master & Slave */
	struct Master master;												/* Master values */
	struct Slave slave;													/* Slave values */

} CANopen;

#endif /* EASY_CANOPEN_STRUCTS_H_ */
