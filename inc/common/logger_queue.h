/*
 * logger_queue.h

 *
 *  Created on: Apr 27, 2018
 *      Author: Shreya
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

#else
#include "sys/time.h"
#include <stdio.h>
struct timeval log_time;

#define LOG_RAW_DATA(data,ptr,len)			log_data_BBB(data,ptr,len)
#define LOG_RAW_STRING(data,ptr)			log_string_BBB(data,ptr)
#define LOG_RAW_INT(ptr,number)				log_integer_BBB(ptr,number)
#define LOG_FLUSH(ptr)							log_flush_BBB(ptr)
#define LOG_RAW_ITEM(structure,ptr)			log_item_BBB(structure,ptr)


#endif




#endif /* INC_COMMON_LOGGER_QUEUE_H_ */
