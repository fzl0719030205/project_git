/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id$
 */

#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

#define USARTx                           USART1
#define USARTxIRQ                        USART1_IRQn
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART1_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART1_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART1_RELEASE_RESET()

#define USARTx_TX_PIN                    GPIO_PIN_9
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_TX_AF                     GPIO_AF7_USART1
#define USARTx_RX_PIN                    GPIO_PIN_10
#define USARTx_RX_GPIO_PORT              GPIOA
#define USARTx_RX_AF                     GPIO_AF7_USART1


#define MB_RX_EN_PIN                     GPIO_PIN_3
#define MB_RX_EN_GPIOx                   GPIOB
#define MB_RX_EN_RCC_EN()                __HAL_RCC_GPIOB_CLK_ENABLE()


UART_HandleTypeDef UartHandle;

#define PORT_BUFFER_LEN 256
UCHAR PortBuffer[PORT_BUFFER_LEN];

/* ----------------------- static functions ---------------------------------*/
static void prvvUARTTxReadyISR( void );
static void prvvUARTRxISR( void );

/* ----------------------- Start implementation -----------------------------*/
void
vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
    if (xRxEnable == TRUE)
    {
        // TODO Enable 485 receive
        HAL_GPIO_WritePin(MB_RX_EN_GPIOx, MB_RX_EN_PIN, GPIO_PIN_RESET);
        
        HAL_UART_Receive_IT(&UartHandle, PortBuffer, PORT_BUFFER_LEN);
    } else {
        HAL_UART_AbortReceive_IT(&UartHandle);
    }
  
    if (xTxEnable == TRUE)
    {
        // TODO Enable 485 trasmit
        HAL_GPIO_WritePin(MB_RX_EN_GPIOx, MB_RX_EN_PIN, GPIO_PIN_SET);

    } else {
        HAL_UART_AbortTransmit_IT(&UartHandle);
    }
}

BOOL
xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
    GPIO_InitTypeDef  GPIO_InitStruct;
  
    /* LED indicator */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* 485 En */
    MB_RX_EN_RCC_EN();
    GPIO_InitStruct.Pin = MB_RX_EN_PIN;
    HAL_GPIO_Init(MB_RX_EN_GPIOx, &GPIO_InitStruct);

    /* serial port */
    UartHandle.Instance            = USARTx;
    UartHandle.Init.BaudRate       = ulBaudRate;
    UartHandle.Init.WordLength     = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits       = UART_STOPBITS_1;
    UartHandle.Init.Parity         = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl      = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode           = UART_MODE_TX_RX;
    //UartHandle.Init.OverSampling   = UART_OVERSAMPLING_8;
    UartHandle.Init.OverSampling   = UART_OVERSAMPLING_16;  
    UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

    if(HAL_UART_DeInit(&UartHandle) != HAL_OK)
    {
        return FALSE;
    }
    if(HAL_UART_Init(&UartHandle) != HAL_OK)
    {
        return FALSE;
    }

    return TRUE;
}


void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_PeriphCLKInitTypeDef  RCC_PeriphCLKInitStruct;

    RCC_PeriphCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
    RCC_PeriphCLKInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_SYSCLK;
    HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInitStruct);

    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    /* Enable GPIO TX/RX clock */
    USARTx_TX_GPIO_CLK_ENABLE();
    USARTx_RX_GPIO_CLK_ENABLE();

    /* Enable USARTx clock */
    USARTx_CLK_ENABLE();
  
    /*##-2- Configure peripheral GPIO ##########################################*/
    /* UART TX GPIO pin configuration  */
    GPIO_InitStruct.Pin       = USARTx_TX_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = USARTx_TX_AF;

    HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

    /* UART RX GPIO pin configuration  */
    GPIO_InitStruct.Pin = USARTx_RX_PIN;
    GPIO_InitStruct.Alternate = USARTx_RX_AF;

    HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
    
    HAL_NVIC_SetPriority(USARTxIRQ, 2, 0);
    HAL_NVIC_EnableIRQ(USARTxIRQ);
}


BOOL
xMBPortSerialPutByte( CHAR ucByte )
{
    HAL_UART_Transmit_IT(&UartHandle, (uint8_t*)&ucByte, 1);

    return TRUE;
}

BOOL
xMBPortSerialPutBuffer( UCHAR * pucByte,  USHORT len)
{
    HAL_UART_Transmit_IT(&UartHandle, (uint8_t*)pucByte, len);

    return TRUE;
}


BOOL
xMBPortSerialGetByte( CHAR * pucByte )
{
    CHAR* ptr = (CHAR*)UartHandle.pRxBuffPtr - 1;
    *pucByte = *ptr;

    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);
  
    return TRUE;
}

/* Create an interrupt handler for the transmit buffer empty interrupt
 * (or an equivalent) for your target processor. This function should then
 * call pxMBFrameCBTransmitterEmpty( ) which tells the protocol stack that
 * a new character can be sent. The protocol stack will then call 
 * xMBPortSerialPutByte( ) to send the character.
 */
static void prvvUARTTxReadyISR( void )
{
    pxMBFrameCBTransmitterEmpty(  );
}

/* Create an interrupt handler for the receive interrupt for your target
 * processor. This function should then call pxMBFrameCBByteReceived( ). The
 * protocol stack will then call xMBPortSerialGetByte( ) to retrieve the
 * character.
 */
static void prvvUARTRxISR( void )
{
    pxMBFrameCBByteReceived(  );
}


void ACC_MbPortHandler(void)
{
    if (UartHandle.RxState == HAL_UART_STATE_BUSY_RX)
    {
        prvvUARTRxISR();
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    prvvUARTTxReadyISR();
}
