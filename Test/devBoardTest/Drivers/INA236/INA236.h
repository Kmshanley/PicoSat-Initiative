/**
  ******************************************************************************
  * @file    INA236.h
  * @brief   This file contains all the function prototypes for
  *          the INA236.c file
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  *  Created on: May 13, 2023
  *      Author: Kieran Shanley
  */
#ifndef INA236_INA236_H_
#define INA236_INA236_H_

#include "i2c.h"

#define INA236_ADDR_1 0b1000000 //GND
#define INA236_ADDR_2 0b1000001 //VS
#define INA236_ADDR_3 0b1000010 //SDA
#define INA236_ADDR_4 0b1000011 //SCL

#define INA236_REG_CONFIG 0x00
#define INA236_REG_SHUNT_VOLTAGE 0x01
#define INA236_REG_BUS_VOLTAGE 0x02
#define INA236_REG_POWER 0x03
#define INA236_REG_CURRENT 0x04
#define INA236_REG_CALIBRATION 0x05
#define INA236_REG_MASK 0x06
#define INA236_REG_ALERT_LIMIT 0x07
#define INA236_REG_MANU_ID 0x3E
#define INA236_REG_DEV_ID 0x3F

#define INA236_LSB_CURRENT 500 // µA/LSB
#define INA236_LSB_BUS_VOLTAGE 1.6f //mV/LSB
#define INA236_LSB_SHUNT_VOLTAGE 2.5f //µV/LSB
#define INA236_LSB_ALERT_LIMIT 2.5f //μV/LSB

#define INA236_REG_SIZE I2C_MEMADD_SIZE_16BIT //all INA236 registers are 16bits

typedef struct {
	I2C_Bus * bus; //Pointer to the i2c bus that this device is on
	uint8_t addr; //The I2c address of this device
} INA236_dev;

typedef enum {
	INA236_operating_mode_shutdown = 0b000,
	INA236_operating_mode_triggered_shunt_voltage = 0b001,
	INA236_operating_mode_triggered_bus_voltage = 0b010,
	INA236_operating_mode_triggered_bus_and_shunt_voltage = 0b011,
	INA236_operating_mode_shutdownAlt = 0b100,
	INA236_operating_mode_continuous_shunt_voltage = 0b101,
	INA236_operating_mode_continuous_bus_voltage = 0b110,
	INA236_operating_mode_continuous_bus_and_shunt_voltage = 0b111,
} INA236_operating_modes;

typedef enum {
	INA236_ADC_1_AVG = 0b000,
	INA236_ADC_4_AVG = 0b001,
	INA236_ADC_16_AVG = 0b010,
	INA236_ADC_64_AVG =  0b011,
	INA236_ADC_128_AVG = 0b100,
	INA236_ADC_256_AVG = 0b101,
	INA236_ADC_512_AVG = 0b110,
	INA236_ADC_1024_AVG = 0b111,
} INA236_adc_conversion_averages;

void INA236_setup(INA236_dev * dev, I2C_Bus * bus, uint8_t addr);
int32_t INA236_trigger_measurement(INA236_dev * dev);
int32_t INA236_get_power(INA236_dev * dev, float * power);
int32_t INA236_get_current(INA236_dev * dev, float * current);
int32_t INA236_get_shunt_voltage(INA236_dev * dev, float * voltage);
int32_t INA236_get_bus_voltage(INA236_dev * dev, float * voltage);
int32_t INA236_read_manuID(INA236_dev * dev, uint16_t * id);

#endif /* INA236_INA236_H_ */
