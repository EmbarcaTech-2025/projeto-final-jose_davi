add_executable(tests tests.c)

pico_set_program_name(tests "tests")
pico_set_program_version(tests "0.1")

pico_enable_stdio_uart(tests 0)
pico_enable_stdio_usb(tests 1)

target_link_libraries(tests
  pico_stdlib
  unity
)

pico_add_extra_outputs(tests)

