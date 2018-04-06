

#include "spi.h"


/*Initializes the SPI controller*/
void SPI_init();
{
  SIM->SCGC4 |=  SIM_SCGC4_SPI0_MASK; // clock gate enable for spi
  SIM->SCGC5 |=  SIM_SCGC5_PORTA_MASK //gpio port a enable
//selecting alternate pin functions for spi 
PORTA_PCR14 = PORT_PCR_MUX(0x2); //Enable chip select
PORTA_PCR15 = PORT_PCR_MUX(0x2); //Enable the SPI_SCK function on PTA15
PORTA_PCR16 = PORT_PCR_MUX(0x2); // Enable the SPI_MOSI function on PTA16
PORTA_PCR17 = PORT_PCR_MUX(0x2);// Enable the SPI_MISO function on PTA17
SPI0_C1=0X54;//configured device as master- MSTR=1, enabled spi SPE = 1, First edge on SPSCK at start of first data transfer cycle CPHA=1
SPI0_C2=0X10;//SPI clocks operate in wait mode
SPI0_BR |= SPI_BR_SPPR(0) | SPI_BR_SPR(2);//Baud Rate Prescalar as 1 and the Baud Rate Divisor as 4
}

/*Reads a single byte from the SPI bus*/ 
uint8_t SPI_read_byte(uint8_t byte)
{
	// Wait until receive data buffer is full
        	while ((SPI0_S & SPI_S_SPRF_MASK) == 0);
		byte = SPI0_D; // Read data from SPI Data register
		return byte;
}

/*Sends a single byte on the SPI bus*/
void SPI_write_byte(uint8_t byte)
{

	
	      while((SPI0_S & SPI_S_SPTEF_MASK)== 0);// Wait untill data buffer is full
	      SPI0_D = byte; // Write data to SPI Data register 
	

}

/*Sends numerous SPI Bytes given a pointer to a byte array and a length of how many
bytes to send.*/
void SPI_send_packet(uint8_* p, size_t length)
{
int i=0;
	if(p !=NULL && length > 0)
	{
		
		for(i=0;i<length;i++)
		{
			 while((SPI0_S & SPI_S_SPTEF_MASK)== 0);// Wait untill data buffer is full
			SPI0_D = *p++;	
		}

	}
}

/*Blocks until SPI transmit buffer has completed transmitting*/
void SPI_flush()
{
	while ((SPI0_S & SPI_S_SPTEF_MASK) == 0); //Flag is set when transmit data buffer is empty
}
 
