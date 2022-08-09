cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)

project(libpo13 C CXX ASM)

pico_sdk_init()

add_library(po13)

#add_subdirectory(../libsh1107 libsh1107)

add_subdirectory(legacy)

target_include_directories(
    po13
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources(
    po13
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src/po13.c
    ${CMAKE_CURRENT_LIST_DIR}/src/legacy.c
)

target_link_libraries(
    po13
    PUBLIC
    #sh1107
    legacy
)

