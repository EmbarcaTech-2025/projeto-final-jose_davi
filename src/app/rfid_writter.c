#include <stdio.h>
#include <math.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "mfrc522.h"

#include "mbedtls/md.h"

#define START_BLOCK 4  // Primeiro bloco de dados disponível em um setor típico

MFRC522Ptr_t mfrc;

const uint8_t HMAC_SECRET_KEY[32] = {
    0x20, 0x02, 0x03, 0x1C, 0x05, 0x06, 0x07, 0x08,
    0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
    0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
    0x19, 0x1A, 0x1B, 0x04, 0x1D, 0x1E, 0x1F, 0x01
};

int main() {
  // Inicializa o stdio para comunicação via USB
  stdio_init_all();

  // Inicializa a instância do MFRC522
  mfrc = MFRC522_Init();

  // Inicializa o hardware SPI e o PCD (Proximity Coupling Device - o leitor)
  // A biblioteca espera que o SPI seja inicializado externamente
  spi_init(spi0, MFRC522_BIT_RATE);
  gpio_set_function(miso_pin, GPIO_FUNC_SPI);
  gpio_set_function(sck_pin, GPIO_FUNC_SPI);
  gpio_set_function(mosi_pin, GPIO_FUNC_SPI);
    
  PCD_Init(mfrc, spi0);

  while (true) {
    // 1. Espera até que um novo cartão seja apresentado
    while (!PICC_IsNewCardPresent(mfrc));

    // 2. Seleciona um dos cartões (lê o UID)
    if (!PICC_ReadCardSerial(mfrc)) {
      printf("Falha ao ler o serial do cartao. Tente novamente.\n");
      sleep_ms(1000);
      continue;
    }

    const char* nome = "Davi Henrique Vieira Lima";
    const char* cpf = "123.456.789-00";

    // --- PASSO CRÍTICO DE SEGURANÇA: GERAR O HMAC ---
    printf("Gerando assinatura criptografica (HMAC-SHA256)...\n");
        
    // a. Preparar os dados a serem assinados (UID + CPF + Nome)
    //    Assinar o UID junto com os dados vincula a assinatura a este cartão físico.
    uint8_t data_to_sign[256];
    int sign_len = 0;
    memcpy(data_to_sign, mfrc->uid.uidByte, mfrc->uid.size);
    sign_len += mfrc->uid.size;
    sign_len += snprintf((char*)(data_to_sign + sign_len), sizeof(data_to_sign) - sign_len, "%s%s", cpf, nome);

    // b. Calcular o HMAC
    uint8_t hmac_result[32]; // SHA-256 produz um hash de 32 bytes
    const mbedtls_md_info_t* md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
    mbedtls_md_hmac(md_info, HMAC_SECRET_KEY, sizeof(HMAC_SECRET_KEY), data_to_sign, sign_len, hmac_result);

    printf("Assinatura gerada com sucesso.\n");

    // 3. Formatar o payload completo para gravação (CPF + Nome + HMAC)
    uint8_t payload[256];
    int payload_len = snprintf((char*)payload, sizeof(payload), "%s%c%s%c", cpf, '\0', nome, '\0');
    memcpy(&payload[payload_len], hmac_result, sizeof(hmac_result));
    payload_len += sizeof(hmac_result);

    // 4. Preparar o buffer final para escrita (1 byte de tamanho + payload)
    uint8_t buffer_to_write[payload_len + 1];
    buffer_to_write[0] = (uint8_t)payload_len;
    memcpy(&buffer_to_write[1], payload, payload_len);

    int total_write_size = payload_len + 1;
    int blocks_needed = (int)ceil((float)total_write_size / 16.0);
    printf("Tamanho total dos dados + assinatura: %d bytes. Blocos necessarios: %d\n", payload_len, blocks_needed);

    // 5. Loop para escrever os dados segmentados nos blocos
    bool write_success = true;
    int data_offset = 0;
    uint8_t current_block = START_BLOCK;
        
    for (int i = 0; i < blocks_needed; i++) {
        // Pula os blocos de trailer, que não podem ser usados para dados
        while ((current_block + 1) % 4 == 0) {
            printf("AVISO: Pulando bloco de trailer %d.\n", current_block);
            current_block++;
        }

        // Autenticar o bloco atual
        MIFARE_Key key;
        for (uint8_t k = 0; k < MF_KEY_SIZE; k++) { key.keybyte[k] = 0xFF; }
        StatusCode status = PCD_Authenticate(mfrc, PICC_CMD_MF_AUTH_KEY_A, current_block, &key, &(mfrc->uid));
        if (status != STATUS_OK) {
            printf("ERRO: Falha na autenticacao do bloco %d! Status: %s\n", current_block, GetStatusCodeName(status));
            write_success = false; break;
        }

        // Copiar o próximo "pedaço" de 16 bytes para um buffer temporário
        uint8_t chunk[16] = {0};
        int bytes_to_copy = total_write_size - data_offset;
        if (bytes_to_copy > 16) bytes_to_copy = 16;
        memcpy(chunk, &buffer_to_write[data_offset], bytes_to_copy);
            
        // Escrever no cartão
        status = MIFARE_Write(mfrc, current_block, chunk, 16);
        if (status != STATUS_OK) {
            printf("ERRO: Falha ao escrever no bloco %d! Status: %s\n", current_block, GetStatusCodeName(status));
            write_success = false; break;
        }
        printf("Bloco %d gravado com sucesso.\n", current_block);
            
        data_offset += 16;
        current_block++;
    }

    if (write_success) {
        printf(">>> SUCESSO! Cracha seguro gravado com sucesso. <<<\n");
    } else {
        printf(">>> FALHA! A gravacao foi interrompida. <<<\n");
    }

    // 7. Libera o cartão
    PICC_HaltA(mfrc);
    PCD_StopCrypto1(mfrc);

    return 0;
  }
}