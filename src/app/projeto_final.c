#include "buzzer.h"
#include "display_oled.h"
#include "led_rgb.h"
#include "mqtt_comm.h"
#include "wifi_conn.h"
#include "bh1750.h"
#include "bmp280.h"
#include "aht10.h"
#include "../include/i2c_config.h"
#include "pico/stdio.h"
#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <hardware/structs/io_bank0.h>
#include <pico/time.h>
#include <stdio.h>
#include <string.h>

int main() {
  // Funções de inicialização do sistema
  stdio_init_all();

  sleep_ms(5000);

  i2c_init(I2C_PORT, 100 * 1000);
  gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA_PIN);
  gpio_pull_up(I2C_SCL_PIN);

  // Teste sensores
  bh1750_init();
  bmp280_init();
  aht10_init();

  float lux = 0;
  float temp = 0;
  float pres = 0;
  float humidity = 0;

  while (true) {
    get_temp_pres(&temp, &pres);
    lux = get_lux();
    humidity = GetHumidity();

    printf("Temperatuta: %.2f C", temp);
    printf("Pressao: %.3f kPa", pres);
    printf("Luminosidade: %.2f lux", lux);
    printf("Umidade: %.2f %%", humidity);

    sleep_ms(1000);
  }

  keyboard_init();

  led_rgb_init();

  buzzer_init();

  display_init();

  // connect_to_wifi("Nome da Rede", "Senha da Rede");
  // mqtt_setup("bitdog1", "IP do Broker", "user", "password");

  char key_input = '?';

  while (true) {
    printf("A - Cadastro\n");
    printf("B - Retirada\n");

    memset(ssd, 0, ssd1306_buffer_length);
    ssd1306_draw_string(ssd, 5, 10, "Pressione:");
    ssd1306_draw_string(ssd, 5, 38, "A - Cadastro");
    ssd1306_draw_string(ssd, 5, 48, "B - Retirada");
    ssd1306_send_buffer(ssd, ssd1306_buffer_length);

    // Estado IDLE
    key_input = read_keyboard("AB");

    // Operação de cadastro de produto
    if (key_input == 'A') {
      printf("Cadastro\n");
      memset(ssd, 0, ssd1306_buffer_length);
      ssd1306_draw_string(ssd, 5, 38, "Cadastro");
      ssd1306_send_buffer(ssd, ssd1306_buffer_length);
      sleep_ms(2000);
    }

    // Operação de retirada de produto
    if (key_input == 'B') {
      printf("Retirada\n");
      memset(ssd, 0, ssd1306_buffer_length);
      ssd1306_draw_string(ssd, 5, 38, "Retirada");
      ssd1306_send_buffer(ssd, ssd1306_buffer_length);
      sleep_ms(2000);
    }
  }

  return 0;
}
