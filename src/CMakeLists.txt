cmake_minimum_required(VERSION 3.14)

project(sup-manager VERSION 1.0 LANGUAGES CXX)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

option(SUP_MANAGER_TESTING "Включить модульное тестирование" ON)
option(SUP_MANAGER_COVERAGE "Включить измерение покрытия кода тестами" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(is_top_level)
    find_package(console-gui-elements-lib REQUIRED)
    find_package(event-system REQUIRED)
    find_package(generic-core REQUIRED)
    find_package(generic-types REQUIRED)
    find_package(filesystem REQUIRED)
endif()

set(public_src
    controller/filespace_controller.cpp
    controller/main_workspace_controller.cpp
    render/render_processor.cpp
)

set(public_headers
    include/i_controller.hpp
    include/i_view.hpp
    model/filespace_model.hpp
    view/filespace_view.hpp
)
    
set(sources
    ${public_src}
    ${public_headers}
    main.cpp 
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_executable(sup-manager)
target_sources(sup-manager PRIVATE ${sources})

target_link_libraries(sup-manager 
    PRIVATE console-gui-elements-lib::console-gui-elements-lib
    PRIVATE event-system::event-system
    PRIVATE filesystem::filesystem
    PRIVATE generic-types::generic-types
    PRIVATE generic-core::generic-core
)