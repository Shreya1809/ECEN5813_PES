/**
 * @file circbuf.h
 * @brief circular buffer library
 * @author Shreya Chakraborty
 * @author Miles Frain
 * @version 1
 * @date 2018-02-21
 */

#ifndef __CIRCBUF_H__
#define __CIRCBUF_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Structure for maintaining handle to circular buffer.
 * Only supports items of 1-byte size.
 * Items added to position after head, and removed from tail.
 */
typedef struct
{
    int8_t* buffer; // Pointer to buffer in memory
    size_t size; // Total size of buffer
    size_t count; // Number of items in buffer
    int8_t* head; // Pointer to newest item added
    int8_t* tail; // Pointer to oldest item added
}cb_struct;

/**
 * @brief Status return codes for circular buffer functions
 */

typedef enum
{
    NULL_POINTER_ERROR,
    ALLOCATION_SUCCESS,
    ALLOCATION_FAILURE,
    DEALLOCATED,
    NO_LENGTH_ERROR,
    BUFFER_FULL,  //1
    BUFFER_FULL_ERROR,
    BUFFER_EMPTY, //1
    BUFFER_EMPTY_ERROR,
    BUFFER_NOT_EMPTY, //0
    BUFFER_NOT_FULL, //0
    WRAP_ADDITION,
    ADDITION_SUCCESSFUL,
    WRAP_REMOVAL,
    REMOVAL_SUCCESSFUL,
    POSITION_ERROR,
    SUCCESS,
}cb_enum;

/**
 * @brief Initialize circular buffer with 'length' bytes
 * Allocates dynamic memory, and populates struct.
 *
 * @param ptr Pointer to circular buf struct handle.
 * @param length Number of bytes to allocate in buffer
 *
 * @return CB status code
 */
cb_enum cb_init(cb_struct *ptr, size_t length);

/**
 * @brief Free circular buffer dynamic memory and reset struct fields
 *
 * @param ptr Pointer to circular buf struct handle
 *
 * @return CB status code
 */
cb_enum cb_destroy(cb_struct *ptr);

/**
 * @brief Adds byte to circular buffer after head.
 * If buffer is full, will not add item, and instead returns
 * CB_FULL_ERROR.
 *
 * @param ptr Pointer to circular buf struct handle
 * @param data_add Byte to add to buffer
 *
 * @return CB status code
 */
cb_enum cb_buffer_add_item(cb_struct *ptr, int8_t data_add);

/**
 * @brief Removes byte from tail of circular buffer.
 * If buffer is empty, will not populate data_remove pointer,
 * and will return CB_EMPTY_ERROR.
 *
 * @param ptr Pointer to circular buf struct handle
 * @param data_remove Pointer of where to write data removed.
 *
 * @return CB status code
 */
cb_enum cb_buffer_remove_item(cb_struct *ptr, int8_t data_remove);

/**
 * @brief Checks if circular buffer is full
 *
 * @param ptr Pointer to circular buf struct handle
 *
 * @return 1 if full, 0 if not full
 * Todo - what should we return if ptr is null?
 */
inline cb_enum cb_is_full(cb_struct *ptr)
{
   cb_enum status;
    if (ptr == NULL || ptr->head == NULL || ptr->tail == NULL || ptr->buffer == NULL) //check for null pointer
    {
        status = NULL_POINTER_ERROR;
    }
    else if((ptr->tail == ptr->head + 1) ||(ptr->head == ptr->tail + (ptr->size -1)) || (ptr->count == ptr->size)) // tail is 1 position ahead of header, buffer is full
    {
        status = BUFFER_FULL; //status = 1
    }
    else status = BUFFER_NOT_FULL ; //status = 0
    return status;

}


/**
 * @brief Checks if circular buffer is empty
 *
 * @param ptr Pointer to circular buf struct handle
 *
 * @return 1 if empty, 0 if not empty
 */
inline cb_enum cb_is_empty(cb_struct *ptr)
{
    cb_enum status;
    if (ptr == NULL || ptr->head == NULL || ptr->tail == NULL || ptr->buffer == NULL) //check for null pointer
    {
        status = NULL_POINTER_ERROR;
    }
    else if((ptr->count == 0) || (ptr ->tail == ptr->head)) //current item count in the buffer is 0 if buffer is empty
    {
        status = BUFFER_EMPTY ; //status = 1
    }
    else status = BUFFER_NOT_EMPTY ; // status = 0
    return status;
}
/**
 * @brief Shows an item at any position in circular buffer
 * without removing item from buffer. If position is not populated,
 * will return CB_POSITION_ERROR.
 *
 * @param ptr Pointer to circular buf struct handle
 * @param position Index from head of where to peek (head is index 0)
 * @param holder Pointer of where to write peeked item.
 *
 * @return CB status code
 */
cb_enum cb_peek(cb_struct *ptr, int8_t position, int8_t *data);

#endif // __CIRCBUF_H__
