/**
 *******************************************
 * @file    W25Nxx.c
 * @author  Kieran Shanley
 * @version
 * @date    6/20/23
 * @brief
 * @note
 *******************************************
 */

#include "W25Nxx.h"

void W25N_setup(W25Nxx_dev * dev, OSPI_HandleTypeDef * ospi, uint8_t flashID) {
	dev->ospi = ospi;
	dev->flashID = flashID;
}


/**
 * @brief W25Q Read ID
 * Function for reading chip ID
 *
 * @param[in] device struct
 * @param[out] buf Pointer to output data (3 bytes)
 * @return W25N_STATE enum
 */
W25N_STATE W25N_ReadJEDECID(W25Nxx_dev * dev, uint32_t * buf) {
	OSPI_RegularCmdTypeDef com = {0};

	com.FlashId = dev->flashID;

	com.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE; // QSPI_INSTRUCTION_...
	com.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	com.Instruction = W25N_DEVID;	 // Command

	com.DummyCycles = 8;
	com.DataMode = HAL_OSPI_DATA_1_LINE;
	com.NbData = 3;

	com.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;

	if (HAL_OSPI_Command(dev->ospi, &com, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25N_SPI_ERR;
	}
	if (HAL_OSPI_Receive(dev->ospi, (uint8_t *)buf, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25N_SPI_ERR;
	}
	return W25N_OK;
}

/**
 * @brief W25Q Write Enable
 *
 * @param[in] device struct
 * @return W25N_STATE enum
 */
W25N_STATE W25N_Write_Enable(W25Nxx_dev * dev) {
	OSPI_RegularCmdTypeDef com = {0};

	com.FlashId = dev->flashID;

	com.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE; // QSPI_INSTRUCTION_...
	com.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	com.Instruction = W25N_WRITE_ENABLE;	 // Command

	if (HAL_OSPI_Command(dev->ospi, &com, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25N_SPI_ERR;
	}
	return W25N_OK;
}

/**
 * @brief W25N Write Enable
 * Must be called before data load.
 * Must be called before block erase.
 *
 * @param[in] device struct
 * @return W25N_STATE enum
 */
W25N_STATE W25N_Write_Disable(W25Nxx_dev * dev) {
	OSPI_RegularCmdTypeDef com = {0};

	com.FlashId = dev->flashID;

	com.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE; // QSPI_INSTRUCTION_...
	com.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	com.Instruction = W25N_WRITE_DISABLE;	 // Command

	if (HAL_OSPI_Command(dev->ospi, &com, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25N_SPI_ERR;
	}
	return W25N_OK;
}

/**
 * @brief W25N Erase Block
 * Erase one 128K Byte block
 * A Write enable instruction must have previously executed
 * Write protection in W25N_PROTECTION_REG for the address block must be disabled or operation will fail
 *
 * @param[in] device struct
 * @param[in] address of the page to erase
 * @return W25N_STATE enum
 */
W25N_STATE W25N_Block_Erase(W25Nxx_dev * dev, uint16_t pageAddress)
{
	OSPI_RegularCmdTypeDef com = {0};

	com.FlashId = dev->flashID;

	com.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE; // QSPI_INSTRUCTION_...
	com.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	com.Instruction = W25N_BLOCK_ERASE;	 // Command

	com.NbData = 2;
	com.DummyCycles = 8;
	com.DataMode = HAL_OSPI_DATA_1_LINE;

	if (HAL_OSPI_Command(dev->ospi, &com, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25N_SPI_ERR;
	}

	if (HAL_OSPI_Transmit(dev->ospi, (uint8_t *)&pageAddress, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		return W25N_SPI_ERR;
	}
	return W25N_OK;
}

/**
 * @brief W25N Read Register
 *
 * @param[in] device struct
 * @param[in] address of register to read
 * @param[out] contents of register
 * @return W25N_STATE enum
 */
W25N_STATE W25N_Read_Status_Reg(W25Nxx_dev * dev, uint8_t SRAddress, uint8_t * reg)
{
	OSPI_RegularCmdTypeDef com = {0};

	com.FlashId = dev->flashID;

	com.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE; // QSPI_INSTRUCTION_...
	com.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	com.Instruction = W25N_READ_SR1;	 // Command

	com.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
	com.AddressSize = HAL_OSPI_ADDRESS_8_BITS;
	com.Address = SRAddress;

	com.DummyCycles = 0;
	com.DataMode = HAL_OSPI_DATA_1_LINE;
	com.NbData = 1;

	if (HAL_OSPI_Command(dev->ospi, &com, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25N_SPI_ERR;
	}
	if (HAL_OSPI_Receive(dev->ospi, (uint8_t *)reg, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25N_SPI_ERR;
	}
	return W25N_OK;
}

/**
 * @brief W25N Write Register
 *
 * @param[in] device struct
 * @param[in] address of register to write
 * @param[in] contents of register
 * @return W25N_STATE enum
 */
W25N_STATE W25N_Write_Status_Reg(W25Nxx_dev * dev, uint8_t SRAddress, uint8_t reg) {
	OSPI_RegularCmdTypeDef com = {0};

	com.FlashId = dev->flashID;

	com.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE; // QSPI_INSTRUCTION_...
	com.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	com.Instruction = W25N_WRITE_SR1;	 // Command

	com.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
	com.AddressSize = HAL_OSPI_ADDRESS_8_BITS;
	com.Address = SRAddress;

	com.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_1_LINE;
	com.AlternateBytes = reg;
	com.AlternateBytesSize = HAL_OSPI_ALTERNATE_BYTES_8_BITS;

	if (HAL_OSPI_Command(dev->ospi, &com, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25N_SPI_ERR;
	}
	return W25N_OK;
}

/**
 * @brief W25N Load Data QSPI
 * Load data into the memory buffer. Using 4 data lanes (QSPI).
 * Program execute instruction must be executed after this command
 * to transfer memory buffer contents to page.
 *
 * @param[in] device struct
 * @param[in] Column Address
 * @param[in] Address of the buffer to write
 * @param[in] Size of the buffer in bytes, max of 2112 bytes
 * @return W25N_STATE enum
 */
W25N_STATE W25N_Load_Data_Quad(W25Nxx_dev * dev, uint16_t columnAddress, uint8_t * buffer, uint32_t bufferSize) {
	OSPI_RegularCmdTypeDef com = {0};

	com.FlashId = dev->flashID;

	com.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE; // QSPI_INSTRUCTION_...
	com.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	com.Instruction = W25N_QUAD_PROGRAM_DATA_LOAD;	 // Command

	com.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
	com.AddressSize = HAL_OSPI_ADDRESS_16_BITS;
	com.Address = columnAddress;

	com.DataMode = HAL_OSPI_DATA_4_LINES; //QSPI
	com.NbData = bufferSize;

	if (HAL_OSPI_Command(dev->ospi, &com, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25N_SPI_ERR;
	}

	//Transmit the data
	if (HAL_OSPI_Transmit(dev->ospi, buffer, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		return W25N_SPI_ERR;
	}
	return W25N_OK;
}

/**
 * @brief W25N Program Execute
 * Program the data buffer contents into a physical memory page.
 *
 * @param[in] device struct
 * @param[in] address of page to write to
 * @return W25N_STATE enum
 */
W25N_STATE W25N_Program_Execute(W25Nxx_dev * dev, uint16_t pageAddress) {
	OSPI_RegularCmdTypeDef com = {0};

	com.FlashId = dev->flashID;

	com.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE; // QSPI_INSTRUCTION_...
	com.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	com.Instruction = W25N_PROGRAM_EXECUTE;	 // Command

	com.NbData = 2; //We will be transmitting 2 bytes for page address
	com.DummyCycles = 8;
	com.DataMode = HAL_OSPI_DATA_1_LINE;

	if (HAL_OSPI_Command(dev->ospi, &com, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25N_SPI_ERR;
	}
	uint16_t addr = pageAddress;
	//Transmit the page address
	if (HAL_OSPI_Transmit(dev->ospi, (uint8_t *)&addr, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		return W25N_SPI_ERR;
	}

	return W25N_OK;
}

/**
 * @brief W25N Page Read
 * Load a 2112 Byte Page into the data buffer
 *
 * @param[in] device struct
 * @param[in] address of page to read
 * @return W25N_STATE enum
 */
W25N_STATE W25N_Page_Data_Read(W25Nxx_dev * dev, uint16_t pageAddress)
{
	OSPI_RegularCmdTypeDef com = {0};

	com.FlashId = dev->flashID;

	com.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE; // QSPI_INSTRUCTION_...
	com.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	com.Instruction = W25N_PAGE_DATA_READ;	 // Command

	com.NbData = 2; //We will be transmitting 2 bytes for page address
	com.DummyCycles = 8;
	com.DataMode = HAL_OSPI_DATA_1_LINE;

	if (HAL_OSPI_Command(dev->ospi, &com, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25N_SPI_ERR;
	}

	//Transmit the page address
	if (HAL_OSPI_Transmit(dev->ospi, (uint8_t *)&pageAddress, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		return W25N_SPI_ERR;
	}

	return W25N_OK;
}

/**
 * @brief W25N Read Buffer Output
 * Read data from the buffer using 4 data lanes (QSPI)
 *
 * @param[in] device struct
 * @param[in] Column address
 * @param[out] buffer to output to
 * @param[in] size of buffer
 * @return W25N_STATE enum
 */
W25N_STATE W25N_Read_Output_Quad(W25Nxx_dev * dev, uint16_t columnAddress, uint8_t * buffer, uint32_t bufferSize)
{
	OSPI_RegularCmdTypeDef com = {0};

	com.FlashId = dev->flashID;

	com.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE; // QSPI_INSTRUCTION_...
	com.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	com.Instruction = W25N_FAST_READ_QUAD;	 // Command

	com.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
	com.AddressSize = HAL_OSPI_ADDRESS_16_BITS;
	com.Address = columnAddress;

	com.DataMode = HAL_OSPI_DATA_4_LINES; //QSPI
	com.NbData = bufferSize;
	com.DummyCycles = 8;

	if (HAL_OSPI_Command(dev->ospi, &com, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25N_SPI_ERR;
	}
	//Receive the data
	if (HAL_OSPI_Receive(dev->ospi, buffer, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		return W25N_SPI_ERR;
	}
	return W25N_OK;
}

/**
 * @brief W25N Read Last ECC Failure Page
 *
 * @param[in] device struct
 * @param[out] Page address of the ecc failure
 * @return W25N_STATE enum
 */
W25N_STATE W25N_Last_ECC_Failure_Page(W25Nxx_dev * dev, uint16_t * pageAddress)
{
	OSPI_RegularCmdTypeDef com = {0};

	com.FlashId = dev->flashID;

	com.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	com.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	com.Instruction = W25N_LAST_EEC_FAILURE_PAGE;	 // Command

	com.DataMode = HAL_OSPI_DATA_1_LINE;
	com.NbData = 2;
	com.DummyCycles = 8;

	if (HAL_OSPI_Command(dev->ospi, &com, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25N_SPI_ERR;
	}
	//Receive the data
	if (HAL_OSPI_Receive(dev->ospi, (uint8_t *)pageAddress, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		return W25N_SPI_ERR;
	}
	return W25N_OK;
}

/**
 * @brief W25N Wait until busy bit is 0
 *
 * @param[in] Device struct
 * @param[in] Timeout
 * @return W25N_STATE enum
 */
W25N_STATE W25N_Wait_Until_Not_Busy(W25Nxx_dev * dev, uint32_t timout_ms)
{
	OSPI_RegularCmdTypeDef com = {0};
	OSPI_AutoPollingTypeDef polling_cmd = {0};

	com.FlashId = dev->flashID;

	com.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE; // QSPI_INSTRUCTION_...
	com.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	com.Instruction = W25N_READ_SR1;	 // Command

	com.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
	com.AddressSize = HAL_OSPI_ADDRESS_8_BITS;
	com.Address = W25N_STATUS_REG;

	com.DummyCycles = 0;
	com.DataMode = HAL_OSPI_DATA_1_LINE;
	com.NbData = 1;

	polling_cmd.AutomaticStop = HAL_OSPI_AUTOMATIC_STOP_ENABLE;
	polling_cmd.Interval = 16U;
	polling_cmd.Mask = 0x00000001; //Busy bit is LSB, the only one we care about
	polling_cmd.Match = 0x00000000; //Busy bit is 0 when not busy
	polling_cmd.MatchMode = HAL_OSPI_MATCH_MODE_AND;

	if (HAL_OSPI_Command(dev->ospi, &com, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25N_SPI_ERR;
	}
	if (HAL_OSPI_AutoPolling(dev->ospi, &polling_cmd, timout_ms) != HAL_OK)
	{
		return W25N_SPI_ERR;
	}
	return W25N_OK;
}
