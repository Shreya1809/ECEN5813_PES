
#include "profiler.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include "memory.h"
#include "logger.h"
#include "conversion.h"
#include "logger_queue.h"

log_struct_t2  *logged_data2;
uint32_t start, end, diff;
#ifdef KL25Z

#include "dma.h"
#include "memory_dma.h"
#include "MKL25Z4.h"
//#include "MKL25Z4_extension.h"
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
    
    uint32_t temp;
    uint32_t len_diff = 0;

     size_t byte_length[4] = {10, 100, 1000, 5000};
     logged_data2 = (log_struct_t2 *) malloc(sizeof(log_struct_t2));

    if (test_type == MEMMOVE_DMA)
    {
    			//PRINTF("LOGGER for MEMMOVE DMA 10, 100, 1000 , 5000 BYTES , BLOCK SIZE ONE BYTE");
                start = SysTick->VAL;
                mem_enum ret = memmove_dma(source, dest, 10 , ONE_BYTE );
                while(DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                //if(ret != NO_ERROR || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
                diff = start - end;
                //PRINTF("Time taken for  memmove dma for 10 byte transfer with 1 byte block size is %lu us\n ", diff/21);
                temp = diff;
                						while(temp != 0)
                						{
                							temp = temp/10;
                							len_diff++;
                						}

                						temp = 0;

                				log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
                				log_item_KL25Z2(tx_buffer, logged_data2);
								LOG_FLUSH(tx_buffer);

                start = SysTick->VAL;
				ret = memmove_dma(source, dest, 100 , ONE_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                if(ret != NO_ERROR || DMA_CHECK_ERROR)
                {
                	//PRINTF("DMA ERROR\n");
                	log_create(logged_data, LOG_ERROR,PROFILER, 9, (uint8_t*)"DMA ERROR");
                	 log_item_KL25Z(tx_buffer, logged_data);
					 LOG_FLUSH(tx_buffer);
                }
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);

				diff = start - end;
				//PRINTF("Time taken for  memmove dma for 100 byte transfer with 1 byte block size is %lu us\n ", diff/21);
				temp = diff;
										while(temp != 0)
										{
											temp = temp/10;
											len_diff++;
										}

										temp = 0;

								log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
								log_item_KL25Z2(tx_buffer, logged_data2);
								LOG_FLUSH(tx_buffer);

				start = SysTick->VAL;
				ret = memmove_dma(source, dest, 1000 , ONE_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                //if(ret != NO_ERROR || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);

				diff = start - end;
				//PRINTF("Time taken for  memmove dma for 1000 byte transfer with 1 byte block size is %lu us\n ", diff/21);
				temp = diff;
										while(temp != 0)
										{
											temp = temp/10;
											len_diff++;
										}

										temp = 0;

								log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
								log_item_KL25Z2(tx_buffer, logged_data2);
								LOG_FLUSH(tx_buffer);
				start = SysTick->VAL;
				ret = memmove_dma(source, dest, 5000 , ONE_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                //if(ret != NO_ERROR || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);

				diff = start - end;
				//PRINTF("Time taken for  memmove dma for 5000 byte transfer with 1 byte block size is %lu us\n ", diff/21);
				temp = diff;
										while(temp != 0)
										{
											temp = temp/10;
											len_diff++;
										}

										temp = 0;

								log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
								log_item_KL25Z2(tx_buffer, logged_data2);
								LOG_FLUSH(tx_buffer);

				//PRINTF("LOGGER for MEMMOVE DMA 10, 100, 1000 , 5000 BYTES , BLOCK SIZE TWO BYTES");
				start = SysTick->VAL;
				ret = memmove_dma(source, dest, 10, TWO_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                //if(ret != NO_ERROR || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);

				diff = start - end;
				//PRINTF("Time taken for  memmove dma for 10 byte transfer with 2 bytes block size is %lu us\n ", diff/21);
				temp = diff;
														while(temp != 0)
														{
															temp = temp/10;
															len_diff++;
														}

														temp = 0;

												log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
												log_item_KL25Z2(tx_buffer, logged_data2);
												LOG_FLUSH(tx_buffer);
				start = SysTick->VAL;
				ret = memmove_dma(source, dest, 100, TWO_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                //if(ret != NO_ERROR  || DMA_CHECK_ERROR )	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);

				diff = start - end;
				//PRINTF("Time taken for  memmove dma for 100 byte transfer with 2 bytes block size is %lu us\n ", diff/21);
				temp = diff;
														while(temp != 0)
														{
															temp = temp/10;
															len_diff++;
														}

														temp = 0;

												log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
												log_item_KL25Z2(tx_buffer, logged_data2);
												LOG_FLUSH(tx_buffer);
				start = SysTick->VAL;
				ret = memmove_dma(source, dest, 1000, TWO_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                //if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);

				diff = start - end;
				//PRINTF("Time taken for  memmove dma for 1000 byte transfer with 2 bytes block size is %lu us\n ", diff/21);
				temp = diff;
														while(temp != 0)
														{
															temp = temp/10;
															len_diff++;
														}

														temp = 0;

												log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
												log_item_KL25Z2(tx_buffer, logged_data2);
												LOG_FLUSH(tx_buffer);
				start = SysTick->VAL;
				ret = memmove_dma(source, dest,5000, TWO_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
               // if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);

				diff = start - end;
				//PRINTF("Time taken for  memmove dma for 5000 byte transfer with 2 bytes block size is %lu us\n ", diff/21);
				temp = diff;
														while(temp != 0)
														{
															temp = temp/10;
															len_diff++;
														}

														temp = 0;

												log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
												log_item_KL25Z2(tx_buffer, logged_data2);
												LOG_FLUSH(tx_buffer);

				//PRINTF("LOGGER for MEMMOVE DMA 10, 100, 1000 , 5000 BYTES , BLOCK SIZE FOUR BYTES");
                start = SysTick->VAL;
				ret = memmove_dma(source, dest,8, FOUR_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                //if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);

				diff = start - end;
				//PRINTF("Time taken for  memmove dma for 10 byte transfer with 4 bytes block size is %lu us\n ", diff/21);
				temp = diff;
														while(temp != 0)
														{
															temp = temp/10;
															len_diff++;
														}

														temp = 0;

												log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
												log_item_KL25Z2(tx_buffer, logged_data2);
												LOG_FLUSH(tx_buffer);
				start = SysTick->VAL;
				ret = memmove_dma(source, dest,100, FOUR_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
                //if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);

				diff = start - end;
				//PRINTF("Time taken for  memmove dma for 100 byte transfer with 4 bytes block size is %lu us\n ", diff/21);
				temp = diff;
														while(temp != 0)
														{
															temp = temp/10;
															len_diff++;
														}

														temp = 0;

												log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
												log_item_KL25Z2(tx_buffer, logged_data2);
												LOG_FLUSH(tx_buffer);
				start = SysTick->VAL;
				ret = memmove_dma(source, dest,1000, FOUR_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
                end = SysTick->VAL;
               // if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
				//end = SysTick->VAL;
				diff = start - end;
				//PRINTF("Time taken for  memmove dma for 1000 byte transfer with 4 bytes block size is %lu us\n ", diff/21);
				temp = diff;
														while(temp != 0)
														{
															temp = temp/10;
															len_diff++;
														}

														temp = 0;

												log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
												log_item_KL25Z2(tx_buffer, logged_data2);
												LOG_FLUSH(tx_buffer);
				start = SysTick->VAL;
				ret = memmove_dma(source, dest,5000, FOUR_BYTE );
                while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
               // if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
                DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
				end = SysTick->VAL;
				diff = start - end;
				//PRINTF("Time taken for  memmove dma for 5000 byte transfer with 4 bytes block size is %lu us\n ", diff/21);

				temp = diff;
						while(temp != 0)
						{
							temp = temp/10;
							len_diff++;
						}

						temp = 0;

				log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
				log_item_KL25Z2(tx_buffer, logged_data2);
				LOG_FLUSH(tx_buffer);
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
                //PRINTF("Time taken for  memset dma for 10 byte transfer with 1 byte block size is %lu us\n ", diff/21);
                temp = diff;
                										while(temp != 0)
                										{
                											temp = temp/10;
                											len_diff++;
                										}

                										temp = 0;

                								log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
                								log_item_KL25Z2(tx_buffer, logged_data2);
												LOG_FLUSH(tx_buffer);
               start = SysTick->VAL;
			   ret = memset_dma(dest, 100, 5,ONE_BYTE );
			   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
			   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
			   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
			   end = SysTick->VAL;
			   diff = start - end;
			   // print report on sizes
			  // PRINTF("Time taken for  memset dma for 100 byte transfer with 1 byte block size is %lu us\n ", diff/21);
		       temp = diff;
											while(temp != 0)
											{
												temp = temp/10;
												len_diff++;
											}

											temp = 0;

									log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
									log_item_KL25Z2(tx_buffer, logged_data2);
									LOG_FLUSH(tx_buffer);
			   start = SysTick->VAL;
			   ret = memset_dma(dest, 1000, 5,ONE_BYTE );
			   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
			   end = SysTick->VAL;
			   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
			   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
			   //end = SysTick->VAL;
			   diff = start - end;
			   // print report on sizes
			  // PRINTF("Time taken for  memset dma for 1000 byte transfer with 1 byte block size is %lu us\n ", diff/21);
			   temp = diff;
			   														while(temp != 0)
			   														{
			   															temp = temp/10;
			   															len_diff++;
			   														}

			   														temp = 0;

			   												log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
			   												log_item_KL25Z2(tx_buffer, logged_data2);
															   LOG_FLUSH(tx_buffer);
			   start = SysTick->VAL;
			   ret = memset_dma(dest, 5000, 5,ONE_BYTE );
			   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
			   end = SysTick->VAL;
			   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
			   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
			   //end = SysTick->VAL;
			   diff = start - end;
			   // print report on sizes
			   //PRINTF("Time taken for  memset dma for 5000 byte transfer with 1 byte block size is %lu us\n ", diff/21);
			   temp = diff;
			   														while(temp != 0)
			   														{
			   															temp = temp/10;
			   															len_diff++;
			   														}

			   														temp = 0;

			   												log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
			   												log_item_KL25Z2(tx_buffer, logged_data2);
															   LOG_FLUSH(tx_buffer);
			   start = SysTick->VAL;
			   ret = memset_dma(dest, 10, 5,TWO_BYTE );
			   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
			   end = SysTick->VAL;
			if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
			DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
			   //end = SysTick->VAL;
			   diff = start - end;
			   // print report on sizes
			  // PRINTF("Time taken for  memset dma for 10 byte transfer with 2 bytes block size is %lu us\n ", diff/21);
			   temp = diff;
											while(temp != 0)
											{
												temp = temp/10;
												len_diff++;
											}

											temp = 0;

									log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
									log_item_KL25Z2(tx_buffer, logged_data2);
									LOG_FLUSH(tx_buffer);
			  start = SysTick->VAL;
		   ret = memset_dma(dest, 100, 5,TWO_BYTE );
		   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
		   end = SysTick->VAL;
		   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
		   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
		   //end = SysTick->VAL;
		   diff = start - end;
		   // print report on sizes
		  // PRINTF("Time taken for  memset dma for 100 byte transfer with 2 bytes block size is %lu us\n ", diff/21);
		   temp = diff;
		   														while(temp != 0)
		   														{
		   															temp = temp/10;
		   															len_diff++;
		   														}

		   														temp = 0;

		   												log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
		   												log_item_KL25Z2(tx_buffer, logged_data2);
														   LOG_FLUSH(tx_buffer);
		   start = SysTick->VAL;
		   ret = memset_dma(dest, 1000, 5,TWO_BYTE );
		   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
		   end = SysTick->VAL;
		   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
		   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
		  // end = SysTick->VAL;
		   diff = start - end;
		   // print report on sizes
		  // PRINTF("Time taken for  memset dma for 1000 byte transfer with 2 bytes block size is %lu us\n ", diff/21);
		   temp = diff;
		   														while(temp != 0)
		   														{
		   															temp = temp/10;
		   															len_diff++;
		   														}

		   														temp = 0;

		   												log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
		   												log_item_KL25Z2(tx_buffer, logged_data2);
														   LOG_FLUSH(tx_buffer);
		   start = SysTick->VAL;
		   ret = memset_dma(dest, 5000, 5,TWO_BYTE );
		   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
		   end = SysTick->VAL;
		   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
		   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
		   //end = SysTick->VAL;
		   diff = start - end;
		   // print report on sizes
		  // PRINTF("Time taken for  memset dma for 5000 byte transfer with 2 bytes block size is %lu us\n ", diff/21);
		   temp = diff;
		   														while(temp != 0)
		   														{
		   															temp = temp/10;
		   															len_diff++;
		   														}

		   														temp = 0;

		   												log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
		   												log_item_KL25Z2(tx_buffer, logged_data2);
														   LOG_FLUSH(tx_buffer);
		   start = SysTick->VAL;
		   ret = memset_dma(dest, 8, 5,FOUR_BYTE );
		   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
		   end = SysTick->VAL;
		   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
		   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
		   //end = SysTick->VAL;
		   diff = start - end;
		   // print report on sizes
		   //PRINTF("Time taken for  memset dma for 10 byte transfer with 4 bytes block size is %lu us\n ", diff/21);
		   temp = diff;
		   														while(temp != 0)
		   														{
		   															temp = temp/10;
		   															len_diff++;
		   														}

		   														temp = 0;

		   												log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
		   												log_item_KL25Z2(tx_buffer, logged_data2);
														   LOG_FLUSH(tx_buffer);
		   start = SysTick->VAL;
		   ret = memset_dma(dest, 100, 5,FOUR_BYTE );
		   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
		   end = SysTick->VAL;
		   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
		   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
		   //end = SysTick->VAL;
		   diff = start - end;
		   // print report on sizes
//		   PRINTF("Time taken for  memset dma for 100 byte transfer with 4 bytes block size is %lu us\n ", diff/21);
		   temp = diff;
		   														while(temp != 0)
		   														{
		   															temp = temp/10;
		   															len_diff++;
		   														}

		   														temp = 0;

		   												log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
		   												log_item_KL25Z2(tx_buffer, logged_data2);
														   LOG_FLUSH(tx_buffer);
		   start = SysTick->VAL;
		   ret = memset_dma(dest, 1000, 5,FOUR_BYTE );
		   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
		   end = SysTick->VAL;
		   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
		   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
		  // end = SysTick->VAL;
		   diff = start - end;
		   // print report on sizes
		   //PRINTF("Time taken for  memset dma for 1000 byte transfer with 4 bytes block size is %lu us\n ", diff/21);
		   temp = diff;
		   														while(temp != 0)
		   														{
		   															temp = temp/10;
		   															len_diff++;
		   														}

		   														temp = 0;

		   												log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
		   												log_item_KL25Z2(tx_buffer, logged_data2);
														   LOG_FLUSH(tx_buffer);
		   start = SysTick->VAL;
		   ret = memset_dma(dest, 5000, 5,FOUR_BYTE );
		   while((ret == NO_ERROR) && DMA_DSR_BCR0 & DMA_DSR_BCR_BSY(1));
		   end = SysTick->VAL;
		   if(ret != NO_ERROR  || DMA_CHECK_ERROR)	PRINTF("DMA ERROR\n");
		   DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);
		   //end = SysTick->VAL;
		   diff = start - end;
		   // print report on sizes
//		   PRINTF("Time taken for  memset dma for 5000 byte transfer with 4 bytes block size is %lu us\n ", diff/21);
		   temp = diff;
		   														while(temp != 0)
		   														{
		   															temp = temp/10;
		   															len_diff++;
		   														}

		   														temp = 0;

		   												log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
		   												log_item_KL25Z2(tx_buffer, logged_data2);
														   LOG_FLUSH(tx_buffer);
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
            //PRINTF("Time taken for my memmove for %d byte transfer is %lu us\n", byte_length[j], diff/21);
            temp = diff;
            														while(temp != 0)
            														{
            															temp = temp/10;
            															len_diff++;
            														}

            														temp = 0;

            												log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
            												log_item_KL25Z2(tx_buffer, logged_data2);
															LOG_FLUSH(tx_buffer);
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
            //PRINTF("Time taken for my memset for %d byte transfer is %lu us\n", byte_length[j], diff/21);
            temp = diff;
            														while(temp != 0)
            														{
            															temp = temp/10;
            															len_diff++;
            														}

            														temp = 0;

            												log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
            												log_item_KL25Z2(tx_buffer, logged_data2);
															LOG_FLUSH(tx_buffer);
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
		//	PRINTF("Time taken for std memmove for %d byte transfer is %lu us\n", byte_length[j], diff/21);
			temp = diff;
																	while(temp != 0)
																	{
																		temp = temp/10;
																		len_diff++;
																	}

																	temp = 0;

															log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
															log_item_KL25Z2(tx_buffer, logged_data2);
															LOG_FLUSH(tx_buffer);
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
			//PRINTF("Time taken for std memset for %d byte transfer is %lu us\n", byte_length[j], diff/21);
			temp = diff;
																	while(temp != 0)
																	{
																		temp = temp/10;
																		len_diff++;
																	}

																	temp = 0;

															log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/21);
															log_item_KL25Z2(tx_buffer, logged_data2);
															LOG_FLUSH(tx_buffer);
		}
    }
}
#else

void bbb_profile_option(uint8_t number)
{
	const size_t byte_length[4] = {10, 100, 1000, 5000};
	tx_buffer = (cb_struct *)malloc(sizeof(cb_struct));
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
	uint32_t temp;
	uint32_t len_diff = 0;
	logged_data2 = (log_struct_t2 *) malloc(sizeof(log_struct_t2));
	cb_enum mystatus = cb_init(tx_buffer, 5000);
				if (mystatus != CB_SUCCESS)
				{
				   printf("Error initializing tx buffer\n");
				}
    if (number == 1)
    {

        	ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
			memmove(source, dest, 5000 );
			ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
			diff = ((end_time.tv_sec - start_time.tv_sec)*1000000000 + (end_time.tv_nsec - start_time.tv_nsec));
			//printf("Time taken for std memmove for 5000 byte transfer is %lf\n", diff);
			temp = diff;
					while(temp != 0)
					{
						temp = temp/10;
						len_diff++;
					}

					temp = 0;

			log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff);
			log_item_BBB2(tx_buffer, logged_data2);
			LOG_FLUSH(tx_buffer);

		ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
			memmove(source, dest, 1000 );
			ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
			diff = ((end_time.tv_sec - start_time.tv_sec)*1000000000 + (end_time.tv_nsec - start_time.tv_nsec));
			//printf("Time taken for std memmove for 1000 byte transfer is %lf\n", diff);
			temp = diff;
					while(temp != 0)
					{
						temp = temp/10;
						len_diff++;
					}

					temp = 0;

			log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff);
			log_item_BBB2(tx_buffer, logged_data2);
			LOG_FLUSH(tx_buffer);

		ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
			memmove(source, dest, 100 );
			ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
			diff = ((end_time.tv_sec - start_time.tv_sec)*1000000000 + (end_time.tv_nsec - start_time.tv_nsec));
			//printf("Time taken for std memmove for 100 byte transfer is %lf\n", diff);
			temp = diff;
					while(temp != 0)
					{
						temp = temp/10;
						len_diff++;
					}

					temp = 0;

			log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff);
			log_item_BBB2(tx_buffer, logged_data2);
			LOG_FLUSH(tx_buffer);

		ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
			memmove(source, dest, 10);
			ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
			diff = ((end_time.tv_sec - start_time.tv_sec)*1000000000 + (end_time.tv_nsec - start_time.tv_nsec));
			//printf("Time taken for std memmove for 10 byte transfer is %lf\n", diff);
			temp = diff;
					while(temp != 0)
					{
						temp = temp/10;
						len_diff++;
					}

					temp = 0;

			log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff);
			log_item_BBB2(tx_buffer, logged_data2);
			LOG_FLUSH(tx_buffer);



    }
    if (number == 2)
    {
    	ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
		memset(source, 10, 5000);
		ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
		diff = ((end_time.tv_sec - start_time.tv_sec)*1000000000 + (end_time.tv_nsec - start_time.tv_nsec));
		//printf("Time taken for std memset for 5000 byte transfer is %lf\n", diff);
		temp = diff;
					while(temp != 0)
					{
						temp = temp/10;
						len_diff++;
					}

					temp = 0;

			log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff);
			log_item_BBB2(tx_buffer, logged_data2);
			LOG_FLUSH(tx_buffer);

	ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
		memset(source, 10, 1000);
		ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
		diff = ((end_time.tv_sec - start_time.tv_sec)*1000000000 + (end_time.tv_nsec - start_time.tv_nsec));
		//printf("Time taken for std memset for 1000 byte transfer is %lf\n", diff);
		temp = diff;
					while(temp != 0)
					{
						temp = temp/10;
						len_diff++;
					}

					temp = 0;

			log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff);
			log_item_BBB2(tx_buffer, logged_data2);
			LOG_FLUSH(tx_buffer);

	ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
		memset(source, 10, 100);
		ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
		diff = ((end_time.tv_sec - start_time.tv_sec)*1000000000 + (end_time.tv_nsec - start_time.tv_nsec));
		//printf("Time taken for std memset for 100 byte transfer is %lf\n", diff);
		temp = diff;
					while(temp != 0)
					{
						temp = temp/10;
						len_diff++;
					}

					temp = 0;

			log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff);
			log_item_BBB2(tx_buffer, logged_data2);
			LOG_FLUSH(tx_buffer);

	ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
		memset(source, 10, 10);
		ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
		diff = ((end_time.tv_sec - start_time.tv_sec)*1000000000 + (end_time.tv_nsec - start_time.tv_nsec));
		//printf("Time taken for std memset for 10 byte transfer is %lf\n", diff);
		temp = diff;
					while(temp != 0)
					{
						temp = temp/10;
						len_diff++;
					}

					temp = 0;

			log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff);
			log_item_BBB2(tx_buffer, logged_data2);
			LOG_FLUSH(tx_buffer);
    }
    if (number == 3)
    {
        for (int j = 3; j >= 0; j--)
        {
			
            ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
            my_memset(source, byte_length[j], 10);
            ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
            diff = ((end_time.tv_sec - start_time.tv_sec)*1000000000 + (end_time.tv_nsec - start_time.tv_nsec));
            //printf("Time taken for  my_memset for %d byte transfer is %lf\n", byte_length[j], diff);
			temp = diff;
					while(temp != 0)
					{
						temp = temp/10;
						len_diff++;
					}

					temp = 0;

			log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/20);
			log_item_BBB2(tx_buffer, logged_data2);
			LOG_FLUSH(tx_buffer);

        }
    }
    if (number == 4)
    {
        for (int j = 3; j >= 0; j--)
        {
            ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
            my_memmove(source, dest, byte_length[j]);
            ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
            diff = ((end_time.tv_sec - start_time.tv_sec)*1000000000 + (end_time.tv_nsec - start_time.tv_nsec));
            //printf("Time taken for  my_memmove for %d byte transfer is %lf\n", byte_length[j], diff);
			temp = diff;
					while(temp != 0)
					{
						temp = temp/10;
						len_diff++;
					}

					temp = 0;

			log_create1(logged_data2, PROFILING_RESULT,PROFILER, len_diff, diff/20);
			log_item_BBB2(tx_buffer, logged_data2);
			LOG_FLUSH(tx_buffer);
			
        }
    }
	//log_flush_BBB(tx_buffer);
    
    if (ret_stat)
        ; // Not used
}
#endif
