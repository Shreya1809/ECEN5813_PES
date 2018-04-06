#include "nordic.h"

/*Read the register and return the value*/
uint8_t nrf_read_register(uint8_t reg)
{	
	uint8_t *p = (uint8_t *)malloc(sizeof(uint8_t));
	nrf_chip_enable();
	SPI_write_byte(reg | READ_INST);
	SPI_read_byte(p);
	SPI_write_byte(nrf_NOP);
	SPI_read_byte(p);
	return *p;
	nrf_chip_disable();
}

/*Write to the given register with the data.*/
void nrf_write_register(uint8_t reg, uint8_t value)
{
	uint8_t *p = (uint8_t *)malloc(sizeof(uint8_t));
	nrf_chip_enable();
	SPI_write_byte(reg | WRITE_INST);
	SPI_read_byte(p);
	SPI_write_byte(value);
	SPI_read_byte(p);
	nrf_chip_disable();
}
/*Reads the STATUS register*/
uint8_t nrf_read_status()
{
	return nrf_read_register(nrf_STATUS);
}
/*Write to CONFIG register*/
void nrf_write_config(uint8_t config)
{
	nrf_write_register(nrf_CONFIG, config);
}
/*Read the CONFIG register*/
uint8_t nrf_read_config()
{
	return nrf_read_register(nrf_CONFIG);
}
 
/* Reads RF_SETUP register*/
uint8_t nrf_read_rf_setup()
{
	return nrf_read_register(nrf_RF_SETUP);
}
/*Writes to the RF_SETUP register*/
void nrf_write_rf_setup(uint8_t config)
{
	nrf_write_register(nrf_RF_SETUP, config);
}
/* Reads RF_CH register*/
uint8_t nrf_read_rf_ch()
{
	return nrf_read_register(nrf_RF_chregister);
}
/*Writes to the RF_CH register*/ 
void nrf_write_rf_ch(uint8_t channel)
{
	nrf_write_register(nrf_RF_chregister, channel);
}
/*Reads the 5 bytes of the TX_ADDR register*/
void nrf_read_TX_ADDR(uint8_t * address)
{
	uint8_t *p = (uint8_t *)malloc(sizeof(uint8_t));
	nrf_chip_enable();
	SPI_write_byte(nrf_TX_ADDR | READ_INST);
	SPI_read_byte(p);
	for (i=0; i<6; i++)                          // Writes to the 5 byte TX_ADDR register
		for (i = 0; i<6; i++)                          // Reads the 5 bytes of the TX_ADDR register
		{
		SPI_write_byte(NOP);
		SPI_read_byte(address);
		address++;
		}
	nrf_chip_disable();
}

/* Writes the 5 byte TX_ADDR register*/
void nrf_write_TX_ADDR(uint8_t * tx_addr)
{
	uint8_t *p = (uint8_t *)malloc(sizeof(uint8_t));
	nrf_chip_enable();
	SPI_write_byte(nrf_TX_ADDR | WRITE_INST);
	SPI_read_byte(p);
	for (i=0; i<6; i++)                          // Writes to the 5 byte TX_ADDR register
		{
		SPI_write_byte(*tx_addr);
		tx_addr++;
		}
	nrf_chip_disable();
}
/* Reads FIFO_STATUS register*/
uint8_t nrf_read_fifo_status()
{
	return nrf_read_register(nrf_FIFO_STATUS);
}

/*Sends the command FLUSH_TX*/
void nrf_flush_tx_fifo()
{
      	nrf_chip_enable();
	SPI_write_byte(nrf_TXFIFO_FLUSH_CMD);
	nrf_chip_disable();                            
}
 
/*Sends the command FLUSH_RX*/
void nrf_flush_rx_fifo()
{
	nrf_chip_enable();
	SPI_write_byte(nrf_RXFIFO_FLUSH_CMD);
	nrf_chip_disable();                            
}
