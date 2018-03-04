/**
 * @file data.h
 * @brief  header file for data.h
 * @author Miles Frain
 * @author Shreya Chakraborty
 * @version 1
 * @date 2018-02-10
 */

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


/**
 * @brief :function to report sizes of the ctd data type 
 */
void print_cstd_type_sizes();

/**
 * @brief :function to report sizes of the stdint data type 
 */
void print_stdint_type_sizes();

/**
 * @brief :function to report sizes of the pointer data type 
 */
void print_pointer_sizes();

/**
 * @brief function to determine current endianness config for the program
 *
 * @return returns the determine endianness macro
 */
uint32_t determine_endianness();

/**
 * @brief function to swap current endianness from little to big or from big to little
 *
 * @param data a pointer to the 1st byte of data ,
 * @param type_length length of the type to swap
 *
 * @return the macro for swap error or swap no error
 */
int32_t  swap_data_endianness(uint8_t * data, size_t type_length);

/*function to change from little to big*/
int8_t little_to_big(uint32_t * data);

/*function to change from big to little*/
int8_t big_to_little(uint32_t * data);

#endif /*data.h*/
