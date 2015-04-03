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
 * Description    : In This example UART loopback is provided by pollingmode.
 *********************************************************************************************************
 * Note(s)		 :
 *********************************************************************************************************
 */
 
 /*
 * Includes
 */
#include <WyzBee_uart.h>
#include <string.h>

#define polling_mode   1
#define Interrput_mode 0
volatile int rx_char;

#if Interrput_mode
void uarttxisr(void)
{
	WyzBeeUart_Write('S');
}

void uartrxisr(void)
{
	
	rx_char=WyzBeeUart_Read();
}

WyzBeeUart_Config_t config_stc = {
		115200,
		UartNormal,
		UartParityNone,
		UartOneStopBit,
		UartEightBits,
		UartLsbBitFirst,
		UartClockMarkLow,
		UartUseNoHwFlow,
	  UartUseIntrMode,
		uarttxisr,
		uartrxisr
};
#endif

#if polling_mode
WyzBeeUart_Config_t config_stc = {
		115200,
		UartNormal,
		UartParityNone,
		UartOneStopBit,
		UartEightBits,
		UartLsbBitFirst,
		UartClockMarkLow,
		UartUseNoHwFlow,
	  UartUseNoIntrMode,
		NULL,
		NULL
};
#endif


int main(void)
{

	volatile uint32 cnt;
	volatile uint8 rx_char;
	volatile err_t res;
	uint8 dummyTx[20];
	uint8 dummyRx[20];
	rx_char='\0';
	
	WyzBeeUart_Init((WyzBeeUart_Config_t *) &config_stc);
	memset(dummyRx,'0',20);
	memset(dummyTx,'0',20);
	strcpy(dummyTx,"HelloWorld");
	cnt=0;

#if polling_mode // send and receive char
	while(1)
	{
		for(cnt=0;dummyTx[cnt];cnt++)
		{
			res = WyzBeeUart_SendChar(dummyTx[cnt]);

			if(res != ERR_UART_TX_TIMEOUT)
			{
				rx_char = WyzBeeUart_RecvChar();
				if(rx_char != ERR_UART_RX_TIMEOUT)
				{
					dummyRx[cnt]=rx_char;
				}
			}
		}
		memset(dummyRx,0,20);
	}
#endif


#if  Interrput_mode // send and recv interrupt
	
	WyzBeeUart_RxIntrEnable();
	WyzBeeUart_TxIntrEnable();

	while(1);
#endif

#if 0 // send and recv string 
	while(1)
	{
		rx_char = strlen(dummyTx);

		WyzBeeUart_SendString(dummyTx);
		WyzBeeUart_RecvString(dummyRx , &rx_char);

		memset(dummyRx,0,20);
	}
#endif
}
/*
 *********************************************************************************************************
 *                                           END
 *********************************************************************************************************
 */