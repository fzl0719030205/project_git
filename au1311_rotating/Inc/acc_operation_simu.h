/**
  ******************************************************************************
  * @file           : acc_operation.h
  * @brief          : This file contains the common definition of process.
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
#ifndef __ACC_OP_H
#define __ACC_OP_H

#ifdef __cplusplus
extern "C" {
#endif /*_cplusplus*/

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
#include "common_def.h"
#include "user_config.h"

#include "bma280.h"
#include "lsm6dsr.h"
#include "au13xx.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
    uint32_t I2C_Timing;
    uint8_t SlaveConfigPort;
    __IO uint16_t Reg_ODR;
    __IO uint16_t ID_map;
    __IO uint8_t ID_idx;
    uint32_t last_ms;
    uint8_t Data_bit;
    uint8_t* acc_buffer;
    uint16_t* sts_buffer;
} ACC_ConfigDef;


/* Exported constants --------------------------------------------------------*/
extern ACC_ConfigDef ACC_Conifg;

/* Exported macro ------------------------------------------------------------*/
//#define PLAY_BUFF_SIZE       4096
//#define PLAY_BUFF_SIZE       4098
#define PLAY_BUFF_SIZE       4320
//#define PLAY_BUFF_SIZE       9600


#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

//#define I2C_TIMING      0x90841F27      //100KHz
//#define I2C_TIMING_400K 0x40310917
//#define I2C_TIMING_1M   0x40000306

//#define SPI_TIMING_5M   SPI_BAUDRATEPRESCALER_16 
//#define SPI_TIMING_10M  SPI_BAUDRATEPRESCALER_8
//#define SPI_TIMING_20M  SPI_BAUDRATEPRESCALER_4

#define SPI_REG_ODR_250 320
#define SPI_REG_ODR_500 160
#define SPI_REG_ODR_1K  80
#define SPI_REG_ODR_2K  40
#define SPI_REG_ODR_4K  20


#define SPI_READ_TAG    0x80

#define SLAVE_PORT_I2C      0x00
#define SLAVE_PORT_SPI      0x01

#define TDM_AUDIO_FREQUENCY_24K     24000U

#define ACC_ID_MAP_ALL      0xFFFF

#define ACC_DATA_16         0
#define ACC_DATA_24         1

#define ACC_NUMS            (AU_DUT_NUMS+REF_DUT_NUMS)

/* Exported functions --------------------------------------------------------*/

void Acc_I2C_Init(void);

void Acc_DUT_Init(void);

HAL_StatusTypeDef ACC_GetID(uint8_t idx, uint8_t* id);

HAL_StatusTypeDef ACC_CheckID(uint8_t idx, uint8_t id);

HAL_StatusTypeDef Acc_ResetDevice(uint8_t idx);

HAL_StatusTypeDef Acc_SetInitConfig(uint8_t idx);

HAL_StatusTypeDef Acc_RegisterRead(uint8_t idx, uint8_t reg, uint8_t *data, uint16_t len);

HAL_StatusTypeDef Acc_RegisterWrite(uint8_t idx, uint8_t reg, uint8_t *data, uint16_t len);

HAL_StatusTypeDef Acc_StopMeasure(uint8_t idx);

HAL_StatusTypeDef Acc_StartMeasure(uint8_t idx);

HAL_StatusTypeDef ACC_ReadData(uint8_t idx, uint8_t* buffer, uint32_t Timeout);

HAL_StatusTypeDef ACC_UpdateData(uint8_t* buffer);

void ACC_Refresh(void);

HAL_StatusTypeDef ACC_RegTimerInit(void);

#ifdef __cplusplus
}
#endif /*_cplusplus*/

#endif /* __ACC_OP_H */
