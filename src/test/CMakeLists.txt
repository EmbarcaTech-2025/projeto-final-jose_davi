add_executable(tests 
  tests.c 
  Unity/unity.c
)

pico_set_program_name(tests "tests")
pico_set_program_version(tests "0.1")

pico_enable_stdio_uart(tests 0)
pico_enable_stdio_usb(tests 1)

target_link_libraries(tests
  pico_stdlib
  keyboard_handler
  wifi_conn
  mqtt_comm
  bmp280
  bh1750
  aht10
  hardware_i2c
  i2c_messages
  sd_card_handler
)

pico_add_extra_outputs(tests)

