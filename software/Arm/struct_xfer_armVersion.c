/*
 * struct_xfer_armVersion.c
 *
 *  Created on: May 6, 2014
 *      Author: Zeus
 *  V2 -- Updated on 2-14-15 by broseidon. Cometh at me, brother doth mine
 *  what do you call a snail that's a sailor? ...not a snailor, that'd be just a stupid joke.
 */

#include "struct_xfer_armVersion.h"

// Reads struct straight up from uart buffer
bool recv_struct( uint32_t uart, receiveStruct* myStruct)
{
	// Variables
	uint8_t i;
	uint8_t start_byte1 = 0x06;
	uint8_t start_byte2 = 0x85;
	uint8_t size;
	uint8_t id;
	uint8_t calc_CS;	   //calculated Chacksum
	int16_t temp;
	uint8_t rx_buffer[20] = {5, 5, 5, 5, 5, 5 ,5 ,5 ,5 , 5, 5, 5,5,5,5,5,5,5,5,5};


	// Check for Start byte 1
	if(uartRxBuf[0] != start_byte1 )
		return false;
	uartRxBuf[0] = 0; //reset values so that the interrupt has to put them back in again


	if (uartRxBuf[1] != start_byte2 )
	{
		// Kick out of function
		return false;
	}
	uartRxBuf[1] = 0;



	//get the size
	size = uartRxBuf[2];
	uartRxBuf[2] = 0;

	// Read in data bytes
	for ( i = 0 ; i < size ; i++)
	{
	 if((temp = UARTCharGet(uart)) == -1)
		{
			return(-1);
		}
		rx_buffer[i] = temp;
	}

	rx_buffer[size] = UARTCharGet(uart); //get the checksum


	// calculate checksum
	calc_CS = size;

	for ( i=0 ; i< size ; i++ )
	{
		calc_CS ^= rx_buffer[i];
	}

	// Does checksum match?
	/*if ( calc_CS != rx_buffer[size])
	{
		// Checksum does not match
		return false;
	}*/

	//retrieve the id, which should be the first parameter in the incoming struct always (if it's not, complain about it)
	id = rx_buffer[0];

	// Copy buffer into struct, then pass in the instruction and id and size bytes
	memcpy (myStruct, (uint8_t*)rx_buffer, size);
	myStruct -> id = id;
	myStruct -> size = size;
	delay(2);
	handled = 0;
	// Success
	return(true);
}


void send_struct(uint32_t uart, void* my_struct, uint8_t id)
{
    uint8_t size;
    uint8_t start_byte1 = 0x06;
    uint8_t start_byte2 = 0x85;
    uint8_t* address = (uint8_t*) my_struct; //pointer for use in sending the data.

	if(id == ARM_STRUCT_ID)
	{
		size = sizeof(*((struct arm_control_struct *)my_struct));
		struct arm_control_struct * armPoint = my_struct;
		armPoint -> struct_id = ARM_STRUCT_ID;
	}
	else if(id == GRIPPER_STRUCT_ID)
	{
		size = sizeof(*((struct gripper_control_struct*)my_struct));
		struct gripper_control_struct * gripPoint = my_struct;
		gripPoint -> struct_id = GRIPPER_STRUCT_ID;
	}
	else if(id == DRILL_STRUCT_ID)
	{
		size = sizeof(*((struct drill_Controls*)my_struct));
		struct drill_Controls * drillPoint = my_struct;
		drillPoint -> struct_id = DRILL_STRUCT_ID;
	}
	else
		return;//id didn't meet anything. Fire the programmer

    uint8_t CS = size; //checksum

    UARTCharPut(uart, start_byte1);

    UARTCharPut(uart, start_byte2);

    UARTCharPut(uart, size);

    uint8_t i;
    for(i = 0; i<size; i++)
    {
        CS^=*(address+i);
        UARTCharPut(uart, (uint8_t)(*(address+i))); //sends the data values byte by byte that
        											//are found at the address variable and
    }												//for each address that = (address + i) until
    												//i = size...in other words, the first data
    												//value in the struct and for all the
    												//following data values within it
    UARTCharPut(uart, CS);
}


