//Robot Arm Main.c
//
// Using Texas Instruments Code Composer Studio RTOS stack. See read me include for copyright
//
// 2015_Owen_Chiaventone_omc8db@mst.edu
// 2015_Judah_Schad_jrs6w7@mst.edu
// 2015_Connor_Walsh
//
// this instatiates global handles, initializes TI modules and then calls the TI BIOS operating system
//
// TI BIOS operating system instatiates the roveTCPHandler, roveCmdCntrl, and roveTelemCntrl threads

// includes globally scoped Texas Instruments (TI) header files

//MAIN:

#include "roveIncludes/RoboticArmMain.h"

// MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "roveIncludes/roveWare.h"

// globally create UART handles

    UART_Handle uart2;		//PD7 MOTHERBOARD_UART 115200
    UART_Handle uart3;		//PC7 END_EFFECTOR_UART 57600
    UART_Handle uart4;		//PC5 DYNAMIXEL_UART 57600
    UART_Handle uart7;		//PE1 LINEAR_ACTUATOR_UART 115200

// globally create watchdog handle

   // Watchdog_Handle arm_watchdog_handle;

int main(void)
{

    //Call board init functions
    Board_initGeneral();
    Board_initGPIO();

    //System_printf("Init Watchdog\n");
    //System_flush();

    //Board_initWatchdog();

    System_printf("Init uarts\n");
    System_flush();

    Board_initUART();

    //System_printf("Assign Watchdog\n");
    //System_flush();

    //arm_watchdog_handle = init_watchdog(0);

    //init UARTS
	System_printf("Assign UARTS\n");
	System_flush();

	uart2 = (UART_Handle)init_uart( 2, 115200 );
	System_printf("Assigned UART 2\n");
	System_flush();

	uart3 = (UART_Handle)init_uart( 3, 57600 );
	System_printf("Assigned UART 3\n");
	System_flush();

	uart4 = (UART_Handle)init_uart( 4, 57600 );
	System_printf("Assigned UART 4\n");
	System_flush();


	uart7 = (UART_Handle)init_uart( 7, 115200 );
	System_printf("Assigned UART 7\n");
	System_flush();

	// start TI BIOS
	System_printf("roboticArmMain init \n\n\n");
	System_flush();

    BIOS_start();

    return (0);

}//end main

