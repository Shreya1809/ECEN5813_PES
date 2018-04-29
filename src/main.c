/**
 * @file main.c
 * @brief Main program entry point
 * @author Miles Frain
 * @author Shreya Chakraborty
 * @version 1
 * @date 2018-02-10
 */
#include "project1.h"
#include "logger.h"
#include "malloc.h"
#include "profiler.h"
#include "conversion.h"
#include "data.h"
#include "platform.h"
#include "data_processing.h"
#include "circbuf.h"
#include "logger_queue.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef KL25Z
#include "uart.h"
#include "clock.h"
#include "port.h"
#include "rtc.h"
//#include "profiler.h"
#include "nordic.h"
#include "dma.h"
// Not sure exactly what state SystemInit() leaves the device in with CLOCK_SETUP
// TODO - check register differences
#define CLOCK_SETUP 1


#endif

extern cb_struct *rx_buffer;
extern cb_struct *tx_buffer;
log_struct_t  *logged_data;





int main()
{
#if defined PROJECT2 || defined PROJECT3
#ifdef KL25Z

	clock_setup();
    UART_configure(BAUD_115200);

    rtc_config();
    cb_struct BUFF[20];
    rx_buffer = &BUFF[0];
   // rx_buffer = (cb_struct *)malloc(sizeof(cb_struct)); //statically allocate buffer
    	    cb_enum status = cb_init(rx_buffer, 256);
    	    if (status != CB_SUCCESS)
    	    {
    		   PRINTF("Error initializing rx buffer\n");
    	    }
	tx_buffer = (cb_struct *)malloc(sizeof(cb_struct));
			cb_enum mystatus = cb_init(tx_buffer, 300);
			if (mystatus != CB_SUCCESS)
			{
			   PRINTF("Error initializing tx buffer\n");
			}
    	    PRINTF("\nStarting Project 4\n");
		PRINTF("PRESS SPACEBAR TO DISPLAY DATA ANALYSIS, ESC TO DISPLAY LOGGER DATA ANALYSIS\n ");
		logged_data = (log_struct_t *) malloc(sizeof(log_struct_t));
		log_create(logged_data, SYSTEM_ID,MAIN, 20,(uint8_t *)"SYSTEM ID WINDOWS 10");
		LOG_RAW_ITEM(tx_buffer, logged_data);
		LOG_FLUSH(tx_buffer);
		log_create(logged_data, LOGGER_INITIALZED,MAIN, 1,(uint8_t*)"0");
		LOG_RAW_ITEM(tx_buffer, logged_data);
		LOG_FLUSH(tx_buffer);
    	log_create(logged_data, SYSTEM_INITIALIZED,MAIN, 1,(uint8_t*)"0");
	    LOG_RAW_ITEM(tx_buffer, logged_data);
		LOG_FLUSH(tx_buffer);
	    log_create(logged_data, SYSTEM_VERSION,MAIN, 37,(uint8_t *)"KINETICS DESIGN STUDIO VERSION 3.2.0");
	    LOG_RAW_ITEM(tx_buffer, logged_data);
		LOG_FLUSH(tx_buffer);

    	 GPIO_Configure();
    	 systick_init();
    	  SPI_init();


#else  // platform not KL25Z
    cb_struct *rx_buffer;
    cb_struct *tx_buffer;// defined by uart otherwise
    if(rx_buffer); // Avoid unused build error for now
#endif // platform


#ifdef PROJECT3
   // PRINTF("\nProject 3 print\n");
#ifdef KL25Z
    DMA_config();
    log_create(logged_data, PROFILING_STARTED,PROFILER, 1,(uint8_t *)1);
    LOG_RAW_ITEM(tx_buffer, logged_data);
	LOG_FLUSH(tx_buffer);
    kl25z_profile_option(MEMMOVE_DMA);
	kl25z_profile_option(MEMSET_DMA);
	kl25z_profile_option(MY_MEMMOVE);
	kl25z_profile_option(MY_MEMSET);
	kl25z_profile_option(MEMMOVE);
	kl25z_profile_option(MEMSET);
	log_create(logged_data, PROFILING_COMPLETED,PROFILER, 1,(uint8_t *)1);
	LOG_RAW_ITEM(tx_buffer, logged_data);
	LOG_FLUSH(tx_buffer);

	log_create(logged_data, INFO,MAIN, 25,(uint8_t *)"NORDIC CHIP NOT CONNECTED");
	LOG_RAW_ITEM(tx_buffer, logged_data);
	LOG_FLUSH(tx_buffer);
	//nordic_test();
	log_create(logged_data, WARNING,MAIN, 12,(uint8_t *)"SPI TEST FAIL");
	LOG_RAW_ITEM(tx_buffer, logged_data);
	LOG_FLUSH(tx_buffer);
	log_create(logged_data, DATA_ANALYSIS_STARTED,DATA_PROCESSIING, 1,(uint8_t *)1);
	LOG_RAW_ITEM(tx_buffer, logged_data);
	LOG_FLUSH(tx_buffer);

	while (1)
		{
			if (!cb_is_empty(rx_buffer))
			{
				//data_process(rx_buffer);

				RGB_RED_TOGGLE();
			}

		}


#else
	cb_struct BUFF[100];
	    rx_buffer = &BUFF[0];
	   // rx_buffer = (cb_struct *)malloc(sizeof(cb_struct)); //statically allocate buffer
	    	    cb_enum status = cb_init(rx_buffer, 256);
	    	    if (status != CB_SUCCESS)
	    	    {
	    		   printf("Error initializing rx buffer\n");
	    	    }
		tx_buffer = (cb_struct *)malloc(sizeof(cb_struct));
				cb_enum mystatus = cb_init(tx_buffer, 2000);
				if (mystatus != CB_SUCCESS)
				{
				   printf("Error initializing tx buffer\n");
				}
	    	    printf("\nStarting Project 4\n");
	    	    printf("PRESS SPACEBAR TO DISPLAY DATA ANALYSIS, ESC TO DISPLAY LOGGER DATA ANALYSIS\n ");
	//uint8_t * ptr = NULL;
	logged_data = (log_struct_t *) malloc(sizeof(log_struct_t));
	log_create(logged_data, SYSTEM_ID,MAIN, 20,(uint8_t *)"SYSTEM ID WINDOWS 10");
	LOG_RAW_ITEM(tx_buffer, logged_data);
	LOG_FLUSH(tx_buffer);
	log_create(logged_data, LOGGER_INITIALZED,MAIN, 1,(uint8_t*)"0");
	LOG_RAW_ITEM(tx_buffer, logged_data);
	LOG_FLUSH(tx_buffer);
	log_create(logged_data, SYSTEM_INITIALIZED,MAIN, 1,(uint8_t*)"0");
	LOG_RAW_ITEM(tx_buffer, logged_data);
	LOG_FLUSH(tx_buffer);
	log_create(logged_data, SYSTEM_VERSION,MAIN, 37,(uint8_t *)"KINETICS DESIGN STUDIO VERSION 3.2.0");
	LOG_RAW_ITEM(tx_buffer, logged_data);
	LOG_FLUSH(tx_buffer);
	log_create(logged_data, PROFILING_STARTED,PROFILER, 1, (uint8_t*)"0");
	LOG_RAW_ITEM(tx_buffer, logged_data);
	LOG_FLUSH(tx_buffer);
    bbb_profile_option(1);
    bbb_profile_option(2);
    bbb_profile_option(3);
    bbb_profile_option(4);
	//bbb_profile_option(5);
    log_create(logged_data, PROFILING_COMPLETED,PROFILER, 1,(uint8_t *)"0");
    LOG_RAW_ITEM(tx_buffer, logged_data);
	//log_flush_BBB(tx_buffer);

    char string[2000];
       while (1)
       {

          
           log_create(logged_data, DATA_ANALYSIS_STARTED,DATA_PROCESSIING, 1,(uint8_t *)"0");
           LOG_RAW_ITEM(tx_buffer, logged_data);
	   printf("\nEnter String: ");scanf("%s", &string);
        //    if(scanf("%s", &string))
		// perror("error enetring string");
           for (int j = 0; string[j] != '\0'; j++)
           {
               cb_buffer_add_item(rx_buffer, string[j]);
        	   data_statistics(string[j]);
           }
           //data_process(rx_buffer);
           int inval;
           printf("Enter option 1 to display data analysis, 2 to display log data analysis : ");
           //if(scanf("%d", &inval) != 1)
		//perror("error");
		scanf("%d", &inval);
           if(inval == 1 )
        	   print_data_entered();
           else if (inval == 2 )
        	   print_all_log();
			else if (inval == 3)
				log_flush_BBB(tx_buffer);
           else printf("invalid input");


       }
#endif // platform
#endif // project 3

#ifdef PROJECT2
    print_data_process_header();

#ifdef KL25Z
    while (1)
    {
        if (!cb_is_empty(rx_buffer))
        {
            data_process(rx_buffer);

            RGB_RED_TOGGLE();
        }
    }
#else  // HOST or BBB
    char string[2000];
    while (1)
    {
        printf("\nEnter String: ");
        scanf("%s", string);
        for (int j = 0; string[j] != '\0'; j++)
        {
            cb_buffer_add_item(rx_buffer, string[j]);
        }
        data_process(rx_buffer);
    }
#endif // platform
#endif // PROJECT2

#endif // project 2 or 3

#ifdef PROJECT1
    project1();
    print_cstd_type_sizes();
    print_stdint_type_sizes();
    print_pointer_sizes();
    uint32_t i = 0x12345678;
    PRINTF("pre swap 0x%lx\n", i);
    determine_endianness();
    swap_data_endianness((uint8_t *)&i, sizeof(i));
    PRINTF("post swap 0x%lx\n", i);
#endif
    log_create(logged_data, SYSTEM_HALTED,MAIN, 1,(uint8_t *)1);
    LOG_RAW_ITEM(tx_buffer, logged_data);
    return 0;
}
