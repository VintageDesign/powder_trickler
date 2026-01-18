find_package(Qt6 REQUIRED COMPONENTS Core Test)
find_package(GTest REQUIRED)

add_executable(test_powder_trickler
    test_control_manager.cpp
)

target_link_libraries(test_powder_trickler PRIVATE
    powder_trickler_lib
    Qt6::Test
    GTest::gtest
    GTest::gtest_main
)

add_test(NAME test_powder_trickler COMMAND test_powder_trickler)
