/************************************************************
Authors:
Miles Frain & Shreya Chakraborty
Description:
header files for platform.h to define various platforms like
- host
- kl25z
- BBB
 **************************************************************/

#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef KL25Z
  #define PRINTF(...)
#else
  #define PRINTF(...) printf( __VA_ARGS__ )
#endif

#endif
