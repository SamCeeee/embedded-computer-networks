/*
 * main.c
 *
 * this is the skeleton for task 3
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


// CODE
gpio_pin_t temp = {PF_6, GPIOF, GPIO_PIN_6};

int32_t adcval;
float temval;



// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
  init_adc(temp);

  // initialise the lcd
  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, SDRAM_DEVICE_ADDR);
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
  
  // set the background colour to blue and clear the lcd
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
  BSP_LCD_Clear(LCD_COLOR_BLUE);
  
  // set the font to use
  BSP_LCD_SetFont(&Font24);
  
  // print the welcome message ...
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  
  HAL_Delay(2000);
  
  while(1)
  {
    char str[25], str2[25];
    adcval = read_adc(temp);
    sprintf(str, "%d", adcval);
    BSP_LCD_ClearStringLine(1);
		BSP_LCD_DisplayStringAtLine(1, (uint8_t *)str);		
		
		
		
		temval = ((adcval*(3300/4095.0)) - 500) / 10.0;
    sprintf(str2, "Temperature = %3.2f", temval);
    BSP_LCD_ClearStringLine(3);
		BSP_LCD_DisplayStringAtLine(3, (uint8_t *)str2);
    
    
    HAL_Delay(500);
  }
}
