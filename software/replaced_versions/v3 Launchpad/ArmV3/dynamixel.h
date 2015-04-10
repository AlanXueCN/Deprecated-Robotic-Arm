/*dynamixel.h
 programmer: Drue
 v1 -- 1/23/15
 created on 1/22/15
 */

#ifndef DYNAMIXEL_H_
#define DYNAMIXEL_H_

#include <stdint.h>

#define START_BYTE 0xFF
#define MOVE_LENGTH 0x05
#define WRITE_DATA 0x03
#define GOAL_POS_L 0x1F
#define RETURN_PACKET_SIZE 6
#define ERROR_SLOT 4
#define MOVING_REGISTER 0X2E
#define READ_MOVING_BUFFER_SIZE 7
#define READ_INSTRUCTION_ARRAY_SIZE  8
#define READ_INSTRUCTION_LEN 0x04
#define READ_DATA 0x02
#define MOVE_ARRAY_SIZE
#define RETURNED_DATA_SLOT 5
#define CW_ANGLE_LIMIT_L 0X06
#define MOVING_SPEED_L 0X20
#define GLOBAL_ID 0xFE

//extern void moveDyno(uint8_t uart, uint8_t id, uint16_t pos);
//extern void readDyno(uint8_t uart, uint8_t id, uint8_t address, uint8_t * buffer);
extern void dynoWheelModeSet(uint32_t uart, uint8_t id);
extern void dynoSpeedSet(uint32_t uart, uint8_t id, int16_t speed);
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

