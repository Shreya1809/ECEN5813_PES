#include "logger.h"
#include "logger_queue.h"
#include "rtc.h"
int platform_flag;


uint32_t getlogtime()
{	if (platform_flag = 1)
	{
		gettimeofday(&log_time,NULL);
		return log_time.tv_usec;
	}
	else return RTC_TSR;
}
#ifdef KL25Z
//KL25Z FUNCTIONS
uint8_t buffer[20];
platform_flag = 1;

/*Takes a pointer to sequence of bytes and length of bytes to log*/
void log_data_KL25Z(uint32_t *ptr,size_t length)
{
	while(!ptr)
	{
	  UART_send_n(ptr,length);
	}
}	
		    

void log_string_KL25Z(char *ptr)//Takes a c-string and logs that to the terminal
{
	int i = 0;
	while(*(ptr+j)!='\0')
	{
	   Uart_send(*(ptr+j));// UART_send(uint8_t data)
	}
}
void log_integer_KL25Z(uint32_t a)// Takes an integer and logs that to the terminal (use itoa)
{
	size_t length;
	length=my_itoa(data,buffer,T10); // Converting in base 10
	log_data_KL25Z(buffer,length);
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
platform_flag = 0;
void log_data_BBB(uint32_t *ptr,size_t length)//Takes a pointer to sequence of bytes and length of bytes to log
{
	int i =0;
	if(ptr!=NULL) 
	{
		for(j=0;i<length;i++)
		{
		printf("%c",*(ptr+i));
	 	}
	}
}
void log_string_BBB(char *ptr)//Takes a c-string and logs that to the terminal
{
	int = 0;
	while(*(ptr+i)!='\0') // print characters till string termination character
	{
		printf("%c",*(ptr+i));
		i++;
	}
}
void log_integer_BBB(uint32_t a)// Takes an integer and logs that to the terminal (use itoa)
{
	size_t length;
	length=my_itoa(data,buffer,T10); // Converting in base 10
	log_data_BBB(buffer,length);
}



#endif
