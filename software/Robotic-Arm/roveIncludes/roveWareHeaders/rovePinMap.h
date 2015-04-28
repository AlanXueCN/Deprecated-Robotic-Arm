///
 // rovePinMap.h
 //
 //  Created on: Apr 26, 2015
 //      Author: mrdtdev
 ///

#pragma once

#ifndef ROVEPINMAP_H_
#define ROVEPINMAP_H_


// includes globally scoped Texas Instruments (TI) header files

// globally scoped Texas Instruments (TI) headers

#include "../RoboticArmMain.h"

// MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "../roveWare.h"



//		UART 0:   TX PA1, RX PA0
// 		UART 1:   TX PB1, RX PB0
//
// 		UART 2:   TX PD7, RX PD6  MOTHERBOARD_UART
//
// 		UART 3:   TX PC7, RX PC6  END_EFFECTOR_UART
// 		UART 4:   TX PC5, RX PC4  DYNAMIXEL_UART
// 		UART 5:   TX PE5, RX PE4
// 		UART 6:   TX PD5, RX PD4
// 		UART 7:   TX PE1, RX PE0  LINEAR_ACTUATOR_UART


// GPIO
//
// DATA_FLOW_CTRL_1: 	DC_1:		PB3
// MOTOR_CONTROLLER_ENABLE:			PD2
// MOTOR_CONTROLLER_INPUT_1			PD3
// MOTOR_CONTROLLER_INPUT_2			PE2


#endif // ROVEPINMAP_H_
