******************************************ReadMe Note******************************************

 
                 (c) Copyright 2015-2020 Redpine Signals Inc. HYDERABAD, INDIA
                                       All rights reserved.
 
     This file is protected by international copyright laws. This file can only be used in
     accordance with a license and should not be redistributed in any way without written
     permission by Redpine Signals.
 
									www.redpinesignals.com

===============================================================================================
                               External Interrupt example program
===============================================================================================

===============================================================================================
History 
Date        Ver     
2015-03-16  1.2    
===============================================================================================                                                       
Project description:
===============================================================================================
Demo External Interrupt with on board push button

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
1. External Interrupt in this demo is configured with the on board push button.

2. Every time the callback function 'Main_ExtIntCallback1()' hits, the Blue LED toggles.

3. INT11 pin on the host MCU is connected to the push button.

4. Whenever there is an Interrupt, 'Main_ExtIntCallback1()' is called and toggles the LED.

===============================================================================================