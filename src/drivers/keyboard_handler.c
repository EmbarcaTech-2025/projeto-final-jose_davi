#include "keyboard_handler.h"
#include "hardware/gpio.h"
#include <pico/time.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

const uint ROW_PINS[4] = {4, 8, 9, 16};
const uint COLUMN_PINS[4] = {17, 18, 19, 20};
const char KEY_VALUES[16] = {'D', 'C', 'B', 'A', '#', '9', '6', '3',
                             '0', '8', '5', '2', '*', '7', '4', '1'};

void keyboard_init() {
  for (int i = 0; i < 4; i++) {
    gpio_init(ROW_PINS[i]);
    gpio_set_dir(ROW_PINS[i], GPIO_OUT);
    gpio_put(ROW_PINS[i], false);
  }

  for (int i = 0; i < 4; i++) {
    gpio_init(COLUMN_PINS[i]);
    gpio_set_dir(COLUMN_PINS[i], GPIO_IN);
    gpio_pull_down(COLUMN_PINS[i]);
  }
}

char get_key() {
  for (int i = 0; i < 4; i++) {
    gpio_put(ROW_PINS[i], true);

    for (int j = 0; j < 4; j++) {
      uint column = gpio_get(COLUMN_PINS[j]);
      if (column) {
        // printf("Linha %d Coluna %d = %u\n", i, j, column);
        // printf("%d\n", j + (4 * i));
        return KEY_VALUES[j + (4 * i)];
      }
    }

    gpio_put(ROW_PINS[i], false);
  }

  return '?';
}

char read_keyboard(char *expected) {
  char key_input = '?';
  int len = strlen(expected);

  // Ler até receber qualquer caractere caso
  // não seja esperado um caractere especifico
  if (!len) {
    while (key_input == '?') {
      key_input = get_key();
      sleep_ms(250);
    }
  }

  // Ler até receber um caractere esperado
  else {
    bool done = false;
    while (!done) {
      key_input = get_key();
      sleep_ms(250);

      for (int i = 0; i < len; i++) {
        if (key_input == expected[i]) {
          done = true;
          break;
        }
      }
    }
  }

  return key_input;
}

int read_number(int len) {
  int number = 0;

  for (int i = 0; i < len; i++) {
    int n = read_keyboard("1234567890") - '0';
    number *= 10;
    number += n;
    printf("Codigo: %d\n", number);
  }

  return number;
}

char is_number(char c) { return (c >= '0' && c <= '9'); }
