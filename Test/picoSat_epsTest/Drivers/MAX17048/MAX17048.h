#pragma once

#define MAX17048_I2C_ADDR 0x36

#define MAX17048_VCELL 0x02
#define MAX17048_SOC 0x04
#define MAX17048_MODE 0x06
#define MAX17048_VERSION 0x08
#define MAX17048_HIBRT 0x0A
#define MAX17048_CONFIG 0x0C
#define MAX17048_VALRT 0x14
#define MAX17048_CRATE 0x16
#define MAX17048_VRESET_ID 0x18
#define MAX17048_STATUS 0x1A
#define MAX17048_TABLE 0x40
#define MAX17048_CMD 0xFE

//Max i2c clock of MAX17048 is 400kHz

typedef enum
{
    RI = (1 << 0),  // Reset indicator
    VH = (1 << 1),  // Voltage high alert
    VL = (1 << 2),  // Voltage low alert
    VR = (1 << 3),  // Voltage reset alert
    HD = (1 << 4),  // SOC low alert
    SC = (1 << 5)   // SOC change alert
} MAX17048_ALERT_t;
