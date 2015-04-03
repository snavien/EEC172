******************************************ReadMe Note******************************************

 
                 (c) Copyright 2015-2020 RedPine Signals Inc. HYDERABAD, INDIA
                                       All rights reserved.
 
     This file is protected by international copyright laws. This file can only be used in
     accordance with a license and should not be redistributed in any way without written
     permission by Redpine Signals.
 
									www.redpinesignals.com

===============================================================================================
									  UART example program
===============================================================================================

===============================================================================================
History 
Date        Ver     
2015-03-16  1.2    
===============================================================================================                                                       
Project description:
===============================================================================================
Demo showing UART loopback implementation.

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
2) Connect UART_IN and UART_OUT lines externally
2) Rebuild and run
3) Break and check the data on the MISO and MOSI lines.

===============================================================================================
Notice:
===============================================================================================
1. UART here can be tested using polling and interrupt method. User can enable the desired Macro.

2. 'WyzBeeUart_Config_t' structure is given proper configuration data.

3. Two callback function is defined for read and write from the UART lines.

4. External wires between MISO and MOSI is used for standalone testing of UART peripheral.

===============================================================================================