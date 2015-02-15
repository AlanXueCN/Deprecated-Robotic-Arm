/*
 * struct_xfer.c
 *
 *  Created on: May 6, 2014
 *      Author: Zeus
 */

#include "struct_xfer.h"



// Reads struct straight up from uart buffer
bool recv_struct( uint32_t uart, void* my_struct )
{
	// Variables
	uint8_t start_byte1 = 0x06;
	uint8_t start_byte2 = 0x85;
	uint8_t size;
	uint8_t calc_CS;	   //calculated Chacksum
	int i;

	// Get size of struct

	char rx_buffer[150];
	char temp;

	// Check for Start byte 1
	do {
		UART_read(uart, &temp, 1);
	} while ( temp != start_byte1 );

	// Check for Start byte 2
	UART_read(uart, &temp, 1);
	if ( temp != start_byte2 )
	{
		// Kick out of function
		return false;
	}

	// Check if size matches
	UART_read(uart, &temp, 1);
	if ( temp != size )
	{
		// Size doesn't match
		return false;
	}

	// Read in data bytes
	for ( i = 0 ; i <= size ; i++ )
	{
		UART_read(uart, &temp, 1);
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

}
