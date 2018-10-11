/*
 * b_led_dice.c
 *
 * this is the main application skeleton for the student exercises in task 3
 *
 */

// include the hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "gpio.h"

// include the shu random number generator
#include "random_numbers.h"

// map the led to GPIO PA8
gpio_pin_t led1 = {PI_1, GPIOI, GPIO_PIN_1};
gpio_pin_t led2 = {PB_14, GPIOB, GPIO_PIN_14};
gpio_pin_t led3 = {PB_15, GPIOB, GPIO_PIN_15};
gpio_pin_t led4 = {PA_8, GPIOA, GPIO_PIN_8};
gpio_pin_t led5 = {PA_15, GPIOA, GPIO_PIN_15};
gpio_pin_t led6 = {PI_2, GPIOI, GPIO_PIN_2};

// map the button
gpio_pin_t but1 = {PG_6, GPIOG, GPIO_PIN_6};

// function defintions
void leds_off (void);

// this is the main method
int main()
{

	// INITIALISE
	HAL_Init();
	init_sysclk_216MHz();
	init_random();
	
	// Initialise the Pins
	init_gpio(led1, OUTPUT);
	init_gpio(led2, OUTPUT);
	init_gpio(led3, OUTPUT);
	init_gpio(led4, OUTPUT);
	init_gpio(led5, OUTPUT);
	init_gpio(led6, OUTPUT);	
	init_gpio(but1, INPUT);
	
	leds_off();

	while(1)
	{
		uint32_t rnd = (get_random_int() % 6) + 1;
		
		leds_off();
		
		switch (rnd)
		{
			case 1:
				write_gpio(led1, HIGH);
				break;
			case 2:
				write_gpio(led1, HIGH);
				write_gpio(led2, HIGH);
				break;
			case 3:
				write_gpio(led1, HIGH);
				write_gpio(led2, HIGH);
				write_gpio(led3, HIGH);
				break;
			case 4:
				write_gpio(led1, HIGH);
				write_gpio(led2, HIGH);
				write_gpio(led3, HIGH);
				write_gpio(led4, HIGH);
				break;
			case 5:
				write_gpio(led1, HIGH);
				write_gpio(led2, HIGH);
				write_gpio(led3, HIGH);
				write_gpio(led4, HIGH);
				write_gpio(led5, HIGH);
				break;
			case 6:
				write_gpio(led1, HIGH);
				write_gpio(led2, HIGH);
				write_gpio(led3, HIGH);
				write_gpio(led4, HIGH);
				write_gpio(led5, HIGH);
				write_gpio(led6, HIGH);
				break;
		}
		HAL_Delay(3000);
	}
}

void leds_off (void)
{
	write_gpio(led1, LOW);
	write_gpio(led2, LOW);
	write_gpio(led3, LOW);
	write_gpio(led4, LOW);
	write_gpio(led5, LOW);
	write_gpio(led6, LOW);
}
