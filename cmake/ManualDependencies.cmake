find_library(GPIOD_LIB gpiodcxx)


include(ExternalProject)

set(ina219_SOURCE_DIR "${PROJECT_BINARY_DIR}/ina219")
ExternalProject_Add(ina219
    GIT_REPOSITORY "https://github.com/regisin/ina219"
    SOURCE_DIR "${ina219_SOURCE_DIR}"
    BUILD_IN_SOURCE TRUE
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make VERBOSE=1
    INSTALL_COMMAND ""
    EXCLUDE_FROM_ALL TRUE
)

file(MAKE_DIRECTORY "${ina219_SOURCE_DIR}")
