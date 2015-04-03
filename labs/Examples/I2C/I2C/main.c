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
 * Description    : This example provides I2C communication between WyzBee board as a master and on board Temparature sensor as slave.
 *********************************************************************************************************
 * Note(s)		 :
 *********************************************************************************************************
 */
 
 /*
 * Includes
 */
#include <WyzBee_i2c.h>

/*I2C Configuration (data rate, Mode, Noise Filter, slave address)*/
WyzBeeI2c_Config_t config ={
		100000,
		I2cMasterMode,
		I2cNoizeFilterLess100M,
		0x00,
};
	float temp_code, hum_code;
	float temp, humidity;

int main(void)
{
	uint8 tx1[1] = {0xE5};
	uint8 tx2[1] = {0xE3};
	uint8 rx1[2];
	uint8 rx2[2];
	uint8 ret; 
	uint16_t rxcnt = 2;

	ret = WyzBeeI2c_Init((WyzBeeI2c_Config_t *) &config);           /*Initialise I2C*/


    while(1)
    {
    	ret = WyzBeeI2c_Write(0x40, tx1, 1);
    	if(!ret)
    		ret = WyzBeeI2c_Read(0x40, rx1, &rxcnt);
    	hum_code = (rx1[0]<<8)|(rx1[1]);
    	humidity = (125 * hum_code)/65536 - 6;

    	ret = WyzBeeI2c_Write(0x40, tx2, 1);
    	if(!ret)
    		ret = WyzBeeI2c_Read(0x40, rx2, &rxcnt);
    	temp_code = (rx2[0]<<8)|(rx2[1]);
    	temp = (175.72 * temp_code)/65536 - 46.85;                  /*As per Si7021.pdf*/

    }
}
/*
 *********************************************************************************************************
 *                                           END
 *********************************************************************************************************
 */