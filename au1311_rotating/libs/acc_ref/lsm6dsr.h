/**
  ******************************************************************************
  * @file           : lsm6dsr.h
  * @brief          : lsm6dsr driver header file
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
#ifndef __LSM6DSR_H
#define __LSM6DSR_H

#ifdef __cplusplus
extern "C" {
#endif /*_cplusplus*/

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "string.h"

/* Private includes ----------------------------------------------------------*/
#include "common_def.h"
#include "user_config.h"
  
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** Device Identification (Who am I) **/
#define LSM6DSR_ID                           0x6BU

#define LSM6DSR_WHO_AM_I                     0x0FU
#define LSM6DSR_CTRL1_XL                     0x10U
#define LSM6DSR_CTRL3_C                      0x12U
#define LSM6DSR_CTRL8_XL                     0x17U
#define LSM6DSR_CTRL9_XL                     0x18U
#define LSM6DSR_STATUS_REG                   0x1EU
#define LSM6DSR_OUT_TEMP_L                   0x20U
#define LSM6DSR_OUT_TEMP_H                   0x21U
#define LSM6DSR_OUTX_L_G                     0x22U
#define LSM6DSR_OUTX_H_G                     0x23U
#define LSM6DSR_OUTY_L_G                     0x24U
#define LSM6DSR_OUTY_H_G                     0x25U
#define LSM6DSR_OUTZ_L_G                     0x26U
#define LSM6DSR_OUTZ_H_G                     0x27U
#define LSM6DSR_OUTX_L_A                     0x28U
#define LSM6DSR_OUTX_H_A                     0x29U
#define LSM6DSR_OUTY_L_A                     0x2AU
#define LSM6DSR_OUTY_H_A                     0x2BU
#define LSM6DSR_OUTZ_L_A                     0x2CU
#define LSM6DSR_OUTZ_H_A                     0x2DU
#define LSM6DSR_EMB_FUNC_STATUS_MAINPAGE     0x35U
#define LSM6DSR_I3C_BUS_AVB                  0x62U
  

#define BDU_SET                              0x40U  
#define SW_RESET                             0x01U
#define I3C_DISABLE                          0x02U
#define XL_DATA_RATE_MASK                    0x0FU
#define LSM6DSR_XL_ODR_416Hz                 0x60U
#define LSM6DSR_XL_ODR_DISABLE               0x00U
#define XL_DATA_VALID                        0x01U
  
/* Exported macro ------------------------------------------------------------*/
#define Lsm6dsr_CtxDef Acc_CtxDef

/* Exported functions --------------------------------------------------------*/
int32_t Lsm6dsr_GetID(Lsm6dsr_CtxDef* ctx, uint8_t* id);

int32_t Lsm6dsr_SoftReset(Lsm6dsr_CtxDef* ctx);

int32_t Lsm6dsr_WriteReg(Lsm6dsr_CtxDef* ctx, uint8_t reg_addr, 
                     uint8_t* reg_data, uint8_t cnt);

int32_t Lsm6dsr_ReadReg(Lsm6dsr_CtxDef* ctx, uint8_t reg_addr, 
                     uint8_t* reg_data, uint8_t cnt);

int32_t  Lsm6dsr_I3cDisable(Lsm6dsr_CtxDef* ctx);

int32_t  Lsm6dsr_BDU_set(Lsm6dsr_CtxDef* ctx);

int32_t Lsm6dsr_XL_DataRateSet(Lsm6dsr_CtxDef* ctx, uint8_t rate);


#ifdef __cplusplus
}
#endif /*_cplusplus*/

#endif /* __LSM6DSR_H */
