add_library(keyboard_handler STATIC
  keyboard_handler.c
)

target_link_libraries(keyboard_handler
  pico_stdlib
  hardware_timer
)

target_include_directories(keyboard_handler PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

add_library(sd_card_handler STATIC
  sd_card_handler.c
  hw_config.c
)

target_link_libraries(sd_card_handler
  pico_stdlib
  hardware_i2c
  no-OS-FatFS-SD-SDIO-SPI-RPi-Pico
)

target_include_directories(sd_card_handler PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

add_library(bmp280 STATIC
  bmp280.c
)

target_link_libraries(bmp280
  hardware_i2c
)

target_include_directories(bmp280 PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

add_library(bh1750 STATIC
  bh1750.c
)

target_link_libraries(bh1750
  hardware_i2c
)

target_include_directories(bh1750 PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

add_library(aht10 STATIC
  aht10.c
)

target_link_libraries(aht10
  hardware_i2c
)

target_include_directories(aht10 PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

add_library(wifi_conn STATIC
  wifi_conn.c
)

target_link_libraries(wifi_conn
  pico_stdlib
  pico_cyw43_arch_lwip_threadsafe_background
  pico_lwip_mqtt
  pico_lwip
  pico_cyw43_driver
)

target_include_directories(wifi_conn PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/../include
)

add_library(mqtt_comm STATIC
  mqtt_comm.c
)

target_link_libraries(mqtt_comm
  pico_stdlib
  pico_cyw43_arch_lwip_threadsafe_background
  pico_lwip_mqtt
  pico_lwip
  pico_cyw43_driver
)

target_include_directories(mqtt_comm PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/../include
)

add_library(mfrc522 STATIC
  mfrc522.c
)

target_link_libraries(mfrc522
  hardware_spi
  pico_stdlib
)

target_include_directories(mfrc522 PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

add_library(led_rgb STATIC
  led_rgb.c
)

target_link_libraries(led_rgb
  pico_stdlib
  hardware_gpio
)

target_include_directories(led_rgb PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/../include
)

add_library(buzzer STATIC
  buzzer.c
)

target_link_libraries(buzzer
  pico_stdlib
  hardware_gpio
  hardware_pwm
)

target_include_directories(buzzer PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/../include
)

add_library(display_oled STATIC
  display_oled.c
  ../inc/ssd1306_i2c.c
)

target_link_libraries(display_oled
  pico_stdlib
  hardware_gpio
  hardware_i2c
)

target_include_directories(display_oled PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/../include
  ${CMAKE_CURRENT_LIST_DIR}/../inc
)

add_library(current_time STATIC
  current_time.c
)

target_link_libraries(current_time
  pico_stdlib
  hardware_rtc       
  pico_cyw43_arch_lwip_threadsafe_background
  wifi_conn 
  pico_lwip_sntp
)

target_include_directories(current_time PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_SOURCE_DIR}
)


