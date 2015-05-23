//roveWatchdog.c MST MRDT 2015
//
// Owen Chiaventone omc8db@mst.edu
//
// Connor Walsh cwd8d@mst.edu
//
// Judah Schad jrs6w7@mst.edu

//TODO change value of timer in EK.C

#include "../roveWareHeaders/roveWatchdog.h"
/*
Watchdog_Handle init_watchdog(UInt watchdog_hardware_index) {

    Watchdog_Handle watchdog_handle;
    Watchdog_Params watchdog_params;

    //init Watchdog
    Watchdog_Params_init(&watchdog_params);

    //watchdog_params.callbackFxn = roveWatchdogCallback;
    //watchdog_params.resetMode = Watchdog_RESET_ON;
    watchdog_params.resetMode = Watchdog_RESET_OFF;

    watchdog_handle = Watchdog_open(watchdog_hardware_index, &watchdog_params);
    if (watchdog_handle == NULL) {
        System_abort("Error opening UART Watchdog!\n");
    }
    return watchdog_handle;

} //endfnct init_uart(UInt uart_index, UInt baud_rate)

// Watchdog interrupt callback function
Void roveWatchdogCallback(UArg watchdog_handle) {

    dynamixelSetSpeedRightCmd(WRIST_A_ID, ZERO_SPEED);
    dynamixelSetSpeedRightCmd(WRIST_B_ID, ZERO_SPEED);
    dynamixelSetSpeedRightCmd(ELBOW_A_ID, ZERO_SPEED);
    dynamixelSetSpeedRightCmd(ELBOW_B_ID, ZERO_SPEED);
    dynamixelSetSpeedRightCmd(BASE_ID, ZERO_SPEED);
    dynamixelSetSpeedRightCmd(GRIPPER_ID, ZERO_SPEED);
    setLinActuatorCmd(LIN_ACT_ID, ZERO_SPEED);
    setDrillCmd(DRILL_ID, ZERO_SPEED);

    System_printf("BOOM Watchdog\n");
    System_flush();

    System_flush();

    Watchdog_clear( (Watchdog_Handle) watchdog_handle);

} //endfnctn roveWatchdogCallback
*/
