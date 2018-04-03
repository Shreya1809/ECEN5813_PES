

#include "dma.h"
#include "memory_dma.h"
#include "MKL25Z4.h"
#include <stdint.h>

mem_enum memmove(uint8_t * src, uint8_t * dst, size_t length)
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

mem_enum memmove_dma(uint8_t * src, uint8_t * dst, size_t length, size_t size)
{
	__disable_irq();
	mem_enum return_status;
	int8_t i;

	if (src == NULL || dst == NULL || length <= 0 || size <= 0)          // if pointers are NULL
        {
		return_status = INVALID_POINTER;
	}
	else if ( size != 1 || size != 2 || size != 3)
	{
		return_status = ERROR;
	}
	else if ((dst + length  < src) && (src + length  < dst))    //Should return a pass for a move
	{
		
		//set source address
		DMA_SAR0 = src;
		// Set Destination Address
		DMA_DAR0 = dst;
		// Set BCR for the no of bytes to be transfered
		DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length);
		// Enable interrupt on completion of transfer, Source and destination address increment after every transfer & Set Source and Destination size as 8bit
		DMA_DCR0 |= ( DMA_DCR_EINT_MASK | DMA_DCR_DINC_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(size) | DMA_DCR_DSIZE(size));
		// Start DMA transfer
		DMA_DCR0 |= DMA_DCR_START_MASK;
		return_status = NO_OVERLAP;
	}
	else if ((dst > src) && (src + length  > dst))      // if source overlaps destination
	{
	
		int overlap = src + length - dst; // overlap
		//memmove_overlap(dst, dst + length - overlap, overlap ); //memmove of overlap data
		DMA_SAR0 = dst;
		// Set Destination Address
		DMA_DAR0 = dst + length - overlap;
		// Set BCR for the no of bytes to be transfered
		DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(overlap);
		// Enable interrupt on completion of transfer, Source and destination address increment after every transfer & Set Source and Destination size as 8bit
		DMA_DCR0 |= ( DMA_DCR_EINT_MASK | DMA_DCR_DINC_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(size) | DMA_DCR_DSIZE(size));
		// Start DMA transfer
		DMA_DCR0 |= DMA_DCR_START_MASK;
		
		//memmove_overlap(src, dst, length-overlap ); //memmove of the remaining data
		DMA_SAR0 = src;
		// Set Destination Address
		DMA_DAR0 = dst;
		// Set BCR for the no of bytes to be transfered
		DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length-overlap );
		// Enable interrupt on completion of transfer, Source and destination address increment after every transfer & Set Source and Destination size as 8bit
		DMA_DCR0 |= ( DMA_DCR_EINT_MASK | DMA_DCR_DINC_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(size) | DMA_DCR_DSIZE(size));
		// Start DMA transfer
		DMA_DCR0 |= DMA_DCR_START_MASK;

        return_status = SRC_IN_DST_OVERLAP;
	}
	else                                                      //destination overlaps source
	{
		
		if ((size == 2 && length%2 != 0))
		{
		//memmove(src + (length - length%2), dst + (length - length%2), length%2);
		//set source address
		DMA_SAR0 = (src + (length - length%2));
		// Set Destination Address
		DMA_DAR0 = (dst + (length - length%2));
		// Set BCR for the no of bytes to be transfered
		DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length%2);
		// Enable interrupt on completion of transfer, Source and destination address increment after every transfer & Set Source and Destination size as 8bit
		DMA_DCR0 |= ( DMA_DCR_EINT_MASK | DMA_DCR_DINC_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(2) | DMA_DCR_DSIZE(2));
		// Start DMA transfer
		DMA_DCR0 |= DMA_DCR_START_MASK
		}
		else if ((size == 4 && length%4 != 0))
		{
		//memmove(src + (length - length%4), dst + (length - length%4), length%4);// handling the remainaing length of bytes to be transferred
		//set source address
		DMA_SAR0 = (src + (length - length%4));
		// Set Destination Address
		DMA_DAR0 = (dst + (length - length%4));
		// Set BCR for the no of bytes to be transfered
		DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length%4);
		// Enable interrupt on completion of transfer, Source and destination address increment after every transfer & Set Source and Destination size as 8bit
		DMA_DCR0 |= ( DMA_DCR_EINT_MASK | DMA_DCR_DINC_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(4) | DMA_DCR_DSIZE(4));
		// Start DMA transfer
		DMA_DCR0 |= DMA_DCR_START_MASK
		} 
		else  //if size is 1,2 or 4 
		{
		//set source address
		DMA_SAR0 = src;
		// Set Destination Address
		DMA_DAR0 = dst;
		// Set BCR for the no of bytes to be transfered
		DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length);
		// Enable interrupt on completion of transfer, Source and destination address increment after every transfer & Set Source and Destination size as 8bit
		DMA_DCR0 |= ( DMA_DCR_EINT_MASK | DMA_DCR_DINC_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(size) | DMA_DCR_DSIZE(size));
		// Start DMA transfer
		DMA_DCR0 |= DMA_DCR_START_MASK;
		}// return_status = ERROR;

	return_status = DST_IN_SRC_OVERLAP;
	}
	
	__enable_irq();
	return return_status;
}

mem_enum memset_dma(uint8_t * dst, size_t length, uint8_t data, size_t size)
{
	uint8_t *b = (uint8_t *)malloc(sizeof(uint8_t)); //temp pointer to store src address 
	*b = data;
	mem_enum return_status = NO_ERROR;
  	int8_t i;

	if (dst == NULL || length <= 0)                  //null pointer
	{
		return_status = INVALID_POINTER;
	}
	else if ( size != 1 || size != 2 || size != 3)
	{
		return_status = ERROR;
	}
    	else if
	{	
		
    		
    			
	 if ((size == 2)&&(length%2 != 0))
    		{
    			//memset(dst + (length - length%2), length%2, data); // in case length is indivisible by 2, and 2 bytes is the size, this line will account for the remaining 1 byte
			// Source Address
    			DMA_SAR0 = b;
    			// Destination Address
    			DMA_DAR0 = (dst + (length - length%2));
    			// BCR for the length of bytes to transfer
    			DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length%2);
    			// Enable interrupt on completion of transfer, Source and destination address increment after every transfer & Set Source and Destination size as 8bit
    			DMA_DCR0 |= ( DMA_DCR_EINT_MASK | DMA_DCR_DINC_MASK | DMA_DCR_DSIZE(2));
       			// Start DMA transfer
    			DMA_DCR0 |= DMA_DCR_START_MASK;
			
    		}
    	else if ((size == 4)&&(length%4 != 0))
    		{
    			//memset(dst + (length - length%4), length%4, data); // in case length is indivisible by 4, and 4 bytes is the size, this line will account for the remaining bytes
			// Source Address
    			DMA_SAR0 = b;
    			// Destination Address
    			DMA_DAR0 = (dst + (length - length%4));
    			// BCR for the length of bytes to transfer
    			DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length%4);
    			// Enable interrupt on completion of transfer, Source and destination address increment after every transfer & Set Source and Destination size as 8bit
    			DMA_DCR0 |= ( DMA_DCR_EINT_MASK | DMA_DCR_DINC_MASK | DMA_DCR_DSIZE(4));
       			// Start DMA transfer
    			DMA_DCR0 |= DMA_DCR_START_MASK;
    		}
    	 else 
		{
    			
    			// Source Address
    			DMA_SAR0 = b;
    			// Destination Address
    			DMA_DAR0 = dst;
    			// BCR for the length of bytes to transfer
    			DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length);
    			// Enable interrupt on completion of transfer, Source and destination address increment after every transfer & Set Source and Destination size as 8bit
    			DMA_DCR0 |= ( DMA_DCR_EINT_MASK | DMA_DCR_DINC_MASK | DMA_DCR_DSIZE(size));
       			// Start DMA transfer
    			DMA_DCR0 |= DMA_DCR_START_MASK;
		}
	//else return_status = ERROR;
    	        return return_status;
	}
























