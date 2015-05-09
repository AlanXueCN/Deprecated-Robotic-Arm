// dynamixel.c 2015

#include "../roveWareHeaders/roveDynamixel.h"

//This is where the function library porting goes:

//int DynamixelClass::setEndless(unsigned char ID, bool Status)

//Runtime Command to turn on and off endless rotation ( maaaybeee feeels a bit liiike Open Loop emulation)

void dynamixelSetEndlessCmd(uint8_t dynamixel_id)
{
		char write_buffer[BUFFER_SIZE];

		int device_port;
		int bytes_to_write;
		int bytes_wrote;

		//_printf("Testing dynamixelSetEndlessCmd dynamixel_id %d\n", dynamixel_id);
		//_flush();

		// get the uart
		device_port = getDevicePort(dynamixel_id);

		// size of message
		bytes_to_write = getStructSize(SET_ENDLESS_CMD);

		// populate the buffer_struct for dynamixel format frame, command_value not used
		buildDynamixelStructMessage(write_buffer, dynamixel_id, SET_ENDLESS_CMD, NULL_COMAND_VALUE);

		// set tristate buffer to transmit
		//digitalWrite(SET_TRI_ST_BUF_Tx, HIGH);

		bytes_wrote = deviceWrite(device_port, write_buffer, bytes_to_write);

		ms_delay(1);

		//debugging only:
		//_printf("dynamixelSetEndlessCmd just wrote: \n");
		//int i = 0;
		//while( i <( bytes_wrote ) )
		//{
		//	System_printf(" : %d\n", write_buffer[i]);
		//	System_flush();
//
		//	i++;
		//}//end while

		// set tri state buffer back for read
		//digitalWrite(SET_TRI_ST_BUF_Tx, LOW);

}//endfnctn  dynamixelSetEndless


void dynamixelSetSpeedLeftCmd(uint8_t dynamixel_id, int16_t speed)
{
		char write_buffer[BUFFER_SIZE];

		int device_port;
		int bytes_to_write;
		int bytes_wrote;

		//_printf("Testing dynamixelSetSpeedLeftCmd dynamixel_id %d, speed %d\n", dynamixel_id, speed);
		//_flush();

		//get the uart
		device_port = getDevicePort(dynamixel_id);

		//size of message
		bytes_to_write = getStructSize(SET_SPEED_LEFT_CMD);

		// set tristate buffer to transmit
		//digitalWrite(SET_TRI_ST_BUF_Tx, HIGH);

		// populate the buffer_struct for dynamixel format frame
		buildDynamixelStructMessage(write_buffer, dynamixel_id, SET_SPEED_LEFT_CMD, speed);

		bytes_wrote = deviceWrite(device_port, write_buffer, bytes_to_write);

		ms_delay(1);

		//debugging only
		//_printf("dynamixelSetSpeedLeftCmd just wrote: \n");
		//int i = 0;
		//while( i <( bytes_wrote ) )
		//{
			//_printf(" : %d\n", write_buffer[i]);
			//_flush();

		//	i++;
		//}//end while

		//set tri state buffer back for read
		//digitalWrite(SET_TRI_ST_BUF_Tx, LOW);

}//endfnctn  dynamixelSetSpeedLeftCmd

void dynamixelSetSpeedRightCmd(uint8_t dynamixel_id, int16_t speed)
{
		char write_buffer[BUFFER_SIZE];

		int device_port;
		int bytes_to_write;
		int bytes_wrote;

		//System_printf("Testing dynamixelSetSpeedRightCmd dynamixel_id %d, speed %d\n", dynamixel_id, speed);
		//System_flush();

		//get the uart
		device_port = getDevicePort(dynamixel_id);

		//size of message
		bytes_to_write = getStructSize(SET_SPEED_RIGHT_CMD);

		// set tristate buffer to transmit
		//digitalWrite(SET_TRI_ST_BUF_Tx, HIGH);

		// populate the buffer_struct for dynamixel format frame
		buildDynamixelStructMessage(write_buffer, dynamixel_id, SET_SPEED_RIGHT_CMD, speed);

		bytes_wrote = deviceWrite(device_port, write_buffer, bytes_to_write);

		ms_delay(1);

		//debugging only
		//_printf("dynamixelSetSpeedRightCmd just wrote: \n");
		//int i = 0;
		//while( i <( bytes_wrote ) )
		//{
			//_printf(" : %d\n", write_buffer[i]);
			//_flush();

		//	i++;
		//}//end while

		//set tri state buffer back for read
		//digitalWrite(SET_TRI_ST_BUF_Tx, LOW);

}//endfnctn  dynamixelSetSpeedRightCmd


void setLinActuatorCmd(uint8_t device_id, int16_t speed)
{
	    char write_buffer[BUFFER_SIZE];

		int device_port;
		int bytes_to_write;
		int bytes_wrote;

		//_printf("Testing setLinActuatorCmd dynamixel_id %d, current_position %d, target_increment %d\n"
						//, device_id, current_position, target_increment);
		//_flush();

		// get the uart
		device_port = getDevicePort(device_id);

		// size of message
		bytes_to_write = getStructSize(SET_LIN_ACTUATOR_CMD);

		// populate the buffer_struct for dynamixel format frame
		buildLinActuatorStructMessage(write_buffer, SET_LIN_ACTUATOR_CMD, speed);

		bytes_wrote = deviceWrite(device_port, write_buffer, bytes_to_write);

		ms_delay(1);

		//debugging only
		//_printf("dynamixelSetSpeedRightCmd just wrote: \n");
		//int i = 0;
		//while( i <( bytes_wrote ) )
		//{
			//_printf(" : %d\n", write_buffer[i]);
			//_flush();

		//	i++;
		//}//end while

		return;

}//endfnctn  setActuatorCmd

//Todo Functions to Add

////Todo Judah Savage Electronics port lib

/*

//Send Runtime direction and speed (one to one preceding dynamixelSetEndlessCmd Command

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



//ask for torque

int DynamixelClass::torqueStatus( unsigned char ID, bool Status)
{
    Checksum = (~(ID + AX_TORQUE_LENGTH + AX_WRITE_DATA + AX_TORQUE_ENABLE + Status))&0xFF;

	switchCom(Direction_Pin,Tx_MODE);
    sendData(AX_START);              // Send Instructions over Serial
    sendData(AX_START);
    sendData(ID);
    sendData(AX_TORQUE_LENGTH);
    sendData(AX_WRITE_DATA);
    sendData(AX_TORQUE_ENABLE);
    sendData(Status);
    sendData(Checksum);
    delayus(TX_DELAY_TIME);
	switchCom(Direction_Pin,Rx_MODE);

    return (read_error());              // Return the read error
}



//read position

int DynamixelClass::readPosition(unsigned char ID)
{
    Checksum = (~(ID + AX_POS_LENGTH  + AX_READ_DATA + AX_PRESENT_POSITION_L + AX_BYTE_READ_POS))&0xFF;

	switchCom(Direction_Pin,Tx_MODE);
    sendData(AX_START);
    sendData(AX_START);
    sendData(ID);
    sendData(AX_POS_LENGTH);
    sendData(AX_READ_DATA);
    sendData(AX_PRESENT_POSITION_L);
    sendData(AX_BYTE_READ_POS);
    sendData(Checksum);
    delayus(TX_DELAY_TIME);
	switchCom(Direction_Pin,Rx_MODE);

    Position_Long_Byte = -1;
	Time_Counter = 0;
    while((availableData() < 7) & (Time_Counter < TIME_OUT)){
		Time_Counter++;
		delayus(1000);
    }

    while (availableData() > 0){
		Incoming_Byte = readData();
		if ( (Incoming_Byte == 255) & (peekData() == 255) ){
			readData();                            // Start Bytes
			readData();                            // Ax-12 ID
			readData();                            // Length
			if( (Error_Byte = readData()) != 0 )   // Error
				return (Error_Byte*(-1));

			Position_Low_Byte = readData();            // Position Bytes
			Position_High_Byte = readData();
			Position_Long_Byte = Position_High_Byte << 8;
			Position_Long_Byte = Position_Long_Byte + Position_Low_Byte;
		}
    }
	return (Position_Long_Byte);     // Returns the read position
}



//read speed

int DynamixelClass::readSpeed(unsigned char ID)
{
    Checksum = (~(ID + AX_POS_LENGTH  + AX_READ_DATA + AX_PRESENT_SPEED_L + AX_BYTE_READ_POS))&0xFF;

	switchCom(Direction_Pin,Tx_MODE);
    sendData(AX_START);
    sendData(AX_START);
    sendData(ID);
    sendData(AX_POS_LENGTH);
    sendData(AX_READ_DATA);
    sendData(AX_PRESENT_SPEED_L);
    sendData(AX_BYTE_READ_POS);
    sendData(Checksum);
    delayus(TX_DELAY_TIME);
	switchCom(Direction_Pin,Rx_MODE);

    Speed_Long_Byte = -1;
	Time_Counter = 0;
    while((availableData() < 7) & (Time_Counter < TIME_OUT)){
		Time_Counter++;
		delayus(1000);
    }

    while (availableData() > 0){
		Incoming_Byte = readData();
		if ( (Incoming_Byte == 255) & (peekData() == 255) ){
			readData();                            // Start Bytes
			readData();                            // Ax-12 ID
			readData();                            // Length
			if( (Error_Byte = readData()) != 0 )   // Error
				return (Error_Byte*(-1));

			Speed_Low_Byte = readData();            // Position Bytes
			Speed_High_Byte = readData();
			Speed_Long_Byte = Speed_High_Byte << 8;
			Speed_Long_Byte = Speed_Long_Byte + Speed_Low_Byte;
		}
    }
	return (Speed_Long_Byte);     // Returns the read position
}



//read load

int DynamixelClass::readLoad(unsigned char ID)
{
    Checksum = (~(ID + AX_POS_LENGTH  + AX_READ_DATA + AX_PRESENT_LOAD_L + AX_BYTE_READ_POS))&0xFF;

	switchCom(Direction_Pin,Tx_MODE);
    sendData(AX_START);
    sendData(AX_START);
    sendData(ID);
    sendData(AX_POS_LENGTH);
    sendData(AX_READ_DATA);
    sendData(AX_PRESENT_LOAD_L);
    sendData(AX_BYTE_READ_POS);
    sendData(Checksum);
    delayus(TX_DELAY_TIME);
	switchCom(Direction_Pin,Rx_MODE);

    Load_Long_Byte = -1;
	Time_Counter = 0;
    while((availableData() < 7) & (Time_Counter < TIME_OUT)){
		Time_Counter++;
		delayus(1000);
    }

    while (availableData() > 0){
		Incoming_Byte = readData();
		if ( (Incoming_Byte == 255) & (peekData() == 255) ){
			readData();                            // Start Bytes
			readData();                            // Ax-12 ID
			readData();                            // Length
			if( (Error_Byte = readData()) != 0 )   // Error
				return (Error_Byte*(-1));

			Load_Low_Byte = readData();            // Position Bytes
			Load_High_Byte = readData();
			Load_Long_Byte = Load_High_Byte << 8;
			Load_Long_Byte = Load_Long_Byte + Load_Low_Byte;
		}
    }
	return (Load_Long_Byte);     // Returns the read position
}


//read volts

int DynamixelClass::readVoltage(unsigned char ID)
{
    Checksum = (~(ID + AX_VOLT_LENGTH  + AX_READ_DATA + AX_PRESENT_VOLTAGE + AX_BYTE_READ))&0xFF;

	switchCom(Direction_Pin,Tx_MODE);
    sendData(AX_START);
    sendData(AX_START);
    sendData(ID);
    sendData(AX_VOLT_LENGTH);
    sendData(AX_READ_DATA);
    sendData(AX_PRESENT_VOLTAGE);
    sendData(AX_BYTE_READ);
    sendData(Checksum);
	delayus(TX_DELAY_TIME);
	switchCom(Direction_Pin,Rx_MODE);

    Voltage_Byte = -1;
	Time_Counter = 0;
    while((availableData() < 6) & (Time_Counter < TIME_OUT)){
		Time_Counter++;
		delayus(1000);
    }

    while (availableData() > 0){
		Incoming_Byte = readData();
		if ( (Incoming_Byte == 255) & (peekData() == 255) ){
			readData();                            // Start Bytes
			readData();                            // Ax-12 ID
			readData();                            // Length
			if( (Error_Byte = readData()) != 0 )   // Error
				return (Error_Byte*(-1));
			Voltage_Byte = readData();             // Voltage
		}
    }
	return (Voltage_Byte);               // Returns the read Voltage
}


////Todo Owen roveWare wrapper lib

//

/*void dynamixelWrite(UART_Handle uart, uint8_t* data_buffer)
{

	return;
}


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
