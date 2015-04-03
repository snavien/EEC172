******************************************ReadMe Note******************************************

 
                 (c) Copyright 2015-2020 Redpine Signals Inc. HYDERABAD, INDIA
                                       All rights reserved.
 
     This file is protected by international copyright laws. This file can only be used in
     accordance with a license and should not be redistributed in any way without written
     permission by Redpine Signals.
 
									www.redpinesignals.com

===============================================================================================
									Timer example program
===============================================================================================

===============================================================================================
History 
Date        Ver     
2015-03-16  1.2    
===============================================================================================                                                       
Project description:
===============================================================================================
Demo showing Dual Timer	implementation for blinking LED with delay

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
2) Rebuild and run
3) Break and check the LED outputs.

===============================================================================================
Notice:
===============================================================================================
1. This demo shows the use of timer by blinking Blue and Red LED on board.

2. In This example 2 timers are used.Depending on the load time timer callbacks will be called.

3. Configuration values consisting of mode, pre-scalar value and the counter size can be set.

4. Channel 10 introduces a timer value of 1 second and blinks Blue LED and Channel 11 introduces 5 seconds and binks Red LED.

===============================================================================================