


#ifndef __PROFILER_H__
#define __PROFILER_H__

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#ifdef KL25Z
extern const size_t byte_lengths[4];

#include "dma.h"
#include "memory_dma.h"
#include "MKL25Z4.h"

void systick();
void kl25z_profile_option( uint8_t number);
#else

#include <sys/time.h>
#include <time.h>


void bbb_profile_option( uint8_t number);


#endif
