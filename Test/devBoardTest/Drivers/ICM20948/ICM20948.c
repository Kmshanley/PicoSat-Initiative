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
