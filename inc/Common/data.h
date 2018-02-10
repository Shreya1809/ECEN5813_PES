/************************************************************
Authors:
 Miles Frain & Shreya Chakraborty
Description:
 header file for data.h for the following function
- print_cstd_type_sizes
- print_stdint_type_sizes
- print_pointer_sizes
- determine_endianness
- swap_data_endianness
**************************************************************/

#ifndef __DATA_H__
#define __DATA_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>


#define LITTLE_ENDIANN  (0)
#define BIG_ENDIANN     (1)
#define SWAP_NO_ERROR  (0)
#define SWAP_ERROR    (-1)


void print_cstd_type_sizes();
/*
@description:function to report sizes of the ctd data type 
@parameters: does not take any parameters 
@return:does not return any data
*/



void print_stdint_type_sizes();
/*
@description:function to report sizes of the stdint data type 
@parameters: does not take any parameters 
@return:does not return any data
*/



void print_pointer_sizes();
/*
@description:function to report sizes of the pointer data type 
@parameters: does not take any parameters 
@return:does not return any data
*/


uint32_t determine_endianness();
/*
@description:function to determine current endianness config for the program
@parameters: does not take any parameters
@return:returns the determine endianness macro
*/


int32_t  swap_data_endianness(uint8_t * data, size_t type_length);
/*
@description:function to swap current endianness from little to big or from big to little
@parameters: a pointer to the 1st byte of data ,length of the type to swap
@return:returns the macro for swap error or swap no error
*/

#endif /*data.h*/
