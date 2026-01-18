find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(powder_trickler_desktop
    main.cpp
    run_screen_view.cpp
    run_screen_view.h
    controller/control_manager.cpp
    controller/control_manager.h
)

qt_add_qml_module(powder_trickler_desktop
    URI PowderTrickler
    VERSION 1.0
    QML_FILES
        main.qml
    SOURCES
        run_screen_view.cpp
        run_screen_view.h
)

target_include_directories(powder_trickler_desktop PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(powder_trickler_desktop PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

set_target_properties(powder_trickler_desktop PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
