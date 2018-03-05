/**
 * @file memory.c
 * @brief Custom memory functions
 *
 * - my_memmove
 * - my_memcpy
 * - my_memset
 * - my_memzero
 * - my_reverse
 * - reserve_words
 * - free_words
 *
 * @author Shreya Chakraborty
 * @author Miles Frain
 * @version 1.0
 * @date 2018-02-07
 */

#include <stdio.h>
#include <stdint.h>
#include <malloc.h>

#include "memory.h"

/*copies a length of bytes from source to destination with no data corruption in case of overlap*/
uint8_t *my_memmove(uint8_t *src, uint8_t *dst, size_t length)
{
    if((src != NULL) && (dst != NULL) && (length > 0))
    {
        if((src + length > dst) && (dst > src)) //overlap, source has lower memory
            //copy from opposite end
        {
            for(int32_t i = length -1; i >= 0; i--)
            {
                *(dst+i) = *(src+i);
            }
        }
        else if ((dst + length > src) && (src > dst)) //overlap, destination has lower memory than source

            //copy from front end
        {
            for(int32_t i = 0; i < length; i++)
            {
                *(dst+i) = *(src+i);
            }
        }
        else if ((src + length <= dst) && (dst > src)) // no overlap, destination has higher memory than source

            //copy from front end
        {
            for(int32_t i = 0; i < length; i++)
            {
                *(dst+i) = *(src+i);
            }
        }
        else if ((dst + length <= src) && (src > dst)) // no overlap, destination has lower memory than source

            //copy from front end
        {
            for(int32_t i = 0; i < length; i++)
            {
                *(dst+i) = *(src+i);
            }
        }
        return dst;
    }
    else
    {
	   return 0;
    }
}


/*copies a length of bytes from source to destination with likely data corruption in case of overlap*/
uint8_t *my_memcpy(uint8_t *src, uint8_t *dst, size_t length)
{
    if((src != NULL) && (dst != NULL) && (length > 0))
    {
	uint8_t * dst_copy = dst;
        while(length--)
        {
            *dst++ = *src++;
        }
        return dst_copy;
    }
    else return 0;
}


/*sets all location of memory to a given value*/
uint8_t *my_memset(uint8_t *src, size_t length, uint8_t value)
{

    if(src != NULL && (length >0))
    {
	uint8_t *src_copy = src;
        while(length!=0)
        {
            *src = value;
            src++;
            length--;
        }
        return src_copy;
    }
    else return 0;
}


/*sets all the elements of the memory space to 0*/
uint8_t *my_memzero(uint8_t *src, size_t length)
{
    if(src != NULL &&  (length > 0))
    {
	uint8_t *src_copy = src;
        while(length!=0) //while length is not zero, execute loop
        {
            *src = 0;
            src++;
            length--;
        }
        return src_copy;
    }
    else return 0;
}


/*reverses the order of all bytes*/
uint8_t *my_reverse(uint8_t *src, size_t length)
{
    if(src != NULL && (length > 0))
    {
        uint8_t a, temp, i = 0;

        if(length%2 == 0) //check is length is even
        {
            a = length/2;//for even string length
        }
        else
	   {
		  a = (length-1)/2;//for odd string length
	   }
        for(i=0;i<a;i++)
        {//swapping to reverse the order of bytes
            temp = *(src+i);
            *(src+i) = *(src+length-1-i);
            *(src+length-1-i) = temp;
        }
        return src;
    }

    else return 0;
}


/*takes a number of words to allocate in dynamic memory*/
uint32_t *reserve_words(size_t length)
{
    return (uint32_t*)malloc(sizeof(uint32_t)*length);
}


/*frees dynamic memory allocation*/
uint8_t free_words(uint32_t *src)
{
    if(src != NULL)
    {
        free(src);
        return 0;
    }
    else return 1;
}

/*gives the size of string*/
uint32_t string_size(uint8_t *src)
{
    uint32_t count = 0;
    while(*src !='\0') //checking the string and incrementing the count untill null is found
    {
        count++;
        src++;
    }
    return count;
}

