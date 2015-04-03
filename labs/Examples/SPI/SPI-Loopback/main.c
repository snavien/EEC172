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
 * Description    : This example provide's loopback for Serial Peripheral Interface (SPI) in interrupt mode.
 *********************************************************************************************************
 * Note(s)		 :
 *********************************************************************************************************
 */
 
 /*
 * Includes
 */

#include  <WyzBee_spi.h>
#include  <string.h>

#define polling_mode   0
#define Interrupt_mode 1

#define MAX_RX_SIZE 34
#define MAX_TX_SIZE 34
#define TX 1
#define RX 1
uint8 check_buf[23];

static volatile uint32 Tx_status =0 ;
static volatile bool_t Rx_status =0 ;
uint8 DummyTxBuf[MAX_TX_SIZE];
uint8 DummyRxBuf[MAX_RX_SIZE];
uint8 data;

#if  Interrupt_mode 
static void MyTxCallBack(void)
{
	WyzBeeSpi_Write('A');

}

static void MyRxCallBack(void)
{

	data=WyzBeeSpi_Read();

}

WyzBeeSpi_Config_t  config_stc={
		4000000,
		SpiMaster,
		SpiSyncWaitZero,
		SpiEightBits,
		SpiMsbBitFirst,
		SpiClockMarkHigh,
		SpiUseIntrMode,
		MyTxCallBack,
		MyRxCallBack
};

#endif

#if polling_mode
WyzBeeSpi_Config_t  config_stc={
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

#endif

int main(void)
{
	memset(DummyTxBuf, '\0' , MAX_TX_SIZE);
	memset(DummyRxBuf, '\0' , MAX_RX_SIZE);
	strcpy(DummyTxBuf , "HelloWorld");
	WyzBeeSpi_Init(&config_stc);

#if polling_mode
	while(1)
	{
		WyzBeeSpi_SyncSendRecv( DummyTxBuf, 10 , DummyRxBuf , 10 );
		memset(DummyRxBuf, '\0' , MAX_RX_SIZE);
		//WyzBeeSpi_SyncRecv(DummyRxBuf,10);
		Tx_status++;
	}
#endif

#if Interrupt_mode
	
	WyzBeeSpi_RxIntrEnable();
	WyzBeeSpi_TxIntrEnable();
#endif	

}

/*
 *********************************************************************************************************
 *                                           END
 *********************************************************************************************************
 */