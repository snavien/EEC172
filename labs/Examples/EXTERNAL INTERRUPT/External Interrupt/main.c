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
 * Description    : In This example pushbutton is used as an external interrput.According to the application led will be on and off by pressing the button. 
 *********************************************************************************************************
 * Note(s)		 :
 *********************************************************************************************************
 */
 
 /*
 * Includes
 */

#include <WyzBee_gpio.h>
#include <WyzBee_ext.h>

void Main_ExtIntCallback1()
{
	static uint8 flag;

	if(!flag)
	{
		WyzBeeGpio_Init(GPIO_LED4,GPIO_OUTPUT,GPIO_LOW);
		flag=1;
	}
	else
	{
		WyzBeeGpio_Put(GPIO_LED4,GPIO_HIGH);
		flag =0;
	}
}

int main(void)
{
	WyzBee_exint_config_t WyzBeeExtIntConfig;

	WyzBee_PDL_ZERO(WyzBeeExtIntConfig);

	WyzBeeExtIntConfig.abEnable[11] = TRUE;   // INT11
	WyzBeeExtIntConfig.aenLevel[11] = CalExIntRisingEdge;
	WyzBeeExtIntConfig.apfnExintCallback[11] = &Main_ExtIntCallback1;

	WyzBee_Exint_Init(&WyzBeeExtIntConfig);
	WyzBee_Exint_EnableChannel(11);


	while(1)
	{}

}
/*
 *********************************************************************************************************
 *                                           END
 *********************************************************************************************************
 */