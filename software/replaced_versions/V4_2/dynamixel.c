/*dynamixel.c
 programmer: Drue
 v1 -- 2/11/15
 created on 1/22/15
 */

#include "dynamixel.h"

//Moves the dynamixel to a certain pos.
//arguments: uart address, dynamixel id, position to move to from 0 to 4095 (0xFFF) on joint mode,
//-28672 to 28672 on multi turn mode (what we use)
void dynoMove(uint32_t uart, uint8_t id, int16_t pos)
{
	uint8_t p[9];
	uint8_t posLow = pos;
	uint8_t posHigh = (pos >> 8);
	int i;
	p[0] = START_BYTE;
	p[1] = START_BYTE;
	p[2] = id;
	p[3] = MOVE_LENGTH;
	p[4] = WRITE_DATA;
	p[5] = GOAL_POS_L;
	p[6] = posLow;
	p[7] = posHigh;
	p[8] = ~(id + MOVE_LENGTH + WRITE_DATA + GOAL_POS_L + posLow + posHigh);
	switchCom(TX_MODE);

    for(i = 0; i < 9; i++)
    {
      UARTCharPut(uart, p[i]); //send the data out
    }

/*for(int i = 0; i < RETURN_PACKET_SIZE; i++)
{
  UARTCharGet(p[i]); //recieves return status packet. Reason for no delay here is so we don't accidentally delay past it's sending us data, since
}//only holds bytes and the dyno's return several bytes we could accidentally start reading halfway through

p[8] = ~(p[2] + p[3] + p[ERROR_SLOT]) //using p[8] as storage for checking off the checksum. p2 holds ID and p3 holds length, CS = ID + L + Error +         parameters (none here)
if((p[ERROR_SLOT]) || (p[8] != p[6]))
    printf("error");
*/
}


//changes the dynamixel's moving speed
//arguments: uart hardware address, dynamixel id, speed to use from 0 to 2047 (0x7FF)
/*Wheel Mode:
0~2047( 0X7FF) can be used, the unit is about 0.1%.
If a value in the range of 0~1023 is used, it is stopped by setting to 0 while rotating to CCW direction.
If a value in the range of 1024~2047 is used, it is stopped by setting to 1024 while rotating to CW direction.
That is, the 10th bit becomes the direction bit to control the direction.
In Wheel Mode, only the output control is possible, not speed.
For example, if it is set to 512, it means the output is controlled by 50% of the maximum output.*/
void dynoSpeedSet(uint32_t uart, uint8_t id, uint16_t speed)
{
    uint8_t p[9];
    uint8_t speedLow = speed;
    uint8_t speedHigh = (speed >> 8);
    int i;
    p[0] = START_BYTE;
    p[1] = START_BYTE;
    p[2] = id;
    p[3] = 0x05;
    p[4] = WRITE_DATA;
    p[5] = MOVING_SPEED_L;
    p[6] = speedLow;
    p[7] = speedHigh;
    p[8] = ~(id + 0x05 + WRITE_DATA +MOVING_SPEED_L + speedLow + speedHigh);

    for(i = 0; i < 9; i++)
    {
        UARTCharPut(uart, p[i]); //send the data out
    }

    //readError();
}

void dynoMultiModeSet(uint32_t uart, uint8_t id)
{
	uint8_t p[11];
	int i;
	p[0] = START_BYTE;
	p[1] = START_BYTE;
	p[2] = id;
	p[3] = 0x07;
	p[4] = WRITE_DATA;
	p[5] = CW_ANGLE_LIMIT_L;
	p[6] = 0xFF;
	p[7] = 0x0F;
	p[8] = 0xFF;
	p[9] = 0x0F;
	p[10] = ~(id + 0x07 + WRITE_DATA + 0xFF + 0x0F + 0xFF + 0x0F +  CW_ANGLE_LIMIT_L);

	for(i = 0; i < 11; i++)
	{
	  UARTCharPut(uart, p[i]); //send the data out
	}

	//readError();
}


void dynoWheelModeSet(uint32_t uart, uint8_t id)
{
    uint8_t p[11];
    int i;
    p[0] = START_BYTE;
    p[1] = START_BYTE;
    p[2] = id;
    p[3] = 0x07;
    p[4] = WRITE_DATA;
    p[5] = CW_ANGLE_LIMIT_L;
    p[6] = 0x00;
    p[7] = 0x00;
    p[8] = 0x00;
    p[9] = 0x00;
    p[10] = ~(id + 0x07 + WRITE_DATA + 0x00 + 0x00 + 0x00 + 0x00 +  CW_ANGLE_LIMIT_L);

    for(i = 0; i < 11; i++)
    {
      UARTCharPut(uart, p[i]); //send the data out
    }

    //readError();

}

void switchCom(bool i)
{
	if(i)
		GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, GPIO_PIN_3);
	else
		GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0);
}


int16_t dynoReadPosition(uint32_t uart, uint8_t id)
{
	clearRxBuffer(uart);

	uint8_t p[8], posLow, posHigh, incoming_byte, i, timer = 0;
	int16_t pos = POS_FALSE_READ;
	p[0] = START_BYTE;
	p[1] = START_BYTE;
	p[2] = id;
	p[3] = READ_LEN;
	p[4] = READ_DATA;
	p[5] = CURRENT_POSITION_L;
	p[6] = 0x02; //read 2 bytes
	p[7] = ~(id + READ_LEN + READ_DATA + CURRENT_POSITION_L + 0x02);

	for(i = 0; i < 8; i++)
	{
	  UARTCharPut(uart, p[i]); //send the data out
	}

	switchCom(RX_MODE);
	delay(DELAY);
	//reads the data

	while(!(UARTCharsAvail(uart)) & (timer < TIME_OUT)) //waits until a byte is recieved or timed out
	{
		timer++;
		delay(1000);
	}

	if(!UARTCharsAvail(uart)) //if nothing transmitted, return false
		return(POS_FALSE_READ);

	delay(DELAY);
	incoming_byte = UARTCharGetNonBlocking(uart);
	if (incoming_byte == START_BYTE)
	{
		UARTCharGet(uart);                            // Start Bytes
		UARTCharGet(uart);                              //  ID
		UARTCharGet(uart);                             // Length
		if((error_byte = UARTCharGet(uart)) != 0 )   // Error byte
		{
			return(POS_FALSE_READ);
		}
		posLow = UARTCharGet(uart);            // Position Bytes
		posHigh = UARTCharGet(uart);
		pos = posHigh << 8;
		pos |= posLow;
	}
	return (pos);     // Returns the read position

}


void clearRxBuffer(uint32_t uart)
{
	while(UARTCharGetNonBlocking(uart))
	{
	}
}