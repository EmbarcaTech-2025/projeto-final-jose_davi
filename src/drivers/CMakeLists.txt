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
  ${CMAKE_CURRENT_LIST_DIR}/../include
)


