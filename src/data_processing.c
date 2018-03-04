
#include "data_processing.h"




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

void data_process(cb_struct *rx_buffer)
{
    //variables to keep count
    static uint8_t alphabet= 0;
    static uint8_t number= 0;
    static uint8_t punctuations= 0;
    static uint8_t miscell= 0;
    static uint8_t current_data= 0;
    static uint8_t count = 0;
    int16_t a = 2000;
    {


        cb_enum status;
	while (a--)
	{
        status = cb_buffer_remove_item(rx_buffer, (int8_t*)&current_data);
        if (status == CB_SUCCESS)
	
        {

            if(alphabetical(current_data))
            {
                alphabet++; count++;

            }
            else if(numerical(current_data))
            {
                number++;count++;
            }
            else if(punctuation(current_data))
            {
                punctuations++;count++;
            }
            else
            {
                miscell++;count++;
            }
		
        }}

    }

    printf("---------statistics---------\n");
    printf("Number of alphabets = %d\n" , alphabet);
    printf("Number of numbers = %d\n" , number);
    printf("Number of punctuations = %d\n" , punctuations);
    printf("Number of miscell char = %d\n" , miscell);
    printf("Number of char passed = %d\n" , count);

}
