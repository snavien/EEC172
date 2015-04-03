******************************************ReadMe Note******************************************

 
                 (c) Copyright 2015-2020 Redpine Signals Inc. HYDERABAD, INDIA
                                       All rights reserved.
 
     This file is protected by international copyright laws. This file can only be used in
     accordance with a license and should not be redistributed in any way without written
     permission by Redpine Signals.
 
									www.redpinesignals.com

===============================================================================================
                               I2C Communication example program
===============================================================================================

===============================================================================================
History 
Date        Ver     
2015-03-16  1.2    
===============================================================================================                                                       
Project description:
===============================================================================================
Demo to exhibit I2C peripheral APIs to sense the Temperature and Humidity sensor data

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
3) Break and check the ambient temperature and the relative humidity.

===============================================================================================
Notice:
===============================================================================================
1. I2C lines of WyzBee are connected to the Temperature and Humidity sensor and many other sensors.

2. I2C lines needs to be configured by giving suitable data rate and mode in the structure 'WyzBeeI2c_Config_t'. 

3. After initialising the I2C lines, registers data of the sensor are accessed using its slave address, i.e. 0x40.

4. Raw data is then manipulated in formulas to calculate the correct ambience readings.

5. User is expected to understand the flow of APIs.

===============================================================================================