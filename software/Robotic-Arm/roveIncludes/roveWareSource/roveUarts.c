//MRDesign Team:: 	roveWare::		roveCom uart :: constructs and instatiates uarts

#include "../roveWareHeaders/roveUarts.h"

UART_Handle init_uart(UInt uart_index, UInt baud_rate){

	UART_Handle uart_handle;

	//for now uart params are declared here

	//TODO: move this into a parameter

	UART_Params uartParams;

	//init UART

	UART_Params_init(&uartParams);

	uartParams.readReturnMode = UART_RETURN_FULL;
	uartParams.readMode = UART_MODE_BLOCKING;
	uartParams.readEcho = UART_ECHO_OFF;
	uartParams.baudRate = baud_rate;

	uart_handle = UART_open(uart_index, &uartParams);

	//System_printf("SUCCESS ASSIGNING %d, %d\n", uart_index, baud_rate );
	//System_flush();

	if (uart_handle == NULL) {

		//System_printf("ERROR ASSIGNING %d\n", uart_index);
		//System_flush();

	}//endif

	return uart_handle;

}//endfnct init_uart(UInt uart_index, UInt baud_rate)

