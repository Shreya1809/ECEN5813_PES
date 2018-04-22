/**
 * @file logger.h
 * @brief logger buffer library
 * @author Shreya Chakraborty
 * @author Miles Frain
 * @version 1
 * @date 2018-04-21
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "malloc.h"
#include "conversion.h"
//#include "logger_queue.h"


/*
* @brief enum for maintaining handle to logger.
*/

typedef enum   {
 LOG_SYSTEM_ID,
 LOG_SYSTEM_VERSION,
 LOG_LOGGER_INITIALZED,
 LOG_GPIO_INITIALZED,
 LOG_SYSTEM_INITIALIZED,
 LOG_SYSTEM_HALTED,
 LOG_INFO,
 LOG_WARNING,
 LOG_ERROR,
 LOG_PROFILING_STARTED,
 LOG_PROFILING_RESULT,
 LOG_PROFILING_COMPLETED,
 LOG_DATA_RECEIVED,
 LOG_DATA_ANALYSIS_STARTED,
 LOG_DATA_ALPHA_COUNT,
 LOG_DATA_NUMERIC_COUNT,
 LOG_DATA_PUNCTUATION_COUNT,
 LOG_DATA_MISC_COUNT,
 LOG_DATA_ANALYSIS_COMPLETED,
 LOG_HEARTBEAT,
 LOG_CORE_DUMP,
}log_enum;


extern char logID_show[21][25];
/*
* @brief structure for maintaining handle to logger.
*/
typedef struct {
 log_enum log_ID; //Indicator on what the log is
 log_enum module_ID;//Indicator of where the log is coming from (File/module)
 uint32_t timestamp;//32-bit RTC value
 size_t log_Length; // Number of bytes of Payload
 uint32_t *payload; //Any associated data that is sent with the log (can vary in size). Dependent on the log ID
 uint32_t checksum;//Any type of checksum you want to implement that allows the log data to be verified
} log_struct;

//log_struct logStructFill;
//extern log_struct *logStructFill; //= malloc(sizeof(log_struct));// to pass log info into the struct

uint32_t getlogtime();

#ifdef KL25Z

#include "uart.h"
#include "rtc.h"

//logger functions for KL25Z
void log_data_KL25Z(uint32_t *ptr,size_t length);//Takes a pointer to sequence of bytes and length of bytes to log
void log_string_KL25Z(char *ptr);//Takes a c-string and logs that to the terminal
void log_integer_KL25Z(uint32_t a);// Takes an integer and logs that to the terminal (use itoa)
void log_flush_KL25Z();//Blocks until the current logger buffer is empty


#else
#include "sys/time.h"
#include "time.h"

//logger functions for BBB/HOST
void log_data_BBB(uint32_t *ptr,size_t length);//Takes a pointer to sequence of bytes and length of bytes to log
void log_string_BBB(char *ptr);//Takes a c-string and logs that to the terminal
void log_integer_BBB(uint32_t a);// Takes an integer and logs that to the terminal (use itoa)

#endif




#endif //LOGGER.H
