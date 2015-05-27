// roboticArmBufferRead.c 2015

#include "roveIncludes/roveWareHeaders/roboticArmBufferRead.h"

// BIOS_start in main inits this as the roboticBufferReadTask Thread

//this is a roboticArm.cfg object::roboticArmTask::priority 1,
//768 persistent private stack, vital_flag = t,


Void roboticArmBufferRead(UArg arg0, UArg arg1)
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

        //Throw out messages we can't deal with
        Mailbox_post(fromMobMailbox, messageBuffer, 500);

    }//endwhile FOREVER

}//endfnct task roboticArmBufferRead
