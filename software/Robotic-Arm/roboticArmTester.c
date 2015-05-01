/// roboticArmTester.c 2015

//TASK:

#include "roveIncludes/roveWareHeaders/roboticArmTester.h"

// BIOS_start in main inits this as the roboticArmTask Thread

// this is a roboticArm.cfg object::roboticArmTask::priority 1,  768 persistent private stack, vital_flag = t,

void roboticArmTester(UArg arg0, UArg arg1)
{
/*
	System_printf("Enter roboticArmTester TASK\n");
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

	System_printf("Testing INIT setLinActuatorCmd %d\n", LIN_ACT_ID);
	System_flush();
	setLinActuatorCmd(LIN_ACT_ID, 0, 0);

	int command_loop_thru_count = 0;
	int test_speed = 100;
	int test_lin_act_increment = 200;
	uint16_t test_lin_act_cur_position = 0;

	while(1)
	{
		ms_delay(10);

		while(test_speed > 0)
			{

			System_printf("Testing dynamixelSetSpeed id %d, speed %d\n", WRIST_A_ID, test_speed);
			System_flush();
			dynamixelSetSpeedLeftCmd(WRIST_A_ID, test_speed);
			System_printf("Testing dynamixelSetSpeed id %d, speed %d\n", WRIST_B_ID, test_speed);
			System_flush();
			dynamixelSetSpeedLeftCmd(WRIST_B_ID, test_speed);
			System_printf("Testing dynamixelSetSpeed id %d, speed %d\n", ELBOW_A_ID, test_speed);
			System_flush();
			dynamixelSetSpeedLeftCmd(ELBOW_A_ID, test_speed);
			System_printf("Testing dynamixelSetSpeed id %d, speed %d\n", ELBOW_B_ID, test_speed);
			System_flush();
			dynamixelSetSpeedLeftCmd(ELBOW_B_ID, test_speed);
			System_printf("Testing dynamixelSetSpeed id %d, speed %d\n", BASE_ID, test_speed);
			System_flush();
			dynamixelSetSpeedLeftCmd(BASE_ID, test_speed);

			test_speed = (test_speed - 10);

			}//

			test_speed = 100;

			ms_delay(10);

			while(test_speed < 100)
			{

			System_printf("Testing dynamixelSetSpeed id %d, speed %d\n", WRIST_A_ID, test_speed);
			System_flush();
			dynamixelSetSpeedRightCmd(WRIST_A_ID, test_speed);
			System_printf("Testing dynamixelSetSpeed id %d, speed %d\n", WRIST_B_ID, test_speed);
			System_flush();
			dynamixelSetSpeedRightCmd(WRIST_B_ID, test_speed);
			System_printf("Testing dynamixelSetSpeed id %d, speed %d\n", ELBOW_A_ID, test_speed);
			System_flush();
			dynamixelSetSpeedRightCmd(ELBOW_A_ID, test_speed);
			System_printf("Testing dynamixelSetSpeed id %d, speed %d\n", ELBOW_B_ID, test_speed);
			System_flush();
			dynamixelSetSpeedRightCmd(ELBOW_B_ID, test_speed);
			System_printf("Testing dynamixelSetSpeed id %d, speed %d\n", BASE_ID, test_speed);
			System_flush();
			dynamixelSetSpeedRightCmd(BASE_ID, test_speed);

			test_speed = (test_speed + 10);

			}//

			System_printf("Testing setLinActuatorCmd id %d, test_lin_act_increment %d\n", LIN_ACT_ID, test_lin_act_increment);
			System_flush();
			test_lin_act_cur_position = setLinActuatorCmd(LIN_ACT_ID, test_lin_act_cur_position, test_lin_act_increment);


		System_printf("Success dynamixelSetSpeedCmd count %d\n", command_loop_thru_count);
		System_flush();

		command_loop_thru_count++;

		ms_delay(10);

	}//while


*/
}//endfnct task roboticArmTester
