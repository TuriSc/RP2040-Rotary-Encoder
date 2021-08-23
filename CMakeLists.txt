# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Rotary-Encoder C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(Rotary-Encoder example.c)

pico_set_program_name(Rotary-Encoder "Rotary-Encoder")
pico_set_program_version(Rotary-Encoder "0.1")

pico_enable_stdio_uart(Rotary-Encoder 1)
pico_enable_stdio_usb(Rotary-Encoder 0)

# Add the standard library to the build
target_link_libraries(Rotary-Encoder pico_stdlib)

pico_add_extra_outputs(Rotary-Encoder)
