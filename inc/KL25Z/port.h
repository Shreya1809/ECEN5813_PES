/**
 * @file port.h
 * @brief Library for GPIO and LED management on KL25Z
 * @author Shreya Chakraborty
 * @author Miles Frain
 * @version 1
 * @date 2018-02-21
 */

#include <stdint.h>
#include <MKL25Z4.h>
#ifndef __PORT_H__
#define __PORT_H__

#define RGB_RED_PIN (18)
#define RGB_GREEN_PIN (19)
#define RGB_BLUE_PIN (1)

#define RGB_GREEN_ON() (PORTB_Clear( RGB_GREEN_PIN ))
#define RGB_GREEN_OFF() (PORTB_Set( RGB_GREEN_PIN ))
#define RGB_GREEN_TOGGLE() (PORTB_Toggle( RGB_GREEN_PIN ))

#define RGB_RED_ON() (PORTB_Clear( RGB_RED_PIN ))
#define RGB_RED_OFF() (PORTB_Set( RGB_RED_PIN ))
#define RGB_RED_TOGGLE() (PORTB_Toggle( RGB_RED_PIN ))

#define RGB_BLUE_ON() (PORTD_Clear( RGB_BLUE_PIN ))
#define RGB_BLUE_OFF() (PORTD_Set( RGB_BLUE_PIN ))
#define RGB_BLUE_TOGGLE() (PORTD_Toggle( RGB_BLUE_PIN ))

void GPIO_Configure();

static inline void Toggle_Red_LED()
{
	PTB->PTOR |= (1 << 18);
}

//These two functions should use the appropriate GPIO function to toggle the output (PSOR)
static inline void PORTB_Set(uint8_t bit_num)
{
	PTB->PSOR |= (1 << bit_num); //port set output register for portB the given pin number
}
static inline void PORTD_Set(uint8_t bit_num)
{
	PTD->PSOR |= (1 << bit_num);//port set output register for portD for the given pin number
}
//These two functions should use the appropriate GPIO function to toggle the output (PCOR)
static inline void PORTB_Clear(uint8_t bit_num)
{
	PTB->PCOR  |= (1 << bit_num); //pin out clear for corresponding pin in port b
}
static inline void PORTD_Clear(uint8_t bit_num)
{
	PTD->PCOR  |= (1 << bit_num); //pin out clear for corresponding pin in port d
}

//These two functions should use the appropriate GPIO function to toggle the output (PTOR)
static inline void PORTB_Toggle(uint8_t bit_num)
{
	PTB->PTOR |= (1 << bit_num); //toggle port b pin bit_num
}
static inline void PORTD_Toggle(uint8_t bit_num)
{
	PTD->PTOR |= (1 << bit_num);//toggle port b pin bit_num
}

#endif // __PORT_H__
