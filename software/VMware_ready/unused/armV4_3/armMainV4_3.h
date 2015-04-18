/*
 * armMainV4_3.h
 * date of birth: 4-10-15
 * date of update:
 *
 * What do you call all the enemies of the mars rover?
 * Dead, that's what. #theMartiansRemember
 */

#ifndef ARMMAINV4_H_
#define ARMMAINV4_H_

#define UART_MOTHER UART2_BASE
#define UART_ENDE	UART3_BASE
#define UART_DYNAMIXEL   UART1_BASE
#define UART_ACTUATOR 	 UART7_BASE

//.c's are included becuase often CCS wont know where to find source files when transferring projects
#include "inc\hw_memmap.h"
#include "inc\hw_types.h"
#include "driverlib\gpio.h"
#include "driverlib\gpio.c"
#include "driverlib\sysctl.h"
#include "driverlib\uart.h"
#include "utils\uartstdio.h"
#include "struct_xfer_armVersion.h"
#include "driverlib\pin_map.h"
#include "driverlib\interrupt.c"
#include "driverlib\cpu.c"
#include "driverlib\uart.c"
#include "driverlib\sysctl.c"
#include "dynamixel.h"
//#include "inc/tm4c123gh6pm.h"
#include <stdint.h>

#define WRIST_1_ID           0x01//todo: get all these values, current are placeholders
#define WRIST_2_ID			 0x02
#define ELBOW_1_ID			 0x03
#define ELBOW_2_ID			 0x04
#define BASE_ID				 0x05

#define ACTUATOR_START_POS		0x00

#define DYNAMIXEL_INC   		57 //56.81 units per 5 degrees, .088 unit per 1 degree
#define ACTUATOR_INC			273//4095 -- it's forward limit -- divided into 15 increments
#define DELAY 5

const short ACTUATOR_FORWARD_LIMIT = 4095;//limit of the values it can be set to on forward
const short ACTUATOR_REVERSE_LIMIT = 0;
const int WRIST_UPPER_LIMIT = 10000;
const int WRIST_LOWER_LIMIT = 0;
const int ELBOW_UPPER_LIMIT = 10000;
const int ELBOW_LOWER_LIMIT = 0;
const int WRIST_CLOCKWISE_LIMIT = 5000; //clockwise arbitrarily set as positive direction
const int WRIST_COUNTERCLOCKWISE_LIMIT = -5000;
const int ELBOW_CLOCKWISE_LIMIT = 5000;
const int ELBOW_COUNTERCLOCKWISE_LIMIT = -5000;
const int BASE_CLOCKWISE_LIMIT = 28672;
const int BASE_COUNTERCLOCKWISE_LIMIT = -28672;


#define ARM_STRUCT_SIZE			14
#define RECEIVE_STRUCT_SIZE		18


////////////////////////////////global variables
uint8_t uartRxBuf[4] = {0,0,0,0};
uint8_t handled = 1;



///////////////////////////////////general functions

//Initializes the hardware. Sets the clock to 16 mhz, the 3 UART modules up -- motherboard and endefector with
//115200 buad rates, dynomixel line with 57600 -- with 1 stop bit and no pariety, and initialize all of the pins that we use
//and setup most to transmit to output, ones used for UART aside.
extern void initHardware();

//Initializes the dynamixels and actuator. Moves them to their initial positions, initializes the position variables.
//Arguments are the position variables for the dynamixel's and actuator, declared in main
extern void initPositions();

//resets the arm control struct
extern void resetStruct(void * myStruct, int size);

//delays about 1 millisecond * time
extern void delay(int time);

//clears the RX buffer. uint32_t uart is the base address of the uart peripheral to be flushed
extern void flushUart(uint32_t uart);


///////////////main movement call functions///////////////////////////////////////////////////////////////
//move wrist clockwise, and so on for the rest...self explanatory names are wonderful aren't they

extern void wristClockWise();
extern void wristCounterClockWise();
extern void wristUp();
extern void wristDown();
extern void elbowCounterClockWise();
extern void elbowClockWise();
extern void elbowDown();
extern void elbowUp();
extern void actuatorForward();
extern void actuatorReverse();
extern void baseClockWise();
extern void baseCounterClockWise();


////////////////motor control function//////
void setMotor(uint32_t uart, uint16_t pos);


////////////////interrupts////////////

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
extern void UARTMotherIntHandler();


//Sets up the interrupts, including: Uart_Mother's RX interrupt at 4 bytes (throws an interrupt at 4 bytes being put into buffer)
extern void IntSetup();


#endif /* ARMMAINV4_H_ */

