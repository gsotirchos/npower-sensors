cmake_minimum_required(VERSION 3.10)

project(npower_sensors
    VERSION 1.0
    DESCRIPTION "Executables to get sensor measurements for npower app."
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -pedantic)

include("${PROJECT_SOURCE_DIR}/cmake/CPMdependencies.cmake")
include("${PROJECT_SOURCE_DIR}/cmake/ManualDependencies.cmake")


### targets ####################################################################
add_executable(demo
    "${PROJECT_SOURCE_DIR}/src/demo.cpp"
)

add_library(npower_sensors
    "${PROJECT_SOURCE_DIR}/include/npower_sensors.hpp"
    "${PROJECT_SOURCE_DIR}/src/npower_sensors.cpp"
)


### includes ###################################################################
target_include_directories(npower_sensors
    PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${ina219_SOURCE_DIR}/src"
)


### linked libraries ###########################################################
target_link_libraries(demo
    PRIVATE
    npower_sensors
)

target_link_libraries(npower_sensors
    PRIVATE
    "${GPIOD_LIB}"
    ina219
)


### Tests ######################################################################
add_executable(hall_sensor_tests
    "${PROJECT_SOURCE_DIR}/tests/steps_test.cpp"
)

target_include_directories(hall_sensor_tests
    PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(hall_sensor_tests
    PRIVATE
    npower_sensors
    gtest
    gmock
    gtest_main
)

enable_testing()
add_test(hall_sensor_tests hall_sensor_tests)
