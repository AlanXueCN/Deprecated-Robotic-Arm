/*
 * dynamixel.h
 *
 *  Created on: Apr 26, 2015
 *      Author: mrdtdev
 */

#ifndef DYNAMIXEL_H_
#define DYNAMIXEL_H_

//Standard headers
#include "Robotic-arm.h"

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
#define ID_LENGTH					0x4

//////////////////////////////////instructions//////
#define INST_PING                     0x01
#define INST_READ_DATA                0x02
#define INST_WRITE_DATA               0x03
#define INST_REG_WRITE                0x04
#define INST_ACTION                   0x05
#define INST_RESET                    0x06
#define INST_SYNC_WRITE               0x83


///////////////////////other//////////////////////
#define GLOBAL_ID 					0xFE
#define START_BYTE					0xFF
#define	TX_MODE 					1  //These two words are for the tristate buffer that most dynamixel data lines reccomend
#define RX_MODE 					0  //using, switching between tx and rx on a single data line
#define TIME_OUT	 				10
#define POS_FALSE_READ				0xFFFF//the word sent back if readPosition fails. -1 doesnt work as that's a position value

// Sets a dynamixel to a specific speed
void DynamixelSetSpeed(UART_Handle, uint8_t id, int16_t speed);

// Sets a dynamixel to a specific angle
void DynamixelSetAngle(UART_Handle, uint8_t id, int16_t angle);

#endif /* DYNAMIXEL_H_ */
