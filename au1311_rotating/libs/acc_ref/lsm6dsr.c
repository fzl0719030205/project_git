/**
  ******************************************************************************
  * @file           : lsm6dsr.c
  * @brief          : lsm6dsr driver
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
#include "lsm6dsr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int32_t Lsm6dsr_GetID(Lsm6dsr_CtxDef* ctx, uint8_t* id)
{
    int32_t ret_val;
    uint8_t reg0 = 0u;

    ret_val = ctx->read(ctx->handle, LSM6DSR_WHO_AM_I, &reg0, 1);
    if (ret_val)
    {
        return ret_val;
    }

    *id = reg0;
    return 0;
}


int32_t Lsm6dsr_SoftReset(Lsm6dsr_CtxDef* ctx)
{
    uint8_t data_u8;
    int32_t ret_val;
    
    ret_val = Lsm6dsr_ReadReg(ctx, LSM6DSR_CTRL3_C, &data_u8, 1);
    if (ret_val)
    {
        return -1;
    }

    data_u8 |= SW_RESET;
    return Lsm6dsr_WriteReg(ctx, LSM6DSR_CTRL3_C, &data_u8, 1);
}


int32_t Lsm6dsr_WriteReg(Lsm6dsr_CtxDef* ctx, uint8_t reg_addr, 
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


int32_t Lsm6dsr_ReadReg(Lsm6dsr_CtxDef* ctx, uint8_t reg_addr, 
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


/* Disable I3C interface */
int32_t Lsm6dsr_I3cDisable(Lsm6dsr_CtxDef* ctx)
{
    uint8_t data_u8;
    int32_t ret_val;
    
    ret_val = Lsm6dsr_ReadReg(ctx, LSM6DSR_CTRL9_XL, &data_u8, 1);
    if (ret_val)
    {
        return -1;
    }

    data_u8 |= I3C_DISABLE;
    ret_val = Lsm6dsr_WriteReg(ctx, LSM6DSR_CTRL9_XL, &data_u8, 1);
    if (ret_val)
    {
        return -1;
    }

    return 0;
}


/* Block data update */
int32_t Lsm6dsr_BDU_set(Lsm6dsr_CtxDef* ctx)
{
    uint8_t data_u8;
    int32_t ret_val;
    
    ret_val = Lsm6dsr_ReadReg(ctx, LSM6DSR_CTRL3_C, &data_u8, 1);
    if (ret_val)
    {
        return -1;
    }

    data_u8 |= BDU_SET;
    ret_val = Lsm6dsr_WriteReg(ctx, LSM6DSR_CTRL3_C, &data_u8, 1);
    if (ret_val)
    {
        return -1;
    }

    return 0;
}


int32_t Lsm6dsr_XL_DataRateSet(Lsm6dsr_CtxDef* ctx, uint8_t rate)
{
    uint8_t data_u8;
    int32_t ret_val;
    
    ret_val = Lsm6dsr_ReadReg(ctx, LSM6DSR_CTRL1_XL, &data_u8, 1);
    if (ret_val)
    {
        return -1;
    }

    data_u8 &= XL_DATA_RATE_MASK;
    data_u8 |= rate;
    ret_val = Lsm6dsr_WriteReg(ctx, LSM6DSR_CTRL1_XL, &data_u8, 1);
    if (ret_val)
    {
        return -1;
    }

    return 0;
}
