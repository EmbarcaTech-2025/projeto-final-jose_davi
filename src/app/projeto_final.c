#include "keyboard_handler.h"
#include "pico/stdio.h"
#include "pico/time.h"
#include <stdio.h>

int main() {
  stdio_init_all();

  keyboard_init();

  while (true) {
    char key = get_key();
    // printf("%c\n", key);
    sleep_ms(500);
  }

  return 0;
}
