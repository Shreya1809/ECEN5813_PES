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

#include <stdio.h>

#ifdef KL25Z
  #include "MKL25Z4.h"
  // overwrote _write() to give KL25Z printf
  #define PRINTF(...) printf( __VA_ARGS__ )
  #define BEGIN_CRITICAL __disable_irq()
  #define END_CRITICAL __disable_irq()
#else
  #define PRINTF(...) printf( __VA_ARGS__ )
  #define BEGIN_CRITICAL
  #define END_CRITICAL
#endif

#endif
