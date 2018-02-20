#ifndef __CIRCBUF_H__
#define __CIRCBUF_H__


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {

int8_t * head;
int8_t * tail;
size_t size;
int8_t count;
int8_t * buffer;

}CB_struct;

typedef enum {

 Success,
 CircBuff Null Pointer Error,
 No Length Error,
 Buffer Full Error,
 Buffer Empty Error,

}CB_enum;


CB_enum CB_init(CB_struct *ptr, int8_t length);
CB_enum CB_destroy(CB_struct *ptr);
CB_enum CB_buffer_add_item(CB_struct *ptr, int8_t data_add);
CB_enum CB_buffer_remove_item(CB_struct *ptr, int8_t data_remove);
CB_enum CB_is_full(CB_struct *ptr);
CB_enum CB_is_empty(CB_struct *ptr);
CB_enum CB_peek(CB_struct *ptr, int8_t position, int8_t holder);

#endif 

