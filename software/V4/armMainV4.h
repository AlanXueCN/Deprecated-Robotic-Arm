/*
 * armMainV4.h
 * date of birth: 1-22-15
 * date of update: 2-11-15
 *
 * What do you call all the enemies of the mars rover?
 * Dead, that's what. #theMarsRemembers
 */

#ifndef ARMMAIN_H_
#define ARMMAIN_H_

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
extern void resetStruct(struct RECEIVE_DATA_STRUCTURE * receiveData);

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


#endif /* ARMMAIN_H_ */




//main summary:

/*Here we control the arm movement for the rover. The overhead process goes: our arm waits in place until the user pushes
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
