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
	/* Check if heartbeat is enabled */
	if(!canopen->producer.time.is_enabled)
		return;

	/* Send out a message if it has pass the threshold of 1 second, then reset, or else count */
	if(canopen->producer.time.count_tick < 1000){
		canopen->producer.time.count_tick++;
		return;
	}
	canopen->producer.time.count_tick = 0;

	/* Get the real clock */
	uint8_t date, month, hour, minute, second;
	uint16_t year;
	Hardware_Get_RTC_Clock_Time(&date, &month, &year, &hour, &minute, &second);
	canopen->producer.time.milliseconds_since_midnight = second*1000 + minute*60000 + hour*3600000; /* To milliseconds */
	canopen->producer.time.days_since_1_januari_1984 = 0; /* Start counting days that have pass since 1 January 1984 */
	for(uint16_t y = 1984; y < year; y++)
		canopen->producer.time.days_since_1_januari_1984 += (y % 4 == 0) || (y % 400 == 0) ? 366 : 365; /* Leap year, not leap year */
	for(uint8_t m = 1; m < month; m++)
		if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
			canopen->producer.time.days_since_1_januari_1984 += 31;
		else if(m == 2)
			canopen->producer.time.days_since_1_januari_1984 += 28; /* Leap */
		else
			canopen->producer.time.days_since_1_januari_1984 += 30;
	canopen->producer.time.days_since_1_januari_1984 += date - 1; /* Days since, does not includes this day */

	/* Send data */
	uint8_t data[8] = {0};
	data[0] = canopen->producer.time.milliseconds_since_midnight;
	data[1] = canopen->producer.time.milliseconds_since_midnight >> 8;
	data[2] = canopen->producer.time.milliseconds_since_midnight >> 16;
	data[3] = canopen->producer.time.milliseconds_since_midnight >> 24;
	data[4] = data[1] = canopen->producer.time.days_since_1_januari_1984;
	data[5] = data[1] = canopen->producer.time.days_since_1_januari_1984 >> 8;
	CAN_Send_Message(FUNCTION_CODE_TIME, data);
}
