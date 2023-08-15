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

int32_t ICM20948_get_x_accel(ICM20948_dev * dev, float * accel) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B0_ACCEL_XOUT_H, 1, (uint8_t *)&new_val, 1) == HAL_OK
		&& dev->bus->read(dev->addr, ICM20948_REG_B0_ACCEL_XOUT_L, 1, (uint8_t *)&new_val, 1) == HAL_OK)
	{
		*accel = ACCEL_XOUT/Accel_Sensitivity;
		return HAL_OK;
	}
	else {
		*accel = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

int32_t ICM20948_get_y_accel(ICM20948_dev * dev, float * accel) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B0_ACCEL_YOUT_H, 1, (uint8_t *)&new_val, 1) == HAL_OK
		&& dev->bus->read(dev->addr, ICM20948_REG_B0_ACCEL_YOUT_L, 1, (uint8_t *)&new_val, 1) == HAL_OK)
	{
		*accel = ACCEL_YOUT/Accel_Sensitivity;
		return HAL_OK;
	}
	else {
		*accel = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

int32_t ICM20948_get_z_accel(ICM20948_dev * dev, float * accel) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B0_ACCEL_ZOUT_H, 1, (uint8_t *)&new_val, 1) == HAL_OK
		&& dev->bus->read(dev->addr, ICM20948_REG_B0_ACCEL_ZOUT_L, 1, (uint8_t *)&new_val, 1) == HAL_OK)
	{
		*accel = ACCEL_ZOUT/Accel_Sensitivity;
		return HAL_OK;
	}
	else {
		*accel = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

int32_t ICM20948_get_x_gyro(ICM20948_dev * dev, float * gyro) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B0_GYRO_XOUT_H, 1, (uint8_t *)&new_val, 1) == HAL_OK
		&& dev->bus->read(dev->addr, ICM20948_REG_B0_GYRO_XOUT_L, 1, (uint8_t *)&new_val, 1) == HAL_OK)
	{
		*gyro = GYRO_XOUT/Gyro_Sensitivity;
		return HAL_OK;
	}
	else {
		*gyro = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

int32_t ICM20948_get_y_gyro(ICM20948_dev * dev, float * gyro) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B0_GYRO_YOUT_H, 1, (uint8_t *)&new_val, 1) == HAL_OK
		&& dev->bus->read(dev->addr, ICM20948_REG_B0_GYRO_YOUT_L, 1, (uint8_t *)&new_val, 1) == HAL_OK)
	{
		*gyro = GYRO_YOUT/Gyro_Sensitivity;
		return HAL_OK;
	}
	else {
		*gyro = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

int32_t ICM20948_get_z_gyro(ICM20948_dev * dev, float * gyro) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B0_GYRO_ZOUT_H, 1, (uint8_t *)&new_val, 1) == HAL_OK
		&& dev->bus->read(dev->addr, ICM20948_REG_B0_GYRO_ZOUT_L, 1, (uint8_t *)&new_val, 1) == HAL_OK)
	{
		*gyro = GYRO_ZOUT/Gyro_Sensitivity;
		return HAL_OK;
	}
	else {
		*gyro = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}
