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
  pico_time
  pico_types
  no-OS-FatFS-SD-SDIO-SPI-RPi-Pico
)

target_include_directories(sd_card_handler PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)
