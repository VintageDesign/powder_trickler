cmake_minimum_required(VERSION 3.16)

project(powder_trickler_desktop_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

enable_testing()

find_package(Qt6 REQUIRED COMPONENTS Core Test)
find_package(GTest REQUIRED)

set(DESKTOP_APP_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../src/desktop_app)

add_executable(test_control_manager
    test_control_manager.cpp
    ${DESKTOP_APP_SRC_DIR}/controller/control_manager.cpp
    ${DESKTOP_APP_SRC_DIR}/run_screen_view.cpp
)

target_include_directories(test_control_manager PRIVATE
    ${DESKTOP_APP_SRC_DIR}
)

target_link_libraries(test_control_manager PRIVATE
    Qt6::Core
    Qt6::Test
    GTest::gtest
    GTest::gtest_main
)

add_test(NAME test_control_manager COMMAND test_control_manager)
