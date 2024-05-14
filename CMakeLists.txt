cmake_minimum_required(VERSION 3.10)
project(QuantumVisualizer)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (QT5_DIR C:\\Qt\\C++\\5.15.2\\mingw81_64\\)

find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)

set(CMAKE_PREFIX_PATH "C:\Qt\5.15.2\mingw81_64")


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)






add_executable(${PROJECT_NAME}
    main.cpp
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui
    QuantumSimulator.cpp
    QuantumSimulator.h
    HelpDialog.h
    HelpDialog.ui
)


target_include_directories(${PROJECT_NAME} PRIVATE ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} )

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    )
