/*
 *********************************************************************************************************
 *
 *                        (c) Copyright 2015-2020 RedPine Signals Inc. HYDERABAD, INDIA
 *                                              All rights reserved.
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
 *											  UART Driver Source File
 *
 * File           : WyzBee_uart.c
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

#include <WyzBee_uart.h>
/*
 *********************************************************************************************************
 *                                              LOCAL DEFINES
 *********************************************************************************************************
 */
#define UART_INSTANCE    &MFS3
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
 *                                         LOCAL GLOBAL VARIABLES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                            GLOBAL VARIABLES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                        LOCAL FUNCTION PROTOTYPES
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
 *                                           WyzBeeUart_Init()
 *
 * Description : Initializes the UART module with user passed configuration parameters
 *
 * Argument(s) : WyzBeeUart_Config_t    		pointer to the WyzBee UART configuration structure
 *
 * Return(s)   : ERR_NONE                 		On successful initialization of the UART module
 *
 *				 ERR_UART_UNINITIALIZED      	If UART modules doesn't configured properly
 *
 *				 ERR_INVALID_PARMS    			If passed parameters to the function was incorrect
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeUart_Init(WyzBeeUart_Config_t   *p_config)
{
	volatile uint16_t 		res;
	stc_mfs_uart_config_t   config_internal;							// UART Internal Configuration structure


	memset(&config_internal,0,sizeof(stc_mfs_uart_config_t));			// Clear Local variables

	if(p_config != NULL )												// Check for valid pointers
	{
		config_internal.u32DataRate   = p_config->BaudRate;
		config_internal.u8UartMode    = p_config->Mode;
		config_internal.u8Parity      = p_config->Parity;
		config_internal.u8StopBit     = p_config->StopBit;
		config_internal.u8CharLength  = p_config->DataLength;
		config_internal.bBitDirection = p_config->BitDirection;
		config_internal.bSignalSystem = p_config->ClockLvl;
		config_internal.bHwFlow       = p_config->HwFlowCntl;

		FM4_GPIO->PFR3 	 = FM4_GPIO->PFR3 	| 0x0006;					// Set UART port as Peripheral I/O port
		FM4_GPIO->EPFR07 = FM4_GPIO->EPFR07 | 0x02800000; 				// Enable SOT and SIN configurations

		(void)Mfs_Uart_DeInit(UART_INSTANCE);							// De-Init UART
																		// Configure the UART with USER configurations
		res =  Mfs_Uart_Init(UART_INSTANCE, (stc_mfs_uart_config_t *)&config_internal);
		if (Ok !=res)													// Check for success
		{													/*----------If Module is not configured----------- */
			(void)Mfs_Uart_DeInit(UART_INSTANCE);						// De-int Module configurations
			FM4_GPIO->PFR3 	 = FM4_GPIO->PFR3 	& ~(0x0006);			// Clear the Port settings
			FM4_GPIO->EPFR07 = FM4_GPIO->EPFR07 & ~(0x02800000); 		// Clear the SOT and SIN configurations
			return ERR_UART_UNINITIALIZED;									// return error
		}
		Mfs_ErrorClear(UART_INSTANCE);									// Clear possible errors
		WyzBeeUart_TxEnable();											// Enable TX channel
		WyzBeeUart_RxEnable();											// Enable RX channel

		if(p_config->UseInterrupts==UartUseIntrMode)					// Check for INTR mode
		{
			Mfs_SetTxIntCallBack(UART_INSTANCE, p_config->TxIsr);		// Register the TX call back function
			Mfs_SetRxIntCallBack(UART_INSTANCE, p_config->RxIsr);		// Register the RX call back function

			Mfs_InitTxIrq(UART_INSTANCE);								// Initialize TX IRQ Request
			Mfs_InitRxIrq(UART_INSTANCE);								// Initialize RX IRQ Request
		}
	}
	else
	{
		return ERR_INVALID_PARMS;										// Return invalid parameters
	}
	return ERR_NONE;													// Return error none
}

/*
 *********************************************************************************************************
 *                                           WyzBeeUart_DeInit()
 *
 * Description : De-Inits the Uart module on WyzBee
 *
 * Argument(s) : none
 *
 * Return(s)   : ERR_NONE        				On success
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeUart_DeInit(void)
{
	(void)Mfs_Uart_DeInit(UART_INSTANCE);								// De-int Module configurations

	FM4_GPIO->PFR3 	 = FM4_GPIO->PFR3 	& ~(0x0006);					// Clear the Port settings
	FM4_GPIO->EPFR07 = FM4_GPIO->EPFR07 & ~(0x02800000);				// Clear the SOT and SIN configurations
	return ERR_NONE;
}

/*
 *********************************************************************************************************
 *                                           WyzBeeUart_SendChar()
 *
 * Description : sends the characters on UART Transmission line
 *
 * Argument(s) : tx_char		 				data to be sent out.
 *
 * Return(s)   : UART_TIMEOUT_VALUE				Send TimeOut error
 *
 * 				 ERR_NONE						On success
 *
 * Caller(s)   : WyzBeeUart_SendChar() called from WyzBeeUart_SendString() function or user can call from
 * 				 main
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeUart_SendChar(uint8_t tx_char)
{
	volatile uint8_t   tx_status;
	volatile uint16_t  cnt;


	cnt = UART_TIMEOUT_VALUE;											// Time out value
	do
	{
		tx_status = Mfs_GetStatus(UART_INSTANCE, MFS_UART_SSR_TDRE);	// Check for Transmission status
		if(cnt == 0)
		{
			return ERR_UART_TX_TIMEOUT;									// Return time out error
		}
		cnt--;
	} while ((tx_status & MFS_UART_SSR_TDRE)!= MFS_UART_SSR_TDRE);

	WyzBeeUart_Write(tx_char);											// Send UART Data
	return ERR_NONE;
}

/*
 *********************************************************************************************************
 *                                           WyzBeeUart_RecvChar()
 *
 * Description : Receives the character from UART Rx line.
 *
 * Argument(s) : none
 *
 * Return(s)   : rx_char						character received on UART RX line.
 *
 * Caller(s)   : This can be called from WyzBeeUart_RecvString() or user can call directly from main
 *
 * Note(s)     :
 *********************************************************************************************************
 */
uint8_t WyzBeeUart_RecvChar(void)
{
	volatile uint8_t     rx_status;
	volatile uint8_t     rx_char;
	volatile stc_mfsn_t* uart_ins;
	volatile uint16_t    cnt;


	cnt 	 = UART_TIMEOUT_VALUE;										// Uart time out value
	uart_ins = UART_INSTANCE;											// Uart instance pointer

	do
	{																	/*--- Check for reception Status--*/
		rx_status = Mfs_GetStatus(uart_ins, (MFS_UART_SSR_ERR | MFS_UART_SSR_RDRF));
		if(cnt==0)
		{
			return ERR_UART_RX_TIMEOUT;									// Return timeout error
		}
		cnt--;

	} while ((rx_status & MFS_UART_SSR_RDRF)!= MFS_UART_SSR_RDRF);

	if(0 != (rx_status & MFS_UART_SSR_ERR))								// check for reception errors
	{
		Mfs_ErrorClear(uart_ins); 										// Clear errors
	}

	if(0 != (rx_status & MFS_UART_SSR_RDRF))							// Check for RDRF data set Bit
	{
		rx_char = (uint8_t)Mfs_ReadData(uart_ins);						// Read UART Data
		return rx_char;													// Return received character
	}
}

/*
 *********************************************************************************************************
 *                                           WyzBeeUart_SendString()
 *
 * Description : Sends the block of data on UART TX line.
 *
 * Argument(s) : p_buf 				     		pointer to the TX buffer
 *
 * Return(s)   : ERR_NONE                   	On success
 *
 *				 ERR_INVALID_PARMS     			If passed parameters to the function was incorrect
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeUart_SendString(uint8_t *p_buf)
{
	volatile uint32_t buf_len;


	if(p_buf != NULL)
	{
		for(buf_len=0;p_buf[buf_len]!='\0';buf_len++)
		{
			WyzBeeUart_SendChar(p_buf[buf_len]);							// Send Data
		}
	}
	else
	{
		return ERR_INVALID_PARMS;
	}

	return ERR_NONE;
}

/*
 *********************************************************************************************************
 *                                           WyzBeeUart_RecvString()
 *
 * Description :
 *
 * Argument(s) : p_buf				      		Pointer to the data buffer
 *
 * 				 buf_len				  		Pointer to the buffer length , indicates bytes to read , and received bytes count (based on data availability in RDRF register) is updated in the same pointer.
 *
 * Return(s)   : ERR_NONE                   	On success
 *
 *				 ERR_INVALID_PARMS      		If passed parameters to the function was incorrect
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeUart_RecvString(uint8_t *p_buf , uint16_t *p_buf_len)
{
	volatile uint16_t  buf_indx;
	volatile uint16_t  res;
	         uint16_t  recv_cnt;


	recv_cnt = *p_buf_len;												// store Read count
	res      =  ERR_NONE;

	if((p_buf != NULL) && (p_buf_len != NULL) && (*p_buf_len != 0))			// Check for valid pointers
	{
		for( buf_indx=0; buf_indx < recv_cnt; buf_indx++ )
		{
			res = (uint8_t) WyzBeeUart_RecvChar();						// Receive each character
			if(res != ERR_UART_RX_TIMEOUT)								// Check for valid data
			{
				p_buf[buf_indx] = res;									// Receive Data
			}
			else
			{
				res == ERR_UART_RX_TIMEOUT;								// Time Out error
				break;													// break if data is not available
			}
		}
	}
	else
	{
		res = ERR_INVALID_PARMS;										// Invalid parameters error
	}

	*p_buf_len = buf_indx;												// update buffer Receive count

	return res;
}

/*
 *********************************************************************************************************
 *                                           WyzBeeUart_TxEnable()
 *
 * Description : Enables the Tx channel of the UART.
 *
 * Argument(s) : none
 *
 * Return(s)   : ERR_NONE                		On success
 *
 * 				 ERR_UNKNOWN					If any error occurs
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeUart_TxEnable(void)
{
	volatile uint16_t res;


	res=Mfs_SetTxEnable(UART_INSTANCE, TRUE);							// Enable TX
	if(res==Ok)
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
 *                                           WyzBeeUart_TxDisable()
 *
 * Description : Disables the Tx channel of the UART.
 *
 * Argument(s) : None
 *
 * Return(s)   : ERR_NONE                		On success
 *
 * 				 ERR_UNKNOWN					If any error occurs
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeUart_TxDisable(void)
{
	volatile uint16_t res;


	res=Mfs_SetTxEnable(UART_INSTANCE, FALSE);							// Disable TX
	if(res==Ok)
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
 *                                           WyzBeeUart_RxEnable()
 *
 * Description : Enables the Rx channel of the UART.
 *
 * Argument(s) : None
 *
 * Return(s)   : ERR_NONE                		On success
 *
 * 				 ERR_UNKNOWN					If any error occurs
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeUart_RxEnable(void)
{
	volatile uint16_t res;


	res = Mfs_SetRxEnable(UART_INSTANCE, TRUE);							// Enable RX
	if(res==Ok)
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
 *                                           WyzBeeUart_RxDisable()
 *
 * Description : Disables the Rx channel of the UART.
 *
 * Argument(s) : None
 *
 * Return(s)   : ERR_NONE                		On success
 *
 * 				 ERR_UNKNOWN					If any error occurs
 *
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeUart_RxDisable(void)
{
	volatile uint16_t res;


	res=Mfs_SetRxEnable(UART_INSTANCE, FALSE);							// Disable RX
	if(res==Ok)
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
 *                                           WyzBeeUart_Write()
 *
 * Description : Writes the data on TX line
 *
 * Argument(s) : tx_char 			  			data to be sent on UART
 *
 * Return(s)   : ERR_NONE                		On success
 *
 * 				 ERR_UNKNOWN					If any error occurs
 *
 * Caller(s)   : Typically called in UART TX ISR routines and and UART send functions
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeUart_Write(uint8_t tx_char)
{
	volatile uint16_t res;


	res=Mfs_WriteData(UART_INSTANCE, tx_char);							// Write Data
	if(res==Ok)
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
 *                                           WyzBeeUart_Read()
 *
 * Description : Reads the data on RX line
 *
 * Argument(s) : None
 *
 * Return(s)   : rx_char						Data received on RX
 *
 * Caller(s)   : Typically called in UART RX ISR routines and and UART receive functions
 *
 * Note(s)     :
 *********************************************************************************************************
 */
uint8_t WyzBeeUart_Read(void)
{
	volatile uint16_t rx_char;


	rx_char = Mfs_ReadData(UART_INSTANCE);								// Read Data
	return (uint8_t) rx_char;
}

/*
 *********************************************************************************************************
 *                                           WyzBeeUart_RxIntrEnable()
 *
 * Description : Enables the RX interrupt
 *
 * Argument(s) : None
 *
 * Return(s)   : ERR_NONE                		On success
 *
 * 				 ERR_UNKNOWN					If any error occurs
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeUart_RxIntrEnable(void)
{
	volatile uint16_t res;


	res = Mfs_SetRxIntEnable(UART_INSTANCE, TRUE);						// Enable RX Interrupt
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
 *                                           WyzBeeUart_RxIntrDisable()
 *
 * Description : Disables the RX interrupt
 *
 * Argument(s) : None
 *
 * Return(s)   : ERR_NONE                		On success
 *
 * 			     ERR_UNKNOWN					If any error occurs
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeUart_RxIntrDisable(void)
{
	volatile uint16_t res;


	res = Mfs_SetRxIntEnable(UART_INSTANCE, FALSE);						// Disable RX Interrupt
	if(res==Ok)
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
 *                                           WyzBeeUart_TxIntrEnable()
 *
 * Description : Enables the TX interrupt
 *
 * Argument(s) : None
 *
 * Return(s)   : ERR_NONE                		On success
 *
 * 				 ERR_UNKNOWN			  		If any error occurs
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeUart_TxIntrEnable(void)
{
	volatile uint16_t res;


	res = Mfs_SetTxIntEnable(UART_INSTANCE, TRUE);						// Enable TX Interrupt
	if(res==Ok)
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
 *                                           WyzBeeUart_TxIntrDisable()
 *
 * Description : Disables the TX interrupt
 *
 * Argument(s) : None
 *
 * Return(s)   : ERR_NONE                		On success
 *
 * 				 ERR_UNKNOWN					If any error occurs
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeeUart_TxIntrDisable(void)
{
	volatile uint16_t res;


	res = Mfs_SetTxIntEnable(UART_INSTANCE, FALSE);						// Disable TX Interrupt
	if(res==Ok)
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
