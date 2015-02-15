/*
 * armMain.h
 *
 *  Created on: Jan 22, 2015
 *      Author: Drue
 */

#ifndef ARMMAIN_H_
#define ARMMAIN_H_

//#include <lm4f120h5qr.h>
#include "C:\StellarisWare\inc\hw_memmap.h"
#include "C:\StellarisWare\inc\hw_types.h"
#include "C:\StellarisWare\driverlib\gpio.h"
#include "C:\StellarisWare\driverlib\gpio.c"
#include "C:\StellarisWare\driverlib\sysctl.h"
#include "C:\StellarisWare\driverlib\uart.h"
#include "C:\StellarisWare\utils\uartstdio.h"
#include "struct_xfer.h"
#include "C:\StellarisWare\driverlib\pin_map.h"


#define DELAY 5
#define GPIO_PC4_U1RX           0x00021002
#define GPIO_PC5_U1TX           0x00021402
#define GPIO_PD6_U2RX           0x00031801
#define GPIO_PD7_U2TX           0x00031C01
#define GPIO_PC6_U3RX           0x00021801
#define GPIO_PC7_U3TX           0x00021C01
const short FORWARD_CHARACTER = 1;
const short REVERSE_CHARACTER = 1;
const int DYNO_CLOCKWISE = 1536;
const int DYNO_COUNTERCLOCKWISE = 512;

extern void reset(void);
extern void wristClockWise();
extern void wristCounterClockWise();
extern void wristUp();
extern void delay(int time);
extern void wristDown();
extern void elbowCounterClockWise();
extern void elbowClockWise();
extern void elbowDown();
extern void elbowUp();
extern void actuatorForward();
extern void actuatorReverse();
extern void baseClockWise();
extern void baseCounterClockWise();
extern void initHardware();
extern void resetStruct(struct RECEIVE_DATA_STRUCTURE * receiveData);
extern void setForward(uint32_t l1Base, uint8_t l1Pin, uint32_t l2Base, uint8_t l2Pin);
extern void setReverse(uint32_t l1Base, uint8_t l1Pin, uint32_t l2Base, uint8_t l2Pin);
extern void setStop(uint32_t l1Base, uint8_t l1Pin, uint32_t l2Base, uint8_t l2Pin);
#endif /* ARMMAIN_H_ */
