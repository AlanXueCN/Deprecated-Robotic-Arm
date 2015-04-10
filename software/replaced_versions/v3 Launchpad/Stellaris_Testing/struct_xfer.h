/*
 * struct_xfer.h
 *
 *  Created on: May 6, 2014
 *      Author: Keenan Johnson
 */

#ifndef STRUCT_XFER_H_
#define STRUCT_XFER_H_

#include <stdbool.h>
//#include <xdc/runtime/System.h>
#include "structs.h"
#include <stdint.h>
#include "utils/uartstdio.h"
#include "driverlib/UART.h"

struct RECEIVE_DATA_STRUCTURE{
	  unsigned int reset;
	  unsigned int wristUp;
	  unsigned int wristDown;
	  unsigned int wristClockWise;
	  unsigned int wristCounterClockWise;
	  unsigned int elbowUp;
	  unsigned int elbowDown;
	  unsigned int elbowClockWise;
	  unsigned int elbowCounterClockWise;
	  unsigned int actuatorForward;
	  unsigned int actuatorReverse;
	  unsigned int baseClockWise;
	  unsigned int baseCounterClockWise;
	};



enum peripheral_devices{motor_controller, bms, robotic_arm, tcp_cmd, drill, gripper, science_payload, gps, lighting_board, camera, power_board};

void send_struct(uint32_t uart, void* my_struct, enum peripheral_devices device);

bool recv_struct( uint32_t uart, void* my_struct);

#endif /* STRUCT_XFER_H_ */
