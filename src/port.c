#include "port.h"
#include"MKL25Z4.h"

//Configures the RGB LEDs to be output with their initial values.
void GPIO_Configure()
{
	SIM_SCGC5 |= 0x00000400; //enable clock gating control for PORT B
	SIM_SCGC5 |= 0x00001000; //enable clock gating control for PORT D
	PTB->PDDR |= 0x00040000;//port B pin 18 RGB led red, set direction as output
	PTB->PDDR |= 0x00080000;//port B pin 19 RGB led green, set direction as output
	PTD->PDDR |= 0x00000002;//port D pin 1 RGB led blue, set direction as output
	SIM_SCGC5 |= SIM_SCGC5_PORTB(1);
	PORTB->PCR[18] |=(1 << 8);
	PORTB->PCR[19] |=(1 << 8);
	PORTD->PCR[1] |=(1 << 8);
	RGB_RED_OFF();
	RGB_GREEN_OFF();
	RGB_BLUE_OFF();
}

