
#include "data_processing.h"
#include "platform.h"




uint8_t alphabetical(uint8_t value) // to check if alphabet
{
    if ((value >= ALPHANUMERIC_A && value <= ALPHANUMERIC_Z) || (value >= alphanumeric_a && value <= alphanumeric_z))
        return 1;
    else
        return 0;
}
uint8_t numerical(uint8_t value)// to check if number
{
    if (value >= number_0 && value <= number_9)
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

void data_process(cb_struct *buf)
{
    //variables to keep count
    static uint8_t alphabet= 0;
    static uint8_t number= 0;
    static uint8_t punctuations= 0;
    static uint8_t miscell= 0;
    static uint8_t current_data= 0;
    static uint8_t count = 0;
    cb_enum status;
    while (!cb_is_empty(buf))
    {
        status = cb_buffer_remove_item(buf, (int8_t*)&current_data);
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

    PRINTF("---------statistics---------\n");
    PRINTF("Number of alphabets = %d\n" , alphabet);
    PRINTF("Number of numbers = %d\n" , number);
    PRINTF("Number of punctuations = %d\n" , punctuations);
    PRINTF("Number of miscell char = %d\n" , miscell);
    PRINTF("Number of char passed = %d\n" , count);

}
