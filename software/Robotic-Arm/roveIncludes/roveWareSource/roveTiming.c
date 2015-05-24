//MRDesign Team::roveWare::		encapsulates the system control call to delay a given number of milliseconds

#include "../roveWareHeaders/roveTiming.h"

//encapsulates the system control call to delay a given number of milliseconds

void ms_delay(int milliseconds){

	SysCtlDelay( milliseconds*(SysCtlClockGet() / 100) );

}//endfnctn ms_delay( int milliseconds )

void us_delay(int microseconds){

    SysCtlDelay(  microseconds*( SysCtlClockGet() / 100000 ) );

}//endfnctn ms_delay( int milliseconds )
