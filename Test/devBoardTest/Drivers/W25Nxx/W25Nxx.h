/*
 * W25Nxx.h
 *
 *  Created on: Jun 20, 2023
 *      Author: Kieran Shanley
 */

#ifndef W25NXX_W25NXX_H_
#define W25NXX_W25NXX_H_

#include "stm32h7xx_hal.h"
#include "stdbool.h"

#define W25N_RESET 								0xFFU
#define W25N_DEVID 								0x9FU	///< read Device ID (same as powerup)
#define W25N_READ_SR1 							0x0FU	///< read status-register
#define W25N_READ_SR2 							0x05U	///< read status-register
#define W25N_WRITE_SR1 							0x1FU	///< write status-register 1 (8.2.5)
#define W25N_WRITE_SR2 							0x01U	///< write status-register 2 (8.2.5)
#define W25N_WRITE_ENABLE 						0x06U
#define W25N_WRITE_DISABLE 						0x04U
#define W25N_BB_MANAGEMENT 						0xA1U
#define W25N_BBM_LUT 							0xA5U
#define W25N_LAST_EEC_FAILURE_PAGE 				0xA9U
#define W25N_BLOCK_ERASE 						0xD8U
#define W25N_PROGRAM_DATA_LOAD 					0x02U
#define W25N_RANDOM_PROGRAM_DATA_LOAD 			0x84U
#define W25N_QUAD_PROGRAM_DATA_LOAD 			0x32U
#define W25N_QUAD_RANDOM_PROGRAM_DATA_LOAD		0x34U
#define W25N_PROGRAM_EXECUTE 					0x10U
#define W25N_PAGE_DATA_READ 					0x13U
#define W25N_READ 								0x03U
#define W25N_FAST_READ 							0x0BU
#define W25N_FAST_READ_4 						0x0CU
#define W25N_FAST_READ_DUAL 					0x3BU
#define W25N_FAST_READ_DUAL_4 					0x3CU
#define W25N_FAST_READ_QUAD 					0x6BU
#define W25N_FAST_READ_QUAD_4 					0x6CU
#define W25N_FAST_READ_DUAL_IO 					0xBBU
#define W25N_FAST_READ_DUAL_IO_4 				0xBCU
#define W25N_FAST_READ_QUAD_IO 					0xEBU
#define W25N_FAST_READ_QUAD_IO_4 				0xECU

#define W25N_PROTECTION_REG 0xA0U
#define W25N_CONFIG_REG 0xB0U
#define W25N_STATUS_REG 0xC0U

#define W25N_PAGE_ID 0x00U //Factory programmed, Read Only, 32-Byte x 16
#define W25N_PAGE_PARAMETER 0x01U //Factory programmed, Read Only, 256-Byte x 3

#define W25N_PAGE_FIRST_USER 0x0C //The first non-special page
//#define W25N_PGAE_LAST_USER 0x3F //The last user page

#define W25N01GW_NUM_PAGES 65536U //Number of pages
#define W25N01GW_PAGE_SIZE 2048U //Size of page in bytes
#define W25N01GW_BLOCK_SIZE_PAGES 64U //Number of pages that must be erased at once
#define W25N01GW_BLOCK_SIZE_BYTES 128000U //Number of bytes that must be erased at once
#define W25N01GW_BLOCK_NUM 1024U //Number of erase-able blocks

typedef struct {
	OSPI_HandleTypeDef * ospi; //Pointer to the Ospi handle
	uint8_t flashID; //ID of this device on a dual quad spi bus
	bool bufferMode;
} W25Nxx_dev;

typedef struct{
	bool SRP1;  // Status Register Protect 1
	bool WPE;	// WP Enable
	bool TB;	// Top/Bottom Protect Bit
	bool BP0; 	//
	bool BP1; 	//
	bool BP2; 	//
	bool BP3;   //
	bool SRP0;  // Status Register Protect 0
}W25N_STATUS_REG_1;

typedef struct{
	bool OTPL;  // OTP Data Pages Lock
	bool OTPE;	// Enter OTP Mode
	bool SR1L;	// Status Register 1 Lock
	bool ECCE; 	// Enable ECC
	bool BUF; 	// Buffer Mode
}W25N_STATUS_REG_2;

typedef struct{
	bool BUSY;  ///< Erase/Write in progress
	bool WEL;	///< Write enable latch (1 - write allowed)
	bool EFAIL;	///< Quad SPI mode
	bool PFAIL; 	///< Suspend Status
	bool ADS; 	///< Current addr mode (0-3 byte / 1-4 byte)
	bool ADP; 	///< Power-up addr mode
	bool SLEEP; ///< Sleep Status
}W25N_STATUS_REG_3;

typedef enum{
	W25N_OK = 0,  		///< Chip OK - Execution fine
	W25N_BUSY = 1,		///< Chip busy
	W25N_PARAM_ERR = 2, ///< Function parameters error
	W25N_CHIP_ERR = 3,	///< Chip error
	W25N_SPI_ERR = 4, 	///< SPI Bus err
	W25N_CHIP_IGNORE = 5, ///< Chip ignore state
}W25N_STATE;

void W25N_setup(W25Nxx_dev * dev, OSPI_HandleTypeDef * ospi, uint8_t flashID);
W25N_STATE W25N_ReadJEDECID(W25Nxx_dev * dev, uint32_t * buf); 		///< Read ID by JEDEC Standards
W25N_STATE W25N_Write_Enable(W25Nxx_dev * dev);
W25N_STATE W25N_Write_Disable(W25Nxx_dev * dev);
W25N_STATE W25N_Block_Erase(W25Nxx_dev * dev, uint16_t pageAddress);
W25N_STATE W25N_Read_Status_Reg(W25Nxx_dev * dev, uint8_t SRAddress, uint8_t * reg);
W25N_STATE W25N_Write_Status_Reg(W25Nxx_dev * dev, uint8_t SRAddress, uint8_t reg);
W25N_STATE W25N_Load_Data_Quad(W25Nxx_dev * dev, uint16_t columnAddress, uint8_t * buffer, uint32_t bufferSize);
W25N_STATE W25N_Program_Execute(W25Nxx_dev * dev, uint16_t pageAddress);
W25N_STATE W25N_Page_Data_Read(W25Nxx_dev * dev, uint16_t pageAddress);
W25N_STATE W25N_Read_Output_Quad(W25Nxx_dev * dev, uint16_t columnAddress, uint8_t * buffer, uint32_t bufferSize);
W25N_STATE W25N_Last_ECC_Failure_Page(W25Nxx_dev * dev, uint16_t * pageAddress);
W25N_STATE W25N_Wait_Until_Not_Busy(W25Nxx_dev * dev, uint32_t timout_ms);

#endif /* W25NXX_W25NXX_H_ */
