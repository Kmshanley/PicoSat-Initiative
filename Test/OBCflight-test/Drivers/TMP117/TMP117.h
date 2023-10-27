/*
 * TMP117.h
 *
 *  Created on: May 17, 2023
 *      Author: shanleyk
 */
#include "i2c.h"

#ifndef TMP117_TMP117_H_
#define TMP117_TMP117_H_

#define TMP117_ADDR_1 0b1001000
#define TMP117_ADDR_2 0b1001001
#define TMP117_ADDR_3 0b1001010
#define TMP117_ADDR_4 0b1001011

#define TMP117_REG_TEMP_RESULT 0x00
#define TMP117_REG_CONFIGURATION 0x01
#define TMP117_REG_THIGH_LIMIT 0x02
#define TMP117_REG_TLOW_LIMIT 0x03
#define TMP117_REG_EEPROM_UL 0x04
#define TMP117_REG_EEPROM_1 0x05
#define TMP117_REG_EEPROM_2 0x06
#define TMP117_REG_TEMP_OFFSET 0x07
#define TMP117_REG_EEPROM_3 0x08
#define TMP117_REG_DEVICE_ID 0x0F

#define TMP117_LSB_TEMP 7.8125f

typedef struct {
	I2C_Bus * bus; //Pointer to the i2c bus that this device is on
	uint8_t addr; //The I2c address of this device
} TMP117_dev;

void TMP117_setup(TMP117_dev * dev, I2C_Bus * bus, uint8_t addr);
int32_t TMP117_set_configuration(TMP117_dev * dev);
int32_t TMP117_read_temperature(TMP117_dev * dev, float * temperature);

#endif /* TMP117_TMP117_H_ */
