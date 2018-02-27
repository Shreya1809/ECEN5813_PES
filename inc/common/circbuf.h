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
#include "malloc.h"

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
    CB_SUCCESS, // no error
    CB_NULL_ERROR, // if any pointer parameter is null
    CB_LENGTH_ERROR, // if attempting to initialize with zero length
    CB_FULL_ERROR, // if attempting to add to full buffer
    CB_EMPTY_ERROR, // if attempting to remove from empty buffer
    CB_POSITION_ERROR, // if attempting to peek at invalid position
    CB_ALLOCATION_FAILURE, // if malloc fails
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
static inline int cb_is_full(cb_struct *ptr)
{
    if (ptr == NULL || ptr->head == NULL || ptr->tail == NULL || ptr->buffer == NULL) //check for null pointer
    {
        // TODO
        return -1; // Evaluates to True / Full
    }
    else if((ptr->tail == ptr->head + 1) || (ptr->count == ptr->size)) // tail is 1 position ahead of header, buffer is full
    {
        return 1; // Full
    }
    return 0; // Not Full
}


/**
 * @brief Checks if circular buffer is empty
 *
 * @param ptr Pointer to circular buf struct handle
 *
 * @return 1 if empty, 0 if not empty
 */
static inline int cb_is_empty(cb_struct *ptr)
{
    if (ptr == NULL || ptr->head == NULL || ptr->tail == NULL || ptr->buffer == NULL) //check for null pointer
    {
        return -1; // Evaluates to True / Empty
    }
    else if((ptr->count == 0) && (ptr ->tail == ptr->head)) //current item count in the buffer is 0 if buffer is empty
    {
        return 1; // Empty
    }
    return 0; // Not empty
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
