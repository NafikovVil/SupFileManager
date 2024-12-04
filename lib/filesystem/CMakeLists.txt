cmake_minimum_required(VERSION 3.14)

project(filesystem
    VERSION 1.0.0
    DESCRIPTION "Template for C++ library built with CMake"
    LANGUAGES CXX
)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include(../../cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

option(FILESYSTEM_LIB_BUILD_TESTS "Build filesystem tests" OFF)
option(FILESYSTEM_LIB_BUILD_DOCS "Build filesystem documentation" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(filesystem) # initialized below
add_library(filesystem::filesystem ALIAS filesystem)

#----------------------------------------------------------------------------------------------------------------------
# filesystem_lib dependencies
#----------------------------------------------------------------------------------------------------------------------

if(is_top_level)
    find_package(generic-core REQUIRED)
endif()

target_link_libraries(filesystem
    PRIVATE generic-core::generic-core
)

#target_include_directories(filesystem
#    INTERFACE
#        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
#        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
#)

#----------------------------------------------------------------------------------------------------------------------
# filesystem_lib sources
#----------------------------------------------------------------------------------------------------------------------

set(public_src
    src/filesystem.cpp
)

set(public_headers
    include/filesystem/filesystem.hpp
)
    
set(sources
    ${public_headers}
    ${public_src}
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# filesystem_lib target
#----------------------------------------------------------------------------------------------------------------------

target_sources(filesystem PRIVATE ${sources})

# Для разных методов подключения разные пути подключения headers
target_include_directories(filesystem
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
)

set_target_properties(filesystem PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION}
)

#----------------------------------------------------------------------------------------------------------------------
# other targets
#----------------------------------------------------------------------------------------------------------------------

if(FILESYSTEM_LIB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(FILESYSTEM_LIB_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()