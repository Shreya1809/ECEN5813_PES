/************************************************************
Authors:
 Miles Frain & Shreya Chakraborty
Description:
 header files for conversion.h for the following conversion function functions
- my_itoa
- my_atoi
**************************************************************/
#ifndef CONVERSION_H
#define CONVERSION_H

#include <stdio.h>
#include <stdint.h>



int32_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base);

/*
@description:function to convert ascii string back to 32 bit integer and copy to the pointer address. 
@parameters: input ascii string, base for conversion and pointer to location where the output will be copied
@return:length of data converted
*/


int32_t my_itoa(int32_t data, uint8_t *ptr, uint32_t base);

/*
@description:function to convert 32 bit integer data to ascii string and copy to the pointer address
@parameters:32 bit integer to be converted, base for conversion  and pointer to the location where output will be copied
@return:length of data converted
*/

#endif /*CONVERSION_H*/
