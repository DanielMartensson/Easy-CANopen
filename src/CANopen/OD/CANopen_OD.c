/*
 * CANopen_OD.c
 *
 *  Created on: 13 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "OD.h"

static OD_STATUS read_or_write(uint32_t *value, void *struct_value, bool set, OD_ACCESS access, OD_DATA_TYPE data_type);

OD_STATUS CANopen_OD_Set_Get_Value(CANopen *canopen, uint16_t index, uint8_t sub_index, bool set, void *value, OD_DATA_TYPE data_type){
	struct OD_Communication *communication = &canopen->od_communication;
	if(index == OD_INDEX_DEVICE_TYPE && sub_index == 0)
		return read_or_write(value, &communication->device_type, set, OD_ACCESS_READ, data_type);
	else if(index == OD_INDEX_ERROR_REGISTER && sub_index == 0)
		return read_or_write(value, &communication->error_register, set, OD_ACCESS_READ, data_type);
	else if(index == OD_INDEX_MANUFACTURER_STATUS_REGISTER && sub_index == 0)
		return read_or_write(value, &communication->manufacturer_status_register, set, OD_ACCESS_READ, data_type);
	else if(index == OD_INDEX_PRE_DEFINED_ERROR_FIELD && sub_index < PRE_DEFINED_ERROR_FIELD_MAX_SUB_INDEX)
		return read_or_write(value, &communication->pre_defined_error_field[sub_index], set, OD_ACCESS_READ, data_type);
	else if(index == OD_INDEX_COB_ID_SYNC_MESSAGE && sub_index == 0)
		return read_or_write(value, &communication->COB_ID_sync_message, set, OD_ACCESS_READ_WRITE, data_type);
	else if(index == OD_INDEX_COMMUNICATION_CYCLE_PERIOD && sub_index == 0)
		return read_or_write(value, &communication->communication_cycle_period, set, OD_ACCESS_READ_WRITE, data_type);
	else if(index == OD_INDEX_SYNCHRONOUS_WINDOW_LENGTH && sub_index == 0)
		return read_or_write(value, &communication->synchronous_window_length, set, OD_ACCESS_READ_WRITE, data_type);
	else if(index == OD_INDEX_MANUFACTURER_DEVICE_NAME && sub_index == 0)
		return read_or_write(value, &communication->manufacturer_device_name, set, OD_ACCESS_READ, data_type);
	else if(index == OD_INDEX_MANUFACTURER_HARDWARE_VERSION && sub_index == 0)
		return read_or_write(value, &communication->manufacturer_hardware_version, set, OD_ACCESS_READ, data_type);
	else if(index == OD_INDEX_MANUFACTURER_SOFTWARE_VERSION && sub_index == 0)
		return read_or_write(value, &communication->manufacturer_software_version, set, OD_ACCESS_READ, data_type);
	else if(index == OD_INDEX_GUARD_TIME_MS && sub_index == 0)
		return read_or_write(value, &communication->guard_time, set, OD_ACCESS_READ_WRITE, data_type);
	else if(index == OD_INDEX_LIFE_FACTOR && sub_index == 0)
		return read_or_write(value, &communication->life_time_factor, set, OD_ACCESS_READ_WRITE, data_type);
	else if(index == OD_INDEX_STORE_PARAMETERS && sub_index < STORE_RE_STORE_PARAMETER_MAX_SUB_INDEX)
		return read_or_write(value, &communication->store_parameters[sub_index], set, OD_ACCESS_READ_WRITE, data_type);
	else if(index == OD_INDEX_RESTORE_DEFAULT_PARAMETERS && sub_index < STORE_RE_STORE_PARAMETER_MAX_SUB_INDEX)
		return read_or_write(value, &communication->restore_default_parameters[sub_index], set, OD_ACCESS_READ_WRITE, data_type);
	else if(index == OD_INDEX_COB_ID_TIME_STAMP_OBJECT && sub_index == 0)
		return read_or_write(value, &communication->COB_ID_time_stamp_object, set, OD_ACCESS_READ_WRITE, data_type);
	else if(index == OD_INDEX_HIGH_RESOLUTION_TIME_STAMP && sub_index == 0)
		return read_or_write(value, &communication->high_resolution_time_stamp, set, OD_ACCESS_READ_WRITE, data_type);
	else if(index == OD_INDEX_COB_ID_EMCY && sub_index == 0)
		return read_or_write(value, &communication->COB_ID_emcy, set, OD_ACCESS_READ_WRITE, data_type);
	else if(index == OD_INDEX_INHIBIT_TIME_EMCY && sub_index == 0)
		return read_or_write(value, &communication->inhibit_time_emcy, set, OD_ACCESS_READ_WRITE, data_type);
	else if(index == OD_INDEX_CONSUMER_HEARTBEAT_TIME && sub_index < CONSUMER_HEARTBEAT_TIME_MAX_SUB_INDEX)
		return read_or_write(value, &communication->consumer_heartbeat_time[sub_index], set, OD_ACCESS_READ_WRITE, data_type);
	else if(index == OD_INDEX_PRODUCER_HEARTBEAT_TIME && sub_index == 0)
		return read_or_write(value, &communication->producer_heartbeat_time, set, OD_ACCESS_READ_WRITE, data_type);
	else if(index == OD_INDEX_IDENTITY_OBJECT && sub_index < IDENTITY_MAX_OBJECT_MAX_SUB_INDEX)
		return read_or_write(value, &communication->identity_object[sub_index], set, OD_ACCESS_READ_WRITE, data_type);
	else if(index == OD_INDEX_SYNCHRONOUS_COUNTER_OVERFLOW_VALUE && sub_index == 0)
		return read_or_write(value, &communication->synchronous_counter_overflow_value, set, OD_ACCESS_READ_WRITE, data_type);
	else if(index == OD_INDEX_VERIFY_CONFIGURATION && sub_index < VERIFY_CONFIGURATION_MAX_SUB_INDEX)
		return read_or_write(value, &communication->verify_configuration[sub_index], set, OD_ACCESS_READ_WRITE, data_type);
	else if(index == OD_INDEX_EMERGENCY_CONSUMER_OBJECT && sub_index < EMERGENCY_CONSUMER_MAX_SUB_INDEX)
		return read_or_write(value, &communication->emergency_consumer_object[sub_index], set, OD_ACCESS_READ_WRITE, data_type);
	else if(index == OD_INDEX_ERROR_BEHAVIOR_OBJECT && sub_index < ERROR_BEHAVIOR_SUB_INDEX)
		return read_or_write(value, &communication->error_behavior_object[sub_index], set, OD_ACCESS_READ_WRITE, data_type);
	return OD_STATUS_NOT_FOUND;
}

OD_DATA_TYPE CANopen_OD_Get_Size_Data_Type(CANopen *canopen, uint16_t index, uint8_t sub_index){
	struct OD_Communication *communication = &canopen->od_communication;
	if(index == OD_INDEX_DEVICE_TYPE && sub_index == 0)
		return sizeof(communication->device_type);
	else if(index == OD_INDEX_ERROR_REGISTER && sub_index == 0)
		return sizeof(communication->error_register);
	else if(index == OD_INDEX_MANUFACTURER_STATUS_REGISTER && sub_index == 0)
		return sizeof(communication->manufacturer_status_register);
	else if(index == OD_INDEX_PRE_DEFINED_ERROR_FIELD && sub_index < PRE_DEFINED_ERROR_FIELD_MAX_SUB_INDEX)
		return sizeof(communication->pre_defined_error_field/communication->pre_defined_error_field[0]);
	else if(index == OD_INDEX_COB_ID_SYNC_MESSAGE && sub_index == 0)
		return sizeof(communication->COB_ID_sync_message);
	else if(index == OD_INDEX_COMMUNICATION_CYCLE_PERIOD && sub_index == 0)
		return sizeof(communication->communication_cycle_period);
	else if(index == OD_INDEX_SYNCHRONOUS_WINDOW_LENGTH && sub_index == 0)
		return sizeof(communication->synchronous_window_length);
	else if(index == OD_INDEX_MANUFACTURER_DEVICE_NAME && sub_index == 0)
		return sizeof(communication->manufacturer_device_name);
	else if(index == OD_INDEX_MANUFACTURER_HARDWARE_VERSION && sub_index == 0)
		return sizeof(communication->manufacturer_hardware_version);
	else if(index == OD_INDEX_MANUFACTURER_SOFTWARE_VERSION && sub_index == 0)
		return sizeof(communication->manufacturer_software_version);
	else if(index == OD_INDEX_GUARD_TIME_MS && sub_index == 0)
		return sizeof(communication->guard_time);
	else if(index == OD_INDEX_LIFE_FACTOR && sub_index == 0)
		return sizeof(communication->life_time_factor);
	else if(index == OD_INDEX_STORE_PARAMETERS && sub_index < STORE_RE_STORE_PARAMETER_MAX_SUB_INDEX)
		return sizeof(communication->store_parameters/communication->store_parameters[0]);
	else if(index == OD_INDEX_RESTORE_DEFAULT_PARAMETERS && sub_index < STORE_RE_STORE_PARAMETER_MAX_SUB_INDEX)
		return sizeof(communication->restore_default_parameters/communication->restore_default_parameters[0]);
	else if(index == OD_INDEX_COB_ID_TIME_STAMP_OBJECT && sub_index == 0)
		return sizeof(communication->COB_ID_time_stamp_object);
	else if(index == OD_INDEX_HIGH_RESOLUTION_TIME_STAMP && sub_index == 0)
		return sizeof(communication->high_resolution_time_stamp);
	else if(index == OD_INDEX_COB_ID_EMCY && sub_index == 0)
		return sizeof(communication->COB_ID_emcy);
	else if(index == OD_INDEX_INHIBIT_TIME_EMCY && sub_index == 0)
		return sizeof(communication->inhibit_time_emcy);
	else if(index == OD_INDEX_CONSUMER_HEARTBEAT_TIME && sub_index < CONSUMER_HEARTBEAT_TIME_MAX_SUB_INDEX)
		return sizeof(communication->consumer_heartbeat_time/communication->consumer_heartbeat_time[0]);
	else if(index == OD_INDEX_PRODUCER_HEARTBEAT_TIME && sub_index == 0)
		return sizeof(communication->producer_heartbeat_time);
	else if(index == OD_INDEX_IDENTITY_OBJECT && sub_index < IDENTITY_MAX_OBJECT_MAX_SUB_INDEX)
		return sizeof(communication->identity_object/communication->identity_object[0]);
	else if(index == OD_INDEX_SYNCHRONOUS_COUNTER_OVERFLOW_VALUE && sub_index == 0)
		return sizeof(communication->synchronous_counter_overflow_value);
	else if(index == OD_INDEX_VERIFY_CONFIGURATION && sub_index < VERIFY_CONFIGURATION_MAX_SUB_INDEX)
		return sizeof(communication->verify_configuration/communication->verify_configuration[0]);
	else if(index == OD_INDEX_EMERGENCY_CONSUMER_OBJECT && sub_index < EMERGENCY_CONSUMER_MAX_SUB_INDEX)
		return sizeof(communication->emergency_consumer_object/communication->emergency_consumer_object[0]);
	else if(index == OD_INDEX_ERROR_BEHAVIOR_OBJECT && sub_index < ERROR_BEHAVIOR_SUB_INDEX)
		return sizeof(communication->error_behavior_object/communication->error_behavior_object[0]);
	return 0;
}

static OD_STATUS read_or_write(void *value, void *struct_value, bool set, OD_ACCESS access, OD_DATA_TYPE data_type){
	switch(set){
	case true:
		switch(access | OD_ACCESS_WRITE){
		case true:
			switch(data_type){
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
			switch(data_type){
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
