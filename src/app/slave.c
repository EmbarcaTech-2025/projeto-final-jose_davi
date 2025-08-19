#include "definitions.h"
#include "hardware/i2c.h"
#include "pico/i2c_slave.h"
#include "pico/stdlib.h"
#include "sd_card_handler.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static const uint I2C_SLAVE_ADDRESS = 0x17;
static const uint I2C_BAUDRATE = 10000;

static const uint I2C_SLAVE_SDA_PIN = 16;
static const uint I2C_SLAVE_SCL_PIN = 17;
static const uint I2C_MASTER_SDA_PIN = 18;
static const uint I2C_MASTER_SCL_PIN = 19;

uint8_t message[58];
uint8_t address = 0;
SLAVE_STATE state = DONE;

static void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
  switch (event) {
  case I2C_SLAVE_RECEIVE:
    if (state == DONE)
      state = i2c_read_byte_raw(i2c);

    else if (state == READING) {
      message[address] = i2c_read_byte_raw(i2c);
      address = (address + 1) % 6;
    }

    else if (state == WRITING) {
      message[address] = i2c_read_byte_raw(i2c);
      address = (address + 1) % 58;
    }

    break;
  case I2C_SLAVE_REQUEST:
    // O mestre deve primeiro perguntar se a operação está pronta
    // Se sim, o escravo envia o valor 0 para o mestre
    if (state == READY) {
      state = DONE;
      i2c_write_byte_raw(i2c, 0);
    }

    // E depois o mestre pede a informação armazenada no escravo
    else if (state == DONE) {
      i2c_write_byte_raw(i2c, message[address]);
      address = (address + 1) % 58;
    }

    // Caso o arquivo não exista o escravo retorna
    // o valor 1
    else if (state == UNAVAILABLE) {
      state = DONE;
      i2c_write_byte_raw(i2c, 1);
    }

    // Caso a operação não esteja pronta o escavo envia
    // o valor 2
    else {
      i2c_write_byte_raw(i2c, 2);
    }
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

  i2c_init(i2c0, I2C_BAUDRATE);
  i2c_slave_init(i2c0, I2C_SLAVE_ADDRESS, &i2c_slave_handler);
}

int main() {
  stdio_init_all();

  sd_mount();
  setup_slave();

  while (true) {
    switch (state) {
    case READING:
      char code[6];

      memcpy(code, message, 6);

      Item *item_r = item_read(code);

      if (item_r != NULL) {
        memcpy(message, item_r->name, 50);
        memcpy(message + 50, &item_r->code, 4);
        memcpy(message + 54, &item_r->count, 4);

        free(item_r);
        state = READY;
      }

      else {
        free(item_r);
        state = UNAVAILABLE;
      }

      break;
    case WRITING:
      Item item_w;

      memcpy(item_w.name, message, 50);
      memcpy(&item_w.code, message + 50, 4);
      memcpy(&item_w.count, message + 54, 4);

      item_write(item_w);

      state = DONE;

      break;
    default:
      break;
    }
  }

  sd_unmount();

  return 0;
}
