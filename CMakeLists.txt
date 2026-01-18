cmake_minimum_required(VERSION 3.16)

project(powder_trickler VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_TESTS "Build tests" ON)

add_subdirectory(src/desktop_app)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests/desktop_app)
endif()
