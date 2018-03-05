/**
 * @file uart.h
 * @brief uart library for KL25Z
 * @author Shreya Chakraborty
 * @author Miles Frain
 * @version 1
 * @date 2018-02-21
 */

#include"MKL25Z4.h"
#include "circbuf.h"

#ifndef __UART_H__
#define __UART_H__

/* Todo BAUD rate calculation macro
 * See section 39.2.1 of KL25 reference manual
 *
 * "The 13 bits in SBR[12:0] are referred to collectively as BR, and
 * they set the modulo divide rate for the baud rate generator. When
 * BR is 1 - 8191, the baud rate equals baud clock / ((OSR+1) ×
 * BR)."
 */


#define UART_OVERSAMPLING 16
#define BAUDRATE_ERROR  (-1)
#define NULL_POINTER_ERROR (-1)
//#define UART_S1_TDRE_MASK (0x80)
//#define UART_S1_RDRF_MASK (0x20)
//#define UART_S1_TC_MASK    (0x40)

typedef enum BAUD_RATE
{
	BAUD_115200 = 115200,
	BAUD_38400 	= 38400,
	BAUD_57200	= 57200,
	BAUD_9600	= 9600,

}BAUDRATE;

extern cb_struct *rx_buffer;
extern cb_struct *tx_buffer;

int8_t UART_configure(BAUDRATE baudselect);
void UART_send(uint8_t data);
void UART_send_n(uint8_t* data, size_t length);
void UART_receive(uint8_t* data);
void UART_receive_n(uint8_t* data, size_t length);
void UART0_IRQHandler();

#endif //__UART_H__
