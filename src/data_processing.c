#include <stdint.h>
#include "circbuf.h"
#include "platform.h"
#include "uart.h"

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
    PRINTF("-----------------Character Statistics-----------------\n");
    PRINTF("--------------------------------------------------------\n");
    PRINTF("Letter\t | Number\t | Punctuation\t | Misc\t | Total\n");
    PRINTF("--------------------------------------------------------\n");
}

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
