///
 // roveHardwareAbstraction.h
 //
 //  Created on: Mar 3, 2015
 //      Author: mrdtdev
 ///

#pragma once

#ifndef ROVEHARDWAREABSTRACTION_H_
#define ROVEHARDWAREABSTRACTION_H_

// globally scoped Texas Instruments (TI) headers

#include "../RoboticArmMain.h"

// MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "../roveWare.h"

//HARDWARE ABSTRACTION FUNCTIONS

void buildDynamixelStructMessage(void* dynamixel_struct, uint8_t dynamixel_id);

// digitalWrite sets a bit to be on or off
// inputs:
// 	pin - name of the pin. Can be found in rovePinMap.h or the eagle file
// 	val - HIGH or LOW
// outputs:
// 	none
// pre: pin has been set to mode OUTPUT by pinMode
// post: Pin is set to on or off
//
// usage example: digitalWrite(U3_MUX_S0, HIGH);

void digitalWrite(int pin, int val);

//////////////////////////////////////////////THESE HANDLE GRIPPER and DRILL:

// deviceWrite sends data passed to it to the specified RS485 jack.
// It will deal with properly muxing to the device and writing to the uart
//    internally
// inputs:
// 	rs485jack - number of the jack to write to (0-18)
// 	buffer - where to get the data from
// 	bytes_to_write - number of bytes to write
// outputs:
// 	returns number of bytes written.
// 		-1 for invalid device.
// 		UART_ERROR for, well, a uart error
// pre: GPIO pins and UARTS have been initialized
// post: mux is set to correct settings for specified rs485 jack, data
// 	sent to device over UART
//
// usage example:
// 	buffer[15] = "My Buffer";
// 	deviceWrite(14, buffer, 15); //Write "My Buffer" to device on jack 14

int deviceWrite(int rs485jack, char* buffer, int bytes_to_write);

// deviceRead Retrieves a specified number of bytes from
// It will deal with properly muxing to the device and writing to the uart
//    internally
// inputs:
// 	rs485jack - number of the jack to write to (0-18) on ONBOARD_ROVECOMM
// 	buf_len - size of the buffer
// 	timeout: number of milliseconds to wait before moving abandoning the read
// 		and returning an error. Also accepts BIOS_WAIT_FOREVER
// outputs:
// 	returns number of bytes read.
// 		-1 for invalid device.
// 		UART_ERROR for, well, a uart error
// 	buffer: Overwritten with the data recieved from uart, and null terminated
// pre: muxes have been set up & UARTS are initialized
// post:mux is set to correct settings for specified rs485 jack, data
// 	recieved from device UART
//
// usage example:
// 	buffer[15];
// 	deviceRead(13, buffer, 1, BIOS_WAIT_FOREVER);
// 	switch(buffer[1])
// 	{
// 		case MY_STRUCT_ID: //This should be defined
// 			deviceRead(13, buffer, sizeof(struct my_struct), BIOS_WAIT_FOREVER);
// 			break;
// 	}

int deviceRead(int rs485jack, char* buffer, int bytes_to_read, int timeout);

#endif // ROVEHARDWAREABSTRACTION_H_
