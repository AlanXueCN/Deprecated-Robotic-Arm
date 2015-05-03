/// roboticArm.c 2015

//TASK:

#include "roveIncludes/roveWareHeaders/roboticArm.h"

// BIOS_start in main inits this as the roboticArmTask Thread

//this is a roboticArm.cfg object::roboticArmTask::priority 1,
//768 persistent private stack, vital_flag = t,

//roveWare.h :: #define SPEED_STRUCT ((speed_struct*)(&buffer_struct))

void roboticArm(UArg arg0, UArg arg1)
{
	//_printf("roboticArmTask init \n\n\n");
	//_flush();

	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
	extern UART_Handle uart7;

	//task scope buffer alloc
	message_struct buffer_struct;

	//alloc task variable to continously track the linear actuators position for cmd ref
	int16_t lin_act_cur_posit = 0;

	//not tracked, alloc reuseable task variable
	int16_t speed = 0;

	//init periphs
	//_printf("Initializing Periphs: \n");
	//_flush();

	//init all motors to zero
	dynamixelSetEndlessCmd(WRIST_A_ID, (void*)&buffer_struct);
	dynamixelSetEndlessCmd(WRIST_B_ID, (void*)&buffer_struct);
	dynamixelSetEndlessCmd(ELBOW_A_ID, (void*)&buffer_struct);
	dynamixelSetEndlessCmd(ELBOW_B_ID, (void*)&buffer_struct);
	dynamixelSetEndlessCmd(BASE_ID, (void*)&buffer_struct);

	dynamixelSetSpeedLeftCmd(WRIST_A_ID, ZERO_SPEED, (void*)&buffer_struct);
	dynamixelSetSpeedLeftCmd(WRIST_B_ID, ZERO_SPEED, (void*)&buffer_struct);
	dynamixelSetSpeedLeftCmd(ELBOW_A_ID, ZERO_SPEED, (void*)&buffer_struct);
	dynamixelSetSpeedRightCmd(ELBOW_B_ID, ZERO_SPEED, (void*)&buffer_struct);
	dynamixelSetSpeedLeftCmd(BASE_ID, ZERO_SPEED, (void*)&buffer_struct);

	lin_act_cur_posit = setLinActuatorCmd(LIN_ACT_ID, lin_act_cur_posit, LIN_ACT_POSITION_ZERO, (void*)&buffer_struct);

	//_printf("Loop Forever: \n");
	//_flush();

	//hack for unreachable statement warnings
	//const uint8_t FOREVER = 1;
	while(FOREVER)
	{

		while( recvSerialStructMessage(MOTHERBOARD_UART, (void*)&buffer_struct) )
		{
			//_printf("recvSerialStructMessage struct_id: %d", buffer_struct.struct_id);
			//_printf("speed: %d\n", SPEED_STRUCT->speed);
			//_flush();

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
						roboArmReverseCmd(buffer_struct.struct_id, (-speed), (void*)&buffer_struct);

					}else{

						roboArmForwardCmd(buffer_struct.struct_id, speed, (void*)&buffer_struct);

					}//endif

				break;

				case e_stop_arm:

					dynamixelSetSpeedLeftCmd(WRIST_A_ID, 0, (void*)&buffer_struct);
					dynamixelSetSpeedLeftCmd(WRIST_B_ID, 0, (void*)&buffer_struct);
					dynamixelSetSpeedLeftCmd(ELBOW_A_ID, 0, (void*)&buffer_struct);
					dynamixelSetSpeedRightCmd(ELBOW_B_ID, 0, (void*)&buffer_struct);
					dynamixelSetSpeedLeftCmd(BASE_ID, 0, (void*)&buffer_struct);
					lin_act_cur_posit = setLinActuatorCmd(LIN_ACT_ID, lin_act_cur_posit, 0, (void*)&buffer_struct);

				//TODO Gripper and Drill e_stop_arm case actions

				break;

				case actuator_increment:

					lin_act_cur_posit = setLinActuatorCmd(LIN_ACT_ID, lin_act_cur_posit, speed, (void*)&buffer_struct);

					////_printf("Actuator increment:  %d 	 lin_act_current_position: 		%d = setLinActuatorCmd();\n", lin_act_cur_posit, speed);
					////_flush();

				break;

				case gripper_open:

					//TODO Gripper

					//_printf("What? Not ready for gripper_open");
					//_flush();

				break;

				case drill:

					//TODO Drill

					//_printf("What? Not ready for drill");
					//_flush();

				break;

				default:
					//_printf("\nERROR in RoboticArm.c! struct_id %d cannot be handled \n", buffer_struct.struct_id);
					//_flush();
				break;

			}//endswitch buffer_struct.struct_id

		}//endwhile recvSerialStructMessage

	}//endwhile FOREVER

}//endfnct task robot arm main

//right is forward
void roboArmForwardCmd(uint8_t struct_id, int16_t speed, void* buffer_struct)
{
	switch(struct_id)
	{
		case wrist_clock_wise:

			////_printf("Testing wrist_clock_wise speed %d\n");
			////_flush();

			dynamixelSetSpeedRightCmd(WRIST_A_ID, speed, (void*)&buffer_struct);
			dynamixelSetSpeedLeftCmd(WRIST_B_ID, speed, (void*)&buffer_struct);

		break;

		case wrist_up:

			////_printf("Testing wrist_up speed %d\n", speed);
			////_flush();

			dynamixelSetSpeedRightCmd(WRIST_A_ID, speed, (void*)&buffer_struct);
			dynamixelSetSpeedRightCmd(WRIST_B_ID, speed, (void*)&buffer_struct);

		break;

		case elbow_clock_wise:

			//_printf("Testing elbow_clock_wise speed %d\n", speed);
			//_flush();

			dynamixelSetSpeedRightCmd(ELBOW_A_ID, speed, (void*)&buffer_struct);
			dynamixelSetSpeedLeftCmd(ELBOW_B_ID, speed, (void*)&buffer_struct);

		break;

		case elbow_up:

			//_printf("Testing elbow_up speed %d\n", speed);
			//_flush();

			dynamixelSetSpeedRightCmd(ELBOW_A_ID, speed, (void*)&buffer_struct);
			dynamixelSetSpeedRightCmd(ELBOW_B_ID, speed, (void*)&buffer_struct);

		break;

		case base_clock_wise:

				//_printf("Testing base_clock_wise speed %d\n", speed);
				//_flush();

				dynamixelSetSpeedRightCmd(BASE_ID, speed, (void*)&buffer_struct);

		break;

		case e_stop_arm:

			//_printf("!!!!!!!Called E stop from roboArmForwardCmd() speed: %d\n", speed);
			//_flush();
//TODO
		default:
			//_printf("\nERROR in RoboticArm.c!   roboArmForwardCmd struct_id %d cannot be handled \n", struct_id);
			//_flush();
		break;

	}//endswitch struct_id

}//endfnctn roboArmForwardCmd

//left is reverse
void roboArmReverseCmd(uint8_t struct_id, int16_t speed, void* buffer_struct)
{
	switch(struct_id)
	{
		//reverse (left) clockwise is counterclockwise
		case wrist_clock_wise:

			//_printf("Testing wrist_counter_clock_wise speed %d\n", speed);
			//_flush();

			dynamixelSetSpeedLeftCmd(WRIST_A_ID, speed, (void*)&buffer_struct);
			dynamixelSetSpeedRightCmd(WRIST_B_ID, speed, (void*)&buffer_struct);

		break;

		case wrist_up:

			//reverse (left) up is down
			//_printf("Testing wrist_down_speed %d\n", speed);
			//_flush();

			dynamixelSetSpeedLeftCmd(WRIST_A_ID, speed, (void*)&buffer_struct);
			dynamixelSetSpeedLeftCmd(WRIST_B_ID, speed, (void*)&buffer_struct);
		break;

		//reverse (left) clockwise is counterclockwise
		case elbow_clock_wise:

			//_printf("Testing elbow_counter_clock_wise speed %d\n", speed);
			//_flush();

			dynamixelSetSpeedLeftCmd(ELBOW_A_ID, speed, (void*)&buffer_struct);
			dynamixelSetSpeedRightCmd(ELBOW_B_ID, speed, (void*)&buffer_struct);
		break;

		//reverse (left) up is down
		case elbow_up:

			//_printf("Testing elbow_down speed %d\n", speed);
			//_flush();

			dynamixelSetSpeedLeftCmd(ELBOW_A_ID, speed, (void*)&buffer_struct);
			dynamixelSetSpeedLeftCmd(ELBOW_B_ID, speed, (void*)&buffer_struct);

		break;

		//reverse (left) clockwise is counterclockwise
		case base_clock_wise:

			//_printf("Testing base_counter_clock_wise speed %d\n", speed);
			//_flush();

			dynamixelSetSpeedLeftCmd(BASE_ID, speed, (void*)&buffer_struct);

		break;

		default:
			//_printf("\nERROR in RoboticArm.c!  roboArmReverseCmd  struct_id %d cannot be handled \n", struct_id);
			//_flush();
		break;

	}//endswitch struct_id

}//endfnctn roboArmReverseCmd
