/*
 * roveStructTransfer.h
 *
 *  Created on: Apr 26, 2015
 *      Author: mrdtdev
 */

#pragma once

#ifndef ROVESTRUCTTRANSFER_H_
#define ROVESTRUCTTRANSFER_H_

// globally scoped Texas Instruments (TI) headers

#include "../RoboticArmMain.h"

// MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "../roveWare.h"

//deprecated in favor of variable speed

#define	robot_arm_id 200

// clockwise is positive, counter clockwise is negative

#define wrist_clock_wise 201
#define wrist_up 202
#define elbow_clock_wise 203
#define elbow_up 204
#define actuator_forward 205
#define base_clock_wise 206
#define e_stop_arm 207

// gripper values

#define gripper_open 220

// telem_device_id

#define	telem_req_id 254

#define	robot_arm_telem_req_id 0
#define	gripper_telem_req_id 1
#define	drill_telem_req_id 2
#define	bms_telem_req_id 3
#define	power_board_telem_req_id 4

#endif /* ROVESTRUCTTRANSFER_H_ */
