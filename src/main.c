/**
 * @file main.c
 * @brief source file for main.c
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
#include "blink.h"
#include "clock.h"
#include "port.h"
// Not sure exactly what state SystemInit() leaves the device in with CLOCK_SETUP
// TODO - check register differences
#define CLOCK_SETUP 1
#endif

int main()
{
#ifdef KL25Z
    // blink();
    clock_setup();
    GPIO_Configure();
    //while(1) RGB_RED_TOGGLE();
    //UART_configure(BAUD_9600);
    cb_enum status;
    rx_buffer = malloc(sizeof(cb_struct));
    status = cb_init(rx_buffer, 32);
    UART_configure(BAUD_115200);
    //char prefix[] = "Prefix: ";
    //char fmt[100];
    //int8_t data;
    printf("\n\rhi\n\r");
    print_data_process_header();
    while(1)
    {
	   if (!cb_is_empty(rx_buffer))
	   {
		  data_process(rx_buffer);

		  //status = cb_buffer_remove_item(rx_buffer, &data);
		  //size_t len = sprintf(fmt, "letter %c yo\n\r", data);
		  //UART_send_n((uint8_t*)fmt, len);

		  //UART_send_n((uint8_t*)prefix, sizeof(prefix));
		  //UART_send(data);
		  RGB_RED_TOGGLE();
		  if (status);
	   }
    }

    //while(1) {UART_send('1');}
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
    /*char string[2000];
    printf("Enter String");
    scanf("%s",string);
    int j;
    cb_struct my_cb;
    cb_init(&my_cb,100);
    for (j = 0; string[j] != '\0'; j++)
    {
        cb_buffer_add_item(&my_cb,string[j]);
    }
	data_process(&my_cb);*/

    return 0;
}

