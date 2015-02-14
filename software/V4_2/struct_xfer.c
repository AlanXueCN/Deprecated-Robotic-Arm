/*
 * struct_xfer.c
 *
 *  Created on: May 6, 2014
 *      Author: Zeus
 *  Updated on 2-13-15 by poseidon. Cometh at me, brother doth mine
 */

#include "struct_xfer.h"

// Reads struct straight up from uart buffer
bool recv_struct( uint32_t uart, void* armStruct, void* gripperStruct, void* drillStruct, uint8_t* id)
{
	// Variables
	uint8_t start_byte1 = 0x06;
	uint8_t start_byte2 = 0x85;
	int gripSize = sizeof(*((struct gripper_control_struct*)gripperStruct));
	int drillSize = sizeof(*((struct drill_Controls*)drillStruct));
	int armSize = sizeof(*((struct arm_data_struct *)armStruct));
	enum peripheral_devices device;

	char temp;

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

	// Use size to check for what the struct is
	temp = UARTCharGet(uart);
	if (temp == gripSize) //if the size is the same size as that of the gripper
	{
		device = gripper;
		*id = GRIPPER;
	}
	else if(temp == drillSize)//if the size is that of that of the drill
	{
		device = drill;
		*id = DRILL;
	}
	else if(temp == armSize) //if the size is that of the arm struct
	{
		device = robotic_arm;
		*id = ROBOTIC_ARM;
	}
	else
		return(false);//size didn't match any. Cue the fail horns




	if(device == gripper)
	{
		if(readStructData(uart, gripperStruct, gripSize, GRIPPER) == false)
			return(false);
	}

	else if(device == drill)
	{
		if(readStructData(uart, drillStruct, drillSize, DRILL) == false)
			return(false);
	}

	else
	{
		if(readStructData(uart, armStruct, armSize, ROBOTIC_ARM) == false)
			return(false);
	}

	return true;
}


void send_struct(uint32_t uart, void* my_struct, enum peripheral_devices device)
{
    uint8_t size;
    uint8_t start_byte1 = 0x06;
    uint8_t start_byte2 = 0x85;

    switch(device)
    {
      //  case motor_controller:
        //    size = sizeof(*((struct motor_struct*)my_struct));
         //   break;
        case robotic_arm:
        	size = sizeof(*((struct arm_data_struct *)my_struct));
        	break;
        case gripper:
        	size = sizeof(*((struct gripper_control_struct*)my_struct));
        	break;
        case drill:
        	size = sizeof(*((struct drill_Controls*)my_struct));
        	break;
   //     case science_payload:
     //   	size =  sizeof(*((struct science_payload_control_struct*)my_struct));
       // 	break;
      //  case lighting_board:
        //	size =  sizeof(*((struct lighting_board_struct*)my_struct));
       // 	break;
      //  case camera:
        //	size =  sizeof(*((struct camera_control_struct*)my_struct));
			//break;

    }

    uint8_t* address = (uint8_t*) my_struct;
    uint8_t CS = size;

    UARTCharPut(uart, start_byte1);

    UARTCharPut(uart, start_byte2);

    UARTCharPut(uart, size);

    int i;
    for(i = 0; i<size; i++)
    {
        CS^=*(address+i);
        UARTCharPut(uart, (uint8_t)(*(address+i)));

    }

    UARTCharPut(uart, CS);
}

bool readStructData(uint32_t uart, void *dataStruct, int size, uint8_t id)
{
	uint8_t i;
	char temp;
	char rx_buffer[150];
	uint8_t calc_CS;	   //calculated Chacksum

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

	// Copy buffer into struct
	if(id == GRIPPER)
		memcpy ((struct gripper_control_struct*)dataStruct, rx_buffer, size);

	else if(id == ROBOTIC_ARM)
		memcpy ((struct arm_data_struct*)dataStruct, rx_buffer, size);

	else
		memcpy ((struct drill_controls*)dataStruct, rx_buffer, size);

	// Success
	return(true);
}

/*
// Reads struct straight up from uart buffer
bool recv_struct( uint32_t uart, void* my_struct )
{
	// Variables
	uint8_t start_byte1 = 0x06;
	uint8_t start_byte2 = 0x85;
	uint8_t calc_CS;	   //calculated Chacksum
	int i;
	int size = 108;

	// Get size of struct

	char rx_buffer[150];
	char temp;

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

	// Check if size matches
	temp = UARTCharGet(uart);
	if ( temp != size )
	{
		// Size doesn't match
		return false;
	}

	// Read in data bytes
	for ( i = 0 ; i <= size ; i++ )
	{
		temp = UARTCharGet(uart);
		rx_buffer[i] = temp;
	}

	// calculate checksum
	calc_CS = size;

	for ( i=0 ; i<size ; i++ )
	{
		calc_CS ^= rx_buffer[i];
	}

	// Does checksum match?
	if ( calc_CS != rx_buffer[size] )
	{
		// Checksum does not match
		return false;
	}

	// Copy buffer into struct
	memcpy ( my_struct, rx_buffer, size );

	// Success
	return true;

}*/

