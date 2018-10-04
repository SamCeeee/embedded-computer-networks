/*
 * a_traffic_lights.c
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

// map the led to GPIO PA8
gpio_pin_t redled = {PI_1, GPIOI, GPIO_PIN_1};
gpio_pin_t amberled = {PB_14, GPIOB, GPIO_PIN_14};
gpio_pin_t greenled = {PB_15, GPIOB, GPIO_PIN_15};

// this is the main method
int main()
{
	// Initialise the HAl library
	HAL_Init();
	init_sysclk_216MHz();
	
	init_gpio(redled, OUTPUT);
	init_gpio(amberled, OUTPUT);
	init_gpio(greenled, OUTPUT);
	
	
	write_gpio(redled, LOW);
	write_gpio(amberled, LOW);
	write_gpio(greenled, LOW);
	
	while(1)
	{
		write_gpio(redled, HIGH);
		HAL_Delay(1000);
		write_gpio(redled, LOW);
		HAL_Delay(1000);
		toggle_gpio(amberled);
		toggle_gpio(greenled);
		HAL_Delay(1000);
		toggle_gpio(greenled);
	}
}
