/*
 * logger_queue.h

 *
 *  Created on: Apr 27, 2018
 *      Author: Shreya
 *      @brief: wrapper function to make codes portable on all platform
 */

#include "logger.h"

#ifndef INC_COMMON_LOGGER_QUEUE_H_
#define INC_COMMON_LOGGER_QUEUE_H_

#ifdef KL25Z


#include "uart.h"
#include "rtc.h"


#define LOG_RAW_DATA(data,ptr,len)			log_data_KL25Z(data,ptr,len)
#define LOG_RAW_STRING(data,ptr)			log_string_KL25Z(data,ptr)
#define LOG_RAW_INT(ptr,number)				log_integer_KL25Z(ptr,number)
#define LOG_FLUSH(ptr)							log_flush_KL25Z(ptr)
#define LOG_RAW_ITEM(structure,ptr)			log_item_KL25Z(structure,ptr)
#define LOG_BINARY(cb_ptr,ptr)				log_binary_KL25Z(cb_ptr,ptr)

#else
#include "sys/time.h"
#include <stdio.h>
struct timeval log_time;

#define LOG_RAW_DATA(data,ptr,len)			log_data_BBB(data,ptr,len)
#define LOG_RAW_STRING(data,ptr)			log_string_BBB(data,ptr)
#define LOG_RAW_INT(ptr,number)				log_integer_BBB(ptr,number)
#define LOG_FLUSH(ptr)						log_flush_BBB(ptr)
#define LOG_RAW_ITEM(structure,ptr)			log_item_BBB(structure,ptr)
#define LOG_BINARY(cb_ptr,ptr)				log_binary_BBB(cb_ptr,ptr)

#endif




#endif /* INC_COMMON_LOGGER_QUEUE_H_ */
