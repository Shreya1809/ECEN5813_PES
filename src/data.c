/**
 * @file data.c
 * @brief source files for data.c
 * @author Miles Frain
 * @author Shreya Chakraborty
 * @version 1
 * @date 2018-02-10
 */

#if defined (__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include "memory.h"
#include "platform.h"

#define LITTLE_ENDIANN  (0)
#define BIG_ENDIANN     (1)
#define SWAP_NO_ERROR  (0)
#define SWAP_ERROR    (-1)

/*reports on the type sizes of cstd*/
void print_cstd_type_sizes()
{
    int a;
    char b;
    short c;
    long d;
    double e;
    float f;
    unsigned char g;
    unsigned int h;
    unsigned long i;
    signed char j;
    signed int k;
    signed long l;

    size_t temp = 0; //stores size of each variable

    temp = sizeof(a);
    PRINTF("size of the integer a is %zu bytes\n", temp);
    temp = sizeof(b);
    PRINTF("size of the character b is %zu bytes\n", temp);
    temp = sizeof(c);
    PRINTF("size of the short c is %zu bytes\n", temp);
    temp = sizeof(d);
    PRINTF("size of the long d is %zu bytes\n", temp);
    temp = sizeof(e);
    PRINTF("size of the double e is %zu bytes\n", temp);
    temp = sizeof(f);
    PRINTF("size of the float f is %zu bytes\n", temp);
    temp = sizeof(g);
    PRINTF("size of the unsigned character g is %zu bytes\n", temp);
    temp = sizeof(h);
    PRINTF("size of the unsigned integer h is %zu bytes\n", temp);
    temp = sizeof(i);
    PRINTF("size of the unsigned long i is %zu bytes\n", temp);
    temp = sizeof(j);
    PRINTF("size of the signed character j is %zu bytes\n", temp);
    temp = sizeof(k);
    PRINTF("size of the signed integer k is %zu bytes\n", temp);
    temp = sizeof(l);
    PRINTF("size of the signed long l is %zu bytes\n", temp);
}

/*reports on the type sizes of stdint*/
void print_stdint_type_sizes()
{
    int8_t a;
    uint8_t b;
    int16_t c;
    uint16_t d;
    int32_t e;
    uint32_t f;
    uint_fast8_t g;
    uint_fast16_t h;
    uint_fast32_t i;
    uint_least8_t j;
    uint_least16_t k;
    uint_least32_t l;
    size_t m;
    ptrdiff_t n;

    size_t temp = 0; //stores size of each variable

    temp = sizeof(a);
    PRINTF("size of the int8_t a is %zu bytes\n", temp);
    temp = sizeof(b);
    PRINTF("size of the uint8_t b is %zu bytes\n", temp);
    temp = sizeof(c);
    PRINTF("size of the int16_t c is %zu bytes\n", temp);
    temp = sizeof(d);
    PRINTF("size of the uint16_t d is %zu bytes\n", temp);
    temp = sizeof(e);
    PRINTF("size of the int32_t e is %zu bytes\n", temp);
    temp = sizeof(f);
    PRINTF("size of the uint32_t f is %zu bytes\n", temp);
    temp = sizeof(g);
    PRINTF("size of the uint_fast8_t g is %zu bytes\n", temp);
    temp = sizeof(h);
    PRINTF("size of the uint_fast16_t h is %zu bytes\n", temp);
    temp = sizeof(i);
    PRINTF("size of the uint_fast32_t i is %zu bytes\n", temp);
    temp = sizeof(j);
    PRINTF("size of the uint_least8_t  j is %zu bytes\n", temp);
    temp = sizeof(k);
    PRINTF("size of the uint_least16_t  k is %zu bytes\n", temp);
    temp = sizeof(l);
    PRINTF("size of the uint_least32_t  l is %zu bytes\n", temp);
    temp = sizeof(m);
    PRINTF("size of the size_t  m is %zu bytes\n", temp);
    temp = sizeof(n);
    PRINTF("size of the ptrdiff_t n is %zu bytes\n", temp);
}

/*reports on the type sizes of pointers*/
void print_pointer_sizes()
{
    char *a;
    short *b;
    int *c;
    long *d;
    double *e;
    float *f;
    void *g;
    int8_t *h;
    int16_t *i;
    int32_t *j;
    char **k;
    int **l;
    void **m;

    size_t temp = 0; //stores size of each variable

    temp = sizeof(a);
    PRINTF("size of the  char ptr a is %zu bytes\n", temp);
    temp = sizeof(b);
    PRINTF("size of the short ptr b is %zu bytes\n", temp);
    temp = sizeof(c);
    PRINTF("size of the int ptr c is %zu bytes\n", temp);
    temp = sizeof(d);
    PRINTF("size of the long ptr d is %zu bytes\n", temp);
    temp = sizeof(e);
    PRINTF("size of the double ptr e is %zu bytes\n", temp);
    temp = sizeof(f);
    PRINTF("size of the float ptr f is %zu bytes\n", temp);
    temp = sizeof(g);
    PRINTF("size of the void ptr g is %zu bytes\n", temp);
    temp = sizeof(h);
    PRINTF("size of the int8_t ptr h is %zu bytes\n", temp);
    temp = sizeof(i);
    PRINTF("size of the int16_t ptr i is %zu bytes\n", temp);
    temp = sizeof(j);
    PRINTF("size of the int32_t ptr  j is %zu bytes\n", temp);
    temp = sizeof(k);
    PRINTF("size of the char double pointer  k is %zu bytes\n", temp);
    temp = sizeof(l);
    PRINTF("size of the int double pointer  l is %zu bytes\n", temp);
    temp = sizeof(m);
    PRINTF("size of the void double pointer  m is %zu bytes\n", temp);
}
/* function to determine the endianness */
uint32_t determine_endianness()
{
    unsigned int x = 0x01234567;
    char *c = (char*) &x;
    PRINTF ("*c is: 0x%x\n", *c);
    if (*c == 0x67)
    {
        PRINTF("little endian. \n");
        return LITTLE_ENDIANN;
    }
    else
    {
        PRINTF("big endian. \n");
        return BIG_ENDIANN;
    }
}

/*function to swap endianess*/
int32_t swap_data_endianness(uint8_t * data, size_t type_length)
{
    if(my_reverse(data, type_length)) //changing the order of bytes
    {
        return SWAP_NO_ERROR;
    }
    else
    {
        return SWAP_ERROR;
    }
}
