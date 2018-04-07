#ifndef __NORDIC_H__
#define __NORDIC_H__


#include "MKL25Z4.h"
#include "gpio.h"
#unclude "spi.h"

#define  nrf_chip_enable()      GPIOD_PCOR |= (1 << 0);   // Enable NRF chip
#define  nrf_chip_disable()     GPIOD_PSOR |= (1 << 0);   // Disable NRF chip
#define  nrf_transmit_enable()  GPIOD_PCOR |= (1 << 5);   // Enable NRF transmission
#define  nrf_transmit_disable() GPIOD_PSOR |= (1 << 5);   // Disable NRF transmission

//register address map
#define nrf_CONFIG 		(0x00)
#define nrf_STATUS 		(0x07)
#define nrf_TX_ADDR 		(0x10)
#define nrf_RF_SETUP 		(0x06)
#define nrf_RF_chregister	(0x05)
#define nrf_FIFO_STATUS		(0x17)

//Commands 
#define nrf_TXFIFO_FLUSH_CMD	(0xE1)
#define nrf_RXFIFO_FLUSH_CMD	(0xE2)
#define nrf_W_TXPAYLD_CMD	(0xA0)
#define nrf_R_RXPAYLD_CMD	(0x61)
#define nrf_ACTIVATE_CMD	(0x50)
#define nrf_ACTIVATE_DATA	(0x73)
#define nrf_RXPAYLD_W_CMD	(0x60)
#define nrf_NOP			(0xFF)

//masks
#define nrf_POWER_UP_MASK       (0x02)
#define nrf_POWER_DOWN_MASK 	(0X00)
#define nrf_CHANNEL_FREQ_MASK   (0x03)
#define nrf_SET_LAN_GAIN_MASK   (0x01)

//read write register
#define READ_INST 0x00
#define WRITE_INST 0x20

/*Read the register and return the value*/
uint8_t nrf_read_register(uint8_t reg);

/*Write to the given register with the data.*/
void nrf_write_register(uint8_t reg, uint8_t value);

/*Reads the STATUS register*/
uint8_t nrf_read_status();

/*Write to CONFIG register*/
void nrf_write_config(uint8_t config);

/*Read the CONFIG register*/
uint8_t nrf_read_config();
 
/* Reads RF_SETUP register*/
uint8_t nrf_read_rf_setup();

/*Writes to the RF_SETUP register*/
void nrf_write_rf_setup(uint8_t config);
 
/* Reads RF_CH register*/
uint8_t nrf_read_rf_ch();

/*Writes to the RF_CH register*/ 
void nrf_write_rf_ch(uint8_t channel);

/*Reads the 5 bytes of the TX_ADDR register*/
void nrf_read_TX_ADDR(uint8_t * address);

/* Writes the 5 byte TX_ADDR register*/
void nrf_write_TX_ADDR(uint8_t * tx_addr);

/* Reads FIFO_STATUS register*/
uint8_t nrf_read_fifo_status();

/*Sends the command FLUSH_TX*/
void nrf_flush_tx_fifo();
 
/*Sends the command FLUSH_RX*/
void nrf_flush_rx_fifo();


#endif
 
