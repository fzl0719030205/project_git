/**
  ******************************************************************************
  * @file           : bma280.h
  * @brief          : bma280 driver header file
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
#ifndef __BMA280_H
#define __BMA280_H

#ifdef __cplusplus
extern "C" {
#endif /*_cplusplus*/

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "string.h"

/* Private includes ----------------------------------------------------------*/
#include "common_def.h"
#include "user_config.h"
  
/* Exported types ------------------------------------------------------------*/
typedef uint8_t u8;

/* Exported constants --------------------------------------------------------*/

#define BMA280_ID                               0xFBu

/**************************************************************/
/**\name    CONSTANTS DEFINITION    */
/**************************************************************/
#define BMA2x2_INIT_VALUE                       ((u8)0)
#define BMA2x2_GEN_READ_WRITE_LENGTH            ((u8)1)
#define BMA2x2_INTERFACE_IDLE_TIME_DELAY        ((u8)1)
#define BMA2x2_LSB_MSB_READ_LENGTH              ((u8)2)
/** BIT SHIFT DEFINITIONS    */
#define BMA2x2_SHIFT_TWO_BITS                   ((u8)2)
#define BMA2x2_SHIFT_FOUR_BITS                  ((u8)4)
#define BMA2x2_SHIFT_FIVE_BITS                  ((u8)5)
#define BMA2x2_SHIFT_SIX_BITS                   ((u8)6)
#define BMA2x2_SHIFT_EIGHT_BITS                 ((u8)8)
/** FIFO DEFINITIONS    */
#define BMA2x2_FIFO_MODE_STATUS_RANGE           ((u8)2)
#define BMA2x2_FIFO_DATA_SELECT_RANGE           ((u8)4)
#define BMA2x2_FIFO_MODE_RANGE                  ((u8)4)
#define BMA2x2_FIFO_WML_RANGE                   ((u8)32)

#define BMA2x2_FIFO_XYZ_DATA_ENABLED            (0x00)
#define BMA2x2_FIFO_X_DATA_ENABLED              (0x01)
#define BMA2x2_FIFO_Y_DATA_ENABLED              (0x02)
#define BMA2x2_FIFO_Z_DATA_ENABLED              (0x03)
#define BMA2x2_FIFO_DATA_ENABLED_MASK           (0x03)
#define BMA2x2_FIFO_XYZ_AXES_FRAME_SIZE         ((u8)6)
#define BMA2x2_FIFO_SINGLE_AXIS_FRAME_SIZE      ((u8)2)
/** MODE RANGES    */
#define BMA2x2_ACCEL_BW_MIN_RANGE               ((u8)7)
#define BMA2x2_ACCEL_BW_1000HZ_RANGE            ((u8)15)
#define BMA2x2_ACCEL_BW_MAX_RANGE               ((u8)16)
#define BMA2x2_SLEEP_DURN_MIN_RANGE             ((u8)4)
#define BMA2x2_SLEEP_TIMER_MODE_RANGE           ((u8)2)
#define BMA2x2_SLEEP_DURN_MAX_RANGE             ((u8)16)
#define BMA2x2_POWER_MODE_RANGE                 ((u8)6)
#define BMA2x2_SELF_TEST_AXIS_RANGE             ((u8)4)
#define BMA2x2_SELF_TEST_SIGN_RANGE             ((u8)2)

/**************************************************************/
/**\name    REGISTER ADDRESS DEFINITIONS    */
/**************************************************************/
#define BMA2x2_EEP_OFFSET                       (0x16)
#define BMA2x2_IMAGE_BASE                       (0x38)
#define BMA2x2_IMAGE_LEN                        (22)
#define BMA2x2_CHIP_ID_ADDR                     (0x00)
/** DATA ADDRESS DEFINITIONS */
#define BMA2x2_X_AXIS_LSB_ADDR                  (0x02)
#define BMA2x2_X_AXIS_MSB_ADDR                  (0x03)
#define BMA2x2_Y_AXIS_LSB_ADDR                  (0x04)
#define BMA2x2_Y_AXIS_MSB_ADDR                  (0x05)
#define BMA2x2_Z_AXIS_LSB_ADDR                  (0x06)
#define BMA2x2_Z_AXIS_MSB_ADDR                  (0x07)
#define BMA2x2_TEMP_ADDR                        (0x08)
/**STATUS ADDRESS DEFINITIONS */
#define BMA2x2_STAT1_ADDR                       (0x09)
#define BMA2x2_STAT2_ADDR                       (0x0A)
#define BMA2x2_STAT_TAP_SLOPE_ADDR              (0x0B)
#define BMA2x2_STAT_ORIENT_HIGH_ADDR            (0x0C)
#define BMA2x2_STAT_FIFO_ADDR                   (0x0E)
/**STATUS ADDRESS DEFINITIONS */
#define BMA2x2_RANGE_SELECT_ADDR                (0x0F)
#define BMA2x2_BW_SELECT_ADDR                   (0x10)
#define BMA2x2_MODE_CTRL_ADDR                   (0x11)
#define BMA2x2_LOW_NOISE_CTRL_ADDR              (0x12)
#define BMA2x2_DATA_CTRL_ADDR                   (0x13)
#define BMA2x2_RST_ADDR                         (0x14)
/**INTERUPT ADDRESS DEFINITIONS */
#define BMA2x2_INTR_ENABLE1_ADDR                (0x16)
#define BMA2x2_INTR_ENABLE2_ADDR                (0x17)
#define BMA2x2_INTR_SLOW_NO_MOTION_ADDR         (0x18)
#define BMA2x2_INTR1_PAD_SELECT_ADDR            (0x19)
#define BMA2x2_INTR_DATA_SELECT_ADDR            (0x1A)
#define BMA2x2_INTR2_PAD_SELECT_ADDR            (0x1B)
#define BMA2x2_INTR_SOURCE_ADDR                 (0x1E)
#define BMA2x2_INTR_SET_ADDR                    (0x20)
#define BMA2x2_INTR_CTRL_ADDR                   (0x21)
/** FEATURE ADDRESS DEFINITIONS */
#define BMA2x2_LOW_DURN_ADDR                     (0x22)
#define BMA2x2_LOW_THRES_ADDR                    (0x23)
#define BMA2x2_LOW_HIGH_HYST_ADDR                (0x24)
#define BMA2x2_HIGH_DURN_ADDR                    (0x25)
#define BMA2x2_HIGH_THRES_ADDR                   (0x26)
#define BMA2x2_SLOPE_DURN_ADDR                   (0x27)
#define BMA2x2_SLOPE_THRES_ADDR                  (0x28)
#define BMA2x2_SLOW_NO_MOTION_THRES_ADDR         (0x29)
#define BMA2x2_TAP_PARAM_ADDR                    (0x2A)
#define BMA2x2_TAP_THRES_ADDR                    (0x2B)
#define BMA2x2_ORIENT_PARAM_ADDR                 (0x2C)
#define BMA2x2_THETA_BLOCK_ADDR                  (0x2D)
#define BMA2x2_THETA_FLAT_ADDR                   (0x2E)
#define BMA2x2_FLAT_HOLD_TIME_ADDR               (0x2F)
#define BMA2x2_SELFTEST_ADDR                     (0x32)
#define BMA2x2_EEPROM_CTRL_ADDR                  (0x33)
#define BMA2x2_SERIAL_CTRL_ADDR                  (0x34)
/**OFFSET ADDRESS DEFINITIONS */
#define BMA2x2_OFFSET_CTRL_ADDR                  (0x36)
#define BMA2x2_OFFSET_PARAMS_ADDR                (0x37)
#define BMA2x2_OFFSET_X_AXIS_ADDR                (0x38)
#define BMA2x2_OFFSET_Y_AXIS_ADDR                (0x39)
#define BMA2x2_OFFSET_Z_AXIS_ADDR                (0x3A)
/**GP ADDRESS DEFINITIONS */
#define BMA2x2_GP0_ADDR                          (0x3B)
#define BMA2x2_GP1_ADDR                          (0x3C)
/**FIFO ADDRESS DEFINITIONS */
#define BMA2x2_FIFO_MODE_ADDR                    (0x3E)
#define BMA2x2_FIFO_DATA_OUTPUT_ADDR             (0x3F)
#define BMA2x2_FIFO_WML_TRIG                     (0x30)

/**************************************************************/
/**\name    ACCEL RESOLUTION DEFINITION   */
/**************************************************************/
#define BMA2x2_12_RESOLUTION                    (0)
#define BMA2x2_10_RESOLUTION                    (1)
#define BMA2x2_14_RESOLUTION                    (2)

/**************************************************************/
/**\name    ACCEL DELAY DEFINITION   */
/**************************************************************/
/* register write and read delays */
#define BMA2x2_MDELAY_DATA_TYPE                 u32
#define BMA2x2_EE_W_DELAY                       (28)

/*********************************************************************/
/**\name REGISTER BIT MASK, BIT LENGTH, BIT POSITION DEFINITIONS  */
/********************************************************************/
/******************************/
/**\name CHIP ID  */
/******************************/
#define BMA2x2_CHIP_ID_POS             (0)
#define BMA2x2_CHIP_ID_MSK             (0xFF)
#define BMA2x2_CHIP_ID_LEN             (8)
#define BMA2x2_CHIP_ID_REG             BMA2x2_CHIP_ID_ADDR

/******************************/
/**\name DATA REGISTER-X  */
/******************************/
#define BMA2x2_NEW_DATA_X_POS          (0)
#define BMA2x2_NEW_DATA_X_LEN          (1)
#define BMA2x2_NEW_DATA_X_MSK          (0x01)
#define BMA2x2_NEW_DATA_X_REG          BMA2x2_X_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_X14_LSB_POS          (2)
#define BMA2x2_ACCEL_X14_LSB_LEN          (6)
#define BMA2x2_ACCEL_X14_LSB_MSK          (0xFC)
#define BMA2x2_ACCEL_X14_LSB_REG           BMA2x2_X_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_X12_LSB_POS           (4)
#define BMA2x2_ACCEL_X12_LSB_LEN           (4)
#define BMA2x2_ACCEL_X12_LSB_MSK           (0xF0)
#define BMA2x2_ACCEL_X12_LSB_REG           BMA2x2_X_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_X10_LSB_POS           (6)
#define BMA2x2_ACCEL_X10_LSB_LEN           (2)
#define BMA2x2_ACCEL_X10_LSB_MSK           (0xC0)
#define BMA2x2_ACCEL_X10_LSB_REG           BMA2x2_X_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_X8_LSB_POS           (0)
#define BMA2x2_ACCEL_X8_LSB_LEN           (0)
#define BMA2x2_ACCEL_X8_LSB_MSK           (0x00)
#define BMA2x2_ACCEL_X8_LSB_REG           BMA2x2_X_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_X_MSB_POS           (0)
#define BMA2x2_ACCEL_X_MSB_LEN           (8)
#define BMA2x2_ACCEL_X_MSB_MSK           (0xFF)
#define BMA2x2_ACCEL_X_MSB_REG           BMA2x2_X_AXIS_MSB_ADDR
/******************************/
/**\name DATA REGISTER-Y  */
/******************************/
#define BMA2x2_NEW_DATA_Y_POS          (0)
#define BMA2x2_NEW_DATA_Y_LEN          (1)
#define BMA2x2_NEW_DATA_Y_MSK          (0x01)
#define BMA2x2_NEW_DATA_Y_REG          BMA2x2_Y_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Y14_LSB_POS           (2)
#define BMA2x2_ACCEL_Y14_LSB_LEN           (6)
#define BMA2x2_ACCEL_Y14_LSB_MSK           (0xFC)
#define BMA2x2_ACCEL_Y14_LSB_REG           BMA2x2_Y_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Y12_LSB_POS           (4)
#define BMA2x2_ACCEL_Y12_LSB_LEN           (4)
#define BMA2x2_ACCEL_Y12_LSB_MSK           (0xF0)
#define BMA2x2_ACCEL_Y12_LSB_REG           BMA2x2_Y_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Y10_LSB_POS           (6)
#define BMA2x2_ACCEL_Y10_LSB_LEN           (2)
#define BMA2x2_ACCEL_Y10_LSB_MSK           (0xC0)
#define BMA2x2_ACCEL_Y10_LSB_REG           BMA2x2_Y_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Y8_LSB_POS           (0)
#define BMA2x2_ACCEL_Y8_LSB_LEN           (0)
#define BMA2x2_ACCEL_Y8_LSB_MSK           (0x00)
#define BMA2x2_ACCEL_Y8_LSB_REG           BMA2x2_Y_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Y_MSB_POS           (0)
#define BMA2x2_ACCEL_Y_MSB_LEN           (8)
#define BMA2x2_ACCEL_Y_MSB_MSK           (0xFF)
#define BMA2x2_ACCEL_Y_MSB_REG           BMA2x2_Y_AXIS_MSB_ADDR
/******************************/
/**\name DATA REGISTER-Z  */
/******************************/
#define BMA2x2_NEW_DATA_Z_POS          (0)
#define BMA2x2_NEW_DATA_Z_LEN          (1)
#define BMA2x2_NEW_DATA_Z_MSK          (0x01)
#define BMA2x2_NEW_DATA_Z_REG          BMA2x2_Z_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Z14_LSB_POS           (2)
#define BMA2x2_ACCEL_Z14_LSB_LEN           (6)
#define BMA2x2_ACCEL_Z14_LSB_MSK           (0xFC)
#define BMA2x2_ACCEL_Z14_LSB_REG           BMA2x2_Z_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Z12_LSB_POS           (4)
#define BMA2x2_ACCEL_Z12_LSB_LEN           (4)
#define BMA2x2_ACCEL_Z12_LSB_MSK           (0xF0)
#define BMA2x2_ACCEL_Z12_LSB_REG           BMA2x2_Z_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Z10_LSB_POS           (6)
#define BMA2x2_ACCEL_Z10_LSB_LEN           (2)
#define BMA2x2_ACCEL_Z10_LSB_MSK           (0xC0)
#define BMA2x2_ACCEL_Z10_LSB_REG           BMA2x2_Z_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Z8_LSB_POS           (0)
#define BMA2x2_ACCEL_Z8_LSB_LEN           (0)
#define BMA2x2_ACCEL_Z8_LSB_MSK           (0x00)
#define BMA2x2_ACCEL_Z8_LSB_REG           BMA2x2_Z_AXIS_LSB_ADDR

#define BMA2x2_ACCEL_Z_MSB_POS           (0)
#define BMA2x2_ACCEL_Z_MSB_LEN           (8)
#define BMA2x2_ACCEL_Z_MSB_MSK           (0xFF)
#define BMA2x2_ACCEL_Z_MSB_REG           BMA2x2_Z_AXIS_MSB_ADDR

/******************************/
/**\name TEMPERATURE */
/******************************/
#define BMA2x2_ACCEL_TEMP_MSB_POS           (0)
#define BMA2x2_ACCEL_TEMP_MSB_LEN           (8)
#define BMA2x2_ACCEL_TEMP_MSB_MSK           (0xFF)
#define BMA2x2_ACCEL_TEMP_MSB_REG           BMA2x2_TEMPERATURE_REG

/***************************************/
/**\name INTERRUPT STATUS OF LOW-G */
/**************************************/
#define BMA2x2_LOW_G_INTR_STAT_POS          (0)
#define BMA2x2_LOW_G_INTR_STAT_LEN          (1)
#define BMA2x2_LOW_G_INTR_STAT_MSK          (0x01)
#define BMA2x2_LOW_G_INTR_STAT_REG          BMA2x2_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF HIGH-G */
/**************************************/
#define BMA2x2_HIGH_G_INTR_STAT_POS          (1)
#define BMA2x2_HIGH_G_INTR_STAT_LEN          (1)
#define BMA2x2_HIGH_G_INTR_STAT_MSK          (0x02)
#define BMA2x2_HIGH_G_INTR_STAT_REG          BMA2x2_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF SLOPE */
/**************************************/
#define BMA2x2_SLOPE_INTR_STAT_POS          (2)
#define BMA2x2_SLOPE_INTR_STAT_LEN          (1)
#define BMA2x2_SLOPE_INTR_STAT_MSK          (0x04)
#define BMA2x2_SLOPE_INTR_STAT_REG          BMA2x2_STAT1_ADDR
/*******************************************/
/**\name INTERRUPT STATUS OF SLOW NO MOTION*/
/*******************************************/
#define BMA2x2_SLOW_NO_MOTION_INTR_STAT_POS          (3)
#define BMA2x2_SLOW_NO_MOTION_INTR_STAT_LEN          (1)
#define BMA2x2_SLOW_NO_MOTION_INTR_STAT_MSK          (0x08)
#define BMA2x2_SLOW_NO_MOTION_INTR_STAT_REG          BMA2x2_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF DOUBLE TAP */
/**************************************/
#define BMA2x2_DOUBLE_TAP_INTR_STAT_POS     (4)
#define BMA2x2_DOUBLE_TAP_INTR_STAT_LEN     (1)
#define BMA2x2_DOUBLE_TAP_INTR_STAT_MSK     (0x10)
#define BMA2x2_DOUBLE_TAP_INTR_STAT_REG     BMA2x2_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF SINGLE TAP */
/**************************************/
#define BMA2x2_SINGLE_TAP_INTR_STAT_POS     (5)
#define BMA2x2_SINGLE_TAP_INTR_STAT_LEN     (1)
#define BMA2x2_SINGLE_TAP_INTR_STAT_MSK     (0x20)
#define BMA2x2_SINGLE_TAP_INTR_STAT_REG     BMA2x2_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF ORIENT*/
/**************************************/
#define BMA2x2_ORIENT_INTR_STAT_POS         (6)
#define BMA2x2_ORIENT_INTR_STAT_LEN         (1)
#define BMA2x2_ORIENT_INTR_STAT_MSK         (0x40)
#define BMA2x2_ORIENT_INTR_STAT_REG         BMA2x2_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF FLAT */
/**************************************/
#define BMA2x2_FLAT_INTR_STAT_POS           (7)
#define BMA2x2_FLAT_INTR_STAT_LEN           (1)
#define BMA2x2_FLAT_INTR_STAT_MSK           (0x80)
#define BMA2x2_FLAT_INTR_STAT_REG           BMA2x2_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF FIFO FULL */
/**************************************/
#define BMA2x2_FIFO_FULL_INTR_STAT_POS           (5)
#define BMA2x2_FIFO_FULL_INTR_STAT_LEN           (1)
#define BMA2x2_FIFO_FULL_INTR_STAT_MSK           (0x20)
#define BMA2x2_FIFO_FULL_INTR_STAT_REG           BMA2x2_STAT2_ADDR
/*******************************************/
/**\name INTERRUPT STATUS OF FIFO WATERMARK*/
/******************************************/
#define BMA2x2_FIFO_WM_INTR_STAT_POS           (6)
#define BMA2x2_FIFO_WM_INTR_STAT_LEN           (1)
#define BMA2x2_FIFO_WM_INTR_STAT_MSK           (0x40)
#define BMA2x2_FIFO_WM_INTR_STAT_REG           BMA2x2_STAT2_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF DATA */
/**************************************/
#define BMA2x2_DATA_INTR_STAT_POS           (7)
#define BMA2x2_DATA_INTR_STAT_LEN           (1)
#define BMA2x2_DATA_INTR_STAT_MSK           (0x80)
#define BMA2x2_DATA_INTR_STAT_REG           BMA2x2_STAT2_ADDR
/*********************************************/
/**\name INTERRUPT STATUS SLOPE XYZ AND SIGN */
/*********************************************/
#define BMA2x2_SLOPE_FIRST_X_POS        (0)
#define BMA2x2_SLOPE_FIRST_X_LEN        (1)
#define BMA2x2_SLOPE_FIRST_X_MSK        (0x01)
#define BMA2x2_SLOPE_FIRST_X_REG        BMA2x2_STAT_TAP_SLOPE_ADDR

#define BMA2x2_SLOPE_FIRST_Y_POS        (1)
#define BMA2x2_SLOPE_FIRST_Y_LEN        (1)
#define BMA2x2_SLOPE_FIRST_Y_MSK        (0x02)
#define BMA2x2_SLOPE_FIRST_Y_REG        BMA2x2_STAT_TAP_SLOPE_ADDR

#define BMA2x2_SLOPE_FIRST_Z_POS        (2)
#define BMA2x2_SLOPE_FIRST_Z_LEN        (1)
#define BMA2x2_SLOPE_FIRST_Z_MSK        (0x04)
#define BMA2x2_SLOPE_FIRST_Z_REG        BMA2x2_STAT_TAP_SLOPE_ADDR

#define BMA2x2_SLOPE_SIGN_STAT_POS         (3)
#define BMA2x2_SLOPE_SIGN_STAT_LEN         (1)
#define BMA2x2_SLOPE_SIGN_STAT_MSK         (0x08)
#define BMA2x2_SLOPE_SIGN_STAT_REG         BMA2x2_STAT_TAP_SLOPE_ADDR
/*********************************************/
/**\name INTERRUPT STATUS TAP XYZ AND SIGN */
/*********************************************/
#define BMA2x2_TAP_FIRST_X_POS        (4)
#define BMA2x2_TAP_FIRST_X_LEN        (1)
#define BMA2x2_TAP_FIRST_X_MSK        (0x10)
#define BMA2x2_TAP_FIRST_X_REG        BMA2x2_STAT_TAP_SLOPE_ADDR

#define BMA2x2_TAP_FIRST_Y_POS        (5)
#define BMA2x2_TAP_FIRST_Y_LEN        (1)
#define BMA2x2_TAP_FIRST_Y_MSK        (0x20)
#define BMA2x2_TAP_FIRST_Y_REG        BMA2x2_STAT_TAP_SLOPE_ADDR

#define BMA2x2_TAP_FIRST_Z_POS        (6)
#define BMA2x2_TAP_FIRST_Z_LEN        (1)
#define BMA2x2_TAP_FIRST_Z_MSK        (0x40)
#define BMA2x2_TAP_FIRST_Z_REG        BMA2x2_STAT_TAP_SLOPE_ADDR

#define BMA2x2_TAP_SIGN_STAT_POS         (7)
#define BMA2x2_TAP_SIGN_STAT_LEN         (1)
#define BMA2x2_TAP_SIGN_STAT_MSK         (0x80)
#define BMA2x2_TAP_SIGN_STAT_REG         BMA2x2_STAT_TAP_SLOPE_ADDR
/*********************************************/
/**\name INTERRUPT STATUS HIGH_G XYZ AND SIGN */
/*********************************************/
#define BMA2x2_HIGH_G_FIRST_X_POS        (0)
#define BMA2x2_HIGH_G_FIRST_X_LEN        (1)
#define BMA2x2_HIGH_G_FIRST_X_MSK        (0x01)
#define BMA2x2_HIGH_G_FIRST_X_REG        BMA2x2_STAT_ORIENT_HIGH_ADDR

#define BMA2x2_HIGH_G_FIRST_Y_POS        (1)
#define BMA2x2_HIGH_G_FIRST_Y_LEN        (1)
#define BMA2x2_HIGH_G_FIRST_Y_MSK        (0x02)
#define BMA2x2_HIGH_G_FIRST_Y_REG        BMA2x2_STAT_ORIENT_HIGH_ADDR

#define BMA2x2_HIGH_G_FIRST_Z_POS        (2)
#define BMA2x2_HIGH_G_FIRST_Z_LEN        (1)
#define BMA2x2_HIGH_G_FIRST_Z_MSK        (0x04)
#define BMA2x2_HIGH_G_FIRST_Z_REG        BMA2x2_STAT_ORIENT_HIGH_ADDR

#define BMA2x2_HIGH_G_SIGN_STAT_POS         (3)
#define BMA2x2_HIGH_G_SIGN_STAT_LEN         (1)
#define BMA2x2_HIGH_G_SIGN_STAT_MSK         (0x08)
#define BMA2x2_HIGH_G_SIGN_STAT_REG         BMA2x2_STAT_ORIENT_HIGH_ADDR
/*********************************************/
/**\name INTERRUPT STATUS ORIENT */
/*********************************************/
#define BMA2x2_ORIENT_STAT_POS             (4)
#define BMA2x2_ORIENT_STAT_LEN             (3)
#define BMA2x2_ORIENT_STAT_MSK             (0x70)
#define BMA2x2_ORIENT_STAT_REG             BMA2x2_STAT_ORIENT_HIGH_ADDR
/*********************************************/
/**\name INTERRUPT STATUS FLAT */
/*********************************************/
#define BMA2x2_FLAT_STAT_POS               (7)
#define BMA2x2_FLAT_STAT_LEN               (1)
#define BMA2x2_FLAT_STAT_MSK               (0x80)
#define BMA2x2_FLAT_STAT_REG               BMA2x2_STAT_ORIENT_HIGH_ADDR

/*********************************************/
/**\name INTERRUPT STATUS OF FIFO FRAME COUNT */
/*********************************************/
#define BMA2x2_FIFO_FRAME_COUNT_STAT_POS             (0)
#define BMA2x2_FIFO_FRAME_COUNT_STAT_LEN             (7)
#define BMA2x2_FIFO_FRAME_COUNT_STAT_MSK             (0x7F)
#define BMA2x2_FIFO_FRAME_COUNT_STAT_REG             BMA2x2_STAT_FIFO_ADDR
/*********************************************/
/**\name INTERRUPT STATUS OF FIFO OVERRUN */
/*********************************************/
#define BMA2x2_FIFO_OVERRUN_STAT_POS             (7)
#define BMA2x2_FIFO_OVERRUN_STAT_LEN             (1)
#define BMA2x2_FIFO_OVERRUN_STAT_MSK             (0x80)
#define BMA2x2_FIFO_OVERRUN_STAT_REG             BMA2x2_STAT_FIFO_ADDR
/****************************/
/**\name RANGE */
/****************************/
#define BMA2x2_RANGE_SELECT_POS             (0)
#define BMA2x2_RANGE_SELECT_LEN             (4)
#define BMA2x2_RANGE_SELECT_MSK             (0x0F)
#define BMA2x2_RANGE_SELECT_REG             BMA2x2_RANGE_SELECT_ADDR
/****************************/
/**\name BANDWIDTH */
/****************************/
#define BMA2x2_BW_POS             (0)
#define BMA2x2_BW_LEN             (5)
#define BMA2x2_BW_MSK             (0x1F)
#define BMA2x2_BW_REG             BMA2x2_BW_SELECT_ADDR
/****************************/
/**\name SLEEP DURATION */
/****************************/
#define BMA2x2_SLEEP_DURN_POS             (1)
#define BMA2x2_SLEEP_DURN_LEN             (4)
#define BMA2x2_SLEEP_DURN_MSK             (0x1E)
#define BMA2x2_SLEEP_DURN_REG             BMA2x2_MODE_CTRL_ADDR
/****************************/
/**\name POWER MODEPOWER MODE */
/****************************/
#define BMA2x2_MODE_CTRL_POS             (5)
#define BMA2x2_MODE_CTRL_LEN             (3)
#define BMA2x2_MODE_CTRL_MSK             (0xE0)
#define BMA2x2_MODE_CTRL_REG             BMA2x2_MODE_CTRL_ADDR
/****************************/
/**\name SLEEP TIMER */
/****************************/
#define BMA2x2_SLEEP_TIMER_POS          (5)
#define BMA2x2_SLEEP_TIMER_LEN          (1)
#define BMA2x2_SLEEP_TIMER_MSK          (0x20)
#define BMA2x2_SLEEP_TIMER_REG          BMA2x2_LOW_NOISE_CTRL_ADDR
/****************************/
/**\name LOWPOWER MODE */
/****************************/
#define BMA2x2_LOW_POWER_MODE_POS          (6)
#define BMA2x2_LOW_POWER_MODE_LEN          (1)
#define BMA2x2_LOW_POWER_MODE_MSK          (0x40)
#define BMA2x2_LOW_POWER_MODE_REG          BMA2x2_LOW_NOISE_CTRL_ADDR
/*******************************************/
/**\name DISABLE MSB SHADOWING PROCEDURE  */
/*******************************************/
#define BMA2x2_DIS_SHADOW_PROC_POS       (6)
#define BMA2x2_DIS_SHADOW_PROC_LEN       (1)
#define BMA2x2_DIS_SHADOW_PROC_MSK       (0x40)
#define BMA2x2_DIS_SHADOW_PROC_REG       BMA2x2_DATA_CTRL_ADDR
/***************************************************/
/**\name FILTERED OR UNFILTERED ACCELERATION DATA   */
/***************************************************/
#define BMA2x2_ENABLE_DATA_HIGH_BW_POS         (7)
#define BMA2x2_ENABLE_DATA_HIGH_BW_LEN         (1)
#define BMA2x2_ENABLE_DATA_HIGH_BW_MSK         (0x80)
#define BMA2x2_ENABLE_DATA_HIGH_BW_REG         BMA2x2_DATA_CTRL_ADDR
/***************************************************/
/**\name SOFT RESET VALUE   */
/***************************************************/
#define BMA2x2_ENABLE_SOFT_RESET_VALUE        (0xB6)
/**********************************************/
/**\name INTERRUPT ENABLE OF SLOPE-XYZ   */
/**********************************************/
#define BMA2x2_ENABLE_SLOPE_X_INTR_POS         (0)
#define BMA2x2_ENABLE_SLOPE_X_INTR_LEN         (1)
#define BMA2x2_ENABLE_SLOPE_X_INTR_MSK         (0x01)
#define BMA2x2_ENABLE_SLOPE_X_INTR_REG         BMA2x2_INTR_ENABLE1_ADDR

#define BMA2x2_ENABLE_SLOPE_Y_INTR_POS         (1)
#define BMA2x2_ENABLE_SLOPE_Y_INTR_LEN         (1)
#define BMA2x2_ENABLE_SLOPE_Y_INTR_MSK         (0x02)
#define BMA2x2_ENABLE_SLOPE_Y_INTR_REG         BMA2x2_INTR_ENABLE1_ADDR

#define BMA2x2_ENABLE_SLOPE_Z_INTR_POS         (2)
#define BMA2x2_ENABLE_SLOPE_Z_INTR_LEN         (1)
#define BMA2x2_ENABLE_SLOPE_Z_INTR_MSK         (0x04)
#define BMA2x2_ENABLE_SLOPE_Z_INTR_REG         BMA2x2_INTR_ENABLE1_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF DOUBLE TAP   */
/**********************************************/
#define BMA2x2_ENABLE_DOUBLE_TAP_INTR_POS      (4)
#define BMA2x2_ENABLE_DOUBLE_TAP_INTR_LEN      (1)
#define BMA2x2_ENABLE_DOUBLE_TAP_INTR_MSK      (0x10)
#define BMA2x2_ENABLE_DOUBLE_TAP_INTR_REG      BMA2x2_INTR_ENABLE1_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF SINGLE TAP   */
/**********************************************/
#define BMA2x2_ENABLE_SINGLE_TAP_INTR_POS      (5)
#define BMA2x2_ENABLE_SINGLE_TAP_INTR_LEN      (1)
#define BMA2x2_ENABLE_SINGLE_TAP_INTR_MSK      (0x20)
#define BMA2x2_ENABLE_SINGLE_TAP_INTR_REG      BMA2x2_INTR_ENABLE1_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF ORIENT  */
/**********************************************/
#define BMA2x2_ENABLE_ORIENT_INTR_POS          (6)
#define BMA2x2_ENABLE_ORIENT_INTR_LEN          (1)
#define BMA2x2_ENABLE_ORIENT_INTR_MSK          (0x40)
#define BMA2x2_ENABLE_ORIENT_INTR_REG          BMA2x2_INTR_ENABLE1_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF FLAT  */
/**********************************************/
#define BMA2x2_ENABLE_FLAT_INTR_POS            (7)
#define BMA2x2_ENABLE_FLAT_INTR_LEN            (1)
#define BMA2x2_ENABLE_FLAT_INTR_MSK            (0x80)
#define BMA2x2_ENABLE_FLAT_INTR_REG            BMA2x2_INTR_ENABLE1_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF HIGH_G-XYZ   */
/**********************************************/
#define BMA2x2_ENABLE_HIGH_G_X_INTR_POS         (0)
#define BMA2x2_ENABLE_HIGH_G_X_INTR_LEN         (1)
#define BMA2x2_ENABLE_HIGH_G_X_INTR_MSK         (0x01)
#define BMA2x2_ENABLE_HIGH_G_X_INTR_REG         BMA2x2_INTR_ENABLE2_ADDR

#define BMA2x2_ENABLE_HIGH_G_Y_INTR_POS         (1)
#define BMA2x2_ENABLE_HIGH_G_Y_INTR_LEN         (1)
#define BMA2x2_ENABLE_HIGH_G_Y_INTR_MSK         (0x02)
#define BMA2x2_ENABLE_HIGH_G_Y_INTR_REG         BMA2x2_INTR_ENABLE2_ADDR

#define BMA2x2_ENABLE_HIGH_G_Z_INTR_POS         (2)
#define BMA2x2_ENABLE_HIGH_G_Z_INTR_LEN         (1)
#define BMA2x2_ENABLE_HIGH_G_Z_INTR_MSK         (0x04)
#define BMA2x2_ENABLE_HIGH_G_Z_INTR_REG         BMA2x2_INTR_ENABLE2_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF LOW_G  */
/**********************************************/
#define BMA2x2_ENABLE_LOW_G_INTR_POS            (3)
#define BMA2x2_ENABLE_LOW_G_INTR_LEN            (1)
#define BMA2x2_ENABLE_LOW_G_INTR_MSK            (0x08)
#define BMA2x2_ENABLE_LOW_G_INTR_REG            BMA2x2_INTR_ENABLE2_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF DATA   */
/**********************************************/
#define BMA2x2_ENABLE_NEW_DATA_INTR_POS        (4)
#define BMA2x2_ENABLE_NEW_DATA_INTR_LEN        (1)
#define BMA2x2_ENABLE_NEW_DATA_INTR_MSK        (0x10)
#define BMA2x2_ENABLE_NEW_DATA_INTR_REG        BMA2x2_INTR_ENABLE2_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF FIFO FULL   */
/**********************************************/
#define BMA2x2_INTR_FIFO_FULL_ENABLE_INTR_POS        (5)
#define BMA2x2_INTR_FIFO_FULL_ENABLE_INTR_LEN        (1)
#define BMA2x2_INTR_FIFO_FULL_ENABLE_INTR_MSK        (0x20)
#define BMA2x2_INTR_FIFO_FULL_ENABLE_INTR_REG        BMA2x2_INTR_ENABLE2_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF FIFO WATER MARK   */
/**********************************************/
#define BMA2x2_INTR_FIFO_WM_ENABLE_INTR_POS        (6)
#define BMA2x2_INTR_FIFO_WM_ENABLE_INTR_LEN        (1)
#define BMA2x2_INTR_FIFO_WM_ENABLE_INTR_MSK        (0x40)
#define BMA2x2_INTR_FIFO_WM_ENABLE_INTR_REG        BMA2x2_INTR_ENABLE2_ADDR
/************************************************/
/**\name INTERRUPT ENABLE OF SLOW NO MOTION-XYZ */
/*************************************************/
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_X_INTR_POS        (0)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_X_INTR_LEN        (1)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_X_INTR_MSK        (0x01)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_X_INTR_REG        \
BMA2x2_INTR_SLOW_NO_MOTION_ADDR

#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Y_INTR_POS        (1)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Y_INTR_LEN        (1)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Y_INTR_MSK        (0x02)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Y_INTR_REG        \
BMA2x2_INTR_SLOW_NO_MOTION_ADDR

#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Z_INTR_POS        (2)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Z_INTR_LEN        (1)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Z_INTR_MSK        (0x04)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Z_INTR_REG        \
BMA2x2_INTR_SLOW_NO_MOTION_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF SLOW NO MOTION SELECT */
/**********************************************/
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_SELECT_INTR_POS        (3)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_SELECT_INTR_LEN        (1)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_SELECT_INTR_MSK        (0x08)
#define BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_SELECT_INTR_REG        \
BMA2x2_INTR_SLOW_NO_MOTION_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD LOW_G */
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_LOW_G_POS        (0)
#define BMA2x2_ENABLE_INTR1_PAD_LOW_G_LEN        (1)
#define BMA2x2_ENABLE_INTR1_PAD_LOW_G_MSK        (0x01)
#define BMA2x2_ENABLE_INTR1_PAD_LOW_G_REG        BMA2x2_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD HIGH_G */
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_HIGH_G_POS       (1)
#define BMA2x2_ENABLE_INTR1_PAD_HIGH_G_LEN       (1)
#define BMA2x2_ENABLE_INTR1_PAD_HIGH_G_MSK       (0x02)
#define BMA2x2_ENABLE_INTR1_PAD_HIGH_G_REG       BMA2x2_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD SLOPE */
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_SLOPE_POS       (2)
#define BMA2x2_ENABLE_INTR1_PAD_SLOPE_LEN       (1)
#define BMA2x2_ENABLE_INTR1_PAD_SLOPE_MSK       (0x04)
#define BMA2x2_ENABLE_INTR1_PAD_SLOPE_REG       BMA2x2_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF SLOW NO MOTION  */
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_SLOW_NO_MOTION_POS        (3)
#define BMA2x2_ENABLE_INTR1_PAD_SLOW_NO_MOTION_LEN        (1)
#define BMA2x2_ENABLE_INTR1_PAD_SLOW_NO_MOTION_MSK        (0x08)
#define BMA2x2_ENABLE_INTR1_PAD_SLOW_NO_MOTION_REG        \
BMA2x2_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD DOUBLE_TAP */
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_DOUBLE_TAP_POS      (4)
#define BMA2x2_ENABLE_INTR1_PAD_DOUBLE_TAP_LEN      (1)
#define BMA2x2_ENABLE_INTR1_PAD_DOUBLE_TAP_MSK      (0x10)
#define BMA2x2_ENABLE_INTR1_PAD_DOUBLE_TAP_REG      BMA2x2_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD SINGLE_TAP */
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_SINGLE_TAP_POS     (5)
#define BMA2x2_ENABLE_INTR1_PAD_SINGLE_TAP_LEN     (1)
#define BMA2x2_ENABLE_INTR1_PAD_SINGLE_TAP_MSK     (0x20)
#define BMA2x2_ENABLE_INTR1_PAD_SINGLE_TAP_REG     BMA2x2_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD ORIENT*/
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_ORIENT_POS      (6)
#define BMA2x2_ENABLE_INTR1_PAD_ORIENT_LEN      (1)
#define BMA2x2_ENABLE_INTR1_PAD_ORIENT_MSK      (0x40)
#define BMA2x2_ENABLE_INTR1_PAD_ORIENT_REG      BMA2x2_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD FLAT */
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_FLAT_POS        (7)
#define BMA2x2_ENABLE_INTR1_PAD_FLAT_LEN        (1)
#define BMA2x2_ENABLE_INTR1_PAD_FLAT_MSK        (0x80)
#define BMA2x2_ENABLE_INTR1_PAD_FLAT_REG        BMA2x2_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD LOW_G */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_LOW_G_POS        (0)
#define BMA2x2_ENABLE_INTR2_PAD_LOW_G_LEN        (1)
#define BMA2x2_ENABLE_INTR2_PAD_LOW_G_MSK        (0x01)
#define BMA2x2_ENABLE_INTR2_PAD_LOW_G_REG        BMA2x2_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD HIGH_G */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_HIGH_G_POS       (1)
#define BMA2x2_ENABLE_INTR2_PAD_HIGH_G_LEN       (1)
#define BMA2x2_ENABLE_INTR2_PAD_HIGH_G_MSK       (0x02)
#define BMA2x2_ENABLE_INTR2_PAD_HIGH_G_REG       BMA2x2_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD SLOPE */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_SLOPE_POS       (2)
#define BMA2x2_ENABLE_INTR2_PAD_SLOPE_LEN       (1)
#define BMA2x2_ENABLE_INTR2_PAD_SLOPE_MSK       (0x04)
#define BMA2x2_ENABLE_INTR2_PAD_SLOPE_REG       BMA2x2_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD SLOW NO MOTION */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_SLOW_NO_MOTION_POS        (3)
#define BMA2x2_ENABLE_INTR2_PAD_SLOW_NO_MOTION_LEN        (1)
#define BMA2x2_ENABLE_INTR2_PAD_SLOW_NO_MOTION_MSK        (0x08)
#define BMA2x2_ENABLE_INTR2_PAD_SLOW_NO_MOTION_REG        \
BMA2x2_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD DOUBLE_TAP */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_DOUBLE_TAP_POS      (4)
#define BMA2x2_ENABLE_INTR2_PAD_DOUBLE_TAP_LEN      (1)
#define BMA2x2_ENABLE_INTR2_PAD_DOUBLE_TAP_MSK      (0x10)
#define BMA2x2_ENABLE_INTR2_PAD_DOUBLE_TAP_REG      BMA2x2_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD SINGLE_TAP */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_SINGLE_TAP_POS     (5)
#define BMA2x2_ENABLE_INTR2_PAD_SINGLE_TAP_LEN     (1)
#define BMA2x2_ENABLE_INTR2_PAD_SINGLE_TAP_MSK     (0x20)
#define BMA2x2_ENABLE_INTR2_PAD_SINGLE_TAP_REG     BMA2x2_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD ORIENT */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_ORIENT_POS      (6)
#define BMA2x2_ENABLE_INTR2_PAD_ORIENT_LEN      (1)
#define BMA2x2_ENABLE_INTR2_PAD_ORIENT_MSK      (0x40)
#define BMA2x2_ENABLE_INTR2_PAD_ORIENT_REG      BMA2x2_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD FLAT */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_FLAT_POS        (7)
#define BMA2x2_ENABLE_INTR2_PAD_FLAT_LEN        (1)
#define BMA2x2_ENABLE_INTR2_PAD_FLAT_MSK        (0x80)
#define BMA2x2_ENABLE_INTR2_PAD_FLAT_REG        BMA2x2_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD DATA */
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_NEWDATA_POS     (0)
#define BMA2x2_ENABLE_INTR1_PAD_NEWDATA_LEN     (1)
#define BMA2x2_ENABLE_INTR1_PAD_NEWDATA_MSK     (0x01)
#define BMA2x2_ENABLE_INTR1_PAD_NEWDATA_REG     BMA2x2_INTR_DATA_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF FIFO WATER MARK */
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_FIFO_WM_POS     (1)
#define BMA2x2_ENABLE_INTR1_PAD_FIFO_WM_LEN     (1)
#define BMA2x2_ENABLE_INTR1_PAD_FIFO_WM_MSK     (0x02)
#define BMA2x2_ENABLE_INTR1_PAD_FIFO_WM_REG     BMA2x2_INTR_DATA_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF FIFO FULL*/
/**********************************************/
#define BMA2x2_ENABLE_INTR1_PAD_FIFO_FULL_POS     (2)
#define BMA2x2_ENABLE_INTR1_PAD_FIFO_FULL_LEN     (1)
#define BMA2x2_ENABLE_INTR1_PAD_FIFO_FULL_MSK     (0x04)
#define BMA2x2_ENABLE_INTR1_PAD_FIFO_FULL_REG     BMA2x2_INTR_DATA_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD FIFO FULL */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_FIFO_FULL_POS     (5)
#define BMA2x2_ENABLE_INTR2_PAD_FIFO_FULL_LEN     (1)
#define BMA2x2_ENABLE_INTR2_PAD_FIFO_FULL_MSK     (0x20)
#define BMA2x2_ENABLE_INTR2_PAD_FIFO_FULL_REG     BMA2x2_INTR_DATA_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD FIFO WATERMARK*/
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_FIFO_WM_POS     (6)
#define BMA2x2_ENABLE_INTR2_PAD_FIFO_WM_LEN     (1)
#define BMA2x2_ENABLE_INTR2_PAD_FIFO_WM_MSK     (0x40)
#define BMA2x2_ENABLE_INTR2_PAD_FIFO_WM_REG     BMA2x2_INTR_DATA_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD DATA */
/**********************************************/
#define BMA2x2_ENABLE_INTR2_PAD_NEWDATA_POS     (7)
#define BMA2x2_ENABLE_INTR2_PAD_NEWDATA_LEN     (1)
#define BMA2x2_ENABLE_INTR2_PAD_NEWDATA_MSK     (0x80)
#define BMA2x2_ENABLE_INTR2_PAD_NEWDATA_REG     BMA2x2_INTR_DATA_SELECT_ADDR
/**********************************************/
/**\name  INTERRUPT SOURCE SELECTION OF LOW_G*/
/**********************************************/
#define BMA2x2_UNFILT_INTR_SOURCE_LOW_G_POS        (0)
#define BMA2x2_UNFILT_INTR_SOURCE_LOW_G_LEN        (1)
#define BMA2x2_UNFILT_INTR_SOURCE_LOW_G_MSK        (0x01)
#define BMA2x2_UNFILT_INTR_SOURCE_LOW_G_REG        BMA2x2_INTR_SOURCE_ADDR
/**********************************************/
/**\name  INTERRUPT SOURCE SELECTION OF HIGH_G*/
/**********************************************/
#define BMA2x2_UNFILT_INTR_SOURCE_HIGH_G_POS       (1)
#define BMA2x2_UNFILT_INTR_SOURCE_HIGH_G_LEN       (1)
#define BMA2x2_UNFILT_INTR_SOURCE_HIGH_G_MSK       (0x02)
#define BMA2x2_UNFILT_INTR_SOURCE_HIGH_G_REG       BMA2x2_INTR_SOURCE_ADDR
/**********************************************/
/**\name  INTERRUPT SOURCE SELECTION OF SLOPE*/
/**********************************************/
#define BMA2x2_UNFILT_INTR_SOURCE_SLOPE_POS       (2)
#define BMA2x2_UNFILT_INTR_SOURCE_SLOPE_LEN       (1)
#define BMA2x2_UNFILT_INTR_SOURCE_SLOPE_MSK       (0x04)
#define BMA2x2_UNFILT_INTR_SOURCE_SLOPE_REG       BMA2x2_INTR_SOURCE_ADDR
/**********************************************/
/**\name  INTERRUPT SOURCE SELECTION OF SLOW NO MOTION*/
/**********************************************/
#define BMA2x2_UNFILT_INTR_SOURCE_SLOW_NO_MOTION_POS        (3)
#define BMA2x2_UNFILT_INTR_SOURCE_SLOW_NO_MOTION_LEN        (1)
#define BMA2x2_UNFILT_INTR_SOURCE_SLOW_NO_MOTION_MSK        (0x08)
#define BMA2x2_UNFILT_INTR_SOURCE_SLOW_NO_MOTION_REG        \
BMA2x2_INTR_SOURCE_ADDR
/**********************************************/
/**\name  INTERRUPT SOURCE SELECTION OF TAP*/
/**********************************************/
#define BMA2x2_UNFILT_INTR_SOURCE_TAP_POS         (4)
#define BMA2x2_UNFILT_INTR_SOURCE_TAP_LEN         (1)
#define BMA2x2_UNFILT_INTR_SOURCE_TAP_MSK         (0x10)
#define BMA2x2_UNFILT_INTR_SOURCE_TAP_REG         BMA2x2_INTR_SOURCE_ADDR
/**********************************************/
/**\name  INTERRUPT SOURCE SELECTION OF DATA*/
/**********************************************/
#define BMA2x2_UNFILT_INTR_SOURCE_DATA_POS        (5)
#define BMA2x2_UNFILT_INTR_SOURCE_DATA_LEN        (1)
#define BMA2x2_UNFILT_INTR_SOURCE_DATA_MSK        (0x20)
#define BMA2x2_UNFILT_INTR_SOURCE_DATA_REG        BMA2x2_INTR_SOURCE_ADDR
/****************************************************/
/**\name  INTERRUPT PAD ACTIVE LEVEL AND OUTPUT TYPE*/
/****************************************************/
#define BMA2x2_INTR1_PAD_ACTIVE_LEVEL_POS       (0)
#define BMA2x2_INTR1_PAD_ACTIVE_LEVEL_LEN       (1)
#define BMA2x2_INTR1_PAD_ACTIVE_LEVEL_MSK       (0x01)
#define BMA2x2_INTR1_PAD_ACTIVE_LEVEL_REG       BMA2x2_INTR_SET_ADDR

#define BMA2x2_INTR2_PAD_ACTIVE_LEVEL_POS       (2)
#define BMA2x2_INTR2_PAD_ACTIVE_LEVEL_LEN       (1)
#define BMA2x2_INTR2_PAD_ACTIVE_LEVEL_MSK       (0x04)
#define BMA2x2_INTR2_PAD_ACTIVE_LEVEL_REG       BMA2x2_INTR_SET_ADDR

#define BMA2x2_INTR1_PAD_OUTPUT_TYPE_POS        (1)
#define BMA2x2_INTR1_PAD_OUTPUT_TYPE_LEN        (1)
#define BMA2x2_INTR1_PAD_OUTPUT_TYPE_MSK        (0x02)
#define BMA2x2_INTR1_PAD_OUTPUT_TYPE_REG        BMA2x2_INTR_SET_ADDR

#define BMA2x2_INTR2_PAD_OUTPUT_TYPE_POS        (3)
#define BMA2x2_INTR2_PAD_OUTPUT_TYPE_LEN        (1)
#define BMA2x2_INTR2_PAD_OUTPUT_TYPE_MSK        (0x08)
#define BMA2x2_INTR2_PAD_OUTPUT_TYPE_REG        BMA2x2_INTR_SET_ADDR
/****************************************************/
/**\name   LATCH INTERRUPT */
/****************************************************/
#define BMA2x2_LATCH_INTR_POS                (0)
#define BMA2x2_LATCH_INTR_LEN                (4)
#define BMA2x2_LATCH_INTR_MSK                (0x0F)
#define BMA2x2_LATCH_INTR_REG                BMA2x2_INTR_CTRL_ADDR
/****************************************************/
/**\name   RESET LATCH INTERRUPT */
/****************************************************/
#define BMA2x2_RESET_INTR_POS           (7)
#define BMA2x2_RESET_INTR_LEN           (1)
#define BMA2x2_RESET_INTR_MSK           (0x80)
#define BMA2x2_RESET_INTR_REG           BMA2x2_INTR_CTRL_ADDR
/****************************************************/
/**\name   LOW_G HYSTERESIS */
/****************************************************/
#define BMA2x2_LOW_G_HYST_POS                   (0)
#define BMA2x2_LOW_G_HYST_LEN                   (2)
#define BMA2x2_LOW_G_HYST_MSK                   (0x03)
#define BMA2x2_LOW_G_HYST_REG                   BMA2x2_LOW_HIGH_HYST_ADDR
/****************************************************/
/**\name   LOW_G MODE */
/****************************************************/
#define BMA2x2_LOW_G_INTR_MODE_POS               (2)
#define BMA2x2_LOW_G_INTR_MODE_LEN               (1)
#define BMA2x2_LOW_G_INTR_MODE_MSK               (0x04)
#define BMA2x2_LOW_G_INTR_MODE_REG               BMA2x2_LOW_HIGH_HYST_ADDR

/****************************************************/
/**\name   HIGH_G HYSTERESIS */
/****************************************************/
#define BMA2x2_HIGH_G_HYST_POS                  (6)
#define BMA2x2_HIGH_G_HYST_LEN                  (2)
#define BMA2x2_HIGH_G_HYST_MSK                  (0xC0)
#define BMA2x2_HIGH_G_HYST_REG                  BMA2x2_LOW_HIGH_HYST_ADDR
/****************************************************/
/**\name   SLOPE DURATION */
/****************************************************/
#define BMA2x2_SLOPE_DURN_POS                    (0)
#define BMA2x2_SLOPE_DURN_LEN                    (2)
#define BMA2x2_SLOPE_DURN_MSK                    (0x03)
#define BMA2x2_SLOPE_DURN_REG                    BMA2x2_SLOPE_DURN_ADDR
/****************************************************/
/**\name   SLOW NO MOTION DURATION */
/****************************************************/
#define BMA2x2_SLOW_NO_MOTION_DURN_POS                    (2)
#define BMA2x2_SLOW_NO_MOTION_DURN_LEN                    (6)
#define BMA2x2_SLOW_NO_MOTION_DURN_MSK                    (0xFC)
#define BMA2x2_SLOW_NO_MOTION_DURN_REG                    BMA2x2_SLOPE_DURN_ADDR

/****************************************************/
/**\name   TAP DURATION */
/****************************************************/
#define BMA2x2_TAP_DURN_POS                    (0)
#define BMA2x2_TAP_DURN_LEN                    (3)
#define BMA2x2_TAP_DURN_MSK                    (0x07)
#define BMA2x2_TAP_DURN_REG                    BMA2x2_TAP_PARAM_ADDR

/****************************************************/
/**\name   TAP SHOCK DURATION */
/****************************************************/
#define BMA2x2_TAP_SHOCK_DURN_POS             (6)
#define BMA2x2_TAP_SHOCK_DURN_LEN             (1)
#define BMA2x2_TAP_SHOCK_DURN_MSK             (0x40)
#define BMA2x2_TAP_SHOCK_DURN_REG             BMA2x2_TAP_PARAM_ADDR

/* This advance tap interrupt only uses for the chip id 0xFB */
#define BMA2x2_ADV_TAP_INTR_POS                (5)
#define BMA2x2_ADV_TAP_INTR_LEN                (1)
#define BMA2x2_ADV_TAP_INTR_MSK                (0x20)
#define BMA2x2_ADV_TAP_INTR_REG                BMA2x2_TAP_PARAM_ADDR
/****************************************************/
/**\name   TAP QUIET DURATION */
/****************************************************/
#define BMA2x2_TAP_QUIET_DURN_POS             (7)
#define BMA2x2_TAP_QUIET_DURN_LEN             (1)
#define BMA2x2_TAP_QUIET_DURN_MSK             (0x80)
#define BMA2x2_TAP_QUIET_DURN_REG             BMA2x2_TAP_PARAM_ADDR
/****************************************************/
/**\name   TAP THRESHOLD */
/****************************************************/
#define BMA2x2_TAP_THRES_POS                  (0)
#define BMA2x2_TAP_THRES_LEN                  (5)
#define BMA2x2_TAP_THRES_MSK                  (0x1F)
#define BMA2x2_TAP_THRES_REG                  BMA2x2_TAP_THRES_ADDR
/****************************************************/
/**\name   TAP SAMPLES */
/****************************************************/
#define BMA2x2_TAP_SAMPLES_POS                (6)
#define BMA2x2_TAP_SAMPLES_LEN                (2)
#define BMA2x2_TAP_SAMPLES_MSK                (0xC0)
#define BMA2x2_TAP_SAMPLES_REG                BMA2x2_TAP_THRES_ADDR
/****************************************************/
/**\name  ORIENT MODE */
/****************************************************/
#define BMA2x2_ORIENT_MODE_POS                  (0)
#define BMA2x2_ORIENT_MODE_LEN                  (2)
#define BMA2x2_ORIENT_MODE_MSK                  (0x03)
#define BMA2x2_ORIENT_MODE_REG                  BMA2x2_ORIENT_PARAM_ADDR
/****************************************************/
/**\name   ORIENT BLOCKING */
/****************************************************/
#define BMA2x2_ORIENT_BLOCK_POS                 (2)
#define BMA2x2_ORIENT_BLOCK_LEN                 (2)
#define BMA2x2_ORIENT_BLOCK_MSK                 (0x0C)
#define BMA2x2_ORIENT_BLOCK_REG                 BMA2x2_ORIENT_PARAM_ADDR
/****************************************************/
/**\name   ORIENT HYSTERESIS */
/****************************************************/
#define BMA2x2_ORIENT_HYST_POS                  (4)
#define BMA2x2_ORIENT_HYST_LEN                  (3)
#define BMA2x2_ORIENT_HYST_MSK                  (0x70)
#define BMA2x2_ORIENT_HYST_REG                  BMA2x2_ORIENT_PARAM_ADDR
/****************************************************/
/**\name   ORIENT AXIS  */
/****************************************************/
#define BMA2x2_ORIENT_UD_ENABLE_POS                  (6)
#define BMA2x2_ORIENT_UD_ENABLE_LEN                  (1)
#define BMA2x2_ORIENT_UD_ENABLE_MSK                  (0x40)
#define BMA2x2_ORIENT_UD_ENABLE_REG                  BMA2x2_THETA_BLOCK_ADDR

/****************************************************/
/**\name   THETA BLOCKING */
/****************************************************/
#define BMA2x2_THETA_BLOCK_POS                  (0)
#define BMA2x2_THETA_BLOCK_LEN                  (6)
#define BMA2x2_THETA_BLOCK_MSK                  (0x3F)
#define BMA2x2_THETA_BLOCK_REG                  BMA2x2_THETA_BLOCK_ADDR
/****************************************************/
/**\name   THETA FLAT */
/****************************************************/
#define BMA2x2_THETA_FLAT_POS                  (0)
#define BMA2x2_THETA_FLAT_LEN                  (6)
#define BMA2x2_THETA_FLAT_MSK                  (0x3F)
#define BMA2x2_THETA_FLAT_REG                  BMA2x2_THETA_FLAT_ADDR
/****************************************************/
/**\name   THETA HOLD TIME */
/****************************************************/
#define BMA2x2_FLAT_HOLD_TIME_POS              (4)
#define BMA2x2_FLAT_HOLD_TIME_LEN              (2)
#define BMA2x2_FLAT_HOLD_TIME_MSK              (0x30)
#define BMA2x2_FLAT_HOLD_TIME_REG              BMA2x2_FLAT_HOLD_TIME_ADDR
/****************************************************/
/**\name   FLAT HYSTERESIS */
/****************************************************/
#define BMA2x2_FLAT_HYST_POS                   (0)
#define BMA2x2_FLAT_HYST_LEN                   (3)
#define BMA2x2_FLAT_HYST_MSK                   (0x07)
#define BMA2x2_FLAT_HYST_REG                   BMA2x2_FLAT_HOLD_TIME_ADDR
/****************************************************/
/**\name   FIFO WATER MARK LEVEL TRIGGER RETAIN  */
/****************************************************/
#define BMA2x2_FIFO_WML_TRIG_RETAIN_POS                   (0)
#define BMA2x2_FIFO_WML_TRIG_RETAIN_LEN                   (6)
#define BMA2x2_FIFO_WML_TRIG_RETAIN_MSK                   (0x3F)
#define BMA2x2_FIFO_WML_TRIG_RETAIN_REG                   BMA2x2_FIFO_WML_TRIG
/****************************************************/
/**\name   ACTIVATE SELF TEST  */
/****************************************************/
#define BMA2x2_ENABLE_SELFTEST_POS                (0)
#define BMA2x2_ENABLE_SELFTEST_LEN                (2)
#define BMA2x2_ENABLE_SELFTEST_MSK                (0x03)
#define BMA2x2_ENABLE_SELFTEST_REG                BMA2x2_SELFTEST_ADDR
/****************************************************/
/**\name   SELF TEST -- NEGATIVE   */
/****************************************************/
#define BMA2x2_NEG_SELFTEST_POS               (2)
#define BMA2x2_NEG_SELFTEST_LEN               (1)
#define BMA2x2_NEG_SELFTEST_MSK               (0x04)
#define BMA2x2_NEG_SELFTEST_REG               BMA2x2_SELFTEST_ADDR
/****************************************************/
/**\name   EEPROM CONTROL   */
/****************************************************/
#define BMA2x2_UNLOCK_EE_PROG_MODE_POS     (0)
#define BMA2x2_UNLOCK_EE_PROG_MODE_LEN     (1)
#define BMA2x2_UNLOCK_EE_PROG_MODE_MSK     (0x01)
#define BMA2x2_UNLOCK_EE_PROG_MODE_REG     BMA2x2_EEPROM_CTRL_ADDR
/**********************************************************************/
/**\name  SETTING THIS BIT STARTS WRITING SETTING REGISTERS TO EEPROM */
/*********************************************************************/
#define BMA2x2_START_EE_PROG_TRIG_POS      (1)
#define BMA2x2_START_EE_PROG_TRIG_LEN      (1)
#define BMA2x2_START_EE_PROG_TRIG_MSK      (0x02)
#define BMA2x2_START_EE_PROG_TRIG_REG      BMA2x2_EEPROM_CTRL_ADDR
/****************************************************/
/**\name   STATUS OF WRITING TO EEPROM   */
/****************************************************/
#define BMA2x2_EE_PROG_READY_POS          (2)
#define BMA2x2_EE_PROG_READY_LEN          (1)
#define BMA2x2_EE_PROG_READY_MSK          (0x04)
#define BMA2x2_EE_PROG_READY_REG          BMA2x2_EEPROM_CTRL_ADDR
/****************************************************/
/**\name   UPDATE IMAGE REGISTERS WRITING TO EEPROM   */
/****************************************************/
#define BMA2x2_UPDATE_IMAGE_POS                (3)
#define BMA2x2_UPDATE_IMAGE_LEN                (1)
#define BMA2x2_UPDATE_IMAGE_MSK                (0x08)
#define BMA2x2_UPDATE_IMAGE_REG                BMA2x2_EEPROM_CTRL_ADDR

#define BMA2x2_EE_REMAIN_POS                (4)
#define BMA2x2_EE_REMAIN_LEN                (4)
#define BMA2x2_EE_REMAIN_MSK                (0xF0)
#define BMA2x2_EE_REMAIN_REG                BMA2x2_EEPROM_CTRL_ADDR
/****************************************************/
/**\name   SPI INTERFACE MODE SELECTION   */
/***************************************************/
#define BMA2x2_ENABLE_SPI_MODE_3_POS              (0)
#define BMA2x2_ENABLE_SPI_MODE_3_LEN              (1)
#define BMA2x2_ENABLE_SPI_MODE_3_MSK              (0x01)
#define BMA2x2_ENABLE_SPI_MODE_3_REG              BMA2x2_SERIAL_CTRL_ADDR
/****************************************************/
/**\name   I2C WATCHDOG PERIOD SELECTION   */
/***************************************************/
#define BMA2x2_I2C_WDT_PERIOD_POS        (1)
#define BMA2x2_I2C_WDT_PERIOD_LEN        (1)
#define BMA2x2_I2C_WDT_PERIOD_MSK        (0x02)
#define BMA2x2_I2C_WDT_PERIOD_REG        BMA2x2_SERIAL_CTRL_ADDR
/****************************************************/
/**\name   I2C WATCHDOG ENABLE   */
/***************************************************/
#define BMA2x2_ENABLE_I2C_WDT_POS            (2)
#define BMA2x2_ENABLE_I2C_WDT_LEN            (1)
#define BMA2x2_ENABLE_I2C_WDT_MSK            (0x04)
#define BMA2x2_ENABLE_I2C_WDT_REG            BMA2x2_SERIAL_CTRL_ADDR
/****************************************************/
/**\name   SPI INTERFACE MODE SELECTIONE            */
/***************************************************/
#define BMA2x2_UNLOCK_EE_WRITE_TRIM_POS        (4)
#define BMA2x2_UNLOCK_EE_WRITE_TRIM_LEN        (4)
#define BMA2x2_UNLOCK_EE_WRITE_TRIM_MSK        (0xF0)
#define BMA2x2_UNLOCK_EE_WRITE_TRIM_REG        BMA2x2_CTRL_UNLOCK_REG
/******************************************************************/
/**\name   OFFSET  COMPENSATION/SLOW COMPENSATION FOR X,Y,Z AXIS */
/*****************************************************************/
#define BMA2x2_ENABLE_SLOW_COMP_X_POS              (0)
#define BMA2x2_ENABLE_SLOW_COMP_X_LEN              (1)
#define BMA2x2_ENABLE_SLOW_COMP_X_MSK              (0x01)
#define BMA2x2_ENABLE_SLOW_COMP_X_REG              BMA2x2_OFFSET_CTRL_ADDR

#define BMA2x2_ENABLE_SLOW_COMP_Y_POS              (1)
#define BMA2x2_ENABLE_SLOW_COMP_Y_LEN              (1)
#define BMA2x2_ENABLE_SLOW_COMP_Y_MSK              (0x02)
#define BMA2x2_ENABLE_SLOW_COMP_Y_REG              BMA2x2_OFFSET_CTRL_ADDR

#define BMA2x2_ENABLE_SLOW_COMP_Z_POS              (2)
#define BMA2x2_ENABLE_SLOW_COMP_Z_LEN              (1)
#define BMA2x2_ENABLE_SLOW_COMP_Z_MSK              (0x04)
#define BMA2x2_ENABLE_SLOW_COMP_Z_REG              BMA2x2_OFFSET_CTRL_ADDR
/****************************************************/
/**\name   FAST COMPENSATION READY FLAG            */
/***************************************************/
#define BMA2x2_FAST_CAL_RDY_STAT_POS             (4)
#define BMA2x2_FAST_CAL_RDY_STAT_LEN             (1)
#define BMA2x2_FAST_CAL_RDY_STAT_MSK             (0x10)
#define BMA2x2_FAST_CAL_RDY_STAT_REG             BMA2x2_OFFSET_CTRL_ADDR
/****************************************************/
/**\name   FAST COMPENSATION FOR X,Y,Z AXIS         */
/***************************************************/
#define BMA2x2_CAL_TRIGGER_POS                (5)
#define BMA2x2_CAL_TRIGGER_LEN                (2)
#define BMA2x2_CAL_TRIGGER_MSK                (0x60)
#define BMA2x2_CAL_TRIGGER_REG                BMA2x2_OFFSET_CTRL_ADDR
/****************************************************/
/**\name   RESET OFFSET REGISTERS         */
/***************************************************/
#define BMA2x2_RST_OFFSET_POS           (7)
#define BMA2x2_RST_OFFSET_LEN           (1)
#define BMA2x2_RST_OFFSET_MSK           (0x80)
#define BMA2x2_RST_OFFSET_REG           BMA2x2_OFFSET_CTRL_ADDR
/****************************************************/
/**\name   SLOW COMPENSATION  CUTOFF        */
/***************************************************/
#define BMA2x2_COMP_CUTOFF_POS                 (0)
#define BMA2x2_COMP_CUTOFF_LEN                 (1)
#define BMA2x2_COMP_CUTOFF_MSK                 (0x01)
#define BMA2x2_COMP_CUTOFF_REG                 BMA2x2_OFFSET_PARAMS_ADDR
/****************************************************/
/**\name    COMPENSATION TARGET       */
/***************************************************/
#define BMA2x2_COMP_TARGET_OFFSET_X_POS        (1)
#define BMA2x2_COMP_TARGET_OFFSET_X_LEN        (2)
#define BMA2x2_COMP_TARGET_OFFSET_X_MSK        (0x06)
#define BMA2x2_COMP_TARGET_OFFSET_X_REG        BMA2x2_OFFSET_PARAMS_ADDR

#define BMA2x2_COMP_TARGET_OFFSET_Y_POS        (3)
#define BMA2x2_COMP_TARGET_OFFSET_Y_LEN        (2)
#define BMA2x2_COMP_TARGET_OFFSET_Y_MSK        (0x18)
#define BMA2x2_COMP_TARGET_OFFSET_Y_REG        BMA2x2_OFFSET_PARAMS_ADDR

#define BMA2x2_COMP_TARGET_OFFSET_Z_POS        (5)
#define BMA2x2_COMP_TARGET_OFFSET_Z_LEN        (2)
#define BMA2x2_COMP_TARGET_OFFSET_Z_MSK        (0x60)
#define BMA2x2_COMP_TARGET_OFFSET_Z_REG        BMA2x2_OFFSET_PARAMS_ADDR
/****************************************************/
/**\name    FIFO DATA SELECT       */
/***************************************************/
#define BMA2x2_FIFO_DATA_SELECT_POS                 (0)
#define BMA2x2_FIFO_DATA_SELECT_LEN                 (2)
#define BMA2x2_FIFO_DATA_SELECT_MSK                 (0x03)
#define BMA2x2_FIFO_DATA_SELECT_REG                 BMA2x2_FIFO_MODE_ADDR
/****************************************************/
/**\name   FIFO MODE      */
/***************************************************/
#define BMA2x2_FIFO_MODE_POS                 (6)
#define BMA2x2_FIFO_MODE_LEN                 (2)
#define BMA2x2_FIFO_MODE_MSK                 (0xC0)
#define BMA2x2_FIFO_MODE_REG                 BMA2x2_FIFO_MODE_ADDR

#define BMA2x2_SENSOR_DATA_XYZ_X_LSB    (0)
#define BMA2x2_SENSOR_DATA_XYZ_X_MSB    (1)
#define BMA2x2_SENSOR_DATA_XYZ_Y_LSB    (2)
#define BMA2x2_SENSOR_DATA_XYZ_Y_MSB    (3)
#define BMA2x2_SENSOR_DATA_XYZ_Z_LSB    (4)
#define BMA2x2_SENSOR_DATA_XYZ_Z_MSB    (5)

#define BMA2x2_14_BIT_SHIFT     (0xFC)

/* Exported macro ------------------------------------------------------------*/
#define Bma_CtxDef Acc_CtxDef

#define BMA2x2_BW_500HZ             (0x0E)

/* Exported functions --------------------------------------------------------*/
int32_t Bma_GetID(Bma_CtxDef* ctx, uint8_t* id);

int32_t Bma_WriteReg(Bma_CtxDef* ctx, uint8_t reg_addr, 
                     uint8_t* reg_data, uint8_t cnt);

int32_t Bma_ReadReg(Bma_CtxDef* ctx, uint8_t reg_addr, 
                     uint8_t* reg_data, uint8_t cnt);

int32_t Bma_SoftReset(Bma_CtxDef* ctx);

#ifdef __cplusplus
}
#endif /*_cplusplus*/

#endif /* __BMA280_H */
