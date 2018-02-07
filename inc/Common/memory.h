/************************************************************
Authors:
 Miles Frain & Shreya Chakraborty
Description:
 header files for memory.c for the following memory functions
- my_memmove
- my_memset
- my_reverse
- my_memcmp
- string_size
- my_memzero
- my_memcpy
- reserve_words
- free_words
**************************************************************/
#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
uint8_t *my_memmove(uint8_t *src, uint8_t *dst, size_t length);

/*
@description:copies a length of bytes from source to destination,can handle overlaps
@parameters:source pointer,destination pointer,length of memory block
@return:pointer to destination
*/

uint8_t *my_memcmp(uint8_t *src, uint8_t *dst, size_t length);

/*
@description: compares source with destination for given size of length
@parameters: source pointer , destination pointer, length of memory block
@return:0 if there is a match
*/

uint8_t *my_memcpy(uint8_t *src, uint8_t *dst, size_t length);

/*
@description:copies a length of bytes from source to destination,undefined behavior in case of overlap
@parameters:source pointer,destination pointer,length of memory block
@return:pointer to destination
*/

uint8_t *my_memset(uint8_t *src, size_t length, uint8_t value);

/*
@description: sets all location of the memory block to the given value
@parameters:src byte to pointer,length of memory block, value to set
@return: byte pointer to source
*/

uint8_t *my_memzero(uint8_t *src, size_t length);

/*
@description: sets all location of memory block to 0
@parameters:src byte pointer and length
@return:byte pointer to src
*/

uint8_t *my_reverse(uint8_t *src, size_t length);

/*
@description: reverses the order of the string
@parameters:src byte pointer and length of memory block
@return: byte pointer to source if successful else turn 0
*/

uint32_t string_size(uint8_t *src);

/*
@description: gives the length of the entered string
@parameters: source string
@return: length of the strin
*/

int32_t *reserve_words(size_t length);

/*
@description:allocates a block of memory of given length
@parameters: length
@return: null for failure and byte pointer to allocation if success
*/

uint8_t free_words(uint32_t *src);

/*
@description: deallocates a block of memory
@parameters: src pointer to memory
@return: 0 if successful and 1 if not
*/

#endif//MEMORY_H
