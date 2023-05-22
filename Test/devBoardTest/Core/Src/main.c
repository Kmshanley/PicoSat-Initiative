/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "dcmi.h"
#include "i2c.h"
#include "octospi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "log.h"
#include "string.h"
#include "INA236.h"
#include "PCA9543.h"
#include "TMP117.h"
#include "aps6408.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t aTxBuffer[] = " **OCTOSPI/Octal-spi PSRAM Memory-mapped communication example** **OCTOSPI/Octal-spi PSRAM Memory-mapped communication example** **OCTOSPI/Octal-spi PSRAM Memory-mapped communication example** **OCTOSPI/Octal-spi PSRAM Memory-mapped communication example**";
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
INA236_dev INA33Bus;
INA236_dev INA18Bus;
TMP117_dev temp_A;
PCA9543_dev i2c_switch;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_DCMI_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_OCTOSPI1_Init();
  /* USER CODE BEGIN 2 */
  log_info("Main Init");
  //EnableMemMapped();
  uint32_t id = 0;
  APS6408_Reset(&hospi1);
  if (APS6408_ReadID(&hospi1, &id, APS6408_READ_LATENCY_7) != HAL_OK)
  {
	  log_error("Unable to read ID");
  }
  else
  {
	  log_info("APS6048 ID:%d", id);
  }

  if (APS6408_EnableMemoryMappedMode(&hospi1, APS6408_READ_LATENCY_7, APS6408_MR4_WLC_7, APS6408_MR8_BL_32_BYTES) != HAL_OK)
  {
	  log_error("Unable to start APS6408 memory mapped mode");
  }

  //DelayBlock_Calibration();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  INA236_setup(&INA33Bus, &i2c_bus_2, INA236_ADDR_1);
  INA236_setup(&INA18Bus, &i2c_bus_2, INA236_ADDR_1);
  PCA9543_setup(&i2c_switch, &i2c_bus_2, PCA9543_ADDR_1);
  TMP117_setup(&temp_A, &i2c_bus_2, TMP117_ADDR_1);

  if (PCA9543_set_channel(&i2c_switch, PCA9543_CHANNEL_1) != HAL_OK)
  {
	  log_error("Unable to set i2c switch channel");
  }

  /*
  if (HAL_I2C_IsDeviceReady(&hi2c2, PCA9543_ADDR_1, 2, 1000) != HAL_OK)
  {
	  log_error("Unable to communicate with i2c switch");
  } */

  if (HAL_I2C_IsDeviceReady(&hi2c2, TMP117_ADDR_1 << 1, 2, 1000) != HAL_OK)
  {
	  log_error("Unable to communicate with TMP117_A");
  }
  else {
	  log_info("TMP117_A Ready");
  }

  if (HAL_I2C_IsDeviceReady(&hi2c1, 0b11010000, 2, 1000) != HAL_OK)
  {
	  log_error("Unable to communicate with ICM-20948");
  }
  else {
	  log_info("ICM-20948 Ready");
  }

  __IO uint8_t *mem_addr;
  uint32_t address = 0;
  uint16_t index1;/*index1 counter of bytes used when reading/writing 256 bytes buffer */
  uint16_t index2;/*index2 counter of 256 bytes buffer used */

  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	float voltage = 0;
	float temperature_A = 0;
	if (TMP117_read_temperature(&temp_A, &temperature_A) == HAL_OK) {
		log_info("Temperature A:%f", temperature_A);
	}
	else {
		log_error("Unable to get temp A");
	}

	/*
	if (INA236_get_bus_voltage(&INA18Bus, &voltage) == HAL_OK) {
	  log_info("1.8v Bus Voltage:%f", voltage);
	}
	else {
	  log_error("Error getting 1.8v bus voltage");
	}
	*/

	mem_addr = (__IO uint8_t *)(OCTOSPI1_BASE + address);
	/*Writing 1Mbyte (256Byte BUFFERSIZE x 4096 times) */
	for (index2 = 0; index2 < EXTENDEDBUFFERSIZE/BUFFERSIZE; index2++)
	{
		for (index1 = 0; index1 < BUFFERSIZE; index1++)
		{
			*mem_addr = aTxBuffer[index1];
			mem_addr++;
		}
	}
	/*----------------------------------------------------------------------*/
	/* Reading Sequence of 1Mbyte */
	mem_addr = (__IO uint8_t *)(OCTOSPI1_BASE + address);
	/*Reading 1Mbyte (256Byte BUFFERSIZE x 4096 times)*/
	for (index2 = 0; index2 < EXTENDEDBUFFERSIZE/BUFFERSIZE; index2++) {
		for (index1 = 0; index1 < BUFFERSIZE; index1++)
		{
			if (*mem_addr != aTxBuffer[index1])
			{
				/*if data read is corrupted we can toggle a led here: example blue led*/
				//log_error("Data Corrupt");
			}
				mem_addr++;
		}
	}
	/*if data read is correct we can toggle a led here: example green led*/
	log_info("PSRAM data transfer success");

	HAL_Delay(1000);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSI);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 16;
  RCC_OscInitStruct.PLL.PLLP = 1;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
