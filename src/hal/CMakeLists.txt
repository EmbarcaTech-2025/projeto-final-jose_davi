add_library(i2c_messages STATIC
  i2c_messages.c
)

target_link_libraries(i2c_messages
  hardware_gpio
  hardware_i2c
  pico_time
  sd_card_handler
)

target_include_directories(i2c_messages PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)
