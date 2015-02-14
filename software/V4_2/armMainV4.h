/*
 * armMainV4.h
 * date of birth: 1-22-15
 * date of update: 2-11-15
 *
 * What do you call all the enemies of the mars rover?
 * Dead, that's what. #theMarsRemembers
 */

#ifndef ARMMAINV4_H_
#define ARMMAINV4_H_

#define UART_MOTHER UART2_BASE
#define UART_ENDE	UART3_BASE
#define UART_DYNO   UART1_BASE

//.c's are included becuase often CCS wont know where to find source files when transferring projects
#include "inc\hw_memmap.h"
#include "inc\hw_types.h"
#include "driverlib\gpio.h"
#include "driverlib\gpio.c"
#include "driverlib\sysctl.h"
#include "driverlib\uart.h"
#include "utils\uartstdio.h"
#include "struct_xfer.h"
#include "driverlib\pin_map.h"
#include "driverlib\interrupt.c"
#include "driverlib\cpu.c"
#include "driverlib\uart.c"
#include "driverlib\sysctl.c"
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

//Initializes the hardware. Sets the clock to 16 mhz, the 3 UART modules up -- motherboard and endefector with
//115200 buad rates, dynomixel line with 57600 -- with 1 stop bit and no pariety, and initialize all of the pins that we use
//and setup most to transmit to output, ones used for UART aside.
extern void initHardware();

//Initializes the dynamixels. Moves them to their initial positions, initializes the position variables. Sets them to
//multi turn mode for now.
extern void initDynos(int16_t * wristVertPos, int16_t * wristHoriPos, int16_t * elbowVertPos, int16_t * elbowHoriPos, int16_t * basePos);

//resets the struct used to keep track of commands sent from motherboard
extern void resetStruct(struct arm_data_struct * armData);

extern void delay(int time); //delay is imprecise; ti's own delay function previously caused errors so this is a substitute.
//Needs to be tweaked if more precision is needed




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


#endif /* ARMMAINV4_H_ */

