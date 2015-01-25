//ArmMain.c
//created by: parker, drue, alec
//updated: 1/22/15
//RoveSoHard

#include "armMain.h"
#include "dynamixel.h"
#include "inc/lm4f120h5qr.h"


//Program is mostly self explanatory. Motherboard sends us a RECIEVE_DATA_STRUCTURE that contains commands for what the arm's to do.
//We read the struct that's received, whichever command variables are set we have the arm do by writing out to the motors through
//the GPIO pins, and the dynamixel on the base through a UART line (which is also how the endefector and motherboard communicate with us)
//

int main(void)
{

	//unsigned int last = 0;
	struct RECEIVE_DATA_STRUCTURE receiveData;

	receiveData.wristUp = 0;
	receiveData.wristDown = 0;
	receiveData.wristClockWise = 0;
	receiveData.wristCounterClockWise = 0;
	receiveData.elbowUp = 1;
	receiveData.elbowDown = 0;
	receiveData.elbowClockWise = 0;
	receiveData.elbowCounterClockWise = 0;
	receiveData.actuatorForward = 0;
	receiveData.actuatorReverse = 0;
	receiveData.baseClockWise = 0;
	receiveData.baseCounterClockWise = 0;
	receiveData.reset = 0;

	//resetStruct(&receiveData);
	initHardware();
	delay(DELAY);
   while(1)
   {
	   //
	   // Turn on the LED.
	   //
	   GPIO_PORTF_DATA_R |= 0x08;
	   //   resetStruct(&receiveData);

	   //if(recv_struct(UART3_BASE,&receiveData)){
		   if(receiveData.reset)
			  resetStruct(&receiveData);
		  if(receiveData.wristUp)
			   wristUp();
		   if(receiveData.wristDown)
			   wristDown();
		   if(receiveData.wristClockWise)
			   wristClockWise();
		   if(receiveData.wristCounterClockWise)
			   wristCounterClockWise();
		   if(receiveData.elbowUp)
			   elbowUp();
		   if(receiveData.elbowDown)
			   elbowDown();
		   if(receiveData.elbowClockWise)
			   elbowClockWise();
		   if(receiveData.elbowCounterClockWise)
			   elbowCounterClockWise();
		   if(receiveData.actuatorForward)
			   actuatorForward();
		   if(receiveData.actuatorReverse)
			   actuatorReverse();
		   if(receiveData.baseClockWise)
			   baseClockWise();
		   if(receiveData.baseCounterClockWise)
			   baseCounterClockWise();
		    //resetStruct(&receiveData);

		   //
		   // Turn off the LED.
		   //
		   GPIO_PORTF_DATA_R &= ~(0x08);
		   delay(DELAY);
	   //}
	}
}

void delay(int time)
{
	int i;
	for(i = 0; i < time * 20000; i++)//1ms
	{
	}
}

void wristClockWise(){
    setForward(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PORTA_BASE, GPIO_PIN_2); //write out on pin D1 the forward character
	delay(DELAY);
  	setStop(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PORTA_BASE, GPIO_PIN_2); //After a delay, resets to 0 so it doesnt stay high for the rest of the program
  	delay(1);
  //last=1;
}

void wristCounterClockWise(){
	setReverse(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PORTA_BASE, GPIO_PIN_2);
	delay(DELAY);
	setStop(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PORTA_BASE, GPIO_PIN_2);
	delay(1);
	//last=2;
}

void wristUp(){
	setForward(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PORTD_BASE, GPIO_PIN_3);
	delay(DELAY);
	setStop(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PORTD_BASE, GPIO_PIN_3);
	delay(1);
	//last=3;
}

void wristDown(){
	setReverse(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PORTD_BASE, GPIO_PIN_3);
	delay(DELAY);
	setStop(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PORTD_BASE, GPIO_PIN_3);
	delay(1);
	//last=4;
}

void elbowCounterClockWise(){
	setForward(GPIO_PORTE_BASE, GPIO_PIN_0, GPIO_PORTF_BASE, GPIO_PIN_0);
	delay(DELAY);
	setStop(GPIO_PORTE_BASE, GPIO_PIN_0, GPIO_PORTF_BASE, GPIO_PIN_0);
	delay(1);
	//last=5;
}

void elbowClockWise(){
	setReverse(GPIO_PORTE_BASE, GPIO_PIN_0, GPIO_PORTF_BASE, GPIO_PIN_0);
	delay(DELAY);
	setStop(GPIO_PORTE_BASE, GPIO_PIN_0, GPIO_PORTF_BASE, GPIO_PIN_0);
	delay(1);
	//last=6;
}

void elbowDown(){
	setReverse(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PORTF_BASE, GPIO_PIN_3);
	delay(DELAY);
	setStop(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PORTF_BASE, GPIO_PIN_3);
	delay(1);
	//last=7;
}

void elbowUp(){
	setForward(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PORTF_BASE, GPIO_PIN_3);
	delay(DELAY);
	setStop(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PORTF_BASE, GPIO_PIN_3);
	delay(DELAY);
	//last=8;
}

void actuatorForward(i){
	setForward(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PORTA_BASE, GPIO_PIN_4);
	delay(DELAY);
	setStop(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PORTA_BASE, GPIO_PIN_4);
	delay(1);
	//last=9;
}

void actuatorReverse(){
	setReverse(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PORTA_BASE, GPIO_PIN_4);
	delay(DELAY);
	setStop(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PORTA_BASE, GPIO_PIN_4);
	delay(1);
	//last=10;
}

void baseClockWise(){
	dynoSpeedSet(UART1_BASE, GLOBAL_ID, DYNO_CLOCKWISE);
	delay(DELAY);
	dynoSpeedSet(UART1_BASE, GLOBAL_ID, 1024); //1024 is the stop for the servo's clockwise motion in motor mode
	delay(1);
	//last=11;
}

void baseCounterClockWise(){
	dynoSpeedSet(UART1_BASE, GLOBAL_ID, DYNO_COUNTERCLOCKWISE);
	delay(DELAY);
	dynoSpeedSet(UART1_BASE, GLOBAL_ID, 0);
	delay(1);
	//last=12;
}

//Initializes the hardware. Sets the clock, the 3 UART modules up with 115200 buad rates and 1 stop bit and no pariety, and initialize all of the pins that we use
//and setup most to transmit to output, ones used for UART aside. Puts the base dynamixel into wheel mode
void initHardware()
{

	//
	// Set the clocking to run directly from the PLL at 100 MHz.
	// The following code:
	// -sets the system clock divider to 10 (200 MHz PLL divide by 2 = 100 MHz)
	// -sets the system clock to use the PLL
	// -uses the main oscillator
	// -configures for use of 16 MHz crystal/oscillator input
	//
	SysCtlClockSet(SYSCTL_SYSDIV_2 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

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

	//uart 2: endefucker
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	GPIOPinConfigure(GPIO_PD6_U2RX);
	GPIOPinConfigure(GPIO_PD7_U2TX);
	GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);
	UARTConfigSetExpClk(UART2_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	//uart 3: motherboard
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
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1); //Motor controller wrist enable A
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_1); //motor controller wrist line A_1
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2); //motor controller wrist A_2
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_2); //motor controller wrist enable B
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2); //motor controller wrist B_1
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_3); //motor controller wrist B_2
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_7); //motor controller elbow enable A
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0); //motor controller elbow A_1
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0); //motor controller elbow A_2
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_2); //motor controller elbow enable B
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2); //motor controller elbow B_1
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3); //motor controller elbow B_2
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_6); //motor controller actuator enable (only one device in this controller)
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3); //motor controller actuator 1
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_4); //motor controller actuator 2

	dynoWheelModeSet(UART1_BASE, GLOBAL_ID);

	//initialize the enables for the motor controllers
	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_PIN_1);
	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_PIN_2);
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, GPIO_PIN_7);
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_PIN_2);
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
    p[10] = ~(id + MOVE_LENGTH + WRITE_DATA + 0x00 + 0x00 + 0x00 + 0x00);

    for(i = 0; i < 11; i++)
    {
      UARTCharPut(uart, p[i]); //send the data out
    }

    /*for(int i = 0; i < RETURN_PACKET_SIZE; i++)
    {
        UARTCharGet(p[i]); //recieves return status packet. Reason for no delay here is so we don't accidentally delay past it's sending us data, since the buffer
    }//only holds bytes and the dyno's return several bytes we could accidentally start reading halfway through

    p[8] = ~(p[2] + p[3] + p[ERROR_SLOT]) //using p[8] as storage for checking off the checksum. p2 holds ID and p3 holds length, CS = ID + L + Error + parameters (none here)
    if((p[ERROR_SLOT]) || (p[8] != p[6]))
        printf("error");*/

}


/*Wheel Mode:
0~2047( 0X7FF) can be used, the unit is about 0.1%.
If a value in the range of 0~1023 is used, it is stopped by setting to 0 while rotating to CCW direction.
If a value in the range of 1024~2047 is used, it is stopped by setting to 1024 while rotating to CW direction.
That is, the 10th bit becomes the direction bit to control the direction.
In Wheel Mode, only the output control is possible, not speed.
For example, if it is set to 512, it means the output is controlled by 50% of the maximum output.*/
void dynoSpeedSet(uint32_t uart, uint8_t id, int16_t speed)
{
    uint8_t p[9];
    int i;
    p[0] = START_BYTE;
    p[1] = START_BYTE;
    p[2] = id;
    p[3] = 0x05;
    p[4] = WRITE_DATA;
    p[5] = MOVING_SPEED_L;
    p[6] = ((uint8_t) speed);
    p[7] = ((uint8_t)(speed >> 8));
    p[8] = ~(id + MOVE_LENGTH + WRITE_DATA + p[6] + p[7]);

    for(i = 0; i < 9; i++)
    {
        UARTCharPut(uart, p[i]); //send the data out
    }

    /*for(int i = 0; i < RETURN_PACKET_SIZE; i++)
    {
        UARTCharGet(p[i]); //recieves return status packet. Reason for no delay here is so we don't accidentally delay past it's sending us data, since the buffer
    }//only holds bytes and the dyno's return several bytes we could accidentally start reading halfway through

    p[8] = ~(p[2] + p[3] + p[ERROR_SLOT]) //using p[8] as storage for checking off the checksum. p2 holds ID and p3 holds length, CS = ID + L + Error + parameters (none here)
    if((p[ERROR_SLOT]) || (p[8] != p[6]))
        printf("error");
    */
}

void setForward(uint32_t l1Base, uint8_t l1Pin, uint32_t l2Base, uint8_t l2Pin)
{
	GPIOPinWrite(l1Base,l1Pin,l1Pin);
	GPIOPinWrite(l2Base,l2Pin,0);
}

void setReverse(uint32_t l1Base, uint8_t l1Pin, uint32_t l2Base, uint8_t l2Pin)
{
	GPIOPinWrite(l1Base,l1Pin,0);
	GPIOPinWrite(l2Base,l2Pin,l2Pin);
}

void setStop(uint32_t l1Base, uint8_t l1Pin, uint32_t l2Base, uint8_t l2Pin)
{
	GPIOPinWrite(l1Base,l1Pin,0);
	GPIOPinWrite(l2Base,l2Pin,0);
}

