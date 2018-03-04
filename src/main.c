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
#include "data_processing.h"
#include <unistd.h>
#ifdef KL25Z
#include "blink.h"

#endif

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
    char string[2000];
    printf("Enter String");
    scanf("%s",string);
    int j;
    cb_struct my_cb;
    cb_init(&my_cb,100);
    for (j = 0; string[j] != '\0'; j++) 
    {
        cb_buffer_add_item(&my_cb,string[j]);
    }
	data_process(&my_cb);
    
   

    return 0;
}

