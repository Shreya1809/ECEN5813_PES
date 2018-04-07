#ifndef __PROFILER_H__
#define __PROFILER_H__

#include <stdint.h>
#define CLOCK_REALTIME     (0)
#ifdef KL25Z
//extern const size_t byte_lengths[4];

void systick();
void kl25z_profile_option( uint8_t number);
#else


void bbb_profile_option( uint8_t number);


#endif
#endif
