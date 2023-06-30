cmake_minimum_required(VERSION 3.14)
project(event-system
    VERSION 1.0.0
    DESCRIPTION "Template for C++ library built with CMake"
    LANGUAGES CXX)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include(../../cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

# EVENT_SYSTEM_LIB_SHARED_LIBS option (undefined by default) can be used to force shared/static build
option(EVENT_SYSTEM_LIB_BUILD_TESTS "Build event-system tests" OFF)
option(EVENT_SYSTEM_LIB_BUILD_DOCS "Build event-system documentation" OFF)

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(event-system INTERFACE) # initialized below
add_library(event-system::event-system ALIAS event-system)

#----------------------------------------------------------------------------------------------------------------------
# eventsystem_lib dependencies
#----------------------------------------------------------------------------------------------------------------------

if(is_top_level)
    find_package(generic-core REQUIRED)
endif()

target_link_libraries(event-system
    PRIVATE generic-core::generic-core
)

#----------------------------------------------------------------------------------------------------------------------
# eventsystem_lib sources
#----------------------------------------------------------------------------------------------------------------------

set(public_src
   src/implementation/event_subscription_impl.hpp
   src/implementation/event_subscription_list.hpp
   src/implementation/i_event_subscribtion_list.hpp
)

set(public_headers
    include/event-system/event_subscription.hpp
    include/event-system/event_system.hpp
    include/event-system/i_event_system.hpp
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
#add_warnings_to_interface_target_test(event-system)

target_include_directories(event-system
    INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
        )

set_target_properties(event-system PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

#----------------------------------------------------------------------------------------------------------------------
# other targets
#----------------------------------------------------------------------------------------------------------------------

if(EVENT_SYSTEM_LIB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(EVENT_SYSTEM_LIB_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()