#include "keyboard_handler.h"
#include "pico/stdio.h"
#include <stdio.h>

int main() {
  // Funções de inicialização do sistema
  stdio_init_all();
  keyboard_init();

  char key_input = '?';

  while (true) {
    printf("A - Cadastro\n");
    printf("B - Retirada\n");

    // Estado IDLE
    key_input = read_keyboard("AB");

    // Operação de cadastro de produto
    if (key_input == 'A') {
      printf("Cadastro\n");
    }

    // Operação de retirada de produto
    if (key_input == 'B') {
      printf("Retirada\n");
    }
  }

  return 0;
}
