find_package(Qt6 REQUIRED COMPONENTS Core Test)
find_package(GTest REQUIRED)

set(DESKTOP_APP_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../src/desktop_app)

add_executable(test_ui_component
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

add_test(NAME test_ui_component COMMAND test_ui_component)
