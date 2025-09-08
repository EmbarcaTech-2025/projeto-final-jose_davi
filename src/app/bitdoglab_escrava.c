#include <stdio.h> // Essencial para usar printf

#include "aht10.h"
#include "bh1750.h"
#include "bmp280.h"
#include "mqtt_comm.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "sd_card_handler.h"
#include "uart_comm.h"
#include "wifi_conn.h"

int main() {
    // Inicializa a comunicação USB para que os logs apareçam no monitor serial
    stdio_init_all();
    sleep_ms(2000); // Uma pequena pausa para dar tempo de conectar o monitor serial
    printf("--- INICIO DO PROGRAMA ---\n");

    // --- INICIALIZAÇÃO DOS PERIFÉRICOS ---
    printf("[INIT] Inicializando UART...\n");
    uart_comm_init();
    printf("[INIT] UART OK.\n");

    AccessLog received_log;

    printf("[INIT] Inicializando I2C na porta i2c1 (SDA: GPIO 2, SCL: GPIO 3)...\n");
    i2c_init(i2c1, 100 * 1000);
    gpio_set_function(2, GPIO_FUNC_I2C);
    gpio_set_function(3, GPIO_FUNC_I2C);
    gpio_pull_up(2);
    gpio_pull_up(3);
    printf("[INIT] I2C OK.\n");

    printf("[INIT] Inicializando sensores...\n");
    bmp280_init();
    printf("  -> BMP280 (Pressao/Temp) iniciado.\n");
    bh1750_init();
    printf("  -> BH1750 (Luminosidade) iniciado.\n");
    aht10_init();
    printf("  -> AHT10 (Umidade/Temp) iniciado.\n");
    printf("[INIT] Sensores OK.\n");

    // --- LÓGICA DE ESCRITA NO SD CARD (MELHORADA) ---
    // Monta o cartão SD uma única vez na inicialização
    printf("[INIT] Montando cartao SD...\n");
    if (sd_mount()) {
        printf("[INIT] Cartao SD montado com sucesso.\n");
    } else {
        printf("[ERRO] Falha ao montar o cartao SD!\n");
    }

    // --- INICIALIZAÇÃO DA REDE ---
    printf("[NET] Conectando ao Wi-Fi...\n");
    connect_to_wifi("iPhone de Davi", "16290101");
    printf("[NET] Wi-Fi conectado com sucesso.\n");
        
    printf("[NET] Configurando MQTT...\n");
    mqtt_setup("bitdoglab_mestre", "172.20.10.2", "bitdoglab_mestre", "12345678");
    printf("[NET] Setup MQTT concluido.\n");

    // --- VARIÁVEIS DO LOOP ---
    float lux = 0;
    float temp = 0;
    float pres = 0;
    float humidity = 0;
    uint64_t last_publish_time = 0;

    printf("\n--- INICIANDO LOOP PRINCIPAL ---\n");
    while (true) {
        // --- SEÇÃO DE RECEBIMENTO VIA UART ---
        if (uart_receive_log(&received_log)) {
            printf("\n[UART] Log recebido via UART:\n");
            printf("  -> Nome: %s, Op: %s, Time: %s\n", received_log.name, received_log.operation, received_log.timestamp);
            
            printf("[SD] Escrevendo log no cartao SD...\n");
            uint bw = write_log(received_log);
            if (bw > 0) {
                printf("[SD] Log escrito com sucesso (%u bytes).\n", bw);
            } else {
                printf("[ERRO] Falha ao escrever log no cartao SD!\n");
            }
        }

        // --- SEÇÃO DE LEITURA E PUBLICAÇÃO DOS SENSORES ---
        uint64_t current_time = time_us_64() / 1000;
        if (current_time - last_publish_time >= 5000) {
            last_publish_time = current_time;
            printf("\n[SENSOR] Realizando leitura dos sensores...\n");

            get_temp_pres(&temp, &pres);
            lux = get_lux();
            humidity = GetHumidity();
            printf("  -> Temp: %.2f C, Pressao: %.2f hPa, Umidade: %.2f %%, Lux: %.2f\n", temp, pres, humidity, lux);
            
            printf("[MQTT] Publicando dados dos sensores...\n");
            // CORRIGIDO: mqqt -> mqtt
            mqqt_publish_sensor_data(temp, pres, humidity, lux);
            printf("[MQTT] Dados publicados.\n");
        }
    }

    return 0; // Esta linha nunca será alcançada
}