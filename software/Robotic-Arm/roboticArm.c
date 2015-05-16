/// roboticArm.c 2015

//TASK:

#include "roveIncludes/roveWareHeaders/roboticArm.h"

// BIOS_start in main inits this as the roboticArmTask Thread

//this is a roboticArm.cfg object::roboticArmTask::priority 1,
//768 persistent private stack, vital_flag = t,

//roveWare.h :: #define SPEED_STRUCT ((speed_struct*)(&buffer_struct))

Void roboticArm(UArg arg0, UArg arg1)
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

	digitalWrite(SET_TRI_ST_BUF_Tx, HIGH);

	//init all motors to zero
	dynamixelSetEndlessCmd(WRIST_A_ID);
	dynamixelSetEndlessCmd(WRIST_B_ID);
	dynamixelSetEndlessCmd(ELBOW_A_ID);
	dynamixelSetEndlessCmd(ELBOW_B_ID);
	dynamixelSetEndlessCmd(BASE_ID);
	dynamixelSetEndlessCmd(GRIPPER_ID);

	dynamixelSetSpeedLeftCmd(WRIST_A_ID, ZERO_SPEED);
	dynamixelSetSpeedLeftCmd(WRIST_B_ID, ZERO_SPEED);
	dynamixelSetSpeedLeftCmd(ELBOW_A_ID, ZERO_SPEED);
	dynamixelSetSpeedLeftCmd(ELBOW_B_ID, ZERO_SPEED);
	dynamixelSetSpeedLeftCmd(BASE_ID, ZERO_SPEED);
	dynamixelSetSpeedLeftCmd(GRIPPER_ID, ZERO_SPEED);

	//lin_act_cur_posit = setLinActuatorCmd(LIN_ACT_ID, lin_act_cur_posit, LIN_ACT_POSITION_ZERO);
	setLinActuatorCmd(LIN_ACT_ID, 0);

	//_printf("Loop Forever: \n");
	//_flush();

	//hack for unreachable statement warnings
	//const uint8_t FOREVER = 1;
	while(FOREVER)
	{

		while( recvSerialStructMessage(MOTHERBOARD_UART, (void*)&buffer_struct ))
		{
			//_printf("recvSerialStructMessage struct_id: %d", buffer_struct.struct_id);
			//_printf("speed: %d\n", SPEED_STRUCT->speed);
			//_flush();

			speed = SPEED_STRUCT->speed;

			//System_printf("Just Recieved struct_id %d, speed %d" buffer_struct.struct_id, SPEED_STRUCT->speed);
			//System_flush;

			switch(buffer_struct.struct_id)
			{
				case wrist_clock_wise...elbow_up:

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

				case base_clock_wise:

                    //Scale and Cap speed from roveWare.h
                    speed = (speed/BASE_SPEED_STEP_DOWN);

                    if(speed < BASE_SPEED_MIN)
                    {
                        speed = BASE_SPEED_MIN;
                    }//end if

                    if(speed > BASE_SPEED_MAX)
                    {
                        speed = BASE_SPEED_MAX;
                    }//end if

                    if(speed < 0)
                    {
                        roboArmReverseCmd(buffer_struct.struct_id, (-speed));

                    }else{

                        roboArmForwardCmd(buffer_struct.struct_id, speed);

                    }//endif

                    break;

				case e_stop_arm:

				    //System_printf("RobotArm.c case e_stop_arm speed: %d\n", SPEED_STRUCT->speed);
				    //System_flush();

					//dynamixelSetSpeedLeftCmd(WRIST_A_ID, 0);
					//dynamixelSetSpeedLeftCmd(WRIST_B_ID, 0);
					//dynamixelSetSpeedLeftCmd(ELBOW_A_ID, 0);
					//dynamixelSetSpeedLeftCmd(ELBOW_B_ID, 0);
					//dynamixelSetSpeedLeftCmd(BASE_ID, 0);
					//lin_act_cur_posit = setLinActuatorCmd(LIN_ACT_ID, lin_act_cur_posit, 0);
				    dynamixelSetSpeedRightCmd(WRIST_A_ID, 0);
                    dynamixelSetSpeedRightCmd(WRIST_B_ID, 0);
                    dynamixelSetSpeedRightCmd(ELBOW_A_ID, 0);
                    dynamixelSetSpeedRightCmd(ELBOW_B_ID, 0);
                    dynamixelSetSpeedRightCmd(BASE_ID, 0);
                    //lin_act_cur_posit = setLinActuatorCmd(LIN_ACT_ID, lin_act_cur_posit, 0);
                    setLinActuatorCmd(LIN_ACT_ID, 0);

				break;

				case actuator_increment:

				    setLinActuatorCmd(LIN_ACT_ID, speed);

					////_printf("Actuator increment:  %d 	 lin_act_current_position: 		%d = setLinActuatorCmd();\n", lin_act_cur_posit, speed);
					////_flush();

				break;

				case gripper_open:

                    if(speed < 0)
                    {
                        roboArmReverseCmd(buffer_struct.struct_id, (-speed));

                    }else{

                        roboArmForwardCmd(buffer_struct.struct_id, speed);

                    }//endif

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
void roboArmForwardCmd(uint8_t struct_id, int16_t speed)
{

    //System_printf("roboArmForwardCmd Thinks struct_id %d, speed %d" struct_id, speed);
    //System_flush;
	switch(struct_id)
	{
		case wrist_clock_wise:

			////_printf("Testing wrist_clock_wise speed %d\n");
			////_flush();

			dynamixelSetSpeedRightCmd(WRIST_A_ID, speed);
			//dynamixelSetSpeedLeftCmd(WRIST_B_ID, speed);
			dynamixelSetSpeedRightCmd(WRIST_B_ID, speed);

		break;

		case wrist_up:

			////_printf("Testing wrist_up speed %d\n", speed);
			////_flush();

			dynamixelSetSpeedRightCmd(WRIST_A_ID, speed);
			//dynamixelSetSpeedRightCmd(WRIST_B_ID, speed);
			dynamixelSetSpeedLeftCmd(WRIST_B_ID, speed);

		break;

		case elbow_clock_wise:

			//_printf("Testing elbow_clock_wise speed %d\n", speed);
			//_flush();

			    //dynamixelSetSpeedRightCmd(ELBOW_A_ID, speed);
			//dynamixelSetSpeedLeftCmd(ELBOW_B_ID, speed);
			    //dynamixelSetSpeedRightCmd(ELBOW_B_ID, speed);

			dynamixelSetSpeedLeftCmd(ELBOW_A_ID, speed);
			dynamixelSetSpeedLeftCmd(ELBOW_B_ID, speed);

		break;

		case elbow_up:

			//_printf("Testing elbow_up speed %d\n", speed);
			//_flush();

			    //dynamixelSetSpeedRightCmd(ELBOW_A_ID, speed);
			//dynamixelSetSpeedRightCmd(ELBOW_B_ID, speed);
			    //dynamixelSetSpeedLeftCmd(ELBOW_B_ID, speed);

			dynamixelSetSpeedLeftCmd(ELBOW_A_ID, speed);
			dynamixelSetSpeedRightCmd(ELBOW_B_ID, speed);

		break;

		case base_clock_wise:

				//_printf("Testing base_clock_wise speed %d\n", speed);
				//_flush();

				dynamixelSetSpeedRightCmd(BASE_ID, speed);

		break;

		case gripper_open:

		    dynamixelSetSpeedRightCmd(GRIPPER_ID, speed);

		break;

		default:
			//_printf("\nERROR in RoboticArm.c!   roboArmForwardCmd struct_id %d cannot be handled \n", struct_id);
			//_flush();
		break;

	}//endswitch struct_id

}//endfnctn roboArmForwardCmd

//left is reverse
void roboArmReverseCmd(uint8_t struct_id, int16_t speed)
{
    //System_printf("roboArmReverseCmd Thinks struct_id %d, speed %d" struct_id, speed);
    //System_flush;
	switch(struct_id)
	{
		//reverse (left) clockwise is counterclockwise
		case wrist_clock_wise:

			//_printf("Testing wrist_counter_clock_wise speed %d\n", speed);
			//_flush();

			dynamixelSetSpeedLeftCmd(WRIST_A_ID, speed);
			//dynamixelSetSpeedRightCmd(WRIST_B_ID, speed);
			dynamixelSetSpeedLeftCmd(WRIST_B_ID, speed);

		break;

		case wrist_up:

			//reverse (left) up is down
			//_printf("Testing wrist_down_speed %d\n", speed);
			//_flush();

			dynamixelSetSpeedLeftCmd(WRIST_A_ID, speed);
			//dynamixelSetSpeedLeftCmd(WRIST_B_ID, speed);
			dynamixelSetSpeedRightCmd(WRIST_B_ID, speed);

		break;

		//reverse (left) clockwise is counterclockwise
		case elbow_clock_wise:

			//_printf("Testing elbow_counter_clock_wise speed %d\n", speed);
			//_flush();

			    //dynamixelSetSpeedLeftCmd(ELBOW_A_ID, speed);
			//dynamixelSetSpeedRightCmd(ELBOW_B_ID, speed);
			    //dynamixelSetSpeedLeftCmd(ELBOW_B_ID, speed);

			dynamixelSetSpeedRightCmd(ELBOW_A_ID, speed);
			dynamixelSetSpeedRightCmd(ELBOW_B_ID, speed);

		break;

		//reverse (left) up is down
		case elbow_up:

			//_printf("Testing elbow_down speed %d\n", speed);
			//_flush();

			    //dynamixelSetSpeedLeftCmd(ELBOW_A_ID, speed);
			//dynamixelSetSpeedLeftCmd(ELBOW_B_ID, speed);
			    //dynamixelSetSpeedRightCmd(ELBOW_B_ID, speed);

			dynamixelSetSpeedRightCmd(ELBOW_A_ID, speed);
			dynamixelSetSpeedLeftCmd(ELBOW_B_ID, speed);

		break;

		//reverse (left) clockwise is counterclockwise
		case base_clock_wise:

			//_printf("Testing base_counter_clock_wise speed %d\n", speed);
			//_flush();

			dynamixelSetSpeedLeftCmd(BASE_ID, speed);

		break;

        case gripper_open:

            dynamixelSetSpeedLeftCmd(GRIPPER_ID, speed);

        break;

		default:
			//_printf("\nERROR in RoboticArm.c!  roboArmReverseCmd  struct_id %d cannot be handled \n", struct_id);
			//_flush();
		break;

	}//endswitch struct_id

}//endfnctn roboArmReverseCmd
