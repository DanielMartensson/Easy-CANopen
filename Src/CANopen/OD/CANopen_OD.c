/*
 * CANopen_OD.c
 *
 *  Created on: 13 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "OD.h"

static OD_STATUS read_or_write(uint32_t *value, void *struct_value, bool set, OD_ACCESS access, OD_DATA_TYPE data_type);

OD_DATA_TYPE CANopen_OD_Get_Data_Type(CANopen *canopen, uint16_t index, uint8_t sub_index){

	/* Initial settings */
	bool set = false;
	uint32_t value;
	uint32_t byte_size;
	OD_DATA_TYPE data_type;
	uint8_t* byte_pointer = NULL;
	OD_ACCESS access;

	/* Get the data type from the bank and return it back */
	CANopen_OD_Bank(canopen, index, sub_index, set, &value, &byte_size, &data_type, byte_pointer, &access);
	return data_type;
}

uint32_t CANopen_OD_Get_Byte_Size(CANopen *canopen, uint16_t index, uint8_t sub_index){

	/* Initial settings */
	bool set = false;
	uint32_t value;
	uint32_t byte_size;
	OD_DATA_TYPE data_type;
	uint8_t* byte_pointer = NULL;
	OD_ACCESS access;

	/* Get the byte size from the bank and return it back */
	CANopen_OD_Bank(canopen, index, sub_index, set, &value, &byte_size, &data_type, byte_pointer, &access);
	return byte_size;
}

uint8_t *CANopen_OD_Get_Byte_Pointer(CANopen *canopen, uint16_t index, uint8_t sub_index){

	/* Initial settings */
	bool set = false;
	uint32_t value;
	uint32_t byte_size;
	OD_DATA_TYPE data_type;
	uint8_t* byte_pointer = NULL;
	OD_ACCESS access;

	/* Get the byte pointer from the bank and return it back */
	CANopen_OD_Bank(canopen, index, sub_index, set, &value, &byte_size, &data_type, byte_pointer, &access);
	return byte_pointer;
}

uint32_t CANopen_OD_Get_Value(CANopen *canopen, uint16_t index, uint8_t sub_index){
	/* Initial settings */
	bool set = false;
	uint32_t value;
	uint32_t byte_size;
	OD_DATA_TYPE data_type;
	uint8_t* byte_pointer = NULL;
	OD_ACCESS access;

	/* Get the byte pointer from the bank and return it back */
	CANopen_OD_Bank(canopen, index, sub_index, set, &value, &byte_size, &data_type, byte_pointer, &access);
	return value;
}

OD_STATUS CANopen_OD_Set_Value(CANopen *canopen, uint16_t index, uint8_t sub_index, uint32_t value){
	/* Initial settings */
	bool set = true;
	uint32_t byte_size;
	OD_DATA_TYPE data_type;
	uint8_t* byte_pointer = NULL;
	OD_ACCESS access;

	/* Get the byte pointer from the bank and return it back */
	return CANopen_OD_Bank(canopen, index, sub_index, set, &value, &byte_size, &data_type, byte_pointer, &access);
}

OD_STATUS CANopen_OD_Bank(CANopen *canopen, uint16_t index, uint8_t sub_index, bool set, uint32_t *value, uint32_t *byte_size, OD_DATA_TYPE *data_type, uint8_t *byte_pointer, OD_ACCESS *access){
	struct OD_Communication *communication = &canopen->od_communication;
	if(index == OD_INDEX_DEVICE_TYPE && sub_index == 0){
		*byte_size = sizeof(communication->device_type);
		*data_type = sizeof(communication->device_type);
		byte_pointer = (uint8_t*) &communication->device_type;
		*access = OD_ACCESS_READ;
		return read_or_write(value, &communication->device_type, set, *access, *data_type);
	}else if(index == OD_INDEX_ERROR_REGISTER && sub_index == 0){
		*byte_size = sizeof(communication->error_register);
		*data_type = sizeof(communication->error_register);
		byte_pointer = (uint8_t*) &communication->error_register;
		*access = OD_ACCESS_READ;
		return read_or_write(value, &communication->error_register, set, *access, *data_type);
	}else if(index == OD_INDEX_MANUFACTURER_STATUS_REGISTER && sub_index == 0){
		*byte_size = sizeof(communication->manufacturer_status_register);
		*data_type = sizeof(communication->manufacturer_status_register);
		byte_pointer = (uint8_t*) &communication->manufacturer_status_register;
		*access = OD_ACCESS_READ;
		return read_or_write(value, &communication->manufacturer_status_register, set, *access, *data_type);
	}else if(index == OD_INDEX_PRE_DEFINED_ERROR_FIELD && sub_index < PRE_DEFINED_ERROR_FIELD_MAX_SUB_INDEX){
		*byte_size = sizeof(communication->pre_defined_error_field);
		*data_type = OD_DATA_TYPE_ARRAY;
		byte_pointer = (uint8_t*) communication->pre_defined_error_field;
		*access = OD_ACCESS_READ;
		return read_or_write(value, &communication->pre_defined_error_field[sub_index], set, *access, *data_type);
	}else if(index == OD_INDEX_COB_ID_SYNC_MESSAGE && sub_index == 0){
		*byte_size = sizeof(communication->COB_ID_sync_message);
		*data_type = sizeof(communication->COB_ID_sync_message);
		byte_pointer = (uint8_t*) &communication->COB_ID_sync_message;
		*access = OD_ACCESS_READ_WRITE;
		return read_or_write(value, &communication->COB_ID_sync_message, set, *access, *data_type);
	}else if(index == OD_INDEX_COMMUNICATION_CYCLE_PERIOD && sub_index == 0){
		*byte_size = sizeof(communication->communication_cycle_period);
		*data_type = sizeof(communication->communication_cycle_period);
		byte_pointer = (uint8_t*) &communication->communication_cycle_period;
		*access = OD_ACCESS_READ_WRITE;
		return read_or_write(value, &communication->communication_cycle_period, set, *access, *data_type);
	}else if(index == OD_INDEX_SYNCHRONOUS_WINDOW_LENGTH && sub_index == 0){
		*byte_size = sizeof(communication->synchronous_window_length);
		*data_type = sizeof(communication->synchronous_window_length);
		byte_pointer = (uint8_t*) &communication->synchronous_window_length;
		*access = OD_ACCESS_READ_WRITE;
		return read_or_write(value, &communication->synchronous_window_length, set, *access, *data_type);
	}else if(index == OD_INDEX_MANUFACTURER_DEVICE_NAME && sub_index < OD_STRING_LENGTH){
		*byte_size = sizeof(communication->manufacturer_device_name);
		*data_type = OD_DATA_TYPE_ARRAY;
		byte_pointer = (uint8_t*) communication->manufacturer_device_name;
		*access = OD_ACCESS_READ;
		return read_or_write(value, &communication->manufacturer_device_name, set, *access, *data_type);
	}else if(index == OD_INDEX_MANUFACTURER_HARDWARE_VERSION && sub_index < OD_STRING_LENGTH){
		*byte_size = sizeof(communication->manufacturer_hardware_version);
		*data_type = OD_DATA_TYPE_ARRAY;
		byte_pointer = (uint8_t*) communication->manufacturer_hardware_version;
		*access = OD_ACCESS_READ;
		return read_or_write(value, &communication->manufacturer_hardware_version, set, *access, *data_type);
	}else if(index == OD_INDEX_MANUFACTURER_SOFTWARE_VERSION && sub_index < OD_STRING_LENGTH){
		*byte_size = sizeof(communication->manufacturer_software_version);
		*data_type = OD_DATA_TYPE_ARRAY;
		byte_pointer = (uint8_t*) communication->manufacturer_software_version;
		*access = OD_ACCESS_READ;
		return read_or_write(value, &communication->manufacturer_software_version, set, *access, *data_type);
	}else if(index == OD_INDEX_GUARD_TIME_MS && sub_index == 0){
		*byte_size = sizeof(communication->guard_time);
		*data_type = sizeof(communication->guard_time);
		byte_pointer = (uint8_t*) &communication->guard_time;
		*access = OD_ACCESS_READ_WRITE;
		return read_or_write(value, &communication->guard_time, set, *access, *data_type);
	}else if(index == OD_INDEX_LIFE_FACTOR && sub_index == 0){
		*byte_size = sizeof(communication->life_time_factor);
		*data_type = sizeof(communication->life_time_factor);
		byte_pointer = (uint8_t*) &communication->life_time_factor;
		*access = OD_ACCESS_READ_WRITE;
		return read_or_write(value, &communication->life_time_factor, set, *access, *data_type);
	}else if(index == OD_INDEX_STORE_PARAMETERS && sub_index < STORE_RE_STORE_PARAMETER_MAX_SUB_INDEX){
		*byte_size = sizeof(communication->store_parameters);
		*data_type = OD_DATA_TYPE_ARRAY;
		byte_pointer = (uint8_t*) communication->store_parameters;
		*access = OD_ACCESS_READ_WRITE;
		return read_or_write(value, &communication->store_parameters[sub_index], set, *access, *data_type);
	}else if(index == OD_INDEX_RESTORE_DEFAULT_PARAMETERS && sub_index < STORE_RE_STORE_PARAMETER_MAX_SUB_INDEX){
		*byte_size = sizeof(communication->restore_default_parameters);
		*data_type = OD_DATA_TYPE_ARRAY;
		byte_pointer = (uint8_t*) communication->restore_default_parameters;
		*access = OD_ACCESS_READ_WRITE;
		return read_or_write(value, &communication->restore_default_parameters[sub_index], set, *access, *data_type);
	}else if(index == OD_INDEX_COB_ID_TIME_STAMP_OBJECT && sub_index == 0){
		*byte_size = sizeof(communication->COB_ID_time_stamp_object);
		*data_type = sizeof(communication->COB_ID_time_stamp_object);
		byte_pointer = (uint8_t*) &communication->COB_ID_time_stamp_object;
		*access = OD_ACCESS_READ_WRITE;
		return read_or_write(value, &communication->COB_ID_time_stamp_object, set, *access, *data_type);
	}else if(index == OD_INDEX_HIGH_RESOLUTION_TIME_STAMP && sub_index == 0){
		*byte_size = sizeof(communication->high_resolution_time_stamp);
		*data_type = sizeof(communication->high_resolution_time_stamp);
		byte_pointer = (uint8_t*) &communication->high_resolution_time_stamp;
		*access = OD_ACCESS_READ_WRITE;
		return read_or_write(value, &communication->high_resolution_time_stamp, set, *access, *data_type);
	}else if(index == OD_INDEX_COB_ID_EMCY && sub_index == 0){
		*byte_size = sizeof(communication->COB_ID_emcy);
		*data_type = sizeof(communication->COB_ID_emcy);
		byte_pointer = (uint8_t*) &communication->COB_ID_emcy;
		*access = OD_ACCESS_READ_WRITE;
		return read_or_write(value, &communication->COB_ID_emcy, set, *access, *data_type);
	}else if(index == OD_INDEX_CONSUMER_HEARTBEAT_TIME && sub_index < CONSUMER_HEARTBEAT_TIME_MAX_SUB_INDEX){
		*byte_size = sizeof(communication->consumer_heartbeat_time);
		*data_type = OD_DATA_TYPE_ARRAY;
		byte_pointer = (uint8_t*) communication->consumer_heartbeat_time;
		*access = OD_ACCESS_READ_WRITE;
		return read_or_write(value, &communication->consumer_heartbeat_time[sub_index], set, *access, *data_type);
	}else if(index == OD_INDEX_PRODUCER_HEARTBEAT_TIME && sub_index == 0){
		*byte_size = sizeof(communication->producer_heartbeat_time);
		*data_type = sizeof(communication->producer_heartbeat_time);
		byte_pointer = (uint8_t*) &communication->producer_heartbeat_time;
		*access = OD_ACCESS_READ_WRITE;
		return read_or_write(value, &communication->producer_heartbeat_time, set, *access, *data_type);
	}else if(index == OD_INDEX_IDENTITY_OBJECT && sub_index == 0x0){
		*byte_size = sizeof(communication->identity_object_highest_supported_sub_index);
		*data_type = sizeof(communication->identity_object_highest_supported_sub_index);
		byte_pointer = (uint8_t*) &communication->identity_object_highest_supported_sub_index;
		*access = OD_ACCESS_READ;
		return read_or_write(value, &communication->identity_object_highest_supported_sub_index, set, *access, *data_type);
	}else if(index == OD_INDEX_IDENTITY_OBJECT && sub_index == 0x1){
		*byte_size = sizeof(communication->vendor_ID);
		*data_type = sizeof(communication->vendor_ID);
		byte_pointer = (uint8_t*) &communication->vendor_ID;
		*access = OD_ACCESS_READ;
		return read_or_write(value, &communication->vendor_ID, set, *access, *data_type);
	}else if(index == OD_INDEX_IDENTITY_OBJECT && sub_index == 0x2){
		*byte_size = sizeof(communication->product_code);
		*data_type = sizeof(communication->product_code);
		byte_pointer = (uint8_t*) &communication->product_code;
		*access = OD_ACCESS_READ;
		return read_or_write(value, &communication->product_code, set, *access, *data_type);
	}else if(index == OD_INDEX_IDENTITY_OBJECT && sub_index == 0x3){
		*byte_size = sizeof(communication->revision_number);
		*data_type = sizeof(communication->revision_number);
		byte_pointer = (uint8_t*) &communication->revision_number;
		*access = OD_ACCESS_READ;
		return read_or_write(value, &communication->revision_number, set, *access, *data_type);
	}else if(index == OD_INDEX_IDENTITY_OBJECT && sub_index == 0x4){
		*byte_size = sizeof(communication->serial_number);
		*data_type = sizeof(communication->serial_number);
		byte_pointer = (uint8_t*) &communication->serial_number;
		*access = OD_ACCESS_READ;
		return read_or_write(value, &communication->serial_number, set, *access, *data_type);
	}else if(index == OD_INDEX_SYNCHRONOUS_COUNTER_OVERFLOW_VALUE && sub_index == 0){
		*byte_size = sizeof(communication->synchronous_counter_overflow_value);
		*data_type = sizeof(communication->synchronous_counter_overflow_value);
		byte_pointer = (uint8_t*) &communication->synchronous_counter_overflow_value;
		*access = OD_ACCESS_READ_WRITE;
		return read_or_write(value, &communication->synchronous_counter_overflow_value, set, *access, *data_type);
	}else if(index == OD_INDEX_VERIFY_CONFIGURATION && sub_index < VERIFY_CONFIGURATION_MAX_SUB_INDEX){
		*byte_size = sizeof(communication->verify_configuration);
		*data_type = OD_DATA_TYPE_ARRAY;
		byte_pointer = (uint8_t*) communication->verify_configuration;
		*access = OD_ACCESS_READ_WRITE;
		return read_or_write(value, &communication->verify_configuration[sub_index], set, *access, *data_type);
	}else if(index == OD_INDEX_EMERGENCY_CONSUMER_OBJECT && sub_index < EMERGENCY_CONSUMER_MAX_SUB_INDEX){
		*byte_size = sizeof(communication->emergency_consumer_object);
		*data_type = OD_DATA_TYPE_ARRAY;
		byte_pointer = (uint8_t*) communication->emergency_consumer_object;
		*access = OD_ACCESS_READ_WRITE;
		return read_or_write(value, &communication->emergency_consumer_object[sub_index], set, *access, *data_type);
	}else if(index == OD_INDEX_ERROR_BEHAVIOR_OBJECT && sub_index < ERROR_BEHAVIOR_SUB_INDEX){
		*byte_size = sizeof(communication->error_behavior_object);
		*data_type = OD_DATA_TYPE_ARRAY;
		byte_pointer = (uint8_t*) communication->error_behavior_object;
		*access = OD_ACCESS_READ_WRITE;
		return read_or_write(value, &communication->error_behavior_object[sub_index], set, *access, *data_type);
	}
	return OD_STATUS_NOT_FOUND;
}

static OD_STATUS read_or_write(uint32_t *value, void *struct_value, bool set, OD_ACCESS access, OD_DATA_TYPE data_type){
	if(set){
		if(access | OD_ACCESS_WRITE){
			switch(data_type){
			case OD_DATA_TYPE_U8:
				*((uint8_t*) struct_value) = *value;
				break;
			case OD_DATA_TYPE_U16:
				*((uint16_t*) struct_value) = *value;
				break;
			case OD_DATA_TYPE_U32:
				*((uint32_t*) struct_value) = *value;
				break;
			default:
				return OD_STATUS_WRONG_DATA_TYPE;
			}
			return OD_STATUS_OK;
		}else{
			return OD_STATUS_NOT_PERMITTED;
		}
	}else{
		if(access | OD_ACCESS_READ){
			switch(data_type){
			case OD_DATA_TYPE_U8:
				*value = *((uint8_t*) struct_value);
				break;
			case OD_DATA_TYPE_U16:
				*value = *((uint16_t*) struct_value);
				break;
			case OD_DATA_TYPE_U32:
				*value = *((uint32_t*) struct_value);
				break;
			default:
				return OD_STATUS_WRONG_DATA_TYPE;
			}
			return OD_STATUS_OK;
		}else{
			return OD_STATUS_NOT_PERMITTED;
		}
	}
	return OD_STATUS_NOT_FOUND;
}
