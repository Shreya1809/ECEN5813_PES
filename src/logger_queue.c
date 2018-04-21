


#include "logger.h"
#include "logger_queue.h"


//function to fill the elements of log struct and store it
log_struct log_create(log_enum log_ID,log_enum module_ID, size_t log_Length, uint32_t * payload) 
{
		logStructFill.log_ID=log_ID;
		logStructFill.module_ID=module_ID;
		logStructFill.timestamp=getlogtime();
		logStructFill.log_Length=log_Length;
		logStructFill.payload=payload;
		logStructFill.checksum=getchecksum(logStructFill.log_ID,logStructFill.module_ID,logStructFill.timestamp,logStructFill.log_Length,logData.payload);
		return &logStructFill;
}
//to calculate checksum	-adds all the parameters
uint32_t getchecksum(log_enum log_ID,log_enum module_ID, uint32_t timestamp , size_t log_Length, uint32_t * payload)
{
	return ((uint32_t)log_ID+(uint32_t)module_ID+timestamp+(uint32_t)log_Length+(uint32_t)payload);
}

void log_print(log_struct *ptr); //prints the value for kl25z/bbb with ptr pointing to the buffer containing the data to be logged

