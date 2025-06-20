find_package(Qt6 REQUIRED COMPONENTS Core Test Widgets Sql Gui Multimedia MultimediaWidgets)


set(CMAKE_AUTOMOC ON)

add_executable(gui_tests
    test_mainwindow.cpp
    ../mainwindow.cpp
    ../minimax.cpp
    ../ButtonAnimation.cpp
    ../hoverbutton.cpp
    ../PasswordTextEdit.cpp
)

target_link_libraries(gui_tests
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    Qt6::Test
    Qt6::Multimedia
    Qt6::MultimediaWidgets
Qt6::Sql
)

add_test(NAME gui_tests COMMAND gui_tests)
