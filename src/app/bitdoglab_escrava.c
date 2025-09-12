#include "pico/stdlib.h"
#include <stdio.h> 
#include "aht10.h"
#include "bh1750.h"
#include "bmp280.h"
#include "wifi_conn.h"
#include "mqtt_comm.h"
#include "pico/cyw43_arch.h"
#include "sd_card_handler.h"
#include "uart_comm.h"

int main() {
    stdio_init_all();
    sleep_ms(2000); 

    uart_comm_init();

    AccessLog received_log;

    i2c_init(i2c1, 100 * 1000);
    gpio_set_function(2, GPIO_FUNC_I2C);
    gpio_set_function(3, GPIO_FUNC_I2C);
    gpio_pull_up(2);
    gpio_pull_up(3);

    bmp280_init();
    bh1750_init();
    aht10_init();

    if (sd_mount()) {
        printf("Cartao SD montado com sucesso.\n");
    } else {
        printf("Falha ao montar o cartao SD!\n");
    }

    connect_to_wifi("SSID", "Senha");

    mqtt_setup("bitdoglab_escravo", "172.20.10.2 ", "bitdoglab_escravo", "12345678");

    float lux = 0;
    float temp = 0;
    float pres = 0;
    float humidity = 0;
    uint64_t last_publish_time = 0;
    while (true) {
        if (uart_receive_log(&received_log)) {
            printf("  -> Nome: %s, Op: %s, Time: %s\n", received_log.name, received_log.operation, received_log.timestamp);

            uint bw = write_log(received_log);
            if (bw > 0) {
                printf("[SD] Log escrito com sucesso (%u bytes).\n", bw);
            } else {
                printf("[ERRO] Falha ao escrever log no cartao SD!\n");
            }
        }

        uint64_t current_time = time_us_64() / 1000;
        if (current_time - last_publish_time >= 5000) {
            last_publish_time = current_time;

            get_temp_pres(&temp, &pres);
            lux = get_lux();
            humidity = GetHumidity();
            printf("  -> Temp: %.2f C, Pressao: %.2f hPa, Umidade: %.2f %%, Lux: %.2f\n", temp, pres, humidity, lux);

            mqqt_publish_sensor_data(temp, pres, humidity, lux);
        }
    }

    return 0; 
}