/*
 * INA236.c
 *
 *  Created on: May 13, 2023
 *      Author: Kieran Shanley
 */
#include "INA236.h"

void INA236_setup(INA236_dev * dev, I2C_Bus * bus, uint8_t addr)
{
	dev->addr = addr;
	dev->bus = bus;
}

int32_t INA236_trigger_measurement(INA236_dev * dev)
{
	uint16_t data = INA236_operating_mode_triggered_bus_and_shunt_voltage;
	if(dev->bus->write(dev->addr, INA236_REG_SIZE, INA236_REG_CONFIG, (uint8_t *)&data, sizeof(data)) == HAL_OK)
	{
		return HAL_OK;
	}
	else {
		return HAL_ERROR;
	}
}

int32_t INA236_get_power(INA236_dev * dev, float * power)
{
	uint16_t data = 0;
	if(dev->bus->read(dev->addr, INA236_REG_SIZE, INA236_REG_POWER, (uint8_t *)&data, sizeof(data)) == HAL_OK)
	{
		*power = (float)data * INA236_LSB_CURRENT * 32.0f;
		return HAL_OK;
	}
	else {
		*power = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

int32_t INA236_get_current(INA236_dev * dev, float * current)
{
	uint16_t data = 0;
	if(dev->bus->read(dev->addr, INA236_REG_SIZE, INA236_REG_CURRENT, (uint8_t *)&data, sizeof(data)) == HAL_OK)
	{
		*current = (float)data * INA236_LSB_CURRENT;
		return HAL_OK;
	}
	else {
		*current = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

int32_t INA236_get_shunt_voltage(INA236_dev * dev, float * voltage)
{
	int16_t data = 0;
	if(dev->bus->read(dev->addr, INA236_REG_SIZE, INA236_REG_SHUNT_VOLTAGE, (uint8_t *)&data, sizeof(data)) == HAL_OK)
	{
		*voltage = (float)data * INA236_LSB_SHUNT_VOLTAGE;
		return HAL_OK;
	}
	else {
		*voltage = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

int32_t INA236_get_bus_voltage(INA236_dev * dev, float * voltage)
{
	int16_t data = 0;
	if(dev->bus->read(dev->addr, INA236_REG_SIZE, INA236_REG_BUS_VOLTAGE, (uint8_t *)&data, sizeof(data)) == HAL_OK)
	{
		*voltage = (float)data * INA236_LSB_BUS_VOLTAGE;
		return HAL_OK;
	}
	else {
		*voltage = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}
