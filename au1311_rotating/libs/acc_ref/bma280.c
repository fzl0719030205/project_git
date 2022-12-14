/**
  ******************************************************************************
  * @file           : bma280.c
  * @brief          : bma280 driver
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
#include "bma280.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int32_t Bma_GetID(Bma_CtxDef* ctx, uint8_t* id)
{
    int32_t ret_val;
    uint8_t reg0 = 0u;
    
    if (ctx == NULL)
    {
        return -1;
    }

    ret_val = ctx->read(ctx->handle, BMA2x2_CHIP_ID_REG, &reg0, BMA2x2_GEN_READ_WRITE_LENGTH);
    if (ret_val)
    {
        return ret_val;
    }

    *id = reg0;
    return 0;
}


int32_t Bma_SoftReset(Bma_CtxDef* ctx)
{
    uint8_t data_u8 = BMA2x2_ENABLE_SOFT_RESET_VALUE;

    return Bma_WriteReg(ctx, BMA2x2_RST_ADDR, &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
}


int32_t Bma_WriteReg(Bma_CtxDef* ctx, uint8_t reg_addr, 
                     uint8_t* reg_data, uint8_t cnt)
{
    uint8_t i;
    int32_t ret_val;
  
    if (ctx == NULL)
    {
        return -1;
    }

    for (i=0;i<cnt;i++)
    {
        ret_val = ctx->write(ctx->handle, reg_addr+i, reg_data+i, 1);
        if (ret_val)
        {
            return -1;
        }
    }

    return 0;
}


int32_t Bma_ReadReg(Bma_CtxDef* ctx, uint8_t reg_addr, 
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
