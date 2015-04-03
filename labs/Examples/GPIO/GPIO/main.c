/*
 *********************************************************************************************************
 *
 *                        (c) Copyright 2015-2020 RedPine Signals Inc. HYDERABAD, INDIA
 *                                            All rights reserved.
 *
 *               This file is protected by international copyright laws. This file can only be used in
 *               accordance with a license and should not be redistributed in any way without written
 *               permission by Redpine Signals.
 *
 *                                            www.redpinesignals.com
 *
 *********************************************************************************************************
 */
 /*
 *********************************************************************************************************
 *
 *											  main file
 *
 * File           : main.c
 * Version        : V1.00
 * Programmer(s)  :
 * Description    : In This example TRILED(red green blue)will blink one after the other with particular delay
 *********************************************************************************************************
 * Note(s)		 :
 *********************************************************************************************************
 */
 
 /*
 * Includes
 */

#include  <WyzBee_gpio.h>

void delay(uint32_t _delay)  // delay
{
	uint32_t x;
	for(x=0;x<10000*_delay;x++);
}

int main(void)
{

while(1)
{
	WyzBeeGpio_Init(GPIO_LED2,GPIO_OUTPUT,GPIO_LOW);
	delay(100);
	WyzBeeGpio_Init(GPIO_LED2,GPIO_OUTPUT,GPIO_HIGH);
	delay(100);
	WyzBeeGpio_Init(GPIO_LED3,GPIO_OUTPUT,GPIO_LOW);
	delay(100);
	WyzBeeGpio_Init(GPIO_LED3,GPIO_OUTPUT,GPIO_HIGH);
	delay(100);
	WyzBeeGpio_Init(GPIO_LED4,GPIO_OUTPUT,GPIO_LOW);
	delay(100);
	WyzBeeGpio_Init(GPIO_LED4,GPIO_OUTPUT,GPIO_HIGH);
	delay(100);
}

}
/*
 *********************************************************************************************************
 *                                           END
 *********************************************************************************************************
 */