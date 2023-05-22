/*
 * PCA9543.h
 *
 *  Created on: May 16, 2023
 *      Author: Kieran Shanley
 */

#ifndef PCA9543_PCA9543_H_
#define PCA9543_PCA9543_H_

#include "i2c.h"

#define PCA9543_ADDR_1 0x70
#define PCA9543_ADDR_2 0b1110001
#define PCA9543_ADDR_3 0b1110010
#define PCA9543_ADDR_4 0b1110011

#define PCA9543_CHANNEL_NONE 0b00000000
#define PCA9543_CHANNEL_0 0b00000001
#define PCA9543_CHANNEL_1 0b00000010

typedef struct {
	I2C_Bus * bus; //Pointer to the i2c bus that this device is on
	uint8_t addr; //The I2c address of this device
} PCA9543_dev;

void PCA9543_setup(PCA9543_dev * dev, I2C_Bus * bus, uint8_t addr);
int32_t PCA9543_set_channel(PCA9543_dev * dev, uint8_t channel);
int32_t PCA9543_get_interrupts(PCA9543_dev dev, uint8_t * interrupts);

#endif /* PCA9543_PCA9543_H_ */
