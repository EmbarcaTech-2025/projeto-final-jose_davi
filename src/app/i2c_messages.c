#include "i2c_messages.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "i2c_definitions.h"
#include <pico/time.h>
#include <stdint.h>
#include <string.h>

void i2c_init_protocol() {
  i2c_init(MASTER_PORT, I2C_BAUDRATE);

  gpio_set_function(I2C_MASTER_SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(I2C_MASTER_SCL_PIN, GPIO_FUNC_I2C);

  gpio_pull_up(I2C_MASTER_SDA_PIN);
  gpio_pull_up(I2C_MASTER_SCL_PIN);
}

uint8_t msg_buf[64];
uint8_t slave_msg_buf[64];
SlaveMessage slave_message;
const size_t msg_len = sizeof(MasterMessage);

Item *slave_read_item(uint32_t code) {
  Item item = {
      "",
      code,
      0,
  };
  MasterMessage message = {
      READING,
      item,
  };

  memcpy(msg_buf, &message, sizeof(MasterMessage));
  i2c_write_blocking(MASTER_PORT, SLAVE_ADDR, msg_buf, msg_len, false);

  sleep_us(100);

  while (true) {
    i2c_read_blocking(MASTER_PORT, SLAVE_ADDR, slave_msg_buf, msg_len, false);
    memcpy(&slave_message, slave_msg_buf, msg_len);
    if (slave_message.state == DONE)
      return &slave_message.item;
    else if (slave_message.state == READ_ERROR)
      return NULL;
    else
      sleep_us(100);
  }
}

bool slave_write_item(Item item) {
  MasterMessage message = {
      READING,
      item,
  };

  memcpy(msg_buf, &message, sizeof(MasterMessage));
  i2c_write_blocking(MASTER_PORT, SLAVE_ADDR, msg_buf, msg_len, false);
  sleep_us(100);

  while (true) {
    i2c_read_blocking(MASTER_PORT, SLAVE_ADDR, slave_msg_buf, msg_len, false);
    memcpy(&slave_message, slave_msg_buf, msg_len);
    if (slave_message.state == DONE)
      return true;
    else if (slave_message.state == WRITE_ERROR)
      return false;
    else
      sleep_us(100);
  }
}
