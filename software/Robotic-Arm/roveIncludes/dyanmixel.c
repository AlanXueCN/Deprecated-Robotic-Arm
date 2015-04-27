/*
 * dyanmixel.c
 *
 *  Created on: Apr 26, 2015
 *      Author: mrdtdev
 */


#include "dynamixel.h"

void DynamixelSendData(UART_Handle uart, char data)
{
	UART_write(uart, &data, 1);
	return;
}

// Sets a dynamixel to a specific speed
void DynamixelSetSpeed(UART_Handle uart, uint8_t id, int side, int16_t speed)
{

}

// Sets a dynamixel to a specific angle
void DynamixelSetAngle(UART_Handle uart, uint8_t id, int16_t angle);


void DynamixelReset(UART_Handle uart, uint8_t id)
{
	char Checksum = (~(id + AX_RESET_LENGTH + AX_RESET))&0xFF;

	DynamixelSendData(uart, AX_START);
	DynamixelSendData(uart, AX_START);
	DynamixelSendData(uart, id);
	DynamixelSendData(uart, AX_RESET_LENGTH);
	DynamixelSendData(uart, AX_RESET);
	DynamixelSendData(uart, Checksum);

	delayMicros(TX_DELAY_TIME);

    return ;
}

void delayMicros(int microseconds)
{

	SysCtlDelay( microseconds*(SysCtlClockGet() / 100000) );

	return;
}
