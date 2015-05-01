/// roboticArm.c 2015

//TASK:

#include "roveIncludes/roveWareHeaders/roboticArm.h"

// BIOS_start in main inits this as the roboticArmTask Thread

// this is a roboticArm.cfg object::roboticArmTask::priority 1,  768 persistent private stack, vital_flag = t,

void roboticArm(UArg arg0, UArg arg1)
{

	System_printf("Enter roboticArm TASK\n");
	System_flush();

	//extern message_struct buffer_struct;
	message_struct buffer_struct;

	//extern const uint8_t FOREVER;
	const uint8_t FOREVER = 1;

	int16_t speed;
	int16_t current_position;

	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
	extern UART_Handle uart7;

	while(FOREVER){

		while( recvSerialStructMessage(MOTHERBOARD_UART, (char*)&buffer_struct) )
		{
			System_printf("BEFORE ANYTHING struct_id %d, speed %d\n"
						, ((struct speed_struct*)(&buffer_struct))->struct_id
						, ((struct speed_struct*)(&buffer_struct))->speed);
			System_flush();

			speed = ((struct speed_struct*)(&buffer_struct))->speed;

			speed = (speed/SPEED_STEP_DOWN);

			if(speed < SPEED_MIN)
			{
				speed = SPEED_MIN;
			}//end if

			if(speed > SPEED_MAX)
			{
				speed = SPEED_MAX;
			}//end if

			switch(buffer_struct.struct_id)
			{
				case wrist_clock_wise...base_clock_wise:

					if(speed < 0)
					{
						roboArmReverseCmd(buffer_struct.struct_id, (-speed), (char*)&buffer_struct);

					}else{

						roboArmForwardCmd(buffer_struct.struct_id, speed, (char*)&buffer_struct);

					}//endif

				break;

				case e_stop_arm:

					dynamixelSetSpeedLeftCmd(WRIST_A_ID, 0);
					dynamixelSetSpeedLeftCmd(WRIST_B_ID, 0);
					dynamixelSetSpeedLeftCmd(ELBOW_A_ID, 0);
					dynamixelSetSpeedRightCmd(ELBOW_B_ID, 0);
					dynamixelSetSpeedLeftCmd(BASE_ID, 0);
					current_position = setLinActuatorCmd(LIN_ACT_ID, current_position, 0);

				//TODO Gripper and Drill e_stop_arm case actions

				case actuator_increment:

					System_printf("BEFORE actuator_increment current %d, inc %d\n", current_position, speed);
					System_flush();

					current_position = setLinActuatorCmd(LIN_ACT_ID, current_position, speed);

					System_printf("AFTER actuator_increment current %d, inc %d\n", current_position, speed);
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

		}//endwhile recvSerialStructMessage

	}//endwhile FOREVER

}//endfnct task robot arm main

//right is forward
void roboArmForwardCmd(uint8_t struct_id, int16_t speed, char* buffer_struct)
{
	switch(struct_id)
	{
		case wrist_clock_wise:

			System_printf("Testing wrist_clock_wise speed %d\n", speed);
			System_flush();

			dynamixelSetSpeedRightCmd(WRIST_A_ID, speed);
			dynamixelSetSpeedLeftCmd(WRIST_B_ID, speed);

		break;

		case wrist_up:

			System_printf("Testing wrist_up speed %d\n", speed);
			System_flush();

			dynamixelSetSpeedRightCmd(WRIST_A_ID, speed);
			dynamixelSetSpeedRightCmd(WRIST_B_ID, speed);

		break;

		case elbow_clock_wise:

			System_printf("Testing elbow_clock_wise speed %d\n", speed);
			System_flush();

			dynamixelSetSpeedRightCmd(ELBOW_A_ID, speed);
			dynamixelSetSpeedLeftCmd(ELBOW_B_ID, speed);

		break;

		case elbow_up:

			System_printf("Testing elbow_up speed %d\n", speed);
			System_flush();

			dynamixelSetSpeedRightCmd(ELBOW_A_ID, speed);
			dynamixelSetSpeedRightCmd(ELBOW_B_ID, speed);

		break;
//TODO
		case actuator_increment:

			System_printf("Tell Josh to change this with estop %d\n", speed);
			System_flush();

		break;

		case base_clock_wise:

			System_printf("Testing elbow_up speed %d\n", speed);
			System_flush();

			dynamixelSetSpeedRightCmd(BASE_ID, speed);

		break;

	}//endswitch struct_id

}//endfnctn roboArmForwardCmd

//left is reverse
void roboArmReverseCmd(uint8_t struct_id, int16_t speed, char* buffer_struct)
{
	switch(struct_id)
	{
		//reverse (left) clockwise is counterclockwise
		case wrist_clock_wise:

			System_printf("Testing wrist_counter_clock_wise speed %d\n", speed);
			System_flush();

			dynamixelSetSpeedLeftCmd(WRIST_A_ID, speed);
			dynamixelSetSpeedRightCmd(WRIST_B_ID, speed);

		break;

		case wrist_up:

			//reverse (left) up is down
			System_printf("Testing wrist_down_speed %d\n", speed);
			System_flush();

			dynamixelSetSpeedLeftCmd(WRIST_A_ID, speed);
			dynamixelSetSpeedLeftCmd(WRIST_B_ID, speed);
		break;

		//reverse (left) clockwise is counterclockwise
		case elbow_clock_wise:

			System_printf("Testing elbow_counter_clock_wise speed %d\n", speed);
			System_flush();

			dynamixelSetSpeedLeftCmd(ELBOW_A_ID, speed);
			dynamixelSetSpeedRightCmd(ELBOW_B_ID, speed);
		break;

		//reverse (left) up is down
		case elbow_up:

			System_printf("Testing elbow_down speed %d\n", speed);
			System_flush();

			dynamixelSetSpeedLeftCmd(ELBOW_A_ID, speed);
			dynamixelSetSpeedLeftCmd(ELBOW_B_ID, speed);

		break;

		//reverse (left) clockwise is counterclockwise
		case base_clock_wise:

			System_printf("Testing base_counter_clock_wise speed %d\n", speed);
			System_flush();

			dynamixelSetSpeedLeftCmd(BASE_ID, speed);

		break;

	}//endswitch struct_id

}//endfnctn roboArmReverseCmd

