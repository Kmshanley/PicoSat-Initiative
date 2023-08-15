/*
 * ICM20948.h
 *
 *  Created on: May 18, 2023
 *      Author: Kieran Shanley
 */
#include "i2c.h"

#ifndef ICM20948_ICM20948_H_
#define ICM20948_ICM20948_H_

#define ICM20948_ADDR_1 0b01101000
#define ICM20948_ADDR_2 0b01101001

/* ICM-20948 Registers */
#define ICM20948_ID									0xEA
#define ICM20948_REG_BANK_SEL						0x7F

// USER BANK 0
#define ICM20948_REG_B0_WHO_AM_I 0x00
#define ICM20948_REG_B0_USER_CTRL 0x03
#define ICM20948_REG_B0_LP_CONFIG					0x05
#define ICM20948_REG_B0_PWR_MGMT_1					0x06
#define ICM20948_REG_B0_PWR_MGMT_2					0x07
#define ICM20948_REG_B0_INT_PIN_CFG					0x0F
#define ICM20948_REG_B0_INT_ENABLE					0x10
#define ICM20948_REG_B0_INT_ENABLE_1				0x11
#define ICM20948_REG_B0_INT_ENABLE_2				0x12
#define ICM20948_REG_B0_INT_ENABLE_3				0x13
#define ICM20948_REG_B0_I2C_MST_STATUS				0x17
#define ICM20948_REG_B0_INT_STATUS					0x19
#define ICM20948_REG_B0_INT_STATUS_1				0x1A
#define ICM20948_REG_B0_INT_STATUS_2				0x1B
#define ICM20948_REG_B0_INT_STATUS_3				0x1C
#define ICM20948_REG_B0_DELAY_TIMEH					0x28
#define ICM20948_REG_B0_DELAY_TIMEL					0x29
#define ICM20948_REG_B0_ACCEL_XOUT_H				0x2D
#define ICM20948_REG_B0_ACCEL_XOUT_L				0x2E
#define ICM20948_REG_B0_ACCEL_YOUT_H				0x2F
#define ICM20948_REG_B0_ACCEL_YOUT_L				0x30
#define ICM20948_REG_B0_ACCEL_ZOUT_H				0x31
#define ICM20948_REG_B0_ACCEL_ZOUT_L				0x32
#define ICM20948_REG_B0_GYRO_XOUT_H					0x33
#define ICM20948_REG_B0_GYRO_XOUT_L					0x34
#define ICM20948_REG_B0_GYRO_YOUT_H					0x35
#define ICM20948_REG_B0_GYRO_YOUT_L					0x36
#define ICM20948_REG_B0_GYRO_ZOUT_H					0x37
#define ICM20948_REG_B0_GYRO_ZOUT_L					0x38
#define ICM20948_REG_B0_TEMP_OUT_H					0x39
#define ICM20948_REG_B0_TEMP_OUT_L					0x3A
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_00		0x3B
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_01		0x3C
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_02		0x3D
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_03		0x3E
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_04		0x3F
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_05		0x40
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_06		0x41
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_07		0x42
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_08		0x43
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_09		0x44
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_10		0x45
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_11		0x46
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_12		0x47
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_13		0x48
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_14		0x49
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_15		0x4A
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_16		0x4B
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_17		0x4C
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_18		0x4D
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_19		0x4E
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_20		0x4F
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_21		0x50
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_22		0x51
#define ICM20948_REG_B0_EXT_SLV_SENS_DATA_23		0x52
#define ICM20948_REG_B0_FIFO_EN_1					0x66
#define ICM20948_REG_B0_FIFO_EN_2					0x67
#define ICM20948_REG_B0_FIFO_RST					0x68
#define ICM20948_REG_B0_FIFO_MODE					0x69
#define ICM20948_REG_B0_FIFO_COUNTH					0X70
#define ICM20948_REG_B0_FIFO_COUNTL					0X71
#define ICM20948_REG_B0_FIFO_R_W					0x72
#define ICM20948_REG_B0_DATA_RDY_STATUS				0x74
#define ICM20948_REG_B0_FIFO_CFG					0x76

// USER BANK 1
#define ICM20948_REG_B1_SELF_TEST_X_GYRO			0x02
#define ICM20948_REG_B1_SELF_TEST_Y_GYRO			0x03
#define ICM20948_REG_B1_SELF_TEST_Z_GYRO			0x04
#define ICM20948_REG_B1_SELF_TEST_X_ACCEL			0x0E
#define ICM20948_REG_B1_SELF_TEST_Y_ACCEL			0x0F
#define ICM20948_REG_B1_SELF_TEST_Z_ACCEL			0x10
#define ICM20948_REG_B1_XA_OFFS_H					0x14
#define ICM20948_REG_B1_XA_OFFS_L					0x15
#define ICM20948_REG_B1_YA_OFFS_H					0x17
#define ICM20948_REG_B1_YA_OFFS_L					0x18
#define ICM20948_REG_B1_ZA_OFFS_H					0x1A
#define ICM20948_REG_B1_ZA_OFFS_L					0x1B
#define ICM20948_REG_B1_TIMEBASE_CORRECTION_PLL		0x28

// USER BANK 2
#define ICM20948_REG_B2_GYRO_SMPLRT_DIV				0x00
#define ICM20948_REG_B2_GYRO_CONFIG_1				0x01
#define ICM20948_REG_B2_GYRO_CONFIG_2				0x02
#define ICM20948_REG_B2_XG_OFFS_USRH				0x03
#define ICM20948_REG_B2_XG_OFFS_USRL 				0x04
#define ICM20948_REG_B2_YG_OFFS_USRH				0x05
#define ICM20948_REG_B2_YG_OFFS_USRL				0x06
#define ICM20948_REG_B2_ZG_OFFS_USRH				0x07
#define ICM20948_REG_B2_ZG_OFFS_USRL				0x08
#define ICM20948_REG_B2_ODR_ALIGN_EN				0x09
#define ICM20948_REG_B2_ACCEL_SMPLRT_DIV_1			0x10
#define ICM20948_REG_B2_ACCEL_SMPLRT_DIV_2			0x11
#define ICM20948_REG_B2_ACCEL_INTEL_CTRL			0x12
#define ICM20948_REG_B2_ACCEL_WOM_THR				0x13
#define ICM20948_REG_B2_ACCEL_CONFIG				0x14
#define ICM20948_REG_B2_ACCEL_CONFIG_2				0x15
#define ICM20948_REG_B2_FSYNC_CONFIG				0x52
#define ICM20948_REG_B2_TEMP_CONFIG					0x53
#define ICM20948_REG_B2_MOD_CTRL_USR				0X54

// USER BANK 3
#define ICM20948_REG_B3_I2C_MST_ODR_CONFIG			0x00
#define ICM20948_REG_B3_I2C_MST_CTRL				0x01
#define ICM20948_REG_B3_I2C_MST_DELAY_CTRL			0x02
#define ICM20948_REG_B3_I2C_SLV0_ADDR				0x03
#define ICM20948_REG_B3_I2C_SLV0_REG				0x04
#define ICM20948_REG_B3_I2C_SLV0_CTRL				0x05
#define ICM20948_REG_B3_I2C_SLV0_DO					0x06
#define ICM20948_REG_B3_I2C_SLV1_ADDR				0x07
#define ICM20948_REG_B3_I2C_SLV1_REG				0x08
#define ICM20948_REG_B3_I2C_SLV1_CTRL				0x09
#define ICM20948_REG_B3_I2C_SLV1_DO					0x0A
#define ICM20948_REG_B3_I2C_SLV2_ADDR				0x0B
#define ICM20948_REG_B3_I2C_SLV2_REG				0x0C
#define ICM20948_REG_B3_I2C_SLV2_CTRL				0x0D
#define ICM20948_REG_B3_I2C_SLV2_DO					0x0E
#define ICM20948_REG_B3_I2C_SLV3_ADDR				0x0F
#define ICM20948_REG_B3_I2C_SLV3_REG				0x10
#define ICM20948_REG_B3_I2C_SLV3_CTRL				0x11
#define ICM20948_REG_B3_I2C_SLV3_DO					0x12
#define ICM20948_REG_B3_I2C_SLV4_ADDR				0x13
#define ICM20948_REG_B3_I2C_SLV4_REG				0x14
#define ICM20948_REG_B3_I2C_SLV4_CTRL				0x15
#define ICM20948_REG_B3_I2C_SLV4_DO					0x16
#define ICM20948_REG_B3_I2C_SLV4_DI					0x17

#define ICM20948_AK09916_REG_MAG_STATUS_1 			0x10
#define ICM20948_AK09916_REG_MAG_X_HIGH 			0x11
#define ICM20948_AK09916_REG_MAG_X_LOW 				0x12
#define ICM20948_AK09916_REG_MAG_Y_HIGH 			0x13
#define ICM20948_AK09916_REG_MAG_Y_LOW 				0x14
#define ICM20948_AK09916_REG_MAG_Z_HIGH 			0x15
#define ICM20948_AK09916_REG_MAG_Z_LOW 				0x16

typedef enum
{
	_250dps,
	_500dps,
	_1000dps,
	_2000dps
} ICM20948_gyro_full_scale;

typedef enum
{
	_2g,
	_4g,
	_8g,
	_16g
} ICM20948_accel_full_scale;

typedef enum
{
	power_down_mode = 0,
	single_measurement_mode = 1,
	continuous_measurement_10hz = 2,
	continuous_measurement_20hz = 4,
	continuous_measurement_50hz = 6,
	continuous_measurement_100hz = 8
} ICM20948_operation_mode;

typedef struct {
	I2C_Bus * bus; //Pointer to the i2c bus that this device is on
	uint8_t addr; //The I2c address of this device
	//calibration data
} ICM20948_dev;

void ICM20948_setup(ICM20948_dev * dev, I2C_Bus * bus, uint8_t addr);
int32_t ICM20948_init(ICM20948_dev * dev);
int32_t ICM20948_reset(ICM20948_dev * dev);
int32_t ICM20948_wakeup(ICM20948_dev * dev);
int32_t ICM20948_get_x_accel(ICM20948_dev * dev, float * accel);
int32_t ICM20948_get_y_accel(ICM20948_dev * dev, float * accel);
int32_t ICM20948_get_z_accel(ICM20948_dev * dev, float * accel);
int32_t ICM20948_get_x_gyro(ICM20948_dev * dev, float * gyro);
int32_t ICM20948_get_y_gyro(ICM20948_dev * dev, float * gyro);
int32_t ICM20948_get_z_gyro(ICM20948_dev * dev, float * gyro);

#endif /* ICM20948_ICM20948_H_ */
