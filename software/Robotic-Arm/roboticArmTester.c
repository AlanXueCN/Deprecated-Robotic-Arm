// roboticArmTester.c 2015

//TESTER TASK:

#include "roveIncludes/roveWareHeaders/roboticArm.h"

// BIOS_start in main inits this as the roboticArmTesterTask Thread

//this is a roboticArm.cfg object::roboticArmTask::priority 1,
//768 persistent private stack, vital_flag = t,

//roveWare.h :: #define TEST_STRUCT ((speed_struct*)(&buffer_struct))

void roboticArmTester(UArg arg0, UArg arg1)
{
	System_printf("roboticArmTesterTask init \n\n\n");
	System_flush();

	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
	extern UART_Handle uart7;

	//task scope buffer alloc
	message_struct buffer_struct;

	buffer_struct.struct_id = 201;
	int16_t speed = 0;

	//track the linear actuators position at the task level
	int16_t lin_act_cur_posit = 0;

	//init periphs
	System_printf("Initializing Periphs: \n");
	System_flush();

	//testing
	System_printf("roboticArm struct_id:	 %d\n", buffer_struct.struct_id);
	System_flush();

//COMMENT* HERE FOR RECIEVE TESTER

	//init all motors to zero
	dynamixelSetEndlessCmd(WRIST_A_ID);
	dynamixelSetEndlessCmd(WRIST_B_ID);
	dynamixelSetEndlessCmd(ELBOW_A_ID);
	dynamixelSetEndlessCmd(ELBOW_B_ID);
	dynamixelSetEndlessCmd(BASE_ID);

	dynamixelSetSpeedLeftCmd(WRIST_A_ID, ZERO_SPEED);
	dynamixelSetSpeedLeftCmd(WRIST_B_ID, ZERO_SPEED);
	dynamixelSetSpeedLeftCmd(ELBOW_A_ID, ZERO_SPEED);
	dynamixelSetSpeedRightCmd(ELBOW_B_ID, ZERO_SPEED);
	dynamixelSetSpeedLeftCmd(BASE_ID, 0);

	lin_act_cur_posit = setLinActuatorCmd(LIN_ACT_ID, lin_act_cur_posit, LIN_ACT_POSITION_ZERO);

	System_printf("Loop Forever: \n");
	System_flush();

	//hack for unreachable statement warnings
	//const uint8_t FOREVER = 1;
	while(FOREVER)
	{

//BEGIN TEST MOD

		TEST_STRUCT->struct_id = 	TEST_MIN_STRUCT_ID;
		TEST_STRUCT->speed = 		TEST_MIN_SPEED;

		while(TEST_STRUCT->struct_id <= TEST_MAX_STRUCT_ID)
		{
			TEST_STRUCT->struct_id = 	TEST_MIN_STRUCT_ID;
			TEST_STRUCT->speed = 		TEST_MIN_SPEED;

			while(TEST_STRUCT->speed <= TEST_MAX_SPEED)
			{
				TEST_STRUCT->struct_id = TEST_STRUCT->struct_id + TEST_STRUCT_INC;
				TEST_STRUCT->speed = TEST_STRUCT->speed + TEST_SPEED_INC;

				System_printf("Tester Posted struct_id %d, speed, %d\n", TEST_STRUCT->struct_id, TEST_STRUCT->speed);
				System_flush();

//END TEST MOD

				speed = SPEED_STRUCT->speed;

				switch(buffer_struct.struct_id)
				{
					case wrist_clock_wise...base_clock_wise:

						//Scale and Cap speed from roveWare.h
						speed = (speed/SPEED_STEP_DOWN);

						if(speed < SPEED_MIN)
						{
							speed = SPEED_MIN;
						}//end if

						if(speed > SPEED_MAX)
						{
							speed = SPEED_MAX;
						}//end if


						if(speed < 0)
						{
							roboArmReverseCmd(buffer_struct.struct_id, (-speed));

						}else{

							roboArmForwardCmd(buffer_struct.struct_id, speed);

						}//endif

					break;

					case e_stop_arm:

						dynamixelSetSpeedLeftCmd(WRIST_A_ID, 0);
						dynamixelSetSpeedLeftCmd(WRIST_B_ID, 0);
						dynamixelSetSpeedLeftCmd(ELBOW_A_ID, 0);
						dynamixelSetSpeedRightCmd(ELBOW_B_ID, 0);
						dynamixelSetSpeedLeftCmd(BASE_ID, 0);
						lin_act_cur_posit = setLinActuatorCmd(LIN_ACT_ID, lin_act_cur_posit, 0);

					//TODO Gripper and Drill e_stop_arm case actions

					break;

					case actuator_increment:

						lin_act_cur_posit = setLinActuatorCmd(LIN_ACT_ID, lin_act_cur_posit, speed);

						System_printf("Actuator increment:  %d 	 lin_act_current_position: 		%d = setLinActuatorCmd();\n", lin_act_cur_posit, speed);
						System_flush();

					break;

					case gripper_open:

						//TODO Gripper

						System_printf("What? Not ready for gripper_open");
						System_flush();

					break;

					case drill:

						//TODO Drill

						System_printf("What? Not ready for drill");
						System_flush();

					break;

					default:
						System_printf("\nERROR in RoboticArm.c! struct_id %d cannot be handled \n", buffer_struct.struct_id);
						System_flush();
					break;

				}//endswitch buffer_struct.struct_id

//BEGIN TEST MOD

				ms_delay(TEST_MS_DELAY);

			}//end while TEST_MAX_SPEED

			while(TEST_STRUCT->speed >= TEST_MIN_SPEED)
			{
				TEST_STRUCT->struct_id = TEST_STRUCT->struct_id - TEST_STRUCT_INC;
				TEST_STRUCT->speed = TEST_STRUCT->speed - TEST_SPEED_INC;

				System_printf("Tester Posted struct_id %d, speed, %d\n", TEST_STRUCT->struct_id, TEST_STRUCT->speed);
				System_flush();

//END TEST MOD

				speed = SPEED_STRUCT->speed;

				switch(buffer_struct.struct_id)
				{
					case wrist_clock_wise...base_clock_wise:

						//Scale and Cap speed from roveWare.h
						speed = (speed/SPEED_STEP_DOWN);

						if(speed < SPEED_MIN)
						{
							speed = SPEED_MIN;
						}//end if

						if(speed > SPEED_MAX)
						{
							speed = SPEED_MAX;
						}//end if


						if(speed < 0)
						{
							roboArmReverseCmd(buffer_struct.struct_id, (-speed));

						}else{

							roboArmForwardCmd(buffer_struct.struct_id, speed);

						}//endif

					break;

					case e_stop_arm:

						dynamixelSetSpeedLeftCmd(WRIST_A_ID, 0);
						dynamixelSetSpeedLeftCmd(WRIST_B_ID, 0);
						dynamixelSetSpeedLeftCmd(ELBOW_A_ID, 0);
						dynamixelSetSpeedRightCmd(ELBOW_B_ID, 0);
						dynamixelSetSpeedLeftCmd(BASE_ID, 0);
						lin_act_cur_posit = setLinActuatorCmd(LIN_ACT_ID, lin_act_cur_posit, 0);

					//TODO Gripper and Drill e_stop_arm case actions

					break;

					case actuator_increment:

						lin_act_cur_posit = setLinActuatorCmd(LIN_ACT_ID, lin_act_cur_posit, speed);

						System_printf("Actuator increment:  %d 	 lin_act_current_position: 		%d = setLinActuatorCmd();\n", lin_act_cur_posit, speed);
						System_flush();

					break;

					case gripper_open:

						//TODO Gripper

						System_printf("What? Not ready for gripper_open");
						System_flush();

					break;

					case drill:

						//TODO Drill

						System_printf("What? Not ready for drill");
						System_flush();

					break;

					default:
						System_printf("\nERROR in RoboticArm.c! struct_id %d cannot be handled \n", buffer_struct.struct_id);
						System_flush();
					break;

				}//endswitch buffer_struct.struct_id

//BEGIN TEST MOD

				ms_delay(TEST_MS_DELAY);

			}//end while TEST_MIN_SPEED

		}//endwhile STRUCT_ID_MAX

//END TEST MOD

//COMMENT* HERE FOR RECIEVE TESTER

/*

    while(FOREVER)
    {
        while( recvSerialStructMessage(MOTHERBOARD_UART, (void*)&buffer_struct) )
        {
            System_printf("recvSerialStructMessage struct_id: %d", buffer_struct.struct_id);
            System_printf("speed: %d\n", SPEED_STRUCT->speed);
            System_flush();
        }//endwhile

//COMMENT* HERE FOR RECIEVE TESTER

*/
	}//endwhile FOREVER

}//endfnct task roboticArmTester
