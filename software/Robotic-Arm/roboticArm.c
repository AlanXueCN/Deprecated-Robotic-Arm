/// roboticArm.c 2015

//TASK:

#include "roveIncludes/roveWareHeaders/roboticArm.h"

// BIOS_start in main inits this as the roboticArmTask Thread

// this is a roboticArm.cfg object::roboticArmTask::priority 1,  768 persistent private stack, vital_flag = t,

void roboticArm(UArg arg0, UArg arg1)
{

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

	System_printf("Testing dynamixelSetEndless %d\n", WRIST_A_ID);
	System_flush();
	dynamixelSetEndlessCmd(WRIST_A_ID);
	System_printf("Testing dynamixelSetEndless %d\n", WRIST_B_ID);
	System_flush();
	dynamixelSetEndlessCmd(WRIST_B_ID);
	System_printf("Testing dynamixelSetEndless %d\n", ELBOW_A_ID);
	System_flush();
	dynamixelSetEndlessCmd(ELBOW_A_ID);
	System_printf("Testing dynamixelSetEndless %d\n", ELBOW_B_ID);
	System_flush();
	dynamixelSetEndlessCmd(ELBOW_B_ID);
	System_printf("Testing dynamixelSetEndless %d\n", BASE_ID);
	System_flush();
	dynamixelSetEndlessCmd(BASE_ID);

	int command_loop_thru_count = 0;
	int test_speed = 1000;
	while(1)
	{
		ms_delay(1);

		//if(test_speed < 900)
		//{

			System_printf("Testing dynamixelSetSpeed id %d, speed %d\n", WRIST_A_ID, test_speed);
			System_flush();
			dynamixelSetSpeedCmd(WRIST_A_ID, test_speed);
			System_printf("Testing dynamixelSetSpeed id %d, speed %d\n", WRIST_B_ID, test_speed);
			System_flush();
			dynamixelSetSpeedCmd(WRIST_B_ID, test_speed);
			System_printf("Testing dynamixelSetSpeed id %d, speed %d\n", ELBOW_A_ID, test_speed);
			System_flush();
			dynamixelSetSpeedCmd(ELBOW_A_ID, test_speed);
			System_printf("Testing dynamixelSetSpeed id %d, speed %d\n", ELBOW_B_ID, test_speed);
			System_flush();
			dynamixelSetSpeedCmd(ELBOW_B_ID, test_speed);
			System_printf("Testing dynamixelSetSpeed id %d, speed %d\n", BASE_ID, test_speed);
			System_flush();
			dynamixelSetSpeedCmd(BASE_ID, test_speed);
		//}else{

		//	test_speed = 0;

		//}//endif

		//test_speed = test_speed + 115;

		System_printf("Success dynamixelSetSpeedCmd count %d\n", command_loop_thru_count);
		System_flush();

		command_loop_thru_count++;


		ms_delay(1);

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
