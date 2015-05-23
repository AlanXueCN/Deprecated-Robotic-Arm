// hardwareAbstraction.c 2015

//the roveWare / texas instruments interface lib

#include "../roveWareHeaders/roveHardwareAbstraction.h"

bool recvSerialStructMessage(int device_port, void* buffer_struct)
{
	char read_buffer[BUFFER_SIZE];

	uint8_t rx_len = 0;
	uint8_t start_byte1 = 0x06;
	uint8_t start_byte2 = 0x85;
	uint8_t check_sum;
	int bytes_read = 0;
	// This is used to decide how much pre-data to discard before quitting
	uint8_t garbage_count = 10;

	bool start_received = false;

	//testing
	//int debug_rx_cnt = 0;

	if (rx_len == 0)
	{
		while (!start_received)
		{
			bytes_read = deviceRead(device_port, read_buffer, 1);

			if (bytes_read == 1)
			{
				if (read_buffer[0] == start_byte1)
				{
					start_received = true;

				}else{

					garbage_count--;

					if (garbage_count <= 0)

						return false;

				}//endif

			}//endif

			//testing
			//debug_rx_cnt++;

		}//endwhile

//		System_printf("Looped through the rx debug_rx_cnt: %d\n", debug_rx_cnt);
//		System_flush();

		if ((bytes_read = deviceRead(device_port, read_buffer, 1)) == 1)
		{
			if (read_buffer[0] != start_byte2)
			{
				return false;
			}//end if
			else
			{
				bytes_read = deviceRead(device_port, read_buffer, 1);
				if (bytes_read == 1)
				{
					rx_len = read_buffer[0];
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
		bytes_read = deviceRead(device_port, read_buffer, rx_len + 1);

		//rx_len + 1 for the checksum byte at the end
		if (bytes_read != (rx_len + 1))

			return false;

		check_sum = calcCheckSum(read_buffer, rx_len);

		if (check_sum != read_buffer[rx_len])
		{
			// Checksum error
			return false;
		}//endif

		memcpy(buffer_struct, read_buffer, rx_len);
		return true;
	}//endif

	return false;

}//endfnctn recvSerialStructMessage


int deviceRead(int device_port, char* read_buffer, int bytes_to_read){

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
		    //just bytes_read = -1?
		    return -1;
		case 1:
		    //just bytes_read = -1?
		                return -1;
		case MOTHERBOARD_UART:
			//System_printf("deviceRead case: %d, bytes_to_read %d\n", MOTHERBOARD_UART, bytes_to_read);
			//System_flush();

			bytes_read = UART_read(uart2, read_buffer, bytes_to_read);

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

		case GRIPPER_ID:

		return END_EFFECTOR_UART;

		case DRILL_ID:

		return END_EFFECTOR_UART;

		default:

			//System_printf("getDevicePort passed invalid device_id %d\n", device_id);
			//System_flush();

		return -1;
	}//endswitch (device)

}//endfnctn getDevicePort

int getStructSize(uint8_t struct_id)
{
	switch(struct_id)
	{
		case SET_ENDLESS_CMD:

			return sizeof(set_dyna_endless_struct);

		case SET_SPEED_LEFT_CMD...SET_SPEED_RIGHT_CMD:

			return sizeof(set_dyna_speed_struct);

		case SET_LIN_ACTUATOR_CMD:

			return sizeof(linear_actuator_struct);

		case GET_DRILL_CMD:

		    return sizeof(drill_struct);

		default:

			//System_printf("getStructSize passed invalid struct_id %d\n", struct_id);
			//System_flush();

		return -1;

	}//endswitch

}//endfnctn getDevicePort


//see roveStructs.h and rovWare.h for config
void buildDynamixelStructMessage(char* write_buffer, uint8_t dynamixel_id, uint8_t struct_id, int16_t command_value)
{
	uint8_t speed_low_byte = (uint8_t)command_value;
	uint8_t speed_high_byte = (uint8_t)(command_value >> 8);

	//System_printf("Testing buildDynamixelStructMessage speed_high_byte %d, speed_low_byte %d\n", speed_high_byte, speed_low_byte);
	//System_flush();

	switch(struct_id)
	{
		case SET_ENDLESS_CMD:

			// macro casting the buffer_struct instance see roveWare.h and roveStruct.h
			SET_ENDLESS_STRUCT->start_byte1 = AX_START;
			SET_ENDLESS_STRUCT->start_byte2 = AX_START;
			SET_ENDLESS_STRUCT->dynamixel_id = dynamixel_id;
			SET_ENDLESS_STRUCT->msg_size = AX_GOAL_LENGTH;
			SET_ENDLESS_STRUCT->read_write_flag = AX_WRITE_DATA;
			SET_ENDLESS_STRUCT->ccw_angle_limit_reg_addr = AX_CCW_ANGLE_LIMIT_L;
			SET_ENDLESS_STRUCT->ccw_angle_limit_low_byte = 0x00;
			SET_ENDLESS_STRUCT->ccw_angle_limit_high_byte = 0x00;

			SET_ENDLESS_STRUCT->check_sum = ( ~(dynamixel_id + AX_GOAL_LENGTH + AX_WRITE_DATA + AX_CCW_ANGLE_LIMIT_L) ) & 0xFF;

			//System_printf("Testing buildDynamixelStructMessage SET_ENDLESS_CMD %d \n", SET_ENDLESS_STRUCT->check_sum);
			//System_flush();

		break;

		case SET_SPEED_LEFT_CMD:

			// macro casting the buffer_struct instance see roveWare.h and roveStruct.h
			SET_DYNA_SPEED_STRUCT->start_byte1 = AX_START;
			SET_DYNA_SPEED_STRUCT->start_byte2 = AX_START;
			SET_DYNA_SPEED_STRUCT->dynamixel_id = dynamixel_id;
			SET_DYNA_SPEED_STRUCT->msg_size = AX_SPEED_LENGTH;
			SET_DYNA_SPEED_STRUCT->read_write_flag = AX_WRITE_DATA;
			SET_DYNA_SPEED_STRUCT->speed_low_byte_reg_addr = AX_GOAL_SPEED_L;
			SET_DYNA_SPEED_STRUCT->speed_low_byte = speed_low_byte;
			SET_DYNA_SPEED_STRUCT->speed_high_byte = speed_high_byte;

			SET_DYNA_SPEED_STRUCT->check_sum  = ( ~(dynamixel_id + AX_SPEED_LENGTH + AX_WRITE_DATA + AX_GOAL_SPEED_L + speed_low_byte + speed_high_byte) ) & 0xFF;

			//System_printf("Testing buildDynamixelStructMessage SET_SPEED_LEFT_CMD\n");
			//System_flush();

		break;

		case SET_SPEED_RIGHT_CMD:

			// macro casting the buffer_struct instance see roveWare.h and roveStruct.h
			SET_DYNA_SPEED_STRUCT ->start_byte1 = AX_START;
			SET_DYNA_SPEED_STRUCT ->start_byte2 = AX_START;
			SET_DYNA_SPEED_STRUCT ->dynamixel_id = dynamixel_id;
			SET_DYNA_SPEED_STRUCT ->msg_size = AX_SPEED_LENGTH;
			SET_DYNA_SPEED_STRUCT ->read_write_flag = AX_WRITE_DATA;
			SET_DYNA_SPEED_STRUCT ->speed_low_byte_reg_addr = AX_GOAL_SPEED_L;
			SET_DYNA_SPEED_STRUCT ->speed_low_byte = speed_low_byte;
			SET_DYNA_SPEED_STRUCT ->speed_high_byte = (speed_high_byte + 4);

		/*	if(command_value == 0)
			{
			    SET_DYNA_SPEED_STRUCT ->speed_high_byte = speed_high_byte;
			}
			else
			{
			    SET_DYNA_SPEED_STRUCT ->speed_high_byte = (speed_high_byte + 4);
			}
*/
			SET_DYNA_SPEED_STRUCT->check_sum = ( ~(dynamixel_id + AX_SPEED_LENGTH + AX_WRITE_DATA + AX_GOAL_SPEED_L + speed_low_byte + speed_high_byte + 4) ) & 0xFF;

			//System_printf("TestingCASE SET_SPEED_RIGHT_CMD speed_high_byte %d, speed_low_byte %d\n", SET_DYNA_SPEED_STRUCT ->speed_high_byte, SET_DYNA_SPEED_STRUCT ->speed_low_byte);
			//System_flush();

		break;

		default:

		    return;
				//System_printf("Error in function: buildDynamixelStructMessage() - struct_id is not valid\n");
				//System_flush();

		}//endswitch

	//System_printf("Testing %d speed_high_byte %d, speed_low_byte %d\n", SET_DYNA_SPEED_STRUCT ->speed_high_byte, SET_DYNA_SPEED_STRUCT ->speed_low_byte);
	//System_flush();


	//memcpy( write_buffer, buffer_struct, sizeof(set_dyna_speed_struct) );

	return;

}//end fnctn buildDynamixelStructMessage

//current_position = buildLinActuatorMessage((void*)(&buffer_struct), write_buffer, device_id, current_position, target_increment);

void buildLinActuatorStructMessage(char* write_buffer, uint8_t struct_id, int16_t speed)
{

	//System_printf("Testing buildLinActuatorStructMessage struct_id %d, \n", struct_id);
	//System_flush();

	switch(struct_id)
	{
		case SET_LIN_ACTUATOR_CMD:

		    if (speed > MAX_LIN_ACT_SPEED)
		    {
		        speed = MAX_LIN_ACT_SPEED;

		    }//endif

		    if (speed < MIN_LIN_ACT_SPEED)
		    {
		        speed = MIN_LIN_ACT_SPEED;

		    }//endif

		    SET_LIN_ACT_STRUCT->command_byte = LIN_ACT_FORWARD;

            if (speed < 0)
            {
                speed = -speed;
                SET_LIN_ACT_STRUCT->command_byte = LIN_ACT_REVERSE;

            }//endif

			SET_LIN_ACT_STRUCT->speed = (uint8_t)speed;
		break;
		default:

		    return;
			//System_printf("Error in function: buildDynamixelStructMessage() - struct_id is not valid");
			//System_flush();

	}//endswitch

	return;

}//end fnctn buildLinActuatorStructMessage


int deviceWrite(int device_port, char* write_buffer,  int bytes_to_write)
{
	int bytes_wrote;

	// give us access to the uart handles defined at the global scope in main
	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
	extern UART_Handle uart7;

	//System_printf("deviceWrite called\n");
	//System_flush();

    if(bytes_to_write < 0)
    {
        return -1;
    }//end if

	switch(device_port)
	{
		case DYNAMIXEL_UART:

			bytes_wrote = UART_write(uart4, write_buffer, bytes_to_write);

		break;
		case LINEAR_ACTUATOR_UART:

			bytes_wrote = UART_write(uart7, write_buffer, bytes_to_write);

		break;

		case END_EFFECTOR_UART:

		     bytes_wrote = UART_write(uart3, write_buffer, bytes_to_write);

		break;

		default:

		    return -1;
			//System_printf("DeviceWrite passed invalid device %d\n", device_port);
			//System_flush();

		//etc.
	}//end switch(jack)

	// make sure the message is fully written before leaving the function

	//ms_delay(1);

	return bytes_wrote;

}//endfnctn deviceWrite


void digitalWrite(int pin_number, int set_pin)
{
	//check 0 case first to optimize indexed compares
	if(set_pin == LOW)
	{
		switch(pin_number)
		{
			case SET_TRI_ST_BUF_Tx:

				GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, (0));

			break;

			default:

				//System_printf("DigitalWrite passed invalid pin %d\n", set_pin);
				//System_flush();

			return;

		}//endswitch

	}else if(set_pin == HIGH)
	{

		switch(pin_number)
		{
			case SET_TRI_ST_BUF_Tx:

				//~0 implies write without calling GPIO_PIN_3 lookup
				GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, (~0));

			break;

			default:

			//	System_printf("DigitalWrite passed invalid pin %d\n", set_pin);
			//	System_flush();

			return;

		}//endswitch

	}//endif

	return;

}//endfnctn digitalWrite


//calcCheckSum(read_buffer, rx_len);
uint8_t calcCheckSum(const char* read_buffer, uint8_t size)
{

	uint8_t check_sum = size;
	uint8_t i;

	for(i = 0; i < size; i++)
		check_sum ^= *(read_buffer + i);

	return check_sum;

}//end fnctn
