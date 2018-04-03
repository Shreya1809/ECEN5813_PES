#include "dma.h"
#include "MKL25Z4.h"

void dma_clockenable()
{
	SIM->SCGC7 |= SIM_SCGC7_DMA(1);
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM->SOPT2 |= SIM_SOPT2_MCGFLLCLK_MASK;
}

void DMA_config()
{
	dma_clockenable();

	//Clear the CHCFG[ENBL] and CHCFG[TRIG] fields of the DMA channel
	DMAMUX0->CHCFG[0] = DMAMUX_CHCFG_ENBL(0) | DMAMUX_CHCFG_TRIG(0) ;

	// Clearing Source size and Destination size fields.
	DMA_DCR0 &= ~(DMA_DCR_SSIZE_MASK | DMA_DCR_DSIZE_MASK);

	// Enables the DMA channel and select the DMA Channel Source
	DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(2);

	NVIC_EnableIRQ(DMA2_IRQn);

	DMA_DCR0 |= DMA_DCR_EINT_MASK;
}

void DMA2_IRQHandler()
{

}
