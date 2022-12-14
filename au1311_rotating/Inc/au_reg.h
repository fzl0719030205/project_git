/**
  ******************************************************************************
  * @file           : au_reg.h
  * @brief          : This file contains the common definition of au registers.
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
#ifndef __AU_REG_H
#define __AU_REG_H

#ifdef __cplusplus
extern "C" {
#endif /*_cplusplus*/

/* Includes ------------------------------------------------------------------*/
/* Private includes ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#define CHIP_ID_DEFAULT     0x78u

#define CHIP_ID_REG         0x00u

#define SOFT_RESET_REG      0x01u
#define SOFT_RESET_OFF      0x00u
#define SOFT_RESET_BIT      0x01u

#define CLK_CTRL_REG        0x02u
#define PD_ODR_CLK_OFF      0x00u
#define ODR_SEL_BCLKOFF     0x01u
#define ADC_CLK_OFF         0x03u
#define ADC_CLK_POL_OFF     0x05u
#define ST_POL_OFF          0x07u

#define PWR_CTRL_REG        0x03u
#define PWR_MODE_OFF        0x00u
#define PWR_CTRL_EN_OFF     0x02u
#define ODR_48K_SEL_OFF     0x04u
#define ADC_BACKUP_SEL_OFF  0x05u
#define TMPS_CLK_SEL_OFF    0x06u
  
#define OTP_CTRL_REG        0x04u
#define OTP_PROG_CLK_EN_OFF 0x01u
#define OTP_PROG_EN_OFF     0x02u
#define OTP_MR_OFF          0x03u

#define TDM_CTRL_REG        0x05u
#define TDM_CMAX_H_OFF      0x00u
#define TDM_TS_DATA_EN_OFF  0x04u
#define TDM_SLOT_MAP_OFF    0x05u
#define TDM_PHASE_OFF       0x06u
#define TDM_DELAY_OFF       0x07u

#define TDM_CMAX_LOW        0x06u
  
#define SPI_DATA_VALID      0x08u

#define HPF_SEL             0x75u
#define HPF_SEL_OFF         0x06u
  
#define SPI_X_16BIT_M       0x7au
#define SPI_X_16BIT_L       0x7bu
#define SPI_Y_16BIT_M       0x7cu
#define SPI_Y_16BIT_L       0x7du
#define SPI_Z_16BIT_M       0x7eu
#define SPI_Z_16BIT_L       0x7fu

#define TDM_X_H             0x80u
#define TDM_X_M             0x81u
#define TDM_X_L             0x82u
#define TDM_Y_H             0x83u
#define TDM_Y_M             0x84u
#define TDM_Y_L             0x85u
#define TDM_Z_H             0x86u
#define TDM_Z_M             0x87u
#define TDM_Z_L             0x88u
  
#define SPI_X_H             0x89u
#define SPI_X_M             0x8au
#define SPI_X_L             0x8bu
#define SPI_Y_H             0x8cu
#define SPI_Y_M             0x8du
#define SPI_Y_L             0x8eu
#define SPI_Z_H             0x8fu
#define SPI_Z_M             0x90u
#define SPI_Z_L             0x91u

#define TEMP_DATA_H         0x92u
#define TEMP_DATA_M         0x93u
#define TEMP_DATA_L         0x94u
  
#define TDM_SELF_X_H        0x95u
#define TDM_SELF_X_M        0x96u
#define TDM_SELF_X_L        0x97u
#define TDM_SELF_Y_H        0x98u
#define TDM_SELF_Y_M        0x99u
#define TDM_SELF_Y_L        0x9au
#define TDM_SELF_Z_H        0x9bu
#define TDM_SELF_Z_M        0x9cu
#define TDM_SELF_Z_L        0x9du

  
#define PWR_MODE_STDBY      0x00u
#define PWR_MODE_NORMA      0x01u
#define PWR_MODE_PD         0x10u

#define ODR_BCLK_SEL_MASK   0x06u
#define TMPS_CLK_SEL_MASK   0xc0u
#define PWR_MODE_MASK       0x03u
#define OTP_MR_MASK         0x18u
#define TDM_CMAX_H_MASK     0x0fu
#define HPF_SEL_MASK        0xc0u
  
#define DATA_VALID          0x01u
  
/* Exported functions --------------------------------------------------------*/


#ifdef __cplusplus
}
#endif /*_cplusplus*/

#endif /* __AU_REG_H */
