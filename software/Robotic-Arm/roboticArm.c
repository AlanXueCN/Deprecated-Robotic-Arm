/// roboticArm.c

//OWENS FRAMEWORK:

#include "roveIncludes/roveWareHeaders/roboticArm.h"

// BIOS_start in main inits this as the roveTcpHandlerTask Thread

// this is a RoverMotherboard.cfg object::roveTcpHandlerTask::		priority 2, vital_flag = t, 2048 persistent private stack


void roboticArm(UArg arg0, UArg arg1){

	System_printf("Enter roboticArmMain\n");
	System_flush();

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
