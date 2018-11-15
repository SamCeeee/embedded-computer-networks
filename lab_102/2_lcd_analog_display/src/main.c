/*
 * main.c
 *
 * this is the skeleton for task 2
 *
 * author:    Dr. Alex Shenfield
 * date:      04/09/2018
 * purpose:   55-604481 embedded computer networks : lab 102
 */

// include the basic headers and hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "stm32746g_discovery_lcd.h"
#include "adc.h"
#include "gpio.h"

// LCD DEFINES

// define a message boarder (note the lcd is 28 characters wide using Font24)
#define BOARDER     "****************************"

// specify a welcome message
const char * welcome_message[2] = 
{
  "*     Hello sonny jim!     *",
  "*     Welcome to Uni!      *"
};

// CODE
gpio_pin_t led1 = {PB_14, GPIOB, GPIO_PIN_14};
gpio_pin_t led2 = {PB_15, GPIOB, GPIO_PIN_15};
gpio_pin_t led3 = {PA_8, GPIOA, GPIO_PIN_8};
gpio_pin_t led4 = {PA_15, GPIOA, GPIO_PIN_15};

gpio_pin_t pot = {PF_8, GPIOF, GPIO_PIN_8};

uint32_t potval;

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
  init_adc(pot);
	init_gpio(led1, OUTPUT);
	init_gpio(led2, OUTPUT);
	init_gpio(led3, OUTPUT);
	init_gpio(led4, OUTPUT);
	
	// initialise the lcd
  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, SDRAM_DEVICE_ADDR);
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

  // set the background colour to blue and clear the lcd
  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
  BSP_LCD_Clear(LCD_COLOR_BLACK);
  
  // set the font to use
  BSP_LCD_SetFont(&Font24); 
  
  // print the welcome message ...
  BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
  BSP_LCD_DisplayStringAtLine(0, (uint8_t *)BOARDER);
  BSP_LCD_DisplayStringAtLine(1, (uint8_t *)welcome_message[0]);
  BSP_LCD_DisplayStringAtLine(2, (uint8_t *)welcome_message[1]);
  BSP_LCD_DisplayStringAtLine(3, (uint8_t *)BOARDER); 
    
  // delay a little ...
  HAL_Delay(1000);
	
  while(1)
	{
		// get pot val
		potval = read_adc(pot);
		potval = (potval*100)/4096;

		// format a string based around the uptime counter
    char str[25], str1[25], str2[25], str3[25], str4[25];
    sprintf(str, "ADC val = %3d%%", potval);
    if (potval >= 80)
		{
			write_gpio(led1, HIGH);
			write_gpio(led2, HIGH);
			write_gpio(led3, HIGH);
			write_gpio(led4, HIGH);
			sprintf(str1, "Led 1 is HIGH");
			sprintf(str2, "Led 2 is HIGH");
			sprintf(str3, "Led 3 is HIGH");
			sprintf(str4, "Led 4 is HIGH");
			BSP_LCD_ClearStringLine(5);
			BSP_LCD_DisplayStringAtLine(5, (uint8_t *)str1);
			BSP_LCD_ClearStringLine(6);
			BSP_LCD_DisplayStringAtLine(6, (uint8_t *)str2);
			BSP_LCD_ClearStringLine(7);
			BSP_LCD_DisplayStringAtLine(7, (uint8_t *)str3);
			BSP_LCD_ClearStringLine(8);
			BSP_LCD_DisplayStringAtLine(8, (uint8_t *)str4);
		}
		else if (potval >= 60)
		{
			write_gpio(led1, HIGH);
			write_gpio(led2, HIGH);
			write_gpio(led3, HIGH);
			write_gpio(led4, LOW);
			sprintf(str1, "Led 1 is HIGH");
			sprintf(str2, "Led 2 is HIGH");
			sprintf(str3, "Led 3 is HIGH");
			sprintf(str4, "Led 4 is LOW");
			BSP_LCD_ClearStringLine(5);
			BSP_LCD_DisplayStringAtLine(5, (uint8_t *)str1);
			BSP_LCD_ClearStringLine(6);
			BSP_LCD_DisplayStringAtLine(6, (uint8_t *)str2);
			BSP_LCD_ClearStringLine(7);
			BSP_LCD_DisplayStringAtLine(7, (uint8_t *)str3);
			BSP_LCD_ClearStringLine(8);
			BSP_LCD_DisplayStringAtLine(8, (uint8_t *)str4);
		}
		else if (potval >= 40)
		{
			write_gpio(led1, HIGH);
			write_gpio(led2, HIGH);
			write_gpio(led3, LOW);
			write_gpio(led4, LOW);
			sprintf(str1, "Led 1 is HIGH");
			sprintf(str2, "Led 2 is HIGH");
			sprintf(str3, "Led 3 is LOW");
			sprintf(str4, "Led 4 is LOW");
			BSP_LCD_ClearStringLine(5);
			BSP_LCD_DisplayStringAtLine(5, (uint8_t *)str1);
			BSP_LCD_ClearStringLine(6);
			BSP_LCD_DisplayStringAtLine(6, (uint8_t *)str2);
			BSP_LCD_ClearStringLine(7);
			BSP_LCD_DisplayStringAtLine(7, (uint8_t *)str3);
			BSP_LCD_ClearStringLine(8);
			BSP_LCD_DisplayStringAtLine(8, (uint8_t *)str4);
		}
		else if (potval >= 20)
		{
			write_gpio(led1, HIGH);
			write_gpio(led2, LOW);
			write_gpio(led3, LOW);
			write_gpio(led4, LOW);
			sprintf(str1, "Led 1 is HIGH");
			sprintf(str2, "Led 2 is LOW");
			sprintf(str3, "Led 3 is LOW");
			sprintf(str4, "Led 4 is LOW");
			BSP_LCD_ClearStringLine(5);
			BSP_LCD_DisplayStringAtLine(5, (uint8_t *)str1);
			BSP_LCD_ClearStringLine(6);
			BSP_LCD_DisplayStringAtLine(6, (uint8_t *)str2);
			BSP_LCD_ClearStringLine(7);
			BSP_LCD_DisplayStringAtLine(7, (uint8_t *)str3);
			BSP_LCD_ClearStringLine(8);
			BSP_LCD_DisplayStringAtLine(8, (uint8_t *)str4);
		}
		else
		{
			write_gpio(led1, LOW);
			write_gpio(led2, LOW);
			write_gpio(led3, LOW);
			write_gpio(led4, LOW);
			sprintf(str1, "Led 1 is LOW");
			sprintf(str2, "Led 2 is LOW");
			sprintf(str3, "Led 3 is LOW");
			sprintf(str4, "Led 4 is LOW");
			BSP_LCD_ClearStringLine(5);
			BSP_LCD_DisplayStringAtLine(5, (uint8_t *)str1);
			BSP_LCD_ClearStringLine(6);
			BSP_LCD_DisplayStringAtLine(6, (uint8_t *)str2);
			BSP_LCD_ClearStringLine(7);
			BSP_LCD_DisplayStringAtLine(7, (uint8_t *)str3);
			BSP_LCD_ClearStringLine(8);
			BSP_LCD_DisplayStringAtLine(8, (uint8_t *)str4);
		}

    // print the message to the lcd
    BSP_LCD_ClearStringLine(4);
    BSP_LCD_DisplayStringAtLine(4, (uint8_t *)str);
    
    HAL_Delay(250);
	}
}