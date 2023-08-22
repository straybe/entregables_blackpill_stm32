/*
 * edx_xprintf.c
 *
 *  Created on: Jul 20, 2022
 *      Author: edx
 */
#include "edx_xprintf.h"

 void uart_xprintf_write(int byte){
	HAL_UART_Transmit(UART_XPRINTF, (uint8_t *)&byte, 1, 100);
	}

extern void xprintf_init(void){
	  xdev_out(uart_xprintf_write);
}

void xprint_clear(void){
	xprintf("\r\x1b[2J\r");
}
