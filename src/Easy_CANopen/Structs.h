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

/* CiA 301: Object dictionary for communication parameter area 0x1000 -> 0x1FFF */
struct OD_Communication{
	uint32_t device_type;												/* Index 0x1000 sub index 0x0 */
	uint8_t error_register;												/* Index 0x1001 sub index 0x0 */
	uint32_t manufacturer_status_register;								/* Index 0x1002 sub index 0x0 */
	uint32_t pre_defined_error_field[11];								/* Index 0x1003 sub index 0x0 -> 0xA */
	uint32_t COB_ID_sync_message;										/* Index 0x1005 sub index 0x0 */
	uint32_t communication_cycle_period;								/* Index 0x1006 sub index 0x0 */
	uint32_t synchronous_window_length;									/* Index 0x1007 sub index 0x0 */
	char manufacturer_device_name[30];									/* Index 0x1008 sub index 0x0 */
	char manufacturer_hardware_version[30];								/* Index 0x1009 sub index 0x0 */
	char manufacturer_software_version[30];								/* Index 0x100A sub index 0x0 */
	uint16_t guard_time;												/* Index 0x100C sub index 0x0 */
	uint8_t life_time_factor;											/* Index 0x100D sub index 0x0 */
	uint32_t store_parameters[4];										/* Index 0x1010 sub index 0x0 -> 0x3 */
	uint32_t restore_default_parameters[4];								/* Index 0x1011 sub index 0x0 -> 0x3 */
	uint32_t COB_ID_time_stamp_object;									/* Index 0x1012 sub index 0x0 */
	uint32_t high_resolution_time_stamp;								/* Index 0x1013 sub index 0x0 */
	uint32_t COB_ID_emcy;												/* Index 0x1014 sub index 0x0 */
	uint16_t inhibit_time_emcy;											/* Index 0x1015 sub index 0x0 */
	uint32_t consumer_heartbeat_time[0x80];								/* Index 0x1016 sub index 0x0 -> 0x7F */
	uint16_t producer_heartbeat_time;									/* Index 0x1017 sub index 0x0 */
	uint32_t identity_object[5];										/* Index 0x1018 sub index 0x0 -> 0x4 */
	uint8_t synchronous_counter_overflow_value;							/* Index 0x1019 sub index 0x0 */
	uint32_t verify_configuration[3];									/* Index 0x1020 sub index 0x0 -> 0x2 */
	uint32_t emergency_consumer_object[0x80];							/* Index 0x1028 sub index 0x0 -> 0x7F */
	uint8_t  error_behavior_object[2];									/* Index 0x1029 sub index 0x0 -> 0x1 */
};

/* CiA 301: Time */
struct TIME{
	uint16_t days_since_1_janunary_1984;								/* Days since 1 January 1984 */
	uint32_t milliseconds_since_midnight;								/* Milliseconds since clock 00:00 */
	uint8_t from_node_ID;												/* Where the time message came from */
};

/* CiA 301: Emergency */
struct EMCY{
	uint16_t error_code;												/* The error code from a node */
	uint8_t error_register;												/* The error register from anode */
	uint8_t from_node_ID;												/* Where the emergency message came from  */
};

/* CiA 305: Layer setting services */
struct LSS{
	uint8_t switch_mode_global_protocol;								/* Disable or enable the LSS service */
	uint8_t status_code;												/* Status code */
	uint8_t status_code_specific;										/* Status code specific */
	bool status_code_is_new;											/* Is true when the status code variables has changed */
	bool selective_value_is_set;										/* Is true when vendor ID, product code, revision number or serial number has changed */
	uint8_t node_ID;													/* Where did the message came from */
	uint32_t vendor_ID;													/* Vendor ID of this device or other device */
	uint32_t product_code;												/* Product code of this device or other device */
	uint32_t revision_number;											/* Revision number of this device or other device */
	uint32_t serial_number;												/* Serial number of this device or other device */
	uint8_t table_index;												/* Baud rate table index */
	bool identity_found;												/* If vendor ID, product code, revision number or serial number has been found */
	bool non_configured_node_ID_found;									/* If the node ID is at the error address 0xFF */
	uint8_t bit_timing_table_index;										/* The baud rate table index */
	uint8_t this_node_ID;												/* This node ID of this device */
};

/* CiA 301: Network management */
struct NMT{
	uint8_t node_status_operation;										/* Status at the other nodes */
	uint8_t status_operational;											/* What status operation is the slave into */
	uint8_t toggle_heartbeat;											/* 1 or 0 for every heartbeat */
	uint32_t count_tick;												/* Counter */
	uint8_t from_node_ID;												/* From node ID */
};

struct Master{
	struct LSS lss;
	struct NMT nmt;
};

struct Slave{
	struct LSS lss;
	struct NMT nmt;
};

struct Consumer{
	struct EMCY emcy;
	struct TIME time;
};


/* This struct is the object used by the CANopen user */
typedef struct {
	/* Latest CAN message */
	uint32_t COB_ID;													/* This is the CAN bus ID */
	uint8_t data[8];													/* This is the CAN bus data */
	bool COB_ID_and_data_is_updated;									/* This is a flag that going to be set to true for every time ID and data */

	/* OD */
	struct OD_Communication od_communication;							/* Communication objects */

	/* LSS, NMT, EMCY, TIME */
	struct Master master;
	struct Slave slave;
	struct Consumer consumer;

} CANopen;

#endif /* EASY_CANOPEN_STRUCTS_H_ */
