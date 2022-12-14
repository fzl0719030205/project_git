/**
  ******************************************************************************
  * @file           : iic_sim.c
  * @brief          : iic simulator
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
#include "iic_sim.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void SysCtlDelay(uint32_t ulCount)
{
    __asm("    subs    r0, #1\n"
          "    bne.n   SysCtlDelay\n"
          "    bx      lr");
}

void _I2C_DelayUs(uint32_t us)
{
    //SysCtlDelay(us*(SystemCoreClock/3000000));
    SysCtlDelay(us*25);
}


void _I2C_RCC_ENABLE(GPIO_TypeDef* GPIOx)
{
    if (GPIOx == GPIOA)
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if (GPIOx == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    } else if (GPIOx == GPIOC) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }
    #if defined(GPIOD)
    else if (GPIOx == GPIOD) {
        __HAL_RCC_GPIOD_CLK_ENABLE();
    }
    #endif
    #if defined(GPIOE)
    else if (GPIOx == GPIOE) {
        __HAL_RCC_GPIOE_CLK_ENABLE();
    }
    #endif
    #if defined(GPIOF)
    else if (GPIOx == GPIOF) {
        __HAL_RCC_GPIOF_CLK_ENABLE();
    }
    #endif
    #if defined(GPIOG)
    else if (GPIOx == GPIOG) {
        __HAL_RCC_GPIOG_CLK_ENABLE();
    }
    #endif
}


void _I2C_PinOutPut(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    GPIO_InitStruct.Mode  = I2C_PIN_MODE;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Pin = Pin;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}


void _I2C_PinInPut(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Pin = Pin;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}


void I2C_SimInit(I2C_PortDef* port)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    _I2C_RCC_ENABLE(port->SCL_GPIOx);
    _I2C_RCC_ENABLE(port->SDA_GPIOx);

    HAL_GPIO_WritePin(port->SDA_GPIOx, port->SDA_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(port->SCL_GPIOx, port->SCL_Pin, GPIO_PIN_SET);

    GPIO_InitStruct.Mode  = I2C_PIN_MODE;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Pin = port->SDA_Pin;
    HAL_GPIO_Init(port->SDA_GPIOx, &GPIO_InitStruct);

    GPIO_InitStruct.Mode  = I2C_PIN_MODE;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Pin = port->SCL_Pin;
    HAL_GPIO_Init(port->SCL_GPIOx, &GPIO_InitStruct);
}


/*
* Start: SDA High->Low, when SCL High
*/
void I2C_SimStart(I2C_PortDef* port)
{
    _I2C_PinOutPut(port->SDA_GPIOx, port->SDA_Pin);

    HAL_GPIO_WritePin(port->SDA_GPIOx, port->SDA_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(port->SCL_GPIOx, port->SCL_Pin, GPIO_PIN_SET);
    _I2C_DelayUs(port->I2C_Timing);
    HAL_GPIO_WritePin(port->SDA_GPIOx, port->SDA_Pin, GPIO_PIN_RESET);
    _I2C_DelayUs(port->I2C_Timing);

    /* Drive bus */
    HAL_GPIO_WritePin(port->SCL_GPIOx, port->SCL_Pin, GPIO_PIN_RESET);
}


/*
* Stop: SDA Low->High, when SCL High
*/
void I2C_SimStop(I2C_PortDef* port)
{
    _I2C_PinOutPut(port->SDA_GPIOx, port->SDA_Pin);

    HAL_GPIO_WritePin(port->SDA_GPIOx, port->SDA_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(port->SCL_GPIOx, port->SCL_Pin, GPIO_PIN_SET);
    _I2C_DelayUs(port->I2C_Timing);
    HAL_GPIO_WritePin(port->SDA_GPIOx, port->SDA_Pin, GPIO_PIN_SET);
    _I2C_DelayUs(port->I2C_Timing);
}


HAL_StatusTypeDef I2C_SimWaitAck(I2C_PortDef* port, uint32_t WaitMs)
{
    uint32_t start;
  
    _I2C_PinInPut(port->SDA_GPIOx, port->SDA_Pin);
    HAL_GPIO_WritePin(port->SDA_GPIOx, port->SDA_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(port->SCL_GPIOx, port->SCL_Pin, GPIO_PIN_SET);
    
    start = HAL_GetTick();
    _I2C_DelayUs(port->I2C_Timing>>1u);
    while(HAL_GPIO_ReadPin(port->SDA_GPIOx, port->SDA_Pin) != GPIO_PIN_RESET)
    {
        if((HAL_GetTick()-start) > WaitMs)
        {
            I2C_SimStop(port);
            return HAL_TIMEOUT;
        }
    }
    
    _I2C_DelayUs(port->I2C_Timing>>1u);
    HAL_GPIO_WritePin(port->SCL_GPIOx, port->SCL_Pin, GPIO_PIN_RESET);
    return HAL_OK;
}


/*
* ACK: SDA Low, when SCL Low->High->Low
*/
void I2C_SimSendAck(I2C_PortDef* port)
{
    HAL_GPIO_WritePin(port->SCL_GPIOx, port->SCL_Pin, GPIO_PIN_RESET);
    _I2C_PinOutPut(port->SDA_GPIOx, port->SDA_Pin);
    
    HAL_GPIO_WritePin(port->SDA_GPIOx, port->SDA_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(port->SCL_GPIOx, port->SCL_Pin, GPIO_PIN_SET);
    _I2C_DelayUs(port->I2C_Timing);
    HAL_GPIO_WritePin(port->SCL_GPIOx, port->SCL_Pin, GPIO_PIN_RESET);
}


/*
* NACK: SDA High, when SCL Low->High->Low
*/
void I2C_SimSendNack(I2C_PortDef* port)
{
    HAL_GPIO_WritePin(port->SCL_GPIOx, port->SCL_Pin, GPIO_PIN_RESET);
    _I2C_PinOutPut(port->SDA_GPIOx, port->SDA_Pin);
    
    HAL_GPIO_WritePin(port->SDA_GPIOx, port->SDA_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(port->SCL_GPIOx, port->SCL_Pin, GPIO_PIN_SET);
    _I2C_DelayUs(port->I2C_Timing);
    HAL_GPIO_WritePin(port->SCL_GPIOx, port->SCL_Pin, GPIO_PIN_RESET);
}


void I2C_SimSendByte(I2C_PortDef* port, uint8_t chr)
{
    uint8_t i;
    
    ENTER_CRITICAL();
    
    _I2C_PinOutPut(port->SDA_GPIOx, port->SDA_Pin);
    HAL_GPIO_WritePin(port->SCL_GPIOx, port->SCL_Pin, GPIO_PIN_RESET);
    
    for (i=0;i<8u;i++)
    {
        if (chr & 0x80)
        {
            HAL_GPIO_WritePin(port->SDA_GPIOx, port->SDA_Pin, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(port->SDA_GPIOx, port->SDA_Pin, GPIO_PIN_RESET);
        }

        _I2C_DelayUs(port->I2C_Timing>>1u);
        HAL_GPIO_WritePin(port->SCL_GPIOx, port->SCL_Pin, GPIO_PIN_SET);
        _I2C_DelayUs(port->I2C_Timing);
        HAL_GPIO_WritePin(port->SCL_GPIOx, port->SCL_Pin, GPIO_PIN_RESET);
        _I2C_DelayUs(port->I2C_Timing>>1u);

        chr <<= 1u;
    }
    
    EXIT_CRITICAL();
}


uint8_t I2C_SimGetByte(I2C_PortDef* port)
{
    uint8_t i;
    uint8_t chr = 0u;
    
    ENTER_CRITICAL();

    _I2C_PinInPut(port->SDA_GPIOx, port->SDA_Pin);
    HAL_GPIO_WritePin(port->SDA_GPIOx, port->SDA_Pin, GPIO_PIN_SET);
    
    for (i=0;i<8u;i++)
    {
        HAL_GPIO_WritePin(port->SCL_GPIOx, port->SCL_Pin, GPIO_PIN_RESET);
        _I2C_DelayUs(port->I2C_Timing>>1u);
        HAL_GPIO_WritePin(port->SCL_GPIOx, port->SCL_Pin, GPIO_PIN_SET);
        _I2C_DelayUs(port->I2C_Timing>>1u);

        chr <<= 1u;
        if (HAL_GPIO_ReadPin(port->SDA_GPIOx, port->SDA_Pin) == GPIO_PIN_SET)
        {
            chr |= 1u;
        }

        _I2C_DelayUs(port->I2C_Timing>>1u);
        HAL_GPIO_WritePin(port->SCL_GPIOx, port->SCL_Pin, GPIO_PIN_RESET);
        _I2C_DelayUs(port->I2C_Timing>>1u);
    } 
    EXIT_CRITICAL();

    return chr;
}


HAL_StatusTypeDef I2C_WaitTill(I2C_PortDef* port, uint32_t start, uint32_t Timeout)
{
    if ((HAL_GetTick()-start) > Timeout)
    {
        I2C_SimStop(port);
        return HAL_TIMEOUT;
    }
    
    return HAL_OK;
}


/*
* I2c write data
* addr: slave address
* Timeout: timeout(ms)
*/
HAL_StatusTypeDef I2C_SimWrite(I2C_PortDef* port, uint8_t addr, 
                               uint8_t *data, uint32_t len, uint32_t Timeout)
{
    uint32_t i;
    uint32_t start;
    
    start = HAL_GetTick();

    I2C_SimStart(port);
    I2C_SimSendByte(port, addr|I2C_WRITE);
    if (I2C_SimWaitAck(port, I2C_BYTE_TIMEOUT) != HAL_OK)
    {
        return HAL_TIMEOUT;
    }

    for (i=0;i<len;i++)
    {
        I2C_SimSendByte(port, data[i]);
        if (I2C_SimWaitAck(port, I2C_BYTE_TIMEOUT) != HAL_OK)
        {
            return HAL_TIMEOUT;
        }

        if (I2C_WaitTill(port, start, Timeout) != HAL_OK)
        {
            return HAL_TIMEOUT;
        }
    }
    I2C_SimStop(port);

    return HAL_OK;
}


HAL_StatusTypeDef I2C_SimRead(I2C_PortDef* port, uint8_t addr, 
                              uint8_t *data, uint32_t len, uint32_t Timeout)
{
    uint32_t i;
    uint32_t start;

    start = HAL_GetTick();

    I2C_SimStart(port);
    I2C_SimSendByte(port, addr|I2C_READ);
    if (I2C_SimWaitAck(port, I2C_BYTE_TIMEOUT) != HAL_OK)
    {
        return HAL_TIMEOUT;
    }

    for (i=0;i<len;i++)
    {
        data[i] = I2C_SimGetByte(port);
        if (i == (len-1))
        {
            I2C_SimSendNack(port);
        } else {
            I2C_SimSendAck(port);
        }

        if (I2C_WaitTill(port, start, Timeout) != HAL_OK)
        {
            return HAL_TIMEOUT;
        }
    }
    I2C_SimStop(port);

    return HAL_OK;
}


HAL_StatusTypeDef I2C_SimMemWrite(I2C_PortDef* port, uint8_t addr, 
                                  uint8_t *memAddr, uint32_t memAddrLen,
                                  uint8_t *data, uint32_t len, uint32_t Timeout)
{
    uint32_t i;
    uint32_t start;

    start = HAL_GetTick();

    I2C_SimStart(port);
    I2C_SimSendByte(port, addr|I2C_WRITE);
    if (I2C_SimWaitAck(port, I2C_BYTE_TIMEOUT) != HAL_OK)
    {
        return HAL_TIMEOUT;
    }
    
    /* Send register addrss */
    for (i=0;i<memAddrLen;i++)
    {
        I2C_SimSendByte(port, memAddr[i]);
        if (I2C_SimWaitAck(port, I2C_BYTE_TIMEOUT) != HAL_OK)
        {
            return HAL_TIMEOUT;
        }

        if (I2C_WaitTill(port, start, Timeout) != HAL_OK)
        {
            return HAL_TIMEOUT;
        }
    }
    
    /* Send data */
    for (i=0;i<len;i++)
    {
        I2C_SimSendByte(port, data[i]);
        if (I2C_SimWaitAck(port, I2C_BYTE_TIMEOUT) != HAL_OK)
        {
            return HAL_TIMEOUT;
        }

        if (I2C_WaitTill(port, start, Timeout) != HAL_OK)
        {
            return HAL_TIMEOUT;
        }
    }
    I2C_SimStop(port);

    return HAL_OK;
}


HAL_StatusTypeDef I2C_SimMemRead(I2C_PortDef* port, uint8_t addr, 
                                 uint8_t *memAddr, uint32_t memAddrLen,
                                 uint8_t *data, uint32_t len, uint32_t Timeout)
{
    uint32_t i;
    uint32_t start;

    start = HAL_GetTick();

    I2C_SimStart(port);
    I2C_SimSendByte(port, addr|I2C_WRITE);
    if (I2C_SimWaitAck(port, I2C_BYTE_TIMEOUT) != HAL_OK)
    {
        return HAL_TIMEOUT;
    }

    /* Send register addrss */
    for (i=0;i<memAddrLen;i++)
    {
        I2C_SimSendByte(port, memAddr[i]);
        if (I2C_SimWaitAck(port, I2C_BYTE_TIMEOUT) != HAL_OK)
        {
            return HAL_TIMEOUT;
        }

        if (I2C_WaitTill(port, start, Timeout) != HAL_OK)
        {
            return HAL_TIMEOUT;
        }
    }

    I2C_SimStart(port);
    I2C_SimSendByte(port, addr|I2C_READ);
    if (I2C_SimWaitAck(port, I2C_BYTE_TIMEOUT) != HAL_OK)
    {
        return HAL_TIMEOUT;
    }

    /* Get data */
    for (i=0;i<len;i++)
    {
        data[i] = I2C_SimGetByte(port);
        if (i == (len-1))
        {
            I2C_SimSendNack(port);
        } else {
            I2C_SimSendAck(port);
        }

        if (I2C_WaitTill(port, start, Timeout) != HAL_OK)
        {
            return HAL_TIMEOUT;
        }
    }
    I2C_SimStop(port);

    return HAL_OK;
}
