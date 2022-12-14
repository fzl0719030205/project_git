/**
  ******************************************************************************
  * @file           : iic_sim.h
  * @brief          : This file contains the iic simulator.
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
#ifndef __IIC_SIMU_H
#define __IIC_SIMU_H

#ifdef __cplusplus
extern "C" {
#endif /*_cplusplus*/

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
#include "common_def.h"
#include "user_config.h"
  
/* Exported types ------------------------------------------------------------*/
typedef struct
{
    uint8_t         Slave_Addr;
    uint32_t        I2C_Timing;
    GPIO_TypeDef*   SCL_GPIOx;
    uint32_t        SCL_Pin;
    GPIO_TypeDef*   SDA_GPIOx;
    uint32_t        SDA_Pin;
} I2C_PortDef;

/* Exported constants --------------------------------------------------------*/
#define I2C_TIMING_100K      4
#define I2C_TIMING_200K      2

#define I2C_WRITE            0u
#define I2C_READ             1u

#define I2C_BYTE_TIMEOUT      10u

#define I2C_PIN_MODE          GPIO_MODE_OUTPUT_OD

/* Exported macro ------------------------------------------------------------*/
#define ENTER_CRITICAL()
#define EXIT_CRITICAL()

/* Exported functions --------------------------------------------------------*/
void I2C_SimInit(I2C_PortDef* port);

HAL_StatusTypeDef I2C_SimWrite(I2C_PortDef* port, uint8_t addr, 
                               uint8_t *data, uint32_t len, uint32_t Timeout);

HAL_StatusTypeDef I2C_SimRead(I2C_PortDef* port, uint8_t addr, 
                              uint8_t *data, uint32_t len, uint32_t Timeout);

HAL_StatusTypeDef I2C_SimMemWrite(I2C_PortDef* port, uint8_t addr, 
                                  uint8_t *memAddr, uint32_t memAddrLen,
                                  uint8_t *data, uint32_t len, uint32_t Timeout);

HAL_StatusTypeDef I2C_SimMemRead(I2C_PortDef* port, uint8_t addr, 
                                 uint8_t *memAddr, uint32_t memAddrLen,
                                 uint8_t *data, uint32_t len, uint32_t Timeout);


#ifdef __cplusplus
}
#endif /*_cplusplus*/

#endif /* __IIC_SIMU_H */
