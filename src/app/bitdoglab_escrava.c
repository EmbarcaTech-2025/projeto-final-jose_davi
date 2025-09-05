#include "../include/mqtt_comm.h"
#include "../include/wifi_conn.h"
#include "aht10.h"
#include "bh1750.h"
#include "bmp280.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "i2c_messages.h"
#include "pico/cyw43_arch.h"
#include "pico/i2c_slave.h"
#include "sd_card_handler.h"
#include <pico/stdio.h>
#include <pico/time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t address = 0;

uint8_t state_buf[4];
SLAVE_STATE state = DONE;

MasterMessage master_message;
uint8_t master_message_buf[64];

SlaveMessage out_message;
uint8_t out_message_buf[64];

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
    i2c_write_byte_raw(i2c, out_message_buf[address]);
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
  // i2c_slave_init(SLAVE_PORT, SLAVE_ADDRESS, &i2c_slave_handler);
}

int main() {
  stdio_init_all();
  setup_slave();

  connect_to_wifi("SSID", "Senha WiFi");
  mqtt_setup("bitdoglab_mestre", "IP do Broker", "bitdoglab_mestre",
             "12345678");

  bmp280_init();
  bh1750_init();
  aht10_init();

  float lux = 0;
  float temp = 0;
  float pres = 0;
  float humidity = 0;

  uint64_t last_publish_time = 0;

  while (true) {
    Item item;
    switch (state) {
    case READING:
      sd_mount();
      Item *item_r = item_read(master_message.item.code);

      if (item_r != NULL) {
        state = DONE;
        memcpy(&out_message.item, item_r, sizeof(Item));
        free(item_r);
      }

      else {
        state = READ_ERROR;
        free(item_r);
      }

      out_message.state = state;
      memcpy(out_message_buf, &out_message, sizeof(SlaveMessage));

      sd_unmount();
      break;
    case WRITING:
      sd_mount();
      uint bw = item_write(master_message.item);
      state = bw == sizeof(Item) ? DONE : WRITE_ERROR;
      out_message.state = state;
      memcpy(out_message_buf, &out_message, sizeof(SlaveMessage));
      sd_unmount();

      break;
    default:
      break;
    }

    // Envio de dados dos sensores
    uint64_t current_time = time_us_64() / 1000;
    if (current_time - last_publish_time > 5000) {
      last_publish_time = current_time;

      get_temp_pres(&temp, &pres);
      lux = get_lux();
      humidity = GetHumidity();

      mqqt_publish_sensor_data(temp, pres, humidity, lux);
    }
  }

  return 0;
}
