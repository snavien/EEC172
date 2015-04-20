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
 * Description    : This example uses Serial Peripheral Interface (SPI) of WyzBee board as master in polling method and OLED screen as slave to print a text message.
 *********************************************************************************************************
 * Note(s)		 :
 *********************************************************************************************************
 */
 
 /*
 * Includes
 */
 
#include <WyzBee.h>
#include <WyzBee_gpio.h>
#include <Adafruit_GFX.h>
#include "Adafruit_SSD1351.h"
#include <SPI_OLED.h>
#include <WyzBee_spi.h>
#include <WyzBee_i2c.h>
#include <stdlib.h>
#include <cstdio>
#include <cstring>

extern Adafruit_SSD1351 tft = Adafruit_SSD1351(); //@  OLED class variable
/*===================================================*/
/**
 * @fn			void print_oled(int8 *text, uint16_t color)
 * @brief		this functions is used to print the data on the oled screen
 * @param 1[in]	int8 *text
 * @param 2[in]	uint16_t color , color
 * @param[out]	none
 * @return		none
 * @description This API should contain the code / function call which will prints the data on the OLED screen.
 */

WyzBeeSpi_Config_t config_stc={
		4000000,
		SpiMaster,
		SpiSyncWaitZero,
		SpiEightBits,
		SpiMsbBitFirst,
		SpiClockMarkHigh,
		SpiNoUseIntrmode,
		NULL,                                                                
		NULL
};

WyzBeeI2c_Config_t config = {
	100000,
	I2cMasterMode,
	I2cNoizeFilterLess100M,
	0x00,
};

void delay(uint32_t _delay)  // delay
{
	uint32_t x;
	for(x=0;x<10000*_delay;x++);
}

int main(void)
{

	WyzBeeGpio_Init(10, GPIO_INPUT, GPIO_LOW);
	WyzBeeGpio_Init(GPIO_1, GPIO_OUTPUT, GPIO_LOW);
	
	while(1)
	{
		WyzBeeGpio_Put(GPIO_1, WyzBeeGpio_Get(10));
		delay(100);
	}
}





/*
 *********************************************************************************************************
 *                                           END
 *********************************************************************************************************
 */