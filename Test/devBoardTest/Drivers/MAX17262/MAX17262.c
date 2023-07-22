/*
 * MAX17262.c
 *
 *  Created on: May 16, 2023
 *      Author: Kieran Shanley
 */
#include "MAX17262.h"

void MAX17262_setup(MAX17262_dev * dev, I2C_Bus * bus, uint8_t addr)
{
	dev->addr = addr;
	dev->bus = bus;
}

int32_t MAX17262_get_voltage(MAX17262_dev *dev, float * volts, bool avg) {
	return HAL_ERROR;
}
