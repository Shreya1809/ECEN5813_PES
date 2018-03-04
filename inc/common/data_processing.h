#include <stdio.h>
#include <stdint.h>
#include "conversion.h"
#include "circbuf.h"

#define ALPHANUMERIC_A   (65)
#define ALPHANUMERIC_Z	 (90)
#define alphanumeric_a	(97)
#define alphanumeric_z	(122)
#define number_0		(48)
#define number_9		(57)


uint8_t alphabetical(uint8_t value); // to check if alphabet

uint8_t numberical(uint8_t value);// to check if number

uint8_t punctuation(uint8_t value); // to check if punctuation

void data_process();

