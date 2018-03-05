#include "uart.h"
#include "MKL25Z4.h"
#include "MKL25Z4_extension.h"
#include "circbuf.h"


cb_struct *rx_buffer = NULL;
cb_struct *tx_buffer = NULL;

int8_t UART_configure(BAUDRATE baudselect)
{
    if (baudselect != BAUD_115200 &&
        baudselect != BAUD_38400 &&
        baudselect != BAUD_57200 &&
        baudselect != BAUD_9600)
    {
        return BAUDRATE_ERROR;
    }
    //selecting the FLL clock source for UART0
    //	/SIM_SOPT2 |= 0x04000000;            // MCGFLLCLK clock
    SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
    //SIM_BWR_SOPT2_UART0SRC(SIM, 1); // UART0 clock source as MCGFLLCLK clock or MCGPLLCLK/2 clock (div2 in our case from PLLFLLSEL = 1)

    // TODO This section is different
#if 0
    // Original uses clock divide by 1
    SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL(0);
#else
    // Other clock setup using divide by 2 instead
    // No need to set again here
    //SIM_BWR_SOPT2_PLLFLLSEL(SIM, 1); // MCGPLLCLK clock with fixed divide by two
#endif

    //uart0 clock gate enable
    SIM->SCGC4 |= SIM_SCGC4_UART0(1); //set bit 10 for uart0
    //SIM_BWR_SCGC4_UART0(SIM, 1); // enable uart 0 clock in system clock gating control reg

    // These are probably the default values
    SIM->SOPT5 |= SIM_SOPT5_UART0ODE(0);
    SIM->SOPT5 |= SIM_SOPT5_UART0RXSRC(0);
    SIM->SOPT5 |= SIM_SOPT5_UART0TXSRC(0);

    // These are probably the default values
    //UART0 RX/TX pin behavior and source
    //SIM_SOPT5 |= 0x04000000;    //UART0ODE,UART0RXSRC,UART0TXSRC bit fields set to 0
    UART0->C2 = 0;						//disabling uart 0 before configuration
    UART0->C1 |= UART_C1_M(0) | UART_C1_PE(0); //8 bit data, no parity
    UART0->BDH |= UART_BDH_SBNS(0);   //1 stop bit


#if 1
    UART0->C4 |= UART0_C4_OSR(OSR); //setting OSR bit to 15
    //calculation for baud rate selection
    uint16_t SBR_val = (uint16_t)((((uint32_t)47939584)/(baudselect*16)) & 0x1FFF);
    UART0->BDL = UART_BDL_SBR(SBR_val);
    UART0->BDH |= UART_BDH_SBR(SBR_val>>8);
#else

    // Assuming clock source is MCGPLLCLK at 48MHz

    // Flexible choices for oversampling rate (osr) and baud rate divisor (sbr)
    //
    // Programming baud rate to
    // clock / (osr * sbr)
    // 48MHz / (32 * 13)
    // 48MHz / (416) = 115384 0.16% error

    UART0_BWR_C4_OSR(UART0, 32-1); // Set oversampling rate to one less than desired value

    //UART0_BWR_BDH_SBR(UART0, 13 >> 8); // Zero in this case
    UART0_WR_BDL(UART0, 13); // Just set entire single LSB of SBR in BDL reg
#endif


    //Enabling RIE Interrupt and the TCIE interrupt now.
    //UART0->C2 |= UART_C2_RIE(1) | UART_C2_TCIE(1);

    //Enabling Rx and TX
    UART0->C2 |= UART_C2_RE(1) | UART_C2_TE(1);
    // Enable UART transmitter and receiver
    //UART0_BWR_C2_TE(UART0, 1);
    //UART0_BWR_C2_RE(UART0, 1);

    SIM_SCGC5 |= 0x00000200;            // enable clock for PORTA
    //SIM_BWR_SCGC5_PORTA(SIM, 1); // Enable clock on PORTA for UART


    //Enabling the NVIC Interrupt for UART0
    //NVIC_EnableIRQ(UART0_IRQn);

    PORTA_PCR1 |= 0x00000200;            // Select PTA1 as Receive pin
    PORTA_PCR2 |= 0x00000200;            // Select PTA2 as Transmit pin
    //PORT_BWR_PCR_MUX(PORTA, 1, 2); // Alternate function 2, UART0_RX
    //PORT_BWR_PCR_MUX(PORTA, 2, 2); // Alternate function 2, UART0_TX


    return 0;
}

void polling_tx(const uint8_t *txBuff, uint32_t txSize)
{
    while (txSize--)
    {
        // Wait until ready to transmit
        while (!UART0_BRD_S1_TDRE(UART0))
        {}

        // Transmit character
        UART0_WR_D(UART0, *txBuff++);
    }
}


void UART_send(uint8_t data)
{
    polling_tx(&data, 1);
    return;

    __disable_irq();
    while(!(UART0->S1 & UART_S1_TDRE_MASK)); //Waiting for the buffer to get empty ie bit TDRE = 1
    UART0->D = data; //write data
    while(!(UART0->S1 & UART_S1_TC_MASK)); //Waiting for transmission to get complete
    __enable_irq();
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
    if((UART0->S1 & UART_S1_RDRF_MASK)&&(UART0->C2 & UART_C2_RIE_MASK))
    {                       //Interrupt caused by receiver
        int8_t data = UART0->D;
        cb_enum status = cb_buffer_add_item(rx_buffer, data);

        if (status == CB_SUCCESS)
        {
            //UART0->D = data;
        }
    }
    else if ((UART0->S1 & UART_S1_TC_MASK)&& (UART0->C2 & UART_C2_TCIE_MASK))
    {                 //Interrupt caused by transmitter
        int8_t data;
        status = cb_buffer_remove_item(tx_buffer , &data);       //send a char

        if (status == CB_SUCCESS)
        {
            UART0->D = data;
        }
        //Clear transmit receive interrupt flag
    }
}

