/**
 * @file main.c
 * @brief Main program entry point
 * @author Miles Frain
 * @author Shreya Chakraborty
 * @version 1
 * @date 2018-02-10
 */
#include "project1.h"
#include "data.h"
#include "platform.h"
#include "data_processing.h"
#include "circbuf.h"
#include <unistd.h>
#ifdef KL25Z
#include "uart.h"
#include "clock.h"
#include "port.h"
// Not sure exactly what state SystemInit() leaves the device in with CLOCK_SETUP
// TODO - check register differences
#define CLOCK_SETUP 1
#endif

int main()
{
#ifdef KL25Z
    clock_setup();
    GPIO_Configure();
    UART_configure(BAUD_115200);
#endif

    rx_buffer = malloc(sizeof(cb_struct));
    cb_enum status = cb_init(rx_buffer, 256);
    if (status != CB_SUCCESS)
    {
	   PRINTF("Error initializing rx buffer\n");
    }
    PRINTF("\nStarting Project 2\n");
    print_data_process_header();

#ifdef KL25Z
    while (1)
    {
	   if (!cb_is_empty(rx_buffer))
	   {
		  data_process(rx_buffer);

		  RGB_RED_TOGGLE();
	   }
    }
#else // HOST or BBB
    char string[2000];
    while (1)
    {
	   printf("Enter String: ");
	   scanf("%s",string);
	   for (int j = 0; string[j] != '\0'; j++)
	   {
		  cb_buffer_add_item(rx_buffer, string[j]);
	   }
	   data_process(rx_buffer);
    }
#endif


#ifdef PROJECT1
    project1();
    print_cstd_type_sizes();
    print_stdint_type_sizes();
    print_pointer_sizes();
    uint32_t i = 0x12345678;
    PRINTF("pre swap 0x%lx\n", i);
    determine_endianness();
    swap_data_endianness((uint8_t*)&i, sizeof(i));
    PRINTF("post swap 0x%lx\n", i);
#endif

    return 0;
}

