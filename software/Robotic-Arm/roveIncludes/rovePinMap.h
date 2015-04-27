/*
 * rovePinMap.h
 *
 *  Created on: Apr 26, 2015
 *      Author: mrdtdev
 */

#ifndef ROVEPINMAP_H_
#define ROVEPINMAP_H_

/*
 * UARTS
 *
 * UART_DYNAMIXEL: 		UART 1: 	TX PC4
 * 									RX PC5
 * UART_MOTHERBOARD:	UART 2:		TX PD7
 * 									RX PD6
 * UART_ENDEFFECTOR:	UART 3:		TX PC7
 * 									RX PC6
 * UART_ACTUATOR		UART 4:		TX PE1
 * 									RX PE0
 */
#define UART_DYNAMIXEL  		UART1_BASE
#define UART_MOTHERBOARD	    UART2_BASE
#define UART_ENDEFFECTOR		UART3_BASE
#define UART_ACTUATOR 			UART7_BASE

/*
 * GPIO
 */

#endif /* ROVEPINMAP_H_ */
