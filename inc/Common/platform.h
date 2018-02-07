/************************************************************
Authors:
Miles Frain & Shreya Chakraborty
Description:
header files for conversion.h for the following conversion function functions
- my_itoa
- my_atoi
 **************************************************************/

#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef KL25Z
  #define PRINTF(...)
#else
  #define PRINTF(...) printf( __VA_ARGS__ )
#endif

#endif
