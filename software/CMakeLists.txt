cmake_minimum_required(VERSION 3.16.3)

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/sdkconfig)
    message(FATAL_ERROR "sdkconfig not found")
endif()

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/config.cmake)
    message(FATAL_ERROR "config.cmake not found")
endif()

include(config.cmake)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_definitions(
    -DASIO_DISABLE_CONCEPTS=1
    -fdiagnostics-color=always
)

set(EXTRA_COMPONENT_DIRS
    esp-protocols/components
)

project(${APP_NAME})

set(expected_build_folder "${CMAKE_CURRENT_SOURCE_DIR}/build")
