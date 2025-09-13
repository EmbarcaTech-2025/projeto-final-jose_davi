# Mude essa variável para escolher o dispositivo
# "MASTER" para o dispositivo mestre
# "SLAVE" para o dispositivo escravo
# "RFID_WRITTER" para um programa de teste de escrita no cartão
set(DEVICE "RFID_WRITTER")

if(DEVICE STREQUAL "MASTER")
  add_executable(${PROJECT_NAME}
      bitdoglab_mestre.c
    )

  pico_set_program_name(${PROJECT_NAME} "bitdoglab_mestre")
  pico_set_program_version(${PROJECT_NAME} "0.1")

  # Modify the below lines to enable/disable output over UART/USB
  pico_enable_stdio_uart(${PROJECT_NAME} 0)
  pico_enable_stdio_usb(${PROJECT_NAME} 1)

  # Add the standard library to the build
  target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_mqtt
    pico_lwip
    pico_cyw43_driver
    hardware_i2c
    sd_card_handler
    mfrc522
    pico_mbedtls
    led_rgb
    buzzer
    display_oled
    bmp280
    bh1750
    aht10
    current_time
    uart_comm
    wifi_conn
  )

  # Add the standard include files to the build
  target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
  )

  pico_add_extra_outputs(${PROJECT_NAME})
elseif(DEVICE STREQUAL "SLAVE")
  add_executable(${PROJECT_NAME}
    bitdoglab_escrava.c
  )

  add_compile_definitions(USE_PRINTF USE_DBG_PRINTF)

  pico_set_program_name(${PROJECT_NAME} "bitdoglab_escrava")
  pico_set_program_version(${PROJECT_NAME} "0.1")

  # Modify the below lines to enable/disable output over UART/USB
  pico_enable_stdio_uart(${PROJECT_NAME} 0)
  pico_enable_stdio_usb(${PROJECT_NAME} 1)

  # Add the standard library to the build
  target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    pico_i2c_slave
    pico_stdio
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_mqtt
    pico_lwip
    pico_cyw43_driver
    pico_mbedtls
    hardware_gpio
    hardware_i2c
    sd_card_handler
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_mqtt
    pico_lwip
    pico_cyw43_driver
    wifi_conn
    mqtt_comm
    bmp280
    bh1750
    aht10
    uart_comm
  )

  # Add the standard include files to the build
  target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
  )

  pico_add_extra_outputs(${PROJECT_NAME})

  # --- NOVA SEÇÃO ADICIONADA ---
elseif(DEVICE STREQUAL "RFID_WRITTER")
  # Adiciona o executável com o código de teste do RFID
  add_executable(${PROJECT_NAME}
        # Crie um arquivo com este nome para o seu código de escrita
        rfid_writter.c
    )

  # Define o nome do arquivo de saída (ex: rfid_writter.uf2)
  pico_set_program_name(${PROJECT_NAME} "rfid_writter")
  pico_set_program_version(${PROJECT_NAME} "0.1")

  # Habilita a saída via USB para ver o printf no terminal
  pico_enable_stdio_uart(${PROJECT_NAME} 0)
  pico_enable_stdio_usb(${PROJECT_NAME} 1)

  # Linka as bibliotecas essenciais para o RFID funcionar
  target_link_libraries(${PROJECT_NAME}
        pico_stdlib
        hardware_spi  # Necessário para o MFRC522
        mfrc522       # Nossa biblioteca customizada do leitor
        pico_mbedtls      # Biblioteca para funções de hash (SHA-256)
    )

  # Inclui o diretório atual para encontrar os headers
  target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
    )

  pico_add_extra_outputs(${PROJECT_NAME})
  # -----------------------------

else()
  message(FATAL_ERROR "Valor inválido para a variável DEVICE: '${DEVICE}'. Use 'MASTER', 'SLAVE' ou 'RFID_WRITTER'.")
endif()
