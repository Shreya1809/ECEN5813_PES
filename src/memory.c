
/************************************************************
Authors:
 Miles Frain & Shreya Chakraborty
Description:
 source files for memory.c for the following memory functions
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



#include "memory.h"

/*copies a length of bytes from source to destination with no data corruption in case of overlap*/
uint8_t *my_memmove(uint8_t *src, uint8_t *dst, size_t length)
{
}



/*compares source with destination and returns 0 if its a match*/
uint8_t *my_memcmp(uint8_t *src, uint8_t *dst, size_t length)
{
}



/*copies a length of bytes from source to destination with likely data corruption in case of overlap*/ 
uint8_t *my_memcpy(uint8_t *src, uint8_t *dst, size_t length)
{
}



/*sets all location of memory to a given value*/
uint8_t *my_memset(uint8_t *src, size_t length, uint8_t value)
{
}



/*sets all the elements of the memory space to 0*/
uint8_t *my_memzero(uint8_t *src, size_t length)
{
}



/*reverses the order of all bytes*/
uint8_t *my_reverse(uint8_t *src, size_t length)
{
}



/*gives the size of string*/
uint32_t string_size(uint8_t *src)
{
}



/*takes a number of words to allocate in dynamic memory*/
int32_t *reserve_words(size_t length)
{
}



/*frees dynamic memory allocation*/
uint8_t free_words(uint8_t *src)
{
}

