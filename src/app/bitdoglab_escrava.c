#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "i2c_messages.h"
#include "pico/i2c_slave.h"
#include "sd_card_handler.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint8_t address = 0;

uint8_t state_buf[4];
SLAVE_STATE state = DONE;

MasterMessage master_message;
uint8_t master_message_buf[64];

SlaveMessage slave_message;
uint8_t slave_message_buf[64];

static void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
  switch (event) {
  case I2C_SLAVE_RECEIVE:
    master_message_buf[address++] = i2c_read_byte_raw(i2c);
    if (address == 64) {
      memcpy(&master_message, master_message_buf, 64);
      state = master_message.type;
      address = 0;
    }
    break;
  case I2C_SLAVE_REQUEST:
    i2c_write_byte_raw(i2c, slave_message_buf[address]);
    address = (address + 1) % 64;
    break;
  case I2C_SLAVE_FINISH: // master has signalled Stop / Restart
    address = 0;
    break;
  default:
    break;
  }
}

static void setup_slave() {
  gpio_init(I2C_SLAVE_SDA_PIN);
  gpio_set_function(I2C_SLAVE_SDA_PIN, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SLAVE_SDA_PIN);

  gpio_init(I2C_SLAVE_SCL_PIN);
  gpio_set_function(I2C_SLAVE_SCL_PIN, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SLAVE_SCL_PIN);

  i2c_init(SLAVE_PORT, I2C_BAUDRATE);
  i2c_slave_init(SLAVE_PORT, SLAVE_ADDRESS, &i2c_slave_handler);
}

int main() {
  sd_mount();
  setup_slave();

  while (true) {
    Item item;
    switch (state) {
    case READING:
      Item *item_r = item_read(master_message.item.code);

      if (item_r != NULL) {
        state = DONE;
        memcpy(&slave_message.item, item_r, sizeof(Item));
        free(item_r);
      }

      else {
        state = READ_ERROR;
        free(item_r);
      }

      slave_message.state = state;
      memcpy(slave_message_buf, &slave_message, sizeof(SlaveMessage));

      break;
    case WRITING:
      uint bw = item_write(master_message.item);
      state = bw == sizeof(Item) ? DONE : WRITE_ERROR;
      slave_message.state = state;
      memcpy(slave_message_buf, &slave_message, sizeof(SlaveMessage));

      break;
    default:
      break;
    }
  }

  sd_unmount();

  return 0;
}
