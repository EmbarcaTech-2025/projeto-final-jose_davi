#include "pico/stdlib.h"
#include "sd_card_handler.h" 
#include "uart_comm.h"       
#include <stdio.h>

int main() {
  stdio_init_all();
  sleep_ms(3000); // Aguarda para abrir o monitor serial

  // --- INICIALIZAÇÕES ---
  uart_comm_init(); // Inicializa a UART

  sleep_ms(5000);
  printf("BitDogLab Escrava Iniciada\n");

  AccessLog received_log;

  while (true) {
    // Tenta receber um log. A função retorna true se um log válido chegou.
    if (uart_receive_log(&received_log)) {
            
      // Um log válido foi recebido, agora vamos processá-lo
      printf("Log recebido!\n");
      printf("  Nome: %s\n", received_log.name);
      printf("  Data/Hora: %s\n", received_log.timestamp);
      printf("  Tipo: %s\n", received_log.operation);

      sleep_ms(1); // Pequena pausa para não sobrecarregar a CPU
    }
  }
  return 0;
}