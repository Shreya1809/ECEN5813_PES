#include "uart.h"
#include"MKL25Z4.h"
#include "circbuf.h"


cb_struct *rx_buffer = NULL;
cb_struct *tx_buffer = NULL;

int8_t UART_configure(BAUDRATE baudselect)
{
	if(baudselect != BAUD_115200 && baudselect != BAUD_38400 && baudselect != BAUD_57200 && baudselect != BAUD_9600)
			return BAUDRATE_ERROR;
	//selecting the FLL clock source for UART0
//	/SIM_SOPT2 |= 0x04000000;            // MCGFLLCLK clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL(0);

	//uart0 clock gate enable
	SIM->SCGC4 |= SIM_SCGC4_UART0(1); //set bit 10 for uart0

	SIM->SOPT5 |= SIM_SOPT5_UART0ODE(0);
	SIM->SOPT5 |= SIM_SOPT5_UART0RXSRC(0);
	SIM->SOPT5 |= SIM_SOPT5_UART0TXSRC(0);

	//UART0 RX/TX pin behavior and source
	//SIM_SOPT5 |= 0x04000000;    //UART0ODE,UART0RXSRC,UART0TXSRC bit fields set to 0
	UART0->C2 = 0;						//disabling uart 0 before configuration
	UART0->C1 |= UART_C1_M(0) | UART_C1_PE(0); //8 bit data, no parity
	UART0->BDH |= UART_BDH_SBNS(0);   //1 stop bit
	UART0->C4 |= UART0_C4_OSR(OSR); //setting OSR bit to 15
	//calculation for baud rate selection
	uint16_t SBR_val = (uint16_t)((((uint32_t)47939584)/(baudselect*16)) & 0x1FFF);
		UART0->BDL = UART_BDL_SBR(SBR_val);
		UART0->BDH |= UART_BDH_SBR(SBR_val>>8);

	//Enabling RIE Interrupt and the TCIE interrupt now.
	UART0->C2 |= UART_C2_RIE(1) | UART_C2_TCIE(1);

	//Enabling Rx and TX
	UART0->C2 |= UART_C2_RE(1) | UART_C2_TE(1);

	SIM_SCGC5 |= 0x00000200;            // enable clock for PORTA

	//Enabling the NVIC Interrupt for UART0
	//NVIC_EnableIRQ(UART0_IRQn);

	 PORTA_PCR1 |= 0x00000200;            // Select PTA1 as Receive pin
	 PORTA_PCR2 |= 0x00000200;            // Select PTA2 as Transmit pin

}
void UART_send(uint8_t data)
{
	__disable_irq();
	while(!(UART0->S1 & UART_S1_TDRE_MASK)); //Waiting for the buffer to get empty ie bit TDRE = 1
	UART0->D = data; //write data
	while(!(UART0->S1 & UART_S1_TC_MASK)); //Waiting for transmission to get complete
	__enable_irq();
}
void UART_send_n(uint8_t* data, size_t length)
{
	_disable_irq();
	if((data == NULL) || (length < 0))
			{
				return -1;
			}
	else
			for(size_t i = 0;i < length;i++)
			{
				UART_send(data + i);
			}

		__enable_irq();
}
void UART_receive(uint8_t* data)
{
	__disable_irq();
	if(data  == NULL)
			{
				return -1;
			}
	else
		{
			while((UART0->S1 & UART_S1_RDRF_MASK) == 0); //Waiting for the data to recv IE RDRF = 1
			*data = UART0->D; //read data
		}
		__enable_irq();
}
void UART_receive_n(uint8_t* data, size_t length)
{
	_disable_irq();
	if((data  == NULL) || (length < 0))
				{
					return -1;
				}
	else
				for(size_t i = 0;i < length;i++)
				{
					UART_receive(data + i);
				}

			__enable_irq();
}
void UART0_IRQHandler()
{
	cb_enum status;
	if((UART0->S1 & UART_S1_RDRF_MASK)&&(UART0->C2 & UART_C2_RIE_MASK))
	{                       //Interrupt caused by receiver
		int8_t data = UART0->D;
		cb_enum status = cb_buffer_add_item(rx_buffer, data);
	}
	else if ((UART0->S1 & UART_S1_TC_MASK)&& (UART0->C2 & UART_C2_TCIE_MASK))
	{                 //Interrupt caused by transmitter
			int8_t data;
	        status = cb_buffer_remove_item(tx_buffer , &data);       //send a char
	        UART0->D = data;
	                             //Clear transmit receive interrupt flag

	    }
}

