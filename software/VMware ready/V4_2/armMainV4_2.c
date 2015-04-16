//ArmMainV4-2.c
//created by: parker, alec, drue
//created on 2-11-15
//updated: 4-8-15 by drue
//
//Update content: Added in content for endefector communication.
//Changed struct_xfer so that we can now receive 3 structs instead of 1. Modified all of main so that it works with the
//new struct_xfer and it can distribute the data structs meant for endefector to where it needs to go. Also, fixed delay
//function so it now is a lot more precise.
//
//Update 4-8-15 -- added in constants for ID's and the actuator limits
//Update 4-15-15 -- set up ability for the arm and wrist to move up and down with dual dynamixel movement.
//WARNING: CLOCKWISE/CC MOVEMENT IS NOT FUNCTIONAL! todo: get this working
//RoveSoHard


#include "armMainV4.h"


void main(void)
{

	struct arm_control_struct armData;
	struct gripper_control_struct gripperData;
	struct drill_Controls drillData;
	receiveStruct receiveData;
	int16_t wristVertPos, wristHoriPos, elbowVertPos, elbowHoriPos, basePos;
	uint16_t actuatorPos;

	resetStruct(&receiveData, RECEIVE_STRUCT_SIZE);

	initHardware();

	actuatorPos = 2250;
    //initPositions(&wristVertPos, &wristClockwisePos, &elbowVertPos, &elbowClockwisePose, &basePos, &actuatorPos);
   // delay(DELAY);


    while(1)
	{
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
		delay(50);*/
		dynoMove(UART_DYNAMIXEL, GLOBAL_ID, 0x00);
		delay(500);
		dynoMove(UART_DYNAMIXEL, GLOBAL_ID, 1000);
		delay(500);
    	//setMotor(UART_ACTUATOR, 2000);
    	//actuatorForward(&actuatorPos);
    	//delay(500);
	}
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
					wristUp(&wristVertPos);
				else if(armData.wristDown)
					wristDown(&wristVertPos);
				else if(armData.wristClockWise)
					wristClockWise(&wristHoriPos);
				else if(armData.wristCounterClockWise)
					wristCounterClockWise(&wristHoriPos);
				else if(armData.elbowUp)
					elbowUp(&elbowVertPos);
				else if(armData.elbowDown)
					elbowDown(&elbowVertPos);
				else if(armData.elbowClockWise)
					elbowClockWise(&elbowHoriPos);
				else if(armData.elbowCounterClockWise)
					elbowCounterClockWise(&elbowHoriPos);
				else if(armData.actuatorForward)
					actuatorForward(&actuatorPos);
				else if(armData.actuatorReverse)
					actuatorReverse(&actuatorPos);
				else if(armData.baseClockWise)
					baseClockWise(&basePos);
				else if(armData.baseCounterClockWise)
					baseCounterClockWise(&basePos);
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

void wristClockWise(int16_t * pos){
    *pos = *pos + DYNAMIXEL_INC;
    dynoMove(UART_DYNAMIXEL, WRIST_HORI_ID, *pos);
    delay(DELAY);
}

void wristCounterClockWise(int16_t * pos){
    *pos -= DYNAMIXEL_INC;
    dynoMove(UART_DYNAMIXEL, WRIST_HORI_ID, *pos);
	delay(DELAY);
}

void wristUp(int16_t * pos){
	*pos += DYNAMIXEL_INC;
    dynoMove(UART_DYNAMIXEL, WRIST_DYNOA_ID, *pos);
    dynoMove(UART_DYNAMIXEL, WRIST_DYNOB_ID, (WRISTB_START_POS - *pos));
	delay(DELAY);
}

void wristDown(int16_t * pos){
    *pos -= DYNAMIXEL_INC;
    dynoMove(UART_DYNAMIXEL, WRIST_DYNOA_ID, *pos);
    dynoMove(UART_DYNAMIXEL, WRIST_DYNOB_ID, (WRISTB_START_POS - *pos));
	delay(DELAY);
}

void elbowCounterClockWise(int16_t * pos){
	*pos -= DYNAMIXEL_INC;
    dynoMove(UART_DYNAMIXEL, ELBOW_HORI_ID, *pos);
	delay(DELAY);
}

void elbowClockWise(int16_t * pos){
	*pos += DYNAMIXEL_INC;
    dynoMove(UART_DYNAMIXEL, ELBOW_HORI_ID, *pos);
	delay(DELAY);
}

void elbowDown(int16_t * pos){
	*pos += DYNAMIXEL_INC;
	dynoMove(UART_DYNAMIXEL, ELBOW_DYNOA_ID, *pos);
	dynoMove(UART_DYNAMIXEL, ELBOW_DYNOB_ID, (ELBOWB_START_POS - *pos));
	delay(DELAY);
}

void elbowUp(int16_t * pos){
	*pos -= DYNAMIXEL_INC;
	dynoMove(UART_DYNAMIXEL, ELBOW_DYNOA_ID, *pos);
	dynoMove(UART_DYNAMIXEL, ELBOW_DYNOB_ID, (ELBOWB_START_POS - *pos));
	delay(DELAY);
}

void actuatorForward(uint16_t *pos){
	if(*pos >= (ACTUATOR_FORWARD_LIMIT + ACTUATOR_INC)) //The normal operation. If it's so that the next increment WONT push it beyond
	{											//or put it right at the limit, proceed as normal
		*pos -= ACTUATOR_INC;
		setMotor(UART_ACTUATOR, *pos);
		delay(DELAY);
	}

	else if(*pos > ACTUATOR_FORWARD_LIMIT) //if it turns out that our increments aren't a nice division of the limit and so it's below the limit but the next increment will
	{									  //still push it beyond it, just set it equal to the limit
		*pos = ACTUATOR_FORWARD_LIMIT;
		setMotor(UART_ACTUATOR, *pos);
		delay(DELAY);
	}
						//else, we're at the limit, no operation
}

void actuatorReverse(uint16_t *pos){
	if(*pos <= (ACTUATOR_REVERSE_LIMIT - ACTUATOR_INC)) //The normal operation. If it's so that the next increment WONT push it beyond
	{											//or put it right at the limit, proceed as normal
		*pos += ACTUATOR_INC;
		setMotor(UART_ACTUATOR, *pos);
		delay(DELAY);
	}

	else if(*pos < ACTUATOR_REVERSE_LIMIT) //if it turns out that our increments aren't a nice division of the limit and so it's below the limit but the next increment will
	{									  //still push it beyond it, just set it equal to the limit
		*pos = ACTUATOR_REVERSE_LIMIT;
		setMotor(UART_ACTUATOR, *pos);
		delay(DELAY);
	}
						//else, we're at the limit, no operation
}

void baseClockWise(int16_t *pos){
	*pos -= DYNAMIXEL_INC;
    dynoMove(UART_DYNAMIXEL, BASE_ID, *pos);
	delay(DELAY);
}

void baseCounterClockWise(int16_t *pos){
	*pos += DYNAMIXEL_INC;
    dynoMove(UART_DYNAMIXEL, BASE_ID, *pos);
	delay(DELAY);
}


//Initializes the hardware. Sets the clock to 16 mhz, the 4 UART modules up -- motherboard and actuator with 115200 buad rates,
//dynamixel line with 57600, endetrucker with 9600 -- with 1 stop bit and no pariety, and initialize all of the pins that we use
//and setup most to transmit to output, ones used for UART aside.
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

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_3); //tri-state-buffer enable
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, GPIO_PIN_3);

	//interrupt setups
	IntSetup();

}

void resetStruct(void * myStruct, int size){
	int i;
	uint8_t * address = (uint8_t *)myStruct;
	for(i = 0; i < size; i++)
	{
		*(address + i) = 0;
	}//if this seems confusing: creates a pointer to the base address of struct, then increments the pointer up to
}//the size of the struct, IE how many variables are in it IE how many memory blocks the struct encompasses and therefore
//the blocks within its scope represent its variables...while setting them all to 0.

void setMotor(uint32_t uart, uint16_t pos)
{
	uint8_t highByte = ((pos >> 5) & 0b01111111);
	uint8_t lowByte = ((uint8_t)pos & 0b00011111);
	lowByte |= 0b11000000;
	UARTCharPut(uart, lowByte);
	UARTCharPut(uart, highByte);
}

void initPositions(int16_t * wristVertPos, int16_t * wristHoriPos, int16_t * elbowVertPos, int16_t * elbowHoriPos, int16_t * basePos, uint16_t * actuatorPos)
{
	switchCom(TX_MODE);
	*wristVertPos = WRISTA_START_POS;
	*wristHoriPos = WRISTB_START_POS;
	*elbowVertPos = ELBOWA_START_POS;
	*elbowHoriPos = ELBOWB_START_POS;
	*basePos = BASE_START_POS;
	*actuatorPos = ACTUATOR_START_POS;
	setMotor(UART_ACTUATOR, *actuatorPos);

	dynoMove(UART_DYNAMIXEL, WRIST_VERT_ID, *wristVertPos);
	dynoMove(UART_DYNAMIXEL, WRIST_HORI_ID, *wristHoriPos);
	dynoMove(UART_DYNAMIXEL, ELBOW_HORI_ID, *elbowHoriPos);
	dynoMove(UART_DYNAMIXEL, ELBOW_VERT_ID, *elbowVertPos);
	dynoMove(UART_DYNAMIXEL, BASE_ID, *basePos);

	dynoMultiModeSet(UART_DYNAMIXEL, GLOBAL_ID); //sets them all to multi turn mode for now
}



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