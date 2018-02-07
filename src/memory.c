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
    if(*src != '\0' && *dst != '\0'&& length > 0)
    {
        if((src+length)>dst && (dst > src)) //overlap, source has lower memory
            //copy from opposite end
        {
            for(uint32_t i = length -1; i > 0; i--)
            {
                *(dst+i) = *(src+i);
            }
        }
        else if ((dst+length)>src && (src > dst)) //overlap, destination has lower 		memory than source

            //copy from front end
        {
            for(uint32_t i = 0; i < length; i++)
            {
                *(dst+i) = *(src+i);
            }
        }
        else if ((src+length)<dst && (dst > src)) // no overlap, destination has higher memory 	than source

            //copy from front end
        {
            for(uint32_t i = 0; i < length; i++)
            {
                *(dst+i) = *(src+i);
            }
        }
        else if ((dst+length)<src && (src > dst)) // no overlap, destination has lower memory than source

            //copy from front end
        {
            for(uint32_t i = 0; i < length; i++)
            {
                *(dst+i) = *(src+i);
            }
        }
        return dst;
    }
    else return 0;
}


/*copies a length of bytes from source to destination with likely data corruption in case of overlap*/
uint8_t *my_memcpy(uint8_t *src, uint8_t *dst, size_t length)
{
    if(*src != '\0' && *dst != '\0'&& (length > 0))
    {
        while(length--)
        {
            *src = *dst;
            if(*src != *dst); //verify data copy
            return NULL;
            src++; dst++;
        }
        return dst;
    }
    else return 0;
}


/*sets all location of memory to a given value*/
uint8_t *my_memset(uint8_t *src, size_t length, uint8_t value)
{

    if(*src != '\0'&& (length >0))
    {
        while(length!=0)
        {
            *src = value;
            src++;
            length--;
        }
        return src;
    }
    else return 0;
}


/*sets all the elements of the memory space to 0*/
uint8_t *my_memzero(uint8_t *src, size_t length)
{
    if(*src != '\0' &&  (length > 0))
    {
        while(length!=0) //while length is not zero, execute loop
        {
            *src = 0;
            src++;
            length--;
        }
        return src;
    }
    else return 0;
}


/*reverses the order of all bytes*/
uint8_t *my_reverse(uint8_t *src, size_t length)
{
    if(*src != '\0' && ( length > 0) && length==string_size(src))
    {
        uint8_t a,temp, i = 0;

        if(length%2 == 0) //check is length is even
        {
            a = length/2;//for even string length
        }
        else a = (length-1)/2;//for odd string length
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
int32_t *reserve_words(size_t length)
{
    int *p;
    p= (int*)malloc(sizeof(uint32_t)*length);
    if (*p == '\0')
        return NULL;
    else return p;
}


/*frees dynamic memory allocation*/
uint8_t free_words(uint32_t *src)
{
    if(*src != '\0')
    {
        free(src);
        return 0;
    }
    else return 1;
}

