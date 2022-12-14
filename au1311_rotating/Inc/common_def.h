/**
  ******************************************************************************
  * @file           : common_def.h
  * @brief          : This file contains the common definition, macros for HAL drivers.
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
#ifndef __COMMON_DEF_H
#define __COMMON_DEF_H

#ifdef __cplusplus
extern "C" {
#endif /*_cplusplus*/

/* Includes ------------------------------------------------------------------*/
#include "inttypes.h"
#include <stdbool.h>

/* Exported types ------------------------------------------------------------*/
typedef int32_t (*write_reg)(void *, uint8_t, const uint8_t *, uint16_t);
typedef int32_t (*read_reg)(void *, uint8_t, uint8_t *, uint16_t);

typedef struct
{
    uint8_t addr;
    write_reg  write;
    read_reg   read;
    void *handle;
} Acc_CtxDef;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#define FALSE       0U
#define TRUE        1U

#define CLEAR       0U
#define SET         1U

#define UNUSED(X) (void)X      /* To avoid gcc/g++ warnings */

#define HAL_SET_BIT(REG, BITN)               ((REG) |= (BITN))
#define HAL_CLR_BIT(REG, BITN)               ((REG) &= ~(BITN))

#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

/* Exported functions --------------------------------------------------------*/
extern void Error_Handler(void);


#ifdef __cplusplus
}
#endif /*_cplusplus*/

#endif /* __COMMON_DEF_H */
