/*
 * armMainV4.h
 * date of birth: 1-22-15
 * date of update: 2-16-15
 *
 * What do you call all the enemies of the mars rover?
 * Dead, that's what. #theRoverRemembers
 */

#ifndef ARMMAINV4_H_
#define ARMMAINV4_H_

#define UART_MOTHER UART2_BASE
#define UART_ENDE	UART3_BASE
#define UART_DYNO   UART1_BASE

//.c's are included becuase often CCS wont know where to find source files when transferring projects
#include "/opt/ti/tirtos_tivac_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/inc/hw_memmap.h"
#include "/opt/ti/tirtos_tivac_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/inc/hw_types.h"
#include "/opt/ti/tirtos_tivac_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/driverlib/gpio.h"
#include "/opt/ti/tirtos_tivac_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/driverlib/gpio.c"
#include "/opt/ti/tirtos_tivac_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/driverlib/sysctl.h"
#include "/opt/ti/tirtos_tivac_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/driverlib/uart.h"
#include "/opt/ti/tirtos_tivac_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/utils/uartstdio.h"
#include "struct_xfer_armVersion.h"
#include "/opt/ti/tirtos_tivac_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/driverlib/pin_map.h"
#include "/opt/ti/tirtos_tivac_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/driverlib/interrupt.c"
#include "/opt/ti/tirtos_tivac_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/driverlib/cpu.c"
#include "/opt/ti/tirtos_tivac_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/driverlib/uart.c"
#include "/opt/ti/tirtos_tivac_10_01_38/products/TivaWare_C_Series-2.1.0.12573c/driverlib/sysctl.c"
#include "dynamixel.h"
//#include "inc/tm4c123gh6pm.h"
#include <stdint.h>

#define DELAY 5
#define GPIO_PC4_U1RX           0x00021002 //for setting pin C4 to be uart1's RX pin in the hardware config function. 
#define GPIO_PC5_U1TX           0x00021402 //and so on and so on with the rest
#define GPIO_PD6_U2RX           0x00031801
#define GPIO_PD7_U2TX           0x00031C01
#define GPIO_PC6_U3RX           0x00021801
#define GPIO_PC7_U3TX           0x00021C01
#define WRIST_VERT_ID           0x01//todo: get all these values, current are placeholders
#define WRIST_HORI_ID			0x01
#define ELBOW_HORI_ID			0x01
#define ELBOW_VERT_ID			0x01
#define BASE_ID					0x01
#define WRISTH_START_POS		0X7FF
#define WRISTV_START_POS		0X7FF
#define ELBOWV_START_POS		0X7FF
#define ELBOWH_START_POS		0X7FF
#define BASE_START_POS			0X7FF
#define INCREMENT   			57 //56.81 units per 5 degrees, .088 unit per 1 degree


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
extern void initDynos(int16_t * wristVertPos, int16_t * wristHoriPos, int16_t * elbowVertPos, int16_t * elbowHoriPos, int16_t * basePos);

//resets the arm control struct
extern void resetStruct(struct arm_control_struct * armData);

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


////////////////motor control functions///////////////////////////////////////////////////////////////////

//In order to move the motors forward, you set the first line high and the second line low
extern void setForward(uint32_t l1Base, uint8_t l1Pin, uint32_t l2Base, uint8_t l2Pin);

//In order to move the motors backward, you set the first line low and the second line high
extern void setReverse(uint32_t l1Base, uint8_t l1Pin, uint32_t l2Base, uint8_t l2Pin);

//In order to stop the motors, you set both of the lines low
extern void setStop(uint32_t l1Base, uint8_t l1Pin, uint32_t l2Base, uint8_t l2Pin);

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

