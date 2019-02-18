/*
 * data_generation_thread.c
 *
 * this is a thread that periodically generates some data and puts it in a 
 * mail queue
 *
 * author:    Dr. Alex Shenfield
 * date:      06/09/2018
 * purpose:   55-604481 embedded computer networks : lab 103
 */
 
// include cmsis_os for the rtos api
#include "cmsis_os.h"

// include main.h (this is where we initialise the mail type and queue)
#include "main.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "random_numbers.h"

// RTOS DEFINES

// declare the thread function prototypes, thread id, and priority
void data_thread(void const *argument);
osThreadId tid_data_thread;
osThreadDef(data_thread, osPriorityNormal, 1, 0);

// set up the mail queue
osMailQDef(mail_box, 16, mail_t);
osMailQId  mail_box;

// set up the blink queue
osMailQDef(blink_box, 5, blink_t);
osMailQId  blink_box;

// THREAD INITIALISATION

// create the data generation thread
int init_data_thread(void)
{
  // initialize random number generator
  init_random();
  
  // create the mailbox
  mail_box = osMailCreate(osMailQ(mail_box), NULL);
	
	// create the blinkbox
  blink_box = osMailCreate(osMailQ(blink_box), NULL);
  
  // create the thread and get its task id
  tid_data_thread = osThreadCreate(osThread(data_thread), NULL);
  
  // check if everything worked ...
  if(!tid_data_thread)
  {
    return(-1);
  }
  return(0);
}

// ACTUAL THREADS

// data generation thread - create some random data and stuff it in a mail 
// queue
void data_thread(void const *argument)
{
  // set up our counter
  uint32_t i = 0;
	int toggle = 0;
  
  // infinite loop generating our fake data (one set of samples per second)
  while(1)
  {
    // create our mail (i.e. the message container)   
    mail_t* mail = (mail_t*) osMailAlloc(mail_box, osWaitForever);
		
		// create our blink (i.e. the message container)   
    blink_t* blink = (blink_t*) osMailAlloc(blink_box, osWaitForever);
    
    // get a random number 
    float random = get_random_float();
    
    // generate our fake data
    i++;
    mail->counter = i;
    mail->current = (1.0f / (random * i)); 
    mail->voltage = (5.0f / (random * i));
		
		// make that blinky
		if (toggle == 1)
		{
			toggle = 0;
			blink->onoff = 1;
		}
		else
		{
			toggle = 1;
			blink->onoff = 0;
		}
    
    // put the data in the boxes and wait for one second
    osMailPut(mail_box, mail);
		osMailPut(blink_box, blink);
    osDelay(1000);
  }
} 
