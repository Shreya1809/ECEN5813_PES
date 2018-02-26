#include <stdio.h>
#include <stdint.h>
#include "conversion.h"
#include "circbuf.h"

#define ALPHANUMERIC_A   (65)
#define ALPHANUMERIC_Z	 (90)
#define alphanumeric_a	(97)
#define alphanumeric_z	(122)
#define number_0		(48)
#define number_9		(57)

//variables to keep count
uint8_t alphabet= 0;
uint8_t number= 0;
uint8_t punctuations= 0;
uint8_t miscell= 0;
uint8_t current_data= 0;



uint8_t alphabetical(uint8_t value) // to check if alphabet
{
	if ((value >= ALPHANUMERIC_A && value =< ALPHANUMERIC_Z) || (value >= alphanumeric_a && value =< alphanumeric_z))
			return 1;
		else
			return 0;
}
uint8_t numberical(uint8_t value)// to check if number
{
	if (value >= number_0 && value =< number_9)
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

void data_process()
{
	cb_enum status;
	status = cb_enum cb_is_empty(rx_buffer);
	if ((status ==  NULL_POINTER_ERROR) || status == BUFFER_EMPTY)
	{
		return status;
	}
	else
	{
		status = cb_enum cb_buffer_remove_item(rx_buffer, current_data);
		if ((status ==  WRAP_REMOVAL) || status == REMOVAL_SUCCESSFUL)
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
						miscell++
					}

			}
	}

	printf("---------statistics---------\n")
	printf("Number of alphabets = %d\n" , alphabet);
	printf("Number of numbers = %d\n" , number);
	printf("Number of punctuations = %d\n" , punctuations);
	printf("Number of miscell char = %d\n" , miscell);

}
