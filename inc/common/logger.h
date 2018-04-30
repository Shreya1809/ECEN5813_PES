/*
 * logger.h
 *
 *  Created on: Apr 24, 2018
 *      Author: Shreya
 *      @brief: logger functions for both platforms
 */

#ifndef INC_COMMON_LOGGER_H_
#define INC_COMMON_LOGGER_H_

#include <stdio.h>
#include <stdint.h>
#include "circbuf.h"


#ifndef LOGGER_H_
#define LOGGER_H_

typedef enum
{
	ERROR,
	SUCCESS,
	NULL_POINTER,
	ALLOCATION_FAILED,
}log_status;

typedef enum
{
	SYSTEM_ID, // Send important information about your system
	SYSTEM_VERSION ,//- Send important information about your system firmware/hardware versions
	LOGGER_INITIALZED, //- No Payload
	GPIO_INITIALZED, //- No Payload
	SYSTEM_INITIALIZED,// - No Payload
	SYSTEM_HALTED,// - No Payload
	INFO ,//- Sends important information with regards to an info string
    WARNING,// - Sends important information with regards to an info string
	LOG_ERROR,// - Sends important information with regards to an info string
	PROFILING_STARTED,// - Profiling analysis has started
	PROFILING_RESULT,// - Logs a function identifier and a count for how long it took
	PROFILING_COMPLETED,// - Profiling analysis has completed
	DATA_RECEIVED,// - Logs that an item was received on the UART, transmits it back
	DATA_ANALYSIS_STARTED,// - No Payload
	DATA_ALPHA_COUNT,// - Logs number of alphabetic characters
	DATA_NUMERIC_COUNT,// - Logs number of alphabetic characters
	DATA_PUNCTUATION_COUNT,// - Logs number of alphabetic characters
	DATA_MISC_COUNT,// - Logs number of alphabetic characters
	DATA_ANALYSIS_COMPLETED,// - No Payload
	HEARTBEAT,// - No Payload
	CORE_DUMP,// - Send information with respect
}logger_enum_t;

typedef enum
{
	MAIN,
	PORT,
	PROFILER,
	DATA_PROCESSIING,
	LOGGER,
	UART,
	RTC_MOD,

}logger_module_t;

typedef struct
{
	logger_enum_t log_ID;
	logger_module_t Module_ID;
	uint32_t Timestamp;
	size_t log_Length;
	uint8_t * Payload;
	uint32_t Checksum;
}log_struct_t;

typedef struct
{
	logger_enum_t log_ID;
	logger_module_t Module_ID;
	uint32_t Timestamp;
	size_t log_Length;
	uint32_t  Payload;
	uint32_t Checksum;
}log_struct_t2;

extern log_struct_t  *logged_data;

/*function to fill the log struct elements*/
log_status log_create(log_struct_t * log_item , logger_enum_t ID, logger_module_t Module, size_t length, uint8_t * payload);

/*function to fill the log struct elements*/
log_status log_create1(log_struct_t2 * log_item , logger_enum_t ID, logger_module_t Module, size_t length, uint32_t  payload);

/*function to store data in buffer for kl25z*/
log_status log_data_KL25Z(cb_struct * CB_ptr, uint8_t * ptr, size_t length);

/*function to store the entire log data in buffer for kl25z*/
log_status log_item_KL25Z2(cb_struct * CB_ptr, log_struct_t2 *log_item);

/*function to store string in buffer for kl25z*/
log_status log_string_KL25Z(cb_struct * CB_ptr, uint8_t *data_ptr);

/*function to store data in buffer for host/bbb*/
log_status log_data_BBB(cb_struct * CB_ptr, uint8_t * ptr, size_t length);

/*function to store string in buffer for host/bbb*/
log_status log_string_BBB(cb_struct * CB_ptr, uint8_t *data_ptr);

/*function to store integer in buffer for kl25z*/
log_status log_integer_KL25Z(cb_struct * CB_ptr, int32_t data);

/*function to store integer in buffer for bbb*/
log_status log_integer_BBB(cb_struct * CB_ptr, int32_t data);

/*function to remove  from buffer and print kl25z*/
log_status log_flush_KL25Z(cb_struct * CB_ptr);

/*function to remove  from buffer and print bbb*/
log_status log_flush_BBB(cb_struct * CB_ptr);

/* simple functions to print on uart*/
log_status UART_integer_display(int32_t data);

log_status UART_string_display(uint8_t * ptr);

log_status UART_data_display(uint8_t * ptr, size_t length);

/*function to store the entire log data in the buffer for KL25Z*/
log_status log_item_KL25Z(cb_struct * CB_ptr, log_struct_t *log_item);

/*function to store the entire log data in the buffer for BBB*/
log_status log_item_BBB(cb_struct * CB_ptr, log_struct_t *log_item);

/*function to store the entire log data in the buffer for BBB*/
log_status log_item_BBB2(cb_struct * CB_ptr, log_struct_t2 *log_item);


#endif





#endif /* INC_COMMON_LOGGER_H_ */
