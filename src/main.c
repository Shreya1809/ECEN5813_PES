/**
 * @file main.c
 * @brief source file for main.c
 * @author Miles Frain
 * @author Shreya Chakraborty
 * @version 1
 * @date 2018-02-10
 */
#include "project1.h"
#include "data.h"
#include "platform.h"
#include "blink.h"

int main()
{
    blink();
}
#if 0
int main()
{
#ifdef KL25Z
    blink();
#endif
#ifdef PROJECT1
    project1();
    print_cstd_type_sizes();
    print_stdint_type_sizes();
    print_pointer_sizes();
    uint32_t i = 0x12345678;
    PRINTF("pre swap 0x%x\n", i);
    determine_endianness();
    swap_data_endianness((uint8_t*)&i, sizeof(i));
    PRINTF("post swap 0x%x\n", i);
#endif
}
#endif

