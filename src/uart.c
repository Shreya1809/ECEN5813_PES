/**
 * @file uart.c
 * @brief UART functions for transmit and receive
 * @author Miles Frain
 * @author Shreya Chakraborty
 * @version 1
 * @date 2018-03-04
 */

#include "uart.h"
#include "MKL25Z4.h"
#include "MKL25Z4_extension.h"
#include "circbuf.h"
#include "port.h"
#include "conversion.h"
#include "logger.h"
#include "data_processing.h"
#include "logger_queue.h"


//cb_struct *rx_buffer = NULL;
//cb_struct *tx_buffer = NULL;
//static uint8_t flag = 0;


volatile uint8_t binary_logger = 0;

int8_t UART_configure(BAUDRATE baudselect)
{
    if (baudselect != BAUD_115200 &&
        baudselect != BAUD_38400 &&
        baudselect != BAUD_57200 &&
        baudselect != BAUD_9600)
    {
        return BAUDRATE_ERROR;
    }

    // Select the FLL clock source for UART0
    SIM_BWR_SOPT2_UART0SRC(SIM, 1); // UART0 clock source as MCGFLLCLK clock or MCGPLLCLK/2 clock (div2 in our case from PLLFLLSEL = 1)

    // uart0 clock gate enable
    SIM_BWR_SCGC4_UART0(SIM, 1); // enable uart0 clock in system clock gating control reg

    UART0_BWR_C4_OSR(UART0, UART_OVERSAMPLING - 1); // Write one less than oversampling value to OSR

    // Calculation for baud rate selection
    uint16_t baud_rate_divider = 47939584 / (baudselect * UART_OVERSAMPLING);
    UART0_WR_BDL(UART0, baud_rate_divider); // LSB of SBR in BDL reg
    UART0_BWR_BDH_SBR(UART0, baud_rate_divider >> 8); // Set remaining 4 high bits of SBR

    //Enabling RIE Interrupt and the TCIE interrupt now.
    //UART0->C2 |= UART_C2_RIE(1) | UART_C2_TCIE(1);
    UART0->C2 |= UART_C2_RIE(1);

    // Enable UART transmitter and receiver
    UART0_BWR_C2_TE(UART0, 1);
    UART0_BWR_C2_RE(UART0, 1);

    SIM_BWR_SCGC5_PORTA(SIM, 1); // Enable clock on PORTA for UART

    //Enabling the NVIC Interrupt for UART0
    NVIC_EnableIRQ(UART0_IRQn);

    PORT_BWR_PCR_MUX(PORTA, 1, 2); // Alternate function 2, UART0_RX
    PORT_BWR_PCR_MUX(PORTA, 2, 2); // Alternate function 2, UART0_TX

    return 0;
}

void UART_send(uint8_t data)
{
    __disable_irq();
    while(!UART0_BRD_S1_TDRE(UART0)); //Waiting for the buffer to get empty ie bit TDRE = 1
    UART0->D = data; //write data
    // Alternate data write macro
	//UART0_WR_D(UART0, data);
	// Probably don't need to wait for transmit to complete
    //while(!(UART0->S1 & UART_S1_TC_MASK)); //Waiting for transmission to get complete
    __enable_irq();
    //RGB_BLUE_TOGGLE();
}

int _write(int fd, const void *buf, size_t len)
{
	(void)fd;

    // Don't think interrupts need to be disabled for this
    //UART_send_n((uint8_t*)buf, len);

    // Improved version where carriage return added to every newline
    size_t count = 0; // actual number of transmitted chars
    while (len--)
    {
        if (*(uint8_t*)buf == '\n')
        {
            UART_send('\r');
            count++;
        }
        UART_send(*(uint8_t*)buf++);
        count++;
    }

	return count;
}

void UART_send_n(uint8_t* data, size_t length)
{
    __disable_irq();
    if((data == NULL) || (length < 0))
    {
        return;
    }
    else
    {
        for(size_t i = 0;i < length;i++)
        {
            UART_send(*(data + i));
            //UART_send(*data++);
        }
    }

    __enable_irq();
}
void UART_receive(uint8_t* data)
{
    __disable_irq();
    if(data  == NULL)
    {
        return;
    }
    else
    {
        while((UART0->S1 & UART_S1_RDRF_MASK) == 0); //Waiting for the data to recv IE RDRF = 1
        *data = UART0->D; //read data
    }
    __enable_irq();
}

// Todo - probably best for interrupt receive and polling transmit

void UART_receive_n(uint8_t* data, size_t length)
{
    __disable_irq();
    if((data  == NULL) || (length < 0))
    {
        return;
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
    static int8_t data;
    //if((UART0->S1 & UART_S1_RDRF_MASK)&&(UART0->C2 & UART_C2_RIE_MASK))
    // Don't need to check UART_C2_RIE, this is a configuration reg that we set once
    //if (UART0->S1 & UART_S1_RDRF_MASK)
    if ((UART0_C2 & UART0_C2_RIE_MASK) == UART0_C2_RIE_MASK)//(UART0_BRD_S1_RDRF(UART0))
    {
        RGB_BLUE_TOGGLE();
        		data = UART0_D;		//receives bit from keyboard
        		if(data != 0)
        		cb_buffer_add_item(rx_buffer, data);
        // Can probably directly check what triggered interrupt another way
        //Interrupt caused by receiver

        UART0_C2 &= ~UART0_C2_RIE_MASK;
        UART0_C2 |= UART0_C2_TIE_MASK;

       // if (status);

           }
    else if ((UART0_C2 & UART0_C2_TIE_MASK) == UART0_C2_TIE_MASK) //((UART0->S1 & UART_S1_TC_MASK)&& (UART0->C2 & UART_C2_TCIE_MASK))
    {                 //Interrupt caused by transmitter

        status = cb_buffer_remove_item(rx_buffer , &data);

        if (status == CB_SUCCESS)
        {
            UART0->D = data;
        }

        if(data != 0 && data != 32 && data != 27 && data != 13 && data!=9)
        {
        		data_statistics(data);

        }

        else if (data == 32)
        {
        	print_data_entered();


        }
        else if (data == 27)
        {
        	print_all_log();
        	log_create(logged_data, CORE_DUMP,UART, 9,(uint8_t *)"CORE DUMP");
        	LOG_RAW_ITEM(tx_buffer, logged_data);
            LOG_FLUSH(tx_buffer);
        }
        else if(data == 13)
        {

			log_create(logged_data, DATA_RECEIVED, UART, 1,(uint8_t *)1);
			LOG_RAW_ITEM(tx_buffer, logged_data);
            LOG_FLUSH(tx_buffer);
        	UART_send_n((uint8_t*)" \r\nENTER ANYTHING : ", 20);
        	heartbeat();
        	if (flag == 1) {flag = 0;} else flag = 1;
        }
        else if(data == 9)
        {
        	(binary_logger == 0) ? (binary_logger = 1) : (binary_logger = 0);
        }
//        else if(data == 9)
//        {
//        	log_flush_KL25Z(tx_buffer);
//        }

		UART0_C2 &= ~UART0_C2_TIE_MASK;
		UART0_C2 |= UART0_C2_RIE_MASK;



        //Clear transmit receive interrupt flag
    }
}

