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
			
	float temp_code, hum_code;
	float temp, humidity;
	float accel, MPSaccel;

void writeToScreen(char * str, int color){
	Adafruit_SSD1351 myOled = Adafruit_SSD1351();
	
	int len = 0;
	while(str[len] != '\0')
	{
		len++;
	}
	int static count = 0;
	if(count == 0)
	{
		myOled.begin();
		count = 1;
	}
	myOled.fillScreen(BLACK);
	myOled.setTextSize(2);
	myOled.setTextColor(color);
	myOled.setCursor(0, 0);

	for(int i = 0; i < len; i++){
		myOled.write(str[i]);
	}
}

void readTemp(){
	temp = 0;
	temp_code = 0;
	uint8 tx2[1] = {0xE3};
	uint8 rx2[2];
	uint8 ret; 
	uint16_t rxcnt = 2;
	char *str;
	
	ret = WyzBeeI2c_Init((WyzBeeI2c_Config_t *) &config);           /*Initialise I2C*/
	if(!ret)
	{
		ret = WyzBeeI2c_Write(0x40, tx2, 1);
		if(!ret)
		{
			ret = WyzBeeI2c_Read(0x40, rx2, &rxcnt);
			if(!ret)
			{
				temp_code = (rx2[0]<<8)|(rx2[1]);
				temp = ((175.72 * temp_code)/65536) - 46.85;

				sprintf(str, "%lf", temp);
				std::strcat(str, " Temp (C)");
				writeToScreen(str, CYAN);
			} // if no error in read
			else
				writeToScreen("READ ERROR", RED);
		} // if no error in write
		else
			writeToScreen("WRITE ERROR", RED);
	} // if no initialization error
	else
		writeToScreen("INIT ERROR", RED);
}

void readHum(){
//	float hum_code, humidity;
	uint8 tx2[1] = {0xE5};
	uint8 rx2[2];
	uint8 ret; 
	uint16_t rxcnt = 2;
	char *str;
	
	ret = WyzBeeI2c_Init((WyzBeeI2c_Config_t *) &config);           /*Initialise I2C*/
	if(!ret)
	{
		ret = WyzBeeI2c_Write(0x40, tx2, 1);
		if(!ret)
		{
			ret = WyzBeeI2c_Read(0x40, rx2, &rxcnt);
			if(!ret)
			{
				hum_code = (rx2[0]<<8)|(rx2[1]);
				humidity = (125 * hum_code)/65536 - 6;
				sprintf(str, "%lf", humidity);
				std::strcat(str, " Humid");
				writeToScreen(str, YELLOW);
			} // if no error in read
			else
				writeToScreen("READ ERROR", RED);
		} // if no error in write
		else
			writeToScreen("WRITE ERROR", RED);
	} // if no initialization error
	else
		writeToScreen("INIT ERROR", RED);
}

void acceleration()
{
	uint8 tx1[1] = {0x3B};
	uint8 rx2[2];
	uint8 ret; 
	uint16_t rxcnt = 2;
	char str[100];
	char text[80];
	std::strcpy(text, "x:");

	ret = WyzBeeI2c_Init((WyzBeeI2c_Config_t *) &config);           /*Initialise I2C*/
	if(!ret)
	{
		ret = WyzBeeI2c_Write(0x68, tx1, 1);
		if(!ret)
		{
			ret = WyzBeeI2c_Read(0x68, rx2, &rxcnt);
			if(!ret)
			{
				accel = (rx2[0]<<8)|(rx2[1]);
				sprintf(str, "%lf", accel);
				std::strcat(text, str);
				writeToScreen(text, WHITE);
			} // if no error in read
			else
				writeToScreen("READ ERROR", RED);
		} // if no error in write
		else
			writeToScreen("WRITE ERROR", RED);
		
	} // if no initialization error
	else
		writeToScreen("INIT ERROR", RED);
}

int main()
{
	WyzBeeSpi_Init(&config_stc);
	WyzBeeI2c_Init(&config);
	
	char * str = "Seanna & Chris";
	
	//writeToScreen(str, MAGENTA );

	while(1)
	{
		acceleration();
/*		
		for(int i = 0; i < 20; i++)
		{
			readTemp();
		}

		for(int i = 0; i < 20; i++)
		{
			readHum();
		}
*/
	}
}


/*
 *********************************************************************************************************
 *                                           END
 *********************************************************************************************************
 */