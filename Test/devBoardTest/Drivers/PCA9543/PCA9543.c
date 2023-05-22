/*
 * PCA9543.c
 *
 *  Created on: May 16, 2023
 *      Author: Kieran Shanley
 */
#include "PCA9543.h"

void PCA9543_setup(PCA9543_dev * dev, I2C_Bus * bus, uint8_t addr)
{
	dev->addr = addr;
	dev->bus = bus;
}

int32_t PCA9543_set_channel(PCA9543_dev * dev, uint8_t channel)
{
	uint8_t data = channel;
	uint8_t addr = dev->addr << 1;
	if (HAL_I2C_Master_Transmit(dev->bus->I2C_Handle, addr, &data, 1, 1000) == HAL_OK) {
		return HAL_OK;
	}

	return HAL_ERROR;
}
