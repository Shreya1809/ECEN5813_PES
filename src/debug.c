/************************************************************
Authors:
Miles Frain & Shreya Chakraborty
Description:
source files for debug.c for the following conversion function
- print_array
 **************************************************************/
#include "debug.h"
#ifdef VERBOSE

void print_array(uint8_t* start, uint32_t length)
{
    int i = 0;
    if(start != NULL)
    {
        while(length != 0)
        {
            printf("Address: %p and Data: %d\n ", (start+i),*(start+i)) ;
            i++; length--;
        }
    }
}
#endif /*end of debug.h*/
