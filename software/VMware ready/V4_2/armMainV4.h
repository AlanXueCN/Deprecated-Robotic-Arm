/*
 * armMainV4.h
 * date of birth: 1-22-15
 * date of update: 2-16-15
 *
 * What do you call all the enemies of the mars rover?
 * Dead, that's what. #theMartiansRemember
 */

#ifndef ARMMAINV4_H_
#define ARMMAINV4_H_

#include <stdbool.h>
#include <stdint.h>

#define UART_MOTHER	    UART2_BASE
#define UART_ENDE		UART3_BASE
#define UART_DYNAMIXEL  UART1_BASE
#define UART_ACTUATOR 	UART7_BASE

//.c's are included becuase often CCS wont know where to find source files when transferring projects
#include "/opt/ti/tirtos_tivac_2_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/inc/hw_memmap.h"
#include "/opt/ti/tirtos_tivac_2_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/inc/hw_types.h"
#include "/opt/ti/tirtos_tivac_2_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/driverlib/gpio.h"
#include "/opt/ti/tirtos_tivac_2_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/driverlib/gpio.c"
#include "/opt/ti/tirtos_tivac_2_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/driverlib/sysctl.h"
#include "/opt/ti/tirtos_tivac_2_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/driverlib/uart.h"
#include "/opt/ti/tirtos_tivac_2_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/utils/uartstdio.h"
#include "/opt/ti/tirtos_tivac_2_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/driverlib/pin_map.h"
#include "/opt/ti/tirtos_tivac_2_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/driverlib/interrupt.c"
#include "/opt/ti/tirtos_tivac_2_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/driverlib/cpu.c"
#include "/opt/ti/tirtos_tivac_2_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/driverlib/uart.c"
#include "/opt/ti/tirtos_tivac_2_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/driverlib/sysctl.c"
#include "/opt/ti/tirtos_tivac_2_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/driverlib/rom.h"
#include "dynamixel.h"
#include "struct_xfer_armVersion.h"


#include <stdint.h>

#define DELAY 5
#define WRIST_DYNOA_ID          0x01
#define WRIST_DYNOB_ID			0x02
#define ELBOW_DYNOA_ID			0x03
#define ELBOW_DYNOB_ID			0x04
#define BASE_DYNO_ID			0x05

#define WRIST_HORI_ID			0x01 //placeholders until the controls system is changed properly out
#define WRIST_VERT_ID			0x02
#define ELBOW_HORI_ID			0x03
#define ELBOW_VERT_ID			0x04
#define BASE_ID					0x05

#define WRISTA_START_POS		0
#define WRISTB_START_POS		0
#define ELBOWA_START_POS		0
#define ELBOWB_START_POS		0
#define BASE_START_POS			0

#define ACTUATOR_START_POS		2400
const short ACTUATOR_FORWARD_LIMIT = 1600;//limit of the values it can be set to on forward
const short ACTUATOR_REVERSE_LIMIT = 2400;
#define DYNAMIXEL_INC   		57 //56.81 units per 5 degrees, .088 unit per 1 degree
#define ACTUATOR_INC			53//800 -- its Difference in limits -- divided into 15 increments
#define DELAY 5

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

//Initializes the dynamixels. Moves them to their initial positions, initializes the position variables. Sets them to
//multi turn mode for now. Arguments are the position variables for the dynamixel's, declared in main
extern void initPositions(int16_t * wristVertPos, int16_t * wristHoriPos, int16_t * elbowVertPos, int16_t * elbowHoriPos, int16_t * basePos, uint16_t * actuatorPos);

//resets the arm control struct
extern void resetStruct(void * myStruct, int size);

//delays about 1 millisecond * time
extern void delay(int time);

//clears the RX buffer. uint32_t uart is the base address of the uart peripheral to be flushed
extern void flushUart(uint32_t uart);


///////////////main movement call functions///////////////////////////////////////////////////////////////
//move wrist clockwise, and so on for the rest...self explanatory names are wonderful aren't they

extern void wristClockWise(int16_t * pos);
extern void wristCounterClockWise(int16_t * pos);
extern void wristUp(int16_t * pos);
extern void wristDown(int16_t * pos);
extern void elbowCounterClockWise(int16_t * pos);
extern void elbowClockWise(int16_t * pos);
extern void elbowDown(int16_t * pos);
extern void elbowUp(int16_t * pos);
extern void actuatorForward();
extern void actuatorReverse();
extern void baseClockWise(int16_t * pos);
extern void baseCounterClockWise(int16_t * pos);

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
