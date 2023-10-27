/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    i2c.h
  * @brief   This file contains all the function prototypes for
  *          the i2c.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern I2C_HandleTypeDef hi2c1;

extern I2C_HandleTypeDef hi2c2;

extern I2C_HandleTypeDef hi2c4;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_I2C1_Init(void);
void MX_I2C2_Init(void);
void MX_I2C4_Init(void);

/* USER CODE BEGIN Prototypes */

typedef int32_t (*readFunc)(uint16_t, uint16_t, uint16_t, uint8_t *, uint16_t);
typedef int32_t (*writeFunc)(uint16_t, uint16_t, uint16_t, uint8_t *, uint16_t);
typedef int32_t (*resetFunc)(void);

typedef struct {
	I2C_HandleTypeDef * I2C_Handle;
	uint8_t type;
	void * activateFunc;
	void * semaphore;
	readFunc read;
	writeFunc write;
	resetFunc reset;
} I2C_Bus;

extern I2C_Bus i2c_bus_1;
extern I2C_Bus i2c_bus_2;
extern I2C_Bus i2c_bus_2_A; //MUX0
extern I2C_Bus i2c_bus_2_B; //MUX1

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */

