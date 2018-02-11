/**
 * @file platform.h
 * @brief header files for platform.h to define various platforms like host,platform,bbb
 * @author Miles Frain
 * @author Shreya Chakraborty
 * @version 1
 * @date 2018-02-10
 */

#ifndef PLATFORM_H
#define PLATFORM_H


#ifdef KL25Z
  #define PRINTF(...)
#else
  #include <stdio.h>
  #define PRINTF(...) printf( __VA_ARGS__ )
#endif

#endif
