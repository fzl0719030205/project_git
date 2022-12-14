/**
  ******************************************************************************
  * @file           : acc_operation.c
  * @brief          : This file contains the acc process
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
#include "acc_operation_simu.h"

/* Private includes ----------------------------------------------------------*/
#include "iic_sim.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define I2C_ADDRESS        0x60
#define BMA2xx_ADDRESS     0x30
#define LSM6xx_ADDRESS     0xD4

#define TIMx                             TIM7
#define TIMx_CLK_ENABLE()                __HAL_RCC_TIM7_CLK_ENABLE()

/* Private variables ---------------------------------------------------------*/
__IO uint8_t                 RegDataReadEn = 0u;
__IO uint8_t                 RegDataToRead = 0u;
__IO uint8_t                 RegDataReady = 0u;
__IO uint16_t                RegDataPointer = 0u;

ACC_ConfigDef ACC_Conifg = {
    0,
    SLAVE_PORT_I2C,
    0,
    ACC_ID_MAP_ALL,
    0,
    0,
    ACC_DATA_16,
    NULL,
    NULL,
};


TIM_HandleTypeDef           TimHandle1;
I2C_PortDef I2cHandle[ACC_NUMS] = {
    {I2C_ADDRESS, I2C_TIMING_200K, GPIOB, GPIO_PIN_9, GPIOB, GPIO_PIN_10},   //DUT1 
    {I2C_ADDRESS, I2C_TIMING_200K, GPIOB, GPIO_PIN_13, GPIOB, GPIO_PIN_14},
    {I2C_ADDRESS, I2C_TIMING_200K, GPIOC, GPIO_PIN_0, GPIOC, GPIO_PIN_1},
    {I2C_ADDRESS, I2C_TIMING_200K, GPIOA, GPIO_PIN_0, GPIOA, GPIO_PIN_1},
    {I2C_ADDRESS, I2C_TIMING_200K, GPIOA, GPIO_PIN_3, GPIOA, GPIO_PIN_4},
    {I2C_ADDRESS, I2C_TIMING_200K, GPIOA, GPIO_PIN_6, GPIOA, GPIO_PIN_7},
    {I2C_ADDRESS, I2C_TIMING_200K, GPIOB, GPIO_PIN_0, GPIOB, GPIO_PIN_1},
    {I2C_ADDRESS, I2C_TIMING_200K, GPIOB, GPIO_PIN_6, GPIOB, GPIO_PIN_7},
    {I2C_ADDRESS, I2C_TIMING_200K, GPIOC, GPIO_PIN_3, GPIOC, GPIO_PIN_4},
    {BMA2xx_ADDRESS, I2C_TIMING_200K, GPIOC, GPIO_PIN_6, GPIOC, GPIO_PIN_7},    //REF1
    {LSM6xx_ADDRESS, I2C_TIMING_200K, GPIOC, GPIO_PIN_10, GPIOC, GPIO_PIN_11},  //REF2
};

#if AU_INT_ODR
typedef struct
{
    GPIO_TypeDef*   INT_GPIOx;
    uint32_t        INT_Pin;
} Int_PortDef;


Int_PortDef IntPort[AU_DUT_NUMS] = {
    {GPIOB, GPIO_PIN_8},
    {GPIOB, GPIO_PIN_12},
    {GPIOC, GPIO_PIN_2},
    {GPIOA, GPIO_PIN_2},
    {GPIOA, GPIO_PIN_5},
    {GPIOA, GPIO_PIN_8},
    {GPIOB, GPIO_PIN_2},
    {GPIOB, GPIO_PIN_5},
    {GPIOC, GPIO_PIN_5},
};
#endif

Au_CtxDef       au_ctx[AU_DUT_NUMS];
Bma_CtxDef      bma_ctx;
Lsm6dsr_CtxDef  lsm_ctx;


/* Private function prototypes -----------------------------------------------*/
int acc_write_ptr(void *handle, uint8_t reg, const uint8_t *data, uint16_t len);
int acc_read_ptr(void *handle, uint8_t reg, uint8_t *data, uint16_t len);

void Acc_I2C_Init(void)
{
    uint8_t i;

    for (i=0;i<ACC_NUMS;i++)
    {
        I2C_SimInit(&I2cHandle[i]);
    }
}


void Acc_DUT_Init(void)
{
    uint8_t i;
    
#if AU_INT_ODR 
    GPIO_InitTypeDef  GPIO_InitStruct;

    for (i=0;i<AU_DUT_NUMS;i++)
    {
        GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull  = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Pin = IntPort[i].INT_Pin;
        HAL_GPIO_Init(IntPort[i].INT_GPIOx, &GPIO_InitStruct);
    }
#endif

    for (i=0;i<AU_DUT_NUMS;i++)
    {
        au_ctx[i].addr = I2C_ADDRESS;
        au_ctx[i].write = acc_write_ptr;
        au_ctx[i].read = acc_read_ptr;
        au_ctx[i].handle = &I2cHandle[i];
        
        Acc_ResetDevice(i);
    }

    bma_ctx.addr = BMA2xx_ADDRESS;
    bma_ctx.write = acc_write_ptr;
    bma_ctx.read = acc_read_ptr;
    bma_ctx.handle = &I2cHandle[REF_DUT1];
    Acc_ResetDevice(REF_DUT1);

    lsm_ctx.addr = LSM6xx_ADDRESS;
    lsm_ctx.write = acc_write_ptr;
    lsm_ctx.read = acc_read_ptr;
    lsm_ctx.handle = &I2cHandle[REF_DUT2];
    Acc_ResetDevice(REF_DUT2);
    
    // wait
    HAL_Delay(50);
}


int acc_write_ptr(void *handle, uint8_t reg, const uint8_t *data, uint16_t len)
{
    HAL_StatusTypeDef ret_val;
    uint8_t reg_address;
    uint8_t i;

    reg_address = reg;

    for (i=0;i<3;i++)
    {
        ret_val = I2C_SimMemWrite((I2C_PortDef*)handle, 
                                  ((I2C_PortDef*)handle)->Slave_Addr, 
                                  &reg_address,
                                  1, 
                                  (uint8_t*)data, 
                                  len, 
                                  50);
        if (ret_val == HAL_OK)
        {
            break;
        } else {
            HAL_Delay(50);
            continue;
        }
    }
    
    if (i == 3)
    {
        return -1;
    }
    
    return 0;
}


int acc_read_ptr(void *handle, uint8_t reg, uint8_t *data, uint16_t len)
{
    HAL_StatusTypeDef ret_val;
    uint8_t reg_address;
    uint8_t i;

    reg_address = reg;

    for (i=0;i<3;i++)
    {
        ret_val = I2C_SimMemRead((I2C_PortDef*)handle, 
                                 ((I2C_PortDef*)handle)->Slave_Addr, 
                                 &reg_address,
                                 1, 
                                 data, 
                                 len, 
                                 50);
        if (ret_val == HAL_OK)
        {
            break;
        } else {
            HAL_Delay(50);
            continue;
        }
    }
    
    if (i == 3)
    {
        return -1;
    }
    
    return 0;
}


/******** operation list ********/

HAL_StatusTypeDef ACC_GetID(uint8_t idx, uint8_t* id)
{
    uint8_t reg_b;
  
    if (idx < AU_DUT_NUMS)
    {
        if (Au_GetID(&au_ctx[idx], &reg_b) != 0)
        {
            return HAL_ERROR;
        }
    } else if (idx == REF_DUT1) {
        if (Bma_GetID(&bma_ctx, &reg_b) != 0)
        {
            return HAL_ERROR;
        }
    } else if (idx == REF_DUT2) {
        if (Lsm6dsr_GetID(&lsm_ctx, &reg_b) != 0)
        {
            return HAL_ERROR;
        }
    } else {
        return HAL_ERROR;
    }

    *id = reg_b;
    return HAL_OK;
}


HAL_StatusTypeDef ACC_CheckID(uint8_t idx, uint8_t id)
{
    if (idx < AU_DUT_NUMS)
    {
        if (CHIP_ID_DEFAULT != id)
        {
            return HAL_ERROR;
        }
    } else if (idx == REF_DUT1) {
        if (BMA280_ID != id)
        {
            return HAL_ERROR;
        }
    } else if (idx == REF_DUT2) {
        if (LSM6DSR_ID != id)
        {
            return HAL_ERROR;
        }
    } else {
        return HAL_ERROR;
    }

    return HAL_OK;
}


HAL_StatusTypeDef Acc_ResetDevice(uint8_t idx)
{
    int32_t ret_val = 0;

    if (idx < AU_DUT_NUMS)
    {
        ret_val = Au_SoftReset(&au_ctx[idx]);
    } else if (idx == REF_DUT1) {
        ret_val = Bma_SoftReset(&bma_ctx);
    } else if (idx == REF_DUT2) {
        ret_val = Lsm6dsr_SoftReset(&lsm_ctx);
    } else {
        return HAL_ERROR;
    }

    if (ret_val)
    {
        return HAL_ERROR;
    }
    
    return HAL_OK;
}


HAL_StatusTypeDef Acc_SetInitConfig(uint8_t idx)
{
    int32_t ret_val = 0;
    uint8_t reg0;

    if (idx < AU_DUT_NUMS) {
    
    
    } else if (idx == REF_DUT1) {
        // always enable
        if (Au_ReadReg(&bma_ctx, BMA2x2_BW_REG, &reg0, 1) != HAL_OK)
        {
            return HAL_ERROR;
        }

        reg0 &= ~BMA2x2_BW_MSK;
        reg0 |= BMA2x2_BW_500HZ;
        ret_val = Au_WriteReg(&bma_ctx, BMA2x2_BW_REG, &reg0, 1);
        if (ret_val)
        {
            return HAL_ERROR;
        }
    } else if (idx == REF_DUT2) {
        ret_val = Lsm6dsr_I3cDisable(&lsm_ctx);
        if (ret_val)
        {
            return HAL_ERROR;
        }

        ret_val = Lsm6dsr_BDU_set(&lsm_ctx);
        if (ret_val)
        {
            return HAL_ERROR;
        }

        ret_val = Lsm6dsr_XL_DataRateSet(&lsm_ctx, LSM6DSR_XL_ODR_416Hz);
        if (ret_val)
        {
            return HAL_ERROR;
        }
    }

    return HAL_OK;
}


HAL_StatusTypeDef Acc_RegisterRead(uint8_t idx, uint8_t reg, uint8_t *data, uint16_t len)
{
    int32_t ret_val = 0;

    if (idx < AU_DUT_NUMS)
    {
        ret_val = Au_ReadReg(&au_ctx[idx], reg, data, len);
    } else if (idx == REF_DUT1) {
        ret_val = Bma_ReadReg(&bma_ctx, reg, data, len);
    } else if (idx == REF_DUT2) {
        ret_val = Lsm6dsr_ReadReg(&lsm_ctx, reg, data, len);
    } else {
        return HAL_ERROR;
    }

    if (ret_val)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}


HAL_StatusTypeDef Acc_RegisterWrite(uint8_t idx, uint8_t reg, uint8_t *data, uint16_t len)
{
    int32_t ret_val = 0;

    if (idx < AU_DUT_NUMS)
    {
        ret_val = Au_WriteReg(&au_ctx[idx], reg, data, len);
    } else if (idx == REF_DUT1) {
        ret_val = Bma_WriteReg(&bma_ctx, reg, data, len);
    } else if (idx == REF_DUT2) {
        ret_val = Lsm6dsr_WriteReg(&lsm_ctx, reg, data, len);
    } else {
        return HAL_ERROR;
    }

    if (ret_val)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}


HAL_StatusTypeDef Acc_StopMeasure(uint8_t idx)
{  
    int32_t ret_val = 0;
    uint8_t reg0;

    if (idx < AU_DUT_NUMS)
    {
        if (Au_ReadReg(&au_ctx[idx], PWR_CTRL_REG, &reg0, 1) != HAL_OK)
        {
            return HAL_ERROR;
        }

        // stop
        reg0 &= ~PWR_MODE_MASK;
        reg0 |= PWR_MODE_STDBY;
        ret_val = Au_WriteReg(&au_ctx[idx], PWR_CTRL_REG, &reg0, 1);
    } else if (idx == REF_DUT1) {
        // no need?
      
    } else if (idx == REF_DUT2) {
        ret_val = Lsm6dsr_XL_DataRateSet(&lsm_ctx, LSM6DSR_XL_ODR_DISABLE);
    } else {
        return HAL_ERROR;
    }

    if (ret_val)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}


HAL_StatusTypeDef Acc_StartMeasure(uint8_t idx)
{
    int32_t ret_val = 0;
    uint8_t reg0;

    if (idx < AU_DUT_NUMS)
    {
        if (Au_ReadReg(&au_ctx[idx], PWR_CTRL_REG, &reg0, 1) != HAL_OK)
        {
            return HAL_ERROR;
        }

        // start
        reg0 &= ~PWR_MODE_MASK;
        reg0 |= PWR_MODE_NORMA;
        ret_val = Au_WriteReg(&au_ctx[idx], PWR_CTRL_REG, &reg0, 1);
    } else if (idx == REF_DUT1) {
        // no need?
      
    } else if (idx == REF_DUT2) {
        ret_val = Lsm6dsr_XL_DataRateSet(&lsm_ctx, LSM6DSR_XL_ODR_416Hz);
    } else {
        return HAL_ERROR;
    }

    if (ret_val)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}


HAL_StatusTypeDef ACC_ReadData(uint8_t idx, uint8_t* buffer, uint32_t Timeout)
{
    uint32_t start = HAL_GetTick();
    uint8_t tmp_data[6];
    int16_t bma_data;
    __IO uint8_t data_valid = 0;
  
    if (idx < AU_DUT_NUMS)
    {
    #if AU_INT_ODR
        // wait INT low
        while(HAL_GPIO_ReadPin(IntPort[idx].INT_GPIOx, 
                               IntPort[idx].INT_Pin) == GPIO_PIN_SET)
        {
            if((HAL_GetTick() - start) > Timeout)
            {
                return HAL_TIMEOUT;
            }
        }
        // wait INT high
        while(HAL_GPIO_ReadPin(IntPort[idx].INT_GPIOx, 
                               IntPort[idx].INT_Pin) == GPIO_PIN_RESET)
        {
            if((HAL_GetTick() - start) > Timeout)
            {
                return HAL_TIMEOUT;
            }
        }
    #else
        while(data_valid == 0)
        {
            if (Acc_RegisterRead(idx, SPI_DATA_VALID, (uint8_t*)&data_valid, 1) != HAL_OK)
            {
                return HAL_ERROR;
            }

            if((HAL_GetTick() - start) > Timeout)
            {
                return HAL_TIMEOUT;
            }
        }
    #endif
    
        if (Acc_RegisterRead(idx, SPI_X_16BIT_M, tmp_data, 6) != HAL_OK)
        {
            return HAL_ERROR;
        }
        
        buffer[0] = tmp_data[1];
        buffer[1] = tmp_data[0];
        buffer[2] = tmp_data[3];
        buffer[3] = tmp_data[2];
        buffer[4] = tmp_data[5];
        buffer[5] = tmp_data[4];
    } else if (idx == REF_DUT1) {
        while(TRUE)
        {
            if (Acc_RegisterRead(idx, BMA2x2_ACCEL_X14_LSB_REG, tmp_data, BMA2x2_SHIFT_SIX_BITS) != HAL_OK)
            {
                return HAL_ERROR;
            }
        
            if((HAL_GetTick() - start) > Timeout)
            {
                return HAL_TIMEOUT;
            }

            if ((tmp_data[BMA2x2_SENSOR_DATA_XYZ_X_LSB] & BMA2x2_NEW_DATA_X_MSK) && 
                    (tmp_data[BMA2x2_SENSOR_DATA_XYZ_Y_LSB] & BMA2x2_NEW_DATA_Y_MSK) &&
                    (tmp_data[BMA2x2_SENSOR_DATA_XYZ_Z_LSB] & BMA2x2_NEW_DATA_Z_MSK))
            {
                break;
            }
        }
        
        bma_data = (int16_t)((((int32_t)((int8_t)
                              tmp_data[BMA2x2_SENSOR_DATA_XYZ_X_MSB])) <<
                                                    BMA2x2_SHIFT_EIGHT_BITS) |
                             (tmp_data[BMA2x2_SENSOR_DATA_XYZ_X_LSB]
                              & BMA2x2_14_BIT_SHIFT));
        bma_data = bma_data >> BMA2x2_SHIFT_TWO_BITS;
        buffer[0] = bma_data & 0xFF;
        buffer[1] = (bma_data >> BMA2x2_SHIFT_EIGHT_BITS) & 0xFF;

        bma_data = (int16_t)((((int32_t)((int8_t)
                              tmp_data[BMA2x2_SENSOR_DATA_XYZ_Y_MSB])) <<
                                                    BMA2x2_SHIFT_EIGHT_BITS) |
                             (tmp_data[BMA2x2_SENSOR_DATA_XYZ_Y_LSB]
                              & BMA2x2_14_BIT_SHIFT));
        bma_data = bma_data >> BMA2x2_SHIFT_TWO_BITS;
        buffer[2] = bma_data & 0xFF;
        buffer[3] = (bma_data >> BMA2x2_SHIFT_EIGHT_BITS) & 0xFF;
        
        bma_data = (int16_t)((((int32_t)((int8_t)
                              tmp_data[BMA2x2_SENSOR_DATA_XYZ_Z_MSB])) <<
                                                    BMA2x2_SHIFT_EIGHT_BITS) |
                             (tmp_data[BMA2x2_SENSOR_DATA_XYZ_Z_LSB]
                              & BMA2x2_14_BIT_SHIFT));
        bma_data = bma_data >> BMA2x2_SHIFT_TWO_BITS;
        buffer[4] = bma_data & 0xFF;
        buffer[5] = (bma_data >> BMA2x2_SHIFT_EIGHT_BITS) & 0xFF;
    } else if (idx == REF_DUT2) {
        while((data_valid & XL_DATA_VALID) == 0)
        {
            if (Acc_RegisterRead(idx, LSM6DSR_STATUS_REG, (uint8_t*)&data_valid, 1) != HAL_OK)
            {
                return HAL_ERROR;
            }

            if((HAL_GetTick() - start) > Timeout)
            {
                return HAL_TIMEOUT;
            }
        }
      
        if (Acc_RegisterRead(idx, LSM6DSR_OUTX_L_A, buffer, 6) != HAL_OK)
        {
            return HAL_ERROR;
        }
    } else {
        return HAL_ERROR;
    }

    return HAL_OK;
}



/******** External ********/

HAL_StatusTypeDef ACC_UpdateData(uint8_t* buffer)
{
    uint8_t i;
    uint8_t* ptr;
    uint8_t has_err = FALSE;

    if (buffer != NULL)
    {
        ptr = buffer;
    } else {
        ptr = ACC_Conifg.acc_buffer;
    }

    for (i=0;i<ACC_NUMS;i++)
    {
        if (ACC_Conifg.ID_map & ((uint16_t)0x01ul << i))
        {
            if (ACC_ReadData(i, ptr, 500) != HAL_OK)
            {
                ACC_Conifg.sts_buffer[i] = 0;
                has_err = TRUE;
            }
        }

        ptr += 10;
    }
    
    if (has_err == TRUE)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}


void ACC_Refresh(void)
{
    if ((ACC_Conifg.Reg_ODR > 0) && 
        ((HAL_GetTick() - ACC_Conifg.last_ms) > ACC_Conifg.Reg_ODR))
    {
        ACC_UpdateData(NULL);
        ACC_Conifg.last_ms = HAL_GetTick();
    }
}



//HAL_StatusTypeDef ACC_RegTimerInit(void)
//{
//    if (ACC_Conifg.Reg_ODR == 0u)
//    {
//        return HAL_OK;
//    }
//    
//    TIMx_CLK_ENABLE();
//
//    TimHandle1.Instance               = TIMx;
//    TimHandle1.Init.Period            = ACC_Conifg.Reg_ODR;
//    TimHandle1.Init.Prescaler         = 0x3E7;   //80KHz
//    TimHandle1.Init.ClockDivision     = 0;
//    TimHandle1.Init.CounterMode       = TIM_COUNTERMODE_UP;
//    TimHandle1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
//
//    if (HAL_TIM_Base_Init(&TimHandle1) != HAL_OK)
//    {
//        return HAL_ERROR;
//    }
//
//    return HAL_OK;
//}
//
//
//HAL_StatusTypeDef ACC_RegReadStart(void)
//{
//    if (HAL_TIM_Base_Start(&TimHandle1) != HAL_OK)
//    {
//        return HAL_ERROR;
//    }
//
//    RegDataReadEn = 1u;
//    RegDataToRead = 0u;
//    RegDataReady = 0u;
//    RegDataPointer = 0u;
//    return HAL_OK;
//}
//
//
//HAL_StatusTypeDef ACC_RegReadStop(void)
//{
//    if (HAL_TIM_Base_Stop(&TimHandle1) != HAL_OK)
//    {
//        return HAL_ERROR;
//    }
//
//    RegDataReadEn = 0u;
//    RegDataToRead = 0u;
//    RegDataReady = 0u;
//    RegDataPointer = 0u;
//    return HAL_OK; 
//}
