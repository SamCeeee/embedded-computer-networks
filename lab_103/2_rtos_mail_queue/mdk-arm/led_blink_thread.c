/*
 * led_blink_thread.c
 *
 * this is a thread that periodically blinks LEDs 
 *
 * author:    Mr. Sam Carswell
 * date:      06/12/2018
 * purpose:   55-604481 embedded computer networks : lab 103
 */
 
 /* INCLUDES */
 
 //include cmsis for the rtos api
 #include "cmsis_os.h"
 
 // include main.h (this is where we initialise the mail type)
#include "main.h"
 
 // include the shu bsp libraries for the stm32f7 discovery board and the gpio
 // configuration file.
 #include "pinmappings.h"
 #include "clock.h"
 #include "gpio.h"
 
 // RTOS DEFINES
 
 // declare the thread func prototypes, thread id, and priority
 void blink_thread (void const *argument);
 osThreadId tid_blink_thread;
 osThreadDef(blink_thread, osPriorityBelowNormal, 1, 0);
 
 // the mailbox we are pulling data from is declared elsewhere ...
extern osMailQId blink_box;

// HARDWARE DEFINES

// led is on PI 1 (the inbuilt led)
gpio_pin_t led1 = {PI_1, GPIOI, GPIO_PIN_1};

// THREAD INITIALISATION

// create the data generation thread
int init_blink_thread(void)
{
	// initialise LED
	init_gpio(led1, OUTPUT);
	
	// create the thread and get its task id
	tid_blink_thread = osThreadCreate(osThread(blink_thread), NULL);
	
	// check if ^ worked
	if(!tid_blink_thread)
	{
		return(-1);
	}
	return(0);
}

// ACTUAL THREADS

// led blink thread - blink the inbuilt led every second, that's it
void blink_thread (void const *argument)
{
	while(1)
	{
		// get the blink ting
		osEvent evt = osMailGet(blink_box, osWaitForever);
		if(evt.status == osEventMail)
		{
			blink_t *blink = (blink_t*)evt.value.p;
			
			write_gpio(led1, blink->onoff);
			osMailFree(blink_box, blink);
		}
		
	}
}
