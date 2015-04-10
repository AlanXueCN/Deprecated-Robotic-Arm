//ArmMainV4_3.c
//created by: drue and alec
//created on 4-10-15
//updated:
//
//
//RoveSoHard


#include "armMainV4_3.h"

/* Here we control the arm movement for the rover. The overhead process goes: our arm waits in place until the user pushes
 * a button/moves a joystick/ whatever or they want to move the endefector, which is directed through
 * the arm board. They send the signal to motherboard who then sends it to us in the form of
 * either the arm_data_control struct, found in struct_xfer.h, or the 2 endefector structs, gripper_control_struct
 * and drill_Controls struct. We stay in a loop where we constantly check with the
 * recv_struct function if motherboard is sending us any data; when they do, we read what struct they're sending
 * and, if it's an arm command, read what variables have been set. and have the arm move accordingly by calling the movement functions.
 * Simple enough; they command, we get commands, we have arm move accordingly. If it's an endefector command, we merely
 * pass it along.
 *
 * Inside the move functions themselves, we either a) move the actuator using the motor control function
 *
 * b) Move the dynamixels. At the moment, this is done by using the dynoMove function as described in dynamixel.h to
 * command it to move to an DYNAMIXEL_INCed position. We do this by DYNAMIXEL_INCing its position variable and then passing the
 * dynoMove function the newly DYNAMIXEL_INCed variable. The position variables are to keep track of the arm's position at all
 * times, and the arm's movement is based off of DYNAMIXEL_INCing the position variables for every movement.
 *
 * Currently there is no usage for the dynamixel's closed loop abilities, though functions exist to read certain values from
 * them they are untested as of 2-11-15
 *
 */

int16_t wristVertPos = 0;
int16_t elbowVertPos = 0;
int16_t wristClockwisePos = 0;
int16_t elbowClockwisePos = 0;
int16_t wristDyno1Pos, wristDyno2Pos, elbowDyno1Pos, elbowDyno2Pos, basePos;
uint16_t actuatorPos;

void main(void)
{

	struct arm_control_struct armData;
	struct gripper_control_struct gripperData;
	struct drill_Controls drillData;
	receiveStruct receiveData;
	resetStruct(&receiveData, RECEIVE_STRUCT_SIZE);

	initHardware();

    //initPositions(&wristVertPos, &wristClockwisePos, &elbowVertPos, &elbowClockwisePose, &basePos, &actuatorPos);
   // delay(DELAY);


    //while(1)
	//{
		 /* UARTCharPut(UART_DYNAMIXEL, 0xFF);
		  UARTCharPut(UART_DYNAMIXEL, 0xFF);
		  UARTCharPut(UART_DYNAMIXEL, GLOBAL_ID); //id
		  UARTCharPut(UART_DYNAMIXEL, 0x04); //Id_length
		  UARTCharPut(UART_DYNAMIXEL, 0x03); //write data
		  UARTCharPut(UART_DYNAMIXEL, 0x03); //ID_register
		  UARTCharPut(UART_DYNAMIXEL, 0x04); //idEnd
		  UARTCharPut(UART_DYNAMIXEL, ~(GLOBAL_ID + 0x04 + 0x03 + 0x03 + 0x04)&0xFF);
    	  delay(10);*/
    	//dynoSetID(UART_DYNAMIXEL, GLOBAL_ID, 0x08);
        //dynoWheelModeSet(UART_DYNAMIXEL, GLOBAL_ID);
    	//dynoSpeedSet(UART_DYNAMIXEL, GLOBAL_ID, 0x1000);
    	//send_struct(UART_ENDE, &gripperData, INST_OTHER, GRIPPER_STRUCT_ID);
		//dynoMove(UART_DYNAMIXEL, GLOBAL_ID, 0x00);
		//for(i = 0; i < 500000; i++);
		//delay(25);
		//dynoMove(UART_DYNAMIXEL, GLOBAL_ID, 0x00);
		//for(i = 0; i < 500000; i++);
		//delay(25);
		//delay(150);
		/*dynoMove(UART_DYNAMIXEL, 2, 0x00);
		delay(50);
		dynoMove(UART_DYNAMIXEL, 2, 4000);
		delay(50);
		dynoMove(UART_DYNAMIXEL, 1, 0x00);
		delay(50);
		dynoMove(UART_DYNAMIXEL, 1, 4000);
		delay(50);*/
	//}
	while(1)
	{

		if(recv_struct(UART_MOTHER, &receiveData))
		{
			delay(1);
			switch(receiveData.id)
			{
			case ARM_STRUCT_ID:
				memcpy(&armData, &receiveData, receiveData.size);

				if(armData.reset)
					resetStruct(&armData, ARM_STRUCT_SIZE);
				else if(armData.wristUp)
					wristUp();
				else if(armData.wristDown)
					wristDown();
				else if(armData.wristClockWise)
					wristClockWise();
				else if(armData.wristCounterClockWise)
					wristCounterClockWise();
				else if(armData.elbowUp)
					elbowUp();
				else if(armData.elbowDown)
					elbowDown();
				else if(armData.elbowClockWise)
					elbowClockWise();
				else if(armData.elbowCounterClockWise)
					elbowCounterClockWise();
				else if(armData.actuatorForward)
					actuatorForward();
				else if(armData.actuatorReverse)
					actuatorReverse();
				else if(armData.baseClockWise)
					baseClockWise();
				else if(armData.baseCounterClockWise)
					baseCounterClockWise();
				delay(DELAY);
				break;

			case GRIPPER_STRUCT_ID:
				memcpy(&gripperData, &receiveData, receiveData.size);
				//send_struct(UART_ENDE, &gripperData, INST_OTHER, GRIPPER_STRUCT_ID);
				delay(DELAY);
				break;



			case DRILL_STRUCT_ID:
				memcpy(&drillData, &receiveData, receiveData.size);
				//send_struct(UART_ENDE, &drillData, INST_OTHER, DRILL_STRUCT_ID);
				delay(DELAY);
				break;
			}
		}

		handled = 0;
		flushUart(UART_MOTHER);
		delay(1);
	}
}

void delay(int time)
{
	SysCtlDelay(time * (SysCtlClockGet()/1000));//1 time is 3/100 seconds
}

void wristClockWise(){
	if(wristClockwisePos < (WRIST_CLOCKWISE_LIMIT - DYNAMIXEL_INC))
	{
		wristDyno1Pos += DYNAMIXEL_INC;
		wristDyno2Pos += DYNAMIXEL_INC;
		wristClockwisePos += DYNAMIXEL_INC;
		dynoMove(UART_DYNAMIXEL, WRIST_1_ID, wristDyno1Pos);
		dynoMove(UART_DYNAMIXEL, WRIST_2_ID, wristDyno2Pos);
	}
	delay(DELAY);
}

void wristCounterClockWise(){
	if(wristClockwisePos > (WRIST_COUNTERCLOCKWISE_LIMIT + DYNAMIXEL_INC))
	{
		wristDyno1Pos -= DYNAMIXEL_INC;
		wristDyno2Pos -= DYNAMIXEL_INC;
		wristClockwisePos -= DYNAMIXEL_INC;
		dynoMove(UART_DYNAMIXEL, WRIST_1_ID, wristDyno1Pos);
		dynoMove(UART_DYNAMIXEL, WRIST_2_ID, wristDyno2Pos);
	}
	delay(DELAY);
}

void wristUp(){
	if(wristVertPos < (WRIST_UPPER_LIMIT - DYNAMIXEL_INC))
	{
		wristDyno1Pos += DYNAMIXEL_INC;
		wristDyno2Pos -= DYNAMIXEL_INC;
		wristVertPos += DYNAMIXEL_INC;
		dynoMove(UART_DYNAMIXEL, WRIST_1_ID, wristDyno1Pos);//todo: get the directions right
		dynoMove(UART_DYNAMIXEL, WRIST_2_ID, wristDyno2Pos);
	}
	delay(DELAY);
}

void wristDown(){
	if(wristVertPos > (WRIST_LOWER_LIMIT + DYNAMIXEL_INC))
	{
		wristDyno1Pos -= DYNAMIXEL_INC;
		wristDyno2Pos += DYNAMIXEL_INC;
		wristVertPos -= DYNAMIXEL_INC;
		dynoMove(UART_DYNAMIXEL, WRIST_1_ID, wristDyno1Pos);//todo: get the directions right
		dynoMove(UART_DYNAMIXEL, WRIST_2_ID, wristDyno2Pos);
	}
	delay(DELAY);
}

void elbowClockWise(){
	if(elbowClockwisePos < (ELBOW_CLOCKWISE_LIMIT - DYNAMIXEL_INC))
	{
		elbowDyno1Pos += DYNAMIXEL_INC;
		elbowDyno2Pos += DYNAMIXEL_INC;
		elbowClockwisePos += DYNAMIXEL_INC;
		dynoMove(UART_DYNAMIXEL, ELBOW_1_ID, elbowDyno1Pos);
		dynoMove(UART_DYNAMIXEL, ELBOW_2_ID, elbowDyno2Pos);
	}
	delay(DELAY);
}

void elbowCounterClockWise(){
	if(elbowClockwisePos > (ELBOW_COUNTERCLOCKWISE_LIMIT + DYNAMIXEL_INC))
	{
		elbowDyno1Pos -= DYNAMIXEL_INC;
		elbowDyno2Pos -= DYNAMIXEL_INC;
		elbowClockwisePos -= DYNAMIXEL_INC;
		dynoMove(UART_DYNAMIXEL, ELBOW_1_ID, elbowDyno1Pos);
		dynoMove(UART_DYNAMIXEL, ELBOW_2_ID, elbowDyno2Pos);
	}
	delay(DELAY);
}

void elbowDown(){
	if(elbowVertPos > (ELBOW_LOWER_LIMIT + DYNAMIXEL_INC))
	{
		elbowDyno1Pos -= DYNAMIXEL_INC;
		elbowDyno2Pos += DYNAMIXEL_INC;
		elbowVertPos -= DYNAMIXEL_INC;
		dynoMove(UART_DYNAMIXEL, ELBOW_1_ID, elbowDyno1Pos);//todo: get the directions right
		dynoMove(UART_DYNAMIXEL, ELBOW_2_ID, elbowDyno2Pos);
	}
	delay(DELAY);
}

void elbowUp(){
	if(elbowVertPos < (ELBOW_UPPER_LIMIT - DYNAMIXEL_INC))
	{
		elbowDyno1Pos += DYNAMIXEL_INC;
		elbowDyno2Pos -= DYNAMIXEL_INC;
		elbowVertPos += DYNAMIXEL_INC;
		dynoMove(UART_DYNAMIXEL, ELBOW_1_ID, elbowDyno1Pos);//todo: get the directions right
		dynoMove(UART_DYNAMIXEL, ELBOW_2_ID, elbowDyno2Pos);
	}
	delay(DELAY);
}

void actuatorForward(){
	if(actuatorPos <= (ACTUATOR_FORWARD_LIMIT - ACTUATOR_INC)) //The normal operation. If it's so that the next increment WONT push it beyond
	{											//or put it right at the limit, proceed as normal
		actuatorPos += ACTUATOR_INC;
		setMotor(UART_ACTUATOR, actuatorPos);
		delay(DELAY);
	}

	else if(actuatorPos < ACTUATOR_FORWARD_LIMIT) //if it turns out that our increments aren't a nice division of the limit and so it's below the limit but the next increment will
	{									  //still push it beyond it, just set it equal to the limit
		actuatorPos = ACTUATOR_FORWARD_LIMIT;
		setMotor(UART_ACTUATOR, actuatorPos);
		delay(DELAY);
	}
						//else, we're at the limit, no operation
}

void actuatorReverse(){
	if(actuatorPos >= (ACTUATOR_REVERSE_LIMIT + ACTUATOR_INC)) //The normal operation. If it's so that the next increment WONT push it beyond
	{											//or put it right at the limit, proceed as normal
		actuatorPos -= ACTUATOR_INC;
		setMotor(UART_ACTUATOR, actuatorPos);
		delay(DELAY);
	}

	else if(actuatorPos > ACTUATOR_REVERSE_LIMIT) //if it turns out that our increments aren't a nice division of the limit and so it's below the limit but the next increment will
	{									  //still push it beyond it, just set it equal to the limit
		actuatorPos = ACTUATOR_FORWARD_LIMIT;
		setMotor(UART_ACTUATOR, actuatorPos);
		delay(DELAY);
	}
						//else, we're at the limit, no operation
}

void baseClockWise(){
	if(basePos < (BASE_CLOCKWISE_LIMIT - DYNAMIXEL_INC))
	{
		basePos += DYNAMIXEL_INC;
		dynoMove(UART_DYNAMIXEL, BASE_ID, basePos);
	}
}

void baseCounterClockWise(){
if(basePos > (BASE_COUNTERCLOCKWISE_LIMIT + DYNAMIXEL_INC))
	{
		basePos -= DYNAMIXEL_INC;
		dynoMove(UART_DYNAMIXEL, BASE_ID, basePos);
	}
}


//Initializes the hardware. Sets the clock to 16 mhz, the 3 UART modules up -- motherboard and endefector with 115200 buad rates,
//dynomixel line with 57600 -- with 1 stop bit and no pariety, and initialize all of the pins that we use
//and setup most to transmit to output, ones used for UART aside. Puts the base dynamixel into wheel mode
void initHardware()
{

	//
	// Set the clocking to run directly from the main oscillator at 16 mhz
	// The following code:
	// -sets the system clock divider to 1
	// -sets the system clock to use an oscillator
	// -uses the main oscillator
	// -configures for use of 16 MHz crystal/oscillator input
	//
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);

	//uart1: dynamixel

	//
	// Enable the peripherals used by this example.
	// The UART itself needs to be enabled, as well as the GPIO port
	// containing the pins that will be used.
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

	//
	// Configure the GPIO pin muxing for the UART function.
	// This is only necessary if your part supports GPIO pin function muxing.
	// Study the data sheet to see which functions are allocated per pin.
	//
	GPIOPinConfigure(GPIO_PC4_U1RX);
	GPIOPinConfigure(GPIO_PC5_U1TX);

	//
	// Since GPIO C4 and C5 are used for the UART function, they must be
	// configured for use as a peripheral function (instead of GPIO).
	GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);

	//
	// Configure the UART for 115,200, 8-N-1 operation.
	// This function uses SysCtlClockGet() to get the system clock
	// frequency.  This could be also be a variable or hard coded value
	// instead of a function call.
	//

	UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 57600, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	//uart 2: motherboard
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	GPIOPinConfigure(GPIO_PD6_U2RX);
	GPIOPinConfigure(GPIO_PD7_U2TX);
	GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);
	UARTConfigSetExpClk(UART2_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	//uart 3: endefector
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	GPIOPinConfigure(GPIO_PC6_U3RX);
	GPIOPinConfigure(GPIO_PC7_U3TX);
	GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);
	UARTConfigSetExpClk(UART3_BASE, SysCtlClockGet(), 9600, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));


	//Uart 7: motor controller
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	GPIOPinConfigure(GPIO_PE0_U7RX);
	GPIOPinConfigure(GPIO_PE1_U7TX);
	GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTConfigSetExpClk(UART7_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));


	//interrupt setups
	IntSetup();


}

//resets all components to the struct.
void resetStruct(void * myStruct, int size){
	int i;
	uint8_t * address = (uint8_t *)myStruct;
	for(i = 0; i < size; i++)
	{
		*(address + i) = 0;
	}
}

void setMotor(uint32_t uart, uint16_t pos)
{
	uint8_t highByte = ((pos >> 5) & 0b01111111);
	uint8_t lowByte = ((uint8_t)pos & 0b00011111);
	lowByte |= 0b11000000;
	UARTCharPut(uart, lowByte);
	UARTCharPut(uart, highByte);
}

void initPositions()
{
	switchCom(TX_MODE);

	setMotor(UART_ACTUATOR, ACTUATOR_START_POS);
	actuatorPos = ACTUATOR_START_POS;

	wristDyno1Pos = dynoReadPosition(UART_DYNAMIXEL, WRIST_1_ID);
	wristDyno2Pos = dynoReadPosition(UART_DYNAMIXEL, WRIST_2_ID);
	elbowDyno1Pos = dynoReadPosition(UART_DYNAMIXEL, ELBOW_1_ID);
	elbowDyno1Pos = dynoReadPosition(UART_DYNAMIXEL, ELBOW_2_ID);
	basePos = dynoReadPosition(UART_DYNAMIXEL, BASE_ID);


	dynoMultiModeSet(UART_DYNAMIXEL, GLOBAL_ID); //sets them all to multi turn mode for now
}


//Int handler for the UART_MOTHER uart. The Arm data struct is so large that our FIFO's cannot handle it, so we use an
//interrupt to clear out the first few before using the recv_struct function for the rest.
//The interrupt can happen at any time when we're not actively in or responding to the
//recv_struct function, and to deal with the possible near constant stream of data the protocol shall go as follows:
//When we don't want the interrupt to change anything, the global variable handled shall be set to 1, meaning it should
//exit as soon as it enters while clearing the interrupt (I could just temporarily disable the interrupt instead, but
//frankly I'm terrified of any hidden consequences). When we're in our idle state, IE waiting for data, handled is set to 0
//and the interrupt shall begin reading upon gaining 4 bytes of data. Should the first byte in the stream be the start signal,
//then it loads up the next 3 bytes as well into the receive buffer and returns presumably to the recv_struct function to be
//used while setting handled to 1 to keep it from reading until the main task returns to idle. If not, then it returns to main
//task, which in its idle state will flush the uart FIFO so that it may read again (the interrupt ONLY fires when the fifo has 4
//bytes, so if we didn't flush it it would probably never return to its proper levels and the whole thing would cease being able
//to receive data.
void UARTMotherIntHandler()
{
	UARTIntClear(UART_MOTHER, UART_INT_RX);
	if(!(handled))
	{
		if((uartRxBuf[0] = UARTCharGetNonBlocking(UART_MOTHER)) == STRUCT_START1)
		{
			uint8_t i;
			for(i = 1; i < 3; i++)
			{
				if(!(HWREG(UART_MOTHER + UART_O_FR) & UART_FR_RXFE))//uartCharGetNonBlocking
				{
					uartRxBuf[i] = HWREG(UART_MOTHER + UART_O_DR);
				}
			}

			handled = 1;
		}
	}
}

//Sets up the interrupts, including: Uart_Mother's RX interrupt at 4 bytes (throws an interrupt at 4 bytes being put into buffer)
void IntSetup()
{
	UARTIntEnable(UART_MOTHER, UART_INT_RX); //must enable before registering the function dynamically
	UARTIntRegister(UART_MOTHER, UARTMotherIntHandler);
	UARTFIFOLevelSet(UART_MOTHER, UART_FIFO_TX1_8, UART_FIFO_RX2_8); //dont worry about the tx, it's unused
	IntMasterEnable();
	handled = 0;
}

void flushUart(uint32_t uart)
{
	while(UARTCharsAvail(uart))
		UARTCharGetNonBlocking(uart);
}
