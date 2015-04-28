/// roboticArm.c

//OWENS FRAMEWORK:

#include "roveIncludes/roveWareHeaders/roboticArm.h"

// BIOS_start in main inits this as the roveTcpHandlerTask Thread

// this is a RoverMotherboard.cfg object::roveTcpHandlerTask::		priority 2, vital_flag = t, 2048 persistent private stack

void roboticArm(UArg arg0, UArg arg1){

	System_printf("Enter roboticArm TASK\n");
	System_flush();

	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
	extern UART_Handle uart7;

	char buffer[] = "This is a test of uart 0";

	System_printf("Testing uarts in TASK\n");
	System_flush();

	UART_write(uart2, "This is a test of uart 2", strlen(buffer));
	UART_write(uart3, "This is a test of uart 3", strlen(buffer));
	UART_write(uart4, "This is a test of uart 4", strlen(buffer));
	UART_write(uart7, "This is a test of uart 7", strlen(buffer));

	while(1)
	{
		ms_delay(100);

		dynamixelSetEndless(WRIST_DYNOA_ID);

		System_printf("Testing dynamixelSetEndless %d\n", WRIST_DYNOA_ID);
		System_flush();

		ms_delay(100);

	}//while

/*	while(recieve struct){

		switch(struct.id){

			case wrist_clock_wise:
				DynamixelSetSpeed(DynamixelUart, WRIST_DYNOA_ID, struct.speed);
				DynamixelSetSpeed(DynamixelUart, WRIST_DYNOB_ID, struct.speed);
				break;
			case wrist_up:
				DynamixelSetSpeed(DynamixelUart, WRIST_DYNOA_ID, struct.speed);
				DynamixelSetSpeed(DynamixelUart, WRIST_DYNOB_ID, -struct.speed);
				break;
			case elbow_clock_wise:
				break;
			case elbow_up:
				break;
			case actuator_forward:
				break;
			case base_clock_wise:
				break;
			case e_stop_arm:
				//call DynamixelReset on every dynamixel
				break;
			case gripper_open:
				//Passthrough to xbee. There should be an xbee.h library in roveIncludes
				break;
			//case whatever_drill_uses:
				//break;
			default

		}//end switch

	}//end while
*/

}//endfnct task robot arm main
