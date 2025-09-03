#include <stdio.h>
#include <string.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "mfrc522.h"
#include "mbedtls/md.h"
#include "led_rgb.h"
#include "buzzer.h"
#include "display_oled.h"
#include "mqtt_comm.h"
#include "wifi_conn.h"
#include "aht10.h"
#include "bh1750.h"
#include "bmp280.h"
#include "i2c_config.h"
#include "pico/cyw43_arch.h"

// Chave Secreta para HMAC
const uint8_t HMAC_SECRET_KEY[32] = {
  0x20, 0x02, 0x03, 0x1C, 0x05, 0x06, 0x07, 0x08,
  0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
  0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
  0x19, 0x1A, 0x1B, 0x04, 0x1D, 0x1E, 0x1F, 0x01
};

const uint8_t START_BLOCK = 4;
MFRC522Ptr_t mfrc;

void get_first_name(const char* full_name, char* first_name_buffer, size_t buffer_size) {
    size_t i = 0;
    while (full_name[i] != '\0' && full_name[i] != ' ' && i < (buffer_size - 1)) {
        first_name_buffer[i] = full_name[i];
        i++;
    }
    first_name_buffer[i] = '\0';
}

int main() {
  // Inicializa o stdio para comunicação via USB
  stdio_init_all();

  // Inicializa a instância do MFRC522
  mfrc = MFRC522_Init();

  // Inicializa o hardware SPI e o PCD (Proximity Coupling Device - o leitor)
  spi_init(spi0, MFRC522_BIT_RATE);
  gpio_set_function(miso_pin, GPIO_FUNC_SPI);
  gpio_set_function(sck_pin, GPIO_FUNC_SPI);
  gpio_set_function(mosi_pin, GPIO_FUNC_SPI);
  PCD_Init(mfrc, spi0);

  // Inicializa os periféricos: LED RGB, Display OLED e Buzzer
  led_rgb_init(); 
  display_init();
  buzzer_init();

  // Configurações de rede (WiFi e MQTT)
  // Para nosso projeto, implementamos autenticação ao broker MQTT
  connect_to_wifi("SSID", "Senha WiFi");
  mqtt_setup("bitdoglab_mestre", "IP do Broker", "bitdoglab_mestre", "12345678");

  i2c_init(I2C_PORT, 100 * 1000);
  gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA_PIN);
  gpio_pull_up(I2C_SCL_PIN);

  bmp280_init();
  bh1750_init();  
  aht10_init();

  float lux = 0;
  float temp = 0;
  float pres = 0;
  float humidity = 0;

  uint64_t last_publish_time = 0;

  while (true) {
    memset(ssd, 0, ssd1306_buffer_length);
    draw_centered_string(ssd, 10, "Aproxime o");
    draw_centered_string(ssd, 29, "cartao RFID");
    draw_centered_string(ssd, 48, "do leitor");
    ssd1306_send_buffer(ssd, ssd1306_buffer_length);

    // Aguarda até que um novo cartão seja detectado
    // Enquanto aguarda, os dados dos sensores são atualizados e enviados via MQTT
    while (!PICC_IsNewCardPresent(mfrc)){
      // Pega o tempo atual
      uint64_t current_time = time_us_64() / 1000; 

      // Verifica se já se passaram 5 segundos desde a última publicação
      if (current_time - last_publish_time > 5000) {
        last_publish_time = current_time; 

        get_temp_pres(&temp, &pres);
        lux = get_lux();
        humidity = GetHumidity();

        mqqt_publish_sensor_data(temp, pres, humidity, lux); 
      }
      sleep_ms(10); 
    }

    // Lê o serial do cartão
    if (!PICC_ReadCardSerial(mfrc)) {
      printf("Falha ao ler o serial do cartao. Tente novamente.\n");
      sleep_ms(1000);
      continue;
    }

    // Autentica e lê os dados do cartão
    MIFARE_Key key;
    for (uint8_t k = 0; k < MF_KEY_SIZE; k++) { key.keybyte[k] = 0xFF; }

    uint8_t first_block_buffer[18];
    uint8_t bufferSize = sizeof(first_block_buffer);

    StatusCode status = PCD_Authenticate(mfrc, PICC_CMD_MF_AUTH_KEY_A, START_BLOCK, &key, &(mfrc->uid));
    if (status != STATUS_OK) {
      printf("ACESSO NEGADO: Falha na autenticacao inicial. Cartao nao confiavel.\n");
      PICC_HaltA(mfrc); PCD_StopCrypto1(mfrc);
      sleep_ms(2000);
      continue;
    }
        
    status = MIFARE_Read(mfrc, START_BLOCK, first_block_buffer, &bufferSize);
    if (status != STATUS_OK) {
      printf("ERRO: Falha ao ler o bloco de cabecalho.\n");
      PICC_HaltA(mfrc); PCD_StopCrypto1(mfrc);
      sleep_ms(2000);
      continue;
    }

    // O primeiro byte do bloco indica o tamanho total do payload (CPF + Nome + HMAC)
    uint8_t total_payload_len = first_block_buffer[0];
    if (total_payload_len == 0 || total_payload_len > 128) {
      printf("ACESSO NEGADO: Cartao vazio ou com dados corrompidos (tamanho=%d).\n", total_payload_len);
      PICC_HaltA(mfrc); PCD_StopCrypto1(mfrc);
      sleep_ms(2000);
      continue;
    }

    // Lê os blocos adicionais conforme necessário
    uint8_t reconstructed_payload[total_payload_len];
    int bytes_read = 15; 
    memcpy(reconstructed_payload, &first_block_buffer[1], bytes_read);

    int blocks_to_read_more = (int)ceil((float)(total_payload_len - 15) / 16.0);

    // Lê os blocos adicionais, pulando os blocos de trailer
    bool read_success = true;
    uint8_t current_block = START_BLOCK + 1;
    for (int i = 0; i < blocks_to_read_more; i++) {
      cyw43_arch_poll();
      while ((current_block + 1) % 4 == 0) { 
        current_block++;
      }

      status = PCD_Authenticate(mfrc, PICC_CMD_MF_AUTH_KEY_A, current_block, &key, &(mfrc->uid));
      if (status != STATUS_OK) { read_success = false; break; }
            
      uint8_t block_buffer[18];
      bufferSize = sizeof(block_buffer);
      status = MIFARE_Read(mfrc, current_block, block_buffer, &bufferSize);
      if (status != STATUS_OK) { read_success = false; break; }

      int bytes_to_copy = total_payload_len - bytes_read;
      if (bytes_to_copy > 16) bytes_to_copy = 16;
      memcpy(&reconstructed_payload[bytes_read], block_buffer, bytes_to_copy);
      bytes_read += bytes_to_copy;
        current_block++;
    }

    if (!read_success) {
      printf("ERRO: Falha ao ler os dados completos do cartao.\n");
      PICC_HaltA(mfrc); PCD_StopCrypto1(mfrc);
      sleep_ms(2000);
      continue;
    }

    // Extrai CPF, Nome e HMAC do payload reconstruído
    char* cpf = (char*)reconstructed_payload;
    char* nome = cpf + strlen(cpf) + 1;
    char first_name[10];
    uint8_t* received_hmac = reconstructed_payload + strlen(cpf) + 1 + strlen(nome) + 1;

    // Prepara os dados que foram originalmente assinados (UID + CPF + Nome)
    uint8_t data_to_verify[256];
    int verify_len = 0;
    memcpy(data_to_verify, mfrc->uid.uidByte, mfrc->uid.size);
    verify_len += mfrc->uid.size;
    verify_len += snprintf((char*)(data_to_verify + verify_len), sizeof(data_to_verify) - verify_len, "%s%s", cpf, nome);

    // Recalcular o HMAC usando a chave secreta do firmware
    uint8_t calculated_hmac[32];
    const mbedtls_md_info_t* md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
    mbedtls_md_hmac(md_info, HMAC_SECRET_KEY, sizeof(HMAC_SECRET_KEY), data_to_verify, verify_len, calculated_hmac);

    // Comparar o HMAC recebido do cartão com o HMAC que acabamos de calcular
    if (memcmp(received_hmac, calculated_hmac, 32) == 0) {
      get_first_name(nome, first_name, 10);
      memset(ssd, 0, ssd1306_buffer_length);
      draw_centered_string(ssd, 10, "Seja bem-vindo");
      draw_centered_string(ssd, 29, first_name);
      draw_centered_string(ssd, 48, "Acesso Liberado");
      ssd1306_send_buffer(ssd, ssd1306_buffer_length);

      gpio_put(LED_RGB_GREEN, 1); 
      play_buzzer();

      for (int i = 0; i < 200; i++) {
        cyw43_arch_poll();
        sleep_ms(10);
      }
      gpio_put(LED_RGB_GREEN, 0);

    } else {
      memset(ssd, 0, ssd1306_buffer_length);
      draw_centered_string(ssd, 20, "ACESSO NEGADO");
      draw_centered_string(ssd, 40, "Tente Novamente");
      ssd1306_send_buffer(ssd, ssd1306_buffer_length);

      gpio_put(LED_RGB_RED, 1);
      play_buzzer();

      for (int i = 0; i < 200; i++) {
        cyw43_arch_poll();
        sleep_ms(10);
      }
      gpio_put(LED_RGB_RED, 0);
    }

    // Libera o cartão
    PICC_HaltA(mfrc);
    PCD_StopCrypto1(mfrc);
  }

    return 0;
}