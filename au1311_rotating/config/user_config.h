/**
  ******************************************************************************
  * @file           : user_config.h
  * @brief          : This file contains the user config defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 Phoenisoar Technology
  * All rights reserved.
  *
  * This software component is licensed by Phoenisoar Technology under Apache Licence 2.0.
  * You may not use this file except in compliance with the License. 
	* For more details, please refer to http://www.apache.org/licenses/LICENSE-2.0.txt
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USER_CONFIG_H
#define __USER_CONFIG_H

#define USE_AU1311      2

#define AU_DUT_NUMS     (9)
#define REF_DUT_NUMS    (2)

#define AU_INT_ODR      (1) //use int as odr clk

#define REF_DUT1        (AU_DUT_NUMS)
#define REF_DUT2        (AU_DUT_NUMS+1)

#define REF_NOISE_GET   (1)

/* Modbus */
#define MB_SLAVE_ADDRESS    0x0A
#define MB_SLAVE_ID         0x34
#define MB_PORT_INDEX       0x02
//#define MB_PORT_RATE        9600
#define MB_PORT_RATE        115200

/* Clock */
#define USE_HSE_12_288          0

#endif /* __USER_CONFIG_H */
