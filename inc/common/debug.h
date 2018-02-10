/************************************************************
Authors:
 Miles Frain & Shreya Chakraborty
Description:
 header file for debug.h for the following function
- print_array
**************************************************************/
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>
#include <stdint.h>

void print_array(uint8_t *start, uint32_t length);

/*
@description: takes a pointer to memory and prints the hex output of bytes
@parameters: a pointer to the memory location and length of bytes to print
*/

#endif /* __DEBUG_H__ */
