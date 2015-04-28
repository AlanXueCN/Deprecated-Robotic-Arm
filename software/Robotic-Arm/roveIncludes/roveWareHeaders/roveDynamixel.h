// dynamixel.h

#pragma once

#ifndef ROVEDYNAMIXEL_H_
#define ROVEDYNAMIXEL_H_

// globally scoped Texas Instruments (TI) headers

#include "../RoboticArmMain.h"

// MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "../roveWare.h"

//void dynamixelSendData(UART_Handle uart, uint8_t* data_buffer);

void dynamixelSetEndless(UART_Handle uart, uint8_t dynamixel_id);

/*
// Sets a dynamixel to a specific speed
void DynamixelSetSpeed(UART_Handle uart, uint8_t id, int side, int16_t speed);

// Sets a dynamixel to a specific angle
void DynamixelSetAngle(UART_Handle uart, uint8_t id, int16_t angle);

void DynamixelReset(UART_Handle uart, uint8_t id);

void delayMicros(int microseconds);
*/
#endif /* DYNAMIXEL_H_ */
