//	TODO: Port To Fresh Build (using TI example:			This version educational practice not for distro)

// RoverMotherboardMain.h
//
// first created:
//
// 02_24_2015_Judah Schad_jrs6w7@mst.edu
//
// last edited:
//
//02_25_2015_Judah Schad_jrs6w7@mst.edu
//
//this implements global scope for header files

#pragma once

#ifndef ROBOTICARMMAIN_H_
#define ROBOTICARMMAIN_H_

//Globally Referencing:

//C lib

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

//CCS TI config

#include <xdc/std.h>

#include <xdc/cfg/global.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

//CCS TI operating system

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>


//TI hardware access routines

#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
//#include <ti/drivers/PWM.h>
#include <ti/drivers/Watchdog.h>


//TI BIOS hardware drivers

#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "inc/hw_memmap.h"
#include "driverlib/watchdog.h"

//defines target device

#include "tiHardware/Board.h"

//CCS TI NDK BSD support

//#include <sys/socket.h>

//TI Mailbox() BIOS software routine support

#include <ti/sysbios/knl/Mailbox.h>

/* OWEN HAD THESE

// XDCtools Header files
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>

// BIOS Header files
#include <ti/sysbios/BIOS.h>

// TI-RTOS Header files
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

// Example/Board Header files
#include "Board.h"

#include <stdint.h>
 */

#endif // ROBOTICARMMAIN_H_
