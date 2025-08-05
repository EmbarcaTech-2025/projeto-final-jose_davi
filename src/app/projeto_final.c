#include "keyboard_handler.h"
#include "../include/mqtt_comm.h"
#include "../include/wifi_conn.h"
#include "../include/led_rgb.h"
#include "../include/buzzer.h"
#include "../include/display_oled.h"
#include "pico/stdio.h"
#include <stdio.h>
#include <string.h>

int main() {
  // Funções de inicialização do sistema
  stdio_init_all();
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
