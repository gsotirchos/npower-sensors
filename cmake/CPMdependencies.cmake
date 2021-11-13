include("${CMAKE_SOURCE_DIR}/cmake/AddCPM.cmake")

## CPM dependencies
CPMAddPackage(
    GITHUB_REPOSITORY google/googletest
    GIT_TAG release-1.10.0
    OPTIONS "INSTALL_GTEST OFF" "gtest_force_shared_crt"
)

CPMAddPackage(
    GITHUB_REPOSITORY gsotirchos/ina219
    GIT_TAG devel
)
