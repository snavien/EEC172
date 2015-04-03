
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
 * Description    : In This example clock pulse can be observed by changing the frequnecy and duty cycle.
 *********************************************************************************************************
 * Note(s)		 :
 *********************************************************************************************************
 */
 
 /*
 * Includes
 */

#include <WyzBee_pwm.h>


/*! \brief Interrupt count value */
static uint32_t m_u32CntIntTrg, m_u32CntIntDuty, m_u32CntIntUnder;

static void PwmDutyMatchIntHandler(void);
static void PwmUnderflowIntHandler(void);
static void PwmTrigIntHandler(void);
static void Delay(void);

int main(void)
{

	uint32_t u32Cnt=0;
	Error_Value err;


	WyzBeePWM_Timer_Config_t    PWM_Timer = {Presclr_Div4,  					// PWM clock = 20MHz @ PCLK = 80MHz
			Restart_Enable,
			Output_Normal,
			ExtTrig_Disable,
			Polarity_Low,
			Continuous

	};

	WyzBeePWM_Interrupt_Config_t  PWM_Interrupt = {1,1,1};

	WyzBeePWM_Interrupt_Callback_t PWM_Callback = {PwmTrigIntHandler,
			PwmDutyMatchIntHandler,
			PwmUnderflowIntHandler};

	WyzBeePWM_Select_PWMPin(0);
	WyzBeePWM_Select_BaseTimer(0,Bt_IoMode0,Bt_PwmMode,&BT_TIMER(0));	//BT = 0 or BT =1 only can be selected

	WyzBeePWM_Init_Timer(&PWM_Timer, &BT_TIMER(0));

	WyzBeePWM_Config_DutyCycle(5,10, &BT_TIMER(0));							//frequency  in KHz and duty cycle in %

	WyzBeePWM_Config_InterruptCallback(&PWM_Interrupt, &PWM_Callback, &BT_TIMER(0));

	WyzBeePWM_Start_PWM(&BT_TIMER(0));

	Delay();					 											    // Delay some time

	WyzBeePWM_DisableInt(&BT_TIMER(0), &PWM_Interrupt); // Disable Interrupt
	Delay();
	WyzBeePWM_EnableSwTrig(&BT_TIMER(0));// Restart triggered by software
	m_u32CntIntTrg = 0;
	m_u32CntIntDuty = 0;
	m_u32CntIntUnder = 0;

	do																		    // Interrupt query mode
	{
		if (Bt_Pwm_GetIntFlag(&BT_TIMER(0), PwmTrigInt) == PdlSet)
		{
			Bt_Pwm_ClrIntFlag(&BT_TIMER(0), PwmTrigInt);
			m_u32CntIntTrg++;
		}
		else if (Bt_Pwm_GetIntFlag(&BT_TIMER(0), PwmDutyMatchInt) == PdlSet)
		{
			Bt_Pwm_ClrIntFlag(&BT_TIMER(0), PwmDutyMatchInt);
			m_u32CntIntDuty++;
		}
		else if (Bt_Pwm_GetIntFlag(&BT_TIMER(0), PwmUnderflowInt) == PdlSet)
		{
			Bt_Pwm_ClrIntFlag(&BT_TIMER(0), PwmUnderflowInt);
			m_u32CntIntUnder++;
		}
		u32Cnt++;
	} while(u32Cnt <2500000UL);




	while(1);



}

static void PwmDutyMatchIntHandler(void)
{
	m_u32CntIntDuty++;
}


static void PwmUnderflowIntHandler(void)
{
	m_u32CntIntUnder++;
}


static void PwmTrigIntHandler(void)
{
	m_u32CntIntTrg++;
}


static void Delay(void)
{
	int32_t u8Cnt1,u8Cnt2;
	//    u8Cnt2 = SystemCoreClock;
	u8Cnt2 = 10000;

	u8Cnt1 = 0;
	while (1)
	{
		u8Cnt1++;
		if (u8Cnt1 > u8Cnt2)
		{
			break;
		}
	}
}

/*
 *********************************************************************************************************
 *                                           END
 *********************************************************************************************************
 */
