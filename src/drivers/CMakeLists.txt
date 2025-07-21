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
