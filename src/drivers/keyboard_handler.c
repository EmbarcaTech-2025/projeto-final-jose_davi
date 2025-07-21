#include "keyboard_handler.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include <stdbool.h>
#include <stdio.h>

const uint ROW_PINS[4] = {4, 8, 9, 16};
const uint COLUMN_PINS[4] = {17, 18, 19, 20};
const char KEY_VALUES[16] = {'1', '2', '3', 'A', '4', '5', '6', 'B',
                             '7', '8', '9', 'C', '*', '0', '#', 'D'};

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
        printf("Linha %d Coluna %d = %u\n", i, j, column);
        printf("%d\n", j + (4 * i));
        return KEY_VALUES[j + (4 * i)];
      }
    }

    gpio_put(ROW_PINS[i], false);
  }

  return '?';
}
