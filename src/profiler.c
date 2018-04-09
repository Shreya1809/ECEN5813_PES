
#include "profiler.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include "memory.h"

const size_t byte_length[4] = {10, 100, 1000, 5000};
const size_t size[3] = {1, 2, 4};
size_t start, end, diff;
#ifdef KL25Z

#include "dma.h"
#include "memory_dma.h"
#include "MKL25Z4.h"
#include "MKL25Z4_extension.h"
#include "uart.h"
#include "platform.h"

void systick_init()
{
    SysTick->LOAD |= SysTick_LOAD_RELOAD_Msk;                                //load value is 0X00FFFFFF which is the maximum
    SysTick->CTRL |= (SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk); //counter enabled, processor clock
    SysTick->VAL = 0;
    //begin = SysTick->VAL;
}

void kl25z_profile_option(uint8_t number)
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

    uint8_t *src = &x[20];
    uint8_t *dst = &x[0];
    size_t length = 16;


    //dma_clockenable();
    //SIM->SCGC7 |= SIM_SCGC7_DMA(1);
    //SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
    SIM_BWR_SCGC7_DMA(SIM, 1);
    SIM_BWR_SCGC6_DMAMUX(SIM, 1);
    //SIM->SOPT2 |= SIM_SOPT2_MCGFLLCLK_MASK;
    // Using below from clock setup
    //SIM_BWR_SOPT2_PLLFLLSEL(SIM, 1); // MCGPLLCLK clock with fixed divide by two

    //Clear the CHCFG[ENBL] and CHCFG[TRIG] fields of the DMA channel
    //DMAMUX0->CHCFG[0] = DMAMUX_CHCFG_ENBL(0) | DMAMUX_CHCFG_TRIG(0);

    // Clearing Source size and Destination size fields.
    //DMA_DCR0 &= ~(DMA_DCR_SSIZE_MASK | DMA_DCR_DSIZE_MASK);

    // Enables the DMA channel and select the DMA Channel Source
    DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(2);

    //NVIC_EnableIRQ(DMA2_IRQn);

    //DMA_DCR0 |= DMA_DCR_EINT_MASK;

    for (int j = 1; j < 7; j++)
    {

        for (int i = 0; i < length; i++)
        {
            src[i] = i * j;
            dst[i] = 0;
        }

        //set source address
        DMA_SAR0 = (intptr_t)src;
        // Set Destination Address
        DMA_DAR0 = (intptr_t)dst;
        // Set BCR for the no of bytes to be transfered
        DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length);
        // Enable interrupt on completion of transfer, Source and destination address increment after every transfer & Set Source and Destination size as 8bit
        //DMA_DCR0 |= (DMA_DCR_EINT_MASK | DMA_DCR_DINC_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(1) | DMA_DCR_DSIZE(1));
        DMA_DCR0 |= (DMA_DCR_DINC_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(1) | DMA_DCR_DSIZE(1));
        // Start DMA transfer
        DMA_DCR0 |= DMA_DCR_START_MASK;

        while (DMA_DSR_BCR0 & DMA_DSR_BCR_BCR_MASK)
            ;

        PRINTF("Transfer complete\n");
        for (int i = 0; i < length; i++)
        {
            PRINTF("dst[%d] = %d\n", i, dst[i]);
        }
    }

    return;

    if (number == 1)
    {

        for (int j = 0; j < 4; j++)
        {
            for (int m = 0; m < 3; m++)
            {
                // Todo - may need to ensure this is reset to maximum value
                start = SysTick->VAL;
                memmove_dma(source, dest, byte_length[j], size[m]);
                end = SysTick->VAL;
                diff = start - end;
                //while (DMA_DSR_BCR0 & DMA_DSR_BCR_BSY_MASK);
                //while (!(DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK));
                while (DMA_DSR_BCR0 & DMA_DSR_BCR_BCR_MASK)
                    ;
                uint32_t diff2 = start - SysTick->VAL;
                // print report on sizes
                PRINTF("Time taken for std memmove for %d byte transfer is %ld %ld\n", byte_length[j], diff, diff2);
            }
        }
    }
    if (number == 2)
    {

        for (int j = 0; j < 4; j++)
        {
            for (int m = 0; m < 3; m++)
            {
                start = SysTick->VAL;
                memset_dma(dest, byte_length[j], 5, size[m]);
                end = SysTick->VAL;
                diff = start - end;
                // print report on sizes
                PRINTF("Time taken for std memmove for %d byte transfer is %ld\n", byte_length[j], diff);
            }
        }
    }

    if (number == 3)
    {

        for (int j = 0; j < 4; j++)
        {

            start = SysTick->VAL;
            my_memmove(source, dest, byte_length[j]);
            end = SysTick->VAL;
            diff = start - end;
            // print report on sizes
            PRINTF("Time taken for std memmove for %d byte transfer is %ld\n", byte_length[j], diff);
        }
    }
    if (number == 4)
    {

        for (int j = 0; j < 4; j++)
        {

            start = SysTick->VAL;
            my_memset(dest, byte_length[j], 10);
            end = SysTick->VAL;
            diff = start - end;
            // print report on sizes
            PRINTF("Time taken for std memmove for %d byte transfer is %ld\n", byte_length[j], diff);
        }
    }
    if (number == 5)
    {
        //get statistics for all kl25z execution times
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
        for (int j = 0; j < 4; j++)
        {
            ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
            memmove(source, dest, byte_length[j]);
            ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
            diff = ((end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec));
            printf("Time taken for std memmove for %d byte transfer is %lf\n", byte_length[j], diff);
        }
    }
    if (number == 2)
    {
        for (int j = 0; j < 4; j++)
        {
            ret_stat = clock_gettime(CLOCK_REALTIME, &start_time);
            memset(source, 10, byte_length[j]);
            ret_stat = clock_gettime(CLOCK_REALTIME, &end_time);
            diff = ((end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec));
            printf("Time taken for std memset for %d byte transfer is %lf\n", byte_length[j], diff);
        }
    }
    if (number == 3)
    {
        for (int j = 0; j < 4; j++)
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
        for (int j = 0; j < 4; j++)
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
