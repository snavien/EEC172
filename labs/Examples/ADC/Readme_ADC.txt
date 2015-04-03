*******************************************ReadMe Note******************************************

 
                 (c) Copyright 2015-2020 Redpine Signals Inc. HYDERABAD, INDIA
                                       All rights reserved.
 
     This file is protected by international copyright laws. This file can only be used in
     accordance with a license and should not be redistributed in any way without written
     permission by Redpine Signals.
 
									www.redpinesignals.com
===============================================================================================
                               ADC example program
===============================================================================================

===============================================================================================
History 
Date        Ver     
2015-03-16  1.2    
===============================================================================================                                                       
Project description:
===============================================================================================
Demo ADC conversion with interrupt polling

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
3) Break and check the sampled FIFO data which is stored in the global variable "AdcValue"

===============================================================================================
Notice:
===============================================================================================
1. ADC in WyzBee detects maximum readings of 4095(i.e. 3.3V) and minimum readings of 0(i.e. 0V).

2. User can change the configuration structure for changing the ADC functionality.

3. In 'MyAdc_conversion_callback()' the ADC reads the value and stores it to the variable 'AdcValue'.

4. Whenever there is value read Interrupt notification flag is set.

5. 'AdcFinished' confirms the setting of the interrupt notification flag.

6. After checking the status of 'AdcFinished' user can access the converted data.

===============================================================================================