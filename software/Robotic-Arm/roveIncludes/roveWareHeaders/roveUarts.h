/*
 * roveUarts.h
 *
 *  Created on: Apr 27, 2015
 *      Author: mrdtdev
 */

#pragma once

#ifndef ROVEUARTS_H_
#define ROVEUARTS_H_

// globally scoped Texas Instruments (TI) headers

#include "../RoboticArmMain.h"

// MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "../roveWare.h"

UART_Handle init_uart( UInt uart_index, UInt baud_rate );

#endif /* ROVEUARTS_H_ */
