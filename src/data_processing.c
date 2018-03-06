/**
 * @file data_processing.c
 * @brief Character counting and statistics functions
 * @author Miles Frain
 * @author Shreya Chakraborty
 * @version 1
 * @date 2018-03-04
 */

#include <stdint.h>
#include "circbuf.h"
#include "platform.h"
#ifdef KL25Z
#include "uart.h"
#include "port.h"
#include "arch_arm32.h"
#endif

uint8_t alphabetical(uint8_t value) // to check if alphabet
{
    if ((value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z'))
        return 1;
    else
        return 0;
}

uint8_t numerical(uint8_t value)// to check if number
{
    if (value >= '0' && value <= '9')
        return 1;
    else
        return 0;
}

uint8_t punctuation(uint8_t value) // to check if punctuation
{
    switch ((unsigned char)value)
    {
        case '.':
        case '\'':
        case '\"':
        case ':':
        case ';':
        case ',':
        case '?':
        case '!': return 1;
        default: return 0;
    }
}

void print_data_process_header(void)
{
    PRINTF("----------------- Character Statistics -----------------\n");
    PRINTF("--------------------------------------------------------\n");
    PRINTF("Letter\t | Number\t | Punctuation\t | Misc\t | Total\n");
    PRINTF("--------------------------------------------------------\n");
}


/*
#define NUM_LEDS 3
uint8_t LED_PINS[] = {
    RGB_GREEN_PIN,
    RGB_RED_PIN,
    RGB_BLUE_PIN
};
__O  uint32_t led_off[] = {
    PTB->PSOR,
    PTB->PSOR,
    PTD->PSOR,
};

__O  uint32_t led_on[] = {
    PTB->PSOR,
    PTB->PSOR,
    PTD->PSOR,
};
*/

void data_process(cb_struct *buf)
{
    //variables to keep count
    static uint32_t alphabet= 0;
    static uint32_t number= 0;
    static uint32_t punctuations= 0;
    static uint32_t miscell= 0;
    static uint32_t current_data= 0;
    static uint32_t count = 0;
    while (!cb_is_empty(buf))
    {
        cb_enum status = cb_buffer_remove_item(buf, (int8_t*)&current_data);
        if (status == CB_SUCCESS)
        {

#ifdef KL25Z
            static uint8_t current_led_index = 0;
            static uint8_t current_led_on = 0;
            switch (current_data)
            {
                case 'a':
                {
                    // LED on
                    current_led_on = 1;
                    switch (current_led_index)
                    {
                        case 0: RGB_RED_ON(); break;
                        case 1: RGB_GREEN_ON(); break;
                        case 2: RGB_BLUE_ON(); break;
                    }
                    break;
                }
                case 'b':
                {
                    // LED off
                    current_led_on = 0;
                    switch (current_led_index)
                    {
                        case 0: RGB_RED_OFF(); break;
                        case 1: RGB_GREEN_OFF(); break;
                        case 2: RGB_BLUE_OFF(); break;
                    }
                    break;
                }
                case 'c':
                {
                    // turn off existing LED if it is on
                    if (current_led_on)
                    {
                        switch (current_led_index)
                        {
                            case 0: RGB_RED_OFF(); break;
                            case 1: RGB_GREEN_OFF(); break;
                            case 2: RGB_BLUE_OFF(); break;
                        }
                    }

                    // change LED
                    current_led_index++;
                    if (current_led_index >= 3)
                    {
                        current_led_index = 0;
                    }

                    // Turn on new led if necessary
                    if (current_led_on)
                    {
                        switch (current_led_index)
                        {
                            case 0: RGB_RED_ON(); break;
                            case 1: RGB_GREEN_ON(); break;
                            case 2: RGB_BLUE_ON(); break;
                        }
                    }
                    break;
                }

                case 'g':
                {
                    // Print part number
                    PRINTF("\nPart number %d\n", ARM32_CPUID_get_part_number());
                }
#endif // KL25Z

            }
            if(alphabetical(current_data))
            {
                alphabet++;

            }
            else if(numerical(current_data))
            {
                number++;
            }
            else if(punctuation(current_data))
            {
                punctuations++;
            }
            else
            {
                miscell++;
            }
            count++;
        }
    }

#ifdef KL25Z
    char line[200];
    char len = sprintf(line,
            " %lu\t | %lu\t\t | %lu\t\t | %lu\t | %lu\r",
            alphabet, number, punctuations, miscell, count);
    UART_send_n((uint8_t*)line, len);
#else
    // Built-in printf forces line buffering before flush
    PRINTF(" %lu\t | %lu\t\t | %lu\t\t | %lu\t | %lu\r",
            alphabet, number, punctuations, miscell, count);
#endif
}
