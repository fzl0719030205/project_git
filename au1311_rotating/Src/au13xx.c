/**
  ******************************************************************************
  * @file           : au13xx.c
  * @brief          : au13xx driver
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

/* Includes ------------------------------------------------------------------*/
#include "au13xx.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int32_t Au_GetID(Au_CtxDef* ctx, uint8_t* id)
{
    int32_t ret_val;
    uint8_t reg0 = 0u;

    ret_val = ctx->read(ctx->handle, CHIP_ID_REG, &reg0, 1);
    if (ret_val)
    {
        return ret_val;
    }

    *id = reg0;
    return 0;
}


int32_t Au_SoftReset(Au_CtxDef* ctx)
{
    uint8_t data_u8;
    int32_t ret_val;
    
    ret_val = Au_ReadReg(ctx, SOFT_RESET_REG, &data_u8, 1);
    if (ret_val)
    {
        return -1;
    }

    data_u8 |= SOFT_RESET_BIT;
    return Au_WriteReg(ctx, SOFT_RESET_REG, &data_u8, 1);
}


int32_t Au_WriteReg(Au_CtxDef* ctx, uint8_t reg_addr, 
                     uint8_t* reg_data, uint8_t cnt)
{
    int32_t ret_val;
  
    if (ctx == NULL)
    {
        return -1;
    }

    ret_val = ctx->write(ctx->handle, reg_addr, reg_data, cnt);
    if (ret_val)
    {
        return -1;
    }

    return 0;
}


int32_t Au_ReadReg(Au_CtxDef* ctx, uint8_t reg_addr, 
                     uint8_t* reg_data, uint8_t cnt)
{
    int32_t ret_val;
  
    if (ctx == NULL)
    {
        return -1;
    }

    ret_val = ctx->read(ctx->handle, reg_addr, reg_data, cnt);
    if (ret_val)
    {
        return -1;
    }

    return 0;
}
