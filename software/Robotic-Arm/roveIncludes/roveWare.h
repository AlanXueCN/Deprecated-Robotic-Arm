// roveWare.h 2015

// roveWare driver configuration flex values

#pragma once

#ifndef ROVEWARE_H_
#define ROVEWARE_H_

#include "roveWareHeaders/roveDynamixel.h"
#include "roveWareHeaders/roveHardwareAbstraction.h"
#include "roveWareHeaders/rovePinMap.h"
#include "roveWareHeaders/roveStructs.h"
#include "roveWareHeaders/roveTiming.h"
#include "roveWareHeaders/roveUarts.h"

#define LOW 0
#define HIGH 1

#define SET_TRI_ST_BUF_Tx 0

#define DYNAMIXEL_UART 0
#define LINEAR_ACTUATOR_UART 1
#define MOTHERBOARD_UART 2

#define SET_ENDLESS_CMD 0
#define SET_SPEED_LEFT_CMD	1
#define SET_SPEED_RIGHT_CMD	2
#define SET_LIN_ACTUATOR_CMD 3

#define WRIST_A_ID  0x01
#define WRIST_B_ID	0x02
#define ELBOW_A_ID	0x03
#define ELBOW_B_ID	0x04
#define BASE_ID		0x05
#define LIN_ACT_ID  0x06
#define MOB_ID 		0x07

#define MIN_LIN_ACT_POSITION 0
#define MAX_LIN_ACT_POSITION 4095

// robot arm values

//deprecated in favor of variable speed

#define	robot_arm_contant_speed_id 200

// clockwise is positive, counter clockwise is negative

#define wrist_clock_wise 201
#define wrist_up 202
#define elbow_clock_wise 203
#define elbow_up 204
#define base_clock_wise 205
#define e_stop_arm 206
#define actuator_increment 207

// gripper values

#define gripper_open 220
#define drill 221

// telem_device_id

#define	telem_req_id 254

#define	robot_arm_telem_req_id 0
#define	gripper_telem_req_id 1
#define	drill_telem_req_id 2

//TODO wtf uint8_t value[30] vs  uint8_t value[MAX_DYNAMIXEL_MSG_SIZE]in roveStructs.h ?
#define MAX_DYNAMIXEL_MSG_SIZE 30

#define LIN_DONT_PRINT_BYTES 4

//From Savage Electronics



//EEPROM AREA
#define AX_MODEL_NUMBER_L           0
#define AX_MODEL_NUMBER_H           1
#define AX_VERSION                  2
#define AX_ID                       3
#define AX_BAUD_RATE                4
#define AX_RETURN_DELAY_TIME        5
#define AX_CW_ANGLE_LIMIT_L         6
#define AX_CW_ANGLE_LIMIT_H         7
#define AX_CCW_ANGLE_LIMIT_L        8
#define AX_CCW_ANGLE_LIMIT_H        9
#define AX_SYSTEM_DATA2             10
#define AX_LIMIT_TEMPERATURE        11
#define AX_DOWN_LIMIT_VOLTAGE       12
#define AX_UP_LIMIT_VOLTAGE         13
#define AX_MAX_TORQUE_L             14
#define AX_MAX_TORQUE_H             15
#define AX_RETURN_LEVEL             16
#define AX_ALARM_LED                17
#define AX_ALARM_SHUTDOWN           18
#define AX_OPERATING_MODE           19
#define AX_DOWN_CALIBRATION_L       20
#define AX_DOWN_CALIBRATION_H       21
#define AX_UP_CALIBRATION_L         22
#define AX_UP_CALIBRATION_H         23

// RAM AREA
#define AX_TORQUE_ENABLE            24
#define AX_LED                      25
#define AX_CW_COMPLIANCE_MARGIN     26
#define AX_CCW_COMPLIANCE_MARGIN    27
#define AX_CW_COMPLIANCE_SLOPE      28
#define AX_CCW_COMPLIANCE_SLOPE     29
#define AX_GOAL_POSITION_L          30
#define AX_GOAL_POSITION_H          31
#define AX_GOAL_SPEED_L             32
#define AX_GOAL_SPEED_H             33
#define AX_TORQUE_LIMIT_L           34
#define AX_TORQUE_LIMIT_H           35
#define AX_PRESENT_POSITION_L       36
#define AX_PRESENT_POSITION_H       37
#define AX_PRESENT_SPEED_L          38
#define AX_PRESENT_SPEED_H          39
#define AX_PRESENT_LOAD_L           40
#define AX_PRESENT_LOAD_H           41
#define AX_PRESENT_VOLTAGE          42
#define AX_PRESENT_TEMPERATURE      43
#define AX_REGISTERED_INSTRUCTION   44
#define AX_PAUSE_TIME               45
#define AX_MOVING                   46
#define AX_LOCK                     47
#define AX_PUNCH_L                  48
#define AX_PUNCH_H                  49

    // Status Return Levels ///////////////////////////////////////////////////////////////
#define AX_RETURN_NONE              0
#define AX_RETURN_READ              1
#define AX_RETURN_ALL               2

    // Instruction Set ///////////////////////////////////////////////////////////////
#define AX_PING                     1
#define AX_READ_DATA                2
#define AX_WRITE_DATA               3
#define AX_REG_WRITE                4
#define AX_ACTION                   5
#define AX_RESET                    6
#define AX_SYNC_WRITE               131

	// Specials ///////////////////////////////////////////////////////////////


//TODO		#define these to make sense in rove so english


#define OFF                         0
#define ON                          1
#define LEFT						0
#define RIGHT                       1
#define AX_BYTE_READ                1
#define AX_BYTE_READ_POS            2
#define AX_RESET_LENGTH				2
#define AX_ACTION_LENGTH			2
#define AX_ID_LENGTH                4
#define AX_LR_LENGTH                4
#define AX_SRL_LENGTH               4
#define AX_RDT_LENGTH               4
#define AX_LEDALARM_LENGTH          4
#define AX_SALARM_LENGTH            4
#define AX_TL_LENGTH                4
#define AX_VL_LENGTH                6
#define AX_CM_LENGTH                6
#define AX_CS_LENGTH                6
#define AX_CCW_CW_LENGTH            8
#define AX_BD_LENGTH                4
#define AX_TEM_LENGTH               4
#define AX_MOVING_LENGTH            4
#define AX_RWS_LENGTH               4
#define AX_VOLT_LENGTH              4
#define AX_LED_LENGTH               4
#define AX_TORQUE_LENGTH            4
#define AX_POS_LENGTH               4
#define AX_GOAL_LENGTH              5
#define AX_MT_LENGTH                5
#define AX_PUNCH_LENGTH             5
#define AX_SPEED_LENGTH             5
#define AX_GOAL_SP_LENGTH           7
#define AX_ACTION_CHECKSUM			250
#define BROADCAST_ID                254
#define AX_START                    255
#define AX_CCW_AL_L                 255
#define AX_CCW_AL_H                 3
#define TIME_OUT                    10         // Este parametro depende de la velocidad de transmision
#define TX_DELAY_TIME				400        // Este parametro depende de la velocidad de transmision - pero pueden ser cambiados para mayor velocidad.
#define TX_MODE                     1
#define RX_MODE                     0
#define LOCK                        1

#endif /* ROVEWARE_H_ */
