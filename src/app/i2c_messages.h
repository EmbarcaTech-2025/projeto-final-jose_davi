#ifndef I2C_MESSAGES_H
#define I2C_MESSAGES_H

#include "i2c_definitions.h"
#include <stdint.h>

extern Item *slave_read_item(uint32_t code);
extern bool slave_write_item(Item item);

#endif
