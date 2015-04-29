// hardwareAbstraction.c 2015

//the roveWare / texas instruments interface lib

#include "../roveWareHeaders/roveHardwareAbstraction.h"

//see roveStructs.h and rovWare.h for config
void buildDynamixelStructMessage(void* dynamixel_struct, uint8_t dynamixel_id, uint16_t command_value)
{
	uint8_t check_sum;
	uint8_t speed_low_byte = (uint8_t)command_value;
	uint8_t speed_high_byte = (uint8_t)(command_value >> 8);

	switch( ( (struct dynamixel_id_cast*)dynamixel_struct)->struct_id)
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

		case SET_SPEED_CMD:

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

		case SET_ACTUATOR_CMD:

			//target = current + command
			((struct linear_actuator_struct*)dynamixel_struct)->target_position =
			(command_value + ( (struct linear_actuator_struct*)dynamixel_struct)->current_position);

			if ((((struct linear_actuator_struct*)dynamixel_struct)->target_position) > MAX_LIN_ACT_POSITION )
			{
				((struct linear_actuator_struct*)dynamixel_struct)->target_position = MAX_LIN_ACT_POSITION;

			}//endif

			if ((((struct linear_actuator_struct*)dynamixel_struct)->target_position) < MIN_LIN_ACT_POSITION )
			{
				((struct linear_actuator_struct*)dynamixel_struct)->target_position = MIN_LIN_ACT_POSITION;

			}//endif

			((struct linear_actuator_struct*)dynamixel_struct)->current_position =
					((struct linear_actuator_struct*)dynamixel_struct)->target_position;

			//target_low_byte = 0xC0 + (target + 0x1F)
			((struct linear_actuator_struct*)dynamixel_struct)->target_low_byte =
			(uint8_t)( 0xC0 + (( ((struct linear_actuator_struct*)dynamixel_struct)->target_position)& 0x1F) );

			//target_high_byte =
			((struct linear_actuator_struct*)dynamixel_struct)->target_high_byte =
			(uint8_t)( ((((struct linear_actuator_struct*)dynamixel_struct)->target_position) >> 5)& 0x7F);

			System_printf("SET_ACTUATOR_CMD() target_position %d/n",
				((struct linear_actuator_struct*)dynamixel_struct)->target_position);

			System_printf("SET_ACTUATOR_CMD() target_low_byte %d/n",
				((struct linear_actuator_struct*)dynamixel_struct)->target_low_byte);

			System_printf("SET_ACTUATOR_CMD() target_high_byte %d/n",
				((struct linear_actuator_struct*)dynamixel_struct)->target_high_byte);
			System_flush();

		break;

		default:

				System_printf("Error in function: buildDynamixelStructMessage() - struct_id is not valid");
				System_flush();



		break;

		}//endswitch

}//end fnctn buildSerialStructMessage


//see roveStructs.h and rovWare.h for config
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

				System_printf("DigitalWrite passed invalid pin %d\n", pin);
				System_flush();

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

				System_printf("DigitalWrite passed invalid pin %d\n", pin);
				System_flush();

			return;

		}//endswitch

	}//endif

	return;

}//endfnctn digitalWrite

//see roveStructs.h and rovWare.h for config
int deviceWrite(int device_port, char* buffer, int bytes_to_write)
{
	int bytes_wrote;

	// give us access to the uart handles defined at the global scope in main
	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
	extern UART_Handle uart7;

	System_printf("deviceWrite called\n");
	System_flush();

	switch(device_port)
	{
		// we have to include case 0 to get TI's compiler to build a jump table
		// if we leave this out, mux performance goes from O(1) to O(n) (That's bad)
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

//see roveStructs.h and rovWare.h for config
int getDevicePort(uint8_t device_id)
{
	switch(device_id)
	{
		case WRIST_A_ID...BASE_ID:

		return DYNAMIXEL_UART;

		case LIN_ACT_ID:

		return LINEAR_ACTUATOR_UART;

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

		case SET_SPEED_CMD:

			return sizeof(struct set_speed_struct);

		case SET_ACTUATOR_CMD:

			return (sizeof(struct linear_actuator_struct) - LIN_DONT_PRINT_BYTES);

		default:

			System_printf("getStructSize passed invalid struct_id %d\n", struct_id);
			System_flush();

		return -1;

	}//endswitch

}//endfnctn getDevicePort

/*

Todo recieve

int deviceRead(int rs485jack, char* buffer, int bytes_to_read, int timeout){

	int bytes_read;

	// give us access to the uart handles defined at the global scope in main

	extern UART_Handle uart0;
	extern UART_Handle uart1;
	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
	extern UART_Handle uart5;
	extern UART_Handle uart6;
	extern UART_Handle uart7;

	// we have to include case 0 to get TI's compiler to build a jump table
	// if we leave this out, mux performance goes from O(1) to O(n) (That's bad)
	switch(rs485jack){
		case 0:
		case 1:
			//Configure the mux pins
			//See the mux datasheet for more info
			digitalWrite(U3_MUX_S0, HIGH);
			digitalWrite(U3_MUX_S1, HIGH);

			//Write the buffer to the device
			bytes_read = UART_read(uart3, buffer, bytes_to_read);
			break;
		case 2:
			digitalWrite(U3_MUX_S0, LOW);
			digitalWrite(U3_MUX_S1, HIGH);
			bytes_read = UART_read(uart3, buffer, bytes_to_read);
			break;
		case 3:
			digitalWrite(U3_MUX_S0, HIGH);
			digitalWrite(U3_MUX_S1, LOW);
			bytes_read = UART_read(uart3, buffer, bytes_to_read);
			break;
		case 4:
			digitalWrite(U6_MUX_S0, LOW);
			digitalWrite(U6_MUX_S1, HIGH);
			bytes_read = UART_read(uart6, buffer, bytes_to_read);
			break;
		case 5:
			digitalWrite(U6_MUX_S0, HIGH);
			digitalWrite(U6_MUX_S1, LOW);
			bytes_read = UART_read(uart6, buffer, bytes_to_read);
			break;
		case 6:
			digitalWrite(U7_MUX_S0, HIGH);
			digitalWrite(U7_MUX_S1, HIGH);
			bytes_read = UART_read(uart7, buffer, bytes_to_read);
			break;
		case 7:
			digitalWrite(U7_MUX_S0, LOW);
			digitalWrite(U7_MUX_S1, HIGH);
			bytes_read = UART_read(uart7, buffer, bytes_to_read);
			break;
		case 8:
			digitalWrite(U7_MUX_S0, HIGH);
			digitalWrite(U7_MUX_S1, LOW);
			bytes_read = UART_read(uart7, buffer, bytes_to_read);
			break;
		case 9:
			digitalWrite(U5_MUX_S0, LOW);
			digitalWrite(U5_MUX_S1, LOW);
			bytes_read = UART_read(uart5, buffer, bytes_to_read);
			break;
		case 10:
			digitalWrite(U5_MUX_S0, LOW);
			digitalWrite(U5_MUX_S1, HIGH);
			bytes_read = UART_read(uart5, buffer, bytes_to_read);
			break;
		case 11:
			digitalWrite(U5_MUX_S0, HIGH);
			digitalWrite(U5_MUX_S1, LOW);
			bytes_read = UART_read(uart5, buffer, bytes_to_read);
			break;
		case 12:
			digitalWrite(U5_MUX_S0, LOW);
			digitalWrite(U5_MUX_S1, LOW);
			bytes_read = UART_read(uart5, buffer, bytes_to_read);
			break;
		case 13:
			digitalWrite(U5_MUX_S0, HIGH);
			digitalWrite(U5_MUX_S1, HIGH);
			bytes_read = UART_read(uart5, buffer, bytes_to_read);
			break;
		case 14:
			digitalWrite(U4_MUX_S0, LOW);
			digitalWrite(U4_MUX_S1, LOW);
			bytes_read = UART_read(uart4, buffer, bytes_to_read);
			break;
		case 15:
			digitalWrite(U4_MUX_S0, LOW);
			digitalWrite(U4_MUX_S1, HIGH);
			bytes_read = UART_read(uart4, buffer, bytes_to_read);
			break;
		case 16:
			digitalWrite(U4_MUX_S0, HIGH);
			digitalWrite(U4_MUX_S1, HIGH);
			bytes_read = UART_read(uart4, buffer, bytes_to_read);
			break;
		case 17:
			digitalWrite(U4_MUX_S0, HIGH);
			digitalWrite(U4_MUX_S1, LOW);
			bytes_read = UART_read(uart4, buffer, bytes_to_read);
			break;
		case POWER_BOARD:
			digitalWrite(U6_MUX_S0, HIGH);
			digitalWrite(U6_MUX_S1, HIGH);
			bytes_read = UART_read(uart6, buffer, bytes_to_read);
			break;
		case ONBOARD_ROVECOMM:
			bytes_read = UART_read(uart2, buffer, bytes_to_read);
			break;
		default:
			//Tried to write to invalid device
			System_printf("DeviceWrite passed invalid device %d\n", rs485jack);
			System_flush();
			return -1;
		//etc.

	}//endswitch(rs485jack)

	return bytes_read;

}//endfnctn deviceRead

uint8_t calcCheckSum(const void* my_struct, uint8_t size){

	uint8_t checkSum = size;
	uint8_t i;

	for(i = 0; i < size; i++)
		checkSum ^= *((char*)my_struct + i);

	return checkSum;

}//end fnctn



*/
