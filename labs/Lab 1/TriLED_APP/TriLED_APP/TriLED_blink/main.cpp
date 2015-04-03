/**
 * @file     main.cpp
 * @version  1.0
 * @date     2015-Feb-26
 *
 * Copyright(C) Redpine Signals 2013
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief main: Beginning of the code
 *
 * @section Description : main function invokes the  system initialization.
 *
 *
 * @section Improvements :
 *
 */
/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/
#include <WyzBee_kit.h>
#include <WyzBee.h>
#include <WyzBee_gpio.h>
#include <Wyzbee_kit.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI_OLED.h>
//#include <mpu_9250.h>
/*
*********************************************************************************************************
*                                         GLOBAL VARIABLES
*********************************************************************************************************
*/

uint32 cnt;

/*
*********************************************************************************************************
*                                             GLOBAL FUNCTIONS
*********************************************************************************************************
*/


int main()
{
	/**Adafruit_SSD1351 myOled = Adafruit_SSD1351();//Constructor
	**myOled.begin();
	**myOled.fillScreen(BLACK);
	**myOled.setCursor(0,0);
	**myOled.setTextSize(3);
	**myOled.write('H');
	**/
	cnt = 0;
	sys_ticks_init();																				/*Initialize Systick timer*/
	while(1)
	{		
			if(WyzBeeGpio_Get(BUTTON) == GPIO_LOW && cnt == 0){
				WyzBeeGpio_Init(GPIO_LED2,GPIO_OUTPUT,GPIO_LOW);	/*Toggling Blue LED*/
				delay(600);																				/*Delay for 600 milliseconds*/
				WyzBeeGpio_Init(GPIO_LED2,GPIO_OUTPUT,GPIO_HIGH);
				cnt++;
			}
			if(WyzBeeGpio_Get(BUTTON) == GPIO_LOW && cnt == 1){
				WyzBeeGpio_Init(GPIO_LED3,GPIO_OUTPUT,GPIO_LOW);	/*Toggling Blue LED*/
				delay(600);																				/*Delay for 600 milliseconds*/
				WyzBeeGpio_Init(GPIO_LED3,GPIO_OUTPUT,GPIO_HIGH);
				cnt++;
			}
			if(WyzBeeGpio_Get(BUTTON) == GPIO_LOW && cnt == 2){
				WyzBeeGpio_Init(GPIO_LED4,GPIO_OUTPUT,GPIO_LOW);	/*Toggling Blue LED*/
				delay(600);																				/*Delay for 600 milliseconds*/
				WyzBeeGpio_Init(GPIO_LED4,GPIO_OUTPUT,GPIO_HIGH);
				
			}
				cnt = 0;
			}
			
			
	}		
		