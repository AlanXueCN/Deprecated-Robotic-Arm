/// roboticArm.c

//OWENS FRAMEWORK:

#include "roveIncludes/roveWareHeaders/roboticArm.h"

// BIOS_start in main inits this as the roveTcpHandlerTask Thread

// this is a RoverMotherboard.cfg object::roveTcpHandlerTask::		priority 2, vital_flag = t, 2048 persistent private stack


void roboticArm(UArg arg0, UArg arg1){

	System_printf("Enter roboticArmMain\n");
	System_flush();

	char buffer[] = "This is a test of uart 0";

//	extern UART_Handle uart0;
//	extern UART_Handle uart1;
	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
//	extern UART_Handle uart5;
//	extern UART_Handle uart6;
//	extern UART_Handle uart7;


	while(1)
	{
		System_printf("Testing uarts\n");
		System_flush();
//		UART_write(uart0, "This is a test of uart 0", strlen(buffer));
//		UART_write(uart1, "This is a test of uart 1", strlen(buffer));
		UART_write(uart2, "This is a test of uart 2", strlen(buffer));
		UART_write(uart3, "This is a test of uart 3", strlen(buffer));
		UART_write(uart4, "This is a test of uart 4", strlen(buffer));
//		UART_write(uart5, "This is a test of uart 5", strlen(buffer));
//		UART_write(uart6, "This is a test of uart 6", strlen(buffer));
//		UART_write(uart7, "This is a test of uart 7", strlen(buffer));
		SysCtlDelay(500);
	}

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
