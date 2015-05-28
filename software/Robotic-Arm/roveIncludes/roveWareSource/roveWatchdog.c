//roveWatchdog.c MST MRDT 2015
//
// Owen Chiaventone omc8db@mst.edu
//
// Connor Walsh cwd8d@mst.edu
//
// Judah Schad jrs6w7@mst.edu

//TODO change value of timer in EK.C

#include "../roveWareHeaders/roveWatchdog.h"

Void roveWatchdogCallback(UArg watchdog_handle)
{
	return;
}

Watchdog_Handle init_watchdog(UInt watchdog_hardware_index)
{
	Watchdog_Params params;
	Watchdog_Handle watchdog;

	Watchdog_Params_init(&params);
	params.callbackFxn = roveWatchdogCallback;
	params.resetMode = Watchdog_RESET_ON;

	watchdog = Watchdog_open(watchdog_hardware_index, &params);
	if (watchdog == NULL) {
			System_abort("Error opening Watchdog!\n");
	}
}

