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
	//initial values??
}


//Toggle the Red LED state. On to Off, or Off to on.
void Toggle_Red_LED()
{
	PTB->PTOR |= (1 << 18);
}

//These two functions should use the appropriate GPIO function to toggle the output (PSOR)
void PORTB_Set(uint8_t bit_num)
{
	PTB->PSOR |= (1 << bit_num); //port set output register for portB the given pin number
}
void PORTD_Set(uint8_t bit_num)
{
	PTD->PSOR |= (1 << bit_num);//port set output register for portD for the given pin number
}
//These two functions should use the appropriate GPIO function to toggle the output (PCOR)
void PORTB_Clear(uint8_t bit_num)
{
	PTB->PCOR  |= (1 << bit_num); //pin out clear for corresponding pin in port b
}
void PORTD_Clear(uint8_t bit_num)
{
	PTD->PCOR  |= (1 << bit_num); //pin out clear for corresponding pin in port d
}

//These two functions should use the appropriate GPIO function to toggle the output (PTOR)
void PORTB_Toggle(uint8_t bit_num)
{
	PTB->PTOR |= (1 << bit_num); //toggle port b pin bit_num
}
void PORTD_Toggle(uint8_t bit_num)
{
	PTD->PTOR |= (1 << bit_num);//toggle port b pin bit_num
}
