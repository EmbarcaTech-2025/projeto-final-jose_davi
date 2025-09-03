# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
  set(USERHOME $ENV{USERPROFILE})
else()
  set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
  include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TARGET_GROUP production CACHE STRING "Group to build")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PICO_BOARD pico_w CACHE STRING "Board type")

if (DEFINED ENV{PICO_SDK_PATH})
  include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)
else()
  include(pico_sdk_import.cmake)
endif()

project(projeto_final C CXX ASM)

include_directories(${CMAKE_SOURCE_DIR})

pico_sdk_init()

add_subdirectory(./src/include/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico/src build)

add_subdirectory(src/drivers)
add_subdirectory(src/test)
# add_subdirectory(src/hal)
add_subdirectory(src/hal)

if(TARGET_GROUP STREQUAL production)
  add_subdirectory(src/app)
elseif(TARGET_GROUP STREQUAL test)
  # add_subdirectory(Unity)
  add_subdirectory(src/test)
else()
  message(FATAL_ERROR "Given TARGET_GROUP unknown")
endif()




