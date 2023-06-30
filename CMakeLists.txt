cmake_minimum_required(VERSION 3.14)
project(sup-manager-union
    VERSION 1.0.0
    DESCRIPTION "Template for C++ library built with CMake"
    LANGUAGES CXX)

add_subdirectory(lib/generic-core)
add_subdirectory(lib/console-gui-elements-lib)
add_subdirectory(lib/event-system)
add_subdirectory(lib/generic-types)
add_subdirectory(lib/filesystem)
add_subdirectory(src)