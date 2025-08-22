#ifndef I2C_DEFINITIONS_H
#define I2C_DEFINITIONS_H

#include "sd_card_handler.h"

const uint SLAVE_ADDR = 0x26;
const uint I2C_BAUDRATE = 10000;

#define SLAVE_PORT i2c0
#define MASTER_PORT i2c1

#define I2C_SLAVE_SDA_PIN 0
#define I2C_SLAVE_SCL_PIN 1
#define I2C_MASTER_SDA_PIN 2
#define I2C_MASTER_SCL_PIN 3

typedef enum {
  READING,
  WRITING,
  READ_ERROR,
  WRITE_ERROR,
  DONE,
} SLAVE_STATE;

typedef struct {
  SLAVE_STATE type;
  Item item;
} MasterMessage;

typedef struct {
  SLAVE_STATE state;
  Item item;
} SlaveMessage;

#endif
