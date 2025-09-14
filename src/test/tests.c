#include "Unity/unity.h"
#include "Unity/unity_internals.h"
#include "mqtt_comm.h"
#include "wifi_conn.h"
#include "bmp280.h"
#include "bh1750.h"
#include "aht10.h"
#include "../include/i2c_config.h"
#include "current_time.h"
#include "uart_comm.h"
#include "mfrc522.h"
#include "sd_card_handler.h"
#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Funções de Configuração e Finalização dos Testes
// Para cada teste, descomente a inicialização necessária
void setUp(void) {
  // Inicialização da conectividade WI-Fi com o protocolo MQTT (test_wifi_mqtt)

  //connect_to_wifi("UFC-MMA", "05142029");
  //mqtt_setup("bitdoglab_escravo", "192.168.0.146", "bitdoglab_escravo", "12345678");
  //mqtt_comm_subscribe("bitdoglab_escravo/teste");

//-----------------------------------------------------------------------------------------
  // Inicialização para o uso dos sensores (test_sensors)

  //i2c_init(I2C_PORT, 100 * 1000);
  //gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
  //gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
  //gpio_pull_up(I2C_SDA_PIN);
  //gpio_pull_up(I2C_SCL_PIN);

  //bmp280_init();
  //bh1750_init();  
  //aht10_init();

//-----------------------------------------------------------------------------------------
  // Inicialização do para uso do protocolo NTP (test_ntp)

  //setup_rtc_from_ntp();

//-----------------------------------------------------------------------------------------
  // Inicialização para uso do protocolo UART (test_uart)

  //uart_comm_init();

//-----------------------------------------------------------------------------------------
  // Inicialização para uso do módulo RFID MFRC522 (test_rfid)

  //spi_init(spi0, MFRC522_BIT_RATE);
  //gpio_set_function(miso_pin, GPIO_FUNC_SPI);
  //gpio_set_function(sck_pin, GPIO_FUNC_SPI);
  //gpio_set_function(mosi_pin, GPIO_FUNC_SPI);

//-----------------------------------------------------------------------------------------
  // Inicialização para o controle da fechadura eletrônica (test_fechadura)

  gpio_init(4);
  gpio_set_dir(4, GPIO_OUT);
};
void tearDown(void) {};

//-----------------------------------------------------------------------------------------
// Funções de Teste

// Teste da conectividade Wi-Fi e do protocolo MQTT
void test_wifi_mqtt(void){
  sleep_ms(4000);
  printf("Enviando mensagem MQTT ao tópico\n");
  mqtt_comm_publish("bitdoglab_escravo/teste", (uint8_t *)"Teste", strlen("Teste"));
  printf("Aguardando mensagem MQTT no tópico 'bitdoglab_escravo/teste'...\n");
  while (ultima_mensagem_recebida[0] == '\0') {
    sleep_ms(10);
  }
  TEST_ASSERT_EQUAL_STRING("Teste", ultima_mensagem_recebida);
  printf("Mensagem MQTT recebida com sucesso: %s \u2705\n", ultima_mensagem_recebida);
}

// Teste dos sensores BMP280, BH1750 e AHT10
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

// Teste do protocolo NTP para obtenção do horário atual
void test_ntp(void) {
  printf("Iniciando teste do NTP...\n");
  char timestamp[20];
  get_current_timestamp_str(timestamp, sizeof(timestamp));
  printf("Timestamp atual: %s\n", timestamp);
  // Verifica se o timestamp não é uma string vazia
  TEST_ASSERT_NOT_EQUAL(0, strcmp("RTC nao sincronizado", timestamp));
}

// Teste do protocolo UART para recepção de logs de acesso
void test_uart(void) {
  sleep_ms(2000);
  AccessLog received_log;
  printf("Iniciando teste do UART...\n");
  printf("Aguardando log via UART...\n");
  while(uart_receive_log(&received_log) == false);
  printf("\n[UART] Log recebido via UART:\n");
  printf("  -> Nome: %s, Op: %s, Time: %s\n", received_log.name, received_log.operation, received_log.timestamp);
  TEST_ASSERT_TRUE_MESSAGE(true, "Log recebido via UART com sucesso.");
}

// Teste do módulo RFID MFRC522
void test_rfid(void) {
  const uint8_t START_BLOCK = 4;

  MFRC522Ptr_t mfrc = MFRC522_Init();
  PCD_Init(mfrc, spi0);

  // Dados Esperados
  const char* EXPECTED_NAME = "Davi Henrique Vieira Lima";
  const char* EXPECTED_CPF = "123.456.789-00";

  sleep_ms(2000);

  printf("Teste do RFID\n");
  printf("Aproxime o Cartão...\n");

  // Aguarda a apresentação de um novo cartão
  while (!PICC_IsNewCardPresent(mfrc));
  printf("Cartao detectado!\n");

  // Seleciona o cartão e lê seu UID
  TEST_ASSERT_TRUE_MESSAGE(PICC_ReadCardSerial(mfrc), "Falha ao ler o serial do cartao (UID).");
    
  // Valida o UID lido
  printf("UID Lido: ");
  for (int i = 0; i < mfrc->uid.size; i++) {
    printf("%02X ", mfrc->uid.uidByte[i]);
  }
  printf("\n");
  TEST_ASSERT_GREATER_THAN_UINT8(0, mfrc->uid.size); 

  // Autentica o primeiro bloco de dados para ler o tamanho do payload
  MIFARE_Key key;
  for (uint8_t k = 0; k < MF_KEY_SIZE; k++) {
    key.keybyte[k] = 0xFF; 
  }
    
  StatusCode status = PCD_Authenticate(mfrc, PICC_CMD_MF_AUTH_KEY_A, START_BLOCK, &key, &(mfrc->uid));
  TEST_ASSERT_EQUAL_INT_MESSAGE(STATUS_OK, status, "Falha ao autenticar o bloco inicial.");

  // Lê o primeiro bloco para descobrir o tamanho total dos dados
  uint8_t first_block_buffer[18];
  uint8_t bufferSize = sizeof(first_block_buffer);
  status = MIFARE_Read(mfrc, START_BLOCK, first_block_buffer, &bufferSize);
  TEST_ASSERT_EQUAL_INT_MESSAGE(STATUS_OK, status, "Falha ao ler o bloco inicial.");
    
  uint8_t total_payload_len = first_block_buffer[0];
  TEST_ASSERT_GREATER_THAN_UINT8_MESSAGE(0, total_payload_len, "Cartao parece estar vazio (tamanho do payload e 0).");
  TEST_ASSERT_LESS_THAN_UINT8_MESSAGE(128, total_payload_len, "Tamanho do payload e invalido (muito grande).");
  printf("Tamanho total do payload a ser lido: %d bytes\n", total_payload_len);

  // Lê os blocos restantes e reconstrói o payload
  uint8_t reconstructed_payload[total_payload_len];
  int bytes_read = 15;
  memcpy(reconstructed_payload, &first_block_buffer[1], bytes_read);

  int blocks_to_read_more = (int)ceil((float)(total_payload_len - 15) / 16.0);
  uint8_t current_block = START_BLOCK + 1;

  for (int i = 0; i < blocks_to_read_more; i++) {
    while ((current_block + 1) % 4 == 0) {
      current_block++;
    }

    status = PCD_Authenticate(mfrc, PICC_CMD_MF_AUTH_KEY_A, current_block, &key, &(mfrc->uid));
    TEST_ASSERT_EQUAL_INT_MESSAGE(STATUS_OK, status, "Falha ao autenticar bloco de dados adicional.");

    uint8_t block_buffer[18];
    bufferSize = sizeof(block_buffer);
    status = MIFARE_Read(mfrc, current_block, block_buffer, &bufferSize);
    TEST_ASSERT_EQUAL_INT_MESSAGE(STATUS_OK, status, "Falha ao ler bloco de dados adicional.");

    int bytes_to_copy = total_payload_len - bytes_read;
    if (bytes_to_copy > 16){
      bytes_to_copy = 16;
    } 

    memcpy(&reconstructed_payload[bytes_read], block_buffer, bytes_to_copy);
    bytes_read += bytes_to_copy;
    current_block++;
  }

  TEST_ASSERT_EQUAL_INT_MESSAGE(total_payload_len, bytes_read, "O numero de bytes lidos nao corresponde ao esperado.");
  printf("Payload reconstruido com sucesso!\n");

  // Extração do CPF e do Nome do payload
  char* cpf = (char*)reconstructed_payload;
  char* nome = cpf + strlen(cpf) + 1;

  printf("Verificando os dados lidos...\n");
  printf("  -> CPF Lido: %s\n", cpf);
  printf("  -> Nome Lido: %s\n", nome);
    
  TEST_ASSERT_EQUAL_STRING(EXPECTED_CPF, cpf);
  TEST_ASSERT_EQUAL_STRING(EXPECTED_NAME, nome);

  printf("Dados validados com SUCESSO!\n");

  PICC_HaltA(mfrc);
  PCD_StopCrypto1(mfrc);
}

// Teste do controle da fechadura eletrônica
void test_fechadura(void){
  sleep_ms(2000);
  printf("Teste da fechadura eletrônica\n");
  printf("Fechadura aberta por 3 segundos...\n");
  gpio_put(4, 0); // Abre a fechadura 
  sleep_ms(3000);
  gpio_put(4, 1); // Fecha a fechadura 
  printf("Fechadura fechada.\n");
}

// Teste do Cartão SD para escrita e leitura de dados
void test_sd_card(void) {
  sleep_ms(2000);
  printf("Iniciando teste de escrita de log no Cartao SD...\n");

  TEST_ASSERT_TRUE_MESSAGE(sd_mount(), "Falha ao montar o cartao SD.");
  printf("Cartao SD montado com sucesso.\n");

  AccessLog log_para_escrever = {
    .name = "Usuario Teste",
    .operation = "Entrada",
    .timestamp = "14/09/25 16:31:48" 
  };

  printf("Escrevendo log de acesso no cartao...\n");
  uint bytes_escritos = write_log(log_para_escrever);

  TEST_ASSERT_EQUAL_UINT_MESSAGE(sizeof(AccessLog), bytes_escritos, "O numero de bytes escritos nao corresponde ao esperado.");
  printf("Log escrito com sucesso (%u bytes)! \u2705\n", bytes_escritos);

  sd_unmount();
  printf("Cartao SD desmontado. Teste concluido.\n");
}

//-----------------------------------------------------------------------------------------
// Função Principal
int main(void) {
  stdio_init_all();
  sleep_ms(1000);
  UNITY_BEGIN();

  // Escolha como argumento a função de teste desejada
  // Exemplo: RUN_TEST(test_wifi_mqtt);
  RUN_TEST(test_sd_card);

  UNITY_END();
}
