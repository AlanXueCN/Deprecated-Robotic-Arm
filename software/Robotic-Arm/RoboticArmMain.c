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

// globally create UART handles

	//UART_Handle uart0;
    //UART_Handle uart1;
    UART_Handle uart2;		//PD7 MOTHERBOARD_UART 115200
    UART_Handle uart3;		//PC7 END_EFFECTOR_UART 9600
    UART_Handle uart4;		//PC5 DYNAMIXEL_UART 57600
    //UART_Handle uart5;
    //UART_Handle uart6;
    UART_Handle uart7;		//PE1 LINEAR_ACTUATOR_UART 115200


int main(void){

    //Call board init functions
    Board_initGeneral();
    Board_initGPIO();

    System_printf("Init uarts\n");
    System_flush();

    Board_initUART();


    //init UARTS

	System_printf("Assign UARTS\n");
	System_flush();

	// not utilizing uart0 or uart1 (no mob to pins)

	//uart0 = (UART_Handle)init_uart( 0, 115200 );

	//System_printf("Assigned UART 0\n");
	//System_flush();


	//uart1 = (UART_Handle)init_uart( 1, 115200 );

	//System_printf("Assigned UART 1\n");
	//System_flush();

	uart2 = (UART_Handle)init_uart( 2, 115200 );

	System_printf("Assigned UART 2\n");
	System_flush();

	uart3 = (UART_Handle)init_uart( 3, 9600 );

	System_printf("Assigned UART 3\n");
	System_flush();

	uart4 = (UART_Handle)init_uart( 4, 57600 );

	System_printf("Assigned UART 4\n");
	System_flush();

	//uart5 = (UART_Handle)init_uart( 5, 115200 );

	//System_printf("Assigned UART 5\n");
	//System_flush();

	//uart6 = (UART_Handle)init_uart( 6, 115200 );

	//System_printf("Assigned UART 6\n");
	//System_flush();

	uart7 = (UART_Handle)init_uart( 7, 115200 );

	System_printf("Assigned UART 7\n");
	System_flush();

	// start TI BIOS
	System_printf("roveMotherboardMain init \n\n\n");
	System_flush();

    BIOS_start();

    return (0);

}//end main

