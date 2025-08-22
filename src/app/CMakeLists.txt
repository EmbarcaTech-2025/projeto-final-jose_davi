# Mude essa variável para escolher o dispositivo
# "MASTER" para o dispositivo mestre
# "SLAVE" para o dispositivo escravo
set(DEVICE "SLAVE")

if(DEVICE STREQUAL "MASTER")
  add_executable(projeto_final
    projeto_final.c
    ../drivers/led_rgb.c
    ../drivers/buzzer.c
    ../drivers/display_oled.c
    ../inc/ssd1306_i2c.c
  )

  add_compile_definitions(USE_PRINTF USE_DBG_PRINTF)

  pico_set_program_name(${PROJECT_NAME} "${PROJECT_NAME}")
  pico_set_program_version(${PROJECT_NAME} "0.1")

  # Modify the below lines to enable/disable output over UART/USB
  pico_enable_stdio_uart(${PROJECT_NAME} 0)
  pico_enable_stdio_usb(${PROJECT_NAME} 1)

  # Add the standard library to the build
  target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_gpio
    hardware_pwm
    hardware_i2c
    keyboard_handler
    bmp280
    bh1750
    aht10
  )

  # Add the standard include files to the build
  target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
  )

  pico_add_extra_outputs(${PROJECT_NAME})
else()
  add_executable(projeto_final
    bitdoglab_escrava.c
  )

  add_compile_definitions(USE_PRINTF USE_DBG_PRINTF)

  pico_set_program_name(${PROJECT_NAME} "${PROJECT_NAME}")
  pico_set_program_version(${PROJECT_NAME} "0.1")

  # Modify the below lines to enable/disable output over UART/USB
  pico_enable_stdio_uart(${PROJECT_NAME} 0)
  pico_enable_stdio_usb(${PROJECT_NAME} 1)

  # Add the standard library to the build
  target_link_libraries(${PROJECT_NAME}
    pico_i2c_slave
    hardware_gpio
    hardware_i2c
    sd_card_handler
  )

  # Add the standard include files to the build
  target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
  )

  pico_add_extra_outputs(${PROJECT_NAME})
endif()
