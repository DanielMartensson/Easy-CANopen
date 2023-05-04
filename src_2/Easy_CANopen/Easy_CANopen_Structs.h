/*
 * Easy_CANopen_Structs.h
 *
 *  Created on: 6 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef EASY_CANOPEN_EASY_CANOPEN_STRUCTS_H_
#define EASY_CANOPEN_EASY_CANOPEN_STRUCTS_H_

/* C standard library */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* Enums */
#include "../CANopen/Global_Enums/Global_Enums.h"

#define PRE_DEFINED_ERROR_FIELD_MAX_SUB_INDEX 11
#define STORE_RE_STORE_PARAMETER_MAX_SUB_INDEX 4
#define CONSUMER_HEARTBEAT_TIME_MAX_SUB_INDEX 128
#define EMERGENCY_CONSUMER_MAX_SUB_INDEX 128
#define VERIFY_CONFIGURATION_MAX_SUB_INDEX 3
#define ERROR_BEHAVIOR_SUB_INDEX 2
#define OD_STRING_LENGTH 20
#define PDO_LENGTH 32

/* CiA 301: Communication parameter record for RPDO (0x1400 - 0x15FF) and TPDO (0x1800 - 0x19FF) */
struct PDO_communication{
	uint8_t highest_sub_index_supported;												/* Sub index 0x0 */
	uint16_t COB_ID;																	/* Sub index 0x1 */
	uint8_t transmission_type;															/* Sub index 0x2 */
	uint16_t inhibit_time;																/* Sub index 0x3 */
	uint8_t reserved;																	/* Sub index 0x4 */
	uint16_t event_timer;																/* Sub index 0x5 */
	uint8_t sync_start_value;															/* Sub index 0x6 */
};

/* CiA 301: Mapping parameter record for RPDO (0x1600 - 0x17FF) and TPDO (0x1A00 - 0x1BFF) */
struct PDO_mapping{
	uint8_t number_of_mapped_objects_in_PDO;											/* Sub index 0x0 */
	uint32_t object_to_be_mapped[8];													/* Sub index 0x1 -> 0x8 */
};

/* CiA 301: Object dictionary for communication parameter area 0x1000 -> 0x1FFF */
struct OD_Communication{
	uint32_t device_type;																/* Index 0x1000 sub index 0x0 - OK */
	uint8_t error_register;																/* Index 0x1001 sub index 0x0 - OK*/
	uint32_t manufacturer_status_register;												/* Index 0x1002 sub index 0x0 - OK */
	uint32_t pre_defined_error_field[PRE_DEFINED_ERROR_FIELD_MAX_SUB_INDEX];			/* Index 0x1003 sub index 0x0 -> 0xA - OK */
	uint32_t COB_ID_sync_message;														/* Index 0x1005 sub index 0x0 - OK */
	uint32_t communication_cycle_period;												/* Index 0x1006 sub index 0x0 */
	uint32_t synchronous_window_length;													/* Index 0x1007 sub index 0x0 */
	uint32_t manufacturer_device_name[OD_STRING_LENGTH];								/* Index 0x1008 sub index 0x0 */
	uint32_t manufacturer_hardware_version[OD_STRING_LENGTH];							/* Index 0x1009 sub index 0x0 */
	uint32_t manufacturer_software_version[OD_STRING_LENGTH];							/* Index 0x100A sub index 0x0 -> 0xA9 */
	uint16_t guard_time;																/* Index 0x100C sub index 0x0 - OK */
	uint8_t life_time_factor;															/* Index 0x100D sub index 0x0 - OK */
	uint32_t store_parameters[STORE_RE_STORE_PARAMETER_MAX_SUB_INDEX];					/* Index 0x1010 sub index 0x0 -> 0x3 */
	uint32_t restore_default_parameters[STORE_RE_STORE_PARAMETER_MAX_SUB_INDEX];		/* Index 0x1011 sub index 0x0 -> 0x3 */
	uint32_t COB_ID_time_stamp_object;													/* Index 0x1012 sub index 0x0 */
	uint32_t high_resolution_time_stamp;												/* Index 0x1013 sub index 0x0 */
	uint32_t COB_ID_emcy;																/* Index 0x1014 sub index 0x0 - OK*/
	uint32_t consumer_heartbeat_time[CONSUMER_HEARTBEAT_TIME_MAX_SUB_INDEX];			/* Index 0x1016 sub index 0x0 -> 0x7F - OK */
	uint16_t producer_heartbeat_time;													/* Index 0x1017 sub index 0x0 - OK */
	uint8_t identity_object_highest_supported_sub_index;								/* Index 0x1018 sub index 0x0 */
	uint32_t vendor_ID;																	/* Index 0x1018 sub index 0x1 */
	uint32_t product_code;																/* Index 0x1018 sub index 0x2 */
	uint32_t revision_number;															/* Index 0x1018 sub index 0x3 */
	uint32_t serial_number;																/* Index 0x1018 sub index 0x4 */
	uint8_t synchronous_counter_overflow_value;											/* Index 0x1019 sub index 0x0 */
	uint32_t verify_configuration[VERIFY_CONFIGURATION_MAX_SUB_INDEX];					/* Index 0x1020 sub index 0x0 -> 0x2 */
	uint32_t emergency_consumer_object[EMERGENCY_CONSUMER_MAX_SUB_INDEX];				/* Index 0x1028 sub index 0x0 -> 0x7F */
	uint8_t error_behavior_object[ERROR_BEHAVIOR_SUB_INDEX];							/* Index 0x1029 sub index 0x0 -> 0x1 */
	struct PDO_communication PDO_communication_receive[PDO_LENGTH];						/* Index 0x1400 -> 0x1400 + PDO_LENGTH -1 */
	struct PDO_communication PDO_communication_transmit[PDO_LENGTH];					/* Index 0x1800 -> 0x1800 + PDO_LENGTH -1 */
	struct PDO_mapping PDO_mapping_receive[PDO_LENGTH];									/* Index 0x1600 -> 0x1600 + PDO_LENGTH -1 */
	struct PDO_mapping PDO_mapping_transmit[PDO_LENGTH];								/* Index 0x1A00 -> 0x1A00 + PDO_LENGTH -1 */

};

/* CiA 305: Layer setting services */
struct LSS{
	uint8_t switch_mode_global_protocol;								/* Disable or enable the LSS service */
	uint8_t status_code;												/* Status code */
	uint8_t status_code_specific;										/* Status code specific */
	bool status_code_is_new;											/* Is true when the status code variables has changed */
	bool selective_value_is_set;										/* Is true when vendor ID, product code, revision number or serial number has changed */
	uint32_t vendor_ID;													/* Vendor ID of this device or other device */
	uint32_t product_code;												/* Product code of this device or other device */
	uint32_t revision_number;											/* Revision number of this device or other device */
	uint32_t serial_number;												/* Serial number of this device or other device */
	uint8_t node_ID;													/* Node ID */
	bool identity_found;												/* If vendor ID, product code, revision number or serial number has been found */
	bool non_configured_node_ID_found;									/* If the node ID is at the error address 0xFF */
};

/* CiA 301: Network management */
struct NMT{
	uint8_t this_node_status_operational;								/* Operational status of this node */
	uint8_t from_node_status_operational;								/* Operational status of other node */
	uint8_t this_node_toggle;											/* Toggle of this node */
	uint8_t from_node_toggle;											/* Toggle of other node */
	uint32_t this_node_count_tick;										/* Counter in milliseconds of this node */
	uint32_t from_node_count_tick;										/* Counter in milliseconds of other node */
	uint8_t from_node_ID;												/* From node ID */
};

/* CiA 301: Service Dictionary Objects */
struct SDO{
	uint32_t expedited_byte;											/* Expedited data or byte size that are going to be sent */
	uint8_t expedited_byte_size;										/* Expedited data size */
	uint32_t transceive_segment_total_byte;								/* Total bytes that are going to be transmitted or received */
	uint32_t transceive_segment_bytes_counter;							/* How many bytes we have transmitted or received */
	uint8_t *transceive_segment_byte_pointer;							/* Data array of transceiver data */

	uint16_t index;														/* At what index did we read or write */
	uint8_t sub_index;													/* At what sub index did we read or write */
	uint8_t from_node_ID;												/* From node ID */
};

struct PDO{
	uint8_t sync_counter_value;											/* Counter sync value for PDO */
	bool start_counting_sync;											/* This is true when sync_start_value above is equal or greater as sync */
	uint8_t event_timer_counter;										/* Event timer counter for PDO */
};

/* CiA 301: Synchronization */
struct SYNC{
	uint8_t counter;													/* This is for the PDO sync */
};

/* CiA 301: Time */
struct TIME{
	uint16_t days_since_1_janunary_1984;								/* Days since 1 January 1984 */
	uint32_t milliseconds_since_midnight;								/* Milliseconds since clock 00:00 */
};

/* CiA 301: Emergency */
struct EMCY{
	uint16_t error_code;												/* The error code from a node */
	uint8_t error_register;												/* The error register from anode */
	uint8_t from_node_ID;												/* Where the emergency message came from  */
};

/**************************************************************************************************/

struct Master{
	struct NMT nmt;
	struct LSS lss;
	struct SYNC sync;
};

struct Slave{
	struct NMT nmt;
	struct LSS lss;
	struct SYNC sync;
	struct TIME time;
	struct SDO sdo;
	struct PDO pdo[PDO_LENGTH];											/* Only for TPDO */
	struct EMCY emcy;
	uint8_t this_node_ID;												/* This node ID of this slave */
	uint8_t this_node_table_index;										/* Baud rate table index of this slave */
};


/* This struct is the object used by the CANopen user */
typedef struct {
	/* Latest CAN message */
	uint16_t COB_ID;													/* This is the CAN bus ID */
	uint8_t data[8];													/* This is the CAN bus data */
	bool COB_ID_and_data_is_updated;									/* This is a flag that going to be set to true for every time ID and data */

	/* CANopen services */
	struct OD_Communication od_communication;							/* Communication objects */
	struct Master master;												/* The node with address 0 */
	struct Slave slave;													/* The nodes with address 1 to 127 */
} CANopen;

#endif /* EASY_CANOPEN_EASY_CANOPEN_STRUCTS_H_ */
