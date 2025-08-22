#include "../include/mqtt_comm.h"
#include "../include/wifi_conn.h"
#include "i2c_messages.h"
#include "keyboard_handler.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>

int main() {
  stdio_init_all();
  i2c_init_master();
  connect_to_wifi("SSID", "Senha");

  // Criar arquivo passw.txt com usuário "bitdoglab_mestre" e senha "12345678"
  mqtt_setup("bitdoglab_mestre", "IP do Broker", "bitdoglab_mestre",
             "12345678");
  mqtt_comm_subscribe("bitdoglab_mestre/produto");

  keyboard_init();

  while (ultima_mensagem_recebida[0] == '\0') {
    sleep_ms(10);
  }

  printf("Produto Recebido\n");

  char numbers_typed[5];
  int i = 0;

  char tecla_pressionada;
  while ((tecla_pressionada = get_key()) != 'A') {
    if (is_number(tecla_pressionada)) {
      // Checagem de segurança para não estourar o buffer
      if (i < 4) {
        printf("Tecla pressionada: %c\n", tecla_pressionada);
        numbers_typed[i] = tecla_pressionada;
        i++;
      }
    }
    // Adicionar um pequeno delay é uma boa prática
    sleep_ms(200);
  }

  int product_quantity = 0;

  for (int j = 0; j < i; j++) {
    product_quantity = product_quantity * 10 + (numbers_typed[j] - '0');
  }

  printf("Quantidade Registrada\n");

  // B: Cadastro
  // C: Retirada
  char addition_or_removal = read_keyboard("BC");

  if (addition_or_removal == 'B') {
    printf("Operação: Cadastro, ");
    printf("Quantidade do produto: %i e Tipo do Produto: %s", product_quantity,
           ultima_mensagem_recebida);
  } else if (addition_or_removal == 'C') {
    printf("Operação: Retirada, ");
    printf("Quantidade do produto: %i e Tipo do Produto: %s", product_quantity,
           ultima_mensagem_recebida);
  }

  printf("Mensgaem enviada");
}
