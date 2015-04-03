/*
*********************************************************************************************************
*
*                           (c) Copyright 2015-2020 RedPine Signals Inc. Hyderabad, INDIA
*                                           All rights reserved.
*
*               This file is protected by international copyright laws. This file can only be used in
*               accordance with a license and should not be redistributed in any way without written
*               permission by Redpine Signals.
*
*                                            www.redpinesignals.com.com
*
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*											  ADC Driver Header File
*
* File           : WyzBee_adc.h
* Version        : V1.00
* Programmer(s)  :
*********************************************************************************************************
* Note(s)		 :
*********************************************************************************************************
*/

#ifndef WyzBee_ADC_H
#define WyzBee_ADC_H


/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/

#include <WyzBee.h>
#include <adc.h>


/*
*********************************************************************************************************
*                                                 DEFINES
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*********************************************************************************************************
*                                               ADC Error Codes
*********************************************************************************************************
*********************************************************************************************************
*/

#define ERR_ADC_UNINITIALIZED			31u			// ADC Module Not Configured Properly
#define ERR_ADC_TIMEOUT					32u			// ADC operation Time Out
#define ERR_ADC_CONVERSION_IN_PROGRESS 	33u			// ADC Conversion is in Progress
#define ERR_ADC_DATA_VALID				34u			// ADC Converted Data is valid
#define ERR_ADC_DATA_INVALID			35u			// ADC Converted Data is invalid
#define ERR_ADC_NOTR_READY				36u			// ADC Module is not ready

/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/
										                     	 	/*----------ADC call back functions--------------------------*/
typedef void (* WyzBeeAdc_Err_t)(void);				// ADC Conversion Error Call Back function pointer
													/* ADC Conversion Complete Call Back function pointer*/
typedef void (* WyzBeeAdc_ConvrnCmpteCb_t)(uint32_t* adcdata);


typedef enum WyzBeeAdc_ScanMode										/*----------ADC conversion modes----------------------------*/
{
	AdcScanSingleConversion  =  0,        			// Single mode of conversion
	AdcScanRepeatConversion  =  1         			// Repeat mode of conversion
} WyzBeeAdc_ScanMode_t;


typedef enum WyzBeeAdc_SamplingTimes								/*----------ADC sampling time multiplier values-------------*/
{
	AdcValue1        	=  0,    					// Set value * 1
	AdcValue4        	=  1,    					// Set value * 4
	AdcValue8        	=  2,    					// Set value * 8
	AdcValue16       	=  3,    					// Set value * 16
	AdcValue32       	=  4,    					// Set value * 32
	AdcValue64       	=  5,    					// Set value * 64
	AdcValue128      	=  6,    					// Set value * 128
	AdcValue256      	=  7,    					// Set value * 256

} WyzBeeAdc_SamplingTimes_t;


typedef enum WyzBeeAdc_FifoDataValid								/*----------ADC FiFo status---------------------------------*/
{
	AdcFifoInvalidData  =  0,    					// FIFO data invalid
	AdcFifoValidData    =  1    					// FIFO data valid

} WyzBeeAdc_FifoDataValid_t;


typedef enum WyzBeeAdc_UseInterrupt									/*----------ADC Interrupt mode enable/disable---------------*/
{
	AdcNoUseIntr  		=  0,						// Do not use ADC interrupt mode
	AdcUseIntr    		=  1    					// Use ADC interrupt mode

} WyzBeeAdc_UseInterrupt_t;


typedef enum WyzBeeAdc_FrequencyDivsion								/*----------ADC Main clock division values------------------*/
{
	AdcClkDiv1			=  0x80, 					// Frequency division ratio 1
	AdcClkDiv2			=  0x00, 					// Frequency division ratio 2
	AdcClkDiv3			=  0x01,					// Frequency division ratio 3
	AdcClkDiv4			=  0x02,					// Frequency division ratio 4
	AdcClkDiv5			=  0x03,					// Frequency division ratio 5
	AdcClkDiv6			=  0x04,					// Frequency division ratio 6
	AdcClkDiv7			=  0x05,					// Frequency division ratio 7
	AdcClkDiv8			=  0x06,					// Frequency division ratio 8
	AdcClkDiv9			=  0x07,					// Frequency division ratio 9
	AdcClkDiv10			=  0x08,					// Frequency division ratio 10
	AdcClkDiv11			=  0x09,					// Frequency division ratio 11
	AdcClkDiv12			=  0x0A,					// Frequency division ratio 12
	AdcClkDiv13			=  0x0B,					// Frequency division ratio 13
	AdcClkDiv14			=  0x0C,					// Frequency division ratio 14
	AdcClkDiv15			=  0x0D,					// Frequency division ratio 15
	AdcClkDiv16			=  0x0E,					// Frequency division ratio 16
	AdcClkDiv17			=  0x0F,					// Frequency division ratio 17
	AdcClkDiv18			=  0x10,					// Frequency division ratio 18
	AdcClkDiv19			=  0x11,					// Frequency division ratio 19
	AdcClkDiv20			=  0x12,					// Frequency division ratio 20
	AdcClkDiv21			=  0x13,					// Frequency division ratio 21
	AdcClkDiv22			=  0x14,					// Frequency division ratio 22
	AdcClkDiv23			=  0x15,					// Frequency division ratio 23
	AdcClkDiv24			=  0x16,					// Frequency division ratio 24
	AdcClkDiv25			=  0x17,					// Frequency division ratio 25
	AdcClkDiv26			=  0x18,					// Frequency division ratio 26
	AdcClkDiv27			=  0x19,					// Frequency division ratio 27
	AdcClkDiv28			=  0x1A,					// Frequency division ratio 28
	AdcClkDiv29			=  0x1B,					// Frequency division ratio 29
	AdcClkDiv30			=  0x1C,					// Frequency division ratio 30
	AdcClkDiv31			=  0x1D,					// Frequency division ratio 31
	AdcClkDiv32			=  0x1E,					// Frequency division ratio 32
	AdcClkDiv33			=  0x1F,					// Frequency division ratio 33
	AdcClkDiv34			=  0x20,					// Frequency division ratio 34
	AdcClkDiv35			=  0x21,					// Frequency division ratio 35
	AdcClkDiv36			=  0x22,					// Frequency division ratio 36
	AdcClkDiv37			=  0x23,					// Frequency division ratio 37
	AdcClkDiv38			=  0x24,					// Frequency division ratio 38
	AdcClkDiv39			=  0x25,					// Frequency division ratio 39
	AdcClkDiv40			=  0x26,					// Frequency division ratio 40
	AdcClkDiv41			=  0x27,					// Frequency division ratio 41
	AdcClkDiv42			=  0x28,					// Frequency division ratio 42
	AdcClkDiv43			=  0x29,					// Frequency division ratio 43
	AdcClkDiv44			=  0x2A,					// Frequency division ratio 44
	AdcClkDiv45			=  0x2B,					// Frequency division ratio 45
	AdcClkDiv46			=  0x2C,					// Frequency division ratio 46
	AdcClkDiv47			=  0x2D,					// Frequency division ratio 47
	AdcClkDiv48			=  0x2E,					// Frequency division ratio 48
	AdcClkDiv49			=  0x2F,					// Frequency division ratio 49
	AdcClkDiv50			=  0x30,					// Frequency division ratio 50
	AdcClkDiv51			=  0x31,					// Frequency division ratio 51
	AdcClkDiv52			=  0x32,					// Frequency division ratio 52
	AdcClkDiv53			=  0x33,					// Frequency division ratio 53
	AdcClkDiv54			=  0x34,					// Frequency division ratio 54
	AdcClkDiv55			=  0x35,					// Frequency division ratio 55
	AdcClkDiv56			=  0x36,					// Frequency division ratio 56
	AdcClkDiv57			=  0x37,					// Frequency division ratio 57
	AdcClkDiv58			=  0x38,					// Frequency division ratio 58
	AdcClkDiv59			=  0x39,					// Frequency division ratio 59
	AdcClkDiv60			=  0x3A,					// Frequency division ratio 60
	AdcClkDiv61			=  0x3B,					// Frequency division ratio 61
	AdcClkDiv62			=  0x3C,					// Frequency division ratio 62
	AdcClkDiv63			=  0x3D,					// Frequency division ratio 63
	AdcClkDiv64			=  0x3E,					// Frequency division ratio 64
	AdcClkDiv65 		=  0x3F 					// Frequency division ratio 65

} WyzBeeAdc_FrequencyDivsion_t;


typedef struct WyzBeeAdc_Config										/*----------ADC configuration structure---------------------*/
{
	WyzBeeAdc_ScanMode_t 			ScanMode;		// AdcScanRepeatConversion , AdcScanSingleConversion see the description of #WyzBeeAdc_ScanMode_t
	WyzBeeAdc_SamplingTimes_t		SampleTime;		// Sets the sampling time multiplication factor see the description of #WyzBeeAdc_SamplingTimes_t
	uint8_t 						SamplingTime;	// Sampling time of the ADC value (0 - 31) allowed
	WyzBeeAdc_FrequencyDivsion_t	ClkDivRatio;	// ADC clock division ratio see the description of #WyzBeeAdc_FrequencyDivsion_t
	WyzBeeAdc_ConvrnCmpteCb_t		AdcCb;			// ADC conversion complete CallBack Function pointer
	WyzBeeAdc_Err_t					ErrCb;			// ADC Conversion error CallBack Function pointer
	WyzBeeAdc_UseInterrupt_t		IntrMode;		// AdcUseIntr , AdcNoUseIntr see the description of #WyzBeeAdc_UseInterrupt_t

} WyzBeeAdc_Config_t;


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

err_t     WyzBeeAdc_Init			 ( WyzBeeAdc_Config_t   *p_config );

err_t     WyzBeeAdc_DeInit			 ( void                           );

err_t     WyzBeeAdc_ConvSwTrigger	 ( void                           );

err_t     WyzBeeAdc_ReadyStatus		 ( void                           );

err_t     WyzBeeAdc_Stop			 ( void                           );

err_t     WyzBeeAdc_ConversionStatus ( void                           );

uint32_t  WyzBeeAdc_ReadData		 ( void                           );

err_t     WyzBeeAdc_DataValid		 ( uint32_t              adc_data );

err_t     WyzBeeAdc_Enable			 ( void                           );

/*
*********************************************************************************************************
*                                           END
*********************************************************************************************************
*/

#endif // WyzBee_ADC_H
