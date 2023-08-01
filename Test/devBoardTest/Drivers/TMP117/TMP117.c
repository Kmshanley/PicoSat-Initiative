/*
notes

the first bit in the 16-bit register is to determine negative values with 1 being negative and a register filled with "ones" is almost zero
next step is to turn the 15 bit register to the actual value

unable to test capability with negative temperatures

Touching the sensor has a high likelyhood of glitching values but still functions in terms of changing degrees

 */
#include "TMP117.h"

#define REV16_A(X) (((X) << 8) | ((X)>>8)) //16

void TMP117_setup(TMP117_dev * dev, I2C_Bus * bus, uint8_t addr)
{
	dev->addr = addr;
	dev->bus = bus;
}

int32_t TMP117_read_temperature(TMP117_dev * dev, float * temperature) {
	int16_t data = 0;
	uint16_t addr = (dev->addr << 1) | 0x01;
	int TMP117_RESOLUTION = .1;

	int16_t _offset = 0;
	//_offset = TMP117_REG_TEMP_OFFSET;				// Reads from the temperature offset register
	float finalOffset = (float)_offset * TMP117_RESOLUTION; // Multiplies by the resolution for correct offset temperature

	int16_t resolutionOffset = _offset / TMP117_RESOLUTION; // Divides by the resolution to send the correct value to the sensor
	//TMP117_REG_TEMP_OFFSET, resolutionOffset;   // Writes to the offset temperature register with the new offset value
	//TMP117_REG_TEMP_OFFSET = *resolutionOffset;


	if(dev->bus->read(addr, TMP117_REG_TEMP_RESULT, 2, (uint8_t *)&data, 2) == HAL_OK)
	{
		if (data == -256) {
			//Invalid Data, TMP117 has not done a conversion yet
			return HAL_ERROR;
		}
		data = REV16_A(data); //switch byte order
		*temperature = (((float)data) * TMP117_LSB_TEMP * 0.00078125);
		//log_info("float data :%d", data);
		//log_info("tmp lsb:%p", TMP117_LSB_TEMP);
		return HAL_OK;
	}
	else
	{
		*temperature = -1;
		return HAL_ERROR;
	}
	return HAL_ERROR;
}
