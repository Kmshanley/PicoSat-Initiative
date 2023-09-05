/*
 * ICM2098.c
 *
 *  Created on: May 18, 2023
 *      Authors: Kieran Shanley & Thomas O'Leary
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

uint32_t ICM20948_get_x_accel(ICM20948_dev * dev, float * accelx, uint16_t * accel_sens) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B0_ACCEL_XOUT_H, 1, (uint8_t *)&data, 2) == HAL_OK)
	{
		*accelx = (float)(data / *accel_sens);
		return HAL_OK;
	}
	else {
		*accelx = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

uint32_t ICM20948_get_y_accel(ICM20948_dev * dev, float * accely, uint16_t * accel_sens) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B0_ACCEL_YOUT_H, 1, (uint8_t *)&data, 2) == HAL_OK)
	{
		*accely = (float)(data / *accel_sens);
		return HAL_OK;
	}
	else {
		*accely = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

uint32_t ICM20948_get_z_accel(ICM20948_dev * dev, float * accelz, uint16_t * accel_sens) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B0_ACCEL_ZOUT_H, 1, (uint8_t *)&data, 2) == HAL_OK)
	{
		*accelz = (float)(data / *accel_sens);
		return HAL_OK;
	}
	else {
		*accelz = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

uint32_t ICM20948_get_x_gyro(ICM20948_dev * dev, float * gyrox, uint16_t * gyro_sens) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B0_GYRO_XOUT_H, 1, (uint8_t *)&data, 2) == HAL_OK)
	{
		*gyrox = (float)(data / *gyro_sens);
		return HAL_OK;
	}
	else {
		*gyrox = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

uint32_t ICM20948_get_y_gyro(ICM20948_dev * dev, float * gyroy, uint16_t * gyro_sens) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B0_GYRO_YOUT_H, 1, (uint8_t *)&data, 2) == HAL_OK)
	{
		*gyroy = (float)(data / *gyro_sens);
		return HAL_OK;
	}
	else {
		*gyroy = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

uint32_t ICM20948_get_z_gyro(ICM20948_dev * dev, float * gyroz, uint16_t * gyro_sens) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B0_GYRO_ZOUT_H, 1, (uint8_t *)&data, 2) == HAL_OK)
	{
		*gyroz = (float)(data / *gyro_sens);
		return HAL_OK;
	}
	else {
		*gyroz = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

void ICM20948_set_gyro_sens(ICM20948_dev * dev, uint16_t gyro_sens) {
	uint8_t data = 0;
	switch (gyro_sens) {
	case _250dps: //sets gyro sensitivity to 250 dps
		dev->bus->read(dev->addr, ICM20948_REG_B2_GYRO_CONFIG_1, 1, (uint8_t *)&data, 1);
		data &= 0b11111001; //sets first and second bit to 00
		dev->bus->write(dev->addr, sizeof(data), ICM20948_REG_B2_GYRO_CONFIG_1, (uint8_t *)&data, sizeof(data));
		break;
	case _500dps: //sets gyro sensitivity to 500 dps
		dev->bus->read(dev->addr, ICM20948_REG_B2_GYRO_CONFIG_1, 1, (uint8_t *)&data, 1);
		data &= 0b11111001;
		data |= 0b00000010; //sets first and second bit to 01
		dev->bus->write(dev->addr, sizeof(data), ICM20948_REG_B2_GYRO_CONFIG_1, (uint8_t *)&data, sizeof(data));
		break;
	case _1000dps: //sets gyro sensitivity to 1000 dps
		dev->bus->read(dev->addr, ICM20948_REG_B2_GYRO_CONFIG_1, 1, (uint8_t *)&data, 1);
		data &= 0b11111001;
		data |= 0b00000100; //sets first and second bit to 10
		dev->bus->write(dev->addr, sizeof(data), ICM20948_REG_B2_GYRO_CONFIG_1, (uint8_t *)&data, sizeof(data));
		break;
	case _2000dps: //sets gyro sensitivity to 2000 dps
		dev->bus->read(dev->addr, ICM20948_REG_B2_GYRO_CONFIG_1, 1, (uint8_t *)&data, 1);
		data &= 0b11111001;
		data |= 0b00000110; //sets first and second bit to 11
		dev->bus->write(dev->addr, sizeof(data), ICM20948_REG_B2_GYRO_CONFIG_1, (uint8_t *)&data, sizeof(data));
		break;
	}
}

uint32_t ICM20948_get_gyro_sens(ICM20948_dev * dev, uint16_t * gyro_sens) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B2_GYRO_CONFIG_1, 1, (uint8_t *)&data, 1) == HAL_OK)
	{
		data &= 0b00000110;
		data = data >> 1;
		*gyro_sens = data;
		return HAL_OK;
	}
	else {
		*gyro_sens = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}

void ICM20948_set_accel_sens(ICM20948_dev * dev, uint16_t accel_sens) {
	uint8_t data = 0;
	switch (accel_sens) {
	case _2g: //sets gyro sensitivity to 250 dps
		dev->bus->read(dev->addr, ICM20948_REG_B2_ACCEL_CONFIG, 1, (uint8_t *)&data, 1);
		data &= 0b11111001; //sets first and second bit to 00
		dev->bus->write(dev->addr, sizeof(data), ICM20948_REG_B2_ACCEL_CONFIG, (uint8_t *)&data, sizeof(data));
		break;
	case _4g: //sets gyro sensitivity to 500 dps
		dev->bus->read(dev->addr, ICM20948_REG_B2_ACCEL_CONFIG, 1, (uint8_t *)&data, 1);
		data &= 0b11111001;
		data |= 0b00000010; //sets first and second bit to 01
		dev->bus->write(dev->addr, sizeof(data), ICM20948_REG_B2_ACCEL_CONFIG, (uint8_t *)&data, sizeof(data));
		break;
	case _8g: //sets gyro sensitivity to 1000 dps
		dev->bus->read(dev->addr, ICM20948_REG_B2_ACCEL_CONFIG, 1, (uint8_t *)&data, 1);
		data &= 0b11111001;
		data |= 0b00000100; //sets first and second bit to 10
		dev->bus->write(dev->addr, sizeof(data), ICM20948_REG_B2_ACCEL_CONFIG, (uint8_t *)&data, sizeof(data));
		break;
	case _16g: //sets gyro sensitivity to 2000 dps
		dev->bus->read(dev->addr, ICM20948_REG_B2_ACCEL_CONFIG, 1, (uint8_t *)&data, 1);
		data &= 0b11111001;
		data |= 0b00000110; //sets first and second bit to 11
		dev->bus->write(dev->addr, sizeof(data), ICM20948_REG_B2_ACCEL_CONFIG, (uint8_t *)&data, sizeof(data));
		break;
	}
}

uint32_t ICM20948_get_accel_sens(ICM20948_dev * dev, uint16_t * accel_sens) {
	uint8_t data = 0;
	if	(dev->bus->read(dev->addr, ICM20948_REG_B2_ACCEL_CONFIG, 1, (uint8_t *)&data, 1) == HAL_OK)
	{
		data &= 0b00000110;
		data = data >> 1;
		*accel_sens = data;
		return HAL_OK;
	}
	else {
		*accel_sens = 0;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}
