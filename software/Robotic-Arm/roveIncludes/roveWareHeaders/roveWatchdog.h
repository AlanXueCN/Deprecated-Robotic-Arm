// roveWatchdog.h

#pragma once

#ifndef ROVEWATCHDOG_H_
#define ROVEWATCHDOG_H_

// globally scoped Texas Instruments (TI) headers

#include "../RoboticArmMain.h"

// MRDesign Team::roveWare::        roveCom and RoveNet services headers

#include "../roveWare.h"

Void roveWatchdogCallback(UArg watchdog_handle);

Watchdog_Handle init_watchdog(UInt watchdog_hardware_index);

#endif // ROVEWATCHDOG_H_
