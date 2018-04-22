#include "logger.h"
#include "logger_queue.h"
#include <malloc.h>
#include "uart.h"
int platform_flag;
uint8_t buffer[20];



#ifdef KL25Z
#include "rtc.h"
#include "MKL25Z4.h"
//KL25Z FUNCTIONS

char logID_show[21][25];
//log_struct *logStructFill;

/*Takes a pointer to sequence of bytes and length of bytes to log*/
void log_data_KL25Z(uint32_t *ptr,size_t length)
{
	while(!ptr)
	{
	  UART_send_n((uint8_t*)ptr,length);
	}
}	
		    

void log_string_KL25Z(char *ptr)//Takes a c-string and logs that to the terminal
{
	int i = 0;
	while(*(ptr+i)!='\0')
	{
	   UART_send(*(ptr+i));// UART_send(uint8_t data)
	   i++;
	}
}
void log_integer_KL25Z(uint32_t a)// Takes an integer and logs that to the terminal (use itoa)
{
	size_t length;
	length=my_itoa(a,buffer,10); // Converting in base 10
	log_data_KL25Z((uint32_t*)buffer,length);
}
void log_flush_KL25Z(CB_log_struct* src_ptr)//Blocks until the current logger buffer is empty
{
	log_struct data;
	while(log_cb_is_empty(src_ptr)!=1)
	{
		log_cb_remove(&data,src_ptr);
		log_print(&data);
	}	
}

/*
@brief gives the timelog
@return returns seconds 
*/
uint32_t getlogtime(){
	return RTC_TSR;
}

#else
//BBB FUNCTIONS

void log_data_BBB(uint32_t *ptr,size_t length)//Takes a pointer to sequence of bytes and length of bytes to log
{
	int i =0;
	if(ptr!=NULL) 
	{
		for(i=0;i<length;i++)
		{
		printf("%c",*(ptr+i));
	 	}
	}
}
void log_string_BBB(char *ptr)//Takes a c-string and logs that to the terminal
{
	int i = 0;
	while(*(ptr+i)!='\0') // print characters till string termination character
	{
		printf("%c",*(ptr+i));
		i++;
	}
}
void log_integer_BBB(uint32_t a)// Takes an integer and logs that to the terminal (use itoa)
{
	size_t length;
	uint8_t buffer[20];
	length=my_itoa(a,buffer,10); // Converting in base 10
	log_data_BBB((uint32_t*)buffer,length);
}

uint32_t getlogtime()
{
	
		gettimeofday(&log_time,NULL);
		return log_time.tv_usec;
	
}



#endif
