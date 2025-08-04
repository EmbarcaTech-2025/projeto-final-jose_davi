// Bibliotecas necessárias
#include <stdio.h> // Biblioteca padrão
#include "pico/stdlib.h" // Biblioteca padrão pico
#include "hardware/pwm.h" // Biblioteca de PWM 
#include "hardware/gpio.h" // Biblioteca de GPIOs
#include "buzzer.h" 

// Função para configuração do PWM do buzzer
void buzzer_init(){
  // Identifica qual "slice" de PWM está conectado ao pino do buzzer
  uint slice = pwm_gpio_to_slice_num(BUZZER_PIN);

  // Configura o pino do buzzer para a função de PWM
  gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM); 
  
  // Define o divisor de clock do PWM. Um valor baixo como 1.0f aumenta a frequência 
  // do PWM para fora da faixa audível, melhorando a qualidade do som.
  pwm_set_clkdiv(slice, 1.0f);  

  pwm_set_wrap(slice, 62500);

  // Define o nível inicial do canal (duty cycle) para 0.
  pwm_set_chan_level(slice, pwm_gpio_to_channel(BUZZER_PIN), 0);

  // Ativa o PWM
  pwm_set_enabled(slice, true);
}

void play_buzzer() {
  pwm_set_gpio_level(BUZZER_PIN, 5000); // Liga o buzzer 

  sleep_ms(1500); // Toca por 1 segundo

  pwm_set_gpio_level(BUZZER_PIN, 0); // Desliga o buzzer
}