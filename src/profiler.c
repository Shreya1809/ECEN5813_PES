
#include "profiler.h"

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include "memory.h"

const size_t byte_length[4]={10,100,1000,5000};
const size_t size[3] = {1,2,4};
//size_t start, end, diff;
#ifdef KL25Z

#include "dma.h"
#include "memory_dma.h"
#include "MKL25Z4.h"


void systick()
{
SysTick-> LOAD |= SysTick_LOAD_RELOAD_Msk; //load value is 0X00FFFFFF which is the maximum
SysTick-> CTRL |= (SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk); //counter enabled, processor clock
SysTick -> VAL = 0;
//begin = SysTick->VAL;
}



void kl25z_profile_option( uint8_t number)
{
	uint8_t *source, *dest;
	uint8_t x[10000];
	for(int k = 0; k <5000; k++)
	{
		x[k]= 1;
	}
	for(int k = 5000; k <10000; k++)
	{
		x[k]= 2;
	}

	source = &x[0];
	dest =&x[4999];

	if(number == 1)
	{

		for (int j = 0;j<4 ; j++)
		{
			for (int m = 0; m<3; m++)
			{
			start = SysTick -> VAL;
			memmove_dma(source,dest, byte_length[j], size[m]);
			end = SysTick -> VAL;
			diff = start - end;
			// print report on sizes
			UART_send(diff);
			}
		}
	}
	if(number == 2)
	{

		for (int j = 0;j<4 ; j++)
		{
			for (int m = 0; m<3; m++)
			{
			start = SysTick -> VAL;
			memset_dma(dest, byte_length[j],5, size[m]);
			end = SysTick -> VAL;
			diff = start - end;
			// print report on sizes
			UART_send(diff);
			}
		}
	}

	if(number == 3)
	{

		for (int j = 0;j<4 ; j++)
		{

			start = SysTick -> VAL;
			my_memmove(source, dest, byte_length[j]);
			end = SysTick -> VAL;
			diff = start - end;
			// print report on sizes
			UART_send(diff);

		}
	}
	if(number == 4)
	{

		for (int j = 0;j<4 ; j++)
		{

			start = SysTick -> VAL;
			my_memset(dest, byte_length[j], 10);
			end = SysTick -> VAL;
			diff = start - end;
			// print report on sizes
			UART_send(diff);

		}
	}
	if(number == 5)
	{

		//get statistics for all kl25z execution times
	}
#else

void bbb_profile_option( uint8_t number)
{
	uint8_t *source, *dest;
	uint8_t x[10000];
	for(int k = 0; k <5000; k++)
	{
		x[k]= 1;
	}
	for(int k = 5000; k <10000; k++)
	{
		x[k]= 2;
	}

	source = &x[0];
	dest =&x[4999];
	//int i = 0;
	int ret_stat = 0;
	struct timespec start_time, end_time;
	double diff;
	if(number == 1)
	{
		for (int j = 0;j<4 ; j++)
			{
			ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
			memmove(source,dest,byte_length[j]);
			ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
			diff = (( end_time.tv_sec - start_time.tv_sec ) + ( end_time.tv_nsec - start_time.tv_nsec ));
			printf("Time taken for std memmove for %d byte transfer is %lf\n",byte_length[j], diff);
			}
	}
	if(number == 2)
	{
		for (int j = 0;j<4 ; j++)
			{
			ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
			memset(source,10, byte_length[j]);
			ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
			diff = (( end_time.tv_sec - start_time.tv_sec ) + ( end_time.tv_nsec - start_time.tv_nsec ));
			printf("Time taken for std memset for %d byte transfer is %lf\n",byte_length[j], diff);
			}
	}
	if(number == 3)
	{
		for (int j = 0;j<4 ; j++)
			{
			ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
			my_memset(source, byte_length[j], 10);
			ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
			diff = (( end_time.tv_sec - start_time.tv_sec ) + ( end_time.tv_nsec - start_time.tv_nsec ));
			printf("Time taken for  my_memset for %d byte transfer is %lf\n",byte_length[j], diff);
			}
	}
	if(number == 4)
	{
		for (int j = 0;j<4 ; j++)
			{
			ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
			my_memmove(source,dest, byte_length[j]);
			ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
			diff = (( end_time.tv_sec - start_time.tv_sec ) + ( end_time.tv_nsec - start_time.tv_nsec ));
			printf("Time taken for  my_memmove for %d byte transfer is %lf\n",byte_length[j], diff);
			}
	}
	if(number == 5)
	{
	// show statistics of all bbb execution times
	}
	if(ret_stat); // Not used
}
#endif
