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
#include "string.h"

//#define KL25Z

#ifdef KL25Z
#include "MKL25Z4.h"
#include "uart.h"
#include "rtc.h"

extern

#else
#include <time.h>
#include <sys/time.h>
#endif

//uint32_t checkSum= 0;
uint8_t buffer[20];

extern volatile uint8_t binary_logger;

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
//	time_t tStamp = RTC_TSR;
//	log_item -> Timestamp = tStamp;
	log_item -> Timestamp = RTC_TSR;

   	 #else
	struct timeval start;
	gettimeofday(&start, NULL);
	log_item->Timestamp = (uint8_t)start.tv_sec;
	#endif
	if(payload != NULL)
	{
//		log_item->Payload = (uint8_t *)malloc(length * sizeof(uint8_t));
//		if(log_item->Payload != NULL)
//		{
//			int i;
//			for(i = 0; i < length; i++)
//			{
//				*(log_item->Payload + i) = *(payload + i);
//			}
//		}

		strncpy((char*)log_item -> Payload, (const char*)payload, sizeof(log_item -> Payload));
	}

	uint32_t checkSum= 0;
	checkSum = (log_item->log_ID) + (log_item->Module_ID)+(log_item->Timestamp); //+(log_item->log_Length);
	size_t len = sizeof(log_item -> Payload);
	for(int i = 0;i < len; i++)
	{
		checkSum += log_item -> Payload[i];
	}

	log_item ->Checksum = checkSum;

	return status;
}


log_status log_create1(log_struct_t * log_item , logger_enum_t ID, logger_module_t Module, size_t length, uint32_t  payload)
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

	uint8_t buff[10] = {0};
	size_t len = my_itoa(payload, buff, 10);

	strncpy((char*)log_item -> Payload, (const char*)buff, sizeof(log_item -> Payload));

	uint32_t checkSum= 0;
	checkSum = (log_item->log_ID) + (log_item->Module_ID)+(log_item->Timestamp); //+(log_item->log_Length);
//	size_t len = sizeof(log_item -> Payload);
	for(int i = 0;i < len; i++)
	{
		checkSum += log_item -> Payload[i];
	}

	log_item ->Checksum = checkSum;

//	log_item -> Payload = payload;
//
//	checkSum = (log_item->log_ID) + (log_item->Module_ID)+(log_item->Timestamp);// +(log_item->log_Length);
//
//	log_item ->Checksum = checkSum;

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

	while(length != 0 && ptr)
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
	if(binary_logger)
	{
		return log_binary(CB_ptr,log_item);
	}
	else
	{
		return log_item_KL25Z_readable(CB_ptr,log_item);
	}
}

log_status log_item_KL25Z_readable(cb_struct * CB_ptr, log_struct_t *log_item)
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
//		log_data_KL25Z(CB_ptr, log_item -> Payload, log_item -> log_Length);
		log_string_KL25Z(CB_ptr, log_item -> Payload);
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
//		log_data_KL25Z(CB_ptr, log_item -> Payload, log_item -> log_Length);
		log_string_KL25Z(CB_ptr, log_item -> Payload);
		log_data_KL25Z(CB_ptr,(uint8_t*) " ", 1);
		}

		log_data_KL25Z(CB_ptr, Checksum, 10);
		log_integer_KL25Z(CB_ptr, log_item -> Checksum);
		log_data_KL25Z(CB_ptr, (uint8_t*)" ", 1);

	}
	return status;
}

log_status log_item_KL25Z2(cb_struct * CB_ptr, log_struct_t *log_item)
{
	return log_item_KL25Z(CB_ptr,log_item);
}
//	log_status status = SUCCESS;
//	if(CB_ptr == NULL || log_item == NULL)
//	{
//		return NULL_POINTER;
//	}
//
//	uint8_t ID[] = "Log ID: ";
//	uint8_t Module[]= "Module_ID:";
//	uint8_t Payload[] = "PayLoad: ";
//	uint8_t Time[] = "Timestamp: ";
//	uint8_t Checksum[] = "Checksum: ";
//
//	if(log_item -> log_ID == 19 && beat == 0)
//	{
//
//	}
//	else if(log_item -> log_ID != 19)
//	{
//
//	log_data_KL25Z(CB_ptr, ID, 8);  //to display log id
//	log_integer_KL25Z(CB_ptr, log_item -> log_ID);
//	log_data_KL25Z(CB_ptr,(uint8_t*) " ", 1);
//	log_data_KL25Z(CB_ptr, Module, 11);//to display module id
//	log_integer_KL25Z(CB_ptr, log_item -> Module_ID);
//	log_data_KL25Z(CB_ptr,(uint8_t*) " ", 1);
//	log_data_KL25Z(CB_ptr, Time, 11);// to display time
//	log_integer_KL25Z(CB_ptr, log_item -> Timestamp);
//	log_data_KL25Z(CB_ptr, (uint8_t*)" ", 1);
//	log_data_KL25Z(CB_ptr, Payload, 9);
//
////	if(log_item -> log_Length != 0)
////	{
////		log_integer_KL25Z(CB_ptr,(int32_t)(log_item -> Payload));//, log_item -> log_Length);
////	}
//
//	if()
//
//	log_data_KL25Z(CB_ptr,(uint8_t*) " ", 1);
//
//	log_data_KL25Z(CB_ptr, Checksum, 10);
//	log_integer_KL25Z(CB_ptr, log_item -> Checksum);
//	log_data_KL25Z(CB_ptr, (uint8_t*)" ", 1);
//
//
//	}
//
//	else if(log_item -> log_ID == 19 && beat == 1)
//	{
//		log_data_KL25Z(CB_ptr, ID, 8);
//				log_integer_KL25Z(CB_ptr, log_item -> log_ID);
//				log_data_KL25Z(CB_ptr,(uint8_t*) " ", 1);
//				log_data_KL25Z(CB_ptr, Module, 11);//to display module id
//				log_integer_KL25Z(CB_ptr, log_item -> Module_ID);
//				log_data_KL25Z(CB_ptr,(uint8_t*) " ", 1);
//				log_data_KL25Z(CB_ptr, Time, 11);// to display time
//				log_integer_KL25Z(CB_ptr, log_item -> Timestamp);
//				log_data_KL25Z(CB_ptr, (uint8_t*)" ", 1);
//
//				if(log_item -> log_Length != 0)
//					{
//						log_integer_KL25Z(CB_ptr,(log_item -> Payload));//, log_item -> log_Length);
//						(log_item -> log_Length)--;
//
//					}
//		log_data_KL25Z(CB_ptr, Checksum, 10);
//		log_integer_KL25Z(CB_ptr, log_item -> Checksum);
//		log_data_KL25Z(CB_ptr, (uint8_t*)" ", 1);
//
//	}
//	return status;
//}

//void log_binary_KL25Z(cb_struct * CB_ptr, log_struct_t *log_item)
//{
//	size_t head_data = sizeof(*log_item) - sizeof(log_item -> Checksum) - sizeof(log_item -> Payload)
//	log_raw_KL25Z(CB_ptr,(uint8_t*)log_item,head_data);
//	log_raw_KL25Z(CB_ptr, log_item -> Payload, sizeof(log_item -> Payload));
//	log_raw_KL25Z(CB_ptr, (uint8_t*)&log_item -> Checksum, sizeof(log_item -> Checksum));
//}

#else 
log_status log_string_BBB(cb_struct * CB_ptr, uint8_t * ptr)
{
	log_status status = SUCCESS;
			if(CB_ptr == NULL || ptr == NULL)
			{

				status = NULL_POINTER;

			}

	while(ptr && *ptr != '\0')
	{
		cb_buffer_add_item(CB_ptr, *ptr);
		//printf("%c",*(ptr));
		ptr++;
	}
	return status;
}

log_status log_data_BBB(cb_struct * CB_ptr, uint8_t * ptr, size_t length)
{
	log_status status = SUCCESS;
	if(CB_ptr == NULL || ptr == NULL)
	{

		status = NULL_POINTER;
		return status;

	}

	while(ptr && length != 0)
	{
		cb_buffer_add_item(CB_ptr, *ptr);
		//printf("%c",*(ptr));
		length--;
		ptr++;
	}
	
	return status;
}

log_status log_raw_BBB(cb_struct * CB_ptr, uint8_t *data, size_t len)// Takes an integer and logs that to the terminal (use itoa)
{

	log_status status = SUCCESS;
	if(CB_ptr == NULL || data == NULL)
	{

		status = NULL_POINTER;
		return status;

	}
	if(len <1)
	{
		status = ERROR;
		return ERROR;
	}
	while(data && len)
	{

		cb_enum status = cb_buffer_add_item(CB_ptr, *data);
		if(status !=CB_SUCCESS)
		{
			break;
		}
		data++;
		len--;
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


log_status log_item_BBB_readable(cb_struct * CB_ptr, log_struct_t *log_item)
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
	//		log_data_BBB(CB_ptr, log_item -> Payload, log_item -> log_Length);
	//		log_data_BBB(CB_ptr, log_item -> Payload, sizeof(log_item -> Payload));
		log_string_BBB(CB_ptr, log_item -> Payload);
		log_data_BBB(CB_ptr,(uint8_t*) " ", 1);
	}

	log_data_BBB(CB_ptr, Checksum, 10);
	log_integer_BBB(CB_ptr, log_item -> Checksum);
	log_data_BBB(CB_ptr, (uint8_t*)" ", 1);


	printf("\r\n");
	}

	return status;


}

log_status log_item_BBB(cb_struct * CB_ptr, log_struct_t *log_item)
{
	if(binary_logger)
	{
		return log_binary(CB_ptr,log_item);
	}
	else
	{
		return log_item_BBB_readable(CB_ptr,log_item);
	}
}

log_status log_item_BBB2(cb_struct * CB_ptr, log_struct_t *log_item)
{
	return log_item_BBB(CB_ptr, log_item);
//	log_status status = SUCCESS;
//	if(CB_ptr == NULL || log_item == NULL)
//	{
//		return NULL_POINTER;
//	}
//
//	uint8_t ID[] = "Log ID: ";
//	uint8_t Module[]= "Module_ID:";
//	uint8_t Payload[] = "PayLoad: ";
//	uint8_t Time[] = "Timestamp: ";
//	uint8_t Checksum[] = "Checksum: ";
//
//	if(log_item -> log_ID != 20)
//	{
//
//	log_data_BBB(CB_ptr, ID, 8);  //to display log id
//	log_integer_BBB(CB_ptr, log_item -> log_ID);
//	log_data_BBB(CB_ptr,(uint8_t*) " ", 1);
//	log_data_BBB(CB_ptr, Module, 11);//to display module id
//	log_integer_BBB(CB_ptr, log_item -> Module_ID);
//	log_data_BBB(CB_ptr,(uint8_t*) " ", 1);
//	log_data_BBB(CB_ptr, Time, 11);// to display time
//	log_integer_BBB(CB_ptr, log_item -> Timestamp);
//	log_data_BBB(CB_ptr, (uint8_t*)" ", 1);
//	log_data_BBB(CB_ptr, Payload, 9);
//
//
//	if(log_item -> log_Length != 0)
//	{
//		log_integer_BBB(CB_ptr,(log_item -> Payload));//, log_item -> log_Length);
//		(log_item -> log_Length)--;
//
//	}
//	log_data_BBB(CB_ptr,(uint8_t*) " ", 1);
//
//	log_data_BBB(CB_ptr, Checksum, 10);
//	log_integer_BBB(CB_ptr, log_item -> Checksum);
//	log_data_BBB(CB_ptr, (uint8_t*)" ", 1);
//
//
//	printf("\r\n");
//	}
//
//	return status;
}

//void log_binary_BBB(cb_struct * CB_ptr, log_struct_t *log_item)
//{
//	log_integer_BBB(CB_ptr, log_item -> log_ID);
//	log_integer_BBB(CB_ptr, log_item -> Module_ID);
//	log_integer_BBB(CB_ptr, log_item -> Timestamp);
//	log_integer_BBB(CB_ptr, (int32_t)log_item -> Payload);
//	log_integer_BBB(CB_ptr, log_item -> Checksum);
//}
//void log_binary_BBB2(cb_struct * CB_ptr, log_struct_t2 *log_item)
//{
//	log_integer_BBB(CB_ptr, log_item -> log_ID);
//	log_integer_BBB(CB_ptr, log_item -> Module_ID);
//	log_integer_BBB(CB_ptr, log_item -> Timestamp);
//	log_integer_BBB(CB_ptr, log_item -> Payload);
//	log_integer_BBB(CB_ptr, log_item -> Checksum);
//}
#endif


log_status log_binary(cb_struct * CB_ptr, log_struct_t *log_item)
{
	log_status status = SUCCESS;
	if(CB_ptr == NULL)
	{
		return NULL_POINTER;
	}
	size_t head_data = sizeof(*log_item) - sizeof(log_item -> Checksum) - sizeof(log_item -> Payload);
	status = log_raw_common(CB_ptr,(uint8_t*)log_item,head_data);
	if(status != SUCCESS)
	{
		return status;
	}
	status = log_raw_common(CB_ptr, log_item -> Payload, sizeof(log_item -> Payload));
	if(status != SUCCESS)
	{
		return status;
	}
	status = log_raw_common(CB_ptr, (uint8_t*)&log_item -> Checksum, sizeof(log_item -> Checksum));

	return status;
}

log_status log_raw_common(cb_struct * CB_ptr, uint8_t *data, size_t len)
{

	log_status status = SUCCESS;
	if(CB_ptr == NULL || data == NULL)
	{

		status = NULL_POINTER;
		return status;

	}
	if(len <1)
	{
		status = ERROR;
		return ERROR;
	}
	while(data && len)
	{

		cb_enum cbstatus = cb_buffer_add_item(CB_ptr, *data);
		if(cbstatus !=CB_SUCCESS)
		{
			break;
		}
		data++;
		len--;
	}
	return status;
}

