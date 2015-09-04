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
 * ARM VERSION UPDATES: This version has been heavily modified. Recv_struct now doesn't block and utilizes the uartRxBuff
 * variable found in main, which is written into by a uart RX interrupt that reads for the start bytes and then puts the
 * next few bytes in the uart RX FIFO buffer into the uartRxBuff as well, which is shared with recv_struct. Recv_struct
 * waits until uartRxBuff[0] = start byte1, then the next 3 from it as well (the interrupt should have loaded them in)
 * then goes about business like usual for the non arm version. Also, it no longer blocks. For more information about the
 * interrupt process, pop over to armMainV4.h and see its description.
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

#ifndef STRUCT_XFER_ARMVERSION_OLD_H_
#define STRUCT_XFER_ARMVERSION_OLD_H_

#include <stdbool.h>
#include <stdint.h>
#include "utils\uartstdio.h"
#include "driverlib\UART.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"

struct arm_control_struct
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

#define STRUCT_START1 0x06
#define STRUCT_START2 0X85



/* Function to read a struct from the specified uart line, works in conjuction with armMain's interrupts. It waits until
 * the uart RX interrupt fills the uartRxBuff variable with the proper data, then after verifying the first few bytes are
 * correct reads the rest and loads the resulting data into the myStruct structure, which is
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
 * Note: Unlike the other versions of recv_struct, the arm specific version is heavily modified and doesn't block.
 */
extern bool recv_struct( uint32_t uart, struct arm_control_struct* myStruct);


//specific to arm version
extern uint8_t uartRxBuf[4];
extern uint8_t handled;
extern void delay(int time);
#endif /* STRUCT_XFER_H_ */