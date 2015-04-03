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
 * Description    : In This example 2 timers are used.Depending on the load time timer callbacks will be called. 
 *********************************************************************************************************
 * Note(s)		 :
 *********************************************************************************************************
 */
 
 /*
 * Includes
 */
#include <WyzBee_gpio.h>
#include <WyzBee_timer.h>

static uint32_t u32CountDt0;
static uint32_t u32CountDt1;
/**
 ******************************************************************************
 ** \brief Callback Function for DT channel 0
 **
 ******************************************************************************/
static void Dt0Callback(void)
{
	static int status =0;
	if(status ==0)
	{
		Dt_ClrIntFlag(DtChannel0);    // Clear Irq
		u32CountDt0++;

		WyzBeeGpio_Init(GPIO_LED4,GPIO_OUTPUT,GPIO_HIGH);
		status = 1;
	}
	else
	{
		WyzBeeGpio_Put(GPIO_LED4,GPIO_LOW);
		status = 0;
	}

}

/**
 ******************************************************************************
 ** \brief Callback Function for DT channel 1
 **
 ******************************************************************************/
static void Dt1Callback(void)
{
	static int status =0;
	if(status ==0)
	{
		Dt_ClrIntFlag(DtChannel0);    // Clear Irq
		u32CountDt0++;
		WyzBeeGpio_Init(GPIO_LED2,GPIO_OUTPUT,GPIO_HIGH);
		status = 1;
	}
	else
	{
		WyzBeeGpio_Put(GPIO_LED2,GPIO_LOW);
		status = 0;
	}

}
int main(void)
{
	err_t err;

	Dual_Timer.u8Mode = Dt_Periodic;
	Dual_Timer.u8PrescalerDiv = Dt_PrescalerDiv16;
	Dual_Timer.u8CounterSize =  Dt_CounterSize32;

	u32CountDt0 = 0;
	u32CountDt1 = 0;

	err = WyzBeeDualTimer_Init(Dual_Timer,Dt_Channel0);
	err = WyzBeeDualTimer_Init(Dual_Timer,Dt_Channel1);

	err = WyzBeeDualTimer_LoadTime(5000000,Dt_Channel0);							//5000000 value signifies a time of 1sec (pll clk 80Mhz/prescalar value 80/16=5Mhz (1/5Mhz=t) (reload value= no of sec or ms /t))
	err = WyzBeeDualTimer_Attach_Callback(Dt0Callback,Dt_Channel0);

	err = WyzBeeDualTimer_LoadTime(25000000,Dt_Channel1);					    	//25000000 value signifies a time of 5sec
	err = WyzBeeDualTimer_Attach_Callback(Dt1Callback,Dt_Channel1);

	while(1);

}
/*
 *********************************************************************************************************
 *                                           END
 *********************************************************************************************************
 */