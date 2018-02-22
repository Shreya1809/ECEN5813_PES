/**
 * @file port.h
 * @brief Library for GPIO and LED management on KL25Z
 * @author Shreya Chakraborty
 * @author Miles Frain
 * @version 1
 * @date 2018-02-21
 */

/* Todo Questions
 *
 * port.h or gpio.h? - gpio.h, led.h
 * toggle_red_led is redundant compared to macro
 * macros are likely more efficient than functions
 * "static" inline not necessary, since we aren't using local static vars in these functions
 */

#ifndef __PORT_H__
#define __PORT_H__

#define RGB_RED_PIN (???)
#define RGB_GREEN_PIN (???)
#define RGB_BLUE_PIN (???)

#define RGB_GREEN_ON() (PORTB_Set( RGB_GREEN_PIN ))
#define RGB_GREEN_OFF() (PORTB_Clear( RGB_GREEN_PIN ))
#define RGB_GREEN_TOGGLE() (PORTB_Toggle( RGB_GREEN_PIN ))

#define RGB_RED_ON() (PORTB_Set( RGB_RED_PIN ))
#define RGB_RED_OFF() (PORTB_Clear( RGB_RED_PIN ))
#define RGB_RED_TOGGLE() (PORTB_Toggle( RGB_RED_PIN ))

#define RGB_BLUE_ON() (PORTB_Set( RGB_BLUE_PIN ))
#define RGB_BLUE_OFF() (PORTB_Clear( RGB_BLUE_PIN ))
#define RGB_BLUE_TOGGLE() (PORTB_Toggle( RGB_BLUE_PIN ))

inline void GPIO_Configure();
inline void Toggle_Red_LED(); // Todo redundant compared to macro?
inline void PORTB_Set(uint8_t bit_num);
inline void PORTD_Set(uint8_t bit_num);
inline void PORTB_Clear(uint8_t bit_num);
inline void PORTD_Clear(uint8_t bit_num);
inline void PORTB_Toggle(uint8_t bit_num);
inline void PORTD_Toggle(uint8_t bit_num);

#endif // __PORT_H__
