/*dynamixel.h
 programmer: Drue
 v1 -- 2/11/15
 created on 1/22/15
 */

#ifndef DYNAMIXEL_H_
#define DYNAMIXEL_H_

#include <stdint.h>
#include "driverlib/uart.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"

#define START_BYTE					0xFF
#define MOVE_LENGTH 				0x05
#define WRITE_DATA 					0x03
#define GOAL_POS_L 					0x1E
#define CURRENT_POSITION_L			0x24
#define MOVING_REGISTER 			0X2E
#define READ_LEN 					0x04
#define READ_DATA				    0x02
#define CW_ANGLE_LIMIT_L 			0X06
#define MOVING_SPEED_L 				0X20
#define GLOBAL_ID 					0xFE
#define	TX_MODE 					1
#define RX_MODE 					0
#define TIME_OUT	 				10
#define POS_FALSE_READ				0xFFFF
#define DELAY 						5

#ifndef DYNO_CLOCKWISE //already declared as ints in a couple previous versions, so guard against double declaration
#define DYNO_CLOCKWISE 1536;  //input number to set the dynamixel moving clockwise at half of max speed while in wheel mode
#endif

#define TURN_CLOCKWISE 1
#define TURN_COUNTERCLOCKWISE 0

int8_t error_byte; //byte used as error object

#ifndef DYNO_COUNTERCLOCKWISE
#define DYNO_COUNTERCLOCKWISE 512;
#endif

extern void dynoWheelModeSet(uint32_t uart, uint8_t id);
extern void dynoMultiModeSet(uint32_t uart, uint8_t id);
extern void dynoSpeedSet(uint32_t uart, uint8_t id, uint16_t speed);
extern void dynoMove(uint32_t uart, uint8_t id, int16_t pos);
extern int16_t dynoReadPosition(uint32_t uart, uint8_t id);
/*v Servomotor rotates to the right or left and the speed indicated only if in continuous rotation mode. v*/
extern void dynoTurn(uint32_t uart, uint8_t id, bool side, uint16_t Speed);
extern void switchCom(bool i);
extern void delay(int time);
extern void clearRxBuffer(uint32_t uart);
#endif

/*  write package: start, start, ID, length, instruction (which operation yon be doing), param 1: starting register address, other parameters...checksum
*   CS for write is ~ ( ID + Length + Instruction + Parameter1 + … Parameter N )
*   length is N (amount of parameters) + 3
*
*  return package (when didn't ask dyno to return any specific value with read function): start, start, ID, length, errors, CS
*  Check Sum = ~ ( ID + Length + Error + Parameter1 + … Parameter N )
*  return package (from read function): S, S, ID, L, Errors, parameters (what the data you asked for is), CS
*
* return package is sent after most functions, unless you iniate the command to talk to all dyno's at once (use ID Of 0XFE)
*
* read function has parameters of (address, length of data to be read)
*/

