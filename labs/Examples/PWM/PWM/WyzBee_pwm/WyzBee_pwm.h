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
*                                        PWM Driver Header File
*
* File           : WyzBee_pwm.h
* Version        : V1.00
* Programmer(s)  :
*********************************************************************************************************
* Note(s)        :
*********************************************************************************************************
*/


#ifndef  WyzBee_PWM_H
#define  WyzBee_PWM_H


/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/

#include   <WyzBee.h>
#include   <bt.h>


/*
*********************************************************************************************************
*                                                 DEFINES
*********************************************************************************************************
*/


#define       BT_TIMER(n)	          BT##n
typedef       stc_btn_t               USER_BT;
typedef       stc_btn_t               base_timer_t;
typedef       en_result_t             Error_Value;



/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/



typedef enum en_WyzBee_pwm_clock_prescaler                  	/*------------------PWM CLOCK PRESCALER----------------------*/
{
    Presclr_None = 0,                                         // PWM prescaler clock: no division
    Presclr_Div4,                                             // PWM prescaler clock: 1/4
    Presclr_Div16,                                            // PWM prescaler clock: 1/16
    Presclr_Div128,                                           // PWM prescaler clock: 1/128
    Presclr_Div256,                                           // PWM prescaler clock: 1/256
    Presclr_ExtClkRising,                                     // Use external clock and count at rising edge
    Presclr_ExtClkFalling,                                    // Use external clock and count at falling edge
    Presclr_ExtClkBoth,                                       // Use external clock and count at both edge
    Presclr_Div512,                                           // PWM prescaler clock: 1/512
    Presclr_Div1024,                                          // PWM prescaler clock: 1/1024
    Presclr_Div2048,                                          // PWM prescaler clock: 1/2048

}en_WyzBee_pwm_clock_prescaler_t;


typedef enum en_WyzBee_pwm_restart_enable                       	/*------------------PWM RESTART----------------------*/
{
    Restart_Disable = 0,                                       // Disable PWM restart
    Restart_Enable,                                            // Enable PWM restart

}en_WyzBee_pwm_restart_enable_t;


typedef enum en_WyzBee_pwm_output_mask                           	/*------------------PWM OUTPUT ----------------------*/
{
    Output_Normal = 0,                                          // Output normal PWM wave
    Output_Mask,                                                // Mask PWM wave

}en_WyzBee_pwm_output_mask_t;



typedef enum en_WyzBee_pwm_ext_trig                              	/*------------------PWM EXTERNAL TRIGGER----------------------*/
{
    ExtTrig_Disable = 0,                                         // Disable external trigger
    ExtTrig_Rising,                                              // Enable external trigger with rising edge
    ExtTrig_Falling,                                             // Enable external trigger with falling edge
    ExtTrig_Both,        									                     	 // Enable external trigger with both edge

}en_WyzBee_pwm_ext_trig_t;


typedef enum en_WyzBee_pwm_output_polarity                     	/*------------------PWM OUTPUT POLARITY----------------------*/        
{
    Polarity_Low = 0,                                             // Initial polarity: low
    Polarity_High,     											                      // Initial polarity: high

}en_WyzBee_pwm_output_polarity_t;


typedef enum en_WyzBee_pwm_mode                                	/*------------------PWM MODE ----------------------*/
{
    Continuous = 0,   											                       // Continuous mode
    Oneshot,          											                       // One-shot mode

}en_WyzBee_pwm_mode_t;



typedef struct WyzBeePWM_Timer_Config                         	/*------------------PWM TIMER CONFIGURATION----------------------*/
{
    en_WyzBee_pwm_clock_prescaler_t         enPres;                // Clock prescaler
    en_WyzBee_pwm_restart_enable_t          enRestartEn;           // Restart enable setting
    en_WyzBee_pwm_output_mask_t             enOutputMask;          // PWM output mask setting
    en_WyzBee_pwm_ext_trig_t                enExtTrig;             // PWM external trigger setting
    en_WyzBee_pwm_output_polarity_t         enOutputPolarity;      // PWM output polarity setting
    en_WyzBee_pwm_mode_t                    enMode;                // Continuous mode or one-shot mode

}WyzBeePWM_Timer_Config_t;


typedef struct WyzBeePWM_Interrupt_Config                     	/*------------------PWM INTERRUPT CONFIGURATION----------------------*/
{
    boolean_t bPwmTrigInt;        									// Trigger interrupt selection
    boolean_t bPwmDutyMatchInt;   									// Duty match interrupt selection
    boolean_t bPwmUnderflowInt;   									// Underflow interrupt selection

}WyzBeePWM_Interrupt_Config_t;


typedef struct WyzBeePWM_Interrupt_Callback               	/*------------------PWM INTERRUPT CALLBACK----------------------*/
{
    func_ptr_t pfnPwmTrigIntCallback;      							// Pointer to trigger interrupt callback function
    func_ptr_t pfnPwmDutyMatchIntCallback; 							// Pointer to duty match interrupt callback function
    func_ptr_t pfnPwmUnderflowIntCallback; 							// Pointer to underflow interrupt callback function

}WyzBeePWM_Interrupt_Callback_t;


typedef enum en_WyzBee_bt_io_mode                     	/*------------------PWM BT I/O MODE----------------------*/
{
    Bt_IoMode0 = 0,           										// BT IO mode 0
    Bt_IoMode1,               										// BT IO mode 1
    Bt_IoMode2,               										// BT IO mode 2
    Bt_IoMode3,               										// BT IO mode 3
    Bt_IoMode4,               										// BT IO mode 4
    Bt_IoMode5,               										// BT IO mode 5
    Bt_IoMode6,               										// BT IO mode 6
    Bt_IoMode7,               										// BT IO mode 7
    Bt_IoMode8,               										// BT IO mode 8

}en_WyzBee_bt_io_mode_t;


typedef enum en_WyzBee_bt_timer_mode                   	/*------------------PWM BT TIMER MODE----------------------*/
{
    Bt_ResetMode = 0,        										// Reset mode
    Bt_PwmMode,              										// PWM timer mode
    Bt_PpgMode,              										// PPG timer mode
    Bt_RtMode,               										// Reload timer mode
    Bt_PwcMode,              										// PWC timer mode

}en_WyzBee_bt_timer_mode_t;




/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/


err_t WyzBeePWM_Init_Timer(WyzBeePWM_Timer_Config_t*  p_pwmtimer, base_timer_t* p_bt);

err_t WyzBeePWM_Config_InterruptCallback(WyzBeePWM_Interrupt_Config_t* p_pwminterrupt, WyzBeePWM_Interrupt_Callback_t* p_pwmcallback, base_timer_t* p_bt);

err_t WyzBeePWM_Select_BaseTimer(uint8_t bt_number ,en_WyzBee_bt_io_mode_t io_mode, en_WyzBee_bt_timer_mode_t timer_mode, base_timer_t* p_bt);

err_t WyzBeePWM_Select_PWMPin(uint8_t  pwm_pin);

err_t WyzBeePWM_Config_DutyCycle(uint16_t frequency, uint16_t duty_cycle, base_timer_t* p_bt);

err_t WyzBeePWM_Start_PWM(base_timer_t* p_bt);

err_t WyzBeePWM_EnableSwTrig(base_timer_t* p_bt);

err_t WyzBeePWM_DisableInt( base_timer_t* p_bt,WyzBeePWM_Interrupt_Config_t* p_pwminterrupt);



/*
*********************************************************************************************************
*                                           END
*********************************************************************************************************
*/


#endif // WyzBee_PWM__H
