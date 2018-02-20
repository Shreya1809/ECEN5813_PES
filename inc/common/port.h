
#ifndef PORT_H_
#define PORT_H_

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

void GPIO_Configure();
void Toggle_Red_LED();
void PORTB_Set(uint8_t bit_num);
void PORTD_Set(uint8_t bit_num);
void PORTB_Clear(uint8_t bit_num);
void PORTD_Clear(uint8_t bit_num);
void PORTB_Toggle(uint8_t bit_num);
void PORTD_Toggle(uint8_t bit_num);

#endif
