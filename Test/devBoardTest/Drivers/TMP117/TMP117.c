/*
 * TMP117.c
 *
 *  Created on: May 17, 2023
 *      Author: shanleyk
 */
#include "TMP117.h"

#define REV16_A(X) (((X) << 8) | ((X)>>8))

void TMP117_setup(TMP117_dev * dev, I2C_Bus * bus, uint8_t addr)
{
	dev->addr = addr;
	dev->bus = bus;
}

int32_t TMP117_read_temperature(TMP117_dev * dev, float * temperature) {
	int16_t data = 0;
	uint16_t addr = (dev->addr << 1) | 0x01;
	if(dev->bus->read(addr, TMP117_REG_TEMP_RESULT, 2, (uint8_t *)&data, 2) == HAL_OK)
	{
		if (data == -256) {
			//Invalid Data, TMP117 has not done a conversion yet
			return HAL_ERROR;
		}
		data = REV16_A(data); //switch byte order
		*temperature = (((float)data) * TMP117_LSB_TEMP) / 1000;
		return HAL_OK;
	}
	else
	{
		*temperature = -1;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}
