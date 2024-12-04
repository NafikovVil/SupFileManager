cmake_minimum_required(VERSION 3.14)
project(generic-types
    VERSION 1.0.0
    DESCRIPTION "Template for C++ library built with CMake"
    LANGUAGES CXX)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include(../../cmake/utils.cmake)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(generic-types INTERFACE) # initialized below
add_library(generic-types::generic-types ALIAS generic-types)

#----------------------------------------------------------------------------------------------------------------------
# lib sources
#----------------------------------------------------------------------------------------------------------------------

set(public_headers
    include/generic-types/i_controller.hpp
    include/generic-types/i_view.hpp
    include/generic-types/thread_safe_queue.hpp
    )
    
set(sources
    ${public_headers}
    )

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# flib target settings
#----------------------------------------------------------------------------------------------------------------------

target_include_directories(generic-types INTERFACE 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
    )

set_target_properties(generic-types PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION}
)

include(CMakePackageConfigHelpers)

if(GENERIC_TYPES_LIB_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/generic-types-config.cmake.in generic-types-config.cmake
        INSTALL_DESTINATION "${GENERIC_TYPES_LIB_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(generic-types-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS generic-types EXPORT generic-types_export
        RUNTIME COMPONENT generic-types
        LIBRARY COMPONENT generic-types NAMELINK_COMPONENT generic-types-dev
        ARCHIVE COMPONENT generic-types-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT generic-types-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/filesystem_lib/${export_file_name}"
        COMPONENT generic-types-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/generic-types")

    set(targets_file "generic-types-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "generic-types-static-targets.cmake")
    endif()

    install(EXPORT generic-types_export
        COMPONENT generic-types-dev
        FILE "${targets_file}"
        DESTINATION "${GENERIC_TYPES_LIB_INSTALL_CMAKEDIR}"
        NAMESPACE generic-types::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/generic-types-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/generic-types-config-version.cmake"
        COMPONENT generic-types-dev
        DESTINATION "${GENERIC_TYPES_LIB_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:generic-types>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:generic-types>/$<TARGET_FILE_PREFIX:generic-types>$<TARGET_FILE_BASE_NAME:generic-types>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT generic-types-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()

#----------------------------------------------------------------------------------------------------------------------
# other targets
#----------------------------------------------------------------------------------------------------------------------

if(GENERIC_TYPES_LIB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(GENERIC_TYPES_LIB_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()