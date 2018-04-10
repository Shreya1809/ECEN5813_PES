
#include "profiler.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include "memory.h"

const size_t byte_length[4] = {10, 100, 1000, 5000};
uint32_t start, end, diff;
#ifdef KL25Z

#include "dma.h"
#include "memory_dma.h"
#include "MKL25Z4.h"
#include "MKL25Z4_extension.h"
#include "uart.h"
#include "platform.h"
const dma_block_size size[3] = {ONE_BYTE, TWO_BYTE, FOUR_BYTE};

#define DMA_CHECK_ERROR (DMA_DSR_BCR0 & (DMA_DSR_BCR_CE_MASK | DMA_DSR_BCR_BES_MASK | DMA_DSR_BCR_BED_MASK))

void systick_init()
{
    SysTick->LOAD |= SysTick_LOAD_RELOAD_Msk;                                //load value is 0X00FFFFFF which is the maximum
    SysTick->CTRL |= (SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk); //counter enabled, processor clock
    SysTick->VAL = 0;
    //begin = SysTick->VAL;
}

void kl25z_profile_option(profile_test test_type)
{
    uint8_t *source, *dest;
    uint8_t x[10000];
    for (int k = 0; k < 5000; k++)
    {
        x[k] = 1;
    }
    for (int k = 5000; k < 10000; k++)
    {
        x[k] = 2;
    }

    source = &x[0];
    dest = &x[5000];



   // uint8_t *src = &x[0];
   // uint8_t *dst = &x[1000];
   // size_t length = 3;

    #if 0
    for (int j = 1; j < 7; j++)
    {
        length = 16 * j;

        // Setup transfer before and after
        for (int i = 0; i < length; i++)
        {
            src[i] = i * j;
            dst[i] = 0;
        }

        start = SysTick->VAL;
        // For reference, this works fine, not sure why later version does not work.
        memmove_dma(src, dst, length, FOUR_BYTE);
        end = SysTick->VAL;
        diff = start - end;
        while (DMA_DSR_BCR0 & DMA_DSR_BCR_BCR_MASK) ;
        uint32_t diff2 = start - SysTick->VAL;
        // print report on sizes
        PRINTF("Time taken for std memmove for transfer is %lu %lu\n", diff, diff2);

        PRINTF("Transfer complete %d\n", dst[1]);
        // Verify transfer successful
        for (int i = 0; i < length; i++)
        {
            if (dst[i] != src[i])
            {
                PRINTF("Bad transfer\n");
                break;
            }
            //PRINTF("dst[%d] = %d\n", i, dst[i]);
        }
    }

    return;
    #endif

    if (test_type == MEMMOVE_DMA)
    {
        PRINTF("trying memmove_dma\n");

                //#if 0
                start = SysTick->VAL;
                mem_enum ret = memmove_dma(source, dest, 10 , ONE_BYTE );
                while(DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                if(ret != NO_ERROR || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
                diff = start - end;
                PRINTF("Time taken for  memmove dma for 10 byte transfer with 1 byte block size is %lu us\n ", diff/21);

                start = SysTick->VAL;
				ret = memmove_dma(source, dest, 100 , ONE_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                if(ret != NO_ERROR || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);

				diff = start - end;
				PRINTF("Time taken for  memmove dma for 100 byte transfer with 1 byte block size is %lu us\n ", diff/21);

				start = SysTick->VAL;
				ret = memmove_dma(source, dest, 1000 , ONE_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                if(ret != NO_ERROR || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);

				diff = start - end;
				PRINTF("Time taken for  memmove dma for 1000 byte transfer with 1 byte block size is %lu us\n ", diff/21);

				start = SysTick->VAL;
				ret = memmove_dma(source, dest, 5000 , ONE_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                if(ret != NO_ERROR || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);

				diff = start - end;
				PRINTF("Time taken for  memmove dma for 5000 byte transfer with 1 byte block size is %lu us\n ", diff/21);

				start = SysTick->VAL;
				ret = memmove_dma(source, dest, 10, TWO_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                if(ret != NO_ERROR || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);

				diff = start - end;
				PRINTF("Time taken for  memmove dma for 10 byte transfer with 2 bytes block size is %lu us\n ", diff/21);

				start = SysTick->VAL;
				ret = memmove_dma(source, dest, 100, TWO_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                if(ret != NO_ERROR  || DMA_CHECK_ERROR )	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);

				diff = start - end;
				PRINTF("Time taken for  memmove dma for 100 byte transfer with 2 bytes block size is %lu us\n ", diff/21);

				start = SysTick->VAL;
				ret = memmove_dma(source, dest, 1000, TWO_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);

				diff = start - end;
				PRINTF("Time taken for  memmove dma for 1000 byte transfer with 2 bytes block size is %lu us\n ", diff/21);

				start = SysTick->VAL;
				ret = memmove_dma(source, dest,5000, TWO_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);

				diff = start - end;
				PRINTF("Time taken for  memmove dma for 5000 byte transfer with 2 bytes block size is %lu us\n ", diff/21);


                start = SysTick->VAL;
				ret = memmove_dma(source, dest,8, FOUR_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);

				diff = start - end;
				PRINTF("Time taken for  memmove dma for 10 byte transfer with 4 bytes block size is %lu us\n ", diff/21);

				start = SysTick->VAL;
				ret = memmove_dma(source, dest,100, FOUR_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);

				diff = start - end;
				PRINTF("Time taken for  memmove dma for 100 byte transfer with 4 bytes block size is %lu us\n ", diff/21);

				start = SysTick->VAL;
				ret = memmove_dma(source, dest,1000, FOUR_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
				//end = SysTick->VAL;
				diff = start - end;
				PRINTF("Time taken for  memmove dma for 1000 byte transfer with 4 bytes block size is %lu us\n ", diff/21);

				start = SysTick->VAL;
				ret = memmove_dma(source, dest,5000, FOUR_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
				end = SysTick->VAL;
				diff = start - end;
				PRINTF("Time taken for  memmove dma for 5000 byte transfer with 4 bytes block size is %lu us\n ", diff/21);

    }
    if (test_type == MEMSET_DMA)
    {

                start = SysTick->VAL;
                mem_enum ret = memset_dma(dest, 10, 5,ONE_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
			    if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
			    DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
                end = SysTick->VAL;
                diff = start - end;
                // print report on sizes
                PRINTF("Time taken for  memset dma for 10 byte transfer with 1 byte block size is %lu us\n ", diff/21);

               start = SysTick->VAL;
			   ret = memset_dma(dest, 100, 5,ONE_BYTE );
			   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
			   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
			   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
			   end = SysTick->VAL;
			   diff = start - end;
			   // print report on sizes
			   PRINTF("Time taken for  memset dma for 100 byte transfer with 1 byte block size is %lu us\n ", diff/21);

			   start = SysTick->VAL;
			   ret = memset_dma(dest, 1000, 5,ONE_BYTE );
			   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
			   end = SysTick->VAL;
			   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
			   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
			   //end = SysTick->VAL;
			   diff = start - end;
			   // print report on sizes
			   PRINTF("Time taken for  memset dma for 1000 byte transfer with 1 byte block size is %lu us\n ", diff/21);

			   start = SysTick->VAL;
			   ret = memset_dma(dest, 5000, 5,ONE_BYTE );
			   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
			   end = SysTick->VAL;
			   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
			   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
			   //end = SysTick->VAL;
			   diff = start - end;
			   // print report on sizes
			   PRINTF("Time taken for  memset dma for 5000 byte transfer with 1 byte block size is %lu us\n ", diff/21);

			   start = SysTick->VAL;
			   ret = memset_dma(dest, 10, 5,TWO_BYTE );
			   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
			   end = SysTick->VAL;
			if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
			DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
			   //end = SysTick->VAL;
			   diff = start - end;
			   // print report on sizes
			   PRINTF("Time taken for  memset dma for 10 byte transfer with 2 bytes block size is %lu us\n ", diff/21);

			  start = SysTick->VAL;
		   ret = memset_dma(dest, 100, 5,TWO_BYTE );
		   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
		   end = SysTick->VAL;
		   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
		   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
		   //end = SysTick->VAL;
		   diff = start - end;
		   // print report on sizes
		   PRINTF("Time taken for  memset dma for 100 byte transfer with 2 bytes block size is %lu us\n ", diff/21);

		   start = SysTick->VAL;
		   ret = memset_dma(dest, 1000, 5,TWO_BYTE );
		   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
		   end = SysTick->VAL;
		   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
		   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
		  // end = SysTick->VAL;
		   diff = start - end;
		   // print report on sizes
		   PRINTF("Time taken for  memset dma for 1000 byte transfer with 2 bytes block size is %lu us\n ", diff/21);

		   start = SysTick->VAL;
		   ret = memset_dma(dest, 5000, 5,TWO_BYTE );
		   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
		   end = SysTick->VAL;
		   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
		   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
		   //end = SysTick->VAL;
		   diff = start - end;
		   // print report on sizes
		   PRINTF("Time taken for  memset dma for 5000 byte transfer with 2 bytes block size is %lu us\n ", diff/21);

		   start = SysTick->VAL;
		   ret = memset_dma(dest, 8, 5,FOUR_BYTE );
		   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
		   end = SysTick->VAL;
		   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
		   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
		   //end = SysTick->VAL;
		   diff = start - end;
		   // print report on sizes
		   PRINTF("Time taken for  memset dma for 10 byte transfer with 4 bytes block size is %lu us\n ", diff/21);

		   start = SysTick->VAL;
		   ret = memset_dma(dest, 100, 5,FOUR_BYTE );
		   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
		   end = SysTick->VAL;
		   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
		   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
		   //end = SysTick->VAL;
		   diff = start - end;
		   // print report on sizes
		   PRINTF("Time taken for  memset dma for 100 byte transfer with 4 bytes block size is %lu us\n ", diff/21);

		   start = SysTick->VAL;
		   ret = memset_dma(dest, 1000, 5,FOUR_BYTE );
		   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
		   end = SysTick->VAL;
		   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
		   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
		  // end = SysTick->VAL;
		   diff = start - end;
		   // print report on sizes
		   PRINTF("Time taken for  memset dma for 1000 byte transfer with 4 bytes block size is %lu us\n ", diff/21);

		   start = SysTick->VAL;
		   ret = memset_dma(dest, 5000, 5,FOUR_BYTE );
		   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
		   end = SysTick->VAL;
		   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
		   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
		   //end = SysTick->VAL;
		   diff = start - end;
		   // print report on sizes
		   PRINTF("Time taken for  memset dma for 5000 byte transfer with 4 bytes block size is %lu us\n ", diff/21);

    }

    if (test_type == MY_MEMMOVE)
    {
        for (int j = 0; j < 4; j++)
        {
            start = SysTick->VAL;
            my_memmove(source, dest, byte_length[j]);
            end = SysTick->VAL;
            diff = start - end;
            // print report on sizes
            PRINTF("Time taken for my memmove for %d byte transfer is %lu us\n", byte_length[j], diff/21);

         }
    }
    if (test_type == MY_MEMSET)
    {

        for (int j = 0; j < 4; j++)
        {

            start = SysTick->VAL;
            my_memset(dest, byte_length[j], 10);
            end = SysTick->VAL;
            diff = start - end;
            // print report on sizes
            PRINTF("Time taken for my memset for %d byte transfer is %lu us\n", byte_length[j], diff/21);
        }
    }
    if (test_type == MEMMOVE)
    {
    	for (int j = 0; j < 4; j++)
		{

			start = SysTick->VAL;
			memmove(dest, source, byte_length[j]);
			end = SysTick->VAL;
			diff = start - end;
			// print report on sizes
			PRINTF("Time taken for std memmove for %d byte transfer is %lu us\n", byte_length[j], diff/21);
		}
    }
    if (test_type == MEMSET)
    {
    	for (int j = 0; j < 4; j++)
		{

			start = SysTick->VAL;
			memset(dest, 10, byte_length[j]);
			end = SysTick->VAL;
			diff = start - end;
			// print report on sizes
			PRINTF("Time taken for std memset for %d byte transfer is %lu us\n", byte_length[j], diff/21);
		}
    }
}
#else

void bbb_profile_option(uint8_t number)
{
    uint8_t *source, *dest;
    uint8_t x[10000];
    for (int k = 0; k < 5000; k++)
    {
        x[k] = 1;
    }
    for (int k = 5000; k < 10000; k++)
    {
        x[k] = 2;
    }

    source = &x[0];
    dest = &x[4999];
    //int i = 0;
    int ret_stat = 0;
    struct timespec start_time, end_time;
    double diff;
    if (number == 1)
    {

        	ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
			memmove(source, dest, 5000 );
			ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
			diff = ((end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec));
			printf("Time taken for std memmove for 5000 byte transfer is %lf\n", diff);

		ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
			memmove(source, dest, 1000 );
			ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
			diff = ((end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec));
			printf("Time taken for std memmove for 1000 byte transfer is %lf\n", diff);

		ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
			memmove(source, dest, 100 );
			ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
			diff = ((end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec));
			printf("Time taken for std memmove for 100 byte transfer is %lf\n", diff);

		ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
			memmove(source, dest, 10);
			ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
			diff = ((end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec));
			printf("Time taken for std memmove for 10 byte transfer is %lf\n", diff);



    }
    if (number == 2)
    {
    	ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
		memset(source, 10, 5000);
		ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
		diff = ((end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec));
		printf("Time taken for std memset for 5000 byte transfer is %lf\n", diff);

	ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
		memset(source, 10, 1000);
		ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
		diff = ((end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec));
		printf("Time taken for std memset for 1000 byte transfer is %lf\n", diff);

	ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
		memset(source, 10, 100);
		ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
		diff = ((end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec));
		printf("Time taken for std memset for 100 byte transfer is %lf\n", diff);

	ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
		memset(source, 10, 10);
		ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
		diff = ((end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec));
		printf("Time taken for std memset for 10 byte transfer is %lf\n", diff);
    }
    if (number == 3)
    {
        for (int j = 3; j >= 0; j--)
        {
            ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
            my_memset(source, byte_length[j], 10);
            ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
            diff = ((end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec));
            printf("Time taken for  my_memset for %d byte transfer is %lf\n", byte_length[j], diff);
        }
    }
    if (number == 4)
    {
        for (int j = 3; j >= 0; j--)
        {
            ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
            my_memmove(source, dest, byte_length[j]);
            ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
            diff = ((end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec));
            printf("Time taken for  my_memmove for %d byte transfer is %lf\n", byte_length[j], diff);
        }
    }
    if (number == 5)
    {
        // show statistics of all bbb execution times
    }
    if (ret_stat)
        ; // Not used
}
#endif
