cmake_minimum_required(VERSION 3.10)

project(NPowerMonitor
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

add_library(NPowerMonitor
    "${PROJECT_SOURCE_DIR}/include/npower_monitor.hpp"
    "${PROJECT_SOURCE_DIR}/src/npower_monitor.cpp"
)


### dependencies ###############################################################
add_dependencies(NPowerMonitor
    ina219_PROJECT
)


### includes ###################################################################
target_include_directories(NPowerMonitor
    PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${ina219_SOURCE_DIR}/src"
)


### linked libraries ###########################################################
target_link_libraries(demo
    PRIVATE
    NPowerMonitor
)

target_link_libraries(NPowerMonitor
    PRIVATE
    "${GPIOD_LIB}"
    ina219
)


### Tests ######################################################################
add_executable(StepsTest
    "${PROJECT_SOURCE_DIR}/tests/steps_test.cpp"
)

target_include_directories(StepsTest
    PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(StepsTest
    PRIVATE
    NPowerMonitor
    gtest
    gmock
    gtest_main
)

enable_testing()
add_test(StepsTest StepsTest)
