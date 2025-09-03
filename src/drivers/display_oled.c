// Bibliotecas necessárias
#include <stdio.h> // Biblioteca padrão
#include <string.h> // Biblioteca para manipulação de strings
#include "pico/stdlib.h" // Biblioteca padrão pico
#include "hardware/gpio.h" // Biblioteca de GPIOs
#include "../include/display_oled.h" // Header do LED RGB

uint8_t ssd[ssd1306_buffer_length]; // Buffer do display OLED

struct render_area frame_area; // Estrutura que define uma área de renderização

void display_init(){
  // Configuração do display OLED
  i2c_init(i2c1, ssd1306_i2c_clock * 1000);

  // Definição dos pinos SDA e SCL
  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);

  // Ativação do pull-up
  gpio_pull_up(I2C_SDA);
  gpio_pull_up(I2C_SCL);

  // Inicialização do display OLED
  ssd1306_init();

  // Limpeza do buffer do display
  memset(ssd, 0, ssd1306_buffer_length);
}

void draw_centered_string(uint8_t* buffer, int y, char* text) {
  const int FONT_CHAR_WIDTH = 8; 

  int text_len = strlen(text);
  int text_width = text_len * FONT_CHAR_WIDTH;

  int x = (DISPLAY_WIDTH - text_width) / 2;

  if (x < 0) {
    x = 0;
  }

  ssd1306_draw_string(buffer, x, y, text);
}