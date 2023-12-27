cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(base-firmware-V2)

target_sources(app PRIVATE src/main.c)

# Application sources

add_subdirectory(src/Fan_cooling)
add_subdirectory(src/Display)
add_subdirectory(src/BMI088)
