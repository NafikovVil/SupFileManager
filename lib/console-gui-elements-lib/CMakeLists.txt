cmake_minimum_required(VERSION 3.14)
project(console-gui-elements-lib
    VERSION 1.0.0
    DESCRIPTION "Template for C++ library built with CMake"
    LANGUAGES CXX)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include(../../cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

# CONSOLE-GUI-ELEMENTS-LIB_SHARED_LIBS option (undefined by default) can be used to force shared/static build
option(CONSOLE-GUI-ELEMENTS-LIB_BUILD_TESTS "Build console-gui-elements-lib tests" OFF)
option(CONSOLE-GUI-ELEMENTS-LIB_BUILD_EXAMPLES "Build console-gui-elements-lib examples" OFF)
option(CONSOLE-GUI-ELEMENTS-LIB_BUILD_DOCS "Build console-gui-elements-lib documentation" OFF)
option(CONSOLE-GUI-ELEMENTS-LIB_INSTALL "Generate target for installing console-gui-elements-lib" ${is_top_level})

set_if_undefined(CONSOLE-GUI-ELEMENTS-LIB_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/console-gui-elements-lib" CACHE STRING
    "Install path for console-gui-elements-lib package-related CMake files")

if(DEFINED CONSOLE-GUI-ELEMENTS-LIB_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${CONSOLE-GUI-ELEMENTS-LIB_SHARED_LIBS})
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Make hidden non-export symbols for dynamic linking 
set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(console-gui-elements-lib) # initialized below
add_library(console-gui-elements-lib::console-gui-elements-lib ALIAS console-gui-elements-lib)

#----------------------------------------------------------------------------------------------------------------------
# filesystem_lib dependencies
#----------------------------------------------------------------------------------------------------------------------

include(FetchContent)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v3.0.0
)

#FetchContent_GetProperties(ftxui)
#if(NOT ftxui_POPULATED)
#  FetchContent_Populate(ftxui)
#  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR})# EXCLUDE_FROM_ALL)
#endif()

FetchContent_MakeAvailable(ftxui)

target_link_libraries(console-gui-elements-lib
    PUBLIC ftxui::screen
    PUBLIC ftxui::dom
    PUBLIC ftxui::component # Not needed for this example.
    )

#----------------------------------------------------------------------------------------------------------------------
# filesystem_lib sources
#----------------------------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.h")
endif()

generate_export_header(console-gui-elements-lib EXPORT_FILE_NAME include/console-gui-elements-lib/${export_file_name})

set(public_src
    src/menu_list.cpp
    )

set(public_headers
    include/console-gui-elements-lib/menu_list.hpp
    ${os_depend_public_headers})
    
set(sources
    ${public_headers}
    ${public_src})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# filesystem_lib target
#----------------------------------------------------------------------------------------------------------------------

target_sources(console-gui-elements-lib PRIVATE ${sources})

# Если сборка статическая, то определяем макрос CONSOLE-GUI-ELEMENTS-LIB_STATIC_DEFINE, который используется в export.h
target_compile_definitions(console-gui-elements-lib PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:CONSOLE-GUI-ELEMENTS-LIB_STATIC_DEFINE>")

# Для разных методов подключения разные пути подключения headers
target_include_directories(console-gui-elements-lib
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

set_target_properties(console-gui-elements-lib PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

# Разобрать код для install метода сборки
# попробывать cmake --install . --component mylib
include(CMakePackageConfigHelpers)

if(CONSOLE-GUI-ELEMENTS-LIB_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/console-gui-elements-lib-config.cmake.in console-gui-elements-lib-config.cmake
        INSTALL_DESTINATION "${CONSOLE-GUI-ELEMENTS-LIB_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(console-gui-elements-lib-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS console-gui-elements-lib EXPORT console-gui-elements-lib_export
        RUNTIME COMPONENT console-gui-elements-lib
        LIBRARY COMPONENT console-gui-elements-lib NAMELINK_COMPONENT console-gui-elements-lib-dev
        ARCHIVE COMPONENT console-gui-elements-lib-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT console-gui-elements-lib-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/filesystem_lib/${export_file_name}"
        COMPONENT console-gui-elements-lib-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/console-gui-elements-lib")

    set(targets_file "console-gui-elements-lib-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "console-gui-elements-lib-static-targets.cmake")
    endif()

    install(EXPORT console-gui-elements-lib_export
        COMPONENT console-gui-elements-lib-dev
        FILE "${targets_file}"
        DESTINATION "${CONSOLE-GUI-ELEMENTS-LIB_INSTALL_CMAKEDIR}"
        NAMESPACE console-gui-elements-lib::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/console-gui-elements-lib-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/console-gui-elements-lib-config-version.cmake"
        COMPONENT console-gui-elements-lib-dev
        DESTINATION "${CONSOLE-GUI-ELEMENTS-LIB_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:console-gui-elements-lib>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:console-gui-elements-lib>/$<TARGET_FILE_PREFIX:console-gui-elements-lib>$<TARGET_FILE_BASE_NAME:console-gui-elements-lib>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT console-gui-elements-lib-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()

#----------------------------------------------------------------------------------------------------------------------
# other targets
#----------------------------------------------------------------------------------------------------------------------

if(CONSOLE-GUI-ELEMENTS-LIB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(CONSOLE-GUI-ELEMENTS-LIB_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(CONSOLE-GUI-ELEMENTS-LIB_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()