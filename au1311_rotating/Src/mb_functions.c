/**
  ******************************************************************************
  * @file           : mb_functions.c
  * @brief          : Modbus functions
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
#include "mb_functions.h"
#include "mb_command.h"

#include "acc_operation_simu.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern ACC_ConfigDef ACC_Conifg;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
UCHAR GetSlaveAddr(void)
{
    return MB_SLAVE_ADDRESS;
}


HAL_StatusTypeDef ACC_MbInit(void)
{
    const UCHAR ucSlaveID[] = {0xAA, 0xBB, 0xCC};

    if(MB_ENOERR != eMBInit(MB_RTU, 
                            GetSlaveAddr(), 
                            MB_PORT_INDEX, 
                            MB_PORT_RATE, 
                            MB_PAR_NONE))
    {
        return HAL_ERROR;
    } else {
        if(MB_ENOERR != eMBSetSlaveID(MB_SLAVE_ID, TRUE, ucSlaveID, 3))
        {
            return HAL_ERROR;
        }
    }

    return HAL_OK;
}


HAL_StatusTypeDef ACC_MbEnable(void)
{
    if(MB_ENOERR != eMBEnable())
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}


void ACC_MbPoll(void)
{
    eMBPoll();
}


HAL_StatusTypeDef ACC_MbDisable(void)
{
    if(MB_ENOERR != eMBDisable())
    {
        return HAL_ERROR;
    }

    if(MB_ENOERR != eMBClose())
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/* Modbus functions */
#define REG_INPUT_START     (1000)
#define REG_INPUT_NREGS     (64)

#define REG_DUT_STS_START   (0x0001)
#define REG_DUT_STS_NREGS   (AU_DUT_NUMS+REF_DUT_NUMS)

#define REG_DUT_DAT_START   (0x0001)
#define REG_DUT_DAT_NREGS   (55)

#define REG_CMD_START       (0x0064)
#define REG_CMD_NREGS       (1)
#define REG_DAT_START       (0x0065)
#define REG_DAT_NREGS       (128)

#define REG_STS_START       (0x012C)
#define REG_STS_NREGS       (1)

static USHORT   usRegInputStart = REG_INPUT_START;
static USHORT   usRegInputBuf[REG_INPUT_NREGS];

static USHORT   usRegDUTSTSBuf[REG_DUT_STS_NREGS] = {0};
static USHORT   usRegDUTDATBuf[REG_DUT_DAT_NREGS];
static USHORT   usRegCMDBuf[REG_CMD_NREGS];
static USHORT   usRegDATBuf[REG_DAT_NREGS];
static USHORT   usRegSTSBuf[REG_STS_NREGS];


typedef struct
{
    USHORT RegStart;
    USHORT RegNum;
    USHORT* RegBuf;
} Mb_RegMap;

#define DISC_MAP_NUM       (1)
Mb_RegMap DISCMap[DISC_MAP_NUM] = {{REG_DUT_STS_START, REG_DUT_STS_NREGS, usRegDUTSTSBuf}};

#define HOLDING_MAP_NUM     (3)
Mb_RegMap HoldingMap[HOLDING_MAP_NUM] = 
                        {{REG_DUT_DAT_START,    REG_DUT_DAT_NREGS,  usRegDUTDATBuf},
                         {REG_DAT_START,          REG_DAT_NREGS,  usRegDATBuf},
                         {REG_STS_START,        REG_STS_NREGS,      usRegSTSBuf}};


void Acc_MbUpdateStatus(void)
{
    uint8_t i;
    uint8_t id;
    
    // set buffer
    ACC_Conifg.acc_buffer = (uint8_t*)usRegDUTDATBuf;;
    ACC_Conifg.sts_buffer = usRegDUTSTSBuf;

    for (i=0;i<REG_DUT_STS_NREGS;i++)
    {
        id = 0;
        
        if (ACC_GetID(i, &id) == HAL_OK)
        {
            if (ACC_CheckID(i, id) == HAL_OK)
            {
                usRegDUTSTSBuf[i] = 0x00FF;

                // Set config
                Acc_SetInitConfig(i);
                continue;
            }
        }

        usRegDUTSTSBuf[i] = 0;
    }
}


eMBErrorCode eMBRegInputCB(UCHAR* pucRegBuffer, USHORT usAddress, USHORT usNRegs)
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;

    if( ( usAddress >= REG_INPUT_START )
        && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - usRegInputStart );
        while( usNRegs > 0 )
        {
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
            iRegIndex++;
            usNRegs--;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}


eMBErrorCode eMBRegHoldingCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode)
{
    eMBErrorCode    eStatus = MB_ENOERR;
    USHORT          iRegIndex;
    USHORT          i;

    if ((usAddress == REG_CMD_START) && (usNRegs == REG_CMD_NREGS))
    {
        iRegIndex = 0;
        switch (eMode)
        {
        case MB_REG_READ:
            *pucRegBuffer++ = (UCHAR)(usRegCMDBuf[iRegIndex] >> 8);
            *pucRegBuffer++ = (UCHAR)(usRegCMDBuf[iRegIndex] & 0xFF);
            break;

        case MB_REG_WRITE:
            usRegCMDBuf[iRegIndex] = *pucRegBuffer++ << 8;
            usRegCMDBuf[iRegIndex] |= *pucRegBuffer++;
            
            // This is command
            Mb_CmdParaDef para;
            
            para.cmd = usRegCMDBuf[0] & 0xff;
            para.seq = (usRegCMDBuf[0] >> 8) & 0xff;
            para.buffer = (uint8_t*)usRegDATBuf;
            para.status = (uint8_t*)usRegSTSBuf;
            para.acc_data = (uint8_t*)usRegDUTDATBuf;
            para.sts_data = usRegDUTSTSBuf;

            Apdu_CommandDispatch(&para);
            break;

        default: break;
        }
    } else {
        for (i=0;i<HOLDING_MAP_NUM;i++)
        {
            if((usAddress >= HoldingMap[i].RegStart) && 
                    ((usAddress+usNRegs) <= (HoldingMap[i].RegStart+HoldingMap[i].RegNum)))
            {
                iRegIndex = (USHORT)(usAddress - HoldingMap[i].RegStart);
                switch (eMode)
                {
                case MB_REG_READ:
                    while( usNRegs > 0 )
                    {
                        *pucRegBuffer++ = (UCHAR)(HoldingMap[i].RegBuf[iRegIndex] >> 8 );
                        *pucRegBuffer++ = (UCHAR)(HoldingMap[i].RegBuf[iRegIndex] & 0xFF );
                        iRegIndex++;
                        usNRegs--;
                    }
                    break;

                case MB_REG_WRITE:
                    while( usNRegs > 0 )
                    {
                        HoldingMap[i].RegBuf[iRegIndex] = *pucRegBuffer++ << 8;
                        HoldingMap[i].RegBuf[iRegIndex] |= *pucRegBuffer++;
                        iRegIndex++;
                        usNRegs--;
                    }
                }

                break;
            }
        }

        if (i >= HOLDING_MAP_NUM)
        {
            eStatus = MB_ENOREG;
        }
    }

    return eStatus;
}


eMBErrorCode eMBRegCoilsCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
               eMBRegisterMode eMode)
{
    return MB_ENOREG;
}


eMBErrorCode eMBRegDiscreteCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete)
{
    eMBErrorCode    eStatus = MB_ENOERR;
    USHORT          iRegIndex;
    USHORT          i;
    USHORT          j;

    for (i=0;i<DISC_MAP_NUM;i++)
    {
        if((usAddress >= DISCMap[i].RegStart) && 
                    ((usAddress+usNDiscrete) <= (DISCMap[i].RegStart+DISCMap[i].RegNum)))
        {
            iRegIndex = (USHORT)(usAddress - DISCMap[i].RegStart);

            while( usNDiscrete > 0 )
            {
                for (j=0;j<8;j++)
                {
                    (*pucRegBuffer) <<= 1;
                    if (DISCMap[i].RegBuf[iRegIndex] == 0x00FF)
                    {
                        (*pucRegBuffer) |= 0x01;
                    }

                    iRegIndex++;
                    usNDiscrete--;
                    if (usNDiscrete == 0)
                    {
                        break;
                    }
                }

                pucRegBuffer++;
            }

            break;
        }
    }

    if (i >= DISC_MAP_NUM)
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}
