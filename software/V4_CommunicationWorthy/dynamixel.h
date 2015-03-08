/*dynamixel.h
 programmer: Drue
 v1 -- 2/11/15
 created on 1/22/15
 */

#ifndef DYNAMIXEL_H_
#define DYNAMIXEL_H_

#include <stdint.h>
#include "driverlib\uart.h"
#include "inc\hw_memmap.h"
#include "driverlib\gpio.h"

///////////////////////EEPROM registers//////////////////
#define MODEL_NUMBER_L 				0x00
#define MODEL_NUMBER_H				0x01
#define FIRMWARE					0x02
#define ID_REGISTER					0x03
#define BAUD_REGISTER				0X04
#define	RETURN_DELAY_REGISTER		0x05
#define CW_ANGLE_LIMIT_L 			0X06
#define CCW_ANGLE_LIMIT_L 			0x08
#define TEMP_LIM_REGISTER			0x0B
#define	VOLT_LIM_LOW				0x0C
#define VOLT_LIM_HIGH				0x0D
#define MAX_TORQUE_L				0x0E
#define STATUS_RETURN_LEVEL 		0x10
#define ALARM_LED_REGISTER			0x11
#define ALARM_SHUTDOWN_REGISTER		0x12
#define MULTITURN_OFFSET_L			0x14
#define RESOLUTION_DIVIDER_REGISTER	0x16

////////////////////RAM registers/////////
#define TORQUE_ENABLE				0x18
#define LED_ENABLE					0x19
//1A-1C are PID related, not touching them. 1D undefined
#define GOAL_POS_L 					0x1E
#define MOVING_SPEED_L 				0X20
#define TORQUE_LIM_L				0x22
#define PRESENT_POSITION_L			0x24
#define PRESENT_SPEED_L				0x26
#define PRESENT_LOAD_L				0x28
#define PRESENT_VOLTAGE				0x2A
#define PRESENT_TEMPERATURE			0x2B
#define REGISTERED_REGISTER			0x2C//just roles off the tongue, dont it
#define MOVING_REGISTER				0X2E
#define	LOCK_EEPROM_REGISTER		0x2F
#define PUNCH_L						0x30
#define CURRENT_L					0x44
#define TORQUE_CONTROL_ENABLE		0x46
#define GOAL_TORQUE_L				0x47
#define GOAL_ACCELERATION			0x49

/////////////////////////////////////package lengths////////
#define READ_LEN 					0x04
#define MOVE_LENGTH 				0x05
#define RESET_LENGTH				0x02
#define PING_LENGTH					0x02

//////////////////////////////////instructions//////
#define INST_PING                     1
#define INST_READ_DATA                2
#define INST_WRITE_DATA               3
#define INST_REG_WRITE                4
#define INST_ACTION                   5
#define INST_RESET                    6
#define INST_SYNC_WRITE               131


///////////////////////other//////////////////////
#define GLOBAL_ID 					0xFE
#define START_BYTE					0xFF
#define	TX_MODE 					1  //These two words are for the tristate buffer that most dynamixel data lines reccomend
#define RX_MODE 					0  //using, switching between tx and rx on a single data line
#define TIME_OUT	 				10
#define POS_FALSE_READ				0xFFFF//the word sent back if readPosition fails. -1 doesnt work as that's a position value
#define DELAY 						5




#ifndef DYNO_CLOCKWISE //already declared as const int vars in a couple previous versions, so guard against overriding them.
#define DYNO_CLOCKWISE 1536;  //input number to set the dynamixel moving clockwise at half of max speed while in wheel mode
#endif

int8_t error_byte; //byte used as error object

#ifndef DYNO_COUNTERCLOCKWISE
#define DYNO_COUNTERCLOCKWISE 512;
#endif

extern void dynoWheelModeSet(uint32_t uart, uint8_t id);
extern void dynoMultiModeSet(uint32_t uart, uint8_t id);
extern void dynoSpeedSet(uint32_t uart, uint8_t id, uint16_t speed);
extern void dynoMove(uint32_t uart, uint8_t id, int16_t pos);
extern int16_t dynoReadPosition(uint32_t uart, uint8_t id);
extern void switchCom(bool i);//note that this one is hardware specific and will need changing depending on device and setup
extern void delay(int time);
extern void clearRxBuffer(uint32_t uart);
extern void dynoReset(uint32_t uart, uint8_t id);
extern void dynoPing(uint32_t uart, uint8_t id);
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

