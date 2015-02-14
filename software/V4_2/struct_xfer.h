/*
 * struct_xfer.h
 *
 *  Created on: May 6, 2014
 *      Author: Keenan Johnson
 */

#ifndef STRUCT_XFER_H_
#define STRUCT_XFER_H_

#include <stdbool.h>
#include <stdint.h>
#include "utils\uartstdio.h"
#include "driverlib\UART.h"

#define GRIPPER 				0//definitions for the id of the struct to return. Would have
#define DRILL	 				1//used the enum, but it caused strange errors in recv_struct
#define ROBOTIC_ARM 			2


struct arm_data_struct
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

struct gripper_control_struct
{
	uint8_t grip_cmd;
};

struct drill_Controls
{
  //Drill Ctrl
  uint8_t goalSpeed;
  uint8_t direction;

  //Thermo Ctrl
  uint8_t heaterPower;
  uint8_t thermoReadings;

  //Gas Ctrl
  uint8_t sensorPower;
  uint8_t gasReadings; //Readings will only be updated when true
};

extern bool recv_struct( uint32_t uart, void* armStruct, void* gripperStruct, void* drillStruct, uint8_t *id);

enum peripheral_devices{robotic_arm, drill, gripper};

extern void send_struct(uint32_t uart, void* my_struct, enum peripheral_devices device);

//Reads the actual data to be put into the data structure. Note this isn't for the user to call,
//it's only supposed to be called by recv_struct
extern bool readStructData(uint32_t uart, void *dataStruct, int size, uint8_t id);

#endif /* STRUCT_XFER_H_ */
