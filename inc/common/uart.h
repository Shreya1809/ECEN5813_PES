/**
 * @file uart.h
 * @brief uart library for KL25Z
 * @author Shreya Chakraborty
 * @author Miles Frain
 * @version 1
 * @date 2018-02-21
 */

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


void UART_configure();
void UART_send(uint8_t* data);
void UART_send_n(uint8_t* data, uint8_t length);
void UART_receive(uint8_t* data);
void UART_receive_n(uint8_t* data, uint8_t length);
void UART0_IRQHandler();

#endif //__UART_H__
