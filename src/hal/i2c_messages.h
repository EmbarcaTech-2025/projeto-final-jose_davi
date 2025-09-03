#ifndef I2C_MESSAGES_H
#define I2C_MESSAGES_H

#include "sd_card_handler.h"

static const uint SLAVE_ADDRESS = 0x26;
static const uint I2C_BAUDRATE = 100 * 1000;

#define SLAVE_PORT i2c0
#define MASTER_PORT i2c0

#define I2C_SLAVE_SDA_PIN 0
#define I2C_SLAVE_SCL_PIN 1
#define I2C_MASTER_SDA_PIN 0
#define I2C_MASTER_SCL_PIN 1

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

extern void i2c_init_master();
extern Item *slave_read_item(uint32_t code);
extern bool slave_write_item(Item item);

#endif
