/**
  ******************************************************************************
  * @file           : mb_command.c
  * @brief          : Modbus command
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
#include "mb_command.h"
#include "acc_operation_simu.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
    uint8_t CmdId;
    void (*Handler)(Mb_CmdParaDef* dev);
} Mb_CmdTableDef;

/* Private define ------------------------------------------------------------*/
Mb_CmdTableDef CmdTable[] = {
    {CMD_GET_VERSION,           Apdu_GetVersion},
    {CMD_MEASURE_CONTRL,        Apdu_MeasureControl},
    {CMD_WRITE_REGISTER_S,      Apdu_WriteRegisterSingle},
    {CMD_READ_REGISTER_S,       Apdu_ReadRegisterSingle},
    {CMD_WRITE_REGISTER_C,      Apdu_WriteRegisterContinuous},
    {CMD_READ_REGISTER_C,       Apdu_ReadRegisterContinuous},
    {CMD_MEASURE_CALC,          Apdu_MeasureCalc},
    {CMD_READ_BUFFER,           Apdu_ReadBuffer},
    {CMD_SET_FUNCTION,          Apdu_SetFunction},
};

/* Private macro -------------------------------------------------------------*/
#define CMD_NUMS        (sizeof(CmdTable) / sizeof(CmdTable[0]))

/* Private variables ---------------------------------------------------------*/
#define VERSION_SIZE    0x16U

const uint8_t HW_Version[8] = "HW v0001";
const uint8_t SW_Version[8] = "FW v0002";

static uint8_t dummyBuffer[APDU_BUFFER_SIZE];

uint16_t calcBuffer[MAX_CALC_SIZE*3];

extern ACC_ConfigDef ACC_Conifg;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void Apdu_SetStatus(Mb_CmdParaDef* dev, uint8_t sts, uint8_t* pdu, uint32_t size)
{
    uint8_t* out_ptr = dev->buffer;
    uint8_t* sts_ptr = dev->status;

    // Copy PDU
    if (pdu)
    {
          // Set length
        out_ptr[0] = size & 0xff;
        out_ptr[1] = (size >> 8) & 0xff;

        memcpy(out_ptr+2, pdu, size);
    }

    // Set status
    sts_ptr[0] = sts;
    sts_ptr[1] = dev->seq;
}


void Apdu_Unsupport(Mb_CmdParaDef* dev)
{
    Apdu_SetStatus(dev, STS_NOT_SUPPORT, NULL, 0);
}

/**
  * @brief  Dispatch command to each handler
  * @param  dev    device instance
  */
void Apdu_CommandDispatch(Mb_CmdParaDef* dev)
{
    uint32_t i;

    Apdu_SetStatus(dev, STS_BUSY, NULL, 0);
    
    for (i=0;i<CMD_NUMS;i++)
    {
        if (dev->cmd == CmdTable[i].CmdId)
        {
            if (CmdTable[i].Handler != NULL)
            {
                CmdTable[i].Handler(dev);
            }
            break;
        }
    }
    
    if (i >= CMD_NUMS)
    {
        Apdu_Unsupport(dev);
    }
}


/**
  * @brief  Measure control
  * @param  dev    device instance
  */
void Apdu_MeasureControl(Mb_CmdParaDef* dev)
{
    uint8_t* data_ptr = dev->buffer;
    uint16_t id_map = 0;
    uint16_t i;

    id_map = data_ptr[0] | (((uint16_t)data_ptr[1]) << 8);

    ACC_Conifg.Data_bit = data_ptr[3];
    ACC_Conifg.ID_map = id_map;

    if (data_ptr[2] == 0)
    {
        // Stop
        ACC_Conifg.Reg_ODR = 0;

        /*
        for (i=0;i<ACC_NUMS;i++)
        {
            if (id_map & ((uint16_t)0x01ul << i))
            {
                Acc_StopMeasure(i);
            }
        }
        */
    } else {
        for (i=0;i<ACC_NUMS;i++)
        {
            if (id_map & ((uint16_t)0x01ul << i))
            {
                // Stop first
                if (Acc_StopMeasure(i) != HAL_OK)
                {
                    Apdu_SetStatus(dev, STS_DATA_ERROR, RESP_NULL);        
                    return;
                }
                HAL_Delay(1);
                if (Acc_StartMeasure(i) != HAL_OK)
                {
                    Apdu_SetStatus(dev, STS_DATA_ERROR, RESP_NULL);        
                    return;
                }
                HAL_Delay(1);
            }
        }

        // update once
        if (ACC_UpdateData(NULL) != HAL_OK)
        {
            Apdu_SetStatus(dev, STS_DATA_ERROR, RESP_NULL);        
            return;
        }
        
        if (data_ptr[2] == 1) {
            ACC_Conifg.Reg_ODR = 0;
        } else {
            // poll data, start trigger
            ACC_Conifg.Reg_ODR = data_ptr[2];
            ACC_Conifg.last_ms = HAL_GetTick();
        }
    }

    Apdu_SetStatus(dev, STS_OK, RESP_NULL);
}


/*** commands ***/
/**
  * @brief  Return information: Chip id, software version, buffer size 
  * @param  dev    device instance
  */
void Apdu_GetVersion(Mb_CmdParaDef* dev)
{
    uint32_t chip_id = 0U;
    uint16_t max_length = APDU_BUFFER_SIZE;

    memset(dummyBuffer, 0U, VERSION_SIZE);
    memcpy(dummyBuffer, &chip_id, sizeof(chip_id));
    memcpy(dummyBuffer + 0x04U, HW_Version, sizeof(HW_Version));
    memcpy(dummyBuffer + 0x0CU, SW_Version, sizeof(SW_Version));
    memcpy(dummyBuffer + 0x14U, &max_length, sizeof(max_length));

    Apdu_SetStatus(dev, STS_OK, dummyBuffer, VERSION_SIZE);
}


void Apdu_WriteRegisterSingle(Mb_CmdParaDef* dev)
{
    uint16_t i;
    uint8_t* data_ptr = dev->buffer;
    uint16_t pdu_len;
    uint16_t id_map = 0;
    uint16_t j;
    uint16_t reg_nums;
    uint8_t* reg_ptr;
    HAL_StatusTypeDef ret_val;
    
    pdu_len = data_ptr[0] | (((uint16_t)data_ptr[1]) << 8);
    if (pdu_len & 0x01)
    {
        Apdu_SetStatus(dev, STS_LEN_ERROR, RESP_NULL);
        return;
    }

    id_map = data_ptr[2] | (((uint16_t)data_ptr[3]) << 8);
    reg_nums = (pdu_len - 2) / 2;

    //start write
    for (i=0;i<ACC_NUMS;i++)
    {
        reg_ptr = data_ptr + 4;

        if (id_map & ((uint16_t)0x01ul << i))
        {
            for (j=0;j<reg_nums;j++)
            {
                ret_val = Acc_RegisterWrite(i, reg_ptr[0], reg_ptr+1, 1);
                if (ret_val != HAL_OK)
                {
                    Apdu_SetStatus(dev, STS_DATA_ERROR, RESP_NULL);
                    return;
                }

                reg_ptr += 2;
            }
        }
    }

    Apdu_SetStatus(dev, STS_OK, RESP_NULL);
}


void Apdu_WriteRegisterContinuous(Mb_CmdParaDef* dev)
{
    uint16_t i;
    uint8_t* data_ptr = dev->buffer;
    uint16_t pdu_len;
    uint16_t id_map = 0;
    uint16_t reg_nums;
    uint8_t* reg_ptr;
    HAL_StatusTypeDef ret_val;
    
    pdu_len = data_ptr[0] | (((uint16_t)data_ptr[1]) << 8);
    id_map = data_ptr[2] | (((uint16_t)data_ptr[3]) << 8);
    reg_nums = pdu_len - 3;
    reg_ptr = data_ptr + 4;
    
    for (i=0;i<ACC_NUMS;i++)
    {
        if (id_map & ((uint16_t)0x01ul << i))
        {
            ret_val = Acc_RegisterWrite(i, reg_ptr[0], reg_ptr+1, reg_nums);
            if (ret_val != HAL_OK)
            {
                Apdu_SetStatus(dev, STS_DATA_ERROR, RESP_NULL);
                return;
            }
        }
    }

    Apdu_SetStatus(dev, STS_OK, RESP_NULL);
}


void Apdu_ReadRegisterSingle(Mb_CmdParaDef* dev)
{
    uint16_t i;
    uint8_t* data_ptr = dev->buffer;
    uint16_t pdu_len;
    uint16_t id_map = 0;
    uint16_t j;
    uint16_t sum = 0;
    uint16_t reg_nums;
    uint8_t* reg_ptr;
    uint8_t* out_ptr;
    HAL_StatusTypeDef ret_val;
    
    pdu_len = data_ptr[0] | (((uint16_t)data_ptr[1]) << 8);
    id_map = data_ptr[2] | (((uint16_t)data_ptr[3]) << 8);
    reg_nums = pdu_len - 2;

    // check data length
    for (i=0;i<ACC_NUMS;i++)
    {
        if (id_map & ((uint16_t)0x01ul << i))
        {
            sum++;
        }
    }
    
    if ((sum * reg_nums + 2) > APDU_BUFFER_SIZE)
    {
        Apdu_SetStatus(dev, STS_OVFLOW_ERROR, RESP_NULL);
        return;
    }

    //start read
    out_ptr = dummyBuffer;
    for (i=0;i<ACC_NUMS;i++)
    {
        reg_ptr = data_ptr + 4;

        if (id_map & ((uint16_t)0x01ul << i))
        {
            for (j=0;j<reg_nums;j++)
            {
                ret_val = Acc_RegisterRead(i, reg_ptr[0], out_ptr, 1);
                if (ret_val != HAL_OK)
                {
                    Apdu_SetStatus(dev, STS_DATA_ERROR, RESP_NULL);
                    return;
                }

                reg_ptr++;
                out_ptr++;
            }
        }
    }

    Apdu_SetStatus(dev, STS_OK, dummyBuffer, sum * reg_nums);
}


void Apdu_ReadRegisterContinuous(Mb_CmdParaDef* dev)
{
    uint16_t i;
    uint8_t* data_ptr = dev->buffer;
    uint16_t pdu_len;
    uint16_t id_map = 0;
    uint16_t sum = 0;
    uint16_t reg_nums;
    uint8_t* reg_ptr;
    uint8_t* out_ptr;
    HAL_StatusTypeDef ret_val;

    pdu_len = data_ptr[0] | (((uint16_t)data_ptr[1]) << 8);
    if (pdu_len != 4)
    {
        Apdu_SetStatus(dev, STS_LEN_ERROR, RESP_NULL);
        return;
    }

    id_map = data_ptr[2] | (((uint16_t)data_ptr[3]) << 8);
    reg_ptr = data_ptr + 4;
    reg_nums = reg_ptr[1];

    // check data length
    for (i=0;i<ACC_NUMS;i++)
    {
        if (id_map & ((uint16_t)0x01ul << i))
        {
            sum++;
        }
    }
    
    if ((sum * reg_nums + 2) > APDU_BUFFER_SIZE)
    {
        Apdu_SetStatus(dev, STS_OVFLOW_ERROR, RESP_NULL);
        return;
    }

    out_ptr = dummyBuffer;
    for (i=0;i<ACC_NUMS;i++)
    {
        if (id_map & ((uint16_t)0x01ul << i))
        {
            ret_val = Acc_RegisterRead(i, reg_ptr[0], out_ptr, reg_nums);
            if (ret_val != HAL_OK)
            {
                Apdu_SetStatus(dev, STS_DATA_ERROR, RESP_NULL);
                return;
            }

            out_ptr += reg_nums;
        }
    }

    Apdu_SetStatus(dev, STS_OK, dummyBuffer, sum * reg_nums);
}


void Apdu_MeasureCalc(Mb_CmdParaDef* dev)
{
    uint16_t i;
    uint16_t j;
    uint8_t* data_ptr = dev->buffer;
    uint16_t id_map = 0;
    uint8_t interval;
    uint16_t count;
    uint8_t type;
    uint8_t res_size;
    uint8_t* calc_ptr;
    uint8_t* curr_ptr;
    uint8_t* out_ptr;
    int32_t avg_X;
    int32_t avg_Y;
    int32_t avg_Z;
    int32_t td_X;
    int32_t td_Y;
    int32_t td_Z;
    int32_t tmp;
    uint16_t sum = 0;
    uint32_t tickstart;
    
    id_map = data_ptr[0] | (((uint16_t)data_ptr[1]) << 8);
    interval = data_ptr[2];
    count = data_ptr[3] | (((uint16_t)data_ptr[4]) << 8);
    type = data_ptr[5];

    if ((type == 0) || (type == 1))
    {
        //avg & td
        res_size = 2;
    } else {
        Apdu_SetStatus(dev, STS_PARAM_ERROR, RESP_NULL);
        return;
    }

    
    // check data length
    for (i=0;i<ACC_NUMS;i++)
    {
        if (id_map & ((uint16_t)0x01ul << i))
        {
            sum++;
        }
    }

    if ((res_size * sum * 3 + 2) > APDU_BUFFER_SIZE)
    {
        Apdu_SetStatus(dev, STS_OVFLOW_ERROR, RESP_NULL);
        return;
    }
    
    curr_ptr = (uint8_t*)calcBuffer;
    out_ptr = dummyBuffer;
    for (i=0;i<ACC_NUMS;i++)
    {
        if (id_map & ((uint16_t)0x01ul << i))
        {
            calc_ptr = (uint8_t*)calcBuffer;
            avg_X = 0;
            avg_Y = 0;
            avg_Z = 0;
            td_X = 0;
            td_Y = 0;
            td_Z = 0;

            for (j=0;j<count;j++)
            {
                tickstart = HAL_GetTick();

                if (ACC_ReadData(i, calc_ptr, 500) != HAL_OK)
                {
                    Apdu_SetStatus(dev, STS_DATA_ERROR, RESP_NULL);
                    return;
                }

                //sum
                avg_X += (((int32_t)((int8_t)calc_ptr[1]))<<8)|calc_ptr[0];
                avg_Y += (((int32_t)((int8_t)calc_ptr[3]))<<8)|calc_ptr[2];
                avg_Z += (((int32_t)((int8_t)calc_ptr[5]))<<8)|calc_ptr[4];
                calc_ptr += 6;

                // wait
                //HAL_Delay(interval);
                while ((HAL_GetTick() - tickstart) < interval)
                {
                }
            }

            // calculate
            avg_X /= count;
            avg_Y /= count;
            avg_Z /= count;

            if (type == 0)
            {
                memcpy(out_ptr, &avg_X, res_size);
                memcpy(out_ptr+res_size, &avg_Y, res_size);
                memcpy(out_ptr+res_size*2, &avg_Z, res_size);
            } else if (type == 1) {
                for (j=0;j<count;j++)
                {
                    //std
                    tmp = (((int32_t)((int8_t)curr_ptr[6*j+1]))<<8)|curr_ptr[6*j];
                    td_X += (tmp - avg_X) * (tmp - avg_X);
                    tmp = (((int32_t)((int8_t)curr_ptr[6*j+3]))<<8)|curr_ptr[6*j+2];
                    td_Y += (tmp - avg_Y) * (tmp - avg_Y);
                    tmp = (((int32_t)((int8_t)curr_ptr[6*j+5]))<<8)|curr_ptr[6*j+4];
                    td_Z += (tmp - avg_Z) * (tmp - avg_Z);
                }

                td_X /= count;
                td_Y /= count;
                td_Z /= count;
                memcpy(out_ptr, &td_X, res_size);
                memcpy(out_ptr+res_size, &td_Y, res_size);
                memcpy(out_ptr+res_size*2, &td_Z, res_size);
            }

            out_ptr += res_size * 3;
        }
    }
    
    Apdu_SetStatus(dev, STS_OK, dummyBuffer, res_size * 3 * sum);
}


void Apdu_ReadBuffer(Mb_CmdParaDef* dev)
{
    uint8_t* data_ptr = dev->buffer;
    uint16_t offset;
    uint8_t r_len;
    
    offset = data_ptr[0] | (((uint16_t)data_ptr[1]) << 8);
    r_len = data_ptr[2];
    if ((offset+r_len) > MAX_CALC_SIZE*6)
    {
        Apdu_SetStatus(dev, STS_OVFLOW_ERROR, RESP_NULL);
        return;
    }

    Apdu_SetStatus(dev, STS_OK, ((uint8_t*)calcBuffer) + offset, r_len);
}


extern void Acc_MbUpdateStatus(void);

void Apdu_SetFunction(Mb_CmdParaDef* dev)
{
    uint8_t* data_ptr = dev->buffer;
    uint8_t cmdID;
    
    cmdID = data_ptr[0];

    if (cmdID == 1)
    {
        Acc_MbUpdateStatus();
    } else {
        Apdu_SetStatus(dev, STS_NOT_SUPPORT, RESP_NULL);
        return;
    }

    Apdu_SetStatus(dev, STS_OK, RESP_NULL);
}
