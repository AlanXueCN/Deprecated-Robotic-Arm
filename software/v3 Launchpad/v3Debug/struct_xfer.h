/*
 * struct_xfer.h
 *
 *  Created on: May 6, 2014
 *      Author: Keenan Johnson
 */

#ifndef STRUCT_XFER_H_
#define STRUCT_XFER_H_

#include <stdbool.h>
//#include "structs.h"
#include <stdint.h>
#include "C:\StellarisWare\utils\uartstdio.h"
#include "C:\StellarisWare\driverlib\UART.h"


struct RECEIVE_DATA_STRUCTURE
{
	  uint8_t reset;
	  uint8_t wristUp;
	  uint8_t wristDown;
	  uint8_t wristClockWise;
	  uint8_t wristCounterClockWise;
	  uint8_t elbowUp;
	  uint8_t elbowDown;
	  uint8_t elbowClockWise;
	  uint8_t elbowCounterClockWise;
	  uint8_t actuatorForward;
	  uint8_t actuatorReverse;
	  uint8_t baseClockWise;
	  uint8_t baseCounterClockWise;
};


bool recv_struct( uint32_t uart, void* my_struct);

/////////////unused///////////////
//enum peripheral_devices{motor_controller, bms, robotic_arm, tcp_cmd, drill, gripper, science_payload, gps, lighting_board, camera, power_board};

//void send_struct(uint32_t uart, void* my_struct, enum peripheral_devices device);

#endif /* STRUCT_XFER_H_ */
