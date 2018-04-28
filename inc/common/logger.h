/*
 * logger.h
 *
 *  Created on: Apr 24, 2018
 *      Author: Shreya
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

//log_status log_create(log_struct_t * log_item , logger_enum_t ID, size_t length, uint8_t * payload);
log_status log_create(log_struct_t * log_item , logger_enum_t ID, logger_module_t Module, size_t length, uint8_t * payload);

log_status log_create1(log_struct_t2 * log_item , logger_enum_t ID, logger_module_t Module, size_t length, uint32_t  payload);

log_status log_data_KL25Z(cb_struct * CB_data, uint8_t * ptr, size_t length);

log_status log_item_KL25Z2(cb_struct * CB_data, log_struct_t2 *log_item);

log_status log_string_KL25Z(cb_struct * CB_data, uint8_t *data_ptr);

log_status log_data_BBB(cb_struct * CB_data, uint8_t * ptr, size_t length);

log_status log_string_BBB(cb_struct * CB_data, uint8_t *data_ptr);

log_status log_integer_KL25Z(cb_struct * CB_data, int32_t data);

log_status log_integer_BBB(cb_struct * CB_data, int32_t data);

log_status log_flush_KL25Z(cb_struct * CB_data);

log_status log_flush_BBB(cb_struct * CB_data);

log_status UART_integer_display(int32_t data);

log_status UART_string_display(uint8_t * ptr);

log_status UART_data_display(uint8_t * ptr, size_t length);

log_status log_item_KL25Z(cb_struct * CB_data, log_struct_t *log_item);

log_status log_item_BBB(cb_struct * CB_data, log_struct_t *log_item);
//logger_status_t log_integer(cb_struct * CB_data, int32_t data);
//
///*
// *@brief - log flush
// *Blocks until the current logger buffer is empty
// *@param -
// *         CB_data: buffer to be flushed
// *@return  NULL_POINTER_PASSED: for null pointer
// *@return  success: if operation is successful
// */
//logger_status_t log_flush(cb_struct * CB_data);
//
///*
// *@brief - log data to UART
// *Takes a pointer to a sequence of bytes and length of bytes and adds it to the log buffer. This is used for HEARTBEAT
// *@param -
// *         data_ptr: Destination Pointer
// *         length: Length of the bytes
// *@return  NULL_POINTER_PASSED: for null pointer
// *@return  success: if logging is successful
// */
//logger_status_t log_data_to_UART(uint8_t *data_ptr, size_t length);
//
///*
// *@brief - log string to UART
// *Takes a C-string and adds it to the log buffer. This is used for HEARTBEAT
// *@param -
// *         data_ptr: Destination Pointer
// *@return  NULL_POINTER_PASSED: for null pointer
// *@return  success: if logging is successful
// */
//logger_status_t log_string_to_UART(uint8_t *data_ptr);
//
///*
// *@brief - log integer to UART
// *Takes an integer and adds it to the log buffer. This is used for HEARTBEAT
// *@param -
// *         data: integer data to be logged
// *         CB_data: Destination Pointer
// *@return  NULL_POINTER_PASSED: for null pointer
// *@return  success: if logging is successful
// */
//logger_status_t log_integer_to_UART(int32_t data);
//
///*
// *@brief - Create log item
// *Updates the logger struct.
// *@param -
// *         Item: logger buffer
// *         ID: Indicator on what the log is
// *         length: Number of bytes of Payload
// *         payload: Any associated data that is sent with the log
// *@return  NULL_POINTER_PASSED: for null pointer
// *@return  success: if the operation is successful
// */
//logger_status_t create_log(LoggedItem_t *Item , logger_status_t ID, size_t length, uint8_t *payload);
//
///*
// *@brief - log item
// *It updates the logger buffer
// *@param -
// *         CB_data: circular buffer
// *         Item: logger buffer
// *@return  NULL_POINTER_PASSED: for null pointer
// *@return  success: if the operation is successful
// */
//logger_status_t log_item(cb_struct * CB_data, LoggedItem_t *Item);
//
//void toggleHeartbeat();

#endif





#endif /* INC_COMMON_LOGGER_H_ */
