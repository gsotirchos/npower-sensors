find_library(GPIOD_LIB gpiodcxx)


set(ina219_SOURCE_DIR "${PROJECT_BINARY_DIR}/ina219_PROJECT")
set(ina219_LIB "${ina219_SOURCE_DIR}/build/ina219${CMAKE_SHARED_LIBRARY_SUFFIX}")

option(EP_UPDATE_DISCONNECTED "Download/build external projects only once" true)

include(ExternalProject)
ExternalProject_Add(ina219_PROJECT
    GIT_REPOSITORY "https://github.com/regisin/ina219"
    SOURCE_DIR "${ina219_SOURCE_DIR}"
    CONFIGURE_COMMAND ""  # don't configure
    BUILD_COMMAND make VERBOSE=1
    INSTALL_COMMAND ""  # don't install
    BUILD_IN_SOURCE TRUE  # in-source build
    BUILD_BYPRODUCTS "${ina219_LIB}"  # required for Ninja to not complain and trust me
)

# required to satisfy set_target_properties below
file(MAKE_DIRECTORY "${ina219_SOURCE_DIR}/src")

add_library(ina219 SHARED IMPORTED GLOBAL)
set_target_properties(ina219
    PROPERTIES
    IMPORTED_LOCATION "${ina219_LIB}"
    INTERFACE_INCLUDE_DIRECTORIES "${ina219_SOURCE_DIR}/src"
)
