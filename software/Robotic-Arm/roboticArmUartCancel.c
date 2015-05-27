// roboticArmBufferRead.c 2015

#include "roveIncludes/roveWareHeaders/roboticArmUartCancel.h"

// BIOS_start in main inits this as the roboticBufferReadTask Thread

//this is a roboticArm.cfg object::roboticArmTask::priority 1,
//768 persistent private stack, vital_flag = t,

void roboticArmUartCancel(UArg arg0, UArg arg1)
{
    System_printf("roboticArmUartCancel init \n\n\n");
    System_flush();

    extern UART_Handle uart2;
    extern UART_Handle uart3;
    extern UART_Handle uart4;
    extern UART_Handle uart7;

    extern uint32_t UART_READ_RETURNED_FLAG;

    while(FOREVER){

        UART_READ_RETURNED_FLAG = 0;

        Task_sleep(UART_CANCEL_DELAY_TICKS);

        if(UART_READ_RETURNED_FLAG == 0)
        {
            UART_readCancel(uart2);

            dynamixelSetSpeedLeftCmd(WRIST_A_ID, ZERO_SPEED);
            dynamixelSetSpeedLeftCmd(WRIST_B_ID, ZERO_SPEED);
            dynamixelSetSpeedLeftCmd(ELBOW_A_ID, ZERO_SPEED);
            dynamixelSetSpeedLeftCmd(ELBOW_B_ID, ZERO_SPEED);
            dynamixelSetSpeedLeftCmd(BASE_ID, ZERO_SPEED);
            dynamixelSetSpeedLeftCmd(GRIPPER_ID, ZERO_SPEED);
            setDrillCmd(DRILL_ID, ZERO_SPEED);
            setLinActuatorCmd(LIN_ACT_ID, ZERO_SPEED);

        }//end if

    }//endwhile FOREVER

}//endfnct task roboticArmUartCancel
