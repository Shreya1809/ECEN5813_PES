
#ifndef UART_H_
#define UART_H_

void UART_configure ();
void UART_send (uint8_t* data);
void UART_send_n (uint8_t* data , uint8_t length);
void UART_receive(uint8_t* data );
void UART_receive_n ( uint8_t* data, uint8_t length);
void UART0_IRQHandler();

#endif
