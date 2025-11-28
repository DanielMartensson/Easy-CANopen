#include <stdio.h>
#include <stdlib.h>

/* Include Easy CANopen */
#include "Easy_CANopen/Easy_CANopen.h"

 /* Every time we want to send a CAN message, this function will be called */
void Callback_Function_Send(uint16_t ID, uint8_t DLC, uint8_t data[]) {
	printf("Callback_Function_Send called\n");
	printf("ID = 0x%X\n", ID);
	printf("DLC = %i\n", DLC);
	for (uint8_t i = 0; i < DLC; i++) {
		printf("data[%i] = 0x%X\n", i, data[i]);
	}
	printf("\n");
}

/* Every time we want to read a CAN message, this function will be called */
void Callback_Function_Read(uint16_t* ID, uint8_t data[], bool* is_new_data) {
	printf("Callback_Function_Read called\n");
	*ID = 0xFF;
	for (uint8_t i = 0; i < 8; i++) {
		data[i] = 0xFF;
	}
	*is_new_data = true;
}

/* Apply your delay here */
void Callback_Function_Delay(uint8_t delay){
	/* Place your hardware delay here e.g HAL_Delay(delay); for STM32 */
}

void Callback_Function_Traffic(uint16_t ID, uint8_t DLC, uint8_t data[], bool is_TX) {	
	/* Print if it is TX or RX */
	printf("%s\t", is_TX ? "TX" : "RX");

	/* Print ID as hex */
	printf("%08X\t", ID);

	/* Print the data */
	uint8_t i;
	for (i = 0U; i < DLC; i++) {
		printf("%X\t", data[i]);
	}

	/* Print the non-data */
	for (i = DLC; i < 8U; i++) {
		printf("%X\t", 0U);
	}

	/* New line */
	printf("\n");
}

int main() {

	/* !!!!! DON'T FORGET TO CHANGE THE PROCESSOR_CHOICE to INTERNAL_CALLBACK in Hardware.h !!!!! */
	Easy_CANopen_Hardware_Set_Callback_Functions(NULL, NULL, Callback_Function_Traffic, NULL);

	/* Declare our structures  */
	CANopen master_node = { 0 };
	CANopen slave_node = { 0 }; /* Notice that ONLY one slave node can be connected to the CAN network */

	/* Begin to activate node configuration so we can write our node ID */
	Easy_CANopen_Other_Node_Activate_Node_Configuration(true);

	/* Reading process for the slave node */
	Easy_CANopen_Thread_Listen_Messages(&slave_node);

	/* Set identification to slave */
	uint32_t vendor_ID = 10003;
	uint32_t product_code = 65467;
	uint32_t revision_number = 565;
	uint32_t serial_number = 3234;
	Easy_CANopen_Other_Node_Set_Vendor_ID_To_Node(&master_node, vendor_ID);
	Easy_CANopen_Other_Node_Set_Product_Code_To_Node(&master_node, product_code);
	Easy_CANopen_Other_Node_Set_Revision_Number_To_Node(&master_node, revision_number);
	Easy_CANopen_Other_Node_Set_Serial_Number_To_Node(&master_node, serial_number);

	/* Reading process for the slave */
	Easy_CANopen_Thread_Listen_Messages(&slave_node);
	Easy_CANopen_Thread_Listen_Messages(&slave_node);
	Easy_CANopen_Thread_Listen_Messages(&slave_node);
	Easy_CANopen_Thread_Listen_Messages(&slave_node);

	/* Read the process for the master */
	Easy_CANopen_Thread_Listen_Messages(&master_node);

	/* Display the identifications for slave node */
	printf("Vendor ID = %i\n", slave_node.od_communication.vendor_ID);
	printf("Product code = %i\n", slave_node.od_communication.product_code);
	printf("Revision number = %i\n", slave_node.od_communication.revision_number);
	printf("Serial number = %i\n", slave_node.od_communication.serial_number);

	/* Dispay the response from the slave */
	printf("Response is set: %i\n", master_node.master.lss.selective_value_is_set);

	return 0;
}