/*
 * CANopen_TIME_Protocol_Produce.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "Easy_CANopen/Easy_CANopen_Structs.h"
#include "TIME_Protocol.h"

/* Layers */
#include "../../../../Hardware/Hardware.h"

/* Utilities */
#include "Utilities/CANopen_TIME/co_time_conversion.h"

void CANopen_TIME_Protocol_Produce_Clock(CANopen *canopen){
	/* Get the real time clock */
	datetime_t now;

	// TODO(fali.unsal): I'm not sure this function call, Because this is blocking call for many processor. Get the time from top layer. Do not in here.
	Easy_CANopen_Hardware_Time_Get_RTC(&now.day, &now.month, &now.year, &now.hour, &now.minute, &now.second);

	TIME CO_Time;

	if (co_time_dt_to_cotime(&now, &CO_Time))
	{
		/* Set data */
		uint8_t data[8] = {0};

		// TODO(fali.unsal): Should we check the endianness of the target device here?
		data[0] = (uint8_t)(CO_Time.milliseconds & 0xFFU);
		data[1] = (uint8_t)((CO_Time.milliseconds >> 8U) & 0xFFU);
		data[2] = (uint8_t)((CO_Time.milliseconds >> 16U) & 0xFFU);
		data[3] = (uint8_t)((CO_Time.milliseconds >> 24U) & 0xFFU);

		data[4] = (uint8_t)(CO_Time.days & 0xFFU);
		data[5] = (uint8_t)((CO_Time.days >> 8U) & 0xFFU);
	
		/* Create the COB ID */
		uint16_t COB_ID = FUNCTION_CODE_TIME << 7U;	/* Only the master node send out this message */
	
		/* Send the message to client */
		Easy_CANopen_Hardware_CAN_Send_Message(COB_ID, data);
	}
}
