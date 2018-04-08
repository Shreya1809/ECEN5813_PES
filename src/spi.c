

#include "spi.h"


/*Initializes the SPI controller*/
void SPI_init()
{
  SIM->SCGC4 |=  SIM_SCGC4_SPI0_MASK; // clock gate enable for spi
  SIM->SCGC5 |=  SIM_SCGC5_PORTD_MASK; //gpio port d enable
  //SIM->SCGC5 |=  SIM_SCGC5_PORTA_MASK; //gpio port a enable
//selecting alternate pin functions for spi 
PORTD_PCR0 = PORT_PCR_MUX(0x1); //Enable chip select
PORTD_PCR1 = PORT_PCR_MUX(0x2); //Enable the SPI_SCK function on PTA15
PORTD_PCR2 = PORT_PCR_MUX(0x2); // Enable the SPI_MOSI function on PTA16
PORTD_PCR3 = PORT_PCR_MUX(0x2);// Enable the SPI_MISO function on PTA17
//SPI0_C1=0X50;//configured device as master- MSTR=1, enabled spi SPE = 1, First edge on SPSCK at start of first data transfer cycle CPHA=1
//SPI0_C1 = 0X54;//configured device as master- MSTR=1, enabled spi SPE = 1, First edge on SPSCK at start of first data transfer cycle CPHA=1
// Should do phase (CPHA) of zero - according to tutorial
SPI0_C1 = SPI_C1_MSTR(1) | SPI_C1_SPE(1) | SPI_C1_CPHA(0);//configured device as master- MSTR=1, enabled spi SPE = 1
//SPI0_C2 = SPI_C2_SPISWAI(1);//SPI clocks operate in wait mode
SPI0_BR |= SPI_BR_SPPR(0) | SPI_BR_SPR(2);//Baud Rate Prescalar as 1 and the Baud Rate Divisor as 4
}

/*Reads a single byte from the SPI bus*/ 
void SPI_read_byte(uint8_t *byte)
{
	if(byte != NULL)
	{	// Wait until receive data buffer is full
        	while ((SPI0_S & SPI_S_SPRF_MASK) == 0);
		*byte = SPI0_D; // Read data from SPI Data register
	}
}

/*Sends a single byte on the SPI bus*/
void SPI_write_byte(uint8_t byte)
{

	      while((SPI0_S & SPI_S_SPTEF_MASK)== 0);// Wait until data buffer is empty
	      SPI0_D = byte; // Write data to SPI Data register 
	

}
/*Sends numerous SPI Bytes given a pointer to a byte array and a length of how many
bytes to send.*/
void SPI_send_packet(uint8_t* p, size_t length)
{
int i=0;
	if(p !=NULL && length > 0)
	{
		
		while(i<length)
		{
			SPI_write_byte((uint8_t)(*p)); 
			p++;
		}

	}
}

/*Blocks until SPI transmit buffer has completed transmitting*/
void SPI_flush()
{
	while ((SPI0_S & SPI_S_SPTEF_MASK) == 0); //Flag is set when transmit data buffer is empty
}
 