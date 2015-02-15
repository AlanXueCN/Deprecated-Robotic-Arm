/*
 * struct_xfer.c
 *
 *  Created on: May 6, 2014
 *      Author: Zeus
 *  V2 -- Updated on 2-14-15 by broseidon. Cometh at me, brother doth mine
 *  what do you call a snail that's a sailor? ...not a snailor, that'd be just a stupid joke.
 */

#include "struct_xfer.h"

// Reads struct straight up from uart buffer
bool recv_struct( uint32_t uart, receiveStruct* myStruct)
{
	// Variables
	uint8_t i;
	uint8_t start_byte1 = 0x06;
	uint8_t start_byte2 = 0x85;
	uint8_t size;
	uint8_t id;
	uint8_t instruction;
	uint8_t calc_CS;	   //calculated Chacksum
	uint8_t temp;
	uint8_t rx_buffer[150];

	//todo:Be a good idea to globalize sizes
	const int gripSize = sizeof(*((struct gripper_control_struct*)myStruct));
	const int drillSize = sizeof(*((struct drill_Controls*)myStruct));
	const int armSize = sizeof(*((struct arm_control_struct *)myStruct));
	const int motorSize= sizeof(*((struct motor_struct*)myStruct));
	const int scienceSize = sizeof(*((struct science_payload_control_struct*)myStruct));
	const int lightingSize = sizeof(*((struct lighting_board_struct*)myStruct));
	const int cameraSize = sizeof(*((struct camera_control_struct*)myStruct));
	//If adding more structs, follow this format to calculate size


	// Check for Start byte 1
	do {
		temp = UARTCharGet(uart);
	} while ( temp != start_byte1 );



	// Check for Start byte 2
	temp = UARTCharGet(uart);
	if ( temp != start_byte2 )
	{
		// Kick out of function
		return false;
	}



	//get struct ID, and get proper size using it.
	temp = UARTCharGet(uart);
	id = temp;
	if (temp == GRIPPER_STRUCT_ID)
	{
		size = gripSize;
	}
	else if(temp == DRILL_STRUCT_ID)
	{
		size = drillSize;
	}
	else if(temp == ARM_STRUCT_ID)
	{
		size = armSize;
	}
	else if(temp == SCIENCE_STRUCT_ID)
	{
		size = scienceSize;
	}
	else if(temp == LIGHTING_STRUCT_ID)
	{
		size = lightingSize;
	}
	else if(temp == CAMERA_STRUCT_ID)
	{
		size = cameraSize;
	}
	else if(temp == MOTOR_STRUCT_ID)
	{
		size = motorSize;
	}						//If adding on more structs, put in another else-if for them here
	else
		return(false);//didn't match any known ID's. Cue the fail horn, fire some people



	//getInstructionID
	temp = UARTCharGet(uart);
	instruction = temp;
	if(temp == INST_IDENTITY_REQUEST)		//the if-else's are there as a check to make sure the data is somethign we'd recognize
		instruction = INST_IDENTITY_REQUEST;//if you think it's unneccessary or want to save some cycles, just save temp directly
											//into instruction
	else if(temp == INST_IDENTITY_REPLY)
		instruction = INST_IDENTITY_REPLY;

	else if(temp == INST_OPSMODE_REQUEST)
		instruction = INST_OPSMODE_REQUEST;

	else if(temp == INST_OPSMODE_REPLY)
		instruction = INST_OPSMODE_REPLY;

	else if(temp == INST_TELEMETRY_REQUEST)
		instruction = INST_TELEMETRY_REQUEST;

	else if(temp == INST_TELEMETRY_REPLY)
		instruction = INST_TELEMETRY_REPLY;

	else if(temp == INST_COMMAND_REQUEST)
		instruction = INST_COMMAND_REQUEST;

	else if(temp == INST_COMMAND_REPLY)
		instruction = INST_COMMAND_REPLY;

	else
		return(false); //fire all the people



	//check size:
	temp = UARTCharGet(uart);

	if(size != temp)
		return(false); //no bad joke this time. :(



	// Read in data bytes
	for ( i = 0 ; i <= size ; i++)
	{
		temp = UARTCharGet(uart);
		rx_buffer[i] = temp;
	}



	// calculate checksum
	calc_CS = size;

	for ( i=0 ; i< size ; i++ )
	{
		calc_CS ^= rx_buffer[i];
	}

	// Does checksum match?
	if ( calc_CS != rx_buffer[size] )
	{
		// Checksum does not match
		return false;
	}



	// Copy buffer into struct, then pass in the instruction and size bytes
	memcpy (myStruct, rx_buffer, size);
	myStruct -> id = id;
	myStruct -> instruction = instruction;
	myStruct -> size = size;

	// Success
	return(true);
}


void send_struct(uint32_t uart, void* my_struct, uint8_t instruction, uint8_t id)
{
    uint8_t size;
    uint8_t start_byte1 = 0x06;
    uint8_t start_byte2 = 0x85;

    switch(id)
    {
        case MOTOR_STRUCT_ID:
            size = sizeof(*((struct motor_struct*)my_struct));
            break;
        case ARM_STRUCT_ID:
        	size = sizeof(*((struct arm_control_struct *)my_struct));
        	break;
        case GRIPPER_STRUCT_ID:
        	size = sizeof(*((struct gripper_control_struct*)my_struct));
        	break;
        case DRILL_STRUCT_ID:
        	size = sizeof(*((struct drill_Controls*)my_struct));
        	break;
        case SCIENCE_STRUCT_ID:
        	size =  sizeof(*((struct science_payload_control_struct*)my_struct));
        	break;
        case LIGHTING_STRUCT_ID:
        	size =  sizeof(*((struct lighting_board_struct*)my_struct));
        	break;
        case CAMERA_STRUCT_ID:
        	size =  sizeof(*((struct camera_control_struct*)my_struct));
			break;

    }

    uint8_t* address = (uint8_t*) my_struct; //pointer for use in sending the data.
    uint8_t CS = size; //checksum

    UARTCharPut(uart, start_byte1);

    UARTCharPut(uart, start_byte2);

    UARTCharPut(uart, id); //todo:Figure out where to put these in protocol

    UARTCharPut(uart, instruction);

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


