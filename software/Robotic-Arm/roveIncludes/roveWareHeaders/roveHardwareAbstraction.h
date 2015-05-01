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

void buildDynamixelStructMessage(void* dynamixel_struct, char* command_buffer, uint8_t dynamixel_id, int16_t command_value );

int16_t buildLinActuatorStructMessage(void* lin_act_struct, char* command_buffer, int16_t current_position, int16_t command_value);

bool recvSerialStructMessage(int device_port, void* recieve_buffer, char* command_buffer);

void digitalWrite(int pin, int val);

int deviceWrite(int device_port, char* buffer, int bytes_to_write);

int deviceRead(int device_port, char* buffer, int bytes_to_read);

int getDevicePort(uint8_t device_id);

int getStructSize(uint8_t struct_id);

uint8_t calcCheckSum(const char* my_struct, uint8_t size);

#endif // ROVEHARDWAREABSTRACTION_H_
