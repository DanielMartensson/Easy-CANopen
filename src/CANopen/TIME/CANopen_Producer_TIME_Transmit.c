/*
 * CANopen_Producer_TIME_Transmit.c
 *
 *  Created on: 19 okt. 2021
 *      Author: Daniel Mårtensson
 */


#include "TIME.h"

/* Layers */
#include "../../Hardware/Hardware.h"

void CANopen_Producer_TIME_Transmit_Clock(CANopen *canopen){
	/* Check if this is allowed to produce */
	uint8_t canopen_device_produces_TIME_message = (canopen->od_communication.COB_ID_time_stamp_object >> 30) & 0x1;
	if(!canopen_device_produces_TIME_message)
		return; /* Nope. Not enabled as producer */

	/* Get the real clock */
	uint8_t date, month, hour, minute, second;
	uint16_t year;
	Hardware_Time_Get_RTC(&date, &month, &year, &hour, &minute, &second);
	uint32_t milliseconds_since_midnight = second*1000 + minute*60000 + hour*3600000; /* To milliseconds */
	uint16_t days_since_1_januari_1984 = 0; /* Start counting days that have pass since 1 January 1984 */
	for(uint16_t y = 1984; y < year; y++)
		days_since_1_januari_1984 += (y % 4 == 0) || (y % 400 == 0) ? 366 : 365; /* Leap year, not leap year */
	for(uint8_t m = 1; m < month; m++)
		if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
			days_since_1_januari_1984 += 31;
		else if(m == 2)
			days_since_1_januari_1984 += 28; /* Leap */
		else
			days_since_1_januari_1984 += 30;
	days_since_1_januari_1984 += date - 1; /* Days since, does not includes this day */

	/* Send data */
	uint8_t data[8] = {0};
	data[0] = milliseconds_since_midnight;
	data[1] = milliseconds_since_midnight >> 8;
	data[2] = milliseconds_since_midnight >> 16;
	data[3] = milliseconds_since_midnight >> 24;
	data[4] = days_since_1_januari_1984;
	data[5] = days_since_1_januari_1984 >> 8;
	Hardware_CAN_Send_Message(FUNCTION_CODE_TIME, data);
}
