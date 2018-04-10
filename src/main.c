/**
 * @file main.c
 * @brief Main program entry point
 * @author Miles Frain
 * @author Shreya Chakraborty
 * @version 1
 * @date 2018-02-10
 */
#include "project1.h"
#include "profiler.h"
#include "data.h"
#include "platform.h"
#include "data_processing.h"
#include "circbuf.h"
#include <unistd.h>
#ifdef KL25Z
#include "uart.h"
#include "clock.h"
#include "port.h"
#include "profiler.h"
#include "nordic.h"
#include "dma.h"
// Not sure exactly what state SystemInit() leaves the device in with CLOCK_SETUP
// TODO - check register differences
#define CLOCK_SETUP 1

//Defining the the stack top as a pointer to access it in the program
extern uint32_t __StackTop[];
extern uint32_t __StackLimit[];
extern uint32_t STACK_SIZE;
uint8_t *stack_top = (uint8_t*)__StackTop-4;
uint8_t *stack_base = (uint8_t*)__StackLimit;
volatile uint32_t stackptr;
#endif

int main()
{
#if defined PROJECT2 || defined PROJECT3
#ifdef KL25Z
    clock_setup();
    UART_configure(BAUD_115200);
    __asm__
	(
    	"LDR r0, = stackptr;"
    	"MOV r1, sp;"
		"STR r1, [r0];"
    );
    uint32_t *temp_sp_low = (uint32_t *)stack_base;
    uint32_t *temp_sp_high = (uint32_t *)stack_top;
    uint32_t size = (uint32_t)&STACK_SIZE;
    //uint32_t stack_val_top= *temp_sp_high;
    for(uint32_t i = 0; i < size; i++)
    {
    	if(*temp_sp_high == 0x0a0a0a0a)
    	{
    		break;
    	}
    	temp_sp_high--;
    }
    uint32_t diff = (uint32_t)temp_sp_high-(uint32_t)temp_sp_low;
    PRINTF("STACKUSE:0x%x",diff);

    GPIO_Configure();

    systick_init();
    SPI_init();

#else  // platform not KL25Z
    cb_struct *rx_buffer; // defined by uart otherwise
    if(rx_buffer); // Avoid unused build error for now
#endif // platform

#if 0
    rx_buffer = malloc(sizeof(cb_struct));
    cb_enum status = cb_init(rx_buffer, 256);
    if (status != CB_SUCCESS)
    {
	   PRINTF("Error initializing rx buffer\n");
    }
    PRINTF("\nStarting Project 2 or 3\n");
#endif

#ifdef PROJECT3
    PRINTF("\nProject 3 print\n");
#ifdef KL25Z
    DMA_config();
    kl25z_profile_option(MEMMOVE_DMA);
	kl25z_profile_option(MEMSET_DMA);
	kl25z_profile_option(MY_MEMMOVE);
	kl25z_profile_option(MY_MEMSET);
	kl25z_profile_option(MEMMOVE);
	kl25z_profile_option(MEMSET);

    nordic_test();

#else
    bbb_profile_option(1);
    bbb_profile_option(2);
    bbb_profile_option(3);
    bbb_profile_option(4);
#endif // platform
#endif // project 3

#ifdef PROJECT2
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
#else  // HOST or BBB
    char string[2000];
    while (1)
    {
        printf("\nEnter String: ");
        scanf("%s", string);
        for (int j = 0; string[j] != '\0'; j++)
        {
            cb_buffer_add_item(rx_buffer, string[j]);
        }
        data_process(rx_buffer);
    }
#endif // platform
#endif // PROJECT2

#endif // project 2 or 3

#ifdef PROJECT1
    project1();
    print_cstd_type_sizes();
    print_stdint_type_sizes();
    print_pointer_sizes();
    uint32_t i = 0x12345678;
    PRINTF("pre swap 0x%lx\n", i);
    determine_endianness();
    swap_data_endianness((uint8_t *)&i, sizeof(i));
    PRINTF("post swap 0x%lx\n", i);
#endif

    return 0;
}
