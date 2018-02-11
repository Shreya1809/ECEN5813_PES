/**
 * @file conversion.h
 * @brief  header files for conversion.h conversion functions
 * @author Miles Frain
 * @author Shreya Chakraborty
 * @version 1
 * @date 2018-02-10
 */

#ifndef CONVERSION_H
#define CONVERSION_H

#include <stdio.h>
#include <stdint.h>



/**
 * @brief :function to convert ascii string back to 32 bit integer and copy to the pointer address. 
 * @param ptr: pointer to location where the output will be copied
 * @param digits: input ascii string
 * @param base: base for conversion 
 * @return :length of data converted
 */
int32_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base);

/**
 * @brief :function to convert 32 bit integer data to ascii string and copy to the pointer address
 * @param data:32 bit integer to be converted,
 * @param ptr: pointer to the location where output will be copied
 * @param base: base for conversion 
 * @return :length of data converted
 */
uint8_t my_itoa(int32_t data, uint8_t *ptr, uint32_t base);


#endif /*CONVERSION_H*/
