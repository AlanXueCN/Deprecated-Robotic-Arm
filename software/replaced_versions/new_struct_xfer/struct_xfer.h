/*
 * struct_xfer.h
 *
 *  Created on: May 6, 2014
 *      Author: Keenan Johnson
 *  V2 -- Updated on 2-14-15 by poseidon. Cometh at me, brother doth mine
 */

/* This program is meant to easily transmit through UART the various structs that we use to keep
 * track of data and commands.
 *
 *Update information: the commands have now been updated so that they can recieve structures
 *without having the luxury of knowing what said structs are before hand, using an ID system
 *and a general storage receive struct to ID what the struct is so the programmer, after receiving,
 *can put the data into its proper struct based on the ID value.
 *
 *
 *Important notice for programmers attempting to update further:
 *current list of structs the function is set up to transmit are: gripper_control_struct,
 *drill_Controls, arm_control_struct, motor_struct, science_payload_struct,
 *lighting_board_struct, and camera_control_struct.
 *To add more, you must both give them a new ID in the list below and also tweak recv_struct for
 *the new struct. The places within recv_struct needing to be editted for new structs are pointed
 *out in comments.
 *
 *Also be aware that the functions are currently only set up to transmit and receive single bytes
 *at a time, which is the default UART transmit size. Larger words shall need to be split down.
 */

#ifndef STRUCT_XFER_H_
#define STRUCT_XFER_H_

#include <stdbool.h>
#include <stdint.h>
#include "utils\uartstdio.h"
#include "driverlib\UART.h"
#include "structs.h"

//struct ID's:
#define GRIPPER_STRUCT_ID	 0
#define DRILL_STRUCT_ID		 1
#define ARM_STRUCT_ID 		 2
#define SCIENCE_STRUCT_ID 	 3
#define LIGHTING_STRUCT_ID 	 4
#define CAMERA_STRUCT_ID 	 5
#define	MOTOR_STRUCT_ID 	 6

//instruction ID's:
#define INST_IDENTITY_REQUEST	0
#define INST_IDENTITY_REPLY		1
#define INST_OPSMODE_REQUEST	2
#define INST_OPSMODE_REPLY		3
#define INST_TELEMETRY_REQUEST	4
#define	INST_TELEMETRY_REPLY	5
#define INST_COMMAND_REQUEST	6
#define INST_COMMAND_REPLY		7
#define INST_OTHER				8 //mostly for purposes of being a placeholding inst until the
								  //instruction set is finalized. If rover communication currently
								  //doesn't use instruction sets, then use this.


/* Waits until the processor detects that something had been transmitted to it through the uart
 * through the specified line. Note that it receives it into the struct receiveStruct, which is
 * a general version of the structures used by the rover. After the function is finished, the
 * programmer should then transfer the data into the structure of their choosing in main by
 * using the memcpy(*destination struct, * copying struct, size of data to be copied (which is
 * stored into the receiveStruct's size value by the recv_struct)) command. Which struct that was
 * actually sent is determined by the id in the receiveStruct field, and the corrallary for which
 * id represents which struct is found in the constants above
 *
 * arguments: uart - base address of uart peripheral, myStruct -pointer to a receiveStruct structure
 *
 * returns: 0 if the receiving failed (checksum didn't match up, size didn't meet excepted value, etc)
 *  		1 if receiving was successful
 *
 * warnings: The program forces the PC to wait in idle inside of the function until it receives
 * something, once called.
 */
extern bool recv_struct( uint32_t uart, receiveStruct* myStruct);




/* sends a struct through the specified uart line.
 *
 * arguments: uart -- uart peripheral base address, *my_struct - a pointer to the struct being sent,
 * instruction -- which instruction the data is being sent for (if instructions aren't currently
 * implemented, use INST_OTHER), and id -- the id of the struct, found in the constants above
 *
 * warnings: blocks program until space in the transmit FIFO opens, though for most this wont be
 * a problem.
 */
extern void send_struct(uint32_t uart, void* my_struct, uint8_t instruction, uint8_t id);

#endif /* STRUCT_XFER_H_ */