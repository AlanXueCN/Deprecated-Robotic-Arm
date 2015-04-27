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

	UART_Handle uart0;
    UART_Handle uart1;
    UART_Handle uart2;
    UART_Handle uart3;
    UART_Handle uart4;
    UART_Handle uart5;
    UART_Handle uart6;
    UART_Handle uart7;

//UART_Handle DynamixelUart;

int main(void){

    //Call board init functions
    Board_initGeneral();
    Board_initGPIO();

    System_printf("Init uarts\n");

    Board_initUART();

    //Grab our dynamixelUart
   //DynamixelUart = uartOpen()


    //init UARTS

	System_printf("Assign UARTS\n");

	// not utilizing uart0 or uart1 (no mob to pins)

	uart0 = (UART_Handle)init_uart( 0, 115200 );
	uart1 = (UART_Handle)init_uart( 1, 115200 );
	uart2 = (UART_Handle)init_uart( 2, 115200 );
	uart3 = (UART_Handle)init_uart( 3, 115200 );
	uart4 = (UART_Handle)init_uart( 4, 115200 );
	uart5 = (UART_Handle)init_uart( 5, 115200 );
	uart6 = (UART_Handle)init_uart( 6, 115200 );
	uart7 = (UART_Handle)init_uart( 7, 115200 );

	// start TI BIOS

	System_printf("roveMotherboardMain init \n");
	System_printf("\n");
	System_printf("\n");
	System_flush();

    BIOS_start();

    return (0);

}//end main

