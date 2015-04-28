//MRDesign Team:: 	roveWare::		encapsulates the system control call to delay a given number of milliseconds

#pragma once

#ifndef ROVETIMING_H_
#define ROVETIMING_H_

// globally scoped Texas Instruments (TI) headers

#include "../RoboticArmMain.h"

// MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "../roveWare.h"

void ms_delay(int milliseconds);

#endif //ROVETIMING_H_
