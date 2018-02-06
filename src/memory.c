
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
unit8_t *my_memmove(unit8_t *src, unit_t *dst, size_t length)
{
    if(*src != '\0' && *dst != '\0'&& 0 < length < 21474836470)
    {
        if((src+length)>dst && (dst > src)) //overlap, source has lower memory
            //copy from opposite end
        {
            for(uint_32 i = length -1; i > 0; i--)
            {
                *(dst+i) = *(src+i);
            }
        }
        else if ((dst+length)>src && (src > dst)) //overlap, destination has lower 		memory than source

            //copy from front end
        {
            for(uint_32 i = 0; i < length; i++)
            {
                *(dst+i) = *(src+i);
            }
        }
        else if ((src+length)<dst && (dst > src)) // no overlap, destination has higher memory 	than source

            //copy from front end
        {
            for(uint_32 i = 0; i < length; i++)
            {
                *(dst+i) = *(src+i);
            }
        }
        else if ((dst+length)<src && (src > dst)) // no overlap, destination has lower memory than source

            //copy from front end
        {
            for(uint_32 i = 0; i < length; i++)
            {
                *(dst+i) = *(src+i);
            }
        }
        return dst;
    }
    else return 0;
}


/*compares source with destination and returns 0 if its a match*/
unit8_t *my_memcmp(unit8_t *src, unit_t *dst, size_t length)
{
    if(*src != '\0' && *dst != '\0'&& 0 < length < 2147483647)
    {
        for(uint32_t i = 0; i < length; i++,src++,dst++)
        {
            if(*src < *dst)
                return 1;
            if(*src > *dst)
                return 1;
        }
    }
    else return 0; // return 0 for match
}


/*copies a length of bytes from source to destination with likely data corruption in case of overlap*/
unit8_t *my_memcpy(unit8_t *src, unit_t *dst, size_t length)
{
    if(*src != '\0' && *dst != '\0'&& 0 < length < 2147483647)
    {
        while(length--)
        {
            *src = *dest
                if(*src ! = *dest) //verify data copy
                    return -1;
            src++; dest++;
        }
        return dst;
    }
    else return 0;
}


/*sets all location of memory to a given value*/
unit8_t *my_memset(unit8_t *src, size_t length, unit8_t value)
{

    if(*src != '\0'&& 0 < length < 2147483647)
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
unit8_t *my_memzero(unit8_t *src, size_t length)
{
    if(*src != '\0' && 0 < length < 2147483647)
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
unit8_t *my_reverse(unit8_t *src, size_t length)
{
    if(*src != '\0' && 0 < length < 2147483647 && length==string_size(src))
    {
        unit8_t a,temp, i = 0;

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


/*gives the size of string*/
unit32_t string_size(unit8_t *src)
{
    unit32_t count = 0;
    while(*src !='\0') //checking the string and incrementing the count untill null is found
    {
        count++;
        src++;
    }
    return count;
}


/*takes a number of words to allocate in dynamic memory*/
int32_t *reserve_words(size_t length)
{
    int *p;
    p= (int*)malloc(sizeof(unit32_t)*length);
    if (p == '\0')
        return NULL;
    else p;
}


/*frees dynamic memory allocation*/
unit8_t free_words(unit8_t *src)
{
    free(src);
    //how to check if free worked?

}

