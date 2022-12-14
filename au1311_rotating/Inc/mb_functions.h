/**
  ******************************************************************************
  * @file           : mb_functions.h
  * @brief          : This file contains the Modbus functions.
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
#ifndef __MB_FUNCTIONS_H
#define __MB_FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif /*_cplusplus*/

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
#include "common_def.h"
#include "user_config.h"

#include "mb.h"
#include "mbport.h"
  
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
HAL_StatusTypeDef ACC_MbInit(void);

HAL_StatusTypeDef ACC_MbEnable(void);

HAL_StatusTypeDef ACC_MbDisable(void);

void ACC_MbPoll(void);

void Acc_MbUpdateStatus(void);


#ifdef __cplusplus
}
#endif /*_cplusplus*/

#endif /* __MB_FUNCTIONS_H */
