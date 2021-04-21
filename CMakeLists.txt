cmake_minimum_required(VERSION 3.10)

project(NPowerSensors
    VERSION 1.0
    DESCRIPTION "Executables to get sensor measurements for npower app."
    LANGUAGES CXX
)

add_compile_options(-Wall -Wextra -pedantic)

include("${PROJECT_SOURCE_DIR}/cmake/CPMdependencies.cmake")
include("${PROJECT_SOURCE_DIR}/cmake/ManualDependencies.cmake")


### targets ####################################################################
add_executable(demo
    "${PROJECT_SOURCE_DIR}/src/demo.cpp"
)

add_library(NPowerSensors
    "${PROJECT_SOURCE_DIR}/include/npower_sensors.hpp"
    "${PROJECT_SOURCE_DIR}/src/npower_sensors.cpp"
)


### dependencies ###############################################################
add_dependencies(NPowerSensors
    ina219_PROJECT
)


### includes ###################################################################
target_include_directories(NPowerSensors
    PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${ina219_SOURCE_DIR}/src"
)


### linked libraries ###########################################################
target_link_libraries(demo
    PRIVATE
    NPowerSensors
)

target_link_libraries(NPowerSensors
    PRIVATE
    "${GPIOD_LIB}"
    ina219
)


### Tests ######################################################################
add_executable(HallSensorTests
    "${PROJECT_SOURCE_DIR}/tests/steps_test.cpp"
)

target_include_directories(HallSensorTests
    PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(HallSensorTests
    PRIVATE
    NPowerSensors
    gtest
    gmock
    gtest_main
)

enable_testing()
add_test(HallSensorTests HallSensorTests)
