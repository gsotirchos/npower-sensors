cmake_minimum_required(VERSION 3.10)

project(npower_monitor
    VERSION 1.0
    DESCRIPTION "Executables to get sensor measurements for npower app."
    LANGUAGES CXX
)

add_compile_options(-Wall -Wextra -pedantic)


add_executable(demo
    src/demo.cpp
)

add_library(npower_monitor
    include/steps_monitor.hpp
    src/steps_monitor.cpp
)


target_include_directories(npower_monitor
    PUBLIC
    include/
)

# use cxx librares instead of c
set_target_properties(npower_monitor
    PROPERTIES
    IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
)

target_link_libraries(demo
    PRIVATE
    npower_monitor
)

find_library(GPIOD_LIB gpiodcxx)
target_link_libraries(npower_monitor
    PRIVATE
    ${GPIOD_LIB}
)


## Tests
enable_testing()

# GoogleTest downloader by Henry Schreiner:
# https://github.com/CLIUtils/cmake
include(cmake/AddGoogleTest.cmake)

add_executable(steps_test
    tests/steps_test.cpp
)

add_gtest(steps_test)
