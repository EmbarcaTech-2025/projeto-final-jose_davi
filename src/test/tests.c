#include "Unity/unity.h"
#include "Unity/unity_internals.h"
#include "keyboard_handler.h"
#include "mqtt_comm.h"
#include "wifi_conn.h"
#include "bmp280.h"
#include "bh1750.h"
#include "aht10.h"
#include "sd_card_handler.h"
#include "i2c_messages.h"
#include "../drivers/i2c_config.h"
#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void setUp(void) {
  // Inicialização do teclado matricial
  //keyboard_init();

  // Inicialização da conectividade WI-Fi com o protocolo MQTT
  //connect_to_wifi("SSID", "Senha");
  //mqtt_setup("bitdoglab_mestre", "IP do Broker", "bitdoglab_mestre", "12345678");
  //mqtt_comm_subscribe("bitdoglab_mestre/produto");

  // Inicialização para o uso dos sensores
  //i2c_init(I2C_PORT, 100 * 1000);
  //gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
  //gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
  //gpio_pull_up(I2C_SDA_PIN);
  //gpio_pull_up(I2C_SCL_PIN);

  //bmp280_init();
  //bh1750_init();  
  //aht10_init();

  i2c_init_master();

};
void tearDown(void) {};

void test_keyboard_handler(void) {
  const char ALL_KEYS[16] = {
    '1', '2', '3', 'A',
    '4', '5', '6', 'B',
    '7', '8', '9', 'C',
    '*', '0', '#', 'D'
  };
    
  char pressed_key = '?';

  sleep_ms(4000); // Um tempo para o usuário ler as instruções

  for (int i = 0; i < 16; i++) {
    char expected_key = ALL_KEYS[i];

    printf("--> Pressione e SEGURE a tecla '%c'...\n", expected_key);

    pressed_key = '?';
    while (pressed_key == '?') {
      pressed_key = get_key();
      sleep_ms(50);
    }

    TEST_ASSERT_EQUAL_CHAR(expected_key, pressed_key);
    printf("'%c' detectado com sucesso! \u2705\n", pressed_key);

    while (pressed_key != '?') {
      pressed_key = get_key();
      sleep_ms(50);
    }
  }
}

void test_wifi_mqtt(void){
  sleep_ms(4000);
  printf("Aguardando mensagem MQTT no tópico 'bitdoglab_mestre/produto'...\n");
  while (ultima_mensagem_recebida[0] == '\0') {
    sleep_ms(10);
  }
  TEST_ASSERT_EQUAL_STRING("Produto", ultima_mensagem_recebida);
  printf("Mensagem MQTT recebida com sucesso: %s \u2705\n", ultima_mensagem_recebida);
}

void test_sensors(void) {
  float lux = 0;
  float temp = 0;
  float pres = 0;
  float humidity = 0;

  get_temp_pres(&temp, &pres);
  sleep_ms(100);
  lux = get_lux();
  sleep_ms(100);
  humidity = GetHumidity();

  printf("Aguardando dados do ambiente...\n");
  sleep_ms(4000);

  // --- Teste de Temperatura ---
  TEST_ASSERT_FLOAT_WITHIN_MESSAGE(25.0, 25.0, temp, "A temperatura está fora do intervalo aceitável (0 a 50 C)");

  // --- Teste de Pressão ---
  TEST_ASSERT_FLOAT_WITHIN_MESSAGE(10.0, 97.50, pres, "A pressão está fora do intervalo aceitável (87.5 a 107.5 kPa)");

  // --- Teste de Luminosidade ---
  TEST_ASSERT_GREATER_OR_EQUAL_UINT16_MESSAGE(0, lux, "A leitura de lux não deve ser negativa.");

  humidity = GetHumidity(); // O primeiro retorno da umidade pode ser 0
  // --- Teste de Umidade ---
  TEST_ASSERT_FLOAT_WITHIN_MESSAGE(45.0, 50.0, humidity, "A umidade está fora do intervalo aceitável (5% a 95%)");
}

void test_i2c_write_and_readback(void) {
  printf("Iniciando teste de escrita e leitura I2C...\n");
  printf("Certifique-se de que o dispositivo escravo está conectado e executando o código.\n");
  sleep_ms(4000);

  Item item_to_send;
  item_to_send.code = 9999;
  item_to_send.count = 123;
  strcpy(item_to_send.name, "TesteI2C");

  // Escrever o item no escravo
  printf("--> Enviando item para o escravo: { code: %lu, count: %d, name: '%s' }\n",
    item_to_send.code, item_to_send.count, item_to_send.name);
           
  bool write_success = slave_write_item(item_to_send);

  TEST_ASSERT_TRUE_MESSAGE(write_success, "A função slave_write_item() retornou 'false'. A comunicação I2C falhou.");
  printf("Escrita I2C confirmada pelo mestre! \u2705\n");
  sleep_ms(500); // Pequeno delay para o escravo processar

  // Tenta ler o mesmo item de volta
  printf("--> Lendo o item de volta do escravo...\n");
  Item *received_item = slave_read_item(item_to_send.code);

  TEST_ASSERT_NOT_NULL_MESSAGE(received_item, "A leitura falhou. O item não foi encontrado no escravo após a escrita.");
  printf("Leitura I2C bem-sucedida! \u2705\n");

  // Compara os dados enviados com os recebidos
  printf("--> Verificando a integridade dos dados...\n");
  TEST_ASSERT_EQUAL_UINT32(item_to_send.code, received_item->code);
  TEST_ASSERT_EQUAL_INT(item_to_send.count, received_item->count);
  TEST_ASSERT_EQUAL_STRING(item_to_send.name, received_item->name);

  printf("Dados verificados com sucesso! \u2705\n");

  if (received_item != NULL) {
    free(received_item);
  }
}

int main(void) {
  stdio_init_all();
  sleep_ms(1000);
  UNITY_BEGIN();

  RUN_TEST(test_wifi_mqtt);

  UNITY_END();
}
