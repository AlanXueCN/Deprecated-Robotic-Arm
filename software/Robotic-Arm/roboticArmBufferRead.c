// roboticArmBufferRead.c 2015

#include "roveIncludes/roveWareHeaders/roboticArmBufferRead.h"

// BIOS_start in main inits this as the roboticBufferReadTask Thread

//this is a roboticArm.cfg object::roboticArmTask::priority 1,
//768 persistent private stack, vital_flag = t,

#define MAX_COMMAND_SIZE 40

#define FOREVER 1

void roboticArmBufferRead(UArg arg0, UArg arg1)
{
    System_printf("roboticArmBufferRead init \n\n\n");
    System_flush();

    extern UART_Handle uart2;
    extern UART_Handle uart3;
    extern UART_Handle uart4;
    extern UART_Handle uart7;

    char messageBuffer[MAX_COMMAND_SIZE];

    while(FOREVER){

        recvSerialStructMessage(MOTHERBOARD_UART, messageBuffer);

        Mailbox_post(fromMobMailbox, messageBuffer, BIOS_WAIT_FOREVER);

    }//endwhile FOREVER

}//endfnct task roboticArmBufferRead
