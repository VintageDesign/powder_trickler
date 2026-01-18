add_library(powder_trickler_lib STATIC
    controller/control_manager.cpp
    settings/settings_manager.cpp
    interfaces/abstract_controller_interface.cpp
    interfaces/uart_interface.cpp
)

target_include_directories(powder_trickler_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    qml/
    settings/
    controller/
)

target_link_libraries(powder_trickler_lib PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::SerialPort
)

qt_add_executable(powder_trickler_desktop
    main.cpp
)

qt_add_qml_module(powder_trickler_desktop
    URI PowderTrickler
    VERSION 1.0
    QML_FILES
        qml/main.qml
    SOURCES
        qml/run_screen_view.cpp
        qml/run_screen_view.h
        qml/settings_view.cpp
        qml/settings_view.h
)

target_link_libraries(powder_trickler_desktop PRIVATE
    powder_trickler_lib
)

set_target_properties(powder_trickler_desktop PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
