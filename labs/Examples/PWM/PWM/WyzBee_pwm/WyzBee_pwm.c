/*
 *********************************************************************************************************
 *
 *                (c) Copyright 2015 Redpine Signals
 *                                           All rights reserved.
 *
 *               This file is protected by international copyright laws. This file can only be used in
 *               accordance with a license and should not be redistributed in any way without written
 *               permission by Redpine Signals.
 *
 *                                            www.redpinesignals.com
 *
 **************************************************************************************************************
 */

/*
 *********************************************************************************************************
 *
 *                                        PWM Driver Source File
 *
 * File           : WyzBee_pwm.c
 * Version        : V1.00
 * Programmer(s)  :
 *********************************************************************************************************
 * Note(s)        :
 *********************************************************************************************************
 */


/*
 *********************************************************************************************************
 *                                              INCLUDE FILES
 *********************************************************************************************************
 */

#include  <WyzBee_pwm.h>
#include <bt.h>


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
 *                                         LOCAL GLOBAL VARIABLES
 *********************************************************************************************************
 */



/*
 *********************************************************************************************************
 *                                         GLOBAL VARIABLES
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
 *                                           WyzBeePWM_Init_Timer()
 *
 * Description :initializes the PWM Timer
 *
 * Argument(s) :p_pwmtimer   base timer configuration structure
 *             :p_bt         base timer to select
 * Return(s)   :error value
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */

err_t WyzBeePWM_Init_Timer(WyzBeePWM_Timer_Config_t*  p_pwmtimer, base_timer_t* p_bt)
{
	stc_bt_pwm_config_t   PwmTimer_Internal;
	err_t  err;

	PwmTimer_Internal.enPres = 			p_pwmtimer->enPres;  			    // PWM clock = 20MHz @ PCLK = 80MHz
	PwmTimer_Internal.enRestartEn = 		p_pwmtimer->enRestartEn;
	PwmTimer_Internal.enOutputMask = 		p_pwmtimer->enOutputMask;
	PwmTimer_Internal.enExtTrig = 			p_pwmtimer->enExtTrig;
	PwmTimer_Internal.enOutputPolarity =   p_pwmtimer->enOutputPolarity;
	PwmTimer_Internal.enMode = 			p_pwmtimer->enMode;

	err = Bt_Pwm_Init(p_bt, &PwmTimer_Internal);

	if(err == Ok) return ERR_NONE;
	else  return ERR_INVALID_PARMS;


}

/*
 *********************************************************************************************************
 *                                           WyzBeePWM_Config_InterruptCallback()
 *
 * Description :initializes PWM Timer callback functions
 *
 * Argument(s) :p_pwminterrupt  interrupt structure to configure types interrupts
 *             :p_pwmcallback   interrupt callback structure to initialize callback functions
 *             :p_bt   selected base timer
 * Return(s)   :error value
 *
 * Caller(s)   :
 *
 *
 * Note(s)     :
 *********************************************************************************************************
 */

err_t WyzBeePWM_Config_InterruptCallback(WyzBeePWM_Interrupt_Config_t* p_pwminterrupt, WyzBeePWM_Interrupt_Callback_t* p_pwmcallback, base_timer_t* p_bt)
{

	stc_pwm_int_sel_t   PwmInterrupt_Internal;
	stc_pwm_int_cb_t    PwmCallback_Internal;
	err_t  err;


	PwmInterrupt_Internal.bPwmTrigInt = 				p_pwminterrupt->bPwmTrigInt;
	PwmInterrupt_Internal.bPwmDutyMatchInt = 			p_pwminterrupt->bPwmDutyMatchInt;
	PwmInterrupt_Internal.bPwmUnderflowInt = 			p_pwminterrupt->bPwmUnderflowInt;

	PwmCallback_Internal.pfnPwmTrigIntCallback = 		p_pwmcallback->pfnPwmTrigIntCallback;
	PwmCallback_Internal.pfnPwmDutyMatchIntCallback =  p_pwmcallback->pfnPwmDutyMatchIntCallback;
	PwmCallback_Internal.pfnPwmUnderflowIntCallback =  p_pwmcallback->pfnPwmUnderflowIntCallback;

	err = Bt_Pwm_EnableInt(p_bt, &PwmInterrupt_Internal, &PwmCallback_Internal);

	if( err ==  Ok) return ERR_NONE;
	else return ERR_INVALID_PARMS;
}

/*
 *********************************************************************************************************
 *                                           WyzBeePWM_Select_BaseTimer()
 *
 * Description :Select and initialize the base timer
 *
 * Argument(s) :bt_number select the base timer
 *             :io_mode   configure the selected base timer io mode
 *             :timer_mode configure the base timer in timer mode
 *             :p_bt      base timer for the selected bt_number
 * Return(s)   :error value
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */


err_t WyzBeePWM_Select_BaseTimer(uint8_t bt_number,en_WyzBee_bt_io_mode_t io_mode, en_WyzBee_bt_timer_mode_t timer_mode, base_timer_t* p_bt)
{

	if((bt_number == 0)||(bt_number==1))

	{
		Bt_ConfigIOMode(p_bt, io_mode);
		Bt_SelTimerMode(p_bt, timer_mode);

		return ERR_NONE;
	}

	if(bt_number > 1)
	{
		return ERR_INVALID_PARMS;
	}

}


/*
 *********************************************************************************************************
 *                                           WyzBeePWM_Select_PWMPin()
 *
 * Description :Associates MCU pin to PWM Timer
 *
 * Argument(s) :pwm_pin configure the base timer to the optional pins to associate
 *
 * Return(s)   :error value
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */

err_t WyzBeePWM_Select_PWMPin(uint8_t  pwm_pin)
{

	if(pwm_pin == 0) { SetPinFunc_TIOA0_0_OUT(); return ERR_NONE;}
	if(pwm_pin == 1) { SetPinFunc_TIOA1_0_OUT(); return ERR_NONE;}

	return ERR_INVALID_PARMS;
}


/*
 *********************************************************************************************************
 *                                           WyzBeePWM_Config_DutyCycle()
 *
 * Description :Initialize the PWM Timer to the selected frequency and duty cycle
 *
 * Argument(s) :frequency frequency of pwm waveform
 *             :duty_cycle duty cycle of pwm waveform
 *             :p_bt  base timer to select
 * Return(s)   :error value
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */



err_t WyzBeePWM_Config_DutyCycle(uint16_t frequency, uint16_t duty_cycle, base_timer_t* p_bt)
{


	uint16_t  pwm_input_freq ;								/* PCLK is configured for 80 MHz      */
	uint16_t  cycle_value ;
	uint16_t  pwm_duty_cycle;
	err_t err;

	pwm_input_freq  = 20000;
	cycle_value= (pwm_input_freq/frequency);
	cycle_value = cycle_value - 1;

	err = Bt_Pwm_WriteCycleVal(p_bt, cycle_value);
	if(err != Ok) return ERR_INVALID_PARMS;


	pwm_duty_cycle = (cycle_value*duty_cycle)/100;

	err = Bt_Pwm_WriteDutyVal(p_bt, pwm_duty_cycle);


	if(err == Ok) return ERR_NONE;
	else return ERR_INVALID_PARMS;

}

/*
 *********************************************************************************************************
 *                                           WyzBeePWM_Start_PWM()
 *
 * Description :Start the PWM Timer after initialization
 *
 * Argument(s) :p_bt selected base timer
 *
 * Return(s)   :error value
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */



err_t WyzBeePWM_Start_PWM(base_timer_t* p_bt)
{

	err_t err;

	err = Bt_Pwm_EnableCount(p_bt);						// Enable count operation
	if(err != Ok) return ERR_INVALID_PARMS;

	err = Bt_Pwm_EnableSwTrig(p_bt);					    // Start triggered by software
	if(err == Ok) return ERR_NONE;
	else return ERR_INVALID_PARMS;



}

/*
 *********************************************************************************************************
 *                                           WyzBeePWM_EnableSwTrig()
 *
 * Description :Start the PWM Timer after initialization
 *
 * Argument(s) :p_bt selected base timer
 *
 * Return(s)   :error value
 *
 * Caller(s)   :
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeePWM_EnableSwTrig(base_timer_t* p_bt)
{

	err_t err;

	err = Bt_Pwm_EnableSwTrig(p_bt);					    // Start triggered by software
	if(err == Ok)
	{
		return ERR_NONE;
	}
	else
	{
		return ERR_INVALID_PARMS;
	}

}


/*
 *********************************************************************************************************
 *                                           WyzBeePWM_DisableInt()
 *
 * Description :initializes PWM Timer callback functions
 *
 * Argument(s) :p_bt   selected base timer
 *             :p_pwminterrupt  interrupt structure to configure types interrupts
 * Return(s)   :error value
 *
 * Caller(s)   :
 *
 *
 * Note(s)     :
 *********************************************************************************************************
 */
err_t WyzBeePWM_DisableInt( base_timer_t* p_bt,WyzBeePWM_Interrupt_Config_t* p_pwminterrupt)
{

	stc_pwm_int_sel_t    PwmCallback_Internal;
	err_t  err;

	err = Bt_Pwm_DisableInt(p_bt, &PwmCallback_Internal);

	if( err ==  Ok) return ERR_NONE;
	else return ERR_INVALID_PARMS;
}

