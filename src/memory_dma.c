

#include "dma.h"
#include "memory_dma.h"
#include "MKL25Z4.h"
#include <stdint.h>

/*mem_enum memmove(uint8_t * src, uint8_t * dst, size_t length)
{
    mem_enum return_status = NO_ERROR;
    int8_t i;

    if ( src == NULL || dst == NULL || length <= 0)          // if pointers are NULL
    {
        return_status = INVALID_POINTER;
    }
    else if ((dst + length  < src) && (src + length  < dst))    //if no overlap
    {
        return_status = NO_OVERLAP;
    }
    else                                                           //destination overlaps source
    {
        for(i = 0; i<length; i++)
        {
            *(dst+i) = *(src+i);
        }
    }
    return return_status;
}

mem_enum memset(uint8_t * dst, size_t length, uint8_t value)
{
    mem_enum return_status = NO_ERROR;
    int8_t i;

    if (dst == NULL || length <= 0)                 // if null pointer
    {
        return_status = INVALID_POINTER;
    }
    else
    {
        for (i = 0; i <length; i++)                  //copying value to destination
        {
            *(dst + i) = value;
        }
    }
    return return_status;
}


mem_enum memmove_overlap(uint8_t * src, uint8_t * dst, size_t length)
{
    mem_enum return_status = NO_ERROR;
    uint8_t *a = (uint8_t *)malloc(sizeof(uint8_t)); // a is a temp pointer which holds the source address

    for(int i = 0; i < length; i++)
    {
        *(a+i) = *(src+i);
    }

    {
        //order for dma transfer
        //set source address
        DMA_SAR0 = a;
        // Set Destination Address
        DMA_DAR0 = dst;
        // Set BCR for the no of bytes to be transfered
        DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length);
        // Enable interrupt on completion of transfer, Source and destination address increment after every transfer & Set Source and Destination size as 8bit
        DMA_DCR0 |= ( DMA_DCR_EINT_MASK | DMA_DCR_DINC_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(1) | DMA_DCR_DSIZE(1));
        // Start DMA transfer
        DMA_DCR0 |= DMA_DCR_START_MASK;

        //return_status = DST_IN_SRC_OVERLAP;
    }
    return return_status;
}
*/

mem_enum memmove_dma(uint8_t * src, uint8_t * dst, size_t length, dma_block_size size)
{
    #if 1
    // Working

    //set source address
    DMA_SAR0 = (intptr_t)src;
    // Set Destination Address
    DMA_DAR0 = (intptr_t)dst;
    // Set BCR for the no of bytes to be transfered
    DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length);
    // Enable interrupt on completion of transfer, Source and destination address increment after every transfer & Set Source and Destination size as 8bit
    //DMA_DCR0 |= (DMA_DCR_EINT_MASK | DMA_DCR_DINC_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(1) | DMA_DCR_DSIZE(1));
    DMA_DCR0 |= (DMA_DCR_DINC_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(size) | DMA_DCR_DSIZE(size));
    //return NO_ERROR;
    // Start DMA transfer
    DMA_DCR0 |= DMA_DCR_START_MASK;

    return NO_ERROR;
    #endif

    __disable_irq();
    mem_enum return_status;
    int8_t i;

    if ( !src || !dst || !length || !size ) // NULL pointer or zero size
    {
        return ERROR;
    }

    // No overlap case
    if ((dst + length < src) ||
        (src + length < dst))
    {
        //set source address
        DMA_SAR0 = (intptr_t) src;
        // Set Destination Address
        DMA_DAR0 = (intptr_t) dst;
        // Set BCR for the no of bytes to be transfered
        DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length);
        // Enable interrupt on completion of transfer, Source and destination address increment after every transfer & Set Source and Destination size as 8bit
        DMA_DCR0 |= ( DMA_DCR_EINT_MASK | DMA_DCR_DINC_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(size) | DMA_DCR_DSIZE(size));
        // Start DMA transfer
        DMA_DCR0 |= DMA_DCR_START_MASK;

        if (length%size != 0)
        {
            for(i = 0; i<= length%size; i++)
            {
                *((dst + (length - length%size))+i) = *((src + (length - length%size))+i);
            }

            //return_status = NO_OVERLAP;
            return_status = NO_ERROR;
        }
    }
    else if ((dst > src) && (src + length > dst))      // if source overlaps destination
    {
        int overlap = src + length - dst; // overlap
        //memmove_overlap(dst, dst + length - overlap, overlap ); //memmove of overlap data
        DMA_SAR0 = (intptr_t) dst;
        // Set Destination Address
        DMA_DAR0 = (intptr_t) (dst + length - overlap);
        // Set BCR for the no of bytes to be transfered
        DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(overlap);
        // Enable interrupt on completion of transfer, Source and destination address increment after every transfer & Set Source and Destination size as 8bit
        DMA_DCR0 |= ( DMA_DCR_EINT_MASK | DMA_DCR_DINC_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(size) | DMA_DCR_DSIZE(size));
        // Start DMA transfer
        DMA_DCR0 |= DMA_DCR_START_MASK;

        //memmove_overlap(src, dst, length-overlap ); //memmove of the remaining data
        DMA_SAR0 = (intptr_t) src;
        // Set Destination Address
        DMA_DAR0 =(intptr_t) dst;
        // Set BCR for the no of bytes to be transfered
        DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length-overlap );
        // Enable interrupt on completion of transfer, Source and destination address increment after every transfer & Set Source and Destination size as 8bit
        DMA_DCR0 |= ( DMA_DCR_EINT_MASK | DMA_DCR_DINC_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(size) | DMA_DCR_DSIZE(size));
        // Start DMA transfer
        DMA_DCR0 |= DMA_DCR_START_MASK;

        //return_status = SRC_IN_DST_OVERLAP;
        return_status = NO_ERROR;
    }
    else                                                      //destination overlaps source
    {
        //set source address
        DMA_SAR0 = (intptr_t) src;
        // Set Destination Address
        DMA_DAR0 = (intptr_t) dst;
        // Set BCR for the no of bytes to be transfered
        DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length);
        // Enable interrupt on completion of transfer, Source and destination address increment after every transfer & Set Source and Destination size as 8bit
        DMA_DCR0 |= ( DMA_DCR_EINT_MASK | DMA_DCR_DINC_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(size) | DMA_DCR_DSIZE(size));
        // Start DMA transfer
        DMA_DCR0 |= DMA_DCR_START_MASK;

        if (length%size != 0)
        {
            for(i = 0; i<= length%size; i++)
            {
                *((dst + (length - length%size))+i) = *((src + (length - length%size))+i);
            }

        }

        //return_status = DST_IN_SRC_OVERLAP;
        return_status = NO_ERROR;
    }

    __enable_irq();
    return return_status;
}

mem_enum memset_dma(uint8_t * dst, size_t length, uint8_t data, dma_block_size size)
{
    uint8_t * b; //temp pointer to store src address
    b = &data;
    mem_enum return_status = NO_ERROR;
    int8_t i;

    if (dst == NULL || length <= 0)                  //null pointer
    {
        return_status = INVALID_POINTER;
    }
    else if ( size != 1 && size != 2 && size != 4)
    {
        return_status = ERROR;
    }
    else
    {

        // Source Address
        DMA_SAR0 =(intptr_t) b;
        // Destination Address
        DMA_DAR0 = (intptr_t) dst;
        // BCR for the length of bytes to transfer
        DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length);
        // Enable interrupt on completion of transfer, Source and destination address increment after every transfer & Set Source and Destination size as 8bit
        DMA_DCR0 |= ( DMA_DCR_EINT_MASK | DMA_DCR_DINC_MASK | DMA_DCR_DSIZE(size));
        // Start DMA transfer
        DMA_DCR0 |= DMA_DCR_START_MASK;



        if (length%size != 0)
        {
            for (i = 0; i<= length%size; i++)
            {
                *((dst + (length - length%size ))+ i) = data;
            }
        }
        //else return_status = ERROR;
    }
    return return_status;
}
