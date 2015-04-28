/*
 * dyanmixel.c
 *
 *  Created on: Apr 26, 2015
 *      Author: mrdtdev
 */

#include "../roveWareHeaders/roveDynamixel.h"

void dynamixelSetEndless(UART_Handle uart, uint8_t dynamixel_id)
{
//TODO:

		int bytes_to_write;
		int bytes_wrote;
		int device_port;

		dynamixel_msg_struct dynamixel_buffer_struct;

		// set tristate buffer to transmit
		digitalWrite(DATA_FLOW_CTRL_1, HIGH);

		// populate the dynamixel_buffer_struct for dynamixel format frame
		buildDynamixelMessage((void*)(&dynamixel_buffer_struct), dynamixel_id);

		//get the uart
		device_port = getDevicePort(dynamixel_id);

		bytes_to_write = getStructSize( ( (struct dynamixel_id_cast*)(&dynamixel_buffer_struct))->struct_id);

		bytes_wrote = deviceWrite(device_port, (char*)&dynamixel_buffer_struct, bytes_to_write);

		//set tri state buffer back for read
		digitalWrite(DATA_FLOW_CTRL_1, HIGH);

}//endfnctn  dynamixelSetEndless

/*void dynamixelWrite(UART_Handle uart, uint8_t* data_buffer)
{

	return;
}

*/

/*
OWENS STUBS

// Sets a dynamixel to a specific speed
void dynamixelSetSpeed(UART_Handle uart, uint8_t id, int side, int16_t speed)
{
	if(speed<0)
	{
		//send the data for reverse
	} else
	{
		//send the data for forward
	}
	return;
}

// Sets a dynamixel to a specific angle
void DynamixelSetAngle(UART_Handle uart, uint8_t id, int16_t angle)
{
	return;
}


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

*/

//END OWENS STUBS
///////////////////////////////ported from SAVAGE ELECTRONICS

//Runtime Command to turn on and off endless rotation ( maaaybeee feeels a bit liiike Open Loop emulation)



//Runtime direction and speed
/*

//TODO port this
int DynamixelClass::turn(unsigned char ID, bool SIDE, int Speed)
{
		if (SIDE == 0){                          // Move Left///////////////////////////

			char Speed_H,Speed_L;
			Speed_H = Speed >> 8;
			Speed_L = Speed;                     // 16 bits - 2 x 8 bits variables
			Checksum = (~(ID + AX_SPEED_LENGTH + AX_WRITE_DATA + AX_GOAL_SPEED_L + Speed_L + Speed_H))&0xFF;

			switchCom(Direction_Pin,Tx_MODE);
			sendData(AX_START);                // Send Instructions over Serial
			sendData(AX_START);
			sendData(ID);
			sendData(AX_SPEED_LENGTH);
			sendData(AX_WRITE_DATA);
			sendData(AX_GOAL_SPEED_L);
			sendData(Speed_L);
			sendData(Speed_H);
			sendData(Checksum);
			delayus(TX_DELAY_TIME);
			switchCom(Direction_Pin,Rx_MODE);

			return(read_error());               // Return the read error
		}
		else
		{                                            // Move Rigth////////////////////
			char Speed_H,Speed_L;
			Speed_H = (Speed >> 8) + 4;
			Speed_L = Speed;                     // 16 bits - 2 x 8 bits variables
			Checksum = (~(ID + AX_SPEED_LENGTH + AX_WRITE_DATA + AX_GOAL_SPEED_L + Speed_L + Speed_H))&0xFF;

			switchCom(Direction_Pin,Tx_MODE);
			sendData(AX_START);                // Send Instructions over Serial
			sendData(AX_START);
			sendData(ID);
			sendData(AX_SPEED_LENGTH);
			sendData(AX_WRITE_DATA);
			sendData(AX_GOAL_SPEED_L);
			sendData(Speed_L);
			sendData(Speed_H);
			sendData(Checksum);
			delayus(TX_DELAY_TIME);
			switchCom(Direction_Pin,Rx_MODE);

			return(read_error());                // Return the read error
		}
}
*/
