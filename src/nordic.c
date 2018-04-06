#include "nordic.h"

/*Read the register and return the value*/
uint8_t nrf_read_register(uint8_t register)

/*Write to the given register with the data.*/
void nrf_write_register(uint8_t register, uint8_t value)

/*Reads the STATUS register*/
uint8_t nrf_read_status()

/*Write to CONFIG register*/
void nrf_write_config(uint8_t config)

/*Read the CONFIG register*/
uint8_t nrf_read_config()
 
/* Reads RF_SETUP register*/
uint8_t nrf_read_rf_setup()

/*Writes to the RF_SETUP register*/
void nrf_write_rf_setup(uint8_t config)
 
/* Reads RF_CH register*/
uint8_t nrf_read_rf_ch()

/*Writes to the RF_CH register*/ 
void nrf_write_rf_ch(uint8_t channel)

/*Reads the 5 bytes of the TX_ADDR register*/
void nrf_read_TX_ADDR(uint8_t * address)

/* Writes the 5 byte TX_ADDR register*/
void nrf_write_TX_ADDR(uint8_t * tx_addr)

/* Reads FIFO_STATUS register*/
uint8_t nrf_read_fifo_status()

/*Sends the command FLUSH_TX*/
void nrf_flush_tx_fifo()
 
/*Sends the command FLUSH_RX*/
void nrf_flush_rx_fifo()
