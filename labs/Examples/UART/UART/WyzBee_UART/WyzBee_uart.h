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
*                                            www.redpinesignals.com
*
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*											 UART Driver Header File
*
* File           : WyzBee_uart.h
* Version        : V1.00
* Programmer(s)  :
*********************************************************************************************************
* Note(s)		 :
*********************************************************************************************************
*/
#ifndef WyzBee_UART_H
#define WyzBee_UART_H

/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/

#include <WyzBee.h>
#include <mfs.h>

/*
*********************************************************************************************************
*                                                 DEFINES
*********************************************************************************************************
*/
#define UART_TIMEOUT_VALUE      100000
/*
*********************************************************************************************************
*********************************************************************************************************
*                                                Error Codes (0x0000-0x001F)
*********************************************************************************************************
*********************************************************************************************************
*/
#define ERR_UART_UNINITIALIZED 	21u
#define ERR_UART_TX_TIMEOUT		22u
#define ERR_UART_RX_TIMEOUT		23u
/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/
															/*-----------CallBack functions-----------*/
typedef void (* WyzBeeUart_TxIsrCallBack_t)(void);	// TX CallBack
typedef void (* WyzBeeUart_RxIsrCallBack_t)(void);	// TX CallBack

typedef enum WyzBeeUart_Mode								/*----------UART MODE configuration------*/
{
    UartNormal 			= 0u,          				// Normal mode
    UartMulti  			= 1u           				// Multi-Processor Mode
    
} WyzBeeUart_Mode_t;


typedef enum WyzBeeUart_Parity								/*----------UART parity configuration------*/
{
	UartParityNone  	= 0u,         				// No parity bit is used.
	UartParityEven  	= 2u,         				// Even parity bit is used.
	UartParityOdd   	= 3u          				// Odd parity bit is used.
    
} WyzBeeUart_Parity_t;


typedef enum WyzBeeUart_StopBit								/*----------UART stopBit configuration------*/
{
	UartOneStopBit    	= 0u,       				// 1 Stop Bit
	UartTwoStopBits   	= 1u,       				// 2 Stop Bits
	UartThreeStopBits 	= 2u,       				// 3 Stop Bits
	UartFourStopBits  	= 3u        				// 4 Stop Bits
    
} WyzBeeUart_StopBit_t;


typedef enum WyzBeeUart_IntrConfig							/*-----------UART INTR MODE configuration--*/
{
   UartUseIntrMode   	= 1u,          				// Enable  Uart interrupts
   UartUseNoIntrMode 	= 0u          				// Disable Uart interrupts

} WyzBeeUart_IntrConfig_t;


typedef enum WyzBeeUart_HwFlowCntl							/*-------------HW FLOW CNTRL---------------*/
{
   UartUseHwFlow   		= 1u,          				// Enable  Uart interrupts
   UartUseNoHwFlow		= 0u          				// Disable Uart interrupts

} WyzBeeUart_HwFlowCntl_t;


typedef enum WyzBeeUart_BitOrde								/*-------------UART BIT ORDER---------------*/
{
	UartMsbBitFirst	    = 1u,          				// MSB bit First
	UartLsbBitFirst 	= 0u          				// LSB bit First

} WyzBeeUart_BitOrde_t;


typedef enum WyzBeeUart_Clock								/*-------------UART CLOK MODE---------------*/
{
	UartClockMarkHigh   = 1u,          				// NRZ
	UartClockMarkLow 	= 0u          				// inverted NRZ

} WyzBeeUart_Clock_t;


typedef enum WyzBeeUart_BitLength							/*-------------UART TRANSFER BIT LENGTHS----*/
{
	UartFiveBits        = 0u,      					//  5  Bit character length
	UartSixBits         = 1u,      					//  6  Bit character length
	UartSevenBits       = 2u,    					//  7  Bit character length
	UartEightBits       = 3u,      					//  8  Bit character length
	UartNineBits        = 4u,      					//  9  Bit character length
	UartTenBits         = 5u,     					//  10 Bit character length
	UartElevenBits      = 6u,     					//  11 Bit character length
	UartTwelveBits      = 7u,      					//  12 Bit character length
	UartThirteenBits    = 8u,      					//  13 Bit character length
	UartFourteenBits    = 9u,      					//  14 Bit character length
	UartFifteenBits     = 10u,     					//  15 Bit character length
	UartSixteenBits     = 11u,     					//  16 Bit character length
} WyzBeeUart_BitLength_t;

typedef struct WyzBeeUart_Config							/*----------UART configuration struct----*/
{
	uint32_t  					BaudRate;			// Baud rate (bps)
	uint8_t   					Mode;				// UART mode , see the description of WyzBeeUart_Mode_t
	uint8_t   					Parity;				// Parity , see the description of WyzBeeUart_Parity_t
	uint8_t   					StopBit;			// Stop bit , see the description of WyzBeeUart_StopBit_t
	uint8_t   					DataLength;			// 5..9 Bit Character Length , see the description of WyzBeeUart_BitLength_t
	bool_t 						BitDirection;		// LSB first / MSB first , see the description of WyzBeeUart_BitOrde_t
	bool_t 						ClockLvl;			// NRZ / Inverted NRZ , see the description of WyzBeeUart_Clock_t
	bool_t 						HwFlowCntl;			// Not use Hardware Flow, / Use Hardware Flow , see the description of WyzBeeUart_HwFlowCntl_t
	bool_t         				UseInterrupts;  	// Enable Disable Interrupts , see the description of WyzBeeUart_IntrConfig_t
	WyzBeeUart_TxIsrCallBack_t  TxIsr;				// TxIsr Callback
	WyzBeeUart_RxIsrCallBack_t  RxIsr;				// Rx Isr CallBack

} WyzBeeUart_Config_t;


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

err_t 	WyzBeeUart_Init			( WyzBeeUart_Config_t	*p_config );

err_t 	WyzBeeUart_SendChar		( uint8_t 			     tx_char  );

uint8_t WyzBeeUart_RecvChar		( void							  );

err_t 	WyzBeeUart_SendString	( uint8_t 			    *buf	  );

err_t 	WyzBeeUart_RecvString	( uint8_t 				*buf,
								  uint16_t 				*buf_len  );

err_t 	WyzBeeUart_TxEnable		( void							  );

err_t 	WyzBeeUart_TxDisable	( void						      );

err_t 	WyzBeeUart_RxEnable		( void							  );

err_t 	WyzBeeUart_RxDisable	( void		  				 	  );

err_t 	WyzBeeUart_Write		( uint8_t 			     tx_char  );

uint8_t WyzBeeUart_Read			( void                            );

err_t 	WyzBeeUart_RxIntrEnable	( void                            );

err_t 	WyzBeeUart_TxIntrEnable	( void                            );

err_t 	WyzBeeUart_TxIntrDisable( void                            );

/*
*********************************************************************************************************
*                                           END
*********************************************************************************************************
*/

#endif // WyzBee_UART_H
