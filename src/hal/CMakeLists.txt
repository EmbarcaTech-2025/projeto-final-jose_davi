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
  ${CMAKE_CURRENT_LIST_DIR}/../include
)

add_library(uart_comm STATIC
  uart_comm.c
)

target_link_libraries(uart_comm
  hardware_uart
  pico_stdlib
)

target_include_directories(uart_comm PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/../include
)
