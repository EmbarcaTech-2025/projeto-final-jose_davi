#include "aht10.h"
#include "bh1750.h"
#include "bmp280.h"
#include "mqtt_comm.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "sd_card_handler.h"
#include "uart_comm.h"
#include "wifi_conn.h"
#include <stdio.h>

int main() {
  stdio_init_all();

  uart_comm_init();

  AccessLog received_log;

  connect_to_wifi("SSID", "Senha WiFi");
  mqtt_setup("bitdoglab_mestre", "IP do Broker", "bitdoglab_mestre",
             "12345678");

  bmp280_init();
  bh1750_init();
  aht10_init();

  float lux = 0;
  float temp = 0;
  float pres = 0;
  float humidity = 0;

  uint64_t last_publish_time = 0;

  while (true) {
    if (uart_receive_log(&received_log)) {
      printf("Log recebido!\n");
      printf("  Nome: %s\n", received_log.name);
      printf("  Data/Hora: %s\n", received_log.timestamp);
      printf("  Tipo: %s\n", received_log.operation);

      sd_mount();

      uint bw = write_log(received_log);

      if (bw != sizeof(received_log)) {
        printf("Erro na escrita do log!\n");
      } else {
        printf("Log escrito com sucesso!\n");
      }
      sd_unmount();

      sleep_ms(1);
    }

    uint64_t current_time = time_us_64() / 1000;
    if (current_time - last_publish_time > 5000) {
      last_publish_time = current_time;

      get_temp_pres(&temp, &pres);
      lux = get_lux();
      humidity = GetHumidity();

      mqqt_publish_sensor_data(temp, pres, humidity, lux);
    }
  }

  return 0;
}
