/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ramecc.c
  * @brief   This file provides code for the configuration
  *          of the RAMECC instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "ramecc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

RAMECC_HandleTypeDef hramecc_m1;
RAMECC_HandleTypeDef hramecc_m2;
RAMECC_HandleTypeDef hramecc_m3;

/* RAMECC init function */
void MX_RAMECC_Init(void)
{

  /* USER CODE BEGIN RAMECC_Init 0 */

  /* USER CODE END RAMECC_Init 0 */

  /* USER CODE BEGIN RAMECC_Init 1 */

  /* USER CODE END RAMECC_Init 1 */

  /** Initialize RAMECC M1 : ITCM-RAM
  */
  hramecc_m1.Instance = RAMECC_Monitor1;
  if (HAL_RAMECC_Init(&hramecc_m1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initialize RAMECC M2 : D0TCM-RAM
  */
  hramecc_m2.Instance = RAMECC_Monitor2;
  if (HAL_RAMECC_Init(&hramecc_m2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initialize RAMECC M3 : D1TCM-RAM
  */
  hramecc_m3.Instance = RAMECC_Monitor3;
  if (HAL_RAMECC_Init(&hramecc_m3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RAMECC_Init 2 */

  /* USER CODE END RAMECC_Init 2 */

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
