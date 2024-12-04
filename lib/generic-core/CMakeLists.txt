cmake_minimum_required(VERSION 3.14)
project(generic-core
    VERSION 1.0.0
    DESCRIPTION "Template for C++ library built with CMake"
    LANGUAGES CXX)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include(../../cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

# GENERIC_CORE_LIB_SHARED_LIBS option (undefined by default) can be used to force shared/static build
option(GENERIC_CORE_LIB_BUILD_TESTS "Build generic-core tests" OFF)
option(GENERIC_CORE_LIB_BUILD_DOCS "Build generic-core documentation" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(generic-core ) # initialized below
add_library(generic-core::generic-core ALIAS generic-core)

#----------------------------------------------------------------------------------------------------------------------
# eventsystem_lib dependencies
#----------------------------------------------------------------------------------------------------------------------
include(FetchContent)

FetchContent_Declare(easyloggingpp
  GIT_REPOSITORY https://github.com/abumq/easyloggingpp.git
  GIT_TAG v9.97.0
)

set(build_static_lib ON)

FetchContent_MakeAvailable(easyloggingpp)

target_link_libraries(generic-core
    PRIVATE easyloggingpp
)

target_include_directories(generic-core 
    PUBLIC ${easyloggingpp_SOURCE_DIR}/src/
)

#----------------------------------------------------------------------------------------------------------------------
# eventsystem_lib sources
#----------------------------------------------------------------------------------------------------------------------

set(public_src
    src/logger.cpp
)

set(public_headers
    include/generic-core/logger.hpp
    include/generic-core/logger_init.hpp
    )
    
set(sources
    ${public_headers}
    ${public_src}
    )

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# eventsystem_lib target
#----------------------------------------------------------------------------------------------------------------------

#include("./../../cmake/warnings.cmake")
#add_warnings_to_interface_target_test(generic-core)

target_sources(generic-core PRIVATE ${sources})

target_include_directories(generic-core
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
        )

set_target_properties(generic-core PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

#----------------------------------------------------------------------------------------------------------------------
# other targets
#----------------------------------------------------------------------------------------------------------------------

if(GENERIC_CORE_LIB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(GENERIC_CORE_LIB_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()