


#include "logger.h"
#include "logger_queue.h"
#include "platform.h"
#include "memory.h"



//function to fill the elements of log struct and store it
log_struct * log_create(log_enum log_ID,log_enum module_ID, size_t log_Length, uint32_t * payload) 
{
		logStructFill->log_ID=log_ID;
		logStructFill->module_ID=module_ID;
		logStructFill->timestamp=getlogtime();
		logStructFill->log_Length=log_Length;
		logStructFill->payload=payload;
		logStructFill->checksum=getchecksum(logStructFill->log_ID,logStructFill->module_ID,logStructFill->timestamp,logStructFill->log_Length,logStructFill->payload);
		return logStructFill;
}
//to calculate checksum	-adds all the parameters
uint32_t getchecksum(log_enum log_ID,log_enum module_ID, uint32_t timestamp , size_t log_Length, uint32_t * payload)
{
	return ((uint32_t)log_ID+(uint32_t)module_ID+timestamp+(uint32_t)log_Length+(uint32_t)payload);
}

void log_print(log_struct *logval_ptr) //prints the value for kl25z/bbb with ptr pointing to the buffer containing the data to be logged
{

	LOG_RAW_STRING(" LOG ID - ");
	LOG_RAW_STRING(logID_show[logval_ptr->log_ID]);
	LOG_RAW_STRING(" TIME - ");
	LOG_RAW_INT(logval_ptr->timestamp);
		if(logval_ptr->payload ==NULL || logval_ptr->log_Length <1)
		{
			LOG_RAW_STRING(" IS WITHOUT ANY PAYLOAD ");
			//LOG_RAW_STRING("\n\r");
		}
		else 
		{
			LOG_RAW_STRING(" IS WITH PAYLOAD - ");
			LOG_RAW_DATA(logval_ptr->payload,(logval_ptr->log_Length));
			//LOG_RAW_STRING("\n\r");
		}
		
		if(getchecksum(logval_ptr->log_ID,logval_ptr->module_ID,logval_ptr->timestamp,logval_ptr->log_Length,logval_ptr->payload)==logval_ptr->checksum) 
		{
		LOG_RAW_STRING("WITH CORRECT CHECKSUM");
		}
		else LOG_RAW_STRING("WITH INCORRECT CHECKSUM");
		LOG_RAW_STRING("\n\r");
	
}
void log_flush_BBB(CB_log_struct* src_ptr)//Blocks until the current logger buffer is empty
{
	log_struct data;
	while(log_cb_is_empty(src_ptr)!=1)
	{
		log_cb_remove(&data,src_ptr);
		printf("%d",data);
	}	
}

//modiflied circuf functions for logging
cb_enum log_cb_init(CB_log_struct* src_ptr, size_t length)
{
	cb_enum status= CB_SUCCESS;
    if (src_ptr == NULL )  //check for null and negative length
    {
        status = CB_NULL_ERROR;
    }
    else if (length <= 0)
    {
        status = CB_LENGTH_ERROR;
    }
    else
    {
        src_ptr -> buffer = malloc(length * sizeof(int8_t)); // allocates the length no of items for the buffer memory
        if(src_ptr -> buffer == NULL)
        {//reinitialise size to 0, current item count in the buffer to 0, head and tail to null
            src_ptr->size = 0;
            src_ptr->head = NULL;
            src_ptr->tail = NULL;
            src_ptr->count = 0;
            status = CB_ALLOCATION_FAILURE;
	    log_cb_add(log_create(LOG_ERROR,LOG_ERROR,0,NULL),logger_queue);
        }
        else
        { //initialise size to given length, current item count in the buffer to 0, head and tail to null
            src_ptr->size = length;
            src_ptr->head = src_ptr->buffer;
            src_ptr->tail = src_ptr->buffer;
            src_ptr->count = 0;
            my_memzero((uint8_t*)src_ptr->buffer, length);
            status = CB_SUCCESS;
        }
    }
    return status;
}

cb_enum log_cb_add(log_struct *logval_ptr, CB_log_struct *src_ptr)
{
	BEGIN_CRITICAL;
    cb_enum status = CB_SUCCESS;
    if (logval_ptr == NULL || src_ptr-> head == NULL || src_ptr->tail == NULL || src_ptr->buffer == NULL) //check for null pointer
    {
        status = CB_NULL_ERROR;
    }
    else if (log_cb_is_full(src_ptr) == 1)
    {
	//do log_flush
        status = CB_FULL_ERROR;
    }
    else if(src_ptr->head == src_ptr->buffer + src_ptr->size -1 ) //wrap around situation, head to wrap around to base when at the end
    {
        *(src_ptr->head) = *logval_ptr;
        src_ptr->head = src_ptr->buffer;
        src_ptr->count++;
        status = CB_SUCCESS;
    }
    else
    {// buffer has empty spaces, hence increment the head to the next buffer location
        *src_ptr->head = *logval_ptr;
        src_ptr->head++;
        src_ptr->count++;
        status = CB_SUCCESS;
    }
    END_CRITICAL;
    return status;
}
cb_enum log_cb_remove(log_struct *logval_ptr , CB_log_struct* src_ptr)
{
	BEGIN_CRITICAL;
    cb_enum status = CB_SUCCESS;
    if (logval_ptr == NULL || src_ptr->head == NULL || src_ptr->tail == NULL || src_ptr->buffer == NULL) //check for null pointer
    {
        status = CB_NULL_ERROR;
    }

    if (log_cb_is_empty(src_ptr))
    {
        status = CB_EMPTY_ERROR;
    }
    else
    {
        if(src_ptr->tail == src_ptr->buffer + src_ptr->size -1) //wrap around situation, tail to wrap around to base when at the end
        {
            *logval_ptr = *(src_ptr->tail);
            //*(src_ptr->tail) = 0;
            src_ptr->tail = src_ptr-> buffer;
            src_ptr->count--;
            status = CB_SUCCESS;
        }
        else
        {// buffer has full spaces, hence increment the tail to the next buffer location
            *logval_ptr = *(src_ptr->tail);
            //*(src_ptr->tail) = 0;
            src_ptr->tail++;
            src_ptr->count--;
            status = CB_SUCCESS;
        }
    }
    END_CRITICAL;
    return status;
}


cb_enum log_cb_is_full(CB_log_struct* src_ptr)//make this attribute (always inline)
{
	if (src_ptr == NULL || src_ptr->head == NULL || src_ptr->tail == NULL || src_ptr->buffer == NULL) //check for null pointer
    {
	log_cb_add(log_create(LOG_ERROR,LOG_ERROR,0,NULL),logger_queue);
        return -1; // Evaluates to True / Full
    }
    else if ((src_ptr->tail == src_ptr->head + 1) || (src_ptr->count == src_ptr->size)) // tail is 1 position ahead of header, buffer is full
    //else if (0)
    {
        return 1; // Full
    }
    return 0; // Not Full
}

cb_enum log_cb_is_empty(CB_log_struct* src_ptr)//make this attribute (always inline)
{
	if (src_ptr == NULL || src_ptr->head == NULL || src_ptr->tail == NULL || src_ptr->buffer == NULL) //check for null pointer
    {
	log_cb_add(log_create(LOG_ERROR,LOG_ERROR,0,NULL),logger_queue);
        return -1; // Evaluates to True / Empty
    }
    else if((src_ptr->count == 0) && (src_ptr->tail == src_ptr->head)) //current item count in the buffer is 0 if buffer is empty
    {
        return 1; // Empty
    }
    return 0; // Not empty
}

