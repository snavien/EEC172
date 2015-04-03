******************************************ReadMe Note******************************************

 
                 (c) Copyright 2015-2020 Redpine Signals Inc. HYDERABAD, INDIA
                                       All rights reserved.
 
     This file is protected by international copyright laws. This file can only be used in
     accordance with a license and should not be redistributed in any way without written
     permission by Redpine Signals.
 
									www.redpinesignals.com

===============================================================================================
                               PWM functionality example program
===============================================================================================

===============================================================================================
History 
Date        Ver     
2015-03-16  1.2    
===============================================================================================                                                       
Project description:
===============================================================================================
Demo showing the PWM use by changing its duty cycle

===============================================================================================
Environment
===============================================================================================
Test Board:
---------------------
WyzBee

Assistance tool:
---------------------
None

Assistance software:
---------------------
None

===============================================================================================
Usage Procedure:
===============================================================================================
1) Connect WyzBee.
2) Connect an external LED or a logic analyser to the PWM1 (P12) pin. 
2) Rebuild and run
3) Break and check the brightness of LED or the pulses in logic analyser.

===============================================================================================
Notice:
===============================================================================================
1. PWM is tested here using the expansion header pin on WyzBee.

2. 'WyzBeePWM_Timer_Config_t' structure sets the configuration data for PWM.

3. Three callback functions are being used in this demo. In This example clock pulse can be observed by changing the frequnecy and duty cycle.

4. On varying the frequency and the duty cycle the intensity of LED varies. The pulse width variation can also be observed using a logic analyser.

===============================================================================================