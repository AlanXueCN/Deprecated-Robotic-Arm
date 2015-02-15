#include <lm4f120h5qr.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "struct_xfer.c"
#include "uart.h"
#define DELAY 5
#define BYTE


	const int FORWARD_CHARACTER = 0;
	const int REVERSE_CHARACTER = 1;

void reset(void);

int main(void){
	//necessary variable definitions

	unsigned int last = 0;
	unsigned int count = 0;
	volatile int state = 0; //unsure if this will work
	struct RECEIVE_DATA_STRUCTURE receiveData;
	short int DEBUG_MODE = false;

	initPins();

	uint32_t uart1;
	uint32_t uart2;
	uint32_t uart3;

	uart1 = init_uart(1,115200);
	uart2 = init_uart(2,115200);
	uart3 = init_uart(3,115200);
	//initialization of Pins


	//const int DUBUG_MODE_SELECT = A3; //unsure if A3 is an int.
	//setup
	UARTStdioInit(0);
	resetStruct();
	//while loop for running the main program
	while(1)
	{
		if(recv_struct(uart3,&receiveData)){
		    if(receiveData.reset)
		      reset();
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
		    resetStruct();
		}
	}
}


void wristClockWise(){
  GPIOPinWrite(GPIO_PORTD_BASE,1,FORWARD_CHARACTER); //psudeo funciton.
  delay(DELAY);
  last=1;
}

void wristCOunterClockWise(){
	GPIOPinWrite(GPIO_PORTA_BASE,2,FORWARD_CHARACTER);
	delay(DELAY);
	last=2;
}

void wristUp(){
	GPIOPinWrite(GPIO_PORTD_BASE,2,FORWARD_CHARACTER);
	delay(DELAY);
	last=3;
}

void wristDown(){
	GPIOPinWrite(GPIO_PORTD_BASE,2,FORWARD_CHARACTER);
	delay(DELAY);
	last=4;
}

void elbowCounterClockWise(){
	GPIOPinWrite(GPIO_PORTE_BASE,0,FORWARD_CHARACTER);
	delay(DELAY);
	last=5;
}

void elbowClockWise(){
	GPIOPinWrite(GPIO_PORTF_BASE,0,FORWARD_CHARACTER);
	delay(DELAY);
	last=6;
}

void elbowDown(){
	GPIOPinWrite(GPIO_PORTF_BASE,2,FORWARD_CHARACTER);
	delay(DELAY);
	last=7;
}

void elbowUp(){
	GPIOPinWrite(GPIO_PORTF_BASE,3,FORWARD_CHARACTER);
	delay(DELAY);
	last=8;
}

void actuatorForward(){
	GPIOPinWrite(GPIO_PORTA_BASE,3,FORWARD_CHARACTER);
	delay(DELAY);
	last=9;
}

void actuatorReverse(){
	GPIOPinWrite(GPIO_PORTA_BASE,4,FORWARD_CHARACTER);
	delay(DELAY);
	last=10;
}

void baseClockWise(){
	UARTwrite(FORWARD_CHARACTER);
	delay(DELAY);
	last=11;
}

void baseCounterClockWise(){
	UARTwrite(FORWARD_CHARACTER);
	delay(DELAY);
	last=12;
}
void initPins(){
		GPIOPinTypeGPIOOutout(GPIO_PORTE_BASE, 1)
		GPIOPinTypeGPIOOutout(GPIO_PORTD_BASE, 1)
		GPIOPinTypeGPIOOutout(GPIO_PORTA_BASE, 2)
		GPIOPinTypeGPIOOutout(GPIO_PORTE_BASE, 2)
		GPIOPinTypeGPIOOutout(GPIO_PORTD_BASE, 3)
		GPIOPinTypeGPIOOutout(GPIO_PORTD_BASE, 3)
		GPIOPinTypeGPIOOutout(GPIO_PORTB_BASE, 7)
		GPIOPinTypeGPIOOutout(GPIO_PORTE_BASE, 0)
		GPIOPinTypeGPIOOutout(GPIO_PORTF_BASE, 0)
		GPIOPinTypeGPIOOutout(GPIO_PORTB_BASE, 2)
		GPIOPinTypeGPIOOutout(GPIO_PORTF_BASE, 2)
		GPIOPinTypeGPIOOutout(GPIO_PORTF_BASE, 3)
		GPIOPinTypeGPIOOutout(GPIO_PORTB_BASE, 6)
		GPIOPinTypeGPIOOutout(GPIO_PORTA_BASE, 3)
		GPIOPinTypeGPIOOutout(GPIO_PORTA_BASE, 4)

}
//resets all components to the struct.
void resetStruct(){
  receiveData.reset = 0;
  receiveData.wristUp = 0;
  receiveData.wristDown = 0;
  receiveData.wristClockWise = 0;
  receiveData.wristCounterClockWise = 0;
  receiveData.elbowUp = 0;
  receiveData.elbowDown = 0;
  receiveData.elbowClockWise = 0;
  receiveData.elbowCounterClockWise = 0;
  receiveData.actuatorForward = 0;
  receiveData.actuatorReverse = 0;
  receiveData.baseClockWise = 0;
  receiveData.baseCounterClockWise = 0;
}
