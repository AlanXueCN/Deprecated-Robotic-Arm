// roveStructs.h 2015

// roveWare comtainer definitions

#pragma once

#ifndef ROVESTRUCTS_H_
#define ROVESTRUCTS_H_

// globally scoped Texas Instruments (TI) headers

#include "../RoboticArmMain.h"

// MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "../roveWare.h"

//TODO why are why typedf the msg pointer here?

typedef struct message_struct{

	//uint8_t value[BUFFER_SIZE];
	uint8_t struct_id;
	uint8_t value[30];

}__attribute__((packed)) message_struct, *msg;

typedef struct speed_struct{

	uint8_t struct_id;
	int16_t speed;

}__attribute__((packed)) speed_struct;

typedef struct set_dyna_speed_struct{

	uint8_t start_byte1;
	uint8_t start_byte2;

	// arg0
	uint8_t dynamixel_id;

	//message
	uint8_t msg_size;
	uint8_t read_write_flag;

	//address of low byte
	uint8_t speed_low_byte_reg_addr;
	uint8_t speed_low_byte;
	uint8_t speed_high_byte;
	uint8_t check_sum;

}__attribute__((packed)) set_dyna_speed_struct;


typedef struct set_dyna_endless_struct{

	uint8_t start_byte1;
	uint8_t start_byte2;

	// arg0
	uint8_t dynamixel_id;

	//message
	uint8_t msg_size;
	uint8_t read_write_flag;

	//address of low byte
	uint8_t ccw_angle_limit_reg_addr;
	uint8_t ccw_angle_limit_low_byte;
	uint8_t ccw_angle_limit_high_byte;
	uint8_t check_sum;

}__attribute__((packed)) set_dyna_endless_struct;


//min position is 0x000	max position is 0xFFF
typedef struct linear_actuator_struct{

	//address of low byte
	uint8_t target_low_byte;
	uint8_t target_high_byte;

	//tracked
	int16_t current_position;

	// arg0
	int16_t target_position;

}__attribute__((packed)) linear_actuator_struct;


#endif /* ROVESTRUCTS_H_ */
