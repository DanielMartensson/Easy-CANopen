/*
 * Easy_CANopen_This_Node.c
 *
 *  Created on: 19 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "Easy_CANopen.h"

/*
 * Set the heartbeat time in milliseconds. If heartbeat time is 0, then HEARTBEAT service is deactivated and GUARD is enabled.
 */
void Easy_CANopen_This_Node_Configure_Heartbeat_Interval(CANopen *canopen, uint16_t interval_ms){
	canopen->od_communication.producer_heartbeat_time = interval_ms; /* If this is zero, then heartbeat will be disabled */
}

/*
 * Set the guard time in milliseconds and life time factor for the GUARD service. This is a limit for a guard response and the limit is guard time multiply with life time factor.
 */
void Easy_CANopen_This_Node_Configure_Guard_Time_And_Life_Factor(CANopen *canopen, uint16_t guard_time_ms, uint8_t life_factor){
	canopen->od_communication.guard_time = guard_time_ms;
	canopen->od_communication.life_time_factor = life_factor;
}

/*
 * This clean up the error register and the predefined errors in this node.
 */
void Easy_CANopen_This_Node_Empty_Error_Messages(CANopen *canopen){
	canopen->od_communication.error_register = 0;
	memset(canopen->od_communication.pre_defined_error_field, 0, sizeof(canopen->od_communication.pre_defined_error_field)/sizeof(canopen->od_communication.pre_defined_error_field[0]));
}
