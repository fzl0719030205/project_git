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

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

#define TIMx                 TIM6
#define TIMx_IRQn            TIM6_IRQn
#define TIMx_CLK_ENABLE()    __HAL_RCC_TIM6_CLK_ENABLE()

TIM_HandleTypeDef            TimHandle;

/* ----------------------- static functions ---------------------------------*/
static void prvvTIMERExpiredISR( void );

/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBPortTimersInit( USHORT usTim1Timerout50us )
{
    TimHandle.Instance               = TIMx;
    TimHandle.Init.Period            = usTim1Timerout50us;
    TimHandle.Init.Prescaler         = 0xF9F;   //20KHz
    TimHandle.Init.ClockDivision     = 0;
    TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
    TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
    {
        return FALSE;
    }

    return TRUE;
}


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    TIMx_CLK_ENABLE();

    HAL_NVIC_SetPriority(TIMx_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(TIMx_IRQn);
}


void vMBPortTimersEnable(void)
{
    __HAL_TIM_CLEAR_IT(&TimHandle, TIM_IT_UPDATE);
    __HAL_TIM_SET_COUNTER(&TimHandle, 0);
    HAL_TIM_Base_Start_IT(&TimHandle);
}

void vMBPortTimersDisable(void)
{
    HAL_TIM_Base_Stop_IT(&TimHandle);
}

/* Create an ISR which is called whenever the timer has expired. This function
 * must then call pxMBPortCBTimerExpired( ) to notify the protocol stack that
 * the timer has expired.
 */
static void prvvTIMERExpiredISR( void )
{
    ( void )pxMBPortCBTimerExpired(  );
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    prvvTIMERExpiredISR();
}
