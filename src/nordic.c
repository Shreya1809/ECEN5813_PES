#include "nordic.h"
#include "platform.h"

/*Read the register and return the value*/
uint8_t nrf_read_register(uint8_t reg)
{
    uint8_t value;
    nrf_chip_enable();
    SPI_write_byte(reg | READ_INST);
    SPI_read_byte(&value); // STATUS returned for first byte
    SPI_write_byte(nrf_NOP); // Write any value to read next byte
    SPI_read_byte(&value); // Value of register we are interested in
    nrf_chip_disable();
    return value;
}

/*Write to the given register with the data.*/
void nrf_write_register(uint8_t reg, uint8_t value)
{
    uint8_t dummy;
    nrf_chip_enable();
    SPI_write_byte(reg | WRITE_INST);
    SPI_read_byte(&dummy); // STATUS returned
    SPI_write_byte(value);
    SPI_read_byte(&dummy); // Need to wait until byte is written before disabling csn. Easiest way to do this is to read dummy value.
    nrf_chip_disable();
}
/*Reads the STATUS register*/
uint8_t nrf_read_status()
{
    // This could be optimized by just sending NOP command, which returns status.
    // Otherwise status returned twice for traditional read.
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
void nrf_read_TX_ADDR(uint8_t *address)
{
    nrf_chip_enable();
    SPI_write_byte(nrf_TX_ADDR | READ_INST);
    SPI_read_byte(address);     // Read status byte returned from command
    for (int i = 0; i < 5; i++) // Reads the 5 bytes of the TX_ADDR register
    {
        SPI_write_byte(0xAA); // Must write a byte to receive a byte, but this written byte can be anything.
        SPI_read_byte(address);
        address++;
    }
    nrf_chip_disable();
}

/* Writes the 5 byte TX_ADDR register*/
void nrf_write_TX_ADDR(uint8_t *tx_addr)
{
    if (!tx_addr)
    {
        return;
    }
    uint8_t dummy;
    nrf_chip_enable();
    SPI_write_byte(nrf_TX_ADDR | WRITE_INST);
    SPI_read_byte(&dummy);
    for (int i = 0; i < 5; i++) // Writes to the 5 byte TX_ADDR register
    {
        SPI_write_byte(*tx_addr);
        tx_addr++;
        SPI_read_byte(&dummy); // Need to wait until byte is written before disabling csn. Easiest way to do this is to read dummy value.
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
	uint8_t dummy;
    nrf_chip_enable();
    SPI_write_byte(nrf_TXFIFO_FLUSH_CMD);
    SPI_read_byte(&dummy); // Need to wait until byte is written before disabling csn. Easiest way to do this is to read dummy value.
    nrf_chip_disable();
}

/*Sends the command FLUSH_RX*/
void nrf_flush_rx_fifo()
{
	uint8_t dummy;
    nrf_chip_enable();
    SPI_write_byte(nrf_RXFIFO_FLUSH_CMD);
    SPI_read_byte(&dummy); // Need to wait until byte is written before disabling csn. Easiest way to do this is to read dummy value.
    nrf_chip_disable();
}

void nordic_test()
{
    uint8_t spi_data[5];
    uint8_t spi_value;

    /*Reads the STATUS register*/
    spi_value = nrf_read_status();

    if (spi_value == 0x0E)
    {
        PRINTF("SPI status okay\n");
    }
    else
    {
        PRINTF("SPI status ERROR\n");
    }

    /*Write to CONFIG register*/
    nrf_write_config(0x0A);

    /*Read the CONFIG register*/
    spi_value = nrf_read_config();

    if (spi_value == 0x0A)
    {
        PRINTF("SPI config okay\n");
    }
    else
    {
        PRINTF("SPI config ERROR\n");
    }

    /*Writes to the RF_SETUP register*/
    nrf_write_rf_setup(0x0B);

    /* Reads RF_SETUP register*/
    spi_value = nrf_read_rf_setup();

    if (spi_value == 0x0B)
    {
        PRINTF("SPI RF_SETUP okay\n");
    }
    else
    {
        PRINTF("SPI RF_SETUP ERROR\n");
    }

    /*Writes to the RF_CH register*/
    nrf_write_rf_ch(0x1B);

    /* Reads RF_CH register*/
    spi_value = nrf_read_rf_ch();

    if (spi_value == 0x1B)
    {
        PRINTF("SPI RF_CH okay\n");
    }
    else
    {
        PRINTF("SPI RF_CH ERROR\n");
    }

    for (int i = 0; i < 5; i++)
    {
        spi_data[i] = i;
    }
    /* Writes the 5 byte TX_ADDR register*/
    nrf_write_TX_ADDR(spi_data);

    /*Reads the 5 bytes of the TX_ADDR register*/
    nrf_read_TX_ADDR(spi_data);

    for (int i = 0; i < 5; i++)
    {
        if (spi_data[i] == i)
        {
            PRINTF("SPI TX_ADDR[%d] okay\n", i);
        }
        else
        {
            PRINTF("SPI TX_ADDR[%d] ERROR\n", i);
        }
    }

    /* Reads FIFO_STATUS register*/
    spi_value = nrf_read_fifo_status();

    if (spi_value == 0x11)
    {
        PRINTF("SPI FIFO_STATUS okay\n");
    }
    else
    {
        PRINTF("SPI FIFO_STATUS ERROR\n");
    }

    /*Sends the command FLUSH_TX*/
    nrf_flush_tx_fifo();

    /*Sends the command FLUSH_RX*/
    nrf_flush_rx_fifo();
}