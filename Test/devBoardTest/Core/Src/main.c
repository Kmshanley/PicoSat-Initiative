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
#include "stdbool.h"
#include "INA236.h"
#include "PCA9543.h"
#include "TMP117.h"
#include "aps6408.h"
#include "aps6408_conf.h"
#include "W25Nxx.h"
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
uint8_t aRxBuffer[512];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
/* USER CODE BEGIN PFP */
void Configure_APMemory(void);
static void test_NAND(void);
static void test_PSRAM(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
INA236_dev INA33Bus;
INA236_dev INA18Bus;
TMP117_dev temp_A;
PCA9543_dev i2c_switch;
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

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_RESET); //Memory reset
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_DCMI_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_OCTOSPI1_Init();
  MX_OCTOSPI2_Init();
  /* USER CODE BEGIN 2 */


  log_info("Main Init");

  //test_PSRAM();
  test_NAND();

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

  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	float temperature_A = 0;
	if (TMP117_read_temperature(&temp_A, &temperature_A) == HAL_OK) {
		log_info("Temperature A:%f", temperature_A);
	}
	else {
		log_error("Unable to get temp A");
	}

	/*
	float voltage = 0;
	if (INA236_get_bus_voltage(&INA18Bus, &voltage) == HAL_OK) {
	  log_info("1.8v Bus Voltage:%f", voltage);
	}
	else {
	  log_error("Error getting 1.8v bus voltage");
	}
	*/



	HAL_Delay(5000);

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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = 64;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 42;
  RCC_OscInitStruct.PLL.PLLP = 1;
  RCC_OscInitStruct.PLL.PLLQ = 2;
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
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CKPER;
  PeriphClkInitStruct.CkperClockSelection = RCC_CLKPSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

static void test_NAND(void)
{
	W25N_setup(&W25N, &hospi2, 0);

	uint32_t nand_id = 0;
	uint8_t statReg = 0;
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
	__HAL_OSPI_DISABLE(&hospi1);
	HAL_Delay(100);
	CLEAR_BIT(hospi1.Instance->DCR1, OCTOSPI_DCR1_FRCK);
	__HAL_OSPI_ENABLE(&hospi1);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_SET); //Memory reset pin HIGH
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET);

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


	if (APS6408_EnableMemoryMappedMode(&hospi1, APS6408_READ_LATENCY_5, DUMMY_CLOCK_CYCLES_WRITE, APS6408_MR8_BL_32_BYTES) != HAL_OK)
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

void Configure_APMemory(void)
{
  /* MR0 register for read and write */
  uint8_t regW_MR0[2]={0x24,0x0D}; /* To configure AP memory Latency Type and drive Strength */
  uint8_t regR_MR0[2]={0};

  /* MR8 register for read and write */
  uint8_t regW_MR8[2]={0x0B,0x08}; /* To configure AP memory Burst Type */
  uint8_t regR_MR8[2]={0};

  /*Read Latency */
  uint8_t latency=6;

  /* Configure Read Latency and drive Strength */
  if (APS6408_WriteReg(&hospi1, APS6408_MR0_ADDRESS, regW_MR0[0]) != HAL_OK)
  {
    Error_Handler();
  }

  /* Check MR0 configuration */
  if (APS6408_ReadReg(&hospi1, APS6408_MR0_ADDRESS, regR_MR0, latency ) != HAL_OK)
  {
    Error_Handler();
  }

    /* Check MR0 configuration */
  if (regR_MR0 [0] != regW_MR0 [0])
  {
	  log_error("MR0 Set failed");
  }

  /* Configure Burst Length */
  if (APS6408_WriteReg(&hospi1, APS6408_MR8_ADDRESS, regW_MR8[0]) != HAL_OK)
  {
    Error_Handler();
  }

  /* Check MR8 configuration */
  if (APS6408_ReadReg(&hospi1, APS6408_MR8_ADDRESS, regR_MR8, 6) != HAL_OK)
  {
    Error_Handler();
  }

  if (regR_MR8[0] != regW_MR8[0])
  {
	  log_error("MR8 Set Failed");
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	log_error("Unrecoverable Error");
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
