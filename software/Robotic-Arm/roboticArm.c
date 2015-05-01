/// roboticArm.c 2015

//TASK:

#include "roveIncludes/roveWareHeaders/roboticArm.h"

// BIOS_start in main inits this as the roboticArmTask Thread

// this is a roboticArm.cfg object::roboticArmTask::priority 1,  768 persistent private stack, vital_flag = t,

//#define MIN_SPEED -1000
//#define MAX_SPEED 1000
//#define SPEED_INCREMENT 100

void roboticArm(UArg arg0, UArg arg1)
{

	System_printf("Enter roboticArm TASK\n");
	System_flush();

	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
	extern UART_Handle uart7;

	//global static buffer alloc
	message_struct buffer_struct;
	char command_buffer[MAX_DYNAMIXEL_MSG_SIZE + 4];

	int16_t speed = 0;
	int16_t lin_act_current_position = 0;

	//init periphs
	System_printf("Initializing Periphs: \n");
	System_flush();
	dynamixelSetSpeedLeftCmd(WRIST_A_ID, 0, (void*)&buffer_struct, command_buffer);
	dynamixelSetSpeedRightCmd(WRIST_B_ID, 0, (void*)&buffer_struct, command_buffer);
	dynamixelSetSpeedLeftCmd(ELBOW_A_ID, 0, (void*)&buffer_struct, command_buffer);
	dynamixelSetSpeedRightCmd(ELBOW_B_ID, 0, (void*)&buffer_struct, command_buffer);
	dynamixelSetSpeedLeftCmd(BASE_ID, 0, (void*)&buffer_struct, command_buffer);
	lin_act_current_position = setLinActuatorCmd(LIN_ACT_ID, lin_act_current_position, 0, (void*)&buffer_struct, command_buffer);
	System_printf("Forever: \n");
	System_flush();

	//hack for unreachable statement warnings
	const uint8_t FOREVER = 1;
	while(FOREVER)
	{

		while( recvSerialStructMessage(MOTHERBOARD_UART, (void*)&buffer_struct, command_buffer) )
		{
			System_printf("recvSerialStructMessage struct_id:	 %d, 	speed:	 %d\n"
			, ((struct speed_struct*)(&buffer_struct))->struct_id
			, ((struct speed_struct*)(&buffer_struct))->speed);
			System_flush();

			speed = ((struct speed_struct*)(&buffer_struct))->speed;

			switch(buffer_struct.struct_id)
			{
				case wrist_clock_wise...base_clock_wise:

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
						roboArmReverseCmd(buffer_struct.struct_id, (-speed), (void*)&buffer_struct, command_buffer);

					}else{

						roboArmForwardCmd(buffer_struct.struct_id, speed, (void*)&buffer_struct, command_buffer);

					}//endif

				break;

				case e_stop_arm:

					dynamixelSetSpeedLeftCmd(WRIST_A_ID, 0, (void*)&buffer_struct, command_buffer);
					dynamixelSetSpeedLeftCmd(WRIST_B_ID, 0, (void*)&buffer_struct, command_buffer);
					dynamixelSetSpeedLeftCmd(ELBOW_A_ID, 0, (void*)&buffer_struct, command_buffer);
					dynamixelSetSpeedRightCmd(ELBOW_B_ID, 0, (void*)&buffer_struct, command_buffer);
					dynamixelSetSpeedLeftCmd(BASE_ID, 0, (void*)&buffer_struct, command_buffer);
					lin_act_current_position = setLinActuatorCmd(LIN_ACT_ID, lin_act_current_position, 0, (void*)&buffer_struct, command_buffer);

				//TODO Gripper and Drill e_stop_arm case actions

				break;

				case actuator_increment:

					lin_act_current_position = setLinActuatorCmd(LIN_ACT_ID, lin_act_current_position, speed, (void*)&buffer_struct, command_buffer);

					System_printf("Actuator increment:  %d 	 lin_act_current_position: 		%d = setLinActuatorCmd();\n", lin_act_current_position, speed);
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
void roboArmForwardCmd(uint8_t struct_id, int16_t speed, void* buffer_struct, char* command_buffer)
{
	switch(struct_id)
	{
		case wrist_clock_wise:

			System_printf("Testing wrist_clock_wise speed %d\n");
			System_flush();

			dynamixelSetSpeedRightCmd(WRIST_A_ID, speed, (void*)&buffer_struct, command_buffer);
			dynamixelSetSpeedLeftCmd(WRIST_B_ID, speed, (void*)&buffer_struct, command_buffer);

		break;

		case wrist_up:

			System_printf("Testing wrist_up speed %d\n", speed);
			System_flush();

			dynamixelSetSpeedRightCmd(WRIST_A_ID, speed, (void*)&buffer_struct, command_buffer);
			dynamixelSetSpeedRightCmd(WRIST_B_ID, speed, (void*)&buffer_struct, command_buffer);

		break;

		case elbow_clock_wise:

			System_printf("Testing elbow_clock_wise speed %d\n", speed);
			System_flush();

			dynamixelSetSpeedRightCmd(ELBOW_A_ID, speed, (void*)&buffer_struct, command_buffer);
			dynamixelSetSpeedLeftCmd(ELBOW_B_ID, speed, (void*)&buffer_struct, command_buffer);

		break;

		case elbow_up:

			System_printf("Testing elbow_up speed %d\n", speed);
			System_flush();

			dynamixelSetSpeedRightCmd(ELBOW_A_ID, speed, (void*)&buffer_struct, command_buffer);
			dynamixelSetSpeedRightCmd(ELBOW_B_ID, speed, (void*)&buffer_struct, command_buffer);

		break;

		case base_clock_wise:

				System_printf("Testing base_clock_wise speed %d\n", speed);
				System_flush();

				dynamixelSetSpeedRightCmd(BASE_ID, speed, (void*)&buffer_struct, command_buffer);

		break;

		case e_stop_arm:

			System_printf("!!!!!!!Called E stop from roboArmForwardCmd() speed: %d\n", speed);
			System_flush();
//TODO
		default:
			System_printf("\nERROR in RoboticArm.c!   roboArmForwardCmd struct_id %d cannot be handled \n", struct_id);
			System_flush();
		break;

	}//endswitch struct_id

}//endfnctn roboArmForwardCmd

//left is reverse
void roboArmReverseCmd(uint8_t struct_id, int16_t speed, void* buffer_struct, char* command_buffer)
{
	switch(struct_id)
	{
		//reverse (left) clockwise is counterclockwise
		case wrist_clock_wise:

			System_printf("Testing wrist_counter_clock_wise speed %d\n", speed);
			System_flush();

			dynamixelSetSpeedLeftCmd(WRIST_A_ID, speed, (void*)&buffer_struct, command_buffer);
			dynamixelSetSpeedRightCmd(WRIST_B_ID, speed, (void*)&buffer_struct, command_buffer);

		break;

		case wrist_up:

			//reverse (left) up is down
			System_printf("Testing wrist_down_speed %d\n", speed);
			System_flush();

			dynamixelSetSpeedLeftCmd(WRIST_A_ID, speed, (void*)&buffer_struct, command_buffer);
			dynamixelSetSpeedLeftCmd(WRIST_B_ID, speed, (void*)&buffer_struct, command_buffer);
		break;

		//reverse (left) clockwise is counterclockwise
		case elbow_clock_wise:

			System_printf("Testing elbow_counter_clock_wise speed %d\n", speed);
			System_flush();

			dynamixelSetSpeedLeftCmd(ELBOW_A_ID, speed, (void*)&buffer_struct, command_buffer);
			dynamixelSetSpeedRightCmd(ELBOW_B_ID, speed, (void*)&buffer_struct, command_buffer);
		break;

		//reverse (left) up is down
		case elbow_up:

			System_printf("Testing elbow_down speed %d\n", speed);
			System_flush();

			dynamixelSetSpeedLeftCmd(ELBOW_A_ID, speed, (void*)&buffer_struct, command_buffer);
			dynamixelSetSpeedLeftCmd(ELBOW_B_ID, speed, (void*)&buffer_struct, command_buffer);

		break;

		//reverse (left) clockwise is counterclockwise
		case base_clock_wise:

			System_printf("Testing base_counter_clock_wise speed %d\n", speed);
			System_flush();

			dynamixelSetSpeedLeftCmd(BASE_ID, speed, (void*)&buffer_struct, command_buffer);

		break;

		default:
			System_printf("\nERROR in RoboticArm.c!  roboArmReverseCmd  struct_id %d cannot be handled \n", struct_id);
			System_flush();
		break;

	}//endswitch struct_id

}//endfnctn roboArmReverseCmd

