cmake_minimum_required(VERSION 3.10)
project(aide_sdk C)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

include_directories(include)

# Find packages
find_package(CURL REQUIRED)

# Library
add_library(aide SHARED src/aide_client.c)
target_link_libraries(aide CURL::libcurl)
set_target_properties(aide PROPERTIES
    VERSION ${VERSION}
    SOVERSION ${VERSION_MAJOR}
    PUBLIC_HEADER "include/aide/aide.h"
)

# Install
include(GNUInstallDirs)
install(TARGETS aide
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/aide
)

# Example
add_executable(example example.c)
target_link_libraries(example aide)
