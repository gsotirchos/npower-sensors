include("${CMAKE_SOURCE_DIR}/cmake/AddCPM.cmake")

## CPM dependencies
CPMAddPackage(
    GITHUB_REPOSITORY google/googletest
    GIT_TAG release-1.10.0
)
