//ArmMain.c
//created by: parker, alec, drue
//created on 2-11-15
//updated: 2-11-15
//RoveSoHard


#include "armMainV4.h"

/* Here we control the arm movement for the rover. The overhead process goes: our arm waits in place until the user pushes
 * a button/moves a joystick/ whatever, they send the signal to motherboard who then sends it to us in the form of the
 * RECIEVE_DATA_STRUCTURE struct, found in struct_xfer.h. We stay in a loop where we constantly check with the
 * recv_struct function if motherboard is sending us said struct; when they do, we read what variables have been set
 * and have the arm move accordingly by calling the movement functions.
 * Simple enough; they command, we get commands, we have arm move accordingly.
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
 */

void main(void)
{

	struct RECEIVE_DATA_STRUCTURE receiveData;
    int16_t wristVertPos, wristHoriPos, elbowVertPos, elbowHoriPos, basePos;

	initHardware();
    initDynos(&wristVertPos, &wristHoriPos, &elbowVertPos, &elbowHoriPos, &basePos);
	int16_t *testPointer = &wristVertPos;
	while(1)
	{
		dynoMove(UART1_BASE, 1, *testPointer); //in for testing
	}
	delay(DELAY);
	while(1)
	{
		if(recv_struct(UART2_BASE, &receiveData))
		{
			if(receiveData.reset)
				resetStruct(&receiveData);
			else if(receiveData.wristUp)
				wristUp(&wristVertPos);
			else if(receiveData.wristDown)
				wristDown(&wristVertPos);
			else if(receiveData.wristClockWise)
				wristClockWise(&wristHoriPos);
			else if(receiveData.wristCounterClockWise)
				wristCounterClockWise(&wristHoriPos);
			else if(receiveData.elbowUp)
				elbowUp(&elbowVertPos);
			else if(receiveData.elbowDown)
				elbowDown(&elbowVertPos);
			else if(receiveData.elbowClockWise)
				elbowClockWise(&elbowHoriPos);
			else if(receiveData.elbowCounterClockWise)
				elbowCounterClockWise(&elbowHoriPos);
			else if(receiveData.actuatorForward)
				actuatorForward();
			else if(receiveData.actuatorReverse)
				actuatorReverse();
			else if(receiveData.baseClockWise)
				baseClockWise(&basePos);
			else if(receiveData.baseCounterClockWise)
				baseCounterClockWise(&basePos);

			delay(DELAY);
		}
	}
}

void delay(int time)
{
	int i;
	for(i = 0; i < time * 20000; i++);//1ms...ishness?
}

void wristClockWise(int16_t * pos){
    *pos = *pos + INCREMENT;
    dynoMove(UART1_BASE, WRIST_HORI_ID, *pos);
    delay(DELAY);
}

void wristCounterClockWise(int16_t * pos){
    *pos -= INCREMENT;
    dynoMove(UART1_BASE, WRIST_HORI_ID, *pos);
	delay(DELAY);
}

void wristUp(int16_t * pos){
	*pos += INCREMENT;
    dynoMove(UART1_BASE, WRIST_VERT_ID, *pos);
	delay(DELAY);
}

void wristDown(int16_t * pos){
    *pos -= INCREMENT;
    dynoMove(UART1_BASE, WRIST_VERT_ID, *pos);
	delay(DELAY);
}

void elbowCounterClockWise(int16_t * pos){
	*pos -= INCREMENT;
    dynoMove(UART1_BASE, ELBOW_HORI_ID, *pos);
	delay(DELAY);
}

void elbowClockWise(int16_t * pos){
	*pos += INCREMENT;
    dynoMove(UART1_BASE, ELBOW_HORI_ID, *pos);
	delay(DELAY);
}

void elbowDown(int16_t * pos){
	*pos -= INCREMENT;
    dynoMove(UART1_BASE, ELBOW_VERT_ID, *pos);
	delay(DELAY);
}

void elbowUp(int16_t * pos){
	*pos += INCREMENT;
    dynoMove(UART1_BASE, ELBOW_VERT_ID, *pos);
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
    dynoMove(UART1_BASE, BASE_ID, *pos);
	delay(DELAY);
}

void baseCounterClockWise(int16_t * pos){
	*pos -= INCREMENT;
    dynoMove(UART1_BASE, BASE_ID, *pos);
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

	//uart 3: endetrucker
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	GPIOPinConfigure(GPIO_PC6_U3RX);
	GPIOPinConfigure(GPIO_PC7_U3TX);
	GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);
	UARTConfigSetExpClk(UART2_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));


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
}

//resets all components to the struct.
void resetStruct(struct RECEIVE_DATA_STRUCTURE * receiveData){
  receiveData-> reset = 0;
  receiveData-> wristUp = 0;
  receiveData-> wristDown = 0;
  receiveData-> wristClockWise = 0;
  receiveData-> wristCounterClockWise = 0;
  receiveData-> elbowUp = 0;
  receiveData-> elbowDown = 0;
  receiveData-> elbowClockWise = 0;
  receiveData-> elbowCounterClockWise = 0;
  receiveData-> actuatorForward = 0;
  receiveData-> actuatorReverse = 0;
  receiveData-> baseClockWise = 0;
  receiveData-> baseCounterClockWise = 0;
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

	dynoMove(UART1_BASE, WRIST_VERT_ID, *wristVertPos);
	dynoMove(UART1_BASE, WRIST_HORI_ID, *wristHoriPos);
	dynoMove(UART1_BASE, ELBOW_HORI_ID, *elbowHoriPos);
	dynoMove(UART1_BASE, ELBOW_VERT_ID, *elbowVertPos);
	dynoMove(UART1_BASE, BASE_ID, *basePos);

	dynoMultiModeSet(UART1_BASE, GLOBAL_ID); //sets them all to multi turn mode for now
}

