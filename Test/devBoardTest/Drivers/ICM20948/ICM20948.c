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

uint32_t ICM20948_wakeup(ICM20948_dev * dev) {
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

uint32_t ICM20948_get_x_accel(ICM20948_dev * dev, float * accelx) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B0_ACCEL_XOUT_H, 1, (uint8_t *)&data, 2) == HAL_OK)
	{
		*accelx = data/ACCEL_SENSITIVITY;
		return HAL_OK;
	}
	else {
		*accelx = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

uint32_t ICM20948_get_y_accel(ICM20948_dev * dev, float * accely) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B0_ACCEL_YOUT_H, 1, (uint8_t *)&data, 2) == HAL_OK)
	{
		*accely = data/Accel_Sensitivity;
		return HAL_OK;
	}
	else {
		*accely = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

uint32_t ICM20948_get_z_accel(ICM20948_dev * dev, float * accelz) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B0_ACCEL_ZOUT_H, 1, (uint8_t *)&data, 2) == HAL_OK)
	{
		*accelz = data/Accel_Sensitivity;
		return HAL_OK;
	}
	else {
		*accelz = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

uint32_t ICM20948_get_x_gyro(ICM20948_dev * dev, float * gyrox) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B0_GYRO_XOUT_H, 1, (uint8_t *)&data, 2) == HAL_OK)
	{
		*gyrox = data/Gyro_Sensitivity;
		return HAL_OK;
	}
	else {
		*gyrox = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

uint32_t ICM20948_get_y_gyro(ICM20948_dev * dev, float * gyroy) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B0_GYRO_YOUT_H, 1, (uint8_t *)&data, 2) == HAL_OK)
	{
		*gyroy = data/Gyro_Sensitivity;
		return HAL_OK;
	}
	else {
		*gyroy = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

uint32_t ICM20948_get_z_gyro(ICM20948_dev * dev, float * gyroz) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B0_GYRO_ZOUT_H, 1, (uint8_t *)&data, 2) == HAL_OK)
	{
		*gyroz = data/Gyro_Sensitivity;
		return HAL_OK;
	}
	else {
		*gyroz = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}
