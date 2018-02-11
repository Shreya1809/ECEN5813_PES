/**
 * @file debug.c
 * @brief source files for debug.c
 * @author Miles Frain
 * @author Shreya Chakraborty
 * @version 1
 * @date 2018-02-10
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdint.h>
#include "debug.h"
#include "platform.h"

void print_array(uint8_t* start, uint32_t length)
{
#ifdef VERBOSE
    int i = 0;
    if(start != NULL)
    {
        while(length != 0)
        {
            PRINTF("Address: %p and Data: %d\n ", (start+i),*(start+i)) ;
            i++; length--;
        }
    }
#endif
}
#endif // __DEBUG_H__
