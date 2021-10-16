/*
 * CANopen_Slave_LSS_Receive.c
 *
 *  Created on: 17 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS.h"

STATUS_CODE CANopen_Slave_LSS_Receive_Switch_Mode_Global_Protocol(CANopen *canopen, uint8_t data[]){
	return CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_6, data[0]);
}
