/*
 * CANopen_OD.c
 *
 *  Created on: 13 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "OD.h"

static OD_STATUS read_or_write(uint32_t *value, void *struct_value, bool set, OD_ACCESS access, uint8_t byte_size);

OD_STATUS CANopen_OD_set_get_value(CANopen *canopen, uint16_t index, uint8_t sub_index, bool set, void *value, uint8_t byte_size){
	struct OD_Communication *communication = &canopen->od_communication;
	switch(index){
	case OD_INDEX_DEVICE_TYPE:
		return read_or_write(value, &communication->device_type, set, OD_ACCESS_READ, byte_size);
	case OD_INDEX_ERROR_REGISTER:
		return read_or_write(value, &communication->error_register, set, OD_ACCESS_READ, byte_size);
	case OD_INDEX_MANUFACTURER_STATUS_REGISTER:
		return read_or_write(value, &communication->manufacturer_status_register, set, OD_ACCESS_READ, byte_size);
	case OD_INDEX_PRE_DEFINED_ERROR_FIELD:
		return read_or_write(value, &communication->pre_defined_error_field[sub_index], set, OD_ACCESS_READ, byte_size);
	case OD_INDEX_COB_ID_SYNC_MESSAGE:
		return read_or_write(value, &communication->COB_ID_sync_message, set, OD_ACCESS_READ_WRITE, byte_size);
	case OD_INDEX_COMMUNICATION_CYCLE_PERIOD:
		return read_or_write(value, &communication->communication_cycle_period, set, OD_ACCESS_READ_WRITE, byte_size);
	case OD_INDEX_SYNCHRONOUS_WINDOW_LENGTH:
		return read_or_write(value, &communication->synchronous_window_length, set, OD_ACCESS_READ_WRITE, byte_size);
	case OD_INDEX_MANUFACTURER_DEVICE_NAME:
		return read_or_write(value, &communication->manufacturer_device_name, set, OD_ACCESS_READ, byte_size);
	case OD_INDEX_MANUFACTURER_HARDWARE_VERSION:
		return read_or_write(value, &communication->manufacturer_hardware_version, set, OD_ACCESS_READ, byte_size);
	case OD_INDEX_MANUFACTURER_SOFTWARE_VERSION:
		return read_or_write(value, &communication->manufacturer_software_version, set, OD_ACCESS_READ, byte_size);
	case OD_INDEX_GUARD_TIME_MS:
		return read_or_write(value, &communication->guard_time, set, OD_ACCESS_READ_WRITE, byte_size);
	case OD_INDEX_LIFE_FACTOR:
		return read_or_write(value, &communication->life_time_factor, set, OD_ACCESS_READ_WRITE, byte_size);
	case OD_INDEX_STORE_PARAMETERS:
		return read_or_write(value, &communication->store_parameters[sub_index], set, OD_ACCESS_READ_WRITE, byte_size);
	case OD_INDEX_RESTORE_DEFAULT_PARAMETERS:
		return read_or_write(value, &communication->restore_default_parameters[sub_index], set, OD_ACCESS_READ_WRITE, byte_size);
	case OD_INDEX_COB_ID_TIME_STAMP_OBJECT:
		return read_or_write(value, &communication->COB_ID_time_stamp_object, set, OD_ACCESS_READ_WRITE, byte_size);
	case OD_INDEX_HIGH_RESOLUTION_TIME_STAMP:
		return read_or_write(value, &communication->high_resolution_time_stamp, set, OD_ACCESS_READ_WRITE, byte_size);
	case OD_INDEX_COB_ID_EMCY:
		return read_or_write(value, &communication->COB_ID_emcy, set, OD_ACCESS_READ_WRITE, byte_size);
	case OD_INDEX_INHIBIT_TIME_EMCY:
		return read_or_write(value, &communication->inhibit_time_emcy, set, OD_ACCESS_READ_WRITE, byte_size);
	case OD_INDEX_CONSUMER_HEARTBEAT_TIME:
		return read_or_write(value, &communication->consumer_heartbeat_time[sub_index], set, OD_ACCESS_READ_WRITE, byte_size);
	case OD_INDEX_PRODUCER_HEARTBEAT_TIME:
		return read_or_write(value, &communication->producer_heartbeat_time, set, OD_ACCESS_READ_WRITE, byte_size);
	case OD_INDEX_IDENTITY_OBJECT:
		return read_or_write(value, &communication->identity_object[sub_index], set, OD_ACCESS_READ_WRITE, byte_size);
	case OD_INDEX_SYNCHRONOUS_COUNTER_OVERFLOW_VALUE:
		return read_or_write(value, &communication->synchronous_counter_overflow_value, set, OD_ACCESS_READ_WRITE, byte_size);
	case OD_INDEX_VERIFY_CONFIGURATION:
		return read_or_write(value, &communication->verify_configuration[sub_index], set, OD_ACCESS_READ_WRITE, byte_size);
	case OD_INDEX_EMERGENCY_CONSUMER_OBJECT:
		return read_or_write(value, &communication->emergency_consumer_object[sub_index], set, OD_ACCESS_READ_WRITE, byte_size);
	case OD_INDEX_ERROR_BEHAVIOR_OBJECT:
		return read_or_write(value, &communication->error_behavior_object[sub_index], set, OD_ACCESS_READ_WRITE, byte_size);
	default:
		return OD_STATUS_NOT_FOUND;
	}
}

static OD_STATUS read_or_write(void *value, void *struct_value, bool set, OD_ACCESS access, uint8_t byte_size){
	switch(set){
	case true:
		switch(access | OD_ACCESS_WRITE){
		case true:
			switch(byte_size){
			case OD_DATA_TYPE_U8:
				*((uint8_t*) struct_value) = *((uint8_t*) value);
				break;
			case OD_DATA_TYPE_U16:
				*((uint16_t*) struct_value) = *((uint16_t*) value);
				break;
			case OD_DATA_TYPE_U32:
				*((uint32_t*) struct_value) = *((uint32_t*) value);
				break;
			default:
				return OD_STATUS_WRONG_DATA_TYPE;
			}
			return OD_STATUS_OK;
		default:
			return OD_STATUS_NOT_PERMITTED;
		}
		break;
	case false:
		switch(access | OD_ACCESS_READ){
		case true:
			switch(byte_size){
			case OD_DATA_TYPE_U8:
				*((uint8_t*) value) = *((uint8_t*) struct_value);
				break;
			case OD_DATA_TYPE_U16:
				*((uint16_t*) value) = *((uint16_t*) struct_value);
				break;
			case OD_DATA_TYPE_U32:
				*((uint32_t*) value) = *((uint32_t*) struct_value);
				break;
			default:
				return OD_STATUS_WRONG_DATA_TYPE;
			}
			return OD_STATUS_OK;
		default:
			return OD_STATUS_NOT_PERMITTED;
		}
	}
	return OD_STATUS_NOT_FOUND;
}
