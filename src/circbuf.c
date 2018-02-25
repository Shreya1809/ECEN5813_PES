
#include <circbuf.h>
#include <stdio.h>
#include <stdint.h>
#include <memory.h>

#define START_CRITICAL()
#define END_CRITICAL()

/*initialisation and allocation of dynamic memory*/
cb_enum cb_init(cb_struct *ptr, size_t length)
{
    cb_enum status;
    if (ptr == NULL )  //check for null and negative length
    {
        status = NULL_POINTER_ERROR;
    }
    else if (length <= 0)
    {
        status = NO_LENGTH_ERROR;
    }
    else
    {
        ptr -> buffer = (int8_t *)malloc(length * sizeof(int8_t)); // allocates the length no of items for the buffer memory
        if(ptr -> buffer == NULL)
        {//reinitialise size to 0, current item count in the buffer to 0, head and tail to null
            ptr->size = 0;
            ptr->head = NULL;
            ptr->tail = NULL;
            ptr->count = 0;
            status = ALLOCATION_FAILURE;
        }
        else
        { //initialise size to given length, current item count in the buffer to 0, head and tail to null
            ptr->size = length;
            ptr->head = ptr->buffer;
            ptr->tail = ptr->buffer;
            ptr->count = 0;
            my_memzero((uint8_t*)ptr->buffer, length);
            status = ALLOCATION_SUCCESS;
        }
    }
    return status;
}


/*The functions takes in a pointer to the circular buffer to be destroyed by deallocating using free*/
cb_enum cb_destroy(cb_struct *ptr)
{
    cb_enum status;
    if (ptr == NULL) //check for null pointer
    {
        status = NULL_POINTER_ERROR;
    }
    else
    {
        if (ptr ->buffer != NULL) //check if pointer not null
        {
            free(ptr->buffer); //deallocate the memory
            ptr->buffer = NULL; //make pointer null
        }
        ptr->size = 0;
        ptr->head = NULL;
        ptr->tail = NULL;
        ptr->count = 0;
        status = DEALLOCATED;
    }
    return status;

}

/*function to add items to the buffer*/
cb_enum cb_buffer_add_item(cb_struct *ptr, int8_t data_add)
{
    cb_enum status = SUCCESS;
    if (ptr == NULL || ptr->head == NULL || ptr->tail == NULL || ptr->buffer == NULL) //check for null pointer
    {
        status = NULL_POINTER_ERROR;
    }
    else if (status == ALLOCATION_FAILURE || status == BUFFER_FULL)
    {
        status = BUFFER_FULL_ERROR;
    }
    else if(ptr->head == ptr->buffer + ptr->size -1) //wrap around situation, head to wrap around to base when at the end
    {
        *(ptr->head) = data_add;
        ptr->head = ptr->buffer;
        ptr->count++;
        status = WRAP_ADDITION;
    }
    else
    {// buffer has empty spaces, hence increment the head to the next buffer location
        *ptr->head = data_add;
        ptr->head++;
        ptr->count++;
        status = ADDITION_SUCCESSFUL;
    }
    return status;

}

/*function to remove items from buffer*/
cb_enum cb_buffer_remove_item(cb_struct *ptr, int8_t data_remove)
{
    cb_enum status = SUCCESS;
    if (ptr == NULL || ptr->head == NULL || ptr->tail == NULL || ptr->buffer == NULL) //check for null pointer
    {
        status = NULL_POINTER_ERROR;
    }
    else if (status == DEALLOCATED || status == BUFFER_EMPTY)
    {
        status = BUFFER_EMPTY_ERROR;
    }
    else if(ptr->tail == ptr->buffer + ptr->size -1) //wrap around situation, tail to wrap around to base when at the end
    {
        *(ptr->tail) = data_remove;
        ptr->tail = ptr-> buffer;
        ptr->count--;
        status = WRAP_REMOVAL;
    }
    else
    {// buffer has full spaces, hence increment the tail to the next buffer location
        *ptr-> tail = data_remove;
        ptr->tail++;
        ptr->count--;
        status = REMOVAL_SUCCESSFUL;
    }
    return status;
}

/*function to peek into buffer*/
cb_enum cb_peek(cb_struct *ptr, int8_t position, int8_t *data)
{
    cb_enum status = SUCCESS;
    if (ptr == NULL || ptr->head == NULL || ptr->tail == NULL || ptr ->buffer == NULL || data == NULL) //check for null pointer
    {
        status = NULL_POINTER_ERROR;
    }
    else if (status == DEALLOCATED || status == BUFFER_EMPTY)
    {
        status = BUFFER_EMPTY_ERROR;
    }
    else if (position <= 0 || position > ptr->size)
    {
        status =  POSITION_ERROR;
    }

    else
    {
        *data = *( ptr->buffer + position );
        status = SUCCESS;
    }
    return status;
}













