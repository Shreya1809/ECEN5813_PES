


#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <stdint.h>
#include <stdlib.h>

typedef enum  {
	NO_ERROR,
	ERROR,
	INVALID_POINTER,
	/*
  	NO_OVERLAP,
  	SRC_IN_DST_OVERLAP,
  	DST_IN_SRC_OVERLAP,
	*/
}mem_enum;

typedef enum
{
    ONE_BYTE = 1,
    TWO_BYTE = 2,
    FOUR_BYTE = 0,
} dma_block_size;


/*typedef struct {
  	uint8_t *src;
  	uint8_t *dst;
  	size_t length;
  	int8_t value;
  	size_t size;
}mem_struct;*/


//mem_enum memmove(uint8_t * src, uint8_t * dst, size_t length);
//mem_enum memset(uint8_t * dst, size_t length, uint8_t value);
//mem_enum memmove_overlap(uint8_t * src, uint8_t * dst, size_t length);
mem_enum memmove_dma(uint8_t * src, uint8_t * dst, uint32_t length, dma_block_size size);
mem_enum memset_dma(uint8_t * dst, uint32_t length, uint8_t value, dma_block_size size);

#endif
