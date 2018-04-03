/* dma.h
 * brief : DMA configuration function
*/


#ifndef __DMA_H__
#define __DMA_H__


/**
* @brief - Enables the clock for DMA
* @return void
**/
void dma_clockenable();

/**
* @brief - configuration for dma
* @return void
**/
void DMA_config();

void DMA2_IRQHandler();


#endif
