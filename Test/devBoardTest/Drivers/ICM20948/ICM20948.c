/*
 * ICM2098.c
 *
 *  Created on: May 18, 2023
 *      Author: Kieran Shanley
 */
#include "ICM20948.h"

void ICM20948_setup(ICM20948_dev * dev, I2C_Bus * bus, uint8_t addr)
{
	dev->addr = addr;
	dev->bus = bus;
}

int32_t ICM20948_wakeup(ICM20948_dev * dev) {
	uint8_t new_val = 0;
	if(dev->bus->read(dev->addr, ICM20948_REG_B0_PWR_MGMT_1, 1, (uint8_t *)&new_val, 1) != HAL_OK)
	{
		return HAL_ERROR;
	}
	new_val &= 0xBF;
	if(dev->bus->write(dev->addr, ICM20948_REG_B0_PWR_MGMT_1, 1, (uint8_t *)&new_val, 1) != HAL_OK) {
		return HAL_ERROR;
	}
	return HAL_OK;

}
