/**
 * @file data_processing.c
 * @brief Character counting and statistics functions
 * @author Miles Frain
 * @author Shreya Chakraborty
 * @version 1
 * @date 2018-03-04
 */

#include <stdint.h>
#include "logger.h"
#include "circbuf.h"
#include "platform.h"
#include "conversion.h"
#include "logger_queue.h"
#ifdef KL25Z
#include "uart.h"
#endif

static uint32_t alphabet= 0;
static uint32_t number= 0;
static uint32_t punctuations= 0;
static uint32_t miscell= 0;
//static uint32_t current_data= 0;
static uint32_t count = 0;
int8_t beat = 1;



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

uint8_t miscelleneous(uint8_t value)
{
	if (value != '\e' && value != '\r' && value != '\t')
	{
		return 1;
	}
		else return 0;
}
void print_data_process_header(void)
{
    PRINTF("\n----------------- Character Statistics -----------------\n");
    PRINTF("---------------------------------------------------------\n");
    PRINTF("Letter\t | Number\t | Punctuation\t | Misc\t | Total\n");
    PRINTF("--------------------------------------------------------\n");
}

void data_statistics(int8_t character)
{
#ifdef KL25Z
	UART0_C2 &= ~UART0_C2_TIE_MASK;
	UART0_C2 &= ~UART0_C2_RIE_MASK;
#endif

    {

            if(alphabetical(character))
            {
                alphabet++;

            }
            else if(numerical(character))
            {
                number++;
            }
            else if(punctuation(character))
            {
                punctuations++;
            }
            else if (miscelleneous(character))
            {
                miscell++;
            }
            count++;
        }
    }
void print_data_entered()
{
	#ifdef KL25Z
	PRINTF("\n----------------- Character Statistics -----------------\n");
	    PRINTF("---------------------------------------------------------\n");
	    PRINTF("Letter\t | Number\t | Punctuation\t | Misc\t | Total\n");
	    PRINTF("--------------------------------------------------------\n");

    char line[200];
    char len = sprintf(line,
            " %lu\t | %lu\t\t | %lu\t\t | %lu\t | %lu\r\n",
            alphabet, number, punctuations, miscell, count);
    UART_send_n((uint8_t*)line, len);
	#else

	printf("\n----------------- Character Statistics -----------------\n");
	printf("---------------------------------------------------------\n");
	printf("Letter\t | Number\t | Punctuation\t | Misc\t | Total\n");
	printf("--------------------------------------------------------\n");
	printf(" %d\t | %d\t\t | %d\t\t | %d\t | %d\n",alphabet, number, punctuations, miscell, count);

	#endif

}
void print_all_log()
{
	#ifdef KL25Z
	UART0_C2 &= ~UART0_C2_TIE_MASK;
	UART0_C2 &= ~UART0_C2_RIE_MASK;
	logged_data = (log_struct_t *) malloc(sizeof(log_struct_t));

	    {
		    UART_send_n((uint8_t*)"\r\n", 4);
			UART_send_n((uint8_t*)" AALPHABET: ", 12);
			uint8_t x[10];
			uint8_t * p;
			uint8_t *alpha; //temp pointer to keep a copy
			p = &x[0];
			alpha = p;
			uint8_t len5;
			len5= my_itoa(alphabet, p, 10);

					while(*p != '\0')
					{
						UART_send(*p);
						p++;
					}
			UART_send_n((uint8_t*)"\r\n", 4);

			log_create(logged_data, DATA_ALPHA_COUNT,DATA_PROCESSIING, len5,alpha);
			log_item_KL25Z(tx_buffer, logged_data);
			LOG_FLUSH(tx_buffer);

			UART_send_n((uint8_t*)" NUMBER: ", 10);
			uint8_t y[10];
			uint8_t * q;
			uint8_t *num;
			uint8_t len4;
			q = &y[0];
			num = q; //stores the value of payload
			len4 = my_itoa(number, q, 10);

					while(*q != '\0')
					{
						UART_send(*q);
						q++;
					}
			UART_send_n((uint8_t*)"\r\n", 4);
			log_create(logged_data, DATA_NUMERIC_COUNT,DATA_PROCESSIING, len4,num);
			log_item_KL25Z(tx_buffer, logged_data);
			LOG_FLUSH(tx_buffer);


			UART_send_n((uint8_t*)" PUNCTUATION: ", 15);
			uint8_t z[10];
			uint8_t * r;
			uint8_t *punc;
			uint8_t len3;
			r = &z[0];
			punc = r;
			len3 = my_itoa(punctuations, r, 10);

					while(*r != '\0')
					{
						UART_send(*r);
						r++;
					}
			UART_send_n((uint8_t*)"\r\n", 4);
			log_create(logged_data, DATA_PUNCTUATION_COUNT,DATA_PROCESSIING, len3,punc);
			log_item_KL25Z(tx_buffer, logged_data);
			LOG_FLUSH(tx_buffer);


			UART_send_n((uint8_t*)" MISCELL: ", 10);
			uint8_t w[10];
			uint8_t * s;
			uint8_t len1;
			uint8_t *mis;
			s = &w[0];
			mis = s;
			len1 = my_itoa(miscell, s, 10);

					while(*s != '\0')
					{
						UART_send(*s);
						s++;
					}
			UART_send_n((uint8_t*)"\r\n", 4);
			log_create(logged_data, DATA_MISC_COUNT,DATA_PROCESSIING, len1,mis);
			log_item_KL25Z(tx_buffer, logged_data);
			LOG_FLUSH(tx_buffer);

			UART_send_n((uint8_t*)" COUNT: ", 10);
			uint8_t v[10];
			uint8_t *c;
			uint8_t len2;
			uint8_t * t;
			t = &v[0];
			c=t;

			len2 = my_itoa(count, t, 10);

					while(*t != '\0')
					{
						UART_send(*t);
						t++;
					}
			UART_send_n((uint8_t*)"\r\n", 4);
			log_create(logged_data, DATA_ANALYSIS_COMPLETED,DATA_PROCESSIING, len2,c);
			log_item_KL25Z(tx_buffer, logged_data);
			LOG_FLUSH(tx_buffer);
		}
		#else
		 {
		    printf("\r\n ALPHABET : %d ", alphabet);
			uint8_t x[10];
			uint8_t *alpha; //temp pointer to keep a copy
			alpha = &x[0];
			uint8_t len5;
			len5= my_itoa(alphabet, alpha, 10);		
			printf("\r\n");
			log_create(logged_data, DATA_ALPHA_COUNT,DATA_PROCESSIING, len5,alpha);
			LOG_RAW_ITEM(tx_buffer, logged_data);
			LOG_FLUSH(tx_buffer);

			printf("\r\n NUMBERS : %d ", number);
			uint8_t y[10];
			uint8_t *num;
			uint8_t len4;
			num = &y[0];
			len4 = my_itoa(number, num, 10);
			printf("\r\n");
			log_create(logged_data, DATA_NUMERIC_COUNT,DATA_PROCESSIING, len4,num);
			LOG_RAW_ITEM(tx_buffer, logged_data);
			LOG_FLUSH(tx_buffer);


			printf("\r\n PUNCTUATION: %d ", punctuations);
			uint8_t z[10];
			uint8_t *punc;
			uint8_t len3;
			punc = &z[0];
			len3 = my_itoa(punctuations, punc, 10);
			printf("\r\n");
			log_create(logged_data, DATA_PUNCTUATION_COUNT,DATA_PROCESSIING, len3,punc);
			LOG_RAW_ITEM(tx_buffer, logged_data);
			LOG_FLUSH(tx_buffer);


			printf("\r\n MISCELL: %d ", miscell);
			uint8_t w[10];
			uint8_t len1;
			uint8_t *mis;
			mis = &w[0];
			len1 = my_itoa(miscell, mis, 10);
			printf("\r\n");
			log_create(logged_data, DATA_MISC_COUNT,DATA_PROCESSIING, len1,mis);
			LOG_RAW_ITEM(tx_buffer, logged_data);
			LOG_FLUSH(tx_buffer);

			printf("\r\n COUNT:  %d ", count);
			uint8_t v[10];
			uint8_t *c;
			uint8_t len2;
			c = &v[0];
			len2 = my_itoa(count, c, 10);
			printf("\r\n");
			log_create(logged_data, DATA_ANALYSIS_COMPLETED,DATA_PROCESSIING, len2,c);
			LOG_RAW_ITEM(tx_buffer, logged_data);
			LOG_FLUSH(tx_buffer);
	    }

		#endif
	    

}


void heartbeat()
{
	if (beat == 1)
	{
		beat = 0;
	}
	else beat = 1;
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
    //while (!cb_is_empty(buf))
    {
        cb_enum status = cb_buffer_remove_item(buf, (int8_t*)&current_data);
        if (status == CB_SUCCESS)
        {
            if(alphabetical(current_data))
            {
                alphabet++;
                //log_create(logged_data, DATA_ALPHA_COUNT,DATA_PROCESSIING, 1,(uint8_t *)1);
                //log_item_KL25Z(rx_buffer, logged_data);

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
