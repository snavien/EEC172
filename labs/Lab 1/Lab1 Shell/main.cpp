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
#include <Adafruit_GFX.h>
#include "Adafruit_SSD1351.h"
#include <SPI_OLED.h>
#include  <WyzBee_spi.h>
#include <WyzBee_i2c.h>
#include <stdlib.h>
#include <cstdio>

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
			

void writeToScreen(char * str, int color){
	Adafruit_SSD1351 myOled = Adafruit_SSD1351();
	
	int len = 0;
	while(str[len] != '\0')
	{
		len++;
	}

	myOled.begin();
	myOled.fillScreen(BLACK);
	myOled.setCursor(0, 0);
	myOled.setTextSize(3);
	myOled.setTextColor(color);
	for(int i = 0; i < len; i++){
		myOled.write(str[i]);
	}
}

void readTempHum(){
	int16_t hum, temp;
	uint8_t data[1] ={0xE5},
					err, 
					ans[2];
	uint16_t len = 2;
	char *str;
	
	//err = WyzBeeI2c_Write(0x40, data, 1);
	if(!err)
	{
		//err = WyzBeeI2c_Read(0x40, ans, &len);
	}
	temp = ((ans[0])<<8 | (ans[1]));
	sprintf(str, "%d", temp);
	writeToScreen(str, CYAN);
}

int main()
{
	WyzBeeSpi_Init(&config_stc);
	//WyzBeeI2c_Init(&config);
	
	char * str = "Seanna & Irene <3";
	
	writeToScreen(str, MAGENTA );
	
}


/*
 *********************************************************************************************************
 *                                           END
 *********************************************************************************************************
 */