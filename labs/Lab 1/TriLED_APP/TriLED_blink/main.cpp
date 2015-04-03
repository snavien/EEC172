/**
 * @file     main.c
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
	sys_ticks_init();																				/*Initialize Systick timer*/
	while(1)
	{
		cnt = 30;
		while(cnt>0)
		{
			if(cnt>=25)
			{
				WyzBeeGpio_Init(GPIO_LED4,GPIO_OUTPUT,GPIO_LOW);	/*Toggling Blue LED*/
				delay(600);																				/*Delay for 600 milliseconds*/
				WyzBeeGpio_Init(GPIO_LED4,GPIO_OUTPUT,GPIO_HIGH);
							
				WyzBeeGpio_Init(GPIO_LED3,GPIO_OUTPUT,GPIO_LOW);	/*Toggling Green LED*/
				delay(600);
				WyzBeeGpio_Init(GPIO_LED3,GPIO_OUTPUT,GPIO_HIGH);
							
				WyzBeeGpio_Init(GPIO_LED2,GPIO_OUTPUT,GPIO_LOW);	/*Toggling Red LED*/
				delay(600);
				WyzBeeGpio_Init(GPIO_LED2,GPIO_OUTPUT,GPIO_HIGH);
				
			}
			
			/*Increasing the blinking speed*/
			
			if(cnt>=15 && cnt<25)
			{
				WyzBeeGpio_Init(GPIO_LED4,GPIO_OUTPUT,GPIO_LOW);
				delay(300);																				/*Delay for 300 milliseconds*/
				WyzBeeGpio_Init(GPIO_LED4,GPIO_OUTPUT,GPIO_HIGH);
								
				WyzBeeGpio_Init(GPIO_LED3,GPIO_OUTPUT,GPIO_LOW);
  			delay(300);
				WyzBeeGpio_Init(GPIO_LED3,GPIO_OUTPUT,GPIO_HIGH);
				
				WyzBeeGpio_Init(GPIO_LED2,GPIO_OUTPUT,GPIO_LOW);
				delay(300);
				WyzBeeGpio_Init(GPIO_LED2,GPIO_OUTPUT,GPIO_HIGH);
			}
			
			/*Increasing the blinking speed*/
			
			if(cnt<15)
			{
				WyzBeeGpio_Init(GPIO_LED4,GPIO_OUTPUT,GPIO_LOW);
				delay(100);																				/*Delay for 100 milliseconds*/
				WyzBeeGpio_Init(GPIO_LED4,GPIO_OUTPUT,GPIO_HIGH);
				
				WyzBeeGpio_Init(GPIO_LED3,GPIO_OUTPUT,GPIO_LOW);
				delay(100);
				WyzBeeGpio_Init(GPIO_LED3,GPIO_OUTPUT,GPIO_HIGH);
				
				WyzBeeGpio_Init(GPIO_LED2,GPIO_OUTPUT,GPIO_LOW);
				delay(100);
				WyzBeeGpio_Init(GPIO_LED2,GPIO_OUTPUT,GPIO_HIGH);
			}
			cnt--;
		}
	}
}