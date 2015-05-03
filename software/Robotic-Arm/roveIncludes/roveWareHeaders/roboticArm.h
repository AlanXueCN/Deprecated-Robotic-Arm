// roboticArm.h

#pragma once

#ifndef ROBOTICARM_H_
#define ROBOTICARM_H_

// globally scoped Texas Instruments (TI) headers

#include "../RoboticArmMain.h"

// MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "../roveWare.h"

void roboticArm(UArg arg0, UArg arg1);

void roboArmForwardCmd(uint8_t struct_id, int16_t speed, void* buffer_struct);

void roboArmReverseCmd(uint8_t struct_id, int16_t speed, void* buffer_struct);

#endif // ROBOTICARM_H_
