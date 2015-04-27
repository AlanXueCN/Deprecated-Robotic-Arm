//Robot Arm Main.c
//
// Using Texas Instruments Code Composer Studio RTOS stack. See read me include for copyright
//
// first created:
//
// 04_26_2015_Owen_Chiaventone omc8db
//
// last edited:
//
// 04_26_2015_Judah Schad_jrs6w7@mst.edu
//
// this instatiates global handles, initializes TI modules and then calls the TI BIOS operating system
//
// TI BIOS operating system instatiates the roveTCPHandler, roveCmdCntrl, and roveTelemCntrl threads

// includes globally scoped Texas Instruments (TI) header files

#include "roveIncludes/RoboticArmMain.h"

// MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "roveIncludes/roveWare.h"

// globally create UART handles

//UART_Handle DynamixelUart;

int main(void){

    /* Call board init functions
    //Board_initGeneral();
    //Board_initGPIO();
    //Board_initUART();

    //Grab our dynamixelUart
    //DynamixelUart = uartOpen()


    // This example has logging and many other debug capabilities enabled
    System_printf("This example does not attempt to minimize code or data "
                  "footprint\n");
    System_flush();

    System_printf("Starting the UART Echo example\nSystem provider is set to "
                  "SysMin. Halt the target to view any SysMin contents in "
                  "ROV.\n");
    // SysMin will only print to the console when you call flush or exit
    System_flush();

    // Start BIOS
    //BIOS_start();
*/
    return (0);

}//end main

