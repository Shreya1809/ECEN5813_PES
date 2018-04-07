#ifndef __SPI_H__
#define __SPI_H__

#include "MKL25Z4.h"
#include <stdint.h>
#include <stdlib.h>

/*Initializes the SPI controller*/
void SPI_init();

/*Reads a single byte from the SPI bus*/ 
void SPI_read_byte(uint8_t *byte);

/*Sends a single byte on the SPI bus*/
void SPI_write_byte(uint8_t byte);

/*Sends numerous SPI Bytes given a pointer to a byte array and a length of how many
bytes to send.*/
void SPI_send_packet(uint8_t *p, size_t length);

/*Blocks until SPI transmit buffer has completed transmitting*/
void SPI_flush();
 #endif
