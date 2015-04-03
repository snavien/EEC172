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
 * Description    : This example converts Analog volatage to Digital value.When the input is ov digital value will be (0)minimum. When the input is 3.3v(max) digital value will be 4096(observed). 
 *********************************************************************************************************
 * Note(s)		 :
 *********************************************************************************************************
 */
 
 /*
 * Includes
 */
#include <WyzBee_adc.h>
#include <string.h>

volatile uint32_t  AdcFifValue  = 0u;							// Global ADC result variable
volatile uint16_t  AdcValue;									// Result value
volatile uint8_t   AdcChannel;									// Result channel
volatile boolean_t AdcFinished = FALSE;							// Interrupt notification flag
float voltage;

void MyAdc_Err_callback(void)
{
	// do some action here if error occured
}

// input parameter ADC FiFo
void MyAdc_conversion_callback(uint32_t* adc_data)
{
	volatile uint16_t res;
	AdcFifValue = (uint32_t)*adc_data;             				// Store result
	res = WyzBeeAdc_DataValid(AdcFifValue);
	if(res == ERR_ADC_DATA_VALID )
	{
		AdcValue  = (0xFFFFu & (uint16_t)(AdcFifValue >> 16u)); // Get result value

		AdcFinished = TRUE;                  					// Set interrupt notification flag
	}
}


int32_t main(void)
{

	volatile uint16_t res;
	volatile uint16 adcVal;
	WyzBeeAdc_Config_t      config;								// ADC config structure

	memset(&config,0,sizeof(WyzBeeAdc_Config_t));

											/*------------ADC configuration parameters fill----------------------*/
	config.ScanMode     = AdcScanRepeatConversion;
	config.SamplingTime = 30u;
	config.SampleTime   = AdcValue32;
	config.IntrMode     = AdcUseIntr;
	config.ClkDivRatio  = AdcClkDiv7;
	config.AdcCb        = MyAdc_conversion_callback;
	config.ErrCb        = MyAdc_conversion_callback;

	res = WyzBeeAdc_Init(&config);								// Init ADC module

	while(1){
		if(res == ERR_NONE)
		{
			WyzBeeAdc_ConvSwTrigger();								// Trigger conversion by Software Trigger.
			if(AdcFinished == TRUE)
			{
				adcVal = AdcValue;
				voltage = (3.3 * adcVal)/4095;
				// do something with ADC data (AdcValue)
				//WyzBeeAdc_Stop();									// Stop ADC
			}
		}
	}
}

/*
 *********************************************************************************************************
 *                                           END
 *********************************************************************************************************
 */