/**
  ******************************************************************************
  * @file           : mb_command.h
  * @brief          : This file contains the Modbus command.
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
#ifndef __MB_CMD_H
#define __MB_CMD_H

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
typedef struct
{
    uint8_t cmd;
    uint8_t seq;
    uint8_t* buffer;
    uint8_t* status;
    uint8_t* acc_data;
    uint16_t* sts_data;
} Mb_CmdParaDef;

/* Exported constants --------------------------------------------------------*/
#define APDU_BUFFER_SIZE        256U

#if REF_NOISE_GET
#define MAX_CALC_SIZE           5000U
#else
#define MAX_CALC_SIZE           200U
#endif

#define CMD_WRITE_REGISTER_S    0x04U
#define CMD_READ_REGISTER_S     0x05U
#define CMD_WRITE_REGISTER_C    0x84U
#define CMD_READ_REGISTER_C     0x85U
#define CMD_MEASURE_CONTRL      0x06U
#define CMD_MEASURE_CALC        0x07U
#define CMD_GET_VERSION         0x08U
#define CMD_READ_BUFFER         0x09U
#define CMD_SET_FUNCTION        0x0AU


#define STS_OK                  0xAAU
#define STS_FAIL                0xABU
#define STS_CRC_ERROR           0xACU
#define STS_TIMEOUT             0xADU
#define STS_NOT_SUPPORT         0xAEU
#define STS_DATA_ERROR          0xAFU
#define STS_FLASH_ERROR         0xB0U
#define STS_LEN_ERROR           0xB1U
#define STS_OVFLOW_ERROR        0xB2U
#define STS_PARAM_ERROR         0xB3U
#define STS_BUSY                0xBAU


/* Exported macro ------------------------------------------------------------*/
#define RESP_NULL           NULL, 0U

/* Exported functions --------------------------------------------------------*/
void Apdu_MeasureControl(Mb_CmdParaDef* dev);

void Apdu_GetVersion(Mb_CmdParaDef* dev);

void Apdu_CommandDispatch(Mb_CmdParaDef* dev);

void Apdu_WriteRegisterSingle(Mb_CmdParaDef* dev);

void Apdu_WriteRegisterContinuous(Mb_CmdParaDef* dev);

void Apdu_ReadRegisterSingle(Mb_CmdParaDef* dev);

void Apdu_ReadRegisterContinuous(Mb_CmdParaDef* dev);

void Apdu_MeasureCalc(Mb_CmdParaDef* dev);

void Apdu_ReadBuffer(Mb_CmdParaDef* dev);

void Apdu_SetFunction(Mb_CmdParaDef* dev);

#ifdef __cplusplus
}
#endif /*_cplusplus*/

#endif /* __MB_CMD_H */
