#include "keyboard_handler.h"
#include "../include/mqtt_comm.h"
#include "../include/wifi_conn.h"
#include "../include/led_rgb.h"
#include "../include/buzzer.h"
#include "../include/display_oled.h"
#include "pico/stdio.h"
#include "pico/time.h"
#include <stdio.h>

int main() {
  stdio_init_all();

  keyboard_init();

  led_rgb_init();
  
  buzzer_init();

  display_init();

  // connect_to_wifi("Nome da Rede", "Senha da Rede");
  // mqtt_setup("bitdog1", "IP do Broker", "user", "password");

  while (true) {
    char key = get_key();
    if (key != '?')
      printf("%c\n", key);
    sleep_ms(250);
  }

  return 0;
}
