/**
 * @file logger_queue.h
 * @brief logger buffer library
 * @author Shreya Chakraborty
 * @author Miles Frain
 * @version 1
 * @date 2018-04-21
 */

#ifndef __LOGGER_QUEUE_H__
#define __LOGGER_QUEUE_H__


#include <stdint.h>
#include "logger.h"
#include "circbuf.h"

#ifdef VERBOSE

#ifdef PLATFORM_KL25Z


#include "uart.h"
#include "rtc.h"

#define LOG_RAW_DATA(data,len)			log_data_KL25Z(data,len)
#define LOG_RAW_STRING(string)			log_string_KL25Z(string)
#define LOG_RAW_INT(number)			log_integer_KL25Z(number)
#define LOG_FLUSH()				log_flush_KL25Z()
#define LOG_RAW_ITEM(structure,len)		log_cb_add(structure,len)
#else

#include <stdio.h>
struct timeval log_time;

#define LOG_RAW_DATA(data,len)			log_data_BBB(data,len)
#define LOG_RAW_STRING(string)			log_string_BBB(string)
#define LOG_RAW_INT(number)			log_integer_BBB(number)
#define LOG_FLUSH()				
#define LOG_RAW_ITEM(structure,len)		log_cb_add(structure,len)



#endif

#endif

typedef struct
{	
	log_struct * buffer; // base address
	log_struct * tail; // last value address
	log_struct * head; // buffer top value address
	size_t size; // total no of items possible
	size_t count; // current total no of items in the buffer
} CB_log_struct;

CB_log_struct *logger_queue;
logger_queue =malloc(sizeof(CB_log_struct)); 
 

log_struct log_create(log_enum log_ID,log_enum module_ID, size_t log_Length, uint32_t * payload); //function to fill the elements of log struct and store it
uint32_t getchecksum(log_enum log_ID,log_enum module_ID, uint32_t timestamp , size_t log_Length, uint32_t * payload);//to calculate checksum
void log_print(log_struct *ptr); //prints the value for kl25z/bbb with ptr pointing to the buffer containing the data to be logged

cb_enum log_cb_init(CB_log_struct* src_ptr, size_t length);
cb_enum log_cb_add(log_struct *logval_ptr , CB_log_struct* src_ptr);
cb_enum log_cb_remove(log_struct *logval_ptr , CB_log_struct* src_ptr);
cb_enum log_cb_is_full(CB_log_struct* src_ptr);//make this attribute (always inline)
cb_enum log_cb_is_empty(CB_log_struct* src_ptr);//make this attribute (always inline)


#endif 

#endif /logger_queue.h
