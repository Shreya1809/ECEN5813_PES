/************************************************************
Authors:
Miles Frain & Shreya Chakraborty
Description:
source files for data.c for the following data functions
- print_cstd_type_sizes
- print_stdint_type_sizes
- print_pointer_sizes
- swap_data_endianness
- determine endianness
 **************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

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
#ifndef KL25Z
    printf("size of the integer a is %zu bytes", temp);
    temp = sizeof(b);
    printf("size of the character b is %zu bytes", temp);
    temp = sizeof(c);
    printf("size of the short c is %zu bytes", temp);
    temp = sizeof(d);
    printf("size of the long d is %zu bytes", temp);
    temp = sizeof(e);
    printf("size of the double e is %zu bytes", temp);
    temp = sizeof(f);
    printf("size of the float f is %zu bytes", temp);
    temp = sizeof(g);
    printf("size of the unsigned character g is %zu bytes", temp);
    temp = sizeof(h);
    printf("size of the unsigned integer h is %zu bytes", temp);
    temp = sizeof(i);
    printf("size of the unsigned long i is %zu bytes", temp);
    temp = sizeof(j);
    printf("size of the signed character j is %zu bytes", temp);
    temp = sizeof(k);
    printf("size of the signed integer k is %zu bytes", temp);
    temp = sizeof(l);
    printf("size of the signed long l is %zu bytes", temp);
#endif
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
#ifndef KL25Z
    printf("size of the int8_t a is %zu bytes", temp);
    temp = sizeof(b);
    printf("size of the uint8_t b is %zu bytes", temp);
    temp = sizeof(c);
    printf("size of the int16_t c is %zu bytes", temp);
    temp = sizeof(d);
    printf("size of the uint16_t d is %zu bytes", temp);
    temp = sizeof(e);
    printf("size of the int32_t e is %zu bytes", temp);
    temp = sizeof(f);
    printf("size of the uint32_t f is %zu bytes", temp);
    temp = sizeof(g);
    printf("size of the uint_fast8_t g is %zu bytes", temp);
    temp = sizeof(h);
    printf("size of the uint_fast16_t h is %zu bytes", temp);
    temp = sizeof(i);
    printf("size of the uint_fast32_t i is %zu bytes", temp);
    temp = sizeof(j);
    printf("size of the uint_least8_t  j is %zu bytes", temp);
    temp = sizeof(k);
    printf("size of the uint_least16_t  k is %zu bytes", temp);
    temp = sizeof(l);
    printf("size of the uint_least32_t  l is %zu bytes", temp);
    temp = sizeof(m);
    printf("size of the size_t  m is %zu bytes", temp);
    temp = sizeof(n);
    printf("size of the ptrdiff_t n is %zu bytes", temp);
#endif
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
#ifndef KL25Z
    printf("size of the  char ptr a is %zu bytes", temp);
    temp = sizeof(b);
    printf("size of the short ptr b is %zu bytes", temp);
    temp = sizeof(c);
    printf("size of the int ptr c is %zu bytes", temp);
    temp = sizeof(d);
    printf("size of the long ptr d is %zu bytes", temp);
    temp = sizeof(e);
    printf("size of the double ptr e is %zu bytes", temp);
    temp = sizeof(f);
    printf("size of the float ptr f is %zu bytes", temp);
    temp = sizeof(g);
    printf("size of the void ptr g is %zu bytes", temp);
    temp = sizeof(h);
    printf("size of the int8_t ptr h is %zu bytes", temp);
    temp = sizeof(i);
    printf("size of the int16_t ptr i is %zu bytes", temp);
    temp = sizeof(j);
    printf("size of the int32_t ptr  j is %zu bytes", temp);
    temp = sizeof(k);
    printf("size of the char double pointer  k is %zu bytes", temp);
    temp = sizeof(l);
    printf("size of the int double pointer  l is %zu bytes", temp);
    temp = sizeof(m);
    printf("size of the void double pointer  m is %zu bytes", temp);
#endif
}
/* function to determine the endianness */
uint32_t determine_endianness()
{
    unsigned int x = 0x01234567;
    char *c = (char*) &x;
#ifndef KL25Z
    printf ("*c is: 0x%x\n", *c);
    if (*c == 0x76)
    {
        printf ("little endian. \n");
        return LITTLE_ENDIANN;
    }
    else
    {
        printf ("big endian. \n");
        return BIG_ENDIANN;
    }
#endif
}

/*function to swap endianess*/
