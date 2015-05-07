// roveHardwareAbstraction.h

#pragma once

#ifndef ROVEHARDWAREABSTRACTION_H_
#define ROVEHARDWAREABSTRACTION_H_

// globally scoped Texas Instruments (TI) headers

#include "../RoboticArmMain.h"

// MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "../roveWare.h"

//HARDWARE ABSTRACTION FUNCTIONS

//fills a write char* write_buffer with the dynamixel formatted putput message
void buildDynamixelStructMessage(char* write_buffer, uint8_t dynamixel_id, uint8_t struct_id, int16_t command_value );

//fills a write char* write_buffer with the linear actuated formatted putput message
int16_t buildLinActuatorStructMessage(char* write_buffer, uint8_t struct_id, int16_t current_position, int16_t command_value);

//calls device read and fills a typdef message_struct buffer_struct with a mob message
bool recvSerialStructMessage(int device_port, void* buffer_struct);

//sets high or low for a GPIO pin number
void digitalWrite(int pin_number, int set_pin);

int deviceWrite(int device_port, char* write_buffer, int bytes_to_write);

int deviceRead(int device_port, char* read_buffer, int bytes_to_read);

int getDevicePort(uint8_t device_id);

int getStructSize(uint8_t struct_id);

uint8_t calcCheckSum(const char* read_buffer, uint8_t size);

#endif // ROVEHARDWAREABSTRACTION_H_
