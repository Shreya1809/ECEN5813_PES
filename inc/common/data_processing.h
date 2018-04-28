/**
 * @file data_processing.h
 * @brief Shows character statistics
 * @author Miles Frain
 * @author Shreya Chakraborty
 * @version 1
 * @date 2018-03-04
 */

#ifndef __DATA_PROCESSING_H__
#define __DATA_PROCESSING_H__


extern int8_t beat;
void print_data_process_header(void);

void data_process();

void data_statistics(uint8_t character);

void print_data_entered();

void print_all_log();

//void print_all_log_BBB();

void heartbeat();
#endif // __DATA_PROCESSING_H__
