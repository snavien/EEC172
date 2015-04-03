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
 *											  ADC Driver Source File
 *
 * File           : WyzBee_adc.c
 * Version        : V1.00
 * Programmer(s)  :
 *********************************************************************************************************
 * Note(s)		 :
 *********************************************************************************************************
 */


/*
 *********************************************************************************************************
 *                                              INCLUDE FILES
 *********************************************************************************************************
 */

#include <WyzBee_adc.h>
/*
 *********************************************************************************************************
 *                                              LOCAL DEFINES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                             LOCAL CONSTANTS
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                            LOCAL DATA TYPES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                          LOCAL GLOBAL VARIABLES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                             GLOBAL VARIABLES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                         LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************
 */



/*
 *********************************************************************************************************
 *********************************************************************************************************
 *                                             GLOBAL FUNCTION
 *********************************************************************************************************
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                           WyzBeeAdc_Init()
 *
 * Description : Initializes the ADC module
 *
 * Argument(s) : p_config 						pointer to the ADC Configuration structure
 *
 * Return(s)   : ERR_NONE                 		On successful initialization of the ADC module
 *
 *				 ERR_ADC_UNINITIALIZED      	If ADC modules doesn't configured properly
 *
 *				 ERR_INVALID_PARMS   			If passed parameters to the function was incorrect
 *
 *				 ERR_ADC_TIMEOUT				Time Out error
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */

err_t WyzBeeAdc_Init( WyzBeeAdc_Config_t   *p_config )
{
	volatile uint16_t   res;
	stc_adc_config_t    config_internal;
	stc_adcn_t*      	adc_instance = NULL;


	if(p_config != NULL)
	{
		memset( &config_internal , 0 , sizeof( stc_adc_config_t ) );

		config_internal.u32CannelSelect.AD_CH_9			=  1u;  					// select ADC channel
		config_internal.u32SamplingTimeSelect.AD_CH_9 	=  0u;						// use sampling time 0
		config_internal.enSamplingTimeN0 				=  p_config->SampleTime; 	// sampling time multipication factor
		config_internal.u8SamplingTime0					=  p_config->SamplingTime; 	// ST values set (0-31) allowed
		config_internal.u8SamplingMultiplier 			=  p_config->ClkDivRatio; 	// ADC main clock division factor
		config_internal.bScanConversionIrqEnable 		=  p_config->IntrMode;  	// ADC Interrupt mode
		config_internal.enScanMode						=  p_config->ScanMode;  	// repeat mode / one shot mode conversion
		config_internal.bLsbAlignment					=  TRUE;					// in register data is LSB aligned.
		config_internal.pfnScanConversion				=  p_config->AdcCb ;		// ADC conversion complete call back function
		config_internal.pfnErrorCallbackAdc				=  p_config->ErrCb ;		// ADC error call back function
		config_internal.bCompareAllChannels 			=  FALSE;					// Disable Compare feature
		config_internal.bRangeComparisonEnable 			=  FALSE;					// Disable Range Compare
		config_internal.bRangeCompareAllChannels 		=  FALSE;					// Disable Range Compare all channels

		if( p_config->ScanMode == AdcScanSingleConversion) 							// check conversion mode.
		{
			config_internal.u8ScanFifoDepth	  =  0u; 								//  FIFO depth 0 data is stored at starting of the FIFO
		}
		else
		{
			config_internal.u8ScanFifoDepth	  =  15u; 								//  FIFO depth generate interrupt for every 15 conversions
		}
		if(p_config->SamplingTime > 31)												// check for max sampling time
		{
			return ERR_INVALID_PARMS;
		}

		adc_instance  =  (stc_adcn_t*) &ADC0; 										// ADC instance data pointers
	}
	else
	{
		return ERR_INVALID_PARMS;
	}

	res = Adc_Init(&ADC0, &config_internal);										// check for init success

	if(res == Ok)
	{
		res = Adc_EnableWaitReady(adc_instance);              				 		// Enable ADC0 and wait for ready
		if(res != Ok)
		{
			return ERR_ADC_TIMEOUT;
		}
	}
	else
	{
		return ERR_ADC_UNINITIALIZED;
	}
	return ERR_NONE;
}

/*
 *********************************************************************************************************
 *                                           WyzBeeAdc_DeInit()
 *
 * Description : De-Initializes the ADC module
 *
 * Argument(s) : None
 *
 * Return(s)   : ERR_NONE                 		On success
 *
 *				 ERR_UNKNOWN		      		If Unknown error occur
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeAdc_DeInit( void )
{
	volatile uint16_t   res;


	res = Adc_DeInit((stc_adcn_t*) &ADC0);											// De-Initializes the ADC module

	if(res == Ok)
	{
		return ERR_NONE;
	}
	else
	{
		return ERR_UNKNOWN;
	}
}

/*
 *********************************************************************************************************
 *                                           WyzBeeAdc_ConvSwTrigger()
 *
 * Description : Triggers the ADC conversion by Software Trigger
 *
 * Argument(s) : None
 *
 * Return(s)   : ERR_NONE                 		On success
 *
 * 				 ERR_UNKNOWN		      		If Unknown error occur
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeAdc_ConvSwTrigger( void )
{
	volatile 		 uint16_t  res;
	stc_adcn_t      *adc_instance = NULL;


	adc_instance = (stc_adcn_t*) &ADC0; 											// ADC instance data pointers

	Adc_ScanSwTrigger(adc_instance);												// Trigger by software

	if(res == Ok)
	{
		return ERR_NONE;
	}
	else
	{
		return ERR_UNKNOWN;
	}
}

/*
 *********************************************************************************************************
 *                                           WyzBeeAdc_ReadyStatus()
 *
 * Description : Checks the ADC readiness
 *
 * Argument(s) : None
 *
 * Return(s)   : ERR_NONE                 	On success
 *
 *				 ERR_ADC_NOTR_READY      	If ADC modules doesn't configured properly
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeAdc_ReadyStatus( void )
{
	volatile 		 uint16_t  res;
	stc_adcn_t      *adc_instance = NULL;


	adc_instance = (stc_adcn_t*) &ADC0; 											// ADC instance data pointers

	res = Adc_Ready(adc_instance); 													// check for readiness

	if(res == Ok)
	{
		return ERR_NONE;
	}
	else
	{
		return ERR_ADC_NOTR_READY;
	}
}


/*
 *********************************************************************************************************
 *                                           WyzBeeAdc_Stop()
 *
 * Description : Stops the ADC conversion.
 *
 * Argument(s) : None
 *
 * Return(s)   : ERR_NONE                 		On success
 *
 * 				 ERR_UNKNOWN		      		If Unknown error occur
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeAdc_Stop( void )
{
	volatile 		 uint16_t  res;
	stc_adcn_t      *adc_instance = NULL;


	adc_instance = (stc_adcn_t*) &ADC0; 											// ADC instance data pointers

	res = Adc_ForceStop(adc_instance);  											// stop ADC

	if(res == Ok)
	{
		return ERR_NONE;
	}
	else
	{
		return ERR_UNKNOWN;
	}
}

/*
 *********************************************************************************************************
 *                                           WyzBeeAdc_ConversionStatus()
 *
 * Description : Checks the ADC conversion status
 *
 * Argument(s) :
 *
 * Return(s)   : ERR_NONE                 			On success
 *
 * 				 ERR_ADC_CONVERSION_IN_PROGRESS		If conversion is in progress
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeAdc_ConversionStatus( void )
{
	volatile 		 uint16_t  res;
	stc_adcn_t      *adc_instance = NULL;


	adc_instance = (stc_adcn_t*) &ADC0; 											// ADC instance data pointers

	res = Adc_ScanStatus(adc_instance);  											// check for conversion status

	if(res == Ok)
	{
		return ERR_NONE;
	}
	else if(res == OperationInProgress)
	{
		return ERR_ADC_CONVERSION_IN_PROGRESS;
	}
}

/*
 *********************************************************************************************************
 *                                           WyzBeeAdc_ReadData()
 *
 * Description : Reads the ADC FIFO data
 *
 * Argument(s) : None
 *
 * Return(s)   : ERR_NONE                 	On success
 *
 * 				 res						Returns the ADC converted FIFO value
 *
 * 				 ERR_UNKNOWN				If Unknown error occur
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
uint32_t WyzBeeAdc_ReadData( void )
{
	volatile 		 uint32_t  res;
	stc_adcn_t      *adc_instance = NULL;


	adc_instance = (stc_adcn_t*) &ADC0; 											// ADC instance data pointers

	res = Adc_ReadScanFifo(adc_instance);  											// check for conversion status

	if(res == 0xFFFFFFFFu)
	{
		return ERR_UNKNOWN;
	}
	return res; 																	// ADC converted value
}

/*
 *********************************************************************************************************
 *                                           WyzBeeAdc_DataValid()
 *
 * Description : Validates the ADC data
 *
 * Argument(s) : adc_data						ADC FIFO value
 *
 * Return(s)   : ERR_ADC_DATA_VALID             If ADC FIFO data is valid
 *
 *				 ERR_ADC_DATA_INVALID      		If ADC FIFO data is invalid
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeAdc_DataValid( uint32_t   adc_data )
{
	if (0u == (0x00001000u & adc_data))  											// check for data valid
	{
		return ERR_ADC_DATA_VALID; 													// ADC data is valid
	}

	return ERR_ADC_DATA_INVALID; 													// ADC data is invalid
}

/*
 *********************************************************************************************************
 *                                           WyzBeeAdc_Enable()
 *
 * Description : Enables The ADC module
 *
 * Argument(s) : None
 *
 * Return(s)   : ERR_NONE                 	On success
 *
 * 				 ERR_UNKNOWN				If Unknown error occur
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeAdc_Enable( void )
{
	volatile 		uint16_t  res;
	stc_adcn_t      *adc_instance = NULL;
	adc_instance = (stc_adcn_t*) &ADC0; 											// ADC instance data pointers

	res = Adc_Enable(adc_instance);  												// stop ADC

	if(res == Ok)
	{
		return ERR_NONE;
	}
	else
	{
		return ERR_UNKNOWN;
	}
}


/*
 *********************************************************************************************************
 *                                           END
 *********************************************************************************************************
 */
