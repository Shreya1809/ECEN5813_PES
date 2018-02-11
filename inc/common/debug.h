/**
 * @file debug.h
 * @brief  header file for debug.h
 * @author Miles Frain
 * @author Shreya Chakraborty
 * @version 1
 * @date 2018-02-10
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>
#include <stdint.h>

/**
 * @brief : takes a pointer to memory and prints the hex output of bytes
 *
 * @param start: a pointer to the memory location
 * @param length: length of bytes to print
 */
void print_array(uint8_t *start, uint32_t length);

#endif /* __DEBUG_H__ */
