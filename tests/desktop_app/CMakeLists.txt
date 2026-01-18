find_package(Qt6 REQUIRED COMPONENTS Core Test)
find_package(GTest REQUIRED)

add_executable(test_ui
    test_control_manager.cpp
    test_settings_manager.cpp
)

target_link_libraries(test_ui PRIVATE
    powder_trickler_lib
    Qt6::Test
    GTest::gtest
    GTest::gtest_main
)

add_test(NAME test_ui COMMAND test_ui)
