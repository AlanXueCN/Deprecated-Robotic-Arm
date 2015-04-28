/*
 * hardwareAbstraction.c
 *
 *  Created on: Apr 27, 2015
 *      Author: mrdtdev
 */

#include "../roveWareHeaders/roveHardwareAbstraction.h"


// roveHardwareAbstraction
//
// first created:
//
// 01_22_2015_Owen_Chiaventone omc8db
//
// last edited:
//
// 02_24_2015_Judah Schad_jrs6w7@mst.edu

#include "../roveWareHeaders/roveHardwareAbstraction.h"

//TODO Configure Patch Panel Jacks to Physical Devices (In Hardware FIRST)

int getDeviceJack(int device_id){

	switch(device_id){
		case 0:
				//Tried to get jack for an null device
				System_printf("getDeviceJack passed null device %d\n", device);
				System_flush();
			return -1;

		case test_device_id:

			return ONBOARD_ROVECOMM;

		case motor_left_id:

			return ONBOARD_ROVECOMM;

		case bms_emergency_stop_command_id ... bms_total_amperage_telem_id:
			return ONBOARD_ROVECOMM;

		case power_board_command_id ... power_board_telem_main_battery_voltage_id:
			return POWER_BOARD;

		default:
				//Tried to get jack for an \ invalid device
				System_printf("getDeviceJack passed invalid device %d\n", device);
				System_flush();
			return -1;

	}//endswitch (device)

}//endfnctn deviceJack



void digitalWrite(int pin, int val){

	//Alarmingly enough, a switch case is really the only way to deal with this
	//Everything is base on a bunch of TI defined constants that can't be indexed into
	//Or iterated through

	if(val == LOW){

		switch(pin){

			case DATA_FLOW_CTRL_1 :
				GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, (0));
				break;

			default:
						//Tried to write to invalid device
						System_printf("DigitalWrite passed invalid pin %d\n", pin);
						System_flush();
				return;
		}//endswitch

	}else if (val == HIGH){

		switch(pin){

			case DATA_FLOW_CTRL_1 :
				GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, (~0));
				break;

			default:
						//Tried to write to invalid device
						System_printf("DigitalWrite passed invalid pin %d\n", pin);
						System_flush();
					return;

		}//endswitch

	}//endif

	return;

}//endfnctn digitalWrite


int deviceWrite(int rs485jack, char* buffer, int bytes_to_write){

/*	int bytes_wrote;

	// give us access to the uart handles defined at the global scope in main

	extern UART_Handle uart0;
	extern UART_Handle uart1;
	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
	extern UART_Handle uart5;
	extern UART_Handle uart6;
	extern UART_Handle uart7;

					//System_printf("deviceWrite called\n");
					//System_flush();

	switch(rs485jack){

		// we have to include case 0 to get TI's compiler to build a jump table
		// if we leave this out, mux performance goes from O(1) to O(n) (That's bad)
		case 0:
		break;
		case 1:
			// configure the mux pins, see the mux datasheet for more info
			digitalWrite(U3_MUX_S0, HIGH);
			digitalWrite(U3_MUX_S1, HIGH);
			// write the buffer to the device
			bytes_wrote = UART_write(uart3, buffer, bytes_to_write);
			break;
		case 2:
			digitalWrite(U3_MUX_S0, LOW);
			digitalWrite(U3_MUX_S1, HIGH);
			bytes_wrote = UART_write(uart3, buffer, bytes_to_write);
			break;
		case 3:
			digitalWrite(U3_MUX_S0, HIGH);
			digitalWrite(U3_MUX_S1, LOW);
			bytes_wrote = UART_write(uart3, buffer, bytes_to_write);
			break;
		case 4:
			digitalWrite(U6_MUX_S0, LOW);
			digitalWrite(U6_MUX_S1, HIGH);
			bytes_wrote = UART_write(uart6, buffer, bytes_to_write);
			break;
		case 5:
			digitalWrite(U6_MUX_S0, HIGH);
			digitalWrite(U6_MUX_S1, LOW);
			bytes_wrote = UART_write(uart6, buffer, bytes_to_write);
			break;
		case 6:
			digitalWrite(U7_MUX_S0, HIGH);
			digitalWrite(U7_MUX_S1, HIGH);
			bytes_wrote = UART_write(uart7, buffer, bytes_to_write);
			break;
		case 7:
			digitalWrite(U7_MUX_S0, LOW);
			digitalWrite(U7_MUX_S1, HIGH);
			bytes_wrote = UART_write(uart7, buffer, bytes_to_write);
			break;
		case 8:
			digitalWrite(U7_MUX_S0, HIGH);
			digitalWrite(U7_MUX_S1, LOW);
			bytes_wrote = UART_write(uart7, buffer, bytes_to_write);
			break;
		case 9:
			digitalWrite(U5_MUX_S0, LOW);
			digitalWrite(U5_MUX_S1, LOW);
			bytes_wrote = UART_write(uart5, buffer, bytes_to_write);
			break;
		case 10:
			digitalWrite(U5_MUX_S0, LOW);
			digitalWrite(U5_MUX_S1, HIGH);
			bytes_wrote = UART_write(uart5, buffer, bytes_to_write);
			break;
		case 11:
			digitalWrite(U5_MUX_S0, HIGH);
			digitalWrite(U5_MUX_S1, LOW);
			bytes_wrote = UART_write(uart5, buffer, bytes_to_write);
			break;
		case 12:
			digitalWrite(U5_MUX_S0, LOW);
			digitalWrite(U5_MUX_S1, LOW);
			bytes_wrote = UART_write(uart5, buffer, bytes_to_write);
			break;
		case 13:
			digitalWrite(U5_MUX_S0, HIGH);
			digitalWrite(U5_MUX_S1, HIGH);
			bytes_wrote = UART_write(uart5, buffer, bytes_to_write);
			break;
		case 14:
			digitalWrite(U4_MUX_S0, LOW);
			digitalWrite(U4_MUX_S1, LOW);
			bytes_wrote = UART_write(uart4, buffer, bytes_to_write);
			break;
		case 15:
			digitalWrite(U4_MUX_S0, LOW);
			digitalWrite(U4_MUX_S1, HIGH);
			bytes_wrote = UART_write(uart4, buffer, bytes_to_write);
			break;
		case 16:
			digitalWrite(U4_MUX_S0, HIGH);
			digitalWrite(U4_MUX_S1, HIGH);
			bytes_wrote = UART_write(uart4, buffer, bytes_to_write);
			break;
		case 17:
			digitalWrite(U4_MUX_S0, HIGH);
			digitalWrite(U4_MUX_S1, LOW);
			bytes_wrote = UART_write(uart4, buffer, bytes_to_write);
			break;
		case POWER_BOARD:
			digitalWrite(U6_MUX_S0, HIGH);
			digitalWrite(U6_MUX_S1, HIGH);
			bytes_wrote = UART_write(uart6, buffer, bytes_to_write);
			break;
		case ONBOARD_ROVECOMM:
			bytes_wrote = UART_write(uart2, buffer, bytes_to_write);
			break;
		default:
			//Tried to write to invalid device
			System_printf("DeviceWrite passed invalid device %d\n", rs485jack);
			System_flush();
			return -1;
		//etc.

	}//end switch(rs485jack)

	// make sure the message is fully written before leaving the function

	ms_delay(1);

	return bytes_wrote;
*/
}//endfnctn deviceWrite

int deviceRead(int rs485jack, char* buffer, int bytes_to_read, int timeout){
/*
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
*/
}//endfnctn deviceRead
