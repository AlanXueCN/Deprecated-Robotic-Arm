// hardwareAbstraction.c 2015

//the roveWare / texas instruments interface lib

#include "../roveWareHeaders/roveHardwareAbstraction.h"

bool recvSerialStructMessage(int device_port, void* recieve_buffer, char* command_buffer)
{
	uint8_t rx_len = 0;
	uint8_t start_byte1 = 0x06;
	uint8_t start_byte2 = 0x85;

	uint8_t check_sum;

	int bytes_read = 0;

	uint8_t garbage_count = 10; // This is used to decide how much pre-data to discard before quitting

	bool start_received = false;

	//testing
	int debug_rx_cnt = 0;

	if (rx_len == 0)
	{
		while (!start_received)
		{
			bytes_read = deviceRead(device_port, command_buffer, 1);

			if (bytes_read == 1)
			{
				if (command_buffer[0] == start_byte1)
				{
					start_received = true;

				}else{

					garbage_count--;

					if (garbage_count <= 0)

						return false;

				}//endif

			}//endif

			debug_rx_cnt++;

		}//endwhile

//		System_printf("Looped through the rx debug_rx_cnt: %d\n", debug_rx_cnt);
//		System_flush();

		if ((bytes_read = deviceRead(device_port, command_buffer, 1)) == 1)
		{
			if (command_buffer[0] != start_byte2)
			{
				return false;
			}//end if
			else
			{
				bytes_read = deviceRead(device_port, command_buffer, 1);
				if (bytes_read == 1)
				{
					rx_len = command_buffer[0];
					if (rx_len == 0)
					{
						return false;
					}//endif
				}//end if
				else
				{
					return false;
				}//end else
			}//endif

		}//endif
		else
		{
			return false;
		}

		//System_printf("rx_len: %d\n", rx_len);
		//System_flush();

	}//end if (rx_len == 0)

	if (rx_len > 0)
	{
		bytes_read = deviceRead(device_port, command_buffer, rx_len + 1);

		//rx_len + 1 for the checksum byte at the end
		if (bytes_read != (rx_len + 1))

			return false;

		check_sum = calcCheckSum(command_buffer, rx_len);

		if (check_sum != command_buffer[rx_len])
		{
			// Checksum error
			return false;
		}//endif

		memcpy(recieve_buffer, command_buffer, rx_len);
		return true;
	}//endif

	return false;

}//endfnctn recvSerialStructMessage


int deviceRead(int device_port, char* command_buffer, int bytes_to_read){

	int bytes_read;

	// give us access to the uart handles defined at the global scope in main

	//System_printf("Entered deviceRead\n");
	//System_flush();

	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
	extern UART_Handle uart7;


	// we have to include case 0 to get TI's compiler to build a jump table
	// if we leave this out, mux performance goes from O(1) to O(n) (That's bad)
	switch(device_port){
		//case 0:
		case 0:
		break;
		case 1:
		break;
		case MOTHERBOARD_UART:
			//Write the command_buffer to the device
			//System_printf("case: %d\n", MOTHERBOARD_UART);
			//System_flush();

			bytes_read = UART_read(uart2, command_buffer, bytes_to_read);

			//System_printf("totally passed UART_read with bytes_read: %d\n", bytes_read);
			//System_flush();
		break;

		default:
			//Tried to write to invalid device
			//System_printf("DeviceRead passed invalid device %d\n", device_port);
			//System_flush();
		return -1;

	}//endswitch(device_port)

	return bytes_read;

}//endfnctn deviceRea


int getDevicePort(uint8_t device_id)
{
	switch(device_id)
	{
		case WRIST_A_ID...BASE_ID:

		return DYNAMIXEL_UART;

		case LIN_ACT_ID:

		return LINEAR_ACTUATOR_UART;

		case MOB_ID:

		return MOTHERBOARD_UART;

		default:

			System_printf("getDevicePort passed invalid device_id %d\n", device_id);
			System_flush();

		return -1;
	}//endswitch (device)

}//endfnctn getDevicePort

int getStructSize(uint8_t struct_id)
{
	switch(struct_id)
	{
		case SET_ENDLESS_CMD:

			return sizeof(struct set_endless_struct);

		case SET_SPEED_LEFT_CMD...SET_SPEED_RIGHT_CMD:

			return sizeof(struct set_speed_struct);

		case SET_LIN_ACTUATOR_CMD:

			return (sizeof(struct linear_actuator_struct) - LIN_DONT_PRINT_BYTES);

		default:

			System_printf("getStructSize passed invalid struct_id %d\n", struct_id);
			System_flush();

		return -1;

	}//endswitch

}//endfnctn getDevicePort


//see roveStructs.h and rovWare.h for config
void buildDynamixelStructMessage(void* dynamixel_struct, char* command_buffer, uint8_t dynamixel_id, int16_t command_value)
{
	uint8_t check_sum;
	uint8_t speed_low_byte = (uint8_t)command_value;
	uint8_t speed_high_byte = (uint8_t)(command_value >> 8);

	System_printf("Testing buildDynamixelStructMessage struct_id %d, \n", ((struct dynamixel_id_cast*)dynamixel_struct)->struct_id);
	System_flush();


	switch( ((struct dynamixel_id_cast*)dynamixel_struct)->struct_id)
	{
		case SET_ENDLESS_CMD:

			// to switch cast the single dynamixel_msg_struct global buffer instance
			// using precompile macros to config flex and avoid extra memory copy
			( (struct set_endless_struct*)dynamixel_struct)->start_byte1 = AX_START;
			( (struct set_endless_struct*)dynamixel_struct)->start_byte2 = AX_START;
			( (struct set_endless_struct*)dynamixel_struct)->dynamixel_id = dynamixel_id;
			( (struct set_endless_struct*)dynamixel_struct)->msg_size = AX_GOAL_LENGTH;
			( (struct set_endless_struct*)dynamixel_struct)->read_write_flag = AX_WRITE_DATA;
			( (struct set_endless_struct*)dynamixel_struct)->ccw_angle_limit_reg_addr = AX_CCW_ANGLE_LIMIT_L;
			( (struct set_endless_struct*)dynamixel_struct)->ccw_angle_limit_low_byte = 0x00;
			( (struct set_endless_struct*)dynamixel_struct)->ccw_angle_limit_high_byte = 0x00;

			check_sum = ( ~(dynamixel_id + AX_GOAL_LENGTH + AX_WRITE_DATA + AX_CCW_ANGLE_LIMIT_L) ) & 0xFF;

			( (struct set_endless_struct*)dynamixel_struct)->check_sum = check_sum;

		break;

		case SET_SPEED_LEFT_CMD:

			( (struct set_speed_struct*)dynamixel_struct)->start_byte1 = AX_START;
			( (struct set_speed_struct*)dynamixel_struct)->start_byte2 = AX_START;
			( (struct set_speed_struct*)dynamixel_struct)->dynamixel_id = dynamixel_id;
			( (struct set_speed_struct*)dynamixel_struct)->msg_size = AX_SPEED_LENGTH;
			( (struct set_speed_struct*)dynamixel_struct)->read_write_flag = AX_WRITE_DATA;
			( (struct set_speed_struct*)dynamixel_struct)->speed_low_byte_reg_addr = AX_GOAL_SPEED_L;
			( (struct set_speed_struct*)dynamixel_struct)->speed_low_byte = speed_low_byte;
			( (struct set_speed_struct*)dynamixel_struct)->speed_high_byte = speed_high_byte;

			check_sum = ( ~(dynamixel_id + AX_SPEED_LENGTH + AX_WRITE_DATA + AX_GOAL_SPEED_L + speed_low_byte + speed_high_byte) ) & 0xFF;

			( (struct set_endless_struct*)dynamixel_struct)->check_sum = check_sum;

		break;

		case SET_SPEED_RIGHT_CMD:

			( (struct set_speed_struct*)dynamixel_struct)->start_byte1 = AX_START;
			( (struct set_speed_struct*)dynamixel_struct)->start_byte2 = AX_START;
			( (struct set_speed_struct*)dynamixel_struct)->dynamixel_id = dynamixel_id;
			( (struct set_speed_struct*)dynamixel_struct)->msg_size = AX_SPEED_LENGTH;
			( (struct set_speed_struct*)dynamixel_struct)->read_write_flag = AX_WRITE_DATA;
			( (struct set_speed_struct*)dynamixel_struct)->speed_low_byte_reg_addr = AX_GOAL_SPEED_L;
			( (struct set_speed_struct*)dynamixel_struct)->speed_low_byte = speed_low_byte;
			( (struct set_speed_struct*)dynamixel_struct)->speed_high_byte = (speed_high_byte + 4);

			check_sum = ( ~(dynamixel_id + AX_SPEED_LENGTH + AX_WRITE_DATA + AX_GOAL_SPEED_L + speed_low_byte + speed_high_byte) ) & 0xFF;

			( (struct set_endless_struct*)dynamixel_struct)->check_sum = check_sum;

		break;

		default:

				System_printf("Error in function: buildDynamixelStructMessage() - struct_id is not valid");
				System_flush();
		break;

		}//endswitch

	memcpy( command_buffer, dynamixel_struct, sizeof(struct set_speed_struct) );

}//end fnctn buildDynamixelStructMessage

//current_position = buildLinActuatorMessage((void*)(&buffer_struct), command_buffer, device_id, current_position, target_increment);

int16_t buildLinActuatorStructMessage(void* lin_act_struct, char* command_buffer, int16_t current_position, int16_t command_value)
{

	switch( ( (struct dynamixel_id_cast*)lin_act_struct)->struct_id)
	{
		case SET_LIN_ACTUATOR_CMD:

			//target = current + command
			((struct linear_actuator_struct*)lin_act_struct)->target_position = current_position + command_value;

			if ( ((struct linear_actuator_struct*)lin_act_struct)->target_position > MAX_LIN_ACT_POSITION )
			{
				((struct linear_actuator_struct*)lin_act_struct)->target_position = MAX_LIN_ACT_POSITION;

			}//endif

			if ( ((struct linear_actuator_struct*)lin_act_struct)->target_position < MIN_LIN_ACT_POSITION )
			{
				((struct linear_actuator_struct*)lin_act_struct)->target_position = MIN_LIN_ACT_POSITION;

			}//endif

			current_position = ((struct linear_actuator_struct*)lin_act_struct)->target_position;

			//target_low_byte = 0xC0 + (target + 0x1F)
			((struct linear_actuator_struct*)lin_act_struct)->target_low_byte =
			(uint8_t)( 0xC0 + (( ((struct linear_actuator_struct*)lin_act_struct)->target_position)& 0x1F) );

			//target_high_byte =
			((struct linear_actuator_struct*)lin_act_struct)->target_high_byte =
			(uint8_t)( ((((struct linear_actuator_struct*)lin_act_struct)->target_position) >> 5)& 0x7F);

		memcpy( command_buffer, lin_act_struct, sizeof(struct linear_actuator_struct) );

		return current_position;

		default:

			System_printf("Error in function: buildDynamixelStructMessage() - struct_id is not valid");
			System_flush();

		return -1;

	}//endswitch

}//end fnctn buildLinActuatorStructMessage


int deviceWrite(int device_port, char* buffer,  int bytes_to_write)
{
	int bytes_wrote;

	// give us access to the uart handles defined at the global scope in main
	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
	extern UART_Handle uart7;

	//System_printf("deviceWrite called\n");
	//System_flush();

	switch(device_port)
	{
		case DYNAMIXEL_UART:

			bytes_wrote = UART_write(uart4, buffer, bytes_to_write);

		break;
		case LINEAR_ACTUATOR_UART:

			bytes_wrote = UART_write(uart7, buffer, bytes_to_write);

		break;

		default:

			System_printf("DeviceWrite passed invalid device %d\n", device_port);
			System_flush();

		break;
		//etc.
	}//end switch(jack)

	// make sure the message is fully written before leaving the function

	ms_delay(1);

	return bytes_wrote;

}//endfnctn deviceWrite


void digitalWrite(int pin, int write)
{
	//check 0 case first to optimize indexed compares
	if(write == LOW)
	{
		switch(pin)
		{
			case SET_TRI_ST_BUF_Tx :

				GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, (0));

			break;

			default:

				//System_printf("DigitalWrite passed invalid pin %d\n", pin);
				//System_flush();

			return;

		}//endswitch

	}else if(write == HIGH)
	{

		switch(pin)
		{
			case SET_TRI_ST_BUF_Tx :

				//~0 implies write without calling GPIO_PIN_3 lookup
				GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, (~0));

			break;

			default:

				//System_printf("DigitalWrite passed invalid pin %d\n", pin);
				//System_flush();

			return;

		}//endswitch

	}//endif

	return;

}//endfnctn digitalWrite


//calcCheckSum(local_buffer, rx_len);
//uint8_t calcCheckSum(const void* my_struct, uint8_t size)
uint8_t calcCheckSum(const char* command_buffer, uint8_t size)
{

	uint8_t check_sum = size;
	uint8_t i;

	for(i = 0; i < size; i++)
		check_sum ^= *(command_buffer + i);

	return check_sum;

}//end fnctn
