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
#include "crc.h"
#include "dcmi.h"
#include "fatfs.h"
#include "i2c.h"
#include "octospi.h"
#include "ramecc.h"
#include "rng.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "log.h"
#include "TMP117.h"
#include "aps6408.h"
#include "aps6408_conf.h"
#include "W25Nxx.h"
#include "stm32l4p5g_discovery_psram.h"
#define CONFIG_YAFFS_DIRECT 1
#include "yaffs_yaffs2.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define BUFFERSIZE (COUNTOF(aTxBuffer) - 1)
#define COUNTOF(__BUFFER__) (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
#define DLYB_BUFFERSIZE (COUNTOF(Cal_buffer) - 1)
#define EXTENDEDBUFFERSIZE (1048576)
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
uint8_t aRxBuffer[512];

static char * testString = "This is a test string, for testing memory.";
static char recvString[128];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
static void test_PSRAM(void);
static void test_NAND(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
TMP117_dev temp_A;
W25Nxx_dev W25N;
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
  MX_DCMI_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_OCTOSPI1_Init();
  MX_USART1_UART_Init();
  MX_I2C4_Init();
  MX_OCTOSPI2_Init();
  MX_RAMECC_Init();
  MX_USART2_UART_Init();
  MX_SPI4_Init();
  MX_CRC_Init();
  MX_RNG_Init();
  MX_RTC_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM12_Init();
  MX_SPI5_Init();
  MX_TIM5_Init();
  MX_FATFS_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
  log_info("Main Init");
  test_NAND();
  test_PSRAM();

  /*
  if (BSP_PSRAM_Init() != PSRAM_OK) {
	  log_error("APS12808 error");
  }
  BSP_PSRAM_WriteData(0x00, (uint8_t *) testString, 43);
  BSP_PSRAM_ReadData(0x00, (uint8_t *) recvString, 43);

  BSP_PSRAM_EnableMemoryMappedMode();
   */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_CRSInitTypeDef RCC_CRSInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSI
                              |RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = 64;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 34;
  RCC_OscInitStruct.PLL.PLLP = 1;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 3072;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the SYSCFG APB clock
  */
  __HAL_RCC_CRS_CLK_ENABLE();

  /** Configures CRS
  */
  RCC_CRSInitStruct.Prescaler = RCC_CRS_SYNC_DIV1;
  RCC_CRSInitStruct.Source = RCC_CRS_SYNC_SOURCE_LSE;
  RCC_CRSInitStruct.Polarity = RCC_CRS_SYNC_POLARITY_RISING;
  RCC_CRSInitStruct.ReloadValue = __HAL_RCC_CRS_RELOADVALUE_CALCULATE(48000000,32768);
  RCC_CRSInitStruct.ErrorLimitValue = 34;
  RCC_CRSInitStruct.HSI48CalibrationValue = 32;

  HAL_RCCEx_CRSConfig(&RCC_CRSInitStruct);
}

/* USER CODE BEGIN 4 */
static void test_NAND(void)
{
	W25N_setup(&W25N, &hospi2, 0);

	uint64_t nand_id = 0;
	uint16_t statReg = 0;
	if (W25N_ReadJEDECID(&W25N, &nand_id) == W25N_OK) {
	  log_info("W25N ID: %X", nand_id);
	}
	else {
	  log_error("Unable to read from W25N");
	}
	W25N_Write_Enable(&W25N);

	W25N_Read_Status_Reg(&W25N, W25N_STATUS_REG, &statReg);
	log_info("W25N status: %X", statReg);
	W25N_Read_Status_Reg(&W25N, W25N_CONFIG_REG, &statReg);
	log_info("W25N config: %X", statReg);
	W25N_Read_Status_Reg(&W25N, W25N_PROTECTION_REG, &statReg);
	log_info("W25N protection: %X", statReg);
	W25N_Write_Status_Reg(&W25N, W25N_PROTECTION_REG, 0x00); //Disable memory protection
	W25N_Write_Status_Reg(&W25N, W25N_CONFIG_REG, 0x18); //Enable ECC and buffer

	W25N_Block_Erase(&W25N, 0x0026);
	W25N_Read_Status_Reg(&W25N, W25N_STATUS_REG, &statReg);
	log_info("W25N status: %X", statReg);
	W25N_Read_Status_Reg(&W25N, W25N_PROTECTION_REG, &statReg);
	log_info("W25N protection: %X", statReg);
	W25N_Wait_Until_Not_Busy(&W25N, 30000);

	memset(aRxBuffer, 0xff, 512);

	W25N_Write_Enable(&W25N); //Must be called before Data load

	if (W25N_Load_Data_Quad(&W25N, 0x00, aTxBuffer, 256) != W25N_OK) {
	  log_error("W25N Unable to load data");
	}

	W25N_Program_Execute(&W25N, 0x0026);
	W25N_Read_Status_Reg(&W25N, W25N_STATUS_REG, &statReg);
	log_info("W25N status after execute: %X", statReg);
	W25N_Wait_Until_Not_Busy(&W25N, 30000);

	W25N_Read_Status_Reg(&W25N, W25N_STATUS_REG, &statReg);
	log_info("W25N status after execute done: %X", statReg);
	W25N_Page_Data_Read(&W25N, 0x0026);
	W25N_Read_Status_Reg(&W25N, W25N_STATUS_REG, &statReg);
	log_info("W25N status after page load: %X", statReg);
	W25N_Wait_Until_Not_Busy(&W25N, 30000);

	W25N_Read_Status_Reg(&W25N, W25N_STATUS_REG, &statReg);
	log_info("W25N status after page load done: %X", statReg);
	if (W25N_Read_Output_Quad(&W25N, 0x00, aRxBuffer, 256) != W25N_OK) {
	  log_error("W25N unable to read output");
	}

	if (aRxBuffer[0] == aTxBuffer[0]) {
	  log_info("----W25N R/W Success----");
	}
	else {
	  log_error("W25N R/W Failure");
	}
}

static void test_PSRAM(void)
{
	uint16_t id;
	if (APS6408_ReadID(&hospi1, &id, 5) != APS6408_OK) {
	  log_error("APS12808 error");
	}
	else {
	  log_info("APS12808 config: %X", id);
	}

	if (APS6408_Write(&hospi1, aTxBuffer, 0x00, 4, DUMMY_CLOCK_CYCLES_WRITE, APS6408_MR8_BL_32_BYTES) != HAL_OK) {
	  log_error("Unable to write to APS6408");
	}
	uint32_t testData = 0;
	if (APS6408_Read(&hospi1, (uint8_t *)&testData, 0x00, 4, DUMMY_CLOCK_CYCLES_READ, APS6408_MR8_BL_32_BYTES) != HAL_OK) {
	  log_error("Unable to write to APS6408");
	}

	if (testData != *((uint32_t *)aTxBuffer)) {
	  log_error("APS6048 Read/Write Fail");
	}
	else {
	  log_info("APS6048 Read/Write Success");
	}


	if (APS6408_EnableMemoryMappedMode(&hospi1, 5, DUMMY_CLOCK_CYCLES_WRITE, APS6408_MR8_BL_32_BYTES) != HAL_OK)
	{
	  log_error("Unable to start APS6408 memory mapped mode");
	}

	__IO uint8_t *mem_addr;
	uint32_t address = 0;
	uint16_t index1;/*index1 counter of bytes used when reading/writing 256 bytes buffer */
	uint16_t index2;/*index2 counter of 256 bytes buffer used */
	bool noErrors = true;
	mem_addr = (__IO uint8_t *)(OCTOSPI1_BASE + address);
	//Writing 1Mbyte (256Byte BUFFERSIZE x 4096 times)
	for (index2 = 0; index2 < EXTENDEDBUFFERSIZE/BUFFERSIZE; index2++)
	{
		for (index1 = 0; index1 < BUFFERSIZE; index1++)
		{
			*mem_addr = aTxBuffer[index1];
			mem_addr++;
		}
	}
	//----------------------------------------------------------------------
	//Reading Sequence of 1Mbyte
	mem_addr = (__IO uint8_t *)(OCTOSPI1_BASE + address);
	//Reading 1Mbyte (256Byte BUFFERSIZE x 4096 times)
	for (index2 = 0; index2 < EXTENDEDBUFFERSIZE/BUFFERSIZE; index2++) {
		for (index1 = 0; index1 < BUFFERSIZE; index1++)
		{
			uint8_t data = *mem_addr;
			if (data != aTxBuffer[index1])
			{
				//if data read is corrupted we can toggle a led here: example blue led
				//log_error("Data Corrupt, %d != %d", data, aTxBuffer[index1]);
				noErrors = false;
			}
				mem_addr++;
		}
	}

	if (noErrors) {
		log_info("PSRAM data transfer success");
	}
	else {
		log_info("PSRAM data transfer failure");
	}
}

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM2 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM2) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
