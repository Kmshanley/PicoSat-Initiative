/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    octospi.c
  * @brief   This file provides code for the configuration
  *          of the OCTOSPI instances.
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
/* Includes ------------------------------------------------------------------*/
#include "octospi.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

OSPI_HandleTypeDef hospi1;

/* OCTOSPI1 init function */
void MX_OCTOSPI1_Init(void)
{

  /* USER CODE BEGIN OCTOSPI1_Init 0 */

  /* USER CODE END OCTOSPI1_Init 0 */

  OSPIM_CfgTypeDef sOspiManagerCfg = {0};

  /* USER CODE BEGIN OCTOSPI1_Init 1 */
  /* USER CODE END OCTOSPI1_Init 1 */
  hospi1.Instance = OCTOSPI1;
  hospi1.Init.FifoThreshold = 1;
  hospi1.Init.DualQuad = HAL_OSPI_DUALQUAD_DISABLE;
  hospi1.Init.MemoryType = HAL_OSPI_MEMTYPE_APMEMORY;
  hospi1.Init.DeviceSize = 24;
  hospi1.Init.ChipSelectHighTime = 1;
  hospi1.Init.FreeRunningClock = HAL_OSPI_FREERUNCLK_DISABLE;
  hospi1.Init.ClockMode = HAL_OSPI_CLOCK_MODE_0;
  hospi1.Init.WrapSize = HAL_OSPI_WRAP_NOT_SUPPORTED;
  hospi1.Init.ClockPrescaler = 1;
  hospi1.Init.SampleShifting = HAL_OSPI_SAMPLE_SHIFTING_NONE;
  hospi1.Init.DelayHoldQuarterCycle = HAL_OSPI_DHQC_ENABLE;
  hospi1.Init.ChipSelectBoundary = 10;
  hospi1.Init.DelayBlockBypass = HAL_OSPI_DELAY_BLOCK_USED;
  hospi1.Init.MaxTran = 0;
  hospi1.Init.Refresh = 400;
  if (HAL_OSPI_Init(&hospi1) != HAL_OK)
  {
    Error_Handler();
  }
  sOspiManagerCfg.ClkPort = 1;
  sOspiManagerCfg.DQSPort = 1;
  sOspiManagerCfg.NCSPort = 1;
  sOspiManagerCfg.IOLowPort = HAL_OSPIM_IOPORT_1_LOW;
  sOspiManagerCfg.IOHighPort = HAL_OSPIM_IOPORT_1_HIGH;
  if (HAL_OSPIM_Config(&hospi1, &sOspiManagerCfg, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN OCTOSPI1_Init 2 */

  /* USER CODE END OCTOSPI1_Init 2 */

}

void HAL_OSPI_MspInit(OSPI_HandleTypeDef* ospiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(ospiHandle->Instance==OCTOSPI1)
  {
  /* USER CODE BEGIN OCTOSPI1_MspInit 0 */

  /* USER CODE END OCTOSPI1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_OSPI;
    PeriphClkInitStruct.PLL2.PLL2M = 4;
    PeriphClkInitStruct.PLL2.PLL2N = 12;
    PeriphClkInitStruct.PLL2.PLL2P = 2;
    PeriphClkInitStruct.PLL2.PLL2Q = 1;
    PeriphClkInitStruct.PLL2.PLL2R = 2;
    PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
    PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
    PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
    PeriphClkInitStruct.OspiClockSelection = RCC_OSPICLKSOURCE_PLL2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* OCTOSPI1 clock enable */
    __HAL_RCC_OCTOSPIM_CLK_ENABLE();
    __HAL_RCC_OSPI1_CLK_ENABLE();

    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    /**OCTOSPI1 GPIO Configuration
    PF6     ------> OCTOSPIM_P1_IO3
    PF7     ------> OCTOSPIM_P1_IO2
    PF8     ------> OCTOSPIM_P1_IO0
    PF9     ------> OCTOSPIM_P1_IO1
    PF10     ------> OCTOSPIM_P1_CLK
    PC3_C     ------> OCTOSPIM_P1_IO6
    PA1     ------> OCTOSPIM_P1_DQS
    PE7     ------> OCTOSPIM_P1_IO4
    PE8     ------> OCTOSPIM_P1_IO5
    PE10     ------> OCTOSPIM_P1_IO7
    PG6     ------> OCTOSPIM_P1_NCS
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPIM_P1;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_OCTOSPIM_P1;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_OCTOSPIM_P1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_OCTOSPIM_P1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPIM_P1;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPIM_P1;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    /* OCTOSPI1 interrupt Init */
    HAL_NVIC_SetPriority(OCTOSPI1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(OCTOSPI1_IRQn);
  /* USER CODE BEGIN OCTOSPI1_MspInit 1 */

  /* USER CODE END OCTOSPI1_MspInit 1 */
  }
}

void HAL_OSPI_MspDeInit(OSPI_HandleTypeDef* ospiHandle)
{

  if(ospiHandle->Instance==OCTOSPI1)
  {
  /* USER CODE BEGIN OCTOSPI1_MspDeInit 0 */

  /* USER CODE END OCTOSPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_OCTOSPIM_CLK_DISABLE();
    __HAL_RCC_OSPI1_CLK_DISABLE();

    /**OCTOSPI1 GPIO Configuration
    PF6     ------> OCTOSPIM_P1_IO3
    PF7     ------> OCTOSPIM_P1_IO2
    PF8     ------> OCTOSPIM_P1_IO0
    PF9     ------> OCTOSPIM_P1_IO1
    PF10     ------> OCTOSPIM_P1_CLK
    PC3_C     ------> OCTOSPIM_P1_IO6
    PA1     ------> OCTOSPIM_P1_DQS
    PE7     ------> OCTOSPIM_P1_IO4
    PE8     ------> OCTOSPIM_P1_IO5
    PE10     ------> OCTOSPIM_P1_IO7
    PG6     ------> OCTOSPIM_P1_NCS
    */
    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_10);

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_3);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1);

    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_10);

    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_6);

    /* OCTOSPI1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(OCTOSPI1_IRQn);
  /* USER CODE BEGIN OCTOSPI1_MspDeInit 1 */

  /* USER CODE END OCTOSPI1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/*----------------------------------------------------------------------*/
/* This function enables memory-mapped mode for Read and Write operations */
void EnableMemMapped(void)
{
	OSPI_RegularCmdTypeDef sCommand;
	OSPI_MemoryMappedTypeDef sMemMappedCfg;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_8_LINES;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_8_LINES;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_ENABLE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_8_LINES;
	sCommand.DataDtrMode = HAL_OSPI_DATA_DTR_ENABLE;
	sCommand.DQSMode = HAL_OSPI_DQS_ENABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	sCommand.Address = 0;
	sCommand.NbData = 1;
	/* Memory-mapped mode configuration for Linear burst write operations */
	sCommand.OperationType = HAL_OSPI_OPTYPE_WRITE_CFG;
	sCommand.Instruction = LINEAR_BURST_WRITE;
	sCommand.DummyCycles = DUMMY_CLOCK_CYCLES_SRAM_WRITE;

	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}
	/* Memory-mapped mode configuration for Linear burst read operations */
	sCommand.OperationType = HAL_OSPI_OPTYPE_READ_CFG;
	sCommand.Instruction = LINEAR_BURST_READ;
	sCommand.DummyCycles = DUMMY_CLOCK_CYCLES_SRAM_READ;
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}
	/*Disable timeout counter for memory mapped mode*/
	sMemMappedCfg.TimeOutActivation = HAL_OSPI_TIMEOUT_COUNTER_DISABLE;
	/*Enable memory mapped mode*/
	if (HAL_OSPI_MemoryMapped(&hospi1, &sMemMappedCfg) != HAL_OK)
	{
		Error_Handler();
	}
}

/*This function is used to calibrate the Delayblock before initiating
USER's application read/write transactions*/
void DelayBlock_Calibration(void)
{
	/*buffer used for calibration*/
	uint8_t Cal_buffer[] = " ****Delay Block Calibration Buffer**** ****Delay Block Calibration Buffer**** ****Delay Block Calibration Buffer**** ****Delay Block Calibration Buffer**** ****Delay Block Calibration Buffer**** ****Delay Block Calibration Buffer**** ";
	uint16_t index;
	__IO uint8_t *mem_addr;
	uint8_t test_failed;
	uint8_t delay = 0x0;
	uint8_t Min_found = 0;
	uint8_t Max_found = 0;
	uint8_t Min_Window = 0x0;
	uint8_t Max_Window = 0xF;
	uint8_t Mid_window = 0;
	uint8_t calibration_ongoing = 1;
	/* Write the Cal_buffer to the memory*/
	mem_addr = (__IO uint8_t *)(OCTOSPI1_BASE);
	for (index = 0; index < DLYB_BUFFERSIZE; index++)
	{
		*mem_addr = Cal_buffer[index];
		mem_addr++;
	}
	while (calibration_ongoing)
	{
		/* update the Delayblock calibration */
		HAL_RCCEx_OCTOSPIDelayConfig(delay, 0);
		test_failed = 0;
		mem_addr = (__IO uint8_t *)(OCTOSPI1_BASE);
		for (index = 0; index < DLYB_BUFFERSIZE; index++)
		{
			/* Read the Cal_buffer from the memory*/
			if (*mem_addr != Cal_buffer[index])
			{
				/*incorrect data read*/
				test_failed = 1;
			}
			mem_addr++;
		}
		/* search for the Min window */
		if (Min_found!=1)
		{
			if (test_failed == 1)
			{
				if (delay < 15)
				{
					delay++;
				}
				else
				{
					/* If delay set to maximum and error still detected: can't use external
					PSRAM */
					Error_Handler();
				}
			}
			else
			{
				Min_Window = delay;
				Min_found=1;
				delay = 0xF;
			}
		}
		/* search for the Max window */
		else if (Max_found!=1)
		{
			if (test_failed == 1)
			{
				if (delay > 0)
				{
					delay--;
				}
				else
				{
					/* If delay set to minimum and error still detected: can't use external
					PSRAM */
					Error_Handler();
				}
			}
			else
			{
				Max_Window = delay;
				Max_found=1;
			}
		}
		/* min and max delay window found, configure the delay block with the middle
		window value and exit calibration */
		else
		{
			Mid_window = (Max_Window+Min_Window)/2;
			HAL_RCCEx_OCTOSPIDelayConfig(Mid_window, 0);
			/* exit calibration */
			calibration_ongoing = 0;
		}
	}
}
/* USER CODE END 1 */
