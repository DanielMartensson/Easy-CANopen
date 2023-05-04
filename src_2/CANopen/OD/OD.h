/*
 * DO.h
 *
 *  Created on: 14 okt. 2021
 *      Author: Danie Mårtensson
 */

#ifndef CANOPEN_OD_OD_H_
#define CANOPEN_OD_OD_H_

#include "../../Easy_CANopen/Easy_CANopen_Structs.h"

OD_DATA_TYPE CANopen_OD_Get_Data_Type(CANopen *canopen, uint16_t index, uint8_t sub_index);
uint32_t CANopen_OD_Get_Byte_Size(CANopen *canopen, uint16_t index, uint8_t sub_index);
uint8_t *CANopen_OD_Get_Byte_Pointer(CANopen *canopen, uint16_t index, uint8_t sub_index);
uint32_t CANopen_OD_Get_Value(CANopen *canopen, uint16_t index, uint8_t sub_index);
OD_STATUS CANopen_OD_Set_Value(CANopen *canopen, uint16_t index, uint8_t sub_index, uint32_t value);
OD_STATUS CANopen_OD_Bank(CANopen *canopen, uint16_t index, uint8_t sub_index, bool set, uint32_t *value, uint32_t *byte_size, OD_DATA_TYPE *data_type, uint8_t *byte_pointer, OD_ACCESS *access);

#endif /* CANOPEN_OD_OD_H_ */
