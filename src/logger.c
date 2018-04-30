/*
 * logger.c
 *
 *  Created on: Apr 24, 2018
 *      Author: Shreya
 */


#include "logger.h"
#include "circbuf.h"
#include "conversion.h"
#include "data_processing.h"
#include "logger_queue.h"

//#define KL25Z

#ifdef KL25Z
#include "MKL25Z4.h"
#include "uart.h"
#include "rtc.h"


#else
#include <time.h>
#include <sys/time.h>
#endif

uint32_t checkSum= 0;
uint8_t buffer[20];


log_status log_create(log_struct_t * log_item , logger_enum_t ID, logger_module_t Module, size_t length, uint8_t * payload)
{
	log_status status = SUCCESS;
	if(log_item == NULL)
	{

		status = NULL_POINTER;

	}

	log_item -> log_ID = (int8_t)ID;
	log_item -> Module_ID = (int8_t)Module;
	log_item -> log_Length = length;
	#ifdef KL25Z
	time_t tStamp = RTC_TSR;
	log_item -> Timestamp = tStamp;
	log_item -> Timestamp = RTC_TSR;

   	 #else
	struct timeval start;
	gettimeofday(&start, NULL);
	log_item->Timestamp = (uint8_t)start.tv_sec;
	#endif
	if(payload != NULL)
	{
		log_item->Payload = (uint8_t *)malloc(length * sizeof(uint8_t));
		if(log_item->Payload != NULL)
		{
			int i;
			for(i = 0; i < length; i++)
			{
				*(log_item->Payload + i) = *(payload + i);
			}
		}			
	}
	checkSum = (log_item->log_ID) + (log_item->Module_ID)+(log_item->Timestamp) +(log_item->log_Length);

	log_item ->Checksum = checkSum;

	return status;
}


log_status log_create1(log_struct_t2 * log_item , logger_enum_t ID, logger_module_t Module, size_t length, uint32_t  payload)
{
	log_status status = SUCCESS;
	if(log_item == NULL)// || payload == NULL)
	{

		status = NULL_POINTER;

	}

	log_item -> log_ID = (int8_t)ID;
	log_item -> Module_ID = (int8_t)Module;
	log_item -> log_Length = length;
	#ifdef KL25Z
	time_t tStamp = RTC_TSR;
	log_item -> Timestamp = tStamp;
	log_item -> Timestamp = RTC_TSR;

    #else
	struct timeval time;
	gettimeofday(&time, NULL);
	log_item->Timestamp = (uint8_t)time.tv_sec;
	#endif

	log_item -> Payload = payload;

	checkSum = (log_item->log_ID) + (log_item->Module_ID)+(log_item->Timestamp) +(log_item->log_Length);

	log_item ->Checksum = checkSum;

	return status;
}


#ifdef KL25Z
log_status log_data_KL25Z(cb_struct * CB_ptr, uint8_t * ptr, size_t length)
{
	log_status status = SUCCESS;
	if(CB_ptr == NULL || ptr == NULL)
	{
		status = NULL_POINTER;
	}

	while(length != 0)
	{
		cb_buffer_add_item(CB_ptr, *ptr);
		//UART_send(*ptr);
		length--;
		ptr++;
	}
	return status;
}




log_status log_string_KL25Z(cb_struct * CB_ptr, uint8_t * ptr)
{
	log_status status = SUCCESS;
		if(CB_ptr == NULL || ptr == NULL)
		{

			status = NULL_POINTER;

		}
	while(*ptr != '\0')
	{
		cb_buffer_add_item(CB_ptr, *ptr);
		//UART_send(*ptr);
		ptr++;
	}
		return status;
}

log_status log_integer_KL25Z(cb_struct * CB_ptr, int32_t data)// Takes an integer and logs that to the terminal (use itoa)
{

	uint8_t * ptr;
	log_status status = SUCCESS;
	if(CB_ptr == NULL)
		{

		status = NULL_POINTER;

		}
	ptr =My_itoa(data, (uint8_t*)CB_ptr,10); // Converting in base 10


	while(*ptr!= '\0')
		{

			cb_buffer_add_item(CB_ptr, *ptr);
			//UART_send(*ptr);
			ptr++;

		}
	return status;
}



log_status UART_data_display(uint8_t * ptr, size_t length)
{
	log_status status = SUCCESS;
		if(ptr == NULL)
			{

			status = NULL_POINTER;

			}

	while(length != 0)
	{
		if(*ptr != 0)
		UART_send(*ptr);
		ptr++;
		length--;
	}
	return status;
}

log_status UART_string_display(uint8_t * ptr)
{

	log_status status = SUCCESS;
		if(ptr == NULL)
			{

			status = NULL_POINTER;

			}

	while(* ptr != '\0')
	{
		if(*ptr != 0)
		UART_send(*ptr);
		ptr++;
	}
	return status;
}

log_status UART_integer_display(int32_t data)
{
	uint8_t * ptr = (uint8_t *)malloc(sizeof(data));

	ptr = My_itoa(data, (uint8_t*)ptr, 10);

	while(* ptr != '\0')
	{
		if(*ptr != 0)
		UART_send(*ptr);
		ptr++;
	}

	return SUCCESS;
}



log_status log_flush_KL25Z(cb_struct * CB_ptr)
{
	log_status status = SUCCESS;
	if(CB_ptr == NULL)
	{

	status = NULL_POINTER;

	}
	if(flag==0)
	{
	uint8_t enter1[] = "\r\n";
	UART_send_n(enter1,4);
	}

	__disable_irq();
	int8_t a;
	int8_t * ptr;
	ptr = &a;
	while(CB_ptr -> count != 0)
	{
		cb_buffer_remove_item(CB_ptr,ptr);
		{
		if((a != 0 && a >= 97 && a <= 122 )||( a >= 65 &&a <= 90)
				|| (a >= 48 && a <= 57)
				||(a == 33) ||( a == 34 )|| (a == 44) ||( a == 46)
				|| (a == 45) ||( a == 58) ||( a == 59) || (a == 39)
				|| (a == 91) || (a == 93) ||( a == 40) || (a == 41 )||( a == 63) || (a ==13) ||( a == 20) || (a ==32))
		UART_send(*ptr);
		}

	}
	__enable_irq();

	return status;
}

log_status log_item_KL25Z(cb_struct * CB_ptr, log_struct_t *log_item)
{
	log_status status = SUCCESS;
	if(CB_ptr == NULL || log_item == NULL)
	{
		return NULL_POINTER;
	}

	uint8_t ID[] = "Log ID: ";
	uint8_t Module[]= "Module_ID:";
	uint8_t Payload[] = "PayLoad: ";
	uint8_t Time[] = "Timestamp: ";
	uint8_t Checksum[] = "Checksum: ";

	if(log_item -> log_ID == 19 && beat == 0)
	{

	}
	else if(log_item -> log_ID != 19)
	{

	log_data_KL25Z(CB_ptr, ID, 8);  //to display log id
	log_integer_KL25Z(CB_ptr, log_item -> log_ID);
	log_data_KL25Z(CB_ptr,(uint8_t*) " ", 1);
	log_data_KL25Z(CB_ptr, Module, 11);//to display module id
	log_integer_KL25Z(CB_ptr, log_item -> Module_ID);
	log_data_KL25Z(CB_ptr,(uint8_t*) " ", 1);
	log_data_KL25Z(CB_ptr, Time, 11);// to display time
	log_integer_KL25Z(CB_ptr, log_item -> Timestamp);
	log_data_KL25Z(CB_ptr, (uint8_t*)" ", 1);


	if(log_item -> log_Length != 0)
	{

		log_data_KL25Z(CB_ptr, Payload, 9);
		log_data_KL25Z(CB_ptr, log_item -> Payload, log_item -> log_Length);
		log_data_KL25Z(CB_ptr,(uint8_t*) " ", 1);
	}

	log_data_KL25Z(CB_ptr, Checksum, 10);
	log_integer_KL25Z(CB_ptr, log_item -> Checksum);
	log_data_KL25Z(CB_ptr, (uint8_t*)" ", 1);

	}

	else if(log_item -> log_ID == 19 && beat == 1)
	{
		log_data_KL25Z(CB_ptr, ID, 8);
		log_integer_KL25Z(CB_ptr, log_item -> log_ID);
		log_data_KL25Z(CB_ptr,(uint8_t*) " ", 1);
		log_data_KL25Z(CB_ptr, Module, 11);//to display module id
		log_integer_KL25Z(CB_ptr, log_item -> Module_ID);
		log_data_KL25Z(CB_ptr,(uint8_t*) " ", 1);
		log_data_KL25Z(CB_ptr, Time, 11);// to display time
		log_integer_KL25Z(CB_ptr, log_item -> Timestamp);
		log_data_KL25Z(CB_ptr, (uint8_t*)" ", 1);

		if(log_item -> log_Length != 0)
		{
		log_data_KL25Z(CB_ptr, Payload, 9);
		log_data_KL25Z(CB_ptr, log_item -> Payload, log_item -> log_Length);
		log_data_KL25Z(CB_ptr,(uint8_t*) " ", 1);
		}

		log_data_KL25Z(CB_ptr, Checksum, 10);
		log_integer_KL25Z(CB_ptr, log_item -> Checksum);
		log_data_KL25Z(CB_ptr, (uint8_t*)" ", 1);

	}
	return status;
}

log_status log_item_KL25Z2(cb_struct * CB_ptr, log_struct_t2 *log_item)
{
	log_status status = SUCCESS;
	if(CB_ptr == NULL || log_item == NULL)
	{
		return NULL_POINTER;
	}

	uint8_t ID[] = "Log ID: ";
	uint8_t Module[]= "Module_ID:";
	uint8_t Payload[] = "PayLoad: ";
	uint8_t Time[] = "Timestamp: ";
	uint8_t Checksum[] = "Checksum: ";

	if(log_item -> log_ID == 19 && beat == 0)
	{

	}
	else if(log_item -> log_ID != 19)
	{

	log_data_KL25Z(CB_ptr, ID, 8);  //to display log id
	log_integer_KL25Z(CB_ptr, log_item -> log_ID);
	log_data_KL25Z(CB_ptr,(uint8_t*) " ", 1);
	log_data_KL25Z(CB_ptr, Module, 11);//to display module id
	log_integer_KL25Z(CB_ptr, log_item -> Module_ID);
	log_data_KL25Z(CB_ptr,(uint8_t*) " ", 1);
	log_data_KL25Z(CB_ptr, Time, 11);// to display time
	log_integer_KL25Z(CB_ptr, log_item -> Timestamp);
	log_data_KL25Z(CB_ptr, (uint8_t*)" ", 1);
	log_data_KL25Z(CB_ptr, Payload, 9);

	if(log_item -> log_Length != 0)
	{
		log_integer_KL25Z(CB_ptr,(int32_t)(log_item -> Payload));//, log_item -> log_Length);


	}
	log_data_KL25Z(CB_ptr,(uint8_t*) " ", 1);

	log_data_KL25Z(CB_ptr, Checksum, 10);
	log_integer_KL25Z(CB_ptr, log_item -> Checksum);
	log_data_KL25Z(CB_ptr, (uint8_t*)" ", 1);


	}

	else if(log_item -> log_ID == 19 && beat == 1)
	{
		log_data_KL25Z(CB_ptr, ID, 8);
				log_integer_KL25Z(CB_ptr, log_item -> log_ID);
				log_data_KL25Z(CB_ptr,(uint8_t*) " ", 1);
				log_data_KL25Z(CB_ptr, Module, 11);//to display module id
				log_integer_KL25Z(CB_ptr, log_item -> Module_ID);
				log_data_KL25Z(CB_ptr,(uint8_t*) " ", 1);
				log_data_KL25Z(CB_ptr, Time, 11);// to display time
				log_integer_KL25Z(CB_ptr, log_item -> Timestamp);
				log_data_KL25Z(CB_ptr, (uint8_t*)" ", 1);

				if(log_item -> log_Length != 0)
					{
						log_integer_KL25Z(CB_ptr,(log_item -> Payload));//, log_item -> log_Length);
						(log_item -> log_Length)--;

					}
		log_data_KL25Z(CB_ptr, Checksum, 10);
		log_integer_KL25Z(CB_ptr, log_item -> Checksum);
		log_data_KL25Z(CB_ptr, (uint8_t*)" ", 1);

	}
	return status;
}

#else 
log_status log_string_BBB(cb_struct * CB_ptr, uint8_t * ptr)
{
	log_status status = SUCCESS;
			if(CB_ptr == NULL || ptr == NULL)
			{

				status = NULL_POINTER;

			}

	while(ptr != '\0')
	{
		cb_buffer_add_item(CB_ptr, *ptr);
		//printf("%c",*(ptr));
		ptr++;
	}
	return status;
}

log_status log_data_BBB(cb_struct * CB_data, uint8_t * ptr, size_t length)
{
	log_status status = SUCCESS;
	if(CB_ptr == NULL || ptr == NULL)
	{

		status = NULL_POINTER;

	}

	while(length != 0)
	{
		cb_buffer_add_item(CB_ptr, *ptr);
		//printf("%c",*(ptr));
		length--;
		ptr++;
	}
	
	return status;
}


log_status log_integer_BBB(cb_struct * CB_ptr, int32_t data)// Takes an integer and logs that to the terminal (use itoa)
{

	uint8_t *  ptr;
	log_status status = SUCCESS;
	if(CB_ptr == NULL)
		{

		status = NULL_POINTER;

		}
	ptr =My_itoa(data, (uint8_t*)CB_ptr,10); // Converting in base 10

	while(*ptr!= '\0')
		{

			cb_buffer_add_item(CB_ptr, *ptr);
			//printf("%c",*ptr);
			ptr++;

		}
	return status;
}
log_status log_flush_BBB(cb_struct * CB_ptr)
{
	log_status status = SUCCESS;
	if(CB_ptr == NULL)
	{

	status = NULL_POINTER;

	}
	printf("\r\n");


	int8_t a;
	int8_t * ptr;
	ptr = &a;
	while(CB_ptr -> count != 0)
	{
		cb_buffer_remove_item(CB_ptr,ptr);
		{
		if((a != 0 && a >= 97 && a <= 122 )||( a >= 65 &&a <= 90)
				|| (a >= 48 && a <= 57)
				||(a == 33) ||( a == 34 )|| (a == 44) ||( a == 46)
				|| (a == 45) ||( a == 58) ||( a == 59) || (a == 39)
				|| (a == 91) || (a == 93) ||( a == 40) || (a == 41 )||( a == 63) || (a ==13) ||( a == 20) || (a ==32))
			printf("%c", *ptr);
		}

	}
	printf("\r\n");


	return status;
}




log_status log_item_BBB(cb_struct * CB_ptr, log_struct_t *log_item)
{
	log_status status = SUCCESS;
	if(CB_ptr == NULL || log_item == NULL)
	{
		return NULL_POINTER;
	}

	uint8_t ID[] = "Log ID: ";
	uint8_t Module[]= "Module_ID:";
	uint8_t Payload[] = "PayLoad: ";
	uint8_t Time[] = "Timestamp: ";
	uint8_t Checksum[] = "Checksum: ";

	if(log_item -> log_ID != 20)
	{

	log_data_BBB(CB_ptr, ID, 8);  //to display log id
	log_integer_BBB(CB_ptr, log_item -> log_ID);
	log_data_BBB(CB_ptr,(uint8_t*) " ", 1);
	log_data_BBB(CB_ptr, Module, 11);//to display module id
	log_integer_BBB(CB_ptr, log_item -> Module_ID);
	log_data_BBB(CB_ptr,(uint8_t*) " ", 1);
	log_data_BBB(CB_ptr, Time, 11);// to display time
	log_integer_BBB(CB_ptr, log_item -> Timestamp);
	log_data_BBB(CB_ptr, (uint8_t*)" ", 1);

	if(log_item -> log_Length != 0)
	{

		log_data_BBB(CB_ptr, Payload, 9);
		log_data_BBB(CB_ptr, log_item -> Payload, log_item -> log_Length);
		log_data_BBB(CB_ptr,(uint8_t*) " ", 1);
	}

	log_data_BBB(CB_ptr, Checksum, 10);
	log_integer_BBB(CB_ptr, log_item -> Checksum);
	log_data_BBB(CB_ptr, (uint8_t*)" ", 1);


	printf("\r\n");
	}
	
	return status;
}

log_status log_item_BBB2(cb_struct * CB_ptr, log_struct_t2 *log_item)
{
	log_status status = SUCCESS;
	if(CB_ptr == NULL || log_item == NULL)
	{
		return NULL_POINTER;
	}

	uint8_t ID[] = "Log ID: ";
	uint8_t Module[]= "Module_ID:";
	uint8_t Payload[] = "PayLoad: ";
	uint8_t Time[] = "Timestamp: ";
	uint8_t Checksum[] = "Checksum: ";

	if(log_item -> log_ID != 20)
	{

	log_data_BBB(CB_ptr, ID, 8);  //to display log id
	log_integer_BBB(CB_ptr, log_item -> log_ID);
	log_data_BBB(CB_ptr,(uint8_t*) " ", 1);
	log_data_BBB(CB_ptr, Module, 11);//to display module id
	log_integer_BBB(CB_ptr, log_item -> Module_ID);
	log_data_BBB(CB_ptr,(uint8_t*) " ", 1);
	log_data_BBB(CB_ptr, Time, 11);// to display time
	log_integer_BBB(CB_ptr, log_item -> Timestamp);
	log_data_BBB(CB_ptr, (uint8_t*)" ", 1);
	log_data_BBB(CB_ptr, Payload, 9);


	if(log_item -> log_Length != 0)
	{
		log_integer_BBB(CB_ptr,(log_item -> Payload));//, log_item -> log_Length);
		(log_item -> log_Length)--;

	}
	log_data_BBB(CB_ptr,(uint8_t*) " ", 1);

	log_data_BBB(CB_ptr, Checksum, 10);
	log_integer_BBB(CB_ptr, log_item -> Checksum);
	log_data_BBB(CB_ptr, (uint8_t*)" ", 1);


	printf("\r\n");
	}

	return status;
}
#endif
