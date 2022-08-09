# legacy Waveshare code for Pico OLED 1.3
add_library(legacy)

#add_subdirectory(../libsh1107 libsh1107)

add_subdirectory(Config)
add_subdirectory(Fonts)
add_subdirectory(GUI)
add_subdirectory(OLED)

target_include_directories(
    legacy
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/GUI
    ${CMAKE_CURRENT_LIST_DIR}/Config
    ${CMAKE_CURRENT_LIST_DIR}/Fonts
    ${CMAKE_CURRENT_LIST_DIR}/OLED
)

target_sources(
    legacy
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src/ImageData.c
    ${CMAKE_CURRENT_LIST_DIR}/src/OLED_1in3_C_test.c
)

target_link_libraries(
    legacy
    PUBLIC
    Config
    Fonts
    GUI
    OLED
    pico_stdlib
    hardware_spi
    hardware_i2c
    hardware_pwm
)

