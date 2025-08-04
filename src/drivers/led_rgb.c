// Bibliotecas necessárias
#include <stdio.h> // Biblioteca padrão
#include "pico/stdlib.h" // Biblioteca padrão pico
#include "hardware/gpio.h" // Biblioteca de GPIOs
#include "led_rgb.h" 

// Função para configuração do LED RGB
void led_rgb_init() {
  gpio_init(LED_RGB_GREEN); // Inicialização do pino do LED RGB Verde
  gpio_set_dir(LED_RGB_GREEN, GPIO_OUT); // Definição do pino como saída

  gpio_init(LED_RGB_RED); // Inicialização do pino do LED RGB Vermelho
  gpio_set_dir(LED_RGB_RED, GPIO_OUT); // Definição do pino como saída

  gpio_init(LED_RGB_BLUE); // Inicialização do pino do LED RGB Azul
  gpio_set_dir(LED_RGB_BLUE, GPIO_OUT); // Definição do pino como saída
}