//ArmMainV4-2.c
//created by: parker, alec, drue
//created on 2-11-15
//updated: 2-16-15 by drue
//
//Update content: Added in content for endefector communication.
//Changed struct_xfer so that we can now recieve 3 structs instead of 1. Modified all of main so that it works with the
//new struct_xfer and it can distribute the data structs meant for endefector to where it needs to go. Also, fixed delay
//function so it now is a lot more precise.
//RoveSoHard


#include "armMainV4.h"

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
 * Inside the move functions themselves, we either a) move the actuator using the motor control functions, delay, and then
 * stop the movement and exit the function. The purpose of setting it up as such is so that it automatically stops itself
 * and we don't have to worry about checking to see if the command is no longer being sent to us and to then stop the motion,
 * saving us a few clock cycles. The actuator itself is slow enough to where the start-stopping doesn't seem to effect its
 * motion, and it continually will move into the move actuator functions so long as the command continues to be sent to us.
 *
 * b) Move the dynamixels. At the moment, this is done by using the dynoMove function as described in dynamixel.h to
 * command it to move to an incremented position. We do this by incrementing its position variable and then passing the
 * dynoMove function the newly incremented variable. The position variables are to keep track of the arm's position at all
 * times, and the arm's movement is based off of incrementing the position variables for every movement.
 *
 * Currently there is no usage for the dynamixel's closed loop abilities, though functions exist to read certain values from
 * them they are untested as of 2-11-15
 *
 * warnings: the program locks itself into an idle state while waiting for commands from the motherboard, and relocks itself
 * upon completing said commands until it recieves more.
 */

void main(void)
{

	struct arm_control_struct armData;
	struct gripper_control_struct gripperData;
	struct drill_Controls drillData;
	receiveStruct receiveData;

    int16_t wristVertPos, wristHoriPos, elbowVertPos, elbowHoriPos, basePos;
	initHardware();
    initDynos(&wristVertPos, &wristHoriPos, &elbowVertPos, &elbowHoriPos, &basePos);
    delay(DELAY);
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
					resetStruct(&armData);
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
					actuatorForward();
				else if(armData.actuatorReverse)
					actuatorReverse();
				else if(armData.baseClockWise)
					baseClockWise(&basePos);
				else if(armData.baseCounterClockWise)
					baseCounterClockWise(&basePos);
				delay(DELAY);
				break;

			case GRIPPER_STRUCT_ID:
				memcpy(&gripperData, &receiveData, receiveData.size);
				send_struct(UART_ENDE, &gripperData, INST_OTHER, GRIPPER_STRUCT_ID);
				delay(DELAY);
				break;



			case DRILL_STRUCT_ID:
				memcpy(&drillData, &receiveData, receiveData.size);
				send_struct(UART_ENDE, &drillData, INST_OTHER, DRILL_STRUCT_ID);
				delay(DELAY);
				break;
			}
		}

		handled = 0;
		flushUart(UART_MOTHER);
		delay(DELAY);
	}
}

void delay(int time)
{
	SysCtlDelay(time * (SysCtlClockGet()/100));//1ms delay
}

void wristClockWise(int16_t * pos){
    *pos = *pos + INCREMENT;
    dynoMove(UART_DYNO, WRIST_HORI_ID, *pos);
    delay(DELAY);
}

void wristCounterClockWise(int16_t * pos){
    *pos -= INCREMENT;
    dynoMove(UART_DYNO, WRIST_HORI_ID, *pos);
	delay(DELAY);
}

void wristUp(int16_t * pos){
	*pos += INCREMENT;
    dynoMove(UART_DYNO, WRIST_VERT_ID, *pos);
	delay(DELAY);
}

void wristDown(int16_t * pos){
    *pos -= INCREMENT;
    dynoMove(UART_DYNO, WRIST_VERT_ID, *pos);
	delay(DELAY);
}

void elbowCounterClockWise(int16_t * pos){
	*pos -= INCREMENT;
    dynoMove(UART_DYNO, ELBOW_HORI_ID, *pos);
	delay(DELAY);
}

void elbowClockWise(int16_t * pos){
	*pos += INCREMENT;
    dynoMove(UART_DYNO, ELBOW_HORI_ID, *pos);
	delay(DELAY);
}

void elbowDown(int16_t * pos){
	*pos -= INCREMENT;
    dynoMove(UART_DYNO, ELBOW_VERT_ID, *pos);
	delay(DELAY);
}

void elbowUp(int16_t * pos){
	*pos += INCREMENT;
    dynoMove(UART_DYNO, ELBOW_VERT_ID, *pos);
	delay(DELAY);
}

void actuatorForward(){
    setReverse(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PORTA_BASE, GPIO_PIN_4);
	delay(DELAY);
	setStop(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PORTA_BASE, GPIO_PIN_4);
	delay(1);
}

void actuatorReverse(){
	setForward(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PORTA_BASE, GPIO_PIN_4);
	delay(DELAY);
	setStop(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PORTA_BASE, GPIO_PIN_4);
	delay(1);
}

void baseClockWise(int16_t * pos){
	*pos += INCREMENT;
    dynoMove(UART_DYNO, BASE_ID, *pos);
	delay(DELAY);
}

void baseCounterClockWise(int16_t * pos){
	*pos -= INCREMENT;
    dynoMove(UART_DYNO, BASE_ID, *pos);
	delay(DELAY);
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
	UARTConfigSetExpClk(UART3_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));


	//initialize the rest of the GPIO sets we need and set up to output the one's that need to be output
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_6); //actuator enable
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3); //actuator 1
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_4); //actuator 2


	//initialize the enable for the actuator
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, GPIO_PIN_6);

	//interrupt setups
	IntSetup();
}

//resets all components to the struct.
void resetStruct(struct arm_control_struct * armData){
  armData-> reset = 0;
  armData-> wristUp = 0;
  armData-> wristDown = 0;
  armData-> wristClockWise = 0;
  armData-> wristCounterClockWise = 0;
  armData-> elbowUp = 0;
  armData-> elbowDown = 0;
  armData-> elbowClockWise = 0;
  armData-> elbowCounterClockWise = 0;
  armData-> actuatorForward = 0;
  armData-> actuatorReverse = 0;
  armData-> baseClockWise = 0;
  armData-> baseCounterClockWise = 0;
}


//In order to move the motors forward, you set the first line high and the second line low
void setForward(uint32_t l1Base, uint8_t l1Pin, uint32_t l2Base, uint8_t l2Pin)
{
	GPIOPinWrite(l1Base,l1Pin,l1Pin);
	GPIOPinWrite(l2Base,l2Pin,0);
}

//In order to move the motors backward, you set the first line low and the second line high
void setReverse(uint32_t l1Base, uint8_t l1Pin, uint32_t l2Base, uint8_t l2Pin)
{
	GPIOPinWrite(l1Base,l1Pin,0);
	GPIOPinWrite(l2Base,l2Pin,l2Pin);
}

//In order to stop the motors, you set both of the lines low
void setStop(uint32_t l1Base, uint8_t l1Pin, uint32_t l2Base, uint8_t l2Pin)
{
	GPIOPinWrite(l1Base,l1Pin,0);
	GPIOPinWrite(l2Base,l2Pin,0);
}

void initDynos(int16_t * wristVertPos, int16_t * wristHoriPos, int16_t * elbowVertPos, int16_t * elbowHoriPos, int16_t * basePos)
{
    //todo: initialize the dynos. Including initial positions
	switchCom(TX_MODE);
	*wristVertPos = WRISTV_START_POS;
	*wristHoriPos = WRISTH_START_POS;
	*elbowVertPos = ELBOWV_START_POS;
	*elbowHoriPos = ELBOWH_START_POS;
	*basePos = BASE_START_POS;

	dynoMove(UART_DYNO, WRIST_VERT_ID, *wristVertPos);
	dynoMove(UART_DYNO, WRIST_HORI_ID, *wristHoriPos);
	dynoMove(UART_DYNO, ELBOW_HORI_ID, *elbowHoriPos);
	dynoMove(UART_DYNO, ELBOW_VERT_ID, *elbowVertPos);
	dynoMove(UART_DYNO, BASE_ID, *basePos);

	dynoMultiModeSet(UART_DYNO, GLOBAL_ID); //sets them all to multi turn mode for now
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
			for(i = 1; i < 4; i++)
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
