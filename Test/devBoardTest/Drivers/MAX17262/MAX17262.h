/*
 * MAX17262.h
 *
 *  Created on: May 16, 2023
 *      Author: Kieran Shanley
 */

#include "i2c.h"
#include "stdbool.h"

#ifndef MAX17262_MAX17262_H_
#define MAX17262_MAX17262_H_

#define MAX17262_I2C_ADDR 0x36

//Parameters are for MAX17262R
#define MAX17262_CAPACITY_LSB 0.5f
#define MAX17262_PERCENTAGE_LSB 1/256
#define MAX17262_CURRENT_LSB 156.25f
#define MAX17262_TEMPERATURE_LSB 1/256
#define MAX17262_RESISTANCE 1/4096
#define MAX17262_TIME_LSB 5.625f
#define MAX17262_VOLTAGE_LSB 1.25f / 16.0f

//ModelGauge m5 EZ Configuration Registers

#define MAX17262_DESIGNCAP 0x18 //holds the nominal capacity of the cell
#define MAX17262_VEMPTY 0x3A //sets thresholds related to empty detection during operation
#define MAX17262_MODELCFG 0xDB //controls basic options of the EZ algorithm
#define MAX17262_CONFIG 0x1D
#define MAX17262_CONFIG2 0xBB

//ModelGauge m5 Algorithm Output Registers

#define MAX17262_REPCAP 0x05 //remaining capacity in mAh
#define MAX17262_REPSOC 0x06 //reported state-of-charge percentage output
#define MAX17262_FULLREPCAP 0x10 //reports the full capacity that goes with RepCap
#define MAX17262_TTE 0x11 //holds the estimated time to empty for the application under present temperature and load conditions
#define MAX17262_TTF 0x20 //holds the estimated time to full for the application under present conditions
#define MAX17262_CYCLES 0x17 //maintains a total count of the number of charge/discharge cycles of the cell
#define MAX17262_STATUS 0x00 //maintains all flags related to alert thresholds and battery insertion or removal

//Analog Measurements

#define MAX17262_VCELL 0x09 //reports the voltage measured between BATT and GND
#define MAX17262_AVGVCELL 0x19 //reports an average of the VCell register readings
#define MAX17262_MAXMINVOLT 0x1B //maintains the maximum and minimum of VCell register values since device reset

//Current Measurement

#define MAX17262_CURRENT 0x0A //uses internal current sensing to monitor the current through the SYS pin
#define MAX17262_AVGCURRENT 0x0B //reports an average of Current register readings
#define MAX17262_MAXMINCURRENT 0x1C //register maintains the maximum and minimum Current register values since the last IC reset

//Temperature Measurement

#define MAX17262_TEMP 0x08 //provides the temperature measured by the thermistor or die temperature based on the Config register setting
#define MAX17262_AVGTA 0x16 //reports an average of the readings from the Temp register
#define MAX17262_MAXMINTEMP 0x1A //maintains the maximum and minimum Temp register (08h) values since the last fuel-gauge reset
#define MAX17262_DIETEMP 0x34 //provides the internal die temperature measurement

//Power Measurement

#define MAX17262_POWER 0xB1 //Instant power calculation from immediate current and voltage. The LSB is 1.6mW
#define MAX17262_AVGPOWER 0xB3 //Filtered average power from the Power register. LSB is 1.6mW

//Alert Function

#define MAX17262_VALRTTH 0x01 //sets upper and lower limits that generate an alert if exceeded by the VCell register value
#define MAX17262_TALRTTH 0x02 //sets upper and lower limits that generate an alert if exceeded by the Temp register value
#define MAX17262_SALRTTG 0x03 //sets upper and lower limits that generate an alert if exceeded by RepSOC
#define MAX17262_IALRTTH 0xB4 //sets upper and lower limits that generate an alert if exceeded by the Current register value

//Hibernation Config
#define MAX17262_SOFTWAKEUP 0x60
#define MAX17262_HIBCFG 0xBA

typedef enum
{
    LICO = (1 << 0),  //Use for most lithium cobalt-oxide variants
    LINCR = (1 << 1),  //Use for lithium NCR or NCA cells such as Panasonic
    LIFEPO4 = (1 << 2),  //Use for lithium iron-phosphate
} MAX17262_MODELS_t;

typedef enum
{
    POR = (1 << 1),  //This bit is set to 1 when the device detects that a software or hardware POR event has occurred. This bit must be cleared by system software to detect the next POR event. POR is set to 1 at power-up
    IMN = (1 << 2),  //Minimum Current-Alert Threshold Exceeded
    BATTST = (1 << 3),  //This bit is set to 0 when a battery is present in the system, and set to 1 when the battery is absent
    IMX = (1 << 6),  //Maximum Current-Alert Threshold Exceeded
    DSOCI = (1 << 7),   //This is set to 1 whenever the RepSOC register crosses an integer percentage boundary such as 50.0%, 51.0%, etc
    VMN = (1 << 8), //Minimum Voltage-Alert Threshold Exceeded
    TMN = (1 << 9), //Minimum Temperature-Alert Threshold Exceeded
    SMN = (1 << 10), //Minimum SOC-Alert Threshold Exceeded
    BATTI = (1 << 11), //Battery Insertion
    VMX = (1 << 12), //Maximum Voltage-Alert Threshold Exceeded
    TMX = (1 << 13), //Maximum Temperature-Alert Threshold Exceeded
    SMX = (1 << 14), //Maximum SOC-Alert Threshold Exceeded
    BATTR = (1 << 15) //Battery removal
} MAX17262_STATUS_t;

typedef struct {
	I2C_Bus * bus; //Pointer to the i2c bus that this device is on
	uint8_t addr; //The I2c address of this device
} MAX17262_dev;

void MAX17262_setup(MAX17262_dev *dev, I2C_Bus * bus, uint8_t addr);
int32_t MAX17262_get_voltage(MAX17262_dev *dev, float * volts, bool avg);
int32_t MAX17262_get_soc(MAX17262_dev *dev, float * soc);
int32_t MAX17262_get_avgCurrent(MAX17262_dev *dev, float * current);
int32_t MAX17262_get_instCurrent(MAX17262_dev *dev, float * current);
int32_t MAX17262_get_remCap(MAX17262_dev *dev, float * remCap);
int32_t MAX17262_get_fullCap(MAX17262_dev *dev, float * fullCap);
int32_t MAX17262_get_avgVbat(MAX17262_dev *dev, float * avgVbat);
int32_t MAX17262_get_avgTemp(MAX17262_dev *dev, float * temp);
int32_t MAX17262_get_TTE(MAX17262_dev *dev, float * tte);
int32_t MAX17262_get_TTF(MAX17262_dev *dev, float * ttf);
int32_t MAX17262_get_cycles(MAX17262_dev *dev, float * cycles);
int32_t MAX17262_get_filteredPower(MAX17262_dev *dev, float * power);
int32_t MAX17262_get_minMaxCurrent(MAX17262_dev *dev, float * minCurrent, float * maxCurrent);
int32_t MAX17262_wakeup(MAX17262_dev *dev);
int32_t MAX17262_autoHibernate(MAX17262_dev *dev);
int32_t MAX17262_set_batt_params(MAX17262_dev *dev, uint32_t cap, float vempty, float vrecovery, uint8_t model);
int32_t MAX17262_check_POR(MAX17262_dev *dev, bool *POR);


#endif /* MAX17262_MAX17262_H_ */
