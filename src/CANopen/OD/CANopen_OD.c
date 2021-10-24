/*
 * CANopen_OD.c
 *
 *  Created on: 13 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "OD.h"

static OD_STATUS read_or_write(uint32_t *value, void *struct_value, bool write_value, bool force, OD_ACCESS access, OD_DATA_TYPE data_type_struct_value);

OD_STATUS CANopen_OD_set_get_value(CANopen *canopen, uint16_t index, uint8_t sub_index, bool write_value, bool force, uint32_t *value){
	struct OD_Communication *communication = &canopen->od_communication;
	if(index == OD_INDEX_DEVICE_TYPE){
		return read_or_write(value, &communication->device_type, write_value, force, OD_ACCESS_READ, sizeof(communication->device_type));
	}else if(index == OD_INDEX_ERROR_REGISTER){
		return read_or_write(value, &communication->error_register, write_value, force, OD_ACCESS_READ, sizeof(communication->error_register));
	}else if(index == OD_INDEX_MANUFACTURER_STATUS_REGISTER){
		return read_or_write(value, &communication->manufacturer_status_register, write_value, force, OD_ACCESS_READ, sizeof(communication->manufacturer_status_register));
	}else if(index == OD_INDEX_PRE_DEFINED_ERROR_FIELD){
		return read_or_write(value, &communication->pre_defined_error_field[sub_index], write_value, force, OD_ACCESS_READ, sizeof(communication->pre_defined_error_field[sub_index]));
	}else if(index == OD_INDEX_COB_ID_SYNC_MESSAGE){
		return read_or_write(value, &communication->COB_ID_sync_message, write_value, force, OD_ACCESS_READ_WRITE, sizeof(communication->COB_ID_sync_message));
	}else if(index == OD_INDEX_COMMUNICATION_CYCLE_PERIOD){
		return read_or_write(value, &communication->communication_cycle_period, write_value, force, OD_ACCESS_READ_WRITE, sizeof(communication->communication_cycle_period));
	}else if(index == OD_INDEX_SYNCHRONOUS_WINDOW_LENGTH){
		return read_or_write(value, &communication->synchronous_window_length, write_value, force, OD_ACCESS_READ_WRITE, sizeof(communication->synchronous_window_length));
	}else if(index == OD_INDEX_MANUFACTURER_DEVICE_NAME){
		return read_or_write(value, &communication->manufacturer_device_name, write_value, force, OD_ACCESS_READ, sizeof(communication->manufacturer_device_name));
	}else if(index == OD_INDEX_MANUFACTURER_HARDWARE_VERSION){
		return read_or_write(value, &communication->manufacturer_hardware_version, write_value, force, OD_ACCESS_READ, sizeof(communication->manufacturer_hardware_version));
	}else if(index == OD_INDEX_MANUFACTURER_SOFTWARE_VERSION){
		return read_or_write(value, &communication->manufacturer_software_version, write_value, force, OD_ACCESS_READ, sizeof(communication->manufacturer_software_version));
	}else if(index == OD_INDEX_GUARD_TIME_MS){
		return read_or_write(value, &communication->guard_time, write_value, force, OD_ACCESS_READ_WRITE, sizeof(communication->guard_time));
	}else if(index == OD_INDEX_LIFE_FACTOR){
		return read_or_write(value, &communication->life_time_factor, write_value, force, OD_ACCESS_READ_WRITE, sizeof(communication->life_time_factor));
	}else if(index == OD_INDEX_STORE_PARAMETERS){
		return read_or_write(value, &communication->store_parameters[sub_index], write_value, force, OD_ACCESS_READ_WRITE, sizeof(communication->store_parameters[sub_index]));
	}else if(index == OD_INDEX_RESTORE_DEFAULT_PARAMETERS){
		return read_or_write(value, &communication->restore_default_parameters[sub_index], write_value, force, OD_ACCESS_READ_WRITE, sizeof(communication->restore_default_parameters[sub_index]));
	}else if(index == OD_INDEX_COB_ID_TIME_STAMP_OBJECT){
		return read_or_write(value, &communication->COB_ID_time_stamp_object, write_value, force, OD_ACCESS_READ_WRITE, sizeof(communication->COB_ID_time_stamp_object));
	}else if(index == OD_INDEX_HIGH_RESOLUTION_TIME_STAMP){
		return read_or_write(value, &communication->high_resolution_time_stamp, write_value, force, OD_ACCESS_READ_WRITE, sizeof(communication->high_resolution_time_stamp));
	}else if(index == OD_INDEX_COB_ID_EMCY){
		return read_or_write(value, &communication->COB_ID_emcy, write_value, force, OD_ACCESS_READ_WRITE, sizeof(communication->COB_ID_emcy));
	}else if(index == OD_INDEX_INHIBIT_TIME_EMCY){
		return read_or_write(value, &communication->inhibit_time_emcy, write_value, force, OD_ACCESS_READ_WRITE, sizeof(communication->inhibit_time_emcy));
	}else if(index == OD_INDEX_CONSUMER_HEARTBEAT_TIME){
		return read_or_write(value, &communication->consumer_heartbeat_time[sub_index], write_value, force, OD_ACCESS_READ_WRITE, sizeof(communication->consumer_heartbeat_time[sub_index]));
	}else if(index == OD_INDEX_PRODUCER_HEARTBEAT_TIME){
		return read_or_write(value, &communication->producer_heartbeat_time, write_value, force, OD_ACCESS_READ_WRITE, sizeof(communication->producer_heartbeat_time));
	}else if(index == OD_INDEX_IDENTITY_OBJECT){
		return read_or_write(value, &communication->identity_object[sub_index], write_value, force, OD_ACCESS_READ_WRITE, sizeof(communication->identity_object[sub_index]));
	}else if(index == OD_INDEX_SYNCHRONOUS_COUNTER_OVERFLOW_VALUE){
		return read_or_write(value, &communication->synchronous_counter_overflow_value, write_value, force, OD_ACCESS_READ_WRITE, sizeof(communication->synchronous_counter_overflow_value));
	}else if(index == OD_INDEX_VERIFY_CONFIGURATION){
		return read_or_write(value, &communication->verify_configuration[sub_index], write_value, force, OD_ACCESS_READ_WRITE, sizeof(communication->verify_configuration[sub_index]));
	}else if(index == OD_INDEX_EMERGENCY_CONSUMER_OBJECT){
		return read_or_write(value, &communication->emergency_consumer_object[sub_index], write_value, force, OD_ACCESS_READ_WRITE, sizeof(communication->emergency_consumer_object[sub_index]));
	}else if(index == OD_INDEX_ERROR_BEHAVIOR_OBJECT){
		return read_or_write(value, &communication->error_behavior_object[sub_index], write_value, force, OD_ACCESS_READ_WRITE, sizeof(communication->error_behavior_object[sub_index]));
	}
	return OD_STATUS_NOT_FOUND;
}

static OD_STATUS read_or_write(uint32_t *value, void *struct_value, bool write_value, bool force, OD_ACCESS access, OD_DATA_TYPE data_type_struct_value){
	if(write_value){
		if(access == OD_ACCESS_READ_WRITE || force){
			if(data_type_struct_value == OD_DATA_TYPE_U8)
				*((uint8_t*) struct_value) = *value;
			if(data_type_struct_value == OD_DATA_TYPE_U16)
				*((uint16_t*) struct_value) = *value;
			if(data_type_struct_value == OD_DATA_TYPE_U32)
				*((uint32_t*) struct_value) = *value;
			return OD_STATUS_OK;
		}
	}else{
		if(access == OD_ACCESS_READ_WRITE || force){
			if(data_type_struct_value == OD_DATA_TYPE_U8)
				*value = *((uint8_t*) struct_value);
			if(data_type_struct_value == OD_DATA_TYPE_U16)
				*value = *((uint16_t*) struct_value);
			if(data_type_struct_value == OD_DATA_TYPE_U32)
				*value = *((uint32_t*) struct_value);
			return OD_STATUS_OK;
		}
	}
	return OD_STATUS_NOT_PERMITTED;
}
