/*
 * DO.h
 *
 *  Created on: 14 okt. 2021
 *      Author: Danie Mårtensson
 */

#ifndef CANOPEN_OD_OD_H_
#define CANOPEN_OD_OD_H_

#include "../../Easy_CANopen/Structs.h"

/* Handlers for dictionary objects */
OD_STATUS CANopen_OD_Set_Get_Value(CANopen *canopen, uint16_t index, uint8_t sub_index, bool write_value, void *value, OD_DATA_TYPE data_type);
OD_DATA_TYPE CANopen_OD_Get_Size_Data_Type(CANopen *canopen, uint16_t index, uint8_t sub_index);


#endif /* CANOPEN_OD_OD_H_ */
