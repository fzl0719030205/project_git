/**
  ******************************************************************************
  * @file           : au13xx.h
  * @brief          : au13xx driver header file
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
#ifndef __AU13XXX_H
#define __AU13XXX_H

#ifdef __cplusplus
extern "C" {
#endif /*_cplusplus*/

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "string.h"

/* Private includes ----------------------------------------------------------*/
#include "common_def.h"
#include "user_config.h"
#include "au_reg.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define Au_CtxDef Acc_CtxDef

/* Exported functions --------------------------------------------------------*/
int32_t Au_GetID(Au_CtxDef* ctx, uint8_t* id);

int32_t Au_SoftReset(Au_CtxDef* ctx);

int32_t Au_WriteReg(Au_CtxDef* ctx, uint8_t reg_addr, 
                     uint8_t* reg_data, uint8_t cnt);

int32_t Au_ReadReg(Au_CtxDef* ctx, uint8_t reg_addr, 
                     uint8_t* reg_data, uint8_t cnt);

#ifdef __cplusplus
}
#endif /*_cplusplus*/

#endif /* __AU13XXX_H */
